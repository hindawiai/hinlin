<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 88pm860x-codec.c -- 88PM860x ALSA SoC Audio Driver
 *
 * Copyright 2010 Marvell International Ltd.
 * Author: Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/initval.h>
#समावेश <sound/jack.h>
#समावेश <trace/events/asoc.h>

#समावेश "88pm860x-codec.h"

#घोषणा MAX_NAME_LEN		20
#घोषणा REG_CACHE_SIZE		0x40
#घोषणा REG_CACHE_BASE		0xb0

/* Status Register 1 (0x01) */
#घोषणा REG_STATUS_1		0x01
#घोषणा MIC_STATUS		(1 << 7)
#घोषणा HOOK_STATUS		(1 << 6)
#घोषणा HEADSET_STATUS		(1 << 5)

/* Mic Detection Register (0x37) */
#घोषणा REG_MIC_DET		0x37
#घोषणा CONTINUOUS_POLLING	(3 << 1)
#घोषणा EN_MIC_DET		(1 << 0)
#घोषणा MICDET_MASK		0x07

/* Headset Detection Register (0x38) */
#घोषणा REG_HS_DET		0x38
#घोषणा EN_HS_DET		(1 << 0)

/* Misc2 Register (0x42) */
#घोषणा REG_MISC2		0x42
#घोषणा AUDIO_PLL		(1 << 5)
#घोषणा AUDIO_SECTION_RESET	(1 << 4)
#घोषणा AUDIO_SECTION_ON	(1 << 3)

/* PCM Interface Register 2 (0xb1) */
#घोषणा PCM_INF2_BCLK		(1 << 6)	/* Bit घड़ी polarity */
#घोषणा PCM_INF2_FS		(1 << 5)	/* Frame Sync polarity */
#घोषणा PCM_INF2_MASTER		(1 << 4)	/* Master / Slave */
#घोषणा PCM_INF2_18WL		(1 << 3)	/* 18 / 16 bits */
#घोषणा PCM_GENERAL_I2S		0
#घोषणा PCM_EXACT_I2S		1
#घोषणा PCM_LEFT_I2S		2
#घोषणा PCM_RIGHT_I2S		3
#घोषणा PCM_SHORT_FS		4
#घोषणा PCM_LONG_FS		5
#घोषणा PCM_MODE_MASK		7

/* I2S Interface Register 4 (0xbe) */
#घोषणा I2S_EQU_BYP		(1 << 6)

/* DAC Offset Register (0xcb) */
#घोषणा DAC_MUTE		(1 << 7)
#घोषणा MUTE_LEFT		(1 << 6)
#घोषणा MUTE_RIGHT		(1 << 2)

/* ADC Analog Register 1 (0xd0) */
#घोषणा REG_ADC_ANA_1		0xd0
#घोषणा MIC1BIAS_MASK		0x60

/* Earpiece/Speaker Control Register 2 (0xda) */
#घोषणा REG_EAR2		0xda
#घोषणा RSYNC_CHANGE		(1 << 2)

/* Audio Supplies Register 2 (0xdc) */
#घोषणा REG_SUPPLIES2		0xdc
#घोषणा LDO15_READY		(1 << 4)
#घोषणा LDO15_EN		(1 << 3)
#घोषणा CPUMP_READY		(1 << 2)
#घोषणा CPUMP_EN		(1 << 1)
#घोषणा AUDIO_EN		(1 << 0)
#घोषणा SUPPLY_MASK		(LDO15_EN | CPUMP_EN | AUDIO_EN)

/* Audio Enable Register 1 (0xdd) */
#घोषणा ADC_MOD_RIGHT		(1 << 1)
#घोषणा ADC_MOD_LEFT		(1 << 0)

/* Audio Enable Register 2 (0xde) */
#घोषणा ADC_LEFT		(1 << 5)
#घोषणा ADC_RIGHT		(1 << 4)

/* DAC Enable Register 2 (0xe1) */
#घोषणा DAC_LEFT		(1 << 5)
#घोषणा DAC_RIGHT		(1 << 4)
#घोषणा MODULATOR		(1 << 3)

/* Shorts Register (0xeb) */
#घोषणा REG_SHORTS		0xeb
#घोषणा CLR_SHORT_LO2		(1 << 7)
#घोषणा SHORT_LO2		(1 << 6)
#घोषणा CLR_SHORT_LO1		(1 << 5)
#घोषणा SHORT_LO1		(1 << 4)
#घोषणा CLR_SHORT_HS2		(1 << 3)
#घोषणा SHORT_HS2		(1 << 2)
#घोषणा CLR_SHORT_HS1		(1 << 1)
#घोषणा SHORT_HS1		(1 << 0)

/*
 * This widget should be just after DAC & PGA in DAPM घातer-on sequence and
 * beक्रमe DAC & PGA in DAPM घातer-off sequence.
 */
#घोषणा PM860X_DAPM_OUTPUT(wname, wevent)	\
	SND_SOC_DAPM_PGA_E(wname, SND_SOC_NOPM, 0, 0, शून्य, 0, wevent, \
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD)

काष्ठा pm860x_det अणु
	काष्ठा snd_soc_jack	*hp_jack;
	काष्ठा snd_soc_jack	*mic_jack;
	पूर्णांक			hp_det;
	पूर्णांक			mic_det;
	पूर्णांक			hook_det;
	पूर्णांक			hs_shrt;
	पूर्णांक			lo_shrt;
पूर्ण;

काष्ठा pm860x_priv अणु
	अचिन्हित पूर्णांक		sysclk;
	अचिन्हित पूर्णांक		pcmclk;
	अचिन्हित पूर्णांक		dir;
	अचिन्हित पूर्णांक		filter;
	काष्ठा snd_soc_component *component;
	काष्ठा i2c_client	*i2c;
	काष्ठा regmap		*regmap;
	काष्ठा pm860x_chip	*chip;
	काष्ठा pm860x_det	det;

	पूर्णांक			irq[4];
	अचिन्हित अक्षर		name[4][MAX_NAME_LEN+1];
पूर्ण;

/* -9450dB to 0dB in 150dB steps ( mute instead of -9450dB) */
अटल स्थिर DECLARE_TLV_DB_SCALE(dpga_tlv, -9450, 150, 1);

