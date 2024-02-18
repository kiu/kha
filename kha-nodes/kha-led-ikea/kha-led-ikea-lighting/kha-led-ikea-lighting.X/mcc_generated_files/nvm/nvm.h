/**
 * 
 * @file nvm.h
 *
 * @defgroup nvm_driver  Non-Volatile Memory
 *
 * @brief This file contains API prototypes and other data types for the Non-Volatile Memory (NVM) driver.
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

#ifndef NVM_H
#define NVM_H

#include "../system/utils/compiler.h"

/**
 * @ingroup nvm_driver
 * @def SERIAL_NUMBER_SIZE
 * Contains the serial number length in bytes.
 */
#define SERIAL_NUMBER_SIZE    (10U)


/**
 * @ingroup nvm_driver
 * @brief Data type for the Signature Row data.
 */
typedef uint8_t sigrow_data_t;
/**
 * @ingroup nvm_driver
 * @brief Datatype for Signature Row address.
 */
typedef uint16_t sigrow_address_t;
/**
 * @ingroup nvm_driver
 * @brief Data type for the Device ID data.
 */
typedef uint32_t device_id_data_t;

/**
 * @ingroup nvm_driver
 * @brief Initializes the NVM driver.
 * @param None.
 * @return None.
 */
void NVM_Initialize(void);


/**
 * @ingroup nvm_driver
 * @brief Reads one Signature Row byte.
 * @param [in] address - Address of the Signature Row byte to be read.
 * @return Signature Row data. 
 */
sigrow_data_t SIGROW_Read(sigrow_address_t address);

/**
 * @ingroup nvm_driver
 * @brief Reads the Device ID.
 * @param [in] address - Starting address of the Device ID.
 * @return Device ID.  
 */
device_id_data_t SIGROW_DeviceIDRead(sigrow_address_t address);

/**
 * @ingroup nvm_driver
 * @brief Reads the serial number.
 *      The size of the buffer must be equal to the size of the serial number.
 * @param [in] address - Starting address of the serial number. 
 * @param [out] *serialNumber - Buffer to hold the serial number. 
 * @return None.
 */
void SIGROW_SerialNumberRead(sigrow_address_t address, sigrow_data_t *serialNumber);

#endif //NVM_H