<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt1015p.c  --  RT1015P ALSA SoC audio amplअगरier driver
//
// Copyright 2020 The Linux Foundation. All rights reserved.

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
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

काष्ठा rt1015p_priv अणु
	काष्ठा gpio_desc *sdb;
	bool calib_करोne;
पूर्ण;

अटल पूर्णांक rt1015p_sdb_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt1015p_priv *rt1015p =
		snd_soc_component_get_drvdata(component);

	अगर (!rt1015p->sdb)
		वापस 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		gpiod_set_value_cansleep(rt1015p->sdb, 1);
		dev_dbg(component->dev, "set sdb to 1");

		अगर (!rt1015p->calib_करोne) अणु
			msleep(300);
			rt1015p->calib_करोne = true;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		gpiod_set_value_cansleep(rt1015p->sdb, 0);
		dev_dbg(component->dev, "set sdb to 0");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1015p_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("Speaker"),
	SND_SOC_DAPM_OUT_DRV_E("SDB", SND_SOC_NOPM, 0, 0, शून्य, 0,
			rt1015p_sdb_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1015p_dapm_routes[] = अणु
	अणु"SDB", शून्य, "HiFi Playback"पूर्ण,
	अणु"Speaker", शून्य, "SDB"पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt1015p_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt1015p_priv *rt1015p = snd_soc_component_get_drvdata(component);

	rt1015p->calib_करोne = false;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt1015p_suspend शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver rt1015p_component_driver = अणु
	.suspend		= rt1015p_suspend,
	.dapm_widमाला_लो		= rt1015p_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt1015p_dapm_widमाला_लो),
	.dapm_routes		= rt1015p_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt1015p_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt1015p_dai_driver = अणु
	.name = "HiFi",
	.playback = अणु
		.stream_name	= "HiFi Playback",
		.क्रमmats	= SNDRV_PCM_FMTBIT_S24 |
					SNDRV_PCM_FMTBIT_S32,
		.rates		= SNDRV_PCM_RATE_48000,
		.channels_min	= 1,
		.channels_max	= 2,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt1015p_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rt1015p_priv *rt1015p;

	rt1015p = devm_kzalloc(&pdev->dev, माप(*rt1015p), GFP_KERNEL);
	अगर (!rt1015p)
		वापस -ENOMEM;

	rt1015p->sdb = devm_gpiod_get_optional(&pdev->dev,
				"sdb", GPIOD_OUT_LOW);
	अगर (IS_ERR(rt1015p->sdb))
		वापस PTR_ERR(rt1015p->sdb);

	dev_set_drvdata(&pdev->dev, rt1015p);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&rt1015p_component_driver,
			&rt1015p_dai_driver, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt1015p_device_id[] = अणु
	अणु .compatible = "realtek,rt1015p" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rt1015p_device_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt1015p_acpi_match[] = अणु
	अणु "RTL1015", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt1015p_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver rt1015p_platक्रमm_driver = अणु
	.driver = अणु
		.name = "rt1015p",
		.of_match_table = of_match_ptr(rt1015p_device_id),
		.acpi_match_table = ACPI_PTR(rt1015p_acpi_match),
	पूर्ण,
	.probe = rt1015p_platक्रमm_probe,
पूर्ण;
module_platक्रमm_driver(rt1015p_platक्रमm_driver);

MODULE_DESCRIPTION("ASoC RT1015P driver");
MODULE_LICENSE("GPL v2");
