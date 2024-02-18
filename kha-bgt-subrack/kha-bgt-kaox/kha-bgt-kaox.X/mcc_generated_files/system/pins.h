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

//get/set IO_BTN03 aliases
#define IO_BTN03_SetHigh() do { PORTD_OUTSET = 0x2; } while(0)
#define IO_BTN03_SetLow() do { PORTD_OUTCLR = 0x2; } while(0)
#define IO_BTN03_Toggle() do { PORTD_OUTTGL = 0x2; } while(0)
#define IO_BTN03_GetValue() (VPORTD.IN & (0x1 << 1))
#define IO_BTN03_SetDigitalInput() do { PORTD_DIRCLR = 0x2; } while(0)
#define IO_BTN03_SetDigitalOutput() do { PORTD_DIRSET = 0x2; } while(0)
#define IO_BTN03_SetPullUp() do { PORTD_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN03_ResetPullUp() do { PORTD_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN03_SetInverted() do { PORTD_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN03_ResetInverted() do { PORTD_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN03_DisableInterruptOnChange() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN03_EnableInterruptForBothEdges() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN03_EnableInterruptForRisingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN03_EnableInterruptForFallingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN03_DisableDigitalInputBuffer() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN03_EnableInterruptForLowLevelSensing() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD1_SetInterruptHandler IO_BTN03_SetInterruptHandler

//get/set IO_BTN02 aliases
#define IO_BTN02_SetHigh() do { PORTD_OUTSET = 0x10; } while(0)
#define IO_BTN02_SetLow() do { PORTD_OUTCLR = 0x10; } while(0)
#define IO_BTN02_Toggle() do { PORTD_OUTTGL = 0x10; } while(0)
#define IO_BTN02_GetValue() (VPORTD.IN & (0x1 << 4))
#define IO_BTN02_SetDigitalInput() do { PORTD_DIRCLR = 0x10; } while(0)
#define IO_BTN02_SetDigitalOutput() do { PORTD_DIRSET = 0x10; } while(0)
#define IO_BTN02_SetPullUp() do { PORTD_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02_ResetPullUp() do { PORTD_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02_SetInverted() do { PORTD_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN02_ResetInverted() do { PORTD_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN02_DisableInterruptOnChange() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN02_EnableInterruptForBothEdges() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN02_EnableInterruptForRisingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN02_EnableInterruptForFallingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN02_DisableDigitalInputBuffer() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN02_EnableInterruptForLowLevelSensing() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD4_SetInterruptHandler IO_BTN02_SetInterruptHandler

//get/set IO_BTN01 aliases
#define IO_BTN01_SetHigh() do { PORTF_OUTSET = 0x1; } while(0)
#define IO_BTN01_SetLow() do { PORTF_OUTCLR = 0x1; } while(0)
#define IO_BTN01_Toggle() do { PORTF_OUTTGL = 0x1; } while(0)
#define IO_BTN01_GetValue() (VPORTF.IN & (0x1 << 0))
#define IO_BTN01_SetDigitalInput() do { PORTF_DIRCLR = 0x1; } while(0)
#define IO_BTN01_SetDigitalOutput() do { PORTF_DIRSET = 0x1; } while(0)
#define IO_BTN01_SetPullUp() do { PORTF_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01_ResetPullUp() do { PORTF_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01_SetInverted() do { PORTF_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN01_ResetInverted() do { PORTF_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN01_DisableInterruptOnChange() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN01_EnableInterruptForBothEdges() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN01_EnableInterruptForRisingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN01_EnableInterruptForFallingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN01_DisableDigitalInputBuffer() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN01_EnableInterruptForLowLevelSensing() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF0_SetInterruptHandler IO_BTN01_SetInterruptHandler

