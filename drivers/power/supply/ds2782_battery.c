<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C client/driver क्रम the Maxim/Dallas DS2782 Stand-Alone Fuel Gauge IC
 *
 * Copyright (C) 2009 Bluewater Systems Ltd
 *
 * Author: Ryan Mallon
 *
 * DS2786 added by Yulia Vilensky <vilensky@compulab.co.il>
 *
 * UEvent sending added by Evgeny Romanov <romanov@neurosoft.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/swab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/idr.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/ds2782_battery.h>

#घोषणा DS2782_REG_RARC		0x06	/* Reमुख्यing active relative capacity */

#घोषणा DS278x_REG_VOLT_MSB	0x0c
#घोषणा DS278x_REG_TEMP_MSB	0x0a
#घोषणा DS278x_REG_CURRENT_MSB	0x0e

/* EEPROM Block */
#घोषणा DS2782_REG_RSNSP	0x69	/* Sense resistor value */

/* Current unit measurement in uA क्रम a 1 milli-ohm sense resistor */
#घोषणा DS2782_CURRENT_UNITS	1563

#घोषणा DS2786_REG_RARC		0x02	/* Reमुख्यing active relative capacity */

#घोषणा DS2786_CURRENT_UNITS	25

#घोषणा DS278x_DELAY		1000

काष्ठा ds278x_info;

काष्ठा ds278x_battery_ops अणु
	पूर्णांक (*get_battery_current)(काष्ठा ds278x_info *info, पूर्णांक *current_uA);
	पूर्णांक (*get_battery_voltage)(काष्ठा ds278x_info *info, पूर्णांक *voltage_uV);
	पूर्णांक (*get_battery_capacity)(काष्ठा ds278x_info *info, पूर्णांक *capacity);
पूर्ण;

#घोषणा to_ds278x_info(x) घातer_supply_get_drvdata(x)

काष्ठा ds278x_info अणु
	काष्ठा i2c_client	*client;
	काष्ठा घातer_supply	*battery;
	काष्ठा घातer_supply_desc	battery_desc;
	स्थिर काष्ठा ds278x_battery_ops *ops;
	काष्ठा delayed_work	bat_work;
	पूर्णांक			id;
	पूर्णांक                     rsns;
	पूर्णांक			capacity;
	पूर्णांक			status;		/* State Of Charge */
पूर्ण;

अटल DEFINE_IDR(battery_id);
अटल DEFINE_MUTEX(battery_lock);