/* -9dB to 0db in 3dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -900, 300, 0);

/* अणु-23, -17, -13.5, -11, -9, -6, -3, 0पूर्णdB */
अटल स्थिर DECLARE_TLV_DB_RANGE(mic_tlv,
	0, 0, TLV_DB_SCALE_ITEM(-2300, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(-1700, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(-1350, 0, 0),
	3, 3, TLV_DB_SCALE_ITEM(-1100, 0, 0),
	4, 7, TLV_DB_SCALE_ITEM(-900, 300, 0)
);

/* अणु0, 0, 0, -6, 0, 6, 12, 18पूर्णdB */
अटल स्थिर DECLARE_TLV_DB_RANGE(aux_tlv,
	0, 2, TLV_DB_SCALE_ITEM(0, 0, 0),
	3, 7, TLV_DB_SCALE_ITEM(-600, 600, 0)
);

/* अणु-16, -13, -10, -7, -5.2, -3,3, -2.2, 0पूर्णdB, mute instead of -16dB */
अटल स्थिर DECLARE_TLV_DB_RANGE(out_tlv,
	0, 3, TLV_DB_SCALE_ITEM(-1600, 300, 1),
	4, 4, TLV_DB_SCALE_ITEM(-520, 0, 0),
	5, 5, TLV_DB_SCALE_ITEM(-330, 0, 0),
	6, 7, TLV_DB_SCALE_ITEM(-220, 220, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(st_tlv,
	0, 1, TLV_DB_SCALE_ITEM(-12041, 602, 0),
	2, 3, TLV_DB_SCALE_ITEM(-11087, 250, 0),
	4, 5, TLV_DB_SCALE_ITEM(-10643, 158, 0),
	6, 7, TLV_DB_SCALE_ITEM(-10351, 116, 0),
	8, 9, TLV_DB_SCALE_ITEM(-10133, 92, 0),
	10, 13, TLV_DB_SCALE_ITEM(-9958, 70, 0),
	14, 17, TLV_DB_SCALE_ITEM(-9689, 53, 0),
	18, 271, TLV_DB_SCALE_ITEM(-9484, 37, 0)
);

/* Sidetone Gain = M * 2^(-5-N) */
काष्ठा st_gain अणु
	अचिन्हित पूर्णांक	db;
	अचिन्हित पूर्णांक	m;
	अचिन्हित पूर्णांक	n;
पूर्ण;

अटल काष्ठा st_gain st_table[] = अणु
	अणु-12041,  1, 15पूर्ण, अणु-11439,  1, 14पूर्ण, अणु-11087,  3, 15पूर्ण, अणु-10837,  1, 13पूर्ण,
	अणु-10643,  5, 15पूर्ण, अणु-10485,  3, 14पूर्ण, अणु-10351,  7, 15पूर्ण, अणु-10235,  1, 12पूर्ण,
	अणु-10133,  9, 15पूर्ण, अणु-10041,  5, 14पूर्ण, अणु -9958, 11, 15पूर्ण, अणु -9883,  3, 13पूर्ण,
	अणु -9813, 13, 15पूर्ण, अणु -9749,  7, 14पूर्ण, अणु -9689, 15, 15पूर्ण, अणु -9633,  1, 11पूर्ण,
	अणु -9580, 17, 15पूर्ण, अणु -9531,  9, 14पूर्ण, अणु -9484, 19, 15पूर्ण, अणु -9439,  5, 13पूर्ण,
	अणु -9397, 21, 15पूर्ण, अणु -9356, 11, 14पूर्ण, अणु -9318, 23, 15पूर्ण, अणु -9281,  3, 12पूर्ण,
	अणु -9245, 25, 15पूर्ण, अणु -9211, 13, 14पूर्ण, अणु -9178, 27, 15पूर्ण, अणु -9147,  7, 13पूर्ण,
	अणु -9116, 29, 15पूर्ण, अणु -9087, 15, 14पूर्ण, अणु -9058, 31, 15पूर्ण, अणु -9031,  1, 10पूर्ण,
	अणु -8978, 17, 14पूर्ण, अणु -8929,  9, 13पूर्ण, अणु -8882, 19, 14पूर्ण, अणु -8837,  5, 12पूर्ण,
	अणु -8795, 21, 14पूर्ण, अणु -8754, 11, 13पूर्ण, अणु -8716, 23, 14पूर्ण, अणु -8679,  3, 11पूर्ण,
	अणु -8643, 25, 14पूर्ण, अणु -8609, 13, 13पूर्ण, अणु -8576, 27, 14पूर्ण, अणु -8545,  7, 12पूर्ण,
	अणु -8514, 29, 14पूर्ण, अणु -8485, 15, 13पूर्ण, अणु -8456, 31, 14पूर्ण, अणु -8429,  1,  9पूर्ण,
	अणु -8376, 17, 13पूर्ण, अणु -8327,  9, 12पूर्ण, अणु -8280, 19, 13पूर्ण, अणु -8235,  5, 11पूर्ण,
	अणु -8193, 21, 13पूर्ण, अणु -8152, 11, 12पूर्ण, अणु -8114, 23, 13पूर्ण, अणु -8077,  3, 10पूर्ण,
	अणु -8041, 25, 13पूर्ण, अणु -8007, 13, 12पूर्ण, अणु -7974, 27, 13पूर्ण, अणु -7943,  7, 11पूर्ण,
	अणु -7912, 29, 13पूर्ण, अणु -7883, 15, 12पूर्ण, अणु -7854, 31, 13पूर्ण, अणु -7827,  1,  8पूर्ण,
	अणु -7774, 17, 12पूर्ण, अणु -7724,  9, 11पूर्ण, अणु -7678, 19, 12पूर्ण, अणु -7633,  5, 10पूर्ण,
	अणु -7591, 21, 12पूर्ण, अणु -7550, 11, 11पूर्ण, अणु -7512, 23, 12पूर्ण, अणु -7475,  3,  9पूर्ण,
	अणु -7439, 25, 12पूर्ण, अणु -7405, 13, 11पूर्ण, अणु -7372, 27, 12पूर्ण, अणु -7341,  7, 10पूर्ण,
	अणु -7310, 29, 12पूर्ण, अणु -7281, 15, 11पूर्ण, अणु -7252, 31, 12पूर्ण, अणु -7225,  1,  7पूर्ण,
	अणु -7172, 17, 11पूर्ण, अणु -7122,  9, 10पूर्ण, अणु -7075, 19, 11पूर्ण, अणु -7031,  5,  9पूर्ण,
	अणु -6989, 21, 11पूर्ण, अणु -6948, 11, 10पूर्ण, अणु -6910, 23, 11पूर्ण, अणु -6873,  3,  8पूर्ण,
	अणु -6837, 25, 11पूर्ण, अणु -6803, 13, 10पूर्ण, अणु -6770, 27, 11पूर्ण, अणु -6739,  7,  9पूर्ण,
	अणु -6708, 29, 11पूर्ण, अणु -6679, 15, 10पूर्ण, अणु -6650, 31, 11पूर्ण, अणु -6623,  1,  6पूर्ण,
	अणु -6570, 17, 10पूर्ण, अणु -6520,  9,  9पूर्ण, अणु -6473, 19, 10पूर्ण, अणु -6429,  5,  8पूर्ण,
	अणु -6386, 21, 10पूर्ण, अणु -6346, 11,  9पूर्ण, अणु -6307, 23, 10पूर्ण, अणु -6270,  3,  7पूर्ण,
	अणु -6235, 25, 10पूर्ण, अणु -6201, 13,  9पूर्ण, अणु -6168, 27, 10पूर्ण, अणु -6137,  7,  8पूर्ण,
	अणु -6106, 29, 10पूर्ण, अणु -6077, 15,  9पूर्ण, अणु -6048, 31, 10पूर्ण, अणु -6021,  1,  5पूर्ण,
	अणु -5968, 17,  9पूर्ण, अणु -5918,  9,  8पूर्ण, अणु -5871, 19,  9पूर्ण, अणु -5827,  5,  7पूर्ण,
	अणु -5784, 21,  9पूर्ण, अणु -5744, 11,  8पूर्ण, अणु -5705, 23,  9पूर्ण, अणु -5668,  3,  6पूर्ण,
	अणु -5633, 25,  9पूर्ण, अणु -5599, 13,  8पूर्ण, अणु -5566, 27,  9पूर्ण, अणु -5535,  7,  7पूर्ण,
	अणु -5504, 29,  9पूर्ण, अणु -5475, 15,  8पूर्ण, अणु -5446, 31,  9पूर्ण, अणु -5419,  1,  4पूर्ण,
	अणु -5366, 17,  8पूर्ण, अणु -5316,  9,  7पूर्ण, अणु -5269, 19,  8पूर्ण, अणु -5225,  5,  6पूर्ण,
	अणु -5182, 21,  8पूर्ण, अणु -5142, 11,  7पूर्ण, अणु -5103, 23,  8पूर्ण, अणु -5066,  3,  5पूर्ण,
	अणु -5031, 25,  8पूर्ण, अणु -4997, 13,  7पूर्ण, अणु -4964, 27,  8पूर्ण, अणु -4932,  7,  6पूर्ण,
	अणु -4902, 29,  8पूर्ण, अणु -4873, 15,  7पूर्ण, अणु -4844, 31,  8पूर्ण, अणु -4816,  1,  3पूर्ण,
	अणु -4764, 17,  7पूर्ण, अणु -4714,  9,  6पूर्ण, अणु -4667, 19,  7पूर्ण, अणु -4623,  5,  5पूर्ण,
	अणु -4580, 21,  7पूर्ण, अणु -4540, 11,  6पूर्ण, अणु -4501, 23,  7पूर्ण, अणु -4464,  3,  4पूर्ण,
	अणु -4429, 25,  7पूर्ण, अणु -4395, 13,  6पूर्ण, अणु -4362, 27,  7पूर्ण, अणु -4330,  7,  5पूर्ण,
	अणु -4300, 29,  7पूर्ण, अणु -4270, 15,  6पूर्ण, अणु -4242, 31,  7पूर्ण, अणु -4214,  1,  2पूर्ण,
	अणु -4162, 17,  6पूर्ण, अणु -4112,  9,  5पूर्ण, अणु -4065, 19,  6पूर्ण, अणु -4021,  5,  4पूर्ण,
	अणु -3978, 21,  6पूर्ण, अणु -3938, 11,  5पूर्ण, अणु -3899, 23,  6पूर्ण, अणु -3862,  3,  3पूर्ण,
	अणु -3827, 25,  6पूर्ण, अणु -3793, 13,  5पूर्ण, अणु -3760, 27,  6पूर्ण, अणु -3728,  7,  4पूर्ण,
	अणु -3698, 29,  6पूर्ण, अणु -3668, 15,  5पूर्ण, अणु -3640, 31,  6पूर्ण, अणु -3612,  1,  1पूर्ण,
	अणु -3560, 17,  5पूर्ण, अणु -3510,  9,  4पूर्ण, अणु -3463, 19,  5पूर्ण, अणु -3419,  5,  3पूर्ण,
	अणु -3376, 21,  5पूर्ण, अणु -3336, 11,  4पूर्ण, अणु -3297, 23,  5पूर्ण, अणु -3260,  3,  2पूर्ण,
	अणु -3225, 25,  5पूर्ण, अणु -3191, 13,  4पूर्ण, अणु -3158, 27,  5पूर्ण, अणु -3126,  7,  3पूर्ण,
	अणु -3096, 29,  5पूर्ण, अणु -3066, 15,  4पूर्ण, अणु -3038, 31,  5पूर्ण, अणु -3010,  1,  0पूर्ण,
	अणु -2958, 17,  4पूर्ण, अणु -2908,  9,  3पूर्ण, अणु -2861, 19,  4पूर्ण, अणु -2816,  5,  2पूर्ण,
	अणु -2774, 21,  4पूर्ण, अणु -2734, 11,  3पूर्ण, अणु -2695, 23,  4पूर्ण, अणु -2658,  3,  1पूर्ण,
	अणु -2623, 25,  4पूर्ण, अणु -2589, 13,  3पूर्ण, अणु -2556, 27,  4पूर्ण, अणु -2524,  7,  2पूर्ण,
	अणु -2494, 29,  4पूर्ण, अणु -2464, 15,  3पूर्ण, अणु -2436, 31,  4पूर्ण, अणु -2408,  2,  0पूर्ण,
	अणु -2356, 17,  3पूर्ण, अणु -2306,  9,  2पूर्ण, अणु -2259, 19,  3पूर्ण, अणु -2214,  5,  1पूर्ण,
	अणु -2172, 21,  3पूर्ण, अणु -2132, 11,  2पूर्ण, अणु -2093, 23,  3पूर्ण, अणु -2056,  3,  0पूर्ण,
	अणु -2021, 25,  3पूर्ण, अणु -1987, 13,  2पूर्ण, अणु -1954, 27,  3पूर्ण, अणु -1922,  7,  1पूर्ण,
	अणु -1892, 29,  3पूर्ण, अणु -1862, 15,  2पूर्ण, अणु -1834, 31,  3पूर्ण, अणु -1806,  4,  0पूर्ण,
	अणु -1754, 17,  2पूर्ण, अणु -1704,  9,  1पूर्ण, अणु -1657, 19,  2पूर्ण, अणु -1612,  5,  0पूर्ण,
	अणु -1570, 21,  2पूर्ण, अणु -1530, 11,  1पूर्ण, अणु -1491, 23,  2पूर्ण, अणु -1454,  6,  0पूर्ण,
	अणु -1419, 25,  2पूर्ण, अणु -1384, 13,  1पूर्ण, अणु -1352, 27,  2पूर्ण, अणु -1320,  7,  0पूर्ण,
	अणु -1290, 29,  2पूर्ण, अणु -1260, 15,  1पूर्ण, अणु -1232, 31,  2पूर्ण, अणु -1204,  8,  0पूर्ण,
	अणु -1151, 17,  1पूर्ण, अणु -1102,  9,  0पूर्ण, अणु -1055, 19,  1पूर्ण, अणु -1010, 10,  0पूर्ण,
	अणु  -968, 21,  1पूर्ण, अणु  -928, 11,  0पूर्ण, अणु  -889, 23,  1पूर्ण, अणु  -852, 12,  0पूर्ण,
	अणु  -816, 25,  1पूर्ण, अणु  -782, 13,  0पूर्ण, अणु  -750, 27,  1पूर्ण, अणु  -718, 14,  0पूर्ण,
	अणु  -688, 29,  1पूर्ण, अणु  -658, 15,  0पूर्ण, अणु  -630, 31,  1पूर्ण, अणु  -602, 16,  0पूर्ण,
	अणु  -549, 17,  0पूर्ण, अणु  -500, 18,  0पूर्ण, अणु  -453, 19,  0पूर्ण, अणु  -408, 20,  0पूर्ण,
	अणु  -366, 21,  0पूर्ण, अणु  -325, 22,  0पूर्ण, अणु  -287, 23,  0पूर्ण, अणु  -250, 24,  0पूर्ण,
	अणु  -214, 25,  0पूर्ण, अणु  -180, 26,  0पूर्ण, अणु  -148, 27,  0पूर्ण, अणु  -116, 28,  0पूर्ण,
	अणु   -86, 29,  0पूर्ण, अणु   -56, 30,  0पूर्ण, अणु   -28, 31,  0पूर्ण, अणु     0,  0,  0पूर्ण,
पूर्ण;

अटल पूर्णांक snd_soc_get_volsw_2r_st(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	पूर्णांक val[2], val2[2], i;

	val[0] = snd_soc_component_पढ़ो(component, reg) & 0x3f;
	val[1] = (snd_soc_component_पढ़ो(component, PM860X_SIDETONE_SHIFT) >> 4) & 0xf;
	val2[0] = snd_soc_component_पढ़ो(component, reg2) & 0x3f;
	val2[1] = (snd_soc_component_पढ़ो(component, PM860X_SIDETONE_SHIFT)) & 0xf;

	क्रम (i = 0; i < ARRAY_SIZE(st_table); i++) अणु
		अगर ((st_table[i].m == val[0]) && (st_table[i].n == val[1]))
			ucontrol->value.पूर्णांकeger.value[0] = i;
		अगर ((st_table[i].m == val2[0]) && (st_table[i].n == val2[1]))
			ucontrol->value.पूर्णांकeger.value[1] = i;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_put_volsw_2r_st(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	पूर्णांक err;
	अचिन्हित पूर्णांक val, val2;

	val = ucontrol->value.पूर्णांकeger.value[0];
	val2 = ucontrol->value.पूर्णांकeger.value[1];

	अगर (val >= ARRAY_SIZE(st_table) || val2 >= ARRAY_SIZE(st_table))
		वापस -EINVAL;

	err = snd_soc_component_update_bits(component, reg, 0x3f, st_table[val].m);
	अगर (err < 0)
		वापस err;
	err = snd_soc_component_update_bits(component, PM860X_SIDETONE_SHIFT, 0xf0,
				  st_table[val].n << 4);
	अगर (err < 0)
		वापस err;

	err = snd_soc_component_update_bits(component, reg2, 0x3f, st_table[val2].m);
	अगर (err < 0)
		वापस err;
	err = snd_soc_component_update_bits(component, PM860X_SIDETONE_SHIFT, 0x0f,
				  st_table[val2].n);
	वापस err;
पूर्ण

अटल पूर्णांक snd_soc_get_volsw_2r_out(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक max = mc->max, val, val2;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;

	val = snd_soc_component_पढ़ो(component, reg) >> shअगरt;
	val2 = snd_soc_component_पढ़ो(component, reg2) >> shअगरt;
	ucontrol->value.पूर्णांकeger.value[0] = (max - val) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (max - val2) & mask;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_put_volsw_2r_out(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	पूर्णांक err;
	अचिन्हित पूर्णांक val, val2, val_mask;

	val_mask = mask << shअगरt;
	val = ((max - ucontrol->value.पूर्णांकeger.value[0]) & mask);
	val2 = ((max - ucontrol->value.पूर्णांकeger.value[1]) & mask);

	val = val << shअगरt;
	val2 = val2 << shअगरt;

	err = snd_soc_component_update_bits(component, reg, val_mask, val);
	अगर (err < 0)
		वापस err;

	err = snd_soc_component_update_bits(component, reg2, val_mask, val2);
	वापस err;
पूर्ण

/* DAPM Widget Events */
/*
 * A lot रेजिस्टरs are beदीर्घ to RSYNC करोमुख्य. It requires enabling RSYNC bit
 * after updating these रेजिस्टरs. Otherwise, these updated रेजिस्टरs won't
 * be effective.
 */
अटल पूर्णांक pm860x_rsync_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	/*
	 * In order to aव्योम current on the load, mute घातer-on and घातer-off
	 * should be transients.
	 * Unmute by DAC_MUTE. It should be unmuted when DAPM sequence is
	 * finished.
	 */
	snd_soc_component_update_bits(component, PM860X_DAC_OFFSET, DAC_MUTE, 0);
	snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
			    RSYNC_CHANGE, RSYNC_CHANGE);
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_dac_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक dac = 0;
	पूर्णांक data;

	अगर (!म_भेद(w->name, "Left DAC"))
		dac = DAC_LEFT;
	अगर (!म_भेद(w->name, "Right DAC"))
		dac = DAC_RIGHT;
	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (dac) अणु
			/* Auto mute in घातer-on sequence. */
			dac |= MODULATOR;
			snd_soc_component_update_bits(component, PM860X_DAC_OFFSET,
					    DAC_MUTE, DAC_MUTE);
			snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
					    RSYNC_CHANGE, RSYNC_CHANGE);
			/* update dac */
			snd_soc_component_update_bits(component, PM860X_DAC_EN_2,
					    dac, dac);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		अगर (dac) अणु
			/* Auto mute in घातer-off sequence. */
			snd_soc_component_update_bits(component, PM860X_DAC_OFFSET,
					    DAC_MUTE, DAC_MUTE);
			snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
					    RSYNC_CHANGE, RSYNC_CHANGE);
			/* update dac */
			data = snd_soc_component_पढ़ो(component, PM860X_DAC_EN_2);
			data &= ~dac;
			अगर (!(data & (DAC_LEFT | DAC_RIGHT)))
				data &= ~MODULATOR;
			snd_soc_component_ग_लिखो(component, PM860X_DAC_EN_2, data);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *pm860x_opamp_texts[] = अणु"-50%", "-25%", "0%", "75%"पूर्ण;

अटल स्थिर अक्षर *pm860x_pa_texts[] = अणु"-33%", "0%", "33%", "66%"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pm860x_hs1_opamp_क्रमागत,
			    PM860X_HS1_CTRL, 5, pm860x_opamp_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_hs2_opamp_क्रमागत,
			    PM860X_HS2_CTRL, 5, pm860x_opamp_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_hs1_pa_क्रमागत,
			    PM860X_HS1_CTRL, 3, pm860x_pa_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_hs2_pa_क्रमागत,
			    PM860X_HS2_CTRL, 3, pm860x_pa_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_lo1_opamp_क्रमागत,
			    PM860X_LO1_CTRL, 5, pm860x_opamp_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_lo2_opamp_क्रमागत,
			    PM860X_LO2_CTRL, 5, pm860x_opamp_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_lo1_pa_क्रमागत,
			    PM860X_LO1_CTRL, 3, pm860x_pa_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_lo2_pa_क्रमागत,
			    PM860X_LO2_CTRL, 3, pm860x_pa_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_spk_pa_क्रमागत,
			    PM860X_EAR_CTRL_1, 5, pm860x_pa_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_ear_pa_क्रमागत,
			    PM860X_EAR_CTRL_2, 0, pm860x_pa_texts);

अटल SOC_ENUM_SINGLE_DECL(pm860x_spk_ear_opamp_क्रमागत,
			    PM860X_EAR_CTRL_1, 3, pm860x_opamp_texts);

अटल स्थिर काष्ठा snd_kcontrol_new pm860x_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("ADC Capture Volume", PM860X_ADC_ANA_2,
			PM860X_ADC_ANA_3, 6, 3, 0, adc_tlv),
	SOC_DOUBLE_TLV("AUX Capture Volume", PM860X_ADC_ANA_3, 0, 3, 7, 0,
			aux_tlv),
	SOC_SINGLE_TLV("MIC1 Capture Volume", PM860X_ADC_ANA_2, 0, 7, 0,
			mic_tlv),
	SOC_SINGLE_TLV("MIC3 Capture Volume", PM860X_ADC_ANA_2, 3, 7, 0,
			mic_tlv),
	SOC_DOUBLE_R_EXT_TLV("Sidetone Volume", PM860X_SIDETONE_L_GAIN,
			     PM860X_SIDETONE_R_GAIN, 0, ARRAY_SIZE(st_table)-1,
			     0, snd_soc_get_volsw_2r_st,
			     snd_soc_put_volsw_2r_st, st_tlv),
	SOC_SINGLE_TLV("Speaker Playback Volume", PM860X_EAR_CTRL_1,
			0, 7, 0, out_tlv),
	SOC_DOUBLE_R_TLV("Line Playback Volume", PM860X_LO1_CTRL,
			 PM860X_LO2_CTRL, 0, 7, 0, out_tlv),
	SOC_DOUBLE_R_TLV("Headset Playback Volume", PM860X_HS1_CTRL,
			 PM860X_HS2_CTRL, 0, 7, 0, out_tlv),
	SOC_DOUBLE_R_EXT_TLV("Hifi Left Playback Volume",
			     PM860X_HIFIL_GAIN_LEFT,
			     PM860X_HIFIL_GAIN_RIGHT, 0, 63, 0,
			     snd_soc_get_volsw_2r_out,
			     snd_soc_put_volsw_2r_out, dpga_tlv),
	SOC_DOUBLE_R_EXT_TLV("Hifi Right Playback Volume",
			     PM860X_HIFIR_GAIN_LEFT,
			     PM860X_HIFIR_GAIN_RIGHT, 0, 63, 0,
			     snd_soc_get_volsw_2r_out,
			     snd_soc_put_volsw_2r_out, dpga_tlv),
	SOC_DOUBLE_R_EXT_TLV("Lofi Playback Volume", PM860X_LOFI_GAIN_LEFT,
			     PM860X_LOFI_GAIN_RIGHT, 0, 63, 0,
			     snd_soc_get_volsw_2r_out,
			     snd_soc_put_volsw_2r_out, dpga_tlv),
	SOC_ENUM("Headset1 Operational Amplifier Current",
		 pm860x_hs1_opamp_क्रमागत),
	SOC_ENUM("Headset2 Operational Amplifier Current",
		 pm860x_hs2_opamp_क्रमागत),
	SOC_ENUM("Headset1 Amplifier Current", pm860x_hs1_pa_क्रमागत),
	SOC_ENUM("Headset2 Amplifier Current", pm860x_hs2_pa_क्रमागत),
	SOC_ENUM("Lineout1 Operational Amplifier Current",
		 pm860x_lo1_opamp_क्रमागत),
	SOC_ENUM("Lineout2 Operational Amplifier Current",
		 pm860x_lo2_opamp_क्रमागत),
	SOC_ENUM("Lineout1 Amplifier Current", pm860x_lo1_pa_क्रमागत),
	SOC_ENUM("Lineout2 Amplifier Current", pm860x_lo2_pa_क्रमागत),
	SOC_ENUM("Speaker Operational Amplifier Current",
		 pm860x_spk_ear_opamp_क्रमागत),
	SOC_ENUM("Speaker Amplifier Current", pm860x_spk_pa_क्रमागत),
	SOC_ENUM("Earpiece Amplifier Current", pm860x_ear_pa_क्रमागत),
पूर्ण;

/*
 * DAPM Controls
 */

/* AUX1 Switch */
अटल स्थिर काष्ठा snd_kcontrol_new aux1_चयन_controls =
	SOC_DAPM_SINGLE("Switch", PM860X_ANA_TO_ANA, 4, 1, 0);

/* AUX2 Switch */
अटल स्थिर काष्ठा snd_kcontrol_new aux2_चयन_controls =
	SOC_DAPM_SINGLE("Switch", PM860X_ANA_TO_ANA, 5, 1, 0);

/* Left Ex. PA Switch */
अटल स्थिर काष्ठा snd_kcontrol_new lepa_चयन_controls =
	SOC_DAPM_SINGLE("Switch", PM860X_DAC_EN_2, 2, 1, 0);

/* Right Ex. PA Switch */
अटल स्थिर काष्ठा snd_kcontrol_new repa_चयन_controls =
	SOC_DAPM_SINGLE("Switch", PM860X_DAC_EN_2, 1, 1, 0);

/* I2S Mux / Mux9 */
अटल स्थिर अक्षर *i2s_din_text[] = अणु
	"DIN", "DIN1",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(i2s_din_क्रमागत,
			    PM860X_I2S_IFACE_3, 1, i2s_din_text);

अटल स्थिर काष्ठा snd_kcontrol_new i2s_din_mux =
	SOC_DAPM_ENUM("I2S DIN Mux", i2s_din_क्रमागत);

/* I2S Mic Mux / Mux8 */
अटल स्थिर अक्षर *i2s_mic_text[] = अणु
	"Ex PA", "ADC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(i2s_mic_क्रमागत,
			    PM860X_I2S_IFACE_3, 4, i2s_mic_text);

अटल स्थिर काष्ठा snd_kcontrol_new i2s_mic_mux =
	SOC_DAPM_ENUM("I2S Mic Mux", i2s_mic_क्रमागत);

/* ADCL Mux / Mux2 */
अटल स्थिर अक्षर *adcl_text[] = अणु
	"ADCR", "ADCL",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adcl_क्रमागत,
			    PM860X_PCM_IFACE_3, 4, adcl_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcl_mux =
	SOC_DAPM_ENUM("ADC Left Mux", adcl_क्रमागत);

/* ADCR Mux / Mux3 */
अटल स्थिर अक्षर *adcr_text[] = अणु
	"ADCL", "ADCR",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adcr_क्रमागत,
			    PM860X_PCM_IFACE_3, 2, adcr_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcr_mux =
	SOC_DAPM_ENUM("ADC Right Mux", adcr_क्रमागत);

/* ADCR EC Mux / Mux6 */
अटल स्थिर अक्षर *adcr_ec_text[] = अणु
	"ADCR", "EC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adcr_ec_क्रमागत,
			    PM860X_ADC_EN_2, 3, adcr_ec_text);

अटल स्थिर काष्ठा snd_kcontrol_new adcr_ec_mux =
	SOC_DAPM_ENUM("ADCR EC Mux", adcr_ec_क्रमागत);

/* EC Mux / Mux4 */
अटल स्थिर अक्षर *ec_text[] = अणु
	"Left", "Right", "Left + Right",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ec_क्रमागत,
			    PM860X_EC_PATH, 1, ec_text);

अटल स्थिर काष्ठा snd_kcontrol_new ec_mux =
	SOC_DAPM_ENUM("EC Mux", ec_क्रमागत);

अटल स्थिर अक्षर *dac_text[] = अणु
	"No input", "Right", "Left", "No input",
पूर्ण;

/* DAC Headset 1 Mux / Mux10 */
अटल SOC_ENUM_SINGLE_DECL(dac_hs1_क्रमागत,
			    PM860X_ANA_INPUT_SEL_1, 0, dac_text);

अटल स्थिर काष्ठा snd_kcontrol_new dac_hs1_mux =
	SOC_DAPM_ENUM("DAC HS1 Mux", dac_hs1_क्रमागत);

/* DAC Headset 2 Mux / Mux11 */
अटल SOC_ENUM_SINGLE_DECL(dac_hs2_क्रमागत,
			    PM860X_ANA_INPUT_SEL_1, 2, dac_text);

अटल स्थिर काष्ठा snd_kcontrol_new dac_hs2_mux =
	SOC_DAPM_ENUM("DAC HS2 Mux", dac_hs2_क्रमागत);

/* DAC Lineout 1 Mux / Mux12 */
अटल SOC_ENUM_SINGLE_DECL(dac_lo1_क्रमागत,
			    PM860X_ANA_INPUT_SEL_1, 4, dac_text);

अटल स्थिर काष्ठा snd_kcontrol_new dac_lo1_mux =
	SOC_DAPM_ENUM("DAC LO1 Mux", dac_lo1_क्रमागत);

/* DAC Lineout 2 Mux / Mux13 */
अटल SOC_ENUM_SINGLE_DECL(dac_lo2_क्रमागत,
			    PM860X_ANA_INPUT_SEL_1, 6, dac_text);

अटल स्थिर काष्ठा snd_kcontrol_new dac_lo2_mux =
	SOC_DAPM_ENUM("DAC LO2 Mux", dac_lo2_क्रमागत);

/* DAC Spearker Earphone Mux / Mux14 */
अटल SOC_ENUM_SINGLE_DECL(dac_spk_ear_क्रमागत,
			    PM860X_ANA_INPUT_SEL_2, 0, dac_text);

अटल स्थिर काष्ठा snd_kcontrol_new dac_spk_ear_mux =
	SOC_DAPM_ENUM("DAC SP Mux", dac_spk_ear_क्रमागत);

/* Headset 1 Mux / Mux15 */
अटल स्थिर अक्षर *in_text[] = अणु
	"Digital", "Analog",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hs1_क्रमागत,
			    PM860X_ANA_TO_ANA, 0, in_text);

