/*
 * event_thread.c
 *
 *  Created on: 2 Nov 2022
 *      Author: a5126135
 */

#include "r_smc_entry.h"
#include "app.h"

static rltos_uint hw_rx_flags = 0U;

/** @brief The event handler and dispatcher for the application.
 * All events from hardware and state changes are managed.
 * Events dispatched to various system components from this thread.
 * Sensors and battery voltage read.
 */
void Event_thread_main(void)
{
	/* Initialise the sensor portion of the application*/
	App_init_sensors();

	while(1)
	{
		/* Wait indefinitely for a Hardware event*/
		Rltos_events_get(&hardware_events, ALL_HARDWARE_EVENTS, &hw_rx_flags, RLTOS_TRUE, RLTOS_FALSE, RLTOS_UINT_MAX);

		if(EVENT_OCCURED(hw_rx_flags, BUTTON_CLICK))
		{
			App_button_click_handler();
		}

		if(EVENT_OCCURED(hw_rx_flags, BUTTON_LONG_PRESS))
		{
			App_button_long_press_handler();
		}

		if(EVENT_OCCURED(hw_rx_flags, CTSU_PROXIMITY))
		{
			App_ctsu_proximity_handler();
		}

		if(EVENT_OCCURED(hw_rx_flags, RTC_BATTERY))
		{
			App_rtc_battery_handler();
		}

		if(EVENT_OCCURED(hw_rx_flags, RTC_SENSOR))
		{
			App_rtc_sensor_handler();
		}
	}
}
/* End of thread*/
