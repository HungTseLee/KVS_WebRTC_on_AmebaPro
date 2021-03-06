/*
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file     rtl8195bhp_vendor_s.h
 * @brief    CMSIS HeaderFile
 * @version  1.0
 * @date     16. June 2017
 * @note     Generated by SVDConv V3.3.9 on Friday, 16.06.2017 11:35:28
 *           from File 'rtl8195b-hp-vendors.svd',
 *           last modified on Friday, 16.06.2017 03:28:20
 */



/** 
 * @addtogroup hs_hal_vdr
 * @{
 */


#ifndef RTL8195BHP_VENDOR_S_H
#define RTL8195BHP_VENDOR_S_H

#ifdef __cplusplus
extern "C" {
#endif

/// @cond DOXYGEN_VDR_S_REG_TYPE

/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup device_vendor_reg
  * @{
  */



/* =========================================================================================================================== */
/* ================                                           VDR_S                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Vendor Secure Region Register (VDR_S)
  */

typedef struct {                                /*!< (@ 0x50002C00) VDR_S Structure                                            */
  __IM  uint32_t  RESERVED[2];

  union {
    __IM  uint32_t gdma0_isr;                   /*!< (@ 0x00000008) Secure GDMA0 ISR Register                                  */

    struct {
      __IM  uint32_t gdma0_ch0_isr : 1;         /*!< [0..0] GDMA 0 ISR for Channel 0                                           */
      __IM  uint32_t gdma0_ch1_isr : 1;         /*!< [1..1] GDMA 0 ISR for Channel 1                                           */
      __IM  uint32_t gdma0_ch2_isr : 1;         /*!< [2..2] GDMA 0 ISR for Channel 2                                           */
      __IM  uint32_t gdma0_ch3_isr : 1;         /*!< [3..3] GDMA 0 ISR for Channel 3                                           */
      __IM  uint32_t gdma0_ch4_isr : 1;         /*!< [4..4] GDMA 0 ISR for Channel 4                                           */
      __IM  uint32_t gdma0_ch5_isr : 1;         /*!< [5..5] GDMA 0 ISR for Channel 5                                           */
    } gdma0_isr_b;
  } ;

  union {
    __IM  uint32_t gdma1_isr;                   /*!< (@ 0x0000000C) Secure GDMA1 ISR Register                                  */

    struct {
      __IM  uint32_t gdma1_ch0_isr : 1;         /*!< [0..0] GDMA 1 ISR for Channel 0                                           */
      __IM  uint32_t gdma1_ch1_isr : 1;         /*!< [1..1] GDMA 1 ISR for Channel 1                                           */
      __IM  uint32_t gdma1_ch2_isr : 1;         /*!< [2..2] GDMA 1 ISR for Channel 2                                           */
      __IM  uint32_t gdma1_ch3_isr : 1;         /*!< [3..3] GDMA 1 ISR for Channel 3                                           */
      __IM  uint32_t gdma1_ch4_isr : 1;         /*!< [4..4] GDMA 1 ISR for Channel 4                                           */
      __IM  uint32_t gdma1_ch5_isr : 1;         /*!< [5..5] GDMA 1 ISR for Channel 5                                           */
    } gdma1_isr_b;
  } ;
  __IM  uint32_t  RESERVED1[24];

  union {
    __IOM uint32_t low_pri_int_mod;             /*!< (@ 0x00000070) Secure Region Low Priority Interrupt Mode Control
                                                                    Register                                                   */

    struct {
      __IOM uint32_t low_pri_int_mode : 32;     /*!< [31..0] Each bit control corresponding interrupt mode. 1: Rising
                                                     edge trigger 0: High level active                                         */
    } low_pri_int_mod_b;
  } ;

  union {
    __IOM uint32_t low_pri_int_imr;             /*!< (@ 0x00000074) Secure Region Low Priority Interrupt Mask Register         */

    struct {
      __IOM uint32_t rxi300_int_imr : 1;        /*!< [0..0] 1: Enable 0: Disable                                               */
    } low_pri_int_imr_b;
  } ;

  union {
    __IOM uint32_t low_pri_int_isr;             /*!< (@ 0x00000078) Secure Region Low Priority Interrupt Status Register       */

    struct {
      __IOM uint32_t rxi300_secure_bus_isr : 1; /*!< [0..0] RXI secure bus interrupt pending status                            */
    } low_pri_int_isr_b;
  } ;
  __IM  uint32_t  RESERVED2;

  union {
    __OM  uint32_t sup_sec_ef_ctrl;             /*!< (@ 0x00000080) Super Secure eFuse Control Register                        */

    struct {
      __OM  uint32_t sec_super_sec_ef_lock : 1; /*!< [0..0] When this bit is written to '1', this bit can not be
                                                     written to 0. Beside the high speed platform is reset.
                                                     1: Super secure zone can not be accessed. 0: Super secure
                                                     zone just can be accessed by secure state. (AXI_PORT[1]
                                                     = 0)                                                                      */
    } sup_sec_ef_ctrl_b;
  } ;
} VDR_S_Type;                                   /*!< Size = 132 (0x84)                                                         */


/** @} */ /* End of group device_vendor_reg */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup device_vendor_addr
  * @{
  */

#define VDR_S_BASE                  0x50002C00UL

/** @} */ /* End of group device_vendor_addr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup device_vendor_decl
  * @{
  */

#define VDR_S                       ((VDR_S_Type*)             VDR_S_BASE)

/** @} */ /* End of group device_vendor_decl */


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__ARMCC_VERSION) &&  (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif

#include "rtl8195bhp_vdr_s_type.h"
/// @endcond /* End of condition DOXYGEN_VDR_S_REG_TYPE */

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BHP_VENDOR_S_H */


/** @} */ /* End of group hs_hal_vdr */


