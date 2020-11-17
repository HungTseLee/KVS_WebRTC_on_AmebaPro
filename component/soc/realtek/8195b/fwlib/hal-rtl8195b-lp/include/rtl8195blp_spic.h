/**************************************************************************//**
 * @file     rtl8195blp_spic.h
 * @brief    The header file of rtl8195blp_spic.c.
 * @version  1.00
 * @date     2017-08-22
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

#ifndef RTL8195BLP_SPIC_H
#define RTL8195BLP_SPIC_H

/**

        \addtogroup ls_hal_spic Flash Controller
        \ingroup 8195bl_hal
        \brief The Flash Controller (SPIC) module of the LS platform.
        @{
*/

#define SPI_FLASH_BASE 0x98000000       //!< Define flash memory address base


/**
  \brief  Enumeration to define flash IO mode
*/
enum spic_io_mode_e {
    SpicOneIOMode = 0,                  //!< Define One IO mode, 1-1-1
    SpicDualOutputMode = 1,             //!< Define Dual Output mode, 1-1-2
    SpicDualIOMode = 2,                 //!< Define Dual IO mode, 1-2-2
    SpicQuadOutputMode = 3,             //!< Define Quad Output mode, 1-1-4
    SpicQuadIOMode = 4,                 //!< Define Quad IO mode, 1-4-4
    SpicQuadIODtrMode = 5,              //!< Define Quad IO DTR mode, 1-4D-4D
    SpicQpiMode = 6,                    //!< Define QPI mode, 4-4-4
    SpicQpiDtrMode = 7,                 //!< Define QPI DTR mode, 4-4D-4D / 4D-4D-4D
    SpicOpiMode = 8,                    //!< Define OPI mode, 8-8-8
    SpicOpiDtrMode = 9                  //!< Define OPI DTR mode, 8D-8D-8D
};
typedef uint8_t spic_io_mode_t;


/**
  \brief  Enumeration to define transfer mode
*/
enum spic_tmod_mode_e {
    TxMode = 0,                         //!< Transmit mode
    RxMode = 3                          //!< Receive mode
};
typedef uint8_t spic_tmod_mode_t;

/**
  \brief  Enumeration to define the channle number used by the controller to access flash
*/
enum spic_channel_number_e {
    SingleChnl = 0,                     //!< Single channel
    DualChnl = 1,                       //!< Dual channel
    QuadChnl = 2,                       //!< Quad channel
    OctalChnl = 3                       //!< Octal channel
};
typedef uint8_t spic_channel_number_t;

/**
  \brief  Enumeration to define the byte number of address phase
*/
enum spic_address_phase_length_e {
    FourBytesLength = 0,                //!< Four bytes length
    OneByteLength = 1,                  //!< One byte length
    TwoBytesLength = 2,                 //!< Two bytes length
    ThreeBytesLength = 3                //!< Three bytes length
};
typedef uint8_t spic_address_phase_length_t;

/**
  \brief  Enumeration to define pinmux selection
*/
enum spic_pin_sel_e {
    SpicDualIOPin = 0,                  //!< Dual IO pin selection, with two data pins
    SpicQuadIOPin = 1,                  //!< Quad IO pin selection, with four data pins
    SpicOctalIOPin = 2                  //!< Octal IO pin selection, with eight data pins
};
typedef uint8_t spic_pin_sel_t;

/**
  \brief  The data struct of calibration setting
*/
typedef struct _spic_init_para_s {
    u8  baud_rate;                      //!< Valid baud rate setting
    u8  rd_dummy_cycle;                 //!< Valid flash controller's dummy cycle setting
    u8  delay_line;                     //!< Valid DPHY delay setting
    u8  valid;                          //!< Indicate data stored in the struct is valid or not
}spic_init_para_t, *pspic_init_para_t;

/**
  \brief  The data struct of SPIC adaptor
*/
typedef struct _hal_spic_adaptor_s {
    SPIC_Type *spic_dev;                //!< The register base of SPIC
    spic_init_para_t spic_init_data;    //!< Calibration settings
    pflash_cmd_t cmd;                   //!< The pointer pointing to flash commands
    pflash_dummy_cycle_t dummy_cycle;   //!< The pointer pointing to various dummy cycles
    u16  read_cmd;                      //!< Flash read command for current IO mode
    u16  rsvd;                          //!< Reserved
    u8   seq_dum_len;                   //!< Dummy cycle of sequentail read mode
    u8   flash_type;                    //!< Flash type
    u8   cmd_byte_num;                  //!< The byte number of command phase
    u8   addr_byte_num;                 //!< The byte number of address phase
    u8   spic_bit_mode;                 //!< Current IO mode used by the adaptor
    u8   spic_send_cmd_mode;            //!< IO mode to send flash commands
    u8   dtr_en;                        //!< Indicate whether DTR mode is enabled
    u8   cmd_chnl;                      //!< The channel number of command phase used by SPIC
    u8   addr_chnl;                     //!< The channel number of address phase used by SPIC
    u8   data_chnl;                     //!< The channel number of data phase used by SPIC
    u8   rsv_auto_dum_len;              //!< The backup information of auto dummy length
    u8   path_delay;                    //!< Reserved
}hal_spic_adaptor_t, *phal_spic_adaptor_t;



