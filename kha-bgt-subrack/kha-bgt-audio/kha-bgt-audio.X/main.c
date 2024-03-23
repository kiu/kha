#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"
#include "main.h"

// ---

#define KEY_AMOUNT 4

#define REGISTER_SIZE 3
#define REGISTER_PRESET_WIDTH 1

#define AUDIO_ADDR_MODE 0x00
#define AUDIO_ADDR_CON 0x01
#define AUDIO_ADDR_MODE_POWERUP 0x02

// ---

static volatile opmode mode = NONE;
static volatile opmode mode_next = NONE;
static volatile bool bt_con = false;

enum BTN_STATE {
    BTN_STATE_RD_OG, BTN_STATE_GN, BTN_STATE_OFF
};
static uint8_t btn_state[4] = {BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF, BTN_STATE_OFF};

static volatile bool manual_interaction = false;

static const uint8_t key_mask = 0b00001111;
static uint8_t key_state[KEY_AMOUNT];
static bool key_down[KEY_AMOUNT];

// ---

void key_pressed(uint8_t i) {
    mode_next = i;

    if (mode == AUXD) {
        bt_con = true;
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

opmode verifyAndCorrect(uint8_t check) {
    if (check > AUXD) {
        check = AUXA;
    }
    return check;
}

// ---

void update_ui() {
    if (!kha_stack_ui_enabled()) {
        IO_LED03_SetLow();
        IO_LED02_SetLow();
        IO_LED01_SetLow();
        IO_LED00_SetLow();
        return;
    }

    if (btn_state[3] == BTN_STATE_OFF) {
        IO_LED03_SetLow();
    } else if (btn_state[3] == BTN_STATE_GN) {
        IO_LED03_SetHigh();
    } else if (btn_state[3] == BTN_STATE_RD_OG) {
        IO_LED03_SetHigh();
    }

    if (btn_state[2] == BTN_STATE_OFF) {
        IO_LED02_SetLow();
    } else if (btn_state[2] == BTN_STATE_GN) {
        IO_LED02_SetHigh();
    } else if (btn_state[2] == BTN_STATE_RD_OG) {
        IO_LED02_SetHigh();
    }

    if (btn_state[1] == BTN_STATE_OFF) {
        IO_LED01_SetLow();
    } else if (btn_state[1] == BTN_STATE_GN) {
        IO_LED01_SetHigh();
    } else if (btn_state[1] == BTN_STATE_RD_OG) {
        IO_LED01_SetHigh();
    }

    if (btn_state[0] == BTN_STATE_OFF) {
        IO_LED00_SetLow();
    } else if (btn_state[0] == BTN_STATE_GN) {
        IO_LED00_SetHigh();
    } else if (btn_state[0] == BTN_STATE_RD_OG) {
        IO_LED00_SetHigh();
    }
}

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    if (enabled) {
        mode_next = kha_stack_register_get(addr + 0);
    }
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (addr == AUDIO_ADDR_MODE) {
            value = verifyAndCorrect(value);
            mode_next = value;
        }

        if (addr == AUDIO_ADDR_CON) {
            if (value > 0) {
                if (mode == AUXD) {
                    bt_con = true;
                }
            }
            value = 0;
        }

        if (addr == AUDIO_ADDR_MODE_POWERUP) {
            value = verifyAndCorrect(value);
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
            value = verifyAndCorrect(value);
        }
    }
    return value;
}

// ---

void mode_switch(opmode om) {
    if (mode == om) {
        return;
    }
    mode = om;
    bt_con = false;

    kha_stack_register_set(AUDIO_ADDR_MODE, om, false);

    uint8_t buf2[2] = {AUDIO_ADDR_MODE, om};
    kha_stack_tx_create(kha_stack_device_address_get(), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);

    btn_state[3] = BTN_STATE_OFF;
    btn_state[2] = BTN_STATE_OFF;
    btn_state[1] = BTN_STATE_OFF;
    btn_state[0] = BTN_STATE_OFF;

    IO_LED00_SetLow();
    IO_LED01_SetLow();
    IO_LED02_SetLow();
    IO_LED03_SetLow();

    USART1_Disable();
    IO_BT_VCC_SetHigh();
    IO_BT_CON_SetLow();

    if (om == AUXA) {
        btn_state[0] = BTN_STATE_RD_OG;
        IO_SR01_SetLow();
        IO_SR02_SetLow();
        IO_SR03_SetLow();
    }
    if (om == AUXB) {
        btn_state[1] = BTN_STATE_RD_OG;
        IO_SR01_SetHigh();
        IO_SR02_SetLow();
        IO_SR03_SetLow();

        uint8_t buf2[2] = {0x02, 0x01};
        kha_stack_tx_create(0xC5, KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
    }

    if (om == AUXC) {
        btn_state[2] = BTN_STATE_RD_OG;
        IO_SR01_SetLow();
        IO_SR02_SetLow();
        IO_SR03_SetHigh();
    }
    if (om == AUXD) {
        btn_state[3] = BTN_STATE_RD_OG;
        IO_SR01_SetLow();
        IO_SR02_SetHigh();
        IO_SR03_SetHigh();
        IO_BT_VCC_SetLow();
        IO_BT_CON_SetHigh();
        USART1_Enable();
    }

    update_ui();
}

// ---

int main(void) {
    SYSTEM_Initialize();

    IO_BT_VCC_SetLow();

    sei();

    kha_stack_register_cbr_change(register_change);
    kha_stack_ui_cbr_change(update_ui);
    kha_stack_preset_cbr_change(preset_change);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);
    mode_next = verifyAndCorrect(kha_stack_register_get(AUDIO_ADDR_MODE_POWERUP));

    update_ui();

    TCA0_Compare0CallbackRegister(key_tick);

    while (1) {
        if (manual_interaction) {
            manual_interaction = false;
            kha_stack_manual_interaction_occured(true, true);
        }

        if (mode != mode_next) {
            mode_switch(mode_next);
        }

        if (bt_con) {
            bt_con = false;

            btn_state[3] = BTN_STATE_OFF;
            update_ui();
            IO_LED03_SetLow();

            IO_BT_CON_SetLow();
            DELAY_milliseconds(600);
            IO_BT_CON_SetHigh();

            IO_LED03_SetHigh();
            btn_state[3] = BTN_STATE_RD_OG;
            update_ui();
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}
