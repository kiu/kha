#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/reset/rstctrl.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/nvm/nvm.h"
#include "kha-constants.h"
#include "kha-stack.h"

// -----------------------------------------------------------------------------

static bool kha_stack_bootloader = false;

// ----

typedef struct {
    uint8_t rx;
    uint8_t rx_error_start_unescaped;
    uint8_t rx_error_start_missing;
    uint8_t rx_error_len;
    uint8_t rx_error_crc;
    uint8_t tx;
    uint8_t tx_error_len;
    uint8_t tx_error_full;
} kha_stack_stats_t;

static kha_stack_stats_t kha_stack_stats;

// ----

static void(*kha_stack_cbh_log)(uint8_t id, uint8_t val1, uint8_t val2, uint8_t val3);
static bool kha_stack_debug = false;

// ----

static void(*kha_stack_ui_cbh_change)();
static bool kha_stack_ui_enabled_state = true;

// ----

static uint8_t kha_stack_userrow[KHA_STACK_USERROW_LEN];
static uint8_t kha_stack_board_type = KHA_BOARD_TYPE_FALLBACK;
static uint8_t kha_stack_board_rev = KHA_BOARD_REV_FALLBACK;
static uint8_t kha_stack_dev_addr = KHA_ADDR_UNICAST_FALLBACK;
static uint8_t kha_stack_dev_group = KHA_ADDR_BROADCAST_GROUP_FALLBACK;

// ----

static uint8_t(*kha_stack_register_cbh_change)(uint8_t addr, uint8_t value);
static uint8_t kha_stack_register_len = KHA_STACK_EEPROM_REGISTER_LEN;
static uint8_t kha_stack_register_buf[KHA_STACK_EEPROM_REGISTER_LEN];
static uint8_t kha_stack_register_preset_start = 0;
static uint8_t kha_stack_register_preset_bytes = 0;

// ----

static void(*kha_stack_preset_cbh_change)(uint8_t preset, bool enabled, uint8_t addr);
static uint8_t kha_stack_preset_value = KHA_PRESET_NONE;

// ----

static enum KHA_STATE_MSG_DECODE_STATE {
    KHA_STATE_MSG_DECODE_IDLE,
    KHA_STATE_MSG_DECODE_START,
    KHA_STATE_MSG_DECODE_LENGTH
} kha_stack_rx_buf_state;

static uint8_t kha_stack_rx_buf[KHA_MSG_LEN_MAX];
static uint8_t kha_stack_rx_buf_idx = 0;
static bool kha_stack_rx_buf_escape_detected = false;

static bool(*kha_stack_rx_cbh_msg_all)(uint8_t buf[]);
static bool(*kha_stack_rx_cbh_msg_all_post)(uint8_t buf[]);
static bool(*kha_stack_rx_cbh_msg_matched)(uint8_t buf[]);
static bool(*kha_stack_rx_cbh_msg_unprocessed)(uint8_t buf[]);

// ----

static uint8_t kha_stack_tx_queue[KHA_STACK_QUEUE_TX_LEN];
static bool kha_stack_tx_enable = true;
static volatile uint16_t kha_stack_tx_block_index = 0;
static bool(*kha_stack_tx_cbh_msg_all)(uint8_t buf[]);

// LOG -------------------------------------------------------------------------

void kha_stack_cbr_log(void(* cb)(uint8_t id, uint8_t val1, uint8_t val2, uint8_t val3)) {
    kha_stack_cbh_log = cb;
}

void kha_stack_log(uint8_t id, uint8_t val1, uint8_t val2, uint8_t val3) {
    if (kha_stack_cbh_log != NULL) {
        (*kha_stack_cbh_log)(id, val1, val2, val3);
    }
    if (kha_stack_debug && id != KHA_STACK_LOG_TX_BUFFER_FULL_ERROR) {
        uint8_t buf[4];
        buf[0] = id;
        buf[1] = val1;
        buf[2] = val2;
        buf[3] = val3;
        kha_stack_tx_create(0x00, KHA_CMD_DEVICE_DEBUG_MSG, 4, buf);
    }
}

// UI --------------------------------------------------------------------------

void kha_stack_ui_cbr_change(void(* cb)()) {
    kha_stack_ui_cbh_change = cb;
}

bool kha_stack_ui_enabled() {
    return kha_stack_ui_enabled_state;
}

void kha_stack_ui_enable() {
    if (kha_stack_ui_enabled_state) {
        return;
    }
    kha_stack_ui_enabled_state = true;
    if (kha_stack_ui_cbh_change != NULL) {
        (*kha_stack_ui_cbh_change)(true);
    }
    kha_stack_tx_create(KHA_ADDR_BROADCAST, KHA_CMD_DEVICE_UI_ENABLE, 0, NULL);
}

void kha_stack_ui_disable() {
    if (!kha_stack_ui_enabled_state) {
        return;
    }
    kha_stack_ui_enabled_state = false;
    if (kha_stack_ui_cbh_change != NULL) {
        (*kha_stack_ui_cbh_change)(false);
    }
    kha_stack_tx_create(KHA_ADDR_BROADCAST, KHA_CMD_DEVICE_UI_DISABLE, 0, NULL);
}

// STATS -----------------------------------------------------------------------

void kha_stack_stats_clear() {
    kha_stack_stats.rx = 0;
    kha_stack_stats.rx_error_start_unescaped = 0;
    kha_stack_stats.rx_error_start_missing = 0;
    kha_stack_stats.rx_error_len = 0;
    kha_stack_stats.rx_error_crc = 0;

    kha_stack_stats.tx = 0;
    kha_stack_stats.tx_error_len = 0;
    kha_stack_stats.tx_error_full = 0;

    kha_stack_log(KHA_STACK_LOG_DEVICE_STATS_CLEAR, 0x00, 0x00, 0x00);
}

// CRC -------------------------------------------------------------------------

//based on https://stackoverflow.com/questions/51752284/how-to-calculate-crc8-in-c

