<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2012 Guenter Roeck <linux@roeck-us.net>
 *
 * based on max1668.c
 * Copyright (c) 2011 David George <david.george@ska.ac.za>
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
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>

#समावेश <linux/platक्रमm_data/max6697.h>

क्रमागत chips अणु max6581, max6602, max6622, max6636, max6689, max6693, max6694,
	     max6697, max6698, max6699 पूर्ण;

/* Report local sensor as temp1 */

अटल स्थिर u8 MAX6697_REG_TEMP[] = अणु
			0x07, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08 पूर्ण;
अटल स्थिर u8 MAX6697_REG_TEMP_EXT[] = अणु
			0x57, 0x09, 0x52, 0x53, 0x54, 0x55, 0x56, 0 पूर्ण;
अटल स्थिर u8 MAX6697_REG_MAX[] = अणु
			0x17, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x18 पूर्ण;
अटल स्थिर u8 MAX6697_REG_CRIT[] = अणु
			0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27 पूर्ण;

/*
 * Map device tree / platक्रमm data रेजिस्टर bit map to chip bit map.
 * Applies to alert रेजिस्टर and over-temperature रेजिस्टर.
 */
#घोषणा MAX6697_ALERT_MAP_BITS(reg)	((((reg) & 0x7e) >> 1) | \
				 (((reg) & 0x01) << 6) | ((reg) & 0x80))
#घोषणा MAX6697_OVERT_MAP_BITS(reg) (((reg) >> 1) | (((reg) & 0x01) << 7))

#घोषणा MAX6697_REG_STAT(n)		(0x44 + (n))

#घोषणा MAX6697_REG_CONFIG		0x41
#घोषणा MAX6581_CONF_EXTENDED		(1 << 1)
#घोषणा MAX6693_CONF_BETA		(1 << 2)
#घोषणा MAX6697_CONF_RESISTANCE		(1 << 3)
#घोषणा MAX6697_CONF_TIMEOUT		(1 << 5)
#घोषणा MAX6697_REG_ALERT_MASK		0x42
#घोषणा MAX6697_REG_OVERT_MASK		0x43

#घोषणा MAX6581_REG_RESISTANCE		0x4a
#घोषणा MAX6581_REG_IDEALITY		0x4b
#घोषणा MAX6581_REG_IDEALITY_SELECT	0x4c
#घोषणा MAX6581_REG_OFFSET		0x4d
#घोषणा MAX6581_REG_OFFSET_SELECT	0x4e
#घोषणा MAX6581_OFFSET_MIN		-31750
#घोषणा MAX6581_OFFSET_MAX		31750

#घोषणा MAX6697_CONV_TIME		156	/* ms per channel, worst हाल */

काष्ठा max6697_chip_data अणु
	पूर्णांक channels;
	u32 have_ext;
	u32 have_crit;
	u32 have_fault;
	u8 valid_conf;
	स्थिर u8 *alarm_map;
पूर्ण;

काष्ठा max6697_data अणु
	काष्ठा i2c_client *client;

	क्रमागत chips type;
	स्थिर काष्ठा max6697_chip_data *chip;

	पूर्णांक update_पूर्णांकerval;	/* in milli-seconds */
	पूर्णांक temp_offset;	/* in degrees C */

	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	bool valid;		/* true अगर following fields are valid */

	/* 1x local and up to 7x remote */
	u8 temp[8][4];		/* [nr][0]=temp [1]=ext [2]=max [3]=crit */
#घोषणा MAX6697_TEMP_INPUT	0
#घोषणा MAX6697_TEMP_EXT	1
#घोषणा MAX6697_TEMP_MAX	2
#घोषणा MAX6697_TEMP_CRIT	3
	u32 alarms;
पूर्ण;

/* Diode fault status bits on MAX6581 are right shअगरted by one bit */
अटल स्थिर u8 max6581_alarm_map[] = अणु
	 0, 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15,
	 16, 17, 18, 19, 20, 21, 22, 23 पूर्ण;

