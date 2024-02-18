/**
  * TCA0 Generated Driver File
  *
  * @file tca0.c
  *
  * @ingroup tca0_normal
  *
  * @brief This file contains the API implementations for TCA0 module driver in Normal (16-bit) mode.
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


#include "../tca0.h"

const struct TMR_INTERFACE TCA0_Interface = {
    .Initialize = TCA0_Initialize,
    .Start = TCA0_Start,
    .Stop = TCA0_Stop,
    .PeriodCountSet = TCA0_Write,
    .TimeoutCallbackRegister = TCA0_OverflowCallbackRegister,
    .Tasks = NULL
};
void TCA0_DefaultCompare0CallbackRegister(void);
void (*TCA0_CMP0_isr_cb)(void) = &TCA0_DefaultCompare0CallbackRegister;

void TCA0_DefaultCompare1CallbackRegister(void);
void (*TCA0_CMP1_isr_cb)(void) = &TCA0_DefaultCompare1CallbackRegister;

void TCA0_DefaultCompare2CallbackRegister(void);
void (*TCA0_CMP2_isr_cb)(void) = &TCA0_DefaultCompare2CallbackRegister;

void TCA0_DefaultOverflowCallbackRegister(void);
void (*TCA0_OVF_isr_cb)(void) = &TCA0_DefaultOverflowCallbackRegister;

void TCA0_DefaultCompare0CallbackRegister(void)
{
    //Add your ISR code here
}

void TCA0_DefaultCompare1CallbackRegister(void)
{
    //Add your ISR code here
}

void TCA0_DefaultCompare2CallbackRegister(void)
{
    //Add your ISR code here
}

void TCA0_DefaultOverflowCallbackRegister(void)
{
    //Add your ISR code here
}

void TCA0_OverflowCallbackRegister(TCA0_cb_t cb)
{
    TCA0_OVF_isr_cb = cb;
}

void TCA0_Compare0CallbackRegister(TCA0_cb_t cb)
{
    TCA0_CMP0_isr_cb = cb;
}

void TCA0_Compare1CallbackRegister(TCA0_cb_t cb)
{
    TCA0_CMP1_isr_cb = cb;
}

void TCA0_Compare2CallbackRegister(TCA0_cb_t cb)
{
    TCA0_CMP2_isr_cb = cb;
}


ISR(TCA0_CMP0_vect)
{
    if (TCA0_CMP0_isr_cb != NULL)
        (*TCA0_CMP0_isr_cb)();
    
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm;
}

void TCA0_Initialize(void) {
    // Compare 0
    TCA0.SINGLE.CMP0 = 0x0;
        
    // Compare 1
    TCA0.SINGLE.CMP1 = 0x0;
    
    // Compare 2
    TCA0.SINGLE.CMP2 = 0x0;
        
    // Count
    TCA0.SINGLE.CNT = 0x0;
    
    // ALUPD disabled; CMP0EN disabled; CMP1EN disabled; CMP2EN disabled; WGMODE NORMAL; 
    TCA0.SINGLE.CTRLB = 0x0;
    
    // CMP0OV disabled; CMP1OV disabled; CMP2OV disabled; 
    TCA0.SINGLE.CTRLC = 0x0;
    
    // SPLITM disabled; 
    TCA0.SINGLE.CTRLD = 0x0;
    
    // CMD NONE; DIR disabled; LUPD disabled; 
    TCA0.SINGLE.CTRLECLR = 0x0;
    
    // CMD NONE; DIR UP; LUPD disabled; 
    TCA0.SINGLE.CTRLESET = 0x0;
    
    // CMP0BV disabled; CMP1BV disabled; CMP2BV disabled; PERBV disabled; 
    TCA0.SINGLE.CTRLFCLR = 0x0;
    
    // CMP0BV disabled; CMP1BV disabled; CMP2BV disabled; PERBV disabled; 
    TCA0.SINGLE.CTRLFSET = 0x0;
    
    // DBGRUN disabled; 
    TCA0.SINGLE.DBGCTRL = 0x0;
    
    // CNTAEI disabled; CNTBEI disabled; EVACTA CNT_POSEDGE; EVACTB NONE; 
    TCA0.SINGLE.EVCTRL = 0x0;
    
    // CMP0 enabled; CMP1 disabled; CMP2 disabled; OVF disabled; 
    TCA0.SINGLE.INTCTRL = 0x10;
    
    // CMP0 disabled; CMP1 disabled; CMP2 disabled; OVF disabled; 
    TCA0.SINGLE.INTFLAGS = 0x0;
    
    // Period
    TCA0.SINGLE.PER = 0x45;
    
    // Temporary data for 16-bit Access
    TCA0.SINGLE.TEMP = 0x0;
    
    // CLKSEL DIV1024; ENABLE enabled; RUNSTDBY disabled; 
    TCA0.SINGLE.CTRLA = 0xF;
    
}

void TCA0_Start(void)
{
    TCA0.SINGLE.CTRLA|= TCA_SINGLE_ENABLE_bm;
}

void TCA0_Stop(void)
{
    TCA0.SINGLE.CTRLA&= ~TCA_SINGLE_ENABLE_bm;
}

void TCA0_Write(uint16_t timerVal)
{
    TCA0.SINGLE.PER=timerVal;
}

uint16_t TCA0_Read(void)
{
    uint16_t readVal;

    readVal = TCA0.SINGLE.CNT;

    return readVal;
}

void TCA0_EnableInterrupt(void)
{
        TCA0.SINGLE.INTCTRL = 1 << TCA_SINGLE_CMP0_bp /* Compare 0 Interrupt: enabled */
	 				| 1 << TCA_SINGLE_CMP1_bp /* Compare 1 Interrupt: enabled */
	 				| 1 << TCA_SINGLE_CMP2_bp /* Compare 2 Interrupt: enabled */
	 				| 1 << TCA_SINGLE_OVF_bp; /* Overflow Interrupt: enabled */
}
void TCA0_DisableInterrupt(void)
{
    TCA0.SINGLE.INTCTRL = 0 << TCA_SINGLE_CMP0_bp /* Compare 0 Interrupt: disabled */
	 				| 0 << TCA_SINGLE_CMP1_bp /* Compare 1 Interrupt: disabled */
	 				| 0 << TCA_SINGLE_CMP2_bp /* Compare 2 Interrupt: disabled */
	 				| 0 << TCA_SINGLE_OVF_bp; /* Overflow Interrupt: disabled */
}
void TCA0_ClearOverflowInterruptFlag(void)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; /* Clear Overflow Interrupt Flag */
}
bool TCA0_IsOverflowInterruptFlagSet(void)
{
    return ((TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm) > 0);
}

