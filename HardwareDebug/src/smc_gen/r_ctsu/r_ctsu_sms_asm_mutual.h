/*
 * SMSASM V1.00.00.01 [29 May 2020]
 * assembled at Thu Dec 15 12:49:41 2022
 */

/* psection */
#if !defined(SC_SMSASM_MUTUAL)
#define SC_SMSASM_MUTUAL

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page1 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page1                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[1])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[6])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[7])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page2 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page2                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[1])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[2])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[7])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  
/*---------------------------------------------------*/

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page3 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page3                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[1])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[2])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[5])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  
/*---------------------------------------------------*/

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page4 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page4                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[1])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[2])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[3])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  
/*---------------------------------------------------*/

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page5 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page5                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[1])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[2])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[3])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  
/*---------------------------------------------------*/

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page6 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page6                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[1])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[2])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[3])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  
/*---------------------------------------------------*/

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page7 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page7                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[1])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[2])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[3])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  
/*---------------------------------------------------*/

/*---------------------------------------------------*/
/* Define SMS General Register Setting Page8 */
/*---------------------------------------------------*/
#define sms_greg_mutual_page8                  \
0x0000                              ,   /*  SMSG0   */  \
(uint16_t)(&g_ctsu_sms_work[0])     ,   /*  SMSG1   */  \
(uint16_t)(&g_ctsu_sms_work[5])     ,   /*  SMSG2   */  \
(uint16_t)(&g_ctsu_sms_work[2])     ,   /*  SMSG3   */  \
(uint16_t)(&g_ctsu_sms_work[4])     ,   /*  SMSG4   */  \
0x0000                              ,   /*  SMSG5   */  \
0x0000                              ,   /*  SMSG6   */  \
0x0000                              ,   /*  SMSG7   */  \
0x0000                              ,   /*  SMSG8   */  \
0x0000                              ,   /*  SMSG9   */  \
(uint16_t)(&g_ctsu_sms_threshold)   ,   /*  SMSG10  */  \
(uint16_t)(&g_ctsu_sms_result)      ,   /*  SMSG11  */  \
0x0000                              ,   /*  SMSG12  */  \
(uint16_t)(&SMSG2)                  ,   /*  SMSG13  */  \
0x0001                              ,   /*  SMSG14  */  \
0xFFFF                                  /*  SMSG15  */  
/*---------------------------------------------------*/

/*----------------------------------------------------*/    
/* Define SMS Program for Initialize                  */
/*----------------------------------------------------*/    
/* end psection */

#define SIZEOF_sms_init_mutual_program (3)

#define sms_init_mutual_program \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04  /*  2: WHILE1  [SMSG13+4].0 */

#define SIZEOF_sms_prog_mutual_page1 (30)

#define sms_prog_mutual_page1 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x3366, /*  3: MOVW    SMSG6, [SMSG3+6] */ \
        0x3670, /*  4: MOVW    SMSG7, [SMSG6+0] */ \
        0x2b70, /*  5: MOVW    [SMSG11+0], SMSG7 */ \
        0x3352, /*  6: MOVW    SMSG5, [SMSG3+2] */ \
        0x3364, /*  7: MOVW    SMSG6, [SMSG3+4] */ \
        0x36c2, /*  8: MOVW    SMSG12, [SMSG6+2] */ \
        0x7651, /*  9: SUBW    SMSG6, SMSG5 */ \
        0x3692, /* 10: MOVW    SMSG9, [SMSG6+2] */ \
        0x7972, /* 11: CMPW    SMSG9, SMSG7 */ \
        0x8020, /* 12: BC      $2 */ \
        0x8fc3, /* 13: BNZ     $-4 */ \
        0x3686, /* 14: MOVW    SMSG8, [SMSG6+6] */ \
        0x7791, /* 15: SUBW    SMSG7, SMSG9 */ \
        0x7891, /* 16: SUBW    SMSG8, SMSG9 */ \
        0x3290, /* 17: MOVW    SMSG9, [SMSG2+0] */ \
        0x3410, /* 18: MOVW    SMSG1, [SMSG4+0] */ \
        0x7990, /* 19: ADDW    SMSG9, SMSG9 */ \
        0x7782, /* 20: CMPW    SMSG7, SMSG8 */ \
        0x8030, /* 21: BC      $3 */ \
        0x7781, /* 22: SUBW    SMSG7, SMSG8 */ \
        0x79e0, /* 23: ADDW    SMSG9, SMSG14 */ \
        0x7770, /* 24: ADDW    SMSG7, SMSG7 */ \
        0x71e1, /* 25: SUBW    SMSG1, SMSG14 */ \
        0x8f93, /* 26: BNZ     $-7 */ \
        0x3680, /* 27: MOVW    SMSG8, [SMSG6+0] */ \
        0x7ff2, /* 28: CMPW    SMSG15, SMSG15 */ \
        0x8e32  /* 29: BZ      $-29 */

