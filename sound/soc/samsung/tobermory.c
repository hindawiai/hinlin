<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Tobermory audio support
//
// Copyright 2011 Wolfson Microelectronics

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश "../codecs/wm8962.h"

अटल पूर्णांक sample_rate = 44100;

अटल पूर्णांक tobermory_set_bias_level(काष्ठा snd_soc_card *card,
					  काष्ठा snd_soc_dapm_context *dapm,
					  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	codec_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (dapm->dev != codec_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (dapm->bias_level == SND_SOC_BIAS_STANDBY) अणु
			ret = snd_soc_dai_set_pll(codec_dai, WM8962_FLL,
						  WM8962_FLL_MCLK, 32768,
						  sample_rate * 512);
			अगर (ret < 0)
				pr_err("Failed to start FLL: %d\n", ret);

			ret = snd_soc_dai_set_sysclk(codec_dai,
						     WM8962_SYSCLK_FLL,
						     sample_rate * 512,
						     SND_SOC_CLOCK_IN);
			अगर (ret < 0) अणु
				pr_err("Failed to set SYSCLK: %d\n", ret);
				snd_soc_dai_set_pll(codec_dai, WM8962_FLL,
						    0, 0, 0);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tobermory_set_bias_level_post(काष्ठा snd_soc_card *card,
					       काष्ठा snd_soc_dapm_context *dapm,
					       क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	codec_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (dapm->dev != codec_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		ret = snd_soc_dai_set_sysclk(codec_dai, WM8962_SYSCLK_MCLK,
					     32768, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			pr_err("Failed to switch away from FLL: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_pll(codec_dai, WM8962_FLL,
					  0, 0, 0);
		अगर (ret < 0) अणु
			pr_err("Failed to stop FLL: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	dapm->bias_level = level;

	वापस 0;
पूर्ण

अटल पूर्णांक tobermory_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	sample_rate = params_rate(params);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops tobermory_ops = अणु
	.hw_params = tobermory_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8962.1-001a", "wm8962")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

अटल काष्ठा snd_soc_dai_link tobermory_dai[] = अणु
	अणु
		.name = "CPU",
		.stream_name = "CPU",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ops = &tobermory_ops,
		SND_SOC_DAILINK_REG(cpu),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Main Speaker"),
	SOC_DAPM_PIN_SWITCH("DMIC"),
पूर्ण;

अटल काष्ठा snd_soc_dapm_widget widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),

	SND_SOC_DAPM_MIC("DMIC", शून्य),
	SND_SOC_DAPM_MIC("AMIC", शून्य),

	SND_SOC_DAPM_SPK("Main Speaker", शून्य),
पूर्ण;

अटल काष्ठा snd_soc_dapm_route audio_paths[] = अणु
	अणु "Headphone", शून्य, "HPOUTL" पूर्ण,
	अणु "Headphone", शून्य, "HPOUTR" पूर्ण,

	अणु "Main Speaker", शून्य, "SPKOUTL" पूर्ण,
	अणु "Main Speaker", शून्य, "SPKOUTR" पूर्ण,

	अणु "Headset Mic", शून्य, "MICBIAS" पूर्ण,
	अणु "IN4L", शून्य, "Headset Mic" पूर्ण,
	अणु "IN4R", शून्य, "Headset Mic" पूर्ण,

	अणु "AMIC", शून्य, "MICBIAS" पूर्ण,
	अणु "IN1L", शून्य, "AMIC" पूर्ण,
	अणु "IN1R", शून्य, "AMIC" पूर्ण,

	अणु "DMIC", शून्य, "MICBIAS" पूर्ण,
	अणु "DMICDAT", शून्य, "DMIC" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack tobermory_headset;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin tobermory_headset_pins[] = अणु
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headphone",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tobermory_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	component = asoc_rtd_to_codec(rtd, 0)->component;
	codec_dai = asoc_rtd_to_codec(rtd, 0);

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8962_SYSCLK_MCLK,
				     32768, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_card_jack_new(card, "Headset", SND_JACK_HEADSET |
				    SND_JACK_BTN_0, &tobermory_headset,
				    tobermory_headset_pins,
				    ARRAY_SIZE(tobermory_headset_pins));
	अगर (ret)
		वापस ret;

	wm8962_mic_detect(component, &tobermory_headset);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_card tobermory = अणु
	.name = "Tobermory",
	.owner = THIS_MODULE,
	.dai_link = tobermory_dai,
	.num_links = ARRAY_SIZE(tobermory_dai),

	.set_bias_level = tobermory_set_bias_level,
	.set_bias_level_post = tobermory_set_bias_level_post,

	.controls = controls,
	.num_controls = ARRAY_SIZE(controls),
	.dapm_widमाला_लो = widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(widमाला_लो),
	.dapm_routes = audio_paths,
	.num_dapm_routes = ARRAY_SIZE(audio_paths),
	.fully_routed = true,

	.late_probe = tobermory_late_probe,
पूर्ण;

अटल पूर्णांक tobermory_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &tobermory;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver tobermory_driver = अणु
	.driver = अणु
		.name = "tobermory",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = tobermory_probe,
पूर्ण;

module_platक्रमm_driver(tobermory_driver);

MODULE_DESCRIPTION("Tobermory audio support");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:tobermory");
