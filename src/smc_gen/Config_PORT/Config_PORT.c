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
* File Name        : Config_PORT.c
* Component Version: 1.4.0
* Device(s)        : R7F100GGNxFB
* Description      : This file implements device driver for Config_PORT.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_PORT.h"
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
* Function Name: R_Config_PORT_Create
* Description  : This function initializes the port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PORT_Create(void)
{
    volatile uint16_t w_count;

    CCDE = _00_P63_OUTPUT_CURRENT_OFF | _40_P62_OUTPUT_CURRENT_ON | _00_P61_OUTPUT_CURRENT_OFF | 
           _00_P60_OUTPUT_CURRENT_OFF | _00_P51_OUTPUT_CURRENT_OFF | _00_P50_OUTPUT_CURRENT_OFF | 
           _02_P17_OUTPUT_CURRENT_ON | _01_P16_OUTPUT_CURRENT_ON;

    /* Wait for stable time (10us) */
    for (w_count = 0U; w_count < PORT_STABLE_WAITTIME; w_count++)
    {
        NOP();
    }
 
    CCS0 = _00_OUTPUT_CURRENT_HIZ;
    CCS6 = _00_OUTPUT_CURRENT_HIZ;
    /* Set PORT0 registers */
    P0 = _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    PDIDIS0 = _00_PDIDISn0_INPUT_BUFFER_ON;
    POM0 = _00_POMn0_NCH_OFF;
    PMCT0 = _00_PMCTn1_DIGITAL_ON | _00_PMCTn0_NOT_USE;
    PMCE0 = _00_PMCEn1_DIGITAL_ON;
    PM0 =  _FC_PM0_DEFAULT | _00_PMn1_MODE_OUTPUT | _01_PMn0_NOT_USE;
    /* Set PORT1 registers */
    P1 = _00_Pn7_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _08_Pn3_OUTPUT_1 | 
         _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    PDIDIS1 = _00_PDIDISn5_INPUT_BUFFER_ON | _00_PDIDISn4_INPUT_BUFFER_ON | _00_PDIDISn3_INPUT_BUFFER_ON | 
              _00_PDIDISn2_INPUT_BUFFER_ON | _00_PDIDISn1_INPUT_BUFFER_ON | _00_PDIDISn0_INPUT_BUFFER_ON;
    POM1 = _00_POMn5_NCH_OFF | _00_POMn4_NCH_OFF | _00_POMn3_NCH_OFF | _00_POMn2_NCH_OFF | _00_POMn1_NCH_OFF | 
           _00_POMn0_NCH_OFF;
    PMCA1 = _F7_PMCA1_DEFAULT | _00_PMCAn3_DIGITAL_ON;
    PMCE1 = _00_PMCEn7_DIGITAL_ON | _00_PMCEn6_DIGITAL_ON | _00_PMCEn5_NOT_USE | _00_PMCEn4_DIGITAL_ON | 
            _00_PMCEn3_DIGITAL_ON | _00_PMCEn2_NOT_USE | _00_PMCEn1_NOT_USE | _00_PMCEn0_NOT_USE;
    PM1 = _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _20_PMn5_NOT_USE | _00_PMn4_MODE_OUTPUT | 
          _00_PMn3_MODE_OUTPUT | _04_PMn2_NOT_USE | _02_PMn1_NOT_USE | _01_PMn0_NOT_USE;
    /* Set PORT2 registers */
    P2 = _00_Pn7_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _00_Pn3_OUTPUT_0 | 
         _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    PMCA2 = _80_PMCAn7_NOT_USE | _00_PMCAn6_DIGITAL_ON | _00_PMCAn5_DIGITAL_ON | _00_PMCAn4_DIGITAL_ON | 
            _00_PMCAn3_DIGITAL_ON | _00_PMCAn2_DIGITAL_ON | _00_PMCAn1_DIGITAL_ON | _00_PMCAn0_DIGITAL_ON;
    PMCT2 = _00_PMCTn7_NOT_USE | _00_PMCTn6_DIGITAL_ON | _00_PMCTn5_DIGITAL_ON | _00_PMCTn4_DIGITAL_ON | 
            _00_PMCTn3_DIGITAL_ON | _00_PMCTn2_DIGITAL_ON;
    PM2 = _80_PMn7_NOT_USE | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT | 
          _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    /* Set PORT4 registers */
    P4 = _02_Pn1_OUTPUT_1 | _00_Pn0_OUTPUT_0;
    PM4 =  _FC_PM4_DEFAULT | _00_PMn1_MODE_OUTPUT | _01_PMn0_NOT_USE;
    /* Set PORT5 registers */
    PDIDIS5 = _01_PDIDISn0_INPUT_BUFFER_OFF;
    /* Set PORT6 registers */
    P6 = _08_Pn3_OUTPUT_1 | _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn0_OUTPUT_0;
    PMCE6 = _00_PMCEn1_NOT_USE | _00_PMCEn0_NOT_USE;
    PM6 =  _F0_PM6_DEFAULT | _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _02_PMn1_NOT_USE | _01_PMn0_NOT_USE;
    /* Set PORT7 registers */
    P7 = _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _08_Pn3_OUTPUT_1 | _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | 
         _01_Pn0_OUTPUT_1;
    PDIDIS7 = _00_PDIDISn4_INPUT_BUFFER_ON | _00_PDIDISn2_INPUT_BUFFER_ON | _00_PDIDISn1_INPUT_BUFFER_ON;
    POM7 = _00_POMn4_NCH_OFF | _00_POMn2_NCH_OFF | _00_POMn1_NCH_OFF;
    PMCT7 = _00_PMCTn5_DIGITAL_ON | _00_PMCTn4_NOT_USE | _00_PMCTn3_DIGITAL_ON | _00_PMCTn2_NOT_USE | 
            _00_PMCTn1_NOT_USE | _00_PMCTn0_DIGITAL_ON;
    PM7 = _C0_PM7_DEFAULT | _00_PMn5_MODE_OUTPUT | _10_PMn4_NOT_USE | _00_PMn3_MODE_OUTPUT | _04_PMn2_NOT_USE | 
          _02_PMn1_NOT_USE | _00_PMn0_MODE_OUTPUT;
    /* Set PORT12 registers */
    P12 = _00_Pn2_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _01_Pn0_OUTPUT_1;
    PDIDIS12 = _00_PDIDISn0_INPUT_BUFFER_ON;
    POM12 = _00_POMn0_NCH_OFF;
    PMCA12 = _FE_PMCA12_DEFAULT | _00_PMCAn0_DIGITAL_ON;
    PM12 = _F8_PM12_DEFAULT | _10_PMn4_NOT_USE | _08_PMn3_NOT_USE | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | 
           _00_PMn0_MODE_OUTPUT;
    /* Set PORT13 registers */
    P13 = _00_Pn0_OUTPUT_0;
    PDIDIS13 = _00_PDIDISn7_INPUT_BUFFER_ON;
    /* Set PORT14 registers */
    P14 = _00_Pn7_OUTPUT_0 | _40_Pn6_OUTPUT_1 | _00_Pn0_OUTPUT_0;
    PMCA14 = _7F_PMCA14_DEFAULT | _00_PMCAn7_DIGITAL_ON;
    PM14 =  _3E_PM14_DEFAULT | _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;

    R_Config_PORT_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_PORT_ReadPmnValues
* Description  : This function specifies the value in the output latch for a port is read when the pin is in output mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PORT_ReadPmnValues(void)
{
    PMS = _00_PMN_VALUES;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
