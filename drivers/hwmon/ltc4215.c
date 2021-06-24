<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Linear Technology LTC4215 I2C Hot Swap Controller
 *
 * Copyright (C) 2009 Ira W. Snyder <iws@ovro.caltech.edu>
 *
 * Datasheet:
 * http://www.linear.com/pc/करोwnloadDocument.करो?navId=H0,C1,C1003,C1006,C1163,P17572,D12697
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>

/* Here are names of the chip's रेजिस्टरs (a.k.a. commands) */
क्रमागत ltc4215_cmd अणु
	LTC4215_CONTROL			= 0x00, /* rw */
	LTC4215_ALERT			= 0x01, /* rw */
	LTC4215_STATUS			= 0x02, /* ro */
	LTC4215_FAULT			= 0x03, /* rw */
	LTC4215_SENSE			= 0x04, /* rw */
	LTC4215_SOURCE			= 0x05, /* rw */
	LTC4215_ADIN			= 0x06, /* rw */
पूर्ण;

काष्ठा ltc4215_data अणु
	काष्ठा i2c_client *client;

	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* Registers */
	u8 regs[7];
पूर्ण;

अटल काष्ठा ltc4215_data *ltc4215_update_device(काष्ठा device *dev)
अणु
	काष्ठा ltc4215_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	s32 val;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	/* The chip's A/D updates 10 बार per second */
	अगर (समय_after(jअगरfies, data->last_updated + HZ / 10) || !data->valid) अणु

		dev_dbg(&client->dev, "Starting ltc4215 update\n");

		/* Read all रेजिस्टरs */
		क्रम (i = 0; i < ARRAY_SIZE(data->regs); i++) अणु
			val = i2c_smbus_पढ़ो_byte_data(client, i);
			अगर (unlikely(val < 0))
				data->regs[i] = 0;
			अन्यथा
				data->regs[i] = val;
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* Return the voltage from the given रेजिस्टर in millivolts */
अटल पूर्णांक ltc4215_get_voltage(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा ltc4215_data *data = ltc4215_update_device(dev);
	स्थिर u8 regval = data->regs[reg];
	u32 voltage = 0;

	चयन (reg) अणु
	हाल LTC4215_SENSE:
		/* 151 uV per increment */
		voltage = regval * 151 / 1000;
		अवरोध;
	हाल LTC4215_SOURCE:
		/* 60.5 mV per increment */
		voltage = regval * 605 / 10;
		अवरोध;
	हाल LTC4215_ADIN:
		/*
		 * The ADIN input is भागided by 12.5, and has 4.82 mV
		 * per increment, so we have the additional multiply
		 */
		voltage = regval * 482 * 125 / 1000;
		अवरोध;
	शेष:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस voltage;
पूर्ण

/* Return the current from the sense resistor in mA */
अटल अचिन्हित पूर्णांक ltc4215_get_current(काष्ठा device *dev)
अणु
	काष्ठा ltc4215_data *data = ltc4215_update_device(dev);

	/*
	 * The strange looking conversions that follow are fixed-poपूर्णांक
	 * math, since we cannot करो भग्नing poपूर्णांक in the kernel.
	 *
	 * Step 1: convert sense रेजिस्टर to microVolts
	 * Step 2: convert voltage to milliAmperes
	 *
	 * If you play around with the V=IR equation, you come up with
	 * the following: X uV / Y mOhm == Z mA
	 *
	 * With the resistors that are fractions of a milliOhm, we multiply
	 * the voltage and resistance by 10, to shअगरt the decimal poपूर्णांक.
	 * Now we can use the normal भागision चालक again.
	 */

	/* Calculate voltage in microVolts (151 uV per increment) */
	स्थिर अचिन्हित पूर्णांक voltage = data->regs[LTC4215_SENSE] * 151;

	/* Calculate current in milliAmperes (4 milliOhm sense resistor) */
	स्थिर अचिन्हित पूर्णांक curr = voltage / 4;

	वापस curr;
पूर्ण

अटल sमाप_प्रकार ltc4215_voltage_show(काष्ठा device *dev,
				    काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	स्थिर पूर्णांक voltage = ltc4215_get_voltage(dev, attr->index);

	वापस sysfs_emit(buf, "%d\n", voltage);
पूर्ण

अटल sमाप_प्रकार ltc4215_current_show(काष्ठा device *dev,
				    काष्ठा device_attribute *da, अक्षर *buf)
अणु
	स्थिर अचिन्हित पूर्णांक curr = ltc4215_get_current(dev);

	वापस sysfs_emit(buf, "%u\n", curr);
पूर्ण

अटल sमाप_प्रकार ltc4215_घातer_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	स्थिर अचिन्हित पूर्णांक curr = ltc4215_get_current(dev);
	स्थिर पूर्णांक output_voltage = ltc4215_get_voltage(dev, LTC4215_ADIN);

	/* current in mA * voltage in mV == घातer in uW */
	स्थिर अचिन्हित पूर्णांक घातer = असल(output_voltage * curr);

	वापस sysfs_emit(buf, "%u\n", घातer);
पूर्ण

अटल sमाप_प्रकार ltc4215_alarm_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ltc4215_data *data = ltc4215_update_device(dev);
	स्थिर u8 reg = data->regs[LTC4215_STATUS];
	स्थिर u32 mask = attr->index;

	वापस sysfs_emit(buf, "%u\n", !!(reg & mask));
पूर्ण

/*
 * These macros are used below in स्थिरructing device attribute objects
 * क्रम use with sysfs_create_group() to make a sysfs device file
 * क्रम each रेजिस्टर.
 */

/* Conकाष्ठा a sensor_device_attribute काष्ठाure क्रम each रेजिस्टर */

/* Current */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ltc4215_current, 0);
अटल SENSOR_DEVICE_ATTR_RO(curr1_max_alarm, ltc4215_alarm, 1 << 2);

/* Power (भव) */
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input, ltc4215_घातer, 0);

