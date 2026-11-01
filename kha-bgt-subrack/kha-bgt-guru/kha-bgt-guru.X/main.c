#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/system/utils/atomic.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---
#define KEY_AMOUNT 1

#define REGISTER_SIZE 2
#define REGISTER_PRESET_WIDTH 0

#define GURU_ADDR_DEST 0x00
#define GURU_ADDR_INTERVAL_MIN 0x01

// GURU_ADDR_DEST: 0x00 = poll all nodes one by one, 0x01-0xEF = poll one node, others = broadcast/group as before
#define GURU_DEST_SEQUENCE KHA_ADDR_NONE
#define GURU_UNICAST_MIN KHA_ADDR_UNICAST_FALLBACK
#define GURU_UNICAST_MAX (KHA_ADDR_BROADCAST_GROUP_FALLBACK - 1)

#define POLL_TIMEOUT_MARGIN_10MS 5 // on top of the reply slot, addr / 20 x 10 ms is more than the stack's slot
#define BLINK_PERIOD_10MS 50

// ---

typedef enum {
    POLL_IDLE,
    POLL_SEND,
    POLL_SENT,
    POLL_WAIT
} POLL_STATE_t;

typedef enum {
    POLL_MODE_SCAN, // all unicast addresses, remember who answers
    POLL_MODE_KNOWN, // only nodes that answered the last scan
    POLL_MODE_DIRECT // one node
} POLL_MODE_t;

static POLL_STATE_t poll_state = POLL_IDLE;
static POLL_MODE_t poll_mode = POLL_MODE_SCAN;
static uint8_t poll_addr = 0;
static bool poll_retry = false;
static bool poll_answered = false;
static uint16_t poll_start_10ms = 0;

static uint8_t nodes_known[32];
static uint8_t nodes_missing[32];

static bool blink_dark = false;
static volatile uint16_t now_10ms = 0;

// ---

static const uint8_t DIGITS[17] = {0b00111111, 0b00011000, 0b01101101, 0b01111100, 0b01011010, 0b01110110, 0b01110111, 0b00111000, 0b01111111, 0b01111110, 0b01111011, 0b01010111, 0b00100111, 0b01011101, 0b01100111, 0b01100011, 0b01000000};

static volatile bool sendClear = false;
static volatile bool sendRequest = false;
static bool dataAvailable = false;
static uint8_t error = 0; // highest single error counter (RX or TX) of any node
static uint8_t error_addr = 0; // the node it came from, 0 = none yet
static volatile uint32_t period_10ms = 0;
static volatile uint32_t tick = 0;

static volatile bool manual_interaction = false;

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

void key_pressed(uint8_t key) {
    manual_interaction = true;
    if (key == 0) {
        sendClear = true;
    }
}

void key_tick() {
    now_10ms++;
    tick++;
    if (tick > period_10ms && period_10ms != 0) {
        tick = 0;
        sendRequest = true;
    }

    key_state[0] = (key_state[0] << 1) | !IO_BTN_CLEAR_GetValue();

    for (uint8_t i = 0; i < KEY_AMOUNT; i++) {
        uint8_t key_masked = (key_state[i] & key_mask);
        if (!key_down[i] && key_masked == key_mask) {
            key_down[i] = true;
            key_pressed(i);
        }
        if (key_down[i] && key_masked == 0b00000000) {
            key_down[i] = false;
        }
    }
}

// ---

void sendRaw(uint8_t buf) {
    for (uint8_t i = 0; i < 8; i++) {
        IO_CLK_SetLow();
        if (buf & (1 << i)) {
            IO_DAT_SetHigh();
        } else {
            IO_DAT_SetLow();
        }
        asm("nop"); // 41.6ns
        asm("nop"); // 41.6ns
        asm("nop"); // 41.6ns
        asm("nop"); // 41.6ns

        IO_CLK_SetHigh();
        asm("nop"); // 41.6ns
        asm("nop"); // 41.6ns
        asm("nop"); // 41.6ns
        asm("nop"); // 41.6ns
    }
}

void sendTM1620Cmd(uint8_t cmd) {
    IO_CS_SetLow();
    sendRaw(cmd);
    asm("nop"); // 41.6ns
    IO_CS_SetHigh();
    asm("nop"); // 41.6ns
}

void sendTM1620CmdData(uint8_t cmd, uint8_t data) {
    IO_CS_SetLow();
    sendRaw(cmd);
    sendRaw(data);
    asm("nop"); // 41.6ns
    IO_CS_SetHigh();
    asm("nop"); // 41.6ns
}

// ---

