<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ak4535.c  --  AK4535 ALSA Soc Audio driver
 *
 * Copyright 2005 Openedhand Ltd.
 *
 * Author: Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
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

#समावेश "ak4535.h"

/* codec निजी data */
काष्ठा ak4535_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक sysclk;
पूर्ण;

/*
 * ak4535 रेजिस्टर cache
 */
अटल स्थिर काष्ठा reg_शेष ak4535_reg_शेषs[] = अणु
	अणु 0, 0x00 पूर्ण,
	अणु 1, 0x80 पूर्ण,
	अणु 2, 0x00 पूर्ण,
	अणु 3, 0x03 पूर्ण,
	अणु 4, 0x02 पूर्ण,
	अणु 5, 0x00 पूर्ण,
	अणु 6, 0x11 पूर्ण,
	अणु 7, 0x01 पूर्ण,
	अणु 8, 0x00 पूर्ण,
	अणु 9, 0x40 पूर्ण,
	अणु 10, 0x36 पूर्ण,
	अणु 11, 0x10 पूर्ण,
	अणु 12, 0x00 पूर्ण,
	अणु 13, 0x00 पूर्ण,
	अणु 14, 0x57 पूर्ण,
पूर्ण;

अटल bool ak4535_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AK4535_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *ak4535_mono_gain[] = अणु"+6dB", "-17dB"पूर्ण;
अटल स्थिर अक्षर *ak4535_mono_out[] = अणु"(L + R)/2", "Hi-Z"पूर्ण;
अटल स्थिर अक्षर *ak4535_hp_out[] = अणु"Stereo", "Mono"पूर्ण;
अटल स्थिर अक्षर *ak4535_deemp[] = अणु"44.1kHz", "Off", "48kHz", "32kHz"पूर्ण;
अटल स्थिर अक्षर *ak4535_mic_select[] = अणु"Internal", "External"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ak4535_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(AK4535_SIG1, 7, 2, ak4535_mono_gain),
	SOC_ENUM_SINGLE(AK4535_SIG1, 6, 2, ak4535_mono_out),
	SOC_ENUM_SINGLE(AK4535_MODE2, 2, 2, ak4535_hp_out),
	SOC_ENUM_SINGLE(AK4535_DAC, 0, 4, ak4535_deemp),
	SOC_ENUM_SINGLE(AK4535_MIC, 1, 2, ak4535_mic_select),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak4535_snd_controls[] = अणु
	SOC_SINGLE("ALC2 Switch", AK4535_SIG1, 1, 1, 0),
	SOC_ENUM("Mono 1 Output", ak4535_क्रमागत[1]),
	SOC_ENUM("Mono 1 Gain", ak4535_क्रमागत[0]),
	SOC_ENUM("Headphone Output", ak4535_क्रमागत[2]),
	SOC_ENUM("Playback Deemphasis", ak4535_क्रमागत[3]),
	SOC_SINGLE("Bass Volume", AK4535_DAC, 2, 3, 0),
	SOC_SINGLE("Mic Boost (+20dB) Switch", AK4535_MIC, 0, 1, 0),
	SOC_ENUM("Mic Select", ak4535_क्रमागत[4]),
	SOC_SINGLE("ALC Operation Time", AK4535_TIMER, 0, 3, 0),
	SOC_SINGLE("ALC Recovery Time", AK4535_TIMER, 2, 3, 0),
	SOC_SINGLE("ALC ZC Time", AK4535_TIMER, 4, 3, 0),
	SOC_SINGLE("ALC 1 Switch", AK4535_ALC1, 5, 1, 0),
	SOC_SINGLE("ALC 2 Switch", AK4535_ALC1, 6, 1, 0),
	SOC_SINGLE("ALC Volume", AK4535_ALC2, 0, 127, 0),
	SOC_SINGLE("Capture Volume", AK4535_PGA, 0, 127, 0),
	SOC_SINGLE("Left Playback Volume", AK4535_LATT, 0, 127, 1),
	SOC_SINGLE("Right Playback Volume", AK4535_RATT, 0, 127, 1),
	SOC_SINGLE("AUX Bypass Volume", AK4535_VOL, 0, 15, 0),
	SOC_SINGLE("Mic Sidetone Volume", AK4535_VOL, 4, 7, 0),
