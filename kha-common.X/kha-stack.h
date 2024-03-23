#ifndef KHA_STACK_H
#define	KHA_STACK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/pgmspace.h>
#define printf(str, ...) printf_P(PSTR(str), ##__VA_ARGS__)

#define KHA_STACK_QUEUE_TX_LEN (KHA_MSG_LEN_MAX + 1) * 10

#define KHA_STACK_EEPROM_ADDR_START 0x1400
#define KHA_STACK_EEPROM_REGISTER_LEN (0xFF - 17) // 4:boot_version 4:boot_cec 4:app_version 4:app_crc 1:OK
#define KHA_STACK_EEPROM_REGISTER_PRESET_WIDTH_MAX 8
#define KHA_STACK_EEPROM_REGISTER_PRESET_BUFFER_LEN (KHA_STACK_EEPROM_REGISTER_PRESET_WIDTH_MAX) * KHA_PRESET_MAX

#define KHA_STACK_EEPROM_MAGIC_OK 0x42
#define KHA_STACK_EEPROM_MAGIC_OFFSET 0xFF
#define KHA_STACK_EEPROM_CRC_APP_OFFSET 0xFB
#define KHA_STACK_EEPROM_VERSION_APP_OFFSET 0xF7
#define KHA_STACK_EEPROM_CRC_BOOT_OFFSET 0xF3
#define KHA_STACK_EEPROM_VERSION_BOOT_OFFSET 0xEF

#define KHA_STACK_USERROW_ADDR_START 0x1080
#define KHA_STACK_USERROW_LEN 32
#define KHA_STACK_USERROW_BOARD_TYPE_OFFSET 0
#define KHA_STACK_USERROW_BOARD_REV_OFFSET 1
#define KHA_STACK_USERROW_ADDR_DEVICE_OFFSET 2
#define KHA_STACK_USERROW_ADDR_GROUP_OFFSET 3
#define KHA_STACK_USERROW_DATA_OFFSET 4

#define KHA_STACK_FLASH_BOOT_START 0x0000
#define KHA_STACK_FLASH_BOOT_END 0x4000
#define KHA_STACK_FLASH_APP_START 0x4000
#define KHA_STACK_FLASH_APP_END 0xFFFF

#define KHA_STACK_PRESET_PC 0x05
#define KHA_STACK_PRESET_TINKER 0x04
#define KHA_STACK_PRESET_TV 0x03
#define KHA_STACK_PRESET_PARTY 0x02

#define KHA_STACK_LOG_HUMAN 0x00

#define KHA_STACK_LOG_INITIALIZATION_STARTED 0x10
#define KHA_STACK_LOG_INITIALIZATION_COMPLETED 0x11

#define KHA_STACK_LOG_IDENT_DEVICE_ADDRESS_SET 0x20
#define KHA_STACK_LOG_IDENT_DEVICE_ADDRESS_ERROR 0x21
#define KHA_STACK_LOG_IDENT_DEVICE_GROUP_SET 0x22
#define KHA_STACK_LOG_IDENT_DEVICE_GROUP_ERROR 0x23
#define KHA_STACK_LOG_IDENT_BOARD_TYPE_SET 0x24
#define KHA_STACK_LOG_IDENT_BOARD_TYPE_ERROR 0x25
#define KHA_STACK_LOG_IDENT_BOARD_REV_SET 0x26
#define KHA_STACK_LOG_IDENT_BOARD_REV_ERROR 0x27
#define KHA_STACK_LOG_IDENT_USERROW_ADDR_ERROR 0x28

#define KHA_STACK_LOG_REGISTER_SETSIZE 0x30
#define KHA_STACK_LOG_REGISTER_SETSIZE_ERROR 0x31
#define KHA_STACK_LOG_REGISTER_LOAD 0x32
#define KHA_STACK_LOG_REGISTER_LOAD_ERROR 0x33
#define KHA_STACK_LOG_REGISTER_WIPE 0x34
#define KHA_STACK_LOG_REGISTER_STORE 0x35
#define KHA_STACK_LOG_REGISTER_READ 0x36
#define KHA_STACK_LOG_REGISTER_READ_SINGLE 0x37
#define KHA_STACK_LOG_REGISTER_WRITE 0x38
#define KHA_STACK_LOG_REGISTER_WRITE_SINGLE 0x39
#define KHA_STACK_LOG_REGISTER_WRITE_CHANGED 0x3a
#define KHA_STACK_LOG_REGISTER_ADDR_ERROR 0x3b
#define KHA_STACK_LOG_REGISTER_LEN_ERROR 0x3c
#define KHA_STACK_LOG_REGISTER_ADDR_LEN_ERROR 0x3d

