#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "mcc_generated_files/spi/spi0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---
#define KEY_AMOUNT 1

#define REGISTER_SIZE 2
#define REGISTER_PRESET_WIDTH 0

#define GURU_ADDR_DEST 0x00
#define GURU_ADDR_INTERVAL_MIN 0x01

// ---

static const uint8_t DIGITS[17] = {0b00111111, 0b00011000, 0b01101101, 0b01111100, 0b01011010, 0b01110110, 0b01110111, 0b00111000, 0b01111111, 0b01111110, 0b01111011, 0b01010111, 0b00100111, 0b01011101, 0b01100111, 0b01100011, 0b01000000};

static volatile bool sendClear = false;
static volatile bool sendRequest = false;
static bool dataAvailable = false;
static uint8_t rx_error = 0;
static uint8_t tx_error = 0;
static volatile uint32_t period_10ms = 0;
static uint32_t tick = 0;

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

unsigned char reverse(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void sendTM1620Cmd(uint8_t cmd) {
    cmd = reverse(cmd);
    IO_CS_SetLow();
    DELAY_microseconds(4);
    SPI0_ByteWrite(cmd);
    DELAY_microseconds(50);
    IO_CS_SetHigh();
    DELAY_microseconds(4);
}

void sendTM1620CmdData(uint8_t cmd, uint8_t data) {
    cmd = reverse(cmd);
    data = reverse(data);
    IO_CS_SetLow();
    DELAY_microseconds(4);
    SPI0_ByteWrite(cmd);
    SPI0_ByteWrite(data);
    DELAY_microseconds(90);
    IO_CS_SetHigh();
    DELAY_microseconds(4);
}

// ---

void update_ui() {
    if (kha_stack_ui_enabled()) {
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
        sendTM1620CmdData(0b11000000 | 0x0A, DIGITS[rx_error >> 4]);
        sendTM1620CmdData(0b11000000 | 0x08, DIGITS[rx_error & 0x0F]);
        sendTM1620CmdData(0b11000000 | 0x04, DIGITS[tx_error >> 4]);
        sendTM1620CmdData(0b11000000 | 0x06, DIGITS[tx_error & 0x0F]);
    }
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (addr == GURU_ADDR_DEST) {
            dataAvailable = false;
            rx_error = 0;
            tx_error = 0;
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
    //uint8_t from = msg[1];
    uint8_t to = msg[2];
    uint8_t cmd = msg[3];
    uint8_t optlen = size - KHA_MSG_LEN_MIN;

    uint8_t opt[optlen];
    for (uint8_t i = 0; i < optlen; i++) {
        opt[i] = msg[4 + i];
    }

    if (cmd == KHA_CMD_DEVICE_STATS_CLEAR && to == kha_stack_register_get(GURU_ADDR_DEST)) {
        dataAvailable = false;
        rx_error = 0;
        tx_error = 0;
        update_ui();
    }

    if (cmd == KHA_CMD_DEVICE_STATS_RESPONSE && to == kha_stack_device_address_get()) {
        if (optlen != 8) {
            return false;
        }

        if (opt[1] > rx_error) rx_error = opt[1]; // kha_stack_stats.rx_error_start_unescaped;
        if (opt[2] > rx_error) rx_error = opt[2]; // kha_stack_stats.rx_error_start_missing;
        if (opt[3] > rx_error) rx_error = opt[3]; // kha_stack_stats.rx_error_len;
        if (opt[4] > rx_error) rx_error = opt[4]; // kha_stack_stats.rx_error_crc;

        if (opt[6] > tx_error) tx_error = opt[6]; // kha_stack_stats.tx_error_len;
        if (opt[7] > tx_error) tx_error = opt[7]; // kha_stack_stats.tx_error_full;

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

    SPI0_Open(0);
    IO_CS_SetHigh();

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
            manual_interaction_occured(true, false);
        }

        if (sendClear) {
            sendClear = false;
            dataAvailable = false;
            rx_error = 0;
            tx_error = 0;
            update_ui();
            kha_stack_stats_clear();
            kha_stack_tx_create(kha_stack_register_get(GURU_ADDR_DEST), KHA_CMD_DEVICE_STATS_CLEAR, 0, NULL);
            sendRequest = true;
        }

        if (sendRequest) {
            sendRequest = false;
            kha_stack_tx_create(kha_stack_register_get(GURU_ADDR_DEST), KHA_CMD_DEVICE_STATS_REQUEST, 0, NULL);
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}