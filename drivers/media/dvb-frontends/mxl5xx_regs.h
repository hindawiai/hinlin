<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011-2013 MaxLinear, Inc. All rights reserved
 *
 * License type: GPLv2
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम more details.
 *
 * This program may alternatively be licensed under a proprietary license from
 * MaxLinear, Inc.
 *
 */

#अगर_अघोषित __MXL58X_REGISTERS_H__
#घोषणा __MXL58X_REGISTERS_H__

#घोषणा HYDRA_INTR_STATUS_REG               0x80030008
#घोषणा HYDRA_INTR_MASK_REG                 0x8003000C

#घोषणा HYDRA_CRYSTAL_SETTING               0x3FFFC5F0 /* 0 - 24 MHz & 1 - 27 MHz */
#घोषणा HYDRA_CRYSTAL_CAP                   0x3FFFEDA4 /* 0 - 24 MHz & 1 - 27 MHz */

#घोषणा HYDRA_CPU_RESET_REG                 0x8003003C
#घोषणा HYDRA_CPU_RESET_DATA                0x00000400

#घोषणा HYDRA_RESET_TRANSPORT_FIFO_REG      0x80030028
#घोषणा HYDRA_RESET_TRANSPORT_FIFO_DATA     0x00000000

#घोषणा HYDRA_RESET_BBAND_REG               0x80030024
#घोषणा HYDRA_RESET_BBAND_DATA              0x00000000

#घोषणा HYDRA_RESET_XBAR_REG                0x80030020
#घोषणा HYDRA_RESET_XBAR_DATA               0x00000000

#घोषणा HYDRA_MODULES_CLK_1_REG             0x80030014
#घोषणा HYDRA_DISABLE_CLK_1                 0x00000000

#घोषणा HYDRA_MODULES_CLK_2_REG             0x8003001C
#घोषणा HYDRA_DISABLE_CLK_2                 0x0000000B

#घोषणा HYDRA_PRCM_ROOT_CLK_REG             0x80030018
#घोषणा HYDRA_PRCM_ROOT_CLK_DISABLE         0x00000000

#घोषणा HYDRA_CPU_RESET_CHECK_REG           0x80030008
#घोषणा HYDRA_CPU_RESET_CHECK_OFFSET        0x40000000  /* <bit 30> */

#घोषणा HYDRA_SKU_ID_REG                    0x90000190

#घोषणा FW_DL_SIGN_ADDR                     0x3FFFEAE0

/* Register to check अगर FW is running or not */
#घोषणा HYDRA_HEAR_BEAT                     0x3FFFEDDC

/* Firmware version */
#घोषणा HYDRA_FIRMWARE_VERSION              0x3FFFEDB8
#घोषणा HYDRA_FW_RC_VERSION                 0x3FFFCFAC

/* Firmware patch version */
#घोषणा HYDRA_FIRMWARE_PATCH_VERSION        0x3FFFEDC2

/* SOC operating temperature in C */
#घोषणा HYDRA_TEMPARATURE                   0x3FFFEDB4

/* Demod & Tuner status रेजिस्टरs */
/* Demod 0 status base address */
#घोषणा HYDRA_DEMOD_0_BASE_ADDR             0x3FFFC64C

/* Tuner 0 status base address */
#घोषणा HYDRA_TUNER_0_BASE_ADDR             0x3FFFCE4C

#घोषणा POWER_FROM_ADCRSSI_READBACK         0x3FFFEB6C

/* Macros to determine base address of respective demod or tuner */
#घोषणा HYDRA_DMD_STATUS_OFFSET(demodID)        ((demodID) * 0x100)
#घोषणा HYDRA_TUNER_STATUS_OFFSET(tunerID)      ((tunerID) * 0x40)

/* Demod status address offset from respective demod's base address */
#घोषणा HYDRA_DMD_AGC_DIG_LEVEL_ADDR_OFFSET               0x3FFFC64C
#घोषणा HYDRA_DMD_LOCK_STATUS_ADDR_OFFSET                 0x3FFFC650
#घोषणा HYDRA_DMD_ACQ_STATUS_ADDR_OFFSET                  0x3FFFC654

