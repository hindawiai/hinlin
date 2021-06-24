<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * adm1029.c - Part of lm_sensors, Linux kernel modules क्रम hardware monitoring
 *
 * Copyright (C) 2006 Corentin LABBE <clabbe.montjoie@gmail.com>
 *
 * Based on LM83 Driver by Jean Delvare <jdelvare@suse.de>
 *
 * Give only processor, motherboard temperatures and fan tachs
 * Very rare chip please let me know अगर you use it
 *
 * http://www.analog.com/UploadedFiles/Data_Sheets/ADM1029.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>

/*
 * Addresses to scan
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CLIENT_END
पूर्ण;

/*
 * The ADM1029 रेजिस्टरs
 * Manufacturer ID is 0x41 क्रम Analog Devices
 */

#घोषणा ADM1029_REG_MAN_ID			0x0D
#घोषणा ADM1029_REG_CHIP_ID			0x0E
#घोषणा ADM1029_REG_CONFIG			0x01
#घोषणा ADM1029_REG_NB_FAN_SUPPORT		0x02

#घोषणा ADM1029_REG_TEMP_DEVICES_INSTALLED	0x06

#घोषणा ADM1029_REG_LOCAL_TEMP			0xA0
#घोषणा ADM1029_REG_REMOTE1_TEMP		0xA1
#घोषणा ADM1029_REG_REMOTE2_TEMP		0xA2

#घोषणा ADM1029_REG_LOCAL_TEMP_HIGH		0x90
#घोषणा ADM1029_REG_REMOTE1_TEMP_HIGH		0x91
#घोषणा ADM1029_REG_REMOTE2_TEMP_HIGH		0x92

#घोषणा ADM1029_REG_LOCAL_TEMP_LOW		0x98
#घोषणा ADM1029_REG_REMOTE1_TEMP_LOW		0x99
#घोषणा ADM1029_REG_REMOTE2_TEMP_LOW		0x9A

#घोषणा ADM1029_REG_FAN1			0x70
#घोषणा ADM1029_REG_FAN2			0x71

#घोषणा ADM1029_REG_FAN1_MIN			0x78
#घोषणा ADM1029_REG_FAN2_MIN			0x79

#घोषणा ADM1029_REG_FAN1_CONFIG			0x68
#घोषणा ADM1029_REG_FAN2_CONFIG			0x69

#घोषणा TEMP_FROM_REG(val)	((val) * 1000)

#घोषणा DIV_FROM_REG(val)	(1 << (((val) >> 6) - 1))

/* Registers to be checked by adm1029_update_device() */
अटल स्थिर u8 ADM1029_REG_TEMP[] = अणु
	ADM1029_REG_LOCAL_TEMP,
	ADM1029_REG_REMOTE1_TEMP,
	ADM1029_REG_REMOTE2_TEMP,
	ADM1029_REG_LOCAL_TEMP_HIGH,
	ADM1029_REG_REMOTE1_TEMP_HIGH,
	ADM1029_REG_REMOTE2_TEMP_HIGH,
	ADM1029_REG_LOCAL_TEMP_LOW,
	ADM1029_REG_REMOTE1_TEMP_LOW,
	ADM1029_REG_REMOTE2_TEMP_LOW,
पूर्ण;

अटल स्थिर u8 ADM1029_REG_FAN[] = अणु
	ADM1029_REG_FAN1,
	ADM1029_REG_FAN2,
	ADM1029_REG_FAN1_MIN,
	ADM1029_REG_FAN2_MIN,
पूर्ण;

अटल स्थिर u8 ADM1029_REG_FAN_DIV[] = अणु
	ADM1029_REG_FAN1_CONFIG,
	ADM1029_REG_FAN2_CONFIG,
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा adm1029_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock; /* protect रेजिस्टर access */
	अक्षर valid;		/* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */

	/* रेजिस्टरs values, चिन्हित क्रम temperature, अचिन्हित क्रम other stuff */
	s8 temp[ARRAY_SIZE(ADM1029_REG_TEMP)];
	u8 fan[ARRAY_SIZE(ADM1029_REG_FAN)];
	u8 fan_भाग[ARRAY_SIZE(ADM1029_REG_FAN_DIV)];
पूर्ण;

/*
 * function that update the status of the chips (temperature क्रम example)
 */