अटल स्थिर काष्ठा max6697_chip_data max6697_chip_data[] = अणु
	[max6581] = अणु
		.channels = 8,
		.have_crit = 0xff,
		.have_ext = 0x7f,
		.have_fault = 0xfe,
		.valid_conf = MAX6581_CONF_EXTENDED | MAX6697_CONF_TIMEOUT,
		.alarm_map = max6581_alarm_map,
	पूर्ण,
	[max6602] = अणु
		.channels = 5,
		.have_crit = 0x12,
		.have_ext = 0x02,
		.have_fault = 0x1e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6622] = अणु
		.channels = 5,
		.have_crit = 0x12,
		.have_ext = 0x02,
		.have_fault = 0x1e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6636] = अणु
		.channels = 7,
		.have_crit = 0x72,
		.have_ext = 0x02,
		.have_fault = 0x7e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6689] = अणु
		.channels = 7,
		.have_crit = 0x72,
		.have_ext = 0x02,
		.have_fault = 0x7e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6693] = अणु
		.channels = 7,
		.have_crit = 0x72,
		.have_ext = 0x02,
		.have_fault = 0x7e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6693_CONF_BETA |
		  MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6694] = अणु
		.channels = 5,
		.have_crit = 0x12,
		.have_ext = 0x02,
		.have_fault = 0x1e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6693_CONF_BETA |
		  MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6697] = अणु
		.channels = 7,
		.have_crit = 0x72,
		.have_ext = 0x02,
		.have_fault = 0x7e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6698] = अणु
		.channels = 7,
		.have_crit = 0x72,
		.have_ext = 0x02,
		.have_fault = 0x0e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6697_CONF_TIMEOUT,
	पूर्ण,
	[max6699] = अणु
		.channels = 5,
		.have_crit = 0x12,
		.have_ext = 0x02,
		.have_fault = 0x1e,
		.valid_conf = MAX6697_CONF_RESISTANCE | MAX6697_CONF_TIMEOUT,
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक max6581_offset_to_millic(पूर्णांक val)
अणु
	वापस sign_extend32(val, 7) * 250;
पूर्ण

अटल काष्ठा max6697_data *max6697_update_device(काष्ठा device *dev)
अणु
	काष्ठा max6697_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा max6697_data *ret = data;
	पूर्णांक val;
	पूर्णांक i;
	u32 alarms;

	mutex_lock(&data->update_lock);

	अगर (data->valid &&
	    !समय_after(jअगरfies, data->last_updated
			+ msecs_to_jअगरfies(data->update_पूर्णांकerval)))
		जाओ पात;

	क्रम (i = 0; i < data->chip->channels; i++) अणु
		अगर (data->chip->have_ext & (1 << i)) अणु
			val = i2c_smbus_पढ़ो_byte_data(client,
						       MAX6697_REG_TEMP_EXT[i]);
			अगर (unlikely(val < 0)) अणु
				ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			data->temp[i][MAX6697_TEMP_EXT] = val;
		पूर्ण

		val = i2c_smbus_पढ़ो_byte_data(client, MAX6697_REG_TEMP[i]);
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp[i][MAX6697_TEMP_INPUT] = val;

		val = i2c_smbus_पढ़ो_byte_data(client, MAX6697_REG_MAX[i]);
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp[i][MAX6697_TEMP_MAX] = val;

		अगर (data->chip->have_crit & (1 << i)) अणु
			val = i2c_smbus_पढ़ो_byte_data(client,
						       MAX6697_REG_CRIT[i]);
			अगर (unlikely(val < 0)) अणु
				ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			data->temp[i][MAX6697_TEMP_CRIT] = val;
		पूर्ण
	पूर्ण

	alarms = 0;
	क्रम (i = 0; i < 3; i++) अणु
		val = i2c_smbus_पढ़ो_byte_data(client, MAX6697_REG_STAT(i));
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		alarms = (alarms << 8) | val;
	पूर्ण
	data->alarms = alarms;
	data->last_updated = jअगरfies;
	data->valid = true;
