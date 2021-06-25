<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
* alc5632.h  --  ALC5632 ALSA SoC Audio Codec
*
* Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.lauchpad.net>
*
* Authors:  Leon Romanovsky <leon@leon.nu>
*           Andrey Danin <danindrey@mail.ru>
*           Ilya Petrov <ilya.muromec@gmail.com>
*           Marc Dietrich <marvin24@gmx.de>
*
* Based on alc5623.h by Arnaud Patard
*/

#अगर_अघोषित _ALC5632_H
#घोषणा _ALC5632_H

#घोषणा ALC5632_RESET				0x00
/* speaker output vol		   2    2           */
/* line output vol                      4    2      */
/* HP output vol		   4    0    4      */
#घोषणा ALC5632_SPK_OUT_VOL			0x02 /* spe out vol */
#घोषणा ALC5632_SPK_OUT_VOL_STEP		1.5
#घोषणा ALC5632_HP_OUT_VOL			0x04 /* hp out vol */
#घोषणा ALC5632_AUX_OUT_VOL			0x06 /* aux out vol */
#घोषणा ALC5632_PHONE_IN_VOL			0x08 /* phone in vol */
#घोषणा ALC5632_LINE_IN_VOL			0x0A /* line in vol */
#घोषणा ALC5632_STEREO_DAC_IN_VOL		0x0C /* stereo dac in vol */
#घोषणा ALC5632_MIC_VOL				0x0E /* mic in vol */
/* stero dac/mic routing */
#घोषणा ALC5632_MIC_ROUTING_CTRL		0x10
#घोषणा ALC5632_MIC_ROUTE_MONOMIX		(1 << 0)
#घोषणा ALC5632_MIC_ROUTE_SPK			(1 << 1)
#घोषणा ALC5632_MIC_ROUTE_HP			(1 << 2)

#घोषणा ALC5632_ADC_REC_GAIN			0x12 /* rec gain */
#घोषणा ALC5632_ADC_REC_GAIN_RANGE		0x1F1F
#घोषणा ALC5632_ADC_REC_GAIN_BASE		(-16.5)
#घोषणा ALC5632_ADC_REC_GAIN_STEP		1.5

#घोषणा ALC5632_ADC_REC_MIXER			0x14 /* mixer control */
#घोषणा ALC5632_ADC_REC_MIC1			(1 << 6)
#घोषणा ALC5632_ADC_REC_MIC2			(1 << 5)
#घोषणा ALC5632_ADC_REC_LINE_IN			(1 << 4)
#घोषणा ALC5632_ADC_REC_AUX			(1 << 3)
#घोषणा ALC5632_ADC_REC_HP			(1 << 2)
#घोषणा ALC5632_ADC_REC_SPK			(1 << 1)
#घोषणा ALC5632_ADC_REC_MONOMIX			(1 << 0)

#घोषणा ALC5632_VOICE_DAC_VOL			0x18 /* voice dac vol */
#घोषणा ALC5632_I2S_OUT_CTL				0x1A /* unकरोcumented reg. found in path scheme */
/* ALC5632_OUTPUT_MIXER_CTRL :			*/
/* same remark as क्रम reg 2 line vs speaker	*/
#घोषणा ALC5632_OUTPUT_MIXER_CTRL		0x1C /* out mix ctrl */
#घोषणा ALC5632_OUTPUT_MIXER_RP			(1 << 14)
#घोषणा ALC5632_OUTPUT_MIXER_WEEK		(1 << 12)
#घोषणा ALC5632_OUTPUT_MIXER_HP			(1 << 10)
#घोषणा ALC5632_OUTPUT_MIXER_AUX_SPK		(2 <<  6)
#घोषणा ALC5632_OUTPUT_MIXER_AUX_HP_LR          (1 << 6)
#घोषणा ALC5632_OUTPUT_MIXER_HP_R               (1 << 8)
#घोषणा ALC5632_OUTPUT_MIXER_HP_L               (1 << 9)

#घोषणा ALC5632_MIC_CTRL			0x22 /* mic phone ctrl */
#घोषणा ALC5632_MIC_BOOST_BYPASS		0
#घोषणा ALC5632_MIC_BOOST_20DB			1
#घोषणा ALC5632_MIC_BOOST_30DB			2
#घोषणा ALC5632_MIC_BOOST_40DB			3

