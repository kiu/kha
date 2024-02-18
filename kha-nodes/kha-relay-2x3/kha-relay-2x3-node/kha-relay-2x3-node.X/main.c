#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "mcc_generated_files/timer/tca0.h"
#include "../../../../kha-common.X/kha-constants.h"
#include "../../../../kha-common.X/kha-stack.h"
#include "kha-version.h"

// ---

#define SOCKET_AMOUNT 6

#define REGISTER_SIZE SOCKET_AMOUNT * 2
#define REGISTER_PRESET_WIDTH 0

#define POWER_OFF_STOP 0xFFFF

// ---

static volatile bool socket_enabled_next[SOCKET_AMOUNT] = {false, false, false, false, false, false};
static volatile bool socket_enabled_off_next[SOCKET_AMOUNT] = {false, false, false, false, false, false};
static volatile uint16_t socket_off_timer[SOCKET_AMOUNT];

// ---

void tick() {
    for (uint8_t socket = 0; socket < SOCKET_AMOUNT; socket++) {
        if (socket_off_timer[socket] != POWER_OFF_STOP) {
            if (socket_off_timer[socket] > 0) {
                socket_off_timer[socket]--;
            } else {
                socket_off_timer[socket] = POWER_OFF_STOP;
                socket_enabled_off_next[socket] = true;
            }
        }
    }
}

void change(uint8_t socket, uint8_t enabled, bool notify) {
    if (!kha_stack_register_set(socket, enabled, false)) {
        return;
    }

    if (notify) {
        uint8_t buf2[2] = {socket, enabled};
        kha_stack_tx_create(kha_stack_device_address_get(), KHA_CMD_REGISTER_WRITE_REQUEST_NO_REPLY, 2, buf2);
    }
}

// ---

uint8_t register_change(uint8_t addr, uint8_t value) {
    // state
    if (addr >= 0 && addr < SOCKET_AMOUNT) {
        if (value > 1) {
            value = 0;
        }

        socket_enabled_next[addr] = value;
        socket_enabled_off_next[addr] = false;

        if (value) {
            uint8_t timer_value = kha_stack_register_get(SOCKET_AMOUNT + addr);
            if (timer_value != 0x00) {
                socket_off_timer[addr] = timer_value * 60;
            } else {
                socket_off_timer[addr] = POWER_OFF_STOP;
            }
        } else {
            socket_off_timer[addr] = POWER_OFF_STOP;
        }

        if (addr == 0) {
            if (value) {
                IO_R00_SetHigh();
            } else {
                IO_R00_SetLow();
            }
        }
        if (addr == 1) {
            if (value) {
                IO_R01_SetHigh();
            } else {
                IO_R01_SetLow();
            }
        }
        if (addr == 2) {
            if (value) {
                IO_R02_SetHigh();
            } else {
                IO_R02_SetLow();
            }
        }
        if (addr == 3) {
            if (value) {
                IO_R03_SetHigh();
            } else {
                IO_R03_SetLow();
            }
        }
        if (addr == 4) {
            if (value) {
                IO_R04_SetHigh();
            } else {
                IO_R04_SetLow();
            }
        }
        if (addr == 5) {
            if (value) {
                IO_R05_SetHigh();
            } else {
                IO_R05_SetLow();
            }
        }

    }

    return value;
}

int main(void) {
    SYSTEM_Initialize();

    sei();

    kha_stack_register_cbr_change(register_change);
    kha_stack_init(false, REGISTER_SIZE, REGISTER_PRESET_WIDTH, KHA_VERSION);

    TCA0_Compare0CallbackRegister(tick);

    while (1) {
        for (uint8_t socket = 0; socket < SOCKET_AMOUNT; socket++) {
            if (socket_enabled_off_next[socket]) {
                socket_enabled_off_next[socket] = false;
                change(socket, false, true);
            }
            change(socket, socket_enabled_next[socket], false);
        }

        kha_stack_process_rx_tx();
        asm("wdr");
    }
}