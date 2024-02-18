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
static void (*IO_R02_InterruptHandler)(void);
static void (*IO_R00_InterruptHandler)(void);
static void (*IO_R01_InterruptHandler)(void);
static void (*IO_R03_InterruptHandler)(void);
static void (*IO_R04_InterruptHandler)(void);
static void (*IO_R05_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{
  /* DIR Registers Initialization */
    PORTA.DIR = 0x9;
    PORTC.DIR = 0x7;
    PORTD.DIR = 0xE0;
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
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
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
    IO_R02_SetInterruptHandler(IO_R02_DefaultInterruptHandler);
    IO_R00_SetInterruptHandler(IO_R00_DefaultInterruptHandler);
    IO_R01_SetInterruptHandler(IO_R01_DefaultInterruptHandler);
    IO_R03_SetInterruptHandler(IO_R03_DefaultInterruptHandler);
    IO_R04_SetInterruptHandler(IO_R04_DefaultInterruptHandler);
    IO_R05_SetInterruptHandler(IO_R05_DefaultInterruptHandler);
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
  Allows selecting an interrupt handler for IO_R02 at application runtime
*/
void IO_R02_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_R02_InterruptHandler = interruptHandler;
}

void IO_R02_DefaultInterruptHandler(void)
{
    // add your IO_R02 interrupt custom code
    // or set custom function using IO_R02_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_R00 at application runtime
*/
void IO_R00_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_R00_InterruptHandler = interruptHandler;
}

void IO_R00_DefaultInterruptHandler(void)
{
    // add your IO_R00 interrupt custom code
    // or set custom function using IO_R00_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_R01 at application runtime
*/
void IO_R01_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_R01_InterruptHandler = interruptHandler;
}

void IO_R01_DefaultInterruptHandler(void)
{
    // add your IO_R01 interrupt custom code
    // or set custom function using IO_R01_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_R03 at application runtime
*/
void IO_R03_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_R03_InterruptHandler = interruptHandler;
}

void IO_R03_DefaultInterruptHandler(void)
{
    // add your IO_R03 interrupt custom code
    // or set custom function using IO_R03_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_R04 at application runtime
*/
void IO_R04_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_R04_InterruptHandler = interruptHandler;
}

void IO_R04_DefaultInterruptHandler(void)
{
    // add your IO_R04 interrupt custom code
    // or set custom function using IO_R04_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_R05 at application runtime
*/
void IO_R05_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_R05_InterruptHandler = interruptHandler;
}

void IO_R05_DefaultInterruptHandler(void)
{
    // add your IO_R05 interrupt custom code
    // or set custom function using IO_R05_SetInterruptHandler()
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
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT0_bm)
    {
       IO_R02_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT1_bm)
    {
       IO_R00_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT2_bm)
    {
       IO_R01_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       IO_R03_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       IO_R04_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       IO_R05_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/