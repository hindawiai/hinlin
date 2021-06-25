<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Linear Technology LTC4151 High Voltage I2C Current
 * and Voltage Monitor
 *
 * Copyright (C) 2011 AppearTV AS
 *
 * Derived from:
 *
 *  Driver क्रम Linear Technology LTC4261 I2C Negative Voltage Hot
 *  Swap Controller
 *  Copyright (C) 2010 Ericsson AB.
 *
 * Datasheet: http://www.linear.com/करोcs/Datasheet/4151fc.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>

/* chip रेजिस्टरs */
#घोषणा LTC4151_SENSE_H	0x00
#घोषणा LTC4151_SENSE_L	0x01
#घोषणा LTC4151_VIN_H	0x02
#घोषणा LTC4151_VIN_L	0x03
#घोषणा LTC4151_ADIN_H	0x04
#घोषणा LTC4151_ADIN_L	0x05

काष्ठा ltc4151_data अणु
	काष्ठा i2c_client *client;

	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	अचिन्हित पूर्णांक shunt; /* in micro ohms */

	/* Registers */
	u8 regs[6];
पूर्ण;

अटल काष्ठा ltc4151_data *ltc4151_update_device(काष्ठा device *dev)
अणु
	काष्ठा ltc4151_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा ltc4151_data *ret = data;

	mutex_lock(&data->update_lock);

	/*
	 * The chip's A/D updates 6 बार per second
	 * (Conversion Rate 6 - 9 Hz)
	 */
	अगर (समय_after(jअगरfies, data->last_updated + HZ / 6) || !data->valid) अणु
		पूर्णांक i;

		dev_dbg(&client->dev, "Starting ltc4151 update\n");

		/* Read all रेजिस्टरs */
		क्रम (i = 0; i < ARRAY_SIZE(data->regs); i++) अणु
			पूर्णांक val;

			val = i2c_smbus_पढ़ो_byte_data(client, i);
			अगर (unlikely(val < 0)) अणु
				dev_dbg(dev,
					"Failed to read ADC value: error %d\n",
					val);
				ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			data->regs[i] = val;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

/* Return the voltage from the given रेजिस्टर in mV */
अटल पूर्णांक ltc4151_get_value(काष्ठा ltc4151_data *data, u8 reg)
अणु
	u32 val;

	val = (data->regs[reg] << 4) + (data->regs[reg + 1] >> 4);

	चयन (reg) अणु
	हाल LTC4151_ADIN_H:
		/* 500uV resolution. Convert to mV. */
		val = val * 500 / 1000;
		अवरोध;
	हाल LTC4151_SENSE_H:
		/*
		 * 20uV resolution. Convert to current as measured with
		 * a given sense resistor, in mA.
		 */
		val = val * 20 * 1000 / data->shunt;
		अवरोध;
	हाल LTC4151_VIN_H:
		/* 25 mV per increment */
		val = val * 25;
		अवरोध;
	शेष:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		val = 0;
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल sमाप_प्रकार ltc4151_value_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ltc4151_data *data = ltc4151_update_device(dev);
	पूर्णांक value;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	value = ltc4151_get_value(data, attr->index);
	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

/*
 * Input voltages.
 */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ltc4151_value, LTC4151_VIN_H);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, ltc4151_value, LTC4151_ADIN_H);

/* Currents (via sense resistor) */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ltc4151_value, LTC4151_SENSE_H);

/*
 * Finally, स्थिरruct an array of poपूर्णांकers to members of the above objects,
 * as required क्रम sysfs_create_group()
 */
अटल काष्ठा attribute *ltc4151_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,

	&sensor_dev_attr_curr1_input.dev_attr.attr,

	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ltc4151);

अटल पूर्णांक ltc4151_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा ltc4151_data *data;
	काष्ठा device *hwmon_dev;
	u32 shunt;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(client->dev.of_node,
				 "shunt-resistor-micro-ohms", &shunt))
		shunt = 1000; /* 1 mOhm अगर not set via DT */

	अगर (shunt == 0)
		वापस -EINVAL;

	data->shunt = shunt;

	data->client = client;
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   ltc4151_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4151_id[] = अणु
	अणु "ltc4151", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc4151_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ltc4151_match[] = अणु
	अणु .compatible = "lltc,ltc4151" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc4151_match);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ltc4151_driver = अणु
	.driver = अणु
		.name	= "ltc4151",
		.of_match_table = of_match_ptr(ltc4151_match),
	पूर्ण,
	.probe_new	= ltc4151_probe,
	.id_table	= ltc4151_id,
पूर्ण;

module_i2c_driver(ltc4151_driver);

MODULE_AUTHOR("Per Dalen <per.dalen@appeartv.com>");
MODULE_DESCRIPTION("LTC4151 driver");
MODULE_LICENSE("GPL");
