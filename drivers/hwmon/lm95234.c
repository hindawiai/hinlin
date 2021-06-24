<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Texas Instruments / National Semiconductor LM95234
 *
 * Copyright (c) 2013, 2014 Guenter Roeck <linux@roeck-us.net>
 *
 * Derived from lm95241.c
 * Copyright (C) 2008, 2010 Davide Rizzo <elpa.rizzo@gmail.com>
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

#घोषणा DRVNAME "lm95234"

क्रमागत chips अणु lm95233, lm95234 पूर्ण;

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x18, 0x2a, 0x2b, 0x4d, 0x4e, I2C_CLIENT_END पूर्ण;

/* LM95234 रेजिस्टरs */
#घोषणा LM95234_REG_MAN_ID		0xFE
#घोषणा LM95234_REG_CHIP_ID		0xFF
#घोषणा LM95234_REG_STATUS		0x02
#घोषणा LM95234_REG_CONFIG		0x03
#घोषणा LM95234_REG_CONVRATE		0x04
#घोषणा LM95234_REG_STS_FAULT		0x07
#घोषणा LM95234_REG_STS_TCRIT1		0x08
#घोषणा LM95234_REG_STS_TCRIT2		0x09
#घोषणा LM95234_REG_TEMPH(x)		((x) + 0x10)
#घोषणा LM95234_REG_TEMPL(x)		((x) + 0x20)
#घोषणा LM95234_REG_UTEMPH(x)		((x) + 0x19)	/* Remote only */
#घोषणा LM95234_REG_UTEMPL(x)		((x) + 0x29)
#घोषणा LM95234_REG_REM_MODEL		0x30
#घोषणा LM95234_REG_REM_MODEL_STS	0x38
#घोषणा LM95234_REG_OFFSET(x)		((x) + 0x31)	/* Remote only */
#घोषणा LM95234_REG_TCRIT1(x)		((x) + 0x40)
#घोषणा LM95234_REG_TCRIT2(x)		((x) + 0x49)	/* Remote channel 1,2 */
#घोषणा LM95234_REG_TCRIT_HYST		0x5a

#घोषणा NATSEMI_MAN_ID			0x01
#घोषणा LM95233_CHIP_ID			0x89
#घोषणा LM95234_CHIP_ID			0x79

/* Client data (each client माला_लो its own) */
काष्ठा lm95234_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated, पूर्णांकerval;	/* in jअगरfies */
	bool valid;		/* false until following fields are valid */
	/* रेजिस्टरs values */
	पूर्णांक temp[5];		/* temperature (चिन्हित) */
	u32 status;		/* fault/alarm status */
	u8 tcrit1[5];		/* critical temperature limit */
	u8 tcrit2[2];		/* high temperature limit */
	s8 toffset[4];		/* remote temperature offset */
	u8 thyst;		/* common hysteresis */

	u8 sensor_type;		/* temperature sensor type */
पूर्ण;

अटल पूर्णांक lm95234_पढ़ो_temp(काष्ठा i2c_client *client, पूर्णांक index, पूर्णांक *t)
अणु
	पूर्णांक val;
	u16 temp = 0;

	अगर (index) अणु
		val = i2c_smbus_पढ़ो_byte_data(client,
					       LM95234_REG_UTEMPH(index - 1));
		अगर (val < 0)
			वापस val;
		temp = val << 8;
		val = i2c_smbus_पढ़ो_byte_data(client,
					       LM95234_REG_UTEMPL(index - 1));
		अगर (val < 0)
			वापस val;
		temp |= val;
		*t = temp;
	पूर्ण
	/*
	 * Read चिन्हित temperature अगर अचिन्हित temperature is 0,
	 * or अगर this is the local sensor.
	 */
	अगर (!temp) अणु
		val = i2c_smbus_पढ़ो_byte_data(client,
					       LM95234_REG_TEMPH(index));
		अगर (val < 0)
			वापस val;
		temp = val << 8;
		val = i2c_smbus_पढ़ो_byte_data(client,
					       LM95234_REG_TEMPL(index));
		अगर (val < 0)
			वापस val;
		temp |= val;
		*t = (s16)temp;
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 update_पूर्णांकervals[] = अणु 143, 364, 1000, 2500 पूर्ण;

