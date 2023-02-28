/*
 * filter.h
 *
 *  Created on: 25 Feb 2023
 *      Author: a5126135
 */

#ifndef FILTER_H_
#define FILTER_H_

#include "r_smc_entry.h"
#include "Q1616.h"

/** @brief Median Filter depth*/
#define MEDIAN_FILTER_DEPTH     (3U)

/** Contains all data related to low pass filter*/
typedef struct
{
	uint16_t y_prev; /**< previous output*/
	Q1616_t coeff; /**< fixed point filter coefficient*/
}lpf_state_t;

/** Contains all data related to median filter*/
typedef struct
{
	uint16_t median_filter_array[MEDIAN_FILTER_DEPTH]; /**< Median filter sample array*/
	uint16_t median_filter_index; /**< Current index of median filters inputs*/
}mf_state_t;

/** Contains all data related to biquad filter*/
typedef struct
{
	Q1616_t feedback_data[2U]; /**< array to contain the previous output data*/
	Q1616_t input_data[3U]; /**< array to contain the input data samples*/

	/** Coefficients*/
	Q1616_t a1;
	Q1616_t a2;
	Q1616_t b0;
	Q1616_t b1;
	Q1616_t b2;
}bq_state_t;

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

/** @brief performs a biquad filter operation.
 * @param state - pointer to bq object.
 * @param data - data to operate on.
 * @return - filtered data.
 */
uint16_t Biquad_filter(bq_state_t * state, uint16_t data);

#endif /* FILTER_H_ */
