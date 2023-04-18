/**
 * @file st7735s.c
 * @brief the source file for the st7735s controller simple source.
 */

#include "st7735s_port.h"
#include "st7735s.h"

#define ROWS_DIF_2 ((132U - DISPLAY_PIXEL_HEIGHT)/2U)
#define COLS_DIF_2 ((162U - DISPLAY_PIXEL_WIDTH)/2U)

#define ROWS_START (ROWS_DIF_2)
#define ROWS_END (DISPLAY_PIXEL_HEIGHT + ROWS_DIF_2 - 1U)

#define COLS_START (COLS_DIF_2)
#define COLS_END (DISPLAY_PIXEL_WIDTH)

#if DISPLAY_COLOUR_BPP == 12
#define COLMOD_BYTE (0x3U)
#define BYTES_PER_COLOUR	(2U)
#elif DISPLAY_COLOUR_BPP == 16
#define COLMOD_BYTE (0x5U)
#define BYTES_PER_COLOUR	(2U)
#elif DISPLAY_COLOUR_BPP == 18
#define COLMOD_BYTE (0x6U)
#define BYTES_PER_COLOUR	(3U)
#else
#error "DISPLAY_COLOUR_BPP unsupported value - please check definition in st7735s.h"
#endif

#if DISPLAY_INVERSION_CONTROL == 0
#define INVCTL_BYTE (0x0U)
#elif DISPLAY_INVERSION_CONTROL == 1
#define uint8_t INVCTL_BYTE (0x7U)
#else
#error "DISPLAY_INVERSION_CONTROL unsupported value - please check definition in st7735s.h"
#endif

#define IMAGE_BUFFER_SIZE	(BYTES_PER_COLOUR * DISPLAY_PIXEL_WIDTH * DISPLAY_PIXEL_HEIGHT)

typedef enum {
	NOP       = 0x00,
	SWRESET   = 0x01, /* Software Reset */
	RDDID     = 0x04, /* Read Display ID */
	RDDST     = 0x09, /* Read Display Status */
	RDDPM     = 0x0a, /* Read Display Power Mode */
	RDDMADCTL = 0x0b, /* Read Display MADCTL */
	RDDCOLMOD = 0x0c, /* Read Display Pixel Format */
	RDDIM     = 0x0d, /* Read Display Image Mode */
	RDDSM     = 0x0e, /* Read Display Signal Mode */
	RDDSDR    = 0x0f, /* Read Display Self-Diagnostic Result */
	SLPIN     = 0x10, /* SLEEP In */
	SLPOUT    = 0x11, /* SLEEP Out */
	PTLON     = 0x12, /* Partial Display Mode On */
	NORON     = 0x13, /* Normal Display Mode On */
	INVOFF    = 0x20, /* Display Inversion Off */
	INVON     = 0x21, /* Display Inversion On */
	GAMSET    = 0x26, /* Gamma Set */
	DISPOFF   = 0x28, /* Display Off */
	DISPON    = 0x29, /* Display On */
	CASET     = 0x2a, /* Column Address Set */
	RASET     = 0x2b, /* Row Address Set */
	RAMWR     = 0x2c, /* Memory Write */
	RGBSET    = 0x2d, /* Color Setting 4k, 65k, 262k */
	RAMRD     = 0x2e, /* Memory Read */
	PTLAR     = 0x30, /* Partial Area */
	SCRLAR    = 0x33, /* Scroll Area Set */
	TEOFF     = 0x34, /* Tearing Effect Line OFF */
	TEON      = 0x35, /* Tearing Effect Line ON */
	MADCTL    = 0x36, /* Memory Data Access Control */
	VSCSAD    = 0x37, /* Vertical Scroll Start Address of RAM */
	IDMOFF    = 0x38, /* Idle Mode Off */
	IDMON     = 0x39, /* Idle Mode On */
	COLMOD    = 0x3a, /* Interface Pixel Format */
	RDID1     = 0xda, /* Read ID1 Value */
	RDID2     = 0xdb, /* Read ID2 Value */
	RDID3     = 0xdc, /* Read ID3 Value */
	FRMCTR1   = 0xb1, /* Frame Rate Control in normal mode, full colors */
	FRMCTR2   = 0xb2, /* Frame Rate Control in idle mode, 8 colors */
	FRMCTR3   = 0xb3, /* Frame Rate Control in partial mode, full colors */
	INVCTR    = 0xb4, /* Display Inversion Control */
	PWCTR1    = 0xc0, /* Power Control 1 */
	PWCTR2    = 0xc1, /* Power Control 2 */
	PWCTR3    = 0xc2, /* Power Control 3 in normal mode, full colors */
	PWCTR4    = 0xc3, /* Power Control 4 in idle mode 8colors */
	PWCTR5    = 0xc4, /* Power Control 5 in partial mode, full colors */
	VMCTR1    = 0xc5, /* VCOM Control 1 */
	VMOFCTR   = 0xc7, /* VCOM Offset Control */
	WRID2     = 0xd1, /* Write ID2 Value */
	WRID3     = 0xd2, /* Write ID3 Value */
	NVFCTR1   = 0xd9, /* NVM Control Status */
	NVFCTR2   = 0xde, /* NVM Read Command */
	NVFCTR3   = 0xdf, /* NVM Write Command */
	GMCTRP1   = 0xe0, /* Gamma '+'Polarity Correction Characteristics Setting */
	GMCTRN1   = 0xe1, /* Gamma '-'Polarity Correction Characteristics Setting */
	GCV       = 0xfc, /* Gate Pump Clock Frequency Variable */
} ST7735S_Command;

