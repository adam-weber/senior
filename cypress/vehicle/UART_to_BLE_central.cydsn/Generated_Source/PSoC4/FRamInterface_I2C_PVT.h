/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
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

#if !defined(CY_SCB_I2C_PVT_FRamInterface_H)
#define CY_SCB_I2C_PVT_FRamInterface_H

#include "FRamInterface_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 FRamInterface_state; /* Current state of I2C FSM */

#if(FRamInterface_I2C_SLAVE_CONST)
    extern volatile uint8 FRamInterface_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * FRamInterface_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  FRamInterface_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  FRamInterface_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * FRamInterface_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  FRamInterface_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  FRamInterface_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  FRamInterface_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   FRamInterface_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (FRamInterface_I2C_SLAVE_CONST) */

#if(FRamInterface_I2C_MASTER_CONST)
    extern volatile uint16 FRamInterface_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  FRamInterface_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * FRamInterface_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  FRamInterface_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  FRamInterface_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * FRamInterface_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  FRamInterface_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  FRamInterface_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  FRamInterface_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (FRamInterface_I2C_MASTER_CONST) */

#if (FRamInterface_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*FRamInterface_customAddressHandler) (void);
#endif /* (FRamInterface_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(FRamInterface_SCB_MODE_I2C_CONST_CFG)
    void FRamInterface_I2CInit(void);
#endif /* (FRamInterface_SCB_MODE_I2C_CONST_CFG) */

void FRamInterface_I2CStop(void);
void FRamInterface_I2CFwBlockReset(void);

void FRamInterface_I2CSaveConfig(void);
void FRamInterface_I2CRestoreConfig(void);

#if(FRamInterface_I2C_MASTER_CONST)
    void FRamInterface_I2CReStartGeneration(void);
#endif /* (FRamInterface_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_FRamInterface_H) */


/* [] END OF FILE */
