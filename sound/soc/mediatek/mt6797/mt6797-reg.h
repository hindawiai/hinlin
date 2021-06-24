<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt6797-reg.h  --  Mediatek 6797 audio driver reg definition
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#अगर_अघोषित _MT6797_REG_H_
#घोषणा _MT6797_REG_H_

#घोषणा AUDIO_TOP_CON0            0x0000
#घोषणा AUDIO_TOP_CON1            0x0004
#घोषणा AUDIO_TOP_CON3            0x000c
#घोषणा AFE_DAC_CON0              0x0010
#घोषणा AFE_DAC_CON1              0x0014
#घोषणा AFE_I2S_CON               0x0018
#घोषणा AFE_DAIBT_CON0            0x001c
#घोषणा AFE_CONN0                 0x0020
#घोषणा AFE_CONN1                 0x0024
#घोषणा AFE_CONN2                 0x0028
#घोषणा AFE_CONN3                 0x002c
#घोषणा AFE_CONN4                 0x0030
#घोषणा AFE_I2S_CON1              0x0034
#घोषणा AFE_I2S_CON2              0x0038
#घोषणा AFE_MRGIF_CON             0x003c
#घोषणा AFE_DL1_BASE              0x0040
#घोषणा AFE_DL1_CUR               0x0044
#घोषणा AFE_DL1_END               0x0048
#घोषणा AFE_I2S_CON3              0x004c
#घोषणा AFE_DL2_BASE              0x0050
#घोषणा AFE_DL2_CUR               0x0054
#घोषणा AFE_DL2_END               0x0058
#घोषणा AFE_CONN5                 0x005c
#घोषणा AFE_CONN_24BIT            0x006c
#घोषणा AFE_AWB_BASE              0x0070
#घोषणा AFE_AWB_END               0x0078
#घोषणा AFE_AWB_CUR               0x007c
#घोषणा AFE_VUL_BASE              0x0080
#घोषणा AFE_VUL_END               0x0088
#घोषणा AFE_VUL_CUR               0x008c
#घोषणा AFE_DAI_BASE              0x0090
#घोषणा AFE_DAI_END               0x0098
#घोषणा AFE_DAI_CUR               0x009c
#घोषणा AFE_CONN6                 0x00bc
#घोषणा AFE_MEMIF_MSB             0x00cc
#घोषणा AFE_MEMIF_MON0            0x00d0
#घोषणा AFE_MEMIF_MON1            0x00d4
#घोषणा AFE_MEMIF_MON2            0x00d8
#घोषणा AFE_MEMIF_MON4            0x00e0
#घोषणा AFE_ADDA_DL_SRC2_CON0     0x0108
#घोषणा AFE_ADDA_DL_SRC2_CON1     0x010c
#घोषणा AFE_ADDA_UL_SRC_CON0      0x0114
#घोषणा AFE_ADDA_UL_SRC_CON1      0x0118
#घोषणा AFE_ADDA_TOP_CON0         0x0120
#घोषणा AFE_ADDA_UL_DL_CON0       0x0124
#घोषणा AFE_ADDA_SRC_DEBUG        0x012c
#घोषणा AFE_ADDA_SRC_DEBUG_MON0   0x0130
#घोषणा AFE_ADDA_SRC_DEBUG_MON1   0x0134
#घोषणा AFE_ADDA_NEWIF_CFG0       0x0138
#घोषणा AFE_ADDA_NEWIF_CFG1       0x013c
#घोषणा AFE_ADDA_NEWIF_CFG2       0x0140
#घोषणा AFE_DMA_CTL               0x0150
#घोषणा AFE_DMA_MON0              0x0154
#घोषणा AFE_DMA_MON1              0x0158
#घोषणा AFE_SIDETONE_DEBUG        0x01d0
#घोषणा AFE_SIDETONE_MON          0x01d4
#घोषणा AFE_SIDETONE_CON0         0x01e0
#घोषणा AFE_SIDETONE_COEFF        0x01e4
#घोषणा AFE_SIDETONE_CON1         0x01e8
#घोषणा AFE_SIDETONE_GAIN         0x01ec
#घोषणा AFE_SGEN_CON0             0x01f0
#घोषणा AFE_SINEGEN_CON_TDM       0x01fc
#घोषणा AFE_TOP_CON0              0x0200
#घोषणा AFE_ADDA_PREDIS_CON0      0x0260
#घोषणा AFE_ADDA_PREDIS_CON1      0x0264
#घोषणा AFE_MRGIF_MON0            0x0270
#घोषणा AFE_MRGIF_MON1            0x0274
#घोषणा AFE_MRGIF_MON2            0x0278
#घोषणा AFE_I2S_MON               0x027c
#घोषणा AFE_MOD_DAI_BASE          0x0330
#घोषणा AFE_MOD_DAI_END           0x0338
#घोषणा AFE_MOD_DAI_CUR           0x033c
#घोषणा AFE_VUL_D2_BASE           0x0350
#घोषणा AFE_VUL_D2_END            0x0358
#घोषणा AFE_VUL_D2_CUR            0x035c
#घोषणा AFE_DL3_BASE              0x0360
#घोषणा AFE_DL3_CUR               0x0364
#घोषणा AFE_DL3_END               0x0368
#घोषणा AFE_HDMI_OUT_CON0         0x0370
#घोषणा AFE_HDMI_BASE             0x0374
#घोषणा AFE_HDMI_CUR              0x0378
#घोषणा AFE_HDMI_END              0x037c
#घोषणा AFE_HDMI_CONN0            0x0390
#घोषणा AFE_IRQ3_MCU_CNT_MON      0x0398
#घोषणा AFE_IRQ4_MCU_CNT_MON      0x039c
#घोषणा AFE_IRQ_MCU_CON           0x03a0
#घोषणा AFE_IRQ_MCU_STATUS        0x03a4
#घोषणा AFE_IRQ_MCU_CLR           0x03a8
#घोषणा AFE_IRQ_MCU_CNT1          0x03ac
#घोषणा AFE_IRQ_MCU_CNT2          0x03b0
#घोषणा AFE_IRQ_MCU_EN            0x03b4
#घोषणा AFE_IRQ_MCU_MON2          0x03b8
#घोषणा AFE_IRQ_MCU_CNT5          0x03bc
#घोषणा AFE_IRQ1_MCU_CNT_MON      0x03c0
#घोषणा AFE_IRQ2_MCU_CNT_MON      0x03c4
#घोषणा AFE_IRQ1_MCU_EN_CNT_MON   0x03c8
#घोषणा AFE_IRQ5_MCU_CNT_MON      0x03cc
#घोषणा AFE_MEMIF_MINLEN          0x03d0
#घोषणा AFE_MEMIF_MAXLEN          0x03d4
#घोषणा AFE_MEMIF_PBUF_SIZE       0x03d8
#घोषणा AFE_IRQ_MCU_CNT7          0x03dc
#घोषणा AFE_IRQ7_MCU_CNT_MON      0x03e0
#घोषणा AFE_IRQ_MCU_CNT3          0x03e4
#घोषणा AFE_IRQ_MCU_CNT4          0x03e8
#घोषणा AFE_APLL1_TUNER_CFG       0x03f0
#घोषणा AFE_APLL2_TUNER_CFG       0x03f4
#घोषणा AFE_MEMIF_HD_MODE         0x03f8
#घोषणा AFE_MEMIF_HDALIGN         0x03fc
#घोषणा AFE_GAIN1_CON0            0x0410
#घोषणा AFE_GAIN1_CON1            0x0414
#घोषणा AFE_GAIN1_CON2            0x0418
#घोषणा AFE_GAIN1_CON3            0x041c
#घोषणा AFE_CONN7                 0x0420
#घोषणा AFE_GAIN1_CUR             0x0424
#घोषणा AFE_GAIN2_CON0            0x0428
#घोषणा AFE_GAIN2_CON1            0x042c
#घोषणा AFE_GAIN2_CON2            0x0430
#घोषणा AFE_GAIN2_CON3            0x0434
#घोषणा AFE_CONN8                 0x0438
#घोषणा AFE_GAIN2_CUR             0x043c
#घोषणा AFE_CONN9                 0x0440
#घोषणा AFE_CONN10                0x0444
#घोषणा AFE_CONN11                0x0448
#घोषणा AFE_CONN12                0x044c
#घोषणा AFE_CONN13                0x0450
#घोषणा AFE_CONN14                0x0454
#घोषणा AFE_CONN15                0x0458
#घोषणा AFE_CONN16                0x045c
#घोषणा AFE_CONN17                0x0460
#घोषणा AFE_CONN18                0x0464
#घोषणा AFE_CONN19                0x0468
#घोषणा AFE_CONN20                0x046c
#घोषणा AFE_CONN21                0x0470
#घोषणा AFE_CONN22                0x0474
#घोषणा AFE_CONN23                0x0478
#घोषणा AFE_CONN24                0x047c
#घोषणा AFE_CONN_RS               0x0494
#घोषणा AFE_CONN_DI               0x0498
#घोषणा AFE_CONN25                0x04b0
#घोषणा AFE_CONN26                0x04b4
#घोषणा AFE_CONN27                0x04b8
#घोषणा AFE_CONN28                0x04bc
#घोषणा AFE_CONN29                0x04c0
#घोषणा AFE_SRAM_DELSEL_CON0      0x04f0
#घोषणा AFE_SRAM_DELSEL_CON1      0x04f4
#घोषणा AFE_ASRC_CON0             0x0500
#घोषणा AFE_ASRC_CON1             0x0504
#घोषणा AFE_ASRC_CON2             0x0508
#घोषणा AFE_ASRC_CON3             0x050c
#घोषणा AFE_ASRC_CON4             0x0510
#घोषणा AFE_ASRC_CON5             0x0514
#घोषणा AFE_ASRC_CON6             0x0518
#घोषणा AFE_ASRC_CON7             0x051c
#घोषणा AFE_ASRC_CON8             0x0520
#घोषणा AFE_ASRC_CON9             0x0524
#घोषणा AFE_ASRC_CON10            0x0528
#घोषणा AFE_ASRC_CON11            0x052c
#घोषणा PCM_INTF_CON1             0x0530
#घोषणा PCM_INTF_CON2             0x0538
#घोषणा PCM2_INTF_CON             0x053c
#घोषणा AFE_TDM_CON1              0x0548
#घोषणा AFE_TDM_CON2              0x054c
#घोषणा AFE_ASRC_CON13            0x0550
#घोषणा AFE_ASRC_CON14            0x0554
#घोषणा AFE_ASRC_CON15            0x0558
#घोषणा AFE_ASRC_CON16            0x055c
#घोषणा AFE_ASRC_CON17            0x0560
#घोषणा AFE_ASRC_CON18            0x0564
#घोषणा AFE_ASRC_CON19            0x0568
#घोषणा AFE_ASRC_CON20            0x056c
#घोषणा AFE_ASRC_CON21            0x0570
#घोषणा CLK_AUDDIV_0              0x05a0
#घोषणा CLK_AUDDIV_1              0x05a4
#घोषणा CLK_AUDDIV_2              0x05a8
#घोषणा CLK_AUDDIV_3              0x05ac
#घोषणा AUDIO_TOP_DBG_CON         0x05c8
#घोषणा AUDIO_TOP_DBG_MON0        0x05cc
#घोषणा AUDIO_TOP_DBG_MON1        0x05d0
#घोषणा AUDIO_TOP_DBG_MON2        0x05d4
#घोषणा AFE_ADDA2_TOP_CON0        0x0600
#घोषणा AFE_ASRC4_CON0            0x06c0
#घोषणा AFE_ASRC4_CON1            0x06c4
#घोषणा AFE_ASRC4_CON2            0x06c8
#घोषणा AFE_ASRC4_CON3            0x06cc
#घोषणा AFE_ASRC4_CON4            0x06d0
#घोषणा AFE_ASRC4_CON5            0x06d4
#घोषणा AFE_ASRC4_CON6            0x06d8
#घोषणा AFE_ASRC4_CON7            0x06dc
#घोषणा AFE_ASRC4_CON8            0x06e0
#घोषणा AFE_ASRC4_CON9            0x06e4
#घोषणा AFE_ASRC4_CON10           0x06e8
#घोषणा AFE_ASRC4_CON11           0x06ec
#घोषणा AFE_ASRC4_CON12           0x06f0
#घोषणा AFE_ASRC4_CON13           0x06f4
#घोषणा AFE_ASRC4_CON14           0x06f8
#घोषणा AFE_ASRC2_CON0            0x0700
#घोषणा AFE_ASRC2_CON1            0x0704
#घोषणा AFE_ASRC2_CON2            0x0708
#घोषणा AFE_ASRC2_CON3            0x070c
#घोषणा AFE_ASRC2_CON4            0x0710
#घोषणा AFE_ASRC2_CON5            0x0714
#घोषणा AFE_ASRC2_CON6            0x0718
#घोषणा AFE_ASRC2_CON7            0x071c
#घोषणा AFE_ASRC2_CON8            0x0720
#घोषणा AFE_ASRC2_CON9            0x0724
#घोषणा AFE_ASRC2_CON10           0x0728
#घोषणा AFE_ASRC2_CON11           0x072c
#घोषणा AFE_ASRC2_CON12           0x0730
#घोषणा AFE_ASRC2_CON13           0x0734
#घोषणा AFE_ASRC2_CON14           0x0738
#घोषणा AFE_ASRC3_CON0            0x0740
#घोषणा AFE_ASRC3_CON1            0x0744
#घोषणा AFE_ASRC3_CON2            0x0748
#घोषणा AFE_ASRC3_CON3            0x074c
#घोषणा AFE_ASRC3_CON4            0x0750
#घोषणा AFE_ASRC3_CON5            0x0754
#घोषणा AFE_ASRC3_CON6            0x0758
#घोषणा AFE_ASRC3_CON7            0x075c
#घोषणा AFE_ASRC3_CON8            0x0760
#घोषणा AFE_ASRC3_CON9            0x0764
#घोषणा AFE_ASRC3_CON10           0x0768
#घोषणा AFE_ASRC3_CON11           0x076c
#घोषणा AFE_ASRC3_CON12           0x0770
#घोषणा AFE_ASRC3_CON13           0x0774
#घोषणा AFE_ASRC3_CON14           0x0778
#घोषणा AFE_GENERAL_REG0          0x0800
#घोषणा AFE_GENERAL_REG1          0x0804
#घोषणा AFE_GENERAL_REG2          0x0808
#घोषणा AFE_GENERAL_REG3          0x080c
#घोषणा AFE_GENERAL_REG4          0x0810
#घोषणा AFE_GENERAL_REG5          0x0814
#घोषणा AFE_GENERAL_REG6          0x0818
#घोषणा AFE_GENERAL_REG7          0x081c
#घोषणा AFE_GENERAL_REG8          0x0820
#घोषणा AFE_GENERAL_REG9          0x0824
#घोषणा AFE_GENERAL_REG10         0x0828
#घोषणा AFE_GENERAL_REG11         0x082c
#घोषणा AFE_GENERAL_REG12         0x0830
#घोषणा AFE_GENERAL_REG13         0x0834
#घोषणा AFE_GENERAL_REG14         0x0838
#घोषणा AFE_GENERAL_REG15         0x083c
#घोषणा AFE_CBIP_CFG0             0x0840
#घोषणा AFE_CBIP_MON0             0x0844
#घोषणा AFE_CBIP_SLV_MUX_MON0     0x0848
#घोषणा AFE_CBIP_SLV_DECODER_MON0 0x084c