void update_ui() {
    if (kha_stack_ui_enabled() && !blink_dark) {
        sendTM1620Cmd(0b10001100); // On
    } else {
        sendTM1620Cmd(0b10000100); // Off
    }

    if (!dataAvailable) {
        sendTM1620CmdData(0b11000000 | 0x0A, DIGITS[0x10]);
        sendTM1620CmdData(0b11000000 | 0x08, DIGITS[0x10]);
        sendTM1620CmdData(0b11000000 | 0x04, DIGITS[0x10]);
        sendTM1620CmdData(0b11000000 | 0x06, DIGITS[0x10]);
    } else {
        // top: highest error, bottom: the node it came from (-- while no node had an error)
        sendTM1620CmdData(0b11000000 | 0x0A, DIGITS[error >> 4]);
        sendTM1620CmdData(0b11000000 | 0x08, DIGITS[error & 0x0F]);
        sendTM1620CmdData(0b11000000 | 0x04, error_addr ? DIGITS[error_addr >> 4] : DIGITS[0x10]);
        sendTM1620CmdData(0b11000000 | 0x06, error_addr ? DIGITS[error_addr & 0x0F] : DIGITS[0x10]);
    }
}

// NODES -----------------------------------------------------------------------

bool nodes_get(uint8_t nodes[], uint8_t addr) {
    return nodes[addr >> 3] & (1 << (addr & 0x07));
}

void nodes_set(uint8_t nodes[], uint8_t addr, bool value) {
    if (value) {
        nodes[addr >> 3] |= (1 << (addr & 0x07));
    } else {
        nodes[addr >> 3] &= ~(1 << (addr & 0x07));
    }
}

bool nodes_any(uint8_t nodes[]) {
    for (uint8_t i = 0; i < sizeof (nodes_known); i++) {
        if (nodes[i]) {
            return true;
        }
    }
    return false;
}

void nodes_clear(uint8_t nodes[]) {
    memset(nodes, 0, sizeof (nodes_known));
}

// POLL ------------------------------------------------------------------------

uint16_t now_get() {
    ENTER_CRITICAL(R);
    uint16_t now = now_10ms;
    EXIT_CRITICAL(R);
    return now;
}

void interval_restart() {
    ENTER_CRITICAL(R);
    tick = 0;
    EXIT_CRITICAL(R);
}

bool dest_sequence() {
    return kha_stack_register_get(GURU_ADDR_DEST) == GURU_DEST_SEQUENCE;
}

bool dest_direct() {
    uint8_t dest = kha_stack_register_get(GURU_ADDR_DEST);
    return dest >= GURU_UNICAST_MIN && dest <= GURU_UNICAST_MAX && dest != kha_stack_device_address_get();
}

// Next address to poll after addr, 0 if there is none
uint8_t poll_next(uint8_t addr) {
    while (addr < GURU_UNICAST_MAX) {
        addr++;
        if (addr == kha_stack_device_address_get()) {
            continue;
        }
        if (poll_mode == POLL_MODE_SCAN || nodes_get(nodes_known, addr)) {
            return addr;
        }
    }
    return 0;
}

void poll_begin(POLL_MODE_t mode, uint8_t addr) {
    poll_mode = mode;
    poll_addr = (mode == POLL_MODE_DIRECT) ? addr : poll_next(0);
    poll_retry = false;
    poll_state = poll_addr ? POLL_SEND : POLL_IDLE;
}

void poll_scan() {
    nodes_clear(nodes_known);
    nodes_clear(nodes_missing);
    poll_begin(POLL_MODE_SCAN, 0);
}

void poll_known() {
    if (!nodes_any(nodes_known)) {
        poll_scan();
        return;
    }
    poll_begin(POLL_MODE_KNOWN, 0);
}

void poll_advance() {
    poll_retry = false;
    if (poll_mode == POLL_MODE_DIRECT) {
        poll_state = POLL_IDLE;
        return;
    }
    poll_addr = poll_next(poll_addr);
    poll_state = poll_addr ? POLL_SEND : POLL_IDLE;
}

void poll_process() {
    switch (poll_state) {
        case POLL_IDLE:
            break;

        case POLL_SEND:
            poll_answered = false;
            kha_stack_tx_create(poll_addr, KHA_CMD_DEVICE_STATS_REQUEST, 0, NULL);
            poll_state = POLL_SENT;
            break;

        case POLL_SENT:
            // kha_stack_process_rx_tx() has waited for our slot and sent the request
            poll_start_10ms = now_get();
            poll_state = POLL_WAIT;
            break;

        case POLL_WAIT:
            if (poll_answered) {
                if (poll_mode == POLL_MODE_SCAN) {
                    nodes_set(nodes_known, poll_addr, true);
                }
                nodes_set(nodes_missing, poll_addr, false);
                poll_advance();
                break;
            }
            if ((uint16_t) (now_get() - poll_start_10ms) <= (poll_addr / 20) + POLL_TIMEOUT_MARGIN_10MS) {
                break;
            }
            if (poll_mode == POLL_MODE_SCAN) {
                poll_advance();
                break;
            }
            if (!poll_retry) {
                poll_retry = true;
                poll_state = POLL_SEND;
                break;
            }
            nodes_set(nodes_missing, poll_addr, true);
            poll_advance();
            break;
    }
}

