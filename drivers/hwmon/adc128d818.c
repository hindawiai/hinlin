<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम TI ADC128D818 System Monitor with Temperature Sensor
 *
 * Copyright (c) 2014 Guenter Roeck
 *
 * Derived from lm80.c
 * Copyright (C) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl>
 *			     and Philip Edelbrock <phil@netroedge.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of.h>

/* Addresses to scan
 * The chip also supports addresses 0x35..0x37. Don't scan those addresses
 * since they are also used by some EEPROMs, which may result in false
 * positives.
 */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x1d, 0x1e, 0x1f, 0x2d, 0x2e, 0x2f, I2C_CLIENT_END पूर्ण;

/* रेजिस्टरs */
#घोषणा ADC128_REG_IN_MAX(nr)		(0x2a + (nr) * 2)
#घोषणा ADC128_REG_IN_MIN(nr)		(0x2b + (nr) * 2)
#घोषणा ADC128_REG_IN(nr)		(0x20 + (nr))

#घोषणा ADC128_REG_TEMP			0x27
#घोषणा ADC128_REG_TEMP_MAX		0x38
#घोषणा ADC128_REG_TEMP_HYST		0x39

#घोषणा ADC128_REG_CONFIG		0x00
#घोषणा ADC128_REG_ALARM		0x01
#घोषणा ADC128_REG_MASK			0x03
#घोषणा ADC128_REG_CONV_RATE		0x07
#घोषणा ADC128_REG_ONESHOT		0x09
#घोषणा ADC128_REG_SHUTDOWN		0x0a
#घोषणा ADC128_REG_CONFIG_ADV		0x0b
#घोषणा ADC128_REG_BUSY_STATUS		0x0c

#घोषणा ADC128_REG_MAN_ID		0x3e
#घोषणा ADC128_REG_DEV_ID		0x3f

/* No. of voltage entries in adc128_attrs */
#घोषणा ADC128_ATTR_NUM_VOLT		(8 * 4)

/* Voltage inमाला_दो visible per operation mode */
अटल स्थिर u8 num_inमाला_दो[] = अणु 7, 8, 4, 6 पूर्ण;

काष्ठा adc128_data अणु
	काष्ठा i2c_client *client;
	काष्ठा regulator *regulator;
	पूर्णांक vref;		/* Reference voltage in mV */
	काष्ठा mutex update_lock;
	u8 mode;		/* Operation mode */
	bool valid;		/* true अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u16 in[3][8];		/* Register value, normalized to 12 bit
				 * 0: input voltage
				 * 1: min limit
				 * 2: max limit
				 */
	s16 temp[3];		/* Register value, normalized to 9 bit
				 * 0: sensor 1: limit 2: hyst
				 */
	u8 alarms;		/* alarm रेजिस्टर value */
पूर्ण;

अटल काष्ठा adc128_data *adc128_update_device(काष्ठा device *dev)
अणु
	काष्ठा adc128_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा adc128_data *ret = data;
	पूर्णांक i, rv;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		क्रम (i = 0; i < num_inमाला_दो[data->mode]; i++) अणु
			rv = i2c_smbus_पढ़ो_word_swapped(client,
							 ADC128_REG_IN(i));
			अगर (rv < 0)
				जाओ पात;
			data->in[0][i] = rv >> 4;

			rv = i2c_smbus_पढ़ो_byte_data(client,
						      ADC128_REG_IN_MIN(i));
			अगर (rv < 0)
				जाओ पात;
			data->in[1][i] = rv << 4;

			rv = i2c_smbus_पढ़ो_byte_data(client,
						      ADC128_REG_IN_MAX(i));
			अगर (rv < 0)
				जाओ पात;
			data->in[2][i] = rv << 4;
		पूर्ण

		अगर (data->mode != 1) अणु
			rv = i2c_smbus_पढ़ो_word_swapped(client,
							 ADC128_REG_TEMP);
			अगर (rv < 0)
				जाओ पात;
			data->temp[0] = rv >> 7;

			rv = i2c_smbus_पढ़ो_byte_data(client,
						      ADC128_REG_TEMP_MAX);
			अगर (rv < 0)
				जाओ पात;
			data->temp[1] = rv << 1;

			rv = i2c_smbus_पढ़ो_byte_data(client,
						      ADC128_REG_TEMP_HYST);
			अगर (rv < 0)
				जाओ पात;
			data->temp[2] = rv << 1;
		पूर्ण

		rv = i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_ALARM);
		अगर (rv < 0)
			जाओ पात;
		data->alarms |= rv;

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण
	जाओ करोne;

