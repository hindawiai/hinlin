<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max6650.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *             monitoring.
 *
 * (C) 2007 by Hans J. Koch <hjk@hansjkoch.de>
 *
 * based on code written by John Morris <john.morris@spirentcom.com>
 * Copyright (c) 2003 Spirent Communications
 * and Claus Gindhart <claus.gindhart@kontron.com>
 *
 * This module has only been tested with the MAX6650 chip. It should
 * also work with the MAX6651. It करोes not distinguish max6650 and max6651
 * chips.
 *
 * The datasheet was last seen at:
 *
 *        http://pdfserv.maxim-ic.com/en/ds/MAX6650-MAX6651.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/of_device.h>
#समावेश <linux/thermal.h>

/*
 * Insmod parameters
 */

/* fan_voltage: 5=5V fan, 12=12V fan, 0=करोn't change */
अटल पूर्णांक fan_voltage;
/* prescaler: Possible values are 1, 2, 4, 8, 16 or 0 क्रम करोn't change */
अटल पूर्णांक prescaler;
/* घड़ी: The घड़ी frequency of the chip (max6651 can be घड़ीed बाह्यally) */
अटल पूर्णांक घड़ी = 254000;

module_param(fan_voltage, पूर्णांक, 0444);
module_param(prescaler, पूर्णांक, 0444);
module_param(घड़ी, पूर्णांक, 0444);

/*
 * MAX 6650/6651 रेजिस्टरs
 */

#घोषणा MAX6650_REG_SPEED	0x00
#घोषणा MAX6650_REG_CONFIG	0x02
#घोषणा MAX6650_REG_GPIO_DEF	0x04
#घोषणा MAX6650_REG_DAC		0x06
#घोषणा MAX6650_REG_ALARM_EN	0x08
#घोषणा MAX6650_REG_ALARM	0x0A
#घोषणा MAX6650_REG_TACH0	0x0C
#घोषणा MAX6650_REG_TACH1	0x0E
#घोषणा MAX6650_REG_TACH2	0x10
#घोषणा MAX6650_REG_TACH3	0x12
#घोषणा MAX6650_REG_GPIO_STAT	0x14
#घोषणा MAX6650_REG_COUNT	0x16

/*
 * Config रेजिस्टर bits
 */

#घोषणा MAX6650_CFG_V12			0x08
#घोषणा MAX6650_CFG_PRESCALER_MASK	0x07
#घोषणा MAX6650_CFG_PRESCALER_2		0x01
#घोषणा MAX6650_CFG_PRESCALER_4		0x02
#घोषणा MAX6650_CFG_PRESCALER_8		0x03
#घोषणा MAX6650_CFG_PRESCALER_16	0x04
#घोषणा MAX6650_CFG_MODE_MASK		0x30
#घोषणा MAX6650_CFG_MODE_ON		0x00
#घोषणा MAX6650_CFG_MODE_OFF		0x10
#घोषणा MAX6650_CFG_MODE_CLOSED_LOOP	0x20
#घोषणा MAX6650_CFG_MODE_OPEN_LOOP	0x30
#घोषणा MAX6650_COUNT_MASK		0x03

/*
 * Alarm status रेजिस्टर bits
 */

#घोषणा MAX6650_ALRM_MAX	0x01
#घोषणा MAX6650_ALRM_MIN	0x02
#घोषणा MAX6650_ALRM_TACH	0x04
#घोषणा MAX6650_ALRM_GPIO1	0x08
#घोषणा MAX6650_ALRM_GPIO2	0x10

/* Minimum and maximum values of the FAN-RPM */
#घोषणा FAN_RPM_MIN 240
#घोषणा FAN_RPM_MAX 30000

#घोषणा DIV_FROM_REG(reg)	(1 << ((reg) & 7))
#घोषणा DAC_LIMIT(v12)		((v12) ? 180 : 76)

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा max6650_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock; /* protect alarm रेजिस्टर updates */
	पूर्णांक nr_fans;
	bool valid; /* false until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टर values */
	u8 speed;
	u8 config;
	u8 tach[4];
	u8 count;
	u8 dac;
	u8 alarm;
	u8 alarm_en;
	अचिन्हित दीर्घ cooling_dev_state;