/** Used for calculating display x and y offsets*/
typedef struct
{
	uint16_t xoffset;
	uint16_t yoffset;
	uint16_t xend;
	uint16_t yend;
}ST7735S_display_constants_t;

/** Used for calculating display x and y offsets*/
typedef struct
{
	ST7735S_display_constants_t area; /**< x & y area of display to be updated*/
	bool dirty_mark; /**< true for dirt marked display*/
	bool dirty_mark_all; /**< true when entire display should be updated*/
}ST7735S_dirty_marking;

static volatile bool spi_tx_done = true;
static const uint8_t * colour_ptr = NULL;
static const uint8_t * bg_colour_ptr = NULL;

ST7735S_display_area_info_t current_display_info = {
		.orientation = ORIENT_0,
		.xmin = 0U,
		.xmax = DISPLAY_PIXEL_WIDTH,
		.ymin = 0U,
		.ymax = DISPLAY_PIXEL_HEIGHT
};

ST7735S_display_constants_t current_display_constants = {
		.xoffset = COLS_START,
		.yoffset = ROWS_START
};

ST7735S_dirty_marking dirty_marking = {
		.area = {
				.xoffset = 0U,
				.yoffset = 0U,
				.xend = 0U,
				.yend = 0U
		},
		.dirty_mark = false,
		.dirty_mark_all = false
};

static const uint8_t init_buf[] = {
		1,  SLPOUT, /* SLEEP out, turn off SLEEP mode */
		1, DISPOFF,  /*  output from frame mem disabled */
		4, FRMCTR1, 0x01, 0x2C, 0x2D, /* frame frequency normal mode */
		4, FRMCTR2, 0x01, 0x2C, 0x2D, /* frame frequency idle mode */
		7, FRMCTR3, 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D,  /* frame freq partial mode: 1-3 dot inv, 4-6 col inv */
		2,  INVCTR, INVCTL_BYTE, /* display inversion control: 3-bit 0=dot, 1=col */

		4,  PWCTR1, 0xA2, 0x02, 0x84, /* power control */
		2,  PWCTR2, 0xC5,
		3,  PWCTR3, 0x0A, 0x00,
		3,  PWCTR4, 0x8A, 0x2A,
		3,  PWCTR5, 0x8A, 0xEE, /* partial */

		/* display brightness and gamma */
		2,     GCV, 0xD8, /* auto gate pump freq, max power save */
		2, NVFCTR1, 0x40, /* automatic adjust gate pumping clock for saving power consumption */
		2,  VMCTR1, 0x0E,  /* VCOM voltage setting */
		2, VMOFCTR, 0x80, /* ligthness of black color 0-0x1f */
		2,  GAMSET, 0x08, /* gamma 1, 2, 4, 8 */

		2,  COLMOD, COLMOD_BYTE, /* 3=12bit, 5=16-bit, 6=18-bit  pixel color mode */
		17, GMCTRP1,0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2C,
		0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10,
		17, GMCTRN1,0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2C,
		0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10,
		1,   INVON, /* display inversion on/off */
		1,  IDMOFF, /* idle mode off */
		1,   NORON  /* normal display mode on */
};

