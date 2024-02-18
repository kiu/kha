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

//get/set IO_PC1 aliases
#define IO_PC1_SetHigh() do { PORTC_OUTSET = 0x2; } while(0)
#define IO_PC1_SetLow() do { PORTC_OUTCLR = 0x2; } while(0)
#define IO_PC1_Toggle() do { PORTC_OUTTGL = 0x2; } while(0)
#define IO_PC1_GetValue() (VPORTC.IN & (0x1 << 1))
#define IO_PC1_SetDigitalInput() do { PORTC_DIRCLR = 0x2; } while(0)
#define IO_PC1_SetDigitalOutput() do { PORTC_DIRSET = 0x2; } while(0)
#define IO_PC1_SetPullUp() do { PORTC_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PC1_ResetPullUp() do { PORTC_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PC1_SetInverted() do { PORTC_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PC1_ResetInverted() do { PORTC_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PC1_DisableInterruptOnChange() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PC1_EnableInterruptForBothEdges() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PC1_EnableInterruptForRisingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PC1_EnableInterruptForFallingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PC1_DisableDigitalInputBuffer() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PC1_EnableInterruptForLowLevelSensing() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC1_SetInterruptHandler IO_PC1_SetInterruptHandler

//get/set IO_PC0 aliases
#define IO_PC0_SetHigh() do { PORTC_OUTSET = 0x1; } while(0)
#define IO_PC0_SetLow() do { PORTC_OUTCLR = 0x1; } while(0)
#define IO_PC0_Toggle() do { PORTC_OUTTGL = 0x1; } while(0)
#define IO_PC0_GetValue() (VPORTC.IN & (0x1 << 0))
#define IO_PC0_SetDigitalInput() do { PORTC_DIRCLR = 0x1; } while(0)
#define IO_PC0_SetDigitalOutput() do { PORTC_DIRSET = 0x1; } while(0)
#define IO_PC0_SetPullUp() do { PORTC_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PC0_ResetPullUp() do { PORTC_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PC0_SetInverted() do { PORTC_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PC0_ResetInverted() do { PORTC_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PC0_DisableInterruptOnChange() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PC0_EnableInterruptForBothEdges() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PC0_EnableInterruptForRisingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PC0_EnableInterruptForFallingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PC0_DisableDigitalInputBuffer() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PC0_EnableInterruptForLowLevelSensing() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC0_SetInterruptHandler IO_PC0_SetInterruptHandler

//get/set IO_BT_LNK aliases
#define IO_BT_LNK_SetHigh() do { PORTC_OUTSET = 0x4; } while(0)
#define IO_BT_LNK_SetLow() do { PORTC_OUTCLR = 0x4; } while(0)
#define IO_BT_LNK_Toggle() do { PORTC_OUTTGL = 0x4; } while(0)
#define IO_BT_LNK_GetValue() (VPORTC.IN & (0x1 << 2))
#define IO_BT_LNK_SetDigitalInput() do { PORTC_DIRCLR = 0x4; } while(0)
#define IO_BT_LNK_SetDigitalOutput() do { PORTC_DIRSET = 0x4; } while(0)
#define IO_BT_LNK_SetPullUp() do { PORTC_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BT_LNK_ResetPullUp() do { PORTC_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BT_LNK_SetInverted() do { PORTC_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BT_LNK_ResetInverted() do { PORTC_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BT_LNK_DisableInterruptOnChange() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BT_LNK_EnableInterruptForBothEdges() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BT_LNK_EnableInterruptForRisingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BT_LNK_EnableInterruptForFallingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BT_LNK_DisableDigitalInputBuffer() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BT_LNK_EnableInterruptForLowLevelSensing() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC2_SetInterruptHandler IO_BT_LNK_SetInterruptHandler

