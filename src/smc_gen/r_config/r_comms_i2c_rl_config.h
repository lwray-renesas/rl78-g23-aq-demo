/* Generated configuration header file - do not edit */
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
/***********************************************************************************************************************
* File Name    : r_comms_i2c_rl_config.h
* Device(s)    : RL78
* Description  : The file r_comms_i2c_rl_config.h is used to configure your HS300x. r_comms_i2c_rl_config.h should be
*                included somewhere in your package so that the r_bsp code has access to it.
*                This file (r_bsp_config_reference.h) is just a reference file that the user can use to make their own
*                r_comms_i2c_rl_config.h file.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 30.09.2020 1.00    First Release
***********************************************************************************************************************/
/* Guards against multiple inclusion */
#ifndef R_COMMS_I2C_CONFIG_H
#define R_COMMS_I2C_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
#define COMMS_DRIVER_NONE       (0)
#define COMMS_DRIVER_I2C        (1)
#define COMMS_DRIVER_SAU_I2C    (2)

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_COMMS_I2C_CFG_PARAM_CHECKING_ENABLE (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF BUSES */
#define COMMS_I2C_CFG_BUS_NUM_MAX               (1)         /* Number (max.) of I2C buses */

/* SPECIFY NUMBER OF DEVICES */
#define COMMS_I2C_CFG_DEVICE_NUM_MAX            (2)         /* Number (max.) of I2C devices */

/* SPECIFY DRIVER TYPE, COMPONENT NAME */
/* For Bus No.0 */
#define COMMS_I2C_CFG_BUS0_DRIVER_TYPE          (COMMS_DRIVER_I2C) /* Driver type of I2C Bus */
#define COMMS_I2C_CFG_BUS0_COMPONENT            Config_IICA0

/* For Bus No.1 */
#define COMMS_I2C_CFG_BUS1_DRIVER_TYPE          (COMMS_DRIVER_NONE) /* Driver type of I2C Bus */
#define COMMS_I2C_CFG_BUS1_COMPONENT            Config_IIC00

/* For Bus No.2 */
#define COMMS_I2C_CFG_BUS2_DRIVER_TYPE          (COMMS_DRIVER_NONE) /* Driver type of I2C Bus */
#define COMMS_I2C_CFG_BUS2_COMPONENT            Config_IIC00

/* For Bus No.3 */
#define COMMS_I2C_CFG_BUS3_DRIVER_TYPE          (COMMS_DRIVER_NONE) /* Driver type of I2C Bus */
#define COMMS_I2C_CFG_BUS3_COMPONENT            Config_IIC00

/* For Bus No.4 */
#define COMMS_I2C_CFG_BUS4_DRIVER_TYPE          (COMMS_DRIVER_NONE) /* Driver type of I2C Bus */
#define COMMS_I2C_CFG_BUS4_COMPONENT            Config_IIC00

/* SPECIFY SLAVE ADDRESS AND CALLBACK FUNCTION EACH DEVICE */
/* For Device No.0 */
#define COMMS_I2C_CFG_DEVICE0_BUS_CH            (g_comms_i2c_bus0_extended_cfg)
#define COMMS_I2C_CFG_DEVICE0_SLAVE_ADDR        (0x44) /* Slave address */
#define COMMS_I2C_CFG_DEVICE0_CALLBACK          (rm_hs300x_callback0) /* Callback function */

/* For Device No.1 */
#define COMMS_I2C_CFG_DEVICE1_BUS_CH            (g_comms_i2c_bus0_extended_cfg)
#define COMMS_I2C_CFG_DEVICE1_SLAVE_ADDR        (0x32) /* Slave address */
#define COMMS_I2C_CFG_DEVICE1_CALLBACK          (rm_zmod4xxx_callback0) /* Callback function */

/* For Device No.2 */
#define COMMS_I2C_CFG_DEVICE2_BUS_CH            (g_comms_i2c_bus0_extended_cfg)
#define COMMS_I2C_CFG_DEVICE2_SLAVE_ADDR        (0x00) /* Slave address */
#define COMMS_I2C_CFG_DEVICE2_CALLBACK          (comms_i2c_user_callback2) /* Callback function */

/* For Device No.3 */
#define COMMS_I2C_CFG_DEVICE3_BUS_CH            (g_comms_i2c_bus0_extended_cfg)
#define COMMS_I2C_CFG_DEVICE3_SLAVE_ADDR        (0x00) /* Slave address */
#define COMMS_I2C_CFG_DEVICE3_CALLBACK          (comms_i2c_user_callback3) /* Callback function */

/* For Device No.4 */
#define COMMS_I2C_CFG_DEVICE4_BUS_CH            (g_comms_i2c_bus0_extended_cfg)
#define COMMS_I2C_CFG_DEVICE4_SLAVE_ADDR        (0x00) /* Slave address */
#define COMMS_I2C_CFG_DEVICE4_CALLBACK          (comms_i2c_user_callback4) /* Callback function */

#if (COMMS_I2C_CFG_BUS0_DRIVER_TYPE == COMMS_DRIVER_I2C ) \
||  (COMMS_I2C_CFG_BUS1_DRIVER_TYPE == COMMS_DRIVER_I2C ) \
||  (COMMS_I2C_CFG_BUS2_DRIVER_TYPE == COMMS_DRIVER_I2C ) \
||  (COMMS_I2C_CFG_BUS3_DRIVER_TYPE == COMMS_DRIVER_I2C ) \
||  (COMMS_I2C_CFG_BUS4_DRIVER_TYPE == COMMS_DRIVER_I2C )
#define COMMS_I2C_CFG_DRIVER_I2C                (1) /* 1: Used IICA */
#else
#define COMMS_I2C_CFG_DRIVER_I2C                (0) /* 0: Unused IICA */
#endif
#if (COMMS_I2C_CFG_BUS0_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C ) \
||  (COMMS_I2C_CFG_BUS1_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C ) \
||  (COMMS_I2C_CFG_BUS2_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C ) \
||  (COMMS_I2C_CFG_BUS3_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C ) \
||  (COMMS_I2C_CFG_BUS4_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C )
#define COMMS_I2C_CFG_DRIVER_SAU_I2C            (1) /* 1: Used SAU IIC */
#else
#define COMMS_I2C_CFG_DRIVER_SAU_I2C            (0) /* 0: Unused SAU IIC */
#endif

#endif  /* R_COMM_I2C_DEVICE_CONFIG_H */
