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

/******************************************************************************************************************//**
 * @addtogroup rm_comm_i2c_bus_rl_instance
 * @{
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stddef.h>
#include "r_comms_i2c_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define FUNC(x, y)  R_ ## x ## y
#define XOPEN(x)    FUNC(x, _Create)
#define XREAD(x)    FUNC(x, _Master_Receive)
#define XWRITE(x)   FUNC(x, _Master_Send)
#define XCOND(x)    FUNC(x, _StopCondition)
#define XCLOSE(x)   FUNC(x, _Stop)
#if (COMMS_I2C_CFG_DEVICE_NUM_MAX >= 1)
#define COMMS_I2C_CFG_BUS0_OPEN             XOPEN(COMMS_I2C_CFG_BUS0_COMPONENT)
#define COMMS_I2C_CFG_BUS0_READ             XREAD(COMMS_I2C_CFG_BUS0_COMPONENT)
#define COMMS_I2C_CFG_BUS0_WRITE            XWRITE(COMMS_I2C_CFG_BUS0_COMPONENT)
#define COMMS_I2C_CFG_BUS0_STOP             XCOND(COMMS_I2C_CFG_BUS0_COMPONENT)
#define COMMS_I2C_CFG_BUS0_CLOSE            XCLOSE(COMMS_I2C_CFG_BUS0_COMPONENT)
#endif

#if (COMMS_I2C_CFG_DEVICE_NUM_MAX >= 2)
#define COMMS_I2C_CFG_BUS1_OPEN             XOPEN(COMMS_I2C_CFG_BUS1_COMPONENT)
#define COMMS_I2C_CFG_BUS1_READ             XREAD(COMMS_I2C_CFG_BUS1_COMPONENT)
#define COMMS_I2C_CFG_BUS1_WRITE            XWRITE(COMMS_I2C_CFG_BUS1_COMPONENT)
#define COMMS_I2C_CFG_BUS1_STOP             XCOND(COMMS_I2C_CFG_BUS1_COMPONENT)
#define COMMS_I2C_CFG_BUS1_CLOSE            XCLOSE(COMMS_I2C_CFG_BUS1_COMPONENT)
#endif

#if (COMMS_I2C_CFG_DEVICE_NUM_MAX >= 3)
#define COMMS_I2C_CFG_BUS2_OPEN             XOPEN(COMMS_I2C_CFG_BUS2_COMPONENT)
#define COMMS_I2C_CFG_BUS2_READ             XREAD(COMMS_I2C_CFG_BUS2_COMPONENT)
#define COMMS_I2C_CFG_BUS2_WRITE            XWRITE(COMMS_I2C_CFG_BUS2_COMPONENT)
#define COMMS_I2C_CFG_BUS2_STOP             XCOND(COMMS_I2C_CFG_BUS2_COMPONENT)
#define COMMS_I2C_CFG_BUS2_CLOSE            XCLOSE(COMMS_I2C_CFG_BUS2_COMPONENT)
#endif

#if (COMMS_I2C_CFG_DEVICE_NUM_MAX >= 4)
#define COMMS_I2C_CFG_BUS3_OPEN             XOPEN(COMMS_I2C_CFG_BUS3_COMPONENT)
#define COMMS_I2C_CFG_BUS3_READ             XREAD(COMMS_I2C_CFG_BUS3_COMPONENT)
#define COMMS_I2C_CFG_BUS3_WRITE            XWRITE(COMMS_I2C_CFG_BUS3_COMPONENT)
#define COMMS_I2C_CFG_BUS3_STOP             XCOND(COMMS_I2C_CFG_BUS3_COMPONENT)
#define COMMS_I2C_CFG_BUS3_CLOSE            XCLOSE(COMMS_I2C_CFG_BUS3_COMPONENT)
#endif

#if (COMMS_I2C_CFG_DEVICE_NUM_MAX >= 5)
#define COMMS_I2C_CFG_BUS4_OPEN             XOPEN(COMMS_I2C_CFG_BUS4_COMPONENT)
#define COMMS_I2C_CFG_BUS4_READ             XREAD(COMMS_I2C_CFG_BUS4_COMPONENT)
#define COMMS_I2C_CFG_BUS4_WRITE            XWRITE(COMMS_I2C_CFG_BUS4_COMPONENT)
#define COMMS_I2C_CFG_BUS4_STOP             XCOND(COMMS_I2C_CFG_BUS4_COMPONENT)
#define COMMS_I2C_CFG_BUS4_CLOSE            XCLOSE(COMMS_I2C_CFG_BUS4_COMPONENT)
#endif

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/
 /* COMMS I2C Shared Bus */
