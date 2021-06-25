<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm92 - Hardware monitoring driver
 * Copyright (C) 2005-2008  Jean Delvare <jdelvare@suse.de>
 *
 * Based on the lm90 driver, with some ideas taken from the lm_sensors
 * lm92 driver as well.
 *
 * The LM92 is a sensor chip made by National Semiconductor. It reports
 * its own temperature with a 0.0625 deg resolution and a 0.33 deg
 * accuracy. Complete datasheet can be obtained from National's website
 * at:
 *   http://www.national.com/pf/LM/LM92.hपंचांगl
 *
 * This driver also supports the MAX6635 sensor chip made by Maxim.
 * This chip is compatible with the LM92, but has a lesser accuracy
 * (1.0 deg). Complete datasheet can be obtained from Maxim's website
 * at:
 *   http://www.maxim-ic.com/quick_view2.cfm/qv_pk/3074
 *
 * Since the LM92 was the first chipset supported by this driver, most
 * comments will refer to this chipset, but are actually general and
 * concern all supported chipsets, unless mentioned otherwise.
 *
 * Support could easily be added क्रम the National Semiconductor LM76
 * and Maxim MAX6633 and MAX6634 chips, which are mostly compatible
 * with the LM92.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>

/*
 * The LM92 and MAX6635 have 2 two-state pins क्रम address selection,
 * resulting in 4 possible addresses.
 */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x48, 0x49, 0x4a, 0x4b,
						I2C_CLIENT_END पूर्ण;
क्रमागत chips अणु lm92, max6635 पूर्ण;

/* The LM92 रेजिस्टरs */
#घोषणा LM92_REG_CONFIG			0x01 /* 8-bit, RW */
#घोषणा LM92_REG_TEMP			0x00 /* 16-bit, RO */
#घोषणा LM92_REG_TEMP_HYST		0x02 /* 16-bit, RW */
#घोषणा LM92_REG_TEMP_CRIT		0x03 /* 16-bit, RW */
#घोषणा LM92_REG_TEMP_LOW		0x04 /* 16-bit, RW */
#घोषणा LM92_REG_TEMP_HIGH		0x05 /* 16-bit, RW */
#घोषणा LM92_REG_MAN_ID			0x07 /* 16-bit, RO, LM92 only */

/*
 * The LM92 uses चिन्हित 13-bit values with LSB = 0.0625 degree Celsius,
 * left-justअगरied in 16-bit रेजिस्टरs. No rounding is करोne, with such
 * a resolution it's just not worth it. Note that the MAX6635 doesn't
 * make use of the 4 lower bits क्रम limits (i.e. effective resolution
 * क्रम limits is 1 degree Celsius).
 */
अटल अंतरभूत पूर्णांक TEMP_FROM_REG(s16 reg)
अणु
	वापस reg / 8 * 625 / 10;
पूर्ण

अटल अंतरभूत s16 TEMP_TO_REG(दीर्घ val)
अणु
	val = clamp_val(val, -60000, 160000);
	वापस val * 10 / 625 * 8;
पूर्ण

/* Alarm flags are stored in the 3 LSB of the temperature रेजिस्टर */
अटल अंतरभूत u8 ALARMS_FROM_REG(s16 reg)
अणु
	वापस reg & 0x0007;
पूर्ण

क्रमागत temp_index अणु
	t_input,
	t_crit,
	t_min,
	t_max,
	t_hyst,
	t_num_regs
पूर्ण;

अटल स्थिर u8 regs[t_num_regs] = अणु
	[t_input] = LM92_REG_TEMP,
	[t_crit] = LM92_REG_TEMP_CRIT,
	[t_min] = LM92_REG_TEMP_LOW,
	[t_max] = LM92_REG_TEMP_HIGH,
	[t_hyst] = LM92_REG_TEMP_HYST,
पूर्ण;

/* Client data (each client माला_लो its own) */
काष्ठा lm92_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टरs values */
	s16 temp[t_num_regs];	/* index with क्रमागत temp_index */
