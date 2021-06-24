<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is a simple driver क्रम the GTM601 Voice PCM पूर्णांकerface
 *
 * Copyright (C) 2015 Goldelico GmbH
 *
 * Author: Marek Belisko <marek@goldelico.com>
 *
 * Based on wm8727.c driver
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

अटल स्थिर काष्ठा snd_soc_dapm_widget gपंचांग601_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("AOUT"),
	SND_SOC_DAPM_INPUT("AIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route gपंचांग601_dapm_routes[] = अणु
	अणु "AOUT", शून्य, "Playback" पूर्ण,
	अणु "Capture", शून्य, "AIN" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver gपंचांग601_dai = अणु
	.name = "gtm601",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver bm818_dai = अणु
	.name = "bm818",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_gपंचांग601 = अणु
	.dapm_widमाला_लो		= gपंचांग601_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(gपंचांग601_dapm_widमाला_लो),
	.dapm_routes		= gपंचांग601_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(gपंचांग601_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक gपंचांग601_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा snd_soc_dai_driver *dai_driver;

	dai_driver = of_device_get_match_data(&pdev->dev);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_gपंचांग601,
			(काष्ठा snd_soc_dai_driver *)dai_driver, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id gपंचांग601_codec_of_match[] __maybe_unused = अणु
	अणु .compatible = "option,gtm601", .data = (व्योम *)&gपंचांग601_dai पूर्ण,
	अणु .compatible = "broadmobi,bm818", .data = (व्योम *)&bm818_dai पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gपंचांग601_codec_of_match);

अटल काष्ठा platक्रमm_driver gपंचांग601_codec_driver = अणु
	.driver = अणु
		.name = "gtm601",
		.of_match_table = of_match_ptr(gपंचांग601_codec_of_match),
	पूर्ण,
	.probe = gपंचांग601_platक्रमm_probe,
पूर्ण;

module_platक्रमm_driver(gपंचांग601_codec_driver);

MODULE_DESCRIPTION("ASoC gtm601 driver");
MODULE_AUTHOR("Marek Belisko <marek@goldelico.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gtm601");