#if KHA_STACK_CRC_LOOKUP >= 1
static const uint8_t kha_crc8_table[256] = {
    0x00, 0x31, 0x62, 0x53, 0xC4, 0xF5, 0xA6, 0x97, 0xB9, 0x88, 0xDB, 0xEA, 0x7D, 0x4C, 0x1F, 0x2E,
    0x43, 0x72, 0x21, 0x10, 0x87, 0xB6, 0xE5, 0xD4, 0xFA, 0xCB, 0x98, 0xA9, 0x3E, 0x0F, 0x5C, 0x6D,
    0x86, 0xB7, 0xE4, 0xD5, 0x42, 0x73, 0x20, 0x11, 0x3F, 0x0E, 0x5D, 0x6C, 0xFB, 0xCA, 0x99, 0xA8,
    0xC5, 0xF4, 0xA7, 0x96, 0x01, 0x30, 0x63, 0x52, 0x7C, 0x4D, 0x1E, 0x2F, 0xB8, 0x89, 0xDA, 0xEB,
    0x3D, 0x0C, 0x5F, 0x6E, 0xF9, 0xC8, 0x9B, 0xAA, 0x84, 0xB5, 0xE6, 0xD7, 0x40, 0x71, 0x22, 0x13,
    0x7E, 0x4F, 0x1C, 0x2D, 0xBA, 0x8B, 0xD8, 0xE9, 0xC7, 0xF6, 0xA5, 0x94, 0x03, 0x32, 0x61, 0x50,
    0xBB, 0x8A, 0xD9, 0xE8, 0x7F, 0x4E, 0x1D, 0x2C, 0x02, 0x33, 0x60, 0x51, 0xC6, 0xF7, 0xA4, 0x95,
    0xF8, 0xC9, 0x9A, 0xAB, 0x3C, 0x0D, 0x5E, 0x6F, 0x41, 0x70, 0x23, 0x12, 0x85, 0xB4, 0xE7, 0xD6,
    0x7A, 0x4B, 0x18, 0x29, 0xBE, 0x8F, 0xDC, 0xED, 0xC3, 0xF2, 0xA1, 0x90, 0x07, 0x36, 0x65, 0x54,
    0x39, 0x08, 0x5B, 0x6A, 0xFD, 0xCC, 0x9F, 0xAE, 0x80, 0xB1, 0xE2, 0xD3, 0x44, 0x75, 0x26, 0x17,
    0xFC, 0xCD, 0x9E, 0xAF, 0x38, 0x09, 0x5A, 0x6B, 0x45, 0x74, 0x27, 0x16, 0x81, 0xB0, 0xE3, 0xD2,
    0xBF, 0x8E, 0xDD, 0xEC, 0x7B, 0x4A, 0x19, 0x28, 0x06, 0x37, 0x64, 0x55, 0xC2, 0xF3, 0xA0, 0x91,
    0x47, 0x76, 0x25, 0x14, 0x83, 0xB2, 0xE1, 0xD0, 0xFE, 0xCF, 0x9C, 0xAD, 0x3A, 0x0B, 0x58, 0x69,
    0x04, 0x35, 0x66, 0x57, 0xC0, 0xF1, 0xA2, 0x93, 0xBD, 0x8C, 0xDF, 0xEE, 0x79, 0x48, 0x1B, 0x2A,
    0xC1, 0xF0, 0xA3, 0x92, 0x05, 0x34, 0x67, 0x56, 0x78, 0x49, 0x1A, 0x2B, 0xBC, 0x8D, 0xDE, 0xEF,
    0x82, 0xB3, 0xE0, 0xD1, 0x46, 0x77, 0x24, 0x15, 0x3B, 0x0A, 0x59, 0x68, 0xFF, 0xCE, 0x9D, 0xAC
};
#endif

uint8_t kha_stack_crc8(uint8_t* data, size_t len) {
#if KHA_STACK_CRC_LOOKUP >= 1
    uint8_t crc = 0xFF; // init value
    for (size_t i = 0; i < len; i++) {
        crc = kha_crc8_table[data[i] ^ crc];
    }
    return crc;
#else
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
#endif
}

uint32_t kha_stack_crc32(uint32_t crc, uint8_t byte) {
    // https://www.mikrocontroller.net/topic/225796
    int8_t i;
    crc = crc ^ byte;
    for (i = 7; i >= 0; i--) {
        crc = (crc >> 1) ^ (0xedb88320ul & (-(crc & 1)));
    }
    return crc;
}

void kha_stack_crc32_flash_and_store(uint16_t from, uint16_t to, uint8_t offset) {
    uint32_t reg = 0xffffffff;
    for (uint16_t i = from; i < to; i++) {
        reg = kha_stack_crc32(reg, (uint8_t) FLASH_Read(i));
    }

    for (uint8_t i = 0; i < 4; i++) {
        while (EEPROM_IsBusy()) {
        }
        EEPROM_Write(KHA_STACK_EEPROM_ADDR_START + offset + i, (reg >> ((3 - i) * 8) & 0xFF));
    }
}

// MSG -------------------------------------------------------------------------

bool kha_stack_msg_match(uint8_t to) {
    if (to == kha_stack_dev_addr) {
        return true;
    }
    if (to == kha_stack_dev_group && kha_stack_dev_group != KHA_ADDR_BROADCAST_GROUP_NONE) {
        return true;
    }
    if (to == KHA_ADDR_BROADCAST) {
        return true;
    }

    return false;
}

bool kha_stack_board_match(uint8_t type, uint8_t rev) {
    if (type != KHA_BOARD_TYPE_ALL && type != kha_stack_board_type) {
        return false;
    }
    if (rev != KHA_BOARD_REV_ALL && rev != kha_stack_board_rev) {
        return false;
    }

    return true;
}

