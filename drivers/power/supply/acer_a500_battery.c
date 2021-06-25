<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Battery driver क्रम Acer Iconia Tab A500.
 *
 * Copyright 2020 GRATE-driver project.
 *
 * Based on करोwnstream driver from Acer Inc.
 * Based on NVIDIA Gas Gauge driver क्रम SBS Compliant Batteries.
 *
 * Copyright (c) 2010, NVIDIA Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

क्रमागत अणु
	REG_CAPACITY,
	REG_VOLTAGE,
	REG_CURRENT,
	REG_DESIGN_CAPACITY,
	REG_TEMPERATURE,
पूर्ण;

#घोषणा EC_DATA(_reg, _psp) अणु			\
	.psp = POWER_SUPPLY_PROP_ ## _psp,	\
	.reg = _reg,				\
पूर्ण

अटल स्थिर काष्ठा battery_रेजिस्टर अणु
	क्रमागत घातer_supply_property psp;
	अचिन्हित पूर्णांक reg;
पूर्ण ec_data[] = अणु
	[REG_CAPACITY]		= EC_DATA(0x00, CAPACITY),
	[REG_VOLTAGE]		= EC_DATA(0x01, VOLTAGE_NOW),
	[REG_CURRENT]		= EC_DATA(0x03, CURRENT_NOW),
	[REG_DESIGN_CAPACITY]	= EC_DATA(0x08, CHARGE_FULL_DESIGN),
	[REG_TEMPERATURE]	= EC_DATA(0x0a, TEMP),
पूर्ण;

अटल स्थिर क्रमागत घातer_supply_property a500_battery_properties[] = अणु
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

काष्ठा a500_battery अणु
	काष्ठा delayed_work poll_work;
	काष्ठा घातer_supply *psy;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक capacity;
पूर्ण;

अटल bool a500_battery_update_capacity(काष्ठा a500_battery *bat)
अणु
	अचिन्हित पूर्णांक capacity;
	पूर्णांक err;

	err = regmap_पढ़ो(bat->regmap, ec_data[REG_CAPACITY].reg, &capacity);
	अगर (err)
		वापस false;

	/* capacity can be >100% even अगर max value is 100% */
	capacity = min(capacity, 100u);

	अगर (bat->capacity != capacity) अणु
		bat->capacity = capacity;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक a500_battery_get_status(काष्ठा a500_battery *bat)
अणु
	अगर (bat->capacity < 100) अणु
		अगर (घातer_supply_am_i_supplied(bat->psy))
			वापस POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			वापस POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	वापस POWER_SUPPLY_STATUS_FULL;
पूर्ण

अटल व्योम a500_battery_unit_adjusपंचांगent(काष्ठा device *dev,
					 क्रमागत घातer_supply_property psp,
					 जोड़ घातer_supply_propval *val)
अणु
	स्थिर अचिन्हित पूर्णांक base_unit_conversion = 1000;
	स्थिर अचिन्हित पूर्णांक temp_kelvin_to_celsius = 2731;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval *= base_unit_conversion;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval -= temp_kelvin_to_celsius;
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = !!val->पूर्णांकval;
		अवरोध;

	शेष:
		dev_dbg(dev,
			"%s: no need for unit conversion %d\n", __func__, psp);
	पूर्ण
पूर्ण

