/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
* THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
************************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup CTSU_API CTSU Interface
 * @brief Interface for Capacitive Touch Sensing Unit (CTSU) functions.
 *
 * @section CTSU_API_Summary Summary
 * The CTSU interface provides CTSU functionality.
 *
 * The CTSU interface can be implemented by:
 * - @ref CTSU
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_CTSU_API_H
#define R_CTSU_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "platform.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CTSU_COUNT_MAX                      (0xFFFF)

#define CTSU_TARGET_VALUE_CONFIG_SUPPORT    (1)

#define CTSU_SUCCESS FSP_SUCCESS

#ifndef FSP_ERR_CTSU_SCANNING
 #define FSP_ERR_CTSU_SCANNING               (fsp_err_t)(6000)  ///< Scanning.
#endif
#ifndef FSP_ERR_CTSU_NOT_GET_DATA
 #define FSP_ERR_CTSU_NOT_GET_DATA           (fsp_err_t)(6001)  ///< Not processed previous scan data.
#endif
#ifndef FSP_ERR_CTSU_INCOMPLETE_TUNING
 #define FSP_ERR_CTSU_INCOMPLETE_TUNING      (fsp_err_t)(6002)  ///< Incomplete initial offset tuning.
#endif
#ifndef FSP_ERR_CTSU_DIAG_NOT_YET
 #define FSP_ERR_CTSU_DIAG_NOT_YET           (fsp_err_t)(6003)  ///< Diagnosis of data collected no yet.
#endif
#ifndef FSP_ERR_CTSU_DIAG_OUTPUT_VOLTAGE
 #define FSP_ERR_CTSU_DIAG_OUTPUT_VOLTAGE    (fsp_err_t)(6009)  ///< Diagnosis of LDO output voltage failed.
#endif
#ifndef FSP_ERR_CTSU_DIAG_OVER_VOLTAGE
 #define FSP_ERR_CTSU_DIAG_OVER_VOLTAGE      (fsp_err_t)(6010)  ///< Diagnosis of over voltage detection circuit failed.
#endif
#ifndef FSP_ERR_CTSU_DIAG_OVER_CURRENT
 #define FSP_ERR_CTSU_DIAG_OVER_CURRENT      (fsp_err_t)(6011)  ///< Diagnosis of over current detection circuit failed.
#endif
#ifndef FSP_ERR_CTSU_DIAG_LOAD_RESISTANCE
 #define FSP_ERR_CTSU_DIAG_LOAD_RESISTANCE   (fsp_err_t)(6012)  ///< Diagnosis of LDO internal resistance value failed.
#endif
#ifndef FSP_ERR_CTSU_DIAG_CURRENT_SOURCE
 #define FSP_ERR_CTSU_DIAG_CURRENT_SOURCE    (fsp_err_t)(6013)  ///< Diagnosis of LDO internal resistance value failed.
#endif
#ifndef FSP_ERR_CTSU_DIAG_SENSCLK_GAIN
 #define FSP_ERR_CTSU_DIAG_SENSCLK_GAIN      (fsp_err_t)(6014)  ///< Diagnosis of SENSCLK frequency gain failed.
#endif
#ifndef FSP_ERR_CTSU_DIAG_SUCLK_GAIN
 #define FSP_ERR_CTSU_DIAG_SUCLK_GAIN        (fsp_err_t)(6015)  ///< Diagnosis of SUCLK frequency gain failed.
#endif
#ifndef FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY
 #define FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY    (fsp_err_t)(6016)  ///< Diagnosis of SUCLK clock recovery function failed.
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef fsp_err_t ctsu_err_t;

/** CTSU Events for callback function */
typedef enum e_ctsu_event
{
    CTSU_EVENT_SCAN_COMPLETE = 0x00,   ///< Normal end
    CTSU_EVENT_OVERFLOW      = 0x01,   ///< Sensor counter overflow (CTSUST.CTSUSOVF set)
    CTSU_EVENT_ICOMP         = 0x02,   ///< Abnormal TSCAP voltage (CTSUERRS.CTSUICOMP set)
    CTSU_EVENT_ICOMP1        = 0x04    ///< Abnormal sensor current (CTSUSR.ICOMP1 set)
} ctsu_event_t;

