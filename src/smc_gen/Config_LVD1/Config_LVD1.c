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
* File Name        : Config_LVD1.c
* Component Version: 1.1.0
* Device(s)        : R7F100GFNxFP
* Description      : This file implements device driver for Config_LVD1.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_LVD1.h"
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
* Function Name: R_Config_LVD1_Create
* Description  : This function initializes the voltage detector module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_LVD1_Create(void)
{        
    LVIMK = 1U;    /* disable INTLVI interrupt */
    LVIIF = 0U;    /* clear INTLVI interrupt flag */
    /* Set INTLVI priority */
    LVIPR1 = 1U;
    LVIPR0 = 1U;
    LVISEN = 1U;    /*Enable of rewriting the LVIS register*/
    LVIS = _00_LVD_MODE_INT | _15_LVD_LEVEL_276;
    LVISEN = 0U;    /*Disable of rewriting the LVIS register*/

    R_Config_LVD1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_LVD1_Start
* Description  : This function starts the voltage detector operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_LVD1_Start(void)
{
    volatile uint16_t w_count;
    LVISEN = 1U;    /*enable of rewriting the LVIS register*/
    LVD1EN = 1U;    /*Start the lvd1 operation*/
    LVISEN = 0U;    /*disable of rewriting the LVIS register*/
    /* LVD1 is enabled after the stabilization waiting time (at least 500 us). */
    for (w_count = 0U; w_count < LVD1_STABILIZATION_WAITTIME; w_count++)
    {
        NOP();
    }
}

/***********************************************************************************************************************
* Function Name: R_Config_LVD1_Stop
* Description  : This function stops the voltage detector operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_LVD1_Stop(void)
{
    LVISEN = 1U;    /*enable of rewriting the LVIS register*/
    LVD1EN = 0U;    /*stop the lvd1 operation*/
    LVISEN = 0U;    /*disable of rewriting the LVIS register*/
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
