<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ads117x.c  --  Driver क्रम ads1174/8 ADC chips
 *
 * Copyright 2009 ShotSpotter Inc.
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#समावेश <linux/of.h>

#घोषणा ADS117X_RATES (SNDRV_PCM_RATE_8000_48000)
#घोषणा ADS117X_FORMATS (SNDRV_PCM_FMTBIT_S16_LE)

अटल स्थिर काष्ठा snd_soc_dapm_widget ads117x_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("Input1"),
SND_SOC_DAPM_INPUT("Input2"),
SND_SOC_DAPM_INPUT("Input3"),
SND_SOC_DAPM_INPUT("Input4"),
SND_SOC_DAPM_INPUT("Input5"),
SND_SOC_DAPM_INPUT("Input6"),
SND_SOC_DAPM_INPUT("Input7"),
SND_SOC_DAPM_INPUT("Input8"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ads117x_dapm_routes[] = अणु
	अणु "Capture", शून्य, "Input1" पूर्ण,
	अणु "Capture", शून्य, "Input2" पूर्ण,
	अणु "Capture", शून्य, "Input3" पूर्ण,
	अणु "Capture", शून्य, "Input4" पूर्ण,
	अणु "Capture", शून्य, "Input5" पूर्ण,
	अणु "Capture", शून्य, "Input6" पूर्ण,
	अणु "Capture", शून्य, "Input7" पूर्ण,
	अणु "Capture", शून्य, "Input8" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ads117x_dai = अणु
/* ADC */
	.name = "ads117x-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 32,
		.rates = ADS117X_RATES,
		.क्रमmats = ADS117X_FORMATS,पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ads117x = अणु
	.dapm_widमाला_लो		= ads117x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ads117x_dapm_widमाला_लो),
	.dapm_routes		= ads117x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ads117x_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ads117x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_ads117x, &ads117x_dai, 1);
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ads117x_dt_ids[] = अणु
	अणु .compatible = "ti,ads1174" पूर्ण,
	अणु .compatible = "ti,ads1178" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ads117x_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ads117x_codec_driver = अणु
	.driver = अणु
			.name = "ads117x-codec",
			.of_match_table = of_match_ptr(ads117x_dt_ids),
	पूर्ण,

	.probe = ads117x_probe,
पूर्ण;

module_platक्रमm_driver(ads117x_codec_driver);

MODULE_DESCRIPTION("ASoC ads117x driver");
MODULE_AUTHOR("Graeme Gregory");
MODULE_LICENSE("GPL");
