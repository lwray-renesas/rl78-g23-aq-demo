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
* Copyright (C) 2021, 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_INTC.c
* Component Version: 1.4.0
* Device(s)        : R7F100GGNxFB
* Description      : This file implements device driver for Config_INTC.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_INTC.h"
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
* Function Name: R_Config_INTC_Create
* Description  : This function initializes the INTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_Create(void)
{
    PMK0 = 1U;    /* disable INTP0 operation */
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
    PMK8 = 1U;    /* disable INTP8 operation */
    PIF8 = 0U;    /* clear INTP8 interrupt flag */
    /* Set INTP0 low priority */
    PPR10 = 1U;
    PPR00 = 1U;
    /* Set INTP8 low priority */
    PPR18 = 1U;
    PPR08 = 1U;
    EGN0 = _01_INTP0_EDGE_FALLING_SEL;
    EGP0 = _00_INTP0_EDGE_RISING_UNSEL;
    EGN1 = _01_INTP8_EDGE_FALLING_SEL;
    EGP1 = _00_INTP8_EDGE_RISING_UNSEL;
    /* Set INTP8 pin */
    PMCT7 &= 0xEFU;
    PM7 |= 0x10U;

    R_Config_INTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP0_Start
* Description  : This function clears INTP0 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP0_Start(void)
{
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
    PMK0 = 0U;    /* enable INTP0 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP0_Stop
* Description  : This function disables INTP0 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP0_Stop(void)
{
    PMK0 = 1U;    /* disable INTP0 interrupt */
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP8_Start
* Description  : This function clears INTP8 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP8_Start(void)
{
    PIF8 = 0U;    /* clear INTP8 interrupt flag */
    PMK8 = 0U;    /* enable INTP8 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP8_Stop
* Description  : This function disables INTP8 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP8_Stop(void)
{
    PMK8 = 1U;    /* disable INTP8 interrupt */
    PIF8 = 0U;    /* clear INTP8 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
