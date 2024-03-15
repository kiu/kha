#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---

#define KEY_AMOUNT 1

#define REGISTER_SIZE 0
#define REGISTER_PRESET_WIDTH 0

// ---

static volatile uint8_t preset_next = KHA_PRESET_NONE;

static bool blink = false;
static volatile bool blink_exec = false;

static volatile uint32_t tick = 0;

enum BTN_STATE {
    BTN_STATE_RD_OG, BTN_STATE_RD_OG_BLINK, BTN_STATE_OFF
};
static uint8_t btn_state[KEY_AMOUNT] = {BTN_STATE_OFF};

static volatile bool manual_interaction = false;

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

void key_pressed(uint8_t key) {
    manual_interaction = true;
    if (key == 0) {
        if (kha_stack_preset() == KHA_PRESET_OFF) {
            preset_next = KHA_PRESET_SHUTDOWN;
        } else {
            preset_next = KHA_PRESET_OFF;
        }
    }
}

void key_tick() {
    tick++;
    if (tick % 100 == 0) {
        blink_exec = true;
    }

    key_state[0] = (key_state[0] << 1) | !IO_BTN_GetValue();

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
    if (btn_state[0] == BTN_STATE_OFF) {
        IO_LED_SetLow();
    } else if (btn_state[0] == BTN_STATE_RD_OG) {
        IO_LED_SetHigh();
    } else if (btn_state[0] == BTN_STATE_RD_OG_BLINK) {
        if (blink) {
            IO_LED_SetHigh();
        } else {
            IO_LED_SetLow();
        }
    }
}

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    preset_next = preset;

    if (preset == KHA_PRESET_SHUTDOWN) {
        btn_state[0] = BTN_STATE_RD_OG_BLINK;
    } else if (preset == KHA_PRESET_OFF) {
        btn_state[0] = BTN_STATE_RD_OG;
    } else {
        btn_state[0] = BTN_STATE_OFF;
    }

    update_ui();
}

int main(void) {
    SYSTEM_Initialize();

    sei();

    kha_stack_ui_cbr_change(update_ui);
    kha_stack_preset_cbr_change(preset_change);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    update_ui();

    TCA0_Compare0CallbackRegister(key_tick);

    while (1) {
        if (blink_exec) {
            blink_exec = false;
            blink = !blink;
            update_ui();
        }

        if (manual_interaction) {
            manual_interaction = false;
            manual_interaction_occured(true, false);
        }

        if (preset_next != kha_stack_preset()) {
            kha_stack_preset_set(preset_next, true);
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}