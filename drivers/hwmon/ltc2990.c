<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Linear Technology LTC2990 घातer monitor
 *
 * Copyright (C) 2014 Topic Embedded Products
 * Author: Mike Looijmans <mike.looijmans@topic.nl>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>

#घोषणा LTC2990_STATUS	0x00
#घोषणा LTC2990_CONTROL	0x01
#घोषणा LTC2990_TRIGGER	0x02
#घोषणा LTC2990_TINT_MSB	0x04
#घोषणा LTC2990_V1_MSB	0x06
#घोषणा LTC2990_V2_MSB	0x08
#घोषणा LTC2990_V3_MSB	0x0A
#घोषणा LTC2990_V4_MSB	0x0C
#घोषणा LTC2990_VCC_MSB	0x0E

#घोषणा LTC2990_IN0	BIT(0)
#घोषणा LTC2990_IN1	BIT(1)
#घोषणा LTC2990_IN2	BIT(2)
#घोषणा LTC2990_IN3	BIT(3)
#घोषणा LTC2990_IN4	BIT(4)
#घोषणा LTC2990_CURR1	BIT(5)
#घोषणा LTC2990_CURR2	BIT(6)
#घोषणा LTC2990_TEMP1	BIT(7)
#घोषणा LTC2990_TEMP2	BIT(8)
#घोषणा LTC2990_TEMP3	BIT(9)
#घोषणा LTC2990_NONE	0
#घोषणा LTC2990_ALL	GENMASK(9, 0)

#घोषणा LTC2990_MODE0_SHIFT	0
#घोषणा LTC2990_MODE0_MASK	GENMASK(2, 0)
#घोषणा LTC2990_MODE1_SHIFT	3
#घोषणा LTC2990_MODE1_MASK	GENMASK(1, 0)

/* Enabled measurements क्रम mode bits 2..0 */
अटल स्थिर पूर्णांक ltc2990_attrs_ena_0[] = अणु
	LTC2990_IN1 | LTC2990_IN2 | LTC2990_TEMP3,
	LTC2990_CURR1 | LTC2990_TEMP3,
	LTC2990_CURR1 | LTC2990_IN3 | LTC2990_IN4,
	LTC2990_TEMP2 | LTC2990_IN3 | LTC2990_IN4,
	LTC2990_TEMP2 | LTC2990_CURR2,
	LTC2990_TEMP2 | LTC2990_TEMP3,
	LTC2990_CURR1 | LTC2990_CURR2,
	LTC2990_IN1 | LTC2990_IN2 | LTC2990_IN3 | LTC2990_IN4
पूर्ण;

/* Enabled measurements क्रम mode bits 4..3 */
अटल स्थिर पूर्णांक ltc2990_attrs_ena_1[] = अणु
	LTC2990_NONE,
	LTC2990_TEMP2 | LTC2990_IN1 | LTC2990_CURR1,
	LTC2990_TEMP3 | LTC2990_IN3 | LTC2990_CURR2,
	LTC2990_ALL
पूर्ण;

काष्ठा ltc2990_data अणु
	काष्ठा i2c_client *i2c;
	u32 mode[2];
पूर्ण;

