<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * emc2103.c - Support क्रम SMSC EMC2103
 * Copyright (c) 2010 SMSC
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

/* Addresses scanned */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2E, I2C_CLIENT_END पूर्ण;

अटल स्थिर u8 REG_TEMP[4] = अणु 0x00, 0x02, 0x04, 0x06 पूर्ण;
अटल स्थिर u8 REG_TEMP_MIN[4] = अणु 0x3c, 0x38, 0x39, 0x3a पूर्ण;
अटल स्थिर u8 REG_TEMP_MAX[4] = अणु 0x34, 0x30, 0x31, 0x32 पूर्ण;

#घोषणा REG_CONF1		0x20
#घोषणा REG_TEMP_MAX_ALARM	0x24
#घोषणा REG_TEMP_MIN_ALARM	0x25
#घोषणा REG_FAN_CONF1		0x42
#घोषणा REG_FAN_TARGET_LO	0x4c
#घोषणा REG_FAN_TARGET_HI	0x4d
#घोषणा REG_FAN_TACH_HI		0x4e
#घोषणा REG_FAN_TACH_LO		0x4f
#घोषणा REG_PRODUCT_ID		0xfd
#घोषणा REG_MFG_ID		0xfe

/* equation 4 from datasheet: rpm = (3932160 * multipler) / count */
#घोषणा FAN_RPM_FACTOR		3932160

/*
 * 2103-2 and 2103-4's 3rd temperature sensor can be connected to two diodes
 * in anti-parallel mode, and in this configuration both can be पढ़ो
 * independently (so we have 4 temperature inमाला_दो).  The device can't
 * detect अगर it's connected in this mode, so we have to manually enable
 * it.  Default is to leave the device in the state it's alपढ़ोy in (-1).
 * This parameter allows APD mode to be optionally क्रमced on or off
 */
अटल पूर्णांक apd = -1;
module_param(apd, bपूर्णांक, 0);
MODULE_PARM_DESC(apd, "Set to zero to disable anti-parallel diode mode");

काष्ठा temperature अणु
	s8	degrees;
	u8	fraction;	/* 0-7 multiples of 0.125 */
पूर्ण;

काष्ठा emc2103_data अणु
	काष्ठा i2c_client	*client;
	स्थिर काष्ठा		attribute_group *groups[4];
	काष्ठा mutex		update_lock;
	bool			valid;		/* रेजिस्टरs are valid */
	bool			fan_rpm_control;
	पूर्णांक			temp_count;	/* num of temp sensors */
	अचिन्हित दीर्घ		last_updated;	/* in jअगरfies */
	काष्ठा temperature	temp[4];	/* पूर्णांकernal + 3 बाह्यal */
	s8			temp_min[4];	/* no fractional part */
	s8			temp_max[4];    /* no fractional part */
	u8			temp_min_alarm;
	u8			temp_max_alarm;
	u8			fan_multiplier;
	u16			fan_tach;
	u16			fan_target;
पूर्ण;

अटल पूर्णांक पढ़ो_u8_from_i2c(काष्ठा i2c_client *client, u8 i2c_reg, u8 *output)
अणु
	पूर्णांक status = i2c_smbus_पढ़ो_byte_data(client, i2c_reg);
	अगर (status < 0) अणु
		dev_warn(&client->dev, "reg 0x%02x, err %d\n",
			i2c_reg, status);
	पूर्ण अन्यथा अणु
		*output = status;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम पढ़ो_temp_from_i2c(काष्ठा i2c_client *client, u8 i2c_reg,
			       काष्ठा temperature *temp)
अणु
	u8 degrees, fractional;

	अगर (पढ़ो_u8_from_i2c(client, i2c_reg, &degrees) < 0)
		वापस;

	अगर (पढ़ो_u8_from_i2c(client, i2c_reg + 1, &fractional) < 0)
		वापस;

	temp->degrees = degrees;
	temp->fraction = (fractional & 0xe0) >> 5;
पूर्ण

अटल व्योम पढ़ो_fan_from_i2c(काष्ठा i2c_client *client, u16 *output,
			      u8 hi_addr, u8 lo_addr)
अणु
	u8 high_byte, lo_byte;

	अगर (पढ़ो_u8_from_i2c(client, hi_addr, &high_byte) < 0)
		वापस;

	अगर (पढ़ो_u8_from_i2c(client, lo_addr, &lo_byte) < 0)
		वापस;

	*output = ((u16)high_byte << 5) | (lo_byte >> 3);
पूर्ण