#define SIZEOF_sms_prog_mutual_page2 (30)

#define sms_prog_mutual_page2 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x3674, /*  3: MOVW    SMSG7, [SMSG6+4] */ \
        0x7781, /*  4: SUBW    SMSG7, SMSG8 */ \
        0x3280, /*  5: MOVW    SMSG8, [SMSG2+0] */ \
        0x3432, /*  6: MOVW    SMSG3, [SMSG4+2] */ \
        0x7803, /*  7: SHRW    SMSG8 */ \
        0x7903, /*  8: SHRW    SMSG9 */ \
        0x8021, /*  9: BNC     $2 */ \
        0x7870, /* 10: ADDW    SMSG8, SMSG7 */ \
        0x73e1, /* 11: SUBW    SMSG3, SMSG14 */ \
        0x8fb3, /* 12: BNZ     $-5 */ \
        0x3690, /* 13: MOVW    SMSG9, [SMSG6+0] */ \
        0x7890, /* 14: ADDW    SMSG8, SMSG9 */ \
        0x8050, /* 15: BC      $5 */ \
        0x3b50, /* 16: MOVW    SMSG5, [SMSG11+0] */ \
        0x75c2, /* 17: CMPW    SMSG5, SMSG12 */ \
        0x8030, /* 18: BC      $3 */ \
        0x8022, /* 19: BZ      $2 */ \
        0x3486, /* 20: MOVW    SMSG8, [SMSG4+6] */ \
        0x3250, /* 21: MOVW    SMSG5, [SMSG2+0] */ \
        0x1157, /* 22: MOV     SMSG5, [SMSG1+7] */ \
        0x7502, /* 23: CMPW    SMSG5, SMSG0 */ \
        0x8023, /* 24: BNZ     $2 */ \
        0x1151, /* 25: MOV     SMSG5, [SMSG1+1] */ \
        0x75e1, /* 26: SUBW    SMSG5, SMSG14 */ \
        0x0157, /* 27: MOV     [SMSG1+7], SMSG5 */ \
        0x7ff2, /* 28: CMPW    SMSG15, SMSG15 */ \
        0x8e32  /* 29: BZ      $-29 */

#define SIZEOF_sms_prog_mutual_page3 (21)

#define sms_prog_mutual_page3 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x6107, /*  3: MOV1    SCY, [SMSG1+7].0 */ \
        0x8070, /*  4: BC      $7 */ \
        0x3296, /*  5: MOVW    SMSG9, [SMSG2+6] */ \
        0x7891, /*  6: SUBW    SMSG8, SMSG9 */ \
        0x2206, /*  7: MOVW    [SMSG2+6], SMSG0 */ \
        0x80a0, /*  8: BC      $10 */ \
        0x2286, /*  9: MOVW    [SMSG2+6], SMSG8 */ \
        0x8081, /* 10: BNC     $8 */ \
        0x2286, /* 11: MOVW    [SMSG2+6], SMSG8 */ \
        0x3460, /* 12: MOVW    SMSG6, [SMSG4+0] */ \
        0x3472, /* 13: MOVW    SMSG7, [SMSG4+2] */ \
        0x2674, /* 14: MOVW    [SMSG6+4], SMSG7 */ \
        0x3474, /* 15: MOVW    SMSG7, [SMSG4+4] */ \
        0x2672, /* 16: MOVW    [SMSG6+2], SMSG7 */ \
        0xf000, /* 17: FINISH */ \
        0x3280, /* 18: MOVW    SMSG8, [SMSG2+0] */ \
        0x7ff2, /* 19: CMPW    SMSG15, SMSG15 */ \
        0x8ec2  /* 20: BZ      $-20 */

