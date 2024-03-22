#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---

#define KEY_AMOUNT 4

#define REGISTER_SIZE KEY_AMOUNT * 2
#define REGISTER_PRESET_WIDTH 4

// ---

static const uint32_t tick_interval_10ms = 100UL * 60UL * 5UL;
static uint32_t tick = (100UL * 60UL * 5UL) - (100UL * 3UL);
static volatile bool tick_exec = false;

enum BTN_STATE {
    BTN_STATE_RD_OG, BTN_STATE_GN, BTN_STATE_OFF
};
static uint8_t btn_state[KEY_AMOUNT] = {BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF};
static volatile uint8_t btn_state_next[KEY_AMOUNT] = {BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF};

static volatile bool manual_interaction = false;

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

void key_pressed(uint8_t key) {
    manual_interaction = true;
    if (btn_state[key] == BTN_STATE_RD_OG) {
        btn_state_next[key] = BTN_STATE_GN;
    }
    if (btn_state[key] == BTN_STATE_GN) {
        btn_state_next[key] = BTN_STATE_RD_OG;
    }
}

void key_tick() {
    tick++;
    if (tick > tick_interval_10ms) {
        tick = 0;
        tick_exec = true;
    }

    key_state[3] = (key_state[3] << 1) | !IO_BTN03_GetValue();
    key_state[2] = (key_state[2] << 1) | !IO_BTN02_GetValue();
    key_state[1] = (key_state[1] << 1) | !IO_BTN01_GetValue();
    key_state[0] = (key_state[0] << 1) | !IO_BTN00_GetValue();

    for (uint8_t key = 0; key < KEY_AMOUNT; key++) {
        uint8_t key_masked = (key_state[key] & key_mask);
        if (!key_down[key] && key_masked == key_mask) {
            key_down[key] = true;
            key_pressed(key);
        }
        if (key_down[key] && key_masked == 0b00000000) {
            key_down[key] = false;
        }
    }
}

// ---

bool change(uint8_t btn, uint8_t state, bool notify) {
    if (notify && btn_state[btn] == BTN_STATE_OFF) {
        btn_state_next[btn] = BTN_STATE_OFF;
        return false;
    }

    btn_state_next[btn] = state;
    if (btn_state[btn] == state) {
        return false;
    }
    btn_state[btn] = state;

    if (notify && state != BTN_STATE_OFF) {
        uint8_t dev_id = kha_stack_register_get(btn * 2);
        uint8_t reg_addr = kha_stack_register_get(btn * 2 + 1);
        if (dev_id != 0x00 && dev_id != 0xFF && reg_addr != 0xFF) {
            uint8_t buf2[2] = {reg_addr, btn_state[btn]};
            kha_stack_tx_create(dev_id, KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
    }

    return true;
}

// ---

void update_ui() {
    if (!kha_stack_ui_enabled()) {
        IO_LED03A_SetLow();
        IO_LED03B_SetLow();

        IO_LED02A_SetLow();
        IO_LED02B_SetLow();

        IO_LED01A_SetLow();
        IO_LED01B_SetLow();

        IO_LED00A_SetLow();
        IO_LED00B_SetLow();

        return;
    }

    if (btn_state[3] == BTN_STATE_GN) {
        IO_LED03A_SetLow();
        IO_LED03B_SetHigh();
    } else if (btn_state[3] == BTN_STATE_RD_OG) {
        IO_LED03A_SetHigh();
        IO_LED03B_SetLow();
    } else {
        IO_LED03A_SetLow();
        IO_LED03B_SetLow();
    }

    if (btn_state[2] == BTN_STATE_GN) {
        IO_LED02A_SetLow();
        IO_LED02B_SetHigh();
    } else if (btn_state[2] == BTN_STATE_RD_OG) {
        IO_LED02A_SetHigh();
        IO_LED02B_SetLow();
    } else {
        IO_LED02A_SetLow();
        IO_LED02B_SetLow();
    }

    if (btn_state[1] == BTN_STATE_GN) {
        IO_LED01A_SetLow();
        IO_LED01B_SetHigh();
    } else if (btn_state[1] == BTN_STATE_RD_OG) {
        IO_LED01A_SetHigh();
        IO_LED01B_SetLow();
    } else {
        IO_LED01A_SetLow();
        IO_LED01B_SetLow();
    }

    if (btn_state[0] == BTN_STATE_GN) {
        IO_LED00A_SetLow();
        IO_LED00B_SetHigh();
    } else if (btn_state[0] == BTN_STATE_RD_OG) {
        IO_LED00A_SetHigh();
        IO_LED00B_SetLow();
    } else {
        IO_LED00A_SetLow();
        IO_LED00B_SetLow();
    }
}

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    if (enabled) {
        bool changed = false;
        for (uint8_t btn = 0; btn < KEY_AMOUNT; btn++) {
            uint8_t val = kha_stack_register_get(addr + btn);
            if (val < 2) {
                changed |= change(btn, val, true);
            }
        }
        if (changed) {
            update_ui();
        }
    }
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (addr % 2 == 0) {
            if (value == 0x00 || value > 0xEF) {
                value = 0xFF;
            }
        } else {
            if (value > KHA_STACK_EEPROM_REGISTER_LEN) {
                value = 0xFF;
            }
        }
        btn_state_next[addr / 2] = BTN_STATE_OFF;
    }

    if (addr >= REGISTER_SIZE && REGISTER_PRESET_WIDTH > 0) {
        uint8_t index = addr - REGISTER_SIZE - ((addr - REGISTER_SIZE) / (REGISTER_PRESET_WIDTH + 1) * (REGISTER_PRESET_WIDTH + 1));
        if (index == 0) {
            if (value > 1) {
                value = 0;
            }
        }
        if (index == 1) {
            if (value > 2) {
                value = 2;
            }
        }
    }

    return value;
}

