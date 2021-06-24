<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lm49453.c  -  LM49453 ALSA Soc Audio driver
 *
 * Copyright (c) 2012 Texas Instruments, Inc
 *
 * Initially based on sound/soc/codecs/wm8350.c
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "lm49453.h"

अटल स्थिर काष्ठा reg_शेष lm49453_reg_defs[] = अणु
	अणु 0, 0x00 पूर्ण,
	अणु 1, 0x00 पूर्ण,
	अणु 2, 0x00 पूर्ण,
	अणु 3, 0x00 पूर्ण,
	अणु 4, 0x00 पूर्ण,
	अणु 5, 0x00 पूर्ण,
	अणु 6, 0x00 पूर्ण,
	अणु 7, 0x00 पूर्ण,
	अणु 8, 0x00 पूर्ण,
	अणु 9, 0x00 पूर्ण,
	अणु 10, 0x00 पूर्ण,
	अणु 11, 0x00 पूर्ण,
	अणु 12, 0x00 पूर्ण,
	अणु 13, 0x00 पूर्ण,
	अणु 14, 0x00 पूर्ण,
	अणु 15, 0x00 पूर्ण,
	अणु 16, 0x00 पूर्ण,
	अणु 17, 0x00 पूर्ण,
	अणु 18, 0x00 पूर्ण,
	अणु 19, 0x00 पूर्ण,
	अणु 20, 0x00 पूर्ण,
	अणु 21, 0x00 पूर्ण,
	अणु 22, 0x00 पूर्ण,
	अणु 23, 0x00 पूर्ण,
	अणु 32, 0x00 पूर्ण,
	अणु 33, 0x00 पूर्ण,
	अणु 35, 0x00 पूर्ण,
	अणु 36, 0x00 पूर्ण,
	अणु 37, 0x00 पूर्ण,
	अणु 46, 0x00 पूर्ण,
	अणु 48, 0x00 पूर्ण,
	अणु 49, 0x00 पूर्ण,
	अणु 51, 0x00 पूर्ण,
	अणु 56, 0x00 पूर्ण,
	अणु 58, 0x00 पूर्ण,
	अणु 59, 0x00 पूर्ण,
	अणु 60, 0x00 पूर्ण,
	अणु 61, 0x00 पूर्ण,
	अणु 62, 0x00 पूर्ण,
	अणु 63, 0x00 पूर्ण,
	अणु 64, 0x00 पूर्ण,
	अणु 65, 0x00 पूर्ण,
	अणु 66, 0x00 पूर्ण,
	अणु 67, 0x00 पूर्ण,
	अणु 68, 0x00 पूर्ण,
	अणु 69, 0x00 पूर्ण,
	अणु 70, 0x00 पूर्ण,
	अणु 71, 0x00 पूर्ण,
	अणु 72, 0x00 पूर्ण,
	अणु 73, 0x00 पूर्ण,
	अणु 74, 0x00 पूर्ण,
	अणु 75, 0x00 पूर्ण,
	अणु 76, 0x00 पूर्ण,
	अणु 77, 0x00 पूर्ण,
	अणु 78, 0x00 पूर्ण,
	अणु 79, 0x00 पूर्ण,
	अणु 80, 0x00 पूर्ण,
	अणु 81, 0x00 पूर्ण,
	अणु 82, 0x00 पूर्ण,
	अणु 83, 0x00 पूर्ण,
	अणु 85, 0x00 पूर्ण,
	अणु 85, 0x00 पूर्ण,
	अणु 86, 0x00 पूर्ण,
	अणु 87, 0x00 पूर्ण,
	अणु 88, 0x00 पूर्ण,
	अणु 89, 0x00 पूर्ण,
	अणु 90, 0x00 पूर्ण,
	अणु 91, 0x00 पूर्ण,
	अणु 92, 0x00 पूर्ण,
	अणु 93, 0x00 पूर्ण,
	अणु 94, 0x00 पूर्ण,
	अणु 95, 0x00 पूर्ण,
	अणु 96, 0x01 पूर्ण,
	अणु 97, 0x00 पूर्ण,
	अणु 98, 0x00 पूर्ण,
	अणु 99, 0x00 पूर्ण,
	अणु 100, 0x00 पूर्ण,
	अणु 101, 0x00 पूर्ण,
	अणु 102, 0x00 पूर्ण,
	अणु 103, 0x01 पूर्ण,
	अणु 104, 0x01 पूर्ण,
	अणु 105, 0x00 पूर्ण,
	अणु 106, 0x01 पूर्ण,
	अणु 107, 0x00 पूर्ण,
	अणु 108, 0x00 पूर्ण,
	अणु 109, 0x00 पूर्ण,
	अणु 110, 0x00 पूर्ण,
	अणु 111, 0x02 पूर्ण,
	अणु 112, 0x02 पूर्ण,
	अणु 113, 0x00 पूर्ण,
	अणु 121, 0x80 पूर्ण,
	अणु 122, 0xBB पूर्ण,
	अणु 123, 0x80 पूर्ण,
	अणु 124, 0xBB पूर्ण,
	अणु 128, 0x00 पूर्ण,
	अणु 130, 0x00 पूर्ण,
	अणु 131, 0x00 पूर्ण,
	अणु 132, 0x00 पूर्ण,
	अणु 133, 0x0A पूर्ण,
	अणु 134, 0x0A पूर्ण,
	अणु 135, 0x0A पूर्ण,
	अणु 136, 0x0F पूर्ण,
	अणु 137, 0x00 पूर्ण,
	अणु 138, 0x73 पूर्ण,
	अणु 139, 0x33 पूर्ण,
	अणु 140, 0x73 पूर्ण,
	अणु 141, 0x33 पूर्ण,
	अणु 142, 0x73 पूर्ण,
	अणु 143, 0x33 पूर्ण,
	अणु 144, 0x73 पूर्ण,
	अणु 145, 0x33 पूर्ण,
	अणु 146, 0x73 पूर्ण,
	अणु 147, 0x33 पूर्ण,
	अणु 148, 0x73 पूर्ण,
	अणु 149, 0x33 पूर्ण,
	अणु 150, 0x73 पूर्ण,
	अणु 151, 0x33 पूर्ण,
	अणु 152, 0x00 पूर्ण,
	अणु 153, 0x00 पूर्ण,
	अणु 154, 0x00 पूर्ण,
	अणु 155, 0x00 पूर्ण,
	अणु 176, 0x00 पूर्ण,
	अणु 177, 0x00 पूर्ण,
	अणु 178, 0x00 पूर्ण,
	अणु 179, 0x00 पूर्ण,
	अणु 180, 0x00 पूर्ण,
	अणु 181, 0x00 पूर्ण,
	अणु 182, 0x00 पूर्ण,
	अणु 183, 0x00 पूर्ण,
	अणु 184, 0x00 पूर्ण,
	अणु 185, 0x00 पूर्ण,
	अणु 186, 0x00 पूर्ण,
	अणु 187, 0x00 पूर्ण,
	अणु 188, 0x00 पूर्ण,
	अणु 189, 0x00 पूर्ण,
	अणु 208, 0x06 पूर्ण,
	अणु 209, 0x00 पूर्ण,
	अणु 210, 0x08 पूर्ण,
	अणु 211, 0x54 पूर्ण,
	अणु 212, 0x14 पूर्ण,
	अणु 213, 0x0d पूर्ण,
	अणु 214, 0x0d पूर्ण,
	अणु 215, 0x14 पूर्ण,
	अणु 216, 0x60 पूर्ण,
	अणु 221, 0x00 पूर्ण,
	अणु 222, 0x00 पूर्ण,
	अणु 223, 0x00 पूर्ण,
	अणु 224, 0x00 पूर्ण,
	अणु 248, 0x00 पूर्ण,
	अणु 249, 0x00 पूर्ण,
	अणु 250, 0x00 पूर्ण,
	अणु 255, 0x00 पूर्ण,
