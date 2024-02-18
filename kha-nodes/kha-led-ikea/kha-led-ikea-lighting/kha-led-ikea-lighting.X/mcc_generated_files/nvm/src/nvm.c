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

#include "../../system/ccp.h"
#include "../nvm.h"

void NVM_Initialize(void)
{ 
    //No initialization needed
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