//get/set IO_BTN00 aliases
#define IO_BTN00_SetHigh() do { PORTD_OUTSET = 0x2; } while(0)
#define IO_BTN00_SetLow() do { PORTD_OUTCLR = 0x2; } while(0)
#define IO_BTN00_Toggle() do { PORTD_OUTTGL = 0x2; } while(0)
#define IO_BTN00_GetValue() (VPORTD.IN & (0x1 << 1))
#define IO_BTN00_SetDigitalInput() do { PORTD_DIRCLR = 0x2; } while(0)
#define IO_BTN00_SetDigitalOutput() do { PORTD_DIRSET = 0x2; } while(0)
#define IO_BTN00_SetPullUp() do { PORTD_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00_ResetPullUp() do { PORTD_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00_SetInverted() do { PORTD_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN00_ResetInverted() do { PORTD_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN00_DisableInterruptOnChange() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN00_EnableInterruptForBothEdges() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN00_EnableInterruptForRisingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN00_EnableInterruptForFallingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN00_DisableDigitalInputBuffer() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN00_EnableInterruptForLowLevelSensing() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD1_SetInterruptHandler IO_BTN00_SetInterruptHandler

//get/set IO_BTN01 aliases
#define IO_BTN01_SetHigh() do { PORTD_OUTSET = 0x8; } while(0)
#define IO_BTN01_SetLow() do { PORTD_OUTCLR = 0x8; } while(0)
#define IO_BTN01_Toggle() do { PORTD_OUTTGL = 0x8; } while(0)
#define IO_BTN01_GetValue() (VPORTD.IN & (0x1 << 3))
#define IO_BTN01_SetDigitalInput() do { PORTD_DIRCLR = 0x8; } while(0)
#define IO_BTN01_SetDigitalOutput() do { PORTD_DIRSET = 0x8; } while(0)
#define IO_BTN01_SetPullUp() do { PORTD_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01_ResetPullUp() do { PORTD_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01_SetInverted() do { PORTD_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN01_ResetInverted() do { PORTD_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN01_DisableInterruptOnChange() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN01_EnableInterruptForBothEdges() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN01_EnableInterruptForRisingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN01_EnableInterruptForFallingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN01_DisableDigitalInputBuffer() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN01_EnableInterruptForLowLevelSensing() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD3_SetInterruptHandler IO_BTN01_SetInterruptHandler

//get/set IO_BTN02 aliases
#define IO_BTN02_SetHigh() do { PORTF_OUTSET = 0x1; } while(0)
#define IO_BTN02_SetLow() do { PORTF_OUTCLR = 0x1; } while(0)
#define IO_BTN02_Toggle() do { PORTF_OUTTGL = 0x1; } while(0)
#define IO_BTN02_GetValue() (VPORTF.IN & (0x1 << 0))
#define IO_BTN02_SetDigitalInput() do { PORTF_DIRCLR = 0x1; } while(0)
#define IO_BTN02_SetDigitalOutput() do { PORTF_DIRSET = 0x1; } while(0)
#define IO_BTN02_SetPullUp() do { PORTF_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02_ResetPullUp() do { PORTF_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02_SetInverted() do { PORTF_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN02_ResetInverted() do { PORTF_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN02_DisableInterruptOnChange() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN02_EnableInterruptForBothEdges() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN02_EnableInterruptForRisingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN02_EnableInterruptForFallingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN02_DisableDigitalInputBuffer() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN02_EnableInterruptForLowLevelSensing() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF0_SetInterruptHandler IO_BTN02_SetInterruptHandler

//get/set IO_BTN03 aliases
#define IO_BTN03_SetHigh() do { PORTF_OUTSET = 0x4; } while(0)
#define IO_BTN03_SetLow() do { PORTF_OUTCLR = 0x4; } while(0)
#define IO_BTN03_Toggle() do { PORTF_OUTTGL = 0x4; } while(0)
#define IO_BTN03_GetValue() (VPORTF.IN & (0x1 << 2))
#define IO_BTN03_SetDigitalInput() do { PORTF_DIRCLR = 0x4; } while(0)
#define IO_BTN03_SetDigitalOutput() do { PORTF_DIRSET = 0x4; } while(0)
#define IO_BTN03_SetPullUp() do { PORTF_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN03_ResetPullUp() do { PORTF_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN03_SetInverted() do { PORTF_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN03_ResetInverted() do { PORTF_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN03_DisableInterruptOnChange() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN03_EnableInterruptForBothEdges() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN03_EnableInterruptForRisingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN03_EnableInterruptForFallingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN03_DisableDigitalInputBuffer() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN03_EnableInterruptForLowLevelSensing() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF2_SetInterruptHandler IO_BTN03_SetInterruptHandler

