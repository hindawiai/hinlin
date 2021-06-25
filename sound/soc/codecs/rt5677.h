<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt5677.h  --  RT5677 ALSA SoC audio driver
 *
 * Copyright 2013 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#अगर_अघोषित __RT5677_H__
#घोषणा __RT5677_H__

#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/consumer.h>

/* Info */
#घोषणा RT5677_RESET				0x00
#घोषणा RT5677_VENDOR_ID			0xfd
#घोषणा RT5677_VENDOR_ID1			0xfe
#घोषणा RT5677_VENDOR_ID2			0xff
/*  I/O - Output */
#घोषणा RT5677_LOUT1				0x01
/* I/O - Input */
#घोषणा RT5677_IN1				0x03
#घोषणा RT5677_MICBIAS				0x04
/* I/O - SLIMBus */
#घोषणा RT5677_SLIMBUS_PARAM			0x07
#घोषणा RT5677_SLIMBUS_RX			0x08
#घोषणा RT5677_SLIMBUS_CTRL			0x09
/* I/O */
#घोषणा RT5677_SIDETONE_CTRL			0x13
/* I/O - ADC/DAC */
#घोषणा RT5677_ANA_DAC1_2_3_SRC			0x15
#घोषणा RT5677_IF_DSP_DAC3_4_MIXER		0x16
#घोषणा RT5677_DAC4_DIG_VOL			0x17
#घोषणा RT5677_DAC3_DIG_VOL			0x18
#घोषणा RT5677_DAC1_DIG_VOL			0x19
#घोषणा RT5677_DAC2_DIG_VOL			0x1a
#घोषणा RT5677_IF_DSP_DAC2_MIXER		0x1b
#घोषणा RT5677_STO1_ADC_DIG_VOL			0x1c
#घोषणा RT5677_MONO_ADC_DIG_VOL			0x1d
#घोषणा RT5677_STO1_2_ADC_BST			0x1e
#घोषणा RT5677_STO2_ADC_DIG_VOL			0x1f
/* Mixer - D-D */
#घोषणा RT5677_ADC_BST_CTRL2			0x20
#घोषणा RT5677_STO3_4_ADC_BST			0x21
#घोषणा RT5677_STO3_ADC_DIG_VOL			0x22
#घोषणा RT5677_STO4_ADC_DIG_VOL			0x23
#घोषणा RT5677_STO4_ADC_MIXER			0x24
#घोषणा RT5677_STO3_ADC_MIXER			0x25
#घोषणा RT5677_STO2_ADC_MIXER			0x26
#घोषणा RT5677_STO1_ADC_MIXER			0x27
#घोषणा RT5677_MONO_ADC_MIXER			0x28
#घोषणा RT5677_ADC_IF_DSP_DAC1_MIXER		0x29
#घोषणा RT5677_STO1_DAC_MIXER			0x2a
#घोषणा RT5677_MONO_DAC_MIXER			0x2b
#घोषणा RT5677_DD1_MIXER			0x2c
#घोषणा RT5677_DD2_MIXER			0x2d
#घोषणा RT5677_IF3_DATA				0x2f
#घोषणा RT5677_IF4_DATA				0x30
/* Mixer - PDM */
#घोषणा RT5677_PDM_OUT_CTRL			0x31
#घोषणा RT5677_PDM_DATA_CTRL1			0x32
#घोषणा RT5677_PDM_DATA_CTRL2			0x33
#घोषणा RT5677_PDM1_DATA_CTRL2			0x34
#घोषणा RT5677_PDM1_DATA_CTRL3			0x35
#घोषणा RT5677_PDM1_DATA_CTRL4			0x36
#घोषणा RT5677_PDM2_DATA_CTRL2			0x37
#घोषणा RT5677_PDM2_DATA_CTRL3			0x38
#घोषणा RT5677_PDM2_DATA_CTRL4			0x39
/* TDM */
#घोषणा RT5677_TDM1_CTRL1			0x3b
#घोषणा RT5677_TDM1_CTRL2			0x3c
#घोषणा RT5677_TDM1_CTRL3			0x3d
#घोषणा RT5677_TDM1_CTRL4			0x3e
#घोषणा RT5677_TDM1_CTRL5			0x3f
#घोषणा RT5677_TDM2_CTRL1			0x40
#घोषणा RT5677_TDM2_CTRL2			0x41
#घोषणा RT5677_TDM2_CTRL3			0x42
#घोषणा RT5677_TDM2_CTRL4			0x43
#घोषणा RT5677_TDM2_CTRL5			0x44
/* I2C_MASTER_CTRL */
#घोषणा RT5677_I2C_MASTER_CTRL1			0x47
#घोषणा RT5677_I2C_MASTER_CTRL2			0x48
#घोषणा RT5677_I2C_MASTER_CTRL3			0x49
#घोषणा RT5677_I2C_MASTER_CTRL4			0x4a
#घोषणा RT5677_I2C_MASTER_CTRL5			0x4b
#घोषणा RT5677_I2C_MASTER_CTRL6			0x4c
#घोषणा RT5677_I2C_MASTER_CTRL7			0x4d
#घोषणा RT5677_I2C_MASTER_CTRL8			0x4e
/* DMIC */
#घोषणा RT5677_DMIC_CTRL1			0x50
#घोषणा RT5677_DMIC_CTRL2			0x51
/* Haptic Generator */
#घोषणा RT5677_HAP_GENE_CTRL1			0x56
#घोषणा RT5677_HAP_GENE_CTRL2			0x57
#घोषणा RT5677_HAP_GENE_CTRL3			0x58
#घोषणा RT5677_HAP_GENE_CTRL4			0x59
#घोषणा RT5677_HAP_GENE_CTRL5			0x5a
#घोषणा RT5677_HAP_GENE_CTRL6			0x5b
#घोषणा RT5677_HAP_GENE_CTRL7			0x5c
#घोषणा RT5677_HAP_GENE_CTRL8			0x5d
#घोषणा RT5677_HAP_GENE_CTRL9			0x5e
#घोषणा RT5677_HAP_GENE_CTRL10			0x5f
/* Power */
#घोषणा RT5677_PWR_DIG1				0x61
#घोषणा RT5677_PWR_DIG2				0x62
#घोषणा RT5677_PWR_ANLG1			0x63
#घोषणा RT5677_PWR_ANLG2			0x64
#घोषणा RT5677_PWR_DSP1				0x65
#घोषणा RT5677_PWR_DSP_ST			0x66
#घोषणा RT5677_PWR_DSP2				0x67
#घोषणा RT5677_ADC_DAC_HPF_CTRL1		0x68
/* Private Register Control */
#घोषणा RT5677_PRIV_INDEX			0x6a
#घोषणा RT5677_PRIV_DATA			0x6c
/* Format - ADC/DAC */
#घोषणा RT5677_I2S4_SDP				0x6f
#घोषणा RT5677_I2S1_SDP				0x70
#घोषणा RT5677_I2S2_SDP				0x71
#घोषणा RT5677_I2S3_SDP				0x72
#घोषणा RT5677_CLK_TREE_CTRL1			0x73
#घोषणा RT5677_CLK_TREE_CTRL2			0x74
#घोषणा RT5677_CLK_TREE_CTRL3			0x75
/* Function - Analog */
#घोषणा RT5677_PLL1_CTRL1			0x7a
#घोषणा RT5677_PLL1_CTRL2			0x7b
#घोषणा RT5677_PLL2_CTRL1			0x7c
#घोषणा RT5677_PLL2_CTRL2			0x7d
#घोषणा RT5677_GLB_CLK1				0x80
#घोषणा RT5677_GLB_CLK2				0x81
#घोषणा RT5677_ASRC_1				0x83
#घोषणा RT5677_ASRC_2				0x84
#घोषणा RT5677_ASRC_3				0x85
#घोषणा RT5677_ASRC_4				0x86
#घोषणा RT5677_ASRC_5				0x87
#घोषणा RT5677_ASRC_6				0x88
#घोषणा RT5677_ASRC_7				0x89
#घोषणा RT5677_ASRC_8				0x8a
#घोषणा RT5677_ASRC_9				0x8b
#घोषणा RT5677_ASRC_10				0x8c
#घोषणा RT5677_ASRC_11				0x8d
#घोषणा RT5677_ASRC_12				0x8e
#घोषणा RT5677_ASRC_13				0x8f
#घोषणा RT5677_ASRC_14				0x90
#घोषणा RT5677_ASRC_15				0x91
#घोषणा RT5677_ASRC_16				0x92
#घोषणा RT5677_ASRC_17				0x93
#घोषणा RT5677_ASRC_18				0x94
#घोषणा RT5677_ASRC_19				0x95
#घोषणा RT5677_ASRC_20				0x97
#घोषणा RT5677_ASRC_21				0x98
#घोषणा RT5677_ASRC_22				0x99
#घोषणा RT5677_ASRC_23				0x9a
#घोषणा RT5677_VAD_CTRL1			0x9c
#घोषणा RT5677_VAD_CTRL2			0x9d
#घोषणा RT5677_VAD_CTRL3			0x9e
#घोषणा RT5677_VAD_CTRL4			0x9f
#घोषणा RT5677_VAD_CTRL5			0xa0
/* Function - Digital */
#घोषणा RT5677_DSP_INB_CTRL1			0xa3
#घोषणा RT5677_DSP_INB_CTRL2			0xa4
#घोषणा RT5677_DSP_IN_OUTB_CTRL			0xa5
#घोषणा RT5677_DSP_OUTB0_1_DIG_VOL		0xa6
#घोषणा RT5677_DSP_OUTB2_3_DIG_VOL		0xa7
#घोषणा RT5677_DSP_OUTB4_5_DIG_VOL		0xa8
#घोषणा RT5677_DSP_OUTB6_7_DIG_VOL		0xa9
#घोषणा RT5677_ADC_EQ_CTRL1			0xae
#घोषणा RT5677_ADC_EQ_CTRL2			0xaf
#घोषणा RT5677_EQ_CTRL1				0xb0
#घोषणा RT5677_EQ_CTRL2				0xb1
#घोषणा RT5677_EQ_CTRL3				0xb2
#घोषणा RT5677_SOFT_VOL_ZERO_CROSS1		0xb3
#घोषणा RT5677_JD_CTRL1				0xb5
#घोषणा RT5677_JD_CTRL2				0xb6
#घोषणा RT5677_JD_CTRL3				0xb8
#घोषणा RT5677_IRQ_CTRL1			0xbd
#घोषणा RT5677_IRQ_CTRL2			0xbe
#घोषणा RT5677_GPIO_ST				0xbf
#घोषणा RT5677_GPIO_CTRL1			0xc0
#घोषणा RT5677_GPIO_CTRL2			0xc1
#घोषणा RT5677_GPIO_CTRL3			0xc2
#घोषणा RT5677_STO1_ADC_HI_FILTER1		0xc5
#घोषणा RT5677_STO1_ADC_HI_FILTER2		0xc6
#घोषणा RT5677_MONO_ADC_HI_FILTER1		0xc7
#घोषणा RT5677_MONO_ADC_HI_FILTER2		0xc8
#घोषणा RT5677_STO2_ADC_HI_FILTER1		0xc9
#घोषणा RT5677_STO2_ADC_HI_FILTER2		0xca
#घोषणा RT5677_STO3_ADC_HI_FILTER1		0xcb
#घोषणा RT5677_STO3_ADC_HI_FILTER2		0xcc
#घोषणा RT5677_STO4_ADC_HI_FILTER1		0xcd
#घोषणा RT5677_STO4_ADC_HI_FILTER2		0xce
#घोषणा RT5677_MB_DRC_CTRL1			0xd0
#घोषणा RT5677_DRC1_CTRL1			0xd2
#घोषणा RT5677_DRC1_CTRL2			0xd3
#घोषणा RT5677_DRC1_CTRL3			0xd4
#घोषणा RT5677_DRC1_CTRL4			0xd5
#घोषणा RT5677_DRC1_CTRL5			0xd6
#घोषणा RT5677_DRC1_CTRL6			0xd7
#घोषणा RT5677_DRC2_CTRL1			0xd8
#घोषणा RT5677_DRC2_CTRL2			0xd9
#घोषणा RT5677_DRC2_CTRL3			0xda
#घोषणा RT5677_DRC2_CTRL4			0xdb
#घोषणा RT5677_DRC2_CTRL5			0xdc
#घोषणा RT5677_DRC2_CTRL6			0xdd
#घोषणा RT5677_DRC1_HL_CTRL1			0xde
#घोषणा RT5677_DRC1_HL_CTRL2			0xdf
#घोषणा RT5677_DRC2_HL_CTRL1			0xe0
#घोषणा RT5677_DRC2_HL_CTRL2			0xe1
#घोषणा RT5677_DSP_INB1_SRC_CTRL1		0xe3
#घोषणा RT5677_DSP_INB1_SRC_CTRL2		0xe4
#घोषणा RT5677_DSP_INB1_SRC_CTRL3		0xe5
#घोषणा RT5677_DSP_INB1_SRC_CTRL4		0xe6
#घोषणा RT5677_DSP_INB2_SRC_CTRL1		0xe7
#घोषणा RT5677_DSP_INB2_SRC_CTRL2		0xe8
#घोषणा RT5677_DSP_INB2_SRC_CTRL3		0xe9
#घोषणा RT5677_DSP_INB2_SRC_CTRL4		0xea
#घोषणा RT5677_DSP_INB3_SRC_CTRL1		0xeb
#घोषणा RT5677_DSP_INB3_SRC_CTRL2		0xec
#घोषणा RT5677_DSP_INB3_SRC_CTRL3		0xed
#घोषणा RT5677_DSP_INB3_SRC_CTRL4		0xee
#घोषणा RT5677_DSP_OUTB1_SRC_CTRL1		0xef
#घोषणा RT5677_DSP_OUTB1_SRC_CTRL2		0xf0
#घोषणा RT5677_DSP_OUTB1_SRC_CTRL3		0xf1
#घोषणा RT5677_DSP_OUTB1_SRC_CTRL4		0xf2
#घोषणा RT5677_DSP_OUTB2_SRC_CTRL1		0xf3
#घोषणा RT5677_DSP_OUTB2_SRC_CTRL2		0xf4
#घोषणा RT5677_DSP_OUTB2_SRC_CTRL3		0xf5
#घोषणा RT5677_DSP_OUTB2_SRC_CTRL4		0xf6

/* Virtual DSP Mixer Control */
#घोषणा RT5677_DSP_OUTB_0123_MIXER_CTRL		0xf7
#घोषणा RT5677_DSP_OUTB_45_MIXER_CTRL		0xf8
#घोषणा RT5677_DSP_OUTB_67_MIXER_CTRL		0xf9

/* General Control */
#घोषणा RT5677_DIG_MISC				0xfa
#घोषणा RT5677_GEN_CTRL1			0xfb
#घोषणा RT5677_GEN_CTRL2			0xfc

/* DSP Mode I2C Control*/
#घोषणा RT5677_DSP_I2C_OP_CODE			0x00
#घोषणा RT5677_DSP_I2C_ADDR_LSB			0x01
#घोषणा RT5677_DSP_I2C_ADDR_MSB			0x02
#घोषणा RT5677_DSP_I2C_DATA_LSB			0x03
#घोषणा RT5677_DSP_I2C_DATA_MSB			0x04

