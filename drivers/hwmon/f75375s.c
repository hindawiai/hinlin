<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * f75375s.c - driver क्रम the Fपूर्णांकek F75375/SP, F75373 and
 *             F75387SG/RG hardware monitoring features
 * Copyright (C) 2006-2007  Riku Voipio
 *
 * Datasheets available at:
 *
 * f75375:
 * http://www.fपूर्णांकek.com.tw/files/productfiles/F75375_V026P.pdf
 *
 * f75373:
 * http://www.fपूर्णांकek.com.tw/files/productfiles/F75373_V025P.pdf
 *
 * f75387:
 * http://www.fपूर्णांकek.com.tw/files/productfiles/F75387_V027P.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/f75375s.h>
#समावेश <linux/slab.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु f75373, f75375, f75387 पूर्ण;

/* Fपूर्णांकek F75375 रेजिस्टरs  */
#घोषणा F75375_REG_CONFIG0		0x0
#घोषणा F75375_REG_CONFIG1		0x1
#घोषणा F75375_REG_CONFIG2		0x2
#घोषणा F75375_REG_CONFIG3		0x3
#घोषणा F75375_REG_ADDR			0x4
#घोषणा F75375_REG_INTR			0x31
#घोषणा F75375_CHIP_ID			0x5A
#घोषणा F75375_REG_VERSION		0x5C
#घोषणा F75375_REG_VENDOR		0x5D
#घोषणा F75375_REG_FAN_TIMER		0x60

#घोषणा F75375_REG_VOLT(nr)		(0x10 + (nr))
#घोषणा F75375_REG_VOLT_HIGH(nr)	(0x20 + (nr) * 2)
#घोषणा F75375_REG_VOLT_LOW(nr)		(0x21 + (nr) * 2)

#घोषणा F75375_REG_TEMP(nr)		(0x14 + (nr))
#घोषणा F75387_REG_TEMP11_LSB(nr)	(0x1a + (nr))
#घोषणा F75375_REG_TEMP_HIGH(nr)	(0x28 + (nr) * 2)
#घोषणा F75375_REG_TEMP_HYST(nr)	(0x29 + (nr) * 2)

#घोषणा F75375_REG_FAN(nr)		(0x16 + (nr) * 2)
#घोषणा F75375_REG_FAN_MIN(nr)		(0x2C + (nr) * 2)
#घोषणा F75375_REG_FAN_FULL(nr)		(0x70 + (nr) * 0x10)
#घोषणा F75375_REG_FAN_PWM_DUTY(nr)	(0x76 + (nr) * 0x10)
#घोषणा F75375_REG_FAN_PWM_CLOCK(nr)	(0x7D + (nr) * 0x10)

#घोषणा F75375_REG_FAN_EXP(nr)		(0x74 + (nr) * 0x10)
#घोषणा F75375_REG_FAN_B_TEMP(nr, step)	((0xA0 + (nr) * 0x10) + (step))
#घोषणा F75375_REG_FAN_B_SPEED(nr, step) \
	((0xA5 + (nr) * 0x10) + (step) * 2)

#घोषणा F75375_REG_PWM1_RAISE_DUTY	0x69
#घोषणा F75375_REG_PWM2_RAISE_DUTY	0x6A
#घोषणा F75375_REG_PWM1_DROP_DUTY	0x6B
#घोषणा F75375_REG_PWM2_DROP_DUTY	0x6C

#घोषणा F75375_FAN_CTRL_LINEAR(nr)	(4 + nr)
#घोषणा F75387_FAN_CTRL_LINEAR(nr)	(1 + ((nr) * 4))
#घोषणा FAN_CTRL_MODE(nr)		(4 + ((nr) * 2))
#घोषणा F75387_FAN_DUTY_MODE(nr)	(2 + ((nr) * 4))
#घोषणा F75387_FAN_MANU_MODE(nr)	((nr) * 4)

/*
 * Data काष्ठाures and manipulation thereof
 */

