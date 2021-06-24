<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm63.c - driver क्रम the National Semiconductor LM63 temperature sensor
 *          with पूर्णांकegrated fan control
 * Copyright (C) 2004-2008  Jean Delvare <jdelvare@suse.de>
 * Based on the lm90 driver.
 *
 * The LM63 is a sensor chip made by National Semiconductor. It measures
 * two temperatures (its own and one बाह्यal one) and the speed of one
 * fan, those speed it can additionally control. Complete datasheet can be
 * obtained from National's website at:
 *   http://www.national.com/pf/LM/LM63.hपंचांगl
 *
 * The LM63 is basically an LM86 with fan speed monitoring and control
 * capabilities added. It misses some of the LM86 features though:
 *  - No low limit क्रम local temperature.
 *  - No critical limit क्रम local temperature.
 *  - Critical limit क्रम remote temperature can be changed only once. We
 *    will consider that the critical limit is पढ़ो-only.
 *
 * The datasheet isn't very clear about what the tachometer पढ़ोing is.
 * I had a explanation from National Semiconductor though. The two lower
 * bits of the पढ़ो value have to be masked out. The value is still 16 bit
 * in width.
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
#समावेश <linux/of_device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

/*
 * Addresses to scan
 * Address is fully defined पूर्णांकernally and cannot be changed except क्रम
 * LM64 which has one pin dedicated to address selection.
 * LM63 and LM96163 have address 0x4c.
 * LM64 can have address 0x18 or 0x4e.
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x18, 0x4c, 0x4e, I2C_CLIENT_END पूर्ण;

/*
 * The LM63 रेजिस्टरs
 */

#घोषणा LM63_REG_CONFIG1		0x03
#घोषणा LM63_REG_CONVRATE		0x04
#घोषणा LM63_REG_CONFIG2		0xBF
#घोषणा LM63_REG_CONFIG_FAN		0x4A

#घोषणा LM63_REG_TACH_COUNT_MSB		0x47
#घोषणा LM63_REG_TACH_COUNT_LSB		0x46
#घोषणा LM63_REG_TACH_LIMIT_MSB		0x49
#घोषणा LM63_REG_TACH_LIMIT_LSB		0x48

#घोषणा LM63_REG_PWM_VALUE		0x4C
#घोषणा LM63_REG_PWM_FREQ		0x4D
#घोषणा LM63_REG_LUT_TEMP_HYST		0x4F
#घोषणा LM63_REG_LUT_TEMP(nr)		(0x50 + 2 * (nr))
#घोषणा LM63_REG_LUT_PWM(nr)		(0x51 + 2 * (nr))

#घोषणा LM63_REG_LOCAL_TEMP		0x00
#घोषणा LM63_REG_LOCAL_HIGH		0x05

#घोषणा LM63_REG_REMOTE_TEMP_MSB	0x01
#घोषणा LM63_REG_REMOTE_TEMP_LSB	0x10
#घोषणा LM63_REG_REMOTE_OFFSET_MSB	0x11
#घोषणा LM63_REG_REMOTE_OFFSET_LSB	0x12
#घोषणा LM63_REG_REMOTE_HIGH_MSB	0x07
#घोषणा LM63_REG_REMOTE_HIGH_LSB	0x13
#घोषणा LM63_REG_REMOTE_LOW_MSB		0x08
#घोषणा LM63_REG_REMOTE_LOW_LSB		0x14
#घोषणा LM63_REG_REMOTE_TCRIT		0x19
#घोषणा LM63_REG_REMOTE_TCRIT_HYST	0x21

#घोषणा LM63_REG_ALERT_STATUS		0x02
#घोषणा LM63_REG_ALERT_MASK		0x16

#घोषणा LM63_REG_MAN_ID			0xFE
#घोषणा LM63_REG_CHIP_ID		0xFF

#घोषणा LM96163_REG_TRUTHERM		0x30
#घोषणा LM96163_REG_REMOTE_TEMP_U_MSB	0x31
#घोषणा LM96163_REG_REMOTE_TEMP_U_LSB	0x32
#घोषणा LM96163_REG_CONFIG_ENHANCED	0x45

#घोषणा LM63_MAX_CONVRATE		9

#घोषणा LM63_MAX_CONVRATE_HZ		32
#घोषणा LM96163_MAX_CONVRATE_HZ		26

