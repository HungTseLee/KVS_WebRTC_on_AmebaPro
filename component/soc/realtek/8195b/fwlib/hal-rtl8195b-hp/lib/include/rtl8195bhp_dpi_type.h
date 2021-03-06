/**************************************************************************//**
 * @file      rtl8195bhp_dpi_type.h
 * @brief
 * @version   V1.00
 * @date      2018-6-22 11:32:28
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
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
 ******************************************************************************/

#ifndef _RTL8195BHP_DPI_TYPE_H_
#define _RTL8195BHP_DPI_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_DPI_REG_TYPE

/**
 * @addtogroup hs_hal_dpi_reg DPI Registers.
 * @ingroup hs_hal_lpddr
 * @{
 */

/**
  \brief Union type to access dpi_crt_ctl (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) CRT Control Register                                       */

  struct {
    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_ddr2_en : 1;           /*!< [1..1] DDR2 Enable                                                        */
    __IOM uint32_t dpi_dat_rate_sel : 1;      /*!< [2..2] DFI Data ratio selection 1 : data ratio 1 : 1 0 : data
                                                   ratio 1 : 2                                                               */
    __IOM uint32_t dpi_adr_rate_sel : 1;      /*!< [3..3] DFI Address/Command ratio selection 1 : data ratio 1
                                                   : 1 0 : data ratio 1 : 2                                                  */
    __IOM uint32_t pin_mux_mode : 1;          /*!< [4..4] 1 : LPDDR1 0 : PSRAM                                               */

    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_dqx2_clk_sel : 1;      /*!< [6..6] select dq clock source: 1: dqsx2 , 0: dqx2                         */
    __IOM uint32_t dpi_psram_clk_sel : 1;     /*!< [7..7] select PSRAM clock source 1 : mck_cmd only 0 : mck_ck
                                                   / mck_cmd / mck_dqs / mck_dq                                              */
    __IOM uint32_t bypass_pll_test_mode : 1;  /*!< [8..8] Bypass PLL clock. If bypass_pll_test_mode = 1, bypass_pll_ref_clk_mode
                                                   = 0, clock from bypass_pll_test_clk. bypass_pll_ref_clk_mode
                                                   = 1, clock from PLL reference clock.                                      */
    __IOM uint32_t bypass_pll_ref_clk_mode : 1;/*!< [9..9] Clock selection when bypass_pll_test_mode enable.                 */

    __IM  uint32_t            : 2;
    __IOM uint32_t pwdpad     : 1;            /*!< [12..12] 1 : PAD power down 0 : PAD power on                              */
  } b;                                        /*!< bit fields for dpi_crt_ctl */
} dpi_crt_ctl_t, *pdpi_crt_ctl_t;

/**
  \brief Union type to access dpi_pll_ctl0 (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) PLL Control Register 0                                     */

  struct {
    __IOM uint32_t dpi_en_post_pi : 12;       /*!< [11..0] Enable PLL phase selecter                                         */
    __IOM uint32_t dpi_pll_sel_cpmode : 1;    /*!< [12..12] PLL charge pump mode selector                                    */

    __IM  uint32_t            : 3;
    __IOM uint32_t dpi_mck_clk_en : 11;       /*!< [26..16] ck_en[10 :0] :clock enable ck_en[0] :mck_ck ck_en[1]
                                                   :mck_cmd ck_en[2]:mck_dqs_0 ck_en[3]:mck_dqs_1 ck_en[4]:mck_dqs_2
                                                   ck_en[5]:mck_dqs_3 ck_en[6]: mck_dq_0 ck_en[7]: mck_dq_1
                                                   ck_en[8]: mck_dq_2 ck_en[9]: mck_dq_3 ck_en[10]:mck_ck_1                  */
  } b;                                        /*!< bit fields for dpi_pll_ctl0 */
} dpi_pll_ctl0_t, *pdpi_pll_ctl0_t;

/**
  \brief Union type to access dpi_pll_ctl1 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) PLL Control Register 1                                     */

  struct {
    __IOM uint32_t dpi_oesync_op_sel : 11;    /*!< [10..0] control signal for output clock enable sync                       */

    __IM  uint32_t            : 5;
    __IOM uint32_t dpi_clk_oe : 11;           /*!< [26..16] clk_oe[10:0]: PLL clock output enable clk_oe[0]:mck_ck
                                                   clk_oe[1]:mck_cmd clk_oe[2]:mck_dqs_0 clk_oe[3]:mck_dqs_1
                                                   clk_oe[4]:mck_dqs_2 clk_oe[5]:mck_dqs_3 clk_oe[6]:mck_dq_0
                                                   clk_oe[7]:mck_dq_1 clk_oe[8]:mck_dq_2 clk_oe[9]:mck_dq_3
                                                   clk_oe[10]:mck_ck_1                                                       */
  } b;                                        /*!< bit fields for dpi_pll_ctl1 */
} dpi_pll_ctl1_t, *pdpi_pll_ctl1_t;

/**
  \brief Union type to access dpi_pll_ctl2 (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) PLL Control Register 2                                     */

  struct {
    __IOM uint32_t dpi_pll_dum : 8;           /*!< [7..0] dpi_pll_dum                                                        */
  } b;                                        /*!< bit fields for dpi_pll_ctl2 */
} dpi_pll_ctl2_t, *pdpi_pll_ctl2_t;

/**
  \brief Union type to access dpi_pll_pi0 (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) PLL PI0 Register                                           */

  struct {
    __IOM uint32_t dpi_post_pi_sel0 : 6;      /*!< [5..0] PLL phase select for mck_ck                                        */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel1 : 6;      /*!< [13..8] PLL phase select for mck_cmd                                      */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel2 : 6;      /*!< [21..16] PLL phase select for mck_dqs_0                                   */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel3 : 6;      /*!< [29..24] PLL phase select for mck_dqs_1                                   */
  } b;                                        /*!< bit fields for dpi_pll_pi0 */
} dpi_pll_pi0_t, *pdpi_pll_pi0_t;

/**
  \brief Union type to access dpi_pll_pi1 (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) PLL PI1 Register                                           */

  struct {
    __IOM uint32_t dpi_post_pi_sel4 : 6;      /*!< [5..0] PLL phase select for mck_dqs_2                                     */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel5 : 6;      /*!< [13..8] PLL phase select for mck_dqs_3                                    */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel6 : 6;      /*!< [21..16] PLL phase select for mck_dq_0                                    */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel : 5;       /*!< [28..24] PLL internal clock phase select                                  */
  } b;                                        /*!< bit fields for dpi_pll_pi1 */
} dpi_pll_pi1_t, *pdpi_pll_pi1_t;

/**
  \brief Union type to access dpi_pll_pi2 (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) PLL PI2 Register                                           */

  struct {
    __IOM uint32_t dpi_post_pi_sel7 : 6;      /*!< [5..0] PLL phase select for mck_dq_1                                      */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel8 : 6;      /*!< [13..8] PLL phase select for mck_dq_2                                     */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel9 : 6;      /*!< [21..16] PLL phase select for mck_dq_3                                    */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_post_pi_sel10 : 6;     /*!< [29..24] PLL phase select for mck_ck_1                                    */
  } b;                                        /*!< bit fields for dpi_pll_pi2 */
} dpi_pll_pi2_t, *pdpi_pll_pi2_t;

/**
  \brief Union type to access dpi_pll_ctl3 (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) PLL Control Register 3                                     */

  struct {
    __IOM uint32_t dpi_cco_band : 2;          /*!< [1..0] CCO Band Select : 0 : 500M~850M 1 : 850M~1600M                     */
    __IOM uint32_t dpi_cco_kvco : 1;          /*!< [2..2] Kcco control 0:small Kcco 1:large Kcco (Default)                   */

    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_icp    : 4;            /*!< [7..4] PLL Charge Pump Current Control                                    */
    __IOM uint32_t dpi_loop_pi_isel : 2;      /*!< [9..8] PLL PI bias current control                                        */
    __IOM uint32_t dpi_cco_sel : 1;           /*!< [10..10] dpi_cco_sel                                                      */

    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_lpf_cp : 1;            /*!< [12..12] PLL Cp Control                                                   */
    __IOM uint32_t dpi_lpf_sr : 3;            /*!< [15..13] PLL Loop Filter Resister Control RS: 000 : 3K 001 :
                                                   6K 010 : 9K 011 : 12K 100 : 15K 101 : 18K 110 : 21K 111
                                                   : 24K                                                                     */
    __IOM uint32_t dpi_pdiv   : 2;            /*!< [17..16] PLL pre-divider 00 : Div1 01 : Div2 10 : Div3 11 :
                                                   Div4                                                                      */
    __IOM uint32_t dpi_pll_dbug_en : 1;       /*!< [18..18] PLL Debug enable 0 : disable 1 : enable                          */
    __IOM uint32_t dpi_v11_ldo_sel : 2;       /*!< [20..19] LDO output control : 00 : 1.6V 01 : 1.7V 10 : 1.8V
                                                   11 : 1.9V                                                                 */
    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_post_pi_bias : 2;      /*!< [23..22] Post PI bias control                                             */
    __IOM uint32_t dpi_post_pi_rl : 2;        /*!< [25..24] Post PI RL control                                               */
    __IOM uint32_t dpi_post_pi_cl : 1;        /*!< [26..26] Post PI RS control                                               */
    __IOM uint32_t dpi_ckref_sel : 1;         /*!< [27..27] Ref Clock select                                                 */
    __IOM uint32_t dpi_vco_ldo_vsel : 2;      /*!< [29..28] pll vco ldo select                                               */

    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_output_iso : 1;        /*!< [31..31] PLL isolation cell enable                                        */
  } b;                                        /*!< bit fields for dpi_pll_ctl3 */
} dpi_pll_ctl3_t, *pdpi_pll_ctl3_t;

