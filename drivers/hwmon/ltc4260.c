<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Linear Technology LTC4260 I2C Positive Voltage Hot Swap Controller
 *
 * Copyright (c) 2014 Guenter Roeck
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/regmap.h>

/* chip रेजिस्टरs */
#घोषणा LTC4260_CONTROL	0x00
#घोषणा LTC4260_ALERT	0x01
#घोषणा LTC4260_STATUS	0x02
#घोषणा LTC4260_FAULT	0x03
#घोषणा LTC4260_SENSE	0x04
#घोषणा LTC4260_SOURCE	0x05
#घोषणा LTC4260_ADIN	0x06

/*
 * Fault रेजिस्टर bits
 */
#घोषणा FAULT_OV	(1 << 0)
#घोषणा FAULT_UV	(1 << 1)
#घोषणा FAULT_OC	(1 << 2)
#घोषणा FAULT_POWER_BAD	(1 << 3)
#घोषणा FAULT_FET_SHORT	(1 << 5)

/* Return the voltage from the given रेजिस्टर in mV or mA */
अटल पूर्णांक ltc4260_get_value(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	चयन (reg) अणु
	हाल LTC4260_ADIN:
		/* 10 mV resolution. Convert to mV. */
		val = val * 10;
		अवरोध;
	हाल LTC4260_SOURCE:
		/* 400 mV resolution. Convert to mV. */
		val = val * 400;
		अवरोध;
	हाल LTC4260_SENSE:
		/*
		 * 300 uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a dअगरferent sense
		 * resistor is installed, calculate the actual current by
		 * भागiding the reported current by the sense resistor value
		 * in mOhm.
		 */
		val = val * 300;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस val;
पूर्ण

अटल sमाप_प्रकार ltc4260_value_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक value;

	value = ltc4260_get_value(dev, attr->index);
	अगर (value < 0)
		वापस value;
	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार ltc4260_bool_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक fault;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, LTC4260_FAULT, &fault);
	अगर (ret < 0)
		वापस ret;

	fault &= attr->index;
	अगर (fault)		/* Clear reported faults in chip रेजिस्टर */
		regmap_update_bits(regmap, LTC4260_FAULT, attr->index, 0);

	वापस sysfs_emit(buf, "%d\n", !!fault);
पूर्ण

/* Voltages */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ltc4260_value, LTC4260_SOURCE);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, ltc4260_value, LTC4260_ADIN);

/*
 * Voltage alarms
 * UV/OV faults are associated with the input voltage, and the POWER BAD and
 * FET SHORT faults are associated with the output voltage.
 */
अटल SENSOR_DEVICE_ATTR_RO(in1_min_alarm, ltc4260_bool, FAULT_UV);
अटल SENSOR_DEVICE_ATTR_RO(in1_max_alarm, ltc4260_bool, FAULT_OV);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, ltc4260_bool,
			     FAULT_POWER_BAD | FAULT_FET_SHORT);

/* Current (via sense resistor) */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ltc4260_value, LTC4260_SENSE);

/* Overcurrent alarm */
अटल SENSOR_DEVICE_ATTR_RO(curr1_max_alarm, ltc4260_bool, FAULT_OC);

अटल काष्ठा attribute *ltc4260_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,

	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_max_alarm.dev_attr.attr,

	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ltc4260);

अटल स्थिर काष्ठा regmap_config ltc4260_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LTC4260_ADIN,
पूर्ण;

अटल पूर्णांक ltc4260_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &ltc4260_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/* Clear faults */
	regmap_ग_लिखो(regmap, LTC4260_FAULT, 0x00);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   regmap,
							   ltc4260_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4260_id[] = अणु
	अणु"ltc4260", 0पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ltc4260_id);

अटल काष्ठा i2c_driver ltc4260_driver = अणु
	.driver = अणु
		   .name = "ltc4260",
		   पूर्ण,
	.probe_new = ltc4260_probe,
	.id_table = ltc4260_id,
पूर्ण;

module_i2c_driver(ltc4260_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("LTC4260 driver");
MODULE_LICENSE("GPL");
