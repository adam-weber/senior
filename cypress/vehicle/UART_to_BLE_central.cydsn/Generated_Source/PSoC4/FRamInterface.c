/***************************************************************************//**
* \file FRamInterface.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (FRamInterface_SCB_MODE_I2C_INC)
    #include "FRamInterface_I2C_PVT.h"
#endif /* (FRamInterface_SCB_MODE_I2C_INC) */

#if (FRamInterface_SCB_MODE_EZI2C_INC)
    #include "FRamInterface_EZI2C_PVT.h"
#endif /* (FRamInterface_SCB_MODE_EZI2C_INC) */

#if (FRamInterface_SCB_MODE_SPI_INC || FRamInterface_SCB_MODE_UART_INC)
    #include "FRamInterface_SPI_UART_PVT.h"
#endif /* (FRamInterface_SCB_MODE_SPI_INC || FRamInterface_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 FRamInterface_scbMode = FRamInterface_SCB_MODE_UNCONFIG;
    uint8 FRamInterface_scbEnableWake;
    uint8 FRamInterface_scbEnableIntr;

    /* I2C configuration variables */
    uint8 FRamInterface_mode;
    uint8 FRamInterface_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * FRamInterface_rxBuffer;
    uint8  FRamInterface_rxDataBits;
    uint32 FRamInterface_rxBufferSize;

    volatile uint8 * FRamInterface_txBuffer;
    uint8  FRamInterface_txDataBits;
    uint32 FRamInterface_txBufferSize;

    /* EZI2C configuration variables */
    uint8 FRamInterface_numberOfAddr;
    uint8 FRamInterface_subAddrSize;
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** FRamInterface_initVar indicates whether the FRamInterface 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the FRamInterface_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  FRamInterface_Init() function can be called before the 
*  FRamInterface_Start() or FRamInterface_Enable() function.
*/
uint8 FRamInterface_initVar = 0u;


#if (! (FRamInterface_SCB_MODE_I2C_CONST_CFG || \
        FRamInterface_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * FRamInterface_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent FRamInterface_Enable() call.
    */
    uint16 FRamInterface_IntrTxMask = 0u;
#endif /* (! (FRamInterface_SCB_MODE_I2C_CONST_CFG || \
              FRamInterface_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (FRamInterface_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_FRamInterface_CUSTOM_INTR_HANDLER)
    void (*FRamInterface_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_FRamInterface_CUSTOM_INTR_HANDLER) */
