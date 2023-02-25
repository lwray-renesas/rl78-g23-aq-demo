/*
 * hw.c
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#include "hw.h"
#include "elcl.h"
#include "r_smc_entry.h"
#include "rltos_task.h"
#include "qe_touch_config.h"

/** @brief macro used to determine the number of consecutive battery readings before considering a battery low*/
#define LOW_BATTERY_READ_COUNT	(5U)

/** @brief Median Filter depth for CTSU*/
#define FILTERDEPTH     (3U)

/** variable to store event flags*/
volatile hardware_event_t hw_event_flags = NO_EVENT;
/** counter defined here but manipulated by timer 00 & 05 modules*/
volatile int16_t rotary_count = 0;
/** local variable used to track the rotary count value*/
static volatile int16_t l_rotary_count = 0;
/** variable used to satisfy memory requirements of callback set API in touch middleware*/
touch_callback_args_t touch_callback_memory;

/** sorted odd size median filter variables */
static uint16_t median_filter_array[FILTERDEPTH] = {0U,};
static uint16_t filter_data;

#pragma address tone=0xfe000
uint8_t tone[8];

/** @brief Performs ELCL Setup*/
static void Setup_elcl(void);

/** @brief Retrieves ctsu data & inserts data point into median filter arrays
 * @param[in] lpf - true to enable low pass filter*/
static void Hw_ctsu_insert_data_point(bool lpf);

/** @brief swaps data at xp with data at yp
 * @param xp - data X
 * @param yp - data Y
 */
static void Swap(uint16_t *xp, uint16_t *yp);

/** @brief Performs bubble sort on data of size n
 * @param array - aray of data to sort.
 * @param n - size of array
 */
static void Bubble_sort(uint16_t * array, uint16_t n);

/** @brief Performs sorting of median filter data */
static void Sorted_median_filter(void);

/** @brief callback used for ctsu scan complete
 * @param p_args - pointer to callback argument struct.
 */
static void Touch_callback(touch_callback_args_t * p_args);

/** @brief function to set ctsu pins*/
extern void R_CTSU_PinSetInit(void);

void Hw_init(void)
{
	touch_err_t err;

	EI();

	/* Generate Tone Sequence*/
	tone[0] = 0x8DU;
	tone[1] = 0x8CU;
	tone[2] = 0x8FU;
	tone[3] = 0x8EU;
	tone[4] = 0x8EU;
	tone[5] = 0x8FU;
	tone[6] = 0x8CU;
	tone[7] = 0x8DU;

	/* Connection of unused pins for P123 and P124 */
	/* The settings for the CMC register are described in the "mcu_clocks.c" file */
	CSC |= 0x40;

	/* Initialize pins (function created by Smart Configurator) */
	R_CTSU_PinSetInit();

	/* Open Touch middleware */
	err = RM_TOUCH_Open(g_qe_touch_instance_config01.p_ctrl, g_qe_touch_instance_config01.p_cfg);
	if (TOUCH_SUCCESS != err)
	{
		/* TODO: Handle/signal/log error*/
		while (true) {}
	}

	err = RM_TOUCH_CallbackSet(g_qe_touch_instance_config01.p_ctrl, Touch_callback, NULL, &touch_callback_memory);
	if (TOUCH_SUCCESS != err)
	{
		/* TODO: Handle/signal/log error*/
		while (true) {}
	}

	MK2H |= 0x40;    /* Disable interrupt servicing of "write request interrupt for setting registers for each channel" */
	MK3L |= 0x01;    /* Disable interrupt servicing of "measurement data transfer request interrupt" */

	R_Config_TAU0_0_Start();
	R_Config_TAU0_1_Start();
	R_Config_TAU0_3_Start();
	R_Config_CSI00_Start_app();
	R_DTCD0_Start();
	Hw_alarm_led_off();

	/* Sets ELCL connections*/
	Setup_elcl();

	/* Enable the rotary*/
	Hw_start_rotary();
}
/* END OF FUNCTION*/

