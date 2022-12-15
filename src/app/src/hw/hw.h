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
	RTC_CONSTANT_PERIOD		=	0x0008U,
	PROXIMITY_SCAN_COMPLETE	=	0x0010U,
	ALL_HARDWARE_EVENTS		=	0x001FU,
}hardware_event_t;

/** Variable to store event flags*/
extern volatile hardware_event_t hw_event_flags;

/** @brief Initialises applications hardware - defaults the rotary to disabled*/
void Hw_init(void);

/** @brief Gets the current tracked rotary encoder count
 * @return integer count representing rotary encoder position (0 at power up, negative for anti-clockwise & positive for clockwise)*/
int16_t Hw_get_rotary_count(void);

/** @brief Starts the ELCL module providing a count source to the event counters*/
void Hw_start_rotary(void);

/** @brief Stops the ELCL module from providing a count source to the event counters*/
void Hw_stop_rotary(void);

/** @brief Enables the capacitive proximity detection circuit*/
void Hw_enable_proximity_detection(void);

/** @brief Disables the capacitive proximity detection circuit*/
void Hw_disable_proximity_detection(void);

/** @brief Returns true if low battery voltage is detected.
 * @return true if battey voltage is low, false otherwise.*/
bool Hw_low_battery(void);

#endif /* APP_HW_HW_H_ */
