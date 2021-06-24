<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * amc6821.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 * Copyright (C) 2009 T. Mertelj <tomaz.mertelj@guest.arnes.si>
 *
 * Based on max6650.c:
 * Copyright (C) 2007 Hans J. Koch <hjk@hansjkoch.de>
 */

#समावेश <linux/kernel.h>	/* Needed क्रम KERN_INFO */
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
 * Addresses to scan.
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु0x18, 0x19, 0x1a, 0x2c, 0x2d, 0x2e,
	0x4c, 0x4d, 0x4e, I2C_CLIENT_ENDपूर्ण;

/*
 * Insmod parameters
 */

अटल पूर्णांक pwminv;	/*Inverted PWM output. */
module_param(pwminv, पूर्णांक, 0444);

अटल पूर्णांक init = 1; /*Power-on initialization.*/
module_param(init, पूर्णांक, 0444);

क्रमागत chips अणु amc6821 पूर्ण;

#घोषणा AMC6821_REG_DEV_ID 0x3D
#घोषणा AMC6821_REG_COMP_ID 0x3E
#घोषणा AMC6821_REG_CONF1 0x00
#घोषणा AMC6821_REG_CONF2 0x01
#घोषणा AMC6821_REG_CONF3 0x3F
#घोषणा AMC6821_REG_CONF4 0x04
#घोषणा AMC6821_REG_STAT1 0x02
#घोषणा AMC6821_REG_STAT2 0x03
#घोषणा AMC6821_REG_TDATA_LOW 0x08
#घोषणा AMC6821_REG_TDATA_HI 0x09
#घोषणा AMC6821_REG_LTEMP_HI 0x0A
#घोषणा AMC6821_REG_RTEMP_HI 0x0B
#घोषणा AMC6821_REG_LTEMP_LIMIT_MIN 0x15
#घोषणा AMC6821_REG_LTEMP_LIMIT_MAX 0x14
#घोषणा AMC6821_REG_RTEMP_LIMIT_MIN 0x19
#घोषणा AMC6821_REG_RTEMP_LIMIT_MAX 0x18
#घोषणा AMC6821_REG_LTEMP_CRIT 0x1B
#घोषणा AMC6821_REG_RTEMP_CRIT 0x1D
#घोषणा AMC6821_REG_PSV_TEMP 0x1C
#घोषणा AMC6821_REG_DCY 0x22
#घोषणा AMC6821_REG_LTEMP_FAN_CTRL 0x24
#घोषणा AMC6821_REG_RTEMP_FAN_CTRL 0x25
#घोषणा AMC6821_REG_DCY_LOW_TEMP 0x21

#घोषणा AMC6821_REG_TACH_LLIMITL 0x10
#घोषणा AMC6821_REG_TACH_LLIMITH 0x11
#घोषणा AMC6821_REG_TACH_HLIMITL 0x12
#घोषणा AMC6821_REG_TACH_HLIMITH 0x13

#घोषणा AMC6821_CONF1_START 0x01
#घोषणा AMC6821_CONF1_FAN_INT_EN 0x02
#घोषणा AMC6821_CONF1_FANIE 0x04
#घोषणा AMC6821_CONF1_PWMINV 0x08
#घोषणा AMC6821_CONF1_FAN_FAULT_EN 0x10
#घोषणा AMC6821_CONF1_FDRC0 0x20
#घोषणा AMC6821_CONF1_FDRC1 0x40
#घोषणा AMC6821_CONF1_THERMOVIE 0x80

#घोषणा AMC6821_CONF2_PWM_EN 0x01
#घोषणा AMC6821_CONF2_TACH_MODE 0x02
#घोषणा AMC6821_CONF2_TACH_EN 0x04
#घोषणा AMC6821_CONF2_RTFIE 0x08
#घोषणा AMC6821_CONF2_LTOIE 0x10
#घोषणा AMC6821_CONF2_RTOIE 0x20
#घोषणा AMC6821_CONF2_PSVIE 0x40
#घोषणा AMC6821_CONF2_RST 0x80

#घोषणा AMC6821_CONF3_THERM_FAN_EN 0x80
#घोषणा AMC6821_CONF3_REV_MASK 0x0F

