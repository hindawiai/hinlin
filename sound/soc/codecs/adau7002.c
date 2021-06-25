<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADAU7002 Stereo PDM-to-I2S/TDM converter driver
 *
 * Copyright 2014-2016 Analog Devices
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <sound/soc.h>

काष्ठा adau7002_priv अणु
	पूर्णांक wakeup_delay;
पूर्ण;

अटल पूर्णांक adau7002_aअगर_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	काष्ठा adau7002_priv *adau7002 =
			snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (adau7002->wakeup_delay)
			msleep(adau7002->wakeup_delay);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adau7002_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau7002_priv *adau7002;

	adau7002 = devm_kzalloc(component->dev, माप(*adau7002),
				GFP_KERNEL);
	अगर (!adau7002)
		वापस -ENOMEM;

	device_property_पढ़ो_u32(component->dev, "wakeup-delay-ms",
				 &adau7002->wakeup_delay);

	snd_soc_component_set_drvdata(component, adau7002);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget adau7002_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT_E("ADAU AIF", "Capture", 0,
			       SND_SOC_NOPM, 0, 0, adau7002_aअगर_event,
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_INPUT("PDM_DAT"),
	SND_SOC_DAPM_REGULATOR_SUPPLY("IOVDD", 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau7002_routes[] = अणु
	अणु "ADAU AIF", शून्य, "PDM_DAT"पूर्ण,
	अणु "Capture", शून्य, "PDM_DAT" पूर्ण,
	अणु "Capture", शून्य, "IOVDD" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver adau7002_dai = अणु
	.name = "adau7002-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S18_3LE |
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE |
			SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S32_LE,
		.sig_bits = 20,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver adau7002_component_driver = अणु
	.probe			= adau7002_component_probe,
	.dapm_widमाला_लो		= adau7002_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adau7002_widमाला_लो),
	.dapm_routes		= adau7002_routes,
	.num_dapm_routes	= ARRAY_SIZE(adau7002_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक adau7002_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&adau7002_component_driver,
			&adau7002_dai, 1);
पूर्ण

अटल पूर्णांक adau7002_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id adau7002_dt_ids[] = अणु
	अणु .compatible = "adi,adau7002", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adau7002_dt_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id adau7002_acpi_match[] = अणु
	अणु "ADAU7002", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, adau7002_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver adau7002_driver = अणु
	.driver = अणु
		.name = "adau7002",
		.of_match_table	= of_match_ptr(adau7002_dt_ids),
		.acpi_match_table = ACPI_PTR(adau7002_acpi_match),
	पूर्ण,
	.probe = adau7002_probe,
	.हटाओ = adau7002_हटाओ,
पूर्ण;
module_platक्रमm_driver(adau7002_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("ADAU7002 Stereo PDM-to-I2S/TDM Converter driver");
MODULE_LICENSE("GPL v2");
