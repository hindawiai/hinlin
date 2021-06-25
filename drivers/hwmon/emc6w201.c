<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * emc6w201.c - Hardware monitoring driver क्रम the SMSC EMC6W201
 * Copyright (C) 2011  Jean Delvare <jdelvare@suse.de>
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

/*
 * Addresses to scan
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

/*
 * The EMC6W201 रेजिस्टरs
 */

#घोषणा EMC6W201_REG_IN(nr)		(0x20 + (nr))
#घोषणा EMC6W201_REG_TEMP(nr)		(0x26 + (nr))
#घोषणा EMC6W201_REG_FAN(nr)		(0x2C + (nr) * 2)
#घोषणा EMC6W201_REG_COMPANY		0x3E
#घोषणा EMC6W201_REG_VERSTEP		0x3F
#घोषणा EMC6W201_REG_CONFIG		0x40
#घोषणा EMC6W201_REG_IN_LOW(nr)		(0x4A + (nr) * 2)
#घोषणा EMC6W201_REG_IN_HIGH(nr)	(0x4B + (nr) * 2)
#घोषणा EMC6W201_REG_TEMP_LOW(nr)	(0x56 + (nr) * 2)
#घोषणा EMC6W201_REG_TEMP_HIGH(nr)	(0x57 + (nr) * 2)
#घोषणा EMC6W201_REG_FAN_MIN(nr)	(0x62 + (nr) * 2)

क्रमागत subfeature अणु input, min, max पूर्ण;

/*
 * Per-device data
 */

काष्ठा emc6w201_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टरs values */
	u8 in[3][6];
	s8 temp[3][6];
	u16 fan[2][5];
पूर्ण;

/*
 * Combine LSB and MSB रेजिस्टरs in a single value
 * Locking: must be called with data->update_lock held
 */
अटल u16 emc6w201_पढ़ो16(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक lsb, msb;

	lsb = i2c_smbus_पढ़ो_byte_data(client, reg);
	msb = i2c_smbus_पढ़ो_byte_data(client, reg + 1);
	अगर (unlikely(lsb < 0 || msb < 0)) अणु
		dev_err(&client->dev, "%d-bit %s failed at 0x%02x\n",
			16, "read", reg);
		वापस 0xFFFF;	/* Arbitrary value */
	पूर्ण

	वापस (msb << 8) | lsb;
पूर्ण

/*
 * Write 16-bit value to LSB and MSB रेजिस्टरs
 * Locking: must be called with data->update_lock held
 */
अटल पूर्णांक emc6w201_ग_लिखो16(काष्ठा i2c_client *client, u8 reg, u16 val)
अणु
	पूर्णांक err;

	err = i2c_smbus_ग_लिखो_byte_data(client, reg, val & 0xff);
	अगर (likely(!err))
		err = i2c_smbus_ग_लिखो_byte_data(client, reg + 1, val >> 8);
	अगर (unlikely(err < 0))
		dev_err(&client->dev, "%d-bit %s failed at 0x%02x\n",
			16, "write", reg);

	वापस err;
पूर्ण

/* Read 8-bit value from रेजिस्टर */
अटल u8 emc6w201_पढ़ो8(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक val;

	val = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (unlikely(val < 0)) अणु
		dev_err(&client->dev, "%d-bit %s failed at 0x%02x\n",
			8, "read", reg);
		वापस 0x00;	/* Arbitrary value */
	पूर्ण

	वापस val;
पूर्ण

/* Write 8-bit value to रेजिस्टर */
अटल पूर्णांक emc6w201_ग_लिखो8(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक err;

	err = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
	अगर (unlikely(err < 0))
		dev_err(&client->dev, "%d-bit %s failed at 0x%02x\n",
			8, "write", reg);

	वापस err;
पूर्ण

अटल काष्ठा emc6w201_data *emc6w201_update_device(काष्ठा device *dev)
अणु
	काष्ठा emc6w201_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		क्रम (nr = 0; nr < 6; nr++) अणु
			data->in[input][nr] =
				emc6w201_पढ़ो8(client,
						EMC6W201_REG_IN(nr));
			data->in[min][nr] =
				emc6w201_पढ़ो8(client,
						EMC6W201_REG_IN_LOW(nr));
			data->in[max][nr] =
				emc6w201_पढ़ो8(client,
						EMC6W201_REG_IN_HIGH(nr));
		पूर्ण

		क्रम (nr = 0; nr < 6; nr++) अणु
			data->temp[input][nr] =
				emc6w201_पढ़ो8(client,
						EMC6W201_REG_TEMP(nr));
			data->temp[min][nr] =
				emc6w201_पढ़ो8(client,
						EMC6W201_REG_TEMP_LOW(nr));
			data->temp[max][nr] =
				emc6w201_पढ़ो8(client,
						EMC6W201_REG_TEMP_HIGH(nr));
		पूर्ण

		क्रम (nr = 0; nr < 5; nr++) अणु
			data->fan[input][nr] =
				emc6w201_पढ़ो16(client,
						EMC6W201_REG_FAN(nr));
			data->fan[min][nr] =
				emc6w201_पढ़ो16(client,
						EMC6W201_REG_FAN_MIN(nr));
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs callback functions
 */

अटल स्थिर s16 nominal_mv[6] = अणु 2500, 1500, 3300, 5000, 1500, 1500 पूर्ण;

अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		       अक्षर *buf)
अणु
	काष्ठा emc6w201_data *data = emc6w201_update_device(dev);
	पूर्णांक sf = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित)data->in[sf][nr] * nominal_mv[nr] / 0xC0);