/*
 * Conversions and various macros
 * For tachometer counts, the LM63 uses 16-bit values.
 * For local temperature and high limit, remote critical limit and hysteresis
 * value, it uses चिन्हित 8-bit values with LSB = 1 degree Celsius.
 * For remote temperature, low and high limits, it uses चिन्हित 11-bit values
 * with LSB = 0.125 degree Celsius, left-justअगरied in 16-bit रेजिस्टरs.
 * For LM64 the actual remote diode temperature is 16 degree Celsius higher
 * than the रेजिस्टर पढ़ोing. Remote temperature setpoपूर्णांकs have to be
 * adapted accordingly.
 */

#घोषणा FAN_FROM_REG(reg)	((reg) == 0xFFFC || (reg) == 0 ? 0 : \
				 5400000 / (reg))
#घोषणा FAN_TO_REG(val)		((val) <= 82 ? 0xFFFC : \
				 (5400000 / (val)) & 0xFFFC)
#घोषणा TEMP8_FROM_REG(reg)	((reg) * 1000)
#घोषणा TEMP8_TO_REG(val)	DIV_ROUND_CLOSEST(clamp_val((val), -128000, \
							    127000), 1000)
#घोषणा TEMP8U_TO_REG(val)	DIV_ROUND_CLOSEST(clamp_val((val), 0, \
							    255000), 1000)
#घोषणा TEMP11_FROM_REG(reg)	((reg) / 32 * 125)
#घोषणा TEMP11_TO_REG(val)	(DIV_ROUND_CLOSEST(clamp_val((val), -128000, \
							     127875), 125) * 32)
#घोषणा TEMP11U_TO_REG(val)	(DIV_ROUND_CLOSEST(clamp_val((val), 0, \
							     255875), 125) * 32)
#घोषणा HYST_TO_REG(val)	DIV_ROUND_CLOSEST(clamp_val((val), 0, 127000), \
						  1000)

#घोषणा UPDATE_INTERVAL(max, rate) \
			((1000 << (LM63_MAX_CONVRATE - (rate))) / (max))

क्रमागत chips अणु lm63, lm64, lm96163 पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा lm63_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	स्थिर काष्ठा attribute_group *groups[5];
	अक्षर valid; /* zero until following fields are valid */
	अक्षर lut_valid; /* zero until lut fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	अचिन्हित दीर्घ lut_last_updated; /* in jअगरfies */
	क्रमागत chips kind;
	पूर्णांक temp2_offset;

	पूर्णांक update_पूर्णांकerval;	/* in milliseconds */
	पूर्णांक max_convrate_hz;
	पूर्णांक lut_size;		/* 8 or 12 */

	/* रेजिस्टरs values */
	u8 config, config_fan;
	u16 fan[2];	/* 0: input
			   1: low limit */
	u8 pwm1_freq;
	u8 pwm1[13];	/* 0: current output
			   1-12: lookup table */
	s8 temp8[15];	/* 0: local input
			   1: local high limit
			   2: remote critical limit
			   3-14: lookup table */
	s16 temp11[4];	/* 0: remote input
			   1: remote low limit
			   2: remote high limit
			   3: remote offset */
	u16 temp11u;	/* remote input (अचिन्हित) */
	u8 temp2_crit_hyst;
	u8 lut_temp_hyst;
	u8 alarms;
	bool pwm_highres;
	bool lut_temp_highres;
	bool remote_अचिन्हित; /* true अगर अचिन्हित remote upper limits */
	bool trutherm;
पूर्ण;

अटल अंतरभूत पूर्णांक temp8_from_reg(काष्ठा lm63_data *data, पूर्णांक nr)
अणु
	अगर (data->remote_अचिन्हित)
		वापस TEMP8_FROM_REG((u8)data->temp8[nr]);
	वापस TEMP8_FROM_REG(data->temp8[nr]);
पूर्ण

अटल अंतरभूत पूर्णांक lut_temp_from_reg(काष्ठा lm63_data *data, पूर्णांक nr)
अणु
	वापस data->temp8[nr] * (data->lut_temp_highres ? 500 : 1000);
पूर्ण

