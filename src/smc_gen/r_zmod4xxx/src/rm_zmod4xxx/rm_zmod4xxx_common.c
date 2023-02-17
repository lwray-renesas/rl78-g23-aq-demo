
/*************************************************
 * インクルード
 *************************************************/
#include "r_smc_entry.h"
#include "rm_zmod4xxx_common.h"
extern void delay_wait(uint32_t count);

/*************************************************
 * マクロ定義
 *************************************************/
#define ZMOD4XXX_PRV_OVERHEAD_CYCLES    (1000)    /* R_BSP_SoftwareDelay() overhead per call */
#define ZMOD4XXX_PRV_OVERHEAD_CYCLES_64 (1000)    /* R_BSP_SoftwareDelay() overhead per call using 64-bit ints */
#define FRQSEL                          (*(volatile __near unsigned char  *)0xC2)
#define CPU_CYCLES_PER_LOOP             (6)

/*************************************************
 * ファイル内グローバル変数
 *************************************************/
/* 遅延時間定義テーブル */
extern unsigned long long bsp_delay_time[];

/*************************************************
 * 関数定義
 *************************************************/
/***********************************************************************************************************************
* Function Name: delay_wait
* Description  : This asm loop executes a known number (5) of CPU cycles. If a value of '4' is passed
*                in as an argument, then this function would consume 20 CPU cycles before returning.
* Arguments    : loop_cnt - A single 32-bit value is provided as the number of loops to execute.
*              :
* Return Value : None
***********************************************************************************************************************/
/*
* 指定した時間だけ遅延させる
* @retval 1: 正常
* @retval 0: エラー
*/
uint8_t R_ZMOD4XXX_SoftwareDelay(uint32_t delay, zmod4xxx_delay_units_t units)
{
    volatile uint32_t fclk_rate;
    volatile uint32_t delay_cycles;
    volatile uint32_t loop_cnt;
    volatile unsigned long long loop_cnt_64;
    volatile unsigned long long delay_cycles_64;

    fclk_rate = R_BSP_GetFclkFreqHz();  /* Get the current ICLK frequency */

    /*
     * In order to handle all possible combinations of delay/ICLK it is necessary to use 64-bit
     * integers (not all MCUs have floating point support). However, there is no native hw support
     * for 64 bit integers so it requires many more clock cycles. This is not an issue if the
     * requested delay is long enough and the ICLK is fast, but for delays in the low microseconds
     * and/or a slow ICLK we use 32 bit integers to reduce the overhead cycles of this function
     * by approximately a third and stand the best chance of achieving the requested delay.
     */
    if ((units == ZMOD4XXX_DELAY_MICROSECS) &&
        (delay <= (0xFFFFFFFFUL / fclk_rate)) )  /* Ensure (fclk_rate * delay) will not exceed 32 bits */
    {
        delay_cycles = ((fclk_rate * delay) / bsp_delay_time[units]);

        if (delay_cycles > ZMOD4XXX_PRV_OVERHEAD_CYCLES)
        {
            delay_cycles -= ZMOD4XXX_PRV_OVERHEAD_CYCLES;
        }
        else
        {
            delay_cycles = 0;
        }

        loop_cnt = delay_cycles / CPU_CYCLES_PER_LOOP;

        if (0 == loop_cnt)
        {
            /* The requested delay is too large/small for the current ICLK. Return false which
             * also results in the minimum possible delay. */
            return 0;
        }
    }
    else
    {
        /* Casting is valid because it matches the type to the right side or argument. */
        delay_cycles_64 = (((unsigned long long)fclk_rate * (unsigned long long)delay) / bsp_delay_time[units]);

        if (delay_cycles_64 > ZMOD4XXX_PRV_OVERHEAD_CYCLES_64)
        {
            delay_cycles_64 -= ZMOD4XXX_PRV_OVERHEAD_CYCLES_64;
        }
        else
        {
            delay_cycles = 0;
        }

        loop_cnt_64 = delay_cycles_64 / CPU_CYCLES_PER_LOOP;

        if ((loop_cnt_64 > 0xFFFFFFFFUL) || (0 == loop_cnt_64))
        {
            /* The requested delay is too large/small for the current ICLK. Return false which
             * also results in the minimum possible delay. */
            return 0;
        }

        /* Casting is valid because it matches the type to the right side or argument. */
        loop_cnt = (uint32_t)loop_cnt_64;
    }

    delay_wait(loop_cnt);

    return 1;
} /* End of function R_BSP_SoftwareDelay() */
