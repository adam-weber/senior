/*******************************************************************************
* File Name: Clock_HiLo.h
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

#if !defined(CY_CLOCK_Clock_HiLo_H)
#define CY_CLOCK_Clock_HiLo_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Clock_HiLo_StartEx(uint32 alignClkDiv);
#define Clock_HiLo_Start() \
    Clock_HiLo_StartEx(Clock_HiLo__PA_DIV_ID)

#else

void Clock_HiLo_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Clock_HiLo_Stop(void);

void Clock_HiLo_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_HiLo_GetDividerRegister(void);
uint8  Clock_HiLo_GetFractionalDividerRegister(void);

#define Clock_HiLo_Enable()                         Clock_HiLo_Start()
#define Clock_HiLo_Disable()                        Clock_HiLo_Stop()
#define Clock_HiLo_SetDividerRegister(clkDivider, reset)  \
    Clock_HiLo_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_HiLo_SetDivider(clkDivider)           Clock_HiLo_SetDividerRegister((clkDivider), 1u)
#define Clock_HiLo_SetDividerValue(clkDivider)      Clock_HiLo_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Clock_HiLo_DIV_ID     Clock_HiLo__DIV_ID

#define Clock_HiLo_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Clock_HiLo_CTRL_REG   (*(reg32 *)Clock_HiLo__CTRL_REGISTER)
#define Clock_HiLo_DIV_REG    (*(reg32 *)Clock_HiLo__DIV_REGISTER)

#define Clock_HiLo_CMD_DIV_SHIFT          (0u)
#define Clock_HiLo_CMD_PA_DIV_SHIFT       (8u)
#define Clock_HiLo_CMD_DISABLE_SHIFT      (30u)
#define Clock_HiLo_CMD_ENABLE_SHIFT       (31u)

#define Clock_HiLo_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Clock_HiLo_CMD_DISABLE_SHIFT))
#define Clock_HiLo_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Clock_HiLo_CMD_ENABLE_SHIFT))

#define Clock_HiLo_DIV_FRAC_MASK  (0x000000F8u)
#define Clock_HiLo_DIV_FRAC_SHIFT (3u)
#define Clock_HiLo_DIV_INT_MASK   (0xFFFFFF00u)
#define Clock_HiLo_DIV_INT_SHIFT  (8u)

#else 

#define Clock_HiLo_DIV_REG        (*(reg32 *)Clock_HiLo__REGISTER)
#define Clock_HiLo_ENABLE_REG     Clock_HiLo_DIV_REG
#define Clock_HiLo_DIV_FRAC_MASK  Clock_HiLo__FRAC_MASK
#define Clock_HiLo_DIV_FRAC_SHIFT (16u)
#define Clock_HiLo_DIV_INT_MASK   Clock_HiLo__DIVIDER_MASK
#define Clock_HiLo_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Clock_HiLo_H) */

/* [] END OF FILE */
