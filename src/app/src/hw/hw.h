/*
 * hw.h
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#ifndef APP_HW_HW_H_
#define APP_HW_HW_H_

#include <stdint.h>
#include <stdbool.h>

#define HW_SET_EVENT(flags,event)	{flags |= event;}
#define HW_EVENT_OCCURRED(flags,event)	( ((flags) & (event)) == event )

/** @brief Enumerated type for hardware event flags*/
typedef enum
{
	NO_EVENT				=	0x0000U,
	BUTTON_CLICK 			=	0x0001U,
	BUTTON_LONG_PRESS 		=	0x0002U,
	ROTARY_COUNT_UPDATED 	=	0x0004U,
	CONSTANT_PERIOD			=	0x0008U,
	PROXIMITY_SCAN_COMPLETE	=	0x0010U,
	ALL_HARDWARE_EVENTS		=	0x001FU,
}hardware_event_t;

/** @brief Enumerated type for backlight level*/
typedef enum
{
	BACKLIGHT_OFF			=	0x0000U,
	BACKLIGHT_DIM			=	0x0001U,
	BACKLIGHT_ON			=	0x0002U,
}backlight_level_t;

/** Variable to store event flags*/
extern volatile hardware_event_t hw_event_flags;

/** @brief Initialises applications hardware - defaults the rotary to disabled*/
void Hw_init(void);

/** @brief Performs initial offset tuning in hardware*/
void Hw_ctsu_start(void);

/** @brief Starts the sensor timer runner*/
void Hw_enable_sensor_timer(void);

/** @brief Gets the current tracked rotary encoder count
 * @return integer count representing rotary encoder position (0 at power up, negative for anti-clockwise & positive for clockwise)*/
int16_t Hw_get_rotary_count(void);

/** @brief Starts the ELCL module providing a count source to the event counters*/
void Hw_start_rotary(void);

/** @brief Stops the ELCL module from providing a count source to the event counters*/
void Hw_stop_rotary(void);

/** @brief Returns true if low battery voltage is detected.
 * @return true if battey voltage is low, false otherwise.*/
bool Hw_low_battery(void);

/** @brief Function to delay a set number of milliseconds.*/
void Hw_delay_ms(uint16_t ms);

/** @brief Function to start the timer for 35ms delay*/
void Hw_start_oneshot(void);

/** @brief Triggers Alarm Hardware (Buzzer sequence + LED)*/
void Hw_trigger_alarm(void);

/** @brief Stop all alarm HW*/
void Hw_stop_alarm(void);

/** @brief Toggles alarm LED*/
void Hw_alarm_led_toggle(void);

/** @brief Disables alarm LED*/
void Hw_alarm_led_off(void);

/** @brief Set backlight level
 * @param[in] backlight_level - level of backlight.*/
void Hw_backlight_set(backlight_level_t const backlight_level);

/** @brief Sorts and processes median filter with proximity determination
 * @return true if proximal sense engaged (touch) - false otherwise (no touch)
 */
bool Hw_ctsu_get_proximity_data(void);

#endif /* APP_HW_HW_H_ */