#घोषणा HYDRA_DMD_STANDARD_ADDR_OFFSET                    0x3FFFC658
#घोषणा HYDRA_DMD_SPECTRUM_INVERSION_ADDR_OFFSET          0x3FFFC65C
#घोषणा HYDRA_DMD_SPECTRUM_ROLL_OFF_ADDR_OFFSET           0x3FFFC660
#घोषणा HYDRA_DMD_SYMBOL_RATE_ADDR_OFFSET                 0x3FFFC664
#घोषणा HYDRA_DMD_MODULATION_SCHEME_ADDR_OFFSET           0x3FFFC668
#घोषणा HYDRA_DMD_FEC_CODE_RATE_ADDR_OFFSET               0x3FFFC66C

#घोषणा HYDRA_DMD_SNR_ADDR_OFFSET                         0x3FFFC670
#घोषणा HYDRA_DMD_FREQ_OFFSET_ADDR_OFFSET                 0x3FFFC674
#घोषणा HYDRA_DMD_CTL_FREQ_OFFSET_ADDR_OFFSET             0x3FFFC678
#घोषणा HYDRA_DMD_STR_FREQ_OFFSET_ADDR_OFFSET             0x3FFFC67C
#घोषणा HYDRA_DMD_FTL_FREQ_OFFSET_ADDR_OFFSET             0x3FFFC680
#घोषणा HYDRA_DMD_STR_NBC_SYNC_LOCK_ADDR_OFFSET           0x3FFFC684
#घोषणा HYDRA_DMD_CYCLE_SLIP_COUNT_ADDR_OFFSET            0x3FFFC688

#घोषणा HYDRA_DMD_DISPLAY_I_ADDR_OFFSET                   0x3FFFC68C
#घोषणा HYDRA_DMD_DISPLAY_Q_ADDR_OFFSET                   0x3FFFC68E

#घोषणा HYDRA_DMD_DVBS2_CRC_ERRORS_ADDR_OFFSET            0x3FFFC690
#घोषणा HYDRA_DMD_DVBS2_PER_COUNT_ADDR_OFFSET             0x3FFFC694
#घोषणा HYDRA_DMD_DVBS2_PER_WINDOW_ADDR_OFFSET            0x3FFFC698

#घोषणा HYDRA_DMD_DVBS_CORR_RS_ERRORS_ADDR_OFFSET         0x3FFFC69C
#घोषणा HYDRA_DMD_DVBS_UNCORR_RS_ERRORS_ADDR_OFFSET       0x3FFFC6A0
#घोषणा HYDRA_DMD_DVBS_BER_COUNT_ADDR_OFFSET              0x3FFFC6A4
#घोषणा HYDRA_DMD_DVBS_BER_WINDOW_ADDR_OFFSET             0x3FFFC6A8

/* Debug-purpose DVB-S DMD 0 */
#घोषणा HYDRA_DMD_DVBS_1ST_CORR_RS_ERRORS_ADDR_OFFSET     0x3FFFC6C8  /* corrected RS Errors: 1st iteration */
#घोषणा HYDRA_DMD_DVBS_1ST_UNCORR_RS_ERRORS_ADDR_OFFSET   0x3FFFC6CC  /* uncorrected RS Errors: 1st iteration */
#घोषणा HYDRA_DMD_DVBS_BER_COUNT_1ST_ADDR_OFFSET          0x3FFFC6D0
#घोषणा HYDRA_DMD_DVBS_BER_WINDOW_1ST_ADDR_OFFSET         0x3FFFC6D4

