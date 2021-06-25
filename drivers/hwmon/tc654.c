<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tc654.c - Linux kernel modules क्रम fan speed controller
 *
 * Copyright (C) 2016 Allied Telesis Lअसल NZ
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/util_macros.h>

क्रमागत tc654_regs अणु
	TC654_REG_RPM1 = 0x00,	/* RPM Output 1 */
	TC654_REG_RPM2 = 0x01,	/* RPM Output 2 */
	TC654_REG_FAN_FAULT1 = 0x02,	/* Fan Fault 1 Threshold */
	TC654_REG_FAN_FAULT2 = 0x03,	/* Fan Fault 2 Threshold */
	TC654_REG_CONFIG = 0x04,	/* Configuration */
	TC654_REG_STATUS = 0x05,	/* Status */
	TC654_REG_DUTY_CYCLE = 0x06,	/* Fan Speed Duty Cycle */
	TC654_REG_MFR_ID = 0x07,	/* Manufacturer Identअगरication */
	TC654_REG_VER_ID = 0x08,	/* Version Identअगरication */
पूर्ण;

/* Macros to easily index the रेजिस्टरs */
#घोषणा TC654_REG_RPM(idx)		(TC654_REG_RPM1 + (idx))
#घोषणा TC654_REG_FAN_FAULT(idx)	(TC654_REG_FAN_FAULT1 + (idx))

/* Config रेजिस्टर bits */
#घोषणा TC654_REG_CONFIG_RES		BIT(6)	/* Resolution Selection */
#घोषणा TC654_REG_CONFIG_DUTYC		BIT(5)	/* Duty Cycle Control */
#घोषणा TC654_REG_CONFIG_SDM		BIT(0)	/* Shutकरोwn Mode */

/* Status रेजिस्टर bits */
#घोषणा TC654_REG_STATUS_F2F		BIT(1)	/* Fan 2 Fault */
#घोषणा TC654_REG_STATUS_F1F		BIT(0)	/* Fan 1 Fault */

/* RPM resolution क्रम RPM Output रेजिस्टरs */
#घोषणा TC654_HIGH_RPM_RESOLUTION	25	/* 25 RPM resolution */
#घोषणा TC654_LOW_RPM_RESOLUTION	50	/* 50 RPM resolution */

/* Convert to the fan fault RPM threshold from रेजिस्टर value */
#घोषणा TC654_FAN_FAULT_FROM_REG(val)	((val) * 50)	/* 50 RPM resolution */

/* Convert to रेजिस्टर value from the fan fault RPM threshold */
#घोषणा TC654_FAN_FAULT_TO_REG(val)	(((val) / 50) & 0xff)

/* Register data is पढ़ो (and cached) at most once per second. */
#घोषणा TC654_UPDATE_INTERVAL		HZ

