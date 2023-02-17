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
* File Name        : r_cg_dtc.h
* Version          : 1.0.11
* Device(s)        : R7F100GFNxFP
* Description      : General header file for DTC peripheral.
***********************************************************************************************************************/

#ifndef DTC_H
#define DTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral Enable Register 1 (PER1)
*/
/* Control of DTC input clock supply (DTCEN) */
#define _00_DTC_CLOCK_STOP                 (0x00U)    /* stops supply of input clock */
#define _08_DTC_CLOCK_SUPPLY               (0x08U)    /* supplies input clock */

/*
    DTC Control Register j (DTCCRj) (j = 0 to 23)
*/
/* Transfer data size selection (SZ) */
#define _00_DTC_DATA_SIZE_8BITS            (0x00U)    /* 8 bits */
#define _40_DTC_DATA_SIZE_16BITS           (0x40U)    /* 16 bits */
/* Enabling/disabling repeat mode interrupts (RPTINT) */
#define _00_DTC_REPEAT_INT_DISABLE         (0x00U)    /* interrupt generation disabled */
#define _20_DTC_REPEAT_INT_ENABLE          (0x20U)    /* interrupt generation enabled */
/* Enabling/disabling chain transfers (CHNE) */
#define _00_DTC_CHAIN_TRANSFER_DISABLE     (0x00U)    /* chain transfers disabled */
#define _10_DTC_CHAIN_TRANSFER_ENABLE      (0x10U)    /* chain transfers enable */
/* Transfer destination address control (DAMOD) */
#define _00_DTC_DEST_ADDR_FIXED            (0x00U)    /* fixed */
#define _08_DTC_DEST_ADDR_INCREMENTED      (0x08U)    /* incremented */
/* Transfer source address control (SAMOD) */
#define _00_DTC_SOURCE_ADDR_FIXED          (0x00U)    /* fixed */
#define _04_DTC_SOURCE_ADDR_INCREMENTED    (0x04U)    /* incremented */
/* Repeat area selection (RPTSEL) */
#define _00_DTC_REPEAT_AREA_DEST           (0x00U)    /* transfer destination is the repeat area */
#define _02_DTC_REPEAT_AREA_SOURCE         (0x02U)    /* transfer source is the repeat area */
/* Transfer mode selection (MODE) */
#define _00_DTC_TRANSFER_MODE_NORMAL       (0x00U)    /* normal mode */
#define _01_DTC_TRANSFER_MODE_REPEAT       (0x01U)    /* repeat mode */

/*
    DTC Activation Enable Register 0 (DTCEN0)
*/
/* DTC activation enable 06 (DTCEN06) */
#define _00_DTC_INTP0_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP0) */
#define _40_DTC_INTP0_ACTIVATION_ENABLE    (0x40U)    /* activation enabled (INTP0) */
/* DTC activation enable 05 (DTCEN05) */
#define _00_DTC_INTP1_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP1) */
#define _20_DTC_INTP1_ACTIVATION_ENABLE    (0x20U)    /* activation enabled (INTP1) */
/* DTC activation enable 04 (DTCEN04) */
#define _00_DTC_INTP2_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP2) */
#define _10_DTC_INTP2_ACTIVATION_ENABLE    (0x10U)    /* activation enabled (INTP2) */
/* DTC activation enable 03 (DTCEN03) */
#define _00_DTC_INTP3_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP3) */
#define _08_DTC_INTP3_ACTIVATION_ENABLE    (0x08U)    /* activation enabled (INTP3) */
/* DTC activation enable 02 (DTCEN02) */
#define _00_DTC_INTP4_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP4) */
#define _04_DTC_INTP4_ACTIVATION_ENABLE    (0x04U)    /* activation enabled (INTP4) */
/* DTC activation enable 01 (DTCEN01) */
#define _00_DTC_INTP5_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP5) */
#define _02_DTC_INTP5_ACTIVATION_ENABLE    (0x02U)    /* activation enabled (INTP5) */
/* DTC activation enable 00 (DTCEN00) */
#define _00_DTC_INTP6_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP6) */
#define _01_DTC_INTP6_ACTIVATION_ENABLE    (0x01U)    /* activation enabled (INTP6) */

