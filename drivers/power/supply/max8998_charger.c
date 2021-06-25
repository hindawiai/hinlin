<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max8998_अक्षरger.c - Power supply consumer driver क्रम the Maxim 8998/LP3974
//
//  Copyright (C) 2009-2010 Samsung Electronics
//  MyungJoo Ham <myungjoo.ham@samsung.com>

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/max8998.h>
#समावेश <linux/mfd/max8998-निजी.h>

काष्ठा max8998_battery_data अणु
	काष्ठा device *dev;
	काष्ठा max8998_dev *iodev;
	काष्ठा घातer_supply *battery;
पूर्ण;

अटल क्रमागत घातer_supply_property max8998_battery_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT, /* the presence of battery */
	POWER_SUPPLY_PROP_ONLINE, /* अक्षरger is active or not */
	POWER_SUPPLY_PROP_STATUS, /* अक्षरger is अक्षरging/disअक्षरging/full */
पूर्ण;

/* Note that the अक्षरger control is करोne by a current regulator "CHARGER" */
अटल पूर्णांक max8998_battery_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max8998_battery_data *max8998 = घातer_supply_get_drvdata(psy);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक ret;
	u8 reg;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = max8998_पढ़ो_reg(i2c, MAX8998_REG_STATUS2, &reg);
		अगर (ret)
			वापस ret;
		अगर (reg & (1 << 4))
			val->पूर्णांकval = 0;
		अन्यथा
			val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = max8998_पढ़ो_reg(i2c, MAX8998_REG_STATUS2, &reg);
		अगर (ret)
			वापस ret;

		अगर (reg & (1 << 5))
			val->पूर्णांकval = 1;
		अन्यथा
			val->पूर्णांकval = 0;

		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = max8998_पढ़ो_reg(i2c, MAX8998_REG_STATUS2, &reg);
		अगर (ret)
			वापस ret;

		अगर (!(reg & (1 << 5))) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		पूर्ण अन्यथा अणु
			अगर (reg & (1 << 6))
				val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
			अन्यथा अगर (reg & (1 << 3))
				val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अन्यथा
				val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc max8998_battery_desc = अणु
	.name		= "max8998_pmic",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.get_property	= max8998_battery_get_property,
	.properties	= max8998_battery_props,
	.num_properties	= ARRAY_SIZE(max8998_battery_props),
पूर्ण;

अटल पूर्णांक max8998_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8998_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8998_platक्रमm_data *pdata = iodev->pdata;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा max8998_battery_data *max8998;
	काष्ठा i2c_client *i2c;
	पूर्णांक ret = 0;

	अगर (!pdata) अणु
		dev_err(pdev->dev.parent, "No platform init data supplied\n");
		वापस -ENODEV;
	पूर्ण

	max8998 = devm_kzalloc(&pdev->dev, माप(काष्ठा max8998_battery_data),
				GFP_KERNEL);
	अगर (!max8998)
		वापस -ENOMEM;

	max8998->dev = &pdev->dev;
	max8998->iodev = iodev;
	platक्रमm_set_drvdata(pdev, max8998);
	i2c = max8998->iodev->i2c;

	/* Setup "End of Charge" */
	/* If EOC value equals 0,
	 * reमुख्य value set from bootloader or शेष value */
	अगर (pdata->eoc >= 10 && pdata->eoc <= 45) अणु
		max8998_update_reg(i2c, MAX8998_REG_CHGR1,
				(pdata->eoc / 5 - 2) << 5, 0x7 << 5);
	पूर्ण अन्यथा अगर (pdata->eoc == 0) अणु
		dev_dbg(max8998->dev,
			"EOC value not set: leave it unchanged.\n");
	पूर्ण अन्यथा अणु
		dev_err(max8998->dev, "Invalid EOC value\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup Charge Restart Level */
	चयन (pdata->restart) अणु
	हाल 100:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x1 << 3, 0x3 << 3);
		अवरोध;
	हाल 150:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x0 << 3, 0x3 << 3);
		अवरोध;
	हाल 200:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x2 << 3, 0x3 << 3);
		अवरोध;
	हाल -1:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x3 << 3, 0x3 << 3);
		अवरोध;
	हाल 0:
		dev_dbg(max8998->dev,
			"Restart Level not set: leave it unchanged.\n");
		अवरोध;
	शेष:
		dev_err(max8998->dev, "Invalid Restart Level\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup Charge Full Timeout */
	चयन (pdata->समयout) अणु
	हाल 5:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x0 << 4, 0x3 << 4);
		अवरोध;
	हाल 6:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x1 << 4, 0x3 << 4);
		अवरोध;
	हाल 7:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x2 << 4, 0x3 << 4);
		अवरोध;
	हाल -1:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x3 << 4, 0x3 << 4);
		अवरोध;
	हाल 0:
		dev_dbg(max8998->dev,
			"Full Timeout not set: leave it unchanged.\n");
		अवरोध;
	शेष:
		dev_err(max8998->dev, "Invalid Full Timeout value\n");
		वापस -EINVAL;
	पूर्ण

	psy_cfg.drv_data = max8998;

	max8998->battery = devm_घातer_supply_रेजिस्टर(max8998->dev,
						      &max8998_battery_desc,
						      &psy_cfg);
	अगर (IS_ERR(max8998->battery)) अणु
		ret = PTR_ERR(max8998->battery);
		dev_err(max8998->dev, "failed: power supply register: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max8998_battery_id[] = अणु
	अणु "max8998-battery", TYPE_MAX8998 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver max8998_battery_driver = अणु
	.driver = अणु
		.name = "max8998-battery",
	पूर्ण,
	.probe = max8998_battery_probe,
	.id_table = max8998_battery_id,
पूर्ण;

module_platक्रमm_driver(max8998_battery_driver);

MODULE_DESCRIPTION("MAXIM 8998 battery control driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:max8998-battery");