#घोषणा HYDRA_DMD_TUNER_ID_ADDR_OFFSET                    0x3FFFC6AC
#घोषणा HYDRA_DMD_DVBS2_PILOT_ON_OFF_ADDR_OFFSET          0x3FFFC6B0
#घोषणा HYDRA_DMD_FREQ_SEARCH_RANGE_KHZ_ADDR_OFFSET       0x3FFFC6B4
#घोषणा HYDRA_DMD_STATUS_LOCK_ADDR_OFFSET                 0x3FFFC6B8
#घोषणा HYDRA_DMD_STATUS_CENTER_FREQ_IN_KHZ_ADDR          0x3FFFC704
#घोषणा HYDRA_DMD_STATUS_INPUT_POWER_ADDR                 0x3FFFC708

/* DVB-S new scaled_BER_count क्रम a new BER API, see HYDRA-1343 "DVB-S post viterbi information" */
#घोषणा DMD0_STATUS_DVBS_1ST_SCALED_BER_COUNT_ADDR        0x3FFFC710 /* DMD 0: 1st iteration BER count scaled by HYDRA_BER_COUNT_SCALING_FACTOR */
#घोषणा DMD0_STATUS_DVBS_SCALED_BER_COUNT_ADDR            0x3FFFC714 /* DMD 0: 2nd iteration BER count scaled by HYDRA_BER_COUNT_SCALING_FACTOR */

#घोषणा DMD0_SPECTRUM_MIN_GAIN_STATUS                     0x3FFFC73C
#घोषणा DMD0_SPECTRUM_MIN_GAIN_WB_SAGC_VALUE              0x3FFFC740
#घोषणा DMD0_SPECTRUM_MIN_GAIN_NB_SAGC_VALUE              0x3FFFC744

#घोषणा HYDRA_DMD_STATUS_END_ADDR_OFFSET                  0x3FFFC748

/* Tuner status address offset from respective tuners's base address */
#घोषणा HYDRA_TUNER_DEMOD_ID_ADDR_OFFSET                  0x3FFFCE4C
#घोषणा HYDRA_TUNER_AGC_LOCK_OFFSET                       0x3FFFCE50
#घोषणा HYDRA_TUNER_SPECTRUM_STATUS_OFFSET                0x3FFFCE54
#घोषणा HYDRA_TUNER_SPECTRUM_BIN_SIZE_OFFSET              0x3FFFCE58
#घोषणा HYDRA_TUNER_SPECTRUM_ADDRESS_OFFSET               0x3FFFCE5C
#घोषणा HYDRA_TUNER_ENABLE_COMPLETE                       0x3FFFEB78

#घोषणा HYDRA_DEMOD_STATUS_LOCK(devId, demodId)   ग_लिखो_रेजिस्टर(devId, (HYDRA_DMD_STATUS_LOCK_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)), MXL_YES)
#घोषणा HYDRA_DEMOD_STATUS_UNLOCK(devId, demodId) ग_लिखो_रेजिस्टर(devId, (HYDRA_DMD_STATUS_LOCK_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)), MXL_NO)

#घोषणा HYDRA_VERSION                                     0x3FFFEDB8
#घोषणा HYDRA_DEMOD0_VERSION                              0x3FFFEDBC
#घोषणा HYDRA_DEMOD1_VERSION                              0x3FFFEDC0
#घोषणा HYDRA_DEMOD2_VERSION                              0x3FFFEDC4
#घोषणा HYDRA_DEMOD3_VERSION                              0x3FFFEDC8
#घोषणा HYDRA_DEMOD4_VERSION                              0x3FFFEDCC
#घोषणा HYDRA_DEMOD5_VERSION                              0x3FFFEDD0
#घोषणा HYDRA_DEMOD6_VERSION                              0x3FFFEDD4
#घोषणा HYDRA_DEMOD7_VERSION                              0x3FFFEDD8
#घोषणा HYDRA_HEAR_BEAT                                   0x3FFFEDDC
#घोषणा HYDRA_SKU_MGMT                                    0x3FFFEBC0

#घोषणा MXL_HYDRA_FPGA_A_ADDRESS                          0x91C00000
#घोषणा MXL_HYDRA_FPGA_B_ADDRESS                          0x91D00000

