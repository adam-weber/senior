/***************************************************************************//**
* \file FRamInterface_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_FRamInterface_H)
#define CY_SCB_PINS_FRamInterface_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define FRamInterface_REMOVE_RX_WAKE_SDA_MOSI_PIN  (1u)
#define FRamInterface_REMOVE_RX_SDA_MOSI_PIN      (1u)
#define FRamInterface_REMOVE_TX_SCL_MISO_PIN      (1u)
#define FRamInterface_REMOVE_CTS_SCLK_PIN      (1u)
#define FRamInterface_REMOVE_RTS_SS0_PIN      (1u)
#define FRamInterface_REMOVE_SS1_PIN                 (1u)
#define FRamInterface_REMOVE_SS2_PIN                 (1u)
#define FRamInterface_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define FRamInterface_REMOVE_I2C_PINS                (0u)
#define FRamInterface_REMOVE_SPI_MASTER_PINS         (1u)
#define FRamInterface_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define FRamInterface_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define FRamInterface_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define FRamInterface_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define FRamInterface_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define FRamInterface_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define FRamInterface_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define FRamInterface_REMOVE_SPI_SLAVE_PINS          (1u)
#define FRamInterface_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define FRamInterface_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define FRamInterface_REMOVE_UART_TX_PIN             (1u)
#define FRamInterface_REMOVE_UART_RX_TX_PIN          (1u)
#define FRamInterface_REMOVE_UART_RX_PIN             (1u)
#define FRamInterface_REMOVE_UART_RX_WAKE_PIN        (1u)
#define FRamInterface_REMOVE_UART_RTS_PIN            (1u)
#define FRamInterface_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define FRamInterface_RX_WAKE_SDA_MOSI_PIN (0u == FRamInterface_REMOVE_RX_WAKE_SDA_MOSI_PIN)
#define FRamInterface_RX_SDA_MOSI_PIN     (0u == FRamInterface_REMOVE_RX_SDA_MOSI_PIN)
#define FRamInterface_TX_SCL_MISO_PIN     (0u == FRamInterface_REMOVE_TX_SCL_MISO_PIN)
#define FRamInterface_CTS_SCLK_PIN     (0u == FRamInterface_REMOVE_CTS_SCLK_PIN)
#define FRamInterface_RTS_SS0_PIN     (0u == FRamInterface_REMOVE_RTS_SS0_PIN)
#define FRamInterface_SS1_PIN                (0u == FRamInterface_REMOVE_SS1_PIN)
#define FRamInterface_SS2_PIN                (0u == FRamInterface_REMOVE_SS2_PIN)
#define FRamInterface_SS3_PIN                (0u == FRamInterface_REMOVE_SS3_PIN)

/* Mode defined pins */
#define FRamInterface_I2C_PINS               (0u == FRamInterface_REMOVE_I2C_PINS)
#define FRamInterface_SPI_MASTER_PINS        (0u == FRamInterface_REMOVE_SPI_MASTER_PINS)
#define FRamInterface_SPI_MASTER_SCLK_PIN    (0u == FRamInterface_REMOVE_SPI_MASTER_SCLK_PIN)
#define FRamInterface_SPI_MASTER_MOSI_PIN    (0u == FRamInterface_REMOVE_SPI_MASTER_MOSI_PIN)
#define FRamInterface_SPI_MASTER_MISO_PIN    (0u == FRamInterface_REMOVE_SPI_MASTER_MISO_PIN)
#define FRamInterface_SPI_MASTER_SS0_PIN     (0u == FRamInterface_REMOVE_SPI_MASTER_SS0_PIN)
#define FRamInterface_SPI_MASTER_SS1_PIN     (0u == FRamInterface_REMOVE_SPI_MASTER_SS1_PIN)
#define FRamInterface_SPI_MASTER_SS2_PIN     (0u == FRamInterface_REMOVE_SPI_MASTER_SS2_PIN)
#define FRamInterface_SPI_MASTER_SS3_PIN     (0u == FRamInterface_REMOVE_SPI_MASTER_SS3_PIN)
#define FRamInterface_SPI_SLAVE_PINS         (0u == FRamInterface_REMOVE_SPI_SLAVE_PINS)
#define FRamInterface_SPI_SLAVE_MOSI_PIN     (0u == FRamInterface_REMOVE_SPI_SLAVE_MOSI_PIN)
#define FRamInterface_SPI_SLAVE_MISO_PIN     (0u == FRamInterface_REMOVE_SPI_SLAVE_MISO_PIN)
#define FRamInterface_UART_TX_PIN            (0u == FRamInterface_REMOVE_UART_TX_PIN)
#define FRamInterface_UART_RX_TX_PIN         (0u == FRamInterface_REMOVE_UART_RX_TX_PIN)
#define FRamInterface_UART_RX_PIN            (0u == FRamInterface_REMOVE_UART_RX_PIN)
#define FRamInterface_UART_RX_WAKE_PIN       (0u == FRamInterface_REMOVE_UART_RX_WAKE_PIN)
#define FRamInterface_UART_RTS_PIN           (0u == FRamInterface_REMOVE_UART_RTS_PIN)
#define FRamInterface_UART_CTS_PIN           (0u == FRamInterface_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
    #include "FRamInterface_uart_rx_wake_i2c_sda_spi_mosi.h"
#endif /* (FRamInterface_RX_SDA_MOSI) */

#if (FRamInterface_RX_SDA_MOSI_PIN)
    #include "FRamInterface_uart_rx_i2c_sda_spi_mosi.h"
#endif /* (FRamInterface_RX_SDA_MOSI) */

#if (FRamInterface_TX_SCL_MISO_PIN)
    #include "FRamInterface_uart_tx_i2c_scl_spi_miso.h"
#endif /* (FRamInterface_TX_SCL_MISO) */

#if (FRamInterface_CTS_SCLK_PIN)
    #include "FRamInterface_uart_cts_spi_sclk.h"
#endif /* (FRamInterface_CTS_SCLK) */

#if (FRamInterface_RTS_SS0_PIN)
    #include "FRamInterface_uart_rts_spi_ss0.h"
#endif /* (FRamInterface_RTS_SS0_PIN) */

#if (FRamInterface_SS1_PIN)
    #include "FRamInterface_spi_ss1.h"
