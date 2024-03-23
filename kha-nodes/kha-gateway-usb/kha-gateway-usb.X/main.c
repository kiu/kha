#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "../../../kha-common.X/kha-constants.h"
#include "../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---

#define REGISTER_SIZE 2
#define REGISTER_PRESET_WIDTH 0

// ---

static volatile uint8_t rxbuf[256];
static volatile uint8_t rxbuf_idx = 0;

static bool print_human = true;
static bool print_proto = false;

// HELPER ----------------------------------------------------------------------

uint8_t helperHex2uint8(char a, char b) {
    a = (a <= '9') ? a - '0' : (a & 0x7) + 9;
    b = (b <= '9') ? b - '0' : (b & 0x7) + 9;
    return (a << 4) +b;
}

// OUTPUT ----------------------------------------------------------------------

void dump_log(uint8_t id, uint8_t val1, uint8_t val2, uint8_t val3) {
    if (print_human) {
        printf("KS %02X LOG ", KHA_STACK_LOG_HUMAN);
        switch (id) {
            case KHA_STACK_LOG_INITIALIZATION_STARTED:
                printf("STACK Initializing (https://github.com/kiu/kha/kha-common)");
                break;
            case KHA_STACK_LOG_INITIALIZATION_COMPLETED:
                printf("STACK Completed (https://github.com/kiu/kha/kha-common)");
                break;

            case KHA_STACK_LOG_IDENT_DEVICE_ADDRESS_SET:
                printf("IDENT Setting device address: %02X", val1);
                break;
            case KHA_STACK_LOG_IDENT_DEVICE_ADDRESS_ERROR:
                printf("IDENT Invalid device address: %02X", val1);
                break;
            case KHA_STACK_LOG_IDENT_DEVICE_GROUP_SET:
                printf("IDENT Setting device group: %02X", val1);
                break;
            case KHA_STACK_LOG_IDENT_DEVICE_GROUP_ERROR:
                printf("IDENT Invalid device group: %02X", val1);
                break;
            case KHA_STACK_LOG_IDENT_BOARD_TYPE_SET:
                printf("IDENT Setting board type: %02X", val1);
                break;
            case KHA_STACK_LOG_IDENT_BOARD_TYPE_ERROR:
                printf("IDENT Invalid board type: %02X", val1);
                break;
            case KHA_STACK_LOG_IDENT_BOARD_REV_SET:
                printf("IDENT Setting board rev: %c", val1);
                break;
            case KHA_STACK_LOG_IDENT_BOARD_REV_ERROR:
                printf("IDENT Invalid board rev: %c", val1);
                break;
            case KHA_STACK_LOG_IDENT_USERROW_ADDR_ERROR:
                printf("IDENT Address %02x for userrow is out of bounds (%02X)", val1, val2);
                break;


            case KHA_STACK_LOG_REGISTER_SETSIZE:
                printf("REGISTER Setting memory to %02X bytes", val1);
                break;
            case KHA_STACK_LOG_REGISTER_SETSIZE_ERROR:
                printf("REGISTER Memory size exceeds length %02X (%02X)", val1, val2);
                break;
            case KHA_STACK_LOG_REGISTER_LOAD:
                printf("REGISTER Loading %02X bytes from storage", val1);
                break;
            case KHA_STACK_LOG_REGISTER_LOAD_ERROR:
                printf("REGISTER Loading from storage failed, read magic %02X but expected %02X", val1, val2);
                break;
            case KHA_STACK_LOG_REGISTER_WIPE:
                printf("REGISTER Wiping %02X bytes in memory", val1);
                break;
            case KHA_STACK_LOG_REGISTER_STORE:
                printf("REGISTER Saving %02X bytes to storage", val1);
                break;
            case KHA_STACK_LOG_REGISTER_READ:
                printf("REGISTER Address %02X, reading %02X bytes", val1, val2);
                break;
            case KHA_STACK_LOG_REGISTER_READ_SINGLE:
                printf("REGISTER Address %02X, reading value: %02X", val1, val2);
                break;
            case KHA_STACK_LOG_REGISTER_WRITE:
                printf("REGISTER Address %02X, writing %02X bytes", val1, val2);
                break;
            case KHA_STACK_LOG_REGISTER_WRITE_SINGLE:
                printf("REGISTER Address %02X, writing value %02X", val1, val2);
                break;
            case KHA_STACK_LOG_REGISTER_WRITE_CHANGED:
                printf("REGISTER Address %02X, modified requested value from %02X to %02X", val1, val2, val3);
                break;
            case KHA_STACK_LOG_REGISTER_ADDR_ERROR:
                printf("REGISTER Address %02X is out of bounds (%02X)", val1, val2);
                break;
            case KHA_STACK_LOG_REGISTER_LEN_ERROR:
                printf("REGISTER Address %02X, length %02X is out of bounds (%02X)", val1, val2, val3);
                break;
            case KHA_STACK_LOG_REGISTER_ADDR_LEN_ERROR:
                printf("REGISTER Address %02X with length %02X is out of bounds (%02X)", val1, val2, val3);
                break;

            case KHA_STACK_LOG_RX_DECODE_START_UNESCAPED_ERROR:
                printf("RX Decode failed, un-escaped START found");
                break;
            case KHA_STACK_LOG_RX_DECODE_START_MISSING_ERROR:
                printf("RX Decode failed, no START found");
                break;
            case KHA_STACK_LOG_RX_DECODE_LEN_ERROR:
                printf("RX Decode failed, exceeding length: %02X (%02X)", val1, val2);
                break;
            case KHA_STACK_LOG_RX_DECODE_CRC_ERROR:
                printf("RX Decode failed, CRC expected %02X but read %02X", val1, val2);
                break;

            case KHA_STACK_LOG_TX_BUFFER_FULL_ERROR:
                printf("TX Message buffer is full");
                break;
            case KHA_STACK_LOG_TX_ENCODE_OPT_LEN:
                printf("TX Message optlen exceeds length %02X (%02X)", val1, val2);
                break;
            case KHA_STACK_LOG_TX_ENABLE:
                printf("TX enabled");
                break;
            case KHA_STACK_LOG_TX_DISABLE:
                printf("TX disabled");
                break;

            case KHA_STACK_LOG_CMD_PARAMETERS_ERROR:
                printf("CMD Command %02X ignored, expected optlen of %02X but read %02X", val1, val2, val3);
                break;
            case KHA_STACK_LOG_CMD_SENDER_IGNORE:
                printf("CMD Command %02X from non-unicast sender %02X ignored", val1, val2);
                break;
            case KHA_STACK_LOG_CMD_BOOTLOADER_IGNORE:
                printf("CMD Command %02X ignored while in bootloader mode", val1);
                break;
            case KHA_STACK_LOG_CMD_WRITE_BROADCAST:
                printf("CMD Register Write with broadcast target ignored");
                break;

            case KHA_STACK_LOG_DEVICE_DEBUG_ENABLE:
                printf("DEVICE Debug enabled");
                break;
            case KHA_STACK_LOG_DEVICE_DEBUG_DISABLE:
                printf("DEVICE Debug disabled");
                break;
            case KHA_STACK_LOG_DEVICE_STATS_CLEAR:
                printf("DEVICE Clearing stats");
                break;

            default:
                printf("Unknown log [%02X %02X %02X %02X]", id, val1, val2, val3);
                break;
        }
        printf("\n");
    }

    if (print_proto) {
        printf("KS %02X %02X %02X %02X\n", id, val1, val2, val3);
    }
}