//get/set IO_SR02 aliases
#define IO_SR02_SetHigh() do { PORTA_OUTSET = 0x10; } while(0)
#define IO_SR02_SetLow() do { PORTA_OUTCLR = 0x10; } while(0)
#define IO_SR02_Toggle() do { PORTA_OUTTGL = 0x10; } while(0)
#define IO_SR02_GetValue() (VPORTA.IN & (0x1 << 4))
#define IO_SR02_SetDigitalInput() do { PORTA_DIRCLR = 0x10; } while(0)
#define IO_SR02_SetDigitalOutput() do { PORTA_DIRSET = 0x10; } while(0)
#define IO_SR02_SetPullUp() do { PORTA_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_SR02_ResetPullUp() do { PORTA_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_SR02_SetInverted() do { PORTA_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_SR02_ResetInverted() do { PORTA_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_SR02_DisableInterruptOnChange() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_SR02_EnableInterruptForBothEdges() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_SR02_EnableInterruptForRisingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_SR02_EnableInterruptForFallingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_SR02_DisableDigitalInputBuffer() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_SR02_EnableInterruptForLowLevelSensing() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA4_SetInterruptHandler IO_SR02_SetInterruptHandler

//get/set IO_SR03 aliases
#define IO_SR03_SetHigh() do { PORTA_OUTSET = 0x20; } while(0)
#define IO_SR03_SetLow() do { PORTA_OUTCLR = 0x20; } while(0)
#define IO_SR03_Toggle() do { PORTA_OUTTGL = 0x20; } while(0)
#define IO_SR03_GetValue() (VPORTA.IN & (0x1 << 5))
#define IO_SR03_SetDigitalInput() do { PORTA_DIRCLR = 0x20; } while(0)
#define IO_SR03_SetDigitalOutput() do { PORTA_DIRSET = 0x20; } while(0)
#define IO_SR03_SetPullUp() do { PORTA_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_SR03_ResetPullUp() do { PORTA_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_SR03_SetInverted() do { PORTA_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_SR03_ResetInverted() do { PORTA_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_SR03_DisableInterruptOnChange() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_SR03_EnableInterruptForBothEdges() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_SR03_EnableInterruptForRisingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_SR03_EnableInterruptForFallingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_SR03_DisableDigitalInputBuffer() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_SR03_EnableInterruptForLowLevelSensing() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA5_SetInterruptHandler IO_SR03_SetInterruptHandler

//get/set IO_SR01 aliases
#define IO_SR01_SetHigh() do { PORTA_OUTSET = 0x40; } while(0)
#define IO_SR01_SetLow() do { PORTA_OUTCLR = 0x40; } while(0)
#define IO_SR01_Toggle() do { PORTA_OUTTGL = 0x40; } while(0)
#define IO_SR01_GetValue() (VPORTA.IN & (0x1 << 6))
#define IO_SR01_SetDigitalInput() do { PORTA_DIRCLR = 0x40; } while(0)
#define IO_SR01_SetDigitalOutput() do { PORTA_DIRSET = 0x40; } while(0)
#define IO_SR01_SetPullUp() do { PORTA_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_SR01_ResetPullUp() do { PORTA_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_SR01_SetInverted() do { PORTA_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_SR01_ResetInverted() do { PORTA_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_SR01_DisableInterruptOnChange() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_SR01_EnableInterruptForBothEdges() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_SR01_EnableInterruptForRisingEdge() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_SR01_EnableInterruptForFallingEdge() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_SR01_DisableDigitalInputBuffer() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_SR01_EnableInterruptForLowLevelSensing() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA6_SetInterruptHandler IO_SR01_SetInterruptHandler

//get/set IO_BT_CON aliases
#define IO_BT_CON_SetHigh() do { PORTA_OUTSET = 0x80; } while(0)
#define IO_BT_CON_SetLow() do { PORTA_OUTCLR = 0x80; } while(0)
#define IO_BT_CON_Toggle() do { PORTA_OUTTGL = 0x80; } while(0)
#define IO_BT_CON_GetValue() (VPORTA.IN & (0x1 << 7))
#define IO_BT_CON_SetDigitalInput() do { PORTA_DIRCLR = 0x80; } while(0)
#define IO_BT_CON_SetDigitalOutput() do { PORTA_DIRSET = 0x80; } while(0)
#define IO_BT_CON_SetPullUp() do { PORTA_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BT_CON_ResetPullUp() do { PORTA_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BT_CON_SetInverted() do { PORTA_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BT_CON_ResetInverted() do { PORTA_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BT_CON_DisableInterruptOnChange() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BT_CON_EnableInterruptForBothEdges() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BT_CON_EnableInterruptForRisingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BT_CON_EnableInterruptForFallingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BT_CON_DisableDigitalInputBuffer() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BT_CON_EnableInterruptForLowLevelSensing() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PA7_SetInterruptHandler IO_BT_CON_SetInterruptHandler

