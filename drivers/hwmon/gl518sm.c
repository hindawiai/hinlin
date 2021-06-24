<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * gl518sm.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *             monitoring
 * Copyright (C) 1998, 1999 Froकरो Looijaard <froकरोl@dds.nl> and
 * Kyosti Malkki <kmalkki@cc.hut.fi>
 * Copyright (C) 2004 Hong-Gunn Chew <hglinux@gunnet.org> and
 * Jean Delvare <jdelvare@suse.de>
 *
 * Ported to Linux 2.6 by Hong-Gunn Chew with the help of Jean Delvare
 * and advice of Greg Kroah-Harपंचांगan.
 *
 * Notes about the port:
 * Release 0x00 of the GL518SM chipset करोesn't support पढ़ोing of in0,
 * in1 nor in2. The original driver had an ugly workaround to get them
 * anyway (changing limits and watching alarms trigger and wear off).
 * We did not keep that part of the original driver in the Linux 2.6
 * version, since it was making the driver signअगरicantly more complex
 * with no real benefit.
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
#समावेश <linux/sysfs.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु gl518sm_r00, gl518sm_r80 पूर्ण;

/* Many GL518 स्थिरants specअगरied below */

/* The GL518 रेजिस्टरs */
#घोषणा GL518_REG_CHIP_ID	0x00
#घोषणा GL518_REG_REVISION	0x01
#घोषणा GL518_REG_VENDOR_ID	0x02
#घोषणा GL518_REG_CONF		0x03
#घोषणा GL518_REG_TEMP_IN	0x04
#घोषणा GL518_REG_TEMP_MAX	0x05
#घोषणा GL518_REG_TEMP_HYST	0x06
#घोषणा GL518_REG_FAN_COUNT	0x07
#घोषणा GL518_REG_FAN_LIMIT	0x08
#घोषणा GL518_REG_VIN1_LIMIT	0x09
#घोषणा GL518_REG_VIN2_LIMIT	0x0a
#घोषणा GL518_REG_VIN3_LIMIT	0x0b
#घोषणा GL518_REG_VDD_LIMIT	0x0c
#घोषणा GL518_REG_VIN3		0x0d
#घोषणा GL518_REG_MISC		0x0f
#घोषणा GL518_REG_ALARM		0x10
#घोषणा GL518_REG_MASK		0x11
#घोषणा GL518_REG_INT		0x12
#घोषणा GL518_REG_VIN2		0x13
#घोषणा GL518_REG_VIN1		0x14
#घोषणा GL518_REG_VDD		0x15


/*
 * Conversions. Rounding and limit checking is only करोne on the TO_REG
 * variants. Note that you should be a bit careful with which arguments
 * these macros are called: arguments may be evaluated more than once.
 * Fixing this is just not worth it.
 */

#घोषणा RAW_FROM_REG(val)	val

#घोषणा BOOL_FROM_REG(val)	((val) ? 0 : 1)
#घोषणा BOOL_TO_REG(val)	((val) ? 0 : 1)

#घोषणा TEMP_CLAMP(val)		clamp_val(val, -119000, 136000)
#घोषणा TEMP_TO_REG(val)	(DIV_ROUND_CLOSEST(TEMP_CLAMP(val), 1000) + 119)
#घोषणा TEMP_FROM_REG(val)	(((val) - 119) * 1000)

अटल अंतरभूत u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	दीर्घ rpmभाग;
	अगर (rpm == 0)
		वापस 0;
	rpmभाग = clamp_val(rpm, 1, 960000) * भाग;
	वापस clamp_val((480000 + rpmभाग / 2) / rpmभाग, 1, 255);
पूर्ण
#घोषणा FAN_FROM_REG(val, भाग)	((val) == 0 ? 0 : (480000 / ((val) * (भाग))))

#घोषणा IN_CLAMP(val)		clamp_val(val, 0, 255 * 19)
#घोषणा IN_TO_REG(val)		DIV_ROUND_CLOSEST(IN_CLAMP(val), 19)
#घोषणा IN_FROM_REG(val)	((val) * 19)

#घोषणा VDD_CLAMP(val)		clamp_val(val, 0, 255 * 95 / 4)
#घोषणा VDD_TO_REG(val)		DIV_ROUND_CLOSEST(VDD_CLAMP(val) * 4, 95)
#घोषणा VDD_FROM_REG(val)	DIV_ROUND_CLOSEST((val) * 95, 4)

#घोषणा DIV_FROM_REG(val)	(1 << (val))