void dump_msg(uint8_t buf[]) {
    printf(" L%02X F%02X T%02X (", buf[0], buf[1], buf[2]);
    switch (kha_stack_msg_addr_type(buf[2])) {
        case KHA_STACK_MSG_ADDR_TYPE_NONE:
            printf("N");
            break;
        case KHA_STACK_MSG_ADDR_TYPE_UNICAST_FALLBACK:
            printf("U");
            break;
        case KHA_STACK_MSG_ADDR_TYPE_UNICAST:
            printf("U");
            break;
        case KHA_STACK_MSG_ADDR_TYPE_MULTICAST_FALLBACK:
            printf("M");
            break;
        case KHA_STACK_MSG_ADDR_TYPE_MULTICAST:
            printf("M");
            break;
        case KHA_STACK_MSG_ADDR_TYPE_BROADCAST:
            printf("B");
            break;
        default:
            printf("?");
            break;
    }
    printf(")");

    printf(" C%02X [", buf[3]);
    switch (buf[3]) {
        case KHA_CMD_MANAGEMENT_REBOOT:
            printf("REBOOT]      ");
            break;
        case KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR:
            printf("BOOT ERROR]  ");
            break;
        case KHA_CMD_MANAGEMENT_BOOT_NOT_EXIT:
            printf("BOOT STAY]   ");
            break;
        case KHA_CMD_MANAGEMENT_BOOT_WIPE_FLASH:
            printf("WIPE FLASH]  ");
            break;
        case KHA_CMD_MANAGEMENT_BOOT_WIPE_EEPROM:
            printf("WIPE EEPROM] ");
            break;
        case KHA_CMD_MANAGEMENT_BOOT_FW_DATA:
            printf("FW DATA]     ");
            break;
        case KHA_CMD_MANAGEMENT_BOOT_FW_WRITE:
            printf("FW WRITE]    ");
            break;
        case KHA_CMD_MANAGEMENT_TX_ENABLE:
            printf("TX ON]       ");
            break;
        case KHA_CMD_MANAGEMENT_TX_DISABLE:
            printf("TX OFF]      ");
            break;


        case KHA_CMD_DEVICE_PRESET:
            printf("PRESET]      ");
            break;
        case KHA_CMD_DEVICE_UI_ENABLE:
            printf("UI ON]       ");
            break;
        case KHA_CMD_DEVICE_UI_DISABLE:
            printf("UI OFF]      ");
            break;
        case KHA_CMD_DEVICE_DEBUG_ENABLE:
            printf("DEBUG ON]    ");
            break;
        case KHA_CMD_DEVICE_DEBUG_DISABLE:
            printf("DEBUG OFF]   ");
            break;
        case KHA_CMD_DEVICE_DEBUG_MSG:
            printf("DEBUG MSG]   ");
            break;
        case KHA_CMD_DEVICE_STATS_CLEAR:
            printf("STATS CLEAR] ");
            break;
        case KHA_CMD_DEVICE_STATS_RESPONSE:
            printf("STATS RES]   ");
            break;
        case KHA_CMD_DEVICE_STATS_REQUEST:
            printf("STATS REQ]   ");
            break;
        case KHA_CMD_DEVICE_PONG:
            printf("PONG]        ");
            break;
        case KHA_CMD_DEVICE_PING:
            printf("PING]        ");
            break;
        case KHA_CMD_DEVICE_UP:
            printf("UP]          ");
            break;
        case KHA_CMD_DEVICE_IDENT_RESPONSE:
            printf("IDENT RES]   ");
            break;
        case KHA_CMD_DEVICE_IDENT_REQUEST:
            printf("IDENT REQ]   ");
            break;

        case KHA_CMD_REGISTER_CONFIG_WIPE:
            printf("REG WIPE]    ");
            break;
        case KHA_CMD_REGISTER_CONFIG_STORE:
            printf("REG STORE]   ");
            break;
        case KHA_CMD_REGISTER_CONFIG_LOAD:
            printf("REG LOAD]    ");
            break;
        case KHA_CMD_REGISTER_WRITE_FAIL:
            printf("WRITE FAIL]  ");
            break;
        case KHA_CMD_REGISTER_WRITE_SUCCESS:
            printf("WRITE OK]    ");
            break;
        case KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY:
            printf("WRITE REQ NR]");
            break;
        case KHA_CMD_REGISTER_WRITE_REQUEST:
            printf("WRITE REQ]   ");
            break;
        case KHA_CMD_REGISTER_READ_RESPONSE:
            printf("READ RES]    ");
            break;
        case KHA_CMD_REGISTER_READ_REQUEST:
            printf("READ REQ]    ");
            break;

        case KHA_CMD_APP_LED_ANIMATION:
            printf("A LED ANIM]  ");
            break;
        case KHA_CMD_APP_LED_HSI:
            printf("A LED HSI]   ");
            break;

        case KHA_CMD_SYSTEM_NOP:
            printf("NOP]         ");
            break;
        default:
            printf("UNKNOWN]     ");
            break;
    }

    printf(" <");
    uint8_t optlen = buf[0] - KHA_MSG_LEN_MIN;
    if (optlen > 0) {
        for (uint8_t i = 0; i < optlen; i++) {
            printf("%02X", buf[4 + i]);
            if ((i + 1) % 4 == 0 && i + 1 < optlen) {
                printf(" ");
            }
        }
    }
    printf(">");

    //printf(" CRC:%02X", buf[buf[0] - 1]);

    printf("\n");
}

