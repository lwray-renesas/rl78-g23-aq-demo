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

/** @brief 15 second inactivity timer at 1sec periodic interrupt*/
#define INACTIVITY_TIMEOUT	(15U)
/** @brief 6 second state inactivity timer at 1sec periodic interrupt*/
#define STATE_TIMEOUT	(3U)
/** @brief 30 minute battery check timer at 1sec periodic interrupt*/
#define BATTERY_TIMEOUT		(1800U)

#if RM_ZMOD4410_IAQ_2ND_GEN_ULP_CFG_LIB_ENABLE == 1
/** @brief 90 sec sensor check timer at 1sec periodic interrupt*/
#define SENSOR_TIMEOUT		(90U)
#elif RM_ZMOD4410_IAQ_2ND_GEN_CFG_LIB_ENABLE == 1
/** @brief 3 sec sensor check timer at 1sec periodic interrupt*/
#define SENSOR_TIMEOUT		(3U)
#else
#error "Sensor unsupported"
#endif


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
static sensor_data_t alarm_sensor_data = {0, 0, {2,50}, {3,50}, {1000,0}, false};
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
/** temporary flag to enable/disable alarm checking during selection process*/
static bool alarm_checking_enabled_temp = false;
/** flag indicating whether the alarm has been acknowledged*/
static bool alarm_condition = false;
/** counter to count the alarm singalling time*/
static uint16_t alarm_length = 0U;

/** @brief gets hardware events
 * @return returns hardware event copy.
 */
static inline hardware_event_t Get_hw_events(void)
{
	hardware_event_t l_hw_events = NO_EVENT;
	RLTOS_PREPARE_CRITICAL_SECTION();

	RLTOS_ENTER_CRITICAL_SECTION();
	l_hw_events = hw_event_flags;
	hw_event_flags &= ~l_hw_events; /* Clear the events which have been detected*/
	RLTOS_EXIT_CRITICAL_SECTION();

	return l_hw_events;
}
/* END OF FUNCTION*/

void App_init_sensors(void)
{
	Rltos_mutex_lock(&sensor_mutex, RLTOS_UINT_MAX);
	Sensor_init();
	Rltos_mutex_release(&sensor_mutex);
}
/* END OF FUNCTION*/

void App_initial_offset_tuning(void)
{
	uint8_t delay_count = 0U;
	static rltos_event_flag_t l_disp_flags = 0U;

	/* Set initial offset tuning screen "CTSU Tuning\n Click button and put me down!"*/
	Rltos_events_set(&gui_events, WAKEUP | backlight_state | DISPLAY_OFFSET_TUNING);

	/* Wait for user to click*/
	while(!HW_EVENT_OCCURRED(Get_hw_events(), BUTTON_CLICK))
	{
		NOP();
	}

	Hw_release_zmod_reset();
	Hw_enable_sensor_timer();

	/* Delay 5seconds (use RTC) and show count down to user*/
	while(delay_count < 5U)
	{
		Rltos_events_set(&gui_events, DISPLAY_COUNTDOWN);
		Rltos_task_sleep(0U);

		/* Wait for periodic (1sec) interrupt*/
		while(!HW_EVENT_OCCURRED(Get_hw_events(), CONSTANT_PERIOD))
		{
			NOP();
		}

		++delay_count;
	}

	delay_count = 0U;

	/* Show user "Tuning..." screen*/
	Rltos_events_set(&gui_events, DISPLAY_TUNING_ELIPSE);
	Rltos_task_sleep(0U);

	/* Perform offset tuning*/
	Hw_ctsu_start();

	/* Show user Success Screen*/
	Rltos_events_set(&gui_events, DISPLAY_SUCCESS);
	Rltos_task_sleep(0U);

	/* Delay 2seconds (use RTC)*/
	while(delay_count < 2U)
	{
		/* Wait for periodic (1sec) interrupt*/
		while(!HW_EVENT_OCCURRED(Get_hw_events(), CONSTANT_PERIOD))
		{
			NOP();
		}

		++delay_count;
	}

	/* Shutdown display and enter application*/
	Rltos_events_set(&gui_events, WRITE_BACKGROUND | SLEEP | BACKLIGHT_OFF);
	Rltos_events_get(&gui_return_events, DISPLAY_ASLEEP | BACKLIGHT_TURNED_OFF, &l_disp_flags, RLTOS_TRUE, RLTOS_TRUE, RLTOS_UINT_MAX);
}
/* END OF FUNCTION*/

