<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8971.c  --  WM8971 ALSA SoC Audio driver
 *
 * Copyright 2005 Lab126, Inc.
 *
 * Author: Kenneth Kiraly <kiraly@lab126.com>
 *
 * Based on wm8753.c by Liam Girdwood
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
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

#समावेश "wm8971.h"

#घोषणा	WM8971_REG_COUNT		43

/* codec निजी data */
काष्ठा wm8971_priv अणु
	अचिन्हित पूर्णांक sysclk;
	काष्ठा delayed_work अक्षरge_work;
	काष्ठा regmap *regmap;
पूर्ण;

/*
 * wm8971 रेजिस्टर cache
 * We can't पढ़ो the WM8971 रेजिस्टर space when we
 * are using 2 wire क्रम device control, so we cache them instead.
 */
अटल स्थिर काष्ठा reg_शेष wm8971_reg_शेषs[] = अणु
	अणु  0, 0x0097 पूर्ण,
	अणु  1, 0x0097 पूर्ण,
	अणु  2, 0x0079 पूर्ण,
	अणु  3, 0x0079 पूर्ण,
	अणु  4, 0x0000 पूर्ण,
	अणु  5, 0x0008 पूर्ण,
	अणु  6, 0x0000 पूर्ण,
	अणु  7, 0x000a पूर्ण,
	अणु  8, 0x0000 पूर्ण,
	अणु  9, 0x0000 पूर्ण,
	अणु 10, 0x00ff पूर्ण,
	अणु 11, 0x00ff पूर्ण,
	अणु 12, 0x000f पूर्ण,
	अणु 13, 0x000f पूर्ण,
	अणु 14, 0x0000 पूर्ण,
	अणु 15, 0x0000 पूर्ण,
	अणु 16, 0x0000 पूर्ण,
	अणु 17, 0x007b पूर्ण,
	अणु 18, 0x0000 पूर्ण,
	अणु 19, 0x0032 पूर्ण,
	अणु 20, 0x0000 पूर्ण,
	अणु 21, 0x00c3 पूर्ण,
	अणु 22, 0x00c3 पूर्ण,
	अणु 23, 0x00c0 पूर्ण,
	अणु 24, 0x0000 पूर्ण,
	अणु 25, 0x0000 पूर्ण,
	अणु 26, 0x0000 पूर्ण,
	अणु 27, 0x0000 पूर्ण,
	अणु 28, 0x0000 पूर्ण,
	अणु 29, 0x0000 पूर्ण,
	अणु 30, 0x0000 पूर्ण,
	अणु 31, 0x0000 पूर्ण,
	अणु 32, 0x0000 पूर्ण,
	अणु 33, 0x0000 पूर्ण,
	अणु 34, 0x0050 पूर्ण,
	अणु 35, 0x0050 पूर्ण,
	अणु 36, 0x0050 पूर्ण,
	अणु 37, 0x0050 पूर्ण,
	अणु 38, 0x0050 पूर्ण,
	अणु 39, 0x0050 पूर्ण,
	अणु 40, 0x0079 पूर्ण,
	अणु 41, 0x0079 पूर्ण,
	अणु 42, 0x0079 पूर्ण,
पूर्ण;

#घोषणा wm8971_reset(c)	snd_soc_component_ग_लिखो(c, WM8971_RESET, 0)

/* WM8971 Controls */
अटल स्थिर अक्षर *wm8971_bass[] = अणु "Linear Control", "Adaptive Boost" पूर्ण;
अटल स्थिर अक्षर *wm8971_bass_filter[] = अणु "130Hz @ 48kHz",
	"200Hz @ 48kHz" पूर्ण;
अटल स्थिर अक्षर *wm8971_treble[] = अणु "8kHz", "4kHz" पूर्ण;
अटल स्थिर अक्षर *wm8971_alc_func[] = अणु "Off", "Right", "Left", "Stereo" पूर्ण;
अटल स्थिर अक्षर *wm8971_ng_type[] = अणु "Constant PGA Gain",
	"Mute ADC Output" पूर्ण;
