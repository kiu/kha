/**
 * TCA0 Generated Driver API Header File
 *
 * @file tca0.h
 *
 * @defgroup tca0_normal TCA0 in Normal Mode
 *
 * @brief This file contains the API prototypes for the TCA0 driver in Normal (16-bit) mode.
 *
 * @version TCA0 Driver Version 2.1.2
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


#ifndef TCA0_H_INCLUDED
#define TCA0_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "../system/system.h"
#include "timer_interface.h"
#include "../system/utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup tca0_normal
 * @typedef void TCA0_cb_t
 * @brief Function pointer to the callback function called by TCA when operating in Normal mode. The default value is set to NULL which means that no callback function will be used.
 */  
typedef void (*TCA0_cb_t)(void);

/**
 * @ingroup tca0_normal
 * @brief Data type for the CMPx register.
 */
typedef uint16_t cmpx_register_value_t;

extern const struct TMR_INTERFACE TCA0_Interface;

/**
 * @ingroup tca0_normal
 * @brief Initializes the TCA.
 * @param None.
 * @return None.
 */ 
void TCA0_Initialize(void);
/**
 * @ingroup tca0_normal
 * @brief Starts the 16-bit timer/counter for the TCA.
 * @param None.
 * @return None.
 */
void TCA0_Start(void);
/**
 * @ingroup tca0_normal
 * @brief Stops the 16-bit timer/counter for the TCA.
 * @param None.
 * @return None.
 */
void TCA0_Stop(void);
/**
 * @ingroup tca0_normal
 * @brief Interrupt Service Routine (ISR) callback function register to be called if the Overflow Interrupt flag is set.
 * @param TCA0_cb_t cb - Callback function for Overflow event.
 * @return None.
 */ 
void TCA0_OverflowCallbackRegister(TCA0_cb_t cb);
/**
 * @ingroup tca0_normal
 * @brief ISR callback function to be called if the Compare 0 Match Interrupt flag is set.
 * @param TCA0_cb_t cb - Callback function for Compare 0 match event.
 * @return None.
 */ 
void TCA0_Compare0CallbackRegister(TCA0_cb_t cb);
/**
 * @ingroup tca0_normal
 * @brief ISR callback function to be called if the Compare 1 Match Interrupt flag is set.
 * @param TCA0_cb_t cb - Callback function for Compare 1 match event.
 * @return None.
 */ 
void TCA0_Compare1CallbackRegister(TCA0_cb_t cb);
/**
 * @ingroup tca0_normal
 * @brief ISR callback function to be called if the Compare 2 Match Interrupt flag is set.
 * @param TCA0_cb_t cb - Callback function for Compare 2 match event.
 * @return None.
 */ 
void TCA0_Compare2CallbackRegister(TCA0_cb_t cb);
/**
 * @ingroup tca0_normal
 * @brief Enables the 16-bit timer/counter interrupt for the TCA.
 * @param None.
 * @return None.
 */
void TCA0_EnableInterrupt(void);
/**
 * @ingroup tca0_normal
 * @brief Disables the 16-bit timer/counter interrupt for the TCA.
 * @param None.
 * @return None.
 */
void TCA0_DisableInterrupt(void);
/**
 * @ingroup tca0_normal
 * @brief Reads the 16-bit timer/counter value for the TCA.
 * @param None.
 * @return uint16_t - timer/counter value returns from the TCA0.
 */
uint16_t TCA0_Read(void);
/**
 * @ingroup tca0_normal
 * @brief Writes the timer value to load to the TCA.
 * @param uint16_t timerVal - Loading the timer value for the TCA.
 * @return None.
 */
void TCA0_Write(uint16_t timerVal);
/**
 * @ingroup tca0_normal
 * @brief Clears the Overflow Interrupt flag after the Overflow flag set.
 * @param None.
 * @return None.
 */
void TCA0_ClearOverflowInterruptFlag(void);
/**
 * @ingroup tca0_normal
 * @brief Checks the Overflow Interrupt flag status for the TCA.
 * @param None.
 * @retval True  - Overflow Interrupt flag is set.
 * @retval False - Overflow Interrupt flag is not set.
 */
bool TCA0_IsOverflowInterruptFlagSet(void);
/**
 * @ingroup tca0_normal
 * @brief Clears the Compare 0 Interrupt flag after the Compare 0 flag is set.
 * @param None.
 * @return None.
 */
void TCA0_ClearCMP0InterruptFlag(void);
/**
 * @ingroup tca0_normal
 * @brief Checks the Compare 0 Interrupt flag status for the TCA.
 * @param None.
 * @retval True  - Compare 0 Interrupt flag is set.
 * @retval False - Compare 0 Interrupt flag is not set.
 */
bool TCA0_IsCMP0InterruptFlagSet(void);
/**
 * @ingroup tca0_normal
 * @brief Clears the Compare 1 Interrupt flag after the Compare 1 flag is set.
 * @param None.
 * @return None.
 */
void TCA0_ClearCMP1InterruptFlag(void);
/**
 * @ingroup tca0_normal
 * @brief Checks the Compare 1 Interrupt flag status for the TCA.
 * @param None.
 * @retval True  - Compare 1 Interrupt flag is set.
 * @retval False - Compare 1 Interrupt flag is not set.
 */