अटल अंतरभूत पूर्णांक lut_temp_to_reg(काष्ठा lm63_data *data, दीर्घ val)
अणु
	val -= data->temp2_offset;
	अगर (data->lut_temp_highres)
		वापस DIV_ROUND_CLOSEST(clamp_val(val, 0, 127500), 500);
	अन्यथा
		वापस DIV_ROUND_CLOSEST(clamp_val(val, 0, 127000), 1000);
पूर्ण

/*
 * Update the lookup table रेजिस्टर cache.
 * client->update_lock must be held when calling this function.
 */
अटल व्योम lm63_update_lut(काष्ठा lm63_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;

	अगर (समय_after(jअगरfies, data->lut_last_updated + 5 * HZ) ||
	    !data->lut_valid) अणु
		क्रम (i = 0; i < data->lut_size; i++) अणु
			data->pwm1[1 + i] = i2c_smbus_पढ़ो_byte_data(client,
					    LM63_REG_LUT_PWM(i));
			data->temp8[3 + i] = i2c_smbus_पढ़ो_byte_data(client,
					     LM63_REG_LUT_TEMP(i));
		पूर्ण
		data->lut_temp_hyst = i2c_smbus_पढ़ो_byte_data(client,
				      LM63_REG_LUT_TEMP_HYST);

		data->lut_last_updated = jअगरfies;
		data->lut_valid = 1;
	पूर्ण
पूर्ण

अटल काष्ठा lm63_data *lm63_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ next_update;

	mutex_lock(&data->update_lock);

	next_update = data->last_updated +
		      msecs_to_jअगरfies(data->update_पूर्णांकerval);
	अगर (समय_after(jअगरfies, next_update) || !data->valid) अणु
		अगर (data->config & 0x04) अणु /* tachometer enabled  */
			/* order matters क्रम fan1_input */
			data->fan[0] = i2c_smbus_पढ़ो_byte_data(client,
				       LM63_REG_TACH_COUNT_LSB) & 0xFC;
			data->fan[0] |= i2c_smbus_पढ़ो_byte_data(client,
					LM63_REG_TACH_COUNT_MSB) << 8;
			data->fan[1] = (i2c_smbus_पढ़ो_byte_data(client,
					LM63_REG_TACH_LIMIT_LSB) & 0xFC)
				     | (i2c_smbus_पढ़ो_byte_data(client,
					LM63_REG_TACH_LIMIT_MSB) << 8);
		पूर्ण

		data->pwm1_freq = i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_PWM_FREQ);
		अगर (data->pwm1_freq == 0)
			data->pwm1_freq = 1;
		data->pwm1[0] = i2c_smbus_पढ़ो_byte_data(client,
				LM63_REG_PWM_VALUE);

		data->temp8[0] = i2c_smbus_पढ़ो_byte_data(client,
				 LM63_REG_LOCAL_TEMP);
		data->temp8[1] = i2c_smbus_पढ़ो_byte_data(client,
				 LM63_REG_LOCAL_HIGH);

		/* order matters क्रम temp2_input */
		data->temp11[0] = i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_REMOTE_TEMP_MSB) << 8;
		data->temp11[0] |= i2c_smbus_पढ़ो_byte_data(client,
				   LM63_REG_REMOTE_TEMP_LSB);
		data->temp11[1] = (i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_REMOTE_LOW_MSB) << 8)
				| i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_REMOTE_LOW_LSB);
		data->temp11[2] = (i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_REMOTE_HIGH_MSB) << 8)
				| i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_REMOTE_HIGH_LSB);
		data->temp11[3] = (i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_REMOTE_OFFSET_MSB) << 8)
				| i2c_smbus_पढ़ो_byte_data(client,
				  LM63_REG_REMOTE_OFFSET_LSB);

		अगर (data->kind == lm96163)
			data->temp11u = (i2c_smbus_पढ़ो_byte_data(client,
					LM96163_REG_REMOTE_TEMP_U_MSB) << 8)
				      | i2c_smbus_पढ़ो_byte_data(client,
					LM96163_REG_REMOTE_TEMP_U_LSB);

		data->temp8[2] = i2c_smbus_पढ़ो_byte_data(client,
				 LM63_REG_REMOTE_TCRIT);
		data->temp2_crit_hyst = i2c_smbus_पढ़ो_byte_data(client,
					LM63_REG_REMOTE_TCRIT_HYST);

		data->alarms = i2c_smbus_पढ़ो_byte_data(client,
			       LM63_REG_ALERT_STATUS) & 0x7F;

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	lm63_update_lut(data);

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Trip poपूर्णांकs in the lookup table should be in ascending order क्रम both
 * temperatures and PWM output values.
 */
