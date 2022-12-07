/*
 * font.h
 *
 *  Created on: 27 Jul 2022
 *      Author: a5126135
 */

#ifndef DISPLAY_TEXT_FONT_H_
#define DISPLAY_TEXT_FONT_H_

#include "stdint.h"

/** Based on modified version of https://lvgl.io/tools/fontconverter output.*/

/** @brief font glyph descriptor to allow parsing of each individual character*/
typedef struct
{
	uint8_t w_px;	/**< width of the glyph*/
	__far const uint8_t * glyph_ptr;	/**< pointer to the first value for the glyph in the bitmap array*/
}font_glyph_descriptor_t;

/** @brief font  descriptor to allow parsing of each individual character*/
typedef struct
{
	uint16_t unicode_start; /**< the first unicode character described in the font*/
	uint16_t unicode_end; /**< the last unicode character described in the font*/
	uint16_t font_height; /**< height, in number of pixels of the font*/
	__far const font_glyph_descriptor_t * ptr_font_glyph_dsc; /**< pointer to an array of font glyph descriptors which make up the font*/
}font_descriptor_t;

/** Default font descriptor*/
extern const font_descriptor_t default_font;
extern const font_descriptor_t small_font;

#endif /* DISPLAY_TEXT_FONT_H_ */
