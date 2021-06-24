<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Functions and रेजिस्टरs to access AC100 codec / RTC combo IC.
 *
 * Copyright (C) 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 */

#अगर_अघोषित __LINUX_MFD_AC100_H
#घोषणा __LINUX_MFD_AC100_H

#समावेश <linux/regmap.h>

काष्ठा ac100_dev अणु
	काष्ठा device			*dev;
	काष्ठा regmap			*regmap;
पूर्ण;

/* Audio codec related रेजिस्टरs */
#घोषणा AC100_CHIP_AUDIO_RST		0x00
#घोषणा AC100_PLL_CTRL1			0x01
#घोषणा AC100_PLL_CTRL2			0x02
#घोषणा AC100_SYSCLK_CTRL		0x03
#घोषणा AC100_MOD_CLK_ENA		0x04
#घोषणा AC100_MOD_RST_CTRL		0x05
#घोषणा AC100_I2S_SR_CTRL		0x06

/* I2S1 पूर्णांकerface */
#घोषणा AC100_I2S1_CLK_CTRL		0x10
#घोषणा AC100_I2S1_SND_OUT_CTRL		0x11
#घोषणा AC100_I2S1_SND_IN_CTRL		0x12
#घोषणा AC100_I2S1_MXR_SRC		0x13
#घोषणा AC100_I2S1_VOL_CTRL1		0x14
#घोषणा AC100_I2S1_VOL_CTRL2		0x15
#घोषणा AC100_I2S1_VOL_CTRL3		0x16
#घोषणा AC100_I2S1_VOL_CTRL4		0x17
#घोषणा AC100_I2S1_MXR_GAIN		0x18

/* I2S2 पूर्णांकerface */
#घोषणा AC100_I2S2_CLK_CTRL		0x20
#घोषणा AC100_I2S2_SND_OUT_CTRL		0x21
#घोषणा AC100_I2S2_SND_IN_CTRL		0x22
#घोषणा AC100_I2S2_MXR_SRC		0x23
#घोषणा AC100_I2S2_VOL_CTRL1		0x24
#घोषणा AC100_I2S2_VOL_CTRL2		0x25
#घोषणा AC100_I2S2_VOL_CTRL3		0x26
#घोषणा AC100_I2S2_VOL_CTRL4		0x27
#घोषणा AC100_I2S2_MXR_GAIN		0x28

/* I2S3 पूर्णांकerface */
#घोषणा AC100_I2S3_CLK_CTRL		0x30
#घोषणा AC100_I2S3_SND_OUT_CTRL		0x31
#घोषणा AC100_I2S3_SND_IN_CTRL		0x32
#घोषणा AC100_I2S3_SIG_PATH_CTRL	0x33

/* ADC digital controls */
#घोषणा AC100_ADC_DIG_CTRL		0x40
#घोषणा AC100_ADC_VOL_CTRL		0x41

/* HMIC plug sensing / key detection */
#घोषणा AC100_HMIC_CTRL1		0x44
#घोषणा AC100_HMIC_CTRL2		0x45
#घोषणा AC100_HMIC_STATUS		0x46

/* DAC digital controls */
#घोषणा AC100_DAC_DIG_CTRL		0x48
#घोषणा AC100_DAC_VOL_CTRL		0x49
#घोषणा AC100_DAC_MXR_SRC		0x4c
#घोषणा AC100_DAC_MXR_GAIN		0x4d

/* Analog controls */
#घोषणा AC100_ADC_APC_CTRL		0x50
#घोषणा AC100_ADC_SRC			0x51
#घोषणा AC100_ADC_SRC_BST_CTRL		0x52
#घोषणा AC100_OUT_MXR_DAC_A_CTRL	0x53
#घोषणा AC100_OUT_MXR_SRC		0x54
#घोषणा AC100_OUT_MXR_SRC_BST		0x55
#घोषणा AC100_HPOUT_CTRL		0x56
#घोषणा AC100_ERPOUT_CTRL		0x57
#घोषणा AC100_SPKOUT_CTRL		0x58
#घोषणा AC100_LINEOUT_CTRL		0x59

/* ADC digital audio processing (high pass filter & स्वतः gain control */
#घोषणा AC100_ADC_DAP_L_STA		0x80
#घोषणा AC100_ADC_DAP_R_STA		0x81
#घोषणा AC100_ADC_DAP_L_CTRL		0x82
#घोषणा AC100_ADC_DAP_R_CTRL		0x83
#घोषणा AC100_ADC_DAP_L_T_L		0x84 /* Left Target Level */
#घोषणा AC100_ADC_DAP_R_T_L		0x85 /* Right Target Level */
#घोषणा AC100_ADC_DAP_L_H_A_C		0x86 /* Left High Avg. Coef */
#घोषणा AC100_ADC_DAP_L_L_A_C		0x87 /* Left Low Avg. Coef */
#घोषणा AC100_ADC_DAP_R_H_A_C		0x88 /* Right High Avg. Coef */
#घोषणा AC100_ADC_DAP_R_L_A_C		0x89 /* Right Low Avg. Coef */
#घोषणा AC100_ADC_DAP_L_D_T		0x8a /* Left Decay Time */
#घोषणा AC100_ADC_DAP_L_A_T		0x8b /* Left Attack Time */
#घोषणा AC100_ADC_DAP_R_D_T		0x8c /* Right Decay Time */
#घोषणा AC100_ADC_DAP_R_A_T		0x8d /* Right Attack Time */
#घोषणा AC100_ADC_DAP_N_TH		0x8e /* Noise Threshold */
#घोषणा AC100_ADC_DAP_L_H_N_A_C		0x8f /* Left High Noise Avg. Coef */
#घोषणा AC100_ADC_DAP_L_L_N_A_C		0x90 /* Left Low Noise Avg. Coef */
#घोषणा AC100_ADC_DAP_R_H_N_A_C		0x91 /* Right High Noise Avg. Coef */
#घोषणा AC100_ADC_DAP_R_L_N_A_C		0x92 /* Right Low Noise Avg. Coef */
#घोषणा AC100_ADC_DAP_H_HPF_C		0x93 /* High High-Pass-Filter Coef */
#घोषणा AC100_ADC_DAP_L_HPF_C		0x94 /* Low High-Pass-Filter Coef */
#घोषणा AC100_ADC_DAP_OPT		0x95 /* AGC Optimum */