अटल पूर्णांक lm63_lut_looks_bad(काष्ठा device *dev, काष्ठा lm63_data *data)
अणु
	पूर्णांक i;

	mutex_lock(&data->update_lock);
	lm63_update_lut(data);

	क्रम (i = 1; i < data->lut_size; i++) अणु
		अगर (data->pwm1[1 + i - 1] > data->pwm1[1 + i]
		 || data->temp8[3 + i - 1] > data->temp8[3 + i]) अणु
			dev_warn(dev,
				 "Lookup table doesn't look sane (check entries %d and %d)\n",
				 i, i + 1);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस i == data->lut_size ? 0 : 1;
पूर्ण

/*
 * Sysfs callback functions and files
 */

अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[attr->index]));
पूर्ण

अटल sमाप_प्रकार set_fan(काष्ठा device *dev, काष्ठा device_attribute *dummy,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan[1] = FAN_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client, LM63_REG_TACH_LIMIT_LSB,
				  data->fan[1] & 0xFF);
	i2c_smbus_ग_लिखो_byte_data(client, LM63_REG_TACH_LIMIT_MSB,
				  data->fan[1] >> 8);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm1(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);
	पूर्णांक nr = attr->index;
	पूर्णांक pwm;

	अगर (data->pwm_highres)
		pwm = data->pwm1[nr];
	अन्यथा
		pwm = data->pwm1[nr] >= 2 * data->pwm1_freq ?
		       255 : (data->pwm1[nr] * 255 + data->pwm1_freq) /
		       (2 * data->pwm1_freq);

	वापस प्र_लिखो(buf, "%d\n", pwm);
पूर्ण

अटल sमाप_प्रकार set_pwm1(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u8 reg;

	अगर (!(data->config_fan & 0x20)) /* रेजिस्टर is पढ़ो-only */
		वापस -EPERM;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	reg = nr ? LM63_REG_LUT_PWM(nr - 1) : LM63_REG_PWM_VALUE;
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	data->pwm1[nr] = data->pwm_highres ? val :
			(val * data->pwm1_freq * 2 + 127) / 255;
	i2c_smbus_ग_लिखो_byte_data(client, reg, data->pwm1[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm1_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *dummy, अक्षर *buf)
अणु
	काष्ठा lm63_data *data = lm63_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->config_fan & 0x20 ? 1 : 2);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *dummy,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val < 1 || val > 2)
		वापस -EINVAL;

	/*
	 * Only let the user चयन to स्वतःmatic mode अगर the lookup table
	 * looks sane.
	 */
	अगर (val == 2 && lm63_lut_looks_bad(dev, data))
		वापस -EPERM;

	mutex_lock(&data->update_lock);
	data->config_fan = i2c_smbus_पढ़ो_byte_data(client,
						    LM63_REG_CONFIG_FAN);
	अगर (val == 1)
		data->config_fan |= 0x20;
	अन्यथा
		data->config_fan &= ~0x20;
	i2c_smbus_ग_लिखो_byte_data(client, LM63_REG_CONFIG_FAN,
				  data->config_fan);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * There are 8bit रेजिस्टरs क्रम both local(temp1) and remote(temp2) sensor.
 * For remote sensor रेजिस्टरs temp2_offset has to be considered,
 * क्रम local sensor it must not.
 * So we need separate 8bit accessors क्रम local and remote sensor.
 */
अटल sमाप_प्रकार show_local_temp8(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP8_FROM_REG(data->temp8[attr->index]));
पूर्ण

अटल sमाप_प्रकार show_remote_temp8(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr,
				 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", temp8_from_reg(data, attr->index)
		       + data->temp2_offset);
पूर्ण

अटल sमाप_प्रकार show_lut_temp(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", lut_temp_from_reg(data, attr->index)
		       + data->temp2_offset);
पूर्ण