#घोषणा AFE_MAX_REGISTER AFE_CBIP_SLV_DECODER_MON0
#घोषणा AFE_IRQ_STATUS_BITS 0x5f

/* AUDIO_TOP_CON0 */
#घोषणा AHB_IDLE_EN_INT_SFT                                 30
#घोषणा AHB_IDLE_EN_INT_MASK                                0x1
#घोषणा AHB_IDLE_EN_INT_MASK_SFT                            (0x1 << 30)
#घोषणा AHB_IDLE_EN_EXT_SFT                                 29
#घोषणा AHB_IDLE_EN_EXT_MASK                                0x1
#घोषणा AHB_IDLE_EN_EXT_MASK_SFT                            (0x1 << 29)
#घोषणा PDN_TML_SFT                                         27
#घोषणा PDN_TML_MASK                                        0x1
#घोषणा PDN_TML_MASK_SFT                                    (0x1 << 27)
#घोषणा PDN_DAC_PREDIS_SFT                                  26
#घोषणा PDN_DAC_PREDIS_MASK                                 0x1
#घोषणा PDN_DAC_PREDIS_MASK_SFT                             (0x1 << 26)
#घोषणा PDN_DAC_SFT                                         25
#घोषणा PDN_DAC_MASK                                        0x1
#घोषणा PDN_DAC_MASK_SFT                                    (0x1 << 25)
#घोषणा PDN_ADC_SFT                                         24
#घोषणा PDN_ADC_MASK                                        0x1
#घोषणा PDN_ADC_MASK_SFT                                    (0x1 << 24)
#घोषणा PDN_TDM_CK_SFT                                      20
#घोषणा PDN_TDM_CK_MASK                                     0x1
#घोषणा PDN_TDM_CK_MASK_SFT                                 (0x1 << 20)
#घोषणा PDN_APLL_TUNER_SFT                                  19
#घोषणा PDN_APLL_TUNER_MASK                                 0x1
#घोषणा PDN_APLL_TUNER_MASK_SFT                             (0x1 << 19)
#घोषणा PDN_APLL2_TUNER_SFT                                 18
#घोषणा PDN_APLL2_TUNER_MASK                                0x1
#घोषणा PDN_APLL2_TUNER_MASK_SFT                            (0x1 << 18)
#घोषणा APB3_SEL_SFT                                        14
#घोषणा APB3_SEL_MASK                                       0x1
#घोषणा APB3_SEL_MASK_SFT                                   (0x1 << 14)
#घोषणा APB_R2T_SFT                                         13
#घोषणा APB_R2T_MASK                                        0x1
#घोषणा APB_R2T_MASK_SFT                                    (0x1 << 13)
#घोषणा APB_W2T_SFT                                         12
#घोषणा APB_W2T_MASK                                        0x1
#घोषणा APB_W2T_MASK_SFT                                    (0x1 << 12)
#घोषणा PDN_24M_SFT                                         9
#घोषणा PDN_24M_MASK                                        0x1
#घोषणा PDN_24M_MASK_SFT                                    (0x1 << 9)
#घोषणा PDN_22M_SFT                                         8
#घोषणा PDN_22M_MASK                                        0x1
#घोषणा PDN_22M_MASK_SFT                                    (0x1 << 8)
#घोषणा PDN_ADDA4_ADC_SFT                                   7
#घोषणा PDN_ADDA4_ADC_MASK                                  0x1
#घोषणा PDN_ADDA4_ADC_MASK_SFT                              (0x1 << 7)
#घोषणा PDN_I2S_SFT                                         6
#घोषणा PDN_I2S_MASK                                        0x1
#घोषणा PDN_I2S_MASK_SFT                                    (0x1 << 6)
#घोषणा PDN_AFE_SFT                                         2
#घोषणा PDN_AFE_MASK                                        0x1
#घोषणा PDN_AFE_MASK_SFT                                    (0x1 << 2)

