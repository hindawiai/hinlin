<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt8192-reg.h  --  Mediatek 8192 audio driver reg definition
 *
 * Copyright (c) 2020 MediaTek Inc.
 * Author: Shane Chien <shane.chien@mediatek.com>
 */

#अगर_अघोषित _MT8192_REG_H_
#घोषणा _MT8192_REG_H_

/* reg bit क्रमागत */
क्रमागत अणु
	MT8192_MEMIF_PBUF_SIZE_32_BYTES,
	MT8192_MEMIF_PBUF_SIZE_64_BYTES,
	MT8192_MEMIF_PBUF_SIZE_128_BYTES,
	MT8192_MEMIF_PBUF_SIZE_256_BYTES,
	MT8192_MEMIF_PBUF_SIZE_NUM,
पूर्ण;

/*****************************************************************************
 *                  R E G I S T E R       D E F I N I T I O N
 *****************************************************************************/
/* AUDIO_TOP_CON3 */
#घोषणा BCK_INVERSE_SFT                              3
#घोषणा BCK_INVERSE_MASK                             0x1
#घोषणा BCK_INVERSE_MASK_SFT                         (0x1 << 3)

/* AFE_DAC_CON0 */
#घोषणा VUL12_ON_SFT                                   31
#घोषणा VUL12_ON_MASK                                  0x1
#घोषणा VUL12_ON_MASK_SFT                              (0x1 << 31)
#घोषणा MOD_DAI_ON_SFT                                 30
#घोषणा MOD_DAI_ON_MASK                                0x1
#घोषणा MOD_DAI_ON_MASK_SFT                            (0x1 << 30)
#घोषणा DAI_ON_SFT                                     29
#घोषणा DAI_ON_MASK                                    0x1
#घोषणा DAI_ON_MASK_SFT                                (0x1 << 29)
#घोषणा DAI2_ON_SFT                                    28
#घोषणा DAI2_ON_MASK                                   0x1
#घोषणा DAI2_ON_MASK_SFT                               (0x1 << 28)
#घोषणा VUL6_ON_SFT                                    23
#घोषणा VUL6_ON_MASK                                   0x1
#घोषणा VUL6_ON_MASK_SFT                               (0x1 << 23)
#घोषणा VUL5_ON_SFT                                    22
#घोषणा VUL5_ON_MASK                                   0x1
#घोषणा VUL5_ON_MASK_SFT                               (0x1 << 22)
#घोषणा VUL4_ON_SFT                                    21
#घोषणा VUL4_ON_MASK                                   0x1
#घोषणा VUL4_ON_MASK_SFT                               (0x1 << 21)
#घोषणा VUL3_ON_SFT                                    20
#घोषणा VUL3_ON_MASK                                   0x1
#घोषणा VUL3_ON_MASK_SFT                               (0x1 << 20)
#घोषणा VUL2_ON_SFT                                    19
#घोषणा VUL2_ON_MASK                                   0x1
#घोषणा VUL2_ON_MASK_SFT                               (0x1 << 19)
#घोषणा VUL_ON_SFT                                     18
#घोषणा VUL_ON_MASK                                    0x1
#घोषणा VUL_ON_MASK_SFT                                (0x1 << 18)
#घोषणा AWB2_ON_SFT                                    17
#घोषणा AWB2_ON_MASK                                   0x1
#घोषणा AWB2_ON_MASK_SFT                               (0x1 << 17)
#घोषणा AWB_ON_SFT                                     16
#घोषणा AWB_ON_MASK                                    0x1
#घोषणा AWB_ON_MASK_SFT                                (0x1 << 16)
#घोषणा DL12_ON_SFT                                    15
#घोषणा DL12_ON_MASK                                   0x1
#घोषणा DL12_ON_MASK_SFT                               (0x1 << 15)
#घोषणा DL9_ON_SFT                                     12
#घोषणा DL9_ON_MASK                                    0x1
#घोषणा DL9_ON_MASK_SFT                                (0x1 << 12)
#घोषणा DL8_ON_SFT                                     11
#घोषणा DL8_ON_MASK                                    0x1
#घोषणा DL8_ON_MASK_SFT                                (0x1 << 11)
#घोषणा DL7_ON_SFT                                     10
#घोषणा DL7_ON_MASK                                    0x1
#घोषणा DL7_ON_MASK_SFT                                (0x1 << 10)
#घोषणा DL6_ON_SFT                                     9
#घोषणा DL6_ON_MASK                                    0x1
#घोषणा DL6_ON_MASK_SFT                                (0x1 << 9)
#घोषणा DL5_ON_SFT                                     8
#घोषणा DL5_ON_MASK                                    0x1
#घोषणा DL5_ON_MASK_SFT                                (0x1 << 8)
#घोषणा DL4_ON_SFT                                     7
#घोषणा DL4_ON_MASK                                    0x1
#घोषणा DL4_ON_MASK_SFT                                (0x1 << 7)
#घोषणा DL3_ON_SFT                                     6
#घोषणा DL3_ON_MASK                                    0x1
#घोषणा DL3_ON_MASK_SFT                                (0x1 << 6)
#घोषणा DL2_ON_SFT                                     5
#घोषणा DL2_ON_MASK                                    0x1
#घोषणा DL2_ON_MASK_SFT                                (0x1 << 5)
#घोषणा DL1_ON_SFT                                     4
#घोषणा DL1_ON_MASK                                    0x1
#घोषणा DL1_ON_MASK_SFT                                (0x1 << 4)
#घोषणा HDMI_OUT_ON_SFT                                1
#घोषणा HDMI_OUT_ON_MASK                               0x1
#घोषणा HDMI_OUT_ON_MASK_SFT                           (0x1 << 1)
#घोषणा AFE_ON_SFT                                     0
#घोषणा AFE_ON_MASK                                    0x1
#घोषणा AFE_ON_MASK_SFT                                (0x1 << 0)

/* AFE_DAC_MON */
#घोषणा AFE_ON_RETM_SFT                                0
#घोषणा AFE_ON_RETM_MASK                               0x1
#घोषणा AFE_ON_RETM_MASK_SFT                           (0x1 << 0)

/* AFE_I2S_CON */
#घोषणा BCK_NEG_EG_LATCH_SFT                           30
#घोषणा BCK_NEG_EG_LATCH_MASK                          0x1
#घोषणा BCK_NEG_EG_LATCH_MASK_SFT                      (0x1 << 30)
#घोषणा BCK_INV_SFT                                    29
#घोषणा BCK_INV_MASK                                   0x1
#घोषणा BCK_INV_MASK_SFT                               (0x1 << 29)
#घोषणा I2SIN_PAD_SEL_SFT                              28
#घोषणा I2SIN_PAD_SEL_MASK                             0x1
#घोषणा I2SIN_PAD_SEL_MASK_SFT                         (0x1 << 28)
#घोषणा I2S_LOOPBACK_SFT                               20
#घोषणा I2S_LOOPBACK_MASK                              0x1
#घोषणा I2S_LOOPBACK_MASK_SFT                          (0x1 << 20)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S1_HD_EN_SFT                                 12
#घोषणा I2S1_HD_EN_MASK                                0x1
#घोषणा I2S1_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S_OUT_MODE_SFT                               8
#घोषणा I2S_OUT_MODE_MASK                              0xf
#घोषणा I2S_OUT_MODE_MASK_SFT                          (0xf << 8)
#घोषणा INV_PAD_CTRL_SFT                               7
#घोषणा INV_PAD_CTRL_MASK                              0x1
#घोषणा INV_PAD_CTRL_MASK_SFT                          (0x1 << 7)
#घोषणा I2S_BYPSRC_SFT                                 6
#घोषणा I2S_BYPSRC_MASK                                0x1
#घोषणा I2S_BYPSRC_MASK_SFT                            (0x1 << 6)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S_FMT_SFT                                    3
#घोषणा I2S_FMT_MASK                                   0x1
#घोषणा I2S_FMT_MASK_SFT                               (0x1 << 3)
#घोषणा I2S_SRC_SFT                                    2
#घोषणा I2S_SRC_MASK                                   0x1
#घोषणा I2S_SRC_MASK_SFT                               (0x1 << 2)
#घोषणा I2S_WLEN_SFT                                   1
#घोषणा I2S_WLEN_MASK                                  0x1
#घोषणा I2S_WLEN_MASK_SFT                              (0x1 << 1)
#घोषणा I2S_EN_SFT                                     0
#घोषणा I2S_EN_MASK                                    0x1
#घोषणा I2S_EN_MASK_SFT                                (0x1 << 0)

/* AFE_I2S_CON1 */
#घोषणा I2S2_LR_SWAP_SFT                               31
#घोषणा I2S2_LR_SWAP_MASK                              0x1
#घोषणा I2S2_LR_SWAP_MASK_SFT                          (0x1 << 31)
#घोषणा I2S2_SEL_O19_O20_SFT                           18
#घोषणा I2S2_SEL_O19_O20_MASK                          0x1
#घोषणा I2S2_SEL_O19_O20_MASK_SFT                      (0x1 << 18)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S2_SEL_O03_O04_SFT                           16
#घोषणा I2S2_SEL_O03_O04_MASK                          0x1
#घोषणा I2S2_SEL_O03_O04_MASK_SFT                      (0x1 << 16)
#घोषणा I2S2_32BIT_EN_SFT                              13
#घोषणा I2S2_32BIT_EN_MASK                             0x1
#घोषणा I2S2_32BIT_EN_MASK_SFT                         (0x1 << 13)
#घोषणा I2S2_HD_EN_SFT                                 12
#घोषणा I2S2_HD_EN_MASK                                0x1
#घोषणा I2S2_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S2_OUT_MODE_SFT                              8
#घोषणा I2S2_OUT_MODE_MASK                             0xf
#घोषणा I2S2_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S2_FMT_SFT                                   3
#घोषणा I2S2_FMT_MASK                                  0x1
#घोषणा I2S2_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S2_WLEN_SFT                                  1
#घोषणा I2S2_WLEN_MASK                                 0x1
#घोषणा I2S2_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S2_EN_SFT                                    0
#घोषणा I2S2_EN_MASK                                   0x1
#घोषणा I2S2_EN_MASK_SFT                               (0x1 << 0)

/* AFE_I2S_CON2 */
#घोषणा I2S3_LR_SWAP_SFT                               31
#घोषणा I2S3_LR_SWAP_MASK                              0x1
#घोषणा I2S3_LR_SWAP_MASK_SFT                          (0x1 << 31)
#घोषणा I2S3_UPDATE_WORD_SFT                           24
#घोषणा I2S3_UPDATE_WORD_MASK                          0x1f
#घोषणा I2S3_UPDATE_WORD_MASK_SFT                      (0x1f << 24)
#घोषणा I2S3_BCK_INV_SFT                               23
#घोषणा I2S3_BCK_INV_MASK                              0x1
#घोषणा I2S3_BCK_INV_MASK_SFT                          (0x1 << 23)
#घोषणा I2S3_FPGA_BIT_TEST_SFT                         22
#घोषणा I2S3_FPGA_BIT_TEST_MASK                        0x1
#घोषणा I2S3_FPGA_BIT_TEST_MASK_SFT                    (0x1 << 22)
#घोषणा I2S3_FPGA_BIT_SFT                              21
#घोषणा I2S3_FPGA_BIT_MASK                             0x1
#घोषणा I2S3_FPGA_BIT_MASK_SFT                         (0x1 << 21)
#घोषणा I2S3_LOOPBACK_SFT                              20
#घोषणा I2S3_LOOPBACK_MASK                             0x1
#घोषणा I2S3_LOOPBACK_MASK_SFT                         (0x1 << 20)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S3_HD_EN_SFT                                 12
#घोषणा I2S3_HD_EN_MASK                                0x1
#घोषणा I2S3_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S3_OUT_MODE_SFT                              8
#घोषणा I2S3_OUT_MODE_MASK                             0xf
#घोषणा I2S3_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा I2S3_FMT_SFT                                   3
#घोषणा I2S3_FMT_MASK                                  0x1
#घोषणा I2S3_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S3_WLEN_SFT                                  1
#घोषणा I2S3_WLEN_MASK                                 0x1
#घोषणा I2S3_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S3_EN_SFT                                    0
#घोषणा I2S3_EN_MASK                                   0x1
#घोषणा I2S3_EN_MASK_SFT                               (0x1 << 0)

/* AFE_I2S_CON3 */
#घोषणा I2S4_LR_SWAP_SFT                               31
#घोषणा I2S4_LR_SWAP_MASK                              0x1
#घोषणा I2S4_LR_SWAP_MASK_SFT                          (0x1 << 31)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S4_32BIT_EN_SFT                              13
#घोषणा I2S4_32BIT_EN_MASK                             0x1
#घोषणा I2S4_32BIT_EN_MASK_SFT                         (0x1 << 13)
#घोषणा I2S4_HD_EN_SFT                                 12
#घोषणा I2S4_HD_EN_MASK                                0x1
#घोषणा I2S4_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S4_OUT_MODE_SFT                              8
#घोषणा I2S4_OUT_MODE_MASK                             0xf
#घोषणा I2S4_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S4_FMT_SFT                                   3
#घोषणा I2S4_FMT_MASK                                  0x1
#घोषणा I2S4_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S4_WLEN_SFT                                  1
#घोषणा I2S4_WLEN_MASK                                 0x1
#घोषणा I2S4_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S4_EN_SFT                                    0
#घोषणा I2S4_EN_MASK                                   0x1
#घोषणा I2S4_EN_MASK_SFT                               (0x1 << 0)

/* AFE_I2S_CON4 */
#घोषणा I2S5_LR_SWAP_SFT                               31
#घोषणा I2S5_LR_SWAP_MASK                              0x1
#घोषणा I2S5_LR_SWAP_MASK_SFT                          (0x1 << 31)
#घोषणा I2S_LOOPBACK_SFT                               20
#घोषणा I2S_LOOPBACK_MASK                              0x1
#घोषणा I2S_LOOPBACK_MASK_SFT                          (0x1 << 20)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S5_32BIT_EN_SFT                              13
#घोषणा I2S5_32BIT_EN_MASK                             0x1
#घोषणा I2S5_32BIT_EN_MASK_SFT                         (0x1 << 13)
#घोषणा I2S5_HD_EN_SFT                                 12
#घोषणा I2S5_HD_EN_MASK                                0x1
#घोषणा I2S5_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S5_OUT_MODE_SFT                              8
#घोषणा I2S5_OUT_MODE_MASK                             0xf
#घोषणा I2S5_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S5_FMT_SFT                                   3
#घोषणा I2S5_FMT_MASK                                  0x1
#घोषणा I2S5_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S5_WLEN_SFT                                  1
#घोषणा I2S5_WLEN_MASK                                 0x1
#घोषणा I2S5_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S5_EN_SFT                                    0
#घोषणा I2S5_EN_MASK                                   0x1
#घोषणा I2S5_EN_MASK_SFT                               (0x1 << 0)

/* AFE_CONNSYS_I2S_CON */
#घोषणा BCK_NEG_EG_LATCH_SFT                           30
#घोषणा BCK_NEG_EG_LATCH_MASK                          0x1
#घोषणा BCK_NEG_EG_LATCH_MASK_SFT                      (0x1 << 30)
#घोषणा BCK_INV_SFT                                    29
#घोषणा BCK_INV_MASK                                   0x1
#घोषणा BCK_INV_MASK_SFT                               (0x1 << 29)
#घोषणा I2SIN_PAD_SEL_SFT                              28
#घोषणा I2SIN_PAD_SEL_MASK                             0x1
#घोषणा I2SIN_PAD_SEL_MASK_SFT                         (0x1 << 28)
#घोषणा I2S_LOOPBACK_SFT                               20
#घोषणा I2S_LOOPBACK_MASK                              0x1
#घोषणा I2S_LOOPBACK_MASK_SFT                          (0x1 << 20)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S_MODE_SFT                                   8
#घोषणा I2S_MODE_MASK                                  0xf
#घोषणा I2S_MODE_MASK_SFT                              (0xf << 8)
#घोषणा INV_PAD_CTRL_SFT                               7
#घोषणा INV_PAD_CTRL_MASK                              0x1
#घोषणा INV_PAD_CTRL_MASK_SFT                          (0x1 << 7)
#घोषणा I2S_BYPSRC_SFT                                 6
#घोषणा I2S_BYPSRC_MASK                                0x1
#घोषणा I2S_BYPSRC_MASK_SFT                            (0x1 << 6)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S_FMT_SFT                                    3
#घोषणा I2S_FMT_MASK                                   0x1
#घोषणा I2S_FMT_MASK_SFT                               (0x1 << 3)
#घोषणा I2S_SRC_SFT                                    2
#घोषणा I2S_SRC_MASK                                   0x1
#घोषणा I2S_SRC_MASK_SFT                               (0x1 << 2)
#घोषणा I2S_WLEN_SFT                                   1
#घोषणा I2S_WLEN_MASK                                  0x1
#घोषणा I2S_WLEN_MASK_SFT                              (0x1 << 1)
#घोषणा I2S_EN_SFT                                     0
#घोषणा I2S_EN_MASK                                    0x1
#घोषणा I2S_EN_MASK_SFT                                (0x1 << 0)

/* AFE_I2S_CON6 */
#घोषणा BCK_NEG_EG_LATCH_SFT                           30
#घोषणा BCK_NEG_EG_LATCH_MASK                          0x1
#घोषणा BCK_NEG_EG_LATCH_MASK_SFT                      (0x1 << 30)
#घोषणा BCK_INV_SFT                                    29
#घोषणा BCK_INV_MASK                                   0x1
#घोषणा BCK_INV_MASK_SFT                               (0x1 << 29)
#घोषणा I2S6_LOOPBACK_SFT                              20
#घोषणा I2S6_LOOPBACK_MASK                             0x1
#घोषणा I2S6_LOOPBACK_MASK_SFT                         (0x1 << 20)
#घोषणा I2S6_ONOFF_NOT_RESET_CK_ENABLE_SFT             17
#घोषणा I2S6_ONOFF_NOT_RESET_CK_ENABLE_MASK            0x1
#घोषणा I2S6_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT        (0x1 << 17)
#घोषणा I2S6_HD_EN_SFT                                 12
#घोषणा I2S6_HD_EN_MASK                                0x1
#घोषणा I2S6_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S6_OUT_MODE_SFT                              8
#घोषणा I2S6_OUT_MODE_MASK                             0xf
#घोषणा I2S6_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा I2S6_BYPSRC_SFT                                6
#घोषणा I2S6_BYPSRC_MASK                               0x1
#घोषणा I2S6_BYPSRC_MASK_SFT                           (0x1 << 6)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S6_FMT_SFT                                   3
#घोषणा I2S6_FMT_MASK                                  0x1
#घोषणा I2S6_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S6_SRC_SFT                                   2
#घोषणा I2S6_SRC_MASK                                  0x1
#घोषणा I2S6_SRC_MASK_SFT                              (0x1 << 2)
#घोषणा I2S6_WLEN_SFT                                  1
#घोषणा I2S6_WLEN_MASK                                 0x1
#घोषणा I2S6_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S6_EN_SFT                                    0
#घोषणा I2S6_EN_MASK                                   0x1
#घोषणा I2S6_EN_MASK_SFT                               (0x1 << 0)

/* AFE_I2S_CON7 */
#घोषणा I2S7_LR_SWAP_SFT                               31
#घोषणा I2S7_LR_SWAP_MASK                              0x1
#घोषणा I2S7_LR_SWAP_MASK_SFT                          (0x1 << 31)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S7_32BIT_EN_SFT                              13
#घोषणा I2S7_32BIT_EN_MASK                             0x1
#घोषणा I2S7_32BIT_EN_MASK_SFT                         (0x1 << 13)
#घोषणा I2S7_HD_EN_SFT                                 12
#घोषणा I2S7_HD_EN_MASK                                0x1
#घोषणा I2S7_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S7_OUT_MODE_SFT                              8
#घोषणा I2S7_OUT_MODE_MASK                             0xf
#घोषणा I2S7_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S7_FMT_SFT                                   3
#घोषणा I2S7_FMT_MASK                                  0x1
#घोषणा I2S7_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S7_WLEN_SFT                                  1
#घोषणा I2S7_WLEN_MASK                                 0x1
#घोषणा I2S7_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S7_EN_SFT                                    0
#घोषणा I2S7_EN_MASK                                   0x1
#घोषणा I2S7_EN_MASK_SFT                               (0x1 << 0)

/* AFE_I2S_CON8 */
#घोषणा BCK_NEG_EG_LATCH_SFT                           30
#घोषणा BCK_NEG_EG_LATCH_MASK                          0x1
#घोषणा BCK_NEG_EG_LATCH_MASK_SFT                      (0x1 << 30)
#घोषणा BCK_INV_SFT                                    29
#घोषणा BCK_INV_MASK                                   0x1
#घोषणा BCK_INV_MASK_SFT                               (0x1 << 29)
#घोषणा I2S8_LOOPBACK_SFT                              20
#घोषणा I2S8_LOOPBACK_MASK                             0x1
#घोषणा I2S8_LOOPBACK_MASK_SFT                         (0x1 << 20)
#घोषणा I2S8_ONOFF_NOT_RESET_CK_ENABLE_SFT             17
#घोषणा I2S8_ONOFF_NOT_RESET_CK_ENABLE_MASK            0x1
#घोषणा I2S8_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT        (0x1 << 17)
#घोषणा I2S8_HD_EN_SFT                                 12
#घोषणा I2S8_HD_EN_MASK                                0x1
#घोषणा I2S8_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S8_OUT_MODE_SFT                              8
#घोषणा I2S8_OUT_MODE_MASK                             0xf
#घोषणा I2S8_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा I2S8_BYPSRC_SFT                                6
#घोषणा I2S8_BYPSRC_MASK                               0x1
#घोषणा I2S8_BYPSRC_MASK_SFT                           (0x1 << 6)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S8_FMT_SFT                                   3
#घोषणा I2S8_FMT_MASK                                  0x1
#घोषणा I2S8_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S8_SRC_SFT                                   2
#घोषणा I2S8_SRC_MASK                                  0x1
#घोषणा I2S8_SRC_MASK_SFT                              (0x1 << 2)
#घोषणा I2S8_WLEN_SFT                                  1
#घोषणा I2S8_WLEN_MASK                                 0x1
#घोषणा I2S8_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S8_EN_SFT                                    0
#घोषणा I2S8_EN_MASK                                   0x1
#घोषणा I2S8_EN_MASK_SFT                               (0x1 << 0)

/* AFE_I2S_CON9 */
#घोषणा I2S9_LR_SWAP_SFT                               31
#घोषणा I2S9_LR_SWAP_MASK                              0x1
#घोषणा I2S9_LR_SWAP_MASK_SFT                          (0x1 << 31)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT              17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK             0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT         (0x1 << 17)
#घोषणा I2S9_32BIT_EN_SFT                              13
#घोषणा I2S9_32BIT_EN_MASK                             0x1
#घोषणा I2S9_32BIT_EN_MASK_SFT                         (0x1 << 13)
#घोषणा I2S9_HD_EN_SFT                                 12
#घोषणा I2S9_HD_EN_MASK                                0x1
#घोषणा I2S9_HD_EN_MASK_SFT                            (0x1 << 12)
#घोषणा I2S9_OUT_MODE_SFT                              8
#घोषणा I2S9_OUT_MODE_MASK                             0xf
#घोषणा I2S9_OUT_MODE_MASK_SFT                         (0xf << 8)
#घोषणा INV_LRCK_SFT                                   5
#घोषणा INV_LRCK_MASK                                  0x1
#घोषणा INV_LRCK_MASK_SFT                              (0x1 << 5)
#घोषणा I2S9_FMT_SFT                                   3
#घोषणा I2S9_FMT_MASK                                  0x1
#घोषणा I2S9_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S9_WLEN_SFT                                  1
#घोषणा I2S9_WLEN_MASK                                 0x1
#घोषणा I2S9_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S9_EN_SFT                                    0
#घोषणा I2S9_EN_MASK                                   0x1
#घोषणा I2S9_EN_MASK_SFT                               (0x1 << 0)

/* AFE_ASRC_2CH_CON2 */
#घोषणा CHSET_O16BIT_SFT                               19
#घोषणा CHSET_O16BIT_MASK                              0x1
#घोषणा CHSET_O16BIT_MASK_SFT                          (0x1 << 19)
#घोषणा CHSET_CLR_IIR_HISTORY_SFT                      17
#घोषणा CHSET_CLR_IIR_HISTORY_MASK                     0x1
#घोषणा CHSET_CLR_IIR_HISTORY_MASK_SFT                 (0x1 << 17)
#घोषणा CHSET_IS_MONO_SFT                              16
#घोषणा CHSET_IS_MONO_MASK                             0x1
#घोषणा CHSET_IS_MONO_MASK_SFT                         (0x1 << 16)
#घोषणा CHSET_IIR_EN_SFT                               11
#घोषणा CHSET_IIR_EN_MASK                              0x1
#घोषणा CHSET_IIR_EN_MASK_SFT                          (0x1 << 11)
#घोषणा CHSET_IIR_STAGE_SFT                            8
#घोषणा CHSET_IIR_STAGE_MASK                           0x7
#घोषणा CHSET_IIR_STAGE_MASK_SFT                       (0x7 << 8)
#घोषणा CHSET_STR_CLR_SFT                              5
#घोषणा CHSET_STR_CLR_MASK                             0x1
#घोषणा CHSET_STR_CLR_MASK_SFT                         (0x1 << 5)
#घोषणा CHSET_ON_SFT                                   2
#घोषणा CHSET_ON_MASK                                  0x1
#घोषणा CHSET_ON_MASK_SFT                              (0x1 << 2)
#घोषणा COEFF_SRAM_CTRL_SFT                            1
#घोषणा COEFF_SRAM_CTRL_MASK                           0x1
#घोषणा COEFF_SRAM_CTRL_MASK_SFT                       (0x1 << 1)
#घोषणा ASM_ON_SFT                                     0
#घोषणा ASM_ON_MASK                                    0x1
#घोषणा ASM_ON_MASK_SFT                                (0x1 << 0)

