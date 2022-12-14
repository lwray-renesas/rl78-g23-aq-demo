/*
 * app.h
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "gfx.h"
#include "sensor.h"
#include "hw.h"
#include "rltos_task.h"
#include "rltos_events.h"
#include "rltos_mutex.h"
#include "rltos_semaphore.h"

/** @brief Enumerate type for gui event flags*/
typedef enum
{
	BACKGROUND_TEMP_HUMID 		=	0x0001U,
	UPDATE_TEMP_HUMID 			=	0x0002U,
	BACKGROUND_AIR_QUALITY		=	0x0004U,
	UPDATE_AIR_QUALITY 			=	0x0008U,
	BACKGROUND_UPDATE_ALARMS	=	0x0010U,
	UPDATE_ALARMS 				=	0x0020U,
	WAKEUP 						=	0x0040U,
	SLEEP 						=	0x0080U,
	BACKGROUND_LOW_BATTERY		=	0x0100U,
	WRITE_BACKGROUND			=	0x0200U,
	REDUCED_BACKLIGHT			=	0x0400U,
	NORMAL_BACKLIGHT			=	0x0800U,
	BACKLIGHT_OFF				=	0x1000U,
	ALL_GUI_EVENTS				=	0x1FFFU,
}gui_event_t;

/** @brief Enumerate type for gui return signal event flags*/
typedef enum
{
	DISPLAY_ASLEEP 				=	0x0001U,
	DISPLAY_BACKLIGHT_OFF		=	0x0002U,
	ALL_GUI_RETURN_EVENTS		=	0x0003U,
}gui_return_event_t;

/** Shared application events*/
extern rltos_events_t gui_events;
extern rltos_events_t gui_return_events;

/** @brief Interface for intialising sensors*/
void App_init_sensors(void);

/** @brief Interface for invoking a sensor update*/
void App_read_sensors(void);

/** @brief Interface for reading the latest sensor data
 * @param[in,out] A pointer to the sensor data structure to be populated*/
void App_get_sensor_data(sensor_data_t * const sense_data_arg);

/** @brief Interface for updating alarm values
 * @param[in,out] A pointer to the sensor data structure to be populated*/
void App_get_alarm_sensor_data(sensor_data_t * const sense_data_arg);

/** @brief Interface for system power management.*/
void App_power_management(void);

/** @brief Signals user activity to application for use in power management*/
void App_signal_activity(void);

/** @brief returns the current hardware events and clears the internal event variable.
 * @return hardware events variable copy.
 */
hardware_event_t App_get_hw_events(void);

/** @brief Handles rotary encoder I/O in set alarm state*/
void App_rotary_processing(void);

/**********************************************************************
 * Hardware Event Handlers
 *********************************************************************/
/** @brief Event handler for button click*/
void App_button_click_handler(void);

/** @brief Event handler for button long press*/
void App_button_long_press_handler(void);

/** @brief Event handler for RTC constant period interrupt*/
void App_rtc_handler(void);

/** @brrief Event handler for proximity events*/
void App_proximity_handler(void);

#endif /* APP_APP_H_ */
