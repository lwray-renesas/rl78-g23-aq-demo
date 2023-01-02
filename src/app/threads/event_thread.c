/*
 * event_thread.c
 *
 *  Created on: 2 Nov 2022
 *      Author: a5126135
 */

#include "r_smc_entry.h"
#include "app.h"

static hardware_event_t hw_event_rx_flags = NO_EVENT; /**< event flags for hw events*/

/** @brief The event handler and dispatcher for the application.
 * All events from hardware and state changes are managed.
 * Events dispatched to various system components from this thread.
 * Sensors and battery voltage read.
 */
void Event_thread_main(void)
{
	/* Initialise the sensor portion of the application*/
	App_init_sensors();

	/* Enable ctsu on power up*/
	Hw_enable_proximity_detection();

	while(1)
	{
		/* Monitor system for power management decisions i.e. entering low power mode & state management when returning from it*/
		hw_event_rx_flags = App_power_management();

		if(HW_EVENT_OCCURRED(hw_event_rx_flags, BUTTON_CLICK))
		{
			App_button_click_handler();
		}

		if(HW_EVENT_OCCURRED(hw_event_rx_flags, BUTTON_LONG_PRESS))
		{
			App_button_long_press_handler();
		}

		if(HW_EVENT_OCCURRED(hw_event_rx_flags, CONSTANT_PERIOD))
		{
			App_constant_period_handler();
		}

		if(HW_EVENT_OCCURRED(hw_event_rx_flags, PROXIMITY_SCAN_COMPLETE))
		{
			App_proximity_handler();
		}

		if(HW_EVENT_OCCURRED(hw_event_rx_flags, ROTARY_COUNT_UPDATED))
		{
			App_rotary_processing();
		}

		Rltos_task_sleep(0U); /* Yield thread*/
	}
}
/* End of thread*/
