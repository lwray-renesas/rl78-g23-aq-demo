/*
 * hw.h
 *
 *  Created on: 26 Oct 2022
 *      Author: a5126135
 */

#ifndef APP_HW_HW_H_
#define APP_HW_HW_H_

#include <stdint.h>
#include <stdbool.h>

/** @brief Initialises applications hardware - defaults the rotary to disabled*/
void Hw_init(void);

/** @brief Gets the current tracked rotary encoder count
 * @return integer count representing rotary encoder position (0 at power up, negative for anti-clockwise & positive for clockwise)*/
int16_t Hw_get_rotary_count(void);

/** @brief Starts the ELCL module providing a count source to the event counters*/
void Hw_start_rotary(void);

/** @brief Stops the ELCL module from providing a count source to the event counters*/
void Hw_stop_rotary(void);

/** @brief Checks if the button has been clicked since last check.
 * @return True if button has been clicked, false otherwise.*/
bool Hw_button_clicked(void);

/** @brief Checks if the button has been long pressed since last check.
 * @return True if button has been long pressed, false otherwise.*/
bool Hw_button_long_pressed(void);

#endif /* APP_HW_HW_H_ */
