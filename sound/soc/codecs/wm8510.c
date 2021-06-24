<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8510.c  --  WM8510 ALSA Soc Audio driver
 *
 * Copyright 2006 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश "wm8510.h"

/*
 * wm8510 रेजिस्टर cache
 * We can't पढ़ो the WM8510 रेजिस्टर space when we are
 * using 2 wire क्रम device control, so we cache them instead.
 */
अटल स्थिर काष्ठा reg_शेष wm8510_reg_शेषs[] = अणु
	अणु  1, 0x0000 पूर्ण,
	अणु  2, 0x0000 पूर्ण,
	अणु  3, 0x0000 पूर्ण,
	अणु  4, 0x0050 पूर्ण,
	अणु  5, 0x0000 पूर्ण,
	अणु  6, 0x0140 पूर्ण,
	अणु  7, 0x0000 पूर्ण,
	अणु  8, 0x0000 पूर्ण,
	अणु  9, 0x0000 पूर्ण,
	अणु 10, 0x0000 पूर्ण,
	अणु 11, 0x00ff पूर्ण,
	अणु 12, 0x0000 पूर्ण,
	अणु 13, 0x0000 पूर्ण,
	अणु 14, 0x0100 पूर्ण,
	अणु 15, 0x00ff पूर्ण,
	अणु 16, 0x0000 पूर्ण,
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
	अणु 44, 0x0003 पूर्ण,
	अणु 45, 0x0010 पूर्ण,
	अणु 46, 0x0000 पूर्ण,
	अणु 47, 0x0000 पूर्ण,
	अणु 48, 0x0000 पूर्ण,
	अणु 49, 0x0002 पूर्ण,
	अणु 50, 0x0001 पूर्ण,
	अणु 51, 0x0000 पूर्ण,
	अणु 52, 0x0000 पूर्ण,
	अणु 53, 0x0000 पूर्ण,
	अणु 54, 0x0039 पूर्ण,
	अणु 55, 0x0000 पूर्ण,
	अणु 56, 0x0001 पूर्ण,
पूर्ण;

अटल bool wm8510_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8510_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#घोषणा WM8510_POWER1_BIASEN  0x08
#घोषणा WM8510_POWER1_BUFIOEN 0x10

#घोषणा wm8510_reset(c)	snd_soc_component_ग_लिखो(c, WM8510_RESET, 0)

/* codec निजी data */
काष्ठा wm8510_priv अणु
	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर अक्षर *wm8510_companding[] = अणु "Off", "NC", "u-law", "A-law" पूर्ण;
अटल स्थिर अक्षर *wm8510_deemp[] = अणु "None", "32kHz", "44.1kHz", "48kHz" पूर्ण;
अटल स्थिर अक्षर *wm8510_alc[] = अणु "ALC", "Limiter" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत wm8510_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(WM8510_COMP, 1, 4, wm8510_companding), /* adc */
	SOC_ENUM_SINGLE(WM8510_COMP, 3, 4, wm8510_companding), /* dac */
	SOC_ENUM_SINGLE(WM8510_DAC,  4, 4, wm8510_deemp),
	SOC_ENUM_SINGLE(WM8510_ALC3,  8, 2, wm8510_alc),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8510_snd_controls[] = अणु

SOC_SINGLE("Digital Loopback Switch", WM8510_COMP, 0, 1, 0),

SOC_ENUM("DAC Companding", wm8510_क्रमागत[1]),
SOC_ENUM("ADC Companding", wm8510_क्रमागत[0]),

SOC_ENUM("Playback De-emphasis", wm8510_क्रमागत[2]),
SOC_SINGLE("DAC Inversion Switch", WM8510_DAC, 0, 1, 0),

SOC_SINGLE("Master Playback Volume", WM8510_DACVOL, 0, 127, 0),

SOC_SINGLE("High Pass Filter Switch", WM8510_ADC, 8, 1, 0),
SOC_SINGLE("High Pass Cut Off", WM8510_ADC, 4, 7, 0),
SOC_SINGLE("ADC Inversion Switch", WM8510_COMP, 0, 1, 0),

