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

#define EVENT_OCCURED(flags,event)	((flags & event) == event)

/** Enumerate type for gui event flags*/
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
	ALL_GUI_EVENTS				=	0x0FFFU,
}gui_event_t;

/** Enumerated type for hardware event flags*/
typedef enum
{
	BUTTON_CLICK 			=	0x0001U,
	BUTTON_LONG_PRESS 		=	0x0002U,
	ROTARY_COUNT_UPDATED 	=	0x0004U,
	CTSU_PROXIMITY 			=	0x0008U,
	RTC_BATTERY 			=	0x0010U,
	RTC_SENSOR 				=	0x0020U,
	ALL_HARDWARE_EVENTS		=	0x003FU,
}hardware_event_t;

/** Shared application events*/
extern rltos_events_t gui_events;
extern rltos_events_t hardware_events;

/** @brief rtos friendly interface for intialising sensors*/
void App_init_sensors(void);

/** @brief rtos friendly interface for invoking a sensor update*/
void App_read_sensors(void);

/** @brief rtos friendly interface for reading the latest sensor data
 * @param[in,out] A pointer to the sensor data structure to be populated*/
void App_get_sensor_data(sensor_data_t * const sense_data_arg);

/** @brief rtos friendly interface for updating alarm values
 * @param[in,out] A pointer to the sensor data structure to be populated*/
void App_get_alarm_sensor_data(sensor_data_t * const sense_data_arg);

/**********************************************************************
 * Hardware Event Handlers
 *********************************************************************/
/** @brief Event handler for button click*/
void App_button_click_handler(void);

/** @brief Event handler for button long press*/
void App_button_long_press_handler(void);

/** @brief Event handler for ctsu proximity*/
void App_ctsu_proximity_handler(void);

/** @brief Event handler for rtc battery*/
void App_rtc_battery_handler(void);

/** @brief Event handler for rtc sensor*/
void App_rtc_sensor_handler(void);

#endif /* APP_APP_H_ */
