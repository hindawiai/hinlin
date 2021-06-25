<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm9705.c  --  ALSA Soc WM9705 codec support
 *
 * Copyright 2008 Ian Molton <spyro@f2s.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/wm97xx.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/ac97/codec.h>
#समावेश <sound/ac97/compat.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#घोषणा WM9705_VENDOR_ID 0x574d4c05
#घोषणा WM9705_VENDOR_ID_MASK 0xffffffff

काष्ठा wm9705_priv अणु
	काष्ठा snd_ac97 *ac97;
	काष्ठा wm97xx_platक्रमm_data *mfd_pdata;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm9705_reg_शेषs[] = अणु
	अणु 0x02, 0x8000 पूर्ण,
	अणु 0x04, 0x8000 पूर्ण,
	अणु 0x06, 0x8000 पूर्ण,
	अणु 0x0a, 0x8000 पूर्ण,
	अणु 0x0c, 0x8008 पूर्ण,
	अणु 0x0e, 0x8008 पूर्ण,
	अणु 0x10, 0x8808 पूर्ण,
	अणु 0x12, 0x8808 पूर्ण,
	अणु 0x14, 0x8808 पूर्ण,
	अणु 0x16, 0x8808 पूर्ण,
	अणु 0x18, 0x8808 पूर्ण,
	अणु 0x1a, 0x0000 पूर्ण,
	अणु 0x1c, 0x8000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x22, 0x0000 पूर्ण,
	अणु 0x26, 0x000f पूर्ण,
	अणु 0x28, 0x0605 पूर्ण,
	अणु 0x2a, 0x0000 पूर्ण,
	अणु 0x2c, 0xbb80 पूर्ण,
	अणु 0x32, 0xbb80 पूर्ण,
	अणु 0x34, 0x2000 पूर्ण,
	अणु 0x5a, 0x0000 पूर्ण,
	अणु 0x5c, 0x0000 पूर्ण,
	अणु 0x72, 0x0808 पूर्ण,
	अणु 0x74, 0x0000 पूर्ण,
	अणु 0x76, 0x0006 पूर्ण,
	अणु 0x78, 0x0000 पूर्ण,
	अणु 0x7a, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm9705_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x7e,
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = regmap_ac97_शेष_अस्थिर,

	.reg_शेषs = wm9705_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm9705_reg_शेषs),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm9705_snd_ac97_controls[] = अणु
	SOC_DOUBLE("Master Playback Volume", AC97_MASTER, 8, 0, 31, 1),
	SOC_SINGLE("Master Playback Switch", AC97_MASTER, 15, 1, 1),
	SOC_DOUBLE("Headphone Playback Volume", AC97_HEADPHONE, 8, 0, 31, 1),
	SOC_SINGLE("Headphone Playback Switch", AC97_HEADPHONE, 15, 1, 1),
	SOC_DOUBLE("PCM Playback Volume", AC97_PCM, 8, 0, 31, 1),
	SOC_SINGLE("PCM Playback Switch", AC97_PCM, 15, 1, 1),
	SOC_SINGLE("Mono Playback Volume", AC97_MASTER_MONO, 0, 31, 1),
	SOC_SINGLE("Mono Playback Switch", AC97_MASTER_MONO, 15, 1, 1),
	SOC_SINGLE("PCBeep Playback Volume", AC97_PC_BEEP, 1, 15, 1),
	SOC_SINGLE("Phone Playback Volume", AC97_PHONE, 0, 31, 1),
	SOC_DOUBLE("Line Playback Volume", AC97_LINE, 8, 0, 31, 1),
	SOC_DOUBLE("CD Playback Volume", AC97_CD, 8, 0, 31, 1),
	SOC_SINGLE("Mic Playback Volume", AC97_MIC, 0, 31, 1),
	SOC_SINGLE("Mic 20dB Boost Switch", AC97_MIC, 6, 1, 0),
	SOC_DOUBLE("Capture Volume", AC97_REC_GAIN, 8, 0, 15, 0),
	SOC_SINGLE("Capture Switch", AC97_REC_GAIN, 15, 1, 1),
पूर्ण;

