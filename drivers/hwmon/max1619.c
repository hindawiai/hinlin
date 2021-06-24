<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max1619.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *             monitoring
 * Copyright (C) 2003-2004 Oleksij Rempel <bug-track@fisher-privat.net>
 *                         Jean Delvare <jdelvare@suse.de>
 *
 * Based on the lm90 driver. The MAX1619 is a sensor chip made by Maxim.
 * It reports up to two temperatures (its own plus up to
 * one बाह्यal one). Complete datasheet can be
 * obtained from Maxim's website at:
 *   http://pdfserv.maxim-ic.com/en/ds/MAX1619.pdf
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
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CLIENT_END पूर्ण;

/*
 * The MAX1619 रेजिस्टरs
 */

#घोषणा MAX1619_REG_R_MAN_ID		0xFE
#घोषणा MAX1619_REG_R_CHIP_ID		0xFF
#घोषणा MAX1619_REG_R_CONFIG		0x03
#घोषणा MAX1619_REG_W_CONFIG		0x09
#घोषणा MAX1619_REG_R_CONVRATE		0x04
#घोषणा MAX1619_REG_W_CONVRATE		0x0A
#घोषणा MAX1619_REG_R_STATUS		0x02
#घोषणा MAX1619_REG_R_LOCAL_TEMP	0x00
#घोषणा MAX1619_REG_R_REMOTE_TEMP	0x01
#घोषणा MAX1619_REG_R_REMOTE_HIGH	0x07
#घोषणा MAX1619_REG_W_REMOTE_HIGH	0x0D
#घोषणा MAX1619_REG_R_REMOTE_LOW	0x08
#घोषणा MAX1619_REG_W_REMOTE_LOW	0x0E
#घोषणा MAX1619_REG_R_REMOTE_CRIT	0x10
#घोषणा MAX1619_REG_W_REMOTE_CRIT	0x12
#घोषणा MAX1619_REG_R_TCRIT_HYST	0x11
#घोषणा MAX1619_REG_W_TCRIT_HYST	0x13

/*
 * Conversions
 */

अटल पूर्णांक temp_from_reg(पूर्णांक val)
अणु
	वापस (val & 0x80 ? val-0x100 : val) * 1000;
पूर्ण

अटल पूर्णांक temp_to_reg(पूर्णांक val)
अणु
	वापस (val < 0 ? val+0x100*1000 : val) / 1000;
पूर्ण

क्रमागत temp_index अणु
	t_input1 = 0,
	t_input2,
	t_low2,
	t_high2,
	t_crit2,
	t_hyst2,
	t_num_regs
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा max1619_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टरs values */
	u8 temp[t_num_regs];	/* index with क्रमागत temp_index */
	u8 alarms;
पूर्ण;

अटल स्थिर u8 regs_पढ़ो[t_num_regs] = अणु
	[t_input1] = MAX1619_REG_R_LOCAL_TEMP,
	[t_input2] = MAX1619_REG_R_REMOTE_TEMP,
	[t_low2] = MAX1619_REG_R_REMOTE_LOW,
	[t_high2] = MAX1619_REG_R_REMOTE_HIGH,
	[t_crit2] = MAX1619_REG_R_REMOTE_CRIT,
	[t_hyst2] = MAX1619_REG_R_TCRIT_HYST,
पूर्ण;

अटल स्थिर u8 regs_ग_लिखो[t_num_regs] = अणु
	[t_low2] = MAX1619_REG_W_REMOTE_LOW,
	[t_high2] = MAX1619_REG_W_REMOTE_HIGH,
	[t_crit2] = MAX1619_REG_W_REMOTE_CRIT,
	[t_hyst2] = MAX1619_REG_W_TCRIT_HYST,
पूर्ण;