#define KHA_STACK_LOG_RX 0x40
#define KHA_STACK_LOG_RX_DECODE_START_UNESCAPED_ERROR 0x41
#define KHA_STACK_LOG_RX_DECODE_START_MISSING_ERROR 0x42
#define KHA_STACK_LOG_RX_DECODE_LEN_ERROR 0x43
#define KHA_STACK_LOG_RX_DECODE_CRC_ERROR 0x44

#define KHA_STACK_LOG_TX 0x50
#define KHA_STACK_LOG_TX_BUFFER_FULL_ERROR 0x51
#define KHA_STACK_LOG_TX_ENCODE_OPT_LEN 0x52
#define KHA_STACK_LOG_TX_ENABLE 0x53
#define KHA_STACK_LOG_TX_DISABLE 0x54

#define KHA_STACK_LOG_CMD_PARAMETERS_ERROR 0x60
#define KHA_STACK_LOG_CMD_SENDER_IGNORE 0x61
#define KHA_STACK_LOG_CMD_BOOTLOADER_IGNORE 0x62
#define KHA_STACK_LOG_CMD_WRITE_BROADCAST 0x63

#define KHA_STACK_LOG_DEVICE_DEBUG_ENABLE 0x81
#define KHA_STACK_LOG_DEVICE_DEBUG_DISABLE 0x82
#define KHA_STACK_LOG_DEVICE_STATS_CLEAR 0x83


#define KHA_STACK_CRC_LOOKUP 0

    typedef enum {
        KHA_STACK_MSG_ADDR_TYPE_NONE,
        KHA_STACK_MSG_ADDR_TYPE_UNICAST,
        KHA_STACK_MSG_ADDR_TYPE_UNICAST_FALLBACK,
        KHA_STACK_MSG_ADDR_TYPE_MULTICAST,
        KHA_STACK_MSG_ADDR_TYPE_MULTICAST_FALLBACK,
        KHA_STACK_MSG_ADDR_TYPE_BROADCAST
    } KHA_STACK_MSG_ADDR_TYPE_t;

    void kha_stack_cbr_log(void (* cb)(uint8_t id, uint8_t val1, uint8_t val2, uint8_t val3));

    void kha_stack_ui_cbr_change(void (* cb)(void));
    bool kha_stack_ui_enabled();
    void kha_stack_ui_enable();
    void kha_stack_ui_disable();

    uint8_t kha_stack_crc8(uint8_t* data, size_t len);

    void kha_stack_stats_clear();

    KHA_STACK_MSG_ADDR_TYPE_t kha_stack_msg_addr_type(uint8_t to);
    bool kha_stack_msg_match(uint8_t to);
    bool kha_stack_board_match(uint8_t type, uint8_t rev);

    uint8_t kha_stack_device_address_get();
    uint8_t kha_stack_device_group_get();
    uint8_t kha_stack_board_type_get();
    uint8_t kha_stack_board_rev_get();

    uint8_t kha_stack_userrow_data(uint8_t addr);

    void kha_stack_app_led_animation_cbr(void (* cb)(uint8_t swe[3]));
    void kha_stack_app_led_hsi_cbr(void (* cb)(uint8_t hsi[3]));

    void kha_stack_register_cbr_change(uint8_t(* cb)(uint8_t addr, uint8_t value));
    uint8_t kha_stack_register_get(uint8_t addr);
    bool kha_stack_register_set(uint8_t addr, uint8_t val, bool force_callback);

    void kha_stack_preset_cbr_change(void(* cb)(uint8_t preset, bool enabled, uint8_t addr));
    uint8_t kha_stack_preset();
    void kha_stack_preset_set(uint8_t preset, bool notify);

    void kha_stack_rx_cbr_msg_all(bool (* cb)(uint8_t buf[]));
    void kha_stack_rx_cbr_msg_all_post(bool (* cb)(uint8_t buf[]));
    void kha_stack_rx_cbr_msg_matched(bool (* cb)(uint8_t buf[]));
    void kha_stack_rx_cbr_msg_unprocessed(bool (* cb)(uint8_t buf[]));

    void kha_stack_tx_cbr_msg_all(bool (* cb)(uint8_t buf[]));
    bool kha_stack_tx_create(uint8_t to, uint8_t cmd, uint8_t optlen, uint8_t opt[]);

    void kha_stack_manual_interaction_occured(bool ui, bool preset);

    void kha_stack_process_rx_tx();

    void kha_stack_init(bool is_boot, uint8_t register_size, uint8_t preset_size, uint32_t version);

#ifdef	__cplusplus
}
#endif

#endif
