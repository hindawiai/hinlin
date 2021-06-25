<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt6797-mt6351.c  --  MT6797 MT6351 ALSA SoC machine driver
//
// Copyright (c) 2018 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश "mt6797-afe-common.h"

SND_SOC_DAILINK_DEFS(playback_1,
	DAILINK_COMP_ARRAY(COMP_CPU("DL1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback_2,
	DAILINK_COMP_ARRAY(COMP_CPU("DL2")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback_3,
	DAILINK_COMP_ARRAY(COMP_CPU("DL3")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture_1,
	DAILINK_COMP_ARRAY(COMP_CPU("UL1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture_2,
	DAILINK_COMP_ARRAY(COMP_CPU("UL2")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture_3,
	DAILINK_COMP_ARRAY(COMP_CPU("UL3")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture_mono_1,
	DAILINK_COMP_ARRAY(COMP_CPU("UL_MONO_1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hostless_lpbk,
	DAILINK_COMP_ARRAY(COMP_CPU("Hostless LPBK DAI")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hostless_speech,
	DAILINK_COMP_ARRAY(COMP_CPU("Hostless Speech DAI")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(primary_codec,
	DAILINK_COMP_ARRAY(COMP_CPU("ADDA")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "mt6351-snd-codec-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(pcm1,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM 1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(pcm2,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM 2")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link mt6797_mt6351_dai_links[] = अणु
	/* FE */
	अणु
		.name = "Playback_1",
		.stream_name = "Playback_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback_1),
	पूर्ण,
	अणु
		.name = "Playback_2",
		.stream_name = "Playback_2",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback_2),
	पूर्ण,
	अणु
		.name = "Playback_3",
		.stream_name = "Playback_3",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback_3),
	पूर्ण,
	अणु
		.name = "Capture_1",
		.stream_name = "Capture_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_1),
	पूर्ण,
	अणु
		.name = "Capture_2",
		.stream_name = "Capture_2",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_2),
	पूर्ण,
	अणु
		.name = "Capture_3",
		.stream_name = "Capture_3",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_3),
	पूर्ण,
	अणु
		.name = "Capture_Mono_1",
		.stream_name = "Capture_Mono_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_mono_1),
	पूर्ण,
	अणु
		.name = "Hostless_LPBK",
		.stream_name = "Hostless_LPBK",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(hostless_lpbk),
	पूर्ण,
	अणु
		.name = "Hostless_Speech",
		.stream_name = "Hostless_Speech",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(hostless_speech),
	पूर्ण,
	/* BE */
	अणु
		.name = "Primary Codec",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(primary_codec),
	पूर्ण,
	अणु
		.name = "PCM 1",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(pcm1),
	पूर्ण,
	अणु
		.name = "PCM 2",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(pcm2),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt6797_mt6351_card = अणु
	.name = "mt6797-mt6351",
	.owner = THIS_MODULE,
	.dai_link = mt6797_mt6351_dai_links,
	.num_links = ARRAY_SIZE(mt6797_mt6351_dai_links),
पूर्ण;

अटल पूर्णांक mt6797_mt6351_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &mt6797_mt6351_card;
	काष्ठा device_node *platक्रमm_node, *codec_node;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक ret, i;

	card->dev = &pdev->dev;

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

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "%s snd_soc_register_card fail %d\n",
			__func__, ret);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mt6797_mt6351_dt_match[] = अणु
	अणु.compatible = "mediatek,mt6797-mt6351-sound",पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mt6797_mt6351_driver = अणु
	.driver = अणु
		.name = "mt6797-mt6351",
#अगर_घोषित CONFIG_OF
		.of_match_table = mt6797_mt6351_dt_match,
#पूर्ण_अगर
	पूर्ण,
	.probe = mt6797_mt6351_dev_probe,
पूर्ण;

module_platक्रमm_driver(mt6797_mt6351_driver);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT6797 MT6351 ALSA SoC machine driver");
MODULE_AUTHOR("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("mt6797 mt6351 soc card");

