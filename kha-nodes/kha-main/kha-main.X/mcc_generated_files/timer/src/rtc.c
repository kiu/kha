/**
  * RTC Generated Driver API Source File.
  *
  * @file rtc.c
  *
  * @ingroup rtc
  *
  * @brief This file contains the API implementations for the RTC driver.
  *
  * version RTC Driver Version 2.1.0
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


#include "../rtc.h"

void (*RTC_OVF_isr_cb)(void) = NULL;
void (*RTC_CMP_isr_cb)(void) = NULL;
void (*RTC_PIT_isr_cb)(void) = NULL;

int8_t RTC_Initialize(void)
{
    while (RTC.STATUS > 0) { /* Wait for all register to be synchronized */
    }
    //Compare 
    RTC.CMP = 0x7FFF;

    //Count
    RTC.CNT = 0x0;

    //Period
    RTC.PER = 0xFFFF;

    //Clock selection
    RTC.CLKSEL = 0x0;


    // CMP disabled; OVF disabled; 
    RTC.INTCTRL = 0x0;

    // DBGRUN disabled; 
    RTC.DBGCTRL = 0x0;

    // CORREN disabled; PRESCALER RTC Clock / 1; RTCEN enabled; RUNSTDBY disabled; 
    RTC.CTRLA = 0x1;


        while (RTC.PITSTATUS > 0) { /* Wait for all register to be synchronized */
    }
    // PI enabled; 
	RTC.PITINTCTRL = 0x1;

    // DBGRUN disabled; 
    RTC.PITDBGCTRL = 0x0;

    // PERIOD RTC Clock Cycles 8; PITEN enabled; 
    RTC.PITCTRLA = 0x11;

    return 0;
}

void RTC_Start(void)
{
    RTC.CTRLA |= RTC_RTCEN_bm;
}

void RTC_Stop(void)
{
    RTC.CTRLA &= ~RTC_RTCEN_bm;
}

void RTC_SetOVFIsrCallback(RTC_cb_t cb)
{
    RTC_OVF_isr_cb = cb;
}

void RTC_SetCMPIsrCallback(RTC_cb_t cb)
{
    RTC_CMP_isr_cb = cb;
}

void RTC_SetPITIsrCallback(RTC_cb_t cb)
{
    RTC_PIT_isr_cb = cb;
}

ISR(RTC_CNT_vect)
{
    if ( (RTC.INTCTRL & RTC_OVF_bm) && (RTC.INTFLAGS & RTC_OVF_bm) )
    {
        if (RTC_OVF_isr_cb != NULL) 
        {
            (*RTC_OVF_isr_cb)();
        } 
    }  
    
    if ( (RTC.INTCTRL & RTC_CMP_bm) && (RTC.INTFLAGS & RTC_CMP_bm) )
    {
        if (RTC_CMP_isr_cb != NULL) 
        {
            (*RTC_CMP_isr_cb)();
        } 
    }  
    RTC.INTFLAGS = (RTC_OVF_bm | RTC_CMP_bm);
}

ISR(RTC_PIT_vect)
{
   if (RTC_PIT_isr_cb != NULL) 
   {
    (*RTC_PIT_isr_cb)();
   } 
   RTC.PITINTFLAGS = RTC_PI_bm;
}

inline void RTC_WriteCounter(uint16_t timerVal)
{
    while (RTC.STATUS & RTC_CNTBUSY_bm);
    RTC.CNT = timerVal;
}

inline uint16_t RTC_ReadCounter(void)
{
    return RTC.CNT;
}

inline void RTC_WritePeriod(uint16_t timerVal)
{
    while (RTC.STATUS & RTC_PERBUSY_bm);
    RTC.PER = timerVal;
}

inline uint16_t RTC_ReadPeriod(void)
{
    return RTC.PER;
}

inline void RTC_EnableCMPInterrupt(void)
{
    RTC.INTCTRL |= RTC_CMP_bm;
}

inline void RTC_DisableCMPInterrupt(void)
{
    RTC.INTCTRL &= ~RTC_CMP_bm; 
}

inline void RTC_EnableOVFInterrupt(void)
{
    RTC.INTCTRL |= RTC_OVF_bm; 
}

inline void RTC_DisableOVFInterrupt(void)
{
    RTC.INTCTRL &= ~RTC_OVF_bm; 
}

inline void RTC_EnablePITInterrupt(void)
{
    RTC.PITINTCTRL |= RTC_PI_bm;  
}

inline void RTC_DisablePITInterrupt(void)
{
    RTC.PITINTCTRL &= ~RTC_PI_bm; 
}

inline void RTC_ClearOVFInterruptFlag(void)
{
    RTC.INTFLAGS = RTC_OVF_bm;
}

inline bool RTC_IsOVFInterruptEnabled(void)
{
    return ((RTC.INTCTRL & RTC_OVF_bm) > 0);
}

inline void RTC_WriteCMPRegister(uint16_t value)
{
    RTC.CMP = value;
}

inline uint16_t RTC_ReadCMPRegister(void)
{
    return RTC.CMP;
}