#घोषणा BEEP_MASK_TO_REG(val)	((val) & 0x7f & data->alarm_mask)
#घोषणा BEEP_MASK_FROM_REG(val)	((val) & 0x7f)

/* Each client has this additional data */
काष्ठा gl518_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	क्रमागत chips type;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 voltage_in[4];	/* Register values; [0] = VDD */
	u8 voltage_min[4];	/* Register values; [0] = VDD */
	u8 voltage_max[4];	/* Register values; [0] = VDD */
	u8 fan_in[2];
	u8 fan_min[2];
	u8 fan_भाग[2];		/* Register encoding, shअगरted right */
	u8 fan_स्वतः1;		/* Boolean */
	u8 temp_in;		/* Register values */
	u8 temp_max;		/* Register values */
	u8 temp_hyst;		/* Register values */
	u8 alarms;		/* Register value */
	u8 alarm_mask;
	u8 beep_mask;		/* Register value */
	u8 beep_enable;		/* Boolean */
पूर्ण;

/*
 * Registers 0x07 to 0x0c are word-sized, others are byte-sized
 * GL518 uses a high-byte first convention, which is exactly opposite to
 * the SMBus standard.
 */
अटल पूर्णांक gl518_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	अगर ((reg >= 0x07) && (reg <= 0x0c))
		वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
	अन्यथा
		वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक gl518_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, u16 value)
अणु
	अगर ((reg >= 0x07) && (reg <= 0x0c))
		वापस i2c_smbus_ग_लिखो_word_swapped(client, reg, value);
	अन्यथा
		वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल काष्ठा gl518_data *gl518_update_device(काष्ठा device *dev)
अणु
	काष्ठा gl518_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक val;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		dev_dbg(&client->dev, "Starting gl518 update\n");

		data->alarms = gl518_पढ़ो_value(client, GL518_REG_INT);
		data->beep_mask = gl518_पढ़ो_value(client, GL518_REG_ALARM);

		val = gl518_पढ़ो_value(client, GL518_REG_VDD_LIMIT);
		data->voltage_min[0] = val & 0xff;
		data->voltage_max[0] = (val >> 8) & 0xff;
		val = gl518_पढ़ो_value(client, GL518_REG_VIN1_LIMIT);
		data->voltage_min[1] = val & 0xff;
		data->voltage_max[1] = (val >> 8) & 0xff;
		val = gl518_पढ़ो_value(client, GL518_REG_VIN2_LIMIT);
		data->voltage_min[2] = val & 0xff;
		data->voltage_max[2] = (val >> 8) & 0xff;
		val = gl518_पढ़ो_value(client, GL518_REG_VIN3_LIMIT);
		data->voltage_min[3] = val & 0xff;
		data->voltage_max[3] = (val >> 8) & 0xff;

		val = gl518_पढ़ो_value(client, GL518_REG_FAN_COUNT);
		data->fan_in[0] = (val >> 8) & 0xff;
		data->fan_in[1] = val & 0xff;

		val = gl518_पढ़ो_value(client, GL518_REG_FAN_LIMIT);
		data->fan_min[0] = (val >> 8) & 0xff;
		data->fan_min[1] = val & 0xff;

		data->temp_in = gl518_पढ़ो_value(client, GL518_REG_TEMP_IN);
		data->temp_max =
		    gl518_पढ़ो_value(client, GL518_REG_TEMP_MAX);
		data->temp_hyst =
		    gl518_पढ़ो_value(client, GL518_REG_TEMP_HYST);

		val = gl518_पढ़ो_value(client, GL518_REG_MISC);
		data->fan_भाग[0] = (val >> 6) & 0x03;
		data->fan_भाग[1] = (val >> 4) & 0x03;
		data->fan_स्वतः1  = (val >> 3) & 0x01;

		data->alarms &= data->alarm_mask;

		val = gl518_पढ़ो_value(client, GL518_REG_CONF);
		data->beep_enable = (val >> 2) & 1;

		अगर (data->type != gl518sm_r00) अणु
			data->voltage_in[0] =
			    gl518_पढ़ो_value(client, GL518_REG_VDD);
			data->voltage_in[1] =
			    gl518_पढ़ो_value(client, GL518_REG_VIN1);
			data->voltage_in[2] =
			    gl518_पढ़ो_value(client, GL518_REG_VIN2);
		पूर्ण
		data->voltage_in[3] =
		    gl518_पढ़ो_value(client, GL518_REG_VIN3);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs stuff
 */

