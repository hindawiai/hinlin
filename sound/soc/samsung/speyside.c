<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Speyside audio support
//
// Copyright 2011 Wolfson Microelectronics

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश "../codecs/wm8996.h"
#समावेश "../codecs/wm9081.h"

#घोषणा WM8996_HPSEL_GPIO 214
#घोषणा MCLK_AUDIO_RATE (512 * 48000)

अटल पूर्णांक speyside_set_bias_level(काष्ठा snd_soc_card *card,
				   काष्ठा snd_soc_dapm_context *dapm,
				   क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[1]);
	codec_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (dapm->dev != codec_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		ret = snd_soc_dai_set_sysclk(codec_dai, WM8996_SYSCLK_MCLK2,
					     32768, SND_SOC_CLOCK_IN);
		अगर (ret < 0)
			वापस ret;

		ret = snd_soc_dai_set_pll(codec_dai, WM8996_FLL_MCLK2,
					  0, 0, 0);
		अगर (ret < 0) अणु
			pr_err("Failed to stop FLL\n");
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक speyside_set_bias_level_post(काष्ठा snd_soc_card *card,
					काष्ठा snd_soc_dapm_context *dapm,
					क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[1]);
	codec_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (dapm->dev != codec_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (card->dapm.bias_level == SND_SOC_BIAS_STANDBY) अणु
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  WM8996_FLL_MCLK2,
						  32768, MCLK_AUDIO_RATE);
			अगर (ret < 0) अणु
				pr_err("Failed to start FLL\n");
				वापस ret;
			पूर्ण

			ret = snd_soc_dai_set_sysclk(codec_dai,
						     WM8996_SYSCLK_FLL,
						     MCLK_AUDIO_RATE,
						     SND_SOC_CLOCK_IN);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	card->dapm.bias_level = level;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_jack speyside_headset;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin speyside_headset_pins[] = अणु
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

/* Default the headphone selection to active high */
अटल पूर्णांक speyside_jack_polarity;

अटल पूर्णांक speyside_get_micbias(काष्ठा snd_soc_dapm_widget *source,
				काष्ठा snd_soc_dapm_widget *sink)
अणु
	अगर (speyside_jack_polarity && (म_भेद(source->name, "MICB1") == 0))
		वापस 1;
	अगर (!speyside_jack_polarity && (म_भेद(source->name, "MICB2") == 0))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम speyside_set_polarity(काष्ठा snd_soc_component *component,
				  पूर्णांक polarity)
अणु
	speyside_jack_polarity = !polarity;
	gpio_direction_output(WM8996_HPSEL_GPIO, speyside_jack_polarity);

	/* Re-run DAPM to make sure we're using the correct mic bias */
	snd_soc_dapm_sync(snd_soc_component_get_dapm(component));
पूर्ण

अटल पूर्णांक speyside_wm0010_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(dai, 0, MCLK_AUDIO_RATE, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक speyside_wm8996_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(dai, WM8996_SYSCLK_MCLK2, 32768, 0);
	अगर (ret < 0)
		वापस ret;

	ret = gpio_request(WM8996_HPSEL_GPIO, "HP_SEL");
	अगर (ret != 0)
		pr_err("Failed to request HP_SEL GPIO: %d\n", ret);
	gpio_direction_output(WM8996_HPSEL_GPIO, speyside_jack_polarity);

	ret = snd_soc_card_jack_new(rtd->card, "Headset", SND_JACK_LINEOUT |
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &speyside_headset, speyside_headset_pins,
				    ARRAY_SIZE(speyside_headset_pins));
	अगर (ret)
		वापस ret;

	wm8996_detect(component, &speyside_headset, speyside_set_polarity);

	वापस 0;
पूर्ण

अटल पूर्णांक speyside_late_probe(काष्ठा snd_soc_card *card)
अणु
	snd_soc_dapm_ignore_suspend(&card->dapm, "Headphone");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Headset Mic");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Main AMIC");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Main DMIC");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Main Speaker");
	snd_soc_dapm_ignore_suspend(&card->dapm, "WM1250 Output");
	snd_soc_dapm_ignore_suspend(&card->dapm, "WM1250 Input");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_pcm_stream dsp_codec_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
पूर्ण;