/* AFE_GAIN1_CON0 */
#घोषणा GAIN1_SAMPLE_PER_STEP_SFT                      8
#घोषणा GAIN1_SAMPLE_PER_STEP_MASK                     0xff
#घोषणा GAIN1_SAMPLE_PER_STEP_MASK_SFT                 (0xff << 8)
#घोषणा GAIN1_MODE_SFT                                 4
#घोषणा GAIN1_MODE_MASK                                0xf
#घोषणा GAIN1_MODE_MASK_SFT                            (0xf << 4)
#घोषणा GAIN1_ON_SFT                                   0
#घोषणा GAIN1_ON_MASK                                  0x1
#घोषणा GAIN1_ON_MASK_SFT                              (0x1 << 0)

/* AFE_GAIN1_CON1 */
#घोषणा GAIN1_TARGET_SFT                               0
#घोषणा GAIN1_TARGET_MASK                              0xfffffff
#घोषणा GAIN1_TARGET_MASK_SFT                          (0xfffffff << 0)

/* AFE_GAIN2_CON0 */
#घोषणा GAIN2_SAMPLE_PER_STEP_SFT                      8
#घोषणा GAIN2_SAMPLE_PER_STEP_MASK                     0xff
#घोषणा GAIN2_SAMPLE_PER_STEP_MASK_SFT                 (0xff << 8)
#घोषणा GAIN2_MODE_SFT                                 4
#घोषणा GAIN2_MODE_MASK                                0xf
#घोषणा GAIN2_MODE_MASK_SFT                            (0xf << 4)
#घोषणा GAIN2_ON_SFT                                   0
#घोषणा GAIN2_ON_MASK                                  0x1
#घोषणा GAIN2_ON_MASK_SFT                              (0x1 << 0)

/* AFE_GAIN2_CON1 */
#घोषणा GAIN2_TARGET_SFT                               0
#घोषणा GAIN2_TARGET_MASK                              0xfffffff
#घोषणा GAIN2_TARGET_MASK_SFT                          (0xfffffff << 0)

/* AFE_GAIN1_CUR */
#घोषणा AFE_GAIN1_CUR_SFT                              0
#घोषणा AFE_GAIN1_CUR_MASK                             0xfffffff
#घोषणा AFE_GAIN1_CUR_MASK_SFT                         (0xfffffff << 0)

/* AFE_GAIN2_CUR */
#घोषणा AFE_GAIN2_CUR_SFT                              0
#घोषणा AFE_GAIN2_CUR_MASK                             0xfffffff
#घोषणा AFE_GAIN2_CUR_MASK_SFT                         (0xfffffff << 0)

/* PCM_INTF_CON1 */
#घोषणा PCM_FIX_VALUE_SEL_SFT                          31
#घोषणा PCM_FIX_VALUE_SEL_MASK                         0x1
#घोषणा PCM_FIX_VALUE_SEL_MASK_SFT                     (0x1 << 31)
#घोषणा PCM_BUFFER_LOOPBACK_SFT                        30
#घोषणा PCM_BUFFER_LOOPBACK_MASK                       0x1
#घोषणा PCM_BUFFER_LOOPBACK_MASK_SFT                   (0x1 << 30)
#घोषणा PCM_PARALLEL_LOOPBACK_SFT                      29
#घोषणा PCM_PARALLEL_LOOPBACK_MASK                     0x1
#घोषणा PCM_PARALLEL_LOOPBACK_MASK_SFT                 (0x1 << 29)
#घोषणा PCM_SERIAL_LOOPBACK_SFT                        28
#घोषणा PCM_SERIAL_LOOPBACK_MASK                       0x1
#घोषणा PCM_SERIAL_LOOPBACK_MASK_SFT                   (0x1 << 28)
#घोषणा PCM_DAI_PCM_LOOPBACK_SFT                       27
#घोषणा PCM_DAI_PCM_LOOPBACK_MASK                      0x1
#घोषणा PCM_DAI_PCM_LOOPBACK_MASK_SFT                  (0x1 << 27)
#घोषणा PCM_I2S_PCM_LOOPBACK_SFT                       26
#घोषणा PCM_I2S_PCM_LOOPBACK_MASK                      0x1
#घोषणा PCM_I2S_PCM_LOOPBACK_MASK_SFT                  (0x1 << 26)
#घोषणा PCM_SYNC_DELSEL_SFT                            25
#घोषणा PCM_SYNC_DELSEL_MASK                           0x1
#घोषणा PCM_SYNC_DELSEL_MASK_SFT                       (0x1 << 25)
#घोषणा PCM_TX_LR_SWAP_SFT                             24
#घोषणा PCM_TX_LR_SWAP_MASK                            0x1
#घोषणा PCM_TX_LR_SWAP_MASK_SFT                        (0x1 << 24)
#घोषणा PCM_SYNC_OUT_INV_SFT                           23
#घोषणा PCM_SYNC_OUT_INV_MASK                          0x1
#घोषणा PCM_SYNC_OUT_INV_MASK_SFT                      (0x1 << 23)
#घोषणा PCM_BCLK_OUT_INV_SFT                           22
#घोषणा PCM_BCLK_OUT_INV_MASK                          0x1
#घोषणा PCM_BCLK_OUT_INV_MASK_SFT                      (0x1 << 22)
#घोषणा PCM_SYNC_IN_INV_SFT                            21
#घोषणा PCM_SYNC_IN_INV_MASK                           0x1
#घोषणा PCM_SYNC_IN_INV_MASK_SFT                       (0x1 << 21)
#घोषणा PCM_BCLK_IN_INV_SFT                            20
#घोषणा PCM_BCLK_IN_INV_MASK                           0x1
#घोषणा PCM_BCLK_IN_INV_MASK_SFT                       (0x1 << 20)
#घोषणा PCM_TX_LCH_RPT_SFT                             19
#घोषणा PCM_TX_LCH_RPT_MASK                            0x1
#घोषणा PCM_TX_LCH_RPT_MASK_SFT                        (0x1 << 19)
#घोषणा PCM_VBT_16K_MODE_SFT                           18
#घोषणा PCM_VBT_16K_MODE_MASK                          0x1
#घोषणा PCM_VBT_16K_MODE_MASK_SFT                      (0x1 << 18)
#घोषणा PCM_EXT_MODEM_SFT                              17
#घोषणा PCM_EXT_MODEM_MASK                             0x1
#घोषणा PCM_EXT_MODEM_MASK_SFT                         (0x1 << 17)
#घोषणा PCM_24BIT_SFT                                  16
#घोषणा PCM_24BIT_MASK                                 0x1
#घोषणा PCM_24BIT_MASK_SFT                             (0x1 << 16)
#घोषणा PCM_WLEN_SFT                                   14
#घोषणा PCM_WLEN_MASK                                  0x3
#घोषणा PCM_WLEN_MASK_SFT                              (0x3 << 14)
#घोषणा PCM_SYNC_LENGTH_SFT                            9
#घोषणा PCM_SYNC_LENGTH_MASK                           0x1f
#घोषणा PCM_SYNC_LENGTH_MASK_SFT                       (0x1f << 9)
#घोषणा PCM_SYNC_TYPE_SFT                              8
#घोषणा PCM_SYNC_TYPE_MASK                             0x1
#घोषणा PCM_SYNC_TYPE_MASK_SFT                         (0x1 << 8)
#घोषणा PCM_BT_MODE_SFT                                7
#घोषणा PCM_BT_MODE_MASK                               0x1
#घोषणा PCM_BT_MODE_MASK_SFT                           (0x1 << 7)
#घोषणा PCM_BYP_ASRC_SFT                               6
#घोषणा PCM_BYP_ASRC_MASK                              0x1
#घोषणा PCM_BYP_ASRC_MASK_SFT                          (0x1 << 6)
#घोषणा PCM_SLAVE_SFT                                  5
#घोषणा PCM_SLAVE_MASK                                 0x1
#घोषणा PCM_SLAVE_MASK_SFT                             (0x1 << 5)
#घोषणा PCM_MODE_SFT                                   3
#घोषणा PCM_MODE_MASK                                  0x3
#घोषणा PCM_MODE_MASK_SFT                              (0x3 << 3)
#घोषणा PCM_FMT_SFT                                    1
#घोषणा PCM_FMT_MASK                                   0x3
#घोषणा PCM_FMT_MASK_SFT                               (0x3 << 1)
#घोषणा PCM_EN_SFT                                     0
#घोषणा PCM_EN_MASK                                    0x1
#घोषणा PCM_EN_MASK_SFT                                (0x1 << 0)

/* PCM_INTF_CON2 */
#घोषणा PCM1_TX_FIFO_OV_SFT                            31
#घोषणा PCM1_TX_FIFO_OV_MASK                           0x1
#घोषणा PCM1_TX_FIFO_OV_MASK_SFT                       (0x1 << 31)
#घोषणा PCM1_RX_FIFO_OV_SFT                            30
#घोषणा PCM1_RX_FIFO_OV_MASK                           0x1
#घोषणा PCM1_RX_FIFO_OV_MASK_SFT                       (0x1 << 30)
#घोषणा PCM2_TX_FIFO_OV_SFT                            29
#घोषणा PCM2_TX_FIFO_OV_MASK                           0x1
#घोषणा PCM2_TX_FIFO_OV_MASK_SFT                       (0x1 << 29)
#घोषणा PCM2_RX_FIFO_OV_SFT                            28
#घोषणा PCM2_RX_FIFO_OV_MASK                           0x1
#घोषणा PCM2_RX_FIFO_OV_MASK_SFT                       (0x1 << 28)
#घोषणा PCM1_SYNC_GLITCH_SFT                           27
#घोषणा PCM1_SYNC_GLITCH_MASK                          0x1
#घोषणा PCM1_SYNC_GLITCH_MASK_SFT                      (0x1 << 27)
#घोषणा PCM2_SYNC_GLITCH_SFT                           26
#घोषणा PCM2_SYNC_GLITCH_MASK                          0x1
#घोषणा PCM2_SYNC_GLITCH_MASK_SFT                      (0x1 << 26)
#घोषणा TX3_RCH_DBG_MODE_SFT                           17
#घोषणा TX3_RCH_DBG_MODE_MASK                          0x1
#घोषणा TX3_RCH_DBG_MODE_MASK_SFT                      (0x1 << 17)
#घोषणा PCM1_PCM2_LOOPBACK_SFT                         16
#घोषणा PCM1_PCM2_LOOPBACK_MASK                        0x1
#घोषणा PCM1_PCM2_LOOPBACK_MASK_SFT                    (0x1 << 16)
#घोषणा DAI_PCM_LOOPBACK_CH_SFT                        14
#घोषणा DAI_PCM_LOOPBACK_CH_MASK                       0x3
#घोषणा DAI_PCM_LOOPBACK_CH_MASK_SFT                   (0x3 << 14)
#घोषणा I2S_PCM_LOOPBACK_CH_SFT                        12
#घोषणा I2S_PCM_LOOPBACK_CH_MASK                       0x3
#घोषणा I2S_PCM_LOOPBACK_CH_MASK_SFT                   (0x3 << 12)
#घोषणा TX_FIX_VALUE_SFT                               0
#घोषणा TX_FIX_VALUE_MASK                              0xff
#घोषणा TX_FIX_VALUE_MASK_SFT                          (0xff << 0)

/* PCM2_INTF_CON */
#घोषणा PCM2_TX_FIX_VALUE_SFT                          24
#घोषणा PCM2_TX_FIX_VALUE_MASK                         0xff
#घोषणा PCM2_TX_FIX_VALUE_MASK_SFT                     (0xff << 24)
#घोषणा PCM2_FIX_VALUE_SEL_SFT                         23
#घोषणा PCM2_FIX_VALUE_SEL_MASK                        0x1
#घोषणा PCM2_FIX_VALUE_SEL_MASK_SFT                    (0x1 << 23)
#घोषणा PCM2_BUFFER_LOOPBACK_SFT                       22
#घोषणा PCM2_BUFFER_LOOPBACK_MASK                      0x1
#घोषणा PCM2_BUFFER_LOOPBACK_MASK_SFT                  (0x1 << 22)
#घोषणा PCM2_PARALLEL_LOOPBACK_SFT                     21
#घोषणा PCM2_PARALLEL_LOOPBACK_MASK                    0x1
#घोषणा PCM2_PARALLEL_LOOPBACK_MASK_SFT                (0x1 << 21)
#घोषणा PCM2_SERIAL_LOOPBACK_SFT                       20
#घोषणा PCM2_SERIAL_LOOPBACK_MASK                      0x1
#घोषणा PCM2_SERIAL_LOOPBACK_MASK_SFT                  (0x1 << 20)
#घोषणा PCM2_DAI_PCM_LOOPBACK_SFT                      19
#घोषणा PCM2_DAI_PCM_LOOPBACK_MASK                     0x1
#घोषणा PCM2_DAI_PCM_LOOPBACK_MASK_SFT                 (0x1 << 19)
#घोषणा PCM2_I2S_PCM_LOOPBACK_SFT                      18
#घोषणा PCM2_I2S_PCM_LOOPBACK_MASK                     0x1
#घोषणा PCM2_I2S_PCM_LOOPBACK_MASK_SFT                 (0x1 << 18)
#घोषणा PCM2_SYNC_DELSEL_SFT                           17
#घोषणा PCM2_SYNC_DELSEL_MASK                          0x1
#घोषणा PCM2_SYNC_DELSEL_MASK_SFT                      (0x1 << 17)
#घोषणा PCM2_TX_LR_SWAP_SFT                            16
#घोषणा PCM2_TX_LR_SWAP_MASK                           0x1
#घोषणा PCM2_TX_LR_SWAP_MASK_SFT                       (0x1 << 16)
#घोषणा PCM2_SYNC_IN_INV_SFT                           15
#घोषणा PCM2_SYNC_IN_INV_MASK                          0x1
#घोषणा PCM2_SYNC_IN_INV_MASK_SFT                      (0x1 << 15)
#घोषणा PCM2_BCLK_IN_INV_SFT                           14
#घोषणा PCM2_BCLK_IN_INV_MASK                          0x1
#घोषणा PCM2_BCLK_IN_INV_MASK_SFT                      (0x1 << 14)
#घोषणा PCM2_TX_LCH_RPT_SFT                            13
#घोषणा PCM2_TX_LCH_RPT_MASK                           0x1
#घोषणा PCM2_TX_LCH_RPT_MASK_SFT                       (0x1 << 13)
#घोषणा PCM2_VBT_16K_MODE_SFT                          12
#घोषणा PCM2_VBT_16K_MODE_MASK                         0x1
#घोषणा PCM2_VBT_16K_MODE_MASK_SFT                     (0x1 << 12)
#घोषणा PCM2_LOOPBACK_CH_SEL_SFT                       10
#घोषणा PCM2_LOOPBACK_CH_SEL_MASK                      0x3
#घोषणा PCM2_LOOPBACK_CH_SEL_MASK_SFT                  (0x3 << 10)
#घोषणा PCM2_TX2_BT_MODE_SFT                           8
#घोषणा PCM2_TX2_BT_MODE_MASK                          0x1
#घोषणा PCM2_TX2_BT_MODE_MASK_SFT                      (0x1 << 8)
#घोषणा PCM2_BT_MODE_SFT                               7
#घोषणा PCM2_BT_MODE_MASK                              0x1
#घोषणा PCM2_BT_MODE_MASK_SFT                          (0x1 << 7)
#घोषणा PCM2_AFIFO_SFT                                 6
#घोषणा PCM2_AFIFO_MASK                                0x1
#घोषणा PCM2_AFIFO_MASK_SFT                            (0x1 << 6)
#घोषणा PCM2_WLEN_SFT                                  5
#घोषणा PCM2_WLEN_MASK                                 0x1
#घोषणा PCM2_WLEN_MASK_SFT                             (0x1 << 5)
#घोषणा PCM2_MODE_SFT                                  3
#घोषणा PCM2_MODE_MASK                                 0x3
#घोषणा PCM2_MODE_MASK_SFT                             (0x3 << 3)
#घोषणा PCM2_FMT_SFT                                   1
#घोषणा PCM2_FMT_MASK                                  0x3
#घोषणा PCM2_FMT_MASK_SFT                              (0x3 << 1)
#घोषणा PCM2_EN_SFT                                    0
#घोषणा PCM2_EN_MASK                                   0x1
#घोषणा PCM2_EN_MASK_SFT                               (0x1 << 0)

/* AFE_ADDA_MTKAIF_CFG0 */
#घोषणा MTKAIF_RXIF_CLKINV_ADC_SFT                     31
#घोषणा MTKAIF_RXIF_CLKINV_ADC_MASK                    0x1
#घोषणा MTKAIF_RXIF_CLKINV_ADC_MASK_SFT                (0x1 << 31)
#घोषणा MTKAIF_RXIF_BYPASS_SRC_SFT                     17
#घोषणा MTKAIF_RXIF_BYPASS_SRC_MASK                    0x1
#घोषणा MTKAIF_RXIF_BYPASS_SRC_MASK_SFT                (0x1 << 17)
#घोषणा MTKAIF_RXIF_PROTOCOL2_SFT                      16
#घोषणा MTKAIF_RXIF_PROTOCOL2_MASK                     0x1
#घोषणा MTKAIF_RXIF_PROTOCOL2_MASK_SFT                 (0x1 << 16)
#घोषणा MTKAIF_TXIF_BYPASS_SRC_SFT                     5
#घोषणा MTKAIF_TXIF_BYPASS_SRC_MASK                    0x1
#घोषणा MTKAIF_TXIF_BYPASS_SRC_MASK_SFT                (0x1 << 5)
#घोषणा MTKAIF_TXIF_PROTOCOL2_SFT                      4
#घोषणा MTKAIF_TXIF_PROTOCOL2_MASK                     0x1
#घोषणा MTKAIF_TXIF_PROTOCOL2_MASK_SFT                 (0x1 << 4)
#घोषणा MTKAIF_TXIF_8TO5_SFT                           2
#घोषणा MTKAIF_TXIF_8TO5_MASK                          0x1
#घोषणा MTKAIF_TXIF_8TO5_MASK_SFT                      (0x1 << 2)
#घोषणा MTKAIF_RXIF_8TO5_SFT                           1
#घोषणा MTKAIF_RXIF_8TO5_MASK                          0x1
#घोषणा MTKAIF_RXIF_8TO5_MASK_SFT                      (0x1 << 1)
#घोषणा MTKAIF_IF_LOOPBACK1_SFT                        0
#घोषणा MTKAIF_IF_LOOPBACK1_MASK                       0x1
#घोषणा MTKAIF_IF_LOOPBACK1_MASK_SFT                   (0x1 << 0)

/* AFE_ADDA_MTKAIF_RX_CFG2 */
#घोषणा MTKAIF_RXIF_DETECT_ON_PROTOCOL2_SFT            16
#घोषणा MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK           0x1
#घोषणा MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK_SFT       (0x1 << 16)
#घोषणा MTKAIF_RXIF_DELAY_CYCLE_SFT                    12
#घोषणा MTKAIF_RXIF_DELAY_CYCLE_MASK                   0xf
#घोषणा MTKAIF_RXIF_DELAY_CYCLE_MASK_SFT               (0xf << 12)
#घोषणा MTKAIF_RXIF_DELAY_DATA_SFT                     8
#घोषणा MTKAIF_RXIF_DELAY_DATA_MASK                    0x1
#घोषणा MTKAIF_RXIF_DELAY_DATA_MASK_SFT                (0x1 << 8)
#घोषणा MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_SFT             4
#घोषणा MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK            0x7
#घोषणा MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK_SFT        (0x7 << 4)

/* AFE_ADDA_DL_SRC2_CON0 */
#घोषणा DL_2_INPUT_MODE_CTL_SFT                        28
#घोषणा DL_2_INPUT_MODE_CTL_MASK                       0xf
#घोषणा DL_2_INPUT_MODE_CTL_MASK_SFT                   (0xf << 28)
#घोषणा DL_2_CH1_SATURATION_EN_CTL_SFT                 27
#घोषणा DL_2_CH1_SATURATION_EN_CTL_MASK                0x1
#घोषणा DL_2_CH1_SATURATION_EN_CTL_MASK_SFT            (0x1 << 27)
#घोषणा DL_2_CH2_SATURATION_EN_CTL_SFT                 26
#घोषणा DL_2_CH2_SATURATION_EN_CTL_MASK                0x1
#घोषणा DL_2_CH2_SATURATION_EN_CTL_MASK_SFT            (0x1 << 26)
#घोषणा DL_2_OUTPUT_SEL_CTL_SFT                        24
#घोषणा DL_2_OUTPUT_SEL_CTL_MASK                       0x3
#घोषणा DL_2_OUTPUT_SEL_CTL_MASK_SFT                   (0x3 << 24)
#घोषणा DL_2_FADEIN_0START_EN_SFT                      16
#घोषणा DL_2_FADEIN_0START_EN_MASK                     0x3
#घोषणा DL_2_FADEIN_0START_EN_MASK_SFT                 (0x3 << 16)
#घोषणा DL_DISABLE_HW_CG_CTL_SFT                       15
#घोषणा DL_DISABLE_HW_CG_CTL_MASK                      0x1
#घोषणा DL_DISABLE_HW_CG_CTL_MASK_SFT                  (0x1 << 15)
#घोषणा C_DATA_EN_SEL_CTL_PRE_SFT                      14
#घोषणा C_DATA_EN_SEL_CTL_PRE_MASK                     0x1
#घोषणा C_DATA_EN_SEL_CTL_PRE_MASK_SFT                 (0x1 << 14)
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_SFT                  13
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_MASK                 0x1
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_MASK_SFT             (0x1 << 13)
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_SFT                  12
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_MASK                 0x1
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_MASK_SFT             (0x1 << 12)
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_SFT                  11
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_MASK                 0x1
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_MASK_SFT             (0x1 << 11)
#घोषणा DL2_ARAMPSP_CTL_PRE_SFT                        9
#घोषणा DL2_ARAMPSP_CTL_PRE_MASK                       0x3
#घोषणा DL2_ARAMPSP_CTL_PRE_MASK_SFT                   (0x3 << 9)
#घोषणा DL_2_IIRMODE_CTL_PRE_SFT                       6
#घोषणा DL_2_IIRMODE_CTL_PRE_MASK                      0x7
#घोषणा DL_2_IIRMODE_CTL_PRE_MASK_SFT                  (0x7 << 6)
#घोषणा DL_2_VOICE_MODE_CTL_PRE_SFT                    5
#घोषणा DL_2_VOICE_MODE_CTL_PRE_MASK                   0x1
#घोषणा DL_2_VOICE_MODE_CTL_PRE_MASK_SFT               (0x1 << 5)
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_SFT                   4
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_MASK                  0x1
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_MASK_SFT              (0x1 << 4)
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_SFT                   3
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_MASK                  0x1
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_MASK_SFT              (0x1 << 3)
#घोषणा DL_2_IIR_ON_CTL_PRE_SFT                        2
#घोषणा DL_2_IIR_ON_CTL_PRE_MASK                       0x1
#घोषणा DL_2_IIR_ON_CTL_PRE_MASK_SFT                   (0x1 << 2)
#घोषणा DL_2_GAIN_ON_CTL_PRE_SFT                       1
#घोषणा DL_2_GAIN_ON_CTL_PRE_MASK                      0x1
#घोषणा DL_2_GAIN_ON_CTL_PRE_MASK_SFT                  (0x1 << 1)
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_SFT                    0
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK                   0x1
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK_SFT               (0x1 << 0)

/* AFE_ADDA_DL_SRC2_CON1 */
#घोषणा DL_2_GAIN_CTL_PRE_SFT                          16
#घोषणा DL_2_GAIN_CTL_PRE_MASK                         0xffff
#घोषणा DL_2_GAIN_CTL_PRE_MASK_SFT                     (0xffff << 16)
#घोषणा DL_2_GAIN_MODE_CTL_SFT                         0
#घोषणा DL_2_GAIN_MODE_CTL_MASK                        0x1
#घोषणा DL_2_GAIN_MODE_CTL_MASK_SFT                    (0x1 << 0)

