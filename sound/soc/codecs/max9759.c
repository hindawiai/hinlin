<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MAX9759 Amplअगरier Driver
 *
 * Copyright (c) 2017 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#घोषणा DRV_NAME "max9759"

काष्ठा max9759 अणु
	काष्ठा gpio_desc *gpiod_shutकरोwn;
	काष्ठा gpio_desc *gpiod_mute;
	काष्ठा gpio_descs *gpiod_gain;
	bool is_mute;
	अचिन्हित पूर्णांक gain;
पूर्ण;

अटल पूर्णांक pga_event(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *control, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max9759 *priv = snd_soc_component_get_drvdata(c);

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_value_cansleep(priv->gpiod_shutकरोwn, 0);
	अन्यथा
		gpiod_set_value_cansleep(priv->gpiod_shutकरोwn, 1);

	वापस 0;
पूर्ण

/* From 6dB to 24dB in steps of 6dB */
अटल स्थिर DECLARE_TLV_DB_SCALE(speaker_gain_tlv, 600, 600, 0);

अटल पूर्णांक speaker_gain_control_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max9759 *priv = snd_soc_component_get_drvdata(c);

	ucontrol->value.पूर्णांकeger.value[0] = priv->gain;

	वापस 0;
पूर्ण

अटल स्थिर bool speaker_gain_table[4][2] = अणु
	/* G1, G2 */
	अणुtrue, trueपूर्ण,	/* +6dB */
	अणुfalse, trueपूर्ण,	/* +12dB */
	अणुtrue, falseपूर्ण,	/* +18dB */
	अणुfalse, falseपूर्ण,	/* +24dB */
पूर्ण;

अटल पूर्णांक speaker_gain_control_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max9759 *priv = snd_soc_component_get_drvdata(c);

	अगर (ucontrol->value.पूर्णांकeger.value[0] > 3)
		वापस -EINVAL;

	priv->gain = ucontrol->value.पूर्णांकeger.value[0];

	/* G1 */
	gpiod_set_value_cansleep(priv->gpiod_gain->desc[0],
				 speaker_gain_table[priv->gain][0]);
	/* G2 */
	gpiod_set_value_cansleep(priv->gpiod_gain->desc[1],
				 speaker_gain_table[priv->gain][1]);

	वापस 1;
पूर्ण

अटल पूर्णांक speaker_mute_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max9759 *priv = snd_soc_component_get_drvdata(c);

	ucontrol->value.पूर्णांकeger.value[0] = !priv->is_mute;

	वापस 0;
पूर्ण

अटल पूर्णांक speaker_mute_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max9759 *priv = snd_soc_component_get_drvdata(c);

	priv->is_mute = !ucontrol->value.पूर्णांकeger.value[0];

	gpiod_set_value_cansleep(priv->gpiod_mute, priv->is_mute);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new max9759_dapm_controls[] = अणु
	SOC_SINGLE_EXT_TLV("Speaker Gain Volume", 0, 0, 3, 0,
			   speaker_gain_control_get, speaker_gain_control_put,
			   speaker_gain_tlv),
	SOC_SINGLE_BOOL_EXT("Playback Switch", 0,
			    speaker_mute_get, speaker_mute_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max9759_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("INL"),
	SND_SOC_DAPM_INPUT("INR"),
	SND_SOC_DAPM_PGA_E("PGA", SND_SOC_NOPM, 0, 0, शून्य, 0, pga_event,
			   (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
	SND_SOC_DAPM_OUTPUT("OUTL"),
	SND_SOC_DAPM_OUTPUT("OUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max9759_dapm_routes[] = अणु
	अणु "PGA", शून्य, "INL" पूर्ण,
	अणु "PGA", शून्य, "INR" पूर्ण,
	अणु "OUTL", शून्य, "PGA" पूर्ण,
	अणु "OUTR", शून्य, "PGA" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver max9759_component_driver = अणु
	.controls		= max9759_dapm_controls,
	.num_controls		= ARRAY_SIZE(max9759_dapm_controls),
	.dapm_widमाला_लो		= max9759_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max9759_dapm_widमाला_लो),
	.dapm_routes		= max9759_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(max9759_dapm_routes),
पूर्ण;

अटल पूर्णांक max9759_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा max9759 *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	priv->gpiod_shutकरोwn = devm_gpiod_get(dev, "shutdown", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpiod_shutकरोwn)) अणु
		err = PTR_ERR(priv->gpiod_shutकरोwn);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'shutdown' gpio: %d", err);
		वापस err;
	पूर्ण

	priv->gpiod_mute = devm_gpiod_get(dev, "mute", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpiod_mute)) अणु
		err = PTR_ERR(priv->gpiod_mute);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'mute' gpio: %d", err);
		वापस err;
	पूर्ण
	priv->is_mute = true;

	priv->gpiod_gain = devm_gpiod_get_array(dev, "gain", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpiod_gain)) अणु
		err = PTR_ERR(priv->gpiod_gain);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'gain' gpios: %d", err);
		वापस err;
	पूर्ण
	priv->gain = 0;

	अगर (priv->gpiod_gain->ndescs != 2) अणु
		dev_err(dev, "Invalid 'gain' gpios count: %d",
			priv->gpiod_gain->ndescs);
		वापस -EINVAL;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, &max9759_component_driver,
					       शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max9759_ids[] = अणु
	अणु .compatible = "maxim,max9759", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max9759_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver max9759_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(max9759_ids),
	पूर्ण,
	.probe = max9759_probe,
पूर्ण;

module_platक्रमm_driver(max9759_driver);

MODULE_DESCRIPTION("ASoC MAX9759 amplifier driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL");
