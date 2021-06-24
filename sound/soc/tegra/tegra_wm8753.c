<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra_wm8753.c - Tegra machine ASoC driver क्रम boards using WM8753 codec.
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010-2012 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 *
 * (c) 2009, 2010 Nvidia Graphics Pvt. Ltd.
 *
 * Copyright 2007 Wolfson Microelectronics PLC.
 * Author: Graeme Gregory
 *         graeme.gregory@wolfsonmicro.com or linux@wolfsonmicro.com
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

#समावेश "../codecs/wm8753.h"

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-snd-wm8753"

काष्ठा tegra_wm8753 अणु
	काष्ठा tegra_asoc_utils_data util_data;
पूर्ण;

अटल पूर्णांक tegra_wm8753_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_wm8753 *machine = snd_soc_card_get_drvdata(card);
	पूर्णांक srate, mclk;
	पूर्णांक err;

	srate = params_rate(params);
	चयन (srate) अणु
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		mclk = 11289600;
		अवरोध;
	शेष:
		mclk = 12288000;
		अवरोध;
	पूर्ण

	err = tegra_asoc_utils_set_rate(&machine->util_data, srate, mclk);
	अगर (err < 0) अणु
		dev_err(card->dev, "Can't configure clocks\n");
		वापस err;
	पूर्ण

	err = snd_soc_dai_set_sysclk(codec_dai, WM8753_MCLK, mclk,
					SND_SOC_CLOCK_IN);
	अगर (err < 0) अणु
		dev_err(card->dev, "codec_dai clock not set\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops tegra_wm8753_ops = अणु
	.hw_params = tegra_wm8753_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra_wm8753_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
पूर्ण;

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8753-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tegra_wm8753_dai = अणु
	.name = "WM8753",
	.stream_name = "WM8753 PCM",
	.ops = &tegra_wm8753_ops,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_tegra_wm8753 = अणु
	.name = "tegra-wm8753",
	.owner = THIS_MODULE,
	.dai_link = &tegra_wm8753_dai,
	.num_links = 1,

	.dapm_widमाला_लो = tegra_wm8753_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra_wm8753_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_wm8753_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_tegra_wm8753;
	काष्ठा tegra_wm8753 *machine;
	पूर्णांक ret;

	machine = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra_wm8753),
			       GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	अगर (ret)
		वापस ret;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	अगर (ret)
		वापस ret;

	tegra_wm8753_dai.codecs->of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	अगर (!tegra_wm8753_dai.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_wm8753_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	अगर (!tegra_wm8753_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_wm8753_dai.platक्रमms->of_node = tegra_wm8753_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "snd_soc_register_card failed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_wm8753_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-wm8753", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_wm8753_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = tegra_wm8753_of_match,
	पूर्ण,
	.probe = tegra_wm8753_driver_probe,
पूर्ण;
module_platक्रमm_driver(tegra_wm8753_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra+WM8753 machine ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra_wm8753_of_match);
