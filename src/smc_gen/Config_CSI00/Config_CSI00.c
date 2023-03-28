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
* File Name        : Config_CSI00.c
* Component Version: 1.2.0
* Device(s)        : R7F100GFNxFP
* Description      : This file implements device driver for Config_CSI00.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_CSI00.h"
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
volatile uint8_t * gp_csi00_tx_address;    /* csi00 send buffer address */
volatile uint16_t g_csi00_tx_count;        /* csi00 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Create
* Description  : This function initializes the CSI00 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI00_Create(void)
{
    SPS0 &= _00F0_SAU_CK00_CLEAR;
    SPS0 |= _0000_SAU_CK00_FCLK_0;
    /* Stop channel 0 */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    /* Set INTCSI00 level 1 priority */
    CSIPR100 = 0U;
    CSIPR000 = 1U;
    SIR00 = _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR00 = _0004_SAU_SCRMN_INITIALVALUE | _8000_SAU_TRANSMISSION | _3000_SAU_TIMING_4 | _0000_SAU_MSB | 
            _0003_SAU_LENGTH_8;
    SDR00 = _0000_SAU0_CH0_BAUDRATE_DIVISOR;
    SO0 &= (uint16_t)~_0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
    SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
    /* Set SO00 pin */
    PMCE1 &= 0xFBU;
    PFOE1 |= 0x01U;
    P1 |= 0x04U;
    PM1 &= 0xFBU;
    /* Set SCK00 pin */
    PMCE1 &= 0xFEU;
    PFOE1 |= 0x04U;
    P1 |= 0x01U;
    PM1 &= 0xFEU;
    
    R_Config_CSI00_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Start
* Description  : This function starts the CSI00 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI00_Start(void)
{
    SO0 &= (uint16_t)~_0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
    SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
    SS0 |= _0001_SAU_CH0_START_TRG_ON;    /* enable CSI00 */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    CSIMK00 = 0U;    /* enable INTCSI00 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Stop
* Description  : This function stops the CSI00 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI00_Stop(void)
{
    CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;    /* disable CSI00 */
    SOE0 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable CSI00 output */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Send
* Description  : This function sends CSI00 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_CSI00_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_csi00_tx_count = tx_num;    /* send data count */
        gp_csi00_tx_address = tx_buf;    /* send buffer pointer */
        CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
        SIO00 = *gp_csi00_tx_address;    /* started by writing data to SDR00[7:0] */
        gp_csi00_tx_address++;
        g_csi00_tx_count--;
        CSIMK00 = 0U;    /* enable INTCSI00 interrupt */
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