/* Fill value cache. Must be called with update lock held. */

अटल पूर्णांक lm95234_fill_cache(काष्ठा lm95234_data *data,
			      काष्ठा i2c_client *client)
अणु
	पूर्णांक i, ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_CONVRATE);
	अगर (ret < 0)
		वापस ret;

	data->पूर्णांकerval = msecs_to_jअगरfies(update_पूर्णांकervals[ret & 0x03]);

	क्रम (i = 0; i < ARRAY_SIZE(data->tcrit1); i++) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_TCRIT1(i));
		अगर (ret < 0)
			वापस ret;
		data->tcrit1[i] = ret;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(data->tcrit2); i++) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_TCRIT2(i));
		अगर (ret < 0)
			वापस ret;
		data->tcrit2[i] = ret;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(data->toffset); i++) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_OFFSET(i));
		अगर (ret < 0)
			वापस ret;
		data->toffset[i] = ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_TCRIT_HYST);
	अगर (ret < 0)
		वापस ret;
	data->thyst = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_REM_MODEL);
	अगर (ret < 0)
		वापस ret;
	data->sensor_type = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक lm95234_update_device(काष्ठा lm95234_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + data->पूर्णांकerval) ||
	    !data->valid) अणु
		पूर्णांक i;

		अगर (!data->valid) अणु
			ret = lm95234_fill_cache(data, client);
			अगर (ret < 0)
				जाओ पात;
		पूर्ण

		data->valid = false;
		क्रम (i = 0; i < ARRAY_SIZE(data->temp); i++) अणु
			ret = lm95234_पढ़ो_temp(client, i, &data->temp[i]);
			अगर (ret < 0)
				जाओ पात;
		पूर्ण

		ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_STS_FAULT);
		अगर (ret < 0)
			जाओ पात;
		data->status = ret;

		ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_STS_TCRIT1);
		अगर (ret < 0)
			जाओ पात;
		data->status |= ret << 8;

		ret = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_STS_TCRIT2);
		अगर (ret < 0)
			जाओ पात;
		data->status |= ret << 16;

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण
	ret = 0;
पात:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n",
		       DIV_ROUND_CLOSEST(data->temp[index] * 125, 32));
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	u32 mask = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u", !!(data->status & mask));
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	u8 mask = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, data->sensor_type & mask ? "1\n" : "2\n");
पूर्ण

अटल sमाप_प्रकार type_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	u8 mask = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val != 1 && val != 2)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (val == 1)
		data->sensor_type |= mask;
	अन्यथा
		data->sensor_type &= ~mask;
	data->valid = false;
	i2c_smbus_ग_लिखो_byte_data(data->client, LM95234_REG_REM_MODEL,
				  data->sensor_type);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार tcrit2_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u", data->tcrit2[index] * 1000);
पूर्ण