/* AUDIO_TOP_CON1 */
#घोषणा PDN_ADC_HIRES_TML_SFT                               17
#घोषणा PDN_ADC_HIRES_TML_MASK                              0x1
#घोषणा PDN_ADC_HIRES_TML_MASK_SFT                          (0x1 << 17)
#घोषणा PDN_ADC_HIRES_SFT                                   16
#घोषणा PDN_ADC_HIRES_MASK                                  0x1
#घोषणा PDN_ADC_HIRES_MASK_SFT                              (0x1 << 16)
#घोषणा I2S4_BCLK_SW_CG_SFT                                 7
#घोषणा I2S4_BCLK_SW_CG_MASK                                0x1
#घोषणा I2S4_BCLK_SW_CG_MASK_SFT                            (0x1 << 7)
#घोषणा I2S3_BCLK_SW_CG_SFT                                 6
#घोषणा I2S3_BCLK_SW_CG_MASK                                0x1
#घोषणा I2S3_BCLK_SW_CG_MASK_SFT                            (0x1 << 6)
#घोषणा I2S2_BCLK_SW_CG_SFT                                 5
#घोषणा I2S2_BCLK_SW_CG_MASK                                0x1
#घोषणा I2S2_BCLK_SW_CG_MASK_SFT                            (0x1 << 5)
#घोषणा I2S1_BCLK_SW_CG_SFT                                 4
#घोषणा I2S1_BCLK_SW_CG_MASK                                0x1
#घोषणा I2S1_BCLK_SW_CG_MASK_SFT                            (0x1 << 4)
#घोषणा I2S_SOFT_RST2_SFT                                   2
#घोषणा I2S_SOFT_RST2_MASK                                  0x1
#घोषणा I2S_SOFT_RST2_MASK_SFT                              (0x1 << 2)
#घोषणा I2S_SOFT_RST_SFT                                    1
#घोषणा I2S_SOFT_RST_MASK                                   0x1
#घोषणा I2S_SOFT_RST_MASK_SFT                               (0x1 << 1)

/* AFE_DAC_CON0 */
#घोषणा AFE_AWB_RETM_SFT                                    31
#घोषणा AFE_AWB_RETM_MASK                                   0x1
#घोषणा AFE_AWB_RETM_MASK_SFT                               (0x1 << 31)
#घोषणा AFE_DL1_DATA2_RETM_SFT                              30
#घोषणा AFE_DL1_DATA2_RETM_MASK                             0x1
#घोषणा AFE_DL1_DATA2_RETM_MASK_SFT                         (0x1 << 30)
#घोषणा AFE_DL2_RETM_SFT                                    29
#घोषणा AFE_DL2_RETM_MASK                                   0x1
#घोषणा AFE_DL2_RETM_MASK_SFT                               (0x1 << 29)
#घोषणा AFE_DL1_RETM_SFT                                    28
#घोषणा AFE_DL1_RETM_MASK                                   0x1
#घोषणा AFE_DL1_RETM_MASK_SFT                               (0x1 << 28)
#घोषणा AFE_ON_RETM_SFT                                     27
#घोषणा AFE_ON_RETM_MASK                                    0x1
#घोषणा AFE_ON_RETM_MASK_SFT                                (0x1 << 27)
#घोषणा MOD_DAI_DUP_WR_SFT                                  26
#घोषणा MOD_DAI_DUP_WR_MASK                                 0x1
#घोषणा MOD_DAI_DUP_WR_MASK_SFT                             (0x1 << 26)
#घोषणा DAI_MODE_SFT                                        24
#घोषणा DAI_MODE_MASK                                       0x3
#घोषणा DAI_MODE_MASK_SFT                                   (0x3 << 24)
#घोषणा VUL_DATA2_MODE_SFT                                  20
#घोषणा VUL_DATA2_MODE_MASK                                 0xf
#घोषणा VUL_DATA2_MODE_MASK_SFT                             (0xf << 20)
#घोषणा DL1_DATA2_MODE_SFT                                  16
#घोषणा DL1_DATA2_MODE_MASK                                 0xf
#घोषणा DL1_DATA2_MODE_MASK_SFT                             (0xf << 16)
#घोषणा DL3_MODE_SFT                                        12
#घोषणा DL3_MODE_MASK                                       0xf
#घोषणा DL3_MODE_MASK_SFT                                   (0xf << 12)
#घोषणा VUL_DATA2_R_MONO_SFT                                11
#घोषणा VUL_DATA2_R_MONO_MASK                               0x1
#घोषणा VUL_DATA2_R_MONO_MASK_SFT                           (0x1 << 11)
#घोषणा VUL_DATA2_DATA_SFT                                  10
#घोषणा VUL_DATA2_DATA_MASK                                 0x1
#घोषणा VUL_DATA2_DATA_MASK_SFT                             (0x1 << 10)
#घोषणा VUL_DATA2_ON_SFT                                    9
#घोषणा VUL_DATA2_ON_MASK                                   0x1
#घोषणा VUL_DATA2_ON_MASK_SFT                               (0x1 << 9)
#घोषणा DL1_DATA2_ON_SFT                                    8
#घोषणा DL1_DATA2_ON_MASK                                   0x1
#घोषणा DL1_DATA2_ON_MASK_SFT                               (0x1 << 8)
#घोषणा MOD_DAI_ON_SFT                                      7
#घोषणा MOD_DAI_ON_MASK                                     0x1
#घोषणा MOD_DAI_ON_MASK_SFT                                 (0x1 << 7)
#घोषणा AWB_ON_SFT                                          6
#घोषणा AWB_ON_MASK                                         0x1
#घोषणा AWB_ON_MASK_SFT                                     (0x1 << 6)
#घोषणा DL3_ON_SFT                                          5
#घोषणा DL3_ON_MASK                                         0x1
#घोषणा DL3_ON_MASK_SFT                                     (0x1 << 5)
#घोषणा DAI_ON_SFT                                          4
#घोषणा DAI_ON_MASK                                         0x1
#घोषणा DAI_ON_MASK_SFT                                     (0x1 << 4)
#घोषणा VUL_ON_SFT                                          3
#घोषणा VUL_ON_MASK                                         0x1
#घोषणा VUL_ON_MASK_SFT                                     (0x1 << 3)
#घोषणा DL2_ON_SFT                                          2
#घोषणा DL2_ON_MASK                                         0x1
#घोषणा DL2_ON_MASK_SFT                                     (0x1 << 2)
#घोषणा DL1_ON_SFT                                          1
#घोषणा DL1_ON_MASK                                         0x1
#घोषणा DL1_ON_MASK_SFT                                     (0x1 << 1)
#घोषणा AFE_ON_SFT                                          0
#घोषणा AFE_ON_MASK                                         0x1
#घोषणा AFE_ON_MASK_SFT                                     (0x1 << 0)

