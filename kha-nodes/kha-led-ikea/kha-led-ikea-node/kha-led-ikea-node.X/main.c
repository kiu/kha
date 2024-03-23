#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "../../../../kha-common.X/kha-constants.h"
#include "../../../../kha-common.X/kha-stack.h"
#include "../../kha-led-const.h"
#include "../../../kha-led-strip/kha-led-strip.X/led-generic.h"
#include "kha-version.h"
#include "main.h"

// ---

#define REGISTER_SIZE 6
#define REGISTER_PRESET_WIDTH 0

#define IKEA_NODE_HARDWARE_OXBERG 2
#define IKEA_NODE_HARDWARE_KALLAX 1
#define IKEA_NODE_HARDWARE_NONE 0

#define LAYOUT_ORIENTATION_NONE 0x0
#define LAYOUT_ORIENTATION_VERTICAL 0x01
#define LAYOUT_ORIENTATION_HORIZONTAL 0x02

// ---

static uint8_t layout_orientation = LAYOUT_ORIENTATION_NONE;
static uint8_t layout_amount = 0;
static uint8_t layout_low_amount = 0;
static uint8_t layout_location = 0;

static uint8_t mode = IKEA_SELECTION_INIT;
static volatile uint8_t mode_next = IKEA_SELECTION_OFF;

static volatile bool hsi_changed = false;
static volatile uint8_t hsi_h_net = HSI_H_INIT;
static uint8_t hsi_s_net = HSI_S_INIT;
static uint8_t hsi_i_net = HSI_I_INIT;

static uint8_t volatile anim_tick_count = 0;
static volatile bool anim_e = ANIM_E_INIT;
static volatile uint8_t anim_s = (0xFF - ANIM_S_INIT);
static volatile uint8_t anim_w = ANIM_W_INIT;

// ---

void send_rx4_raw(uint8_t data) {
    while (!USART1_IsTxReady()) {
    }
    USART1_Write(data);
}

void send_rx4(uint8_t addr, uint8_t cmd, uint8_t optlen, uint8_t* opt) {
    // Raw:      0x42 0x23 <----------- payload ------------>
    // Encoded:  0x42 0x23 <len> <addr> <cmd> <options> <crc>
    // Decoded:  0x42      <len> <addr> <cmd> <options> <crc>
    // Buffer:                   <addr> <cmd> <options> <crc>

    uint8_t txlen = optlen + 4; // len + addr + cmd + 4 opt + crc
    uint8_t tx[txlen];

    tx[0] = txlen;
    tx[1] = addr;
    tx[2] = cmd;
    memcpy(tx + 3, opt, optlen);
    tx[3 + optlen] = kha_stack_crc8(tx, txlen - 2);

    while (!USART1_IsTxDone()) {
    }

    send_rx4_raw(KHA_LED_MSG_START);
    send_rx4_raw(KHA_LED_MSG_START_CONFIRM);
    for (uint8_t i = 0; i < txlen; i++) {
        send_rx4_raw(tx[i]);
        if (tx[i] == KHA_LED_MSG_START) {
            send_rx4_raw(KHA_LED_MSG_START_ESCAPE);
        }
    }
}

void send_rx4_hsi(uint8_t addr, uint8_t h, uint8_t s, uint8_t i) {
    uint8_t buf3[3];
    buf3[0] = h;
    buf3[1] = s;
    buf3[2] = i;
    send_rx4(addr, KHA_LED_CMD_SET_HSI, 3, buf3);
}

void send_rx4_ident() {
    send_rx4(KHA_LED_ADDR_BROADCAST, KHA_LED_CMD_IDENT, 0, NULL);
}

// ---

void update_led() {
    if (mode == IKEA_SELECTION_OFF) {
        return;
    }

    if (layout_orientation == LAYOUT_ORIENTATION_NONE) {
        return;
    }

    if (layout_amount == 0) {
        return;
    }

    if (!anim_e) {
        if (layout_orientation != LAYOUT_ORIENTATION_VERTICAL) {
            send_rx4_hsi(KHA_LED_ADDR_BROADCAST, hsi_h_net, hsi_s_net, hsi_i_net);
            return;
        }

        if (mode == IKEA_SELECTION_LOW) {
            for (uint8_t i = 0; i < layout_amount; i++) {
                if (i < layout_low_amount) {
                    send_rx4_hsi(i + 1, hsi_h_net, hsi_s_net, hsi_i_net);
                } else {
                    send_rx4_hsi(i + 1, hsi_h_net, hsi_s_net, 0x00);
                }
            }
        }

        if (mode == IKEA_SELECTION_GRADIENT) {
            float fraction = hsi_i_net / (float) (layout_amount + 1);
            for (uint8_t i = 0; i < layout_amount; i++) {
                send_rx4_hsi(i + 1, hsi_h_net, hsi_s_net, fraction * (layout_amount - i));
            }
        }

        if (mode == IKEA_SELECTION_FULL) {
            send_rx4_hsi(KHA_LED_ADDR_BROADCAST, hsi_h_net, hsi_s_net, hsi_i_net);
        }
    }

    if (anim_e) {        
        float step = anim_w / 6;
        
        if (mode == IKEA_SELECTION_LOW) {
            if (layout_orientation == LAYOUT_ORIENTATION_HORIZONTAL && layout_amount > 1) {
                for (uint8_t i = 0; i < layout_amount; i++) {
                    send_rx4_hsi(i + 1, hsi_h_net + ((layout_location + i) * step), hsi_s_net, hsi_i_net);
                }
            } else {
                for (uint8_t i = 0; i < layout_amount; i++) {
                    if (i < layout_low_amount) {
                        send_rx4_hsi(i + 1, hsi_h_net + (layout_location * step), hsi_s_net, hsi_i_net);
                    } else {
                        send_rx4_hsi(i + 1, hsi_h_net + (layout_location * step), hsi_s_net, 0x00);
                    }
                }
            }
        }

        if (mode == IKEA_SELECTION_GRADIENT) {
            float fraction = hsi_i_net / (float) (layout_amount + 1);
            if (layout_orientation == LAYOUT_ORIENTATION_HORIZONTAL && layout_amount > 1) {
                for (uint8_t i = 0; i < layout_amount; i++) {
                    send_rx4_hsi(i + 1, hsi_h_net + ((layout_location + i) * step), hsi_s_net, fraction * (layout_amount - i));
                }
            } else {
                for (uint8_t i = 0; i < layout_amount; i++) {
                    send_rx4_hsi(i + 1, hsi_h_net + (layout_location * step), hsi_s_net, fraction * (layout_amount - i));
                }
            }
        }

        if (mode == IKEA_SELECTION_FULL) {
            if (layout_orientation == LAYOUT_ORIENTATION_HORIZONTAL && layout_amount > 1) {
                for (uint8_t i = 0; i < layout_amount; i++) {
                    send_rx4_hsi(i + 1, hsi_h_net + ((layout_location + i) * step), hsi_s_net, hsi_i_net);
                }
            } else {
                send_rx4_hsi(KHA_LED_ADDR_BROADCAST, hsi_h_net + (layout_location * step), hsi_s_net, hsi_i_net);
            }
        }
    }
}

