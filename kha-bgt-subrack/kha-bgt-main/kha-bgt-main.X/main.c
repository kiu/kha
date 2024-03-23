#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---

#define KEY_AMOUNT 2

#define REGISTER_SIZE 1
#define REGISTER_PRESET_WIDTH 0

#define MAIN_ADDR_TIMER 0x00

// ---

static volatile uint8_t preset_next = KHA_PRESET_NONE;

static bool blink = false;
static volatile bool blink_exec = false;

static volatile uint32_t period_10ms = 0;
static volatile uint32_t tick = 0;

enum BTN_STATE {
    BTN_STATE_RD_OG, BTN_STATE_GN, BTN_STATE_RD_OG_BLINK, BTN_STATE_GN_BLINK, BTN_STATE_OFF
};
static uint8_t btn_state[KEY_AMOUNT] = {BTN_STATE_RD_OG, BTN_STATE_RD_OG};

static volatile bool manual_interaction = false;

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

void key_pressed(uint8_t key) {
    manual_interaction = true;
    if (key == 1) {
        if (kha_stack_preset() != KHA_PRESET_SHUTDOWN) {
            preset_next = KHA_PRESET_SHUTDOWN;
        } else {
            preset_next = KHA_PRESET_NONE;
        }
    }
    if (key == 0) {
        preset_next = KHA_PRESET_OFF;
    }
}

void key_tick() {
    tick++;
    if (period_10ms != 0 && tick > period_10ms) {
        period_10ms = 0;
        tick = 0;
        preset_next = KHA_PRESET_OFF;
    }
    if (tick % 100 == 0) {
        blink_exec = true;
    }

    key_state[1] = (key_state[1] << 1) | !IO_BTN_SHUTDOWN_GetValue();
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

void update_ui() {
    if (!kha_stack_ui_enabled()) {
        IO_LED_OFF_SetLow();
        IO_LED_SHUTDOWN_SetLow();
        return;
    }

    if (btn_state[1] == BTN_STATE_OFF) {
        IO_LED_SHUTDOWN_SetLow();
    } else if (btn_state[1] == BTN_STATE_GN) {
        IO_LED_SHUTDOWN_SetHigh();
    } else if (btn_state[1] == BTN_STATE_RD_OG) {
        IO_LED_SHUTDOWN_SetHigh();
    } else if (btn_state[1] == BTN_STATE_GN_BLINK) {
        if (blink) {
            IO_LED_SHUTDOWN_SetHigh();
        } else {
            IO_LED_SHUTDOWN_SetLow();
        }
    } else if (btn_state[1] == BTN_STATE_RD_OG_BLINK) {
        if (blink) {
            IO_LED_SHUTDOWN_SetHigh();
        } else {
            IO_LED_SHUTDOWN_SetLow();
        }
    }

    if (btn_state[0] == BTN_STATE_OFF) {
        IO_LED_OFF_SetLow();
    } else if (btn_state[0] == BTN_STATE_GN) {
        IO_LED_OFF_SetHigh();
    } else if (btn_state[0] == BTN_STATE_RD_OG) {
        IO_LED_OFF_SetHigh();
    } else if (btn_state[0] == BTN_STATE_GN_BLINK) {
        if (blink) {
            IO_LED_OFF_SetHigh();
        } else {
            IO_LED_OFF_SetLow();
        }
    } else if (btn_state[0] == BTN_STATE_RD_OG_BLINK) {
        if (blink) {
            IO_LED_OFF_SetHigh();
        } else {
            IO_LED_OFF_SetLow();
        }
    }
}

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    preset_next = preset;

    if (preset == KHA_PRESET_SHUTDOWN) {
        btn_state[1] = BTN_STATE_RD_OG_BLINK;
        tick = 0;
        period_10ms = kha_stack_register_get(MAIN_ADDR_TIMER) * 100UL;
    } else {
        btn_state[1] = BTN_STATE_RD_OG;
        period_10ms = 0;
    }

    if (preset == KHA_PRESET_OFF) {
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
            kha_stack_manual_interaction_occured(true, false);
        }

        if (preset_next != kha_stack_preset()) {
            kha_stack_preset_set(preset_next, true);
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}