पूर्ण;

/* codec निजी data */
काष्ठा lm49453_priv अणु
	काष्ठा regmap *regmap;
पूर्ण;

/* capture path controls */

अटल स्थिर अक्षर *lm49453_mic2mode_text[] = अणु"Single Ended", "Differential"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lm49453_mic2mode_क्रमागत, LM49453_P0_MICR_REG, 5,
			    lm49453_mic2mode_text);

अटल स्थिर अक्षर *lm49453_dmic_cfg_text[] = अणु"DMICDAT1", "DMICDAT2"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lm49453_dmic12_cfg_क्रमागत,
			    LM49453_P0_DIGITAL_MIC1_CONFIG_REG, 7,
			    lm49453_dmic_cfg_text);

अटल SOC_ENUM_SINGLE_DECL(lm49453_dmic34_cfg_क्रमागत,
			    LM49453_P0_DIGITAL_MIC2_CONFIG_REG, 7,
			    lm49453_dmic_cfg_text);

/* MUX Controls */
अटल स्थिर अक्षर *lm49453_adcl_mux_text[] = अणु "MIC1", "Aux_L" पूर्ण;

अटल स्थिर अक्षर *lm49453_adcr_mux_text[] = अणु "MIC2", "Aux_R" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lm49453_adcl_क्रमागत,
			    LM49453_P0_ANALOG_MIXER_ADC_REG, 0,
			    lm49453_adcl_mux_text);