अटल स्थिर अक्षर *wm9705_mic[] = अणु"Mic 1", "Mic 2"पूर्ण;
अटल स्थिर अक्षर *wm9705_rec_sel[] = अणु"Mic", "CD", "NC", "NC",
	"Line", "Stereo Mix", "Mono Mix", "Phone"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm9705_क्रमागत_mic,
			    AC97_GENERAL_PURPOSE, 8, wm9705_mic);
अटल SOC_ENUM_SINGLE_DECL(wm9705_क्रमागत_rec_l,
			    AC97_REC_SEL, 8, wm9705_rec_sel);
अटल SOC_ENUM_SINGLE_DECL(wm9705_क्रमागत_rec_r,
			    AC97_REC_SEL, 0, wm9705_rec_sel);

/* Headphone Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm9705_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("PCBeep Playback Switch", AC97_PC_BEEP, 15, 1, 1),
	SOC_DAPM_SINGLE("CD Playback Switch", AC97_CD, 15, 1, 1),
	SOC_DAPM_SINGLE("Mic Playback Switch", AC97_MIC, 15, 1, 1),
	SOC_DAPM_SINGLE("Phone Playback Switch", AC97_PHONE, 15, 1, 1),
	SOC_DAPM_SINGLE("Line Playback Switch", AC97_LINE, 15, 1, 1),
पूर्ण;

/* Mic source */
अटल स्थिर काष्ठा snd_kcontrol_new wm9705_mic_src_controls =
	SOC_DAPM_ENUM("Route", wm9705_क्रमागत_mic);

/* Capture source */
अटल स्थिर काष्ठा snd_kcontrol_new wm9705_capture_selectl_controls =
	SOC_DAPM_ENUM("Route", wm9705_क्रमागत_rec_l);
अटल स्थिर काष्ठा snd_kcontrol_new wm9705_capture_selectr_controls =
	SOC_DAPM_ENUM("Route", wm9705_क्रमागत_rec_r);

/* DAPM widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm9705_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Mic Source", SND_SOC_NOPM, 0, 0,
		&wm9705_mic_src_controls),
	SND_SOC_DAPM_MUX("Left Capture Source", SND_SOC_NOPM, 0, 0,
		&wm9705_capture_selectl_controls),
	SND_SOC_DAPM_MUX("Right Capture Source", SND_SOC_NOPM, 0, 0,
		&wm9705_capture_selectr_controls),
	SND_SOC_DAPM_DAC("Left DAC", "Left HiFi Playback",
		SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("Right DAC", "Right HiFi Playback",
		SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MIXER_NAMED_CTL("HP Mixer", SND_SOC_NOPM, 0, 0,
		&wm9705_hp_mixer_controls[0],
		ARRAY_SIZE(wm9705_hp_mixer_controls)),
	SND_SOC_DAPM_MIXER("Mono Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left HiFi Capture", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right HiFi Capture", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("Headphone PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Speaker PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Line PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Line out PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mono PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Phone PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("PCBEEP PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("CD PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ADC PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("HPOUTL"),
	SND_SOC_DAPM_OUTPUT("HPOUTR"),
	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_INPUT("PHONE"),
	SND_SOC_DAPM_INPUT("LINEINL"),
	SND_SOC_DAPM_INPUT("LINEINR"),
	SND_SOC_DAPM_INPUT("CDINL"),
	SND_SOC_DAPM_INPUT("CDINR"),
	SND_SOC_DAPM_INPUT("PCBEEP"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
पूर्ण;

/* Audio map
 * WM9705 has no चयनes to disable the route from the inमाला_दो to the HP mixer
 * so in order to prevent active inमाला_दो from क्रमcing the audio outमाला_दो to be
 * स्थिरantly enabled, we use the mutes on those inमाला_दो to simulate such
 * controls.
 */