#endif /* (FRamInterface_SS1_PIN) */

#if (FRamInterface_SS2_PIN)
    #include "FRamInterface_spi_ss2.h"
#endif /* (FRamInterface_SS2_PIN) */

#if (FRamInterface_SS3_PIN)
    #include "FRamInterface_spi_ss3.h"
#endif /* (FRamInterface_SS3_PIN) */

#if (FRamInterface_I2C_PINS)
    #include "FRamInterface_scl.h"
    #include "FRamInterface_sda.h"
#endif /* (FRamInterface_I2C_PINS) */

#if (FRamInterface_SPI_MASTER_PINS)
#if (FRamInterface_SPI_MASTER_SCLK_PIN)
    #include "FRamInterface_sclk_m.h"
#endif /* (FRamInterface_SPI_MASTER_SCLK_PIN) */

#if (FRamInterface_SPI_MASTER_MOSI_PIN)
    #include "FRamInterface_mosi_m.h"
#endif /* (FRamInterface_SPI_MASTER_MOSI_PIN) */

#if (FRamInterface_SPI_MASTER_MISO_PIN)
    #include "FRamInterface_miso_m.h"
#endif /*(FRamInterface_SPI_MASTER_MISO_PIN) */
#endif /* (FRamInterface_SPI_MASTER_PINS) */

#if (FRamInterface_SPI_SLAVE_PINS)
    #include "FRamInterface_sclk_s.h"
    #include "FRamInterface_ss_s.h"

#if (FRamInterface_SPI_SLAVE_MOSI_PIN)
    #include "FRamInterface_mosi_s.h"
#endif /* (FRamInterface_SPI_SLAVE_MOSI_PIN) */

#if (FRamInterface_SPI_SLAVE_MISO_PIN)
    #include "FRamInterface_miso_s.h"
#endif /*(FRamInterface_SPI_SLAVE_MISO_PIN) */
#endif /* (FRamInterface_SPI_SLAVE_PINS) */

#if (FRamInterface_SPI_MASTER_SS0_PIN)
    #include "FRamInterface_ss0_m.h"
#endif /* (FRamInterface_SPI_MASTER_SS0_PIN) */

#if (FRamInterface_SPI_MASTER_SS1_PIN)
    #include "FRamInterface_ss1_m.h"
#endif /* (FRamInterface_SPI_MASTER_SS1_PIN) */

#if (FRamInterface_SPI_MASTER_SS2_PIN)
    #include "FRamInterface_ss2_m.h"
#endif /* (FRamInterface_SPI_MASTER_SS2_PIN) */

#if (FRamInterface_SPI_MASTER_SS3_PIN)
    #include "FRamInterface_ss3_m.h"
#endif /* (FRamInterface_SPI_MASTER_SS3_PIN) */

#if (FRamInterface_UART_TX_PIN)
    #include "FRamInterface_tx.h"
#endif /* (FRamInterface_UART_TX_PIN) */

#if (FRamInterface_UART_RX_TX_PIN)
    #include "FRamInterface_rx_tx.h"
#endif /* (FRamInterface_UART_RX_TX_PIN) */

#if (FRamInterface_UART_RX_PIN)
    #include "FRamInterface_rx.h"
#endif /* (FRamInterface_UART_RX_PIN) */

#if (FRamInterface_UART_RX_WAKE_PIN)
    #include "FRamInterface_rx_wake.h"
#endif /* (FRamInterface_UART_RX_WAKE_PIN) */

#if (FRamInterface_UART_RTS_PIN)
    #include "FRamInterface_rts.h"
#endif /* (FRamInterface_UART_RTS_PIN) */

#if (FRamInterface_UART_CTS_PIN)
    #include "FRamInterface_cts.h"
#endif /* (FRamInterface_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (FRamInterface_RX_SDA_MOSI_PIN)
    #define FRamInterface_RX_SDA_MOSI_HSIOM_REG   (*(reg32 *) FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    #define FRamInterface_RX_SDA_MOSI_HSIOM_PTR   ( (reg32 *) FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    
    #define FRamInterface_RX_SDA_MOSI_HSIOM_MASK      (FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define FRamInterface_RX_SDA_MOSI_HSIOM_POS       (FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define FRamInterface_RX_SDA_MOSI_HSIOM_SEL_GPIO  (FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define FRamInterface_RX_SDA_MOSI_HSIOM_SEL_I2C   (FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define FRamInterface_RX_SDA_MOSI_HSIOM_SEL_SPI   (FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define FRamInterface_RX_SDA_MOSI_HSIOM_SEL_UART  (FRamInterface_uart_rx_i2c_sda_spi_mosi__0__HSIOM_UART)
    
#elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG   (*(reg32 *) FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_PTR   ( (reg32 *) FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_MASK      (FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_POS       (FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_SEL_GPIO  (FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_SEL_I2C   (FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_SEL_SPI   (FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_SEL_UART  (FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_UART)    
   
    #define FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_REG (*(reg32 *) FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_PTR ( (reg32 *) FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS  (FRamInterface_uart_rx_wake_i2c_sda_spi_mosi__SHIFT)
    #define FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK ((uint32) FRamInterface_INTCFG_TYPE_MASK << \
                                                                           FRamInterface_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins FRamInterface_RX_SDA_MOSI_PIN or FRamInterface_RX_WAKE_SDA_MOSI_PIN present.*/
#endif /* (FRamInterface_RX_SDA_MOSI_PIN) */

#if (FRamInterface_TX_SCL_MISO_PIN)
    #define FRamInterface_TX_SCL_MISO_HSIOM_REG   (*(reg32 *) FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    #define FRamInterface_TX_SCL_MISO_HSIOM_PTR   ( (reg32 *) FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    
    #define FRamInterface_TX_SCL_MISO_HSIOM_MASK      (FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM_MASK)
    #define FRamInterface_TX_SCL_MISO_HSIOM_POS       (FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM_SHIFT)
    #define FRamInterface_TX_SCL_MISO_HSIOM_SEL_GPIO  (FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM_GPIO)
    #define FRamInterface_TX_SCL_MISO_HSIOM_SEL_I2C   (FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM_I2C)
    #define FRamInterface_TX_SCL_MISO_HSIOM_SEL_SPI   (FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM_SPI)
    #define FRamInterface_TX_SCL_MISO_HSIOM_SEL_UART  (FRamInterface_uart_tx_i2c_scl_spi_miso__0__HSIOM_UART)