पूर्ण

अटल sमाप_प्रकार in_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा emc6w201_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक sf = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक err;
	दीर्घ val;
	u8 reg;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(val, 0, 255 * nominal_mv[nr] / 192);
	val = DIV_ROUND_CLOSEST(val * 192, nominal_mv[nr]);
	reg = (sf == min) ? EMC6W201_REG_IN_LOW(nr)
			  : EMC6W201_REG_IN_HIGH(nr);

	mutex_lock(&data->update_lock);
	data->in[sf][nr] = val;
	err = emc6w201_ग_लिखो8(client, reg, data->in[sf][nr]);
	mutex_unlock(&data->update_lock);

	वापस err < 0 ? err : count;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा emc6w201_data *data = emc6w201_update_device(dev);
	पूर्णांक sf = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->temp[sf][nr] * 1000);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा emc6w201_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक sf = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक err;
	दीर्घ val;
	u8 reg;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(val, -127000, 127000);
	val = DIV_ROUND_CLOSEST(val, 1000);
	reg = (sf == min) ? EMC6W201_REG_TEMP_LOW(nr)
			  : EMC6W201_REG_TEMP_HIGH(nr);

	mutex_lock(&data->update_lock);
	data->temp[sf][nr] = val;
	err = emc6w201_ग_लिखो8(client, reg, data->temp[sf][nr]);
	mutex_unlock(&data->update_lock);

	वापस err < 0 ? err : count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा emc6w201_data *data = emc6w201_update_device(dev);
	पूर्णांक sf = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	अचिन्हित rpm;

	अगर (data->fan[sf][nr] == 0 || data->fan[sf][nr] == 0xFFFF)
		rpm = 0;
	अन्यथा
		rpm = 5400000U / data->fan[sf][nr];

	वापस प्र_लिखो(buf, "%u\n", rpm);
पूर्ण

अटल sमाप_प्रकार fan_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा emc6w201_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक sf = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक err;
	अचिन्हित दीर्घ val;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (val == 0) अणु
		val = 0xFFFF;
	पूर्ण अन्यथा अणु
		val = DIV_ROUND_CLOSEST(5400000U, val);
		val = clamp_val(val, 0, 0xFFFE);
	पूर्ण

	mutex_lock(&data->update_lock);
	data->fan[sf][nr] = val;
	err = emc6w201_ग_लिखो16(client, EMC6W201_REG_FAN_MIN(nr),
			       data->fan[sf][nr]);
	mutex_unlock(&data->update_lock);

	वापस err < 0 ? err : count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_2_RO(in0_input, in, 0, input);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_min, in, 0, min);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_max, in, 0, max);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_input, in, 1, input);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_min, in, 1, min);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_max, in, 1, max);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_input, in, 2, input);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_min, in, 2, min);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_max, in, 2, max);
अटल SENSOR_DEVICE_ATTR_2_RO(in3_input, in, 3, input);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_min, in, 3, min);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_max, in, 3, max);
अटल SENSOR_DEVICE_ATTR_2_RO(in4_input, in, 4, input);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_min, in, 4, min);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_max, in, 4, max);
अटल SENSOR_DEVICE_ATTR_2_RO(in5_input, in, 5, input);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_min, in, 5, min);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_max, in, 5, max);