अटल व्योम ग_लिखो_fan_target_to_i2c(काष्ठा i2c_client *client, u16 new_target)
अणु
	u8 high_byte = (new_target & 0x1fe0) >> 5;
	u8 low_byte = (new_target & 0x001f) << 3;
	i2c_smbus_ग_लिखो_byte_data(client, REG_FAN_TARGET_LO, low_byte);
	i2c_smbus_ग_लिखो_byte_data(client, REG_FAN_TARGET_HI, high_byte);
पूर्ण

अटल व्योम पढ़ो_fan_config_from_i2c(काष्ठा i2c_client *client)

अणु
	काष्ठा emc2103_data *data = i2c_get_clientdata(client);
	u8 conf1;

	अगर (पढ़ो_u8_from_i2c(client, REG_FAN_CONF1, &conf1) < 0)
		वापस;

	data->fan_multiplier = 1 << ((conf1 & 0x60) >> 5);
	data->fan_rpm_control = (conf1 & 0x80) != 0;
पूर्ण

अटल काष्ठा emc2103_data *emc2103_update_device(काष्ठा device *dev)
अणु
	काष्ठा emc2103_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		पूर्णांक i;

		क्रम (i = 0; i < data->temp_count; i++) अणु
			पढ़ो_temp_from_i2c(client, REG_TEMP[i], &data->temp[i]);
			पढ़ो_u8_from_i2c(client, REG_TEMP_MIN[i],
				&data->temp_min[i]);
			पढ़ो_u8_from_i2c(client, REG_TEMP_MAX[i],
				&data->temp_max[i]);
		पूर्ण

		पढ़ो_u8_from_i2c(client, REG_TEMP_MIN_ALARM,
			&data->temp_min_alarm);
		पढ़ो_u8_from_i2c(client, REG_TEMP_MAX_ALARM,
			&data->temp_max_alarm);

		पढ़ो_fan_from_i2c(client, &data->fan_tach,
			REG_FAN_TACH_HI, REG_FAN_TACH_LO);
		पढ़ो_fan_from_i2c(client, &data->fan_target,
			REG_FAN_TARGET_HI, REG_FAN_TARGET_LO);
		पढ़ो_fan_config_from_i2c(client);

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल sमाप_प्रकार
temp_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	पूर्णांक millidegrees = data->temp[nr].degrees * 1000
		+ data->temp[nr].fraction * 125;
	वापस प्र_लिखो(buf, "%d\n", millidegrees);
पूर्ण

अटल sमाप_प्रकार
temp_min_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	पूर्णांक millidegrees = data->temp_min[nr] * 1000;
	वापस प्र_लिखो(buf, "%d\n", millidegrees);
पूर्ण

अटल sमाप_प्रकार
temp_max_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	पूर्णांक millidegrees = data->temp_max[nr] * 1000;
	वापस प्र_लिखो(buf, "%d\n", millidegrees);
पूर्ण

