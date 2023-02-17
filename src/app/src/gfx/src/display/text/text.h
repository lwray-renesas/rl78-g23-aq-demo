/*
 * text.h
 *
 *  Created on: 27 Jul 2022
 *      Author: a5126135
 */

#ifndef DISPLAY_TEXT_TEXT_H_
#define DISPLAY_TEXT_TEXT_H_

#include "font.h"

/** @brief set the font for use when writing to the display.
 * @param[in] font_dsc - pointer to the font descriptor.
 */
void Text_set_font(const font_descriptor_t * font_dsc);

/** @brief sets the current x and y limits of the drawing library
 * @param x_max - maximum x coordinate.
 * @param y_max - maximum y coordinate.
 */
void Text_init(uint16_t x_max, uint16_t y_max);

/** @brief puts character on display
 * @param[in] x - x location of character.
 * @param[in] y - y location of character
 * @param[in] c - character (char - ascii).
 * @param[in] colour - pointer to colour of text
 * @param[in] bg_colour - pointer to background colour of text
 * @return width of character written in pixels.
 */
uint8_t Text_put_char(const uint16_t x, const uint16_t y, const char c, const uint8_t * colour, const uint8_t * bg_colour);

/** @brief puts custom glyph on display
 * @param[in] x - x location of character.
 * @param[in] y - y location of character
 * @param[in] glyph - glyph for drawing
 * @param[in] colour - pointer to colour of text
 * @param[in] bg_colour - pointer to background colour of text
 * @return width of character written in pixels.
 */
uint8_t Text_put_custom_glyph(const uint16_t x, const uint16_t y, const font_glyph_descriptor_t * glyph, const uint8_t * colour, const uint8_t * bg_colour);

/** @brief puts character string on display up to one line long.
 * @param[in] x - x location of character.
 * @param[in] y - y location of character
 * @param[in] str - NULL terminated character string (char - ascii).
 * @param[in] colour - pointer to colour of text
 * @param[in] bg_colour - pointer to background colour of text
 * @return width of character string written in pixels.
 */
uint16_t Text_put_line(const uint16_t x, const uint16_t y, const char * str, const uint8_t * colour, const uint8_t * bg_colour);

/** @brief puts character string on display - process' \n and \r to place new lines on display
 * @param[in] x - x location of character.
 * @param[in] y - y location of character
 * @param[in] str - NULL terminated character string (char - ascii).
 * @param[in] colour - pointer to colour of text
 * @param[in] bg_colour - pointer to background colour of text
 * @return width of character string written in pixels.
 */
uint16_t Text_put_str(const uint16_t x, const uint16_t y, const char * str, const uint8_t * colour, const uint8_t * bg_colour);

/** @brief returns size of string in pixels.
 * @param str - input string
 * @return size of string in ;ixels
 */
uint16_t Text_str_len_px(const char * str);

/** @brief converts a signed integer into a string to maximum significatn figures, prepending zeroes as required.
 * @param i - signed integer
 * @param sf - significant figures to place.
 * @param str - output string
 * @return size of string excluding null
 */
int16_t Text_int_to_str_sf(int16_t i, uint16_t sf, char * const str);

/** @brief converts a signed integer into a string
 * @param i - signed integer
 * @param str - output string
 * @return size of string excluding null
 */
int16_t Text_int_to_str(int16_t i, char * const str);


#endif /* DISPLAY_TEXT_TEXT_H_ */
