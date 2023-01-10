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
#include "hw.h"

/** callback status enumerated type*/
typedef enum
{
	SENSOR_CALLBACK_STATUS_WAIT = (0),
	SENSOR_CALLBACK_STATUS_SUCCESS,
	SENSOR_CALLBACK_STATUS_REPEAT,
}sensor_callback_status_t;

static volatile sensor_callback_status_t zmod_4410_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static volatile sensor_callback_status_t  zmod_4410_irq_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static volatile rm_zmod4xxx_iaq_2nd_data_t zmod_4410_data;

static volatile sensor_callback_status_t hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static volatile sensor_callback_status_t hs300x_oneshot_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
static rm_hs300x_data_t hs300x_data;

static volatile sensor_read_state_t sensor_read_state = SENSOR_WAITING;

/** @brief function to handle/log errors in sensor code*/
static void Demo_err(void);

/**********************************************************************
 * Sensor API
 *********************************************************************/
void Sensor_init(void)
{
	fsp_err_t err = g_hs300x_sensor0.p_api->open(g_hs300x_sensor0.p_ctrl, g_hs300x_sensor0.p_cfg);

	if (FSP_SUCCESS != err)
	{
		Demo_err();
	}

	err = g_zmod4xxx_sensor0.p_api->open(g_zmod4xxx_sensor0.p_ctrl, g_zmod4xxx_sensor0.p_cfg);
	if (FSP_SUCCESS != err)
	{
		Demo_err();
	}
}
/* END OF FUNCTION*/

