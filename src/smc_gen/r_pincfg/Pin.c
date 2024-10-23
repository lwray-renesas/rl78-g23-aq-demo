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
* Copyright (C) 2021, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Pin.c
* Version          : 1.0.0
* Device(s)        : R7F100GGNxFB
* Description      : This file implements SMC pin code generation.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
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
* Function Name: R_Pins_Create
* Description  : This function initializes Smart Configurator pins
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Pins_Create(void)
{
    /* Set CCD00 pin */
    PMCE1 &= 0xBFU;
    CCDE |= 0x01U;
    P1 &= 0xBFU;
    PM1 &= 0xBFU;

    /* Set CCD01 pin */
    PMCE1 &= 0x7FU;
    CCDE |= 0x02U;
    PTDC &= 0xFBU;
    P1 &= 0x7FU;
    PM1 &= 0x7FU;

    /* Set CCD06 pin */
    CCDE |= 0x40U;
    P6 &= 0xFBU;
    PM6 &= 0xFBU;

    /* Set INTP0 pin */
    /* No register setting has been required for pin */

    /* Set INTP8 pin */
    PMCT7 &= 0xEFU;
    PM7 |= 0x10U;

    /* Set PCLBUZ1 pin */
    POM1 &= 0xDFU;
    PMCE1 &= 0xDFU;
    P1 &= 0xDFU;
    PM1 &= 0xDFU;

    /* Set RxDA0 pin */
    PMCT7 &= 0xFDU;
    PM7 |= 0x02U;

    /* Set TS25 pin */
    PMCA2 &= 0x7FU;
    PMCT2 |= 0x80U;
    PM2 |= 0x80U;

    /* Set TSCAP pin */
    PMCT3 |= 0x01U;
    PM3 |= 0x01U;

    /* Set TxDA0 pin */
    PMCT7 &= 0xFBU;
    PFOE1 |= 0x10U;
    P7 |= 0x04U;
    PM7 &= 0xFBU;

}

