<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 David George <david.george@ska.ac.za>
 *
 * based on adm1021.c
 * some credit to Christoph Scheurer, but largely a reग_लिखो
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
अटल स्थिर अचिन्हित लघु max1668_addr_list[] = अणु
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x4c, 0x4d, 0x4e, I2C_CLIENT_END पूर्ण;

/* max1668 रेजिस्टरs */

#घोषणा MAX1668_REG_TEMP(nr)	(nr)
#घोषणा MAX1668_REG_STAT1	0x05
#घोषणा MAX1668_REG_STAT2	0x06
#घोषणा MAX1668_REG_MAN_ID	0xfe
#घोषणा MAX1668_REG_DEV_ID	0xff

/* limits */

/* ग_लिखो high limits */
#घोषणा MAX1668_REG_LIMH_WR(nr)	(0x13 + 2 * (nr))
/* ग_लिखो low limits */
#घोषणा MAX1668_REG_LIML_WR(nr)	(0x14 + 2 * (nr))
/* पढ़ो high limits */
#घोषणा MAX1668_REG_LIMH_RD(nr)	(0x08 + 2 * (nr))
/* पढ़ो low limits */
#घोषणा MAX1668_REG_LIML_RD(nr)	(0x09 + 2 * (nr))

/* manufacturer and device ID Constants */
#घोषणा MAN_ID_MAXIM		0x4d
#घोषणा DEV_ID_MAX1668		0x3
#घोषणा DEV_ID_MAX1805		0x5
#घोषणा DEV_ID_MAX1989		0xb

/* पढ़ो only mode module parameter */
अटल bool पढ़ो_only;
module_param(पढ़ो_only, bool, 0);
MODULE_PARM_DESC(पढ़ो_only, "Don't set any values, read only mode");

क्रमागत chips अणु max1668, max1805, max1989 पूर्ण;

काष्ठा max1668_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	क्रमागत chips type;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* 1x local and 4x remote */
	s8 temp_max[5];
	s8 temp_min[5];
	s8 temp[5];
	u16 alarms;
पूर्ण;

अटल काष्ठा max1668_data *max1668_update_device(काष्ठा device *dev)
अणु
	काष्ठा max1668_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा max1668_data *ret = data;
	s32 val;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (data->valid && !समय_after(jअगरfies,
			data->last_updated + HZ + HZ / 2))
		जाओ पात;

	क्रम (i = 0; i < 5; i++) अणु
		val = i2c_smbus_पढ़ो_byte_data(client, MAX1668_REG_TEMP(i));
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp[i] = (s8) val;

		val = i2c_smbus_पढ़ो_byte_data(client, MAX1668_REG_LIMH_RD(i));
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp_max[i] = (s8) val;

		val = i2c_smbus_पढ़ो_byte_data(client, MAX1668_REG_LIML_RD(i));
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp_min[i] = (s8) val;
	पूर्ण

	val = i2c_smbus_पढ़ो_byte_data(client, MAX1668_REG_STAT1);
	अगर (unlikely(val < 0)) अणु
		ret = ERR_PTR(val);
		जाओ पात;
	पूर्ण
	data->alarms = val << 8;

	val = i2c_smbus_पढ़ो_byte_data(client, MAX1668_REG_STAT2);
	अगर (unlikely(val < 0)) अणु
		ret = ERR_PTR(val);
		जाओ पात;
	पूर्ण
	data->alarms |= val;

	data->last_updated = jअगरfies;
	data->valid = 1;
पात:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_temp(काष्ठा device *dev,
			 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा max1668_data *data = max1668_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->temp[index] * 1000);
पूर्ण

अटल sमाप_प्रकार show_temp_max(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा max1668_data *data = max1668_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->temp_max[index] * 1000);
पूर्ण

अटल sमाप_प्रकार show_temp_min(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा max1668_data *data = max1668_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->temp_min[index] * 1000);
पूर्ण

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा max1668_data *data = max1668_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> index) & 0x1);
पूर्ण

अटल sमाप_प्रकार show_fault(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा max1668_data *data = max1668_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%u\n",
		       (data->alarms & (1 << 12)) && data->temp[index] == 127);
पूर्ण

अटल sमाप_प्रकार set_temp_max(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा max1668_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &temp);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);
	data->temp_max[index] = clamp_val(temp/1000, -128, 127);
	ret = i2c_smbus_ग_लिखो_byte_data(client,
					MAX1668_REG_LIMH_WR(index),
					data->temp_max[index]);
	अगर (ret < 0)
		count = ret;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार set_temp_min(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा max1668_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &temp);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);
	data->temp_min[index] = clamp_val(temp/1000, -128, 127);
	ret = i2c_smbus_ग_लिखो_byte_data(client,
					MAX1668_REG_LIML_WR(index),
					data->temp_min[index]);
	अगर (ret < 0)
		count = ret;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, show_temp, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_max, S_IRUGO, show_temp_max,
				set_temp_max, 0);
अटल SENSOR_DEVICE_ATTR(temp1_min, S_IRUGO, show_temp_min,
				set_temp_min, 0);
अटल SENSOR_DEVICE_ATTR(temp2_input, S_IRUGO, show_temp, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp2_max, S_IRUGO, show_temp_max,
				set_temp_max, 1);
अटल SENSOR_DEVICE_ATTR(temp2_min, S_IRUGO, show_temp_min,
				set_temp_min, 1);