static uint8_t image_buffer[IMAGE_BUFFER_SIZE];

/**
 * @brief Used to send SPI data.
 * @param tx_buf - pointer to buffer for transmission.
 * @param tx_num - number of bytes to send.
 */
static inline void Spi_send_blocking(const uint8_t * const tx_buf, uint16_t tx_num)
{
	CS_low(); /* Assert chip select signal*/

	Spi_write_block(tx_buf, tx_num); /* Start the write sequence*/

	CS_high(); /* Deassert chip select signal*/
	DC_high(); /* Deassert DC signal*/
}
/* END OF FUNCTION*/

/**
 * @brief Used to send single command buffer.
 * @param tx_buf - pointer to buffer for transmission.
 * @param tx_num - number of bytes to send.
 */
static void St7735s_write_cmd_buf(const uint8_t * const tx_buf, uint16_t tx_num)
{
	DC_low();
	Spi_send_blocking(tx_buf, 1U);

	if(tx_num > 1U)
	{
		Spi_send_blocking(tx_buf + 1, tx_num-1U);
	}
}
/* END OF FUNCTION*/

/** @brief Writes a sequence of commands formatted like the init buf */
static void St7735s_write_cmd_sequence(const uint8_t * const tx_seq_buf, uint16_t tx_seq_buf_len)
{
	uint16_t args;

	for(uint16_t i = 0; i < tx_seq_buf_len; i+=args+1)
	{
		args = tx_seq_buf[i];

		St7735s_write_cmd_buf(tx_seq_buf + i + 1, args);
	}
}
/* END OF FUNCTION*/

/** @brief sends the RAMWR command to the display controller*/
static inline void St7735s_set_ram_access(void)
{
	static const uint8_t ram_cmd[] = { RAMWR };

	St7735s_write_cmd_buf(ram_cmd, sizeof(ram_cmd));
}
/* END OF FUNCTION*/

/** @brief sends the RAMWR command to the display controller*/
static inline void St7735s_soft_reset(void)
{
	static const uint8_t swreset_cmd[] = { SWRESET };

	St7735s_write_cmd_buf(swreset_cmd, sizeof(swreset_cmd));

	Delay_ms(150U);
}
/* END OF FUNCTION*/

/**
 * @brief Used to send data buffer.
 * @param tx_buf - pointer to buffer for transmission.
 * @param tx_num - number of bytes to send.
 */
static void St7735s_write_data_buf(const uint8_t * const tx_buf, uint16_t tx_num)
{
	DC_high();

	Spi_send_blocking(tx_buf, tx_num);
}
/* END OF FUNCTION*/

void St7735s_init(const uint8_t * const init_fill_colour)
{
	spi_tx_done = true;

	St7735s_soft_reset();

	St7735s_write_cmd_sequence(init_buf, sizeof(init_buf));

	St7735s_set_orientation(ORIENT_180);

	colour_ptr = init_fill_colour;

	St7735s_fill_display();

	St7735s_sleep_display();
}
/* END OF FUNCTION*/