KHA_STACK_MSG_ADDR_TYPE_t kha_stack_msg_addr_type(uint8_t addr) {
    if (addr == KHA_ADDR_NONE) {
        return KHA_STACK_MSG_ADDR_TYPE_NONE;
    }

    if (addr == KHA_ADDR_UNICAST_FALLBACK) {
        return KHA_STACK_MSG_ADDR_TYPE_UNICAST_FALLBACK;
    }

    if (addr == KHA_ADDR_BROADCAST_GROUP_FALLBACK) {
        return KHA_STACK_MSG_ADDR_TYPE_MULTICAST_FALLBACK;
    }

    if (addr >= KHA_ADDR_BROADCAST_GROUP_MIN && addr <= KHA_ADDR_BROADCAST_GROUP_MAX) {
        return KHA_STACK_MSG_ADDR_TYPE_MULTICAST;
    }

    if (addr == KHA_ADDR_BROADCAST) {
        return KHA_STACK_MSG_ADDR_TYPE_BROADCAST;
    }

    return KHA_STACK_MSG_ADDR_TYPE_UNICAST;
}

// GETTER ----------------------------------------------------------------------

uint8_t kha_stack_device_address_get() {
    return kha_stack_dev_addr;
}

uint8_t kha_stack_device_group_get() {
    return kha_stack_dev_group;
}

uint8_t kha_stack_board_type_get() {
    return kha_stack_board_type;
}

uint8_t kha_stack_board_rev_get() {
    return kha_stack_board_rev;
}

uint8_t kha_stack_userrow_data(uint8_t addr) {
    if (addr + KHA_STACK_USERROW_DATA_OFFSET > KHA_STACK_USERROW_LEN) {
        kha_stack_log(KHA_STACK_LOG_IDENT_USERROW_ADDR_ERROR, addr, KHA_STACK_USERROW_LEN - KHA_STACK_USERROW_DATA_OFFSET, 0x00);
        return 0x00;
    }
    return kha_stack_userrow[addr + KHA_STACK_USERROW_DATA_OFFSET];
}

// REGISTER --------------------------------------------------------------------

void kha_stack_register_cbr_change(uint8_t(* cb)(uint8_t addr, uint8_t value)) {
    kha_stack_register_cbh_change = cb;
}

uint8_t kha_stack_register_get(uint8_t addr) {
    if (addr >= kha_stack_register_len) {
        kha_stack_log(KHA_STACK_LOG_REGISTER_ADDR_ERROR, addr, kha_stack_register_len, 0x00);
        return 0x00;
    }
    uint8_t val = kha_stack_register_buf[addr];
    kha_stack_log(KHA_STACK_LOG_REGISTER_READ_SINGLE, addr, val, 0x00);
    return val;
}

bool kha_stack_register_set(uint8_t addr, uint8_t val, bool force_callback) {
    if (addr >= kha_stack_register_len) {
        kha_stack_log(KHA_STACK_LOG_REGISTER_ADDR_ERROR, addr, kha_stack_register_len, 0x00);
        return false;
    }

    if (!force_callback && val == kha_stack_register_buf[addr]) {
        return true;
    }

    if (kha_stack_register_cbh_change != NULL) {
        uint8_t valnew = (*kha_stack_register_cbh_change)(addr, val);
        if (val != valnew) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_WRITE_CHANGED, addr, val, valnew);
            val = valnew;
        }
    }

    kha_stack_log(KHA_STACK_LOG_REGISTER_WRITE_SINGLE, addr, val, 0x00);
    kha_stack_register_buf[addr] = val;
    return true;
}

void kha_stack_register_wipe() {
    kha_stack_log(KHA_STACK_LOG_REGISTER_WIPE, kha_stack_register_len, 0x00, 0x00);

    for (uint8_t i = 0; i < kha_stack_register_len; i++) {
        kha_stack_register_set(i, 0x00, true);
    }
}

void kha_stack_register_store() {
    for (uint8_t i = 0; i < kha_stack_register_len; i++) {
        while (EEPROM_IsBusy()) {
        }
        EEPROM_Write(KHA_STACK_EEPROM_ADDR_START + i, kha_stack_register_buf[i]);
    }
    while (EEPROM_IsBusy()) {
    }

    EEPROM_Write(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_MAGIC_OFFSET, KHA_STACK_EEPROM_MAGIC_OK);
    kha_stack_log(KHA_STACK_LOG_REGISTER_STORE, kha_stack_register_len, 0x00, 0x00);
}

void kha_stack_register_load() {
    uint8_t magic = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_MAGIC_OFFSET);
    if (magic != KHA_STACK_EEPROM_MAGIC_OK) {
        kha_stack_log(KHA_STACK_LOG_REGISTER_LOAD_ERROR, magic, KHA_STACK_EEPROM_MAGIC_OK, 0x00);
        kha_stack_register_wipe();
        kha_stack_register_store();
        return;
    }

    kha_stack_log(KHA_STACK_LOG_REGISTER_LOAD, kha_stack_register_len, 0x00, 0x00);
    for (uint8_t i = 0; i < kha_stack_register_len; i++) {
        while (EEPROM_IsBusy()) {
        }
        kha_stack_register_set(i, EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + i), true);
    }
}

// PRESET ----------------------------------------------------------------------

void kha_stack_preset_cbr_change(void(* cb)(uint8_t preset, bool enabled, uint8_t addr)) {
    kha_stack_preset_cbh_change = cb;
}

uint8_t kha_stack_preset() {
    return kha_stack_preset_value;
}

void kha_stack_preset_set(uint8_t preset, bool notify) {
    if (preset != KHA_PRESET_NONE && preset > KHA_PRESET_MAX) {
        return;
    }

    if (preset == kha_stack_preset_value) {
        return;
    }

    kha_stack_preset_value = preset;

    if (notify) {
        uint8_t buf1[1] = {preset};
        kha_stack_tx_create(KHA_ADDR_BROADCAST, KHA_CMD_DEVICE_PRESET, 1, buf1);
    }

    if (kha_stack_preset_cbh_change != NULL) {
        bool enabled = false;
        uint8_t start = 0xFF;

        if (kha_stack_register_preset_bytes > 0 && preset <= KHA_PRESET_MAX) {
            start = kha_stack_register_preset_start + (preset * (kha_stack_register_preset_bytes + 1));
            enabled = kha_stack_register_get(start);
        }

        (*kha_stack_preset_cbh_change)(preset, enabled, start + 1);
    }
}

