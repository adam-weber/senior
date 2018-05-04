/*******************************************************************************
* File Name: FRamInterface_scl.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_FRamInterface_scl_H) /* Pins FRamInterface_scl_H */
#define CY_PINS_FRamInterface_scl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FRamInterface_scl_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} FRamInterface_scl_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   FRamInterface_scl_Read(void);
void    FRamInterface_scl_Write(uint8 value);
uint8   FRamInterface_scl_ReadDataReg(void);
#if defined(FRamInterface_scl__PC) || (CY_PSOC4_4200L) 
    void    FRamInterface_scl_SetDriveMode(uint8 mode);
#endif
void    FRamInterface_scl_SetInterruptMode(uint16 position, uint16 mode);
uint8   FRamInterface_scl_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void FRamInterface_scl_Sleep(void); 
void FRamInterface_scl_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(FRamInterface_scl__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define FRamInterface_scl_DRIVE_MODE_BITS        (3)
    #define FRamInterface_scl_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FRamInterface_scl_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the FRamInterface_scl_SetDriveMode() function.
         *  @{
         */
        #define FRamInterface_scl_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define FRamInterface_scl_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define FRamInterface_scl_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define FRamInterface_scl_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define FRamInterface_scl_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define FRamInterface_scl_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define FRamInterface_scl_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define FRamInterface_scl_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define FRamInterface_scl_MASK               FRamInterface_scl__MASK
#define FRamInterface_scl_SHIFT              FRamInterface_scl__SHIFT
#define FRamInterface_scl_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FRamInterface_scl_SetInterruptMode() function.
     *  @{
     */
        #define FRamInterface_scl_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define FRamInterface_scl_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define FRamInterface_scl_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define FRamInterface_scl_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(FRamInterface_scl__SIO)
    #define FRamInterface_scl_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(FRamInterface_scl__PC) && (CY_PSOC4_4200L)
    #define FRamInterface_scl_USBIO_ENABLE               ((uint32)0x80000000u)
    #define FRamInterface_scl_USBIO_DISABLE              ((uint32)(~FRamInterface_scl_USBIO_ENABLE))
    #define FRamInterface_scl_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define FRamInterface_scl_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define FRamInterface_scl_USBIO_ENTER_SLEEP          ((uint32)((1u << FRamInterface_scl_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << FRamInterface_scl_USBIO_SUSPEND_DEL_SHIFT)))
    #define FRamInterface_scl_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << FRamInterface_scl_USBIO_SUSPEND_SHIFT)))
    #define FRamInterface_scl_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << FRamInterface_scl_USBIO_SUSPEND_DEL_SHIFT)))
    #define FRamInterface_scl_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(FRamInterface_scl__PC)
    /* Port Configuration */
    #define FRamInterface_scl_PC                 (* (reg32 *) FRamInterface_scl__PC)
#endif
/* Pin State */
#define FRamInterface_scl_PS                     (* (reg32 *) FRamInterface_scl__PS)
/* Data Register */
#define FRamInterface_scl_DR                     (* (reg32 *) FRamInterface_scl__DR)
/* Input Buffer Disable Override */
#define FRamInterface_scl_INP_DIS                (* (reg32 *) FRamInterface_scl__PC2)

/* Interrupt configuration Registers */
#define FRamInterface_scl_INTCFG                 (* (reg32 *) FRamInterface_scl__INTCFG)
#define FRamInterface_scl_INTSTAT                (* (reg32 *) FRamInterface_scl__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define FRamInterface_scl_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(FRamInterface_scl__SIO)
    #define FRamInterface_scl_SIO_REG            (* (reg32 *) FRamInterface_scl__SIO)
#endif /* (FRamInterface_scl__SIO_CFG) */

/* USBIO registers */
#if !defined(FRamInterface_scl__PC) && (CY_PSOC4_4200L)
    #define FRamInterface_scl_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define FRamInterface_scl_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define FRamInterface_scl_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define FRamInterface_scl_DRIVE_MODE_SHIFT       (0x00u)
#define FRamInterface_scl_DRIVE_MODE_MASK        (0x07u << FRamInterface_scl_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins FRamInterface_scl_H */


/* [] END OF FILE */
