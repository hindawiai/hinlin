<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम generic Bluetooth SCO link
 * Copyright 2011 Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <sound/soc.h>

अटल स्थिर काष्ठा snd_soc_dapm_widget bt_sco_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("RX"),
	SND_SOC_DAPM_OUTPUT("TX"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route bt_sco_routes[] = अणु
	अणु "Capture", शून्य, "RX" पूर्ण,
	अणु "TX", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver bt_sco_dai[] = अणु
	अणु
		.name = "bt-sco-pcm",
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
	पूर्ण,
	अणु
		.name = "bt-sco-pcm-wb",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 1,
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.capture = अणु
			 .stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 1,
			.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_bt_sco = अणु
	.dapm_widमाला_लो		= bt_sco_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(bt_sco_widमाला_लो),
	.dapm_routes		= bt_sco_routes,
	.num_dapm_routes	= ARRAY_SIZE(bt_sco_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक bt_sco_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &soc_component_dev_bt_sco,
				      bt_sco_dai, ARRAY_SIZE(bt_sco_dai));
पूर्ण

अटल पूर्णांक bt_sco_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bt_sco_driver_ids[] = अणु
	अणु
		.name		= "dfbmcs320",
	पूर्ण,
	अणु
		.name		= "bt-sco",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bt_sco_driver_ids);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id bt_sco_codec_of_match[] = अणु
	अणु .compatible = "delta,dfbmcs320", पूर्ण,
	अणु .compatible = "linux,bt-sco", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bt_sco_codec_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver bt_sco_driver = अणु
	.driver = अणु
		.name = "bt-sco",
		.of_match_table = of_match_ptr(bt_sco_codec_of_match),
	पूर्ण,
	.probe = bt_sco_probe,
	.हटाओ = bt_sco_हटाओ,
	.id_table = bt_sco_driver_ids,
पूर्ण;

module_platक्रमm_driver(bt_sco_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("ASoC generic bluetooth sco link driver");
MODULE_LICENSE("GPL");
