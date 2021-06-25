<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mt8173-max98090.c  --  MT8173 MAX98090 ALSA SoC machine driver
 *
 * Copyright (c) 2015 MediaTek Inc.
 * Author: Koro Chen <koro.chen@mediatek.com>
 */

#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <linux/gpपन.स>
#समावेश "../../codecs/max98090.h"

अटल काष्ठा snd_soc_jack mt8173_max98090_jack;

अटल काष्ठा snd_soc_jack_pin mt8173_max98090_jack_pins[] = अणु
	अणु
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget mt8173_max98090_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8173_max98090_routes[] = अणु
	अणु"Speaker", शून्य, "SPKL"पूर्ण,
	अणु"Speaker", शून्य, "SPKR"पूर्ण,
	अणु"DMICL", शून्य, "Int Mic"पूर्ण,
	अणु"Headphone", शून्य, "HPL"पूर्ण,
	अणु"Headphone", शून्य, "HPR"पूर्ण,
	अणु"Headset Mic", शून्य, "MICBIAS"पूर्ण,
	अणु"IN34", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8173_max98090_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल पूर्णांक mt8173_max98090_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	वापस snd_soc_dai_set_sysclk(codec_dai, 0, params_rate(params) * 256,
				      SND_SOC_CLOCK_IN);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8173_max98090_ops = अणु
	.hw_params = mt8173_max98090_hw_params,
पूर्ण;

अटल पूर्णांक mt8173_max98090_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(runसमय, 0)->component;

	/* enable jack detection */
	ret = snd_soc_card_jack_new(card, "Headphone", SND_JACK_HEADPHONE,
				    &mt8173_max98090_jack,
				    mt8173_max98090_jack_pins,
				    ARRAY_SIZE(mt8173_max98090_jack_pins));
	अगर (ret) अणु
		dev_err(card->dev, "Can't create a new Jack %d\n", ret);
		वापस ret;
	पूर्ण

	वापस max98090_mic_detect(component, &mt8173_max98090_jack);
पूर्ण

SND_SOC_DAILINK_DEFS(playback,
	DAILINK_COMP_ARRAY(COMP_CPU("DL1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture,
	DAILINK_COMP_ARRAY(COMP_CPU("VUL")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "HiFi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

/* Digital audio पूर्णांकerface glue - connects codec <---> CPU */
अटल काष्ठा snd_soc_dai_link mt8173_max98090_dais[] = अणु
	/* Front End DAI links */
	अणु
		.name = "MAX98090 Playback",
		.stream_name = "MAX98090 Playback",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback),
	पूर्ण,
	अणु
		.name = "MAX98090 Capture",
		.stream_name = "MAX98090 Capture",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture),
	पूर्ण,
	/* Back End DAI links */
	अणु
		.name = "Codec",
		.no_pcm = 1,
		.init = mt8173_max98090_init,
		.ops = &mt8173_max98090_ops,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(hअगरi),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt8173_max98090_card = अणु
	.name = "mt8173-max98090",
	.owner = THIS_MODULE,
	.dai_link = mt8173_max98090_dais,
	.num_links = ARRAY_SIZE(mt8173_max98090_dais),
	.controls = mt8173_max98090_controls,
	.num_controls = ARRAY_SIZE(mt8173_max98090_controls),
	.dapm_widमाला_लो = mt8173_max98090_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt8173_max98090_widमाला_लो),
	.dapm_routes = mt8173_max98090_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8173_max98090_routes),
पूर्ण;

अटल पूर्णांक mt8173_max98090_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &mt8173_max98090_card;
	काष्ठा device_node *codec_node, *platक्रमm_node;
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
	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "%s snd_soc_register_card fail %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt8173_max98090_dt_match[] = अणु
	अणु .compatible = "mediatek,mt8173-max98090", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt8173_max98090_dt_match);

अटल काष्ठा platक्रमm_driver mt8173_max98090_driver = अणु
	.driver = अणु
		   .name = "mt8173-max98090",
		   .of_match_table = mt8173_max98090_dt_match,
#अगर_घोषित CONFIG_PM
		   .pm = &snd_soc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt8173_max98090_dev_probe,
पूर्ण;

module_platक्रमm_driver(mt8173_max98090_driver);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT8173 MAX98090 ALSA SoC machine driver");
MODULE_AUTHOR("Koro Chen <koro.chen@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mt8173-max98090");

