<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * adm1031.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 * Based on lm75.c and lm85.c
 * Supports adm1030 / adm1031
 * Copyright (C) 2004 Alexandre d'Alton <alex@alexdalton.org>
 * Reworked by Jean Delvare <jdelvare@suse.de>
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

/* Following macros takes channel parameter starting from 0 to 2 */
#घोषणा ADM1031_REG_FAN_SPEED(nr)	(0x08 + (nr))
#घोषणा ADM1031_REG_FAN_DIV(nr)		(0x20 + (nr))
#घोषणा ADM1031_REG_PWM			(0x22)
#घोषणा ADM1031_REG_FAN_MIN(nr)		(0x10 + (nr))
#घोषणा ADM1031_REG_FAN_FILTER		(0x23)

#घोषणा ADM1031_REG_TEMP_OFFSET(nr)	(0x0d + (nr))
#घोषणा ADM1031_REG_TEMP_MAX(nr)	(0x14 + 4 * (nr))
#घोषणा ADM1031_REG_TEMP_MIN(nr)	(0x15 + 4 * (nr))
#घोषणा ADM1031_REG_TEMP_CRIT(nr)	(0x16 + 4 * (nr))

#घोषणा ADM1031_REG_TEMP(nr)		(0x0a + (nr))
#घोषणा ADM1031_REG_AUTO_TEMP(nr)	(0x24 + (nr))

#घोषणा ADM1031_REG_STATUS(nr)		(0x2 + (nr))

#घोषणा ADM1031_REG_CONF1		0x00
#घोषणा ADM1031_REG_CONF2		0x01
#घोषणा ADM1031_REG_EXT_TEMP		0x06

#घोषणा ADM1031_CONF1_MONITOR_ENABLE	0x01	/* Monitoring enable */
#घोषणा ADM1031_CONF1_PWM_INVERT	0x08	/* PWM Invert */
#घोषणा ADM1031_CONF1_AUTO_MODE		0x80	/* Auto FAN */

#घोषणा ADM1031_CONF2_PWM1_ENABLE	0x01
#घोषणा ADM1031_CONF2_PWM2_ENABLE	0x02
#घोषणा ADM1031_CONF2_TACH1_ENABLE	0x04
#घोषणा ADM1031_CONF2_TACH2_ENABLE	0x08
#घोषणा ADM1031_CONF2_TEMP_ENABLE(chan)	(0x10 << (chan))

#घोषणा ADM1031_UPDATE_RATE_MASK	0x1c
#घोषणा ADM1031_UPDATE_RATE_SHIFT	2

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु adm1030, adm1031 पूर्ण;

प्रकार u8 स्वतः_chan_table_t[8][2];

/* Each client has this additional data */
काष्ठा adm1031_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	काष्ठा mutex update_lock;
	पूर्णांक chip_type;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अचिन्हित पूर्णांक update_पूर्णांकerval;	/* In milliseconds */
	/*
	 * The chan_select_table contains the possible configurations क्रम
	 * स्वतः fan control.
	 */
	स्थिर स्वतः_chan_table_t *chan_select_table;
	u16 alarm;
	u8 conf1;
	u8 conf2;
	u8 fan[2];
	u8 fan_भाग[2];
	u8 fan_min[2];
	u8 pwm[2];
	u8 old_pwm[2];
	s8 temp[3];
	u8 ext_temp[3];
	u8 स्वतः_temp[3];
	u8 स्वतः_temp_min[3];
	u8 स्वतः_temp_off[3];
	u8 स्वतः_temp_max[3];
	s8 temp_offset[3];
	s8 temp_min[3];
	s8 temp_max[3];
	s8 temp_crit[3];
पूर्ण;

