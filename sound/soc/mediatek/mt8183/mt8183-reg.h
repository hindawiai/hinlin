<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt8183-reg.h  --  Mediatek 8183 audio driver reg definition
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#अगर_अघोषित _MT8183_REG_H_
#घोषणा _MT8183_REG_H_

#घोषणा AUDIO_TOP_CON0              0x0000
#घोषणा AUDIO_TOP_CON1              0x0004
#घोषणा AUDIO_TOP_CON3              0x000c
#घोषणा AFE_DAC_CON0                0x0010
#घोषणा AFE_DAC_CON1                0x0014
#घोषणा AFE_I2S_CON                 0x0018
#घोषणा AFE_DAIBT_CON0              0x001c
#घोषणा AFE_CONN0                   0x0020
#घोषणा AFE_CONN1                   0x0024
#घोषणा AFE_CONN2                   0x0028
#घोषणा AFE_CONN3                   0x002c
#घोषणा AFE_CONN4                   0x0030
#घोषणा AFE_I2S_CON1                0x0034
#घोषणा AFE_I2S_CON2                0x0038
#घोषणा AFE_MRGIF_CON               0x003c
#घोषणा AFE_DL1_BASE                0x0040
#घोषणा AFE_DL1_CUR                 0x0044
#घोषणा AFE_DL1_END                 0x0048
#घोषणा AFE_I2S_CON3                0x004c
#घोषणा AFE_DL2_BASE                0x0050
#घोषणा AFE_DL2_CUR                 0x0054
#घोषणा AFE_DL2_END                 0x0058
#घोषणा AFE_CONN5                   0x005c
#घोषणा AFE_CONN_24BIT              0x006c
#घोषणा AFE_AWB_BASE                0x0070
#घोषणा AFE_AWB_END                 0x0078
#घोषणा AFE_AWB_CUR                 0x007c
#घोषणा AFE_VUL_BASE                0x0080
#घोषणा AFE_VUL_END                 0x0088
#घोषणा AFE_VUL_CUR                 0x008c
#घोषणा AFE_CONN6                   0x00bc
#घोषणा AFE_MEMIF_MSB               0x00cc
#घोषणा AFE_MEMIF_MON0              0x00d0
#घोषणा AFE_MEMIF_MON1              0x00d4
#घोषणा AFE_MEMIF_MON2              0x00d8
#घोषणा AFE_MEMIF_MON3              0x00dc
#घोषणा AFE_MEMIF_MON4              0x00e0
#घोषणा AFE_MEMIF_MON5              0x00e4
#घोषणा AFE_MEMIF_MON6              0x00e8
#घोषणा AFE_MEMIF_MON7              0x00ec
#घोषणा AFE_MEMIF_MON8              0x00f0
#घोषणा AFE_MEMIF_MON9              0x00f4
#घोषणा AFE_ADDA_DL_SRC2_CON0       0x0108
#घोषणा AFE_ADDA_DL_SRC2_CON1       0x010c
#घोषणा AFE_ADDA_UL_SRC_CON0        0x0114
#घोषणा AFE_ADDA_UL_SRC_CON1        0x0118
#घोषणा AFE_ADDA_TOP_CON0           0x0120
#घोषणा AFE_ADDA_UL_DL_CON0         0x0124
#घोषणा AFE_ADDA_SRC_DEBUG          0x012c
#घोषणा AFE_ADDA_SRC_DEBUG_MON0     0x0130
#घोषणा AFE_ADDA_SRC_DEBUG_MON1     0x0134
#घोषणा AFE_ADDA_UL_SRC_MON0        0x0148
#घोषणा AFE_ADDA_UL_SRC_MON1        0x014c
#घोषणा AFE_SIDETONE_DEBUG          0x01d0
#घोषणा AFE_SIDETONE_MON            0x01d4
#घोषणा AFE_SINEGEN_CON2            0x01dc
#घोषणा AFE_SIDETONE_CON0           0x01e0
#घोषणा AFE_SIDETONE_COEFF          0x01e4
#घोषणा AFE_SIDETONE_CON1           0x01e8
#घोषणा AFE_SIDETONE_GAIN           0x01ec
#घोषणा AFE_SINEGEN_CON0            0x01f0
#घोषणा AFE_TOP_CON0                0x0200
#घोषणा AFE_BUS_CFG                 0x0240
#घोषणा AFE_BUS_MON0                0x0244
#घोषणा AFE_ADDA_PREDIS_CON0        0x0260
#घोषणा AFE_ADDA_PREDIS_CON1        0x0264
#घोषणा AFE_MRGIF_MON0              0x0270
#घोषणा AFE_MRGIF_MON1              0x0274
#घोषणा AFE_MRGIF_MON2              0x0278
#घोषणा AFE_I2S_MON                 0x027c
#घोषणा AFE_ADDA_IIR_COEF_02_01     0x0290
#घोषणा AFE_ADDA_IIR_COEF_04_03     0x0294
#घोषणा AFE_ADDA_IIR_COEF_06_05     0x0298
#घोषणा AFE_ADDA_IIR_COEF_08_07     0x029c
#घोषणा AFE_ADDA_IIR_COEF_10_09     0x02a0
#घोषणा AFE_DAC_CON2                0x02e0
#घोषणा AFE_IRQ_MCU_CON1            0x02e4
#घोषणा AFE_IRQ_MCU_CON2            0x02e8
#घोषणा AFE_DAC_MON                 0x02ec
#घोषणा AFE_VUL2_BASE               0x02f0
#घोषणा AFE_VUL2_END                0x02f8
#घोषणा AFE_VUL2_CUR                0x02fc
#घोषणा AFE_IRQ_MCU_CNT0            0x0300
#घोषणा AFE_IRQ_MCU_CNT6            0x0304
#घोषणा AFE_IRQ_MCU_CNT8            0x0308
#घोषणा AFE_IRQ_MCU_EN1             0x030c
#घोषणा AFE_IRQ0_MCU_CNT_MON        0x0310
#घोषणा AFE_IRQ6_MCU_CNT_MON        0x0314
#घोषणा AFE_MOD_DAI_BASE            0x0330
#घोषणा AFE_MOD_DAI_END             0x0338
#घोषणा AFE_MOD_DAI_CUR             0x033c
#घोषणा AFE_VUL_D2_BASE             0x0350
#घोषणा AFE_VUL_D2_END              0x0358
#घोषणा AFE_VUL_D2_CUR              0x035c
#घोषणा AFE_DL3_BASE                0x0360
#घोषणा AFE_DL3_CUR                 0x0364
#घोषणा AFE_DL3_END                 0x0368
#घोषणा AFE_HDMI_OUT_CON0           0x0370
#घोषणा AFE_HDMI_OUT_BASE           0x0374
#घोषणा AFE_HDMI_OUT_CUR            0x0378
#घोषणा AFE_HDMI_OUT_END            0x037c
#घोषणा AFE_HDMI_CONN0              0x0390
#घोषणा AFE_IRQ3_MCU_CNT_MON        0x0398
#घोषणा AFE_IRQ4_MCU_CNT_MON        0x039c
#घोषणा AFE_IRQ_MCU_CON0            0x03a0
#घोषणा AFE_IRQ_MCU_STATUS          0x03a4
#घोषणा AFE_IRQ_MCU_CLR             0x03a8
#घोषणा AFE_IRQ_MCU_CNT1            0x03ac
#घोषणा AFE_IRQ_MCU_CNT2            0x03b0
#घोषणा AFE_IRQ_MCU_EN              0x03b4
#घोषणा AFE_IRQ_MCU_MON2            0x03b8
#घोषणा AFE_IRQ_MCU_CNT5            0x03bc
#घोषणा AFE_IRQ1_MCU_CNT_MON        0x03c0
#घोषणा AFE_IRQ2_MCU_CNT_MON        0x03c4
#घोषणा AFE_IRQ1_MCU_EN_CNT_MON     0x03c8
#घोषणा AFE_IRQ5_MCU_CNT_MON        0x03cc
#घोषणा AFE_MEMIF_MINLEN            0x03d0
#घोषणा AFE_MEMIF_MAXLEN            0x03d4
#घोषणा AFE_MEMIF_PBUF_SIZE         0x03d8
#घोषणा AFE_IRQ_MCU_CNT7            0x03dc
#घोषणा AFE_IRQ7_MCU_CNT_MON        0x03e0
#घोषणा AFE_IRQ_MCU_CNT3            0x03e4
#घोषणा AFE_IRQ_MCU_CNT4            0x03e8
#घोषणा AFE_IRQ_MCU_CNT11           0x03ec
#घोषणा AFE_APLL1_TUNER_CFG         0x03f0
#घोषणा AFE_APLL2_TUNER_CFG         0x03f4
#घोषणा AFE_MEMIF_HD_MODE           0x03f8
#घोषणा AFE_MEMIF_HDALIGN           0x03fc
#घोषणा AFE_CONN33                  0x0408
#घोषणा AFE_IRQ_MCU_CNT12           0x040c
#घोषणा AFE_GAIN1_CON0              0x0410
#घोषणा AFE_GAIN1_CON1              0x0414
#घोषणा AFE_GAIN1_CON2              0x0418
#घोषणा AFE_GAIN1_CON3              0x041c
#घोषणा AFE_CONN7                   0x0420
#घोषणा AFE_GAIN1_CUR               0x0424
#घोषणा AFE_GAIN2_CON0              0x0428
#घोषणा AFE_GAIN2_CON1              0x042c
#घोषणा AFE_GAIN2_CON2              0x0430
#घोषणा AFE_GAIN2_CON3              0x0434
#घोषणा AFE_CONN8                   0x0438
#घोषणा AFE_GAIN2_CUR               0x043c
#घोषणा AFE_CONN9                   0x0440
#घोषणा AFE_CONN10                  0x0444
#घोषणा AFE_CONN11                  0x0448
#घोषणा AFE_CONN12                  0x044c
#घोषणा AFE_CONN13                  0x0450
#घोषणा AFE_CONN14                  0x0454
#घोषणा AFE_CONN15                  0x0458
#घोषणा AFE_CONN16                  0x045c
#घोषणा AFE_CONN17                  0x0460
#घोषणा AFE_CONN18                  0x0464
#घोषणा AFE_CONN19                  0x0468
#घोषणा AFE_CONN20                  0x046c
#घोषणा AFE_CONN21                  0x0470
#घोषणा AFE_CONN22                  0x0474
#घोषणा AFE_CONN23                  0x0478
#घोषणा AFE_CONN24                  0x047c
#घोषणा AFE_CONN_RS                 0x0494
#घोषणा AFE_CONN_DI                 0x0498
#घोषणा AFE_CONN25                  0x04b0
#घोषणा AFE_CONN26                  0x04b4
#घोषणा AFE_CONN27                  0x04b8
#घोषणा AFE_CONN28                  0x04bc
#घोषणा AFE_CONN29                  0x04c0
#घोषणा AFE_CONN30                  0x04c4
#घोषणा AFE_CONN31                  0x04c8
#घोषणा AFE_CONN32                  0x04cc
#घोषणा AFE_SRAM_DELSEL_CON0        0x04f0
#घोषणा AFE_SRAM_DELSEL_CON2        0x04f8
#घोषणा AFE_SRAM_DELSEL_CON3        0x04fc
#घोषणा AFE_ASRC_2CH_CON12          0x0528
#घोषणा AFE_ASRC_2CH_CON13          0x052c
#घोषणा PCM_INTF_CON1               0x0530
#घोषणा PCM_INTF_CON2               0x0538
#घोषणा PCM2_INTF_CON               0x053c
#घोषणा AFE_TDM_CON1                0x0548
#घोषणा AFE_TDM_CON2                0x054c
#घोषणा AFE_CONN34                  0x0580
#घोषणा FPGA_CFG0                   0x05b0
#घोषणा FPGA_CFG1                   0x05b4
#घोषणा FPGA_CFG2                   0x05c0
#घोषणा FPGA_CFG3                   0x05c4
#घोषणा AUDIO_TOP_DBG_CON           0x05c8
#घोषणा AUDIO_TOP_DBG_MON0          0x05cc
#घोषणा AUDIO_TOP_DBG_MON1          0x05d0
#घोषणा AFE_IRQ8_MCU_CNT_MON        0x05e4
#घोषणा AFE_IRQ11_MCU_CNT_MON       0x05e8
#घोषणा AFE_IRQ12_MCU_CNT_MON       0x05ec
#घोषणा AFE_GENERAL_REG0            0x0800
#घोषणा AFE_GENERAL_REG1            0x0804
#घोषणा AFE_GENERAL_REG2            0x0808
#घोषणा AFE_GENERAL_REG3            0x080c
#घोषणा AFE_GENERAL_REG4            0x0810
#घोषणा AFE_GENERAL_REG5            0x0814
#घोषणा AFE_GENERAL_REG6            0x0818
#घोषणा AFE_GENERAL_REG7            0x081c
#घोषणा AFE_GENERAL_REG8            0x0820
#घोषणा AFE_GENERAL_REG9            0x0824
#घोषणा AFE_GENERAL_REG10           0x0828
#घोषणा AFE_GENERAL_REG11           0x082c
#घोषणा AFE_GENERAL_REG12           0x0830
#घोषणा AFE_GENERAL_REG13           0x0834
#घोषणा AFE_GENERAL_REG14           0x0838
#घोषणा AFE_GENERAL_REG15           0x083c
#घोषणा AFE_CBIP_CFG0               0x0840
#घोषणा AFE_CBIP_MON0               0x0844
#घोषणा AFE_CBIP_SLV_MUX_MON0       0x0848
#घोषणा AFE_CBIP_SLV_DECODER_MON0   0x084c
#घोषणा AFE_CONN0_1                 0x0900
#घोषणा AFE_CONN1_1                 0x0904
#घोषणा AFE_CONN2_1                 0x0908
#घोषणा AFE_CONN3_1                 0x090c
#घोषणा AFE_CONN4_1                 0x0910
#घोषणा AFE_CONN5_1                 0x0914
#घोषणा AFE_CONN6_1                 0x0918
#घोषणा AFE_CONN7_1                 0x091c
#घोषणा AFE_CONN8_1                 0x0920
#घोषणा AFE_CONN9_1                 0x0924
#घोषणा AFE_CONN10_1                0x0928
#घोषणा AFE_CONN11_1                0x092c
#घोषणा AFE_CONN12_1                0x0930
#घोषणा AFE_CONN13_1                0x0934
#घोषणा AFE_CONN14_1                0x0938
#घोषणा AFE_CONN15_1                0x093c
#घोषणा AFE_CONN16_1                0x0940
#घोषणा AFE_CONN17_1                0x0944
#घोषणा AFE_CONN18_1                0x0948
#घोषणा AFE_CONN19_1                0x094c
#घोषणा AFE_CONN20_1                0x0950
#घोषणा AFE_CONN21_1                0x0954
#घोषणा AFE_CONN22_1                0x0958
#घोषणा AFE_CONN23_1                0x095c
#घोषणा AFE_CONN24_1                0x0960
#घोषणा AFE_CONN25_1                0x0964
#घोषणा AFE_CONN26_1                0x0968
#घोषणा AFE_CONN27_1                0x096c
#घोषणा AFE_CONN28_1                0x0970
#घोषणा AFE_CONN29_1                0x0974
#घोषणा AFE_CONN30_1                0x0978
#घोषणा AFE_CONN31_1                0x097c
#घोषणा AFE_CONN32_1                0x0980
#घोषणा AFE_CONN33_1                0x0984
#घोषणा AFE_CONN34_1                0x0988
#घोषणा AFE_CONN_RS_1               0x098c
#घोषणा AFE_CONN_DI_1               0x0990
#घोषणा AFE_CONN_24BIT_1            0x0994
#घोषणा AFE_CONN_REG                0x0998
#घोषणा AFE_CONN35                  0x09a0
#घोषणा AFE_CONN36                  0x09a4
#घोषणा AFE_CONN37                  0x09a8
#घोषणा AFE_CONN38                  0x09ac
#घोषणा AFE_CONN35_1                0x09b0
#घोषणा AFE_CONN36_1                0x09b4
#घोषणा AFE_CONN37_1                0x09b8
#घोषणा AFE_CONN38_1                0x09bc
#घोषणा AFE_CONN39                  0x09c0
#घोषणा AFE_CONN40                  0x09c4
#घोषणा AFE_CONN41                  0x09c8
#घोषणा AFE_CONN42                  0x09cc
#घोषणा AFE_CONN39_1                0x09e0
#घोषणा AFE_CONN40_1                0x09e4
#घोषणा AFE_CONN41_1                0x09e8
#घोषणा AFE_CONN42_1                0x09ec
#घोषणा AFE_I2S_CON4                0x09f8
#घोषणा AFE_ADDA6_TOP_CON0          0x0a80
#घोषणा AFE_ADDA6_UL_SRC_CON0       0x0a84
#घोषणा AFE_ADD6_UL_SRC_CON1        0x0a88
#घोषणा AFE_ADDA6_SRC_DEBUG         0x0a8c
#घोषणा AFE_ADDA6_SRC_DEBUG_MON0    0x0a90
#घोषणा AFE_ADDA6_ULCF_CFG_02_01    0x0aa0
#घोषणा AFE_ADDA6_ULCF_CFG_04_03    0x0aa4
#घोषणा AFE_ADDA6_ULCF_CFG_06_05    0x0aa8
#घोषणा AFE_ADDA6_ULCF_CFG_08_07    0x0aac
#घोषणा AFE_ADDA6_ULCF_CFG_10_09    0x0ab0
#घोषणा AFE_ADDA6_ULCF_CFG_12_11    0x0ab4
#घोषणा AFE_ADDA6_ULCF_CFG_14_13    0x0ab8
#घोषणा AFE_ADDA6_ULCF_CFG_16_15    0x0abc
#घोषणा AFE_ADDA6_ULCF_CFG_18_17    0x0ac0
#घोषणा AFE_ADDA6_ULCF_CFG_20_19    0x0ac4
#घोषणा AFE_ADDA6_ULCF_CFG_22_21    0x0ac8
#घोषणा AFE_ADDA6_ULCF_CFG_24_23    0x0acc
#घोषणा AFE_ADDA6_ULCF_CFG_26_25    0x0ad0
#घोषणा AFE_ADDA6_ULCF_CFG_28_27    0x0ad4
#घोषणा AFE_ADDA6_ULCF_CFG_30_29    0x0ad8
#घोषणा AFE_ADD6A_UL_SRC_MON0       0x0ae4
#घोषणा AFE_ADDA6_UL_SRC_MON1       0x0ae8
#घोषणा AFE_CONN43                  0x0af8
#घोषणा AFE_CONN43_1                0x0afc
#घोषणा AFE_DL1_BASE_MSB            0x0b00
#घोषणा AFE_DL1_CUR_MSB             0x0b04
#घोषणा AFE_DL1_END_MSB             0x0b08
#घोषणा AFE_DL2_BASE_MSB            0x0b10
#घोषणा AFE_DL2_CUR_MSB             0x0b14
#घोषणा AFE_DL2_END_MSB             0x0b18
#घोषणा AFE_AWB_BASE_MSB            0x0b20
#घोषणा AFE_AWB_END_MSB             0x0b28
#घोषणा AFE_AWB_CUR_MSB             0x0b2c
#घोषणा AFE_VUL_BASE_MSB            0x0b30
#घोषणा AFE_VUL_END_MSB             0x0b38
#घोषणा AFE_VUL_CUR_MSB             0x0b3c
#घोषणा AFE_VUL2_BASE_MSB           0x0b50
#घोषणा AFE_VUL2_END_MSB            0x0b58
#घोषणा AFE_VUL2_CUR_MSB            0x0b5c
#घोषणा AFE_MOD_DAI_BASE_MSB        0x0b60
#घोषणा AFE_MOD_DAI_END_MSB         0x0b68
#घोषणा AFE_MOD_DAI_CUR_MSB         0x0b6c
#घोषणा AFE_VUL_D2_BASE_MSB         0x0b80
#घोषणा AFE_VUL_D2_END_MSB          0x0b88
#घोषणा AFE_VUL_D2_CUR_MSB          0x0b8c
#घोषणा AFE_DL3_BASE_MSB            0x0b90
#घोषणा AFE_DL3_CUR_MSB             0x0b94
#घोषणा AFE_DL3_END_MSB             0x0b98
#घोषणा AFE_HDMI_OUT_BASE_MSB       0x0ba4
#घोषणा AFE_HDMI_OUT_CUR_MSB        0x0ba8
#घोषणा AFE_HDMI_OUT_END_MSB        0x0bac
#घोषणा AFE_AWB2_BASE               0x0bd0
#घोषणा AFE_AWB2_END                0x0bd8
#घोषणा AFE_AWB2_CUR                0x0bdc
#घोषणा AFE_AWB2_BASE_MSB           0x0be0
#घोषणा AFE_AWB2_END_MSB            0x0be8
#घोषणा AFE_AWB2_CUR_MSB            0x0bec
#घोषणा AFE_ADDA_DL_SDM_DCCOMP_CON  0x0c50
#घोषणा AFE_ADDA_DL_SDM_TEST        0x0c54
#घोषणा AFE_ADDA_DL_DC_COMP_CFG0    0x0c58
#घोषणा AFE_ADDA_DL_DC_COMP_CFG1    0x0c5c
#घोषणा AFE_ADDA_DL_SDM_FIFO_MON    0x0c60
#घोषणा AFE_ADDA_DL_SRC_LCH_MON     0x0c64
#घोषणा AFE_ADDA_DL_SRC_RCH_MON     0x0c68
#घोषणा AFE_ADDA_DL_SDM_OUT_MON     0x0c6c
#घोषणा AFE_CONNSYS_I2S_CON         0x0c78
#घोषणा AFE_CONNSYS_I2S_MON         0x0c7c
#घोषणा AFE_ASRC_2CH_CON0           0x0c80
#घोषणा AFE_ASRC_2CH_CON1           0x0c84
#घोषणा AFE_ASRC_2CH_CON2           0x0c88
#घोषणा AFE_ASRC_2CH_CON3           0x0c8c
#घोषणा AFE_ASRC_2CH_CON4           0x0c90
#घोषणा AFE_ASRC_2CH_CON5           0x0c94
#घोषणा AFE_ASRC_2CH_CON6           0x0c98
#घोषणा AFE_ASRC_2CH_CON7           0x0c9c
#घोषणा AFE_ASRC_2CH_CON8           0x0ca0
#घोषणा AFE_ASRC_2CH_CON9           0x0ca4
#घोषणा AFE_ASRC_2CH_CON10          0x0ca8
#घोषणा AFE_ADDA6_IIR_COEF_02_01    0x0ce0
#घोषणा AFE_ADDA6_IIR_COEF_04_03    0x0ce4
#घोषणा AFE_ADDA6_IIR_COEF_06_05    0x0ce8
#घोषणा AFE_ADDA6_IIR_COEF_08_07    0x0cec
#घोषणा AFE_ADDA6_IIR_COEF_10_09    0x0cf0
#घोषणा AFE_ADDA_PREDIS_CON2        0x0d40
#घोषणा AFE_ADDA_PREDIS_CON3        0x0d44
#घोषणा AFE_MEMIF_MON12             0x0d70
#घोषणा AFE_MEMIF_MON13             0x0d74
#घोषणा AFE_MEMIF_MON14             0x0d78
#घोषणा AFE_MEMIF_MON15             0x0d7c
#घोषणा AFE_MEMIF_MON16             0x0d80
#घोषणा AFE_MEMIF_MON17             0x0d84
#घोषणा AFE_MEMIF_MON18             0x0d88
#घोषणा AFE_MEMIF_MON19             0x0d8c
#घोषणा AFE_MEMIF_MON20             0x0d90
#घोषणा AFE_MEMIF_MON21             0x0d94
#घोषणा AFE_MEMIF_MON22             0x0d98
#घोषणा AFE_MEMIF_MON23             0x0d9c
#घोषणा AFE_MEMIF_MON24             0x0da0
#घोषणा AFE_HD_ENGEN_ENABLE         0x0dd0
#घोषणा AFE_ADDA_MTKAIF_CFG0        0x0e00
#घोषणा AFE_ADDA_MTKAIF_TX_CFG1     0x0e14
#घोषणा AFE_ADDA_MTKAIF_RX_CFG0     0x0e20
#घोषणा AFE_ADDA_MTKAIF_RX_CFG1     0x0e24
#घोषणा AFE_ADDA_MTKAIF_RX_CFG2     0x0e28
#घोषणा AFE_ADDA_MTKAIF_MON0        0x0e34
#घोषणा AFE_ADDA_MTKAIF_MON1        0x0e38
#घोषणा AFE_AUD_PAD_TOP             0x0e40
#घोषणा AFE_GENERAL1_ASRC_2CH_CON0  0x0e80
#घोषणा AFE_GENERAL1_ASRC_2CH_CON1  0x0e84
#घोषणा AFE_GENERAL1_ASRC_2CH_CON2  0x0e88
#घोषणा AFE_GENERAL1_ASRC_2CH_CON3  0x0e8c
#घोषणा AFE_GENERAL1_ASRC_2CH_CON4  0x0e90
#घोषणा AFE_GENERAL1_ASRC_2CH_CON5  0x0e94
#घोषणा AFE_GENERAL1_ASRC_2CH_CON6  0x0e98
#घोषणा AFE_GENERAL1_ASRC_2CH_CON7  0x0e9c
#घोषणा AFE_GENERAL1_ASRC_2CH_CON8  0x0ea0
#घोषणा AFE_GENERAL1_ASRC_2CH_CON9  0x0ea4
#घोषणा AFE_GENERAL1_ASRC_2CH_CON10 0x0ea8
#घोषणा AFE_GENERAL1_ASRC_2CH_CON12 0x0eb0
#घोषणा AFE_GENERAL1_ASRC_2CH_CON13 0x0eb4
#घोषणा GENERAL_ASRC_MODE           0x0eb8
#घोषणा GENERAL_ASRC_EN_ON          0x0ebc
#घोषणा AFE_GENERAL2_ASRC_2CH_CON0  0x0f00
#घोषणा AFE_GENERAL2_ASRC_2CH_CON1  0x0f04
#घोषणा AFE_GENERAL2_ASRC_2CH_CON2  0x0f08
#घोषणा AFE_GENERAL2_ASRC_2CH_CON3  0x0f0c
#घोषणा AFE_GENERAL2_ASRC_2CH_CON4  0x0f10
#घोषणा AFE_GENERAL2_ASRC_2CH_CON5  0x0f14
#घोषणा AFE_GENERAL2_ASRC_2CH_CON6  0x0f18
#घोषणा AFE_GENERAL2_ASRC_2CH_CON7  0x0f1c
#घोषणा AFE_GENERAL2_ASRC_2CH_CON8  0x0f20
#घोषणा AFE_GENERAL2_ASRC_2CH_CON9  0x0f24
#घोषणा AFE_GENERAL2_ASRC_2CH_CON10 0x0f28
#घोषणा AFE_GENERAL2_ASRC_2CH_CON12 0x0f30
#घोषणा AFE_GENERAL2_ASRC_2CH_CON13 0x0f34

