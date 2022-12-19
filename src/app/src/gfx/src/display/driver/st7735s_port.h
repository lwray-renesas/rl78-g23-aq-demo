/**
 * @file st7735s_port.h
 * @brief the header file for the st7735s controller simple source for the porting layer.
 * @note This source ONLY supports 8bit SPI control mode & remember to set the CONFIG_SPI_INTEGRATED_CS macro to fit the applications available HW.
 */

#ifndef ST7735S_PORT_H_
#define ST7735S_PORT_H_

#include "r_smc_entry.h"

#if defined(__clang__) || defined(__GNUC__)

/** @brief Inline assembly used for nop.*/
#define ST7735S_NOP()				__asm__(" NOP")
/** @brief Inline assembly used for putting device in low power mode when performing blocking operations.*/
#define ST7735S_SLEEP()				__asm__(" HALT")

#elif defined(__ICCRL78__)

/** @brief Inline assembly used for nop.*/
#define ST7735S_NOP()				__no_operation()
/** @brief Inline assembly used for putting device in low power mode when performing blocking operations.*/
#define ST7735S_SLEEP()				__halt()

#else

/** @brief Inline assembly used for nop - you could replace this with a yield call in rtos applications*/
#define ST7735S_NOP()				__nop()
/** @brief Inline assembly used for putting device in low power mode when performing blocking operations.*/
#define ST7735S_SLEEP()				__halt()

#endif

#define DC_high()	 {P14_bit.no0 = 1U;}
#define DC_low()	 {P14_bit.no0 = 0U;}
#define Reset_high() {P0_bit.no2 = 1U;}
#define Reset_low()  {P0_bit.no2 = 0U;}
#define CS_high()    {P0_bit.no3 = 1U;}
#define CS_low()     {P0_bit.no3 = 0U;}

/** @brief tx_buf must satisfy uint8_t const * const & tx_num must satisfy uint16_t*/
#define Spi_write_block(tx_buf, tx_num)	{R_Config_CSI30_Send_app(tx_buf, tx_num);}

/** @brief Implements milli-second resolution delay*/
static inline void Delay_ms(uint16_t ms)
{
	if(ms > 0U)
	{
		TDR04 = (ms > 1U) ? (ms << 2U)-1U : 0U;

		TMMK04 = 1U;    /* disable INTTM02 interrupt */
		TMIF04 = 0U;    /* clear INTTM02 interrupt flag */

		TS0 |= _0010_TAU_CH4_START_TRG_ON;

		while(0U == TMIF04)
		{
			ST7735S_SLEEP();
		}

		TT0 |= _0010_TAU_CH4_STOP_TRG_ON;

		TMIF04 = 0U;    /* clear INTTM02 interrupt flag */
	}
}
/* END OF FUNCTION*/

#endif /* ST7735S_PORT_H_ */