bool rx_all_register_slice(uint8_t id, uint8_t addr, uint8_t value) {
    if (id == KHA_ADDR_NONE) {
        return false;
    }
    if (id == KHA_ADDR_BROADCAST) {
        return false;
    }

    if (value > 1) {
        value = 0;
    }
    bool changed = false;
    for (uint8_t btn = 0; btn < KEY_AMOUNT; btn++) {
        if (id == kha_stack_register_get(btn * 2) && addr == kha_stack_register_get(btn * 2 + 1)) {
            changed |= change(btn, value, false);
        }
    }
    return changed;
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

    bool changed = false;
    if (cmd == KHA_CMD_REGISTER_READ_RESPONSE) {
        uint16_t reg_addr = opt[0];
        uint8_t reg_len = optlen - 1;
        for (uint8_t i = 0; i < reg_len; i++) {
            changed |= rx_all_register_slice(from, reg_addr + i, opt[i + 1]);
        }
    }
    if (cmd == KHA_CMD_REGISTER_WRITE_REQUEST || cmd == KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY) {
        uint16_t reg_addr = opt[0];
        uint8_t reg_len = optlen - 1;
        for (uint8_t i = 0; i < reg_len; i++) {
            changed |= rx_all_register_slice(to, reg_addr + i, opt[i + 1]);
        }
    }

    if (changed) {
        update_ui();
    }

    return false;
}

int main(void) {
    SYSTEM_Initialize();

    sei();

    kha_stack_register_cbr_change(register_change);
    kha_stack_ui_cbr_change(update_ui);
    kha_stack_preset_cbr_change(preset_change);
    kha_stack_rx_cbr_msg_all_post(rx_all);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    update_ui();

    TCA0_Compare0CallbackRegister(key_tick);

    while (1) {
        if (manual_interaction) {
            manual_interaction = false;
            manual_interaction_occured(true, true);
        }

        if (tick_exec) {
            tick_exec = false;
            for (uint8_t btn = 0; btn < KEY_AMOUNT; btn++) {
                if (btn_state[btn] != BTN_STATE_OFF) {
                    continue;
                }
                uint8_t dev_id = kha_stack_register_get(btn * 2);
                uint8_t reg_addr = kha_stack_register_get(btn * 2 + 1);
                if (dev_id != 0xFF && dev_id != 0x00 && reg_addr != 0xFF) {
                    uint8_t buf2[2] = {reg_addr, 0x01};
                    kha_stack_tx_create(dev_id, KHA_CMD_REGISTER_READ_REQUEST, 2, buf2);
                }
            }
        }

        bool changed = false;
        for (uint8_t btn = 0; btn < KEY_AMOUNT; btn++) {
            if (btn_state_next[btn] != btn_state[btn]) {
                changed |= change(btn, btn_state_next[btn], true);
            }
        }
        if (changed) {
            update_ui();
        }

        kha_stack_process_rx_tx();
        asm("wdr");
    }
}