// COMMANDS --------------------------------------------------------------------

void kha_stack_send_ident_or_up(uint8_t to, uint8_t cmd) {
    uint8_t buf[20];
    buf[0] = kha_stack_board_type;
    buf[1] = kha_stack_board_rev;
    buf[2] = kha_stack_dev_group;
    buf[3] = !kha_stack_bootloader;

    buf[4] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_BOOT_OFFSET + 0);
    buf[5] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_BOOT_OFFSET + 1);
    buf[6] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_BOOT_OFFSET + 2);
    buf[7] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_BOOT_OFFSET + 3);

    buf[8] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_BOOT_OFFSET + 0);
    buf[9] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_BOOT_OFFSET + 1);
    buf[10] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_BOOT_OFFSET + 2);
    buf[11] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_BOOT_OFFSET + 3);

    buf[12] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_APP_OFFSET + 0);
    buf[13] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_APP_OFFSET + 1);
    buf[14] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_APP_OFFSET + 2);
    buf[15] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_VERSION_APP_OFFSET + 3);

    buf[16] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_APP_OFFSET + 0);
    buf[17] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_APP_OFFSET + 1);
    buf[18] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_APP_OFFSET + 2);
    buf[19] = EEPROM_Read(KHA_STACK_EEPROM_ADDR_START + KHA_STACK_EEPROM_CRC_APP_OFFSET + 3);

    kha_stack_tx_create(to, cmd, 20, buf);
}