#define SIZEOF_sms_prog_mutual_page4 (32)

#define sms_prog_mutual_page4 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x1185, /*  3: MOV     SMSG8, [SMSG1+5] */ \
        0x3b92, /*  4: MOVW    SMSG9, [SMSG11+2] */ \
        0x3b62, /*  5: MOVW    SMSG6, [SMSG11+2] */ \
        0x3276, /*  6: MOVW    SMSG7, [SMSG2+6] */ \
        0x7802, /*  7: CMPW    SMSG8, SMSG0 */ \
        0x8052, /*  8: BZ      $5 */ \
        0x7603, /*  9: SHRW    SMSG6 */ \
        0x7703, /* 10: SHRW    SMSG7 */ \
        0x78e1, /* 11: SUBW    SMSG8, SMSG14 */ \
        0x8fb1, /* 12: BNC     $-5 */ \
        0x7961, /* 13: SUBW    SMSG9, SMSG6 */ \
        0x7970, /* 14: ADDW    SMSG9, SMSG7 */ \
        0x2b92, /* 15: MOVW    [SMSG11+2], SMSG9 */ \
        0x3260, /* 16: MOVW    SMSG6, [SMSG2+0] */ \
        0x1166, /* 17: MOV     SMSG6, [SMSG1+6] */ \
        0x76e0, /* 18: ADDW    SMSG6, SMSG14 */ \
        0x32c4, /* 19: MOVW    SMSG12, [SMSG2+4] */ \
        0x7602, /* 20: CMPW    SMSG6, SMSG0 */ \
        0x8072, /* 21: BZ      $7 */ \
        0x7803, /* 22: SHRW    SMSG8 */ \
        0x7903, /* 23: SHRW    SMSG9 */ \
        0x8021, /* 24: BNC     $2 */ \
        0x78c0, /* 25: ADDW    SMSG8, SMSG12 */ \
        0x76e1, /* 26: SUBW    SMSG6, SMSG14 */ \
        0x8f91, /* 27: BNC     $-7 */ \
        0x3b64, /* 28: MOVW    SMSG6, [SMSG11+4] */ \
        0x3b76, /* 29: MOVW    SMSG7, [SMSG11+6] */ \
        0x7ff2, /* 30: CMPW    SMSG15, SMSG15 */ \
        0x8e12  /* 31: BZ      $-31 */

#define SIZEOF_sms_prog_mutual_page5 (32)

#define sms_prog_mutual_page5 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x7970, /*  3: ADDW    SMSG9, SMSG7 */ \
        0x7860, /*  4: ADDW    SMSG8, SMSG6 */ \
        0x8021, /*  5: BNC     $2 */ \
        0x79e0, /*  6: ADDW    SMSG9, SMSG14 */ \
        0x34c0, /*  7: MOVW    SMSG12, [SMSG4+0] */ \
        0x7cb0, /*  8: ADDW    SMSG12, SMSG11 */ \
        0x6c04, /*  9: MOV1    SCY, [SMSG12+4].0 */ \
        0x80c0, /* 10: BC      $12 */ \
        0x3c60, /* 11: MOVW    SMSG6, [SMSG12+0] */ \
        0x3370, /* 12: MOVW    SMSG7, [SMSG3+0] */ \
        0x7702, /* 13: CMPW    SMSG7, SMSG0 */ \
        0x80d2, /* 14: BZ      $13 */ \
        0x7670, /* 15: ADDW    SMSG6, SMSG7 */ \
        0x8081, /* 16: BNC     $8 */ \
        0x2c92, /* 17: MOVW    [SMSG12+2], SMSG9 */ \
        0x2c00, /* 18: MOVW    [SMSG12+0], SMSG0 */ \
        0x2b04, /* 19: MOVW    [SMSG11+4], SMSG0 */ \
        0x2b06, /* 20: MOVW    [SMSG11+6], SMSG0 */ \
        0x8070, /* 21: BC      $7 */ \
        0x3c92, /* 22: MOVW    SMSG9, [SMSG12+2] */ \
        0x8fb0, /* 23: BC      $-5 */ \
        0x2c60, /* 24: MOVW    [SMSG12+0], SMSG6 */ \
        0x2b84, /* 25: MOVW    [SMSG11+4], SMSG8 */ \
        0x2b96, /* 26: MOVW    [SMSG11+6], SMSG9 */ \
        0x3c92, /* 27: MOVW    SMSG9, [SMSG12+2] */ \
        0x3a60, /* 28: MOVW    SMSG6, [SMSG10+0] */ \
        0x3a72, /* 29: MOVW    SMSG7, [SMSG10+2] */ \
        0x7ff2, /* 30: CMPW    SMSG15, SMSG15 */ \
        0x8e12  /* 31: BZ      $-31 */

