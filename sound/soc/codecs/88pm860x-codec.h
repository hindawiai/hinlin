<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * 88pm860x-codec.h -- 88PM860x ALSA SoC Audio Driver
 *
 * Copyright 2010 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#अगर_अघोषित __88PM860X_H
#घोषणा __88PM860X_H

#घोषणा PM860X_PCM_IFACE_1		0xb0
#घोषणा PM860X_PCM_IFACE_2		0xb1
#घोषणा PM860X_PCM_IFACE_3		0xb2
#घोषणा PM860X_PCM_RATE			0xb3
#घोषणा PM860X_EC_PATH			0xb4
#घोषणा PM860X_SIDETONE_L_GAIN		0xb5
#घोषणा PM860X_SIDETONE_R_GAIN		0xb6
#घोषणा PM860X_SIDETONE_SHIFT		0xb7
#घोषणा PM860X_ADC_OFFSET_1		0xb8
#घोषणा PM860X_ADC_OFFSET_2		0xb9
#घोषणा PM860X_DMIC_DELAY		0xba

#घोषणा PM860X_I2S_IFACE_1		0xbb
#घोषणा PM860X_I2S_IFACE_2		0xbc
#घोषणा PM860X_I2S_IFACE_3		0xbd
#घोषणा PM860X_I2S_IFACE_4		0xbe
#घोषणा PM860X_EQUALIZER_N0_1		0xbf
#घोषणा PM860X_EQUALIZER_N0_2		0xc0
#घोषणा PM860X_EQUALIZER_N1_1		0xc1
#घोषणा PM860X_EQUALIZER_N1_2		0xc2
#घोषणा PM860X_EQUALIZER_D1_1		0xc3
#घोषणा PM860X_EQUALIZER_D1_2		0xc4
#घोषणा PM860X_LOFI_GAIN_LEFT		0xc5
#घोषणा PM860X_LOFI_GAIN_RIGHT		0xc6
#घोषणा PM860X_HIFIL_GAIN_LEFT		0xc7
#घोषणा PM860X_HIFIL_GAIN_RIGHT		0xc8
#घोषणा PM860X_HIFIR_GAIN_LEFT		0xc9
#घोषणा PM860X_HIFIR_GAIN_RIGHT		0xca
#घोषणा PM860X_DAC_OFFSET		0xcb
#घोषणा PM860X_OFFSET_LEFT_1		0xcc
#घोषणा PM860X_OFFSET_LEFT_2		0xcd
#घोषणा PM860X_OFFSET_RIGHT_1		0xce
#घोषणा PM860X_OFFSET_RIGHT_2		0xcf
#घोषणा PM860X_ADC_ANA_1		0xd0
#घोषणा PM860X_ADC_ANA_2		0xd1
#घोषणा PM860X_ADC_ANA_3		0xd2
#घोषणा PM860X_ADC_ANA_4		0xd3
#घोषणा PM860X_ANA_TO_ANA		0xd4
#घोषणा PM860X_HS1_CTRL			0xd5
#घोषणा PM860X_HS2_CTRL			0xd6
#घोषणा PM860X_LO1_CTRL			0xd7
#घोषणा PM860X_LO2_CTRL			0xd8
#घोषणा PM860X_EAR_CTRL_1		0xd9
#घोषणा PM860X_EAR_CTRL_2		0xda
#घोषणा PM860X_AUDIO_SUPPLIES_1		0xdb
#घोषणा PM860X_AUDIO_SUPPLIES_2		0xdc
#घोषणा PM860X_ADC_EN_1			0xdd
#घोषणा PM860X_ADC_EN_2			0xde
#घोषणा PM860X_DAC_EN_1			0xdf
#घोषणा PM860X_DAC_EN_2			0xe1
#घोषणा PM860X_AUDIO_CAL_1		0xe2
#घोषणा PM860X_AUDIO_CAL_2		0xe3
#घोषणा PM860X_AUDIO_CAL_3		0xe4
#घोषणा PM860X_AUDIO_CAL_4		0xe5
#घोषणा PM860X_AUDIO_CAL_5		0xe6
#घोषणा PM860X_ANA_INPUT_SEL_1		0xe7
#घोषणा PM860X_ANA_INPUT_SEL_2		0xe8

#घोषणा PM860X_PCM_IFACE_4		0xe9
#घोषणा PM860X_I2S_IFACE_5		0xea

#घोषणा PM860X_SHORTS			0x3b
#घोषणा PM860X_PLL_ADJ_1		0x3c
#घोषणा PM860X_PLL_ADJ_2		0x3d

/* bits definition */
#घोषणा PM860X_CLK_सूची_IN		0
#घोषणा PM860X_CLK_सूची_OUT		1

#घोषणा PM860X_DET_HEADSET		(1 << 0)
#घोषणा PM860X_DET_MIC			(1 << 1)
#घोषणा PM860X_DET_HOOK			(1 << 2)
#घोषणा PM860X_SHORT_HEADSET		(1 << 3)
#घोषणा PM860X_SHORT_LINEOUT		(1 << 4)
#घोषणा PM860X_DET_MASK			0x1F

बाह्य पूर्णांक pm860x_hs_jack_detect(काष्ठा snd_soc_component *, काष्ठा snd_soc_jack *,
				 पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक pm860x_mic_jack_detect(काष्ठा snd_soc_component *, काष्ठा snd_soc_jack *,
				  पूर्णांक);

#पूर्ण_अगर	/* __88PM860X_H */