#endif /* (FRamInterface_TX_SCL_MISO_PIN) */

#if (FRamInterface_CTS_SCLK_PIN)
    #define FRamInterface_CTS_SCLK_HSIOM_REG   (*(reg32 *) FRamInterface_uart_cts_spi_sclk__0__HSIOM)
    #define FRamInterface_CTS_SCLK_HSIOM_PTR   ( (reg32 *) FRamInterface_uart_cts_spi_sclk__0__HSIOM)
    
    #define FRamInterface_CTS_SCLK_HSIOM_MASK      (FRamInterface_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define FRamInterface_CTS_SCLK_HSIOM_POS       (FRamInterface_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define FRamInterface_CTS_SCLK_HSIOM_SEL_GPIO  (FRamInterface_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define FRamInterface_CTS_SCLK_HSIOM_SEL_I2C   (FRamInterface_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define FRamInterface_CTS_SCLK_HSIOM_SEL_SPI   (FRamInterface_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define FRamInterface_CTS_SCLK_HSIOM_SEL_UART  (FRamInterface_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (FRamInterface_CTS_SCLK_PIN) */

#if (FRamInterface_RTS_SS0_PIN)
    #define FRamInterface_RTS_SS0_HSIOM_REG   (*(reg32 *) FRamInterface_uart_rts_spi_ss0__0__HSIOM)
    #define FRamInterface_RTS_SS0_HSIOM_PTR   ( (reg32 *) FRamInterface_uart_rts_spi_ss0__0__HSIOM)
    
    #define FRamInterface_RTS_SS0_HSIOM_MASK      (FRamInterface_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define FRamInterface_RTS_SS0_HSIOM_POS       (FRamInterface_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define FRamInterface_RTS_SS0_HSIOM_SEL_GPIO  (FRamInterface_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define FRamInterface_RTS_SS0_HSIOM_SEL_I2C   (FRamInterface_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define FRamInterface_RTS_SS0_HSIOM_SEL_SPI   (FRamInterface_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(FRamInterface_CY_SCBIP_V0 || FRamInterface_CY_SCBIP_V1)
    #define FRamInterface_RTS_SS0_HSIOM_SEL_UART  (FRamInterface_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(FRamInterface_CY_SCBIP_V0 || FRamInterface_CY_SCBIP_V1) */
#endif /* (FRamInterface_RTS_SS0_PIN) */

#if (FRamInterface_SS1_PIN)
    #define FRamInterface_SS1_HSIOM_REG  (*(reg32 *) FRamInterface_spi_ss1__0__HSIOM)
    #define FRamInterface_SS1_HSIOM_PTR  ( (reg32 *) FRamInterface_spi_ss1__0__HSIOM)
    
    #define FRamInterface_SS1_HSIOM_MASK     (FRamInterface_spi_ss1__0__HSIOM_MASK)
    #define FRamInterface_SS1_HSIOM_POS      (FRamInterface_spi_ss1__0__HSIOM_SHIFT)
    #define FRamInterface_SS1_HSIOM_SEL_GPIO (FRamInterface_spi_ss1__0__HSIOM_GPIO)
    #define FRamInterface_SS1_HSIOM_SEL_I2C  (FRamInterface_spi_ss1__0__HSIOM_I2C)
    #define FRamInterface_SS1_HSIOM_SEL_SPI  (FRamInterface_spi_ss1__0__HSIOM_SPI)
#endif /* (FRamInterface_SS1_PIN) */

#if (FRamInterface_SS2_PIN)
    #define FRamInterface_SS2_HSIOM_REG     (*(reg32 *) FRamInterface_spi_ss2__0__HSIOM)
    #define FRamInterface_SS2_HSIOM_PTR     ( (reg32 *) FRamInterface_spi_ss2__0__HSIOM)
    
    #define FRamInterface_SS2_HSIOM_MASK     (FRamInterface_spi_ss2__0__HSIOM_MASK)
    #define FRamInterface_SS2_HSIOM_POS      (FRamInterface_spi_ss2__0__HSIOM_SHIFT)
    #define FRamInterface_SS2_HSIOM_SEL_GPIO (FRamInterface_spi_ss2__0__HSIOM_GPIO)
    #define FRamInterface_SS2_HSIOM_SEL_I2C  (FRamInterface_spi_ss2__0__HSIOM_I2C)
    #define FRamInterface_SS2_HSIOM_SEL_SPI  (FRamInterface_spi_ss2__0__HSIOM_SPI)
#endif /* (FRamInterface_SS2_PIN) */

#if (FRamInterface_SS3_PIN)
    #define FRamInterface_SS3_HSIOM_REG     (*(reg32 *) FRamInterface_spi_ss3__0__HSIOM)
    #define FRamInterface_SS3_HSIOM_PTR     ( (reg32 *) FRamInterface_spi_ss3__0__HSIOM)
    
    #define FRamInterface_SS3_HSIOM_MASK     (FRamInterface_spi_ss3__0__HSIOM_MASK)
    #define FRamInterface_SS3_HSIOM_POS      (FRamInterface_spi_ss3__0__HSIOM_SHIFT)
    #define FRamInterface_SS3_HSIOM_SEL_GPIO (FRamInterface_spi_ss3__0__HSIOM_GPIO)
    #define FRamInterface_SS3_HSIOM_SEL_I2C  (FRamInterface_spi_ss3__0__HSIOM_I2C)
    #define FRamInterface_SS3_HSIOM_SEL_SPI  (FRamInterface_spi_ss3__0__HSIOM_SPI)
#endif /* (FRamInterface_SS3_PIN) */

