/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

#ifndef R_COMMS_I2C_IF_H_
#define R_COMMS_I2C_IF_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_smc_entry.h"
#include "rm_comms_i2c.h"


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/* I2C device specific configuration */
typedef struct st_rm_comms_i2c_device_cfg
{
    uint32_t const slave_address;      ///< Slave address of I2C device
    uint32_t const slave_address_bits; ///< Indicates how slave fields should be interpreted
} rm_comms_i2c_device_cfg_t;

/* RL78 Driver Instance */
typedef struct st_i2c_driver_instance
{
    uint32_t   const    driver_type;
    uint32_t * const    p_slave_address;
    void       const *  p_api;
} i2c_driver_instance_t;
/* IICA APIs */
typedef struct st_iica_api
{
    void (* open)(void);                                                                     /**< Open */
    MD_STATUS (* read)(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num, uint8_t wait);  /**< Read */
    MD_STATUS (* write)(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num, uint8_t wait); /**< Write */
    void (* stopCondition)(void);                                                            /**< Stop Condition */
    void (* close)(void);                                                                    /**< Close */
} iica_api_t;

/* SAU IIC APIs */
typedef struct st_sau_api
{
    void (* open)(void);                                                  /**< Open */
    void (* read)(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);  /**< Read */
    void (* write)(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num); /**< Write */
    void (* startCondition)(void);                                        /**< Start Condition */
    void (* stopCondition)(void);                                         /**< Stop Condition */
    void (* close)(void);                                                 /**< Close */
} sau_api_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
 /* COMMS I2C Shared Bus */
#if (1 <= COMMS_I2C_CFG_BUS_NUM_MAX)
extern rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus0_extended_cfg;
extern void rm_comms_i2c_bus0_callback(bool aborted);
#endif
#if (2 <= COMMS_I2C_CFG_BUS_NUM_MAX)
extern rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus1_extended_cfg;
extern void rm_comms_i2c_bus1_callback(bool aborted);
#endif
#if (3 <= COMMS_I2C_CFG_BUS_NUM_MAX)
extern rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus2_extended_cfg;
extern void rm_comms_i2c_bus2_callback(bool aborted);
#endif
#if (4 <= COMMS_I2C_CFG_BUS_NUM_MAX)
extern rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus3_extended_cfg;
extern void rm_comms_i2c_bus3_callback(bool aborted);
#endif
#if (5 <= COMMS_I2C_CFG_BUS_NUM_MAX)
extern rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus4_extended_cfg;
extern void rm_comms_i2c_bus4_callback(bool aborted);
#endif

 /* COMMS I2C Device */
#if (1 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
extern const rm_comms_instance_t g_comms_i2c_device0;
#endif
#if (2 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
extern const rm_comms_instance_t g_comms_i2c_device1;
#endif
#if (3 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
extern const rm_comms_instance_t g_comms_i2c_device2;
#endif
#if (4 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
extern const rm_comms_instance_t g_comms_i2c_device3;
#endif
#if (5 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
extern const rm_comms_instance_t g_comms_i2c_device4;
#endif

#endif /* R_COMMS_I2C_IF_H_ */