#घोषणा AFE_MAX_REGISTER AFE_GENERAL2_ASRC_2CH_CON13
#घोषणा AFE_IRQ_STATUS_BITS 0x1fff

/* AUDIO_TOP_CON3 */
#घोषणा BCK_INVERSE_SFT                              3
#घोषणा BCK_INVERSE_MASK                             0x1
#घोषणा BCK_INVERSE_MASK_SFT                         (0x1 << 3)

/* AFE_DAC_CON0 */
#घोषणा AWB2_ON_SFT                                   29
#घोषणा AWB2_ON_MASK                                  0x1
#घोषणा AWB2_ON_MASK_SFT                              (0x1 << 29)
#घोषणा VUL2_ON_SFT                                   27
#घोषणा VUL2_ON_MASK                                  0x1
#घोषणा VUL2_ON_MASK_SFT                              (0x1 << 27)
#घोषणा MOD_DAI_DUP_WR_SFT                            26
#घोषणा MOD_DAI_DUP_WR_MASK                           0x1
#घोषणा MOD_DAI_DUP_WR_MASK_SFT                       (0x1 << 26)
#घोषणा VUL12_MODE_SFT                                20
#घोषणा VUL12_MODE_MASK                               0xf
#घोषणा VUL12_MODE_MASK_SFT                           (0xf << 20)
#घोषणा VUL12_R_MONO_SFT                              11
#घोषणा VUL12_R_MONO_MASK                             0x1
#घोषणा VUL12_R_MONO_MASK_SFT                         (0x1 << 11)
#घोषणा VUL12_MONO_SFT                                10
#घोषणा VUL12_MONO_MASK                               0x1
#घोषणा VUL12_MONO_MASK_SFT                           (0x1 << 10)
#घोषणा VUL12_ON_SFT                                  9
#घोषणा VUL12_ON_MASK                                 0x1
#घोषणा VUL12_ON_MASK_SFT                             (0x1 << 9)
#घोषणा MOD_DAI_ON_SFT                                7
#घोषणा MOD_DAI_ON_MASK                               0x1
#घोषणा MOD_DAI_ON_MASK_SFT                           (0x1 << 7)
#घोषणा AWB_ON_SFT                                    6
#घोषणा AWB_ON_MASK                                   0x1
#घोषणा AWB_ON_MASK_SFT                               (0x1 << 6)
#घोषणा DL3_ON_SFT                                    5
#घोषणा DL3_ON_MASK                                   0x1
#घोषणा DL3_ON_MASK_SFT                               (0x1 << 5)
#घोषणा VUL_ON_SFT                                    3
#घोषणा VUL_ON_MASK                                   0x1
#घोषणा VUL_ON_MASK_SFT                               (0x1 << 3)
#घोषणा DL2_ON_SFT                                    2
#घोषणा DL2_ON_MASK                                   0x1
#घोषणा DL2_ON_MASK_SFT                               (0x1 << 2)
#घोषणा DL1_ON_SFT                                    1
#घोषणा DL1_ON_MASK                                   0x1
#घोषणा DL1_ON_MASK_SFT                               (0x1 << 1)
#घोषणा AFE_ON_SFT                                    0
#घोषणा AFE_ON_MASK                                   0x1
#घोषणा AFE_ON_MASK_SFT                               (0x1 << 0)