अटल स्थिर काष्ठा snd_kcontrol_new hs1_mux =
	SOC_DAPM_ENUM("Headset1 Mux", hs1_क्रमागत);

/* Headset 2 Mux / Mux16 */
अटल SOC_ENUM_SINGLE_DECL(hs2_क्रमागत,
			    PM860X_ANA_TO_ANA, 1, in_text);

अटल स्थिर काष्ठा snd_kcontrol_new hs2_mux =
	SOC_DAPM_ENUM("Headset2 Mux", hs2_क्रमागत);

/* Lineout 1 Mux / Mux17 */
अटल SOC_ENUM_SINGLE_DECL(lo1_क्रमागत,
			    PM860X_ANA_TO_ANA, 2, in_text);

अटल स्थिर काष्ठा snd_kcontrol_new lo1_mux =
	SOC_DAPM_ENUM("Lineout1 Mux", lo1_क्रमागत);

/* Lineout 2 Mux / Mux18 */
अटल SOC_ENUM_SINGLE_DECL(lo2_क्रमागत,
			    PM860X_ANA_TO_ANA, 3, in_text);

अटल स्थिर काष्ठा snd_kcontrol_new lo2_mux =
	SOC_DAPM_ENUM("Lineout2 Mux", lo2_क्रमागत);

