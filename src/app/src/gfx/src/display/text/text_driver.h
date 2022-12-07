/*
 * text_driver.h
 *
 *  Created on: 27 Jul 2022
 *      Author: a5126135
 */

#ifndef DISPLAY_TEXT_TEXT_DRIVER_H_
#define DISPLAY_TEXT_TEXT_DRIVER_H_

/* Include header(s) for the driver which MUST provide the following API:
 * - Set_pixel(uint16_t x, uint16_t y)
 * - Set_bgpixel(uint16_t x, uint16_t y)
 * - Set_colour(uint8_t const * const colour)
 * - Set_bgcolour(uint8_t const * const bg_colour)
 */

#include "st7735s.h"

#define Set_pixel(x,y)	{St7735s_set_pixel(x, y);}

#define Set_bgpixel(x,y)	{St7735s_set_bgpixel(x, y);}

#define Set_colour(colour)	{St7735s_set_colour(colour);}

#define Set_bgcolour(bg_colour)	{St7735s_set_bgcolour(bg_colour);}

#endif /* DISPLAY_TEXT_TEXT_DRIVER_H_ */
