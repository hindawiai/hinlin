<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _css_receiver_2400_defs_h_
#घोषणा _css_receiver_2400_defs_h_

#समावेश "css_receiver_2400_common_defs.h"

#घोषणा CSS_RECEIVER_DATA_WIDTH                8
#घोषणा CSS_RECEIVER_RX_TRIG                   4
#घोषणा CSS_RECEIVER_RF_WORD                  32
#घोषणा CSS_RECEIVER_IMG_PROC_RF_ADDR         10
#घोषणा CSS_RECEIVER_CSI_RF_ADDR               4
#घोषणा CSS_RECEIVER_DATA_OUT                 12
#घोषणा CSS_RECEIVER_CHN_NO                    2
#घोषणा CSS_RECEIVER_DWORD_CNT                11
#घोषणा CSS_RECEIVER_FORMAT_TYP                5
#घोषणा CSS_RECEIVER_HRESPONSE                 2
#घोषणा CSS_RECEIVER_STATE_WIDTH               3
#घोषणा CSS_RECEIVER_FIFO_DAT                 32
#घोषणा CSS_RECEIVER_CNT_VAL                   2
#घोषणा CSS_RECEIVER_PRED10_VAL               10
#घोषणा CSS_RECEIVER_PRED12_VAL               12
#घोषणा CSS_RECEIVER_CNT_WIDTH                 8
#घोषणा CSS_RECEIVER_WORD_CNT                 16
#घोषणा CSS_RECEIVER_PIXEL_LEN                 6
#घोषणा CSS_RECEIVER_PIXEL_CNT                 5
#घोषणा CSS_RECEIVER_COMP_8_BIT                8
#घोषणा CSS_RECEIVER_COMP_7_BIT                7
#घोषणा CSS_RECEIVER_COMP_6_BIT                6

#घोषणा CSI_CONFIG_WIDTH                       4

/* भागision of gen_लघु data, ch_id and fmt_type over streaming data पूर्णांकerface */
#घोषणा _HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_DATA_BIT_LSB     0
#घोषणा _HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_FMT_TYPE_BIT_LSB (_HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_DATA_BIT_LSB     + _HRT_CSS_RECEIVER_2400_GEN_SHORT_DATA_WIDTH)
#घोषणा _HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_CH_ID_BIT_LSB    (_HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_FMT_TYPE_BIT_LSB + _HRT_CSS_RECEIVER_2400_GEN_SHORT_FMT_TYPE_WIDTH)
#घोषणा _HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_DATA_BIT_MSB     (_HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_FMT_TYPE_BIT_LSB - 1)
#घोषणा _HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_FMT_TYPE_BIT_MSB (_HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_CH_ID_BIT_LSB    - 1)
#घोषणा _HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_CH_ID_BIT_MSB    (_HRT_CSS_RECEIVER_2400_GEN_SHORT_STR_REAL_WIDTH       - 1)

#घोषणा _HRT_CSS_RECEIVER_2400_REG_ALIGN 4
#घोषणा _HRT_CSS_RECEIVER_2400_BYTES_PER_PKT             4

#घोषणा hrt_css_receiver_2400_4_lane_port_offset  0x100
#घोषणा hrt_css_receiver_2400_1_lane_port_offset  0x200
#घोषणा hrt_css_receiver_2400_2_lane_port_offset  0x300
#घोषणा hrt_css_receiver_2400_backend_port_offset 0x100

