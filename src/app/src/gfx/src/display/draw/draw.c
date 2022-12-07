/*
 * draw.c
 *
 *  Created on: 27 Jul 2022
 *      Author: a5126135
 */

#include "draw_driver.h"
#include "draw.h"
#include  "stddef.h"
#include "display_assert.h"

static uint16_t max_x = 0U;
static uint16_t max_y = 0U;

/**
 * @brief Forms parts of the bresenham line drawing algorithm.
 * @param x0 - initial x.
 * @param y0 - initial y.
 * @param x1 - final x.
 * @param y1 - final y.
 * @param dx - x1-x0.
 * @param dy - y1-y0.
 * @param thickness - thickness of line to be drawn.
 */
static void Plot_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, int16_t dx, int16_t dy, uint16_t thickness)
{
	int16_t yi = 1;

	if(dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	int16_t D = (2*dy) - dx;
	int16_t y = y0;

	for (uint16_t x = x0; x < x1; ++x)
	{
		/* Thickness control*/
		for(uint16_t pad = 0U; pad < thickness; ++pad)
		{
			Set_pixel(x, (uint16_t)(y)+pad);
		}

		if(D > 0)
		{
			y = y + yi;
			D = D + (2*(dy - (int16_t)(dx)));
		}
		else
		{
			D = D + 2*dy;
		}
	}
}
/* END OF FUNCTION*/

/**
 * @brief Forms parts of the bresenham line drawing algorithm.
 * @param x0 - initial x.
 * @param y0 - initial y.
 * @param x1 - final x.
 * @param y1 - final y.
 * @param dx - x1-x0.
 * @param dy - y1-y0.
 * @param thickness - thickness of line to be drawn.
 */
static void Plot_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, int16_t dx, int16_t dy, uint16_t thickness)
{
	int16_t xi = 1;

	if(dx < 0)
	{
		xi = -1;
		dx = -dx;
	}

	int16_t D = (2*dx) - dy;
	int16_t x = x0;

	for (uint16_t y = y0; y < y1; ++y)
	{
		/* Thickness control*/
		for(uint16_t pad = 0U; pad < thickness; ++pad)
		{
			Set_pixel((uint16_t)(x)+pad, y);
		}

		if(D > 0)
		{
			x = x + xi;
			D = D + (2*(dx - dy));
		}
		else
		{
			D = D + 2*dx;
		}
	}
}
/* END OF FUNCTION*/

void Draw_init(uint16_t x_max, uint16_t y_max)
{
	max_x = x_max;
	max_y = y_max;
}
/* END OF FUNCTION*/

void Draw_line(const line_t * const p_line_obj)
{
	DISPLAY_ASSERT_VOID((p_line_obj->x0 < max_x) && (p_line_obj->x1 < max_x) &&
			(p_line_obj->y0 < max_y) && (p_line_obj->y1 < max_y));

	uint16_t dy = (p_line_obj->y0>p_line_obj->y1) ? p_line_obj->y0 - p_line_obj->y1 : p_line_obj->y1 - p_line_obj->y0;
	uint16_t dx = (p_line_obj->x0>p_line_obj->x1) ? p_line_obj->x0 - p_line_obj->x1 : p_line_obj->x1 - p_line_obj->x0;
	bool rev_inputs = (p_line_obj->y0>p_line_obj->y1) || (p_line_obj->x0>p_line_obj->x1);

	Set_colour(p_line_obj->colour);

	if(dy < dx)
	{
		DISPLAY_ASSERT_VOID(((p_line_obj->y0 + p_line_obj->thickness) < max_y) && ((p_line_obj->y1 + p_line_obj->thickness) < max_y));

		if(rev_inputs)
		{
			Plot_line_low(p_line_obj->x1, p_line_obj->y1, p_line_obj->x0, p_line_obj->y0, dx, dy, p_line_obj->thickness);
		}
		else
		{
			Plot_line_low(p_line_obj->x0, p_line_obj->y0, p_line_obj->x1, p_line_obj->y1, dx, dy, p_line_obj->thickness);
		}
	}
	else
	{
		DISPLAY_ASSERT_VOID(((p_line_obj->x0 + p_line_obj->thickness) < max_x) && ((p_line_obj->x1 + p_line_obj->thickness) < max_x));

		if(rev_inputs)
		{
			Plot_line_high(p_line_obj->x1, p_line_obj->y1, p_line_obj->x0, p_line_obj->y0, dx, dy, p_line_obj->thickness);
		}
		else
		{
			Plot_line_high(p_line_obj->x0, p_line_obj->y0, p_line_obj->x1, p_line_obj->y1, dx, dy, p_line_obj->thickness);
		}
	}
}
/* END OF FUNCTION*/

