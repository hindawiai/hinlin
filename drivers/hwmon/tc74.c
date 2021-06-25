<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * An hwmon driver क्रम the Microchip TC74
 *
 * Copyright 2015 Maciej Szmigiero <mail@maciej.szmigiero.name>
 *
 * Based on ad7414.c:
 *	Copyright 2006 Stefan Roese, DENX Software Engineering
 *	Copyright 2008 Sean MacLennan, PIKA Technologies
 *	Copyright 2008 Frank Edelhaeuser, Spansion Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

/* TC74 रेजिस्टरs */
#घोषणा TC74_REG_TEMP		0x00
#घोषणा TC74_REG_CONFIG		0x01

काष्ठा tc74_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		lock;	/* atomic पढ़ो data updates */
	bool			valid;	/* validity of fields below */
	अचिन्हित दीर्घ		next_update;	/* In jअगरfies */
	s8			temp_input;	/* Temp value in dC */
पूर्ण;

अटल पूर्णांक tc74_update_device(काष्ठा device *dev)
अणु
	काष्ठा tc74_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&data->lock);
	अगर (ret)
		वापस ret;

	अगर (समय_after(jअगरfies, data->next_update) || !data->valid) अणु
		s32 value;

		value = i2c_smbus_पढ़ो_byte_data(client, TC74_REG_CONFIG);
		अगर (value < 0) अणु
			dev_dbg(&client->dev, "TC74_REG_CONFIG read err %d\n",
				(पूर्णांक)value);

			ret = value;
			जाओ ret_unlock;
		पूर्ण

		अगर (!(value & BIT(6))) अणु
			/* not पढ़ोy yet */

			ret = -EAGAIN;
			जाओ ret_unlock;
		पूर्ण

		value = i2c_smbus_पढ़ो_byte_data(client, TC74_REG_TEMP);
		अगर (value < 0) अणु
			dev_dbg(&client->dev, "TC74_REG_TEMP read err %d\n",
				(पूर्णांक)value);

			ret = value;
			जाओ ret_unlock;
		पूर्ण

		data->temp_input = value;
		data->next_update = jअगरfies + HZ / 4;
		data->valid = true;
	पूर्ण

ret_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tc74_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = tc74_update_device(dev);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", data->temp_input * 1000);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_input, 0);

अटल काष्ठा attribute *tc74_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(tc74);

अटल पूर्णांक tc74_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tc74_data *data;
	काष्ठा device *hwmon_dev;
	s32 conf;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EOPNOTSUPP;

	data = devm_kzalloc(dev, माप(काष्ठा tc74_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->lock);

	/* Make sure the chip is घातered up. */
	conf = i2c_smbus_पढ़ो_byte_data(client, TC74_REG_CONFIG);
	अगर (conf < 0) अणु
		dev_err(dev, "unable to read config register\n");

		वापस conf;
	पूर्ण

	अगर (conf & 0x3f) अणु
		dev_err(dev, "invalid config register value\n");

		वापस -ENODEV;
	पूर्ण

	अगर (conf & BIT(7)) अणु
		s32 ret;

		conf &= ~BIT(7);

		ret = i2c_smbus_ग_लिखो_byte_data(client, TC74_REG_CONFIG, conf);
		अगर (ret)
			dev_warn(dev, "unable to disable STANDBY\n");
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
							   client->name,
							   data, tc74_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tc74_id[] = अणु
	अणु "tc74", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tc74_id);

अटल काष्ठा i2c_driver tc74_driver = अणु
	.driver = अणु
		.name	= "tc74",
	पूर्ण,
	.probe_new = tc74_probe,
	.id_table = tc74_id,
पूर्ण;

module_i2c_driver(tc74_driver);

MODULE_AUTHOR("Maciej Szmigiero <mail@maciej.szmigiero.name>");

MODULE_DESCRIPTION("TC74 driver");
MODULE_LICENSE("GPL");
