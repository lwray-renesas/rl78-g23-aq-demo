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
* File Name        : Config_TAU0_3.c
* Component Version: 1.2.0
* Device(s)        : R7F100GFNxFP
* Description      : This file implements device driver for Config_TAU0_3.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_TAU0_3.h"
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
* Function Name: R_Config_TAU0_3_Create
* Description  : This function initializes the TAU0 channel3 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_3_Create(void)
{
    TPS0 &= _FF0F_TAU_CKM1_CLEAR;
    TPS0 |= _00E0_TAU_CKM1_FCLK_14;
    /* Stop channel 3 */
    TT0 |= _0008_TAU_CH3_STOP_TRG_ON;
    /* Mask channel 3 interrupt */
    TMMK03 = 1U;    /* disable INTTM03 interrupt */
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
    /* Set INTTM03 low priority */
    TMPR103 = 1U;
    TMPR003 = 1U;
    /* TAU03 is used as delay count function */
    NFEN1 |= _08_TAU_CH3_NOISE_ON;
    TMR03 = _8000_TAU_CLOCK_SELECT_CKM1 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_16BITS_MODE | 
            _0100_TAU_TRIGGER_TIMN_VALID | _0040_TAU_TIMN_EDGE_RISING | _0008_TAU_MODE_ONE_COUNT | 
            _0000_TAU_START_INT_UNUSED;
    TDR03 = _00C2_TAU_TDR03_VALUE;
    TOM0 &= (uint16_t)~_0008_TAU_CH3_SLAVE_OUTPUT;
    TOL0 &= (uint16_t)~_0008_TAU_CH3_OUTPUT_LEVEL_L;
    TO0 &= (uint16_t)~_0008_TAU_CH3_OUTPUT_VALUE_1;
    TOE0 &= (uint16_t)~_0008_TAU_CH3_OUTPUT_ENABLE;
    /* Set TI03 pin */
    PMCT3 &= 0xFDU;
    PM3 |= 0x02U;

    R_Config_TAU0_3_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_3_Start
* Description  : This function starts the TAU0 channel3 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_3_Start(void)
{
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
    TMMK03 = 0U;    /* enable INTTM03 interrupt */
    TS0 |= _0008_TAU_CH3_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_3_Stop
* Description  : This function stops the TAU0 channel3 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_3_Stop(void)
{
    TT0 |= _0008_TAU_CH3_STOP_TRG_ON;
    /* Mask channel 3 interrupt */
    TMMK03 = 1U;    /* disable INTTM03 interrupt */
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_3_Set_SoftwareTriggerOn
* Description  : This function generates software trigger.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_3_Set_SoftwareTriggerOn(void)
{
    TS0 |= _0008_TAU_CH3_START_TRG_ON;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