void Hw_ctsu_start(void)
{
	static uint64_t l_button_status = 0ULL;
	fsp_err_t err = FSP_SUCCESS;
	uint16_t seed_array_count = FILTERDEPTH;

	/* for ExternalTrigger */
	err = RM_TOUCH_ScanStart(g_qe_touch_instance_config01.p_ctrl);
	if (FSP_SUCCESS != err)
	{
		while (true) {}
	}

	/* Clear interval timer interrupt flags & start the timer (ctsu trigger)*/
	ITLS0 = 0U;
	ITLIF = 0U;
	R_Config_ITL000_ITL001_Start();

	/* Measurement loop for initial offset tuning.*/
	while (true)
	{
		while (!HW_EVENT_OCCURRED(hw_event_flags, PROXIMITY_SCAN_COMPLETE))
		{
			NOP();
		}

		hw_event_flags = NO_EVENT; /* Reset the event flags*/

		err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &l_button_status, NULL, NULL);
		if ((FSP_SUCCESS == err) && (l_button_status == 0ULL))
		{
			break;
		}
	}

	/* Scan until the array is seeded with real world data*/
	do
	{
		while (!HW_EVENT_OCCURRED(hw_event_flags, PROXIMITY_SCAN_COMPLETE))
		{
			NOP();
		}

		hw_event_flags = NO_EVENT; /* Reset the event flags*/

		Hw_ctsu_insert_data_point(false);
		--seed_array_count;
	}
	while(seed_array_count > 0U);
}
/* END OF FUNCTION*/

void Hw_enable_sensor_timer(void)
{
	R_Config_RTC_Start();
}
/* END OF FUNCTION*/

int16_t Hw_get_rotary_count(void)
{
	RLTOS_PREPARE_CRITICAL_SECTION();

	RLTOS_ENTER_CRITICAL_SECTION();

	l_rotary_count = rotary_count;
	rotary_count = 0; /* reset rotary count to ensure only relative changes are registered*/

	RLTOS_EXIT_CRITICAL_SECTION();

	return l_rotary_count;
}
/* END OF FUNCTION*/

void Hw_start_rotary(void)
{
	Elcl_set_output_state(&elcl_ctl, ELCL_OUTPUT_3, ELCL_OUTPUT_ENABLED);
	Elcl_set_output_state(&elcl_ctl, ELCL_OUTPUT_4, ELCL_OUTPUT_ENABLED);
}
/* END OF FUNCTION*/

void Hw_stop_rotary(void)
{
	Elcl_set_output_state(&elcl_ctl, ELCL_OUTPUT_3, ELCL_OUTPUT_DISABLED);
	Elcl_set_output_state(&elcl_ctl, ELCL_OUTPUT_4, ELCL_OUTPUT_DISABLED);
}
/* END OF FUNCTION*/

bool Hw_low_battery(void)
{
	uint8_t low_battery_count = 0U;
	uint8_t read_count = 0U;

	/* Perform X reads - only if every read is low battery, do we consider the battery to be low*/
	while(read_count < LOW_BATTERY_READ_COUNT)
	{
		++read_count;

		LVIIF = 0U;

		R_Config_LVD1_Start();

		low_battery_count = (LVIIF > 0U) ? (low_battery_count += 1U) : (0U);

		R_Config_LVD1_Stop();

		/* Reset the interrupt flags*/
		DLVD1FCLR = 1U;
		LVIIF = 0U;
	}

	return (low_battery_count == LOW_BATTERY_READ_COUNT);
}
/* END OF FUNCTION*/

void Hw_delay_ms(uint16_t ms)
{
	if(ms > 0U)
	{
		TDR04 = (ms > 1U) ? (ms << 2U)-1U : 0U;

		TMMK04 = 1U;    /* disable INTTM02 interrupt */
		TMIF04 = 0U;    /* clear INTTM02 interrupt flag */

		TS0 |= _0010_TAU_CH4_START_TRG_ON;

		while(0U == TMIF04)
		{
			NOP();
		}

		TT0 |= _0010_TAU_CH4_STOP_TRG_ON;

		TMIF04 = 0U;    /* clear INTTM02 interrupt flag */
	}
}
/* END OF FUNCTION*/

void Hw_start_oneshot(void)
{
	R_Config_TAU0_5_Start();
}
/* END OF FUNCTION*/

void Hw_trigger_alarm(void)
{
	P1_bit.no7 = 0U; /* Enable CCIO*/
	P1_bit.no6 = 0U;
	CCDE |= 0x03U; /* Turn on LED's*/
	CCS0 = 0x01U;
	R_Config_TAU0_6_Start();
}
/* END OF FUNCTION*/