#if (FRamInterface_I2C_PINS)
    #define FRamInterface_SCL_HSIOM_REG  (*(reg32 *) FRamInterface_scl__0__HSIOM)
    #define FRamInterface_SCL_HSIOM_PTR  ( (reg32 *) FRamInterface_scl__0__HSIOM)
    
    #define FRamInterface_SCL_HSIOM_MASK     (FRamInterface_scl__0__HSIOM_MASK)
    #define FRamInterface_SCL_HSIOM_POS      (FRamInterface_scl__0__HSIOM_SHIFT)
    #define FRamInterface_SCL_HSIOM_SEL_GPIO (FRamInterface_sda__0__HSIOM_GPIO)
    #define FRamInterface_SCL_HSIOM_SEL_I2C  (FRamInterface_sda__0__HSIOM_I2C)
    
    #define FRamInterface_SDA_HSIOM_REG  (*(reg32 *) FRamInterface_sda__0__HSIOM)
    #define FRamInterface_SDA_HSIOM_PTR  ( (reg32 *) FRamInterface_sda__0__HSIOM)
    
    #define FRamInterface_SDA_HSIOM_MASK     (FRamInterface_sda__0__HSIOM_MASK)
    #define FRamInterface_SDA_HSIOM_POS      (FRamInterface_sda__0__HSIOM_SHIFT)
    #define FRamInterface_SDA_HSIOM_SEL_GPIO (FRamInterface_sda__0__HSIOM_GPIO)
    #define FRamInterface_SDA_HSIOM_SEL_I2C  (FRamInterface_sda__0__HSIOM_I2C)
#endif /* (FRamInterface_I2C_PINS) */

#if (FRamInterface_SPI_SLAVE_PINS)
    #define FRamInterface_SCLK_S_HSIOM_REG   (*(reg32 *) FRamInterface_sclk_s__0__HSIOM)
    #define FRamInterface_SCLK_S_HSIOM_PTR   ( (reg32 *) FRamInterface_sclk_s__0__HSIOM)
    
    #define FRamInterface_SCLK_S_HSIOM_MASK      (FRamInterface_sclk_s__0__HSIOM_MASK)
    #define FRamInterface_SCLK_S_HSIOM_POS       (FRamInterface_sclk_s__0__HSIOM_SHIFT)
    #define FRamInterface_SCLK_S_HSIOM_SEL_GPIO  (FRamInterface_sclk_s__0__HSIOM_GPIO)
    #define FRamInterface_SCLK_S_HSIOM_SEL_SPI   (FRamInterface_sclk_s__0__HSIOM_SPI)
    
    #define FRamInterface_SS0_S_HSIOM_REG    (*(reg32 *) FRamInterface_ss0_s__0__HSIOM)
    #define FRamInterface_SS0_S_HSIOM_PTR    ( (reg32 *) FRamInterface_ss0_s__0__HSIOM)
    
    #define FRamInterface_SS0_S_HSIOM_MASK       (FRamInterface_ss0_s__0__HSIOM_MASK)
    #define FRamInterface_SS0_S_HSIOM_POS        (FRamInterface_ss0_s__0__HSIOM_SHIFT)
    #define FRamInterface_SS0_S_HSIOM_SEL_GPIO   (FRamInterface_ss0_s__0__HSIOM_GPIO)  
    #define FRamInterface_SS0_S_HSIOM_SEL_SPI    (FRamInterface_ss0_s__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_SLAVE_PINS) */

#if (FRamInterface_SPI_SLAVE_MOSI_PIN)
    #define FRamInterface_MOSI_S_HSIOM_REG   (*(reg32 *) FRamInterface_mosi_s__0__HSIOM)
    #define FRamInterface_MOSI_S_HSIOM_PTR   ( (reg32 *) FRamInterface_mosi_s__0__HSIOM)
    
    #define FRamInterface_MOSI_S_HSIOM_MASK      (FRamInterface_mosi_s__0__HSIOM_MASK)
    #define FRamInterface_MOSI_S_HSIOM_POS       (FRamInterface_mosi_s__0__HSIOM_SHIFT)
    #define FRamInterface_MOSI_S_HSIOM_SEL_GPIO  (FRamInterface_mosi_s__0__HSIOM_GPIO)
    #define FRamInterface_MOSI_S_HSIOM_SEL_SPI   (FRamInterface_mosi_s__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_SLAVE_MOSI_PIN) */

#if (FRamInterface_SPI_SLAVE_MISO_PIN)
    #define FRamInterface_MISO_S_HSIOM_REG   (*(reg32 *) FRamInterface_miso_s__0__HSIOM)
    #define FRamInterface_MISO_S_HSIOM_PTR   ( (reg32 *) FRamInterface_miso_s__0__HSIOM)
    
    #define FRamInterface_MISO_S_HSIOM_MASK      (FRamInterface_miso_s__0__HSIOM_MASK)
    #define FRamInterface_MISO_S_HSIOM_POS       (FRamInterface_miso_s__0__HSIOM_SHIFT)
    #define FRamInterface_MISO_S_HSIOM_SEL_GPIO  (FRamInterface_miso_s__0__HSIOM_GPIO)
    #define FRamInterface_MISO_S_HSIOM_SEL_SPI   (FRamInterface_miso_s__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_SLAVE_MISO_PIN) */

#if (FRamInterface_SPI_MASTER_MISO_PIN)
    #define FRamInterface_MISO_M_HSIOM_REG   (*(reg32 *) FRamInterface_miso_m__0__HSIOM)
    #define FRamInterface_MISO_M_HSIOM_PTR   ( (reg32 *) FRamInterface_miso_m__0__HSIOM)
    
    #define FRamInterface_MISO_M_HSIOM_MASK      (FRamInterface_miso_m__0__HSIOM_MASK)
    #define FRamInterface_MISO_M_HSIOM_POS       (FRamInterface_miso_m__0__HSIOM_SHIFT)
    #define FRamInterface_MISO_M_HSIOM_SEL_GPIO  (FRamInterface_miso_m__0__HSIOM_GPIO)
    #define FRamInterface_MISO_M_HSIOM_SEL_SPI   (FRamInterface_miso_m__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_MASTER_MISO_PIN) */

#if (FRamInterface_SPI_MASTER_MOSI_PIN)
    #define FRamInterface_MOSI_M_HSIOM_REG   (*(reg32 *) FRamInterface_mosi_m__0__HSIOM)
    #define FRamInterface_MOSI_M_HSIOM_PTR   ( (reg32 *) FRamInterface_mosi_m__0__HSIOM)
    
    #define FRamInterface_MOSI_M_HSIOM_MASK      (FRamInterface_mosi_m__0__HSIOM_MASK)
    #define FRamInterface_MOSI_M_HSIOM_POS       (FRamInterface_mosi_m__0__HSIOM_SHIFT)
    #define FRamInterface_MOSI_M_HSIOM_SEL_GPIO  (FRamInterface_mosi_m__0__HSIOM_GPIO)
    #define FRamInterface_MOSI_M_HSIOM_SEL_SPI   (FRamInterface_mosi_m__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_MASTER_MOSI_PIN) */

