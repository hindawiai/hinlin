<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC SPDIF सूची (Digital Interface Reciever) driver
 *
 * Based on ALSA SoC SPDIF DIT driver
 *
 *  This driver is used by controllers which can operate in सूची (SPDI/F) where
 *  no codec is needed.  This file provides stub codec that can be used
 *  in these configurations. SPEAr SPDIF IN Audio controller uses this driver.
 *
 * Author:      Vipin Kumar,  <vipin.kumar@st.com>
 * Copyright:   (C) 2012  ST Microelectronics
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <linux/of.h>

अटल स्थिर काष्ठा snd_soc_dapm_widget dir_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("spdif-in"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route dir_routes[] = अणु
	अणु "Capture", शून्य, "spdif-in" पूर्ण,
पूर्ण;

#घोषणा STUB_RATES	SNDRV_PCM_RATE_8000_192000
#घोषणा STUB_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE  | \
			SNDRV_PCM_FMTBIT_S32_LE | \
			SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE)

अटल काष्ठा snd_soc_component_driver soc_codec_spdअगर_dir = अणु
	.dapm_widमाला_लो		= dir_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(dir_widमाला_लो),
	.dapm_routes		= dir_routes,
	.num_dapm_routes	= ARRAY_SIZE(dir_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver dir_stub_dai = अणु
	.name		= "dir-hifi",
	.capture	= अणु
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= 384,
		.rates		= STUB_RATES,
		.क्रमmats	= STUB_FORMATS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक spdअगर_dir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_codec_spdअगर_dir,
			&dir_stub_dai, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spdअगर_dir_dt_ids[] = अणु
	अणु .compatible = "linux,spdif-dir", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spdअगर_dir_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver spdअगर_dir_driver = अणु
	.probe		= spdअगर_dir_probe,
	.driver		= अणु
		.name	= "spdif-dir",
		.of_match_table = of_match_ptr(spdअगर_dir_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spdअगर_dir_driver);

MODULE_DESCRIPTION("ASoC SPDIF DIR driver");
MODULE_AUTHOR("Vipin Kumar <vipin.kumar@st.com>");
MODULE_LICENSE("GPL");