bool kha_stack_process_cmd(uint8_t msg[KHA_MSG_LEN_MAX]) {
    uint8_t size = msg[0];
    uint8_t from = msg[1];
    uint8_t to = msg[2];
    uint8_t cmd = msg[3];
    uint8_t optlen = size - KHA_MSG_LEN_MIN;
    uint8_t opt[optlen];
    for (uint8_t i = 0; i < optlen; i++) {
        opt[i] = msg[4 + i];
    }

    // -------------------------------------------------------------------------

    if ((kha_stack_msg_addr_type(from) != KHA_STACK_MSG_ADDR_TYPE_UNICAST) && (kha_stack_msg_addr_type(from) != KHA_STACK_MSG_ADDR_TYPE_UNICAST_FALLBACK)) {
        kha_stack_log(KHA_STACK_LOG_CMD_SENDER_IGNORE, cmd, from, 0x00);
        return true;
    }

    // -------------------------------------------------------------------------

    if (cmd == KHA_CMD_MANAGEMENT_REBOOT) {
        if (optlen == 0) {
            RSTCTRL_reset();
            while (1) {
            };
        }
        if (optlen == 2) {
            uint8_t type = opt[0];
            uint8_t rev = opt[1];

            if (type == KHA_BOARD_TYPE_ALL || type == kha_stack_board_type) {
                if (rev == KHA_BOARD_REV_ALL || rev == kha_stack_board_rev) {
                    RSTCTRL_reset();
                    while (1) {
                    };
                }
            }
            return true;
        }

        kha_stack_log(KHA_STACK_LOG_CMD_PARAMETERS_ERROR, cmd, 2, optlen);
        return true;
    }

    if (cmd == KHA_CMD_MANAGEMENT_TX_ENABLE) {
        kha_stack_log(KHA_STACK_LOG_TX_ENABLE, 0x00, 0x00, 0x00);
        kha_stack_tx_enable = true;
        return true;
    }

    if (cmd == KHA_CMD_MANAGEMENT_TX_DISABLE) {
        kha_stack_log(KHA_STACK_LOG_TX_DISABLE, 0x00, 0x00, 0x00);
        kha_stack_tx_enable = false;
        return true;
    }

    // ---

    if (cmd == KHA_CMD_DEVICE_PRESET) {
        if (optlen != 1) {
            kha_stack_log(KHA_STACK_LOG_CMD_PARAMETERS_ERROR, cmd, 1, optlen);
            return true;
        }

        kha_stack_preset_set(opt[0], false);
        return true;
    }

    if (cmd == KHA_CMD_DEVICE_UI_ENABLE) {
        kha_stack_ui_enabled_state = true;
        if (kha_stack_ui_cbh_change != NULL) {
            (*kha_stack_ui_cbh_change)(true);
        }
    }

    if (cmd == KHA_CMD_DEVICE_UI_DISABLE) {
        kha_stack_ui_enabled_state = false;
        if (kha_stack_ui_cbh_change != NULL) {
            (*kha_stack_ui_cbh_change)(false);
        }
    }

    if (cmd == KHA_CMD_DEVICE_DEBUG_ENABLE) {
        kha_stack_log(KHA_STACK_LOG_DEVICE_DEBUG_ENABLE, 0x00, 0x00, 0x00);
        kha_stack_debug = true;
        return true;
    }

    if (cmd == KHA_CMD_DEVICE_DEBUG_DISABLE) {
        kha_stack_log(KHA_STACK_LOG_DEVICE_DEBUG_DISABLE, 0x00, 0x00, 0x00);
        kha_stack_debug = false;
        return true;
    }

    if (cmd == KHA_CMD_DEVICE_STATS_CLEAR) {
        kha_stack_stats_clear();
        return true;
    }

    if (cmd == KHA_CMD_DEVICE_STATS_REQUEST) {
        uint8_t buf[8];
        buf[0] = kha_stack_stats.rx;
        buf[1] = kha_stack_stats.rx_error_start_unescaped;
        buf[2] = kha_stack_stats.rx_error_start_missing;
        buf[3] = kha_stack_stats.rx_error_len;
        buf[4] = kha_stack_stats.rx_error_crc;
        buf[5] = kha_stack_stats.tx;
        buf[6] = kha_stack_stats.tx_error_len;
        buf[7] = kha_stack_stats.tx_error_full;
        kha_stack_tx_create(from, KHA_CMD_DEVICE_STATS_RESPONSE, 8, buf);
        return true;
    }

    if (cmd == KHA_CMD_DEVICE_PING) {
        kha_stack_tx_create(from, KHA_CMD_DEVICE_PONG, 0, NULL);
        return true;
    }

    if (cmd == KHA_CMD_DEVICE_IDENT_REQUEST) {
        kha_stack_send_ident_or_up(from, KHA_CMD_DEVICE_IDENT_RESPONSE);
        return true;
    }

    // ---

    if (cmd == KHA_CMD_REGISTER_CONFIG_WIPE) {
        if (kha_stack_bootloader) {
            kha_stack_log(KHA_STACK_LOG_CMD_BOOTLOADER_IGNORE, cmd, 0x00, 0x00);
            return true;
        }
        kha_stack_register_wipe();
        return true;
    }

    if (cmd == KHA_CMD_REGISTER_CONFIG_STORE) {
        if (kha_stack_bootloader) {
            kha_stack_log(KHA_STACK_LOG_CMD_BOOTLOADER_IGNORE, cmd, 0x00, 0x00);
            return true;
        }
        kha_stack_register_store();
        return true;
    }

    if (cmd == KHA_CMD_REGISTER_CONFIG_LOAD) {
        if (kha_stack_bootloader) {
            kha_stack_log(KHA_STACK_LOG_CMD_BOOTLOADER_IGNORE, cmd, 0x00, 0x00);
            return true;
        }
        kha_stack_register_load();
        return true;
    }

    if (cmd == KHA_CMD_REGISTER_WRITE_REQUEST || cmd == KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY) {
        if (optlen < 2) {
            kha_stack_log(KHA_STACK_LOG_CMD_PARAMETERS_ERROR, cmd, 2, optlen);
            return true;
        }
        if (kha_stack_bootloader) {
            kha_stack_log(KHA_STACK_LOG_CMD_BOOTLOADER_IGNORE, cmd, 0x00, 0x00);
            return true;
        }

        if (to == KHA_ADDR_BROADCAST) {
            kha_stack_log(KHA_STACK_LOG_CMD_WRITE_BROADCAST, cmd, 0x00, 0x00);
            return true;
        }

        bool send_reply = cmd == KHA_CMD_REGISTER_WRITE_REQUEST;

        uint16_t reg_addr = opt[0];
        uint8_t reg_len = optlen - 1;
        uint8_t reg_reply[1] = {reg_addr};

        if (reg_addr >= kha_stack_register_len) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_ADDR_ERROR, reg_addr, reg_len, kha_stack_register_len);
            if (send_reply) {
                kha_stack_tx_create(from, KHA_CMD_REGISTER_WRITE_FAIL, 1, reg_reply);
            }
            return true;
        }
        if (reg_len > kha_stack_register_len) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_LEN_ERROR, reg_addr, reg_len, kha_stack_register_len);
            if (send_reply) {
                kha_stack_tx_create(from, KHA_CMD_REGISTER_WRITE_FAIL, 1, reg_reply);
            }
            return true;
        }
        if (reg_addr + reg_len > kha_stack_register_len) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_ADDR_LEN_ERROR, reg_addr, reg_len, kha_stack_register_len);
            if (send_reply) {
                kha_stack_tx_create(from, KHA_CMD_REGISTER_WRITE_FAIL, 1, reg_reply);
            }
            return true;
        }

        kha_stack_log(KHA_STACK_LOG_REGISTER_WRITE, reg_addr, reg_len, 0x00);

        bool error = false;
        for (uint8_t i = 0; i < reg_len; i++) {
            error = error | !kha_stack_register_set(reg_addr + i, opt[i + 1], false);
        }

        if (send_reply) {
            if (error) {
                kha_stack_tx_create(from, KHA_CMD_REGISTER_WRITE_FAIL, 1, reg_reply);
            } else {
                kha_stack_tx_create(from, KHA_CMD_REGISTER_WRITE_SUCCESS, 1, reg_reply);
            }
        }

        return true;
    }

    if (cmd == KHA_CMD_REGISTER_READ_REQUEST) {
        if (optlen != 2) {
            kha_stack_log(KHA_STACK_LOG_CMD_PARAMETERS_ERROR, cmd, 0x02, optlen);
            return true;
        }

        if (kha_stack_bootloader) {
            kha_stack_log(KHA_STACK_LOG_CMD_BOOTLOADER_IGNORE, cmd, 0x00, 0x00);
            return true;
        }

        uint16_t reg_addr = opt[0];
        uint8_t reg_len = opt[1];

        if (reg_addr >= kha_stack_register_len) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_ADDR_ERROR, reg_addr, reg_len, 0x00);
            kha_stack_tx_create(from, KHA_CMD_REGISTER_READ_RESPONSE, 0, NULL);
            return true;
        }
        if (reg_len > kha_stack_register_len) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_LEN_ERROR, reg_addr, reg_len, kha_stack_register_len);
            kha_stack_tx_create(from, KHA_CMD_REGISTER_READ_RESPONSE, 0, NULL);
            return true;
        }
        if (reg_len > KHA_MSG_LEN_OPT_MAX - 1) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_LEN_ERROR, reg_addr, reg_len, KHA_MSG_LEN_OPT_MAX - 1);
            kha_stack_tx_create(from, KHA_CMD_REGISTER_READ_RESPONSE, 0, NULL);
            return true;
        }
        if (reg_addr + reg_len > kha_stack_register_len) {
            kha_stack_log(KHA_STACK_LOG_REGISTER_ADDR_LEN_ERROR, reg_addr, reg_len, kha_stack_register_len);
            kha_stack_tx_create(from, KHA_CMD_REGISTER_READ_RESPONSE, 0, NULL);
            return true;
        }

        kha_stack_log(KHA_STACK_LOG_REGISTER_READ, reg_addr, reg_len, 0x00);

        uint8_t reply[1 + reg_len];
        reply[0] = reg_addr;
        for (uint8_t i = 0; i < reg_len; i++) {
            reply[i + 1] = kha_stack_register_buf[reg_addr + i];
        }
        kha_stack_tx_create(from, KHA_CMD_REGISTER_READ_RESPONSE, 1 + reg_len, reply);
        return true;
    }

    // ---

    if (cmd == KHA_CMD_SYSTEM_NOP) {
        return true;
    }

    // -------------------------------------------------------------------------

    return false;
}

