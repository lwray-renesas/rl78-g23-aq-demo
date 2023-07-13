/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
* THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
************************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup CTSU
 * @{
 **********************************************************************************************************************/

#ifndef R_CTSU_H
#define R_CTSU_H

#ifdef QE_TOUCH_CONFIGURATION
 #include "qe_touch_define.h"
#endif
#include "r_ctsu_config.h"
#include "r_ctsu_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if (defined(BSP_MCU_GROUP_RL78G22) || defined(BSP_MCU_GROUP_RL78G23))
#define BSP_FEATURE_CTSU_VERSION                  (2)  ///< CTSU IP version
#else
#define BSP_FEATURE_CTSU_VERSION                  (1)  ///< CTSU IP version
#endif

#if  (defined(BSP_MCU_GROUP_RL78G16))
#define CTSU_CFG_MCU_PROCESS_MF3                  (1)

#define CTSU_HAS_TXVSEL                           (1)
#define BSP_FEATURE_CTSU_HAS_TRMR                 (1)
/* For parts with CTSUCHAC2/3/4 and CTSUTRC2/3/4 registers (more than 16 TS pins) */
#if (BSP_FEATURE_CTSU_VERSION == 2)
#define BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT  (3)
#define BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT (3)
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
#define BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT  (2)
#define BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT (2)
#endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #define CTSU_CORRECTION_POINT_NUM        (12) ///< number of correction table
 #define CTSU_CORRCFC_POINT_NUM           (5)  ///< number of CFC correction table

 #define CTSU_DIAG_HIGH_CURRENT_SOURCE    (16) ///< number of high current source table at Diagnosis
 #define CTSU_DIAG_LOW_CURRENT_SOURCE     (10) ///< number of low current source table at Diagnosis
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
/* =========================================================================================================================== */
/* ================                                          R_CTSU1                                          ================ */
/* =========================================================================================================================== */

/* ========================================================  CTSUCR0 ========================================================= */
 #define CTSUCR0_IOC_Pos            (3UL)       /*!< CTSUIOC (Bit 3)                                        */
 #define CTSUCR0_IOC_Msk            (0x8UL)     /*!< CTSUIOC (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTSUCR1 ========================================================= */
 #define CTSUCR1_MD0_Pos            (6UL)       /*!< CTSUMD0 (Bit 6)                                        */
 #define CTSUCR1_MD0_Msk            (0x40UL)    /*!< CTSUMD0 (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTSUMCH0 ======================================================== */
 #define CTSUMCH_MCH0_Pos           (0UL)       /*!< CTSUMCH0 (Bit 0)                                       */
 #define CTSUMCH_MCH0_Msk           (0x1FUL)    /*!< CTSUMCH0 (Bitfield-Mask: 0x1F)                         */
/* ========================================================  CTSUMCH1 ======================================================== */
 #define CTSUMCH_MCH1_Pos           (0UL)       /*!< CTSUMCH1 (Bit 0)                                       */
 #define CTSUMCH_MCH1_Msk           (0x1FUL)    /*!< CTSUMCH1 (Bitfield-Mask: 0x1F)                         */
/* ========================================================  CTSUERRS ======================================================== */
 #define CTSUERRS_TSOD_Pos          (2UL)       /*!< CTSUTSOD (Bit 2)                                       */
 #define CTSUERRS_TSOD_Msk          (0x4UL)     /*!< CTSUTSOD (Bitfield-Mask: 0x01)                         */
 #define CTSUERRS_ALMES_Pos         (13UL)      /*!< CTSUALMES (Bit 13)                                     */
 #define CTSUERRS_ALMES_Msk         (0x2000UL)  /*!< CTSUALMES (Bitfield-Mask: 0x01)                        */
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
/* =========================================================================================================================== */
/* ================                                          R_CTSU2                                          ================ */
/* =========================================================================================================================== */

/* ========================================================  CTSUCRAL ======================================================== */
 #define CTSUCRA_STRT_Pos      (0UL)          /*!< STRT (Bit 0)                                          */
 #define CTSUCRA_STRT_Msk      (0x1UL)        /*!< STRT (Bitfield-Mask: 0x01)                            */
 #define CTSUCRA_CAP_Pos       (1UL)          /*!< CAP (Bit 1)                                           */
 #define CTSUCRA_CAP_Msk       (0x2UL)        /*!< CAP (Bitfield-Mask: 0x01)                             */
 #define CTSUCRA_SNZ_Pos       (2UL)          /*!< SNZ (Bit 2)                                           */
 #define CTSUCRA_SNZ_Msk       (0x4UL)        /*!< SNZ (Bitfield-Mask: 0x01)                             */
 #define CTSUCRA_CFCON_Pos     (3UL)          /*!< CFCON (Bit 3)                                         */
 #define CTSUCRA_CFCON_Msk     (0x8UL)        /*!< CFCON (Bitfield-Mask: 0x01)                           */
 #define CTSUCRA_INIT_Pos      (4UL)          /*!< INIT (Bit 4)                                          */
 #define CTSUCRA_INIT_Msk      (0x10UL)       /*!< INIT (Bitfield-Mask: 0x01)                            */
 #define CTSUCRA_PUMPON_Pos    (5UL)          /*!< PUMPON (Bit 5)                                        */
 #define CTSUCRA_PUMPON_Msk    (0x20UL)       /*!< PUMPON (Bitfield-Mask: 0x01)                          */
 #define CTSUCRA_TXVSEL_Pos    (6UL)          /*!< TXVSEL (Bit 6)                                        */
 #define CTSUCRA_TXVSEL_Msk    (0xc0UL)       /*!< TXVSEL (Bitfield-Mask: 0x03)                          */
 #define CTSUCRA_PON_Pos       (8UL)          /*!< PON (Bit 8)                                           */
 #define CTSUCRA_PON_Msk       (0x100UL)      /*!< PON (Bitfield-Mask: 0x01)                             */
 #define CTSUCRA_CSW_Pos       (9UL)          /*!< CSW (Bit 9)                                           */
 #define CTSUCRA_CSW_Msk       (0x200UL)      /*!< CSW (Bitfield-Mask: 0x01)                             */
 #define CTSUCRA_ATUNE0_Pos    (10UL)         /*!< ATUNE0 (Bit 10)                                       */
 #define CTSUCRA_ATUNE0_Msk    (0x400UL)      /*!< ATUNE0 (Bitfield-Mask: 0x01)                          */
 #define CTSUCRA_ATUNE1_Pos    (11UL)         /*!< ATUNE1 (Bit 11)                                       */
 #define CTSUCRA_ATUNE1_Msk    (0x800UL)      /*!< ATUNE1 (Bitfield-Mask: 0x01)                          */
 #define CTSUCRA_CLK_Pos       (12UL)         /*!< CLK (Bit 12)                                          */
 #define CTSUCRA_CLK_Msk       (0x3000UL)     /*!< CLK (Bitfield-Mask: 0x03)                             */
 #define CTSUCRA_MD0_Pos       (14UL)         /*!< MD0 (Bit 14)                                          */
 #define CTSUCRA_MD0_Msk       (0x4000UL)     /*!< MD0 (Bitfield-Mask: 0x01)                             */
 #define CTSUCRA_MD1_Pos       (15UL)         /*!< MD1 (Bit 15)                                          */
 #define CTSUCRA_MD1_Msk       (0x8000UL)     /*!< MD1 (Bitfield-Mask: 0x01)                             */
/* =======================================================  CTSUCRAH  ======================================================== */
 #define CTSUCRA_MD2_Pos       (0UL)          /*!< MD2 (Bit 16)                                          */
 #define CTSUCRA_MD2_Msk       (0x1UL)        /*!< MD2 (Bitfield-Mask: 0x01)                             */
 #define CTSUCRA_ATUNE2_Pos    (1UL)          /*!< ATUNE2 (Bit 17)                                       */
 #define CTSUCRA_ATUNE2_Msk    (0x2UL)        /*!< ATUNE2 (Bitfield-Mask: 0x01)                          */
 #define CTSUCRA_LOAD_Pos      (2UL)          /*!< LOAD (Bit 18)                                         */
 #define CTSUCRA_LOAD_Msk      (0xcUL)        /*!< LOAD (Bitfield-Mask: 0x03)                            */
 #define CTSUCRA_POSEL_Pos     (4UL)          /*!< POSEL (Bit 20)                                        */
 #define CTSUCRA_POSEL_Msk     (0x30UL)       /*!< POSEL (Bitfield-Mask: 0x03)                           */
 #define CTSUCRA_SDPSEL_Pos    (6UL)          /*!< SDPSEL (Bit 22)                                       */
 #define CTSUCRA_SDPSEL_Msk    (0x40UL)       /*!< SDPSEL (Bitfield-Mask: 0x01)                          */
 #define CTSUCRA_PCSEL_Pos     (7UL)          /*!< PCSEL (Bit 23)                                       */
 #define CTSUCRA_PCSEL_Msk     (0x80UL)       /*!< PCSEL (Bitfield-Mask: 0x01)                          */
 #define CTSUCRA_STCLK_Pos     (8UL)          /*!< STCLK (Bit 24)                                        */
 #define CTSUCRA_STCLK_Msk     (0x3f00UL)     /*!< STCLK (Bitfield-Mask: 0x3f)                           */
 #define CTSUCRA_DCMODE_Pos    (14UL)         /*!< DCMODE (Bit 30)                                       */
 #define CTSUCRA_DCMODE_Msk    (0x4000UL)     /*!< DCMODE (Bitfield-Mask: 0x01)                          */
 #define CTSUCRA_DCBACK_Pos    (15UL)         /*!< DCBACK (Bit 31)                                       */
 #define CTSUCRA_DCBACK_Msk    (0x8000UL)     /*!< DCBACK (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTSUCRBL ======================================================== */
 #define CTSUCRB_PRRATIO_Pos    (0UL)          /*!< PRRATIO (Bit 0)                                       */
 #define CTSUCRB_PRRATIO_Msk    (0xfUL)        /*!< PRRATIO (Bitfield-Mask: 0x0f)                         */
 #define CTSUCRB_PRMODE_Pos     (4UL)          /*!< PRMODE (Bit 4)                                        */
 #define CTSUCRB_PRMODE_Msk     (0x30UL)       /*!< PRMODE (Bitfield-Mask: 0x03)                          */
 #define CTSUCRB_SOFF_Pos       (6UL)          /*!< SOFF (Bit 6)                                          */
 #define CTSUCRB_SOFF_Msk       (0x40UL)       /*!< SOFF (Bitfield-Mask: 0x01)                            */
 #define CTSUCRB_PROFF_Pos      (7UL)          /*!< PROFF (Bit 7)                                         */
 #define CTSUCRB_PROFF_Msk      (0x80UL)       /*!< PROFF (Bitfield-Mask: 0x01)                           */
 #define CTSUCRB_SST_Pos        (8UL)          /*!< SST (Bit 8)                                           */
 #define CTSUCRB_SST_Msk        (0xff00UL)     /*!< SST (Bitfield-Mask: 0xff)                             */
/* =======================================================  CTSUCRBH  ======================================================== */
 #define CTSUCRB_SSMOD_Pos      (8UL)          /*!< SSMOD (Bit 24)                                        */
 #define CTSUCRB_SSMOD_Msk      (0x700UL)      /*!< SSMOD (Bitfield-Mask: 0x07)                           */
 #define CTSUCRB_SSCNT_Pos      (12UL)         /*!< SSCNT (Bit 28)                                        */
 #define CTSUCRB_SSCNT_Msk      (0x3000UL)     /*!< SSCNT (Bitfield-Mask: 0x03)                           */
/* ========================================================  CTSUMCHL ======================================================== */
 #define CTSUMCH_MCH0_Pos    (0UL)       /*!< MCH0 (Bit 0)                                          */
 #define CTSUMCH_MCH0_Msk    (0x3fUL)    /*!< MCH0 (Bitfield-Mask: 0x3f)                            */
 #define CTSUMCH_MCH1_Pos    (8UL)       /*!< MCH1 (Bit 8)                                          */
 #define CTSUMCH_MCH1_Msk    (0x3f00UL)  /*!< MCH1 (Bitfield-Mask: 0x3f)                            */
/* =======================================================  CTSUMCHH  ======================================================== */
 #define CTSUMCH_MCA0_Pos    (0UL)       /*!< MCA0 (Bit 16)                                         */
 #define CTSUMCH_MCA0_Msk    (0x1UL)     /*!< MCA0 (Bitfield-Mask: 0x01)                            */
 #define CTSUMCH_MCA1_Pos    (1UL)       /*!< MCA1 (Bit 17)                                         */
 #define CTSUMCH_MCA1_Msk    (0x2UL)     /*!< MCA1 (Bitfield-Mask: 0x01)                            */
 #define CTSUMCH_MCA2_Pos    (2UL)       /*!< MCA2 (Bit 18)                                         */
 #define CTSUMCH_MCA2_Msk    (0x4UL)     /*!< MCA2 (Bitfield-Mask: 0x01)                            */
 #define CTSUMCH_MCA3_Pos    (3UL)       /*!< MCA3 (Bit 19)                                         */
 #define CTSUMCH_MCA3_Msk    (0x8UL)     /*!< MCA3 (Bitfield-Mask: 0x01)                            */
/* ======================================================  CTSUCHACAL  ======================================================= */
/* ======================================================  CTSUCHACAH  ======================================================= */
/* ======================================================  CTSUCHACBL  ======================================================= */
/* ======================================================  CTSUCHTRCAL  ====================================================== */
/* ======================================================  CTSUCHTRCAH  ====================================================== */
/* ======================================================  CTSUCHTRCBL  ====================================================== */
/* ========================================================  CTSUSRL ========================================================= */
 #define CTSUSR_MFC_Pos            (0UL)        /*!< MFC (Bit 0)                                           */
 #define CTSUSR_MFC_Msk            (0x3UL)      /*!< MFC (Bitfield-Mask: 0x03)                             */
 #define CTSUSR_ICOMPRST_Pos       (5UL)        /*!< ICOMPRST (Bit 5)                                      */
 #define CTSUSR_ICOMPRST_Msk       (0x20UL)     /*!< ICOMPRST (Bitfield-Mask: 0x01)                        */
 #define CTSUSR_ICOMP1_Pos         (6UL)        /*!< ICOMP1 (Bit 6)                                        */
 #define CTSUSR_ICOMP1_Msk         (0x40UL)     /*!< ICOMP1 (Bitfield-Mask: 0x01)                          */
 #define CTSUSR_ICOMP0_Pos         (7UL)        /*!< ICOMP0 (Bit 7)                                        */
 #define CTSUSR_ICOMP0_Msk         (0x80UL)     /*!< ICOMP0 (Bitfield-Mask: 0x01)                          */
 #define CTSUSR_STC_Pos            (8UL)        /*!< STC (Bit 8)                                           */
 #define CTSUSR_STC_Msk            (0x700UL)    /*!< STC (Bitfield-Mask: 0x07)                             */
 #define CTSUSR_DTSR_Pos           (12UL)       /*!< DTSR (Bit 12)                                         */
 #define CTSUSR_DTSR_Msk           (0x1000UL)   /*!< DTSR (Bitfield-Mask: 0x01)                            */
 #define CTSUSR_SENSOVF_Pos        (13UL)       /*!< SENSOVF (Bit 13)                                      */
 #define CTSUSR_SENSOVF_Msk        (0x2000UL)   /*!< SENSOVF (Bitfield-Mask: 0x01)                         */
 #define CTSUSR_PS_Pos             (15UL)       /*!< PS (Bit 15)                                           */
 #define CTSUSR_PS_Msk             (0x8000UL)   /*!< PS (Bitfield-Mask: 0x01)                              */
/* ========================================================  CTSUSRH  ======================================================== */
/* ========================================================  CTSUSO0  ======================================================== */
 #define CTSUSO_SO_Pos             (0UL)          /*!< SO (Bit 0)                                            */
 #define CTSUSO_SO_Msk             (0x3ffUL)      /*!< SO (Bitfield-Mask: 0x3ff)                             */
 #define CTSUSO_SNUM_Pos           (10UL)         /*!< SNUM (Bit 10)                                         */
 #define CTSUSO_SNUM_Msk           (0x3fc00UL)    /*!< SNUM (Bitfield-Mask: 0xff)                            */
/* ========================================================  CTSUSO1  ======================================================== */
 #define CTSUSO_SSDIV_Pos          (4UL)          /*!< SSDIV (Bit 20)                                        */
 #define CTSUSO_SSDIV_Msk          (0xf0UL)       /*!< SSDIV (Bitfield-Mask: 0x0f)                           */
 #define CTSUSO_SDPA_Pos           (8UL)          /*!< SDPA (Bit 24)                                         */
 #define CTSUSO_SDPA_Msk           (0xff00UL)     /*!< SDPA (Bitfield-Mask: 0xff)                            */
/* ========================================================  CTSUSC  ========================================================= */
 #define CTSUSCNT_SENSCNT_Pos      (0UL)          /*!< SENSCNT (Bit 0)                                       */
 #define CTSUSCNT_SENSCNT_Msk      (0xffffUL)     /*!< SENSCNT (Bitfield-Mask: 0xffff)                       */
/* =======================================================  CTSUDBGR0  ======================================================= */
 #define CTSUCALIB_TSOD_Pos        (2UL)          /*!< TSOD (Bit 2)                                          */
 #define CTSUCALIB_TSOD_Msk        (0x4UL)        /*!< TSOD (Bitfield-Mask: 0x01)                            */
 #define CTSUCALIB_DRV_Pos         (3UL)          /*!< DRV (Bit 3)                                           */
 #define CTSUCALIB_DRV_Msk         (0x8UL)        /*!< DRV (Bitfield-Mask: 0x01)                             */
 #define CTSUCALIB_CLKSEL_Pos       (4UL)          /*!< CLKSEL (Bit 4)                                        */
 #define CTSUCALIB_CLKSEL_Msk       (0x30UL)       /*!< CLKSEL (Bitfield-Mask: 0x03)                          */
 #define CTSUCALIB_SUCLKEN_Pos     (6UL)          /*!< SUCLKEN (Bit 6)                                       */
 #define CTSUCALIB_SUCLKEN_Msk     (0x40UL)       /*!< SUCLKEN (Bitfield-Mask: 0x01)                         */
 #define CTSUCALIB_TSOC_Pos        (7UL)          /*!< TSOC (Bit 7)                                          */
 #define CTSUCALIB_TSOC_Msk        (0x80UL)       /*!< TSOC (Bitfield-Mask: 0x01)                            */
 #define CTSUCALIB_CNTRDSEL_Pos     (8UL)          /*!< CNTRDSEL (Bit 8)                                      */
 #define CTSUCALIB_CNTRDSEL_Msk     (0x100UL)      /*!< CNTRDSEL (Bitfield-Mask: 0x01)                        */
 #define CTSUCALIB_IOC_Pos         (9UL)          /*!< IOC (Bit 9)                                           */
 #define CTSUCALIB_IOC_Msk         (0x200UL)      /*!< IOC (Bitfield-Mask: 0x01)                             */
 #define CTSUCALIB_DCOFF_Pos       (11UL)         /*!< DCOFF (Bit 11)                                        */
 #define CTSUCALIB_DCOFF_Msk       (0x800UL)      /*!< DCOFF (Bitfield-Mask: 0x01)                           */
/* =======================================================  CTSUDBGR1  ======================================================= */
 #define CTSUCALIB_DACMSEL_Pos     (8UL)          /*!< DACMSEL (Bit 24)                                      */
 #define CTSUCALIB_DACMSEL_Msk     (0x100UL)      /*!< DACMSEL (Bitfield-Mask: 0x01)                         */
 #define CTSUCALIB_DACCARRY_Pos    (9UL)          /*!< DACCARRY (Bit 25)                                     */
 #define CTSUCALIB_DACCARRY_Msk    (0x200UL)      /*!< DACCARRY (Bitfield-Mask: 0x01)                        */
 #define CTSUCALIB_SUMSEL_Pos      (26UL)         /*!< SUMSEL (Bit 26)                                       */
 #define CTSUCALIB_SUMSEL_Msk      (0x400UL)  /*!< SUMSEL (Bitfield-Mask: 0x01)                              */
 #define CTSUCALIB_SUCARRY_Pos     (11UL)         /*!< SUCARRY (Bit 27)                                      */
 #define CTSUCALIB_SUCARRY_Msk     (0x800UL)      /*!< SUCARRY (Bitfield-Mask: 0x01)                         */
 #define CTSUCALIB_DACCLK_Pos      (12UL)         /*!< DACCLK (Bit 28)                                       */
 #define CTSUCALIB_DACCLK_Msk      (0x1000UL)     /*!< DACCLK (Bitfield-Mask: 0x01)                          */
 #define CTSUCALIB_CCOCLK_Pos      (13UL)         /*!< CCOCLK (Bit 29)                                       */
 #define CTSUCALIB_CCOCLK_Msk      (0x2000UL)     /*!< CCOCLK (Bitfield-Mask: 0x01)                          */
 #define CTSUCALIB_CCOCALIB_Pos    (14UL)         /*!< CCOCALIB (Bit 30)                                     */
 #define CTSUCALIB_CCOCALIB_Msk    (0x4000UL)     /*!< CCOCALIB (Bitfield-Mask: 0x01)                        */
 #define CTSUCALIB_TXREV_Pos       (15UL)         /*!< TXREV (Bit 31)                                        */
 #define CTSUCALIB_TXREV_Msk       (0x8000UL) /*!< TXREV (Bitfield-Mask: 0x01)                               */
/* ======================================================  CTSUSUCLK0  ======================================================= */
 #define CTSUSUCLKA_SUADJ0_Pos      (0UL)          /*!< SUADJ0 (Bit 0)                                        */
 #define CTSUSUCLKA_SUADJ0_Msk      (0xffUL)       /*!< SUADJ0 (Bitfield-Mask: 0xff)                          */
 #define CTSUSUCLKA_SUMULTI0_Pos    (8UL)          /*!< SUMULTI0 (Bit 8)                                      */
 #define CTSUSUCLKA_SUMULTI0_Msk    (0xff00UL)     /*!< SUMULTI0 (Bitfield-Mask: 0xff)                        */
/* ======================================================  CTSUSUCLK1  ======================================================= */
 #define CTSUSUCLKA_SUADJ1_Pos      (0UL)          /*!< SUADJ1 (Bit 16)                                       */
 #define CTSUSUCLKA_SUADJ1_Msk      (0xffUL)       /*!< SUADJ1 (Bitfield-Mask: 0xff)                          */
 #define CTSUSUCLKA_SUMULTI1_Pos    (8UL)          /*!< SUMULTI1 (Bit 24)                                     */
 #define CTSUSUCLKA_SUMULTI1_Msk    (0xff00UL)     /*!< SUMULTI1 (Bitfield-Mask: 0xff)                        */
/* ======================================================  CTSUSUCLK2  ======================================================= */
 #define CTSUSUCLKB_SUADJ2_Pos      (0UL)         /*!< SUADJ2 (Bit 0)                                        */
 #define CTSUSUCLKB_SUADJ2_Msk      (0xffUL)      /*!< SUADJ2 (Bitfield-Mask: 0xff)                          */
 #define CTSUSUCLKB_SUMULTI2_Pos    (8UL)         /*!< SUMULTI2 (Bit 8)                                      */
 #define CTSUSUCLKB_SUMULTI2_Msk    (0xff00UL)    /*!< SUMULTI2 (Bitfield-Mask: 0xff)                        */
/* ======================================================  CTSUSUCLK3  ======================================================= */
 #define CTSUSUCLKB_SUADJ3_Pos      (0UL)         /*!< SUADJ3 (Bit 16)                                       */
 #define CTSUSUCLKB_SUADJ3_Msk      (0xffUL)      /*!< SUADJ3 (Bitfield-Mask: 0xff)                          */
 #define CTSUSUCLKB_SUMULTI3_Pos    (8UL)         /*!< SUMULTI3 (Bit 24)                                     */
 #define CTSUSUCLKB_SUMULTI3_Msk    (0xff00UL)    /*!< SUMULTI3 (Bitfield-Mask: 0xff)                        */
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CTSU run state */
typedef enum e_ctsu_state
{
    CTSU_STATE_INIT,                   ///< Not open.
    CTSU_STATE_IDLE,                   ///< Opened.
    CTSU_STATE_SCANNING,               ///< Scanning now.
    CTSU_STATE_SCANNED                 ///< Scan end.
} ctsu_state_t;

/** CTSU Initial offset tuning status */
typedef enum e_ctsu_tuning
{
    CTSU_TUNING_INCOMPLETE,            ///< Initial offset tuning incomplete
    CTSU_TUNING_COMPLETE               ///< Initial offset tuning complete
} ctsu_tuning_t;

/** CTSU Correction status */
typedef enum e_ctsu_correction_status
{
    CTSU_CORRECTION_INIT,              ///< Correction initial status.
    CTSU_CORRECTION_RUN,               ///< Correction scan running.
    CTSU_CORRECTION_COMPLETE,          ///< Correction complete.
    CTSU_CORRECTION_ERROR              ///< Correction error.
} ctsu_correction_status_t;

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** CTSU Diagnosis status */
typedef enum e_ctsu_diagnosis_status
{
    CTSU_DIAG_INIT,                    ///< Diagnosis initial status.
    CTSU_DIAG_OVER_VOLTAGE,            ///< Diagnosis of over_voltage running.
    CTSU_DIAG_CCO_HIGH,                ///< Diagnosis of oscillator 19.2uA running.
    CTSU_DIAG_CCO_LOW,                 ///< Diagnosis of oscillator 2.4uA running.
    CTSU_DIAG_SSCG,                    ///< Diagnosis of sscg_oscillator running.
    CTSU_DIAG_DAC,                     ///< Diagnosis of dac running.
    CTSU_DIAG_COMPLETE                 ///< Diagnosis complete.
} ctsu_diagnosis_status_t;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** CTSU Diagnosis status */
typedef enum e_ctsu_diagnosis_state
{
    CTSU_DIAG_INIT,                    ///< Diagnosis initial status.
    CTSU_DIAG_OUTPUT_VOLTAGE,          ///< Diagnosis of output voltage running.
    CTSU_DIAG_OVER_VOLTAGE,            ///< Diagnosis of over voltage running.
    CTSU_DIAG_OVER_CURRENT,            ///< Diagnosis of over current running.
    CTSU_DIAG_LOAD_RESISTANCE,         ///< Diagnosis of load resistance running.
    CTSU_DIAG_CURRENT_SOURCE,          ///< Diagnosis of current source running.
    CTSU_DIAG_SENSCLK,                 ///< Diagnosis of SENCLK running.
    CTSU_DIAG_SUCLK,                   ///< Diagnosis of SUCLK running.
    CTSU_DIAG_CLOCK_RECOVERY,          ///< Diagnosis of clock recovery running.
    CTSU_DIAG_CFC,                     ///< Diagnosis of CFC running.
    CTSU_DIAG_COMPLETE                 ///< Diagnosis complete.
} ctsu_diagnosis_state_t;
 #endif
#endif

/** CTSU range definition */
typedef enum e_ctsu_range
{
    CTSU_RANGE_20UA,                   ///< 20uA mode
    CTSU_RANGE_40UA,                   ///< 40uA mode
    CTSU_RANGE_80UA,                   ///< 80uA mode
    CTSU_RANGE_160UA,                  ///< 160uA mode
    CTSU_RANGE_NUM                     ///< number of range
} ctsu_range_t;

/** CTSUWR write register value */
typedef struct st_ctsu_wr
{
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t ctsuso;                   ///< Copy from ((sdpa << 24) | (ssdiv << 20) | (snum << 10) | so) by Open API.
#else
    uint16_t ctsussc;                  ///< Copy from (ssdiv << 8) by Open API.
    uint16_t ctsuso0;                  ///< Copy from ((snum << 10) | so) by Open API.
    uint16_t ctsuso1;                  ///< Copy from (sdpa << 8) by Open API. ICOG and RICOA is set recommend value.
#endif
} ctsu_ctsuwr_t;

/** Scan buffer data formats (Self) */
#if (BSP_FEATURE_CTSU_VERSION == 2)
typedef uint16_t ctsu_self_buf_t;
#else
typedef struct st_ctsu_self_buf
{
    uint16_t sen;                      ///< Sensor counter data
    uint16_t ref;                      ///< Reference counter data (Not used)
} ctsu_self_buf_t;
#endif

/** Scan buffer data formats (Mutual) */
#if (BSP_FEATURE_CTSU_VERSION == 2)
typedef uint16_t ctsu_mutual_buf_t;
#else
typedef struct st_ctsu_mutual_buf
{
    uint16_t pri_sen;                  ///< Primary sensor data
    uint16_t pri_ref;                  ///< Primary reference data (Not used)
    uint16_t snd_sen;                  ///< Secondary sensor data
    uint16_t snd_ref;                  ///< Secondary reference data (Not used)
} ctsu_mutual_buf_t;
#endif

/** Correction information */
typedef struct st_ctsu_correction_info
{
    ctsu_correction_status_t status;                               ///< Correction status
    ctsu_ctsuwr_t            ctsuwr;                               ///< Correction scan parameter
    volatile ctsu_self_buf_t scanbuf;                              ///< Correction scan buffer
#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
    uint16_t scan_index;                                           ///< Scan point index
    uint16_t update_counter;                                       ///< Coefficient update counter
    uint16_t ex_base_value;                                        ///< Value of external registance measurement
    uint8_t  suadj0;                                               ///< Stored SUADJ0 value
 #endif
    uint16_t base_value[CTSU_RANGE_NUM];                           ///< Value of internal registance measurement
    uint16_t error_rate[CTSU_RANGE_NUM];                           ///< Error rate of base vs DAC
    uint16_t range_ratio[CTSU_RANGE_NUM - 1];                      ///< Ratio between 160uA range and other ranges
    uint16_t dac_value[CTSU_CORRECTION_POINT_NUM];                 ///< Value of internal DAC measurement
    uint16_t ref_value[CTSU_RANGE_NUM][CTSU_CORRECTION_POINT_NUM]; ///< Value of reference
#else
    uint16_t first_val;                                            ///< 1st correction value
    uint16_t second_val;                                           ///< 2nd correction value
    uint32_t first_coefficient;                                    ///< 1st correction coefficient
    uint32_t second_coefficient;                                   ///< 2nd correction coefficient
    uint32_t ctsu_clock;                                           ///< CTSU clock [MHz]
#endif
} ctsu_correction_info_t;

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_NUM_CFC != 0)