/* AFE_DAC_CON1 */
#घोषणा MOD_DAI_MODE_SFT                              30
#घोषणा MOD_DAI_MODE_MASK                             0x3
#घोषणा MOD_DAI_MODE_MASK_SFT                         (0x3 << 30)
#घोषणा VUL_R_MONO_SFT                                28
#घोषणा VUL_R_MONO_MASK                               0x1
#घोषणा VUL_R_MONO_MASK_SFT                           (0x1 << 28)
#घोषणा VUL_DATA_SFT                                  27
#घोषणा VUL_DATA_MASK                                 0x1
#घोषणा VUL_DATA_MASK_SFT                             (0x1 << 27)
#घोषणा AWB_R_MONO_SFT                                25
#घोषणा AWB_R_MONO_MASK                               0x1
#घोषणा AWB_R_MONO_MASK_SFT                           (0x1 << 25)
#घोषणा AWB_DATA_SFT                                  24
#घोषणा AWB_DATA_MASK                                 0x1
#घोषणा AWB_DATA_MASK_SFT                             (0x1 << 24)
#घोषणा DL3_DATA_SFT                                  23
#घोषणा DL3_DATA_MASK                                 0x1
#घोषणा DL3_DATA_MASK_SFT                             (0x1 << 23)
#घोषणा DL2_DATA_SFT                                  22
#घोषणा DL2_DATA_MASK                                 0x1
#घोषणा DL2_DATA_MASK_SFT                             (0x1 << 22)
#घोषणा DL1_DATA_SFT                                  21
#घोषणा DL1_DATA_MASK                                 0x1
#घोषणा DL1_DATA_MASK_SFT                             (0x1 << 21)
#घोषणा VUL_MODE_SFT                                  16
#घोषणा VUL_MODE_MASK                                 0xf
#घोषणा VUL_MODE_MASK_SFT                             (0xf << 16)
#घोषणा AWB_MODE_SFT                                  12
#घोषणा AWB_MODE_MASK                                 0xf
#घोषणा AWB_MODE_MASK_SFT                             (0xf << 12)
#घोषणा I2S_MODE_SFT                                  8
#घोषणा I2S_MODE_MASK                                 0xf
#घोषणा I2S_MODE_MASK_SFT                             (0xf << 8)
#घोषणा DL2_MODE_SFT                                  4
#घोषणा DL2_MODE_MASK                                 0xf
#घोषणा DL2_MODE_MASK_SFT                             (0xf << 4)
#घोषणा DL1_MODE_SFT                                  0
#घोषणा DL1_MODE_MASK                                 0xf
#घोषणा DL1_MODE_MASK_SFT                             (0xf << 0)

/* AFE_DAC_CON2 */
#घोषणा AWB2_R_MONO_SFT                               21
#घोषणा AWB2_R_MONO_MASK                              0x1
#घोषणा AWB2_R_MONO_MASK_SFT                          (0x1 << 21)
#घोषणा AWB2_DATA_SFT                                 20
#घोषणा AWB2_DATA_MASK                                0x1
#घोषणा AWB2_DATA_MASK_SFT                            (0x1 << 20)
#घोषणा AWB2_MODE_SFT                                 16
#घोषणा AWB2_MODE_MASK                                0xf
#घोषणा AWB2_MODE_MASK_SFT                            (0xf << 16)
#घोषणा DL3_MODE_SFT                                  8
#घोषणा DL3_MODE_MASK                                 0xf
#घोषणा DL3_MODE_MASK_SFT                             (0xf << 8)
#घोषणा VUL2_MODE_SFT                                 4
#घोषणा VUL2_MODE_MASK                                0xf
#घोषणा VUL2_MODE_MASK_SFT                            (0xf << 4)
#घोषणा VUL2_R_MONO_SFT                               1
#घोषणा VUL2_R_MONO_MASK                              0x1
#घोषणा VUL2_R_MONO_MASK_SFT                          (0x1 << 1)
#घोषणा VUL2_DATA_SFT                                 0
#घोषणा VUL2_DATA_MASK                                0x1
#घोषणा VUL2_DATA_MASK_SFT                            (0x1 << 0)

/* AFE_DAC_MON */
#घोषणा AFE_ON_RETM_SFT                               0
#घोषणा AFE_ON_RETM_MASK                              0x1
#घोषणा AFE_ON_RETM_MASK_SFT                          (0x1 << 0)

/* AFE_I2S_CON */
#घोषणा BCK_NEG_EG_LATCH_SFT                          30
#घोषणा BCK_NEG_EG_LATCH_MASK                         0x1
#घोषणा BCK_NEG_EG_LATCH_MASK_SFT                     (0x1 << 30)
#घोषणा BCK_INV_SFT                                   29
#घोषणा BCK_INV_MASK                                  0x1
#घोषणा BCK_INV_MASK_SFT                              (0x1 << 29)
#घोषणा I2SIN_PAD_SEL_SFT                             28
#घोषणा I2SIN_PAD_SEL_MASK                            0x1
#घोषणा I2SIN_PAD_SEL_MASK_SFT                        (0x1 << 28)
#घोषणा I2S_LOOPBACK_SFT                              20
#घोषणा I2S_LOOPBACK_MASK                             0x1
#घोषणा I2S_LOOPBACK_MASK_SFT                         (0x1 << 20)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT             17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK            0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT        (0x1 << 17)
#घोषणा I2S1_HD_EN_SFT                                12
#घोषणा I2S1_HD_EN_MASK                               0x1
#घोषणा I2S1_HD_EN_MASK_SFT                           (0x1 << 12)
#घोषणा INV_PAD_CTRL_SFT                              7
#घोषणा INV_PAD_CTRL_MASK                             0x1
#घोषणा INV_PAD_CTRL_MASK_SFT                         (0x1 << 7)
#घोषणा I2S_BYPSRC_SFT                                6
#घोषणा I2S_BYPSRC_MASK                               0x1
#घोषणा I2S_BYPSRC_MASK_SFT                           (0x1 << 6)
#घोषणा INV_LRCK_SFT                                  5
#घोषणा INV_LRCK_MASK                                 0x1
#घोषणा INV_LRCK_MASK_SFT                             (0x1 << 5)
#घोषणा I2S_FMT_SFT                                   3
#घोषणा I2S_FMT_MASK                                  0x1
#घोषणा I2S_FMT_MASK_SFT                              (0x1 << 3)
#घोषणा I2S_SRC_SFT                                   2
#घोषणा I2S_SRC_MASK                                  0x1
#घोषणा I2S_SRC_MASK_SFT                              (0x1 << 2)
#घोषणा I2S_WLEN_SFT                                  1
#घोषणा I2S_WLEN_MASK                                 0x1
#घोषणा I2S_WLEN_MASK_SFT                             (0x1 << 1)
#घोषणा I2S_EN_SFT                                    0
#घोषणा I2S_EN_MASK                                   0x1
#घोषणा I2S_EN_MASK_SFT                               (0x1 << 0)

/* AFE_I2S_CON1 */
#घोषणा I2S2_LR_SWAP_SFT                              31
#घोषणा I2S2_LR_SWAP_MASK                             0x1
#घोषणा I2S2_LR_SWAP_MASK_SFT                         (0x1 << 31)
#घोषणा I2S2_SEL_O19_O20_SFT                          18
#घोषणा I2S2_SEL_O19_O20_MASK                         0x1
#घोषणा I2S2_SEL_O19_O20_MASK_SFT                     (0x1 << 18)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT             17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK            0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT        (0x1 << 17)
#घोषणा I2S2_SEL_O03_O04_SFT                          16
#घोषणा I2S2_SEL_O03_O04_MASK                         0x1
#घोषणा I2S2_SEL_O03_O04_MASK_SFT                     (0x1 << 16)
#घोषणा I2S2_32BIT_EN_SFT                             13
#घोषणा I2S2_32BIT_EN_MASK                            0x1
#घोषणा I2S2_32BIT_EN_MASK_SFT                        (0x1 << 13)
#घोषणा I2S2_HD_EN_SFT                                12
#घोषणा I2S2_HD_EN_MASK                               0x1
#घोषणा I2S2_HD_EN_MASK_SFT                           (0x1 << 12)
#घोषणा I2S2_OUT_MODE_SFT                             8
#घोषणा I2S2_OUT_MODE_MASK                            0xf
#घोषणा I2S2_OUT_MODE_MASK_SFT                        (0xf << 8)
#घोषणा INV_LRCK_SFT                                  5
#घोषणा INV_LRCK_MASK                                 0x1
#घोषणा INV_LRCK_MASK_SFT                             (0x1 << 5)
#घोषणा I2S2_FMT_SFT                                  3
#घोषणा I2S2_FMT_MASK                                 0x1
#घोषणा I2S2_FMT_MASK_SFT                             (0x1 << 3)
#घोषणा I2S2_WLEN_SFT                                 1
#घोषणा I2S2_WLEN_MASK                                0x1
#घोषणा I2S2_WLEN_MASK_SFT                            (0x1 << 1)
#घोषणा I2S2_EN_SFT                                   0
#घोषणा I2S2_EN_MASK                                  0x1
#घोषणा I2S2_EN_MASK_SFT                              (0x1 << 0)

/* AFE_I2S_CON2 */
#घोषणा I2S3_LR_SWAP_SFT                              31
#घोषणा I2S3_LR_SWAP_MASK                             0x1
#घोषणा I2S3_LR_SWAP_MASK_SFT                         (0x1 << 31)
#घोषणा I2S3_UPDATE_WORD_SFT                          24
#घोषणा I2S3_UPDATE_WORD_MASK                         0x1f
#घोषणा I2S3_UPDATE_WORD_MASK_SFT                     (0x1f << 24)
#घोषणा I2S3_BCK_INV_SFT                              23
#घोषणा I2S3_BCK_INV_MASK                             0x1
#घोषणा I2S3_BCK_INV_MASK_SFT                         (0x1 << 23)
#घोषणा I2S3_FPGA_BIT_TEST_SFT                        22
#घोषणा I2S3_FPGA_BIT_TEST_MASK                       0x1
#घोषणा I2S3_FPGA_BIT_TEST_MASK_SFT                   (0x1 << 22)
#घोषणा I2S3_FPGA_BIT_SFT                             21
#घोषणा I2S3_FPGA_BIT_MASK                            0x1
#घोषणा I2S3_FPGA_BIT_MASK_SFT                        (0x1 << 21)
#घोषणा I2S3_LOOPBACK_SFT                             20
#घोषणा I2S3_LOOPBACK_MASK                            0x1
#घोषणा I2S3_LOOPBACK_MASK_SFT                        (0x1 << 20)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT             17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK            0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT        (0x1 << 17)
#घोषणा I2S3_HD_EN_SFT                                12
#घोषणा I2S3_HD_EN_MASK                               0x1
#घोषणा I2S3_HD_EN_MASK_SFT                           (0x1 << 12)
#घोषणा I2S3_OUT_MODE_SFT                             8
#घोषणा I2S3_OUT_MODE_MASK                            0xf
#घोषणा I2S3_OUT_MODE_MASK_SFT                        (0xf << 8)
#घोषणा I2S3_FMT_SFT                                  3
#घोषणा I2S3_FMT_MASK                                 0x1
#घोषणा I2S3_FMT_MASK_SFT                             (0x1 << 3)
#घोषणा I2S3_WLEN_SFT                                 1
#घोषणा I2S3_WLEN_MASK                                0x1
#घोषणा I2S3_WLEN_MASK_SFT                            (0x1 << 1)
#घोषणा I2S3_EN_SFT                                   0
#घोषणा I2S3_EN_MASK                                  0x1
#घोषणा I2S3_EN_MASK_SFT                              (0x1 << 0)

/* AFE_I2S_CON3 */
#घोषणा I2S4_LR_SWAP_SFT                              31
#घोषणा I2S4_LR_SWAP_MASK                             0x1
#घोषणा I2S4_LR_SWAP_MASK_SFT                         (0x1 << 31)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT             17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK            0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT        (0x1 << 17)
#घोषणा I2S4_32BIT_EN_SFT                             13
#घोषणा I2S4_32BIT_EN_MASK                            0x1
#घोषणा I2S4_32BIT_EN_MASK_SFT                        (0x1 << 13)
#घोषणा I2S4_HD_EN_SFT                                12
#घोषणा I2S4_HD_EN_MASK                               0x1
#घोषणा I2S4_HD_EN_MASK_SFT                           (0x1 << 12)
#घोषणा I2S4_OUT_MODE_SFT                             8
#घोषणा I2S4_OUT_MODE_MASK                            0xf
#घोषणा I2S4_OUT_MODE_MASK_SFT                        (0xf << 8)
#घोषणा INV_LRCK_SFT                                  5
#घोषणा INV_LRCK_MASK                                 0x1
#घोषणा INV_LRCK_MASK_SFT                             (0x1 << 5)
#घोषणा I2S4_FMT_SFT                                  3
#घोषणा I2S4_FMT_MASK                                 0x1
#घोषणा I2S4_FMT_MASK_SFT                             (0x1 << 3)
#घोषणा I2S4_WLEN_SFT                                 1
#घोषणा I2S4_WLEN_MASK                                0x1
#घोषणा I2S4_WLEN_MASK_SFT                            (0x1 << 1)
#घोषणा I2S4_EN_SFT                                   0
#घोषणा I2S4_EN_MASK                                  0x1
#घोषणा I2S4_EN_MASK_SFT                              (0x1 << 0)