// RX --------------------------------------------------------------------------

void kha_stack_rx_cbr_msg_all(bool(* cb)(uint8_t buf[])) {
    kha_stack_rx_cbh_msg_all = cb;
}

void kha_stack_rx_cbr_msg_all_post(bool(* cb)(uint8_t buf[])) {
    kha_stack_rx_cbh_msg_all_post = cb;
}

void kha_stack_rx_cbr_msg_matched(bool(* cb)(uint8_t buf[])) {
    kha_stack_rx_cbh_msg_matched = cb;
}

void kha_stack_rx_cbr_msg_unprocessed(bool(* cb)(uint8_t buf[])) {
    kha_stack_rx_cbh_msg_unprocessed = cb;
}

void kha_process_rx() {
    bool skip = false;

    if (kha_stack_rx_cbh_msg_all != NULL) {
        if ((*kha_stack_rx_cbh_msg_all)(kha_stack_rx_buf)) {
            skip = true;
        }
    }

    if (!skip && !kha_stack_msg_match(kha_stack_rx_buf[2])) {
        skip = true;
    }

    if (!skip && kha_stack_rx_cbh_msg_matched != NULL) {
        if ((*kha_stack_rx_cbh_msg_matched)(kha_stack_rx_buf)) {
            skip = true;
        }
    }

    if (!skip && kha_stack_process_cmd(kha_stack_rx_buf)) {
        skip = true;
    }

    if (!skip && kha_stack_rx_cbh_msg_unprocessed != NULL) {
        if ((*kha_stack_rx_cbh_msg_unprocessed)(kha_stack_rx_buf)) {
            skip = true;
        }
    }

    if (kha_stack_rx_cbh_msg_all_post != NULL) {
        (*kha_stack_rx_cbh_msg_all_post)(kha_stack_rx_buf);
    }
}

void kha_stack_process_rx() {

    // Raw:      0x42 0x23 <-----------     data     ------------>
    // Encoded:  0x42 0x23 <len> <from> <to> <cmd> <payload> <crc>
    // Buffer:             <len> <from> <to> <cmd> <payload> <crc>

    while (USART0_IsRxReady()) {
        uint8_t in = USART0_Read();

        // Has the magic byte been received?
        if (in == KHA_MSG_START) {
            kha_stack_rx_buf_escape_detected = true;
            continue;
        }

        //If the last byte was the magic byte, act on next byte.
        if (kha_stack_rx_buf_escape_detected) {
            kha_stack_rx_buf_escape_detected = false;
            // Confirmed that message start was meant
            if (in == KHA_MSG_START_CONFIRM) {
                kha_stack_rx_buf_state = KHA_STATE_MSG_DECODE_START;
                continue;
            }
            // It wasn't a confirmed start, but also not an escaped byte
            if (in != KHA_MSG_START_ESCAPE) {
                kha_stack_rx_buf_state = KHA_STATE_MSG_DECODE_IDLE;
                kha_stack_log(KHA_STACK_LOG_RX_DECODE_START_UNESCAPED_ERROR, 0x00, 0x00, 0x00);
                if (kha_stack_stats.rx_error_start_unescaped != 0xFF) {
                    kha_stack_stats.rx_error_start_unescaped++;
                }
                continue;
            }
            in = KHA_MSG_START;
        }

        // While in idle, they only way to start is with a confirmed start
        if (kha_stack_rx_buf_state == KHA_STATE_MSG_DECODE_IDLE) {
            kha_stack_log(KHA_STACK_LOG_RX_DECODE_START_MISSING_ERROR, 0x00, 0x00, 0x00);
            if (kha_stack_stats.rx_error_start_missing != 0xFF) {
                kha_stack_stats.rx_error_start_missing++;
            }
            continue;
        }

        if (kha_stack_rx_buf_state == KHA_STATE_MSG_DECODE_START) {
            if (in >= KHA_MSG_LEN_MIN && in <= KHA_MSG_LEN_MAX) {
                kha_stack_rx_buf[0] = in;
                kha_stack_rx_buf_idx = 1;
                kha_stack_rx_buf_state = KHA_STATE_MSG_DECODE_LENGTH;
                continue;
            }
            kha_stack_rx_buf_state = KHA_STATE_MSG_DECODE_IDLE;
            kha_stack_log(KHA_STACK_LOG_RX_DECODE_LEN_ERROR, in, KHA_MSG_LEN_MAX, 0x00);
            if (kha_stack_stats.rx_error_len != 0xFF) {
                kha_stack_stats.rx_error_len++;
            }
            continue;
        }

        if (kha_stack_rx_buf_state == KHA_STATE_MSG_DECODE_LENGTH) {
            if (kha_stack_rx_buf_idx < kha_stack_rx_buf[0]) {
                kha_stack_rx_buf[kha_stack_rx_buf_idx] = in;
                kha_stack_rx_buf_idx++;
            }
            if (kha_stack_rx_buf_idx == kha_stack_rx_buf[0]) {
                kha_stack_rx_buf_state = KHA_STATE_MSG_DECODE_IDLE;

                uint8_t crc_rx = kha_stack_rx_buf[kha_stack_rx_buf_idx - 1];
                uint8_t crc_calc = kha_stack_crc8(kha_stack_rx_buf, kha_stack_rx_buf_idx - 2);
                if (crc_rx != crc_calc) {
                    kha_stack_log(KHA_STACK_LOG_RX_DECODE_CRC_ERROR, crc_rx, crc_calc, 0x00);
                    if (kha_stack_stats.rx_error_crc != 0xFF) {
                        kha_stack_stats.rx_error_crc++;
                    }
                    continue;
                }

                if (kha_stack_stats.rx != 0xFF) {
                    kha_stack_stats.rx++;
                }

                kha_process_rx();
            }
        }
    }
}

