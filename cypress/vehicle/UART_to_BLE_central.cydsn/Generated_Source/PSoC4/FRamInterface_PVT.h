/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_FRamInterface_H)
#define CY_SCB_PVT_FRamInterface_H

#include "FRamInterface.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define FRamInterface_SetI2CExtClkInterruptMode(interruptMask) FRamInterface_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define FRamInterface_ClearI2CExtClkInterruptSource(interruptMask) FRamInterface_CLEAR_INTR_I2C_EC(interruptMask)
#define FRamInterface_GetI2CExtClkInterruptSource()                (FRamInterface_INTR_I2C_EC_REG)
#define FRamInterface_GetI2CExtClkInterruptMode()                  (FRamInterface_INTR_I2C_EC_MASK_REG)
#define FRamInterface_GetI2CExtClkInterruptSourceMasked()          (FRamInterface_INTR_I2C_EC_MASKED_REG)

#if (!FRamInterface_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define FRamInterface_SetSpiExtClkInterruptMode(interruptMask) \
                                                                FRamInterface_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define FRamInterface_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                FRamInterface_CLEAR_INTR_SPI_EC(interruptMask)
    #define FRamInterface_GetExtSpiClkInterruptSource()                 (FRamInterface_INTR_SPI_EC_REG)
    #define FRamInterface_GetExtSpiClkInterruptMode()                   (FRamInterface_INTR_SPI_EC_MASK_REG)
    #define FRamInterface_GetExtSpiClkInterruptSourceMasked()           (FRamInterface_INTR_SPI_EC_MASKED_REG)
#endif /* (!FRamInterface_CY_SCBIP_V1) */

#if(FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void FRamInterface_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (FRamInterface_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_FRamInterface_CUSTOM_INTR_HANDLER)
    extern cyisraddress FRamInterface_customIntrHandler;
#endif /* !defined (CY_REMOVE_FRamInterface_CUSTOM_INTR_HANDLER) */
#endif /* (FRamInterface_SCB_IRQ_INTERNAL) */

extern FRamInterface_BACKUP_STRUCT FRamInterface_backup;

#if(FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 FRamInterface_scbMode;
    extern uint8 FRamInterface_scbEnableWake;
    extern uint8 FRamInterface_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 FRamInterface_mode;
    extern uint8 FRamInterface_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * FRamInterface_rxBuffer;
    extern uint8   FRamInterface_rxDataBits;
    extern uint32  FRamInterface_rxBufferSize;

    extern volatile uint8 * FRamInterface_txBuffer;
    extern uint8   FRamInterface_txDataBits;
    extern uint32  FRamInterface_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 FRamInterface_numberOfAddr;
    extern uint8 FRamInterface_subAddrSize;
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (FRamInterface_SCB_MODE_I2C_CONST_CFG || \
        FRamInterface_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 FRamInterface_IntrTxMask;
#endif /* (! (FRamInterface_SCB_MODE_I2C_CONST_CFG || \
              FRamInterface_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define FRamInterface_SCB_MODE_I2C_RUNTM_CFG     (FRamInterface_SCB_MODE_I2C      == FRamInterface_scbMode)
    #define FRamInterface_SCB_MODE_SPI_RUNTM_CFG     (FRamInterface_SCB_MODE_SPI      == FRamInterface_scbMode)
    #define FRamInterface_SCB_MODE_UART_RUNTM_CFG    (FRamInterface_SCB_MODE_UART     == FRamInterface_scbMode)
    #define FRamInterface_SCB_MODE_EZI2C_RUNTM_CFG   (FRamInterface_SCB_MODE_EZI2C    == FRamInterface_scbMode)
    #define FRamInterface_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (FRamInterface_SCB_MODE_UNCONFIG == FRamInterface_scbMode)

    /* Defines wakeup enable */
    #define FRamInterface_SCB_WAKE_ENABLE_CHECK       (0u != FRamInterface_scbEnableWake)
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!FRamInterface_CY_SCBIP_V1)
    #define FRamInterface_SCB_PINS_NUMBER    (7u)
#else
    #define FRamInterface_SCB_PINS_NUMBER    (2u)
#endif /* (!FRamInterface_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_FRamInterface_H) */


/* [] END OF FILE */