/* Speaker Earpiece Demux */
अटल स्थिर अक्षर *spk_text[] = अणु
	"Earpiece", "Speaker",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(spk_क्रमागत,
			    PM860X_ANA_TO_ANA, 6, spk_text);

अटल स्थिर काष्ठा snd_kcontrol_new spk_demux =
	SOC_DAPM_ENUM("Speaker Earpiece Demux", spk_क्रमागत);

/* MIC Mux / Mux1 */
अटल स्थिर अक्षर *mic_text[] = अणु
	"Mic 1", "Mic 2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mic_क्रमागत,
			    PM860X_ADC_ANA_4, 4, mic_text);

अटल स्थिर काष्ठा snd_kcontrol_new mic_mux =
	SOC_DAPM_ENUM("MIC Mux", mic_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget pm860x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("PCM SDI", "PCM Playback", 0,
			    PM860X_ADC_EN_2, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PCM SDO", "PCM Capture", 0,
			     PM860X_PCM_IFACE_3, 1, 1),


	SND_SOC_DAPM_AIF_IN("I2S DIN", "I2S Playback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("I2S DIN1", "I2S Playback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("I2S DOUT", "I2S Capture", 0,
			     PM860X_I2S_IFACE_3, 5, 1),
	SND_SOC_DAPM_SUPPLY("I2S CLK", PM860X_DAC_EN_2, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("I2S Mic Mux", SND_SOC_NOPM, 0, 0, &i2s_mic_mux),
	SND_SOC_DAPM_MUX("ADC Left Mux", SND_SOC_NOPM, 0, 0, &adcl_mux),
	SND_SOC_DAPM_MUX("ADC Right Mux", SND_SOC_NOPM, 0, 0, &adcr_mux),
	SND_SOC_DAPM_MUX("EC Mux", SND_SOC_NOPM, 0, 0, &ec_mux),
	SND_SOC_DAPM_MUX("ADCR EC Mux", SND_SOC_NOPM, 0, 0, &adcr_ec_mux),
	SND_SOC_DAPM_SWITCH("Left EPA", SND_SOC_NOPM, 0, 0,
			    &lepa_चयन_controls),
	SND_SOC_DAPM_SWITCH("Right EPA", SND_SOC_NOPM, 0, 0,
			    &repa_चयन_controls),

	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "Left ADC MOD", PM860X_ADC_EN_1,
			 0, 1, 1, 0),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "Right ADC MOD", PM860X_ADC_EN_1,
			 1, 1, 1, 0),
	SND_SOC_DAPM_ADC("Left ADC", शून्य, PM860X_ADC_EN_2, 5, 0),
	SND_SOC_DAPM_ADC("Right ADC", शून्य, PM860X_ADC_EN_2, 4, 0),

	SND_SOC_DAPM_SWITCH("AUX1 Switch", SND_SOC_NOPM, 0, 0,
			    &aux1_चयन_controls),
	SND_SOC_DAPM_SWITCH("AUX2 Switch", SND_SOC_NOPM, 0, 0,
			    &aux2_चयन_controls),

	SND_SOC_DAPM_MUX("MIC Mux", SND_SOC_NOPM, 0, 0, &mic_mux),
	SND_SOC_DAPM_MICBIAS("Mic1 Bias", PM860X_ADC_ANA_1, 2, 0),
	SND_SOC_DAPM_MICBIAS("Mic3 Bias", PM860X_ADC_ANA_1, 7, 0),
	SND_SOC_DAPM_PGA("MIC1 Volume", PM860X_ADC_EN_1, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIC3 Volume", PM860X_ADC_EN_1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUX1 Volume", PM860X_ADC_EN_1, 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUX2 Volume", PM860X_ADC_EN_1, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Sidetone PGA", PM860X_ADC_EN_2, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Lofi PGA", PM860X_ADC_EN_2, 2, 0, शून्य, 0),

	SND_SOC_DAPM_INPUT("AUX1"),
	SND_SOC_DAPM_INPUT("AUX2"),
	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),
	SND_SOC_DAPM_INPUT("MIC3P"),
	SND_SOC_DAPM_INPUT("MIC3N"),

	SND_SOC_DAPM_DAC_E("Left DAC", शून्य, SND_SOC_NOPM, 0, 0,
			   pm860x_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_DAC_E("Right DAC", शून्य, SND_SOC_NOPM, 0, 0,
			   pm860x_dac_event,
			   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_MUX("I2S DIN Mux", SND_SOC_NOPM, 0, 0, &i2s_din_mux),
	SND_SOC_DAPM_MUX("DAC HS1 Mux", SND_SOC_NOPM, 0, 0, &dac_hs1_mux),
	SND_SOC_DAPM_MUX("DAC HS2 Mux", SND_SOC_NOPM, 0, 0, &dac_hs2_mux),
	SND_SOC_DAPM_MUX("DAC LO1 Mux", SND_SOC_NOPM, 0, 0, &dac_lo1_mux),
	SND_SOC_DAPM_MUX("DAC LO2 Mux", SND_SOC_NOPM, 0, 0, &dac_lo2_mux),
	SND_SOC_DAPM_MUX("DAC SP Mux", SND_SOC_NOPM, 0, 0, &dac_spk_ear_mux),
	SND_SOC_DAPM_MUX("Headset1 Mux", SND_SOC_NOPM, 0, 0, &hs1_mux),
	SND_SOC_DAPM_MUX("Headset2 Mux", SND_SOC_NOPM, 0, 0, &hs2_mux),
	SND_SOC_DAPM_MUX("Lineout1 Mux", SND_SOC_NOPM, 0, 0, &lo1_mux),
	SND_SOC_DAPM_MUX("Lineout2 Mux", SND_SOC_NOPM, 0, 0, &lo2_mux),
	SND_SOC_DAPM_MUX("Speaker Earpiece Demux", SND_SOC_NOPM, 0, 0,
			 &spk_demux),


	SND_SOC_DAPM_PGA("Headset1 PGA", PM860X_DAC_EN_1, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Headset2 PGA", PM860X_DAC_EN_1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("HS1"),
	SND_SOC_DAPM_OUTPUT("HS2"),
	SND_SOC_DAPM_PGA("Lineout1 PGA", PM860X_DAC_EN_1, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Lineout2 PGA", PM860X_DAC_EN_1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("LINEOUT1"),
	SND_SOC_DAPM_OUTPUT("LINEOUT2"),
	SND_SOC_DAPM_PGA("Earpiece PGA", PM860X_DAC_EN_1, 4, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("EARP"),
	SND_SOC_DAPM_OUTPUT("EARN"),
	SND_SOC_DAPM_PGA("Speaker PGA", PM860X_DAC_EN_1, 5, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("LSP"),
	SND_SOC_DAPM_OUTPUT("LSN"),
	SND_SOC_DAPM_REG(snd_soc_dapm_supply, "VCODEC", PM860X_AUDIO_SUPPLIES_2,
			 0, SUPPLY_MASK, SUPPLY_MASK, 0),

	PM860X_DAPM_OUTPUT("RSYNC", pm860x_rsync_event),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pm860x_dapm_routes[] = अणु
	/* supply */
	अणु"Left DAC", शून्य, "VCODEC"पूर्ण,
	अणु"Right DAC", शून्य, "VCODEC"पूर्ण,
	अणु"Left ADC", शून्य, "VCODEC"पूर्ण,
	अणु"Right ADC", शून्य, "VCODEC"पूर्ण,
	अणु"Left ADC", शून्य, "Left ADC MOD"पूर्ण,
	अणु"Right ADC", शून्य, "Right ADC MOD"पूर्ण,

	/* I2S Clock */
	अणु"I2S DIN", शून्य, "I2S CLK"पूर्ण,
	अणु"I2S DIN1", शून्य, "I2S CLK"पूर्ण,
	अणु"I2S DOUT", शून्य, "I2S CLK"पूर्ण,

	/* PCM/AIF1 Inमाला_दो */
	अणु"PCM SDO", शून्य, "ADC Left Mux"पूर्ण,
	अणु"PCM SDO", शून्य, "ADCR EC Mux"पूर्ण,

	/* PCM/AFI2 Outमाला_दो */
	अणु"Lofi PGA", शून्य, "PCM SDI"पूर्ण,
	अणु"Lofi PGA", शून्य, "Sidetone PGA"पूर्ण,
	अणु"Left DAC", शून्य, "Lofi PGA"पूर्ण,
	अणु"Right DAC", शून्य, "Lofi PGA"पूर्ण,

	/* I2S/AIF2 Inमाला_दो */
	अणु"MIC Mux", "Mic 1", "MIC1P"पूर्ण,
	अणु"MIC Mux", "Mic 1", "MIC1N"पूर्ण,
	अणु"MIC Mux", "Mic 2", "MIC2P"पूर्ण,
	अणु"MIC Mux", "Mic 2", "MIC2N"पूर्ण,
	अणु"MIC1 Volume", शून्य, "MIC Mux"पूर्ण,
	अणु"MIC3 Volume", शून्य, "MIC3P"पूर्ण,
	अणु"MIC3 Volume", शून्य, "MIC3N"पूर्ण,
	अणु"Left ADC", शून्य, "MIC1 Volume"पूर्ण,
	अणु"Right ADC", शून्य, "MIC3 Volume"पूर्ण,
	अणु"ADC Left Mux", "ADCR", "Right ADC"पूर्ण,
	अणु"ADC Left Mux", "ADCL", "Left ADC"पूर्ण,
	अणु"ADC Right Mux", "ADCL", "Left ADC"पूर्ण,
	अणु"ADC Right Mux", "ADCR", "Right ADC"पूर्ण,
	अणु"Left EPA", "Switch", "Left DAC"पूर्ण,
	अणु"Right EPA", "Switch", "Right DAC"पूर्ण,
	अणु"EC Mux", "Left", "Left DAC"पूर्ण,
	अणु"EC Mux", "Right", "Right DAC"पूर्ण,
	अणु"EC Mux", "Left + Right", "Left DAC"पूर्ण,
	अणु"EC Mux", "Left + Right", "Right DAC"पूर्ण,
	अणु"ADCR EC Mux", "ADCR", "ADC Right Mux"पूर्ण,
	अणु"ADCR EC Mux", "EC", "EC Mux"पूर्ण,
	अणु"I2S Mic Mux", "Ex PA", "Left EPA"पूर्ण,
	अणु"I2S Mic Mux", "Ex PA", "Right EPA"पूर्ण,
	अणु"I2S Mic Mux", "ADC", "ADC Left Mux"पूर्ण,
	अणु"I2S Mic Mux", "ADC", "ADCR EC Mux"पूर्ण,
	अणु"I2S DOUT", शून्य, "I2S Mic Mux"पूर्ण,

	/* I2S/AIF2 Outमाला_दो */
	अणु"I2S DIN Mux", "DIN", "I2S DIN"पूर्ण,
	अणु"I2S DIN Mux", "DIN1", "I2S DIN1"पूर्ण,
	अणु"Left DAC", शून्य, "I2S DIN Mux"पूर्ण,
	अणु"Right DAC", शून्य, "I2S DIN Mux"पूर्ण,
	अणु"DAC HS1 Mux", "Left", "Left DAC"पूर्ण,
	अणु"DAC HS1 Mux", "Right", "Right DAC"पूर्ण,
	अणु"DAC HS2 Mux", "Left", "Left DAC"पूर्ण,
	अणु"DAC HS2 Mux", "Right", "Right DAC"पूर्ण,
	अणु"DAC LO1 Mux", "Left", "Left DAC"पूर्ण,
	अणु"DAC LO1 Mux", "Right", "Right DAC"पूर्ण,
	अणु"DAC LO2 Mux", "Left", "Left DAC"पूर्ण,
	अणु"DAC LO2 Mux", "Right", "Right DAC"पूर्ण,
	अणु"Headset1 Mux", "Digital", "DAC HS1 Mux"पूर्ण,
	अणु"Headset2 Mux", "Digital", "DAC HS2 Mux"पूर्ण,
	अणु"Lineout1 Mux", "Digital", "DAC LO1 Mux"पूर्ण,
	अणु"Lineout2 Mux", "Digital", "DAC LO2 Mux"पूर्ण,
	अणु"Headset1 PGA", शून्य, "Headset1 Mux"पूर्ण,
	अणु"Headset2 PGA", शून्य, "Headset2 Mux"पूर्ण,
	अणु"Lineout1 PGA", शून्य, "Lineout1 Mux"पूर्ण,
	अणु"Lineout2 PGA", शून्य, "Lineout2 Mux"पूर्ण,
	अणु"DAC SP Mux", "Left", "Left DAC"पूर्ण,
	अणु"DAC SP Mux", "Right", "Right DAC"पूर्ण,
	अणु"Speaker Earpiece Demux", "Speaker", "DAC SP Mux"पूर्ण,
	अणु"Speaker PGA", शून्य, "Speaker Earpiece Demux"पूर्ण,
	अणु"Earpiece PGA", शून्य, "Speaker Earpiece Demux"पूर्ण,

	अणु"RSYNC", शून्य, "Headset1 PGA"पूर्ण,
	अणु"RSYNC", शून्य, "Headset2 PGA"पूर्ण,
	अणु"RSYNC", शून्य, "Lineout1 PGA"पूर्ण,
	अणु"RSYNC", शून्य, "Lineout2 PGA"पूर्ण,
	अणु"RSYNC", शून्य, "Speaker PGA"पूर्ण,
	अणु"RSYNC", शून्य, "Speaker PGA"पूर्ण,
	अणु"RSYNC", शून्य, "Earpiece PGA"पूर्ण,
	अणु"RSYNC", शून्य, "Earpiece PGA"पूर्ण,

	अणु"HS1", शून्य, "RSYNC"पूर्ण,
	अणु"HS2", शून्य, "RSYNC"पूर्ण,
	अणु"LINEOUT1", शून्य, "RSYNC"पूर्ण,
	अणु"LINEOUT2", शून्य, "RSYNC"पूर्ण,
	अणु"LSP", शून्य, "RSYNC"पूर्ण,
	अणु"LSN", शून्य, "RSYNC"पूर्ण,
	अणु"EARP", शून्य, "RSYNC"पूर्ण,
	अणु"EARN", शून्य, "RSYNC"पूर्ण,
पूर्ण;

/*
 * Use MUTE_LEFT & MUTE_RIGHT to implement digital mute.
 * These bits can also be used to mute.
 */
अटल पूर्णांक pm860x_mute_stream(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक data = 0, mask = MUTE_LEFT | MUTE_RIGHT;

	अगर (mute)
		data = mask;
	snd_soc_component_update_bits(component, PM860X_DAC_OFFSET, mask, data);
	snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
			    RSYNC_CHANGE, RSYNC_CHANGE);
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित अक्षर inf = 0, mask = 0;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		inf &= ~PCM_INF2_18WL;
		अवरोध;
	हाल 18:
		inf |= PCM_INF2_18WL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	mask |= PCM_INF2_18WL;
	snd_soc_component_update_bits(component, PM860X_PCM_IFACE_2, mask, inf);

	/* sample rate */
	चयन (params_rate(params)) अणु
	हाल 8000:
		inf = 0;
		अवरोध;
	हाल 16000:
		inf = 3;
		अवरोध;
	हाल 32000:
		inf = 6;
		अवरोध;
	हाल 48000:
		inf = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, PM860X_PCM_RATE, 0x0f, inf);

	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_pcm_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				  अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर inf = 0, mask = 0;
	पूर्णांक ret = -EINVAL;

	mask |= PCM_INF2_BCLK | PCM_INF2_FS | PCM_INF2_MASTER;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
		अगर (pm860x->dir == PM860X_CLK_सूची_OUT) अणु
			inf |= PCM_INF2_MASTER;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगर (pm860x->dir == PM860X_CLK_सूची_IN) अणु
			inf &= ~PCM_INF2_MASTER;
			ret = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		inf |= PCM_EXACT_I2S;
		ret = 0;
		अवरोध;
	पूर्ण
	mask |= PCM_MODE_MASK;
	अगर (ret)
		वापस ret;
	snd_soc_component_update_bits(component, PM860X_PCM_IFACE_2, mask, inf);
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);

	अगर (dir == PM860X_CLK_सूची_OUT)
		pm860x->dir = PM860X_CLK_सूची_OUT;
	अन्यथा	/* Slave mode is not supported */
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित अक्षर inf;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		inf = 0;
		अवरोध;
	हाल 18:
		inf = PCM_INF2_18WL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_2, PCM_INF2_18WL, inf);

	/* sample rate */
	चयन (params_rate(params)) अणु
	हाल 8000:
		inf = 0;
		अवरोध;
	हाल 11025:
		inf = 1;
		अवरोध;
	हाल 16000:
		inf = 3;
		अवरोध;
	हाल 22050:
		inf = 4;
		अवरोध;
	हाल 32000:
		inf = 6;
		अवरोध;
	हाल 44100:
		inf = 7;
		अवरोध;
	हाल 48000:
		inf = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_4, 0xf, inf);

	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_i2s_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				  अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर inf = 0, mask = 0;

	mask |= PCM_INF2_BCLK | PCM_INF2_FS | PCM_INF2_MASTER;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगर (pm860x->dir == PM860X_CLK_सूची_OUT)
			inf |= PCM_INF2_MASTER;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगर (pm860x->dir == PM860X_CLK_सूची_IN)
			inf &= ~PCM_INF2_MASTER;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		inf |= PCM_EXACT_I2S;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	mask |= PCM_MODE_MASK;
	snd_soc_component_update_bits(component, PM860X_I2S_IFACE_2, mask, inf);
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	पूर्णांक data;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Enable Audio PLL & Audio section */
			data = AUDIO_PLL | AUDIO_SECTION_ON;
			pm860x_reg_ग_लिखो(pm860x->i2c, REG_MISC2, data);
			udelay(300);
			data = AUDIO_PLL | AUDIO_SECTION_RESET
				| AUDIO_SECTION_ON;
			pm860x_reg_ग_लिखो(pm860x->i2c, REG_MISC2, data);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		data = AUDIO_PLL | AUDIO_SECTION_RESET | AUDIO_SECTION_ON;
		pm860x_set_bits(pm860x->i2c, REG_MISC2, data, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pm860x_pcm_dai_ops = अणु
	.mute_stream	= pm860x_mute_stream,
	.hw_params	= pm860x_pcm_hw_params,
	.set_fmt	= pm860x_pcm_set_dai_fmt,
	.set_sysclk	= pm860x_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops pm860x_i2s_dai_ops = अणु
	.mute_stream	= pm860x_mute_stream,
	.hw_params	= pm860x_i2s_hw_params,
	.set_fmt	= pm860x_i2s_set_dai_fmt,
	.set_sysclk	= pm860x_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा PM860X_RATES	(SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |	\
			 SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000)

अटल काष्ठा snd_soc_dai_driver pm860x_dai[] = अणु
	अणु
		/* DAI PCM */
		.name	= "88pm860x-pcm",
		.id	= 1,
		.playback = अणु
			.stream_name	= "PCM Playback",
			.channels_min	= 2,
			.channels_max	= 2,
			.rates		= PM860X_RATES,
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE | \
					  SNDRV_PCM_FMTBIT_S18_3LE,
		पूर्ण,
		.capture = अणु
			.stream_name	= "PCM Capture",
			.channels_min	= 2,
			.channels_max	= 2,
			.rates		= PM860X_RATES,
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE | \
					  SNDRV_PCM_FMTBIT_S18_3LE,
		पूर्ण,
		.ops	= &pm860x_pcm_dai_ops,
	पूर्ण, अणु
		/* DAI I2S */
		.name	= "88pm860x-i2s",
		.id	= 2,
		.playback = अणु
			.stream_name	= "I2S Playback",
			.channels_min	= 2,
			.channels_max	= 2,
			.rates		= SNDRV_PCM_RATE_8000_48000,
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE | \
					  SNDRV_PCM_FMTBIT_S18_3LE,
		पूर्ण,
		.capture = अणु
			.stream_name	= "I2S Capture",
			.channels_min	= 2,
			.channels_max	= 2,
			.rates		= SNDRV_PCM_RATE_8000_48000,
			.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE | \
					  SNDRV_PCM_FMTBIT_S18_3LE,
		पूर्ण,
		.ops	= &pm860x_i2s_dai_ops,
	पूर्ण,
पूर्ण;

अटल irqवापस_t pm860x_component_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_priv *pm860x = data;
	पूर्णांक status, shrt, report = 0, mic_report = 0;
	पूर्णांक mask;

	status = pm860x_reg_पढ़ो(pm860x->i2c, REG_STATUS_1);
	shrt = pm860x_reg_पढ़ो(pm860x->i2c, REG_SHORTS);
	mask = pm860x->det.hs_shrt | pm860x->det.hook_det | pm860x->det.lo_shrt
		| pm860x->det.hp_det;

#अगर_अघोषित CONFIG_SND_SOC_88PM860X_MODULE
	अगर (status & (HEADSET_STATUS | MIC_STATUS | SHORT_HS1 | SHORT_HS2 |
		      SHORT_LO1 | SHORT_LO2))
		trace_snd_soc_jack_irq(dev_name(pm860x->component->dev));
#पूर्ण_अगर

	अगर ((pm860x->det.hp_det & SND_JACK_HEADPHONE)
		&& (status & HEADSET_STATUS))
		report |= SND_JACK_HEADPHONE;

	अगर ((pm860x->det.mic_det & SND_JACK_MICROPHONE)
		&& (status & MIC_STATUS))
		mic_report |= SND_JACK_MICROPHONE;

	अगर (pm860x->det.hs_shrt && (shrt & (SHORT_HS1 | SHORT_HS2)))
		report |= pm860x->det.hs_shrt;

	अगर (pm860x->det.hook_det && (status & HOOK_STATUS))
		report |= pm860x->det.hook_det;

	अगर (pm860x->det.lo_shrt && (shrt & (SHORT_LO1 | SHORT_LO2)))
		report |= pm860x->det.lo_shrt;

	अगर (report)
		snd_soc_jack_report(pm860x->det.hp_jack, report, mask);
	अगर (mic_report)
		snd_soc_jack_report(pm860x->det.mic_jack, SND_JACK_MICROPHONE,
				    SND_JACK_MICROPHONE);

	dev_dbg(pm860x->component->dev, "headphone report:0x%x, mask:%x\n",
		report, mask);
	dev_dbg(pm860x->component->dev, "microphone report:0x%x\n", mic_report);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक pm860x_hs_jack_detect(काष्ठा snd_soc_component *component,
			  काष्ठा snd_soc_jack *jack,
			  पूर्णांक det, पूर्णांक hook, पूर्णांक hs_shrt, पूर्णांक lo_shrt)
अणु
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	पूर्णांक data;

	pm860x->det.hp_jack = jack;
	pm860x->det.hp_det = det;
	pm860x->det.hook_det = hook;
	pm860x->det.hs_shrt = hs_shrt;
	pm860x->det.lo_shrt = lo_shrt;

	अगर (det & SND_JACK_HEADPHONE)
		pm860x_set_bits(pm860x->i2c, REG_HS_DET,
				EN_HS_DET, EN_HS_DET);
	/* headset लघु detect */
	अगर (hs_shrt) अणु
		data = CLR_SHORT_HS2 | CLR_SHORT_HS1;
		pm860x_set_bits(pm860x->i2c, REG_SHORTS, data, data);
	पूर्ण
	/* Lineout लघु detect */
	अगर (lo_shrt) अणु
		data = CLR_SHORT_LO2 | CLR_SHORT_LO1;
		pm860x_set_bits(pm860x->i2c, REG_SHORTS, data, data);
	पूर्ण

	/* sync status */
	pm860x_component_handler(0, pm860x);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm860x_hs_jack_detect);

पूर्णांक pm860x_mic_jack_detect(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_jack *jack, पूर्णांक det)
अणु
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);

	pm860x->det.mic_jack = jack;
	pm860x->det.mic_det = det;

	अगर (det & SND_JACK_MICROPHONE)
		pm860x_set_bits(pm860x->i2c, REG_MIC_DET,
				MICDET_MASK, MICDET_MASK);

	/* sync status */
	pm860x_component_handler(0, pm860x);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm860x_mic_jack_detect);

अटल पूर्णांक pm860x_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;

	pm860x->component = component;
	snd_soc_component_init_regmap(component,  pm860x->regmap);

	क्रम (i = 0; i < 4; i++) अणु
		ret = request_thपढ़ोed_irq(pm860x->irq[i], शून्य,
					   pm860x_component_handler, IRQF_ONESHOT,
					   pm860x->name[i], pm860x);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to request IRQ!\n");
			जाओ out;
		पूर्ण
	पूर्ण

	वापस 0;

out:
	जबतक (--i >= 0)
		मुक्त_irq(pm860x->irq[i], pm860x);
	वापस ret;
पूर्ण

अटल व्योम pm860x_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा pm860x_priv *pm860x = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	क्रम (i = 3; i >= 0; i--)
		मुक्त_irq(pm860x->irq[i], pm860x);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_pm860x = अणु
	.probe			= pm860x_probe,
	.हटाओ			= pm860x_हटाओ,
	.set_bias_level		= pm860x_set_bias_level,
	.controls		= pm860x_snd_controls,
	.num_controls		= ARRAY_SIZE(pm860x_snd_controls),
	.dapm_widमाला_लो		= pm860x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pm860x_dapm_widमाला_लो),
	.dapm_routes		= pm860x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pm860x_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक pm860x_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm860x_priv *pm860x;
	काष्ठा resource *res;
	पूर्णांक i, ret;

	pm860x = devm_kzalloc(&pdev->dev, माप(काष्ठा pm860x_priv),
			      GFP_KERNEL);
	अगर (pm860x == शून्य)
		वापस -ENOMEM;

	pm860x->chip = chip;
	pm860x->i2c = (chip->id == CHIP_PM8607) ? chip->client
			: chip->companion;
	pm860x->regmap = (chip->id == CHIP_PM8607) ? chip->regmap
			: chip->regmap_companion;
	platक्रमm_set_drvdata(pdev, pm860x);

	क्रम (i = 0; i < 4; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, i);
		अगर (!res) अणु
			dev_err(&pdev->dev, "Failed to get IRQ resources\n");
			वापस -EINVAL;
		पूर्ण
		pm860x->irq[i] = res->start + chip->irq_base;
		म_नकलन(pm860x->name[i], res->name, MAX_NAME_LEN);
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				     &soc_component_dev_pm860x,
				     pm860x_dai, ARRAY_SIZE(pm860x_dai));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register component\n");
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pm860x_codec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm860x_codec_driver = अणु
	.driver	= अणु
		.name	= "88pm860x-codec",
	पूर्ण,
	.probe	= pm860x_codec_probe,
	.हटाओ	= pm860x_codec_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm860x_codec_driver);

MODULE_DESCRIPTION("ASoC 88PM860x driver");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:88pm860x-codec");