पूर्ण;

अटल स्थिर u8 tach_reg[] = अणु
	MAX6650_REG_TACH0,
	MAX6650_REG_TACH1,
	MAX6650_REG_TACH2,
	MAX6650_REG_TACH3,
पूर्ण;

अटल स्थिर काष्ठा of_device_id __maybe_unused max6650_dt_match[] = अणु
	अणु
		.compatible = "maxim,max6650",
		.data = (व्योम *)1
	पूर्ण,
	अणु
		.compatible = "maxim,max6651",
		.data = (व्योम *)4
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max6650_dt_match);

अटल पूर्णांक dac_to_pwm(पूर्णांक dac, bool v12)
अणु
	/*
	 * Useful range क्रम dac is 0-180 क्रम 12V fans and 0-76 क्रम 5V fans.
	 * Lower DAC values mean higher speeds.
	 */
	वापस clamp_val(255 - (255 * dac) / DAC_LIMIT(v12), 0, 255);
पूर्ण

अटल u8 pwm_to_dac(अचिन्हित पूर्णांक pwm, bool v12)
अणु
	पूर्णांक limit = DAC_LIMIT(v12);

	वापस limit - (limit * pwm) / 255;
पूर्ण

अटल काष्ठा max6650_data *max6650_update_device(काष्ठा device *dev)
अणु
	काष्ठा max6650_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक reg, err = 0;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		क्रम (i = 0; i < data->nr_fans; i++) अणु
			reg = i2c_smbus_पढ़ो_byte_data(client, tach_reg[i]);
			अगर (reg < 0) अणु
				err = reg;
				जाओ error;
			पूर्ण
			data->tach[i] = reg;
		पूर्ण

		/*
		 * Alarms are cleared on पढ़ो in हाल the condition that
		 * caused the alarm is हटाओd. Keep the value latched here
		 * क्रम providing the रेजिस्टर through dअगरferent alarm files.
		 */
		reg = i2c_smbus_पढ़ो_byte_data(client, MAX6650_REG_ALARM);
		अगर (reg < 0) अणु
			err = reg;
			जाओ error;
		पूर्ण
		data->alarm |= reg;
		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण

error:
	mutex_unlock(&data->update_lock);
	अगर (err)
		data = ERR_PTR(err);
	वापस data;
पूर्ण

/*
 * Change the operating mode of the chip (अगर needed).
 * mode is one of the MAX6650_CFG_MODE_* values.
 */
अटल पूर्णांक max6650_set_operating_mode(काष्ठा max6650_data *data, u8 mode)
अणु
	पूर्णांक result;
	u8 config = data->config;

	अगर (mode == (config & MAX6650_CFG_MODE_MASK))
		वापस 0;

	config = (config & ~MAX6650_CFG_MODE_MASK) | mode;

	result = i2c_smbus_ग_लिखो_byte_data(data->client, MAX6650_REG_CONFIG,
					   config);
	अगर (result < 0)
		वापस result;

	data->config = config;

	वापस 0;
पूर्ण

/*
 * Set the fan speed to the specअगरied RPM (or पढ़ो back the RPM setting).
 * This works in बंदd loop mode only. Use pwm1 क्रम खोलो loop speed setting.
 *
 * The MAX6650/1 will स्वतःmatically control fan speed when in बंदd loop
 * mode.
 *
 * Assumptions:
 *
 * 1) The MAX6650/1 पूर्णांकernal 254kHz घड़ी frequency is set correctly. Use
 *    the घड़ी module parameter अगर you need to fine tune this.
 *
 * 2) The prescaler (low three bits of the config रेजिस्टर) has alपढ़ोy
 *    been set to an appropriate value. Use the prescaler module parameter
 *    अगर your BIOS करोesn't initialize the chip properly.
 *
 * The relevant equations are given on pages 21 and 22 of the datasheet.
 *
 * From the datasheet, the relevant equation when in regulation is:
 *
 *    [fCLK / (128 x (KTACH + 1))] = 2 x FanSpeed / KSCALE
 *
 * where:
 *
 *    fCLK is the oscillator frequency (either the 254kHz पूर्णांकernal
 *         oscillator or the बाह्यally applied घड़ी)
 *
 *    KTACH is the value in the speed रेजिस्टर
 *
 *    FanSpeed is the speed of the fan in rps
 *
 *    KSCALE is the prescaler value (1, 2, 4, 8, or 16)
 *
 * When पढ़ोing, we need to solve क्रम FanSpeed. When writing, we need to
 * solve क्रम KTACH.
 *
 * Note: this tachometer is completely separate from the tachometers
 * used to measure the fan speeds. Only one fan's speed (fan1) is
 * controlled.
 */

