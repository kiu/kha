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

//get/set IO_PA1 aliases
#define IO_PA1_SetHigh() do { PORTA_OUTSET = 0x2; } while(0)
#define IO_PA1_SetLow() do { PORTA_OUTCLR = 0x2; } while(0)
#define IO_PA1_Toggle() do { PORTA_OUTTGL = 0x2; } while(0)
#define IO_PA1_GetValue() (VPORTA.IN & (0x1 << 1))
#define IO_PA1_SetDigitalInput() do { PORTA_DIRCLR = 0x2; } while(0)
#define IO_PA1_SetDigitalOutput() do { PORTA_DIRSET = 0x2; } while(0)
#define IO_PA1_SetPullUp() do { PORTA_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PA1_ResetPullUp() do { PORTA_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PA1_SetInverted() do { PORTA_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PA1_ResetInverted() do { PORTA_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PA1_DisableInterruptOnChange() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PA1_EnableInterruptForBothEdges() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PA1_EnableInterruptForRisingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PA1_EnableInterruptForFallingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PA1_DisableDigitalInputBuffer() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PA1_EnableInterruptForLowLevelSensing() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA1_SetInterruptHandler IO_PA1_SetInterruptHandler

//get/set IO_PA0 aliases
#define IO_PA0_SetHigh() do { PORTA_OUTSET = 0x1; } while(0)
#define IO_PA0_SetLow() do { PORTA_OUTCLR = 0x1; } while(0)
#define IO_PA0_Toggle() do { PORTA_OUTTGL = 0x1; } while(0)
#define IO_PA0_GetValue() (VPORTA.IN & (0x1 << 0))
#define IO_PA0_SetDigitalInput() do { PORTA_DIRCLR = 0x1; } while(0)
#define IO_PA0_SetDigitalOutput() do { PORTA_DIRSET = 0x1; } while(0)
#define IO_PA0_SetPullUp() do { PORTA_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PA0_ResetPullUp() do { PORTA_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PA0_SetInverted() do { PORTA_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PA0_ResetInverted() do { PORTA_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PA0_DisableInterruptOnChange() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PA0_EnableInterruptForBothEdges() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PA0_EnableInterruptForRisingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PA0_EnableInterruptForFallingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PA0_DisableDigitalInputBuffer() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PA0_EnableInterruptForLowLevelSensing() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA0_SetInterruptHandler IO_PA0_SetInterruptHandler

//get/set IO_PA3 aliases
#define IO_PA3_SetHigh() do { PORTA_OUTSET = 0x8; } while(0)
#define IO_PA3_SetLow() do { PORTA_OUTCLR = 0x8; } while(0)
#define IO_PA3_Toggle() do { PORTA_OUTTGL = 0x8; } while(0)
#define IO_PA3_GetValue() (VPORTA.IN & (0x1 << 3))
#define IO_PA3_SetDigitalInput() do { PORTA_DIRCLR = 0x8; } while(0)
#define IO_PA3_SetDigitalOutput() do { PORTA_DIRSET = 0x8; } while(0)
#define IO_PA3_SetPullUp() do { PORTA_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PA3_ResetPullUp() do { PORTA_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PA3_SetInverted() do { PORTA_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PA3_ResetInverted() do { PORTA_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PA3_DisableInterruptOnChange() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PA3_EnableInterruptForBothEdges() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PA3_EnableInterruptForRisingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PA3_EnableInterruptForFallingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PA3_DisableDigitalInputBuffer() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PA3_EnableInterruptForLowLevelSensing() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA3_SetInterruptHandler IO_PA3_SetInterruptHandler

//get/set IO_BTN_SHUTDOWN aliases
#define IO_BTN_SHUTDOWN_SetHigh() do { PORTF_OUTSET = 0x4; } while(0)
#define IO_BTN_SHUTDOWN_SetLow() do { PORTF_OUTCLR = 0x4; } while(0)
#define IO_BTN_SHUTDOWN_Toggle() do { PORTF_OUTTGL = 0x4; } while(0)
#define IO_BTN_SHUTDOWN_GetValue() (VPORTF.IN & (0x1 << 2))
#define IO_BTN_SHUTDOWN_SetDigitalInput() do { PORTF_DIRCLR = 0x4; } while(0)
#define IO_BTN_SHUTDOWN_SetDigitalOutput() do { PORTF_DIRSET = 0x4; } while(0)
#define IO_BTN_SHUTDOWN_SetPullUp() do { PORTF_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN_SHUTDOWN_ResetPullUp() do { PORTF_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN_SHUTDOWN_SetInverted() do { PORTF_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN_SHUTDOWN_ResetInverted() do { PORTF_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN_SHUTDOWN_DisableInterruptOnChange() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN_SHUTDOWN_EnableInterruptForBothEdges() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN_SHUTDOWN_EnableInterruptForRisingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN_SHUTDOWN_EnableInterruptForFallingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN_SHUTDOWN_DisableDigitalInputBuffer() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN_SHUTDOWN_EnableInterruptForLowLevelSensing() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF2_SetInterruptHandler IO_BTN_SHUTDOWN_SetInterruptHandler