SOC_SINGLE("Capture Volume", WM8510_ADCVOL,  0, 127, 0),

SOC_SINGLE("DAC Playback Limiter Switch", WM8510_DACLIM1,  8, 1, 0),
SOC_SINGLE("DAC Playback Limiter Decay", WM8510_DACLIM1,  4, 15, 0),
SOC_SINGLE("DAC Playback Limiter Attack", WM8510_DACLIM1,  0, 15, 0),

SOC_SINGLE("DAC Playback Limiter Threshold", WM8510_DACLIM2,  4, 7, 0),
SOC_SINGLE("DAC Playback Limiter Boost", WM8510_DACLIM2,  0, 15, 0),

SOC_SINGLE("ALC Enable Switch", WM8510_ALC1,  8, 1, 0),
SOC_SINGLE("ALC Capture Max Gain", WM8510_ALC1,  3, 7, 0),
SOC_SINGLE("ALC Capture Min Gain", WM8510_ALC1,  0, 7, 0),

SOC_SINGLE("ALC Capture ZC Switch", WM8510_ALC2,  8, 1, 0),
SOC_SINGLE("ALC Capture Hold", WM8510_ALC2,  4, 7, 0),
SOC_SINGLE("ALC Capture Target", WM8510_ALC2,  0, 15, 0),

SOC_ENUM("ALC Capture Mode", wm8510_क्रमागत[3]),
SOC_SINGLE("ALC Capture Decay", WM8510_ALC3,  4, 15, 0),
SOC_SINGLE("ALC Capture Attack", WM8510_ALC3,  0, 15, 0),

SOC_SINGLE("ALC Capture Noise Gate Switch", WM8510_NGATE,  3, 1, 0),
SOC_SINGLE("ALC Capture Noise Gate Threshold", WM8510_NGATE,  0, 7, 0),

SOC_SINGLE("Capture PGA ZC Switch", WM8510_INPPGA,  7, 1, 0),
SOC_SINGLE("Capture PGA Volume", WM8510_INPPGA,  0, 63, 0),

SOC_SINGLE("Speaker Playback ZC Switch", WM8510_SPKVOL,  7, 1, 0),
SOC_SINGLE("Speaker Playback Switch", WM8510_SPKVOL,  6, 1, 1),
SOC_SINGLE("Speaker Playback Volume", WM8510_SPKVOL,  0, 63, 0),
SOC_SINGLE("Speaker Boost", WM8510_OUTPUT, 2, 1, 0),

SOC_SINGLE("Capture Boost(+20dB)", WM8510_ADCBOOST,  8, 1, 0),
SOC_SINGLE("Mono Playback Switch", WM8510_MONOMIX, 6, 1, 1),
पूर्ण;

