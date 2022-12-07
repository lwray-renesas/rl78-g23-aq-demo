/*
 * app.c
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#include "app.h"
#include "r_smc_entry.h"
#include "r_hs300x_if.h"
#include "r_zmod4xxx_if.h"


/** @brief enumerated type for system state machine*/
typedef enum
{
	POWER_ON = 0U, /**< State for power on*/
	TEMPERATURE_HUMIDITY, /**< State for reading and updating temperature and humidity to display*/
	AIR_QUALITY, /**< State for reading and updating air quality to display*/
	SET_ALARM, /**< State for setting the alarm thresholds*/
	LOW_POWER, /**< State for low power "sleep" mode*/
	LOW_BATTERY, /**< State when the batteries are no longer of sufficient voltage to run the system*/
}system_state_t;

/** @brief enumerated type for alarm setting state machine*/
typedef enum
{
	ECO2 = 0U, /**< Alarm controls targeted at eco2 level*/
	IAQ, /**< Alarm controls targeted at IAQ level*/
	TVOC /**< Alarm controls targeted at TVOC level*/
}alarm_state_t;

/** Sensor data structure mutex*/
extern rltos_mutex_t sensor_mutex;
/** Alarm Sensor Data Mutex*/
extern rltos_mutex_t alarm_sensor_mutex;
/** System state mutex*/
extern rltos_mutex_t sys_state_mutex;


/** Local sensor data structure*/
static sensor_data_t sensor_data;
/** Local alarm sensor data structure*/
static sensor_data_t alarm_sensor_data = {0, 0, {1,0}, {1,0}, {400,0}, false};
/** System state variable*/
static system_state_t sys_state = POWER_ON;
/** Alarm setting state variable*/
static alarm_state_t alarm_state = ECO2;


/** @brief rtos friendly function to set the system state*/
static void App_set_state(system_state_t const target_state);

/** @brief rtos friendly function to get the current system state.
 * @return the current system state*/
static system_state_t App_get_state(void);

void App_init_sensors(void)
{
	/* First sensor reading is bogus - so perform two reads on initialisation*/
	Rltos_mutex_lock(&sensor_mutex, RLTOS_UINT_MAX);
	Sensor_init();
	Sensor_read(&sensor_data);
	Sensor_read(&sensor_data);
	Rltos_mutex_release(&sensor_mutex);
}
/* END OF FUNCTION*/

void App_read_sensors(void)
{
	Rltos_mutex_lock(&sensor_mutex, RLTOS_UINT_MAX);
	Sensor_read(&sensor_data);
	Rltos_mutex_release(&sensor_mutex);
}
/* END OF FUNCTION*/

void App_get_sensor_data(sensor_data_t * const sense_data_arg)
{
	Rltos_mutex_lock(&sensor_mutex, RLTOS_UINT_MAX);
	memcpy(sense_data_arg, &sensor_data, sizeof(sensor_data_t));
	Rltos_mutex_release(&sensor_mutex);
}
/* END OF FUNCTION*/

void App_get_alarm_sensor_data(sensor_data_t * const sense_data_arg)
{
	Rltos_mutex_lock(&alarm_sensor_mutex, RLTOS_UINT_MAX);
	sense_data_arg->eco2 = alarm_sensor_data.eco2;
	sense_data_arg->tvoc = alarm_sensor_data.tvoc;
	sense_data_arg->iaq = alarm_sensor_data.iaq;
	Rltos_mutex_release(&alarm_sensor_mutex);
}
/* END OF FUNCTION*/

static void App_set_state(system_state_t const target_state)
{
	Rltos_mutex_lock(&sys_state_mutex, RLTOS_UINT_MAX);
	sys_state = target_state;
	Rltos_mutex_release(&sys_state_mutex);
}
/* END OF FUNCTION*/

static system_state_t App_get_state(void)
{
	system_state_t l_sys_state = POWER_ON;

	Rltos_mutex_lock(&sys_state_mutex, RLTOS_UINT_MAX);
	l_sys_state = sys_state;
	Rltos_mutex_release(&sys_state_mutex);

	return l_sys_state;
}
/* END OF FUNCTION*/

/**********************************************************************
 * Hardware Event Handlers
 *********************************************************************/