//get/set IO_BTN_OFF aliases
#define IO_BTN_OFF_SetHigh() do { PORTF_OUTSET = 0x20; } while(0)
#define IO_BTN_OFF_SetLow() do { PORTF_OUTCLR = 0x20; } while(0)
#define IO_BTN_OFF_Toggle() do { PORTF_OUTTGL = 0x20; } while(0)
#define IO_BTN_OFF_GetValue() (VPORTF.IN & (0x1 << 5))
#define IO_BTN_OFF_SetDigitalInput() do { PORTF_DIRCLR = 0x20; } while(0)
#define IO_BTN_OFF_SetDigitalOutput() do { PORTF_DIRSET = 0x20; } while(0)
#define IO_BTN_OFF_SetPullUp() do { PORTF_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN_OFF_ResetPullUp() do { PORTF_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN_OFF_SetInverted() do { PORTF_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN_OFF_ResetInverted() do { PORTF_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN_OFF_DisableInterruptOnChange() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN_OFF_EnableInterruptForBothEdges() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN_OFF_EnableInterruptForRisingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN_OFF_EnableInterruptForFallingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN_OFF_DisableDigitalInputBuffer() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN_OFF_EnableInterruptForLowLevelSensing() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF5_SetInterruptHandler IO_BTN_OFF_SetInterruptHandler

//get/set IO_PF0 aliases
#define IO_PF0_SetHigh() do { PORTF_OUTSET = 0x1; } while(0)
#define IO_PF0_SetLow() do { PORTF_OUTCLR = 0x1; } while(0)
#define IO_PF0_Toggle() do { PORTF_OUTTGL = 0x1; } while(0)
#define IO_PF0_GetValue() (VPORTF.IN & (0x1 << 0))
#define IO_PF0_SetDigitalInput() do { PORTF_DIRCLR = 0x1; } while(0)
#define IO_PF0_SetDigitalOutput() do { PORTF_DIRSET = 0x1; } while(0)
#define IO_PF0_SetPullUp() do { PORTF_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PF0_ResetPullUp() do { PORTF_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PF0_SetInverted() do { PORTF_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PF0_ResetInverted() do { PORTF_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PF0_DisableInterruptOnChange() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PF0_EnableInterruptForBothEdges() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PF0_EnableInterruptForRisingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PF0_EnableInterruptForFallingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PF0_DisableDigitalInputBuffer() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PF0_EnableInterruptForLowLevelSensing() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF0_SetInterruptHandler IO_PF0_SetInterruptHandler

//get/set IO_LED_SHUTDOWN aliases
#define IO_LED_SHUTDOWN_SetHigh() do { PORTF_OUTSET = 0x2; } while(0)
#define IO_LED_SHUTDOWN_SetLow() do { PORTF_OUTCLR = 0x2; } while(0)
#define IO_LED_SHUTDOWN_Toggle() do { PORTF_OUTTGL = 0x2; } while(0)
#define IO_LED_SHUTDOWN_GetValue() (VPORTF.IN & (0x1 << 1))
#define IO_LED_SHUTDOWN_SetDigitalInput() do { PORTF_DIRCLR = 0x2; } while(0)
#define IO_LED_SHUTDOWN_SetDigitalOutput() do { PORTF_DIRSET = 0x2; } while(0)
#define IO_LED_SHUTDOWN_SetPullUp() do { PORTF_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED_SHUTDOWN_ResetPullUp() do { PORTF_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED_SHUTDOWN_SetInverted() do { PORTF_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED_SHUTDOWN_ResetInverted() do { PORTF_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED_SHUTDOWN_DisableInterruptOnChange() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED_SHUTDOWN_EnableInterruptForBothEdges() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED_SHUTDOWN_EnableInterruptForRisingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED_SHUTDOWN_EnableInterruptForFallingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED_SHUTDOWN_DisableDigitalInputBuffer() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED_SHUTDOWN_EnableInterruptForLowLevelSensing() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF1_SetInterruptHandler IO_LED_SHUTDOWN_SetInterruptHandler