पूर्ण;

/* Mono 1 Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_mono1_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Mic Sidetone Switch", AK4535_SIG1, 4, 1, 0),
	SOC_DAPM_SINGLE("Mono Playback Switch", AK4535_SIG1, 5, 1, 0),
पूर्ण;

/* Stereo Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_stereo_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Mic Sidetone Switch", AK4535_SIG2, 4, 1, 0),
	SOC_DAPM_SINGLE("Playback Switch", AK4535_SIG2, 7, 1, 0),
	SOC_DAPM_SINGLE("Aux Bypass Switch", AK4535_SIG2, 5, 1, 0),
पूर्ण;

/* Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_input_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Mic Capture Switch", AK4535_MIC, 2, 1, 0),
	SOC_DAPM_SINGLE("Aux Capture Switch", AK4535_MIC, 5, 1, 0),
पूर्ण;

/* Input mux */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_input_mux_control =
	SOC_DAPM_ENUM("Input Select", ak4535_क्रमागत[4]);

/* HP L चयन */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_hpl_control =
	SOC_DAPM_SINGLE("Switch", AK4535_SIG2, 1, 1, 1);

/* HP R चयन */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_hpr_control =
	SOC_DAPM_SINGLE("Switch", AK4535_SIG2, 0, 1, 1);

/* mono 2 चयन */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_mono2_control =
	SOC_DAPM_SINGLE("Switch", AK4535_SIG1, 0, 1, 0);

/* Line out चयन */
अटल स्थिर काष्ठा snd_kcontrol_new ak4535_line_control =
	SOC_DAPM_SINGLE("Switch", AK4535_SIG2, 6, 1, 0);

