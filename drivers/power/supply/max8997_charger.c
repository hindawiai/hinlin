<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max8997_अक्षरger.c - Power supply consumer driver क्रम the Maxim 8997/8966
//
//  Copyright (C) 2011 Samsung Electronics
//  MyungJoo Ham <myungjoo.ham@samsung.com>

#समावेश <linux/err.h>
#समावेश <linux/extcon.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/max8997.h>
#समावेश <linux/mfd/max8997-निजी.h>
#समावेश <linux/regulator/consumer.h>

/* MAX8997_REG_STATUS4 */
#घोषणा DCINOK_SHIFT		1
#घोषणा DCINOK_MASK		(1 << DCINOK_SHIFT)
#घोषणा DETBAT_SHIFT		2
#घोषणा DETBAT_MASK		(1 << DETBAT_SHIFT)

/* MAX8997_REG_MBCCTRL1 */
#घोषणा TFCH_SHIFT		4
#घोषणा TFCH_MASK		(7 << TFCH_SHIFT)

/* MAX8997_REG_MBCCTRL5 */
#घोषणा ITOPOFF_SHIFT		0
#घोषणा ITOPOFF_MASK		(0xF << ITOPOFF_SHIFT)

काष्ठा अक्षरger_data अणु
	काष्ठा device *dev;
	काष्ठा max8997_dev *iodev;
	काष्ठा घातer_supply *battery;
	काष्ठा regulator *reg;
	काष्ठा extcon_dev *edev;
	काष्ठा notअगरier_block extcon_nb;
	काष्ठा work_काष्ठा extcon_work;
पूर्ण;

अटल क्रमागत घातer_supply_property max8997_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS, /* "FULL", "CHARGING" or "DISCHARGING". */
	POWER_SUPPLY_PROP_PRESENT, /* the presence of battery */
	POWER_SUPPLY_PROP_ONLINE, /* अक्षरger is active or not */
पूर्ण;

/* Note that the अक्षरger control is करोne by a current regulator "CHARGER" */
अटल पूर्णांक max8997_battery_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा अक्षरger_data *अक्षरger = घातer_supply_get_drvdata(psy);
	काष्ठा i2c_client *i2c = अक्षरger->iodev->i2c;
	पूर्णांक ret;
	u8 reg;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = 0;
		ret = max8997_पढ़ो_reg(i2c, MAX8997_REG_STATUS4, &reg);
		अगर (ret)
			वापस ret;
		अगर ((reg & (1 << 0)) == 0x1)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा अगर ((reg & DCINOK_MASK))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;

		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = 0;
		ret = max8997_पढ़ो_reg(i2c, MAX8997_REG_STATUS4, &reg);
		अगर (ret)
			वापस ret;
		अगर ((reg & DETBAT_MASK) == 0x0)
			val->पूर्णांकval = 1;

		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = 0;
		ret = max8997_पढ़ो_reg(i2c, MAX8997_REG_STATUS4, &reg);
		अगर (ret)
			वापस ret;
		अगर (reg & DCINOK_MASK)
			val->पूर्णांकval = 1;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max8997_battery_extcon_evt_stop_work(व्योम *data)
अणु
	काष्ठा अक्षरger_data *अक्षरger = data;

	cancel_work_sync(&अक्षरger->extcon_work);
पूर्ण

अटल व्योम max8997_battery_extcon_evt_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अक्षरger_data *अक्षरger =
	    container_of(work, काष्ठा अक्षरger_data, extcon_work);
	काष्ठा extcon_dev *edev = अक्षरger->edev;
	पूर्णांक current_limit;

	अगर (extcon_get_state(edev, EXTCON_CHG_USB_SDP) > 0) अणु
		dev_dbg(अक्षरger->dev, "USB SDP charger is connected\n");
		current_limit = 450000;
	पूर्ण अन्यथा अगर (extcon_get_state(edev, EXTCON_CHG_USB_DCP) > 0) अणु
		dev_dbg(अक्षरger->dev, "USB DCP charger is connected\n");
		current_limit = 650000;
	पूर्ण अन्यथा अगर (extcon_get_state(edev, EXTCON_CHG_USB_FAST) > 0) अणु
		dev_dbg(अक्षरger->dev, "USB FAST charger is connected\n");
		current_limit = 650000;
	पूर्ण अन्यथा अगर (extcon_get_state(edev, EXTCON_CHG_USB_SLOW) > 0) अणु
		dev_dbg(अक्षरger->dev, "USB SLOW charger is connected\n");
		current_limit = 650000;
	पूर्ण अन्यथा अगर (extcon_get_state(edev, EXTCON_CHG_USB_CDP) > 0) अणु
		dev_dbg(अक्षरger->dev, "USB CDP charger is connected\n");
		current_limit = 650000;
	पूर्ण अन्यथा अणु
		dev_dbg(अक्षरger->dev, "USB charger is disconnected\n");
		current_limit = -1;
	पूर्ण

	अगर (current_limit > 0) अणु
		पूर्णांक ret = regulator_set_current_limit(अक्षरger->reg, current_limit, current_limit);

		अगर (ret) अणु
			dev_err(अक्षरger->dev, "failed to set current limit: %d\n", ret);
			वापस;
		पूर्ण
		ret = regulator_enable(अक्षरger->reg);
		अगर (ret)
			dev_err(अक्षरger->dev, "failed to enable regulator: %d\n", ret);
	पूर्ण अन्यथा अणु
		पूर्णांक ret  = regulator_disable(अक्षरger->reg);

		अगर (ret)
			dev_err(अक्षरger->dev, "failed to disable regulator: %d\n", ret);
	पूर्ण
