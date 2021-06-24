<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 BayLibre SAS
// Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
//
// Battery अक्षरger driver क्रम MAXIM 77650/77651 अक्षरger/घातer-supply.

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/max77650.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>

#घोषणा MAX77650_CHARGER_ENABLED		BIT(0)
#घोषणा MAX77650_CHARGER_DISABLED		0x00
#घोषणा MAX77650_CHARGER_CHG_EN_MASK		BIT(0)

#घोषणा MAX77650_CHG_DETAILS_MASK		GENMASK(7, 4)
#घोषणा MAX77650_CHG_DETAILS_BITS(_reg) \
		(((_reg) & MAX77650_CHG_DETAILS_MASK) >> 4)

/* Charger is OFF. */
#घोषणा MAX77650_CHG_OFF			0x00
/* Charger is in prequalअगरication mode. */
#घोषणा MAX77650_CHG_PREQ			0x01
/* Charger is in fast-अक्षरge स्थिरant current mode. */
#घोषणा MAX77650_CHG_ON_CURR			0x02
/* Charger is in JEITA modअगरied fast-अक्षरge स्थिरant-current mode. */
#घोषणा MAX77650_CHG_ON_CURR_JEITA		0x03
/* Charger is in fast-अक्षरge स्थिरant-voltage mode. */
#घोषणा MAX77650_CHG_ON_VOLT			0x04
/* Charger is in JEITA modअगरied fast-अक्षरge स्थिरant-voltage mode. */
#घोषणा MAX77650_CHG_ON_VOLT_JEITA		0x05
/* Charger is in top-off mode. */
#घोषणा MAX77650_CHG_ON_TOPOFF			0x06
/* Charger is in JEITA modअगरied top-off mode. */
#घोषणा MAX77650_CHG_ON_TOPOFF_JEITA		0x07
/* Charger is करोne. */
#घोषणा MAX77650_CHG_DONE			0x08
/* Charger is JEITA modअगरied करोne. */
#घोषणा MAX77650_CHG_DONE_JEITA			0x09
/* Charger is suspended due to a prequalअगरication समयr fault. */
#घोषणा MAX77650_CHG_SUSP_PREQ_TIM_FAULT	0x0a
/* Charger is suspended due to a fast-अक्षरge समयr fault. */
#घोषणा MAX77650_CHG_SUSP_FAST_CHG_TIM_FAULT	0x0b
/* Charger is suspended due to a battery temperature fault. */
#घोषणा MAX77650_CHG_SUSP_BATT_TEMP_FAULT	0x0c

#घोषणा MAX77650_CHGIN_DETAILS_MASK		GENMASK(3, 2)
#घोषणा MAX77650_CHGIN_DETAILS_BITS(_reg) \
		(((_reg) & MAX77650_CHGIN_DETAILS_MASK) >> 2)

#घोषणा MAX77650_CHGIN_UNDERVOLTAGE_LOCKOUT	0x00
#घोषणा MAX77650_CHGIN_OVERVOLTAGE_LOCKOUT	0x01
#घोषणा MAX77650_CHGIN_OKAY			0x11

#घोषणा MAX77650_CHARGER_CHG_MASK	BIT(1)
#घोषणा MAX77650_CHARGER_CHG_CHARGING(_reg) \
		(((_reg) & MAX77650_CHARGER_CHG_MASK) > 1)

#घोषणा MAX77650_CHARGER_VCHGIN_MIN_MASK	0xc0
#घोषणा MAX77650_CHARGER_VCHGIN_MIN_SHIFT(_val)	((_val) << 5)

#घोषणा MAX77650_CHARGER_ICHGIN_LIM_MASK	0x1c
#घोषणा MAX77650_CHARGER_ICHGIN_LIM_SHIFT(_val)	((_val) << 2)

काष्ठा max77650_अक्षरger_data अणु
	काष्ठा regmap *map;
	काष्ठा device *dev;
पूर्ण;

अटल क्रमागत घातer_supply_property max77650_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CHARGE_TYPE
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max77650_अक्षरger_vchgin_min_table[] = अणु
	4000000, 4100000, 4200000, 4300000, 4400000, 4500000, 4600000, 4700000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max77650_अक्षरger_ichgin_lim_table[] = अणु
	95000, 190000, 285000, 380000, 475000
पूर्ण;

अटल पूर्णांक max77650_अक्षरger_set_vchgin_min(काष्ठा max77650_अक्षरger_data *chg,
					   अचिन्हित पूर्णांक val)
