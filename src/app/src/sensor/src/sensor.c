/*
 * sensor.c
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#include "sensor.h"
#include "r_cg_macrodriver.h"
#include "r_zmod4xxx_if.h"
#include "r_hs300x_if.h"
#include "rltos_task.h"

/** callback status enumerated type*/
typedef enum
{
    SENSOR_CALLBACK_STATUS_WAIT = (0),
    SENSOR_CALLBACK_STATUS_SUCCESS,
    SENSOR_CALLBACK_STATUS_REPEAT,
}sensor_callback_status_t;

static volatile sensor_callback_status_t gs_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static volatile rm_zmod4xxx_iaq_2nd_data_t zmod_4410_data;

static volatile sensor_callback_status_t gs_demo_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static rm_hs300x_data_t hs300x_data;
static rm_hs300x_raw_data_t raw_data;

sensor_data_t dummy_sense_data; /* used to store dummy read of sensor data*/

/** @brief function to handle/log errors in sensor code*/
static void Demo_err(void);

/** @brief function to initialise zmod4410*/
static void Zmod4410_init(void);

/** @brief function to read zmod4410 and populate sensor structure
 * @param[in,out] A pointer to the sensor data structure to be populated*/
static void Zmod4410_read(sensor_data_t * const sense_data_arg);

/** @brief function to initialise hs3001*/
static void Hs300x_init(void);

/** @brief function to read hs3001 and populate sensor structure
 * @param[in,out] A pointer to the sensor data structure to be populated*/
static void Hs300x_read(sensor_data_t * const sense_data_arg);


/**********************************************************************
 * Sensor API
 *********************************************************************/
void Sensor_init(void)
{
	Hs300x_init();
	Zmod4410_init();
}
/* END OF FUNCTION*/

void Sensor_read(sensor_data_t * const sense_data_arg)
{
	Hs300x_read(sense_data_arg);
	Zmod4410_read(sense_data_arg);
}
/* END OF FUNCTION*/

void Int_dec_add(int_dec_t * const x, int_dec_t const * const y)
{
	int16_t decimal_part_temp = x->decimal_part + y->decimal_part;

	x->integer_part += y->integer_part;

	if(decimal_part_temp > 90)
	{
		x->integer_part += 1;
		x->decimal_part = decimal_part_temp - 100;
	}
	else if(decimal_part_temp < 0)
	{
		x->integer_part -= 1;
		x->decimal_part = decimal_part_temp + 100;
	}
	else
	{
		x->decimal_part = decimal_part_temp;
	}
}
/* END OF FUNCTION*/

bool Int_dec_larger_than(int_dec_t * const x, int_dec_t const * const y)
{
	bool x_larger_than_y = false;

	if(x->integer_part > y->integer_part)
	{
		x_larger_than_y = true;
	}
	else if(x->integer_part == y->integer_part)
	{
		if(x->decimal_part > y->decimal_part)
		{
			x_larger_than_y = true;
		}
	}
	else
	{
		/* Do nothing - X integer < Y integer*/
	}

	return x_larger_than_y;
}
/* END OF FUNCTION*/

/**********************************************************************
 * HS3001
 *********************************************************************/

void Hs300x_init(void)
{
	volatile fsp_err_t err = g_hs300x_sensor0.p_api->open(g_hs300x_sensor0.p_ctrl, g_hs300x_sensor0.p_cfg);

	if (FSP_SUCCESS != err)
	{
		Demo_err();
	}
}

void Hs300x_read(sensor_data_t * const sense_data_arg)
{
	fsp_err_t err;

	/* Clear status */
	gs_demo_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

	while(SENSOR_CALLBACK_STATUS_SUCCESS != gs_demo_callback_status)
	{
		/* Start measurement */
		err = g_hs300x_sensor0.p_api->measurementStart(g_hs300x_sensor0.p_ctrl);
		if (FSP_SUCCESS != err)
		{
			Demo_err();
		}

		while(SENSOR_CALLBACK_STATUS_WAIT == gs_demo_callback_status)
		{
			Rltos_task_sleep(1U);
		}
	}

	/* Clear status */
	gs_demo_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

	while(SENSOR_CALLBACK_STATUS_SUCCESS != gs_demo_callback_status)
	{
		/* Read data */
		err = g_hs300x_sensor0.p_api->read(g_hs300x_sensor0.p_ctrl, &raw_data);
		if (FSP_SUCCESS != err)
		{
			Demo_err();
		}

		while(SENSOR_CALLBACK_STATUS_WAIT == gs_demo_callback_status)
		{
			Rltos_task_sleep(1U);
		}
	}

	/* Calculate data */
	err = g_hs300x_sensor0.p_api->dataCalculate(g_hs300x_sensor0.p_ctrl, &raw_data, &hs300x_data);
	if (FSP_SUCCESS == err)
	{
		sense_data_arg->temperature_int = hs300x_data.temperature.integer_part;
		sense_data_arg->humidity_int = hs300x_data.humidity.integer_part;
	}
}

