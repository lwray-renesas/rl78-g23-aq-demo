/*
 * gfx.c
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#include "gfx.h"
#include "st7735s_port.h"
#include "st7735s.h"
#include "r_smc_entry.h"
#include "draw.h"
#include "text.h"
#include "string.h"
#include "images.h"

/********** TEXT ********************/
#define BACKGROUND_TEXT_COLOUR	COLOUR_WHITE
#define FOREGROUND_TEXT_COLOUR	COLOUR_GREY
#define PROBLEM_TEXT_COLOUR	COLOUR_RED

/*********** TITLE ********************/
#define TITLE_IMAGE_OFFSET_X  (22U)
#define TITLE_IMAGE_OFFSET_Y  (3U)
#define TITLE_IMAGE_WIDTH  (116U)
#define TITLE_IMAGE_HEIGHT  (20U)

/*********** BACKGROUND GENERIC *************/
#define BACKGROUND_X_START	(10U)
#define BACKGROUND_Y_START	(23U)
#define BACKGROUND_WIDTH	(149U)
#define BACKGROUND_HEIGHT	(57U)

/*********** TEMPERATURE ********************/
#define TEMPERATURE_IMAGE_OFFSET_X  (12U)
#define TEMPERATURE_IMAGE_OFFSET_Y  (30U)
#define TEMPERATURE_IMAGE_WIDTH  (40U)
#define TEMPERATURE_IMAGE_HEIGHT  (40U)

#define TEMPERATURE_TEXT_OFFSET_X (42U)
#define TEMPERATURE_TEXT_OFFSET_Y (28U)

/*********** HUMIDITY ********************/
#define HUMIDITY_IMAGE_OFFSET_X  (77U)
#define HUMIDITY_IMAGE_OFFSET_Y  (30U)
#define HUMIDITY_IMAGE_WIDTH  (40U)
#define HUMIDITY_IMAGE_HEIGHT  (40U)

#define HUMIDITY_TEXT_OFFSET_X (117U)
#define HUMIDITY_TEXT_OFFSET_Y (28U)

/*********** ECO2 ********************/
#define ECO2_IMAGE_OFFSET_X  (15U)
#define ECO2_IMAGE_OFFSET_Y  (23U)
#define ECO2_IMAGE_WIDTH  (28U)
#define ECO2_IMAGE_HEIGHT  (28U)

#define ECO2_TEXT_OFFSET_X  (15U)
#define ECO2_TEXT_OFFSET_Y  (52U)

/*********** IAQ ********************/
#define IAQ_IMAGE_OFFSET_X  (65U)
#define IAQ_IMAGE_OFFSET_Y  (20U)
#define IAQ_IMAGE_WIDTH  (28U)
#define IAQ_IMAGE_HEIGHT  (28U)

#define IAQ_TEXT_OFFSET_X  (62U)
#define IAQ_TEXT_OFFSET_Y  (47U)

/*********** TVOC ********************/
#define TVOC_IMAGE_OFFSET_X  (115U)
#define TVOC_IMAGE_OFFSET_Y  (23U)
#define TVOC_IMAGE_WIDTH  (28U)
#define TVOC_IMAGE_HEIGHT  (28U)

#define TVOC_TEXT_OFFSET_X  (110U)
#define TVOC_TEXT_OFFSET_Y  (52U)

/*********** LOW BATTERY ********************/
#define LOW_BATT_IMAGE_OFFSET_X  (60U)
#define LOW_BATT_IMAGE_OFFSET_Y  (23U)
#define LOW_BATT_IMAGE_WIDTH  (50U)
#define LOW_BATT_IMAGE_HEIGHT  (50U)

/*********** ALARM ********************/
#define ALARM_IMAGE_OFFSET_X  (59U)
#define ALARM_IMAGE_OFFSET_Y  (23U)
#define ALARM_IMAGE_WIDTH  (48U)
#define ALARM_IMAGE_HEIGHT  (48U)

/** @brief abs function for gfx stuff*/
#define GFX_ABS(a, b) ((a > b) ? a-b : b-a)

/** Display area data*/
static ST7735S_display_area_info_t disp_info;
/** flag indicating calibration text is being displayed*/
static bool calibration_text = false;

/** @brief Writes the temperature and humidity readings to the display.
 * @param[in] sense_data - sensor data object
 * @param[in] sense_data - sensor data object for comparison - highlghts text as red if any paramater in sense data exceeds & this object i non-NULL.
 * @param[in] data_to_highlight - selects which data to highlight*/
