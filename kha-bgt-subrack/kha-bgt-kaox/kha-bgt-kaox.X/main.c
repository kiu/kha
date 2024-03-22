#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "../../../kha-nodes/kha-led-strip/kha-led-strip.X/led-generic.h"
#include "../../../kha-nodes/kha-led-ikea/kha-led-ikea-node/kha-led-ikea-node.X/main.h"
#include "kha-version.h"

// ---

#define KEY_AMOUNT 4

#define KAOX_ADDR_DEST 0x00

#define REGISTER_SIZE 1
#define REGISTER_PRESET_WIDTH 1

// ---

enum KAOX_MODE {
    KAOX_MODE_OFF, KAOX_MODE_LOW, KAOX_MODE_GRADIENT, KAOX_MODE_FULL, KAOX_MODE_INIT
};

static uint8_t mode = KAOX_MODE_INIT;
static volatile uint8_t mode_next = KAOX_MODE_OFF;

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
    if (key == 0 && mode == KAOX_MODE_OFF) {
        mode_next = KAOX_MODE_FULL;
    } else {
        mode_next = key;
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

void mode_do(uint8_t value, bool notify) {
    mode = value;
    mode_next = value;

    btn_state[3] = BTN_STATE_OFF;
    btn_state[2] = BTN_STATE_OFF;
    btn_state[1] = BTN_STATE_OFF;
    btn_state[0] = BTN_STATE_OFF;

    if (mode == KAOX_MODE_FULL) {
        if (notify) {
            uint8_t buf2[6] = {LED_ADDR_SELECTION, IKEA_SELECTION_FULL};
            kha_stack_tx_create(kha_stack_register_get(KAOX_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
        btn_state[3] = BTN_STATE_RD_OG;
        btn_state[0] = BTN_STATE_GN;
    }

    if (mode == KAOX_MODE_GRADIENT) {
        if (notify) {
            uint8_t buf2[6] = {LED_ADDR_SELECTION, IKEA_SELECTION_GRADIENT};
            kha_stack_tx_create(kha_stack_register_get(KAOX_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
        btn_state[2] = BTN_STATE_RD_OG;
        btn_state[0] = BTN_STATE_GN;
    }

    if (mode == KAOX_MODE_LOW) {
        if (notify) {
            uint8_t buf2[6] = {LED_ADDR_SELECTION, IKEA_SELECTION_LOW};
            kha_stack_tx_create(kha_stack_register_get(KAOX_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
        btn_state[1] = BTN_STATE_RD_OG;
        btn_state[0] = BTN_STATE_GN;
    }

    if (mode == KAOX_MODE_OFF) {
        if (notify) {
            uint8_t buf2[2] = {LED_ADDR_SELECTION, IKEA_SELECTION_OFF};
            kha_stack_tx_create(kha_stack_register_get(KAOX_ADDR_DEST), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
        }
        btn_state[0] = BTN_STATE_RD_OG;
    }

    update_ui();
}

void preset_change(uint8_t preset, bool enabled, uint8_t addr) {
    if (enabled) {
        mode_next = kha_stack_register_get(addr + 0);
    }
}

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr == KAOX_ADDR_DEST) {
        if (value == 0xFF) {
            value = 0x00;
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
            if (value > KAOX_MODE_FULL) {
                value = KAOX_MODE_OFF;
            }
        }
    }

    return value;
}

void rx_all_register_slice(uint8_t addr, uint8_t value) {
    if (addr == 0) {
        if (value == IKEA_SELECTION_FULL) {
            mode_do(KAOX_MODE_FULL, false);
        }
        if (value == IKEA_SELECTION_GRADIENT) {
            mode_do(KAOX_MODE_GRADIENT, false);
        }
        if (value == IKEA_SELECTION_LOW) {
            mode_do(KAOX_MODE_LOW, false);
        }
        if (value == IKEA_SELECTION_OFF) {
            mode_do(KAOX_MODE_OFF, false);
        }
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

        if (to == kha_stack_register_get(KAOX_ADDR_DEST)) {
            for (uint8_t i = 0; i < reg_len; i++) {
                rx_all_register_slice(reg_addr + i, opt[i + 1]);
            }
        }
    }

    return false;
}

// ---

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

        if (mode_next != mode) {
            mode_do(mode_next, true);
        }

        kha_stack_process_rx_tx();

        asm("wdr");
    }
}