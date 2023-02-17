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
* File Name        : Config_PCLBUZ1.c
* Component Version: 1.2.0
* Device(s)        : R7F100GFNxFP
* Description      : This file implements device driver for Config_PCLBUZ1.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_PCLBUZ1.h"
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
* Function Name: R_Config_PCLBUZ1_Create
* Description  : This function initializes the PCLBUZ1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PCLBUZ1_Create(void)
{
    PCLOE1 = 0U;    /* disable PCLBUZ1 operation */
    /* Set PCLBUZ1 pin */
    POM1 &= 0xDFU;
    PMCE1 &= 0xDFU;
    P1 &= 0xDFU;
    PM1 &= 0xDFU;
    CKS1 = _0E_PCLBUZ_OUTCLK_FSXP6;

    R_Config_PCLBUZ1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_PCLBUZ1_Start
* Description  : This function starts the PCLBUZ1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PCLBUZ1_Start(void)
{
    PCLOE1 = 1U;    /* enable PCLBUZ1 operation */
}

/***********************************************************************************************************************
* Function Name: R_Config_PCLBUZ1_Stop
* Description  : This function stops the PCLBUZ1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PCLBUZ1_Stop(void)
{
    PCLOE1 = 0U;    /* disable PCLBUZ1 operation */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
