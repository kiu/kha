#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"
#include "led-generic.h"
#include "main.h"

// ---

#include "math.h"
#define DEG_TO_RAD(X) (M_PI*(X)/180)

// ---

#define REGISTER_SIZE 4
#define REGISTER_PRESET_WIDTH 0

#define LED_DAT_SET PORTD_OUTSET = 0x10;
#define LED_DAT_CLR PORTD_OUTCLR = 0x10;

#define LED_MAX_SIZE 240L

// ---

static uint8_t strip_cfg_leds = 0;

enum STRIP_MODE {
    STRIP_SELECTION_OFF, STRIP_SELECTION_FULL
};

enum STRIP_COMM {
    STRIP_COMM_APA102, STRIP_COMM_WS2814
} strip_cfg_comm = STRIP_COMM_APA102;

static uint8_t strip_cfg_intensity_max = HSI_I_MAX;

static uint8_t mode = STRIP_SELECTION_OFF;
static volatile uint8_t mode_next = STRIP_SELECTION_OFF;

static volatile bool hsi_changed = false;
static volatile uint8_t hsi_h_net = HSI_H_INIT;
static uint8_t hsi_s_net = HSI_S_INIT;
static uint8_t hsi_i_net = HSI_I_INIT;

static uint8_t volatile anim_tick_count = 0;
static volatile bool anim_e = ANIM_E_INIT;
static volatile uint8_t anim_s = (0xFF - ANIM_S_INIT);
static volatile uint8_t anim_w = ANIM_W_INIT;

static uint8_t led_buffer[LED_MAX_SIZE * 0x04];
static uint8_t rgbw[4];

// ---

//https://blog.saikoled.com/post/44677718712/how-to-convert-from-hsi-to-rgb-white

void hsi2rgbw(uint8_t *hsi, uint8_t *rgbw) {
    float H = (float) hsi[0] * 1.411764706;
    float S = (float) hsi[1] * 0.003921569;
    float I = (float) hsi[2] * 0.003921569;

    //H = fmod(H, 360); // cycle H around to 0-360 degrees
    H = 3.14159 * H / (float) 180; // Convert to radians.
    //S = S > 0 ? (S < 1 ? S : 1) : 0; // clamp S and I to interval [0,1]
    //I = I > 0 ? (I < 1 ? I : 1) : 0;

    float H_org = H;

    if (H_org < 2.09439) {
    } else if (H_org < 4.188787) {
        H = H - 2.09439;
    } else {
        H = H - 4.188787;
    }

    float cos_h = cos(H);
    float cos_1047_h = cos(1.047196667 - H);

    uint8_t c1 = S * 255 * I / 3 * (1 + cos_h / cos_1047_h);
    uint8_t c2 = S * 255 * I / 3 * (1 + (1 - cos_h / cos_1047_h));
    uint8_t c3 = 255 * (1 - S) * I;

    if (H_org < 2.09439) {
        rgbw[0] = c1;
        rgbw[1] = c2;
        rgbw[2] = 0;
        rgbw[3] = c3;
    } else if (H_org < 4.188787) {
        rgbw[1] = c1;
        rgbw[2] = c2;
        rgbw[0] = 0;
        rgbw[3] = c3;
    } else {
        rgbw[2] = c1;
        rgbw[0] = c2;
        rgbw[1] = 0;
        rgbw[3] = c3;
    }
}
// https://blog.saikoled.com/post/43693602826/why-every-led-light-should-be-using-hsi