//get/set IO_PF3 aliases
#define IO_PF3_SetHigh() do { PORTF_OUTSET = 0x8; } while(0)
#define IO_PF3_SetLow() do { PORTF_OUTCLR = 0x8; } while(0)
#define IO_PF3_Toggle() do { PORTF_OUTTGL = 0x8; } while(0)
#define IO_PF3_GetValue() (VPORTF.IN & (0x1 << 3))
#define IO_PF3_SetDigitalInput() do { PORTF_DIRCLR = 0x8; } while(0)
#define IO_PF3_SetDigitalOutput() do { PORTF_DIRSET = 0x8; } while(0)
#define IO_PF3_SetPullUp() do { PORTF_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PF3_ResetPullUp() do { PORTF_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PF3_SetInverted() do { PORTF_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PF3_ResetInverted() do { PORTF_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PF3_DisableInterruptOnChange() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PF3_EnableInterruptForBothEdges() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PF3_EnableInterruptForRisingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PF3_EnableInterruptForFallingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PF3_DisableDigitalInputBuffer() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PF3_EnableInterruptForLowLevelSensing() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF3_SetInterruptHandler IO_PF3_SetInterruptHandler

//get/set IO_LED_OFF aliases
#define IO_LED_OFF_SetHigh() do { PORTF_OUTSET = 0x10; } while(0)
#define IO_LED_OFF_SetLow() do { PORTF_OUTCLR = 0x10; } while(0)
#define IO_LED_OFF_Toggle() do { PORTF_OUTTGL = 0x10; } while(0)
#define IO_LED_OFF_GetValue() (VPORTF.IN & (0x1 << 4))
#define IO_LED_OFF_SetDigitalInput() do { PORTF_DIRCLR = 0x10; } while(0)
#define IO_LED_OFF_SetDigitalOutput() do { PORTF_DIRSET = 0x10; } while(0)
#define IO_LED_OFF_SetPullUp() do { PORTF_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED_OFF_ResetPullUp() do { PORTF_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED_OFF_SetInverted() do { PORTF_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED_OFF_ResetInverted() do { PORTF_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED_OFF_DisableInterruptOnChange() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED_OFF_EnableInterruptForBothEdges() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED_OFF_EnableInterruptForRisingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED_OFF_EnableInterruptForFallingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED_OFF_DisableDigitalInputBuffer() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED_OFF_EnableInterruptForLowLevelSensing() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF4_SetInterruptHandler IO_LED_OFF_SetInterruptHandler

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize();

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PA1 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PA1_SetInterruptHandler() method.
 *        This handler is called every time the IO_PA1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PA1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PA1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PA1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PA1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PA0 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PA0_SetInterruptHandler() method.
 *        This handler is called every time the IO_PA0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PA0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PA0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PA0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PA0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PA3 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PA3_SetInterruptHandler() method.
 *        This handler is called every time the IO_PA3 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PA3_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PA3 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PA3 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PA3_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN_SHUTDOWN pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN_SHUTDOWN_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN_SHUTDOWN ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN_SHUTDOWN_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN_SHUTDOWN pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN_SHUTDOWN at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN_SHUTDOWN_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN_OFF pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN_OFF_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN_OFF ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN_OFF_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN_OFF pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN_OFF at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN_OFF_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PF0 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PF0_SetInterruptHandler() method.
 *        This handler is called every time the IO_PF0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PF0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PF0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PF0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PF0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED_SHUTDOWN pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED_SHUTDOWN_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED_SHUTDOWN ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED_SHUTDOWN_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED_SHUTDOWN pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED_SHUTDOWN at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED_SHUTDOWN_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PF3 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PF3_SetInterruptHandler() method.
 *        This handler is called every time the IO_PF3 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PF3_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PF3 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PF3 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PF3_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED_OFF pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED_OFF_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED_OFF ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED_OFF_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED_OFF pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED_OFF at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED_OFF_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