/* Speaker Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8510_speaker_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Bypass Switch", WM8510_SPKMIX, 1, 1, 0),
SOC_DAPM_SINGLE("Aux Playback Switch", WM8510_SPKMIX, 5, 1, 0),
SOC_DAPM_SINGLE("PCM Playback Switch", WM8510_SPKMIX, 0, 1, 0),
पूर्ण;

/* Mono Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8510_mono_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Bypass Switch", WM8510_MONOMIX, 1, 1, 0),
SOC_DAPM_SINGLE("Aux Playback Switch", WM8510_MONOMIX, 2, 1, 0),
SOC_DAPM_SINGLE("PCM Playback Switch", WM8510_MONOMIX, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8510_boost_controls[] = अणु
SOC_DAPM_SINGLE("Mic PGA Switch", WM8510_INPPGA,  6, 1, 1),
SOC_DAPM_SINGLE("Aux Volume", WM8510_ADCBOOST, 0, 7, 0),
SOC_DAPM_SINGLE("Mic Volume", WM8510_ADCBOOST, 4, 7, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8510_micpga_controls[] = अणु
SOC_DAPM_SINGLE("MICP Switch", WM8510_INPUT, 0, 1, 0),
SOC_DAPM_SINGLE("MICN Switch", WM8510_INPUT, 1, 1, 0),
SOC_DAPM_SINGLE("AUX Switch", WM8510_INPUT, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8510_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MIXER("Speaker Mixer", WM8510_POWER3, 2, 0,
	&wm8510_speaker_mixer_controls[0],
	ARRAY_SIZE(wm8510_speaker_mixer_controls)),
SND_SOC_DAPM_MIXER("Mono Mixer", WM8510_POWER3, 3, 0,
	&wm8510_mono_mixer_controls[0],
	ARRAY_SIZE(wm8510_mono_mixer_controls)),
SND_SOC_DAPM_DAC("DAC", "HiFi Playback", WM8510_POWER3, 0, 0),
SND_SOC_DAPM_ADC("ADC", "HiFi Capture", WM8510_POWER2, 0, 0),
SND_SOC_DAPM_PGA("Aux Input", WM8510_POWER1, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("SpkN Out", WM8510_POWER3, 5, 0, शून्य, 0),
SND_SOC_DAPM_PGA("SpkP Out", WM8510_POWER3, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("Mono Out", WM8510_POWER3, 7, 0, शून्य, 0),

SND_SOC_DAPM_MIXER("Mic PGA", WM8510_POWER2, 2, 0,
		   &wm8510_micpga_controls[0],
		   ARRAY_SIZE(wm8510_micpga_controls)),
SND_SOC_DAPM_MIXER("Boost Mixer", WM8510_POWER2, 4, 0,
	&wm8510_boost_controls[0],
	ARRAY_SIZE(wm8510_boost_controls)),

SND_SOC_DAPM_MICBIAS("Mic Bias", WM8510_POWER1, 4, 0),

SND_SOC_DAPM_INPUT("MICN"),
SND_SOC_DAPM_INPUT("MICP"),
SND_SOC_DAPM_INPUT("AUX"),
SND_SOC_DAPM_OUTPUT("MONOOUT"),
SND_SOC_DAPM_OUTPUT("SPKOUTP"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8510_dapm_routes[] = अणु
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

	/* Microphone PGA */
	अणु"Mic PGA", "MICN Switch", "MICN"पूर्ण,
	अणु"Mic PGA", "MICP Switch", "MICP"पूर्ण,
	अणु "Mic PGA", "AUX Switch", "Aux Input" पूर्ण,

	/* Boost Mixer */
	अणु"Boost Mixer", "Mic PGA Switch", "Mic PGA"पूर्ण,
	अणु"Boost Mixer", "Mic Volume", "MICP"पूर्ण,
	अणु"Boost Mixer", "Aux Volume", "Aux Input"पूर्ण,

	अणु"ADC", शून्य, "Boost Mixer"पूर्ण,
पूर्ण;

काष्ठा pll_ अणु
	अचिन्हित पूर्णांक pre_भाग:4; /* prescale - 1 */
	अचिन्हित पूर्णांक n:4;
	अचिन्हित पूर्णांक k;
पूर्ण;

अटल काष्ठा pll_ pll_भाग;

/* The size in bits of the pll भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_PLL_SIZE ((1 << 24) * 10)

अटल व्योम pll_factors(अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक source)
अणु
	अचिन्हित दीर्घ दीर्घ Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;

	Nभाग = target / source;
	अगर (Nभाग < 6) अणु
		source >>= 1;
		pll_भाग.pre_भाग = 1;
		Nभाग = target / source;
	पूर्ण अन्यथा
		pll_भाग.pre_भाग = 0;

	अगर ((Nभाग < 6) || (Nभाग > 12))
		prपूर्णांकk(KERN_WARNING
			"WM8510 N value %u outwith recommended range!d\n",
			Nभाग);

	pll_भाग.n = Nभाग;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	/* Check अगर we need to round */
	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	K /= 10;

	pll_भाग.k = K;