/**
  \brief Union type to access dpi_ssc0 (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) SSC0 Register                                              */

  struct {
    __IOM uint32_t dpi_bypass_pi : 1;         /*!< [0..0] When no fractional divider or SSC,bypass Phase Intepolator
                                                   for CMU loop 0: including PI inside the loop 1: bypass
                                                   PI inside the loop                                                        */
    __IOM uint32_t dpi_en_ssc : 1;            /*!< [1..1] Enable SSC function                                                */
    __IOM uint32_t dpi_order  : 1;            /*!< [2..2] not used                                                           */
    __IOM uint32_t dpi_sel_mode : 1;          /*!< [3..3] SSC mode selector                                                  */
    __IOM uint32_t dpi_en_center_in : 1;      /*!< [4..4] Enable center SSC no used for PCIe                                 */
    __IOM uint32_t dpi_weighting_sel : 3;     /*!< [7..5] not used                                                           */
    __IOM uint32_t dpi_step_in : 15;          /*!< [22..8] SSC profile per-step delta code                                   */
  } b;                                        /*!< bit fields for dpi_ssc0 */
} dpi_ssc0_t, *pdpi_ssc0_t;

/**
  \brief Union type to access dpi_ssc1 (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) SSC1 Register                                              */

  struct {
    __IOM uint32_t dpi_f_code : 15;           /*!< [14..0] Fractional code of loop divider                                   */

    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_tbase  : 12;           /*!< [27..16] SSC profile step number                                          */
  } b;                                        /*!< bit fields for dpi_ssc1 */
} dpi_ssc1_t, *pdpi_ssc1_t;

/**
  \brief Union type to access dpi_ssc2 (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) SSC2 Register                                              */

  struct {
    __IOM uint32_t dpi_n_code : 8;            /*!< [7..0] Integer code of loop divider                                       */
    __IOM uint32_t dpi_vbg_sel : 3;           /*!< [10..8] PLL band gap voltage selection                                    */
    __IOM uint32_t dpi_bg_pow : 1;            /*!< [11..11] PLL band gap power                                               */
    __IOM uint32_t dpi_bg_bias : 2;           /*!< [13..12] PLL band gap bias control                                        */
  } b;                                        /*!< bit fields for dpi_ssc2 */
} dpi_ssc2_t, *pdpi_ssc2_t;

/**
  \brief Union type to access dpi_wdog (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) Watch Dog Register                                         */

  struct {
    __IOM uint32_t dpi_wd_enable : 1;         /*!< [0..0] Enable watch dog function                                          */
    __IOM uint32_t dpi_f390k  : 2;            /*!< [2..1] F390K output delay, not used                                       */

    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_time0_ck : 3;          /*!< [6..4] Watchdog timing control                                            */

    __IM  uint32_t            : 1;
    __IOM uint32_t dpi_time_rdy_ckout : 2;    /*!< [9..8] Clock ready timing control                                         */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpi_time2_rst_width : 2;   /*!< [13..12] Reset timing ontrol                                              */
  } b;                                        /*!< bit fields for dpi_wdog */
} dpi_wdog_t, *pdpi_wdog_t;

/**
  \brief Union type to access dpi_ca_pupd0 (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) CA_PUPD0 Register                                          */

  struct {
    __IM  uint32_t            : 8;
    __IOM uint32_t b00_pd     : 1;            /*!< [8..8] BANK0 PD                                                           */
    __IOM uint32_t b00_pu     : 1;            /*!< [9..9] BANK0 PU                                                           */
    __IOM uint32_t b01_pd     : 1;            /*!< [10..10] BANK1 PD                                                         */
    __IOM uint32_t b01_pu     : 1;            /*!< [11..11] BANK1 PU                                                         */
    __IOM uint32_t b02_pd     : 1;            /*!< [12..12] BANK2 PD                                                         */
    __IOM uint32_t b02_pu     : 1;            /*!< [13..13] BANK2 PU                                                         */
    __IOM uint32_t reset_pd   : 1;            /*!< [14..14] RESET PD                                                         */
    __IOM uint32_t reset_pu   : 1;            /*!< [15..15] RESET PU                                                         */
    __IOM uint32_t odt_pd     : 1;            /*!< [16..16] ODT PD                                                           */
    __IOM uint32_t odt_pu     : 1;            /*!< [17..17] ODT PU                                                           */
    __IOM uint32_t we_pd      : 1;            /*!< [18..18] WE PD                                                            */
    __IOM uint32_t we_pu      : 1;            /*!< [19..19] WE PU                                                            */
    __IOM uint32_t cas_pd     : 1;            /*!< [20..20] CAS PD                                                           */
    __IOM uint32_t cas_pu     : 1;            /*!< [21..21] CAS PU                                                           */
    __IOM uint32_t ras_pd     : 1;            /*!< [22..22] RAS PD                                                           */
    __IOM uint32_t ras_pu     : 1;            /*!< [23..23] RAS PU                                                           */
    __IOM uint32_t cs_pd      : 1;            /*!< [24..24] CS PD                                                            */
    __IOM uint32_t cs_pu      : 1;            /*!< [25..25] CS PU                                                            */
    __IOM uint32_t cke_pd     : 1;            /*!< [26..26] CKE PD                                                           */
    __IOM uint32_t cke_pu     : 1;            /*!< [27..27] CKE PU                                                           */
    __IOM uint32_t ck_n_pd    : 1;            /*!< [28..28] CKB PD                                                           */
    __IOM uint32_t ck_n_pu    : 1;            /*!< [29..29] CKB PU                                                           */
    __IOM uint32_t ck_p_pd    : 1;            /*!< [30..30] CK PD                                                            */
    __IOM uint32_t ck_p_pu    : 1;            /*!< [31..31] CK PU                                                            */
  } b;                                        /*!< bit fields for dpi_ca_pupd0 */
} dpi_ca_pupd0_t, *pdpi_ca_pupd0_t;

/**
  \brief Union type to access dpi_ca_pupd1 (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) CA_PUPD1 Register                                          */

  struct {
    __IOM uint32_t a00_pd     : 1;            /*!< [0..0] A0 PD                                                              */
    __IOM uint32_t a00_pu     : 1;            /*!< [1..1] A0 PU                                                              */
    __IOM uint32_t a01_pd     : 1;            /*!< [2..2] A1 PD                                                              */
    __IOM uint32_t a01_pu     : 1;            /*!< [3..3] A1 PU                                                              */
    __IOM uint32_t a02_pd     : 1;            /*!< [4..4] A2 PD                                                              */
    __IOM uint32_t a02_pu     : 1;            /*!< [5..5] A2 PU                                                              */
    __IOM uint32_t a03_pd     : 1;            /*!< [6..6] A3 PD                                                              */
    __IOM uint32_t a03_pu     : 1;            /*!< [7..7] A3 PU                                                              */
    __IOM uint32_t a04_pd     : 1;            /*!< [8..8] A4 PD                                                              */
    __IOM uint32_t a04_pu     : 1;            /*!< [9..9] A4 PU                                                              */
    __IOM uint32_t a05_pd     : 1;            /*!< [10..10] A5 PD                                                            */
    __IOM uint32_t a05_pu     : 1;            /*!< [11..11] A5 PU                                                            */
    __IOM uint32_t a06_pd     : 1;            /*!< [12..12] A6 PD                                                            */
    __IOM uint32_t a06_pu     : 1;            /*!< [13..13] A6 PU                                                            */
    __IOM uint32_t a07_pd     : 1;            /*!< [14..14] A7 PD                                                            */
    __IOM uint32_t a07_pu     : 1;            /*!< [15..15] A7 PU                                                            */
    __IOM uint32_t a08_pd     : 1;            /*!< [16..16] A8 PD                                                            */
    __IOM uint32_t a08_pu     : 1;            /*!< [17..17] A8 PU                                                            */
    __IOM uint32_t a09_pd     : 1;            /*!< [18..18] A9 PD                                                            */
    __IOM uint32_t a09_pu     : 1;            /*!< [19..19] A9 PU                                                            */
    __IOM uint32_t a10_pd     : 1;            /*!< [20..20] A10 PD                                                           */
    __IOM uint32_t a10_pu     : 1;            /*!< [21..21] A10 PU                                                           */
    __IOM uint32_t a11_pd     : 1;            /*!< [22..22] A11 PD                                                           */
    __IOM uint32_t a11_pu     : 1;            /*!< [23..23] A11 PU                                                           */
    __IOM uint32_t a12_pd     : 1;            /*!< [24..24] A12 PD                                                           */
    __IOM uint32_t a12_pu     : 1;            /*!< [25..25] A12 PU                                                           */
    __IOM uint32_t a13_pd     : 1;            /*!< [26..26] A13 PD                                                           */
    __IOM uint32_t a13_pu     : 1;            /*!< [27..27] A13 PU                                                           */
    __IOM uint32_t a14_pd     : 1;            /*!< [28..28] A14 PD                                                           */
    __IOM uint32_t a14_pu     : 1;            /*!< [29..29] A14 PU                                                           */
    __IOM uint32_t a15_pd     : 1;            /*!< [30..30] A15 PD                                                           */
    __IOM uint32_t a15_pu     : 1;            /*!< [31..31] A15 PU                                                           */
  } b;                                        /*!< bit fields for dpi_ca_pupd1 */
} dpi_ca_pupd1_t, *pdpi_ca_pupd1_t;