/* TS control base address */
#घोषणा HYDRA_TS_CTRL_BASE_ADDR                           0x90700000

#घोषणा MPEG_MUX_MODE_SLICE0_REG            (HYDRA_TS_CTRL_BASE_ADDR + 0x08)

#घोषणा MPEG_MUX_MODE_SLICE1_REG            (HYDRA_TS_CTRL_BASE_ADDR + 0x08)

#घोषणा PID_BANK_SEL_SLICE0_REG             (HYDRA_TS_CTRL_BASE_ADDR + 0x190)
#घोषणा PID_BANK_SEL_SLICE1_REG             (HYDRA_TS_CTRL_BASE_ADDR + 0x1B0)

#घोषणा MPEG_CLK_GATED_REG                  (HYDRA_TS_CTRL_BASE_ADDR + 0x20)

#घोषणा MPEG_CLK_ALWAYS_ON_REG              (HYDRA_TS_CTRL_BASE_ADDR + 0x1D4)

#घोषणा HYDRA_REGULAR_PID_BANK_A_REG        (HYDRA_TS_CTRL_BASE_ADDR + 0x190)

#घोषणा HYDRA_FIXED_PID_BANK_A_REG          (HYDRA_TS_CTRL_BASE_ADDR + 0x190)

#घोषणा HYDRA_REGULAR_PID_BANK_B_REG        (HYDRA_TS_CTRL_BASE_ADDR + 0x1B0)

#घोषणा HYDRA_FIXED_PID_BANK_B_REG          (HYDRA_TS_CTRL_BASE_ADDR + 0x1B0)

#घोषणा FIXED_PID_TBL_REG_ADDRESS_0         (HYDRA_TS_CTRL_BASE_ADDR + 0x9000)
#घोषणा FIXED_PID_TBL_REG_ADDRESS_1         (HYDRA_TS_CTRL_BASE_ADDR + 0x9100)
#घोषणा FIXED_PID_TBL_REG_ADDRESS_2         (HYDRA_TS_CTRL_BASE_ADDR + 0x9200)
#घोषणा FIXED_PID_TBL_REG_ADDRESS_3         (HYDRA_TS_CTRL_BASE_ADDR + 0x9300)

#घोषणा FIXED_PID_TBL_REG_ADDRESS_4         (HYDRA_TS_CTRL_BASE_ADDR + 0xB000)
#घोषणा FIXED_PID_TBL_REG_ADDRESS_5         (HYDRA_TS_CTRL_BASE_ADDR + 0xB100)
#घोषणा FIXED_PID_TBL_REG_ADDRESS_6         (HYDRA_TS_CTRL_BASE_ADDR + 0xB200)
#घोषणा FIXED_PID_TBL_REG_ADDRESS_7         (HYDRA_TS_CTRL_BASE_ADDR + 0xB300)

#घोषणा REGULAR_PID_TBL_REG_ADDRESS_0       (HYDRA_TS_CTRL_BASE_ADDR + 0x8000)
#घोषणा REGULAR_PID_TBL_REG_ADDRESS_1       (HYDRA_TS_CTRL_BASE_ADDR + 0x8200)
#घोषणा REGULAR_PID_TBL_REG_ADDRESS_2       (HYDRA_TS_CTRL_BASE_ADDR + 0x8400)
#घोषणा REGULAR_PID_TBL_REG_ADDRESS_3       (HYDRA_TS_CTRL_BASE_ADDR + 0x8600)

#घोषणा REGULAR_PID_TBL_REG_ADDRESS_4       (HYDRA_TS_CTRL_BASE_ADDR + 0xA000)
#घोषणा REGULAR_PID_TBL_REG_ADDRESS_5       (HYDRA_TS_CTRL_BASE_ADDR + 0xA200)
#घोषणा REGULAR_PID_TBL_REG_ADDRESS_6       (HYDRA_TS_CTRL_BASE_ADDR + 0xA400)
#घोषणा REGULAR_PID_TBL_REG_ADDRESS_7       (HYDRA_TS_CTRL_BASE_ADDR + 0xA600)