पूर्ण

अटल पूर्णांक wm8510_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	अगर (freq_in == 0 || freq_out == 0) अणु
		/* Clock CODEC directly from MCLK */
		reg = snd_soc_component_पढ़ो(component, WM8510_CLOCK);
		snd_soc_component_ग_लिखो(component, WM8510_CLOCK, reg & 0x0ff);

		/* Turn off PLL */
		reg = snd_soc_component_पढ़ो(component, WM8510_POWER1);
		snd_soc_component_ग_लिखो(component, WM8510_POWER1, reg & 0x1df);
		वापस 0;
	पूर्ण

	pll_factors(freq_out*4, freq_in);

	snd_soc_component_ग_लिखो(component, WM8510_PLLN, (pll_भाग.pre_भाग << 4) | pll_भाग.n);
	snd_soc_component_ग_लिखो(component, WM8510_PLLK1, pll_भाग.k >> 18);
	snd_soc_component_ग_लिखो(component, WM8510_PLLK2, (pll_भाग.k >> 9) & 0x1ff);
	snd_soc_component_ग_लिखो(component, WM8510_PLLK3, pll_भाग.k & 0x1ff);
	reg = snd_soc_component_पढ़ो(component, WM8510_POWER1);
	snd_soc_component_ग_लिखो(component, WM8510_POWER1, reg | 0x020);

	/* Run CODEC from PLL instead of MCLK */
	reg = snd_soc_component_पढ़ो(component, WM8510_CLOCK);
	snd_soc_component_ग_लिखो(component, WM8510_CLOCK, reg | 0x100);

	वापस 0;
पूर्ण

/*
 * Configure WM8510 घड़ी भागiders.
 */
अटल पूर्णांक wm8510_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	चयन (भाग_id) अणु
	हाल WM8510_OPCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8510_GPIO) & 0x1cf;
		snd_soc_component_ग_लिखो(component, WM8510_GPIO, reg | भाग);
		अवरोध;
	हाल WM8510_MCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8510_CLOCK) & 0x11f;
		snd_soc_component_ग_लिखो(component, WM8510_CLOCK, reg | भाग);
		अवरोध;
	हाल WM8510_ADCCLK:
		reg = snd_soc_component_पढ़ो(component, WM8510_ADC) & 0x1f7;
		snd_soc_component_ग_लिखो(component, WM8510_ADC, reg | भाग);
		अवरोध;
	हाल WM8510_DACCLK:
		reg = snd_soc_component_पढ़ो(component, WM8510_DAC) & 0x1f7;
		snd_soc_component_ग_लिखो(component, WM8510_DAC, reg | भाग);
		अवरोध;
	हाल WM8510_BCLKDIV:
		reg = snd_soc_component_पढ़ो(component, WM8510_CLOCK) & 0x1e3;
		snd_soc_component_ग_लिखो(component, WM8510_CLOCK, reg | भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8510_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = 0;
	u16 clk = snd_soc_component_पढ़ो(component, WM8510_CLOCK) & 0x1fe;

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

	snd_soc_component_ग_लिखो(component, WM8510_IFACE, अगरace);
	snd_soc_component_ग_लिखो(component, WM8510_CLOCK, clk);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8510_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8510_IFACE) & 0x19f;
	u16 adn = snd_soc_component_पढ़ो(component, WM8510_ADD) & 0x1f1;

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

	snd_soc_component_ग_लिखो(component, WM8510_IFACE, अगरace);
	snd_soc_component_ग_लिखो(component, WM8510_ADD, adn);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8510_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8510_DAC) & 0xffbf;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8510_DAC, mute_reg | 0x40);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8510_DAC, mute_reg);
	वापस 0;
पूर्ण