/**
  \brief Union type to access dpi_dq_pupd (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) DQ_PUPD Register                                           */

  struct {
    __IM  uint32_t            : 12;
    __IOM uint32_t dm_pd      : 1;            /*!< [12..12] DM PD                                                            */
    __IOM uint32_t dm_pu      : 1;            /*!< [13..13] DM PU                                                            */
    __IOM uint32_t dq0_pd     : 1;            /*!< [14..14] DQ0 PD                                                           */
    __IOM uint32_t dq0_pu     : 1;            /*!< [15..15] DQ0 PU                                                           */
    __IOM uint32_t dq1_pd     : 1;            /*!< [16..16] DQ1 PD                                                           */
    __IOM uint32_t dq1_pu     : 1;            /*!< [17..17] DQ1 PU                                                           */
    __IOM uint32_t dq2_pd     : 1;            /*!< [18..18] DQ2 PD                                                           */
    __IOM uint32_t dq2_pu     : 1;            /*!< [19..19] DQ2 PU                                                           */
    __IOM uint32_t dq3_pd     : 1;            /*!< [20..20] DQ3 PD                                                           */
    __IOM uint32_t dq3_pu     : 1;            /*!< [21..21] DQ3 PU                                                           */
    __IOM uint32_t dq4_pd     : 1;            /*!< [22..22] DQ4 PD                                                           */
    __IOM uint32_t dq4_pu     : 1;            /*!< [23..23] DQ4 PU                                                           */
    __IOM uint32_t dq5_pd     : 1;            /*!< [24..24] DQ5 PD                                                           */
    __IOM uint32_t dq5_pu     : 1;            /*!< [25..25] DQ5 PU                                                           */
    __IOM uint32_t dq6_pd     : 1;            /*!< [26..26] DQ6 PD                                                           */
    __IOM uint32_t dq6_pu     : 1;            /*!< [27..27] DQ6 PU                                                           */
    __IOM uint32_t dq7_pd     : 1;            /*!< [28..28] DQ7 PD                                                           */
    __IOM uint32_t dq7_pu     : 1;            /*!< [29..29] DQ7 PU                                                           */
    __IOM uint32_t dqs_p_pd   : 1;            /*!< [30..30] DQS PD                                                           */
    __IOM uint32_t dqs_p_pu   : 1;            /*!< [31..31] DQS PU                                                           */
  } b;                                        /*!< bit fields for dpi_dq_pupd */
} dpi_dq_pupd_t, *pdpi_dq_pupd_t;

/**
  \brief Union type to access dpi_crt_dmy (@ 0x0000007C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000007C) CRT_DMY Register                                           */

  struct {
    __IOM uint32_t dmy        : 32;           /*!< [31..0] Dummy Registers                                                   */
  } b;                                        /*!< bit fields for dpi_crt_dmy */
} dpi_crt_dmy_t, *pdpi_crt_dmy_t;

/**
  \brief Union type to access dpi_adr_dly0 (@ 0x00000200).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000200) ADR_DLY_0 Register                                         */

  struct {
    __IOM uint32_t adr00_dly_sel : 4;         /*!< [3..0] Address[0] delay chain control                                     */
    __IOM uint32_t adr01_dly_sel : 4;         /*!< [7..4] Address[1] delay chain control                                     */
    __IOM uint32_t adr02_dly_sel : 4;         /*!< [11..8] Address[2] delay chain control                                    */
    __IOM uint32_t adr03_dly_sel : 4;         /*!< [15..12] Address[3] delay chain control                                   */
    __IOM uint32_t adr04_dly_sel : 4;         /*!< [19..16] Address[4] delay chain control                                   */
    __IOM uint32_t adr05_dly_sel : 4;         /*!< [23..20] Address[5] delay chain control                                   */
    __IOM uint32_t adr06_dly_sel : 4;         /*!< [27..24] Address[6] delay chain control                                   */
    __IOM uint32_t adr07_dly_sel : 4;         /*!< [31..28] Address[7] delay chain control                                   */
  } b;                                        /*!< bit fields for dpi_adr_dly0 */
} dpi_adr_dly0_t, *pdpi_adr_dly0_t;

/**
  \brief Union type to access dpi_adr_dly1 (@ 0x00000204).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000204) ADR_DLY_1 Register                                         */

  struct {
    __IOM uint32_t adr08_dly_sel : 4;         /*!< [3..0] Address[8] delay chain control                                     */
    __IOM uint32_t adr09_dly_sel : 4;         /*!< [7..4] Address[9] delay chain control                                     */
    __IOM uint32_t adr10_dly_sel : 4;         /*!< [11..8] Address[10] delay chain control                                   */
    __IOM uint32_t adr11_dly_sel : 4;         /*!< [15..12] Address[11] delay chain control                                  */
    __IOM uint32_t adr12_dly_sel : 4;         /*!< [19..16] Address[12] delay chain control                                  */
    __IOM uint32_t adr13_dly_sel : 4;         /*!< [23..20] Address[13] delay chain control                                  */
    __IOM uint32_t adr14_dly_sel : 4;         /*!< [27..24] Address[14] delay chain control                                  */
    __IOM uint32_t adr15_dly_sel : 4;         /*!< [31..28] Address[15] delay chain control                                  */
  } b;                                        /*!< bit fields for dpi_adr_dly1 */
} dpi_adr_dly1_t, *pdpi_adr_dly1_t;

/**
  \brief Union type to access dpi_adr_dly2 (@ 0x00000208).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000208) ADR_DLY_2 Register                                         */

  struct {
    __IOM uint32_t adr4_ext_dly_sel : 4;      /*!< [3..0] Extent address[4] delay chain control                              */
    __IOM uint32_t adr5_ext_dly_sel : 4;      /*!< [7..4] Extent address[5] delay chain control                              */
    __IOM uint32_t ba0_dly_sel : 4;           /*!< [11..8] BANK[0] delay chain control                                       */
    __IOM uint32_t ba1_dly_sel : 4;           /*!< [15..12] BANK[1] delay chain control                                      */
    __IOM uint32_t ba2_dly_sel : 4;           /*!< [19..16] BANK[2] delay chain control                                      */
  } b;                                        /*!< bit fields for dpi_adr_dly2 */
} dpi_adr_dly2_t, *pdpi_adr_dly2_t;

/**
  \brief Union type to access dpi_cmd_dly0 (@ 0x0000020C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000020C) CMD_DLY_0 Register                                         */

  struct {
    __IOM uint32_t cke_dly_sel : 4;           /*!< [3..0] CKE delay chain control                                            */
    __IOM uint32_t ras_n_dly_sel : 4;         /*!< [7..4] RAS_N delay chain control                                          */
    __IOM uint32_t cas_n_dly_sel : 4;         /*!< [11..8] CAS_N delay chain control                                         */
    __IOM uint32_t we_n_dly_sel : 4;          /*!< [15..12] WE_N delay chain control                                         */
    __IOM uint32_t odt_dly_sel : 4;           /*!< [19..16] ODT delay chain control                                          */
    __IOM uint32_t cs_n_dly_sel : 6;          /*!< [25..20] CS_N delay chain control                                         */
    __IOM uint32_t cs_n_1_dly_sel : 6;        /*!< [31..26] CS_N_1 delay chain control                                       */
  } b;                                        /*!< bit fields for dpi_cmd_dly0 */
} dpi_cmd_dly0_t, *pdpi_cmd_dly0_t;