void App_button_click_handler(void)
{
	const system_state_t l_sys_state = App_get_state();

	switch(l_sys_state)
	{
	case POWER_ON:
	{
		App_set_state(TEMPERATURE_HUMIDITY);
		Rltos_events_set(&gui_events, WAKEUP | NORMAL_BACKLIGHT | WRITE_BACKGROUND | BACKGROUND_TEMP_HUMID);
	}
	break;

	case TEMPERATURE_HUMIDITY:
	{
		App_set_state(AIR_QUALITY);
		Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY);
	}
	break;

	case AIR_QUALITY:
	{
		App_set_state(LOW_BATTERY);
		Rltos_events_set(&gui_events, BACKGROUND_LOW_BATTERY);
	}
	break;

	case LOW_BATTERY:
	{
		App_set_state(TEMPERATURE_HUMIDITY);
		Rltos_events_set(&gui_events, NORMAL_BACKLIGHT | BACKGROUND_TEMP_HUMID);
	}
	break;

	default:
		/* If not explicitly handled we just drop the event*/
		break;
	}
}
/* END OF FUNCTION*/


void App_button_long_press_handler(void)
{
	if(AIR_QUALITY == App_get_state())
	{
		App_set_state(SET_ALARM);
		Hw_start_rotary();
		Rltos_events_set(&gui_events, BACKGROUND_UPDATE_ALARMS);

		while(1)
		{
			static rltos_uint evnt;
			Rltos_events_get(&hardware_events, ALL_HARDWARE_EVENTS, &evnt, RLTOS_TRUE, RLTOS_FALSE, 0U);

			/* On long press return to alarm screen*/
			if(EVENT_OCCURED(evnt, BUTTON_LONG_PRESS))
			{
				App_set_state(AIR_QUALITY);
				Hw_stop_rotary();
				Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY);
				break;
			}
			else if(EVENT_OCCURED(evnt, BUTTON_CLICK))
			{
				switch(alarm_state)
				{
				case ECO2: alarm_state = IAQ; break;
				case IAQ: alarm_state = TVOC; break;
				case TVOC: alarm_state = ECO2; break;
				default: alarm_state = IAQ; break;
				}
			}
			else
			{
				static int16_t l_rot_count = 0;

				l_rot_count = Hw_get_rotary_count();

				if(l_rot_count != 0)
				{
					l_rot_count *= 10;

					switch(alarm_state)
					{
					case ECO2:
					{
						Rltos_mutex_lock(&alarm_sensor_mutex, RLTOS_UINT_MAX);

						alarm_sensor_data.eco2.integer_part += l_rot_count;

						if(alarm_sensor_data.eco2.integer_part < 0)
						{
							alarm_sensor_data.eco2.integer_part = 0;
						}

						Rltos_mutex_release(&alarm_sensor_mutex);
					}
					break;

					case IAQ:
					{
						static int_dec_t temp_iaq = {0,0};

						temp_iaq.decimal_part = l_rot_count % 100;
						temp_iaq.integer_part = l_rot_count / 100;

						Rltos_mutex_lock(&alarm_sensor_mutex, RLTOS_UINT_MAX);

						Int_dec_add(&alarm_sensor_data.iaq, &temp_iaq);

						if(alarm_sensor_data.iaq.integer_part < 0)
						{
							alarm_sensor_data.iaq.integer_part = 0;
							alarm_sensor_data.iaq.decimal_part = 0;
						}

						Rltos_mutex_release(&alarm_sensor_mutex);
					}
					break;

					case TVOC:
					{
						static int_dec_t temp_tvoc = {0,0};

						temp_tvoc.decimal_part = l_rot_count % 100;
						temp_tvoc.integer_part = l_rot_count / 100;

						Rltos_mutex_lock(&alarm_sensor_mutex, RLTOS_UINT_MAX);

						Int_dec_add(&alarm_sensor_data.tvoc, &temp_tvoc);

						if(alarm_sensor_data.tvoc.integer_part < 0)
						{
							alarm_sensor_data.tvoc.integer_part = 0;
							alarm_sensor_data.tvoc.decimal_part = 0;
						}

						Rltos_mutex_release(&alarm_sensor_mutex);
					}
					break;

					default:
						/* Shouldn't get here*/
						break;
					}

					Rltos_events_set(&gui_events, UPDATE_ALARMS);
				}
			}

			Rltos_task_sleep(1U);
		}
	}
}
/* END OF FUNCTION*/


void App_ctsu_proximity_handler(void)
{

}
/* END OF FUNCTION*/


void App_rtc_battery_handler(void)
{

}
/* END OF FUNCTION*/


void App_rtc_sensor_handler(void)
{
	App_read_sensors();

	if(App_get_state() == TEMPERATURE_HUMIDITY)
	{
		Rltos_events_set(&gui_events, UPDATE_TEMP_HUMID);
	}

	if(App_get_state() == AIR_QUALITY)
	{
		Rltos_events_set(&gui_events, UPDATE_AIR_QUALITY);
	}
}
/* END OF FUNCTION*/