bool App_read_sensors(void)
{
	bool sensor_read_complete = false;

	Rltos_mutex_lock(&sensor_mutex, RLTOS_UINT_MAX);
	sensor_read_complete = Sensor_read(&sensor_data);
	Rltos_mutex_release(&sensor_mutex);

	return sensor_read_complete;
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

hardware_event_t App_power_management(void)
{
	/* Only enter low power mode if the sensor state machines do not require processing*/
	if(!Sensor_state_machine_ready())
	{
		/* Only enter stop state if we are not reading the sensors or we are awaiting the IRQ on the ZMOD while in the system LOW_POWER state*/
		if( (LOW_POWER == sys_state) && (Sensor_stop_safe()) )
		{
			/* Enter STOP - only leave if we have a periodic interrupt to process or proximity scan*/
			STOP();
		}
		else
		{
			/* Enter HALT - just while we wait for another event to process, then regardless of event, exit power management*/
			HALT();
		}
	}

	return Get_hw_events();
}
/* END OF FUNCTION*/

void App_signal_activity(void)
{
	activity_flag = true;
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
			alarm_checking_enabled_temp = true;
			Rltos_events_set(&gui_events, BACKGROUND_ENABLE_ALARM_ON);
		}
		else if(l_rot_count < 0)
		{
			App_signal_activity();
			/* Anti-clockwise = Off*/
			alarm_checking_enabled_temp = false;
			Rltos_events_set(&gui_events, BACKGROUND_ENABLE_ALARM_OFF);
		}
		else
		{
			/* Do Nothing*/
		}
	}
	else if(TEMPERATURE_HUMIDITY == sys_state)
	{
		int16_t l_rot_count = Hw_get_rotary_count();

		if(0 != l_rot_count)
		{
			App_signal_activity();
			sys_state = AIR_QUALITY;
			Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY | UPDATE_AIR_QUALITY);
		}
	}
	else if(AIR_QUALITY == sys_state)
	{
		int16_t l_rot_count = Hw_get_rotary_count();

		if(0 != l_rot_count)
		{
			App_signal_activity();
			sys_state = TEMPERATURE_HUMIDITY;
			Rltos_events_set(&gui_events, BACKGROUND_TEMP_HUMID | UPDATE_TEMP_HUMID);
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

		alarm_length = 0U;
		Hw_alarm_led_off();
		Hw_stop_alarm();
		alarm_condition = false;

		sys_state = AIR_QUALITY;
		Rltos_events_set(&gui_events, BACKGROUND_AIR_QUALITY | UPDATE_AIR_QUALITY);
	}
	break;

	case ENABLE_ALARM:
	{
		/* Latch in the alarm checking state*/
		alarm_checking_enabled = alarm_checking_enabled_temp;
		App_signal_activity();
		sys_state = AIR_QUALITY;
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
		/* Disable the alarm checking when updating alarm data*/
		alarm_checking_enabled = false;
		sys_state = SET_ALARM;
		switch(alarm_state)
		{
		case IAQ: Rltos_events_set(&gui_events, UPDATE_ALARM_IAQ); break;
		case TVOC: Rltos_events_set(&gui_events, UPDATE_ALARM_TVOC); break;
		case ECO2: Rltos_events_set(&gui_events, UPDATE_ALARM_ECO2); break;
		default:
			/* Do Nothing*/
			break;
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


void App_constant_period_handler(bool sensor_readings_completed)
{
	static uint16_t constant_period_counter = 0U;
	static uint16_t inactivity_counter = 0U;

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
	if((constant_period_counter % SENSOR_TIMEOUT) == 0U)
	{
		/* If the sensors handler is in the waiting state - trigger the state machine*/
		Sensor_try_trigger_read();
	}

	/* Handle alarm HW*/
	if(alarm_condition)
	{
		Hw_alarm_led_toggle();

		if(alarm_length > 10U)
		{
			Hw_stop_alarm();
		}
		else
		{
			++alarm_length;
		}
	}

	/* Inactivity tracking*/
	if(LOW_POWER != sys_state)
	{
		if(!activity_flag)
		{
			++inactivity_counter;
			if(inactivity_counter > INACTIVITY_TIMEOUT)
			{
				static rltos_event_flag_t l_disp_asleep_flag = 0U;

				/* Transition application to low power state*/
				sys_state = LOW_POWER;

				/* Wait for the display to go to sleep*/
				Rltos_events_set(&gui_events, SLEEP | BACKLIGHT_OFF);
				Rltos_events_get(&gui_return_events, DISPLAY_ASLEEP | BACKLIGHT_TURNED_OFF, &l_disp_asleep_flag, RLTOS_TRUE, RLTOS_TRUE, RLTOS_UINT_MAX);

				inactivity_counter = 0U;
			}
			else if((inactivity_counter % STATE_TIMEOUT) == 0U)
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
			inactivity_counter = 0U;
			activity_flag = false;
		}
	}

	/* Check if readings are ready to use*/
	if(sensor_readings_completed)
	{
		if(TEMPERATURE_HUMIDITY == sys_state)
		{
			Rltos_events_set(&gui_events, UPDATE_TEMP_HUMID);
		}

		if(AIR_QUALITY == sys_state)
		{
			Rltos_events_set(&gui_events, UPDATE_AIR_QUALITY);
		}

		if(alarm_checking_enabled && sensor_data.zmod_calibrated)
		{
			bool alarm_breached = false;

			Rltos_mutex_lock(&sensor_mutex, RLTOS_UINT_MAX);
			Rltos_mutex_lock(&alarm_sensor_mutex, RLTOS_UINT_MAX);

			alarm_breached = (Int_dec_larger_than(&sensor_data.tvoc, &alarm_sensor_data.tvoc) ||
					Int_dec_larger_than(&sensor_data.iaq, &alarm_sensor_data.iaq) ||
					Int_dec_larger_than(&sensor_data.eco2, &alarm_sensor_data.eco2));

			Rltos_mutex_release(&sensor_mutex);
			Rltos_mutex_release(&alarm_sensor_mutex);

			if(alarm_breached)
			{
				App_signal_activity();

				Hw_trigger_alarm();

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
				alarm_checking_enabled_temp = false;
				alarm_condition = true;
			}
		}
	}
}
/* END OF FUNCTION*/


void App_proximity_handler(void)
{
	/* Check if the proximity sensor has triggered*/
	if(Hw_ctsu_get_proximity_data())
	{
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
}
/* END OF FUNCTION*/