static void Gfx_write_air_quality_text(const volatile sensor_data_t * sense_data, const volatile sensor_data_t * c_sense_data, const sensor_data_highlight_t data_to_highlight);
/** @brief Utility function to erase text.
 * @param[in] x - x position of text to erase.
 * @param[in] y - y position of text to erase.
 * @param[in] length - length of text (in pixels) to erase - can be found using utility function Text_str_len_px */
static void Erase_text(uint16_t x, uint16_t y, uint16_t length);
/** @brief Utility functino used to clear the display background area (everything but the title/renesas logo)*/
static void Erase_background(void);
/** @brief Utility functino used to clear the entire display*/
static void Erase_display(void);
/** @brief Utility function which returns a colour depending on the air quality index value which corresponds to the severity.
 * @param[in] iaqx100 - air quality index reading.*/
static const uint8_t * Colour_lookup_iaq(const int_dec_t iaq);

void Gfx_init(void)
{
	St7735s_init(COLOUR_WHITE);

	St7735s_get_display_area_info(&disp_info);

	Text_init(disp_info.xmax, disp_info.ymax);
	Draw_init(disp_info.xmax, disp_info.ymax);

	Text_set_font(&default_font);
}
/* END OF FUNCTION*/

void Gfx_set_background_title(void)
{
	St7735s_send_image(TITLE_IMAGE_OFFSET_X, TITLE_IMAGE_OFFSET_Y, TITLE_IMAGE_WIDTH, TITLE_IMAGE_HEIGHT, (__far const uint8_t *)renesas_title);
}
/* END OF FUNCTION*/

void Gfx_set_background_temp_humid(void)
{
	Erase_background();
	St7735s_send_image(TEMPERATURE_IMAGE_OFFSET_X, TEMPERATURE_IMAGE_OFFSET_Y, TEMPERATURE_IMAGE_WIDTH, TEMPERATURE_IMAGE_HEIGHT, (__far const uint8_t *)thermometer);
	St7735s_send_image(HUMIDITY_IMAGE_OFFSET_X, HUMIDITY_IMAGE_OFFSET_Y, HUMIDITY_IMAGE_WIDTH, HUMIDITY_IMAGE_HEIGHT, (__far const uint8_t *)droplet);
}
/* END OF FUNCTION*/

void Gfx_write_temp_humid(const volatile sensor_data_t * sense_data)
{
	static uint16_t str_nav = 0U; /* Variable used to navigate strings*/
	static uint16_t temp_str_len_prev = 0U; /* Variable used to store the previously written temperature string length*/
	static uint16_t hum_str_len_prev = 0U; /* Variable used to store the previously written humidity string length*/
	static uint16_t str_len_tmp = 0U; /* variable used to read in the current string length of a string of interest*/
	static char temp_str[16]; /* variable used to store the temperature string*/
	static char hum_str[16]; /* variable used to store the humidity string*/
	static const char temp_unit_str[] = "\x7f""C";
	static const char humidity_unit_str[] = "%";

	str_nav = Text_int_to_str(sense_data->temperature_int, temp_str);
	(void)strcpy(&temp_str[str_nav], temp_unit_str);
	str_nav = Text_int_to_str(sense_data->humidity_int, hum_str);
	(void)strcpy(&hum_str[str_nav], humidity_unit_str);

	/* Write the temperature*/
	Text_set_font(&default_font);
	str_len_tmp = Text_put_line(TEMPERATURE_TEXT_OFFSET_X, TEMPERATURE_TEXT_OFFSET_Y, temp_str, FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);

	/* Erase any extra pixels resulting in  shorter string*/
	if(temp_str_len_prev > str_len_tmp)
	{
		Erase_text(TEMPERATURE_TEXT_OFFSET_X + str_len_tmp, TEMPERATURE_TEXT_OFFSET_Y, temp_str_len_prev - str_len_tmp);
	}

	temp_str_len_prev = str_len_tmp;

	/* Write the humidity*/
	str_len_tmp = Text_put_line(HUMIDITY_TEXT_OFFSET_X, HUMIDITY_TEXT_OFFSET_Y, hum_str, FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);

	/* Erase any extra pixels resulting in  shorter string*/
	if(hum_str_len_prev > str_len_tmp)
	{
		Erase_text(HUMIDITY_TEXT_OFFSET_X + str_len_tmp, HUMIDITY_TEXT_OFFSET_Y, hum_str_len_prev - str_len_tmp);
	}

	hum_str_len_prev = str_len_tmp;
}
/* END OF FUNCTION*/

