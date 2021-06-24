<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra machine ASoC driver क्रम boards using a MAX90809 CODEC.
 *
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * Based on code copyright/by:
 *
 * Copyright (C) 2010-2012 - NVIDIA, Inc.
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.lauchpad.net>
 * (c) 2009, 2010 Nvidia Graphics Pvt. Ltd.
 * Copyright 2007 Wolfson Microelectronics PLC.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-snd-max98090"

काष्ठा tegra_max98090 अणु
	काष्ठा tegra_asoc_utils_data util_data;
	पूर्णांक gpio_hp_det;
	पूर्णांक gpio_mic_det;
पूर्ण;

अटल पूर्णांक tegra_max98090_asoc_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_max98090 *machine = snd_soc_card_get_drvdata(card);
	पूर्णांक srate, mclk;
	पूर्णांक err;

	srate = params_rate(params);
	चयन (srate) अणु
	हाल 8000:
	हाल 16000:
	हाल 24000:
	हाल 32000:
	हाल 48000:
	हाल 64000:
	हाल 96000:
		mclk = 12288000;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		mclk = 11289600;
		अवरोध;
	शेष:
		mclk = 12000000;
		अवरोध;
	पूर्ण

	err = tegra_asoc_utils_set_rate(&machine->util_data, srate, mclk);
	अगर (err < 0) अणु
		dev_err(card->dev, "Can't configure clocks\n");
		वापस err;
	पूर्ण

	err = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
					SND_SOC_CLOCK_IN);
	अगर (err < 0) अणु
		dev_err(card->dev, "codec_dai clock not set\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops tegra_max98090_ops = अणु
	.hw_params = tegra_max98090_asoc_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_max98090_hp_jack;

अटल काष्ठा snd_soc_jack_pin tegra_max98090_hp_jack_pins[] = अणु
	अणु
		.pin = "Headphones",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio tegra_max98090_hp_jack_gpio = अणु
	.name = "Headphone detection",
	.report = SND_JACK_HEADPHONE,
	.debounce_समय = 150,
	.invert = 1,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_max98090_mic_jack;

अटल काष्ठा snd_soc_jack_pin tegra_max98090_mic_jack_pins[] = अणु
	अणु
		.pin = "Mic Jack",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio tegra_max98090_mic_jack_gpio = अणु
	.name = "Mic detection",
	.report = SND_JACK_MICROPHONE,
	.debounce_समय = 150,
	.invert = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra_max98090_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_SPK("Speakers", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tegra_max98090_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("Speakers"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
पूर्ण;

अटल पूर्णांक tegra_max98090_asoc_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा tegra_max98090 *machine = snd_soc_card_get_drvdata(rtd->card);

	अगर (gpio_is_valid(machine->gpio_hp_det)) अणु
		snd_soc_card_jack_new(rtd->card, "Headphones",
				      SND_JACK_HEADPHONE,
				      &tegra_max98090_hp_jack,
				      tegra_max98090_hp_jack_pins,
				      ARRAY_SIZE(tegra_max98090_hp_jack_pins));

		tegra_max98090_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_jack_add_gpios(&tegra_max98090_hp_jack,
					1,
					&tegra_max98090_hp_jack_gpio);
	पूर्ण

	अगर (gpio_is_valid(machine->gpio_mic_det)) अणु
		snd_soc_card_jack_new(rtd->card, "Mic Jack",
				      SND_JACK_MICROPHONE,
				      &tegra_max98090_mic_jack,
				      tegra_max98090_mic_jack_pins,
				      ARRAY_SIZE(tegra_max98090_mic_jack_pins));

		tegra_max98090_mic_jack_gpio.gpio = machine->gpio_mic_det;
		snd_soc_jack_add_gpios(&tegra_max98090_mic_jack,
				       1,
				       &tegra_max98090_mic_jack_gpio);
	पूर्ण

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "HiFi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tegra_max98090_dai = अणु
	.name = "max98090",
	.stream_name = "max98090 PCM",
	.init = tegra_max98090_asoc_init,
	.ops = &tegra_max98090_ops,
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_tegra_max98090 = अणु
	.name = "tegra-max98090",
	.owner = THIS_MODULE,
	.dai_link = &tegra_max98090_dai,
	.num_links = 1,
	.controls = tegra_max98090_controls,
	.num_controls = ARRAY_SIZE(tegra_max98090_controls),
	.dapm_widमाला_लो = tegra_max98090_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra_max98090_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_max98090_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_tegra_max98090;
	काष्ठा tegra_max98090 *machine;
	पूर्णांक ret;

	machine = devm_kzalloc(&pdev->dev,
			माप(काष्ठा tegra_max98090), GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	machine->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	अगर (machine->gpio_hp_det == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	machine->gpio_mic_det =
			of_get_named_gpio(np, "nvidia,mic-det-gpios", 0);
	अगर (machine->gpio_mic_det == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	अगर (ret)
		वापस ret;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	अगर (ret)
		वापस ret;

	tegra_max98090_dai.codecs->of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	अगर (!tegra_max98090_dai.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_max98090_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	अगर (!tegra_max98090_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_max98090_dai.platक्रमms->of_node = tegra_max98090_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "snd_soc_register_card failed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_max98090_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-max98090", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_max98090_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = tegra_max98090_of_match,
	पूर्ण,
	.probe = tegra_max98090_probe,
पूर्ण;
module_platक्रमm_driver(tegra_max98090_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra max98090 machine ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra_max98090_of_match);
