<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm77.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	    monitoring
 *
 * Copyright (c) 2004  Andras BALI <drewie@मुक्तmail.hu>
 *
 * Heavily based on lm75.c by Froकरो Looijaard <froकरोl@dds.nl>.  The LM77
 * is a temperature sensor and thermal winकरोw comparator with 0.5 deg
 * resolution made by National Semiconductor.  Complete datasheet can be
 * obtained at their site:
 *	http://www.national.com/pf/LM/LM77.hपंचांगl
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
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x48, 0x49, 0x4a, 0x4b,
						I2C_CLIENT_END पूर्ण;

/* The LM77 रेजिस्टरs */
#घोषणा LM77_REG_TEMP		0x00
#घोषणा LM77_REG_CONF		0x01
#घोषणा LM77_REG_TEMP_HYST	0x02
#घोषणा LM77_REG_TEMP_CRIT	0x03
#घोषणा LM77_REG_TEMP_MIN	0x04
#घोषणा LM77_REG_TEMP_MAX	0x05

क्रमागत temp_index अणु
	t_input = 0,
	t_crit,
	t_min,
	t_max,
	t_hyst,
	t_num_temp
पूर्ण;

अटल स्थिर u8 temp_regs[t_num_temp] = अणु
	[t_input] = LM77_REG_TEMP,
	[t_min] = LM77_REG_TEMP_MIN,
	[t_max] = LM77_REG_TEMP_MAX,
	[t_crit] = LM77_REG_TEMP_CRIT,
	[t_hyst] = LM77_REG_TEMP_HYST,
पूर्ण;

/* Each client has this additional data */
काष्ठा lm77_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		update_lock;
	अक्षर			valid;
	अचिन्हित दीर्घ		last_updated;	/* In jअगरfies */
	पूर्णांक			temp[t_num_temp]; /* index using temp_index */
	u8			alarms;
पूर्ण;

/* straight from the datasheet */
#घोषणा LM77_TEMP_MIN (-55000)
#घोषणा LM77_TEMP_MAX 125000

/*
 * In the temperature रेजिस्टरs, the low 3 bits are not part of the
 * temperature values; they are the status bits.
 */
अटल अंतरभूत s16 LM77_TEMP_TO_REG(पूर्णांक temp)
अणु
	वापस (temp / 500) * 8;
पूर्ण

अटल अंतरभूत पूर्णांक LM77_TEMP_FROM_REG(s16 reg)
अणु
	वापस (reg / 8) * 500;
पूर्ण

/*
 * All रेजिस्टरs are word-sized, except क्रम the configuration रेजिस्टर.
 * The LM77 uses the high-byte first convention.
 */
अटल u16 lm77_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	अगर (reg == LM77_REG_CONF)
		वापस i2c_smbus_पढ़ो_byte_data(client, reg);
	अन्यथा
		वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
पूर्ण

अटल पूर्णांक lm77_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, u16 value)
अणु
	अगर (reg == LM77_REG_CONF)
		वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
	अन्यथा
		वापस i2c_smbus_ग_लिखो_word_swapped(client, reg, value);
पूर्ण

अटल काष्ठा lm77_data *lm77_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm77_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		dev_dbg(&client->dev, "Starting lm77 update\n");
		क्रम (i = 0; i < t_num_temp; i++) अणु
			data->temp[i] =
			  LM77_TEMP_FROM_REG(lm77_पढ़ो_value(client,
							     temp_regs[i]));
		पूर्ण
		data->alarms =
			lm77_पढ़ो_value(client, LM77_REG_TEMP) & 0x0007;
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* sysfs stuff */

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm77_data *data = lm77_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", data->temp[attr->index]);
पूर्ण

अटल sमाप_प्रकार temp_hyst_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm77_data *data = lm77_update_device(dev);
	पूर्णांक nr = attr->index;
	पूर्णांक temp;

	temp = nr == t_min ? data->temp[nr] + data->temp[t_hyst] :
			     data->temp[nr] - data->temp[t_hyst];

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm77_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val = clamp_val(val, LM77_TEMP_MIN, LM77_TEMP_MAX);
	mutex_lock(&data->update_lock);
	data->temp[nr] = val;
	lm77_ग_लिखो_value(client, temp_regs[nr], LM77_TEMP_TO_REG(val));
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * hysteresis is stored as a relative value on the chip, so it has to be
 * converted first.
 */
अटल sमाप_प्रकार temp_hyst_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm77_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	val = clamp_val(data->temp[t_crit] - val, LM77_TEMP_MIN, LM77_TEMP_MAX);
	data->temp[t_hyst] = val;
	lm77_ग_लिखो_value(client, LM77_REG_TEMP_HYST,
			 LM77_TEMP_TO_REG(data->temp[t_hyst]));
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm77_data *data = lm77_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, t_input);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp, t_crit);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp, t_min);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, t_max);