अटल अंतरभूत u8 adm1031_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक
adm1031_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, अचिन्हित पूर्णांक value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल काष्ठा adm1031_data *adm1031_update_device(काष्ठा device *dev)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ next_update;
	पूर्णांक chan;

	mutex_lock(&data->update_lock);

	next_update = data->last_updated
	  + msecs_to_jअगरfies(data->update_पूर्णांकerval);
	अगर (समय_after(jअगरfies, next_update) || !data->valid) अणु

		dev_dbg(&client->dev, "Starting adm1031 update\n");
		क्रम (chan = 0;
		     chan < ((data->chip_type == adm1031) ? 3 : 2); chan++) अणु
			u8 oldh, newh;

			oldh =
			    adm1031_पढ़ो_value(client, ADM1031_REG_TEMP(chan));
			data->ext_temp[chan] =
			    adm1031_पढ़ो_value(client, ADM1031_REG_EXT_TEMP);
			newh =
			    adm1031_पढ़ो_value(client, ADM1031_REG_TEMP(chan));
			अगर (newh != oldh) अणु
				data->ext_temp[chan] =
				    adm1031_पढ़ो_value(client,
						       ADM1031_REG_EXT_TEMP);
#अगर_घोषित DEBUG
				oldh =
				    adm1031_पढ़ो_value(client,
						       ADM1031_REG_TEMP(chan));

				/* oldh is actually newer */
				अगर (newh != oldh)
					dev_warn(&client->dev,
					  "Remote temperature may be wrong.\n");
#पूर्ण_अगर
			पूर्ण
			data->temp[chan] = newh;

			data->temp_offset[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_TEMP_OFFSET(chan));
			data->temp_min[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_TEMP_MIN(chan));
			data->temp_max[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_TEMP_MAX(chan));
			data->temp_crit[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_TEMP_CRIT(chan));
			data->स्वतः_temp[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_AUTO_TEMP(chan));

		पूर्ण

		data->conf1 = adm1031_पढ़ो_value(client, ADM1031_REG_CONF1);
		data->conf2 = adm1031_पढ़ो_value(client, ADM1031_REG_CONF2);

		data->alarm = adm1031_पढ़ो_value(client, ADM1031_REG_STATUS(0))
		    | (adm1031_पढ़ो_value(client, ADM1031_REG_STATUS(1)) << 8);
		अगर (data->chip_type == adm1030)
			data->alarm &= 0xc0ff;

		क्रम (chan = 0; chan < (data->chip_type == adm1030 ? 1 : 2);
		     chan++) अणु
			data->fan_भाग[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_FAN_DIV(chan));
			data->fan_min[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_FAN_MIN(chan));
			data->fan[chan] =
			    adm1031_पढ़ो_value(client,
					       ADM1031_REG_FAN_SPEED(chan));
			data->pwm[chan] =
			  (adm1031_पढ़ो_value(client,
					ADM1031_REG_PWM) >> (4 * chan)) & 0x0f;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

#घोषणा TEMP_TO_REG(val)		(((val) < 0 ? ((val - 500) / 1000) : \
					((val + 500) / 1000)))

#घोषणा TEMP_FROM_REG(val)		((val) * 1000)

#घोषणा TEMP_FROM_REG_EXT(val, ext)	(TEMP_FROM_REG(val) + (ext) * 125)

#घोषणा TEMP_OFFSET_TO_REG(val)		(TEMP_TO_REG(val) & 0x8f)
#घोषणा TEMP_OFFSET_FROM_REG(val)	TEMP_FROM_REG((val) < 0 ? \
						      (val) | 0x70 : (val))

#घोषणा FAN_FROM_REG(reg, भाग)		((reg) ? \
					 (11250 * 60) / ((reg) * (भाग)) : 0)

अटल पूर्णांक FAN_TO_REG(पूर्णांक reg, पूर्णांक भाग)
अणु
	पूर्णांक पंचांगp;
	पंचांगp = FAN_FROM_REG(clamp_val(reg, 0, 65535), भाग);
	वापस पंचांगp > 255 ? 255 : पंचांगp;
पूर्ण

#घोषणा FAN_DIV_FROM_REG(reg)		(1<<(((reg)&0xc0)>>6))

#घोषणा PWM_TO_REG(val)			(clamp_val((val), 0, 255) >> 4)
#घोषणा PWM_FROM_REG(val)		((val) << 4)

#घोषणा FAN_CHAN_FROM_REG(reg)		(((reg) >> 5) & 7)
#घोषणा FAN_CHAN_TO_REG(val, reg)	\
	(((reg) & 0x1F) | (((val) << 5) & 0xe0))

#घोषणा AUTO_TEMP_MIN_TO_REG(val, reg)	\
	((((val) / 500) & 0xf8) | ((reg) & 0x7))