/** CFC correction information */
typedef struct st_ctsu_corrcfc_info
{
    ctsu_correction_status_t status;                                              ///< Correction status
    ctsu_ctsuwr_t            ctsuwr;                                              ///< Correction scan parameter
    volatile ctsu_self_buf_t scanbuf[CTSU_CFG_NUM_CFC];                           ///< Correction scan buffer
    uint16_t                 base_value[CTSU_CFG_NUM_CFC];                        ///< Value of CFC circuit measurement
    uint16_t                 error_rate[CTSU_CFG_NUM_CFC];                        ///< Error rate of base vs DAC
    uint16_t                 dac_value[CTSU_CFG_NUM_CFC][CTSU_CORRCFC_POINT_NUM]; ///< Value of internal DAC measurement
    uint16_t                 ref_value[CTSU_CFG_NUM_CFC][CTSU_CORRCFC_POINT_NUM]; ///< Value of reference
    uint8_t  ts_table[CTSU_CFG_NUM_CFC];                                          ///< Number of TS terminal
    uint8_t  index;                                                               ///< Index of ts_table
    uint8_t  num_ts;                                                              ///< Number of CFC-TS for instance
    uint64_t stored_rx_bitmap;                                                    ///< Bitmap of registered CFC terminal
} ctsu_corrcfc_info_t;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** Correction information */
typedef struct st_ctsu_diag_info
{
    volatile ctsu_diagnosis_status_t state; ///< Diagnosis state
    ctsu_ctsuwr_t            ctsuwr;        ///< Correction scan parameter
    uint8_t                  loop_count;    ///< Diagnosis loop counter
    volatile ctsu_self_buf_t scanbuf;       ///< Diagnosis scan buffer
    uint16_t                 correct_data;  ///< Diagnosis correct value
    volatile uint8_t         icomp;         ///< Diagnosis icomp flag
    uint16_t                 cco_high;      ///< Diagnosis cco high count
    uint16_t                 cco_low;       ///< Diagnosis cco low count
    uint16_t                 sscg;          ///< Diagnosis sscg count
    uint16_t                 dac_cnt[6];    ///< Diagnosis dac count
    uint16_t                 so0_4uc_val;   ///< Diagnosis dac value
    uint16_t                 dac_init;      ///< Diagnosis dac
    ctsu_tuning_t            tuning;        ///< Diagnosis dac initial tuning flag
    int32_t                  tuning_diff;   ///< Diagnosis
} ctsu_diag_info_t;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/** Correction information */
typedef struct st_ctsu_diag_info
{
    volatile ctsu_diagnosis_state_t state;                                                      ///< Diagnosis state
    ctsu_ctsuwr_t ctsuwr;                                                                       ///< Correction scan parameter
    uint8_t       lvmode;                                                                       ///< Diagnosis lv mode flag
    uint8_t       loop_count;                                                                   ///< Diagnosis loop counter
    uint32_t      ctsuscnt[3];                                                                  ///< Diagnosis raw data (suclk count value & sens count value)
    uint32_t      error_registance[CTSU_RANGE_NUM];                                             ///< Diagnosis error regista
    uint16_t      output_voltage_cnt[CTSU_RANGE_NUM * 2];                                       ///< Diagnosis load resistance count value
    uint16_t      icomp0_value;                                                                 ///< Diagnosis icomp0 register value in over voltage test
    uint16_t      icomp1_value;                                                                 ///< Diagnosis icomp1 register value in over current test
    uint16_t      load_resistance[CTSU_RANGE_NUM];                                              ///< Diagnosis load resistance count value
    uint16_t      current_source[CTSU_DIAG_HIGH_CURRENT_SOURCE + CTSU_DIAG_LOW_CURRENT_SOURCE]; ///< Diagnosis current source count value
    uint16_t      sensclk_cnt[CTSU_CORRECTION_POINT_NUM];                                       ///< Diagnosis sensclk count value
    uint16_t      suclk_cnt[CTSU_CORRECTION_POINT_NUM];                                         ///< Diagnosis suclk count value
    uint16_t      suclk_count_clk_recv[3];                                                      ///< Diagnosis clock recovery suclk count value
    uint16_t      cfc_cnt[CTSU_CORRCFC_POINT_NUM];                                              ///< Diagnosis cfc count value
    uint32_t      chaca;                                                                        ///< Diagnosis CHACA
    uint32_t      chacb;                                                                        ///< Diagnosis CHACB
} ctsu_diag_info_t;
 #endif
