<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max31790.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *             monitoring.
 *
 * (C) 2015 by Il Han <corone.il.han@gmail.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

/* MAX31790 रेजिस्टरs */
#घोषणा MAX31790_REG_GLOBAL_CONFIG	0x00
#घोषणा MAX31790_REG_FAN_CONFIG(ch)	(0x02 + (ch))
#घोषणा MAX31790_REG_FAN_DYNAMICS(ch)	(0x08 + (ch))
#घोषणा MAX31790_REG_FAN_FAULT_STATUS2	0x10
#घोषणा MAX31790_REG_FAN_FAULT_STATUS1	0x11
#घोषणा MAX31790_REG_TACH_COUNT(ch)	(0x18 + (ch) * 2)
#घोषणा MAX31790_REG_PWM_DUTY_CYCLE(ch)	(0x30 + (ch) * 2)
#घोषणा MAX31790_REG_PWMOUT(ch)		(0x40 + (ch) * 2)
#घोषणा MAX31790_REG_TARGET_COUNT(ch)	(0x50 + (ch) * 2)

/* Fan Config रेजिस्टर bits */
#घोषणा MAX31790_FAN_CFG_RPM_MODE	0x80
#घोषणा MAX31790_FAN_CFG_TACH_INPUT_EN	0x08
#घोषणा MAX31790_FAN_CFG_TACH_INPUT	0x01

/* Fan Dynamics रेजिस्टर bits */
#घोषणा MAX31790_FAN_DYN_SR_SHIFT	5
#घोषणा MAX31790_FAN_DYN_SR_MASK	0xE0
#घोषणा SR_FROM_REG(reg)		(((reg) & MAX31790_FAN_DYN_SR_MASK) \
					 >> MAX31790_FAN_DYN_SR_SHIFT)

#घोषणा FAN_RPM_MIN			120
#घोषणा FAN_RPM_MAX			7864320

#घोषणा RPM_FROM_REG(reg, sr)		(((reg) >> 4) ? \
					 ((60 * (sr) * 8192) / ((reg) >> 4)) : \
					 FAN_RPM_MAX)
#घोषणा RPM_TO_REG(rpm, sr)		((60 * (sr) * 8192) / ((rpm) * 2))

#घोषणा NR_CHANNEL			6

/*
 * Client data (each client माला_लो its own)
 */
काष्ठा max31790_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	bool valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* रेजिस्टर values */
	u8 fan_config[NR_CHANNEL];
	u8 fan_dynamics[NR_CHANNEL];
	u16 fault_status;
	u16 tach[NR_CHANNEL * 2];
	u16 pwm[NR_CHANNEL];
	u16 target_count[NR_CHANNEL];
पूर्ण;

अटल काष्ठा max31790_data *max31790_update_device(काष्ठा device *dev)
अणु
	काष्ठा max31790_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा max31790_data *ret = data;
	पूर्णांक i;
	पूर्णांक rv;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		rv = i2c_smbus_पढ़ो_byte_data(client,
				MAX31790_REG_FAN_FAULT_STATUS1);
		अगर (rv < 0)
			जाओ पात;
		data->fault_status = rv & 0x3F;

		rv = i2c_smbus_पढ़ो_byte_data(client,
				MAX31790_REG_FAN_FAULT_STATUS2);
		अगर (rv < 0)
			जाओ पात;
		data->fault_status |= (rv & 0x3F) << 6;

		क्रम (i = 0; i < NR_CHANNEL; i++) अणु
			rv = i2c_smbus_पढ़ो_word_swapped(client,
					MAX31790_REG_TACH_COUNT(i));
			अगर (rv < 0)
				जाओ पात;
			data->tach[i] = rv;

			अगर (data->fan_config[i]
			    & MAX31790_FAN_CFG_TACH_INPUT) अणु
				rv = i2c_smbus_पढ़ो_word_swapped(client,
					MAX31790_REG_TACH_COUNT(NR_CHANNEL
								+ i));
				अगर (rv < 0)
					जाओ पात;
				data->tach[NR_CHANNEL + i] = rv;
			पूर्ण अन्यथा अणु
				rv = i2c_smbus_पढ़ो_word_swapped(client,
						MAX31790_REG_PWMOUT(i));
				अगर (rv < 0)
					जाओ पात;
				data->pwm[i] = rv;

				rv = i2c_smbus_पढ़ो_word_swapped(client,
						MAX31790_REG_TARGET_COUNT(i));
				अगर (rv < 0)
					जाओ पात;
				data->target_count[i] = rv;
			पूर्ण
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण
	जाओ करोne;

