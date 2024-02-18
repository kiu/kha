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

//get/set IO_BTN02A aliases
#define IO_BTN02A_SetHigh() do { PORTD_OUTSET = 0x10; } while(0)
#define IO_BTN02A_SetLow() do { PORTD_OUTCLR = 0x10; } while(0)
#define IO_BTN02A_Toggle() do { PORTD_OUTTGL = 0x10; } while(0)
#define IO_BTN02A_GetValue() (VPORTD.IN & (0x1 << 4))
#define IO_BTN02A_SetDigitalInput() do { PORTD_DIRCLR = 0x10; } while(0)
#define IO_BTN02A_SetDigitalOutput() do { PORTD_DIRSET = 0x10; } while(0)
#define IO_BTN02A_SetPullUp() do { PORTD_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02A_ResetPullUp() do { PORTD_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02A_SetInverted() do { PORTD_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN02A_ResetInverted() do { PORTD_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN02A_DisableInterruptOnChange() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN02A_EnableInterruptForBothEdges() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN02A_EnableInterruptForRisingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN02A_EnableInterruptForFallingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN02A_DisableDigitalInputBuffer() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN02A_EnableInterruptForLowLevelSensing() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD4_SetInterruptHandler IO_BTN02A_SetInterruptHandler

//get/set IO_BTN02B aliases
#define IO_BTN02B_SetHigh() do { PORTD_OUTSET = 0x20; } while(0)
#define IO_BTN02B_SetLow() do { PORTD_OUTCLR = 0x20; } while(0)
#define IO_BTN02B_Toggle() do { PORTD_OUTTGL = 0x20; } while(0)
#define IO_BTN02B_GetValue() (VPORTD.IN & (0x1 << 5))
#define IO_BTN02B_SetDigitalInput() do { PORTD_DIRCLR = 0x20; } while(0)
#define IO_BTN02B_SetDigitalOutput() do { PORTD_DIRSET = 0x20; } while(0)
#define IO_BTN02B_SetPullUp() do { PORTD_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02B_ResetPullUp() do { PORTD_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02B_SetInverted() do { PORTD_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN02B_ResetInverted() do { PORTD_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN02B_DisableInterruptOnChange() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN02B_EnableInterruptForBothEdges() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN02B_EnableInterruptForRisingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN02B_EnableInterruptForFallingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN02B_DisableDigitalInputBuffer() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN02B_EnableInterruptForLowLevelSensing() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD5_SetInterruptHandler IO_BTN02B_SetInterruptHandler

//get/set IO_BTN02P aliases
#define IO_BTN02P_SetHigh() do { PORTD_OUTSET = 0x40; } while(0)
#define IO_BTN02P_SetLow() do { PORTD_OUTCLR = 0x40; } while(0)
#define IO_BTN02P_Toggle() do { PORTD_OUTTGL = 0x40; } while(0)
#define IO_BTN02P_GetValue() (VPORTD.IN & (0x1 << 6))
#define IO_BTN02P_SetDigitalInput() do { PORTD_DIRCLR = 0x40; } while(0)
#define IO_BTN02P_SetDigitalOutput() do { PORTD_DIRSET = 0x40; } while(0)
#define IO_BTN02P_SetPullUp() do { PORTD_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02P_ResetPullUp() do { PORTD_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN02P_SetInverted() do { PORTD_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN02P_ResetInverted() do { PORTD_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN02P_DisableInterruptOnChange() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN02P_EnableInterruptForBothEdges() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN02P_EnableInterruptForRisingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN02P_EnableInterruptForFallingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN02P_DisableDigitalInputBuffer() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN02P_EnableInterruptForLowLevelSensing() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PD6_SetInterruptHandler IO_BTN02P_SetInterruptHandler