#if (1 <= COMMS_I2C_CFG_BUS_NUM_MAX)
void rm_comms_i2c_bus0_callback(bool aborted);
#endif
#if (2 <= COMMS_I2C_CFG_BUS_NUM_MAX)
void rm_comms_i2c_bus1_callback(bool aborted);
#endif
#if (3 <= COMMS_I2C_CFG_BUS_NUM_MAX)
void rm_comms_i2c_bus2_callback(bool aborted);
#endif
#if (4 <= COMMS_I2C_CFG_BUS_NUM_MAX)
void rm_comms_i2c_bus3_callback(bool aborted);
#endif
#if (5 <= COMMS_I2C_CFG_BUS_NUM_MAX)
void rm_comms_i2c_bus4_callback(bool aborted);
#endif

 /* COMMS I2C Device */
#if (1 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
 void COMMS_I2C_CFG_DEVICE0_CALLBACK(rm_comms_callback_args_t * p_args); /* Callback function for device0 */
#endif
#if (2 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
 void COMMS_I2C_CFG_DEVICE1_CALLBACK(rm_comms_callback_args_t * p_args); /* Callback function for device1 */
#endif
#if (3 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
 void COMMS_I2C_CFG_DEVICE2_CALLBACK(rm_comms_callback_args_t * p_args); /* Callback function for device2 */
#endif
#if (4 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
 void COMMS_I2C_CFG_DEVICE3_CALLBACK(rm_comms_callback_args_t * p_args); /* Callback function for device3 */
#endif
#if (5 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
 void COMMS_I2C_CFG_DEVICE4_CALLBACK(rm_comms_callback_args_t * p_args); /* Callback function for device4 */
#endif

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
 /* COMMS I2C Shared Bus */
#if (1 <= COMMS_I2C_CFG_BUS_NUM_MAX)
 #if (COMMS_I2C_CFG_BUS0_DRIVER_TYPE == COMMS_DRIVER_I2C)
iica_api_t g_comms_i2c_bus0_driver_api =
 #elif (COMMS_I2C_CFG_BUS0_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C)
sau_api_t g_comms_i2c_bus0_driver_api =
 #endif
{
    .open           = COMMS_I2C_CFG_BUS0_OPEN,
    .read           = COMMS_I2C_CFG_BUS0_READ,
    .write          = COMMS_I2C_CFG_BUS0_WRITE,
    .stopCondition  = COMMS_I2C_CFG_BUS0_STOP,
    .close          = COMMS_I2C_CFG_BUS0_CLOSE,
};

const i2c_driver_instance_t g_comms_i2c_bus0_driver_instance =
{
    .driver_type = COMMS_I2C_CFG_BUS0_DRIVER_TYPE,
 #if (COMMS_I2C_CFG_BUS0_DRIVER_TYPE == COMM_DRIVER_NONE)
    .p_api       = NULL,
 #else
    .p_api       = (void const *)&g_comms_i2c_bus0_driver_api,
 #endif
};
rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus0_extended_cfg =
{
    .p_driver_instance = (void*)&g_comms_i2c_bus0_driver_instance,
    .p_current_ctrl    = NULL,
};
#endif

#if (2 <= COMMS_I2C_CFG_BUS_NUM_MAX)
 #if (COMMS_I2C_CFG_BUS1_DRIVER_TYPE == COMMS_DRIVER_I2C)
iica_api_t g_comms_i2c_bus1_driver_api =
 #elif (COMMS_I2C_CFG_BUS1_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C)
sau_api_t g_comms_i2c_bus1_driver_api =
 #endif
{
    .open           = COMMS_I2C_CFG_BUS1_OPEN,
    .read           = COMMS_I2C_CFG_BUS1_READ,
    .write          = COMMS_I2C_CFG_BUS1_WRITE,
    .stopCondition  = COMMS_I2C_CFG_BUS1_STOP,
    .close          = COMMS_I2C_CFG_BUS1_CLOSE,
};
const i2c_driver_instance_t g_comms_i2c_bus1_driver_instance =
{
    .driver_type = COMMS_I2C_CFG_BUS1_DRIVER_TYPE,
 #if (COMMS_I2C_CFG_BUS1_DRIVER_TYPE == COMM_DRIVER_NONE)
    .p_api       = NULL,
 #else
    .p_api       = (void const *)&g_comms_i2c_bus1_driver_api,
 #endif
};
rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus1_extended_cfg =
{
    .p_driver_instance = (void*)&g_comms_i2c_bus1_driver_instance,
    .p_current_ctrl    = NULL,
};
#endif

