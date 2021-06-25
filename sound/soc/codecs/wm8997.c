<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8997.c  --  WM8997 ALSA SoC Audio driver
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

#समावेश "arizona.h"
#समावेश "wm8997.h"

काष्ठा wm8997_priv अणु
	काष्ठा arizona_priv core;
	काष्ठा arizona_fll fll[2];
पूर्ण;

अटल DECLARE_TLV_DB_SCALE(ana_tlv, 0, 100, 0);
अटल DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल DECLARE_TLV_DB_SCALE(digital_tlv, -6400, 50, 0);
अटल DECLARE_TLV_DB_SCALE(noise_tlv, -13200, 600, 0);
अटल DECLARE_TLV_DB_SCALE(ng_tlv, -10200, 600, 0);

अटल स्थिर काष्ठा reg_शेष wm8997_sysclk_reva_patch[] = अणु
	अणु 0x301D, 0x7B15 पूर्ण,
	अणु 0x301B, 0x0050 पूर्ण,
	अणु 0x305D, 0x7B17 पूर्ण,
	अणु 0x305B, 0x0050 पूर्ण,
	अणु 0x3001, 0x08FE पूर्ण,
	अणु 0x3003, 0x00F4 पूर्ण,
	अणु 0x3041, 0x08FF पूर्ण,
	अणु 0x3043, 0x0005 पूर्ण,
	अणु 0x3020, 0x0225 पूर्ण,
	अणु 0x3021, 0x0A00 पूर्ण,
	अणु 0x3022, 0xE24D पूर्ण,
	अणु 0x3023, 0x0800 पूर्ण,
	अणु 0x3024, 0xE24D पूर्ण,
	अणु 0x3025, 0xF000 पूर्ण,
	अणु 0x3060, 0x0226 पूर्ण,
	अणु 0x3061, 0x0A00 पूर्ण,
	अणु 0x3062, 0xE252 पूर्ण,
	अणु 0x3063, 0x0800 पूर्ण,
	अणु 0x3064, 0xE252 पूर्ण,
	अणु 0x3065, 0xF000 पूर्ण,
	अणु 0x3116, 0x022B पूर्ण,
	अणु 0x3117, 0xFA00 पूर्ण,
	अणु 0x3110, 0x246C पूर्ण,
	अणु 0x3111, 0x0A03 पूर्ण,
	अणु 0x3112, 0x246E पूर्ण,
	अणु 0x3113, 0x0A03 पूर्ण,
	अणु 0x3114, 0x2470 पूर्ण,
	अणु 0x3115, 0x0A03 पूर्ण,
	अणु 0x3126, 0x246C पूर्ण,
	अणु 0x3127, 0x0A02 पूर्ण,
	अणु 0x3128, 0x246E पूर्ण,
	अणु 0x3129, 0x0A02 पूर्ण,
	अणु 0x312A, 0x2470 पूर्ण,
	अणु 0x312B, 0xFA02 पूर्ण,
	अणु 0x3125, 0x0800 पूर्ण,
पूर्ण;

अटल पूर्णांक wm8997_sysclk_ev(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा arizona *arizona = dev_get_drvdata(component->dev->parent);
	काष्ठा regmap *regmap = arizona->regmap;
	स्थिर काष्ठा reg_शेष *patch = शून्य;
	पूर्णांक i, patch_size;

	चयन (arizona->rev) अणु
	हाल 0:
		patch = wm8997_sysclk_reva_patch;
		patch_size = ARRAY_SIZE(wm8997_sysclk_reva_patch);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (patch)
			क्रम (i = 0; i < patch_size; i++)
				regmap_ग_लिखो_async(regmap, patch[i].reg,
						   patch[i].def);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMU:
	हाल SND_SOC_DAPM_POST_PMD:
		वापस arizona_clk_ev(w, kcontrol, event);
	शेष:
		वापस 0;
	पूर्ण

	वापस arizona_dvfs_sysclk_ev(w, kcontrol, event);
पूर्ण

अटल स्थिर अक्षर * स्थिर wm8997_osr_text[] = अणु
	"Low power", "Normal", "High performance",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm8997_osr_val[] = अणु
	0x0, 0x3, 0x5,
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8997_hpout_osr[] = अणु
	SOC_VALUE_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_1L,
			      ARIZONA_OUT1_OSR_SHIFT, 0x7,
			      ARRAY_SIZE(wm8997_osr_text),
			      wm8997_osr_text, wm8997_osr_val),
	SOC_VALUE_ENUM_SINGLE(ARIZONA_OUTPUT_PATH_CONFIG_3L,
			      ARIZONA_OUT3_OSR_SHIFT, 0x7,
			      ARRAY_SIZE(wm8997_osr_text),
			      wm8997_osr_text, wm8997_osr_val),
पूर्ण;

#घोषणा WM8997_NG_SRC(name, base) \
	SOC_SINGLE(name " NG HPOUT1L Switch",  base, 0, 1, 0), \
	SOC_SINGLE(name " NG HPOUT1R Switch",  base, 1, 1, 0), \
	SOC_SINGLE(name " NG EPOUT Switch",    base, 4, 1, 0), \
	SOC_SINGLE(name " NG SPKOUT Switch",   base, 6, 1, 0), \
	SOC_SINGLE(name " NG SPKDAT1L Switch", base, 8, 1, 0), \
	SOC_SINGLE(name " NG SPKDAT1R Switch", base, 9, 1, 0)

अटल स्थिर काष्ठा snd_kcontrol_new wm8997_snd_controls[] = अणु
SOC_SINGLE("IN1 High Performance Switch", ARIZONA_IN1L_CONTROL,
	   ARIZONA_IN1_OSR_SHIFT, 1, 0),
SOC_SINGLE("IN2 High Performance Switch", ARIZONA_IN2L_CONTROL,
	   ARIZONA_IN2_OSR_SHIFT, 1, 0),

SOC_SINGLE_RANGE_TLV("IN1L Volume", ARIZONA_IN1L_CONTROL,
		     ARIZONA_IN1L_PGA_VOL_SHIFT, 0x40, 0x5f, 0, ana_tlv),
SOC_SINGLE_RANGE_TLV("IN1R Volume", ARIZONA_IN1R_CONTROL,
		     ARIZONA_IN1R_PGA_VOL_SHIFT, 0x40, 0x5f, 0, ana_tlv),
SOC_SINGLE_RANGE_TLV("IN2L Volume", ARIZONA_IN2L_CONTROL,
		     ARIZONA_IN2L_PGA_VOL_SHIFT, 0x40, 0x5f, 0, ana_tlv),
SOC_SINGLE_RANGE_TLV("IN2R Volume", ARIZONA_IN2R_CONTROL,
		     ARIZONA_IN2R_PGA_VOL_SHIFT, 0x40, 0x5f, 0, ana_tlv),

SOC_SINGLE_TLV("IN1L Digital Volume", ARIZONA_ADC_DIGITAL_VOLUME_1L,
	       ARIZONA_IN1L_DIG_VOL_SHIFT, 0xbf, 0, digital_tlv),
SOC_SINGLE_TLV("IN1R Digital Volume", ARIZONA_ADC_DIGITAL_VOLUME_1R,
	       ARIZONA_IN1R_DIG_VOL_SHIFT, 0xbf, 0, digital_tlv),