/** CTSU Scan Start Trigger Select */
typedef enum e_ctsu_cap
{
    CTSU_CAP_SOFTWARE,                 ///< Scan start by software trigger
    CTSU_CAP_EXTERNAL                  ///< Scan start by external trigger
} ctsu_cap_t;

/** CTSU Transmission Power Supply Select */
typedef enum e_ctsu_txvsel
{
    CTSU_TXVSEL_VCC,                   ///< VCC selected
    CTSU_TXVSEL_INTERNAL_POWER         ///< Internal logic power supply selected
} ctsu_txvsel_t;

/** CTSU Transmission Power Supply Select 2 (CTSU2 Only) */
typedef enum e_ctsu_txvsel2
{
    CTSU_TXVSEL_MODE,                  ///< Follow TXVSEL setting
    CTSU_TXVSEL_VCC_PRIVATE,           ///< VCC private selected
} ctsu_txvsel2_t;

/** CTSU Power Supply Capacity Adjustment (CTSU Only) */
typedef enum e_ctsu_atune1
{
    CTSU_ATUNE1_NORMAL,                ///< Normal output (40uA)
    CTSU_ATUNE1_HIGH                   ///< High-current output (80uA)
} ctsu_atune1_t;
/** CTSU Power Supply Capacity Adjustment (CTSU2 Only) */
typedef enum e_ctsu_atune12
{
    CTSU_ATUNE12_80UA,                 ///< High-current output (80uA)
    CTSU_ATUNE12_40UA,                 ///< Normal output (40uA)
    CTSU_ATUNE12_20UA,                 ///< Low-current output (20uA)
    CTSU_ATUNE12_160UA                 ///< Very high-current output (160uA)
} ctsu_atune12_t;

/** CTSU Measurement Mode Select */
typedef enum e_ctsu_mode
{
    CTSU_MODE_SELF_MULTI_SCAN  = 1,    ///< Self-capacitance multi scan mode
    CTSU_MODE_MUTUAL_FULL_SCAN = 3,    ///< Mutual capacitance full scan mode
    CTSU_MODE_MUTUAL_CFC_SCAN  = 7,    ///< Mutual capacitance cfc scan mode (CTSU2 Only)
    CTSU_MODE_CURRENT_SCAN     = 9,    ///< Current scan mode (CTSU2 Only)
    CTSU_MODE_CORRECTION_SCAN  = 17,   ///< Correction scan mode (CTSU2 Only)
    CTSU_MODE_DIAGNOSIS_SCAN   = 33    ///< Diagnosis scan mode
} ctsu_md_t;

/** CTSU Non-Measured Channel Output Select (CTSU2 Only) */
typedef enum e_ctsu_posel
{
    CTSU_POSEL_LOW_GPIO,               ///< Output low through GPIO
    CTSU_POSEL_HI_Z,                   ///< Hi-Z
    CTSU_POSEL_LOW,                    ///< Setting prohibited
    CTSU_POSEL_SAME_PULSE              ///< Same phase pulse output as transmission channel through the power setting by the TXVSEL[1:0] bits
} ctsu_posel_t;

