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
* File Name        : Config_ITL012_ITL013.c
* Component Version: 1.2.0
* Device(s)        : R7F100GSNxFB
* Description      : This file implements device driver for Config_ITL012_ITL013.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_ITL012_ITL013.h"
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
* Function Name: R_Config_ITL012_ITL013_Create
* Description  : This function initializes the ITL012_ITL013 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ITL012_ITL013_Create(void)
{
    /* Stop 32-bit interval timer */
    ITLCTL0 = 0x00U;
    /* 32-bit interval timer used as 16-bit timer */
    ITLCTL0 |= _40_ITL_MODE_16BIT;
    ITLCSEL0 &= _F8_ITL_CLOCK_FITL0_CLEAR;
    ITLCSEL0 |= _04_ITL_CLOCK_FITL0_FSXP;
    ITLFDIV01 &= _F8_ITL_ITL012_FITL0_CLEAR;
    ITLFDIV01 |= _07_ITL_ITL012_FITL0_128;
    ITLCMP01 = _59FF_ITL_ITLCMP01_VALUE;
    
    R_Config_ITL012_ITL013_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_ITL012_ITL013_Start
* Description  : This function starts the ITL012_ITL013 channel.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ITL012_ITL013_Start(void)
{
    ITLEN02 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_ITL012_ITL013_Stop
* Description  : This function stops the ITL012_ITL013 channel.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ITL012_ITL013_Stop(void)
{
    ITLEN02 = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_ITL012_ITL013_Set_OperationMode
* Description  : This function is used to stop counter and clear interrupt flag before changing operation mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ITL012_ITL013_Set_OperationMode(void)
{
    /* Stop 32-bit interval timer */
    ITLCTL0 &= 0xF0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */