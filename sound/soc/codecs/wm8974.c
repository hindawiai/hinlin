<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8974.c  --  WM8974 ALSA Soc Audio driver
 *
 * Copyright 2006-2009 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood <Liam.Girdwood@wolfsonmicro.com>
 */

#समावेश <linux/module.h>
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

#समावेश "wm8974.h"

काष्ठा wm8974_priv अणु
	अचिन्हित पूर्णांक mclk;
	अचिन्हित पूर्णांक fs;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8974_reg_शेषs[] = अणु
	अणु  0, 0x0000 पूर्ण, अणु  1, 0x0000 पूर्ण, अणु  2, 0x0000 पूर्ण, अणु  3, 0x0000 पूर्ण,
	अणु  4, 0x0050 पूर्ण, अणु  5, 0x0000 पूर्ण, अणु  6, 0x0140 पूर्ण, अणु  7, 0x0000 पूर्ण,
	अणु  8, 0x0000 पूर्ण, अणु  9, 0x0000 पूर्ण, अणु 10, 0x0000 पूर्ण, अणु 11, 0x00ff पूर्ण,
	अणु 12, 0x0000 पूर्ण, अणु 13, 0x0000 पूर्ण, अणु 14, 0x0100 पूर्ण, अणु 15, 0x00ff पूर्ण,
	अणु 16, 0x0000 पूर्ण, अणु 17, 0x0000 पूर्ण, अणु 18, 0x012c पूर्ण, अणु 19, 0x002c पूर्ण,
	अणु 20, 0x002c पूर्ण, अणु 21, 0x002c पूर्ण, अणु 22, 0x002c पूर्ण, अणु 23, 0x0000 पूर्ण,
	अणु 24, 0x0032 पूर्ण, अणु 25, 0x0000 पूर्ण, अणु 26, 0x0000 पूर्ण, अणु 27, 0x0000 पूर्ण,
	अणु 28, 0x0000 पूर्ण, अणु 29, 0x0000 पूर्ण, अणु 30, 0x0000 पूर्ण, अणु 31, 0x0000 पूर्ण,
	अणु 32, 0x0038 पूर्ण, अणु 33, 0x000b पूर्ण, अणु 34, 0x0032 पूर्ण, अणु 35, 0x0000 पूर्ण,
	अणु 36, 0x0008 पूर्ण, अणु 37, 0x000c पूर्ण, अणु 38, 0x0093 पूर्ण, अणु 39, 0x00e9 पूर्ण,
	अणु 40, 0x0000 पूर्ण, अणु 41, 0x0000 पूर्ण, अणु 42, 0x0000 पूर्ण, अणु 43, 0x0000 पूर्ण,
	अणु 44, 0x0003 पूर्ण, अणु 45, 0x0010 पूर्ण, अणु 46, 0x0000 पूर्ण, अणु 47, 0x0000 पूर्ण,
	अणु 48, 0x0000 पूर्ण, अणु 49, 0x0002 पूर्ण, अणु 50, 0x0000 पूर्ण, अणु 51, 0x0000 पूर्ण,
	अणु 52, 0x0000 पूर्ण, अणु 53, 0x0000 पूर्ण, अणु 54, 0x0039 पूर्ण, अणु 55, 0x0000 पूर्ण,
	अणु 56, 0x0000 पूर्ण,
पूर्ण;

#घोषणा WM8974_POWER1_BIASEN  0x08
#घोषणा WM8974_POWER1_BUFIOEN 0x04

#घोषणा wm8974_reset(c)	snd_soc_component_ग_लिखो(c, WM8974_RESET, 0)

अटल स्थिर अक्षर *wm8974_companding[] = अणु"Off", "NC", "u-law", "A-law" पूर्ण;
अटल स्थिर अक्षर *wm8974_deemp[] = अणु"None", "32kHz", "44.1kHz", "48kHz" पूर्ण;
अटल स्थिर अक्षर *wm8974_eqmode[] = अणु"Capture", "Playback" पूर्ण;
अटल स्थिर अक्षर *wm8974_bw[] = अणु"Narrow", "Wide" पूर्ण;
अटल स्थिर अक्षर *wm8974_eq1[] = अणु"80Hz", "105Hz", "135Hz", "175Hz" पूर्ण;
अटल स्थिर अक्षर *wm8974_eq2[] = अणु"230Hz", "300Hz", "385Hz", "500Hz" पूर्ण;
अटल स्थिर अक्षर *wm8974_eq3[] = अणु"650Hz", "850Hz", "1.1kHz", "1.4kHz" पूर्ण;
अटल स्थिर अक्षर *wm8974_eq4[] = अणु"1.8kHz", "2.4kHz", "3.2kHz", "4.1kHz" पूर्ण;
अटल स्थिर अक्षर *wm8974_eq5[] = अणु"5.3kHz", "6.9kHz", "9kHz", "11.7kHz" पूर्ण;
अटल स्थिर अक्षर *wm8974_alc[] = अणु"ALC", "Limiter" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8974_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(WM8974_COMP, 1, 4, wm8974_companding), /* adc */
	SOC_ENUM_SINGLE(WM8974_COMP, 3, 4, wm8974_companding), /* dac */
	SOC_ENUM_SINGLE(WM8974_DAC,  4, 4, wm8974_deemp),
	SOC_ENUM_SINGLE(WM8974_EQ1,  8, 2, wm8974_eqmode),

	SOC_ENUM_SINGLE(WM8974_EQ1,  5, 4, wm8974_eq1),
	SOC_ENUM_SINGLE(WM8974_EQ2,  8, 2, wm8974_bw),
	SOC_ENUM_SINGLE(WM8974_EQ2,  5, 4, wm8974_eq2),
	SOC_ENUM_SINGLE(WM8974_EQ3,  8, 2, wm8974_bw),

	SOC_ENUM_SINGLE(WM8974_EQ3,  5, 4, wm8974_eq3),
	SOC_ENUM_SINGLE(WM8974_EQ4,  8, 2, wm8974_bw),
	SOC_ENUM_SINGLE(WM8974_EQ4,  5, 4, wm8974_eq4),
	SOC_ENUM_SINGLE(WM8974_EQ5,  8, 2, wm8974_bw),

	SOC_ENUM_SINGLE(WM8974_EQ5,  5, 4, wm8974_eq5),
	SOC_ENUM_SINGLE(WM8974_ALC3,  8, 2, wm8974_alc),
पूर्ण;

अटल स्थिर अक्षर *wm8974_auxmode_text[] = अणु "Buffer", "Mixer" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8974_auxmode,
			    WM8974_INPUT,  3, wm8974_auxmode_text);

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_tlv, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_tlv, -1200, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(spk_tlv, -5700, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new wm8974_snd_controls[] = अणु

SOC_SINGLE("Digital Loopback Switch", WM8974_COMP, 0, 1, 0),

SOC_ENUM("DAC Companding", wm8974_क्रमागत[1]),
SOC_ENUM("ADC Companding", wm8974_क्रमागत[0]),

SOC_ENUM("Playback De-emphasis", wm8974_क्रमागत[2]),
SOC_SINGLE("DAC Inversion Switch", WM8974_DAC, 0, 1, 0),

SOC_SINGLE_TLV("PCM Volume", WM8974_DACVOL, 0, 255, 0, digital_tlv),

SOC_SINGLE("High Pass Filter Switch", WM8974_ADC, 8, 1, 0),
SOC_SINGLE("High Pass Cut Off", WM8974_ADC, 4, 7, 0),
SOC_SINGLE("ADC Inversion Switch", WM8974_ADC, 0, 1, 0),

SOC_SINGLE_TLV("Capture Volume", WM8974_ADCVOL,  0, 255, 0, digital_tlv),

SOC_ENUM("Equaliser Function", wm8974_क्रमागत[3]),
SOC_ENUM("EQ1 Cut Off", wm8974_क्रमागत[4]),
SOC_SINGLE_TLV("EQ1 Volume", WM8974_EQ1,  0, 24, 1, eq_tlv),

SOC_ENUM("Equaliser EQ2 Bandwidth", wm8974_क्रमागत[5]),
SOC_ENUM("EQ2 Cut Off", wm8974_क्रमागत[6]),
SOC_SINGLE_TLV("EQ2 Volume", WM8974_EQ2,  0, 24, 1, eq_tlv),

SOC_ENUM("Equaliser EQ3 Bandwidth", wm8974_क्रमागत[7]),
SOC_ENUM("EQ3 Cut Off", wm8974_क्रमागत[8]),
SOC_SINGLE_TLV("EQ3 Volume", WM8974_EQ3,  0, 24, 1, eq_tlv),

SOC_ENUM("Equaliser EQ4 Bandwidth", wm8974_क्रमागत[9]),
SOC_ENUM("EQ4 Cut Off", wm8974_क्रमागत[10]),
SOC_SINGLE_TLV("EQ4 Volume", WM8974_EQ4,  0, 24, 1, eq_tlv),

SOC_ENUM("Equaliser EQ5 Bandwidth", wm8974_क्रमागत[11]),
SOC_ENUM("EQ5 Cut Off", wm8974_क्रमागत[12]),
SOC_SINGLE_TLV("EQ5 Volume", WM8974_EQ5,  0, 24, 1, eq_tlv),

SOC_SINGLE("DAC Playback Limiter Switch", WM8974_DACLIM1,  8, 1, 0),
SOC_SINGLE("DAC Playback Limiter Decay", WM8974_DACLIM1,  4, 15, 0),
SOC_SINGLE("DAC Playback Limiter Attack", WM8974_DACLIM1,  0, 15, 0),

SOC_SINGLE("DAC Playback Limiter Threshold", WM8974_DACLIM2,  4, 7, 0),
SOC_SINGLE("DAC Playback Limiter Boost", WM8974_DACLIM2,  0, 15, 0),

SOC_SINGLE("ALC Enable Switch", WM8974_ALC1,  8, 1, 0),
SOC_SINGLE("ALC Capture Max Gain", WM8974_ALC1,  3, 7, 0),
SOC_SINGLE("ALC Capture Min Gain", WM8974_ALC1,  0, 7, 0),

SOC_SINGLE("ALC Capture ZC Switch", WM8974_ALC2,  8, 1, 0),
SOC_SINGLE("ALC Capture Hold", WM8974_ALC2,  4, 7, 0),
SOC_SINGLE("ALC Capture Target", WM8974_ALC2,  0, 15, 0),

SOC_ENUM("ALC Capture Mode", wm8974_क्रमागत[13]),
SOC_SINGLE("ALC Capture Decay", WM8974_ALC3,  4, 15, 0),
SOC_SINGLE("ALC Capture Attack", WM8974_ALC3,  0, 15, 0),

SOC_SINGLE("ALC Capture Noise Gate Switch", WM8974_NGATE,  3, 1, 0),
SOC_SINGLE("ALC Capture Noise Gate Threshold", WM8974_NGATE,  0, 7, 0),

SOC_SINGLE("Capture PGA ZC Switch", WM8974_INPPGA,  7, 1, 0),
SOC_SINGLE_TLV("Capture PGA Volume", WM8974_INPPGA,  0, 63, 0, inpga_tlv),

SOC_SINGLE("Speaker Playback ZC Switch", WM8974_SPKVOL,  7, 1, 0),
SOC_SINGLE("Speaker Playback Switch", WM8974_SPKVOL,  6, 1, 1),
SOC_SINGLE_TLV("Speaker Playback Volume", WM8974_SPKVOL,  0, 63, 0, spk_tlv),

SOC_ENUM("Aux Mode", wm8974_auxmode),

SOC_SINGLE("Capture Boost(+20dB)", WM8974_ADCBOOST,  8, 1, 0),
SOC_SINGLE("Mono Playback Switch", WM8974_MONOMIX, 6, 1, 1),

/* DAC / ADC oversampling */
SOC_SINGLE("DAC 128x Oversampling Switch", WM8974_DAC, 8, 1, 0),
SOC_SINGLE("ADC 128x Oversampling Switch", WM8974_ADC, 8, 1, 0),
पूर्ण;

/* Speaker Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8974_speaker_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Bypass Switch", WM8974_SPKMIX, 1, 1, 0),
SOC_DAPM_SINGLE("Aux Playback Switch", WM8974_SPKMIX, 5, 1, 0),
SOC_DAPM_SINGLE("PCM Playback Switch", WM8974_SPKMIX, 0, 1, 0),
पूर्ण;

/* Mono Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8974_mono_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Bypass Switch", WM8974_MONOMIX, 1, 1, 0),
SOC_DAPM_SINGLE("Aux Playback Switch", WM8974_MONOMIX, 2, 1, 0),
SOC_DAPM_SINGLE("PCM Playback Switch", WM8974_MONOMIX, 0, 1, 0),
पूर्ण;

/* Boost mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8974_boost_mixer[] = अणु
SOC_DAPM_SINGLE("Aux Switch", WM8974_INPPGA, 6, 1, 1),
पूर्ण;

/* Input PGA */
अटल स्थिर काष्ठा snd_kcontrol_new wm8974_inpga[] = अणु
SOC_DAPM_SINGLE("Aux Switch", WM8974_INPUT, 2, 1, 0),
SOC_DAPM_SINGLE("MicN Switch", WM8974_INPUT, 1, 1, 0),
SOC_DAPM_SINGLE("MicP Switch", WM8974_INPUT, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8974_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MIXER("Speaker Mixer", WM8974_POWER3, 2, 0,
	&wm8974_speaker_mixer_controls[0],
	ARRAY_SIZE(wm8974_speaker_mixer_controls)),
SND_SOC_DAPM_MIXER("Mono Mixer", WM8974_POWER3, 3, 0,
	&wm8974_mono_mixer_controls[0],
	ARRAY_SIZE(wm8974_mono_mixer_controls)),
SND_SOC_DAPM_DAC("DAC", "HiFi Playback", WM8974_POWER3, 0, 0),
SND_SOC_DAPM_ADC("ADC", "HiFi Capture", WM8974_POWER2, 0, 0),
SND_SOC_DAPM_PGA("Aux Input", WM8974_POWER1, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("SpkN Out", WM8974_POWER3, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("SpkP Out", WM8974_POWER3, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Mono Out", WM8974_POWER3, 7, 0, शून्य, 0),

SND_SOC_DAPM_MIXER("Input PGA", WM8974_POWER2, 2, 0, wm8974_inpga,
		   ARRAY_SIZE(wm8974_inpga)),
SND_SOC_DAPM_MIXER("Boost Mixer", WM8974_POWER2, 4, 0,
		   wm8974_boost_mixer, ARRAY_SIZE(wm8974_boost_mixer)),

SND_SOC_DAPM_SUPPLY("Mic Bias", WM8974_POWER1, 4, 0, शून्य, 0),

SND_SOC_DAPM_INPUT("MICN"),
SND_SOC_DAPM_INPUT("MICP"),
SND_SOC_DAPM_INPUT("AUX"),
SND_SOC_DAPM_OUTPUT("MONOOUT"),
SND_SOC_DAPM_OUTPUT("SPKOUTP"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8974_dapm_routes[] = अणु
	/* Mono output mixer */
	अणु"Mono Mixer", "PCM Playback Switch", "DAC"पूर्ण,
	अणु"Mono Mixer", "Aux Playback Switch", "Aux Input"पूर्ण,
	अणु"Mono Mixer", "Line Bypass Switch", "Boost Mixer"पूर्ण,

	/* Speaker output mixer */
	अणु"Speaker Mixer", "PCM Playback Switch", "DAC"पूर्ण,
	अणु"Speaker Mixer", "Aux Playback Switch", "Aux Input"पूर्ण,
	अणु"Speaker Mixer", "Line Bypass Switch", "Boost Mixer"पूर्ण,

	/* Outमाला_दो */
	अणु"Mono Out", शून्य, "Mono Mixer"पूर्ण,
	अणु"MONOOUT", शून्य, "Mono Out"पूर्ण,
	अणु"SpkN Out", शून्य, "Speaker Mixer"पूर्ण,
	अणु"SpkP Out", शून्य, "Speaker Mixer"पूर्ण,
	अणु"SPKOUTN", शून्य, "SpkN Out"पूर्ण,
	अणु"SPKOUTP", शून्य, "SpkP Out"पूर्ण,

	/* Boost Mixer */
	अणु"ADC", शून्य, "Boost Mixer"पूर्ण,
	अणु"Boost Mixer", "Aux Switch", "Aux Input"पूर्ण,
	अणु"Boost Mixer", शून्य, "Input PGA"पूर्ण,
	अणु"Boost Mixer", शून्य, "MICP"पूर्ण,

	/* Input PGA */
	अणु"Input PGA", "Aux Switch", "Aux Input"पूर्ण,
	अणु"Input PGA", "MicN Switch", "MICN"पूर्ण,
	अणु"Input PGA", "MicP Switch", "MICP"पूर्ण,

	/* Inमाला_दो */
	अणु"Aux Input", शून्य, "AUX"पूर्ण,
पूर्ण;

काष्ठा pll_ अणु
	अचिन्हित पूर्णांक pre_भाग:1;
	अचिन्हित पूर्णांक n:4;
	अचिन्हित पूर्णांक k;
पूर्ण;

/* The size in bits of the pll भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_PLL_SIZE ((1 << 24) * 10)

अटल व्योम pll_factors(काष्ठा pll_ *pll_भाग,
			अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक source)
अणु
	अचिन्हित दीर्घ दीर्घ Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;

	/* There is a fixed भागide by 4 in the output path */
	target *= 4;

	Nभाग = target / source;
	अगर (Nभाग < 6) अणु
		source /= 2;
		pll_भाग->pre_भाग = 1;
		Nभाग = target / source;
	पूर्ण अन्यथा
		pll_भाग->pre_भाग = 0;

	अगर ((Nभाग < 6) || (Nभाग > 12))
		prपूर्णांकk(KERN_WARNING
			"WM8974 N value %u outwith recommended range!\n",
			Nभाग);

	pll_भाग->n = Nभाग;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	/* Check अगर we need to round */
	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	K /= 10;

	pll_भाग->k = K;
पूर्ण

अटल पूर्णांक wm8974_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा pll_ pll_भाग;
	u16 reg;

	अगर (freq_in == 0 || freq_out == 0) अणु
		/* Clock CODEC directly from MCLK */
		reg = snd_soc_component_पढ़ो(component, WM8974_CLOCK);
		snd_soc_component_ग_लिखो(component, WM8974_CLOCK, reg & 0x0ff);

		/* Turn off PLL */
		reg = snd_soc_component_पढ़ो(component, WM8974_POWER1);
		snd_soc_component_ग_लिखो(component, WM8974_POWER1, reg & 0x1df);
		वापस 0;
	पूर्ण

	pll_factors(&pll_भाग, freq_out, freq_in);

	snd_soc_component_ग_लिखो(component, WM8974_PLLN, (pll_भाग.pre_भाग << 4) | pll_भाग.n);
	snd_soc_component_ग_लिखो(component, WM8974_PLLK1, pll_भाग.k >> 18);
	snd_soc_component_ग_लिखो(component, WM8974_PLLK2, (pll_भाग.k >> 9) & 0x1ff);
	snd_soc_component_ग_लिखो(component, WM8974_PLLK3, pll_भाग.k & 0x1ff);
	reg = snd_soc_component_पढ़ो(component, WM8974_POWER1);
	snd_soc_component_ग_लिखो(component, WM8974_POWER1, reg | 0x020);

	/* Run CODEC from PLL instead of MCLK */
	reg = snd_soc_component_पढ़ो(component, WM8974_CLOCK);
	snd_soc_component_ग_लिखो(component, WM8974_CLOCK, reg | 0x100);

	वापस 0;
पूर्ण

/*
 * Configure WM8974 घड़ी भागiders.
 */
अटल पूर्णांक wm8974_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	चयन (भाग_id) अणु
	हाल WM8974_OPCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8974_GPIO) & 0x1cf;
		snd_soc_component_ग_लिखो(component, WM8974_GPIO, reg | भाग);
		अवरोध;
	हाल WM8974_MCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8974_CLOCK) & 0x11f;
		snd_soc_component_ग_लिखो(component, WM8974_CLOCK, reg | भाग);
		अवरोध;
	हाल WM8974_BCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8974_CLOCK) & 0x1e3;
		snd_soc_component_ग_लिखो(component, WM8974_CLOCK, reg | भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक wm8974_get_mclkभाग(अचिन्हित पूर्णांक f_in, अचिन्हित पूर्णांक f_out,
				       पूर्णांक *mclkभाग)
अणु
	अचिन्हित पूर्णांक ratio = 2 * f_in / f_out;

	अगर (ratio <= 2) अणु
		*mclkभाग = WM8974_MCLKDIV_1;
		ratio = 2;
	पूर्ण अन्यथा अगर (ratio == 3) अणु
		*mclkभाग = WM8974_MCLKDIV_1_5;
	पूर्ण अन्यथा अगर (ratio == 4) अणु
		*mclkभाग = WM8974_MCLKDIV_2;
	पूर्ण अन्यथा अगर (ratio <= 6) अणु
		*mclkभाग = WM8974_MCLKDIV_3;
		ratio = 6;
	पूर्ण अन्यथा अगर (ratio <= 8) अणु
		*mclkभाग = WM8974_MCLKDIV_4;
		ratio = 8;
	पूर्ण अन्यथा अगर (ratio <= 12) अणु
		*mclkभाग = WM8974_MCLKDIV_6;
		ratio = 12;
	पूर्ण अन्यथा अगर (ratio <= 16) अणु
		*mclkभाग = WM8974_MCLKDIV_8;
		ratio = 16;
	पूर्ण अन्यथा अणु
		*mclkभाग = WM8974_MCLKDIV_12;
		ratio = 24;
	पूर्ण

	वापस f_out * ratio / 2;
पूर्ण

अटल पूर्णांक wm8974_update_घड़ीs(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8974_priv *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक fs256;
	अचिन्हित पूर्णांक fpll = 0;
	अचिन्हित पूर्णांक f;
	पूर्णांक mclkभाग;

	अगर (!priv->mclk || !priv->fs)
		वापस 0;

	fs256 = 256 * priv->fs;

	f = wm8974_get_mclkभाग(priv->mclk, fs256, &mclkभाग);

	अगर (f != priv->mclk) अणु
		/* The PLL perक्रमms best around 90MHz */
		fpll = wm8974_get_mclkभाग(22500000, fs256, &mclkभाग);
	पूर्ण

	wm8974_set_dai_pll(dai, 0, 0, priv->mclk, fpll);
	wm8974_set_dai_clkभाग(dai, WM8974_MCLKDIV, mclkभाग);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8974_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				 अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8974_priv *priv = snd_soc_component_get_drvdata(component);

	अगर (dir != SND_SOC_CLOCK_IN)
		वापस -EINVAL;

	priv->mclk = freq;

	वापस wm8974_update_घड़ीs(dai);
पूर्ण

अटल पूर्णांक wm8974_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;
	u16 clk = snd_soc_component_पढ़ो(component, WM8974_CLOCK) & 0x1fe;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		clk |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x0010;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x0008;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगर ((fmt & SND_SOC_DAIFMT_INV_MASK) == SND_SOC_DAIFMT_IB_IF ||
		    (fmt & SND_SOC_DAIFMT_INV_MASK) == SND_SOC_DAIFMT_NB_IF) अणु
			वापस -EINVAL;
		पूर्ण
		अगरace |= 0x00018;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x0180;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x0100;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x0080;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8974_IFACE, अगरace);
	snd_soc_component_ग_लिखो(component, WM8974_CLOCK, clk);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8974_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8974_priv *priv = snd_soc_component_get_drvdata(component);
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8974_IFACE) & 0x19f;
	u16 adn = snd_soc_component_पढ़ो(component, WM8974_ADD) & 0x1f1;
	पूर्णांक err;

	priv->fs = params_rate(params);
	err = wm8974_update_घड़ीs(dai);
	अगर (err)
		वापस err;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= 0x0020;
		अवरोध;
	हाल 24:
		अगरace |= 0x0040;
		अवरोध;
	हाल 32:
		अगरace |= 0x0060;
		अवरोध;
	पूर्ण

	/* filter coefficient */
	चयन (params_rate(params)) अणु
	हाल 8000:
		adn |= 0x5 << 1;
		अवरोध;
	हाल 11025:
		adn |= 0x4 << 1;
		अवरोध;
	हाल 16000:
		adn |= 0x3 << 1;
		अवरोध;
	हाल 22050:
		adn |= 0x2 << 1;
		अवरोध;
	हाल 32000:
		adn |= 0x1 << 1;
		अवरोध;
	हाल 44100:
	हाल 48000:
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8974_IFACE, अगरace);
	snd_soc_component_ग_लिखो(component, WM8974_ADD, adn);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8974_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8974_DAC) & 0xffbf;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8974_DAC, mute_reg | 0x40);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8974_DAC, mute_reg);
	वापस 0;