/* Index of Codec Private Register definition */
#घोषणा RT5677_PR_DRC1_CTRL_1			0x01
#घोषणा RT5677_PR_DRC1_CTRL_2			0x02
#घोषणा RT5677_PR_DRC1_CTRL_3			0x03
#घोषणा RT5677_PR_DRC1_CTRL_4			0x04
#घोषणा RT5677_PR_DRC1_CTRL_5			0x05
#घोषणा RT5677_PR_DRC1_CTRL_6			0x06
#घोषणा RT5677_PR_DRC1_CTRL_7			0x07
#घोषणा RT5677_PR_DRC2_CTRL_1			0x08
#घोषणा RT5677_PR_DRC2_CTRL_2			0x09
#घोषणा RT5677_PR_DRC2_CTRL_3			0x0a
#घोषणा RT5677_PR_DRC2_CTRL_4			0x0b
#घोषणा RT5677_PR_DRC2_CTRL_5			0x0c
#घोषणा RT5677_PR_DRC2_CTRL_6			0x0d
#घोषणा RT5677_PR_DRC2_CTRL_7			0x0e
#घोषणा RT5677_BIAS_CUR1			0x10
#घोषणा RT5677_BIAS_CUR2			0x12
#घोषणा RT5677_BIAS_CUR3			0x13
#घोषणा RT5677_BIAS_CUR4			0x14
#घोषणा RT5677_BIAS_CUR5			0x15
#घोषणा RT5677_VREF_LOUT_CTRL			0x17
#घोषणा RT5677_DIG_VOL_CTRL1			0x1a
#घोषणा RT5677_DIG_VOL_CTRL2			0x1b
#घोषणा RT5677_ANA_ADC_GAIN_CTRL		0x1e
#घोषणा RT5677_VAD_SRAM_TEST1			0x20
#घोषणा RT5677_VAD_SRAM_TEST2			0x21
#घोषणा RT5677_VAD_SRAM_TEST3			0x22
#घोषणा RT5677_VAD_SRAM_TEST4			0x23
#घोषणा RT5677_PAD_DRV_CTRL			0x26
#घोषणा RT5677_DIG_IN_PIN_ST_CTRL1		0x29
#घोषणा RT5677_DIG_IN_PIN_ST_CTRL2		0x2a
#घोषणा RT5677_DIG_IN_PIN_ST_CTRL3		0x2b
#घोषणा RT5677_PLL1_INT				0x38
#घोषणा RT5677_PLL2_INT				0x39
#घोषणा RT5677_TEST_CTRL1			0x3a
#घोषणा RT5677_TEST_CTRL2			0x3b
#घोषणा RT5677_TEST_CTRL3			0x3c
#घोषणा RT5677_CHOP_DAC_ADC			0x3d
#घोषणा RT5677_SOFT_DEPOP_DAC_CLK_CTRL		0x3e
#घोषणा RT5677_CROSS_OVER_FILTER1		0x90
#घोषणा RT5677_CROSS_OVER_FILTER2		0x91
#घोषणा RT5677_CROSS_OVER_FILTER3		0x92
#घोषणा RT5677_CROSS_OVER_FILTER4		0x93
#घोषणा RT5677_CROSS_OVER_FILTER5		0x94
#घोषणा RT5677_CROSS_OVER_FILTER6		0x95
#घोषणा RT5677_CROSS_OVER_FILTER7		0x96
#घोषणा RT5677_CROSS_OVER_FILTER8		0x97
#घोषणा RT5677_CROSS_OVER_FILTER9		0x98
#घोषणा RT5677_CROSS_OVER_FILTER10		0x99

/* global definition */
#घोषणा RT5677_L_MUTE				(0x1 << 15)
#घोषणा RT5677_L_MUTE_SFT			15
#घोषणा RT5677_VOL_L_MUTE			(0x1 << 14)
#घोषणा RT5677_VOL_L_SFT			14
#घोषणा RT5677_R_MUTE				(0x1 << 7)
#घोषणा RT5677_R_MUTE_SFT			7
#घोषणा RT5677_VOL_R_MUTE			(0x1 << 6)
#घोषणा RT5677_VOL_R_SFT			6
#घोषणा RT5677_L_VOL_MASK			(0x7f << 9)
#घोषणा RT5677_L_VOL_SFT			9
#घोषणा RT5677_R_VOL_MASK			(0x7f << 1)
#घोषणा RT5677_R_VOL_SFT			1

/* LOUT1 Control (0x01) */
#घोषणा RT5677_LOUT1_L_MUTE			(0x1 << 15)
#घोषणा RT5677_LOUT1_L_MUTE_SFT			(15)
#घोषणा RT5677_LOUT1_L_DF			(0x1 << 14)
#घोषणा RT5677_LOUT1_L_DF_SFT			(14)
#घोषणा RT5677_LOUT2_L_MUTE			(0x1 << 13)
#घोषणा RT5677_LOUT2_L_MUTE_SFT			(13)
#घोषणा RT5677_LOUT2_L_DF			(0x1 << 12)
#घोषणा RT5677_LOUT2_L_DF_SFT			(12)
#घोषणा RT5677_LOUT3_L_MUTE			(0x1 << 11)
#घोषणा RT5677_LOUT3_L_MUTE_SFT			(11)
#घोषणा RT5677_LOUT3_L_DF			(0x1 << 10)
#घोषणा RT5677_LOUT3_L_DF_SFT			(10)
#घोषणा RT5677_LOUT1_ENH_DRV			(0x1 << 9)
#घोषणा RT5677_LOUT1_ENH_DRV_SFT		(9)
#घोषणा RT5677_LOUT2_ENH_DRV			(0x1 << 8)
#घोषणा RT5677_LOUT2_ENH_DRV_SFT		(8)
#घोषणा RT5677_LOUT3_ENH_DRV			(0x1 << 7)
#घोषणा RT5677_LOUT3_ENH_DRV_SFT		(7)

/* IN1 Control (0x03) */
#घोषणा RT5677_BST_MASK1			(0xf << 12)
#घोषणा RT5677_BST_SFT1				12
#घोषणा RT5677_BST_MASK2			(0xf << 8)
#घोषणा RT5677_BST_SFT2				8
#घोषणा RT5677_IN_DF1				(0x1 << 7)
#घोषणा RT5677_IN_DF1_SFT			7
#घोषणा RT5677_IN_DF2				(0x1 << 6)
#घोषणा RT5677_IN_DF2_SFT			6

/* Micbias Control (0x04) */
#घोषणा RT5677_MICBIAS1_OUTVOLT_MASK		(0x1 << 15)
#घोषणा RT5677_MICBIAS1_OUTVOLT_SFT		(15)
#घोषणा RT5677_MICBIAS1_OUTVOLT_2_7V		(0x0 << 15)
#घोषणा RT5677_MICBIAS1_OUTVOLT_2_25V		(0x1 << 15)
#घोषणा RT5677_MICBIAS1_CTRL_VDD_MASK		(0x1 << 14)
#घोषणा RT5677_MICBIAS1_CTRL_VDD_SFT		(14)
#घोषणा RT5677_MICBIAS1_CTRL_VDD_1_8V		(0x0 << 14)
#घोषणा RT5677_MICBIAS1_CTRL_VDD_3_3V		(0x1 << 14)
#घोषणा RT5677_MICBIAS1_OVCD_MASK		(0x1 << 11)
#घोषणा RT5677_MICBIAS1_OVCD_SHIFT		(11)
#घोषणा RT5677_MICBIAS1_OVCD_DIS		(0x0 << 11)
#घोषणा RT5677_MICBIAS1_OVCD_EN			(0x1 << 11)
#घोषणा RT5677_MICBIAS1_OVTH_MASK		(0x3 << 9)
#घोषणा RT5677_MICBIAS1_OVTH_SFT		9
#घोषणा RT5677_MICBIAS1_OVTH_640UA		(0x0 << 9)
#घोषणा RT5677_MICBIAS1_OVTH_1280UA		(0x1 << 9)
#घोषणा RT5677_MICBIAS1_OVTH_1920UA		(0x2 << 9)

/* SLIMbus Parameter (0x07) */

/* SLIMbus Rx (0x08) */
#घोषणा RT5677_SLB_ADC4_MASK			(0x3 << 6)
#घोषणा RT5677_SLB_ADC4_SFT			6
#घोषणा RT5677_SLB_ADC3_MASK			(0x3 << 4)
#घोषणा RT5677_SLB_ADC3_SFT			4
#घोषणा RT5677_SLB_ADC2_MASK			(0x3 << 2)
#घोषणा RT5677_SLB_ADC2_SFT			2
#घोषणा RT5677_SLB_ADC1_MASK			(0x3 << 0)
#घोषणा RT5677_SLB_ADC1_SFT			0

/* SLIMBus control (0x09) */

/* Sidetone Control (0x13) */
#घोषणा RT5677_ST_HPF_SEL_MASK			(0x7 << 13)
#घोषणा RT5677_ST_HPF_SEL_SFT			13
#घोषणा RT5677_ST_HPF_PATH			(0x1 << 12)
#घोषणा RT5677_ST_HPF_PATH_SFT			12
#घोषणा RT5677_ST_SEL_MASK			(0x7 << 9)
#घोषणा RT5677_ST_SEL_SFT			9
#घोषणा RT5677_ST_EN				(0x1 << 6)
#घोषणा RT5677_ST_EN_SFT			6
#घोषणा RT5677_ST_GAIN				(0x1 << 5)
#घोषणा RT5677_ST_GAIN_SFT			5
#घोषणा RT5677_ST_VOL_MASK			(0x1f << 0)
#घोषणा RT5677_ST_VOL_SFT			0

/* Analog DAC1/2/3 Source Control (0x15) */
#घोषणा RT5677_ANA_DAC3_SRC_SEL_MASK		(0x3 << 4)
#घोषणा RT5677_ANA_DAC3_SRC_SEL_SFT		4
#घोषणा RT5677_ANA_DAC1_2_SRC_SEL_MASK		(0x3 << 0)
#घोषणा RT5677_ANA_DAC1_2_SRC_SEL_SFT		0

/* IF/DSP to DAC3/4 Mixer Control (0x16) */
#घोषणा RT5677_M_DAC4_L_VOL			(0x1 << 15)
#घोषणा RT5677_M_DAC4_L_VOL_SFT			15
#घोषणा RT5677_SEL_DAC4_L_SRC_MASK		(0x7 << 12)
#घोषणा RT5677_SEL_DAC4_L_SRC_SFT		12
#घोषणा RT5677_M_DAC4_R_VOL			(0x1 << 11)
#घोषणा RT5677_M_DAC4_R_VOL_SFT			11
#घोषणा RT5677_SEL_DAC4_R_SRC_MASK		(0x7 << 8)
#घोषणा RT5677_SEL_DAC4_R_SRC_SFT		8
#घोषणा RT5677_M_DAC3_L_VOL			(0x1 << 7)
#घोषणा RT5677_M_DAC3_L_VOL_SFT			7
#घोषणा RT5677_SEL_DAC3_L_SRC_MASK		(0x7 << 4)
#घोषणा RT5677_SEL_DAC3_L_SRC_SFT		4
#घोषणा RT5677_M_DAC3_R_VOL			(0x1 << 3)
#घोषणा RT5677_M_DAC3_R_VOL_SFT			3
#घोषणा RT5677_SEL_DAC3_R_SRC_MASK		(0x7 << 0)
#घोषणा RT5677_SEL_DAC3_R_SRC_SFT		0

/* DAC4 Digital Volume (0x17) */
#घोषणा RT5677_DAC4_L_VOL_MASK			(0xff << 8)
#घोषणा RT5677_DAC4_L_VOL_SFT			8
#घोषणा RT5677_DAC4_R_VOL_MASK			(0xff)
#घोषणा RT5677_DAC4_R_VOL_SFT			0

/* DAC3 Digital Volume (0x18) */
#घोषणा RT5677_DAC3_L_VOL_MASK			(0xff << 8)
#घोषणा RT5677_DAC3_L_VOL_SFT			8
#घोषणा RT5677_DAC3_R_VOL_MASK			(0xff)
#घोषणा RT5677_DAC3_R_VOL_SFT			0

/* DAC3 Digital Volume (0x19) */
#घोषणा RT5677_DAC1_L_VOL_MASK			(0xff << 8)
#घोषणा RT5677_DAC1_L_VOL_SFT			8
#घोषणा RT5677_DAC1_R_VOL_MASK			(0xff)
#घोषणा RT5677_DAC1_R_VOL_SFT			0

/* DAC2 Digital Volume (0x1a) */
#घोषणा RT5677_DAC2_L_VOL_MASK			(0xff << 8)
#घोषणा RT5677_DAC2_L_VOL_SFT			8
#घोषणा RT5677_DAC2_R_VOL_MASK			(0xff)
#घोषणा RT5677_DAC2_R_VOL_SFT			0

/* IF/DSP to DAC2 Mixer Control (0x1b) */
#घोषणा RT5677_M_DAC2_L_VOL			(0x1 << 7)
#घोषणा RT5677_M_DAC2_L_VOL_SFT			7
#घोषणा RT5677_SEL_DAC2_L_SRC_MASK		(0x7 << 4)
#घोषणा RT5677_SEL_DAC2_L_SRC_SFT		4
#घोषणा RT5677_M_DAC2_R_VOL			(0x1 << 3)
#घोषणा RT5677_M_DAC2_R_VOL_SFT			3
#घोषणा RT5677_SEL_DAC2_R_SRC_MASK		(0x7 << 0)
#घोषणा RT5677_SEL_DAC2_R_SRC_SFT		0

/* Stereo1 ADC Digital Volume Control (0x1c) */
#घोषणा RT5677_STO1_ADC_L_VOL_MASK		(0x3f << 9)
#घोषणा RT5677_STO1_ADC_L_VOL_SFT		9
#घोषणा RT5677_STO1_ADC_R_VOL_MASK		(0x3f << 1)
#घोषणा RT5677_STO1_ADC_R_VOL_SFT		1

/* Mono ADC Digital Volume Control (0x1d) */
#घोषणा RT5677_MONO_ADC_L_VOL_MASK		(0x3f << 9)
#घोषणा RT5677_MONO_ADC_L_VOL_SFT		9
#घोषणा RT5677_MONO_ADC_R_VOL_MASK		(0x3f << 1)
#घोषणा RT5677_MONO_ADC_R_VOL_SFT		1

/* Stereo 1/2 ADC Boost Gain Control (0x1e) */
#घोषणा RT5677_STO1_ADC_L_BST_MASK		(0x3 << 14)
#घोषणा RT5677_STO1_ADC_L_BST_SFT		14
#घोषणा RT5677_STO1_ADC_R_BST_MASK		(0x3 << 12)
#घोषणा RT5677_STO1_ADC_R_BST_SFT		12
#घोषणा RT5677_STO1_ADC_COMP_MASK		(0x3 << 10)
#घोषणा RT5677_STO1_ADC_COMP_SFT		10
#घोषणा RT5677_STO2_ADC_L_BST_MASK		(0x3 << 8)
#घोषणा RT5677_STO2_ADC_L_BST_SFT		8
#घोषणा RT5677_STO2_ADC_R_BST_MASK		(0x3 << 6)
#घोषणा RT5677_STO2_ADC_R_BST_SFT		6
#घोषणा RT5677_STO2_ADC_COMP_MASK		(0x3 << 4)
#घोषणा RT5677_STO2_ADC_COMP_SFT		4

/* Stereo2 ADC Digital Volume Control (0x1f) */
#घोषणा RT5677_STO2_ADC_L_VOL_MASK		(0x7f << 8)
#घोषणा RT5677_STO2_ADC_L_VOL_SFT		8
#घोषणा RT5677_STO2_ADC_R_VOL_MASK		(0x7f)
#घोषणा RT5677_STO2_ADC_R_VOL_SFT		0

/* ADC Boost Gain Control 2 (0x20) */
#घोषणा RT5677_MONO_ADC_L_BST_MASK		(0x3 << 14)
#घोषणा RT5677_MONO_ADC_L_BST_SFT		14
#घोषणा RT5677_MONO_ADC_R_BST_MASK		(0x3 << 12)
#घोषणा RT5677_MONO_ADC_R_BST_SFT		12
#घोषणा RT5677_MONO_ADC_COMP_MASK		(0x3 << 10)
#घोषणा RT5677_MONO_ADC_COMP_SFT		10