अटल sमाप_प्रकार set_temp8(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;
	पूर्णांक temp;
	u8 reg;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (nr) अणु
	हाल 2:
		reg = LM63_REG_REMOTE_TCRIT;
		अगर (data->remote_अचिन्हित)
			temp = TEMP8U_TO_REG(val - data->temp2_offset);
		अन्यथा
			temp = TEMP8_TO_REG(val - data->temp2_offset);
		अवरोध;
	हाल 1:
		reg = LM63_REG_LOCAL_HIGH;
		temp = TEMP8_TO_REG(val);
		अवरोध;
	शेष:	/* lookup table */
		reg = LM63_REG_LUT_TEMP(nr - 3);
		temp = lut_temp_to_reg(data, val);
	पूर्ण
	data->temp8[nr] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, reg, temp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_temp11(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);
	पूर्णांक nr = attr->index;
	पूर्णांक temp;

	अगर (!nr) अणु
		/*
		 * Use अचिन्हित temperature unless its value is zero.
		 * If it is zero, use चिन्हित temperature.
		 */
		अगर (data->temp11u)
			temp = TEMP11_FROM_REG(data->temp11u);
		अन्यथा
			temp = TEMP11_FROM_REG(data->temp11[nr]);
	पूर्ण अन्यथा अणु
		अगर (data->remote_अचिन्हित && nr == 2)
			temp = TEMP11_FROM_REG((u16)data->temp11[nr]);
		अन्यथा
			temp = TEMP11_FROM_REG(data->temp11[nr]);
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", temp + data->temp2_offset);
पूर्ण

अटल sमाप_प्रकार set_temp11(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अटल स्थिर u8 reg[6] = अणु
		LM63_REG_REMOTE_LOW_MSB,
		LM63_REG_REMOTE_LOW_LSB,
		LM63_REG_REMOTE_HIGH_MSB,
		LM63_REG_REMOTE_HIGH_LSB,
		LM63_REG_REMOTE_OFFSET_MSB,
		LM63_REG_REMOTE_OFFSET_LSB,
	पूर्ण;

	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;
	पूर्णांक nr = attr->index;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (data->remote_अचिन्हित && nr == 2)
		data->temp11[nr] = TEMP11U_TO_REG(val - data->temp2_offset);
	अन्यथा
		data->temp11[nr] = TEMP11_TO_REG(val - data->temp2_offset);

	i2c_smbus_ग_लिखो_byte_data(client, reg[(nr - 1) * 2],
				  data->temp11[nr] >> 8);
	i2c_smbus_ग_लिखो_byte_data(client, reg[(nr - 1) * 2 + 1],
				  data->temp11[nr] & 0xff);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Hysteresis रेजिस्टर holds a relative value, जबतक we want to present
 * an असलolute to user-space
 */
अटल sमाप_प्रकार temp2_crit_hyst_show(काष्ठा device *dev,
				    काष्ठा device_attribute *dummy, अक्षर *buf)
अणु
	काष्ठा lm63_data *data = lm63_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", temp8_from_reg(data, 2)
		       + data->temp2_offset
		       - TEMP8_FROM_REG(data->temp2_crit_hyst));
पूर्ण

अटल sमाप_प्रकार show_lut_temp_hyst(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", lut_temp_from_reg(data, attr->index)
		       + data->temp2_offset
		       - TEMP8_FROM_REG(data->lut_temp_hyst));
पूर्ण

/*
 * And now the other way around, user-space provides an असलolute
 * hysteresis value and we have to store a relative one
 */
अटल sमाप_प्रकार temp2_crit_hyst_store(काष्ठा device *dev,
				     काष्ठा device_attribute *dummy,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;
	दीर्घ hyst;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	hyst = temp8_from_reg(data, 2) + data->temp2_offset - val;
	i2c_smbus_ग_लिखो_byte_data(client, LM63_REG_REMOTE_TCRIT_HYST,
				  HYST_TO_REG(hyst));
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Set conversion rate.
 * client->update_lock must be held when calling this function.
 */
अटल व्योम lm63_set_convrate(काष्ठा lm63_data *data, अचिन्हित पूर्णांक पूर्णांकerval)
अणु
	काष्ठा i2c_client *client = data->client;
	अचिन्हित पूर्णांक update_पूर्णांकerval;
	पूर्णांक i;

	/* Shअगरt calculations to aव्योम rounding errors */
	पूर्णांकerval <<= 6;

	/* find the nearest update rate */
	update_पूर्णांकerval = (1 << (LM63_MAX_CONVRATE + 6)) * 1000
	  / data->max_convrate_hz;
	क्रम (i = 0; i < LM63_MAX_CONVRATE; i++, update_पूर्णांकerval >>= 1)
		अगर (पूर्णांकerval >= update_पूर्णांकerval * 3 / 4)
			अवरोध;

	i2c_smbus_ग_लिखो_byte_data(client, LM63_REG_CONVRATE, i);
	data->update_पूर्णांकerval = UPDATE_INTERVAL(data->max_convrate_hz, i);
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", data->update_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	lm63_set_convrate(data, clamp_val(val, 0, 100000));
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp2_type_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, data->trutherm ? "1\n" : "2\n");
पूर्ण

अटल sमाप_प्रकार temp2_type_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm63_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;
	u8 reg;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val != 1 && val != 2)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->trutherm = val == 1;
	reg = i2c_smbus_पढ़ो_byte_data(client, LM96163_REG_TRUTHERM) & ~0x02;
	i2c_smbus_ग_लिखो_byte_data(client, LM96163_REG_TRUTHERM,
				  reg | (data->trutherm ? 0x02 : 0x00));
	data->valid = 0;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *dummy,
			   अक्षर *buf)