//get/set IO_BTN00 aliases
#define IO_BTN00_SetHigh() do { PORTF_OUTSET = 0x8; } while(0)
#define IO_BTN00_SetLow() do { PORTF_OUTCLR = 0x8; } while(0)
#define IO_BTN00_Toggle() do { PORTF_OUTTGL = 0x8; } while(0)
#define IO_BTN00_GetValue() (VPORTF.IN & (0x1 << 3))
#define IO_BTN00_SetDigitalInput() do { PORTF_DIRCLR = 0x8; } while(0)
#define IO_BTN00_SetDigitalOutput() do { PORTF_DIRSET = 0x8; } while(0)
#define IO_BTN00_SetPullUp() do { PORTF_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00_ResetPullUp() do { PORTF_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00_SetInverted() do { PORTF_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN00_ResetInverted() do { PORTF_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN00_DisableInterruptOnChange() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN00_EnableInterruptForBothEdges() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN00_EnableInterruptForRisingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN00_EnableInterruptForFallingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN00_DisableDigitalInputBuffer() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN00_EnableInterruptForLowLevelSensing() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF3_SetInterruptHandler IO_BTN00_SetInterruptHandler

//get/set IO_PC3 aliases
#define IO_PC3_SetHigh() do { PORTC_OUTSET = 0x8; } while(0)
#define IO_PC3_SetLow() do { PORTC_OUTCLR = 0x8; } while(0)
#define IO_PC3_Toggle() do { PORTC_OUTTGL = 0x8; } while(0)
#define IO_PC3_GetValue() (VPORTC.IN & (0x1 << 3))
#define IO_PC3_SetDigitalInput() do { PORTC_DIRCLR = 0x8; } while(0)
#define IO_PC3_SetDigitalOutput() do { PORTC_DIRSET = 0x8; } while(0)
#define IO_PC3_SetPullUp() do { PORTC_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PC3_ResetPullUp() do { PORTC_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PC3_SetInverted() do { PORTC_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PC3_ResetInverted() do { PORTC_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PC3_DisableInterruptOnChange() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PC3_EnableInterruptForBothEdges() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PC3_EnableInterruptForRisingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PC3_EnableInterruptForFallingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PC3_DisableDigitalInputBuffer() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PC3_EnableInterruptForLowLevelSensing() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC3_SetInterruptHandler IO_PC3_SetInterruptHandler

//get/set IO_LED03A aliases
#define IO_LED03A_SetHigh() do { PORTD_OUTSET = 0x4; } while(0)
#define IO_LED03A_SetLow() do { PORTD_OUTCLR = 0x4; } while(0)
#define IO_LED03A_Toggle() do { PORTD_OUTTGL = 0x4; } while(0)
#define IO_LED03A_GetValue() (VPORTD.IN & (0x1 << 2))
#define IO_LED03A_SetDigitalInput() do { PORTD_DIRCLR = 0x4; } while(0)
#define IO_LED03A_SetDigitalOutput() do { PORTD_DIRSET = 0x4; } while(0)
#define IO_LED03A_SetPullUp() do { PORTD_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED03A_ResetPullUp() do { PORTD_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED03A_SetInverted() do { PORTD_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED03A_ResetInverted() do { PORTD_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED03A_DisableInterruptOnChange() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED03A_EnableInterruptForBothEdges() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED03A_EnableInterruptForRisingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED03A_EnableInterruptForFallingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED03A_DisableDigitalInputBuffer() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED03A_EnableInterruptForLowLevelSensing() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD2_SetInterruptHandler IO_LED03A_SetInterruptHandler

//get/set IO_LED03B aliases
#define IO_LED03B_SetHigh() do { PORTD_OUTSET = 0x8; } while(0)
#define IO_LED03B_SetLow() do { PORTD_OUTCLR = 0x8; } while(0)
#define IO_LED03B_Toggle() do { PORTD_OUTTGL = 0x8; } while(0)
#define IO_LED03B_GetValue() (VPORTD.IN & (0x1 << 3))
#define IO_LED03B_SetDigitalInput() do { PORTD_DIRCLR = 0x8; } while(0)
#define IO_LED03B_SetDigitalOutput() do { PORTD_DIRSET = 0x8; } while(0)
#define IO_LED03B_SetPullUp() do { PORTD_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED03B_ResetPullUp() do { PORTD_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED03B_SetInverted() do { PORTD_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED03B_ResetInverted() do { PORTD_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED03B_DisableInterruptOnChange() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED03B_EnableInterruptForBothEdges() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED03B_EnableInterruptForRisingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED03B_EnableInterruptForFallingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED03B_DisableDigitalInputBuffer() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED03B_EnableInterruptForLowLevelSensing() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD3_SetInterruptHandler IO_LED03B_SetInterruptHandler