/** CTSU Spectrum Diffusion Frequency Division Setting (CTSU Only) */
typedef enum e_ctsu_ssdiv
{
    CTSU_SSDIV_4000,                   ///< 4.00 <= Base clock frequency (MHz)
    CTSU_SSDIV_2000,                   ///< 2.00 <= Base clock frequency (MHz) < 4.00
    CTSU_SSDIV_1330,                   ///< 1.33 <= Base clock frequency (MHz) < 2.00
    CTSU_SSDIV_1000,                   ///< 1.00 <= Base clock frequency (MHz) < 1.33
    CTSU_SSDIV_0800,                   ///< 0.80 <= Base clock frequency (MHz) < 1.00
    CTSU_SSDIV_0670,                   ///< 0.67 <= Base clock frequency (MHz) < 0.80
    CTSU_SSDIV_0570,                   ///< 0.57 <= Base clock frequency (MHz) < 0.67
    CTSU_SSDIV_0500,                   ///< 0.50 <= Base clock frequency (MHz) < 0.57
    CTSU_SSDIV_0440,                   ///< 0.44 <= Base clock frequency (MHz) < 0.50
    CTSU_SSDIV_0400,                   ///< 0.40 <= Base clock frequency (MHz) < 0.44
    CTSU_SSDIV_0360,                   ///< 0.36 <= Base clock frequency (MHz) < 0.40
    CTSU_SSDIV_0330,                   ///< 0.33 <= Base clock frequency (MHz) < 0.36
    CTSU_SSDIV_0310,                   ///< 0.31 <= Base clock frequency (MHz) < 0.33
    CTSU_SSDIV_0290,                   ///< 0.29 <= Base clock frequency (MHz) < 0.31
    CTSU_SSDIV_0270,                   ///< 0.27 <= Base clock frequency (MHz) < 0.29
    CTSU_SSDIV_0000                    ///< 0.00 <= Base clock frequency (MHz) < 0.27
} ctsu_ssdiv_t;

/** CTSU select data type for slect data get */
typedef enum e_ctsu_specific_data_type
{
    CTSU_SPECIFIC_RAW_DATA,
    CTSU_SPECIFIC_CORRECTION_DATA,
    CTSU_SPECIFIC_SELECTED_FREQ,
} ctsu_specific_data_type_t;

/** Callback function parameter data */
typedef struct st_ctsu_callback_args
{
    ctsu_event_t event;                ///< The event can be used to identify what caused the callback.
    void const * p_context;            ///< Placeholder for user data. Set in ctsu_api_t::open function in ::ctsu_cfg_t.
} ctsu_callback_args_t;

/** CTSU Control block. Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - ctsu_instance_ctrl_t
 */
typedef void ctsu_ctrl_t;

/** CTSU Configuration parameters. */
/** Element Configuration */
typedef struct st_ctsu_element
{
    ctsu_ssdiv_t ssdiv;                ///< CTSU Spectrum Diffusion Frequency Division Setting (CTSU Only)
    uint16_t     so;                   ///< CTSU Sensor Offset Adjustment
    uint8_t      snum;                 ///< CTSU Measurement Count Setting
    uint8_t      sdpa;                 ///< CTSU Base Clock Setting
} ctsu_element_cfg_t;

