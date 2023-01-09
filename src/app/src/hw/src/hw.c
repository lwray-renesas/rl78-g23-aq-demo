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

/** variable to store event flags*/
volatile hardware_event_t hw_event_flags = NO_EVENT;
/** counter defined here but manipulated by timer 00 & 05 modules*/
volatile int16_t rotary_count = 0;
/** local variable used to track the rotary count value*/
static volatile int16_t l_rotary_count = 0;

/** @brief Performs ELCL Setup*/
static void Setup_elcl(void);

/** @brief function to set ctsu pins*/
extern void R_CTSU_PinSetInit(void);

void Hw_init(void)
{
	static uint64_t l_button_status = 0ULL;
	touch_err_t err;

	EI();

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

	MK2H |= 0x40;    /* Disable interrupt servicing of "write request interrupt for setting registers for each channel" */
	MK3L |= 0x01;    /* Disable interrupt servicing of "measurement data transfer request interrupt" */

	R_Config_TAU0_0_Start();
	R_Config_TAU0_1_Start();
	R_Config_TAU0_2_Start();
	R_Config_CSI30_Start_app();

	/* Sets ELCL connections*/
	Setup_elcl();
}
/* END OF FUNCTION*/

void Hw_ctsu_start(void)
{
	static uint64_t l_button_status = 0ULL;
	fsp_err_t err = FSP_SUCCESS;

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
		if (FSP_SUCCESS == err)
		{
			break;
		}
	}

	/* Keep reading until touch has been removed*/
	while(true)
	{
		while (!HW_EVENT_OCCURRED(hw_event_flags, PROXIMITY_SCAN_COMPLETE))
		{
			NOP();
		}

		hw_event_flags = NO_EVENT; /* Reset the event flags*/

		err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &l_button_status, NULL, NULL);
		if (l_button_status == 0ULL)
		{
			break;
		}
	}
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
	Elcl_set_logic(&elcl_ctl, ELCL_BLOCK1, ELCL_AND_CELL_0);
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
