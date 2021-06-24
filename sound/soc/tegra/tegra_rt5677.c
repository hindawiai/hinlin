<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* tegra_rt5677.c - Tegra machine ASoC driver क्रम boards using RT5677 codec.
 *
 * Copyright (c) 2014, The Chromium OS Authors.  All rights reserved.
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

#समावेश "../codecs/rt5677.h"

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-snd-rt5677"

काष्ठा tegra_rt5677 अणु
	काष्ठा tegra_asoc_utils_data util_data;
	पूर्णांक gpio_hp_det;
	पूर्णांक gpio_hp_en;
	पूर्णांक gpio_mic_present;
	पूर्णांक gpio_dmic_clk_en;
पूर्ण;

अटल पूर्णांक tegra_rt5677_asoc_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_rt5677 *machine = snd_soc_card_get_drvdata(card);
	पूर्णांक srate, mclk, err;

	srate = params_rate(params);
	mclk = 256 * srate;

	err = tegra_asoc_utils_set_rate(&machine->util_data, srate, mclk);
	अगर (err < 0) अणु
		dev_err(card->dev, "Can't configure clocks\n");
		वापस err;
	पूर्ण

	err = snd_soc_dai_set_sysclk(codec_dai, RT5677_SCLK_S_MCLK, mclk,
					SND_SOC_CLOCK_IN);
	अगर (err < 0) अणु
		dev_err(card->dev, "codec_dai clock not set\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_rt5677_event_hp(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tegra_rt5677 *machine = snd_soc_card_get_drvdata(card);

	अगर (!gpio_is_valid(machine->gpio_hp_en))
		वापस 0;

	gpio_set_value_cansleep(machine->gpio_hp_en,
		SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops tegra_rt5677_ops = अणु
	.hw_params = tegra_rt5677_asoc_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_rt5677_hp_jack;

अटल काष्ठा snd_soc_jack_pin tegra_rt5677_hp_jack_pins = अणु
	.pin = "Headphone",
	.mask = SND_JACK_HEADPHONE,
पूर्ण;
अटल काष्ठा snd_soc_jack_gpio tegra_rt5677_hp_jack_gpio = अणु
	.name = "Headphone detection",
	.report = SND_JACK_HEADPHONE,
	.debounce_समय = 150,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_rt5677_mic_jack;

अटल काष्ठा snd_soc_jack_pin tegra_rt5677_mic_jack_pins = अणु
	.pin = "Headset Mic",
	.mask = SND_JACK_MICROPHONE,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio tegra_rt5677_mic_jack_gpio = अणु
	.name = "Headset Mic detection",
	.report = SND_JACK_MICROPHONE,
	.debounce_समय = 150,
	.invert = 1
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra_rt5677_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_HP("Headphone", tegra_rt5677_event_hp),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Internal Mic 1", शून्य),
	SND_SOC_DAPM_MIC("Internal Mic 2", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tegra_rt5677_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Internal Mic 1"),
	SOC_DAPM_PIN_SWITCH("Internal Mic 2"),
पूर्ण;

अटल पूर्णांक tegra_rt5677_asoc_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा tegra_rt5677 *machine = snd_soc_card_get_drvdata(rtd->card);

	snd_soc_card_jack_new(rtd->card, "Headphone Jack", SND_JACK_HEADPHONE,
			      &tegra_rt5677_hp_jack,
			      &tegra_rt5677_hp_jack_pins, 1);

	अगर (gpio_is_valid(machine->gpio_hp_det)) अणु
		tegra_rt5677_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_jack_add_gpios(&tegra_rt5677_hp_jack, 1,
				&tegra_rt5677_hp_jack_gpio);
	पूर्ण


	snd_soc_card_jack_new(rtd->card, "Mic Jack", SND_JACK_MICROPHONE,
			      &tegra_rt5677_mic_jack,
			      &tegra_rt5677_mic_jack_pins, 1);

	अगर (gpio_is_valid(machine->gpio_mic_present)) अणु
		tegra_rt5677_mic_jack_gpio.gpio = machine->gpio_mic_present;
		snd_soc_jack_add_gpios(&tegra_rt5677_mic_jack, 1,
				&tegra_rt5677_mic_jack_gpio);
	पूर्ण

	snd_soc_dapm_क्रमce_enable_pin(&rtd->card->dapm, "MICBIAS1");

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "rt5677-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tegra_rt5677_dai = अणु
	.name = "RT5677",
	.stream_name = "RT5677 PCM",
	.init = tegra_rt5677_asoc_init,
	.ops = &tegra_rt5677_ops,
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_tegra_rt5677 = अणु
	.name = "tegra-rt5677",
	.owner = THIS_MODULE,
	.dai_link = &tegra_rt5677_dai,
	.num_links = 1,
	.controls = tegra_rt5677_controls,
	.num_controls = ARRAY_SIZE(tegra_rt5677_controls),
	.dapm_widमाला_लो = tegra_rt5677_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra_rt5677_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_rt5677_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_tegra_rt5677;
	काष्ठा tegra_rt5677 *machine;
	पूर्णांक ret;

	machine = devm_kzalloc(&pdev->dev,
			माप(काष्ठा tegra_rt5677), GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	machine->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	अगर (machine->gpio_hp_det == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	machine->gpio_mic_present = of_get_named_gpio(np,
			"nvidia,mic-present-gpios", 0);
	अगर (machine->gpio_mic_present == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	machine->gpio_hp_en = of_get_named_gpio(np, "nvidia,hp-en-gpios", 0);
	अगर (machine->gpio_hp_en == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(machine->gpio_hp_en)) अणु
		ret = devm_gpio_request_one(&pdev->dev, machine->gpio_hp_en,
				GPIOF_OUT_INIT_LOW, "hp_en");
		अगर (ret) अणु
			dev_err(card->dev, "cannot get hp_en gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	machine->gpio_dmic_clk_en = of_get_named_gpio(np,
		"nvidia,dmic-clk-en-gpios", 0);
	अगर (machine->gpio_dmic_clk_en == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(machine->gpio_dmic_clk_en)) अणु
		ret = devm_gpio_request_one(&pdev->dev,
				machine->gpio_dmic_clk_en,
				GPIOF_OUT_INIT_HIGH, "dmic_clk_en");
		अगर (ret) अणु
			dev_err(card->dev, "cannot get dmic_clk_en gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	अगर (ret)
		जाओ err;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	अगर (ret)
		जाओ err;

	tegra_rt5677_dai.codecs->of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	अगर (!tegra_rt5677_dai.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	tegra_rt5677_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	अगर (!tegra_rt5677_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		जाओ err_put_codec_of_node;
	पूर्ण
	tegra_rt5677_dai.platक्रमms->of_node = tegra_rt5677_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	अगर (ret)
		जाओ err_put_cpu_of_node;

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err_probe(&pdev->dev, ret,
			      "snd_soc_register_card failed\n");
		जाओ err_put_cpu_of_node;
	पूर्ण

	वापस 0;

err_put_cpu_of_node:
	of_node_put(tegra_rt5677_dai.cpus->of_node);
	tegra_rt5677_dai.cpus->of_node = शून्य;
	tegra_rt5677_dai.platक्रमms->of_node = शून्य;
err_put_codec_of_node:
	of_node_put(tegra_rt5677_dai.codecs->of_node);
	tegra_rt5677_dai.codecs->of_node = शून्य;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_rt5677_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_card(card);

	tegra_rt5677_dai.platक्रमms->of_node = शून्य;
	of_node_put(tegra_rt5677_dai.codecs->of_node);
	tegra_rt5677_dai.codecs->of_node = शून्य;
	of_node_put(tegra_rt5677_dai.cpus->of_node);
	tegra_rt5677_dai.cpus->of_node = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_rt5677_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-rt5677", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_rt5677_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = tegra_rt5677_of_match,
	पूर्ण,
	.probe = tegra_rt5677_probe,
	.हटाओ = tegra_rt5677_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_rt5677_driver);

MODULE_AUTHOR("Anatol Pomozov <anatol@google.com>");
MODULE_DESCRIPTION("Tegra+RT5677 machine ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra_rt5677_of_match);