पूर्ण

अटल पूर्णांक max8997_battery_extcon_evt(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *param)
अणु
	काष्ठा अक्षरger_data *अक्षरger =
		container_of(nb, काष्ठा अक्षरger_data, extcon_nb);
	schedule_work(&अक्षरger->extcon_work);
	वापस NOTIFY_OK;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc max8997_battery_desc = अणु
	.name		= "max8997_pmic",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.get_property	= max8997_battery_get_property,
	.properties	= max8997_battery_props,
	.num_properties	= ARRAY_SIZE(max8997_battery_props),
पूर्ण;

अटल पूर्णांक max8997_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा अक्षरger_data *अक्षरger;
	काष्ठा max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा i2c_client *i2c = iodev->i2c;
	काष्ठा max8997_platक्रमm_data *pdata = iodev->pdata;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data supplied.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->eoc_mA) अणु
		पूर्णांक val = (pdata->eoc_mA - 50) / 10;
		अगर (val < 0)
			val = 0;
		अगर (val > 0xf)
			val = 0xf;

		ret = max8997_update_reg(i2c, MAX8997_REG_MBCCTRL5,
				val << ITOPOFF_SHIFT, ITOPOFF_MASK);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Cannot use i2c bus.\n");
			वापस ret;
		पूर्ण
	पूर्ण
	चयन (pdata->समयout) अणु
	हाल 5:
		ret = max8997_update_reg(i2c, MAX8997_REG_MBCCTRL1,
				0x2 << TFCH_SHIFT, TFCH_MASK);
		अवरोध;
	हाल 6:
		ret = max8997_update_reg(i2c, MAX8997_REG_MBCCTRL1,
				0x3 << TFCH_SHIFT, TFCH_MASK);
		अवरोध;
	हाल 7:
		ret = max8997_update_reg(i2c, MAX8997_REG_MBCCTRL1,
				0x4 << TFCH_SHIFT, TFCH_MASK);
		अवरोध;
	हाल 0:
		ret = max8997_update_reg(i2c, MAX8997_REG_MBCCTRL1,
				0x7 << TFCH_SHIFT, TFCH_MASK);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "incorrect timeout value (%d)\n",
				pdata->समयout);
		वापस -EINVAL;
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Cannot use i2c bus.\n");
		वापस ret;
	पूर्ण

	अक्षरger = devm_kzalloc(&pdev->dev, माप(*अक्षरger), GFP_KERNEL);
	अगर (!अक्षरger)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, अक्षरger);

	अक्षरger->dev = &pdev->dev;
	अक्षरger->iodev = iodev;

	psy_cfg.drv_data = अक्षरger;

	अक्षरger->battery = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						 &max8997_battery_desc,
						 &psy_cfg);
	अगर (IS_ERR(अक्षरger->battery)) अणु
		dev_err(&pdev->dev, "failed: power supply register\n");
		वापस PTR_ERR(अक्षरger->battery);
	पूर्ण

	// grab regulator from parent device's node
	pdev->dev.of_node = iodev->dev->of_node;
	अक्षरger->reg = devm_regulator_get_optional(&pdev->dev, "charger");
	pdev->dev.of_node = np;
	अगर (IS_ERR(अक्षरger->reg)) अणु
		अगर (PTR_ERR(अक्षरger->reg) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(&pdev->dev, "couldn't get charger regulator\n");
	पूर्ण
	अक्षरger->edev = extcon_get_extcon_dev("max8997-muic");
	अगर (IS_ERR_OR_शून्य(अक्षरger->edev)) अणु
		अगर (!अक्षरger->edev)
			वापस -EPROBE_DEFER;
		dev_info(अक्षरger->dev, "couldn't get extcon device\n");
	पूर्ण

	अगर (!IS_ERR(अक्षरger->reg) && !IS_ERR_OR_शून्य(अक्षरger->edev)) अणु
		INIT_WORK(&अक्षरger->extcon_work, max8997_battery_extcon_evt_worker);
		ret = devm_add_action(&pdev->dev, max8997_battery_extcon_evt_stop_work, अक्षरger);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to add extcon evt stop action: %d\n", ret);
			वापस ret;
		पूर्ण
		अक्षरger->extcon_nb.notअगरier_call = max8997_battery_extcon_evt;
		ret = devm_extcon_रेजिस्टर_notअगरier_all(&pdev->dev, अक्षरger->edev,
							&अक्षरger->extcon_nb);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to register extcon notifier\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max8997_battery_id[] = अणु
	अणु "max8997-battery", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max8997_battery_id);

अटल काष्ठा platक्रमm_driver max8997_battery_driver = अणु
	.driver = अणु
		.name = "max8997-battery",
	पूर्ण,
	.probe = max8997_battery_probe,
	.id_table = max8997_battery_id,
पूर्ण;
module_platक्रमm_driver(max8997_battery_driver);

MODULE_DESCRIPTION("MAXIM 8997/8966 battery control driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_LICENSE("GPL");