/* AFE_ADDA_UL_SRC_CON0 */
#घोषणा ULCF_CFG_EN_CTL_SFT                            31
#घोषणा ULCF_CFG_EN_CTL_MASK                           0x1
#घोषणा ULCF_CFG_EN_CTL_MASK_SFT                       (0x1 << 31)
#घोषणा UL_DMIC_PHASE_SEL_CH1_SFT                      27
#घोषणा UL_DMIC_PHASE_SEL_CH1_MASK                     0x7
#घोषणा UL_DMIC_PHASE_SEL_CH1_MASK_SFT                 (0x7 << 27)
#घोषणा UL_DMIC_PHASE_SEL_CH2_SFT                      24
#घोषणा UL_DMIC_PHASE_SEL_CH2_MASK                     0x7
#घोषणा UL_DMIC_PHASE_SEL_CH2_MASK_SFT                 (0x7 << 24)
#घोषणा UL_MODE_3P25M_CH2_CTL_SFT                      22
#घोषणा UL_MODE_3P25M_CH2_CTL_MASK                     0x1
#घोषणा UL_MODE_3P25M_CH2_CTL_MASK_SFT                 (0x1 << 22)
#घोषणा UL_MODE_3P25M_CH1_CTL_SFT                      21
#घोषणा UL_MODE_3P25M_CH1_CTL_MASK                     0x1
#घोषणा UL_MODE_3P25M_CH1_CTL_MASK_SFT                 (0x1 << 21)
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_SFT                  17
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_MASK                 0x7
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_MASK_SFT             (0x7 << 17)
#घोषणा UL_AP_DMIC_ON_SFT                              16
#घोषणा UL_AP_DMIC_ON_MASK                             0x1
#घोषणा UL_AP_DMIC_ON_MASK_SFT                         (0x1 << 16)
#घोषणा DMIC_LOW_POWER_MODE_CTL_SFT                    14
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK                   0x3
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK_SFT               (0x3 << 14)
#घोषणा UL_DISABLE_HW_CG_CTL_SFT                       12
#घोषणा UL_DISABLE_HW_CG_CTL_MASK                      0x1
#घोषणा UL_DISABLE_HW_CG_CTL_MASK_SFT                  (0x1 << 12)
#घोषणा UL_IIR_ON_TMP_CTL_SFT                          10
#घोषणा UL_IIR_ON_TMP_CTL_MASK                         0x1
#घोषणा UL_IIR_ON_TMP_CTL_MASK_SFT                     (0x1 << 10)
#घोषणा UL_IIRMODE_CTL_SFT                             7
#घोषणा UL_IIRMODE_CTL_MASK                            0x7
#घोषणा UL_IIRMODE_CTL_MASK_SFT                        (0x7 << 7)
#घोषणा DIGMIC_4P33M_SEL_SFT                           6
#घोषणा DIGMIC_4P33M_SEL_MASK                          0x1
#घोषणा DIGMIC_4P33M_SEL_MASK_SFT                      (0x1 << 6)
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_SFT                5
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK               0x1
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK_SFT           (0x1 << 5)
#घोषणा UL_LOOP_BACK_MODE_CTL_SFT                      2
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK                     0x1
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK_SFT                 (0x1 << 2)
#घोषणा UL_SDM_3_LEVEL_CTL_SFT                         1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK                        0x1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK_SFT                    (0x1 << 1)
#घोषणा UL_SRC_ON_TMP_CTL_SFT                          0
#घोषणा UL_SRC_ON_TMP_CTL_MASK                         0x1
#घोषणा UL_SRC_ON_TMP_CTL_MASK_SFT                     (0x1 << 0)

/* AFE_ADDA_UL_SRC_CON1 */
#घोषणा C_DAC_EN_CTL_SFT                               27
#घोषणा C_DAC_EN_CTL_MASK                              0x1
#घोषणा C_DAC_EN_CTL_MASK_SFT                          (0x1 << 27)
#घोषणा C_MUTE_SW_CTL_SFT                              26
#घोषणा C_MUTE_SW_CTL_MASK                             0x1
#घोषणा C_MUTE_SW_CTL_MASK_SFT                         (0x1 << 26)
#घोषणा ASDM_SRC_SEL_CTL_SFT                           25
#घोषणा ASDM_SRC_SEL_CTL_MASK                          0x1
#घोषणा ASDM_SRC_SEL_CTL_MASK_SFT                      (0x1 << 25)
#घोषणा C_AMP_DIV_CH2_CTL_SFT                          21
#घोषणा C_AMP_DIV_CH2_CTL_MASK                         0x7
#घोषणा C_AMP_DIV_CH2_CTL_MASK_SFT                     (0x7 << 21)
#घोषणा C_FREQ_DIV_CH2_CTL_SFT                         16
#घोषणा C_FREQ_DIV_CH2_CTL_MASK                        0x1f
#घोषणा C_FREQ_DIV_CH2_CTL_MASK_SFT                    (0x1f << 16)
#घोषणा C_SINE_MODE_CH2_CTL_SFT                        12
#घोषणा C_SINE_MODE_CH2_CTL_MASK                       0xf
#घोषणा C_SINE_MODE_CH2_CTL_MASK_SFT                   (0xf << 12)
#घोषणा C_AMP_DIV_CH1_CTL_SFT                          9
#घोषणा C_AMP_DIV_CH1_CTL_MASK                         0x7
#घोषणा C_AMP_DIV_CH1_CTL_MASK_SFT                     (0x7 << 9)
#घोषणा C_FREQ_DIV_CH1_CTL_SFT                         4
#घोषणा C_FREQ_DIV_CH1_CTL_MASK                        0x1f
#घोषणा C_FREQ_DIV_CH1_CTL_MASK_SFT                    (0x1f << 4)
#घोषणा C_SINE_MODE_CH1_CTL_SFT                        0
#घोषणा C_SINE_MODE_CH1_CTL_MASK                       0xf
#घोषणा C_SINE_MODE_CH1_CTL_MASK_SFT                   (0xf << 0)

/* AFE_ADDA_TOP_CON0 */
#घोषणा C_LOOP_BACK_MODE_CTL_SFT                       12
#घोषणा C_LOOP_BACK_MODE_CTL_MASK                      0xf
#घोषणा C_LOOP_BACK_MODE_CTL_MASK_SFT                  (0xf << 12)
#घोषणा ADDA_UL_GAIN_MODE_SFT                          8
#घोषणा ADDA_UL_GAIN_MODE_MASK                         0x3
#घोषणा ADDA_UL_GAIN_MODE_MASK_SFT                     (0x3 << 8)
#घोषणा C_EXT_ADC_CTL_SFT                              0
#घोषणा C_EXT_ADC_CTL_MASK                             0x1
#घोषणा C_EXT_ADC_CTL_MASK_SFT                         (0x1 << 0)

/* AFE_ADDA_UL_DL_CON0 */
#घोषणा AFE_ADDA_UL_LR_SWAP_SFT                        31
#घोषणा AFE_ADDA_UL_LR_SWAP_MASK                       0x1
#घोषणा AFE_ADDA_UL_LR_SWAP_MASK_SFT                   (0x1 << 31)
#घोषणा AFE_ADDA_CKDIV_RST_SFT                         30
#घोषणा AFE_ADDA_CKDIV_RST_MASK                        0x1
#घोषणा AFE_ADDA_CKDIV_RST_MASK_SFT                    (0x1 << 30)
#घोषणा AFE_ADDA_FIFO_AUTO_RST_SFT                     29
#घोषणा AFE_ADDA_FIFO_AUTO_RST_MASK                    0x1
#घोषणा AFE_ADDA_FIFO_AUTO_RST_MASK_SFT                (0x1 << 29)
#घोषणा AFE_ADDA_UL_FIFO_DIGMIC_TESTIN_SFT             21
#घोषणा AFE_ADDA_UL_FIFO_DIGMIC_TESTIN_MASK            0x3
#घोषणा AFE_ADDA_UL_FIFO_DIGMIC_TESTIN_MASK_SFT        (0x3 << 21)
#घोषणा AFE_ADDA_UL_FIFO_DIGMIC_WDATA_TESTEN_SFT       20
#घोषणा AFE_ADDA_UL_FIFO_DIGMIC_WDATA_TESTEN_MASK      0x1
#घोषणा AFE_ADDA_UL_FIFO_DIGMIC_WDATA_TESTEN_MASK_SFT  (0x1 << 20)
#घोषणा AFE_ADDA6_UL_LR_SWAP_SFT                       15
#घोषणा AFE_ADDA6_UL_LR_SWAP_MASK                      0x1
#घोषणा AFE_ADDA6_UL_LR_SWAP_MASK_SFT                  (0x1 << 15)
#घोषणा AFE_ADDA6_CKDIV_RST_SFT                        14
#घोषणा AFE_ADDA6_CKDIV_RST_MASK                       0x1
#घोषणा AFE_ADDA6_CKDIV_RST_MASK_SFT                   (0x1 << 14)
#घोषणा AFE_ADDA6_FIFO_AUTO_RST_SFT                    13
#घोषणा AFE_ADDA6_FIFO_AUTO_RST_MASK                   0x1
#घोषणा AFE_ADDA6_FIFO_AUTO_RST_MASK_SFT               (0x1 << 13)
#घोषणा AFE_ADDA6_UL_FIFO_DIGMIC_TESTIN_SFT            5
#घोषणा AFE_ADDA6_UL_FIFO_DIGMIC_TESTIN_MASK           0x3
#घोषणा AFE_ADDA6_UL_FIFO_DIGMIC_TESTIN_MASK_SFT       (0x3 << 5)
#घोषणा AFE_ADDA6_UL_FIFO_DIGMIC_WDATA_TESTEN_SFT      4
#घोषणा AFE_ADDA6_UL_FIFO_DIGMIC_WDATA_TESTEN_MASK     0x1
#घोषणा AFE_ADDA6_UL_FIFO_DIGMIC_WDATA_TESTEN_MASK_SFT (0x1 << 4)
#घोषणा ADDA_AFE_ON_SFT                                0
#घोषणा ADDA_AFE_ON_MASK                               0x1
#घोषणा ADDA_AFE_ON_MASK_SFT                           (0x1 << 0)

/* AFE_SIDETONE_CON0 */
#घोषणा R_RDY_SFT                                      30
#घोषणा R_RDY_MASK                                     0x1
#घोषणा R_RDY_MASK_SFT                                 (0x1 << 30)
#घोषणा W_RDY_SFT                                      29
#घोषणा W_RDY_MASK                                     0x1
#घोषणा W_RDY_MASK_SFT                                 (0x1 << 29)
#घोषणा R_W_EN_SFT                                     25
#घोषणा R_W_EN_MASK                                    0x1
#घोषणा R_W_EN_MASK_SFT                                (0x1 << 25)
#घोषणा R_W_SEL_SFT                                    24
#घोषणा R_W_SEL_MASK                                   0x1
#घोषणा R_W_SEL_MASK_SFT                               (0x1 << 24)
#घोषणा SEL_CH2_SFT                                    23
#घोषणा SEL_CH2_MASK                                   0x1
#घोषणा SEL_CH2_MASK_SFT                               (0x1 << 23)
#घोषणा SIDE_TONE_COEFFICIENT_ADDR_SFT                 16
#घोषणा SIDE_TONE_COEFFICIENT_ADDR_MASK                0x1f
#घोषणा SIDE_TONE_COEFFICIENT_ADDR_MASK_SFT            (0x1f << 16)
#घोषणा SIDE_TONE_COEFFICIENT_SFT                      0
#घोषणा SIDE_TONE_COEFFICIENT_MASK                     0xffff
#घोषणा SIDE_TONE_COEFFICIENT_MASK_SFT                 (0xffff << 0)

/* AFE_SIDETONE_COEFF */
#घोषणा SIDE_TONE_COEFF_SFT                            0
#घोषणा SIDE_TONE_COEFF_MASK                           0xffff
#घोषणा SIDE_TONE_COEFF_MASK_SFT                       (0xffff << 0)

/* AFE_SIDETONE_CON1 */
#घोषणा STF_BYPASS_MODE_SFT                            31
#घोषणा STF_BYPASS_MODE_MASK                           0x1
#घोषणा STF_BYPASS_MODE_MASK_SFT                       (0x1 << 31)
#घोषणा STF_BYPASS_MODE_O28_O29_SFT                    30
#घोषणा STF_BYPASS_MODE_O28_O29_MASK                   0x1
#घोषणा STF_BYPASS_MODE_O28_O29_MASK_SFT               (0x1 << 30)
#घोषणा STF_BYPASS_MODE_I2S4_SFT                       29
#घोषणा STF_BYPASS_MODE_I2S4_MASK                      0x1
#घोषणा STF_BYPASS_MODE_I2S4_MASK_SFT                  (0x1 << 29)
#घोषणा STF_BYPASS_MODE_I2S5_SFT                       28
#घोषणा STF_BYPASS_MODE_I2S5_MASK                      0x1
#घोषणा STF_BYPASS_MODE_I2S5_MASK_SFT                  (0x1 << 28)
#घोषणा STF_BYPASS_MODE_DL3_SFT                        27
#घोषणा STF_BYPASS_MODE_DL3_MASK                       0x1
#घोषणा STF_BYPASS_MODE_DL3_MASK_SFT                   (0x1 << 27)
#घोषणा STF_BYPASS_MODE_I2S7_SFT                       26
#घोषणा STF_BYPASS_MODE_I2S7_MASK                      0x1
#घोषणा STF_BYPASS_MODE_I2S7_MASK_SFT                  (0x1 << 26)
#घोषणा STF_BYPASS_MODE_I2S9_SFT                       25
#घोषणा STF_BYPASS_MODE_I2S9_MASK                      0x1
#घोषणा STF_BYPASS_MODE_I2S9_MASK_SFT                  (0x1 << 25)
#घोषणा STF_O19O20_OUT_EN_SEL_SFT                      13
#घोषणा STF_O19O20_OUT_EN_SEL_MASK                     0x1
#घोषणा STF_O19O20_OUT_EN_SEL_MASK_SFT                 (0x1 << 13)
#घोषणा STF_SOURCE_FROM_O19O20_SFT                     12
#घोषणा STF_SOURCE_FROM_O19O20_MASK                    0x1
#घोषणा STF_SOURCE_FROM_O19O20_MASK_SFT                (0x1 << 12)
#घोषणा SIDE_TONE_ON_SFT                               8
#घोषणा SIDE_TONE_ON_MASK                              0x1
#घोषणा SIDE_TONE_ON_MASK_SFT                          (0x1 << 8)
#घोषणा SIDE_TONE_HALF_TAP_NUM_SFT                     0
#घोषणा SIDE_TONE_HALF_TAP_NUM_MASK                    0x3f
#घोषणा SIDE_TONE_HALF_TAP_NUM_MASK_SFT                (0x3f << 0)

/* AFE_SIDETONE_GAIN */
#घोषणा POSITIVE_GAIN_SFT                              16
#घोषणा POSITIVE_GAIN_MASK                             0x7
#घोषणा POSITIVE_GAIN_MASK_SFT                         (0x7 << 16)
#घोषणा SIDE_TONE_GAIN_SFT                             0
#घोषणा SIDE_TONE_GAIN_MASK                            0xffff
#घोषणा SIDE_TONE_GAIN_MASK_SFT                        (0xffff << 0)

/* AFE_ADDA_DL_SDM_DCCOMP_CON */
#घोषणा USE_3RD_SDM_SFT                                28
#घोषणा USE_3RD_SDM_MASK                               0x1
#घोषणा USE_3RD_SDM_MASK_SFT                           (0x1 << 28)
#घोषणा DL_FIFO_START_POINT_SFT                        24
#घोषणा DL_FIFO_START_POINT_MASK                       0x7
#घोषणा DL_FIFO_START_POINT_MASK_SFT                   (0x7 << 24)
#घोषणा DL_FIFO_SWAP_SFT                               20
#घोषणा DL_FIFO_SWAP_MASK                              0x1
#घोषणा DL_FIFO_SWAP_MASK_SFT                          (0x1 << 20)
#घोषणा C_AUDSDM1ORDSELECT_CTL_SFT                     19
#घोषणा C_AUDSDM1ORDSELECT_CTL_MASK                    0x1
#घोषणा C_AUDSDM1ORDSELECT_CTL_MASK_SFT                (0x1 << 19)
#घोषणा C_SDM7BITSEL_CTL_SFT                           18
#घोषणा C_SDM7BITSEL_CTL_MASK                          0x1
#घोषणा C_SDM7BITSEL_CTL_MASK_SFT                      (0x1 << 18)
#घोषणा GAIN_AT_SDM_RST_PRE_CTL_SFT                    15
#घोषणा GAIN_AT_SDM_RST_PRE_CTL_MASK                   0x1
#घोषणा GAIN_AT_SDM_RST_PRE_CTL_MASK_SFT               (0x1 << 15)
#घोषणा DL_DCM_AUTO_IDLE_EN_SFT                        14
#घोषणा DL_DCM_AUTO_IDLE_EN_MASK                       0x1
#घोषणा DL_DCM_AUTO_IDLE_EN_MASK_SFT                   (0x1 << 14)
#घोषणा AFE_DL_SRC_DCM_EN_SFT                          13
#घोषणा AFE_DL_SRC_DCM_EN_MASK                         0x1
#घोषणा AFE_DL_SRC_DCM_EN_MASK_SFT                     (0x1 << 13)
#घोषणा AFE_DL_POST_SRC_DCM_EN_SFT                     12
#घोषणा AFE_DL_POST_SRC_DCM_EN_MASK                    0x1
#घोषणा AFE_DL_POST_SRC_DCM_EN_MASK_SFT                (0x1 << 12)
#घोषणा AUD_SDM_MONO_SFT                               9
#घोषणा AUD_SDM_MONO_MASK                              0x1
#घोषणा AUD_SDM_MONO_MASK_SFT                          (0x1 << 9)
#घोषणा AUD_DC_COMP_EN_SFT                             8
#घोषणा AUD_DC_COMP_EN_MASK                            0x1
#घोषणा AUD_DC_COMP_EN_MASK_SFT                        (0x1 << 8)
#घोषणा ATTGAIN_CTL_SFT                                0
#घोषणा ATTGAIN_CTL_MASK                               0x3f
#घोषणा ATTGAIN_CTL_MASK_SFT                           (0x3f << 0)

/* AFE_SINEGEN_CON0 */
#घोषणा DAC_EN_SFT                                     26
#घोषणा DAC_EN_MASK                                    0x1
#घोषणा DAC_EN_MASK_SFT                                (0x1 << 26)
#घोषणा MUTE_SW_CH2_SFT                                25
#घोषणा MUTE_SW_CH2_MASK                               0x1
#घोषणा MUTE_SW_CH2_MASK_SFT                           (0x1 << 25)
#घोषणा MUTE_SW_CH1_SFT                                24
#घोषणा MUTE_SW_CH1_MASK                               0x1
#घोषणा MUTE_SW_CH1_MASK_SFT                           (0x1 << 24)
#घोषणा SINE_MODE_CH2_SFT                              20
#घोषणा SINE_MODE_CH2_MASK                             0xf
#घोषणा SINE_MODE_CH2_MASK_SFT                         (0xf << 20)
#घोषणा AMP_DIV_CH2_SFT                                17
#घोषणा AMP_DIV_CH2_MASK                               0x7
#घोषणा AMP_DIV_CH2_MASK_SFT                           (0x7 << 17)
#घोषणा FREQ_DIV_CH2_SFT                               12
#घोषणा FREQ_DIV_CH2_MASK                              0x1f
#घोषणा FREQ_DIV_CH2_MASK_SFT                          (0x1f << 12)
#घोषणा SINE_MODE_CH1_SFT                              8
#घोषणा SINE_MODE_CH1_MASK                             0xf
#घोषणा SINE_MODE_CH1_MASK_SFT                         (0xf << 8)
#घोषणा AMP_DIV_CH1_SFT                                5
#घोषणा AMP_DIV_CH1_MASK                               0x7
#घोषणा AMP_DIV_CH1_MASK_SFT                           (0x7 << 5)
#घोषणा FREQ_DIV_CH1_SFT                               0
#घोषणा FREQ_DIV_CH1_MASK                              0x1f
#घोषणा FREQ_DIV_CH1_MASK_SFT                          (0x1f << 0)

/* AFE_SINEGEN_CON2 */
#घोषणा INNER_LOOP_BACK_MODE_SFT                       0
#घोषणा INNER_LOOP_BACK_MODE_MASK                      0x3f
#घोषणा INNER_LOOP_BACK_MODE_MASK_SFT                  (0x3f << 0)

/* AFE_HD_ENGEN_ENABLE */
#घोषणा AFE_24M_ON_SFT                                 1
#घोषणा AFE_24M_ON_MASK                                0x1
#घोषणा AFE_24M_ON_MASK_SFT                            (0x1 << 1)
#घोषणा AFE_22M_ON_SFT                                 0
#घोषणा AFE_22M_ON_MASK                                0x1
#घोषणा AFE_22M_ON_MASK_SFT                            (0x1 << 0)

/* AFE_ADDA_DL_NLE_FIFO_MON */
#घोषणा DL_NLE_FIFO_WBIN_SFT                           8
#घोषणा DL_NLE_FIFO_WBIN_MASK                          0xf
#घोषणा DL_NLE_FIFO_WBIN_MASK_SFT                      (0xf << 8)
#घोषणा DL_NLE_FIFO_RBIN_SFT                           4
#घोषणा DL_NLE_FIFO_RBIN_MASK                          0xf
#घोषणा DL_NLE_FIFO_RBIN_MASK_SFT                      (0xf << 4)
#घोषणा DL_NLE_FIFO_RDACTIVE_SFT                       3
#घोषणा DL_NLE_FIFO_RDACTIVE_MASK                      0x1
#घोषणा DL_NLE_FIFO_RDACTIVE_MASK_SFT                  (0x1 << 3)
#घोषणा DL_NLE_FIFO_STARTRD_SFT                        2
#घोषणा DL_NLE_FIFO_STARTRD_MASK                       0x1
#घोषणा DL_NLE_FIFO_STARTRD_MASK_SFT                   (0x1 << 2)
#घोषणा DL_NLE_FIFO_RD_EMPTY_SFT                       1
#घोषणा DL_NLE_FIFO_RD_EMPTY_MASK                      0x1
#घोषणा DL_NLE_FIFO_RD_EMPTY_MASK_SFT                  (0x1 << 1)
#घोषणा DL_NLE_FIFO_WR_FULL_SFT                        0
#घोषणा DL_NLE_FIFO_WR_FULL_MASK                       0x1
#घोषणा DL_NLE_FIFO_WR_FULL_MASK_SFT                   (0x1 << 0)

