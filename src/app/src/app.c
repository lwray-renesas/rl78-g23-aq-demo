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

/** @brief 15 second inactivity timer at 200msec periodic interrupt from CTSU*/
#define CTSU_INACTIVITY_TIMEOUT	(75U)
/** @brief 6 second inactivity timer at 200msec periodic interrupt*/
#define CTSU_STATE_TIMEOUT	(30U)
/** @brief 30 minute battery check timer at 3sec periodic interrupt*/
#define BATTERY_TIMEOUT		(600U)
/** @brief 3 sec sensor check timer at 3sec periodic interrupt*/
#define SENSOR_TIMEOUT		(1U)

/** @brief enumerated type for system state machine*/
typedef enum
{
	TEMPERATURE_HUMIDITY = 0U, /**< State for reading and updating temperature and humidity to display*/
	AIR_QUALITY, /**< State for reading and updating air quality to display*/
	SET_ALARM, /**< State for setting the alarm thresholds*/
	ENABLE_ALARM, /**< State for enabling the alarm feature*/
	LOW_POWER, /**< State for low power "sleep" mode*/
	LOW_BATTERY, /**< State for low battery screen*/
	BREACH_ALARM, /**< State for alarming the air quality has dropped*/
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
static rltos_event_flag_t backlight_state = NORMAL_BACKLIGHT;
/** flag indicating battery is low*/
static bool low_battery_flag = false;
/** flag to enable/disable alarm checking*/
static bool alarm_checking_enabled = false;
/** flag indicating whether the alarm has been acknowledged*/
static bool alarm_condition = false;
/** flag to indicate whether sensor reading is enbaled*/
static bool sensor_read_enabled = true;

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
	if(LOW_POWER == sys_state)
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
	if(SET_ALARM == sys_state)
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

				Rltos_events_set(&gui_events, UPDATE_ALARM_ECO2);
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

				Rltos_events_set(&gui_events, UPDATE_ALARM_IAQ);
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

				Rltos_events_set(&gui_events, UPDATE_ALARM_TVOC);
			}
			break;

			default:
				/* Shouldn't get here*/
				break;
			}
		}
	}
	else if(ENABLE_ALARM == sys_state)
	{
		int16_t l_rot_count = Hw_get_rotary_count();

		if(l_rot_count > 0)
		{
			App_signal_activity();
			/* Clockwise = ON*/
			alarm_checking_enabled = true;
			Rltos_events_set(&gui_events, BACKGROUND_ENABLE_ALARM_ON);
		}
		else if(l_rot_count < 0)
		{
			App_signal_activity();
			/* Anti-clockwise = Off*/
			alarm_checking_enabled = false;
			Rltos_events_set(&gui_events, BACKGROUND_ENABLE_ALARM_OFF);
		}
		else
		{
			/* Do Nothing*/
		}
	}
	else
	{
		/* Do Nothing*/
	}
}
/* END OF FUNCTION*/

/**********************************************************************
 * Hardware Event Handlers
 *********************************************************************/
