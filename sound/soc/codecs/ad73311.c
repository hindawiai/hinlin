<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ad73311.c  --  ALSA Soc AD73311 codec support
 *
 * Copyright:	Analog Devices Inc.
 * Author:	Clअगरf Cai <clअगरf.cai@analog.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#समावेश "ad73311.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget ad73311_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("VINP"),
SND_SOC_DAPM_INPUT("VINN"),
SND_SOC_DAPM_OUTPUT("VOUTN"),
SND_SOC_DAPM_OUTPUT("VOUTP"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ad73311_dapm_routes[] = अणु
	अणु "Capture", शून्य, "VINP" पूर्ण,
	अणु "Capture", शून्य, "VINN" पूर्ण,

	अणु "VOUTN", शून्य, "Playback" पूर्ण,
	अणु "VOUTP", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ad73311_dai = अणु
	.name = "ad73311-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE, पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ad73311 = अणु
	.dapm_widमाला_लो		= ad73311_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ad73311_dapm_widमाला_लो),
	.dapm_routes		= ad73311_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ad73311_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ad73311_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_ad73311, &ad73311_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver ad73311_codec_driver = अणु
	.driver = अणु
			.name = "ad73311",
	पूर्ण,

	.probe = ad73311_probe,
पूर्ण;

module_platक्रमm_driver(ad73311_codec_driver);

MODULE_DESCRIPTION("ASoC ad73311 driver");
MODULE_AUTHOR("Cliff Cai ");
MODULE_LICENSE("GPL");
