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
* File Name        : Config_CSI00_user.c
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
#include "r_smc_entry.h"
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_CSI00_interrupt(vect=INTCSI00)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_csi00_tx_address;    /* csi00 send buffer address */
extern volatile uint16_t g_csi00_tx_count;        /* csi00 send data count */
/* Start user code for global. Do not edit comment generated here */

static volatile bool tx_done = true;

/** @brief sends the SPI via simple polling of interrupt flags (doesn't use isr)
 * @param tx_buf - pointer to data to send
 * @param tx_num - number of bytes to send
 */
static void Simple_polling_send(const uint8_t * const tx_buf, uint16_t tx_num);

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Create_UserInit
* Description  : This function adds user code after initializing the CSI00.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI00_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_CSI00_callback_sendend
* Description  : This function is a callback function when CSI00 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_CSI00_callback_sendend(void)
{
    /* Start user code for r_Config_CSI00_callback_sendend. Do not edit comment generated here */
	tx_done = true;
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_CSI00_interrupt
* Description  : This function is INTCSI00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_CSI00_interrupt(void)
{
    uint8_t err_type;

    err_type = (uint8_t)(SSR00 & _0001_SAU_OVERRUN_ERROR);
    SIR00 = (uint16_t)err_type;

    if (1U != err_type)
    {
        if (g_csi00_tx_count > 0U)
        {
            SIO00 = *gp_csi00_tx_address;
            gp_csi00_tx_address++;
            g_csi00_tx_count--;
        }
        else
        {
            r_Config_CSI00_callback_sendend();    /* complete send */
        }
    }
}

/* Start user code for adding. Do not edit comment generated here */

void R_Config_CSI00_Start_app(void)
{
	SO0 &= (uint16_t)~_0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
	SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
	SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
	SS0 |= _0001_SAU_CH0_START_TRG_ON;    /* enable CSI00 */
	CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
	CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
	g_csi00_tx_count = 0U; /* Force the spi tx end callback to trigger on dtc completion*/
}
/* END OF FUNCTION*/

void R_Config_CSI00_Send_app(const uint8_t * const tx_buf, uint16_t tx_num)
{
	const uint8_t * l_tx_buf = tx_buf;
	uint16_t l_tx_num = tx_num;
	uint16_t bytes_to_send = 0U;

	/* Wait for previous transmission to complete*/
	while(!tx_done)
	{
		NOP();
	}

	CSIMK00 = 0U;    /* enable INTCSI00 interrupt */

	do
	{
		tx_done = false;

		bytes_to_send = (l_tx_num > 255U) ? 256U : l_tx_num;
		l_tx_num = (l_tx_num > 255U) ? (l_tx_num-256U) : 0U;

		/* Two bytes or less don't use DTC*/
		if(bytes_to_send < 3U)
		{
			Simple_polling_send(l_tx_buf, bytes_to_send);
		}
		else
		{
			Start_dtc1(l_tx_buf+1, (__near uint8_t *)&SIO00, bytes_to_send-1U); /* Setup the DTC*/
			SIO00 = *l_tx_buf;    /* Trigger SPI transmission */
			l_tx_buf += bytes_to_send; /* Move the buffer pointer forward*/
		}

		/* Wait for transmission to complete*/
		while(!tx_done)
		{
			HALT();
		}
	}
	while(l_tx_num > 0U);

	CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
}
/* END OF FUNCTION*/

static void Simple_polling_send(const uint8_t * const tx_buf, uint16_t tx_num)
{
	uint16_t l_tx_num = tx_num;
	const uint8_t * l_tx_buf = tx_buf;

	CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
	CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */

	tx_done = false;

	while(l_tx_num > 0U)
	{
		SIO00 = *l_tx_buf;

		l_tx_num--;
		l_tx_buf++;

		/* Wait for the interrupt flag to set*/
		while(0U == CSIIF00)
		{
			NOP();
		}

		CSIIF00 = 0U;
	}

	tx_done = true;
}
/* END OF FUNCTION*/

/* End user code. Do not edit comment generated here */