पूर्ण;

/*
 * Sysfs attributes and callback functions
 */

अटल काष्ठा lm92_data *lm92_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm92_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) ||
	    !data->valid) अणु
		dev_dbg(&client->dev, "Updating lm92 data\n");
		क्रम (i = 0; i < t_num_regs; i++) अणु
			data->temp[i] =
				i2c_smbus_पढ़ो_word_swapped(client, regs[i]);
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm92_data *data = lm92_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm92_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[nr] = TEMP_TO_REG(val);
	i2c_smbus_ग_लिखो_word_swapped(client, regs[nr], data->temp[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_hyst_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm92_data *data = lm92_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[attr->index])
		       - TEMP_FROM_REG(data->temp[t_hyst]));
पूर्ण

अटल sमाप_प्रकार temp1_min_hyst_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm92_data *data = lm92_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[t_min])
		       + TEMP_FROM_REG(data->temp[t_hyst]));
पूर्ण

अटल sमाप_प्रकार temp_hyst_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm92_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val = clamp_val(val, -120000, 220000);
	mutex_lock(&data->update_lock);
	data->temp[t_hyst] =
		TEMP_TO_REG(TEMP_FROM_REG(data->temp[attr->index]) - val);
	i2c_smbus_ग_लिखो_word_swapped(client, LM92_REG_TEMP_HYST,
				     data->temp[t_hyst]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm92_data *data = lm92_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", ALARMS_FROM_REG(data->temp[t_input]));
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm92_data *data = lm92_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->temp[t_input] >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, t_input);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp, t_crit);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit_hyst, temp_hyst, t_crit);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp, t_min);
अटल DEVICE_ATTR_RO(temp1_min_hyst);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, t_max);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_hyst, temp_hyst, t_max);
अटल DEVICE_ATTR_RO(alarms);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 1);

/*
 * Detection and registration
 */

अटल व्योम lm92_init_client(काष्ठा i2c_client *client)
अणु
	u8 config;

	/* Start the conversions अगर needed */
	config = i2c_smbus_पढ़ो_byte_data(client, LM92_REG_CONFIG);
	अगर (config & 0x01)
		i2c_smbus_ग_लिखो_byte_data(client, LM92_REG_CONFIG,
					  config & 0xFE);
पूर्ण

अटल काष्ठा attribute *lm92_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&dev_attr_temp1_min_hyst.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&dev_attr_alarms.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm92);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm92_detect(काष्ठा i2c_client *new_client,
		       काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	u8 config;
	u16 man_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
					    | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	config = i2c_smbus_पढ़ो_byte_data(new_client, LM92_REG_CONFIG);
	man_id = i2c_smbus_पढ़ो_word_data(new_client, LM92_REG_MAN_ID);

	अगर ((config & 0xe0) == 0x00 && man_id == 0x0180)
		pr_info("lm92: Found National Semiconductor LM92 chip\n");
	अन्यथा
		वापस -ENODEV;

	strlcpy(info->type, "lm92", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक lm92_probe(काष्ठा i2c_client *new_client)
अणु
	काष्ठा device *hwmon_dev;
	काष्ठा lm92_data *data;

	data = devm_kzalloc(&new_client->dev, माप(काष्ठा lm92_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = new_client;
	mutex_init(&data->update_lock);

	/* Initialize the chipset */
	lm92_init_client(new_client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&new_client->dev,
							   new_client->name,
							   data, lm92_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/*
 * Module and driver stuff
 */

अटल स्थिर काष्ठा i2c_device_id lm92_id[] = अणु
	अणु "lm92", lm92 पूर्ण,
	अणु "max6635", max6635 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm92_id);

अटल काष्ठा i2c_driver lm92_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm92",
	पूर्ण,
	.probe_new	= lm92_probe,
	.id_table	= lm92_id,
	.detect		= lm92_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm92_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("LM92/MAX6635 driver");
MODULE_LICENSE("GPL");
