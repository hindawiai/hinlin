<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 *
 * max98357a.c -- MAX98357A ALSA SoC Codec driver
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc-dapm.h>

काष्ठा max98357a_priv अणु
	काष्ठा gpio_desc *sdmode;
	अचिन्हित पूर्णांक sdmode_delay;
	पूर्णांक sdmode_चयन;
पूर्ण;

अटल पूर्णांक max98357a_daiops_trigger(काष्ठा snd_pcm_substream *substream,
		पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98357a_priv *max98357a =
		snd_soc_component_get_drvdata(component);

	अगर (!max98357a->sdmode)
		वापस 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		mdelay(max98357a->sdmode_delay);
		अगर (max98357a->sdmode_चयन) अणु
			gpiod_set_value(max98357a->sdmode, 1);
			dev_dbg(component->dev, "set sdmode to 1");
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		gpiod_set_value(max98357a->sdmode, 0);
		dev_dbg(component->dev, "set sdmode to 0");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max98357a_sdmode_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98357a_priv *max98357a =
		snd_soc_component_get_drvdata(component);

	अगर (event & SND_SOC_DAPM_POST_PMU)
		max98357a->sdmode_चयन = 1;
	अन्यथा अगर (event & SND_SOC_DAPM_POST_PMD)
		max98357a->sdmode_चयन = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget max98357a_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("Speaker"),
	SND_SOC_DAPM_OUT_DRV_E("SD_MODE", SND_SOC_NOPM, 0, 0, शून्य, 0,
			max98357a_sdmode_event,
			SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98357a_dapm_routes[] = अणु
	अणु"SD_MODE", शून्य, "HiFi Playback"पूर्ण,
	अणु"Speaker", शून्य, "SD_MODE"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver max98357a_component_driver = अणु
	.dapm_widमाला_लो		= max98357a_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98357a_dapm_widमाला_लो),
	.dapm_routes		= max98357a_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(max98357a_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops max98357a_dai_ops = अणु
	.trigger        = max98357a_daiops_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98357a_dai_driver = अणु
	.name = "HiFi",
	.playback = अणु
		.stream_name	= "HiFi Playback",
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16 |
					SNDRV_PCM_FMTBIT_S24 |
					SNDRV_PCM_FMTBIT_S32,
		.rates		= SNDRV_PCM_RATE_8000 |
					SNDRV_PCM_RATE_16000 |
					SNDRV_PCM_RATE_32000 |
					SNDRV_PCM_RATE_44100 |
					SNDRV_PCM_RATE_48000 |
					SNDRV_PCM_RATE_88200 |
					SNDRV_PCM_RATE_96000,
		.rate_min	= 8000,
		.rate_max	= 96000,
		.channels_min	= 1,
		.channels_max	= 2,
	पूर्ण,
	.ops    = &max98357a_dai_ops,
पूर्ण;

अटल पूर्णांक max98357a_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max98357a_priv *max98357a;
	पूर्णांक ret;

	max98357a = devm_kzalloc(&pdev->dev, माप(*max98357a), GFP_KERNEL);
	अगर (!max98357a)
		वापस -ENOMEM;

	max98357a->sdmode = devm_gpiod_get_optional(&pdev->dev,
				"sdmode", GPIOD_OUT_LOW);
	अगर (IS_ERR(max98357a->sdmode))
		वापस PTR_ERR(max98357a->sdmode);

	ret = device_property_पढ़ो_u32(&pdev->dev, "sdmode-delay",
					&max98357a->sdmode_delay);
	अगर (ret) अणु
		max98357a->sdmode_delay = 0;
		dev_dbg(&pdev->dev,
			"no optional property 'sdmode-delay' found, "
			"default: no delay\n");
	पूर्ण

	dev_set_drvdata(&pdev->dev, max98357a);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&max98357a_component_driver,
			&max98357a_dai_driver, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max98357a_device_id[] = अणु
	अणु .compatible = "maxim,max98357a" पूर्ण,
	अणु .compatible = "maxim,max98360a" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98357a_device_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id max98357a_acpi_match[] = अणु
	अणु "MX98357A", 0 पूर्ण,
	अणु "MX98360A", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max98357a_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver max98357a_platक्रमm_driver = अणु
	.driver = अणु
		.name = "max98357a",
		.of_match_table = of_match_ptr(max98357a_device_id),
		.acpi_match_table = ACPI_PTR(max98357a_acpi_match),
	पूर्ण,
	.probe	= max98357a_platक्रमm_probe,
पूर्ण;
module_platक्रमm_driver(max98357a_platक्रमm_driver);

MODULE_DESCRIPTION("Maxim MAX98357A Codec Driver");
MODULE_LICENSE("GPL v2");