अणु
	काष्ठा lm63_data *data = lm63_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm63_data *data = lm63_update_device(dev);
	पूर्णांक bitnr = attr->index;

	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR(fan1_input, S_IRUGO, show_fan, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_min, S_IWUSR | S_IRUGO, show_fan,
	set_fan, 1);

अटल SENSOR_DEVICE_ATTR(pwm1, S_IWUSR | S_IRUGO, show_pwm1, set_pwm1, 0);
अटल DEVICE_ATTR_RW(pwm1_enable);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक1_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 1);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक1_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 3);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक2_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 2);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक2_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 4);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक2_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक3_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 3);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक3_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 5);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक3_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक4_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 4);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक4_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 6);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक4_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक5_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 5);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक5_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 7);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक5_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक6_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 6);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक6_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 8);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक6_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक7_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 7);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक7_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 9);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक7_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 9);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक8_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 8);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक8_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 10);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक8_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 10);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक9_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 9);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक9_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 11);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक9_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 11);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक10_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 10);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक10_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 12);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक10_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 12);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक11_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 11);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक11_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 13);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक11_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 13);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक12_pwm, S_IWUSR | S_IRUGO,
	show_pwm1, set_pwm1, 12);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक12_temp, S_IWUSR | S_IRUGO,
	show_lut_temp, set_temp8, 14);
अटल SENSOR_DEVICE_ATTR(pwm1_स्वतः_poपूर्णांक12_temp_hyst, S_IRUGO,
	show_lut_temp_hyst, शून्य, 14);

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, show_local_temp8, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_max, S_IWUSR | S_IRUGO, show_local_temp8,
	set_temp8, 1);

अटल SENSOR_DEVICE_ATTR(temp2_input, S_IRUGO, show_temp11, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp2_min, S_IWUSR | S_IRUGO, show_temp11,
	set_temp11, 1);
अटल SENSOR_DEVICE_ATTR(temp2_max, S_IWUSR | S_IRUGO, show_temp11,
	set_temp11, 2);
अटल SENSOR_DEVICE_ATTR(temp2_offset, S_IWUSR | S_IRUGO, show_temp11,
	set_temp11, 3);
अटल SENSOR_DEVICE_ATTR(temp2_crit, S_IRUGO, show_remote_temp8,
	set_temp8, 2);
अटल DEVICE_ATTR_RW(temp2_crit_hyst);

अटल DEVICE_ATTR_RW(temp2_type);