/**
  \brief Union type to access dpi_pad_oe_ctl (@ 0x00000210).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000210) PAD_OE_CTL Register                                        */

  struct {
    __IOM uint32_t adr00_oe   : 1;            /*!< [0..0] Ouput enable of address[00]                                        */
    __IOM uint32_t adr01_oe   : 1;            /*!< [1..1] Ouput enable of address[01]                                        */
    __IOM uint32_t adr02_oe   : 1;            /*!< [2..2] Ouput enable of address[02]                                        */
    __IOM uint32_t adr03_oe   : 1;            /*!< [3..3] Ouput enable of address[03]                                        */
    __IOM uint32_t adr04_oe   : 1;            /*!< [4..4] Ouput enable of address[04]                                        */
    __IOM uint32_t adr05_oe   : 1;            /*!< [5..5] Ouput enable of address[05]                                        */
    __IOM uint32_t adr06_oe   : 1;            /*!< [6..6] Ouput enable of address[06]                                        */
    __IOM uint32_t adr07_oe   : 1;            /*!< [7..7] Ouput enable of address[07]                                        */
    __IOM uint32_t adr08_oe   : 1;            /*!< [8..8] Ouput enable of address[08]                                        */
    __IOM uint32_t adr09_oe   : 1;            /*!< [9..9] Ouput enable of address[09]                                        */
    __IOM uint32_t adr10_oe   : 1;            /*!< [10..10] Ouput enable of address[10]                                      */
    __IOM uint32_t adr11_oe   : 1;            /*!< [11..11] Ouput enable of address[11]                                      */
    __IOM uint32_t adr12_oe   : 1;            /*!< [12..12] Ouput enable of address[12]                                      */
    __IOM uint32_t adr13_oe   : 1;            /*!< [13..13] Ouput enable of address[13]                                      */
    __IOM uint32_t adr14_oe   : 1;            /*!< [14..14] Ouput enable of address[14]                                      */
    __IOM uint32_t adr15_oe   : 1;            /*!< [15..15] Ouput enable of address[15]                                      */
    __IOM uint32_t ext_adr4_oe : 1;           /*!< [16..16] Ouput enable of Extent address[4]                                */
    __IOM uint32_t ext_adr5_oe : 1;           /*!< [17..17] Ouput enable of Extent address[5]                                */
    __IOM uint32_t bk0_oe     : 1;            /*!< [18..18] Ouput enable of BANK[0]                                          */
    __IOM uint32_t bk1_oe     : 1;            /*!< [19..19] Ouput enable of BANK[1]                                          */
    __IOM uint32_t bk2_oe     : 1;            /*!< [20..20] Ouput enable of BANK[2]                                          */
    __IOM uint32_t reset_n_oe : 1;            /*!< [21..21] Ouput enable of Reset_N                                          */
    __IOM uint32_t odt_oe     : 1;            /*!< [22..22] Ouput enable of ODT                                              */
    __IOM uint32_t we_n_oe    : 1;            /*!< [23..23] Ouput enable of WE_N                                             */
    __IOM uint32_t cas_n_oe   : 1;            /*!< [24..24] Ouput enable of CAS_N                                            */
    __IOM uint32_t ras_n_oe   : 1;            /*!< [25..25] Ouput enable of RAS_N                                            */
    __IOM uint32_t cke_oe     : 1;            /*!< [26..26] Ouput enable of CKE                                              */
    __IOM uint32_t cs_n_oe    : 1;            /*!< [27..27] Output enable of DCS_N                                           */
    __IOM uint32_t cs_n_1_oe  : 1;            /*!< [28..28] Output enable of DCS_N_1                                         */
    __IOM uint32_t dck_oe     : 1;            /*!< [29..29] Ouput enable of DCK                                              */
    __IOM uint32_t dck_1_oe   : 1;            /*!< [30..30] Output enable of DCK_1                                           */
    __IOM uint32_t adr54_1to1 : 1;            /*!< [31..31] Address[5:4] OCD control                                         */
  } b;                                        /*!< bit fields for dpi_pad_oe_ctl */
} dpi_pad_oe_ctl_t, *pdpi_pad_oe_ctl_t;

/**
  \brief Union type to access dpi_wrlvl_ctrl (@ 0x00000228).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000228) WRLVL_CTRL Register                                        */

  struct {
    __IOM uint32_t wrlvl_en   : 1;            /*!< [0..0] Write level enable                                                 */
    __IOM uint32_t wrlvl_trig : 1;            /*!< [1..1] Write level trigger                                                */

    __IM  uint32_t            : 2;
    __IOM uint32_t wrlvl_fb_dqs : 4;          /*!< [7..4] Write level feedback MUX selection                                 */
    __IOM uint32_t wrlvl_fb_dq : 4;           /*!< [11..8] Write level feedback MUX selection                                */
    __IOM uint32_t wrlvl_dly_dqs : 4;         /*!< [15..12] Write level feedback delay 1T                                    */
    __IOM uint32_t wrlvl_dly_dq : 4;          /*!< [19..16] Write level feedback delay 1T                                    */
    __IOM uint32_t wait_ie    : 1;            /*!< [20..20] PSRAM WIAT IE control                                            */
    __IOM uint32_t cs_ph_sel  : 3;            /*!< [23..21] CS output delay                                                  */
    __IOM uint32_t cs_1_ph_sel : 3;           /*!< [26..24] CS_1 output delay                                                */
    __IOM uint32_t cmd_geardown : 1;          /*!< [27..27] Command output delay select                                      */
    __IOM uint32_t cs_geardown : 1;           /*!< [28..28] CS output delay select                                           */
    __IOM uint32_t cs_ph_en   : 1;            /*!< [29..29] CS output delay enable                                           */
    __IOM uint32_t cs_1_geardown : 1;         /*!< [30..30] CS_1 output delay select                                         */
    __IOM uint32_t cs_1_ph_en : 1;            /*!< [31..31] CS_1 output delay enable                                         */
  } b;                                        /*!< bit fields for dpi_wrlvl_ctrl */
} dpi_wrlvl_ctrl_t, *pdpi_wrlvl_ctrl_t;

/**
  \brief Union type to access dpi_wrlvl_rd_data (@ 0x0000022C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000022C) WRLVL_RD_DATA Register                                     */

  struct {
    __IOM uint32_t wrlvl_rddata : 32;         /*!< [31..0] Read data from DDR when wrlvl_en is high                          */
  } b;                                        /*!< bit fields for dpi_wrlvl_rd_data */
} dpi_wrlvl_rd_data_t, *pdpi_wrlvl_rd_data_t;

/**
  \brief Union type to access dpi_test_ctrl0 (@ 0x00000230).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000230) TEST_CTRL0 Register                                        */

  struct {
    __IOM uint32_t rd_dbg_sel0_0 : 5;         /*!< [4..0] Debug selection for data slice0                                    */
    __IOM uint32_t rd_dbg_sel0_1 : 5;         /*!< [9..5] Debug selection for data slice1                                    */
    __IOM uint32_t rd_dbg_sel0_2 : 5;         /*!< [14..10] Debug selection for data slice2                                  */
    __IOM uint32_t rd_dbg_sel0_3 : 5;         /*!< [19..15] Debug selection for data slice3                                  */
    __IOM uint32_t rw_dbg_sel0 : 2;           /*!< [21..20] Debug selection for read / write slice top                       */
    __IOM uint32_t top_dbg_sel : 2;           /*!< [23..22] Debug selection for top                                          */
    __IOM uint32_t dbg_pcmd_out : 1;          /*!< [24..24] Debug output from CMD PAD                                        */

    __IM  uint32_t            : 5;
    __IOM uint32_t lbk_mode   : 2;            /*!< [31..30] Self look back mode                                              */
  } b;                                        /*!< bit fields for dpi_test_ctrl0 */
} dpi_test_ctrl0_t, *pdpi_test_ctrl0_t;

/**
  \brief Union type to access dpi_test_ctrl1 (@ 0x00000234).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000234) TEST_CTRL1 Register                                        */

  struct {
    __IOM uint32_t rd_dbg_sel1_0 : 5;         /*!< [4..0] Debug selection for data slice0                                    */
    __IOM uint32_t rd_dbg_sel1_1 : 5;         /*!< [9..5] Debug selection for data slice1                                    */
    __IOM uint32_t rd_dbg_sel1_2 : 5;         /*!< [14..10] Debug selection for data slice2                                  */
    __IOM uint32_t rd_dbg_sel1_3 : 5;         /*!< [19..15] Debug selection for data slice3                                  */
    __IOM uint32_t rw_dbg_sel1 : 2;           /*!< [21..20] Debug selection for read / write slice top                       */
  } b;                                        /*!< bit fields for dpi_test_ctrl1 */
} dpi_test_ctrl1_t, *pdpi_test_ctrl1_t;

/**
  \brief Union type to access dpi_dq_dly0 (@ 0x00000238).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000238) DQ_DLY Register 0                                          */

  struct {
    __IOM uint32_t dq0_dly_sel : 4;           /*!< [3..0] DQ[0] delay chain control                                          */
    __IOM uint32_t dq1_dly_sel : 4;           /*!< [7..4] DQ[1] delay chain control                                          */
    __IOM uint32_t dq2_dly_sel : 4;           /*!< [11..8] DQ[2] delay chain control                                         */
    __IOM uint32_t dq3_dly_sel : 4;           /*!< [15..12] DQ[3] delay chain control                                        */
    __IOM uint32_t dq4_dly_sel : 4;           /*!< [19..16] DQ[4] delay chain control                                        */
    __IOM uint32_t dq5_dly_sel : 4;           /*!< [23..20] DQ[5] delay chain control                                        */
    __IOM uint32_t dq6_dly_sel : 4;           /*!< [27..24] DQ[6] delay chain control                                        */
    __IOM uint32_t dq7_dly_sel : 4;           /*!< [31..28] DQ[7] delay chain control                                        */
  } b;                                        /*!< bit fields for dpi_dq_dly0 */
} dpi_dq_dly0_t, *pdpi_dq_dly0_t;

