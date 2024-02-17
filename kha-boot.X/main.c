#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "../kha-common.X/kha-constants.h"
#include "../kha-common.X/kha-stack.h"
#include "kha-version.h"
#include "mcc_generated_files/reset/rstctrl.h"

// ---

LOCKBITS = 0xA33A3AA3; // {KEY=RWLOCK}

// ---

#define REGISTER_SIZE 0
#define REGISTER_PRESET_WIDTH 0

#define PAGE_SIZE 512UL
#define PAGE_START 32UL
#define PAGE_END 128UL

#define PAGE_PARTS 64

#define BOOTLOADER_EXIT_DELAY_S 6

// ---

static bool bootloader_exit = true;

static uint8_t buf_page[PAGE_SIZE];

// ---

void eeprom_wipe() {
    while (EEPROM_IsBusy()) {
    }
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_EECHER_gc);

    while (EEPROM_IsBusy()) {
    }
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_NONE_gc);
}

bool flash_wipe() {
    bool success = true;

    for (uint16_t page = PAGE_START; page < PAGE_END; page++) {
        while (FLASH_IsBusy()) {
        }
        if (FLASH_PageErase(page * PAGE_SIZE) != NVM_OK) {
            success = false;
        }
    }

    return success;
}

bool flash_write(uint8_t page) {
    bool success = true;

    while (FLASH_IsBusy()) {
    }
    if (FLASH_RowWrite(page * PAGE_SIZE, buf_page) != NVM_OK) {
        success = false;
    }
    memset(buf_page, 0xFF, PAGE_SIZE);

    return success;
}

bool process_msg(uint8_t buf[]) {
    uint8_t size = buf[0];
    uint8_t from = buf[1];
    //    uint8_t to = buf[2];
    uint8_t cmd = buf[3];
    uint8_t optlen = size - KHA_MSG_LEN_MIN;
    uint8_t opt[optlen];

    for (uint8_t i = 0; i < optlen; i++) {
        opt[i] = buf[4 + i];
    }

    uint8_t board = 0x00;
    uint8_t rev = 0x00;
    if (optlen >= 2) {
        board = opt[0];
        rev = opt[1];
    }

    uint8_t cmd_reply[1] = {cmd};

    if (cmd == KHA_CMD_MANAGEMENT_BOOT_NOT_EXIT) {
        if (optlen != 2) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }
        if (!kha_stack_board_match(board, rev)) {
            return true;
        }

        bootloader_exit = false;
        return true;
    }

    if (cmd == KHA_CMD_MANAGEMENT_BOOT_WIPE_FLASH) {
        if (optlen != 2) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }
        if (!kha_stack_board_match(board, rev)) {
            return true;
        }

        if (!flash_wipe()) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
        }
        return true;
    }

    if (cmd == KHA_CMD_MANAGEMENT_BOOT_WIPE_EEPROM) {
        if (optlen != 2) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }
        if (!kha_stack_board_match(board, rev)) {
            return true;
        }

        eeprom_wipe();
        return true;
    }


    if (cmd == KHA_CMD_MANAGEMENT_BOOT_FW_DATA) {
        if (optlen != PAGE_PARTS + 3) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }
        if (!kha_stack_board_match(board, rev)) {
            return true;
        }

        uint8_t part = opt[2];
        uint8_t part_max = (PAGE_SIZE / PAGE_PARTS) - 1;
        if (part > part_max) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }

        memcpy(buf_page + (part * PAGE_PARTS), opt + 3, PAGE_PARTS);
        return true;
    }

    if (cmd == KHA_CMD_MANAGEMENT_BOOT_FW_WRITE) {
        if (optlen != 3) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }
        if (!kha_stack_board_match(board, rev)) {
            return true;
        }

        uint8_t page = opt[2];
        if (page < PAGE_START || page > PAGE_END) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }

        if (!flash_write(page)) {
            kha_stack_tx_create(from, KHA_CMD_MANAGEMENT_BOOT_CMD_ERROR, 1, cmd_reply);
            return true;
        }

        return true;
    }

    return false;
}

int main(void) {
    SYSTEM_Initialize();

    memset(buf_page, 0xFF, PAGE_SIZE);

    sei();

    kha_stack_rx_cbr_msg_matched(process_msg);
    kha_stack_init(true, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    uint16_t countdown = BOOTLOADER_EXIT_DELAY_S * 10;
    while (countdown > 0) {
        kha_stack_process_rx_tx();
        if (!bootloader_exit) {
            break;
        }
        asm("wdr");
        DELAY_milliseconds(100);
        countdown--;
    }

    if (bootloader_exit) {
        cli();
        void (*app)(void) = (PAGE_START * PAGE_SIZE) / 2;
        app();
    }

    while (true) {        
        kha_stack_process_rx_tx();
        asm("wdr");
    }
}
