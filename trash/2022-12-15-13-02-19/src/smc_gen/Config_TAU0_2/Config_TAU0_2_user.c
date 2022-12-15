/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021, 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_TAU0_2_user.c
* Component Version: 1.2.0
* Device(s)        : R7F100GSNxFB
* Description      : This file implements device driver for Config_TAU0_2.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_TAU0_2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_TAU0_2_interrupt(vect=INTTM02)
/* Start user code for pragma. Do not edit comment generated here */
#include "app.h"

#define BUTTON_ASSERTED			(0U)
#define BUTTON_LONG_PRESS_COUNT	(9U)
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
static volatile uint8_t button_hold_count = 0U;

typedef enum
{
	FIRST_DETECTION = 0U,
	HOLDING,
	WAIT_FOR_RELASE
}button_state_t;

volatile button_state_t button_state = FIRST_DETECTION;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_2_Create_UserInit
* Description  : This function adds user code after initializing the TAU0 channel2.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_2_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_TAU0_2_interrupt
* Description  : This function is INTTM02 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_TAU0_2_interrupt(void)
{
    /* Start user code for r_Config_TAU0_2_interrupt. Do not edit comment generated here */

	switch(button_state)
	{

	case FIRST_DETECTION:
	{
		/* Increment the hold count*/
		++button_hold_count;

		/* If the port is now de-asserted*/
		if(P1_bit.no7 != BUTTON_ASSERTED)
		{
			/* Consider the button to have been clicked*/
			button_state = FIRST_DETECTION;
			button_hold_count = 0U;
			HW_SET_EVENT(hw_event_flags, BUTTON_CLICK);
		}
		else
		{
			/* Otherwise, we are holding the button down*/
			button_state = HOLDING;
		    TS0 |= _0004_TAU_CH2_START_TRG_ON; /* Manual trigger the delay counter again*/
		}
	}
	break;

	case HOLDING:
	{
		/* Increment the hold count*/
		++button_hold_count;

		/* If we have been holding the button down for the appropriate number of time slices*/
		if(button_hold_count > BUTTON_LONG_PRESS_COUNT)
		{
			/* Consider the button to have been held*/
			button_state = WAIT_FOR_RELASE;
			button_hold_count = 0U;
			HW_SET_EVENT(hw_event_flags, BUTTON_LONG_PRESS);
		    TS0 |= _0004_TAU_CH2_START_TRG_ON; /* Manual trigger the delay counter again*/
		}
		else
		{
			/* If the port is now de-asserted*/
			if(P1_bit.no7 != BUTTON_ASSERTED)
			{
				/* Consider the button to have been clicked*/
				button_state = FIRST_DETECTION;
				button_hold_count = 0U;
				HW_SET_EVENT(hw_event_flags, BUTTON_CLICK);
			}
			else
			{
			    TS0 |= _0004_TAU_CH2_START_TRG_ON; /* Manual trigger the delay counter again*/
			}
		}
	}
	break;

	case WAIT_FOR_RELASE:
	{
		/* If the port is now de-asserted*/
		if(P1_bit.no7 != BUTTON_ASSERTED)
		{
			/* Consider the button to be released - now we can wait for the next event*/
			button_state = FIRST_DETECTION;
		}
		else
		{
		    TS0 |= _0004_TAU_CH2_START_TRG_ON; /* Manual trigger the delay counter again*/
		}
	}
	break;

	default:
		/* Do Nothing - Never Get Here*/
		break;
	}
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
