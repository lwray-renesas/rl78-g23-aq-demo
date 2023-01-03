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
#define	BACKGROUND_TEMP_HUMID 		(0x000001UL)
#define	UPDATE_TEMP_HUMID 			(0x000002UL)
#define	BACKGROUND_AIR_QUALITY		(0x000004UL)
#define	UPDATE_ALARM_IAQ			(0x000008UL)
#define	UPDATE_ALARM_TVOC			(0x000010UL)
#define	UPDATE_ALARM_ECO2			(0x000020UL)
#define	WAKEUP 						(0x000040UL)
#define	SLEEP 						(0x000080UL)
#define	BACKGROUND_LOW_BATTERY		(0x000100UL)
#define	WRITE_BACKGROUND			(0x000200UL)
#define	REDUCED_BACKLIGHT			(0x000400UL)
#define	NORMAL_BACKLIGHT			(0x000800UL)
#define	BACKGROUND_ENABLE_ALARM		(0x001000UL)
#define	BACKGROUND_ENABLE_ALARM_OFF	(0x002000UL)
#define	BACKGROUND_ENABLE_ALARM_ON	(0x004000UL)
#define	BACKGROUND_BREACH_ALARM		(0x008000UL)
#define	UPDATE_AIR_QUALITY			(0x010000UL)
#define BACKLIGHT_OFF				(0x020000UL)
#define DISPLAY_OFFSET_TUNING		(0x040000UL)
#define DISPLAY_COUNTDOWN			(0x080000UL)
#define DISPLAY_TUNING_ELIPSE		(0x100000UL)
#define DISPLAY_SUCCESS				(0x200000UL)
#define	ALL_GUI_EVENTS				(0x3FFFFFUL)

/** GUI RETURN EVENTS*/
#define DISPLAY_ASLEEP 				(0x000001UL)
#define BACKLIGHT_TURNED_OFF		(0x000002UL)
#define TUNING_ELIPSE_DISPLAYED		(0x000004UL)
#define SUCCESS_DISPLAYED			(0x000008UL)
#define COUNTDOWN_DISPLAYED			(0x000010UL)
#define ALL_GUI_RETURN_EVENTS		(0x00001FUL)

/** Shared application events*/
extern rltos_events_t gui_events;
extern rltos_events_t gui_return_events;

/** @brief Interface for intialising sensors*/
void App_init_sensors(void);

/** @brief Performs initial offset tuning in RTOS & user friendly way*/
void App_initial_offset_tuning(void);

/** @brief Interface for invoking a sensor update*/
void App_read_sensors(void);

/** @brief Interface for reading the latest sensor data
 * @param[in,out] A pointer to the sensor data structure to be populated*/
void App_get_sensor_data(sensor_data_t * const sense_data_arg);

/** @brief Interface for updating alarm values
 * @param[in,out] A pointer to the sensor data structure to be populated*/
void App_get_alarm_sensor_data(sensor_data_t * const sense_data_arg);

/** @brief Interface for system power management.
 * @return hardware events variable copy.*/
hardware_event_t App_power_management(void);

/** @brief Signals user activity to application for use in power management*/
void App_signal_activity(void);

/** @brief Handles rotary encoder I/O in set alarm state*/
void App_rotary_processing(void);

/**********************************************************************
 * Hardware Event Handlers
 *********************************************************************/
/** @brief Event handler for button click*/
void App_button_click_handler(void);

/** @brief Event handler for button long press*/
void App_button_long_press_handler(void);

/** @brief Event handler for constant period interrupt*/
void App_constant_period_handler(void);

/** @brrief Event handler for proximity events*/
void App_proximity_handler(void);

#endif /* APP_APP_H_ */
