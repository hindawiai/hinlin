<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * w83l785ts.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *               monitoring
 * Copyright (C) 2003-2009  Jean Delvare <jdelvare@suse.de>
 *
 * Inspired from the lm83 driver. The W83L785TS-S is a sensor chip made
 * by Winbond. It reports a single बाह्यal temperature with a 1 deg
 * resolution and a 3 deg accuracy. Datasheet can be obtained from
 * Winbond's website at:
 *   http://www.winbond-usa.com/products/winbond_products/pdfs/PCIC/W83L785TS-S.pdf
 *
 * Ported to Linux 2.6 by Wolfgang Ziegler <nuppla@gmx.at> and Jean Delvare
 * <jdelvare@suse.de>.
 *
 * Thanks to James Bolt <james@evilpenguin.com> क्रम benchmarking the पढ़ो
 * error handling mechanism.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>

/* How many retries on रेजिस्टर पढ़ो error */
#घोषणा MAX_RETRIES	5

/*
 * Address to scan
 * Address is fully defined पूर्णांकernally and cannot be changed.
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2e, I2C_CLIENT_END पूर्ण;

/*
 * The W83L785TS-S रेजिस्टरs
 * Manufacturer ID is 0x5CA3 क्रम Winbond.
 */

#घोषणा W83L785TS_REG_MAN_ID1		0x4D
#घोषणा W83L785TS_REG_MAN_ID2		0x4C
#घोषणा W83L785TS_REG_CHIP_ID		0x4E
#घोषणा W83L785TS_REG_CONFIG		0x40
#घोषणा W83L785TS_REG_TYPE		0x52
#घोषणा W83L785TS_REG_TEMP		0x27
#घोषणा W83L785TS_REG_TEMP_OVER		0x53 /* not sure about this one */

/*
 * Conversions
 * The W83L785TS-S uses चिन्हित 8-bit values.
 */

#घोषणा TEMP_FROM_REG(val)	((val) * 1000)

/*
 * Functions declaration
 */

अटल पूर्णांक w83l785ts_probe(काष्ठा i2c_client *client);
अटल पूर्णांक w83l785ts_detect(काष्ठा i2c_client *client,
			    काष्ठा i2c_board_info *info);
अटल पूर्णांक w83l785ts_हटाओ(काष्ठा i2c_client *client);
अटल u8 w83l785ts_पढ़ो_value(काष्ठा i2c_client *client, u8 reg, u8 defval);
अटल काष्ठा w83l785ts_data *w83l785ts_update_device(काष्ठा device *dev);

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id w83l785ts_id[] = अणु
	अणु "w83l785ts", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, w83l785ts_id);

अटल काष्ठा i2c_driver w83l785ts_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "w83l785ts",
	पूर्ण,
	.probe_new	= w83l785ts_probe,
	.हटाओ		= w83l785ts_हटाओ,
	.id_table	= w83l785ts_id,
	.detect		= w83l785ts_detect,
	.address_list	= normal_i2c,
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा w83l785ts_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टरs values */
	s8 temp[2]; /* 0: input, 1: critical limit */
पूर्ण;

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *devattr,
	अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा w83l785ts_data *data = w83l785ts_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, show_temp, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_max, S_IRUGO, show_temp, शून्य, 1);