/* Stereo 3/4 ADC Boost Gain Control (0x21) */
#घोषणा RT5677_STO3_ADC_L_BST_MASK		(0x3 << 14)
#घोषणा RT5677_STO3_ADC_L_BST_SFT		14
#घोषणा RT5677_STO3_ADC_R_BST_MASK		(0x3 << 12)
#घोषणा RT5677_STO3_ADC_R_BST_SFT		12
#घोषणा RT5677_STO3_ADC_COMP_MASK		(0x3 << 10)
#घोषणा RT5677_STO3_ADC_COMP_SFT		10
#घोषणा RT5677_STO4_ADC_L_BST_MASK		(0x3 << 8)
#घोषणा RT5677_STO4_ADC_L_BST_SFT		8
#घोषणा RT5677_STO4_ADC_R_BST_MASK		(0x3 << 6)
#घोषणा RT5677_STO4_ADC_R_BST_SFT		6
#घोषणा RT5677_STO4_ADC_COMP_MASK		(0x3 << 4)
#घोषणा RT5677_STO4_ADC_COMP_SFT		4

/* Stereo3 ADC Digital Volume Control (0x22) */
#घोषणा RT5677_STO3_ADC_L_VOL_MASK		(0x7f << 8)
#घोषणा RT5677_STO3_ADC_L_VOL_SFT		8
#घोषणा RT5677_STO3_ADC_R_VOL_MASK		(0x7f)
#घोषणा RT5677_STO3_ADC_R_VOL_SFT		0

/* Stereo4 ADC Digital Volume Control (0x23) */
#घोषणा RT5677_STO4_ADC_L_VOL_MASK		(0x7f << 8)
#घोषणा RT5677_STO4_ADC_L_VOL_SFT		8
#घोषणा RT5677_STO4_ADC_R_VOL_MASK		(0x7f)
#घोषणा RT5677_STO4_ADC_R_VOL_SFT		0

/* Stereo4 ADC Mixer control (0x24) */
#घोषणा RT5677_M_STO4_ADC_L2			(0x1 << 15)
#घोषणा RT5677_M_STO4_ADC_L2_SFT		15
#घोषणा RT5677_M_STO4_ADC_L1			(0x1 << 14)
#घोषणा RT5677_M_STO4_ADC_L1_SFT		14
#घोषणा RT5677_SEL_STO4_ADC1_MASK		(0x3 << 12)
#घोषणा RT5677_SEL_STO4_ADC1_SFT		12
#घोषणा RT5677_SEL_STO4_ADC2_MASK		(0x3 << 10)
#घोषणा RT5677_SEL_STO4_ADC2_SFT		10
#घोषणा RT5677_SEL_STO4_DMIC_MASK		(0x3 << 8)
#घोषणा RT5677_SEL_STO4_DMIC_SFT		8
#घोषणा RT5677_M_STO4_ADC_R1			(0x1 << 7)
#घोषणा RT5677_M_STO4_ADC_R1_SFT		7
#घोषणा RT5677_M_STO4_ADC_R2			(0x1 << 6)
#घोषणा RT5677_M_STO4_ADC_R2_SFT		6

/* Stereo3 ADC Mixer control (0x25) */
#घोषणा RT5677_M_STO3_ADC_L2			(0x1 << 15)
#घोषणा RT5677_M_STO3_ADC_L2_SFT		15
#घोषणा RT5677_M_STO3_ADC_L1			(0x1 << 14)
#घोषणा RT5677_M_STO3_ADC_L1_SFT		14
#घोषणा RT5677_SEL_STO3_ADC1_MASK		(0x3 << 12)
#घोषणा RT5677_SEL_STO3_ADC1_SFT		12
#घोषणा RT5677_SEL_STO3_ADC2_MASK		(0x3 << 10)
#घोषणा RT5677_SEL_STO3_ADC2_SFT		10
#घोषणा RT5677_SEL_STO3_DMIC_MASK		(0x3 << 8)
#घोषणा RT5677_SEL_STO3_DMIC_SFT		8
#घोषणा RT5677_M_STO3_ADC_R1			(0x1 << 7)
#घोषणा RT5677_M_STO3_ADC_R1_SFT		7
#घोषणा RT5677_M_STO3_ADC_R2			(0x1 << 6)
#घोषणा RT5677_M_STO3_ADC_R2_SFT		6

/* Stereo2 ADC Mixer Control (0x26) */
#घोषणा RT5677_M_STO2_ADC_L2			(0x1 << 15)
#घोषणा RT5677_M_STO2_ADC_L2_SFT		15
#घोषणा RT5677_M_STO2_ADC_L1			(0x1 << 14)
#घोषणा RT5677_M_STO2_ADC_L1_SFT		14
#घोषणा RT5677_SEL_STO2_ADC1_MASK		(0x3 << 12)
#घोषणा RT5677_SEL_STO2_ADC1_SFT		12
#घोषणा RT5677_SEL_STO2_ADC2_MASK		(0x3 << 10)
#घोषणा RT5677_SEL_STO2_ADC2_SFT		10
#घोषणा RT5677_SEL_STO2_DMIC_MASK		(0x3 << 8)
#घोषणा RT5677_SEL_STO2_DMIC_SFT		8
#घोषणा RT5677_M_STO2_ADC_R1			(0x1 << 7)
#घोषणा RT5677_M_STO2_ADC_R1_SFT		7
#घोषणा RT5677_M_STO2_ADC_R2			(0x1 << 6)
#घोषणा RT5677_M_STO2_ADC_R2_SFT		6
#घोषणा RT5677_SEL_STO2_LR_MIX_MASK		(0x1 << 0)
#घोषणा RT5677_SEL_STO2_LR_MIX_SFT		0
#घोषणा RT5677_SEL_STO2_LR_MIX_L		(0x0 << 0)
#घोषणा RT5677_SEL_STO2_LR_MIX_LR		(0x1 << 0)

/* Stereo1 ADC Mixer control (0x27) */
#घोषणा RT5677_M_STO1_ADC_L2			(0x1 << 15)
#घोषणा RT5677_M_STO1_ADC_L2_SFT		15
#घोषणा RT5677_M_STO1_ADC_L1			(0x1 << 14)
#घोषणा RT5677_M_STO1_ADC_L1_SFT		14
#घोषणा RT5677_SEL_STO1_ADC1_MASK		(0x3 << 12)
#घोषणा RT5677_SEL_STO1_ADC1_SFT		12
#घोषणा RT5677_SEL_STO1_ADC2_MASK		(0x3 << 10)
#घोषणा RT5677_SEL_STO1_ADC2_SFT		10
#घोषणा RT5677_SEL_STO1_DMIC_MASK		(0x3 << 8)
#घोषणा RT5677_SEL_STO1_DMIC_SFT		8
#घोषणा RT5677_M_STO1_ADC_R1			(0x1 << 7)
#घोषणा RT5677_M_STO1_ADC_R1_SFT		7
#घोषणा RT5677_M_STO1_ADC_R2			(0x1 << 6)
#घोषणा RT5677_M_STO1_ADC_R2_SFT		6

/* Mono ADC Mixer control (0x28) */
#घोषणा RT5677_M_MONO_ADC_L2			(0x1 << 15)
#घोषणा RT5677_M_MONO_ADC_L2_SFT		15
#घोषणा RT5677_M_MONO_ADC_L1			(0x1 << 14)
#घोषणा RT5677_M_MONO_ADC_L1_SFT		14
#घोषणा RT5677_SEL_MONO_ADC_L1_MASK		(0x3 << 12)
#घोषणा RT5677_SEL_MONO_ADC_L1_SFT		12
#घोषणा RT5677_SEL_MONO_ADC_L2_MASK		(0x3 << 10)
#घोषणा RT5677_SEL_MONO_ADC_L2_SFT		10
#घोषणा RT5677_SEL_MONO_DMIC_L_MASK		(0x3 << 8)
#घोषणा RT5677_SEL_MONO_DMIC_L_SFT		8
#घोषणा RT5677_M_MONO_ADC_R1			(0x1 << 7)
#घोषणा RT5677_M_MONO_ADC_R1_SFT		7
#घोषणा RT5677_M_MONO_ADC_R2			(0x1 << 6)
#घोषणा RT5677_M_MONO_ADC_R2_SFT		6
#घोषणा RT5677_SEL_MONO_ADC_R1_MASK		(0x3 << 4)
#घोषणा RT5677_SEL_MONO_ADC_R1_SFT		4
#घोषणा RT5677_SEL_MONO_ADC_R2_MASK		(0x3 << 2)
#घोषणा RT5677_SEL_MONO_ADC_R2_SFT		2
#घोषणा RT5677_SEL_MONO_DMIC_R_MASK		(0x3 << 0)
#घोषणा RT5677_SEL_MONO_DMIC_R_SFT		0

/* ADC/IF/DSP to DAC1 Mixer control (0x29) */
#घोषणा RT5677_M_ADDA_MIXER1_L			(0x1 << 15)
#घोषणा RT5677_M_ADDA_MIXER1_L_SFT		15
#घोषणा RT5677_M_DAC1_L				(0x1 << 14)
#घोषणा RT5677_M_DAC1_L_SFT			14
#घोषणा RT5677_DAC1_L_SEL_MASK			(0x7 << 8)
#घोषणा RT5677_DAC1_L_SEL_SFT			8
#घोषणा RT5677_M_ADDA_MIXER1_R			(0x1 << 7)
#घोषणा RT5677_M_ADDA_MIXER1_R_SFT		7
#घोषणा RT5677_M_DAC1_R				(0x1 << 6)
#घोषणा RT5677_M_DAC1_R_SFT			6
#घोषणा RT5677_ADDA1_SEL_MASK			(0x3 << 0)
#घोषणा RT5677_ADDA1_SEL_SFT			0

/* Stereo1 DAC Mixer L/R Control (0x2a) */
#घोषणा RT5677_M_ST_DAC1_L			(0x1 << 15)
#घोषणा RT5677_M_ST_DAC1_L_SFT			15
#घोषणा RT5677_M_DAC1_L_STO_L			(0x1 << 13)
#घोषणा RT5677_M_DAC1_L_STO_L_SFT		13
#घोषणा RT5677_DAC1_L_STO_L_VOL_MASK		(0x1 << 12)
#घोषणा RT5677_DAC1_L_STO_L_VOL_SFT		12
#घोषणा RT5677_M_DAC2_L_STO_L			(0x1 << 11)
#घोषणा RT5677_M_DAC2_L_STO_L_SFT		11
#घोषणा RT5677_DAC2_L_STO_L_VOL_MASK		(0x1 << 10)
#घोषणा RT5677_DAC2_L_STO_L_VOL_SFT		10
#घोषणा RT5677_M_DAC1_R_STO_L			(0x1 << 9)
#घोषणा RT5677_M_DAC1_R_STO_L_SFT		9
#घोषणा RT5677_DAC1_R_STO_L_VOL_MASK		(0x1 << 8)
#घोषणा RT5677_DAC1_R_STO_L_VOL_SFT		8
#घोषणा RT5677_M_ST_DAC1_R			(0x1 << 7)
#घोषणा RT5677_M_ST_DAC1_R_SFT			7
#घोषणा RT5677_M_DAC1_R_STO_R			(0x1 << 5)
#घोषणा RT5677_M_DAC1_R_STO_R_SFT		5
#घोषणा RT5677_DAC1_R_STO_R_VOL_MASK		(0x1 << 4)
#घोषणा RT5677_DAC1_R_STO_R_VOL_SFT		4
#घोषणा RT5677_M_DAC2_R_STO_R			(0x1 << 3)
#घोषणा RT5677_M_DAC2_R_STO_R_SFT		3
#घोषणा RT5677_DAC2_R_STO_R_VOL_MASK		(0x1 << 2)
#घोषणा RT5677_DAC2_R_STO_R_VOL_SFT		2
#घोषणा RT5677_M_DAC1_L_STO_R			(0x1 << 1)
#घोषणा RT5677_M_DAC1_L_STO_R_SFT		1
#घोषणा RT5677_DAC1_L_STO_R_VOL_MASK		(0x1 << 0)
#घोषणा RT5677_DAC1_L_STO_R_VOL_SFT		0

/* Mono DAC Mixer L/R Control (0x2b) */
#घोषणा RT5677_M_ST_DAC2_L			(0x1 << 15)
#घोषणा RT5677_M_ST_DAC2_L_SFT			15
#घोषणा RT5677_M_DAC2_L_MONO_L			(0x1 << 13)
#घोषणा RT5677_M_DAC2_L_MONO_L_SFT		13
#घोषणा RT5677_DAC2_L_MONO_L_VOL_MASK		(0x1 << 12)
#घोषणा RT5677_DAC2_L_MONO_L_VOL_SFT		12
#घोषणा RT5677_M_DAC2_R_MONO_L			(0x1 << 11)
#घोषणा RT5677_M_DAC2_R_MONO_L_SFT		11
#घोषणा RT5677_DAC2_R_MONO_L_VOL_MASK		(0x1 << 10)
#घोषणा RT5677_DAC2_R_MONO_L_VOL_SFT		10
#घोषणा RT5677_M_DAC1_L_MONO_L			(0x1 << 9)
#घोषणा RT5677_M_DAC1_L_MONO_L_SFT		9
#घोषणा RT5677_DAC1_L_MONO_L_VOL_MASK		(0x1 << 8)
#घोषणा RT5677_DAC1_L_MONO_L_VOL_SFT		8
#घोषणा RT5677_M_ST_DAC2_R			(0x1 << 7)
#घोषणा RT5677_M_ST_DAC2_R_SFT			7
#घोषणा RT5677_M_DAC2_R_MONO_R			(0x1 << 5)
#घोषणा RT5677_M_DAC2_R_MONO_R_SFT		5
#घोषणा RT5677_DAC2_R_MONO_R_VOL_MASK		(0x1 << 4)
#घोषणा RT5677_DAC2_R_MONO_R_VOL_SFT		4
#घोषणा RT5677_M_DAC1_R_MONO_R			(0x1 << 3)
#घोषणा RT5677_M_DAC1_R_MONO_R_SFT		3
#घोषणा RT5677_DAC1_R_MONO_R_VOL_MASK		(0x1 << 2)
#घोषणा RT5677_DAC1_R_MONO_R_VOL_SFT		2
#घोषणा RT5677_M_DAC2_L_MONO_R			(0x1 << 1)
#घोषणा RT5677_M_DAC2_L_MONO_R_SFT		1
#घोषणा RT5677_DAC2_L_MONO_R_VOL_MASK		(0x1 << 0)
#घोषणा RT5677_DAC2_L_MONO_R_VOL_SFT		0

/* DD Mixer 1 Control (0x2c) */
#घोषणा RT5677_M_STO_L_DD1_L			(0x1 << 15)
#घोषणा RT5677_M_STO_L_DD1_L_SFT		15
#घोषणा RT5677_STO_L_DD1_L_VOL_MASK		(0x1 << 14)
#घोषणा RT5677_STO_L_DD1_L_VOL_SFT		14
#घोषणा RT5677_M_MONO_L_DD1_L			(0x1 << 13)
#घोषणा RT5677_M_MONO_L_DD1_L_SFT		13
#घोषणा RT5677_MONO_L_DD1_L_VOL_MASK		(0x1 << 12)
#घोषणा RT5677_MONO_L_DD1_L_VOL_SFT		12
#घोषणा RT5677_M_DAC3_L_DD1_L			(0x1 << 11)
#घोषणा RT5677_M_DAC3_L_DD1_L_SFT		11
#घोषणा RT5677_DAC3_L_DD1_L_VOL_MASK		(0x1 << 10)
#घोषणा RT5677_DAC3_L_DD1_L_VOL_SFT		10
#घोषणा RT5677_M_DAC3_R_DD1_L			(0x1 << 9)
#घोषणा RT5677_M_DAC3_R_DD1_L_SFT		9
#घोषणा RT5677_DAC3_R_DD1_L_VOL_MASK		(0x1 << 8)
#घोषणा RT5677_DAC3_R_DD1_L_VOL_SFT		8
#घोषणा RT5677_M_STO_R_DD1_R			(0x1 << 7)
#घोषणा RT5677_M_STO_R_DD1_R_SFT		7
#घोषणा RT5677_STO_R_DD1_R_VOL_MASK		(0x1 << 6)
#घोषणा RT5677_STO_R_DD1_R_VOL_SFT		6
#घोषणा RT5677_M_MONO_R_DD1_R			(0x1 << 5)
#घोषणा RT5677_M_MONO_R_DD1_R_SFT		5
#घोषणा RT5677_MONO_R_DD1_R_VOL_MASK		(0x1 << 4)
#घोषणा RT5677_MONO_R_DD1_R_VOL_SFT		4
#घोषणा RT5677_M_DAC3_R_DD1_R			(0x1 << 3)
#घोषणा RT5677_M_DAC3_R_DD1_R_SFT		3
#घोषणा RT5677_DAC3_R_DD1_R_VOL_MASK		(0x1 << 2)
#घोषणा RT5677_DAC3_R_DD1_R_VOL_SFT		2
#घोषणा RT5677_M_DAC3_L_DD1_R			(0x1 << 1)
#घोषणा RT5677_M_DAC3_L_DD1_R_SFT		1
#घोषणा RT5677_DAC3_L_DD1_R_VOL_MASK		(0x1 << 0)
#घोषणा RT5677_DAC3_L_DD1_R_VOL_SFT		0