#घोषणा AUTO_TEMP_RANGE_FROM_REG(reg)	(5000 * (1 << ((reg) & 0x7)))
#घोषणा AUTO_TEMP_MIN_FROM_REG(reg)	(1000 * ((((reg) >> 3) & 0x1f) << 2))

#घोषणा AUTO_TEMP_MIN_FROM_REG_DEG(reg)	((((reg) >> 3) & 0x1f) << 2)

#घोषणा AUTO_TEMP_OFF_FROM_REG(reg)		\
	(AUTO_TEMP_MIN_FROM_REG(reg) - 5000)

#घोषणा AUTO_TEMP_MAX_FROM_REG(reg)		\
	(AUTO_TEMP_RANGE_FROM_REG(reg) +	\
	AUTO_TEMP_MIN_FROM_REG(reg))

अटल पूर्णांक AUTO_TEMP_MAX_TO_REG(पूर्णांक val, पूर्णांक reg, पूर्णांक pwm)
अणु
	पूर्णांक ret;
	पूर्णांक range = val - AUTO_TEMP_MIN_FROM_REG(reg);

	range = ((val - AUTO_TEMP_MIN_FROM_REG(reg))*10)/(16 - pwm);
	ret = ((reg & 0xf8) |
	       (range < 10000 ? 0 :
		range < 20000 ? 1 :
		range < 40000 ? 2 : range < 80000 ? 3 : 4));
	वापस ret;
पूर्ण

/* FAN स्वतः control */
#घोषणा GET_FAN_AUTO_BITFIELD(data, idx)	\
	(*(data)->chan_select_table)[FAN_CHAN_FROM_REG((data)->conf1)][idx % 2]

/*
 * The tables below contains the possible values क्रम the स्वतः fan
 * control bitfields. the index in the table is the रेजिस्टर value.
 * MSb is the स्वतः fan control enable bit, so the four first entries
 * in the table disables स्वतः fan control when both bitfields are zero.
 */
अटल स्थिर स्वतः_chan_table_t स्वतः_channel_select_table_adm1031 = अणु
	अणु 0, 0 पूर्ण, अणु 0, 0 पूर्ण, अणु 0, 0 पूर्ण, अणु 0, 0 पूर्ण,
	अणु 2 /* 0b010 */ , 4 /* 0b100 */ पूर्ण,
	अणु 2 /* 0b010 */ , 2 /* 0b010 */ पूर्ण,
	अणु 4 /* 0b100 */ , 4 /* 0b100 */ पूर्ण,
	अणु 7 /* 0b111 */ , 7 /* 0b111 */ पूर्ण,
पूर्ण;

अटल स्थिर स्वतः_chan_table_t स्वतः_channel_select_table_adm1030 = अणु
	अणु 0, 0 पूर्ण, अणु 0, 0 पूर्ण, अणु 0, 0 पूर्ण, अणु 0, 0 पूर्ण,
	अणु 2 /* 0b10 */		, 0 पूर्ण,
	अणु 0xff /* invalid */	, 0 पूर्ण,
	अणु 0xff /* invalid */	, 0 पूर्ण,
	अणु 3 /* 0b11 */		, 0 पूर्ण,
पूर्ण;

/*
 * That function checks अगर a bitfield is valid and वापसs the other bitfield
 * nearest match अगर no exact match where found.
 */
अटल पूर्णांक
get_fan_स्वतः_nearest(काष्ठा adm1031_data *data, पूर्णांक chan, u8 val, u8 reg)
अणु
	पूर्णांक i;
	पूर्णांक first_match = -1, exact_match = -1;
	u8 other_reg_val =
	    (*data->chan_select_table)[FAN_CHAN_FROM_REG(reg)][chan ? 0 : 1];

	अगर (val == 0)
		वापस 0;

	क्रम (i = 0; i < 8; i++) अणु
		अगर ((val == (*data->chan_select_table)[i][chan]) &&
		    ((*data->chan_select_table)[i][chan ? 0 : 1] ==
		     other_reg_val)) अणु
			/* We found an exact match */
			exact_match = i;
			अवरोध;
		पूर्ण अन्यथा अगर (val == (*data->chan_select_table)[i][chan] &&
			   first_match == -1) अणु
			/*
			 * Save the first match in हाल of an exact match has
			 * not been found
			 */
			first_match = i;
		पूर्ण
	पूर्ण

	अगर (exact_match >= 0)
		वापस exact_match;
	अन्यथा अगर (first_match >= 0)
		वापस first_match;

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार fan_स्वतः_channel_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", GET_FAN_AUTO_BITFIELD(data, nr));
पूर्ण