#घोषणा show(type, suffix, value)					\
अटल sमाप_प्रकार show_##suffix(काष्ठा device *dev,			\
			     काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा gl518_data *data = gl518_update_device(dev);		\
	वापस प्र_लिखो(buf, "%d\n", type##_FROM_REG(data->value));	\
पूर्ण

show(TEMP, temp_input1, temp_in);
show(TEMP, temp_max1, temp_max);
show(TEMP, temp_hyst1, temp_hyst);
show(BOOL, fan_स्वतः1, fan_स्वतः1);
show(VDD, in_input0, voltage_in[0]);
show(IN, in_input1, voltage_in[1]);
show(IN, in_input2, voltage_in[2]);
show(IN, in_input3, voltage_in[3]);
show(VDD, in_min0, voltage_min[0]);
show(IN, in_min1, voltage_min[1]);
show(IN, in_min2, voltage_min[2]);
show(IN, in_min3, voltage_min[3]);
show(VDD, in_max0, voltage_max[0]);
show(IN, in_max1, voltage_max[1]);
show(IN, in_max2, voltage_max[2]);
show(IN, in_max3, voltage_max[3]);
show(RAW, alarms, alarms);
show(BOOL, beep_enable, beep_enable);
show(BEEP_MASK, beep_mask, beep_mask);

अटल sमाप_प्रकार fan_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा gl518_data *data = gl518_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_in[nr],
					DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा gl518_data *data = gl518_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr],
					DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा gl518_data *data = gl518_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

#घोषणा set(type, suffix, value, reg)					\
अटल sमाप_प्रकार set_##suffix(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	काष्ठा gl518_data *data = dev_get_drvdata(dev);			\
	काष्ठा i2c_client *client = data->client;			\
	दीर्घ val;							\
	पूर्णांक err = kम_से_दीर्घ(buf, 10, &val);				\
	अगर (err)							\
		वापस err;						\
									\
	mutex_lock(&data->update_lock);					\
	data->value = type##_TO_REG(val);				\
	gl518_ग_लिखो_value(client, reg, data->value);			\
	mutex_unlock(&data->update_lock);				\
	वापस count;							\
पूर्ण

#घोषणा set_bits(type, suffix, value, reg, mask, shअगरt)			\
अटल sमाप_प्रकार set_##suffix(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf, माप_प्रकार count)		\
अणु									\
	काष्ठा gl518_data *data = dev_get_drvdata(dev);			\
	काष्ठा i2c_client *client = data->client;			\
	पूर्णांक regvalue;							\
	अचिन्हित दीर्घ val;						\
	पूर्णांक err = kम_से_अदीर्घ(buf, 10, &val);				\
	अगर (err)							\
		वापस err;						\
									\
	mutex_lock(&data->update_lock);					\
	regvalue = gl518_पढ़ो_value(client, reg);			\
	data->value = type##_TO_REG(val);				\
	regvalue = (regvalue & ~mask) | (data->value << shअगरt);		\
	gl518_ग_लिखो_value(client, reg, regvalue);			\
	mutex_unlock(&data->update_lock);				\
	वापस count;							\
पूर्ण

#घोषणा set_low(type, suffix, value, reg)				\
	set_bits(type, suffix, value, reg, 0x00ff, 0)
#घोषणा set_high(type, suffix, value, reg)				\
	set_bits(type, suffix, value, reg, 0xff00, 8)