/* DD Mixer 2 Control (0x2d) */
#घोषणा RT5677_M_STO_L_DD2_L			(0x1 << 15)
#घोषणा RT5677_M_STO_L_DD2_L_SFT		15
#घोषणा RT5677_STO_L_DD2_L_VOL_MASK		(0x1 << 14)
#घोषणा RT5677_STO_L_DD2_L_VOL_SFT		14
#घोषणा RT5677_M_MONO_L_DD2_L			(0x1 << 13)
#घोषणा RT5677_M_MONO_L_DD2_L_SFT		13
#घोषणा RT5677_MONO_L_DD2_L_VOL_MASK		(0x1 << 12)
#घोषणा RT5677_MONO_L_DD2_L_VOL_SFT		12
#घोषणा RT5677_M_DAC4_L_DD2_L			(0x1 << 11)
#घोषणा RT5677_M_DAC4_L_DD2_L_SFT		11
#घोषणा RT5677_DAC4_L_DD2_L_VOL_MASK		(0x1 << 10)
#घोषणा RT5677_DAC4_L_DD2_L_VOL_SFT		10
#घोषणा RT5677_M_DAC4_R_DD2_L			(0x1 << 9)
#घोषणा RT5677_M_DAC4_R_DD2_L_SFT		9
#घोषणा RT5677_DAC4_R_DD2_L_VOL_MASK		(0x1 << 8)
#घोषणा RT5677_DAC4_R_DD2_L_VOL_SFT		8
#घोषणा RT5677_M_STO_R_DD2_R			(0x1 << 7)
#घोषणा RT5677_M_STO_R_DD2_R_SFT		7
#घोषणा RT5677_STO_R_DD2_R_VOL_MASK		(0x1 << 6)
#घोषणा RT5677_STO_R_DD2_R_VOL_SFT		6
#घोषणा RT5677_M_MONO_R_DD2_R			(0x1 << 5)
#घोषणा RT5677_M_MONO_R_DD2_R_SFT		5
#घोषणा RT5677_MONO_R_DD2_R_VOL_MASK		(0x1 << 4)
#घोषणा RT5677_MONO_R_DD2_R_VOL_SFT		4
#घोषणा RT5677_M_DAC4_R_DD2_R			(0x1 << 3)
#घोषणा RT5677_M_DAC4_R_DD2_R_SFT		3
#घोषणा RT5677_DAC4_R_DD2_R_VOL_MASK		(0x1 << 2)
#घोषणा RT5677_DAC4_R_DD2_R_VOL_SFT		2
#घोषणा RT5677_M_DAC4_L_DD2_R			(0x1 << 1)
#घोषणा RT5677_M_DAC4_L_DD2_R_SFT		1
#घोषणा RT5677_DAC4_L_DD2_R_VOL_MASK		(0x1 << 0)
#घोषणा RT5677_DAC4_L_DD2_R_VOL_SFT		0

/* IF3 data control (0x2f) */
#घोषणा RT5677_IF3_DAC_SEL_MASK			(0x3 << 6)
#घोषणा RT5677_IF3_DAC_SEL_SFT			6
#घोषणा RT5677_IF3_ADC_SEL_MASK			(0x3 << 4)
#घोषणा RT5677_IF3_ADC_SEL_SFT			4
#घोषणा RT5677_IF3_ADC_IN_MASK			(0xf << 0)
#घोषणा RT5677_IF3_ADC_IN_SFT			0

/* IF4 data control (0x30) */
#घोषणा RT5677_IF4_ADC_IN_MASK			(0xf << 4)
#घोषणा RT5677_IF4_ADC_IN_SFT			4
#घोषणा RT5677_IF4_DAC_SEL_MASK			(0x3 << 2)
#घोषणा RT5677_IF4_DAC_SEL_SFT			2
#घोषणा RT5677_IF4_ADC_SEL_MASK			(0x3 << 0)
#घोषणा RT5677_IF4_ADC_SEL_SFT			0

/* PDM Output Control (0x31) */
#घोषणा RT5677_M_PDM1_L				(0x1 << 15)
#घोषणा RT5677_M_PDM1_L_SFT			15
#घोषणा RT5677_SEL_PDM1_L_MASK			(0x3 << 12)
#घोषणा RT5677_SEL_PDM1_L_SFT			12
#घोषणा RT5677_M_PDM1_R				(0x1 << 11)
#घोषणा RT5677_M_PDM1_R_SFT			11
#घोषणा RT5677_SEL_PDM1_R_MASK			(0x3 << 8)
#घोषणा RT5677_SEL_PDM1_R_SFT			8
#घोषणा RT5677_M_PDM2_L				(0x1 << 7)
#घोषणा RT5677_M_PDM2_L_SFT			7
#घोषणा RT5677_SEL_PDM2_L_MASK			(0x3 << 4)
#घोषणा RT5677_SEL_PDM2_L_SFT			4
#घोषणा RT5677_M_PDM2_R				(0x1 << 3)
#घोषणा RT5677_M_PDM2_R_SFT			3
#घोषणा RT5677_SEL_PDM2_R_MASK			(0x3 << 0)
#घोषणा RT5677_SEL_PDM2_R_SFT			0

/* PDM I2C / Data Control 1 (0x32) */
#घोषणा RT5677_PDM2_PW_DOWN			(0x1 << 7)
#घोषणा RT5677_PDM1_PW_DOWN			(0x1 << 6)
#घोषणा RT5677_PDM2_BUSY			(0x1 << 5)
#घोषणा RT5677_PDM1_BUSY			(0x1 << 4)
#घोषणा RT5677_PDM_PATTERN			(0x1 << 3)
#घोषणा RT5677_PDM_GAIN				(0x1 << 2)
#घोषणा RT5677_PDM_DIV_MASK			(0x3 << 0)

/* PDM I2C / Data Control 2 (0x33) */
#घोषणा RT5677_PDM1_I2C_ID			(0xf << 12)
#घोषणा RT5677_PDM1_EXE				(0x1 << 11)
#घोषणा RT5677_PDM1_I2C_CMD			(0x1 << 10)
#घोषणा RT5677_PDM1_I2C_EXE			(0x1 << 9)
#घोषणा RT5677_PDM1_I2C_BUSY			(0x1 << 8)
#घोषणा RT5677_PDM2_I2C_ID			(0xf << 4)
#घोषणा RT5677_PDM2_EXE				(0x1 << 3)
#घोषणा RT5677_PDM2_I2C_CMD			(0x1 << 2)
#घोषणा RT5677_PDM2_I2C_EXE			(0x1 << 1)
#घोषणा RT5677_PDM2_I2C_BUSY			(0x1 << 0)

/* TDM1 control 1 (0x3b) */
#घोषणा RT5677_IF1_ADC_MODE_MASK		(0x1 << 12)
#घोषणा RT5677_IF1_ADC_MODE_SFT			12
#घोषणा RT5677_IF1_ADC_MODE_I2S			(0x0 << 12)
#घोषणा RT5677_IF1_ADC_MODE_TDM			(0x1 << 12)
#घोषणा RT5677_IF1_ADC1_SWAP_MASK		(0x3 << 6)
#घोषणा RT5677_IF1_ADC1_SWAP_SFT		6
#घोषणा RT5677_IF1_ADC2_SWAP_MASK		(0x3 << 4)
#घोषणा RT5677_IF1_ADC2_SWAP_SFT		4
#घोषणा RT5677_IF1_ADC3_SWAP_MASK		(0x3 << 2)
#घोषणा RT5677_IF1_ADC3_SWAP_SFT		2
#घोषणा RT5677_IF1_ADC4_SWAP_MASK		(0x3 << 0)
#घोषणा RT5677_IF1_ADC4_SWAP_SFT		0

/* TDM1 control 2 (0x3c) */
#घोषणा RT5677_IF1_ADC4_MASK			(0x3 << 10)
#घोषणा RT5677_IF1_ADC4_SFT			10
#घोषणा RT5677_IF1_ADC3_MASK			(0x3 << 8)
#घोषणा RT5677_IF1_ADC3_SFT			8
#घोषणा RT5677_IF1_ADC2_MASK			(0x3 << 6)
#घोषणा RT5677_IF1_ADC2_SFT			6
#घोषणा RT5677_IF1_ADC1_MASK			(0x3 << 4)
#घोषणा RT5677_IF1_ADC1_SFT			4
#घोषणा RT5677_IF1_ADC_CTRL_MASK		(0x7 << 0)
#घोषणा RT5677_IF1_ADC_CTRL_SFT			0

/* TDM1 control 4 (0x3e) */
#घोषणा RT5677_IF1_DAC0_MASK			(0x7 << 12)
#घोषणा RT5677_IF1_DAC0_SFT			12
#घोषणा RT5677_IF1_DAC1_MASK			(0x7 << 8)
#घोषणा RT5677_IF1_DAC1_SFT			8
#घोषणा RT5677_IF1_DAC2_MASK			(0x7 << 4)
#घोषणा RT5677_IF1_DAC2_SFT			4
#घोषणा RT5677_IF1_DAC3_MASK			(0x7 << 0)
#घोषणा RT5677_IF1_DAC3_SFT			0

/* TDM1 control 5 (0x3f) */
#घोषणा RT5677_IF1_DAC4_MASK			(0x7 << 12)
#घोषणा RT5677_IF1_DAC4_SFT			12
#घोषणा RT5677_IF1_DAC5_MASK			(0x7 << 8)
#घोषणा RT5677_IF1_DAC5_SFT			8
#घोषणा RT5677_IF1_DAC6_MASK			(0x7 << 4)
#घोषणा RT5677_IF1_DAC6_SFT			4
#घोषणा RT5677_IF1_DAC7_MASK			(0x7 << 0)
#घोषणा RT5677_IF1_DAC7_SFT			0

/* TDM2 control 1 (0x40) */
#घोषणा RT5677_IF2_ADC_MODE_MASK		(0x1 << 12)
#घोषणा RT5677_IF2_ADC_MODE_SFT			12
#घोषणा RT5677_IF2_ADC_MODE_I2S			(0x0 << 12)
#घोषणा RT5677_IF2_ADC_MODE_TDM			(0x1 << 12)
#घोषणा RT5677_IF2_ADC1_SWAP_MASK		(0x3 << 6)
#घोषणा RT5677_IF2_ADC1_SWAP_SFT		6
#घोषणा RT5677_IF2_ADC2_SWAP_MASK		(0x3 << 4)
#घोषणा RT5677_IF2_ADC2_SWAP_SFT		4
#घोषणा RT5677_IF2_ADC3_SWAP_MASK		(0x3 << 2)
#घोषणा RT5677_IF2_ADC3_SWAP_SFT		2
#घोषणा RT5677_IF2_ADC4_SWAP_MASK		(0x3 << 0)
#घोषणा RT5677_IF2_ADC4_SWAP_SFT		0

/* TDM2 control 2 (0x41) */
#घोषणा RT5677_IF2_ADC4_MASK			(0x3 << 10)
#घोषणा RT5677_IF2_ADC4_SFT			10
#घोषणा RT5677_IF2_ADC3_MASK			(0x3 << 8)
#घोषणा RT5677_IF2_ADC3_SFT			8
#घोषणा RT5677_IF2_ADC2_MASK			(0x3 << 6)
#घोषणा RT5677_IF2_ADC2_SFT			6
#घोषणा RT5677_IF2_ADC1_MASK			(0x3 << 4)
#घोषणा RT5677_IF2_ADC1_SFT			4
#घोषणा RT5677_IF2_ADC_CTRL_MASK		(0x7 << 0)
#घोषणा RT5677_IF2_ADC_CTRL_SFT			0

/* TDM2 control 4 (0x43) */
#घोषणा RT5677_IF2_DAC0_MASK			(0x7 << 12)
#घोषणा RT5677_IF2_DAC0_SFT			12
#घोषणा RT5677_IF2_DAC1_MASK			(0x7 << 8)
#घोषणा RT5677_IF2_DAC1_SFT			8
#घोषणा RT5677_IF2_DAC2_MASK			(0x7 << 4)
#घोषणा RT5677_IF2_DAC2_SFT			4
#घोषणा RT5677_IF2_DAC3_MASK			(0x7 << 0)
#घोषणा RT5677_IF2_DAC3_SFT			0

/* TDM2 control 5 (0x44) */
#घोषणा RT5677_IF2_DAC4_MASK			(0x7 << 12)
#घोषणा RT5677_IF2_DAC4_SFT			12
#घोषणा RT5677_IF2_DAC5_MASK			(0x7 << 8)
#घोषणा RT5677_IF2_DAC5_SFT			8
#घोषणा RT5677_IF2_DAC6_MASK			(0x7 << 4)
#घोषणा RT5677_IF2_DAC6_SFT			4
#घोषणा RT5677_IF2_DAC7_MASK			(0x7 << 0)
#घोषणा RT5677_IF2_DAC7_SFT			0

/* Digital Microphone Control 1 (0x50) */
#घोषणा RT5677_DMIC_1_EN_MASK			(0x1 << 15)
#घोषणा RT5677_DMIC_1_EN_SFT			15
#घोषणा RT5677_DMIC_1_DIS			(0x0 << 15)
#घोषणा RT5677_DMIC_1_EN			(0x1 << 15)
#घोषणा RT5677_DMIC_2_EN_MASK			(0x1 << 14)
#घोषणा RT5677_DMIC_2_EN_SFT			14
#घोषणा RT5677_DMIC_2_DIS			(0x0 << 14)
#घोषणा RT5677_DMIC_2_EN			(0x1 << 14)
#घोषणा RT5677_DMIC_L_STO1_LH_MASK		(0x1 << 13)
#घोषणा RT5677_DMIC_L_STO1_LH_SFT		13
#घोषणा RT5677_DMIC_L_STO1_LH_FALLING		(0x0 << 13)
#घोषणा RT5677_DMIC_L_STO1_LH_RISING		(0x1 << 13)
#घोषणा RT5677_DMIC_R_STO1_LH_MASK		(0x1 << 12)
#घोषणा RT5677_DMIC_R_STO1_LH_SFT		12
#घोषणा RT5677_DMIC_R_STO1_LH_FALLING		(0x0 << 12)
#घोषणा RT5677_DMIC_R_STO1_LH_RISING		(0x1 << 12)
#घोषणा RT5677_DMIC_L_STO3_LH_MASK		(0x1 << 11)
#घोषणा RT5677_DMIC_L_STO3_LH_SFT		11
#घोषणा RT5677_DMIC_L_STO3_LH_FALLING		(0x0 << 11)
#घोषणा RT5677_DMIC_L_STO3_LH_RISING		(0x1 << 11)
#घोषणा RT5677_DMIC_R_STO3_LH_MASK		(0x1 << 10)
#घोषणा RT5677_DMIC_R_STO3_LH_SFT		10
#घोषणा RT5677_DMIC_R_STO3_LH_FALLING		(0x0 << 10)
#घोषणा RT5677_DMIC_R_STO3_LH_RISING		(0x1 << 10)
#घोषणा RT5677_DMIC_L_STO2_LH_MASK		(0x1 << 9)
#घोषणा RT5677_DMIC_L_STO2_LH_SFT		9
#घोषणा RT5677_DMIC_L_STO2_LH_FALLING		(0x0 << 9)
#घोषणा RT5677_DMIC_L_STO2_LH_RISING		(0x1 << 9)
#घोषणा RT5677_DMIC_R_STO2_LH_MASK		(0x1 << 8)
#घोषणा RT5677_DMIC_R_STO2_LH_SFT		8
#घोषणा RT5677_DMIC_R_STO2_LH_FALLING		(0x0 << 8)
#घोषणा RT5677_DMIC_R_STO2_LH_RISING		(0x1 << 8)
#घोषणा RT5677_DMIC_CLK_MASK			(0x7 << 5)
#घोषणा RT5677_DMIC_CLK_SFT			5
#घोषणा RT5677_DMIC_3_EN_MASK			(0x1 << 4)
#घोषणा RT5677_DMIC_3_EN_SFT			4
#घोषणा RT5677_DMIC_3_DIS			(0x0 << 4)
#घोषणा RT5677_DMIC_3_EN			(0x1 << 4)
#घोषणा RT5677_DMIC_R_MONO_LH_MASK		(0x1 << 2)
#घोषणा RT5677_DMIC_R_MONO_LH_SFT		2
#घोषणा RT5677_DMIC_R_MONO_LH_FALLING		(0x0 << 2)
#घोषणा RT5677_DMIC_R_MONO_LH_RISING		(0x1 << 2)
#घोषणा RT5677_DMIC_L_STO4_LH_MASK		(0x1 << 1)
#घोषणा RT5677_DMIC_L_STO4_LH_SFT		1
#घोषणा RT5677_DMIC_L_STO4_LH_FALLING		(0x0 << 1)
#घोषणा RT5677_DMIC_L_STO4_LH_RISING		(0x1 << 1)
#घोषणा RT5677_DMIC_R_STO4_LH_MASK		(0x1 << 0)
#घोषणा RT5677_DMIC_R_STO4_LH_SFT		0
#घोषणा RT5677_DMIC_R_STO4_LH_FALLING		(0x0 << 0)
#घोषणा RT5677_DMIC_R_STO4_LH_RISING		(0x1 << 0)