अटल काष्ठा adm1029_data *adm1029_update_device(काष्ठा device *dev)
अणु
	काष्ठा adm1029_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);
	/*
	 * Use the "cache" Luke, करोn't recheck values
	 * अगर there are alपढ़ोy checked not a दीर्घ समय later
	 */
	अगर (समय_after(jअगरfies, data->last_updated + HZ * 2) || !data->valid) अणु
		पूर्णांक nr;

		dev_dbg(&client->dev, "Updating adm1029 data\n");

		क्रम (nr = 0; nr < ARRAY_SIZE(ADM1029_REG_TEMP); nr++) अणु
			data->temp[nr] =
			    i2c_smbus_पढ़ो_byte_data(client,
						     ADM1029_REG_TEMP[nr]);
		पूर्ण
		क्रम (nr = 0; nr < ARRAY_SIZE(ADM1029_REG_FAN); nr++) अणु
			data->fan[nr] =
			    i2c_smbus_पढ़ो_byte_data(client,
						     ADM1029_REG_FAN[nr]);
		पूर्ण
		क्रम (nr = 0; nr < ARRAY_SIZE(ADM1029_REG_FAN_DIV); nr++) अणु
			data->fan_भाग[nr] =
			    i2c_smbus_पढ़ो_byte_data(client,
						     ADM1029_REG_FAN_DIV[nr]);
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार
temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adm1029_data *data = adm1029_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार
fan_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adm1029_data *data = adm1029_update_device(dev);
	u16 val;

	अगर (data->fan[attr->index] == 0 ||
	    (data->fan_भाग[attr->index] & 0xC0) == 0 ||
	    data->fan[attr->index] == 255) अणु
		वापस प्र_लिखो(buf, "0\n");
	पूर्ण

	val = 1880 * 120 / DIV_FROM_REG(data->fan_भाग[attr->index])
	    / data->fan[attr->index];
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार
fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adm1029_data *data = adm1029_update_device(dev);

	अगर ((data->fan_भाग[attr->index] & 0xC0) == 0)
		वापस प्र_लिखो(buf, "0\n");
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[attr->index]));
पूर्ण

अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1029_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	u8 reg;
	दीर्घ val;
	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &val);

	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);

	/*Read actual config */
	reg = i2c_smbus_पढ़ो_byte_data(client,
				       ADM1029_REG_FAN_DIV[attr->index]);

	चयन (val) अणु
	हाल 1:
		val = 1;
		अवरोध;
	हाल 2:
		val = 2;
		अवरोध;
	हाल 4:
		val = 3;
		अवरोध;
	शेष:
		mutex_unlock(&data->update_lock);
		dev_err(&client->dev,
			"fan_div value %ld not supported. Choose one of 1, 2 or 4!\n",
			val);
		वापस -EINVAL;
	पूर्ण
	/* Update the value */
	reg = (reg & 0x3F) | (val << 6);

	/* Update the cache */
	data->fan_भाग[attr->index] = reg;

	/* Write value */
	i2c_smbus_ग_लिखो_byte_data(client,
				  ADM1029_REG_FAN_DIV[attr->index], reg);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* Access rights on sysfs. */
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);

अटल SENSOR_DEVICE_ATTR_RO(temp1_max, temp, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max, temp, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max, temp, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_min, temp, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min, temp, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp3_min, temp, 8);

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);

अटल SENSOR_DEVICE_ATTR_RO(fan1_min, fan, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan2_min, fan, 3);

अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);

अटल काष्ठा attribute *adm1029_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(adm1029);

/*
 * Real code
 */

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adm1029_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u8 man_id, chip_id, temp_devices_installed, nb_fan_support;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/*
	 * ADM1029 करोesn't have CHIP ID, check just MAN ID
	 * For better detection we check also ADM1029_TEMP_DEVICES_INSTALLED,
	 * ADM1029_REG_NB_FAN_SUPPORT and compare it with possible values
	 * करोcumented
	 */

	man_id = i2c_smbus_पढ़ो_byte_data(client, ADM1029_REG_MAN_ID);
	chip_id = i2c_smbus_पढ़ो_byte_data(client, ADM1029_REG_CHIP_ID);
	temp_devices_installed = i2c_smbus_पढ़ो_byte_data(client,
					ADM1029_REG_TEMP_DEVICES_INSTALLED);
	nb_fan_support = i2c_smbus_पढ़ो_byte_data(client,
						  ADM1029_REG_NB_FAN_SUPPORT);
	/* 0x41 is Analog Devices */
	अगर (man_id != 0x41 || (temp_devices_installed & 0xf9) != 0x01 ||
	    nb_fan_support != 0x03)
		वापस -ENODEV;

	अगर ((chip_id & 0xF0) != 0x00) अणु
		/*
		 * There are no "official" CHIP ID, so actually
		 * we use Major/Minor revision क्रम that
		 */
		pr_info("Unknown major revision %x, please let us know\n",
			chip_id);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "adm1029", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक adm1029_init_client(काष्ठा i2c_client *client)
अणु
	u8 config;

	config = i2c_smbus_पढ़ो_byte_data(client, ADM1029_REG_CONFIG);
	अगर ((config & 0x10) == 0) अणु
		i2c_smbus_ग_लिखो_byte_data(client, ADM1029_REG_CONFIG,
					  config | 0x10);
	पूर्ण
	/* recheck config */
	config = i2c_smbus_पढ़ो_byte_data(client, ADM1029_REG_CONFIG);
	अगर ((config & 0x10) == 0) अणु
		dev_err(&client->dev, "Initialization failed!\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक adm1029_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा adm1029_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा adm1029_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/*
	 * Initialize the ADM1029 chip
	 * Check config रेजिस्टर
	 */
	अगर (adm1029_init_client(client) == 0)
		वापस -ENODEV;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   adm1029_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1029_id[] = अणु
	अणु "adm1029", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1029_id);

अटल काष्ठा i2c_driver adm1029_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name = "adm1029",
	पूर्ण,
	.probe_new	= adm1029_probe,
	.id_table	= adm1029_id,
	.detect		= adm1029_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adm1029_driver);

MODULE_AUTHOR("Corentin LABBE <clabbe.montjoie@gmail.com>");
MODULE_DESCRIPTION("adm1029 driver");
MODULE_LICENSE("GPL v2");
