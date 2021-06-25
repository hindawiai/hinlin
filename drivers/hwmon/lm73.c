<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LM73 Sensor driver
 * Based on LM75
 *
 * Copyright (C) 2007, CenoSYS (www.cenosys.com).
 * Copyright (C) 2009, Bollore telecom (www.bolloretelecom.eu).
 *
 * Guillaume Ligneul <guillaume.ligneul@gmail.com>
 * Adrien Demarez <adrien.demarez@bolloretelecom.eu>
 * Jeremy Laine <jeremy.laine@bolloretelecom.eu>
 * Chris Verges <kg4ysn@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>


/* Addresses scanned */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x48, 0x49, 0x4a, 0x4c,
					0x4d, 0x4e, I2C_CLIENT_END पूर्ण;

/* LM73 रेजिस्टरs */
#घोषणा LM73_REG_INPUT		0x00
#घोषणा LM73_REG_CONF		0x01
#घोषणा LM73_REG_MAX		0x02
#घोषणा LM73_REG_MIN		0x03
#घोषणा LM73_REG_CTRL		0x04
#घोषणा LM73_REG_ID		0x07

#घोषणा LM73_ID			0x9001	/* 0x0190, byte-swapped */
#घोषणा DRVNAME			"lm73"
#घोषणा LM73_TEMP_MIN		(-256000 / 250)
#घोषणा LM73_TEMP_MAX		(255750 / 250)

#घोषणा LM73_CTRL_RES_SHIFT	5
#घोषणा LM73_CTRL_RES_MASK	(BIT(5) | BIT(6))
#घोषणा LM73_CTRL_TO_MASK	BIT(7)

#घोषणा LM73_CTRL_HI_SHIFT	2
#घोषणा LM73_CTRL_LO_SHIFT	1

अटल स्थिर अचिन्हित लघु lm73_convrates[] = अणु
	14,	/* 11-bits (0.25000 C/LSB): RES1 Bit = 0, RES0 Bit = 0 */
	28,	/* 12-bits (0.12500 C/LSB): RES1 Bit = 0, RES0 Bit = 1 */
	56,	/* 13-bits (0.06250 C/LSB): RES1 Bit = 1, RES0 Bit = 0 */
	112,	/* 14-bits (0.03125 C/LSB): RES1 Bit = 1, RES0 Bit = 1 */
पूर्ण;

काष्ठा lm73_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 ctrl;			/* control रेजिस्टर value */
पूर्ण;

/*-----------------------------------------------------------------------*/

अटल sमाप_प्रकार temp_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm73_data *data = dev_get_drvdata(dev);
	दीर्घ temp;
	लघु value;
	s32 err;

	पूर्णांक status = kम_से_दीर्घ(buf, 10, &temp);
	अगर (status < 0)
		वापस status;

	/* Write value */
	value = clamp_val(temp / 250, LM73_TEMP_MIN, LM73_TEMP_MAX) << 5;
	err = i2c_smbus_ग_लिखो_word_swapped(data->client, attr->index, value);
	वापस (err < 0) ? err : count;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm73_data *data = dev_get_drvdata(dev);
	पूर्णांक temp;

	s32 err = i2c_smbus_पढ़ो_word_swapped(data->client, attr->index);
	अगर (err < 0)
		वापस err;

	/* use पूर्णांकeger भागision instead of equivalent right shअगरt to
	   guarantee arithmetic shअगरt and preserve the sign */
	temp = (((s16) err) * 250) / 32;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार convrate_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm73_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ convrate;
	s32 err;
	पूर्णांक res = 0;

	err = kम_से_अदीर्घ(buf, 10, &convrate);
	अगर (err < 0)
		वापस err;

	/*
	 * Convert the desired conversion rate पूर्णांकo रेजिस्टर bits.
	 * res is alपढ़ोy initialized, and everything past the second-to-last
	 * value in the array is treated as beदीर्घing to the last value
	 * in the array.
	 */
	जबतक (res < (ARRAY_SIZE(lm73_convrates) - 1) &&
			convrate > lm73_convrates[res])
		res++;

	mutex_lock(&data->lock);
	data->ctrl &= LM73_CTRL_TO_MASK;
	data->ctrl |= res << LM73_CTRL_RES_SHIFT;
	err = i2c_smbus_ग_लिखो_byte_data(data->client, LM73_REG_CTRL,
					data->ctrl);
	mutex_unlock(&data->lock);

	अगर (err < 0)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार convrate_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			     अक्षर *buf)