#घोषणा AMC6821_CONF4_OVREN 0x10
#घोषणा AMC6821_CONF4_TACH_FAST 0x20
#घोषणा AMC6821_CONF4_PSPR 0x40
#घोषणा AMC6821_CONF4_MODE 0x80

#घोषणा AMC6821_STAT1_RPM_ALARM 0x01
#घोषणा AMC6821_STAT1_FANS 0x02
#घोषणा AMC6821_STAT1_RTH 0x04
#घोषणा AMC6821_STAT1_RTL 0x08
#घोषणा AMC6821_STAT1_R_THERM 0x10
#घोषणा AMC6821_STAT1_RTF 0x20
#घोषणा AMC6821_STAT1_LTH 0x40
#घोषणा AMC6821_STAT1_LTL 0x80

#घोषणा AMC6821_STAT2_RTC 0x08
#घोषणा AMC6821_STAT2_LTC 0x10
#घोषणा AMC6821_STAT2_LPSV 0x20
#घोषणा AMC6821_STAT2_L_THERM 0x40
#घोषणा AMC6821_STAT2_THERM_IN 0x80

क्रमागत अणुIDX_TEMP1_INPUT = 0, IDX_TEMP1_MIN, IDX_TEMP1_MAX,
	IDX_TEMP1_CRIT, IDX_TEMP2_INPUT, IDX_TEMP2_MIN,
	IDX_TEMP2_MAX, IDX_TEMP2_CRIT,
	TEMP_IDX_LEN, पूर्ण;

अटल स्थिर u8 temp_reg[] = अणुAMC6821_REG_LTEMP_HI,
			AMC6821_REG_LTEMP_LIMIT_MIN,
			AMC6821_REG_LTEMP_LIMIT_MAX,
			AMC6821_REG_LTEMP_CRIT,
			AMC6821_REG_RTEMP_HI,
			AMC6821_REG_RTEMP_LIMIT_MIN,
			AMC6821_REG_RTEMP_LIMIT_MAX,
			AMC6821_REG_RTEMP_CRIT, पूर्ण;

क्रमागत अणुIDX_FAN1_INPUT = 0, IDX_FAN1_MIN, IDX_FAN1_MAX,
	FAN1_IDX_LEN, पूर्ण;

अटल स्थिर u8 fan_reg_low[] = अणुAMC6821_REG_TDATA_LOW,
			AMC6821_REG_TACH_LLIMITL,
			AMC6821_REG_TACH_HLIMITL, पूर्ण;


अटल स्थिर u8 fan_reg_hi[] = अणुAMC6821_REG_TDATA_HI,
			AMC6821_REG_TACH_LLIMITH,
			AMC6821_REG_TACH_HLIMITH, पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा amc6821_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टर values */
	पूर्णांक temp[TEMP_IDX_LEN];

	u16 fan[FAN1_IDX_LEN];
	u8 fan1_भाग;

	u8 pwm1;
	u8 temp1_स्वतः_poपूर्णांक_temp[3];
	u8 temp2_स्वतः_poपूर्णांक_temp[3];
	u8 pwm1_स्वतः_poपूर्णांक_pwm[3];
	u8 pwm1_enable;
	u8 pwm1_स्वतः_channels_temp;

	u8 stat1;
	u8 stat2;
पूर्ण;

