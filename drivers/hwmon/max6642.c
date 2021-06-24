<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम +/-1 degree C, SMBus-Compatible Remote/Local Temperature Sensor
 * with Overtemperature Alarm
 *
 * Copyright (C) 2011 AppearTV AS
 *
 * Derived from:
 *
 *  Based on the max1619 driver.
 *  Copyright (C) 2003-2004 Oleksij Rempel <bug-track@fisher-privat.net>
 *                          Jean Delvare <jdelvare@suse.de>
 *
 * The MAX6642 is a sensor chip made by Maxim.
 * It reports up to two temperatures (its own plus up to
 * one बाह्यal one). Complete datasheet can be
 * obtained from Maxim's website at:
 *   http://datasheets.maxim-ic.com/en/ds/MAX6642.pdf
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

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, I2C_CLIENT_END पूर्ण;

/*
 * The MAX6642 रेजिस्टरs
 */

#घोषणा MAX6642_REG_R_MAN_ID		0xFE
#घोषणा MAX6642_REG_R_CONFIG		0x03
#घोषणा MAX6642_REG_W_CONFIG		0x09
#घोषणा MAX6642_REG_R_STATUS		0x02
#घोषणा MAX6642_REG_R_LOCAL_TEMP	0x00
#घोषणा MAX6642_REG_R_LOCAL_TEMPL	0x11
#घोषणा MAX6642_REG_R_LOCAL_HIGH	0x05
#घोषणा MAX6642_REG_W_LOCAL_HIGH	0x0B
#घोषणा MAX6642_REG_R_REMOTE_TEMP	0x01
#घोषणा MAX6642_REG_R_REMOTE_TEMPL	0x10
#घोषणा MAX6642_REG_R_REMOTE_HIGH	0x07
#घोषणा MAX6642_REG_W_REMOTE_HIGH	0x0D

/*
 * Conversions
 */

अटल पूर्णांक temp_from_reg10(पूर्णांक val)
अणु
	वापस val * 250;
पूर्ण

अटल पूर्णांक temp_from_reg(पूर्णांक val)
अणु
	वापस val * 1000;
पूर्ण

अटल पूर्णांक temp_to_reg(पूर्णांक val)
अणु
	वापस val / 1000;
पूर्ण

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा max6642_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	bool valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टरs values */
	u16 temp_input[2]; /* local/remote */
	u16 temp_high[2]; /* local/remote */
	u8 alarms;
पूर्ण;

/*
 * Real code
 */

अटल व्योम max6642_init_client(काष्ठा max6642_data *data,
				काष्ठा i2c_client *client)
अणु
	u8 config;

	/*
	 * Start the conversions.
	 */
	config = i2c_smbus_पढ़ो_byte_data(client, MAX6642_REG_R_CONFIG);
	अगर (config & 0x40)
		i2c_smbus_ग_लिखो_byte_data(client, MAX6642_REG_W_CONFIG,
					  config & 0xBF); /* run */

	data->temp_high[0] = i2c_smbus_पढ़ो_byte_data(client,
				MAX6642_REG_R_LOCAL_HIGH);
	data->temp_high[1] = i2c_smbus_पढ़ो_byte_data(client,
				MAX6642_REG_R_REMOTE_HIGH);
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक max6642_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u8 reg_config, reg_status, man_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* identअगरication */
	man_id = i2c_smbus_पढ़ो_byte_data(client, MAX6642_REG_R_MAN_ID);
	अगर (man_id != 0x4D)
		वापस -ENODEV;

	/* sanity check */
	अगर (i2c_smbus_पढ़ो_byte_data(client, 0x04) != 0x4D
	    || i2c_smbus_पढ़ो_byte_data(client, 0x06) != 0x4D
	    || i2c_smbus_पढ़ो_byte_data(client, 0xff) != 0x4D)
		वापस -ENODEV;

	/*
	 * We पढ़ो the config and status रेजिस्टर, the 4 lower bits in the
	 * config रेजिस्टर should be zero and bit 5, 3, 1 and 0 should be
	 * zero in the status रेजिस्टर.
	 */
	reg_config = i2c_smbus_पढ़ो_byte_data(client, MAX6642_REG_R_CONFIG);
	अगर ((reg_config & 0x0f) != 0x00)
		वापस -ENODEV;

	/* in between, another round of sanity checks */
	अगर (i2c_smbus_पढ़ो_byte_data(client, 0x04) != reg_config
	    || i2c_smbus_पढ़ो_byte_data(client, 0x06) != reg_config
	    || i2c_smbus_पढ़ो_byte_data(client, 0xff) != reg_config)
		वापस -ENODEV;

	reg_status = i2c_smbus_पढ़ो_byte_data(client, MAX6642_REG_R_STATUS);
	अगर ((reg_status & 0x2b) != 0x00)
		वापस -ENODEV;

	strlcpy(info->type, "max6642", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल काष्ठा max6642_data *max6642_update_device(काष्ठा device *dev)
अणु
	काष्ठा max6642_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u16 val, पंचांगp;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		dev_dbg(dev, "Updating max6642 data.\n");
		val = i2c_smbus_पढ़ो_byte_data(client,
					MAX6642_REG_R_LOCAL_TEMPL);
		पंचांगp = (val >> 6) & 3;
		val = i2c_smbus_पढ़ो_byte_data(client,
					MAX6642_REG_R_LOCAL_TEMP);
		val = (val << 2) | पंचांगp;
		data->temp_input[0] = val;
		val = i2c_smbus_पढ़ो_byte_data(client,
					MAX6642_REG_R_REMOTE_TEMPL);
		पंचांगp = (val >> 6) & 3;
		val = i2c_smbus_पढ़ो_byte_data(client,
					MAX6642_REG_R_REMOTE_TEMP);
		val = (val << 2) | पंचांगp;
		data->temp_input[1] = val;
		data->alarms = i2c_smbus_पढ़ो_byte_data(client,
					MAX6642_REG_R_STATUS);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार temp_max10_show(काष्ठा device *dev,
			       काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6642_data *data = max6642_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       temp_from_reg10(data->temp_input[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(attr);
	काष्ठा max6642_data *data = max6642_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", temp_from_reg(data->temp_high[attr2->nr]));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(attr);
	काष्ठा max6642_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_high[attr2->nr] = clamp_val(temp_to_reg(val), 0, 255);
	i2c_smbus_ग_लिखो_byte_data(data->client, attr2->index,
				  data->temp_high[attr2->nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा max6642_data *data = max6642_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_max10, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp_max10, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_max, temp_max, 0,
			       MAX6642_REG_W_LOCAL_HIGH);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_max, temp_max, 1,
			       MAX6642_REG_W_REMOTE_HIGH);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, 4);

अटल काष्ठा attribute *max6642_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,

	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(max6642);

अटल पूर्णांक max6642_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा max6642_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा max6642_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the MAX6642 chip */
	max6642_init_client(data, client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   client->name, data,
							   max6642_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id max6642_id[] = अणु
	अणु "max6642", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max6642_id);

अटल काष्ठा i2c_driver max6642_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "max6642",
	पूर्ण,
	.probe_new	= max6642_probe,
	.id_table	= max6642_id,
	.detect		= max6642_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(max6642_driver);

MODULE_AUTHOR("Per Dalen <per.dalen@appeartv.com>");
MODULE_DESCRIPTION("MAX6642 sensor driver");
MODULE_LICENSE("GPL");
