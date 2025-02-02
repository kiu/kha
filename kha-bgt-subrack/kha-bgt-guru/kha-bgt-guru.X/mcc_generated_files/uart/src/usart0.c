/**
 * USART0 Generated Driver API Header File
 * 
 * @file usart0.c
 * 
 * @ingroup usart0
 * 
 * @brief This is the generated driver implementation file for the USART0 driver using the  Universal Synchronous and Asynchronous serial Receiver and Transmitter (USART) module. 
 *
 * @version USART0 Driver Version 2.1.1
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

/**
  Section: Included Files
*/

#include "../usart0.h"

/**
  Section: Macro Declarations
*/

#define USART0_RX_BUFFER_SIZE (512U) //buffer size should be 2^n
#define USART0_RX_BUFFER_MASK (USART0_RX_BUFFER_SIZE - 1U)



/**
  Section: Driver Interface
 */

const uart_drv_interface_t UART0 = {
    .Initialize = &USART0_Initialize,
    .Deinitialize = &USART0_Deinitialize,
    .Read = &USART0_Read,
    .Write = &USART0_Write,
    .IsRxReady = &USART0_IsRxReady,
    .IsTxReady = &USART0_IsTxReady,
    .IsTxDone = &USART0_IsTxDone,
    .TransmitEnable = &USART0_TransmitEnable,
    .TransmitDisable = &USART0_TransmitDisable,
    .AutoBaudSet = &USART0_AutoBaudSet,
    .AutoBaudQuery = &USART0_AutoBaudQuery,
    .BRGCountSet = NULL,
    .BRGCountGet = NULL,
    .BaudRateSet = NULL,
    .BaudRateGet = NULL,
    .AutoBaudEventEnableGet = NULL,
    .ErrorGet = &USART0_ErrorGet,
    .TxCompleteCallbackRegister = NULL,
    .RxCompleteCallbackRegister = &USART0_RxCompleteCallbackRegister,
    .TxCollisionCallbackRegister = NULL,
    .FramingErrorCallbackRegister = &USART0_FramingErrorCallbackRegister,
    .OverrunErrorCallbackRegister = &USART0_OverrunErrorCallbackRegister,
    .ParityErrorCallbackRegister = &USART0_ParityErrorCallbackRegister,
    .EventCallbackRegister = NULL,
};

/**
  Section: USART0 variables
*/
static volatile uint16_t usart0RxHead = 0;
static volatile uint16_t usart0RxTail = 0;
static volatile uint16_t usart0RxCount;
static volatile uint8_t usart0RxBuffer[USART0_RX_BUFFER_SIZE];
/**
 * @misradeviation{@advisory,19.2}
 * The UART error status necessitates checking the bit field and accessing the status within the group byte therefore the use of a union is essential.
 */
  /* cppcheck-suppress misra-c2012-19.2 */
static volatile usart0_status_t usart0RxStatusBuffer[USART0_RX_BUFFER_SIZE];
 /* cppcheck-suppress misra-c2012-19.2 */
static volatile usart0_status_t usart0RxLastError;

/**
  Section: USART0 APIs
*/
static void (*USART0_FramingErrorHandler)(void);
static void (*USART0_OverrunErrorHandler)(void);
static void (*USART0_ParityErrorHandler)(void);
void (*USART0_RxInterruptHandler)(void);
static void (*USART0_RxCompleteInterruptHandler)(void) = NULL;

static void USART0_DefaultFramingErrorCallback(void);
static void USART0_DefaultOverrunErrorCallback(void);
static void USART0_DefaultParityErrorCallback(void);
void USART0_ReceiveISR(void);



/**
  Section: USART0  APIs
*/