#घोषणा ALC5632_DIGI_BOOST_CTRL			0x24 /* digi mic / bost ctl */
#घोषणा ALC5632_MIC_BOOST_RANGE			7
#घोषणा ALC5632_MIC_BOOST_STEP			6
#घोषणा ALC5632_PWR_DOWN_CTRL_STATUS		0x26
#घोषणा ALC5632_PWR_DOWN_CTRL_STATUS_MASK	0xEF00
#घोषणा ALC5632_PWR_VREF_PR3			(1 << 11)
#घोषणा ALC5632_PWR_VREF_PR2			(1 << 10)
#घोषणा ALC5632_PWR_VREF_STATUS			(1 << 3)
#घोषणा ALC5632_PWR_AMIX_STATUS			(1 << 2)
#घोषणा ALC5632_PWR_DAC_STATUS			(1 << 1)
#घोषणा ALC5632_PWR_ADC_STATUS			(1 << 0)
/* stereo/voice DAC / stereo adc func ctrl */
#घोषणा ALC5632_DAC_FUNC_SELECT			0x2E

/* Main serial data port ctrl (i2s) */
#घोषणा ALC5632_DAI_CONTROL			0x34

#घोषणा ALC5632_DAI_SDP_MASTER_MODE		(0 << 15)
#घोषणा ALC5632_DAI_SDP_SLAVE_MODE		(1 << 15)
#घोषणा ALC5632_DAI_SADLRCK_MODE		(1 << 14)
/* 0:voice, 1:मुख्य */
#घोषणा ALC5632_DAI_MAIN_I2S_SYSCLK_SEL		(1 <<  8)
#घोषणा ALC5632_DAI_MAIN_I2S_BCLK_POL_CTRL	(1 <<  7)
/* 0:normal, 1:invert */
#घोषणा ALC5632_DAI_MAIN_I2S_LRCK_INV		(1 <<  6)
#घोषणा ALC5632_DAI_I2S_DL_MASK			(3 <<  2)
#घोषणा ALC5632_DAI_I2S_DL_8			(3 <<  2)
#घोषणा	ALC5632_DAI_I2S_DL_24			(2 <<  2)
#घोषणा	ALC5632_DAI_I2S_DL_20			(1 <<  2)
#घोषणा ALC5632_DAI_I2S_DL_16			(0 <<  2)
#घोषणा ALC5632_DAI_I2S_DF_MASK			(3 <<  0)
#घोषणा ALC5632_DAI_I2S_DF_PCM_B		(3 <<  0)
#घोषणा	ALC5632_DAI_I2S_DF_PCM_A		(2 <<  0)
#घोषणा ALC5632_DAI_I2S_DF_LEFT			(1 <<  0)
#घोषणा ALC5632_DAI_I2S_DF_I2S			(0 <<  0)
/* extend serial data port control (VoDAC_i2c/pcm) */
#घोषणा ALC5632_DAI_CONTROL2			0x36
/* 0:gpio func, 1:voice pcm */
#घोषणा ALC5632_DAI_VOICE_PCM_ENABLE		(1 << 15)
/* 0:master, 1:slave */
#घोषणा ALC5632_DAI_VOICE_MODE_SEL		(1 << 14)
/* 0:disable, 1:enable */
#घोषणा ALC5632_DAI_HPF_CLK_CTRL		(1 << 13)
/* 0:मुख्य, 1:voice */
#घोषणा ALC5632_DAI_VOICE_I2S_SYSCLK_SEL	(1 <<  8)
/* 0:normal, 1:invert */
#घोषणा ALC5632_DAI_VOICE_VBCLK_SYSCLK_SEL	(1 <<  7)
/* 0:normal, 1:invert */
#घोषणा ALC5632_DAI_VOICE_I2S_LR_INV		(1 <<  6)
#घोषणा ALC5632_DAI_VOICE_DL_MASK		(3 <<  2)
#घोषणा ALC5632_DAI_VOICE_DL_16			(0 <<  2)
#घोषणा ALC5632_DAI_VOICE_DL_20			(1 <<  2)
#घोषणा ALC5632_DAI_VOICE_DL_24			(2 <<  2)
#घोषणा ALC5632_DAI_VOICE_DL_8			(3 <<  2)
#घोषणा ALC5632_DAI_VOICE_DF_MASK		(3 <<  0)
#घोषणा ALC5632_DAI_VOICE_DF_I2S		(0 <<  0)
#घोषणा ALC5632_DAI_VOICE_DF_LEFT		(1 <<  0)
#घोषणा ALC5632_DAI_VOICE_DF_PCM_A		(2 <<  0)
#घोषणा ALC5632_DAI_VOICE_DF_PCM_B		(3 <<  0)

