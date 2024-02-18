/**
  * SPI0 Generated Driver File
  *
  * @file spi0.c
  *
  * @ingroup spi0
  *
  * @brief This file contains the driver code for the SPI0 module.
  *
  * @version SPI0 Driver Version 3.0.0
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

#include "../spi0.h"
#include "../spi_interrupt_types.h"


const struct SPI_INTERFACE SPI0_Host = 
{
    .Initialize = SPI0_Initialize,
    .Deinitialize = SPI0_Deinitialize,
    .Open = SPI0_Open,
    .Close = SPI0_Close,
    .BufferExchange = SPI0_BufferExchange,
    .BufferWrite = SPI0_BufferWrite,
    .BufferRead = SPI0_BufferRead,	
    .ByteExchange = SPI0_ByteExchange,
    .ByteWrite = SPI0_ByteWrite,
    .ByteRead = SPI0_ByteRead,
    .IsTxReady = SPI0_IsTxReady,
    .IsRxReady = SPI0_IsRxReady,
    .RxCompleteCallbackRegister = SPI0_RxCompleteCallbackRegister,
    .TxCompleteCallbackRegister = NULL
};

static void (*SPI0_RxCompleteCallback)(void);
void SPI0_ISR(void);

static spi_descriptor_t spi0_descriptor = 
{
    .buffer = NULL,
    .bufferLength = 0,
    .status = SPI_RESET
};

static const spi_configuration_t spi0_configuration[] = 
{
    { 0x27, 0xc4 },
    { 0x35, 0xC4 }
};

void SPI0_Initialize(void)
{
    
    SPI0.CTRLA = 0x00;
    SPI0.INTFLAGS = 0x00;
    SPI0.INTFLAGS = 0x00;
    SPI0.INTCTRL = 0x00;

    // Set Callback handler to NULL
    SPI0_RxCompleteCallbackRegister(NULL);
    spi0_descriptor.status = SPI_RESET;
}

void SPI0_Deinitialize(void)
{

    SPI0.CTRLA = 0x00;
    SPI0.CTRLB = 0x00;
    SPI0.INTFLAGS = 0x00;
    SPI0.INTCTRL = 0x00;

    spi0_descriptor.status = SPI_RESET;
}

bool SPI0_Open(uint8_t spiConfigIndex)
{
    bool returnValue = false;
    if (0 == (SPI0.CTRLA & SPI_ENABLE_bm)) 
    {
        //BUFEN enabled; BUFWR enabled; MODE 0; SSD enabled; 
        SPI0.CTRLB = spi0_configuration[spiConfigIndex].ctrlb;
        //CLK2X enabled; DORD disabled; ENABLE enabled; MASTER enabled; PRESC DIV64; 
        SPI0.CTRLA = spi0_configuration[spiConfigIndex].ctrla;
        
        spi0_descriptor.status = SPI_IDLE;
        returnValue = true;
    } 
    else 
    {
        returnValue = false;
    }
    return returnValue;
}

void SPI0_Close(void)
{

    SPI0.CTRLA = 0x00;
    SPI0.CTRLB = 0x00;
    SPI0.INTFLAGS = 0x00;
    SPI0.INTCTRL = 0x00;

    spi0_descriptor.status = SPI_RESET;    
}

void SPI0_RxCompleteCallbackRegister(void (* CallbackHandler)(void))
{
    SPI0_RxCompleteCallback = CallbackHandler;
}

uint8_t SPI0_ByteExchange(uint8_t byteData)
{
    while(SPI_IDLE != spi0_descriptor.status)
    { 
        ; // Wait until ongoing SPI transfer is completed
    }
    spi0_descriptor.buffer = (uint8_t*)&byteData;
    spi0_descriptor.bufferLength = 0;
    spi0_descriptor.transferType = SPI_READ;
    spi0_descriptor.status = SPI_BUSY;

    //DREIE disabled; IE disabled; RXCIE enabled; SSIE disabled; TXCIE disabled; 
    SPI0.INTCTRL = 0x80;
    SPI0.DATA = *spi0_descriptor.buffer;
    
    while (SPI_BUSY == spi0_descriptor.status)
    {
        ; // Wait until ongoing SPI transfer is completed
    }
    return byteData;
}

void SPI0_BufferExchange(void *bufferData, size_t bufferSize)
{
    if(SPI_IDLE == spi0_descriptor.status)
    {
        spi0_descriptor.buffer   = (uint8_t *)bufferData;
        spi0_descriptor.bufferLength   = bufferSize-(size_t)1;
        spi0_descriptor.transferType   = SPI_EXCHANGE;
        spi0_descriptor.status = SPI_BUSY;

        //DREIE disabled; IE disabled; RXCIE enabled; SSIE disabled; TXCIE disabled; 
        SPI0.INTCTRL = 0x80;
        SPI0.DATA = *spi0_descriptor.buffer;
    }
    else
    {
        ; // Exiting due to SPI transfer in progress
    }
}

void SPI0_BufferWrite(void *bufferData, size_t bufferSize)
{
    if(SPI_IDLE == spi0_descriptor.status)
    {
        spi0_descriptor.buffer   = (uint8_t *)bufferData;
        spi0_descriptor.bufferLength   = bufferSize-(size_t)1;
        spi0_descriptor.transferType   = SPI_WRITE;
        spi0_descriptor.status = SPI_BUSY;

        //DREIE disabled; IE disabled; RXCIE enabled; SSIE disabled; TXCIE disabled; 
        SPI0.INTCTRL = 0x80;
        SPI0.DATA = *spi0_descriptor.buffer;
    }
    else
    {
        ; // Exiting due to SPI transfer in progress 
    }
}

void SPI0_BufferRead(void *bufferData, size_t bufferSize)
{
    if(SPI_IDLE == spi0_descriptor.status)
    {
        spi0_descriptor.buffer   = (uint8_t *)bufferData;
        spi0_descriptor.bufferLength   = bufferSize-(size_t)1;
        spi0_descriptor.transferType   = SPI_READ;
        spi0_descriptor.status = SPI_BUSY;

        //DREIE disabled; IE disabled; RXCIE enabled; SSIE disabled; TXCIE disabled; 
        SPI0.INTCTRL = 0x80;
        SPI0.DATA = 0;
    }
    else
    {
        ; // Exiting due to SPI transfer in progress
    }
}

void SPI0_ByteWrite(uint8_t byteData)
{
    if(SPI_IDLE == spi0_descriptor.status)
    {
        SPI0.DATA = byteData;
    }
    else
    {
        ;
    }
}

uint8_t SPI0_ByteRead(void)
{   
    uint8_t readData = 0;
    if(SPI_IDLE == spi0_descriptor.status)
    {
        readData = SPI0.DATA;
    }
    else
    {
        ;
    } 
    return readData;  
}

bool SPI0_IsTxReady(void)
{
    bool returnValue = false;
    if(SPI_IDLE == spi0_descriptor.status)
    {
        returnValue = true;
    }
    else
    {
        returnValue = false;
    }
    return returnValue;
}

bool SPI0_IsRxReady(void)
{
    bool returnValue = false;
    if((SPI_IDLE == spi0_descriptor.status) && (0 != (SPI0.INTFLAGS & SPI_RXCIF_bm)))
    {
        returnValue = true;
    }
    else
    {
        returnValue = false;
    }
    return returnValue;
}

void SPI0_ISR(void)
{
    uint8_t readData = SPI0.DATA;
    uint8_t writeData = 0;

    // Clear interrupt flag
    SPI0.INTFLAGS |= SPI_RXCIF_bm;

    if((spi0_descriptor.bufferLength) > 0)
    {
        if (SPI_WRITE != spi0_descriptor.transferType) 
        {
            *spi0_descriptor.buffer = readData;
        }
        else
        {
            ; // Transfer type is not SPI_WRITE
        }
        spi0_descriptor.buffer++;

        if (SPI_READ != spi0_descriptor.transferType)
        {
            writeData = *spi0_descriptor.buffer;
        }
        else
        {
            ; // Transfer type is not SPI_READ
        }
        spi0_descriptor.bufferLength--;
        SPI0.DATA = writeData;
    }
    else
    {
        if ((SPI_WRITE != spi0_descriptor.transferType) && (SPI_BUSY == spi0_descriptor.status))
        {
            *spi0_descriptor.buffer = readData;
        }
        else
        {
            ;
        }
        spi0_descriptor.status = SPI_IDLE;
        SPI0.INTCTRL = 0x00;

        if (SPI0_RxCompleteCallback != NULL)
        {
            SPI0_RxCompleteCallback();
        }
        else
        {
            ; // No transfer complete callback defined
        }
    }
}

/* cppcheck-suppress misra-c2012-8.2 */
/* cppcheck-suppress misra-c2012-8.4 */
ISR(SPI0_INT_vect){
    SPI0_ISR();
}