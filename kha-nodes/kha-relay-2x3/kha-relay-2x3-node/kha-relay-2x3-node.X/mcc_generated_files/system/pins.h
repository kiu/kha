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

//get/set IO_R02 aliases
#define IO_R02_SetHigh() do { PORTC_OUTSET = 0x1; } while(0)
#define IO_R02_SetLow() do { PORTC_OUTCLR = 0x1; } while(0)
#define IO_R02_Toggle() do { PORTC_OUTTGL = 0x1; } while(0)
#define IO_R02_GetValue() (VPORTC.IN & (0x1 << 0))
#define IO_R02_SetDigitalInput() do { PORTC_DIRCLR = 0x1; } while(0)
#define IO_R02_SetDigitalOutput() do { PORTC_DIRSET = 0x1; } while(0)
#define IO_R02_SetPullUp() do { PORTC_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_R02_ResetPullUp() do { PORTC_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_R02_SetInverted() do { PORTC_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_R02_ResetInverted() do { PORTC_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_R02_DisableInterruptOnChange() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_R02_EnableInterruptForBothEdges() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_R02_EnableInterruptForRisingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_R02_EnableInterruptForFallingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_R02_DisableDigitalInputBuffer() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_R02_EnableInterruptForLowLevelSensing() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC0_SetInterruptHandler IO_R02_SetInterruptHandler

//get/set IO_R00 aliases
#define IO_R00_SetHigh() do { PORTC_OUTSET = 0x2; } while(0)
#define IO_R00_SetLow() do { PORTC_OUTCLR = 0x2; } while(0)
#define IO_R00_Toggle() do { PORTC_OUTTGL = 0x2; } while(0)
#define IO_R00_GetValue() (VPORTC.IN & (0x1 << 1))
#define IO_R00_SetDigitalInput() do { PORTC_DIRCLR = 0x2; } while(0)
#define IO_R00_SetDigitalOutput() do { PORTC_DIRSET = 0x2; } while(0)
#define IO_R00_SetPullUp() do { PORTC_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_R00_ResetPullUp() do { PORTC_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_R00_SetInverted() do { PORTC_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_R00_ResetInverted() do { PORTC_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_R00_DisableInterruptOnChange() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_R00_EnableInterruptForBothEdges() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_R00_EnableInterruptForRisingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_R00_EnableInterruptForFallingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_R00_DisableDigitalInputBuffer() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_R00_EnableInterruptForLowLevelSensing() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC1_SetInterruptHandler IO_R00_SetInterruptHandler

//get/set IO_R01 aliases
#define IO_R01_SetHigh() do { PORTC_OUTSET = 0x4; } while(0)
#define IO_R01_SetLow() do { PORTC_OUTCLR = 0x4; } while(0)
#define IO_R01_Toggle() do { PORTC_OUTTGL = 0x4; } while(0)
#define IO_R01_GetValue() (VPORTC.IN & (0x1 << 2))
#define IO_R01_SetDigitalInput() do { PORTC_DIRCLR = 0x4; } while(0)
#define IO_R01_SetDigitalOutput() do { PORTC_DIRSET = 0x4; } while(0)
#define IO_R01_SetPullUp() do { PORTC_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_R01_ResetPullUp() do { PORTC_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_R01_SetInverted() do { PORTC_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_R01_ResetInverted() do { PORTC_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_R01_DisableInterruptOnChange() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_R01_EnableInterruptForBothEdges() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_R01_EnableInterruptForRisingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_R01_EnableInterruptForFallingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_R01_DisableDigitalInputBuffer() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_R01_EnableInterruptForLowLevelSensing() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC2_SetInterruptHandler IO_R01_SetInterruptHandler