#घोषणा _HRT_CSS_RECEIVER_2400_DEVICE_READY_REG_IDX      0
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_STATUS_REG_IDX        1
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ENABLE_REG_IDX        2
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_FUNC_PROG_REG_IDX    3
#घोषणा _HRT_CSS_RECEIVER_2400_INIT_COUNT_REG_IDX        4
#घोषणा _HRT_CSS_RECEIVER_2400_FS_TO_LS_DELAY_REG_IDX    7
#घोषणा _HRT_CSS_RECEIVER_2400_LS_TO_DATA_DELAY_REG_IDX  8
#घोषणा _HRT_CSS_RECEIVER_2400_DATA_TO_LE_DELAY_REG_IDX  9
#घोषणा _HRT_CSS_RECEIVER_2400_LE_TO_FE_DELAY_REG_IDX   10
#घोषणा _HRT_CSS_RECEIVER_2400_FE_TO_FS_DELAY_REG_IDX   11
#घोषणा _HRT_CSS_RECEIVER_2400_LE_TO_LS_DELAY_REG_IDX   12
#घोषणा _HRT_CSS_RECEIVER_2400_TWO_PIXEL_EN_REG_IDX     13
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_18_DATAID_REG_IDX  14
#घोषणा _HRT_CSS_RECEIVER_2400_SYNC_COUNT_REG_IDX       15
#घोषणा _HRT_CSS_RECEIVER_2400_RX_COUNT_REG_IDX         16
#घोषणा _HRT_CSS_RECEIVER_2400_BACKEND_RST_REG_IDX      17
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG0_IDX 18
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG1_IDX 19
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG0_IDX 20
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG1_IDX 21
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG0_IDX 22
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG1_IDX 23
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG0_IDX 24
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG1_IDX 25
#घोषणा _HRT_CSS_RECEIVER_2400_RAW18_REG_IDX            26
#घोषणा _HRT_CSS_RECEIVER_2400_FORCE_RAW8_REG_IDX       27
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_REG_IDX            28

/* Interrupt bits क्रम IRQ_STATUS and IRQ_ENABLE रेजिस्टरs */
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_OVERRUN_BIT                0
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_RESERVED_BIT               1
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_SLEEP_MODE_ENTRY_BIT       2
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_SLEEP_MODE_EXIT_BIT        3
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_SOT_HS_BIT             4
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_SOT_SYNC_HS_BIT        5
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_CONTROL_BIT            6
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_DOUBLE_BIT         7
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_CORRECTED_BIT      8
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_NO_CORRECTION_BIT  9
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_CRC_BIT               10
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ID_BIT                11
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_FRAME_SYNC_BIT        12
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_FRAME_DATA_BIT        13
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_DATA_TIMEOUT_BIT          14
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ESCAPE_BIT            15
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_LINE_SYNC_BIT         16

#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_OVERRUN_CAUSE_                  "Fifo Overrun"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_RESERVED_CAUSE_                 "Reserved"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_SLEEP_MODE_ENTRY_CAUSE_         "Sleep mode entry"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_SLEEP_MODE_EXIT_CAUSE_          "Sleep mode exit"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_SOT_HS_CAUSE_               "Error high speed SOT"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_SOT_SYNC_HS_CAUSE_          "Error high speed sync SOT"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_CONTROL_CAUSE_              "Error control"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_DOUBLE_CAUSE_           "Error correction double bit"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_CORRECTED_CAUSE_        "Error correction single bit"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_NO_CORRECTION_CAUSE_    "No error"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_CRC_CAUSE_                  "Error cyclic redundancy check"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ID_CAUSE_                   "Error id"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_FRAME_SYNC_CAUSE_           "Error frame sync"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_FRAME_DATA_CAUSE_           "Error frame data"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_DATA_TIMEOUT_CAUSE_             "Data time-out"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_ESCAPE_CAUSE_               "Error escape"
#घोषणा _HRT_CSS_RECEIVER_2400_IRQ_ERR_LINE_SYNC_CAUSE_            "Error line sync"

/* Bits क्रम CSI2_DEVICE_READY रेजिस्टर */
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_DEVICE_READY_IDX                          0
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_MASK_INIT_TIME_OUT_ERR_IDX                2
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_MASK_OVER_RUN_ERR_IDX                     3
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_MASK_SOT_SYNC_ERR_IDX                     4
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_MASK_RECEIVE_DATA_TIME_OUT_ERR_IDX        5
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_MASK_ECC_TWO_BIT_ERR_IDX                  6
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_MASK_DATA_ID_ERR_IDX                      7

/* Bits क्रम CSI2_FUNC_PROG रेजिस्टर */
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_DATA_TIMEOUT_IDX    0
#घोषणा _HRT_CSS_RECEIVER_2400_CSI2_DATA_TIMEOUT_BITS   19

