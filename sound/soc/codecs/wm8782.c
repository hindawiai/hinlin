<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sound/soc/codecs/wm8782.c
 * simple, strap-pin configured 24bit 2ch ADC
 *
 * Copyright: 2011 Raumfeld GmbH
 * Author: Johannes Stezenbach <js@sig21.net>
 *
 * based on ad73311.c
 * Copyright:	Analog Devices Inc.
 * Author:	Clअगरf Cai <clअगरf.cai@analog.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8782_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("AINL"),
SND_SOC_DAPM_INPUT("AINR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8782_dapm_routes[] = अणु
	अणु "Capture", शून्य, "AINL" पूर्ण,
	अणु "Capture", शून्य, "AINR" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8782_dai = अणु
	.name = "wm8782",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		/* For configurations with FSAMPEN=0 */
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S20_3LE |
			   SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण;

/* regulator घातer supply names */
अटल स्थिर अक्षर *supply_names[] = अणु
	"Vdda", /* analog supply, 2.7V - 3.6V */
	"Vdd",  /* digital supply, 2.7V - 5.5V */
पूर्ण;

काष्ठा wm8782_priv अणु
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(supply_names)];
पूर्ण;

अटल पूर्णांक wm8782_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8782_priv *priv = snd_soc_component_get_drvdata(component);
	वापस regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
पूर्ण

अटल व्योम wm8782_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8782_priv *priv = snd_soc_component_get_drvdata(component);
	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm8782_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8782_priv *priv = snd_soc_component_get_drvdata(component);
	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8782_soc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8782_priv *priv = snd_soc_component_get_drvdata(component);
	वापस regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
पूर्ण
#अन्यथा
#घोषणा wm8782_soc_suspend      शून्य
#घोषणा wm8782_soc_resume       शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8782 = अणु
	.probe			= wm8782_soc_probe,
	.हटाओ			= wm8782_soc_हटाओ,
	.suspend		= wm8782_soc_suspend,
	.resume			= wm8782_soc_resume,
	.dapm_widमाला_लो		= wm8782_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8782_dapm_widमाला_लो),
	.dapm_routes		= wm8782_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8782_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8782_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wm8782_priv *priv;
	पूर्णांक ret, i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);

	क्रम (i = 0; i < ARRAY_SIZE(supply_names); i++)
		priv->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(priv->supplies),
				      priv->supplies);
	अगर (ret < 0)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm8782, &wm8782_dai, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id wm8782_of_match[] = अणु
	अणु .compatible = "wlf,wm8782", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8782_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver wm8782_codec_driver = अणु
	.driver = अणु
		.name = "wm8782",
		.of_match_table = of_match_ptr(wm8782_of_match),
	पूर्ण,
	.probe = wm8782_probe,
पूर्ण;

module_platक्रमm_driver(wm8782_codec_driver);

MODULE_DESCRIPTION("ASoC WM8782 driver");
MODULE_AUTHOR("Johannes Stezenbach <js@sig21.net>");
MODULE_LICENSE("GPL");
