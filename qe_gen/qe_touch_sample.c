/***********************************************************************
 *
 * FILE : qe_sample_main.c
 * DATE : 2022-02-14
 * DESCRIPTION : Main Program for RL78
 *
 * NOTE:THIS IS A TYPICAL EXAMPLE.
 *
 ***********************************************************************/
#include "qe_touch_config.h"
#include "filter.h"
#include "st7735s.h"
#include "text.h"
#include "r_smc_entry.h"
#include "elcl.h"

#define TOUCH_SCAN_INTERVAL_EXAMPLE (200 * 1000)    /* microseconds */

/** @brief Configuration macro for state text X location*/
#define TEXT_X_POSITION		(65U)
/** @brief Configuration macro for state text Y location*/
#define TEXT_Y_POSITION		(20U)

void R_CTSU_PinSetInit(void);
void qe_touch_main(void);
void qe_touch_delay(uint16_t delay_us);

extern volatile uint8_t      g_qe_touch_flag;
extern volatile ctsu_event_t g_qe_ctsu_event;

uint64_t button_status = 0ULL;
uint64_t prev_button_status = 0ULL;
uint16_t measurement_data[TOUCH_CFG_NUM_BUTTONS] = {0U,};
uint16_t filtered_data[TOUCH_CFG_NUM_BUTTONS] = {0U,};
/** variable used to satisfy memory requirements of callback set API in touch middleware*/
extern touch_callback_args_t touch_callback_memory;

/** Colours*/
static const uint8_t COLOUR_BLACK[] = {0x00, 0x00};
static const uint8_t COLOUR_WHITE[] = {0xFF, 0xFF};

/** lpf state object*/
static lpf_state_t lpf0_state[TOUCH_CFG_NUM_BUTTONS];

/** lpf state object*/
static lpf_state_t lpf1_state[TOUCH_CFG_NUM_BUTTONS];

/** median filter state object*/
static mf_state_t mf_state[TOUCH_CFG_NUM_BUTTONS];

/** Display area data*/
static ST7735S_display_area_info_t disp_info;

/** @brief callback used for ctsu scan complete
 * @param p_args - pointer to callback argument struct.
 */
static void Touch_callback(touch_callback_args_t * p_args);