अणु
	पूर्णांक i, rv;

	क्रम (i = 0; i < ARRAY_SIZE(max77650_अक्षरger_vchgin_min_table); i++) अणु
		अगर (val == max77650_अक्षरger_vchgin_min_table[i]) अणु
			rv = regmap_update_bits(chg->map,
					MAX77650_REG_CNFG_CHG_B,
					MAX77650_CHARGER_VCHGIN_MIN_MASK,
					MAX77650_CHARGER_VCHGIN_MIN_SHIFT(i));
			अगर (rv)
				वापस rv;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max77650_अक्षरger_set_ichgin_lim(काष्ठा max77650_अक्षरger_data *chg,
					   अचिन्हित पूर्णांक val)
अणु
	पूर्णांक i, rv;

	क्रम (i = 0; i < ARRAY_SIZE(max77650_अक्षरger_ichgin_lim_table); i++) अणु
		अगर (val == max77650_अक्षरger_ichgin_lim_table[i]) अणु
			rv = regmap_update_bits(chg->map,
					MAX77650_REG_CNFG_CHG_B,
					MAX77650_CHARGER_ICHGIN_LIM_MASK,
					MAX77650_CHARGER_ICHGIN_LIM_SHIFT(i));
			अगर (rv)
				वापस rv;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max77650_अक्षरger_enable(काष्ठा max77650_अक्षरger_data *chg)
अणु
	पूर्णांक rv;

	rv = regmap_update_bits(chg->map,
				MAX77650_REG_CNFG_CHG_B,
				MAX77650_CHARGER_CHG_EN_MASK,
				MAX77650_CHARGER_ENABLED);
	अगर (rv)
		dev_err(chg->dev, "unable to enable the charger: %d\n", rv);

	वापस rv;
पूर्ण

अटल पूर्णांक max77650_अक्षरger_disable(काष्ठा max77650_अक्षरger_data *chg)
अणु
	पूर्णांक rv;

	rv = regmap_update_bits(chg->map,
				MAX77650_REG_CNFG_CHG_B,
				MAX77650_CHARGER_CHG_EN_MASK,
				MAX77650_CHARGER_DISABLED);
	अगर (rv)
		dev_err(chg->dev, "unable to disable the charger: %d\n", rv);

	वापस rv;
पूर्ण

