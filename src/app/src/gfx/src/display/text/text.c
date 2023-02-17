/*
 * text.c
 *
 *  Created on: 27 Jul 2022
 *      Author: a5126135
 */

#include "text_driver.h"
#include "text.h"
#include "stddef.h"
#include "display_assert.h"

static const font_descriptor_t * cur_font_dsc;

static uint16_t max_x = 0U;
static uint16_t max_y = 0U;

void Text_set_font(const font_descriptor_t * font_dsc)
{
	cur_font_dsc = font_dsc;
}
/* END OF FUNCTION*/

void Text_init(uint16_t x_max, uint16_t y_max)
{
	max_x = x_max-1U;
	max_y = y_max-1U;
}
/* END OF FUNCTION*/

/** @brief Computes length of str
 * @param str - pointer to string for computation.
 * @return length of string in characters.
 */
static uint16_t Local_str_len(const char * str)
{
	uint16_t len = 0U;

	while(*str != '\0')
	{
		++len;
		++str;
	}

	return len;
}
/* END OF FUNCTION*/

/** @brief Writes a character to the display.
 * @param x - x position of the character
 * @param y - y position of the character.
 * @param c - the character for sending.
 * @param set_bg_colour - flag to indicate whether or not to set a background colour.
 * @return returns the number of pixels in the x direction the characters has taken up.
 */
static uint8_t Write_char(const uint16_t x, const uint16_t y, const char c, const bool set_bg_colour)
{
	uint16_t px_width = cur_font_dsc->ptr_font_glyph_dsc[c - cur_font_dsc->unicode_start].w_px;
	const uint16_t px_height = cur_font_dsc->font_height;
	__far const uint8_t * glyph = cur_font_dsc->ptr_font_glyph_dsc[c - cur_font_dsc->unicode_start].glyph_ptr;
	const uint16_t bytes_in_width = (px_width >> 3U) + (((px_width & 7U) > 0U) ? 1U : 0U);

	DISPLAY_ASSERT(((x + px_width) < max_x) && ((y + px_height) < max_y), 0U);

	for(uint16_t yp = 0U, byte_nav = 0U; byte_nav < (bytes_in_width * px_height); ++byte_nav, ++yp)
	{
		for(uint16_t xp = 0U; xp < px_width; ++xp)
		{
			if( (*(glyph + byte_nav) & (0x80U >> (xp & 7U))) > 0U)
			{
				Set_pixel(x+xp, y+yp);
			}
			else if(set_bg_colour)
			{
				Set_bgpixel(x+xp, y+yp);
			}
			else
			{
				/* Do Nothing*/
			}

			if(((0x80U >> (xp & 7U)) == 1U) && (xp+1U < px_width))
			{
				++byte_nav;
			}
		}
	}

	return px_width;
}
/* END OF FUNCTION*/

uint8_t Text_put_char(const uint16_t x, const uint16_t y, const char c, const uint8_t * colour, const uint8_t * bg_colour)
{
	const bool set_bg_colour = (NULL != bg_colour);

	Set_colour(colour);

	if(set_bg_colour)
	{
		Set_bgcolour(bg_colour);
	}

	return Write_char(x, y, c, set_bg_colour);
}
/* END OF FUNCTION*/

uint8_t Text_put_custom_glyph(const uint16_t x, const uint16_t y, const font_glyph_descriptor_t * glyph, const uint8_t * colour, const uint8_t * bg_colour)
{
	const uint16_t bytes_in_width = (glyph->w_px >> 3U) + (((glyph->w_px & 7U) > 0U) ? 1U : 0U);
	const bool set_bg_colour = bg_colour != NULL;
	const uint16_t byte_count = cur_font_dsc->font_height * bytes_in_width;

	DISPLAY_ASSERT(((x + glyph->w_px) < max_x) && ((y + cur_font_dsc->font_height) < max_y), 0U);

	Set_colour(colour);

	if(bg_colour)
	{
		Set_bgcolour(bg_colour);
	}

	for(uint16_t yp = 0U, byte_nav = 0U; byte_nav < byte_count; ++byte_nav, ++yp)
	{
		for(uint16_t xp = 0U; xp < glyph->w_px; ++xp)
		{
			if( (*(glyph->glyph_ptr + byte_nav) & (0x80U >> (xp & 7U))) > 0U)
			{
				Set_pixel(x+xp, y+yp);
			}
			else if(set_bg_colour)
			{
				Set_bgpixel(x+xp, y+yp);
			}
			else
			{
				/* Do Nothing*/
			}

			if(((0x80U >> (xp & 7U)) == 1U) && (xp+1U < glyph->w_px))
			{
				++byte_nav;
			}
		}
	}

	return glyph->w_px;
}
/* END OF FUNCTION*/

