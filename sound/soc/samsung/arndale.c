<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2014, Inसंकेत Co., Ltd.
//
//  Author: Claude <claude@insginal.co.kr>

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "../codecs/wm8994.h"
#समावेश "i2s.h"

अटल पूर्णांक arndale_rt5631_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक rfs, ret;
	अचिन्हित दीर्घ rclk;

	rfs = 256;

	rclk = params_rate(params) * rfs;

	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_CDCLK,
					0, SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_RCLKSRC_0,
					0, SND_SOC_CLOCK_OUT);

	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, rclk, SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops arndale_rt5631_ops = अणु
	.hw_params = arndale_rt5631_hw_params,
पूर्ण;

अटल पूर्णांक arndale_wm1811_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक rfs, rclk;

	/* Ensure AIF1CLK is >= 3 MHz क्रम optimal perक्रमmance */
	अगर (params_width(params) == 24)
		rfs = 384;
	अन्यथा अगर (params_rate(params) == 8000 || params_rate(params) == 11025)
		rfs = 512;
	अन्यथा
		rfs = 256;

	rclk = params_rate(params) * rfs;

	/*
	 * We add 1 to the frequency value to ensure proper EPLL setting
	 * क्रम each audio sampling rate (see epll_24mhz_tbl in drivers/clk/
	 * samsung/clk-exynos5250.c क्रम list of available EPLL rates).
	 * The CODEC uses clk API and the value will be rounded hence the MCLK1
	 * घड़ी's frequency will still be exact multiple of the sample rate.
	 */
	वापस snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_MCLK1,
					rclk + 1, SND_SOC_CLOCK_IN);
पूर्ण

अटल काष्ठा snd_soc_ops arndale_wm1811_ops = अणु
	.hw_params = arndale_wm1811_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(rt5631_hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "rt5631-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link arndale_rt5631_dai[] = अणु
	अणु
		.name = "RT5631 HiFi",
		.stream_name = "Primary",
		.dai_fmt = SND_SOC_DAIFMT_I2S
			| SND_SOC_DAIFMT_NB_NF
			| SND_SOC_DAIFMT_CBS_CFS,
		.ops = &arndale_rt5631_ops,
		SND_SOC_DAILINK_REG(rt5631_hअगरi),
	पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(wm1811_hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link arndale_wm1811_dai[] = अणु
	अणु
		.name = "WM1811 HiFi",
		.stream_name = "Primary",
		.dai_fmt = SND_SOC_DAIFMT_I2S
			| SND_SOC_DAIFMT_NB_NF
			| SND_SOC_DAIFMT_CBM_CFM,
		.ops = &arndale_wm1811_ops,
		SND_SOC_DAILINK_REG(wm1811_hअगरi),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card arndale_rt5631 = अणु
	.name = "Arndale RT5631",
	.owner = THIS_MODULE,
	.dai_link = arndale_rt5631_dai,
	.num_links = ARRAY_SIZE(arndale_rt5631_dai),
पूर्ण;

अटल काष्ठा snd_soc_card arndale_wm1811 = अणु
	.name = "Arndale WM1811",
	.owner = THIS_MODULE,
	.dai_link = arndale_wm1811_dai,
	.num_links = ARRAY_SIZE(arndale_wm1811_dai),
पूर्ण;

अटल व्योम arndale_put_of_nodes(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक i;

	क्रम_each_card_prelinks(card, i, dai_link) अणु
		of_node_put(dai_link->cpus->of_node);
		of_node_put(dai_link->codecs->of_node);
	पूर्ण
पूर्ण

अटल पूर्णांक arndale_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक ret;

	card = (काष्ठा snd_soc_card *)of_device_get_match_data(&pdev->dev);
	card->dev = &pdev->dev;
	dai_link = card->dai_link;

	dai_link->cpus->of_node = of_parse_phandle(np, "samsung,audio-cpu", 0);
	अगर (!dai_link->cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'samsung,audio-cpu' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!dai_link->platक्रमms->name)
		dai_link->platक्रमms->of_node = dai_link->cpus->of_node;

	dai_link->codecs->of_node = of_parse_phandle(np, "samsung,audio-codec", 0);
	अगर (!dai_link->codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'samsung,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		जाओ err_put_of_nodes;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(card->dev, card);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"snd_soc_register_card() failed: %d\n", ret);
		जाओ err_put_of_nodes;
	पूर्ण
	वापस 0;

err_put_of_nodes:
	arndale_put_of_nodes(card);
	वापस ret;
पूर्ण

अटल पूर्णांक arndale_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	arndale_put_of_nodes(card);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id arndale_audio_of_match[] = अणु
	अणु .compatible = "samsung,arndale-rt5631",  .data = &arndale_rt5631 पूर्ण,
	अणु .compatible = "samsung,arndale-alc5631", .data = &arndale_rt5631 पूर्ण,
	अणु .compatible = "samsung,arndale-wm1811",  .data = &arndale_wm1811 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arndale_audio_of_match);

अटल काष्ठा platक्रमm_driver arndale_audio_driver = अणु
	.driver = अणु
		.name = "arndale-audio",
		.pm = &snd_soc_pm_ops,
		.of_match_table = arndale_audio_of_match,
	पूर्ण,
	.probe = arndale_audio_probe,
	.हटाओ = arndale_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(arndale_audio_driver);

MODULE_AUTHOR("Claude <claude@insignal.co.kr>");
MODULE_DESCRIPTION("ALSA SoC Driver for Arndale Board");
MODULE_LICENSE("GPL");
