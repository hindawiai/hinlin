<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A hwmon driver क्रम the Analog Devices ADT7470
 * Copyright (C) 2007 IBM
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/util_macros.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2C, 0x2E, 0x2F, I2C_CLIENT_END पूर्ण;

/* ADT7470 रेजिस्टरs */
#घोषणा ADT7470_REG_BASE_ADDR			0x20
#घोषणा ADT7470_REG_TEMP_BASE_ADDR		0x20
#घोषणा ADT7470_REG_TEMP_MAX_ADDR		0x29
#घोषणा ADT7470_REG_FAN_BASE_ADDR		0x2A
#घोषणा ADT7470_REG_FAN_MAX_ADDR		0x31
#घोषणा ADT7470_REG_PWM_BASE_ADDR		0x32
#घोषणा ADT7470_REG_PWM_MAX_ADDR		0x35
#घोषणा ADT7470_REG_PWM_MAX_BASE_ADDR		0x38
#घोषणा ADT7470_REG_PWM_MAX_MAX_ADDR		0x3B
#घोषणा ADT7470_REG_CFG				0x40
#घोषणा		ADT7470_FSPD_MASK		0x04
#घोषणा ADT7470_REG_ALARM1			0x41
#घोषणा		ADT7470_R1T_ALARM		0x01
#घोषणा		ADT7470_R2T_ALARM		0x02
#घोषणा		ADT7470_R3T_ALARM		0x04
#घोषणा		ADT7470_R4T_ALARM		0x08
#घोषणा		ADT7470_R5T_ALARM		0x10
#घोषणा		ADT7470_R6T_ALARM		0x20
#घोषणा		ADT7470_R7T_ALARM		0x40
#घोषणा		ADT7470_OOL_ALARM		0x80
#घोषणा ADT7470_REG_ALARM2			0x42
#घोषणा		ADT7470_R8T_ALARM		0x01
#घोषणा		ADT7470_R9T_ALARM		0x02
#घोषणा		ADT7470_R10T_ALARM		0x04
#घोषणा		ADT7470_FAN1_ALARM		0x10
#घोषणा		ADT7470_FAN2_ALARM		0x20
#घोषणा		ADT7470_FAN3_ALARM		0x40
#घोषणा		ADT7470_FAN4_ALARM		0x80
#घोषणा ADT7470_REG_TEMP_LIMITS_BASE_ADDR	0x44
#घोषणा ADT7470_REG_TEMP_LIMITS_MAX_ADDR	0x57
#घोषणा ADT7470_REG_FAN_MIN_BASE_ADDR		0x58
#घोषणा ADT7470_REG_FAN_MIN_MAX_ADDR		0x5F
#घोषणा ADT7470_REG_FAN_MAX_BASE_ADDR		0x60
#घोषणा ADT7470_REG_FAN_MAX_MAX_ADDR		0x67
#घोषणा ADT7470_REG_PWM_CFG_BASE_ADDR		0x68
#घोषणा ADT7470_REG_PWM12_CFG			0x68
#घोषणा		ADT7470_PWM2_AUTO_MASK		0x40
#घोषणा		ADT7470_PWM1_AUTO_MASK		0x80
#घोषणा		ADT7470_PWM_AUTO_MASK		0xC0
#घोषणा ADT7470_REG_PWM34_CFG			0x69
#घोषणा		ADT7470_PWM3_AUTO_MASK		0x40
#घोषणा		ADT7470_PWM4_AUTO_MASK		0x80
#घोषणा	ADT7470_REG_PWM_MIN_BASE_ADDR		0x6A
#घोषणा ADT7470_REG_PWM_MIN_MAX_ADDR		0x6D
#घोषणा ADT7470_REG_PWM_TEMP_MIN_BASE_ADDR	0x6E
#घोषणा ADT7470_REG_PWM_TEMP_MIN_MAX_ADDR	0x71
#घोषणा ADT7470_REG_CFG_2			0x74
#घोषणा ADT7470_REG_ACOUSTICS12			0x75
#घोषणा ADT7470_REG_ACOUSTICS34			0x76
#घोषणा ADT7470_REG_DEVICE			0x3D
#घोषणा ADT7470_REG_VENDOR			0x3E
#घोषणा ADT7470_REG_REVISION			0x3F
#घोषणा ADT7470_REG_ALARM1_MASK			0x72
#घोषणा ADT7470_REG_ALARM2_MASK			0x73
#घोषणा ADT7470_REG_PWM_AUTO_TEMP_BASE_ADDR	0x7C
#घोषणा ADT7470_REG_PWM_AUTO_TEMP_MAX_ADDR	0x7D
#घोषणा ADT7470_REG_MAX_ADDR			0x81