पात:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	काष्ठा max6697_data *data = max6697_update_device(dev);
	पूर्णांक temp;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	temp = (data->temp[index][MAX6697_TEMP_INPUT] - data->temp_offset) << 3;
	temp |= data->temp[index][MAX6697_TEMP_EXT] >> 5;

	वापस प्र_लिखो(buf, "%d\n", temp * 125);
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक index = to_sensor_dev_attr_2(devattr)->index;
	काष्ठा max6697_data *data = max6697_update_device(dev);
	पूर्णांक temp;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	temp = data->temp[nr][index];
	temp -= data->temp_offset;

	वापस प्र_लिखो(buf, "%d\n", temp * 1000);
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा max6697_data *data = max6697_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (data->chip->alarm_map)
		index = data->chip->alarm_map[index];

	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> index) & 0x1);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक index = to_sensor_dev_attr_2(devattr)->index;
	काष्ठा max6697_data *data = dev_get_drvdata(dev);
	दीर्घ temp;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &temp);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);
	temp = DIV_ROUND_CLOSEST(temp, 1000) + data->temp_offset;
	temp = clamp_val(temp, 0, data->type == max6581 ? 255 : 127);
	data->temp[nr][index] = temp;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					index == 2 ? MAX6697_REG_MAX[nr]
						   : MAX6697_REG_CRIT[nr],
					temp);
	mutex_unlock(&data->update_lock);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार offset_store(काष्ठा device *dev, काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक val, ret, index, select;
	काष्ठा max6697_data *data;
	bool channel_enabled;
	दीर्घ temp;

	index = to_sensor_dev_attr(devattr)->index;
	data = dev_get_drvdata(dev);
	ret = kम_से_दीर्घ(buf, 10, &temp);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);
	select = i2c_smbus_पढ़ो_byte_data(data->client, MAX6581_REG_OFFSET_SELECT);
	अगर (select < 0) अणु
		ret = select;
		जाओ पात;
	पूर्ण
	channel_enabled = (select & (1 << (index - 1)));
	temp = clamp_val(temp, MAX6581_OFFSET_MIN, MAX6581_OFFSET_MAX);
	val = DIV_ROUND_CLOSEST(temp, 250);
	/* disable the offset क्रम channel अगर the new offset is 0 */
	अगर (val == 0) अणु
		अगर (channel_enabled)
			ret = i2c_smbus_ग_लिखो_byte_data(data->client, MAX6581_REG_OFFSET_SELECT,
							select & ~(1 << (index - 1)));
		ret = ret < 0 ? ret : count;
		जाओ पात;
	पूर्ण
	अगर (!channel_enabled) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(data->client, MAX6581_REG_OFFSET_SELECT,
						select | (1 << (index - 1)));
		अगर (ret < 0)
			जाओ पात;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, MAX6581_REG_OFFSET, val);
	ret = ret < 0 ? ret : count;

पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार offset_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा max6697_data *data;
	पूर्णांक select, ret, index;

	index = to_sensor_dev_attr(devattr)->index;
	data = dev_get_drvdata(dev);
	mutex_lock(&data->update_lock);
	select = i2c_smbus_पढ़ो_byte_data(data->client, MAX6581_REG_OFFSET_SELECT);
	अगर (select < 0)
		ret = select;
	अन्यथा अगर (select & (1 << (index - 1)))
		ret = i2c_smbus_पढ़ो_byte_data(data->client, MAX6581_REG_OFFSET);
	अन्यथा
		ret = 0;
	mutex_unlock(&data->update_lock);
	वापस ret < 0 ? ret : प्र_लिखो(buf, "%d\n", max6581_offset_to_millic(ret));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_input, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_max, temp, 0, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_crit, temp, 0, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp_input, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_max, temp, 1, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_crit, temp, 1, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp_input, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_max, temp, 2, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_crit, temp, 2, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp_input, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_max, temp, 3, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_crit, temp, 3, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp5_input, temp_input, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_max, temp, 4, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_crit, temp, 4, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp6_input, temp_input, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(temp6_max, temp, 5, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp6_crit, temp, 5, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp7_input, temp_input, 6);