set(TEMP, temp_max1, temp_max, GL518_REG_TEMP_MAX);
set(TEMP, temp_hyst1, temp_hyst, GL518_REG_TEMP_HYST);
set_bits(BOOL, fan_स्वतः1, fan_स्वतः1, GL518_REG_MISC, 0x08, 3);
set_low(VDD, in_min0, voltage_min[0], GL518_REG_VDD_LIMIT);
set_low(IN, in_min1, voltage_min[1], GL518_REG_VIN1_LIMIT);
set_low(IN, in_min2, voltage_min[2], GL518_REG_VIN2_LIMIT);
set_low(IN, in_min3, voltage_min[3], GL518_REG_VIN3_LIMIT);
set_high(VDD, in_max0, voltage_max[0], GL518_REG_VDD_LIMIT);
set_high(IN, in_max1, voltage_max[1], GL518_REG_VIN1_LIMIT);
set_high(IN, in_max2, voltage_max[2], GL518_REG_VIN2_LIMIT);
set_high(IN, in_max3, voltage_max[3], GL518_REG_VIN3_LIMIT);
set_bits(BOOL, beep_enable, beep_enable, GL518_REG_CONF, 0x04, 2);
set(BEEP_MASK, beep_mask, beep_mask, GL518_REG_ALARM);

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा gl518_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	पूर्णांक regvalue;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	regvalue = gl518_पढ़ो_value(client, GL518_REG_FAN_LIMIT);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	regvalue = (regvalue & (0xff << (8 * nr)))
		 | (data->fan_min[nr] << (8 * (1 - nr)));
	gl518_ग_लिखो_value(client, GL518_REG_FAN_LIMIT, regvalue);

	data->beep_mask = gl518_पढ़ो_value(client, GL518_REG_ALARM);
	अगर (data->fan_min[nr] == 0)
		data->alarm_mask &= ~(0x20 << nr);
	अन्यथा
		data->alarm_mask |= (0x20 << nr);
	data->beep_mask &= data->alarm_mask;
	gl518_ग_लिखो_value(client, GL518_REG_ALARM, data->beep_mask);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा gl518_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	पूर्णांक regvalue;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	चयन (val) अणु
	हाल 1:
		val = 0;
		अवरोध;
	हाल 2:
		val = 1;
		अवरोध;
	हाल 4:
		val = 2;
		अवरोध;
	हाल 8:
		val = 3;
		अवरोध;
	शेष:
		dev_err(dev,
			"Invalid fan clock divider %lu, choose one of 1, 2, 4 or 8\n",
			val);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);
	regvalue = gl518_पढ़ो_value(client, GL518_REG_MISC);
	data->fan_भाग[nr] = val;
	regvalue = (regvalue & ~(0xc0 >> (2 * nr)))
		 | (data->fan_भाग[nr] << (6 - 2 * nr));
	gl518_ग_लिखो_value(client, GL518_REG_MISC, regvalue);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(temp1_input, 0444, show_temp_input1, शून्य);
अटल DEVICE_ATTR(temp1_max, 0644, show_temp_max1, set_temp_max1);
अटल DEVICE_ATTR(temp1_max_hyst, 0644,
		   show_temp_hyst1, set_temp_hyst1);
अटल DEVICE_ATTR(fan1_स्वतः, 0644, show_fan_स्वतः1, set_fan_स्वतः1);
अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);
अटल DEVICE_ATTR(in0_input, 0444, show_in_input0, शून्य);
अटल DEVICE_ATTR(in1_input, 0444, show_in_input1, शून्य);
अटल DEVICE_ATTR(in2_input, 0444, show_in_input2, शून्य);
अटल DEVICE_ATTR(in3_input, 0444, show_in_input3, शून्य);
अटल DEVICE_ATTR(in0_min, 0644, show_in_min0, set_in_min0);
अटल DEVICE_ATTR(in1_min, 0644, show_in_min1, set_in_min1);
अटल DEVICE_ATTR(in2_min, 0644, show_in_min2, set_in_min2);
अटल DEVICE_ATTR(in3_min, 0644, show_in_min3, set_in_min3);
अटल DEVICE_ATTR(in0_max, 0644, show_in_max0, set_in_max0);
अटल DEVICE_ATTR(in1_max, 0644, show_in_max1, set_in_max1);
अटल DEVICE_ATTR(in2_max, 0644, show_in_max2, set_in_max2);
अटल DEVICE_ATTR(in3_max, 0644, show_in_max3, set_in_max3);
अटल DEVICE_ATTR(alarms, 0444, show_alarms, शून्य);
अटल DEVICE_ATTR(beep_enable, 0644,
		   show_beep_enable, set_beep_enable);
अटल DEVICE_ATTR(beep_mask, 0644,
		   show_beep_mask, set_beep_mask);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा gl518_data *data = gl518_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 6);

