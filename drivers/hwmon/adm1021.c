<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * adm1021.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 * Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl> and
 *			     Philip Edelbrock <phil@netroedge.com>
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


/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु
	adm1021, adm1023, max1617, max1617a, thmc10, lm84, gl523sm, mc1066 पूर्ण;

/* adm1021 स्थिरants specअगरied below */

/* The adm1021 रेजिस्टरs */
/* Read-only */
/* For nr in 0-1 */
#घोषणा ADM1021_REG_TEMP(nr)		(nr)
#घोषणा ADM1021_REG_STATUS		0x02
/* 0x41 = AD, 0x49 = TI, 0x4D = Maxim, 0x23 = Genesys , 0x54 = Onsemi */
#घोषणा ADM1021_REG_MAN_ID		0xFE
/* ADM1021 = 0x0X, ADM1023 = 0x3X */
#घोषणा ADM1021_REG_DEV_ID		0xFF
/* These use dअगरferent addresses क्रम पढ़ोing/writing */
#घोषणा ADM1021_REG_CONFIG_R		0x03
#घोषणा ADM1021_REG_CONFIG_W		0x09
#घोषणा ADM1021_REG_CONV_RATE_R		0x04
#घोषणा ADM1021_REG_CONV_RATE_W		0x0A
/* These are क्रम the ADM1023's additional precision on the remote temp sensor */
#घोषणा ADM1023_REG_REM_TEMP_PREC	0x10
#घोषणा ADM1023_REG_REM_OFFSET		0x11
#घोषणा ADM1023_REG_REM_OFFSET_PREC	0x12
#घोषणा ADM1023_REG_REM_TOS_PREC	0x13
#घोषणा ADM1023_REG_REM_THYST_PREC	0x14
/* limits */
/* For nr in 0-1 */
#घोषणा ADM1021_REG_TOS_R(nr)		(0x05 + 2 * (nr))
#घोषणा ADM1021_REG_TOS_W(nr)		(0x0B + 2 * (nr))
#घोषणा ADM1021_REG_THYST_R(nr)		(0x06 + 2 * (nr))
#घोषणा ADM1021_REG_THYST_W(nr)		(0x0C + 2 * (nr))
/* ग_लिखो-only */
#घोषणा ADM1021_REG_ONESHOT		0x0F

/* Initial values */

/*
 * Note: Even though I left the low and high limits named os and hyst,
 * they करोn't quite work like a thermostat the way the LM75 करोes.  I.e.,
 * a lower temp than THYST actually triggers an alarm instead of
 * clearing it.  Weird, ey?   --Phil
 */

/* Each client has this additional data */
काष्ठा adm1021_data अणु
	काष्ठा i2c_client *client;
	क्रमागत chips type;

	स्थिर काष्ठा attribute_group *groups[3];

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अक्षर low_घातer;		/* !=0 अगर device in low घातer mode */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	पूर्णांक temp_max[2];		/* Register values */
	पूर्णांक temp_min[2];
	पूर्णांक temp[2];
	u8 alarms;
	/* Special values क्रम ADM1023 only */
	u8 remote_temp_offset;
	u8 remote_temp_offset_prec;
पूर्ण;

/* (amalysh) पढ़ो only mode, otherwise any limit's writing confuse BIOS */
अटल bool पढ़ो_only;