void USART0_Initialize(void)
{
    USART0_RxInterruptHandler = USART0_ReceiveISR;  
    // Set the USART0 module to the options selected in the user interface.

    //BAUD 192; 
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(500000UL);
	
    // ABEIE disabled; DREIE disabled; LBME disabled; RS485 ENABLE; RXCIE enabled; RXSIE enabled; TXCIE disabled; 
    USART0.CTRLA = 0x91;
	
    // MPCM disabled; ODME disabled; RXEN enabled; RXMODE NORMAL; SFDEN disabled; TXEN enabled; 
    USART0.CTRLB = 0xC0;
	
    // CMODE Asynchronous Mode; UCPHA enabled; UDORD disabled; CHSIZE Character size: 8 bit; PMODE No Parity; SBMODE 1 stop bit; 
    USART0.CTRLC = 0x3;
	
    //DBGRUN disabled; 
    USART0.DBGCTRL = 0x0;
	
    //IREI disabled; 
    USART0.EVCTRL = 0x0;
	
    //RXPL 0x0; 
    USART0.RXPLCTRL = 0x0;
	
    //TXPL 0x0; 
    USART0.TXPLCTRL = 0x0;
	
    USART0_FramingErrorCallbackRegister(USART0_DefaultFramingErrorCallback);
    USART0_OverrunErrorCallbackRegister(USART0_DefaultOverrunErrorCallback);
    USART0_ParityErrorCallbackRegister(USART0_DefaultParityErrorCallback);
    usart0RxLastError.status = 0;  
    usart0RxHead = 0;
    usart0RxTail = 0;
    usart0RxCount = 0;
    USART0.CTRLA |= USART_RXCIE_bm; 

}

void USART0_Deinitialize(void)
{
    USART0.CTRLA &= ~(USART_RXCIE_bm);    
    USART0.BAUD = 0x00;	
    USART0.CTRLA = 0x00;	
    USART0.CTRLB = 0x00;	
    USART0.CTRLC = 0x00;	
    USART0.DBGCTRL = 0x00;	
    USART0.EVCTRL = 0x00;	
    USART0.RXPLCTRL = 0x00;	
    USART0.TXPLCTRL = 0x00;	
}

void USART0_Enable(void)
{
    USART0.CTRLB |= USART_RXEN_bm | USART_TXEN_bm; 
}

void USART0_Disable(void)
{
    USART0.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm); 
}

void USART0_TransmitEnable(void)
{
    USART0.CTRLB |= USART_TXEN_bm; 
}

void USART0_TransmitDisable(void)
{
    USART0.CTRLB &= ~(USART_TXEN_bm); 
}

void USART0_ReceiveEnable(void)
{
    USART0.CTRLB |= USART_RXEN_bm ; 
}

void USART0_ReceiveDisable(void)
{
    USART0.CTRLB &= ~(USART_RXEN_bm); 
}

void USART0_AutoBaudSet(bool enable)
{
    if(enable)
    {
        USART0.CTRLB |= USART_RXMODE_gm & (0x02 << USART_RXMODE_gp); 
        USART0.STATUS |= USART_WFB_bm ; 
    }
    else
    {
       USART0.CTRLB &= ~(USART_RXMODE_gm); 
       USART0.STATUS &= ~(USART_BDF_bm);  
    }
}

bool USART0_AutoBaudQuery(void)
{
     return (bool)(USART0.STATUS & USART_BDF_bm) ; 
}

bool USART0_IsAutoBaudDetectError(void)
{
     return (bool)(USART0.STATUS & USART_ISFIF_bm) ; 
}

void USART0_AutoBaudDetectErrorReset(void)
{
    USART0.STATUS |= USART_ISFIF_bm ;
	USART0_AutoBaudSet(false);
    USART0_ReceiveDisable();
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    USART0_ReceiveEnable();
    USART0_AutoBaudSet(true);
}

void USART0_ReceiveInterruptEnable(void)
{
    USART0.CTRLA |= USART_RXCIE_bm ; 
}
void USART0_ReceiveInterruptDisable(void)
{
    USART0.CTRLA &= ~(USART_RXCIE_bm); 
}

bool USART0_IsRxReady(void)
{
    return (usart0RxCount ? true : false);
}

bool USART0_IsTxReady(void)
{
    return (bool)(USART0.STATUS & USART_DREIF_bm);
}