/**
 * @brief Forms parts of the modified bresenham line drawing algorithm to draw two parallel lines.
 * @param x0 - initial x.
 * @param y0 - initial y.
 * @param x1 - final x.
 * @param y1 - final y.
 * @param dx - x1-x0.
 * @param dy - y1-y0.
 * @param offset - distance between described line and parallel one.
 * @param thickness - thickness of line to be drawn.
 * @param setbg - flag if true - set background fill pixels, otherwise do not.
 */
static void Plot_parallel_lines_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, int16_t dx, int16_t dy, uint16_t offset, uint16_t thickness, bool setbg)
{
	int16_t yi = 1;

	if(dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	int16_t D = (2*dy) - dx;
	int16_t y = y0;

	for (uint16_t x = x0; x < x1; ++x)
	{
		/* Thickness control*/
		for(uint16_t pad = 0U; pad < thickness; ++pad)
		{
			Set_pixel(x, (uint16_t)(y)+pad);
			Set_pixel(x, (uint16_t)(y)+offset-pad);
		}

		if(setbg)
		{
			/* Colour in*/
			for(uint16_t ybg = (uint16_t)(y)+thickness; ybg < ((uint16_t)(y)+offset-thickness+1U); ++ybg)
			{
				Set_bgpixel(x, ybg);
			}
		}

		if(D > 0)
		{
			y = y + yi;
			D = D + (2*(dy - (int16_t)(dx)));
		}
		else
		{
			D = D + 2*dy;
		}
	}
}
/* END OF FUNCTION*/

/**
 * @brief Forms parts of the modified bresenham line drawing algorithm to draw two parallel lines.
 * @param x0 - initial x.
 * @param y0 - initial y.
 * @param x1 - final x.
 * @param y1 - final y.
 * @param dx - x1-x0.
 * @param dy - y1-y0.
 * @param offset - distance between described line and parallel one.
 * @param thickness - thickness of line to be drawn.
 * @param setbg - flag if true - set background fill pixels, otherwise do not.
 */
static void Plot_parallel_lines_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, int16_t dx, int16_t dy, uint16_t offset, uint16_t thickness, bool setbg)
{
	int16_t xi = 1;

	if(dx < 0)
	{
		xi = -1;
		dx = -dx;
	}

	int16_t D = (2*dx) - dy;
	int16_t x = x0;

	for (uint16_t y = y0; y < y1; ++y)
	{
		/* Thickness control*/
		for(uint16_t pad = 0U; pad < thickness; ++pad)
		{
			Set_pixel((uint16_t)(x)+pad, y);
			Set_pixel((uint16_t)(x)+offset-pad, y);
		}

		if(setbg)
		{
			/* Colour in*/
			for(uint16_t xbg = (uint16_t)(x)+thickness; xbg < ((uint16_t)(x)+offset-thickness+1U); ++xbg)
			{
				Set_bgpixel(xbg, y);
			}
		}

		if(D > 0)
		{
			x = x + xi;
			D = D + (2*(dx - dy));
		}
		else
		{
			D = D + 2*dx;
		}
	}
}
/* END OF FUNCTION*/

