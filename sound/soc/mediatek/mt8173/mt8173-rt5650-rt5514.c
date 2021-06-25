<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mt8173-rt5650-rt5514.c  --  MT8173 machine driver with RT5650/5514 codecs
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Koro Chen <koro.chen@mediatek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश "../../codecs/rt5645.h"

#घोषणा MCLK_FOR_CODECS		12288000

अटल स्थिर काष्ठा snd_soc_dapm_widget mt8173_rt5650_rt5514_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8173_rt5650_rt5514_routes[] = अणु
	अणु"Speaker", शून्य, "SPOL"पूर्ण,
	अणु"Speaker", शून्य, "SPOR"पूर्ण,
	अणु"Sub DMIC1L", शून्य, "Int Mic"पूर्ण,
	अणु"Sub DMIC1R", शून्य, "Int Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN1N", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8173_rt5650_rt5514_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल पूर्णांक mt8173_rt5650_rt5514_hw_params(काष्ठा snd_pcm_substream *substream,
					  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक i, ret;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		/* pll from mclk 12.288M */
		ret = snd_soc_dai_set_pll(codec_dai, 0, 0, MCLK_FOR_CODECS,
					  params_rate(params) * 512);
		अगर (ret)
			वापस ret;

		/* sysclk from pll */
		ret = snd_soc_dai_set_sysclk(codec_dai, 1,
					     params_rate(params) * 512,
					     SND_SOC_CLOCK_IN);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8173_rt5650_rt5514_ops = अणु
	.hw_params = mt8173_rt5650_rt5514_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack mt8173_rt5650_rt5514_jack;

अटल पूर्णांक mt8173_rt5650_rt5514_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(runसमय, 0)->component;
	पूर्णांक ret;

	rt5645_sel_asrc_clk_src(component,
				RT5645_DA_STEREO_FILTER |
				RT5645_AD_STEREO_FILTER,
				RT5645_CLK_SEL_I2S1_ASRC);

	/* enable jack detection */
	ret = snd_soc_card_jack_new(card, "Headset Jack",
				    SND_JACK_HEADPHONE | SND_JACK_MICROPHONE |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &mt8173_rt5650_rt5514_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "Can't new Headset Jack %d\n", ret);
		वापस ret;
	पूर्ण

	वापस rt5645_set_jack_detect(component,
				      &mt8173_rt5650_rt5514_jack,
				      &mt8173_rt5650_rt5514_jack,
				      &mt8173_rt5650_rt5514_jack);
पूर्ण

क्रमागत अणु
	DAI_LINK_PLAYBACK,
	DAI_LINK_CAPTURE,
	DAI_LINK_CODEC_I2S,
पूर्ण;

SND_SOC_DAILINK_DEFS(playback,
	DAILINK_COMP_ARRAY(COMP_CPU("DL1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture,
	DAILINK_COMP_ARRAY(COMP_CPU("VUL")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(codec,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "rt5645-aif1"),
			   COMP_CODEC(शून्य, "rt5514-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

/* Digital audio पूर्णांकerface glue - connects codec <---> CPU */
अटल काष्ठा snd_soc_dai_link mt8173_rt5650_rt5514_dais[] = अणु
	/* Front End DAI links */
	[DAI_LINK_PLAYBACK] = अणु
		.name = "rt5650_rt5514 Playback",
		.stream_name = "rt5650_rt5514 Playback",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback),
	पूर्ण,
	[DAI_LINK_CAPTURE] = अणु
		.name = "rt5650_rt5514 Capture",
		.stream_name = "rt5650_rt5514 Capture",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture),
	पूर्ण,
	/* Back End DAI links */
	[DAI_LINK_CODEC_I2S] = अणु
		.name = "Codec",
		.no_pcm = 1,
		.init = mt8173_rt5650_rt5514_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &mt8173_rt5650_rt5514_ops,
		.ignore_pmकरोwn_समय = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(codec),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf mt8173_rt5650_rt5514_codec_conf[] = अणु
	अणु
		.name_prefix = "Sub",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt8173_rt5650_rt5514_card = अणु
	.name = "mtk-rt5650-rt5514",
	.owner = THIS_MODULE,
	.dai_link = mt8173_rt5650_rt5514_dais,
	.num_links = ARRAY_SIZE(mt8173_rt5650_rt5514_dais),
	.codec_conf = mt8173_rt5650_rt5514_codec_conf,
	.num_configs = ARRAY_SIZE(mt8173_rt5650_rt5514_codec_conf),
	.controls = mt8173_rt5650_rt5514_controls,
	.num_controls = ARRAY_SIZE(mt8173_rt5650_rt5514_controls),
	.dapm_widमाला_लो = mt8173_rt5650_rt5514_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt8173_rt5650_rt5514_widमाला_लो),
	.dapm_routes = mt8173_rt5650_rt5514_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8173_rt5650_rt5514_routes),
पूर्ण;

अटल पूर्णांक mt8173_rt5650_rt5514_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &mt8173_rt5650_rt5514_card;
	काष्ठा device_node *platक्रमm_node;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक i, ret;

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

	mt8173_rt5650_rt5514_dais[DAI_LINK_CODEC_I2S].codecs[0].of_node =
		of_parse_phandle(pdev->dev.of_node, "mediatek,audio-codec", 0);
	अगर (!mt8173_rt5650_rt5514_dais[DAI_LINK_CODEC_I2S].codecs[0].of_node) अणु
		dev_err(&pdev->dev,
			"Property 'audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	mt8173_rt5650_rt5514_dais[DAI_LINK_CODEC_I2S].codecs[1].of_node =
		of_parse_phandle(pdev->dev.of_node, "mediatek,audio-codec", 1);
	अगर (!mt8173_rt5650_rt5514_dais[DAI_LINK_CODEC_I2S].codecs[1].of_node) अणु
		dev_err(&pdev->dev,
			"Property 'audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	mt8173_rt5650_rt5514_codec_conf[0].dlc.of_node =
		mt8173_rt5650_rt5514_dais[DAI_LINK_CODEC_I2S].codecs[1].of_node;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "%s snd_soc_register_card fail %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt8173_rt5650_rt5514_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8173-rt5650-rt5514", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt8173_rt5650_rt5514_dt_match);

अटल काष्ठा platक्रमm_driver mt8173_rt5650_rt5514_driver = अणु
	.driver = अणु
		   .name = "mtk-rt5650-rt5514",
		   .of_match_table = mt8173_rt5650_rt5514_dt_match,
#अगर_घोषित CONFIG_PM
		   .pm = &snd_soc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt8173_rt5650_rt5514_dev_probe,
पूर्ण;

module_platक्रमm_driver(mt8173_rt5650_rt5514_driver);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT8173 RT5650 and RT5514 SoC machine driver");
MODULE_AUTHOR("Koro Chen <koro.chen@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mtk-rt5650-rt5514");

