<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Linear Technology LTC4222 Dual Hot Swap controller
 *
 * Copyright (c) 2014 Guenter Roeck
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/regmap.h>

/* chip रेजिस्टरs */

#घोषणा LTC4222_CONTROL1	0xd0
#घोषणा LTC4222_ALERT1		0xd1
#घोषणा LTC4222_STATUS1		0xd2
#घोषणा LTC4222_FAULT1		0xd3
#घोषणा LTC4222_CONTROL2	0xd4
#घोषणा LTC4222_ALERT2		0xd5
#घोषणा LTC4222_STATUS2		0xd6
#घोषणा LTC4222_FAULT2		0xd7
#घोषणा LTC4222_SOURCE1		0xd8
#घोषणा LTC4222_SOURCE2		0xda
#घोषणा LTC4222_ADIN1		0xdc
#घोषणा LTC4222_ADIN2		0xde
#घोषणा LTC4222_SENSE1		0xe0
#घोषणा LTC4222_SENSE2		0xe2
#घोषणा LTC4222_ADC_CONTROL	0xe4

/*
 * Fault रेजिस्टर bits
 */
#घोषणा FAULT_OV	BIT(0)
#घोषणा FAULT_UV	BIT(1)
#घोषणा FAULT_OC	BIT(2)
#घोषणा FAULT_POWER_BAD	BIT(3)
#घोषणा FAULT_FET_BAD	BIT(5)

/* Return the voltage from the given रेजिस्टर in mV or mA */
अटल पूर्णांक ltc4222_get_value(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	u8 buf[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(regmap, reg, buf, 2);
	अगर (ret < 0)
		वापस ret;

	val = ((buf[0] << 8) + buf[1]) >> 6;

	चयन (reg) अणु
	हाल LTC4222_ADIN1:
	हाल LTC4222_ADIN2:
		/* 1.25 mV resolution. Convert to mV. */
		val = DIV_ROUND_CLOSEST(val * 5, 4);
		अवरोध;
	हाल LTC4222_SOURCE1:
	हाल LTC4222_SOURCE2:
		/* 31.25 mV resolution. Convert to mV. */
		val = DIV_ROUND_CLOSEST(val * 125, 4);
		अवरोध;
	हाल LTC4222_SENSE1:
	हाल LTC4222_SENSE2:
		/*
		 * 62.5 uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a dअगरferent sense
		 * resistor is installed, calculate the actual current by
		 * भागiding the reported current by the sense resistor value
		 * in mOhm.
		 */
		val = DIV_ROUND_CLOSEST(val * 125, 2);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस val;
पूर्ण

अटल sमाप_प्रकार ltc4222_value_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक value;

	value = ltc4222_get_value(dev, attr->index);
	अगर (value < 0)
		वापस value;
	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार ltc4222_bool_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(da);
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक fault;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, attr->nr, &fault);
	अगर (ret < 0)
		वापस ret;
	fault &= attr->index;
	अगर (fault)		/* Clear reported faults in chip रेजिस्टर */
		regmap_update_bits(regmap, attr->nr, attr->index, 0);

	वापस sysfs_emit(buf, "%d\n", !!fault);
पूर्ण

/* Voltages */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ltc4222_value, LTC4222_SOURCE1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, ltc4222_value, LTC4222_ADIN1);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, ltc4222_value, LTC4222_SOURCE2);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, ltc4222_value, LTC4222_ADIN2);

/*
 * Voltage alarms
 * UV/OV faults are associated with the input voltage, and घातer bad and fet
 * faults are associated with the output voltage.
 */
अटल SENSOR_DEVICE_ATTR_2_RO(in1_min_alarm, ltc4222_bool, LTC4222_FAULT1,
			       FAULT_UV);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_max_alarm, ltc4222_bool, LTC4222_FAULT1,
			       FAULT_OV);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_alarm, ltc4222_bool, LTC4222_FAULT1,
			       FAULT_POWER_BAD | FAULT_FET_BAD);

अटल SENSOR_DEVICE_ATTR_2_RO(in3_min_alarm, ltc4222_bool, LTC4222_FAULT2,
			       FAULT_UV);
अटल SENSOR_DEVICE_ATTR_2_RO(in3_max_alarm, ltc4222_bool, LTC4222_FAULT2,
			       FAULT_OV);
अटल SENSOR_DEVICE_ATTR_2_RO(in4_alarm, ltc4222_bool, LTC4222_FAULT2,
			       FAULT_POWER_BAD | FAULT_FET_BAD);

/* Current (via sense resistor) */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ltc4222_value, LTC4222_SENSE1);
अटल SENSOR_DEVICE_ATTR_RO(curr2_input, ltc4222_value, LTC4222_SENSE2);

/* Overcurrent alarm */
अटल SENSOR_DEVICE_ATTR_2_RO(curr1_max_alarm, ltc4222_bool, LTC4222_FAULT1,
			       FAULT_OC);
अटल SENSOR_DEVICE_ATTR_2_RO(curr2_max_alarm, ltc4222_bool, LTC4222_FAULT2,
			       FAULT_OC);

अटल काष्ठा attribute *ltc4222_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,

	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_curr2_input.dev_attr.attr,
	&sensor_dev_attr_curr2_max_alarm.dev_attr.attr,

	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ltc4222);

अटल स्थिर काष्ठा regmap_config ltc4222_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LTC4222_ADC_CONTROL,
पूर्ण;

अटल पूर्णांक ltc4222_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &ltc4222_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/* Clear faults */
	regmap_ग_लिखो(regmap, LTC4222_FAULT1, 0x00);
	regmap_ग_लिखो(regmap, LTC4222_FAULT2, 0x00);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   regmap,
							   ltc4222_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4222_id[] = अणु
	अणु"ltc4222", 0पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ltc4222_id);

अटल काष्ठा i2c_driver ltc4222_driver = अणु
	.driver = अणु
		   .name = "ltc4222",
		   पूर्ण,
	.probe_new = ltc4222_probe,
	.id_table = ltc4222_id,
पूर्ण;

module_i2c_driver(ltc4222_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("LTC4222 driver");
MODULE_LICENSE("GPL");