void hsi_set(uint8_t hsi[3]) {
    hsi_h_net = hsi[0];
    hsi_s_net = hsi[1];
    hsi_i_net = hsi[2];
    hsi_changed = true;
}

void anim_tick() {
    if (mode == IKEA_SELECTION_OFF) {
        return;
    }
    if (hsi_s_net == 0x00) {
        return;
    }
    if (hsi_i_net == 0x00) {
        return;
    }

    anim_tick_count++;
    if (anim_tick_count >= anim_s) {
        anim_tick_count = 0;
        hsi_h_net++;
        hsi_changed = true;
    }
}

void anim_set(uint8_t swe[3]) {
    uint8_t tmp;

    tmp = swe[0];
    if (tmp < ANIM_S_MIN) {
        tmp = ANIM_S_MIN;
    }
    if (tmp > ANIM_S_MAX) {
        tmp = ANIM_S_MAX;
    }
    anim_s = 0xFF - tmp;

    tmp = swe[1];
    if (tmp < ANIM_W_MIN) {
        tmp = ANIM_W_MIN;
    }
    if (tmp > ANIM_W_MAX) {
        tmp = ANIM_W_MAX;
    }
    anim_w = tmp;

    tmp = swe[2];
    if (tmp > 1) {
        tmp = 0;
    }
    anim_e = tmp;
    if (anim_e) {
        TCA0_Compare0CallbackRegister(anim_tick);
    } else {
        TCA0_Compare0CallbackRegister(NULL);
    }

    hsi_changed = true;
}

// ---

void led_on() {
    if (!IO_PD6_GetValue()) {
        IO_PD6_SetHigh();
        DELAY_milliseconds(300);
    }
}

void led_off() {
    if (IO_PD6_GetValue()) {
        send_rx4_hsi(KHA_LED_ADDR_BROADCAST, 0x00, 0x00, 0x00);
        DELAY_milliseconds(300);
        IO_PD6_SetLow();
    }
}

// ---

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (addr == LED_ADDR_SELECTION) {
            if (value > IKEA_SELECTION_FULL) {
                value = IKEA_SELECTION_OFF;
            }
            mode_next = value;
        }
        
        if (addr == IKEA_ADDR_IDENT) {
            if (value > 0) {
                value = 0;
                led_on();
                send_rx4_ident();
            }
        }

        if (addr == IKEA_ADDR_LAYOUT_AMOUNT) {
            layout_amount = value;
        }

        if (addr == IKEA_ADDR_LAYOUT_ORIENTATION) {
            if (value > LAYOUT_ORIENTATION_HORIZONTAL) {
                value = LAYOUT_ORIENTATION_NONE;
            }
            layout_orientation = value;
        }

        if (addr == IKEA_ADDR_LAYOUT_LOW_AMOUNT) {
            if (value > layout_amount) {
                value = layout_amount;
            }
            layout_low_amount = value;
        }

        if (addr == IKEA_ADDR_LAYOUT_LOCATION) {
            layout_location = value;
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

void mode_changed() {
    mode = mode_next;
    if (mode_next != IKEA_SELECTION_OFF) {
        led_on();
    } else {
        led_off();
    }
    update_led();
}

int main(void) {
    SYSTEM_Initialize();

    sei();

    send_rx4_raw(0x00); // Needed to initialize USART1_IsTxDone()

    led_off();

    kha_stack_register_cbr_change(register_change);
    kha_stack_app_led_animation_cbr(anim_set);
    kha_stack_app_led_hsi_cbr(hsi_set);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    update_led();

    while (1) {
        if (hsi_changed) {
            hsi_changed = false;
            update_led();
        }

        if (mode_next != mode) {
            mode_changed();
        }

        kha_stack_process_rx_tx();
        asm("wdr");
    }
}