void hsi2rgb(uint8_t *hsi, uint8_t *rgbw) {
    float H = (float) hsi[0] * 1.411764706;
    float S = (float) hsi[1] * 0.003921569;
    float I = (float) hsi[2] * 0.003921569;

    //H = fmod(H, 360); // cycle H around to 0-360 degrees
    H = 3.14159 * H / (float) 180; // Convert to radians.
    //S = S > 0 ? (S < 1 ? S : 1) : 0; // clamp S and I to interval [0,1]
    //I = I > 0 ? (I < 1 ? I : 1) : 0;

    float H_org = H;

    if (H_org < 2.09439) {
    } else if (H_org < 4.188787) {
        H = H - 2.09439;
    } else {
        H = H - 4.188787;
    }

    float cos_h = cos(H);
    float cos_1047_h = cos(1.047196667 - H);

    uint8_t c1 = 255 * I / 3 * (1 + S * cos_h / cos_1047_h);
    uint8_t c2 = 255 * I / 3 * (1 + S * (1 - cos_h / cos_1047_h));
    uint8_t c3 = 255 * I / 3 * (1 - S);

    if (H_org < 2.09439) {
        rgbw[0] = c1;
        rgbw[1] = c2;
        rgbw[2] = c3;
    } else if (H_org < 4.188787) {
        rgbw[1] = c1;
        rgbw[2] = c2;
        rgbw[0] = c3;
    } else {
        rgbw[2] = c1;
        rgbw[0] = c2;
        rgbw[1] = c3;
    }
}

static inline void led_send_bit(bool b) {
    if (b) {
        LED_DAT_SET
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");

        LED_DAT_CLR
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    } else {
        LED_DAT_SET
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");

        LED_DAT_CLR
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }
}

void led_send_byte(uint8_t v) {
    led_send_bit(v & (1 << 7));
    led_send_bit(v & (1 << 6));
    led_send_bit(v & (1 << 5));
    led_send_bit(v & (1 << 4));
    led_send_bit(v & (1 << 3));
    led_send_bit(v & (1 << 2));
    led_send_bit(v & (1 << 1));
    led_send_bit(v & (1 << 0));
}

void led_send_reset() {
    LED_DAT_SetLow();
    DELAY_microseconds(300);
}

void led_send(uint16_t len) {
    if (strip_cfg_comm == STRIP_COMM_APA102) {
        for (uint16_t i = 0; i < len; i++) {
            while (!SPI0_IsTxReady()) {
            }
            SPI0_ByteWrite(led_buffer[i]);
        }
    }
    if (strip_cfg_comm == STRIP_COMM_WS2814) {
        led_send_reset();
        cli();
        for (uint16_t i = 0; i < len; i++) {
            led_send_byte(led_buffer[i]);
        }
        sei();
    }
}
// ---

void led_off() {
    if (LED_EN_GetValue()) {
        LED_EN_SetLow();
        DELAY_milliseconds(300);
    }
}

void led_on() {
    if (!LED_EN_GetValue()) {
        LED_EN_SetHigh();
        DELAY_milliseconds(300);
    }
}

// ---

