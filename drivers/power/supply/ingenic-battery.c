<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Battery driver क्रम the Ingenic JZ47xx SoCs
 * Copyright (c) 2019 Artur Rojek <contact@artur-rojek.eu>
 *
 * based on drivers/घातer/supply/jz4740-battery.c
 */

#समावेश <linux/iio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/property.h>

काष्ठा ingenic_battery अणु
	काष्ठा device *dev;
	काष्ठा iio_channel *channel;
	काष्ठा घातer_supply_desc desc;
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply_battery_info info;
पूर्ण;

अटल पूर्णांक ingenic_battery_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ingenic_battery *bat = घातer_supply_get_drvdata(psy);
	काष्ठा घातer_supply_battery_info *info = &bat->info;
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = iio_पढ़ो_channel_processed(bat->channel, &val->पूर्णांकval);
		val->पूर्णांकval *= 1000;
		अगर (val->पूर्णांकval < info->voltage_min_design_uv)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
		अन्यथा अगर (val->पूर्णांकval > info->voltage_max_design_uv)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		वापस ret;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = iio_पढ़ो_channel_processed(bat->channel, &val->पूर्णांकval);
		val->पूर्णांकval *= 1000;
		वापस ret;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = info->voltage_min_design_uv;
		वापस 0;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = info->voltage_max_design_uv;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Set the most appropriate IIO channel voltage reference scale
 * based on the battery's max voltage.
 */
अटल पूर्णांक ingenic_battery_set_scale(काष्ठा ingenic_battery *bat)
अणु
	स्थिर पूर्णांक *scale_raw;
	पूर्णांक scale_len, scale_type, best_idx = -1, best_mV, max_raw, i, ret;
	u64 max_mV;

	ret = iio_पढ़ो_max_channel_raw(bat->channel, &max_raw);
	अगर (ret) अणु
		dev_err(bat->dev, "Unable to read max raw channel value\n");
		वापस ret;
	पूर्ण

	ret = iio_पढ़ो_avail_channel_attribute(bat->channel, &scale_raw,
					       &scale_type, &scale_len,
					       IIO_CHAN_INFO_SCALE);
	अगर (ret < 0) अणु
		dev_err(bat->dev, "Unable to read channel avail scale\n");
		वापस ret;
	पूर्ण
	अगर (ret != IIO_AVAIL_LIST || scale_type != IIO_VAL_FRACTIONAL_LOG2)
		वापस -EINVAL;

	max_mV = bat->info.voltage_max_design_uv / 1000;

	क्रम (i = 0; i < scale_len; i += 2) अणु
		u64 scale_mV = (max_raw * scale_raw[i]) >> scale_raw[i + 1];

		अगर (scale_mV < max_mV)
			जारी;

		अगर (best_idx >= 0 && scale_mV > best_mV)
			जारी;

		best_mV = scale_mV;
		best_idx = i;
	पूर्ण

	अगर (best_idx < 0) अणु
		dev_err(bat->dev, "Unable to find matching voltage scale\n");
		वापस -EINVAL;
	पूर्ण

	/* Only set scale अगर there is more than one (fractional) entry */
	अगर (scale_len > 2) अणु
		ret = iio_ग_लिखो_channel_attribute(bat->channel,
						  scale_raw[best_idx],
						  scale_raw[best_idx + 1],
						  IIO_CHAN_INFO_SCALE);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property ingenic_battery_properties[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
पूर्ण;

अटल पूर्णांक ingenic_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ingenic_battery *bat;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा घातer_supply_desc *desc;
	पूर्णांक ret;

	bat = devm_kzalloc(dev, माप(*bat), GFP_KERNEL);
	अगर (!bat)
		वापस -ENOMEM;

	bat->dev = dev;
	bat->channel = devm_iio_channel_get(dev, "battery");
	अगर (IS_ERR(bat->channel))
		वापस PTR_ERR(bat->channel);

	desc = &bat->desc;
	desc->name = "jz-battery";
	desc->type = POWER_SUPPLY_TYPE_BATTERY;
	desc->properties = ingenic_battery_properties;
	desc->num_properties = ARRAY_SIZE(ingenic_battery_properties);
	desc->get_property = ingenic_battery_get_property;
	psy_cfg.drv_data = bat;
	psy_cfg.of_node = dev->of_node;

	bat->battery = devm_घातer_supply_रेजिस्टर(dev, desc, &psy_cfg);
	अगर (IS_ERR(bat->battery))
		वापस dev_err_probe(dev, PTR_ERR(bat->battery),
				     "Unable to register battery\n");

	ret = घातer_supply_get_battery_info(bat->battery, &bat->info);
	अगर (ret) अणु
		dev_err(dev, "Unable to get battery info: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (bat->info.voltage_min_design_uv < 0) अणु
		dev_err(dev, "Unable to get voltage min design\n");
		वापस bat->info.voltage_min_design_uv;
	पूर्ण
	अगर (bat->info.voltage_max_design_uv < 0) अणु
		dev_err(dev, "Unable to get voltage max design\n");
		वापस bat->info.voltage_max_design_uv;
	पूर्ण

	वापस ingenic_battery_set_scale(bat);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ingenic_battery_of_match[] = अणु
	अणु .compatible = "ingenic,jz4740-battery", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_battery_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ingenic_battery_driver = अणु
	.driver = अणु
		.name = "ingenic-battery",
		.of_match_table = of_match_ptr(ingenic_battery_of_match),
	पूर्ण,
	.probe = ingenic_battery_probe,
पूर्ण;
module_platक्रमm_driver(ingenic_battery_driver);

MODULE_DESCRIPTION("Battery driver for Ingenic JZ47xx SoCs");
MODULE_AUTHOR("Artur Rojek <contact@artur-rojek.eu>");
MODULE_LICENSE("GPL");
