

/**
  * CLKCTRL Generated Driver File
  *
  * @file clkctrl.c
  *
  * @ingroup clkctrl
  *
  * @brief This file contains the driver code for CLKCTRL module.
  *
  * version CLKCTRL Driver Version 1.1.4
  *
  * @version Package Version 2.0.10
*/
/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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


#include "../clock.h"

void CLOCK_Initialize(void)
{
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLA),(0 << CLKCTRL_CLKOUT_bp)   // CLKOUT disabled
            | CLKCTRL_CLKSEL_OSCHF_gc   // CLKSEL Internal high-frequency oscillator
            );
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLB),CLKCTRL_PDIV_2X_gc   // PDIV 2X
            | (0 << CLKCTRL_PEN_bp)   // PEN disabled
            );
    ccp_write_io((void*)&(CLKCTRL.OSC32KCTRLA),(0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            );
    ccp_write_io((void*)&(CLKCTRL.OSCHFCTRLA),(0 << CLKCTRL_AUTOTUNE_bp)   // AUTOTUNE disabled
            | CLKCTRL_FRQSEL_24M_gc   // FRQSEL 24 MHz system clock
            | (0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            );
    ccp_write_io((void*)&(CLKCTRL.OSCHFTUNE),0x0   // TUNE 0x0
            );
    ccp_write_io((void*)&(CLKCTRL.PLLCTRLA),CLKCTRL_MULFAC_DISABLE_gc   // MULFAC PLL is disabled
            | (0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            | CLKCTRL_SOURCE_OSCHF_gc   // SOURCE OSCHF
            );
    ccp_write_io((void*)&(CLKCTRL.XOSC32KCTRLA),CLKCTRL_CSUT_1K_gc   // CSUT 1k cycles
            | (0 << CLKCTRL_ENABLE_bp)   // ENABLE disabled
            | (0 << CLKCTRL_LPMODE_bp)   // LPMODE disabled
            | (0 << CLKCTRL_RUNSTDBY_bp)   // RUNSTDBY disabled
            | (0 << CLKCTRL_SEL_bp)   // SEL disabled
            );
    ccp_write_io((void*)&(CLKCTRL.MCLKCTRLC),(0 << CLKCTRL_CFDEN_bp)   // CFDEN disabled
            | CLKCTRL_CFDSRC_CLKMAIN_gc   // CFDSRC CLKMAIN
            | (0 << CLKCTRL_CFDTST_bp)   // CFDTST disabled
            );
    ccp_write_io((void*)&(CLKCTRL.MCLKINTCTRL),(0 << CLKCTRL_CFD_bp)   // CFD disabled
            | CLKCTRL_INTTYPE_INT_gc   // INTTYPE INT
            );
    ccp_write_io((void*)&(CLKCTRL.MCLKINTFLAGS),(0 << CLKCTRL_CFD_bp)   // CFD disabled
            );
    ccp_write_io((void*)&(CLKCTRL.XOSCHFCTRLA),CLKCTRL_CSUTHF_256_gc   // CSUTHF 256
            | (0 << CLKCTRL_ENABLE_bp)   // ENABLE disabled
            | CLKCTRL_FRQRANGE_8M_gc   // FRQRANGE 8M
            | (0 << CLKCTRL_RUNSTBY_bp)   // RUNSTBY disabled
            | CLKCTRL_SELHF_XTAL_gc   // SELHF XTAL
            );

    // System clock stability check by polling the status register.
    while(!(CLKCTRL.MCLKSTATUS & CLKCTRL_OSCHFS_bm))
    {
    }

}

void CFD_Enable(CLKCTRL_CFDSRC_t cfd_source)
{
    /* Enable Clock Failure Detection on main clock */
    ccp_write_io((uint8_t *) & CLKCTRL.MCLKCTRLC, cfd_source | CLKCTRL_CFDEN_bm);
}

void CFD_Disable(void)
{
    /* Disable Clock Failure Detection on main clock */
    ccp_write_io((uint8_t *) & CLKCTRL.MCLKCTRLC, CLKCTRL.MCLKCTRLC & ~CLKCTRL_CFDEN_bm);
}


/**
 End of File
*/