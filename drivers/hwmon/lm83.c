<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm83.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *          monitoring
 * Copyright (C) 2003-2009  Jean Delvare <jdelvare@suse.de>
 *
 * Heavily inspired from the lm78, lm75 and adm1021 drivers. The LM83 is
 * a sensor chip made by National Semiconductor. It reports up to four
 * temperatures (its own plus up to three बाह्यal ones) with a 1 deg
 * resolution and a 3-4 deg accuracy. Complete datasheet can be obtained
 * from National's website at:
 *   http://www.national.com/pf/LM/LM83.hपंचांगl
 * Since the datasheet omits to give the chip stepping code, I give it
 * here: 0x03 (at रेजिस्टर 0xff).
 *
 * Also supports the LM82 temp sensor, which is basically a stripped करोwn
 * model of the LM83.  Datasheet is here:
 * http://www.national.com/pf/LM/LM82.hपंचांगl
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
#समावेश <linux/sysfs.h>

/*
 * Addresses to scan
 * Address is selected using 2 three-level pins, resulting in 9 possible
 * addresses.
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु lm83, lm82 पूर्ण;

/*
 * The LM83 रेजिस्टरs
 * Manufacturer ID is 0x01 क्रम National Semiconductor.
 */

#घोषणा LM83_REG_R_MAN_ID		0xFE
#घोषणा LM83_REG_R_CHIP_ID		0xFF
#घोषणा LM83_REG_R_CONFIG		0x03
#घोषणा LM83_REG_W_CONFIG		0x09
#घोषणा LM83_REG_R_STATUS1		0x02
#घोषणा LM83_REG_R_STATUS2		0x35
#घोषणा LM83_REG_R_LOCAL_TEMP		0x00
#घोषणा LM83_REG_R_LOCAL_HIGH		0x05
#घोषणा LM83_REG_W_LOCAL_HIGH		0x0B
#घोषणा LM83_REG_R_REMOTE1_TEMP		0x30
#घोषणा LM83_REG_R_REMOTE1_HIGH		0x38
#घोषणा LM83_REG_W_REMOTE1_HIGH		0x50
#घोषणा LM83_REG_R_REMOTE2_TEMP		0x01
#घोषणा LM83_REG_R_REMOTE2_HIGH		0x07
#घोषणा LM83_REG_W_REMOTE2_HIGH		0x0D
#घोषणा LM83_REG_R_REMOTE3_TEMP		0x31
#घोषणा LM83_REG_R_REMOTE3_HIGH		0x3A
#घोषणा LM83_REG_W_REMOTE3_HIGH		0x52
#घोषणा LM83_REG_R_TCRIT		0x42
#घोषणा LM83_REG_W_TCRIT		0x5A

/*
 * Conversions and various macros
 * The LM83 uses चिन्हित 8-bit values with LSB = 1 degree Celsius.
 */

#घोषणा TEMP_FROM_REG(val)	((val) * 1000)
#घोषणा TEMP_TO_REG(val)	((val) <= -128000 ? -128 : \
				 (val) >= 127000 ? 127 : \
				 (val) < 0 ? ((val) - 500) / 1000 : \
				 ((val) + 500) / 1000)

अटल स्थिर u8 LM83_REG_R_TEMP[] = अणु
	LM83_REG_R_LOCAL_TEMP,
	LM83_REG_R_REMOTE1_TEMP,
	LM83_REG_R_REMOTE2_TEMP,
	LM83_REG_R_REMOTE3_TEMP,
	LM83_REG_R_LOCAL_HIGH,
	LM83_REG_R_REMOTE1_HIGH,
	LM83_REG_R_REMOTE2_HIGH,
	LM83_REG_R_REMOTE3_HIGH,
	LM83_REG_R_TCRIT,
पूर्ण;

अटल स्थिर u8 LM83_REG_W_HIGH[] = अणु
	LM83_REG_W_LOCAL_HIGH,
	LM83_REG_W_REMOTE1_HIGH,
	LM83_REG_W_REMOTE2_HIGH,
	LM83_REG_W_REMOTE3_HIGH,
	LM83_REG_W_TCRIT,
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा lm83_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टरs values */
	s8 temp[9];	/* 0..3: input 1-4,
			   4..7: high limit 1-4,
			   8   : critical limit */
	u16 alarms; /* bitvector, combined */
पूर्ण;

