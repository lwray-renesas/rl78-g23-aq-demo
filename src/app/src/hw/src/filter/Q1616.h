/*
 * Q1616.h
 *
 *  Created on: 27 Feb 2023
 *      Author: a5126135
 */

#ifndef Q1616_H_
#define Q1616_H_

#include <stdint.h>
#include <stdbool.h>

/** @brief defining the type for a 16bit integer 16bit decimal unsigned type*/
typedef uint32_t Q1616_t;

static const Q1616_t q1616_one = 0x00010000UL;

/** @brief converts i.d format number to Q1616 format e.g. 1.1234 = Q1616(1,1234)
 * Limitation - d only works up to 99,999*/
#define Q1616(i,d) ( (Q1616_t) ( (Q1616_t)(i) * 0x00010000 ) + ( ((Q1616_t)(d) * 65536U) / ( \
		((d) < 10) ? (10) : \
				((d) < 100) ? (100) : \
						((d) < 1000) ? (1000) : \
								((d) < 10000) ? (10000) : (100000) ) ) )

/**@brief convert 16bit unsigned integer to Q1616
 * @param x - number to convert
 * @return uint16 versionn of number*/
static inline Q1616_t Uint16_to_Q1616(uint16_t x)
{
	return (Q1616_t) x * q1616_one;
}
/* END OF FUNCTION*/

/**@brief convert Q1616 to 16bit unsigned integer
 * @param x - number to convert
 * @return uint16 versionn of number*/
static inline uint16_t Q1616_to_uint16(Q1616_t x)
{
	Q1616_t temp = x >> 16;

	if( (x & 0x00008000U) > 0U )
	{
		temp += 1U;
	}

	return (uint16_t)temp;
}
/* END OF FUNCTION*/


/** @brief x * y
 * @param x - first parameter
 * @param y - second parameter
 * @return result of multiplication
 */
static inline Q1616_t Q1616_mul(Q1616_t x, Q1616_t y)
{
	return (Q1616_t) (((uint64_t) x * (uint64_t) y) >> 16);
}
/* END OF FUNCTION*/


/** @brief dividend / divisor
 * @param dividend - the number being divided  up
 * @param divisor - the number we are dividing by
 * @return result of division
 */
static inline Q1616_t Q1616_div(Q1616_t dividend, Q1616_t divisor)
{
	return ((uint64_t)(dividend) << 16)/(uint64_t)(divisor);
}
/* END OF FUNCTION*/

#endif /* Q1616_H_ */