/* Digital Microphone Control 2 (0x51) */
#घोषणा RT5677_DMIC_4_EN_MASK			(0x1 << 15)
#घोषणा RT5677_DMIC_4_EN_SFT			15
#घोषणा RT5677_DMIC_4_DIS			(0x0 << 15)
#घोषणा RT5677_DMIC_4_EN			(0x1 << 15)
#घोषणा RT5677_DMIC_4L_LH_MASK			(0x1 << 7)
#घोषणा RT5677_DMIC_4L_LH_SFT			7
#घोषणा RT5677_DMIC_4L_LH_FALLING		(0x0 << 7)
#घोषणा RT5677_DMIC_4L_LH_RISING		(0x1 << 7)
#घोषणा RT5677_DMIC_4R_LH_MASK			(0x1 << 6)
#घोषणा RT5677_DMIC_4R_LH_SFT			6
#घोषणा RT5677_DMIC_4R_LH_FALLING		(0x0 << 6)
#घोषणा RT5677_DMIC_4R_LH_RISING		(0x1 << 6)
#घोषणा RT5677_DMIC_3L_LH_MASK			(0x1 << 5)
#घोषणा RT5677_DMIC_3L_LH_SFT			5
#घोषणा RT5677_DMIC_3L_LH_FALLING		(0x0 << 5)
#घोषणा RT5677_DMIC_3L_LH_RISING		(0x1 << 5)
#घोषणा RT5677_DMIC_3R_LH_MASK			(0x1 << 4)
#घोषणा RT5677_DMIC_3R_LH_SFT			4
#घोषणा RT5677_DMIC_3R_LH_FALLING		(0x0 << 4)
#घोषणा RT5677_DMIC_3R_LH_RISING		(0x1 << 4)
#घोषणा RT5677_DMIC_2L_LH_MASK			(0x1 << 3)
#घोषणा RT5677_DMIC_2L_LH_SFT			3
#घोषणा RT5677_DMIC_2L_LH_FALLING		(0x0 << 3)
#घोषणा RT5677_DMIC_2L_LH_RISING		(0x1 << 3)
#घोषणा RT5677_DMIC_2R_LH_MASK			(0x1 << 2)
#घोषणा RT5677_DMIC_2R_LH_SFT			2
#घोषणा RT5677_DMIC_2R_LH_FALLING		(0x0 << 2)
#घोषणा RT5677_DMIC_2R_LH_RISING		(0x1 << 2)
#घोषणा RT5677_DMIC_1L_LH_MASK			(0x1 << 1)
#घोषणा RT5677_DMIC_1L_LH_SFT			1
#घोषणा RT5677_DMIC_1L_LH_FALLING		(0x0 << 1)
#घोषणा RT5677_DMIC_1L_LH_RISING		(0x1 << 1)
#घोषणा RT5677_DMIC_1R_LH_MASK			(0x1 << 0)
#घोषणा RT5677_DMIC_1R_LH_SFT			0
#घोषणा RT5677_DMIC_1R_LH_FALLING		(0x0 << 0)
#घोषणा RT5677_DMIC_1R_LH_RISING		(0x1 << 0)

/* Power Management क्रम Digital 1 (0x61) */
#घोषणा RT5677_PWR_I2S1				(0x1 << 15)
#घोषणा RT5677_PWR_I2S1_BIT			15
#घोषणा RT5677_PWR_I2S2				(0x1 << 14)
#घोषणा RT5677_PWR_I2S2_BIT			14
#घोषणा RT5677_PWR_I2S3				(0x1 << 13)
#घोषणा RT5677_PWR_I2S3_BIT			13
#घोषणा RT5677_PWR_DAC1				(0x1 << 12)
#घोषणा RT5677_PWR_DAC1_BIT			12
#घोषणा RT5677_PWR_DAC2				(0x1 << 11)
#घोषणा RT5677_PWR_DAC2_BIT			11
#घोषणा RT5677_PWR_I2S4				(0x1 << 10)
#घोषणा RT5677_PWR_I2S4_BIT			10
#घोषणा RT5677_PWR_SLB				(0x1 << 9)
#घोषणा RT5677_PWR_SLB_BIT			9
#घोषणा RT5677_PWR_DAC3				(0x1 << 7)
#घोषणा RT5677_PWR_DAC3_BIT			7
#घोषणा RT5677_PWR_ADCFED2			(0x1 << 4)
#घोषणा RT5677_PWR_ADCFED2_BIT			4
#घोषणा RT5677_PWR_ADCFED1			(0x1 << 3)
#घोषणा RT5677_PWR_ADCFED1_BIT			3
#घोषणा RT5677_PWR_ADC_L			(0x1 << 2)
#घोषणा RT5677_PWR_ADC_L_BIT			2
#घोषणा RT5677_PWR_ADC_R			(0x1 << 1)
#घोषणा RT5677_PWR_ADC_R_BIT			1
#घोषणा RT5677_PWR_I2C_MASTER			(0x1 << 0)
#घोषणा RT5677_PWR_I2C_MASTER_BIT		0

/* Power Management क्रम Digital 2 (0x62) */
#घोषणा RT5677_PWR_ADC_S1F			(0x1 << 15)
#घोषणा RT5677_PWR_ADC_S1F_BIT			15
#घोषणा RT5677_PWR_ADC_MF_L			(0x1 << 14)
#घोषणा RT5677_PWR_ADC_MF_L_BIT			14
#घोषणा RT5677_PWR_ADC_MF_R			(0x1 << 13)
#घोषणा RT5677_PWR_ADC_MF_R_BIT			13
#घोषणा RT5677_PWR_DAC_S1F			(0x1 << 12)
#घोषणा RT5677_PWR_DAC_S1F_BIT			12
#घोषणा RT5677_PWR_DAC_M2F_L			(0x1 << 11)
#घोषणा RT5677_PWR_DAC_M2F_L_BIT		11
#घोषणा RT5677_PWR_DAC_M2F_R			(0x1 << 10)
#घोषणा RT5677_PWR_DAC_M2F_R_BIT		10
#घोषणा RT5677_PWR_DAC_M3F_L			(0x1 << 9)
#घोषणा RT5677_PWR_DAC_M3F_L_BIT		9
#घोषणा RT5677_PWR_DAC_M3F_R			(0x1 << 8)
#घोषणा RT5677_PWR_DAC_M3F_R_BIT		8
#घोषणा RT5677_PWR_DAC_M4F_L			(0x1 << 7)
#घोषणा RT5677_PWR_DAC_M4F_L_BIT		7
#घोषणा RT5677_PWR_DAC_M4F_R			(0x1 << 6)
#घोषणा RT5677_PWR_DAC_M4F_R_BIT		6
#घोषणा RT5677_PWR_ADC_S2F			(0x1 << 5)
#घोषणा RT5677_PWR_ADC_S2F_BIT			5
#घोषणा RT5677_PWR_ADC_S3F			(0x1 << 4)
#घोषणा RT5677_PWR_ADC_S3F_BIT			4
#घोषणा RT5677_PWR_ADC_S4F			(0x1 << 3)
#घोषणा RT5677_PWR_ADC_S4F_BIT			3
#घोषणा RT5677_PWR_PDM1				(0x1 << 2)
#घोषणा RT5677_PWR_PDM1_BIT			2
#घोषणा RT5677_PWR_PDM2				(0x1 << 1)
#घोषणा RT5677_PWR_PDM2_BIT			1

/* Power Management क्रम Analog 1 (0x63) */
#घोषणा RT5677_PWR_VREF1			(0x1 << 15)
#घोषणा RT5677_PWR_VREF1_BIT			15
#घोषणा RT5677_PWR_FV1				(0x1 << 14)
#घोषणा RT5677_PWR_FV1_BIT			14
#घोषणा RT5677_PWR_MB				(0x1 << 13)
#घोषणा RT5677_PWR_MB_BIT			13
#घोषणा RT5677_PWR_LO1				(0x1 << 12)
#घोषणा RT5677_PWR_LO1_BIT			12
#घोषणा RT5677_PWR_BG				(0x1 << 11)
#घोषणा RT5677_PWR_BG_BIT			11
#घोषणा RT5677_PWR_LO2				(0x1 << 10)
#घोषणा RT5677_PWR_LO2_BIT			10
#घोषणा RT5677_PWR_LO3				(0x1 << 9)
#घोषणा RT5677_PWR_LO3_BIT			9
#घोषणा RT5677_PWR_VREF2			(0x1 << 8)
#घोषणा RT5677_PWR_VREF2_BIT			8
#घोषणा RT5677_PWR_FV2				(0x1 << 7)
#घोषणा RT5677_PWR_FV2_BIT			7
#घोषणा RT5677_LDO2_SEL_MASK			(0x7 << 4)
#घोषणा RT5677_LDO2_SEL_SFT			4
#घोषणा RT5677_LDO1_SEL_MASK			(0x7 << 0)
#घोषणा RT5677_LDO1_SEL_SFT			0

/* Power Management क्रम Analog 2 (0x64) */
#घोषणा RT5677_PWR_BST1				(0x1 << 15)
#घोषणा RT5677_PWR_BST1_BIT			15
#घोषणा RT5677_PWR_BST2				(0x1 << 14)
#घोषणा RT5677_PWR_BST2_BIT			14
#घोषणा RT5677_PWR_CLK_MB1			(0x1 << 13)
#घोषणा RT5677_PWR_CLK_MB1_BIT			13
#घोषणा RT5677_PWR_SLIM				(0x1 << 12)
#घोषणा RT5677_PWR_SLIM_BIT			12
#घोषणा RT5677_PWR_MB1				(0x1 << 11)
#घोषणा RT5677_PWR_MB1_BIT			11
#घोषणा RT5677_PWR_PP_MB1			(0x1 << 10)
#घोषणा RT5677_PWR_PP_MB1_BIT			10
#घोषणा RT5677_PWR_PLL1				(0x1 << 9)
#घोषणा RT5677_PWR_PLL1_BIT			9
#घोषणा RT5677_PWR_PLL2				(0x1 << 8)
#घोषणा RT5677_PWR_PLL2_BIT			8
#घोषणा RT5677_PWR_CORE				(0x1 << 7)
#घोषणा RT5677_PWR_CORE_BIT			7
#घोषणा RT5677_PWR_CLK_MB			(0x1 << 6)
#घोषणा RT5677_PWR_CLK_MB_BIT			6
#घोषणा RT5677_PWR_BST1_P			(0x1 << 5)
#घोषणा RT5677_PWR_BST1_P_BIT			5
#घोषणा RT5677_PWR_BST2_P			(0x1 << 4)
#घोषणा RT5677_PWR_BST2_P_BIT			4
#घोषणा RT5677_PWR_IPTV				(0x1 << 3)
#घोषणा RT5677_PWR_IPTV_BIT			3
#घोषणा RT5677_PWR_25M_CLK			(0x1 << 1)
#घोषणा RT5677_PWR_25M_CLK_BIT			1
#घोषणा RT5677_PWR_LDO1				(0x1 << 0)
#घोषणा RT5677_PWR_LDO1_BIT			0

/* Power Management क्रम DSP (0x65) */
#घोषणा RT5677_PWR_SR7				(0x1 << 10)
#घोषणा RT5677_PWR_SR7_BIT			10
#घोषणा RT5677_PWR_SR6				(0x1 << 9)
#घोषणा RT5677_PWR_SR6_BIT			9
#घोषणा RT5677_PWR_SR5				(0x1 << 8)
#घोषणा RT5677_PWR_SR5_BIT			8
#घोषणा RT5677_PWR_SR4				(0x1 << 7)
#घोषणा RT5677_PWR_SR4_BIT			7
#घोषणा RT5677_PWR_SR3				(0x1 << 6)
#घोषणा RT5677_PWR_SR3_BIT			6
#घोषणा RT5677_PWR_SR2				(0x1 << 5)
#घोषणा RT5677_PWR_SR2_BIT			5
#घोषणा RT5677_PWR_SR1				(0x1 << 4)
#घोषणा RT5677_PWR_SR1_BIT			4
#घोषणा RT5677_PWR_SR0				(0x1 << 3)
#घोषणा RT5677_PWR_SR0_BIT			3
#घोषणा RT5677_PWR_MLT				(0x1 << 2)
#घोषणा RT5677_PWR_MLT_BIT			2
#घोषणा RT5677_PWR_DSP				(0x1 << 1)
#घोषणा RT5677_PWR_DSP_BIT			1
#घोषणा RT5677_PWR_DSP_CPU			(0x1 << 0)
#घोषणा RT5677_PWR_DSP_CPU_BIT			0

/* Power Status क्रम DSP (0x66) */
#घोषणा RT5677_PWR_SR7_RDY			(0x1 << 9)
#घोषणा RT5677_PWR_SR7_RDY_BIT			9
#घोषणा RT5677_PWR_SR6_RDY			(0x1 << 8)
#घोषणा RT5677_PWR_SR6_RDY_BIT			8
#घोषणा RT5677_PWR_SR5_RDY			(0x1 << 7)
#घोषणा RT5677_PWR_SR5_RDY_BIT			7
#घोषणा RT5677_PWR_SR4_RDY			(0x1 << 6)
#घोषणा RT5677_PWR_SR4_RDY_BIT			6
#घोषणा RT5677_PWR_SR3_RDY			(0x1 << 5)
#घोषणा RT5677_PWR_SR3_RDY_BIT			5
#घोषणा RT5677_PWR_SR2_RDY			(0x1 << 4)
#घोषणा RT5677_PWR_SR2_RDY_BIT			4
#घोषणा RT5677_PWR_SR1_RDY			(0x1 << 3)
#घोषणा RT5677_PWR_SR1_RDY_BIT			3
#घोषणा RT5677_PWR_SR0_RDY			(0x1 << 2)
#घोषणा RT5677_PWR_SR0_RDY_BIT			2
#घोषणा RT5677_PWR_MLT_RDY			(0x1 << 1)
#घोषणा RT5677_PWR_MLT_RDY_BIT			1
#घोषणा RT5677_PWR_DSP_RDY			(0x1 << 0)
#घोषणा RT5677_PWR_DSP_RDY_BIT			0