//get/set IO_LED02A aliases
#define IO_LED02A_SetHigh() do { PORTD_OUTSET = 0x20; } while(0)
#define IO_LED02A_SetLow() do { PORTD_OUTCLR = 0x20; } while(0)
#define IO_LED02A_Toggle() do { PORTD_OUTTGL = 0x20; } while(0)
#define IO_LED02A_GetValue() (VPORTD.IN & (0x1 << 5))
#define IO_LED02A_SetDigitalInput() do { PORTD_DIRCLR = 0x20; } while(0)
#define IO_LED02A_SetDigitalOutput() do { PORTD_DIRSET = 0x20; } while(0)
#define IO_LED02A_SetPullUp() do { PORTD_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED02A_ResetPullUp() do { PORTD_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED02A_SetInverted() do { PORTD_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED02A_ResetInverted() do { PORTD_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED02A_DisableInterruptOnChange() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED02A_EnableInterruptForBothEdges() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED02A_EnableInterruptForRisingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED02A_EnableInterruptForFallingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED02A_DisableDigitalInputBuffer() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED02A_EnableInterruptForLowLevelSensing() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD5_SetInterruptHandler IO_LED02A_SetInterruptHandler

//get/set IO_LED02B aliases
#define IO_LED02B_SetHigh() do { PORTD_OUTSET = 0x40; } while(0)
#define IO_LED02B_SetLow() do { PORTD_OUTCLR = 0x40; } while(0)
#define IO_LED02B_Toggle() do { PORTD_OUTTGL = 0x40; } while(0)
#define IO_LED02B_GetValue() (VPORTD.IN & (0x1 << 6))
#define IO_LED02B_SetDigitalInput() do { PORTD_DIRCLR = 0x40; } while(0)
#define IO_LED02B_SetDigitalOutput() do { PORTD_DIRSET = 0x40; } while(0)
#define IO_LED02B_SetPullUp() do { PORTD_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED02B_ResetPullUp() do { PORTD_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED02B_SetInverted() do { PORTD_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED02B_ResetInverted() do { PORTD_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED02B_DisableInterruptOnChange() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED02B_EnableInterruptForBothEdges() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED02B_EnableInterruptForRisingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED02B_EnableInterruptForFallingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED02B_DisableDigitalInputBuffer() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED02B_EnableInterruptForLowLevelSensing() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD6_SetInterruptHandler IO_LED02B_SetInterruptHandler

//get/set IO_LED01A aliases
#define IO_LED01A_SetHigh() do { PORTF_OUTSET = 0x2; } while(0)
#define IO_LED01A_SetLow() do { PORTF_OUTCLR = 0x2; } while(0)
#define IO_LED01A_Toggle() do { PORTF_OUTTGL = 0x2; } while(0)
#define IO_LED01A_GetValue() (VPORTF.IN & (0x1 << 1))
#define IO_LED01A_SetDigitalInput() do { PORTF_DIRCLR = 0x2; } while(0)
#define IO_LED01A_SetDigitalOutput() do { PORTF_DIRSET = 0x2; } while(0)
#define IO_LED01A_SetPullUp() do { PORTF_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED01A_ResetPullUp() do { PORTF_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED01A_SetInverted() do { PORTF_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED01A_ResetInverted() do { PORTF_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED01A_DisableInterruptOnChange() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED01A_EnableInterruptForBothEdges() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED01A_EnableInterruptForRisingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED01A_EnableInterruptForFallingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED01A_DisableDigitalInputBuffer() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED01A_EnableInterruptForLowLevelSensing() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF1_SetInterruptHandler IO_LED01A_SetInterruptHandler

//get/set IO_LED01B aliases
#define IO_LED01B_SetHigh() do { PORTF_OUTSET = 0x4; } while(0)
#define IO_LED01B_SetLow() do { PORTF_OUTCLR = 0x4; } while(0)
#define IO_LED01B_Toggle() do { PORTF_OUTTGL = 0x4; } while(0)
#define IO_LED01B_GetValue() (VPORTF.IN & (0x1 << 2))
#define IO_LED01B_SetDigitalInput() do { PORTF_DIRCLR = 0x4; } while(0)
#define IO_LED01B_SetDigitalOutput() do { PORTF_DIRSET = 0x4; } while(0)
#define IO_LED01B_SetPullUp() do { PORTF_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED01B_ResetPullUp() do { PORTF_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED01B_SetInverted() do { PORTF_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED01B_ResetInverted() do { PORTF_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED01B_DisableInterruptOnChange() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED01B_EnableInterruptForBothEdges() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED01B_EnableInterruptForRisingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED01B_EnableInterruptForFallingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED01B_DisableDigitalInputBuffer() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED01B_EnableInterruptForLowLevelSensing() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF2_SetInterruptHandler IO_LED01B_SetInterruptHandler

