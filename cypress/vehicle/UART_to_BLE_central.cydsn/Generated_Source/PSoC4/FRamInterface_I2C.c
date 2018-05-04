/***************************************************************************//**
* \file FRamInterface_I2C.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "FRamInterface_PVT.h"
#include "FRamInterface_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 FRamInterface_state;  /* Current state of I2C FSM */

#if(FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const FRamInterface_I2C_INIT_STRUCT FRamInterface_configI2C =
    {
        FRamInterface_I2C_MODE,
        FRamInterface_I2C_OVS_FACTOR_LOW,
        FRamInterface_I2C_OVS_FACTOR_HIGH,
        FRamInterface_I2C_MEDIAN_FILTER_ENABLE,
        FRamInterface_I2C_SLAVE_ADDRESS,
        FRamInterface_I2C_SLAVE_ADDRESS_MASK,
        FRamInterface_I2C_ACCEPT_ADDRESS,
        FRamInterface_I2C_WAKE_ENABLE,
        FRamInterface_I2C_BYTE_MODE_ENABLE,
        FRamInterface_I2C_DATA_RATE,
        FRamInterface_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: FRamInterface_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the FRamInterface for I2C operation.
    *
    *  This function is intended specifically to be used when the FRamInterface 
    *  configuration is set to “Unconfigured FRamInterface” in the customizer. 
    *  After initializing the FRamInterface in I2C mode using this function, 
    *  the component can be enabled using the FRamInterface_Start() or 
    * FRamInterface_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void FRamInterface_I2CInit(const FRamInterface_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            FRamInterface_SetPins(FRamInterface_SCB_MODE_I2C, FRamInterface_DUMMY_PARAM,
                                     FRamInterface_DUMMY_PARAM);

            /* Store internal configuration */
            FRamInterface_scbMode       = (uint8) FRamInterface_SCB_MODE_I2C;
            FRamInterface_scbEnableWake = (uint8) config->enableWake;
            FRamInterface_scbEnableIntr = (uint8) FRamInterface_SCB_IRQ_INTERNAL;

            FRamInterface_mode          = (uint8) config->mode;
            FRamInterface_acceptAddr    = (uint8) config->acceptAddr;

        #if (FRamInterface_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            FRamInterface_SET_I2C_CFG_SDA_FILT_TRIM(FRamInterface_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (FRamInterface_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((FRamInterface_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= FRamInterface_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (FRamInterface_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                FRamInterface_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = FRamInterface_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                FRamInterface_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = FRamInterface_DIGITAL_FILTER_ENABLE;
            }

        #if (!FRamInterface_CY_SCBIP_V0)
            locEnableWake = (FRamInterface_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!FRamInterface_CY_SCBIP_V0) */

            /* Configure I2C interface */
            FRamInterface_CTRL_REG     = FRamInterface_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            FRamInterface_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            FRamInterface_GET_CTRL_EC_AM_MODE (locEnableWake);

            FRamInterface_I2C_CTRL_REG = FRamInterface_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    FRamInterface_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    FRamInterface_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    FRamInterface_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            FRamInterface_RX_CTRL_REG      = FRamInterface_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                FRamInterface_I2C_RX_CTRL;
            FRamInterface_RX_FIFO_CTRL_REG = FRamInterface_CLEAR_REG;

            /* Set default address and mask */
            FRamInterface_RX_MATCH_REG    = ((FRamInterface_I2C_SLAVE) ?
                                                (FRamInterface_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 FRamInterface_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (FRamInterface_CLEAR_REG));


            /* Configure TX direction */
            FRamInterface_TX_CTRL_REG      = FRamInterface_I2C_TX_CTRL;
            FRamInterface_TX_FIFO_CTRL_REG = FRamInterface_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (FRamInterface_ISR_NUMBER);
            CyIntSetPriority(FRamInterface_ISR_NUMBER, FRamInterface_ISR_PRIORITY);
            (void) CyIntSetVector(FRamInterface_ISR_NUMBER, &FRamInterface_I2C_ISR);

            /* Configure interrupt sources */
        #if(!FRamInterface_CY_SCBIP_V1)
            FRamInterface_INTR_SPI_EC_MASK_REG = FRamInterface_NO_INTR_SOURCES;
        #endif /* (!FRamInterface_CY_SCBIP_V1) */

            FRamInterface_INTR_I2C_EC_MASK_REG = FRamInterface_NO_INTR_SOURCES;
            FRamInterface_INTR_RX_MASK_REG     = FRamInterface_NO_INTR_SOURCES;
            FRamInterface_INTR_TX_MASK_REG     = FRamInterface_NO_INTR_SOURCES;

            FRamInterface_INTR_SLAVE_MASK_REG  = ((FRamInterface_I2C_SLAVE) ?
                            (FRamInterface_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             FRamInterface_I2C_INTR_SLAVE_MASK) : (FRamInterface_CLEAR_REG));

            FRamInterface_INTR_MASTER_MASK_REG = FRamInterface_NO_INTR_SOURCES;

            /* Configure global variables */
            FRamInterface_state = FRamInterface_I2C_FSM_IDLE;

            /* Internal slave variables */
            FRamInterface_slStatus        = 0u;
            FRamInterface_slRdBufIndex    = 0u;
            FRamInterface_slWrBufIndex    = 0u;
            FRamInterface_slOverFlowCount = 0u;

            /* Internal master variables */
            FRamInterface_mstrStatus     = 0u;
            FRamInterface_mstrRdBufIndex = 0u;
            FRamInterface_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: FRamInterface_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void FRamInterface_I2CInit(void)
    {
    #if(FRamInterface_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        FRamInterface_SET_I2C_CFG_SDA_FILT_TRIM(FRamInterface_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (FRamInterface_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        FRamInterface_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        FRamInterface_CTRL_REG     = FRamInterface_I2C_DEFAULT_CTRL;
        FRamInterface_I2C_CTRL_REG = FRamInterface_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        FRamInterface_RX_CTRL_REG      = FRamInterface_I2C_DEFAULT_RX_CTRL;
        FRamInterface_RX_FIFO_CTRL_REG = FRamInterface_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        FRamInterface_RX_MATCH_REG     = FRamInterface_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        FRamInterface_TX_CTRL_REG      = FRamInterface_I2C_DEFAULT_TX_CTRL;
        FRamInterface_TX_FIFO_CTRL_REG = FRamInterface_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (FRamInterface_ISR_NUMBER);
        CyIntSetPriority(FRamInterface_ISR_NUMBER, FRamInterface_ISR_PRIORITY);
    #if(!FRamInterface_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(FRamInterface_ISR_NUMBER, &FRamInterface_I2C_ISR);
    #endif /* (FRamInterface_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!FRamInterface_CY_SCBIP_V1)
        FRamInterface_INTR_SPI_EC_MASK_REG = FRamInterface_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!FRamInterface_CY_SCBIP_V1) */

        FRamInterface_INTR_I2C_EC_MASK_REG = FRamInterface_I2C_DEFAULT_INTR_I2C_EC_MASK;
        FRamInterface_INTR_SLAVE_MASK_REG  = FRamInterface_I2C_DEFAULT_INTR_SLAVE_MASK;
        FRamInterface_INTR_MASTER_MASK_REG = FRamInterface_I2C_DEFAULT_INTR_MASTER_MASK;
        FRamInterface_INTR_RX_MASK_REG     = FRamInterface_I2C_DEFAULT_INTR_RX_MASK;
        FRamInterface_INTR_TX_MASK_REG     = FRamInterface_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        FRamInterface_state = FRamInterface_I2C_FSM_IDLE;

    #if(FRamInterface_I2C_SLAVE)
        /* Internal slave variable */
        FRamInterface_slStatus        = 0u;
        FRamInterface_slRdBufIndex    = 0u;
        FRamInterface_slWrBufIndex    = 0u;
        FRamInterface_slOverFlowCount = 0u;
    #endif /* (FRamInterface_I2C_SLAVE) */

    #if(FRamInterface_I2C_MASTER)
    /* Internal master variable */
        FRamInterface_mstrStatus     = 0u;
        FRamInterface_mstrRdBufIndex = 0u;
        FRamInterface_mstrWrBufIndex = 0u;
    #endif /* (FRamInterface_I2C_MASTER) */
    }
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: FRamInterface_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void FRamInterface_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    FRamInterface_I2C_MASTER_CMD_REG = 0u;
    FRamInterface_I2C_SLAVE_CMD_REG  = 0u;
    
    FRamInterface_state = FRamInterface_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: FRamInterface_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void FRamInterface_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    FRamInterface_CTRL_REG &= (uint32) ~FRamInterface_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    FRamInterface_I2C_MASTER_CMD_REG = 0u;
    FRamInterface_I2C_SLAVE_CMD_REG  = 0u;

    FRamInterface_DISABLE_AUTO_DATA;

    FRamInterface_SetTxInterruptMode(FRamInterface_NO_INTR_SOURCES);
    FRamInterface_SetRxInterruptMode(FRamInterface_NO_INTR_SOURCES);
    
#if(FRamInterface_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    FRamInterface_ClearTxInterruptSource    (FRamInterface_INTR_TX_ALL);
    FRamInterface_ClearRxInterruptSource    (FRamInterface_INTR_RX_ALL);
    FRamInterface_ClearSlaveInterruptSource (FRamInterface_INTR_SLAVE_ALL);
    FRamInterface_ClearMasterInterruptSource(FRamInterface_INTR_MASTER_ALL);
#endif /* (FRamInterface_CY_SCBIP_V0) */

    FRamInterface_state = FRamInterface_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    FRamInterface_CTRL_REG |= (uint32) FRamInterface_CTRL_ENABLED;
}