void St7735s_set_orientation(const ST7735S_orientation_t rot)
{
	switch(rot)
	{
	case ORIENT_90:
	{
		static const uint8_t current_orientation_buf[] = {2, MADCTL, 0x08, 5, CASET, 0x00, ROWS_START, 0x00, ROWS_END, 5, RASET, 0x00, COLS_START, 0x00, COLS_END};
		current_display_info.xmax = DISPLAY_PIXEL_HEIGHT;
		current_display_info.ymax = DISPLAY_PIXEL_WIDTH;
		current_display_constants.xoffset = ROWS_START;
		current_display_constants.yoffset = COLS_START;
		current_display_constants.xend = ROWS_END;
		current_display_constants.yend = COLS_END;
		St7735s_write_cmd_sequence(current_orientation_buf, sizeof(current_orientation_buf));
	}
	break;
	case ORIENT_180:
	{
		static const uint8_t current_orientation_buf[] = {2, MADCTL, 0x68, 5, CASET, 0x00, COLS_START, 0x00, COLS_END, 5, RASET, 0x00, ROWS_START, 0x00, ROWS_END};
		current_display_info.xmax = DISPLAY_PIXEL_WIDTH;
		current_display_info.ymax = DISPLAY_PIXEL_HEIGHT;
		current_display_constants.xoffset = COLS_START;
		current_display_constants.yoffset = ROWS_START;
		current_display_constants.xend = COLS_END;
		current_display_constants.yend = ROWS_END;
		St7735s_write_cmd_sequence(current_orientation_buf, sizeof(current_orientation_buf));
	}
	break;
	case ORIENT_270:
	{
		static const uint8_t current_orientation_buf[] = {2, MADCTL, 0xC8, 5, CASET, 0x00, ROWS_START, 0x00, ROWS_END, 5, RASET, 0x00, COLS_START, 0x00, COLS_END};
		current_display_info.xmax = DISPLAY_PIXEL_HEIGHT;
		current_display_info.ymax = DISPLAY_PIXEL_WIDTH;
		current_display_constants.xoffset = ROWS_START;
		current_display_constants.yoffset = COLS_START;
		current_display_constants.xend = ROWS_END;
		current_display_constants.yend = COLS_END;
		St7735s_write_cmd_sequence(current_orientation_buf, sizeof(current_orientation_buf));
	}
	break;
	default:
	{
		static const uint8_t current_orientation_buf[] = {2, MADCTL, 0xA8, 5, CASET, 0x00, COLS_START, 0x00, COLS_END, 5, RASET, 0x00, ROWS_START, 0x00, ROWS_END};
		current_display_info.xmax = DISPLAY_PIXEL_WIDTH;
		current_display_info.ymax = DISPLAY_PIXEL_HEIGHT;
		current_display_constants.xoffset = COLS_START;
		current_display_constants.yoffset = ROWS_START;
		current_display_constants.xend = COLS_END;
		current_display_constants.yend = ROWS_END;
		St7735s_write_cmd_sequence(current_orientation_buf, sizeof(current_orientation_buf));
	}
	break;
	}

	current_display_info.orientation = rot;
}
/* END OF FUNCTION*/

void St7735s_get_display_area_info(ST7735S_display_area_info_t * disp_arg)
{
	disp_arg->orientation = current_display_info.orientation;
	disp_arg->xmin = current_display_info.xmin;
	disp_arg->xmax = current_display_info.xmax;
	disp_arg->ymin = current_display_info.ymin;
	disp_arg->ymax = current_display_info.ymax;
}
/* END OF FUNCTION*/

void St7735s_set_colour(const uint8_t * const colour)
{
	colour_ptr = colour;
}
/* END OF FUNCTION*/

void St7735s_set_bgcolour(const uint8_t * const bg_colour)
{
	bg_colour_ptr = bg_colour;
}
/* END OF FUNCTION*/

void St7735s_set_pixel(uint16_t x, uint16_t y)
{
	if(!dirty_marking.dirty_mark)
	{
		dirty_marking.dirty_mark = true;
		dirty_marking.area.xoffset = x;
		dirty_marking.area.xend = x;
		dirty_marking.area.yoffset = y;
		dirty_marking.area.yend = y;
	}
	else
	{
		if(x < dirty_marking.area.xoffset)
		{
			dirty_marking.area.xoffset = x;
		}
		else if(x > dirty_marking.area.xend)
		{
			dirty_marking.area.xend = x;
		}
		else
		{
			/* Do Nothing*/
		}

		if(y < dirty_marking.area.yoffset)
		{
			dirty_marking.area.yoffset = y;
		}
		else if(y > dirty_marking.area.yend)
		{
			dirty_marking.area.yend = y;
		}
		else
		{
			/* Do Nothing*/
		}
	}

#if BYTES_PER_COLOUR == 3
	image_buffer[((y * DISPLAY_PIXEL_WIDTH) + x)*3U] = colour_ptr[0U];
	image_buffer[(((y * DISPLAY_PIXEL_WIDTH) + x)*3U)+1U] = colour_ptr[1U];
	image_buffer[(((y * DISPLAY_PIXEL_WIDTH) + x)*3U)+2U] = colour_ptr[2U];
#else
	image_buffer[((y * DISPLAY_PIXEL_WIDTH) + x)<<1U] = colour_ptr[0U];
	image_buffer[(((y * DISPLAY_PIXEL_WIDTH) + x)<<1U)+1U] = colour_ptr[1U];
#endif
}
/* END OF FUNCTION*/