अटल sमाप_प्रकार
fan_स्वतः_channel_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	u8 reg;
	पूर्णांक ret;
	u8 old_fan_mode;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	old_fan_mode = data->conf1;

	mutex_lock(&data->update_lock);

	ret = get_fan_स्वतः_nearest(data, nr, val, data->conf1);
	अगर (ret < 0) अणु
		mutex_unlock(&data->update_lock);
		वापस ret;
	पूर्ण
	reg = ret;
	data->conf1 = FAN_CHAN_TO_REG(reg, data->conf1);
	अगर ((data->conf1 & ADM1031_CONF1_AUTO_MODE) ^
	    (old_fan_mode & ADM1031_CONF1_AUTO_MODE)) अणु
		अगर (data->conf1 & ADM1031_CONF1_AUTO_MODE) अणु
			/*
			 * Switch to Auto Fan Mode
			 * Save PWM रेजिस्टरs
			 * Set PWM रेजिस्टरs to 33% Both
			 */
			data->old_pwm[0] = data->pwm[0];
			data->old_pwm[1] = data->pwm[1];
			adm1031_ग_लिखो_value(client, ADM1031_REG_PWM, 0x55);
		पूर्ण अन्यथा अणु
			/* Switch to Manual Mode */
			data->pwm[0] = data->old_pwm[0];
			data->pwm[1] = data->old_pwm[1];
			/* Restore PWM रेजिस्टरs */
			adm1031_ग_लिखो_value(client, ADM1031_REG_PWM,
					    data->pwm[0] | (data->pwm[1] << 4));
		पूर्ण
	पूर्ण
	data->conf1 = FAN_CHAN_TO_REG(reg, data->conf1);
	adm1031_ग_लिखो_value(client, ADM1031_REG_CONF1, data->conf1);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(स्वतः_fan1_channel, fan_स्वतः_channel, 0);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_fan2_channel, fan_स्वतः_channel, 1);

/* Auto Temps */
अटल sमाप_प्रकार स्वतः_temp_off_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       AUTO_TEMP_OFF_FROM_REG(data->स्वतः_temp[nr]));
पूर्ण
अटल sमाप_प्रकार स्वतः_temp_min_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       AUTO_TEMP_MIN_FROM_REG(data->स्वतः_temp[nr]));
पूर्ण
अटल sमाप_प्रकार
स्वतः_temp_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	val = clamp_val(val, 0, 127000);
	mutex_lock(&data->update_lock);
	data->स्वतः_temp[nr] = AUTO_TEMP_MIN_TO_REG(val, data->स्वतः_temp[nr]);
	adm1031_ग_लिखो_value(client, ADM1031_REG_AUTO_TEMP(nr),
			    data->स्वतः_temp[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार स्वतः_temp_max_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       AUTO_TEMP_MAX_FROM_REG(data->स्वतः_temp[nr]));
पूर्ण
अटल sमाप_प्रकार
स्वतः_temp_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	val = clamp_val(val, 0, 127000);
	mutex_lock(&data->update_lock);
	data->temp_max[nr] = AUTO_TEMP_MAX_TO_REG(val, data->स्वतः_temp[nr],
						  data->pwm[nr]);
	adm1031_ग_लिखो_value(client, ADM1031_REG_AUTO_TEMP(nr),
			    data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(स्वतः_temp1_off, स्वतः_temp_off, 0);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_temp1_min, स्वतः_temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_temp1_max, स्वतः_temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(स्वतः_temp2_off, स्वतः_temp_off, 1);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_temp2_min, स्वतः_temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_temp2_max, स्वतः_temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(स्वतः_temp3_off, स्वतः_temp_off, 2);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_temp3_min, स्वतः_temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_temp3_max, स्वतः_temp_max, 2);

/* pwm */
अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", PWM_FROM_REG(data->pwm[nr]));
पूर्ण
अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret, reg;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->update_lock);
	अगर ((data->conf1 & ADM1031_CONF1_AUTO_MODE) &&
	    (((val>>4) & 0xf) != 5)) अणु
		/* In स्वतःmatic mode, the only PWM accepted is 33% */
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण
	data->pwm[nr] = PWM_TO_REG(val);
	reg = adm1031_पढ़ो_value(client, ADM1031_REG_PWM);
	adm1031_ग_लिखो_value(client, ADM1031_REG_PWM,
			    nr ? ((data->pwm[nr] << 4) & 0xf0) | (reg & 0xf)
			    : (data->pwm[nr] & 0xf) | (reg & 0xf0));
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_fan1_min_pwm, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(स्वतः_fan2_min_pwm, pwm, 1);