/* AFE_DL1_CON0 */
#घोषणा DL1_MODE_SFT                                   24
#घोषणा DL1_MODE_MASK                                  0xf
#घोषणा DL1_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL1_MINLEN_SFT                                 20
#घोषणा DL1_MINLEN_MASK                                0xf
#घोषणा DL1_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL1_MAXLEN_SFT                                 16
#घोषणा DL1_MAXLEN_MASK                                0xf
#घोषणा DL1_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL1_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL1_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL1_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL1_PBUF_SIZE_SFT                              12
#घोषणा DL1_PBUF_SIZE_MASK                             0x3
#घोषणा DL1_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL1_MONO_SFT                                   8
#घोषणा DL1_MONO_MASK                                  0x1
#घोषणा DL1_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL1_NORMAL_MODE_SFT                            5
#घोषणा DL1_NORMAL_MODE_MASK                           0x1
#घोषणा DL1_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL1_HALIGN_SFT                                 4
#घोषणा DL1_HALIGN_MASK                                0x1
#घोषणा DL1_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL1_HD_MODE_SFT                                0
#घोषणा DL1_HD_MODE_MASK                               0x3
#घोषणा DL1_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL2_CON0 */
#घोषणा DL2_MODE_SFT                                   24
#घोषणा DL2_MODE_MASK                                  0xf
#घोषणा DL2_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL2_MINLEN_SFT                                 20
#घोषणा DL2_MINLEN_MASK                                0xf
#घोषणा DL2_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL2_MAXLEN_SFT                                 16
#घोषणा DL2_MAXLEN_MASK                                0xf
#घोषणा DL2_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL2_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL2_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL2_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL2_PBUF_SIZE_SFT                              12
#घोषणा DL2_PBUF_SIZE_MASK                             0x3
#घोषणा DL2_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL2_MONO_SFT                                   8
#घोषणा DL2_MONO_MASK                                  0x1
#घोषणा DL2_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL2_NORMAL_MODE_SFT                            5
#घोषणा DL2_NORMAL_MODE_MASK                           0x1
#घोषणा DL2_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL2_HALIGN_SFT                                 4
#घोषणा DL2_HALIGN_MASK                                0x1
#घोषणा DL2_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL2_HD_MODE_SFT                                0
#घोषणा DL2_HD_MODE_MASK                               0x3
#घोषणा DL2_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL3_CON0 */
#घोषणा DL3_MODE_SFT                                   24
#घोषणा DL3_MODE_MASK                                  0xf
#घोषणा DL3_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL3_MINLEN_SFT                                 20
#घोषणा DL3_MINLEN_MASK                                0xf
#घोषणा DL3_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL3_MAXLEN_SFT                                 16
#घोषणा DL3_MAXLEN_MASK                                0xf
#घोषणा DL3_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL3_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL3_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL3_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL3_PBUF_SIZE_SFT                              12
#घोषणा DL3_PBUF_SIZE_MASK                             0x3
#घोषणा DL3_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL3_MONO_SFT                                   8
#घोषणा DL3_MONO_MASK                                  0x1
#घोषणा DL3_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL3_NORMAL_MODE_SFT                            5
#घोषणा DL3_NORMAL_MODE_MASK                           0x1
#घोषणा DL3_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL3_HALIGN_SFT                                 4
#घोषणा DL3_HALIGN_MASK                                0x1
#घोषणा DL3_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL3_HD_MODE_SFT                                0
#घोषणा DL3_HD_MODE_MASK                               0x3
#घोषणा DL3_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL4_CON0 */
#घोषणा DL4_MODE_SFT                                   24
#घोषणा DL4_MODE_MASK                                  0xf
#घोषणा DL4_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL4_MINLEN_SFT                                 20
#घोषणा DL4_MINLEN_MASK                                0xf
#घोषणा DL4_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL4_MAXLEN_SFT                                 16
#घोषणा DL4_MAXLEN_MASK                                0xf
#घोषणा DL4_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL4_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL4_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL4_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL4_PBUF_SIZE_SFT                              12
#घोषणा DL4_PBUF_SIZE_MASK                             0x3
#घोषणा DL4_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL4_MONO_SFT                                   8
#घोषणा DL4_MONO_MASK                                  0x1
#घोषणा DL4_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL4_NORMAL_MODE_SFT                            5
#घोषणा DL4_NORMAL_MODE_MASK                           0x1
#घोषणा DL4_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL4_HALIGN_SFT                                 4
#घोषणा DL4_HALIGN_MASK                                0x1
#घोषणा DL4_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL4_HD_MODE_SFT                                0
#घोषणा DL4_HD_MODE_MASK                               0x3
#घोषणा DL4_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL5_CON0 */
#घोषणा DL5_MODE_SFT                                   24
#घोषणा DL5_MODE_MASK                                  0xf
#घोषणा DL5_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL5_MINLEN_SFT                                 20
#घोषणा DL5_MINLEN_MASK                                0xf
#घोषणा DL5_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL5_MAXLEN_SFT                                 16
#घोषणा DL5_MAXLEN_MASK                                0xf
#घोषणा DL5_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL5_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL5_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL5_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL5_PBUF_SIZE_SFT                              12
#घोषणा DL5_PBUF_SIZE_MASK                             0x3
#घोषणा DL5_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL5_MONO_SFT                                   8
#घोषणा DL5_MONO_MASK                                  0x1
#घोषणा DL5_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL5_NORMAL_MODE_SFT                            5
#घोषणा DL5_NORMAL_MODE_MASK                           0x1
#घोषणा DL5_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL5_HALIGN_SFT                                 4
#घोषणा DL5_HALIGN_MASK                                0x1
#घोषणा DL5_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL5_HD_MODE_SFT                                0
#घोषणा DL5_HD_MODE_MASK                               0x3
#घोषणा DL5_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL6_CON0 */
#घोषणा DL6_MODE_SFT                                   24
#घोषणा DL6_MODE_MASK                                  0xf
#घोषणा DL6_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL6_MINLEN_SFT                                 20
#घोषणा DL6_MINLEN_MASK                                0xf
#घोषणा DL6_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL6_MAXLEN_SFT                                 16
#घोषणा DL6_MAXLEN_MASK                                0xf
#घोषणा DL6_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL6_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL6_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL6_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL6_PBUF_SIZE_SFT                              12
#घोषणा DL6_PBUF_SIZE_MASK                             0x3
#घोषणा DL6_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL6_MONO_SFT                                   8
#घोषणा DL6_MONO_MASK                                  0x1
#घोषणा DL6_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL6_NORMAL_MODE_SFT                            5
#घोषणा DL6_NORMAL_MODE_MASK                           0x1
#घोषणा DL6_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL6_HALIGN_SFT                                 4
#घोषणा DL6_HALIGN_MASK                                0x1
#घोषणा DL6_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL6_HD_MODE_SFT                                0
#घोषणा DL6_HD_MODE_MASK                               0x3
#घोषणा DL6_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL7_CON0 */
#घोषणा DL7_MODE_SFT                                   24
#घोषणा DL7_MODE_MASK                                  0xf
#घोषणा DL7_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL7_MINLEN_SFT                                 20
#घोषणा DL7_MINLEN_MASK                                0xf
#घोषणा DL7_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL7_MAXLEN_SFT                                 16
#घोषणा DL7_MAXLEN_MASK                                0xf
#घोषणा DL7_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL7_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL7_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL7_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL7_PBUF_SIZE_SFT                              12
#घोषणा DL7_PBUF_SIZE_MASK                             0x3
#घोषणा DL7_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL7_MONO_SFT                                   8
#घोषणा DL7_MONO_MASK                                  0x1
#घोषणा DL7_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL7_NORMAL_MODE_SFT                            5
#घोषणा DL7_NORMAL_MODE_MASK                           0x1
#घोषणा DL7_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL7_HALIGN_SFT                                 4
#घोषणा DL7_HALIGN_MASK                                0x1
#घोषणा DL7_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL7_HD_MODE_SFT                                0
#घोषणा DL7_HD_MODE_MASK                               0x3
#घोषणा DL7_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL8_CON0 */
#घोषणा DL8_MODE_SFT                                   24
#घोषणा DL8_MODE_MASK                                  0xf
#घोषणा DL8_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL8_MINLEN_SFT                                 20
#घोषणा DL8_MINLEN_MASK                                0xf
#घोषणा DL8_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL8_MAXLEN_SFT                                 16
#घोषणा DL8_MAXLEN_MASK                                0xf
#घोषणा DL8_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL8_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL8_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL8_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL8_PBUF_SIZE_SFT                              12
#घोषणा DL8_PBUF_SIZE_MASK                             0x3
#घोषणा DL8_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL8_MONO_SFT                                   8
#घोषणा DL8_MONO_MASK                                  0x1
#घोषणा DL8_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL8_NORMAL_MODE_SFT                            5
#घोषणा DL8_NORMAL_MODE_MASK                           0x1
#घोषणा DL8_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL8_HALIGN_SFT                                 4
#घोषणा DL8_HALIGN_MASK                                0x1
#घोषणा DL8_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL8_HD_MODE_SFT                                0
#घोषणा DL8_HD_MODE_MASK                               0x3
#घोषणा DL8_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL9_CON0 */
#घोषणा DL9_MODE_SFT                                   24
#घोषणा DL9_MODE_MASK                                  0xf
#घोषणा DL9_MODE_MASK_SFT                              (0xf << 24)
#घोषणा DL9_MINLEN_SFT                                 20
#घोषणा DL9_MINLEN_MASK                                0xf
#घोषणा DL9_MINLEN_MASK_SFT                            (0xf << 20)
#घोषणा DL9_MAXLEN_SFT                                 16
#घोषणा DL9_MAXLEN_MASK                                0xf
#घोषणा DL9_MAXLEN_MASK_SFT                            (0xf << 16)
#घोषणा DL9_SW_CLEAR_BUF_EMPTY_SFT                     15
#घोषणा DL9_SW_CLEAR_BUF_EMPTY_MASK                    0x1
#घोषणा DL9_SW_CLEAR_BUF_EMPTY_MASK_SFT                (0x1 << 15)
#घोषणा DL9_PBUF_SIZE_SFT                              12
#घोषणा DL9_PBUF_SIZE_MASK                             0x3
#घोषणा DL9_PBUF_SIZE_MASK_SFT                         (0x3 << 12)
#घोषणा DL9_MONO_SFT                                   8
#घोषणा DL9_MONO_MASK                                  0x1
#घोषणा DL9_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DL9_NORMAL_MODE_SFT                            5
#घोषणा DL9_NORMAL_MODE_MASK                           0x1
#घोषणा DL9_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DL9_HALIGN_SFT                                 4
#घोषणा DL9_HALIGN_MASK                                0x1
#घोषणा DL9_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DL9_HD_MODE_SFT                                0
#घोषणा DL9_HD_MODE_MASK                               0x3
#घोषणा DL9_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_DL12_CON0 */
#घोषणा DL12_MODE_SFT                                  24
#घोषणा DL12_MODE_MASK                                 0xf
#घोषणा DL12_MODE_MASK_SFT                             (0xf << 24)
#घोषणा DL12_MINLEN_SFT                                20
#घोषणा DL12_MINLEN_MASK                               0xf
#घोषणा DL12_MINLEN_MASK_SFT                           (0xf << 20)
#घोषणा DL12_MAXLEN_SFT                                16
#घोषणा DL12_MAXLEN_MASK                               0xf
#घोषणा DL12_MAXLEN_MASK_SFT                           (0xf << 16)
#घोषणा DL12_SW_CLEAR_BUF_EMPTY_SFT                    15
#घोषणा DL12_SW_CLEAR_BUF_EMPTY_MASK                   0x1
#घोषणा DL12_SW_CLEAR_BUF_EMPTY_MASK_SFT               (0x1 << 15)
#घोषणा DL12_PBUF_SIZE_SFT                             12
#घोषणा DL12_PBUF_SIZE_MASK                            0x3
#घोषणा DL12_PBUF_SIZE_MASK_SFT                        (0x3 << 12)
#घोषणा DL12_4CH_EN_SFT                                11
#घोषणा DL12_4CH_EN_MASK                               0x1
#घोषणा DL12_4CH_EN_MASK_SFT                           (0x1 << 11)
#घोषणा DL12_MONO_SFT                                  8
#घोषणा DL12_MONO_MASK                                 0x1
#घोषणा DL12_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा DL12_NORMAL_MODE_SFT                           5
#घोषणा DL12_NORMAL_MODE_MASK                          0x1
#घोषणा DL12_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा DL12_HALIGN_SFT                                4
#घोषणा DL12_HALIGN_MASK                               0x1
#घोषणा DL12_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा DL12_HD_MODE_SFT                               0
#घोषणा DL12_HD_MODE_MASK                              0x3
#घोषणा DL12_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_AWB_CON0 */
#घोषणा AWB_MODE_SFT                                   24
#घोषणा AWB_MODE_MASK                                  0xf
#घोषणा AWB_MODE_MASK_SFT                              (0xf << 24)
#घोषणा AWB_SW_CLEAR_BUF_FULL_SFT                      15
#घोषणा AWB_SW_CLEAR_BUF_FULL_MASK                     0x1
#घोषणा AWB_SW_CLEAR_BUF_FULL_MASK_SFT                 (0x1 << 15)
#घोषणा AWB_R_MONO_SFT                                 9
#घोषणा AWB_R_MONO_MASK                                0x1
#घोषणा AWB_R_MONO_MASK_SFT                            (0x1 << 9)
#घोषणा AWB_MONO_SFT                                   8
#घोषणा AWB_MONO_MASK                                  0x1
#घोषणा AWB_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा AWB_WR_SIGN_SFT                                6
#घोषणा AWB_WR_SIGN_MASK                               0x1
#घोषणा AWB_WR_SIGN_MASK_SFT                           (0x1 << 6)
#घोषणा AWB_NORMAL_MODE_SFT                            5
#घोषणा AWB_NORMAL_MODE_MASK                           0x1
#घोषणा AWB_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा AWB_HALIGN_SFT                                 4
#घोषणा AWB_HALIGN_MASK                                0x1
#घोषणा AWB_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा AWB_HD_MODE_SFT                                0
#घोषणा AWB_HD_MODE_MASK                               0x3
#घोषणा AWB_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_AWB2_CON0 */
#घोषणा AWB2_MODE_SFT                                  24
#घोषणा AWB2_MODE_MASK                                 0xf
#घोषणा AWB2_MODE_MASK_SFT                             (0xf << 24)
#घोषणा AWB2_SW_CLEAR_BUF_FULL_SFT                     15
#घोषणा AWB2_SW_CLEAR_BUF_FULL_MASK                    0x1
#घोषणा AWB2_SW_CLEAR_BUF_FULL_MASK_SFT                (0x1 << 15)
#घोषणा AWB2_R_MONO_SFT                                9
#घोषणा AWB2_R_MONO_MASK                               0x1
#घोषणा AWB2_R_MONO_MASK_SFT                           (0x1 << 9)
#घोषणा AWB2_MONO_SFT                                  8
#घोषणा AWB2_MONO_MASK                                 0x1
#घोषणा AWB2_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा AWB2_WR_SIGN_SFT                               6
#घोषणा AWB2_WR_SIGN_MASK                              0x1
#घोषणा AWB2_WR_SIGN_MASK_SFT                          (0x1 << 6)
#घोषणा AWB2_NORMAL_MODE_SFT                           5
#घोषणा AWB2_NORMAL_MODE_MASK                          0x1
#घोषणा AWB2_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा AWB2_HALIGN_SFT                                4
#घोषणा AWB2_HALIGN_MASK                               0x1
#घोषणा AWB2_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा AWB2_HD_MODE_SFT                               0
#घोषणा AWB2_HD_MODE_MASK                              0x3
#घोषणा AWB2_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_VUL_CON0 */
#घोषणा VUL_MODE_SFT                                   24
#घोषणा VUL_MODE_MASK                                  0xf
#घोषणा VUL_MODE_MASK_SFT                              (0xf << 24)
#घोषणा VUL_SW_CLEAR_BUF_FULL_SFT                      15
#घोषणा VUL_SW_CLEAR_BUF_FULL_MASK                     0x1
#घोषणा VUL_SW_CLEAR_BUF_FULL_MASK_SFT                 (0x1 << 15)
#घोषणा VUL_R_MONO_SFT                                 9
#घोषणा VUL_R_MONO_MASK                                0x1
#घोषणा VUL_R_MONO_MASK_SFT                            (0x1 << 9)
#घोषणा VUL_MONO_SFT                                   8
#घोषणा VUL_MONO_MASK                                  0x1
#घोषणा VUL_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा VUL_WR_SIGN_SFT                                6
#घोषणा VUL_WR_SIGN_MASK                               0x1
#घोषणा VUL_WR_SIGN_MASK_SFT                           (0x1 << 6)
#घोषणा VUL_NORMAL_MODE_SFT                            5
#घोषणा VUL_NORMAL_MODE_MASK                           0x1
#घोषणा VUL_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा VUL_HALIGN_SFT                                 4
#घोषणा VUL_HALIGN_MASK                                0x1
#घोषणा VUL_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा VUL_HD_MODE_SFT                                0
#घोषणा VUL_HD_MODE_MASK                               0x3
#घोषणा VUL_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_VUL12_CON0 */
#घोषणा VUL12_MODE_SFT                                 24
#घोषणा VUL12_MODE_MASK                                0xf
#घोषणा VUL12_MODE_MASK_SFT                            (0xf << 24)
#घोषणा VUL12_SW_CLEAR_BUF_FULL_SFT                    15
#घोषणा VUL12_SW_CLEAR_BUF_FULL_MASK                   0x1
#घोषणा VUL12_SW_CLEAR_BUF_FULL_MASK_SFT               (0x1 << 15)
#घोषणा VUL12_4CH_EN_SFT                               11
#घोषणा VUL12_4CH_EN_MASK                              0x1
#घोषणा VUL12_4CH_EN_MASK_SFT                          (0x1 << 11)
#घोषणा VUL12_R_MONO_SFT                               9
#घोषणा VUL12_R_MONO_MASK                              0x1
#घोषणा VUL12_R_MONO_MASK_SFT                          (0x1 << 9)
#घोषणा VUL12_MONO_SFT                                 8
#घोषणा VUL12_MONO_MASK                                0x1
#घोषणा VUL12_MONO_MASK_SFT                            (0x1 << 8)
#घोषणा VUL12_WR_SIGN_SFT                              6
#घोषणा VUL12_WR_SIGN_MASK                             0x1
#घोषणा VUL12_WR_SIGN_MASK_SFT                         (0x1 << 6)
#घोषणा VUL12_NORMAL_MODE_SFT                          5
#घोषणा VUL12_NORMAL_MODE_MASK                         0x1
#घोषणा VUL12_NORMAL_MODE_MASK_SFT                     (0x1 << 5)
#घोषणा VUL12_HALIGN_SFT                               4
#घोषणा VUL12_HALIGN_MASK                              0x1
#घोषणा VUL12_HALIGN_MASK_SFT                          (0x1 << 4)
#घोषणा VUL12_HD_MODE_SFT                              0
#घोषणा VUL12_HD_MODE_MASK                             0x3
#घोषणा VUL12_HD_MODE_MASK_SFT                         (0x3 << 0)

/* AFE_VUL2_CON0 */
#घोषणा VUL2_MODE_SFT                                  24
#घोषणा VUL2_MODE_MASK                                 0xf
#घोषणा VUL2_MODE_MASK_SFT                             (0xf << 24)
#घोषणा VUL2_SW_CLEAR_BUF_FULL_SFT                     15
#घोषणा VUL2_SW_CLEAR_BUF_FULL_MASK                    0x1
#घोषणा VUL2_SW_CLEAR_BUF_FULL_MASK_SFT                (0x1 << 15)
#घोषणा VUL2_R_MONO_SFT                                9
#घोषणा VUL2_R_MONO_MASK                               0x1
#घोषणा VUL2_R_MONO_MASK_SFT                           (0x1 << 9)
#घोषणा VUL2_MONO_SFT                                  8
#घोषणा VUL2_MONO_MASK                                 0x1
#घोषणा VUL2_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा VUL2_WR_SIGN_SFT                               6
#घोषणा VUL2_WR_SIGN_MASK                              0x1
#घोषणा VUL2_WR_SIGN_MASK_SFT                          (0x1 << 6)
#घोषणा VUL2_NORMAL_MODE_SFT                           5
#घोषणा VUL2_NORMAL_MODE_MASK                          0x1
#घोषणा VUL2_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा VUL2_HALIGN_SFT                                4
#घोषणा VUL2_HALIGN_MASK                               0x1
#घोषणा VUL2_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा VUL2_HD_MODE_SFT                               0
#घोषणा VUL2_HD_MODE_MASK                              0x3
#घोषणा VUL2_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_VUL3_CON0 */
#घोषणा VUL3_MODE_SFT                                  24
#घोषणा VUL3_MODE_MASK                                 0xf
#घोषणा VUL3_MODE_MASK_SFT                             (0xf << 24)
#घोषणा VUL3_SW_CLEAR_BUF_FULL_SFT                     15
#घोषणा VUL3_SW_CLEAR_BUF_FULL_MASK                    0x1
#घोषणा VUL3_SW_CLEAR_BUF_FULL_MASK_SFT                (0x1 << 15)
#घोषणा VUL3_R_MONO_SFT                                9
#घोषणा VUL3_R_MONO_MASK                               0x1
#घोषणा VUL3_R_MONO_MASK_SFT                           (0x1 << 9)
#घोषणा VUL3_MONO_SFT                                  8
#घोषणा VUL3_MONO_MASK                                 0x1
#घोषणा VUL3_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा VUL3_WR_SIGN_SFT                               6
#घोषणा VUL3_WR_SIGN_MASK                              0x1
#घोषणा VUL3_WR_SIGN_MASK_SFT                          (0x1 << 6)
#घोषणा VUL3_NORMAL_MODE_SFT                           5
#घोषणा VUL3_NORMAL_MODE_MASK                          0x1
#घोषणा VUL3_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा VUL3_HALIGN_SFT                                4
#घोषणा VUL3_HALIGN_MASK                               0x1
#घोषणा VUL3_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा VUL3_HD_MODE_SFT                               0
#घोषणा VUL3_HD_MODE_MASK                              0x3
#घोषणा VUL3_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_VUL4_CON0 */
#घोषणा VUL4_MODE_SFT                                  24
#घोषणा VUL4_MODE_MASK                                 0xf
#घोषणा VUL4_MODE_MASK_SFT                             (0xf << 24)
#घोषणा VUL4_SW_CLEAR_BUF_FULL_SFT                     15
#घोषणा VUL4_SW_CLEAR_BUF_FULL_MASK                    0x1
#घोषणा VUL4_SW_CLEAR_BUF_FULL_MASK_SFT                (0x1 << 15)
#घोषणा VUL4_R_MONO_SFT                                9
#घोषणा VUL4_R_MONO_MASK                               0x1
#घोषणा VUL4_R_MONO_MASK_SFT                           (0x1 << 9)
#घोषणा VUL4_MONO_SFT                                  8
#घोषणा VUL4_MONO_MASK                                 0x1
#घोषणा VUL4_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा VUL4_WR_SIGN_SFT                               6
#घोषणा VUL4_WR_SIGN_MASK                              0x1
#घोषणा VUL4_WR_SIGN_MASK_SFT                          (0x1 << 6)
#घोषणा VUL4_NORMAL_MODE_SFT                           5
#घोषणा VUL4_NORMAL_MODE_MASK                          0x1
#घोषणा VUL4_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा VUL4_HALIGN_SFT                                4
#घोषणा VUL4_HALIGN_MASK                               0x1
#घोषणा VUL4_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा VUL4_HD_MODE_SFT                               0
#घोषणा VUL4_HD_MODE_MASK                              0x3
#घोषणा VUL4_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_VUL5_CON0 */
#घोषणा VUL5_MODE_SFT                                  24
#घोषणा VUL5_MODE_MASK                                 0xf
#घोषणा VUL5_MODE_MASK_SFT                             (0xf << 24)
#घोषणा VUL5_SW_CLEAR_BUF_FULL_SFT                     15
#घोषणा VUL5_SW_CLEAR_BUF_FULL_MASK                    0x1
#घोषणा VUL5_SW_CLEAR_BUF_FULL_MASK_SFT                (0x1 << 15)
#घोषणा VUL5_R_MONO_SFT                                9
#घोषणा VUL5_R_MONO_MASK                               0x1
#घोषणा VUL5_R_MONO_MASK_SFT                           (0x1 << 9)
#घोषणा VUL5_MONO_SFT                                  8
#घोषणा VUL5_MONO_MASK                                 0x1
#घोषणा VUL5_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा VUL5_WR_SIGN_SFT                               6
#घोषणा VUL5_WR_SIGN_MASK                              0x1
#घोषणा VUL5_WR_SIGN_MASK_SFT                          (0x1 << 6)
#घोषणा VUL5_NORMAL_MODE_SFT                           5
#घोषणा VUL5_NORMAL_MODE_MASK                          0x1
#घोषणा VUL5_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा VUL5_HALIGN_SFT                                4
#घोषणा VUL5_HALIGN_MASK                               0x1
#घोषणा VUL5_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा VUL5_HD_MODE_SFT                               0
#घोषणा VUL5_HD_MODE_MASK                              0x3
#घोषणा VUL5_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_VUL6_CON0 */
#घोषणा VUL6_MODE_SFT                                  24
#घोषणा VUL6_MODE_MASK                                 0xf
#घोषणा VUL6_MODE_MASK_SFT                             (0xf << 24)
#घोषणा VUL6_SW_CLEAR_BUF_FULL_SFT                     15
#घोषणा VUL6_SW_CLEAR_BUF_FULL_MASK                    0x1
#घोषणा VUL6_SW_CLEAR_BUF_FULL_MASK_SFT                (0x1 << 15)
#घोषणा VUL6_R_MONO_SFT                                9
#घोषणा VUL6_R_MONO_MASK                               0x1
#घोषणा VUL6_R_MONO_MASK_SFT                           (0x1 << 9)
#घोषणा VUL6_MONO_SFT                                  8
#घोषणा VUL6_MONO_MASK                                 0x1
#घोषणा VUL6_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा VUL6_WR_SIGN_SFT                               6
#घोषणा VUL6_WR_SIGN_MASK                              0x1
#घोषणा VUL6_WR_SIGN_MASK_SFT                          (0x1 << 6)
#घोषणा VUL6_NORMAL_MODE_SFT                           5
#घोषणा VUL6_NORMAL_MODE_MASK                          0x1
#घोषणा VUL6_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा VUL6_HALIGN_SFT                                4
#घोषणा VUL6_HALIGN_MASK                               0x1
#घोषणा VUL6_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा VUL6_HD_MODE_SFT                               0
#घोषणा VUL6_HD_MODE_MASK                              0x3
#घोषणा VUL6_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_DAI_CON0 */
#घोषणा DAI_MODE_SFT                                   24
#घोषणा DAI_MODE_MASK                                  0x3
#घोषणा DAI_MODE_MASK_SFT                              (0x3 << 24)
#घोषणा DAI_SW_CLEAR_BUF_FULL_SFT                      15
#घोषणा DAI_SW_CLEAR_BUF_FULL_MASK                     0x1
#घोषणा DAI_SW_CLEAR_BUF_FULL_MASK_SFT                 (0x1 << 15)
#घोषणा DAI_DUPLICATE_WR_SFT                           10
#घोषणा DAI_DUPLICATE_WR_MASK                          0x1
#घोषणा DAI_DUPLICATE_WR_MASK_SFT                      (0x1 << 10)
#घोषणा DAI_MONO_SFT                                   8
#घोषणा DAI_MONO_MASK                                  0x1
#घोषणा DAI_MONO_MASK_SFT                              (0x1 << 8)
#घोषणा DAI_WR_SIGN_SFT                                6
#घोषणा DAI_WR_SIGN_MASK                               0x1
#घोषणा DAI_WR_SIGN_MASK_SFT                           (0x1 << 6)
#घोषणा DAI_NORMAL_MODE_SFT                            5
#घोषणा DAI_NORMAL_MODE_MASK                           0x1
#घोषणा DAI_NORMAL_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा DAI_HALIGN_SFT                                 4
#घोषणा DAI_HALIGN_MASK                                0x1
#घोषणा DAI_HALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा DAI_HD_MODE_SFT                                0
#घोषणा DAI_HD_MODE_MASK                               0x3
#घोषणा DAI_HD_MODE_MASK_SFT                           (0x3 << 0)

/* AFE_MOD_DAI_CON0 */
#घोषणा MOD_DAI_MODE_SFT                               24
#घोषणा MOD_DAI_MODE_MASK                              0x3
#घोषणा MOD_DAI_MODE_MASK_SFT                          (0x3 << 24)
#घोषणा MOD_DAI_SW_CLEAR_BUF_FULL_SFT                  15
#घोषणा MOD_DAI_SW_CLEAR_BUF_FULL_MASK                 0x1
#घोषणा MOD_DAI_SW_CLEAR_BUF_FULL_MASK_SFT             (0x1 << 15)
#घोषणा MOD_DAI_DUPLICATE_WR_SFT                       10
#घोषणा MOD_DAI_DUPLICATE_WR_MASK                      0x1
#घोषणा MOD_DAI_DUPLICATE_WR_MASK_SFT                  (0x1 << 10)
#घोषणा MOD_DAI_MONO_SFT                               8
#घोषणा MOD_DAI_MONO_MASK                              0x1
#घोषणा MOD_DAI_MONO_MASK_SFT                          (0x1 << 8)
#घोषणा MOD_DAI_WR_SIGN_SFT                            6
#घोषणा MOD_DAI_WR_SIGN_MASK                           0x1
#घोषणा MOD_DAI_WR_SIGN_MASK_SFT                       (0x1 << 6)
#घोषणा MOD_DAI_NORMAL_MODE_SFT                        5
#घोषणा MOD_DAI_NORMAL_MODE_MASK                       0x1
#घोषणा MOD_DAI_NORMAL_MODE_MASK_SFT                   (0x1 << 5)
#घोषणा MOD_DAI_HALIGN_SFT                             4
#घोषणा MOD_DAI_HALIGN_MASK                            0x1
#घोषणा MOD_DAI_HALIGN_MASK_SFT                        (0x1 << 4)
#घोषणा MOD_DAI_HD_MODE_SFT                            0
#घोषणा MOD_DAI_HD_MODE_MASK                           0x3
#घोषणा MOD_DAI_HD_MODE_MASK_SFT                       (0x3 << 0)