अटल काष्ठा adm1021_data *adm1021_update_device(काष्ठा device *dev)
अणु
	काष्ठा adm1021_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		पूर्णांक i;

		dev_dbg(dev, "Starting adm1021 update\n");

		क्रम (i = 0; i < 2; i++) अणु
			data->temp[i] = 1000 *
				(s8) i2c_smbus_पढ़ो_byte_data(
					client, ADM1021_REG_TEMP(i));
			data->temp_max[i] = 1000 *
				(s8) i2c_smbus_पढ़ो_byte_data(
					client, ADM1021_REG_TOS_R(i));
			अगर (data->type != lm84) अणु
				data->temp_min[i] = 1000 *
				  (s8) i2c_smbus_पढ़ो_byte_data(client,
							ADM1021_REG_THYST_R(i));
			पूर्ण
		पूर्ण
		data->alarms = i2c_smbus_पढ़ो_byte_data(client,
						ADM1021_REG_STATUS) & 0x7c;
		अगर (data->type == adm1023) अणु
			/*
			 * The ADM1023 provides 3 extra bits of precision क्रम
			 * the remote sensor in extra रेजिस्टरs.
			 */
			data->temp[1] += 125 * (i2c_smbus_पढ़ो_byte_data(
				client, ADM1023_REG_REM_TEMP_PREC) >> 5);
			data->temp_max[1] += 125 * (i2c_smbus_पढ़ो_byte_data(
				client, ADM1023_REG_REM_TOS_PREC) >> 5);
			data->temp_min[1] += 125 * (i2c_smbus_पढ़ो_byte_data(
				client, ADM1023_REG_REM_THYST_PREC) >> 5);
			data->remote_temp_offset =
				i2c_smbus_पढ़ो_byte_data(client,
						ADM1023_REG_REM_OFFSET);
			data->remote_temp_offset_prec =
				i2c_smbus_पढ़ो_byte_data(client,
						ADM1023_REG_REM_OFFSET_PREC);
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
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा adm1021_data *data = adm1021_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", data->temp[index]);
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा adm1021_data *data = adm1021_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", data->temp_max[index]);
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा adm1021_data *data = adm1021_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", data->temp_min[index]);
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1021_data *data = adm1021_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> index) & 1);
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा adm1021_data *data = adm1021_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा adm1021_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;
	पूर्णांक reg_val, err;

	err = kम_से_दीर्घ(buf, 10, &temp);
	अगर (err)
		वापस err;
	temp /= 1000;

	mutex_lock(&data->update_lock);
	reg_val = clamp_val(temp, -128, 127);
	data->temp_max[index] = reg_val * 1000;
	अगर (!पढ़ो_only)
		i2c_smbus_ग_लिखो_byte_data(client, ADM1021_REG_TOS_W(index),
					  reg_val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा adm1021_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;
	पूर्णांक reg_val, err;

	err = kम_से_दीर्घ(buf, 10, &temp);
	अगर (err)
		वापस err;
	temp /= 1000;

	mutex_lock(&data->update_lock);
	reg_val = clamp_val(temp, -128, 127);
	data->temp_min[index] = reg_val * 1000;
	अगर (!पढ़ो_only)
		i2c_smbus_ग_लिखो_byte_data(client, ADM1021_REG_THYST_W(index),
					  reg_val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार low_घातer_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा adm1021_data *data = adm1021_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->low_घातer);
पूर्ण

अटल sमाप_प्रकार low_घातer_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1021_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अक्षर low_घातer;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	low_घातer = val != 0;

	mutex_lock(&data->update_lock);
	अगर (low_घातer != data->low_घातer) अणु
		पूर्णांक config = i2c_smbus_पढ़ो_byte_data(
			client, ADM1021_REG_CONFIG_R);
		data->low_घातer = low_घातer;
		i2c_smbus_ग_लिखो_byte_data(client, ADM1021_REG_CONFIG_W,
			(config & 0xBF) | (low_घातer << 6));
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण


अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 2);

अटल DEVICE_ATTR_RO(alarms);
अटल DEVICE_ATTR_RW(low_घातer);

अटल काष्ठा attribute *adm1021_attributes[] = अणु
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&dev_attr_alarms.attr,
	&dev_attr_low_घातer.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1021_group = अणु
	.attrs = adm1021_attributes,
पूर्ण;