काष्ठा tc654_data अणु
	काष्ठा i2c_client *client;

	/* update mutex */
	काष्ठा mutex update_lock;

	/* tc654 रेजिस्टर cache */
	bool valid;
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */

	u8 rpm_output[2];	/* The fan RPM data क्रम fans 1 and 2 is then
				 * written to रेजिस्टरs RPM1 and RPM2
				 */
	u8 fan_fault[2];	/* The Fan Fault Threshold Registers are used to
				 * set the fan fault threshold levels क्रम fan 1
				 * and fan 2
				 */
	u8 config;	/* The Configuration Register is an 8-bit पढ़ो/
			 * writable multi-function control रेजिस्टर
			 *   7: Fan Fault Clear
			 *      1 = Clear Fan Fault
			 *      0 = Normal Operation (शेष)
			 *   6: Resolution Selection क्रम RPM Output Registers
			 *      RPM Output Registers (RPM1 and RPM2) will be
			 *      set क्रम
			 *      1 = 25 RPM (9-bit) resolution
			 *      0 = 50 RPM (8-bit) resolution (शेष)
			 *   5: Duty Cycle Control Method
			 *      The V OUT duty cycle will be controlled via
			 *      1 = the SMBus पूर्णांकerface.
			 *      0 = via the V IN analog input pin. (शेष)
			 * 4,3: Fan 2 Pulses Per Rotation
			 *      00 = 1
			 *      01 = 2 (शेष)
			 *      10 = 4
			 *      11 = 8
			 * 2,1: Fan 1 Pulses Per Rotation
			 *      00 = 1
			 *      01 = 2 (शेष)
			 *      10 = 4
			 *      11 = 8
			 *   0: Shutकरोwn Mode
			 *      1 = Shutकरोwn mode.
			 *      0 = Normal operation. (शेष)
			 */
	u8 status;	/* The Status रेजिस्टर provides all the inक्रमmation
			 * about what is going on within the TC654/TC655
			 * devices.
			 * 7,6: Unimplemented, Read as '0'
			 *   5: Over-Temperature Fault Condition
			 *      1 = Over-Temperature condition has occurred
			 *      0 = Normal operation. V IN is less than 2.6V
			 *   4: RPM2 Counter Overflow
			 *      1 = Fault condition
			 *      0 = Normal operation
			 *   3: RPM1 Counter Overflow
			 *      1 = Fault condition
			 *      0 = Normal operation
			 *   2: V IN Input Status
			 *      1 = V IN is खोलो
			 *      0 = Normal operation. voltage present at V IN
			 *   1: Fan 2 Fault
			 *      1 = Fault condition
			 *      0 = Normal operation
			 *   0: Fan 1 Fault
			 *      1 = Fault condition
			 *      0 = Normal operation
			 */
	u8 duty_cycle;	/* The DUTY_CYCLE रेजिस्टर is a 4-bit पढ़ो/
			 * writable रेजिस्टर used to control the duty
			 * cycle of the V OUT output.
			 */
पूर्ण;

/* helper to grab and cache data, at most one समय per second */
अटल काष्ठा tc654_data *tc654_update_client(काष्ठा device *dev)
अणु
	काष्ठा tc654_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret = 0;

	mutex_lock(&data->update_lock);
	अगर (समय_beक्रमe(jअगरfies, data->last_updated + TC654_UPDATE_INTERVAL) &&
	    likely(data->valid))
		जाओ out;

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_RPM(0));
	अगर (ret < 0)
		जाओ out;
	data->rpm_output[0] = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_RPM(1));
	अगर (ret < 0)
		जाओ out;
	data->rpm_output[1] = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_FAN_FAULT(0));
	अगर (ret < 0)
		जाओ out;
	data->fan_fault[0] = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_FAN_FAULT(1));
	अगर (ret < 0)
		जाओ out;
	data->fan_fault[1] = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_CONFIG);
	अगर (ret < 0)
		जाओ out;
	data->config = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_STATUS);
	अगर (ret < 0)
		जाओ out;
	data->status = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_DUTY_CYCLE);
	अगर (ret < 0)
		जाओ out;
	data->duty_cycle = ret & 0x0f;

	data->last_updated = jअगरfies;
	data->valid = true;
out:
	mutex_unlock(&data->update_lock);

	अगर (ret < 0)		/* upon error, encode it in वापस value */
		data = ERR_PTR(ret);

	वापस data;
पूर्ण