अटल काष्ठा amc6821_data *amc6821_update_device(काष्ठा device *dev)
अणु
	काष्ठा amc6821_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक समयout = HZ;
	u8 reg;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + समयout) ||
			!data->valid) अणु

		क्रम (i = 0; i < TEMP_IDX_LEN; i++)
			data->temp[i] = (पूर्णांक8_t)i2c_smbus_पढ़ो_byte_data(
				client, temp_reg[i]);

		data->stat1 = i2c_smbus_पढ़ो_byte_data(client,
			AMC6821_REG_STAT1);
		data->stat2 = i2c_smbus_पढ़ो_byte_data(client,
			AMC6821_REG_STAT2);

		data->pwm1 = i2c_smbus_पढ़ो_byte_data(client,
			AMC6821_REG_DCY);
		क्रम (i = 0; i < FAN1_IDX_LEN; i++) अणु
			data->fan[i] = i2c_smbus_पढ़ो_byte_data(
					client,
					fan_reg_low[i]);
			data->fan[i] += i2c_smbus_पढ़ो_byte_data(
					client,
					fan_reg_hi[i]) << 8;
		पूर्ण
		data->fan1_भाग = i2c_smbus_पढ़ो_byte_data(client,
			AMC6821_REG_CONF4);
		data->fan1_भाग = data->fan1_भाग & AMC6821_CONF4_PSPR ? 4 : 2;

		data->pwm1_स्वतः_poपूर्णांक_pwm[0] = 0;
		data->pwm1_स्वतः_poपूर्णांक_pwm[2] = 255;
		data->pwm1_स्वतः_poपूर्णांक_pwm[1] = i2c_smbus_पढ़ो_byte_data(client,
			AMC6821_REG_DCY_LOW_TEMP);

		data->temp1_स्वतः_poपूर्णांक_temp[0] =
			i2c_smbus_पढ़ो_byte_data(client,
					AMC6821_REG_PSV_TEMP);
		data->temp2_स्वतः_poपूर्णांक_temp[0] =
				data->temp1_स्वतः_poपूर्णांक_temp[0];
		reg = i2c_smbus_पढ़ो_byte_data(client,
			AMC6821_REG_LTEMP_FAN_CTRL);
		data->temp1_स्वतः_poपूर्णांक_temp[1] = (reg & 0xF8) >> 1;
		reg &= 0x07;
		reg = 0x20 >> reg;
		अगर (reg > 0)
			data->temp1_स्वतः_poपूर्णांक_temp[2] =
				data->temp1_स्वतः_poपूर्णांक_temp[1] +
				(data->pwm1_स्वतः_poपूर्णांक_pwm[2] -
				data->pwm1_स्वतः_poपूर्णांक_pwm[1]) / reg;
		अन्यथा
			data->temp1_स्वतः_poपूर्णांक_temp[2] = 255;

		reg = i2c_smbus_पढ़ो_byte_data(client,
			AMC6821_REG_RTEMP_FAN_CTRL);
		data->temp2_स्वतः_poपूर्णांक_temp[1] = (reg & 0xF8) >> 1;
		reg &= 0x07;
		reg = 0x20 >> reg;
		अगर (reg > 0)
			data->temp2_स्वतः_poपूर्णांक_temp[2] =
				data->temp2_स्वतः_poपूर्णांक_temp[1] +
				(data->pwm1_स्वतः_poपूर्णांक_pwm[2] -
				data->pwm1_स्वतः_poपूर्णांक_pwm[1]) / reg;
		अन्यथा
			data->temp2_स्वतः_poपूर्णांक_temp[2] = 255;

		reg = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_CONF1);
		reg = (reg >> 5) & 0x3;
		चयन (reg) अणु
		हाल 0: /*खोलो loop: software sets pwm1*/
			data->pwm1_स्वतः_channels_temp = 0;
			data->pwm1_enable = 1;
			अवरोध;
		हाल 2: /*बंदd loop: remote T (temp2)*/
			data->pwm1_स्वतः_channels_temp = 2;
			data->pwm1_enable = 2;
			अवरोध;
		हाल 3: /*बंदd loop: local and remote T (temp2)*/
			data->pwm1_स्वतः_channels_temp = 3;
			data->pwm1_enable = 3;
			अवरोध;
		हाल 1: /*
			 * semi-खोलो loop: software sets rpm, chip controls
			 * pwm1, currently not implemented
			 */
			data->pwm1_स्वतः_channels_temp = 0;
			data->pwm1_enable = 0;
			अवरोध;
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	पूर्णांक ix = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", data->temp[ix] * 1000);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amc6821_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ix = to_sensor_dev_attr(attr)->index;
	दीर्घ val;

	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;
	val = clamp_val(val / 1000, -128, 127);

	mutex_lock(&data->update_lock);
	data->temp[ix] = val;
	अगर (i2c_smbus_ग_लिखो_byte_data(client, temp_reg[ix], data->temp[ix])) अणु
		dev_err(&client->dev, "Register write error, aborting.\n");
		count = -EIO;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_alarm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	पूर्णांक ix = to_sensor_dev_attr(devattr)->index;
	u8 flag;

	चयन (ix) अणु
	हाल IDX_TEMP1_MIN:
		flag = data->stat1 & AMC6821_STAT1_LTL;
		अवरोध;
	हाल IDX_TEMP1_MAX:
		flag = data->stat1 & AMC6821_STAT1_LTH;
		अवरोध;
	हाल IDX_TEMP1_CRIT:
		flag = data->stat2 & AMC6821_STAT2_LTC;
		अवरोध;
	हाल IDX_TEMP2_MIN:
		flag = data->stat1 & AMC6821_STAT1_RTL;
		अवरोध;
	हाल IDX_TEMP2_MAX:
		flag = data->stat1 & AMC6821_STAT1_RTH;
		अवरोध;
	हाल IDX_TEMP2_CRIT:
		flag = data->stat2 & AMC6821_STAT2_RTC;
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown attr->index (%d).\n", ix);
		वापस -EINVAL;
	पूर्ण
	अगर (flag)
		वापस प्र_लिखो(buf, "1");
	अन्यथा
		वापस प्र_लिखो(buf, "0");
