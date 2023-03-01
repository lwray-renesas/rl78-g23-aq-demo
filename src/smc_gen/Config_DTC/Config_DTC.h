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
* File Name        : Config_DTC.h
* Component Version: 1.1.1
* Device(s)        : R7F100GFNxFP
* Description      : This file implements device driver for Config_DTC.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_dtc.h"

#ifndef CFG_Config_DTC_H
#define CFG_Config_DTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _01_DTCD0_TRANSFER_BLOCKSIZE       (0x01U)    /* transfer block size */
#define _08_DTCD0_TRANSFER_BYTE            (0x08U)    /* number of transfers */
#define _E000_DTCD0_SRC_ADDRESS            (0xE000U)
#define _FFA6_DTCD0_DEST_ADDRESS           (0xFFA6U)
#define _01_DTCD1_TRANSFER_BLOCKSIZE       (0x01U)    /* transfer block size */
#define _01_DTCD1_TRANSFER_BYTE            (0x01U)    /* number of transfers */
#define _0000_DTCD1_SRC_ADDRESS            (0x0000U)
#define _0000_DTCD1_DEST_ADDRESS           (0x0000U)
#define _01_DTCD22_TRANSFER_BLOCKSIZE       (0x01U)    /* transfer block size */
#define _01_DTCD22_TRANSFER_BYTE            (0x01U)    /* number of transfers */
#define _0000_DTCD22_SRC_ADDRESS            (0x0000U)
#define _0000_DTCD22_DEST_ADDRESS           (0x0000U)
#define _01_DTCD23_TRANSFER_BLOCKSIZE       (0x01U)    /* transfer block size */
#define _01_DTCD23_TRANSFER_BYTE            (0x01U)    /* number of transfers */
#define _0000_DTCD23_SRC_ADDRESS            (0x0000U)
#define _0000_DTCD23_DEST_ADDRESS           (0x0000U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct
{
    uint8_t  dtccr;
    uint8_t  dtbls;
    uint8_t  dtcct;
    uint8_t  dtrld;
    uint16_t dtsar;
    uint16_t dtdar;
}st_dtc_data_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_DTC_Create(void);
void R_DTCD0_Start(void);
void R_DTCD0_Stop(void);
void R_DTCD1_Start(void);
void R_DTCD1_Stop(void);
void R_DTCD22_Start(void);
void R_DTCD22_Stop(void);
void R_DTCD23_Start(void);
void R_DTCD23_Stop(void);
void R_Config_DTC_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
/** @brief Function to start the DTC running for spi operation.
 * @param src - pointer to src data
 * @param dst - pointer to destination
 * @param cnt - number of bytes to transmit
 */
 void Start_dtc1(__near const uint8_t * src, __near uint8_t * dst, uint16_t cnt);
/* End user code. Do not edit comment generated here */
#endif