पात:
	data->valid = false;
	ret = ERR_PTR(rv);

करोne:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल स्थिर u8 tach_period[8] = अणु 1, 2, 4, 8, 16, 32, 32, 32 पूर्ण;

अटल u8 get_tach_period(u8 fan_dynamics)
अणु
	वापस tach_period[SR_FROM_REG(fan_dynamics)];
पूर्ण

अटल u8 bits_क्रम_tach_period(पूर्णांक rpm)
अणु
	u8 bits;

	अगर (rpm < 500)
		bits = 0x0;
	अन्यथा अगर (rpm < 1000)
		bits = 0x1;
	अन्यथा अगर (rpm < 2000)
		bits = 0x2;
	अन्यथा अगर (rpm < 4000)
		bits = 0x3;
	अन्यथा अगर (rpm < 8000)
		bits = 0x4;
	अन्यथा
		bits = 0x5;

	वापस bits;
पूर्ण

अटल पूर्णांक max31790_पढ़ो_fan(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा max31790_data *data = max31790_update_device(dev);
	पूर्णांक sr, rpm;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	चयन (attr) अणु
	हाल hwmon_fan_input:
		sr = get_tach_period(data->fan_dynamics[channel]);
		rpm = RPM_FROM_REG(data->tach[channel], sr);
		*val = rpm;
		वापस 0;
	हाल hwmon_fan_target:
		sr = get_tach_period(data->fan_dynamics[channel]);
		rpm = RPM_FROM_REG(data->target_count[channel], sr);
		*val = rpm;
		वापस 0;
	हाल hwmon_fan_fault:
		*val = !!(data->fault_status & (1 << channel));
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक max31790_ग_लिखो_fan(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा max31790_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक target_count;
	पूर्णांक err = 0;
	u8 bits;
	पूर्णांक sr;

	mutex_lock(&data->update_lock);

	चयन (attr) अणु
	हाल hwmon_fan_target:
		val = clamp_val(val, FAN_RPM_MIN, FAN_RPM_MAX);
		bits = bits_क्रम_tach_period(val);
		data->fan_dynamics[channel] =
			((data->fan_dynamics[channel] &
			  ~MAX31790_FAN_DYN_SR_MASK) |
			 (bits << MAX31790_FAN_DYN_SR_SHIFT));
		err = i2c_smbus_ग_लिखो_byte_data(client,
					MAX31790_REG_FAN_DYNAMICS(channel),
					data->fan_dynamics[channel]);
		अगर (err < 0)
			अवरोध;

		sr = get_tach_period(data->fan_dynamics[channel]);
		target_count = RPM_TO_REG(val, sr);
		target_count = clamp_val(target_count, 0x1, 0x7FF);

		data->target_count[channel] = target_count << 5;

		err = i2c_smbus_ग_लिखो_word_swapped(client,
					MAX31790_REG_TARGET_COUNT(channel),
					data->target_count[channel]);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस err;
पूर्ण

अटल umode_t max31790_fan_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा max31790_data *data = _data;
	u8 fan_config = data->fan_config[channel % NR_CHANNEL];

	चयन (attr) अणु
	हाल hwmon_fan_input:
	हाल hwmon_fan_fault:
		अगर (channel < NR_CHANNEL ||
		    (fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			वापस 0444;
		वापस 0;
	हाल hwmon_fan_target:
		अगर (channel < NR_CHANNEL &&
		    !(fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			वापस 0644;
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक max31790_पढ़ो_pwm(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा max31790_data *data = max31790_update_device(dev);
	u8 fan_config;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	fan_config = data->fan_config[channel];

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		*val = data->pwm[channel] >> 8;
		वापस 0;
	हाल hwmon_pwm_enable:
		अगर (fan_config & MAX31790_FAN_CFG_RPM_MODE)
			*val = 2;
		अन्यथा अगर (fan_config & MAX31790_FAN_CFG_TACH_INPUT_EN)
			*val = 1;
		अन्यथा
			*val = 0;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक max31790_ग_लिखो_pwm(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा max31790_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 fan_config;
	पूर्णांक err = 0;

	mutex_lock(&data->update_lock);

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		अगर (val < 0 || val > 255) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		data->pwm[channel] = val << 8;
		err = i2c_smbus_ग_लिखो_word_swapped(client,
						   MAX31790_REG_PWMOUT(channel),
						   data->pwm[channel]);
		अवरोध;
	हाल hwmon_pwm_enable:
		fan_config = data->fan_config[channel];
		अगर (val == 0) अणु
			fan_config &= ~(MAX31790_FAN_CFG_TACH_INPUT_EN |
					MAX31790_FAN_CFG_RPM_MODE);
		पूर्ण अन्यथा अगर (val == 1) अणु
			fan_config = (fan_config |
				      MAX31790_FAN_CFG_TACH_INPUT_EN) &
				     ~MAX31790_FAN_CFG_RPM_MODE;
		पूर्ण अन्यथा अगर (val == 2) अणु
			fan_config |= MAX31790_FAN_CFG_TACH_INPUT_EN |
				      MAX31790_FAN_CFG_RPM_MODE;
		पूर्ण अन्यथा अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		data->fan_config[channel] = fan_config;
		err = i2c_smbus_ग_लिखो_byte_data(client,
					MAX31790_REG_FAN_CONFIG(channel),
					fan_config);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस err;
पूर्ण

अटल umode_t max31790_pwm_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा max31790_data *data = _data;
	u8 fan_config = data->fan_config[channel];

	चयन (attr) अणु
	हाल hwmon_pwm_input:
	हाल hwmon_pwm_enable:
		अगर (!(fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			वापस 0644;
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक max31790_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_fan:
		वापस max31790_पढ़ो_fan(dev, attr, channel, val);
	हाल hwmon_pwm:
		वापस max31790_पढ़ो_pwm(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक max31790_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			  u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_fan:
		वापस max31790_ग_लिखो_fan(dev, attr, channel, val);
	हाल hwmon_pwm:
		वापस max31790_ग_लिखो_pwm(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t max31790_is_visible(स्थिर व्योम *data,
				   क्रमागत hwmon_sensor_types type,
				   u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_fan:
		वापस max31790_fan_is_visible(data, attr, channel);
	हाल hwmon_pwm:
		वापस max31790_pwm_is_visible(data, attr, channel);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *max31790_info[] = अणु
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_TARGET | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_TARGET | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_TARGET | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_TARGET | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_TARGET | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_TARGET | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT),
	HWMON_CHANNEL_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops max31790_hwmon_ops = अणु
	.is_visible = max31790_is_visible,
	.पढ़ो = max31790_पढ़ो,
	.ग_लिखो = max31790_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info max31790_chip_info = अणु
	.ops = &max31790_hwmon_ops,
	.info = max31790_info,
पूर्ण;

अटल पूर्णांक max31790_init_client(काष्ठा i2c_client *client,
				काष्ठा max31790_data *data)
अणु
	पूर्णांक i, rv;

	क्रम (i = 0; i < NR_CHANNEL; i++) अणु
		rv = i2c_smbus_पढ़ो_byte_data(client,
				MAX31790_REG_FAN_CONFIG(i));
		अगर (rv < 0)
			वापस rv;
		data->fan_config[i] = rv;

		rv = i2c_smbus_पढ़ो_byte_data(client,
				MAX31790_REG_FAN_DYNAMICS(i));
		अगर (rv < 0)
			वापस rv;
		data->fan_dynamics[i] = rv;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max31790_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा max31790_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	अगर (!i2c_check_functionality(adapter,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(काष्ठा max31790_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/*
	 * Initialize the max31790 chip
	 */
	err = max31790_init_client(client, data);
	अगर (err)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data,
							 &max31790_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max31790_id[] = अणु
	अणु "max31790", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max31790_id);

अटल काष्ठा i2c_driver max31790_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.probe_new	= max31790_probe,
	.driver = अणु
		.name	= "max31790",
	पूर्ण,
	.id_table	= max31790_id,
पूर्ण;

module_i2c_driver(max31790_driver);

MODULE_AUTHOR("Il Han <corone.il.han@gmail.com>");
MODULE_DESCRIPTION("MAX31790 sensor driver");
MODULE_LICENSE("GPL");
