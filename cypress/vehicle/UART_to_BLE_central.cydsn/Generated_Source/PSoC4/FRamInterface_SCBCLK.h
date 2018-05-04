/*******************************************************************************
* File Name: FRamInterface_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_FRamInterface_SCBCLK_H)
#define CY_CLOCK_FRamInterface_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void FRamInterface_SCBCLK_StartEx(uint32 alignClkDiv);
#define FRamInterface_SCBCLK_Start() \
    FRamInterface_SCBCLK_StartEx(FRamInterface_SCBCLK__PA_DIV_ID)

#else

void FRamInterface_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void FRamInterface_SCBCLK_Stop(void);

void FRamInterface_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 FRamInterface_SCBCLK_GetDividerRegister(void);
uint8  FRamInterface_SCBCLK_GetFractionalDividerRegister(void);

#define FRamInterface_SCBCLK_Enable()                         FRamInterface_SCBCLK_Start()
#define FRamInterface_SCBCLK_Disable()                        FRamInterface_SCBCLK_Stop()
#define FRamInterface_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    FRamInterface_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define FRamInterface_SCBCLK_SetDivider(clkDivider)           FRamInterface_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define FRamInterface_SCBCLK_SetDividerValue(clkDivider)      FRamInterface_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define FRamInterface_SCBCLK_DIV_ID     FRamInterface_SCBCLK__DIV_ID

#define FRamInterface_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define FRamInterface_SCBCLK_CTRL_REG   (*(reg32 *)FRamInterface_SCBCLK__CTRL_REGISTER)
#define FRamInterface_SCBCLK_DIV_REG    (*(reg32 *)FRamInterface_SCBCLK__DIV_REGISTER)

#define FRamInterface_SCBCLK_CMD_DIV_SHIFT          (0u)
#define FRamInterface_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define FRamInterface_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define FRamInterface_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define FRamInterface_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << FRamInterface_SCBCLK_CMD_DISABLE_SHIFT))
#define FRamInterface_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << FRamInterface_SCBCLK_CMD_ENABLE_SHIFT))

#define FRamInterface_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define FRamInterface_SCBCLK_DIV_FRAC_SHIFT (3u)
#define FRamInterface_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define FRamInterface_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define FRamInterface_SCBCLK_DIV_REG        (*(reg32 *)FRamInterface_SCBCLK__REGISTER)
#define FRamInterface_SCBCLK_ENABLE_REG     FRamInterface_SCBCLK_DIV_REG
#define FRamInterface_SCBCLK_DIV_FRAC_MASK  FRamInterface_SCBCLK__FRAC_MASK
#define FRamInterface_SCBCLK_DIV_FRAC_SHIFT (16u)
#define FRamInterface_SCBCLK_DIV_INT_MASK   FRamInterface_SCBCLK__DIVIDER_MASK
#define FRamInterface_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_FRamInterface_SCBCLK_H) */

/* [] END OF FILE */