/* Input Voltage */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ltc4215_voltage, LTC4215_ADIN);
अटल SENSOR_DEVICE_ATTR_RO(in1_max_alarm, ltc4215_alarm, 1 << 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_min_alarm, ltc4215_alarm, 1 << 1);

/* Output Voltage */
अटल SENSOR_DEVICE_ATTR_RO(in2_input, ltc4215_voltage, LTC4215_SOURCE);
अटल SENSOR_DEVICE_ATTR_RO(in2_min_alarm, ltc4215_alarm, 1 << 3);

/*
 * Finally, स्थिरruct an array of poपूर्णांकers to members of the above objects,
 * as required क्रम sysfs_create_group()
 */
अटल काष्ठा attribute *ltc4215_attrs[] = अणु
	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_max_alarm.dev_attr.attr,

	&sensor_dev_attr_घातer1_input.dev_attr.attr,

	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_min_alarm.dev_attr.attr,

	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min_alarm.dev_attr.attr,

	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ltc4215);

अटल पूर्णांक ltc4215_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा ltc4215_data *data;
	काष्ठा device *hwmon_dev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the LTC4215 chip */
	i2c_smbus_ग_लिखो_byte_data(client, LTC4215_FAULT, 0x00);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   ltc4215_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4215_id[] = अणु
	अणु "ltc4215", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc4215_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ltc4215_driver = अणु
	.driver = अणु
		.name	= "ltc4215",
	पूर्ण,
	.probe_new	= ltc4215_probe,
	.id_table	= ltc4215_id,
पूर्ण;

module_i2c_driver(ltc4215_driver);

MODULE_AUTHOR("Ira W. Snyder <iws@ovro.caltech.edu>");
MODULE_DESCRIPTION("LTC4215 driver");
MODULE_LICENSE("GPL");