पूर्ण

अटल sमाप_प्रकार temp2_fault_show(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	अगर (data->stat1 & AMC6821_STAT1_RTF)
		वापस प्र_लिखो(buf, "1");
	अन्यथा
		वापस प्र_लिखो(buf, "0");
पूर्ण

अटल sमाप_प्रकार pwm1_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm1);
पूर्ण

अटल sमाप_प्रकार pwm1_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा amc6821_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->update_lock);
	data->pwm1 = clamp_val(val , 0, 255);
	i2c_smbus_ग_लिखो_byte_data(client, AMC6821_REG_DCY, data->pwm1);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm1_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm1_enable);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amc6821_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक config = kम_से_दीर्घ(buf, 10, &val);
	अगर (config)
		वापस config;

	mutex_lock(&data->update_lock);
	config = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_CONF1);
	अगर (config < 0) अणु
			dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
			count = config;
			जाओ unlock;
	पूर्ण

	चयन (val) अणु
	हाल 1:
		config &= ~AMC6821_CONF1_FDRC0;
		config &= ~AMC6821_CONF1_FDRC1;
		अवरोध;
	हाल 2:
		config &= ~AMC6821_CONF1_FDRC0;
		config |= AMC6821_CONF1_FDRC1;
		अवरोध;
	हाल 3:
		config |= AMC6821_CONF1_FDRC0;
		config |= AMC6821_CONF1_FDRC1;
		अवरोध;
	शेष:
		count = -EINVAL;
		जाओ unlock;
	पूर्ण
	अगर (i2c_smbus_ग_लिखो_byte_data(client, AMC6821_REG_CONF1, config)) अणु
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			count = -EIO;
	पूर्ण
unlock:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm1_स्वतः_channels_temp_show(काष्ठा device *dev,
					    काष्ठा device_attribute *devattr,
					    अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm1_स्वतः_channels_temp);
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_poपूर्णांक_temp_show(काष्ठा device *dev,
					 काष्ठा device_attribute *devattr,
					 अक्षर *buf)