// TX --------------------------------------------------------------------------

void kha_stack_tx_cbr_msg_all(bool(* cb)(uint8_t buf[])) {
    kha_stack_tx_cbh_msg_all = cb;
}

void kha_stack_tick() {
    kha_stack_tx_block_index++;
    if (kha_stack_tx_block_index >= (KHA_ADDR_BROADCAST_GROUP_FALLBACK * 2)) {
        kha_stack_tx_block_index = 0;
    }
}

void kha_stack_rx_detect() {
    kha_stack_tx_block_index = 0;
}

bool kha_stack_tx_add(uint8_t buf[]) {
    uint16_t i = 0;
    while (kha_stack_tx_queue[i] != 0xFF && i < KHA_STACK_QUEUE_TX_LEN) {
        i = i + kha_stack_tx_queue[i];
    }

    if (i + buf[0] > KHA_STACK_QUEUE_TX_LEN) {
        kha_stack_log(KHA_STACK_LOG_TX_BUFFER_FULL_ERROR, 0x00, 0x00, 0x00);
        if (kha_stack_stats.tx_error_full != 0xFF) {
            kha_stack_stats.tx_error_full++;
        }
        return false;
    }

    memcpy(i + kha_stack_tx_queue, buf, buf[0]);

    return true;
}

bool kha_stack_tx_create(uint8_t to, uint8_t cmd, uint8_t optlen, uint8_t opt[]) {
    if (optlen > KHA_MSG_LEN_OPT_MAX) {
        kha_stack_log(KHA_STACK_LOG_TX_ENCODE_OPT_LEN, optlen, KHA_MSG_LEN_OPT_MAX, 0x00);
        if (kha_stack_stats.tx_error_len != 0xFF) {
            kha_stack_stats.tx_error_len++;
        }
        return false;
    }

    uint8_t size = KHA_MSG_LEN_MIN + optlen;
    uint8_t buffer[size];
    buffer[0] = size;
    buffer[1] = kha_stack_dev_addr;
    buffer[2] = to;
    buffer[3] = cmd;
    for (uint8_t i = 0; i < optlen; i++) {
        buffer[4 + i] = opt[i];
    }
    buffer[4 + optlen] = kha_stack_crc8(buffer, size - 2);

    return kha_stack_tx_add(buffer);
}

void kha_stack_tx_remove(uint8_t len) {
    memcpy(kha_stack_tx_queue, kha_stack_tx_queue + len, KHA_STACK_QUEUE_TX_LEN - len);
    memset(kha_stack_tx_queue + KHA_STACK_QUEUE_TX_LEN - len, 0xFF, len);
}

bool kha_stack_process_tx() {
    uint8_t len = kha_stack_tx_queue[0];
    if (len == 0xFF) {
        return false;
    }

    uint8_t buf[KHA_MSG_LEN_MAX];
    memcpy(buf, kha_stack_tx_queue, kha_stack_tx_queue[0]);

    if (!kha_stack_tx_enable) {
        return false;
    }

    if (kha_stack_stats.tx != 0xFF) {
        kha_stack_stats.tx++;
    }

    kha_stack_tx_remove(len);

    if (kha_stack_tx_cbh_msg_all != NULL) {
        if ((*kha_stack_tx_cbh_msg_all)(buf)) {
            kha_stack_tx_remove(len);
            return true;
        }
    }

    //if (buf[2] == 0x01) { // localhost?
    //    kha_stack_process_cmd(buf);
    //    return true;
    //}

    if (!(buf[3] >= KHA_CMD_MANAGEMENT_BOOT_FW_WRITE && buf[3] <= KHA_CMD_MANAGEMENT_BOOT_WIPE_FLASH)) {
        while (kha_stack_tx_block_index != (2 * kha_stack_dev_addr)) {
            asm("wdr");
        }
    }

    // TODO Should we rx process all tx messages?

    while (!UART0_IsTxReady()) {
    }
    USART0_Write(KHA_MSG_START);

    while (!UART0_IsTxReady()) {
    }
    USART0_Write(KHA_MSG_START_CONFIRM);

    for (uint8_t i = 0; i < buf[0]; i++) {
        while (!UART0_IsTxReady()) {
        }
        USART0_Write(buf[i]);

        if (buf[i] == KHA_MSG_START) {
            while (!UART0_IsTxReady()) {
            }
            USART0_Write(KHA_MSG_START_ESCAPE);
        }
    }

    kha_stack_tx_block_index = 0;

    return true;
}

// PROCESS ---------------------------------------------------------------------

void kha_stack_process_rx_tx() {
    kha_stack_process_rx();
    while (kha_stack_process_tx()) {
    }
}

// INIT ------------------------------------------------------------------------

void kha_stack_init_register(uint8_t register_len, uint8_t preset_len) {
    uint8_t register_combined_len = 0;

    if (preset_len > KHA_STACK_EEPROM_REGISTER_PRESET_WIDTH_MAX) {
        preset_len = 0;
        kha_stack_register_preset_start = 0;
        kha_stack_register_preset_bytes = 0;
    } else {
        kha_stack_register_preset_bytes = preset_len;
    }

    register_combined_len = register_len + ((preset_len + 1) * KHA_PRESET_MAX);

    if (register_combined_len > KHA_STACK_EEPROM_REGISTER_LEN) {
        kha_stack_register_len = 0;
        kha_stack_register_preset_start = 0;
        kha_stack_register_preset_bytes = 0;
        kha_stack_log(KHA_STACK_LOG_REGISTER_SETSIZE_ERROR, register_combined_len, KHA_STACK_EEPROM_REGISTER_LEN, 0x00);
    } else {
        kha_stack_register_len = register_combined_len;
        kha_stack_register_preset_start = register_len;
    }

    kha_stack_log(KHA_STACK_LOG_REGISTER_SETSIZE, kha_stack_register_len, 0x00, 0x00);
    kha_stack_register_load();
}

