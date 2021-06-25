<शैली गुरु>
/*
 * Battery driver क्रम LEGO MINDSTORMS EV3
 *
 * Copyright (C) 2017 David Lechner <david@lechnology.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.

 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>

काष्ठा lego_ev3_battery अणु
	काष्ठा iio_channel *iio_v;
	काष्ठा iio_channel *iio_i;
	काष्ठा gpio_desc *reअक्षरgeable_gpio;
	काष्ठा घातer_supply *psy;
	पूर्णांक technology;
	पूर्णांक v_max;
	पूर्णांक v_min;
पूर्ण;

अटल पूर्णांक lego_ev3_battery_get_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp,
					 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lego_ev3_battery *batt = घातer_supply_get_drvdata(psy);
	पूर्णांक ret, val2;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = batt->technology;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		/* battery voltage is iio channel * 2 + Vce of transistor */
		ret = iio_पढ़ो_channel_processed(batt->iio_v, &val->पूर्णांकval);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval *= 2000;
		val->पूर्णांकval += 50000;

		/* plus adjust क्रम shunt resistor drop */
		ret = iio_पढ़ो_channel_processed(batt->iio_i, &val2);
		अगर (ret)
			वापस ret;

		val2 *= 1000;
		val2 /= 15;
		val->पूर्णांकval += val2;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = batt->v_max;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = batt->v_min;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		/* battery current is iio channel / 15 / 0.05 ohms */
		ret = iio_पढ़ो_channel_processed(batt->iio_i, &val->पूर्णांकval);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval *= 20000;
		val->पूर्णांकval /= 15;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_SYSTEM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lego_ev3_battery_set_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp,
					 स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lego_ev3_battery *batt = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		/*
		 * Only allow changing technology from Unknown to NiMH. Li-ion
		 * batteries are स्वतःmatically detected and should not be
		 * overridden. Reअक्षरgeable AA batteries, on the other hand,
		 * cannot be स्वतःmatically detected, and so must be manually
		 * specअगरied. This should only be set once during प्रणाली init,
		 * so there is no mechanism to go back to Unknown.
		 */
		अगर (batt->technology != POWER_SUPPLY_TECHNOLOGY_UNKNOWN)
			वापस -EINVAL;
		चयन (val->पूर्णांकval) अणु
		हाल POWER_SUPPLY_TECHNOLOGY_NiMH:
			batt->technology = POWER_SUPPLY_TECHNOLOGY_NiMH;
			batt->v_max = 7800000;
			batt->v_min = 5400000;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lego_ev3_battery_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
						  क्रमागत घातer_supply_property psp)
अणु
	काष्ठा lego_ev3_battery *batt = घातer_supply_get_drvdata(psy);

	वापस psp == POWER_SUPPLY_PROP_TECHNOLOGY &&
		batt->technology == POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
पूर्ण

अटल क्रमागत घातer_supply_property lego_ev3_battery_props[] = अणु
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_SCOPE,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc lego_ev3_battery_desc = अणु
	.name			= "lego-ev3-battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= lego_ev3_battery_props,
	.num_properties		= ARRAY_SIZE(lego_ev3_battery_props),
	.get_property		= lego_ev3_battery_get_property,
	.set_property		= lego_ev3_battery_set_property,
	.property_is_ग_लिखोable	= lego_ev3_battery_property_is_ग_लिखोable,
पूर्ण;

अटल पूर्णांक lego_ev3_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lego_ev3_battery *batt;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक err;

	batt = devm_kzalloc(dev, माप(*batt), GFP_KERNEL);
	अगर (!batt)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, batt);

	batt->iio_v = devm_iio_channel_get(dev, "voltage");
	err = PTR_ERR_OR_ZERO(batt->iio_v);
	अगर (err)
		वापस dev_err_probe(dev, err,
				     "Failed to get voltage iio channel\n");

	batt->iio_i = devm_iio_channel_get(dev, "current");
	err = PTR_ERR_OR_ZERO(batt->iio_i);
	अगर (err)
		वापस dev_err_probe(dev, err,
				     "Failed to get current iio channel\n");

	batt->reअक्षरgeable_gpio = devm_gpiod_get(dev, "rechargeable", GPIOD_IN);
	err = PTR_ERR_OR_ZERO(batt->reअक्षरgeable_gpio);
	अगर (err)
		वापस dev_err_probe(dev, err,
				     "Failed to get rechargeable gpio\n");

	/*
	 * The reअक्षरgeable battery indication चयन cannot be changed without
	 * removing the battery, so we only need to पढ़ो it once.
	 */
	अगर (gpiod_get_value(batt->reअक्षरgeable_gpio)) अणु
		/* 2-cell Li-ion, 7.4V nominal */
		batt->technology = POWER_SUPPLY_TECHNOLOGY_LION;
		batt->v_max = 84000000;
		batt->v_min = 60000000;
	पूर्ण अन्यथा अणु
		/* 6x AA Alkaline, 9V nominal */
		batt->technology = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
		batt->v_max = 90000000;
		batt->v_min = 48000000;
	पूर्ण

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = batt;

	batt->psy = devm_घातer_supply_रेजिस्टर(dev, &lego_ev3_battery_desc,
					       &psy_cfg);
	err = PTR_ERR_OR_ZERO(batt->psy);
	अगर (err) अणु
		dev_err(dev, "failed to register power supply\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_lego_ev3_battery_match[] = अणु
	अणु .compatible = "lego,ev3-battery", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lego_ev3_battery_match);

अटल काष्ठा platक्रमm_driver lego_ev3_battery_driver = अणु
	.driver	= अणु
		.name		= "lego-ev3-battery",
		.of_match_table = of_lego_ev3_battery_match,
	पूर्ण,
	.probe	= lego_ev3_battery_probe,
पूर्ण;
module_platक्रमm_driver(lego_ev3_battery_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_DESCRIPTION("LEGO MINDSTORMS EV3 Battery Driver");