#घोषणा ADT7470_TEMP_COUNT	10
#घोषणा ADT7470_TEMP_REG(x)	(ADT7470_REG_TEMP_BASE_ADDR + (x))
#घोषणा ADT7470_TEMP_MIN_REG(x) (ADT7470_REG_TEMP_LIMITS_BASE_ADDR + ((x) * 2))
#घोषणा ADT7470_TEMP_MAX_REG(x) (ADT7470_REG_TEMP_LIMITS_BASE_ADDR + \
				((x) * 2) + 1)

#घोषणा ADT7470_FAN_COUNT	4
#घोषणा ADT7470_REG_FAN(x)	(ADT7470_REG_FAN_BASE_ADDR + ((x) * 2))
#घोषणा ADT7470_REG_FAN_MIN(x)	(ADT7470_REG_FAN_MIN_BASE_ADDR + ((x) * 2))
#घोषणा ADT7470_REG_FAN_MAX(x)	(ADT7470_REG_FAN_MAX_BASE_ADDR + ((x) * 2))

#घोषणा ADT7470_PWM_COUNT	4
#घोषणा ADT7470_REG_PWM(x)	(ADT7470_REG_PWM_BASE_ADDR + (x))
#घोषणा ADT7470_REG_PWM_MAX(x)	(ADT7470_REG_PWM_MAX_BASE_ADDR + (x))
#घोषणा ADT7470_REG_PWM_MIN(x)	(ADT7470_REG_PWM_MIN_BASE_ADDR + (x))
#घोषणा ADT7470_REG_PWM_TMIN(x)	(ADT7470_REG_PWM_TEMP_MIN_BASE_ADDR + (x))
#घोषणा ADT7470_REG_PWM_CFG(x)	(ADT7470_REG_PWM_CFG_BASE_ADDR + ((x) / 2))
#घोषणा ADT7470_REG_PWM_AUTO_TEMP(x)	(ADT7470_REG_PWM_AUTO_TEMP_BASE_ADDR + \
					((x) / 2))

#घोषणा ALARM2(x)		((x) << 8)

#घोषणा ADT7470_VENDOR		0x41
#घोषणा ADT7470_DEVICE		0x70
/* datasheet only mentions a revision 2 */
#घोषणा ADT7470_REVISION	0x02

/* "all temps" according to hwmon sysfs पूर्णांकerface spec */
#घोषणा ADT7470_PWM_ALL_TEMPS	0x3FF

/* How often करो we reपढ़ो sensors values? (In jअगरfies) */
#घोषणा SENSOR_REFRESH_INTERVAL	(5 * HZ)

/* How often करो we reपढ़ो sensor limit values? (In jअगरfies) */
#घोषणा LIMIT_REFRESH_INTERVAL	(60 * HZ)

/* Wait at least 200ms per sensor क्रम 10 sensors */
#घोषणा TEMP_COLLECTION_TIME	2000

/* स्वतः update thing won't fire more than every 2s */
#घोषणा AUTO_UPDATE_INTERVAL	2000

/* datasheet says to भागide this number by the fan पढ़ोing to get fan rpm */
#घोषणा FAN_PERIOD_TO_RPM(x)	((90000 * 60) / (x))
#घोषणा FAN_RPM_TO_PERIOD	FAN_PERIOD_TO_RPM
#घोषणा FAN_PERIOD_INVALID	65535
#घोषणा FAN_DATA_VALID(x)	((x) && (x) != FAN_PERIOD_INVALID)

/* Config रेजिस्टरs 1 and 2 include fields क्रम selecting the PWM frequency */
#घोषणा ADT7470_CFG_LF		0x40
#घोषणा ADT7470_FREQ_MASK	0x70
#घोषणा ADT7470_FREQ_SHIFT	4