void kha_stack_init_userrow() {
    // USERROW
    // <board type> <board rev> <unicast> <multicast> <config> <custom>
    //  2            1           2         2           1       32-8 = 24

    uint8_t tmp;

    for (uint8_t i = 0; i < KHA_STACK_USERROW_LEN; i++) {
        kha_stack_userrow[i] = SIGROW_Read(KHA_STACK_USERROW_ADDR_START + i);
    }

    // BOARD TYPE --------------------------------------------------------------

    tmp = kha_stack_userrow[KHA_STACK_USERROW_BOARD_TYPE_OFFSET];
    if (tmp == KHA_BOARD_TYPE_NONE || tmp == KHA_BOARD_TYPE_ALL || (tmp < KHA_BOARD_TYPE_MIN && tmp > KHA_BOARD_TYPE_MAX)) {
        kha_stack_board_type = KHA_BOARD_TYPE_FALLBACK;
        kha_stack_log(KHA_STACK_LOG_IDENT_BOARD_TYPE_ERROR, tmp, 0x00, 0x00);
    } else {
        kha_stack_board_type = tmp;
    }
    kha_stack_log(KHA_STACK_LOG_IDENT_BOARD_TYPE_SET, kha_stack_board_type, 0x00, 0x00);

    // BOARD REV ---------------------------------------------------------------

    tmp = kha_stack_userrow[KHA_STACK_USERROW_BOARD_REV_OFFSET];
    if (tmp == KHA_BOARD_REV_NONE || tmp == KHA_BOARD_REV_ALL || tmp < KHA_BOARD_REV_MIN || tmp > KHA_BOARD_REV_MAX) {
        kha_stack_board_rev = KHA_BOARD_REV_FALLBACK;
        kha_stack_log(KHA_STACK_LOG_IDENT_BOARD_REV_ERROR, tmp, 0x00, 0x00);
    } else {
        kha_stack_board_rev = tmp;
    }
    kha_stack_log(KHA_STACK_LOG_IDENT_BOARD_REV_SET, kha_stack_board_rev, 0x00, 0x00);

    // ADDR DEVICE -------------------------------------------------------------

    tmp = kha_stack_userrow[KHA_STACK_USERROW_ADDR_DEVICE_OFFSET];
    if (tmp == KHA_ADDR_NONE || tmp == KHA_ADDR_BROADCAST || (tmp >= KHA_ADDR_BROADCAST_GROUP_MIN && tmp <= KHA_ADDR_BROADCAST_GROUP_MAX)) {
        kha_stack_dev_addr = KHA_ADDR_UNICAST_FALLBACK;
        kha_stack_log(KHA_STACK_LOG_IDENT_DEVICE_ADDRESS_ERROR, tmp, 0x00, 0x00);
    } else {
        kha_stack_dev_addr = tmp;
    }
    kha_stack_log(KHA_STACK_LOG_IDENT_DEVICE_ADDRESS_SET, kha_stack_dev_addr, 0x00, 0x00);

    // ADDR GROUP --------------------------------------------------------------

    tmp = kha_stack_userrow[KHA_STACK_USERROW_ADDR_GROUP_OFFSET];
    if ((tmp != KHA_ADDR_BROADCAST_GROUP_NONE) && (tmp < KHA_ADDR_BROADCAST_GROUP_MIN || tmp > KHA_ADDR_BROADCAST_GROUP_MAX)) {
        kha_stack_log(KHA_STACK_LOG_IDENT_DEVICE_GROUP_ERROR, tmp, 0x00, 0x00);
        tmp = KHA_ADDR_BROADCAST_GROUP_FALLBACK;
    }

    kha_stack_dev_group = tmp;
    kha_stack_log(KHA_STACK_LOG_IDENT_DEVICE_GROUP_SET, kha_stack_dev_group, 0x00, 0x00);
}

void kha_stack_init_version_and_crc(uint32_t version) {
    uint8_t offset = kha_stack_bootloader ? KHA_STACK_EEPROM_VERSION_BOOT_OFFSET : KHA_STACK_EEPROM_VERSION_APP_OFFSET;

    for (uint8_t i = 0; i < 4; i++) {
        while (EEPROM_IsBusy()) {
        }
        EEPROM_Write(KHA_STACK_EEPROM_ADDR_START + offset + i, (version >> ((3 - i) * 8) & 0xFF));
    }

    kha_stack_crc32_flash_and_store(KHA_STACK_FLASH_BOOT_START, KHA_STACK_FLASH_BOOT_END, KHA_STACK_EEPROM_CRC_BOOT_OFFSET);
    kha_stack_crc32_flash_and_store(KHA_STACK_FLASH_APP_START, KHA_STACK_FLASH_APP_END, KHA_STACK_EEPROM_CRC_APP_OFFSET);
}

void manual_interaction_occured(bool ui, bool preset) {
    if (ui) {
        kha_stack_ui_enable();
    }
    if (preset) {
        kha_stack_preset_set(KHA_PRESET_NONE, true);
    }
}

void kha_stack_init(bool bootloader, uint8_t register_size, uint8_t preset_size, uint32_t version) {
    memset(kha_stack_tx_queue, 0xFF, KHA_STACK_QUEUE_TX_LEN);

    kha_stack_bootloader = bootloader;

    kha_stack_log(KHA_STACK_LOG_INITIALIZATION_STARTED, 0x00, 0x00, 0x00);

    kha_stack_init_userrow();
    kha_stack_init_register(register_size, preset_size);
    kha_stack_init_version_and_crc(version);

    RTC_SetPITIsrCallback(kha_stack_tick);
    IO_PA1_SetInterruptHandler(kha_stack_rx_detect);
    IO_PA1_EnableInterruptForFallingEdge();

    DELAY_milliseconds(kha_stack_dev_addr * 2);

    kha_stack_send_ident_or_up(KHA_ADDR_NONE, KHA_CMD_DEVICE_UP);
    kha_stack_log(KHA_STACK_LOG_INITIALIZATION_COMPLETED, 0x00, 0x00, 0x00);
}
