#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"
#include "../../../kha-nodes/kha-led-ikea/kha-led-ikea-node/kha-led-ikea-node.X/main.h"
#include "../../../kha-nodes/kha-led-ikea/kha-led-const.h"

// ---

#define KEY_AMOUNT 3
#define ENC_AMOUNT 3

#define REGISTER_SIZE 1
#define REGISTER_PRESET_WIDTH 3

#define HSI_ADDR_DEST 0x00

// ---

static uint8_t hue = HSI_H_INIT;
static volatile uint8_t hue_next = HSI_H_INIT;
static uint8_t sat = HSI_S_INIT;
static volatile uint8_t sat_next = HSI_S_INIT;
static uint8_t intense = HSI_I_INIT;
static volatile uint8_t intense_next = HSI_I_INIT;

static volatile bool manual_interaction = false;

static const bool enc_overflow[ENC_AMOUNT] = {HSI_I_OVF, HSI_S_OVF, HSI_H_OVF};
static const uint8_t enc_min[ENC_AMOUNT] = {HSI_I_MIN, HSI_S_MIN, HSI_H_MIN};
static const uint8_t enc_max[ENC_AMOUNT] = {HSI_I_MAX, HSI_S_MAX, HSI_H_MAX};
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
        hue_next = encoder_range(key, hue_next, -64);
    }
    if (key == 1) {
        sat_next = encoder_flip(key, sat_next);
    }
    if (key == 0) {
        intense_next = encoder_flip(key, intense_next);
    }
}

void key_tick() {
    key_state[2] = (key_state[2] << 1) | !IO_BTN02P_GetValue();
    key_state[1] = (key_state[1] << 1) | !IO_BTN01P_GetValue();
    key_state[0] = (key_state[0] << 1) | !IO_BTN00P_GetValue();

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
        if (key == 2) {
            if (IO_BTN02A_GetValue()) enc_code = 3;
            if (IO_BTN02B_GetValue()) enc_code ^= 1; // convert gray to binary
        } else if (key == 1) {
            if (IO_BTN01A_GetValue()) enc_code = 3;
            if (IO_BTN01B_GetValue()) enc_code ^= 1; // convert gray to binary
        } else if (key == 0) {
            if (IO_BTN00A_GetValue()) enc_code = 3;
            if (IO_BTN00B_GetValue()) enc_code ^= 1; // convert gray to binary
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

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    if (enabled) {
        hue_next = kha_stack_register_get(addr + 0);
        sat_next = kha_stack_register_get(addr + 1);
        intense_next = kha_stack_register_get(addr + 2);

    }
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (addr == HSI_ADDR_DEST) {
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
        if (index == 1) {
            value = encoder_verify(2, value);
        }
        if (index == 2) {
            value = encoder_verify(1, value);
        }
        if (index == 3) {
            value = encoder_verify(0, value);
        }
    }

    return value;
}

void rx_all_register_slice(uint8_t addr, uint8_t value) {
    if (addr == IKEA_ADDR_HUE) {
        hue = encoder_verify(2, value);
        hue_next = encoder_verify(2, value);
    }
    if (addr == IKEA_ADDR_SATURATION) {
        sat = encoder_verify(1, value);
        sat_next = encoder_verify(1, value);
    }
    if (addr == IKEA_ADDR_INTENSE) {
        intense = encoder_verify(0, value);
        intense_next = encoder_verify(0, value);
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

        if (to == kha_stack_register_get(HSI_ADDR_DEST)) {
            for (uint8_t i = 0; i < reg_len; i++) {
                rx_all_register_slice(reg_addr + i, opt[i + 1]);
            }
        }
    }

    return false;
}

int main(void) {
    SYSTEM_Initialize();

    sei();

    kha_stack_register_cbr_change(register_change);
    kha_stack_preset_cbr_change(preset_change);
    kha_stack_rx_cbr_msg_all_post(rx_all);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    TCA0_Compare0CallbackRegister(tick);

    while (1) {

        for (uint8_t key = 0; key < ENC_AMOUNT; key++) {
            int8_t diff = enc_delta[key] >> 2;
            if (diff != 0) {
                enc_delta[key] = enc_delta[key] & 3;
                manual_interaction = true;
                if (key == 2) {
                    hue_next = encoder_range(key, hue_next, diff);
                } else if (key == 1) {
                    sat_next = encoder_range(key, sat_next, diff);
                } else if (key == 0) {
                    intense_next = encoder_range(key, intense_next, diff);
                }
            }
        }

        if (manual_interaction) {
            manual_interaction = false;
            manual_interaction_occured(true, true);
        }

        if (hue != hue_next) {
            hue = hue_next;
            uint8_t buf2[2] = {IKEA_ADDR_HUE, hue};
            kha_stack_tx_create(kha_stack_register_get(HSI_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
        if (sat != sat_next) {
            sat = sat_next;
            uint8_t buf2[2] = {IKEA_ADDR_SATURATION, sat};
            kha_stack_tx_create(kha_stack_register_get(HSI_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
        if (intense != intense_next) {
            intense = intense_next;
            uint8_t buf2[2] = {IKEA_ADDR_INTENSE, intense};
            kha_stack_tx_create(kha_stack_register_get(HSI_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}