काष्ठा adt7470_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		lock;
	अक्षर			sensors_valid;
	अक्षर			limits_valid;
	अचिन्हित दीर्घ		sensors_last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ		limits_last_updated;	/* In jअगरfies */

	पूर्णांक			num_temp_sensors;	/* -1 = probe */
	पूर्णांक			temperatures_probed;

	s8			temp[ADT7470_TEMP_COUNT];
	s8			temp_min[ADT7470_TEMP_COUNT];
	s8			temp_max[ADT7470_TEMP_COUNT];
	u16			fan[ADT7470_FAN_COUNT];
	u16			fan_min[ADT7470_FAN_COUNT];
	u16			fan_max[ADT7470_FAN_COUNT];
	u16			alarm;
	u16			alarms_mask;
	u8			क्रमce_pwm_max;
	u8			pwm[ADT7470_PWM_COUNT];
	u8			pwm_max[ADT7470_PWM_COUNT];
	u8			pwm_स्वतःmatic[ADT7470_PWM_COUNT];
	u8			pwm_min[ADT7470_PWM_COUNT];
	s8			pwm_पंचांगin[ADT7470_PWM_COUNT];
	u8			pwm_स्वतः_temp[ADT7470_PWM_COUNT];

	काष्ठा task_काष्ठा	*स्वतः_update;
	अचिन्हित पूर्णांक		स्वतः_update_पूर्णांकerval;
पूर्ण;

/*
 * 16-bit रेजिस्टरs on the ADT7470 are low-byte first.  The data sheet says
 * that the low byte must be पढ़ो beक्रमe the high byte.
 */
अटल अंतरभूत पूर्णांक adt7470_पढ़ो_word_data(काष्ठा i2c_client *client, u8 reg)
अणु
	u16 foo;
	foo = i2c_smbus_पढ़ो_byte_data(client, reg);
	foo |= ((u16)i2c_smbus_पढ़ो_byte_data(client, reg + 1) << 8);
	वापस foo;
पूर्ण

अटल अंतरभूत पूर्णांक adt7470_ग_लिखो_word_data(काष्ठा i2c_client *client, u8 reg,
					  u16 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value & 0xFF)
	       || i2c_smbus_ग_लिखो_byte_data(client, reg + 1, value >> 8);
पूर्ण

/* Probe क्रम temperature sensors.  Assumes lock is held */
अटल पूर्णांक adt7470_पढ़ो_temperatures(काष्ठा i2c_client *client,
				     काष्ठा adt7470_data *data)
अणु
	अचिन्हित दीर्घ res;
	पूर्णांक i;
	u8 cfg, pwm[4], pwm_cfg[2];

	/* save pwm[1-4] config रेजिस्टर */
	pwm_cfg[0] = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_PWM_CFG(0));
	pwm_cfg[1] = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_PWM_CFG(2));

	/* set manual pwm to whatever it is set to now */
	क्रम (i = 0; i < ADT7470_FAN_COUNT; i++)
		pwm[i] = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_PWM(i));

	/* put pwm in manual mode */
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM_CFG(0),
		pwm_cfg[0] & ~(ADT7470_PWM_AUTO_MASK));
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM_CFG(2),
		pwm_cfg[1] & ~(ADT7470_PWM_AUTO_MASK));

	/* ग_लिखो pwm control to whatever it was */
	क्रम (i = 0; i < ADT7470_FAN_COUNT; i++)
		i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM(i), pwm[i]);

	/* start पढ़ोing temperature sensors */
	cfg = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_CFG);
	cfg |= 0x80;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_CFG, cfg);

	/* Delay is 200ms * number of temp sensors. */
	res = msleep_पूर्णांकerruptible((data->num_temp_sensors >= 0 ?
				    data->num_temp_sensors * 200 :
				    TEMP_COLLECTION_TIME));

	/* करोne पढ़ोing temperature sensors */
	cfg = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_CFG);
	cfg &= ~0x80;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_CFG, cfg);

	/* restore pwm[1-4] config रेजिस्टरs */
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM_CFG(0), pwm_cfg[0]);
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM_CFG(2), pwm_cfg[1]);

	अगर (res) अणु
		pr_err("ha ha, interrupted\n");
		वापस -EAGAIN;
	पूर्ण

	/* Only count fans अगर we have to */
	अगर (data->num_temp_sensors >= 0)
		वापस 0;

	क्रम (i = 0; i < ADT7470_TEMP_COUNT; i++) अणु
		data->temp[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_TEMP_REG(i));
		अगर (data->temp[i])
			data->num_temp_sensors = i + 1;
	पूर्ण
	data->temperatures_probed = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक adt7470_update_thपढ़ो(व्योम *p)