//get/set IO_BTN01A aliases
#define IO_BTN01A_SetHigh() do { PORTF_OUTSET = 0x1; } while(0)
#define IO_BTN01A_SetLow() do { PORTF_OUTCLR = 0x1; } while(0)
#define IO_BTN01A_Toggle() do { PORTF_OUTTGL = 0x1; } while(0)
#define IO_BTN01A_GetValue() (VPORTF.IN & (0x1 << 0))
#define IO_BTN01A_SetDigitalInput() do { PORTF_DIRCLR = 0x1; } while(0)
#define IO_BTN01A_SetDigitalOutput() do { PORTF_DIRSET = 0x1; } while(0)
#define IO_BTN01A_SetPullUp() do { PORTF_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01A_ResetPullUp() do { PORTF_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01A_SetInverted() do { PORTF_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN01A_ResetInverted() do { PORTF_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN01A_DisableInterruptOnChange() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN01A_EnableInterruptForBothEdges() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN01A_EnableInterruptForRisingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN01A_EnableInterruptForFallingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN01A_DisableDigitalInputBuffer() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN01A_EnableInterruptForLowLevelSensing() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF0_SetInterruptHandler IO_BTN01A_SetInterruptHandler

//get/set IO_BTN01B aliases
#define IO_BTN01B_SetHigh() do { PORTF_OUTSET = 0x2; } while(0)
#define IO_BTN01B_SetLow() do { PORTF_OUTCLR = 0x2; } while(0)
#define IO_BTN01B_Toggle() do { PORTF_OUTTGL = 0x2; } while(0)
#define IO_BTN01B_GetValue() (VPORTF.IN & (0x1 << 1))
#define IO_BTN01B_SetDigitalInput() do { PORTF_DIRCLR = 0x2; } while(0)
#define IO_BTN01B_SetDigitalOutput() do { PORTF_DIRSET = 0x2; } while(0)
#define IO_BTN01B_SetPullUp() do { PORTF_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01B_ResetPullUp() do { PORTF_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01B_SetInverted() do { PORTF_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN01B_ResetInverted() do { PORTF_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN01B_DisableInterruptOnChange() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN01B_EnableInterruptForBothEdges() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN01B_EnableInterruptForRisingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN01B_EnableInterruptForFallingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN01B_DisableDigitalInputBuffer() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN01B_EnableInterruptForLowLevelSensing() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF1_SetInterruptHandler IO_BTN01B_SetInterruptHandler

//get/set IO_BTN01P aliases
#define IO_BTN01P_SetHigh() do { PORTF_OUTSET = 0x4; } while(0)
#define IO_BTN01P_SetLow() do { PORTF_OUTCLR = 0x4; } while(0)
#define IO_BTN01P_Toggle() do { PORTF_OUTTGL = 0x4; } while(0)
#define IO_BTN01P_GetValue() (VPORTF.IN & (0x1 << 2))
#define IO_BTN01P_SetDigitalInput() do { PORTF_DIRCLR = 0x4; } while(0)
#define IO_BTN01P_SetDigitalOutput() do { PORTF_DIRSET = 0x4; } while(0)
#define IO_BTN01P_SetPullUp() do { PORTF_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01P_ResetPullUp() do { PORTF_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN01P_SetInverted() do { PORTF_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN01P_ResetInverted() do { PORTF_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN01P_DisableInterruptOnChange() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN01P_EnableInterruptForBothEdges() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN01P_EnableInterruptForRisingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN01P_EnableInterruptForFallingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN01P_DisableDigitalInputBuffer() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN01P_EnableInterruptForLowLevelSensing() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF2_SetInterruptHandler IO_BTN01P_SetInterruptHandler

//get/set IO_BTN00A aliases
#define IO_BTN00A_SetHigh() do { PORTF_OUTSET = 0x8; } while(0)
#define IO_BTN00A_SetLow() do { PORTF_OUTCLR = 0x8; } while(0)
#define IO_BTN00A_Toggle() do { PORTF_OUTTGL = 0x8; } while(0)
#define IO_BTN00A_GetValue() (VPORTF.IN & (0x1 << 3))
#define IO_BTN00A_SetDigitalInput() do { PORTF_DIRCLR = 0x8; } while(0)
#define IO_BTN00A_SetDigitalOutput() do { PORTF_DIRSET = 0x8; } while(0)
#define IO_BTN00A_SetPullUp() do { PORTF_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00A_ResetPullUp() do { PORTF_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00A_SetInverted() do { PORTF_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN00A_ResetInverted() do { PORTF_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN00A_DisableInterruptOnChange() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN00A_EnableInterruptForBothEdges() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN00A_EnableInterruptForRisingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN00A_EnableInterruptForFallingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN00A_DisableDigitalInputBuffer() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN00A_EnableInterruptForLowLevelSensing() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF3_SetInterruptHandler IO_BTN00A_SetInterruptHandler