/* Bits क्रम INIT_COUNT रेजिस्टर */
#घोषणा _HRT_CSS_RECEIVER_2400_INIT_TIMER_IDX  0
#घोषणा _HRT_CSS_RECEIVER_2400_INIT_TIMER_BITS 16

/* Bits क्रम COUNT रेजिस्टरs */
#घोषणा _HRT_CSS_RECEIVER_2400_SYNC_COUNT_IDX     0
#घोषणा _HRT_CSS_RECEIVER_2400_SYNC_COUNT_BITS    8
#घोषणा _HRT_CSS_RECEIVER_2400_RX_COUNT_IDX       0
#घोषणा _HRT_CSS_RECEIVER_2400_RX_COUNT_BITS      8

/* Bits क्रम RAW116_18_DATAID रेजिस्टर */
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_18_DATAID_RAW16_BITS_IDX   0
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_18_DATAID_RAW16_BITS_BITS  6
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_18_DATAID_RAW18_BITS_IDX   8
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_18_DATAID_RAW18_BITS_BITS  6

/* Bits क्रम COMP_FORMAT रेजिस्टर, this selects the compression data क्रमmat */
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_RAW_BITS_IDX  0
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_RAW_BITS_BITS 8
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_NUM_BITS_IDX  (_HRT_CSS_RECEIVER_2400_COMP_RAW_BITS_IDX + _HRT_CSS_RECEIVER_2400_COMP_RAW_BITS_BITS)
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_NUM_BITS_BITS 8

/* Bits क्रम COMP_PREDICT रेजिस्टर, this selects the predictor algorithm */
#घोषणा _HRT_CSS_RECEIVER_2400_PREDICT_NO_COMP 0
#घोषणा _HRT_CSS_RECEIVER_2400_PREDICT_1       1
#घोषणा _HRT_CSS_RECEIVER_2400_PREDICT_2       2

/* Number of bits used क्रम the delay रेजिस्टरs */
#घोषणा _HRT_CSS_RECEIVER_2400_DELAY_BITS 8

/* Bits क्रम COMP_SCHEME रेजिस्टर, this  selects the compression scheme क्रम a VC */
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD1_BITS_IDX  0
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD2_BITS_IDX  5
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD3_BITS_IDX  10
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD4_BITS_IDX  15
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD5_BITS_IDX  20
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD6_BITS_IDX  25
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD7_BITS_IDX  0
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD8_BITS_IDX  5
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD_BITS_BITS  5
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD_FMT_BITS_IDX   0
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD_FMT_BITS_BITS  3
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD_PRED_BITS_IDX  3
#घोषणा _HRT_CSS_RECEIVER_2400_COMP_SCHEME_USD_PRED_BITS_BITS 2

/* BITS क्रम backend RAW16 and RAW 18 रेजिस्टरs */

#घोषणा _HRT_CSS_RECEIVER_2400_RAW18_DATAID_IDX    0
#घोषणा _HRT_CSS_RECEIVER_2400_RAW18_DATAID_BITS   6
#घोषणा _HRT_CSS_RECEIVER_2400_RAW18_OPTION_IDX    6
#घोषणा _HRT_CSS_RECEIVER_2400_RAW18_OPTION_BITS   2
#घोषणा _HRT_CSS_RECEIVER_2400_RAW18_EN_IDX        8
#घोषणा _HRT_CSS_RECEIVER_2400_RAW18_EN_BITS       1

#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_DATAID_IDX    0
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_DATAID_BITS   6
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_OPTION_IDX    6
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_OPTION_BITS   2
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_EN_IDX        8
#घोषणा _HRT_CSS_RECEIVER_2400_RAW16_EN_BITS       1

/* These hsync and vsync values are क्रम HSS simulation only */
#घोषणा _HRT_CSS_RECEIVER_2400_HSYNC_VAL BIT(16)
#घोषणा _HRT_CSS_RECEIVER_2400_VSYNC_VAL BIT(17)

