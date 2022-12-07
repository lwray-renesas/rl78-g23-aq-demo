/*
 * draw.h
 *
 *  Created on: 27 Jul 2022
 *      Author: a5126135
 */

#ifndef DISPLAY_DRAW_DRAW_H_
#define DISPLAY_DRAW_DRAW_H_

/** @brief Struct defining the line object*/
typedef struct
{
	uint16_t x0; /**< x0 - initial x*/
	uint16_t y0; /**< initial y*/
	uint16_t x1; /**< final x*/
	uint16_t y1; /**< final y*/
	uint16_t thickness; /**< thickness of the line*/
	const uint8_t * colour; /**< pointer to colour array for setting the colour using the driver*/
}line_t;


/** @brief Struct defining the parallel lines object*/
typedef struct
{
	uint16_t x0; /**< x0 - initial x*/
	uint16_t y0; /**< initial y*/
	uint16_t x1; /**< final x*/
	uint16_t y1; /**< final y*/
	uint16_t offset; /**< distance between the line described and the one parallel to it*/
	uint16_t thickness; /**< thickness of the lines*/
	const uint8_t * colour; /**< pointer to colour array for setting the colour using the driver*/
	const uint8_t * bgcolour; /**< pointer to colour array for setting the background colour using the driver (set to NULL if no background colouring is desired)*/
}parallel_lines_t;


/** @brief Struct defining the rectangle object*/
typedef struct
{
	uint16_t x0; /**< initial x of top line*/
	uint16_t y0; /**< initial y of top line*/
	uint16_t width; /**< width of the box (x direction)*/
	uint16_t height; /**< height of the box (y direction)*/
	uint16_t thickness; /**< thickness of the rectangles lines*/
	const uint8_t * colour; /**< pointer to colour array for setting the colour using the driver*/
	const uint8_t * bgcolour; /**< pointer to colour array for setting the background colour using the driver (set to NULL if no background colouring is desired)*/
}rectangle_t;


/** @brief Struct defining the solid rectangle object*/
typedef struct
{
	uint16_t x0; /**< initial x of top line*/
	uint16_t y0; /**< initial y of top line*/
	uint16_t width; /**< width of the box (x direction)*/
	uint16_t height; /**< height of the box (y direction)*/
	const uint8_t * colour; /**< pointer to colour array for setting the colour using the driver*/
}solid_rectangle_t;

/** @brief Struct defining the circle object*/
typedef struct
{
	uint16_t xc; /**< x coord of centre*/
	uint16_t yc; /**< y coord of centre*/
	uint16_t r; /**< radius of circle*/
	uint16_t thickness; /**< thickness of circle*/
	const uint8_t * colour; /**< pointer to colour array for setting the colour using the driver*/
	const uint8_t * bgcolour; /**< pointer to colour array for setting the background colour using the driver (set to NULL if no background colouring is desired)*/
}circle_t;

/** @brief sets the current x and y limits of the drawing library
 * @param x_max - maximum x coordinate.
 * @param y_max - maximum y coordinate.
 */
void Draw_init(uint16_t x_max, uint16_t y_max);

/**
 * @brief Draws a line in the display RAM (top left to bottom right --> 0,0 --> max,max).
 * @details Implementation ported from pseudo code on wikipedia: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm_for_integer_arithmetic
 * @param p_line_obj - pointer to a line object.
 */
void Draw_line(const line_t * const p_line_obj);

/**
 * @brief Draws two parallel lines in the display RAM (top left to bottom right --> 0,0 --> max,max)
 * @details Modified Implementation of the ported pseudo code on wikipedia: https://enwikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm_for_integer_arithmetic
 * @param p_plines_obj - pointer to a parallel lines object.
 */
void Draw_parallel_lines(const parallel_lines_t  * const p_plines_obj);

/**
 * @brief Draws a rectangle in the display ram - provided with the cordinates describing the rectangles top line + height.
 * @param p_rect_obj pointer to a rectangle object.
 */
void Draw_rectangle(const rectangle_t * const p_rect_obj);

/**
 * @brief Draws a solid rectangle in the display ram fast.
 * @param p_solid_rect_obj pointer to a rectangle object.
 */
void Draw_solid_rectangle(const solid_rectangle_t * const p_solid_rect_obj);

/**
 * @brief Draws a circle in the display ram.
 * @param p_circle_obj - pointer to a circle object.
 */
void Draw_circle(const circle_t  * const p_circle_obj);

#endif /* DISPLAY_DRAW_DRAW_H_ */