void Hs300x_user_callback0(rm_hs300x_callback_args_t * p_args)
{
	if (RM_HS300X_EVENT_SUCCESS == p_args->event)
	{
		gs_demo_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
	}
	else
	{
		gs_demo_callback_status = SENSOR_CALLBACK_STATUS_REPEAT;
	}
}

/**********************************************************************
 * ZMOD4410
 *********************************************************************/

void Zmod4410_init(void)
{
    fsp_err_t err = g_zmod4xxx_sensor0.p_api->open(g_zmod4xxx_sensor0.p_ctrl, g_zmod4xxx_sensor0.p_cfg);
    if (FSP_SUCCESS != err)
    {
        Demo_err();
    }
}

void Zmod4410_read(sensor_data_t * const sense_data_arg)
{
    fsp_err_t err;
    rm_zmod4xxx_raw_data_t raw_data;

    /* Clear status */
    gs_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

    while(SENSOR_CALLBACK_STATUS_SUCCESS != gs_i2c_callback_status)
    {
        /* Start measurement */
        err = g_zmod4xxx_sensor0.p_api->measurementStart(g_zmod4xxx_sensor0.p_ctrl);
        if (FSP_SUCCESS != err)
        {
            Demo_err();
        }

		Rltos_task_sleep(1U);
    }


    /* Clear status */
    gs_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

    while(SENSOR_CALLBACK_STATUS_SUCCESS != gs_i2c_callback_status)
    {
        /* Get status */
        err = g_zmod4xxx_sensor0.p_api->statusCheck(g_zmod4xxx_sensor0.p_ctrl);
        if (FSP_SUCCESS != err)
        {
            Demo_err();
        }

		Rltos_task_sleep(1U);
    }

    /* Clear status */
    gs_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

    while(SENSOR_CALLBACK_STATUS_SUCCESS != gs_i2c_callback_status)
    {
        /* Read data */
        err = g_zmod4xxx_sensor0.p_api->read(g_zmod4xxx_sensor0.p_ctrl, &raw_data);
        if (FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED == err)
        {
			Rltos_task_sleep(1U);

            /* Get status */
            err = g_zmod4xxx_sensor0.p_api->statusCheck(g_zmod4xxx_sensor0.p_ctrl);
            if (FSP_SUCCESS != err)
            {
                Demo_err();
            }

			Rltos_task_sleep(1U);
        }
        else if (FSP_SUCCESS != err)
        {
            Demo_err();
        }
    }

    /* Calculate data */
    err = g_zmod4xxx_sensor0.p_api->iaq2ndGenDataCalculate(g_zmod4xxx_sensor0.p_ctrl,
                                                           &raw_data,
                                                           (rm_zmod4xxx_iaq_2nd_data_t*)&zmod_4410_data);
    if (FSP_SUCCESS == err)
    {
    	sense_data_arg->zmod_calibrated = true;
    	sense_data_arg->iaq.integer_part = (int16_t)(zmod_4410_data.iaq);
    	sense_data_arg->iaq.decimal_part = (int16_t)(zmod_4410_data.iaq*100.00f)%100;
    	sense_data_arg->tvoc.integer_part = (int16_t)(zmod_4410_data.tvoc);
    	sense_data_arg->tvoc.decimal_part = (int16_t)(zmod_4410_data.tvoc*100.00f)%100;
    	sense_data_arg->eco2.integer_part = (int16_t)(zmod_4410_data.eco2);
    	sense_data_arg->eco2.decimal_part = (int16_t)(zmod_4410_data.eco2*100.00f)%100;
    }
}

void Zmod4xxx_user_i2c_callback0(rm_zmod4xxx_callback_args_t * p_args)
{
    if (RM_ZMOD4XXX_EVENT_ERROR != p_args->event)
    {
        gs_i2c_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
    }
    else
    {
        gs_i2c_callback_status = SENSOR_CALLBACK_STATUS_REPEAT;
    }
}

/**********************************************************************
 * General
 *********************************************************************/

static void Demo_err(void)
{
    while(1)
    {
        // nothing
    }
}