#if (FRamInterface_SPI_MASTER_SCLK_PIN)
    #define FRamInterface_SCLK_M_HSIOM_REG   (*(reg32 *) FRamInterface_sclk_m__0__HSIOM)
    #define FRamInterface_SCLK_M_HSIOM_PTR   ( (reg32 *) FRamInterface_sclk_m__0__HSIOM)
    
    #define FRamInterface_SCLK_M_HSIOM_MASK      (FRamInterface_sclk_m__0__HSIOM_MASK)
    #define FRamInterface_SCLK_M_HSIOM_POS       (FRamInterface_sclk_m__0__HSIOM_SHIFT)
    #define FRamInterface_SCLK_M_HSIOM_SEL_GPIO  (FRamInterface_sclk_m__0__HSIOM_GPIO)
    #define FRamInterface_SCLK_M_HSIOM_SEL_SPI   (FRamInterface_sclk_m__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_MASTER_SCLK_PIN) */

#if (FRamInterface_SPI_MASTER_SS0_PIN)
    #define FRamInterface_SS0_M_HSIOM_REG    (*(reg32 *) FRamInterface_ss0_m__0__HSIOM)
    #define FRamInterface_SS0_M_HSIOM_PTR    ( (reg32 *) FRamInterface_ss0_m__0__HSIOM)
    
    #define FRamInterface_SS0_M_HSIOM_MASK       (FRamInterface_ss0_m__0__HSIOM_MASK)
    #define FRamInterface_SS0_M_HSIOM_POS        (FRamInterface_ss0_m__0__HSIOM_SHIFT)
    #define FRamInterface_SS0_M_HSIOM_SEL_GPIO   (FRamInterface_ss0_m__0__HSIOM_GPIO)
    #define FRamInterface_SS0_M_HSIOM_SEL_SPI    (FRamInterface_ss0_m__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_MASTER_SS0_PIN) */

#if (FRamInterface_SPI_MASTER_SS1_PIN)
    #define FRamInterface_SS1_M_HSIOM_REG    (*(reg32 *) FRamInterface_ss1_m__0__HSIOM)
    #define FRamInterface_SS1_M_HSIOM_PTR    ( (reg32 *) FRamInterface_ss1_m__0__HSIOM)
    
    #define FRamInterface_SS1_M_HSIOM_MASK       (FRamInterface_ss1_m__0__HSIOM_MASK)
    #define FRamInterface_SS1_M_HSIOM_POS        (FRamInterface_ss1_m__0__HSIOM_SHIFT)
    #define FRamInterface_SS1_M_HSIOM_SEL_GPIO   (FRamInterface_ss1_m__0__HSIOM_GPIO)
    #define FRamInterface_SS1_M_HSIOM_SEL_SPI    (FRamInterface_ss1_m__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_MASTER_SS1_PIN) */

#if (FRamInterface_SPI_MASTER_SS2_PIN)
    #define FRamInterface_SS2_M_HSIOM_REG    (*(reg32 *) FRamInterface_ss2_m__0__HSIOM)
    #define FRamInterface_SS2_M_HSIOM_PTR    ( (reg32 *) FRamInterface_ss2_m__0__HSIOM)
    
    #define FRamInterface_SS2_M_HSIOM_MASK       (FRamInterface_ss2_m__0__HSIOM_MASK)
    #define FRamInterface_SS2_M_HSIOM_POS        (FRamInterface_ss2_m__0__HSIOM_SHIFT)
    #define FRamInterface_SS2_M_HSIOM_SEL_GPIO   (FRamInterface_ss2_m__0__HSIOM_GPIO)
    #define FRamInterface_SS2_M_HSIOM_SEL_SPI    (FRamInterface_ss2_m__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_MASTER_SS2_PIN) */

#if (FRamInterface_SPI_MASTER_SS3_PIN)
    #define FRamInterface_SS3_M_HSIOM_REG    (*(reg32 *) FRamInterface_ss3_m__0__HSIOM)
    #define FRamInterface_SS3_M_HSIOM_PTR    ( (reg32 *) FRamInterface_ss3_m__0__HSIOM)
    
    #define FRamInterface_SS3_M_HSIOM_MASK      (FRamInterface_ss3_m__0__HSIOM_MASK)
    #define FRamInterface_SS3_M_HSIOM_POS       (FRamInterface_ss3_m__0__HSIOM_SHIFT)
    #define FRamInterface_SS3_M_HSIOM_SEL_GPIO  (FRamInterface_ss3_m__0__HSIOM_GPIO)
    #define FRamInterface_SS3_M_HSIOM_SEL_SPI   (FRamInterface_ss3_m__0__HSIOM_SPI)
#endif /* (FRamInterface_SPI_MASTER_SS3_PIN) */

#if (FRamInterface_UART_RX_PIN)
    #define FRamInterface_RX_HSIOM_REG   (*(reg32 *) FRamInterface_rx__0__HSIOM)
    #define FRamInterface_RX_HSIOM_PTR   ( (reg32 *) FRamInterface_rx__0__HSIOM)
    
    #define FRamInterface_RX_HSIOM_MASK      (FRamInterface_rx__0__HSIOM_MASK)
    #define FRamInterface_RX_HSIOM_POS       (FRamInterface_rx__0__HSIOM_SHIFT)
    #define FRamInterface_RX_HSIOM_SEL_GPIO  (FRamInterface_rx__0__HSIOM_GPIO)
    #define FRamInterface_RX_HSIOM_SEL_UART  (FRamInterface_rx__0__HSIOM_UART)
#endif /* (FRamInterface_UART_RX_PIN) */