अटल sमाप_प्रकार
temp_fault_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	bool fault = (data->temp[nr].degrees == -128);
	वापस प्र_लिखो(buf, "%d\n", fault ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार
temp_min_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
		    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	bool alarm = data->temp_min_alarm & (1 << nr);
	वापस प्र_लिखो(buf, "%d\n", alarm ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार
temp_max_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
		    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	bool alarm = data->temp_max_alarm & (1 << nr);
	वापस प्र_लिखो(buf, "%d\n", alarm ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;

	पूर्णांक result = kम_से_दीर्घ(buf, 10, &val);
	अगर (result < 0)
		वापस result;

	val = DIV_ROUND_CLOSEST(clamp_val(val, -63000, 127000), 1000);

	mutex_lock(&data->update_lock);
	data->temp_min[nr] = val;
	i2c_smbus_ग_लिखो_byte_data(client, REG_TEMP_MIN[nr], val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा emc2103_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;

	पूर्णांक result = kम_से_दीर्घ(buf, 10, &val);
	अगर (result < 0)
		वापस result;

	val = DIV_ROUND_CLOSEST(clamp_val(val, -63000, 127000), 1000);

	mutex_lock(&data->update_lock);
	data->temp_max[nr] = val;
	i2c_smbus_ग_लिखो_byte_data(client, REG_TEMP_MAX[nr], val);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
fan1_input_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	पूर्णांक rpm = 0;
	अगर (data->fan_tach != 0)
		rpm = (FAN_RPM_FACTOR * data->fan_multiplier) / data->fan_tach;
	वापस प्र_लिखो(buf, "%d\n", rpm);
पूर्ण

अटल sमाप_प्रकार
fan1_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	पूर्णांक fan_भाग = 8 / data->fan_multiplier;
	वापस प्र_लिखो(buf, "%d\n", fan_भाग);
पूर्ण

/*
 * Note: we also update the fan target here, because its value is
 * determined in part by the fan घड़ी भागider.  This follows the principle
 * of least surprise; the user करोesn't expect the fan target to change just
 * because the भागider changed.
 */
अटल sमाप_प्रकार fan1_भाग_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक new_range_bits, old_भाग = 8 / data->fan_multiplier;
	दीर्घ new_भाग;

	पूर्णांक status = kम_से_दीर्घ(buf, 10, &new_भाग);
	अगर (status < 0)
		वापस status;

	अगर (new_भाग == old_भाग) /* No change */
		वापस count;

	चयन (new_भाग) अणु
	हाल 1:
		new_range_bits = 3;
		अवरोध;
	हाल 2:
		new_range_bits = 2;
		अवरोध;
	हाल 4:
		new_range_bits = 1;
		अवरोध;
	हाल 8:
		new_range_bits = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);

	status = i2c_smbus_पढ़ो_byte_data(client, REG_FAN_CONF1);
	अगर (status < 0) अणु
		dev_dbg(&client->dev, "reg 0x%02x, err %d\n",
			REG_FAN_CONF1, status);
		mutex_unlock(&data->update_lock);
		वापस status;
	पूर्ण
	status &= 0x9F;
	status |= (new_range_bits << 5);
	i2c_smbus_ग_लिखो_byte_data(client, REG_FAN_CONF1, status);

	data->fan_multiplier = 8 / new_भाग;

	/* update fan target अगर high byte is not disabled */
	अगर ((data->fan_target & 0x1fe0) != 0x1fe0) अणु
		u16 new_target = (data->fan_target * old_भाग) / new_भाग;
		data->fan_target = min(new_target, (u16)0x1fff);
		ग_लिखो_fan_target_to_i2c(client, data->fan_target);
	पूर्ण

	/* invalidate data to क्रमce re-पढ़ो from hardware */
	data->valid = false;

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
fan1_target_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	पूर्णांक rpm = 0;

	/* high byte of 0xff indicates disabled so वापस 0 */
	अगर ((data->fan_target != 0) && ((data->fan_target & 0x1fe0) != 0x1fe0))
		rpm = (FAN_RPM_FACTOR * data->fan_multiplier)
			/ data->fan_target;

	वापस प्र_लिखो(buf, "%d\n", rpm);
पूर्ण

अटल sमाप_प्रकार fan1_target_store(काष्ठा device *dev,
				 काष्ठा device_attribute *da, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ rpm_target;

	पूर्णांक result = kम_से_अदीर्घ(buf, 10, &rpm_target);
	अगर (result < 0)
		वापस result;

	/* Datasheet states 16384 as maximum RPM target (table 3.2) */
	rpm_target = clamp_val(rpm_target, 0, 16384);

	mutex_lock(&data->update_lock);

	अगर (rpm_target == 0)
		data->fan_target = 0x1fff;
	अन्यथा
		data->fan_target = clamp_val(
			(FAN_RPM_FACTOR * data->fan_multiplier) / rpm_target,
			0, 0x1fff);

	ग_लिखो_fan_target_to_i2c(client, data->fan_target);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
fan1_fault_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	bool fault = ((data->fan_tach & 0x1fe0) == 0x1fe0);
	वापस प्र_लिखो(buf, "%d\n", fault ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार
pwm1_enable_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा emc2103_data *data = emc2103_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->fan_rpm_control ? 3 : 0);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *da, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	काष्ठा emc2103_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ new_value;
	u8 conf_reg;

	पूर्णांक result = kम_से_दीर्घ(buf, 10, &new_value);
	अगर (result < 0)
		वापस result;

	mutex_lock(&data->update_lock);
	चयन (new_value) अणु
	हाल 0:
		data->fan_rpm_control = false;
		अवरोध;
	हाल 3:
		data->fan_rpm_control = true;
		अवरोध;
	शेष:
		count = -EINVAL;
		जाओ err;
	पूर्ण

	result = पढ़ो_u8_from_i2c(client, REG_FAN_CONF1, &conf_reg);
	अगर (result < 0) अणु
		count = result;
		जाओ err;
	पूर्ण

	अगर (data->fan_rpm_control)
		conf_reg |= 0x80;
	अन्यथा
		conf_reg &= ~0x80;

	i2c_smbus_ग_लिखो_byte_data(client, REG_FAN_CONF1, conf_reg);
err:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_fault, temp_fault, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, temp_min_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, temp_max_alarm, 0);

अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, temp_fault, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min_alarm, temp_min_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, temp_max_alarm, 1);

अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, temp_fault, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_min_alarm, temp_min_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_alarm, temp_max_alarm, 2);

अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp4_min, temp_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max, temp_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp4_fault, temp_fault, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp4_min_alarm, temp_min_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp4_max_alarm, temp_max_alarm, 3);

