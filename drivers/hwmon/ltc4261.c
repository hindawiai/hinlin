<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Linear Technology LTC4261 I2C Negative Voltage Hot Swap Controller
 *
 * Copyright (C) 2010 Ericsson AB.
 *
 * Derived from:
 *
 *  Driver क्रम Linear Technology LTC4245 I2C Multiple Supply Hot Swap Controller
 *  Copyright (C) 2008 Ira W. Snyder <iws@ovro.caltech.edu>
 *
 * Datasheet: http://cds.linear.com/करोcs/Datasheet/42612fb.pdf
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

/* chip रेजिस्टरs */
#घोषणा LTC4261_STATUS	0x00	/* पढ़ोonly */
#घोषणा LTC4261_FAULT	0x01
#घोषणा LTC4261_ALERT	0x02
#घोषणा LTC4261_CONTROL	0x03
#घोषणा LTC4261_SENSE_H	0x04
#घोषणा LTC4261_SENSE_L	0x05
#घोषणा LTC4261_ADIN2_H	0x06
#घोषणा LTC4261_ADIN2_L	0x07
#घोषणा LTC4261_ADIN_H	0x08
#घोषणा LTC4261_ADIN_L	0x09

/*
 * Fault रेजिस्टर bits
 */
#घोषणा FAULT_OV	(1<<0)
#घोषणा FAULT_UV	(1<<1)
#घोषणा FAULT_OC	(1<<2)

काष्ठा ltc4261_data अणु
	काष्ठा i2c_client *client;

	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */

	/* Registers */
	u8 regs[10];
पूर्ण;

अटल काष्ठा ltc4261_data *ltc4261_update_device(काष्ठा device *dev)
अणु
	काष्ठा ltc4261_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा ltc4261_data *ret = data;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ / 4) || !data->valid) अणु
		पूर्णांक i;

		/* Read रेजिस्टरs -- 0x00 to 0x09 */
		क्रम (i = 0; i < ARRAY_SIZE(data->regs); i++) अणु
			पूर्णांक val;

			val = i2c_smbus_पढ़ो_byte_data(client, i);
			अगर (unlikely(val < 0)) अणु
				dev_dbg(dev,
					"Failed to read ADC value: error %d\n",
					val);
				ret = ERR_PTR(val);
				data->valid = 0;
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

/* Return the voltage from the given रेजिस्टर in mV or mA */
अटल पूर्णांक ltc4261_get_value(काष्ठा ltc4261_data *data, u8 reg)
अणु
	u32 val;

	val = (data->regs[reg] << 2) + (data->regs[reg + 1] >> 6);

	चयन (reg) अणु
	हाल LTC4261_ADIN_H:
	हाल LTC4261_ADIN2_H:
		/* 2.5mV resolution. Convert to mV. */
		val = val * 25 / 10;
		अवरोध;
	हाल LTC4261_SENSE_H:
		/*
		 * 62.5uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a dअगरferent sense
		 * resistor is installed, calculate the actual current by
		 * भागiding the reported current by the sense resistor value
		 * in mOhm.
		 */
		val = val * 625 / 10;
		अवरोध;
	शेष:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		val = 0;
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल sमाप_प्रकार ltc4261_value_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ltc4261_data *data = ltc4261_update_device(dev);
	पूर्णांक value;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	value = ltc4261_get_value(data, attr->index);
	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार ltc4261_bool_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ltc4261_data *data = ltc4261_update_device(dev);
	u8 fault;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	fault = data->regs[LTC4261_FAULT] & attr->index;
	अगर (fault)		/* Clear reported faults in chip रेजिस्टर */
		i2c_smbus_ग_लिखो_byte_data(data->client, LTC4261_FAULT, ~fault);

	वापस sysfs_emit(buf, "%d\n", fault ? 1 : 0);
पूर्ण

/*
 * Input voltages.
 */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ltc4261_value, LTC4261_ADIN_H);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, ltc4261_value, LTC4261_ADIN2_H);

/*
 * Voltage alarms. The chip has only one set of voltage alarm status bits,
 * triggered by input voltage alarms. In many designs, those alarms are
 * associated with the ADIN2 sensor, due to the proximity of the ADIN2 pin
 * to the OV pin. ADIN2 is, however, not available on all chip variants.
 * To ensure that the alarm condition is reported to the user, report it
 * with both voltage sensors.
 */
अटल SENSOR_DEVICE_ATTR_RO(in1_min_alarm, ltc4261_bool, FAULT_UV);
अटल SENSOR_DEVICE_ATTR_RO(in1_max_alarm, ltc4261_bool, FAULT_OV);
अटल SENSOR_DEVICE_ATTR_RO(in2_min_alarm, ltc4261_bool, FAULT_UV);
अटल SENSOR_DEVICE_ATTR_RO(in2_max_alarm, ltc4261_bool, FAULT_OV);

/* Currents (via sense resistor) */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ltc4261_value, LTC4261_SENSE_H);

/* Overcurrent alarm */
अटल SENSOR_DEVICE_ATTR_RO(curr1_max_alarm, ltc4261_bool, FAULT_OC);

अटल काष्ठा attribute *ltc4261_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_max_alarm.dev_attr.attr,

	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_max_alarm.dev_attr.attr,

	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ltc4261);

अटल पूर्णांक ltc4261_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा ltc4261_data *data;
	काष्ठा device *hwmon_dev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	अगर (i2c_smbus_पढ़ो_byte_data(client, LTC4261_STATUS) < 0) अणु
		dev_err(dev, "Failed to read status register\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Clear faults */
	i2c_smbus_ग_लिखो_byte_data(client, LTC4261_FAULT, 0x00);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   ltc4261_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4261_id[] = अणु
	अणु"ltc4261", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ltc4261_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ltc4261_driver = अणु
	.driver = अणु
		   .name = "ltc4261",
		   पूर्ण,
	.probe_new = ltc4261_probe,
	.id_table = ltc4261_id,
पूर्ण;

module_i2c_driver(ltc4261_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("LTC4261 driver");
MODULE_LICENSE("GPL");
