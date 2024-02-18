#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---

#define KEY_AMOUNT 2

#define REGISTER_SIZE 0
#define REGISTER_PRESET_WIDTH 1

// ---

static volatile bool sendOn = false;
static volatile bool sendOff = false;

static volatile bool manual_interaction = false;

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

void key_pressed(uint8_t key) {
    manual_interaction = true;
    if (key == 1) {
        sendOn = true;
    }
    if (key == 0) {
        sendOff = true;
    }
}

void key_tick() {
    key_state[1] = (key_state[1] << 1) | !IO_BTN_ON_GetValue();
    key_state[0] = (key_state[0] << 1) | !IO_BTN_OFF_GetValue();

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

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    if (enabled) {
        bool value = kha_stack_register_get(addr + 0);
        if (value == 0) {
            sendOff = true;
        }
        if (value == 1) {
            sendOn = true;
        }
    }
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr >= REGISTER_SIZE && REGISTER_PRESET_WIDTH > 0) {
        uint8_t index = addr - REGISTER_SIZE - ((addr - REGISTER_SIZE) / (REGISTER_PRESET_WIDTH + 1) * (REGISTER_PRESET_WIDTH + 1));
        if (index == 0) {
            if (value > 1) {
                value = 0;
            }
        }
        if (index == 1) {
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
    kha_stack_preset_cbr_change(preset_change);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    TCA0_Compare0CallbackRegister(key_tick);

    while (1) {
        if (manual_interaction) {
            manual_interaction = false;
            manual_interaction_occured(false, true);
        }

        if (sendOn) {
            sendOn = false;
            kha_stack_ui_enable();
        }
        if (sendOff) {
            sendOff = false;
            kha_stack_ui_disable();
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}