#if (3 <= COMMS_I2C_CFG_BUS_NUM_MAX)
 #if (COMMS_I2C_CFG_BUS2_DRIVER_TYPE == COMMS_DRIVER_I2C)
iica_api_t g_comms_i2c_bus2_driver_api =
 #elif (COMMS_I2C_CFG_BUS2_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C)
sau_api_t g_comms_i2c_bus2_driver_api =
#endif
{
    .open           = COMMS_I2C_CFG_BUS2_OPEN,
    .read           = COMMS_I2C_CFG_BUS2_READ,
    .write          = COMMS_I2C_CFG_BUS2_WRITE,
    .stopCondition  = COMMS_I2C_CFG_BUS2_STOP,
    .close          = COMMS_I2C_CFG_BUS2_CLOSE,
};
const i2c_driver_instance_t g_comms_i2c_bus2_driver_instance =
{
    .driver_type = COMMS_I2C_CFG_BUS2_DRIVER_TYPE,
 #if (COMMS_I2C_CFG_BUS2_DRIVER_TYPE == COMM_DRIVER_NONE)
    .p_api       = NULL,
 #else
    .p_api       = (void const *)&g_comms_i2c_bus2_driver_api,
 #endif
};
rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus2_extended_cfg =
{
    .p_driver_instance = (void*)&g_comms_i2c_bus2_driver_instance,
    .p_current_ctrl    = NULL,
};
#endif

#if (4 <= COMMS_I2C_CFG_BUS_NUM_MAX)
 #if (COMMS_I2C_CFG_BUS3_DRIVER_TYPE == COMMS_DRIVER_I2C)
iica_api_t g_comms_i2c_bus3_driver_api =
 #elif (COMMS_I2C_CFG_BUS3_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C)
sau_api_t g_comms_i2c_bus3_driver_api =
#endif
{
    .open           = COMMS_I2C_CFG_BUS3_OPEN,
    .read           = COMMS_I2C_CFG_BUS3_READ,
    .write          = COMMS_I2C_CFG_BUS3_WRITE,
    .stopCondition  = COMMS_I2C_CFG_BUS3_STOP,
    .close          = COMMS_I2C_CFG_BUS3_CLOSE,
};
const i2c_driver_instance_t g_comms_i2c_bus3_driver_instance =
{
    .driver_type = COMMS_I2C_CFG_BUS3_DRIVER_TYPE,
 #if (COMMS_I2C_CFG_BUS3_DRIVER_TYPE == COMM_DRIVER_NONE)
    .p_api       = NULL,
 #else
    .p_api       = (void const *)&g_comms_i2c_bus3_driver_api,
 #endif
};
rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus3_extended_cfg =
{
    .p_driver_instance = (void*)&g_comms_i2c_bus3_driver_instance,
    .p_current_ctrl    = NULL,
};
#endif

#if (5 <= COMMS_I2C_CFG_BUS_NUM_MAX)
 #if (COMMS_I2C_CFG_BUS4_DRIVER_TYPE == COMMS_DRIVER_I2C)
iica_api_t g_comms_i2c_bus4_driver_api =
 #elif (COMMS_I2C_CFG_BUS4_DRIVER_TYPE == COMMS_DRIVER_SAU_I2C)
sau_api_t g_comms_i2c_bus4_driver_api =
#endif
{
    .open           = COMMS_I2C_CFG_BUS4_OPEN,
    .read           = COMMS_I2C_CFG_BUS4_READ,
    .write          = COMMS_I2C_CFG_BUS4_WRITE,
    .stopCondition  = COMMS_I2C_CFG_BUS4_STOP,
    .close          = COMMS_I2C_CFG_BUS4_CLOSE,
};
const i2c_driver_instance_t g_comms_i2c_bus4_driver_instance =
{
    .driver_type = COMMS_I2C_CFG_BUS4_DRIVER_TYPE,
 #if (COMMS_I2C_CFG_BUS4_DRIVER_TYPE == COMM_DRIVER_NONE)
    .p_api       = NULL,
 #else
    .p_api       = (void const *)&g_comms_i2c_bus4_driver_api,
 #endif
};
rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus4_extended_cfg =
{
    .p_driver_instance = (void*)&g_comms_i2c_bus4_driver_instance,
    .p_current_ctrl    = NULL,
};
#endif