अटल स्थिर काष्ठा snd_soc_dapm_route wm9705_audio_map[] = अणु
	/* HP mixer */
	अणु"HP Mixer", "PCBeep Playback Switch", "PCBEEP PGA"पूर्ण,
	अणु"HP Mixer", "CD Playback Switch", "CD PGA"पूर्ण,
	अणु"HP Mixer", "Mic Playback Switch", "Mic PGA"पूर्ण,
	अणु"HP Mixer", "Phone Playback Switch", "Phone PGA"पूर्ण,
	अणु"HP Mixer", "Line Playback Switch", "Line PGA"पूर्ण,
	अणु"HP Mixer", शून्य, "Left DAC"पूर्ण,
	अणु"HP Mixer", शून्य, "Right DAC"पूर्ण,

	/* mono mixer */
	अणु"Mono Mixer", शून्य, "HP Mixer"पूर्ण,

	/* outमाला_दो */
	अणु"Headphone PGA", शून्य, "HP Mixer"पूर्ण,
	अणु"HPOUTL", शून्य, "Headphone PGA"पूर्ण,
	अणु"HPOUTR", शून्य, "Headphone PGA"पूर्ण,
	अणु"Line out PGA", शून्य, "HP Mixer"पूर्ण,
	अणु"LOUT", शून्य, "Line out PGA"पूर्ण,
	अणु"ROUT", शून्य, "Line out PGA"पूर्ण,
	अणु"Mono PGA", शून्य, "Mono Mixer"पूर्ण,
	अणु"MONOOUT", शून्य, "Mono PGA"पूर्ण,

	/* inमाला_दो */
	अणु"CD PGA", शून्य, "CDINL"पूर्ण,
	अणु"CD PGA", शून्य, "CDINR"पूर्ण,
	अणु"Line PGA", शून्य, "LINEINL"पूर्ण,
	अणु"Line PGA", शून्य, "LINEINR"पूर्ण,
	अणु"Phone PGA", शून्य, "PHONE"पूर्ण,
	अणु"Mic Source", "Mic 1", "MIC1"पूर्ण,
	अणु"Mic Source", "Mic 2", "MIC2"पूर्ण,
	अणु"Mic PGA", शून्य, "Mic Source"पूर्ण,
	अणु"PCBEEP PGA", शून्य, "PCBEEP"पूर्ण,

	/* Left capture selector */
	अणु"Left Capture Source", "Mic", "Mic Source"पूर्ण,
	अणु"Left Capture Source", "CD", "CDINL"पूर्ण,
	अणु"Left Capture Source", "Line", "LINEINL"पूर्ण,
	अणु"Left Capture Source", "Stereo Mix", "HP Mixer"पूर्ण,
	अणु"Left Capture Source", "Mono Mix", "HP Mixer"पूर्ण,
	अणु"Left Capture Source", "Phone", "PHONE"पूर्ण,

	/* Right capture source */
	अणु"Right Capture Source", "Mic", "Mic Source"पूर्ण,
	अणु"Right Capture Source", "CD", "CDINR"पूर्ण,
	अणु"Right Capture Source", "Line", "LINEINR"पूर्ण,
	अणु"Right Capture Source", "Stereo Mix", "HP Mixer"पूर्ण,
	अणु"Right Capture Source", "Mono Mix", "HP Mixer"पूर्ण,
	अणु"Right Capture Source", "Phone", "PHONE"पूर्ण,

	अणु"ADC PGA", शून्य, "Left Capture Source"पूर्ण,
	अणु"ADC PGA", शून्य, "Right Capture Source"पूर्ण,

	/* ADC's */
	अणु"Left ADC",  शून्य, "ADC PGA"पूर्ण,
	अणु"Right ADC", शून्य, "ADC PGA"पूर्ण,
पूर्ण;

अटल पूर्णांक ac97_prepare(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक reg;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x1, 0x1);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = AC97_PCM_FRONT_DAC_RATE;
	अन्यथा
		reg = AC97_PCM_LR_ADC_RATE;

	वापस snd_soc_component_ग_लिखो(component, reg, substream->runसमय->rate);
पूर्ण

#घोषणा WM9705_AC97_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 | \
			SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | \
			SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
			SNDRV_PCM_RATE_48000)