bool TCA0_IsCMP1InterruptFlagSet(void);
/**
 * @ingroup tca0_normal
 * @brief Clears the Compare 2 Interrupt flag after the Compare 2 flag is set.
 * @param None.
 * @return None.
 */
void TCA0_ClearCMP2InterruptFlag(void);

/**
 * @ingroup tca0_normal
 * @brief Checks the Compare 2 Interrupt flag status for the TCA.
 * @param None.
 * @retval True  - Compare 2 Interrupt flag is set.
 * @retval False - Compare 2 Interrupt flag is not set.
 */
bool TCA0_IsCMP2InterruptFlagSet(void);

/**
 * @ingroup tca0_normal
 * @brief Writes the value to load to the CMP0.
 * @param count - 16-bit value to be loaded to the CMP0 register.
 * @return None.
 */
void TCA0_WaveformFreqRegCountSet(cmpx_register_value_t count);

/**
 * @ingroup tca0_normal
 * @brief Reads the 16-bit CMP0 value for the TCA.
 * @param None.
 * @return cmpx_register_value_t - 16-bit CMP0 value returns from the CMP0 register of TCA.
 */
uint16_t TCA0_WaveformFreqRegCountGet(void);

/**
 * @ingroup tca0_normal
 * @brief Writes the value to load to the CMP1.
 * @param count - 16-bit value to be loaded to the CMP1 register.
 * @return None.
 */
void TCA0_WO1OffsetRegCountSet(cmpx_register_value_t count);

/**
 * @ingroup tca0_normal
 * @brief Reads the 16-bit CMP1 value for the TCA.
 * @param None.
 * @return cmpx_register_value_t - 16-bit CMP1 value returns from the CMP0 register of TCA.
 */
uint16_t TCA0_WO1OffsetRegCountGet(void);
/**
 * @ingroup tca0_normal
 * @brief Writes the value to load to the CMP2.
 * @param count - 16-bit value to be loaded to the CMP2 register.
 * @return None.
 */
void TCA0_WO2OffsetRegCountSet(cmpx_register_value_t count);

/**
 * @ingroup tca0_normal
 * @brief Reads the 16-bit CMP2 value for the TCA.
 * @param None.
 * @return cmpx_register_value_t - 16-bit CMP2 value returns from the CMP0 register of TCA.
 */
uint16_t TCA0_WO2OffsetRegCountGet(void);




/**
 * @ingroup tca0_normal
 * @brief Returns the Count (CNT) register value for the TCA.
 * @pre Initialize the TCA before calling this API.
 * @param None.
 * @return uint16_t - CNT register value for the TCA.
 *
 */
uint16_t TCA0CounterGet(void);

/**
 * @ingroup tca0_normal
 * @brief Sets the Count (CNT) register value for the TCA.
 * @pre Initialize the TCA before calling this API.
 * @param uint16_t - value to be written to the CNT register.
 * @return uint16_t - None.
 *
 */
void TCA0CounterSet(uint16_t value);

/**
 * @ingroup tca0_normal
 * @brief Sets the Compare 0 (CMP0) register value for the TCA.
 * @pre Initialize the TCA before calling this API.
 * @param uint16_t -value to be written to the CMP0 register.
 * @return None.
 */
void TCA0_Compare0Set(uint16_t value);

/**
 * @ingroup tca0_normal
 * @brief Sets the Compare 1 (CMP1) register value for the TCA.
 * @pre Initialize the TCA before calling this API.
 * @param uint16_t -value to be written to the CMP1 register.
 * @return None.
 */
void TCA0_Compare1Set(uint16_t value);

/**
 * @ingroup tca0_normal
 * @brief Sets the Compare 2 (CMP2) register value for the TCA.
 * @pre Initialize the TCA before calling this API.
 * @param uint16_t -value to be written to the CMP2 register.
 * @return None.
 */
void TCA0_Compare2Set(uint16_t value);

/**
 * @ingroup tca0_normal
 * @brief Sets the Wave mode for the TCA.
 * @pre Initialize the TCA before calling this API.
 * @param TCA_SINGLE_WGMODE_t mode:
 * - @c TCA_SINGLE_WGMODE_NORMAL_gc      @c  -     Normal Mode
 * - @c TCA_SINGLE_WGMODE_FRQ_gc         @c  -     Frequency Generation Mode
 * - @c TCA_SINGLE_WGMODE_SINGLESLOPE_gc @c  -     Single Slope PWM
 * - @c TCA_SINGLE_WGMODE_DSTOP_gc       @c  -     Dual Slope PWM, overflow on TOP
 * - @c TCA_SINGLE_WGMODE_DSBOTH_gc      @c  -     Dual Slope PWM, overflow on TOP and BOTTOM
 * - @c TCA_SINGLE_WGMODE_DSBOTTOM_gc    @c  -     Dual Slope PWM, overflow on BOTTOM
 * @return None.
 *
 */
void TCA0_ModeSet(TCA_SINGLE_WGMODE_t mode);

/**
 * @ingroup tca0_normal
 * @brief Performs the tasks to be executed on timer events.
 * @param None.
 * @return None.
 */
void TCA0_Tasks(void);

#ifdef __cplusplus
}
#endif

#endif /* TCA0_H_INCLUDED */