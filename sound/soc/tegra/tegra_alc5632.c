<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* tegra_alc5632.c  --  Toshiba AC100(PAZ00) machine ASoC driver
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.lauchpad.net>
 * Copyright (C) 2012 - NVIDIA, Inc.
 *
 * Authors:  Leon Romanovsky <leon@leon.nu>
 *           Andrey Danin <danindrey@mail.ru>
 *           Marc Dietrich <marvin24@gmx.de>
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

#समावेश "../codecs/alc5632.h"

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-alc5632"

काष्ठा tegra_alc5632 अणु
	काष्ठा tegra_asoc_utils_data util_data;
	पूर्णांक gpio_hp_det;
पूर्ण;

अटल पूर्णांक tegra_alc5632_asoc_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_alc5632 *alc5632 = snd_soc_card_get_drvdata(card);
	पूर्णांक srate, mclk;
	पूर्णांक err;

	srate = params_rate(params);
	mclk = 512 * srate;

	err = tegra_asoc_utils_set_rate(&alc5632->util_data, srate, mclk);
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

अटल स्थिर काष्ठा snd_soc_ops tegra_alc5632_asoc_ops = अणु
	.hw_params = tegra_alc5632_asoc_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_alc5632_hs_jack;

अटल काष्ठा snd_soc_jack_pin tegra_alc5632_hs_jack_pins[] = अणु
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headset Stereophone",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio tegra_alc5632_hp_jack_gpio = अणु
	.name = "Headset detection",
	.report = SND_JACK_HEADSET,
	.debounce_समय = 150,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra_alc5632_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Int Spk", शून्य),
	SND_SOC_DAPM_HP("Headset Stereophone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Digital Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tegra_alc5632_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Int Spk"),
पूर्ण;

अटल पूर्णांक tegra_alc5632_asoc_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा tegra_alc5632 *machine = snd_soc_card_get_drvdata(rtd->card);

	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET,
				    &tegra_alc5632_hs_jack,
				    tegra_alc5632_hs_jack_pins,
				    ARRAY_SIZE(tegra_alc5632_hs_jack_pins));
	अगर (ret)
		वापस ret;

	अगर (gpio_is_valid(machine->gpio_hp_det)) अणु
		tegra_alc5632_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_jack_add_gpios(&tegra_alc5632_hs_jack,
						1,
						&tegra_alc5632_hp_jack_gpio);
	पूर्ण

	snd_soc_dapm_क्रमce_enable_pin(&rtd->card->dapm, "MICBIAS1");

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "alc5632-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tegra_alc5632_dai = अणु
	.name = "ALC5632",
	.stream_name = "ALC5632 PCM",
	.init = tegra_alc5632_asoc_init,
	.ops = &tegra_alc5632_asoc_ops,
	.dai_fmt = SND_SOC_DAIFMT_I2S
			   | SND_SOC_DAIFMT_NB_NF
			   | SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_tegra_alc5632 = अणु
	.name = "tegra-alc5632",
	.owner = THIS_MODULE,
	.dai_link = &tegra_alc5632_dai,
	.num_links = 1,
	.controls = tegra_alc5632_controls,
	.num_controls = ARRAY_SIZE(tegra_alc5632_controls),
	.dapm_widमाला_लो = tegra_alc5632_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra_alc5632_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_alc5632_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_tegra_alc5632;
	काष्ठा tegra_alc5632 *alc5632;
	पूर्णांक ret;

	alc5632 = devm_kzalloc(&pdev->dev,
			माप(काष्ठा tegra_alc5632), GFP_KERNEL);
	अगर (!alc5632)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, alc5632);

	alc5632->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	अगर (alc5632->gpio_hp_det == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	अगर (ret)
		जाओ err;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	अगर (ret)
		जाओ err;

	tegra_alc5632_dai.codecs->of_node = of_parse_phandle(
			pdev->dev.of_node, "nvidia,audio-codec", 0);

	अगर (!tegra_alc5632_dai.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	tegra_alc5632_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	अगर (!tegra_alc5632_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		जाओ err_put_codec_of_node;
	पूर्ण

	tegra_alc5632_dai.platक्रमms->of_node = tegra_alc5632_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&alc5632->util_data, &pdev->dev);
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
	of_node_put(tegra_alc5632_dai.cpus->of_node);
	tegra_alc5632_dai.cpus->of_node = शून्य;
	tegra_alc5632_dai.platक्रमms->of_node = शून्य;
err_put_codec_of_node:
	of_node_put(tegra_alc5632_dai.codecs->of_node);
	tegra_alc5632_dai.codecs->of_node = शून्य;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_alc5632_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_card(card);

	of_node_put(tegra_alc5632_dai.cpus->of_node);
	tegra_alc5632_dai.cpus->of_node = शून्य;
	tegra_alc5632_dai.platक्रमms->of_node = शून्य;
	of_node_put(tegra_alc5632_dai.codecs->of_node);
	tegra_alc5632_dai.codecs->of_node = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_alc5632_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-alc5632", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_alc5632_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = tegra_alc5632_of_match,
	पूर्ण,
	.probe = tegra_alc5632_probe,
	.हटाओ = tegra_alc5632_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_alc5632_driver);

MODULE_AUTHOR("Leon Romanovsky <leon@leon.nu>");
MODULE_DESCRIPTION("Tegra+ALC5632 machine ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra_alc5632_of_match);
