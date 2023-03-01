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
* File Name        : Config_DTC.c
* Component Version: 1.1.1
* Device(s)        : R7F100GFNxFP
* Description      : This file implements device driver for Config_DTC.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_DTC.h"
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
#pragma address dtc_vectortable = 0x0FFD00U
uint8_t __near dtc_vectortable[40U];

#pragma address dtc_controldata_0 = 0x0FFD40U
st_dtc_data_t __near dtc_controldata_0;

#pragma address dtc_controldata_1 = 0x0FFD48U
st_dtc_data_t __near dtc_controldata_1;

#pragma address dtc_controldata_22 = 0x0FFDF0U
st_dtc_data_t __near dtc_controldata_22;

#pragma address dtc_controldata_23 = 0x0FFDF8U
st_dtc_data_t __near dtc_controldata_23;

/***********************************************************************************************************************
* Function Name: R_Config_DTC_Create
* Description  : This function initializes the DTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_DTC_Create(void)
{
    /* Enable input clock supply */
    DTCEN = 1U;
    /* Disable all DTC channels operation */
    DTCEN0 = 0x00U;
    DTCEN1 = 0x00U;
    DTCEN2 = 0x00U;
    DTCEN3 = 0x00U;
    DTCEN4 = 0x00U;
    /* Set base address */
    DTCBAR = 0xFDU;
    /* Set DTCD0 */
    dtc_vectortable[29U] = 0x40U;
    dtc_controldata_0.dtccr = _00_DTC_DATA_SIZE_8BITS | _00_DTC_REPEAT_INT_DISABLE | _00_DTC_CHAIN_TRANSFER_DISABLE | 
                              _00_DTC_DEST_ADDR_FIXED | _02_DTC_REPEAT_AREA_SOURCE | _01_DTC_TRANSFER_MODE_REPEAT;
    dtc_controldata_0.dtbls = _01_DTCD0_TRANSFER_BLOCKSIZE;
    dtc_controldata_0.dtcct = _08_DTCD0_TRANSFER_BYTE;
    dtc_controldata_0.dtrld = _08_DTCD0_TRANSFER_BYTE;
    dtc_controldata_0.dtsar = _E000_DTCD0_SRC_ADDRESS;
    dtc_controldata_0.dtdar = _FFA6_DTCD0_DEST_ADDRESS;
    /* Set DTCD1 */
    dtc_vectortable[12U] = 0x48U;
    dtc_controldata_1.dtccr = _00_DTC_DATA_SIZE_8BITS | _00_DTC_CHAIN_TRANSFER_DISABLE | _00_DTC_DEST_ADDR_FIXED | 
                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_TRANSFER_MODE_NORMAL;
    dtc_controldata_1.dtbls = _01_DTCD1_TRANSFER_BLOCKSIZE;
    dtc_controldata_1.dtcct = _01_DTCD1_TRANSFER_BYTE;
    dtc_controldata_1.dtrld = 0x00U;
    dtc_controldata_1.dtsar = _0000_DTCD1_SRC_ADDRESS;
    dtc_controldata_1.dtdar = _0000_DTCD1_DEST_ADDRESS;
    /* Set DTCD22 */
    dtc_vectortable[33U] = 0xF0U;
    dtc_controldata_22.dtccr = _40_DTC_DATA_SIZE_16BITS | _00_DTC_CHAIN_TRANSFER_DISABLE | _00_DTC_DEST_ADDR_FIXED | 
                               _00_DTC_SOURCE_ADDR_FIXED | _00_DTC_TRANSFER_MODE_NORMAL;
    dtc_controldata_22.dtbls = _01_DTCD22_TRANSFER_BLOCKSIZE;
    dtc_controldata_22.dtcct = _01_DTCD22_TRANSFER_BYTE;
    dtc_controldata_22.dtrld = 0x00U;
    dtc_controldata_22.dtsar = _0000_DTCD22_SRC_ADDRESS;
    dtc_controldata_22.dtdar = _0000_DTCD22_DEST_ADDRESS;
    /* Set DTCD23 */
    dtc_vectortable[34U] = 0xF8U;
    dtc_controldata_23.dtccr = _40_DTC_DATA_SIZE_16BITS | _00_DTC_CHAIN_TRANSFER_DISABLE | _00_DTC_DEST_ADDR_FIXED | 
                               _00_DTC_SOURCE_ADDR_FIXED | _00_DTC_TRANSFER_MODE_NORMAL;
    dtc_controldata_23.dtbls = _01_DTCD23_TRANSFER_BLOCKSIZE;
    dtc_controldata_23.dtcct = _01_DTCD23_TRANSFER_BYTE;
    dtc_controldata_23.dtrld = 0x00U;
    dtc_controldata_23.dtsar = _0000_DTCD23_SRC_ADDRESS;
    dtc_controldata_23.dtdar = _0000_DTCD23_DEST_ADDRESS;

    R_Config_DTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_DTCD0_Start
* Description  : This function starts DTCD0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD0_Start(void)
{
    DTCEN3 |= _04_DTC_TAU06_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD0_Stop
* Description  : This function stops DTCD0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD0_Stop(void)
{
    DTCEN3 &= (uint8_t)~_04_DTC_TAU06_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD1_Start
* Description  : This function starts DTCD1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD1_Start(void)
{
    DTCEN1 |= _08_DTC_UART0T_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD1_Stop
* Description  : This function stops DTCD1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD1_Stop(void)
{
    DTCEN1 &= (uint8_t)~_08_DTC_UART0T_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD22_Start
* Description  : This function starts DTCD22 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD22_Start(void)
{
    DTCEN4 |= _40_DTC_CTSUWR_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD22_Stop
* Description  : This function stops DTCD22 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD22_Stop(void)
{
    DTCEN4 &= (uint8_t)~_40_DTC_CTSUWR_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD23_Start
* Description  : This function starts DTCD23 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD23_Start(void)
{
    DTCEN4 |= _20_DTC_CTSURD_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD23_Stop
* Description  : This function stops DTCD23 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD23_Stop(void)
{
    DTCEN4 &= (uint8_t)~_20_DTC_CTSURD_ACTIVATION_ENABLE;
}

/* Start user code for adding. Do not edit comment generated here */

void Start_dtc1(__near const uint8_t * src, __near uint8_t * dst, uint16_t cnt)
{
	dtc_controldata_1.dtbls = 1U;
	dtc_controldata_1.dtcct = (cnt > 255U) ? 0U : (uint8_t)cnt;
	dtc_controldata_1.dtsar = (uint16_t)src;
	dtc_controldata_1.dtdar = (uint16_t)dst;

	R_DTCD1_Start();
}
/* END OF FUNCTION*/

/* End user code. Do not edit comment generated here */