/* AFE_DAC_CON1 */
#घोषणा MOD_DAI_MODE_SFT                                    30
#घोषणा MOD_DAI_MODE_MASK                                   0x3
#घोषणा MOD_DAI_MODE_MASK_SFT                               (0x3 << 30)
#घोषणा DAI_DUP_WR_SFT                                      29
#घोषणा DAI_DUP_WR_MASK                                     0x1
#घोषणा DAI_DUP_WR_MASK_SFT                                 (0x1 << 29)
#घोषणा VUL_R_MONO_SFT                                      28
#घोषणा VUL_R_MONO_MASK                                     0x1
#घोषणा VUL_R_MONO_MASK_SFT                                 (0x1 << 28)
#घोषणा VUL_DATA_SFT                                        27
#घोषणा VUL_DATA_MASK                                       0x1
#घोषणा VUL_DATA_MASK_SFT                                   (0x1 << 27)
#घोषणा AXI_2X1_CG_DISABLE_SFT                              26
#घोषणा AXI_2X1_CG_DISABLE_MASK                             0x1
#घोषणा AXI_2X1_CG_DISABLE_MASK_SFT                         (0x1 << 26)
#घोषणा AWB_R_MONO_SFT                                      25
#घोषणा AWB_R_MONO_MASK                                     0x1
#घोषणा AWB_R_MONO_MASK_SFT                                 (0x1 << 25)
#घोषणा AWB_DATA_SFT                                        24
#घोषणा AWB_DATA_MASK                                       0x1
#घोषणा AWB_DATA_MASK_SFT                                   (0x1 << 24)
#घोषणा DL3_DATA_SFT                                        23
#घोषणा DL3_DATA_MASK                                       0x1
#घोषणा DL3_DATA_MASK_SFT                                   (0x1 << 23)
#घोषणा DL2_DATA_SFT                                        22
#घोषणा DL2_DATA_MASK                                       0x1
#घोषणा DL2_DATA_MASK_SFT                                   (0x1 << 22)
#घोषणा DL1_DATA_SFT                                        21
#घोषणा DL1_DATA_MASK                                       0x1
#घोषणा DL1_DATA_MASK_SFT                                   (0x1 << 21)
#घोषणा DL1_DATA2_DATA_SFT                                  20
#घोषणा DL1_DATA2_DATA_MASK                                 0x1
#घोषणा DL1_DATA2_DATA_MASK_SFT                             (0x1 << 20)
#घोषणा VUL_MODE_SFT                                        16
#घोषणा VUL_MODE_MASK                                       0xf
#घोषणा VUL_MODE_MASK_SFT                                   (0xf << 16)
#घोषणा AWB_MODE_SFT                                        12
#घोषणा AWB_MODE_MASK                                       0xf
#घोषणा AWB_MODE_MASK_SFT                                   (0xf << 12)
#घोषणा I2S_MODE_SFT                                        8
#घोषणा I2S_MODE_MASK                                       0xf
#घोषणा I2S_MODE_MASK_SFT                                   (0xf << 8)
#घोषणा DL2_MODE_SFT                                        4
#घोषणा DL2_MODE_MASK                                       0xf
#घोषणा DL2_MODE_MASK_SFT                                   (0xf << 4)
#घोषणा DL1_MODE_SFT                                        0
#घोषणा DL1_MODE_MASK                                       0xf
#घोषणा DL1_MODE_MASK_SFT                                   (0xf << 0)

/* AFE_ADDA_DL_SRC2_CON0 */
#घोषणा DL_2_INPUT_MODE_CTL_SFT                             28
#घोषणा DL_2_INPUT_MODE_CTL_MASK                            0xf
#घोषणा DL_2_INPUT_MODE_CTL_MASK_SFT                        (0xf << 28)
#घोषणा DL_2_CH1_SATURATION_EN_CTL_SFT                      27
#घोषणा DL_2_CH1_SATURATION_EN_CTL_MASK                     0x1
#घोषणा DL_2_CH1_SATURATION_EN_CTL_MASK_SFT                 (0x1 << 27)
#घोषणा DL_2_CH2_SATURATION_EN_CTL_SFT                      26
#घोषणा DL_2_CH2_SATURATION_EN_CTL_MASK                     0x1
#घोषणा DL_2_CH2_SATURATION_EN_CTL_MASK_SFT                 (0x1 << 26)
#घोषणा DL_2_OUTPUT_SEL_CTL_SFT                             24
#घोषणा DL_2_OUTPUT_SEL_CTL_MASK                            0x3
#घोषणा DL_2_OUTPUT_SEL_CTL_MASK_SFT                        (0x3 << 24)
#घोषणा DL_2_FADEIN_0START_EN_SFT                           16
#घोषणा DL_2_FADEIN_0START_EN_MASK                          0x3
#घोषणा DL_2_FADEIN_0START_EN_MASK_SFT                      (0x3 << 16)
#घोषणा DL_DISABLE_HW_CG_CTL_SFT                            15
#घोषणा DL_DISABLE_HW_CG_CTL_MASK                           0x1
#घोषणा DL_DISABLE_HW_CG_CTL_MASK_SFT                       (0x1 << 15)
#घोषणा C_DATA_EN_SEL_CTL_PRE_SFT                           14
#घोषणा C_DATA_EN_SEL_CTL_PRE_MASK                          0x1
#घोषणा C_DATA_EN_SEL_CTL_PRE_MASK_SFT                      (0x1 << 14)
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_SFT                       13
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_MASK                      0x1
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_MASK_SFT                  (0x1 << 13)
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_SFT                       12
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_MASK                      0x1
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_MASK_SFT                  (0x1 << 12)
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_SFT                       11
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_MASK                      0x1
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_MASK_SFT                  (0x1 << 11)
#घोषणा DL2_ARAMPSP_CTL_PRE_SFT                             9
#घोषणा DL2_ARAMPSP_CTL_PRE_MASK                            0x3
#घोषणा DL2_ARAMPSP_CTL_PRE_MASK_SFT                        (0x3 << 9)
#घोषणा DL_2_IIRMODE_CTL_PRE_SFT                            6
#घोषणा DL_2_IIRMODE_CTL_PRE_MASK                           0x7
#घोषणा DL_2_IIRMODE_CTL_PRE_MASK_SFT                       (0x7 << 6)
#घोषणा DL_2_VOICE_MODE_CTL_PRE_SFT                         5
#घोषणा DL_2_VOICE_MODE_CTL_PRE_MASK                        0x1
#घोषणा DL_2_VOICE_MODE_CTL_PRE_MASK_SFT                    (0x1 << 5)
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_SFT                        4
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_MASK                       0x1
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_MASK_SFT                   (0x1 << 4)
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_SFT                        3
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_MASK                       0x1
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_MASK_SFT                   (0x1 << 3)
#घोषणा DL_2_IIR_ON_CTL_PRE_SFT                             2
#घोषणा DL_2_IIR_ON_CTL_PRE_MASK                            0x1
#घोषणा DL_2_IIR_ON_CTL_PRE_MASK_SFT                        (0x1 << 2)
#घोषणा DL_2_GAIN_ON_CTL_PRE_SFT                            1
#घोषणा DL_2_GAIN_ON_CTL_PRE_MASK                           0x1
#घोषणा DL_2_GAIN_ON_CTL_PRE_MASK_SFT                       (0x1 << 1)
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_SFT                         0
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK                        0x1
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK_SFT                    (0x1 << 0)

/* AFE_ADDA_DL_SRC2_CON1 */
#घोषणा DL_2_GAIN_CTL_PRE_SFT                               16
#घोषणा DL_2_GAIN_CTL_PRE_MASK                              0xffff
#घोषणा DL_2_GAIN_CTL_PRE_MASK_SFT                          (0xffff << 16)
#घोषणा DL_2_GAIN_MODE_CTL_SFT                              0
#घोषणा DL_2_GAIN_MODE_CTL_MASK                             0x1
#घोषणा DL_2_GAIN_MODE_CTL_MASK_SFT                         (0x1 << 0)

