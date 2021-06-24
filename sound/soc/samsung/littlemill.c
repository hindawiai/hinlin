<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Littlemill audio support
//
// Copyright 2011 Wolfson Microelectronics

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश "../codecs/wm8994.h"

अटल पूर्णांक sample_rate = 44100;

अटल पूर्णांक littlemill_set_bias_level(काष्ठा snd_soc_card *card,
					  काष्ठा snd_soc_dapm_context *dapm,
					  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *aअगर1_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	aअगर1_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (dapm->dev != aअगर1_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		/*
		 * If we've not alपढ़ोy घड़ीed things via hw_params()
		 * then करो so now, otherwise these are noops.
		 */
		अगर (dapm->bias_level == SND_SOC_BIAS_STANDBY) अणु
			ret = snd_soc_dai_set_pll(aअगर1_dai, WM8994_FLL1,
						  WM8994_FLL_SRC_MCLK2, 32768,
						  sample_rate * 512);
			अगर (ret < 0) अणु
				pr_err("Failed to start FLL: %d\n", ret);
				वापस ret;
			पूर्ण

			ret = snd_soc_dai_set_sysclk(aअगर1_dai,
						     WM8994_SYSCLK_FLL1,
						     sample_rate * 512,
						     SND_SOC_CLOCK_IN);
			अगर (ret < 0) अणु
				pr_err("Failed to set SYSCLK: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक littlemill_set_bias_level_post(काष्ठा snd_soc_card *card,
					       काष्ठा snd_soc_dapm_context *dapm,
					       क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *aअगर1_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	aअगर1_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (dapm->dev != aअगर1_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		ret = snd_soc_dai_set_sysclk(aअगर1_dai, WM8994_SYSCLK_MCLK2,
					     32768, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			pr_err("Failed to switch away from FLL1: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_pll(aअगर1_dai, WM8994_FLL1,
					  0, 0, 0);
		अगर (ret < 0) अणु
			pr_err("Failed to stop FLL1: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	dapm->bias_level = level;

	वापस 0;
पूर्ण

अटल पूर्णांक littlemill_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	sample_rate = params_rate(params);

	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1,
				  WM8994_FLL_SRC_MCLK2, 32768,
				  sample_rate * 512);
	अगर (ret < 0) अणु
		pr_err("Failed to start FLL: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai,
				     WM8994_SYSCLK_FLL1,
				     sample_rate * 512,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		pr_err("Failed to set SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops littlemill_ops = अणु
	.hw_params = littlemill_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_pcm_stream baseband_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.rate_min = 8000,
	.rate_max = 8000,
	.channels_min = 2,
	.channels_max = 2,
पूर्ण;

SND_SOC_DAILINK_DEFS(cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8994-codec", "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(baseband,
	DAILINK_COMP_ARRAY(COMP_CPU("wm8994-aif2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm1250-ev1.1-0027",
				      "wm1250-ev1")));

अटल काष्ठा snd_soc_dai_link littlemill_dai[] = अणु
	अणु
		.name = "CPU",
		.stream_name = "CPU",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ops = &littlemill_ops,
		SND_SOC_DAILINK_REG(cpu),
	पूर्ण,
	अणु
		.name = "Baseband",
		.stream_name = "Baseband",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		.params = &baseband_params,
		SND_SOC_DAILINK_REG(baseband),
	पूर्ण,
पूर्ण;

अटल पूर्णांक bbclk_ev(काष्ठा snd_soc_dapm_widget *w,
		    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *aअगर2_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[1]);
	aअगर2_dai = asoc_rtd_to_cpu(rtd, 0);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = snd_soc_dai_set_pll(aअगर2_dai, WM8994_FLL2,
					  WM8994_FLL_SRC_BCLK, 64 * 8000,
					  8000 * 256);
		अगर (ret < 0) अणु
			pr_err("Failed to start FLL: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_sysclk(aअगर2_dai, WM8994_SYSCLK_FLL2,
					     8000 * 256,
					     SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			pr_err("Failed to set SYSCLK: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		ret = snd_soc_dai_set_sysclk(aअगर2_dai, WM8994_SYSCLK_MCLK2,
					     32768, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			pr_err("Failed to switch away from FLL2: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_pll(aअगर2_dai, WM8994_FLL2,
					  0, 0, 0);
		अगर (ret < 0) अणु
			pr_err("Failed to stop FLL2: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	SOC_DAPM_PIN_SWITCH("WM1250 Input"),
	SOC_DAPM_PIN_SWITCH("WM1250 Output"),
पूर्ण;

अटल काष्ठा snd_soc_dapm_widget widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),

	SND_SOC_DAPM_MIC("AMIC", शून्य),
	SND_SOC_DAPM_MIC("DMIC", शून्य),

	SND_SOC_DAPM_SUPPLY_S("Baseband Clock", -1, SND_SOC_NOPM, 0, 0,
			      bbclk_ev,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल काष्ठा snd_soc_dapm_route audio_paths[] = अणु
	अणु "Headphone", शून्य, "HPOUT1L" पूर्ण,
	अणु "Headphone", शून्य, "HPOUT1R" पूर्ण,

	अणु "AMIC", शून्य, "MICBIAS1" पूर्ण,   /* Default क्रम AMICBIAS jumper */
	अणु "IN1LN", शून्य, "AMIC" पूर्ण,

	अणु "DMIC", शून्य, "MICBIAS2" पूर्ण,   /* Default क्रम DMICBIAS jumper */
	अणु "DMIC1DAT", शून्य, "DMIC" पूर्ण,
	अणु "DMIC2DAT", शून्य, "DMIC" पूर्ण,

	अणु "AIF2CLK", शून्य, "Baseband Clock" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack littlemill_headset;

अटल पूर्णांक littlemill_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *aअगर1_dai;
	काष्ठा snd_soc_dai *aअगर2_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	component = asoc_rtd_to_codec(rtd, 0)->component;
	aअगर1_dai = asoc_rtd_to_codec(rtd, 0);

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[1]);
	aअगर2_dai = asoc_rtd_to_cpu(rtd, 0);

	ret = snd_soc_dai_set_sysclk(aअगर1_dai, WM8994_SYSCLK_MCLK2,
				     32768, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_sysclk(aअगर2_dai, WM8994_SYSCLK_MCLK2,
				     32768, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_card_jack_new(card, "Headset",
				    SND_JACK_HEADSET | SND_JACK_MECHANICAL |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3 |
				    SND_JACK_BTN_4 | SND_JACK_BTN_5,
				    &littlemill_headset, शून्य, 0);
	अगर (ret)
		वापस ret;

	/* This will check device compatibility itself */
	wm8958_mic_detect(component, &littlemill_headset, शून्य, शून्य, शून्य, शून्य);

	/* As will this */
	wm8994_mic_detect(component, &littlemill_headset, 1);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_card littlemill = अणु
	.name = "Littlemill",
	.owner = THIS_MODULE,
	.dai_link = littlemill_dai,
	.num_links = ARRAY_SIZE(littlemill_dai),

	.set_bias_level = littlemill_set_bias_level,
	.set_bias_level_post = littlemill_set_bias_level_post,

	.controls = controls,
	.num_controls = ARRAY_SIZE(controls),
	.dapm_widमाला_लो = widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(widमाला_लो),
	.dapm_routes = audio_paths,
	.num_dapm_routes = ARRAY_SIZE(audio_paths),

	.late_probe = littlemill_late_probe,
पूर्ण;

अटल पूर्णांक littlemill_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &littlemill;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver littlemill_driver = अणु
	.driver = अणु
		.name = "littlemill",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = littlemill_probe,
पूर्ण;

module_platक्रमm_driver(littlemill_driver);

MODULE_DESCRIPTION("Littlemill audio support");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:littlemill");