/* AFE_I2S_CON4 */
#घोषणा I2S5_LR_SWAP_SFT                              31
#घोषणा I2S5_LR_SWAP_MASK                             0x1
#घोषणा I2S5_LR_SWAP_MASK_SFT                         (0x1 << 31)
#घोषणा I2S_LOOPBACK_SFT                              20
#घोषणा I2S_LOOPBACK_MASK                             0x1
#घोषणा I2S_LOOPBACK_MASK_SFT                         (0x1 << 20)
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_SFT             17
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK            0x1
#घोषणा I2S_ONOFF_NOT_RESET_CK_ENABLE_MASK_SFT        (0x1 << 17)
#घोषणा I2S5_32BIT_EN_SFT                             13
#घोषणा I2S5_32BIT_EN_MASK                            0x1
#घोषणा I2S5_32BIT_EN_MASK_SFT                        (0x1 << 13)
#घोषणा I2S5_HD_EN_SFT                                12
#घोषणा I2S5_HD_EN_MASK                               0x1
#घोषणा I2S5_HD_EN_MASK_SFT                           (0x1 << 12)
#घोषणा I2S5_OUT_MODE_SFT                             8
#घोषणा I2S5_OUT_MODE_MASK                            0xf
#घोषणा I2S5_OUT_MODE_MASK_SFT                        (0xf << 8)
#घोषणा INV_LRCK_SFT                                  5
#घोषणा INV_LRCK_MASK                                 0x1
#घोषणा INV_LRCK_MASK_SFT                             (0x1 << 5)
#घोषणा I2S5_FMT_SFT                                  3
#घोषणा I2S5_FMT_MASK                                 0x1
#घोषणा I2S5_FMT_MASK_SFT                             (0x1 << 3)
#घोषणा I2S5_WLEN_SFT                                 1
#घोषणा I2S5_WLEN_MASK                                0x1
#घोषणा I2S5_WLEN_MASK_SFT                            (0x1 << 1)
#घोषणा I2S5_EN_SFT                                   0
#घोषणा I2S5_EN_MASK                                  0x1
#घोषणा I2S5_EN_MASK_SFT                              (0x1 << 0)

/* AFE_GAIN1_CON0 */
#घोषणा GAIN1_SAMPLE_PER_STEP_SFT                     8
#घोषणा GAIN1_SAMPLE_PER_STEP_MASK                    0xff
#घोषणा GAIN1_SAMPLE_PER_STEP_MASK_SFT                (0xff << 8)
#घोषणा GAIN1_MODE_SFT                                4
#घोषणा GAIN1_MODE_MASK                               0xf
#घोषणा GAIN1_MODE_MASK_SFT                           (0xf << 4)
#घोषणा GAIN1_ON_SFT                                  0
#घोषणा GAIN1_ON_MASK                                 0x1
#घोषणा GAIN1_ON_MASK_SFT                             (0x1 << 0)

/* AFE_GAIN1_CON1 */
#घोषणा GAIN1_TARGET_SFT                              0
#घोषणा GAIN1_TARGET_MASK                             0xfffff
#घोषणा GAIN1_TARGET_MASK_SFT                         (0xfffff << 0)

/* AFE_GAIN2_CON0 */
#घोषणा GAIN2_SAMPLE_PER_STEP_SFT                     8
#घोषणा GAIN2_SAMPLE_PER_STEP_MASK                    0xff
#घोषणा GAIN2_SAMPLE_PER_STEP_MASK_SFT                (0xff << 8)
#घोषणा GAIN2_MODE_SFT                                4
#घोषणा GAIN2_MODE_MASK                               0xf
#घोषणा GAIN2_MODE_MASK_SFT                           (0xf << 4)
#घोषणा GAIN2_ON_SFT                                  0
#घोषणा GAIN2_ON_MASK                                 0x1
#घोषणा GAIN2_ON_MASK_SFT                             (0x1 << 0)

/* AFE_GAIN2_CON1 */
#घोषणा GAIN2_TARGET_SFT                              0
#घोषणा GAIN2_TARGET_MASK                             0xfffff
#घोषणा GAIN2_TARGET_MASK_SFT                         (0xfffff << 0)

/* AFE_GAIN1_CUR */
#घोषणा AFE_GAIN1_CUR_SFT                             0
#घोषणा AFE_GAIN1_CUR_MASK                            0xfffff
#घोषणा AFE_GAIN1_CUR_MASK_SFT                        (0xfffff << 0)

/* AFE_GAIN2_CUR */
#घोषणा AFE_GAIN2_CUR_SFT                             0
#घोषणा AFE_GAIN2_CUR_MASK                            0xfffff
#घोषणा AFE_GAIN2_CUR_MASK_SFT                        (0xfffff << 0)

/* AFE_MEMIF_HD_MODE */
#घोषणा AWB2_HD_SFT                                   28
#घोषणा AWB2_HD_MASK                                  0x3
#घोषणा AWB2_HD_MASK_SFT                              (0x3 << 28)
#घोषणा HDMI_HD_SFT                                   20
#घोषणा HDMI_HD_MASK                                  0x3
#घोषणा HDMI_HD_MASK_SFT                              (0x3 << 20)
#घोषणा MOD_DAI_HD_SFT                                18
#घोषणा MOD_DAI_HD_MASK                               0x3
#घोषणा MOD_DAI_HD_MASK_SFT                           (0x3 << 18)
#घोषणा DAI_HD_SFT                                    16
#घोषणा DAI_HD_MASK                                   0x3
#घोषणा DAI_HD_MASK_SFT                               (0x3 << 16)
#घोषणा VUL2_HD_SFT                                   14
#घोषणा VUL2_HD_MASK                                  0x3
#घोषणा VUL2_HD_MASK_SFT                              (0x3 << 14)
#घोषणा VUL12_HD_SFT                                  12
#घोषणा VUL12_HD_MASK                                 0x3
#घोषणा VUL12_HD_MASK_SFT                             (0x3 << 12)
#घोषणा VUL_HD_SFT                                    10
#घोषणा VUL_HD_MASK                                   0x3
#घोषणा VUL_HD_MASK_SFT                               (0x3 << 10)
#घोषणा AWB_HD_SFT                                    8
#घोषणा AWB_HD_MASK                                   0x3
#घोषणा AWB_HD_MASK_SFT                               (0x3 << 8)
#घोषणा DL3_HD_SFT                                    6
#घोषणा DL3_HD_MASK                                   0x3
#घोषणा DL3_HD_MASK_SFT                               (0x3 << 6)
#घोषणा DL2_HD_SFT                                    4
#घोषणा DL2_HD_MASK                                   0x3
#घोषणा DL2_HD_MASK_SFT                               (0x3 << 4)
#घोषणा DL1_HD_SFT                                    0
#घोषणा DL1_HD_MASK                                   0x3
#घोषणा DL1_HD_MASK_SFT                               (0x3 << 0)

/* AFE_MEMIF_HDALIGN */
#घोषणा AWB2_NORMAL_MODE_SFT                          30
#घोषणा AWB2_NORMAL_MODE_MASK                         0x1
#घोषणा AWB2_NORMAL_MODE_MASK_SFT                     (0x1 << 30)
#घोषणा HDMI_NORMAL_MODE_SFT                          26
#घोषणा HDMI_NORMAL_MODE_MASK                         0x1
#घोषणा HDMI_NORMAL_MODE_MASK_SFT                     (0x1 << 26)
#घोषणा MOD_DAI_NORMAL_MODE_SFT                       25
#घोषणा MOD_DAI_NORMAL_MODE_MASK                      0x1
#घोषणा MOD_DAI_NORMAL_MODE_MASK_SFT                  (0x1 << 25)
#घोषणा DAI_NORMAL_MODE_SFT                           24
#घोषणा DAI_NORMAL_MODE_MASK                          0x1
#घोषणा DAI_NORMAL_MODE_MASK_SFT                      (0x1 << 24)
#घोषणा VUL2_NORMAL_MODE_SFT                          23
#घोषणा VUL2_NORMAL_MODE_MASK                         0x1
#घोषणा VUL2_NORMAL_MODE_MASK_SFT                     (0x1 << 23)
#घोषणा VUL12_NORMAL_MODE_SFT                         22
#घोषणा VUL12_NORMAL_MODE_MASK                        0x1
#घोषणा VUL12_NORMAL_MODE_MASK_SFT                    (0x1 << 22)
#घोषणा VUL_NORMAL_MODE_SFT                           21
#घोषणा VUL_NORMAL_MODE_MASK                          0x1
#घोषणा VUL_NORMAL_MODE_MASK_SFT                      (0x1 << 21)
#घोषणा AWB_NORMAL_MODE_SFT                           20
#घोषणा AWB_NORMAL_MODE_MASK                          0x1
#घोषणा AWB_NORMAL_MODE_MASK_SFT                      (0x1 << 20)
#घोषणा DL3_NORMAL_MODE_SFT                           19
#घोषणा DL3_NORMAL_MODE_MASK                          0x1
#घोषणा DL3_NORMAL_MODE_MASK_SFT                      (0x1 << 19)
#घोषणा DL2_NORMAL_MODE_SFT                           18
#घोषणा DL2_NORMAL_MODE_MASK                          0x1
#घोषणा DL2_NORMAL_MODE_MASK_SFT                      (0x1 << 18)
#घोषणा DL1_NORMAL_MODE_SFT                           16
#घोषणा DL1_NORMAL_MODE_MASK                          0x1
#घोषणा DL1_NORMAL_MODE_MASK_SFT                      (0x1 << 16)
#घोषणा RESERVED1_SFT                                 15
#घोषणा RESERVED1_MASK                                0x1
#घोषणा RESERVED1_MASK_SFT                            (0x1 << 15)
#घोषणा AWB2_ALIGN_SFT                                14
#घोषणा AWB2_ALIGN_MASK                               0x1
#घोषणा AWB2_ALIGN_MASK_SFT                           (0x1 << 14)
#घोषणा HDMI_HD_ALIGN_SFT                             10
#घोषणा HDMI_HD_ALIGN_MASK                            0x1
#घोषणा HDMI_HD_ALIGN_MASK_SFT                        (0x1 << 10)
#घोषणा MOD_DAI_HD_ALIGN_SFT                          9
#घोषणा MOD_DAI_HD_ALIGN_MASK                         0x1
#घोषणा MOD_DAI_HD_ALIGN_MASK_SFT                     (0x1 << 9)
#घोषणा VUL2_HD_ALIGN_SFT                             7
#घोषणा VUL2_HD_ALIGN_MASK                            0x1
#घोषणा VUL2_HD_ALIGN_MASK_SFT                        (0x1 << 7)
#घोषणा VUL12_HD_ALIGN_SFT                            6
#घोषणा VUL12_HD_ALIGN_MASK                           0x1
#घोषणा VUL12_HD_ALIGN_MASK_SFT                       (0x1 << 6)
#घोषणा VUL_HD_ALIGN_SFT                              5
#घोषणा VUL_HD_ALIGN_MASK                             0x1
#घोषणा VUL_HD_ALIGN_MASK_SFT                         (0x1 << 5)
#घोषणा AWB_HD_ALIGN_SFT                              4
#घोषणा AWB_HD_ALIGN_MASK                             0x1
#घोषणा AWB_HD_ALIGN_MASK_SFT                         (0x1 << 4)
#घोषणा DL3_HD_ALIGN_SFT                              3
#घोषणा DL3_HD_ALIGN_MASK                             0x1
#घोषणा DL3_HD_ALIGN_MASK_SFT                         (0x1 << 3)
#घोषणा DL2_HD_ALIGN_SFT                              2
#घोषणा DL2_HD_ALIGN_MASK                             0x1
#घोषणा DL2_HD_ALIGN_MASK_SFT                         (0x1 << 2)
#घोषणा DL1_HD_ALIGN_SFT                              0
#घोषणा DL1_HD_ALIGN_MASK                             0x1
#घोषणा DL1_HD_ALIGN_MASK_SFT                         (0x1 << 0)