अटल अंतरभूत पूर्णांक ds278x_पढ़ो_reg(काष्ठा ds278x_info *info, पूर्णांक reg, u8 *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(info->client, reg);
	अगर (ret < 0) अणु
		dev_err(&info->client->dev, "register read failed\n");
		वापस ret;
	पूर्ण

	*val = ret;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ds278x_पढ़ो_reg16(काष्ठा ds278x_info *info, पूर्णांक reg_msb,
				    s16 *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_data(info->client, reg_msb);
	अगर (ret < 0) अणु
		dev_err(&info->client->dev, "register read failed\n");
		वापस ret;
	पूर्ण

	*val = swab16(ret);
	वापस 0;
पूर्ण

अटल पूर्णांक ds278x_get_temp(काष्ठा ds278x_info *info, पूर्णांक *temp)
अणु
	s16 raw;
	पूर्णांक err;

	/*
	 * Temperature is measured in units of 0.125 degrees celcius, the
	 * घातer_supply class measures temperature in tenths of degrees
	 * celsius. The temperature value is stored as a 10 bit number, plus
	 * sign in the upper bits of a 16 bit रेजिस्टर.
	 */
	err = ds278x_पढ़ो_reg16(info, DS278x_REG_TEMP_MSB, &raw);
	अगर (err)
		वापस err;
	*temp = ((raw / 32) * 125) / 100;
	वापस 0;
पूर्ण

अटल पूर्णांक ds2782_get_current(काष्ठा ds278x_info *info, पूर्णांक *current_uA)
अणु
	पूर्णांक sense_res;
	पूर्णांक err;
	u8 sense_res_raw;
	s16 raw;

	/*
	 * The units of measurement क्रम current are dependent on the value of
	 * the sense resistor.
	 */
	err = ds278x_पढ़ो_reg(info, DS2782_REG_RSNSP, &sense_res_raw);
	अगर (err)
		वापस err;
	अगर (sense_res_raw == 0) अणु
		dev_err(&info->client->dev, "sense resistor value is 0\n");
		वापस -ENXIO;
	पूर्ण
	sense_res = 1000 / sense_res_raw;

	dev_dbg(&info->client->dev, "sense resistor = %d milli-ohms\n",
		sense_res);
	err = ds278x_पढ़ो_reg16(info, DS278x_REG_CURRENT_MSB, &raw);
	अगर (err)
		वापस err;
	*current_uA = raw * (DS2782_CURRENT_UNITS / sense_res);
	वापस 0;
पूर्ण

अटल पूर्णांक ds2782_get_voltage(काष्ठा ds278x_info *info, पूर्णांक *voltage_uV)
अणु
	s16 raw;
	पूर्णांक err;

	/*
	 * Voltage is measured in units of 4.88mV. The voltage is stored as
	 * a 10-bit number plus sign, in the upper bits of a 16-bit रेजिस्टर
	 */
	err = ds278x_पढ़ो_reg16(info, DS278x_REG_VOLT_MSB, &raw);
	अगर (err)
		वापस err;
	*voltage_uV = (raw / 32) * 4800;
	वापस 0;
पूर्ण

अटल पूर्णांक ds2782_get_capacity(काष्ठा ds278x_info *info, पूर्णांक *capacity)
अणु
	पूर्णांक err;
	u8 raw;

	err = ds278x_पढ़ो_reg(info, DS2782_REG_RARC, &raw);
	अगर (err)
		वापस err;
	*capacity = raw;
	वापस 0;
पूर्ण

अटल पूर्णांक ds2786_get_current(काष्ठा ds278x_info *info, पूर्णांक *current_uA)
अणु
	पूर्णांक err;
	s16 raw;

	err = ds278x_पढ़ो_reg16(info, DS278x_REG_CURRENT_MSB, &raw);
	अगर (err)
		वापस err;
	*current_uA = (raw / 16) * (DS2786_CURRENT_UNITS / info->rsns);
	वापस 0;
पूर्ण

अटल पूर्णांक ds2786_get_voltage(काष्ठा ds278x_info *info, पूर्णांक *voltage_uV)
अणु
	s16 raw;
	पूर्णांक err;

	/*
	 * Voltage is measured in units of 1.22mV. The voltage is stored as
	 * a 12-bit number plus sign, in the upper bits of a 16-bit रेजिस्टर
	 */
	err = ds278x_पढ़ो_reg16(info, DS278x_REG_VOLT_MSB, &raw);
	अगर (err)
		वापस err;
	*voltage_uV = (raw / 8) * 1220;
	वापस 0;
पूर्ण

अटल पूर्णांक ds2786_get_capacity(काष्ठा ds278x_info *info, पूर्णांक *capacity)
अणु
	पूर्णांक err;
	u8 raw;

	err = ds278x_पढ़ो_reg(info, DS2786_REG_RARC, &raw);
	अगर (err)
		वापस err;
	/* Relative capacity is displayed with resolution 0.5 % */
	*capacity = raw/2 ;
	वापस 0;
पूर्ण

अटल पूर्णांक ds278x_get_status(काष्ठा ds278x_info *info, पूर्णांक *status)
अणु
	पूर्णांक err;
	पूर्णांक current_uA;
	पूर्णांक capacity;

	err = info->ops->get_battery_current(info, &current_uA);
	अगर (err)
		वापस err;

	err = info->ops->get_battery_capacity(info, &capacity);
	अगर (err)
		वापस err;

	info->capacity = capacity;

	अगर (capacity == 100)
		*status = POWER_SUPPLY_STATUS_FULL;
	अन्यथा अगर (current_uA == 0)
		*status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	अन्यथा अगर (current_uA < 0)
		*status = POWER_SUPPLY_STATUS_DISCHARGING;
	अन्यथा
		*status = POWER_SUPPLY_STATUS_CHARGING;

	वापस 0;
पूर्ण

अटल पूर्णांक ds278x_battery_get_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property prop,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ds278x_info *info = to_ds278x_info(psy);
	पूर्णांक ret;

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = ds278x_get_status(info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = info->ops->get_battery_capacity(info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = info->ops->get_battery_voltage(info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = info->ops->get_battery_current(info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_TEMP:
		ret = ds278x_get_temp(info, &val->पूर्णांकval);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ds278x_bat_update(काष्ठा ds278x_info *info)
अणु
	पूर्णांक old_status = info->status;
	पूर्णांक old_capacity = info->capacity;

	ds278x_get_status(info, &info->status);

	अगर ((old_status != info->status) || (old_capacity != info->capacity))
		घातer_supply_changed(info->battery);
पूर्ण

अटल व्योम ds278x_bat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ds278x_info *info;

	info = container_of(work, काष्ठा ds278x_info, bat_work.work);
	ds278x_bat_update(info);

	schedule_delayed_work(&info->bat_work, DS278x_DELAY);
पूर्ण

अटल क्रमागत घातer_supply_property ds278x_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल व्योम ds278x_घातer_supply_init(काष्ठा घातer_supply_desc *battery)
अणु
	battery->type			= POWER_SUPPLY_TYPE_BATTERY;
	battery->properties		= ds278x_battery_props;
	battery->num_properties		= ARRAY_SIZE(ds278x_battery_props);
	battery->get_property		= ds278x_battery_get_property;
	battery->बाह्यal_घातer_changed	= शून्य;
पूर्ण

अटल पूर्णांक ds278x_battery_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ds278x_info *info = i2c_get_clientdata(client);
	पूर्णांक id = info->id;

	घातer_supply_unरेजिस्टर(info->battery);
	cancel_delayed_work_sync(&info->bat_work);
	kमुक्त(info->battery_desc.name);
	kमुक्त(info);

	mutex_lock(&battery_lock);
	idr_हटाओ(&battery_id, id);
	mutex_unlock(&battery_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक ds278x_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ds278x_info *info = i2c_get_clientdata(client);

	cancel_delayed_work(&info->bat_work);
	वापस 0;
पूर्ण

अटल पूर्णांक ds278x_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ds278x_info *info = i2c_get_clientdata(client);

	schedule_delayed_work(&info->bat_work, DS278x_DELAY);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(ds278x_battery_pm_ops, ds278x_suspend, ds278x_resume);

क्रमागत ds278x_num_id अणु
	DS2782 = 0,
	DS2786,
पूर्ण;

अटल स्थिर काष्ठा ds278x_battery_ops ds278x_ops[] = अणु
	[DS2782] = अणु
		.get_battery_current  = ds2782_get_current,
		.get_battery_voltage  = ds2782_get_voltage,
		.get_battery_capacity = ds2782_get_capacity,
	पूर्ण,
	[DS2786] = अणु
		.get_battery_current  = ds2786_get_current,
		.get_battery_voltage  = ds2786_get_voltage,
		.get_battery_capacity = ds2786_get_capacity,
	पूर्ण
पूर्ण;

अटल पूर्णांक ds278x_battery_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ds278x_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा ds278x_info *info;
	पूर्णांक ret;
	पूर्णांक num;

	/*
	 * ds2786 should have the sense resistor value set
	 * in the platक्रमm data
	 */
	अगर (id->driver_data == DS2786 && !pdata) अणु
		dev_err(&client->dev, "missing platform data for ds2786\n");
		वापस -EINVAL;
	पूर्ण

	/* Get an ID क्रम this battery */
	mutex_lock(&battery_lock);
	ret = idr_alloc(&battery_id, client, 0, 0, GFP_KERNEL);
	mutex_unlock(&battery_lock);
	अगर (ret < 0)
		जाओ fail_id;
	num = ret;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ fail_info;
	पूर्ण

	info->battery_desc.name = kaप्र_लिखो(GFP_KERNEL, "%s-%d",
					    client->name, num);
	अगर (!info->battery_desc.name) अणु
		ret = -ENOMEM;
		जाओ fail_name;
	पूर्ण

	अगर (id->driver_data == DS2786)
		info->rsns = pdata->rsns;

	i2c_set_clientdata(client, info);
	info->client = client;
	info->id = num;
	info->ops  = &ds278x_ops[id->driver_data];
	ds278x_घातer_supply_init(&info->battery_desc);
	psy_cfg.drv_data = info;

	info->capacity = 100;
	info->status = POWER_SUPPLY_STATUS_FULL;

	INIT_DELAYED_WORK(&info->bat_work, ds278x_bat_work);

	info->battery = घातer_supply_रेजिस्टर(&client->dev,
					      &info->battery_desc, &psy_cfg);
	अगर (IS_ERR(info->battery)) अणु
		dev_err(&client->dev, "failed to register battery\n");
		ret = PTR_ERR(info->battery);
		जाओ fail_रेजिस्टर;
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&info->bat_work, DS278x_DELAY);
	पूर्ण

	वापस 0;

fail_रेजिस्टर:
	kमुक्त(info->battery_desc.name);
fail_name:
	kमुक्त(info);
fail_info:
	mutex_lock(&battery_lock);
	idr_हटाओ(&battery_id, num);
	mutex_unlock(&battery_lock);
fail_id:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ds278x_id[] = अणु
	अणु"ds2782", DS2782पूर्ण,
	अणु"ds2786", DS2786पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds278x_id);

अटल काष्ठा i2c_driver ds278x_battery_driver = अणु
	.driver 	= अणु
		.name	= "ds2782-battery",
		.pm	= &ds278x_battery_pm_ops,
	पूर्ण,
	.probe		= ds278x_battery_probe,
	.हटाओ		= ds278x_battery_हटाओ,
	.id_table	= ds278x_id,
पूर्ण;
module_i2c_driver(ds278x_battery_driver);

MODULE_AUTHOR("Ryan Mallon");
MODULE_DESCRIPTION("Maxim/Dallas DS2782 Stand-Alone Fuel Gauge IC driver");
MODULE_LICENSE("GPL");