अटल काष्ठा lm83_data *lm83_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm83_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ * 2) || !data->valid) अणु
		पूर्णांक nr;

		dev_dbg(&client->dev, "Updating lm83 data.\n");
		क्रम (nr = 0; nr < 9; nr++) अणु
			data->temp[nr] =
			    i2c_smbus_पढ़ो_byte_data(client,
			    LM83_REG_R_TEMP[nr]);
		पूर्ण
		data->alarms =
		    i2c_smbus_पढ़ो_byte_data(client, LM83_REG_R_STATUS1)
		    + (i2c_smbus_पढ़ो_byte_data(client, LM83_REG_R_STATUS2)
		    << 8);

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
	काष्ठा lm83_data *data = lm83_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm83_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक nr = attr->index;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[nr] = TEMP_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client, LM83_REG_W_HIGH[nr - 4],
				  data->temp[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *dummy,
			   अक्षर *buf)
अणु
	काष्ठा lm83_data *data = lm83_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm83_data *data = lm83_update_device(dev);
	पूर्णांक bitnr = attr->index;

	वापस प्र_लिखो(buf, "%d\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp, 6);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max, temp, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit, temp, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit, temp, 8);
अटल SENSOR_DEVICE_ATTR_RW(temp3_crit, temp, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp4_crit, temp, 8);

/* Inभागidual alarm files */
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp4_crit_alarm, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(temp4_fault, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(temp4_max_alarm, alarm, 12);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 13);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, 15);
/* Raw alarm file क्रम compatibility */
अटल DEVICE_ATTR_RO(alarms);

अटल काष्ठा attribute *lm83_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,

	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&dev_attr_alarms.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm83_group = अणु
	.attrs = lm83_attributes,
पूर्ण;

अटल काष्ठा attribute *lm83_attributes_opt[] = अणु
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp4_crit.dev_attr.attr,

	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_fault.dev_attr.attr,
	&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm83_group_opt = अणु
	.attrs = lm83_attributes_opt,
पूर्ण;

/*
 * Real code
 */

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm83_detect(काष्ठा i2c_client *new_client,
		       काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	स्थिर अक्षर *name;
	u8 man_id, chip_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Detection */
	अगर ((i2c_smbus_पढ़ो_byte_data(new_client, LM83_REG_R_STATUS1) & 0xA8) ||
	    (i2c_smbus_पढ़ो_byte_data(new_client, LM83_REG_R_STATUS2) & 0x48) ||
	    (i2c_smbus_पढ़ो_byte_data(new_client, LM83_REG_R_CONFIG) & 0x41)) अणु
		dev_dbg(&adapter->dev, "LM83 detection failed at 0x%02x\n",
			new_client->addr);
		वापस -ENODEV;
	पूर्ण

	/* Identअगरication */
	man_id = i2c_smbus_पढ़ो_byte_data(new_client, LM83_REG_R_MAN_ID);
	अगर (man_id != 0x01)	/* National Semiconductor */
		वापस -ENODEV;

	chip_id = i2c_smbus_पढ़ो_byte_data(new_client, LM83_REG_R_CHIP_ID);
	चयन (chip_id) अणु
	हाल 0x03:
		name = "lm83";
		अवरोध;
	हाल 0x01:
		name = "lm82";
		अवरोध;
	शेष:
		/* identअगरication failed */
		dev_info(&adapter->dev,
			 "Unsupported chip (man_id=0x%02X, chip_id=0x%02X)\n",
			 man_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm83_id[];

अटल पूर्णांक lm83_probe(काष्ठा i2c_client *new_client)
अणु
	काष्ठा device *hwmon_dev;
	काष्ठा lm83_data *data;

	data = devm_kzalloc(&new_client->dev, माप(काष्ठा lm83_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = new_client;
	mutex_init(&data->update_lock);

	/*
	 * Register sysfs hooks
	 * The LM82 can only monitor one बाह्यal diode which is
	 * at the same रेजिस्टर as the LM83 temp3 entry - so we
	 * declare 1 and 3 common, and then 2 and 4 only क्रम the LM83.
	 */
	data->groups[0] = &lm83_group;
	अगर (i2c_match_id(lm83_id, new_client)->driver_data == lm83)
		data->groups[1] = &lm83_group_opt;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&new_client->dev,
							   new_client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id lm83_id[] = अणु
	अणु "lm83", lm83 पूर्ण,
	अणु "lm82", lm82 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm83_id);

अटल काष्ठा i2c_driver lm83_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm83",
	पूर्ण,
	.probe_new	= lm83_probe,
	.id_table	= lm83_id,
	.detect		= lm83_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm83_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("LM83 driver");
MODULE_LICENSE("GPL");