अणु
	काष्ठा i2c_client *client = p;
	काष्ठा adt7470_data *data = i2c_get_clientdata(client);

	जबतक (!kthपढ़ो_should_stop()) अणु
		mutex_lock(&data->lock);
		adt7470_पढ़ो_temperatures(client, data);
		mutex_unlock(&data->lock);

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		schedule_समयout(msecs_to_jअगरfies(data->स्वतः_update_पूर्णांकerval));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adt7470_update_sensors(काष्ठा adt7470_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	u8 cfg;
	पूर्णांक i;

	अगर (!data->temperatures_probed)
		adt7470_पढ़ो_temperatures(client, data);
	अन्यथा
		क्रम (i = 0; i < ADT7470_TEMP_COUNT; i++)
			data->temp[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_TEMP_REG(i));

	क्रम (i = 0; i < ADT7470_FAN_COUNT; i++)
		data->fan[i] = adt7470_पढ़ो_word_data(client,
						ADT7470_REG_FAN(i));

	क्रम (i = 0; i < ADT7470_PWM_COUNT; i++) अणु
		पूर्णांक reg;
		पूर्णांक reg_mask;

		data->pwm[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_REG_PWM(i));

		अगर (i % 2)
			reg_mask = ADT7470_PWM2_AUTO_MASK;
		अन्यथा
			reg_mask = ADT7470_PWM1_AUTO_MASK;

		reg = ADT7470_REG_PWM_CFG(i);
		अगर (i2c_smbus_पढ़ो_byte_data(client, reg) & reg_mask)
			data->pwm_स्वतःmatic[i] = 1;
		अन्यथा
			data->pwm_स्वतःmatic[i] = 0;

		reg = ADT7470_REG_PWM_AUTO_TEMP(i);
		cfg = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (!(i % 2))
			data->pwm_स्वतः_temp[i] = cfg >> 4;
		अन्यथा
			data->pwm_स्वतः_temp[i] = cfg & 0xF;
	पूर्ण

	अगर (i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_CFG) &
	    ADT7470_FSPD_MASK)
		data->क्रमce_pwm_max = 1;
	अन्यथा
		data->क्रमce_pwm_max = 0;

	data->alarm = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_ALARM1);
	अगर (data->alarm & ADT7470_OOL_ALARM)
		data->alarm |= ALARM2(i2c_smbus_पढ़ो_byte_data(client,
							ADT7470_REG_ALARM2));
	data->alarms_mask = adt7470_पढ़ो_word_data(client,
						   ADT7470_REG_ALARM1_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक adt7470_update_limits(काष्ठा adt7470_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;

	क्रम (i = 0; i < ADT7470_TEMP_COUNT; i++) अणु
		data->temp_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_TEMP_MIN_REG(i));
		data->temp_max[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_TEMP_MAX_REG(i));
	पूर्ण

	क्रम (i = 0; i < ADT7470_FAN_COUNT; i++) अणु
		data->fan_min[i] = adt7470_पढ़ो_word_data(client,
						ADT7470_REG_FAN_MIN(i));
		data->fan_max[i] = adt7470_पढ़ो_word_data(client,
						ADT7470_REG_FAN_MAX(i));
	पूर्ण

	क्रम (i = 0; i < ADT7470_PWM_COUNT; i++) अणु
		data->pwm_max[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_REG_PWM_MAX(i));
		data->pwm_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_REG_PWM_MIN(i));
		data->pwm_पंचांगin[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7470_REG_PWM_TMIN(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा adt7470_data *adt7470_update_device(काष्ठा device *dev)
अणु
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ local_jअगरfies = jअगरfies;
	पूर्णांक need_sensors = 1;
	पूर्णांक need_limits = 1;
	पूर्णांक err;

	/*
	 * Figure out अगर we need to update the shaकरोw रेजिस्टरs.
	 * Lockless means that we may occasionally report out of
	 * date data.
	 */
	अगर (समय_beक्रमe(local_jअगरfies, data->sensors_last_updated +
			SENSOR_REFRESH_INTERVAL) &&
	    data->sensors_valid)
		need_sensors = 0;

	अगर (समय_beक्रमe(local_jअगरfies, data->limits_last_updated +
			LIMIT_REFRESH_INTERVAL) &&
	    data->limits_valid)
		need_limits = 0;

	अगर (!need_sensors && !need_limits)
		वापस data;

	mutex_lock(&data->lock);
	अगर (need_sensors) अणु
		err = adt7470_update_sensors(data);
		अगर (err < 0)
			जाओ out;
		data->sensors_last_updated = local_jअगरfies;
		data->sensors_valid = 1;
	पूर्ण

	अगर (need_limits) अणु
		err = adt7470_update_limits(data);
		अगर (err < 0)
			जाओ out;
		data->limits_last_updated = local_jअगरfies;
		data->limits_valid = 1;
	पूर्ण
out:
	mutex_unlock(&data->lock);

	वापस err < 0 ? ERR_PTR(err) : data;
पूर्ण

अटल sमाप_प्रकार स्वतः_update_पूर्णांकerval_show(काष्ठा device *dev,
					 काष्ठा device_attribute *devattr,
					 अक्षर *buf)
अणु
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->स्वतः_update_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार स्वतः_update_पूर्णांकerval_store(काष्ठा device *dev,
					  काष्ठा device_attribute *devattr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 60000);

	mutex_lock(&data->lock);
	data->स्वतः_update_पूर्णांकerval = temp;
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार num_temp_sensors_show(काष्ठा device *dev,
				     काष्ठा device_attribute *devattr,
				     अक्षर *buf)
अणु
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->num_temp_sensors);
पूर्ण

अटल sमाप_प्रकार num_temp_sensors_store(काष्ठा device *dev,
				      काष्ठा device_attribute *devattr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, -1, 10);

	mutex_lock(&data->lock);
	data->num_temp_sensors = temp;
	अगर (temp < 0)
		data->temperatures_probed = 0;
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", 1000 * data->temp_min[attr->index]);
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, -128000, 127000);
	temp = DIV_ROUND_CLOSEST(temp, 1000);

	mutex_lock(&data->lock);
	data->temp_min[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_TEMP_MIN_REG(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", 1000 * data->temp_max[attr->index]);
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, -128000, 127000);
	temp = DIV_ROUND_CLOSEST(temp, 1000);

	mutex_lock(&data->lock);
	data->temp_max[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_TEMP_MAX_REG(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", 1000 * data->temp[attr->index]);
पूर्ण

अटल sमाप_प्रकार alarm_mask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr,
			   अक्षर *buf)
अणु
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%x\n", data->alarms_mask);
पूर्ण

अटल sमाप_प्रकार alarm_mask_store(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	दीर्घ mask;

	अगर (kम_से_अदीर्घ(buf, 0, &mask))
		वापस -EINVAL;

	अगर (mask & ~0xffff)
		वापस -EINVAL;

	mutex_lock(&data->lock);
	data->alarms_mask = mask;
	adt7470_ग_लिखो_word_data(data->client, ADT7470_REG_ALARM1_MASK, mask);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_max_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (FAN_DATA_VALID(data->fan_max[attr->index]))
		वापस प्र_लिखो(buf, "%d\n",
			       FAN_PERIOD_TO_RPM(data->fan_max[attr->index]));
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार fan_max_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp) || !temp)
		वापस -EINVAL;

	temp = FAN_RPM_TO_PERIOD(temp);
	temp = clamp_val(temp, 1, 65534);

	mutex_lock(&data->lock);
	data->fan_max[attr->index] = temp;
	adt7470_ग_लिखो_word_data(client, ADT7470_REG_FAN_MAX(attr->index), temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (FAN_DATA_VALID(data->fan_min[attr->index]))
		वापस प्र_लिखो(buf, "%d\n",
			       FAN_PERIOD_TO_RPM(data->fan_min[attr->index]));
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp) || !temp)
		वापस -EINVAL;

	temp = FAN_RPM_TO_PERIOD(temp);
	temp = clamp_val(temp, 1, 65534);

	mutex_lock(&data->lock);
	data->fan_min[attr->index] = temp;
	adt7470_ग_लिखो_word_data(client, ADT7470_REG_FAN_MIN(attr->index), temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (FAN_DATA_VALID(data->fan[attr->index]))
		वापस प्र_लिखो(buf, "%d\n",
			       FAN_PERIOD_TO_RPM(data->fan[attr->index]));
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार क्रमce_pwm_max_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->क्रमce_pwm_max);
पूर्ण

