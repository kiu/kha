/**
 *
 * @file nvm.c
 *
 * @ingroup nvm_driver
 *
 * @brief Contains the implementation file for the NVM driver.
 *
 * @version NVM Driver Version 3.0.0
 */
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <avr/pgmspace.h>
#include "../../system/ccp.h"
#include "../nvm.h"

void NVM_Initialize(void)
{    
    NVM_StatusClear();  
    //APPCODEWP enabled; APPDATAWP enabled; BOOTRP disabled; FLMAP SECTION0; FLMAPLOCK disabled; 
    NVMCTRL.CTRLB = 0x5;
}

nvm_status_t NVM_StatusGet(void)
{
    return (((NVMCTRL.STATUS & NVMCTRL_ERROR_gm) != 0) ? NVM_ERROR : NVM_OK);
}

void NVM_StatusClear(void)
{
    NVMCTRL.STATUS &= ~NVMCTRL_ERROR_gm;
}

static void FLASH_SpmWriteWord(flash_address_t address, uint16_t data)
{
    __asm__ __volatile__(
                         "push r0\n\t" /* back up R0*/\
                         "movw r0, %A1\n\t" /* update R0,R1 pair with word*/\
                         "movw r30, %A0\n\t" /* update R30,R31 pair with address[Byte1,Byte0]*/\
                         "spm \n\t" /* spm */\
                         "clr r1\n\t" /* R1 is always assumed to be zero by the compiler. Resetting R1 to zero*/\
                         "pop r0 \n\t" /* restore R0*/\
                         :                                                      \
                         : "r" ((uint32_t) (address)), "r" ((uint16_t) (data))  \
                         : "r30", "r31" /* Clobber R30, R31 to indicate they are used here*/
                         );
}

flash_data_t FLASH_Read(flash_address_t address)
{
    return pgm_read_byte_near(address);
}

nvm_status_t FLASH_Write(flash_address_t address, uint16_t data)
{
    //Write the flash page
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_FLWR_gc);

    //Write data to the page buffer
    FLASH_SpmWriteWord(address, data);

    //Clear the current command
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_NONE_gc);

    return (((NVMCTRL.STATUS & NVMCTRL_ERROR_gm) != 0) ? NVM_ERROR : NVM_OK);
}

nvm_status_t FLASH_RowWrite(flash_address_t address, flash_data_t *dataBuffer)
{
    uint16_t dataWord;

    //Write the flash page
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_FLWR_gc);

    //Write data to the page buffer, one word at a time
    for (uint16_t i = 0; i < PROGMEM_PAGE_SIZE; i = i + 2U)
    {
	    //Access wordwise data from buffer
        dataWord = (uint16_t) (dataBuffer[i] | (dataBuffer[i+1U] << 8U));     
        FLASH_SpmWriteWord(address + (uint32_t) i, dataWord);
    }

    //Clear the current command
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_NONE_gc);

    return (((NVMCTRL.STATUS & NVMCTRL_ERROR_gm) != 0) ? NVM_ERROR : NVM_OK);
}

nvm_status_t FLASH_PageErase(flash_address_t address)
{
    //Erase the flash page
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_FLPER_gc);

    //Dummy write to start erase operation
    FLASH_SpmWriteWord(address, 0);

    //Clear the current command
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_NONE_gc);

    return (((NVMCTRL.STATUS & NVMCTRL_ERROR_gm) != 0) ? NVM_ERROR : NVM_OK);
}

bool FLASH_IsBusy(void)
{
        return (NVMCTRL.STATUS & NVMCTRL_FBUSY_bm);
}

flash_address_t FLASH_PageAddressGet(flash_address_t address)
{
    return (flash_address_t) (address & ((PROGMEM_SIZE - 1) ^ (PROGMEM_PAGE_SIZE - 1)));
}

uint16_t FLASH_PageOffsetGet(flash_address_t address)
{
    return (uint16_t) (address & (PROGMEM_PAGE_SIZE - 1));
}

eeprom_data_t EEPROM_Read(eeprom_address_t address)
{
    return *(eeprom_data_t *) address;
}

void EEPROM_Write(eeprom_address_t address, eeprom_data_t data)
{
    //Program the EEPROM with desired value(s)
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_EEERWR_gc);

    //Write byte to EEPROM
    *(uint8_t *) address = data;

    //Clear the current command
    ccp_write_spm((void *) &NVMCTRL.CTRLA, NVMCTRL_CMD_NONE_gc);
}

bool EEPROM_IsBusy(void)
{
    return (NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm);
}

sigrow_data_t SIGROW_Read(sigrow_address_t address)
{
    return *(sigrow_data_t *) (address);
}

device_id_data_t SIGROW_DeviceIDRead(sigrow_address_t address)
{
    device_id_data_t deviceID = 0;
    
    deviceID =  (device_id_data_t) (*(sigrow_data_t *) (address)) << 16;
    deviceID |= (device_id_data_t) (*(sigrow_data_t *) (address + 1U)) << 8;
    deviceID |= (device_id_data_t) (*(sigrow_data_t *) (address + 2U));
    
    return deviceID;
}

void SIGROW_SerialNumberRead(sigrow_address_t address, sigrow_data_t *serialNumber)
{
    uint8_t serialNumberIndex = 0;
    
    while (serialNumberIndex++ < SERIAL_NUMBER_SIZE)
    {
        *serialNumber++ = *(sigrow_data_t *) (address++);
    }
}