/*
    DTC Activation Enable Register 1 (DTCEN1)
*/
/* DTC activation enable 17 (DTCEN17) */
#define _00_DTC_INTP7_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (INTP7) */
#define _80_DTC_INTP7_ACTIVATION_ENABLE    (0x80U)    /* activation enabled (INTP7) */
/* DTC activation enable 16 (DTCEN16) */
#define _00_DTC_KEY_ACTIVATION_DISABLE     (0x00U)    /* activation disabled (KEY) */
#define _40_DTC_KEY_ACTIVATION_ENABLE      (0x40U)    /* activation enabled (KEY) */
/* DTC activation enable 15 (DTCEN15) */
#define _00_DTC_AD_ACTIVATION_DISABLE      (0x00U)    /* activation disabled (AD) */
#define _20_DTC_AD_ACTIVATION_ENABLE       (0x20U)    /* activation enabled (AD) */
/* DTC activation enable 14 (DTCEN14) */
#define _00_DTC_UART0R_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART0R) */
#define _10_DTC_UART0R_ACTIVATION_ENABLE   (0x10U)    /* activation enabled (UART0R) */
/* DTC activation enable 13 (DTCEN13) */
#define _00_DTC_UART0T_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART0T) */
#define _08_DTC_UART0T_ACTIVATION_ENABLE   (0x08U)    /* activation enabled (UART0T) */
/* DTC activation enable 12 (DTCEN12) */
#define _00_DTC_UART1R_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART1R) */
#define _04_DTC_UART1R_ACTIVATION_ENABLE   (0x04U)    /* activation enabled (UART1R) */
/* DTC activation enable 11 (DTCEN11) */
#define _00_DTC_UART1T_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART1T) */
#define _02_DTC_UART1T_ACTIVATION_ENABLE   (0x02U)    /* activation enabled (UART1T) */
/* DTC activation enable 10 (DTCEN10) */
#define _00_DTC_UART2R_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART2R) */
#define _01_DTC_UART2R_ACTIVATION_ENABLE   (0x01U)    /* activation enabled (UART2R) */

/*
    DTC Activation Enable Register 2 (DTCEN2)
*/
/* DTC activation enable 27 (DTCEN27) */
#define _00_DTC_UART2T_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART2T) */
#define _80_DTC_UART2T_ACTIVATION_ENABLE   (0x80U)    /* activation enabled (UART2T) */
/* DTC activation enable 26 (DTCEN26) */
#define _00_DTC_UART3R_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART3R) */
#define _40_DTC_UART3R_ACTIVATION_ENABLE   (0x40U)    /* activation enabled (UART3R) */
/* DTC activation enable 25 (DTCEN25) */
#define _00_DTC_UART3T_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (UART3T) */
#define _20_DTC_UART3T_ACTIVATION_ENABLE   (0x20U)    /* activation enabled (UART3T) */
/* DTC activation enable 24 (DTCEN24) */
#define _00_DTC_UARTA0R_ACTIVATION_DISABLE (0x00U)    /* activation disabled (UARTA0R) */
#define _10_DTC_UARTA0R_ACTIVATION_ENABLE  (0x10U)    /* activation enabled (UARTA0R) */
/* DTC activation enable 23 (DTCEN23) */
#define _00_DTC_UARTA0T_ACTIVATION_DISABLE (0x00U)    /* activation disabled (UARTA0T) */
#define _08_DTC_UARTA0T_ACTIVATION_ENABLE  (0x08U)    /* activation enabled (UARTA0T) */
/* DTC activation enable 22 (DTCEN22) */
#define _00_DTC_UARTA1R_ACTIVATION_DISABLE (0x00U)    /* activation disabled (UARTA1R) */
#define _04_DTC_UARTA1R_ACTIVATION_ENABLE  (0x04U)    /* activation enabled (UARTA1R) */
/* DTC activation enable 21 (DTCEN21) */
#define _00_DTC_UARTA1T_ACTIVATION_DISABLE (0x00U)    /* activation disabled (UARTA1T) */
#define _02_DTC_UARTA1T_ACTIVATION_ENABLE  (0x02U)    /* activation enabled (UARTA1T) */
/* DTC activation enable 20 (DTCEN20) */
#define _00_DTC_TAU00_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU00) */
#define _01_DTC_TAU00_ACTIVATION_ENABLE    (0x01U)    /* activation enabled (TAU00) */