अटल sमाप_प्रकार tcrit2_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), 0, index ? 255 : 127);

	mutex_lock(&data->update_lock);
	data->tcrit2[index] = val;
	i2c_smbus_ग_लिखो_byte_data(data->client, LM95234_REG_TCRIT2(index), val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार tcrit2_hyst_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	/* Result can be negative, so be careful with अचिन्हित opeअक्रमs */
	वापस प्र_लिखो(buf, "%d",
		       ((पूर्णांक)data->tcrit2[index] - (पूर्णांक)data->thyst) * 1000);
पूर्ण

अटल sमाप_प्रकार tcrit1_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%u", data->tcrit1[index] * 1000);
पूर्ण

अटल sमाप_प्रकार tcrit1_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);
	दीर्घ val;

	अगर (ret)
		वापस ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	val = clamp_val(DIV_ROUND_CLOSEST(val, 1000), 0, 255);

	mutex_lock(&data->update_lock);
	data->tcrit1[index] = val;
	i2c_smbus_ग_लिखो_byte_data(data->client, LM95234_REG_TCRIT1(index), val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार tcrit1_hyst_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	/* Result can be negative, so be careful with अचिन्हित opeअक्रमs */
	वापस प्र_लिखो(buf, "%d",
		       ((पूर्णांक)data->tcrit1[index] - (पूर्णांक)data->thyst) * 1000);
पूर्ण

अटल sमाप_प्रकार tcrit1_hyst_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);
	दीर्घ val;

	अगर (ret)
		वापस ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	val = DIV_ROUND_CLOSEST(val, 1000);
	val = clamp_val((पूर्णांक)data->tcrit1[index] - val, 0, 31);

	mutex_lock(&data->update_lock);
	data->thyst = val;
	i2c_smbus_ग_लिखो_byte_data(data->client, LM95234_REG_TCRIT_HYST, val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार offset_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d", data->toffset[index] * 500);
पूर्ण

अटल sमाप_प्रकार offset_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = lm95234_update_device(data);
	दीर्घ val;

	अगर (ret)
		वापस ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	/* Accuracy is 1/2 degrees C */
	val = clamp_val(DIV_ROUND_CLOSEST(val, 500), -128, 127);

	mutex_lock(&data->update_lock);
	data->toffset[index] = val;
	i2c_smbus_ग_लिखो_byte_data(data->client, LM95234_REG_OFFSET(index), val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = lm95234_update_device(data);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%lu\n",
		       DIV_ROUND_CLOSEST(data->पूर्णांकerval * 1000, HZ));
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm95234_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = lm95234_update_device(data);
	अचिन्हित दीर्घ val;
	u8 regval;

	अगर (ret)
		वापस ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	क्रम (regval = 0; regval < 3; regval++) अणु
		अगर (val <= update_पूर्णांकervals[regval])
			अवरोध;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->पूर्णांकerval = msecs_to_jअगरfies(update_पूर्णांकervals[regval]);
	i2c_smbus_ग_लिखो_byte_data(data->client, LM95234_REG_CONVRATE, regval);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_input, temp, 4);

अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, BIT(0) | BIT(1));
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, BIT(2) | BIT(3));
अटल SENSOR_DEVICE_ATTR_RO(temp4_fault, alarm, BIT(4) | BIT(5));
अटल SENSOR_DEVICE_ATTR_RO(temp5_fault, alarm, BIT(6) | BIT(7));

अटल SENSOR_DEVICE_ATTR_RW(temp2_type, type, BIT(1));
अटल SENSOR_DEVICE_ATTR_RW(temp3_type, type, BIT(2));
अटल SENSOR_DEVICE_ATTR_RW(temp4_type, type, BIT(3));
अटल SENSOR_DEVICE_ATTR_RW(temp5_type, type, BIT(4));

अटल SENSOR_DEVICE_ATTR_RW(temp1_max, tcrit1, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, tcrit2, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, tcrit2, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max, tcrit1, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp5_max, tcrit1, 4);

अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, tcrit1_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_hyst, tcrit2_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_hyst, tcrit2_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp4_max_hyst, tcrit1_hyst, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_max_hyst, tcrit1_hyst, 4);

अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, BIT(0 + 8));
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, BIT(1 + 16));
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_alarm, alarm, BIT(2 + 16));
अटल SENSOR_DEVICE_ATTR_RO(temp4_max_alarm, alarm, BIT(3 + 8));
अटल SENSOR_DEVICE_ATTR_RO(temp5_max_alarm, alarm, BIT(4 + 8));

अटल SENSOR_DEVICE_ATTR_RW(temp2_crit, tcrit1, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_crit, tcrit1, 2);

अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_hyst, tcrit1_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_hyst, tcrit1_hyst, 2);

अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, alarm, BIT(1 + 8));
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_alarm, alarm, BIT(2 + 8));

अटल SENSOR_DEVICE_ATTR_RW(temp2_offset, offset, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp3_offset, offset, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp4_offset, offset, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp5_offset, offset, 3);

अटल DEVICE_ATTR_RW(update_पूर्णांकerval);