/* PCM_INTF_CON1 */
#घोषणा PCM_FIX_VALUE_SEL_SFT                         31
#घोषणा PCM_FIX_VALUE_SEL_MASK                        0x1
#घोषणा PCM_FIX_VALUE_SEL_MASK_SFT                    (0x1 << 31)
#घोषणा PCM_BUFFER_LOOPBACK_SFT                       30
#घोषणा PCM_BUFFER_LOOPBACK_MASK                      0x1
#घोषणा PCM_BUFFER_LOOPBACK_MASK_SFT                  (0x1 << 30)
#घोषणा PCM_PARALLEL_LOOPBACK_SFT                     29
#घोषणा PCM_PARALLEL_LOOPBACK_MASK                    0x1
#घोषणा PCM_PARALLEL_LOOPBACK_MASK_SFT                (0x1 << 29)
#घोषणा PCM_SERIAL_LOOPBACK_SFT                       28
#घोषणा PCM_SERIAL_LOOPBACK_MASK                      0x1
#घोषणा PCM_SERIAL_LOOPBACK_MASK_SFT                  (0x1 << 28)
#घोषणा PCM_DAI_PCM_LOOPBACK_SFT                      27
#घोषणा PCM_DAI_PCM_LOOPBACK_MASK                     0x1
#घोषणा PCM_DAI_PCM_LOOPBACK_MASK_SFT                 (0x1 << 27)
#घोषणा PCM_I2S_PCM_LOOPBACK_SFT                      26
#घोषणा PCM_I2S_PCM_LOOPBACK_MASK                     0x1
#घोषणा PCM_I2S_PCM_LOOPBACK_MASK_SFT                 (0x1 << 26)
#घोषणा PCM_SYNC_DELSEL_SFT                           25
#घोषणा PCM_SYNC_DELSEL_MASK                          0x1
#घोषणा PCM_SYNC_DELSEL_MASK_SFT                      (0x1 << 25)
#घोषणा PCM_TX_LR_SWAP_SFT                            24
#घोषणा PCM_TX_LR_SWAP_MASK                           0x1
#घोषणा PCM_TX_LR_SWAP_MASK_SFT                       (0x1 << 24)
#घोषणा PCM_SYNC_OUT_INV_SFT                          23
#घोषणा PCM_SYNC_OUT_INV_MASK                         0x1
#घोषणा PCM_SYNC_OUT_INV_MASK_SFT                     (0x1 << 23)
#घोषणा PCM_BCLK_OUT_INV_SFT                          22
#घोषणा PCM_BCLK_OUT_INV_MASK                         0x1
#घोषणा PCM_BCLK_OUT_INV_MASK_SFT                     (0x1 << 22)
#घोषणा PCM_SYNC_IN_INV_SFT                           21
#घोषणा PCM_SYNC_IN_INV_MASK                          0x1
#घोषणा PCM_SYNC_IN_INV_MASK_SFT                      (0x1 << 21)
#घोषणा PCM_BCLK_IN_INV_SFT                           20
#घोषणा PCM_BCLK_IN_INV_MASK                          0x1
#घोषणा PCM_BCLK_IN_INV_MASK_SFT                      (0x1 << 20)
#घोषणा PCM_TX_LCH_RPT_SFT                            19
#घोषणा PCM_TX_LCH_RPT_MASK                           0x1
#घोषणा PCM_TX_LCH_RPT_MASK_SFT                       (0x1 << 19)
#घोषणा PCM_VBT_16K_MODE_SFT                          18
#घोषणा PCM_VBT_16K_MODE_MASK                         0x1
#घोषणा PCM_VBT_16K_MODE_MASK_SFT                     (0x1 << 18)
#घोषणा PCM_EXT_MODEM_SFT                             17
#घोषणा PCM_EXT_MODEM_MASK                            0x1
#घोषणा PCM_EXT_MODEM_MASK_SFT                        (0x1 << 17)
#घोषणा PCM_24BIT_SFT                                 16
#घोषणा PCM_24BIT_MASK                                0x1
#घोषणा PCM_24BIT_MASK_SFT                            (0x1 << 16)
#घोषणा PCM_WLEN_SFT                                  14
#घोषणा PCM_WLEN_MASK                                 0x3
#घोषणा PCM_WLEN_MASK_SFT                             (0x3 << 14)
#घोषणा PCM_SYNC_LENGTH_SFT                           9
#घोषणा PCM_SYNC_LENGTH_MASK                          0x1f
#घोषणा PCM_SYNC_LENGTH_MASK_SFT                      (0x1f << 9)
#घोषणा PCM_SYNC_TYPE_SFT                             8
#घोषणा PCM_SYNC_TYPE_MASK                            0x1
#घोषणा PCM_SYNC_TYPE_MASK_SFT                        (0x1 << 8)
#घोषणा PCM_BT_MODE_SFT                               7
#घोषणा PCM_BT_MODE_MASK                              0x1
#घोषणा PCM_BT_MODE_MASK_SFT                          (0x1 << 7)
#घोषणा PCM_BYP_ASRC_SFT                              6
#घोषणा PCM_BYP_ASRC_MASK                             0x1
#घोषणा PCM_BYP_ASRC_MASK_SFT                         (0x1 << 6)
#घोषणा PCM_SLAVE_SFT                                 5
#घोषणा PCM_SLAVE_MASK                                0x1
#घोषणा PCM_SLAVE_MASK_SFT                            (0x1 << 5)
#घोषणा PCM_MODE_SFT                                  3
#घोषणा PCM_MODE_MASK                                 0x3
#घोषणा PCM_MODE_MASK_SFT                             (0x3 << 3)
#घोषणा PCM_FMT_SFT                                   1
#घोषणा PCM_FMT_MASK                                  0x3
#घोषणा PCM_FMT_MASK_SFT                              (0x3 << 1)
#घोषणा PCM_EN_SFT                                    0
#घोषणा PCM_EN_MASK                                   0x1
#घोषणा PCM_EN_MASK_SFT                               (0x1 << 0)

/* PCM_INTF_CON2 */
#घोषणा PCM1_TX_FIFO_OV_SFT                           31
#घोषणा PCM1_TX_FIFO_OV_MASK                          0x1
#घोषणा PCM1_TX_FIFO_OV_MASK_SFT                      (0x1 << 31)
#घोषणा PCM1_RX_FIFO_OV_SFT                           30
#घोषणा PCM1_RX_FIFO_OV_MASK                          0x1
#घोषणा PCM1_RX_FIFO_OV_MASK_SFT                      (0x1 << 30)
#घोषणा PCM2_TX_FIFO_OV_SFT                           29
#घोषणा PCM2_TX_FIFO_OV_MASK                          0x1
#घोषणा PCM2_TX_FIFO_OV_MASK_SFT                      (0x1 << 29)
#घोषणा PCM2_RX_FIFO_OV_SFT                           28
#घोषणा PCM2_RX_FIFO_OV_MASK                          0x1
#घोषणा PCM2_RX_FIFO_OV_MASK_SFT                      (0x1 << 28)
#घोषणा PCM1_SYNC_GLITCH_SFT                          27
#घोषणा PCM1_SYNC_GLITCH_MASK                         0x1
#घोषणा PCM1_SYNC_GLITCH_MASK_SFT                     (0x1 << 27)
#घोषणा PCM2_SYNC_GLITCH_SFT                          26
#घोषणा PCM2_SYNC_GLITCH_MASK                         0x1
#घोषणा PCM2_SYNC_GLITCH_MASK_SFT                     (0x1 << 26)
#घोषणा TX3_RCH_DBG_MODE_SFT                          17
#घोषणा TX3_RCH_DBG_MODE_MASK                         0x1
#घोषणा TX3_RCH_DBG_MODE_MASK_SFT                     (0x1 << 17)
#घोषणा PCM1_PCM2_LOOPBACK_SFT                        16
#घोषणा PCM1_PCM2_LOOPBACK_MASK                       0x1
#घोषणा PCM1_PCM2_LOOPBACK_MASK_SFT                   (0x1 << 16)
#घोषणा DAI_PCM_LOOPBACK_CH_SFT                       14
#घोषणा DAI_PCM_LOOPBACK_CH_MASK                      0x3
#घोषणा DAI_PCM_LOOPBACK_CH_MASK_SFT                  (0x3 << 14)
#घोषणा I2S_PCM_LOOPBACK_CH_SFT                       12
#घोषणा I2S_PCM_LOOPBACK_CH_MASK                      0x3
#घोषणा I2S_PCM_LOOPBACK_CH_MASK_SFT                  (0x3 << 12)
#घोषणा TX_FIX_VALUE_SFT                              0
#घोषणा TX_FIX_VALUE_MASK                             0xff
#घोषणा TX_FIX_VALUE_MASK_SFT                         (0xff << 0)

/* PCM2_INTF_CON */
#घोषणा PCM2_TX_FIX_VALUE_SFT                         24
#घोषणा PCM2_TX_FIX_VALUE_MASK                        0xff
#घोषणा PCM2_TX_FIX_VALUE_MASK_SFT                    (0xff << 24)
#घोषणा PCM2_FIX_VALUE_SEL_SFT                        23
#घोषणा PCM2_FIX_VALUE_SEL_MASK                       0x1
#घोषणा PCM2_FIX_VALUE_SEL_MASK_SFT                   (0x1 << 23)
#घोषणा PCM2_BUFFER_LOOPBACK_SFT                      22
#घोषणा PCM2_BUFFER_LOOPBACK_MASK                     0x1
#घोषणा PCM2_BUFFER_LOOPBACK_MASK_SFT                 (0x1 << 22)
#घोषणा PCM2_PARALLEL_LOOPBACK_SFT                    21
#घोषणा PCM2_PARALLEL_LOOPBACK_MASK                   0x1
#घोषणा PCM2_PARALLEL_LOOPBACK_MASK_SFT               (0x1 << 21)
#घोषणा PCM2_SERIAL_LOOPBACK_SFT                      20
#घोषणा PCM2_SERIAL_LOOPBACK_MASK                     0x1
#घोषणा PCM2_SERIAL_LOOPBACK_MASK_SFT                 (0x1 << 20)
#घोषणा PCM2_DAI_PCM_LOOPBACK_SFT                     19
#घोषणा PCM2_DAI_PCM_LOOPBACK_MASK                    0x1
#घोषणा PCM2_DAI_PCM_LOOPBACK_MASK_SFT                (0x1 << 19)
#घोषणा PCM2_I2S_PCM_LOOPBACK_SFT                     18
#घोषणा PCM2_I2S_PCM_LOOPBACK_MASK                    0x1
#घोषणा PCM2_I2S_PCM_LOOPBACK_MASK_SFT                (0x1 << 18)
#घोषणा PCM2_SYNC_DELSEL_SFT                          17
#घोषणा PCM2_SYNC_DELSEL_MASK                         0x1
#घोषणा PCM2_SYNC_DELSEL_MASK_SFT                     (0x1 << 17)
#घोषणा PCM2_TX_LR_SWAP_SFT                           16
#घोषणा PCM2_TX_LR_SWAP_MASK                          0x1
#घोषणा PCM2_TX_LR_SWAP_MASK_SFT                      (0x1 << 16)
#घोषणा PCM2_SYNC_IN_INV_SFT                          15
#घोषणा PCM2_SYNC_IN_INV_MASK                         0x1
#घोषणा PCM2_SYNC_IN_INV_MASK_SFT                     (0x1 << 15)
#घोषणा PCM2_BCLK_IN_INV_SFT                          14
#घोषणा PCM2_BCLK_IN_INV_MASK                         0x1
#घोषणा PCM2_BCLK_IN_INV_MASK_SFT                     (0x1 << 14)
#घोषणा PCM2_TX_LCH_RPT_SFT                           13
#घोषणा PCM2_TX_LCH_RPT_MASK                          0x1
#घोषणा PCM2_TX_LCH_RPT_MASK_SFT                      (0x1 << 13)
#घोषणा PCM2_VBT_16K_MODE_SFT                         12
#घोषणा PCM2_VBT_16K_MODE_MASK                        0x1
#घोषणा PCM2_VBT_16K_MODE_MASK_SFT                    (0x1 << 12)
#घोषणा PCM2_LOOPBACK_CH_SEL_SFT                      10
#घोषणा PCM2_LOOPBACK_CH_SEL_MASK                     0x3
#घोषणा PCM2_LOOPBACK_CH_SEL_MASK_SFT                 (0x3 << 10)
#घोषणा PCM2_TX2_BT_MODE_SFT                          8
#घोषणा PCM2_TX2_BT_MODE_MASK                         0x1
#घोषणा PCM2_TX2_BT_MODE_MASK_SFT                     (0x1 << 8)
#घोषणा PCM2_BT_MODE_SFT                              7
#घोषणा PCM2_BT_MODE_MASK                             0x1
#घोषणा PCM2_BT_MODE_MASK_SFT                         (0x1 << 7)
#घोषणा PCM2_AFIFO_SFT                                6
#घोषणा PCM2_AFIFO_MASK                               0x1
#घोषणा PCM2_AFIFO_MASK_SFT                           (0x1 << 6)
#घोषणा PCM2_WLEN_SFT                                 5
#घोषणा PCM2_WLEN_MASK                                0x1
#घोषणा PCM2_WLEN_MASK_SFT                            (0x1 << 5)
#घोषणा PCM2_MODE_SFT                                 3
#घोषणा PCM2_MODE_MASK                                0x3
#घोषणा PCM2_MODE_MASK_SFT                            (0x3 << 3)
#घोषणा PCM2_FMT_SFT                                  1
#घोषणा PCM2_FMT_MASK                                 0x3
#घोषणा PCM2_FMT_MASK_SFT                             (0x3 << 1)
#घोषणा PCM2_EN_SFT                                   0
#घोषणा PCM2_EN_MASK                                  0x1
#घोषणा PCM2_EN_MASK_SFT                              (0x1 << 0)

/* AFE_ADDA_MTKAIF_CFG0 */
#घोषणा MTKAIF_RXIF_CLKINV_ADC_SFT                    31
#घोषणा MTKAIF_RXIF_CLKINV_ADC_MASK                   0x1
#घोषणा MTKAIF_RXIF_CLKINV_ADC_MASK_SFT               (0x1 << 31)
#घोषणा MTKAIF_RXIF_BYPASS_SRC_SFT                    17
#घोषणा MTKAIF_RXIF_BYPASS_SRC_MASK                   0x1
#घोषणा MTKAIF_RXIF_BYPASS_SRC_MASK_SFT               (0x1 << 17)
#घोषणा MTKAIF_RXIF_PROTOCOL2_SFT                     16
#घोषणा MTKAIF_RXIF_PROTOCOL2_MASK                    0x1
#घोषणा MTKAIF_RXIF_PROTOCOL2_MASK_SFT                (0x1 << 16)
#घोषणा MTKAIF_TXIF_BYPASS_SRC_SFT                    5
#घोषणा MTKAIF_TXIF_BYPASS_SRC_MASK                   0x1
#घोषणा MTKAIF_TXIF_BYPASS_SRC_MASK_SFT               (0x1 << 5)
#घोषणा MTKAIF_TXIF_PROTOCOL2_SFT                     4
#घोषणा MTKAIF_TXIF_PROTOCOL2_MASK                    0x1
#घोषणा MTKAIF_TXIF_PROTOCOL2_MASK_SFT                (0x1 << 4)
#घोषणा MTKAIF_TXIF_8TO5_SFT                          2
#घोषणा MTKAIF_TXIF_8TO5_MASK                         0x1
#घोषणा MTKAIF_TXIF_8TO5_MASK_SFT                     (0x1 << 2)
#घोषणा MTKAIF_RXIF_8TO5_SFT                          1
#घोषणा MTKAIF_RXIF_8TO5_MASK                         0x1
#घोषणा MTKAIF_RXIF_8TO5_MASK_SFT                     (0x1 << 1)
#घोषणा MTKAIF_IF_LOOPBACK1_SFT                       0
#घोषणा MTKAIF_IF_LOOPBACK1_MASK                      0x1
#घोषणा MTKAIF_IF_LOOPBACK1_MASK_SFT                  (0x1 << 0)

/* AFE_ADDA_MTKAIF_RX_CFG2 */
#घोषणा MTKAIF_RXIF_DETECT_ON_PROTOCOL2_SFT           16
#घोषणा MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK          0x1
#घोषणा MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK_SFT      (0x1 << 16)
#घोषणा MTKAIF_RXIF_DELAY_CYCLE_SFT                   12
#घोषणा MTKAIF_RXIF_DELAY_CYCLE_MASK                  0xf
#घोषणा MTKAIF_RXIF_DELAY_CYCLE_MASK_SFT              (0xf << 12)
#घोषणा MTKAIF_RXIF_DELAY_DATA_SFT                    8
#घोषणा MTKAIF_RXIF_DELAY_DATA_MASK                   0x1
#घोषणा MTKAIF_RXIF_DELAY_DATA_MASK_SFT               (0x1 << 8)
#घोषणा MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_SFT            4
#घोषणा MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK           0x7
#घोषणा MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK_SFT       (0x7 << 4)

