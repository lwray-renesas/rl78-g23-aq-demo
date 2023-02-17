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

/**
 * @file   zmod4410_config_odor.h
 * @brief  This is the configuration for zmod4410 module using the odor algorithm.
 * @author Renesas Electronics Corporation
 * @version 2.1.2
 */

#ifndef _ZMOD4410_CONFIG_ODOR_H
#define _ZMOD4410_CONFIG_ODOR_H

#include <stdio.h>
#include "../zmod4xxx_types.h"

#define ZMOD4410_H_ADDR           0x40
#define ZMOD4410_D_ADDR           0x50
#define ZMOD4410_M_ADDR           0x60
#define ZMOD4410_S_ADDR           0x68

#define ZMOD4410_PROD_DATA_LEN    6

static uint8_t data_set_4410i[] =
{
    0x00, 0x50,
    0x00, 0x28,0xC3,  0xE3,
    0x00, 0x00,0x80,  0x40
};

static uint8_t data_set_4410_cont[] =
{
    0xFD, 0xA8,
    0x20, 0x04,0x20,  0x04,
    0x03,
    0x00, 0x00,0x80,  0x08
};

zmod4xxx_conf g_zmod4410_odor_sensor_type[] =
{
    {
        .start = 0x80,
        .h     = {.addr = ZMOD4410_H_ADDR, .len = 2, .data_buf = &data_set_4410i[0]    },
        .d     = {.addr = ZMOD4410_D_ADDR, .len = 2, .data_buf = &data_set_4410i[2]    },
        .m     = {.addr = ZMOD4410_M_ADDR, .len = 2, .data_buf = &data_set_4410i[4]    },
        .s     = {.addr = ZMOD4410_S_ADDR, .len = 4, .data_buf = &data_set_4410i[6]    },
        .r     = {.addr = 0x97,            .len = 4},
    },

    {
        .start         = 0xC0,
        .h             = {.addr = ZMOD4410_H_ADDR, .len = 2, .data_buf = &data_set_4410_cont[0]},
        .d             = {.addr = ZMOD4410_D_ADDR, .len = 4, .data_buf = &data_set_4410_cont[2]},
        .m             = {.addr = ZMOD4410_M_ADDR, .len = 1, .data_buf = &data_set_4410_cont[6]},
        .s             = {.addr = ZMOD4410_S_ADDR, .len = 4, .data_buf = &data_set_4410_cont[7]},
        .r             = {.addr = 0x99,    .len = 2},
        .prod_data_len = ZMOD4410_PROD_DATA_LEN,
    }
};

#endif                                 // _ZMOD4410_CONFIG_ODOR_H
