<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8978.c  --  WM8978 ALSA SoC Audio Codec driver
 *
 * Copyright (C) 2009-2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 * Copyright (C) 2007 Carlos Munoz <carlos@kenati.com>
 * Copyright 2006-2009 Wolfson Microelectronics PLC.
 * Based on wm8974 and wm8990 by Liam Girdwood <lrg@slimlogic.co.uk>
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
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "wm8978.h"

अटल स्थिर काष्ठा reg_शेष wm8978_reg_शेषs[] = अणु
	अणु 1, 0x0000 पूर्ण,
	अणु 2, 0x0000 पूर्ण,
	अणु 3, 0x0000 पूर्ण,
	अणु 4, 0x0050 पूर्ण,
	अणु 5, 0x0000 पूर्ण,
	अणु 6, 0x0140 पूर्ण,
	अणु 7, 0x0000 पूर्ण,
	अणु 8, 0x0000 पूर्ण,
	अणु 9, 0x0000 पूर्ण,
	अणु 10, 0x0000 पूर्ण,
	अणु 11, 0x00ff पूर्ण,
	अणु 12, 0x00ff पूर्ण,
	अणु 13, 0x0000 पूर्ण,
	अणु 14, 0x0100 पूर्ण,
	अणु 15, 0x00ff पूर्ण,
	अणु 16, 0x00ff पूर्ण,
	अणु 17, 0x0000 पूर्ण,
	अणु 18, 0x012c पूर्ण,
	अणु 19, 0x002c पूर्ण,
	अणु 20, 0x002c पूर्ण,
	अणु 21, 0x002c पूर्ण,
	अणु 22, 0x002c पूर्ण,
	अणु 23, 0x0000 पूर्ण,
	अणु 24, 0x0032 पूर्ण,
	अणु 25, 0x0000 पूर्ण,
	अणु 26, 0x0000 पूर्ण,
	अणु 27, 0x0000 पूर्ण,
	अणु 28, 0x0000 पूर्ण,
	अणु 29, 0x0000 पूर्ण,
	अणु 30, 0x0000 पूर्ण,
	अणु 31, 0x0000 पूर्ण,
	अणु 32, 0x0038 पूर्ण,
	अणु 33, 0x000b पूर्ण,
	अणु 34, 0x0032 पूर्ण,
	अणु 35, 0x0000 पूर्ण,
	अणु 36, 0x0008 पूर्ण,
	अणु 37, 0x000c पूर्ण,
	अणु 38, 0x0093 पूर्ण,
	अणु 39, 0x00e9 पूर्ण,
	अणु 40, 0x0000 पूर्ण,
	अणु 41, 0x0000 पूर्ण,
	अणु 42, 0x0000 पूर्ण,
	अणु 43, 0x0000 पूर्ण,
	अणु 44, 0x0033 पूर्ण,
	अणु 45, 0x0010 पूर्ण,
	अणु 46, 0x0010 पूर्ण,
	अणु 47, 0x0100 पूर्ण,
	अणु 48, 0x0100 पूर्ण,
	अणु 49, 0x0002 पूर्ण,
	अणु 50, 0x0001 पूर्ण,
	अणु 51, 0x0001 पूर्ण,
	अणु 52, 0x0039 पूर्ण,
	अणु 53, 0x0039 पूर्ण,
	अणु 54, 0x0039 पूर्ण,
	अणु 55, 0x0039 पूर्ण,
	अणु 56, 0x0001 पूर्ण,
	अणु 57, 0x0001 पूर्ण,
पूर्ण;

अटल bool wm8978_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == WM8978_RESET;
पूर्ण

/* codec निजी data */
काष्ठा wm8978_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक f_pllout;
	अचिन्हित पूर्णांक f_mclk;
	अचिन्हित पूर्णांक f_256fs;
	अचिन्हित पूर्णांक f_opclk;
	पूर्णांक mclk_idx;
	क्रमागत wm8978_sysclk_src sysclk;
पूर्ण;

अटल स्थिर अक्षर *wm8978_companding[] = अणु"Off", "NC", "u-law", "A-law"पूर्ण;
अटल स्थिर अक्षर *wm8978_eqmode[] = अणु"Capture", "Playback"पूर्ण;
अटल स्थिर अक्षर *wm8978_bw[] = अणु"Narrow", "Wide"पूर्ण;
अटल स्थिर अक्षर *wm8978_eq1[] = अणु"80Hz", "105Hz", "135Hz", "175Hz"पूर्ण;
अटल स्थिर अक्षर *wm8978_eq2[] = अणु"230Hz", "300Hz", "385Hz", "500Hz"पूर्ण;
अटल स्थिर अक्षर *wm8978_eq3[] = अणु"650Hz", "850Hz", "1.1kHz", "1.4kHz"पूर्ण;
अटल स्थिर अक्षर *wm8978_eq4[] = अणु"1.8kHz", "2.4kHz", "3.2kHz", "4.1kHz"पूर्ण;
अटल स्थिर अक्षर *wm8978_eq5[] = अणु"5.3kHz", "6.9kHz", "9kHz", "11.7kHz"पूर्ण;
अटल स्थिर अक्षर *wm8978_alc3[] = अणु"ALC", "Limiter"पूर्ण;
अटल स्थिर अक्षर *wm8978_alc1[] = अणु"Off", "Right", "Left", "Both"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adc_compand, WM8978_COMPANDING_CONTROL, 1,
			    wm8978_companding);