अटल पूर्णांक max6650_set_target(काष्ठा max6650_data *data, अचिन्हित दीर्घ rpm)
अणु
	पूर्णांक kscale, ktach;

	अगर (rpm == 0)
		वापस max6650_set_operating_mode(data, MAX6650_CFG_MODE_OFF);

	rpm = clamp_val(rpm, FAN_RPM_MIN, FAN_RPM_MAX);

	/*
	 * Divide the required speed by 60 to get from rpm to rps, then
	 * use the datasheet equation:
	 *
	 *     KTACH = [(fCLK x KSCALE) / (256 x FanSpeed)] - 1
	 */

	kscale = DIV_FROM_REG(data->config);
	ktach = ((घड़ी * kscale) / (256 * rpm / 60)) - 1;
	अगर (ktach < 0)
		ktach = 0;
	अगर (ktach > 255)
		ktach = 255;
	data->speed = ktach;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MAX6650_REG_SPEED,
					 data->speed);
पूर्ण

/*
 * Get gpio alarm status:
 * Possible values:
 * 0 = no alarm
 * 1 = alarm
 */

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा max6650_data *data = max6650_update_device(dev);
	bool alarm;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	alarm = data->alarm & attr->index;
	अगर (alarm) अणु
		mutex_lock(&data->update_lock);
		data->alarm &= ~attr->index;
		data->valid = false;
		mutex_unlock(&data->update_lock);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", alarm);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(gpio1_alarm, alarm, MAX6650_ALRM_GPIO1);
अटल SENSOR_DEVICE_ATTR_RO(gpio2_alarm, alarm, MAX6650_ALRM_GPIO2);