अटल irqवापस_t max77650_अक्षरger_check_status(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77650_अक्षरger_data *chg = data;
	पूर्णांक rv, reg;

	rv = regmap_पढ़ो(chg->map, MAX77650_REG_STAT_CHG_B, &reg);
	अगर (rv) अणु
		dev_err(chg->dev,
			"unable to read the charger status: %d\n", rv);
		वापस IRQ_HANDLED;
	पूर्ण

	चयन (MAX77650_CHGIN_DETAILS_BITS(reg)) अणु
	हाल MAX77650_CHGIN_UNDERVOLTAGE_LOCKOUT:
		dev_err(chg->dev, "undervoltage lockout detected, disabling charger\n");
		max77650_अक्षरger_disable(chg);
		अवरोध;
	हाल MAX77650_CHGIN_OVERVOLTAGE_LOCKOUT:
		dev_err(chg->dev, "overvoltage lockout detected, disabling charger\n");
		max77650_अक्षरger_disable(chg);
		अवरोध;
	हाल MAX77650_CHGIN_OKAY:
		max77650_अक्षरger_enable(chg);
		अवरोध;
	शेष:
		/* May be 0x10 - debouncing */
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max77650_अक्षरger_get_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp,
					 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max77650_अक्षरger_data *chg = घातer_supply_get_drvdata(psy);
	पूर्णांक rv, reg;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		rv = regmap_पढ़ो(chg->map, MAX77650_REG_STAT_CHG_B, &reg);
		अगर (rv)
			वापस rv;

		अगर (MAX77650_CHARGER_CHG_CHARGING(reg)) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		पूर्ण

		चयन (MAX77650_CHG_DETAILS_BITS(reg)) अणु
		हाल MAX77650_CHG_OFF:
		हाल MAX77650_CHG_SUSP_PREQ_TIM_FAULT:
		हाल MAX77650_CHG_SUSP_FAST_CHG_TIM_FAULT:
		हाल MAX77650_CHG_SUSP_BATT_TEMP_FAULT:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
		हाल MAX77650_CHG_PREQ:
		हाल MAX77650_CHG_ON_CURR:
		हाल MAX77650_CHG_ON_CURR_JEITA:
		हाल MAX77650_CHG_ON_VOLT:
		हाल MAX77650_CHG_ON_VOLT_JEITA:
		हाल MAX77650_CHG_ON_TOPOFF:
		हाल MAX77650_CHG_ON_TOPOFF_JEITA:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल MAX77650_CHG_DONE:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		rv = regmap_पढ़ो(chg->map, MAX77650_REG_STAT_CHG_B, &reg);
		अगर (rv)
			वापस rv;

		val->पूर्णांकval = MAX77650_CHARGER_CHG_CHARGING(reg);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		rv = regmap_पढ़ो(chg->map, MAX77650_REG_STAT_CHG_B, &reg);
		अगर (rv)
			वापस rv;

		अगर (!MAX77650_CHARGER_CHG_CHARGING(reg)) अणु
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			अवरोध;
		पूर्ण

		चयन (MAX77650_CHG_DETAILS_BITS(reg)) अणु
		हाल MAX77650_CHG_PREQ:
		हाल MAX77650_CHG_ON_CURR:
		हाल MAX77650_CHG_ON_CURR_JEITA:
		हाल MAX77650_CHG_ON_VOLT:
		हाल MAX77650_CHG_ON_VOLT_JEITA:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
			अवरोध;
		हाल MAX77650_CHG_ON_TOPOFF:
		हाल MAX77650_CHG_ON_TOPOFF_JEITA:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc max77650_battery_desc = अणु
	.name		= "max77650",
	.type		= POWER_SUPPLY_TYPE_USB,
	.get_property	= max77650_अक्षरger_get_property,
	.properties	= max77650_अक्षरger_properties,
	.num_properties	= ARRAY_SIZE(max77650_अक्षरger_properties),
पूर्ण;

अटल पूर्णांक max77650_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config pscfg = अणुपूर्ण;
	काष्ठा max77650_अक्षरger_data *chg;
	काष्ठा घातer_supply *battery;
	काष्ठा device *dev, *parent;
	पूर्णांक rv, chg_irq, chgin_irq;
	अचिन्हित पूर्णांक prop;

	dev = &pdev->dev;
	parent = dev->parent;

	chg = devm_kzalloc(dev, माप(*chg), GFP_KERNEL);
	अगर (!chg)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chg);

	chg->map = dev_get_regmap(parent, शून्य);
	अगर (!chg->map)
		वापस -ENODEV;

	chg->dev = dev;

	pscfg.of_node = dev->of_node;
	pscfg.drv_data = chg;

	chg_irq = platक्रमm_get_irq_byname(pdev, "CHG");
	अगर (chg_irq < 0)
		वापस chg_irq;

	chgin_irq = platक्रमm_get_irq_byname(pdev, "CHGIN");
	अगर (chgin_irq < 0)
		वापस chgin_irq;

	rv = devm_request_any_context_irq(dev, chg_irq,
					  max77650_अक्षरger_check_status,
					  IRQF_ONESHOT, "chg", chg);
	अगर (rv < 0)
		वापस rv;

	rv = devm_request_any_context_irq(dev, chgin_irq,
					  max77650_अक्षरger_check_status,
					  IRQF_ONESHOT, "chgin", chg);
	अगर (rv < 0)
		वापस rv;

	battery = devm_घातer_supply_रेजिस्टर(dev,
					     &max77650_battery_desc, &pscfg);
	अगर (IS_ERR(battery))
		वापस PTR_ERR(battery);

	rv = of_property_पढ़ो_u32(dev->of_node,
				  "input-voltage-min-microvolt", &prop);
	अगर (rv == 0) अणु
		rv = max77650_अक्षरger_set_vchgin_min(chg, prop);
		अगर (rv)
			वापस rv;
	पूर्ण

	rv = of_property_पढ़ो_u32(dev->of_node,
				  "input-current-limit-microamp", &prop);
	अगर (rv == 0) अणु
		rv = max77650_अक्षरger_set_ichgin_lim(chg, prop);
		अगर (rv)
			वापस rv;
	पूर्ण

	वापस max77650_अक्षरger_enable(chg);
पूर्ण

अटल पूर्णांक max77650_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77650_अक्षरger_data *chg = platक्रमm_get_drvdata(pdev);

	वापस max77650_अक्षरger_disable(chg);
पूर्ण

अटल स्थिर काष्ठा of_device_id max77650_अक्षरger_of_match[] = अणु
	अणु .compatible = "maxim,max77650-charger" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max77650_अक्षरger_of_match);

अटल काष्ठा platक्रमm_driver max77650_अक्षरger_driver = अणु
	.driver = अणु
		.name = "max77650-charger",
		.of_match_table = max77650_अक्षरger_of_match,
	पूर्ण,
	.probe = max77650_अक्षरger_probe,
	.हटाओ = max77650_अक्षरger_हटाओ,
पूर्ण;
module_platक्रमm_driver(max77650_अक्षरger_driver);

MODULE_DESCRIPTION("MAXIM 77650/77651 charger driver");
MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:max77650-charger");
