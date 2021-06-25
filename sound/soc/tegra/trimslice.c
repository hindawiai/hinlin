<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * trimslice.c - TrimSlice machine ASoC driver
 *
 * Copyright (C) 2011 - CompuLab, Ltd.
 * Author: Mike Rapoport <mike@compulab.co.il>
 *
 * Based on code copyright/by:
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010-2011 - NVIDIA, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "../codecs/tlv320aic23.h"

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-snd-trimslice"

काष्ठा tegra_trimslice अणु
	काष्ठा tegra_asoc_utils_data util_data;
पूर्ण;

अटल पूर्णांक trimslice_asoc_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_trimslice *trimslice = snd_soc_card_get_drvdata(card);
	पूर्णांक srate, mclk;
	पूर्णांक err;

	srate = params_rate(params);
	mclk = 128 * srate;

	err = tegra_asoc_utils_set_rate(&trimslice->util_data, srate, mclk);
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

अटल स्थिर काष्ठा snd_soc_ops trimslice_asoc_ops = अणु
	.hw_params = trimslice_asoc_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget trimslice_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Line Out", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route trimslice_audio_map[] = अणु
	अणु"Line Out", शून्य, "LOUT"पूर्ण,
	अणु"Line Out", शून्य, "ROUT"पूर्ण,

	अणु"LLINEIN", शून्य, "Line In"पूर्ण,
	अणु"RLINEIN", शून्य, "Line In"पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(single_dsp,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "tlv320aic23-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link trimslice_tlv320aic23_dai = अणु
	.name = "TLV320AIC23",
	.stream_name = "AIC23",
	.ops = &trimslice_asoc_ops,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(single_dsp),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_trimslice = अणु
	.name = "tegra-trimslice",
	.owner = THIS_MODULE,
	.dai_link = &trimslice_tlv320aic23_dai,
	.num_links = 1,

	.dapm_widमाला_लो = trimslice_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(trimslice_dapm_widमाला_लो),
	.dapm_routes = trimslice_audio_map,
	.num_dapm_routes = ARRAY_SIZE(trimslice_audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_snd_trimslice_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_trimslice;
	काष्ठा tegra_trimslice *trimslice;
	पूर्णांक ret;

	trimslice = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra_trimslice),
				 GFP_KERNEL);
	अगर (!trimslice)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, trimslice);

	trimslice_tlv320aic23_dai.codecs->of_node = of_parse_phandle(np,
			"nvidia,audio-codec", 0);
	अगर (!trimslice_tlv320aic23_dai.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	trimslice_tlv320aic23_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	अगर (!trimslice_tlv320aic23_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	trimslice_tlv320aic23_dai.platक्रमms->of_node =
			trimslice_tlv320aic23_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&trimslice->util_data, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "snd_soc_register_card failed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id trimslice_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-trimslice", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, trimslice_of_match);

अटल काष्ठा platक्रमm_driver tegra_snd_trimslice_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = trimslice_of_match,
	पूर्ण,
	.probe = tegra_snd_trimslice_probe,
पूर्ण;
module_platक्रमm_driver(tegra_snd_trimslice_driver);

MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_DESCRIPTION("Trimslice machine ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
