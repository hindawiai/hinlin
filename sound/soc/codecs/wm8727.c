<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8727.c
 *
 *  Created on: 15-Oct-2009
 *      Author: neil.jones@imgtec.com
 *
 * Copyright (C) 2009 Imagination Technologies Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8727_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_OUTPUT("VOUTL"),
SND_SOC_DAPM_OUTPUT("VOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8727_dapm_routes[] = अणु
	अणु "VOUTL", शून्य, "Playback" पूर्ण,
	अणु "VOUTR", शून्य, "Playback" पूर्ण,
पूर्ण;

/*
 * Note this is a simple chip with no configuration पूर्णांकerface, sample rate is
 * determined स्वतःmatically by examining the Master घड़ी and Bit घड़ी ratios
 */
#घोषणा WM8727_RATES  (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
			SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 |\
			SNDRV_PCM_RATE_192000)

अटल काष्ठा snd_soc_dai_driver wm8727_dai = अणु
	.name = "wm8727-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8727_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
		पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8727 = अणु
	.dapm_widमाला_लो		= wm8727_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8727_dapm_widमाला_लो),
	.dapm_routes		= wm8727_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8727_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8727_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm8727, &wm8727_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver wm8727_codec_driver = अणु
	.driver = अणु
			.name = "wm8727",
	पूर्ण,

	.probe = wm8727_probe,
पूर्ण;

module_platक्रमm_driver(wm8727_codec_driver);

MODULE_DESCRIPTION("ASoC wm8727 driver");
MODULE_AUTHOR("Neil Jones");
MODULE_LICENSE("GPL");