//get/set IO_R03 aliases
#define IO_R03_SetHigh() do { PORTD_OUTSET = 0x20; } while(0)
#define IO_R03_SetLow() do { PORTD_OUTCLR = 0x20; } while(0)
#define IO_R03_Toggle() do { PORTD_OUTTGL = 0x20; } while(0)
#define IO_R03_GetValue() (VPORTD.IN & (0x1 << 5))
#define IO_R03_SetDigitalInput() do { PORTD_DIRCLR = 0x20; } while(0)
#define IO_R03_SetDigitalOutput() do { PORTD_DIRSET = 0x20; } while(0)
#define IO_R03_SetPullUp() do { PORTD_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_R03_ResetPullUp() do { PORTD_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_R03_SetInverted() do { PORTD_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_R03_ResetInverted() do { PORTD_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_R03_DisableInterruptOnChange() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_R03_EnableInterruptForBothEdges() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_R03_EnableInterruptForRisingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_R03_EnableInterruptForFallingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_R03_DisableDigitalInputBuffer() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_R03_EnableInterruptForLowLevelSensing() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD5_SetInterruptHandler IO_R03_SetInterruptHandler

//get/set IO_R04 aliases
#define IO_R04_SetHigh() do { PORTD_OUTSET = 0x40; } while(0)
#define IO_R04_SetLow() do { PORTD_OUTCLR = 0x40; } while(0)
#define IO_R04_Toggle() do { PORTD_OUTTGL = 0x40; } while(0)
#define IO_R04_GetValue() (VPORTD.IN & (0x1 << 6))
#define IO_R04_SetDigitalInput() do { PORTD_DIRCLR = 0x40; } while(0)
#define IO_R04_SetDigitalOutput() do { PORTD_DIRSET = 0x40; } while(0)
#define IO_R04_SetPullUp() do { PORTD_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_R04_ResetPullUp() do { PORTD_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_R04_SetInverted() do { PORTD_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_R04_ResetInverted() do { PORTD_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_R04_DisableInterruptOnChange() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_R04_EnableInterruptForBothEdges() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_R04_EnableInterruptForRisingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_R04_EnableInterruptForFallingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_R04_DisableDigitalInputBuffer() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_R04_EnableInterruptForLowLevelSensing() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD6_SetInterruptHandler IO_R04_SetInterruptHandler

//get/set IO_R05 aliases
#define IO_R05_SetHigh() do { PORTD_OUTSET = 0x80; } while(0)
#define IO_R05_SetLow() do { PORTD_OUTCLR = 0x80; } while(0)
#define IO_R05_Toggle() do { PORTD_OUTTGL = 0x80; } while(0)
#define IO_R05_GetValue() (VPORTD.IN & (0x1 << 7))
#define IO_R05_SetDigitalInput() do { PORTD_DIRCLR = 0x80; } while(0)
#define IO_R05_SetDigitalOutput() do { PORTD_DIRSET = 0x80; } while(0)
#define IO_R05_SetPullUp() do { PORTD_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_R05_ResetPullUp() do { PORTD_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_R05_SetInverted() do { PORTD_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_R05_ResetInverted() do { PORTD_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_R05_DisableInterruptOnChange() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_R05_EnableInterruptForBothEdges() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_R05_EnableInterruptForRisingEdge() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_R05_EnableInterruptForFallingEdge() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_R05_DisableDigitalInputBuffer() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_R05_EnableInterruptForLowLevelSensing() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD7_SetInterruptHandler IO_R05_SetInterruptHandler

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
 * @brief Default Interrupt Handler for IO_R02 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_R02_SetInterruptHandler() method.
 *        This handler is called every time the IO_R02 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_R02_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_R02 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_R02 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_R02_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_R00 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_R00_SetInterruptHandler() method.
 *        This handler is called every time the IO_R00 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_R00_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_R00 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_R00 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_R00_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_R01 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_R01_SetInterruptHandler() method.
 *        This handler is called every time the IO_R01 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_R01_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_R01 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_R01 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_R01_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_R03 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_R03_SetInterruptHandler() method.
 *        This handler is called every time the IO_R03 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_R03_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_R03 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_R03 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_R03_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_R04 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_R04_SetInterruptHandler() method.
 *        This handler is called every time the IO_R04 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_R04_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_R04 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_R04 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_R04_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_R05 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_R05_SetInterruptHandler() method.
 *        This handler is called every time the IO_R05 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_R05_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_R05 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_R05 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_R05_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
