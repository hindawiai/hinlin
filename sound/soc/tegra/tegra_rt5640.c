<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* tegra_rt5640.c - Tegra machine ASoC driver क्रम boards using RT5640 codec.
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

#समावेश "../codecs/rt5640.h"

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-snd-rt5640"

काष्ठा tegra_rt5640 अणु
	काष्ठा tegra_asoc_utils_data util_data;
	पूर्णांक gpio_hp_det;
	क्रमागत of_gpio_flags gpio_hp_det_flags;
पूर्ण;

अटल पूर्णांक tegra_rt5640_asoc_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_rt5640 *machine = snd_soc_card_get_drvdata(card);
	पूर्णांक srate, mclk;
	पूर्णांक err;

	srate = params_rate(params);
	mclk = 256 * srate;

	err = tegra_asoc_utils_set_rate(&machine->util_data, srate, mclk);
	अगर (err < 0) अणु
		dev_err(card->dev, "Can't configure clocks\n");
		वापस err;
	पूर्ण

	err = snd_soc_dai_set_sysclk(codec_dai, RT5640_SCLK_S_MCLK, mclk,
					SND_SOC_CLOCK_IN);
	अगर (err < 0) अणु
		dev_err(card->dev, "codec_dai clock not set\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops tegra_rt5640_ops = अणु
	.hw_params = tegra_rt5640_asoc_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_rt5640_hp_jack;

अटल काष्ठा snd_soc_jack_pin tegra_rt5640_hp_jack_pins[] = अणु
	अणु
		.pin = "Headphones",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio tegra_rt5640_hp_jack_gpio = अणु
	.name = "Headphone detection",
	.report = SND_JACK_HEADPHONE,
	.debounce_समय = 150,
	.invert = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra_rt5640_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_SPK("Speakers", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tegra_rt5640_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speakers"),
पूर्ण;

अटल पूर्णांक tegra_rt5640_asoc_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा tegra_rt5640 *machine = snd_soc_card_get_drvdata(rtd->card);

	snd_soc_card_jack_new(rtd->card, "Headphones", SND_JACK_HEADPHONE,
			      &tegra_rt5640_hp_jack, tegra_rt5640_hp_jack_pins,
			      ARRAY_SIZE(tegra_rt5640_hp_jack_pins));

	अगर (gpio_is_valid(machine->gpio_hp_det)) अणु
		tegra_rt5640_hp_jack_gpio.gpio = machine->gpio_hp_det;
		tegra_rt5640_hp_jack_gpio.invert =
			!!(machine->gpio_hp_det_flags & OF_GPIO_ACTIVE_LOW);
		snd_soc_jack_add_gpios(&tegra_rt5640_hp_jack,
						1,
						&tegra_rt5640_hp_jack_gpio);
	पूर्ण

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(aअगर1,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "rt5640-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tegra_rt5640_dai = अणु
	.name = "RT5640",
	.stream_name = "RT5640 PCM",
	.init = tegra_rt5640_asoc_init,
	.ops = &tegra_rt5640_ops,
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(aअगर1),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_tegra_rt5640 = अणु
	.name = "tegra-rt5640",
	.owner = THIS_MODULE,
	.dai_link = &tegra_rt5640_dai,
	.num_links = 1,
	.controls = tegra_rt5640_controls,
	.num_controls = ARRAY_SIZE(tegra_rt5640_controls),
	.dapm_widमाला_लो = tegra_rt5640_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra_rt5640_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_rt5640_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_tegra_rt5640;
	काष्ठा tegra_rt5640 *machine;
	पूर्णांक ret;

	machine = devm_kzalloc(&pdev->dev,
			माप(काष्ठा tegra_rt5640), GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	machine->gpio_hp_det = of_get_named_gpio_flags(
		np, "nvidia,hp-det-gpios", 0, &machine->gpio_hp_det_flags);
	अगर (machine->gpio_hp_det == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	अगर (ret)
		वापस ret;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	अगर (ret)
		वापस ret;

	tegra_rt5640_dai.codecs->of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	अगर (!tegra_rt5640_dai.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_rt5640_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	अगर (!tegra_rt5640_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_rt5640_dai.platक्रमms->of_node = tegra_rt5640_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "snd_soc_register_card failed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_rt5640_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-rt5640", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_rt5640_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = tegra_rt5640_of_match,
	पूर्ण,
	.probe = tegra_rt5640_probe,
पूर्ण;
module_platक्रमm_driver(tegra_rt5640_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra+RT5640 machine ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra_rt5640_of_match);