/* AFE_DAI2_CON0 */
#घोषणा DAI2_MODE_SFT                                  24
#घोषणा DAI2_MODE_MASK                                 0xf
#घोषणा DAI2_MODE_MASK_SFT                             (0xf << 24)
#घोषणा DAI2_SW_CLEAR_BUF_FULL_SFT                     15
#घोषणा DAI2_SW_CLEAR_BUF_FULL_MASK                    0x1
#घोषणा DAI2_SW_CLEAR_BUF_FULL_MASK_SFT                (0x1 << 15)
#घोषणा DAI2_DUPLICATE_WR_SFT                          10
#घोषणा DAI2_DUPLICATE_WR_MASK                         0x1
#घोषणा DAI2_DUPLICATE_WR_MASK_SFT                     (0x1 << 10)
#घोषणा DAI2_MONO_SFT                                  8
#घोषणा DAI2_MONO_MASK                                 0x1
#घोषणा DAI2_MONO_MASK_SFT                             (0x1 << 8)
#घोषणा DAI2_WR_SIGN_SFT                               6
#घोषणा DAI2_WR_SIGN_MASK                              0x1
#घोषणा DAI2_WR_SIGN_MASK_SFT                          (0x1 << 6)
#घोषणा DAI2_NORMAL_MODE_SFT                           5
#घोषणा DAI2_NORMAL_MODE_MASK                          0x1
#घोषणा DAI2_NORMAL_MODE_MASK_SFT                      (0x1 << 5)
#घोषणा DAI2_HALIGN_SFT                                4
#घोषणा DAI2_HALIGN_MASK                               0x1
#घोषणा DAI2_HALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा DAI2_HD_MODE_SFT                               0
#घोषणा DAI2_HD_MODE_MASK                              0x3
#घोषणा DAI2_HD_MODE_MASK_SFT                          (0x3 << 0)

/* AFE_MEMIF_CON0 */
#घोषणा CPU_COMPACT_MODE_SFT                           2
#घोषणा CPU_COMPACT_MODE_MASK                          0x1
#घोषणा CPU_COMPACT_MODE_MASK_SFT                      (0x1 << 2)
#घोषणा CPU_HD_ALIGN_SFT                               1
#घोषणा CPU_HD_ALIGN_MASK                              0x1
#घोषणा CPU_HD_ALIGN_MASK_SFT                          (0x1 << 1)
#घोषणा SYSRAM_SIGN_SFT                                0
#घोषणा SYSRAM_SIGN_MASK                               0x1
#घोषणा SYSRAM_SIGN_MASK_SFT                           (0x1 << 0)

/* AFE_HDMI_OUT_CON0 */
#घोषणा HDMI_CH_NUM_SFT                                24
#घोषणा HDMI_CH_NUM_MASK                               0xf
#घोषणा HDMI_CH_NUM_MASK_SFT                           (0xf << 24)
#घोषणा HDMI_OUT_MINLEN_SFT                            20
#घोषणा HDMI_OUT_MINLEN_MASK                           0xf
#घोषणा HDMI_OUT_MINLEN_MASK_SFT                       (0xf << 20)
#घोषणा HDMI_OUT_MAXLEN_SFT                            16
#घोषणा HDMI_OUT_MAXLEN_MASK                           0xf
#घोषणा HDMI_OUT_MAXLEN_MASK_SFT                       (0xf << 16)
#घोषणा HDMI_OUT_SW_CLEAR_BUF_EMPTY_SFT                15
#घोषणा HDMI_OUT_SW_CLEAR_BUF_EMPTY_MASK               0x1
#घोषणा HDMI_OUT_SW_CLEAR_BUF_EMPTY_MASK_SFT           (0x1 << 15)
#घोषणा HDMI_OUT_PBUF_SIZE_SFT                         12
#घोषणा HDMI_OUT_PBUF_SIZE_MASK                        0x3
#घोषणा HDMI_OUT_PBUF_SIZE_MASK_SFT                    (0x3 << 12)
#घोषणा HDMI_OUT_NORMAL_MODE_SFT                       5
#घोषणा HDMI_OUT_NORMAL_MODE_MASK                      0x1
#घोषणा HDMI_OUT_NORMAL_MODE_MASK_SFT                  (0x1 << 5)
#घोषणा HDMI_OUT_HALIGN_SFT                            4
#घोषणा HDMI_OUT_HALIGN_MASK                           0x1
#घोषणा HDMI_OUT_HALIGN_MASK_SFT                       (0x1 << 4)
#घोषणा HDMI_OUT_HD_MODE_SFT                           0
#घोषणा HDMI_OUT_HD_MODE_MASK                          0x3
#घोषणा HDMI_OUT_HD_MODE_MASK_SFT                      (0x3 << 0)

/* AFE_IRQ_MCU_CON0 */
#घोषणा IRQ31_MCU_ON_SFT                               31
#घोषणा IRQ31_MCU_ON_MASK                              0x1
#घोषणा IRQ31_MCU_ON_MASK_SFT                          (0x1 << 31)
#घोषणा IRQ26_MCU_ON_SFT                               26
#घोषणा IRQ26_MCU_ON_MASK                              0x1
#घोषणा IRQ26_MCU_ON_MASK_SFT                          (0x1 << 26)
#घोषणा IRQ25_MCU_ON_SFT                               25
#घोषणा IRQ25_MCU_ON_MASK                              0x1
#घोषणा IRQ25_MCU_ON_MASK_SFT                          (0x1 << 25)
#घोषणा IRQ24_MCU_ON_SFT                               24
#घोषणा IRQ24_MCU_ON_MASK                              0x1
#घोषणा IRQ24_MCU_ON_MASK_SFT                          (0x1 << 24)
#घोषणा IRQ23_MCU_ON_SFT                               23
#घोषणा IRQ23_MCU_ON_MASK                              0x1
#घोषणा IRQ23_MCU_ON_MASK_SFT                          (0x1 << 23)
#घोषणा IRQ22_MCU_ON_SFT                               22
#घोषणा IRQ22_MCU_ON_MASK                              0x1
#घोषणा IRQ22_MCU_ON_MASK_SFT                          (0x1 << 22)
#घोषणा IRQ21_MCU_ON_SFT                               21
#घोषणा IRQ21_MCU_ON_MASK                              0x1
#घोषणा IRQ21_MCU_ON_MASK_SFT                          (0x1 << 21)
#घोषणा IRQ20_MCU_ON_SFT                               20
#घोषणा IRQ20_MCU_ON_MASK                              0x1
#घोषणा IRQ20_MCU_ON_MASK_SFT                          (0x1 << 20)
#घोषणा IRQ19_MCU_ON_SFT                               19
#घोषणा IRQ19_MCU_ON_MASK                              0x1
#घोषणा IRQ19_MCU_ON_MASK_SFT                          (0x1 << 19)
#घोषणा IRQ18_MCU_ON_SFT                               18
#घोषणा IRQ18_MCU_ON_MASK                              0x1
#घोषणा IRQ18_MCU_ON_MASK_SFT                          (0x1 << 18)
#घोषणा IRQ17_MCU_ON_SFT                               17
#घोषणा IRQ17_MCU_ON_MASK                              0x1
#घोषणा IRQ17_MCU_ON_MASK_SFT                          (0x1 << 17)
#घोषणा IRQ16_MCU_ON_SFT                               16
#घोषणा IRQ16_MCU_ON_MASK                              0x1
#घोषणा IRQ16_MCU_ON_MASK_SFT                          (0x1 << 16)
#घोषणा IRQ15_MCU_ON_SFT                               15
#घोषणा IRQ15_MCU_ON_MASK                              0x1
#घोषणा IRQ15_MCU_ON_MASK_SFT                          (0x1 << 15)
#घोषणा IRQ14_MCU_ON_SFT                               14
#घोषणा IRQ14_MCU_ON_MASK                              0x1
#घोषणा IRQ14_MCU_ON_MASK_SFT                          (0x1 << 14)
#घोषणा IRQ13_MCU_ON_SFT                               13
#घोषणा IRQ13_MCU_ON_MASK                              0x1
#घोषणा IRQ13_MCU_ON_MASK_SFT                          (0x1 << 13)
#घोषणा IRQ12_MCU_ON_SFT                               12
#घोषणा IRQ12_MCU_ON_MASK                              0x1
#घोषणा IRQ12_MCU_ON_MASK_SFT                          (0x1 << 12)
#घोषणा IRQ11_MCU_ON_SFT                               11
#घोषणा IRQ11_MCU_ON_MASK                              0x1
#घोषणा IRQ11_MCU_ON_MASK_SFT                          (0x1 << 11)
#घोषणा IRQ10_MCU_ON_SFT                               10
#घोषणा IRQ10_MCU_ON_MASK                              0x1
#घोषणा IRQ10_MCU_ON_MASK_SFT                          (0x1 << 10)
#घोषणा IRQ9_MCU_ON_SFT                                9
#घोषणा IRQ9_MCU_ON_MASK                               0x1
#घोषणा IRQ9_MCU_ON_MASK_SFT                           (0x1 << 9)
#घोषणा IRQ8_MCU_ON_SFT                                8
#घोषणा IRQ8_MCU_ON_MASK                               0x1
#घोषणा IRQ8_MCU_ON_MASK_SFT                           (0x1 << 8)
#घोषणा IRQ7_MCU_ON_SFT                                7
#घोषणा IRQ7_MCU_ON_MASK                               0x1
#घोषणा IRQ7_MCU_ON_MASK_SFT                           (0x1 << 7)
#घोषणा IRQ6_MCU_ON_SFT                                6
#घोषणा IRQ6_MCU_ON_MASK                               0x1
#घोषणा IRQ6_MCU_ON_MASK_SFT                           (0x1 << 6)
#घोषणा IRQ5_MCU_ON_SFT                                5
#घोषणा IRQ5_MCU_ON_MASK                               0x1
#घोषणा IRQ5_MCU_ON_MASK_SFT                           (0x1 << 5)
#घोषणा IRQ4_MCU_ON_SFT                                4
#घोषणा IRQ4_MCU_ON_MASK                               0x1
#घोषणा IRQ4_MCU_ON_MASK_SFT                           (0x1 << 4)
#घोषणा IRQ3_MCU_ON_SFT                                3
#घोषणा IRQ3_MCU_ON_MASK                               0x1
#घोषणा IRQ3_MCU_ON_MASK_SFT                           (0x1 << 3)
#घोषणा IRQ2_MCU_ON_SFT                                2
#घोषणा IRQ2_MCU_ON_MASK                               0x1
#घोषणा IRQ2_MCU_ON_MASK_SFT                           (0x1 << 2)
#घोषणा IRQ1_MCU_ON_SFT                                1
#घोषणा IRQ1_MCU_ON_MASK                               0x1
#घोषणा IRQ1_MCU_ON_MASK_SFT                           (0x1 << 1)
#घोषणा IRQ0_MCU_ON_SFT                                0
#घोषणा IRQ0_MCU_ON_MASK                               0x1
#घोषणा IRQ0_MCU_ON_MASK_SFT                           (0x1 << 0)

/* AFE_IRQ_MCU_CON1 */
#घोषणा IRQ7_MCU_MODE_SFT                              28
#घोषणा IRQ7_MCU_MODE_MASK                             0xf
#घोषणा IRQ7_MCU_MODE_MASK_SFT                         (0xf << 28)
#घोषणा IRQ6_MCU_MODE_SFT                              24
#घोषणा IRQ6_MCU_MODE_MASK                             0xf
#घोषणा IRQ6_MCU_MODE_MASK_SFT                         (0xf << 24)
#घोषणा IRQ5_MCU_MODE_SFT                              20
#घोषणा IRQ5_MCU_MODE_MASK                             0xf
#घोषणा IRQ5_MCU_MODE_MASK_SFT                         (0xf << 20)
#घोषणा IRQ4_MCU_MODE_SFT                              16
#घोषणा IRQ4_MCU_MODE_MASK                             0xf
#घोषणा IRQ4_MCU_MODE_MASK_SFT                         (0xf << 16)
#घोषणा IRQ3_MCU_MODE_SFT                              12
#घोषणा IRQ3_MCU_MODE_MASK                             0xf
#घोषणा IRQ3_MCU_MODE_MASK_SFT                         (0xf << 12)
#घोषणा IRQ2_MCU_MODE_SFT                              8
#घोषणा IRQ2_MCU_MODE_MASK                             0xf
#घोषणा IRQ2_MCU_MODE_MASK_SFT                         (0xf << 8)
#घोषणा IRQ1_MCU_MODE_SFT                              4
#घोषणा IRQ1_MCU_MODE_MASK                             0xf
#घोषणा IRQ1_MCU_MODE_MASK_SFT                         (0xf << 4)
#घोषणा IRQ0_MCU_MODE_SFT                              0
#घोषणा IRQ0_MCU_MODE_MASK                             0xf
#घोषणा IRQ0_MCU_MODE_MASK_SFT                         (0xf << 0)

/* AFE_IRQ_MCU_CON2 */
#घोषणा IRQ15_MCU_MODE_SFT                             28
#घोषणा IRQ15_MCU_MODE_MASK                            0xf
#घोषणा IRQ15_MCU_MODE_MASK_SFT                        (0xf << 28)
#घोषणा IRQ14_MCU_MODE_SFT                             24
#घोषणा IRQ14_MCU_MODE_MASK                            0xf
#घोषणा IRQ14_MCU_MODE_MASK_SFT                        (0xf << 24)
#घोषणा IRQ13_MCU_MODE_SFT                             20
#घोषणा IRQ13_MCU_MODE_MASK                            0xf
#घोषणा IRQ13_MCU_MODE_MASK_SFT                        (0xf << 20)
#घोषणा IRQ12_MCU_MODE_SFT                             16
#घोषणा IRQ12_MCU_MODE_MASK                            0xf
#घोषणा IRQ12_MCU_MODE_MASK_SFT                        (0xf << 16)
#घोषणा IRQ11_MCU_MODE_SFT                             12
#घोषणा IRQ11_MCU_MODE_MASK                            0xf
#घोषणा IRQ11_MCU_MODE_MASK_SFT                        (0xf << 12)
#घोषणा IRQ10_MCU_MODE_SFT                             8
#घोषणा IRQ10_MCU_MODE_MASK                            0xf
#घोषणा IRQ10_MCU_MODE_MASK_SFT                        (0xf << 8)
#घोषणा IRQ9_MCU_MODE_SFT                              4
#घोषणा IRQ9_MCU_MODE_MASK                             0xf
#घोषणा IRQ9_MCU_MODE_MASK_SFT                         (0xf << 4)
#घोषणा IRQ8_MCU_MODE_SFT                              0
#घोषणा IRQ8_MCU_MODE_MASK                             0xf
#घोषणा IRQ8_MCU_MODE_MASK_SFT                         (0xf << 0)

/* AFE_IRQ_MCU_CON3 */
#घोषणा IRQ23_MCU_MODE_SFT                             28
#घोषणा IRQ23_MCU_MODE_MASK                            0xf
#घोषणा IRQ23_MCU_MODE_MASK_SFT                        (0xf << 28)
#घोषणा IRQ22_MCU_MODE_SFT                             24
#घोषणा IRQ22_MCU_MODE_MASK                            0xf
#घोषणा IRQ22_MCU_MODE_MASK_SFT                        (0xf << 24)
#घोषणा IRQ21_MCU_MODE_SFT                             20
#घोषणा IRQ21_MCU_MODE_MASK                            0xf
#घोषणा IRQ21_MCU_MODE_MASK_SFT                        (0xf << 20)
#घोषणा IRQ20_MCU_MODE_SFT                             16
#घोषणा IRQ20_MCU_MODE_MASK                            0xf
#घोषणा IRQ20_MCU_MODE_MASK_SFT                        (0xf << 16)
#घोषणा IRQ19_MCU_MODE_SFT                             12
#घोषणा IRQ19_MCU_MODE_MASK                            0xf
#घोषणा IRQ19_MCU_MODE_MASK_SFT                        (0xf << 12)
#घोषणा IRQ18_MCU_MODE_SFT                             8
#घोषणा IRQ18_MCU_MODE_MASK                            0xf
#घोषणा IRQ18_MCU_MODE_MASK_SFT                        (0xf << 8)
#घोषणा IRQ17_MCU_MODE_SFT                             4
#घोषणा IRQ17_MCU_MODE_MASK                            0xf
#घोषणा IRQ17_MCU_MODE_MASK_SFT                        (0xf << 4)
#घोषणा IRQ16_MCU_MODE_SFT                             0
#घोषणा IRQ16_MCU_MODE_MASK                            0xf
#घोषणा IRQ16_MCU_MODE_MASK_SFT                        (0xf << 0)

/* AFE_IRQ_MCU_CON4 */
#घोषणा IRQ26_MCU_MODE_SFT                             8
#घोषणा IRQ26_MCU_MODE_MASK                            0xf
#घोषणा IRQ26_MCU_MODE_MASK_SFT                        (0xf << 8)
#घोषणा IRQ25_MCU_MODE_SFT                             4
#घोषणा IRQ25_MCU_MODE_MASK                            0xf
#घोषणा IRQ25_MCU_MODE_MASK_SFT                        (0xf << 4)
#घोषणा IRQ24_MCU_MODE_SFT                             0
#घोषणा IRQ24_MCU_MODE_MASK                            0xf
#घोषणा IRQ24_MCU_MODE_MASK_SFT                        (0xf << 0)

/* AFE_IRQ_MCU_CLR */
#घोषणा IRQ31_MCU_CLR_SFT                              31
#घोषणा IRQ31_MCU_CLR_MASK                             0x1
#घोषणा IRQ31_MCU_CLR_MASK_SFT                         (0x1 << 31)
#घोषणा IRQ26_MCU_CLR_SFT                              26
#घोषणा IRQ26_MCU_CLR_MASK                             0x1
#घोषणा IRQ26_MCU_CLR_MASK_SFT                         (0x1 << 26)
#घोषणा IRQ25_MCU_CLR_SFT                              25
#घोषणा IRQ25_MCU_CLR_MASK                             0x1
#घोषणा IRQ25_MCU_CLR_MASK_SFT                         (0x1 << 25)
#घोषणा IRQ24_MCU_CLR_SFT                              24
#घोषणा IRQ24_MCU_CLR_MASK                             0x1
#घोषणा IRQ24_MCU_CLR_MASK_SFT                         (0x1 << 24)
#घोषणा IRQ23_MCU_CLR_SFT                              23
#घोषणा IRQ23_MCU_CLR_MASK                             0x1
#घोषणा IRQ23_MCU_CLR_MASK_SFT                         (0x1 << 23)
#घोषणा IRQ22_MCU_CLR_SFT                              22
#घोषणा IRQ22_MCU_CLR_MASK                             0x1
#घोषणा IRQ22_MCU_CLR_MASK_SFT                         (0x1 << 22)
#घोषणा IRQ21_MCU_CLR_SFT                              21
#घोषणा IRQ21_MCU_CLR_MASK                             0x1
#घोषणा IRQ21_MCU_CLR_MASK_SFT                         (0x1 << 21)
#घोषणा IRQ20_MCU_CLR_SFT                              20
#घोषणा IRQ20_MCU_CLR_MASK                             0x1
#घोषणा IRQ20_MCU_CLR_MASK_SFT                         (0x1 << 20)
#घोषणा IRQ19_MCU_CLR_SFT                              19
#घोषणा IRQ19_MCU_CLR_MASK                             0x1
#घोषणा IRQ19_MCU_CLR_MASK_SFT                         (0x1 << 19)
#घोषणा IRQ18_MCU_CLR_SFT                              18
#घोषणा IRQ18_MCU_CLR_MASK                             0x1
#घोषणा IRQ18_MCU_CLR_MASK_SFT                         (0x1 << 18)
#घोषणा IRQ17_MCU_CLR_SFT                              17
#घोषणा IRQ17_MCU_CLR_MASK                             0x1
#घोषणा IRQ17_MCU_CLR_MASK_SFT                         (0x1 << 17)
#घोषणा IRQ16_MCU_CLR_SFT                              16
#घोषणा IRQ16_MCU_CLR_MASK                             0x1
#घोषणा IRQ16_MCU_CLR_MASK_SFT                         (0x1 << 16)
#घोषणा IRQ15_MCU_CLR_SFT                              15
#घोषणा IRQ15_MCU_CLR_MASK                             0x1
#घोषणा IRQ15_MCU_CLR_MASK_SFT                         (0x1 << 15)
#घोषणा IRQ14_MCU_CLR_SFT                              14
#घोषणा IRQ14_MCU_CLR_MASK                             0x1
#घोषणा IRQ14_MCU_CLR_MASK_SFT                         (0x1 << 14)
#घोषणा IRQ13_MCU_CLR_SFT                              13
#घोषणा IRQ13_MCU_CLR_MASK                             0x1
#घोषणा IRQ13_MCU_CLR_MASK_SFT                         (0x1 << 13)
#घोषणा IRQ12_MCU_CLR_SFT                              12
#घोषणा IRQ12_MCU_CLR_MASK                             0x1
#घोषणा IRQ12_MCU_CLR_MASK_SFT                         (0x1 << 12)
#घोषणा IRQ11_MCU_CLR_SFT                              11
#घोषणा IRQ11_MCU_CLR_MASK                             0x1
#घोषणा IRQ11_MCU_CLR_MASK_SFT                         (0x1 << 11)
#घोषणा IRQ10_MCU_CLR_SFT                              10
#घोषणा IRQ10_MCU_CLR_MASK                             0x1
#घोषणा IRQ10_MCU_CLR_MASK_SFT                         (0x1 << 10)
#घोषणा IRQ9_MCU_CLR_SFT                               9
#घोषणा IRQ9_MCU_CLR_MASK                              0x1
#घोषणा IRQ9_MCU_CLR_MASK_SFT                          (0x1 << 9)
#घोषणा IRQ8_MCU_CLR_SFT                               8
#घोषणा IRQ8_MCU_CLR_MASK                              0x1
#घोषणा IRQ8_MCU_CLR_MASK_SFT                          (0x1 << 8)
#घोषणा IRQ7_MCU_CLR_SFT                               7
#घोषणा IRQ7_MCU_CLR_MASK                              0x1
#घोषणा IRQ7_MCU_CLR_MASK_SFT                          (0x1 << 7)
#घोषणा IRQ6_MCU_CLR_SFT                               6
#घोषणा IRQ6_MCU_CLR_MASK                              0x1
#घोषणा IRQ6_MCU_CLR_MASK_SFT                          (0x1 << 6)
#घोषणा IRQ5_MCU_CLR_SFT                               5
#घोषणा IRQ5_MCU_CLR_MASK                              0x1
#घोषणा IRQ5_MCU_CLR_MASK_SFT                          (0x1 << 5)
#घोषणा IRQ4_MCU_CLR_SFT                               4
#घोषणा IRQ4_MCU_CLR_MASK                              0x1
#घोषणा IRQ4_MCU_CLR_MASK_SFT                          (0x1 << 4)
#घोषणा IRQ3_MCU_CLR_SFT                               3
#घोषणा IRQ3_MCU_CLR_MASK                              0x1
#घोषणा IRQ3_MCU_CLR_MASK_SFT                          (0x1 << 3)
#घोषणा IRQ2_MCU_CLR_SFT                               2
#घोषणा IRQ2_MCU_CLR_MASK                              0x1
#घोषणा IRQ2_MCU_CLR_MASK_SFT                          (0x1 << 2)
#घोषणा IRQ1_MCU_CLR_SFT                               1
#घोषणा IRQ1_MCU_CLR_MASK                              0x1
#घोषणा IRQ1_MCU_CLR_MASK_SFT                          (0x1 << 1)
#घोषणा IRQ0_MCU_CLR_SFT                               0
#घोषणा IRQ0_MCU_CLR_MASK                              0x1
#घोषणा IRQ0_MCU_CLR_MASK_SFT                          (0x1 << 0)

/* AFE_IRQ_MCU_EN */
#घोषणा IRQ31_MCU_EN_SFT                               31
#घोषणा IRQ30_MCU_EN_SFT                               30
#घोषणा IRQ29_MCU_EN_SFT                               29
#घोषणा IRQ28_MCU_EN_SFT                               28
#घोषणा IRQ27_MCU_EN_SFT                               27
#घोषणा IRQ26_MCU_EN_SFT                               26
#घोषणा IRQ25_MCU_EN_SFT                               25
#घोषणा IRQ24_MCU_EN_SFT                               24
#घोषणा IRQ23_MCU_EN_SFT                               23
#घोषणा IRQ22_MCU_EN_SFT                               22
#घोषणा IRQ21_MCU_EN_SFT                               21
#घोषणा IRQ20_MCU_EN_SFT                               20
#घोषणा IRQ19_MCU_EN_SFT                               19
#घोषणा IRQ18_MCU_EN_SFT                               18
#घोषणा IRQ17_MCU_EN_SFT                               17
#घोषणा IRQ16_MCU_EN_SFT                               16
#घोषणा IRQ15_MCU_EN_SFT                               15
#घोषणा IRQ14_MCU_EN_SFT                               14
#घोषणा IRQ13_MCU_EN_SFT                               13
#घोषणा IRQ12_MCU_EN_SFT                               12
#घोषणा IRQ11_MCU_EN_SFT                               11
#घोषणा IRQ10_MCU_EN_SFT                               10
#घोषणा IRQ9_MCU_EN_SFT                                9
#घोषणा IRQ8_MCU_EN_SFT                                8
#घोषणा IRQ7_MCU_EN_SFT                                7
#घोषणा IRQ6_MCU_EN_SFT                                6
#घोषणा IRQ5_MCU_EN_SFT                                5
#घोषणा IRQ4_MCU_EN_SFT                                4
#घोषणा IRQ3_MCU_EN_SFT                                3
#घोषणा IRQ2_MCU_EN_SFT                                2
#घोषणा IRQ1_MCU_EN_SFT                                1
#घोषणा IRQ0_MCU_EN_SFT                                0