/* Inभागidual alarm files */
अटल SENSOR_DEVICE_ATTR(fan1_min_alarm, S_IRUGO, show_alarm, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp2_crit_alarm, S_IRUGO, show_alarm, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp2_fault, S_IRUGO, show_alarm, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp2_min_alarm, S_IRUGO, show_alarm, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(temp2_max_alarm, S_IRUGO, show_alarm, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(temp1_max_alarm, S_IRUGO, show_alarm, शून्य, 6);
/* Raw alarm file क्रम compatibility */
अटल DEVICE_ATTR_RO(alarms);

अटल DEVICE_ATTR_RW(update_पूर्णांकerval);

अटल काष्ठा attribute *lm63_attributes[] = अणु
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&dev_attr_pwm1_enable.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक5_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक5_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक5_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक6_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक6_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक6_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक7_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक7_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक7_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक8_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक8_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक8_temp_hyst.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&dev_attr_temp2_crit_hyst.attr,

	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&dev_attr_alarms.attr,
	&dev_attr_update_पूर्णांकerval.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *lm63_attributes_temp2_type[] = अणु
	&dev_attr_temp2_type.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm63_group_temp2_type = अणु
	.attrs = lm63_attributes_temp2_type,
पूर्ण;

अटल काष्ठा attribute *lm63_attributes_extra_lut[] = अणु
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक9_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक9_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक9_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक10_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक10_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक10_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक11_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक11_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक11_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक12_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक12_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक12_temp_hyst.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm63_group_extra_lut = अणु
	.attrs = lm63_attributes_extra_lut,
पूर्ण;

/*
 * On LM63, temp2_crit can be set only once, which should be job
 * of the bootloader.
 * On LM64, temp2_crit can always be set.
 * On LM96163, temp2_crit can be set अगर bit 1 of the configuration
 * रेजिस्टर is true.
 */
अटल umode_t lm63_attribute_mode(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा lm63_data *data = dev_get_drvdata(dev);

	अगर (attr == &sensor_dev_attr_temp2_crit.dev_attr.attr
	    && (data->kind == lm64 ||
		(data->kind == lm96163 && (data->config & 0x02))))
		वापस attr->mode | S_IWUSR;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group lm63_group = अणु
	.is_visible = lm63_attribute_mode,
	.attrs = lm63_attributes,
पूर्ण;

अटल काष्ठा attribute *lm63_attributes_fan1[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,

	&sensor_dev_attr_fan1_min_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm63_group_fan1 = अणु
	.attrs = lm63_attributes_fan1,
पूर्ण;

/*
 * Real code
 */

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm63_detect(काष्ठा i2c_client *client,
		       काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u8 man_id, chip_id, reg_config1, reg_config2;
	u8 reg_alert_status, reg_alert_mask;
	पूर्णांक address = client->addr;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	man_id = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_MAN_ID);
	chip_id = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_CHIP_ID);

	reg_config1 = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_CONFIG1);
	reg_config2 = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_CONFIG2);
	reg_alert_status = i2c_smbus_पढ़ो_byte_data(client,
			   LM63_REG_ALERT_STATUS);
	reg_alert_mask = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_ALERT_MASK);

	अगर (man_id != 0x01 /* National Semiconductor */
	 || (reg_config1 & 0x18) != 0x00
	 || (reg_config2 & 0xF8) != 0x00
	 || (reg_alert_status & 0x20) != 0x00
	 || (reg_alert_mask & 0xA4) != 0xA4) अणु
		dev_dbg(&adapter->dev,
			"Unsupported chip (man_id=0x%02X, chip_id=0x%02X)\n",
			man_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	अगर (chip_id == 0x41 && address == 0x4c)
		strlcpy(info->type, "lm63", I2C_NAME_SIZE);
	अन्यथा अगर (chip_id == 0x51 && (address == 0x18 || address == 0x4e))
		strlcpy(info->type, "lm64", I2C_NAME_SIZE);
	अन्यथा अगर (chip_id == 0x49 && address == 0x4c)
		strlcpy(info->type, "lm96163", I2C_NAME_SIZE);
	अन्यथा
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Ideally we shouldn't have to initialize anything, since the BIOS
 * should have taken care of everything
 */
अटल व्योम lm63_init_client(काष्ठा lm63_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	काष्ठा device *dev = &client->dev;
	u8 convrate;

	data->config = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_CONFIG1);
	data->config_fan = i2c_smbus_पढ़ो_byte_data(client,
						    LM63_REG_CONFIG_FAN);

	/* Start converting अगर needed */
	अगर (data->config & 0x40) अणु /* standby */
		dev_dbg(dev, "Switching to operational mode\n");
		data->config &= 0xA7;
		i2c_smbus_ग_लिखो_byte_data(client, LM63_REG_CONFIG1,
					  data->config);
	पूर्ण
	/* Tachometer is always enabled on LM64 */
	अगर (data->kind == lm64)
		data->config |= 0x04;

	/* We may need pwm1_freq beक्रमe ever updating the client data */
	data->pwm1_freq = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_PWM_FREQ);
	अगर (data->pwm1_freq == 0)
		data->pwm1_freq = 1;

	चयन (data->kind) अणु
	हाल lm63:
	हाल lm64:
		data->max_convrate_hz = LM63_MAX_CONVRATE_HZ;
		data->lut_size = 8;
		अवरोध;
	हाल lm96163:
		data->max_convrate_hz = LM96163_MAX_CONVRATE_HZ;
		data->lut_size = 12;
		data->trutherm
		  = i2c_smbus_पढ़ो_byte_data(client,
					     LM96163_REG_TRUTHERM) & 0x02;
		अवरोध;
	पूर्ण
	convrate = i2c_smbus_पढ़ो_byte_data(client, LM63_REG_CONVRATE);
	अगर (unlikely(convrate > LM63_MAX_CONVRATE))
		convrate = LM63_MAX_CONVRATE;
	data->update_पूर्णांकerval = UPDATE_INTERVAL(data->max_convrate_hz,
						convrate);

	/*
	 * For LM96163, check अगर high resolution PWM
	 * and अचिन्हित temperature क्रमmat is enabled.
	 */
	अगर (data->kind == lm96163) अणु
		u8 config_enhanced
		  = i2c_smbus_पढ़ो_byte_data(client,
					     LM96163_REG_CONFIG_ENHANCED);
		अगर (config_enhanced & 0x20)
			data->lut_temp_highres = true;
		अगर ((config_enhanced & 0x10)
		    && !(data->config_fan & 0x08) && data->pwm1_freq == 8)
			data->pwm_highres = true;
		अगर (config_enhanced & 0x08)
			data->remote_अचिन्हित = true;
	पूर्ण

	/* Show some debug info about the LM63 configuration */
	अगर (data->kind == lm63)
		dev_dbg(dev, "Alert/tach pin configured for %s\n",
			(data->config & 0x04) ? "tachometer input" :
			"alert output");
	dev_dbg(dev, "PWM clock %s kHz, output frequency %u Hz\n",
		(data->config_fan & 0x08) ? "1.4" : "360",
		((data->config_fan & 0x08) ? 700 : 180000) / data->pwm1_freq);
	dev_dbg(dev, "PWM output active %s, %s mode\n",
		(data->config_fan & 0x10) ? "low" : "high",
		(data->config_fan & 0x20) ? "manual" : "auto");
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm63_id[];

