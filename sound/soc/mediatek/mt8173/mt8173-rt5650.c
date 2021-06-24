<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mt8173-rt5650.c  --  MT8173 machine driver with RT5650 codecs
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

क्रमागत mt8173_rt5650_mclk अणु
	MT8173_RT5650_MCLK_EXTERNAL = 0,
	MT8173_RT5650_MCLK_INTERNAL,
पूर्ण;

काष्ठा mt8173_rt5650_platक्रमm_data अणु
	क्रमागत mt8173_rt5650_mclk pll_from;
	/* 0 = बाह्यal oscillator; 1 = पूर्णांकernal source from mt8173 */
पूर्ण;

अटल काष्ठा mt8173_rt5650_platक्रमm_data mt8173_rt5650_priv = अणु
	.pll_from = MT8173_RT5650_MCLK_EXTERNAL,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mt8173_rt5650_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8173_rt5650_routes[] = अणु
	अणु"Speaker", शून्य, "SPOL"पूर्ण,
	अणु"Speaker", शून्य, "SPOR"पूर्ण,
	अणु"DMIC L1", शून्य, "Int Mic"पूर्ण,
	अणु"DMIC R1", शून्य, "Int Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN1N", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8173_rt5650_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल पूर्णांक mt8173_rt5650_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	अचिन्हित पूर्णांक mclk_घड़ी;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक i, ret;

	चयन (mt8173_rt5650_priv.pll_from) अणु
	हाल MT8173_RT5650_MCLK_EXTERNAL:
		/* mclk = 12.288M */
		mclk_घड़ी = MCLK_FOR_CODECS;
		अवरोध;
	हाल MT8173_RT5650_MCLK_INTERNAL:
		/* mclk = sampling rate*256 */
		mclk_घड़ी = params_rate(params) * 256;
		अवरोध;
	शेष:
		/* mclk = 12.288M */
		mclk_घड़ी = MCLK_FOR_CODECS;
		अवरोध;
	पूर्ण

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		/* pll from mclk */
		ret = snd_soc_dai_set_pll(codec_dai, 0, 0, mclk_घड़ी,
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

अटल स्थिर काष्ठा snd_soc_ops mt8173_rt5650_ops = अणु
	.hw_params = mt8173_rt5650_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack mt8173_rt5650_jack, mt8173_rt5650_hdmi_jack;

अटल पूर्णांक mt8173_rt5650_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(runसमय, 0)->component;
	स्थिर अक्षर *codec_capture_dai = asoc_rtd_to_codec(runसमय, 1)->name;
	पूर्णांक ret;

	rt5645_sel_asrc_clk_src(component,
				RT5645_DA_STEREO_FILTER,
				RT5645_CLK_SEL_I2S1_ASRC);

	अगर (!म_भेद(codec_capture_dai, "rt5645-aif1")) अणु
		rt5645_sel_asrc_clk_src(component,
					RT5645_AD_STEREO_FILTER,
					RT5645_CLK_SEL_I2S1_ASRC);
	पूर्ण अन्यथा अगर (!म_भेद(codec_capture_dai, "rt5645-aif2")) अणु
		rt5645_sel_asrc_clk_src(component,
					RT5645_AD_STEREO_FILTER,
					RT5645_CLK_SEL_I2S2_ASRC);
	पूर्ण अन्यथा अणु
		dev_warn(card->dev,
			 "Only one dai codec found in DTS, enabled rt5645 AD filter\n");
		rt5645_sel_asrc_clk_src(component,
					RT5645_AD_STEREO_FILTER,
					RT5645_CLK_SEL_I2S1_ASRC);
	पूर्ण

	/* enable jack detection */
	ret = snd_soc_card_jack_new(card, "Headset Jack",
				    SND_JACK_HEADPHONE | SND_JACK_MICROPHONE |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &mt8173_rt5650_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "Can't new Headset Jack %d\n", ret);
		वापस ret;
	पूर्ण

	वापस rt5645_set_jack_detect(component,
				      &mt8173_rt5650_jack,
				      &mt8173_rt5650_jack,
				      &mt8173_rt5650_jack);
पूर्ण

अटल पूर्णांक mt8173_rt5650_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;

	ret = snd_soc_card_jack_new(rtd->card, "HDMI Jack", SND_JACK_LINEOUT,
				    &mt8173_rt5650_hdmi_jack, शून्य, 0);
	अगर (ret)
		वापस ret;

	वापस snd_soc_component_set_jack(asoc_rtd_to_codec(rtd, 0)->component,
					  &mt8173_rt5650_hdmi_jack, शून्य);
पूर्ण

क्रमागत अणु
	DAI_LINK_PLAYBACK,
	DAI_LINK_CAPTURE,
	DAI_LINK_HDMI,
	DAI_LINK_CODEC_I2S,
	DAI_LINK_HDMI_I2S,
पूर्ण;

SND_SOC_DAILINK_DEFS(playback,
	DAILINK_COMP_ARRAY(COMP_CPU("DL1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture,
	DAILINK_COMP_ARRAY(COMP_CPU("VUL")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hdmi_pcm,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(codec,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "rt5645-aif1"), /* Playback */
			   COMP_CODEC(शून्य, "rt5645-aif1")),/* Capture */
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hdmi_be,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMIO")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "i2s-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

/* Digital audio पूर्णांकerface glue - connects codec <---> CPU */
अटल काष्ठा snd_soc_dai_link mt8173_rt5650_dais[] = अणु
	/* Front End DAI links */
	[DAI_LINK_PLAYBACK] = अणु
		.name = "rt5650 Playback",
		.stream_name = "rt5650 Playback",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback),
	पूर्ण,
	[DAI_LINK_CAPTURE] = अणु
		.name = "rt5650 Capture",
		.stream_name = "rt5650 Capture",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture),
	पूर्ण,
	[DAI_LINK_HDMI] = अणु
		.name = "HDMI",
		.stream_name = "HDMI PCM",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(hdmi_pcm),
	पूर्ण,
	/* Back End DAI links */
	[DAI_LINK_CODEC_I2S] = अणु
		.name = "Codec",
		.no_pcm = 1,
		.init = mt8173_rt5650_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &mt8173_rt5650_ops,
		.ignore_pmकरोwn_समय = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(codec),
	पूर्ण,
	[DAI_LINK_HDMI_I2S] = अणु
		.name = "HDMI BE",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.init = mt8173_rt5650_hdmi_init,
		SND_SOC_DAILINK_REG(hdmi_be),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt8173_rt5650_card = अणु
	.name = "mtk-rt5650",
	.owner = THIS_MODULE,
	.dai_link = mt8173_rt5650_dais,
	.num_links = ARRAY_SIZE(mt8173_rt5650_dais),
	.controls = mt8173_rt5650_controls,
	.num_controls = ARRAY_SIZE(mt8173_rt5650_controls),
	.dapm_widमाला_लो = mt8173_rt5650_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt8173_rt5650_widमाला_लो),
	.dapm_routes = mt8173_rt5650_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8173_rt5650_routes),