पात:
	ret = ERR_PTR(rv);
	data->valid = false;
करोne:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार adc128_in_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adc128_data *data = adc128_update_device(dev);
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = DIV_ROUND_CLOSEST(data->in[index][nr] * data->vref, 4095);
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार adc128_in_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा adc128_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;
	u8 reg, regval;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	/* 10 mV LSB on limit रेजिस्टरs */
	regval = clamp_val(DIV_ROUND_CLOSEST(val, 10), 0, 255);
	data->in[index][nr] = regval << 4;
	reg = index == 1 ? ADC128_REG_IN_MIN(nr) : ADC128_REG_IN_MAX(nr);
	i2c_smbus_ग_लिखो_byte_data(data->client, reg, regval);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार adc128_temp_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adc128_data *data = adc128_update_device(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक temp;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	temp = sign_extend32(data->temp[index], 8);
	वापस प्र_लिखो(buf, "%d\n", temp * 500);/* 0.5 degrees C resolution */
पूर्ण

अटल sमाप_प्रकार adc128_temp_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adc128_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक err;
	s8 regval;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	regval = clamp_val(DIV_ROUND_CLOSEST(val, 1000), -128, 127);
	data->temp[index] = regval << 1;
	i2c_smbus_ग_लिखो_byte_data(data->client,
				  index == 1 ? ADC128_REG_TEMP_MAX
					     : ADC128_REG_TEMP_HYST,
				  regval);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार adc128_alarm_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adc128_data *data = adc128_update_device(dev);
	पूर्णांक mask = 1 << to_sensor_dev_attr(attr)->index;
	u8 alarms;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	/*
	 * Clear an alarm after reporting it to user space. If it is still
	 * active, the next update sequence will set the alarm bit again.
	 */
	alarms = data->alarms;
	data->alarms &= ~mask;

	वापस प्र_लिखो(buf, "%u\n", !!(alarms & mask));
पूर्ण

अटल umode_t adc128_is_visible(काष्ठा kobject *kobj,
				 काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा adc128_data *data = dev_get_drvdata(dev);

	अगर (index < ADC128_ATTR_NUM_VOLT) अणु
		/* Voltage, visible according to num_inमाला_दो[] */
		अगर (index >= num_inमाला_दो[data->mode] * 4)
			वापस 0;
	पूर्ण अन्यथा अणु
		/* Temperature, visible अगर not in mode 1 */
		अगर (data->mode == 1)
			वापस 0;
	पूर्ण

	वापस attr->mode;
पूर्ण

अटल SENSOR_DEVICE_ATTR_2_RO(in0_input, adc128_in, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_min, adc128_in, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_max, adc128_in, 0, 2);

अटल SENSOR_DEVICE_ATTR_2_RO(in1_input, adc128_in, 1, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_min, adc128_in, 1, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_max, adc128_in, 1, 2);

अटल SENSOR_DEVICE_ATTR_2_RO(in2_input, adc128_in, 2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_min, adc128_in, 2, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_max, adc128_in, 2, 2);

अटल SENSOR_DEVICE_ATTR_2_RO(in3_input, adc128_in, 3, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_min, adc128_in, 3, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_max, adc128_in, 3, 2);

अटल SENSOR_DEVICE_ATTR_2_RO(in4_input, adc128_in, 4, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_min, adc128_in, 4, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_max, adc128_in, 4, 2);

अटल SENSOR_DEVICE_ATTR_2_RO(in5_input, adc128_in, 5, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_min, adc128_in, 5, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_max, adc128_in, 5, 2);

अटल SENSOR_DEVICE_ATTR_2_RO(in6_input, adc128_in, 6, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_min, adc128_in, 6, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_max, adc128_in, 6, 2);

अटल SENSOR_DEVICE_ATTR_2_RO(in7_input, adc128_in, 7, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in7_min, adc128_in, 7, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in7_max, adc128_in, 7, 2);

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, adc128_temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, adc128_temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, adc128_temp, 2);

अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, adc128_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, adc128_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, adc128_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, adc128_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, adc128_alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, adc128_alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, adc128_alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_alarm, adc128_alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, adc128_alarm, 7);

अटल काष्ठा attribute *adc128_attrs[] = अणु
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adc128_group = अणु
	.attrs = adc128_attrs,
	.is_visible = adc128_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(adc128);