#घोषणा	ALC5632_PWR_MANAG_ADD1			0x3A
#घोषणा	ALC5632_PWR_MANAG_ADD1_MASK		0xEFFF
#घोषणा ALC5632_PWR_ADD1_DAC_L_EN		(1 << 15)
#घोषणा ALC5632_PWR_ADD1_DAC_R_EN		(1 << 14)
#घोषणा ALC5632_PWR_ADD1_ZERO_CROSS		(1 << 13)
#घोषणा ALC5632_PWR_ADD1_MAIN_I2S_EN		(1 << 11)
#घोषणा ALC5632_PWR_ADD1_SPK_AMP_EN		(1 << 10)
#घोषणा ALC5632_PWR_ADD1_HP_OUT_AMP		(1 <<  9)
#घोषणा ALC5632_PWR_ADD1_HP_OUT_ENH_AMP		(1 <<  8)
#घोषणा ALC5632_PWR_ADD1_VOICE_DAC_MIX		(1 <<  7)
#घोषणा	ALC5632_PWR_ADD1_SOFTGEN_EN		(1 <<  6)
#घोषणा	ALC5632_PWR_ADD1_MIC1_SHORT_CURR	(1 <<  5)
#घोषणा	ALC5632_PWR_ADD1_MIC2_SHORT_CURR	(1 <<  4)
#घोषणा	ALC5632_PWR_ADD1_MIC1_EN		(1 <<  3)
#घोषणा	ALC5632_PWR_ADD1_MIC2_EN		(1 <<  2)
#घोषणा ALC5632_PWR_ADD1_MAIN_BIAS		(1 <<  1)
#घोषणा ALC5632_PWR_ADD1_DAC_REF		(1 <<  0)

#घोषणा ALC5632_PWR_MANAG_ADD2			0x3C
#घोषणा ALC5632_PWR_MANAG_ADD2_MASK		0x7FFF
#घोषणा ALC5632_PWR_ADD2_PLL1			(1 << 15)
#घोषणा ALC5632_PWR_ADD2_PLL2			(1 << 14)
#घोषणा ALC5632_PWR_ADD2_VREF			(1 << 13)
#घोषणा ALC5632_PWR_ADD2_OVT_DET		(1 << 12)
#घोषणा ALC5632_PWR_ADD2_VOICE_DAC		(1 << 10)
#घोषणा ALC5632_PWR_ADD2_L_DAC_CLK		(1 <<  9)
#घोषणा ALC5632_PWR_ADD2_R_DAC_CLK		(1 <<  8)
#घोषणा ALC5632_PWR_ADD2_L_ADC_CLK_GAIN		(1 <<  7)
#घोषणा ALC5632_PWR_ADD2_R_ADC_CLK_GAIN		(1 <<  6)
#घोषणा ALC5632_PWR_ADD2_L_HP_MIXER		(1 <<  5)
#घोषणा ALC5632_PWR_ADD2_R_HP_MIXER		(1 <<  4)
#घोषणा ALC5632_PWR_ADD2_SPK_MIXER		(1 <<  3)
#घोषणा ALC5632_PWR_ADD2_MONO_MIXER		(1 <<  2)
#घोषणा ALC5632_PWR_ADD2_L_ADC_REC_MIXER	(1 <<  1)
#घोषणा ALC5632_PWR_ADD2_R_ADC_REC_MIXER	(1 <<  0)

#घोषणा ALC5632_PWR_MANAG_ADD3			0x3E
#घोषणा ALC5632_PWR_MANAG_ADD3_MASK		0x7CFF
#घोषणा ALC5632_PWR_ADD3_AUXOUT_VOL		(1 << 14)
#घोषणा ALC5632_PWR_ADD3_SPK_L_OUT		(1 << 13)
#घोषणा ALC5632_PWR_ADD3_SPK_R_OUT		(1 << 12)
#घोषणा ALC5632_PWR_ADD3_HP_L_OUT_VOL		(1 << 11)
#घोषणा ALC5632_PWR_ADD3_HP_R_OUT_VOL		(1 << 10)
#घोषणा ALC5632_PWR_ADD3_LINEIN_L_VOL		(1 <<  7)
#घोषणा ALC5632_PWR_ADD3_LINEIN_R_VOL		(1 <<  6)
#घोषणा ALC5632_PWR_ADD3_AUXIN_VOL		(1 <<  5)
#घोषणा ALC5632_PWR_ADD3_AUXIN_MIX		(1 <<  4)
#घोषणा ALC5632_PWR_ADD3_MIC1_VOL		(1 <<  3)
#घोषणा ALC5632_PWR_ADD3_MIC2_VOL		(1 <<  2)
#घोषणा ALC5632_PWR_ADD3_MIC1_BOOST_AD		(1 <<  1)
#घोषणा ALC5632_PWR_ADD3_MIC2_BOOST_AD		(1 <<  0)

