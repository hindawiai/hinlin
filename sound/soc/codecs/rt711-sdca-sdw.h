<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt711-sdw-sdca.h -- RT711 SDCA ALSA SoC audio driver header
 *
 * Copyright(c) 2021 Realtek Semiconductor Corp.
 */

#अगर_अघोषित __RT711_SDW_SDCA_H__
#घोषणा __RT711_SDW_SDCA_H__

#समावेश <linux/regmap.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>

अटल स्थिर काष्ठा reg_शेष rt711_sdca_reg_शेषs[] = अणु
	अणु 0x201a, 0x00 पूर्ण,
	अणु 0x201e, 0x00 पूर्ण,
	अणु 0x201f, 0x00 पूर्ण,
	अणु 0x2020, 0x00 पूर्ण,
	अणु 0x2021, 0x00 पूर्ण,
	अणु 0x2022, 0x00 पूर्ण,
	अणु 0x2023, 0x00 पूर्ण,
	अणु 0x2024, 0x00 पूर्ण,
	अणु 0x2025, 0x01 पूर्ण,
	अणु 0x2026, 0x00 पूर्ण,
	अणु 0x2027, 0x00 पूर्ण,
	अणु 0x2029, 0x00 पूर्ण,
	अणु 0x202a, 0x00 पूर्ण,
	अणु 0x202d, 0x00 पूर्ण,
	अणु 0x202e, 0x00 पूर्ण,
	अणु 0x202f, 0x00 पूर्ण,
	अणु 0x2030, 0x00 पूर्ण,
	अणु 0x2031, 0x00 पूर्ण,
	अणु 0x2032, 0x00 पूर्ण,
	अणु 0x2033, 0x00 पूर्ण,
	अणु 0x2230, 0x00 पूर्ण,
	अणु 0x2231, 0x2f पूर्ण,
	अणु 0x2232, 0x80 पूर्ण,
	अणु 0x2233, 0x00 पूर्ण,
	अणु 0x2234, 0x00 पूर्ण,
	अणु 0x2235, 0x00 पूर्ण,
	अणु 0x2236, 0x00 पूर्ण,
	अणु 0x2237, 0x00 पूर्ण,
	अणु 0x2238, 0x00 पूर्ण,
	अणु 0x2239, 0x00 पूर्ण,
	अणु 0x2f01, 0x00 पूर्ण,
	अणु 0x2f02, 0x09 पूर्ण,
	अणु 0x2f03, 0x00 पूर्ण,
	अणु 0x2f04, 0x00 पूर्ण,
	अणु 0x2f05, 0x0b पूर्ण,
	अणु 0x2f06, 0x01 पूर्ण,
	अणु 0x2f08, 0x00 पूर्ण,
	अणु 0x2f09, 0x00 पूर्ण,
	अणु 0x2f0a, 0x00 पूर्ण,
	अणु 0x2f0b, 0x00 पूर्ण,
	अणु 0x2f0c, 0x00 पूर्ण,
	अणु 0x2f0d, 0x00 पूर्ण,
	अणु 0x2f0e, 0x14 पूर्ण,
	अणु 0x2f0f, 0x00 पूर्ण,
	अणु 0x2f50, 0x03 पूर्ण,
	अणु 0x2f5a, 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_CS01, RT711_SDCA_CTL_SAMPLE_FREQ_INDEX, 0), 0x09 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05, RT711_SDCA_CTL_FU_MUTE, CH_L), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05, RT711_SDCA_CTL_FU_MUTE, CH_R), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F, RT711_SDCA_CTL_FU_MUTE, CH_L), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F, RT711_SDCA_CTL_FU_MUTE, CH_R), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PDE28, RT711_SDCA_CTL_REQ_POWER_STATE, 0), 0x03 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E, RT711_SDCA_CTL_FU_MUTE, CH_L), 0x01 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E, RT711_SDCA_CTL_FU_MUTE, CH_R), 0x01 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt711_sdca_mbq_शेषs[] = अणु
	अणु 0x2000009, 0x1029 पूर्ण,
	अणु 0x2000011, 0x007a पूर्ण,
	अणु 0x200001a, 0x8003 पूर्ण,
	अणु 0x2000045, 0x5289 पूर्ण,
	अणु 0x2000048, 0x8049 पूर्ण,
	अणु 0x200004a, 0xa83b पूर्ण,
	अणु 0x200006b, 0x5064 पूर्ण,
	अणु 0x200006f, 0x058b पूर्ण,
	अणु 0x5800000, 0x0008 पूर्ण,
	अणु 0x5800001, 0x0000 पूर्ण,
	अणु 0x5f00001, 0x000a पूर्ण,
	अणु 0x6100000, 0x6100 पूर्ण,
	अणु 0x6100035, 0x0060 पूर्ण,
	अणु 0x6100036, 0x0029 पूर्ण,
	अणु 0x610003f, 0xff12 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05, RT711_SDCA_CTL_FU_VOLUME, CH_L), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05, RT711_SDCA_CTL_FU_VOLUME, CH_R), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E, RT711_SDCA_CTL_FU_VOLUME, CH_L), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E, RT711_SDCA_CTL_FU_VOLUME, CH_R), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F, RT711_SDCA_CTL_FU_VOLUME, CH_L), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F, RT711_SDCA_CTL_FU_VOLUME, CH_R), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PLATFORM_FU44, RT711_SDCA_CTL_FU_CH_GAIN, CH_L), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PLATFORM_FU44, RT711_SDCA_CTL_FU_CH_GAIN, CH_R), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_PLATFORM_FU15, RT711_SDCA_CTL_FU_CH_GAIN, CH_L), 0x00 पूर्ण,
	अणु SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_PLATFORM_FU15, RT711_SDCA_CTL_FU_CH_GAIN, CH_R), 0x00 पूर्ण,
पूर्ण;

#पूर्ण_अगर /* __RT711_SDW_SDCA_H__ */