अटल SENSOR_DEVICE_ATTR_2_RW(temp7_max, temp, 6, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp7_crit, temp, 6, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp8_input, temp_input, 7);
अटल SENSOR_DEVICE_ATTR_2_RW(temp8_max, temp, 7, MAX6697_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_2_RW(temp8_crit, temp, 7, MAX6697_TEMP_CRIT);

अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 22);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, 16);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_alarm, alarm, 17);
अटल SENSOR_DEVICE_ATTR_RO(temp4_max_alarm, alarm, 18);
अटल SENSOR_DEVICE_ATTR_RO(temp5_max_alarm, alarm, 19);
अटल SENSOR_DEVICE_ATTR_RO(temp6_max_alarm, alarm, 20);
अटल SENSOR_DEVICE_ATTR_RO(temp7_max_alarm, alarm, 21);
अटल SENSOR_DEVICE_ATTR_RO(temp8_max_alarm, alarm, 23);

अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 14);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_alarm, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(temp4_crit_alarm, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(temp5_crit_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp6_crit_alarm, alarm, 12);
अटल SENSOR_DEVICE_ATTR_RO(temp7_crit_alarm, alarm, 13);
अटल SENSOR_DEVICE_ATTR_RO(temp8_crit_alarm, alarm, 15);

अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_fault, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_fault, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_fault, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp7_fault, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp8_fault, alarm, 7);

/* There is no offset क्रम local temperature so starting from temp2 */
अटल SENSOR_DEVICE_ATTR_RW(temp2_offset, offset, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_offset, offset, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_offset, offset, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp5_offset, offset, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp6_offset, offset, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp7_offset, offset, 6);
अटल SENSOR_DEVICE_ATTR_RW(temp8_offset, offset, 7);

अटल DEVICE_ATTR(dummy, 0, शून्य, शून्य);

अटल umode_t max6697_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				  पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा max6697_data *data = dev_get_drvdata(dev);
	स्थिर काष्ठा max6697_chip_data *chip = data->chip;
	पूर्णांक channel = index / 7;	/* channel number */
	पूर्णांक nr = index % 7;		/* attribute index within channel */

	अगर (channel >= chip->channels)
		वापस 0;

	अगर ((nr == 3 || nr == 4) && !(chip->have_crit & (1 << channel)))
		वापस 0;
	अगर (nr == 5 && !(chip->have_fault & (1 << channel)))
		वापस 0;
	/* offset reg is only supported on max6581 remote channels */
	अगर (nr == 6)
		अगर (data->type != max6581 || channel == 0)
			वापस 0;

	वापस attr->mode;
पूर्ण

/*
 * max6697_is_visible uses the index पूर्णांकo the following array to determine
 * अगर attributes should be created or not. Any change in order or content
 * must be matched in max6697_is_visible.
 */
अटल काष्ठा attribute *max6697_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&dev_attr_dummy.attr,
	&dev_attr_dummy.attr,

	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,

	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,

	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_crit.dev_attr.attr,
	&sensor_dev_attr_temp4_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_fault.dev_attr.attr,
	&sensor_dev_attr_temp4_offset.dev_attr.attr,

	&sensor_dev_attr_temp5_input.dev_attr.attr,
	&sensor_dev_attr_temp5_max.dev_attr.attr,
	&sensor_dev_attr_temp5_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_crit.dev_attr.attr,
	&sensor_dev_attr_temp5_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_fault.dev_attr.attr,
	&sensor_dev_attr_temp5_offset.dev_attr.attr,

	&sensor_dev_attr_temp6_input.dev_attr.attr,
	&sensor_dev_attr_temp6_max.dev_attr.attr,
	&sensor_dev_attr_temp6_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp6_crit.dev_attr.attr,
	&sensor_dev_attr_temp6_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp6_fault.dev_attr.attr,
	&sensor_dev_attr_temp6_offset.dev_attr.attr,

	&sensor_dev_attr_temp7_input.dev_attr.attr,
	&sensor_dev_attr_temp7_max.dev_attr.attr,
	&sensor_dev_attr_temp7_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp7_crit.dev_attr.attr,
	&sensor_dev_attr_temp7_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp7_fault.dev_attr.attr,
	&sensor_dev_attr_temp7_offset.dev_attr.attr,

	&sensor_dev_attr_temp8_input.dev_attr.attr,
	&sensor_dev_attr_temp8_max.dev_attr.attr,
	&sensor_dev_attr_temp8_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp8_crit.dev_attr.attr,
	&sensor_dev_attr_temp8_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp8_fault.dev_attr.attr,
	&sensor_dev_attr_temp8_offset.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group max6697_group = अणु
	.attrs = max6697_attributes, .is_visible = max6697_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(max6697);

