<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mt2701-wm8960.c  --  MT2701 WM8960 ALSA SoC machine driver
 *
 * Copyright (c) 2017 MediaTek Inc.
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश "mt2701-afe-common.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget mt2701_wm8960_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("AMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt2701_wm8960_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
पूर्ण;

अटल पूर्णांक mt2701_wm8960_be_ops_hw_params(काष्ठा snd_pcm_substream *substream,
					  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक mclk_rate;
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक भाग_mclk_over_bck = rate > 192000 ? 2 : 4;
	अचिन्हित पूर्णांक भाग_bck_over_lrck = 64;

	mclk_rate = rate * भाग_bck_over_lrck * भाग_mclk_over_bck;

	snd_soc_dai_set_sysclk(cpu_dai, 0, mclk_rate, SND_SOC_CLOCK_OUT);
	snd_soc_dai_set_sysclk(codec_dai, 0, mclk_rate, SND_SOC_CLOCK_IN);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops mt2701_wm8960_be_ops = अणु
	.hw_params = mt2701_wm8960_be_ops_hw_params
पूर्ण;

SND_SOC_DAILINK_DEFS(playback,
	DAILINK_COMP_ARRAY(COMP_CPU("PCMO0")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM0")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(codec,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S0")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8960-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link mt2701_wm8960_dai_links[] = अणु
	/* FE */
	अणु
		.name = "wm8960-playback",
		.stream_name = "wm8960-playback",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST,
			    SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback),
	पूर्ण,
	अणु
		.name = "wm8960-capture",
		.stream_name = "wm8960-capture",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST,
			    SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture),
	पूर्ण,
	/* BE */
	अणु
		.name = "wm8960-codec",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			| SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_wm8960_be_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(codec),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt2701_wm8960_card = अणु
	.name = "mt2701-wm8960",
	.owner = THIS_MODULE,
	.dai_link = mt2701_wm8960_dai_links,
	.num_links = ARRAY_SIZE(mt2701_wm8960_dai_links),
	.controls = mt2701_wm8960_controls,
	.num_controls = ARRAY_SIZE(mt2701_wm8960_controls),
	.dapm_widमाला_लो = mt2701_wm8960_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt2701_wm8960_widमाला_लो),
पूर्ण;

अटल पूर्णांक mt2701_wm8960_machine_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &mt2701_wm8960_card;
	काष्ठा device_node *platक्रमm_node, *codec_node;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक ret, i;

	platक्रमm_node = of_parse_phandle(pdev->dev.of_node,
					 "mediatek,platform", 0);
	अगर (!platक्रमm_node) अणु
		dev_err(&pdev->dev, "Property 'platform' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	क्रम_each_card_prelinks(card, i, dai_link) अणु
		अगर (dai_link->platक्रमms->name)
			जारी;
		dai_link->platक्रमms->of_node = platक्रमm_node;
	पूर्ण

	card->dev = &pdev->dev;

	codec_node = of_parse_phandle(pdev->dev.of_node,
				      "mediatek,audio-codec", 0);
	अगर (!codec_node) अणु
		dev_err(&pdev->dev,
			"Property 'audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	क्रम_each_card_prelinks(card, i, dai_link) अणु
		अगर (dai_link->codecs->name)
			जारी;
		dai_link->codecs->of_node = codec_node;
	पूर्ण

	ret = snd_soc_of_parse_audio_routing(card, "audio-routing");
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to parse audio-routing: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "%s snd_soc_register_card fail %d\n",
			__func__, ret);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mt2701_wm8960_machine_dt_match[] = अणु
	अणु.compatible = "mediatek,mt2701-wm8960-machine",पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mt2701_wm8960_machine = अणु
	.driver = अणु
		.name = "mt2701-wm8960",
#अगर_घोषित CONFIG_OF
		.of_match_table = mt2701_wm8960_machine_dt_match,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt2701_wm8960_machine_probe,
पूर्ण;

module_platक्रमm_driver(mt2701_wm8960_machine);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT2701 WM8960 ALSA SoC machine driver");
MODULE_AUTHOR("Ryder Lee <ryder.lee@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("mt2701 wm8960 soc card");