अटल SENSOR_DEVICE_ATTR_2_RO(temp1_input, temp, 0, input);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_min, temp, 0, min);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_max, temp, 0, max);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_input, temp, 1, input);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_min, temp, 1, min);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_max, temp, 1, max);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_input, temp, 2, input);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_min, temp, 2, min);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_max, temp, 2, max);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_input, temp, 3, input);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_min, temp, 3, min);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_max, temp, 3, max);
अटल SENSOR_DEVICE_ATTR_2_RO(temp5_input, temp, 4, input);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_min, temp, 4, min);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_max, temp, 4, max);
अटल SENSOR_DEVICE_ATTR_2_RO(temp6_input, temp, 5, input);
अटल SENSOR_DEVICE_ATTR_2_RW(temp6_min, temp, 5, min);
अटल SENSOR_DEVICE_ATTR_2_RW(temp6_max, temp, 5, max);

अटल SENSOR_DEVICE_ATTR_2_RO(fan1_input, fan, 0, input);
अटल SENSOR_DEVICE_ATTR_2_RW(fan1_min, fan, 0, min);
अटल SENSOR_DEVICE_ATTR_2_RO(fan2_input, fan, 1, input);
अटल SENSOR_DEVICE_ATTR_2_RW(fan2_min, fan, 1, min);
अटल SENSOR_DEVICE_ATTR_2_RO(fan3_input, fan, 2, input);
अटल SENSOR_DEVICE_ATTR_2_RW(fan3_min, fan, 2, min);
अटल SENSOR_DEVICE_ATTR_2_RO(fan4_input, fan, 3, input);
अटल SENSOR_DEVICE_ATTR_2_RW(fan4_min, fan, 3, min);
अटल SENSOR_DEVICE_ATTR_2_RO(fan5_input, fan, 4, input);
अटल SENSOR_DEVICE_ATTR_2_RW(fan5_min, fan, 4, min);

अटल काष्ठा attribute *emc6w201_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp4_min.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp5_input.dev_attr.attr,
	&sensor_dev_attr_temp5_min.dev_attr.attr,
	&sensor_dev_attr_temp5_max.dev_attr.attr,
	&sensor_dev_attr_temp6_input.dev_attr.attr,
	&sensor_dev_attr_temp6_min.dev_attr.attr,
	&sensor_dev_attr_temp6_max.dev_attr.attr,

	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan5_input.dev_attr.attr,
	&sensor_dev_attr_fan5_min.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(emc6w201);

/*
 * Driver पूर्णांकerface
 */

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक emc6w201_detect(काष्ठा i2c_client *client,
			   काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक company, verstep, config;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Identअगरication */
	company = i2c_smbus_पढ़ो_byte_data(client, EMC6W201_REG_COMPANY);
	अगर (company != 0x5C)
		वापस -ENODEV;
	verstep = i2c_smbus_पढ़ो_byte_data(client, EMC6W201_REG_VERSTEP);
	अगर (verstep < 0 || (verstep & 0xF0) != 0xB0)
		वापस -ENODEV;
	अगर ((verstep & 0x0F) > 2) अणु
		dev_dbg(&client->dev, "Unknown EMC6W201 stepping %d\n",
			verstep & 0x0F);
		वापस -ENODEV;
	पूर्ण

	/* Check configuration */
	config = i2c_smbus_पढ़ो_byte_data(client, EMC6W201_REG_CONFIG);
	अगर (config < 0 || (config & 0xF4) != 0x04)
		वापस -ENODEV;
	अगर (!(config & 0x01)) अणु
		dev_err(&client->dev, "Monitoring not enabled\n");
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "emc6w201", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक emc6w201_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा emc6w201_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा emc6w201_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   emc6w201_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id emc6w201_id[] = अणु
	अणु "emc6w201", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, emc6w201_id);

अटल काष्ठा i2c_driver emc6w201_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "emc6w201",
	पूर्ण,
	.probe_new	= emc6w201_probe,
	.id_table	= emc6w201_id,
	.detect		= emc6w201_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(emc6w201_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("SMSC EMC6W201 hardware monitoring driver");
MODULE_LICENSE("GPL");