/*
 * Real code
 */

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक w83l785ts_detect(काष्ठा i2c_client *client,
			    काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u16 man_id;
	u8 chip_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* detection */
	अगर ((w83l785ts_पढ़ो_value(client, W83L785TS_REG_CONFIG, 0) & 0x80)
	 || (w83l785ts_पढ़ो_value(client, W83L785TS_REG_TYPE, 0) & 0xFC)) अणु
		dev_dbg(&adapter->dev,
			"W83L785TS-S detection failed at 0x%02x\n",
			client->addr);
		वापस -ENODEV;
	पूर्ण

	/* Identअगरication */
	man_id = (w83l785ts_पढ़ो_value(client, W83L785TS_REG_MAN_ID1, 0) << 8)
	       + w83l785ts_पढ़ो_value(client, W83L785TS_REG_MAN_ID2, 0);
	chip_id = w83l785ts_पढ़ो_value(client, W83L785TS_REG_CHIP_ID, 0);

	अगर (man_id != 0x5CA3		/* Winbond */
	 || chip_id != 0x70) अणु		/* W83L785TS-S */
		dev_dbg(&adapter->dev,
			"Unsupported chip (man_id=0x%04X, chip_id=0x%02X)\n",
			man_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "w83l785ts", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक w83l785ts_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा w83l785ts_data *data;
	काष्ठा device *dev = &client->dev;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा w83l785ts_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/*
	 * Initialize the W83L785TS chip
	 * Nothing yet, assume it is alपढ़ोy started.
	 */

	err = device_create_file(dev, &sensor_dev_attr_temp1_input.dev_attr);
	अगर (err)
		वापस err;

	err = device_create_file(dev, &sensor_dev_attr_temp1_max.dev_attr);
	अगर (err)
		जाओ निकास_हटाओ;

	/* Register sysfs hooks */
	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	वापस 0;

निकास_हटाओ:
	device_हटाओ_file(dev, &sensor_dev_attr_temp1_input.dev_attr);
	device_हटाओ_file(dev, &sensor_dev_attr_temp1_max.dev_attr);
	वापस err;
पूर्ण

अटल पूर्णांक w83l785ts_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा w83l785ts_data *data = i2c_get_clientdata(client);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	device_हटाओ_file(&client->dev,
			   &sensor_dev_attr_temp1_input.dev_attr);
	device_हटाओ_file(&client->dev,
			   &sensor_dev_attr_temp1_max.dev_attr);

	वापस 0;
पूर्ण

अटल u8 w83l785ts_पढ़ो_value(काष्ठा i2c_client *client, u8 reg, u8 defval)
अणु
	पूर्णांक value, i;
	काष्ठा device *dev;
	स्थिर अक्षर *prefix;

	/*
	 * We might be called during detection, at which poपूर्णांक the client
	 * isn't yet fully initialized, so we can't use dev_dbg on it
	 */
	अगर (i2c_get_clientdata(client)) अणु
		dev = &client->dev;
		prefix = "";
	पूर्ण अन्यथा अणु
		dev = &client->adapter->dev;
		prefix = "w83l785ts: ";
	पूर्ण

	/*
	 * Frequent पढ़ो errors have been reported on Asus boards, so we
	 * retry on पढ़ो errors. If it still fails (unlikely), वापस the
	 * शेष value requested by the caller.
	 */
	क्रम (i = 1; i <= MAX_RETRIES; i++) अणु
		value = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (value >= 0) अणु
			dev_dbg(dev, "%sRead 0x%02x from register 0x%02x.\n",
				prefix, value, reg);
			वापस value;
		पूर्ण
		dev_dbg(dev, "%sRead failed, will retry in %d.\n", prefix, i);
		msleep(i);
	पूर्ण

	dev_err(dev, "%sCouldn't read value from register 0x%02x.\n", prefix,
		reg);
	वापस defval;
पूर्ण

अटल काष्ठा w83l785ts_data *w83l785ts_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83l785ts_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	अगर (!data->valid || समय_after(jअगरfies, data->last_updated + HZ * 2)) अणु
		dev_dbg(&client->dev, "Updating w83l785ts data.\n");
		data->temp[0] = w83l785ts_पढ़ो_value(client,
				W83L785TS_REG_TEMP, data->temp[0]);
		data->temp[1] = w83l785ts_पढ़ो_value(client,
				W83L785TS_REG_TEMP_OVER, data->temp[1]);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

module_i2c_driver(w83l785ts_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("W83L785TS-S driver");
MODULE_LICENSE("GPL");