void St7735s_set_bgpixel(uint16_t x, uint16_t y)
{
	if(!dirty_marking.dirty_mark)
	{
		dirty_marking.dirty_mark = true;
		dirty_marking.area.xoffset = x;
		dirty_marking.area.xend = x;
		dirty_marking.area.yoffset = y;
		dirty_marking.area.yend = y;
	}
	else
	{
		if(x < dirty_marking.area.xoffset)
		{
			dirty_marking.area.xoffset = x;
		}
		else if(x > dirty_marking.area.xend)
		{
			dirty_marking.area.xend = x;
		}
		else
		{
			/* Do Nothing*/
		}

		if(y < dirty_marking.area.yoffset)
		{
			dirty_marking.area.yoffset = y;
		}
		else if(y > dirty_marking.area.yend)
		{
			dirty_marking.area.yend = y;
		}
		else
		{
			/* Do Nothing*/
		}
	}

#if BYTES_PER_COLOUR == 3
	image_buffer[((y * DISPLAY_PIXEL_WIDTH) + x)*3U] = bg_colour_ptr[0U];
	image_buffer[(((y * DISPLAY_PIXEL_WIDTH) + x)*3U)+1U] = bg_colour_ptr[1U];
	image_buffer[(((y * DISPLAY_PIXEL_WIDTH) + x)*3U)+2U] = bg_colour_ptr[2U];
#else
	image_buffer[((y * DISPLAY_PIXEL_WIDTH) + x)<<1U] = bg_colour_ptr[0U];
	image_buffer[(((y * DISPLAY_PIXEL_WIDTH) + x)<<1U)+1U] = bg_colour_ptr[1U];
#endif
}
/* END OF FUNCTION*/

void St7735s_refresh(void)
{
	static uint8_t pixel_buf[] = {5, CASET, 0x00, 0x00, 0x00, 0x00, 5, RASET, 0x00, 0x00, 0x00, 0x00};

	if(dirty_marking.dirty_mark_all)
	{
		dirty_marking.dirty_mark_all = false;
		dirty_marking.dirty_mark = false;

		pixel_buf[3] = current_display_constants.xoffset;
		pixel_buf[5] = current_display_constants.xend;
		pixel_buf[9] = current_display_constants.yoffset;
		pixel_buf[11] = current_display_constants.yend;

		St7735s_write_cmd_sequence(pixel_buf, sizeof(pixel_buf));
		St7735s_set_ram_access();
		St7735s_write_data_buf(image_buffer, IMAGE_BUFFER_SIZE);
	}
	else if(dirty_marking.dirty_mark)
	{
		uint8_t * image_buf_nav = NULL;

		const uint16_t y_diff = dirty_marking.area.yend-dirty_marking.area.yoffset;
#if BYTES_PER_COLOUR == 3
		const uint16_t x_diff = ((dirty_marking.area.xend-dirty_marking.area.xoffset)+1U)*3U;
#else
		const uint16_t x_diff = ((dirty_marking.area.xend-dirty_marking.area.xoffset)+1U)<<1U;
#endif
		dirty_marking.dirty_mark = false;

		pixel_buf[3] = dirty_marking.area.xoffset + current_display_constants.xoffset;
		pixel_buf[5] = dirty_marking.area.xend + current_display_constants.xoffset;
		pixel_buf[9] = dirty_marking.area.yoffset + current_display_constants.yoffset;
		pixel_buf[11] = dirty_marking.area.yend + current_display_constants.yoffset;

		St7735s_write_cmd_sequence(pixel_buf, sizeof(pixel_buf));
		St7735s_set_ram_access();

#if BYTES_PER_COLOUR == 3
		image_buf_nav = &image_buffer[((dirty_marking.area.yoffset * DISPLAY_PIXEL_WIDTH) + dirty_marking.area.xoffset)*3U];
#else
		image_buf_nav = &image_buffer[((dirty_marking.area.yoffset * DISPLAY_PIXEL_WIDTH) + dirty_marking.area.xoffset)<<1U];
#endif

		for(uint16_t i = 0U; i <= y_diff; ++i)
		{
			St7735s_write_data_buf(image_buf_nav, x_diff);
			image_buf_nav += (DISPLAY_PIXEL_WIDTH << 1U);
		}
	}
}
/* END OF FUNCTION*/