#if (FRamInterface_UART_RX_WAKE_PIN)
    #define FRamInterface_RX_WAKE_HSIOM_REG   (*(reg32 *) FRamInterface_rx_wake__0__HSIOM)
    #define FRamInterface_RX_WAKE_HSIOM_PTR   ( (reg32 *) FRamInterface_rx_wake__0__HSIOM)
    
    #define FRamInterface_RX_WAKE_HSIOM_MASK      (FRamInterface_rx_wake__0__HSIOM_MASK)
    #define FRamInterface_RX_WAKE_HSIOM_POS       (FRamInterface_rx_wake__0__HSIOM_SHIFT)
    #define FRamInterface_RX_WAKE_HSIOM_SEL_GPIO  (FRamInterface_rx_wake__0__HSIOM_GPIO)
    #define FRamInterface_RX_WAKE_HSIOM_SEL_UART  (FRamInterface_rx_wake__0__HSIOM_UART)
#endif /* (FRamInterface_UART_WAKE_RX_PIN) */

#if (FRamInterface_UART_CTS_PIN)
    #define FRamInterface_CTS_HSIOM_REG   (*(reg32 *) FRamInterface_cts__0__HSIOM)
    #define FRamInterface_CTS_HSIOM_PTR   ( (reg32 *) FRamInterface_cts__0__HSIOM)
    
    #define FRamInterface_CTS_HSIOM_MASK      (FRamInterface_cts__0__HSIOM_MASK)
    #define FRamInterface_CTS_HSIOM_POS       (FRamInterface_cts__0__HSIOM_SHIFT)
    #define FRamInterface_CTS_HSIOM_SEL_GPIO  (FRamInterface_cts__0__HSIOM_GPIO)
    #define FRamInterface_CTS_HSIOM_SEL_UART  (FRamInterface_cts__0__HSIOM_UART)
#endif /* (FRamInterface_UART_CTS_PIN) */

#if (FRamInterface_UART_TX_PIN)
    #define FRamInterface_TX_HSIOM_REG   (*(reg32 *) FRamInterface_tx__0__HSIOM)
    #define FRamInterface_TX_HSIOM_PTR   ( (reg32 *) FRamInterface_tx__0__HSIOM)
    
    #define FRamInterface_TX_HSIOM_MASK      (FRamInterface_tx__0__HSIOM_MASK)
    #define FRamInterface_TX_HSIOM_POS       (FRamInterface_tx__0__HSIOM_SHIFT)
    #define FRamInterface_TX_HSIOM_SEL_GPIO  (FRamInterface_tx__0__HSIOM_GPIO)
    #define FRamInterface_TX_HSIOM_SEL_UART  (FRamInterface_tx__0__HSIOM_UART)
#endif /* (FRamInterface_UART_TX_PIN) */

#if (FRamInterface_UART_RX_TX_PIN)
    #define FRamInterface_RX_TX_HSIOM_REG   (*(reg32 *) FRamInterface_rx_tx__0__HSIOM)
    #define FRamInterface_RX_TX_HSIOM_PTR   ( (reg32 *) FRamInterface_rx_tx__0__HSIOM)
    
    #define FRamInterface_RX_TX_HSIOM_MASK      (FRamInterface_rx_tx__0__HSIOM_MASK)
    #define FRamInterface_RX_TX_HSIOM_POS       (FRamInterface_rx_tx__0__HSIOM_SHIFT)
    #define FRamInterface_RX_TX_HSIOM_SEL_GPIO  (FRamInterface_rx_tx__0__HSIOM_GPIO)
    #define FRamInterface_RX_TX_HSIOM_SEL_UART  (FRamInterface_rx_tx__0__HSIOM_UART)
#endif /* (FRamInterface_UART_RX_TX_PIN) */

#if (FRamInterface_UART_RTS_PIN)
    #define FRamInterface_RTS_HSIOM_REG      (*(reg32 *) FRamInterface_rts__0__HSIOM)
    #define FRamInterface_RTS_HSIOM_PTR      ( (reg32 *) FRamInterface_rts__0__HSIOM)
    
    #define FRamInterface_RTS_HSIOM_MASK     (FRamInterface_rts__0__HSIOM_MASK)
    #define FRamInterface_RTS_HSIOM_POS      (FRamInterface_rts__0__HSIOM_SHIFT)    
    #define FRamInterface_RTS_HSIOM_SEL_GPIO (FRamInterface_rts__0__HSIOM_GPIO)
    #define FRamInterface_RTS_HSIOM_SEL_UART (FRamInterface_rts__0__HSIOM_UART)    
#endif /* (FRamInterface_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define FRamInterface_HSIOM_DEF_SEL      (0x00u)
#define FRamInterface_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for FRamInterface_CY_SCBIP_V0 
* and FRamInterface_CY_SCBIP_V1. It is not recommended to use them for 
* FRamInterface_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define FRamInterface_HSIOM_UART_SEL     (0x09u)
#define FRamInterface_HSIOM_I2C_SEL      (0x0Eu)
#define FRamInterface_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX   (0u)
#define FRamInterface_RX_SDA_MOSI_PIN_INDEX       (0u)
#define FRamInterface_TX_SCL_MISO_PIN_INDEX       (1u)
#define FRamInterface_CTS_SCLK_PIN_INDEX       (2u)
#define FRamInterface_RTS_SS0_PIN_INDEX       (3u)
#define FRamInterface_SS1_PIN_INDEX                  (4u)
#define FRamInterface_SS2_PIN_INDEX                  (5u)
#define FRamInterface_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define FRamInterface_RX_WAKE_SDA_MOSI_PIN_MASK ((uint32) 0x01u << FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX)
#define FRamInterface_RX_SDA_MOSI_PIN_MASK     ((uint32) 0x01u << FRamInterface_RX_SDA_MOSI_PIN_INDEX)
#define FRamInterface_TX_SCL_MISO_PIN_MASK     ((uint32) 0x01u << FRamInterface_TX_SCL_MISO_PIN_INDEX)
#define FRamInterface_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << FRamInterface_CTS_SCLK_PIN_INDEX)
#define FRamInterface_RTS_SS0_PIN_MASK     ((uint32) 0x01u << FRamInterface_RTS_SS0_PIN_INDEX)
#define FRamInterface_SS1_PIN_MASK                ((uint32) 0x01u << FRamInterface_SS1_PIN_INDEX)
#define FRamInterface_SS2_PIN_MASK                ((uint32) 0x01u << FRamInterface_SS2_PIN_INDEX)
#define FRamInterface_SS3_PIN_MASK                ((uint32) 0x01u << FRamInterface_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define FRamInterface_INTCFG_TYPE_MASK           (0x03u)
#define FRamInterface_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define FRamInterface_PIN_DM_ALG_HIZ  (0u)
#define FRamInterface_PIN_DM_DIG_HIZ  (1u)
#define FRamInterface_PIN_DM_OD_LO    (4u)
#define FRamInterface_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define FRamInterface_DM_MASK    (0x7u)
#define FRamInterface_DM_SIZE    (3u)
#define FRamInterface_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) FRamInterface_DM_MASK << (FRamInterface_DM_SIZE * (pos)))) >> \
                                                              (FRamInterface_DM_SIZE * (pos)) )