/**
  \brief Union type to access dpi_dq_dly0_1 (@ 0x0000023C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000023C) DQ_DLY Register 0_1                                        */

  struct {
    __IOM uint32_t dq0_dly_sel : 4;           /*!< [3..0] DQ[0] delay chain control                                          */
    __IOM uint32_t dq1_dly_sel : 4;           /*!< [7..4] DQ[1] delay chain control                                          */
    __IOM uint32_t dq2_dly_sel : 4;           /*!< [11..8] DQ[2] delay chain control                                         */
    __IOM uint32_t dq3_dly_sel : 4;           /*!< [15..12] DQ[3] delay chain control                                        */
    __IOM uint32_t dq4_dly_sel : 4;           /*!< [19..16] DQ[4] delay chain control                                        */
    __IOM uint32_t dq5_dly_sel : 4;           /*!< [23..20] DQ[5] delay chain control                                        */
    __IOM uint32_t dq6_dly_sel : 4;           /*!< [27..24] DQ[6] delay chain control                                        */
    __IOM uint32_t dq7_dly_sel : 4;           /*!< [31..28] DQ[7] delay chain control                                        */
  } b;                                        /*!< bit fields for dpi_dq_dly0_1 */
} dpi_dq_dly0_1_t, *pdpi_dq_dly0_1_t;

/**
  \brief Union type to access dpi_dq_dly0_2 (@ 0x00000240).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000240) DQ_DLY Register 0_2                                        */

  struct {
    __IOM uint32_t dq0_dly_sel : 4;           /*!< [3..0] DQ[0] delay chain control                                          */
    __IOM uint32_t dq1_dly_sel : 4;           /*!< [7..4] DQ[1] delay chain control                                          */
    __IOM uint32_t dq2_dly_sel : 4;           /*!< [11..8] DQ[2] delay chain control                                         */
    __IOM uint32_t dq3_dly_sel : 4;           /*!< [15..12] DQ[3] delay chain control                                        */
    __IOM uint32_t dq4_dly_sel : 4;           /*!< [19..16] DQ[4] delay chain control                                        */
    __IOM uint32_t dq5_dly_sel : 4;           /*!< [23..20] DQ[5] delay chain control                                        */
    __IOM uint32_t dq6_dly_sel : 4;           /*!< [27..24] DQ[6] delay chain control                                        */
    __IOM uint32_t dq7_dly_sel : 4;           /*!< [31..28] DQ[7] delay chain control                                        */
  } b;                                        /*!< bit fields for dpi_dq_dly0_2 */
} dpi_dq_dly0_2_t, *pdpi_dq_dly0_2_t;

/**
  \brief Union type to access dpi_dq_dly0_3 (@ 0x00000244).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000244) DQ_DLY Register 0_3                                        */

  struct {
    __IOM uint32_t dq0_dly_sel : 4;           /*!< [3..0] DQ[0] delay chain control                                          */
    __IOM uint32_t dq1_dly_sel : 4;           /*!< [7..4] DQ[1] delay chain control                                          */
    __IOM uint32_t dq2_dly_sel : 4;           /*!< [11..8] DQ[2] delay chain control                                         */
    __IOM uint32_t dq3_dly_sel : 4;           /*!< [15..12] DQ[3] delay chain control                                        */
    __IOM uint32_t dq4_dly_sel : 4;           /*!< [19..16] DQ[4] delay chain control                                        */
    __IOM uint32_t dq5_dly_sel : 4;           /*!< [23..20] DQ[5] delay chain control                                        */
    __IOM uint32_t dq6_dly_sel : 4;           /*!< [27..24] DQ[6] delay chain control                                        */
    __IOM uint32_t dq7_dly_sel : 4;           /*!< [31..28] DQ[7] delay chain control                                        */
  } b;                                        /*!< bit fields for dpi_dq_dly0_3 */
} dpi_dq_dly0_3_t, *pdpi_dq_dly0_3_t;

/**
  \brief Union type to access dpi_dq_dly1 (@ 0x00000248).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000248) DQ_DLY Register 1                                          */

  struct {
    __IOM uint32_t dqs_dly_sel_0 : 4;         /*!< [3..0] Slice0 DQS delay chain control                                     */
    __IOM uint32_t dm_dly_sel_0 : 4;          /*!< [7..4] Slice0 DM delay chain control                                      */
    __IOM uint32_t dqs_dly_sel_1 : 4;         /*!< [11..8] Slice1 DQS delay chain control                                    */
    __IOM uint32_t dm_dly_sel_1 : 4;          /*!< [15..12] Slice1 DM delay chain control                                    */
    __IOM uint32_t dqs_dly_sel_2 : 4;         /*!< [19..16] Slice2 DQS delay chain control                                   */
    __IOM uint32_t dm_dly_sel_2 : 4;          /*!< [23..20] Slice2 DM delay chain control                                    */
    __IOM uint32_t dqs_dly_sel_3 : 4;         /*!< [27..24] Slice3 DQS delay chain control                                   */
    __IOM uint32_t dm_dly_sel_3 : 4;          /*!< [31..28] Slice3 DM delay chain control                                    */
  } b;                                        /*!< bit fields for dpi_dq_dly1 */
} dpi_dq_dly1_t, *pdpi_dq_dly1_t;

/**
  \brief Union type to access dpi_dq_dly2 (@ 0x0000024C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000024C) DQ_DLY Register 2                                          */

  struct {
    __IOM uint32_t dqs_oe_dly_sel_0 : 4;      /*!< [3..0] Slice0 DQS output enable delay chain control                       */
    __IOM uint32_t dqs_oe_dly_sel_1 : 4;      /*!< [7..4] Slice1 DQS output enable delay chain control                       */
    __IOM uint32_t dqs_oe_dly_sel_2 : 4;      /*!< [11..8] Slice2 DQS output enable delay chain control                      */
    __IOM uint32_t dqs_oe_dly_sel_3 : 4;      /*!< [15..12] Slice3 DQS output enable delay chain control                     */
  } b;                                        /*!< bit fields for dpi_dq_dly2 */
} dpi_dq_dly2_t, *pdpi_dq_dly2_t;

/**
  \brief Union type to access dpi_read_ctrl0_0 (@ 0x00000254).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000254) Read Control Register 0_0                                  */

  struct {
    __IOM uint32_t tm_dqs_en  : 5;            /*!< [4..0] dqs_en latency from read command                                   */

    __IM  uint32_t            : 3;
    __IOM uint32_t dqs_en_dly_sel : 6;        /*!< [13..8] dqs_en delay chain control                                        */
    __IOM uint32_t dqs_fifo_dly_sel : 2;      /*!< [15..14] dqs clock to read FIFO delay control                             */
    __IOM uint32_t dqs_det_dly_sel : 4;       /*!< [19..16] dqs_det delay control                                            */
    __IOM uint32_t dqs_rclin_dly_sel : 5;     /*!< [24..20] dqs clock to receive_1st delay control                           */
  } b;                                        /*!< bit fields for dpi_read_ctrl0_0 */
} dpi_read_ctrl0_0_t, *pdpi_read_ctrl0_0_t;

/**
  \brief Union type to access dpi_read_ctrl0_1 (@ 0x00000258).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000258) Read Control Register 0_1                                  */

  struct {
    __IOM uint32_t tm_dqs_en  : 5;            /*!< [4..0] dqs_en latency from read command                                   */

    __IM  uint32_t            : 3;
    __IOM uint32_t dqs_en_dly_sel : 6;        /*!< [13..8] dqs_en delay chain control                                        */
    __IOM uint32_t dqs_fifo_dly_sel : 2;      /*!< [15..14] dqs clock to read FIFO delay control                             */
    __IOM uint32_t dqs_det_dly_sel : 4;       /*!< [19..16] dqs_det delay control                                            */
    __IOM uint32_t dqs_rclin_dly_sel : 5;     /*!< [24..20] dqs clock to receive_1st delay control                           */
  } b;                                        /*!< bit fields for dpi_read_ctrl0_1 */
} dpi_read_ctrl0_1_t, *pdpi_read_ctrl0_1_t;

/**
  \brief Union type to access dpi_read_ctrl1 (@ 0x00000264).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000264) Read Control Register 1                                    */

  struct {
    __IOM uint32_t tm_rd_fifo : 5;            /*!< [4..0] read FIFO latency from read command                                */

    __IM  uint32_t            : 3;
    __IOM uint32_t dq_lat_en_force_sig : 1;   /*!< [8..8] If set dq_lat_en_force_sel, dq latch enable is controlled
                                                   by dq_lat_en_force_sig.                                                   */
    __IOM uint32_t dq_lat_en_force_sel : 1;   /*!< [9..9] dq latch control                                                   */
    __IOM uint32_t rd_dly_follow_dq0 : 1;     /*!< [10..10] When this field is set to 1, FW can program read delay
                                                   chain setting by dq0                                                      */
    __IOM uint32_t dqsen_cal_en : 1;          /*!< [11..11] DQS enable calibration                                           */
    __IOM uint32_t dqsen_cal_sel : 6;         /*!< [17..12] Central point of DQS enable calibratio                           */
    __IOM uint32_t dqsen_cal_pre_sel : 4;     /*!< [21..18] Left point of DQS enable calibration                             */
    __IOM uint32_t dqsen_cal_pos_sel : 4;     /*!< [25..22] Right of DQS enable calibration                                  */
  } b;                                        /*!< bit fields for dpi_read_ctrl1 */
} dpi_read_ctrl1_t, *pdpi_read_ctrl1_t;