अटल व्योम max6697_get_config_of(काष्ठा device_node *node,
				  काष्ठा max6697_platक्रमm_data *pdata)
अणु
	पूर्णांक len;
	स्थिर __be32 *prop;

	pdata->smbus_समयout_disable =
		of_property_पढ़ो_bool(node, "smbus-timeout-disable");
	pdata->extended_range_enable =
		of_property_पढ़ो_bool(node, "extended-range-enable");
	pdata->beta_compensation =
		of_property_पढ़ो_bool(node, "beta-compensation-enable");

	prop = of_get_property(node, "alert-mask", &len);
	अगर (prop && len == माप(u32))
		pdata->alert_mask = be32_to_cpu(prop[0]);
	prop = of_get_property(node, "over-temperature-mask", &len);
	अगर (prop && len == माप(u32))
		pdata->over_temperature_mask = be32_to_cpu(prop[0]);
	prop = of_get_property(node, "resistance-cancellation", &len);
	अगर (prop) अणु
		अगर (len == माप(u32))
			pdata->resistance_cancellation = be32_to_cpu(prop[0]);
		अन्यथा
			pdata->resistance_cancellation = 0xfe;
	पूर्ण
	prop = of_get_property(node, "transistor-ideality", &len);
	अगर (prop && len == 2 * माप(u32)) अणु
			pdata->ideality_mask = be32_to_cpu(prop[0]);
			pdata->ideality_value = be32_to_cpu(prop[1]);
	पूर्ण
पूर्ण

अटल पूर्णांक max6697_init_chip(काष्ठा max6697_data *data,
			     काष्ठा i2c_client *client)