अटल स्थिर अक्षर *wm8971_deemp[] = अणु "None", "32kHz", "44.1kHz", "48kHz" पूर्ण;
अटल स्थिर अक्षर *wm8971_mono_mux[] = अणु"Stereo", "Mono (Left)",
	"Mono (Right)", "Digital Mono"पूर्ण;
अटल स्थिर अक्षर *wm8971_dac_phase[] = अणु "Non Inverted", "Inverted" पूर्ण;
अटल स्थिर अक्षर *wm8971_lline_mux[] = अणु"Line", "NC", "NC", "PGA",
	"Differential"पूर्ण;
अटल स्थिर अक्षर *wm8971_rline_mux[] = अणु"Line", "Mic", "NC", "PGA",
	"Differential"पूर्ण;
अटल स्थिर अक्षर *wm8971_lpga_sel[] = अणु"Line", "NC", "NC", "Differential"पूर्ण;
अटल स्थिर अक्षर *wm8971_rpga_sel[] = अणु"Line", "Mic", "NC", "Differential"पूर्ण;
अटल स्थिर अक्षर *wm8971_adcpol[] = अणु"Normal", "L Invert", "R Invert",
	"L + R Invert"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8971_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(WM8971_BASS, 7, 2, wm8971_bass),	/* 0 */
	SOC_ENUM_SINGLE(WM8971_BASS, 6, 2, wm8971_bass_filter),
	SOC_ENUM_SINGLE(WM8971_TREBLE, 6, 2, wm8971_treble),
	SOC_ENUM_SINGLE(WM8971_ALC1, 7, 4, wm8971_alc_func),
	SOC_ENUM_SINGLE(WM8971_NGATE, 1, 2, wm8971_ng_type),    /* 4 */
	SOC_ENUM_SINGLE(WM8971_ADCDAC, 1, 4, wm8971_deemp),
	SOC_ENUM_SINGLE(WM8971_ADCTL1, 4, 4, wm8971_mono_mux),
	SOC_ENUM_SINGLE(WM8971_ADCTL1, 1, 2, wm8971_dac_phase),
	SOC_ENUM_SINGLE(WM8971_LOUTM1, 0, 5, wm8971_lline_mux), /* 8 */
	SOC_ENUM_SINGLE(WM8971_ROUTM1, 0, 5, wm8971_rline_mux),
	SOC_ENUM_SINGLE(WM8971_LADCIN, 6, 4, wm8971_lpga_sel),
	SOC_ENUM_SINGLE(WM8971_RADCIN, 6, 4, wm8971_rpga_sel),
	SOC_ENUM_SINGLE(WM8971_ADCDAC, 5, 4, wm8971_adcpol),    /* 12 */
	SOC_ENUM_SINGLE(WM8971_ADCIN, 6, 4, wm8971_mono_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8971_snd_controls[] = अणु
	SOC_DOUBLE_R("Capture Volume", WM8971_LINVOL, WM8971_RINVOL, 0, 63, 0),
	SOC_DOUBLE_R("Capture ZC Switch", WM8971_LINVOL, WM8971_RINVOL,
		     6, 1, 0),
	SOC_DOUBLE_R("Capture Switch", WM8971_LINVOL, WM8971_RINVOL, 7, 1, 1),

	SOC_DOUBLE_R("Headphone Playback ZC Switch", WM8971_LOUT1V,
		WM8971_ROUT1V, 7, 1, 0),
	SOC_DOUBLE_R("Speaker Playback ZC Switch", WM8971_LOUT2V,
		WM8971_ROUT2V, 7, 1, 0),
	SOC_SINGLE("Mono Playback ZC Switch", WM8971_MOUTV, 7, 1, 0),

	SOC_DOUBLE_R("PCM Volume", WM8971_LDAC, WM8971_RDAC, 0, 255, 0),

	SOC_DOUBLE_R("Bypass Left Playback Volume", WM8971_LOUTM1,
		WM8971_LOUTM2, 4, 7, 1),
	SOC_DOUBLE_R("Bypass Right Playback Volume", WM8971_ROUTM1,
		WM8971_ROUTM2, 4, 7, 1),
	SOC_DOUBLE_R("Bypass Mono Playback Volume", WM8971_MOUTM1,
		WM8971_MOUTM2, 4, 7, 1),

	SOC_DOUBLE_R("Headphone Playback Volume", WM8971_LOUT1V,
		WM8971_ROUT1V, 0, 127, 0),
	SOC_DOUBLE_R("Speaker Playback Volume", WM8971_LOUT2V,
		WM8971_ROUT2V, 0, 127, 0),

	SOC_ENUM("Bass Boost", wm8971_क्रमागत[0]),
	SOC_ENUM("Bass Filter", wm8971_क्रमागत[1]),
	SOC_SINGLE("Bass Volume", WM8971_BASS, 0, 7, 1),

	SOC_SINGLE("Treble Volume", WM8971_TREBLE, 0, 7, 0),
	SOC_ENUM("Treble Cut-off", wm8971_क्रमागत[2]),

	SOC_SINGLE("Capture Filter Switch", WM8971_ADCDAC, 0, 1, 1),

	SOC_SINGLE("ALC Target Volume", WM8971_ALC1, 0, 7, 0),
	SOC_SINGLE("ALC Max Volume", WM8971_ALC1, 4, 7, 0),

	SOC_SINGLE("ALC Capture Target Volume", WM8971_ALC1, 0, 7, 0),
	SOC_SINGLE("ALC Capture Max Volume", WM8971_ALC1, 4, 7, 0),
	SOC_ENUM("ALC Capture Function", wm8971_क्रमागत[3]),
	SOC_SINGLE("ALC Capture ZC Switch", WM8971_ALC2, 7, 1, 0),
	SOC_SINGLE("ALC Capture Hold Time", WM8971_ALC2, 0, 15, 0),
	SOC_SINGLE("ALC Capture Decay Time", WM8971_ALC3, 4, 15, 0),
	SOC_SINGLE("ALC Capture Attack Time", WM8971_ALC3, 0, 15, 0),
	SOC_SINGLE("ALC Capture NG Threshold", WM8971_NGATE, 3, 31, 0),
	SOC_ENUM("ALC Capture NG Type", wm8971_क्रमागत[4]),
	SOC_SINGLE("ALC Capture NG Switch", WM8971_NGATE, 0, 1, 0),

	SOC_SINGLE("Capture 6dB Attenuate", WM8971_ADCDAC, 8, 1, 0),
	SOC_SINGLE("Playback 6dB Attenuate", WM8971_ADCDAC, 7, 1, 0),

	SOC_ENUM("Playback De-emphasis", wm8971_क्रमागत[5]),
	SOC_ENUM("Playback Function", wm8971_क्रमागत[6]),
	SOC_ENUM("Playback Phase", wm8971_क्रमागत[7]),

	SOC_DOUBLE_R("Mic Boost", WM8971_LADCIN, WM8971_RADCIN, 4, 3, 0),
पूर्ण;

/*
 * DAPM Controls
 */

/* Left Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Playback Switch", WM8971_LOUTM1, 8, 1, 0),
SOC_DAPM_SINGLE("Left Bypass Switch", WM8971_LOUTM1, 7, 1, 0),
SOC_DAPM_SINGLE("Right Playback Switch", WM8971_LOUTM2, 8, 1, 0),
SOC_DAPM_SINGLE("Right Bypass Switch", WM8971_LOUTM2, 7, 1, 0),
पूर्ण;

/* Right Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Left Playback Switch", WM8971_ROUTM1, 8, 1, 0),
SOC_DAPM_SINGLE("Left Bypass Switch", WM8971_ROUTM1, 7, 1, 0),
SOC_DAPM_SINGLE("Playback Switch", WM8971_ROUTM2, 8, 1, 0),
SOC_DAPM_SINGLE("Right Bypass Switch", WM8971_ROUTM2, 7, 1, 0),
पूर्ण;

/* Mono Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_mono_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Left Playback Switch", WM8971_MOUTM1, 8, 1, 0),
SOC_DAPM_SINGLE("Left Bypass Switch", WM8971_MOUTM1, 7, 1, 0),
SOC_DAPM_SINGLE("Right Playback Switch", WM8971_MOUTM2, 8, 1, 0),
SOC_DAPM_SINGLE("Right Bypass Switch", WM8971_MOUTM2, 7, 1, 0),
पूर्ण;

/* Left Line Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_left_line_controls =
SOC_DAPM_ENUM("Route", wm8971_क्रमागत[8]);

/* Right Line Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_right_line_controls =
SOC_DAPM_ENUM("Route", wm8971_क्रमागत[9]);

/* Left PGA Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_left_pga_controls =
SOC_DAPM_ENUM("Route", wm8971_क्रमागत[10]);

/* Right PGA Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_right_pga_controls =
SOC_DAPM_ENUM("Route", wm8971_क्रमागत[11]);

/* Mono ADC Mux */
अटल स्थिर काष्ठा snd_kcontrol_new wm8971_monomux_controls =
SOC_DAPM_ENUM("Route", wm8971_क्रमागत[13]);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8971_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Left Mixer", SND_SOC_NOPM, 0, 0,
		&wm8971_left_mixer_controls[0],
		ARRAY_SIZE(wm8971_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Mixer", SND_SOC_NOPM, 0, 0,
		&wm8971_right_mixer_controls[0],
		ARRAY_SIZE(wm8971_right_mixer_controls)),
	SND_SOC_DAPM_MIXER("Mono Mixer", WM8971_PWR2, 2, 0,
		&wm8971_mono_mixer_controls[0],
		ARRAY_SIZE(wm8971_mono_mixer_controls)),

	SND_SOC_DAPM_PGA("Right Out 2", WM8971_PWR2, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left Out 2", WM8971_PWR2, 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Out 1", WM8971_PWR2, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Left Out 1", WM8971_PWR2, 6, 0, शून्य, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Right Playback", WM8971_PWR2, 7, 0),
	SND_SOC_DAPM_DAC("Left DAC", "Left Playback", WM8971_PWR2, 8, 0),
	SND_SOC_DAPM_PGA("Mono Out 1", WM8971_PWR2, 2, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias", WM8971_PWR1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", WM8971_PWR1, 2, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", WM8971_PWR1, 3, 0),

	SND_SOC_DAPM_MUX("Left PGA Mux", WM8971_PWR1, 5, 0,
		&wm8971_left_pga_controls),
	SND_SOC_DAPM_MUX("Right PGA Mux", WM8971_PWR1, 4, 0,
		&wm8971_right_pga_controls),
	SND_SOC_DAPM_MUX("Left Line Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_left_line_controls),
	SND_SOC_DAPM_MUX("Right Line Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_right_line_controls),

	SND_SOC_DAPM_MUX("Left ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_monomux_controls),
	SND_SOC_DAPM_MUX("Right ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_monomux_controls),

	SND_SOC_DAPM_OUTPUT("LOUT1"),
	SND_SOC_DAPM_OUTPUT("ROUT1"),
	SND_SOC_DAPM_OUTPUT("LOUT2"),
	SND_SOC_DAPM_OUTPUT("ROUT2"),
	SND_SOC_DAPM_OUTPUT("MONO"),

	SND_SOC_DAPM_INPUT("LINPUT1"),
	SND_SOC_DAPM_INPUT("RINPUT1"),
	SND_SOC_DAPM_INPUT("MIC"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8971_dapm_routes[] = अणु
	/* left mixer */
	अणु"Left Mixer", "Playback Switch", "Left DAC"पूर्ण,
	अणु"Left Mixer", "Left Bypass Switch", "Left Line Mux"पूर्ण,
	अणु"Left Mixer", "Right Playback Switch", "Right DAC"पूर्ण,
	अणु"Left Mixer", "Right Bypass Switch", "Right Line Mux"पूर्ण,

	/* right mixer */
	अणु"Right Mixer", "Left Playback Switch", "Left DAC"पूर्ण,
	अणु"Right Mixer", "Left Bypass Switch", "Left Line Mux"पूर्ण,
	अणु"Right Mixer", "Playback Switch", "Right DAC"पूर्ण,
	अणु"Right Mixer", "Right Bypass Switch", "Right Line Mux"पूर्ण,

	/* left out 1 */
	अणु"Left Out 1", शून्य, "Left Mixer"पूर्ण,
	अणु"LOUT1", शून्य, "Left Out 1"पूर्ण,

	/* left out 2 */
	अणु"Left Out 2", शून्य, "Left Mixer"पूर्ण,
	अणु"LOUT2", शून्य, "Left Out 2"पूर्ण,

	/* right out 1 */
	अणु"Right Out 1", शून्य, "Right Mixer"पूर्ण,
	अणु"ROUT1", शून्य, "Right Out 1"पूर्ण,

	/* right out 2 */
	अणु"Right Out 2", शून्य, "Right Mixer"पूर्ण,
	अणु"ROUT2", शून्य, "Right Out 2"पूर्ण,

	/* mono mixer */
	अणु"Mono Mixer", "Left Playback Switch", "Left DAC"पूर्ण,
	अणु"Mono Mixer", "Left Bypass Switch", "Left Line Mux"पूर्ण,
	अणु"Mono Mixer", "Right Playback Switch", "Right DAC"पूर्ण,
	अणु"Mono Mixer", "Right Bypass Switch", "Right Line Mux"पूर्ण,

	/* mono out */
	अणु"Mono Out", शून्य, "Mono Mixer"पूर्ण,
	अणु"MONO1", शून्य, "Mono Out"पूर्ण,

	/* Left Line Mux */
	अणु"Left Line Mux", "Line", "LINPUT1"पूर्ण,
	अणु"Left Line Mux", "PGA", "Left PGA Mux"पूर्ण,
	अणु"Left Line Mux", "Differential", "Differential Mux"पूर्ण,

	/* Right Line Mux */
	अणु"Right Line Mux", "Line", "RINPUT1"पूर्ण,
	अणु"Right Line Mux", "Mic", "MIC"पूर्ण,
	अणु"Right Line Mux", "PGA", "Right PGA Mux"पूर्ण,
	अणु"Right Line Mux", "Differential", "Differential Mux"पूर्ण,

	/* Left PGA Mux */
	अणु"Left PGA Mux", "Line", "LINPUT1"पूर्ण,
	अणु"Left PGA Mux", "Differential", "Differential Mux"पूर्ण,

	/* Right PGA Mux */
	अणु"Right PGA Mux", "Line", "RINPUT1"पूर्ण,
	अणु"Right PGA Mux", "Differential", "Differential Mux"पूर्ण,

	/* Dअगरferential Mux */
	अणु"Differential Mux", "Line", "LINPUT1"पूर्ण,
	अणु"Differential Mux", "Line", "RINPUT1"पूर्ण,

	/* Left ADC Mux */
	अणु"Left ADC Mux", "Stereo", "Left PGA Mux"पूर्ण,
	अणु"Left ADC Mux", "Mono (Left)", "Left PGA Mux"पूर्ण,
	अणु"Left ADC Mux", "Digital Mono", "Left PGA Mux"पूर्ण,

	/* Right ADC Mux */
	अणु"Right ADC Mux", "Stereo", "Right PGA Mux"पूर्ण,
	अणु"Right ADC Mux", "Mono (Right)", "Right PGA Mux"पूर्ण,
	अणु"Right ADC Mux", "Digital Mono", "Right PGA Mux"पूर्ण,

	/* ADC */
	अणु"Left ADC", शून्य, "Left ADC Mux"पूर्ण,
	अणु"Right ADC", शून्य, "Right ADC Mux"पूर्ण,
पूर्ण;

काष्ठा _coeff_भाग अणु
	u32 mclk;
	u32 rate;
	u16 fs;
	u8 sr:5;
	u8 usb:1;
पूर्ण;

/* codec hअगरi mclk घड़ी भागider coefficients */
अटल स्थिर काष्ठा _coeff_भाग coeff_भाग[] = अणु
	/* 8k */
	अणु12288000, 8000, 1536, 0x6, 0x0पूर्ण,
	अणु11289600, 8000, 1408, 0x16, 0x0पूर्ण,
	अणु18432000, 8000, 2304, 0x7, 0x0पूर्ण,
	अणु16934400, 8000, 2112, 0x17, 0x0पूर्ण,
	अणु12000000, 8000, 1500, 0x6, 0x1पूर्ण,

	/* 11.025k */
	अणु11289600, 11025, 1024, 0x18, 0x0पूर्ण,
	अणु16934400, 11025, 1536, 0x19, 0x0पूर्ण,
	अणु12000000, 11025, 1088, 0x19, 0x1पूर्ण,

	/* 16k */
	अणु12288000, 16000, 768, 0xa, 0x0पूर्ण,
	अणु18432000, 16000, 1152, 0xb, 0x0पूर्ण,
	अणु12000000, 16000, 750, 0xa, 0x1पूर्ण,

	/* 22.05k */
	अणु11289600, 22050, 512, 0x1a, 0x0पूर्ण,
	अणु16934400, 22050, 768, 0x1b, 0x0पूर्ण,
	अणु12000000, 22050, 544, 0x1b, 0x1पूर्ण,

	/* 32k */
	अणु12288000, 32000, 384, 0xc, 0x0पूर्ण,
	अणु18432000, 32000, 576, 0xd, 0x0पूर्ण,
	अणु12000000, 32000, 375, 0xa, 0x1पूर्ण,

	/* 44.1k */
	अणु11289600, 44100, 256, 0x10, 0x0पूर्ण,
	अणु16934400, 44100, 384, 0x11, 0x0पूर्ण,
	अणु12000000, 44100, 272, 0x11, 0x1पूर्ण,

	/* 48k */
	अणु12288000, 48000, 256, 0x0, 0x0पूर्ण,
	अणु18432000, 48000, 384, 0x1, 0x0पूर्ण,
	अणु12000000, 48000, 250, 0x0, 0x1पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, 128, 0x1e, 0x0पूर्ण,
	अणु16934400, 88200, 192, 0x1f, 0x0पूर्ण,
	अणु12000000, 88200, 136, 0x1f, 0x1पूर्ण,

	/* 96k */
	अणु12288000, 96000, 128, 0xe, 0x0पूर्ण,
	अणु18432000, 96000, 192, 0xf, 0x0पूर्ण,
	अणु12000000, 96000, 125, 0xe, 0x1पूर्ण,
पूर्ण;

अटल पूर्णांक get_coeff(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].rate == rate && coeff_भाग[i].mclk == mclk)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8971_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8971_priv *wm8971 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल 11289600:
	हाल 12000000:
	हाल 12288000:
	हाल 16934400:
	हाल 18432000:
		wm8971->sysclk = freq;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8971_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace = 0x0040;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= 0x0003;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= 0x0013;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x0090;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x0080;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x0010;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8971_IFACE, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8971_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8971_priv *wm8971 = snd_soc_component_get_drvdata(component);
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8971_IFACE) & 0x1f3;
	u16 srate = snd_soc_component_पढ़ो(component, WM8971_SRATE) & 0x1c0;
	पूर्णांक coeff = get_coeff(wm8971->sysclk, params_rate(params));

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= 0x0004;
		अवरोध;
	हाल 24:
		अगरace |= 0x0008;
		अवरोध;
	हाल 32:
		अगरace |= 0x000c;
		अवरोध;
	पूर्ण

	/* set अगरace & srate */
	snd_soc_component_ग_लिखो(component, WM8971_IFACE, अगरace);
	अगर (coeff >= 0)
		snd_soc_component_ग_लिखो(component, WM8971_SRATE, srate |
			(coeff_भाग[coeff].sr << 1) | coeff_भाग[coeff].usb);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8971_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8971_ADCDAC) & 0xfff7;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8971_ADCDAC, mute_reg | 0x8);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8971_ADCDAC, mute_reg);
	वापस 0;
पूर्ण

अटल व्योम wm8971_अक्षरge_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm8971_priv *wm8971 =
		container_of(work, काष्ठा wm8971_priv, अक्षरge_work.work);

	/* Set to 500k */
	regmap_update_bits(wm8971->regmap, WM8971_PWR1, 0x0180, 0x0100);
पूर्ण

अटल पूर्णांक wm8971_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8971_priv *wm8971 = snd_soc_component_get_drvdata(component);
	u16 pwr_reg = snd_soc_component_पढ़ो(component, WM8971_PWR1) & 0xfe3e;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* set vmid to 50k and unmute dac */
		snd_soc_component_ग_लिखो(component, WM8971_PWR1, pwr_reg | 0x00c1);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		/* Wait until fully अक्षरged */
		flush_delayed_work(&wm8971->अक्षरge_work);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_cache_sync(component);
			/* अक्षरge output caps - set vmid to 5k क्रम quick घातer up */
			snd_soc_component_ग_लिखो(component, WM8971_PWR1, pwr_reg | 0x01c0);
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
				&wm8971->अक्षरge_work, msecs_to_jअगरfies(1000));
		पूर्ण अन्यथा अणु
			/* mute dac and set vmid to 500k, enable VREF */
			snd_soc_component_ग_लिखो(component, WM8971_PWR1, pwr_reg | 0x0140);
		पूर्ण

		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		cancel_delayed_work_sync(&wm8971->अक्षरge_work);
		snd_soc_component_ग_लिखो(component, WM8971_PWR1, 0x0001);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8971_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_44100 | \
		SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)