#define SIZEOF_sms_prog_mutual_page6 (32)

#define sms_prog_mutual_page6 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x3b82, /*  3: MOVW    SMSG8, [SMSG11+2] */ \
        0x1c56, /*  4: MOV     SMSG5, [SMSG12+6] */ \
        0x6c04, /*  5: MOV1    SCY, [SMSG12+4].0 */ \
        0x80b0, /*  6: BC      $11 */ \
        0x7790, /*  7: ADDW    SMSG7, SMSG9 */ \
        0x8101, /*  8: BNC     $16 */ \
        0x7872, /*  9: CMPW    SMSG8, SMSG7 */ \
        0x80e1, /* 10: BNC     $14 */ \
        0x7502, /* 11: CMPW    SMSG5, SMSG0 */ \
        0x80f3, /* 12: BNZ     $15 */ \
        0x4c04, /* 13: SET1    [SMSG12+4].0 */ \
        0x1152, /* 14: MOV     SMSG5, [SMSG1+2] */ \
        0x6202, /* 15: MOV1    SCY, [SMSG2+2].0 */ \
        0x80c0, /* 16: BC      $12 */ \
        0x7690, /* 17: ADDW    SMSG6, SMSG9 */ \
        0x8031, /* 18: BNC     $3 */ \
        0x7682, /* 19: CMPW    SMSG6, SMSG8 */ \
        0x8fa1, /* 20: BNC     $-6 */ \
        0x7502, /* 21: CMPW    SMSG5, SMSG0 */ \
        0x8053, /* 22: BNZ     $5 */ \
        0x5c04, /* 23: CLR1    [SMSG12+4].0 */ \
        0x1153, /* 24: MOV     SMSG5, [SMSG1+3] */ \
        0x6202, /* 25: MOV1    SCY, [SMSG2+2].0 */ \
        0x8020, /* 26: BC      $2 */ \
        0x75e1, /* 27: SUBW    SMSG5, SMSG14 */ \
        0x0c56, /* 28: MOV     [SMSG12+6], SMSG5 */ \
        0x3362, /* 29: MOVW    SMSG6, [SMSG3+2] */ \
        0x7ff2, /* 30: CMPW    SMSG15, SMSG15 */ \
        0x8e12  /* 31: BZ      $-31 */

#define SIZEOF_sms_prog_mutual_page7 (32)

