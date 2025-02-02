/**
 * TCA0 Generated Driver API Header File
 *
 * @file tca0.h
 *
 * @defgroup tca0_normal TCA0 in Normal Mode
 *
 * @brief This file contains the API prototypes for the TCA0 driver in Normal (16-bit) mode.
 *
 * @version TCA0 Driver Version 3.0.0
 *
 * @version Package Version 7.0.0
 */
/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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
#include "../system/utils/compiler.h"
#include "./tca0_deprecated.h"

/**
 * @misradeviation{@advisory,2.5}
 * MCC Melody drivers provide macros that can be added to an application. 
 * It depends on the application whether a macro is used or not. 
 */

/**
 * @ingroup tca0_normal
 * @brief Defines the maximum count of the timer.
 */
#define TCA0_MAX_COUNT (65535U)
/**
 * @ingroup tca0_normal
 * @brief Defines the timer prescaled clock frequency in hertz.
 */
 /* cppcheck-suppress misra-c2012-2.5 */  
#define TCA0_CLOCK_FREQ (23437UL)

/**
 * @ingroup tca0_normal
 * @typedef TCA0_cb_t
 * @brief Function pointer to the callback function called by TCA while operating in Normal mode.
 *        The default value is set to NULL, which means that no callback function will be used.
 */
typedef void (*TCA0_cb_t)(void);

/**
 * @ingroup tca0_normal
 * @brief Initializes the TCA0 module.
 * @param None.
 * @return None.
 */ 
void TCA0_Initialize(void);

/**
 * @ingroup tca0_normal
 * @brief Deinitializes the TCA0 module.
 * @param None.
 * @return None.
 */
void TCA0_Deinitialize(void);

/**
 * @ingroup tca0_normal
 * @brief Starts the TCA0.
 * @param None.
 * @return None.
 */
void TCA0_Start(void);

/**
 * @ingroup tca0_normal
 * @brief Stops the TCA0.
 * @param None.
 * @return None.
 */
void TCA0_Stop(void);

/**
 * @ingroup tca0_normal
 * @brief Returns the current counter value.
 * @param None.
 * @return Current count value from the CNT register
 */
uint16_t TCA0_CounterGet(void);

/**
 * @ingroup tca0_normal
 * @brief Sets the counter value.
 * @param count - Counter value to be written to the CNT register
 * @return None.
 */
void TCA0_CounterSet(uint16_t count);

/**
 * @ingroup tca0_normal
 * @brief Returns the current period value.
 * @pre Initialize the TCA0 with TCA0__Initialize() before calling this API.
 * @param None.
 * @return Period value from the PER register
 */
uint16_t TCA0_PeriodGet(void);

/**
 * @ingroup tca0_normal
 * @brief Sets the period value.
 * @pre Initialize the TCA0 with TCA0__Initialize() before calling this API.
 * @param periodVal - Period count value written to the PER register
 * @return None.
 */
void TCA0_PeriodSet(uint16_t periodVal);

/**
 * @ingroup tca0_normal
 * @brief Sets the Compare 0 (CMP0) count value.
 * @pre Initialize the TCA0 with TCA0__Initialize() before calling this API.
 * @param value - Count value written to the CMP0 register
 * @return None.
 */
void TCA0_Compare0Set(uint16_t value);

/**
 * @ingroup tca0_normal
 * @brief Sets the Compare 1 (CMP1) count value.
 * @pre Initialize the TCA0 with TCA0__Initialize() before calling this API.
 * @param value - Count value written to the CMP1 register
 * @return None.
 */
void TCA0_Compare1Set(uint16_t value);

/**
 * @ingroup tca0_normal
 * @brief Sets the Compare 2 (CMP2) count value.
 * @pre Initialize the TCA0 with TCA0__Initialize() before calling this API.
 * @param value - Count value written to the CMP2 register
 * @return None.
 */
void TCA0_Compare2Set(uint16_t value);

/**
 * @ingroup tca0_normal
 * @brief Returns the maximum count value.
 * @param None.
 * @return Maximum count value
 */
uint16_t TCA0_MaxCountGet(void);

/**
 * @ingroup tca0_normal
 * @brief Sets the Waveform Generation mode.
 * @pre Initialize the TCA0 with TCA0__Initialize() before calling this API.
 * @param TCA_SINGLE_WGMODE_t mode:
 * - @c TCA_SINGLE_WGMODE_NORMAL_gc      @c  -     Normal mode
 * - @c TCA_SINGLE_WGMODE_FRQ_gc         @c  -     Frequency Generation mode
 * - @c TCA_SINGLE_WGMODE_SINGLESLOPE_gc @c  -     Single-Slope PWM
 * - @c TCA_SINGLE_WGMODE_DSTOP_gc       @c  -     Dual-Slope PWM, overflow on TOP
 * - @c TCA_SINGLE_WGMODE_DSBOTH_gc      @c  -     Dual-Slope PWM, overflow on TOP and BOTTOM
 * - @c TCA_SINGLE_WGMODE_DSBOTTOM_gc    @c  -     Dual-Slope PWM, overflow on BOTTOM
 * @return None.
 *
 */
void TCA0_ModeSet(TCA_SINGLE_WGMODE_t mode) __attribute__((deprecated("This function is deprecated.")));;

/**
 * @ingroup tca0_normal
 * @brief Enables the TCA0 interrupts.
 * @param None.
 * @return None.
 */
void TCA0_InterruptEnable(void);

/**
 * @ingroup tca0_normal
 * @brief Disables the TCA0 interrupts.
 * @param None.
 * @return None.
 */
void TCA0_InterruptDisable(void);

/**
 * @ingroup tca0_normal
 * @brief Registers a callback function for the TCA0 overflow or underflow event.
 * @param CallbackHandler - Address to the custom callback function
 * @return None.
 */ 

void TCA0_OverflowCallbackRegister(TCA0_cb_t CallbackHandler);

/**
 * @ingroup tca0_normal
 * @brief Registers a callback function for the TCA0 Compare 0 match event.
 * @param CallbackHandler - Address to the custom callback function
 * @return None.
 */ 
void TCA0_Compare0CallbackRegister(TCA0_cb_t CallbackHandler);

/**
 * @ingroup tca0_normal
 * @brief Registers a callback function for the TCA0 Compare 1 match event.
 * @param CallbackHandler - Address to the custom callback function
 * @return None.
 */ 
void TCA0_Compare1CallbackRegister(TCA0_cb_t CallbackHandler);

/**
 * @ingroup tca0_normal
 * @brief Registers a callback function for the TCA0 Compare 2 match event.
 * @param CallbackHandler - Address to the custom callback function
 * @return None.
 */ 
void TCA0_Compare2CallbackRegister(TCA0_cb_t CallbackHandler);


#endif /* TCA0_H_INCLUDED */