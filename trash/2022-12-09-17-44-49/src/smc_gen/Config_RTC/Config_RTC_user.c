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
* File Name        : Config_RTC_user.c
* Component Version: 1.2.0
* Device(s)        : R7F100GSNxFB
* Description      : This file implements device driver for Config_RTC.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_RTC.h"
/* Start user code for include. Do not edit comment generated here */
#include "app.h"
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_RTC_interrupt(vect=INTRTC)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
static uint16_t rtc_battery_counter = 0U;
static uint16_t rtc_inactivity_counter = 0U;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Create_UserInit
* Description  : This function adds user code after initializing the real-time clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_RTC_callback_constperiod
* Description  : This function is real-time clock constant-period interrupt service handler.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_RTC_callback_constperiod(void)
{
    /* Start user code for r_Config_RTC_callback_constperiod. Do not edit comment generated here */
	++rtc_battery_counter;

	/* Read the battery every 30 minutes*/
	if(rtc_battery_counter > 29U)
	{
		Rltos_events_set(&gui_return_events, RTC_BATTERY);
		rtc_battery_counter = 0U;
	}

	/* Read the sensors every minute*/
	Rltos_events_set(&gui_return_events, RTC_SENSOR);

	/* If the system is inactive for a length of time - enter low power*/
	if(!App_get_signal_activity())
	{
		++rtc_inactivity_counter;

		if(rtc_inactivity_counter > 3U)
		{
			/* Set the system as inactive*/
			rtc_inactivity_counter = 0U;
			App_signal_inactivity();
		}
	}

    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_RTC_interrupt
* Description  : This function is INTRTC interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_RTC_interrupt(void)
{
    if (1U == RIFG)
    {
        /* clear RIFG */
        RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;
        r_Config_RTC_callback_constperiod();
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