/* Power Management क्रम DSP (0x67) */
#घोषणा RT5677_PWR_SLIM_ISO			(0x1 << 11)
#घोषणा RT5677_PWR_SLIM_ISO_BIT			11
#घोषणा RT5677_PWR_CORE_ISO			(0x1 << 10)
#घोषणा RT5677_PWR_CORE_ISO_BIT			10
#घोषणा RT5677_PWR_DSP_ISO			(0x1 << 9)
#घोषणा RT5677_PWR_DSP_ISO_BIT			9
#घोषणा RT5677_PWR_SR7_ISO			(0x1 << 8)
#घोषणा RT5677_PWR_SR7_ISO_BIT			8
#घोषणा RT5677_PWR_SR6_ISO			(0x1 << 7)
#घोषणा RT5677_PWR_SR6_ISO_BIT			7
#घोषणा RT5677_PWR_SR5_ISO			(0x1 << 6)
#घोषणा RT5677_PWR_SR5_ISO_BIT			6
#घोषणा RT5677_PWR_SR4_ISO			(0x1 << 5)
#घोषणा RT5677_PWR_SR4_ISO_BIT			5
#घोषणा RT5677_PWR_SR3_ISO			(0x1 << 4)
#घोषणा RT5677_PWR_SR3_ISO_BIT			4
#घोषणा RT5677_PWR_SR2_ISO			(0x1 << 3)
#घोषणा RT5677_PWR_SR2_ISO_BIT			3
#घोषणा RT5677_PWR_SR1_ISO			(0x1 << 2)
#घोषणा RT5677_PWR_SR1_ISO_BIT			2
#घोषणा RT5677_PWR_SR0_ISO			(0x1 << 1)
#घोषणा RT5677_PWR_SR0_ISO_BIT			1
#घोषणा RT5677_PWR_MLT_ISO			(0x1 << 0)
#घोषणा RT5677_PWR_MLT_ISO_BIT			0

/* I2S1/2/3/4 Audio Serial Data Port Control (0x6f 0x70 0x71 0x72) */
#घोषणा RT5677_I2S_MS_MASK			(0x1 << 15)
#घोषणा RT5677_I2S_MS_SFT			15
#घोषणा RT5677_I2S_MS_M				(0x0 << 15)
#घोषणा RT5677_I2S_MS_S				(0x1 << 15)
#घोषणा RT5677_I2S_O_CP_MASK			(0x3 << 10)
#घोषणा RT5677_I2S_O_CP_SFT			10
#घोषणा RT5677_I2S_O_CP_OFF			(0x0 << 10)
#घोषणा RT5677_I2S_O_CP_U_LAW			(0x1 << 10)
#घोषणा RT5677_I2S_O_CP_A_LAW			(0x2 << 10)
#घोषणा RT5677_I2S_I_CP_MASK			(0x3 << 8)
#घोषणा RT5677_I2S_I_CP_SFT			8
#घोषणा RT5677_I2S_I_CP_OFF			(0x0 << 8)
#घोषणा RT5677_I2S_I_CP_U_LAW			(0x1 << 8)
#घोषणा RT5677_I2S_I_CP_A_LAW			(0x2 << 8)
#घोषणा RT5677_I2S_BP_MASK			(0x1 << 7)
#घोषणा RT5677_I2S_BP_SFT			7
#घोषणा RT5677_I2S_BP_NOR			(0x0 << 7)
#घोषणा RT5677_I2S_BP_INV			(0x1 << 7)
#घोषणा RT5677_I2S_DL_MASK			(0x3 << 2)
#घोषणा RT5677_I2S_DL_SFT			2
#घोषणा RT5677_I2S_DL_16			(0x0 << 2)
#घोषणा RT5677_I2S_DL_20			(0x1 << 2)
#घोषणा RT5677_I2S_DL_24			(0x2 << 2)
#घोषणा RT5677_I2S_DL_8				(0x3 << 2)
#घोषणा RT5677_I2S_DF_MASK			(0x3 << 0)
#घोषणा RT5677_I2S_DF_SFT			0
#घोषणा RT5677_I2S_DF_I2S			(0x0 << 0)
#घोषणा RT5677_I2S_DF_LEFT			(0x1 << 0)
#घोषणा RT5677_I2S_DF_PCM_A			(0x2 << 0)
#घोषणा RT5677_I2S_DF_PCM_B			(0x3 << 0)

/* Clock Tree Control 1 (0x73) */
#घोषणा RT5677_I2S_PD1_MASK			(0x7 << 12)
#घोषणा RT5677_I2S_PD1_SFT			12
#घोषणा RT5677_I2S_PD1_1			(0x0 << 12)
#घोषणा RT5677_I2S_PD1_2			(0x1 << 12)
#घोषणा RT5677_I2S_PD1_3			(0x2 << 12)
#घोषणा RT5677_I2S_PD1_4			(0x3 << 12)
#घोषणा RT5677_I2S_PD1_6			(0x4 << 12)
#घोषणा RT5677_I2S_PD1_8			(0x5 << 12)
#घोषणा RT5677_I2S_PD1_12			(0x6 << 12)
#घोषणा RT5677_I2S_PD1_16			(0x7 << 12)
#घोषणा RT5677_I2S_BCLK_MS2_MASK		(0x1 << 11)
#घोषणा RT5677_I2S_BCLK_MS2_SFT			11
#घोषणा RT5677_I2S_BCLK_MS2_32			(0x0 << 11)
#घोषणा RT5677_I2S_BCLK_MS2_64			(0x1 << 11)
#घोषणा RT5677_I2S_PD2_MASK			(0x7 << 8)
#घोषणा RT5677_I2S_PD2_SFT			8
#घोषणा RT5677_I2S_PD2_1			(0x0 << 8)
#घोषणा RT5677_I2S_PD2_2			(0x1 << 8)
#घोषणा RT5677_I2S_PD2_3			(0x2 << 8)
#घोषणा RT5677_I2S_PD2_4			(0x3 << 8)
#घोषणा RT5677_I2S_PD2_6			(0x4 << 8)
#घोषणा RT5677_I2S_PD2_8			(0x5 << 8)
#घोषणा RT5677_I2S_PD2_12			(0x6 << 8)
#घोषणा RT5677_I2S_PD2_16			(0x7 << 8)
#घोषणा RT5677_I2S_BCLK_MS3_MASK		(0x1 << 7)
#घोषणा RT5677_I2S_BCLK_MS3_SFT			7
#घोषणा RT5677_I2S_BCLK_MS3_32			(0x0 << 7)
#घोषणा RT5677_I2S_BCLK_MS3_64			(0x1 << 7)
#घोषणा RT5677_I2S_PD3_MASK			(0x7 << 4)
#घोषणा RT5677_I2S_PD3_SFT			4
#घोषणा RT5677_I2S_PD3_1			(0x0 << 4)
#घोषणा RT5677_I2S_PD3_2			(0x1 << 4)
#घोषणा RT5677_I2S_PD3_3			(0x2 << 4)
#घोषणा RT5677_I2S_PD3_4			(0x3 << 4)
#घोषणा RT5677_I2S_PD3_6			(0x4 << 4)
#घोषणा RT5677_I2S_PD3_8			(0x5 << 4)
#घोषणा RT5677_I2S_PD3_12			(0x6 << 4)
#घोषणा RT5677_I2S_PD3_16			(0x7 << 4)
#घोषणा RT5677_I2S_BCLK_MS4_MASK		(0x1 << 3)
#घोषणा RT5677_I2S_BCLK_MS4_SFT			3
#घोषणा RT5677_I2S_BCLK_MS4_32			(0x0 << 3)
#घोषणा RT5677_I2S_BCLK_MS4_64			(0x1 << 3)
#घोषणा RT5677_I2S_PD4_MASK			(0x7 << 0)
#घोषणा RT5677_I2S_PD4_SFT			0
#घोषणा RT5677_I2S_PD4_1			(0x0 << 0)
#घोषणा RT5677_I2S_PD4_2			(0x1 << 0)
#घोषणा RT5677_I2S_PD4_3			(0x2 << 0)
#घोषणा RT5677_I2S_PD4_4			(0x3 << 0)
#घोषणा RT5677_I2S_PD4_6			(0x4 << 0)
#घोषणा RT5677_I2S_PD4_8			(0x5 << 0)
#घोषणा RT5677_I2S_PD4_12			(0x6 << 0)
#घोषणा RT5677_I2S_PD4_16			(0x7 << 0)

/* Clock Tree Control 2 (0x74) */
#घोषणा RT5677_I2S_PD5_MASK			(0x7 << 12)
#घोषणा RT5677_I2S_PD5_SFT			12
#घोषणा RT5677_I2S_PD5_1			(0x0 << 12)
#घोषणा RT5677_I2S_PD5_2			(0x1 << 12)
#घोषणा RT5677_I2S_PD5_3			(0x2 << 12)
#घोषणा RT5677_I2S_PD5_4			(0x3 << 12)
#घोषणा RT5677_I2S_PD5_6			(0x4 << 12)
#घोषणा RT5677_I2S_PD5_8			(0x5 << 12)
#घोषणा RT5677_I2S_PD5_12			(0x6 << 12)
#घोषणा RT5677_I2S_PD5_16			(0x7 << 12)
#घोषणा RT5677_I2S_PD6_MASK			(0x7 << 8)
#घोषणा RT5677_I2S_PD6_SFT			8
#घोषणा RT5677_I2S_PD6_1			(0x0 << 8)
#घोषणा RT5677_I2S_PD6_2			(0x1 << 8)
#घोषणा RT5677_I2S_PD6_3			(0x2 << 8)
#घोषणा RT5677_I2S_PD6_4			(0x3 << 8)
#घोषणा RT5677_I2S_PD6_6			(0x4 << 8)
#घोषणा RT5677_I2S_PD6_8			(0x5 << 8)
#घोषणा RT5677_I2S_PD6_12			(0x6 << 8)
#घोषणा RT5677_I2S_PD6_16			(0x7 << 8)
#घोषणा RT5677_I2S_PD7_MASK			(0x7 << 4)
#घोषणा RT5677_I2S_PD7_SFT			4
#घोषणा RT5677_I2S_PD7_1			(0x0 << 4)
#घोषणा RT5677_I2S_PD7_2			(0x1 << 4)
#घोषणा RT5677_I2S_PD7_3			(0x2 << 4)
#घोषणा RT5677_I2S_PD7_4			(0x3 << 4)
#घोषणा RT5677_I2S_PD7_6			(0x4 << 4)
#घोषणा RT5677_I2S_PD7_8			(0x5 << 4)
#घोषणा RT5677_I2S_PD7_12			(0x6 << 4)
#घोषणा RT5677_I2S_PD7_16			(0x7 << 4)
#घोषणा RT5677_I2S_PD8_MASK			(0x7 << 0)
#घोषणा RT5677_I2S_PD8_SFT			0
#घोषणा RT5677_I2S_PD8_1			(0x0 << 0)
#घोषणा RT5677_I2S_PD8_2			(0x1 << 0)
#घोषणा RT5677_I2S_PD8_3			(0x2 << 0)
#घोषणा RT5677_I2S_PD8_4			(0x3 << 0)
#घोषणा RT5677_I2S_PD8_6			(0x4 << 0)
#घोषणा RT5677_I2S_PD8_8			(0x5 << 0)
#घोषणा RT5677_I2S_PD8_12			(0x6 << 0)
#घोषणा RT5677_I2S_PD8_16			(0x7 << 0)

/* Clock Tree Control 3 (0x75) */
#घोषणा RT5677_DSP_ASRC_O_MASK			(0x3 << 6)
#घोषणा RT5677_DSP_ASRC_O_SFT			6
#घोषणा RT5677_DSP_ASRC_O_1_0			(0x0 << 6)
#घोषणा RT5677_DSP_ASRC_O_1_5			(0x1 << 6)
#घोषणा RT5677_DSP_ASRC_O_2_0			(0x2 << 6)
#घोषणा RT5677_DSP_ASRC_O_3_0			(0x3 << 6)
#घोषणा RT5677_DSP_ASRC_I_MASK			(0x3 << 4)
#घोषणा RT5677_DSP_ASRC_I_SFT			4
#घोषणा RT5677_DSP_ASRC_I_1_0			(0x0 << 4)
#घोषणा RT5677_DSP_ASRC_I_1_5			(0x1 << 4)
#घोषणा RT5677_DSP_ASRC_I_2_0			(0x2 << 4)
#घोषणा RT5677_DSP_ASRC_I_3_0			(0x3 << 4)
#घोषणा RT5677_DSP_BUS_PD_MASK			(0x7 << 0)
#घोषणा RT5677_DSP_BUS_PD_SFT			0
#घोषणा RT5677_DSP_BUS_PD_1			(0x0 << 0)
#घोषणा RT5677_DSP_BUS_PD_2			(0x1 << 0)
#घोषणा RT5677_DSP_BUS_PD_3			(0x2 << 0)
#घोषणा RT5677_DSP_BUS_PD_4			(0x3 << 0)
#घोषणा RT5677_DSP_BUS_PD_6			(0x4 << 0)
#घोषणा RT5677_DSP_BUS_PD_8			(0x5 << 0)
#घोषणा RT5677_DSP_BUS_PD_12			(0x6 << 0)
#घोषणा RT5677_DSP_BUS_PD_16			(0x7 << 0)

#घोषणा RT5677_PLL_INP_MAX			40000000
#घोषणा RT5677_PLL_INP_MIN			2048000
/* PLL M/N/K Code Control 1 (0x7a 0x7c) */
#घोषणा RT5677_PLL_N_MAX			0x1ff
#घोषणा RT5677_PLL_N_MASK			(RT5677_PLL_N_MAX << 7)
#घोषणा RT5677_PLL_N_SFT			7
#घोषणा RT5677_PLL_K_BP				(0x1 << 5)
#घोषणा RT5677_PLL_K_BP_SFT			5
#घोषणा RT5677_PLL_K_MAX			0x1f
#घोषणा RT5677_PLL_K_MASK			(RT5677_PLL_K_MAX)
#घोषणा RT5677_PLL_K_SFT			0

/* PLL M/N/K Code Control 2 (0x7b 0x7d) */
#घोषणा RT5677_PLL_M_MAX			0xf
#घोषणा RT5677_PLL_M_MASK			(RT5677_PLL_M_MAX << 12)
#घोषणा RT5677_PLL_M_SFT			12
#घोषणा RT5677_PLL_M_BP				(0x1 << 11)
#घोषणा RT5677_PLL_M_BP_SFT			11
#घोषणा RT5677_PLL_UPDATE_PLL1			(0x1 << 1)
#घोषणा RT5677_PLL_UPDATE_PLL1_SFT		1

/* Global Clock Control 1 (0x80) */
#घोषणा RT5677_SCLK_SRC_MASK			(0x3 << 14)
#घोषणा RT5677_SCLK_SRC_SFT			14
#घोषणा RT5677_SCLK_SRC_MCLK			(0x0 << 14)
#घोषणा RT5677_SCLK_SRC_PLL1			(0x1 << 14)
#घोषणा RT5677_SCLK_SRC_RCCLK			(0x2 << 14) /* 25MHz */
#घोषणा RT5677_SCLK_SRC_SLIM			(0x3 << 14)
#घोषणा RT5677_PLL1_SRC_MASK			(0x7 << 11)
#घोषणा RT5677_PLL1_SRC_SFT			11
#घोषणा RT5677_PLL1_SRC_MCLK			(0x0 << 11)
#घोषणा RT5677_PLL1_SRC_BCLK1			(0x1 << 11)
#घोषणा RT5677_PLL1_SRC_BCLK2			(0x2 << 11)
#घोषणा RT5677_PLL1_SRC_BCLK3			(0x3 << 11)
#घोषणा RT5677_PLL1_SRC_BCLK4			(0x4 << 11)
#घोषणा RT5677_PLL1_SRC_RCCLK			(0x5 << 11)
#घोषणा RT5677_PLL1_SRC_SLIM			(0x6 << 11)
#घोषणा RT5677_MCLK_SRC_MASK			(0x1 << 10)
#घोषणा RT5677_MCLK_SRC_SFT			10
#घोषणा RT5677_MCLK1_SRC			(0x0 << 10)
#घोषणा RT5677_MCLK2_SRC			(0x1 << 10)
#घोषणा RT5677_PLL1_PD_MASK			(0x1 << 8)
#घोषणा RT5677_PLL1_PD_SFT			8
#घोषणा RT5677_PLL1_PD_1			(0x0 << 8)
#घोषणा RT5677_PLL1_PD_2			(0x1 << 8)
#घोषणा RT5677_DAC_OSR_MASK			(0x3 << 6)
#घोषणा RT5677_DAC_OSR_SFT			6
#घोषणा RT5677_DAC_OSR_128			(0x0 << 6)
#घोषणा RT5677_DAC_OSR_64			(0x1 << 6)
#घोषणा RT5677_DAC_OSR_32			(0x2 << 6)
#घोषणा RT5677_ADC_OSR_MASK			(0x3 << 4)
#घोषणा RT5677_ADC_OSR_SFT			4
#घोषणा RT5677_ADC_OSR_128			(0x0 << 4)
#घोषणा RT5677_ADC_OSR_64			(0x1 << 4)
#घोषणा RT5677_ADC_OSR_32			(0x2 << 4)