//get/set IO_BT_VCC aliases
#define IO_BT_VCC_SetHigh() do { PORTC_OUTSET = 0x8; } while(0)
#define IO_BT_VCC_SetLow() do { PORTC_OUTCLR = 0x8; } while(0)
#define IO_BT_VCC_Toggle() do { PORTC_OUTTGL = 0x8; } while(0)
#define IO_BT_VCC_GetValue() (VPORTC.IN & (0x1 << 3))
#define IO_BT_VCC_SetDigitalInput() do { PORTC_DIRCLR = 0x8; } while(0)
#define IO_BT_VCC_SetDigitalOutput() do { PORTC_DIRSET = 0x8; } while(0)
#define IO_BT_VCC_SetPullUp() do { PORTC_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BT_VCC_ResetPullUp() do { PORTC_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BT_VCC_SetInverted() do { PORTC_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BT_VCC_ResetInverted() do { PORTC_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BT_VCC_DisableInterruptOnChange() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BT_VCC_EnableInterruptForBothEdges() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BT_VCC_EnableInterruptForRisingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BT_VCC_EnableInterruptForFallingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BT_VCC_DisableDigitalInputBuffer() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BT_VCC_EnableInterruptForLowLevelSensing() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PC3_SetInterruptHandler IO_BT_VCC_SetInterruptHandler

//get/set IO_LED00 aliases
#define IO_LED00_SetHigh() do { PORTD_OUTSET = 0x4; } while(0)
#define IO_LED00_SetLow() do { PORTD_OUTCLR = 0x4; } while(0)
#define IO_LED00_Toggle() do { PORTD_OUTTGL = 0x4; } while(0)
#define IO_LED00_GetValue() (VPORTD.IN & (0x1 << 2))
#define IO_LED00_SetDigitalInput() do { PORTD_DIRCLR = 0x4; } while(0)
#define IO_LED00_SetDigitalOutput() do { PORTD_DIRSET = 0x4; } while(0)
#define IO_LED00_SetPullUp() do { PORTD_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED00_ResetPullUp() do { PORTD_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED00_SetInverted() do { PORTD_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED00_ResetInverted() do { PORTD_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED00_DisableInterruptOnChange() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED00_EnableInterruptForBothEdges() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED00_EnableInterruptForRisingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED00_EnableInterruptForFallingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED00_DisableDigitalInputBuffer() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED00_EnableInterruptForLowLevelSensing() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD2_SetInterruptHandler IO_LED00_SetInterruptHandler

//get/set IO_LED01 aliases
#define IO_LED01_SetHigh() do { PORTD_OUTSET = 0x10; } while(0)
#define IO_LED01_SetLow() do { PORTD_OUTCLR = 0x10; } while(0)
#define IO_LED01_Toggle() do { PORTD_OUTTGL = 0x10; } while(0)
#define IO_LED01_GetValue() (VPORTD.IN & (0x1 << 4))
#define IO_LED01_SetDigitalInput() do { PORTD_DIRCLR = 0x10; } while(0)
#define IO_LED01_SetDigitalOutput() do { PORTD_DIRSET = 0x10; } while(0)
#define IO_LED01_SetPullUp() do { PORTD_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED01_ResetPullUp() do { PORTD_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED01_SetInverted() do { PORTD_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED01_ResetInverted() do { PORTD_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED01_DisableInterruptOnChange() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED01_EnableInterruptForBothEdges() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED01_EnableInterruptForRisingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED01_EnableInterruptForFallingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED01_DisableDigitalInputBuffer() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED01_EnableInterruptForLowLevelSensing() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD4_SetInterruptHandler IO_LED01_SetInterruptHandler