void St7735s_send_image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, __far const uint8_t * data)
{
	uint16_t data_index = 0U;

	if(!dirty_marking.dirty_mark)
	{
		dirty_marking.dirty_mark = true;
		dirty_marking.area.xoffset = x;
		dirty_marking.area.xend = (x+width);
		dirty_marking.area.yoffset = y;
		dirty_marking.area.yend = (y+height);
	}
	else
	{
		if(x < dirty_marking.area.xoffset)
		{
			dirty_marking.area.xoffset = x;
		}
		else if((x+width) > dirty_marking.area.xend)
		{
			dirty_marking.area.xend = (x+width);
		}
		else
		{
			/* Do Nothing*/
		}

		if(y < dirty_marking.area.yoffset)
		{
			dirty_marking.area.yoffset = y;
		}
		else if((y+height) > dirty_marking.area.yend)
		{
			dirty_marking.area.yend = (y+height);
		}
		else
		{
			/* Do Nothing*/
		}
	}

	for(uint16_t y_pos = y; y_pos < (y+height); ++y_pos)
	{
		for(uint16_t x_pos = x; x_pos < (x+width); ++x_pos)
		{
#if BYTES_PER_COLOUR == 3
			image_buffer[((y_pos * DISPLAY_PIXEL_WIDTH) + x_pos)*3U] = data[data_index];
			image_buffer[(((y_pos * DISPLAY_PIXEL_WIDTH) + x_pos)*3U)+1U] = data[data_index+1U];
			image_buffer[(((y_pos * DISPLAY_PIXEL_WIDTH) + x_pos)*3U)+2U] = data[data_index+2U];
			data_index += 3U;
#else
			image_buffer[((y_pos * DISPLAY_PIXEL_WIDTH) + x_pos)<<1U] = data[data_index];
			image_buffer[(((y_pos * DISPLAY_PIXEL_WIDTH) + x_pos)<<1U)+1U] = data[data_index+1U];
			data_index += 2U;
#endif
		}
	}
}
/* END OF FUNCTION*/

void St7735s_fill_area_bg(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	for(uint16_t x_pos = x; x_pos < (x+width); ++x_pos)
	{
		for(uint16_t y_pos = y; y_pos < (y+height); ++y_pos)
		{
			St7735s_set_bgpixel(x_pos,y_pos);
		}
	}
}
/* END OF FUNCTION*/

void St7735s_fill_display(void)
{
	dirty_marking.dirty_mark_all = true;

	for(uint16_t pixel_pos = 0U; pixel_pos < IMAGE_BUFFER_SIZE; ++pixel_pos)
	{
		image_buffer[pixel_pos] = colour_ptr[0U];
		image_buffer[pixel_pos] = colour_ptr[1U];
	}
}
/* END OF FUNCTION*/

void St7735s_sleep_display(void)
{
	static const uint8_t SLEEP_buf[] = {SLPIN};
	St7735s_write_cmd_buf(SLEEP_buf, sizeof(SLEEP_buf));

	Delay_ms(120U);
}
/* END OF FUNCTION*/

void St7735s_wake_display(void)
{
	static const uint8_t wake_buf[] = {SLPOUT};
	St7735s_write_cmd_buf(wake_buf, sizeof(wake_buf));

	Delay_ms(120U);
}
/* END OF FUNCTION*/

void St7735s_display_on(void)
{
	static const uint8_t on_buf[] = {DISPON};
	St7735s_write_cmd_buf(on_buf, sizeof(on_buf));
}
/* END OF FUNCTION*/

void St7735s_display_off(void)
{
	static const uint8_t off_buf[] = {DISPOFF};
	St7735s_write_cmd_buf(off_buf, sizeof(off_buf));
}
/* END OF FUNCTION*/

void St7735s_inversion_on(void)
{
	static const uint8_t on_buf[] = {INVON};
	St7735s_write_cmd_buf(on_buf, sizeof(on_buf));
}
/* END OF FUNCTION*/

void St7735s_inversion_off(void)
{
	static const uint8_t off_buf[] = {INVOFF};
	St7735s_write_cmd_buf(off_buf, sizeof(off_buf));
}
/* END OF FUNCTION*/

