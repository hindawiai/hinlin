<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max6639.c - Support क्रम Maxim MAX6639
 *
 * 2-Channel Temperature Monitor with Dual PWM Fan-Speed Controller
 *
 * Copyright (C) 2010, 2011 Roland Stigge <stigge@antcom.de>
 *
 * based on the initial MAX6639 support from semptian.net
 * by He Changqing <hechangqing@semptian.com>
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
#समावेश <linux/platक्रमm_data/max6639.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2e, 0x2f, I2C_CLIENT_END पूर्ण;

/* The MAX6639 रेजिस्टरs, valid channel numbers: 0, 1 */
#घोषणा MAX6639_REG_TEMP(ch)			(0x00 + (ch))
#घोषणा MAX6639_REG_STATUS			0x02
#घोषणा MAX6639_REG_OUTPUT_MASK			0x03
#घोषणा MAX6639_REG_GCONFIG			0x04
#घोषणा MAX6639_REG_TEMP_EXT(ch)		(0x05 + (ch))
#घोषणा MAX6639_REG_ALERT_LIMIT(ch)		(0x08 + (ch))
#घोषणा MAX6639_REG_OT_LIMIT(ch)		(0x0A + (ch))
#घोषणा MAX6639_REG_THERM_LIMIT(ch)		(0x0C + (ch))
#घोषणा MAX6639_REG_FAN_CONFIG1(ch)		(0x10 + (ch) * 4)
#घोषणा MAX6639_REG_FAN_CONFIG2a(ch)		(0x11 + (ch) * 4)
#घोषणा MAX6639_REG_FAN_CONFIG2b(ch)		(0x12 + (ch) * 4)
#घोषणा MAX6639_REG_FAN_CONFIG3(ch)		(0x13 + (ch) * 4)
#घोषणा MAX6639_REG_FAN_CNT(ch)			(0x20 + (ch))
#घोषणा MAX6639_REG_TARGET_CNT(ch)		(0x22 + (ch))
#घोषणा MAX6639_REG_FAN_PPR(ch)			(0x24 + (ch))
#घोषणा MAX6639_REG_TARGTDUTY(ch)		(0x26 + (ch))
#घोषणा MAX6639_REG_FAN_START_TEMP(ch)		(0x28 + (ch))
#घोषणा MAX6639_REG_DEVID			0x3D
#घोषणा MAX6639_REG_MANUID			0x3E
#घोषणा MAX6639_REG_DEVREV			0x3F

/* Register bits */
#घोषणा MAX6639_GCONFIG_STANDBY			0x80
#घोषणा MAX6639_GCONFIG_POR			0x40
#घोषणा MAX6639_GCONFIG_DISABLE_TIMEOUT		0x20
#घोषणा MAX6639_GCONFIG_CH2_LOCAL		0x10
#घोषणा MAX6639_GCONFIG_PWM_FREQ_HI		0x08

#घोषणा MAX6639_FAN_CONFIG1_PWM			0x80

#घोषणा MAX6639_FAN_CONFIG3_THERM_FULL_SPEED	0x40

अटल स्थिर पूर्णांक rpm_ranges[] = अणु 2000, 4000, 8000, 16000 पूर्ण;

#घोषणा FAN_FROM_REG(val, rpm_range)	((val) == 0 || (val) == 255 ? \
				0 : (rpm_ranges[rpm_range] * 30) / (val))
#घोषणा TEMP_LIMIT_TO_REG(val)	clamp_val((val) / 1000, 0, 255)

/*
 * Client data (each client माला_लो its own)
 */