void App_button_click_handler(void)
{
	switch(sys_state)
	{
	case TEMPERATURE_HUMIDITY:
	{
		App_signal_activity();
		sys_state = AIR_QUALITY;
		Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY | UPDATE_AIR_QUALITY);
	}
	break;

	case AIR_QUALITY:
	case LOW_BATTERY:
	{
		App_signal_activity();
		sys_state = TEMPERATURE_HUMIDITY;
		Rltos_events_set(&gui_events, BACKGROUND_TEMP_HUMID | UPDATE_TEMP_HUMID);
	}
	break;

	case SET_ALARM:
	{
		App_signal_activity();
		sensor_read_enabled = true;
		switch(alarm_state)
		{
		case ECO2: alarm_state = IAQ; Rltos_events_set(&gui_events, UPDATE_ALARM_IAQ); break;
		case IAQ: alarm_state = TVOC; Rltos_events_set(&gui_events, UPDATE_ALARM_TVOC); break;
		case TVOC: alarm_state = ECO2; Rltos_events_set(&gui_events, UPDATE_ALARM_ECO2); break;
		default: alarm_state = IAQ; break;
		}
	}
	break;

	case BREACH_ALARM:
	{
		App_signal_activity();
		alarm_condition = false;
		sys_state = AIR_QUALITY;
		Hw_stop_rotary();
		Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY | UPDATE_AIR_QUALITY);
	}
	break;

	case ENABLE_ALARM:
	{
		App_signal_activity();
		sys_state = AIR_QUALITY;
		Hw_stop_rotary();
		Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY | UPDATE_AIR_QUALITY);
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
	if(AIR_QUALITY == sys_state)
	{
		App_signal_activity();
		sys_state = SET_ALARM;
		sensor_read_enabled = false;
		Hw_start_rotary();
		switch(alarm_state)
		{
		case IAQ: Rltos_events_set(&gui_events, UPDATE_ALARM_IAQ); break;
		case TVOC: Rltos_events_set(&gui_events, UPDATE_ALARM_TVOC); break;
		case ECO2: Rltos_events_set(&gui_events, UPDATE_ALARM_ECO2); break;
		}
	}
	else if(SET_ALARM == sys_state)
	{
		App_signal_activity();
		sys_state = ENABLE_ALARM;
		if(alarm_checking_enabled)
		{
			Rltos_events_set(&gui_events, BACKGROUND_ENABLE_ALARM | BACKGROUND_ENABLE_ALARM_ON);
		}
		else
		{
			Rltos_events_set(&gui_events, BACKGROUND_ENABLE_ALARM | BACKGROUND_ENABLE_ALARM_OFF);
		}
	}
	else
	{
		/* Do Nothing*/
	}
}
/* END OF FUNCTION*/


void App_constant_period_handler(void)
{
	static uint16_t constant_period_counter = 0U;

	++constant_period_counter;

	/* Battery checking activity*/
	if((constant_period_counter % BATTERY_TIMEOUT) == 0U)
	{
		constant_period_counter = 0U;

		if( (!low_battery_flag) && (Hw_low_battery()))
		{
			/* Set the low battery flag to ensure on CTSU wakeup we present the low battery screen*/
			low_battery_flag = true;
			/* Reduce the backlight for the application*/
			backlight_state = REDUCED_BACKLIGHT;

			/* If we are not currently in a low power state set the immediate system state to low battery & present the low battery screen*/
			if(LOW_POWER != sys_state)
			{
				sys_state = LOW_BATTERY;
				Rltos_events_set(&gui_events, BACKGROUND_LOW_BATTERY | backlight_state);
			}
		}
	}

	/* Sensor checking activity*/
	if( ((constant_period_counter % SENSOR_TIMEOUT) == 0U) && (sensor_read_enabled) )
	{
		App_read_sensors();

		if(TEMPERATURE_HUMIDITY == sys_state)
		{
			Rltos_events_set(&gui_events, UPDATE_TEMP_HUMID);
		}

		if(AIR_QUALITY == sys_state)
		{
			Rltos_events_set(&gui_events, UPDATE_AIR_QUALITY);
		}

		if(alarm_checking_enabled)
		{
			bool alarm_breached = false;

			Rltos_mutex_lock(&sensor_mutex, RLTOS_UINT_MAX);
			Rltos_mutex_lock(&alarm_sensor_mutex, RLTOS_UINT_MAX);

			alarm_breached = (Int_dec_larger_than(&sensor_data.tvoc, &alarm_sensor_data.tvoc) ||
					Int_dec_larger_than(&sensor_data.iaq, &alarm_sensor_data.iaq) ||
					Int_dec_larger_than(&sensor_data.eco2, &alarm_sensor_data.eco2)) && (sensor_data.zmod_calibrated);

			Rltos_mutex_release(&sensor_mutex);
			Rltos_mutex_release(&alarm_sensor_mutex);

			if(alarm_breached)
			{
				App_signal_activity();

				if(LOW_POWER == sys_state)
				{
					Rltos_events_set(&gui_events, WAKEUP | backlight_state | WRITE_BACKGROUND | BACKGROUND_BREACH_ALARM);
				}
				else
				{
					Rltos_events_set(&gui_events, BACKGROUND_BREACH_ALARM);
				}

				sys_state = BREACH_ALARM;
				alarm_checking_enabled = false;
				alarm_condition = true;
			}
		}
	}
}
/* END OF FUNCTION*/


