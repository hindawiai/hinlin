<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * An hwmon driver क्रम the Analog Devices AD7414
 *
 * Copyright 2006 Stefan Roese <sr at denx.de>, DENX Software Engineering
 *
 * Copyright (c) 2008 PIKA Technologies
 *   Sean MacLennan <smaclennan@pikatech.com>
 *
 * Copyright (c) 2008 Spansion Inc.
 *   Frank Edelhaeuser <frank.edelhaeuser at spansion.com>
 *   (converted to "new style" I2C driver model, हटाओd checkpatch.pl warnings)
 *
 * Based on ad7418.c
 * Copyright 2006 Tower Technologies, Alessandro Zummo <a.zummo at towertech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>


/* AD7414 रेजिस्टरs */
#घोषणा AD7414_REG_TEMP		0x00
#घोषणा AD7414_REG_CONF		0x01
#घोषणा AD7414_REG_T_HIGH	0x02
#घोषणा AD7414_REG_T_LOW	0x03

अटल u8 AD7414_REG_LIMIT[] = अणु AD7414_REG_T_HIGH, AD7414_REG_T_LOW पूर्ण;

काष्ठा ad7414_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		lock;	/* atomic पढ़ो data updates */
	अक्षर			valid;	/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ		next_update;	/* In jअगरfies */
	s16			temp_input;	/* Register values */
	s8			temps[ARRAY_SIZE(AD7414_REG_LIMIT)];
पूर्ण;

/* REG: (0.25C/bit, two's complement) << 6 */
अटल अंतरभूत पूर्णांक ad7414_temp_from_reg(s16 reg)
अणु
	/*
	 * use पूर्णांकeger भागision instead of equivalent right shअगरt to
	 * guarantee arithmetic shअगरt and preserve the sign
	 */
	वापस ((पूर्णांक)reg / 64) * 250;
पूर्ण

अटल अंतरभूत पूर्णांक ad7414_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	अगर (reg == AD7414_REG_TEMP)
		वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
	अन्यथा
		वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक ad7414_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल काष्ठा ad7414_data *ad7414_update_device(काष्ठा device *dev)
अणु
	काष्ठा ad7414_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->lock);

	अगर (समय_after(jअगरfies, data->next_update) || !data->valid) अणु
		पूर्णांक value, i;

		dev_dbg(&client->dev, "starting ad7414 update\n");

		value = ad7414_पढ़ो(client, AD7414_REG_TEMP);
		अगर (value < 0)
			dev_dbg(&client->dev, "AD7414_REG_TEMP err %d\n",
				value);
		अन्यथा
			data->temp_input = value;

		क्रम (i = 0; i < ARRAY_SIZE(AD7414_REG_LIMIT); ++i) अणु
			value = ad7414_पढ़ो(client, AD7414_REG_LIMIT[i]);
			अगर (value < 0)
				dev_dbg(&client->dev, "AD7414 reg %d err %d\n",
					AD7414_REG_LIMIT[i], value);
			अन्यथा
				data->temps[i] = value;
		पूर्ण

		data->next_update = jअगरfies + HZ + HZ / 2;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस data;
पूर्ण

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ad7414_data *data = ad7414_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", ad7414_temp_from_reg(data->temp_input));
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_input, 0);

अटल sमाप_प्रकार max_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा ad7414_data *data = ad7414_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temps[index] * 1000);
पूर्ण

अटल sमाप_प्रकार max_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा ad7414_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	u8 reg = AD7414_REG_LIMIT[index];
	दीर्घ temp;
	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &temp);

	अगर (ret < 0)
		वापस ret;

	temp = clamp_val(temp, -40000, 85000);
	temp = (temp + (temp < 0 ? -500 : 500)) / 1000;

	mutex_lock(&data->lock);
	data->temps[index] = temp;
	ad7414_ग_लिखो(client, reg, temp);
	mutex_unlock(&data->lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_max, max_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, max_min, 1);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा ad7414_data *data = ad7414_update_device(dev);
	पूर्णांक value = (data->temp_input >> bitnr) & 1;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 4);

अटल काष्ठा attribute *ad7414_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(ad7414);

अटल पूर्णांक ad7414_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ad7414_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक conf;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -EOPNOTSUPP;

	data = devm_kzalloc(dev, माप(काष्ठा ad7414_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->lock);

	dev_info(&client->dev, "chip found\n");

	/* Make sure the chip is घातered up. */
	conf = i2c_smbus_पढ़ो_byte_data(client, AD7414_REG_CONF);
	अगर (conf < 0)
		dev_warn(dev, "ad7414_probe unable to read config register.\n");
	अन्यथा अणु
		conf &= ~(1 << 7);
		i2c_smbus_ग_लिखो_byte_data(client, AD7414_REG_CONF, conf);
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
							   client->name,
							   data, ad7414_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad7414_id[] = अणु
	अणु "ad7414", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad7414_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ad7414_of_match[] = अणु
	अणु .compatible = "ad,ad7414" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7414_of_match);

अटल काष्ठा i2c_driver ad7414_driver = अणु
	.driver = अणु
		.name	= "ad7414",
		.of_match_table = of_match_ptr(ad7414_of_match),
	पूर्ण,
	.probe_new = ad7414_probe,
	.id_table = ad7414_id,
पूर्ण;

module_i2c_driver(ad7414_driver);

MODULE_AUTHOR("Stefan Roese <sr at denx.de>, "
	      "Frank Edelhaeuser <frank.edelhaeuser at spansion.com>");

MODULE_DESCRIPTION("AD7414 driver");
MODULE_LICENSE("GPL");