अटल sमाप_प्रकार क्रमce_pwm_max_store(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;
	u8 reg;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	mutex_lock(&data->lock);
	data->क्रमce_pwm_max = temp;
	reg = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_CFG);
	अगर (temp)
		reg |= ADT7470_FSPD_MASK;
	अन्यथा
		reg &= ~ADT7470_FSPD_MASK;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_CFG, reg);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->pwm[attr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255);

	mutex_lock(&data->lock);
	data->pwm[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM(attr->index), temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

/* These are the valid PWM frequencies to the nearest Hz */
अटल स्थिर पूर्णांक adt7470_freq_map[] = अणु
	11, 15, 22, 29, 35, 44, 59, 88, 1400, 22500
पूर्ण;

अटल sमाप_प्रकार pwm1_freq_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा adt7470_data *data = adt7470_update_device(dev);
	अचिन्हित अक्षर cfg_reg_1;
	अचिन्हित अक्षर cfg_reg_2;
	पूर्णांक index;

	mutex_lock(&data->lock);
	cfg_reg_1 = i2c_smbus_पढ़ो_byte_data(data->client, ADT7470_REG_CFG);
	cfg_reg_2 = i2c_smbus_पढ़ो_byte_data(data->client, ADT7470_REG_CFG_2);
	mutex_unlock(&data->lock);

	index = (cfg_reg_2 & ADT7470_FREQ_MASK) >> ADT7470_FREQ_SHIFT;
	अगर (!(cfg_reg_1 & ADT7470_CFG_LF))
		index += 8;
	अगर (index >= ARRAY_SIZE(adt7470_freq_map))
		index = ARRAY_SIZE(adt7470_freq_map) - 1;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", adt7470_freq_map[index]);
पूर्ण

अटल sमाप_प्रकार pwm1_freq_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ freq;
	पूर्णांक index;
	पूर्णांक low_freq = ADT7470_CFG_LF;
	अचिन्हित अक्षर val;

	अगर (kम_से_दीर्घ(buf, 10, &freq))
		वापस -EINVAL;

	/* Round the user value given to the बंदst available frequency */
	index = find_बंदst(freq, adt7470_freq_map,
			     ARRAY_SIZE(adt7470_freq_map));

	अगर (index >= 8) अणु
		index -= 8;
		low_freq = 0;
	पूर्ण

	mutex_lock(&data->lock);
	/* Configuration Register 1 */
	val = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_CFG);
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_CFG,
				  (val & ~ADT7470_CFG_LF) | low_freq);
	/* Configuration Register 2 */
	val = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_CFG_2);
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_CFG_2,
		(val & ~ADT7470_FREQ_MASK) | (index << ADT7470_FREQ_SHIFT));
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_max_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->pwm_max[attr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_max_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255);

	mutex_lock(&data->lock);
	data->pwm_max[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM_MAX(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_min_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->pwm_min[attr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255);

	mutex_lock(&data->lock);
	data->pwm_min[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM_MIN(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_पंचांगax_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	/* the datasheet says that पंचांगax = पंचांगin + 20C */
	वापस प्र_लिखो(buf, "%d\n", 1000 * (20 + data->pwm_पंचांगin[attr->index]));
पूर्ण

अटल sमाप_प्रकार pwm_पंचांगin_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", 1000 * data->pwm_पंचांगin[attr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_पंचांगin_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, -128000, 127000);
	temp = DIV_ROUND_CLOSEST(temp, 1000);

	mutex_lock(&data->lock);
	data->pwm_पंचांगin[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_PWM_TMIN(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", 1 + data->pwm_स्वतःmatic[attr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक pwm_स्वतः_reg = ADT7470_REG_PWM_CFG(attr->index);
	पूर्णांक pwm_स्वतः_reg_mask;
	दीर्घ temp;
	u8 reg;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	अगर (attr->index % 2)
		pwm_स्वतः_reg_mask = ADT7470_PWM2_AUTO_MASK;
	अन्यथा
		pwm_स्वतः_reg_mask = ADT7470_PWM1_AUTO_MASK;

	अगर (temp != 2 && temp != 1)
		वापस -EINVAL;
	temp--;

	mutex_lock(&data->lock);
	data->pwm_स्वतःmatic[attr->index] = temp;
	reg = i2c_smbus_पढ़ो_byte_data(client, pwm_स्वतः_reg);
	अगर (temp)
		reg |= pwm_स्वतः_reg_mask;
	अन्यथा
		reg &= ~pwm_स्वतः_reg_mask;
	i2c_smbus_ग_लिखो_byte_data(client, pwm_स्वतः_reg, reg);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_temp_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);
	u8 ctrl;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	ctrl = data->pwm_स्वतः_temp[attr->index];
	अगर (ctrl)
		वापस प्र_लिखो(buf, "%d\n", 1 << (ctrl - 1));
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", ADT7470_PWM_ALL_TEMPS);
पूर्ण

अटल पूर्णांक cvt_स्वतः_temp(पूर्णांक input)
अणु
	अगर (input == ADT7470_PWM_ALL_TEMPS)
		वापस 0;
	अगर (input < 1 || !is_घातer_of_2(input))
		वापस -EINVAL;
	वापस ilog2(input) + 1;
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_temp_store(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक pwm_स्वतः_reg = ADT7470_REG_PWM_AUTO_TEMP(attr->index);
	दीर्घ temp;
	u8 reg;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = cvt_स्वतः_temp(temp);
	अगर (temp < 0)
		वापस temp;

	mutex_lock(&data->lock);
	data->pwm_स्वतःmatic[attr->index] = temp;
	reg = i2c_smbus_पढ़ो_byte_data(client, pwm_स्वतः_reg);

	अगर (!(attr->index % 2)) अणु
		reg &= 0xF;
		reg |= (temp << 4) & 0xF0;
	पूर्ण अन्यथा अणु
		reg &= 0xF0;
		reg |= temp & 0xF;
	पूर्ण

	i2c_smbus_ग_लिखो_byte_data(client, pwm_स्वतः_reg, reg);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7470_data *data = adt7470_update_device(dev);

	अगर (data->alarm & attr->index)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल DEVICE_ATTR_RW(alarm_mask);
अटल DEVICE_ATTR_RW(num_temp_sensors);
अटल DEVICE_ATTR_RW(स्वतः_update_पूर्णांकerval);

अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max, temp_max, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp5_max, temp_max, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp6_max, temp_max, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp7_max, temp_max, 6);
अटल SENSOR_DEVICE_ATTR_RW(temp8_max, temp_max, 7);
अटल SENSOR_DEVICE_ATTR_RW(temp9_max, temp_max, 8);
अटल SENSOR_DEVICE_ATTR_RW(temp10_max, temp_max, 9);

अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_min, temp_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp5_min, temp_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp6_min, temp_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp7_min, temp_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(temp8_min, temp_min, 7);
अटल SENSOR_DEVICE_ATTR_RW(temp9_min, temp_min, 8);
अटल SENSOR_DEVICE_ATTR_RW(temp10_min, temp_min, 9);

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_input, temp, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_input, temp, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp7_input, temp, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp8_input, temp, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp9_input, temp, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp10_input, temp, 9);

अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, ADT7470_R1T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, ADT7470_R2T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, ADT7470_R3T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp4_alarm, alarm, ADT7470_R4T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp5_alarm, alarm, ADT7470_R5T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp6_alarm, alarm, ADT7470_R6T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp7_alarm, alarm, ADT7470_R7T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp8_alarm, alarm, ALARM2(ADT7470_R8T_ALARM));
अटल SENSOR_DEVICE_ATTR_RO(temp9_alarm, alarm, ALARM2(ADT7470_R9T_ALARM));
अटल SENSOR_DEVICE_ATTR_RO(temp10_alarm, alarm, ALARM2(ADT7470_R10T_ALARM));

अटल SENSOR_DEVICE_ATTR_RW(fan1_max, fan_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_max, fan_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_max, fan_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_max, fan_max, 3);

अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_min, fan_min, 3);

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, fan, 3);

अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, ALARM2(ADT7470_FAN1_ALARM));
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, ALARM2(ADT7470_FAN2_ALARM));
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, alarm, ALARM2(ADT7470_FAN3_ALARM));
अटल SENSOR_DEVICE_ATTR_RO(fan4_alarm, alarm, ALARM2(ADT7470_FAN4_ALARM));

