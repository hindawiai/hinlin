<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/soc.h>

#घोषणा DRV_NAME "simple-amplifier"

काष्ठा simple_amp अणु
	काष्ठा gpio_desc *gpiod_enable;
पूर्ण;

अटल पूर्णांक drv_event(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *control, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा simple_amp *priv = snd_soc_component_get_drvdata(c);
	पूर्णांक val;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val = 1;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		val = 0;
		अवरोध;
	शेष:
		WARN(1, "Unexpected event");
		वापस -EINVAL;
	पूर्ण

	gpiod_set_value_cansleep(priv->gpiod_enable, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget simple_amp_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("INL"),
	SND_SOC_DAPM_INPUT("INR"),
	SND_SOC_DAPM_OUT_DRV_E("DRV", SND_SOC_NOPM, 0, 0, शून्य, 0, drv_event,
			       (SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD)),
	SND_SOC_DAPM_OUTPUT("OUTL"),
	SND_SOC_DAPM_OUTPUT("OUTR"),
	SND_SOC_DAPM_REGULATOR_SUPPLY("VCC", 20, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route simple_amp_dapm_routes[] = अणु
	अणु "DRV", शून्य, "INL" पूर्ण,
	अणु "DRV", शून्य, "INR" पूर्ण,
	अणु "OUTL", शून्य, "VCC" पूर्ण,
	अणु "OUTR", शून्य, "VCC" पूर्ण,
	अणु "OUTL", शून्य, "DRV" पूर्ण,
	अणु "OUTR", शून्य, "DRV" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver simple_amp_component_driver = अणु
	.dapm_widमाला_लो		= simple_amp_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(simple_amp_dapm_widमाला_लो),
	.dapm_routes		= simple_amp_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(simple_amp_dapm_routes),
पूर्ण;

अटल पूर्णांक simple_amp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा simple_amp *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->gpiod_enable = devm_gpiod_get_optional(dev, "enable",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_enable)) अणु
		err = PTR_ERR(priv->gpiod_enable);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'enable' gpio: %d", err);
		वापस err;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev,
					       &simple_amp_component_driver,
					       शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id simple_amp_ids[] = अणु
	अणु .compatible = "dioo,dio2125", पूर्ण,
	अणु .compatible = "simple-audio-amplifier", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, simple_amp_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver simple_amp_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(simple_amp_ids),
	पूर्ण,
	.probe = simple_amp_probe,
पूर्ण;

module_platक्रमm_driver(simple_amp_driver);

MODULE_DESCRIPTION("ASoC Simple Audio Amplifier driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL");