/**
  \brief Union type to access dpi_read_ctrl2_0 (@ 0x00000268).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000268) Read Control Register 2_0                                  */

  struct {
    __IOM uint32_t tm_odt_en  : 22;           /*!< [21..0] odt_en when read delay                                            */
    __IOM uint32_t odt_force_sig : 1;         /*!< [22..22] If set odt_force_sel, TE is controlled by odt_force_sig.         */
    __IOM uint32_t odt_force_sel : 1;         /*!< [23..23] ODT pad control.                                                 */
  } b;                                        /*!< bit fields for dpi_read_ctrl2_0 */
} dpi_read_ctrl2_0_t, *pdpi_read_ctrl2_0_t;

/**
  \brief Union type to access dpi_read_ctrl2_1 (@ 0x0000026C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000026C) Read Control Register 2_1                                  */

  struct {
    __IOM uint32_t tm_odt_en  : 22;           /*!< [21..0] odt_en when read delay                                            */
    __IOM uint32_t odt_force_sig : 1;         /*!< [22..22] If set odt_force_sel, TE is controlled by odt_force_sig.         */
    __IOM uint32_t odt_force_sel : 1;         /*!< [23..23] ODT pad control.                                                 */
  } b;                                        /*!< bit fields for dpi_read_ctrl2_1 */
} dpi_read_ctrl2_1_t, *pdpi_read_ctrl2_1_t;

/**
  \brief Union type to access dpi_cal_ls_sel_0 (@ 0x00000298).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000298) Calibration Left Shift Select 0                            */
  
  struct {
    __IOM uint32_t pre_shift_sel_0 : 3;       /*!< [2..0] Left sampling point of 3-point calibration for dq[0].              */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_1 : 3;       /*!< [6..4] Left sampling point of 3-point calibration for dq[1].              */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_2 : 3;       /*!< [10..8] Left sampling point of 3-point calibration for dq[2].             */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_3 : 3;       /*!< [14..12] Left sampling point of 3-point calibration for dq[3].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_4 : 3;       /*!< [18..16] Left sampling point of 3-point calibration for dq[4].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_5 : 3;       /*!< [22..20] Left sampling point of 3-point calibration for dq[5].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_6 : 3;       /*!< [26..24] Left sampling point of 3-point calibration for dq[6].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_7 : 3;       /*!< [30..28] Left sampling point of 3-point calibration for dq[7].            */
  } b;                                        /*!< bit fields for dpi_cal_ls_sel_0 */
} dpi_cal_ls_sel_0_t, *pdpi_cal_ls_sel_0_t;

/**
  \brief Union type to access dpi_cal_ls_sel_1 (@ 0x0000029C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000029C) Calibration Left Shift Select 1                            */
  
  struct {
    __IOM uint32_t pre_shift_sel_0 : 3;       /*!< [2..0] Left sampling point of 3-point calibration for dq[0].              */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_1 : 3;       /*!< [6..4] Left sampling point of 3-point calibration for dq[1].              */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_2 : 3;       /*!< [10..8] Left sampling point of 3-point calibration for dq[2].             */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_3 : 3;       /*!< [14..12] Left sampling point of 3-point calibration for dq[3].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_4 : 3;       /*!< [18..16] Left sampling point of 3-point calibration for dq[4].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_5 : 3;       /*!< [22..20] Left sampling point of 3-point calibration for dq[5].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_6 : 3;       /*!< [26..24] Left sampling point of 3-point calibration for dq[6].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_7 : 3;       /*!< [30..28] Left sampling point of 3-point calibration for dq[7].            */
  } b;                                        /*!< bit fields for dpi_cal_ls_sel_1 */
} dpi_cal_ls_sel_1_t, *pdpi_cal_ls_sel_1_t;

/**
  \brief Union type to access dpi_cal_rs_sel_0 (@ 0x000002A8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002A8) Calibration Right Shift Select 0                           */
  
  struct {
    __IOM uint32_t pre_shift_sel_0 : 3;       /*!< [2..0] Right sampling point of 3-point calibration for dq[0].             */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_1 : 3;       /*!< [6..4] Right sampling point of 3-point calibration for dq[1].             */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_2 : 3;       /*!< [10..8] Rightsampling point of 3-point calibration for dq[2].             */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_3 : 3;       /*!< [14..12] Right sampling point of 3-point calibration for dq[3].           */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_4 : 3;       /*!< [18..16] Right sampling point of 3-point calibration for dq[4].           */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_5 : 3;       /*!< [22..20] Rightsampling point of 3-point calibration for dq[5].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_6 : 3;       /*!< [26..24] Rightsampling point of 3-point calibration for dq[6].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_7 : 3;       /*!< [30..28] Rightsampling point of 3-point calibration for dq[7].            */
  } b;                                        /*!< bit fields for dpi_cal_rs_sel_0 */
} dpi_cal_rs_sel_0_t, *pdpi_cal_rs_sel_0_t;

/**
  \brief Union type to access dpi_cal_rs_sel_1 (@ 0x000002AC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002AC) Calibration Right Shift Select 1                           */
  
  struct {
    __IOM uint32_t pre_shift_sel_0 : 3;       /*!< [2..0] Right sampling point of 3-point calibration for dq[0].             */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_1 : 3;       /*!< [6..4] Right sampling point of 3-point calibration for dq[1].             */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_2 : 3;       /*!< [10..8] Right sampling point of 3-point calibration for dq[2].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_3 : 3;       /*!< [14..12] Right sampling point of 3-point calibration for dq[3].           */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_4 : 3;       /*!< [18..16] Right sampling point of 3-point calibration for dq[4].           */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_5 : 3;       /*!< [22..20] Rightsampling point of 3-point calibration for dq[5].            */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_6 : 3;       /*!< [26..24] Right sampling point of 3-point calibration for dq[6].           */
    __IM  uint32_t            : 1;
    __IOM uint32_t pre_shift_sel_7 : 3;       /*!< [30..28] Right sampling point of 3-point calibration for dq[7].           */
  } b;                                        /*!< bit fields for dpi_cal_rs_sel_1 */
} dpi_cal_rs_sel_1_t, *pdpi_cal_rs_sel_1_t;

/**
  \brief Union type to access dpi_dqs_in_dly_0 (@ 0x000002B8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002B8) DQS In Delay Register 0                                    */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_0 : 5;   /*!< [4..0] DQS_IN[0] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_1 : 5;   /*!< [12..8] DQS_IN[1] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_2 : 5;   /*!< [20..16] DQS_IN[2] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_3 : 5;   /*!< [28..24] DQS_IN[3] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_0 */
} dpi_dqs_in_dly_0_t, *pdpi_dqs_in_dly_0_t;

/**
  \brief Union type to access dpi_dqs_in_dly_0_1 (@ 0x000002BC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002BC) DQS In Delay Register 0_1                                  */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_0 : 5;   /*!< [4..0] DQS_IN[0] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_1 : 5;   /*!< [12..8] DQS_IN[1] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_2 : 5;   /*!< [20..16] DQS_IN[2] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_3 : 5;   /*!< [28..24] DQS_IN[3] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_0_1 */
} dpi_dqs_in_dly_0_1_t, *pdpi_dqs_in_dly_0_1_t;

/**
  \brief Union type to access dpi_dqs_in_dly_0_2 (@ 0x000002C0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002C0) DQS In Delay Register 0_2                                  */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_0 : 5;   /*!< [4..0] DQS_IN[0] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_1 : 5;   /*!< [12..8] DQS_IN[1] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_2 : 5;   /*!< [20..16] DQS_IN[2] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_3 : 5;   /*!< [28..24] DQS_IN[3] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_0_2 */
} dpi_dqs_in_dly_0_2_t, *pdpi_dqs_in_dly_0_2_t;

/**
  \brief Union type to access dpi_dqs_in_dly_0_3 (@ 0x000002C4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002C4) DQS In Delay Register 0_3                                  */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_0 : 5;   /*!< [4..0] DQS_IN[0] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_1 : 5;   /*!< [12..8] DQS_IN[1] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_2 : 5;   /*!< [20..16] DQS_IN[2] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_3 : 5;   /*!< [28..24] DQS_IN[3] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_0_3 */
} dpi_dqs_in_dly_0_3_t, *pdpi_dqs_in_dly_0_3_t;

/**
  \brief Union type to access dpi_dqs_in_dly_1 (@ 0x000002C8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002C8) DQS In Delay Register 1                                    */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_4 : 5;   /*!< [4..0] DQS_IN[4] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_5 : 5;   /*!< [12..8] DQS_IN[5] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_6 : 5;   /*!< [20..16] DQS_IN[6] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_7 : 5;   /*!< [28..24] DQS_IN[7] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_1 */
} dpi_dqs_in_dly_1_t, *pdpi_dqs_in_dly_1_t;

