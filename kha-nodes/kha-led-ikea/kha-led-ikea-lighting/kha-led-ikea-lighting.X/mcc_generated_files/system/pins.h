/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  1.1.0
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

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "./port.h"

//get/set IO_PA7 aliases
#define IO_PA7_SetHigh() do { PORTA_OUTSET = 0x80; } while(0)
#define IO_PA7_SetLow() do { PORTA_OUTCLR = 0x80; } while(0)
#define IO_PA7_Toggle() do { PORTA_OUTTGL = 0x80; } while(0)
#define IO_PA7_GetValue() (VPORTA.IN & (0x1 << 7))
#define IO_PA7_SetDigitalInput() do { PORTA_DIRCLR = 0x80; } while(0)
#define IO_PA7_SetDigitalOutput() do { PORTA_DIRSET = 0x80; } while(0)
#define IO_PA7_SetPullUp() do { PORTA_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PA7_ResetPullUp() do { PORTA_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PA7_SetInverted() do { PORTA_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PA7_ResetInverted() do { PORTA_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PA7_DisableInterruptOnChange() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PA7_EnableInterruptForBothEdges() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PA7_EnableInterruptForRisingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PA7_EnableInterruptForFallingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PA7_DisableDigitalInputBuffer() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PA7_EnableInterruptForLowLevelSensing() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA7_SetInterruptHandler IO_PA7_SetInterruptHandler

//get/set IO_LED aliases
#define IO_LED_SetHigh() do { PORTA_OUTSET = 0x8; } while(0)
#define IO_LED_SetLow() do { PORTA_OUTCLR = 0x8; } while(0)
#define IO_LED_Toggle() do { PORTA_OUTTGL = 0x8; } while(0)
#define IO_LED_GetValue() (VPORTA.IN & (0x1 << 3))
#define IO_LED_SetDigitalInput() do { PORTA_DIRCLR = 0x8; } while(0)
#define IO_LED_SetDigitalOutput() do { PORTA_DIRSET = 0x8; } while(0)
#define IO_LED_SetPullUp() do { PORTA_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED_ResetPullUp() do { PORTA_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED_SetInverted() do { PORTA_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED_ResetInverted() do { PORTA_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED_DisableInterruptOnChange() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED_EnableInterruptForBothEdges() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED_EnableInterruptForRisingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED_EnableInterruptForFallingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED_DisableDigitalInputBuffer() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED_EnableInterruptForLowLevelSensing() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA3_SetInterruptHandler IO_LED_SetInterruptHandler

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize();

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PA7 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PA7_SetInterruptHandler() method.
 *        This handler is called every time the IO_PA7 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PA7_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PA7 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PA7 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PA7_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
