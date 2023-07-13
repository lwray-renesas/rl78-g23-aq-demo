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
* File Name        : r_cg_pclbuz.h
* Version          : 1.0.13
* Device(s)        : R7F100GGNxFB
* Description      : General header file for PCLBUZ peripheral.
***********************************************************************************************************************/

#ifndef PCLBUZ_H
#define PCLBUZ_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Clock Output Select Registers n (CKSn)
*/
/* PCLBUZn output enable/disable specification (PCLOEn) */
#define _80_PCLBUZ_OUTPUT_ENABLE        (0x80U)    /* pclbuz pin output enable */
#define _00_PCLBUZ_OUTPUT_DISABLE       (0x00U)    /* pclbuz pin output disable */
/* PCLBUZn output clock selection (CSELn, CCSn2 - CCSn0) */
#define _00_PCLBUZ_OUTCLK_FMAIN0        (0x00U)    /* fMAIN */
#define _01_PCLBUZ_OUTCLK_FMAIN1        (0x01U)    /* fMAIN/2 */
#define _02_PCLBUZ_OUTCLK_FMAIN2        (0x02U)    /* fMAIN/2^2 */
#define _03_PCLBUZ_OUTCLK_FMAIN3        (0x03U)    /* fMAIN/2^3 */
#define _04_PCLBUZ_OUTCLK_FMAIN4        (0x04U)    /* fMAIN/2^4 */
#define _05_PCLBUZ_OUTCLK_FMAIN11       (0x05U)    /* fMAIN/2^11 */
#define _06_PCLBUZ_OUTCLK_FMAIN12       (0x06U)    /* fMAIN/2^12 */
#define _07_PCLBUZ_OUTCLK_FMAIN13       (0x07U)    /* fMAIN/2^13 */
#define _08_PCLBUZ_OUTCLK_FSXP0         (0x08U)    /* fSXP */
#define _09_PCLBUZ_OUTCLK_FSXP1         (0x09U)    /* fSXP/2 */
#define _0A_PCLBUZ_OUTCLK_FSXP2         (0x0AU)    /* fSXP/2^2 */
#define _0B_PCLBUZ_OUTCLK_FSXP3         (0x0BU)    /* fSXP/2^3 */
#define _0C_PCLBUZ_OUTCLK_FSXP4         (0x0CU)    /* fSXP/2^4 */
#define _0D_PCLBUZ_OUTCLK_FSXP5         (0x0DU)    /* fSXP/2^5 */
#define _0E_PCLBUZ_OUTCLK_FSXP6         (0x0EU)    /* fSXP/2^6 */
#define _0F_PCLBUZ_OUTCLK_FSXP7         (0x0FU)    /* fSXP/2^7 */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