void Gfx_set_background_air_quality(void)
{
	Erase_background();
	St7735s_send_image(IAQ_IMAGE_OFFSET_X, IAQ_IMAGE_OFFSET_Y, IAQ_IMAGE_WIDTH, IAQ_IMAGE_HEIGHT, (__far const uint8_t *)air_quality);
	St7735s_send_image(ECO2_IMAGE_OFFSET_X, ECO2_IMAGE_OFFSET_Y, ECO2_IMAGE_WIDTH, ECO2_IMAGE_HEIGHT, (__far const uint8_t *)eco2_img);
	St7735s_send_image(TVOC_IMAGE_OFFSET_X, TVOC_IMAGE_OFFSET_Y, TVOC_IMAGE_WIDTH, TVOC_IMAGE_HEIGHT, (__far const uint8_t *)tvoc_img);
}
/* END OF FUNCTION*/

void Gfx_write_air_quality(const volatile sensor_data_t * sense_data, const volatile sensor_data_t * c_sense_data)
{
	if(sense_data->zmod_calibrated)
	{
		if(calibration_text)
		{
			Erase_text(ECO2_TEXT_OFFSET_X, ECO2_TEXT_OFFSET_Y, Text_str_len_px("CALIBRATING..."));
			calibration_text = false;
		}

		Gfx_write_air_quality_text(sense_data, c_sense_data, NONE_HIGHLIGHT);
	}
	else
	{
		Text_put_line(ECO2_TEXT_OFFSET_X, ECO2_TEXT_OFFSET_Y, "CALIBRATING...", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
		calibration_text = true;
	}
}
/* END OF FUNCTION*/

void Gfx_write_alarm(const volatile sensor_data_t * sense_data, const sensor_data_highlight_t data_to_highlight)
{
	if(calibration_text)
	{
		Erase_text(ECO2_TEXT_OFFSET_X, ECO2_TEXT_OFFSET_Y, Text_str_len_px("CALIBRATING..."));
		calibration_text = false;
	}

	Gfx_write_air_quality_text(sense_data, NULL, data_to_highlight);
}
/* END OF FUNCTION*/

void Gfx_set_background_low_battery(void)
{
	Erase_background();
	St7735s_send_image(LOW_BATT_IMAGE_OFFSET_X, LOW_BATT_IMAGE_OFFSET_Y, LOW_BATT_IMAGE_WIDTH, LOW_BATT_IMAGE_HEIGHT, (__far const uint8_t *)low_battery_img);
}
/* END OF FUNCTION*/

void Gfx_display_off(void)
{
	St7735s_sleep_display();
	St7735s_display_off();
}
/* END OF FUNCTION*/

void Gfx_display_on(void)
{
	St7735s_wake_display();
	St7735s_display_on();
}
/* END OF FUNCTION*/

void Gfx_reduced_backlight(void)
{
	Hw_backlight_set(BACKLIGHT_DIM);
}
/* END OF FUNCTION*/

void Gfx_normal_backlight(void)
{
	Hw_backlight_set(BACKLIGHT_ON);
}
/* END OF FUNCTION*/

void Gfx_backlight_off(void)
{
	Hw_backlight_set(BACKLIGHT_OFF);
}
/* END OF FUNCTION*/

void Gfx_set_backgound_enable_alarm(void)
{
	uint16_t l_txt = 0U;
	Erase_background();
	(void)Text_put_line(55U, 25U, "ALARM", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
	l_txt = Text_put_line(BACKGROUND_X_START + 25U, 50U, " OFF ", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
	l_txt += Text_put_line(BACKGROUND_X_START + l_txt + 25U, 50U, "    ", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
	(void)Text_put_line(BACKGROUND_X_START + l_txt + 25U, 50U, " ON ", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
}
/* END OF FUNCTION*/

void Gfx_set_backgound_enable_alarm_off(void)
{
	uint16_t l_txt = 0U;
	l_txt = Text_put_line(BACKGROUND_X_START + 25U, 50U, " OFF ", BACKGROUND_TEXT_COLOUR, FOREGROUND_TEXT_COLOUR);
	l_txt += Text_put_line(BACKGROUND_X_START + l_txt + 25U, 50U, "    ", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
	(void)Text_put_line(BACKGROUND_X_START + l_txt + 25U, 50U, " ON ", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
}
/* END OF FUNCTION*/

void Gfx_set_backgound_enable_alarm_on(void)
{
	uint16_t l_txt = 0U;
	l_txt = Text_put_line(BACKGROUND_X_START + 25U, 50U, " OFF ", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
	l_txt += Text_put_line(BACKGROUND_X_START + l_txt + 25U, 50U, "    ", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
	(void)Text_put_line(BACKGROUND_X_START + l_txt + 25U, 50U, " ON ", BACKGROUND_TEXT_COLOUR, FOREGROUND_TEXT_COLOUR);
}
/* END OF FUNCTION*/

void Gfx_set_backgound_breach_alarm(void)
{
	Erase_background();
	St7735s_send_image(ALARM_IMAGE_OFFSET_X, ALARM_IMAGE_OFFSET_Y, ALARM_IMAGE_WIDTH, ALARM_IMAGE_HEIGHT, (__far const uint8_t *)alarm_img);
}
/* END OF FUNCTION*/

void Gfx_display_offset_tuning(void)
{
	(void)Text_put_str(TITLE_IMAGE_OFFSET_X, TITLE_IMAGE_OFFSET_Y, "CTSU Tuning", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
	(void)Text_put_str(BACKGROUND_X_START, BACKGROUND_Y_START, "1. Put Me Down\n2. Click Button", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
}
/* END OF FUNCTION*/

void Gfx_display_countdown(void)
{
	static uint8_t countdown_state = 5U;

	switch(countdown_state)
	{
	case 5U:
	{
		Erase_display();
		(void)Text_put_str(15U, BACKGROUND_Y_START, "Countdown: 5", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
		--countdown_state;
	}
	break;
	case 4U:
	{
		Erase_text(15U, BACKGROUND_Y_START, Text_str_len_px("Countdown: 5"));
		(void)Text_put_str(15U, BACKGROUND_Y_START, "Countdown: 4", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
		--countdown_state;
	}
	break;
	case 3U:
	{
		Erase_text(15U, BACKGROUND_Y_START, Text_str_len_px("Countdown: 4"));
		(void)Text_put_str(15U, BACKGROUND_Y_START, "Countdown: 3", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
		--countdown_state;
	}
	break;
	case 2U:
	{
		Erase_text(15U, BACKGROUND_Y_START, Text_str_len_px("Countdown: 3"));
		(void)Text_put_str(15U, BACKGROUND_Y_START, "Countdown: 2", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
		--countdown_state;
	}
	break;
	case 1U:
	{
		Erase_text(15U, BACKGROUND_Y_START, Text_str_len_px("Countdown: 2"));
		(void)Text_put_str(15U, BACKGROUND_Y_START, "Countdown: 1", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
		countdown_state = 5U;
	}
	break;
	default:
		/* Shouldn't get here*/
	break;
	}
}
/* END OF FUNCTION*/

void Gfx_display_tuning_elipse(void)
{
	Erase_background();
	(void)Text_put_str(40U, BACKGROUND_Y_START, "Tuning...", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
}
/* END OF FUNCTION*/

void Gfx_display_success(void)
{
	Erase_background();
	(void)Text_put_str(40U, BACKGROUND_Y_START, "Success!!!", FOREGROUND_TEXT_COLOUR, BACKGROUND_TEXT_COLOUR);
}
/* END OF FUNCTION*/

void Gfx_display_refresh(void)
{
	St7735s_refresh();
}
/* END OF FUNCTION*/

static void Gfx_write_air_quality_text(const volatile sensor_data_t * sense_data, const volatile sensor_data_t * c_sense_data, const sensor_data_highlight_t data_to_highlight)
{
	static uint16_t str_nav = 0U; /* Variable used to navigate the strings*/
	static uint16_t iaq_str_len_prev = 0U; /* Variable used to store the previously written iaq string length*/
	static uint16_t tvoc_str_len_prev = 0U; /* Variable used to store the previously written tvoc string length*/
	static uint16_t eco2_str_len_prev = 0U; /* Variable used to store the previously written eco2 string length*/
	static uint16_t str_len_tmp = 0U; /* variable used to read in the current string length of a string of interest*/
	static char iaq_str[16]; /* variable used to store the iaq string*/
	static char tvoc_str[16]; /* variable used to store the tvoc string*/
	static char eco2_str[16]; /* variable used to store the eco2 string*/
	static const char tvoc_unit_str[] = "mg/m3";
	static const char eco2_unit_str[] = "ppm";
	static solid_rectangle_t status_bar = {
			.height = 10U,
			.width = 49U,
			.x0 = 53U,
			.y0 = 67U,
	};

	const uint8_t * IAQ_FOREGROUND_COLOUR_PTR = NULL;
	const uint8_t * IAQ_BACKGROUND_COLOUR_PTR = NULL;
	const uint8_t * TVOC_FOREGROUND_COLOUR_PTR = NULL;
	const uint8_t * TVOC_BACKGROUND_COLOUR_PTR = NULL;
	const uint8_t * ECO2_FOREGROUND_COLOUR_PTR = NULL;
	const uint8_t * ECO2_BACKGROUND_COLOUR_PTR = NULL;

	/* Determine how to highlight text if applicable*/
	if(NONE_HIGHLIGHT != data_to_highlight)
	{
		IAQ_FOREGROUND_COLOUR_PTR = (data_to_highlight == IAQ_HIGHLIGHT) ? BACKGROUND_TEXT_COLOUR : FOREGROUND_TEXT_COLOUR;
		IAQ_BACKGROUND_COLOUR_PTR = (data_to_highlight == IAQ_HIGHLIGHT) ? FOREGROUND_TEXT_COLOUR : BACKGROUND_TEXT_COLOUR;
		TVOC_FOREGROUND_COLOUR_PTR = (data_to_highlight == TVOC_HIGHLIGHT) ? BACKGROUND_TEXT_COLOUR : FOREGROUND_TEXT_COLOUR;
		TVOC_BACKGROUND_COLOUR_PTR = (data_to_highlight == TVOC_HIGHLIGHT) ? FOREGROUND_TEXT_COLOUR : BACKGROUND_TEXT_COLOUR;
		ECO2_FOREGROUND_COLOUR_PTR = (data_to_highlight == ECO2_HIGHLIGHT) ? BACKGROUND_TEXT_COLOUR : FOREGROUND_TEXT_COLOUR;
		ECO2_BACKGROUND_COLOUR_PTR = (data_to_highlight == ECO2_HIGHLIGHT) ? FOREGROUND_TEXT_COLOUR : BACKGROUND_TEXT_COLOUR;
	}
	else
	{
		IAQ_FOREGROUND_COLOUR_PTR = ((NULL != c_sense_data) && (Int_dec_larger_than((int_dec_t *)&sense_data->iaq, (int_dec_t *)&c_sense_data->iaq))) ? PROBLEM_TEXT_COLOUR : FOREGROUND_TEXT_COLOUR;
		IAQ_BACKGROUND_COLOUR_PTR = BACKGROUND_TEXT_COLOUR;
		TVOC_FOREGROUND_COLOUR_PTR = ((NULL != c_sense_data) && (Int_dec_larger_than((int_dec_t *)&sense_data->tvoc, (int_dec_t *)&c_sense_data->tvoc))) ? PROBLEM_TEXT_COLOUR : FOREGROUND_TEXT_COLOUR;
		TVOC_BACKGROUND_COLOUR_PTR = BACKGROUND_TEXT_COLOUR;
		ECO2_FOREGROUND_COLOUR_PTR = ((NULL != c_sense_data) && (Int_dec_larger_than((int_dec_t *)&sense_data->eco2, (int_dec_t *)&c_sense_data->eco2))) ? PROBLEM_TEXT_COLOUR : FOREGROUND_TEXT_COLOUR;
		ECO2_BACKGROUND_COLOUR_PTR = BACKGROUND_TEXT_COLOUR;
	}

	status_bar.colour = Colour_lookup_iaq(sense_data->iaq);

	Draw_solid_rectangle(&status_bar);

	str_nav = Text_int_to_str(sense_data->iaq.integer_part, iaq_str);
	iaq_str[str_nav] = '.';
	++str_nav;
	str_nav = Text_int_to_str_sf(sense_data->iaq.decimal_part, 2U, &iaq_str[str_nav]);
	str_nav = Text_int_to_str(sense_data->tvoc.integer_part, tvoc_str);
	tvoc_str[str_nav] = '.';
	++str_nav;
	str_nav = Text_int_to_str_sf(sense_data->tvoc.decimal_part, 2U, &tvoc_str[str_nav]);
	str_nav = Text_int_to_str(sense_data->eco2.integer_part, eco2_str);

	/* Write the iaq*/
	str_len_tmp = Text_put_line(IAQ_TEXT_OFFSET_X, IAQ_TEXT_OFFSET_Y, iaq_str, IAQ_FOREGROUND_COLOUR_PTR, IAQ_BACKGROUND_COLOUR_PTR);

	/* Erase any extra pixels resulting in  shorter string*/
	if(iaq_str_len_prev > str_len_tmp)
	{
		Erase_text(IAQ_TEXT_OFFSET_X + str_len_tmp, IAQ_TEXT_OFFSET_Y, iaq_str_len_prev - str_len_tmp);
	}

	iaq_str_len_prev = str_len_tmp;

	/* Write the tvoc*/
	str_len_tmp = Text_put_line(TVOC_TEXT_OFFSET_X, TVOC_TEXT_OFFSET_Y, tvoc_str, TVOC_FOREGROUND_COLOUR_PTR, TVOC_BACKGROUND_COLOUR_PTR);
	Text_set_font(&small_font);
	Text_put_line(TVOC_TEXT_OFFSET_X, TVOC_TEXT_OFFSET_Y+16U, tvoc_unit_str, TVOC_FOREGROUND_COLOUR_PTR, TVOC_BACKGROUND_COLOUR_PTR);

	/* Erase any extra pixels resulting in  shorter string*/
	if(tvoc_str_len_prev > str_len_tmp)
	{
		Erase_text(TVOC_TEXT_OFFSET_X + str_len_tmp, TVOC_TEXT_OFFSET_Y, tvoc_str_len_prev - str_len_tmp);
	}

	tvoc_str_len_prev = str_len_tmp;

	/* Write the eco2*/
	Text_set_font(&default_font);
	str_len_tmp = Text_put_line(ECO2_TEXT_OFFSET_X, ECO2_TEXT_OFFSET_Y, eco2_str, ECO2_FOREGROUND_COLOUR_PTR, ECO2_BACKGROUND_COLOUR_PTR);
	Text_set_font(&small_font);
	Text_put_line(ECO2_TEXT_OFFSET_X, ECO2_TEXT_OFFSET_Y+16U, eco2_unit_str, ECO2_FOREGROUND_COLOUR_PTR, ECO2_BACKGROUND_COLOUR_PTR);

	/* Erase any extra pixels resulting in  shorter string*/
	if(eco2_str_len_prev > str_len_tmp)
	{
		Erase_text(ECO2_TEXT_OFFSET_X + str_len_tmp, ECO2_TEXT_OFFSET_Y, eco2_str_len_prev - str_len_tmp);
	}

	eco2_str_len_prev = str_len_tmp;

	Text_set_font(&default_font);
}
/* END OF FUNCTION*/

static void Erase_text(uint16_t x, uint16_t y, uint16_t length)
{
	static solid_rectangle_t eraser = {
			.height = 16U,
			.colour = BACKGROUND_TEXT_COLOUR
	};

	eraser.width = length;
	eraser.y0 = y;
	eraser.x0 = x;
	Draw_solid_rectangle(&eraser);
}
/* END OF FUNCTION*/

static void Erase_background(void)
{
	static const solid_rectangle_t eraser = {
			.height = BACKGROUND_HEIGHT,
			.width = BACKGROUND_WIDTH,
			.x0 = BACKGROUND_X_START,
			.y0 = BACKGROUND_Y_START,
			.colour = BACKGROUND_TEXT_COLOUR,
	};

	Draw_solid_rectangle(&eraser);
}
/* END OF FUNCTION*/

static void Erase_display(void)
{
	St7735s_set_colour(BACKGROUND_TEXT_COLOUR);
	St7735s_fill_display();
	St7735s_set_colour(FOREGROUND_TEXT_COLOUR);
}
/* END OF FUNCTION*/

static const uint8_t * Colour_lookup_iaq(const int_dec_t iaq)
{
	const uint8_t * colour_ptr = COLOUR_BAD;

	if(iaq.integer_part < 2U)
	{
		colour_ptr = COLOUR_VERY_GOOD;
	}
	else if(iaq.integer_part < 3U)
	{
		colour_ptr = COLOUR_GOOD;
	}
	else if(iaq.integer_part < 4U)
	{
		colour_ptr = COLOUR_MEDIUM;
	}
	else if(iaq.integer_part < 5U)
	{
		colour_ptr = COLOUR_POOR;
	}
	else
	{
		/* Do Nothing*/
	}

	return colour_ptr;
}
/* END OF FUNCTION*/
