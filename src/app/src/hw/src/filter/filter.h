/*
 * filter.h
 *
 *  Created on: 25 Feb 2023
 *      Author: a5126135
 */

#ifndef APP_SRC_HW_SRC_FILTER_FILTER_H_
#define APP_SRC_HW_SRC_FILTER_FILTER_H_

#include "r_smc_entry.h"

/** @brief Median Filter depth for CTSU*/
#define FILTERDEPTH     (3U)

/** Contains all data related to low pass filter*/
typedef struct
{
	uint16_t y_prev;
	uint16_t coeff;
}lpf_state_t;

/** Contains all data related to median filter*/
typedef struct
{
	uint16_t median_filter_array[FILTERDEPTH];
	uint16_t median_filter_index;
}mf_state_t;

/** Contains all data related to kalman filter*/
typedef struct
{
	uint16_t some_data;
}kf_state_t;

/** @brief Performs low pass filter.
 * @param[in] state - pointer to lpf object.
 * @param[in] data - data to operate on.
 * @return - filtered data.
 */
uint16_t Low_pass_filter(lpf_state_t * state, uint16_t data);

/** @brief performs a median filter operation.
 * @param state - pointer to mf object.
 * @param data - data to operate on.
 * @return - filtered data.
 */
uint16_t Median_filter(mf_state_t * state, uint16_t data);

/** @brief performs kalman filter operation on data set
 * @param state - pointer to mf object.
 * @param data - data to operate on.
 * @return - filtered data.
 */
uint16_t Kalman_filter(kf_state_t * state, uint16_t data);

#endif /* APP_SRC_HW_SRC_FILTER_FILTER_H_ */
