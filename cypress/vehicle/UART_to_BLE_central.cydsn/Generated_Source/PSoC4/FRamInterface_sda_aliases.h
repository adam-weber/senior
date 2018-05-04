/*******************************************************************************
* File Name: FRamInterface_sda.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_FRamInterface_sda_ALIASES_H) /* Pins FRamInterface_sda_ALIASES_H */
#define CY_PINS_FRamInterface_sda_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FRamInterface_sda_0			(FRamInterface_sda__0__PC)
#define FRamInterface_sda_0_PS		(FRamInterface_sda__0__PS)
#define FRamInterface_sda_0_PC		(FRamInterface_sda__0__PC)
#define FRamInterface_sda_0_DR		(FRamInterface_sda__0__DR)
#define FRamInterface_sda_0_SHIFT	(FRamInterface_sda__0__SHIFT)
#define FRamInterface_sda_0_INTR	((uint16)((uint16)0x0003u << (FRamInterface_sda__0__SHIFT*2u)))

#define FRamInterface_sda_INTR_ALL	 ((uint16)(FRamInterface_sda_0_INTR))


#endif /* End Pins FRamInterface_sda_ALIASES_H */


/* [] END OF FILE */
