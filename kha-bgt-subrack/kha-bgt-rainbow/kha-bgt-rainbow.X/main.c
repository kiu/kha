#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "../../../kha-nodes/kha-led-strip/kha-led-strip.X/led-generic.h"
#include "../../../kha-nodes/kha-led-ikea/kha-led-const.h"
#include "kha-version.h"

// ---

#define KEY_AMOUNT 3
#define ENC_AMOUNT 2

#define REGISTER_SIZE 1
#define REGISTER_PRESET_WIDTH 3

#define RAINBOW_ADDR_DEST 0x00

// ---

static uint8_t speed = ANIM_S_INIT;
static volatile uint8_t speed_next = ANIM_S_INIT;
static uint8_t width = ANIM_W_INIT;
static volatile uint8_t width_next = ANIM_W_INIT;

static bool enabled = ANIM_E_INIT;
static volatile bool enabled_next = ANIM_E_INIT;

enum BTN_STATE {
    BTN_STATE_RD_OG, BTN_STATE_GN, BTN_STATE_OFF
};
static uint8_t btn_state[1] = {BTN_STATE_RD_OG};

static volatile bool manual_interaction = false;

static const bool enc_overflow[ENC_AMOUNT] = {ANIM_W_OVF, ANIM_S_OVF};
static const uint8_t enc_min[ENC_AMOUNT] = {ANIM_W_MIN, ANIM_S_MIN};
static const uint8_t enc_max[ENC_AMOUNT] = {ANIM_W_MAX, ANIM_S_MAX};
static int8_t enc_last[ENC_AMOUNT];
static volatile int8_t enc_delta[ENC_AMOUNT]; // -128 ... 127

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

uint8_t encoder_verify(uint8_t key, uint8_t value) {
    if (value < enc_min[key]) {
        return enc_min[key];
    }
    if (value > enc_max[key]) {
        return enc_max[key];
    }
    return value;
}

uint8_t encoder_range(uint8_t key, uint8_t current, int8_t diff) {
    int16_t val = current - diff;
    if (!enc_overflow[key]) {
        if (diff > 0 && val < enc_min[key]) {
            return enc_min[key];
        }
        if (diff < 0 && val > enc_max[key]) {
            return enc_max[key];
        }
    } else {
        if (diff > 0 && val < enc_min[key]) {
            return enc_max[key] - (enc_min[key] - val) + 1;
        }
        if (diff < 0 && val > enc_max[key]) {
            return enc_min[key] + (val - enc_max[key]) - 1;
        }
    }
    return val;
}

uint8_t encoder_flip(uint8_t key, uint8_t current) {
    if (current <= enc_min[key]) {
        return enc_max[key];
    }
    if (current >= enc_max[key]) {
        return enc_min[key];
    }

    if (current >= (enc_max[key] - enc_min[key]) / 2) {
        return enc_max[key];
    } else {
        return enc_min[key];
    }
}

void key_pressed(uint8_t key) {
    manual_interaction = true;
    if (key == 2) {
        speed_next = encoder_flip(key - 1, speed_next);
    }
    if (key == 1) {
        width_next = encoder_flip(key - 1, width_next);
    }
    if (key == 0) {
        enabled_next = !enabled_next;
    }
}