/* AFE_ADDA_UL_SRC_CON0 */
#घोषणा C_COMB_OUT_SIN_GEN_CTL_SFT                          31
#घोषणा C_COMB_OUT_SIN_GEN_CTL_MASK                         0x1
#घोषणा C_COMB_OUT_SIN_GEN_CTL_MASK_SFT                     (0x1 << 31)
#घोषणा C_BASEBAND_SIN_GEN_CTL_SFT                          30
#घोषणा C_BASEBAND_SIN_GEN_CTL_MASK                         0x1
#घोषणा C_BASEBAND_SIN_GEN_CTL_MASK_SFT                     (0x1 << 30)
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_SFT                      27
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_MASK                     0x7
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_MASK_SFT                 (0x7 << 27)
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_SFT                      24
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_MASK                     0x7
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_MASK_SFT                 (0x7 << 24)
#घोषणा C_TWO_DIGITAL_MIC_CTL_SFT                           23
#घोषणा C_TWO_DIGITAL_MIC_CTL_MASK                          0x1
#घोषणा C_TWO_DIGITAL_MIC_CTL_MASK_SFT                      (0x1 << 23)
#घोषणा UL_MODE_3P25M_CH2_CTL_SFT                           22
#घोषणा UL_MODE_3P25M_CH2_CTL_MASK                          0x1
#घोषणा UL_MODE_3P25M_CH2_CTL_MASK_SFT                      (0x1 << 22)
#घोषणा UL_MODE_3P25M_CH1_CTL_SFT                           21
#घोषणा UL_MODE_3P25M_CH1_CTL_MASK                          0x1
#घोषणा UL_MODE_3P25M_CH1_CTL_MASK_SFT                      (0x1 << 21)
#घोषणा UL_SRC_USE_CIC_OUT_CTL_SFT                          20
#घोषणा UL_SRC_USE_CIC_OUT_CTL_MASK                         0x1
#घोषणा UL_SRC_USE_CIC_OUT_CTL_MASK_SFT                     (0x1 << 20)
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_SFT                       17
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_MASK                      0x7
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_MASK_SFT                  (0x7 << 17)
#घोषणा DMIC_LOW_POWER_MODE_CTL_SFT                         14
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK                        0x3
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK_SFT                    (0x3 << 14)
#घोषणा DMIC_48K_SEL_CTL_SFT                                13
#घोषणा DMIC_48K_SEL_CTL_MASK                               0x1
#घोषणा DMIC_48K_SEL_CTL_MASK_SFT                           (0x1 << 13)
#घोषणा UL_DISABLE_HW_CG_CTL_SFT                            12
#घोषणा UL_DISABLE_HW_CG_CTL_MASK                           0x1
#घोषणा UL_DISABLE_HW_CG_CTL_MASK_SFT                       (0x1 << 12)
#घोषणा UL_IIR_ON_TMP_CTL_SFT                               10
#घोषणा UL_IIR_ON_TMP_CTL_MASK                              0x1
#घोषणा UL_IIR_ON_TMP_CTL_MASK_SFT                          (0x1 << 10)
#घोषणा UL_IIRMODE_CTL_SFT                                  7
#घोषणा UL_IIRMODE_CTL_MASK                                 0x7
#घोषणा UL_IIRMODE_CTL_MASK_SFT                             (0x7 << 7)
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_SFT                     5
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK                    0x1
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK_SFT                (0x1 << 5)
#घोषणा AGC_260K_SEL_CH2_CTL_SFT                            4
#घोषणा AGC_260K_SEL_CH2_CTL_MASK                           0x1
#घोषणा AGC_260K_SEL_CH2_CTL_MASK_SFT                       (0x1 << 4)
#घोषणा AGC_260K_SEL_CH1_CTL_SFT                            3
#घोषणा AGC_260K_SEL_CH1_CTL_MASK                           0x1
#घोषणा AGC_260K_SEL_CH1_CTL_MASK_SFT                       (0x1 << 3)
#घोषणा UL_LOOP_BACK_MODE_CTL_SFT                           2
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK                          0x1
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK_SFT                      (0x1 << 2)
#घोषणा UL_SDM_3_LEVEL_CTL_SFT                              1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK                             0x1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK_SFT                         (0x1 << 1)
#घोषणा UL_SRC_ON_TMP_CTL_SFT                               0
#घोषणा UL_SRC_ON_TMP_CTL_MASK                              0x1
#घोषणा UL_SRC_ON_TMP_CTL_MASK_SFT                          (0x1 << 0)

/* AFE_ADDA_UL_SRC_CON1 */
#घोषणा C_SDM_RESET_CTL_SFT                                 31
#घोषणा C_SDM_RESET_CTL_MASK                                0x1
#घोषणा C_SDM_RESET_CTL_MASK_SFT                            (0x1 << 31)
#घोषणा ADITHON_CTL_SFT                                     30
#घोषणा ADITHON_CTL_MASK                                    0x1
#घोषणा ADITHON_CTL_MASK_SFT                                (0x1 << 30)
#घोषणा ADITHVAL_CTL_SFT                                    28
#घोषणा ADITHVAL_CTL_MASK                                   0x3
#घोषणा ADITHVAL_CTL_MASK_SFT                               (0x3 << 28)
#घोषणा C_DAC_EN_CTL_SFT                                    27
#घोषणा C_DAC_EN_CTL_MASK                                   0x1
#घोषणा C_DAC_EN_CTL_MASK_SFT                               (0x1 << 27)
#घोषणा C_MUTE_SW_CTL_SFT                                   26
#घोषणा C_MUTE_SW_CTL_MASK                                  0x1
#घोषणा C_MUTE_SW_CTL_MASK_SFT                              (0x1 << 26)
#घोषणा ASDM_SRC_SEL_CTL_SFT                                25
#घोषणा ASDM_SRC_SEL_CTL_MASK                               0x1
#घोषणा ASDM_SRC_SEL_CTL_MASK_SFT                           (0x1 << 25)
#घोषणा C_AMP_DIV_CH2_CTL_SFT                               21
#घोषणा C_AMP_DIV_CH2_CTL_MASK                              0x7
#घोषणा C_AMP_DIV_CH2_CTL_MASK_SFT                          (0x7 << 21)
#घोषणा C_FREQ_DIV_CH2_CTL_SFT                              16
#घोषणा C_FREQ_DIV_CH2_CTL_MASK                             0x1f
#घोषणा C_FREQ_DIV_CH2_CTL_MASK_SFT                         (0x1f << 16)
#घोषणा C_SINE_MODE_CH2_CTL_SFT                             12
#घोषणा C_SINE_MODE_CH2_CTL_MASK                            0xf
#घोषणा C_SINE_MODE_CH2_CTL_MASK_SFT                        (0xf << 12)
#घोषणा C_AMP_DIV_CH1_CTL_SFT                               9
#घोषणा C_AMP_DIV_CH1_CTL_MASK                              0x7
#घोषणा C_AMP_DIV_CH1_CTL_MASK_SFT                          (0x7 << 9)
#घोषणा C_FREQ_DIV_CH1_CTL_SFT                              4
#घोषणा C_FREQ_DIV_CH1_CTL_MASK                             0x1f
#घोषणा C_FREQ_DIV_CH1_CTL_MASK_SFT                         (0x1f << 4)
#घोषणा C_SINE_MODE_CH1_CTL_SFT                             0
#घोषणा C_SINE_MODE_CH1_CTL_MASK                            0xf
#घोषणा C_SINE_MODE_CH1_CTL_MASK_SFT                        (0xf << 0)

/* AFE_ADDA_TOP_CON0 */
#घोषणा C_LOOP_BACK_MODE_CTL_SFT                            12
#घोषणा C_LOOP_BACK_MODE_CTL_MASK                           0xf
#घोषणा C_LOOP_BACK_MODE_CTL_MASK_SFT                       (0xf << 12)
#घोषणा C_EXT_ADC_CTL_SFT                                   0
#घोषणा C_EXT_ADC_CTL_MASK                                  0x1
#घोषणा C_EXT_ADC_CTL_MASK_SFT                              (0x1 << 0)

/* AFE_ADDA_UL_DL_CON0 */
#घोषणा AFE_UL_DL_CON0_RESERVED_SFT                         1
#घोषणा AFE_UL_DL_CON0_RESERVED_MASK                        0x3fff
#घोषणा AFE_UL_DL_CON0_RESERVED_MASK_SFT                    (0x3fff << 1)
#घोषणा ADDA_AFE_ON_SFT                                     0
#घोषणा ADDA_AFE_ON_MASK                                    0x1
#घोषणा ADDA_AFE_ON_MASK_SFT                                (0x1 << 0)

/* AFE_IRQ_MCU_CON */
#घोषणा IRQ7_MCU_MODE_SFT                                   24
#घोषणा IRQ7_MCU_MODE_MASK                                  0xf
#घोषणा IRQ7_MCU_MODE_MASK_SFT                              (0xf << 24)
#घोषणा IRQ4_MCU_MODE_SFT                                   20
#घोषणा IRQ4_MCU_MODE_MASK                                  0xf
#घोषणा IRQ4_MCU_MODE_MASK_SFT                              (0xf << 20)
#घोषणा IRQ3_MCU_MODE_SFT                                   16
#घोषणा IRQ3_MCU_MODE_MASK                                  0xf
#घोषणा IRQ3_MCU_MODE_MASK_SFT                              (0xf << 16)
#घोषणा IRQ7_MCU_ON_SFT                                     14
#घोषणा IRQ7_MCU_ON_MASK                                    0x1
#घोषणा IRQ7_MCU_ON_MASK_SFT                                (0x1 << 14)
#घोषणा IRQ5_MCU_ON_SFT                                     12
#घोषणा IRQ5_MCU_ON_MASK                                    0x1
#घोषणा IRQ5_MCU_ON_MASK_SFT                                (0x1 << 12)
#घोषणा IRQ2_MCU_MODE_SFT                                   8
#घोषणा IRQ2_MCU_MODE_MASK                                  0xf
#घोषणा IRQ2_MCU_MODE_MASK_SFT                              (0xf << 8)
#घोषणा IRQ1_MCU_MODE_SFT                                   4
#घोषणा IRQ1_MCU_MODE_MASK                                  0xf
#घोषणा IRQ1_MCU_MODE_MASK_SFT                              (0xf << 4)
#घोषणा IRQ4_MCU_ON_SFT                                     3
#घोषणा IRQ4_MCU_ON_MASK                                    0x1
#घोषणा IRQ4_MCU_ON_MASK_SFT                                (0x1 << 3)
#घोषणा IRQ3_MCU_ON_SFT                                     2
#घोषणा IRQ3_MCU_ON_MASK                                    0x1
#घोषणा IRQ3_MCU_ON_MASK_SFT                                (0x1 << 2)
#घोषणा IRQ2_MCU_ON_SFT                                     1
#घोषणा IRQ2_MCU_ON_MASK                                    0x1
#घोषणा IRQ2_MCU_ON_MASK_SFT                                (0x1 << 1)
#घोषणा IRQ1_MCU_ON_SFT                                     0
#घोषणा IRQ1_MCU_ON_MASK                                    0x1
#घोषणा IRQ1_MCU_ON_MASK_SFT                                (0x1 << 0)