SOC_SINGLE_TLV("IN2L Digital Volume", ARIZONA_ADC_DIGITAL_VOLUME_2L,
	       ARIZONA_IN2L_DIG_VOL_SHIFT, 0xbf, 0, digital_tlv),
SOC_SINGLE_TLV("IN2R Digital Volume", ARIZONA_ADC_DIGITAL_VOLUME_2R,
	       ARIZONA_IN2R_DIG_VOL_SHIFT, 0xbf, 0, digital_tlv),

SOC_ENUM("Input Ramp Up", arizona_in_vi_ramp),
SOC_ENUM("Input Ramp Down", arizona_in_vd_ramp),

ARIZONA_MIXER_CONTROLS("EQ1", ARIZONA_EQ1MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("EQ2", ARIZONA_EQ2MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("EQ3", ARIZONA_EQ3MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("EQ4", ARIZONA_EQ4MIX_INPUT_1_SOURCE),

ARIZONA_EQ_CONTROL("EQ1 Coefficients", ARIZONA_EQ1_2),
SOC_SINGLE_TLV("EQ1 B1 Volume", ARIZONA_EQ1_1, ARIZONA_EQ1_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 B2 Volume", ARIZONA_EQ1_1, ARIZONA_EQ1_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 B3 Volume", ARIZONA_EQ1_1, ARIZONA_EQ1_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 B4 Volume", ARIZONA_EQ1_2, ARIZONA_EQ1_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ1 B5 Volume", ARIZONA_EQ1_2, ARIZONA_EQ1_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

ARIZONA_EQ_CONTROL("EQ2 Coefficients", ARIZONA_EQ2_2),
SOC_SINGLE_TLV("EQ2 B1 Volume", ARIZONA_EQ2_1, ARIZONA_EQ2_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 B2 Volume", ARIZONA_EQ2_1, ARIZONA_EQ2_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 B3 Volume", ARIZONA_EQ2_1, ARIZONA_EQ2_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 B4 Volume", ARIZONA_EQ2_2, ARIZONA_EQ2_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ2 B5 Volume", ARIZONA_EQ2_2, ARIZONA_EQ2_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

ARIZONA_EQ_CONTROL("EQ3 Coefficients", ARIZONA_EQ3_2),
SOC_SINGLE_TLV("EQ3 B1 Volume", ARIZONA_EQ3_1, ARIZONA_EQ3_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 B2 Volume", ARIZONA_EQ3_1, ARIZONA_EQ3_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 B3 Volume", ARIZONA_EQ3_1, ARIZONA_EQ3_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 B4 Volume", ARIZONA_EQ3_2, ARIZONA_EQ3_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ3 B5 Volume", ARIZONA_EQ3_2, ARIZONA_EQ3_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

ARIZONA_EQ_CONTROL("EQ4 Coefficients", ARIZONA_EQ4_2),
SOC_SINGLE_TLV("EQ4 B1 Volume", ARIZONA_EQ4_1, ARIZONA_EQ4_B1_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 B2 Volume", ARIZONA_EQ4_1, ARIZONA_EQ4_B2_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 B3 Volume", ARIZONA_EQ4_1, ARIZONA_EQ4_B3_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 B4 Volume", ARIZONA_EQ4_2, ARIZONA_EQ4_B4_GAIN_SHIFT,
	       24, 0, eq_tlv),
SOC_SINGLE_TLV("EQ4 B5 Volume", ARIZONA_EQ4_2, ARIZONA_EQ4_B5_GAIN_SHIFT,
	       24, 0, eq_tlv),

ARIZONA_MIXER_CONTROLS("DRC1L", ARIZONA_DRC1LMIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("DRC1R", ARIZONA_DRC1RMIX_INPUT_1_SOURCE),

SND_SOC_BYTES_MASK("DRC1", ARIZONA_DRC1_CTRL1, 5,
		   ARIZONA_DRC1R_ENA | ARIZONA_DRC1L_ENA),

ARIZONA_MIXER_CONTROLS("LHPF1", ARIZONA_HPLP1MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("LHPF2", ARIZONA_HPLP2MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("LHPF3", ARIZONA_HPLP3MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("LHPF4", ARIZONA_HPLP4MIX_INPUT_1_SOURCE),

SOC_ENUM("LHPF1 Mode", arizona_lhpf1_mode),
SOC_ENUM("LHPF2 Mode", arizona_lhpf2_mode),
SOC_ENUM("LHPF3 Mode", arizona_lhpf3_mode),
SOC_ENUM("LHPF4 Mode", arizona_lhpf4_mode),

ARIZONA_LHPF_CONTROL("LHPF1 Coefficients", ARIZONA_HPLPF1_2),
ARIZONA_LHPF_CONTROL("LHPF2 Coefficients", ARIZONA_HPLPF2_2),
ARIZONA_LHPF_CONTROL("LHPF3 Coefficients", ARIZONA_HPLPF3_2),
ARIZONA_LHPF_CONTROL("LHPF4 Coefficients", ARIZONA_HPLPF4_2),

SOC_ENUM("ISRC1 FSL", arizona_isrc_fsl[0]),
SOC_ENUM("ISRC2 FSL", arizona_isrc_fsl[1]),

ARIZONA_MIXER_CONTROLS("Mic", ARIZONA_MICMIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("Noise", ARIZONA_NOISEMIX_INPUT_1_SOURCE),

SOC_SINGLE_TLV("Noise Generator Volume", ARIZONA_COMFORT_NOISE_GENERATOR,
	       ARIZONA_NOISE_GEN_GAIN_SHIFT, 0x16, 0, noise_tlv),

ARIZONA_MIXER_CONTROLS("HPOUT1L", ARIZONA_OUT1LMIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("HPOUT1R", ARIZONA_OUT1RMIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("EPOUT", ARIZONA_OUT3LMIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SPKOUT", ARIZONA_OUT4LMIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SPKDAT1L", ARIZONA_OUT5LMIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SPKDAT1R", ARIZONA_OUT5RMIX_INPUT_1_SOURCE),

SOC_SINGLE("Speaker High Performance Switch", ARIZONA_OUTPUT_PATH_CONFIG_4L,
	   ARIZONA_OUT4_OSR_SHIFT, 1, 0),
SOC_SINGLE("SPKDAT1 High Performance Switch", ARIZONA_OUTPUT_PATH_CONFIG_5L,
	   ARIZONA_OUT5_OSR_SHIFT, 1, 0),

SOC_DOUBLE_R("HPOUT1 Digital Switch", ARIZONA_DAC_DIGITAL_VOLUME_1L,
	     ARIZONA_DAC_DIGITAL_VOLUME_1R, ARIZONA_OUT1L_MUTE_SHIFT, 1, 1),
SOC_SINGLE("EPOUT Digital Switch", ARIZONA_DAC_DIGITAL_VOLUME_3L,
	   ARIZONA_OUT3L_MUTE_SHIFT, 1, 1),
SOC_SINGLE("Speaker Digital Switch", ARIZONA_DAC_DIGITAL_VOLUME_4L,
	   ARIZONA_OUT4L_MUTE_SHIFT, 1, 1),
SOC_DOUBLE_R("SPKDAT1 Digital Switch", ARIZONA_DAC_DIGITAL_VOLUME_5L,
	     ARIZONA_DAC_DIGITAL_VOLUME_5R, ARIZONA_OUT5L_MUTE_SHIFT, 1, 1),

SOC_DOUBLE_R_TLV("HPOUT1 Digital Volume", ARIZONA_DAC_DIGITAL_VOLUME_1L,
		 ARIZONA_DAC_DIGITAL_VOLUME_1R, ARIZONA_OUT1L_VOL_SHIFT,
		 0xbf, 0, digital_tlv),
SOC_SINGLE_TLV("EPOUT Digital Volume", ARIZONA_DAC_DIGITAL_VOLUME_3L,
	       ARIZONA_OUT3L_VOL_SHIFT, 0xbf, 0, digital_tlv),
SOC_SINGLE_TLV("Speaker Digital Volume", ARIZONA_DAC_DIGITAL_VOLUME_4L,
	       ARIZONA_OUT4L_VOL_SHIFT, 0xbf, 0, digital_tlv),
SOC_DOUBLE_R_TLV("SPKDAT1 Digital Volume", ARIZONA_DAC_DIGITAL_VOLUME_5L,
		 ARIZONA_DAC_DIGITAL_VOLUME_5R, ARIZONA_OUT5L_VOL_SHIFT,
		 0xbf, 0, digital_tlv),

SOC_ENUM("HPOUT1 OSR", wm8997_hpout_osr[0]),
SOC_ENUM("EPOUT OSR", wm8997_hpout_osr[1]),

SOC_ENUM("Output Ramp Up", arizona_out_vi_ramp),
SOC_ENUM("Output Ramp Down", arizona_out_vd_ramp),

SOC_DOUBLE("SPKDAT1 Switch", ARIZONA_PDM_SPK1_CTRL_1, ARIZONA_SPK1L_MUTE_SHIFT,
	   ARIZONA_SPK1R_MUTE_SHIFT, 1, 1),

SOC_SINGLE("Noise Gate Switch", ARIZONA_NOISE_GATE_CONTROL,
	   ARIZONA_NGATE_ENA_SHIFT, 1, 0),
SOC_SINGLE_TLV("Noise Gate Threshold Volume", ARIZONA_NOISE_GATE_CONTROL,
	       ARIZONA_NGATE_THR_SHIFT, 7, 1, ng_tlv),
SOC_ENUM("Noise Gate Hold", arizona_ng_hold),

WM8997_NG_SRC("HPOUT1L", ARIZONA_NOISE_GATE_SELECT_1L),
WM8997_NG_SRC("HPOUT1R", ARIZONA_NOISE_GATE_SELECT_1R),
WM8997_NG_SRC("EPOUT", ARIZONA_NOISE_GATE_SELECT_3L),
WM8997_NG_SRC("SPKOUT", ARIZONA_NOISE_GATE_SELECT_4L),
WM8997_NG_SRC("SPKDAT1L", ARIZONA_NOISE_GATE_SELECT_5L),
WM8997_NG_SRC("SPKDAT1R", ARIZONA_NOISE_GATE_SELECT_5R),

ARIZONA_MIXER_CONTROLS("AIF1TX1", ARIZONA_AIF1TX1MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF1TX2", ARIZONA_AIF1TX2MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF1TX3", ARIZONA_AIF1TX3MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF1TX4", ARIZONA_AIF1TX4MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF1TX5", ARIZONA_AIF1TX5MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF1TX6", ARIZONA_AIF1TX6MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF1TX7", ARIZONA_AIF1TX7MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF1TX8", ARIZONA_AIF1TX8MIX_INPUT_1_SOURCE),

ARIZONA_MIXER_CONTROLS("AIF2TX1", ARIZONA_AIF2TX1MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("AIF2TX2", ARIZONA_AIF2TX2MIX_INPUT_1_SOURCE),

ARIZONA_MIXER_CONTROLS("SLIMTX1", ARIZONA_SLIMTX1MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SLIMTX2", ARIZONA_SLIMTX2MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SLIMTX3", ARIZONA_SLIMTX3MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SLIMTX4", ARIZONA_SLIMTX4MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SLIMTX5", ARIZONA_SLIMTX5MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SLIMTX6", ARIZONA_SLIMTX6MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SLIMTX7", ARIZONA_SLIMTX7MIX_INPUT_1_SOURCE),
ARIZONA_MIXER_CONTROLS("SLIMTX8", ARIZONA_SLIMTX8MIX_INPUT_1_SOURCE),
पूर्ण;

ARIZONA_MIXER_ENUMS(EQ1, ARIZONA_EQ1MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(EQ2, ARIZONA_EQ2MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(EQ3, ARIZONA_EQ3MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(EQ4, ARIZONA_EQ4MIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(DRC1L, ARIZONA_DRC1LMIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(DRC1R, ARIZONA_DRC1RMIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(LHPF1, ARIZONA_HPLP1MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(LHPF2, ARIZONA_HPLP2MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(LHPF3, ARIZONA_HPLP3MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(LHPF4, ARIZONA_HPLP4MIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(Mic, ARIZONA_MICMIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(Noise, ARIZONA_NOISEMIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(PWM1, ARIZONA_PWM1MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(PWM2, ARIZONA_PWM2MIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(OUT1L, ARIZONA_OUT1LMIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(OUT1R, ARIZONA_OUT1RMIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(OUT3, ARIZONA_OUT3LMIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SPKOUT, ARIZONA_OUT4LMIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SPKDAT1L, ARIZONA_OUT5LMIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SPKDAT1R, ARIZONA_OUT5RMIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(AIF1TX1, ARIZONA_AIF1TX1MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF1TX2, ARIZONA_AIF1TX2MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF1TX3, ARIZONA_AIF1TX3MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF1TX4, ARIZONA_AIF1TX4MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF1TX5, ARIZONA_AIF1TX5MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF1TX6, ARIZONA_AIF1TX6MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF1TX7, ARIZONA_AIF1TX7MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF1TX8, ARIZONA_AIF1TX8MIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(AIF2TX1, ARIZONA_AIF2TX1MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(AIF2TX2, ARIZONA_AIF2TX2MIX_INPUT_1_SOURCE);

ARIZONA_MIXER_ENUMS(SLIMTX1, ARIZONA_SLIMTX1MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SLIMTX2, ARIZONA_SLIMTX2MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SLIMTX3, ARIZONA_SLIMTX3MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SLIMTX4, ARIZONA_SLIMTX4MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SLIMTX5, ARIZONA_SLIMTX5MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SLIMTX6, ARIZONA_SLIMTX6MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SLIMTX7, ARIZONA_SLIMTX7MIX_INPUT_1_SOURCE);
ARIZONA_MIXER_ENUMS(SLIMTX8, ARIZONA_SLIMTX8MIX_INPUT_1_SOURCE);

ARIZONA_MUX_ENUMS(ISRC1INT1, ARIZONA_ISRC1INT1MIX_INPUT_1_SOURCE);
ARIZONA_MUX_ENUMS(ISRC1INT2, ARIZONA_ISRC1INT2MIX_INPUT_1_SOURCE);

ARIZONA_MUX_ENUMS(ISRC1DEC1, ARIZONA_ISRC1DEC1MIX_INPUT_1_SOURCE);
ARIZONA_MUX_ENUMS(ISRC1DEC2, ARIZONA_ISRC1DEC2MIX_INPUT_1_SOURCE);

ARIZONA_MUX_ENUMS(ISRC2INT1, ARIZONA_ISRC2INT1MIX_INPUT_1_SOURCE);
ARIZONA_MUX_ENUMS(ISRC2INT2, ARIZONA_ISRC2INT2MIX_INPUT_1_SOURCE);

ARIZONA_MUX_ENUMS(ISRC2DEC1, ARIZONA_ISRC2DEC1MIX_INPUT_1_SOURCE);
ARIZONA_MUX_ENUMS(ISRC2DEC2, ARIZONA_ISRC2DEC2MIX_INPUT_1_SOURCE);

अटल स्थिर अक्षर *wm8997_aec_loopback_texts[] = अणु
	"HPOUT1L", "HPOUT1R", "EPOUT", "SPKOUT", "SPKDAT1L", "SPKDAT1R",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक wm8997_aec_loopback_values[] = अणु
	0, 1, 4, 6, 8, 9,
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8997_aec_loopback =
	SOC_VALUE_ENUM_SINGLE(ARIZONA_DAC_AEC_CONTROL_1,
			      ARIZONA_AEC_LOOPBACK_SRC_SHIFT, 0xf,
			      ARRAY_SIZE(wm8997_aec_loopback_texts),
			      wm8997_aec_loopback_texts,
			      wm8997_aec_loopback_values);

अटल स्थिर काष्ठा snd_kcontrol_new wm8997_aec_loopback_mux =
	SOC_DAPM_ENUM("AEC Loopback", wm8997_aec_loopback);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8997_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("SYSCLK", ARIZONA_SYSTEM_CLOCK_1, ARIZONA_SYSCLK_ENA_SHIFT,
		    0, wm8997_sysclk_ev,
		    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD |
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("ASYNCCLK", ARIZONA_ASYNC_CLOCK_1,
		    ARIZONA_ASYNC_CLK_ENA_SHIFT, 0, arizona_clk_ev,
		    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_SUPPLY("OPCLK", ARIZONA_OUTPUT_SYSTEM_CLOCK,
		    ARIZONA_OPCLK_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("ASYNCOPCLK", ARIZONA_OUTPUT_ASYNC_CLOCK,
		    ARIZONA_OPCLK_ASYNC_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_REGULATOR_SUPPLY("DBVDD2", 0, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("CPVDD", 20, 0),
SND_SOC_DAPM_REGULATOR_SUPPLY("MICVDD", 0, SND_SOC_DAPM_REGULATOR_BYPASS),
SND_SOC_DAPM_REGULATOR_SUPPLY("SPKVDD", 0, 0),

SND_SOC_DAPM_SIGGEN("TONE"),
SND_SOC_DAPM_SIGGEN("NOISE"),
SND_SOC_DAPM_SIGGEN("HAPTICS"),

SND_SOC_DAPM_INPUT("IN1L"),
SND_SOC_DAPM_INPUT("IN1R"),
SND_SOC_DAPM_INPUT("IN2L"),
SND_SOC_DAPM_INPUT("IN2R"),

SND_SOC_DAPM_PGA_E("IN1L PGA", ARIZONA_INPUT_ENABLES, ARIZONA_IN1L_ENA_SHIFT,
		   0, शून्य, 0, arizona_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN1R PGA", ARIZONA_INPUT_ENABLES, ARIZONA_IN1R_ENA_SHIFT,
		   0, शून्य, 0, arizona_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN2L PGA", ARIZONA_INPUT_ENABLES, ARIZONA_IN2L_ENA_SHIFT,
		   0, शून्य, 0, arizona_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("IN2R PGA", ARIZONA_INPUT_ENABLES, ARIZONA_IN2R_ENA_SHIFT,
		   0, शून्य, 0, arizona_in_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

SND_SOC_DAPM_SUPPLY("MICBIAS1", ARIZONA_MIC_BIAS_CTRL_1,
		    ARIZONA_MICB1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS2", ARIZONA_MIC_BIAS_CTRL_2,
		    ARIZONA_MICB2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MICBIAS3", ARIZONA_MIC_BIAS_CTRL_3,
		    ARIZONA_MICB3_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Noise Generator", ARIZONA_COMFORT_NOISE_GENERATOR,
		 ARIZONA_NOISE_GEN_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Tone Generator 1", ARIZONA_TONE_GENERATOR_1,
		 ARIZONA_TONE1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Tone Generator 2", ARIZONA_TONE_GENERATOR_1,
		 ARIZONA_TONE2_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("Mic Mute Mixer", ARIZONA_MIC_NOISE_MIX_CONTROL_1,
		 ARIZONA_MICMUTE_MIX_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("EQ1", ARIZONA_EQ1_1, ARIZONA_EQ1_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ2", ARIZONA_EQ2_1, ARIZONA_EQ2_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ3", ARIZONA_EQ3_1, ARIZONA_EQ3_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("EQ4", ARIZONA_EQ4_1, ARIZONA_EQ4_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("DRC1L", ARIZONA_DRC1_CTRL1, ARIZONA_DRC1L_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("DRC1R", ARIZONA_DRC1_CTRL1, ARIZONA_DRC1R_ENA_SHIFT, 0,
		 शून्य, 0),

SND_SOC_DAPM_PGA("LHPF1", ARIZONA_HPLPF1_1, ARIZONA_LHPF1_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF2", ARIZONA_HPLPF2_1, ARIZONA_LHPF2_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF3", ARIZONA_HPLPF3_1, ARIZONA_LHPF3_ENA_SHIFT, 0,
		 शून्य, 0),
SND_SOC_DAPM_PGA("LHPF4", ARIZONA_HPLPF4_1, ARIZONA_LHPF4_ENA_SHIFT, 0,
		 शून्य, 0),

SND_SOC_DAPM_PGA("PWM1 Driver", ARIZONA_PWM_DRIVE_1, ARIZONA_PWM1_ENA_SHIFT,
		 0, शून्य, 0),
SND_SOC_DAPM_PGA("PWM2 Driver", ARIZONA_PWM_DRIVE_1, ARIZONA_PWM2_ENA_SHIFT,
		 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC1INT1", ARIZONA_ISRC_1_CTRL_3,
		 ARIZONA_ISRC1_INT0_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1INT2", ARIZONA_ISRC_1_CTRL_3,
		 ARIZONA_ISRC1_INT1_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC1DEC1", ARIZONA_ISRC_1_CTRL_3,
		 ARIZONA_ISRC1_DEC0_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC1DEC2", ARIZONA_ISRC_1_CTRL_3,
		 ARIZONA_ISRC1_DEC1_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC2INT1", ARIZONA_ISRC_2_CTRL_3,
		 ARIZONA_ISRC2_INT0_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2INT2", ARIZONA_ISRC_2_CTRL_3,
		 ARIZONA_ISRC2_INT1_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_PGA("ISRC2DEC1", ARIZONA_ISRC_2_CTRL_3,
		 ARIZONA_ISRC2_DEC0_ENA_SHIFT, 0, शून्य, 0),
SND_SOC_DAPM_PGA("ISRC2DEC2", ARIZONA_ISRC_2_CTRL_3,
		 ARIZONA_ISRC2_DEC1_ENA_SHIFT, 0, शून्य, 0),

SND_SOC_DAPM_AIF_OUT("AIF1TX1", शून्य, 0,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX2", शून्य, 1,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX3", शून्य, 2,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX4", शून्य, 3,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX5", शून्य, 4,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX6", शून्य, 5,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX7", शून्य, 6,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX8", शून्य, 7,
		     ARIZONA_AIF1_TX_ENABLES, ARIZONA_AIF1TX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF1RX1", शून्य, 0,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX2", शून्य, 1,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX3", शून्य, 2,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX4", शून्य, 3,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX5", शून्य, 4,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX6", शून्य, 5,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX7", शून्य, 6,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF1RX8", शून्य, 7,
		    ARIZONA_AIF1_RX_ENABLES, ARIZONA_AIF1RX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("AIF2TX1", शून्य, 0,
		     ARIZONA_AIF2_TX_ENABLES, ARIZONA_AIF2TX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("AIF2TX2", शून्य, 1,
		     ARIZONA_AIF2_TX_ENABLES, ARIZONA_AIF2TX2_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("AIF2RX1", शून्य, 0,
		    ARIZONA_AIF2_RX_ENABLES, ARIZONA_AIF2RX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("AIF2RX2", शून्य, 1,
		    ARIZONA_AIF2_RX_ENABLES, ARIZONA_AIF2RX2_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_OUT("SLIMTX1", शून्य, 0,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX2", शून्य, 1,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX3", शून्य, 2,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX4", शून्य, 3,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX5", शून्य, 4,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX6", शून्य, 5,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX7", शून्य, 6,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_OUT("SLIMTX8", शून्य, 7,
		     ARIZONA_SLIMBUS_TX_CHANNEL_ENABLE,
		     ARIZONA_SLIMTX8_ENA_SHIFT, 0),

SND_SOC_DAPM_AIF_IN("SLIMRX1", शून्य, 0,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX1_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX2", शून्य, 1,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX2_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX3", शून्य, 2,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX3_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX4", शून्य, 3,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX4_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX5", शून्य, 4,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX5_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX6", शून्य, 5,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX6_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX7", शून्य, 6,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX7_ENA_SHIFT, 0),
SND_SOC_DAPM_AIF_IN("SLIMRX8", शून्य, 7,
		    ARIZONA_SLIMBUS_RX_CHANNEL_ENABLE,
		    ARIZONA_SLIMRX8_ENA_SHIFT, 0),

SND_SOC_DAPM_MUX("AEC Loopback", ARIZONA_DAC_AEC_CONTROL_1,
		 ARIZONA_AEC_LOOPBACK_ENA_SHIFT, 0, &wm8997_aec_loopback_mux),

SND_SOC_DAPM_PGA_E("OUT1L", SND_SOC_NOPM,
		   ARIZONA_OUT1L_ENA_SHIFT, 0, शून्य, 0, arizona_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT1R", SND_SOC_NOPM,
		   ARIZONA_OUT1R_ENA_SHIFT, 0, शून्य, 0, arizona_hp_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT3L", ARIZONA_OUTPUT_ENABLES_1,
		   ARIZONA_OUT3L_ENA_SHIFT, 0, शून्य, 0, arizona_out_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD |
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT5L", ARIZONA_OUTPUT_ENABLES_1,
		   ARIZONA_OUT5L_ENA_SHIFT, 0, शून्य, 0, arizona_out_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
SND_SOC_DAPM_PGA_E("OUT5R", ARIZONA_OUTPUT_ENABLES_1,
		   ARIZONA_OUT5R_ENA_SHIFT, 0, शून्य, 0, arizona_out_ev,
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),

ARIZONA_MIXER_WIDGETS(EQ1, "EQ1"),
ARIZONA_MIXER_WIDGETS(EQ2, "EQ2"),
ARIZONA_MIXER_WIDGETS(EQ3, "EQ3"),
ARIZONA_MIXER_WIDGETS(EQ4, "EQ4"),

ARIZONA_MIXER_WIDGETS(DRC1L, "DRC1L"),
ARIZONA_MIXER_WIDGETS(DRC1R, "DRC1R"),

ARIZONA_MIXER_WIDGETS(LHPF1, "LHPF1"),
ARIZONA_MIXER_WIDGETS(LHPF2, "LHPF2"),
ARIZONA_MIXER_WIDGETS(LHPF3, "LHPF3"),
ARIZONA_MIXER_WIDGETS(LHPF4, "LHPF4"),

ARIZONA_MIXER_WIDGETS(Mic, "Mic"),
ARIZONA_MIXER_WIDGETS(Noise, "Noise"),

ARIZONA_MIXER_WIDGETS(PWM1, "PWM1"),
ARIZONA_MIXER_WIDGETS(PWM2, "PWM2"),

ARIZONA_MIXER_WIDGETS(OUT1L, "HPOUT1L"),
ARIZONA_MIXER_WIDGETS(OUT1R, "HPOUT1R"),
ARIZONA_MIXER_WIDGETS(OUT3, "EPOUT"),
ARIZONA_MIXER_WIDGETS(SPKOUT, "SPKOUT"),
ARIZONA_MIXER_WIDGETS(SPKDAT1L, "SPKDAT1L"),
ARIZONA_MIXER_WIDGETS(SPKDAT1R, "SPKDAT1R"),

ARIZONA_MIXER_WIDGETS(AIF1TX1, "AIF1TX1"),
ARIZONA_MIXER_WIDGETS(AIF1TX2, "AIF1TX2"),
ARIZONA_MIXER_WIDGETS(AIF1TX3, "AIF1TX3"),
ARIZONA_MIXER_WIDGETS(AIF1TX4, "AIF1TX4"),
ARIZONA_MIXER_WIDGETS(AIF1TX5, "AIF1TX5"),
ARIZONA_MIXER_WIDGETS(AIF1TX6, "AIF1TX6"),
ARIZONA_MIXER_WIDGETS(AIF1TX7, "AIF1TX7"),
ARIZONA_MIXER_WIDGETS(AIF1TX8, "AIF1TX8"),

ARIZONA_MIXER_WIDGETS(AIF2TX1, "AIF2TX1"),
ARIZONA_MIXER_WIDGETS(AIF2TX2, "AIF2TX2"),

ARIZONA_MIXER_WIDGETS(SLIMTX1, "SLIMTX1"),
ARIZONA_MIXER_WIDGETS(SLIMTX2, "SLIMTX2"),
ARIZONA_MIXER_WIDGETS(SLIMTX3, "SLIMTX3"),
ARIZONA_MIXER_WIDGETS(SLIMTX4, "SLIMTX4"),
ARIZONA_MIXER_WIDGETS(SLIMTX5, "SLIMTX5"),
ARIZONA_MIXER_WIDGETS(SLIMTX6, "SLIMTX6"),
ARIZONA_MIXER_WIDGETS(SLIMTX7, "SLIMTX7"),
ARIZONA_MIXER_WIDGETS(SLIMTX8, "SLIMTX8"),

ARIZONA_MUX_WIDGETS(ISRC1DEC1, "ISRC1DEC1"),
ARIZONA_MUX_WIDGETS(ISRC1DEC2, "ISRC1DEC2"),

ARIZONA_MUX_WIDGETS(ISRC1INT1, "ISRC1INT1"),
ARIZONA_MUX_WIDGETS(ISRC1INT2, "ISRC1INT2"),

ARIZONA_MUX_WIDGETS(ISRC2DEC1, "ISRC2DEC1"),
ARIZONA_MUX_WIDGETS(ISRC2DEC2, "ISRC2DEC2"),

ARIZONA_MUX_WIDGETS(ISRC2INT1, "ISRC2INT1"),
ARIZONA_MUX_WIDGETS(ISRC2INT2, "ISRC2INT2"),

SND_SOC_DAPM_OUTPUT("HPOUT1L"),
SND_SOC_DAPM_OUTPUT("HPOUT1R"),
SND_SOC_DAPM_OUTPUT("EPOUTN"),
SND_SOC_DAPM_OUTPUT("EPOUTP"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),
SND_SOC_DAPM_OUTPUT("SPKOUTP"),
SND_SOC_DAPM_OUTPUT("SPKDAT1L"),
SND_SOC_DAPM_OUTPUT("SPKDAT1R"),

SND_SOC_DAPM_OUTPUT("MICSUPP"),
पूर्ण;

#घोषणा ARIZONA_MIXER_INPUT_ROUTES(name)	\
	अणु name, "Noise Generator", "Noise Generator" पूर्ण, \
	अणु name, "Tone Generator 1", "Tone Generator 1" पूर्ण, \
	अणु name, "Tone Generator 2", "Tone Generator 2" पूर्ण, \
	अणु name, "Haptics", "HAPTICS" पूर्ण, \
	अणु name, "AEC", "AEC Loopback" पूर्ण, \
	अणु name, "IN1L", "IN1L PGA" पूर्ण, \
	अणु name, "IN1R", "IN1R PGA" पूर्ण, \
	अणु name, "IN2L", "IN2L PGA" पूर्ण, \
	अणु name, "IN2R", "IN2R PGA" पूर्ण, \
	अणु name, "Mic Mute Mixer", "Mic Mute Mixer" पूर्ण, \
	अणु name, "AIF1RX1", "AIF1RX1" पूर्ण, \
	अणु name, "AIF1RX2", "AIF1RX2" पूर्ण, \
	अणु name, "AIF1RX3", "AIF1RX3" पूर्ण, \
	अणु name, "AIF1RX4", "AIF1RX4" पूर्ण, \
	अणु name, "AIF1RX5", "AIF1RX5" पूर्ण, \
	अणु name, "AIF1RX6", "AIF1RX6" पूर्ण, \
	अणु name, "AIF1RX7", "AIF1RX7" पूर्ण, \
	अणु name, "AIF1RX8", "AIF1RX8" पूर्ण, \
	अणु name, "AIF2RX1", "AIF2RX1" पूर्ण, \
	अणु name, "AIF2RX2", "AIF2RX2" पूर्ण, \
	अणु name, "SLIMRX1", "SLIMRX1" पूर्ण, \
	अणु name, "SLIMRX2", "SLIMRX2" पूर्ण, \
	अणु name, "SLIMRX3", "SLIMRX3" पूर्ण, \
	अणु name, "SLIMRX4", "SLIMRX4" पूर्ण, \
	अणु name, "SLIMRX5", "SLIMRX5" पूर्ण, \
	अणु name, "SLIMRX6", "SLIMRX6" पूर्ण, \
	अणु name, "SLIMRX7", "SLIMRX7" पूर्ण, \
	अणु name, "SLIMRX8", "SLIMRX8" पूर्ण, \
	अणु name, "EQ1", "EQ1" पूर्ण, \
	अणु name, "EQ2", "EQ2" पूर्ण, \
	अणु name, "EQ3", "EQ3" पूर्ण, \
	अणु name, "EQ4", "EQ4" पूर्ण, \
	अणु name, "DRC1L", "DRC1L" पूर्ण, \
	अणु name, "DRC1R", "DRC1R" पूर्ण, \
	अणु name, "LHPF1", "LHPF1" पूर्ण, \
	अणु name, "LHPF2", "LHPF2" पूर्ण, \
	अणु name, "LHPF3", "LHPF3" पूर्ण, \
	अणु name, "LHPF4", "LHPF4" पूर्ण, \
	अणु name, "ISRC1DEC1", "ISRC1DEC1" पूर्ण, \
	अणु name, "ISRC1DEC2", "ISRC1DEC2" पूर्ण, \
	अणु name, "ISRC1INT1", "ISRC1INT1" पूर्ण, \
	अणु name, "ISRC1INT2", "ISRC1INT2" पूर्ण, \
	अणु name, "ISRC2DEC1", "ISRC2DEC1" पूर्ण, \
	अणु name, "ISRC2DEC2", "ISRC2DEC2" पूर्ण, \
	अणु name, "ISRC2INT1", "ISRC2INT1" पूर्ण, \
	अणु name, "ISRC2INT2", "ISRC2INT2" पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route wm8997_dapm_routes[] = अणु
	अणु "AIF2 Capture", शून्य, "DBVDD2" पूर्ण,
	अणु "AIF2 Playback", शून्य, "DBVDD2" पूर्ण,

	अणु "OUT1L", शून्य, "CPVDD" पूर्ण,
	अणु "OUT1R", शून्य, "CPVDD" पूर्ण,
	अणु "OUT3L", शून्य, "CPVDD" पूर्ण,

	अणु "OUT4L", शून्य, "SPKVDD" पूर्ण,

	अणु "OUT1L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT1R", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT3L", शून्य, "SYSCLK" पूर्ण,
	अणु "OUT4L", शून्य, "SYSCLK" पूर्ण,

	अणु "IN1L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN1R", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2L", शून्य, "SYSCLK" पूर्ण,
	अणु "IN2R", शून्य, "SYSCLK" पूर्ण,

	अणु "MICBIAS1", शून्य, "MICVDD" पूर्ण,
	अणु "MICBIAS2", शून्य, "MICVDD" पूर्ण,
	अणु "MICBIAS3", शून्य, "MICVDD" पूर्ण,

	अणु "Noise Generator", शून्य, "SYSCLK" पूर्ण,
	अणु "Tone Generator 1", शून्य, "SYSCLK" पूर्ण,
	अणु "Tone Generator 2", शून्य, "SYSCLK" पूर्ण,

	अणु "Noise Generator", शून्य, "NOISE" पूर्ण,
	अणु "Tone Generator 1", शून्य, "TONE" पूर्ण,
	अणु "Tone Generator 2", शून्य, "TONE" पूर्ण,

	अणु "AIF1 Capture", शून्य, "AIF1TX1" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX2" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX3" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX4" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX5" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX6" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX7" पूर्ण,
	अणु "AIF1 Capture", शून्य, "AIF1TX8" पूर्ण,

	अणु "AIF1RX1", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX2", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX3", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX4", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX5", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX6", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX7", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1RX8", शून्य, "AIF1 Playback" पूर्ण,

	अणु "AIF2 Capture", शून्य, "AIF2TX1" पूर्ण,
	अणु "AIF2 Capture", शून्य, "AIF2TX2" पूर्ण,

	अणु "AIF2RX1", शून्य, "AIF2 Playback" पूर्ण,
	अणु "AIF2RX2", शून्य, "AIF2 Playback" पूर्ण,

	अणु "Slim1 Capture", शून्य, "SLIMTX1" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SLIMTX2" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SLIMTX3" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SLIMTX4" पूर्ण,

	अणु "SLIMRX1", शून्य, "Slim1 Playback" पूर्ण,
	अणु "SLIMRX2", शून्य, "Slim1 Playback" पूर्ण,
	अणु "SLIMRX3", शून्य, "Slim1 Playback" पूर्ण,
	अणु "SLIMRX4", शून्य, "Slim1 Playback" पूर्ण,

	अणु "Slim2 Capture", शून्य, "SLIMTX5" पूर्ण,
	अणु "Slim2 Capture", शून्य, "SLIMTX6" पूर्ण,

	अणु "SLIMRX5", शून्य, "Slim2 Playback" पूर्ण,
	अणु "SLIMRX6", शून्य, "Slim2 Playback" पूर्ण,

	अणु "Slim3 Capture", शून्य, "SLIMTX7" पूर्ण,
	अणु "Slim3 Capture", शून्य, "SLIMTX8" पूर्ण,

	अणु "SLIMRX7", शून्य, "Slim3 Playback" पूर्ण,
	अणु "SLIMRX8", शून्य, "Slim3 Playback" पूर्ण,

	अणु "AIF1 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim1 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim2 Playback", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim3 Playback", शून्य, "SYSCLK" पूर्ण,

	अणु "AIF1 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "AIF2 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim1 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim2 Capture", शून्य, "SYSCLK" पूर्ण,
	अणु "Slim3 Capture", शून्य, "SYSCLK" पूर्ण,

	अणु "IN1L PGA", शून्य, "IN1L" पूर्ण,
	अणु "IN1R PGA", शून्य, "IN1R" पूर्ण,

	अणु "IN2L PGA", शून्य, "IN2L" पूर्ण,
	अणु "IN2R PGA", शून्य, "IN2R" पूर्ण,

	ARIZONA_MIXER_ROUTES("OUT1L", "HPOUT1L"),
	ARIZONA_MIXER_ROUTES("OUT1R", "HPOUT1R"),
	ARIZONA_MIXER_ROUTES("OUT3L", "EPOUT"),

	ARIZONA_MIXER_ROUTES("OUT4L", "SPKOUT"),
	ARIZONA_MIXER_ROUTES("OUT5L", "SPKDAT1L"),
	ARIZONA_MIXER_ROUTES("OUT5R", "SPKDAT1R"),

	ARIZONA_MIXER_ROUTES("PWM1 Driver", "PWM1"),
	ARIZONA_MIXER_ROUTES("PWM2 Driver", "PWM2"),

	ARIZONA_MIXER_ROUTES("AIF1TX1", "AIF1TX1"),
	ARIZONA_MIXER_ROUTES("AIF1TX2", "AIF1TX2"),
	ARIZONA_MIXER_ROUTES("AIF1TX3", "AIF1TX3"),
	ARIZONA_MIXER_ROUTES("AIF1TX4", "AIF1TX4"),
	ARIZONA_MIXER_ROUTES("AIF1TX5", "AIF1TX5"),
	ARIZONA_MIXER_ROUTES("AIF1TX6", "AIF1TX6"),
	ARIZONA_MIXER_ROUTES("AIF1TX7", "AIF1TX7"),
	ARIZONA_MIXER_ROUTES("AIF1TX8", "AIF1TX8"),

	ARIZONA_MIXER_ROUTES("AIF2TX1", "AIF2TX1"),
	ARIZONA_MIXER_ROUTES("AIF2TX2", "AIF2TX2"),

	ARIZONA_MIXER_ROUTES("SLIMTX1", "SLIMTX1"),
	ARIZONA_MIXER_ROUTES("SLIMTX2", "SLIMTX2"),
	ARIZONA_MIXER_ROUTES("SLIMTX3", "SLIMTX3"),
	ARIZONA_MIXER_ROUTES("SLIMTX4", "SLIMTX4"),
	ARIZONA_MIXER_ROUTES("SLIMTX5", "SLIMTX5"),
	ARIZONA_MIXER_ROUTES("SLIMTX6", "SLIMTX6"),
	ARIZONA_MIXER_ROUTES("SLIMTX7", "SLIMTX7"),
	ARIZONA_MIXER_ROUTES("SLIMTX8", "SLIMTX8"),

	ARIZONA_MIXER_ROUTES("EQ1", "EQ1"),
	ARIZONA_MIXER_ROUTES("EQ2", "EQ2"),
	ARIZONA_MIXER_ROUTES("EQ3", "EQ3"),
	ARIZONA_MIXER_ROUTES("EQ4", "EQ4"),

	ARIZONA_MIXER_ROUTES("DRC1L", "DRC1L"),
	ARIZONA_MIXER_ROUTES("DRC1R", "DRC1R"),

	ARIZONA_MIXER_ROUTES("LHPF1", "LHPF1"),
	ARIZONA_MIXER_ROUTES("LHPF2", "LHPF2"),
	ARIZONA_MIXER_ROUTES("LHPF3", "LHPF3"),
	ARIZONA_MIXER_ROUTES("LHPF4", "LHPF4"),

	ARIZONA_MIXER_ROUTES("Mic Mute Mixer", "Noise"),
	ARIZONA_MIXER_ROUTES("Mic Mute Mixer", "Mic"),

	ARIZONA_MUX_ROUTES("ISRC1INT1", "ISRC1INT1"),
	ARIZONA_MUX_ROUTES("ISRC1INT2", "ISRC1INT2"),

	ARIZONA_MUX_ROUTES("ISRC1DEC1", "ISRC1DEC1"),
	ARIZONA_MUX_ROUTES("ISRC1DEC2", "ISRC1DEC2"),

	ARIZONA_MUX_ROUTES("ISRC2INT1", "ISRC2INT1"),
	ARIZONA_MUX_ROUTES("ISRC2INT2", "ISRC2INT2"),

	ARIZONA_MUX_ROUTES("ISRC2DEC1", "ISRC2DEC1"),
	ARIZONA_MUX_ROUTES("ISRC2DEC2", "ISRC2DEC2"),

	अणु "AEC Loopback", "HPOUT1L", "OUT1L" पूर्ण,
	अणु "AEC Loopback", "HPOUT1R", "OUT1R" पूर्ण,
	अणु "HPOUT1L", शून्य, "OUT1L" पूर्ण,
	अणु "HPOUT1R", शून्य, "OUT1R" पूर्ण,

	अणु "AEC Loopback", "EPOUT", "OUT3L" पूर्ण,
	अणु "EPOUTN", शून्य, "OUT3L" पूर्ण,
	अणु "EPOUTP", शून्य, "OUT3L" पूर्ण,

	अणु "AEC Loopback", "SPKOUT", "OUT4L" पूर्ण,
	अणु "SPKOUTN", शून्य, "OUT4L" पूर्ण,
	अणु "SPKOUTP", शून्य, "OUT4L" पूर्ण,

	अणु "AEC Loopback", "SPKDAT1L", "OUT5L" पूर्ण,
	अणु "AEC Loopback", "SPKDAT1R", "OUT5R" पूर्ण,
	अणु "SPKDAT1L", शून्य, "OUT5L" पूर्ण,
	अणु "SPKDAT1R", शून्य, "OUT5R" पूर्ण,

	अणु "MICSUPP", शून्य, "SYSCLK" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8997_set_fll(काष्ठा snd_soc_component *component, पूर्णांक fll_id,
			  पूर्णांक source, अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	काष्ठा wm8997_priv *wm8997 = snd_soc_component_get_drvdata(component);

	चयन (fll_id) अणु
	हाल WM8997_FLL1:
		वापस arizona_set_fll(&wm8997->fll[0], source, Fref, Fout);
	हाल WM8997_FLL2:
		वापस arizona_set_fll(&wm8997->fll[1], source, Fref, Fout);
	हाल WM8997_FLL1_REFCLK:
		वापस arizona_set_fll_refclk(&wm8997->fll[0], source, Fref,
					      Fout);
	हाल WM8997_FLL2_REFCLK:
		वापस arizona_set_fll_refclk(&wm8997->fll[1], source, Fref,
					      Fout);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा WM8997_RATES SNDRV_PCM_RATE_KNOT

#घोषणा WM8997_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver wm8997_dai[] = अणु
	अणु
		.name = "wm8997-aif1",
		.id = 1,
		.base = ARIZONA_AIF1_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.capture = अणु
			 .stream_name = "AIF1 Capture",
			 .channels_min = 1,
			 .channels_max = 8,
			 .rates = WM8997_RATES,
			 .क्रमmats = WM8997_FORMATS,
		 पूर्ण,
		.ops = &arizona_dai_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "wm8997-aif2",
		.id = 2,
		.base = ARIZONA_AIF2_BCLK_CTRL,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.capture = अणु
			 .stream_name = "AIF2 Capture",
			 .channels_min = 1,
			 .channels_max = 2,
			 .rates = WM8997_RATES,
			 .क्रमmats = WM8997_FORMATS,
		 पूर्ण,
		.ops = &arizona_dai_ops,
		.symmetric_rate = 1,
		.symmetric_sample_bits = 1,
	पूर्ण,
	अणु
		.name = "wm8997-slim1",
		.id = 3,
		.playback = अणु
			.stream_name = "Slim1 Playback",
			.channels_min = 1,
			.channels_max = 4,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Slim1 Capture",
			.channels_min = 1,
			.channels_max = 4,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.ops = &arizona_simple_dai_ops,
	पूर्ण,
	अणु
		.name = "wm8997-slim2",
		.id = 4,
		.playback = अणु
			.stream_name = "Slim2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Slim2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.ops = &arizona_simple_dai_ops,
	पूर्ण,
	अणु
		.name = "wm8997-slim3",
		.id = 5,
		.playback = अणु
			.stream_name = "Slim3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Slim3 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM8997_RATES,
			.क्रमmats = WM8997_FORMATS,
		पूर्ण,
		.ops = &arizona_simple_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm8997_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा wm8997_priv *priv = snd_soc_component_get_drvdata(component);
	काष्ठा arizona *arizona = priv->core.arizona;
	पूर्णांक ret;

	snd_soc_component_init_regmap(component, arizona->regmap);

	ret = arizona_init_spk(component);
	अगर (ret < 0)
		वापस ret;

	snd_soc_component_disable_pin(component, "HAPTICS");

	priv->core.arizona->dapm = dapm;

	वापस 0;
पूर्ण

अटल व्योम wm8997_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8997_priv *priv = snd_soc_component_get_drvdata(component);

	priv->core.arizona->dapm = शून्य;
पूर्ण

#घोषणा WM8997_DIG_VU 0x0200

अटल अचिन्हित पूर्णांक wm8997_digital_vu[] = अणु
	ARIZONA_DAC_DIGITAL_VOLUME_1L,
	ARIZONA_DAC_DIGITAL_VOLUME_1R,
	ARIZONA_DAC_DIGITAL_VOLUME_3L,
	ARIZONA_DAC_DIGITAL_VOLUME_4L,
	ARIZONA_DAC_DIGITAL_VOLUME_5L,
	ARIZONA_DAC_DIGITAL_VOLUME_5R,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8997 = अणु
	.probe			= wm8997_component_probe,
	.हटाओ			= wm8997_component_हटाओ,
	.set_sysclk		= arizona_set_sysclk,
	.set_pll		= wm8997_set_fll,
	.set_jack		= arizona_jack_set_jack,
	.controls		= wm8997_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8997_snd_controls),
	.dapm_widमाला_लो		= wm8997_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8997_dapm_widमाला_लो),
	.dapm_routes		= wm8997_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8997_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8997_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm8997_priv *wm8997;
	पूर्णांक i, ret;

	wm8997 = devm_kzalloc(&pdev->dev, माप(काष्ठा wm8997_priv),
			      GFP_KERNEL);
	अगर (wm8997 == शून्य)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, wm8997);

	अगर (IS_ENABLED(CONFIG_OF)) अणु
		अगर (!dev_get_platdata(arizona->dev)) अणु
			ret = arizona_of_get_audio_pdata(arizona);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	wm8997->core.arizona = arizona;
	wm8997->core.num_inमाला_दो = 4;

	arizona_init_dvfs(&wm8997->core);

	/* This may वापस -EPROBE_DEFER, so करो this early on */
	ret = arizona_jack_codec_dev_probe(&wm8997->core, &pdev->dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(wm8997->fll); i++)
		wm8997->fll[i].vco_mult = 1;

	arizona_init_fll(arizona, 1, ARIZONA_FLL1_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL1_LOCK, ARIZONA_IRQ_FLL1_CLOCK_OK,
			 &wm8997->fll[0]);
	arizona_init_fll(arizona, 2, ARIZONA_FLL2_CONTROL_1 - 1,
			 ARIZONA_IRQ_FLL2_LOCK, ARIZONA_IRQ_FLL2_CLOCK_OK,
			 &wm8997->fll[1]);

	/* SR2 fixed at 8kHz, SR3 fixed at 16kHz */
	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_2,
			   ARIZONA_SAMPLE_RATE_2_MASK, 0x11);
	regmap_update_bits(arizona->regmap, ARIZONA_SAMPLE_RATE_3,
			   ARIZONA_SAMPLE_RATE_3_MASK, 0x12);

	क्रम (i = 0; i < ARRAY_SIZE(wm8997_dai); i++)
		arizona_init_dai(&wm8997->core, i);

	/* Latch volume update bits */
	क्रम (i = 0; i < ARRAY_SIZE(wm8997_digital_vu); i++)
		regmap_update_bits(arizona->regmap, wm8997_digital_vu[i],
				   WM8997_DIG_VU, WM8997_DIG_VU);

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_idle(&pdev->dev);

	arizona_init_common(arizona);

	ret = arizona_init_vol_limit(arizona);
	अगर (ret < 0)
		जाओ err_jack_codec_dev;
	ret = arizona_init_spk_irqs(arizona);
	अगर (ret < 0)
		जाओ err_jack_codec_dev;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &soc_component_dev_wm8997,
					      wm8997_dai,
					      ARRAY_SIZE(wm8997_dai));
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);
		जाओ err_spk_irqs;
	पूर्ण

	वापस ret;

err_spk_irqs:
	arizona_मुक्त_spk_irqs(arizona);
err_jack_codec_dev:
	arizona_jack_codec_dev_हटाओ(&wm8997->core);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8997_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8997_priv *wm8997 = platक्रमm_get_drvdata(pdev);
	काष्ठा arizona *arizona = wm8997->core.arizona;

	pm_runसमय_disable(&pdev->dev);

	arizona_मुक्त_spk_irqs(arizona);

	arizona_jack_codec_dev_हटाओ(&wm8997->core);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8997_codec_driver = अणु
	.driver = अणु
		.name = "wm8997-codec",
	पूर्ण,
	.probe = wm8997_probe,
	.हटाओ = wm8997_हटाओ,
पूर्ण;

module_platक्रमm_driver(wm8997_codec_driver);

MODULE_DESCRIPTION("ASoC WM8997 driver");
MODULE_AUTHOR("Charles Keepax <ckeepax@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8997-codec");