//get/set IO_LED00A aliases
#define IO_LED00A_SetHigh() do { PORTF_OUTSET = 0x10; } while(0)
#define IO_LED00A_SetLow() do { PORTF_OUTCLR = 0x10; } while(0)
#define IO_LED00A_Toggle() do { PORTF_OUTTGL = 0x10; } while(0)
#define IO_LED00A_GetValue() (VPORTF.IN & (0x1 << 4))
#define IO_LED00A_SetDigitalInput() do { PORTF_DIRCLR = 0x10; } while(0)
#define IO_LED00A_SetDigitalOutput() do { PORTF_DIRSET = 0x10; } while(0)
#define IO_LED00A_SetPullUp() do { PORTF_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED00A_ResetPullUp() do { PORTF_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED00A_SetInverted() do { PORTF_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED00A_ResetInverted() do { PORTF_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED00A_DisableInterruptOnChange() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED00A_EnableInterruptForBothEdges() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED00A_EnableInterruptForRisingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED00A_EnableInterruptForFallingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED00A_DisableDigitalInputBuffer() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED00A_EnableInterruptForLowLevelSensing() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF4_SetInterruptHandler IO_LED00A_SetInterruptHandler

//get/set IO_LED00B aliases
#define IO_LED00B_SetHigh() do { PORTF_OUTSET = 0x20; } while(0)
#define IO_LED00B_SetLow() do { PORTF_OUTCLR = 0x20; } while(0)
#define IO_LED00B_Toggle() do { PORTF_OUTTGL = 0x20; } while(0)
#define IO_LED00B_GetValue() (VPORTF.IN & (0x1 << 5))
#define IO_LED00B_SetDigitalInput() do { PORTF_DIRCLR = 0x20; } while(0)
#define IO_LED00B_SetDigitalOutput() do { PORTF_DIRSET = 0x20; } while(0)
#define IO_LED00B_SetPullUp() do { PORTF_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED00B_ResetPullUp() do { PORTF_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED00B_SetInverted() do { PORTF_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED00B_ResetInverted() do { PORTF_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED00B_DisableInterruptOnChange() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED00B_EnableInterruptForBothEdges() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED00B_EnableInterruptForRisingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED00B_EnableInterruptForFallingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED00B_DisableDigitalInputBuffer() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED00B_EnableInterruptForLowLevelSensing() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF5_SetInterruptHandler IO_LED00B_SetInterruptHandler

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
 * @brief Default Interrupt Handler for IO_BTN03 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN03_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN03 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN03_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN03 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN03 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN03_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN02 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN02_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN02 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN02_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN02 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN02 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN02_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN01 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN01_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN01 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN01_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN01 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN01 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN01_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN00 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN00_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN00 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN00_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN00 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN00 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN00_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PC3 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PC3_SetInterruptHandler() method.
 *        This handler is called every time the IO_PC3 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PC3_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PC3 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PC3 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PC3_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED03A pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED03A_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED03A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED03A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED03A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED03A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED03A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED03B pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED03B_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED03B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED03B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED03B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED03B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED03B_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED02A pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED02A_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED02A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED02A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED02A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED02A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED02A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED02B pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED02B_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED02B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED02B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED02B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED02B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED02B_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED01A pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED01A_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED01A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED01A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED01A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED01A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED01A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED01B pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED01B_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED01B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED01B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED01B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED01B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED01B_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED00A pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED00A_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED00A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED00A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED00A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED00A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED00A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED00B pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED00B_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED00B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED00B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED00B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED00B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED00B_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