/* COMMS I2C Device */
#if (1 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
rm_comms_i2c_instance_ctrl_t g_comms_i2c_device0_ctrl;
const rm_comms_i2c_device_cfg_t g_comms_i2c_device0_lower_level_cfg =
{
    .slave_address      = COMMS_I2C_CFG_DEVICE0_SLAVE_ADDR,
};
const rm_comms_cfg_t g_comms_i2c_device0_cfg =
{
    .p_lower_level_cfg = (void *)&g_comms_i2c_device0_lower_level_cfg,
    .p_extend          = (void *)(&(COMMS_I2C_CFG_DEVICE0_BUS_CH)),
    .p_callback        = (void (*)(rm_comms_callback_args_t *))COMMS_I2C_CFG_DEVICE0_CALLBACK,
};
const rm_comms_instance_t g_comms_i2c_device0 =
{
    .p_ctrl = &g_comms_i2c_device0_ctrl,
    .p_cfg  = &g_comms_i2c_device0_cfg,
    .p_api  = &g_comms_on_comms_i2c,
};
#endif

#if (2 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
rm_comms_i2c_instance_ctrl_t g_comms_i2c_device1_ctrl;
const rm_comms_i2c_device_cfg_t g_comms_i2c_device1_lower_level_cfg =
{
    .slave_address      = COMMS_I2C_CFG_DEVICE1_SLAVE_ADDR,
};
const rm_comms_cfg_t g_comms_i2c_device1_cfg =
{
    .p_lower_level_cfg = (void *)&g_comms_i2c_device1_lower_level_cfg,
    .p_extend          = (void *)(&(COMMS_I2C_CFG_DEVICE1_BUS_CH)),
    .p_callback        = (void (*)(rm_comms_callback_args_t *))COMMS_I2C_CFG_DEVICE1_CALLBACK,
};
const rm_comms_instance_t g_comms_i2c_device1 =
{
    .p_ctrl = &g_comms_i2c_device1_ctrl,
    .p_cfg  = &g_comms_i2c_device1_cfg,
    .p_api  = &g_comms_on_comms_i2c,
};
#endif

#if (3 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
rm_comms_i2c_instance_ctrl_t g_comms_i2c_device2_ctrl;
const rm_comms_i2c_device_cfg_t g_comms_i2c_device2_lower_level_cfg =
{
    .slave_address      = COMMS_I2C_CFG_DEVICE2_SLAVE_ADDR,
};
const rm_comms_cfg_t g_comms_i2c_device2_cfg =
{
    .p_lower_level_cfg = (void *)&g_comms_i2c_device2_lower_level_cfg,
    .p_extend          = (void *)(&(COMMS_I2C_CFG_DEVICE2_BUS_CH)),
    .p_callback        = (void (*)(rm_comms_callback_args_t *))COMMS_I2C_CFG_DEVICE2_CALLBACK,
};
const rm_comms_instance_t g_comms_i2c_device2 =
{
    .p_ctrl = &g_comms_i2c_device2_ctrl,
    .p_cfg  = &g_comms_i2c_device2_cfg,
    .p_api  = &g_comms_on_comms_i2c,
};
#endif

#if (4 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
rm_comms_i2c_instance_ctrl_t g_comms_i2c_device3_ctrl;
const rm_comms_i2c_device_cfg_t g_comms_i2c_device3_lower_level_cfg =
{
    .slave_address      = COMMS_I2C_CFG_DEVICE3_SLAVE_ADDR,
};
const rm_comms_cfg_t g_comms_i2c_device3_cfg =
{
    .p_lower_level_cfg = (void *)&g_comms_i2c_device3_lower_level_cfg,
    .p_extend          = (void *)(&(COMMS_I2C_CFG_DEVICE3_BUS_CH)),
    .p_callback        = (void (*)(rm_comms_callback_args_t *))COMMS_I2C_CFG_DEVICE3_CALLBACK,
};
const rm_comms_instance_t g_comms_i2c_device3 =
{
    .p_ctrl = &g_comms_i2c_device3_ctrl,
    .p_cfg  = &g_comms_i2c_device3_cfg,
    .p_api  = &g_comms_on_comms_i2c,
};
#endif

#if (5 <= COMMS_I2C_CFG_DEVICE_NUM_MAX)
rm_comms_i2c_instance_ctrl_t g_comms_i2c_device4_ctrl;
const rm_comms_i2c_device_cfg_t g_comms_i2c_device4_lower_level_cfg =
{
    .slave_address      = COMMS_I2C_CFG_DEVICE4_SLAVE_ADDR,
};
const rm_comms_cfg_t g_comms_i2c_device4_cfg =
{
    .p_lower_level_cfg = (void *)&g_comms_i2c_device4_lower_level_cfg,
    .p_extend          = (void *)(&(COMMS_I2C_CFG_DEVICE4_BUS_CH)),
    .p_callback        = (void (*)(rm_comms_callback_args_t *))COMMS_I2C_CFG_DEVICE4_CALLBACK,
};
const rm_comms_instance_t g_comms_i2c_device4 =
{
    .p_ctrl = &g_comms_i2c_device4_ctrl,
    .p_cfg  = &g_comms_i2c_device4_cfg,
    .p_api  = &g_comms_on_comms_i2c,
};
#endif

