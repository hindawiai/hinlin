<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Fuel gauge driver क्रम Richtek RT5033
 *
 * Copyright (C) 2014 Samsung Electronics, Co., Ltd.
 * Author: Beomho Seo <beomho.seo@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/rt5033-निजी.h>
#समावेश <linux/mfd/rt5033.h>

अटल पूर्णांक rt5033_battery_get_capacity(काष्ठा i2c_client *client)
अणु
	काष्ठा rt5033_battery *battery = i2c_get_clientdata(client);
	u32 msb;

	regmap_पढ़ो(battery->regmap, RT5033_FUEL_REG_SOC_H, &msb);

	वापस msb;
पूर्ण

अटल पूर्णांक rt5033_battery_get_present(काष्ठा i2c_client *client)
अणु
	काष्ठा rt5033_battery *battery = i2c_get_clientdata(client);
	u32 val;

	regmap_पढ़ो(battery->regmap, RT5033_FUEL_REG_CONFIG_L, &val);

	वापस (val & RT5033_FUEL_BAT_PRESENT) ? true : false;
पूर्ण

अटल पूर्णांक rt5033_battery_get_watt_prop(काष्ठा i2c_client *client,
		क्रमागत घातer_supply_property psp)
अणु
	काष्ठा rt5033_battery *battery = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक regh, regl;
	पूर्णांक ret;
	u32 msb, lsb;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		regh = RT5033_FUEL_REG_VBAT_H;
		regl = RT5033_FUEL_REG_VBAT_L;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		regh = RT5033_FUEL_REG_AVG_VOLT_H;
		regl = RT5033_FUEL_REG_AVG_VOLT_L;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_OCV:
		regh = RT5033_FUEL_REG_OCV_H;
		regl = RT5033_FUEL_REG_OCV_L;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_पढ़ो(battery->regmap, regh, &msb);
	regmap_पढ़ो(battery->regmap, regl, &lsb);

	ret = ((msb << 4) + (lsb >> 4)) * 1250 / 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक rt5033_battery_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा rt5033_battery *battery = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
	हाल POWER_SUPPLY_PROP_VOLTAGE_OCV:
		val->पूर्णांकval = rt5033_battery_get_watt_prop(battery->client,
									psp);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = rt5033_battery_get_present(battery->client);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = rt5033_battery_get_capacity(battery->client);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property rt5033_battery_props[] = अणु
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_OCV,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5033_battery_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= RT5033_FUEL_REG_END,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc rt5033_battery_desc = अणु
	.name		= "rt5033-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.get_property	= rt5033_battery_get_property,
	.properties	= rt5033_battery_props,
	.num_properties	= ARRAY_SIZE(rt5033_battery_props),
पूर्ण;

अटल पूर्णांक rt5033_battery_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा rt5033_battery *battery;
	u32 ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		वापस -EIO;

	battery = devm_kzalloc(&client->dev, माप(*battery), GFP_KERNEL);
	अगर (!battery)
		वापस -ENOMEM;

	battery->client = client;
	battery->regmap = devm_regmap_init_i2c(client,
			&rt5033_battery_regmap_config);
	अगर (IS_ERR(battery->regmap)) अणु
		dev_err(&client->dev, "Failed to initialize regmap\n");
		वापस -EINVAL;
	पूर्ण

	i2c_set_clientdata(client, battery);
	psy_cfg.drv_data = battery;

	battery->psy = घातer_supply_रेजिस्टर(&client->dev,
					     &rt5033_battery_desc, &psy_cfg);
	अगर (IS_ERR(battery->psy)) अणु
		dev_err(&client->dev, "Failed to register power supply\n");
		ret = PTR_ERR(battery->psy);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5033_battery_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rt5033_battery *battery = i2c_get_clientdata(client);

	घातer_supply_unरेजिस्टर(battery->psy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rt5033_battery_id[] = अणु
	अणु "rt5033-battery", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5033_battery_id);

अटल काष्ठा i2c_driver rt5033_battery_driver = अणु
	.driver = अणु
		.name = "rt5033-battery",
	पूर्ण,
	.probe = rt5033_battery_probe,
	.हटाओ = rt5033_battery_हटाओ,
	.id_table = rt5033_battery_id,
पूर्ण;
module_i2c_driver(rt5033_battery_driver);

MODULE_DESCRIPTION("Richtek RT5033 fuel gauge driver");
MODULE_AUTHOR("Beomho Seo <beomho.seo@samsung.com>");
MODULE_LICENSE("GPL");
