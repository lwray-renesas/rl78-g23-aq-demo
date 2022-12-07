/*
 * gui_thread.c
 *
 *  Created on: 2 Nov 2022
 *      Author: a5126135
 */

#include "r_smc_entry.h"
#include "app.h"

static rltos_uint gui_rx_flags = 0U;
static sensor_data_t gui_sensor_data;
static sensor_data_t gui_alarm_sensor_data;

/** @brief The GUI handler for the application.
 * Responds to events from the event dispatcher thread & controls the GUI accordingly.
 */
void Gui_thread_main(void)
{
	/* Initialise the gfx portion of the application*/
	Gfx_init();

	while(1)
	{
		/* Wait indefinitely for a GUI event*/
		Rltos_events_get(&gui_events, ALL_GUI_EVENTS, &gui_rx_flags, RLTOS_TRUE, RLTOS_FALSE, RLTOS_UINT_MAX);

		if(EVENT_OCCURED(gui_rx_flags, BACKGROUND_TEMP_HUMID))
		{
			Gfx_set_background_temp_humid();
			App_get_sensor_data(&gui_sensor_data);
			Gfx_write_temp_humid(&gui_sensor_data);
		}

		if(EVENT_OCCURED(gui_rx_flags, UPDATE_TEMP_HUMID))
		{
			App_get_sensor_data(&gui_sensor_data);
			Gfx_write_temp_humid(&gui_sensor_data);
		}

		if(EVENT_OCCURED(gui_rx_flags, BACKGROUND_AIR_QUALITY))
		{
			Gfx_set_background_air_quality();
			App_get_sensor_data(&gui_sensor_data);
			Gfx_write_air_quality(&gui_sensor_data);
		}

		if(EVENT_OCCURED(gui_rx_flags, UPDATE_AIR_QUALITY))
		{
			App_get_sensor_data(&gui_sensor_data);
			Gfx_write_air_quality(&gui_sensor_data);
		}

		if(EVENT_OCCURED(gui_rx_flags, BACKGROUND_UPDATE_ALARMS))
		{
			Gfx_set_background_alarm();
			App_get_alarm_sensor_data(&gui_alarm_sensor_data);
			Gfx_write_alarm(&gui_alarm_sensor_data);
		}

		if(EVENT_OCCURED(gui_rx_flags, UPDATE_ALARMS))
		{
			App_get_alarm_sensor_data(&gui_alarm_sensor_data);
			Gfx_write_alarm(&gui_alarm_sensor_data);
		}

		if(EVENT_OCCURED(gui_rx_flags, WAKEUP))
		{
			Gfx_display_on();
		}

		if(EVENT_OCCURED(gui_rx_flags, SLEEP))
		{
			Gfx_display_off();
		}

		if(EVENT_OCCURED(gui_rx_flags, BACKGROUND_LOW_BATTERY))
		{
			Gfx_reduced_backlight();
			Gfx_set_background_low_battery();
		}

		if(EVENT_OCCURED(gui_rx_flags, WRITE_BACKGROUND))
		{
			Gfx_set_background_title();
		}

		if(EVENT_OCCURED(gui_rx_flags, REDUCED_BACKLIGHT))
		{
			Gfx_reduced_backlight();
		}

		if(EVENT_OCCURED(gui_rx_flags, NORMAL_BACKLIGHT))
		{
			Gfx_normal_backlight();
		}

		Rltos_task_sleep(3U);
	}
}
/* End of thread*/