bool USART0_IsTxDone(void)
{
    return (bool)(USART0.STATUS & USART_TXCIF_bm);
}

size_t USART0_ErrorGet(void)
{
    usart0RxLastError.status = usart0RxStatusBuffer[usart0RxTail & USART0_RX_BUFFER_MASK].status;
    return usart0RxLastError.status;
}

uint8_t USART0_Read(void)
{
    uint8_t readValue  = 0;
    uint16_t tempRxTail;
    
    readValue = usart0RxBuffer[usart0RxTail];
    tempRxTail = (usart0RxTail + 1U) & USART0_RX_BUFFER_MASK; // Buffer size of RX should be in the 2^n  
    usart0RxTail = tempRxTail;
    USART0.CTRLA &= ~(USART_RXCIE_bm); 
    if(0U != usart0RxCount)
    {
        usart0RxCount--;
    }
    USART0.CTRLA |= USART_RXCIE_bm; 


    return readValue;
}

/* Interrupt service routine for RX complete */
/* cppcheck-suppress misra-c2012-2.7 */
/* cppcheck-suppress misra-c2012-8.4 */
ISR(USART0_RXC_vect)
/* cppcheck-suppress misra-c2012-5.5 */
{
    USART0_ReceiveISR();
}

void USART0_ReceiveISR(void)
{
    uint8_t regValue;
    uint16_t tempRxHead;
    
    usart0RxStatusBuffer[usart0RxHead].status = 0;

    if(USART_FERR_bm == (USART0.RXDATAH & USART_FERR_bm))
    {
        usart0RxStatusBuffer[usart0RxHead].ferr = 1;
        if(NULL != USART0_FramingErrorHandler)
        {
            USART0_FramingErrorHandler();
        } 
    }
    if(USART_PERR_bm == (USART0.RXDATAH & USART_PERR_bm))
    {
        usart0RxLastError.perr = 1;
        if(NULL != USART0_ParityErrorHandler)
        {
            USART0_ParityErrorHandler();
        }  
    }
    if(USART_BUFOVF_bm == (USART0.RXDATAH & USART_BUFOVF_bm))
    {
        usart0RxStatusBuffer[usart0RxHead].oerr = 1;
        if(NULL != USART0_OverrunErrorHandler)
        {
            USART0_OverrunErrorHandler();
        }   
    }    
    
    regValue = USART0.RXDATAL;
    
    tempRxHead = (usart0RxHead + 1U) & USART0_RX_BUFFER_MASK;// Buffer size of RX should be in the 2^n
    if (tempRxHead == usart0RxTail) {
		// ERROR! Receive buffer overflow 
	} 
    else
    {
        // Store received data in buffer 
		usart0RxBuffer[usart0RxHead] = regValue;
		usart0RxHead = tempRxHead;

		usart0RxCount++;
	}
    if (NULL != USART0_RxCompleteInterruptHandler)
    {
        (*USART0_RxCompleteInterruptHandler)();
    }
    
    else {
        // Do Nothing. Added for MISRA C Compliant.
    }
}

void USART0_Write(uint8_t txData)
{
    USART0.TXDATAL = txData;    // Write the data byte to the USART.
}
static void USART0_DefaultFramingErrorCallback(void)
{
    
}

static void USART0_DefaultOverrunErrorCallback(void)
{
    
}

static void USART0_DefaultParityErrorCallback(void)
{
    
}

void USART0_FramingErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        USART0_FramingErrorHandler = callbackHandler;
    }
}

void USART0_OverrunErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        USART0_OverrunErrorHandler = callbackHandler;
    }    
}

void USART0_ParityErrorCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
        USART0_ParityErrorHandler = callbackHandler;
    } 
}

void USART0_RxCompleteCallbackRegister(void (* callbackHandler)(void))
{
    if(NULL != callbackHandler)
    {
       USART0_RxCompleteInterruptHandler = callbackHandler; 
    }   
}