/* AFE_ADDA_DL_SRC2_CON0 */
#घोषणा DL_2_INPUT_MODE_CTL_SFT                       28
#घोषणा DL_2_INPUT_MODE_CTL_MASK                      0xf
#घोषणा DL_2_INPUT_MODE_CTL_MASK_SFT                  (0xf << 28)
#घोषणा DL_2_CH1_SATURATION_EN_CTL_SFT                27
#घोषणा DL_2_CH1_SATURATION_EN_CTL_MASK               0x1
#घोषणा DL_2_CH1_SATURATION_EN_CTL_MASK_SFT           (0x1 << 27)
#घोषणा DL_2_CH2_SATURATION_EN_CTL_SFT                26
#घोषणा DL_2_CH2_SATURATION_EN_CTL_MASK               0x1
#घोषणा DL_2_CH2_SATURATION_EN_CTL_MASK_SFT           (0x1 << 26)
#घोषणा DL_2_OUTPUT_SEL_CTL_SFT                       24
#घोषणा DL_2_OUTPUT_SEL_CTL_MASK                      0x3
#घोषणा DL_2_OUTPUT_SEL_CTL_MASK_SFT                  (0x3 << 24)
#घोषणा DL_2_FADEIN_0START_EN_SFT                     16
#घोषणा DL_2_FADEIN_0START_EN_MASK                    0x3
#घोषणा DL_2_FADEIN_0START_EN_MASK_SFT                (0x3 << 16)
#घोषणा DL_DISABLE_HW_CG_CTL_SFT                      15
#घोषणा DL_DISABLE_HW_CG_CTL_MASK                     0x1
#घोषणा DL_DISABLE_HW_CG_CTL_MASK_SFT                 (0x1 << 15)
#घोषणा C_DATA_EN_SEL_CTL_PRE_SFT                     14
#घोषणा C_DATA_EN_SEL_CTL_PRE_MASK                    0x1
#घोषणा C_DATA_EN_SEL_CTL_PRE_MASK_SFT                (0x1 << 14)
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_SFT                 13
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_MASK                0x1
#घोषणा DL_2_SIDE_TONE_ON_CTL_PRE_MASK_SFT            (0x1 << 13)
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_SFT                 12
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_MASK                0x1
#घोषणा DL_2_MUTE_CH1_OFF_CTL_PRE_MASK_SFT            (0x1 << 12)
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_SFT                 11
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_MASK                0x1
#घोषणा DL_2_MUTE_CH2_OFF_CTL_PRE_MASK_SFT            (0x1 << 11)
#घोषणा DL2_ARAMPSP_CTL_PRE_SFT                       9
#घोषणा DL2_ARAMPSP_CTL_PRE_MASK                      0x3
#घोषणा DL2_ARAMPSP_CTL_PRE_MASK_SFT                  (0x3 << 9)
#घोषणा DL_2_IIRMODE_CTL_PRE_SFT                      6
#घोषणा DL_2_IIRMODE_CTL_PRE_MASK                     0x7
#घोषणा DL_2_IIRMODE_CTL_PRE_MASK_SFT                 (0x7 << 6)
#घोषणा DL_2_VOICE_MODE_CTL_PRE_SFT                   5
#घोषणा DL_2_VOICE_MODE_CTL_PRE_MASK                  0x1
#घोषणा DL_2_VOICE_MODE_CTL_PRE_MASK_SFT              (0x1 << 5)
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_SFT                  4
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_MASK                 0x1
#घोषणा D2_2_MUTE_CH1_ON_CTL_PRE_MASK_SFT             (0x1 << 4)
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_SFT                  3
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_MASK                 0x1
#घोषणा D2_2_MUTE_CH2_ON_CTL_PRE_MASK_SFT             (0x1 << 3)
#घोषणा DL_2_IIR_ON_CTL_PRE_SFT                       2
#घोषणा DL_2_IIR_ON_CTL_PRE_MASK                      0x1
#घोषणा DL_2_IIR_ON_CTL_PRE_MASK_SFT                  (0x1 << 2)
#घोषणा DL_2_GAIN_ON_CTL_PRE_SFT                      1
#घोषणा DL_2_GAIN_ON_CTL_PRE_MASK                     0x1
#घोषणा DL_2_GAIN_ON_CTL_PRE_MASK_SFT                 (0x1 << 1)
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_SFT                   0
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK                  0x1
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK_SFT              (0x1 << 0)

/* AFE_ADDA_DL_SRC2_CON1 */
#घोषणा DL_2_GAIN_CTL_PRE_SFT                         16
#घोषणा DL_2_GAIN_CTL_PRE_MASK                        0xffff
#घोषणा DL_2_GAIN_CTL_PRE_MASK_SFT                    (0xffff << 16)
#घोषणा DL_2_GAIN_MODE_CTL_SFT                        0
#घोषणा DL_2_GAIN_MODE_CTL_MASK                       0x1
#घोषणा DL_2_GAIN_MODE_CTL_MASK_SFT                   (0x1 << 0)

/* AFE_ADDA_UL_SRC_CON0 */
#घोषणा ULCF_CFG_EN_CTL_SFT                           31
#घोषणा ULCF_CFG_EN_CTL_MASK                          0x1
#घोषणा ULCF_CFG_EN_CTL_MASK_SFT                      (0x1 << 31)
#घोषणा UL_MODE_3P25M_CH2_CTL_SFT                     22
#घोषणा UL_MODE_3P25M_CH2_CTL_MASK                    0x1
#घोषणा UL_MODE_3P25M_CH2_CTL_MASK_SFT                (0x1 << 22)
#घोषणा UL_MODE_3P25M_CH1_CTL_SFT                     21
#घोषणा UL_MODE_3P25M_CH1_CTL_MASK                    0x1
#घोषणा UL_MODE_3P25M_CH1_CTL_MASK_SFT                (0x1 << 21)
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_SFT                 17
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_MASK                0x7
#घोषणा UL_VOICE_MODE_CH1_CH2_CTL_MASK_SFT            (0x7 << 17)
#घोषणा DMIC_LOW_POWER_MODE_CTL_SFT                   14
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK                  0x3
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK_SFT              (0x3 << 14)
#घोषणा UL_DISABLE_HW_CG_CTL_SFT                      12
#घोषणा UL_DISABLE_HW_CG_CTL_MASK                     0x1
#घोषणा UL_DISABLE_HW_CG_CTL_MASK_SFT                 (0x1 << 12)
#घोषणा UL_IIR_ON_TMP_CTL_SFT                         10
#घोषणा UL_IIR_ON_TMP_CTL_MASK                        0x1
#घोषणा UL_IIR_ON_TMP_CTL_MASK_SFT                    (0x1 << 10)
#घोषणा UL_IIRMODE_CTL_SFT                            7
#घोषणा UL_IIRMODE_CTL_MASK                           0x7
#घोषणा UL_IIRMODE_CTL_MASK_SFT                       (0x7 << 7)
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_SFT               5
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK              0x1
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK_SFT          (0x1 << 5)
#घोषणा UL_LOOP_BACK_MODE_CTL_SFT                     2
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK                    0x1
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK_SFT                (0x1 << 2)
#घोषणा UL_SDM_3_LEVEL_CTL_SFT                        1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK                       0x1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK_SFT                   (0x1 << 1)
#घोषणा UL_SRC_ON_TMP_CTL_SFT                         0
#घोषणा UL_SRC_ON_TMP_CTL_MASK                        0x1
#घोषणा UL_SRC_ON_TMP_CTL_MASK_SFT                    (0x1 << 0)

/* AFE_ADDA_UL_SRC_CON1 */
#घोषणा C_DAC_EN_CTL_SFT                              27
#घोषणा C_DAC_EN_CTL_MASK                             0x1
#घोषणा C_DAC_EN_CTL_MASK_SFT                         (0x1 << 27)
#घोषणा C_MUTE_SW_CTL_SFT                             26
#घोषणा C_MUTE_SW_CTL_MASK                            0x1
#घोषणा C_MUTE_SW_CTL_MASK_SFT                        (0x1 << 26)
#घोषणा ASDM_SRC_SEL_CTL_SFT                          25
#घोषणा ASDM_SRC_SEL_CTL_MASK                         0x1
#घोषणा ASDM_SRC_SEL_CTL_MASK_SFT                     (0x1 << 25)
#घोषणा C_AMP_DIV_CH2_CTL_SFT                         21
#घोषणा C_AMP_DIV_CH2_CTL_MASK                        0x7
#घोषणा C_AMP_DIV_CH2_CTL_MASK_SFT                    (0x7 << 21)
#घोषणा C_FREQ_DIV_CH2_CTL_SFT                        16
#घोषणा C_FREQ_DIV_CH2_CTL_MASK                       0x1f
#घोषणा C_FREQ_DIV_CH2_CTL_MASK_SFT                   (0x1f << 16)
#घोषणा C_SINE_MODE_CH2_CTL_SFT                       12
#घोषणा C_SINE_MODE_CH2_CTL_MASK                      0xf
#घोषणा C_SINE_MODE_CH2_CTL_MASK_SFT                  (0xf << 12)
#घोषणा C_AMP_DIV_CH1_CTL_SFT                         9
#घोषणा C_AMP_DIV_CH1_CTL_MASK                        0x7
#घोषणा C_AMP_DIV_CH1_CTL_MASK_SFT                    (0x7 << 9)
#घोषणा C_FREQ_DIV_CH1_CTL_SFT                        4
#घोषणा C_FREQ_DIV_CH1_CTL_MASK                       0x1f
#घोषणा C_FREQ_DIV_CH1_CTL_MASK_SFT                   (0x1f << 4)
#घोषणा C_SINE_MODE_CH1_CTL_SFT                       0
#घोषणा C_SINE_MODE_CH1_CTL_MASK                      0xf
#घोषणा C_SINE_MODE_CH1_CTL_MASK_SFT                  (0xf << 0)

/* AFE_ADDA_TOP_CON0 */
#घोषणा C_LOOP_BACK_MODE_CTL_SFT                      12
#घोषणा C_LOOP_BACK_MODE_CTL_MASK                     0xf
#घोषणा C_LOOP_BACK_MODE_CTL_MASK_SFT                 (0xf << 12)
#घोषणा C_EXT_ADC_CTL_SFT                             0
#घोषणा C_EXT_ADC_CTL_MASK                            0x1
#घोषणा C_EXT_ADC_CTL_MASK_SFT                        (0x1 << 0)

/* AFE_ADDA_UL_DL_CON0 */
#घोषणा AFE_ADDA6_UL_LR_SWAP_SFT                      15
#घोषणा AFE_ADDA6_UL_LR_SWAP_MASK                     0x1
#घोषणा AFE_ADDA6_UL_LR_SWAP_MASK_SFT                 (0x1 << 15)
#घोषणा AFE_ADDA6_CKDIV_RST_SFT                       14
#घोषणा AFE_ADDA6_CKDIV_RST_MASK                      0x1
#घोषणा AFE_ADDA6_CKDIV_RST_MASK_SFT                  (0x1 << 14)
#घोषणा AFE_ADDA6_FIFO_AUTO_RST_SFT                   13
#घोषणा AFE_ADDA6_FIFO_AUTO_RST_MASK                  0x1
#घोषणा AFE_ADDA6_FIFO_AUTO_RST_MASK_SFT              (0x1 << 13)
#घोषणा UL_FIFO_DIGMIC_TESTIN_SFT                     5
#घोषणा UL_FIFO_DIGMIC_TESTIN_MASK                    0x3
#घोषणा UL_FIFO_DIGMIC_TESTIN_MASK_SFT                (0x3 << 5)
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTEN_SFT               4
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTEN_MASK              0x1
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTEN_MASK_SFT          (0x1 << 4)
#घोषणा ADDA_AFE_ON_SFT                               0
#घोषणा ADDA_AFE_ON_MASK                              0x1
#घोषणा ADDA_AFE_ON_MASK_SFT                          (0x1 << 0)

/* AFE_SIDETONE_CON0 */
#घोषणा R_RDY_SFT                                     30
#घोषणा R_RDY_MASK                                    0x1
#घोषणा R_RDY_MASK_SFT                                (0x1 << 30)
#घोषणा W_RDY_SFT                                     29
#घोषणा W_RDY_MASK                                    0x1
#घोषणा W_RDY_MASK_SFT                                (0x1 << 29)
#घोषणा R_W_EN_SFT                                    25
#घोषणा R_W_EN_MASK                                   0x1
#घोषणा R_W_EN_MASK_SFT                               (0x1 << 25)
#घोषणा R_W_SEL_SFT                                   24
#घोषणा R_W_SEL_MASK                                  0x1
#घोषणा R_W_SEL_MASK_SFT                              (0x1 << 24)
#घोषणा SEL_CH2_SFT                                   23
#घोषणा SEL_CH2_MASK                                  0x1
#घोषणा SEL_CH2_MASK_SFT                              (0x1 << 23)
#घोषणा SIDE_TONE_COEFFICIENT_ADDR_SFT                16
#घोषणा SIDE_TONE_COEFFICIENT_ADDR_MASK               0x1f
#घोषणा SIDE_TONE_COEFFICIENT_ADDR_MASK_SFT           (0x1f << 16)
#घोषणा SIDE_TONE_COEFFICIENT_SFT                     0
#घोषणा SIDE_TONE_COEFFICIENT_MASK                    0xffff
#घोषणा SIDE_TONE_COEFFICIENT_MASK_SFT                (0xffff << 0)

/* AFE_SIDETONE_COEFF */
#घोषणा SIDE_TONE_COEFF_SFT                           0
#घोषणा SIDE_TONE_COEFF_MASK                          0xffff
#घोषणा SIDE_TONE_COEFF_MASK_SFT                      (0xffff << 0)

