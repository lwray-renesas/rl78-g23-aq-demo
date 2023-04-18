/**
 * @file st7735s.h
 * @brief the header file for the st7735s controller simple source.
 * @note This source ONLY supports 8bit SPI control mode & remember to set the CONFIG_SPI_INTEGRATED_CS macro to fit the applications available HW.
 * Also only supports 16bit colour depth - initialisation buffer should be reviewed for every display.
 */

#ifndef ST7735S_H_
#define ST7735S_H_

#include "stdint.h"
#include "stdbool.h"

/** @brief Length of display in pixels.*/
#define DISPLAY_PIXEL_WIDTH			(160U)
/** @brief Height of display in pixels.*/
#define DISPLAY_PIXEL_HEIGHT		(80U)
/** @brief macro used to define number of bits per colour*/
#define DISPLAY_COLOUR_BPP			(16U)
/** @brief macro used to define inversion method (0 = dot vs 1 = column)*/
#define DISPLAY_INVERSION_CONTROL	(0)

/** @brief enumerated type to describe orientations for ST7735S controller*/
typedef enum
{
	ORIENT_0 = 0U, /**< Orientation default*/
	ORIENT_90, /**< Orientation 90deg*/
	ORIENT_180, /**< Orientation 180deg*/
	ORIENT_270 /**< Orientation 270deg*/
}ST7735S_orientation_t;

/** @brief struct to determine what the current operating parameters of the display are.*/
typedef struct
{
	ST7735S_orientation_t orientation; /**< current orientation*/
	uint16_t xmin; /**< current x minimum*/
	uint16_t xmax; /**< current x maximum*/
	uint16_t ymin; /**< current y minimum*/
	uint16_t ymax; /**< current y maximum*/
}ST7735S_display_area_info_t;

/** @brief Complete initialisation of the ST7735 driver module for a given display - the sequence finishes by putting the display in SLEEP mode.
 * @param[in] init_fill_colour - pointer to colour array for initial fill of display.
 */
void St7735s_init(const uint8_t * const init_fill_colour);

/** @brief function used to change the orientation of the display.
 * @details moves the 0,0 pixel around every corner - writing always occurs left to left.
 * @param[in] rot - rotation constant:
 * ORIENT_0 top left --> top right [per line]
 * ORIENT_90 top right --> bottom right [per line]
 * ORIENT_180 bottom right --> bottom left [per line]
 * ORIENT_270 bottom left --> top left [per line]
 */
void St7735s_set_orientation(const ST7735S_orientation_t rot);

/** @brief outputs current display area info
 * @param pointer to struct ot populate with display area info.
 */
void St7735s_get_display_area_info(ST7735S_display_area_info_t * disp_arg);

/** @brief function used to set the current output colour of the display driver.
 * @param[in] colour - pointer to colour array
 */
void St7735s_set_colour(const uint8_t * const colour);

/** @brief function used to set the current output background colour of the display driver.
 * @param[in] bg_colour - pointer to colour array
 */
void St7735s_set_bgcolour(const uint8_t * const bg_colour);

/** @brief Function used to set a pixel the current colour on the display.
 * @param x - x pixel
 * @param y - y pixel
 */
void St7735s_set_pixel(uint16_t x, uint16_t y);

/** @brief Function used to set a pixel the current background colour on the display.
 * @param x - x pixel
 * @param y - y pixel
 */
void St7735s_set_bgpixel(uint16_t x, uint16_t y);

/** @brief Function to refresh the screen with current RAM contents*/
void St7735s_refresh(void);

/** @brief Function used to send raw image data to display.
 * @details Images can be converted using: http://javl.github.io/image2cpp/
 * @param x - x coordinate
 * @param y - y coorindate
 * @param width - width of image
 * @param height - height of image
 * @param data - array containing image data bytes.
 */
void St7735s_send_image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, __far const uint8_t * data);

/** @brief Function used to fill an area with the background pixel colour
 * @param x - x coordinate
 * @param y - y coorindate
 * @param width - width of area
 * @param height - height of area
 */
void St7735s_fill_area_bg(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/** @brief Fills display area with current colour*/
void St7735s_fill_display(void);

/** @brief Puts display into low power mode*/
void St7735s_sleep_display(void);

/** @brief Wakes display up*/
void St7735s_wake_display(void);

/** @brief turns display output off*/
void St7735s_display_on(void);

/** @brief turns display output on*/
void St7735s_display_off(void);

/** @brief turns display inversion on*/
void St7735s_inversion_on(void);

/** @brief turns display inversion off*/
void St7735s_inversion_off(void);

#endif /* ST7735S_H_ */