//get/set IO_BTN00B aliases
#define IO_BTN00B_SetHigh() do { PORTF_OUTSET = 0x10; } while(0)
#define IO_BTN00B_SetLow() do { PORTF_OUTCLR = 0x10; } while(0)
#define IO_BTN00B_Toggle() do { PORTF_OUTTGL = 0x10; } while(0)
#define IO_BTN00B_GetValue() (VPORTF.IN & (0x1 << 4))
#define IO_BTN00B_SetDigitalInput() do { PORTF_DIRCLR = 0x10; } while(0)
#define IO_BTN00B_SetDigitalOutput() do { PORTF_DIRSET = 0x10; } while(0)
#define IO_BTN00B_SetPullUp() do { PORTF_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00B_ResetPullUp() do { PORTF_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00B_SetInverted() do { PORTF_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN00B_ResetInverted() do { PORTF_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN00B_DisableInterruptOnChange() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN00B_EnableInterruptForBothEdges() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN00B_EnableInterruptForRisingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN00B_EnableInterruptForFallingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN00B_DisableDigitalInputBuffer() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN00B_EnableInterruptForLowLevelSensing() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF4_SetInterruptHandler IO_BTN00B_SetInterruptHandler

//get/set IO_BTN00P aliases
#define IO_BTN00P_SetHigh() do { PORTF_OUTSET = 0x20; } while(0)
#define IO_BTN00P_SetLow() do { PORTF_OUTCLR = 0x20; } while(0)
#define IO_BTN00P_Toggle() do { PORTF_OUTTGL = 0x20; } while(0)
#define IO_BTN00P_GetValue() (VPORTF.IN & (0x1 << 5))
#define IO_BTN00P_SetDigitalInput() do { PORTF_DIRCLR = 0x20; } while(0)
#define IO_BTN00P_SetDigitalOutput() do { PORTF_DIRSET = 0x20; } while(0)
#define IO_BTN00P_SetPullUp() do { PORTF_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00P_ResetPullUp() do { PORTF_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_BTN00P_SetInverted() do { PORTF_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_BTN00P_ResetInverted() do { PORTF_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_BTN00P_DisableInterruptOnChange() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_BTN00P_EnableInterruptForBothEdges() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_BTN00P_EnableInterruptForRisingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_BTN00P_EnableInterruptForFallingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_BTN00P_DisableDigitalInputBuffer() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_BTN00P_EnableInterruptForLowLevelSensing() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)
#define PF5_SetInterruptHandler IO_BTN00P_SetInterruptHandler

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
 * @brief Default Interrupt Handler for IO_BTN02A pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN02A_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN02A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN02A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN02A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN02A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN02A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN02B pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN02B_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN02B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN02B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN02B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN02B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN02B_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN02P pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN02P_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN02P ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN02P_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN02P pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN02P at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN02P_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN01A pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN01A_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN01A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN01A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN01A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN01A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN01A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN01B pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN01B_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN01B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN01B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN01B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN01B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN01B_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN01P pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN01P_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN01P ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN01P_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN01P pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN01P at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN01P_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN00A pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN00A_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN00A ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN00A_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN00A pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN00A at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN00A_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN00B pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN00B_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN00B ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN00B_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN00B pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN00B at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN00B_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for IO_BTN00P pin. 
 *        This is a predefined interrupt handler to be used together with the IO_BTN00P_SetInterruptHandler() method.
 *        This handler is called every time the IO_BTN00P ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void IO_BTN00P_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for IO_BTN00P pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for IO_BTN00P at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void IO_BTN00P_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