/* Global Clock Control 2 (0x81) */
#घोषणा RT5677_PLL2_PR_SRC_MASK			(0x1 << 15)
#घोषणा RT5677_PLL2_PR_SRC_SFT			15
#घोषणा RT5677_PLL2_PR_SRC_MCLK1		(0x0 << 15)
#घोषणा RT5677_PLL2_PR_SRC_MCLK2		(0x1 << 15)
#घोषणा RT5677_PLL2_SRC_MASK			(0x7 << 12)
#घोषणा RT5677_PLL2_SRC_SFT			12
#घोषणा RT5677_PLL2_SRC_MCLK			(0x0 << 12)
#घोषणा RT5677_PLL2_SRC_BCLK1			(0x1 << 12)
#घोषणा RT5677_PLL2_SRC_BCLK2			(0x2 << 12)
#घोषणा RT5677_PLL2_SRC_BCLK3			(0x3 << 12)
#घोषणा RT5677_PLL2_SRC_BCLK4			(0x4 << 12)
#घोषणा RT5677_PLL2_SRC_RCCLK			(0x5 << 12)
#घोषणा RT5677_PLL2_SRC_SLIM			(0x6 << 12)
#घोषणा RT5677_DSP_ASRC_O_SRC			(0x3 << 10)
#घोषणा RT5677_DSP_ASRC_O_SRC_SFT		10
#घोषणा RT5677_DSP_ASRC_O_MCLK			(0x0 << 10)
#घोषणा RT5677_DSP_ASRC_O_PLL1			(0x1 << 10)
#घोषणा RT5677_DSP_ASRC_O_SLIM			(0x2 << 10)
#घोषणा RT5677_DSP_ASRC_O_RCCLK			(0x3 << 10)
#घोषणा RT5677_DSP_ASRC_I_SRC			(0x3 << 8)
#घोषणा RT5677_DSP_ASRC_I_SRC_SFT		8
#घोषणा RT5677_DSP_ASRC_I_MCLK			(0x0 << 8)
#घोषणा RT5677_DSP_ASRC_I_PLL1			(0x1 << 8)
#घोषणा RT5677_DSP_ASRC_I_SLIM			(0x2 << 8)
#घोषणा RT5677_DSP_ASRC_I_RCCLK			(0x3 << 8)
#घोषणा RT5677_DSP_CLK_SRC_MASK			(0x1 << 7)
#घोषणा RT5677_DSP_CLK_SRC_SFT			7
#घोषणा RT5677_DSP_CLK_SRC_PLL2			(0x0 << 7)
#घोषणा RT5677_DSP_CLK_SRC_BYPASS		(0x1 << 7)

/* ASRC Control 3 (0x85) */
#घोषणा RT5677_DA_STO_CLK_SEL_MASK		(0xf << 12)
#घोषणा RT5677_DA_STO_CLK_SEL_SFT		12
#घोषणा RT5677_DA_MONO2L_CLK_SEL_MASK		(0xf << 4)
#घोषणा RT5677_DA_MONO2L_CLK_SEL_SFT		4
#घोषणा RT5677_DA_MONO2R_CLK_SEL_MASK		(0xf << 0)
#घोषणा RT5677_DA_MONO2R_CLK_SEL_SFT		0

/* ASRC Control 4 (0x86) */
#घोषणा RT5677_DA_MONO3L_CLK_SEL_MASK		(0xf << 12)
#घोषणा RT5677_DA_MONO3L_CLK_SEL_SFT		12
#घोषणा RT5677_DA_MONO3R_CLK_SEL_MASK		(0xf << 8)
#घोषणा RT5677_DA_MONO3R_CLK_SEL_SFT		8
#घोषणा RT5677_DA_MONO4L_CLK_SEL_MASK		(0xf << 4)
#घोषणा RT5677_DA_MONO4L_CLK_SEL_SFT		4
#घोषणा RT5677_DA_MONO4R_CLK_SEL_MASK		(0xf << 0)
#घोषणा RT5677_DA_MONO4R_CLK_SEL_SFT		0

/* ASRC Control 5 (0x87) */
#घोषणा RT5677_AD_STO1_CLK_SEL_MASK		(0xf << 12)
#घोषणा RT5677_AD_STO1_CLK_SEL_SFT		12
#घोषणा RT5677_AD_STO2_CLK_SEL_MASK		(0xf << 8)
#घोषणा RT5677_AD_STO2_CLK_SEL_SFT		8
#घोषणा RT5677_AD_STO3_CLK_SEL_MASK		(0xf << 4)
#घोषणा RT5677_AD_STO3_CLK_SEL_SFT		4
#घोषणा RT5677_AD_STO4_CLK_SEL_MASK		(0xf << 0)
#घोषणा RT5677_AD_STO4_CLK_SEL_SFT		0

/* ASRC Control 6 (0x88) */
#घोषणा RT5677_AD_MONOL_CLK_SEL_MASK		(0xf << 12)
#घोषणा RT5677_AD_MONOL_CLK_SEL_SFT		12
#घोषणा RT5677_AD_MONOR_CLK_SEL_MASK		(0xf << 8)
#घोषणा RT5677_AD_MONOR_CLK_SEL_SFT		8

/* ASRC Control 7 (0x89) */
#घोषणा RT5677_DSP_OB_0_3_CLK_SEL_MASK		(0xf << 12)
#घोषणा RT5677_DSP_OB_0_3_CLK_SEL_SFT		12
#घोषणा RT5677_DSP_OB_4_7_CLK_SEL_MASK		(0xf << 8)
#घोषणा RT5677_DSP_OB_4_7_CLK_SEL_SFT		8

/* ASRC Control 8 (0x8a) */
#घोषणा RT5677_I2S1_CLK_SEL_MASK		(0xf << 12)
#घोषणा RT5677_I2S1_CLK_SEL_SFT			12
#घोषणा RT5677_I2S2_CLK_SEL_MASK		(0xf << 8)
#घोषणा RT5677_I2S2_CLK_SEL_SFT			8
#घोषणा RT5677_I2S3_CLK_SEL_MASK		(0xf << 4)
#घोषणा RT5677_I2S3_CLK_SEL_SFT			4
#घोषणा RT5677_I2S4_CLK_SEL_MASK		(0xf)
#घोषणा RT5677_I2S4_CLK_SEL_SFT			0

/* VAD Function Control 1 (0x9c) */
#घोषणा RT5677_VAD_MIN_DUR_MASK			(0x3 << 13)
#घोषणा RT5677_VAD_MIN_DUR_SFT			13
#घोषणा RT5677_VAD_ADPCM_BYPASS			(1 << 10)
#घोषणा RT5677_VAD_ADPCM_BYPASS_BIT		10
#घोषणा RT5677_VAD_FG2ENC			(1 << 9)
#घोषणा RT5677_VAD_FG2ENC_BIT			9
#घोषणा RT5677_VAD_BUF_OW			(1 << 8)
#घोषणा RT5677_VAD_BUF_OW_BIT			8
#घोषणा RT5677_VAD_CLR_FLAG			(1 << 7)
#घोषणा RT5677_VAD_CLR_FLAG_BIT			7
#घोषणा RT5677_VAD_BUF_POP			(1 << 6)
#घोषणा RT5677_VAD_BUF_POP_BIT			6
#घोषणा RT5677_VAD_BUF_PUSH			(1 << 5)
#घोषणा RT5677_VAD_BUF_PUSH_BIT			5
#घोषणा RT5677_VAD_DET_ENABLE			(1 << 4)
#घोषणा RT5677_VAD_DET_ENABLE_BIT		4
#घोषणा RT5677_VAD_FUNC_ENABLE			(1 << 3)
#घोषणा RT5677_VAD_FUNC_ENABLE_BIT		3
#घोषणा RT5677_VAD_FUNC_RESET			(1 << 2)
#घोषणा RT5677_VAD_FUNC_RESET_BIT		2

/* VAD Function Control 4 (0x9f) */
#घोषणा RT5677_VAD_OUT_SRC_RATE_MASK		(0x1 << 11)
#घोषणा RT5677_VAD_OUT_SRC_RATE_SFT		11
#घोषणा RT5677_VAD_OUT_SRC_MASK			(0x1 << 10)
#घोषणा RT5677_VAD_OUT_SRC_SFT			10
#घोषणा RT5677_VAD_SRC_MASK			(0x3 << 8)
#घोषणा RT5677_VAD_SRC_SFT			8
#घोषणा RT5677_VAD_LV_DIFF_MASK			(0xff << 0)
#घोषणा RT5677_VAD_LV_DIFF_SFT			0

/* DSP InBound Control (0xa3) */
#घोषणा RT5677_IB01_SRC_MASK			(0x7 << 12)
#घोषणा RT5677_IB01_SRC_SFT			12
#घोषणा RT5677_IB23_SRC_MASK			(0x7 << 8)
#घोषणा RT5677_IB23_SRC_SFT			8
#घोषणा RT5677_IB45_SRC_MASK			(0x7 << 4)
#घोषणा RT5677_IB45_SRC_SFT			4
#घोषणा RT5677_IB6_SRC_MASK			(0x7 << 0)
#घोषणा RT5677_IB6_SRC_SFT			0

/* DSP InBound Control (0xa4) */
#घोषणा RT5677_IB7_SRC_MASK			(0x7 << 12)
#घोषणा RT5677_IB7_SRC_SFT			12
#घोषणा RT5677_IB8_SRC_MASK			(0x7 << 8)
#घोषणा RT5677_IB8_SRC_SFT			8
#घोषणा RT5677_IB9_SRC_MASK			(0x7 << 4)
#घोषणा RT5677_IB9_SRC_SFT			4

/* DSP In/OutBound Control (0xa5) */
#घोषणा RT5677_SEL_SRC_OB23			(0x1 << 4)
#घोषणा RT5677_SEL_SRC_OB23_SFT			4
#घोषणा RT5677_SEL_SRC_OB01			(0x1 << 3)
#घोषणा RT5677_SEL_SRC_OB01_SFT			3
#घोषणा RT5677_SEL_SRC_IB45			(0x1 << 2)
#घोषणा RT5677_SEL_SRC_IB45_SFT			2
#घोषणा RT5677_SEL_SRC_IB23			(0x1 << 1)
#घोषणा RT5677_SEL_SRC_IB23_SFT			1
#घोषणा RT5677_SEL_SRC_IB01			(0x1 << 0)
#घोषणा RT5677_SEL_SRC_IB01_SFT			0

/* Jack Detect Control 1 (0xb5) */
#घोषणा RT5677_SEL_GPIO_JD1_MASK		(0x3 << 14)
#घोषणा RT5677_SEL_GPIO_JD1_SFT			14
#घोषणा RT5677_SEL_GPIO_JD2_MASK		(0x3 << 12)
#घोषणा RT5677_SEL_GPIO_JD2_SFT			12
#घोषणा RT5677_SEL_GPIO_JD3_MASK		(0x3 << 10)
#घोषणा RT5677_SEL_GPIO_JD3_SFT			10

/* IRQ Control 1 (0xbd) */
#घोषणा RT5677_STA_GPIO_JD1			(0x1 << 15)
#घोषणा RT5677_STA_GPIO_JD1_SFT			15
#घोषणा RT5677_EN_IRQ_GPIO_JD1			(0x1 << 14)
#घोषणा RT5677_EN_IRQ_GPIO_JD1_SFT		14
#घोषणा RT5677_EN_GPIO_JD1_STICKY		(0x1 << 13)
#घोषणा RT5677_EN_GPIO_JD1_STICKY_SFT		13
#घोषणा RT5677_INV_GPIO_JD1			(0x1 << 12)
#घोषणा RT5677_INV_GPIO_JD1_SFT			12
#घोषणा RT5677_STA_GPIO_JD2			(0x1 << 11)
#घोषणा RT5677_STA_GPIO_JD2_SFT			11
#घोषणा RT5677_EN_IRQ_GPIO_JD2			(0x1 << 10)
#घोषणा RT5677_EN_IRQ_GPIO_JD2_SFT		10
#घोषणा RT5677_EN_GPIO_JD2_STICKY		(0x1 << 9)
#घोषणा RT5677_EN_GPIO_JD2_STICKY_SFT		9
#घोषणा RT5677_INV_GPIO_JD2			(0x1 << 8)
#घोषणा RT5677_INV_GPIO_JD2_SFT			8
#घोषणा RT5677_STA_MICBIAS1_OVCD		(0x1 << 7)
#घोषणा RT5677_STA_MICBIAS1_OVCD_SFT		7
#घोषणा RT5677_EN_IRQ_MICBIAS1_OVCD		(0x1 << 6)
#घोषणा RT5677_EN_IRQ_MICBIAS1_OVCD_SFT		6
#घोषणा RT5677_EN_MICBIAS1_OVCD_STICKY		(0x1 << 5)
#घोषणा RT5677_EN_MICBIAS1_OVCD_STICKY_SFT	5
#घोषणा RT5677_INV_MICBIAS1_OVCD		(0x1 << 4)
#घोषणा RT5677_INV_MICBIAS1_OVCD_SFT		4
#घोषणा RT5677_STA_GPIO_JD3			(0x1 << 3)
#घोषणा RT5677_STA_GPIO_JD3_SFT			3
#घोषणा RT5677_EN_IRQ_GPIO_JD3			(0x1 << 2)
#घोषणा RT5677_EN_IRQ_GPIO_JD3_SFT		2
#घोषणा RT5677_EN_GPIO_JD3_STICKY		(0x1 << 1)
#घोषणा RT5677_EN_GPIO_JD3_STICKY_SFT		1
#घोषणा RT5677_INV_GPIO_JD3			(0x1 << 0)
#घोषणा RT5677_INV_GPIO_JD3_SFT			0

/* GPIO status (0xbf) */
#घोषणा RT5677_GPIO6_STATUS_MASK		(0x1 << 5)
#घोषणा RT5677_GPIO6_STATUS_SFT			5
#घोषणा RT5677_GPIO5_STATUS_MASK		(0x1 << 4)
#घोषणा RT5677_GPIO5_STATUS_SFT			4
#घोषणा RT5677_GPIO4_STATUS_MASK		(0x1 << 3)
#घोषणा RT5677_GPIO4_STATUS_SFT			3
#घोषणा RT5677_GPIO3_STATUS_MASK		(0x1 << 2)
#घोषणा RT5677_GPIO3_STATUS_SFT			2
#घोषणा RT5677_GPIO2_STATUS_MASK		(0x1 << 1)
#घोषणा RT5677_GPIO2_STATUS_SFT			1
#घोषणा RT5677_GPIO1_STATUS_MASK		(0x1 << 0)
#घोषणा RT5677_GPIO1_STATUS_SFT			0