पूर्ण;

अटल पूर्णांक mt8173_rt5650_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &mt8173_rt5650_card;
	काष्ठा device_node *platक्रमm_node;
	काष्ठा device_node *np;
	स्थिर अक्षर *codec_capture_dai;
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

	mt8173_rt5650_dais[DAI_LINK_CODEC_I2S].codecs[0].of_node =
		of_parse_phandle(pdev->dev.of_node, "mediatek,audio-codec", 0);
	अगर (!mt8173_rt5650_dais[DAI_LINK_CODEC_I2S].codecs[0].of_node) अणु
		dev_err(&pdev->dev,
			"Property 'audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	mt8173_rt5650_dais[DAI_LINK_CODEC_I2S].codecs[1].of_node =
		mt8173_rt5650_dais[DAI_LINK_CODEC_I2S].codecs[0].of_node;

	np = of_get_child_by_name(pdev->dev.of_node, "codec-capture");
	अगर (np) अणु
		ret = snd_soc_of_get_dai_name(np, &codec_capture_dai);
		of_node_put(np);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"%s codec_capture_dai name fail %d\n",
				__func__, ret);
			वापस ret;
		पूर्ण
		mt8173_rt5650_dais[DAI_LINK_CODEC_I2S].codecs[1].dai_name =
			codec_capture_dai;
	पूर्ण

	अगर (device_property_present(&pdev->dev, "mediatek,mclk")) अणु
		ret = device_property_पढ़ो_u32(&pdev->dev,
					       "mediatek,mclk",
					       &mt8173_rt5650_priv.pll_from);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"%s snd_soc_register_card fail %d\n",
				__func__, ret);
		पूर्ण
	पूर्ण

	mt8173_rt5650_dais[DAI_LINK_HDMI_I2S].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node, "mediatek,audio-codec", 1);
	अगर (!mt8173_rt5650_dais[DAI_LINK_HDMI_I2S].codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "%s snd_soc_register_card fail %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt8173_rt5650_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8173-rt5650", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt8173_rt5650_dt_match);

अटल काष्ठा platक्रमm_driver mt8173_rt5650_driver = अणु
	.driver = अणु
		   .name = "mtk-rt5650",
		   .of_match_table = mt8173_rt5650_dt_match,
#अगर_घोषित CONFIG_PM
		   .pm = &snd_soc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt8173_rt5650_dev_probe,
पूर्ण;

module_platक्रमm_driver(mt8173_rt5650_driver);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT8173 RT5650 SoC machine driver");
MODULE_AUTHOR("Koro Chen <koro.chen@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mtk-rt5650");