/* AFE_SIDETONE_CON1 */
#घोषणा STF_BYPASS_MODE_SFT                           31
#घोषणा STF_BYPASS_MODE_MASK                          0x1
#घोषणा STF_BYPASS_MODE_MASK_SFT                      (0x1 << 31)
#घोषणा STF_BYPASS_MODE_O28_O29_SFT                   30
#घोषणा STF_BYPASS_MODE_O28_O29_MASK                  0x1
#घोषणा STF_BYPASS_MODE_O28_O29_MASK_SFT              (0x1 << 30)
#घोषणा STF_BYPASS_MODE_I2S4_SFT                      29
#घोषणा STF_BYPASS_MODE_I2S4_MASK                     0x1
#घोषणा STF_BYPASS_MODE_I2S4_MASK_SFT                 (0x1 << 29)
#घोषणा STF_BYPASS_MODE_I2S5_SFT                      28
#घोषणा STF_BYPASS_MODE_I2S5_MASK                     0x1
#घोषणा STF_BYPASS_MODE_I2S5_MASK_SFT                 (0x1 << 28)
#घोषणा STF_INPUT_EN_SEL_SFT                          13
#घोषणा STF_INPUT_EN_SEL_MASK                         0x1
#घोषणा STF_INPUT_EN_SEL_MASK_SFT                     (0x1 << 13)
#घोषणा STF_SOURCE_FROM_O19O20_SFT                    12
#घोषणा STF_SOURCE_FROM_O19O20_MASK                   0x1
#घोषणा STF_SOURCE_FROM_O19O20_MASK_SFT               (0x1 << 12)
#घोषणा SIDE_TONE_ON_SFT                              8
#घोषणा SIDE_TONE_ON_MASK                             0x1
#घोषणा SIDE_TONE_ON_MASK_SFT                         (0x1 << 8)
#घोषणा SIDE_TONE_HALF_TAP_NUM_SFT                    0
#घोषणा SIDE_TONE_HALF_TAP_NUM_MASK                   0x3f
#घोषणा SIDE_TONE_HALF_TAP_NUM_MASK_SFT               (0x3f << 0)

/* AFE_SIDETONE_GAIN */
#घोषणा POSITIVE_GAIN_SFT                             16
#घोषणा POSITIVE_GAIN_MASK                            0x7
#घोषणा POSITIVE_GAIN_MASK_SFT                        (0x7 << 16)
#घोषणा SIDE_TONE_GAIN_SFT                            0
#घोषणा SIDE_TONE_GAIN_MASK                           0xffff
#घोषणा SIDE_TONE_GAIN_MASK_SFT                       (0xffff << 0)

/* AFE_ADDA_DL_SDM_DCCOMP_CON */
#घोषणा AUD_DC_COMP_EN_SFT                            8
#घोषणा AUD_DC_COMP_EN_MASK                           0x1
#घोषणा AUD_DC_COMP_EN_MASK_SFT                       (0x1 << 8)
#घोषणा ATTGAIN_CTL_SFT                               0
#घोषणा ATTGAIN_CTL_MASK                              0x3f
#घोषणा ATTGAIN_CTL_MASK_SFT                          (0x3f << 0)

/* AFE_SINEGEN_CON0 */
#घोषणा DAC_EN_SFT                                    26
#घोषणा DAC_EN_MASK                                   0x1
#घोषणा DAC_EN_MASK_SFT                               (0x1 << 26)
#घोषणा MUTE_SW_CH2_SFT                               25
#घोषणा MUTE_SW_CH2_MASK                              0x1
#घोषणा MUTE_SW_CH2_MASK_SFT                          (0x1 << 25)
#घोषणा MUTE_SW_CH1_SFT                               24
#घोषणा MUTE_SW_CH1_MASK                              0x1
#घोषणा MUTE_SW_CH1_MASK_SFT                          (0x1 << 24)
#घोषणा SINE_MODE_CH2_SFT                             20
#घोषणा SINE_MODE_CH2_MASK                            0xf
#घोषणा SINE_MODE_CH2_MASK_SFT                        (0xf << 20)
#घोषणा AMP_DIV_CH2_SFT                               17
#घोषणा AMP_DIV_CH2_MASK                              0x7
#घोषणा AMP_DIV_CH2_MASK_SFT                          (0x7 << 17)
#घोषणा FREQ_DIV_CH2_SFT                              12
#घोषणा FREQ_DIV_CH2_MASK                             0x1f
#घोषणा FREQ_DIV_CH2_MASK_SFT                         (0x1f << 12)
#घोषणा SINE_MODE_CH1_SFT                             8
#घोषणा SINE_MODE_CH1_MASK                            0xf
#घोषणा SINE_MODE_CH1_MASK_SFT                        (0xf << 8)
#घोषणा AMP_DIV_CH1_SFT                               5
#घोषणा AMP_DIV_CH1_MASK                              0x7
#घोषणा AMP_DIV_CH1_MASK_SFT                          (0x7 << 5)
#घोषणा FREQ_DIV_CH1_SFT                              0
#घोषणा FREQ_DIV_CH1_MASK                             0x1f
#घोषणा FREQ_DIV_CH1_MASK_SFT                         (0x1f << 0)

/* AFE_SINEGEN_CON2 */
#घोषणा INNER_LOOP_BACK_MODE_SFT                      0
#घोषणा INNER_LOOP_BACK_MODE_MASK                     0x3f
#घोषणा INNER_LOOP_BACK_MODE_MASK_SFT                 (0x3f << 0)

/* AFE_MEMIF_MINLEN */
#घोषणा HDMI_MINLEN_SFT                               24
#घोषणा HDMI_MINLEN_MASK                              0xf
#घोषणा HDMI_MINLEN_MASK_SFT                          (0xf << 24)
#घोषणा DL3_MINLEN_SFT                                12
#घोषणा DL3_MINLEN_MASK                               0xf
#घोषणा DL3_MINLEN_MASK_SFT                           (0xf << 12)
#घोषणा DL2_MINLEN_SFT                                8
#घोषणा DL2_MINLEN_MASK                               0xf
#घोषणा DL2_MINLEN_MASK_SFT                           (0xf << 8)
#घोषणा DL1_DATA2_MINLEN_SFT                          4
#घोषणा DL1_DATA2_MINLEN_MASK                         0xf
#घोषणा DL1_DATA2_MINLEN_MASK_SFT                     (0xf << 4)
#घोषणा DL1_MINLEN_SFT                                0
#घोषणा DL1_MINLEN_MASK                               0xf
#घोषणा DL1_MINLEN_MASK_SFT                           (0xf << 0)

/* AFE_MEMIF_MAXLEN */
#घोषणा HDMI_MAXLEN_SFT                               24
#घोषणा HDMI_MAXLEN_MASK                              0xf
#घोषणा HDMI_MAXLEN_MASK_SFT                          (0xf << 24)
#घोषणा DL3_MAXLEN_SFT                                8
#घोषणा DL3_MAXLEN_MASK                               0xf
#घोषणा DL3_MAXLEN_MASK_SFT                           (0xf << 8)
#घोषणा DL2_MAXLEN_SFT                                4
#घोषणा DL2_MAXLEN_MASK                               0xf
#घोषणा DL2_MAXLEN_MASK_SFT                           (0xf << 4)
#घोषणा DL1_MAXLEN_SFT                                0
#घोषणा DL1_MAXLEN_MASK                               0x3
#घोषणा DL1_MAXLEN_MASK_SFT                           (0x3 << 0)

/* AFE_MEMIF_PBUF_SIZE */
#घोषणा VUL12_4CH_SFT                                 17
#घोषणा VUL12_4CH_MASK                                0x1
#घोषणा VUL12_4CH_MASK_SFT                            (0x1 << 17)
#घोषणा DL3_PBUF_SIZE_SFT                             10
#घोषणा DL3_PBUF_SIZE_MASK                            0x3
#घोषणा DL3_PBUF_SIZE_MASK_SFT                        (0x3 << 10)
#घोषणा HDMI_PBUF_SIZE_SFT                            4
#घोषणा HDMI_PBUF_SIZE_MASK                           0x3
#घोषणा HDMI_PBUF_SIZE_MASK_SFT                       (0x3 << 4)
#घोषणा DL2_PBUF_SIZE_SFT                             2
#घोषणा DL2_PBUF_SIZE_MASK                            0x3
#घोषणा DL2_PBUF_SIZE_MASK_SFT                        (0x3 << 2)
#घोषणा DL1_PBUF_SIZE_SFT                             0
#घोषणा DL1_PBUF_SIZE_MASK                            0x3
#घोषणा DL1_PBUF_SIZE_MASK_SFT                        (0x3 << 0)

/* AFE_HD_ENGEN_ENABLE */
#घोषणा AFE_24M_ON_SFT                                1
#घोषणा AFE_24M_ON_MASK                               0x1
#घोषणा AFE_24M_ON_MASK_SFT                           (0x1 << 1)
#घोषणा AFE_22M_ON_SFT                                0
#घोषणा AFE_22M_ON_MASK                               0x1
#घोषणा AFE_22M_ON_MASK_SFT                           (0x1 << 0)

/* AFE_IRQ_MCU_CON0 */
#घोषणा IRQ12_MCU_ON_SFT                              12
#घोषणा IRQ12_MCU_ON_MASK                             0x1
#घोषणा IRQ12_MCU_ON_MASK_SFT                         (0x1 << 12)
#घोषणा IRQ11_MCU_ON_SFT                              11
#घोषणा IRQ11_MCU_ON_MASK                             0x1
#घोषणा IRQ11_MCU_ON_MASK_SFT                         (0x1 << 11)
#घोषणा IRQ10_MCU_ON_SFT                              10
#घोषणा IRQ10_MCU_ON_MASK                             0x1
#घोषणा IRQ10_MCU_ON_MASK_SFT                         (0x1 << 10)
#घोषणा IRQ9_MCU_ON_SFT                               9
#घोषणा IRQ9_MCU_ON_MASK                              0x1
#घोषणा IRQ9_MCU_ON_MASK_SFT                          (0x1 << 9)
#घोषणा IRQ8_MCU_ON_SFT                               8
#घोषणा IRQ8_MCU_ON_MASK                              0x1
#घोषणा IRQ8_MCU_ON_MASK_SFT                          (0x1 << 8)
#घोषणा IRQ7_MCU_ON_SFT                               7
#घोषणा IRQ7_MCU_ON_MASK                              0x1
#घोषणा IRQ7_MCU_ON_MASK_SFT                          (0x1 << 7)
#घोषणा IRQ6_MCU_ON_SFT                               6
#घोषणा IRQ6_MCU_ON_MASK                              0x1
#घोषणा IRQ6_MCU_ON_MASK_SFT                          (0x1 << 6)
#घोषणा IRQ5_MCU_ON_SFT                               5
#घोषणा IRQ5_MCU_ON_MASK                              0x1
#घोषणा IRQ5_MCU_ON_MASK_SFT                          (0x1 << 5)
#घोषणा IRQ4_MCU_ON_SFT                               4
#घोषणा IRQ4_MCU_ON_MASK                              0x1
#घोषणा IRQ4_MCU_ON_MASK_SFT                          (0x1 << 4)
#घोषणा IRQ3_MCU_ON_SFT                               3
#घोषणा IRQ3_MCU_ON_MASK                              0x1
#घोषणा IRQ3_MCU_ON_MASK_SFT                          (0x1 << 3)
#घोषणा IRQ2_MCU_ON_SFT                               2
#घोषणा IRQ2_MCU_ON_MASK                              0x1
#घोषणा IRQ2_MCU_ON_MASK_SFT                          (0x1 << 2)
#घोषणा IRQ1_MCU_ON_SFT                               1
#घोषणा IRQ1_MCU_ON_MASK                              0x1
#घोषणा IRQ1_MCU_ON_MASK_SFT                          (0x1 << 1)
#घोषणा IRQ0_MCU_ON_SFT                               0
#घोषणा IRQ0_MCU_ON_MASK                              0x1
#घोषणा IRQ0_MCU_ON_MASK_SFT                          (0x1 << 0)

/* AFE_IRQ_MCU_CON1 */
#घोषणा IRQ7_MCU_MODE_SFT                             28
#घोषणा IRQ7_MCU_MODE_MASK                            0xf
#घोषणा IRQ7_MCU_MODE_MASK_SFT                        (0xf << 28)
#घोषणा IRQ6_MCU_MODE_SFT                             24
#घोषणा IRQ6_MCU_MODE_MASK                            0xf
#घोषणा IRQ6_MCU_MODE_MASK_SFT                        (0xf << 24)
#घोषणा IRQ5_MCU_MODE_SFT                             20
#घोषणा IRQ5_MCU_MODE_MASK                            0xf
#घोषणा IRQ5_MCU_MODE_MASK_SFT                        (0xf << 20)
#घोषणा IRQ4_MCU_MODE_SFT                             16
#घोषणा IRQ4_MCU_MODE_MASK                            0xf
#घोषणा IRQ4_MCU_MODE_MASK_SFT                        (0xf << 16)
#घोषणा IRQ3_MCU_MODE_SFT                             12
#घोषणा IRQ3_MCU_MODE_MASK                            0xf
#घोषणा IRQ3_MCU_MODE_MASK_SFT                        (0xf << 12)
#घोषणा IRQ2_MCU_MODE_SFT                             8
#घोषणा IRQ2_MCU_MODE_MASK                            0xf
#घोषणा IRQ2_MCU_MODE_MASK_SFT                        (0xf << 8)
#घोषणा IRQ1_MCU_MODE_SFT                             4
#घोषणा IRQ1_MCU_MODE_MASK                            0xf
#घोषणा IRQ1_MCU_MODE_MASK_SFT                        (0xf << 4)
#घोषणा IRQ0_MCU_MODE_SFT                             0
#घोषणा IRQ0_MCU_MODE_MASK                            0xf
#घोषणा IRQ0_MCU_MODE_MASK_SFT                        (0xf << 0)

/* AFE_IRQ_MCU_CON2 */
#घोषणा IRQ12_MCU_MODE_SFT                            4
#घोषणा IRQ12_MCU_MODE_MASK                           0xf
#घोषणा IRQ12_MCU_MODE_MASK_SFT                       (0xf << 4)
#घोषणा IRQ11_MCU_MODE_SFT                            0
#घोषणा IRQ11_MCU_MODE_MASK                           0xf
#घोषणा IRQ11_MCU_MODE_MASK_SFT                       (0xf << 0)

