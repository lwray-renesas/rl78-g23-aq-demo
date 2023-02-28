/*
 * filter.c
 *
 *  Created on: 25 Feb 2023
 *      Author: a5126135
 */

#include "filter.h"
#include "Q1616.h"

uint16_t Low_pass_filter(lpf_state_t * state, uint16_t data)
{
	uint16_t y_cur = Q1616_to_uint16(Q1616_mul(Uint16_to_Q1616(state->y_prev), (q1616_one - state->coeff)) + Q1616_mul(Uint16_to_Q1616(data), state->coeff));

	state->y_prev = y_cur;

	return y_cur;
}
/* END OF FUNCTION*/

uint16_t Median_filter(mf_state_t * state, uint16_t data)
{
	uint16_t filter_data = 0U;
	uint16_t i = 0U;
	uint16_t j = 0U;

	state->median_filter_array[state->median_filter_index] = data;
	++state->median_filter_index;

	if(state->median_filter_index > MEDIAN_FILTER_DEPTH)
	{
		state->median_filter_index = 0U;
	}

	/* perform a simple bubble sort on the array*/
	for (i = 0U; i < MEDIAN_FILTER_DEPTH-1U; i++)
	{
		for (j = 0U; j < MEDIAN_FILTER_DEPTH-i-1U; j++)
		{
			if (state->median_filter_array[j] > state->median_filter_array[j+1U])
			{
				uint16_t temp = state->median_filter_array[j];
				state->median_filter_array[j] = state->median_filter_array[j+1U];
				state->median_filter_array[j+1U] = temp;
			}
		}
	}

	/* calculate median from sorted array. Pick middle value for faster processing
	 *  discover if filter depth is even or odd
	 */
#if ( (FILTERDEPTH % 2U) == 0 )
		filter_data = (uint16_t) (state->median_filter_array[(MEDIAN_FILTER_DEPTH-1U) >> 1U] + state->median_filter_array[MEDIAN_FILTER_DEPTH >> 1U]) >> 1U;
#else
		filter_data = state->median_filter_array[(MEDIAN_FILTER_DEPTH-1U) >> 1U];
#endif
		return filter_data;
}
/* END OF FUNCTION*/

uint16_t Biquad_filter(bq_state_t * state, uint16_t data)
{
	Q1616_t filter_data = 0UL;

	/* Shift inputs along*/
	state->input_data[2U] = state->input_data[1U];
	state->input_data[1U] = state->input_data[0U];
	state->input_data[0U] = Uint16_to_Q1616(data);

	/* Compute filter output*/
	filter_data = (Q1616_mul(state->b0, state->input_data[0U]) +
			Q1616_mul(state->b1, state->input_data[1U]) +
			Q1616_mul(state->b2, state->input_data[2U])) -
			(Q1616_mul(state->a1, state->feedback_data[0U]) +
			Q1616_mul(state->a2, state->feedback_data[1U]));

	/* Shift in feedback data*/
	state->feedback_data[1U] = state->feedback_data[0U];
	state->feedback_data[0U] = filter_data;

	return Q1616_to_uint16(filter_data);
}
/* END OF FUNCTION*/