काष्ठा f75375_data अणु
	अचिन्हित लघु addr;
	काष्ठा device *hwmon_dev;

	स्थिर अक्षर *name;
	पूर्णांक kind;
	काष्ठा mutex update_lock; /* protect रेजिस्टर access */
	अक्षर valid;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ last_limits;	/* In jअगरfies */

	/* Register values */
	u8 in[4];
	u8 in_max[4];
	u8 in_min[4];
	u16 fan[2];
	u16 fan_min[2];
	u16 fan_max[2];
	u16 fan_target[2];
	u8 fan_समयr;
	u8 pwm[2];
	u8 pwm_mode[2];
	u8 pwm_enable[2];
	/*
	 * f75387: For remote temperature पढ़ोing, it uses चिन्हित 11-bit
	 * values with LSB = 0.125 degree Celsius, left-justअगरied in 16-bit
	 * रेजिस्टरs. For original 8-bit temp पढ़ोings, the LSB just is 0.
	 */
	s16 temp11[2];
	s8 temp_high[2];
	s8 temp_max_hyst[2];
पूर्ण;

अटल पूर्णांक f75375_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info);
अटल पूर्णांक f75375_probe(काष्ठा i2c_client *client);
अटल पूर्णांक f75375_हटाओ(काष्ठा i2c_client *client);

अटल स्थिर काष्ठा i2c_device_id f75375_id[] = अणु
	अणु "f75373", f75373 पूर्ण,
	अणु "f75375", f75375 पूर्ण,
	अणु "f75387", f75387 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, f75375_id);

अटल काष्ठा i2c_driver f75375_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "f75375",
	पूर्ण,
	.probe_new = f75375_probe,
	.हटाओ = f75375_हटाओ,
	.id_table = f75375_id,
	.detect = f75375_detect,
	.address_list = normal_i2c,
पूर्ण;

