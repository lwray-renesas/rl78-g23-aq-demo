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
* File Name        : Config_CSI30.c
* Component Version: 1.2.0
* Device(s)        : R7F100GSNxFB
* Description      : This file implements device driver for Config_CSI30.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_CSI30.h"
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
volatile uint8_t * gp_csi30_tx_address;    /* csi30 send buffer address */
volatile uint16_t g_csi30_tx_count;        /* csi30 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_CSI30_Create
* Description  : This function initializes the CSI30 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI30_Create(void)
{
    SPS1 &= _00F0_SAU_CK00_CLEAR;
    SPS1 |= _0000_SAU_CK00_FCLK_0;
    /* Stop channel 2 */
    ST1 |= _0004_SAU_CH2_STOP_TRG_ON;
    /* Mask channel 2 interrupt */
    CSIMK30 = 1U;    /* disable INTCSI30 interrupt */
    CSIIF30 = 0U;    /* clear INTCSI30 interrupt flag */
    /* Set INTCSI30 level 1 priority */
    CSIPR130 = 0U;
    CSIPR030 = 1U;
    SIR12 = _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR12 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR12 = _0004_SAU_SCRMN_INITIALVALUE | _8000_SAU_TRANSMISSION | _3000_SAU_TIMING_4 | _0000_SAU_MSB | 
            _0003_SAU_LENGTH_8;
    SDR12 = _0200_SAU1_CH2_BAUDRATE_DIVISOR;
    SO1 &= (uint16_t)~_0400_SAU_CH2_CLOCK_OUTPUT_1;    /* CSI30 clock initial level */
    SO1 &= (uint16_t)~_0004_SAU_CH2_DATA_OUTPUT_1;    /* CSI30 SO initial level */
    SOE1 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable CSI30 output */
    /* Set SO30 pin */
    P14 |= 0x10U;
    PM14 &= 0xEFU;
    /* Set SCK30 pin */
    P14 |= 0x04U;
    PM14 &= 0xFBU;
    
    R_Config_CSI30_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI30_Start
* Description  : This function starts the CSI30 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI30_Start(void)
{
    SO1 &= (uint16_t)~_0400_SAU_CH2_CLOCK_OUTPUT_1;    /* CSI30 clock initial level */
    SO1 &= (uint16_t)~_0004_SAU_CH2_DATA_OUTPUT_1;    /* CSI30 SO initial level */
    SOE1 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable CSI30 output */
    SS1 |= _0004_SAU_CH2_START_TRG_ON;    /* enable CSI30 */
    CSIIF30 = 0U;    /* clear INTCSI30 interrupt flag */
    CSIMK30 = 0U;    /* enable INTCSI30 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI30_Stop
* Description  : This function stops the CSI30 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI30_Stop(void)
{
    CSIMK30 = 1U;    /* disable INTCSI30 interrupt */
    ST1 |= _0004_SAU_CH2_STOP_TRG_ON;    /* disable CSI30 */
    SOE1 &= (uint16_t)~_0004_SAU_CH2_OUTPUT_ENABLE;    /* disable CSI30 output */
    CSIIF30 = 0U;    /* clear INTCSI30 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI30_Send
* Description  : This function sends CSI30 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_CSI30_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_csi30_tx_count = tx_num;    /* send data count */
        gp_csi30_tx_address = tx_buf;    /* send buffer pointer */
        CSIMK30 = 1U;    /* disable INTCSI30 interrupt */
        SIO30 = *gp_csi30_tx_address;    /* started by writing data to SDR12[7:0] */
        gp_csi30_tx_address++;
        g_csi30_tx_count--;
        CSIMK30 = 0U;    /* enable INTCSI30 interrupt */
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */

void R_Config_CSI30_Start_app(void)
{
	SO1 &= (uint16_t)~_0400_SAU_CH2_CLOCK_OUTPUT_1;    /* CSI30 clock initial level */
	SO1 &= (uint16_t)~_0004_SAU_CH2_DATA_OUTPUT_1;    /* CSI30 SO initial level */
	SOE1 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable CSI30 output */
	SS1 |= _0004_SAU_CH2_START_TRG_ON;    /* enable CSI30 */
	CSIMK30 = 1U;    /* disable INTCSI30 interrupt */
	CSIIF30 = 0U;    /* clear INTCSI30 interrupt flag */
}

void R_Config_CSI30_Send_app(uint8_t __far const * const tx_buf, uint16_t tx_num)
{
	uint16_t l_tx_num = tx_num;
	uint8_t __far const * l_tx_buf = tx_buf;

	while(l_tx_num > 0U)
	{
		SIO30 = *l_tx_buf;

		l_tx_num--;
		l_tx_buf++;

		/* Wait for the interrupt flag to set*/
		while(0U == CSIIF30)
		{
			NOP();
		}

		CSIIF30 = 0U;
	}
}

/* End user code. Do not edit comment generated here */