#घोषणा ALC5632_GPCR1				0x40
#घोषणा ALC5632_GPCR1_CLK_SYS_SRC_SEL_PLL1	(1 << 15)
#घोषणा ALC5632_GPCR1_CLK_SYS_SRC_SEL_MCLK	(0 << 15)
#घोषणा ALC5632_GPCR1_DAC_HI_FLT_EN		(1 << 10)
#घोषणा ALC5632_GPCR1_SPK_AMP_CTRL		(7 <<  1)
#घोषणा ALC5632_GPCR1_VDD_100			(5 <<  1)
#घोषणा ALC5632_GPCR1_VDD_125			(4 <<  1)
#घोषणा ALC5632_GPCR1_VDD_150			(3 <<  1)
#घोषणा ALC5632_GPCR1_VDD_175			(2 <<  1)
#घोषणा ALC5632_GPCR1_VDD_200			(1 <<  1)
#घोषणा ALC5632_GPCR1_VDD_225			(0 <<  1)

#घोषणा	ALC5632_GPCR2				0x42
#घोषणा ALC5632_GPCR2_PLL1_SOUR_SEL		(3 << 12)
#घोषणा ALC5632_PLL_FR_MCLK			(0 << 12)
#घोषणा ALC5632_PLL_FR_BCLK			(2 << 12)
#घोषणा ALC5632_PLL_FR_VBCLK			(3 << 12)
#घोषणा ALC5632_GPCR2_CLK_PLL_PRE_DIV1		(0 <<  0)

#घोषणा ALC5632_PLL1_CTRL			0x44
#घोषणा ALC5632_PLL1_CTRL_N_VAL(n)		(((n) & 0x0f) << 8)
#घोषणा ALC5632_PLL1_M_BYPASS			(1 <<  7)
#घोषणा ALC5632_PLL1_CTRL_K_VAL(k)		(((k) & 0x07) << 4)
#घोषणा ALC5632_PLL1_CTRL_M_VAL(m)		(((m) & 0x0f) << 0)

#घोषणा ALC5632_PLL2_CTRL			0x46
#घोषणा ALC5632_PLL2_EN				(1 << 15)
#घोषणा ALC5632_PLL2_RATIO			(0 << 15)

#घोषणा ALC5632_GPIO_PIN_CONFIG			0x4C
#घोषणा ALC5632_GPIO_PIN_POLARITY		0x4E
#घोषणा ALC5632_GPIO_PIN_STICKY			0x50
#घोषणा ALC5632_GPIO_PIN_WAKEUP			0x52
#घोषणा ALC5632_GPIO_PIN_STATUS			0x54
#घोषणा ALC5632_GPIO_PIN_SHARING		0x56
#घोषणा	ALC5632_OVER_CURR_STATUS		0x58
#घोषणा ALC5632_SOFTVOL_CTRL			0x5A
#घोषणा ALC5632_GPIO_OUPUT_PIN_CTRL		0x5C

#घोषणा ALC5632_MISC_CTRL			0x5E
#घोषणा ALC5632_MISC_DISABLE_FAST_VREG		(1 << 15)
#घोषणा ALC5632_MISC_AVC_TRGT_SEL		(3 << 12)
#घोषणा ALC5632_MISC_AVC_TRGT_RIGHT		(1 << 12)
#घोषणा ALC5632_MISC_AVC_TRGT_LEFT		(2 << 12)
#घोषणा ALC5632_MISC_AVC_TRGT_BOTH		(3 << 12)
#घोषणा ALC5632_MISC_HP_DEPOP_MODE1_EN		(1 <<  9)
#घोषणा ALC5632_MISC_HP_DEPOP_MODE2_EN		(1 <<  8)
#घोषणा ALC5632_MISC_HP_DEPOP_MUTE_L		(1 <<  7)
#घोषणा ALC5632_MISC_HP_DEPOP_MUTE_R		(1 <<  6)
#घोषणा ALC5632_MISC_HP_DEPOP_MUTE		(1 <<  5)
#घोषणा ALC5632_MISC_GPIO_WAKEUP_CTRL		(1 <<  1)
#घोषणा ALC5632_MISC_IRQOUT_INV_CTRL		(1 <<  0)

#घोषणा ALC5632_DAC_CLK_CTRL1			0x60
#घोषणा ALC5632_DAC_CLK_CTRL2			0x62
#घोषणा ALC5632_DAC_CLK_CTRL2_DIV1_2		(1 << 0)
#घोषणा ALC5632_VOICE_DAC_PCM_CLK_CTRL1		0x64
#घोषणा ALC5632_PSEUDO_SPATIAL_CTRL		0x68
#घोषणा ALC5632_HID_CTRL_INDEX			0x6A
#घोषणा ALC5632_HID_CTRL_DATA			0x6C
#घोषणा ALC5632_EQ_CTRL				0x6E

/* unकरोcumented */
#घोषणा ALC5632_VENDOR_ID1			0x7C
#घोषणा ALC5632_VENDOR_ID2			0x7E

#घोषणा ALC5632_MAX_REGISTER        0x7E

#पूर्ण_अगर