void qe_touch_main(void)
{
	fsp_err_t err;
	uint16_t seed_array_count = MEDIAN_FILTER_DEPTH;

	BSP_ENABLE_INTERRUPT();

	Elcl_set_input(&elcl_ctl, ELCL_INPUT_7, ELCL_SRC_INTC0_611_INTC6); /* INTITL*/
	Elcl_link_input(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_3, ELCL_INPUT_REG_7, ELCL_POSITIVE_LOGIC);
	Elcl_set_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_PASSTHROUGH_CELL_1);
	Elcl_link_to_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_LNK_3, ELCL_CELL1_INPUT_0);
	Elcl_set_output(&elcl_ctl, ELCL_OUTPUT_6, ELCL_OUTPUT_L1_CELL1, ELCL_POSITIVE_LOGIC); /* CTSU*/
	Elcl_set_output_state(&elcl_ctl, ELCL_OUTPUT_6, ELCL_OUTPUT_ENABLED);

	R_Config_CSI00_Start_app();

	St7735s_init(COLOUR_WHITE);
	St7735s_get_display_area_info(&disp_info);
	Text_init(disp_info.xmax, disp_info.ymax);
	Text_set_font(&default_font);
	St7735s_wake_display();
	St7735s_display_on();
	P6_bit.no2 = 0U;
	CCDE |= 0x40U;
	CCS6 = 0x02U; /* 5mA backlight*/

	/* Write initial text*/
	Text_put_line(TEXT_X_POSITION, TEXT_Y_POSITION, "OFF", COLOUR_BLACK, COLOUR_WHITE);
	St7735s_refresh();

	/* Initialize pins (function created by Smart Configurator) */
	R_CTSU_PinSetInit();

	/* Open Touch middleware */
	err = RM_TOUCH_Open(g_qe_touch_instance_config01.p_ctrl, g_qe_touch_instance_config01.p_cfg);
	if (FSP_SUCCESS != err)
	{
		while (true) {}
	}

	err = RM_TOUCH_CallbackSet(g_qe_touch_instance_config01.p_ctrl, Touch_callback, NULL, &touch_callback_memory);
	if (TOUCH_SUCCESS != err)
	{
		/* TODO: Handle/signal/log error*/
		while (true) {}
	}

	/* Initialise LPF coefficients*/
	for(uint16_t i = 0U; i < TOUCH_CFG_NUM_BUTTONS; ++i)
	{
		lpf0_state[i].coeff = Q1616(0,50);
		lpf1_state[i].coeff = Q1616(0,90);
	}

	err = RM_TOUCH_ScanStart(g_qe_touch_instance_config01.p_ctrl);
	if (FSP_SUCCESS != err)
	{
		while (true) {}
	}

	ITLS0 = 0U;
	ITLIF = 0U;
	R_Config_ITL000_ITL001_Start();

	/* Measurement loop for initial offset tuning.*/
	while (true)
	{
		while (0 == g_qe_touch_flag) {}
		g_qe_touch_flag = 0;

		err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &button_status, NULL, NULL);
		if ((FSP_SUCCESS == err) && (button_status == 0ULL))
		{
			break;
		}
	}

	/* Prime the filters with real world data*/
	do
	{
		while (0 == g_qe_touch_flag) {}
		g_qe_touch_flag = 0;

		err = R_CTSU_DataGet(g_qe_ctsu_instance_config01.p_ctrl, measurement_data);

		if(FSP_SUCCESS == err)
		{
			for(uint16_t i = 0U; i < TOUCH_CFG_NUM_BUTTONS; ++i)
			{
				mf_state[i].median_filter_array[mf_state[i].median_filter_index] = measurement_data[i];
				++mf_state[i].median_filter_index;

				if(mf_state[i].median_filter_index >= MEDIAN_FILTER_DEPTH)
				{
					mf_state[i].median_filter_index = 0U;
				}

				lpf0_state[i].y_prev = measurement_data[i];
				lpf1_state[i].y_prev = measurement_data[i];
			}
		}

		--seed_array_count;
	}
	while(seed_array_count > 0U);

	/* Main loop */
	while (true)
	{
		while (0 == g_qe_touch_flag) {}
		g_qe_touch_flag = 0;

		err = R_CTSU_DataGet(g_qe_ctsu_instance_config01.p_ctrl, measurement_data);

		if(FSP_SUCCESS == err)
		{
			for(uint16_t i = 0U; i < TOUCH_CFG_NUM_BUTTONS; ++i)
			{
				filtered_data[i] = Low_pass_filter(&lpf0_state[i], measurement_data[i]);
//				filtered_data[i] = Median_filter(&mf_state[i], filtered_data[i]);
//				filtered_data[i] = Low_pass_filter(&lpf1_state[i], filtered_data[i]);
			}
		}

		err = R_CTSU_DataInsert(g_qe_ctsu_instance_config01.p_ctrl, filtered_data);

		if(err == FSP_SUCCESS)
		{
			err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &button_status, NULL, NULL);

			if(err == FSP_SUCCESS )
			{
				if(prev_button_status != button_status)
				{
					/* Erase previous text*/
					Text_put_line(TEXT_X_POSITION, TEXT_Y_POSITION, "ERROR", COLOUR_WHITE, COLOUR_WHITE);
				}

				if(button_status > 0ULL)
				{
					/* Write new text*/
					Text_put_line(TEXT_X_POSITION, TEXT_Y_POSITION, "ON", COLOUR_BLACK, COLOUR_WHITE);
				}
				else
				{
					/* Write new text*/
					Text_put_line(TEXT_X_POSITION, TEXT_Y_POSITION, "OFF", COLOUR_BLACK, COLOUR_WHITE);
				}

				prev_button_status = button_status;
			}
			else
			{
				/* Erase previous text*/
				Text_put_line(TEXT_X_POSITION, TEXT_Y_POSITION, "ERROR", COLOUR_WHITE, COLOUR_WHITE);
				/* Write new text*/
				Text_put_line(TEXT_X_POSITION, TEXT_Y_POSITION, "ERROR", COLOUR_BLACK, COLOUR_WHITE);
			}

			St7735s_refresh();
		}
	}
}

void qe_touch_delay(uint16_t delay_us)
{
	uint32_t i;
	uint32_t loops_required;
	uint16_t clock_mhz;

	clock_mhz = (uint16_t)(R_BSP_GetFclkFreqHz() / 1000000);
	if (0 == clock_mhz)
	{
		clock_mhz = 1;
	}

	loops_required = ((uint32_t)delay_us * (uint32_t)clock_mhz);
	loops_required /= 20;
	for (i = 0; i < loops_required; i++)
	{
		BSP_NOP();
	}
}

static void Touch_callback(touch_callback_args_t * p_args)
{
	(void)p_args;

    g_qe_touch_flag = 1;
    g_qe_ctsu_event = p_args -> event;

	/* Clear interval timer interrupt flags*/
	ITLS0 = 0U;
	ITLIF = 0U;
}
/* END OF FUNCTION*/