#endif /* (FRamInterface_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void FRamInterface_ScbEnableIntr(void);
static void FRamInterface_ScbModeStop(void);
static void FRamInterface_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: FRamInterface_Init
****************************************************************************//**
*
*  Initializes the FRamInterface component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  FRamInterface_I2CInit, FRamInterface_SpiInit, 
*  FRamInterface_UartInit or FRamInterface_EzI2CInit.
*
*******************************************************************************/
void FRamInterface_Init(void)
{
#if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    if (FRamInterface_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        FRamInterface_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (FRamInterface_SCB_MODE_I2C_CONST_CFG)
    FRamInterface_I2CInit();

#elif (FRamInterface_SCB_MODE_SPI_CONST_CFG)
    FRamInterface_SpiInit();

#elif (FRamInterface_SCB_MODE_UART_CONST_CFG)
    FRamInterface_UartInit();

#elif (FRamInterface_SCB_MODE_EZI2C_CONST_CFG)
    FRamInterface_EzI2CInit();

#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: FRamInterface_Enable
****************************************************************************//**
*
*  Enables FRamInterface component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  FRamInterface_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The FRamInterface configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured FRamInterface”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void FRamInterface_Enable(void)
{
#if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!FRamInterface_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        FRamInterface_CTRL_REG |= FRamInterface_CTRL_ENABLED;

        FRamInterface_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        FRamInterface_ScbModePostEnable();
    }
#else
    FRamInterface_CTRL_REG |= FRamInterface_CTRL_ENABLED;

    FRamInterface_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    FRamInterface_ScbModePostEnable();
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: FRamInterface_Start
****************************************************************************//**
*
*  Invokes FRamInterface_Init() and FRamInterface_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  FRamInterface_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void FRamInterface_Start(void)
{
    if (0u == FRamInterface_initVar)
    {
        FRamInterface_Init();
        FRamInterface_initVar = 1u; /* Component was initialized */
    }

    FRamInterface_Enable();
}


/*******************************************************************************
* Function Name: FRamInterface_Stop
****************************************************************************//**
*
*  Disables the FRamInterface component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function FRamInterface_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void FRamInterface_Stop(void)
{
#if (FRamInterface_SCB_IRQ_INTERNAL)
    FRamInterface_DisableInt();
#endif /* (FRamInterface_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    FRamInterface_ScbModeStop();

    /* Disable SCB IP */
    FRamInterface_CTRL_REG &= (uint32) ~FRamInterface_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    FRamInterface_SetTxInterruptMode(FRamInterface_NO_INTR_SOURCES);

#if (FRamInterface_SCB_IRQ_INTERNAL)
    FRamInterface_ClearPendingInt();
#endif /* (FRamInterface_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: FRamInterface_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void FRamInterface_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = FRamInterface_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~FRamInterface_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (FRamInterface_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    FRamInterface_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: FRamInterface_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void FRamInterface_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = FRamInterface_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~FRamInterface_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (FRamInterface_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    FRamInterface_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (FRamInterface_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: FRamInterface_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void FRamInterface_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_FRamInterface_CUSTOM_INTR_HANDLER)
        FRamInterface_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_FRamInterface_CUSTOM_INTR_HANDLER) */
    }