//get/set IO_LED02 aliases
#define IO_LED02_SetHigh() do { PORTF_OUTSET = 0x2; } while(0)
#define IO_LED02_SetLow() do { PORTF_OUTCLR = 0x2; } while(0)
#define IO_LED02_Toggle() do { PORTF_OUTTGL = 0x2; } while(0)
#define IO_LED02_GetValue() (VPORTF.IN & (0x1 << 1))
#define IO_LED02_SetDigitalInput() do { PORTF_DIRCLR = 0x2; } while(0)
#define IO_LED02_SetDigitalOutput() do { PORTF_DIRSET = 0x2; } while(0)
#define IO_LED02_SetPullUp() do { PORTF_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED02_ResetPullUp() do { PORTF_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED02_SetInverted() do { PORTF_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED02_ResetInverted() do { PORTF_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED02_DisableInterruptOnChange() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED02_EnableInterruptForBothEdges() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED02_EnableInterruptForRisingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED02_EnableInterruptForFallingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED02_DisableDigitalInputBuffer() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED02_EnableInterruptForLowLevelSensing() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF1_SetInterruptHandler IO_LED02_SetInterruptHandler

//get/set IO_LED03 aliases
#define IO_LED03_SetHigh() do { PORTF_OUTSET = 0x8; } while(0)
#define IO_LED03_SetLow() do { PORTF_OUTCLR = 0x8; } while(0)
#define IO_LED03_Toggle() do { PORTF_OUTTGL = 0x8; } while(0)
#define IO_LED03_GetValue() (VPORTF.IN & (0x1 << 3))
#define IO_LED03_SetDigitalInput() do { PORTF_DIRCLR = 0x8; } while(0)
#define IO_LED03_SetDigitalOutput() do { PORTF_DIRSET = 0x8; } while(0)
#define IO_LED03_SetPullUp() do { PORTF_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_LED03_ResetPullUp() do { PORTF_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_LED03_SetInverted() do { PORTF_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_LED03_ResetInverted() do { PORTF_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_LED03_DisableInterruptOnChange() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_LED03_EnableInterruptForBothEdges() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_LED03_EnableInterruptForRisingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_LED03_EnableInterruptForFallingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_LED03_DisableDigitalInputBuffer() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_LED03_EnableInterruptForLowLevelSensing() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF3_SetInterruptHandler IO_LED03_SetInterruptHandler

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
 * @brief Default Interrupt Handler for IO_PC1 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PC1_SetInterruptHandler() method.
 *        This handler is called every time the IO_PC1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PC1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PC1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PC1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PC1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_PC0 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_PC0_SetInterruptHandler() method.
 *        This handler is called every time the IO_PC0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_PC0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_PC0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_PC0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_PC0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BT_LNK pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BT_LNK_SetInterruptHandler() method.
 *        This handler is called every time the IO_BT_LNK ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BT_LNK_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BT_LNK pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BT_LNK at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BT_LNK_SetInterruptHandler(void (* interruptHandler)(void)) ; 

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
 * @brief Default Interrupt Handler for IO_SR02 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_SR02_SetInterruptHandler() method.
 *        This handler is called every time the IO_SR02 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_SR02_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_SR02 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_SR02 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_SR02_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_SR03 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_SR03_SetInterruptHandler() method.
 *        This handler is called every time the IO_SR03 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_SR03_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_SR03 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_SR03 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_SR03_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_SR01 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_SR01_SetInterruptHandler() method.
 *        This handler is called every time the IO_SR01 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_SR01_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_SR01 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_SR01 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_SR01_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BT_CON pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BT_CON_SetInterruptHandler() method.
 *        This handler is called every time the IO_BT_CON ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BT_CON_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BT_CON pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BT_CON at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BT_CON_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BT_VCC pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BT_VCC_SetInterruptHandler() method.
 *        This handler is called every time the IO_BT_VCC ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BT_VCC_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BT_VCC pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BT_VCC at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BT_VCC_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED00 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED00_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED00 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED00_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED00 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED00 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED00_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED01 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED01_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED01 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED01_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED01 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED01 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED01_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED02 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED02_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED02 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED02_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED02 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED02 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED02_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_LED03 pin. 
 *        This is a predefined interrupt handler to be used together with the IO_LED03_SetInterruptHandler() method.
 *        This handler is called every time the IO_LED03 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_LED03_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_LED03 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_LED03 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_LED03_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