अटल स्थिर काष्ठा snd_soc_dai_ops wm9705_dai_ops = अणु
	.prepare	= ac97_prepare,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm9705_dai[] = अणु
	अणु
		.name = "wm9705-hifi",
		.playback = अणु
			.stream_name = "HiFi Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM9705_AC97_RATES,
			.क्रमmats = SND_SOC_STD_AC97_FMTS,
		पूर्ण,
		.capture = अणु
			.stream_name = "HiFi Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM9705_AC97_RATES,
			.क्रमmats = SND_SOC_STD_AC97_FMTS,
		पूर्ण,
		.ops = &wm9705_dai_ops,
	पूर्ण,
	अणु
		.name = "wm9705-aux",
		.playback = अणु
			.stream_name = "Aux Playback",
			.channels_min = 1,
			.channels_max = 1,
			.rates = WM9705_AC97_RATES,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm9705_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	regcache_cache_bypass(component->regmap, true);
	snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0xffff);
	regcache_cache_bypass(component->regmap, false);

	वापस 0;
पूर्ण

अटल पूर्णांक wm9705_soc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9705_priv *wm9705 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = snd_ac97_reset(wm9705->ac97, true, WM9705_VENDOR_ID,
		WM9705_VENDOR_ID_MASK);
	अगर (ret < 0)
		वापस ret;

	snd_soc_component_cache_sync(component);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा wm9705_soc_suspend शून्य
#घोषणा wm9705_soc_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक wm9705_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9705_priv *wm9705 = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *regmap;

	अगर (wm9705->mfd_pdata) अणु
		wm9705->ac97 = wm9705->mfd_pdata->ac97;
		regmap = wm9705->mfd_pdata->regmap;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_SND_SOC_AC97_BUS)) अणु
		wm9705->ac97 = snd_soc_new_ac97_component(component, WM9705_VENDOR_ID,
						      WM9705_VENDOR_ID_MASK);
		अगर (IS_ERR(wm9705->ac97)) अणु
			dev_err(component->dev, "Failed to register AC97 codec\n");
			वापस PTR_ERR(wm9705->ac97);
		पूर्ण

		regmap = regmap_init_ac97(wm9705->ac97, &wm9705_regmap_config);
		अगर (IS_ERR(regmap)) अणु
			snd_soc_मुक्त_ac97_component(wm9705->ac97);
			वापस PTR_ERR(regmap);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENXIO;
	पूर्ण

	snd_soc_component_set_drvdata(component, wm9705->ac97);
	snd_soc_component_init_regmap(component, regmap);

	वापस 0;
पूर्ण

अटल व्योम wm9705_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm9705_priv *wm9705 = snd_soc_component_get_drvdata(component);

	अगर (IS_ENABLED(CONFIG_SND_SOC_AC97_BUS) && !wm9705->mfd_pdata) अणु
		snd_soc_component_निकास_regmap(component);
		snd_soc_मुक्त_ac97_component(wm9705->ac97);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm9705 = अणु
	.probe			= wm9705_soc_probe,
	.हटाओ			= wm9705_soc_हटाओ,
	.suspend		= wm9705_soc_suspend,
	.resume			= wm9705_soc_resume,
	.controls		= wm9705_snd_ac97_controls,
	.num_controls		= ARRAY_SIZE(wm9705_snd_ac97_controls),
	.dapm_widमाला_लो		= wm9705_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm9705_dapm_widमाला_लो),
	.dapm_routes		= wm9705_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(wm9705_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm9705_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm9705_priv *wm9705;

	wm9705 = devm_kzalloc(&pdev->dev, माप(*wm9705), GFP_KERNEL);
	अगर (wm9705 == शून्य)
		वापस -ENOMEM;

	wm9705->mfd_pdata = dev_get_platdata(&pdev->dev);
	platक्रमm_set_drvdata(pdev, wm9705);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm9705, wm9705_dai, ARRAY_SIZE(wm9705_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver wm9705_codec_driver = अणु
	.driver = अणु
			.name = "wm9705-codec",
	पूर्ण,

	.probe = wm9705_probe,
पूर्ण;

module_platक्रमm_driver(wm9705_codec_driver);

MODULE_DESCRIPTION("ASoC WM9705 driver");
MODULE_AUTHOR("Ian Molton");
MODULE_LICENSE("GPL v2");