/** User configuration structure, used in open function */
typedef struct st_ctsu_cfg
{
    ctsu_cap_t                 cap;                     ///< CTSU Scan Start Trigger Select
    ctsu_txvsel_t              txvsel;                  ///< CTSU Transmission Power Supply Select
    ctsu_txvsel2_t             txvsel2;                 ///< CTSU Transmission Power Supply Select 2 (CTSU2 Only)
    ctsu_atune1_t              atune1;                  ///< CTSU Power Supply Capacity Adjustment (CTSU Only)
    ctsu_atune12_t             atune12;                 ///< CTSU Power Supply Capacity Adjustment (CTSU2 Only)
    ctsu_md_t                  md;                      ///< CTSU Measurement Mode Select
    ctsu_posel_t               posel;                   ///< CTSU Non-Measured Channel Output Select (CTSU2 Only)
    uint8_t                    tsod;                    ///< TS all terminal output control for multi electrode scan
    uint8_t                    mec_ts;                  ///< TS number used when using the MEC function
    uint8_t                    mec_shield_ts;           ///< TS number of active shield used when using MEC function
    uint8_t                    ctsuchac0;               ///< TS00-TS07 enable mask
    uint8_t                    ctsuchac1;               ///< TS08-TS15 enable mask
    uint8_t                    ctsuchac2;               ///< TS16-TS23 enable mask
    uint8_t                    ctsuchac3;               ///< TS24-TS31 enable mask
    uint8_t                    ctsuchac4;               ///< TS32-TS39 enable mask
    uint8_t                    ctsuchtrc0;              ///< TS00-TS07 mutual-tx mask
    uint8_t                    ctsuchtrc1;              ///< TS08-TS15 mutual-tx mask
    uint8_t                    ctsuchtrc2;              ///< TS16-TS23 mutual-tx mask
    uint8_t                    ctsuchtrc3;              ///< TS24-TS31 mutual-tx mask
    uint8_t                    ctsuchtrc4;              ///< TS32-TS39 mutual-tx mask
    ctsu_element_cfg_t const * p_elements;              ///< Pointer to elements configuration array
    uint8_t                    num_rx;                  ///< Number of receive terminals
    uint8_t                    num_tx;                  ///< Number of transmit terminals
    uint16_t                   num_moving_average;      ///< Number of moving average for measurement data
    uint8_t                    tunning_enable;          ///< Initial offset tuning flag
    void (* p_callback)(ctsu_callback_args_t * p_args); ///< Callback provided when CTSUFN ISR occurs.
    void const * p_context;                             ///< User defined context passed into callback function.
    void const * p_extend;                              ///< Pointer to extended configuration by instance of interface.
    uint16_t     tuning_self_target_value;              ///< Target self value for initial offset tuning
    uint16_t     tuning_mutual_target_value;            ///< Target mutual value for initial offset tuning
} ctsu_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ctsu_api
{
    /** Open driver.
     * @par Implemented as
     * - @ref R_CTSU_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ctsu_ctrl_t * const p_ctrl, ctsu_cfg_t const * const p_cfg);

    /** Scan start.
     * @par Implemented as
     * - @ref R_CTSU_ScanStart()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* scanStart)(ctsu_ctrl_t * const p_ctrl);

    /** Data get.
     * @par Implemented as
     * - @ref R_CTSU_DataGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_data       Pointer to get data array.
     */
    fsp_err_t (* dataGet)(ctsu_ctrl_t * const p_ctrl, uint16_t * p_data);

    /** ScanStop.
     * @par Implemented as
     * - @ref R_CTSU_ScanStop()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* scanStop)(ctsu_ctrl_t * const p_ctrl);

    /** Diagnosis.
     * @par Implemented as
     * - @ref R_CTSU_Diagnosis()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* diagnosis)(ctsu_ctrl_t * const p_ctrl);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_CTSU_CallbackSet()
     *
     * @param[in]   p_ctrl                   Pointer to the CTSU control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(ctsu_ctrl_t * const p_api_ctrl, void (* p_callback)(ctsu_callback_args_t *),
                              void const * const p_context, ctsu_callback_args_t * const p_callback_memory);

    /** SMS set.
     * @par Implemented as
     * - @ref R_CTSU_SmsSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_threshold  Pointer to threshold array.
     * @param[in]  p_hysteresis Pointer to hysteresis array.
     * @param[in]  count_filter Value of ON/OFF count filter.
     */
    fsp_err_t (* smsSet)(ctsu_ctrl_t * const p_ctrl, uint16_t * p_threshold,
                         uint16_t * p_hysteresis, uint16_t count_filter);

    /** Close driver.
     * @par Implemented as
     * - @ref R_CTSU_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ctsu_ctrl_t * const p_ctrl);

    /** Specific Data get.
     * @par Implemented as
     * - @ref R_CTSU_SpecificDataGet()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[out] p_specific_data     Pointer to get specific data array.
     * @param[in]  specific_data_type  Specific data type
     */
    fsp_err_t (* specificDataGet)(ctsu_ctrl_t * const p_ctrl, uint16_t * p_specific_data,
                                  ctsu_specific_data_type_t specific_data_type);

    /** Data Insert.
     * @par Implemented as
     * - @ref R_CTSU_DataInsert()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[in]  p_insert_data       Pointer to insert data.
     */
    fsp_err_t (* dataInsert)(ctsu_ctrl_t * const p_ctrl, uint16_t * p_insert_data);

    /** Adjust the offset value to tune the sensor.
     * @par Implemented as
     * - @ref R_CTSU_OffsetTuning()
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     */
    fsp_err_t (* offsetTuning)(ctsu_ctrl_t * const p_ctrl);

} ctsu_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ctsu_instance
{
    ctsu_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    ctsu_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    ctsu_api_t const * p_api;          ///< Pointer to the API structure for this instance
} ctsu_instance_t;

#endif                                 /* R_CTSU_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup CTSU_API)
 **********************************************************************************************************************/