bool Sensor_read(sensor_data_t * const sense_data_arg)
{
	static rm_hs300x_raw_data_t hs300x_raw_data;
	static rm_zmod4xxx_raw_data_t zmod_4410_raw_data;
	fsp_err_t err = FSP_SUCCESS;
	bool readings_completed = false;

	switch(sensor_read_state)
	{

	case SENSOR_START_MEASURMENT:
	{
		/**********************
		 * HS3001
		 *********************/
		/* Start measurement */
		err = g_hs300x_sensor0.p_api->measurementStart(g_hs300x_sensor0.p_ctrl);
		if (FSP_SUCCESS != err)
		{
			Demo_err();
		}

		/* Wait for IIC to finish*/
		while(SENSOR_CALLBACK_STATUS_WAIT == hs300x_i2c_callback_status)
		{
			HALT();
		}


		/**********************
		 * ZMOD4410
		 *********************/
		/* Start measurement */
		err = g_zmod4xxx_sensor0.p_api->measurementStart(g_zmod4xxx_sensor0.p_ctrl);
		if (FSP_SUCCESS != err)
		{
			Demo_err();
		}

		/* Wait for IIC to finish*/
		while(SENSOR_CALLBACK_STATUS_WAIT == zmod_4410_i2c_callback_status)
		{
			HALT();
		}

		Hw_start_oneshot(); /* Wait for oneshot to elapse before reading HS300X*/
		sensor_read_state = SENSOR_WAIT_TO_READ;
	}
	break;

	case SENSOR_WAIT_TO_READ:
	{
		/* Only read and process data if the sensors are ready*/
		if( (SENSOR_CALLBACK_STATUS_SUCCESS == hs300x_oneshot_callback_status) && (SENSOR_CALLBACK_STATUS_SUCCESS == zmod_4410_irq_callback_status) )
		{
			hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

			/* Read data */
			err = g_hs300x_sensor0.p_api->read(g_hs300x_sensor0.p_ctrl, &hs300x_raw_data);
			if (FSP_SUCCESS != err)
			{
				Demo_err();
			}

			/* Wait for IIC to finish*/
			while(SENSOR_CALLBACK_STATUS_WAIT == hs300x_i2c_callback_status)
			{
				HALT();
			}

			zmod_4410_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

			/* Read data */
			err = g_zmod4xxx_sensor0.p_api->read(g_zmod4xxx_sensor0.p_ctrl, &zmod_4410_raw_data);
			if (FSP_SUCCESS != err)
			{
				Demo_err();
			}

			/* Wait for IIC to finish*/
			while(SENSOR_CALLBACK_STATUS_WAIT == zmod_4410_i2c_callback_status)
			{
				HALT();
			}

			/* Calculate data */
			err = g_hs300x_sensor0.p_api->dataCalculate(g_hs300x_sensor0.p_ctrl, &hs300x_raw_data, &hs300x_data);
			if (FSP_SUCCESS == err)
			{
				sense_data_arg->temperature_int = hs300x_data.temperature.integer_part;
				sense_data_arg->humidity_int = hs300x_data.humidity.integer_part;
			}

#if RM_ZMOD4410_IAQ_2ND_GEN_ULP_CFG_LIB_ENABLE == 1
			/* TH compensation*/
			err = g_zmod4xxx_sensor0.p_api->temperatureAndHumiditySet(g_zmod4xxx_sensor0.p_ctrl,
					(float)sense_data_arg->temperature_int,
					(float)sense_data_arg->humidity_int);
			if (FSP_SUCCESS != err)
			{
				Demo_err();
			}
#endif

			/* Calculate data */
			err = g_zmod4xxx_sensor0.p_api->iaq2ndGenDataCalculate(g_zmod4xxx_sensor0.p_ctrl,
					&zmod_4410_raw_data,
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

			zmod_4410_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
			zmod_4410_irq_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
			hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_WAIT;
			hs300x_oneshot_callback_status = SENSOR_CALLBACK_STATUS_WAIT;

			sensor_read_state = SENSOR_WAITING;
			readings_completed = true;
		}
	}
	break;

	default:
		/* Do Nothing*/
		break;
	}

	return readings_completed;
}
/* END OF FUNCTION*/

bool Sensor_stop_safe(void)
{
	return (SENSOR_WAITING == sensor_read_state) ||
			((SENSOR_WAIT_TO_READ == sensor_read_state) &&
			 (SENSOR_CALLBACK_STATUS_SUCCESS == hs300x_oneshot_callback_status) &&
			 (SENSOR_CALLBACK_STATUS_SUCCESS != zmod_4410_irq_callback_status));
}
/* END OF FUNCTION*/

bool Sensor_state_machine_ready(void)
{
	return (SENSOR_START_MEASURMENT == sensor_read_state) ||
			((SENSOR_WAIT_TO_READ == sensor_read_state) &&
			 (SENSOR_CALLBACK_STATUS_SUCCESS == hs300x_oneshot_callback_status) &&
			 (SENSOR_CALLBACK_STATUS_SUCCESS == zmod_4410_irq_callback_status));
}
/* END OF FUNCTION*/

void Sensor_try_trigger_read(void)
{
	if(SENSOR_WAITING == sensor_read_state)
	{
		sensor_read_state = SENSOR_START_MEASURMENT;
	}
}
/* END OF FUNCTION*/

void Sensor_oneshot_callback(void)
{
	hs300x_oneshot_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
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

void Hs300x_user_callback0(rm_hs300x_callback_args_t * p_args)
{
	if (RM_HS300X_EVENT_SUCCESS == p_args->event)
	{
		hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
	}
	else
	{
		hs300x_i2c_callback_status = SENSOR_CALLBACK_STATUS_REPEAT;
	}
}

void Zmod4xxx_user_i2c_callback0(rm_zmod4xxx_callback_args_t * p_args)
{
	if (RM_ZMOD4XXX_EVENT_ERROR != p_args->event)
	{
		zmod_4410_i2c_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
	}
	else
	{
		zmod_4410_i2c_callback_status = SENSOR_CALLBACK_STATUS_REPEAT;
	}
}

void Zmod4xxx_user_irq_callback0(rm_zmod4xxx_callback_args_t * p_args)
{
	(void)p_args;

	zmod_4410_irq_callback_status = SENSOR_CALLBACK_STATUS_SUCCESS;
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