अटल अंतरभूत पूर्णांक f75375_पढ़ो8(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

/* in most हालs, should be called जबतक holding update_lock */
अटल अंतरभूत u16 f75375_पढ़ो16(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस (i2c_smbus_पढ़ो_byte_data(client, reg) << 8)
		| i2c_smbus_पढ़ो_byte_data(client, reg + 1);
पूर्ण

अटल अंतरभूत व्योम f75375_ग_लिखो8(काष्ठा i2c_client *client, u8 reg,
		u8 value)
अणु
	i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल अंतरभूत व्योम f75375_ग_लिखो16(काष्ठा i2c_client *client, u8 reg,
		u16 value)
अणु
	पूर्णांक err = i2c_smbus_ग_लिखो_byte_data(client, reg, (value >> 8));
	अगर (err)
		वापस;
	i2c_smbus_ग_लिखो_byte_data(client, reg + 1, (value & 0xFF));
पूर्ण

अटल व्योम f75375_ग_लिखो_pwm(काष्ठा i2c_client *client, पूर्णांक nr)
अणु
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अगर (data->kind == f75387)
		f75375_ग_लिखो16(client, F75375_REG_FAN_EXP(nr), data->pwm[nr]);
	अन्यथा
		f75375_ग_लिखो8(client, F75375_REG_FAN_PWM_DUTY(nr),
			      data->pwm[nr]);
पूर्ण

अटल काष्ठा f75375_data *f75375_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	पूर्णांक nr;

	mutex_lock(&data->update_lock);

	/* Limit रेजिस्टरs cache is refreshed after 60 seconds */
	अगर (समय_after(jअगरfies, data->last_limits + 60 * HZ)
		|| !data->valid) अणु
		क्रम (nr = 0; nr < 2; nr++) अणु
			data->temp_high[nr] =
				f75375_पढ़ो8(client, F75375_REG_TEMP_HIGH(nr));
			data->temp_max_hyst[nr] =
				f75375_पढ़ो8(client, F75375_REG_TEMP_HYST(nr));
			data->fan_max[nr] =
				f75375_पढ़ो16(client, F75375_REG_FAN_FULL(nr));
			data->fan_min[nr] =
				f75375_पढ़ो16(client, F75375_REG_FAN_MIN(nr));
			data->fan_target[nr] =
				f75375_पढ़ो16(client, F75375_REG_FAN_EXP(nr));
		पूर्ण
		क्रम (nr = 0; nr < 4; nr++) अणु
			data->in_max[nr] =
				f75375_पढ़ो8(client, F75375_REG_VOLT_HIGH(nr));
			data->in_min[nr] =
				f75375_पढ़ो8(client, F75375_REG_VOLT_LOW(nr));
		पूर्ण
		data->fan_समयr = f75375_पढ़ो8(client, F75375_REG_FAN_TIMER);
		data->last_limits = jअगरfies;
	पूर्ण

	/* Measurement रेजिस्टरs cache is refreshed after 2 second */
	अगर (समय_after(jअगरfies, data->last_updated + 2 * HZ)
		|| !data->valid) अणु
		क्रम (nr = 0; nr < 2; nr++) अणु
			data->pwm[nr] =	f75375_पढ़ो8(client,
				F75375_REG_FAN_PWM_DUTY(nr));
			/* assign MSB, thereक्रमe shअगरt it by 8 bits */
			data->temp11[nr] =
				f75375_पढ़ो8(client, F75375_REG_TEMP(nr)) << 8;
			अगर (data->kind == f75387)
				/* merge F75387's temperature LSB (11-bit) */
				data->temp11[nr] |=
					f75375_पढ़ो8(client,
						     F75387_REG_TEMP11_LSB(nr));
			data->fan[nr] =
				f75375_पढ़ो16(client, F75375_REG_FAN(nr));
		पूर्ण
		क्रम (nr = 0; nr < 4; nr++)
			data->in[nr] =
				f75375_पढ़ो8(client, F75375_REG_VOLT(nr));

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

अटल अंतरभूत u16 rpm_from_reg(u16 reg)
अणु
	अगर (reg == 0 || reg == 0xffff)
		वापस 0;
	वापस 1500000 / reg;
पूर्ण

अटल अंतरभूत u16 rpm_to_reg(पूर्णांक rpm)
अणु
	अगर (rpm < 367 || rpm > 0xffff)
		वापस 0xffff;
	वापस 1500000 / rpm;
पूर्ण

अटल bool duty_mode_enabled(u8 pwm_enable)
अणु
	चयन (pwm_enable) अणु
	हाल 0: /* Manual, duty mode (full speed) */
	हाल 1: /* Manual, duty mode */
	हाल 4: /* Auto, duty mode */
		वापस true;
	हाल 2: /* Auto, speed mode */
	हाल 3: /* Manual, speed mode */
		वापस false;
	शेष:
		WARN(1, "Unexpected pwm_enable value %d\n", pwm_enable);
		वापस true;
	पूर्ण
पूर्ण

अटल bool स्वतः_mode_enabled(u8 pwm_enable)
अणु
	चयन (pwm_enable) अणु
	हाल 0: /* Manual, duty mode (full speed) */
	हाल 1: /* Manual, duty mode */
	हाल 3: /* Manual, speed mode */
		वापस false;
	हाल 2: /* Auto, speed mode */
	हाल 4: /* Auto, duty mode */
		वापस true;
	शेष:
		WARN(1, "Unexpected pwm_enable value %d\n", pwm_enable);
		वापस false;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार set_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = rpm_to_reg(val);
	f75375_ग_लिखो16(client, F75375_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार set_fan_target(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (स्वतः_mode_enabled(data->pwm_enable[nr]))
		वापस -EINVAL;
	अगर (data->kind == f75387 && duty_mode_enabled(data->pwm_enable[nr]))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->fan_target[nr] = rpm_to_reg(val);
	f75375_ग_लिखो16(client, F75375_REG_FAN_EXP(nr), data->fan_target[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार set_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (स्वतः_mode_enabled(data->pwm_enable[nr]) ||
	    !duty_mode_enabled(data->pwm_enable[nr]))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = clamp_val(val, 0, 255);
	f75375_ग_लिखो_pwm(client, nr);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute
		*attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm_enable[nr]);
पूर्ण

अटल पूर्णांक set_pwm_enable_direct(काष्ठा i2c_client *client, पूर्णांक nr, पूर्णांक val)
अणु
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	u8 fanmode;

	अगर (val < 0 || val > 4)
		वापस -EINVAL;

	fanmode = f75375_पढ़ो8(client, F75375_REG_FAN_TIMER);
	अगर (data->kind == f75387) अणु
		/* For now, deny dangerous toggling of duty mode */
		अगर (duty_mode_enabled(data->pwm_enable[nr]) !=
				duty_mode_enabled(val))
			वापस -EOPNOTSUPP;
		/* clear each fanX_mode bit beक्रमe setting them properly */
		fanmode &= ~(1 << F75387_FAN_DUTY_MODE(nr));
		fanmode &= ~(1 << F75387_FAN_MANU_MODE(nr));
		चयन (val) अणु
		हाल 0: /* full speed */
			fanmode |= (1 << F75387_FAN_MANU_MODE(nr));
			fanmode |= (1 << F75387_FAN_DUTY_MODE(nr));
			data->pwm[nr] = 255;
			अवरोध;
		हाल 1: /* PWM */
			fanmode  |= (1 << F75387_FAN_MANU_MODE(nr));
			fanmode  |= (1 << F75387_FAN_DUTY_MODE(nr));
			अवरोध;
		हाल 2: /* Automatic, speed mode */
			अवरोध;
		हाल 3: /* fan speed */
			fanmode |= (1 << F75387_FAN_MANU_MODE(nr));
			अवरोध;
		हाल 4: /* Automatic, pwm */
			fanmode |= (1 << F75387_FAN_DUTY_MODE(nr));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* clear each fanX_mode bit beक्रमe setting them properly */
		fanmode &= ~(3 << FAN_CTRL_MODE(nr));
		चयन (val) अणु
		हाल 0: /* full speed */
			fanmode  |= (3 << FAN_CTRL_MODE(nr));
			data->pwm[nr] = 255;
			अवरोध;
		हाल 1: /* PWM */
			fanmode  |= (3 << FAN_CTRL_MODE(nr));
			अवरोध;
		हाल 2: /* AUTOMATIC*/
			fanmode  |= (1 << FAN_CTRL_MODE(nr));
			अवरोध;
		हाल 3: /* fan speed */
			अवरोध;
		हाल 4: /* Automatic pwm */
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	f75375_ग_लिखो8(client, F75375_REG_FAN_TIMER, fanmode);
	data->pwm_enable[nr] = val;
	अगर (val == 0)
		f75375_ग_लिखो_pwm(client, nr);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार set_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	err = set_pwm_enable_direct(client, nr, val);
	mutex_unlock(&data->update_lock);
	वापस err ? err : count;
पूर्ण

अटल sमाप_प्रकार set_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	u8 conf;
	अक्षर reg, ctrl;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (!(val == 0 || val == 1))
		वापस -EINVAL;

	/* F75373 करोes not support DC (linear voltage) fan control mode */
	अगर (data->kind == f75373 && val == 0)
		वापस -EINVAL;

	/* take care क्रम dअगरferent रेजिस्टरs */
	अगर (data->kind == f75387) अणु
		reg = F75375_REG_FAN_TIMER;
		ctrl = F75387_FAN_CTRL_LINEAR(nr);
	पूर्ण अन्यथा अणु
		reg = F75375_REG_CONFIG1;
		ctrl = F75375_FAN_CTRL_LINEAR(nr);
	पूर्ण

	mutex_lock(&data->update_lock);
	conf = f75375_पढ़ो8(client, reg);
	conf &= ~(1 << ctrl);

	अगर (val == 0)
		conf |= (1 << ctrl);

	f75375_ग_लिखो8(client, reg, conf);
	data->pwm_mode[nr] = val;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev, काष्ठा device_attribute
		*attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm[nr]);
पूर्ण

अटल sमाप_प्रकार show_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute
		*attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm_mode[nr]);
पूर्ण

#घोषणा VOLT_FROM_REG(val) ((val) * 8)
#घोषणा VOLT_TO_REG(val) ((val) / 8)

अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", VOLT_FROM_REG(data->in[nr]));
पूर्ण

अटल sमाप_प्रकार show_in_max(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", VOLT_FROM_REG(data->in_max[nr]));
पूर्ण

अटल sमाप_प्रकार show_in_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", VOLT_FROM_REG(data->in_min[nr]));
पूर्ण

अटल sमाप_प्रकार set_in_max(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(VOLT_TO_REG(val), 0, 0xff);
	mutex_lock(&data->update_lock);
	data->in_max[nr] = val;
	f75375_ग_लिखो8(client, F75375_REG_VOLT_HIGH(nr), data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार set_in_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(VOLT_TO_REG(val), 0, 0xff);
	mutex_lock(&data->update_lock);
	data->in_min[nr] = val;
	f75375_ग_लिखो8(client, F75375_REG_VOLT_LOW(nr), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
#घोषणा TEMP_FROM_REG(val) ((val) * 1000)
#घोषणा TEMP_TO_REG(val) ((val) / 1000)
#घोषणा TEMP11_FROM_REG(reg)	((reg) / 32 * 125)

अटल sमाप_प्रकार show_temp11(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP11_FROM_REG(data->temp11[nr]));
पूर्ण

अटल sमाप_प्रकार show_temp_max(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_high[nr]));
पूर्ण

अटल sमाप_प्रकार show_temp_max_hyst(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा f75375_data *data = f75375_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max_hyst[nr]));
पूर्ण

अटल sमाप_प्रकार set_temp_max(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(TEMP_TO_REG(val), 0, 127);
	mutex_lock(&data->update_lock);
	data->temp_high[nr] = val;
	f75375_ग_लिखो8(client, F75375_REG_TEMP_HIGH(nr), data->temp_high[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार set_temp_max_hyst(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = clamp_val(TEMP_TO_REG(val), 0, 127);
	mutex_lock(&data->update_lock);
	data->temp_max_hyst[nr] = val;
	f75375_ग_लिखो8(client, F75375_REG_TEMP_HYST(nr),
		data->temp_max_hyst[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

#घोषणा show_fan(thing) \
अटल sमाप_प्रकार show_##thing(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			अक्षर *buf)\
अणु\
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;\
	काष्ठा f75375_data *data = f75375_update_device(dev); \
	वापस प्र_लिखो(buf, "%d\n", rpm_from_reg(data->thing[nr])); \
पूर्ण

show_fan(fan);
show_fan(fan_min);
show_fan(fan_max);
show_fan(fan_target);

अटल SENSOR_DEVICE_ATTR(in0_input, S_IRUGO, show_in, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in0_max, S_IRUGO|S_IWUSR,
	show_in_max, set_in_max, 0);
अटल SENSOR_DEVICE_ATTR(in0_min, S_IRUGO|S_IWUSR,
	show_in_min, set_in_min, 0);
अटल SENSOR_DEVICE_ATTR(in1_input, S_IRUGO, show_in, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in1_max, S_IRUGO|S_IWUSR,
	show_in_max, set_in_max, 1);
अटल SENSOR_DEVICE_ATTR(in1_min, S_IRUGO|S_IWUSR,
	show_in_min, set_in_min, 1);
अटल SENSOR_DEVICE_ATTR(in2_input, S_IRUGO, show_in, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(in2_max, S_IRUGO|S_IWUSR,
	show_in_max, set_in_max, 2);
अटल SENSOR_DEVICE_ATTR(in2_min, S_IRUGO|S_IWUSR,
	show_in_min, set_in_min, 2);
अटल SENSOR_DEVICE_ATTR(in3_input, S_IRUGO, show_in, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(in3_max, S_IRUGO|S_IWUSR,
	show_in_max, set_in_max, 3);
अटल SENSOR_DEVICE_ATTR(in3_min, S_IRUGO|S_IWUSR,
	show_in_min, set_in_min, 3);
अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, show_temp11, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_max_hyst, S_IRUGO|S_IWUSR,
	show_temp_max_hyst, set_temp_max_hyst, 0);
अटल SENSOR_DEVICE_ATTR(temp1_max, S_IRUGO|S_IWUSR,
	show_temp_max, set_temp_max, 0);
अटल SENSOR_DEVICE_ATTR(temp2_input, S_IRUGO, show_temp11, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp2_max_hyst, S_IRUGO|S_IWUSR,
	show_temp_max_hyst, set_temp_max_hyst, 1);
अटल SENSOR_DEVICE_ATTR(temp2_max, S_IRUGO|S_IWUSR,
	show_temp_max, set_temp_max, 1);
अटल SENSOR_DEVICE_ATTR(fan1_input, S_IRUGO, show_fan, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_max, S_IRUGO, show_fan_max, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_min, S_IRUGO|S_IWUSR,
	show_fan_min, set_fan_min, 0);
अटल SENSOR_DEVICE_ATTR(fan1_target, S_IRUGO|S_IWUSR,
	show_fan_target, set_fan_target, 0);
अटल SENSOR_DEVICE_ATTR(fan2_input, S_IRUGO, show_fan, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(fan2_max, S_IRUGO, show_fan_max, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(fan2_min, S_IRUGO|S_IWUSR,
	show_fan_min, set_fan_min, 1);
अटल SENSOR_DEVICE_ATTR(fan2_target, S_IRUGO|S_IWUSR,
	show_fan_target, set_fan_target, 1);
अटल SENSOR_DEVICE_ATTR(pwm1, S_IRUGO|S_IWUSR,
	show_pwm, set_pwm, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_enable, S_IRUGO|S_IWUSR,
	show_pwm_enable, set_pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_mode, S_IRUGO,
	show_pwm_mode, set_pwm_mode, 0);
अटल SENSOR_DEVICE_ATTR(pwm2, S_IRUGO | S_IWUSR,
	show_pwm, set_pwm, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_enable, S_IRUGO|S_IWUSR,
	show_pwm_enable, set_pwm_enable, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_mode, S_IRUGO,
	show_pwm_mode, set_pwm_mode, 1);

अटल काष्ठा attribute *f75375_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_max.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_target.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_max.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_target.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_mode.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_mode.dev_attr.attr,
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group f75375_group = अणु
	.attrs = f75375_attributes,
पूर्ण;

अटल व्योम f75375_init(काष्ठा i2c_client *client, काष्ठा f75375_data *data,
		काष्ठा f75375s_platक्रमm_data *f75375s_pdata)
अणु
	पूर्णांक nr;

	अगर (!f75375s_pdata) अणु
		u8 conf, mode;
		पूर्णांक nr;

		conf = f75375_पढ़ो8(client, F75375_REG_CONFIG1);
		mode = f75375_पढ़ो8(client, F75375_REG_FAN_TIMER);
		क्रम (nr = 0; nr < 2; nr++) अणु
			अगर (data->kind == f75387) अणु
				bool manu, duty;

				अगर (!(mode & (1 << F75387_FAN_CTRL_LINEAR(nr))))
					data->pwm_mode[nr] = 1;

				manu = ((mode >> F75387_FAN_MANU_MODE(nr)) & 1);
				duty = ((mode >> F75387_FAN_DUTY_MODE(nr)) & 1);
				अगर (!manu && duty)
					/* स्वतः, pwm */
					data->pwm_enable[nr] = 4;
				अन्यथा अगर (manu && !duty)
					/* manual, speed */
					data->pwm_enable[nr] = 3;
				अन्यथा अगर (!manu && !duty)
					/* स्वतःmatic, speed */
					data->pwm_enable[nr] = 2;
				अन्यथा
					/* manual, pwm */
					data->pwm_enable[nr] = 1;
			पूर्ण अन्यथा अणु
				अगर (!(conf & (1 << F75375_FAN_CTRL_LINEAR(nr))))
					data->pwm_mode[nr] = 1;

				चयन ((mode >> FAN_CTRL_MODE(nr)) & 3) अणु
				हाल 0:		/* speed */
					data->pwm_enable[nr] = 3;
					अवरोध;
				हाल 1:		/* स्वतःmatic */
					data->pwm_enable[nr] = 2;
					अवरोध;
				शेष:	/* manual */
					data->pwm_enable[nr] = 1;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	set_pwm_enable_direct(client, 0, f75375s_pdata->pwm_enable[0]);
	set_pwm_enable_direct(client, 1, f75375s_pdata->pwm_enable[1]);
	क्रम (nr = 0; nr < 2; nr++) अणु
		अगर (स्वतः_mode_enabled(f75375s_pdata->pwm_enable[nr]) ||
		    !duty_mode_enabled(f75375s_pdata->pwm_enable[nr]))
			जारी;
		data->pwm[nr] = clamp_val(f75375s_pdata->pwm[nr], 0, 255);
		f75375_ग_लिखो_pwm(client, nr);
	पूर्ण

पूर्ण

अटल पूर्णांक f75375_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा f75375_data *data;
	काष्ठा f75375s_platक्रमm_data *f75375s_pdata =
			dev_get_platdata(&client->dev);
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;
	data = devm_kzalloc(&client->dev, माप(काष्ठा f75375_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->kind = i2c_match_id(f75375_id, client)->driver_data;

	err = sysfs_create_group(&client->dev.kobj, &f75375_group);
	अगर (err)
		वापस err;

	अगर (data->kind != f75373) अणु
		err = sysfs_chmod_file(&client->dev.kobj,
			&sensor_dev_attr_pwm1_mode.dev_attr.attr,
			S_IRUGO | S_IWUSR);
		अगर (err)
			जाओ निकास_हटाओ;
		err = sysfs_chmod_file(&client->dev.kobj,
			&sensor_dev_attr_pwm2_mode.dev_attr.attr,
			S_IRUGO | S_IWUSR);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&client->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	f75375_init(client, data, f75375s_pdata);

	वापस 0;

निकास_हटाओ:
	sysfs_हटाओ_group(&client->dev.kobj, &f75375_group);
	वापस err;
पूर्ण

अटल पूर्णांक f75375_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा f75375_data *data = i2c_get_clientdata(client);
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&client->dev.kobj, &f75375_group);
	वापस 0;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक f75375_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u16 vendid, chipid;
	u8 version;
	स्थिर अक्षर *name;

	vendid = f75375_पढ़ो16(client, F75375_REG_VENDOR);
	chipid = f75375_पढ़ो16(client, F75375_CHIP_ID);
	अगर (vendid != 0x1934)
		वापस -ENODEV;

	अगर (chipid == 0x0306)
		name = "f75375";
	अन्यथा अगर (chipid == 0x0204)
		name = "f75373";
	अन्यथा अगर (chipid == 0x0410)
		name = "f75387";
	अन्यथा
		वापस -ENODEV;

	version = f75375_पढ़ो8(client, F75375_REG_VERSION);
	dev_info(&adapter->dev, "found %s version: %02X\n", name, version);
	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

module_i2c_driver(f75375_driver);

MODULE_AUTHOR("Riku Voipio");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("F75373/F75375/F75387 hardware monitoring driver");