#endif

/** CTSU private control block. DO NOT MODIFY. Initialization occurs when R_CTSU_Open() is called. */
typedef struct st_ctsu_instance_ctrl
{
    uint32_t                 open;               ///< Whether or not driver is open.
    volatile ctsu_state_t    state;              ///< CTSU run state.
    ctsu_cap_t               cap;                ///< CTSU Scan Start Trigger Select
    ctsu_md_t                md;                 ///< CTSU Measurement Mode Select(copy to cfg)
    ctsu_tuning_t            tuning;             ///< CTSU Initial offset tuning status.
    uint16_t                 num_elements;       ///< Number of elements to scan
    uint16_t                 wr_index;           ///< Word index into ctsuwr register array.
    uint16_t                 rd_index;           ///< Word index into scan data buffer.
    uint8_t                * p_tuning_count;     ///< Pointer to tuning count of each element. g_ctsu_tuning_count[] is set by Open API.
    int32_t                * p_tuning_diff;      ///< Pointer to difference from base value of each element. g_ctsu_tuning_diff[] is set by Open API.
    uint16_t                 average;            ///< CTSU Moving average counter.
    uint16_t                 num_moving_average; ///< Copy from config by Open API.
    uint8_t                  ctsucr1;            ///< Copy from (atune1 << 3, md << 6) by Open API. CLK, ATUNE0, CSW, and PON is set by HAL driver.
    ctsu_ctsuwr_t          * p_ctsuwr;           ///< CTSUWR write register value. g_ctsu_ctsuwr[] is set by Open API.
    ctsu_self_buf_t        * p_self_raw;         ///< Pointer to Self raw data. g_ctsu_self_raw[] is set by Open API.
    uint16_t               * p_self_corr;        ///< Pointer to Self correction data. g_ctsu_self_corr[] is set by Open API.
    uint16_t               * p_self_data;        ///< Pointer to Self moving average data. g_ctsu_self_data[] is set by Open API.
    ctsu_mutual_buf_t      * p_mutual_raw;       ///< Pointer to Mutual raw data. g_ctsu_mutual_raw[] is set by Open API.
    uint16_t               * p_mutual_pri_corr;  ///< Pointer to Mutual primary correction data. g_ctsu_mutual_pri_corr[] is set by Open API.
    uint16_t               * p_mutual_snd_corr;  ///< Pointer to Mutual secondary correction data. g_ctsu_mutual_snd_corr[] is set by Open API.
    uint16_t               * p_mutual_pri_data;  ///< Pointer to Mutual primary moving average data. g_ctsu_mutual_pri_data[] is set by Open API.
    uint16_t               * p_mutual_snd_data;  ///< Pointer to Mutual secondary moving average data. g_ctsu_mutual_snd_data[] is set by Open API.
    ctsu_correction_info_t * p_correction_info;  ///< Pointer to correction info
    ctsu_txvsel_t            txvsel;             ///< CTSU Transmission Power Supply Select
    ctsu_txvsel2_t           txvsel2;            ///< CTSU Transmission Power Supply Select 2 (CTSU2 Only)
    uint8_t                  ctsuchac0;          ///< TS00-TS07 enable mask
    uint8_t                  ctsuchac1;          ///< TS08-TS15 enable mask
    uint8_t                  ctsuchac2;          ///< TS16-TS23 enable mask
    uint8_t                  ctsuchac3;          ///< TS24-TS31 enable mask
    uint8_t                  ctsuchac4;          ///< TS32-TS39 enable mask
    uint8_t                  ctsuchtrc0;         ///< TS00-TS07 mutual-tx mask
    uint8_t                  ctsuchtrc1;         ///< TS08-TS15 mutual-tx mask
    uint8_t                  ctsuchtrc2;         ///< TS16-TS23 mutual-tx mask
    uint8_t                  ctsuchtrc3;         ///< TS24-TS31 mutual-tx mask
    uint8_t                  ctsuchtrc4;         ///< TS32-TS39 mutual-tx mask
    uint16_t                 self_elem_index;    ///< self element index number for Current instance.
    uint16_t                 mutual_elem_index;  ///< mutual element index number for Current instance.
    uint16_t                 ctsu_elem_index;    ///< CTSU element index number for Current instance.
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint8_t * p_selected_freq_self;              ///< Frequency selected by self-capacity
    uint8_t * p_selected_freq_mutual;            ///< Frequency selected by mutual-capacity
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    ctsu_diag_info_t * p_diag_info;              ///< pointer to diagnosis info
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
    ctsu_range_t range;                            ///< According to atune12. (20uA : 0, 40uA : 1, 80uA : 2, 160uA : 3)
    uint8_t      ctsucr2;                          ///< Copy from (posel, atune1, md) by Open API. FCMODE and SDPSEL and LOAD is set by HAL driver.
 #if (CTSU_CFG_NUM_CFC != 0)
    uint64_t              cfc_rx_bitmap;           ///< Bitmap of CFC receive terminal.
    ctsu_corrcfc_info_t * p_corrcfc_info;          ///< pointer to CFC correction info
 #endif
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    ctsu_diag_info_t * p_diag_info;                ///< pointer to diagnosis info
 #endif
#endif
    uint8_t                  sms;                ///< Whether or not SMS use.
    ctsu_cfg_t const * p_ctsu_cfg;                 ///< Pointer to initial configurations.
    void (* p_callback)(ctsu_callback_args_t *);   ///< Callback provided when a CTSUFN occurs.
    uint8_t                interrupt_reverse_flag; ///< Flag in which read interrupt and end interrupt are reversed
    ctsu_event_t           error_status;           ///< error status variable to send to QE for serial tuning.
    ctsu_callback_args_t * p_callback_memory;      ///< Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void const           * p_context;              ///< Placeholder for user data.
    bool     serial_tuning_enable;                 ///< Flag of serial tuning status.
    uint16_t serial_tuning_mutual_cnt;             ///< Word index into ctsuwr register array.
    uint16_t tuning_self_target_value;             ///< Target self value for initial offset tuning
    uint16_t tuning_mutual_target_value;           ///< Target mutual value for initial offset tuning
    uint8_t                    tsod;               ///< Copy from tsod by Open API.
    uint8_t                    mec_ts;             ///< Copy from mec_ts by Open API.
    uint8_t                    mec_shield_ts;      ///< Copy from mec_shield_ts by Open API.
} ctsu_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ctsu_api_t g_ctsu_on_ctsu;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_CTSU_Open(ctsu_ctrl_t * const p_ctrl, ctsu_cfg_t const * const p_cfg);
fsp_err_t R_CTSU_ScanStart(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_DataGet(ctsu_ctrl_t * const p_ctrl, uint16_t * p_data);
fsp_err_t R_CTSU_ScanStop(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_CallbackSet(ctsu_ctrl_t * const          p_api_ctrl,
                             void (                     * p_callback)(ctsu_callback_args_t *),
                             void const * const           p_context,
                             ctsu_callback_args_t * const p_callback_memory);
fsp_err_t R_CTSU_SmsSet (ctsu_ctrl_t * const p_ctrl,
                         uint16_t * p_threshold,
                         uint16_t * p_hysteresis,
                         uint16_t count_filter);
fsp_err_t R_CTSU_Diagnosis(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_Close(ctsu_ctrl_t * const p_ctrl);
fsp_err_t R_CTSU_SpecificDataGet(ctsu_ctrl_t * const       p_ctrl,
                                 uint16_t                * p_specific_data,
                                 ctsu_specific_data_type_t specific_data_type);
fsp_err_t R_CTSU_DataInsert(ctsu_ctrl_t * const p_ctrl, uint16_t * p_insert_data);
fsp_err_t R_CTSU_OffsetTuning(ctsu_ctrl_t * const p_ctrl);

#endif                                 // R_CTSU_H

/*******************************************************************************************************************//**
 * @} (end addtogroup CTSU)
 **********************************************************************************************************************/