अणु
	पूर्णांक ix = to_sensor_dev_attr_2(devattr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	चयन (nr) अणु
	हाल 1:
		वापस प्र_लिखो(buf, "%d\n",
			data->temp1_स्वतः_poपूर्णांक_temp[ix] * 1000);
	हाल 2:
		वापस प्र_लिखो(buf, "%d\n",
			data->temp2_स्वतः_poपूर्णांक_temp[ix] * 1000);
	शेष:
		dev_dbg(dev, "Unknown attr->nr (%d).\n", nr);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार pwm1_स्वतः_poपूर्णांक_pwm_show(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	पूर्णांक ix = to_sensor_dev_attr(devattr)->index;
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm1_स्वतः_poपूर्णांक_pwm[ix]);
पूर्ण

अटल अंतरभूत sमाप_प्रकार set_slope_रेजिस्टर(काष्ठा i2c_client *client,
		u8 reg,
		u8 dpwm,
		u8 *ptemp)
अणु
	पूर्णांक dt;
	u8 पंचांगp;

	dt = ptemp[2]-ptemp[1];
	क्रम (पंचांगp = 4; पंचांगp > 0; पंचांगp--) अणु
		अगर (dt * (0x20 >> पंचांगp) >= dpwm)
			अवरोध;
	पूर्ण
	पंचांगp |= (ptemp[1] & 0x7C) << 1;
	अगर (i2c_smbus_ग_लिखो_byte_data(client,
			reg, पंचांगp)) अणु
		dev_err(&client->dev, "Register write error, aborting.\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_poपूर्णांक_temp_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ix = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;
	u8 *ptemp;
	u8 reg;
	पूर्णांक dpwm;
	दीर्घ val;
	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	चयन (nr) अणु
	हाल 1:
		ptemp = data->temp1_स्वतः_poपूर्णांक_temp;
		reg = AMC6821_REG_LTEMP_FAN_CTRL;
		अवरोध;
	हाल 2:
		ptemp = data->temp2_स्वतः_poपूर्णांक_temp;
		reg = AMC6821_REG_RTEMP_FAN_CTRL;
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown attr->nr (%d).\n", nr);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->valid = 0;

	चयन (ix) अणु
	हाल 0:
		ptemp[0] = clamp_val(val / 1000, 0,
				     data->temp1_स्वतः_poपूर्णांक_temp[1]);
		ptemp[0] = clamp_val(ptemp[0], 0,
				     data->temp2_स्वतः_poपूर्णांक_temp[1]);
		ptemp[0] = clamp_val(ptemp[0], 0, 63);
		अगर (i2c_smbus_ग_लिखो_byte_data(
					client,
					AMC6821_REG_PSV_TEMP,
					ptemp[0])) अणु
				dev_err(&client->dev,
					"Register write error, aborting.\n");
				count = -EIO;
		पूर्ण
		जाओ EXIT;
	हाल 1:
		ptemp[1] = clamp_val(val / 1000, (ptemp[0] & 0x7C) + 4, 124);
		ptemp[1] &= 0x7C;
		ptemp[2] = clamp_val(ptemp[2], ptemp[1] + 1, 255);
		अवरोध;
	हाल 2:
		ptemp[2] = clamp_val(val / 1000, ptemp[1]+1, 255);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown attr->index (%d).\n", ix);
		count = -EINVAL;
		जाओ EXIT;
	पूर्ण
	dpwm = data->pwm1_स्वतः_poपूर्णांक_pwm[2] - data->pwm1_स्वतः_poपूर्णांक_pwm[1];
	अगर (set_slope_रेजिस्टर(client, reg, dpwm, ptemp))
		count = -EIO;

EXIT:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm1_स्वतः_poपूर्णांक_pwm_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amc6821_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक dpwm;
	दीर्घ val;
	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->update_lock);
	data->pwm1_स्वतः_poपूर्णांक_pwm[1] = clamp_val(val, 0, 254);
	अगर (i2c_smbus_ग_लिखो_byte_data(client, AMC6821_REG_DCY_LOW_TEMP,
			data->pwm1_स्वतः_poपूर्णांक_pwm[1])) अणु
		dev_err(&client->dev, "Register write error, aborting.\n");
		count = -EIO;
		जाओ EXIT;
	पूर्ण
	dpwm = data->pwm1_स्वतः_poपूर्णांक_pwm[2] - data->pwm1_स्वतः_poपूर्णांक_pwm[1];
	अगर (set_slope_रेजिस्टर(client, AMC6821_REG_LTEMP_FAN_CTRL, dpwm,
			data->temp1_स्वतः_poपूर्णांक_temp)) अणु
		count = -EIO;
		जाओ EXIT;
	पूर्ण
	अगर (set_slope_रेजिस्टर(client, AMC6821_REG_RTEMP_FAN_CTRL, dpwm,
			data->temp2_स्वतः_poपूर्णांक_temp)) अणु
		count = -EIO;
		जाओ EXIT;
	पूर्ण

EXIT:
	data->valid = 0;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	पूर्णांक ix = to_sensor_dev_attr(devattr)->index;
	अगर (0 == data->fan[ix])
		वापस प्र_लिखो(buf, "0");
	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)(6000000 / data->fan[ix]));
पूर्ण

अटल sमाप_प्रकार fan1_fault_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	अगर (data->stat1 & AMC6821_STAT1_FANS)
		वापस प्र_लिखो(buf, "1");
	अन्यथा
		वापस प्र_लिखो(buf, "0");