#घोषणा WM8971_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8971_dai_ops = अणु
	.hw_params	= wm8971_pcm_hw_params,
	.mute_stream	= wm8971_mute,
	.set_fmt	= wm8971_set_dai_fmt,
	.set_sysclk	= wm8971_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8971_dai = अणु
	.name = "wm8971-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8971_RATES,
		.क्रमmats = WM8971_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8971_RATES,
		.क्रमmats = WM8971_FORMATS,पूर्ण,
	.ops = &wm8971_dai_ops,
पूर्ण;

अटल पूर्णांक wm8971_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8971_priv *wm8971 = snd_soc_component_get_drvdata(component);

	INIT_DELAYED_WORK(&wm8971->अक्षरge_work, wm8971_अक्षरge_work);

	wm8971_reset(component);

	/* set the update bits */
	snd_soc_component_update_bits(component, WM8971_LDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_RDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_LOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_ROUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_LOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_ROUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_LINVOL, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_RINVOL, 0x0100, 0x0100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8971 = अणु
	.probe			= wm8971_probe,
	.set_bias_level		= wm8971_set_bias_level,
	.controls		= wm8971_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8971_snd_controls),
	.dapm_widमाला_लो		= wm8971_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8971_dapm_widमाला_लो),
	.dapm_routes		= wm8971_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8971_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8971_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8971_MOUTV,

	.reg_शेषs = wm8971_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8971_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक wm8971_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8971_priv *wm8971;
	पूर्णांक ret;

	wm8971 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8971_priv),
			      GFP_KERNEL);
	अगर (wm8971 == शून्य)
		वापस -ENOMEM;

	wm8971->regmap = devm_regmap_init_i2c(i2c, &wm8971_regmap);
	अगर (IS_ERR(wm8971->regmap))
		वापस PTR_ERR(wm8971->regmap);

	i2c_set_clientdata(i2c, wm8971);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8971, &wm8971_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8971_i2c_id[] = अणु
	अणु "wm8971", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8971_i2c_id);

अटल काष्ठा i2c_driver wm8971_i2c_driver = अणु
	.driver = अणु
		.name = "wm8971",
	पूर्ण,
	.probe =    wm8971_i2c_probe,
	.id_table = wm8971_i2c_id,
पूर्ण;

module_i2c_driver(wm8971_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8971 driver");
MODULE_AUTHOR("Lab126");
MODULE_LICENSE("GPL");