/**
  \brief Union type to access dpi_dqs_in_dly_1_1 (@ 0x000002CC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002CC) DQS In Delay Register 1_1                                  */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_4 : 5;   /*!< [4..0] DQS_IN[4] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_5 : 5;   /*!< [12..8] DQS_IN[5] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_6 : 5;   /*!< [20..16] DQS_IN[6] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_7 : 5;   /*!< [28..24] DQS_IN[7] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_1_1 */
} dpi_dqs_in_dly_1_1_t, *pdpi_dqs_in_dly_1_1_t;

/**
  \brief Union type to access dpi_dqs_in_dly_1_2 (@ 0x000002D0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002D0) DQS In Delay Register 1_2                                  */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_4 : 5;   /*!< [4..0] DQS_IN[4] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_5 : 5;   /*!< [12..8] DQS_IN[5] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_6 : 5;   /*!< [20..16] DQS_IN[6] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_7 : 5;   /*!< [28..24] DQS_IN[7] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_1_2 */
} dpi_dqs_in_dly_1_2_t, *pdpi_dqs_in_dly_1_2_t;

/**
  \brief Union type to access dpi_dqs_in_dly_1_3 (@ 0x000002D4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002D4) DQS In Delay Register 1_3                                  */

  struct {
    __IOM uint32_t fw_rd_dly_pos_sel_4 : 5;   /*!< [4..0] DQS_IN[4] raising edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_5 : 5;   /*!< [12..8] DQS_IN[5] raising edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_6 : 5;   /*!< [20..16] DQS_IN[6] raising edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_pos_sel_7 : 5;   /*!< [28..24] DQS_IN[7] raising edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_1_3 */
} dpi_dqs_in_dly_1_3_t, *pdpi_dqs_in_dly_1_3_t;

/**
  \brief Union type to access dpi_dqs_in_dly_2 (@ 0x000002D8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002D8) DQS In Delay Register 2                                    */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_0 : 5;   /*!< [4..0] DQS_IN[0] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_1 : 5;   /*!< [12..8] DQS_IN[1] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_2 : 5;   /*!< [20..16] DQS_IN[2] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_3 : 5;   /*!< [28..24] DQS_IN[3] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_2 */
} dpi_dqs_in_dly_2_t, *pdpi_dqs_in_dly_2_t;

/**
  \brief Union type to access dpi_dqs_in_dly_2_1 (@ 0x000002DC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002DC) DQS In Delay Register 2_1                                  */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_0 : 5;   /*!< [4..0] DQS_IN[0] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_1 : 5;   /*!< [12..8] DQS_IN[1] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_2 : 5;   /*!< [20..16] DQS_IN[2] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_3 : 5;   /*!< [28..24] DQS_IN[3] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_2_1 */
} dpi_dqs_in_dly_2_1_t, *pdpi_dqs_in_dly_2_1_t;

/**
  \brief Union type to access dpi_dqs_in_dly_2_2 (@ 0x000002E0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002E0) DQS In Delay Register 2_2                                  */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_0 : 5;   /*!< [4..0] DQS_IN[0] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_1 : 5;   /*!< [12..8] DQS_IN[1] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_2 : 5;   /*!< [20..16] DQS_IN[2] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_3 : 5;   /*!< [28..24] DQS_IN[3] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_2_2 */
} dpi_dqs_in_dly_2_2_t, *pdpi_dqs_in_dly_2_2_t;

/**
  \brief Union type to access dpi_dqs_in_dly_2_3 (@ 0x000002E4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002E4) DQS In Delay Register 2_3                                  */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_0 : 5;   /*!< [4..0] DQS_IN[0] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_1 : 5;   /*!< [12..8] DQS_IN[1] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_2 : 5;   /*!< [20..16] DQS_IN[2] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_3 : 5;   /*!< [28..24] DQS_IN[3] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_2_3 */
} dpi_dqs_in_dly_2_3_t, *pdpi_dqs_in_dly_2_3_t;

/**
  \brief Union type to access dpi_dqs_in_dly_3 (@ 0x000002E8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002E8) DQS In Delay Register 3                                    */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_4 : 5;   /*!< [4..0] DQS_IN[4] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_5 : 5;   /*!< [12..8] DQS_IN[5] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_6 : 5;   /*!< [20..16] DQS_IN[6] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_7 : 5;   /*!< [28..24] DQS_IN[7] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_3 */
} dpi_dqs_in_dly_3_t, *pdpi_dqs_in_dly_3_t;

/**
  \brief Union type to access dpi_dqs_in_dly_3_1 (@ 0x000002EC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002EC) DQS In Delay Register 3_1                                  */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_4 : 5;   /*!< [4..0] DQS_IN[4] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_5 : 5;   /*!< [12..8] DQS_IN[5] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_6 : 5;   /*!< [20..16] DQS_IN[6] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_7 : 5;   /*!< [28..24] DQS_IN[7] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_3_1 */
} dpi_dqs_in_dly_3_1_t, *pdpi_dqs_in_dly_3_1_t;

/**
  \brief Union type to access dpi_dqs_in_dly_3_2 (@ 0x000002F0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002F0) DQS In Delay Register 3_2                                  */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_4 : 5;   /*!< [4..0] DQS_IN[4] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_5 : 5;   /*!< [12..8] DQS_IN[5] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_6 : 5;   /*!< [20..16] DQS_IN[6] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_7 : 5;   /*!< [28..24] DQS_IN[7] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_3_2 */
} dpi_dqs_in_dly_3_2_t, *pdpi_dqs_in_dly_3_2_t;

/**
  \brief Union type to access dpi_dqs_in_dly_3_3 (@ 0x000002F4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002F4) DQS In Delay Register 3_3                                  */

  struct {
    __IOM uint32_t fw_rd_dly_neg_sel_4 : 5;   /*!< [4..0] DQS_IN[4] falling edge delay chain control                         */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_5 : 5;   /*!< [12..8] DQS_IN[5] falling edge delay chain control                        */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_6 : 5;   /*!< [20..16] DQS_IN[6] falling edge delay chain control                       */

    __IM  uint32_t            : 3;
    __IOM uint32_t fw_rd_dly_neg_sel_7 : 5;   /*!< [28..24] DQS_IN[7] falling edge delay chain control                       */
  } b;                                        /*!< bit fields for dpi_dqs_in_dly_3_3 */
} dpi_dqs_in_dly_3_3_t, *pdpi_dqs_in_dly_3_3_t;

/**
  \brief Union type to access dpi_dq_pad_ctrl (@ 0x0000031C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000031C) DQ PAD Control Register                                    */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_dq_pad_ctrl */
} dpi_dq_pad_ctrl_t, *pdpi_dq_pad_ctrl_t;

/**
  \brief Union type to access dpi_dq_pad_ctrl1 (@ 0x00000320).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000320) DQ PAD Control Register 1                                  */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_dq_pad_ctrl1 */
} dpi_dq_pad_ctrl1_t, *pdpi_dq_pad_ctrl1_t;

/**
  \brief Union type to access dpi_dqs_p_pad_ctrl (@ 0x00000324).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000324) DQS P Pad Control Register                                 */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_dqs_p_pad_ctrl */
} dpi_dqs_p_pad_ctrl_t, *pdpi_dqs_p_pad_ctrl_t;

/**
  \brief Union type to access dpi_dqs_p_pad_ctrl1 (@ 0x00000328).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000328) DQS P Pad Control Register 1                               */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_dqs_p_pad_ctrl1 */
} dpi_dqs_p_pad_ctrl1_t, *pdpi_dqs_p_pad_ctrl1_t;

/**
  \brief Union type to access dpi_dqs_n_pad_ctrl (@ 0x0000032C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000032C) DQS N Pad Control Register                                 */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 5;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_dqs_n_pad_ctrl */
} dpi_dqs_n_pad_ctrl_t, *pdpi_dqs_n_pad_ctrl_t;

/**
  \brief Union type to access dpi_dqs_n_pad_ctrl1 (@ 0x00000330).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000330) DQS N Pad Control Register 1                               */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 5;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_dqs_n_pad_ctrl1 */
} dpi_dqs_n_pad_ctrl1_t, *pdpi_dqs_n_pad_ctrl1_t;

/**
  \brief Union type to access dpi_ck_p_pad_ctrl (@ 0x00000334).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000334) CK P Pad Control Register                                  */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_ck_p_pad_ctrl */
} dpi_ck_p_pad_ctrl_t, *pdpi_ck_p_pad_ctrl_t;

/**
  \brief Union type to access dpi_ck_p_pad_ctrl1 (@ 0x00000338).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000338) CK P Pad Control Register 1                                */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_ck_p_pad_ctrl1 */
} dpi_ck_p_pad_ctrl1_t, *pdpi_ck_p_pad_ctrl1_t;

/**
  \brief Union type to access dpi_ck_n_pad_ctrl (@ 0x0000033C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000033C) CK N Pad Control Register                                  */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 5;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_ck_n_pad_ctrl */
} dpi_ck_n_pad_ctrl_t, *pdpi_ck_n_pad_ctrl_t;