/* Return the converted value from the given रेजिस्टर in uV or mC */
अटल पूर्णांक ltc2990_get_value(काष्ठा i2c_client *i2c, पूर्णांक index, पूर्णांक *result)
अणु
	पूर्णांक val;
	u8 reg;

	चयन (index) अणु
	हाल LTC2990_IN0:
		reg = LTC2990_VCC_MSB;
		अवरोध;
	हाल LTC2990_IN1:
	हाल LTC2990_CURR1:
	हाल LTC2990_TEMP2:
		reg = LTC2990_V1_MSB;
		अवरोध;
	हाल LTC2990_IN2:
		reg = LTC2990_V2_MSB;
		अवरोध;
	हाल LTC2990_IN3:
	हाल LTC2990_CURR2:
	हाल LTC2990_TEMP3:
		reg = LTC2990_V3_MSB;
		अवरोध;
	हाल LTC2990_IN4:
		reg = LTC2990_V4_MSB;
		अवरोध;
	हाल LTC2990_TEMP1:
		reg = LTC2990_TINT_MSB;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = i2c_smbus_पढ़ो_word_swapped(i2c, reg);
	अगर (unlikely(val < 0))
		वापस val;

	चयन (index) अणु
	हाल LTC2990_TEMP1:
	हाल LTC2990_TEMP2:
	हाल LTC2990_TEMP3:
		/* temp, 0.0625 degrees/LSB */
		*result = sign_extend32(val, 12) * 1000 / 16;
		अवरोध;
	हाल LTC2990_CURR1:
	हाल LTC2990_CURR2:
		 /* Vx-Vy, 19.42uV/LSB */
		*result = sign_extend32(val, 14) * 1942 / 100;
		अवरोध;
	हाल LTC2990_IN0:
		/* Vcc, 305.18uV/LSB, 2.5V offset */
		*result = sign_extend32(val, 14) * 30518 / (100 * 1000) + 2500;
		अवरोध;
	हाल LTC2990_IN1:
	हाल LTC2990_IN2:
	हाल LTC2990_IN3:
	हाल LTC2990_IN4:
		/* Vx, 305.18uV/LSB */
		*result = sign_extend32(val, 14) * 30518 / (100 * 1000);
		अवरोध;
	शेष:
		वापस -EINVAL; /* won't happen, keep compiler happy */
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ltc2990_value_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ltc2990_data *data = dev_get_drvdata(dev);
	पूर्णांक value;
	पूर्णांक ret;

	ret = ltc2990_get_value(data->i2c, attr->index, &value);
	अगर (unlikely(ret < 0))
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल umode_t ltc2990_attrs_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा ltc2990_data *data = dev_get_drvdata(dev);
	काष्ठा device_attribute *da =
			container_of(a, काष्ठा device_attribute, attr);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);

	पूर्णांक attrs_mask = LTC2990_IN0 | LTC2990_TEMP1 |
			 (ltc2990_attrs_ena_0[data->mode[0]] &
			  ltc2990_attrs_ena_1[data->mode[1]]);

	अगर (attr->index & attrs_mask)
		वापस a->mode;

	वापस 0;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, ltc2990_value, LTC2990_TEMP1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, ltc2990_value, LTC2990_TEMP2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, ltc2990_value, LTC2990_TEMP3);
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ltc2990_value, LTC2990_CURR1);
अटल SENSOR_DEVICE_ATTR_RO(curr2_input, ltc2990_value, LTC2990_CURR2);
अटल SENSOR_DEVICE_ATTR_RO(in0_input, ltc2990_value, LTC2990_IN0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ltc2990_value, LTC2990_IN1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, ltc2990_value, LTC2990_IN2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, ltc2990_value, LTC2990_IN3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, ltc2990_value, LTC2990_IN4);

अटल काष्ठा attribute *ltc2990_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr2_input.dev_attr.attr,
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ltc2990_group = अणु
	.attrs = ltc2990_attrs,
	.is_visible = ltc2990_attrs_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(ltc2990);

अटल पूर्णांक ltc2990_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	पूर्णांक ret;
	काष्ठा device *hwmon_dev;
	काष्ठा ltc2990_data *data;

	अगर (!i2c_check_functionality(i2c->adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(&i2c->dev, माप(काष्ठा ltc2990_data), GFP_KERNEL);
	अगर (unlikely(!data))
		वापस -ENOMEM;

	data->i2c = i2c;

	अगर (dev_fwnode(&i2c->dev)) अणु
		ret = device_property_पढ़ो_u32_array(&i2c->dev,
						     "lltc,meas-mode",
						     data->mode, 2);
		अगर (ret < 0)
			वापस ret;

		अगर (data->mode[0] & ~LTC2990_MODE0_MASK ||
		    data->mode[1] & ~LTC2990_MODE1_MASK)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ret = i2c_smbus_पढ़ो_byte_data(i2c, LTC2990_CONTROL);
		अगर (ret < 0)
			वापस ret;

		data->mode[0] = ret >> LTC2990_MODE0_SHIFT & LTC2990_MODE0_MASK;
		data->mode[1] = ret >> LTC2990_MODE1_SHIFT & LTC2990_MODE1_MASK;
	पूर्ण

	/* Setup continuous mode */
	ret = i2c_smbus_ग_लिखो_byte_data(i2c, LTC2990_CONTROL,
					data->mode[0] << LTC2990_MODE0_SHIFT |
					data->mode[1] << LTC2990_MODE1_SHIFT);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Error: Failed to set control mode.\n");
		वापस ret;
	पूर्ण
	/* Trigger once to start continuous conversion */
	ret = i2c_smbus_ग_लिखो_byte_data(i2c, LTC2990_TRIGGER, 1);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Error: Failed to start acquisition.\n");
		वापस ret;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&i2c->dev,
							   i2c->name,
							   data,
							   ltc2990_groups);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc2990_i2c_id[] = अणु
	अणु "ltc2990", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc2990_i2c_id);

अटल काष्ठा i2c_driver ltc2990_i2c_driver = अणु
	.driver = अणु
		.name = "ltc2990",
	पूर्ण,
	.probe_new = ltc2990_i2c_probe,
	.id_table = ltc2990_i2c_id,
पूर्ण;

module_i2c_driver(ltc2990_i2c_driver);

MODULE_DESCRIPTION("LTC2990 Sensor Driver");
MODULE_AUTHOR("Topic Embedded Products");
MODULE_LICENSE("GPL v2");