/* Fans */

/*
 * That function checks the हालs where the fan पढ़ोing is not
 * relevant.  It is used to provide 0 as fan पढ़ोing when the fan is
 * not supposed to run
 */
अटल पूर्णांक trust_fan_पढ़ोings(काष्ठा adm1031_data *data, पूर्णांक chan)
अणु
	पूर्णांक res = 0;

	अगर (data->conf1 & ADM1031_CONF1_AUTO_MODE) अणु
		चयन (data->conf1 & 0x60) अणु
		हाल 0x00:
			/*
			 * remote temp1 controls fan1,
			 * remote temp2 controls fan2
			 */
			res = data->temp[chan+1] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->स्वतः_temp[chan+1]);
			अवरोध;
		हाल 0x20:	/* remote temp1 controls both fans */
			res =
			    data->temp[1] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->स्वतः_temp[1]);
			अवरोध;
		हाल 0x40:	/* remote temp2 controls both fans */
			res =
			    data->temp[2] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->स्वतः_temp[2]);
			अवरोध;
		हाल 0x60:	/* max controls both fans */
			res =
			    data->temp[0] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->स्वतः_temp[0])
			    || data->temp[1] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->स्वतः_temp[1])
			    || (data->chip_type == adm1031
				&& data->temp[2] >=
				AUTO_TEMP_MIN_FROM_REG_DEG(data->स्वतः_temp[2]));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		res = data->pwm[chan] > 0;
	पूर्ण
	वापस res;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	पूर्णांक value;

	value = trust_fan_पढ़ोings(data, nr) ? FAN_FROM_REG(data->fan[nr],
				 FAN_DIV_FROM_REG(data->fan_भाग[nr])) : 0;
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण
अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       FAN_FROM_REG(data->fan_min[nr],
				    FAN_DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण
अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->update_lock);
	अगर (val) अणु
		data->fan_min[nr] =
			FAN_TO_REG(val, FAN_DIV_FROM_REG(data->fan_भाग[nr]));
	पूर्ण अन्यथा अणु
		data->fan_min[nr] = 0xff;
	पूर्ण
	adm1031_ग_लिखो_value(client, ADM1031_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	u8 पंचांगp;
	पूर्णांक old_भाग;
	पूर्णांक new_min;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	पंचांगp = val == 8 ? 0xc0 :
	      val == 4 ? 0x80 :
	      val == 2 ? 0x40 :
	      val == 1 ? 0x00 :
	      0xff;
	अगर (पंचांगp == 0xff)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	/* Get fresh पढ़ोings */
	data->fan_भाग[nr] = adm1031_पढ़ो_value(client,
					       ADM1031_REG_FAN_DIV(nr));
	data->fan_min[nr] = adm1031_पढ़ो_value(client,
					       ADM1031_REG_FAN_MIN(nr));

	/* Write the new घड़ी भागider and fan min */
	old_भाग = FAN_DIV_FROM_REG(data->fan_भाग[nr]);
	data->fan_भाग[nr] = पंचांगp | (0x3f & data->fan_भाग[nr]);
	new_min = data->fan_min[nr] * old_भाग / val;
	data->fan_min[nr] = new_min > 0xff ? 0xff : new_min;

	adm1031_ग_लिखो_value(client, ADM1031_REG_FAN_DIV(nr),
			    data->fan_भाग[nr]);
	adm1031_ग_लिखो_value(client, ADM1031_REG_FAN_MIN(nr),
			    data->fan_min[nr]);

	/* Invalidate the cache: fan speed is no दीर्घer valid */
	data->valid = 0;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);