/* ak4535 dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget ak4535_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIXER("Stereo Mixer", SND_SOC_NOPM, 0, 0,
		&ak4535_stereo_mixer_controls[0],
		ARRAY_SIZE(ak4535_stereo_mixer_controls)),
	SND_SOC_DAPM_MIXER("Mono1 Mixer", SND_SOC_NOPM, 0, 0,
		&ak4535_mono1_mixer_controls[0],
		ARRAY_SIZE(ak4535_mono1_mixer_controls)),
	SND_SOC_DAPM_MIXER("Input Mixer", SND_SOC_NOPM, 0, 0,
		&ak4535_input_mixer_controls[0],
		ARRAY_SIZE(ak4535_input_mixer_controls)),
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
		&ak4535_input_mux_control),
	SND_SOC_DAPM_DAC("DAC", "Playback", AK4535_PM2, 0, 0),
	SND_SOC_DAPM_SWITCH("Mono 2 Enable", SND_SOC_NOPM, 0, 0,
		&ak4535_mono2_control),
	/* speaker घातersave bit */
	SND_SOC_DAPM_PGA("Speaker Enable", AK4535_MODE2, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SWITCH("Line Out Enable", SND_SOC_NOPM, 0, 0,
		&ak4535_line_control),
	SND_SOC_DAPM_SWITCH("Left HP Enable", SND_SOC_NOPM, 0, 0,
		&ak4535_hpl_control),
	SND_SOC_DAPM_SWITCH("Right HP Enable", SND_SOC_NOPM, 0, 0,
		&ak4535_hpr_control),
	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("ROUT"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("SPP"),
	SND_SOC_DAPM_OUTPUT("SPN"),
	SND_SOC_DAPM_OUTPUT("MOUT1"),
	SND_SOC_DAPM_OUTPUT("MOUT2"),
	SND_SOC_DAPM_OUTPUT("MICOUT"),
	SND_SOC_DAPM_ADC("ADC", "Capture", AK4535_PM1, 0, 0),
	SND_SOC_DAPM_PGA("Spk Amp", AK4535_PM2, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HP R Amp", AK4535_PM2, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HP L Amp", AK4535_PM2, 2, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic", AK4535_PM1, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Line Out", AK4535_PM1, 4, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono Out", AK4535_PM1, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("AUX In", AK4535_PM1, 2, 0, शून्य, 0),

	SND_SOC_DAPM_MICBIAS("Mic Int Bias", AK4535_MIC, 3, 0),
	SND_SOC_DAPM_MICBIAS("Mic Ext Bias", AK4535_MIC, 4, 0),
	SND_SOC_DAPM_INPUT("MICIN"),
	SND_SOC_DAPM_INPUT("MICEXT"),
	SND_SOC_DAPM_INPUT("AUX"),
	SND_SOC_DAPM_INPUT("MIN"),
	SND_SOC_DAPM_INPUT("AIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4535_audio_map[] = अणु
	/*stereo mixer */
	अणु"Stereo Mixer", "Playback Switch", "DAC"पूर्ण,
	अणु"Stereo Mixer", "Mic Sidetone Switch", "Mic"पूर्ण,
	अणु"Stereo Mixer", "Aux Bypass Switch", "AUX In"पूर्ण,

	/* mono1 mixer */
	अणु"Mono1 Mixer", "Mic Sidetone Switch", "Mic"पूर्ण,
	अणु"Mono1 Mixer", "Mono Playback Switch", "DAC"पूर्ण,

	/* Mic */
	अणु"Mic", शून्य, "AIN"पूर्ण,
	अणु"Input Mux", "Internal", "Mic Int Bias"पूर्ण,
	अणु"Input Mux", "External", "Mic Ext Bias"पूर्ण,
	अणु"Mic Int Bias", शून्य, "MICIN"पूर्ण,
	अणु"Mic Ext Bias", शून्य, "MICEXT"पूर्ण,
	अणु"MICOUT", शून्य, "Input Mux"पूर्ण,

	/* line out */
	अणु"LOUT", शून्य, "Line Out Enable"पूर्ण,
	अणु"ROUT", शून्य, "Line Out Enable"पूर्ण,
	अणु"Line Out Enable", "Switch", "Line Out"पूर्ण,
	अणु"Line Out", शून्य, "Stereo Mixer"पूर्ण,

	/* mono1 out */
	अणु"MOUT1", शून्य, "Mono Out"पूर्ण,
	अणु"Mono Out", शून्य, "Mono1 Mixer"पूर्ण,

	/* left HP */
	अणु"HPL", शून्य, "Left HP Enable"पूर्ण,
	अणु"Left HP Enable", "Switch", "HP L Amp"पूर्ण,
	अणु"HP L Amp", शून्य, "Stereo Mixer"पूर्ण,

	/* right HP */
	अणु"HPR", शून्य, "Right HP Enable"पूर्ण,
	अणु"Right HP Enable", "Switch", "HP R Amp"पूर्ण,
	अणु"HP R Amp", शून्य, "Stereo Mixer"पूर्ण,

	/* speaker */
	अणु"SPP", शून्य, "Speaker Enable"पूर्ण,
	अणु"SPN", शून्य, "Speaker Enable"पूर्ण,
	अणु"Speaker Enable", "Switch", "Spk Amp"पूर्ण,
	अणु"Spk Amp", शून्य, "MIN"पूर्ण,

	/* mono 2 */
	अणु"MOUT2", शून्य, "Mono 2 Enable"पूर्ण,
	अणु"Mono 2 Enable", "Switch", "Stereo Mixer"पूर्ण,

	/* Aux In */
	अणु"Aux In", शून्य, "AUX"पूर्ण,

	/* ADC */
	अणु"ADC", शून्य, "Input Mixer"पूर्ण,
	अणु"Input Mixer", "Mic Capture Switch", "Mic"पूर्ण,
	अणु"Input Mixer", "Aux Capture Switch", "Aux In"पूर्ण,
पूर्ण;

अटल पूर्णांक ak4535_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा ak4535_priv *ak4535 = snd_soc_component_get_drvdata(component);

	ak4535->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक ak4535_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4535_priv *ak4535 = snd_soc_component_get_drvdata(component);
	u8 mode2 = snd_soc_component_पढ़ो(component, AK4535_MODE2) & ~(0x3 << 5);
	पूर्णांक rate = params_rate(params), fs = 256;

	अगर (rate)
		fs = ak4535->sysclk / rate;

	/* set fs */
	चयन (fs) अणु
	हाल 1024:
		mode2 |= (0x2 << 5);
		अवरोध;
	हाल 512:
		mode2 |= (0x1 << 5);
		अवरोध;
	हाल 256:
		अवरोध;
	पूर्ण

	/* set rate */
	snd_soc_component_ग_लिखो(component, AK4535_MODE2, mode2);
	वापस 0;
पूर्ण

अटल पूर्णांक ak4535_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 mode1 = 0;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		mode1 = 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		mode1 = 0x0001;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* use 32 fs क्रम BCLK to save घातer */
	mode1 |= 0x4;

	snd_soc_component_ग_लिखो(component, AK4535_MODE1, mode1);
	वापस 0;
पूर्ण

अटल पूर्णांक ak4535_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, AK4535_DAC);

	अगर (!mute)
		snd_soc_component_ग_लिखो(component, AK4535_DAC, mute_reg & ~0x20);
	अन्यथा
		snd_soc_component_ग_लिखो(component, AK4535_DAC, mute_reg | 0x20);
	वापस 0;
पूर्ण

अटल पूर्णांक ak4535_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, AK4535_DAC, 0x20, 0);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, AK4535_DAC, 0x20, 0x20);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, AK4535_PM1, 0x80, 0x80);
		snd_soc_component_update_bits(component, AK4535_PM2, 0x80, 0);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, AK4535_PM1, 0x80, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AK4535_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
		SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)