अणु
	काष्ठा max6697_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा max6697_platक्रमm_data p;
	स्थिर काष्ठा max6697_chip_data *chip = data->chip;
	पूर्णांक factor = chip->channels;
	पूर्णांक ret, reg;

	/*
	 * Don't touch configuration अगर neither platक्रमm data nor OF
	 * configuration was specअगरied. If that is the हाल, use the
	 * current chip configuration.
	 */
	अगर (!pdata && !client->dev.of_node) अणु
		reg = i2c_smbus_पढ़ो_byte_data(client, MAX6697_REG_CONFIG);
		अगर (reg < 0)
			वापस reg;
		अगर (data->type == max6581) अणु
			अगर (reg & MAX6581_CONF_EXTENDED)
				data->temp_offset = 64;
			reg = i2c_smbus_पढ़ो_byte_data(client,
						       MAX6581_REG_RESISTANCE);
			अगर (reg < 0)
				वापस reg;
			factor += hweight8(reg);
		पूर्ण अन्यथा अणु
			अगर (reg & MAX6697_CONF_RESISTANCE)
				factor++;
		पूर्ण
		जाओ करोne;
	पूर्ण

	अगर (client->dev.of_node) अणु
		स_रखो(&p, 0, माप(p));
		max6697_get_config_of(client->dev.of_node, &p);
		pdata = &p;
	पूर्ण

	reg = 0;
	अगर (pdata->smbus_समयout_disable &&
	    (chip->valid_conf & MAX6697_CONF_TIMEOUT)) अणु
		reg |= MAX6697_CONF_TIMEOUT;
	पूर्ण
	अगर (pdata->extended_range_enable &&
	    (chip->valid_conf & MAX6581_CONF_EXTENDED)) अणु
		reg |= MAX6581_CONF_EXTENDED;
		data->temp_offset = 64;
	पूर्ण
	अगर (pdata->resistance_cancellation &&
	    (chip->valid_conf & MAX6697_CONF_RESISTANCE)) अणु
		reg |= MAX6697_CONF_RESISTANCE;
		factor++;
	पूर्ण
	अगर (pdata->beta_compensation &&
	    (chip->valid_conf & MAX6693_CONF_BETA)) अणु
		reg |= MAX6693_CONF_BETA;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(client, MAX6697_REG_CONFIG, reg);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, MAX6697_REG_ALERT_MASK,
				MAX6697_ALERT_MAP_BITS(pdata->alert_mask));
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, MAX6697_REG_OVERT_MASK,
			MAX6697_OVERT_MAP_BITS(pdata->over_temperature_mask));
	अगर (ret < 0)
		वापस ret;

	अगर (data->type == max6581) अणु
		factor += hweight8(pdata->resistance_cancellation >> 1);
		ret = i2c_smbus_ग_लिखो_byte_data(client, MAX6581_REG_RESISTANCE,
					pdata->resistance_cancellation >> 1);
		अगर (ret < 0)
			वापस ret;
		ret = i2c_smbus_ग_लिखो_byte_data(client, MAX6581_REG_IDEALITY,
						pdata->ideality_value);
		अगर (ret < 0)
			वापस ret;
		ret = i2c_smbus_ग_लिखो_byte_data(client,
						MAX6581_REG_IDEALITY_SELECT,
						pdata->ideality_mask >> 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
करोne:
	data->update_पूर्णांकerval = factor * MAX6697_CONV_TIME;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max6697_id[];

अटल पूर्णांक max6697_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा max6697_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(काष्ठा max6697_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (client->dev.of_node)
		data->type = (क्रमागत chips)of_device_get_match_data(&client->dev);
	अन्यथा
		data->type = i2c_match_id(max6697_id, client)->driver_data;
	data->chip = &max6697_chip_data[data->type];
	data->client = client;
	mutex_init(&data->update_lock);

	err = max6697_init_chip(data, client);
	अगर (err)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   max6697_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max6697_id[] = अणु
	अणु "max6581", max6581 पूर्ण,
	अणु "max6602", max6602 पूर्ण,
	अणु "max6622", max6622 पूर्ण,
	अणु "max6636", max6636 पूर्ण,
	अणु "max6689", max6689 पूर्ण,
	अणु "max6693", max6693 पूर्ण,
	अणु "max6694", max6694 पूर्ण,
	अणु "max6697", max6697 पूर्ण,
	अणु "max6698", max6698 पूर्ण,
	अणु "max6699", max6699 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max6697_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused max6697_of_match[] = अणु
	अणु
		.compatible = "maxim,max6581",
		.data = (व्योम *)max6581
	पूर्ण,
	अणु
		.compatible = "maxim,max6602",
		.data = (व्योम *)max6602
	पूर्ण,
	अणु
		.compatible = "maxim,max6622",
		.data = (व्योम *)max6622
	पूर्ण,
	अणु
		.compatible = "maxim,max6636",
		.data = (व्योम *)max6636
	पूर्ण,
	अणु
		.compatible = "maxim,max6689",
		.data = (व्योम *)max6689
	पूर्ण,
	अणु
		.compatible = "maxim,max6693",
		.data = (व्योम *)max6693
	पूर्ण,
	अणु
		.compatible = "maxim,max6694",
		.data = (व्योम *)max6694
	पूर्ण,
	अणु
		.compatible = "maxim,max6697",
		.data = (व्योम *)max6697
	पूर्ण,
	अणु
		.compatible = "maxim,max6698",
		.data = (व्योम *)max6698
	पूर्ण,
	अणु
		.compatible = "maxim,max6699",
		.data = (व्योम *)max6699
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max6697_of_match);

अटल काष्ठा i2c_driver max6697_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "max6697",
		.of_match_table = of_match_ptr(max6697_of_match),
	पूर्ण,
	.probe_new = max6697_probe,
	.id_table = max6697_id,
पूर्ण;

module_i2c_driver(max6697_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("MAX6697 temperature sensor driver");
MODULE_LICENSE("GPL");
