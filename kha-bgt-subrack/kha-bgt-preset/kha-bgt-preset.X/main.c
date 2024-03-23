#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---

#define KEY_AMOUNT 4
#define PRESET_AMOUNT 4

#define REGISTER_SIZE PRESET_AMOUNT
#define REGISTER_PRESET_WIDTH 0

// ---

static volatile uint8_t preset_next = KHA_PRESET_NONE;
static volatile uint8_t preset_config[PRESET_AMOUNT];

enum BTN_STATE {
    BTN_STATE_RD_OG, BTN_STATE_GN, BTN_STATE_OFF
};
static uint8_t btn_state[4] = {BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF};

static volatile bool manual_interaction = false;

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

void key_pressed(uint8_t key) {
    if (preset_config[key] != KHA_PRESET_NONE) {
        preset_next = preset_config[key];
    }
    manual_interaction = true;
}

void key_tick() {
    key_state[3] = (key_state[3] << 1) | !IO_BTN03_GetValue();
    key_state[2] = (key_state[2] << 1) | !IO_BTN02_GetValue();
    key_state[1] = (key_state[1] << 1) | !IO_BTN01_GetValue();
    key_state[0] = (key_state[0] << 1) | !IO_BTN00_GetValue();

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

    if (btn_state[3] == BTN_STATE_OFF) {
        IO_LED03A_SetLow();
        IO_LED03B_SetLow();
    } else if (btn_state[3] == BTN_STATE_GN) {
        IO_LED03A_SetLow();
        IO_LED03B_SetHigh();
    } else if (btn_state[3] == BTN_STATE_RD_OG) {
        IO_LED03A_SetHigh();
        IO_LED03B_SetLow();
    }

    if (btn_state[2] == BTN_STATE_OFF) {
        IO_LED02A_SetLow();
        IO_LED02B_SetLow();
    } else if (btn_state[2] == BTN_STATE_GN) {
        IO_LED02A_SetLow();
        IO_LED02B_SetHigh();
    } else if (btn_state[2] == BTN_STATE_RD_OG) {
        IO_LED02A_SetHigh();
        IO_LED02B_SetLow();
    }

    if (btn_state[1] == BTN_STATE_OFF) {
        IO_LED01A_SetLow();
        IO_LED01B_SetLow();
    } else if (btn_state[1] == BTN_STATE_GN) {
        IO_LED01A_SetLow();
        IO_LED01B_SetHigh();
    } else if (btn_state[1] == BTN_STATE_RD_OG) {
        IO_LED01A_SetHigh();
        IO_LED01B_SetLow();
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

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    preset_next = preset;

    btn_state[3] = BTN_STATE_OFF;
    btn_state[2] = BTN_STATE_OFF;
    btn_state[1] = BTN_STATE_OFF;
    btn_state[0] = BTN_STATE_OFF;

    if (preset_config[3] == preset && preset_config[3] != KHA_PRESET_NONE) {
        btn_state[3] = BTN_STATE_RD_OG;
    }

    if (preset_config[2] == preset && preset_config[2] != KHA_PRESET_NONE) {
        btn_state[2] = BTN_STATE_RD_OG;
    }

    if (preset_config[1] == preset && preset_config[1] != KHA_PRESET_NONE) {
        btn_state[1] = BTN_STATE_RD_OG;
    }

    if (preset_config[0] == preset && preset_config[0] != KHA_PRESET_NONE) {
        btn_state[0] = BTN_STATE_RD_OG;
    }

    update_ui();
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (value > KHA_PRESET_MAX) {
            value = KHA_PRESET_NONE;
        }
        if (preset_config[addr] != value) {
            preset_config[addr] = value;
            preset_change(kha_stack_preset(), false, 0);
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

int main(void) {
    SYSTEM_Initialize();

    sei();

    kha_stack_register_cbr_change(register_change);
    kha_stack_ui_cbr_change(update_ui);
    kha_stack_preset_cbr_change(preset_change);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    update_ui();

    TCA0_Compare0CallbackRegister(key_tick);

    while (1) {
        if (manual_interaction) {
            manual_interaction = false;
            kha_stack_manual_interaction_occured(true, false);
        }

        if (preset_next != kha_stack_preset()) {
            kha_stack_preset_set(preset_next, true);
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}