uint16_t Text_put_line(const uint16_t x, const uint16_t y, const char * str, const uint8_t * colour, const uint8_t * bg_colour)
{
	const uint16_t str_len_bytes = Local_str_len(str);
	const bool set_bg_colour = (NULL != bg_colour);
	uint16_t pixels_written = 0U;

	Set_colour(colour);

	if(set_bg_colour)
	{
		Set_bgcolour(bg_colour);
	}

	for(uint16_t c = 0U; c < str_len_bytes; ++c)
	{
		pixels_written += Write_char(x+pixels_written, y, *(str+c), set_bg_colour);
	}

	return pixels_written;
}
/* END OF FUNCTION*/

uint16_t Text_put_str(const uint16_t x, const uint16_t y, const char * str, const uint8_t * colour, const uint8_t * bg_colour)
{
	const uint16_t str_len_bytes = Local_str_len(str);
	const bool set_bg_colour = (NULL != bg_colour);
	uint16_t pixels_written = 0U;

	uint16_t l_x = x, l_y = y;

	Set_colour(colour);

	if(set_bg_colour)
	{
		Set_bgcolour(bg_colour);
	}

	for(uint16_t c = 0U; c < str_len_bytes; ++c)
	{
		bool too_much_text = false;
		while((*(str+c) == '\n') || (*(str+c) == '\r') || ((l_x + cur_font_dsc->ptr_font_glyph_dsc[*(str+c) - cur_font_dsc->unicode_start].w_px) > max_x))
		{
			l_x = x;
			l_y += cur_font_dsc->font_height;

			if((*(str+c) == '\n') || (*(str+c) == '\r'))
			{
				++c;
			}

			if((l_y > max_y) || (c >= str_len_bytes))
			{
				too_much_text = true;
				break;
			}
		}

		if(too_much_text)
		{
			break;
		}
		else
		{
			pixels_written = Write_char(l_x, l_y, *(str+c), set_bg_colour);
			l_x += pixels_written;
		}
	}

	return l_x;
}
/* END OF FUNCTION*/

uint16_t Text_str_len_px(const char * str)
{
	const char * l_str = str;
	uint16_t len = 0U;

	while(*l_str != '\0')
	{
		len += cur_font_dsc->ptr_font_glyph_dsc[*l_str - cur_font_dsc->unicode_start].w_px;
		++l_str;
	}

	return len;
}

/** @brief Reverses a string.
 * @param str - string to reverse
 * @param len - length of string.
 */
static void Str_rev(char * const str, uint16_t len)
{
	const uint16_t half_str_len = len >> 1U;
	char temp = '0';

	for (uint16_t j = 0; j < half_str_len; ++j)
	{
		temp = str[j];
		str[j] = str[len - j - 1];
		str[len - j - 1] = temp;
	}
}
/* END OF FUNCTION*/

int16_t Text_int_to_str_sf(int16_t i, uint16_t sf, char * const str)
{
	const bool is_negative = (i < 0);
	char * l_str = str;
	uint16_t ui = (is_negative) ? (uint16_t) (i * -1) : (uint16_t) i;
	uint16_t str_len = 0U;
	uint16_t l_sf = sf;

	do
	{
		*l_str = (ui % 10U) + '0';
		ui /= 10U;

		++l_str;
		++str_len;
		--l_sf;
	}
	while ( (ui > 0U) || (l_sf > 0U));

	if(is_negative)
	{
		*l_str = '-';
		++l_str;
		++str_len;
	}

	Str_rev(l_str-str_len, str_len);

	*l_str = '\0'; /* NULL Terminate*/

	return str_len;
}
/* END OF FUNCTION*/

int16_t Text_int_to_str(int16_t i, char * const str)
{
	const bool is_negative = (i < 0);
	char * l_str = str;
	uint16_t ui = (is_negative) ? (uint16_t) (i * -1) : (uint16_t) i;
	uint16_t str_len = 0U;

	do
	{
		*l_str = (ui % 10U) + '0';
		ui /= 10U;

		++l_str;
		++str_len;
	}
	while (ui > 0U);

	if(is_negative)
	{
		*l_str = '-';
		++l_str;
		++str_len;
	}

	Str_rev(l_str-str_len, str_len);

	*l_str = '\0'; /* NULL Terminate*/

	return str_len;
}
/* END OF FUNCTION*/