#if (1 <= COMMS_I2C_CFG_BUS_NUM_MAX)
/**********************************************************************************************************************
 * Function Name: rm_comms_i2c_bus0_callback
 * Description  : The function callback by r_riic_rx or r_sci_iic_rx
 * Arguments    :
 * Return Value :
 * Doxygen commenting is provided with prototype in this file.
 *********************************************************************************************************************/
void rm_comms_i2c_bus0_callback(bool aborted)
{   
    if (NULL != g_comms_i2c_bus0_extended_cfg.p_current_ctrl)
    {
        rm_comms_i2c_callback (g_comms_i2c_bus0_extended_cfg.p_current_ctrl, aborted);
    }    
}
/**********************************************************************************************************************
 * End of function rm_comms_i2c_bus0_callback
 *********************************************************************************************************************/
#endif

#if (2 <= COMMS_I2C_CFG_BUS_NUM_MAX)
/**********************************************************************************************************************
 * Function Name: rm_comms_i2c_bus1_callback
 * Description  : The function callback
 * Arguments    :
 * Return Value :
 * Doxygen commenting is provided with prototype in this file.
 *********************************************************************************************************************/
void rm_comms_i2c_bus1_callback(bool aborted)
{
    if (NULL != g_comms_i2c_bus1_extended_cfg.p_current_ctrl)
    {
        rm_comms_i2c_callback (g_comms_i2c_bus1_extended_cfg.p_current_ctrl, aborted);
    }    
}
/**********************************************************************************************************************
 * End of function rm_comms_i2c_bus1_callback
 *********************************************************************************************************************/
#endif

#if (3 <= COMMS_I2C_CFG_BUS_NUM_MAX)
/**********************************************************************************************************************
 * Function Name: rm_comms_i2c_bus2_callback
 * Description  : The function callback
 * Arguments    :
 * Return Value :
 * Doxygen commenting is provided with prototype in this file.
 *********************************************************************************************************************/
void rm_comms_i2c_bus2_callback(bool aborted)
{
    if (NULL != g_comms_i2c_bus2_extended_cfg.p_current_ctrl)
    {
        rm_comms_i2c_callback (g_comms_i2c_bus2_extended_cfg.p_current_ctrl, aborted);
    }    
}
/**********************************************************************************************************************
 * End of function rm_comms_i2c_bus2_callback
 *********************************************************************************************************************/
#endif

#if (4 <= COMMS_I2C_CFG_BUS_NUM_MAX)
/**********************************************************************************************************************
 * Function Name: rm_comms_i2c_bus3_callback
 * Description  : The function callback
 * Arguments    :
 * Return Value :
 * Doxygen commenting is provided with prototype in this file.
 *********************************************************************************************************************/
void rm_comms_i2c_bus3_callback(bool aborted)
{
    if (NULL != g_comms_i2c_bus3_extended_cfg.p_current_ctrl)
    {
        rm_comms_i2c_callback (g_comms_i2c_bus3_extended_cfg.p_current_ctrl, aborted);
    }    
}
/**********************************************************************************************************************
 * End of function rm_comms_i2c_bus3_callback
 *********************************************************************************************************************/
#endif

#if (5 <= COMMS_I2C_CFG_BUS_NUM_MAX)
/**********************************************************************************************************************
 * Function Name: rm_comms_i2c_bus4_callback
 * Description  : The function callback
 * Arguments    :
 * Return Value :
 * Doxygen commenting is provided with prototype in this file.
 *********************************************************************************************************************/
void rm_comms_i2c_bus4_callback(bool aborted)
{
    if (NULL != g_comms_i2c_bus4_extended_cfg.p_current_ctrl)
    {
        rm_comms_i2c_callback (g_comms_i2c_bus4_extended_cfg.p_current_ctrl, aborted);
    }    
}
/**********************************************************************************************************************
 * End of function rm_comms_i2c_bus4_callback
 *********************************************************************************************************************/
#endif


/******************************************************************************************************************//**
 * @} (end addtogroup rm_comm_i2c_bus_rl_instance)
 *********************************************************************************************************************/
