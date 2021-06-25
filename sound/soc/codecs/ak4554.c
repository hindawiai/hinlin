<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ak4554.c
//
// Copyright (C) 2013 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#समावेश <linux/module.h>
#समावेश <sound/soc.h>

/*
 * ak4554 is very simple DA/AD converter which has no setting रेजिस्टर.
 *
 * CAUTION
 *
 * ak4554 playback क्रमmat is SND_SOC_DAIFMT_RIGHT_J,
 * and,   capture  क्रमmat is SND_SOC_DAIFMT_LEFT_J
 * on same bit घड़ी, LR घड़ी.
 * But, this driver करोesn't have snd_soc_dai_ops :: set_fmt
 *
 * CPU/Codec DAI image
 *
 * CPU-DAI1 (plaback only fmt = RIGHT_J) --+-- ak4554
 *					   |
 * CPU-DAI2 (capture only fmt = LEFT_J) ---+
 */

अटल स्थिर काष्ठा snd_soc_dapm_widget ak4554_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("AINL"),
SND_SOC_DAPM_INPUT("AINR"),

SND_SOC_DAPM_OUTPUT("AOUTL"),
SND_SOC_DAPM_OUTPUT("AOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4554_dapm_routes[] = अणु
	अणु "Capture", शून्य, "AINL" पूर्ण,
	अणु "Capture", शून्य, "AINR" पूर्ण,

	अणु "AOUTL", शून्य, "Playback" पूर्ण,
	अणु "AOUTR", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4554_dai = अणु
	.name = "ak4554-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ak4554 = अणु
	.dapm_widमाला_लो		= ak4554_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4554_dapm_widमाला_लो),
	.dapm_routes		= ak4554_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ak4554_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ak4554_soc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &soc_component_dev_ak4554,
				      &ak4554_dai, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id ak4554_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak4554" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ak4554_of_match);

अटल काष्ठा platक्रमm_driver ak4554_driver = अणु
	.driver = अणु
		.name = "ak4554-adc-dac",
		.of_match_table = ak4554_of_match,
	पूर्ण,
	.probe	= ak4554_soc_probe,
पूर्ण;
module_platक्रमm_driver(ak4554_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SoC AK4554 driver");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