अटल पूर्णांक a500_battery_get_ec_data_index(काष्ठा device *dev,
					  क्रमागत घातer_supply_property psp)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * DESIGN_CAPACITY रेजिस्टर always वापसs a non-zero value अगर
	 * battery is connected and zero अगर disconnected, hence we'll use
	 * it क्रम judging the battery presence.
	 */
	अगर (psp == POWER_SUPPLY_PROP_PRESENT)
		psp = POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN;

	क्रम (i = 0; i < ARRAY_SIZE(ec_data); i++)
		अगर (psp == ec_data[i].psp)
			वापस i;

	dev_dbg(dev, "%s: invalid property %u\n", __func__, psp);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक a500_battery_get_property(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp,
				     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा a500_battery *bat = घातer_supply_get_drvdata(psy);
	काष्ठा device *dev = psy->dev.parent;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = a500_battery_get_status(bat);
		अवरोध;

	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		a500_battery_update_capacity(bat);
		val->पूर्णांकval = bat->capacity;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_PRESENT:
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = a500_battery_get_ec_data_index(dev, psp);
		अगर (ret < 0)
			अवरोध;

		ret = regmap_पढ़ो(bat->regmap, ec_data[ret].reg, &val->पूर्णांकval);
		अवरोध;

	शेष:
		dev_err(dev, "%s: invalid property %u\n", __func__, psp);
		वापस -EINVAL;
	पूर्ण

	अगर (!ret) अणु
		/* convert units to match requirements of घातer supply class */
		a500_battery_unit_adjusपंचांगent(dev, psp, val);
	पूर्ण

	dev_dbg(dev, "%s: property = %d, value = %x\n",
		__func__, psp, val->पूर्णांकval);

	/* वापस NODATA क्रम properties अगर battery not presents */
	अगर (ret)
		वापस -ENODATA;

	वापस 0;
पूर्ण

अटल व्योम a500_battery_poll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा a500_battery *bat;
	bool capacity_changed;

	bat = container_of(work, काष्ठा a500_battery, poll_work.work);
	capacity_changed = a500_battery_update_capacity(bat);

	अगर (capacity_changed)
		घातer_supply_changed(bat->psy);

	/* continuously send uevent notअगरication */
	schedule_delayed_work(&bat->poll_work, 30 * HZ);
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc a500_battery_desc = अणु
	.name = "ec-battery",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = a500_battery_properties,
	.get_property = a500_battery_get_property,
	.num_properties = ARRAY_SIZE(a500_battery_properties),
	.बाह्यal_घातer_changed = घातer_supply_changed,
पूर्ण;

अटल पूर्णांक a500_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा a500_battery *bat;

	bat = devm_kzalloc(&pdev->dev, माप(*bat), GFP_KERNEL);
	अगर (!bat)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, bat);

	psy_cfg.of_node = pdev->dev.parent->of_node;
	psy_cfg.drv_data = bat;

	bat->regmap = dev_get_regmap(pdev->dev.parent, "KB930");
	अगर (!bat->regmap)
		वापस -EINVAL;

	bat->psy = devm_घातer_supply_रेजिस्टर_no_ws(&pdev->dev,
						    &a500_battery_desc,
						    &psy_cfg);
	अगर (IS_ERR(bat->psy))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(bat->psy),
				     "failed to register battery\n");

	INIT_DELAYED_WORK(&bat->poll_work, a500_battery_poll_work);
	schedule_delayed_work(&bat->poll_work, HZ);

	वापस 0;
पूर्ण

अटल पूर्णांक a500_battery_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा a500_battery *bat = dev_get_drvdata(&pdev->dev);

	cancel_delayed_work_sync(&bat->poll_work);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused a500_battery_suspend(काष्ठा device *dev)
अणु
	काष्ठा a500_battery *bat = dev_get_drvdata(dev);

	cancel_delayed_work_sync(&bat->poll_work);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused a500_battery_resume(काष्ठा device *dev)
अणु
	काष्ठा a500_battery *bat = dev_get_drvdata(dev);

	schedule_delayed_work(&bat->poll_work, HZ);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(a500_battery_pm_ops,
			 a500_battery_suspend, a500_battery_resume);

अटल काष्ठा platक्रमm_driver a500_battery_driver = अणु
	.driver = अणु
		.name = "acer-a500-iconia-battery",
		.pm = &a500_battery_pm_ops,
	पूर्ण,
	.probe = a500_battery_probe,
	.हटाओ = a500_battery_हटाओ,
पूर्ण;
module_platक्रमm_driver(a500_battery_driver);

MODULE_DESCRIPTION("Battery gauge driver for Acer Iconia Tab A500");
MODULE_AUTHOR("Dmitry Osipenko <digetx@gmail.com>");
MODULE_ALIAS("platform:acer-a500-iconia-battery");
MODULE_LICENSE("GPL");