पूर्ण

/* liam need to make this lower घातer with dapm */
अटल पूर्णांक wm8974_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	u16 घातer1 = snd_soc_component_पढ़ो(component, WM8974_POWER1) & ~0x3;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		घातer1 |= 0x1;  /* VMID 50k */
		snd_soc_component_ग_लिखो(component, WM8974_POWER1, घातer1);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		घातer1 |= WM8974_POWER1_BIASEN | WM8974_POWER1_BUFIOEN;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_sync(dev_get_regmap(component->dev, शून्य));

			/* Initial cap अक्षरge at VMID 5k */
			snd_soc_component_ग_लिखो(component, WM8974_POWER1, घातer1 | 0x3);
			mdelay(100);
		पूर्ण

		घातer1 |= 0x2;  /* VMID 500k */
		snd_soc_component_ग_लिखो(component, WM8974_POWER1, घातer1);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, WM8974_POWER1, 0);
		snd_soc_component_ग_लिखो(component, WM8974_POWER2, 0);
		snd_soc_component_ग_लिखो(component, WM8974_POWER3, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8974_RATES (SNDRV_PCM_RATE_8000_48000)

#घोषणा WM8974_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8974_ops = अणु
	.hw_params = wm8974_pcm_hw_params,
	.mute_stream = wm8974_mute,
	.set_fmt = wm8974_set_dai_fmt,
	.set_clkभाग = wm8974_set_dai_clkभाग,
	.set_pll = wm8974_set_dai_pll,
	.set_sysclk = wm8974_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8974_dai = अणु
	.name = "wm8974-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,   /* Only 1 channel of data */
		.rates = WM8974_RATES,
		.क्रमmats = WM8974_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,   /* Only 1 channel of data */
		.rates = WM8974_RATES,
		.क्रमmats = WM8974_FORMATS,पूर्ण,
	.ops = &wm8974_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8974_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = WM8974_MONOMIX,
	.reg_शेषs = wm8974_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8974_reg_शेषs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक wm8974_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;

	ret = wm8974_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8974 = अणु
	.probe			= wm8974_probe,
	.set_bias_level		= wm8974_set_bias_level,
	.controls		= wm8974_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8974_snd_controls),
	.dapm_widमाला_लो		= wm8974_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8974_dapm_widमाला_लो),
	.dapm_routes		= wm8974_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8974_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8974_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8974_priv *priv;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	priv = devm_kzalloc(&i2c->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, priv);

	regmap = devm_regmap_init_i2c(i2c, &wm8974_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8974, &wm8974_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8974_i2c_id[] = अणु
	अणु "wm8974", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8974_i2c_id);

अटल स्थिर काष्ठा of_device_id wm8974_of_match[] = अणु
       अणु .compatible = "wlf,wm8974", पूर्ण,
       अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8974_of_match);

अटल काष्ठा i2c_driver wm8974_i2c_driver = अणु
	.driver = अणु
		.name = "wm8974",
		.of_match_table = wm8974_of_match,
	पूर्ण,
	.probe =    wm8974_i2c_probe,
	.id_table = wm8974_i2c_id,
पूर्ण;

module_i2c_driver(wm8974_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8974 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