अटल SOC_ENUM_SINGLE_DECL(dac_compand, WM8978_COMPANDING_CONTROL, 3,
			    wm8978_companding);
अटल SOC_ENUM_SINGLE_DECL(eqmode, WM8978_EQ1, 8, wm8978_eqmode);
अटल SOC_ENUM_SINGLE_DECL(eq1, WM8978_EQ1, 5, wm8978_eq1);
अटल SOC_ENUM_SINGLE_DECL(eq2bw, WM8978_EQ2, 8, wm8978_bw);
अटल SOC_ENUM_SINGLE_DECL(eq2, WM8978_EQ2, 5, wm8978_eq2);
अटल SOC_ENUM_SINGLE_DECL(eq3bw, WM8978_EQ3, 8, wm8978_bw);
अटल SOC_ENUM_SINGLE_DECL(eq3, WM8978_EQ3, 5, wm8978_eq3);
अटल SOC_ENUM_SINGLE_DECL(eq4bw, WM8978_EQ4, 8, wm8978_bw);
अटल SOC_ENUM_SINGLE_DECL(eq4, WM8978_EQ4, 5, wm8978_eq4);
अटल SOC_ENUM_SINGLE_DECL(eq5, WM8978_EQ5, 5, wm8978_eq5);
अटल SOC_ENUM_SINGLE_DECL(alc3, WM8978_ALC_CONTROL_3, 8, wm8978_alc3);
अटल SOC_ENUM_SINGLE_DECL(alc1, WM8978_ALC_CONTROL_1, 7, wm8978_alc1);

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_tlv, -1200, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(spk_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(boost_tlv, -1500, 300, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(limiter_tlv, 0, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8978_snd_controls[] = अणु

	SOC_SINGLE("Digital Loopback Switch",
		WM8978_COMPANDING_CONTROL, 0, 1, 0),

	SOC_ENUM("ADC Companding", adc_compand),
	SOC_ENUM("DAC Companding", dac_compand),

	SOC_DOUBLE("DAC Inversion Switch", WM8978_DAC_CONTROL, 0, 1, 1, 0),

	SOC_DOUBLE_R_TLV("PCM Volume",
		WM8978_LEFT_DAC_DIGITAL_VOLUME, WM8978_RIGHT_DAC_DIGITAL_VOLUME,
		0, 255, 0, digital_tlv),

	SOC_SINGLE("High Pass Filter Switch", WM8978_ADC_CONTROL, 8, 1, 0),
	SOC_SINGLE("High Pass Cut Off", WM8978_ADC_CONTROL, 4, 7, 0),
	SOC_DOUBLE("ADC Inversion Switch", WM8978_ADC_CONTROL, 0, 1, 1, 0),

	SOC_DOUBLE_R_TLV("ADC Volume",
		WM8978_LEFT_ADC_DIGITAL_VOLUME, WM8978_RIGHT_ADC_DIGITAL_VOLUME,
		0, 255, 0, digital_tlv),

	SOC_ENUM("Equaliser Function", eqmode),
	SOC_ENUM("EQ1 Cut Off", eq1),
	SOC_SINGLE_TLV("EQ1 Volume", WM8978_EQ1,  0, 24, 1, eq_tlv),

	SOC_ENUM("Equaliser EQ2 Bandwidth", eq2bw),
	SOC_ENUM("EQ2 Cut Off", eq2),
	SOC_SINGLE_TLV("EQ2 Volume", WM8978_EQ2,  0, 24, 1, eq_tlv),

	SOC_ENUM("Equaliser EQ3 Bandwidth", eq3bw),
	SOC_ENUM("EQ3 Cut Off", eq3),
	SOC_SINGLE_TLV("EQ3 Volume", WM8978_EQ3,  0, 24, 1, eq_tlv),

	SOC_ENUM("Equaliser EQ4 Bandwidth", eq4bw),
	SOC_ENUM("EQ4 Cut Off", eq4),
	SOC_SINGLE_TLV("EQ4 Volume", WM8978_EQ4,  0, 24, 1, eq_tlv),

	SOC_ENUM("EQ5 Cut Off", eq5),
	SOC_SINGLE_TLV("EQ5 Volume", WM8978_EQ5, 0, 24, 1, eq_tlv),

	SOC_SINGLE("DAC Playback Limiter Switch",
		WM8978_DAC_LIMITER_1, 8, 1, 0),
	SOC_SINGLE("DAC Playback Limiter Decay",
		WM8978_DAC_LIMITER_1, 4, 15, 0),
	SOC_SINGLE("DAC Playback Limiter Attack",
		WM8978_DAC_LIMITER_1, 0, 15, 0),

	SOC_SINGLE("DAC Playback Limiter Threshold",
		WM8978_DAC_LIMITER_2, 4, 7, 0),
	SOC_SINGLE_TLV("DAC Playback Limiter Volume",
		WM8978_DAC_LIMITER_2, 0, 12, 0, limiter_tlv),

	SOC_ENUM("ALC Enable Switch", alc1),
	SOC_SINGLE("ALC Capture Min Gain", WM8978_ALC_CONTROL_1, 0, 7, 0),
	SOC_SINGLE("ALC Capture Max Gain", WM8978_ALC_CONTROL_1, 3, 7, 0),

	SOC_SINGLE("ALC Capture Hold", WM8978_ALC_CONTROL_2, 4, 10, 0),
	SOC_SINGLE("ALC Capture Target", WM8978_ALC_CONTROL_2, 0, 15, 0),

	SOC_ENUM("ALC Capture Mode", alc3),
	SOC_SINGLE("ALC Capture Decay", WM8978_ALC_CONTROL_3, 4, 10, 0),
	SOC_SINGLE("ALC Capture Attack", WM8978_ALC_CONTROL_3, 0, 10, 0),

	SOC_SINGLE("ALC Capture Noise Gate Switch", WM8978_NOISE_GATE, 3, 1, 0),
	SOC_SINGLE("ALC Capture Noise Gate Threshold",
		WM8978_NOISE_GATE, 0, 7, 0),

	SOC_DOUBLE_R("Capture PGA ZC Switch",
		WM8978_LEFT_INP_PGA_CONTROL, WM8978_RIGHT_INP_PGA_CONTROL,
		7, 1, 0),

	/* OUT1 - Headphones */
	SOC_DOUBLE_R("Headphone Playback ZC Switch",
		WM8978_LOUT1_HP_CONTROL, WM8978_ROUT1_HP_CONTROL, 7, 1, 0),

	SOC_DOUBLE_R_TLV("Headphone Playback Volume",
		WM8978_LOUT1_HP_CONTROL, WM8978_ROUT1_HP_CONTROL,
		0, 63, 0, spk_tlv),

	/* OUT2 - Speakers */
	SOC_DOUBLE_R("Speaker Playback ZC Switch",
		WM8978_LOUT2_SPK_CONTROL, WM8978_ROUT2_SPK_CONTROL, 7, 1, 0),

	SOC_DOUBLE_R_TLV("Speaker Playback Volume",
		WM8978_LOUT2_SPK_CONTROL, WM8978_ROUT2_SPK_CONTROL,
		0, 63, 0, spk_tlv),

	/* OUT3/4 - Line Output */
	SOC_DOUBLE_R("Line Playback Switch",
		WM8978_OUT3_MIXER_CONTROL, WM8978_OUT4_MIXER_CONTROL, 6, 1, 1),

	/* Mixer #3: Boost (Input) mixer */
	SOC_DOUBLE_R("PGA Boost (+20dB)",
		WM8978_LEFT_ADC_BOOST_CONTROL, WM8978_RIGHT_ADC_BOOST_CONTROL,
		8, 1, 0),
	SOC_DOUBLE_R_TLV("L2/R2 Boost Volume",
		WM8978_LEFT_ADC_BOOST_CONTROL, WM8978_RIGHT_ADC_BOOST_CONTROL,
		4, 7, 0, boost_tlv),
	SOC_DOUBLE_R_TLV("Aux Boost Volume",
		WM8978_LEFT_ADC_BOOST_CONTROL, WM8978_RIGHT_ADC_BOOST_CONTROL,
		0, 7, 0, boost_tlv),

	/* Input PGA volume */
	SOC_DOUBLE_R_TLV("Input PGA Volume",
		WM8978_LEFT_INP_PGA_CONTROL, WM8978_RIGHT_INP_PGA_CONTROL,
		0, 63, 0, inpga_tlv),

	/* Headphone */
	SOC_DOUBLE_R("Headphone Switch",
		WM8978_LOUT1_HP_CONTROL, WM8978_ROUT1_HP_CONTROL, 6, 1, 1),

	/* Speaker */
	SOC_DOUBLE_R("Speaker Switch",
		WM8978_LOUT2_SPK_CONTROL, WM8978_ROUT2_SPK_CONTROL, 6, 1, 1),

	/* DAC / ADC oversampling */
	SOC_SINGLE("DAC 128x Oversampling Switch", WM8978_DAC_CONTROL,
		   5, 1, 0),
	SOC_SINGLE("ADC 128x Oversampling Switch", WM8978_ADC_CONTROL,
		   5, 1, 0),
पूर्ण;

/* Mixer #1: Output (OUT1, OUT2) Mixer: mix AUX, Input mixer output and DAC */
अटल स्थिर काष्ठा snd_kcontrol_new wm8978_left_out_mixer[] = अणु
	SOC_DAPM_SINGLE("Line Bypass Switch", WM8978_LEFT_MIXER_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux Playback Switch", WM8978_LEFT_MIXER_CONTROL, 5, 1, 0),
	SOC_DAPM_SINGLE("PCM Playback Switch", WM8978_LEFT_MIXER_CONTROL, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8978_right_out_mixer[] = अणु
	SOC_DAPM_SINGLE("Line Bypass Switch", WM8978_RIGHT_MIXER_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux Playback Switch", WM8978_RIGHT_MIXER_CONTROL, 5, 1, 0),
	SOC_DAPM_SINGLE("PCM Playback Switch", WM8978_RIGHT_MIXER_CONTROL, 0, 1, 0),
पूर्ण;

/* OUT3/OUT4 Mixer not implemented */

/* Mixer #2: Input PGA Mute */
अटल स्थिर काष्ठा snd_kcontrol_new wm8978_left_input_mixer[] = अणु
	SOC_DAPM_SINGLE("L2 Switch", WM8978_INPUT_CONTROL, 2, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", WM8978_INPUT_CONTROL, 1, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", WM8978_INPUT_CONTROL, 0, 1, 0),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new wm8978_right_input_mixer[] = अणु
	SOC_DAPM_SINGLE("R2 Switch", WM8978_INPUT_CONTROL, 6, 1, 0),
	SOC_DAPM_SINGLE("MicN Switch", WM8978_INPUT_CONTROL, 5, 1, 0),
	SOC_DAPM_SINGLE("MicP Switch", WM8978_INPUT_CONTROL, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8978_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("Left DAC", "Left HiFi Playback",
			 WM8978_POWER_MANAGEMENT_3, 0, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Right HiFi Playback",
			 WM8978_POWER_MANAGEMENT_3, 1, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left HiFi Capture",
			 WM8978_POWER_MANAGEMENT_2, 0, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right HiFi Capture",
			 WM8978_POWER_MANAGEMENT_2, 1, 0),

	/* Mixer #1: OUT1,2 */
	SOC_MIXER_ARRAY("Left Output Mixer", WM8978_POWER_MANAGEMENT_3,
			2, 0, wm8978_left_out_mixer),
	SOC_MIXER_ARRAY("Right Output Mixer", WM8978_POWER_MANAGEMENT_3,
			3, 0, wm8978_right_out_mixer),

	SOC_MIXER_ARRAY("Left Input Mixer", WM8978_POWER_MANAGEMENT_2,
			2, 0, wm8978_left_input_mixer),
	SOC_MIXER_ARRAY("Right Input Mixer", WM8978_POWER_MANAGEMENT_2,
			3, 0, wm8978_right_input_mixer),

	SND_SOC_DAPM_PGA("Left Boost Mixer", WM8978_POWER_MANAGEMENT_2,
			 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Boost Mixer", WM8978_POWER_MANAGEMENT_2,
			 5, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Capture PGA", WM8978_LEFT_INP_PGA_CONTROL,
			 6, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Capture PGA", WM8978_RIGHT_INP_PGA_CONTROL,
			 6, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Headphone Out", WM8978_POWER_MANAGEMENT_2,
			 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Headphone Out", WM8978_POWER_MANAGEMENT_2,
			 8, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Left Speaker Out", WM8978_POWER_MANAGEMENT_3,
			 6, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Speaker Out", WM8978_POWER_MANAGEMENT_3,
			 5, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("OUT4 VMID", WM8978_POWER_MANAGEMENT_3,
			   8, 0, शून्य, 0),

	SND_SOC_DAPM_MICBIAS("Mic Bias", WM8978_POWER_MANAGEMENT_1, 4, 0),

	SND_SOC_DAPM_INPUT("LMICN"),
	SND_SOC_DAPM_INPUT("LMICP"),
	SND_SOC_DAPM_INPUT("RMICN"),
	SND_SOC_DAPM_INPUT("RMICP"),
	SND_SOC_DAPM_INPUT("LAUX"),
	SND_SOC_DAPM_INPUT("RAUX"),
	SND_SOC_DAPM_INPUT("L2"),
	SND_SOC_DAPM_INPUT("R2"),
	SND_SOC_DAPM_OUTPUT("LHP"),
	SND_SOC_DAPM_OUTPUT("RHP"),
	SND_SOC_DAPM_OUTPUT("LSPK"),
	SND_SOC_DAPM_OUTPUT("RSPK"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8978_dapm_routes[] = अणु
	/* Output mixer */
	अणु"Right Output Mixer", "PCM Playback Switch", "Right DAC"पूर्ण,
	अणु"Right Output Mixer", "Aux Playback Switch", "RAUX"पूर्ण,
	अणु"Right Output Mixer", "Line Bypass Switch", "Right Boost Mixer"पूर्ण,

	अणु"Left Output Mixer", "PCM Playback Switch", "Left DAC"पूर्ण,
	अणु"Left Output Mixer", "Aux Playback Switch", "LAUX"पूर्ण,
	अणु"Left Output Mixer", "Line Bypass Switch", "Left Boost Mixer"पूर्ण,

	/* Outमाला_दो */
	अणु"Right Headphone Out", शून्य, "Right Output Mixer"पूर्ण,
	अणु"RHP", शून्य, "Right Headphone Out"पूर्ण,

	अणु"Left Headphone Out", शून्य, "Left Output Mixer"पूर्ण,
	अणु"LHP", शून्य, "Left Headphone Out"पूर्ण,

	अणु"Right Speaker Out", शून्य, "Right Output Mixer"पूर्ण,
	अणु"RSPK", शून्य, "Right Speaker Out"पूर्ण,

	अणु"Left Speaker Out", शून्य, "Left Output Mixer"पूर्ण,
	अणु"LSPK", शून्य, "Left Speaker Out"पूर्ण,

	/* Boost Mixer */
	अणु"Right ADC", शून्य, "Right Boost Mixer"पूर्ण,

	अणु"Right Boost Mixer", शून्य, "RAUX"पूर्ण,
	अणु"Right Boost Mixer", शून्य, "Right Capture PGA"पूर्ण,
	अणु"Right Boost Mixer", शून्य, "R2"पूर्ण,

	अणु"Left ADC", शून्य, "Left Boost Mixer"पूर्ण,

	अणु"Left Boost Mixer", शून्य, "LAUX"पूर्ण,
	अणु"Left Boost Mixer", शून्य, "Left Capture PGA"पूर्ण,
	अणु"Left Boost Mixer", शून्य, "L2"पूर्ण,

	/* Input PGA */
	अणु"Right Capture PGA", शून्य, "Right Input Mixer"पूर्ण,
	अणु"Left Capture PGA", शून्य, "Left Input Mixer"पूर्ण,

	अणु"Right Input Mixer", "R2 Switch", "R2"पूर्ण,
	अणु"Right Input Mixer", "MicN Switch", "RMICN"पूर्ण,
	अणु"Right Input Mixer", "MicP Switch", "RMICP"पूर्ण,

	अणु"Left Input Mixer", "L2 Switch", "L2"पूर्ण,
	अणु"Left Input Mixer", "MicN Switch", "LMICN"पूर्ण,
	अणु"Left Input Mixer", "MicP Switch", "LMICP"पूर्ण,
पूर्ण;

/* PLL भागisors */
काष्ठा wm8978_pll_भाग अणु
	u32 k;
	u8 n;
	u8 भाग2;
पूर्ण;

#घोषणा FIXED_PLL_SIZE (1 << 24)

अटल व्योम pll_factors(काष्ठा snd_soc_component *component,
		काष्ठा wm8978_pll_भाग *pll_भाग, अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक source)
अणु
	u64 k_part;
	अचिन्हित पूर्णांक k, n_भाग, n_mod;

	n_भाग = target / source;
	अगर (n_भाग < 6) अणु
		source >>= 1;
		pll_भाग->भाग2 = 1;
		n_भाग = target / source;
	पूर्ण अन्यथा अणु
		pll_भाग->भाग2 = 0;
	पूर्ण

	अगर (n_भाग < 6 || n_भाग > 12)
		dev_warn(component->dev,
			 "WM8978 N value exceeds recommended range! N = %u\n",
			 n_भाग);

	pll_भाग->n = n_भाग;
	n_mod = target - source * n_भाग;
	k_part = FIXED_PLL_SIZE * (दीर्घ दीर्घ)n_mod + source / 2;

	करो_भाग(k_part, source);

	k = k_part & 0xFFFFFFFF;

	pll_भाग->k = k;
पूर्ण

/* MCLK भागiders */
अटल स्थिर पूर्णांक mclk_numerator[]	= अणु1, 3, 2, 3, 4, 6, 8, 12पूर्ण;
अटल स्थिर पूर्णांक mclk_denominator[]	= अणु1, 2, 1, 1, 1, 1, 1, 1पूर्ण;

/*
 * find index >= idx, such that, क्रम a given f_out,
 * 3 * f_mclk / 4 <= f_PLLOUT < 13 * f_mclk / 4
 * f_out can be f_256fs or f_opclk, currently only used क्रम f_256fs. Can be
 * generalised क्रम f_opclk with suitable coefficient arrays, but currently
 * the OPCLK भागisor is calculated directly, not iteratively.
 */
अटल पूर्णांक wm8978_क्रमागत_mclk(अचिन्हित पूर्णांक f_out, अचिन्हित पूर्णांक f_mclk,
			    अचिन्हित पूर्णांक *f_pllout)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mclk_numerator); i++) अणु
		अचिन्हित पूर्णांक f_pllout_x4 = 4 * f_out * mclk_numerator[i] /
			mclk_denominator[i];
		अगर (3 * f_mclk <= f_pllout_x4 && f_pllout_x4 < 13 * f_mclk) अणु
			*f_pllout = f_pllout_x4 / 4;
			वापस i;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Calculate पूर्णांकernal frequencies and भागiders, according to Figure 40
 * "PLL and Clock Select Circuit" in WM8978 datasheet Rev. 2.6
 */
अटल पूर्णांक wm8978_configure_pll(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8978_pll_भाग pll_भाग;
	अचिन्हित पूर्णांक f_opclk = wm8978->f_opclk, f_mclk = wm8978->f_mclk,
		f_256fs = wm8978->f_256fs;
	अचिन्हित पूर्णांक f2;

	अगर (!f_mclk)
		वापस -EINVAL;

	अगर (f_opclk) अणु
		अचिन्हित पूर्णांक opclk_भाग;
		/* Cannot set up MCLK भागider now, करो later */
		wm8978->mclk_idx = -1;

		/*
		 * The user needs OPCLK. Choose OPCLKDIV to put
		 * 6 <= R = f2 / f1 < 13, 1 <= OPCLKDIV <= 4.
		 * f_opclk = f_mclk * prescale * R / 4 / OPCLKDIV, where
		 * prescale = 1, or prescale = 2. Prescale is calculated inside
		 * pll_factors(). We have to select f_PLLOUT, such that
		 * f_mclk * 3 / 4 <= f_PLLOUT < f_mclk * 13 / 4. Must be
		 * f_mclk * 3 / 16 <= f_opclk < f_mclk * 13 / 4.
		 */
		अगर (16 * f_opclk < 3 * f_mclk || 4 * f_opclk >= 13 * f_mclk)
			वापस -EINVAL;

		अगर (4 * f_opclk < 3 * f_mclk)
			/* Have to use OPCLKDIV */
			opclk_भाग = (3 * f_mclk / 4 + f_opclk - 1) / f_opclk;
		अन्यथा
			opclk_भाग = 1;

		dev_dbg(component->dev, "%s: OPCLKDIV=%d\n", __func__, opclk_भाग);

		snd_soc_component_update_bits(component, WM8978_GPIO_CONTROL, 0x30,
				    (opclk_भाग - 1) << 4);

		wm8978->f_pllout = f_opclk * opclk_भाग;
	पूर्ण अन्यथा अगर (f_256fs) अणु
		/*
		 * Not using OPCLK, but PLL is used क्रम the codec, choose R:
		 * 6 <= R = f2 / f1 < 13, to put 1 <= MCLKDIV <= 12.
		 * f_256fs = f_mclk * prescale * R / 4 / MCLKDIV, where
		 * prescale = 1, or prescale = 2. Prescale is calculated inside
		 * pll_factors(). We have to select f_PLLOUT, such that
		 * f_mclk * 3 / 4 <= f_PLLOUT < f_mclk * 13 / 4. Must be
		 * f_mclk * 3 / 48 <= f_256fs < f_mclk * 13 / 4. This means MCLK
		 * must be 3.781MHz <= f_MCLK <= 32.768MHz
		 */
		पूर्णांक idx = wm8978_क्रमागत_mclk(f_256fs, f_mclk, &wm8978->f_pllout);
		अगर (idx < 0)
			वापस idx;

		wm8978->mclk_idx = idx;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	f2 = wm8978->f_pllout * 4;

	dev_dbg(component->dev, "%s: f_MCLK=%uHz, f_PLLOUT=%uHz\n", __func__,
		wm8978->f_mclk, wm8978->f_pllout);

	pll_factors(component, &pll_भाग, f2, wm8978->f_mclk);

	dev_dbg(component->dev, "%s: calculated PLL N=0x%x, K=0x%x, div2=%d\n",
		__func__, pll_भाग.n, pll_भाग.k, pll_भाग.भाग2);

	/* Turn PLL off क्रम configuration... */
	snd_soc_component_update_bits(component, WM8978_POWER_MANAGEMENT_1, 0x20, 0);

	snd_soc_component_ग_लिखो(component, WM8978_PLL_N, (pll_भाग.भाग2 << 4) | pll_भाग.n);
	snd_soc_component_ग_लिखो(component, WM8978_PLL_K1, pll_भाग.k >> 18);
	snd_soc_component_ग_लिखो(component, WM8978_PLL_K2, (pll_भाग.k >> 9) & 0x1ff);
	snd_soc_component_ग_लिखो(component, WM8978_PLL_K3, pll_भाग.k & 0x1ff);

	/* ...and on again */
	snd_soc_component_update_bits(component, WM8978_POWER_MANAGEMENT_1, 0x20, 0x20);

	अगर (f_opclk)
		/* Output PLL (OPCLK) to GPIO1 */
		snd_soc_component_update_bits(component, WM8978_GPIO_CONTROL, 7, 4);

	वापस 0;
पूर्ण

/*
 * Configure WM8978 घड़ी भागiders.
 */
अटल पूर्णांक wm8978_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (भाग_id) अणु
	हाल WM8978_OPCLKRATE:
		wm8978->f_opclk = भाग;

		अगर (wm8978->f_mclk)
			/*
			 * We know the MCLK frequency, the user has requested
			 * OPCLK, configure the PLL based on that and start it
			 * and OPCLK immediately. We will configure PLL to match
			 * user-requested OPCLK frquency as good as possible.
			 * In fact, it is likely, that matching the sampling
			 * rate, when it becomes known, is more important, and
			 * we will not be reconfiguring PLL then, because we
			 * must not पूर्णांकerrupt OPCLK. But it should be fine,
			 * because typically the user will request OPCLK to run
			 * at 256fs or 512fs, and क्रम these हालs we will also
			 * find an exact MCLK भागider configuration - it will
			 * be equal to or द्विगुन the OPCLK भागisor.
			 */
			ret = wm8978_configure_pll(component);
		अवरोध;
	हाल WM8978_BCLKDIV:
		अगर (भाग & ~0x1c)
			वापस -EINVAL;
		snd_soc_component_update_bits(component, WM8978_CLOCKING, 0x1c, भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "%s: ID %d, value %u\n", __func__, भाग_id, भाग);

	वापस ret;
पूर्ण

/*
 * @freq:	when .set_pll() us not used, freq is codec MCLK input frequency
 */
अटल पूर्णांक wm8978_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai, पूर्णांक clk_id,
				 अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	dev_dbg(component->dev, "%s: ID %d, freq %u\n", __func__, clk_id, freq);

	अगर (freq) अणु
		wm8978->f_mclk = freq;

		/* Even अगर MCLK is used क्रम प्रणाली घड़ी, might have to drive OPCLK */
		अगर (wm8978->f_opclk)
			ret = wm8978_configure_pll(component);

		/* Our sysclk is fixed to 256 * fs, will configure in .hw_params()  */

		अगर (!ret)
			wm8978->sysclk = clk_id;
	पूर्ण

	अगर (wm8978->sysclk == WM8978_PLL && (!freq || clk_id == WM8978_MCLK)) अणु
		/* Clock CODEC directly from MCLK */
		snd_soc_component_update_bits(component, WM8978_CLOCKING, 0x100, 0);

		/* GPIO1 पूर्णांकo शेष mode as input - beक्रमe configuring PLL */
		snd_soc_component_update_bits(component, WM8978_GPIO_CONTROL, 7, 0);

		/* Turn off PLL */
		snd_soc_component_update_bits(component, WM8978_POWER_MANAGEMENT_1, 0x20, 0);
		wm8978->sysclk = WM8978_MCLK;
		wm8978->f_pllout = 0;
		wm8978->f_opclk = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Set ADC and Voice DAC क्रमmat.
 */
अटल पूर्णांक wm8978_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	/*
	 * BCLK polarity mask = 0x100, LRC घड़ी polarity mask = 0x80,
	 * Data Format mask = 0x18: all will be calculated anew
	 */
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8978_AUDIO_INTERFACE) & ~0x198;
	u16 clk = snd_soc_component_पढ़ो(component, WM8978_CLOCKING);

	dev_dbg(component->dev, "%s\n", __func__);

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		clk |= 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		clk &= ~1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x10;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x8;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= 0x18;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x180;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x100;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x80;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8978_AUDIO_INTERFACE, अगरace);
	snd_soc_component_ग_लिखो(component, WM8978_CLOCKING, clk);

	वापस 0;
पूर्ण

/*
 * Set PCM DAI bit size and sample rate.
 */
अटल पूर्णांक wm8978_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);
	/* Word length mask = 0x60 */
	u16 अगरace_ctl = snd_soc_component_पढ़ो(component, WM8978_AUDIO_INTERFACE) & ~0x60;
	/* Sampling rate mask = 0xe (क्रम filters) */
	u16 add_ctl = snd_soc_component_पढ़ो(component, WM8978_ADDITIONAL_CONTROL) & ~0xe;
	u16 clking = snd_soc_component_पढ़ो(component, WM8978_CLOCKING);
	क्रमागत wm8978_sysclk_src current_clk_id = (clking & 0x100) ?
		WM8978_PLL : WM8978_MCLK;
	अचिन्हित पूर्णांक f_sel, dअगरf, dअगरf_best = पूर्णांक_उच्च;
	पूर्णांक i, best = 0;

	अगर (!wm8978->f_mclk)
		वापस -EINVAL;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace_ctl |= 0x20;
		अवरोध;
	हाल 24:
		अगरace_ctl |= 0x40;
		अवरोध;
	हाल 32:
		अगरace_ctl |= 0x60;
		अवरोध;
	पूर्ण

	/* filter coefficient */
	चयन (params_rate(params)) अणु
	हाल 8000:
		add_ctl |= 0x5 << 1;
		अवरोध;
	हाल 11025:
		add_ctl |= 0x4 << 1;
		अवरोध;
	हाल 16000:
		add_ctl |= 0x3 << 1;
		अवरोध;
	हाल 22050:
		add_ctl |= 0x2 << 1;
		अवरोध;
	हाल 32000:
		add_ctl |= 0x1 << 1;
		अवरोध;
	हाल 44100:
	हाल 48000:
		अवरोध;
	पूर्ण

	/* Sampling rate is known now, can configure the MCLK भागider */
	wm8978->f_256fs = params_rate(params) * 256;

	अगर (wm8978->sysclk == WM8978_MCLK) अणु
		wm8978->mclk_idx = -1;
		f_sel = wm8978->f_mclk;
	पूर्ण अन्यथा अणु
		अगर (!wm8978->f_opclk) अणु
			/* We only enter here, अगर OPCLK is not used */
			पूर्णांक ret = wm8978_configure_pll(component);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		f_sel = wm8978->f_pllout;
	पूर्ण

	अगर (wm8978->mclk_idx < 0) अणु
		/* Either MCLK is used directly, or OPCLK is used */
		अगर (f_sel < wm8978->f_256fs || f_sel > 12 * wm8978->f_256fs)
			वापस -EINVAL;

		क्रम (i = 0; i < ARRAY_SIZE(mclk_numerator); i++) अणु
			dअगरf = असल(wm8978->f_256fs * 3 -
				   f_sel * 3 * mclk_denominator[i] / mclk_numerator[i]);

			अगर (dअगरf < dअगरf_best) अणु
				dअगरf_best = dअगरf;
				best = i;
			पूर्ण

			अगर (!dअगरf)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* OPCLK not used, codec driven by PLL */
		best = wm8978->mclk_idx;
		dअगरf = 0;
	पूर्ण

	अगर (dअगरf)
		dev_warn(component->dev, "Imprecise sampling rate: %uHz%s\n",
			f_sel * mclk_denominator[best] / mclk_numerator[best] / 256,
			wm8978->sysclk == WM8978_MCLK ?
			", consider using PLL" : "");

	dev_dbg(component->dev, "%s: width %d, rate %u, MCLK divisor #%d\n", __func__,
		params_width(params), params_rate(params), best);

	/* MCLK भागisor mask = 0xe0 */
	snd_soc_component_update_bits(component, WM8978_CLOCKING, 0xe0, best << 5);

	snd_soc_component_ग_लिखो(component, WM8978_AUDIO_INTERFACE, अगरace_ctl);
	snd_soc_component_ग_लिखो(component, WM8978_ADDITIONAL_CONTROL, add_ctl);

	अगर (wm8978->sysclk != current_clk_id) अणु
		अगर (wm8978->sysclk == WM8978_PLL)
			/* Run CODEC from PLL instead of MCLK */
			snd_soc_component_update_bits(component, WM8978_CLOCKING,
					    0x100, 0x100);
		अन्यथा
			/* Clock CODEC directly from MCLK */
			snd_soc_component_update_bits(component, WM8978_CLOCKING, 0x100, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8978_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	dev_dbg(component->dev, "%s: %d\n", __func__, mute);

	अगर (mute)
		snd_soc_component_update_bits(component, WM8978_DAC_CONTROL, 0x40, 0x40);
	अन्यथा
		snd_soc_component_update_bits(component, WM8978_DAC_CONTROL, 0x40, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8978_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	u16 घातer1 = snd_soc_component_पढ़ो(component, WM8978_POWER_MANAGEMENT_1) & ~3;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		घातer1 |= 1;  /* VMID 75k */
		snd_soc_component_ग_लिखो(component, WM8978_POWER_MANAGEMENT_1, घातer1);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* bit 3: enable bias, bit 2: enable I/O tie off buffer */
		घातer1 |= 0xc;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Initial cap अक्षरge at VMID 5k */
			snd_soc_component_ग_लिखो(component, WM8978_POWER_MANAGEMENT_1,
				      घातer1 | 0x3);
			mdelay(100);
		पूर्ण

		घातer1 |= 0x2;  /* VMID 500k */
		snd_soc_component_ग_लिखो(component, WM8978_POWER_MANAGEMENT_1, घातer1);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* Preserve PLL - OPCLK may be used by someone */
		snd_soc_component_update_bits(component, WM8978_POWER_MANAGEMENT_1, ~0x20, 0);
		snd_soc_component_ग_लिखो(component, WM8978_POWER_MANAGEMENT_2, 0);
		snd_soc_component_ग_लिखो(component, WM8978_POWER_MANAGEMENT_3, 0);
		अवरोध;
	पूर्ण

	dev_dbg(component->dev, "%s: %d, %x\n", __func__, level, घातer1);

	वापस 0;
पूर्ण

#घोषणा WM8978_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8978_dai_ops = अणु
	.hw_params	= wm8978_hw_params,
	.mute_stream	= wm8978_mute,
	.set_fmt	= wm8978_set_dai_fmt,
	.set_clkभाग	= wm8978_set_dai_clkभाग,
	.set_sysclk	= wm8978_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

/* Also supports 12kHz */
अटल काष्ठा snd_soc_dai_driver wm8978_dai = अणु
	.name = "wm8978-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = WM8978_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = WM8978_FORMATS,
	पूर्ण,
	.ops = &wm8978_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8978_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);
	/* Also चयन PLL off */
	snd_soc_component_ग_लिखो(component, WM8978_POWER_MANAGEMENT_1, 0);

	regcache_mark_dirty(wm8978->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8978_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);

	/* Sync reg_cache with the hardware */
	regcache_sync(wm8978->regmap);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	अगर (wm8978->f_pllout)
		/* Switch PLL on */
		snd_soc_component_update_bits(component, WM8978_POWER_MANAGEMENT_1, 0x20, 0x20);

	वापस 0;
पूर्ण

/*
 * These रेजिस्टरs contain an "update" bit - bit 8. This means, क्रम example,
 * that one can ग_लिखो new DAC digital volume क्रम both channels, but only when
 * the update bit is set, will also the volume be updated - simultaneously क्रम
 * both channels.
 */
अटल स्थिर पूर्णांक update_reg[] = अणु
	WM8978_LEFT_DAC_DIGITAL_VOLUME,
	WM8978_RIGHT_DAC_DIGITAL_VOLUME,
	WM8978_LEFT_ADC_DIGITAL_VOLUME,
	WM8978_RIGHT_ADC_DIGITAL_VOLUME,
	WM8978_LEFT_INP_PGA_CONTROL,
	WM8978_RIGHT_INP_PGA_CONTROL,
	WM8978_LOUT1_HP_CONTROL,
	WM8978_ROUT1_HP_CONTROL,
	WM8978_LOUT2_SPK_CONTROL,
	WM8978_ROUT2_SPK_CONTROL,
पूर्ण;

अटल पूर्णांक wm8978_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8978_priv *wm8978 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	/*
	 * Set शेष प्रणाली घड़ी to PLL, it is more precise, this is also the
	 * शेष hardware setting
	 */
	wm8978->sysclk = WM8978_PLL;

	/*
	 * Set the update bit in all रेजिस्टरs, that have one. This way all
	 * ग_लिखोs to those रेजिस्टरs will also cause the update bit to be
	 * written.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(update_reg); i++)
		snd_soc_component_update_bits(component, update_reg[i], 0x100, 0x100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8978 = अणु
	.probe			= wm8978_probe,
	.suspend		= wm8978_suspend,
	.resume			= wm8978_resume,
	.set_bias_level		= wm8978_set_bias_level,
	.controls		= wm8978_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8978_snd_controls),
	.dapm_widमाला_लो		= wm8978_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8978_dapm_widमाला_लो),
	.dapm_routes		= wm8978_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8978_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8978_regmap_config = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = WM8978_MAX_REGISTER,
	.अस्थिर_reg = wm8978_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = wm8978_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8978_reg_शेषs),
पूर्ण;

अटल पूर्णांक wm8978_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8978_priv *wm8978;
	पूर्णांक ret;

	wm8978 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8978_priv),
			      GFP_KERNEL);
	अगर (wm8978 == शून्य)
		वापस -ENOMEM;

	wm8978->regmap = devm_regmap_init_i2c(i2c, &wm8978_regmap_config);
	अगर (IS_ERR(wm8978->regmap)) अणु
		ret = PTR_ERR(wm8978->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8978);

	/* Reset the codec */
	ret = regmap_ग_लिखो(wm8978->regmap, WM8978_RESET, 0);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to issue reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8978, &wm8978_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8978_i2c_id[] = अणु
	अणु "wm8978", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8978_i2c_id);

अटल स्थिर काष्ठा of_device_id wm8978_of_match[] = अणु
	अणु .compatible = "wlf,wm8978", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8978_of_match);

अटल काष्ठा i2c_driver wm8978_i2c_driver = अणु
	.driver = अणु
		.name = "wm8978",
		.of_match_table = wm8978_of_match,
	पूर्ण,
	.probe =    wm8978_i2c_probe,
	.id_table = wm8978_i2c_id,
पूर्ण;

module_i2c_driver(wm8978_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8978 codec driver");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_LICENSE("GPL");