#if (FRamInterface_TX_SCL_MISO_PIN)
    #define FRamInterface_CHECK_TX_SCL_MISO_PIN_USED \
                (FRamInterface_PIN_DM_ALG_HIZ != \
                    FRamInterface_GET_P4_PIN_DM(FRamInterface_uart_tx_i2c_scl_spi_miso_PC, \
                                                   FRamInterface_uart_tx_i2c_scl_spi_miso_SHIFT))
#endif /* (FRamInterface_TX_SCL_MISO_PIN) */

#if (FRamInterface_RTS_SS0_PIN)
    #define FRamInterface_CHECK_RTS_SS0_PIN_USED \
                (FRamInterface_PIN_DM_ALG_HIZ != \
                    FRamInterface_GET_P4_PIN_DM(FRamInterface_uart_rts_spi_ss0_PC, \
                                                   FRamInterface_uart_rts_spi_ss0_SHIFT))
#endif /* (FRamInterface_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define FRamInterface_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define FRamInterface_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define FRamInterface_SET_HSIOM_SEL(reg, mask, pos, sel) FRamInterface_SET_REGISTER_BITS(reg, mask, pos, sel)
#define FRamInterface_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        FRamInterface_SET_REGISTER_BITS(reg, mask, pos, intType)
#define FRamInterface_SET_INP_DIS(reg, mask, val) FRamInterface_SET_REGISTER_BIT(reg, mask, val)

/* FRamInterface_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  FRamInterface_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (FRamInterface_CY_SCBIP_V0)
#if (FRamInterface_I2C_PINS)
    #define FRamInterface_SET_I2C_SCL_DR(val) FRamInterface_scl_Write(val)

    #define FRamInterface_SET_I2C_SCL_HSIOM_SEL(sel) \
                          FRamInterface_SET_HSIOM_SEL(FRamInterface_SCL_HSIOM_REG,  \
                                                         FRamInterface_SCL_HSIOM_MASK, \
                                                         FRamInterface_SCL_HSIOM_POS,  \
                                                         (sel))
    #define FRamInterface_WAIT_SCL_SET_HIGH  (0u == FRamInterface_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
    #define FRamInterface_SET_I2C_SCL_DR(val) \
                            FRamInterface_uart_rx_wake_i2c_sda_spi_mosi_Write(val)

    #define FRamInterface_SET_I2C_SCL_HSIOM_SEL(sel) \
                    FRamInterface_SET_HSIOM_SEL(FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG,  \
                                                   FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_MASK, \
                                                   FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define FRamInterface_WAIT_SCL_SET_HIGH  (0u == FRamInterface_uart_rx_wake_i2c_sda_spi_mosi_Read())

#elif (FRamInterface_RX_SDA_MOSI_PIN)
    #define FRamInterface_SET_I2C_SCL_DR(val) \
                            FRamInterface_uart_rx_i2c_sda_spi_mosi_Write(val)


    #define FRamInterface_SET_I2C_SCL_HSIOM_SEL(sel) \
                            FRamInterface_SET_HSIOM_SEL(FRamInterface_RX_SDA_MOSI_HSIOM_REG,  \
                                                           FRamInterface_RX_SDA_MOSI_HSIOM_MASK, \
                                                           FRamInterface_RX_SDA_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define FRamInterface_WAIT_SCL_SET_HIGH  (0u == FRamInterface_uart_rx_i2c_sda_spi_mosi_Read())

#else
    #define FRamInterface_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define FRamInterface_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define FRamInterface_WAIT_SCL_SET_HIGH  (0u)
#endif /* (FRamInterface_I2C_PINS) */

/* SCB I2C: sda signal */
#if (FRamInterface_I2C_PINS)
    #define FRamInterface_WAIT_SDA_SET_HIGH  (0u == FRamInterface_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (FRamInterface_TX_SCL_MISO_PIN)
    #define FRamInterface_WAIT_SDA_SET_HIGH  (0u == FRamInterface_uart_tx_i2c_scl_spi_miso_Read())
#else
    #define FRamInterface_WAIT_SDA_SET_HIGH  (0u)
#endif /* (FRamInterface_MOSI_SCL_RX_PIN) */
#endif /* (FRamInterface_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (FRamInterface_RX_SDA_MOSI_PIN)
    #define FRamInterface_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (FRamInterface_RX_WAKE_SDA_MOSI_PIN)
    #define FRamInterface_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) FRamInterface_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(FRamInterface_UART_RX_WAKE_PIN)
    #define FRamInterface_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) FRamInterface_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (FRamInterface_RX_SDA_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define FRamInterface_REMOVE_MOSI_SCL_RX_WAKE_PIN    FRamInterface_REMOVE_RX_WAKE_SDA_MOSI_PIN
#define FRamInterface_REMOVE_MOSI_SCL_RX_PIN         FRamInterface_REMOVE_RX_SDA_MOSI_PIN
#define FRamInterface_REMOVE_MISO_SDA_TX_PIN         FRamInterface_REMOVE_TX_SCL_MISO_PIN
#ifndef FRamInterface_REMOVE_SCLK_PIN
#define FRamInterface_REMOVE_SCLK_PIN                FRamInterface_REMOVE_CTS_SCLK_PIN
#endif /* FRamInterface_REMOVE_SCLK_PIN */
#ifndef FRamInterface_REMOVE_SS0_PIN
#define FRamInterface_REMOVE_SS0_PIN                 FRamInterface_REMOVE_RTS_SS0_PIN
#endif /* FRamInterface_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define FRamInterface_MOSI_SCL_RX_WAKE_PIN   FRamInterface_RX_WAKE_SDA_MOSI_PIN
#define FRamInterface_MOSI_SCL_RX_PIN        FRamInterface_RX_SDA_MOSI_PIN
#define FRamInterface_MISO_SDA_TX_PIN        FRamInterface_TX_SCL_MISO_PIN
#ifndef FRamInterface_SCLK_PIN
#define FRamInterface_SCLK_PIN               FRamInterface_CTS_SCLK_PIN
#endif /* FRamInterface_SCLK_PIN */
#ifndef FRamInterface_SS0_PIN
#define FRamInterface_SS0_PIN                FRamInterface_RTS_SS0_PIN
#endif /* FRamInterface_SS0_PIN */

