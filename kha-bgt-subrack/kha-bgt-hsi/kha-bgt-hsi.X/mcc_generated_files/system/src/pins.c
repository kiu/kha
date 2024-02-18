/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
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

#include "../pins.h"

static void (*IO_PA1_InterruptHandler)(void);
static void (*IO_PA0_InterruptHandler)(void);
static void (*IO_PA3_InterruptHandler)(void);
static void (*IO_BTN02A_InterruptHandler)(void);
static void (*IO_BTN02B_InterruptHandler)(void);
static void (*IO_BTN02P_InterruptHandler)(void);
static void (*IO_BTN01A_InterruptHandler)(void);
static void (*IO_BTN01B_InterruptHandler)(void);
static void (*IO_BTN01P_InterruptHandler)(void);
static void (*IO_BTN00A_InterruptHandler)(void);
static void (*IO_BTN00B_InterruptHandler)(void);
static void (*IO_BTN00P_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{
  /* DIR Registers Initialization */
    PORTA.DIR = 0x9;
    PORTC.DIR = 0x0;
    PORTD.DIR = 0x0;
    PORTF.DIR = 0x0;

  /* OUT Registers Initialization */
    PORTA.OUT = 0x1;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x0;
    PORTF.OUT = 0x0;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x8;
    PORTD.PIN5CTRL = 0x8;
    PORTD.PIN6CTRL = 0x8;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x8;
    PORTF.PIN1CTRL = 0x8;
    PORTF.PIN2CTRL = 0x8;
    PORTF.PIN3CTRL = 0x8;
    PORTF.PIN4CTRL = 0x8;
    PORTF.PIN5CTRL = 0x8;
    PORTF.PIN6CTRL = 0x0;
    PORTF.PIN7CTRL = 0x0;

  /* EVGENCTRL registers Initialization */

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TCDROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    IO_PA1_SetInterruptHandler(IO_PA1_DefaultInterruptHandler);
    IO_PA0_SetInterruptHandler(IO_PA0_DefaultInterruptHandler);
    IO_PA3_SetInterruptHandler(IO_PA3_DefaultInterruptHandler);
    IO_BTN02A_SetInterruptHandler(IO_BTN02A_DefaultInterruptHandler);
    IO_BTN02B_SetInterruptHandler(IO_BTN02B_DefaultInterruptHandler);
    IO_BTN02P_SetInterruptHandler(IO_BTN02P_DefaultInterruptHandler);
    IO_BTN01A_SetInterruptHandler(IO_BTN01A_DefaultInterruptHandler);
    IO_BTN01B_SetInterruptHandler(IO_BTN01B_DefaultInterruptHandler);
    IO_BTN01P_SetInterruptHandler(IO_BTN01P_DefaultInterruptHandler);
    IO_BTN00A_SetInterruptHandler(IO_BTN00A_DefaultInterruptHandler);
    IO_BTN00B_SetInterruptHandler(IO_BTN00B_DefaultInterruptHandler);
    IO_BTN00P_SetInterruptHandler(IO_BTN00P_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for IO_PA1 at application runtime
*/
void IO_PA1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA1_InterruptHandler = interruptHandler;
}

void IO_PA1_DefaultInterruptHandler(void)
{
    // add your IO_PA1 interrupt custom code
    // or set custom function using IO_PA1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA0 at application runtime
*/
void IO_PA0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA0_InterruptHandler = interruptHandler;
}

void IO_PA0_DefaultInterruptHandler(void)
{
    // add your IO_PA0 interrupt custom code
    // or set custom function using IO_PA0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA3 at application runtime
*/
void IO_PA3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA3_InterruptHandler = interruptHandler;
}

void IO_PA3_DefaultInterruptHandler(void)
{
    // add your IO_PA3 interrupt custom code
    // or set custom function using IO_PA3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN02A at application runtime
*/
void IO_BTN02A_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN02A_InterruptHandler = interruptHandler;
}

void IO_BTN02A_DefaultInterruptHandler(void)
{
    // add your IO_BTN02A interrupt custom code
    // or set custom function using IO_BTN02A_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN02B at application runtime
*/
void IO_BTN02B_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN02B_InterruptHandler = interruptHandler;
}

void IO_BTN02B_DefaultInterruptHandler(void)
{
    // add your IO_BTN02B interrupt custom code
    // or set custom function using IO_BTN02B_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN02P at application runtime
*/
void IO_BTN02P_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN02P_InterruptHandler = interruptHandler;
}

void IO_BTN02P_DefaultInterruptHandler(void)
{
    // add your IO_BTN02P interrupt custom code
    // or set custom function using IO_BTN02P_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN01A at application runtime
*/
void IO_BTN01A_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN01A_InterruptHandler = interruptHandler;
}

void IO_BTN01A_DefaultInterruptHandler(void)
{
    // add your IO_BTN01A interrupt custom code
    // or set custom function using IO_BTN01A_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN01B at application runtime
*/
void IO_BTN01B_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN01B_InterruptHandler = interruptHandler;
}

void IO_BTN01B_DefaultInterruptHandler(void)
{
    // add your IO_BTN01B interrupt custom code
    // or set custom function using IO_BTN01B_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN01P at application runtime
*/
void IO_BTN01P_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN01P_InterruptHandler = interruptHandler;
}

void IO_BTN01P_DefaultInterruptHandler(void)
{
    // add your IO_BTN01P interrupt custom code
    // or set custom function using IO_BTN01P_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN00A at application runtime
*/
void IO_BTN00A_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN00A_InterruptHandler = interruptHandler;
}

void IO_BTN00A_DefaultInterruptHandler(void)
{
    // add your IO_BTN00A interrupt custom code
    // or set custom function using IO_BTN00A_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN00B at application runtime
*/
void IO_BTN00B_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN00B_InterruptHandler = interruptHandler;
}

void IO_BTN00B_DefaultInterruptHandler(void)
{
    // add your IO_BTN00B interrupt custom code
    // or set custom function using IO_BTN00B_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_BTN00P at application runtime
*/
void IO_BTN00P_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_BTN00P_InterruptHandler = interruptHandler;
}

void IO_BTN00P_DefaultInterruptHandler(void)
{
    // add your IO_BTN00P interrupt custom code
    // or set custom function using IO_BTN00P_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       IO_PA1_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       IO_PA0_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT3_bm)
    {
       IO_PA3_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       IO_BTN02A_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       IO_BTN02B_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       IO_BTN02P_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT0_bm)
    {
       IO_BTN01A_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT1_bm)
    {
       IO_BTN01B_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       IO_BTN01P_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT3_bm)
    {
       IO_BTN00A_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       IO_BTN00B_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       IO_BTN00P_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/