/* AFE_IRQ_MCU_CLR */
#घोषणा IRQ12_MCU_MISS_CNT_CLR_SFT                    28
#घोषणा IRQ12_MCU_MISS_CNT_CLR_MASK                   0x1
#घोषणा IRQ12_MCU_MISS_CNT_CLR_MASK_SFT               (0x1 << 28)
#घोषणा IRQ11_MCU_MISS_CNT_CLR_SFT                    27
#घोषणा IRQ11_MCU_MISS_CNT_CLR_MASK                   0x1
#घोषणा IRQ11_MCU_MISS_CNT_CLR_MASK_SFT               (0x1 << 27)
#घोषणा IRQ10_MCU_MISS_CLR_SFT                        26
#घोषणा IRQ10_MCU_MISS_CLR_MASK                       0x1
#घोषणा IRQ10_MCU_MISS_CLR_MASK_SFT                   (0x1 << 26)
#घोषणा IRQ9_MCU_MISS_CLR_SFT                         25
#घोषणा IRQ9_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ9_MCU_MISS_CLR_MASK_SFT                    (0x1 << 25)
#घोषणा IRQ8_MCU_MISS_CLR_SFT                         24
#घोषणा IRQ8_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ8_MCU_MISS_CLR_MASK_SFT                    (0x1 << 24)
#घोषणा IRQ7_MCU_MISS_CLR_SFT                         23
#घोषणा IRQ7_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ7_MCU_MISS_CLR_MASK_SFT                    (0x1 << 23)
#घोषणा IRQ6_MCU_MISS_CLR_SFT                         22
#घोषणा IRQ6_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ6_MCU_MISS_CLR_MASK_SFT                    (0x1 << 22)
#घोषणा IRQ5_MCU_MISS_CLR_SFT                         21
#घोषणा IRQ5_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ5_MCU_MISS_CLR_MASK_SFT                    (0x1 << 21)
#घोषणा IRQ4_MCU_MISS_CLR_SFT                         20
#घोषणा IRQ4_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ4_MCU_MISS_CLR_MASK_SFT                    (0x1 << 20)
#घोषणा IRQ3_MCU_MISS_CLR_SFT                         19
#घोषणा IRQ3_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ3_MCU_MISS_CLR_MASK_SFT                    (0x1 << 19)
#घोषणा IRQ2_MCU_MISS_CLR_SFT                         18
#घोषणा IRQ2_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ2_MCU_MISS_CLR_MASK_SFT                    (0x1 << 18)
#घोषणा IRQ1_MCU_MISS_CLR_SFT                         17
#घोषणा IRQ1_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ1_MCU_MISS_CLR_MASK_SFT                    (0x1 << 17)
#घोषणा IRQ0_MCU_MISS_CLR_SFT                         16
#घोषणा IRQ0_MCU_MISS_CLR_MASK                        0x1
#घोषणा IRQ0_MCU_MISS_CLR_MASK_SFT                    (0x1 << 16)
#घोषणा IRQ12_MCU_CLR_SFT                             12
#घोषणा IRQ12_MCU_CLR_MASK                            0x1
#घोषणा IRQ12_MCU_CLR_MASK_SFT                        (0x1 << 12)
#घोषणा IRQ11_MCU_CLR_SFT                             11
#घोषणा IRQ11_MCU_CLR_MASK                            0x1
#घोषणा IRQ11_MCU_CLR_MASK_SFT                        (0x1 << 11)
#घोषणा IRQ10_MCU_CLR_SFT                             10
#घोषणा IRQ10_MCU_CLR_MASK                            0x1
#घोषणा IRQ10_MCU_CLR_MASK_SFT                        (0x1 << 10)
#घोषणा IRQ9_MCU_CLR_SFT                              9
#घोषणा IRQ9_MCU_CLR_MASK                             0x1
#घोषणा IRQ9_MCU_CLR_MASK_SFT                         (0x1 << 9)
#घोषणा IRQ8_MCU_CLR_SFT                              8
#घोषणा IRQ8_MCU_CLR_MASK                             0x1
#घोषणा IRQ8_MCU_CLR_MASK_SFT                         (0x1 << 8)
#घोषणा IRQ7_MCU_CLR_SFT                              7
#घोषणा IRQ7_MCU_CLR_MASK                             0x1
#घोषणा IRQ7_MCU_CLR_MASK_SFT                         (0x1 << 7)
#घोषणा IRQ6_MCU_CLR_SFT                              6
#घोषणा IRQ6_MCU_CLR_MASK                             0x1
#घोषणा IRQ6_MCU_CLR_MASK_SFT                         (0x1 << 6)
#घोषणा IRQ5_MCU_CLR_SFT                              5
#घोषणा IRQ5_MCU_CLR_MASK                             0x1
#घोषणा IRQ5_MCU_CLR_MASK_SFT                         (0x1 << 5)
#घोषणा IRQ4_MCU_CLR_SFT                              4
#घोषणा IRQ4_MCU_CLR_MASK                             0x1
#घोषणा IRQ4_MCU_CLR_MASK_SFT                         (0x1 << 4)
#घोषणा IRQ3_MCU_CLR_SFT                              3
#घोषणा IRQ3_MCU_CLR_MASK                             0x1
#घोषणा IRQ3_MCU_CLR_MASK_SFT                         (0x1 << 3)
#घोषणा IRQ2_MCU_CLR_SFT                              2
#घोषणा IRQ2_MCU_CLR_MASK                             0x1
#घोषणा IRQ2_MCU_CLR_MASK_SFT                         (0x1 << 2)
#घोषणा IRQ1_MCU_CLR_SFT                              1
#घोषणा IRQ1_MCU_CLR_MASK                             0x1
#घोषणा IRQ1_MCU_CLR_MASK_SFT                         (0x1 << 1)
#घोषणा IRQ0_MCU_CLR_SFT                              0
#घोषणा IRQ0_MCU_CLR_MASK                             0x1
#घोषणा IRQ0_MCU_CLR_MASK_SFT                         (0x1 << 0)

/* AFE_MEMIF_MSB */
#घोषणा CPU_COMPACT_MODE_SFT                          29
#घोषणा CPU_COMPACT_MODE_MASK                         0x1
#घोषणा CPU_COMPACT_MODE_MASK_SFT                     (0x1 << 29)
#घोषणा CPU_HD_ALIGN_SFT                              28
#घोषणा CPU_HD_ALIGN_MASK                             0x1
#घोषणा CPU_HD_ALIGN_MASK_SFT                         (0x1 << 28)
#घोषणा AWB2_AXI_WR_SIGN_SFT                          24
#घोषणा AWB2_AXI_WR_SIGN_MASK                         0x1
#घोषणा AWB2_AXI_WR_SIGN_MASK_SFT                     (0x1 << 24)
#घोषणा VUL2_AXI_WR_SIGN_SFT                          22
#घोषणा VUL2_AXI_WR_SIGN_MASK                         0x1
#घोषणा VUL2_AXI_WR_SIGN_MASK_SFT                     (0x1 << 22)
#घोषणा VUL12_AXI_WR_SIGN_SFT                         21
#घोषणा VUL12_AXI_WR_SIGN_MASK                        0x1
#घोषणा VUL12_AXI_WR_SIGN_MASK_SFT                    (0x1 << 21)
#घोषणा VUL_AXI_WR_SIGN_SFT                           20
#घोषणा VUL_AXI_WR_SIGN_MASK                          0x1
#घोषणा VUL_AXI_WR_SIGN_MASK_SFT                      (0x1 << 20)
#घोषणा MOD_DAI_AXI_WR_SIGN_SFT                       18
#घोषणा MOD_DAI_AXI_WR_SIGN_MASK                      0x1
#घोषणा MOD_DAI_AXI_WR_SIGN_MASK_SFT                  (0x1 << 18)
#घोषणा AWB_MSTR_SIGN_SFT                             17
#घोषणा AWB_MSTR_SIGN_MASK                            0x1
#घोषणा AWB_MSTR_SIGN_MASK_SFT                        (0x1 << 17)
#घोषणा SYSRAM_SIGN_SFT                               16
#घोषणा SYSRAM_SIGN_MASK                              0x1
#घोषणा SYSRAM_SIGN_MASK_SFT                          (0x1 << 16)

/* AFE_HDMI_CONN0 */
#घोषणा HDMI_O_7_SFT                                  21
#घोषणा HDMI_O_7_MASK                                 0x7
#घोषणा HDMI_O_7_MASK_SFT                             (0x7 << 21)
#घोषणा HDMI_O_6_SFT                                  18
#घोषणा HDMI_O_6_MASK                                 0x7
#घोषणा HDMI_O_6_MASK_SFT                             (0x7 << 18)
#घोषणा HDMI_O_5_SFT                                  15
#घोषणा HDMI_O_5_MASK                                 0x7
#घोषणा HDMI_O_5_MASK_SFT                             (0x7 << 15)
#घोषणा HDMI_O_4_SFT                                  12
#घोषणा HDMI_O_4_MASK                                 0x7
#घोषणा HDMI_O_4_MASK_SFT                             (0x7 << 12)
#घोषणा HDMI_O_3_SFT                                  9
#घोषणा HDMI_O_3_MASK                                 0x7
#घोषणा HDMI_O_3_MASK_SFT                             (0x7 << 9)
#घोषणा HDMI_O_2_SFT                                  6
#घोषणा HDMI_O_2_MASK                                 0x7
#घोषणा HDMI_O_2_MASK_SFT                             (0x7 << 6)
#घोषणा HDMI_O_1_SFT                                  3
#घोषणा HDMI_O_1_MASK                                 0x7
#घोषणा HDMI_O_1_MASK_SFT                             (0x7 << 3)
#घोषणा HDMI_O_0_SFT                                  0
#घोषणा HDMI_O_0_MASK                                 0x7
#घोषणा HDMI_O_0_MASK_SFT                             (0x7 << 0)

/* AFE_TDM_CON1 */
#घोषणा TDM_EN_SFT                                    0
#घोषणा TDM_EN_MASK                                   0x1
#घोषणा TDM_EN_MASK_SFT                               (0x1 << 0)
#घोषणा LRCK_INVERSE_SFT                              2
#घोषणा LRCK_INVERSE_MASK                             0x1
#घोषणा LRCK_INVERSE_MASK_SFT                         (0x1 << 2)
#घोषणा DELAY_DATA_SFT                                3
#घोषणा DELAY_DATA_MASK                               0x1
#घोषणा DELAY_DATA_MASK_SFT                           (0x1 << 3)
#घोषणा LEFT_ALIGN_SFT                                4
#घोषणा LEFT_ALIGN_MASK                               0x1
#घोषणा LEFT_ALIGN_MASK_SFT                           (0x1 << 4)
#घोषणा WLEN_SFT                                      8
#घोषणा WLEN_MASK                                     0x3
#घोषणा WLEN_MASK_SFT                                 (0x3 << 8)
#घोषणा CHANNEL_NUM_SFT                               10
#घोषणा CHANNEL_NUM_MASK                              0x3
#घोषणा CHANNEL_NUM_MASK_SFT                          (0x3 << 10)
#घोषणा CHANNEL_BCK_CYCLES_SFT                        12
#घोषणा CHANNEL_BCK_CYCLES_MASK                       0x3
#घोषणा CHANNEL_BCK_CYCLES_MASK_SFT                   (0x3 << 12)
#घोषणा DAC_BIT_NUM_SFT                               16
#घोषणा DAC_BIT_NUM_MASK                              0x1f
#घोषणा DAC_BIT_NUM_MASK_SFT                          (0x1f << 16)
#घोषणा LRCK_TDM_WIDTH_SFT                            24
#घोषणा LRCK_TDM_WIDTH_MASK                           0xff
#घोषणा LRCK_TDM_WIDTH_MASK_SFT                       (0xff << 24)

/* AFE_TDM_CON2 */
#घोषणा ST_CH_PAIR_SOUT0_SFT                          0
#घोषणा ST_CH_PAIR_SOUT0_MASK                         0x7
#घोषणा ST_CH_PAIR_SOUT0_MASK_SFT                     (0x7 << 0)
#घोषणा ST_CH_PAIR_SOUT1_SFT                          4
#घोषणा ST_CH_PAIR_SOUT1_MASK                         0x7
#घोषणा ST_CH_PAIR_SOUT1_MASK_SFT                     (0x7 << 4)
#घोषणा ST_CH_PAIR_SOUT2_SFT                          8
#घोषणा ST_CH_PAIR_SOUT2_MASK                         0x7
#घोषणा ST_CH_PAIR_SOUT2_MASK_SFT                     (0x7 << 8)
#घोषणा ST_CH_PAIR_SOUT3_SFT                          12
#घोषणा ST_CH_PAIR_SOUT3_MASK                         0x7
#घोषणा ST_CH_PAIR_SOUT3_MASK_SFT                     (0x7 << 12)
#घोषणा TDM_FIX_VALUE_SEL_SFT                         16
#घोषणा TDM_FIX_VALUE_SEL_MASK                        0x1
#घोषणा TDM_FIX_VALUE_SEL_MASK_SFT                    (0x1 << 16)
#घोषणा TDM_I2S_LOOPBACK_SFT                          20
#घोषणा TDM_I2S_LOOPBACK_MASK                         0x1
#घोषणा TDM_I2S_LOOPBACK_MASK_SFT                     (0x1 << 20)
#घोषणा TDM_I2S_LOOPBACK_CH_SFT                       21
#घोषणा TDM_I2S_LOOPBACK_CH_MASK                      0x3
#घोषणा TDM_I2S_LOOPBACK_CH_MASK_SFT                  (0x3 << 21)
#घोषणा TDM_FIX_VALUE_SFT                             24
#घोषणा TDM_FIX_VALUE_MASK                            0xff
#घोषणा TDM_FIX_VALUE_MASK_SFT                        (0xff << 24)

/* AFE_HDMI_OUT_CON0 */
#घोषणा AFE_HDMI_OUT_ON_RETM_SFT                      8
#घोषणा AFE_HDMI_OUT_ON_RETM_MASK                     0x1
#घोषणा AFE_HDMI_OUT_ON_RETM_MASK_SFT                 (0x1 << 8)
#घोषणा AFE_HDMI_OUT_CH_NUM_SFT                       4
#घोषणा AFE_HDMI_OUT_CH_NUM_MASK                      0xf
#घोषणा AFE_HDMI_OUT_CH_NUM_MASK_SFT                  (0xf << 4)
#घोषणा AFE_HDMI_OUT_BIT_WIDTH_SFT                    1
#घोषणा AFE_HDMI_OUT_BIT_WIDTH_MASK                   0x1
#घोषणा AFE_HDMI_OUT_BIT_WIDTH_MASK_SFT               (0x1 << 1)
#घोषणा AFE_HDMI_OUT_ON_SFT                           0
#घोषणा AFE_HDMI_OUT_ON_MASK                          0x1
#घोषणा AFE_HDMI_OUT_ON_MASK_SFT                      (0x1 << 0)
#पूर्ण_अगर
