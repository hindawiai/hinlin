<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC Texas Instruments TPA6130A2 headset stereo amplअगरier driver
 *
 * Copyright (C) Nokia Corporation
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/tpa6130a2-plat.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>

#समावेश "tpa6130a2.h"

क्रमागत tpa_model अणु
	TPA6130A2,
	TPA6140A2,
पूर्ण;

/* This काष्ठा is used to save the context */
काष्ठा tpa6130a2_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator *supply;
	पूर्णांक घातer_gpio;
	क्रमागत tpa_model id;
पूर्ण;

अटल पूर्णांक tpa6130a2_घातer(काष्ठा tpa6130a2_data *data, bool enable)
अणु
	पूर्णांक ret = 0, ret2;

	अगर (enable) अणु
		ret = regulator_enable(data->supply);
		अगर (ret != 0) अणु
			dev_err(data->dev,
				"Failed to enable supply: %d\n", ret);
			वापस ret;
		पूर्ण
		/* Power on */
		अगर (data->घातer_gpio >= 0)
			gpio_set_value(data->घातer_gpio, 1);

		/* Sync रेजिस्टरs */
		regcache_cache_only(data->regmap, false);
		ret = regcache_sync(data->regmap);
		अगर (ret != 0) अणु
			dev_err(data->dev,
				"Failed to sync registers: %d\n", ret);
			regcache_cache_only(data->regmap, true);
			अगर (data->घातer_gpio >= 0)
				gpio_set_value(data->घातer_gpio, 0);
			ret2 = regulator_disable(data->supply);
			अगर (ret2 != 0)
				dev_err(data->dev,
					"Failed to disable supply: %d\n", ret2);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Powered off device करोes not retain रेजिस्टरs. While device
		 * is off, any रेजिस्टर updates (i.e. volume changes) should
		 * happen in cache only.
		 */
		regcache_mark_dirty(data->regmap);
		regcache_cache_only(data->regmap, true);

		/* Power off */
		अगर (data->घातer_gpio >= 0)
			gpio_set_value(data->घातer_gpio, 0);

		ret = regulator_disable(data->supply);
		अगर (ret != 0) अणु
			dev_err(data->dev,
				"Failed to disable supply: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tpa6130a2_घातer_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kctrl, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा tpa6130a2_data *data = snd_soc_component_get_drvdata(c);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		/* Beक्रमe widget घातer up: turn chip on, sync रेजिस्टरs */
		वापस tpa6130a2_घातer(data, true);
	पूर्ण अन्यथा अणु
		/* After widget घातer करोwn: turn chip off */
		वापस tpa6130a2_घातer(data, false);
	पूर्ण
पूर्ण

/*
 * TPA6130 volume. From -59.5 to 4 dB with increasing step size when going
 * करोwn in gain.
 */
अटल स्थिर DECLARE_TLV_DB_RANGE(tpa6130_tlv,
	0, 1, TLV_DB_SCALE_ITEM(-5950, 600, 0),
	2, 3, TLV_DB_SCALE_ITEM(-5000, 250, 0),
	4, 5, TLV_DB_SCALE_ITEM(-4550, 160, 0),
	6, 7, TLV_DB_SCALE_ITEM(-4140, 190, 0),
	8, 9, TLV_DB_SCALE_ITEM(-3650, 120, 0),
	10, 11, TLV_DB_SCALE_ITEM(-3330, 160, 0),
	12, 13, TLV_DB_SCALE_ITEM(-3040, 180, 0),
	14, 20, TLV_DB_SCALE_ITEM(-2710, 110, 0),
	21, 37, TLV_DB_SCALE_ITEM(-1960, 74, 0),
	38, 63, TLV_DB_SCALE_ITEM(-720, 45, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new tpa6130a2_controls[] = अणु
	SOC_SINGLE_TLV("Headphone Playback Volume",
		       TPA6130A2_REG_VOL_MUTE, 0, 0x3f, 0,
		       tpa6130_tlv),
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(tpa6140_tlv,
	0, 8, TLV_DB_SCALE_ITEM(-5900, 400, 0),
	9, 16, TLV_DB_SCALE_ITEM(-2500, 200, 0),
	17, 31, TLV_DB_SCALE_ITEM(-1000, 100, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new tpa6140a2_controls[] = अणु
	SOC_SINGLE_TLV("Headphone Playback Volume",
		       TPA6130A2_REG_VOL_MUTE, 1, 0x1f, 0,
		       tpa6140_tlv),
पूर्ण;

अटल पूर्णांक tpa6130a2_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tpa6130a2_data *data = snd_soc_component_get_drvdata(component);

	अगर (data->id == TPA6140A2)
		वापस snd_soc_add_component_controls(component,
			tpa6140a2_controls, ARRAY_SIZE(tpa6140a2_controls));
	अन्यथा
		वापस snd_soc_add_component_controls(component,
			tpa6130a2_controls, ARRAY_SIZE(tpa6130a2_controls));
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget tpa6130a2_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("LEFTIN"),
	SND_SOC_DAPM_INPUT("RIGHTIN"),
	SND_SOC_DAPM_OUTPUT("HPLEFT"),
	SND_SOC_DAPM_OUTPUT("HPRIGHT"),

	SND_SOC_DAPM_PGA("Left Mute", TPA6130A2_REG_VOL_MUTE,
			 TPA6130A2_HP_EN_L_SHIFT, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Right Mute", TPA6130A2_REG_VOL_MUTE,
			 TPA6130A2_HP_EN_R_SHIFT, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Left PGA", TPA6130A2_REG_CONTROL,
			 TPA6130A2_HP_EN_L_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right PGA", TPA6130A2_REG_CONTROL,
			 TPA6130A2_HP_EN_R_SHIFT, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Power", TPA6130A2_REG_CONTROL,
			    TPA6130A2_SWS_SHIFT, 1, tpa6130a2_घातer_event,
			    SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tpa6130a2_dapm_routes[] = अणु
	अणु "Left PGA", शून्य, "LEFTIN" पूर्ण,
	अणु "Right PGA", शून्य, "RIGHTIN" पूर्ण,

	अणु "Left Mute", शून्य, "Left PGA" पूर्ण,
	अणु "Right Mute", शून्य, "Right PGA" पूर्ण,

	अणु "HPLEFT", शून्य, "Left Mute" पूर्ण,
	अणु "HPRIGHT", शून्य, "Right Mute" पूर्ण,

	अणु "Left PGA", शून्य, "Power" पूर्ण,
	अणु "Right PGA", शून्य, "Power" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tpa6130a2_component_driver = अणु
	.name = "tpa6130a2",
	.probe = tpa6130a2_component_probe,
	.dapm_widमाला_लो = tpa6130a2_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tpa6130a2_dapm_widमाला_लो),
	.dapm_routes = tpa6130a2_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(tpa6130a2_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष tpa6130a2_reg_शेषs[] = अणु
	अणु TPA6130A2_REG_CONTROL, TPA6130A2_SWS पूर्ण,
	अणु TPA6130A2_REG_VOL_MUTE, TPA6130A2_MUTE_R | TPA6130A2_MUTE_L पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tpa6130a2_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = TPA6130A2_REG_VERSION,
	.reg_शेषs = tpa6130a2_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tpa6130a2_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक tpa6130a2_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev;
	काष्ठा tpa6130a2_data *data;
	काष्ठा tpa6130a2_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा device_node *np = client->dev.of_node;
	स्थिर अक्षर *regulator;
	अचिन्हित पूर्णांक version;
	पूर्णांक ret;

	dev = &client->dev;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = dev;

	data->regmap = devm_regmap_init_i2c(client, &tpa6130a2_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	अगर (pdata) अणु
		data->घातer_gpio = pdata->घातer_gpio;
	पूर्ण अन्यथा अगर (np) अणु
		data->घातer_gpio = of_get_named_gpio(np, "power-gpio", 0);
	पूर्ण अन्यथा अणु
		dev_err(dev, "Platform data not set\n");
		dump_stack();
		वापस -ENODEV;
	पूर्ण

	i2c_set_clientdata(client, data);

	data->id = id->driver_data;

	अगर (data->घातer_gpio >= 0) अणु
		ret = devm_gpio_request(dev, data->घातer_gpio,
					"tpa6130a2 enable");
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to request power GPIO (%d)\n",
				data->घातer_gpio);
			वापस ret;
		पूर्ण
		gpio_direction_output(data->घातer_gpio, 0);
	पूर्ण

	चयन (data->id) अणु
	शेष:
		dev_warn(dev, "Unknown TPA model (%d). Assuming 6130A2\n",
			 data->id);
		fallthrough;
	हाल TPA6130A2:
		regulator = "Vdd";
		अवरोध;
	हाल TPA6140A2:
		regulator = "AVdd";
		अवरोध;
	पूर्ण

	data->supply = devm_regulator_get(dev, regulator);
	अगर (IS_ERR(data->supply)) अणु
		ret = PTR_ERR(data->supply);
		dev_err(dev, "Failed to request supply: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tpa6130a2_घातer(data, true);
	अगर (ret != 0)
		वापस ret;


	/* Read version */
	regmap_पढ़ो(data->regmap, TPA6130A2_REG_VERSION, &version);
	version &= TPA6130A2_VERSION_MASK;
	अगर ((version != 1) && (version != 2))
		dev_warn(dev, "UNTESTED version detected (%d)\n", version);

	/* Disable the chip */
	ret = tpa6130a2_घातer(data, false);
	अगर (ret != 0)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(&client->dev,
			&tpa6130a2_component_driver, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tpa6130a2_id[] = अणु
	अणु "tpa6130a2", TPA6130A2 पूर्ण,
	अणु "tpa6140a2", TPA6140A2 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tpa6130a2_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tpa6130a2_of_match[] = अणु
	अणु .compatible = "ti,tpa6130a2", पूर्ण,
	अणु .compatible = "ti,tpa6140a2" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tpa6130a2_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tpa6130a2_i2c_driver = अणु
	.driver = अणु
		.name = "tpa6130a2",
		.of_match_table = of_match_ptr(tpa6130a2_of_match),
	पूर्ण,
	.probe = tpa6130a2_probe,
	.id_table = tpa6130a2_id,
पूर्ण;

module_i2c_driver(tpa6130a2_i2c_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("TPA6130A2 Headphone amplifier driver");
MODULE_LICENSE("GPL");