पूर्ण

अटल sमाप_प्रकार fan_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amc6821_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक ix = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;
	val = 1 > val ? 0xFFFF : 6000000/val;

	mutex_lock(&data->update_lock);
	data->fan[ix] = (u16) clamp_val(val, 1, 0xFFFF);
	अगर (i2c_smbus_ग_लिखो_byte_data(client, fan_reg_low[ix],
			data->fan[ix] & 0xFF)) अणु
		dev_err(&client->dev, "Register write error, aborting.\n");
		count = -EIO;
		जाओ EXIT;
	पूर्ण
	अगर (i2c_smbus_ग_लिखो_byte_data(client,
			fan_reg_hi[ix], data->fan[ix] >> 8)) अणु
		dev_err(&client->dev, "Register write error, aborting.\n");
		count = -EIO;
	पूर्ण
EXIT:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan1_भाग_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा amc6821_data *data = amc6821_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->fan1_भाग);
पूर्ण

अटल sमाप_प्रकार fan1_भाग_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा amc6821_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक config = kम_से_दीर्घ(buf, 10, &val);
	अगर (config)
		वापस config;

	mutex_lock(&data->update_lock);
	config = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_CONF4);
	अगर (config < 0) अणु
		dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
		count = config;
		जाओ EXIT;
	पूर्ण
	चयन (val) अणु
	हाल 2:
		config &= ~AMC6821_CONF4_PSPR;
		data->fan1_भाग = 2;
		अवरोध;
	हाल 4:
		config |= AMC6821_CONF4_PSPR;
		data->fan1_भाग = 4;
		अवरोध;
	शेष:
		count = -EINVAL;
		जाओ EXIT;
	पूर्ण
	अगर (i2c_smbus_ग_लिखो_byte_data(client, AMC6821_REG_CONF4, config)) अणु
		dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
		count = -EIO;
	पूर्ण
EXIT:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, IDX_TEMP1_INPUT);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp, IDX_TEMP1_MIN);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, IDX_TEMP1_MAX);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp, IDX_TEMP1_CRIT);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, temp_alarm, IDX_TEMP1_MIN);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, temp_alarm, IDX_TEMP1_MAX);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, temp_alarm, IDX_TEMP1_CRIT);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, IDX_TEMP2_INPUT);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp, IDX_TEMP2_MIN);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp, IDX_TEMP2_MAX);
अटल SENSOR_DEVICE_ATTR_RW(temp2_crit, temp, IDX_TEMP2_CRIT);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, temp2_fault, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min_alarm, temp_alarm, IDX_TEMP2_MIN);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, temp_alarm, IDX_TEMP2_MAX);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, temp_alarm, IDX_TEMP2_CRIT);
अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, IDX_FAN1_INPUT);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan, IDX_FAN1_MIN);
अटल SENSOR_DEVICE_ATTR_RW(fan1_max, fan, IDX_FAN1_MAX);
अटल SENSOR_DEVICE_ATTR_RO(fan1_fault, fan1_fault, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan1_भाग, 0);

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm1, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm1_enable, 0);
अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक1_pwm, pwm1_स्वतः_poपूर्णांक_pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक2_pwm, pwm1_स्वतः_poपूर्णांक_pwm, 1);
अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक3_pwm, pwm1_स्वतः_poपूर्णांक_pwm, 2);
अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_channels_temp, pwm1_स्वतः_channels_temp,
			     0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_स्वतः_poपूर्णांक1_temp, temp_स्वतः_poपूर्णांक_temp,
			       1, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_poपूर्णांक2_temp, temp_स्वतः_poपूर्णांक_temp,
			       1, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_poपूर्णांक3_temp, temp_स्वतः_poपूर्णांक_temp,
			       1, 2);

अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_poपूर्णांक1_temp, temp_स्वतः_poपूर्णांक_temp,
			       2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_poपूर्णांक2_temp, temp_स्वतः_poपूर्णांक_temp,
			       2, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_poपूर्णांक3_temp, temp_स्वतः_poपूर्णांक_temp,
			       2, 2);