void update_led() {
    if (strip_cfg_leds == 0) {
        return;
    }
    if (mode == STRIP_SELECTION_OFF) {
        return;
    }

    uint16_t bytes_per_update = strip_cfg_leds * 4;

    uint8_t hsi[3];
    hsi[0] = hsi_h_net;
    hsi[1] = hsi_s_net;
    hsi[2] = hsi_i_net;

    uint16_t i = 0;
    uint8_t apa102_post = (strip_cfg_leds / 2 / 8) + 1;

    if (!anim_e) {
        if (strip_cfg_comm == STRIP_COMM_APA102) {
            for (i = 0; i < 4; i++) {
                led_buffer[i] = 0x00;
            }
            led_send(4);

            hsi2rgb(hsi, rgbw);
            for (i = 0; i < bytes_per_update;) {
                led_buffer[i] = 0xFF;
                i++;
                led_buffer[i] = rgbw[2];
                i++;
                led_buffer[i] = rgbw[1];
                i++;
                led_buffer[i] = rgbw[0];
                i++;
            }
            led_send(bytes_per_update);

            for (i = 0; i < apa102_post; i++) {
                led_buffer[i] = 0xFF;
            }
            led_send(apa102_post);
        }
        if (strip_cfg_comm == STRIP_COMM_WS2814) {
            hsi2rgbw(hsi, rgbw);
            for (i = 0; i < bytes_per_update;) {
                led_buffer[i] = rgbw[3];
                i++;
                led_buffer[i] = rgbw[0];
                i++;
                led_buffer[i] = rgbw[1];
                i++;
                led_buffer[i] = rgbw[2];
                i++;
            }
            led_send(bytes_per_update);
        }
    } else {
        float step = (float) anim_w / (float) strip_cfg_leds;
        float hf = hsi[0];

        if (strip_cfg_comm == STRIP_COMM_APA102) {
            for (i = 0; i < 4; i++) {
                led_buffer[i] = 0x00;
            }
            led_send(4);

            i = 0;
            for (uint8_t c = 0; c < strip_cfg_leds; c++) {
                hsi[0] = hf;
                hsi2rgb(hsi, rgbw);
                hf += step;

                led_buffer[i] = 0xFF;
                i++;
                led_buffer[i] = rgbw[2];
                i++;
                led_buffer[i] = rgbw[1];
                i++;
                led_buffer[i] = rgbw[0];
                i++;
            }
            led_send(bytes_per_update);

            for (i = 0; i < apa102_post; i++) {
                led_buffer[i] = 0xFF;
            }
            led_send(apa102_post);
        }
        if (strip_cfg_comm == STRIP_COMM_WS2814) {
            i = 0;
            for (uint8_t c = 0; c < strip_cfg_leds; c++) {
                hsi[0] = hf;
                hsi2rgbw(hsi, rgbw);
                hf += step;

                led_buffer[i] = rgbw[3];
                i++;
                led_buffer[i] = rgbw[0];
                i++;
                led_buffer[i] = rgbw[1];
                i++;
                led_buffer[i] = rgbw[2];
                i++;
            }
            led_send(bytes_per_update);
        }
    }
}

void anim_tick() {
    if (mode == STRIP_SELECTION_OFF) {
        return;
    }
    if (strip_cfg_leds == 0) {
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

void hsi_set(uint8_t hsi[3]) {
    hsi_h_net = hsi[0];
    hsi_s_net = hsi[1];
    if (hsi[2] > strip_cfg_intensity_max) {
        hsi_i_net = strip_cfg_intensity_max;
    } else {
        hsi_i_net = hsi[2];
    }
    hsi_changed = true;
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

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {

        if (addr == LED_ADDR_SELECTION) {
            if (value > STRIP_SELECTION_FULL) {
                value = STRIP_SELECTION_FULL;
            }
            mode_next = value;
        }

        if (addr == STRIP_ADDR_CFG_LEDS) {
            if (value > LED_MAX_SIZE) {
                value = LED_MAX_SIZE;
            }
            strip_cfg_leds = value;
            hsi_changed = true;
        }
        if (addr == STRIP_ADDR_CFG_COMM) {
            if (value > STRIP_COMM_WS2814) {
                value = STRIP_COMM_WS2814;
            }
            strip_cfg_comm = value;
            hsi_changed = true;
            if (value == STRIP_COMM_APA102) {
                SPI0_Open(0x00);
            }
            if (value == STRIP_COMM_WS2814) {
                SPI0_Close();
            }
        }
        if (addr == STRIP_ADDR_CFG_INTENSITY_MAX) {
            strip_cfg_intensity_max = value;
            uint8_t hsi[3];
            hsi[0] = hsi_h_net;
            hsi[1] = hsi_s_net;
            hsi[2] = hsi_i_net;
            hsi_set(hsi);
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
    if (mode_next != STRIP_SELECTION_OFF) {
        led_on();
        hsi_changed = true;
    } else {
        led_off();
    }
}

// ---

int main(void) {
    SYSTEM_Initialize();

    sei();

    led_off();

    kha_stack_register_cbr_change(register_change);
    kha_stack_app_led_animation_cbr(anim_set);
    kha_stack_app_led_hsi_cbr(hsi_set);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

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

