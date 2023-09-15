/*
 * gui_thread.c
 *
 *  Created on: 2 Nov 2022
 *      Author: a5126135
 */

#include "r_smc_entry.h"
#include "app.h"

static rltos_event_flag_t gui_rx_flags = 0U;
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

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKGROUND_TEMP_HUMID))
		{
			Gfx_set_background_temp_humid();
			Rltos_events_set(&gui_return_events, TEMP_HUMID_SET);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, UPDATE_TEMP_HUMID))
		{
			App_get_sensor_data(&gui_sensor_data);
			Gfx_write_temp_humid(&gui_sensor_data);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKGROUND_AIR_QUALITY))
		{
			Gfx_set_background_air_quality();
			Rltos_events_set(&gui_return_events, AIR_QUALITY_SET);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, UPDATE_AIR_QUALITY))
		{
			App_get_sensor_data(&gui_sensor_data);
			App_get_alarm_sensor_data(&gui_alarm_sensor_data);
			Gfx_write_air_quality(&gui_sensor_data, &gui_alarm_sensor_data);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, UPDATE_ALARM_IAQ))
		{
			App_get_alarm_sensor_data(&gui_alarm_sensor_data);
			Gfx_write_alarm(&gui_alarm_sensor_data, IAQ_HIGHLIGHT);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, UPDATE_ALARM_TVOC))
		{
			App_get_alarm_sensor_data(&gui_alarm_sensor_data);
			Gfx_write_alarm(&gui_alarm_sensor_data, TVOC_HIGHLIGHT);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, UPDATE_ALARM_ECO2))
		{
			App_get_alarm_sensor_data(&gui_alarm_sensor_data);
			Gfx_write_alarm(&gui_alarm_sensor_data, ECO2_HIGHLIGHT);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKLIGHT_OFF))
		{
			Gfx_backlight_off();
			Rltos_events_set(&gui_return_events, BACKLIGHT_TURNED_OFF);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, SLEEP))
		{
			Gfx_display_off();
			Rltos_events_set(&gui_return_events, DISPLAY_ASLEEP);
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKGROUND_LOW_BATTERY))
		{
			Gfx_set_background_low_battery();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, WRITE_BACKGROUND))
		{
			Gfx_set_background_title();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKGROUND_ENABLE_ALARM))
		{
			Gfx_set_backgound_enable_alarm();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKGROUND_ENABLE_ALARM_OFF))
		{
			Gfx_set_backgound_enable_alarm_off();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKGROUND_ENABLE_ALARM_ON))
		{
			Gfx_set_backgound_enable_alarm_on();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, BACKGROUND_BREACH_ALARM))
		{
			Gfx_set_backgound_breach_alarm();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, DISPLAY_OFFSET_TUNING_CW))
		{
			Gfx_display_offset_tuning_cw();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, DISPLAY_OFFSET_TUNING_CCW))
		{
			Gfx_display_offset_tuning_ccw();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, DISPLAY_OFFSET_TUNING_CLICK))
		{
			Gfx_display_offset_tuning_click();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, DISPLAY_COUNTDOWN))
		{
			Gfx_display_countdown();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, DISPLAY_TUNING_ELIPSE))
		{
			Gfx_display_tuning_elipse();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, DISPLAY_SUCCESS))
		{
			Gfx_display_success();
		}

		/* Refresh the display contents*/
		Gfx_display_refresh();

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, WAKEUP))
		{
			Gfx_display_on();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, REDUCED_BACKLIGHT))
		{
			Gfx_reduced_backlight();
		}

		if(EVENTS_EXACT_OCCURED(gui_rx_flags, NORMAL_BACKLIGHT))
		{
			Gfx_normal_backlight();
		}

		/* Yield thread*/
		Rltos_task_sleep(0U);
	}
}
/* End of thread*/