void App_proximity_handler(void)
{
	static uint64_t proximity_status = 0ULL;
	static uint16_t ctsu_inactivity_counter = 0U;

	/* Immediately retrieve the CTSU data*/
	fsp_err_t err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &proximity_status, NULL, NULL);

	/* Allow failures for incomplete tuning - first few scans will inevitably be for offset compensation*/
	if((err != FSP_SUCCESS) && (err != FSP_ERR_CTSU_INCOMPLETE_TUNING))
	{
		while(1){}
	}

	/* Check if the proximity sensor has triggered*/
	if(proximity_status > 0ULL)
	{
		proximity_status = 0ULL;
		App_signal_activity();

		if(LOW_POWER == sys_state)
		{
			/* If we have detected an alarm or low battery during sleep - present alarm or low battery screen on wakeup otherwise temp & humidity*/
			if(alarm_condition)
			{
				sys_state = BREACH_ALARM;
				Rltos_events_set(&gui_events, WAKEUP | backlight_state | WRITE_BACKGROUND | BACKGROUND_BREACH_ALARM);
			}
			else if(low_battery_flag)
			{
				sys_state = LOW_BATTERY;
				Rltos_events_set(&gui_events, WAKEUP | backlight_state | WRITE_BACKGROUND | BACKGROUND_LOW_BATTERY);
			}
			else
			{
				sys_state = TEMPERATURE_HUMIDITY;
				Rltos_events_set(&gui_events, WAKEUP | backlight_state | WRITE_BACKGROUND | BACKGROUND_TEMP_HUMID | UPDATE_TEMP_HUMID);
			}
		}
	}
	else
	{
		/* Inactivity tracking*/
		if(LOW_POWER != sys_state)
		{
			if(!activity_flag)
			{
				++ctsu_inactivity_counter;
				if(ctsu_inactivity_counter > CTSU_INACTIVITY_TIMEOUT)
				{
					static rltos_event_flag_t l_disp_asleep_flag = 0U;

					/* Transition application to low power state*/
					sys_state = LOW_POWER;

					/* Ensure the rotary decoder is disabled to*/
					Hw_stop_rotary();

					/* Forcefully ensure sensor reading is enabled*/
					sensor_read_enabled = true;

					/* Wait for the display to go to sleep*/
					Rltos_events_set(&gui_events, SLEEP | BACKLIGHT_OFF);
					Rltos_events_get(&gui_return_events, DISPLAY_ASLEEP | BACKLIGHT_TURNED_OFF, &l_disp_asleep_flag, RLTOS_TRUE, RLTOS_TRUE, RLTOS_UINT_MAX);

					ctsu_inactivity_counter = 0U;
				}
				else if((ctsu_inactivity_counter % CTSU_STATE_TIMEOUT) == 0U)
				{
					/* Auto menu change from temp & humidity to air quality*/
					if(TEMPERATURE_HUMIDITY == sys_state)
					{
						sys_state = AIR_QUALITY;
						Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY | UPDATE_AIR_QUALITY);
					}
					else if(AIR_QUALITY == sys_state)
					{
						sys_state = TEMPERATURE_HUMIDITY;
						Rltos_events_set(&gui_events, BACKGROUND_TEMP_HUMID | UPDATE_TEMP_HUMID);
					}
					else
					{
						/* Shouldn't Get Here*/
					}
				}
				else
				{
					/* Do Nothing*/
				}
			}
			else
			{
				ctsu_inactivity_counter = 0U;
				activity_flag = false;
			}
		}
	}
}
/* END OF FUNCTION*/
