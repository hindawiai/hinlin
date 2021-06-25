<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC SPDIF DIT driver
 *
 *  This driver is used by controllers which can operate in DIT (SPDI/F) where
 *  no codec is needed.  This file provides stub codec that can be used
 *  in these configurations. TI DaVinci Audio controller uses this driver.
 *
 * Author:      Steve Chen,  <schen@mvista.com>
 * Copyright:   (C) 2009 MontaVista Software, Inc., <source@mvista.com>
 * Copyright:   (C) 2009  Texas Instruments, India
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <linux/of.h>

#घोषणा DRV_NAME "spdif-dit"

#घोषणा STUB_RATES	SNDRV_PCM_RATE_8000_192000
#घोषणा STUB_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE  | \
			SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dapm_widget dit_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("spdif-out"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route dit_routes[] = अणु
	अणु "spdif-out", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_component_driver soc_codec_spdअगर_dit = अणु
	.dapm_widमाला_लो		= dit_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(dit_widमाला_लो),
	.dapm_routes		= dit_routes,
	.num_dapm_routes	= ARRAY_SIZE(dit_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver dit_stub_dai = अणु
	.name		= "dit-hifi",
	.playback 	= अणु
		.stream_name	= "Playback",
		.channels_min	= 1,
		.channels_max	= 384,
		.rates		= STUB_RATES,
		.क्रमmats	= STUB_FORMATS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक spdअगर_dit_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_codec_spdअगर_dit,
			&dit_stub_dai, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spdअगर_dit_dt_ids[] = अणु
	अणु .compatible = "linux,spdif-dit", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spdअगर_dit_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver spdअगर_dit_driver = अणु
	.probe		= spdअगर_dit_probe,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = of_match_ptr(spdअगर_dit_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spdअगर_dit_driver);

MODULE_AUTHOR("Steve Chen <schen@mvista.com>");
MODULE_DESCRIPTION("SPDIF dummy codec driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