/***************************************************************************/

#घोषणा PAD_MUX_GPIO_00_SYNC_BASEADDR                          0x90000188


#घोषणा PAD_MUX_UART_RX_C_PINMUX_BASEADDR 0x9000001C

#घोषणा   XPT_PACKET_GAP_MIN_BASEADDR                            0x90700044
#घोषणा   XPT_NCO_COUNT_BASEADDR                                 0x90700238

#घोषणा   XPT_NCO_COUNT_BASEADDR1                                0x9070023C

/* V2 DigRF status रेजिस्टर */

#घोषणा   XPT_PID_BASEADDR                                       0x90708000

#घोषणा   XPT_PID_REMAP_BASEADDR                                 0x90708004

#घोषणा   XPT_KNOWN_PID_BASEADDR                                 0x90709000

#घोषणा   XPT_PID_BASEADDR1                                      0x9070A000

#घोषणा   XPT_PID_REMAP_BASEADDR1                                0x9070A004

#घोषणा   XPT_KNOWN_PID_BASEADDR1                                0x9070B000

#घोषणा   XPT_BERT_LOCK_BASEADDR                                 0x907000B8

#घोषणा   XPT_BERT_BASEADDR                                      0x907000BC

#घोषणा   XPT_BERT_INVERT_BASEADDR                               0x907000C0

#घोषणा   XPT_BERT_HEADER_BASEADDR                               0x907000C4

#घोषणा   XPT_BERT_BASEADDR1                                     0x907000C8

#घोषणा   XPT_BERT_BIT_COUNT0_BASEADDR                           0x907000CC

#घोषणा   XPT_BERT_BIT_COUNT0_BASEADDR1                          0x907000D0

#घोषणा   XPT_BERT_BIT_COUNT1_BASEADDR                           0x907000D4

#घोषणा   XPT_BERT_BIT_COUNT1_BASEADDR1                          0x907000D8

#घोषणा   XPT_BERT_BIT_COUNT2_BASEADDR                           0x907000DC

#घोषणा   XPT_BERT_BIT_COUNT2_BASEADDR1                          0x907000E0

#घोषणा   XPT_BERT_BIT_COUNT3_BASEADDR                           0x907000E4

#घोषणा   XPT_BERT_BIT_COUNT3_BASEADDR1                          0x907000E8

#घोषणा   XPT_BERT_BIT_COUNT4_BASEADDR                           0x907000EC

#घोषणा   XPT_BERT_BIT_COUNT4_BASEADDR1                          0x907000F0

#घोषणा   XPT_BERT_BIT_COUNT5_BASEADDR                           0x907000F4

#घोषणा   XPT_BERT_BIT_COUNT5_BASEADDR1                          0x907000F8

#घोषणा   XPT_BERT_BIT_COUNT6_BASEADDR                           0x907000FC

#घोषणा   XPT_BERT_BIT_COUNT6_BASEADDR1                          0x90700100

#घोषणा   XPT_BERT_BIT_COUNT7_BASEADDR                           0x90700104

#घोषणा   XPT_BERT_BIT_COUNT7_BASEADDR1                          0x90700108

#घोषणा   XPT_BERT_ERR_COUNT0_BASEADDR                           0x9070010C

#घोषणा   XPT_BERT_ERR_COUNT0_BASEADDR1                          0x90700110

#घोषणा   XPT_BERT_ERR_COUNT1_BASEADDR                           0x90700114

#घोषणा   XPT_BERT_ERR_COUNT1_BASEADDR1                          0x90700118

#घोषणा   XPT_BERT_ERR_COUNT2_BASEADDR                           0x9070011C

#घोषणा   XPT_BERT_ERR_COUNT2_BASEADDR1                          0x90700120

#घोषणा   XPT_BERT_ERR_COUNT3_BASEADDR                           0x90700124

#घोषणा   XPT_BERT_ERR_COUNT3_BASEADDR1                          0x90700128