/* AFE_IRQ_MCU_EN */
#घोषणा AFE_IRQ_CM4_EN_SFT                                  16
#घोषणा AFE_IRQ_CM4_EN_MASK                                 0x7f
#घोषणा AFE_IRQ_CM4_EN_MASK_SFT                             (0x7f << 16)
#घोषणा AFE_IRQ_MD32_EN_SFT                                 8
#घोषणा AFE_IRQ_MD32_EN_MASK                                0x7f
#घोषणा AFE_IRQ_MD32_EN_MASK_SFT                            (0x7f << 8)
#घोषणा AFE_IRQ_MCU_EN_SFT                                  0
#घोषणा AFE_IRQ_MCU_EN_MASK                                 0x7f
#घोषणा AFE_IRQ_MCU_EN_MASK_SFT                             (0x7f << 0)

/* AFE_IRQ_MCU_CLR */
#घोषणा IRQ7_MCU_CLR_SFT                                    6
#घोषणा IRQ7_MCU_CLR_MASK                                   0x1
#घोषणा IRQ7_MCU_CLR_MASK_SFT                               (0x1 << 6)
#घोषणा IRQ5_MCU_CLR_SFT                                    4
#घोषणा IRQ5_MCU_CLR_MASK                                   0x1
#घोषणा IRQ5_MCU_CLR_MASK_SFT                               (0x1 << 4)
#घोषणा IRQ4_MCU_CLR_SFT                                    3
#घोषणा IRQ4_MCU_CLR_MASK                                   0x1
#घोषणा IRQ4_MCU_CLR_MASK_SFT                               (0x1 << 3)
#घोषणा IRQ3_MCU_CLR_SFT                                    2
#घोषणा IRQ3_MCU_CLR_MASK                                   0x1
#घोषणा IRQ3_MCU_CLR_MASK_SFT                               (0x1 << 2)
#घोषणा IRQ2_MCU_CLR_SFT                                    1
#घोषणा IRQ2_MCU_CLR_MASK                                   0x1
#घोषणा IRQ2_MCU_CLR_MASK_SFT                               (0x1 << 1)
#घोषणा IRQ1_MCU_CLR_SFT                                    0
#घोषणा IRQ1_MCU_CLR_MASK                                   0x1
#घोषणा IRQ1_MCU_CLR_MASK_SFT                               (0x1 << 0)

/* AFE_IRQ_MCU_CNT1 */
#घोषणा AFE_IRQ_MCU_CNT1_SFT                                0
#घोषणा AFE_IRQ_MCU_CNT1_MASK                               0x3ffff
#घोषणा AFE_IRQ_MCU_CNT1_MASK_SFT                           (0x3ffff << 0)

/* AFE_IRQ_MCU_CNT2 */
#घोषणा AFE_IRQ_MCU_CNT2_SFT                                0
#घोषणा AFE_IRQ_MCU_CNT2_MASK                               0x3ffff
#घोषणा AFE_IRQ_MCU_CNT2_MASK_SFT                           (0x3ffff << 0)

/* AFE_IRQ_MCU_CNT3 */
#घोषणा AFE_IRQ_MCU_CNT3_SFT                                0
#घोषणा AFE_IRQ_MCU_CNT3_MASK                               0x3ffff
#घोषणा AFE_IRQ_MCU_CNT3_MASK_SFT                           (0x3ffff << 0)

/* AFE_IRQ_MCU_CNT4 */
#घोषणा AFE_IRQ_MCU_CNT4_SFT                                0
#घोषणा AFE_IRQ_MCU_CNT4_MASK                               0x3ffff
#घोषणा AFE_IRQ_MCU_CNT4_MASK_SFT                           (0x3ffff << 0)

/* AFE_IRQ_MCU_CNT5 */
#घोषणा AFE_IRQ_MCU_CNT5_SFT                                0
#घोषणा AFE_IRQ_MCU_CNT5_MASK                               0x3ffff
#घोषणा AFE_IRQ_MCU_CNT5_MASK_SFT                           (0x3ffff << 0)

/* AFE_IRQ_MCU_CNT7 */
#घोषणा AFE_IRQ_MCU_CNT7_SFT                                0
#घोषणा AFE_IRQ_MCU_CNT7_MASK                               0x3ffff
#घोषणा AFE_IRQ_MCU_CNT7_MASK_SFT                           (0x3ffff << 0)

/* AFE_MEMIF_MSB */
#घोषणा CPU_COMPACT_MODE_SFT                                23
#घोषणा CPU_COMPACT_MODE_MASK                               0x1
#घोषणा CPU_COMPACT_MODE_MASK_SFT                           (0x1 << 23)
#घोषणा CPU_HD_ALIGN_SFT                                    22
#घोषणा CPU_HD_ALIGN_MASK                                   0x1
#घोषणा CPU_HD_ALIGN_MASK_SFT                               (0x1 << 22)

/* AFE_MEMIF_HD_MODE */
#घोषणा HDMI_HD_SFT                                         20
#घोषणा HDMI_HD_MASK                                        0x3
#घोषणा HDMI_HD_MASK_SFT                                    (0x3 << 20)
#घोषणा MOD_DAI_HD_SFT                                      18
#घोषणा MOD_DAI_HD_MASK                                     0x3
#घोषणा MOD_DAI_HD_MASK_SFT                                 (0x3 << 18)
#घोषणा DAI_HD_SFT                                          16
#घोषणा DAI_HD_MASK                                         0x3
#घोषणा DAI_HD_MASK_SFT                                     (0x3 << 16)
#घोषणा VUL_DATA2_HD_SFT                                    12
#घोषणा VUL_DATA2_HD_MASK                                   0x3
#घोषणा VUL_DATA2_HD_MASK_SFT                               (0x3 << 12)
#घोषणा VUL_HD_SFT                                          10
#घोषणा VUL_HD_MASK                                         0x3
#घोषणा VUL_HD_MASK_SFT                                     (0x3 << 10)
#घोषणा AWB_HD_SFT                                          8
#घोषणा AWB_HD_MASK                                         0x3
#घोषणा AWB_HD_MASK_SFT                                     (0x3 << 8)
#घोषणा DL3_HD_SFT                                          6
#घोषणा DL3_HD_MASK                                         0x3
#घोषणा DL3_HD_MASK_SFT                                     (0x3 << 6)
#घोषणा DL2_HD_SFT                                          4
#घोषणा DL2_HD_MASK                                         0x3
#घोषणा DL2_HD_MASK_SFT                                     (0x3 << 4)
#घोषणा DL1_DATA2_HD_SFT                                    2
#घोषणा DL1_DATA2_HD_MASK                                   0x3
#घोषणा DL1_DATA2_HD_MASK_SFT                               (0x3 << 2)
#घोषणा DL1_HD_SFT                                          0
#घोषणा DL1_HD_MASK                                         0x3
#घोषणा DL1_HD_MASK_SFT                                     (0x3 << 0)