अटल काष्ठा attribute *lm95234_common_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_type.dev_attr.attr,
	&sensor_dev_attr_temp3_type.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,
	&dev_attr_update_पूर्णांकerval.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm95234_common_group = अणु
	.attrs = lm95234_common_attrs,
पूर्ण;

अटल काष्ठा attribute *lm95234_attrs[] = अणु
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp5_input.dev_attr.attr,
	&sensor_dev_attr_temp4_fault.dev_attr.attr,
	&sensor_dev_attr_temp5_fault.dev_attr.attr,
	&sensor_dev_attr_temp4_type.dev_attr.attr,
	&sensor_dev_attr_temp5_type.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp5_max.dev_attr.attr,
	&sensor_dev_attr_temp4_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp5_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_offset.dev_attr.attr,
	&sensor_dev_attr_temp5_offset.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm95234_group = अणु
	.attrs = lm95234_attrs,
पूर्ण;

अटल पूर्णांक lm95234_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक address = client->addr;
	u8 config_mask, model_mask;
	पूर्णांक mfg_id, chip_id, val;
	स्थिर अक्षर *name;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	mfg_id = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_MAN_ID);
	अगर (mfg_id != NATSEMI_MAN_ID)
		वापस -ENODEV;

	chip_id = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_CHIP_ID);
	चयन (chip_id) अणु
	हाल LM95233_CHIP_ID:
		अगर (address != 0x18 && address != 0x2a && address != 0x2b)
			वापस -ENODEV;
		config_mask = 0xbf;
		model_mask = 0xf9;
		name = "lm95233";
		अवरोध;
	हाल LM95234_CHIP_ID:
		अगर (address != 0x18 && address != 0x4d && address != 0x4e)
			वापस -ENODEV;
		config_mask = 0xbc;
		model_mask = 0xe1;
		name = "lm95234";
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	val = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_STATUS);
	अगर (val & 0x30)
		वापस -ENODEV;

	val = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_CONFIG);
	अगर (val & config_mask)
		वापस -ENODEV;

	val = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_CONVRATE);
	अगर (val & 0xfc)
		वापस -ENODEV;

	val = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_REM_MODEL);
	अगर (val & model_mask)
		वापस -ENODEV;

	val = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_REM_MODEL_STS);
	अगर (val & model_mask)
		वापस -ENODEV;

	strlcpy(info->type, name, I2C_NAME_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक lm95234_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक val, model;

	/* start conversion अगर necessary */
	val = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_CONFIG);
	अगर (val < 0)
		वापस val;
	अगर (val & 0x40)
		i2c_smbus_ग_लिखो_byte_data(client, LM95234_REG_CONFIG,
					  val & ~0x40);

	/* If diode type status reports an error, try to fix it */
	val = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_REM_MODEL_STS);
	अगर (val < 0)
		वापस val;
	model = i2c_smbus_पढ़ो_byte_data(client, LM95234_REG_REM_MODEL);
	अगर (model < 0)
		वापस model;
	अगर (model & val) अणु
		dev_notice(&client->dev,
			   "Fixing remote diode type misconfiguration (0x%x)\n",
			   val);
		i2c_smbus_ग_लिखो_byte_data(client, LM95234_REG_REM_MODEL,
					  model & ~val);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm95234_id[];

अटल पूर्णांक lm95234_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा lm95234_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा lm95234_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the LM95234 chip */
	err = lm95234_init_client(client);
	अगर (err < 0)
		वापस err;

	data->groups[0] = &lm95234_common_group;
	अगर (i2c_match_id(lm95234_id, client)->driver_data == lm95234)
		data->groups[1] = &lm95234_group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/* Driver data (common to all clients) */
अटल स्थिर काष्ठा i2c_device_id lm95234_id[] = अणु
	अणु "lm95233", lm95233 पूर्ण,
	अणु "lm95234", lm95234 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm95234_id);

अटल काष्ठा i2c_driver lm95234_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe_new	= lm95234_probe,
	.id_table	= lm95234_id,
	.detect		= lm95234_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm95234_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("LM95233/LM95234 sensor driver");
MODULE_LICENSE("GPL");