void TCA0_ClearCMP0InterruptFlag(void)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm; /* Clear Compare Channel-0 Interrupt Flag */
}

bool TCA0_IsCMP0InterruptFlagSet(void)
{
    return ((TCA0.SINGLE.INTFLAGS & TCA_SINGLE_CMP0_bm) > 0);
}

void TCA0_ClearCMP1InterruptFlag(void)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP1_bm; /* Clear Compare Channel-1 Interrupt Flag */
}

bool TCA0_IsCMP1InterruptFlagSet(void)
{
    return ((TCA0.SINGLE.INTFLAGS & TCA_SINGLE_CMP1_bm) > 0);
}

void TCA0_ClearCMP2InterruptFlag(void)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP2_bm; /* Clear Compare Channel-2 Interrupt Flag */
}

bool TCA0_IsCMP2InterruptFlagSet(void)
{
    return ((TCA0.SINGLE.INTFLAGS & TCA_SINGLE_CMP2_bm) > 0);
}

void TCA0_WaveformFreqRegCountSet(cmpx_register_value_t count)
{
    //Write value to CMP0 register
    TCA0.SINGLE.CMP0=count;
}

uint16_t TCA0_WaveformFreqRegCountGet(void)
{
    //Returns CMP0 register value
    return TCA0.SINGLE.CMP0;
}

void TCA0_WO1OffsetRegCountSet(cmpx_register_value_t count)
{
    //Write value to CMP1 register
    TCA0.SINGLE.CMP1=count;
}

uint16_t TCA0_WO1OffsetRegCountGet(void)
{
    //Returns CMP1 register value
    return TCA0.SINGLE.CMP1;
}

void TCA0_WO2OffsetRegCountSet(cmpx_register_value_t count)
{
    //Write value to CMP2 register
    TCA0.SINGLE.CMP2=count;
}

uint16_t TCA0_WO2OffsetRegCountGet(void)
{
    //Returns CMP2 register value
    return TCA0.SINGLE.CMP2;;
}



void TCA0CounterSet(uint16_t value)
{
    //Write value to CNT register
    TCA0.SINGLE.CNT=value;
}

uint16_t TCA0CounterGet(void)
{
    //Returns CNT register value
    return TCA0.SINGLE.CNT;
}

void TCA0_Compare0Set(uint16_t value)
{
    //Write value to CMP0 register
    TCA0.SINGLE.CMP0=value;
}

void TCA0_Compare1Set(uint16_t value)
{
    //Write value to CMP1 register
    TCA0.SINGLE.CMP1=value;
}

void TCA0_Compare2Set(uint16_t value)
{
    //Write value to CMP2 register
    TCA0.SINGLE.CMP2=value;
}

void TCA0_ModeSet(TCA_SINGLE_WGMODE_t mode)
{
  uint8_t temp;
  if((mode == TCA_SINGLE_WGMODE_NORMAL_gc) ||
     (mode == TCA_SINGLE_WGMODE_FRQ_gc) ||
     (mode == TCA_SINGLE_WGMODE_SINGLESLOPE_gc) ||
     (mode == TCA_SINGLE_WGMODE_DSTOP_gc) ||
     (mode == TCA_SINGLE_WGMODE_DSBOTH_gc) ||
     (mode == TCA_SINGLE_WGMODE_DSBOTTOM_gc))
  {
      temp = (TCA0.SINGLE.CTRLB & ~TCA_SINGLE_WGMODE_gm) |
             (  mode     &  TCA_SINGLE_WGMODE_gm);
      TCA0.SINGLE.CTRLB = temp;
  }
}


