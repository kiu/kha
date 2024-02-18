/**
 * SPI Type Definitions Header File
 *
 * @file spi_interrupt_types.h
 *
 * @defgroup spi SPI
 *
 * @brief This header file provides type definitions for the SPI module operation in Interrupt mode.
 *
 * @version SPI Driver Version 3.0.0
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

#ifndef SPI_INTERRUPT_TYPES_H
#define	SPI_INTERRUPT_TYPES_H

/**
 * @ingroup spi
 * @typedef enum spi_status_t
 * @brief Enumeration for the different states of the SPI module.
 * @note The enum values are chosen with a specific bit pattern to make sure no error happens in case a single bit changes.
 */
typedef enum
{
    SPI_RESET = 0x00U,  /**< SPI module is in Reset state */
    SPI_IDLE  = 0x81U,  /**< SPI module is ready to use*/
    SPI_BUSY  = 0x42U   /**< SPI module is in use */
}spi_status_t;

/**
 * @ingroup spi
 * @typedef enum spi_transfer_type_t
 * @brief Enumeration for the different transfer types of the SPI module.
 * @note The enum values are chosen with a specific bit pattern to make sure no error happens in case a single bit changes.
 */
typedef enum
{
    SPI_READ     = 0x00U,   /**< SPI Module is performing a read operation */
    SPI_WRITE    = 0x81U,   /**< SPI Module is performing a write operation */
    SPI_EXCHANGE = 0X42U    /**< SPI Module is performing a exchange operation */
}spi_transfer_type_t;

/**
 * @ingroup spi
 * @typedef struct spi_descriptor_t
 * @brief Transfer information for current transaction.
 */
typedef volatile struct
{ 
    uint8_t* buffer;                    // Pointer to SPI buffer
    size_t bufferLength;                // Stores number of bytes that needs to be processed
    spi_transfer_type_t transferType;   // Type of SPI API being run at the moment
    spi_status_t status;                // Indicates if SPI driver is still completing a requested transaction
} spi_descriptor_t;

/**
 * @ingroup spi
 * @typedef struct spi_configuration_t
 * @brief Holds register configurations for SPI module.
 */
typedef struct 
{  
    uint8_t ctrla;
    uint8_t ctrlb;
} spi_configuration_t;

#endif /* SPI_INTERRUPT_TYPES_H */
