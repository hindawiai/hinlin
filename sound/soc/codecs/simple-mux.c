<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Bootlin SA
 * Author: Alexandre Belloni <alexandre.belloni@bootlin.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/soc.h>

काष्ठा simple_mux अणु
	काष्ठा gpio_desc *gpiod_mux;
	अचिन्हित पूर्णांक mux;
पूर्ण;

अटल स्थिर अक्षर * स्थिर simple_mux_texts[] = अणु
	"Input 1", "Input 2"
पूर्ण;

अटल SOC_ENUM_SINGLE_EXT_DECL(simple_mux_क्रमागत, simple_mux_texts);

अटल पूर्णांक simple_mux_control_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	काष्ठा simple_mux *priv = snd_soc_component_get_drvdata(c);

	ucontrol->value.क्रमागतerated.item[0] = priv->mux;

	वापस 0;
पूर्ण

अटल पूर्णांक simple_mux_control_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	काष्ठा simple_mux *priv = snd_soc_component_get_drvdata(c);

	अगर (ucontrol->value.क्रमागतerated.item[0] > e->items)
		वापस -EINVAL;

	अगर (priv->mux == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	priv->mux = ucontrol->value.क्रमागतerated.item[0];

	gpiod_set_value_cansleep(priv->gpiod_mux, priv->mux);

	वापस snd_soc_dapm_mux_update_घातer(dapm, kcontrol,
					     ucontrol->value.क्रमागतerated.item[0],
					     e, शून्य);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new simple_mux_mux =
	SOC_DAPM_ENUM_EXT("Muxer", simple_mux_क्रमागत, simple_mux_control_get, simple_mux_control_put);

अटल स्थिर काष्ठा snd_soc_dapm_widget simple_mux_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("IN1"),
	SND_SOC_DAPM_INPUT("IN2"),
	SND_SOC_DAPM_MUX("MUX", SND_SOC_NOPM, 0, 0, &simple_mux_mux),
	SND_SOC_DAPM_OUTPUT("OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route simple_mux_dapm_routes[] = अणु
	अणु "OUT", शून्य, "MUX" पूर्ण,
	अणु "MUX", "Input 1", "IN1" पूर्ण,
	अणु "MUX", "Input 2", "IN2" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver simple_mux_component_driver = अणु
	.dapm_widमाला_लो		= simple_mux_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(simple_mux_dapm_widमाला_लो),
	.dapm_routes		= simple_mux_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(simple_mux_dapm_routes),
पूर्ण;

अटल पूर्णांक simple_mux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा simple_mux *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);

	priv->gpiod_mux = devm_gpiod_get(dev, "mux", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpiod_mux)) अणु
		err = PTR_ERR(priv->gpiod_mux);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'mux' gpio: %d", err);
		वापस err;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, &simple_mux_component_driver, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id simple_mux_ids[] = अणु
	अणु .compatible = "simple-audio-mux", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, simple_mux_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver simple_mux_driver = अणु
	.driver = अणु
		.name = "simple-mux",
		.of_match_table = of_match_ptr(simple_mux_ids),
	पूर्ण,
	.probe = simple_mux_probe,
पूर्ण;

module_platक्रमm_driver(simple_mux_driver);

MODULE_DESCRIPTION("ASoC Simple Audio Mux driver");
MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@bootlin.com>");
MODULE_LICENSE("GPL");