/* AFE_MEMIF_HDALIGN */
#घोषणा HDMI_NORMAL_MODE_SFT                                26
#घोषणा HDMI_NORMAL_MODE_MASK                               0x1
#घोषणा HDMI_NORMAL_MODE_MASK_SFT                           (0x1 << 26)
#घोषणा MOD_DAI_NORMAL_MODE_SFT                             25
#घोषणा MOD_DAI_NORMAL_MODE_MASK                            0x1
#घोषणा MOD_DAI_NORMAL_MODE_MASK_SFT                        (0x1 << 25)
#घोषणा DAI_NORMAL_MODE_SFT                                 24
#घोषणा DAI_NORMAL_MODE_MASK                                0x1
#घोषणा DAI_NORMAL_MODE_MASK_SFT                            (0x1 << 24)
#घोषणा VUL_DATA2_NORMAL_MODE_SFT                           22
#घोषणा VUL_DATA2_NORMAL_MODE_MASK                          0x1
#घोषणा VUL_DATA2_NORMAL_MODE_MASK_SFT                      (0x1 << 22)
#घोषणा VUL_NORMAL_MODE_SFT                                 21
#घोषणा VUL_NORMAL_MODE_MASK                                0x1
#घोषणा VUL_NORMAL_MODE_MASK_SFT                            (0x1 << 21)
#घोषणा AWB_NORMAL_MODE_SFT                                 20
#घोषणा AWB_NORMAL_MODE_MASK                                0x1
#घोषणा AWB_NORMAL_MODE_MASK_SFT                            (0x1 << 20)
#घोषणा DL3_NORMAL_MODE_SFT                                 19
#घोषणा DL3_NORMAL_MODE_MASK                                0x1
#घोषणा DL3_NORMAL_MODE_MASK_SFT                            (0x1 << 19)
#घोषणा DL2_NORMAL_MODE_SFT                                 18
#घोषणा DL2_NORMAL_MODE_MASK                                0x1
#घोषणा DL2_NORMAL_MODE_MASK_SFT                            (0x1 << 18)
#घोषणा DL1_DATA2_NORMAL_MODE_SFT                           17
#घोषणा DL1_DATA2_NORMAL_MODE_MASK                          0x1
#घोषणा DL1_DATA2_NORMAL_MODE_MASK_SFT                      (0x1 << 17)
#घोषणा DL1_NORMAL_MODE_SFT                                 16
#घोषणा DL1_NORMAL_MODE_MASK                                0x1
#घोषणा DL1_NORMAL_MODE_MASK_SFT                            (0x1 << 16)
#घोषणा HDMI_HD_ALIGN_SFT                                   10
#घोषणा HDMI_HD_ALIGN_MASK                                  0x1
#घोषणा HDMI_HD_ALIGN_MASK_SFT                              (0x1 << 10)
#घोषणा MOD_DAI_HD_ALIGN_SFT                                9
#घोषणा MOD_DAI_HD_ALIGN_MASK                               0x1
#घोषणा MOD_DAI_HD_ALIGN_MASK_SFT                           (0x1 << 9)
#घोषणा DAI_ALIGN_SFT                                       8
#घोषणा DAI_ALIGN_MASK                                      0x1
#घोषणा DAI_ALIGN_MASK_SFT                                  (0x1 << 8)
#घोषणा VUL2_HD_ALIGN_SFT                                   7
#घोषणा VUL2_HD_ALIGN_MASK                                  0x1
#घोषणा VUL2_HD_ALIGN_MASK_SFT                              (0x1 << 7)
#घोषणा VUL_DATA2_HD_ALIGN_SFT                              6
#घोषणा VUL_DATA2_HD_ALIGN_MASK                             0x1
#घोषणा VUL_DATA2_HD_ALIGN_MASK_SFT                         (0x1 << 6)
#घोषणा VUL_HD_ALIGN_SFT                                    5
#घोषणा VUL_HD_ALIGN_MASK                                   0x1
#घोषणा VUL_HD_ALIGN_MASK_SFT                               (0x1 << 5)
#घोषणा AWB_HD_ALIGN_SFT                                    4
#घोषणा AWB_HD_ALIGN_MASK                                   0x1
#घोषणा AWB_HD_ALIGN_MASK_SFT                               (0x1 << 4)
#घोषणा DL3_HD_ALIGN_SFT                                    3
#घोषणा DL3_HD_ALIGN_MASK                                   0x1
#घोषणा DL3_HD_ALIGN_MASK_SFT                               (0x1 << 3)
#घोषणा DL2_HD_ALIGN_SFT                                    2
#घोषणा DL2_HD_ALIGN_MASK                                   0x1
#घोषणा DL2_HD_ALIGN_MASK_SFT                               (0x1 << 2)
#घोषणा DL1_DATA2_HD_ALIGN_SFT                              1
#घोषणा DL1_DATA2_HD_ALIGN_MASK                             0x1
#घोषणा DL1_DATA2_HD_ALIGN_MASK_SFT                         (0x1 << 1)
#घोषणा DL1_HD_ALIGN_SFT                                    0
#घोषणा DL1_HD_ALIGN_MASK                                   0x1
#घोषणा DL1_HD_ALIGN_MASK_SFT                               (0x1 << 0)

/* PCM_INTF_CON1 */
#घोषणा PCM_FIX_VALUE_SEL_SFT                               31
#घोषणा PCM_FIX_VALUE_SEL_MASK                              0x1
#घोषणा PCM_FIX_VALUE_SEL_MASK_SFT                          (0x1 << 31)
#घोषणा PCM_BUFFER_LOOPBACK_SFT                             30
#घोषणा PCM_BUFFER_LOOPBACK_MASK                            0x1
#घोषणा PCM_BUFFER_LOOPBACK_MASK_SFT                        (0x1 << 30)
#घोषणा PCM_PARALLEL_LOOPBACK_SFT                           29
#घोषणा PCM_PARALLEL_LOOPBACK_MASK                          0x1
#घोषणा PCM_PARALLEL_LOOPBACK_MASK_SFT                      (0x1 << 29)
#घोषणा PCM_SERIAL_LOOPBACK_SFT                             28
#घोषणा PCM_SERIAL_LOOPBACK_MASK                            0x1
#घोषणा PCM_SERIAL_LOOPBACK_MASK_SFT                        (0x1 << 28)
#घोषणा PCM_DAI_PCM_LOOPBACK_SFT                            27
#घोषणा PCM_DAI_PCM_LOOPBACK_MASK                           0x1
#घोषणा PCM_DAI_PCM_LOOPBACK_MASK_SFT                       (0x1 << 27)
#घोषणा PCM_I2S_PCM_LOOPBACK_SFT                            26
#घोषणा PCM_I2S_PCM_LOOPBACK_MASK                           0x1
#घोषणा PCM_I2S_PCM_LOOPBACK_MASK_SFT                       (0x1 << 26)
#घोषणा PCM_SYNC_DELSEL_SFT                                 25
#घोषणा PCM_SYNC_DELSEL_MASK                                0x1
#घोषणा PCM_SYNC_DELSEL_MASK_SFT                            (0x1 << 25)
#घोषणा PCM_TX_LR_SWAP_SFT                                  24
#घोषणा PCM_TX_LR_SWAP_MASK                                 0x1
#घोषणा PCM_TX_LR_SWAP_MASK_SFT                             (0x1 << 24)
#घोषणा PCM_SYNC_OUT_INV_SFT                                23
#घोषणा PCM_SYNC_OUT_INV_MASK                               0x1
#घोषणा PCM_SYNC_OUT_INV_MASK_SFT                           (0x1 << 23)
#घोषणा PCM_BCLK_OUT_INV_SFT                                22
#घोषणा PCM_BCLK_OUT_INV_MASK                               0x1
#घोषणा PCM_BCLK_OUT_INV_MASK_SFT                           (0x1 << 22)
#घोषणा PCM_SYNC_IN_INV_SFT                                 21
#घोषणा PCM_SYNC_IN_INV_MASK                                0x1
#घोषणा PCM_SYNC_IN_INV_MASK_SFT                            (0x1 << 21)
#घोषणा PCM_BCLK_IN_INV_SFT                                 20
#घोषणा PCM_BCLK_IN_INV_MASK                                0x1
#घोषणा PCM_BCLK_IN_INV_MASK_SFT                            (0x1 << 20)
#घोषणा PCM_TX_LCH_RPT_SFT                                  19
#घोषणा PCM_TX_LCH_RPT_MASK                                 0x1
#घोषणा PCM_TX_LCH_RPT_MASK_SFT                             (0x1 << 19)
#घोषणा PCM_VBT_16K_MODE_SFT                                18
#घोषणा PCM_VBT_16K_MODE_MASK                               0x1
#घोषणा PCM_VBT_16K_MODE_MASK_SFT                           (0x1 << 18)
#घोषणा PCM_EXT_MODEM_SFT                                   17
#घोषणा PCM_EXT_MODEM_MASK                                  0x1
#घोषणा PCM_EXT_MODEM_MASK_SFT                              (0x1 << 17)
#घोषणा PCM_24BIT_SFT                                       16
#घोषणा PCM_24BIT_MASK                                      0x1
#घोषणा PCM_24BIT_MASK_SFT                                  (0x1 << 16)
#घोषणा PCM_WLEN_SFT                                        14
#घोषणा PCM_WLEN_MASK                                       0x3
#घोषणा PCM_WLEN_MASK_SFT                                   (0x3 << 14)
#घोषणा PCM_SYNC_LENGTH_SFT                                 9
#घोषणा PCM_SYNC_LENGTH_MASK                                0x1f
#घोषणा PCM_SYNC_LENGTH_MASK_SFT                            (0x1f << 9)
#घोषणा PCM_SYNC_TYPE_SFT                                   8
#घोषणा PCM_SYNC_TYPE_MASK                                  0x1
#घोषणा PCM_SYNC_TYPE_MASK_SFT                              (0x1 << 8)
#घोषणा PCM_BT_MODE_SFT                                     7
#घोषणा PCM_BT_MODE_MASK                                    0x1
#घोषणा PCM_BT_MODE_MASK_SFT                                (0x1 << 7)
#घोषणा PCM_BYP_ASRC_SFT                                    6
#घोषणा PCM_BYP_ASRC_MASK                                   0x1
#घोषणा PCM_BYP_ASRC_MASK_SFT                               (0x1 << 6)
#घोषणा PCM_SLAVE_SFT                                       5
#घोषणा PCM_SLAVE_MASK                                      0x1
#घोषणा PCM_SLAVE_MASK_SFT                                  (0x1 << 5)
#घोषणा PCM_MODE_SFT                                        3
#घोषणा PCM_MODE_MASK                                       0x3
#घोषणा PCM_MODE_MASK_SFT                                   (0x3 << 3)
#घोषणा PCM_FMT_SFT                                         1
#घोषणा PCM_FMT_MASK                                        0x3
#घोषणा PCM_FMT_MASK_SFT                                    (0x3 << 1)
#घोषणा PCM_EN_SFT                                          0
#घोषणा PCM_EN_MASK                                         0x1
#घोषणा PCM_EN_MASK_SFT                                     (0x1 << 0)

