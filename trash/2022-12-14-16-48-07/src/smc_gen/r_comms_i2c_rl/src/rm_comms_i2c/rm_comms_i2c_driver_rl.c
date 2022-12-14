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

/*******************************************************************************************************************//**
 * Includes
 **********************************************************************************************************************/
#include "r_comms_i2c_if.h"

/*******************************************************************************************************************//**
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Typedef definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_comms_i2c_process_in_callback(rm_comms_ctrl_t * const          p_api_ctrl,
                                             rm_comms_callback_args_t * const p_args);
static fsp_err_t rm_comms_i2c_bus_reconfigure(rm_comms_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * Private global variables
 **********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_status_check(rm_comms_ctrl_t * const p_api_ctrl);
fsp_err_t rm_comms_i2c_bus_read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t rm_comms_i2c_bus_write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t rm_comms_i2c_bus_write_read(rm_comms_ctrl_t * const            p_api_ctrl,
                                      rm_comms_write_read_params_t const write_read_params);

/*******************************************************************************************************************//**
 * Global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Checks if the I2C driver module is open.
 *
 * @retval FSP_SUCCESS                  successfully configured. (The bus of RL78 is always opened by initialization)
 **********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_status_check(rm_comms_ctrl_t * const p_api_ctrl)
{
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Function Name: rm_comms_i2c_bus_read
 * @brief Read data from the device using the I2C driver module.
 * @param[in]  p_api_ctrl           Pointer to instance control structure
 *             p_dest               Pointer to destination buffer
 *             bytes                Number of destination data
 * @retval FSP_SUCCESS              Successfully started.
 ***********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t    * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_driver_instance_t           * p_driver_instance = (i2c_driver_instance_t *) p_ctrl->p_bus->p_driver_instance;
    rm_comms_i2c_device_cfg_t    * p_device_cfg      = (rm_comms_i2c_device_cfg_t *) p_ctrl->p_cfg->p_lower_level_cfg;

    /* Reconfigure a bus */
    err = rm_comms_i2c_bus_reconfigure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear transfer data */
    p_ctrl->p_transfer_data     = NULL;
    p_ctrl->transfer_data_bytes = 0;

    if (COMMS_DRIVER_I2C == p_driver_instance->driver_type)
    {
#if (COMMS_I2C_CFG_DRIVER_I2C)
        iica_api_t * p_iica_api  = (iica_api_t *)p_driver_instance->p_api;
        MD_STATUS    status;
        uint8_t      wait = 0xFF;

        status = (p_iica_api->read)((p_device_cfg->slave_address << 1), p_dest, bytes, wait);
        switch (status)
        {
            case MD_OK:
                err = FSP_SUCCESS;
                break;
            case MD_ERROR1:
            case MD_ERROR2:
                err = FSP_ERR_IN_USE;
                break;
            default:
                err = FSP_ERR_ABORTED;
                break;
        }
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    }
    else if (COMMS_DRIVER_SAU_I2C == p_driver_instance->driver_type)
    {
#if (COMMS_I2C_CFG_DRIVER_SAU_I2C)
        sau_api_t * p_sau_api = (sau_api_t *)p_driver_instance->p_api;

        (p_sau_api->read)((p_device_cfg->slave_address << 1), p_dest, bytes);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Function Name: comms_i2c_driver_write
 * @brief Write data to the device using the I2C driver module.
 * @param[in]  p_api_ctrl           Pointer to instance control structure
 *             p_src                Pointer to source buffer
 *             bytes                Number of source data
 * @retval FSP_SUCCESS              Successfully started.
 ***********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_driver_instance_t        * p_driver_instance = (i2c_driver_instance_t *) p_ctrl->p_bus->p_driver_instance;
    rm_comms_i2c_device_cfg_t    * p_device_cfg      = (rm_comms_i2c_device_cfg_t *) p_ctrl->p_cfg->p_lower_level_cfg;

    /* Reconfigure a bus */
    err = rm_comms_i2c_bus_reconfigure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear transfer data */
    p_ctrl->p_transfer_data     = NULL;
    p_ctrl->transfer_data_bytes = 0;

    if (COMMS_DRIVER_I2C == p_driver_instance->driver_type)
    {
#if (COMMS_I2C_CFG_DRIVER_I2C)
        iica_api_t * p_iica_api  = (iica_api_t *)p_driver_instance->p_api;
        MD_STATUS    status;
        uint8_t      wait = 0xFF;

        status = (p_iica_api->write)((p_device_cfg->slave_address << 1), p_src, bytes, wait);
        switch (status)
        {
            case MD_OK:
                err = FSP_SUCCESS;
                break;
            case MD_ERROR1:
            case MD_ERROR2:
                err = FSP_ERR_IN_USE;
                break;
            default:
                err = FSP_ERR_ABORTED;
                break;
        }
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    }
    else if (COMMS_DRIVER_SAU_I2C == p_driver_instance->driver_type)
    {
#if (COMMS_I2C_CFG_DRIVER_SAU_I2C)
        sau_api_t * p_sau_api = (sau_api_t *)p_driver_instance->p_api;

        (p_sau_api->write)((p_device_cfg->slave_address << 1), p_src, bytes);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Function Name: rm_comms_i2c_driver_write_read
 * @brief Writes to I2C bus, then reads with restart.
 * @param[in]  p_api_ctrl           Pointer to instance control structure
 *             write_read_params    Write / read buffer structure
 * @retval FSP_SUCCESS              Successfully started.
 ***********************************************************************************************************************/
fsp_err_t rm_comms_i2c_bus_write_read (rm_comms_ctrl_t * const p_api_ctrl, rm_comms_write_read_params_t write_read_params)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_driver_instance_t        * p_driver_instance = (i2c_driver_instance_t *) p_ctrl->p_bus->p_driver_instance;
    rm_comms_i2c_device_cfg_t    * p_device_cfg      = (rm_comms_i2c_device_cfg_t *) p_ctrl->p_cfg->p_lower_level_cfg;

    /* Reconfigure a bus */
    err = rm_comms_i2c_bus_reconfigure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set read data */
    p_ctrl->p_transfer_data     = write_read_params.p_dest;
    p_ctrl->transfer_data_bytes = write_read_params.dest_bytes;

    if (COMMS_DRIVER_I2C == p_driver_instance->driver_type)
    {
#if (COMMS_I2C_CFG_DRIVER_I2C)
        iica_api_t * p_iica_api  = (iica_api_t *)p_driver_instance->p_api;
        MD_STATUS    status;
        uint8_t      wait = 0xFF;

        status = (p_iica_api->write)((p_device_cfg->slave_address << 1), write_read_params.p_src, write_read_params.src_bytes, wait);
        switch (status)
        {
            case MD_OK:
                err = FSP_SUCCESS;
                break;
            case MD_ERROR1:
            case MD_ERROR2:
                err = FSP_ERR_IN_USE;
                break;
            default:
                err = FSP_ERR_ABORTED;
                break;
        }
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    }
    else if (COMMS_DRIVER_SAU_I2C == p_driver_instance->driver_type)
    {
#if (COMMS_I2C_CFG_DRIVER_SAU_I2C)
        sau_api_t * p_sau_api = (sau_api_t *)p_driver_instance->p_api;

        (p_sau_api->write)((p_device_cfg->slave_address << 1), write_read_params.p_src, write_read_params.src_bytes);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Function Name: rm_comms_i2c_callback
 * @brief Common callback function called in the I2C driver callback function.
 * @param[in]  p_args                      Pointer to I2C callback arguments structure
 * @param[in]  p_api_ctrl                  Pointer to instance control structure
 ***********************************************************************************************************************/
void rm_comms_i2c_callback (rm_comms_ctrl_t const * p_api_ctrl, bool aborted)
{
    fsp_err_t                      err;
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    i2c_driver_instance_t        * p_driver_instance = (i2c_driver_instance_t *) p_ctrl->p_bus->p_driver_instance;
    rm_comms_callback_args_t       comms_i2c_args;

    /* Set error */
    if (false == aborted)
    {
        comms_i2c_args.event = RM_COMMS_EVENT_OPERATION_COMPLETE;
    }
    else
    {
        comms_i2c_args.event = RM_COMMS_EVENT_ERROR;
    }

    /* Restart reading */
    if ((NULL != p_ctrl->p_transfer_data)
        && (RM_COMMS_EVENT_OPERATION_COMPLETE == comms_i2c_args.event))
    {
        /* Read data with restart */
        err = rm_comms_i2c_bus_read(p_ctrl,
                                    p_ctrl->p_transfer_data,
                                    p_ctrl->transfer_data_bytes);

        if (FSP_SUCCESS != err)
        {
            /* Set event */
            comms_i2c_args.event = RM_COMMS_EVENT_ERROR;

            /* Call user callback function */
            rm_comms_i2c_process_in_callback(p_ctrl, &comms_i2c_args);
        }
    }
    else
    {
        if (COMMS_DRIVER_I2C == p_driver_instance->driver_type)
        {
#if (COMMS_I2C_CFG_DRIVER_I2C)
            iica_api_t *            p_iica_api        = (iica_api_t *)p_driver_instance->p_api;

    	    /* Generate stop condition */
            (p_iica_api->stopCondition)();
#endif
        }
        else if (COMMS_DRIVER_SAU_I2C == p_driver_instance->driver_type)
        {
#if (COMMS_I2C_CFG_DRIVER_SAU_I2C)
            sau_api_t * p_sau_api = (sau_api_t *)p_driver_instance->p_api;

    	    /* Generate stop condition */
            (p_sau_api->stopCondition)();
#endif
        }

        /* Call user callback function */
        rm_comms_i2c_process_in_callback(p_ctrl, &comms_i2c_args);
    }
}

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal Communications Middleware I2C driver private function.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Function Name: rm_comms_i2c_process_in_callback
 * @brief Process in callback function. Release semaphores in RTOS and call user callback.
 * @param[in] p_api_ctrl            Pointer to instance control structure
 *            p_args                Pointer to callback arguments structure
 * @retval FSP_SUCCESS              Successfully started.
 ***********************************************************************************************************************/
 static void rm_comms_i2c_process_in_callback (rm_comms_ctrl_t * const          p_api_ctrl,
                                              rm_comms_callback_args_t * const p_args)
{
    rm_comms_i2c_instance_ctrl_t * p_ctrl = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;
    {
        if (NULL != p_ctrl->p_callback)
        {
            /* Call user callback */
            p_ctrl->p_callback(p_args);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief Reconfigure I2C bus.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
static fsp_err_t rm_comms_i2c_bus_reconfigure (rm_comms_ctrl_t * const p_api_ctrl)
{
    rm_comms_i2c_instance_ctrl_t * p_ctrl            = (rm_comms_i2c_instance_ctrl_t *) p_api_ctrl;

    if (p_ctrl->p_bus->p_current_ctrl != p_ctrl)
    {
        /* Update control block on bus */
        p_ctrl->p_bus->p_current_ctrl = (rm_comms_ctrl_t *) p_ctrl;
    }

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @} (end addtogroup r_comms_i2c)
 *********************************************************************************************************************/
