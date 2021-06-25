<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery measurement code क्रम Zipit Z2
 *
 * Copyright (C) 2009 Peter Edwards <sweetlilmre@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/z2_battery.h>

#घोषणा	Z2_DEFAULT_NAME	"Z2"

काष्ठा z2_अक्षरger अणु
	काष्ठा z2_battery_info		*info;
	काष्ठा gpio_desc		*अक्षरge_gpiod;
	पूर्णांक				bat_status;
	काष्ठा i2c_client		*client;
	काष्ठा घातer_supply		*batt_ps;
	काष्ठा घातer_supply_desc	batt_ps_desc;
	काष्ठा mutex			work_lock;
	काष्ठा work_काष्ठा		bat_work;
पूर्ण;

अटल अचिन्हित दीर्घ z2_पढ़ो_bat(काष्ठा z2_अक्षरger *अक्षरger)
अणु
	पूर्णांक data;
	data = i2c_smbus_पढ़ो_byte_data(अक्षरger->client,
					अक्षरger->info->batt_I2C_reg);
	अगर (data < 0)
		वापस 0;

	वापस data * अक्षरger->info->batt_mult / अक्षरger->info->batt_भाग;
पूर्ण

अटल पूर्णांक z2_batt_get_property(काष्ठा घातer_supply *batt_ps,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा z2_अक्षरger *अक्षरger = घातer_supply_get_drvdata(batt_ps);
	काष्ठा z2_battery_info *info = अक्षरger->info;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = अक्षरger->bat_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = info->batt_tech;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (info->batt_I2C_reg >= 0)
			val->पूर्णांकval = z2_पढ़ो_bat(अक्षरger);
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		अगर (info->max_voltage >= 0)
			val->पूर्णांकval = info->max_voltage;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		अगर (info->min_voltage >= 0)
			val->पूर्णांकval = info->min_voltage;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम z2_batt_ext_घातer_changed(काष्ठा घातer_supply *batt_ps)
अणु
	काष्ठा z2_अक्षरger *अक्षरger = घातer_supply_get_drvdata(batt_ps);

	schedule_work(&अक्षरger->bat_work);
पूर्ण

अटल व्योम z2_batt_update(काष्ठा z2_अक्षरger *अक्षरger)
अणु
	पूर्णांक old_status = अक्षरger->bat_status;

	mutex_lock(&अक्षरger->work_lock);

	अक्षरger->bat_status = अक्षरger->अक्षरge_gpiod ?
		(gpiod_get_value(अक्षरger->अक्षरge_gpiod) ?
		POWER_SUPPLY_STATUS_CHARGING :
		POWER_SUPPLY_STATUS_DISCHARGING) :
		POWER_SUPPLY_STATUS_UNKNOWN;

	अगर (old_status != अक्षरger->bat_status) अणु
		pr_debug("%s: %i -> %i\n", अक्षरger->batt_ps->desc->name,
				old_status,
				अक्षरger->bat_status);
		घातer_supply_changed(अक्षरger->batt_ps);
	पूर्ण

	mutex_unlock(&अक्षरger->work_lock);
पूर्ण

अटल व्योम z2_batt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा z2_अक्षरger *अक्षरger;
	अक्षरger = container_of(work, काष्ठा z2_अक्षरger, bat_work);
	z2_batt_update(अक्षरger);
पूर्ण

अटल irqवापस_t z2_अक्षरge_चयन_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा z2_अक्षरger *अक्षरger = devid;
	schedule_work(&अक्षरger->bat_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक z2_batt_ps_init(काष्ठा z2_अक्षरger *अक्षरger, पूर्णांक props)
अणु
	पूर्णांक i = 0;
	क्रमागत घातer_supply_property *prop;
	काष्ठा z2_battery_info *info = अक्षरger->info;

	अगर (अक्षरger->अक्षरge_gpiod)
		props++;	/* POWER_SUPPLY_PROP_STATUS */
	अगर (info->batt_tech >= 0)
		props++;	/* POWER_SUPPLY_PROP_TECHNOLOGY */
	अगर (info->batt_I2C_reg >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_NOW */
	अगर (info->max_voltage >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_MAX */
	अगर (info->min_voltage >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_MIN */

	prop = kसुस्मृति(props, माप(*prop), GFP_KERNEL);
	अगर (!prop)
		वापस -ENOMEM;

	prop[i++] = POWER_SUPPLY_PROP_PRESENT;
	अगर (अक्षरger->अक्षरge_gpiod)
		prop[i++] = POWER_SUPPLY_PROP_STATUS;
	अगर (info->batt_tech >= 0)
		prop[i++] = POWER_SUPPLY_PROP_TECHNOLOGY;
	अगर (info->batt_I2C_reg >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_NOW;
	अगर (info->max_voltage >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_MAX;
	अगर (info->min_voltage >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_MIN;

	अगर (!info->batt_name) अणु
		dev_info(&अक्षरger->client->dev,
				"Please consider setting proper battery "
				"name in platform definition file, falling "
				"back to name \" Z2_DEFAULT_NAME \"\n");
		अक्षरger->batt_ps_desc.name = Z2_DEFAULT_NAME;
	पूर्ण अन्यथा
		अक्षरger->batt_ps_desc.name = info->batt_name;

	अक्षरger->batt_ps_desc.properties	= prop;
	अक्षरger->batt_ps_desc.num_properties	= props;
	अक्षरger->batt_ps_desc.type		= POWER_SUPPLY_TYPE_BATTERY;
	अक्षरger->batt_ps_desc.get_property	= z2_batt_get_property;
	अक्षरger->batt_ps_desc.बाह्यal_घातer_changed =
						z2_batt_ext_घातer_changed;
	अक्षरger->batt_ps_desc.use_क्रम_apm	= 1;

	वापस 0;
पूर्ण

अटल पूर्णांक z2_batt_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = 0;
	पूर्णांक props = 1;	/* POWER_SUPPLY_PROP_PRESENT */
	काष्ठा z2_अक्षरger *अक्षरger;
	काष्ठा z2_battery_info *info = client->dev.platक्रमm_data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

	अगर (info == शून्य) अणु
		dev_err(&client->dev,
			"Please set platform device platform_data"
			" to a valid z2_battery_info pointer!\n");
		वापस -EINVAL;
	पूर्ण

	अक्षरger = kzalloc(माप(*अक्षरger), GFP_KERNEL);
	अगर (अक्षरger == शून्य)
		वापस -ENOMEM;

	अक्षरger->bat_status = POWER_SUPPLY_STATUS_UNKNOWN;
	अक्षरger->info = info;
	अक्षरger->client = client;
	i2c_set_clientdata(client, अक्षरger);
	psy_cfg.drv_data = अक्षरger;

	mutex_init(&अक्षरger->work_lock);

	अक्षरger->अक्षरge_gpiod = devm_gpiod_get_optional(&client->dev,
							शून्य, GPIOD_IN);
	अगर (IS_ERR(अक्षरger->अक्षरge_gpiod))
		वापस dev_err_probe(&client->dev,
				     PTR_ERR(अक्षरger->अक्षरge_gpiod),
				     "failed to get charge GPIO\n");

	अगर (अक्षरger->अक्षरge_gpiod) अणु
		gpiod_set_consumer_name(अक्षरger->अक्षरge_gpiod, "BATT CHRG");

		irq_set_irq_type(gpiod_to_irq(अक्षरger->अक्षरge_gpiod),
				 IRQ_TYPE_EDGE_BOTH);
		ret = request_irq(gpiod_to_irq(अक्षरger->अक्षरge_gpiod),
				z2_अक्षरge_चयन_irq, 0,
				"AC Detect", अक्षरger);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = z2_batt_ps_init(अक्षरger, props);
	अगर (ret)
		जाओ err3;

	INIT_WORK(&अक्षरger->bat_work, z2_batt_work);

	अक्षरger->batt_ps = घातer_supply_रेजिस्टर(&client->dev,
						 &अक्षरger->batt_ps_desc,
						 &psy_cfg);
	अगर (IS_ERR(अक्षरger->batt_ps)) अणु
		ret = PTR_ERR(अक्षरger->batt_ps);
		जाओ err4;
	पूर्ण

	schedule_work(&अक्षरger->bat_work);

	वापस 0;

err4:
	kमुक्त(अक्षरger->batt_ps_desc.properties);
err3:
	अगर (अक्षरger->अक्षरge_gpiod)
		मुक्त_irq(gpiod_to_irq(अक्षरger->अक्षरge_gpiod), अक्षरger);
err:
	kमुक्त(अक्षरger);
	वापस ret;
पूर्ण

अटल पूर्णांक z2_batt_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा z2_अक्षरger *अक्षरger = i2c_get_clientdata(client);

	cancel_work_sync(&अक्षरger->bat_work);
	घातer_supply_unरेजिस्टर(अक्षरger->batt_ps);

	kमुक्त(अक्षरger->batt_ps_desc.properties);
	अगर (अक्षरger->अक्षरge_gpiod)
		मुक्त_irq(gpiod_to_irq(अक्षरger->अक्षरge_gpiod), अक्षरger);

	kमुक्त(अक्षरger);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक z2_batt_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा z2_अक्षरger *अक्षरger = i2c_get_clientdata(client);

	flush_work(&अक्षरger->bat_work);
	वापस 0;
पूर्ण

अटल पूर्णांक z2_batt_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा z2_अक्षरger *अक्षरger = i2c_get_clientdata(client);

	schedule_work(&अक्षरger->bat_work);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops z2_battery_pm_ops = अणु
	.suspend	= z2_batt_suspend,
	.resume		= z2_batt_resume,
पूर्ण;

#घोषणा	Z2_BATTERY_PM_OPS	(&z2_battery_pm_ops)

#अन्यथा
#घोषणा	Z2_BATTERY_PM_OPS	(शून्य)
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id z2_batt_id[] = अणु
	अणु "aer915", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, z2_batt_id);

अटल काष्ठा i2c_driver z2_batt_driver = अणु
	.driver	= अणु
		.name	= "z2-battery",
		.pm	= Z2_BATTERY_PM_OPS
	पूर्ण,
	.probe		= z2_batt_probe,
	.हटाओ		= z2_batt_हटाओ,
	.id_table	= z2_batt_id,
पूर्ण;
module_i2c_driver(z2_batt_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Edwards <sweetlilmre@gmail.com>");
MODULE_DESCRIPTION("Zipit Z2 battery driver");