/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup ls_hal_spic_rom_func Flash Controller HAL ROM APIs
        @{
*/


/** \brief Description of spic_enable_rtl8195blp
 *
 *    spic_enable_rtl8195blp is used to enable flash controller.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
static inline void spic_enable_rtl8195blp(SPIC_Type *spic_dev)
{
    spic_dev->ssienr = ENABLE;
}

/** \brief Description of spic_disable_rtl8195blp
 *
 *    spic_disable_rtl8195blp is used to disable flash controller.
 *    Some registers should call this funciton first to disable the flash controller so that values can be correctly set to registers.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
static inline void spic_disable_rtl8195blp(SPIC_Type *spic_dev)
{
    spic_dev->ssienr = DISABLE;
}


/** \brief Description of spic_set_ctrl1_rtl8195blp
 *
 *    spic_set_ctrl1_rtl8195blp is used to set number of data frames (data length)expect to receive in user mode.
 *    The chip select line does not de-assert until the number of data received reaches the data length.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *   \param u32 length:      data length, the unit is byte.
 *
 *   \return void.
 */
static inline void spic_set_ctrl1_rtl8195blp(SPIC_Type *spic_dev, u32 length)
{
    spic_dev->ctrlr1_b.ndf = length;
}

/** \brief Description of spic_set_baudr_rtl8195blp
 *
 *    spic_set_baudr_rtl8195blp is used to flush FIFO of the flash controller.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *   \param u8 baudr:      The value of baud rate divider.
 *
 *   \return void.
 */
static inline void spic_set_baudr_rtl8195blp(SPIC_Type *spic_dev, u8 baudr)
{
    spic_dev->baudr_b.sckdv = baudr;
}

/** \brief Description of spic_set_fbaudr_rtl8195blp
 *
 *    spic_set_fbaudr_rtl8195blp is used to set baud rate of the flash controller for fast read.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *   \param u8 fbaudr:      The value of baud rate divider.
 *
 *   \return void.
 */
static inline void spic_set_fbaudr_rtl8195blp(SPIC_Type *spic_dev, u8 fbaudr)
{
    spic_dev->fbaudr_b.fsckdv = fbaudr;
}

/** \brief Description of spic_set_dummy_cycle_rtl8195blp
 *
 *    spic_set_dummy_cycle_rtl8195blp is used to tune timing to receive data correctly.
 *    This dummy cycle adjustment mechanism is implemented in the flash controller.
 *    The unit of dummy cycle is bus clock.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *   \param u8 dummy_cycle:      The level of dummy cycles, can be up to MAX_AUTO_LENGTH.
 *
 *   \return void.
 */
static inline void spic_set_dummy_cycle_rtl8195blp(SPIC_Type *spic_dev, u8 dummy_cycle)
{
    spic_dev->auto_length_b.rd_dummy_length = (u16)dummy_cycle;
}

/** \brief Description of spic_get_baudr_rtl8195blp
 *
 *    spic_get_baudr_rtl8195blp is used to get baud rate setting of the flash controller.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return u8: value of baud rate divider.
 */
static inline u8 spic_get_baudr_rtl8195blp(SPIC_Type *spic_dev)
{
    u8 baudr = 0;

    baudr = (u8)spic_dev->baudr;
    return baudr;
}

/** \brief Description of spic_get_fbaudr_rtl8195blp
 *
 *    spic_get_fbaudr_rtl8195blp is used to get baud rate setting of the flash controller for fast read.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return u8: value of baud rate divider.
 */
static inline u8 spic_get_fbaudr_rtl8195blp(SPIC_Type *spic_dev)
{
    u8 fbaudr = 0;

    fbaudr = (u8)spic_dev->fbaudr;
    return fbaudr;
}

void spic_load_default_setting_rtl8195blp(pspic_init_para_t pspic_init_data);
void spic_init_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor);
void spic_enable_seq_read_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor);
void spic_disable_seq_read_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor);
void spic_set_chnl_num_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor);
void spic_set_delay_line_rtl8195blp(u8 delay_line);
void spic_rx_cmd_8io_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_rx_cmd_4io_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_rx_cmd_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_8io_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_4io_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_8io_no_check_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_4io_no_check_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_no_check_rtl8195blp(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_wait_ready_rtl8195blp(SPIC_Type *spic_dev);
void spic_flush_fifo_rtl8195blp(SPIC_Type *spic_dev);

/** *@} */ /* End of group ls_hal_spic_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/**
  \brief  The data struct of flash controller stub functions. ROM code functions are accessed in RAM code through stub functions.
*/
typedef struct hal_spic_func_stubs_s {
    void (*spic_load_default_setting) (pspic_init_para_t pspic_init_data);
    void (*spic_init) (phal_spic_adaptor_t phal_spic_adaptor);
    void (*spic_enable_seq_read) (phal_spic_adaptor_t phal_spic_adaptor);
    void (*spic_disable_seq_read) (phal_spic_adaptor_t phal_spic_adaptor);
    void (*spic_set_chnl_num) (phal_spic_adaptor_t phal_spic_adaptor);
    void (*spic_set_delay_line ) (u8 delay_line);
    void (*spic_rx_cmd_8io ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_rx_cmd_4io ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_rx_cmd ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_tx_cmd_8io ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_tx_cmd_4io ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_tx_cmd ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_tx_cmd_8io_no_check ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_tx_cmd_4io_no_check ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_tx_cmd_no_check ) (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
    void (*spic_wait_ready) (SPIC_Type *spic_dev);
    void (*spic_flush_fifo) (SPIC_Type *spic_dev);
    uint32_t reserved[6];  // reserved space for next ROM code version function table extending.
} hal_spic_func_stubs_t;

/** *@} */ /* End of group ls_hal_spic */


#endif /* RTL8195BLP_SPIC_H */