अटल पूर्णांक adc128_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	पूर्णांक man_id, dev_id;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	man_id = i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_MAN_ID);
	dev_id = i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_DEV_ID);
	अगर (man_id != 0x01 || dev_id != 0x09)
		वापस -ENODEV;

	/* Check unused bits क्रम confirmation */
	अगर (i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_CONFIG) & 0xf4)
		वापस -ENODEV;
	अगर (i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_CONV_RATE) & 0xfe)
		वापस -ENODEV;
	अगर (i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_ONESHOT) & 0xfe)
		वापस -ENODEV;
	अगर (i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_SHUTDOWN) & 0xfe)
		वापस -ENODEV;
	अगर (i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_CONFIG_ADV) & 0xf8)
		वापस -ENODEV;
	अगर (i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_BUSY_STATUS) & 0xfc)
		वापस -ENODEV;

	strlcpy(info->type, "adc128d818", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक adc128_init_client(काष्ठा adc128_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक err;
	u8 regval = 0x0;

	/*
	 * Reset chip to शेषs.
	 * This makes most other initializations unnecessary.
	 */
	err = i2c_smbus_ग_लिखो_byte_data(client, ADC128_REG_CONFIG, 0x80);
	अगर (err)
		वापस err;

	/* Set operation mode, अगर non-शेष */
	अगर (data->mode != 0)
		regval |= data->mode << 1;

	/* If बाह्यal vref is selected, configure the chip to use it */
	अगर (data->regulator)
		regval |= 0x01;

	/* Write advanced configuration रेजिस्टर */
	अगर (regval != 0x0) अणु
		err = i2c_smbus_ग_लिखो_byte_data(client, ADC128_REG_CONFIG_ADV,
						regval);
		अगर (err)
			वापस err;
	पूर्ण

	/* Start monitoring */
	err = i2c_smbus_ग_लिखो_byte_data(client, ADC128_REG_CONFIG, 0x01);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक adc128_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा regulator *regulator;
	काष्ठा device *hwmon_dev;
	काष्ठा adc128_data *data;
	पूर्णांक err, vref;

	data = devm_kzalloc(dev, माप(काष्ठा adc128_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* vref is optional. If specअगरied, is used as chip reference voltage */
	regulator = devm_regulator_get_optional(dev, "vref");
	अगर (!IS_ERR(regulator)) अणु
		data->regulator = regulator;
		err = regulator_enable(regulator);
		अगर (err < 0)
			वापस err;
		vref = regulator_get_voltage(regulator);
		अगर (vref < 0) अणु
			err = vref;
			जाओ error;
		पूर्ण
		data->vref = DIV_ROUND_CLOSEST(vref, 1000);
	पूर्ण अन्यथा अणु
		data->vref = 2560;	/* 2.56V, in mV */
	पूर्ण

	/* Operation mode is optional. If unspecअगरied, keep current mode */
	अगर (of_property_पढ़ो_u8(dev->of_node, "ti,mode", &data->mode) == 0) अणु
		अगर (data->mode > 3) अणु
			dev_err(dev, "invalid operation mode %d\n",
				data->mode);
			err = -EINVAL;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = i2c_smbus_पढ़ो_byte_data(client, ADC128_REG_CONFIG_ADV);
		अगर (err < 0)
			जाओ error;
		data->mode = (err >> 1) & ADC128_REG_MASK;
	पूर्ण

	data->client = client;
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the chip */
	err = adc128_init_client(data);
	अगर (err < 0)
		जाओ error;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, adc128_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		err = PTR_ERR(hwmon_dev);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	अगर (data->regulator)
		regulator_disable(data->regulator);
	वापस err;
पूर्ण

अटल पूर्णांक adc128_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adc128_data *data = i2c_get_clientdata(client);

	अगर (data->regulator)
		regulator_disable(data->regulator);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adc128_id[] = अणु
	अणु "adc128d818", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adc128_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused adc128_of_match[] = अणु
	अणु .compatible = "ti,adc128d818" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adc128_of_match);

अटल काष्ठा i2c_driver adc128_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adc128d818",
		.of_match_table = of_match_ptr(adc128_of_match),
	पूर्ण,
	.probe_new	= adc128_probe,
	.हटाओ		= adc128_हटाओ,
	.id_table	= adc128_id,
	.detect		= adc128_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adc128_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("Driver for ADC128D818");
MODULE_LICENSE("GPL");
