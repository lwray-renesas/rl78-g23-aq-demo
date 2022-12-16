/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/* Guards against multiple inclusion */
#ifndef RM_HS300X_COMMON_H
#define RM_HS300X_COMMON_H

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
* Macro definitions
 *********************************************************************************************************************/
/* NOP(Assembler) */
#if defined(__CCRL__)
#define	BSP_NOP()           __nop()                     /* NOP命令 */
#elif defined(__ICCRL78__)
#define BSP_NOP     (__no_operation)
#endif

#define HS300X_CFG_FMX_HZ   (20000000) // Main clock frequency
#define HS300X_CFG_FIH_HZ   (32000000) // On-chip oscillator frequency
#define HS300X_SUB_CLOCK_HZ (32768)    // Sub clock frequency

/* Available delay units. */
// ★
// RXから流用のまま、BSP_DELAY_MICROSECS = 1000000 を
// enum 定義に使用すると、intのキャパオーバーでコンパイルエラーになる。
// よって、このenumから、別の配列を参照して、1000000/1000/1 の時間を取得することとする。
typedef enum
{
    HS300X_DELAY_SECS = 0,              // Requested delay amount is in seconds
    HS300X_DELAY_MILLISECS,             // Requested delay amount is in milliseconds
    HS300X_DELAY_MICROSECS              // Requested delay amount is in microseconds
} hs300x_delay_units_t;

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
// ★
// R_BSP_SoftwareDelay()の戻り値は、RXでは、bool を使用しているが、
// CCRL ではコンパイラバージョンにより、コンパイルエラーになってしまう。
// とりあえずは環境によらず、コンパイルできる uint8_t に変更している。
uint8_t R_HS300X_SoftwareDelay(uint32_t delay, hs300x_delay_units_t units);

#endif	// #define RM_HS300X_COMMON_H