void Draw_parallel_lines(const parallel_lines_t * const p_plines_obj)
{
	DISPLAY_ASSERT_VOID((p_plines_obj->x0 < max_x) && (p_plines_obj->x1 < max_x) &&
			(p_plines_obj->y0 < max_y) && (p_plines_obj->y1 < max_y));

	uint16_t dy = (p_plines_obj->y0>p_plines_obj->y1) ? p_plines_obj->y0 - p_plines_obj->y1 : p_plines_obj->y1 - p_plines_obj->y0;
	uint16_t dx = (p_plines_obj->x0>p_plines_obj->x1) ? p_plines_obj->x0 - p_plines_obj->x1 : p_plines_obj->x1 - p_plines_obj->x0;
	bool rev_inputs = (p_plines_obj->y0>p_plines_obj->y1) || (p_plines_obj->x0>p_plines_obj->x1);
	bool setbg = (NULL != p_plines_obj->bgcolour);

	Set_colour(p_plines_obj->colour);

	if(setbg)
	{
		Set_bgcolour(p_plines_obj->bgcolour);
	}

	if(dy < dx)
	{
		DISPLAY_ASSERT_VOID(((p_plines_obj->y0 + p_plines_obj->offset) < max_y) && ((p_plines_obj->y1 + p_plines_obj->offset) < max_y));

		if(rev_inputs)
		{
			Plot_parallel_lines_low(p_plines_obj->x1, p_plines_obj->y1, p_plines_obj->x0, p_plines_obj->y0, dx, dy, p_plines_obj->offset, p_plines_obj->thickness, setbg);
		}
		else
		{
			Plot_parallel_lines_low(p_plines_obj->x0, p_plines_obj->y0, p_plines_obj->x1, p_plines_obj->y1, dx, dy, p_plines_obj->offset, p_plines_obj->thickness, setbg);
		}
	}
	else
	{
		DISPLAY_ASSERT_VOID(((p_plines_obj->x0 + p_plines_obj->offset) < max_x) && ((p_plines_obj->x1 + p_plines_obj->offset) < max_x));

		if(rev_inputs)
		{
			Plot_parallel_lines_high(p_plines_obj->x1, p_plines_obj->y1, p_plines_obj->x0, p_plines_obj->y0, dx, dy, p_plines_obj->offset, p_plines_obj->thickness, setbg);
		}
		else
		{
			Plot_parallel_lines_high(p_plines_obj->x0, p_plines_obj->y0, p_plines_obj->x1, p_plines_obj->y1, dx, dy, p_plines_obj->offset, p_plines_obj->thickness, setbg);
		}
	}
}
/* END OF FUNCTION*/

void Draw_rectangle(const rectangle_t * const p_rect_obj)
{
	static parallel_lines_t first_lines;
	static parallel_lines_t second_lines;

	first_lines.x0 = p_rect_obj->x0;
	first_lines.y0 = p_rect_obj->y0;
	first_lines.x1 = p_rect_obj->x0+p_rect_obj->width;
	first_lines.y1 = p_rect_obj->y0;
	first_lines.offset = p_rect_obj->height;
	first_lines.colour = p_rect_obj->colour;
	first_lines.bgcolour = p_rect_obj->bgcolour;
	first_lines.thickness = p_rect_obj->thickness;

	second_lines.x0 = p_rect_obj->x0;
	second_lines.y0 = p_rect_obj->y0;
	second_lines.x1 = p_rect_obj->x0;
	second_lines.y1 = p_rect_obj->y0+p_rect_obj->height;
	second_lines.offset = p_rect_obj->width;
	second_lines.colour = p_rect_obj->colour;
	second_lines.bgcolour = NULL; /* Only colour it once*/
	second_lines.thickness = p_rect_obj->thickness;

	Draw_parallel_lines(&first_lines);
	Draw_parallel_lines(&second_lines);

	/* Account for missing pixel*/
	if(p_rect_obj->thickness > 0U)
	{
		DISPLAY_ASSERT_VOID((first_lines.x1 < max_x) && (second_lines.y1 < max_y));
		Set_pixel(first_lines.x1, second_lines.y1);
	}
}
/* END OF FUNCTION*/

void Draw_solid_rectangle(const solid_rectangle_t  * const p_solid_rect_obj)
{
	Set_bgcolour(p_solid_rect_obj->colour);
	St7735s_fill_area_bg(p_solid_rect_obj->x0, p_solid_rect_obj->y0, p_solid_rect_obj->width, p_solid_rect_obj->height);
}
/* END OF FUNCTION*/