/* GPIO Control 1 (0xc0) */
#घोषणा RT5677_GPIO1_PIN_MASK			(0x1 << 15)
#घोषणा RT5677_GPIO1_PIN_SFT			15
#घोषणा RT5677_GPIO1_PIN_GPIO1			(0x0 << 15)
#घोषणा RT5677_GPIO1_PIN_IRQ			(0x1 << 15)
#घोषणा RT5677_IPTV_MODE_MASK			(0x1 << 14)
#घोषणा RT5677_IPTV_MODE_SFT			14
#घोषणा RT5677_IPTV_MODE_GPIO			(0x0 << 14)
#घोषणा RT5677_IPTV_MODE_IPTV			(0x1 << 14)
#घोषणा RT5677_FUNC_MODE_MASK			(0x1 << 13)
#घोषणा RT5677_FUNC_MODE_SFT			13
#घोषणा RT5677_FUNC_MODE_DMIC_GPIO		(0x0 << 13)
#घोषणा RT5677_FUNC_MODE_JTAG			(0x1 << 13)

/* GPIO Control 2 (0xc1) */
#घोषणा RT5677_GPIO5_सूची_MASK			(0x1 << 14)
#घोषणा RT5677_GPIO5_सूची_SFT			14
#घोषणा RT5677_GPIO5_सूची_IN			(0x0 << 14)
#घोषणा RT5677_GPIO5_सूची_OUT			(0x1 << 14)
#घोषणा RT5677_GPIO5_OUT_MASK			(0x1 << 13)
#घोषणा RT5677_GPIO5_OUT_SFT			13
#घोषणा RT5677_GPIO5_OUT_LO			(0x0 << 13)
#घोषणा RT5677_GPIO5_OUT_HI			(0x1 << 13)
#घोषणा RT5677_GPIO5_P_MASK			(0x1 << 12)
#घोषणा RT5677_GPIO5_P_SFT			12
#घोषणा RT5677_GPIO5_P_NOR			(0x0 << 12)
#घोषणा RT5677_GPIO5_P_INV			(0x1 << 12)
#घोषणा RT5677_GPIO4_सूची_MASK			(0x1 << 11)
#घोषणा RT5677_GPIO4_सूची_SFT			11
#घोषणा RT5677_GPIO4_सूची_IN			(0x0 << 11)
#घोषणा RT5677_GPIO4_सूची_OUT			(0x1 << 11)
#घोषणा RT5677_GPIO4_OUT_MASK			(0x1 << 10)
#घोषणा RT5677_GPIO4_OUT_SFT			10
#घोषणा RT5677_GPIO4_OUT_LO			(0x0 << 10)
#घोषणा RT5677_GPIO4_OUT_HI			(0x1 << 10)
#घोषणा RT5677_GPIO4_P_MASK			(0x1 << 9)
#घोषणा RT5677_GPIO4_P_SFT			9
#घोषणा RT5677_GPIO4_P_NOR			(0x0 << 9)
#घोषणा RT5677_GPIO4_P_INV			(0x1 << 9)
#घोषणा RT5677_GPIO3_सूची_MASK			(0x1 << 8)
#घोषणा RT5677_GPIO3_सूची_SFT			8
#घोषणा RT5677_GPIO3_सूची_IN			(0x0 << 8)
#घोषणा RT5677_GPIO3_सूची_OUT			(0x1 << 8)
#घोषणा RT5677_GPIO3_OUT_MASK			(0x1 << 7)
#घोषणा RT5677_GPIO3_OUT_SFT			7
#घोषणा RT5677_GPIO3_OUT_LO			(0x0 << 7)
#घोषणा RT5677_GPIO3_OUT_HI			(0x1 << 7)
#घोषणा RT5677_GPIO3_P_MASK			(0x1 << 6)
#घोषणा RT5677_GPIO3_P_SFT			6
#घोषणा RT5677_GPIO3_P_NOR			(0x0 << 6)
#घोषणा RT5677_GPIO3_P_INV			(0x1 << 6)
#घोषणा RT5677_GPIO2_सूची_MASK			(0x1 << 5)
#घोषणा RT5677_GPIO2_सूची_SFT			5
#घोषणा RT5677_GPIO2_सूची_IN			(0x0 << 5)
#घोषणा RT5677_GPIO2_सूची_OUT			(0x1 << 5)
#घोषणा RT5677_GPIO2_OUT_MASK			(0x1 << 4)
#घोषणा RT5677_GPIO2_OUT_SFT			4
#घोषणा RT5677_GPIO2_OUT_LO			(0x0 << 4)
#घोषणा RT5677_GPIO2_OUT_HI			(0x1 << 4)
#घोषणा RT5677_GPIO2_P_MASK			(0x1 << 3)
#घोषणा RT5677_GPIO2_P_SFT			3
#घोषणा RT5677_GPIO2_P_NOR			(0x0 << 3)
#घोषणा RT5677_GPIO2_P_INV			(0x1 << 3)
#घोषणा RT5677_GPIO1_सूची_MASK			(0x1 << 2)
#घोषणा RT5677_GPIO1_सूची_SFT			2
#घोषणा RT5677_GPIO1_सूची_IN			(0x0 << 2)
#घोषणा RT5677_GPIO1_सूची_OUT			(0x1 << 2)
#घोषणा RT5677_GPIO1_OUT_MASK			(0x1 << 1)
#घोषणा RT5677_GPIO1_OUT_SFT			1
#घोषणा RT5677_GPIO1_OUT_LO			(0x0 << 1)
#घोषणा RT5677_GPIO1_OUT_HI			(0x1 << 1)
#घोषणा RT5677_GPIO1_P_MASK			(0x1 << 0)
#घोषणा RT5677_GPIO1_P_SFT			0
#घोषणा RT5677_GPIO1_P_NOR			(0x0 << 0)
#घोषणा RT5677_GPIO1_P_INV			(0x1 << 0)

/* GPIO Control 3 (0xc2) */
#घोषणा RT5677_GPIO6_सूची_MASK			(0x1 << 2)
#घोषणा RT5677_GPIO6_सूची_SFT			2
#घोषणा RT5677_GPIO6_सूची_IN			(0x0 << 2)
#घोषणा RT5677_GPIO6_सूची_OUT			(0x1 << 2)
#घोषणा RT5677_GPIO6_OUT_MASK			(0x1 << 1)
#घोषणा RT5677_GPIO6_OUT_SFT			1
#घोषणा RT5677_GPIO6_OUT_LO			(0x0 << 1)
#घोषणा RT5677_GPIO6_OUT_HI			(0x1 << 1)
#घोषणा RT5677_GPIO6_P_MASK			(0x1 << 0)
#घोषणा RT5677_GPIO6_P_SFT			0
#घोषणा RT5677_GPIO6_P_NOR			(0x0 << 0)
#घोषणा RT5677_GPIO6_P_INV			(0x1 << 0)

/* General Control (0xfa) */
#घोषणा RT5677_IRQ_DEBOUNCE_SEL_MASK		(0x3 << 3)
#घोषणा RT5677_IRQ_DEBOUNCE_SEL_MCLK		(0x0 << 3)
#घोषणा RT5677_IRQ_DEBOUNCE_SEL_RC		(0x1 << 3)
#घोषणा RT5677_IRQ_DEBOUNCE_SEL_SLIM		(0x2 << 3)

/* Virtual DSP Mixer Control (0xf7 0xf8 0xf9) */
#घोषणा RT5677_DSP_IB_01_H			(0x1 << 15)
#घोषणा RT5677_DSP_IB_01_H_SFT			15
#घोषणा RT5677_DSP_IB_23_H			(0x1 << 14)
#घोषणा RT5677_DSP_IB_23_H_SFT			14
#घोषणा RT5677_DSP_IB_45_H			(0x1 << 13)
#घोषणा RT5677_DSP_IB_45_H_SFT			13
#घोषणा RT5677_DSP_IB_6_H			(0x1 << 12)
#घोषणा RT5677_DSP_IB_6_H_SFT			12
#घोषणा RT5677_DSP_IB_7_H			(0x1 << 11)
#घोषणा RT5677_DSP_IB_7_H_SFT			11
#घोषणा RT5677_DSP_IB_8_H			(0x1 << 10)
#घोषणा RT5677_DSP_IB_8_H_SFT			10
#घोषणा RT5677_DSP_IB_9_H			(0x1 << 9)
#घोषणा RT5677_DSP_IB_9_H_SFT			9
#घोषणा RT5677_DSP_IB_01_L			(0x1 << 7)
#घोषणा RT5677_DSP_IB_01_L_SFT			7
#घोषणा RT5677_DSP_IB_23_L			(0x1 << 6)
#घोषणा RT5677_DSP_IB_23_L_SFT			6
#घोषणा RT5677_DSP_IB_45_L			(0x1 << 5)
#घोषणा RT5677_DSP_IB_45_L_SFT			5
#घोषणा RT5677_DSP_IB_6_L			(0x1 << 4)
#घोषणा RT5677_DSP_IB_6_L_SFT			4
#घोषणा RT5677_DSP_IB_7_L			(0x1 << 3)
#घोषणा RT5677_DSP_IB_7_L_SFT			3
#घोषणा RT5677_DSP_IB_8_L			(0x1 << 2)
#घोषणा RT5677_DSP_IB_8_L_SFT			2
#घोषणा RT5677_DSP_IB_9_L			(0x1 << 1)
#घोषणा RT5677_DSP_IB_9_L_SFT			1

/* General Control2 (0xfc)*/
#घोषणा RT5677_GPIO5_FUNC_MASK			(0x1 << 9)
#घोषणा RT5677_GPIO5_FUNC_GPIO			(0x0 << 9)
#घोषणा RT5677_GPIO5_FUNC_DMIC			(0x1 << 9)

#घोषणा RT5677_FIRMWARE1	"rt5677_dsp_fw1.bin"
#घोषणा RT5677_FIRMWARE2	"rt5677_dsp_fw2.bin"

#घोषणा RT5677_DRV_NAME		"rt5677"

/* System Clock Source */
क्रमागत अणु
	RT5677_SCLK_S_MCLK,
	RT5677_SCLK_S_PLL1,
	RT5677_SCLK_S_RCCLK,
पूर्ण;

/* PLL1 Source */
क्रमागत अणु
	RT5677_PLL1_S_MCLK,
	RT5677_PLL1_S_BCLK1,
	RT5677_PLL1_S_BCLK2,
	RT5677_PLL1_S_BCLK3,
	RT5677_PLL1_S_BCLK4,
पूर्ण;

क्रमागत अणु
	RT5677_AIF1,
	RT5677_AIF2,
	RT5677_AIF3,
	RT5677_AIF4,
	RT5677_AIF5,
	RT5677_AIFS,
	RT5677_DSPBUFF,
पूर्ण;

क्रमागत अणु
	RT5677_GPIO1,
	RT5677_GPIO2,
	RT5677_GPIO3,
	RT5677_GPIO4,
	RT5677_GPIO5,
	RT5677_GPIO6,
	RT5677_GPIO_NUM,
पूर्ण;

क्रमागत अणु
	RT5677_IRQ_JD1,
	RT5677_IRQ_JD2,
	RT5677_IRQ_JD3,
	RT5677_IRQ_NUM,
पूर्ण;

क्रमागत rt5677_type अणु
	RT5677,
	RT5676,
पूर्ण;

/* ASRC घड़ी source selection */
क्रमागत अणु
	RT5677_CLK_SEL_SYS,
	RT5677_CLK_SEL_I2S1_ASRC,
	RT5677_CLK_SEL_I2S2_ASRC,
	RT5677_CLK_SEL_I2S3_ASRC,
	RT5677_CLK_SEL_I2S4_ASRC,
	RT5677_CLK_SEL_I2S5_ASRC,
	RT5677_CLK_SEL_I2S6_ASRC,
	RT5677_CLK_SEL_SYS2,
	RT5677_CLK_SEL_SYS3,
	RT5677_CLK_SEL_SYS4,
	RT5677_CLK_SEL_SYS5,
	RT5677_CLK_SEL_SYS6,
	RT5677_CLK_SEL_SYS7,
पूर्ण;

/* filter mask */
क्रमागत अणु
	RT5677_DA_STEREO_FILTER = 0x1,
	RT5677_DA_MONO2_L_FILTER = (0x1 << 1),
	RT5677_DA_MONO2_R_FILTER = (0x1 << 2),
	RT5677_DA_MONO3_L_FILTER = (0x1 << 3),
	RT5677_DA_MONO3_R_FILTER = (0x1 << 4),
	RT5677_DA_MONO4_L_FILTER = (0x1 << 5),
	RT5677_DA_MONO4_R_FILTER = (0x1 << 6),
	RT5677_AD_STEREO1_FILTER = (0x1 << 7),
	RT5677_AD_STEREO2_FILTER = (0x1 << 8),
	RT5677_AD_STEREO3_FILTER = (0x1 << 9),
	RT5677_AD_STEREO4_FILTER = (0x1 << 10),
	RT5677_AD_MONO_L_FILTER = (0x1 << 11),
	RT5677_AD_MONO_R_FILTER = (0x1 << 12),
	RT5677_DSP_OB_0_3_FILTER = (0x1 << 13),
	RT5677_DSP_OB_4_7_FILTER = (0x1 << 14),
	RT5677_I2S1_SOURCE = (0x1 << 15),
	RT5677_I2S2_SOURCE = (0x1 << 16),
	RT5677_I2S3_SOURCE = (0x1 << 17),
	RT5677_I2S4_SOURCE = (0x1 << 18),
पूर्ण;

क्रमागत rt5677_dmic2_clk अणु
	RT5677_DMIC_CLK1 = 0,
	RT5677_DMIC_CLK2 = 1,
पूर्ण;

काष्ठा rt5677_platक्रमm_data अणु
	/* IN1/IN2/LOUT1/LOUT2/LOUT3 can optionally be dअगरferential */
	bool in1_dअगरf;
	bool in2_dअगरf;
	bool lout1_dअगरf;
	bool lout2_dअगरf;
	bool lout3_dअगरf;
	/* DMIC2 घड़ी source selection */
	क्रमागत rt5677_dmic2_clk dmic2_clk_pin;

	/* configures GPIO, 0 - भग्नing, 1 - pullकरोwn, 2 - pullup */
	u8 gpio_config[6];

	/* jd1 can select 0 ~ 3 as OFF, GPIO1, GPIO2 and GPIO3 respectively */
	अचिन्हित पूर्णांक jd1_gpio;
	/* jd2 and jd3 can select 0 ~ 3 as
		OFF, GPIO4, GPIO5 and GPIO6 respectively */
	अचिन्हित पूर्णांक jd2_gpio;
	अचिन्हित पूर्णांक jd3_gpio;

	/* Set MICBIAS1 VDD 1v8 or 3v3 */
	bool micbias1_vdd_3v3;
पूर्ण;

काष्ठा rt5677_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा device *dev;
	काष्ठा rt5677_platक्रमm_data pdata;
	काष्ठा regmap *regmap, *regmap_physical;
	स्थिर काष्ठा firmware *fw1, *fw2;
	काष्ठा mutex dsp_cmd_lock, dsp_pri_lock;

	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck[RT5677_AIFS];
	पूर्णांक bclk[RT5677_AIFS];
	पूर्णांक master[RT5677_AIFS];
	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;
	काष्ठा gpio_desc *घात_lकरो2; /* POW_LDO2 pin */
	काष्ठा gpio_desc *reset_pin; /* RESET pin */
	क्रमागत rt5677_type type;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio_chip;
#पूर्ण_अगर
	bool dsp_vad_en_request; /* DSP VAD enable/disable request */
	bool dsp_vad_en; /* dsp_work parameter */
	bool is_dsp_mode;
	bool is_vref_slow;
	काष्ठा delayed_work dsp_work;

	/* Interrupt handling */
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा mutex irq_lock;
	अचिन्हित पूर्णांक irq_en;
	काष्ठा delayed_work resume_irq_check;
	पूर्णांक irq;

	पूर्णांक (*set_dsp_vad)(काष्ठा snd_soc_component *component, bool on);
पूर्ण;

पूर्णांक rt5677_sel_asrc_clk_src(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक filter_mask, अचिन्हित पूर्णांक clk_src);

#पूर्ण_अगर /* __RT5677_H__ */