काष्ठा max6639_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* Register values sampled regularly */
	u16 temp[2];		/* Temperature, in 1/8 C, 0..255 C */
	bool temp_fault[2];	/* Detected temperature diode failure */
	u8 fan[2];		/* Register value: TACH count क्रम fans >=30 */
	u8 status;		/* Detected channel alarms and fan failures */

	/* Register values only written to */
	u8 pwm[2];		/* Register value: Duty cycle 0..120 */
	u8 temp_therm[2];	/* THERM Temperature, 0..255 C (->_max) */
	u8 temp_alert[2];	/* ALERT Temperature, 0..255 C (->_crit) */
	u8 temp_ot[2];		/* OT Temperature, 0..255 C (->_emergency) */

	/* Register values initialized only once */
	u8 ppr;			/* Pulses per rotation 0..3 क्रम 1..4 ppr */
	u8 rpm_range;		/* Index in above rpm_ranges table */
पूर्ण;

अटल काष्ठा max6639_data *max6639_update_device(काष्ठा device *dev)
अणु
	काष्ठा max6639_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा max6639_data *ret = data;
	पूर्णांक i;
	पूर्णांक status_reg;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + 2 * HZ) || !data->valid) अणु
		पूर्णांक res;

		dev_dbg(&client->dev, "Starting max6639 update\n");

		status_reg = i2c_smbus_पढ़ो_byte_data(client,
						      MAX6639_REG_STATUS);
		अगर (status_reg < 0) अणु
			ret = ERR_PTR(status_reg);
			जाओ पात;
		पूर्ण

		data->status = status_reg;

		क्रम (i = 0; i < 2; i++) अणु
			res = i2c_smbus_पढ़ो_byte_data(client,
					MAX6639_REG_FAN_CNT(i));
			अगर (res < 0) अणु
				ret = ERR_PTR(res);
				जाओ पात;
			पूर्ण
			data->fan[i] = res;

			res = i2c_smbus_पढ़ो_byte_data(client,
					MAX6639_REG_TEMP_EXT(i));
			अगर (res < 0) अणु
				ret = ERR_PTR(res);
				जाओ पात;
			पूर्ण
			data->temp[i] = res >> 5;
			data->temp_fault[i] = res & 0x01;

			res = i2c_smbus_पढ़ो_byte_data(client,
					MAX6639_REG_TEMP(i));
			अगर (res < 0) अणु
				ret = ERR_PTR(res);
				जाओ पात;
			पूर्ण
			data->temp[i] |= res << 3;
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	दीर्घ temp;
	काष्ठा max6639_data *data = max6639_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	temp = data->temp[attr->index] * 125;
	वापस प्र_लिखो(buf, "%ld\n", temp);
पूर्ण

