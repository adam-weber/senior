/***************************************************************************//**
* \file FRamInterface_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "FRamInterface.h"
#include "FRamInterface_PVT.h"

#if(FRamInterface_SCB_MODE_I2C_INC)
    #include "FRamInterface_I2C_PVT.h"
#endif /* (FRamInterface_SCB_MODE_I2C_INC) */

#if(FRamInterface_SCB_MODE_EZI2C_INC)
    #include "FRamInterface_EZI2C_PVT.h"
#endif /* (FRamInterface_SCB_MODE_EZI2C_INC) */

#if(FRamInterface_SCB_MODE_SPI_INC || FRamInterface_SCB_MODE_UART_INC)
    #include "FRamInterface_SPI_UART_PVT.h"
#endif /* (FRamInterface_SCB_MODE_SPI_INC || FRamInterface_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG || \
   (FRamInterface_SCB_MODE_I2C_CONST_CFG   && (!FRamInterface_I2C_WAKE_ENABLE_CONST))   || \
   (FRamInterface_SCB_MODE_EZI2C_CONST_CFG && (!FRamInterface_EZI2C_WAKE_ENABLE_CONST)) || \
   (FRamInterface_SCB_MODE_SPI_CONST_CFG   && (!FRamInterface_SPI_WAKE_ENABLE_CONST))   || \
   (FRamInterface_SCB_MODE_UART_CONST_CFG  && (!FRamInterface_UART_WAKE_ENABLE_CONST)))

    FRamInterface_BACKUP_STRUCT FRamInterface_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: FRamInterface_Sleep
****************************************************************************//**
*
*  Prepares the FRamInterface component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the FRamInterface_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void FRamInterface_Sleep(void)
{
#if(FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)

    if(FRamInterface_SCB_WAKE_ENABLE_CHECK)
    {
        if(FRamInterface_SCB_MODE_I2C_RUNTM_CFG)
        {
            FRamInterface_I2CSaveConfig();
        }
        else if(FRamInterface_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            FRamInterface_EzI2CSaveConfig();
        }
    #if(!FRamInterface_CY_SCBIP_V1)
        else if(FRamInterface_SCB_MODE_SPI_RUNTM_CFG)
        {
            FRamInterface_SpiSaveConfig();
        }
        else if(FRamInterface_SCB_MODE_UART_RUNTM_CFG)
        {
            FRamInterface_UartSaveConfig();
        }
    #endif /* (!FRamInterface_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        FRamInterface_backup.enableState = (uint8) FRamInterface_GET_CTRL_ENABLED;

        if(0u != FRamInterface_backup.enableState)
        {
            FRamInterface_Stop();
        }
    }

#else

    #if (FRamInterface_SCB_MODE_I2C_CONST_CFG && FRamInterface_I2C_WAKE_ENABLE_CONST)
        FRamInterface_I2CSaveConfig();

    #elif (FRamInterface_SCB_MODE_EZI2C_CONST_CFG && FRamInterface_EZI2C_WAKE_ENABLE_CONST)
        FRamInterface_EzI2CSaveConfig();

    #elif (FRamInterface_SCB_MODE_SPI_CONST_CFG && FRamInterface_SPI_WAKE_ENABLE_CONST)
        FRamInterface_SpiSaveConfig();

    #elif (FRamInterface_SCB_MODE_UART_CONST_CFG && FRamInterface_UART_WAKE_ENABLE_CONST)
        FRamInterface_UartSaveConfig();

    #else

        FRamInterface_backup.enableState = (uint8) FRamInterface_GET_CTRL_ENABLED;

        if(0u != FRamInterface_backup.enableState)
        {
            FRamInterface_Stop();
        }

    #endif /* defined (FRamInterface_SCB_MODE_I2C_CONST_CFG) && (FRamInterface_I2C_WAKE_ENABLE_CONST) */

#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: FRamInterface_Wakeup
****************************************************************************//**
*
*  Prepares the FRamInterface component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the FRamInterface_Wakeup() function without first calling the 
*   FRamInterface_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void FRamInterface_Wakeup(void)
{
#if(FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)

    if(FRamInterface_SCB_WAKE_ENABLE_CHECK)
    {
        if(FRamInterface_SCB_MODE_I2C_RUNTM_CFG)
        {
            FRamInterface_I2CRestoreConfig();
        }
        else if(FRamInterface_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            FRamInterface_EzI2CRestoreConfig();
        }
    #if(!FRamInterface_CY_SCBIP_V1)
        else if(FRamInterface_SCB_MODE_SPI_RUNTM_CFG)
        {
            FRamInterface_SpiRestoreConfig();
        }
        else if(FRamInterface_SCB_MODE_UART_RUNTM_CFG)
        {
            FRamInterface_UartRestoreConfig();
        }
    #endif /* (!FRamInterface_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != FRamInterface_backup.enableState)
        {
            FRamInterface_Enable();
        }
    }

#else

    #if (FRamInterface_SCB_MODE_I2C_CONST_CFG  && FRamInterface_I2C_WAKE_ENABLE_CONST)
        FRamInterface_I2CRestoreConfig();

    #elif (FRamInterface_SCB_MODE_EZI2C_CONST_CFG && FRamInterface_EZI2C_WAKE_ENABLE_CONST)
        FRamInterface_EzI2CRestoreConfig();

    #elif (FRamInterface_SCB_MODE_SPI_CONST_CFG && FRamInterface_SPI_WAKE_ENABLE_CONST)
        FRamInterface_SpiRestoreConfig();

    #elif (FRamInterface_SCB_MODE_UART_CONST_CFG && FRamInterface_UART_WAKE_ENABLE_CONST)
        FRamInterface_UartRestoreConfig();

    #else

        if(0u != FRamInterface_backup.enableState)
        {
            FRamInterface_Enable();
        }

    #endif /* (FRamInterface_I2C_WAKE_ENABLE_CONST) */

#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
