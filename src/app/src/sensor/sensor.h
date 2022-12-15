/*
 * sensor.h
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#ifndef APP_SENSOR_SENSOR_H_
#define APP_SENSOR_SENSOR_H_

#include <stdbool.h>
#include <stdint.h>

/* custom struct type for splitting decimal and integer portions of sensor readings*/
typedef struct
{
	int16_t integer_part;
	int16_t decimal_part;
}int_dec_t;

/** struct type for defining the sensor data*/
typedef struct
{
	int16_t temperature_int; /**< integer portion of the temperature*/
	int16_t humidity_int; /**< integer portion of the humidity*/
	int_dec_t iaq; /**< indoor air quality*/
	int_dec_t tvoc; /**< total volatile organic compounds*/
	int_dec_t eco2; /**< estimated carbon dioxide levels*/
	bool zmod_calibrated; /**< is the zmod calibrated*/
}sensor_data_t;

/** @brief Initiaises the sensors in the application*/
void Sensor_init(void);

/** @brief performs a read on the sensors in the application
 * @param[in,out] A pointer to the sensor data structure to be populated*/
void Sensor_read(sensor_data_t * const sense_data_arg);

/** @brief Adds the value y to x.
 * @param x - value changed.
 * @param y - values added to x.
 */
void Int_dec_add(int_dec_t * const x, int_dec_t const * const y);

/** @brief Checks if X > Y
 * @param x - value to compare
 * @param y - value to compare
 * @return true if X > Y, otherwise false.
 */
bool Int_dec_larger_than(int_dec_t * const x, int_dec_t const * const y);

#endif /* APP_SENSOR_SENSOR_H_ */