/* DAC digital audio processing (high pass filter & dynamic range control) */
#घोषणा AC100_DAC_DAP_CTRL		0xa0
#घोषणा AC100_DAC_DAP_H_HPF_C		0xa1 /* High High-Pass-Filter Coef */
#घोषणा AC100_DAC_DAP_L_HPF_C		0xa2 /* Low High-Pass-Filter Coef */
#घोषणा AC100_DAC_DAP_L_H_E_A_C		0xa3 /* Left High Energy Avg Coef */
#घोषणा AC100_DAC_DAP_L_L_E_A_C		0xa4 /* Left Low Energy Avg Coef */
#घोषणा AC100_DAC_DAP_R_H_E_A_C		0xa5 /* Right High Energy Avg Coef */
#घोषणा AC100_DAC_DAP_R_L_E_A_C		0xa6 /* Right Low Energy Avg Coef */
#घोषणा AC100_DAC_DAP_H_G_D_T_C		0xa7 /* High Gain Delay Time Coef */
#घोषणा AC100_DAC_DAP_L_G_D_T_C		0xa8 /* Low Gain Delay Time Coef */
#घोषणा AC100_DAC_DAP_H_G_A_T_C		0xa9 /* High Gain Attack Time Coef */
#घोषणा AC100_DAC_DAP_L_G_A_T_C		0xaa /* Low Gain Attack Time Coef */
#घोषणा AC100_DAC_DAP_H_E_TH		0xab /* High Energy Threshold */
#घोषणा AC100_DAC_DAP_L_E_TH		0xac /* Low Energy Threshold */
#घोषणा AC100_DAC_DAP_H_G_K		0xad /* High Gain K parameter */
#घोषणा AC100_DAC_DAP_L_G_K		0xae /* Low Gain K parameter */
#घोषणा AC100_DAC_DAP_H_G_OFF		0xaf /* High Gain offset */
#घोषणा AC100_DAC_DAP_L_G_OFF		0xb0 /* Low Gain offset */
#घोषणा AC100_DAC_DAP_OPT		0xb1 /* DRC optimum */

/* Digital audio processing enable */
#घोषणा AC100_ADC_DAP_ENA		0xb4
#घोषणा AC100_DAC_DAP_ENA		0xb5

/* SRC control */
#घोषणा AC100_SRC1_CTRL1		0xb8
#घोषणा AC100_SRC1_CTRL2		0xb9
#घोषणा AC100_SRC1_CTRL3		0xba
#घोषणा AC100_SRC1_CTRL4		0xbb
#घोषणा AC100_SRC2_CTRL1		0xbc
#घोषणा AC100_SRC2_CTRL2		0xbd
#घोषणा AC100_SRC2_CTRL3		0xbe
#घोषणा AC100_SRC2_CTRL4		0xbf

/* RTC clk control */
#घोषणा AC100_CLK32K_ANALOG_CTRL	0xc0
#घोषणा AC100_CLKOUT_CTRL1		0xc1
#घोषणा AC100_CLKOUT_CTRL2		0xc2
#घोषणा AC100_CLKOUT_CTRL3		0xc3

/* RTC module */
#घोषणा AC100_RTC_RST			0xc6
#घोषणा AC100_RTC_CTRL			0xc7
#घोषणा AC100_RTC_SEC			0xc8 /* second */
#घोषणा AC100_RTC_MIN			0xc9 /* minute */
#घोषणा AC100_RTC_HOU			0xca /* hour */
#घोषणा AC100_RTC_WEE			0xcb /* weekday */
#घोषणा AC100_RTC_DAY			0xcc /* day */
#घोषणा AC100_RTC_MON			0xcd /* month */
#घोषणा AC100_RTC_YEA			0xce /* year */
#घोषणा AC100_RTC_UPD			0xcf /* update trigger */

/* RTC alarm */
#घोषणा AC100_ALM_INT_ENA		0xd0
#घोषणा	AC100_ALM_INT_STA		0xd1
#घोषणा AC100_ALM_SEC			0xd8
#घोषणा AC100_ALM_MIN			0xd9
#घोषणा AC100_ALM_HOU			0xda
#घोषणा AC100_ALM_WEE			0xdb
#घोषणा AC100_ALM_DAY			0xdc
#घोषणा AC100_ALM_MON			0xdd
#घोषणा AC100_ALM_YEA			0xde
#घोषणा AC100_ALM_UPD			0xdf

/* RTC general purpose रेजिस्टर 0 ~ 15 */
#घोषणा AC100_RTC_GP(x)			(0xe0 + (x))

#पूर्ण_अगर /* __LINUX_MFD_AC100_H */