अटल SENSOR_DEVICE_ATTR_RW(temp1_crit_hyst, temp_hyst, t_crit);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_hyst, temp_hyst, t_min);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_hyst, temp_hyst, t_max);

अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 1);

अटल काष्ठा attribute *lm77_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_min_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm77);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm77_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक i, cur, conf, hyst, crit, min, max;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	/*
	 * Here comes the reमुख्यing detection.  Since the LM77 has no
	 * रेजिस्टर dedicated to identअगरication, we have to rely on the
	 * following tricks:
	 *
	 * 1. the high 4 bits represent the sign and thus they should
	 *    always be the same
	 * 2. the high 3 bits are unused in the configuration रेजिस्टर
	 * 3. addresses 0x06 and 0x07 वापस the last पढ़ो value
	 * 4. रेजिस्टरs cycling over 8-address boundaries
	 *
	 * Word-sized रेजिस्टरs are high-byte first.
	 */

	/* addresses cycling */
	cur = i2c_smbus_पढ़ो_word_data(client, 0);
	conf = i2c_smbus_पढ़ो_byte_data(client, 1);
	hyst = i2c_smbus_पढ़ो_word_data(client, 2);
	crit = i2c_smbus_पढ़ो_word_data(client, 3);
	min = i2c_smbus_पढ़ो_word_data(client, 4);
	max = i2c_smbus_पढ़ो_word_data(client, 5);
	क्रम (i = 8; i <= 0xff; i += 8) अणु
		अगर (i2c_smbus_पढ़ो_byte_data(client, i + 1) != conf
		 || i2c_smbus_पढ़ो_word_data(client, i + 2) != hyst
		 || i2c_smbus_पढ़ो_word_data(client, i + 3) != crit
		 || i2c_smbus_पढ़ो_word_data(client, i + 4) != min
		 || i2c_smbus_पढ़ो_word_data(client, i + 5) != max)
			वापस -ENODEV;
	पूर्ण

	/* sign bits */
	अगर (((cur & 0x00f0) != 0xf0 && (cur & 0x00f0) != 0x0)
	 || ((hyst & 0x00f0) != 0xf0 && (hyst & 0x00f0) != 0x0)
	 || ((crit & 0x00f0) != 0xf0 && (crit & 0x00f0) != 0x0)
	 || ((min & 0x00f0) != 0xf0 && (min & 0x00f0) != 0x0)
	 || ((max & 0x00f0) != 0xf0 && (max & 0x00f0) != 0x0))
		वापस -ENODEV;

	/* unused bits */
	अगर (conf & 0xe0)
		वापस -ENODEV;

	/* 0x06 and 0x07 वापस the last पढ़ो value */
	cur = i2c_smbus_पढ़ो_word_data(client, 0);
	अगर (i2c_smbus_पढ़ो_word_data(client, 6) != cur
	 || i2c_smbus_पढ़ो_word_data(client, 7) != cur)
		वापस -ENODEV;
	hyst = i2c_smbus_पढ़ो_word_data(client, 2);
	अगर (i2c_smbus_पढ़ो_word_data(client, 6) != hyst
	 || i2c_smbus_पढ़ो_word_data(client, 7) != hyst)
		वापस -ENODEV;
	min = i2c_smbus_पढ़ो_word_data(client, 4);
	अगर (i2c_smbus_पढ़ो_word_data(client, 6) != min
	 || i2c_smbus_पढ़ो_word_data(client, 7) != min)
		वापस -ENODEV;

	strlcpy(info->type, "lm77", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम lm77_init_client(काष्ठा i2c_client *client)
अणु
	/* Initialize the LM77 chip - turn off shutकरोwn mode */
	पूर्णांक conf = lm77_पढ़ो_value(client, LM77_REG_CONF);
	अगर (conf & 1)
		lm77_ग_लिखो_value(client, LM77_REG_CONF, conf & 0xfe);
पूर्ण

अटल पूर्णांक lm77_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm77_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा lm77_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the LM77 chip */
	lm77_init_client(client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, lm77_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm77_id[] = अणु
	अणु "lm77", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm77_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver lm77_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm77",
	पूर्ण,
	.probe_new	= lm77_probe,
	.id_table	= lm77_id,
	.detect		= lm77_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm77_driver);

MODULE_AUTHOR("Andras BALI <drewie@freemail.hu>");
MODULE_DESCRIPTION("LM77 driver");
MODULE_LICENSE("GPL");
