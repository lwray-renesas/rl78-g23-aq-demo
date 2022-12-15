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

/** GUI EVENTS*/
#define	BACKGROUND_TEMP_HUMID 		(0x00001UL)
#define	UPDATE_TEMP_HUMID 			(0x00002UL)
#define	BACKGROUND_AIR_QUALITY		(0x00004UL)
#define	UPDATE_ALARM_IAQ			(0x00008UL)
#define	UPDATE_ALARM_TVOC			(0x00010UL)
#define	UPDATE_ALARM_ECO2			(0x00020UL)
#define	WAKEUP 						(0x00040UL)
#define	SLEEP 						(0x00080UL)
#define	BACKGROUND_LOW_BATTERY		(0x00100UL)
#define	WRITE_BACKGROUND			(0x00200UL)
#define	REDUCED_BACKLIGHT			(0x00400UL)
#define	NORMAL_BACKLIGHT			(0x00800UL)
#define	BACKGROUND_ENABLE_ALARM		(0x01000UL)
#define	BACKGROUND_ENABLE_ALARM_OFF	(0x02000UL)
#define	BACKGROUND_ENABLE_ALARM_ON	(0x04000UL)
#define	BACKGROUND_BREACH_ALARM		(0x08000UL)
#define	UPDATE_AIR_QUALITY			(0x10000UL)
#define	ALL_GUI_EVENTS				(0x1FFFFUL)

/** GUI RETURN EVENTS*/
#define DISPLAY_ASLEEP 				(0x00001UL)
#define ALL_GUI_RETURN_EVENTS		(0x00001UL)

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