/* PCM_INTF_CON2 */
#घोषणा PCM1_TX_FIFO_OV_SFT                                 31
#घोषणा PCM1_TX_FIFO_OV_MASK                                0x1
#घोषणा PCM1_TX_FIFO_OV_MASK_SFT                            (0x1 << 31)
#घोषणा PCM1_RX_FIFO_OV_SFT                                 30
#घोषणा PCM1_RX_FIFO_OV_MASK                                0x1
#घोषणा PCM1_RX_FIFO_OV_MASK_SFT                            (0x1 << 30)
#घोषणा PCM2_TX_FIFO_OV_SFT                                 29
#घोषणा PCM2_TX_FIFO_OV_MASK                                0x1
#घोषणा PCM2_TX_FIFO_OV_MASK_SFT                            (0x1 << 29)
#घोषणा PCM2_RX_FIFO_OV_SFT                                 28
#घोषणा PCM2_RX_FIFO_OV_MASK                                0x1
#घोषणा PCM2_RX_FIFO_OV_MASK_SFT                            (0x1 << 28)
#घोषणा PCM1_SYNC_GLITCH_SFT                                27
#घोषणा PCM1_SYNC_GLITCH_MASK                               0x1
#घोषणा PCM1_SYNC_GLITCH_MASK_SFT                           (0x1 << 27)
#घोषणा PCM2_SYNC_GLITCH_SFT                                26
#घोषणा PCM2_SYNC_GLITCH_MASK                               0x1
#घोषणा PCM2_SYNC_GLITCH_MASK_SFT                           (0x1 << 26)
#घोषणा PCM1_PCM2_LOOPBACK_SFT                              15
#घोषणा PCM1_PCM2_LOOPBACK_MASK                             0x1
#घोषणा PCM1_PCM2_LOOPBACK_MASK_SFT                         (0x1 << 15)
#घोषणा DAI_PCM_LOOPBACK_CH_SFT                             13
#घोषणा DAI_PCM_LOOPBACK_CH_MASK                            0x1
#घोषणा DAI_PCM_LOOPBACK_CH_MASK_SFT                        (0x1 << 13)
#घोषणा I2S_PCM_LOOPBACK_CH_SFT                             12
#घोषणा I2S_PCM_LOOPBACK_CH_MASK                            0x1
#घोषणा I2S_PCM_LOOPBACK_CH_MASK_SFT                        (0x1 << 12)
#घोषणा PCM_USE_MD3_SFT                                     8
#घोषणा PCM_USE_MD3_MASK                                    0x1
#घोषणा PCM_USE_MD3_MASK_SFT                                (0x1 << 8)
#घोषणा TX_FIX_VALUE_SFT                                    0
#घोषणा TX_FIX_VALUE_MASK                                   0xff
#घोषणा TX_FIX_VALUE_MASK_SFT                               (0xff << 0)

/* PCM2_INTF_CON */
#घोषणा PCM2_TX_FIX_VALUE_SFT                                24
#घोषणा PCM2_TX_FIX_VALUE_MASK                               0xff
#घोषणा PCM2_TX_FIX_VALUE_MASK_SFT                           (0xff << 24)
#घोषणा PCM2_FIX_VALUE_SEL_SFT                               23
#घोषणा PCM2_FIX_VALUE_SEL_MASK                              0x1
#घोषणा PCM2_FIX_VALUE_SEL_MASK_SFT                          (0x1 << 23)
#घोषणा PCM2_BUFFER_LOOPBACK_SFT                             22
#घोषणा PCM2_BUFFER_LOOPBACK_MASK                            0x1
#घोषणा PCM2_BUFFER_LOOPBACK_MASK_SFT                        (0x1 << 22)
#घोषणा PCM2_PARALLEL_LOOPBACK_SFT                           21
#घोषणा PCM2_PARALLEL_LOOPBACK_MASK                          0x1
#घोषणा PCM2_PARALLEL_LOOPBACK_MASK_SFT                      (0x1 << 21)
#घोषणा PCM2_SERIAL_LOOPBACK_SFT                             20
#घोषणा PCM2_SERIAL_LOOPBACK_MASK                            0x1
#घोषणा PCM2_SERIAL_LOOPBACK_MASK_SFT                        (0x1 << 20)
#घोषणा PCM2_DAI_PCM_LOOPBACK_SFT                            19
#घोषणा PCM2_DAI_PCM_LOOPBACK_MASK                           0x1
#घोषणा PCM2_DAI_PCM_LOOPBACK_MASK_SFT                       (0x1 << 19)
#घोषणा PCM2_I2S_PCM_LOOPBACK_SFT                            18
#घोषणा PCM2_I2S_PCM_LOOPBACK_MASK                           0x1
#घोषणा PCM2_I2S_PCM_LOOPBACK_MASK_SFT                       (0x1 << 18)
#घोषणा PCM2_SYNC_DELSEL_SFT                                 17
#घोषणा PCM2_SYNC_DELSEL_MASK                                0x1
#घोषणा PCM2_SYNC_DELSEL_MASK_SFT                            (0x1 << 17)
#घोषणा PCM2_TX_LR_SWAP_SFT                                  16
#घोषणा PCM2_TX_LR_SWAP_MASK                                 0x1
#घोषणा PCM2_TX_LR_SWAP_MASK_SFT                             (0x1 << 16)
#घोषणा PCM2_SYNC_IN_INV_SFT                                 15
#घोषणा PCM2_SYNC_IN_INV_MASK                                0x1
#घोषणा PCM2_SYNC_IN_INV_MASK_SFT                            (0x1 << 15)
#घोषणा PCM2_BCLK_IN_INV_SFT                                 14
#घोषणा PCM2_BCLK_IN_INV_MASK                                0x1
#घोषणा PCM2_BCLK_IN_INV_MASK_SFT                            (0x1 << 14)
#घोषणा PCM2_TX_LCH_RPT_SFT                                  13
#घोषणा PCM2_TX_LCH_RPT_MASK                                 0x1
#घोषणा PCM2_TX_LCH_RPT_MASK_SFT                             (0x1 << 13)
#घोषणा PCM2_VBT_16K_MODE_SFT                                12
#घोषणा PCM2_VBT_16K_MODE_MASK                               0x1
#घोषणा PCM2_VBT_16K_MODE_MASK_SFT                           (0x1 << 12)
#घोषणा PCM2_LOOPBACK_CH_SEL_SFT                             10
#घोषणा PCM2_LOOPBACK_CH_SEL_MASK                            0x3
#घोषणा PCM2_LOOPBACK_CH_SEL_MASK_SFT                        (0x3 << 10)
#घोषणा PCM2_TX2_BT_MODE_SFT                                 8
#घोषणा PCM2_TX2_BT_MODE_MASK                                0x1
#घोषणा PCM2_TX2_BT_MODE_MASK_SFT                            (0x1 << 8)
#घोषणा PCM2_BT_MODE_SFT                                     7
#घोषणा PCM2_BT_MODE_MASK                                    0x1
#घोषणा PCM2_BT_MODE_MASK_SFT                                (0x1 << 7)
#घोषणा PCM2_AFIFO_SFT                                       6
#घोषणा PCM2_AFIFO_MASK                                      0x1
#घोषणा PCM2_AFIFO_MASK_SFT                                  (0x1 << 6)
#घोषणा PCM2_WLEN_SFT                                        5
#घोषणा PCM2_WLEN_MASK                                       0x1
#घोषणा PCM2_WLEN_MASK_SFT                                   (0x1 << 5)
#घोषणा PCM2_MODE_SFT                                        3
#घोषणा PCM2_MODE_MASK                                       0x3
#घोषणा PCM2_MODE_MASK_SFT                                   (0x3 << 3)
#घोषणा PCM2_FMT_SFT                                         1
#घोषणा PCM2_FMT_MASK                                        0x3
#घोषणा PCM2_FMT_MASK_SFT                                    (0x3 << 1)
#घोषणा PCM2_EN_SFT                                          0
#घोषणा PCM2_EN_MASK                                         0x1
#घोषणा PCM2_EN_MASK_SFT                                     (0x1 << 0)
#पूर्ण_अगर