अटल umode_t max6650_attrs_visible(काष्ठा kobject *kobj, काष्ठा attribute *a,
				     पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा max6650_data *data = dev_get_drvdata(dev);
	काष्ठा device_attribute *devattr;

	/*
	 * Hide the alarms that have not been enabled by the firmware
	 */

	devattr = container_of(a, काष्ठा device_attribute, attr);
	अगर (devattr == &sensor_dev_attr_gpio1_alarm.dev_attr ||
	    devattr == &sensor_dev_attr_gpio2_alarm.dev_attr) अणु
		अगर (!(data->alarm_en & to_sensor_dev_attr(devattr)->index))
			वापस 0;
	पूर्ण

	वापस a->mode;
पूर्ण

अटल काष्ठा attribute *max6650_attrs[] = अणु
	&sensor_dev_attr_gpio1_alarm.dev_attr.attr,
	&sensor_dev_attr_gpio2_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group max6650_group = अणु
	.attrs = max6650_attrs,
	.is_visible = max6650_attrs_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *max6650_groups[] = अणु
	&max6650_group,
	शून्य
पूर्ण;

अटल पूर्णांक max6650_init_client(काष्ठा max6650_data *data,
			       काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक reg;
	पूर्णांक err;
	u32 voltage;
	u32 prescale;
	u32 target_rpm;

	अगर (of_property_पढ़ो_u32(dev->of_node, "maxim,fan-microvolt",
				 &voltage))
		voltage = fan_voltage;
	अन्यथा
		voltage /= 1000000; /* Microvolts to volts */
	अगर (of_property_पढ़ो_u32(dev->of_node, "maxim,fan-prescale",
				 &prescale))
		prescale = prescaler;

	reg = i2c_smbus_पढ़ो_byte_data(client, MAX6650_REG_CONFIG);
	अगर (reg < 0) अणु
		dev_err(dev, "Error reading config register, aborting.\n");
		वापस reg;
	पूर्ण

	चयन (voltage) अणु
	हाल 0:
		अवरोध;
	हाल 5:
		reg &= ~MAX6650_CFG_V12;
		अवरोध;
	हाल 12:
		reg |= MAX6650_CFG_V12;
		अवरोध;
	शेष:
		dev_err(dev, "illegal value for fan_voltage (%d)\n", voltage);
	पूर्ण

	चयन (prescale) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		reg &= ~MAX6650_CFG_PRESCALER_MASK;
		अवरोध;
	हाल 2:
		reg = (reg & ~MAX6650_CFG_PRESCALER_MASK)
			 | MAX6650_CFG_PRESCALER_2;
		अवरोध;
	हाल  4:
		reg = (reg & ~MAX6650_CFG_PRESCALER_MASK)
			 | MAX6650_CFG_PRESCALER_4;
		अवरोध;
	हाल  8:
		reg = (reg & ~MAX6650_CFG_PRESCALER_MASK)
			 | MAX6650_CFG_PRESCALER_8;
		अवरोध;
	हाल 16:
		reg = (reg & ~MAX6650_CFG_PRESCALER_MASK)
			 | MAX6650_CFG_PRESCALER_16;
		अवरोध;
	शेष:
		dev_err(dev, "illegal value for prescaler (%d)\n", prescale);
	पूर्ण

	dev_info(dev, "Fan voltage: %dV, prescaler: %d.\n",
		 (reg & MAX6650_CFG_V12) ? 12 : 5,
		 1 << (reg & MAX6650_CFG_PRESCALER_MASK));

	err = i2c_smbus_ग_लिखो_byte_data(client, MAX6650_REG_CONFIG, reg);
	अगर (err) अणु
		dev_err(dev, "Config write error, aborting.\n");
		वापस err;
	पूर्ण
	data->config = reg;

	reg = i2c_smbus_पढ़ो_byte_data(client, MAX6650_REG_SPEED);
	अगर (reg < 0) अणु
		dev_err(dev, "Failed to read speed register, aborting.\n");
		वापस reg;
	पूर्ण
	data->speed = reg;

	reg = i2c_smbus_पढ़ो_byte_data(client, MAX6650_REG_DAC);
	अगर (reg < 0) अणु
		dev_err(dev, "Failed to read DAC register, aborting.\n");
		वापस reg;
	पूर्ण
	data->dac = reg;

	reg = i2c_smbus_पढ़ो_byte_data(client, MAX6650_REG_COUNT);
	अगर (reg < 0) अणु
		dev_err(dev, "Failed to read count register, aborting.\n");
		वापस reg;
	पूर्ण
	data->count = reg;

	reg = i2c_smbus_पढ़ो_byte_data(client, MAX6650_REG_ALARM_EN);
	अगर (reg < 0) अणु
		dev_err(dev, "Failed to read alarm configuration, aborting.\n");
		वापस reg;
	पूर्ण
	data->alarm_en = reg;

	अगर (!of_property_पढ़ो_u32(client->dev.of_node, "maxim,fan-target-rpm",
				  &target_rpm)) अणु
		max6650_set_target(data, target_rpm);
		max6650_set_operating_mode(data, MAX6650_CFG_MODE_CLOSED_LOOP);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max6650_get_max_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	*state = 255;

	वापस 0;
पूर्ण

अटल पूर्णांक max6650_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	काष्ठा max6650_data *data = cdev->devdata;

	*state = data->cooling_dev_state;

	वापस 0;
पूर्ण

अटल पूर्णांक max6650_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ state)
अणु
	काष्ठा max6650_data *data = cdev->devdata;
	काष्ठा i2c_client *client = data->client;
	पूर्णांक err;

	state = clamp_val(state, 0, 255);

	mutex_lock(&data->update_lock);

	data->dac = pwm_to_dac(state, data->config & MAX6650_CFG_V12);
	err = i2c_smbus_ग_लिखो_byte_data(client, MAX6650_REG_DAC, data->dac);
	अगर (!err) अणु
		max6650_set_operating_mode(data, state ?
					   MAX6650_CFG_MODE_OPEN_LOOP :
					   MAX6650_CFG_MODE_OFF);
		data->cooling_dev_state = state;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops max6650_cooling_ops = अणु
	.get_max_state = max6650_get_max_state,
	.get_cur_state = max6650_get_cur_state,
	.set_cur_state = max6650_set_cur_state,
पूर्ण;

अटल पूर्णांक max6650_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा max6650_data *data = max6650_update_device(dev);
	पूर्णांक mode;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	चयन (type) अणु
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
			*val = dac_to_pwm(data->dac,
					  data->config & MAX6650_CFG_V12);
			अवरोध;
		हाल hwmon_pwm_enable:
			/*
			 * Possible values:
			 * 0 = Fan always on
			 * 1 = Open loop, Voltage is set according to speed,
			 *     not regulated.
			 * 2 = Closed loop, RPM क्रम all fans regulated by fan1
			 *     tachometer
			 * 3 = Fan off
			 */
			mode = (data->config & MAX6650_CFG_MODE_MASK) >> 4;
			*val = (4 - mode) & 3; /* अणु0 1 2 3पूर्ण -> अणु0 3 2 1पूर्ण */
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_input:
			/*
			 * Calculation details:
			 *
			 * Each tachometer counts over an पूर्णांकerval given by the
			 * "count" रेजिस्टर (0.25, 0.5, 1 or 2 seconds).
			 * The driver assumes that the fans produce two pulses
			 * per revolution (this seems to be the most common).
			 */
			*val = DIV_ROUND_CLOSEST(data->tach[channel] * 120,
						 DIV_FROM_REG(data->count));
			अवरोध;
		हाल hwmon_fan_भाग:
			*val = DIV_FROM_REG(data->count);
			अवरोध;
		हाल hwmon_fan_target:
			/*
			 * Use the datasheet equation:
			 *    FanSpeed = KSCALE x fCLK / [256 x (KTACH + 1)]
			 * then multiply by 60 to give rpm.
			 */
			*val = 60 * DIV_FROM_REG(data->config) * घड़ी /
				(256 * (data->speed + 1));
			अवरोध;
		हाल hwmon_fan_min_alarm:
			*val = !!(data->alarm & MAX6650_ALRM_MIN);
			data->alarm &= ~MAX6650_ALRM_MIN;
			data->valid = false;
			अवरोध;
		हाल hwmon_fan_max_alarm:
			*val = !!(data->alarm & MAX6650_ALRM_MAX);
			data->alarm &= ~MAX6650_ALRM_MAX;
			data->valid = false;
			अवरोध;
		हाल hwmon_fan_fault:
			*val = !!(data->alarm & MAX6650_ALRM_TACH);
			data->alarm &= ~MAX6650_ALRM_TACH;
			data->valid = false;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर u8 max6650_pwm_modes[] = अणु
	MAX6650_CFG_MODE_ON,
	MAX6650_CFG_MODE_OPEN_LOOP,
	MAX6650_CFG_MODE_CLOSED_LOOP,
	MAX6650_CFG_MODE_OFF,
पूर्ण;

अटल पूर्णांक max6650_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा max6650_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	u8 reg;

	mutex_lock(&data->update_lock);

	चयन (type) अणु
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
			reg = pwm_to_dac(clamp_val(val, 0, 255),
					 data->config & MAX6650_CFG_V12);
			ret = i2c_smbus_ग_लिखो_byte_data(data->client,
							MAX6650_REG_DAC, reg);
			अगर (ret)
				अवरोध;
			data->dac = reg;
			अवरोध;
		हाल hwmon_pwm_enable:
			अगर (val < 0 || val >= ARRAY_SIZE(max6650_pwm_modes)) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			ret = max6650_set_operating_mode(data,
						max6650_pwm_modes[val]);
			अवरोध;
		शेष:
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_भाग:
			चयन (val) अणु
			हाल 1:
				reg = 0;
				अवरोध;
			हाल 2:
				reg = 1;
				अवरोध;
			हाल 4:
				reg = 2;
				अवरोध;
			हाल 8:
				reg = 3;
				अवरोध;
			शेष:
				ret = -EINVAL;
				जाओ error;
			पूर्ण
			ret = i2c_smbus_ग_लिखो_byte_data(data->client,
							MAX6650_REG_COUNT, reg);
			अगर (ret)
				अवरोध;
			data->count = reg;
			अवरोध;
		हाल hwmon_fan_target:
			अगर (val < 0) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			ret = max6650_set_target(data, val);
			अवरोध;
		शेष:
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

error:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल umode_t max6650_is_visible(स्थिर व्योम *_data,
				  क्रमागत hwmon_sensor_types type, u32 attr,
				  पूर्णांक channel)
अणु
	स्थिर काष्ठा max6650_data *data = _data;

	अगर (channel && (channel >= data->nr_fans || type != hwmon_fan))
		वापस 0;

	चयन (type) अणु
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_input:
			वापस 0444;
		हाल hwmon_fan_target:
		हाल hwmon_fan_भाग:
			वापस 0644;
		हाल hwmon_fan_min_alarm:
			अगर (data->alarm_en & MAX6650_ALRM_MIN)
				वापस 0444;
			अवरोध;
		हाल hwmon_fan_max_alarm:
			अगर (data->alarm_en & MAX6650_ALRM_MAX)
				वापस 0444;
			अवरोध;
		हाल hwmon_fan_fault:
			अगर (data->alarm_en & MAX6650_ALRM_TACH)
				वापस 0444;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
		हाल hwmon_pwm_enable:
			वापस 0644;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *max6650_info[] = अणु
	HWMON_CHANNEL_INFO(fan, HWMON_F_INPUT | HWMON_F_TARGET | HWMON_F_DIV |
			   HWMON_F_MIN_ALARM | HWMON_F_MAX_ALARM |
			   HWMON_F_FAULT,
			   HWMON_F_INPUT, HWMON_F_INPUT, HWMON_F_INPUT),
	HWMON_CHANNEL_INFO(pwm, HWMON_PWM_INPUT | HWMON_PWM_ENABLE),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops max6650_hwmon_ops = अणु
	.पढ़ो = max6650_पढ़ो,
	.ग_लिखो = max6650_ग_लिखो,
	.is_visible = max6650_is_visible,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info max6650_chip_info = अणु
	.ops = &max6650_hwmon_ops,
	.info = max6650_info,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id max6650_id[];

अटल पूर्णांक max6650_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा thermal_cooling_device *cooling_dev;
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा of_device_id *of_id =
		of_match_device(of_match_ptr(max6650_dt_match), dev);
	काष्ठा max6650_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा max6650_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->nr_fans = of_id ? (पूर्णांक)(uपूर्णांकptr_t)of_id->data :
				i2c_match_id(max6650_id, client)->driver_data;

	/*
	 * Initialize the max6650 chip
	 */
	err = max6650_init_client(data, client);
	अगर (err)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev,
							 client->name, data,
							 &max6650_chip_info,
							 max6650_groups);
	err = PTR_ERR_OR_ZERO(hwmon_dev);
	अगर (err)
		वापस err;

	अगर (IS_ENABLED(CONFIG_THERMAL)) अणु
		cooling_dev = devm_thermal_of_cooling_device_रेजिस्टर(dev,
						dev->of_node, client->name,
						data, &max6650_cooling_ops);
		अगर (IS_ERR(cooling_dev)) अणु
			dev_warn(dev, "thermal cooling device register failed: %ld\n",
				 PTR_ERR(cooling_dev));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max6650_id[] = अणु
	अणु "max6650", 1 पूर्ण,
	अणु "max6651", 4 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max6650_id);

अटल काष्ठा i2c_driver max6650_driver = अणु
	.driver = अणु
		.name	= "max6650",
		.of_match_table = of_match_ptr(max6650_dt_match),
	पूर्ण,
	.probe_new	= max6650_probe,
	.id_table	= max6650_id,
पूर्ण;

module_i2c_driver(max6650_driver);

MODULE_AUTHOR("Hans J. Koch");
MODULE_DESCRIPTION("MAX6650 sensor driver");
MODULE_LICENSE("GPL");