/* liam need to make this lower घातer with dapm */
अटल पूर्णांक wm8510_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8510_priv *wm8510 = snd_soc_component_get_drvdata(component);
	u16 घातer1 = snd_soc_component_पढ़ो(component, WM8510_POWER1) & ~0x3;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		घातer1 |= 0x1;  /* VMID 50k */
		snd_soc_component_ग_लिखो(component, WM8510_POWER1, घातer1);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		घातer1 |= WM8510_POWER1_BIASEN | WM8510_POWER1_BUFIOEN;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_sync(wm8510->regmap);

			/* Initial cap अक्षरge at VMID 5k */
			snd_soc_component_ग_लिखो(component, WM8510_POWER1, घातer1 | 0x3);
			mdelay(100);
		पूर्ण

		घातer1 |= 0x2;  /* VMID 500k */
		snd_soc_component_ग_लिखो(component, WM8510_POWER1, घातer1);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, WM8510_POWER1, 0);
		snd_soc_component_ग_लिखो(component, WM8510_POWER2, 0);
		snd_soc_component_ग_लिखो(component, WM8510_POWER3, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8510_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
		SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)

#घोषणा WM8510_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8510_dai_ops = अणु
	.hw_params	= wm8510_pcm_hw_params,
	.mute_stream	= wm8510_mute,
	.set_fmt	= wm8510_set_dai_fmt,
	.set_clkभाग	= wm8510_set_dai_clkभाग,
	.set_pll	= wm8510_set_dai_pll,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8510_dai = अणु
	.name = "wm8510-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8510_RATES,
		.क्रमmats = WM8510_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8510_RATES,
		.क्रमmats = WM8510_FORMATS,पूर्ण,
	.ops = &wm8510_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक wm8510_probe(काष्ठा snd_soc_component *component)
अणु
	wm8510_reset(component);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8510 = अणु
	.probe			= wm8510_probe,
	.set_bias_level		= wm8510_set_bias_level,
	.controls		= wm8510_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8510_snd_controls),
	.dapm_widमाला_लो		= wm8510_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8510_dapm_widमाला_लो),
	.dapm_routes		= wm8510_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8510_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8510_of_match[] = अणु
	अणु .compatible = "wlf,wm8510" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8510_of_match);

अटल स्थिर काष्ठा regmap_config wm8510_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8510_MONOMIX,

	.reg_शेषs = wm8510_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8510_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8510_अस्थिर,
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8510_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8510_priv *wm8510;
	पूर्णांक ret;

	wm8510 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8510_priv),
			      GFP_KERNEL);
	अगर (wm8510 == शून्य)
		वापस -ENOMEM;

	wm8510->regmap = devm_regmap_init_spi(spi, &wm8510_regmap);
	अगर (IS_ERR(wm8510->regmap))
		वापस PTR_ERR(wm8510->regmap);

	spi_set_drvdata(spi, wm8510);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8510, &wm8510_dai, 1);

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8510_spi_driver = अणु
	.driver = अणु
		.name	= "wm8510",
		.of_match_table = wm8510_of_match,
	पूर्ण,
	.probe		= wm8510_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8510_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8510_priv *wm8510;
	पूर्णांक ret;

	wm8510 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8510_priv),
			      GFP_KERNEL);
	अगर (wm8510 == शून्य)
		वापस -ENOMEM;

	wm8510->regmap = devm_regmap_init_i2c(i2c, &wm8510_regmap);
	अगर (IS_ERR(wm8510->regmap))
		वापस PTR_ERR(wm8510->regmap);

	i2c_set_clientdata(i2c, wm8510);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8510, &wm8510_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8510_i2c_id[] = अणु
	अणु "wm8510", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8510_i2c_id);

अटल काष्ठा i2c_driver wm8510_i2c_driver = अणु
	.driver = अणु
		.name = "wm8510",
		.of_match_table = wm8510_of_match,
	पूर्ण,
	.probe =    wm8510_i2c_probe,
	.id_table = wm8510_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8510_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8510_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8510 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8510_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8510 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8510_modinit);

अटल व्योम __निकास wm8510_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8510_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8510_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8510_निकास);

MODULE_DESCRIPTION("ASoC WM8510 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
