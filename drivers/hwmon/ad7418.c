<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An hwmon driver क्रम the Analog Devices AD7416/17/18
 * Copyright (C) 2006-07 Tower Technologies
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 * Based on lm75.c
 * Copyright (C) 1998-99 Froकरो Looijaard <froकरोl@dds.nl>
 */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "lm75.h"

#घोषणा DRV_VERSION "0.4"

क्रमागत chips अणु ad7416, ad7417, ad7418 पूर्ण;

/* AD7418 रेजिस्टरs */
#घोषणा AD7418_REG_TEMP_IN	0x00
#घोषणा AD7418_REG_CONF		0x01
#घोषणा AD7418_REG_TEMP_HYST	0x02
#घोषणा AD7418_REG_TEMP_OS	0x03
#घोषणा AD7418_REG_ADC		0x04
#घोषणा AD7418_REG_CONF2	0x05

#घोषणा AD7418_REG_ADC_CH(x)	((x) << 5)
#घोषणा AD7418_CH_TEMP		AD7418_REG_ADC_CH(0)

अटल स्थिर u8 AD7418_REG_TEMP[] = अणु AD7418_REG_TEMP_IN,
					AD7418_REG_TEMP_HYST,
					AD7418_REG_TEMP_OS पूर्ण;

काष्ठा ad7418_data अणु
	काष्ठा i2c_client	*client;
	क्रमागत chips		type;
	काष्ठा mutex		lock;
	पूर्णांक			adc_max;	/* number of ADC channels */
	अक्षर			valid;
	अचिन्हित दीर्घ		last_updated;	/* In jअगरfies */
	s16			temp[3];	/* Register values */
	u16			in[4];
पूर्ण;

अटल पूर्णांक ad7418_update_device(काष्ठा device *dev)
अणु
	काष्ठा ad7418_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	s32 val;

	mutex_lock(&data->lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
		|| !data->valid) अणु
		u8 cfg;
		पूर्णांक i, ch;

		/* पढ़ो config रेजिस्टर and clear channel bits */
		val = i2c_smbus_पढ़ो_byte_data(client, AD7418_REG_CONF);
		अगर (val < 0)
			जाओ पात;

		cfg = val;
		cfg &= 0x1F;

		val = i2c_smbus_ग_लिखो_byte_data(client, AD7418_REG_CONF,
						cfg | AD7418_CH_TEMP);
		अगर (val < 0)
			जाओ पात;

		udelay(30);

		क्रम (i = 0; i < 3; i++) अणु
			val = i2c_smbus_पढ़ो_word_swapped(client,
							  AD7418_REG_TEMP[i]);
			अगर (val < 0)
				जाओ पात;

			data->temp[i] = val;
		पूर्ण

		क्रम (i = 0, ch = 4; i < data->adc_max; i++, ch--) अणु
			val = i2c_smbus_ग_लिखो_byte_data(client, AD7418_REG_CONF,
					cfg | AD7418_REG_ADC_CH(ch));
			अगर (val < 0)
				जाओ पात;

			udelay(15);
			val = i2c_smbus_पढ़ो_word_swapped(client,
							  AD7418_REG_ADC);
			अगर (val < 0)
				जाओ पात;

			data->in[data->adc_max - 1 - i] = val;
		पूर्ण

		/* restore old configuration value */
		val = i2c_smbus_ग_लिखो_word_swapped(client, AD7418_REG_CONF,
						   cfg);
		अगर (val < 0)
			जाओ पात;

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->lock);
	वापस 0;

पात:
	data->valid = 0;
	mutex_unlock(&data->lock);
	वापस val;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा ad7418_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = ad7418_update_device(dev);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n",
		LM75_TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार adc_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा ad7418_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = ad7418_update_device(dev);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n",
		((data->in[attr->index] >> 6) * 2500 + 512) / 1024);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा ad7418_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;
	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &temp);

	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->lock);
	data->temp[attr->index] = LM75_TEMP_TO_REG(temp);
	i2c_smbus_ग_लिखो_word_swapped(client,
				     AD7418_REG_TEMP[attr->index],
				     data->temp[attr->index]);
	mutex_unlock(&data->lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, 2);

अटल SENSOR_DEVICE_ATTR_RO(in1_input, adc, 0);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, adc, 1);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, adc, 2);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, adc, 3);

अटल काष्ठा attribute *ad7416_attrs[] = अणु
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(ad7416);

अटल काष्ठा attribute *ad7417_attrs[] = अणु
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(ad7417);

अटल काष्ठा attribute *ad7418_attrs[] = अणु
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(ad7418);

अटल व्योम ad7418_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा ad7418_data *data = i2c_get_clientdata(client);

	पूर्णांक reg = i2c_smbus_पढ़ो_byte_data(client, AD7418_REG_CONF);
	अगर (reg < 0) अणु
		dev_err(&client->dev, "cannot read configuration register\n");
	पूर्ण अन्यथा अणु
		dev_info(&client->dev, "configuring for mode 1\n");
		i2c_smbus_ग_लिखो_byte_data(client, AD7418_REG_CONF, reg & 0xfe);

		अगर (data->type == ad7417 || data->type == ad7418)
			i2c_smbus_ग_लिखो_byte_data(client,
						AD7418_REG_CONF2, 0x00);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad7418_id[];

अटल पूर्णांक ad7418_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा ad7418_data *data;
	काष्ठा device *hwmon_dev;
	स्थिर काष्ठा attribute_group **attr_groups = शून्य;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EOPNOTSUPP;

	data = devm_kzalloc(dev, माप(काष्ठा ad7418_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);

	mutex_init(&data->lock);
	data->client = client;
	अगर (dev->of_node)
		data->type = (क्रमागत chips)of_device_get_match_data(dev);
	अन्यथा
		data->type = i2c_match_id(ad7418_id, client)->driver_data;

	चयन (data->type) अणु
	हाल ad7416:
		data->adc_max = 0;
		attr_groups = ad7416_groups;
		अवरोध;

	हाल ad7417:
		data->adc_max = 4;
		attr_groups = ad7417_groups;
		अवरोध;

	हाल ad7418:
		data->adc_max = 1;
		attr_groups = ad7418_groups;
		अवरोध;
	पूर्ण

	dev_info(dev, "%s chip found\n", client->name);

	/* Initialize the AD7418 chip */
	ad7418_init_client(client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
							   client->name,
							   data, attr_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad7418_id[] = अणु
	अणु "ad7416", ad7416 पूर्ण,
	अणु "ad7417", ad7417 पूर्ण,
	अणु "ad7418", ad7418 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad7418_id);

अटल स्थिर काष्ठा of_device_id ad7418_dt_ids[] = अणु
	अणु .compatible = "adi,ad7416", .data = (व्योम *)ad7416, पूर्ण,
	अणु .compatible = "adi,ad7417", .data = (व्योम *)ad7417, पूर्ण,
	अणु .compatible = "adi,ad7418", .data = (व्योम *)ad7418, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7418_dt_ids);

अटल काष्ठा i2c_driver ad7418_driver = अणु
	.driver = अणु
		.name	= "ad7418",
		.of_match_table = ad7418_dt_ids,
	पूर्ण,
	.probe_new	= ad7418_probe,
	.id_table	= ad7418_id,
पूर्ण;

module_i2c_driver(ad7418_driver);

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("AD7416/17/18 driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