अटल SENSOR_DEVICE_ATTR(temp3_input, S_IRUGO, show_temp, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp3_max, S_IRUGO, show_temp_max,
				set_temp_max, 2);
अटल SENSOR_DEVICE_ATTR(temp3_min, S_IRUGO, show_temp_min,
				set_temp_min, 2);
अटल SENSOR_DEVICE_ATTR(temp4_input, S_IRUGO, show_temp, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(temp4_max, S_IRUGO, show_temp_max,
				set_temp_max, 3);
अटल SENSOR_DEVICE_ATTR(temp4_min, S_IRUGO, show_temp_min,
				set_temp_min, 3);
अटल SENSOR_DEVICE_ATTR(temp5_input, S_IRUGO, show_temp, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(temp5_max, S_IRUGO, show_temp_max,
				set_temp_max, 4);
अटल SENSOR_DEVICE_ATTR(temp5_min, S_IRUGO, show_temp_min,
				set_temp_min, 4);

अटल SENSOR_DEVICE_ATTR(temp1_max_alarm, S_IRUGO, show_alarm, शून्य, 14);
अटल SENSOR_DEVICE_ATTR(temp1_min_alarm, S_IRUGO, show_alarm, शून्य, 13);
अटल SENSOR_DEVICE_ATTR(temp2_min_alarm, S_IRUGO, show_alarm, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(temp2_max_alarm, S_IRUGO, show_alarm, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(temp3_min_alarm, S_IRUGO, show_alarm, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(temp3_max_alarm, S_IRUGO, show_alarm, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(temp4_min_alarm, S_IRUGO, show_alarm, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(temp4_max_alarm, S_IRUGO, show_alarm, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp5_min_alarm, S_IRUGO, show_alarm, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp5_max_alarm, S_IRUGO, show_alarm, शून्य, 0);

अटल SENSOR_DEVICE_ATTR(temp2_fault, S_IRUGO, show_fault, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp3_fault, S_IRUGO, show_fault, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp4_fault, S_IRUGO, show_fault, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(temp5_fault, S_IRUGO, show_fault, शून्य, 4);

/* Attributes common to MAX1668, MAX1989 and MAX1805 */
अटल काष्ठा attribute *max1668_attribute_common[] = अणु
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,

	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_min_alarm.dev_attr.attr,

	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	शून्य
पूर्ण;

/* Attributes not present on MAX1805 */
अटल काष्ठा attribute *max1668_attribute_unique[] = अणु
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp4_min.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp5_max.dev_attr.attr,
	&sensor_dev_attr_temp5_min.dev_attr.attr,
	&sensor_dev_attr_temp5_input.dev_attr.attr,

	&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_min_alarm.dev_attr.attr,

	&sensor_dev_attr_temp4_fault.dev_attr.attr,
	&sensor_dev_attr_temp5_fault.dev_attr.attr,
	शून्य
पूर्ण;

अटल umode_t max1668_attribute_mode(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक index)
अणु
	umode_t ret = S_IRUGO;
	अगर (पढ़ो_only)
		वापस ret;
	अगर (attr == &sensor_dev_attr_temp1_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp2_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp3_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp4_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp5_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp1_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp2_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp3_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp4_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_temp5_min.dev_attr.attr)
		ret |= S_IWUSR;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा attribute_group max1668_group_common = अणु
	.attrs = max1668_attribute_common,
	.is_visible = max1668_attribute_mode
पूर्ण;

अटल स्थिर काष्ठा attribute_group max1668_group_unique = अणु
	.attrs = max1668_attribute_unique,
	.is_visible = max1668_attribute_mode
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक max1668_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	स्थिर अक्षर *type_name;
	पूर्णांक man_id, dev_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Check क्रम unsupported part */
	man_id = i2c_smbus_पढ़ो_byte_data(client, MAX1668_REG_MAN_ID);
	अगर (man_id != MAN_ID_MAXIM)
		वापस -ENODEV;

	dev_id = i2c_smbus_पढ़ो_byte_data(client, MAX1668_REG_DEV_ID);
	अगर (dev_id < 0)
		वापस -ENODEV;

	type_name = शून्य;
	अगर (dev_id == DEV_ID_MAX1668)
		type_name = "max1668";
	अन्यथा अगर (dev_id == DEV_ID_MAX1805)
		type_name = "max1805";
	अन्यथा अगर (dev_id == DEV_ID_MAX1989)
		type_name = "max1989";

	अगर (!type_name)
		वापस -ENODEV;

	strlcpy(info->type, type_name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max1668_id[];

अटल पूर्णांक max1668_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा max1668_data *data;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(काष्ठा max1668_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->type = i2c_match_id(max1668_id, client)->driver_data;
	mutex_init(&data->update_lock);

	/* sysfs hooks */
	data->groups[0] = &max1668_group_common;
	अगर (data->type == max1668 || data->type == max1989)
		data->groups[1] = &max1668_group_unique;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max1668_id[] = अणु
	अणु "max1668", max1668 पूर्ण,
	अणु "max1805", max1805 पूर्ण,
	अणु "max1989", max1989 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max1668_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver max1668_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		  .name	= "max1668",
		  पूर्ण,
	.probe_new = max1668_probe,
	.id_table = max1668_id,
	.detect	= max1668_detect,
	.address_list = max1668_addr_list,
पूर्ण;

module_i2c_driver(max1668_driver);

MODULE_AUTHOR("David George <david.george@ska.ac.za>");
MODULE_DESCRIPTION("MAX1668 remote temperature sensor driver");
MODULE_LICENSE("GPL");