void dump_msg_raw(uint8_t buf[]) {
    for (uint8_t i = 0; i < buf[0]; i++) {
        printf("%02X", buf[i]);
    }
}
// TX --------------------------------------------------------------------------

bool tx_all(uint8_t buf[]) {
    if (print_human) {
        printf("KS %02X TX", KHA_STACK_LOG_HUMAN);
        dump_msg(buf);
    }
    if (print_proto) {

        printf("KS %02X ", KHA_STACK_LOG_TX);
        dump_msg_raw(buf);
        printf("\n");
    }
    return false;
}

bool tx_send_hex(uint8_t buf[], uint8_t buf_len) {
    if (buf_len % 2 != 0) {
        if (print_human) {
            printf("GW 00 Uneven hex characters: %02X\n", buf_len);
        }
        if (print_proto) {
            printf("GW 10 %02X\n", buf_len);
        }
        return false;
    }

    for (uint8_t p = 0; p < buf_len; p++) {
        char c = buf[p];
        if (c >= 97 && c <= 102) {
            // Uppercase
            buf[p] = c - 32;
            c = buf[p];
        }

        if (c >= 48 && c <= 57) {
            continue;
        }
        if (c >= 65 && c <= 70) {
            continue;
        }

        if (print_human) {
            printf("GW 00 Invalid hex characters: %s\n", buf);
        }
        if (print_proto) {
            printf("GW 11 %s\n", buf);
        }

        return false;
    }

    uint8_t to = helperHex2uint8(buf[0], buf[1]);
    uint8_t cmd = helperHex2uint8(buf[2], buf[3]);
    uint8_t optlen = (buf_len - 4) / 2;

    if (optlen > KHA_MSG_LEN_OPT_MAX) {
        if (print_human) {
            printf("GW 00 Message options exceeds length %02X vs %02X\n", optlen, KHA_MSG_LEN_OPT_MAX);
        }
        if (print_proto) {
            printf("GW 12 %02X %02X\n", optlen, KHA_MSG_LEN_OPT_MAX);
        }
        return false;
    }

    uint8_t opt[optlen];
    for (uint8_t p = 0; p < optlen; p++) {
        opt[p] = helperHex2uint8(buf[(p * 2) + 4], buf[(p * 2) + 5]);
    }

    kha_stack_tx_create(to, cmd, optlen, opt);

    return true;
}

