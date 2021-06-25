<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// nau8315.c  --  NAU8315 ALSA SoC Audio Amplअगरier Driver
//
// Copyright 2020 Nuvoton Technology Crop.
//
// Author: David Lin <ctlin0@nuvoton.com>
//
// Based on MAX98357A.c

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc-dapm.h>

काष्ठा nau8315_priv अणु
	काष्ठा gpio_desc *enable;
	पूर्णांक enpin_चयन;
पूर्ण;

अटल पूर्णांक nau8315_daiops_trigger(काष्ठा snd_pcm_substream *substream,
		पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा nau8315_priv *nau8315 =
		snd_soc_component_get_drvdata(component);

	अगर (!nau8315->enable)
		वापस 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (nau8315->enpin_चयन) अणु
			gpiod_set_value(nau8315->enable, 1);
			dev_dbg(component->dev, "set enable to 1");
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		gpiod_set_value(nau8315->enable, 0);
		dev_dbg(component->dev, "set enable to 0");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nau8315_enpin_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा nau8315_priv *nau8315 =
		snd_soc_component_get_drvdata(component);

	अगर (event & SND_SOC_DAPM_PRE_PMU)
		nau8315->enpin_चयन = 1;
	अन्यथा अगर (event & SND_SOC_DAPM_POST_PMD)
		nau8315->enpin_चयन = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget nau8315_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("Speaker"),
	SND_SOC_DAPM_OUT_DRV_E("EN_Pin", SND_SOC_NOPM, 0, 0, शून्य, 0,
			nau8315_enpin_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route nau8315_dapm_routes[] = अणु
	अणु"EN_Pin", शून्य, "HiFi Playback"पूर्ण,
	अणु"Speaker", शून्य, "EN_Pin"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver nau8315_component_driver = अणु
	.dapm_widमाला_लो		= nau8315_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(nau8315_dapm_widमाला_लो),
	.dapm_routes		= nau8315_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(nau8315_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops nau8315_dai_ops = अणु
	.trigger	= nau8315_daiops_trigger,
पूर्ण;

#घोषणा NAU8315_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा NAU8315_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_3LE)

अटल काष्ठा snd_soc_dai_driver nau8315_dai_driver = अणु
	.name = "nau8315-hifi",
	.playback = अणु
		.stream_name	= "HiFi Playback",
		.क्रमmats	= NAU8315_FORMATS,
		.rates		= NAU8315_RATES,
		.channels_min	= 1,
		.channels_max	= 2,
	पूर्ण,
	.ops    = &nau8315_dai_ops,
पूर्ण;

अटल पूर्णांक nau8315_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nau8315_priv *nau8315;

	nau8315 = devm_kzalloc(&pdev->dev, माप(*nau8315), GFP_KERNEL);
	अगर (!nau8315)
		वापस -ENOMEM;

	nau8315->enable = devm_gpiod_get_optional(&pdev->dev,
				"enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(nau8315->enable))
		वापस PTR_ERR(nau8315->enable);

	dev_set_drvdata(&pdev->dev, nau8315);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&nau8315_component_driver,
			&nau8315_dai_driver, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id nau8315_device_id[] = अणु
	अणु .compatible = "nuvoton,nau8315" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nau8315_device_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id nau8315_acpi_match[] = अणु
	अणु "NVTN2010", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, nau8315_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver nau8315_platक्रमm_driver = अणु
	.driver = अणु
		.name = "nau8315",
		.of_match_table = of_match_ptr(nau8315_device_id),
		.acpi_match_table = ACPI_PTR(nau8315_acpi_match),
	पूर्ण,
	.probe	= nau8315_platक्रमm_probe,
पूर्ण;
module_platक्रमm_driver(nau8315_platक्रमm_driver);

MODULE_DESCRIPTION("ASoC NAU8315 Mono Class-D Amplifier Driver");
MODULE_AUTHOR("David Lin <ctlin0@nuvoton.com>");
MODULE_LICENSE("GPL v2");