SND_SOC_DAILINK_DEFS(cpu_dsp,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("spi0.0", "wm0010-sdi1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(dsp_codec,
	DAILINK_COMP_ARRAY(COMP_CPU("wm0010-sdi2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8996.1-001a", "wm8996-aif1")));

SND_SOC_DAILINK_DEFS(baseband,
	DAILINK_COMP_ARRAY(COMP_CPU("wm8996-aif2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm1250-ev1.1-0027", "wm1250-ev1")));

अटल काष्ठा snd_soc_dai_link speyside_dai[] = अणु
	अणु
		.name = "CPU-DSP",
		.stream_name = "CPU-DSP",
		.init = speyside_wm0010_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAILINK_REG(cpu_dsp),
	पूर्ण,
	अणु
		.name = "DSP-CODEC",
		.stream_name = "DSP-CODEC",
		.init = speyside_wm8996_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.params = &dsp_codec_params,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(dsp_codec),
	पूर्ण,
	अणु
		.name = "Baseband",
		.stream_name = "Baseband",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(baseband),
	पूर्ण,
पूर्ण;

अटल पूर्णांक speyside_wm9081_init(काष्ठा snd_soc_component *component)
अणु
	/* At any समय the WM9081 is active it will have this घड़ी */
	वापस snd_soc_component_set_sysclk(component, WM9081_SYSCLK_MCLK, 0,
					MCLK_AUDIO_RATE, 0);
पूर्ण

अटल काष्ठा snd_soc_aux_dev speyside_aux_dev[] = अणु
	अणु
		.dlc = COMP_AUX("wm9081.1-006c"),
		.init = speyside_wm9081_init,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf speyside_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("wm9081.1-006c"),
		.name_prefix = "Sub",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Main Speaker"),
	SOC_DAPM_PIN_SWITCH("Main DMIC"),
	SOC_DAPM_PIN_SWITCH("Main AMIC"),
	SOC_DAPM_PIN_SWITCH("WM1250 Input"),
	SOC_DAPM_PIN_SWITCH("WM1250 Output"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
पूर्ण;

अटल काष्ठा snd_soc_dapm_widget widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),

	SND_SOC_DAPM_SPK("Main Speaker", शून्य),

	SND_SOC_DAPM_MIC("Main AMIC", शून्य),
	SND_SOC_DAPM_MIC("Main DMIC", शून्य),
पूर्ण;

अटल काष्ठा snd_soc_dapm_route audio_paths[] = अणु
	अणु "IN1RN", शून्य, "MICB1" पूर्ण,
	अणु "IN1RP", शून्य, "MICB1" पूर्ण,
	अणु "IN1RN", शून्य, "MICB2" पूर्ण,
	अणु "IN1RP", शून्य, "MICB2" पूर्ण,
	अणु "MICB1", शून्य, "Headset Mic", speyside_get_micbias पूर्ण,
	अणु "MICB2", शून्य, "Headset Mic", speyside_get_micbias पूर्ण,

	अणु "IN1LP", शून्य, "MICB2" पूर्ण,
	अणु "IN1RN", शून्य, "MICB1" पूर्ण,
	अणु "MICB2", शून्य, "Main AMIC" पूर्ण,

	अणु "DMIC1DAT", शून्य, "MICB1" पूर्ण,
	अणु "DMIC2DAT", शून्य, "MICB1" पूर्ण,
	अणु "MICB1", शून्य, "Main DMIC" पूर्ण,

	अणु "Headphone", शून्य, "HPOUT1L" पूर्ण,
	अणु "Headphone", शून्य, "HPOUT1R" पूर्ण,

	अणु "Sub IN1", शून्य, "HPOUT2L" पूर्ण,
	अणु "Sub IN2", शून्य, "HPOUT2R" पूर्ण,

	अणु "Main Speaker", शून्य, "Sub SPKN" पूर्ण,
	अणु "Main Speaker", शून्य, "Sub SPKP" पूर्ण,
	अणु "Main Speaker", शून्य, "SPKDAT" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card speyside = अणु
	.name = "Speyside",
	.owner = THIS_MODULE,
	.dai_link = speyside_dai,
	.num_links = ARRAY_SIZE(speyside_dai),
	.aux_dev = speyside_aux_dev,
	.num_aux_devs = ARRAY_SIZE(speyside_aux_dev),
	.codec_conf = speyside_codec_conf,
	.num_configs = ARRAY_SIZE(speyside_codec_conf),

	.set_bias_level = speyside_set_bias_level,
	.set_bias_level_post = speyside_set_bias_level_post,

	.controls = controls,
	.num_controls = ARRAY_SIZE(controls),
	.dapm_widमाला_लो = widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(widमाला_लो),
	.dapm_routes = audio_paths,
	.num_dapm_routes = ARRAY_SIZE(audio_paths),
	.fully_routed = true,

	.late_probe = speyside_late_probe,
पूर्ण;

अटल पूर्णांक speyside_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &speyside;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver speyside_driver = अणु
	.driver = अणु
		.name = "speyside",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = speyside_probe,
पूर्ण;

module_platक्रमm_driver(speyside_driver);

MODULE_DESCRIPTION("Speyside audio support");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:speyside");