अटल sमाप_प्रकार beep_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा gl518_data *data = gl518_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->beep_mask >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार beep_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gl518_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	अचिन्हित दीर्घ bit;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &bit);
	अगर (err)
		वापस err;

	अगर (bit & ~1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->beep_mask = gl518_पढ़ो_value(client, GL518_REG_ALARM);
	अगर (bit)
		data->beep_mask |= (1 << bitnr);
	अन्यथा
		data->beep_mask &= ~(1 << bitnr);
	gl518_ग_लिखो_value(client, GL518_REG_ALARM, data->beep_mask);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(in0_beep, beep, 0);
अटल SENSOR_DEVICE_ATTR_RW(in1_beep, beep, 1);
अटल SENSOR_DEVICE_ATTR_RW(in2_beep, beep, 2);
अटल SENSOR_DEVICE_ATTR_RW(in3_beep, beep, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp1_beep, beep, 4);
अटल SENSOR_DEVICE_ATTR_RW(fan1_beep, beep, 5);
अटल SENSOR_DEVICE_ATTR_RW(fan2_beep, beep, 6);

अटल काष्ठा attribute *gl518_attributes[] = अणु
	&dev_attr_in3_input.attr,
	&dev_attr_in0_min.attr,
	&dev_attr_in1_min.attr,
	&dev_attr_in2_min.attr,
	&dev_attr_in3_min.attr,
	&dev_attr_in0_max.attr,
	&dev_attr_in1_max.attr,
	&dev_attr_in2_max.attr,
	&dev_attr_in3_max.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_beep.dev_attr.attr,
	&sensor_dev_attr_in1_beep.dev_attr.attr,
	&sensor_dev_attr_in2_beep.dev_attr.attr,
	&sensor_dev_attr_in3_beep.dev_attr.attr,

	&dev_attr_fan1_स्वतः.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_beep.dev_attr.attr,
	&sensor_dev_attr_fan2_beep.dev_attr.attr,

	&dev_attr_temp1_input.attr,
	&dev_attr_temp1_max.attr,
	&dev_attr_temp1_max_hyst.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_beep.dev_attr.attr,

	&dev_attr_alarms.attr,
	&dev_attr_beep_enable.attr,
	&dev_attr_beep_mask.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gl518_group = अणु
	.attrs = gl518_attributes,
पूर्ण;

अटल काष्ठा attribute *gl518_attributes_r80[] = अणु
	&dev_attr_in0_input.attr,
	&dev_attr_in1_input.attr,
	&dev_attr_in2_input.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gl518_group_r80 = अणु
	.attrs = gl518_attributes_r80,
पूर्ण;

/*
 * Real code
 */

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक gl518_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक rev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	/* Now, we करो the reमुख्यing detection. */
	अगर ((gl518_पढ़ो_value(client, GL518_REG_CHIP_ID) != 0x80)
	 || (gl518_पढ़ो_value(client, GL518_REG_CONF) & 0x80))
		वापस -ENODEV;

	/* Determine the chip type. */
	rev = gl518_पढ़ो_value(client, GL518_REG_REVISION);
	अगर (rev != 0x00 && rev != 0x80)
		वापस -ENODEV;

	strlcpy(info->type, "gl518sm", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

/*
 * Called when we have found a new GL518SM.
 * Note that we preserve D4:NoFan2 and D2:beep_enable.
 */
अटल व्योम gl518_init_client(काष्ठा i2c_client *client)
अणु
	/* Make sure we leave D7:Reset untouched */
	u8 regvalue = gl518_पढ़ो_value(client, GL518_REG_CONF) & 0x7f;

	/* Comparator mode (D3=0), standby mode (D6=0) */
	gl518_ग_लिखो_value(client, GL518_REG_CONF, (regvalue &= 0x37));

	/* Never पूर्णांकerrupts */
	gl518_ग_लिखो_value(client, GL518_REG_MASK, 0x00);

	/* Clear status रेजिस्टर (D5=1), start (D6=1) */
	gl518_ग_लिखो_value(client, GL518_REG_CONF, 0x20 | regvalue);
	gl518_ग_लिखो_value(client, GL518_REG_CONF, 0x40 | regvalue);
पूर्ण

अटल पूर्णांक gl518_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा gl518_data *data;
	पूर्णांक revision;

	data = devm_kzalloc(dev, माप(काष्ठा gl518_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	revision = gl518_पढ़ो_value(client, GL518_REG_REVISION);
	data->type = revision == 0x80 ? gl518sm_r80 : gl518sm_r00;
	mutex_init(&data->update_lock);

	/* Initialize the GL518SM chip */
	data->alarm_mask = 0xff;
	gl518_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &gl518_group;
	अगर (data->type == gl518sm_r80)
		data->groups[1] = &gl518_group_r80;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id gl518_id[] = अणु
	अणु "gl518sm", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, gl518_id);

अटल काष्ठा i2c_driver gl518_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "gl518sm",
	पूर्ण,
	.probe_new	= gl518_probe,
	.id_table	= gl518_id,
	.detect		= gl518_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(gl518_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>, "
	"Kyosti Malkki <kmalkki@cc.hut.fi> and "
	"Hong-Gunn Chew <hglinux@gunnet.org>");
MODULE_DESCRIPTION("GL518SM driver");
MODULE_LICENSE("GPL");