/**
  \brief Union type to access dpi_ck_n_pad_ctrl1 (@ 0x00000340).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000340) CK N Pad Control Register 1                                */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 5;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_ck_n_pad_ctrl1 */
} dpi_ck_n_pad_ctrl1_t, *pdpi_ck_n_pad_ctrl1_t;

/**
  \brief Union type to access dpi_cmd_pad_ctrl (@ 0x00000344).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000344) CMD Pad Control Register                                   */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_cmd_pad_ctrl */
} dpi_cmd_pad_ctrl_t, *pdpi_cmd_pad_ctrl_t;

/**
  \brief Union type to access dpi_cs_pad_ctrl (@ 0x00000348).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000348) CS Pad Control Register                                    */
  
  struct {
    __IOM uint32_t ne         : 3;            /*!< [2..0] Driving control                                                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t pe         : 3;            /*!< [6..4] Driving control                                                    */
    __IM  uint32_t            : 3;
    __IOM uint32_t smt        : 1;            /*!< [10..10] Schmitt trigger                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t ttcn       : 4;            /*!< [15..12] On die termination control                                       */
    __IOM uint32_t ttcp       : 4;            /*!< [19..16] On die termination control                                       */
  } b;                                        /*!< bit fields for dpi_cs_pad_ctrl */
} dpi_cs_pad_ctrl_t, *pdpi_cs_pad_ctrl_t;

/**
  \brief Union type to access dpi_dpi_ctrl0 (@ 0x0000037C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000037C) DPI Control Register 0                                     */

  struct {
    __IOM uint32_t fw_set_mode : 2;           /*!< [1..0] FW set delay chain of data slice mode                              */
    __IOM uint32_t rst_fifo_mode : 2;         /*!< [3..2] Reset read FIFO pointer mode                                       */
    __IOM uint32_t cal_set_mode : 2;          /*!< [5..4] 3-point calibration set mode                                       */
    __IOM uint32_t dqsen_mode : 2;            /*!< [7..6] Generate DQS enable mode                                           */
    __IOM uint32_t ref_update_dly : 6;        /*!< [13..8] Update delay chain setting after receiving refresh command        */
    __IOM uint32_t ref_cmd_sel : 1;           /*!< [14..14] DDR command swap, when ref_cmd_sel == 1                          */

    __IM  uint32_t            : 1;
    __IOM uint32_t rd_update_dly : 5;         /*!< [20..16] Update delay chain setting after read data enable                */
    __IOM uint32_t wr_update_dly : 3;         /*!< [23..21] Update delay chain setting after write data enable               */
    __IOM uint32_t cmd_ph_en  : 1;            /*!< [24..24] Command output delay enable                                      */
    __IOM uint32_t cmd_ph_sel : 3;            /*!< [27..25] Command output delay                                             */
  } b;                                        /*!< bit fields for dpi_dpi_ctrl0 */
} dpi_dpi_ctrl0_t, *pdpi_dpi_ctrl0_t;

/**
  \brief Union type to access dpi_dpi_ctrl1 (@ 0x00000380).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000380) DPI Control Register 1                                     */

  struct {
    __IOM uint32_t fw_set_wr_dly : 1;         /*!< [0..0] FW set write delay chain of data slice                             */

    __OM  uint32_t write_en_0 : 1;            /*!< [1..1] Enable of the following row                                        */
    __OM  uint32_t fw_set_rd_dly : 1;         /*!< [2..2] FW set read delay chain of data slice                              */
    __OM  uint32_t write_en_1 : 1;            /*!< [3..3] Enable of the following row                                        */
    __OM  uint32_t fw_set_cal_range : 1;      /*!< [4..4] FW set 3-point calibration range                                   */
    __OM  uint32_t write_en_2 : 1;            /*!< [5..5] Enable of the following row                                        */
    __OM  uint32_t fw_set_rd_det : 1;         /*!< [6..6] FW set read delay chain of valid window detection                  */
    __OM  uint32_t write_en_3 : 1;            /*!< [7..7] Enable of the following row                                        */
  } b;                                        /*!< bit fields for dpi_dpi_ctrl1 */
} dpi_dpi_ctrl1_t, *pdpi_dpi_ctrl1_t;

/**
  \brief Union type to access dpi_bist_2to1_0 (@ 0x000003D8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000003D8) bist 2to1 Register 0                                       */

  struct {
    __IOM uint32_t bist_debug_sel : 5;        /*!< [4..0] debug selection                                                    */

    __IM  uint32_t            : 15;
    __IOM uint32_t bist_mode  : 3;            /*!< [22..20] Bist mode                                                        */
    __IOM uint32_t bist_en    : 1;            /*!< [23..23] Enable bist circuit in PHY                                       */
    __IOM uint32_t b_2to1_wrlv_delay_0 : 1;   /*!< [24..24] slice0 add one cycle delay for write leveling                    */
    __IOM uint32_t b_2to1_wrlv_delay_1 : 1;   /*!< [25..25] slice1 add one cycle delay for write leveling                    */
    __IOM uint32_t b_2to1_wrlv_delay_2 : 1;   /*!< [26..26] slice2 add one cycle delay for write leveling                    */
    __IOM uint32_t b_2to1_wrlv_delay_3 : 1;   /*!< [27..27] slice3 add one cycle delay for write leveling                    */
    __IOM uint32_t b_2to1_en_dq : 1;          /*!< [28..28] For data slice                                                   */
    __IOM uint32_t b_2to1_wrdelay : 1;        /*!< [29..29] add one cycle delay for write command                            */
    __IOM uint32_t b_2to1_rddelay : 1;        /*!< [30..30] add one cycle delay for read command                             */
    __IOM uint32_t b_2to1_en_adr : 1;         /*!< [31..31] For address and command slice                                    */
  } b;                                        /*!< bit fields for dpi_bist_2to1_0 */
} dpi_bist_2to1_0_t, *pdpi_bist_2to1_0_t;

/**
  \brief Union type to access dpi_int_ctrl (@ 0x000003E8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000003E8) Init Control Register                                      */

  struct {
    __IOM uint32_t int_dqs_en : 1;            /*!< [0..0] dqs_int enable                                                     */

    __OM  uint32_t write_en_0 : 1;            /*!< [1..1] Enable of the following row                                        */
    __IOM uint32_t int_cal_bdy_en : 1;        /*!< [2..2] cal_bdy_int enable                                                 */

    __OM  uint32_t write_en_1 : 1;            /*!< [3..3] Enable of the following row                                        */
    __IOM uint32_t fw_clr_dqs_int : 1;        /*!< [4..4] FW clear dqs_int (one cycle pulse, HW auto clear)                  */

    __OM  uint32_t write_en_2 : 1;            /*!< [5..5] Enable of the following row                                        */
    __IOM uint32_t int_cpu_0_en : 1;          /*!< [6..6] To CPU 0 interrupt enable                                          */

    __OM  uint32_t write_en_3 : 1;            /*!< [7..7] Enable of the following row                                        */
    __IOM uint32_t int_cpu_1_en : 1;          /*!< [8..8] To CPU 1 interrupt enable                                          */

    __OM  uint32_t write_en_4 : 1;            /*!< [9..9] Enable of the following row                                        */
    __IOM uint32_t int_cpu_2_en : 1;          /*!< [10..10] To CPU 2 interrupt enable                                        */

    __OM  uint32_t write_en_5 : 1;            /*!< [11..11] Enable of the following row                                      */
    __IOM uint32_t int_cpu_3_en : 1;          /*!< [12..12] To CPU 3 interrupt enable                                        */

    __OM  uint32_t write_en_6 : 1;            /*!< [13..13] Enable of the following row                                      */
    __IOM uint32_t int_pll_en : 1;            /*!< [14..14] Enable PLL stable interrupt                                      */

    __OM  uint32_t write_en_7 : 1;            /*!< [15..15] Enable of the following row                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t int_2to1_en : 1;           /*!< [20..20] Enable 2to1 read fail interrupt                                  */

    __OM  uint32_t write_en_10 : 1;           /*!< [21..21] Enable of the following row                                      */
    __IM  uint32_t            : 2;
    __IOM uint32_t int_fifo_ptr__en : 1;      /*!< [24..24] fifo_prt_int enable                                              */

    __OM  uint32_t write_en_12 : 1;           /*!< [25..25] Enable of the following row                                      */
  } b;                                        /*!< bit fields for dpi_int_ctrl */
} dpi_int_ctrl_t, *pdpi_int_ctrl_t;

/**
  \brief Union type to access dpi_int_status_0 (@ 0x000003EC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000003EC) Init Status Register 0                                     */

  struct {
    __IOM uint32_t dqs_int_0  : 1;            /*!< [0..0] dqs_int of data slice0                                             */
    __IOM uint32_t dqs_int_1  : 1;            /*!< [1..1] dqs_int of data slice1                                             */
    __IOM uint32_t dqs_int_2  : 1;            /*!< [2..2] dqs_int of data slice2                                             */
    __IOM uint32_t dqs_int_3  : 1;            /*!< [3..3] dqs_int of data slice3                                             */
  } b;                                        /*!< bit fields for dpi_int_status_0 */
} dpi_int_status_0_t, *pdpi_int_status_0_t;

/** @} */ /* End of group hs_hal_dpi_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_DPI_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_DPI_TYPE_H_