/* Temps */
अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	पूर्णांक ext;
	ext = nr == 0 ?
	    ((data->ext_temp[nr] >> 6) & 0x3) * 2 :
	    (((data->ext_temp[nr] >> ((nr - 1) * 3)) & 7));
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG_EXT(data->temp[nr], ext));
पूर्ण
अटल sमाप_प्रकार temp_offset_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       TEMP_OFFSET_FROM_REG(data->temp_offset[nr]));
पूर्ण
अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_min[nr]));
पूर्ण
अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[nr]));
पूर्ण
अटल sमाप_प्रकार temp_crit_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_crit[nr]));
पूर्ण
अटल sमाप_प्रकार temp_offset_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	val = clamp_val(val, -15000, 15000);
	mutex_lock(&data->update_lock);
	data->temp_offset[nr] = TEMP_OFFSET_TO_REG(val);
	adm1031_ग_लिखो_value(client, ADM1031_REG_TEMP_OFFSET(nr),
			    data->temp_offset[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	val = clamp_val(val, -55000, 127000);
	mutex_lock(&data->update_lock);
	data->temp_min[nr] = TEMP_TO_REG(val);
	adm1031_ग_लिखो_value(client, ADM1031_REG_TEMP_MIN(nr),
			    data->temp_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	val = clamp_val(val, -55000, 127000);
	mutex_lock(&data->update_lock);
	data->temp_max[nr] = TEMP_TO_REG(val);
	adm1031_ग_लिखो_value(client, ADM1031_REG_TEMP_MAX(nr),
			    data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार temp_crit_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	val = clamp_val(val, -55000, 127000);
	mutex_lock(&data->update_lock);
	data->temp_crit[nr] = TEMP_TO_REG(val);
	adm1031_ग_लिखो_value(client, ADM1031_REG_TEMP_CRIT(nr),
			    data->temp_crit[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_offset, temp_offset, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp_crit, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_offset, temp_offset, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_crit, temp_crit, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_offset, temp_offset, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_crit, temp_crit, 2);

/* Alarms */
अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarm);
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1031_data *data = adm1031_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->alarm >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan1_fault, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(fan2_fault, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_alarm, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(temp3_min_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_alarm, alarm, 12);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, 13);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 14);

/* Update Interval */
अटल स्थिर अचिन्हित पूर्णांक update_पूर्णांकervals[] = अणु
	16000, 8000, 4000, 2000, 1000, 500, 250, 125,
पूर्ण;

अटल sमाप_प्रकार update_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", data->update_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1031_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक i, err;
	u8 reg;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	/*
	 * Find the nearest update पूर्णांकerval from the table.
	 * Use it to determine the matching update rate.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(update_पूर्णांकervals) - 1; i++) अणु
		अगर (val >= update_पूर्णांकervals[i])
			अवरोध;
	पूर्ण
	/* अगर not found, we poपूर्णांक to the last entry (lowest update पूर्णांकerval) */

	/* set the new update rate जबतक preserving other settings */
	reg = adm1031_पढ़ो_value(client, ADM1031_REG_FAN_FILTER);
	reg &= ~ADM1031_UPDATE_RATE_MASK;
	reg |= i << ADM1031_UPDATE_RATE_SHIFT;
	adm1031_ग_लिखो_value(client, ADM1031_REG_FAN_FILTER, reg);

	mutex_lock(&data->update_lock);
	data->update_पूर्णांकerval = update_पूर्णांकervals[i];
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(update_पूर्णांकerval);

अटल काष्ठा attribute *adm1031_attributes[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_fault.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_स्वतः_fan1_channel.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_offset.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,

	&sensor_dev_attr_स्वतः_temp1_off.dev_attr.attr,
	&sensor_dev_attr_स्वतः_temp1_min.dev_attr.attr,
	&sensor_dev_attr_स्वतः_temp1_max.dev_attr.attr,

	&sensor_dev_attr_स्वतः_temp2_off.dev_attr.attr,
	&sensor_dev_attr_स्वतः_temp2_min.dev_attr.attr,
	&sensor_dev_attr_स्वतः_temp2_max.dev_attr.attr,

	&sensor_dev_attr_स्वतः_fan1_min_pwm.dev_attr.attr,

	&dev_attr_update_पूर्णांकerval.attr,
	&dev_attr_alarms.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1031_group = अणु
	.attrs = adm1031_attributes,
पूर्ण;

अटल काष्ठा attribute *adm1031_attributes_opt[] = अणु
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_fault.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_स्वतः_fan2_channel.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_स्वतः_temp3_off.dev_attr.attr,
	&sensor_dev_attr_स्वतः_temp3_min.dev_attr.attr,
	&sensor_dev_attr_स्वतः_temp3_max.dev_attr.attr,
	&sensor_dev_attr_स्वतः_fan2_min_pwm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1031_group_opt = अणु
	.attrs = adm1031_attributes_opt,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adm1031_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	स्थिर अक्षर *name;
	पूर्णांक id, co;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	id = i2c_smbus_पढ़ो_byte_data(client, 0x3d);
	co = i2c_smbus_पढ़ो_byte_data(client, 0x3e);

	अगर (!((id == 0x31 || id == 0x30) && co == 0x41))
		वापस -ENODEV;
	name = (id == 0x30) ? "adm1030" : "adm1031";

	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम adm1031_init_client(काष्ठा i2c_client *client)
अणु
	अचिन्हित पूर्णांक पढ़ो_val;
	अचिन्हित पूर्णांक mask;
	पूर्णांक i;
	काष्ठा adm1031_data *data = i2c_get_clientdata(client);

	mask = (ADM1031_CONF2_PWM1_ENABLE | ADM1031_CONF2_TACH1_ENABLE);
	अगर (data->chip_type == adm1031) अणु
		mask |= (ADM1031_CONF2_PWM2_ENABLE |
			ADM1031_CONF2_TACH2_ENABLE);
	पूर्ण
	/* Initialize the ADM1031 chip (enables fan speed पढ़ोing ) */
	पढ़ो_val = adm1031_पढ़ो_value(client, ADM1031_REG_CONF2);
	अगर ((पढ़ो_val | mask) != पढ़ो_val)
		adm1031_ग_लिखो_value(client, ADM1031_REG_CONF2, पढ़ो_val | mask);

	पढ़ो_val = adm1031_पढ़ो_value(client, ADM1031_REG_CONF1);
	अगर ((पढ़ो_val | ADM1031_CONF1_MONITOR_ENABLE) != पढ़ो_val) अणु
		adm1031_ग_लिखो_value(client, ADM1031_REG_CONF1,
				    पढ़ो_val | ADM1031_CONF1_MONITOR_ENABLE);
	पूर्ण

	/* Read the chip's update rate */
	mask = ADM1031_UPDATE_RATE_MASK;
	पढ़ो_val = adm1031_पढ़ो_value(client, ADM1031_REG_FAN_FILTER);
	i = (पढ़ो_val & mask) >> ADM1031_UPDATE_RATE_SHIFT;
	/* Save it as update पूर्णांकerval */
	data->update_पूर्णांकerval = update_पूर्णांकervals[i];
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1031_id[];

अटल पूर्णांक adm1031_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा adm1031_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा adm1031_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	data->chip_type = i2c_match_id(adm1031_id, client)->driver_data;
	mutex_init(&data->update_lock);

	अगर (data->chip_type == adm1030)
		data->chan_select_table = &स्वतः_channel_select_table_adm1030;
	अन्यथा
		data->chan_select_table = &स्वतः_channel_select_table_adm1031;

	/* Initialize the ADM1031 chip */
	adm1031_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &adm1031_group;
	अगर (data->chip_type == adm1031)
		data->groups[1] = &adm1031_group_opt;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1031_id[] = अणु
	अणु "adm1030", adm1030 पूर्ण,
	अणु "adm1031", adm1031 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1031_id);

अटल काष्ठा i2c_driver adm1031_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name = "adm1031",
	पूर्ण,
	.probe_new	= adm1031_probe,
	.id_table	= adm1031_id,
	.detect		= adm1031_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adm1031_driver);

MODULE_AUTHOR("Alexandre d'Alton <alex@alexdalton.org>");
MODULE_DESCRIPTION("ADM1031/ADM1030 driver");
MODULE_LICENSE("GPL");