void key_tick() {
    key_state[2] = (key_state[2] << 1) | !IO_BTN02P_GetValue();
    key_state[1] = (key_state[1] << 1) | !IO_BTN01P_GetValue();
    key_state[0] = (key_state[0] << 1) | !IO_LED00P_GetValue();

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

void encoder_tick() {
    int8_t enc_code, enc_diff;
    for (uint8_t key = 0; key < ENC_AMOUNT; key++) {
        enc_code = 0;
        if (key == 1) {
            if (IO_BTN02A_GetValue()) enc_code = 3;
            if (IO_BTN02B_GetValue()) enc_code ^= 1; // convert gray to binary
        } else if (key == 0) {
            if (IO_BTN01A_GetValue()) enc_code = 3;
            if (IO_BTN01B_GetValue()) enc_code ^= 1; // convert gray to binary
        }

        enc_diff = enc_last[key] - enc_code; // difference last - new
        if (enc_diff & 1) { // bit 0 = value (1)
            enc_last[key] = enc_code; // store new as next last
            enc_delta[key] += (enc_diff & 2) - 1; // bit 1 = direction (+/-)
        }
    }
}

void tick() {
    key_tick();
    encoder_tick();
}

// ---

void update_ui() {
    if (!kha_stack_ui_enabled()) {
        IO_LED00A_SetLow();
        IO_LED00B_SetLow();
        return;
    }

    if (btn_state[0] == BTN_STATE_OFF) {
        IO_LED00A_SetLow();
        IO_LED00B_SetLow();
    } else if (btn_state[0] == BTN_STATE_GN) {
        IO_LED00A_SetLow();
        IO_LED00B_SetHigh();
    } else if (btn_state[0] == BTN_STATE_RD_OG) {
        IO_LED00A_SetHigh();
        IO_LED00B_SetLow();
    }
}

void mode_change(bool notify) {
    if (speed != speed_next) {
        speed = speed_next;
        enabled_next = true;
        if (notify) {
            uint8_t buf2[2] = {LED_ADDR_ANIM_SPEED, speed};
            kha_stack_tx_create(kha_stack_register_get(RAINBOW_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
    }
    if (width != width_next) {
        width = width_next;
        enabled_next = true;
        if (notify) {
            uint8_t buf2[2] = {LED_ADDR_ANIM_WIDTH, width};
            kha_stack_tx_create(kha_stack_register_get(RAINBOW_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
    }
    if (enabled != enabled_next) {
        enabled = enabled_next;
        if (enabled) {
            btn_state[0] = BTN_STATE_GN;
        } else {
            btn_state[0] = BTN_STATE_RD_OG;
        }
        update_ui();
        if (notify) {
            uint8_t buf2[2] = {LED_ADDR_ANIM_ENABLED, enabled};
            kha_stack_tx_create(kha_stack_register_get(RAINBOW_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
    }
}

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    if (enabled) {
        speed_next = kha_stack_register_get(addr + 0);
        width_next = kha_stack_register_get(addr + 1);
        enabled_next = kha_stack_register_get(addr + 2);
    }
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (addr == RAINBOW_ADDR_DEST) {
            if (value == 0xFF) {
                value = 0x00;
            }
        }
    }

    if (addr >= REGISTER_SIZE && REGISTER_PRESET_WIDTH > 0) {
        uint8_t index = addr - REGISTER_SIZE - ((addr - REGISTER_SIZE) / (REGISTER_PRESET_WIDTH + 1) * (REGISTER_PRESET_WIDTH + 1));
        if (index == 0) {
            if (value > 1) {
                value = 0;
            }
        }
        if (index == 1) { // speed
            value = encoder_verify(1, value);
        }
        if (index == 2) { // width
            value = encoder_verify(0, value);
        }
        if (index == 3) {
            if (value > 1) {
                value = 0;
            }
        }
    }

    return value;
}

void rx_all_register_slice(uint8_t addr, uint8_t value) {
    if (addr == LED_ADDR_ANIM_ENABLED) {
        enabled_next = value;
        mode_change(false);
    }
    if (addr == LED_ADDR_ANIM_SPEED) {
        speed_next = encoder_verify(1, value);
        mode_change(false);
    }
    if (addr == LED_ADDR_ANIM_WIDTH) {
        width_next = encoder_verify(0, value);
        mode_change(false);
    }
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

    if (cmd == KHA_CMD_REGISTER_WRITE_REQUEST || cmd == KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY) {
        uint16_t reg_addr = opt[0];
        uint8_t reg_len = optlen - 1;

        if (reg_addr >= KHA_STACK_EEPROM_REGISTER_LEN) {
            return false;
        }
        if (reg_len > KHA_STACK_EEPROM_REGISTER_LEN) {
            return false;
        }
        if (reg_addr + reg_len > KHA_STACK_EEPROM_REGISTER_LEN) {
            return false;
        }

        if (to == kha_stack_register_get(RAINBOW_ADDR_DEST)) {
            for (uint8_t i = 0; i < reg_len; i++) {
                rx_all_register_slice(reg_addr + i, opt[i + 1]);
            }
        }
    }

    return false;
}

int main(void) {
    SYSTEM_Initialize();

    speed_next = enc_min[1];
    width_next = enc_min[0];

    sei();

    kha_stack_register_cbr_change(register_change);
    kha_stack_ui_cbr_change(update_ui);
    kha_stack_preset_cbr_change(preset_change);
    kha_stack_rx_cbr_msg_all_post(rx_all);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    update_ui();

    TCA0_Compare0CallbackRegister(tick);

    while (1) {
        for (uint8_t key = 0; key < ENC_AMOUNT; key++) {
            int8_t diff = enc_delta[key] >> 2;
            if (diff != 0) {
                enc_delta[key] = enc_delta[key] & 3;
                manual_interaction = true;
                enabled_next = true;
                if (key == 1) {
                    speed_next = encoder_range(key, speed_next, diff);
                } else if (key == 0) {
                    width_next = encoder_range(key, width_next, diff);
                }
            }
        }

        if (manual_interaction) {
            manual_interaction = false;
            manual_interaction_occured(true, true);
        }

        mode_change(true);

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}