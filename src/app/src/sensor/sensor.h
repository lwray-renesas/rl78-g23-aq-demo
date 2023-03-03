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

/** @brief enumerated type for sensor read state*/
typedef enum
{
	SENSOR_WAITING = 0U, /**< Sensor waiting to be triggered*/
	SENSOR_START_MEASURMENT,
	SENSOR_WAIT_TO_READ,
}sensor_read_state_t;

/** @brief Initiaises the sensors in the application*/
void Sensor_init(void);

/** @brief performs a read on the sensors in the application
 * @details before this function does any processing - Sensor_try_trigger_read must be called to start the state machine.
 * @param[in,out] A pointer to the sensor data structure to be populated
 * @return true if reading completed on last call, false otherwise.*/
bool Sensor_read(sensor_data_t * const sense_data_arg);

/** @brief function which checks if the sensor state machine is in a safe stop to enter STOP mode.
 * @return true if it is safe, false otherwise.*/
bool Sensor_stop_safe(void);

/** @brief function which checks if the sensor state machine is ready to work*/
bool Sensor_state_machine_ready(void);

/** @brief function to attempt to start the state machine within Sensor_read function*/
void Sensor_try_trigger_read(void);

/** @brief Sensor callback tomindicate end of delay*/
void Sensor_oneshot_callback(void);

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