अटल स्थिर काष्ठा snd_soc_dai_ops ak4535_dai_ops = अणु
	.hw_params	= ak4535_hw_params,
	.set_fmt	= ak4535_set_dai_fmt,
	.mute_stream	= ak4535_mute,
	.set_sysclk	= ak4535_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4535_dai = अणु
	.name = "ak4535-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = AK4535_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = AK4535_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &ak4535_dai_ops,
पूर्ण;

अटल पूर्णांक ak4535_resume(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_cache_sync(component);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config ak4535_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = AK4535_STATUS,
	.अस्थिर_reg = ak4535_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = ak4535_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ak4535_reg_शेषs),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ak4535 = अणु
	.resume			= ak4535_resume,
	.set_bias_level		= ak4535_set_bias_level,
	.controls		= ak4535_snd_controls,
	.num_controls		= ARRAY_SIZE(ak4535_snd_controls),
	.dapm_widमाला_लो		= ak4535_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4535_dapm_widमाला_लो),
	.dapm_routes		= ak4535_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(ak4535_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ak4535_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ak4535_priv *ak4535;
	पूर्णांक ret;

	ak4535 = devm_kzalloc(&i2c->dev, माप(काष्ठा ak4535_priv),
			      GFP_KERNEL);
	अगर (ak4535 == शून्य)
		वापस -ENOMEM;

	ak4535->regmap = devm_regmap_init_i2c(i2c, &ak4535_regmap);
	अगर (IS_ERR(ak4535->regmap)) अणु
		ret = PTR_ERR(ak4535->regmap);
		dev_err(&i2c->dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, ak4535);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_ak4535, &ak4535_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ak4535_i2c_id[] = अणु
	अणु "ak4535", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak4535_i2c_id);

अटल काष्ठा i2c_driver ak4535_i2c_driver = अणु
	.driver = अणु
		.name = "ak4535",
	पूर्ण,
	.probe =    ak4535_i2c_probe,
	.id_table = ak4535_i2c_id,
पूर्ण;

module_i2c_driver(ak4535_i2c_driver);

MODULE_DESCRIPTION("Soc AK4535 driver");
MODULE_AUTHOR("Richard Purdie");
MODULE_LICENSE("GPL");