#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_WIDTH                 28
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_A_LSB              0
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_A_MSB             (_HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_A_LSB + CSS_RECEIVER_DATA_OUT - 1)
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_A_VAL_BIT         (_HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_A_MSB + 1)
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_B_LSB             (_HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_A_VAL_BIT + 1)
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_B_MSB             (_HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_B_LSB + CSS_RECEIVER_DATA_OUT - 1)
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_B_VAL_BIT         (_HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_B_MSB + 1)
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_SOP_BIT               (_HRT_CSS_RECEIVER_2400_BE_STREAMING_PIX_B_VAL_BIT + 1)
#घोषणा _HRT_CSS_RECEIVER_2400_BE_STREAMING_EOP_BIT               (_HRT_CSS_RECEIVER_2400_BE_STREAMING_SOP_BIT + 1)

// SH Backend Register IDs
#घोषणा _HRT_CSS_RECEIVER_2400_BE_GSP_ACC_OVL_REG_IDX              0
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_REG_IDX                     1
#घोषणा _HRT_CSS_RECEIVER_2400_BE_TWO_PPC_REG_IDX                  2
#घोषणा _HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG0_IDX             3
#घोषणा _HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG1_IDX             4
#घोषणा _HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG2_IDX             5
#घोषणा _HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG3_IDX             6
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SEL_REG_IDX                      7
#घोषणा _HRT_CSS_RECEIVER_2400_BE_RAW16_CONFIG_REG_IDX             8
#घोषणा _HRT_CSS_RECEIVER_2400_BE_RAW18_CONFIG_REG_IDX             9
#घोषणा _HRT_CSS_RECEIVER_2400_BE_FORCE_RAW8_REG_IDX              10
#घोषणा _HRT_CSS_RECEIVER_2400_BE_IRQ_STATUS_REG_IDX              11
#घोषणा _HRT_CSS_RECEIVER_2400_BE_IRQ_CLEAR_REG_IDX               12
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_EN_REG_IDX                 13
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_DATA_STATE_REG_IDX         14    /* Data State 0,1,2 config */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S0P0_REG_IDX       15    /* Pixel Extractor config क्रम Data State 0 & Pix 0 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S0P1_REG_IDX       16    /* Pixel Extractor config क्रम Data State 0 & Pix 1 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S0P2_REG_IDX       17    /* Pixel Extractor config क्रम Data State 0 & Pix 2 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S0P3_REG_IDX       18    /* Pixel Extractor config क्रम Data State 0 & Pix 3 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S1P0_REG_IDX       19    /* Pixel Extractor config क्रम Data State 1 & Pix 0 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S1P1_REG_IDX       20    /* Pixel Extractor config क्रम Data State 1 & Pix 1 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S1P2_REG_IDX       21    /* Pixel Extractor config क्रम Data State 1 & Pix 2 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S1P3_REG_IDX       22    /* Pixel Extractor config क्रम Data State 1 & Pix 3 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S2P0_REG_IDX       23    /* Pixel Extractor config क्रम Data State 2 & Pix 0 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S2P1_REG_IDX       24    /* Pixel Extractor config क्रम Data State 2 & Pix 1 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S2P2_REG_IDX       25    /* Pixel Extractor config क्रम Data State 2 & Pix 2 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_EXT_S2P3_REG_IDX       26    /* Pixel Extractor config क्रम Data State 2 & Pix 3 */
#घोषणा _HRT_CSS_RECEIVER_2400_BE_CUST_PIX_VALID_EOP_REG_IDX      27    /* Pixel Valid & EoP config क्रम Pix 0,1,2,3 */

#घोषणा _HRT_CSS_RECEIVER_2400_BE_NOF_REGISTERS                   28

#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_HE                          0
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_RCF                         1
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_PF                          2
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_SM                          3
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_PD                          4
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_SD                          5
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_OT                          6
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_BC                          7
#घोषणा _HRT_CSS_RECEIVER_2400_BE_SRST_WIDTH                       8

#पूर्ण_अगर /* _css_receiver_2400_defs_h_ */
