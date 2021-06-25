<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Analog Devices SSM2305 Amplअगरier Driver
//
// Copyright (C) 2018 Pengutronix, Marco Felsch <kernel@pengutronix.de>
//

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#घोषणा DRV_NAME "ssm2305"

काष्ठा ssm2305 अणु
	/* shutकरोwn gpio  */
	काष्ठा gpio_desc *gpiod_shutकरोwn;
पूर्ण;

अटल पूर्णांक ssm2305_घातer_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kctrl, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा ssm2305 *data = snd_soc_component_get_drvdata(c);

	gpiod_set_value_cansleep(data->gpiod_shutकरोwn,
				 SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget ssm2305_dapm_widमाला_लो[] = अणु
	/* Stereo input/output */
	SND_SOC_DAPM_INPUT("L_IN"),
	SND_SOC_DAPM_INPUT("R_IN"),
	SND_SOC_DAPM_OUTPUT("L_OUT"),
	SND_SOC_DAPM_OUTPUT("R_OUT"),

	SND_SOC_DAPM_SUPPLY("Power", SND_SOC_NOPM, 0, 0, ssm2305_घातer_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ssm2305_dapm_routes[] = अणु
	अणु "L_OUT", शून्य, "L_IN" पूर्ण,
	अणु "R_OUT", शून्य, "R_IN" पूर्ण,
	अणु "L_IN", शून्य, "Power" पूर्ण,
	अणु "R_IN", शून्य, "Power" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver ssm2305_component_driver = अणु
	.dapm_widमाला_लो		= ssm2305_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ssm2305_dapm_widमाला_लो),
	.dapm_routes		= ssm2305_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ssm2305_dapm_routes),
पूर्ण;

अटल पूर्णांक ssm2305_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ssm2305 *priv;
	पूर्णांक err;

	/* Allocate the निजी data */
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	/* Get shutकरोwn gpio */
	priv->gpiod_shutकरोwn = devm_gpiod_get(dev, "shutdown",
					      GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_shutकरोwn)) अणु
		err = PTR_ERR(priv->gpiod_shutकरोwn);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'shutdown' gpio: %d\n",
				err);
		वापस err;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, &ssm2305_component_driver,
					       शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ssm2305_of_match[] = अणु
	अणु .compatible = "adi,ssm2305", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ssm2305_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ssm2305_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(ssm2305_of_match),
	पूर्ण,
	.probe = ssm2305_probe,
पूर्ण;

module_platक्रमm_driver(ssm2305_driver);

MODULE_DESCRIPTION("ASoC SSM2305 amplifier driver");
MODULE_AUTHOR("Marco Felsch <m.felsch@pengutronix.de>");
MODULE_LICENSE("GPL v2");