/* AFE_IRQ_MCU_SCP_EN */
#घोषणा IRQ31_MCU_SCP_EN_SFT                           31
#घोषणा IRQ30_MCU_SCP_EN_SFT                           30
#घोषणा IRQ29_MCU_SCP_EN_SFT                           29
#घोषणा IRQ28_MCU_SCP_EN_SFT                           28
#घोषणा IRQ27_MCU_SCP_EN_SFT                           27
#घोषणा IRQ26_MCU_SCP_EN_SFT                           26
#घोषणा IRQ25_MCU_SCP_EN_SFT                           25
#घोषणा IRQ24_MCU_SCP_EN_SFT                           24
#घोषणा IRQ23_MCU_SCP_EN_SFT                           23
#घोषणा IRQ22_MCU_SCP_EN_SFT                           22
#घोषणा IRQ21_MCU_SCP_EN_SFT                           21
#घोषणा IRQ20_MCU_SCP_EN_SFT                           20
#घोषणा IRQ19_MCU_SCP_EN_SFT                           19
#घोषणा IRQ18_MCU_SCP_EN_SFT                           18
#घोषणा IRQ17_MCU_SCP_EN_SFT                           17
#घोषणा IRQ16_MCU_SCP_EN_SFT                           16
#घोषणा IRQ15_MCU_SCP_EN_SFT                           15
#घोषणा IRQ14_MCU_SCP_EN_SFT                           14
#घोषणा IRQ13_MCU_SCP_EN_SFT                           13
#घोषणा IRQ12_MCU_SCP_EN_SFT                           12
#घोषणा IRQ11_MCU_SCP_EN_SFT                           11
#घोषणा IRQ10_MCU_SCP_EN_SFT                           10
#घोषणा IRQ9_MCU_SCP_EN_SFT                            9
#घोषणा IRQ8_MCU_SCP_EN_SFT                            8
#घोषणा IRQ7_MCU_SCP_EN_SFT                            7
#घोषणा IRQ6_MCU_SCP_EN_SFT                            6
#घोषणा IRQ5_MCU_SCP_EN_SFT                            5
#घोषणा IRQ4_MCU_SCP_EN_SFT                            4
#घोषणा IRQ3_MCU_SCP_EN_SFT                            3
#घोषणा IRQ2_MCU_SCP_EN_SFT                            2
#घोषणा IRQ1_MCU_SCP_EN_SFT                            1
#घोषणा IRQ0_MCU_SCP_EN_SFT                            0

/* AFE_TDM_CON1 */
#घोषणा TDM_EN_SFT                                     0
#घोषणा TDM_EN_MASK                                    0x1
#घोषणा TDM_EN_MASK_SFT                                (0x1 << 0)
#घोषणा LRCK_INVERSE_SFT                               2
#घोषणा LRCK_INVERSE_MASK                              0x1
#घोषणा LRCK_INVERSE_MASK_SFT                          (0x1 << 2)
#घोषणा DELAY_DATA_SFT                                 3
#घोषणा DELAY_DATA_MASK                                0x1
#घोषणा DELAY_DATA_MASK_SFT                            (0x1 << 3)
#घोषणा LEFT_ALIGN_SFT                                 4
#घोषणा LEFT_ALIGN_MASK                                0x1
#घोषणा LEFT_ALIGN_MASK_SFT                            (0x1 << 4)
#घोषणा WLEN_SFT                                       8
#घोषणा WLEN_MASK                                      0x3
#घोषणा WLEN_MASK_SFT                                  (0x3 << 8)
#घोषणा CHANNEL_NUM_SFT                                10
#घोषणा CHANNEL_NUM_MASK                               0x3
#घोषणा CHANNEL_NUM_MASK_SFT                           (0x3 << 10)
#घोषणा CHANNEL_BCK_CYCLES_SFT                         12
#घोषणा CHANNEL_BCK_CYCLES_MASK                        0x3
#घोषणा CHANNEL_BCK_CYCLES_MASK_SFT                    (0x3 << 12)
#घोषणा DAC_BIT_NUM_SFT                                16
#घोषणा DAC_BIT_NUM_MASK                               0x1f
#घोषणा DAC_BIT_NUM_MASK_SFT                           (0x1f << 16)
#घोषणा LRCK_TDM_WIDTH_SFT                             24
#घोषणा LRCK_TDM_WIDTH_MASK                            0xff
#घोषणा LRCK_TDM_WIDTH_MASK_SFT                        (0xff << 24)

/* AFE_TDM_CON2 */
#घोषणा ST_CH_PAIR_SOUT0_SFT                           0
#घोषणा ST_CH_PAIR_SOUT0_MASK                          0x7
#घोषणा ST_CH_PAIR_SOUT0_MASK_SFT                      (0x7 << 0)
#घोषणा ST_CH_PAIR_SOUT1_SFT                           4
#घोषणा ST_CH_PAIR_SOUT1_MASK                          0x7
#घोषणा ST_CH_PAIR_SOUT1_MASK_SFT                      (0x7 << 4)
#घोषणा ST_CH_PAIR_SOUT2_SFT                           8
#घोषणा ST_CH_PAIR_SOUT2_MASK                          0x7
#घोषणा ST_CH_PAIR_SOUT2_MASK_SFT                      (0x7 << 8)
#घोषणा ST_CH_PAIR_SOUT3_SFT                           12
#घोषणा ST_CH_PAIR_SOUT3_MASK                          0x7
#घोषणा ST_CH_PAIR_SOUT3_MASK_SFT                      (0x7 << 12)
#घोषणा TDM_FIX_VALUE_SEL_SFT                          16
#घोषणा TDM_FIX_VALUE_SEL_MASK                         0x1
#घोषणा TDM_FIX_VALUE_SEL_MASK_SFT                     (0x1 << 16)
#घोषणा TDM_I2S_LOOPBACK_SFT                           20
#घोषणा TDM_I2S_LOOPBACK_MASK                          0x1
#घोषणा TDM_I2S_LOOPBACK_MASK_SFT                      (0x1 << 20)
#घोषणा TDM_I2S_LOOPBACK_CH_SFT                        21
#घोषणा TDM_I2S_LOOPBACK_CH_MASK                       0x3
#घोषणा TDM_I2S_LOOPBACK_CH_MASK_SFT                   (0x3 << 21)
#घोषणा TDM_FIX_VALUE_SFT                              24
#घोषणा TDM_FIX_VALUE_MASK                             0xff
#घोषणा TDM_FIX_VALUE_MASK_SFT                         (0xff << 24)

/* AFE_HDMI_CONN0 */
#घोषणा HDMI_O_7_SFT                                   21
#घोषणा HDMI_O_7_MASK                                  0x7
#घोषणा HDMI_O_7_MASK_SFT                              (0x7 << 21)
#घोषणा HDMI_O_6_SFT                                   18
#घोषणा HDMI_O_6_MASK                                  0x7
#घोषणा HDMI_O_6_MASK_SFT                              (0x7 << 18)
#घोषणा HDMI_O_5_SFT                                   15
#घोषणा HDMI_O_5_MASK                                  0x7
#घोषणा HDMI_O_5_MASK_SFT                              (0x7 << 15)
#घोषणा HDMI_O_4_SFT                                   12
#घोषणा HDMI_O_4_MASK                                  0x7
#घोषणा HDMI_O_4_MASK_SFT                              (0x7 << 12)
#घोषणा HDMI_O_3_SFT                                   9
#घोषणा HDMI_O_3_MASK                                  0x7
#घोषणा HDMI_O_3_MASK_SFT                              (0x7 << 9)
#घोषणा HDMI_O_2_SFT                                   6
#घोषणा HDMI_O_2_MASK                                  0x7
#घोषणा HDMI_O_2_MASK_SFT                              (0x7 << 6)
#घोषणा HDMI_O_1_SFT                                   3
#घोषणा HDMI_O_1_MASK                                  0x7
#घोषणा HDMI_O_1_MASK_SFT                              (0x7 << 3)
#घोषणा HDMI_O_0_SFT                                   0
#घोषणा HDMI_O_0_MASK                                  0x7
#घोषणा HDMI_O_0_MASK_SFT                              (0x7 << 0)

/* AFE_AUD_PAD_TOP */
#घोषणा AUD_PAD_TOP_MON_SFT                            15
#घोषणा AUD_PAD_TOP_MON_MASK                           0x1ffff
#घोषणा AUD_PAD_TOP_MON_MASK_SFT                       (0x1ffff << 15)
#घोषणा AUD_PAD_TOP_FIFO_RSP_SFT                       4
#घोषणा AUD_PAD_TOP_FIFO_RSP_MASK                      0xf
#घोषणा AUD_PAD_TOP_FIFO_RSP_MASK_SFT                  (0xf << 4)
#घोषणा RG_RX_PROTOCOL2_SFT                            3
#घोषणा RG_RX_PROTOCOL2_MASK                           0x1
#घोषणा RG_RX_PROTOCOL2_MASK_SFT                       (0x1 << 3)
#घोषणा RESERVDED_01_SFT                               1
#घोषणा RESERVDED_01_MASK                              0x3
#घोषणा RESERVDED_01_MASK_SFT                          (0x3 << 1)
#घोषणा RG_RX_FIFO_ON_SFT                              0
#घोषणा RG_RX_FIFO_ON_MASK                             0x1
#घोषणा RG_RX_FIFO_ON_MASK_SFT                         (0x1 << 0)

/* AFE_ADDA_MTKAIF_SYNCWORD_CFG */
#घोषणा RG_ADDA6_MTKAIF_RX_SYNC_WORD2_DISABLE_SFT      23
#घोषणा RG_ADDA6_MTKAIF_RX_SYNC_WORD2_DISABLE_MASK     0x1
#घोषणा RG_ADDA6_MTKAIF_RX_SYNC_WORD2_DISABLE_MASK_SFT (0x1 << 23)

/* AFE_ADDA_MTKAIF_RX_CFG0 */
#घोषणा MTKAIF_RXIF_VOICE_MODE_SFT                     20
#घोषणा MTKAIF_RXIF_VOICE_MODE_MASK                    0xf
#घोषणा MTKAIF_RXIF_VOICE_MODE_MASK_SFT                (0xf << 20)
#घोषणा MTKAIF_RXIF_DETECT_ON_SFT                      16
#घोषणा MTKAIF_RXIF_DETECT_ON_MASK                     0x1
#घोषणा MTKAIF_RXIF_DETECT_ON_MASK_SFT                 (0x1 << 16)
#घोषणा MTKAIF_RXIF_DATA_BIT_SFT                       8
#घोषणा MTKAIF_RXIF_DATA_BIT_MASK                      0x7
#घोषणा MTKAIF_RXIF_DATA_BIT_MASK_SFT                  (0x7 << 8)
#घोषणा MTKAIF_RXIF_FIFO_RSP_SFT                       4
#घोषणा MTKAIF_RXIF_FIFO_RSP_MASK                      0x7
#घोषणा MTKAIF_RXIF_FIFO_RSP_MASK_SFT                  (0x7 << 4)
#घोषणा MTKAIF_RXIF_DATA_MODE_SFT                      0
#घोषणा MTKAIF_RXIF_DATA_MODE_MASK                     0x1
#घोषणा MTKAIF_RXIF_DATA_MODE_MASK_SFT                 (0x1 << 0)

/* GENERAL_ASRC_MODE */
#घोषणा GENERAL2_ASRCOUT_MODE_SFT                      12
#घोषणा GENERAL2_ASRCOUT_MODE_MASK                     0xf
#घोषणा GENERAL2_ASRCOUT_MODE_MASK_SFT                 (0xf << 12)
#घोषणा GENERAL2_ASRCIN_MODE_SFT                       8
#घोषणा GENERAL2_ASRCIN_MODE_MASK                      0xf
#घोषणा GENERAL2_ASRCIN_MODE_MASK_SFT                  (0xf << 8)
#घोषणा GENERAL1_ASRCOUT_MODE_SFT                      4
#घोषणा GENERAL1_ASRCOUT_MODE_MASK                     0xf
#घोषणा GENERAL1_ASRCOUT_MODE_MASK_SFT                 (0xf << 4)
#घोषणा GENERAL1_ASRCIN_MODE_SFT                       0
#घोषणा GENERAL1_ASRCIN_MODE_MASK                      0xf
#घोषणा GENERAL1_ASRCIN_MODE_MASK_SFT                  (0xf << 0)

/* GENERAL_ASRC_EN_ON */
#घोषणा GENERAL2_ASRC_EN_ON_SFT                        1
#घोषणा GENERAL2_ASRC_EN_ON_MASK                       0x1
#घोषणा GENERAL2_ASRC_EN_ON_MASK_SFT                   (0x1 << 1)
#घोषणा GENERAL1_ASRC_EN_ON_SFT                        0
#घोषणा GENERAL1_ASRC_EN_ON_MASK                       0x1
#घोषणा GENERAL1_ASRC_EN_ON_MASK_SFT                   (0x1 << 0)

/* AFE_GENERAL1_ASRC_2CH_CON0 */
#घोषणा G_SRC_CHSET_STR_CLR_SFT                        4
#घोषणा G_SRC_CHSET_STR_CLR_MASK                       0x1
#घोषणा G_SRC_CHSET_STR_CLR_MASK_SFT                   (0x1 << 4)
#घोषणा G_SRC_CHSET_ON_SFT                             2
#घोषणा G_SRC_CHSET_ON_MASK                            0x1
#घोषणा G_SRC_CHSET_ON_MASK_SFT                        (0x1 << 2)
#घोषणा G_SRC_COEFF_SRAM_CTRL_SFT                      1
#घोषणा G_SRC_COEFF_SRAM_CTRL_MASK                     0x1
#घोषणा G_SRC_COEFF_SRAM_CTRL_MASK_SFT                 (0x1 << 1)
#घोषणा G_SRC_ASM_ON_SFT                               0
#घोषणा G_SRC_ASM_ON_MASK                              0x1
#घोषणा G_SRC_ASM_ON_MASK_SFT                          (0x1 << 0)

/* AFE_GENERAL1_ASRC_2CH_CON3 */
#घोषणा G_SRC_ASM_FREQ_4_SFT                           0
#घोषणा G_SRC_ASM_FREQ_4_MASK                          0xffffff
#घोषणा G_SRC_ASM_FREQ_4_MASK_SFT                      (0xffffff << 0)

/* AFE_GENERAL1_ASRC_2CH_CON4 */
#घोषणा G_SRC_ASM_FREQ_5_SFT                           0
#घोषणा G_SRC_ASM_FREQ_5_MASK                          0xffffff
#घोषणा G_SRC_ASM_FREQ_5_MASK_SFT                      (0xffffff << 0)

/* AFE_GENERAL1_ASRC_2CH_CON13 */
#घोषणा G_SRC_COEFF_SRAM_ADR_SFT                       0
#घोषणा G_SRC_COEFF_SRAM_ADR_MASK                      0x3f
#घोषणा G_SRC_COEFF_SRAM_ADR_MASK_SFT                  (0x3f << 0)

/* AFE_GENERAL1_ASRC_2CH_CON2 */
#घोषणा G_SRC_CHSET_O16BIT_SFT                         19
#घोषणा G_SRC_CHSET_O16BIT_MASK                        0x1
#घोषणा G_SRC_CHSET_O16BIT_MASK_SFT                    (0x1 << 19)
#घोषणा G_SRC_CHSET_CLR_IIR_HISTORY_SFT                17
#घोषणा G_SRC_CHSET_CLR_IIR_HISTORY_MASK               0x1
#घोषणा G_SRC_CHSET_CLR_IIR_HISTORY_MASK_SFT           (0x1 << 17)
#घोषणा G_SRC_CHSET_IS_MONO_SFT                        16
#घोषणा G_SRC_CHSET_IS_MONO_MASK                       0x1
#घोषणा G_SRC_CHSET_IS_MONO_MASK_SFT                   (0x1 << 16)
#घोषणा G_SRC_CHSET_IIR_EN_SFT                         11
#घोषणा G_SRC_CHSET_IIR_EN_MASK                        0x1
#घोषणा G_SRC_CHSET_IIR_EN_MASK_SFT                    (0x1 << 11)
#घोषणा G_SRC_CHSET_IIR_STAGE_SFT                      8
#घोषणा G_SRC_CHSET_IIR_STAGE_MASK                     0x7
#घोषणा G_SRC_CHSET_IIR_STAGE_MASK_SFT                 (0x7 << 8)
#घोषणा G_SRC_CHSET_STR_CLR_RU_SFT                     5
#घोषणा G_SRC_CHSET_STR_CLR_RU_MASK                    0x1
#घोषणा G_SRC_CHSET_STR_CLR_RU_MASK_SFT                (0x1 << 5)
#घोषणा G_SRC_CHSET_ON_SFT                             2
#घोषणा G_SRC_CHSET_ON_MASK                            0x1
#घोषणा G_SRC_CHSET_ON_MASK_SFT                        (0x1 << 2)
#घोषणा G_SRC_COEFF_SRAM_CTRL_SFT                      1
#घोषणा G_SRC_COEFF_SRAM_CTRL_MASK                     0x1
#घोषणा G_SRC_COEFF_SRAM_CTRL_MASK_SFT                 (0x1 << 1)
#घोषणा G_SRC_ASM_ON_SFT                               0
#घोषणा G_SRC_ASM_ON_MASK                              0x1
#घोषणा G_SRC_ASM_ON_MASK_SFT                          (0x1 << 0)

/* AFE_ADDA_DL_SDM_AUTO_RESET_CON */
#घोषणा ADDA_SDM_AUTO_RESET_ONOFF_SFT                  31
#घोषणा ADDA_SDM_AUTO_RESET_ONOFF_MASK                 0x1
#घोषणा ADDA_SDM_AUTO_RESET_ONOFF_MASK_SFT             (0x1 << 31)

/* AFE_ADDA_3RD_DAC_DL_SDM_AUTO_RESET_CON */
#घोषणा ADDA_3RD_DAC_SDM_AUTO_RESET_ONOFF_SFT          31
#घोषणा ADDA_3RD_DAC_SDM_AUTO_RESET_ONOFF_MASK         0x1
#घोषणा ADDA_3RD_DAC_SDM_AUTO_RESET_ONOFF_MASK_SFT     (0x1 << 31)

/* AFE_TINY_CONN0 */
#घोषणा O_3_CFG_SFT                                    24
#घोषणा O_3_CFG_MASK                                   0x1f
#घोषणा O_3_CFG_MASK_SFT                               (0x1f << 24)
#घोषणा O_2_CFG_SFT                                    16
#घोषणा O_2_CFG_MASK                                   0x1f
#घोषणा O_2_CFG_MASK_SFT                               (0x1f << 16)
#घोषणा O_1_CFG_SFT                                    8
#घोषणा O_1_CFG_MASK                                   0x1f
#घोषणा O_1_CFG_MASK_SFT                               (0x1f << 8)
#घोषणा O_0_CFG_SFT                                    0
#घोषणा O_0_CFG_MASK                                   0x1f
#घोषणा O_0_CFG_MASK_SFT                               (0x1f << 0)

/* AFE_TINY_CONN5 */
#घोषणा O_23_CFG_SFT                                    24
#घोषणा O_23_CFG_MASK                                   0x1f
#घोषणा O_23_CFG_MASK_SFT                               (0x1f << 24)
#घोषणा O_22_CFG_SFT                                    16
#घोषणा O_22_CFG_MASK                                   0x1f
#घोषणा O_22_CFG_MASK_SFT                               (0x1f << 16)
#घोषणा O_21_CFG_SFT                                    8
#घोषणा O_21_CFG_MASK                                   0x1f
#घोषणा O_21_CFG_MASK_SFT                               (0x1f << 8)
#घोषणा O_20_CFG_SFT                                    0
#घोषणा O_20_CFG_MASK                                   0x1f
#घोषणा O_20_CFG_MASK_SFT                               (0x1f << 0)

/* AFE_MEMIF_CONN */
#घोषणा VUL6_USE_TINY_SFT                              8
#घोषणा VUL6_USE_TINY_MASK                             1
#घोषणा VUL6_USE_TINY_MASK_SFT                         (0x1 << 8)
#घोषणा VUL5_USE_TINY_SFT                              7
#घोषणा VUL5_USE_TINY_MASK                             1
#घोषणा VUL5_USE_TINY_MASK_SFT                         (0x1 << 7)
#घोषणा VUL4_USE_TINY_SFT                              6
#घोषणा VUL4_USE_TINY_MASK                             1
#घोषणा VUL4_USE_TINY_MASK_SFT                         (0x1 << 6)
#घोषणा VUL3_USE_TINY_SFT                              5
#घोषणा VUL3_USE_TINY_MASK                             1
#घोषणा VUL3_USE_TINY_MASK_SFT                         (0x1 << 5)
#घोषणा AWB2_USE_TINY_SFT                              4
#घोषणा AWB2_USE_TINY_MASK                             1
#घोषणा AWB2_USE_TINY_MASK_SFT                         (0x1 << 4)
#घोषणा AWB_USE_TINY_SFT                               3
#घोषणा AWB_USE_TINY_MASK                              1
#घोषणा AWB_USE_TINY_MASK_SFT                          (0x1 << 3)
#घोषणा VUL12_USE_TINY_SFT                             2
#घोषणा VUL12_USE_TINY_MASK                            1
#घोषणा VUL12_USE_TINY_MASK_SFT                        (0x1 << 2)
#घोषणा VUL2_USE_TINY_SFT                              1
#घोषणा VUL2_USE_TINY_MASK                             1
#घोषणा VUL2_USE_TINY_MASK_SFT                         (0x1 << 1)
#घोषणा VUL1_USE_TINY_SFT                              0
#घोषणा VUL1_USE_TINY_MASK                             1
#घोषणा VUL1_USE_TINY_MASK_SFT                         (0x1 << 0)

/* AFE_ASRC_2CH_CON0 */
#घोषणा CON0_CHSET_STR_CLR_SFT                         4
#घोषणा CON0_CHSET_STR_CLR_MASK                        1
#घोषणा CON0_CHSET_STR_CLR_MASK_SFT                    (0x1 << 4)
#घोषणा CON0_ASM_ON_SFT                                0
#घोषणा CON0_ASM_ON_MASK                               1
#घोषणा CON0_ASM_ON_MASK_SFT                           (0x1 << 0)

/* AFE_ASRC_2CH_CON5 */
#घोषणा CALI_EN_SFT                                    0
#घोषणा CALI_EN_MASK                                   1
#घोषणा CALI_EN_MASK_SFT                               (0x1 << 0)

