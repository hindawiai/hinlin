<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ds620.c - Support क्रम temperature sensor and thermostat DS620
 *
 *  Copyright (C) 2010, 2011 Roland Stigge <stigge@antcom.de>
 *
 *  based on ds1621.c by Christian W. Zuckschwerdt  <zany@triq.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_data/ds620.h>

/*
 * Many DS620 स्थिरants specअगरied below
 *  15   14   13   12   11   10   09    08
 * |Done|NVB |THF |TLF |R1  |R0  |AUTOC|1SHOT|
 *
 *  07   06   05   04   03   02   01    00
 * |PO2 |PO1 |A2  |A1  |A0  |    |     |     |
 */
#घोषणा DS620_REG_CONFIG_DONE		0x8000
#घोषणा DS620_REG_CONFIG_NVB		0x4000
#घोषणा DS620_REG_CONFIG_THF		0x2000
#घोषणा DS620_REG_CONFIG_TLF		0x1000
#घोषणा DS620_REG_CONFIG_R1		0x0800
#घोषणा DS620_REG_CONFIG_R0		0x0400
#घोषणा DS620_REG_CONFIG_AUTOC		0x0200
#घोषणा DS620_REG_CONFIG_1SHOT		0x0100
#घोषणा DS620_REG_CONFIG_PO2		0x0080
#घोषणा DS620_REG_CONFIG_PO1		0x0040
#घोषणा DS620_REG_CONFIG_A2		0x0020
#घोषणा DS620_REG_CONFIG_A1		0x0010
#घोषणा DS620_REG_CONFIG_A0		0x0008

/* The DS620 रेजिस्टरs */
अटल स्थिर u8 DS620_REG_TEMP[3] = अणु
	0xAA,			/* input, word, RO */
	0xA2,			/* min, word, RW */
	0xA0,			/* max, word, RW */
पूर्ण;

#घोषणा DS620_REG_CONF		0xAC	/* word, RW */
#घोषणा DS620_COM_START		0x51	/* no data */
#घोषणा DS620_COM_STOP		0x22	/* no data */

/* Each client has this additional data */
काष्ठा ds620_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	s16 temp[3];		/* Register values, word */
पूर्ण;

अटल व्योम ds620_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा ds620_platक्रमm_data *ds620_info = dev_get_platdata(&client->dev);
	u16 conf, new_conf;

	new_conf = conf =
	    i2c_smbus_पढ़ो_word_swapped(client, DS620_REG_CONF);

	/* चयन to continuous conversion mode */
	new_conf &= ~DS620_REG_CONFIG_1SHOT;
	/* alपढ़ोy high at घातer-on, but करोn't trust the BIOS! */
	new_conf |= DS620_REG_CONFIG_PO2;
	/* thermostat mode according to platक्रमm data */
	अगर (ds620_info && ds620_info->pomode == 1)
		new_conf &= ~DS620_REG_CONFIG_PO1; /* PO_LOW */
	अन्यथा अगर (ds620_info && ds620_info->pomode == 2)
		new_conf |= DS620_REG_CONFIG_PO1; /* PO_HIGH */
	अन्यथा
		new_conf &= ~DS620_REG_CONFIG_PO2; /* always low */
	/* with highest precision */
	new_conf |= DS620_REG_CONFIG_R1 | DS620_REG_CONFIG_R0;

	अगर (conf != new_conf)
		i2c_smbus_ग_लिखो_word_swapped(client, DS620_REG_CONF, new_conf);

	/* start conversion */
	i2c_smbus_ग_लिखो_byte(client, DS620_COM_START);
पूर्ण

अटल काष्ठा ds620_data *ds620_update_client(काष्ठा device *dev)
अणु
	काष्ठा ds620_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा ds620_data *ret = data;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		पूर्णांक i;
		पूर्णांक res;

		dev_dbg(&client->dev, "Starting ds620 update\n");

		क्रम (i = 0; i < ARRAY_SIZE(data->temp); i++) अणु
			res = i2c_smbus_पढ़ो_word_swapped(client,
							  DS620_REG_TEMP[i]);
			अगर (res < 0) अणु
				ret = ERR_PTR(res);
				जाओ पात;
			पूर्ण

			data->temp[i] = res;
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ds620_data *data = ds620_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", ((data->temp[attr->index] / 8) * 625) / 10);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक res;
	दीर्घ val;

	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ds620_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	res = kम_से_दीर्घ(buf, 10, &val);

	अगर (res)
		वापस res;

	val = (clamp_val(val, -128000, 128000) * 10 / 625) * 8;

	mutex_lock(&data->update_lock);
	data->temp[attr->index] = val;
	i2c_smbus_ग_लिखो_word_swapped(client, DS620_REG_TEMP[attr->index],
				     data->temp[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ds620_data *data = ds620_update_client(dev);
	काष्ठा i2c_client *client;
	u16 conf, new_conf;
	पूर्णांक res;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	client = data->client;

	/* reset alarms अगर necessary */
	res = i2c_smbus_पढ़ो_word_swapped(client, DS620_REG_CONF);
	अगर (res < 0)
		वापस res;

	new_conf = conf = res;
	new_conf &= ~attr->index;
	अगर (conf != new_conf) अणु
		res = i2c_smbus_ग_लिखो_word_swapped(client, DS620_REG_CONF,
						   new_conf);
		अगर (res < 0)
			वापस res;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", !!(conf & attr->index));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, alarm, DS620_REG_CONFIG_TLF);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, DS620_REG_CONFIG_THF);

अटल काष्ठा attribute *ds620_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(ds620);

अटल पूर्णांक ds620_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा ds620_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा ds620_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the DS620 chip */
	ds620_init_client(client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, ds620_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ds620_id[] = अणु
	अणु"ds620", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ds620_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ds620_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		   .name = "ds620",
	पूर्ण,
	.probe_new = ds620_probe,
	.id_table = ds620_id,
पूर्ण;

module_i2c_driver(ds620_driver);

MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("DS620 driver");
MODULE_LICENSE("GPL");