static void Plot_circle_points(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y)
{
	Set_pixel(xc+x, yc+y);
	Set_pixel(xc+y, yc+x);
	Set_pixel(xc-y, yc+x);
	Set_pixel(xc-x, yc+y);

	Set_pixel(xc-x, yc-y);
	Set_pixel(xc-y, yc-x);
	Set_pixel(xc+y, yc-x);
	Set_pixel(xc+x, yc-y);
}
/* END OF FUNCTION*/

static void Draw_single_circle(const circle_t * const p_circle_obj)
{
    int16_t x = (int16_t)p_circle_obj->r;
    int16_t y = 0;
    int16_t err = 0;

    while (x >= y)
    {
        Plot_circle_points(p_circle_obj->xc,p_circle_obj->yc,x,y);

        if ( err > 0)
        {
        	--x;
        	err -= 2*x + 1;
        }
        else
        {
        	++y;
        	err += 2*y + 1;
        }
    }
}
/* END OF FUNCTION*/

static void Draw_filled_circle(const circle_t * const p_circle_obj)
{
	int16_t x = (int16_t)p_circle_obj->r;
	int16_t y = 0;
	int16_t err = 0;

	while (x >= y)
	{
		static line_t circle_line;
		circle_line.thickness = 1U;
		circle_line.colour = p_circle_obj->bgcolour;

		circle_line.x0 = p_circle_obj->xc - x;
		circle_line.y0 = p_circle_obj->yc - y;
		circle_line.x1 = p_circle_obj->xc + x + 1U;
		circle_line.y1 = p_circle_obj->yc - y;
		Draw_line(&circle_line);

		circle_line.x0 = p_circle_obj->xc - x;
		circle_line.y0 = p_circle_obj->yc + y;
		circle_line.x1 = p_circle_obj->xc + x + 1U;
		circle_line.y1 = p_circle_obj->yc + y;
		Draw_line(&circle_line);

		circle_line.x0 = p_circle_obj->xc - y;
		circle_line.y0 = p_circle_obj->yc + x;
		circle_line.x1 = p_circle_obj->xc + y + 1U;
		circle_line.y1 = p_circle_obj->yc + x;
		Draw_line(&circle_line);

		circle_line.x0 = p_circle_obj->xc - y;
		circle_line.y0 = p_circle_obj->yc - x;
		circle_line.x1 = p_circle_obj->xc + y + 1U;
		circle_line.y1 = p_circle_obj->yc - x;
		Draw_line(&circle_line);

		if ( err > 0)
		{
			--x;
			err -= 2*x + 1;
		}
		else
		{
			++y;
			err += 2*y + 1;
		}
	}
}
/* END OF FUNCTION*/

void Draw_circle(const circle_t * const p_circle_obj)
{
	static circle_t l_circle;

	DISPLAY_ASSERT_VOID((p_circle_obj->xc + p_circle_obj->r < max_x) && (p_circle_obj->xc - p_circle_obj->r > 0xFFFFU) &&
			(p_circle_obj->yc + p_circle_obj->r < max_y) && (p_circle_obj->yc - p_circle_obj->r > 0xFFFFU));

	l_circle.colour = p_circle_obj->colour;
	l_circle.bgcolour = p_circle_obj->bgcolour;
	l_circle.r = p_circle_obj->r;
	l_circle.thickness = p_circle_obj->thickness;
	l_circle.xc = p_circle_obj->xc;
	l_circle.yc = p_circle_obj->yc;

	Set_colour(p_circle_obj->colour);

	/* Keep drawing circles inside each circle until we reach desired thickness*/
	while(l_circle.thickness > 0U)
	{
		Draw_single_circle(&l_circle);

		--l_circle.thickness;
		--l_circle.r;
	}

	/* If there is a background colour set it and draw a filled circle*/
	if(p_circle_obj->bgcolour != NULL)
	{
		Draw_filled_circle(&l_circle);
	}
}
/* END OF FUNCTION*/