अटल पूर्णांक lm63_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm63_data *data;
	पूर्णांक groups = 0;

	data = devm_kzalloc(dev, माप(काष्ठा lm63_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Set the device type */
	अगर (client->dev.of_node)
		data->kind = (क्रमागत chips)of_device_get_match_data(&client->dev);
	अन्यथा
		data->kind = i2c_match_id(lm63_id, client)->driver_data;
	अगर (data->kind == lm64)
		data->temp2_offset = 16000;

	/* Initialize chip */
	lm63_init_client(data);

	/* Register sysfs hooks */
	data->groups[groups++] = &lm63_group;
	अगर (data->config & 0x04)	/* tachometer enabled */
		data->groups[groups++] = &lm63_group_fan1;

	अगर (data->kind == lm96163) अणु
		data->groups[groups++] = &lm63_group_temp2_type;
		data->groups[groups++] = &lm63_group_extra_lut;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id lm63_id[] = अणु
	अणु "lm63", lm63 पूर्ण,
	अणु "lm64", lm64 पूर्ण,
	अणु "lm96163", lm96163 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm63_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused lm63_of_match[] = अणु
	अणु
		.compatible = "national,lm63",
		.data = (व्योम *)lm63
	पूर्ण,
	अणु
		.compatible = "national,lm64",
		.data = (व्योम *)lm64
	पूर्ण,
	अणु
		.compatible = "national,lm96163",
		.data = (व्योम *)lm96163
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lm63_of_match);

अटल काष्ठा i2c_driver lm63_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm63",
		.of_match_table = of_match_ptr(lm63_of_match),
	पूर्ण,
	.probe_new	= lm63_probe,
	.id_table	= lm63_id,
	.detect		= lm63_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm63_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("LM63 driver");
MODULE_LICENSE("GPL");