/*
    DTC Activation Enable Register 3 (DTCEN3)
*/
/* DTC activation enable 37 (DTCEN37) */
#define _00_DTC_TAU01_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU01) */
#define _80_DTC_TAU01_ACTIVATION_ENABLE    (0x80U)    /* activation enabled (TAU01) */
/* DTC activation enable 36 (DTCEN36) */
#define _00_DTC_TAU02_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU02) */
#define _40_DTC_TAU02_ACTIVATION_ENABLE    (0x40U)    /* activation enabled (TAU02) */
/* DTC activation enable 35 (DTCEN35) */
#define _00_DTC_TAU03_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU03) */
#define _20_DTC_TAU03_ACTIVATION_ENABLE    (0x20U)    /* activation enabled (TAU03) */
/* DTC activation enable 34 (DTCEN34) */
#define _00_DTC_TAU04_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU04) */
#define _10_DTC_TAU04_ACTIVATION_ENABLE    (0x10U)    /* activation enabled (TAU04) */
/* DTC activation enable 33 (DTCEN33) */
#define _00_DTC_TAU05_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU05) */
#define _08_DTC_TAU05_ACTIVATION_ENABLE    (0x08U)    /* activation enabled (TAU05) */
/* DTC activation enable 32 (DTCEN32) */
#define _00_DTC_TAU06_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU06) */
#define _04_DTC_TAU06_ACTIVATION_ENABLE    (0x04U)    /* activation enabled (TAU06) */
/* DTC activation enable 31 (DTCEN31) */
#define _00_DTC_TAU07_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (TAU07) */
#define _02_DTC_TAU07_ACTIVATION_ENABLE    (0x02U)    /* activation enabled (TAU07) */
/* DTC activation enable 30 (DTCEN30) */
#define _00_DTC_RTC_ACTIVATION_DISABLE     (0x00U)    /* activation disabled (RTC) */
#define _01_DTC_RTC_ACTIVATION_ENABLE      (0x01U)    /* activation enabled (RTC) */

/*
    DTC Activation Enable Register 4 (DTCEN4)
*/
/* DTC activation enable 47 (DTCEN47) */
#define _00_DTC_ITL_ACTIVATION_DISABLE     (0x00U)    /* activation disabled (ITL) */
#define _80_DTC_ITL_ACTIVATION_ENABLE      (0x80U)    /* activation enabled (ITL) */
/* DTC activation enable 46 (DTCEN46) */
#define _00_DTC_CTSUWR_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (CTSUWR) */
#define _40_DTC_CTSUWR_ACTIVATION_ENABLE   (0x40U)    /* activation enabled (CTSUWR) */
/* DTC activation enable 45 (DTCEN45) */
#define _00_DTC_CTSURD_ACTIVATION_DISABLE  (0x00U)    /* activation disabled (CTSURD) */
#define _20_DTC_CTSURD_ACTIVATION_ENABLE   (0x20U)    /* activation enabled (CTSURD) */
/* DTC activation enable 44 (DTCEN44) */
#define _00_DTC_COMP0_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (COMP0) */
#define _10_DTC_COMP0_ACTIVATION_ENABLE    (0x10U)    /* activation enabled (COMP0) */
/* DTC activation enable 43 (DTCEN43) */
#define _00_DTC_COMP1_ACTIVATION_DISABLE   (0x00U)    /* activation disabled (COMP1) */
#define _08_DTC_COMP1_ACTIVATION_ENABLE    (0x08U)    /* activation enabled (COMP1) */
/* DTC activation enable 42 (DTCEN42) */
#define _00_DTC_ELCL_ACTIVATION_DISABLE    (0x00U)    /* activation disabled (ELCL) */
#define _04_DTC_ELCL_ACTIVATION_ENABLE     (0x04U)    /* activation enabled (ELCL) */
/* DTC activation enable 41 (DTCEN41) */
#define _00_DTC_SMS_ACTIVATION_DISABLE     (0x00U)    /* activation disabled (SMS) */
#define _02_DTC_SMS_ACTIVATION_ENABLE      (0x02U)    /* activation enabled (SMS) */
/* DTC activation enable 40 (DTCEN40) */
#define _00_DTC_LVD_ACTIVATION_DISABLE     (0x00U)    /* activation disabled (LVD) */
#define _01_DTC_LVD_ACTIVATION_ENABLE      (0x01U)    /* activation enabled (LVD) */

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
