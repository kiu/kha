#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/nvm/nvm.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/uart/usart0.h"
#include "../../kha-led-const.h"

// ----

#include "math.h"
#define DEG_TO_RAD(X) (M_PI*(X)/180)

// ----

static uint8_t devaddr = 0;

static uint8_t msgState = 0; // IDLE, START, LENGTH, PAYLOAD
static bool msgEscapeDetected = false;
static uint8_t msgPayload[KHA_LED_MSG_SIZE_MAX];
static uint8_t msgPayloadIdx = 0;

static uint8_t hsi_h_net = 0x00;
static uint8_t hsi_s_net = 0x00;
static uint8_t hsi_i_net = 0x00;

static uint8_t led_r = 0;
static uint8_t led_g = 0;
static uint8_t led_b = 0;
static uint8_t led_w = 0;

uint8_t calculate_crc8(uint8_t* data, size_t len) {
    uint8_t crc = 0xff; // init value
    size_t i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t) ((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

void hsi2rgbw() {
    float H = (float) hsi_h_net * 1.411764706;
    float S = (float) hsi_s_net * 0.003921569;
    float I = (float) hsi_i_net * 0.003921569;

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

    uint8_t a = S * 255 * I / 3 * (1 + cos_h / cos_1047_h);
    uint8_t b = S * 255 * I / 3 * (1 + (1 - cos_h / cos_1047_h));
    uint8_t c = 255 * (1 - S) * I;

    if (H_org < 2.09439) {
        led_r = a;
        led_g = b;
        led_b = 0;
        led_w = c;
    } else if (H_org < 4.188787) {
        led_g = a;
        led_b = b;
        led_r = 0;
        led_w = c;
    } else {
        led_b = a;
        led_r = b;
        led_g = 0;
        led_w = c;
    }
}

static inline void T0H() {
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
}

static inline void T1() {
    asm("nop");
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

void led_send_reset() {
    PORTA_OUTCLR = 0x8;
    DELAY_microseconds(80);
}

void led_send_byte(uint8_t v) {
    for (uint8_t i = 8; i > 0; i--) {
        if (v & (1 << i)) {
            PORTA_OUTSET = 0x8;
            T1();
            PORTA_OUTCLR = 0x8;
            T1();
        } else {
            PORTA_OUTSET = 0x8;
            T0H();
            PORTA_OUTCLR = 0x8;
            T1(); // 2 more?
        }
    }
}

void led_set(bool hsi_use, bool enableInterrupts) {
    if (hsi_use) {
        hsi2rgbw();
    }
    led_send_reset();
    cli();
    led_send_byte(led_g);
    led_send_byte(led_r);
    led_send_byte(led_b);
    led_send_byte(led_w);
    if (enableInterrupts) {
        sei();
    }
}

void d1000() {
    DELAY_milliseconds(1000);
}

void led_ident(bool enableInterrupts) {
    led_r = 0x00;
    led_g = 0x00;
    led_b = 0x00;
    led_w = 0xFF;

    led_set(false, enableInterrupts);
    d1000();

    led_w = 0x00;
    led_set(false, enableInterrupts);
    d1000();

    hsi_s_net = 0xFF;
    hsi_i_net = 0xFF;

    for (uint8_t bit = 8; bit > 0; bit--) {
        if (devaddr & (1 << (bit - 1))) {
            led_r = 0x00;
            led_g = 0xFF;
            led_set(false, enableInterrupts);
        } else {
            led_r = 0xFF;
            led_g = 0x00;
            led_set(false, enableInterrupts);
        }
        d1000();

        led_r = 0x00;
        led_g = 0x00;
        led_set(false, enableInterrupts);
        d1000();
    }

    led_b = 0xFF;
    led_set(false, enableInterrupts);
    d1000();

    led_b = 0x00;
    led_set(false, enableInterrupts);
    d1000();
}

void process_rx() {
    uint8_t len = msgPayload[0];
    uint8_t addr = msgPayload[1];
    uint8_t cmd = msgPayload[2];
    uint8_t optlen = len - KHA_LED_MSG_SIZE_MIN;
    uint8_t opt[optlen];
    for (uint8_t i = 0; i < optlen; i++) {
        opt[i] = msgPayload[3 + i];
    }
    uint8_t crc = msgPayload[len - 1];

    if (calculate_crc8(msgPayload, len - 2) != crc) {
        return;
    }

    if (addr != devaddr && addr != KHA_LED_ADDR_BROADCAST) {
        return;
    }

    if (cmd == KHA_LED_CMD_SET_HSI && optlen == 3) {
        hsi_h_net = opt[0];
        hsi_s_net = opt[1];
        hsi_i_net = opt[2];
        led_set(true, true);
        return;
    }

    if (cmd == KHA_LED_CMD_SET_RGBW && optlen == 4) {
        led_r = opt[0];
        led_g = opt[1];
        led_b = opt[2];
        led_w = opt[3];

        led_set(false, true);
        return;
    }

    if (cmd == KHA_LED_CMD_IDENT && optlen == 0) {
        led_ident(true);
        return;
    }

}

int main(void) {
    SYSTEM_Initialize();

    //DELAY_milliseconds(10);
    //led_set(true, false);

    devaddr = SIGROW_Read(0x1300); //0x1300  
    if (devaddr == KHA_LED_ADDR_NONE || devaddr == KHA_LED_ADDR_BROADCAST) {
        while (1) {
            led_ident(false);
        }
    }

    sei();

    while (1) {
        // Raw:      0x42 0x23 <----------- payload ------------>
        // Encoded:  0x42 0x23 <len> <addr> <cmd> <options> <crc>
        // Decoded:  0x42      <len> <addr> <cmd> <options> <crc>
        // Buffer:                   <addr> <cmd> <options> <crc>       
        while (USART0_IsRxReady()) {
            uint8_t in = USART0_Read();

            if (in == KHA_LED_MSG_START) {
                msgEscapeDetected = true;
                continue;
            }

            if (msgEscapeDetected) {
                msgEscapeDetected = false;
                if (in == KHA_LED_MSG_START_CONFIRM) {
                    msgState = 1;
                    continue;
                }
                if (in != KHA_LED_MSG_START_ESCAPE) {
                    msgState = 0;
                    continue;
                }
                in = KHA_LED_MSG_START;
            }

            if (msgState == 0) {
                continue;
            }

            if (msgState == 1) {
                if (in >= KHA_LED_MSG_SIZE_MIN && in <= KHA_LED_MSG_SIZE_MAX) {
                    msgPayload[0] = in;
                    msgPayloadIdx = 1;
                    msgState = 2;
                    continue;
                }
                msgState = 0;
                continue;
            }

            if (msgState == 2) {
                if (msgPayloadIdx < msgPayload[0]) {
                    msgPayload[msgPayloadIdx] = in;
                    msgPayloadIdx++;
                }
                if (msgPayloadIdx == msgPayload[0]) {
                    msgState = 0;
                    process_rx();
                }
            }
        }
    }
}


/*
 // https://blog.saikoled.com/post/44677718712/how-to-convert-from-hsi-to-rgb-white

#include "math.h"
#define DEG_TO_RAD(X) (M_PI*(X)/180)

void hsi2rgbw(float H, float S, float I, int* rgbw) {
  int r, g, b, w;
  float cos_h, cos_1047_h;
  H = fmod(H,360); // cycle H around to 0-360 degrees
  H = 3.14159*H/(float)180; // Convert to radians.
  S = S>0?(S<1?S:1):0; // clamp S and I to interval [0,1]
  I = I>0?(I<1?I:1):0;
  
  if(H < 2.09439) {
    cos_h = cos(H);
    cos_1047_h = cos(1.047196667-H);
    r = S*255*I/3*(1+cos_h/cos_1047_h);
    g = S*255*I/3*(1+(1-cos_h/cos_1047_h));
    b = 0;
    w = 255*(1-S)*I;
  } else if(H < 4.188787) {
    H = H - 2.09439;
    cos_h = cos(H);
    cos_1047_h = cos(1.047196667-H);
    g = S*255*I/3*(1+cos_h/cos_1047_h);
    b = S*255*I/3*(1+(1-cos_h/cos_1047_h));
    r = 0;
    w = 255*(1-S)*I;
  } else {
    H = H - 4.188787;
    cos_h = cos(H);
    cos_1047_h = cos(1.047196667-H);
    b = S*255*I/3*(1+cos_h/cos_1047_h);
    r = S*255*I/3*(1+(1-cos_h/cos_1047_h));
    g = 0;
    w = 255*(1-S)*I;
  }  
  rgbw[0]=r;
  rgbw[1]=g;
  rgbw[2]=b;
  rgbw[3]=w;
}
 */