void blink_process() {
    bool dark = nodes_any(nodes_missing) && ((now_get() / BLINK_PERIOD_10MS) & 0x01);
    if (dark != blink_dark) {
        blink_dark = dark;
        update_ui();
    }
}

// REGISTER --------------------------------------------------------------------

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (addr == GURU_ADDR_DEST) {
            poll_state = POLL_IDLE;
            nodes_clear(nodes_known);
            nodes_clear(nodes_missing);
            dataAvailable = false;
            error = 0;
            error_addr = 0;
            update_ui();
        }
        if (addr == GURU_ADDR_INTERVAL_MIN) {
            period_10ms = value * 100UL * 60UL;
        }
    }

    if (addr >= REGISTER_SIZE && REGISTER_PRESET_WIDTH > 0) {
        uint8_t index = addr - REGISTER_SIZE - ((addr - REGISTER_SIZE) / (REGISTER_PRESET_WIDTH + 1) * (REGISTER_PRESET_WIDTH + 1));
        if (index == 0) {
            if (value > 1) {
                value = 0;
            }
        }
    }

    return value;
}

bool rx_all(uint8_t msg[KHA_MSG_LEN_MAX]) {
    uint8_t size = msg[0];
    uint8_t from = msg[1];
    uint8_t to = msg[2];
    uint8_t cmd = msg[3];
    uint8_t optlen = size - KHA_MSG_LEN_MIN;

    uint8_t opt[optlen];
    for (uint8_t i = 0; i < optlen; i++) {
        opt[i] = msg[4 + i];
    }

    if (cmd == KHA_CMD_DEVICE_STATS_CLEAR && to == kha_stack_register_get(GURU_ADDR_DEST)) {
        dataAvailable = false;
        error = 0;
        error_addr = 0;
        update_ui();
    }

    if (cmd == KHA_CMD_DEVICE_STATS_RESPONSE && to == kha_stack_device_address_get()) {
        if (optlen != KHA_STATS_LEN) {
            return false;
        }

        if ((poll_state == POLL_SENT || poll_state == POLL_WAIT) && from == poll_addr) {
            poll_answered = true;
        }

        for (uint8_t i = 0; i < KHA_STATS_LEN; i++) {
            if (i == KHA_STATS_RX || i == KHA_STATS_TX) {
                continue;
            }
            if (opt[i] > error) {
                error = opt[i];
                error_addr = from;
            }
        }

        dataAvailable = true;
        update_ui();

        return true;
    }

    return false;
}

int main(void) {
    SYSTEM_Initialize();

    sei();

    kha_stack_register_cbr_change(register_change);
    kha_stack_ui_cbr_change(update_ui);
    kha_stack_rx_cbr_msg_all_post(rx_all);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    IO_CS_SetHigh();
    IO_CLK_SetHigh();

    DELAY_milliseconds(300);

    sendTM1620Cmd(0b00000010); // 6 digits, 8 segments
    sendTM1620Cmd(0b01000100); // Fixed Address
    for (uint8_t i = 0; i < 0x0B; i++) {
        sendTM1620CmdData(0b11000000 | i, 0b00000000); // Clear
    }
    sendTM1620CmdData(0b11000000 | 0x0A, DIGITS[0x10]);
    sendTM1620CmdData(0b11000000 | 0x08, DIGITS[0x10]);
    sendTM1620CmdData(0b11000000 | 0x04, DIGITS[0x10]);
    sendTM1620CmdData(0b11000000 | 0x06, DIGITS[0x10]);
    sendTM1620Cmd(0b10001100); // On    

    update_ui();

    TCA0_Compare0CallbackRegister(key_tick);

    while (1) {
        if (manual_interaction) {
            manual_interaction = false;
            kha_stack_manual_interaction_occured(true, false);
        }

        if (sendClear) {
            sendClear = false;
            dataAvailable = false;
            error = 0;
            error_addr = 0;
            nodes_clear(nodes_missing);
            update_ui();
            kha_stack_stats_clear();
            interval_restart();
            if (dest_sequence()) {
                kha_stack_tx_create(KHA_ADDR_BROADCAST, KHA_CMD_DEVICE_STATS_CLEAR, 0, NULL);
                poll_scan();
            } else {
                kha_stack_tx_create(kha_stack_register_get(GURU_ADDR_DEST), KHA_CMD_DEVICE_STATS_CLEAR, 0, NULL);
                sendRequest = true;
            }
        }

        if (sendRequest) {
            sendRequest = false;
            if (dest_sequence()) {
                if (poll_state == POLL_IDLE) {
                    poll_known();
                }
            } else if (dest_direct()) {
                poll_begin(POLL_MODE_DIRECT, kha_stack_register_get(GURU_ADDR_DEST));
            } else {
                kha_stack_tx_create(kha_stack_register_get(GURU_ADDR_DEST), KHA_CMD_DEVICE_STATS_REQUEST, 0, NULL);
            }
        }

        poll_process();
        blink_process();

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}