#endif /* (FRamInterface_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: FRamInterface_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void FRamInterface_ScbEnableIntr(void)
{
#if (FRamInterface_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != FRamInterface_scbEnableIntr)
        {
            FRamInterface_EnableInt();
        }

    #else
        FRamInterface_EnableInt();

    #endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (FRamInterface_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: FRamInterface_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void FRamInterface_ScbModePostEnable(void)
{
#if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!FRamInterface_CY_SCBIP_V1)
    if (FRamInterface_SCB_MODE_SPI_RUNTM_CFG)
    {
        FRamInterface_SpiPostEnable();
    }
    else if (FRamInterface_SCB_MODE_UART_RUNTM_CFG)
    {
        FRamInterface_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!FRamInterface_CY_SCBIP_V1) */

#elif (FRamInterface_SCB_MODE_SPI_CONST_CFG)
    FRamInterface_SpiPostEnable();

#elif (FRamInterface_SCB_MODE_UART_CONST_CFG)
    FRamInterface_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: FRamInterface_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void FRamInterface_ScbModeStop(void)
{
#if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    if (FRamInterface_SCB_MODE_I2C_RUNTM_CFG)
    {
        FRamInterface_I2CStop();
    }
    else if (FRamInterface_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        FRamInterface_EzI2CStop();
    }
#if (!FRamInterface_CY_SCBIP_V1)
    else if (FRamInterface_SCB_MODE_SPI_RUNTM_CFG)
    {
        FRamInterface_SpiStop();
    }
    else if (FRamInterface_SCB_MODE_UART_RUNTM_CFG)
    {
        FRamInterface_UartStop();
    }
#endif /* (!FRamInterface_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (FRamInterface_SCB_MODE_I2C_CONST_CFG)
    FRamInterface_I2CStop();

#elif (FRamInterface_SCB_MODE_EZI2C_CONST_CFG)
    FRamInterface_EzI2CStop();

#elif (FRamInterface_SCB_MODE_SPI_CONST_CFG)
    FRamInterface_SpiStop();

#elif (FRamInterface_SCB_MODE_UART_CONST_CFG)
    FRamInterface_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: FRamInterface_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void FRamInterface_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[FRamInterface_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!FRamInterface_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!FRamInterface_CY_SCBIP_V1) */
        
        uint32 hsiomSel[FRamInterface_SCB_PINS_NUMBER] = 
        {
            FRamInterface_RX_SDA_MOSI_HSIOM_SEL_GPIO,
            FRamInterface_TX_SCL_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (FRamInterface_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (FRamInterface_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < FRamInterface_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = FRamInterface_PIN_DM_ALG_HIZ;
        }

        if ((FRamInterface_SCB_MODE_I2C   == mode) ||
            (FRamInterface_SCB_MODE_EZI2C == mode))
        {
        #if (FRamInterface_RX_SDA_MOSI_PIN)
            hsiomSel[FRamInterface_RX_SDA_MOSI_PIN_INDEX] = FRamInterface_RX_SDA_MOSI_HSIOM_SEL_I2C;
            pinsDm  [FRamInterface_RX_SDA_MOSI_PIN_INDEX] = FRamInterface_PIN_DM_OD_LO;
        #elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
            hsiomSel[FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX] = FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_SEL_I2C;
            pinsDm  [FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX] = FRamInterface_PIN_DM_OD_LO;
        #else
        #endif /* (FRamInterface_RX_SDA_MOSI_PIN) */
        
        #if (FRamInterface_TX_SCL_MISO_PIN)
            hsiomSel[FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_TX_SCL_MISO_HSIOM_SEL_I2C;
            pinsDm  [FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_PIN_DM_OD_LO;
        #endif /* (FRamInterface_TX_SCL_MISO_PIN) */
        }
    #if (!FRamInterface_CY_SCBIP_V1)
        else if (FRamInterface_SCB_MODE_SPI == mode)
        {
        #if (FRamInterface_RX_SDA_MOSI_PIN)
            hsiomSel[FRamInterface_RX_SDA_MOSI_PIN_INDEX] = FRamInterface_RX_SDA_MOSI_HSIOM_SEL_SPI;
        #elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
            hsiomSel[FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX] = FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (FRamInterface_RX_SDA_MOSI_PIN) */
        
        #if (FRamInterface_TX_SCL_MISO_PIN)
            hsiomSel[FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_TX_SCL_MISO_HSIOM_SEL_SPI;
        #endif /* (FRamInterface_TX_SCL_MISO_PIN) */
        
        #if (FRamInterface_CTS_SCLK_PIN)
            hsiomSel[FRamInterface_CTS_SCLK_PIN_INDEX] = FRamInterface_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (FRamInterface_CTS_SCLK_PIN) */

            if (FRamInterface_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[FRamInterface_RX_SDA_MOSI_PIN_INDEX] = FRamInterface_PIN_DM_DIG_HIZ;
                pinsDm[FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                pinsDm[FRamInterface_CTS_SCLK_PIN_INDEX] = FRamInterface_PIN_DM_DIG_HIZ;

            #if (FRamInterface_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[FRamInterface_RTS_SS0_PIN_INDEX] = FRamInterface_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [FRamInterface_RTS_SS0_PIN_INDEX] = FRamInterface_PIN_DM_DIG_HIZ;
            #endif /* (FRamInterface_RTS_SS0_PIN) */

            #if (FRamInterface_TX_SCL_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= FRamInterface_TX_SCL_MISO_PIN_MASK;
            #endif /* (FRamInterface_TX_SCL_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[FRamInterface_RX_SDA_MOSI_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                pinsDm[FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_PIN_DM_DIG_HIZ;
                pinsDm[FRamInterface_CTS_SCLK_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;

            #if (FRamInterface_RTS_SS0_PIN)
                hsiomSel [FRamInterface_RTS_SS0_PIN_INDEX] = FRamInterface_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [FRamInterface_RTS_SS0_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                pinsInBuf |= FRamInterface_RTS_SS0_PIN_MASK;
            #endif /* (FRamInterface_RTS_SS0_PIN) */

            #if (FRamInterface_SS1_PIN)
                hsiomSel [FRamInterface_SS1_PIN_INDEX] = FRamInterface_SS1_HSIOM_SEL_SPI;
                pinsDm   [FRamInterface_SS1_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                pinsInBuf |= FRamInterface_SS1_PIN_MASK;
            #endif /* (FRamInterface_SS1_PIN) */

            #if (FRamInterface_SS2_PIN)
                hsiomSel [FRamInterface_SS2_PIN_INDEX] = FRamInterface_SS2_HSIOM_SEL_SPI;
                pinsDm   [FRamInterface_SS2_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                pinsInBuf |= FRamInterface_SS2_PIN_MASK;
            #endif /* (FRamInterface_SS2_PIN) */

            #if (FRamInterface_SS3_PIN)
                hsiomSel [FRamInterface_SS3_PIN_INDEX] = FRamInterface_SS3_HSIOM_SEL_SPI;
                pinsDm   [FRamInterface_SS3_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                pinsInBuf |= FRamInterface_SS3_PIN_MASK;
            #endif /* (FRamInterface_SS3_PIN) */

                /* Disable input buffers */
            #if (FRamInterface_RX_SDA_MOSI_PIN)
                pinsInBuf |= FRamInterface_RX_SDA_MOSI_PIN_MASK;
            #elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
                pinsInBuf |= FRamInterface_RX_WAKE_SDA_MOSI_PIN_MASK;
            #else
            #endif /* (FRamInterface_RX_SDA_MOSI_PIN) */

            #if (FRamInterface_CTS_SCLK_PIN)
                pinsInBuf |= FRamInterface_CTS_SCLK_PIN_MASK;
            #endif /* (FRamInterface_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (FRamInterface_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (FRamInterface_TX_SCL_MISO_PIN)
                hsiomSel[FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_TX_SCL_MISO_HSIOM_SEL_UART;
                pinsDm  [FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_PIN_DM_OD_LO;
            #endif /* (FRamInterface_TX_SCL_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (FRamInterface_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (FRamInterface_RX_SDA_MOSI_PIN)
                    hsiomSel[FRamInterface_RX_SDA_MOSI_PIN_INDEX] = FRamInterface_RX_SDA_MOSI_HSIOM_SEL_UART;
                    pinsDm  [FRamInterface_RX_SDA_MOSI_PIN_INDEX] = FRamInterface_PIN_DM_DIG_HIZ;
                #elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
                    hsiomSel[FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX] = FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_SEL_UART;
                    pinsDm  [FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX] = FRamInterface_PIN_DM_DIG_HIZ;
                #else
                #endif /* (FRamInterface_RX_SDA_MOSI_PIN) */
                }

                if (0u != (FRamInterface_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (FRamInterface_TX_SCL_MISO_PIN)
                    hsiomSel[FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_TX_SCL_MISO_HSIOM_SEL_UART;
                    pinsDm  [FRamInterface_TX_SCL_MISO_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= FRamInterface_TX_SCL_MISO_PIN_MASK;
                #endif /* (FRamInterface_TX_SCL_MISO_PIN) */
                }

            #if !(FRamInterface_CY_SCBIP_V0 || FRamInterface_CY_SCBIP_V1)
                if (FRamInterface_UART_MODE_STD == subMode)
                {
                    if (0u != (FRamInterface_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (FRamInterface_CTS_SCLK_PIN)
                        hsiomSel[FRamInterface_CTS_SCLK_PIN_INDEX] = FRamInterface_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [FRamInterface_CTS_SCLK_PIN_INDEX] = FRamInterface_PIN_DM_DIG_HIZ;
                    #endif /* (FRamInterface_CTS_SCLK_PIN) */
                    }

                    if (0u != (FRamInterface_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (FRamInterface_RTS_SS0_PIN)
                        hsiomSel[FRamInterface_RTS_SS0_PIN_INDEX] = FRamInterface_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [FRamInterface_RTS_SS0_PIN_INDEX] = FRamInterface_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= FRamInterface_RTS_SS0_PIN_MASK;
                    #endif /* (FRamInterface_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(FRamInterface_CY_SCBIP_V0 || FRamInterface_CY_SCBIP_V1) */
            }
        }
    #endif /* (!FRamInterface_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (FRamInterface_RX_SDA_MOSI_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_RX_SDA_MOSI_HSIOM_REG,
                                       FRamInterface_RX_SDA_MOSI_HSIOM_MASK,
                                       FRamInterface_RX_SDA_MOSI_HSIOM_POS,
                                        hsiomSel[FRamInterface_RX_SDA_MOSI_PIN_INDEX]);

        FRamInterface_uart_rx_i2c_sda_spi_mosi_SetDriveMode((uint8) pinsDm[FRamInterface_RX_SDA_MOSI_PIN_INDEX]);

        #if (!FRamInterface_CY_SCBIP_V1)
            FRamInterface_SET_INP_DIS(FRamInterface_uart_rx_i2c_sda_spi_mosi_INP_DIS,
                                         FRamInterface_uart_rx_i2c_sda_spi_mosi_MASK,
                                         (0u != (pinsInBuf & FRamInterface_RX_SDA_MOSI_PIN_MASK)));
        #endif /* (!FRamInterface_CY_SCBIP_V1) */
    
    #elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG,
                                       FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_MASK,
                                       FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_POS,
                                       hsiomSel[FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX]);

        FRamInterface_uart_rx_wake_i2c_sda_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX]);

        FRamInterface_SET_INP_DIS(FRamInterface_uart_rx_wake_i2c_sda_spi_mosi_INP_DIS,
                                     FRamInterface_uart_rx_wake_i2c_sda_spi_mosi_MASK,
                                     (0u != (pinsInBuf & FRamInterface_RX_WAKE_SDA_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        FRamInterface_SET_INCFG_TYPE(FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_REG,
                                        FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK,
                                        FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS,
                                        FRamInterface_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (FRamInterface_RX_WAKE_SDA_MOSI_PIN) */

    #if (FRamInterface_TX_SCL_MISO_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_TX_SCL_MISO_HSIOM_REG,
                                       FRamInterface_TX_SCL_MISO_HSIOM_MASK,
                                       FRamInterface_TX_SCL_MISO_HSIOM_POS,
                                        hsiomSel[FRamInterface_TX_SCL_MISO_PIN_INDEX]);

        FRamInterface_uart_tx_i2c_scl_spi_miso_SetDriveMode((uint8) pinsDm[FRamInterface_TX_SCL_MISO_PIN_INDEX]);

    #if (!FRamInterface_CY_SCBIP_V1)
        FRamInterface_SET_INP_DIS(FRamInterface_uart_tx_i2c_scl_spi_miso_INP_DIS,
                                     FRamInterface_uart_tx_i2c_scl_spi_miso_MASK,
                                    (0u != (pinsInBuf & FRamInterface_TX_SCL_MISO_PIN_MASK)));
    #endif /* (!FRamInterface_CY_SCBIP_V1) */
    #endif /* (FRamInterface_RX_SDA_MOSI_PIN) */

    #if (FRamInterface_CTS_SCLK_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_CTS_SCLK_HSIOM_REG,
                                       FRamInterface_CTS_SCLK_HSIOM_MASK,
                                       FRamInterface_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[FRamInterface_CTS_SCLK_PIN_INDEX]);

        FRamInterface_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[FRamInterface_CTS_SCLK_PIN_INDEX]);

        FRamInterface_SET_INP_DIS(FRamInterface_uart_cts_spi_sclk_INP_DIS,
                                     FRamInterface_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & FRamInterface_CTS_SCLK_PIN_MASK)));
    #endif /* (FRamInterface_CTS_SCLK_PIN) */

    #if (FRamInterface_RTS_SS0_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_RTS_SS0_HSIOM_REG,
                                       FRamInterface_RTS_SS0_HSIOM_MASK,
                                       FRamInterface_RTS_SS0_HSIOM_POS,
                                       hsiomSel[FRamInterface_RTS_SS0_PIN_INDEX]);

        FRamInterface_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[FRamInterface_RTS_SS0_PIN_INDEX]);

        FRamInterface_SET_INP_DIS(FRamInterface_uart_rts_spi_ss0_INP_DIS,
                                     FRamInterface_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & FRamInterface_RTS_SS0_PIN_MASK)));
    #endif /* (FRamInterface_RTS_SS0_PIN) */

    #if (FRamInterface_SS1_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_SS1_HSIOM_REG,
                                       FRamInterface_SS1_HSIOM_MASK,
                                       FRamInterface_SS1_HSIOM_POS,
                                       hsiomSel[FRamInterface_SS1_PIN_INDEX]);

        FRamInterface_spi_ss1_SetDriveMode((uint8) pinsDm[FRamInterface_SS1_PIN_INDEX]);

        FRamInterface_SET_INP_DIS(FRamInterface_spi_ss1_INP_DIS,
                                     FRamInterface_spi_ss1_MASK,
                                     (0u != (pinsInBuf & FRamInterface_SS1_PIN_MASK)));
    #endif /* (FRamInterface_SS1_PIN) */

    #if (FRamInterface_SS2_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_SS2_HSIOM_REG,
                                       FRamInterface_SS2_HSIOM_MASK,
                                       FRamInterface_SS2_HSIOM_POS,
                                       hsiomSel[FRamInterface_SS2_PIN_INDEX]);

        FRamInterface_spi_ss2_SetDriveMode((uint8) pinsDm[FRamInterface_SS2_PIN_INDEX]);

        FRamInterface_SET_INP_DIS(FRamInterface_spi_ss2_INP_DIS,
                                     FRamInterface_spi_ss2_MASK,
                                     (0u != (pinsInBuf & FRamInterface_SS2_PIN_MASK)));
    #endif /* (FRamInterface_SS2_PIN) */

    #if (FRamInterface_SS3_PIN)
        FRamInterface_SET_HSIOM_SEL(FRamInterface_SS3_HSIOM_REG,
                                       FRamInterface_SS3_HSIOM_MASK,
                                       FRamInterface_SS3_HSIOM_POS,
                                       hsiomSel[FRamInterface_SS3_PIN_INDEX]);

        FRamInterface_spi_ss3_SetDriveMode((uint8) pinsDm[FRamInterface_SS3_PIN_INDEX]);

        FRamInterface_SET_INP_DIS(FRamInterface_spi_ss3_INP_DIS,
                                     FRamInterface_spi_ss3_MASK,
                                     (0u != (pinsInBuf & FRamInterface_SS3_PIN_MASK)));
    #endif /* (FRamInterface_SS3_PIN) */
    }

#endif /* (FRamInterface_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (FRamInterface_CY_SCBIP_V0 || FRamInterface_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: FRamInterface_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void FRamInterface_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (FRamInterface_CTRL_REG & FRamInterface_CTRL_EC_AM_MODE)) &&
            (0u == (FRamInterface_I2C_CTRL_REG & FRamInterface_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            FRamInterface_CTRL_REG &= ~FRamInterface_CTRL_EC_AM_MODE;
            FRamInterface_CTRL_REG |=  FRamInterface_CTRL_EC_AM_MODE;
        }

        FRamInterface_I2C_SLAVE_CMD_REG = FRamInterface_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (FRamInterface_CY_SCBIP_V0 || FRamInterface_CY_SCBIP_V1) */


/* [] END OF FILE */