अटल काष्ठा max1619_data *max1619_update_device(काष्ठा device *dev)
अणु
	काष्ठा max1619_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक config, i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ * 2) || !data->valid) अणु
		dev_dbg(&client->dev, "Updating max1619 data.\n");
		क्रम (i = 0; i < t_num_regs; i++)
			data->temp[i] = i2c_smbus_पढ़ो_byte_data(client,
					regs_पढ़ो[i]);
		data->alarms = i2c_smbus_पढ़ो_byte_data(client,
					MAX1619_REG_R_STATUS);
		/* If OVERT polarity is low, reverse alarm bit */
		config = i2c_smbus_पढ़ो_byte_data(client, MAX1619_REG_R_CONFIG);
		अगर (!(config & 0x20))
			data->alarms ^= 0x02;

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा max1619_data *data = max1619_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", temp_from_reg(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा max1619_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[attr->index] = temp_to_reg(val);
	i2c_smbus_ग_लिखो_byte_data(client, regs_ग_लिखो[attr->index],
				  data->temp[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा max1619_data *data = max1619_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा max1619_data *data = max1619_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, t_input1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, t_input2);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp, t_low2);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp, t_high2);
अटल SENSOR_DEVICE_ATTR_RW(temp2_crit, temp, t_crit2);
अटल SENSOR_DEVICE_ATTR_RW(temp2_crit_hyst, temp, t_hyst2);

अटल DEVICE_ATTR_RO(alarms);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, 4);

अटल काष्ठा attribute *max1619_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_hyst.dev_attr.attr,

	&dev_attr_alarms.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(max1619);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक max1619_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u8 reg_config, reg_convrate, reg_status, man_id, chip_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* detection */
	reg_config = i2c_smbus_पढ़ो_byte_data(client, MAX1619_REG_R_CONFIG);
	reg_convrate = i2c_smbus_पढ़ो_byte_data(client, MAX1619_REG_R_CONVRATE);
	reg_status = i2c_smbus_पढ़ो_byte_data(client, MAX1619_REG_R_STATUS);
	अगर ((reg_config & 0x03) != 0x00
	 || reg_convrate > 0x07 || (reg_status & 0x61) != 0x00) अणु
		dev_dbg(&adapter->dev, "MAX1619 detection failed at 0x%02x\n",
			client->addr);
		वापस -ENODEV;
	पूर्ण

	/* identअगरication */
	man_id = i2c_smbus_पढ़ो_byte_data(client, MAX1619_REG_R_MAN_ID);
	chip_id = i2c_smbus_पढ़ो_byte_data(client, MAX1619_REG_R_CHIP_ID);
	अगर (man_id != 0x4D || chip_id != 0x04) अणु
		dev_info(&adapter->dev,
			 "Unsupported chip (man_id=0x%02X, chip_id=0x%02X).\n",
			 man_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "max1619", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम max1619_init_client(काष्ठा i2c_client *client)
अणु
	u8 config;

	/*
	 * Start the conversions.
	 */
	i2c_smbus_ग_लिखो_byte_data(client, MAX1619_REG_W_CONVRATE,
				  5); /* 2 Hz */
	config = i2c_smbus_पढ़ो_byte_data(client, MAX1619_REG_R_CONFIG);
	अगर (config & 0x40)
		i2c_smbus_ग_लिखो_byte_data(client, MAX1619_REG_W_CONFIG,
					  config & 0xBF); /* run */
पूर्ण

अटल पूर्णांक max1619_probe(काष्ठा i2c_client *new_client)
अणु
	काष्ठा max1619_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(&new_client->dev, माप(काष्ठा max1619_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = new_client;
	mutex_init(&data->update_lock);

	/* Initialize the MAX1619 chip */
	max1619_init_client(new_client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&new_client->dev,
							   new_client->name,
							   data,
							   max1619_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max1619_id[] = अणु
	अणु "max1619", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max1619_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max1619_of_match[] = अणु
	अणु .compatible = "maxim,max1619", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, max1619_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max1619_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "max1619",
		.of_match_table = of_match_ptr(max1619_of_match),
	पूर्ण,
	.probe_new	= max1619_probe,
	.id_table	= max1619_id,
	.detect		= max1619_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(max1619_driver);

MODULE_AUTHOR("Oleksij Rempel <bug-track@fisher-privat.net>, Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("MAX1619 sensor driver");
MODULE_LICENSE("GPL");
