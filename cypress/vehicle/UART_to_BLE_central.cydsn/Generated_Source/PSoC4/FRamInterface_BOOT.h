/***************************************************************************//**
* \file FRamInterface_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_FRamInterface_H)
#define CY_SCB_BOOT_FRamInterface_H

#include "FRamInterface_PVT.h"

#if (FRamInterface_SCB_MODE_I2C_INC)
    #include "FRamInterface_I2C.h"
#endif /* (FRamInterface_SCB_MODE_I2C_INC) */

#if (FRamInterface_SCB_MODE_EZI2C_INC)
    #include "FRamInterface_EZI2C.h"
#endif /* (FRamInterface_SCB_MODE_EZI2C_INC) */

#if (FRamInterface_SCB_MODE_SPI_INC || FRamInterface_SCB_MODE_UART_INC)
    #include "FRamInterface_SPI_UART.h"
#endif /* (FRamInterface_SCB_MODE_SPI_INC || FRamInterface_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define FRamInterface_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_FRamInterface) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (FRamInterface_SCB_MODE_I2C_INC)
    #define FRamInterface_I2C_BTLDR_COMM_ENABLED     (FRamInterface_BTLDR_COMM_ENABLED && \
                                                            (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             FRamInterface_I2C_SLAVE_CONST))
#else
     #define FRamInterface_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (FRamInterface_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (FRamInterface_SCB_MODE_EZI2C_INC)
    #define FRamInterface_EZI2C_BTLDR_COMM_ENABLED   (FRamInterface_BTLDR_COMM_ENABLED && \
                                                         FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define FRamInterface_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (FRamInterface_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (FRamInterface_SCB_MODE_SPI_INC)
    #define FRamInterface_SPI_BTLDR_COMM_ENABLED     (FRamInterface_BTLDR_COMM_ENABLED && \
                                                            (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             FRamInterface_SPI_SLAVE_CONST))
#else
        #define FRamInterface_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (FRamInterface_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (FRamInterface_SCB_MODE_UART_INC)
       #define FRamInterface_UART_BTLDR_COMM_ENABLED    (FRamInterface_BTLDR_COMM_ENABLED && \
                                                            (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (FRamInterface_UART_RX_DIRECTION && \
                                                              FRamInterface_UART_TX_DIRECTION)))
#else
     #define FRamInterface_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (FRamInterface_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define FRamInterface_BTLDR_COMM_MODE_ENABLED    (FRamInterface_I2C_BTLDR_COMM_ENABLED   || \
                                                     FRamInterface_SPI_BTLDR_COMM_ENABLED   || \
                                                     FRamInterface_EZI2C_BTLDR_COMM_ENABLED || \
                                                     FRamInterface_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void FRamInterface_I2CCyBtldrCommStart(void);
    void FRamInterface_I2CCyBtldrCommStop (void);
    void FRamInterface_I2CCyBtldrCommReset(void);
    cystatus FRamInterface_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus FRamInterface_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (FRamInterface_SCB_MODE_I2C_CONST_CFG)
        #define FRamInterface_CyBtldrCommStart   FRamInterface_I2CCyBtldrCommStart
        #define FRamInterface_CyBtldrCommStop    FRamInterface_I2CCyBtldrCommStop
        #define FRamInterface_CyBtldrCommReset   FRamInterface_I2CCyBtldrCommReset
        #define FRamInterface_CyBtldrCommRead    FRamInterface_I2CCyBtldrCommRead
        #define FRamInterface_CyBtldrCommWrite   FRamInterface_I2CCyBtldrCommWrite
    #endif /* (FRamInterface_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void FRamInterface_EzI2CCyBtldrCommStart(void);
    void FRamInterface_EzI2CCyBtldrCommStop (void);
    void FRamInterface_EzI2CCyBtldrCommReset(void);
    cystatus FRamInterface_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus FRamInterface_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (FRamInterface_SCB_MODE_EZI2C_CONST_CFG)
        #define FRamInterface_CyBtldrCommStart   FRamInterface_EzI2CCyBtldrCommStart
        #define FRamInterface_CyBtldrCommStop    FRamInterface_EzI2CCyBtldrCommStop
        #define FRamInterface_CyBtldrCommReset   FRamInterface_EzI2CCyBtldrCommReset
        #define FRamInterface_CyBtldrCommRead    FRamInterface_EzI2CCyBtldrCommRead
        #define FRamInterface_CyBtldrCommWrite   FRamInterface_EzI2CCyBtldrCommWrite
    #endif /* (FRamInterface_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void FRamInterface_SpiCyBtldrCommStart(void);
    void FRamInterface_SpiCyBtldrCommStop (void);
    void FRamInterface_SpiCyBtldrCommReset(void);
    cystatus FRamInterface_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus FRamInterface_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (FRamInterface_SCB_MODE_SPI_CONST_CFG)
        #define FRamInterface_CyBtldrCommStart   FRamInterface_SpiCyBtldrCommStart
        #define FRamInterface_CyBtldrCommStop    FRamInterface_SpiCyBtldrCommStop
        #define FRamInterface_CyBtldrCommReset   FRamInterface_SpiCyBtldrCommReset
        #define FRamInterface_CyBtldrCommRead    FRamInterface_SpiCyBtldrCommRead
        #define FRamInterface_CyBtldrCommWrite   FRamInterface_SpiCyBtldrCommWrite
    #endif /* (FRamInterface_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void FRamInterface_UartCyBtldrCommStart(void);
    void FRamInterface_UartCyBtldrCommStop (void);
    void FRamInterface_UartCyBtldrCommReset(void);
    cystatus FRamInterface_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus FRamInterface_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (FRamInterface_SCB_MODE_UART_CONST_CFG)
        #define FRamInterface_CyBtldrCommStart   FRamInterface_UartCyBtldrCommStart
        #define FRamInterface_CyBtldrCommStop    FRamInterface_UartCyBtldrCommStop
        #define FRamInterface_CyBtldrCommReset   FRamInterface_UartCyBtldrCommReset
        #define FRamInterface_CyBtldrCommRead    FRamInterface_UartCyBtldrCommRead
        #define FRamInterface_CyBtldrCommWrite   FRamInterface_UartCyBtldrCommWrite
    #endif /* (FRamInterface_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_BTLDR_COMM_ENABLED)
    #if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void FRamInterface_CyBtldrCommStart(void);
        void FRamInterface_CyBtldrCommStop (void);
        void FRamInterface_CyBtldrCommReset(void);
        cystatus FRamInterface_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus FRamInterface_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_FRamInterface)
        #define CyBtldrCommStart    FRamInterface_CyBtldrCommStart
        #define CyBtldrCommStop     FRamInterface_CyBtldrCommStop
        #define CyBtldrCommReset    FRamInterface_CyBtldrCommReset
        #define CyBtldrCommWrite    FRamInterface_CyBtldrCommWrite
        #define CyBtldrCommRead     FRamInterface_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_FRamInterface) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (FRamInterface_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define FRamInterface_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define FRamInterface_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define FRamInterface_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define FRamInterface_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef FRamInterface_SPI_BYTE_TO_BYTE
    #define FRamInterface_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef FRamInterface_UART_BYTE_TO_BYTE
    #define FRamInterface_UART_BYTE_TO_BYTE  (2500u)
#endif /* FRamInterface_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_FRamInterface_H) */


/* [] END OF FILE */