/*
 * sysfs attributes
 */

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा tc654_data *data = tc654_update_client(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (data->config & TC654_REG_CONFIG_RES)
		val = data->rpm_output[nr] * TC654_HIGH_RPM_RESOLUTION;
	अन्यथा
		val = data->rpm_output[nr] * TC654_LOW_RPM_RESOLUTION;

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा tc654_data *data = tc654_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n",
		       TC654_FAN_FAULT_FROM_REG(data->fan_fault[nr]));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा tc654_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	val = clamp_val(val, 0, 12750);

	mutex_lock(&data->update_lock);

	data->fan_fault[nr] = TC654_FAN_FAULT_TO_REG(val);
	ret = i2c_smbus_ग_लिखो_byte_data(client, TC654_REG_FAN_FAULT(nr),
					data->fan_fault[nr]);

	mutex_unlock(&data->update_lock);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार fan_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			      अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा tc654_data *data = tc654_update_client(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (nr == 0)
		val = !!(data->status & TC654_REG_STATUS_F1F);
	अन्यथा
		val = !!(data->status & TC654_REG_STATUS_F2F);

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल स्थिर u8 TC654_FAN_PULSE_SHIFT[] = अणु 1, 3 पूर्ण;

अटल sमाप_प्रकार fan_pulses_show(काष्ठा device *dev,
			       काष्ठा device_attribute *da, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा tc654_data *data = tc654_update_client(dev);
	u8 val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = BIT((data->config >> TC654_FAN_PULSE_SHIFT[nr]) & 0x03);
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार fan_pulses_store(काष्ठा device *dev,
				काष्ठा device_attribute *da, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	काष्ठा tc654_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 config;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	चयन (val) अणु
	हाल 1:
		config = 0;
		अवरोध;
	हाल 2:
		config = 1;
		अवरोध;
	हाल 4:
		config = 2;
		अवरोध;
	हाल 8:
		config = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);

	data->config &= ~(0x03 << TC654_FAN_PULSE_SHIFT[nr]);
	data->config |= (config << TC654_FAN_PULSE_SHIFT[nr]);
	ret = i2c_smbus_ग_लिखो_byte_data(client, TC654_REG_CONFIG, data->config);

	mutex_unlock(&data->update_lock);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार pwm_mode_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			     अक्षर *buf)
अणु
	काष्ठा tc654_data *data = tc654_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", !!(data->config & TC654_REG_CONFIG_DUTYC));
पूर्ण

अटल sमाप_प्रकार pwm_mode_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tc654_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	अगर (val)
		data->config |= TC654_REG_CONFIG_DUTYC;
	अन्यथा
		data->config &= ~TC654_REG_CONFIG_DUTYC;

	ret = i2c_smbus_ग_लिखो_byte_data(client, TC654_REG_CONFIG, data->config);

	mutex_unlock(&data->update_lock);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल स्थिर पूर्णांक tc654_pwm_map[16] = अणु 77,  88, 102, 112, 124, 136, 148, 160,
				      172, 184, 196, 207, 219, 231, 243, 255पूर्ण;

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			अक्षर *buf)
अणु
	काष्ठा tc654_data *data = tc654_update_client(dev);
	पूर्णांक pwm;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (data->config & TC654_REG_CONFIG_SDM)
		pwm = 0;
	अन्यथा
		pwm = tc654_pwm_map[data->duty_cycle];

	वापस प्र_लिखो(buf, "%d\n", pwm);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tc654_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;
	अगर (val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);

	अगर (val == 0)
		data->config |= TC654_REG_CONFIG_SDM;
	अन्यथा
		data->config &= ~TC654_REG_CONFIG_SDM;

	data->duty_cycle = find_बंदst(val, tc654_pwm_map,
					ARRAY_SIZE(tc654_pwm_map));

	ret = i2c_smbus_ग_लिखो_byte_data(client, TC654_REG_CONFIG, data->config);
	अगर (ret < 0)
		जाओ out;

	ret = i2c_smbus_ग_लिखो_byte_data(client, TC654_REG_DUTY_CYCLE,
					data->duty_cycle);

out:
	mutex_unlock(&data->update_lock);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, fan_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, fan_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan1_pulses, fan_pulses, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_pulses, fan_pulses, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_mode, pwm_mode, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);

/* Driver data */
अटल काष्ठा attribute *tc654_attrs[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_pulses.dev_attr.attr,
	&sensor_dev_attr_fan2_pulses.dev_attr.attr,
	&sensor_dev_attr_pwm1_mode.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(tc654);

/*
 * device probe and removal
 */

अटल पूर्णांक tc654_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tc654_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(काष्ठा tc654_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	ret = i2c_smbus_पढ़ो_byte_data(client, TC654_REG_CONFIG);
	अगर (ret < 0)
		वापस ret;

	data->config = ret;

	hwmon_dev =
	    devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name, data,
						   tc654_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tc654_id[] = अणु
	अणु"tc654", 0पूर्ण,
	अणु"tc655", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tc654_id);

अटल काष्ठा i2c_driver tc654_driver = अणु
	.driver = अणु
		   .name = "tc654",
		   पूर्ण,
	.probe_new = tc654_probe,
	.id_table = tc654_id,
पूर्ण;

module_i2c_driver(tc654_driver);

MODULE_AUTHOR("Allied Telesis Labs");
MODULE_DESCRIPTION("Microchip TC654/TC655 driver");
MODULE_LICENSE("GPL");