#घोषणा   XPT_BERT_ERR_COUNT4_BASEADDR                           0x9070012C

#घोषणा   XPT_BERT_ERR_COUNT4_BASEADDR1                          0x90700130

#घोषणा   XPT_BERT_ERR_COUNT5_BASEADDR                           0x90700134

#घोषणा   XPT_BERT_ERR_COUNT5_BASEADDR1                          0x90700138

#घोषणा   XPT_BERT_ERR_COUNT6_BASEADDR                           0x9070013C

#घोषणा   XPT_BERT_ERR_COUNT6_BASEADDR1                          0x90700140

#घोषणा   XPT_BERT_ERR_COUNT7_BASEADDR                           0x90700144

#घोषणा   XPT_BERT_ERR_COUNT7_BASEADDR1                          0x90700148

#घोषणा   XPT_BERT_ERROR_BASEADDR                                0x9070014C

#घोषणा   XPT_BERT_ANALYZER_BASEADDR                             0x90700150

#घोषणा   XPT_BERT_ANALYZER_BASEADDR1                            0x90700154

#घोषणा   XPT_BERT_ANALYZER_BASEADDR2                            0x90700158

#घोषणा   XPT_BERT_ANALYZER_BASEADDR3                            0x9070015C

#घोषणा   XPT_BERT_ANALYZER_BASEADDR4                            0x90700160

#घोषणा   XPT_BERT_ANALYZER_BASEADDR5                            0x90700164

#घोषणा   XPT_BERT_ANALYZER_BASEADDR6                            0x90700168

#घोषणा   XPT_BERT_ANALYZER_BASEADDR7                            0x9070016C

#घोषणा   XPT_BERT_ANALYZER_BASEADDR8                            0x90700170

#घोषणा   XPT_BERT_ANALYZER_BASEADDR9                            0x90700174

#घोषणा   XPT_DMD0_BASEADDR                                      0x9070024C

/* V2 AGC Gain Freeze & step */
#घोषणा   DBG_ENABLE_DISABLE_AGC                                 (0x3FFFCF60) /* 1: DISABLE, 0:ENABLE */
#घोषणा   WB_DFE0_DFE_FB_RF1_BASEADDR                            0x903004A4

#घोषणा   WB_DFE1_DFE_FB_RF1_BASEADDR                            0x904004A4

#घोषणा   WB_DFE2_DFE_FB_RF1_BASEADDR                            0x905004A4

#घोषणा   WB_DFE3_DFE_FB_RF1_BASEADDR                            0x906004A4

#घोषणा   AFE_REG_D2A_TA_RFFE_LNA_BO_1P8_BASEADDR                0x90200104

#घोषणा   AFE_REG_AFE_REG_SPARE_BASEADDR                         0x902000A0

#घोषणा   AFE_REG_AFE_REG_SPARE_BASEADDR1                        0x902000B4

#घोषणा   AFE_REG_AFE_REG_SPARE_BASEADDR2                        0x902000C4

#घोषणा   AFE_REG_AFE_REG_SPARE_BASEADDR3                        0x902000D4

#घोषणा   WB_DFE0_DFE_FB_AGC_BASEADDR                            0x90300498

#घोषणा   WB_DFE1_DFE_FB_AGC_BASEADDR                            0x90400498

#घोषणा   WB_DFE2_DFE_FB_AGC_BASEADDR                            0x90500498

#घोषणा   WB_DFE3_DFE_FB_AGC_BASEADDR                            0x90600498

#घोषणा   WDT_WD_INT_BASEADDR                                    0x8002000C

#घोषणा   FSK_TX_FTM_BASEADDR                                    0x80090000

#घोषणा   FSK_TX_FTM_TX_CNT_BASEADDR                             0x80090018

#घोषणा   AFE_REG_D2A_FSK_BIAS_BASEADDR                          0x90200040

#घोषणा   DMD_TEI_BASEADDR                                       0x3FFFEBE0

#पूर्ण_अगर /* __MXL58X_REGISTERS_H__ */