void Hw_stop_alarm(void)
{
	R_Config_TAU0_6_Stop(); /* Stop tone sequence generation timer*/
	CKS1 = 0x0FU; /* Turn off buzzer*/
}
/* END OF FUNCTION*/

void Hw_alarm_led_toggle(void)
{
	CCS0 ^= 0x01U;
}
/* END OF FUNCTION*/

void Hw_alarm_led_off(void)
{
	P1_bit.no7 = 1U;
	P1_bit.no6 = 1U;
	CCS0 = 0x00U;
	CCDE &= ~0x03U; /* Turn off LED's*/
}
/* END OF FUNCTION*/

void Hw_backlight_set(backlight_level_t const backlight_level)
{
	switch(backlight_level)
	{
	case BACKLIGHT_OFF:
	{
		P6_bit.no2 = 1U;
		CCS6 = 0x00U; /* Hi-Z backlight*/
		CCDE &= ~0x40U;
	}
	break;

	case BACKLIGHT_DIM:
	{
		P6_bit.no2 = 0U;
		CCDE |= 0x40U;
		CCS6 = 0x01U; /* 2mA backlight*/
	}
	break;

	case BACKLIGHT_ON:
	{
		P6_bit.no2 = 0U;
		CCDE |= 0x40U;
		CCS6 = 0x04U; /* 15mA backlight*/
	}
	break;

	default:
		/* Do Nothing - shouldn;t get here*/
		break;

	}
}
/* END OF FUNCTION*/

bool Hw_ctsu_get_proximity_data(void)
{
	uint64_t proximity_status = 0ULL;
	fsp_err_t err = FSP_SUCCESS;

	/* Retrieve the latest data*/
	Hw_ctsu_insert_data_point(true);

	/* Run the filter*/
	Sorted_median_filter();

	err = R_CTSU_DataInsert(g_qe_ctsu_instance_config01.p_ctrl, &filter_data);

	if(err == FSP_SUCCESS)
	{
		err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &proximity_status, NULL, NULL);
	}

	return (err == FSP_SUCCESS) && (proximity_status > 0ULL);
}
/* END OF FUNCTION*/

static void Setup_elcl(void)
{
	/****************************************************************
	 *  ROTARY DECODING
	 ***************************************************************/
	Elcl_set_input(&elcl_ctl, ELCL_INPUT_4, ELCL_SRC_PIN1_611_INTC5); /* B = PIN1 = Input 4 = P00*/
	Elcl_set_input(&elcl_ctl, ELCL_INPUT_6, ELCL_SRC_P51); /* A = P51*/
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_2, ELCL_INPUT_REG_4, ELCL_INVERTED_LOGIC);
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_6, ELCL_INPUT_REG_6, ELCL_INVERTED_LOGIC);
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_0, ELCL_INPUT_REG_4, ELCL_INVERTED_LOGIC);
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_1, ELCL_INPUT_REG_6, ELCL_INVERTED_LOGIC);
	Elcl_set_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_ENABLE_FLIPFLOP0);
	Elcl_set_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_EXOR_CELL_0);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_2, ELCL_FLIP_FLOP0_INPUT);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_6, ELCL_FLIP_FLOP0_CLK);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_0, ELCL_CELL0_INPUT_0);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_1, ELCL_CELL0_INPUT_1);

	Elcl_link_input(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_0, ELCL_OUTPUT_FLIP_FLOP0_L1, ELCL_INVERTED_LOGIC);
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_1, ELCL_OUTPUT_FLIP_FLOP0_L1, ELCL_POSITIVE_LOGIC);
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_2, ELCL_OUTPUT_CELL0_L1, ELCL_INVERTED_LOGIC);
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_3, ELCL_OUTPUT_CELL0_L1, ELCL_INVERTED_LOGIC);
	Elcl_set_logic(&elcl_ctl, ELCL_BLOCK2, ELCL_AND_CELL_0);
	Elcl_set_logic(&elcl_ctl, ELCL_BLOCK2, ELCL_AND_CELL_1);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_0, ELCL_CELL0_INPUT_0);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_2, ELCL_CELL0_INPUT_1);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_1, ELCL_CELL1_INPUT_0);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK2, ELCL_LNK_3, ELCL_CELL1_INPUT_1);
	Elcl_set_output(&elcl_ctl, ELCL_OUTPUT_3, ELCL_OUTPUT_L2_CELL0, ELCL_POSITIVE_LOGIC); /* TAU00*/
	Elcl_set_output(&elcl_ctl, ELCL_OUTPUT_4, ELCL_OUTPUT_L2_CELL1, ELCL_POSITIVE_LOGIC); /* TAU01*/

	/****************************************************************
	 *  INTITL --> CTSU
	 ***************************************************************/
	Elcl_set_input(&elcl_ctl, ELCL_INPUT_7, ELCL_SRC_INTC0_611_INTC6); /* INTITL*/
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_3, ELCL_INPUT_REG_7, ELCL_POSITIVE_LOGIC);
	Elcl_set_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_PASSTHROUGH_CELL_1);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_3, ELCL_CELL1_INPUT_0);
	Elcl_set_output(&elcl_ctl, ELCL_OUTPUT_6, ELCL_OUTPUT_L1_CELL1, ELCL_POSITIVE_LOGIC); /* CTSU*/
	Elcl_set_output_state(&elcl_ctl, ELCL_OUTPUT_6, ELCL_OUTPUT_ENABLED);
}
/* END OF FUNCTION*/