अणु
	काष्ठा lm73_data *data = dev_get_drvdata(dev);
	पूर्णांक res;

	res = (data->ctrl & LM73_CTRL_RES_MASK) >> LM73_CTRL_RES_SHIFT;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%hu\n", lm73_convrates[res]);
पूर्ण

अटल sमाप_प्रकार maxmin_alarm_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm73_data *data = dev_get_drvdata(dev);
	s32 ctrl;

	mutex_lock(&data->lock);
	ctrl = i2c_smbus_पढ़ो_byte_data(data->client, LM73_REG_CTRL);
	अगर (ctrl < 0)
		जाओ पात;
	data->ctrl = ctrl;
	mutex_unlock(&data->lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (ctrl >> attr->index) & 1);

पात:
	mutex_unlock(&data->lock);
	वापस ctrl;
पूर्ण

/*-----------------------------------------------------------------------*/

/* sysfs attributes क्रम hwmon */

अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, LM73_REG_MAX);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp, LM73_REG_MIN);
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, LM73_REG_INPUT);
अटल SENSOR_DEVICE_ATTR_RW(update_पूर्णांकerval, convrate, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, maxmin_alarm,
			     LM73_CTRL_HI_SHIFT);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, maxmin_alarm,
			     LM73_CTRL_LO_SHIFT);

अटल काष्ठा attribute *lm73_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_update_पूर्णांकerval.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm73);

/*-----------------------------------------------------------------------*/

/* device probe and removal */

अटल पूर्णांक
lm73_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm73_data *data;
	पूर्णांक ctrl;

	data = devm_kzalloc(dev, माप(काष्ठा lm73_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->lock);

	ctrl = i2c_smbus_पढ़ो_byte_data(client, LM73_REG_CTRL);
	अगर (ctrl < 0)
		वापस ctrl;
	data->ctrl = ctrl;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, lm73_groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(dev, "sensor '%s'\n", client->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm73_ids[] = अणु
	अणु "lm73", 0 पूर्ण,
	अणु /* LIST END */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm73_ids);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm73_detect(काष्ठा i2c_client *new_client,
			काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	पूर्णांक id, ctrl, conf;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	/*
	 * Do as much detection as possible with byte पढ़ोs first, as word
	 * पढ़ोs can confuse other devices.
	 */
	ctrl = i2c_smbus_पढ़ो_byte_data(new_client, LM73_REG_CTRL);
	अगर (ctrl < 0 || (ctrl & 0x10))
		वापस -ENODEV;

	conf = i2c_smbus_पढ़ो_byte_data(new_client, LM73_REG_CONF);
	अगर (conf < 0 || (conf & 0x0c))
		वापस -ENODEV;

	id = i2c_smbus_पढ़ो_byte_data(new_client, LM73_REG_ID);
	अगर (id < 0 || id != (LM73_ID & 0xff))
		वापस -ENODEV;

	/* Check device ID */
	id = i2c_smbus_पढ़ो_word_data(new_client, LM73_REG_ID);
	अगर (id < 0 || id != LM73_ID)
		वापस -ENODEV;

	strlcpy(info->type, "lm73", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lm73_of_match[] = अणु
	अणु
		.compatible = "ti,lm73",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, lm73_of_match);

अटल काष्ठा i2c_driver lm73_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm73",
		.of_match_table = lm73_of_match,
	पूर्ण,
	.probe_new	= lm73_probe,
	.id_table	= lm73_ids,
	.detect		= lm73_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm73_driver);

MODULE_AUTHOR("Guillaume Ligneul <guillaume.ligneul@gmail.com>");
MODULE_DESCRIPTION("LM73 driver");
MODULE_LICENSE("GPL");