#define sms_prog_mutual_page7 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x6c04, /*  3: MOV1    SCY, [SMSG12+4].0 */ \
        0x8021, /*  4: BNC     $2 */ \
        0x76e0, /*  5: ADDW    SMSG6, SMSG14 */ \
        0x1157, /*  6: MOV     SMSG5, [SMSG1+7] */ \
        0x7502, /*  7: CMPW    SMSG5, SMSG0 */ \
        0x80a3, /*  8: BNZ     $10 */ \
        0x3290, /*  9: MOVW    SMSG9, [SMSG2+0] */ \
        0x1194, /* 10: MOV     SMSG9, [SMSG1+4] */ \
        0x7962, /* 11: CMPW    SMSG9, SMSG6 */ \
        0x8030, /* 12: BC      $3 */ \
        0x5c44, /* 13: CLR1    [SMSG12+4].4 */ \
        0x8031, /* 14: BNC     $3 */ \
        0x4c44, /* 15: SET1    [SMSG12+4].4 */ \
        0x4170, /* 16: SET1    [SMSG1+0].7 */ \
        0x3260, /* 17: MOVW    SMSG6, [SMSG2+0] */ \
        0x2362, /* 18: MOVW    [SMSG3+2], SMSG6 */ \
        0x3476, /* 19: MOVW    SMSG7, [SMSG4+6] */ \
        0x77e1, /* 20: SUBW    SMSG7, SMSG14 */ \
        0x7702, /* 21: CMPW    SMSG7, SMSG0 */ \
        0x8033, /* 22: BNZ     $3 */ \
        0x32c0, /* 23: MOVW    SMSG12, [SMSG2+0] */ \
        0x3474, /* 24: MOVW    SMSG7, [SMSG4+4] */ \
        0x2476, /* 25: MOVW    [SMSG4+6], SMSG7 */ \
        0x3462, /* 26: MOVW    SMSG6, [SMSG4+2] */ \
        0x7a60, /* 27: ADDW    SMSG10, SMSG6 */ \
        0x7660, /* 28: ADDW    SMSG6, SMSG6 */ \
        0x7660, /* 29: ADDW    SMSG6, SMSG6 */ \
        0x7b60, /* 30: ADDW    SMSG11, SMSG6 */ \
        0x8e13  /* 31: BNZ     $-31 */

#define SIZEOF_sms_prog_mutual_page8 (32)

#define sms_prog_mutual_page8 \
        0x2df4, /*  0: MOVW    [SMSG13+4], SMSG15 */ \
        0xf002, /*  1: DTCTRG */ \
        0xad04, /*  2: WHILE1  [SMSG13+4].0 */ \
        0x7c02, /*  3: CMPW    SMSG12, SMSG0 */ \
        0x80d3, /*  4: BNZ     $13 */ \
        0x33a4, /*  5: MOVW    SMSG10, [SMSG3+4] */ \
        0x33b6, /*  6: MOVW    SMSG11, [SMSG3+6] */ \
        0x3494, /*  7: MOVW    SMSG9, [SMSG4+4] */ \
        0x5920, /*  8: CLR1    [SMSG9+0].2 */ \
        0x4920, /*  9: SET1    [SMSG9+0].2 */ \
        0x7603, /* 10: SHRW    SMSG6 */ \
        0x7960, /* 11: ADDW    SMSG9, SMSG6 */ \
        0x3486, /* 12: MOVW    SMSG8, [SMSG4+6] */ \
        0x2980, /* 13: MOVW    [SMSG9+0], SMSG8 */ \
        0x3452, /* 14: MOVW    SMSG5, [SMSG4+2] */ \
        0x3286, /* 15: MOVW    SMSG8, [SMSG2+6] */ \
        0x0580, /* 16: MOV     [SMSG5+0], SMSG8 */ \
        0x3260, /* 17: MOVW    SMSG6, [SMSG2+0] */ \
        0x3272, /* 18: MOVW    SMSG7, [SMSG2+2] */ \
        0x2674, /* 19: MOVW    [SMSG6+4], SMSG7 */ \
        0x3274, /* 20: MOVW    SMSG7, [SMSG2+4] */ \
        0x2672, /* 21: MOVW    [SMSG6+2], SMSG7 */ \
        0x7c02, /* 22: CMPW    SMSG12, SMSG0 */ \
        0x8083, /* 23: BNZ     $8 */ \
        0x3490, /* 24: MOVW    SMSG9, [SMSG4+0] */ \
        0x6970, /* 25: MOV1    SCY, [SMSG9+0].7 */ \
        0x8030, /* 26: BC      $3 */ \
        0x6170, /* 27: MOV1    SCY, [SMSG1+0].7 */ \
        0x8031, /* 28: BNC     $3 */ \
        0x5170, /* 29: CLR1    [SMSG1+0].7 */ \
        0xf001, /* 30: WAKEUP */ \
        0xf000  /* 31: FINISH */

/* psection */

#endif /* SC_SMSASM_MUTUAL */
/* end psection */