static void Hw_ctsu_insert_data_point(bool lpf)
{
	static uint16_t median_filter_index = 0U;
	static const uint32_t filter_coef = 50000;
	static uint16_t y_prev = 0UL;
	static uint16_t y_cur = 0UL;
	uint16_t measurement_data = 0U;
	fsp_err_t err = FSP_SUCCESS;
	uint32_t y_prev_32 = 0UL;
	uint32_t measurement_data_32 = 0UL;
	uint32_t y_cur_32 = 0ULL;

	err = R_CTSU_DataGet(g_qe_ctsu_instance_config01.p_ctrl, &measurement_data);

	if(FSP_SUCCESS == err)
	{
		if(lpf)
		{
			measurement_data_32 = (uint32_t)measurement_data;
			y_prev_32 = (uint32_t)y_prev;
			y_cur_32 = ((y_prev_32 * (0x0000FFFFUL - filter_coef)) + (measurement_data_32 * filter_coef)) >> 16U;
			y_cur = (uint16_t)y_cur_32;
			y_prev = y_cur;
		}
		else
		{
			y_cur = measurement_data;
			y_prev = y_cur;
		}

		median_filter_array[median_filter_index] = y_cur;
		++median_filter_index;

		if(median_filter_index > FILTERDEPTH)
		{
			median_filter_index = 0U;
		}
	}
}
/* END OF FUNCTION*/

static void Swap(uint16_t *xp, uint16_t *yp)
{
	uint16_t temp = *xp;
	*xp = *yp;
	*yp = temp;
}
/* END OF FUNCTION*/

static void Bubble_sort(uint16_t * array, uint16_t n)
{
	uint16_t i = 0U;
	uint16_t j = 0U;

	for (i = 0U; i < n-1U; i++)
	{
		for (j = 0U; j < n-i-1U; j++)
		{
			if (array[j] > array[j+1U])
			{
				Swap(&array[j], &array[j+1U]);
			}
		}
	}
}
/* END OF FUNCTION*/

static void Sorted_median_filter(void)
{
	/* perform a simple bubble sort on the array*/
	Bubble_sort(median_filter_array, FILTERDEPTH);

	/* calculate median from sorted array. Pick middle value for faster processing
	 *  discover if filter depth is even or odd
	 */
#if ( (FILTERDEPTH % 2U) == 0 )
		filter_data = (uint16_t) (median_filter_array[(FILTERDEPTH-1U) >> 1U] + median_filter_array[FILTERDEPTH >> 1U]) >> 1U;
#else
		filter_data = median_filter_array[(FILTERDEPTH-1U) >> 1U];
#endif
}
/* END OF FUNCTION*/

static void Touch_callback(touch_callback_args_t * p_args)
{
	(void)p_args;

	HW_SET_EVENT(hw_event_flags, PROXIMITY_SCAN_COMPLETE);

	/* Clear interval timer interrupt flags*/
	ITLS0 = 0U;
	ITLIF = 0U;
}
/* END OF FUNCTION*/