#घोषणा AUDIO_TOP_CON0                                 0x0000
#घोषणा AUDIO_TOP_CON1                                 0x0004
#घोषणा AUDIO_TOP_CON2                                 0x0008
#घोषणा AUDIO_TOP_CON3                                 0x000c
#घोषणा AFE_DAC_CON0                                   0x0010
#घोषणा AFE_I2S_CON                                    0x0018
#घोषणा AFE_CONN0                                      0x0020
#घोषणा AFE_CONN1                                      0x0024
#घोषणा AFE_CONN2                                      0x0028
#घोषणा AFE_CONN3                                      0x002c
#घोषणा AFE_CONN4                                      0x0030
#घोषणा AFE_I2S_CON1                                   0x0034
#घोषणा AFE_I2S_CON2                                   0x0038
#घोषणा AFE_I2S_CON3                                   0x0040
#घोषणा AFE_CONN5                                      0x0044
#घोषणा AFE_CONN_24BIT                                 0x0048
#घोषणा AFE_DL1_CON0                                   0x004c
#घोषणा AFE_DL1_BASE_MSB                               0x0050
#घोषणा AFE_DL1_BASE                                   0x0054
#घोषणा AFE_DL1_CUR_MSB                                0x0058
#घोषणा AFE_DL1_CUR                                    0x005c
#घोषणा AFE_DL1_END_MSB                                0x0060
#घोषणा AFE_DL1_END                                    0x0064
#घोषणा AFE_DL2_CON0                                   0x0068
#घोषणा AFE_DL2_BASE_MSB                               0x006c
#घोषणा AFE_DL2_BASE                                   0x0070
#घोषणा AFE_DL2_CUR_MSB                                0x0074
#घोषणा AFE_DL2_CUR                                    0x0078
#घोषणा AFE_DL2_END_MSB                                0x007c
#घोषणा AFE_DL2_END                                    0x0080
#घोषणा AFE_DL3_CON0                                   0x0084
#घोषणा AFE_DL3_BASE_MSB                               0x0088
#घोषणा AFE_DL3_BASE                                   0x008c
#घोषणा AFE_DL3_CUR_MSB                                0x0090
#घोषणा AFE_DL3_CUR                                    0x0094
#घोषणा AFE_DL3_END_MSB                                0x0098
#घोषणा AFE_DL3_END                                    0x009c
#घोषणा AFE_CONN6                                      0x00bc
#घोषणा AFE_DL4_CON0                                   0x00cc
#घोषणा AFE_DL4_BASE_MSB                               0x00d0
#घोषणा AFE_DL4_BASE                                   0x00d4
#घोषणा AFE_DL4_CUR_MSB                                0x00d8
#घोषणा AFE_DL4_CUR                                    0x00dc
#घोषणा AFE_DL4_END_MSB                                0x00e0
#घोषणा AFE_DL4_END                                    0x00e4
#घोषणा AFE_DL12_CON0                                  0x00e8
#घोषणा AFE_DL12_BASE_MSB                              0x00ec
#घोषणा AFE_DL12_BASE                                  0x00f0
#घोषणा AFE_DL12_CUR_MSB                               0x00f4
#घोषणा AFE_DL12_CUR                                   0x00f8
#घोषणा AFE_DL12_END_MSB                               0x00fc
#घोषणा AFE_DL12_END                                   0x0100
#घोषणा AFE_ADDA_DL_SRC2_CON0                          0x0108
#घोषणा AFE_ADDA_DL_SRC2_CON1                          0x010c
#घोषणा AFE_ADDA_UL_SRC_CON0                           0x0114
#घोषणा AFE_ADDA_UL_SRC_CON1                           0x0118
#घोषणा AFE_ADDA_TOP_CON0                              0x0120
#घोषणा AFE_ADDA_UL_DL_CON0                            0x0124
#घोषणा AFE_ADDA_SRC_DEBUG                             0x012c
#घोषणा AFE_ADDA_SRC_DEBUG_MON0                        0x0130
#घोषणा AFE_ADDA_SRC_DEBUG_MON1                        0x0134
#घोषणा AFE_ADDA_UL_SRC_MON0                           0x0148
#घोषणा AFE_ADDA_UL_SRC_MON1                           0x014c
#घोषणा AFE_SECURE_CON0                                0x0150
#घोषणा AFE_SRAM_BOUND                                 0x0154
#घोषणा AFE_SECURE_CON1                                0x0158
#घोषणा AFE_SECURE_CONN0                               0x015c
#घोषणा AFE_VUL_CON0                                   0x0170
#घोषणा AFE_VUL_BASE_MSB                               0x0174
#घोषणा AFE_VUL_BASE                                   0x0178
#घोषणा AFE_VUL_CUR_MSB                                0x017c
#घोषणा AFE_VUL_CUR                                    0x0180
#घोषणा AFE_VUL_END_MSB                                0x0184
#घोषणा AFE_VUL_END                                    0x0188
#घोषणा AFE_ADDA_3RD_DAC_DL_SDM_AUTO_RESET_CON         0x018c
#घोषणा AFE_ADDA_3RD_DAC_DL_SRC2_CON0                  0x0190
#घोषणा AFE_ADDA_3RD_DAC_DL_SRC2_CON1                  0x0194
#घोषणा AFE_ADDA_3RD_DAC_PREDIS_CON0                   0x01a0
#घोषणा AFE_ADDA_3RD_DAC_PREDIS_CON1                   0x01a4
#घोषणा AFE_ADDA_3RD_DAC_PREDIS_CON2                   0x01a8
#घोषणा AFE_ADDA_3RD_DAC_PREDIS_CON3                   0x01ac
#घोषणा AFE_ADDA_3RD_DAC_DL_SDM_DCCOMP_CON             0x01b0
#घोषणा AFE_ADDA_3RD_DAC_DL_SDM_TEST                   0x01b4
#घोषणा AFE_ADDA_3RD_DAC_DL_DC_COMP_CFG0               0x01b8
#घोषणा AFE_ADDA_3RD_DAC_DL_DC_COMP_CFG1               0x01bc
#घोषणा AFE_ADDA_3RD_DAC_DL_SDM_FIFO_MON               0x01c0
#घोषणा AFE_ADDA_3RD_DAC_DL_SRC_LCH_MON                0x01c4
#घोषणा AFE_ADDA_3RD_DAC_DL_SRC_RCH_MON                0x01c8
#घोषणा AFE_ADDA_3RD_DAC_DL_SDM_OUT_MON                0x01cc
#घोषणा AFE_SIDETONE_DEBUG                             0x01d0
#घोषणा AFE_SIDETONE_MON                               0x01d4
#घोषणा AFE_ADDA_3RD_DAC_DL_SDM_DITHER_CON             0x01d8
#घोषणा AFE_SINEGEN_CON2                               0x01dc
#घोषणा AFE_SIDETONE_CON0                              0x01e0
#घोषणा AFE_SIDETONE_COEFF                             0x01e4
#घोषणा AFE_SIDETONE_CON1                              0x01e8
#घोषणा AFE_SIDETONE_GAIN                              0x01ec
#घोषणा AFE_SINEGEN_CON0                               0x01f0
#घोषणा AFE_I2S_MON2                                   0x01f8
#घोषणा AFE_SINEGEN_CON_TDM                            0x01fc
#घोषणा AFE_TOP_CON0                                   0x0200
#घोषणा AFE_VUL2_CON0                                  0x020c
#घोषणा AFE_VUL2_BASE_MSB                              0x0210
#घोषणा AFE_VUL2_BASE                                  0x0214
#घोषणा AFE_VUL2_CUR_MSB                               0x0218
#घोषणा AFE_VUL2_CUR                                   0x021c
#घोषणा AFE_VUL2_END_MSB                               0x0220
#घोषणा AFE_VUL2_END                                   0x0224
#घोषणा AFE_VUL3_CON0                                  0x0228
#घोषणा AFE_VUL3_BASE_MSB                              0x022c
#घोषणा AFE_VUL3_BASE                                  0x0230
#घोषणा AFE_VUL3_CUR_MSB                               0x0234
#घोषणा AFE_VUL3_CUR                                   0x0238
#घोषणा AFE_VUL3_END_MSB                               0x023c
#घोषणा AFE_VUL3_END                                   0x0240
#घोषणा AFE_BUSY                                       0x0244
#घोषणा AFE_BUS_CFG                                    0x0250
#घोषणा AFE_ADDA_PREDIS_CON0                           0x0260
#घोषणा AFE_ADDA_PREDIS_CON1                           0x0264
#घोषणा AFE_I2S_MON                                    0x027c
#घोषणा AFE_ADDA_IIR_COEF_02_01                        0x0290
#घोषणा AFE_ADDA_IIR_COEF_04_03                        0x0294
#घोषणा AFE_ADDA_IIR_COEF_06_05                        0x0298
#घोषणा AFE_ADDA_IIR_COEF_08_07                        0x029c
#घोषणा AFE_ADDA_IIR_COEF_10_09                        0x02a0
#घोषणा AFE_IRQ_MCU_CON1                               0x02e4
#घोषणा AFE_IRQ_MCU_CON2                               0x02e8
#घोषणा AFE_DAC_MON                                    0x02ec
#घोषणा AFE_IRQ_MCU_CON3                               0x02f0
#घोषणा AFE_IRQ_MCU_CON4                               0x02f4
#घोषणा AFE_IRQ_MCU_CNT0                               0x0300
#घोषणा AFE_IRQ_MCU_CNT6                               0x0304
#घोषणा AFE_IRQ_MCU_CNT8                               0x0308
#घोषणा AFE_IRQ_MCU_DSP2_EN                            0x030c
#घोषणा AFE_IRQ0_MCU_CNT_MON                           0x0310
#घोषणा AFE_IRQ6_MCU_CNT_MON                           0x0314
#घोषणा AFE_VUL4_CON0                                  0x0358
#घोषणा AFE_VUL4_BASE_MSB                              0x035c
#घोषणा AFE_VUL4_BASE                                  0x0360
#घोषणा AFE_VUL4_CUR_MSB                               0x0364
#घोषणा AFE_VUL4_CUR                                   0x0368
#घोषणा AFE_VUL4_END_MSB                               0x036c
#घोषणा AFE_VUL4_END                                   0x0370
#घोषणा AFE_VUL12_CON0                                 0x0374
#घोषणा AFE_VUL12_BASE_MSB                             0x0378
#घोषणा AFE_VUL12_BASE                                 0x037c
#घोषणा AFE_VUL12_CUR_MSB                              0x0380
#घोषणा AFE_VUL12_CUR                                  0x0384
#घोषणा AFE_VUL12_END_MSB                              0x0388
#घोषणा AFE_VUL12_END                                  0x038c
#घोषणा AFE_HDMI_CONN0                                 0x0390
#घोषणा AFE_IRQ3_MCU_CNT_MON                           0x0398
#घोषणा AFE_IRQ4_MCU_CNT_MON                           0x039c
#घोषणा AFE_IRQ_MCU_CON0                               0x03a0
#घोषणा AFE_IRQ_MCU_STATUS                             0x03a4
#घोषणा AFE_IRQ_MCU_CLR                                0x03a8
#घोषणा AFE_IRQ_MCU_CNT1                               0x03ac
#घोषणा AFE_IRQ_MCU_CNT2                               0x03b0
#घोषणा AFE_IRQ_MCU_EN                                 0x03b4
#घोषणा AFE_IRQ_MCU_MON2                               0x03b8
#घोषणा AFE_IRQ_MCU_CNT5                               0x03bc
#घोषणा AFE_IRQ1_MCU_CNT_MON                           0x03c0
#घोषणा AFE_IRQ2_MCU_CNT_MON                           0x03c4
#घोषणा AFE_IRQ5_MCU_CNT_MON                           0x03cc
#घोषणा AFE_IRQ_MCU_DSP_EN                             0x03d0
#घोषणा AFE_IRQ_MCU_SCP_EN                             0x03d4
#घोषणा AFE_IRQ_MCU_CNT7                               0x03dc
#घोषणा AFE_IRQ7_MCU_CNT_MON                           0x03e0
#घोषणा AFE_IRQ_MCU_CNT3                               0x03e4
#घोषणा AFE_IRQ_MCU_CNT4                               0x03e8
#घोषणा AFE_IRQ_MCU_CNT11                              0x03ec
#घोषणा AFE_APLL1_TUNER_CFG                            0x03f0
#घोषणा AFE_APLL2_TUNER_CFG                            0x03f4
#घोषणा AFE_IRQ_MCU_MISS_CLR                           0x03f8
#घोषणा AFE_CONN33                                     0x0408
#घोषणा AFE_IRQ_MCU_CNT12                              0x040c
#घोषणा AFE_GAIN1_CON0                                 0x0410
#घोषणा AFE_GAIN1_CON1                                 0x0414
#घोषणा AFE_GAIN1_CON2                                 0x0418
#घोषणा AFE_GAIN1_CON3                                 0x041c
#घोषणा AFE_CONN7                                      0x0420
#घोषणा AFE_GAIN1_CUR                                  0x0424
#घोषणा AFE_GAIN2_CON0                                 0x0428
#घोषणा AFE_GAIN2_CON1                                 0x042c
#घोषणा AFE_GAIN2_CON2                                 0x0430
#घोषणा AFE_GAIN2_CON3                                 0x0434
#घोषणा AFE_CONN8                                      0x0438
#घोषणा AFE_GAIN2_CUR                                  0x043c
#घोषणा AFE_CONN9                                      0x0440
#घोषणा AFE_CONN10                                     0x0444
#घोषणा AFE_CONN11                                     0x0448
#घोषणा AFE_CONN12                                     0x044c
#घोषणा AFE_CONN13                                     0x0450
#घोषणा AFE_CONN14                                     0x0454
#घोषणा AFE_CONN15                                     0x0458
#घोषणा AFE_CONN16                                     0x045c
#घोषणा AFE_CONN17                                     0x0460
#घोषणा AFE_CONN18                                     0x0464
#घोषणा AFE_CONN19                                     0x0468
#घोषणा AFE_CONN20                                     0x046c
#घोषणा AFE_CONN21                                     0x0470
#घोषणा AFE_CONN22                                     0x0474
#घोषणा AFE_CONN23                                     0x0478
#घोषणा AFE_CONN24                                     0x047c
#घोषणा AFE_CONN_RS                                    0x0494
#घोषणा AFE_CONN_DI                                    0x0498
#घोषणा AFE_CONN25                                     0x04b0
#घोषणा AFE_CONN26                                     0x04b4
#घोषणा AFE_CONN27                                     0x04b8
#घोषणा AFE_CONN28                                     0x04bc
#घोषणा AFE_CONN29                                     0x04c0
#घोषणा AFE_CONN30                                     0x04c4
#घोषणा AFE_CONN31                                     0x04c8
#घोषणा AFE_CONN32                                     0x04cc
#घोषणा AFE_SRAM_DELSEL_CON1                           0x04f4
#घोषणा AFE_CONN56                                     0x0500
#घोषणा AFE_CONN57                                     0x0504
#घोषणा AFE_CONN56_1                                   0x0510
#घोषणा AFE_CONN57_1                                   0x0514
#घोषणा AFE_TINY_CONN2                                 0x0520
#घोषणा AFE_TINY_CONN3                                 0x0524
#घोषणा AFE_TINY_CONN4                                 0x0528
#घोषणा AFE_TINY_CONN5                                 0x052c
#घोषणा PCM_INTF_CON1                                  0x0530
#घोषणा PCM_INTF_CON2                                  0x0538
#घोषणा PCM2_INTF_CON                                  0x053c
#घोषणा AFE_TDM_CON1                                   0x0548
#घोषणा AFE_TDM_CON2                                   0x054c
#घोषणा AFE_I2S_CON6                                   0x0564
#घोषणा AFE_I2S_CON7                                   0x0568
#घोषणा AFE_I2S_CON8                                   0x056c
#घोषणा AFE_I2S_CON9                                   0x0570
#घोषणा AFE_CONN34                                     0x0580
#घोषणा FPGA_CFG0                                      0x05b0
#घोषणा FPGA_CFG1                                      0x05b4
#घोषणा FPGA_CFG2                                      0x05c0
#घोषणा FPGA_CFG3                                      0x05c4
#घोषणा AUDIO_TOP_DBG_CON                              0x05c8
#घोषणा AUDIO_TOP_DBG_MON0                             0x05cc
#घोषणा AUDIO_TOP_DBG_MON1                             0x05d0
#घोषणा AFE_IRQ8_MCU_CNT_MON                           0x05e4
#घोषणा AFE_IRQ11_MCU_CNT_MON                          0x05e8
#घोषणा AFE_IRQ12_MCU_CNT_MON                          0x05ec
#घोषणा AFE_IRQ_MCU_CNT9                               0x0600
#घोषणा AFE_IRQ_MCU_CNT10                              0x0604
#घोषणा AFE_IRQ_MCU_CNT13                              0x0608
#घोषणा AFE_IRQ_MCU_CNT14                              0x060c
#घोषणा AFE_IRQ_MCU_CNT15                              0x0610
#घोषणा AFE_IRQ_MCU_CNT16                              0x0614
#घोषणा AFE_IRQ_MCU_CNT17                              0x0618
#घोषणा AFE_IRQ_MCU_CNT18                              0x061c
#घोषणा AFE_IRQ_MCU_CNT19                              0x0620
#घोषणा AFE_IRQ_MCU_CNT20                              0x0624
#घोषणा AFE_IRQ_MCU_CNT21                              0x0628
#घोषणा AFE_IRQ_MCU_CNT22                              0x062c
#घोषणा AFE_IRQ_MCU_CNT23                              0x0630
#घोषणा AFE_IRQ_MCU_CNT24                              0x0634
#घोषणा AFE_IRQ_MCU_CNT25                              0x0638
#घोषणा AFE_IRQ_MCU_CNT26                              0x063c
#घोषणा AFE_IRQ_MCU_CNT31                              0x0640
#घोषणा AFE_TINY_CONN6                                 0x0650
#घोषणा AFE_TINY_CONN7                                 0x0654
#घोषणा AFE_IRQ9_MCU_CNT_MON                           0x0660
#घोषणा AFE_IRQ10_MCU_CNT_MON                          0x0664
#घोषणा AFE_IRQ13_MCU_CNT_MON                          0x0668
#घोषणा AFE_IRQ14_MCU_CNT_MON                          0x066c
#घोषणा AFE_IRQ15_MCU_CNT_MON                          0x0670
#घोषणा AFE_IRQ16_MCU_CNT_MON                          0x0674
#घोषणा AFE_IRQ17_MCU_CNT_MON                          0x0678
#घोषणा AFE_IRQ18_MCU_CNT_MON                          0x067c
#घोषणा AFE_IRQ19_MCU_CNT_MON                          0x0680
#घोषणा AFE_IRQ20_MCU_CNT_MON                          0x0684
#घोषणा AFE_IRQ21_MCU_CNT_MON                          0x0688
#घोषणा AFE_IRQ22_MCU_CNT_MON                          0x068c
#घोषणा AFE_IRQ23_MCU_CNT_MON                          0x0690
#घोषणा AFE_IRQ24_MCU_CNT_MON                          0x0694
#घोषणा AFE_IRQ25_MCU_CNT_MON                          0x0698
#घोषणा AFE_IRQ26_MCU_CNT_MON                          0x069c
#घोषणा AFE_IRQ31_MCU_CNT_MON                          0x06a0
#घोषणा AFE_GENERAL_REG0                               0x0800
#घोषणा AFE_GENERAL_REG1                               0x0804
#घोषणा AFE_GENERAL_REG2                               0x0808
#घोषणा AFE_GENERAL_REG3                               0x080c
#घोषणा AFE_GENERAL_REG4                               0x0810
#घोषणा AFE_GENERAL_REG5                               0x0814
#घोषणा AFE_GENERAL_REG6                               0x0818
#घोषणा AFE_GENERAL_REG7                               0x081c
#घोषणा AFE_GENERAL_REG8                               0x0820
#घोषणा AFE_GENERAL_REG9                               0x0824
#घोषणा AFE_GENERAL_REG10                              0x0828
#घोषणा AFE_GENERAL_REG11                              0x082c
#घोषणा AFE_GENERAL_REG12                              0x0830
#घोषणा AFE_GENERAL_REG13                              0x0834
#घोषणा AFE_GENERAL_REG14                              0x0838
#घोषणा AFE_GENERAL_REG15                              0x083c
#घोषणा AFE_CBIP_CFG0                                  0x0840
#घोषणा AFE_CBIP_MON0                                  0x0844
#घोषणा AFE_CBIP_SLV_MUX_MON0                          0x0848
#घोषणा AFE_CBIP_SLV_DECODER_MON0                      0x084c
#घोषणा AFE_ADDA6_MTKAIF_MON0                          0x0854
#घोषणा AFE_ADDA6_MTKAIF_MON1                          0x0858
#घोषणा AFE_AWB_CON0                                   0x085c
#घोषणा AFE_AWB_BASE_MSB                               0x0860
#घोषणा AFE_AWB_BASE                                   0x0864
#घोषणा AFE_AWB_CUR_MSB                                0x0868
#घोषणा AFE_AWB_CUR                                    0x086c
#घोषणा AFE_AWB_END_MSB                                0x0870
#घोषणा AFE_AWB_END                                    0x0874
#घोषणा AFE_AWB2_CON0                                  0x0878
#घोषणा AFE_AWB2_BASE_MSB                              0x087c
#घोषणा AFE_AWB2_BASE                                  0x0880
#घोषणा AFE_AWB2_CUR_MSB                               0x0884
#घोषणा AFE_AWB2_CUR                                   0x0888
#घोषणा AFE_AWB2_END_MSB                               0x088c
#घोषणा AFE_AWB2_END                                   0x0890
#घोषणा AFE_DAI_CON0                                   0x0894
#घोषणा AFE_DAI_BASE_MSB                               0x0898
#घोषणा AFE_DAI_BASE                                   0x089c
#घोषणा AFE_DAI_CUR_MSB                                0x08a0
#घोषणा AFE_DAI_CUR                                    0x08a4
#घोषणा AFE_DAI_END_MSB                                0x08a8
#घोषणा AFE_DAI_END                                    0x08ac
#घोषणा AFE_DAI2_CON0                                  0x08b0
#घोषणा AFE_DAI2_BASE_MSB                              0x08b4
#घोषणा AFE_DAI2_BASE                                  0x08b8
#घोषणा AFE_DAI2_CUR_MSB                               0x08bc
#घोषणा AFE_DAI2_CUR                                   0x08c0
#घोषणा AFE_DAI2_END_MSB                               0x08c4
#घोषणा AFE_DAI2_END                                   0x08c8
#घोषणा AFE_MEMIF_CON0                                 0x08cc
#घोषणा AFE_CONN0_1                                    0x0900
#घोषणा AFE_CONN1_1                                    0x0904
#घोषणा AFE_CONN2_1                                    0x0908
#घोषणा AFE_CONN3_1                                    0x090c
#घोषणा AFE_CONN4_1                                    0x0910
#घोषणा AFE_CONN5_1                                    0x0914
#घोषणा AFE_CONN6_1                                    0x0918
#घोषणा AFE_CONN7_1                                    0x091c
#घोषणा AFE_CONN8_1                                    0x0920
#घोषणा AFE_CONN9_1                                    0x0924
#घोषणा AFE_CONN10_1                                   0x0928
#घोषणा AFE_CONN11_1                                   0x092c
#घोषणा AFE_CONN12_1                                   0x0930
#घोषणा AFE_CONN13_1                                   0x0934
#घोषणा AFE_CONN14_1                                   0x0938
#घोषणा AFE_CONN15_1                                   0x093c
#घोषणा AFE_CONN16_1                                   0x0940
#घोषणा AFE_CONN17_1                                   0x0944
#घोषणा AFE_CONN18_1                                   0x0948
#घोषणा AFE_CONN19_1                                   0x094c
#घोषणा AFE_CONN20_1                                   0x0950
#घोषणा AFE_CONN21_1                                   0x0954
#घोषणा AFE_CONN22_1                                   0x0958
#घोषणा AFE_CONN23_1                                   0x095c
#घोषणा AFE_CONN24_1                                   0x0960
#घोषणा AFE_CONN25_1                                   0x0964
#घोषणा AFE_CONN26_1                                   0x0968
#घोषणा AFE_CONN27_1                                   0x096c
#घोषणा AFE_CONN28_1                                   0x0970
#घोषणा AFE_CONN29_1                                   0x0974
#घोषणा AFE_CONN30_1                                   0x0978
#घोषणा AFE_CONN31_1                                   0x097c
#घोषणा AFE_CONN32_1                                   0x0980
#घोषणा AFE_CONN33_1                                   0x0984
#घोषणा AFE_CONN34_1                                   0x0988
#घोषणा AFE_CONN_RS_1                                  0x098c
#घोषणा AFE_CONN_DI_1                                  0x0990
#घोषणा AFE_CONN_24BIT_1                               0x0994
#घोषणा AFE_CONN_REG                                   0x0998
#घोषणा AFE_CONN35                                     0x09a0
#घोषणा AFE_CONN36                                     0x09a4
#घोषणा AFE_CONN37                                     0x09a8
#घोषणा AFE_CONN38                                     0x09ac
#घोषणा AFE_CONN35_1                                   0x09b0
#घोषणा AFE_CONN36_1                                   0x09b4
#घोषणा AFE_CONN37_1                                   0x09b8
#घोषणा AFE_CONN38_1                                   0x09bc
#घोषणा AFE_CONN39                                     0x09c0
#घोषणा AFE_CONN40                                     0x09c4
#घोषणा AFE_CONN41                                     0x09c8
#घोषणा AFE_CONN42                                     0x09cc
#घोषणा AFE_SGEN_CON_SGEN32                            0x09d0
#घोषणा AFE_CONN39_1                                   0x09e0
#घोषणा AFE_CONN40_1                                   0x09e4
#घोषणा AFE_CONN41_1                                   0x09e8
#घोषणा AFE_CONN42_1                                   0x09ec
#घोषणा AFE_I2S_CON4                                   0x09f8
#घोषणा AFE_ADDA6_TOP_CON0                             0x0a80
#घोषणा AFE_ADDA6_UL_SRC_CON0                          0x0a84
#घोषणा AFE_ADDA6_UL_SRC_CON1                          0x0a88
#घोषणा AFE_ADDA6_SRC_DEBUG                            0x0a8c
#घोषणा AFE_ADDA6_SRC_DEBUG_MON0                       0x0a90
#घोषणा AFE_ADDA6_ULCF_CFG_02_01                       0x0aa0
#घोषणा AFE_ADDA6_ULCF_CFG_04_03                       0x0aa4
#घोषणा AFE_ADDA6_ULCF_CFG_06_05                       0x0aa8
#घोषणा AFE_ADDA6_ULCF_CFG_08_07                       0x0aac
#घोषणा AFE_ADDA6_ULCF_CFG_10_09                       0x0ab0
#घोषणा AFE_ADDA6_ULCF_CFG_12_11                       0x0ab4
#घोषणा AFE_ADDA6_ULCF_CFG_14_13                       0x0ab8
#घोषणा AFE_ADDA6_ULCF_CFG_16_15                       0x0abc
#घोषणा AFE_ADDA6_ULCF_CFG_18_17                       0x0ac0
#घोषणा AFE_ADDA6_ULCF_CFG_20_19                       0x0ac4
#घोषणा AFE_ADDA6_ULCF_CFG_22_21                       0x0ac8
#घोषणा AFE_ADDA6_ULCF_CFG_24_23                       0x0acc
#घोषणा AFE_ADDA6_ULCF_CFG_26_25                       0x0ad0
#घोषणा AFE_ADDA6_ULCF_CFG_28_27                       0x0ad4
#घोषणा AFE_ADDA6_ULCF_CFG_30_29                       0x0ad8
#घोषणा AFE_ADD6A_UL_SRC_MON0                          0x0ae4
#घोषणा AFE_ADDA6_UL_SRC_MON1                          0x0ae8
#घोषणा AFE_TINY_CONN0                                 0x0af0
#घोषणा AFE_TINY_CONN1                                 0x0af4
#घोषणा AFE_CONN43                                     0x0af8
#घोषणा AFE_CONN43_1                                   0x0afc
#घोषणा AFE_MOD_DAI_CON0                               0x0b00
#घोषणा AFE_MOD_DAI_BASE_MSB                           0x0b04
#घोषणा AFE_MOD_DAI_BASE                               0x0b08
#घोषणा AFE_MOD_DAI_CUR_MSB                            0x0b0c
#घोषणा AFE_MOD_DAI_CUR                                0x0b10
#घोषणा AFE_MOD_DAI_END_MSB                            0x0b14
#घोषणा AFE_MOD_DAI_END                                0x0b18
#घोषणा AFE_HDMI_OUT_CON0                              0x0b1c
#घोषणा AFE_HDMI_OUT_BASE_MSB                          0x0b20
#घोषणा AFE_HDMI_OUT_BASE                              0x0b24
#घोषणा AFE_HDMI_OUT_CUR_MSB                           0x0b28
#घोषणा AFE_HDMI_OUT_CUR                               0x0b2c
#घोषणा AFE_HDMI_OUT_END_MSB                           0x0b30
#घोषणा AFE_HDMI_OUT_END                               0x0b34
#घोषणा AFE_AWB_RCH_MON                                0x0b70
#घोषणा AFE_AWB_LCH_MON                                0x0b74
#घोषणा AFE_VUL_RCH_MON                                0x0b78
#घोषणा AFE_VUL_LCH_MON                                0x0b7c
#घोषणा AFE_VUL12_RCH_MON                              0x0b80
#घोषणा AFE_VUL12_LCH_MON                              0x0b84
#घोषणा AFE_VUL2_RCH_MON                               0x0b88
#घोषणा AFE_VUL2_LCH_MON                               0x0b8c
#घोषणा AFE_DAI_DATA_MON                               0x0b90
#घोषणा AFE_MOD_DAI_DATA_MON                           0x0b94
#घोषणा AFE_DAI2_DATA_MON                              0x0b98
#घोषणा AFE_AWB2_RCH_MON                               0x0b9c
#घोषणा AFE_AWB2_LCH_MON                               0x0ba0
#घोषणा AFE_VUL3_RCH_MON                               0x0ba4
#घोषणा AFE_VUL3_LCH_MON                               0x0ba8
#घोषणा AFE_VUL4_RCH_MON                               0x0bac
#घोषणा AFE_VUL4_LCH_MON                               0x0bb0
#घोषणा AFE_VUL5_RCH_MON                               0x0bb4
#घोषणा AFE_VUL5_LCH_MON                               0x0bb8
#घोषणा AFE_VUL6_RCH_MON                               0x0bbc
#घोषणा AFE_VUL6_LCH_MON                               0x0bc0
#घोषणा AFE_DL1_RCH_MON                                0x0bc4
#घोषणा AFE_DL1_LCH_MON                                0x0bc8
#घोषणा AFE_DL2_RCH_MON                                0x0bcc
#घोषणा AFE_DL2_LCH_MON                                0x0bd0
#घोषणा AFE_DL12_RCH1_MON                              0x0bd4
#घोषणा AFE_DL12_LCH1_MON                              0x0bd8
#घोषणा AFE_DL12_RCH2_MON                              0x0bdc
#घोषणा AFE_DL12_LCH2_MON                              0x0be0
#घोषणा AFE_DL3_RCH_MON                                0x0be4
#घोषणा AFE_DL3_LCH_MON                                0x0be8
#घोषणा AFE_DL4_RCH_MON                                0x0bec
#घोषणा AFE_DL4_LCH_MON                                0x0bf0
#घोषणा AFE_DL5_RCH_MON                                0x0bf4
#घोषणा AFE_DL5_LCH_MON                                0x0bf8
#घोषणा AFE_DL6_RCH_MON                                0x0bfc
#घोषणा AFE_DL6_LCH_MON                                0x0c00
#घोषणा AFE_DL7_RCH_MON                                0x0c04
#घोषणा AFE_DL7_LCH_MON                                0x0c08
#घोषणा AFE_DL8_RCH_MON                                0x0c0c
#घोषणा AFE_DL8_LCH_MON                                0x0c10
#घोषणा AFE_VUL5_CON0                                  0x0c14
#घोषणा AFE_VUL5_BASE_MSB                              0x0c18
#घोषणा AFE_VUL5_BASE                                  0x0c1c
#घोषणा AFE_VUL5_CUR_MSB                               0x0c20
#घोषणा AFE_VUL5_CUR                                   0x0c24
#घोषणा AFE_VUL5_END_MSB                               0x0c28
#घोषणा AFE_VUL5_END                                   0x0c2c
#घोषणा AFE_VUL6_CON0                                  0x0c30
#घोषणा AFE_VUL6_BASE_MSB                              0x0c34
#घोषणा AFE_VUL6_BASE                                  0x0c38
#घोषणा AFE_VUL6_CUR_MSB                               0x0c3c
#घोषणा AFE_VUL6_CUR                                   0x0c40
#घोषणा AFE_VUL6_END_MSB                               0x0c44
#घोषणा AFE_VUL6_END                                   0x0c48
#घोषणा AFE_ADDA_DL_SDM_DCCOMP_CON                     0x0c50
#घोषणा AFE_ADDA_DL_SDM_TEST                           0x0c54
#घोषणा AFE_ADDA_DL_DC_COMP_CFG0                       0x0c58
#घोषणा AFE_ADDA_DL_DC_COMP_CFG1                       0x0c5c
#घोषणा AFE_ADDA_DL_SDM_FIFO_MON                       0x0c60
#घोषणा AFE_ADDA_DL_SRC_LCH_MON                        0x0c64
#घोषणा AFE_ADDA_DL_SRC_RCH_MON                        0x0c68
#घोषणा AFE_ADDA_DL_SDM_OUT_MON                        0x0c6c
#घोषणा AFE_ADDA_DL_SDM_DITHER_CON                     0x0c70
#घोषणा AFE_ADDA_DL_SDM_AUTO_RESET_CON                 0x0c74
#घोषणा AFE_CONNSYS_I2S_CON                            0x0c78
#घोषणा AFE_CONNSYS_I2S_MON                            0x0c7c
#घोषणा AFE_ASRC_2CH_CON0                              0x0c80
#घोषणा AFE_ASRC_2CH_CON1                              0x0c84
#घोषणा AFE_ASRC_2CH_CON2                              0x0c88
#घोषणा AFE_ASRC_2CH_CON3                              0x0c8c
#घोषणा AFE_ASRC_2CH_CON4                              0x0c90
#घोषणा AFE_ASRC_2CH_CON5                              0x0c94
#घोषणा AFE_ASRC_2CH_CON6                              0x0c98
#घोषणा AFE_ASRC_2CH_CON7                              0x0c9c
#घोषणा AFE_ASRC_2CH_CON8                              0x0ca0
#घोषणा AFE_ASRC_2CH_CON9                              0x0ca4
#घोषणा AFE_ASRC_2CH_CON10                             0x0ca8
#घोषणा AFE_ASRC_2CH_CON12                             0x0cb0
#घोषणा AFE_ASRC_2CH_CON13                             0x0cb4
#घोषणा AFE_ADDA6_IIR_COEF_02_01                       0x0ce0
#घोषणा AFE_ADDA6_IIR_COEF_04_03                       0x0ce4
#घोषणा AFE_ADDA6_IIR_COEF_06_05                       0x0ce8
#घोषणा AFE_ADDA6_IIR_COEF_08_07                       0x0cec
#घोषणा AFE_ADDA6_IIR_COEF_10_09                       0x0cf0
#घोषणा AFE_SE_PROT_SIDEBAND                           0x0d38
#घोषणा AFE_SE_DOMAIN_SIDEBAND0                        0x0d3c
#घोषणा AFE_ADDA_PREDIS_CON2                           0x0d40
#घोषणा AFE_ADDA_PREDIS_CON3                           0x0d44
#घोषणा AFE_MEMIF_CONN                                 0x0d50
#घोषणा AFE_SE_DOMAIN_SIDEBAND1                        0x0d54
#घोषणा AFE_SE_DOMAIN_SIDEBAND2                        0x0d58
#घोषणा AFE_SE_DOMAIN_SIDEBAND3                        0x0d5c
#घोषणा AFE_CONN44                                     0x0d70
#घोषणा AFE_CONN45                                     0x0d74
#घोषणा AFE_CONN46                                     0x0d78
#घोषणा AFE_CONN47                                     0x0d7c
#घोषणा AFE_CONN44_1                                   0x0d80
#घोषणा AFE_CONN45_1                                   0x0d84
#घोषणा AFE_CONN46_1                                   0x0d88
#घोषणा AFE_CONN47_1                                   0x0d8c
#घोषणा AFE_DL9_CUR_MSB                                0x0dc0
#घोषणा AFE_DL9_CUR                                    0x0dc4
#घोषणा AFE_DL9_END_MSB                                0x0dc8
#घोषणा AFE_DL9_END                                    0x0dcc
#घोषणा AFE_HD_ENGEN_ENABLE                            0x0dd0
#घोषणा AFE_ADDA_DL_NLE_FIFO_MON                       0x0dfc
#घोषणा AFE_ADDA_MTKAIF_CFG0                           0x0e00
#घोषणा AFE_ADDA_MTKAIF_SYNCWORD_CFG                   0x0e14
#घोषणा AFE_ADDA_MTKAIF_RX_CFG0                        0x0e20
#घोषणा AFE_ADDA_MTKAIF_RX_CFG1                        0x0e24
#घोषणा AFE_ADDA_MTKAIF_RX_CFG2                        0x0e28
#घोषणा AFE_ADDA_MTKAIF_MON0                           0x0e34
#घोषणा AFE_ADDA_MTKAIF_MON1                           0x0e38
#घोषणा AFE_AUD_PAD_TOP                                0x0e40
#घोषणा AFE_DL_NLE_R_CFG0                              0x0e44
#घोषणा AFE_DL_NLE_R_CFG1                              0x0e48
#घोषणा AFE_DL_NLE_L_CFG0                              0x0e4c
#घोषणा AFE_DL_NLE_L_CFG1                              0x0e50
#घोषणा AFE_DL_NLE_R_MON0                              0x0e54
#घोषणा AFE_DL_NLE_R_MON1                              0x0e58
#घोषणा AFE_DL_NLE_R_MON2                              0x0e5c
#घोषणा AFE_DL_NLE_L_MON0                              0x0e60
#घोषणा AFE_DL_NLE_L_MON1                              0x0e64
#घोषणा AFE_DL_NLE_L_MON2                              0x0e68
#घोषणा AFE_DL_NLE_GAIN_CFG0                           0x0e6c
#घोषणा AFE_ADDA6_MTKAIF_CFG0                          0x0e70
#घोषणा AFE_ADDA6_MTKAIF_RX_CFG0                       0x0e74
#घोषणा AFE_ADDA6_MTKAIF_RX_CFG1                       0x0e78
#घोषणा AFE_ADDA6_MTKAIF_RX_CFG2                       0x0e7c
#घोषणा AFE_GENERAL1_ASRC_2CH_CON0                     0x0e80
#घोषणा AFE_GENERAL1_ASRC_2CH_CON1                     0x0e84
#घोषणा AFE_GENERAL1_ASRC_2CH_CON2                     0x0e88
#घोषणा AFE_GENERAL1_ASRC_2CH_CON3                     0x0e8c
#घोषणा AFE_GENERAL1_ASRC_2CH_CON4                     0x0e90
#घोषणा AFE_GENERAL1_ASRC_2CH_CON5                     0x0e94
#घोषणा AFE_GENERAL1_ASRC_2CH_CON6                     0x0e98
#घोषणा AFE_GENERAL1_ASRC_2CH_CON7                     0x0e9c
#घोषणा AFE_GENERAL1_ASRC_2CH_CON8                     0x0ea0
#घोषणा AFE_GENERAL1_ASRC_2CH_CON9                     0x0ea4
#घोषणा AFE_GENERAL1_ASRC_2CH_CON10                    0x0ea8
#घोषणा AFE_GENERAL1_ASRC_2CH_CON12                    0x0eb0
#घोषणा AFE_GENERAL1_ASRC_2CH_CON13                    0x0eb4
#घोषणा GENERAL_ASRC_MODE                              0x0eb8
#घोषणा GENERAL_ASRC_EN_ON                             0x0ebc
#घोषणा AFE_CONN48                                     0x0ec0
#घोषणा AFE_CONN49                                     0x0ec4
#घोषणा AFE_CONN50                                     0x0ec8
#घोषणा AFE_CONN51                                     0x0ecc
#घोषणा AFE_CONN52                                     0x0ed0
#घोषणा AFE_CONN53                                     0x0ed4
#घोषणा AFE_CONN54                                     0x0ed8
#घोषणा AFE_CONN55                                     0x0edc
#घोषणा AFE_CONN48_1                                   0x0ee0
#घोषणा AFE_CONN49_1                                   0x0ee4
#घोषणा AFE_CONN50_1                                   0x0ee8
#घोषणा AFE_CONN51_1                                   0x0eec
#घोषणा AFE_CONN52_1                                   0x0ef0
#घोषणा AFE_CONN53_1                                   0x0ef4
#घोषणा AFE_CONN54_1                                   0x0ef8
#घोषणा AFE_CONN55_1                                   0x0efc
#घोषणा AFE_GENERAL2_ASRC_2CH_CON0                     0x0f00
#घोषणा AFE_GENERAL2_ASRC_2CH_CON1                     0x0f04
#घोषणा AFE_GENERAL2_ASRC_2CH_CON2                     0x0f08
#घोषणा AFE_GENERAL2_ASRC_2CH_CON3                     0x0f0c
#घोषणा AFE_GENERAL2_ASRC_2CH_CON4                     0x0f10
#घोषणा AFE_GENERAL2_ASRC_2CH_CON5                     0x0f14
#घोषणा AFE_GENERAL2_ASRC_2CH_CON6                     0x0f18
#घोषणा AFE_GENERAL2_ASRC_2CH_CON7                     0x0f1c
#घोषणा AFE_GENERAL2_ASRC_2CH_CON8                     0x0f20
#घोषणा AFE_GENERAL2_ASRC_2CH_CON9                     0x0f24
#घोषणा AFE_GENERAL2_ASRC_2CH_CON10                    0x0f28
#घोषणा AFE_GENERAL2_ASRC_2CH_CON12                    0x0f30
#घोषणा AFE_GENERAL2_ASRC_2CH_CON13                    0x0f34
#घोषणा AFE_DL9_RCH_MON                                0x0f38
#घोषणा AFE_DL9_LCH_MON                                0x0f3c
#घोषणा AFE_DL5_CON0                                   0x0f4c
#घोषणा AFE_DL5_BASE_MSB                               0x0f50
#घोषणा AFE_DL5_BASE                                   0x0f54
#घोषणा AFE_DL5_CUR_MSB                                0x0f58
#घोषणा AFE_DL5_CUR                                    0x0f5c
#घोषणा AFE_DL5_END_MSB                                0x0f60
#घोषणा AFE_DL5_END                                    0x0f64
#घोषणा AFE_DL6_CON0                                   0x0f68
#घोषणा AFE_DL6_BASE_MSB                               0x0f6c
#घोषणा AFE_DL6_BASE                                   0x0f70
#घोषणा AFE_DL6_CUR_MSB                                0x0f74
#घोषणा AFE_DL6_CUR                                    0x0f78
#घोषणा AFE_DL6_END_MSB                                0x0f7c
#घोषणा AFE_DL6_END                                    0x0f80
#घोषणा AFE_DL7_CON0                                   0x0f84
#घोषणा AFE_DL7_BASE_MSB                               0x0f88
#घोषणा AFE_DL7_BASE                                   0x0f8c
#घोषणा AFE_DL7_CUR_MSB                                0x0f90
#घोषणा AFE_DL7_CUR                                    0x0f94
#घोषणा AFE_DL7_END_MSB                                0x0f98
#घोषणा AFE_DL7_END                                    0x0f9c
#घोषणा AFE_DL8_CON0                                   0x0fa0
#घोषणा AFE_DL8_BASE_MSB                               0x0fa4
#घोषणा AFE_DL8_BASE                                   0x0fa8
#घोषणा AFE_DL8_CUR_MSB                                0x0fac
#घोषणा AFE_DL8_CUR                                    0x0fb0
#घोषणा AFE_DL8_END_MSB                                0x0fb4
#घोषणा AFE_DL8_END                                    0x0fb8
#घोषणा AFE_DL9_CON0                                   0x0fbc
#घोषणा AFE_DL9_BASE_MSB                               0x0fc0
#घोषणा AFE_DL9_BASE                                   0x0fc4
#घोषणा AFE_SE_SECURE_CON                              0x1004
#घोषणा AFE_PROT_SIDEBAND_MON                          0x1008
#घोषणा AFE_DOMAIN_SIDEBAND0_MON                       0x100c
#घोषणा AFE_DOMAIN_SIDEBAND1_MON                       0x1010
#घोषणा AFE_DOMAIN_SIDEBAND2_MON                       0x1014
#घोषणा AFE_DOMAIN_SIDEBAND3_MON                       0x1018
#घोषणा AFE_SECURE_MASK_CONN0                          0x1020
#घोषणा AFE_SECURE_MASK_CONN1                          0x1024
#घोषणा AFE_SECURE_MASK_CONN2                          0x1028
#घोषणा AFE_SECURE_MASK_CONN3                          0x102c
#घोषणा AFE_SECURE_MASK_CONN4                          0x1030
#घोषणा AFE_SECURE_MASK_CONN5                          0x1034
#घोषणा AFE_SECURE_MASK_CONN6                          0x1038
#घोषणा AFE_SECURE_MASK_CONN7                          0x103c
#घोषणा AFE_SECURE_MASK_CONN8                          0x1040
#घोषणा AFE_SECURE_MASK_CONN9                          0x1044
#घोषणा AFE_SECURE_MASK_CONN10                         0x1048
#घोषणा AFE_SECURE_MASK_CONN11                         0x104c
#घोषणा AFE_SECURE_MASK_CONN12                         0x1050
#घोषणा AFE_SECURE_MASK_CONN13                         0x1054
#घोषणा AFE_SECURE_MASK_CONN14                         0x1058
#घोषणा AFE_SECURE_MASK_CONN15                         0x105c
#घोषणा AFE_SECURE_MASK_CONN16                         0x1060
#घोषणा AFE_SECURE_MASK_CONN17                         0x1064
#घोषणा AFE_SECURE_MASK_CONN18                         0x1068
#घोषणा AFE_SECURE_MASK_CONN19                         0x106c
#घोषणा AFE_SECURE_MASK_CONN20                         0x1070
#घोषणा AFE_SECURE_MASK_CONN21                         0x1074
#घोषणा AFE_SECURE_MASK_CONN22                         0x1078
#घोषणा AFE_SECURE_MASK_CONN23                         0x107c
#घोषणा AFE_SECURE_MASK_CONN24                         0x1080
#घोषणा AFE_SECURE_MASK_CONN25                         0x1084
#घोषणा AFE_SECURE_MASK_CONN26                         0x1088
#घोषणा AFE_SECURE_MASK_CONN27                         0x108c
#घोषणा AFE_SECURE_MASK_CONN28                         0x1090
#घोषणा AFE_SECURE_MASK_CONN29                         0x1094
#घोषणा AFE_SECURE_MASK_CONN30                         0x1098
#घोषणा AFE_SECURE_MASK_CONN31                         0x109c
#घोषणा AFE_SECURE_MASK_CONN32                         0x10a0
#घोषणा AFE_SECURE_MASK_CONN33                         0x10a4
#घोषणा AFE_SECURE_MASK_CONN34                         0x10a8
#घोषणा AFE_SECURE_MASK_CONN35                         0x10ac
#घोषणा AFE_SECURE_MASK_CONN36                         0x10b0
#घोषणा AFE_SECURE_MASK_CONN37                         0x10b4
#घोषणा AFE_SECURE_MASK_CONN38                         0x10b8
#घोषणा AFE_SECURE_MASK_CONN39                         0x10bc
#घोषणा AFE_SECURE_MASK_CONN40                         0x10c0
#घोषणा AFE_SECURE_MASK_CONN41                         0x10c4
#घोषणा AFE_SECURE_MASK_CONN42                         0x10c8
#घोषणा AFE_SECURE_MASK_CONN43                         0x10cc
#घोषणा AFE_SECURE_MASK_CONN44                         0x10d0
#घोषणा AFE_SECURE_MASK_CONN45                         0x10d4
#घोषणा AFE_SECURE_MASK_CONN46                         0x10d8
#घोषणा AFE_SECURE_MASK_CONN47                         0x10dc
#घोषणा AFE_SECURE_MASK_CONN48                         0x10e0
#घोषणा AFE_SECURE_MASK_CONN49                         0x10e4
#घोषणा AFE_SECURE_MASK_CONN50                         0x10e8
#घोषणा AFE_SECURE_MASK_CONN51                         0x10ec
#घोषणा AFE_SECURE_MASK_CONN52                         0x10f0
#घोषणा AFE_SECURE_MASK_CONN53                         0x10f4
#घोषणा AFE_SECURE_MASK_CONN54                         0x10f8
#घोषणा AFE_SECURE_MASK_CONN55                         0x10fc
#घोषणा AFE_SECURE_MASK_CONN56                         0x1100
#घोषणा AFE_SECURE_MASK_CONN57                         0x1104
#घोषणा AFE_SECURE_MASK_CONN0_1                        0x1108
#घोषणा AFE_SECURE_MASK_CONN1_1                        0x110c
#घोषणा AFE_SECURE_MASK_CONN2_1                        0x1110
#घोषणा AFE_SECURE_MASK_CONN3_1                        0x1114
#घोषणा AFE_SECURE_MASK_CONN4_1                        0x1118
#घोषणा AFE_SECURE_MASK_CONN5_1                        0x111c
#घोषणा AFE_SECURE_MASK_CONN6_1                        0x1120
#घोषणा AFE_SECURE_MASK_CONN7_1                        0x1124
#घोषणा AFE_SECURE_MASK_CONN8_1                        0x1128
#घोषणा AFE_SECURE_MASK_CONN9_1                        0x112c
#घोषणा AFE_SECURE_MASK_CONN10_1                       0x1130
#घोषणा AFE_SECURE_MASK_CONN11_1                       0x1134
#घोषणा AFE_SECURE_MASK_CONN12_1                       0x1138
#घोषणा AFE_SECURE_MASK_CONN13_1                       0x113c
#घोषणा AFE_SECURE_MASK_CONN14_1                       0x1140
#घोषणा AFE_SECURE_MASK_CONN15_1                       0x1144
#घोषणा AFE_SECURE_MASK_CONN16_1                       0x1148
#घोषणा AFE_SECURE_MASK_CONN17_1                       0x114c
#घोषणा AFE_SECURE_MASK_CONN18_1                       0x1150
#घोषणा AFE_SECURE_MASK_CONN19_1                       0x1154
#घोषणा AFE_SECURE_MASK_CONN20_1                       0x1158
#घोषणा AFE_SECURE_MASK_CONN21_1                       0x115c
#घोषणा AFE_SECURE_MASK_CONN22_1                       0x1160
#घोषणा AFE_SECURE_MASK_CONN23_1                       0x1164
#घोषणा AFE_SECURE_MASK_CONN24_1                       0x1168
#घोषणा AFE_SECURE_MASK_CONN25_1                       0x116c
#घोषणा AFE_SECURE_MASK_CONN26_1                       0x1170
#घोषणा AFE_SECURE_MASK_CONN27_1                       0x1174
#घोषणा AFE_SECURE_MASK_CONN28_1                       0x1178
#घोषणा AFE_SECURE_MASK_CONN29_1                       0x117c
#घोषणा AFE_SECURE_MASK_CONN30_1                       0x1180
#घोषणा AFE_SECURE_MASK_CONN31_1                       0x1184
#घोषणा AFE_SECURE_MASK_CONN32_1                       0x1188
#घोषणा AFE_SECURE_MASK_CONN33_1                       0x118c
#घोषणा AFE_SECURE_MASK_CONN34_1                       0x1190
#घोषणा AFE_SECURE_MASK_CONN35_1                       0x1194
#घोषणा AFE_SECURE_MASK_CONN36_1                       0x1198
#घोषणा AFE_SECURE_MASK_CONN37_1                       0x119c
#घोषणा AFE_SECURE_MASK_CONN38_1                       0x11a0
#घोषणा AFE_SECURE_MASK_CONN39_1                       0x11a4
#घोषणा AFE_SECURE_MASK_CONN40_1                       0x11a8
#घोषणा AFE_SECURE_MASK_CONN41_1                       0x11ac
#घोषणा AFE_SECURE_MASK_CONN42_1                       0x11b0
#घोषणा AFE_SECURE_MASK_CONN43_1                       0x11b4
#घोषणा AFE_SECURE_MASK_CONN44_1                       0x11b8
#घोषणा AFE_SECURE_MASK_CONN45_1                       0x11bc
#घोषणा AFE_SECURE_MASK_CONN46_1                       0x11c0
#घोषणा AFE_SECURE_MASK_CONN47_1                       0x11c4
#घोषणा AFE_SECURE_MASK_CONN48_1                       0x11c8
#घोषणा AFE_SECURE_MASK_CONN49_1                       0x11cc
#घोषणा AFE_SECURE_MASK_CONN50_1                       0x11d0
#घोषणा AFE_SECURE_MASK_CONN51_1                       0x11d4
#घोषणा AFE_SECURE_MASK_CONN52_1                       0x11d8
#घोषणा AFE_SECURE_MASK_CONN53_1                       0x11dc
#घोषणा AFE_SECURE_MASK_CONN54_1                       0x11e0
#घोषणा AFE_SECURE_MASK_CONN55_1                       0x11e4
#घोषणा AFE_SECURE_MASK_CONN56_1                       0x11e8
#घोषणा AFE_SECURE_MASK_TINY_CONN0                     0x1200
#घोषणा AFE_SECURE_MASK_TINY_CONN1                     0x1204
#घोषणा AFE_SECURE_MASK_TINY_CONN2                     0x1208
#घोषणा AFE_SECURE_MASK_TINY_CONN3                     0x120c
#घोषणा AFE_SECURE_MASK_TINY_CONN4                     0x1210
#घोषणा AFE_SECURE_MASK_TINY_CONN5                     0x1214
#घोषणा AFE_SECURE_MASK_TINY_CONN6                     0x1218
#घोषणा AFE_SECURE_MASK_TINY_CONN7                     0x121c

#घोषणा AFE_MAX_REGISTER AFE_SECURE_MASK_TINY_CONN7

#घोषणा AFE_IRQ_STATUS_BITS 0x87FFFFFF
#घोषणा AFE_IRQ_CNT_SHIFT 0
#घोषणा AFE_IRQ_CNT_MASK 0x3ffff

#पूर्ण_अगर
