/**
 * RTC Generated Driver API Header File.
 *
 * @file rtc.h
 *
 * @defgroup rtc RTC
 *
 * @brief This file contains the API prototypes of the RTC driver.
 *
 * @version RTC Driver Version 2.1.0
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


#ifndef RTCDRIVER_H
#define RTCDRIVER_H

#include "../system/utils/compiler.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup rtc
 * @typedef void RTC_cb_t
 * @brief Function pointer to callback function called by the RTC. The default value is set to NULL which means that no callback function will be used.
 */ 
typedef void (*RTC_cb_t)(void);
/**
 * @ingroup rtc
 * @brief Interrupt Service Routine (ISR) callback function to be called if Overflow (OVF) Interrupt flag is set.
 * @param RTC_cb_t cb - Callback function to be called on Overflow event.
 * @return None.
 */ 
void RTC_SetOVFIsrCallback(RTC_cb_t cb);
/**
 * @ingroup rtc
 * @brief ISR callback function to be called if Compare (CMP) match Interrupt flag is set.
 * @param RTC_cb_t cb - Callback function to be called on compare match event.
 * @return None.
 */ 
void RTC_SetCMPIsrCallback(RTC_cb_t cb);
/**
 * @ingroup rtc
 * @brief ISR callback function to be called if the Periodic Interrupt Timer (PIT) Interrupt flag is set.
 * @param RTC_cb_t cb - Callback function to be called on periodic interrupt event.
 * @return None.
 */ 
void RTC_SetPITIsrCallback(RTC_cb_t cb);
/**
 * @ingroup rtc
 * @brief Initializes the RTC module.
 * @param None.
 * @retval 0 - the RTC initialization is successful
 * @retval 1 - the RTC initialization is not successful
 */ 
int8_t RTC_Initialize(void);
/**
 * @ingroup rtc
 * @brief Starts the counter register for the RTC module.
 * @param None.
 * @return None.
 */
void RTC_Start(void);
/**
 * @ingroup rtc
 * @brief Stops the counter register for the RTC module.
 * @param None.
 * @return None.
 */
void RTC_Stop(void);
/**
 * @ingroup rtc
 * @brief Writes a value to the Counter register of the RTC module.
 * @param uint16_t timerVal - Value to be written to the Counter register of the RTC.
 * @return None.
 */
void RTC_WriteCounter(uint16_t timerVal);
/**
 * @ingroup rtc
 * @brief Writes a value to the Period register of the RTC module.
 * @param uint16_t timerVal - Value to be written to the Period register of the RTC.
 * @return None.
 */
void RTC_WritePeriod(uint16_t timerVal);
/**
 * @ingroup rtc
 * @brief Returns the counter value from the Counter register.
 * @param None.
 * @return uint16_t - Value of the Counter register.
 */
uint16_t RTC_ReadCounter(void);
/**
 * @ingroup rtc
 * @brief Returns the value of the Period register.
 * @param None.
 * @return uint16_t - Value of the Period register.
 */
uint16_t RTC_ReadPeriod(void);
/**
 * @ingroup rtc
 * @brief Enables the Compare (CMP) Interrupt.
 * @param None.
 * @return None.
 */
void RTC_EnableCMPInterrupt(void);
/**
 * @ingroup rtc
 * @brief Disables the CMP Interrupt.
 * @param None.
 * @return None.
 */
void RTC_DisableCMPInterrupt(void);
/**
 * @ingroup rtc
 * @brief Enables the Overflow (OVF) Interrupt. 
 * @param None.
 * @return None.
 */
void RTC_EnableOVFInterrupt(void);
/**
 * @ingroup rtc
 * @brief Disables the OVF Interrupt for the RTC module.
 * @param None.
 * @return None.
 */
void RTC_DisableOVFInterrupt(void);
/**
 * @ingroup rtc
 * @brief Enables the Periodic Interrupt Timer (PIT) interrupt for the RTC module. 
 * @param None.
 * @return None.
 */
void RTC_EnablePITInterrupt(void);
/**
 * @ingroup rtc
 * @brief Disables the PIT Interrupt for the RTC module.
 * @param None.
 * @return None.
 */
void RTC_DisablePITInterrupt(void);
/**
 * @ingroup rtc
 * @brief Clears the OVF Interrupt flag.
 * @param None.
 * @return None.
 */
void RTC_ClearOVFInterruptFlag(void);
/**
 * @ingroup rtc
 * @brief Checks if Overflow interrupt has occurred.
 * @param None.
 * @retval True - Interrupt is enabled.
 * @retval False - Interrupt is disabled.
 */
bool RTC_IsOVFInterruptEnabled(void);
/**
 * @ingroup rtc
 * @brief Writes a value to the CMP register of the RTC module.
 * @param uint16_t value - Value to be written to the CMP register of the RTC.
 * @return None.
 */
void RTC_WriteCMPRegister(uint16_t value);
/**
 * @ingroup rtc
 * @brief Returns the value from the CMP register.
 * @param None.
 * @return uint16_t - Value of the Compare register.
 */
uint16_t RTC_ReadCMPRegister(void);


#endif /* RTCDRIVER_H */

/** @}*/