अटल काष्ठा attribute *amc6821_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_max.dev_attr.attr,
	&sensor_dev_attr_fan1_fault.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(amc6821);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक amc6821_detect(
		काष्ठा i2c_client *client,
		काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक address = client->addr;
	पूर्णांक dev_id, comp_id;

	dev_dbg(&adapter->dev, "amc6821_detect called.\n");

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_dbg(&adapter->dev,
			"amc6821: I2C bus doesn't support byte mode, "
			"skipping.\n");
		वापस -ENODEV;
	पूर्ण

	dev_id = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_DEV_ID);
	comp_id = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_COMP_ID);
	अगर (dev_id != 0x21 || comp_id != 0x49) अणु
		dev_dbg(&adapter->dev,
			"amc6821: detection failed at 0x%02x.\n",
			address);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Bit 7 of the address रेजिस्टर is ignored, so we can check the
	 * ID रेजिस्टरs again
	 */
	dev_id = i2c_smbus_पढ़ो_byte_data(client, 0x80 | AMC6821_REG_DEV_ID);
	comp_id = i2c_smbus_पढ़ो_byte_data(client, 0x80 | AMC6821_REG_COMP_ID);
	अगर (dev_id != 0x21 || comp_id != 0x49) अणु
		dev_dbg(&adapter->dev,
			"amc6821: detection failed at 0x%02x.\n",
			address);
		वापस -ENODEV;
	पूर्ण

	dev_info(&adapter->dev, "amc6821: chip found at 0x%02x.\n", address);
	strlcpy(info->type, "amc6821", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक amc6821_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक config;
	पूर्णांक err = -EIO;

	अगर (init) अणु
		config = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_CONF4);

		अगर (config < 0) अणु
				dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
				वापस err;
		पूर्ण

		config |= AMC6821_CONF4_MODE;

		अगर (i2c_smbus_ग_लिखो_byte_data(client, AMC6821_REG_CONF4,
				config)) अणु
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			वापस err;
		पूर्ण

		config = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_CONF3);

		अगर (config < 0) अणु
			dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
			वापस err;
		पूर्ण

		dev_info(&client->dev, "Revision %d\n", config & 0x0f);

		config &= ~AMC6821_CONF3_THERM_FAN_EN;

		अगर (i2c_smbus_ग_लिखो_byte_data(client, AMC6821_REG_CONF3,
				config)) अणु
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			वापस err;
		पूर्ण

		config = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_CONF2);

		अगर (config < 0) अणु
			dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
			वापस err;
		पूर्ण

		config &= ~AMC6821_CONF2_RTFIE;
		config &= ~AMC6821_CONF2_LTOIE;
		config &= ~AMC6821_CONF2_RTOIE;
		अगर (i2c_smbus_ग_लिखो_byte_data(client,
				AMC6821_REG_CONF2, config)) अणु
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			वापस err;
		पूर्ण

		config = i2c_smbus_पढ़ो_byte_data(client, AMC6821_REG_CONF1);

		अगर (config < 0) अणु
			dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
			वापस err;
		पूर्ण

		config &= ~AMC6821_CONF1_THERMOVIE;
		config &= ~AMC6821_CONF1_FANIE;
		config |= AMC6821_CONF1_START;
		अगर (pwminv)
			config |= AMC6821_CONF1_PWMINV;
		अन्यथा
			config &= ~AMC6821_CONF1_PWMINV;

		अगर (i2c_smbus_ग_लिखो_byte_data(
				client, AMC6821_REG_CONF1, config)) अणु
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amc6821_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा amc6821_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा amc6821_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/*
	 * Initialize the amc6821 chip
	 */
	err = amc6821_init_client(client);
	अगर (err)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   amc6821_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id amc6821_id[] = अणु
	अणु "amc6821", amc6821 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, amc6821_id);

अटल काष्ठा i2c_driver amc6821_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "amc6821",
	पूर्ण,
	.probe_new = amc6821_probe,
	.id_table = amc6821_id,
	.detect = amc6821_detect,
	.address_list = normal_i2c,
पूर्ण;

module_i2c_driver(amc6821_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("T. Mertelj <tomaz.mertelj@guest.arnes.si>");
MODULE_DESCRIPTION("Texas Instruments amc6821 hwmon driver");
