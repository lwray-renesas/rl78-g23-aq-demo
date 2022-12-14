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
#include "qe_touch_config.h"

/** @brief 15 second inactivity timer at 1sec periodic interrupt*/
#define RTC_INACTIVITY_TIMEOUT	(14U)
/** @brief 30 minute battery check timer at 1sec periodic interrupt*/
#define RTC_BATTERY_TIMEOUT		(1800U)
/** @brief 1 minute sensor check timer at 1sec periodic interrupt*/
#define RTC_SENSOR_TIMEOUT		(60U)

/** @brief enumerated type for system state machine*/
typedef enum
{
	TEMPERATURE_HUMIDITY = 0U, /**< State for reading and updating temperature and humidity to display*/
	AIR_QUALITY, /**< State for reading and updating air quality to display*/
	SET_ALARM, /**< State for setting the alarm thresholds*/
	LOW_POWER, /**< State for low power "sleep" mode*/
	LOW_BATTERY, /**< State for low battery screen*/
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
static system_state_t sys_state = LOW_POWER;
/** Alarm setting state variable*/
static alarm_state_t alarm_state = ECO2;
/** signal variable used by system to symbolise user activity - default inactive on power up*/
static bool activity_flag = false;
/** variable to maintain peristence of backlight across application depending on battery state*/
static gui_event_t backlight_state = NORMAL_BACKLIGHT;
/** flag indicating battery is low*/
static bool low_battery_flag = false;

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

void App_power_management(void)
{
	system_state_t l_sys_state = App_get_state();

	if(LOW_POWER == l_sys_state)
	{
		STOP(); /* Enter low power mode*/
	}
	else
	{
		HALT(); /* Just halt the cpu until an event occurs which we want to handle*/
	}
}
/* END OF FUNCTION*/

void App_signal_activity(void)
{
	activity_flag = true;
}
/* END OF FUNCTION*/

hardware_event_t App_get_hw_events(void)
{
	hardware_event_t l_hw_events = NO_EVENT;
	RLTOS_PREPARE_CRITICAL_SECTION();

	RLTOS_ENTER_CRITICAL_SECTION();

	l_hw_events = hw_event_flags;
	hw_event_flags = NO_EVENT;

	RLTOS_EXIT_CRITICAL_SECTION();

	return l_hw_events;
}
/* END OF FUNCTION*/

void App_rotary_processing(void)
{
	system_state_t l_sys_state = App_get_state();

	if(SET_ALARM == l_sys_state)
	{
		int16_t l_rot_count = Hw_get_rotary_count();

		if(l_rot_count != 0)
		{
			App_signal_activity();
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
	system_state_t l_sys_state = TEMPERATURE_HUMIDITY;

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
	case TEMPERATURE_HUMIDITY:
	{
		App_signal_activity();
		App_set_state(AIR_QUALITY);
		Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY);
	}
	break;

	case AIR_QUALITY:
	case LOW_BATTERY:
	{
		App_signal_activity();
		App_set_state(TEMPERATURE_HUMIDITY);
		Rltos_events_set(&gui_events, BACKGROUND_TEMP_HUMID);
	}
	break;

	case SET_ALARM:
	{
		App_signal_activity();
		switch(alarm_state)
		{
		case ECO2: alarm_state = IAQ; break;
		case IAQ: alarm_state = TVOC; break;
		case TVOC: alarm_state = ECO2; break;
		default: alarm_state = IAQ; break;
		}
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
	system_state_t l_sys_state = App_get_state();

	if(AIR_QUALITY == l_sys_state)
	{
		App_signal_activity();
		App_set_state(SET_ALARM);
		Hw_start_rotary();
		Rltos_events_set(&gui_events, BACKGROUND_UPDATE_ALARMS);
	}
	else if(SET_ALARM == l_sys_state)
	{
		App_signal_activity();
		App_set_state(AIR_QUALITY);
		Hw_stop_rotary();
		Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY);
	}
	else
	{
		/* Do Nothing*/
	}

}
/* END OF FUNCTION*/


void App_rtc_handler(void)
{
	static uint16_t rtc_counter = 0U;
	static uint16_t rtc_inactivity_counter = 0U;
	system_state_t l_sys_state = LOW_POWER;

	++rtc_counter;

	l_sys_state = App_get_state();

	/* Read the battery every 30 minutes*/
	if((rtc_counter % RTC_BATTERY_TIMEOUT) == 0U)
	{
		/* TODO: Handle battery read & implement below on low battery reading!*/

#if 0 /* if battery is low*/
		/* Set the low battery flag to ensure on CTSU wakeups we present the low batttery screen*/
		low_battery_flag = true;
		/* Reduce the backlight for the application*/
		backlight_state = REDUCED_BACKLIGHT;

		/* If we are not currently in a low power state set the immediate system state to low battery & present the low battery screen*/
		if(l_sys_state != LOW_POWER)
		{
			App_set_state(LOW_BATTERY);
			Rltos_events_set(&gui_events, BACKGROUND_LOW_BATTERY | backlight_state);
		}
#endif
	}

	if((rtc_counter % RTC_SENSOR_TIMEOUT) == 0U)
	{
		/* Sensor Read Processing*/
		App_read_sensors();

		if(TEMPERATURE_HUMIDITY == l_sys_state)
		{
			Rltos_events_set(&gui_events, UPDATE_TEMP_HUMID);
		}

		if(AIR_QUALITY == l_sys_state)
		{
			Rltos_events_set(&gui_events, UPDATE_AIR_QUALITY);
		}

		/* TODO: Alarm check!*/
	}

	/* If not in the low power state - check for inactivity*/
	if(LOW_POWER != l_sys_state)
	{
		/* If the system is inactive for at least one consecutive minute*/
		if(!activity_flag)
		{
			++rtc_inactivity_counter;
			if(rtc_inactivity_counter > RTC_INACTIVITY_TIMEOUT)
			{
				static rltos_uint l_disp_asleep_flag = 0U;

				/* Transition application to low power state*/
				App_set_state(LOW_POWER);

				/* Ensure the rotary decoder is disabled to*/
				Hw_stop_rotary();

				/* Wait for the display to go to sleep*/
				Rltos_events_set(&gui_events, SLEEP | BACKLIGHT_OFF);
				Rltos_events_get(&gui_return_events, DISPLAY_ASLEEP | DISPLAY_BACKLIGHT_OFF, &l_disp_asleep_flag, RLTOS_TRUE, RLTOS_TRUE, RLTOS_UINT_MAX);

				rtc_inactivity_counter = 0U;
			}
		}
		else
		{
			rtc_inactivity_counter = 0U;
			activity_flag = false;
		}
	}
}
/* END OF FUNCTION*/


void App_proximity_handler(void)
{
	static uint64_t proximity_status = 0ULL;

	/* Immediately retrieve the CTSU data*/
	fsp_err_t err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &proximity_status, NULL, NULL);

	if((err != FSP_SUCCESS) && (err != FSP_ERR_CTSU_INCOMPLETE_TUNING))
	{
		while(1){}
	}

	/* Check if the proximity sensor has triggered*/
	if(proximity_status > 0ULL)
	{
		proximity_status = 0ULL;
		App_signal_activity();

		if(LOW_POWER == App_get_state())
		{
			/* If we have detected a low battery during sleep - present low battery screen on wakeup otherwise temp & humidity*/
			if(low_battery_flag)
			{
				App_set_state(LOW_BATTERY);
				Rltos_events_set(&gui_events, WAKEUP | backlight_state | WRITE_BACKGROUND | BACKGROUND_LOW_BATTERY);
			}
			else
			{
				App_set_state(TEMPERATURE_HUMIDITY);
				Rltos_events_set(&gui_events, WAKEUP | backlight_state | WRITE_BACKGROUND | BACKGROUND_TEMP_HUMID);
			}
		}
	}
}
/* END OF FUNCTION*/
