
/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
* Macro definitions
 *********************************************************************************************************************/
 /* Include guard */
#ifndef RM_ZMOD4XXX_COMMON_H
#define RM_ZMOD4XXX_COMMON_H

/* NOP(Assembler) */
#if defined(__CCRL__)
#define	BSP_NOP()           __nop()                     /* NOP命令 */
#elif defined(__ICCRL78__)
#define BSP_NOP     (__no_operation)
#endif

/* Available delay units. */
// ★
// RXから流用のまま、BSP_DELAY_MICROSECS = 1000000 を
// enum 定義に使用すると、intのキャパオーバーでコンパイルエラーになる。
// よって、このenumから、別の配列を参照して、1000000/1000/1 の時間を取得することとする。
typedef enum
{
    ZMOD4XXX_DELAY_SECS = 0,             // Requested delay amount is in seconds
    ZMOD4XXX_DELAY_MILLISECS,            // Requested delay amount is in milliseconds
    ZMOD4XXX_DELAY_MICROSECS             // Requested delay amount is in microseconds
} zmod4xxx_delay_units_t;

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
// ★
// R_BSP_SoftwareDelay()の戻り値は、RXでは、bool を使用しているが、
// CCRL ではコンパイラバージョンにより、コンパイルエラーになってしまう。
// とりあえずは環境によらず、コンパイルできる uint8_t に変更している。
uint8_t R_ZMOD4XXX_SoftwareDelay(uint32_t delay, zmod4xxx_delay_units_t units);

#endif	// #define RM_ZMOD4XXX_COMMON_H