अटल sमाप_प्रकार temp_fault_show(काष्ठा device *dev,
			       काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा max6639_data *data = max6639_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->temp_fault[attr->index]);
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", (data->temp_therm[attr->index] * 1000));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *dev_attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक res;

	res = kम_से_अदीर्घ(buf, 10, &val);
	अगर (res)
		वापस res;

	mutex_lock(&data->update_lock);
	data->temp_therm[attr->index] = TEMP_LIMIT_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client,
				  MAX6639_REG_THERM_LIMIT(attr->index),
				  data->temp_therm[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_crit_show(काष्ठा device *dev,
			      काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", (data->temp_alert[attr->index] * 1000));
पूर्ण

अटल sमाप_प्रकार temp_crit_store(काष्ठा device *dev,
			       काष्ठा device_attribute *dev_attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक res;

	res = kम_से_अदीर्घ(buf, 10, &val);
	अगर (res)
		वापस res;

	mutex_lock(&data->update_lock);
	data->temp_alert[attr->index] = TEMP_LIMIT_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client,
				  MAX6639_REG_ALERT_LIMIT(attr->index),
				  data->temp_alert[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_emergency_show(काष्ठा device *dev,
				   काष्ठा device_attribute *dev_attr,
				   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", (data->temp_ot[attr->index] * 1000));
पूर्ण

अटल sमाप_प्रकार temp_emergency_store(काष्ठा device *dev,
				    काष्ठा device_attribute *dev_attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक res;

	res = kम_से_अदीर्घ(buf, 10, &val);
	अगर (res)
		वापस res;

	mutex_lock(&data->update_lock);
	data->temp_ot[attr->index] = TEMP_LIMIT_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client,
				  MAX6639_REG_OT_LIMIT(attr->index),
				  data->temp_ot[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *dev_attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", data->pwm[attr->index] * 255 / 120);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev,
			 काष्ठा device_attribute *dev_attr, स्थिर अक्षर *buf,
			 माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा max6639_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक res;

	res = kम_से_अदीर्घ(buf, 10, &val);
	अगर (res)
		वापस res;

	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	data->pwm[attr->index] = (u8)(val * 120 / 255);
	i2c_smbus_ग_लिखो_byte_data(client,
				  MAX6639_REG_TARGTDUTY(attr->index),
				  data->pwm[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा max6639_data *data = max6639_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[attr->index],
		       data->rpm_range));
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev,
			  काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा max6639_data *data = max6639_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", !!(data->status & (1 << attr->index)));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp_input, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp1_fault, temp_fault, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, temp_fault, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp_crit, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_crit, temp_crit, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_emergency, temp_emergency, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_emergency, temp_emergency, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_input, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan1_fault, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan2_fault, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp1_emergency_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp2_emergency_alarm, alarm, 4);


अटल काष्ठा attribute *max6639_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_emergency.dev_attr.attr,
	&sensor_dev_attr_temp2_emergency.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan1_fault.dev_attr.attr,
	&sensor_dev_attr_fan2_fault.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_emergency_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_emergency_alarm.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(max6639);

/*
 *  वापसs respective index in rpm_ranges table
 *  1 by शेष on invalid range
 */
अटल पूर्णांक rpm_range_to_reg(पूर्णांक range)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rpm_ranges); i++) अणु
		अगर (rpm_ranges[i] == range)
			वापस i;
	पूर्ण

	वापस 1; /* शेष: 4000 RPM */
पूर्ण

अटल पूर्णांक max6639_init_client(काष्ठा i2c_client *client,
			       काष्ठा max6639_data *data)
अणु
	काष्ठा max6639_platक्रमm_data *max6639_info =
		dev_get_platdata(&client->dev);
	पूर्णांक i;
	पूर्णांक rpm_range = 1; /* शेष: 4000 RPM */
	पूर्णांक err;

	/* Reset chip to शेष values, see below क्रम GCONFIG setup */
	err = i2c_smbus_ग_लिखो_byte_data(client, MAX6639_REG_GCONFIG,
				  MAX6639_GCONFIG_POR);
	अगर (err)
		जाओ निकास;

	/* Fans pulse per revolution is 2 by शेष */
	अगर (max6639_info && max6639_info->ppr > 0 &&
			max6639_info->ppr < 5)
		data->ppr = max6639_info->ppr;
	अन्यथा
		data->ppr = 2;
	data->ppr -= 1;

	अगर (max6639_info)
		rpm_range = rpm_range_to_reg(max6639_info->rpm_range);
	data->rpm_range = rpm_range;

	क्रम (i = 0; i < 2; i++) अणु

		/* Set Fan pulse per revolution */
		err = i2c_smbus_ग_लिखो_byte_data(client,
				MAX6639_REG_FAN_PPR(i),
				data->ppr << 6);
		अगर (err)
			जाओ निकास;

		/* Fans config PWM, RPM */
		err = i2c_smbus_ग_लिखो_byte_data(client,
			MAX6639_REG_FAN_CONFIG1(i),
			MAX6639_FAN_CONFIG1_PWM | rpm_range);
		अगर (err)
			जाओ निकास;

		/* Fans PWM polarity high by शेष */
		अगर (max6639_info && max6639_info->pwm_polarity == 0)
			err = i2c_smbus_ग_लिखो_byte_data(client,
				MAX6639_REG_FAN_CONFIG2a(i), 0x00);
		अन्यथा
			err = i2c_smbus_ग_लिखो_byte_data(client,
				MAX6639_REG_FAN_CONFIG2a(i), 0x02);
		अगर (err)
			जाओ निकास;

		/*
		 * /THERM full speed enable,
		 * PWM frequency 25kHz, see also GCONFIG below
		 */
		err = i2c_smbus_ग_लिखो_byte_data(client,
			MAX6639_REG_FAN_CONFIG3(i),
			MAX6639_FAN_CONFIG3_THERM_FULL_SPEED | 0x03);
		अगर (err)
			जाओ निकास;

		/* Max. temp. 80C/90C/100C */
		data->temp_therm[i] = 80;
		data->temp_alert[i] = 90;
		data->temp_ot[i] = 100;
		err = i2c_smbus_ग_लिखो_byte_data(client,
				MAX6639_REG_THERM_LIMIT(i),
				data->temp_therm[i]);
		अगर (err)
			जाओ निकास;
		err = i2c_smbus_ग_लिखो_byte_data(client,
				MAX6639_REG_ALERT_LIMIT(i),
				data->temp_alert[i]);
		अगर (err)
			जाओ निकास;
		err = i2c_smbus_ग_लिखो_byte_data(client,
				MAX6639_REG_OT_LIMIT(i), data->temp_ot[i]);
		अगर (err)
			जाओ निकास;

		/* PWM 120/120 (i.e. 100%) */
		data->pwm[i] = 120;
		err = i2c_smbus_ग_लिखो_byte_data(client,
				MAX6639_REG_TARGTDUTY(i), data->pwm[i]);
		अगर (err)
			जाओ निकास;
	पूर्ण
	/* Start monitoring */
	err = i2c_smbus_ग_लिखो_byte_data(client, MAX6639_REG_GCONFIG,
		MAX6639_GCONFIG_DISABLE_TIMEOUT | MAX6639_GCONFIG_CH2_LOCAL |
		MAX6639_GCONFIG_PWM_FREQ_HI);
निकास:
	वापस err;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक max6639_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक dev_id, manu_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Actual detection via device and manufacturer ID */
	dev_id = i2c_smbus_पढ़ो_byte_data(client, MAX6639_REG_DEVID);
	manu_id = i2c_smbus_पढ़ो_byte_data(client, MAX6639_REG_MANUID);
	अगर (dev_id != 0x58 || manu_id != 0x4D)
		वापस -ENODEV;

	strlcpy(info->type, "max6639", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक max6639_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा max6639_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा max6639_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the max6639 chip */
	err = max6639_init_client(client, data);
	अगर (err < 0)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   max6639_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max6639_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक data = i2c_smbus_पढ़ो_byte_data(client, MAX6639_REG_GCONFIG);
	अगर (data < 0)
		वापस data;

	वापस i2c_smbus_ग_लिखो_byte_data(client,
			MAX6639_REG_GCONFIG, data | MAX6639_GCONFIG_STANDBY);
पूर्ण

अटल पूर्णांक max6639_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक data = i2c_smbus_पढ़ो_byte_data(client, MAX6639_REG_GCONFIG);
	अगर (data < 0)
		वापस data;

	वापस i2c_smbus_ग_लिखो_byte_data(client,
			MAX6639_REG_GCONFIG, data & ~MAX6639_GCONFIG_STANDBY);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा i2c_device_id max6639_id[] = अणु
	अणु"max6639", 0पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max6639_id);

अटल SIMPLE_DEV_PM_OPS(max6639_pm_ops, max6639_suspend, max6639_resume);

अटल काष्ठा i2c_driver max6639_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		   .name = "max6639",
		   .pm = &max6639_pm_ops,
		   पूर्ण,
	.probe_new = max6639_probe,
	.id_table = max6639_id,
	.detect = max6639_detect,
	.address_list = normal_i2c,
पूर्ण;

module_i2c_driver(max6639_driver);

MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("max6639 driver");
MODULE_LICENSE("GPL");
