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
* File Name        : Config_RTC.c
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
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Create
* Description  : This function initializes the real-time clock module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Create(void)
{
    /* Supplies input clock */
    RTCWEN = 1U;
    /* Disable RTC clock operation */
    RTCE = 0U;
    /* Disable INTRTC interrupt */
    RTCMK = 1U;
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
    /* Set INTRTC Low priority */
    RTCPR1 = 1U;
    RTCPR0 = 1U;
    /* Set fRTCCK */
    RTCC0 = _00_RTC_CLK_32KHZ;
    /* Set 12-/24-hour system and period of Constant-period interrupt (INTRTC) */
    RTCC0 |= (_03_RTC_INTRTC_CLOCK_1MINU);

    R_Config_RTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Start
* Description  : This function enables the real-time clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Start(void)
{
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
    /* Enable INTRTC interrupt */
    RTCMK = 0U;
    /* Enable RTC clock operation */
    RTCE = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Stop
* Description  : This function disables the real-time clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Stop(void)
{
    /* Disable RTC clock operation */
    RTCE = 0U;
    /* Disable INTRTC interrupt */
    RTCMK = 1U;
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Set_ConstPeriodInterruptOn
* Description  : This function enables constant-period interrupt.
* Arguments    : period -
*                    the constant period of INTRTC
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_RTC_Set_ConstPeriodInterruptOn(e_rtc_int_period_t period)
{
    MD_STATUS status = MD_OK;
    if ((period < HALFSEC) || (period > ONEMONTH))
    {
        status = MD_ARGERROR;
    }
    else
    {
        /* Disable INTRTC */
        RTCMK = 1U;
        RTCC0 = (uint8_t)((RTCC0 & _F8_RTC_INTRTC_CLEAR) | period);
        RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;
        /* Clear INTRTC interrupt flag */
        RTCIF = 0U;
        /* Enable INTRTC interrupt */
        RTCMK = 0U;
    }
    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Set_ConstPeriodInterruptOff
* Description  : This function disables constant-period interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Set_ConstPeriodInterruptOff(void)
{
    RTCC0 &= _F8_RTC_INTRTC_CLEAR;
    RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