#if (FRamInterface_MOSI_SCL_RX_WAKE_PIN)
    #define FRamInterface_MOSI_SCL_RX_WAKE_HSIOM_REG     FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define FRamInterface_MOSI_SCL_RX_WAKE_HSIOM_PTR     FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define FRamInterface_MOSI_SCL_RX_WAKE_HSIOM_MASK    FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define FRamInterface_MOSI_SCL_RX_WAKE_HSIOM_POS     FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define FRamInterface_MOSI_SCL_RX_WAKE_INTCFG_REG    FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define FRamInterface_MOSI_SCL_RX_WAKE_INTCFG_PTR    FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define FRamInterface_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define FRamInterface_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  FRamInterface_RX_WAKE_SDA_MOSI_HSIOM_REG
#endif /* (FRamInterface_RX_WAKE_SDA_MOSI_PIN) */

#if (FRamInterface_MOSI_SCL_RX_PIN)
    #define FRamInterface_MOSI_SCL_RX_HSIOM_REG      FRamInterface_RX_SDA_MOSI_HSIOM_REG
    #define FRamInterface_MOSI_SCL_RX_HSIOM_PTR      FRamInterface_RX_SDA_MOSI_HSIOM_PTR
    #define FRamInterface_MOSI_SCL_RX_HSIOM_MASK     FRamInterface_RX_SDA_MOSI_HSIOM_MASK
    #define FRamInterface_MOSI_SCL_RX_HSIOM_POS      FRamInterface_RX_SDA_MOSI_HSIOM_POS
#endif /* (FRamInterface_MOSI_SCL_RX_PIN) */

#if (FRamInterface_MISO_SDA_TX_PIN)
    #define FRamInterface_MISO_SDA_TX_HSIOM_REG      FRamInterface_TX_SCL_MISO_HSIOM_REG
    #define FRamInterface_MISO_SDA_TX_HSIOM_PTR      FRamInterface_TX_SCL_MISO_HSIOM_REG
    #define FRamInterface_MISO_SDA_TX_HSIOM_MASK     FRamInterface_TX_SCL_MISO_HSIOM_REG
    #define FRamInterface_MISO_SDA_TX_HSIOM_POS      FRamInterface_TX_SCL_MISO_HSIOM_REG
#endif /* (FRamInterface_MISO_SDA_TX_PIN_PIN) */

#if (FRamInterface_SCLK_PIN)
    #ifndef FRamInterface_SCLK_HSIOM_REG
    #define FRamInterface_SCLK_HSIOM_REG     FRamInterface_CTS_SCLK_HSIOM_REG
    #define FRamInterface_SCLK_HSIOM_PTR     FRamInterface_CTS_SCLK_HSIOM_PTR
    #define FRamInterface_SCLK_HSIOM_MASK    FRamInterface_CTS_SCLK_HSIOM_MASK
    #define FRamInterface_SCLK_HSIOM_POS     FRamInterface_CTS_SCLK_HSIOM_POS
    #endif /* FRamInterface_SCLK_HSIOM_REG */
#endif /* (FRamInterface_SCLK_PIN) */

#if (FRamInterface_SS0_PIN)
    #ifndef FRamInterface_SS0_HSIOM_REG
    #define FRamInterface_SS0_HSIOM_REG      FRamInterface_RTS_SS0_HSIOM_REG
    #define FRamInterface_SS0_HSIOM_PTR      FRamInterface_RTS_SS0_HSIOM_PTR
    #define FRamInterface_SS0_HSIOM_MASK     FRamInterface_RTS_SS0_HSIOM_MASK
    #define FRamInterface_SS0_HSIOM_POS      FRamInterface_RTS_SS0_HSIOM_POS
    #endif /* FRamInterface_SS0_HSIOM_REG */
#endif /* (FRamInterface_SS0_PIN) */

#define FRamInterface_MOSI_SCL_RX_WAKE_PIN_INDEX FRamInterface_RX_WAKE_SDA_MOSI_PIN_INDEX
#define FRamInterface_MOSI_SCL_RX_PIN_INDEX      FRamInterface_RX_SDA_MOSI_PIN_INDEX
#define FRamInterface_MISO_SDA_TX_PIN_INDEX      FRamInterface_TX_SCL_MISO_PIN_INDEX
#ifndef FRamInterface_SCLK_PIN_INDEX
#define FRamInterface_SCLK_PIN_INDEX             FRamInterface_CTS_SCLK_PIN_INDEX
#endif /* FRamInterface_SCLK_PIN_INDEX */
#ifndef FRamInterface_SS0_PIN_INDEX
#define FRamInterface_SS0_PIN_INDEX              FRamInterface_RTS_SS0_PIN_INDEX
#endif /* FRamInterface_SS0_PIN_INDEX */

#define FRamInterface_MOSI_SCL_RX_WAKE_PIN_MASK FRamInterface_RX_WAKE_SDA_MOSI_PIN_MASK
#define FRamInterface_MOSI_SCL_RX_PIN_MASK      FRamInterface_RX_SDA_MOSI_PIN_MASK
#define FRamInterface_MISO_SDA_TX_PIN_MASK      FRamInterface_TX_SCL_MISO_PIN_MASK
#ifndef FRamInterface_SCLK_PIN_MASK
#define FRamInterface_SCLK_PIN_MASK             FRamInterface_CTS_SCLK_PIN_MASK
#endif /* FRamInterface_SCLK_PIN_MASK */
#ifndef FRamInterface_SS0_PIN_MASK
#define FRamInterface_SS0_PIN_MASK              FRamInterface_RTS_SS0_PIN_MASK
#endif /* FRamInterface_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_FRamInterface_H) */


/* [] END OF FILE */