// RX --------------------------------------------------------------------------

bool rx_msg_all(uint8_t buf[]) {
    if (print_human) {
        printf("KS %02X RX", KHA_STACK_LOG_HUMAN);
        dump_msg(buf);
    }
    if (print_proto) {
        printf("KS %02X ", KHA_STACK_LOG_RX);
        dump_msg_raw(buf);
        printf("\n");
    }

    return false;
}

void rx(void) {
    uint8_t c = '\0';
    while (USART1_IsRxReady()) {
        c = USART1_Read();
        if (c == '\r') {
            continue;
        }
        if (c == ' ') {
            continue;
        }
        if (c == '\n' || rxbuf_idx == 255) {
            rxbuf[rxbuf_idx] = '\0';
            uint8_t hex[rxbuf_idx];
            for (uint8_t i = 0; i < rxbuf_idx; i++) {
                hex[i] = rxbuf[i];
            }
            tx_send_hex(hex, rxbuf_idx);
            rxbuf_idx = 0;
        } else {
            rxbuf[rxbuf_idx] = c;
            rxbuf_idx++;
        }
    }
}

// REGISTER ------------------------------------------------------------------------

uint8_t register_change(uint8_t addr, uint8_t value) {
    if (addr < REGISTER_SIZE) {
        if (value > 1) {
            value = 0;
        }
        if (addr == 0) {
            print_proto = value;
        }
        if (addr == 1) {
            print_human = value;
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

// INIT ------------------------------------------------------------------------

int main(void) {
    SYSTEM_Initialize();

    sei();

    printf("\n\nhttps://github.com/kiu/kha\n");
    printf("kha-gateway-usb (V%lu): Initializing\n\n", KHA_VERSION);

    kha_stack_register_cbr_change(register_change);
    kha_stack_rx_cbr_msg_all(rx_msg_all);
    kha_stack_tx_cbr_msg_all(tx_all);
    kha_stack_cbr_log(dump_log);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);
    
    USART1_RxCompleteCallbackRegister(rx);

    while (1) {
        kha_stack_process_rx_tx();
        asm("wdr");
    }
}