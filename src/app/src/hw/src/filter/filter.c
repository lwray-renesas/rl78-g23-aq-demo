/*
 * filter.c
 *
 *  Created on: 25 Feb 2023
 *      Author: a5126135
 */

#include "filter.h"

/** @brief swaps data at xp with data at yp
 * @param xp - data X
 * @param yp - data Y
 */
static void Swap(uint16_t *xp, uint16_t *yp);

/** @brief Performs bubble sort on data of size n
 * @param array - aray of data to sort.
 * @param n - size of array
 */
static void Bubble_sort(uint16_t * array, uint16_t n);

uint16_t Low_pass_filter(lpf_state_t * state, uint16_t data)
{
	uint32_t y_cur_32 = (((uint32_t)state->y_prev * (0x0000FFFFUL - (uint32_t)state->coeff)) + ((uint32_t)data * state->coeff)) >> 16U;

	state->y_prev = (uint16_t)y_cur_32;

	return (uint16_t)y_cur_32;
}
/* END OF FUNCTION*/

uint16_t Median_filter(mf_state_t * state, uint16_t data)
{
	uint16_t filter_data = 0U;

	state->median_filter_array[state->median_filter_index] = data;
	++state->median_filter_index;

	if(state->median_filter_index > FILTERDEPTH)
	{
		state->median_filter_index = 0U;
	}

	/* perform a simple bubble sort on the array*/
	Bubble_sort(state->median_filter_array, FILTERDEPTH);

	/* calculate median from sorted array. Pick middle value for faster processing
	 *  discover if filter depth is even or odd
	 */
#if ( (FILTERDEPTH % 2U) == 0 )
		filter_data = (uint16_t) (state->median_filter_array[(FILTERDEPTH-1U) >> 1U] + state->median_filter_array[FILTERDEPTH >> 1U]) >> 1U;
#else
		filter_data = state->median_filter_array[(FILTERDEPTH-1U) >> 1U];
#endif
		return filter_data;
}
/* END OF FUNCTION*/

uint16_t Kalman_filter(kf_state_t * state, uint16_t data)
{
	uint16_t prediction = data;

	(void)state;

	return prediction;
}
/* END OF FUNCTION*/


static void Swap(uint16_t *xp, uint16_t *yp)
{
	uint16_t temp = *xp;
	*xp = *yp;
	*yp = temp;
}
/* END OF FUNCTION*/

static void Bubble_sort(uint16_t * array, uint16_t n)
{
	uint16_t i = 0U;
	uint16_t j = 0U;

	for (i = 0U; i < n-1U; i++)
	{
		for (j = 0U; j < n-i-1U; j++)
		{
			if (array[j] > array[j+1U])
			{
				Swap(&array[j], &array[j+1U]);
			}
		}
	}
}
/* END OF FUNCTION*/