#if(FRamInterface_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: FRamInterface_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables FRamInterface_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void FRamInterface_I2CSaveConfig(void)
    {
    #if (!FRamInterface_CY_SCBIP_V0)
        #if (FRamInterface_I2C_MULTI_MASTER_SLAVE_CONST && FRamInterface_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (FRamInterface_CTRL_REG & FRamInterface_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                FRamInterface_Stop();
                FRamInterface_CTRL_REG |= FRamInterface_CTRL_EC_AM_MODE;
                FRamInterface_Enable();
            }
        #endif /* (FRamInterface_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (FRamInterface_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            FRamInterface_SCBCLK_Stop();
        #endif /* (FRamInterface_SCB_CLK_INTERNAL) */
    #endif /* (!FRamInterface_CY_SCBIP_V0) */

        FRamInterface_SetI2CExtClkInterruptMode(FRamInterface_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: FRamInterface_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables FRamInterface_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void FRamInterface_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        FRamInterface_SetI2CExtClkInterruptMode(FRamInterface_NO_INTR_SOURCES);

    #if (!FRamInterface_CY_SCBIP_V0)
        #if (FRamInterface_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            FRamInterface_SCBCLK_Start();
        #endif /* (FRamInterface_SCB_CLK_INTERNAL) */
    #endif /* (!FRamInterface_CY_SCBIP_V0) */
    }
#endif /* (FRamInterface_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
