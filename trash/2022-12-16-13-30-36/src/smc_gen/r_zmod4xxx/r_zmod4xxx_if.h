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

#ifndef R_ZMOD4XXX_IF_H_
#define R_ZMOD4XXX_IF_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_zmod4xxx.h"
#include "r_zmod4xxx_rl_config.h"
#include "src\rm_zmod4xxx\rm_zmod4xxx_common.h"
#if RM_ZMOD4XXX_CFG_IRQ_ENABLE
#endif

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/
/* IRQ */
#if RM_ZMOD4XXX_CFG_IRQ_ENABLE
typedef struct st_external_irq_instance
{
    void (* p_start)(void);
    void (* p_stop)(void);
} external_irq_instance_t;
#endif
typedef struct st_external_irq_callback_args
{
    void * p_context;
} external_irq_callback_args_t;

 /**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
#if (1 <= RM_ZMOD4XXX_CFG_DEVICE_NUM_MAX)
extern const rm_zmod4xxx_instance_t         g_zmod4xxx_sensor0;
extern       rm_zmod4xxx_lib_extended_cfg_t g_zmod4xxx_sensor0_extended_cfg;
#endif
#if (2 <= RM_ZMOD4XXX_CFG_DEVICE_NUM_MAX)
extern const rm_zmod4xxx_instance_t         g_zmod4xxx_sensor1;
extern       rm_zmod4xxx_lib_extended_cfg_t g_zmod4xxx_sensor1_extended_cfg;
#endif

#endif /* R_ZMOD4XXX_IF_H_ */