अटल SOC_ENUM_SINGLE_DECL(lm49453_adcr_क्रमागत,
			    LM49453_P0_ANALOG_MIXER_ADC_REG, 1,
			    lm49453_adcr_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_adcl_mux_control =
	SOC_DAPM_ENUM("ADC Left Mux", lm49453_adcl_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_adcr_mux_control =
	SOC_DAPM_ENUM("ADC Right Mux", lm49453_adcr_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_headset_left_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACHPL1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACHPL1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACHPL1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACHPL1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACHPL1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACHPL1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACHPL1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACHPL1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACHPL2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACHPL2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACHPL2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACHPL2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACHPL2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACHPL2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACHPL2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACHPL2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 0, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_headset_right_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACHPR1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACHPR1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACHPR1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACHPR1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACHPR1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACHPR1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACHPR1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACHPR1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACHPR2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACHPR2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACHPR2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACHPR2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACHPR2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACHPR2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACHPR2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACHPR2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 1, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_speaker_left_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACLSL1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACLSL1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACLSL1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACLSL1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACLSL1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACLSL1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACLSL1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACLSL1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACLSL2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACLSL2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACLSL2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACLSL2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACLSL2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACLSL2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACLSL2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACLSL2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 2, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_speaker_right_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACLSR1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACLSR1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACLSR1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACLSR1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACLSR1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACLSR1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACLSR1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACLSR1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACLSR2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACLSR2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACLSR2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACLSR2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACLSR2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACLSR2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACLSR2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACLSR2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 3, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_haptic_left_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACHAL1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACHAL1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACHAL1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACHAL1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACHAL1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACHAL1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACHAL1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACHAL1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACHAL2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACHAL2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACHAL2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACHAL2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACHAL2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACHAL2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACHAL2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACHAL2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 4, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_haptic_right_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACHAR1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACHAR1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACHAR1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACHAR1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACHAR1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACHAR1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACHAR1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACHAR1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACHAR2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACHAR2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACHAR2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACHAR2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACHAR2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACHAR2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACHAR2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACHAR2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 5, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_lineout_left_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACLOL1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACLOL1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACLOL1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACLOL1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACLOL1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACLOL1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACLOL1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACLOL1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACLOL2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACLOL2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACLOL2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACLOL2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACLOL2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACLOL2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACLOL2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACLOL2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 6, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_lineout_right_mixer[] = अणु
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_DACLOR1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_DACLOR1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_DACLOR1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_DACLOR1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_DACLOR1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_DACLOR1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_DACLOR1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_DACLOR1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_DACLOR2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_DACLOR2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_DACLOR2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_DACLOR2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_DACLOR2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_DACLOR2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_DACLOR2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_DACLOR2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("Sidetone Switch", LM49453_P0_STN_SEL_REG, 7, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx1_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_PORT1_TX1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_PORT1_TX1_REG, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx2_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_PORT1_TX2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_PORT1_TX2_REG, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx3_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX3_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX3_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX3_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX3_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX3_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX3_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_3 Switch", LM49453_P0_PORT1_TX3_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx4_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX4_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX4_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX4_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX4_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX4_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX4_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_4 Switch", LM49453_P0_PORT1_TX4_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx5_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX5_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX5_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX5_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX5_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX5_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX5_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_5 Switch", LM49453_P0_PORT1_TX5_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx6_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX6_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX6_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX6_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX6_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX6_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX6_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_6 Switch", LM49453_P0_PORT1_TX6_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx7_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX7_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX7_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX7_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX7_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX7_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX7_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_7 Switch", LM49453_P0_PORT1_TX7_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port1_tx8_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT1_TX8_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT1_TX8_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT1_TX8_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT1_TX8_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT1_TX8_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT1_TX8_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_8 Switch", LM49453_P0_PORT1_TX8_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port2_tx1_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT2_TX1_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT2_TX1_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT2_TX1_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT2_TX1_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT2_TX1_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT2_TX1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_1 Switch", LM49453_P0_PORT2_TX1_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_1 Switch", LM49453_P0_PORT2_TX1_REG, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_port2_tx2_mixer[] = अणु
SOC_DAPM_SINGLE("DMIC1L Switch", LM49453_P0_PORT2_TX2_REG, 0, 1, 0),
SOC_DAPM_SINGLE("DMIC1R Switch", LM49453_P0_PORT2_TX2_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DMIC2L Switch", LM49453_P0_PORT2_TX2_REG, 2, 1, 0),
SOC_DAPM_SINGLE("DMIC2R Switch", LM49453_P0_PORT2_TX2_REG, 3, 1, 0),
SOC_DAPM_SINGLE("ADCL Switch", LM49453_P0_PORT2_TX2_REG, 4, 1, 0),
SOC_DAPM_SINGLE("ADCR Switch", LM49453_P0_PORT2_TX2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("Port1_2 Switch", LM49453_P0_PORT2_TX2_REG, 6, 1, 0),
SOC_DAPM_SINGLE("Port2_2 Switch", LM49453_P0_PORT2_TX2_REG, 7, 1, 0),
पूर्ण;

/* TLV Declarations */
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_dac_tlv, -7650, 150, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_tlv, 0, 200, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(port_tlv, -1800, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(stn_tlv, -7200, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_sidetone_mixer_controls[] = अणु
/* Sidetone supports mono only */
SOC_DAPM_SINGLE_TLV("Sidetone ADCL Volume", LM49453_P0_STN_VOL_ADCL_REG,
		     0, 0x3F, 0, stn_tlv),
SOC_DAPM_SINGLE_TLV("Sidetone ADCR Volume", LM49453_P0_STN_VOL_ADCR_REG,
		     0, 0x3F, 0, stn_tlv),
SOC_DAPM_SINGLE_TLV("Sidetone DMIC1L Volume", LM49453_P0_STN_VOL_DMIC1L_REG,
		     0, 0x3F, 0, stn_tlv),
SOC_DAPM_SINGLE_TLV("Sidetone DMIC1R Volume", LM49453_P0_STN_VOL_DMIC1R_REG,
		     0, 0x3F, 0, stn_tlv),
SOC_DAPM_SINGLE_TLV("Sidetone DMIC2L Volume", LM49453_P0_STN_VOL_DMIC2L_REG,
		     0, 0x3F, 0, stn_tlv),
SOC_DAPM_SINGLE_TLV("Sidetone DMIC2R Volume", LM49453_P0_STN_VOL_DMIC2R_REG,
		     0, 0x3F, 0, stn_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new lm49453_snd_controls[] = अणु
	/* mic1 and mic2 supports mono only */
	SOC_SINGLE_TLV("Mic1 Volume", LM49453_P0_MICL_REG, 0, 15, 0, mic_tlv),
	SOC_SINGLE_TLV("Mic2 Volume", LM49453_P0_MICR_REG, 0, 15, 0, mic_tlv),

	SOC_SINGLE_TLV("ADCL Volume", LM49453_P0_ADC_LEVELL_REG, 0, 63,
			0, adc_dac_tlv),
	SOC_SINGLE_TLV("ADCR Volume", LM49453_P0_ADC_LEVELR_REG, 0, 63,
			0, adc_dac_tlv),

	SOC_DOUBLE_R_TLV("DMIC1 Volume", LM49453_P0_DMIC1_LEVELL_REG,
			  LM49453_P0_DMIC1_LEVELR_REG, 0, 63, 0, adc_dac_tlv),
	SOC_DOUBLE_R_TLV("DMIC2 Volume", LM49453_P0_DMIC2_LEVELL_REG,
			  LM49453_P0_DMIC2_LEVELR_REG, 0, 63, 0, adc_dac_tlv),

	SOC_DAPM_ENUM("Mic2Mode", lm49453_mic2mode_क्रमागत),
	SOC_DAPM_ENUM("DMIC12 SRC", lm49453_dmic12_cfg_क्रमागत),
	SOC_DAPM_ENUM("DMIC34 SRC", lm49453_dmic34_cfg_क्रमागत),

	/* Capture path filter enable */
	SOC_SINGLE("DMIC1 HPFilter Switch", LM49453_P0_ADC_FX_ENABLES_REG,
					    0, 1, 0),
	SOC_SINGLE("DMIC2 HPFilter Switch", LM49453_P0_ADC_FX_ENABLES_REG,
					    1, 1, 0),
	SOC_SINGLE("ADC HPFilter Switch", LM49453_P0_ADC_FX_ENABLES_REG,
					  2, 1, 0),

	SOC_DOUBLE_R_TLV("DAC HP Volume", LM49453_P0_DAC_HP_LEVELL_REG,
			  LM49453_P0_DAC_HP_LEVELR_REG, 0, 63, 0, adc_dac_tlv),
	SOC_DOUBLE_R_TLV("DAC LO Volume", LM49453_P0_DAC_LO_LEVELL_REG,
			  LM49453_P0_DAC_LO_LEVELR_REG, 0, 63, 0, adc_dac_tlv),
	SOC_DOUBLE_R_TLV("DAC LS Volume", LM49453_P0_DAC_LS_LEVELL_REG,
			  LM49453_P0_DAC_LS_LEVELR_REG, 0, 63, 0, adc_dac_tlv),
	SOC_DOUBLE_R_TLV("DAC HA Volume", LM49453_P0_DAC_HA_LEVELL_REG,
			  LM49453_P0_DAC_HA_LEVELR_REG, 0, 63, 0, adc_dac_tlv),

	SOC_SINGLE_TLV("EP Volume", LM49453_P0_DAC_LS_LEVELL_REG,
			0, 63, 0, adc_dac_tlv),

	SOC_SINGLE_TLV("PORT1_1_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL1_REG,
			0, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT1_2_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL1_REG,
			2, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT1_3_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL1_REG,
			4, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT1_4_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL1_REG,
			6, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT1_5_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL2_REG,
			0, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT1_6_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL2_REG,
			2, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT1_7_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL2_REG,
			4, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT1_8_RX_LVL Volume", LM49453_P0_PORT1_RX_LVL2_REG,
			6, 3, 0, port_tlv),

	SOC_SINGLE_TLV("PORT2_1_RX_LVL Volume", LM49453_P0_PORT2_RX_LVL_REG,
			0, 3, 0, port_tlv),
	SOC_SINGLE_TLV("PORT2_2_RX_LVL Volume", LM49453_P0_PORT2_RX_LVL_REG,
			2, 3, 0, port_tlv),

	SOC_SINGLE("Port1 Playback Switch", LM49453_P0_AUDIO_PORT1_BASIC_REG,
		    1, 1, 0),
	SOC_SINGLE("Port2 Playback Switch", LM49453_P0_AUDIO_PORT2_BASIC_REG,
		    1, 1, 0),
	SOC_SINGLE("Port1 Capture Switch", LM49453_P0_AUDIO_PORT1_BASIC_REG,
		    2, 1, 0),
	SOC_SINGLE("Port2 Capture Switch", LM49453_P0_AUDIO_PORT2_BASIC_REG,
		    2, 1, 0)

पूर्ण;

/* DAPM widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget lm49453_dapm_widमाला_लो[] = अणु

	/* All end poपूर्णांकs HP,EP, LS, Lineout and Haptic */
	SND_SOC_DAPM_OUTPUT("HPOUTL"),
	SND_SOC_DAPM_OUTPUT("HPOUTR"),
	SND_SOC_DAPM_OUTPUT("EPOUT"),
	SND_SOC_DAPM_OUTPUT("LSOUTL"),
	SND_SOC_DAPM_OUTPUT("LSOUTR"),
	SND_SOC_DAPM_OUTPUT("LOOUTR"),
	SND_SOC_DAPM_OUTPUT("LOOUTL"),
	SND_SOC_DAPM_OUTPUT("HAOUTL"),
	SND_SOC_DAPM_OUTPUT("HAOUTR"),

	SND_SOC_DAPM_INPUT("AMIC1"),
	SND_SOC_DAPM_INPUT("AMIC2"),
	SND_SOC_DAPM_INPUT("DMIC1DAT"),
	SND_SOC_DAPM_INPUT("DMIC2DAT"),
	SND_SOC_DAPM_INPUT("AUXL"),
	SND_SOC_DAPM_INPUT("AUXR"),

	SND_SOC_DAPM_PGA("PORT1_1_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT1_2_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT1_3_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT1_4_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT1_5_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT1_6_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT1_7_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT1_8_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT2_1_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PORT2_2_RX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("AMIC1Bias", LM49453_P0_MICL_REG, 6, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AMIC2Bias", LM49453_P0_MICR_REG, 6, 0, शून्य, 0),

	/* playback path driver enables */
	SND_SOC_DAPM_OUT_DRV("Headset Switch",
			LM49453_P0_PMC_SETUP_REG, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Earpiece Switch",
			LM49453_P0_EP_REG, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Speaker Left Switch",
			LM49453_P0_DIS_PKVL_FB_REG, 0, 1, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Speaker Right Switch",
			LM49453_P0_DIS_PKVL_FB_REG, 1, 1, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Haptic Left Switch",
			LM49453_P0_DIS_PKVL_FB_REG, 2, 1, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Haptic Right Switch",
			LM49453_P0_DIS_PKVL_FB_REG, 3, 1, शून्य, 0),

	/* DAC */
	SND_SOC_DAPM_DAC("HPL DAC", "Headset", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("HPR DAC", "Headset", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("LSL DAC", "Speaker", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("LSR DAC", "Speaker", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("HAL DAC", "Haptic", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("HAR DAC", "Haptic", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("LOL DAC", "Lineout", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("LOR DAC", "Lineout", SND_SOC_NOPM, 0, 0),


	SND_SOC_DAPM_PGA("AUXL Input",
			LM49453_P0_ANALOG_MIXER_ADC_REG, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUXR Input",
			LM49453_P0_ANALOG_MIXER_ADC_REG, 3, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Sidetone", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* ADC */
	SND_SOC_DAPM_ADC("DMIC1 Left", "Capture", SND_SOC_NOPM, 1, 0),
	SND_SOC_DAPM_ADC("DMIC1 Right", "Capture", SND_SOC_NOPM, 1, 0),
	SND_SOC_DAPM_ADC("DMIC2 Left", "Capture", SND_SOC_NOPM, 1, 0),
	SND_SOC_DAPM_ADC("DMIC2 Right", "Capture", SND_SOC_NOPM, 1, 0),

	SND_SOC_DAPM_ADC("ADC Left", "Capture", SND_SOC_NOPM, 1, 0),
	SND_SOC_DAPM_ADC("ADC Right", "Capture", SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("ADCL Mux", SND_SOC_NOPM, 0, 0,
			  &lm49453_adcl_mux_control),
	SND_SOC_DAPM_MUX("ADCR Mux", SND_SOC_NOPM, 0, 0,
			  &lm49453_adcr_mux_control),

	SND_SOC_DAPM_MUX("Mic1 Input",
			SND_SOC_NOPM, 0, 0, &lm49453_adcl_mux_control),

	SND_SOC_DAPM_MUX("Mic2 Input",
			SND_SOC_NOPM, 0, 0, &lm49453_adcr_mux_control),

	/* AIF */
	SND_SOC_DAPM_AIF_IN("PORT1_SDI", शून्य, 0,
			    LM49453_P0_PULL_CONFIG1_REG, 2, 0),
	SND_SOC_DAPM_AIF_IN("PORT2_SDI", शून्य, 0,
			    LM49453_P0_PULL_CONFIG1_REG, 6, 0),

	SND_SOC_DAPM_AIF_OUT("PORT1_SDO", शून्य, 0,
			     LM49453_P0_PULL_CONFIG1_REG, 3, 0),
	SND_SOC_DAPM_AIF_OUT("PORT2_SDO", शून्य, 0,
			      LM49453_P0_PULL_CONFIG1_REG, 7, 0),

	/* Port1 TX controls */
	SND_SOC_DAPM_OUT_DRV("P1_1_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P1_2_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P1_3_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P1_4_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P1_5_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P1_6_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P1_7_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P1_8_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Port2 TX controls */
	SND_SOC_DAPM_OUT_DRV("P2_1_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("P2_2_TX", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Sidetone Mixer */
	SND_SOC_DAPM_MIXER("Sidetone Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_sidetone_mixer_controls,
			    ARRAY_SIZE(lm49453_sidetone_mixer_controls)),

	/* DAC MIXERS */
	SND_SOC_DAPM_MIXER("HPL Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_headset_left_mixer,
			    ARRAY_SIZE(lm49453_headset_left_mixer)),
	SND_SOC_DAPM_MIXER("HPR Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_headset_right_mixer,
			    ARRAY_SIZE(lm49453_headset_right_mixer)),
	SND_SOC_DAPM_MIXER("LOL Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_lineout_left_mixer,
			    ARRAY_SIZE(lm49453_lineout_left_mixer)),
	SND_SOC_DAPM_MIXER("LOR Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_lineout_right_mixer,
			    ARRAY_SIZE(lm49453_lineout_right_mixer)),
	SND_SOC_DAPM_MIXER("LSL Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_speaker_left_mixer,
			    ARRAY_SIZE(lm49453_speaker_left_mixer)),
	SND_SOC_DAPM_MIXER("LSR Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_speaker_right_mixer,
			    ARRAY_SIZE(lm49453_speaker_right_mixer)),
	SND_SOC_DAPM_MIXER("HAL Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_haptic_left_mixer,
			    ARRAY_SIZE(lm49453_haptic_left_mixer)),
	SND_SOC_DAPM_MIXER("HAR Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_haptic_right_mixer,
			    ARRAY_SIZE(lm49453_haptic_right_mixer)),

	/* Capture Mixer */
	SND_SOC_DAPM_MIXER("Port1_1 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx1_mixer,
			    ARRAY_SIZE(lm49453_port1_tx1_mixer)),
	SND_SOC_DAPM_MIXER("Port1_2 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx2_mixer,
			    ARRAY_SIZE(lm49453_port1_tx2_mixer)),
	SND_SOC_DAPM_MIXER("Port1_3 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx3_mixer,
			    ARRAY_SIZE(lm49453_port1_tx3_mixer)),
	SND_SOC_DAPM_MIXER("Port1_4 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx4_mixer,
			    ARRAY_SIZE(lm49453_port1_tx4_mixer)),
	SND_SOC_DAPM_MIXER("Port1_5 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx5_mixer,
			    ARRAY_SIZE(lm49453_port1_tx5_mixer)),
	SND_SOC_DAPM_MIXER("Port1_6 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx6_mixer,
			    ARRAY_SIZE(lm49453_port1_tx6_mixer)),
	SND_SOC_DAPM_MIXER("Port1_7 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx7_mixer,
			    ARRAY_SIZE(lm49453_port1_tx7_mixer)),
	SND_SOC_DAPM_MIXER("Port1_8 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port1_tx8_mixer,
			    ARRAY_SIZE(lm49453_port1_tx8_mixer)),

	SND_SOC_DAPM_MIXER("Port2_1 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port2_tx1_mixer,
			    ARRAY_SIZE(lm49453_port2_tx1_mixer)),
	SND_SOC_DAPM_MIXER("Port2_2 Mixer", SND_SOC_NOPM, 0, 0,
			    lm49453_port2_tx2_mixer,
			    ARRAY_SIZE(lm49453_port2_tx2_mixer)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route lm49453_audio_map[] = अणु
	/* Port SDI mapping */
	अणु "PORT1_1_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,
	अणु "PORT1_2_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,
	अणु "PORT1_3_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,
	अणु "PORT1_4_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,
	अणु "PORT1_5_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,
	अणु "PORT1_6_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,
	अणु "PORT1_7_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,
	अणु "PORT1_8_RX", "Port1 Playback Switch", "PORT1_SDI" पूर्ण,

	अणु "PORT2_1_RX", "Port2 Playback Switch", "PORT2_SDI" पूर्ण,
	अणु "PORT2_2_RX", "Port2 Playback Switch", "PORT2_SDI" पूर्ण,

	/* HP mapping */
	अणु "HPL Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "HPL Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "HPL Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "HPL Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "HPL Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "HPL Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "HPL Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "HPL Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	अणु "HPL Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "HPL Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "HPL Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "HPL Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "HPL Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "HPL Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "HPL Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "HPL Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,
	अणु "HPL Mixer", "Sidetone Switch", "Sidetone" पूर्ण,

	अणु "HPL DAC", शून्य, "HPL Mixer" पूर्ण,

	अणु "HPR Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "HPR Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "HPR Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "HPR Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "HPR Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "HPR Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "HPR Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "HPR Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	/* Port 2 */
	अणु "HPR Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "HPR Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "HPR Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "HPR Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "HPR Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "HPR Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "HPR Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "HPR Mixer", "DMIC2L Switch", "DMIC2 Right" पूर्ण,
	अणु "HPR Mixer", "Sidetone Switch", "Sidetone" पूर्ण,

	अणु "HPR DAC", शून्य, "HPR Mixer" पूर्ण,

	अणु "HPOUTL", "Headset Switch", "HPL DAC"पूर्ण,
	अणु "HPOUTR", "Headset Switch", "HPR DAC"पूर्ण,

	/* EP map */
	अणु "EPOUT", "Earpiece Switch", "HPL DAC" पूर्ण,

	/* Speaker map */
	अणु "LSL Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "LSL Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "LSL Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "LSL Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "LSL Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "LSL Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "LSL Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "LSL Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	/* Port 2 */
	अणु "LSL Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "LSL Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "LSL Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "LSL Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "LSL Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "LSL Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "LSL Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "LSL Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,
	अणु "LSL Mixer", "Sidetone Switch", "Sidetone" पूर्ण,

	अणु "LSL DAC", शून्य, "LSL Mixer" पूर्ण,

	अणु "LSR Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "LSR Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "LSR Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "LSR Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "LSR Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "LSR Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "LSR Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "LSR Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	/* Port 2 */
	अणु "LSR Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "LSR Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "LSR Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "LSR Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "LSR Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "LSR Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "LSR Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "LSR Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,
	अणु "LSR Mixer", "Sidetone Switch", "Sidetone" पूर्ण,

	अणु "LSR DAC", शून्य, "LSR Mixer" पूर्ण,

	अणु "LSOUTL", "Speaker Left Switch", "LSL DAC"पूर्ण,
	अणु "LSOUTR", "Speaker Left Switch", "LSR DAC"पूर्ण,

	/* Haptic map */
	अणु "HAL Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "HAL Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "HAL Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "HAL Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "HAL Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "HAL Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "HAL Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "HAL Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	/* Port 2 */
	अणु "HAL Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "HAL Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "HAL Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "HAL Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "HAL Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "HAL Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "HAL Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "HAL Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,
	अणु "HAL Mixer", "Sidetone Switch", "Sidetone" पूर्ण,

	अणु "HAL DAC", शून्य, "HAL Mixer" पूर्ण,

	अणु "HAR Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "HAR Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "HAR Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "HAR Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "HAR Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "HAR Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "HAR Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "HAR Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	/* Port 2 */
	अणु "HAR Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "HAR Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "HAR Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "HAR Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "HAR Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "HAR Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "HAR Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "HAR Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,
	अणु "HAR Mixer", "Sideton Switch", "Sidetone" पूर्ण,

	अणु "HAR DAC", शून्य, "HAR Mixer" पूर्ण,

	अणु "HAOUTL", "Haptic Left Switch", "HAL DAC" पूर्ण,
	अणु "HAOUTR", "Haptic Right Switch", "HAR DAC" पूर्ण,

	/* Lineout map */
	अणु "LOL Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "LOL Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "LOL Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "LOL Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "LOL Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "LOL Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "LOL Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "LOL Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	/* Port 2 */
	अणु "LOL Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "LOL Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "LOL Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "LOL Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "LOL Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "LOL Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "LOL Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "LOL Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,
	अणु "LOL Mixer", "Sidetone Switch", "Sidetone" पूर्ण,

	अणु "LOL DAC", शून्य, "LOL Mixer" पूर्ण,

	अणु "LOR Mixer", "Port1_1 Switch", "PORT1_1_RX" पूर्ण,
	अणु "LOR Mixer", "Port1_2 Switch", "PORT1_2_RX" पूर्ण,
	अणु "LOR Mixer", "Port1_3 Switch", "PORT1_3_RX" पूर्ण,
	अणु "LOR Mixer", "Port1_4 Switch", "PORT1_4_RX" पूर्ण,
	अणु "LOR Mixer", "Port1_5 Switch", "PORT1_5_RX" पूर्ण,
	अणु "LOR Mixer", "Port1_6 Switch", "PORT1_6_RX" पूर्ण,
	अणु "LOR Mixer", "Port1_7 Switch", "PORT1_7_RX" पूर्ण,
	अणु "LOR Mixer", "Port1_8 Switch", "PORT1_8_RX" पूर्ण,

	/* Port 2 */
	अणु "LOR Mixer", "Port2_1 Switch", "PORT2_1_RX" पूर्ण,
	अणु "LOR Mixer", "Port2_2 Switch", "PORT2_2_RX" पूर्ण,

	अणु "LOR Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "LOR Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "LOR Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "LOR Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "LOR Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "LOR Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,
	अणु "LOR Mixer", "Sidetone Switch", "Sidetone" पूर्ण,

	अणु "LOR DAC", शून्य, "LOR Mixer" पूर्ण,

	अणु "LOOUTL", शून्य, "LOL DAC" पूर्ण,
	अणु "LOOUTR", शून्य, "LOR DAC" पूर्ण,

	/* TX map */
	/* Port1 mappings */
	अणु "Port1_1 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_1 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_1 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_1 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_1 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_1 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port1_2 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_2 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_2 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_2 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_2 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_2 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port1_3 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_3 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_3 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_3 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_3 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_3 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port1_4 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_4 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_4 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_4 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_4 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_4 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port1_5 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_5 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_5 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_5 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_5 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_5 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port1_6 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_6 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_6 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_6 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_6 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_6 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port1_7 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_7 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_7 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_7 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_7 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_7 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port1_8 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port1_8 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port1_8 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port1_8 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port1_8 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port1_8 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port2_1 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port2_1 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port2_1 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port2_1 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port2_1 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port2_1 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "Port2_2 Mixer", "ADCL Switch", "ADC Left" पूर्ण,
	अणु "Port2_2 Mixer", "ADCR Switch", "ADC Right" पूर्ण,
	अणु "Port2_2 Mixer", "DMIC1L Switch", "DMIC1 Left" पूर्ण,
	अणु "Port2_2 Mixer", "DMIC1R Switch", "DMIC1 Right" पूर्ण,
	अणु "Port2_2 Mixer", "DMIC2L Switch", "DMIC2 Left" पूर्ण,
	अणु "Port2_2 Mixer", "DMIC2R Switch", "DMIC2 Right" पूर्ण,

	अणु "P1_1_TX", शून्य, "Port1_1 Mixer" पूर्ण,
	अणु "P1_2_TX", शून्य, "Port1_2 Mixer" पूर्ण,
	अणु "P1_3_TX", शून्य, "Port1_3 Mixer" पूर्ण,
	अणु "P1_4_TX", शून्य, "Port1_4 Mixer" पूर्ण,
	अणु "P1_5_TX", शून्य, "Port1_5 Mixer" पूर्ण,
	अणु "P1_6_TX", शून्य, "Port1_6 Mixer" पूर्ण,
	अणु "P1_7_TX", शून्य, "Port1_7 Mixer" पूर्ण,
	अणु "P1_8_TX", शून्य, "Port1_8 Mixer" पूर्ण,

	अणु "P2_1_TX", शून्य, "Port2_1 Mixer" पूर्ण,
	अणु "P2_2_TX", शून्य, "Port2_2 Mixer" पूर्ण,

	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_1_TX"पूर्ण,
	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_2_TX"पूर्ण,
	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_3_TX"पूर्ण,
	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_4_TX"पूर्ण,
	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_5_TX"पूर्ण,
	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_6_TX"पूर्ण,
	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_7_TX"पूर्ण,
	अणु "PORT1_SDO", "Port1 Capture Switch", "P1_8_TX"पूर्ण,

	अणु "PORT2_SDO", "Port2 Capture Switch", "P2_1_TX"पूर्ण,
	अणु "PORT2_SDO", "Port2 Capture Switch", "P2_2_TX"पूर्ण,

	अणु "Mic1 Input", शून्य, "AMIC1" पूर्ण,
	अणु "Mic2 Input", शून्य, "AMIC2" पूर्ण,

	अणु "AUXL Input", शून्य, "AUXL" पूर्ण,
	अणु "AUXR Input", शून्य, "AUXR" पूर्ण,

	/* AUX connections */
	अणु "ADCL Mux", "Aux_L", "AUXL Input" पूर्ण,
	अणु "ADCL Mux", "MIC1", "Mic1 Input" पूर्ण,

	अणु "ADCR Mux", "Aux_R", "AUXR Input" पूर्ण,
	अणु "ADCR Mux", "MIC2", "Mic2 Input" पूर्ण,

	/* ADC connection */
	अणु "ADC Left", शून्य, "ADCL Mux"पूर्ण,
	अणु "ADC Right", शून्य, "ADCR Mux"पूर्ण,

	अणु "DMIC1 Left", शून्य, "DMIC1DAT"पूर्ण,
	अणु "DMIC1 Right", शून्य, "DMIC1DAT"पूर्ण,
	अणु "DMIC2 Left", शून्य, "DMIC2DAT"पूर्ण,
	अणु "DMIC2 Right", शून्य, "DMIC2DAT"पूर्ण,

	/* Sidetone map */
	अणु "Sidetone Mixer", शून्य, "ADC Left" पूर्ण,
	अणु "Sidetone Mixer", शून्य, "ADC Right" पूर्ण,
	अणु "Sidetone Mixer", शून्य, "DMIC1 Left" पूर्ण,
	अणु "Sidetone Mixer", शून्य, "DMIC1 Right" पूर्ण,
	अणु "Sidetone Mixer", शून्य, "DMIC2 Left" पूर्ण,
	अणु "Sidetone Mixer", शून्य, "DMIC2 Right" पूर्ण,

	अणु "Sidetone", "Sidetone Switch", "Sidetone Mixer" पूर्ण,
पूर्ण;

अटल पूर्णांक lm49453_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 clk_भाग = 0;

	/* Setting DAC घड़ी भागiders based on substream sample rate. */
	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
	हाल 32000:
	हाल 24000:
	हाल 48000:
		clk_भाग = 256;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
		clk_भाग = 216;
		अवरोध;
	हाल 96000:
		clk_भाग = 127;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, LM49453_P0_ADC_CLK_DIV_REG, clk_भाग);
	snd_soc_component_ग_लिखो(component, LM49453_P0_DAC_HP_CLK_DIV_REG, clk_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	u16 aअगर_val;
	पूर्णांक mode = 0;
	पूर्णांक clk_phase = 0;
	पूर्णांक clk_shअगरt = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		aअगर_val = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		aअगर_val = LM49453_AUDIO_PORT1_BASIC_SYNC_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		aअगर_val = LM49453_AUDIO_PORT1_BASIC_CLK_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर_val = LM49453_AUDIO_PORT1_BASIC_CLK_MS |
			  LM49453_AUDIO_PORT1_BASIC_SYNC_MS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		mode = 1;
		clk_phase = (1 << 5);
		clk_shअगरt = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		mode = 1;
		clk_phase = (1 << 5);
		clk_shअगरt = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, LM49453_P0_AUDIO_PORT1_BASIC_REG,
			    LM49453_AUDIO_PORT1_BASIC_FMT_MASK|BIT(0)|BIT(5),
			    (aअगर_val | mode | clk_phase));

	snd_soc_component_ग_लिखो(component, LM49453_P0_AUDIO_PORT1_RX_MSB_REG, clk_shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 pll_clk = 0;

	चयन (freq) अणु
	हाल 12288000:
	हाल 26000000:
	हाल 19200000:
		/* pll clk slection */
		pll_clk = 0;
		अवरोध;
	हाल 48000:
	हाल 32576:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, LM49453_P0_PMC_SETUP_REG, BIT(4), pll_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_hp_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, LM49453_P0_DAC_DSP_REG, BIT(1)|BIT(0),
			    (mute ? (BIT(1)|BIT(0)) : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_lo_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, LM49453_P0_DAC_DSP_REG, BIT(3)|BIT(2),
			    (mute ? (BIT(3)|BIT(2)) : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_ls_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, LM49453_P0_DAC_DSP_REG, BIT(5)|BIT(4),
			    (mute ? (BIT(5)|BIT(4)) : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_ep_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, LM49453_P0_DAC_DSP_REG, BIT(4),
			    (mute ? BIT(4) : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_ha_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, LM49453_P0_DAC_DSP_REG, BIT(7)|BIT(6),
			    (mute ? (BIT(7)|BIT(6)) : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक lm49453_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा lm49453_priv *lm49453 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			regcache_sync(lm49453->regmap);

		snd_soc_component_update_bits(component, LM49453_P0_PMC_SETUP_REG,
				    LM49453_PMC_SETUP_CHIP_EN, LM49453_CHIP_EN);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, LM49453_P0_PMC_SETUP_REG,
				    LM49453_PMC_SETUP_CHIP_EN, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Formates supported by LM49453 driver. */
#घोषणा LM49453_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			 SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops lm49453_headset_dai_ops = अणु
	.hw_params	= lm49453_hw_params,
	.set_sysclk	= lm49453_set_dai_sysclk,
	.set_fmt	= lm49453_set_dai_fmt,
	.mute_stream	= lm49453_hp_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops lm49453_speaker_dai_ops = अणु
	.hw_params	= lm49453_hw_params,
	.set_sysclk	= lm49453_set_dai_sysclk,
	.set_fmt	= lm49453_set_dai_fmt,
	.mute_stream	= lm49453_ls_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops lm49453_haptic_dai_ops = अणु
	.hw_params	= lm49453_hw_params,
	.set_sysclk	= lm49453_set_dai_sysclk,
	.set_fmt	= lm49453_set_dai_fmt,
	.mute_stream	= lm49453_ha_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops lm49453_ep_dai_ops = अणु
	.hw_params	= lm49453_hw_params,
	.set_sysclk	= lm49453_set_dai_sysclk,
	.set_fmt	= lm49453_set_dai_fmt,
	.mute_stream	= lm49453_ep_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops lm49453_lineout_dai_ops = अणु
	.hw_params	= lm49453_hw_params,
	.set_sysclk	= lm49453_set_dai_sysclk,
	.set_fmt	= lm49453_set_dai_fmt,
	.mute_stream	= lm49453_lo_mute,
	.no_capture_mute = 1,
पूर्ण;

/* LM49453 dai काष्ठाure. */
अटल काष्ठा snd_soc_dai_driver lm49453_dai[] = अणु
	अणु
		.name = "LM49453 Headset",
		.playback = अणु
			.stream_name = "Headset",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = LM49453_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 5,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = LM49453_FORMATS,
		पूर्ण,
		.ops = &lm49453_headset_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "LM49453 Speaker",
		.playback = अणु
			.stream_name = "Speaker",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = LM49453_FORMATS,
		पूर्ण,
		.ops = &lm49453_speaker_dai_ops,
	पूर्ण,
	अणु
		.name = "LM49453 Haptic",
		.playback = अणु
			.stream_name = "Haptic",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = LM49453_FORMATS,
		पूर्ण,
		.ops = &lm49453_haptic_dai_ops,
	पूर्ण,
	अणु
		.name = "LM49453 Earpiece",
		.playback = अणु
			.stream_name = "Earpiece",
			.channels_min = 1,
			.channels_max = 1,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = LM49453_FORMATS,
		पूर्ण,
		.ops = &lm49453_ep_dai_ops,
	पूर्ण,
	अणु
		.name = "LM49453 line out",
		.playback = अणु
			.stream_name = "Lineout",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = LM49453_FORMATS,
		पूर्ण,
		.ops = &lm49453_lineout_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_lm49453 = अणु
	.set_bias_level		= lm49453_set_bias_level,
	.controls		= lm49453_snd_controls,
	.num_controls		= ARRAY_SIZE(lm49453_snd_controls),
	.dapm_widमाला_लो		= lm49453_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(lm49453_dapm_widमाला_लो),
	.dapm_routes		= lm49453_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(lm49453_audio_map),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lm49453_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LM49453_MAX_REGISTER,
	.reg_शेषs = lm49453_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lm49453_reg_defs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक lm49453_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm49453_priv *lm49453;
	पूर्णांक ret = 0;

	lm49453 = devm_kzalloc(&i2c->dev, माप(काष्ठा lm49453_priv),
				GFP_KERNEL);

	अगर (lm49453 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, lm49453);

	lm49453->regmap = devm_regmap_init_i2c(i2c, &lm49453_regmap_config);
	अगर (IS_ERR(lm49453->regmap)) अणु
		ret = PTR_ERR(lm49453->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret =  devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				      &soc_component_dev_lm49453,
				      lm49453_dai, ARRAY_SIZE(lm49453_dai));
	अगर (ret < 0)
		dev_err(&i2c->dev, "Failed to register component: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक lm49453_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm49453_i2c_id[] = अणु
	अणु "lm49453", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm49453_i2c_id);

अटल काष्ठा i2c_driver lm49453_i2c_driver = अणु
	.driver = अणु
		.name = "lm49453",
	पूर्ण,
	.probe = lm49453_i2c_probe,
	.हटाओ = lm49453_i2c_हटाओ,
	.id_table = lm49453_i2c_id,
पूर्ण;

module_i2c_driver(lm49453_i2c_driver);

MODULE_DESCRIPTION("ASoC LM49453 driver");
MODULE_AUTHOR("M R Swami Reddy <MR.Swami.Reddy@ti.com>");
MODULE_LICENSE("GPL v2");