अटल काष्ठा attribute *adm1021_min_attributes[] = अणु
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1021_min_group = अणु
	.attrs = adm1021_min_attributes,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adm1021_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	स्थिर अक्षर *type_name;
	पूर्णांक conv_rate, status, config, man_id, dev_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		pr_debug("detect failed, smbus byte data not supported!\n");
		वापस -ENODEV;
	पूर्ण

	status = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_STATUS);
	conv_rate = i2c_smbus_पढ़ो_byte_data(client,
					     ADM1021_REG_CONV_RATE_R);
	config = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_CONFIG_R);

	/* Check unused bits */
	अगर ((status & 0x03) || (config & 0x3F) || (conv_rate & 0xF8)) अणु
		pr_debug("detect failed, chip not detected!\n");
		वापस -ENODEV;
	पूर्ण

	/* Determine the chip type. */
	man_id = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_MAN_ID);
	dev_id = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_DEV_ID);

	अगर (man_id < 0 || dev_id < 0)
		वापस -ENODEV;

	अगर (man_id == 0x4d && dev_id == 0x01)
		type_name = "max1617a";
	अन्यथा अगर (man_id == 0x41) अणु
		अगर ((dev_id & 0xF0) == 0x30)
			type_name = "adm1023";
		अन्यथा अगर ((dev_id & 0xF0) == 0x00)
			type_name = "adm1021";
		अन्यथा
			वापस -ENODEV;
	पूर्ण अन्यथा अगर (man_id == 0x49)
		type_name = "thmc10";
	अन्यथा अगर (man_id == 0x23)
		type_name = "gl523sm";
	अन्यथा अगर (man_id == 0x54)
		type_name = "mc1066";
	अन्यथा अणु
		पूर्णांक lte, rte, lhi, rhi, llo, rlo;

		/* extra checks क्रम LM84 and MAX1617 to aव्योम misdetections */

		llo = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_THYST_R(0));
		rlo = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_THYST_R(1));

		/* fail अगर any of the additional रेजिस्टर पढ़ोs failed */
		अगर (llo < 0 || rlo < 0)
			वापस -ENODEV;

		lte = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_TEMP(0));
		rte = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_TEMP(1));
		lhi = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_TOS_R(0));
		rhi = i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_TOS_R(1));

		/*
		 * Fail क्रम negative temperatures and negative high limits.
		 * This check also catches पढ़ो errors on the tested रेजिस्टरs.
		 */
		अगर ((s8)lte < 0 || (s8)rte < 0 || (s8)lhi < 0 || (s8)rhi < 0)
			वापस -ENODEV;

		/* fail अगर all रेजिस्टरs hold the same value */
		अगर (lte == rte && lte == lhi && lte == rhi && lte == llo
		    && lte == rlo)
			वापस -ENODEV;

		/*
		 * LM84 Mfr ID is in a dअगरferent place,
		 * and it has more unused bits.
		 */
		अगर (conv_rate == 0x00
		    && (config & 0x7F) == 0x00
		    && (status & 0xAB) == 0x00) अणु
			type_name = "lm84";
		पूर्ण अन्यथा अणु
			/* fail अगर low limits are larger than high limits */
			अगर ((s8)llo > lhi || (s8)rlo > rhi)
				वापस -ENODEV;
			type_name = "max1617";
		पूर्ण
	पूर्ण

	pr_debug("Detected chip %s at adapter %d, address 0x%02x.\n",
		 type_name, i2c_adapter_id(adapter), client->addr);
	strlcpy(info->type, type_name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम adm1021_init_client(काष्ठा i2c_client *client)
अणु
	/* Enable ADC and disable suspend mode */
	i2c_smbus_ग_लिखो_byte_data(client, ADM1021_REG_CONFIG_W,
		i2c_smbus_पढ़ो_byte_data(client, ADM1021_REG_CONFIG_R) & 0xBF);
	/* Set Conversion rate to 1/sec (this can be tinkered with) */
	i2c_smbus_ग_लिखो_byte_data(client, ADM1021_REG_CONV_RATE_W, 0x04);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1021_id[];

अटल पूर्णांक adm1021_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा adm1021_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा adm1021_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->type = i2c_match_id(adm1021_id, client)->driver_data;
	mutex_init(&data->update_lock);

	/* Initialize the ADM1021 chip */
	अगर (data->type != lm84 && !पढ़ो_only)
		adm1021_init_client(client);

	data->groups[0] = &adm1021_group;
	अगर (data->type != lm84)
		data->groups[1] = &adm1021_min_group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1021_id[] = अणु
	अणु "adm1021", adm1021 पूर्ण,
	अणु "adm1023", adm1023 पूर्ण,
	अणु "max1617", max1617 पूर्ण,
	अणु "max1617a", max1617a पूर्ण,
	अणु "thmc10", thmc10 पूर्ण,
	अणु "lm84", lm84 पूर्ण,
	अणु "gl523sm", gl523sm पूर्ण,
	अणु "mc1066", mc1066 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1021_id);

अटल काष्ठा i2c_driver adm1021_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adm1021",
	पूर्ण,
	.probe_new	= adm1021_probe,
	.id_table	= adm1021_id,
	.detect		= adm1021_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adm1021_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl> and "
		"Philip Edelbrock <phil@netroedge.com>");
MODULE_DESCRIPTION("adm1021 driver");
MODULE_LICENSE("GPL");

module_param(पढ़ो_only, bool, 0);
MODULE_PARM_DESC(पढ़ो_only, "Don't set any values, read only mode");