अटल SENSOR_DEVICE_ATTR_RW(क्रमce_pwm_max, क्रमce_pwm_max, 0);

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4, pwm, 3);

अटल DEVICE_ATTR_RW(pwm1_freq);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक1_pwm, pwm_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक1_pwm, pwm_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक1_pwm, pwm_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_स्वतः_poपूर्णांक1_pwm, pwm_min, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक2_pwm, pwm_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक2_pwm, pwm_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक2_pwm, pwm_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_स्वतः_poपूर्णांक2_pwm, pwm_max, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 3);

अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 0);
अटल SENSOR_DEVICE_ATTR_RO(pwm2_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 1);
अटल SENSOR_DEVICE_ATTR_RO(pwm3_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 2);
अटल SENSOR_DEVICE_ATTR_RO(pwm4_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_स्वतः, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_स्वतः, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_enable, pwm_स्वतः, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_enable, pwm_स्वतः, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_channels_temp, pwm_स्वतः_temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_channels_temp, pwm_स्वतः_temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_channels_temp, pwm_स्वतः_temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_स्वतः_channels_temp, pwm_स्वतः_temp, 3);

अटल काष्ठा attribute *adt7470_attrs[] = अणु
	&dev_attr_alarm_mask.attr,
	&dev_attr_num_temp_sensors.attr,
	&dev_attr_स्वतः_update_पूर्णांकerval.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp5_max.dev_attr.attr,
	&sensor_dev_attr_temp6_max.dev_attr.attr,
	&sensor_dev_attr_temp7_max.dev_attr.attr,
	&sensor_dev_attr_temp8_max.dev_attr.attr,
	&sensor_dev_attr_temp9_max.dev_attr.attr,
	&sensor_dev_attr_temp10_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp4_min.dev_attr.attr,
	&sensor_dev_attr_temp5_min.dev_attr.attr,
	&sensor_dev_attr_temp6_min.dev_attr.attr,
	&sensor_dev_attr_temp7_min.dev_attr.attr,
	&sensor_dev_attr_temp8_min.dev_attr.attr,
	&sensor_dev_attr_temp9_min.dev_attr.attr,
	&sensor_dev_attr_temp10_min.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp5_input.dev_attr.attr,
	&sensor_dev_attr_temp6_input.dev_attr.attr,
	&sensor_dev_attr_temp7_input.dev_attr.attr,
	&sensor_dev_attr_temp8_input.dev_attr.attr,
	&sensor_dev_attr_temp9_input.dev_attr.attr,
	&sensor_dev_attr_temp10_input.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_alarm.dev_attr.attr,
	&sensor_dev_attr_temp6_alarm.dev_attr.attr,
	&sensor_dev_attr_temp7_alarm.dev_attr.attr,
	&sensor_dev_attr_temp8_alarm.dev_attr.attr,
	&sensor_dev_attr_temp9_alarm.dev_attr.attr,
	&sensor_dev_attr_temp10_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_max.dev_attr.attr,
	&sensor_dev_attr_fan2_max.dev_attr.attr,
	&sensor_dev_attr_fan3_max.dev_attr.attr,
	&sensor_dev_attr_fan4_max.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,
	&sensor_dev_attr_क्रमce_pwm_max.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&dev_attr_pwm1_freq.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm4.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm4_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_channels_temp.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(adt7470);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adt7470_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक venकरोr, device, revision;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	venकरोr = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_VENDOR);
	अगर (venकरोr != ADT7470_VENDOR)
		वापस -ENODEV;

	device = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_DEVICE);
	अगर (device != ADT7470_DEVICE)
		वापस -ENODEV;

	revision = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_REVISION);
	अगर (revision != ADT7470_REVISION)
		वापस -ENODEV;

	strlcpy(info->type, "adt7470", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम adt7470_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक reg = i2c_smbus_पढ़ो_byte_data(client, ADT7470_REG_CFG);

	अगर (reg < 0) अणु
		dev_err(&client->dev, "cannot read configuration register\n");
	पूर्ण अन्यथा अणु
		/* start monitoring (and करो a self-test) */
		i2c_smbus_ग_लिखो_byte_data(client, ADT7470_REG_CFG, reg | 3);
	पूर्ण
पूर्ण

अटल पूर्णांक adt7470_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा adt7470_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा adt7470_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->num_temp_sensors = -1;
	data->स्वतः_update_पूर्णांकerval = AUTO_UPDATE_INTERVAL;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->lock);

	dev_info(&client->dev, "%s chip found\n", client->name);

	/* Initialize the ADT7470 chip */
	adt7470_init_client(client);

	/* Register sysfs hooks */
	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   adt7470_groups);

	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	data->स्वतः_update = kthपढ़ो_run(adt7470_update_thपढ़ो, client, "%s",
					dev_name(hwmon_dev));
	अगर (IS_ERR(data->स्वतः_update)) अणु
		वापस PTR_ERR(data->स्वतः_update);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adt7470_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा adt7470_data *data = i2c_get_clientdata(client);

	kthपढ़ो_stop(data->स्वतः_update);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adt7470_id[] = अणु
	अणु "adt7470", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adt7470_id);

अटल काष्ठा i2c_driver adt7470_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adt7470",
	पूर्ण,
	.probe_new	= adt7470_probe,
	.हटाओ		= adt7470_हटाओ,
	.id_table	= adt7470_id,
	.detect		= adt7470_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adt7470_driver);

MODULE_AUTHOR("Darrick J. Wong <darrick.wong@oracle.com>");
MODULE_DESCRIPTION("ADT7470 driver");
MODULE_LICENSE("GPL");
