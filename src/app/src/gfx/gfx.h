/*
 * gfx.h
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#ifndef APP_GFX_GFX_H_
#define APP_GFX_GFX_H_

#include <stdint.h>
#include "sensor.h"

/** @brief type to define which sensor to highlight*/
typedef enum
{
	IAQ_HIGHLIGHT = 0U,
	TVOC_HIGHLIGHT,
	ECO2_HIGHLIGHT,
	NONE_HIGHLIGHT,
}sensor_data_highlight_t;

/** @brief Initialises all graphical portions of the application*/
void Gfx_init(void);

/** @brief writes the title (renesas logo) to the display.*/
void Gfx_set_background_title(void);

/** @brief Sets up the display for temperature and humidity readings*/
void Gfx_set_background_temp_humid(void);

/** @brief Writes the temperature and humidity readings to the display.*/
void Gfx_write_temp_humid(const volatile sensor_data_t * sense_data);

/** @brief Sets up the display for air quality readings*/
void Gfx_set_background_air_quality(void);

/** @brief Writes the air quality readings to the display.
 * @param[in] sense_data - sensor data object*/
void Gfx_write_air_quality(const volatile sensor_data_t * sense_data);

/** @brief Writes the alarm data to the display*
 * @param[in] sense_data - sensor data object*/
void Gfx_write_alarm(const volatile sensor_data_t * sense_data, const sensor_data_highlight_t data_to_highlight);

/** @brief Sets the display to low battery.*/
void Gfx_set_background_low_battery(void);

/** @brief Turns display off (low power settings)*/
void Gfx_display_off(void);

/** @brief turns display on*/
void Gfx_display_on(void);

/** @brief set rduced backlight*/
void Gfx_reduced_backlight(void);

/** @brief set normal backlight*/
void Gfx_normal_backlight(void);

/** @brief set backlight off*/
void Gfx_backlight_off(void);

/** @brief Sets background for enabling alarms*/
void Gfx_set_backgound_enable_alarm(void);

/** @brief Highlights Alarm Off Text*/
void Gfx_set_backgound_enable_alarm_off(void);

/** @brief Highlights Alarm On Text*/
void Gfx_set_backgound_enable_alarm_on(void);

/** @brief Sets the display to breached Alarm Message*/
void Gfx_set_backgound_breach_alarm(void);

#endif /* APP_GFX_GFX_H_ */