अटल DEVICE_ATTR_RO(fan1_input);
अटल DEVICE_ATTR_RW(fan1_भाग);
अटल DEVICE_ATTR_RW(fan1_target);
अटल DEVICE_ATTR_RO(fan1_fault);

अटल DEVICE_ATTR_RW(pwm1_enable);

/* sensors present on all models */
अटल काष्ठा attribute *emc2103_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&dev_attr_fan1_input.attr,
	&dev_attr_fan1_भाग.attr,
	&dev_attr_fan1_target.attr,
	&dev_attr_fan1_fault.attr,
	&dev_attr_pwm1_enable.attr,
	शून्य
पूर्ण;

/* extra temperature sensors only present on 2103-2 and 2103-4 */
अटल काष्ठा attribute *emc2103_attributes_temp3[] = अणु
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;

/* extra temperature sensors only present on 2103-2 and 2103-4 in APD mode */
अटल काष्ठा attribute *emc2103_attributes_temp4[] = अणु
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp4_min.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp4_fault.dev_attr.attr,
	&sensor_dev_attr_temp4_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group emc2103_group = अणु
	.attrs = emc2103_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group emc2103_temp3_group = अणु
	.attrs = emc2103_attributes_temp3,
पूर्ण;

अटल स्थिर काष्ठा attribute_group emc2103_temp4_group = अणु
	.attrs = emc2103_attributes_temp4,
पूर्ण;

अटल पूर्णांक
emc2103_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा emc2103_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक status, idx = 0;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	data = devm_kzalloc(&client->dev, माप(काष्ठा emc2103_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	/* 2103-2 and 2103-4 have 3 बाह्यal diodes, 2103-1 has 1 */
	status = i2c_smbus_पढ़ो_byte_data(client, REG_PRODUCT_ID);
	अगर (status == 0x24) अणु
		/* 2103-1 only has 1 बाह्यal diode */
		data->temp_count = 2;
	पूर्ण अन्यथा अणु
		/* 2103-2 and 2103-4 have 3 or 4 बाह्यal diodes */
		status = i2c_smbus_पढ़ो_byte_data(client, REG_CONF1);
		अगर (status < 0) अणु
			dev_dbg(&client->dev, "reg 0x%02x, err %d\n", REG_CONF1,
				status);
			वापस status;
		पूर्ण

		/* detect current state of hardware */
		data->temp_count = (status & 0x01) ? 4 : 3;

		/* क्रमce APD state अगर module parameter is set */
		अगर (apd == 0) अणु
			/* क्रमce APD mode off */
			data->temp_count = 3;
			status &= ~(0x01);
			i2c_smbus_ग_लिखो_byte_data(client, REG_CONF1, status);
		पूर्ण अन्यथा अगर (apd == 1) अणु
			/* क्रमce APD mode on */
			data->temp_count = 4;
			status |= 0x01;
			i2c_smbus_ग_लिखो_byte_data(client, REG_CONF1, status);
		पूर्ण
	पूर्ण

	/* sysfs hooks */
	data->groups[idx++] = &emc2103_group;
	अगर (data->temp_count >= 3)
		data->groups[idx++] = &emc2103_temp3_group;
	अगर (data->temp_count == 4)
		data->groups[idx++] = &emc2103_temp4_group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   client->name, data,
							   data->groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(&client->dev, "%s: sensor '%s'\n",
		 dev_name(hwmon_dev), client->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id emc2103_ids[] = अणु
	अणु "emc2103", 0, पूर्ण,
	अणु /* LIST END */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, emc2103_ids);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक
emc2103_detect(काष्ठा i2c_client *new_client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	पूर्णांक manufacturer, product;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	manufacturer = i2c_smbus_पढ़ो_byte_data(new_client, REG_MFG_ID);
	अगर (manufacturer != 0x5D)
		वापस -ENODEV;

	product = i2c_smbus_पढ़ो_byte_data(new_client, REG_PRODUCT_ID);
	अगर ((product != 0x24) && (product != 0x26))
		वापस -ENODEV;

	strlcpy(info->type, "emc2103", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver emc2103_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "emc2103",
	पूर्ण,
	.probe_new	= emc2103_probe,
	.id_table	= emc2103_ids,
	.detect		= emc2103_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(emc2103_driver);

MODULE_AUTHOR("Steve Glendinning <steve.glendinning@shawell.net>");
MODULE_DESCRIPTION("SMSC EMC2103 hwmon driver");
MODULE_LICENSE("GPL");
