<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * asb100.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	      monitoring
 *
 * Copyright (C) 2004 Mark M. Hoffman <mhoffman@lightlink.com>
 *
 * (derived from w83781d.c)
 *
 * Copyright (C) 1998 - 2003  Froकरो Looijaard <froकरोl@dds.nl>,
 *			      Philip Edelbrock <phil@netroedge.com>, and
 *			      Mark Studebaker <mdsxyz123@yahoo.com>
 */

/*
 * This driver supports the hardware sensor chips: Asus ASB100 and
 * ASB100-A "BACH".
 *
 * ASB100-A supports pwm1, जबतक plain ASB100 करोes not.  There is no known
 * way क्रम the driver to tell which one is there.
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * asb100	7	3	1	4	0x31	0x0694	yes	no
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश "lm75.h"

/* I2C addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2d, I2C_CLIENT_END पूर्ण;

अटल अचिन्हित लघु क्रमce_subclients[4];
module_param_array(क्रमce_subclients, लघु, शून्य, 0);
MODULE_PARM_DESC(क्रमce_subclients,
	"List of subclient addresses: {bus, clientaddr, subclientaddr1, subclientaddr2}");

/* Voltage IN रेजिस्टरs 0-6 */
#घोषणा ASB100_REG_IN(nr)	(0x20 + (nr))
#घोषणा ASB100_REG_IN_MAX(nr)	(0x2b + (nr * 2))
#घोषणा ASB100_REG_IN_MIN(nr)	(0x2c + (nr * 2))

/* FAN IN रेजिस्टरs 1-3 */
#घोषणा ASB100_REG_FAN(nr)	(0x28 + (nr))
#घोषणा ASB100_REG_FAN_MIN(nr)	(0x3b + (nr))

/* TEMPERATURE रेजिस्टरs 1-4 */
अटल स्थिर u16 asb100_reg_temp[]	= अणु0, 0x27, 0x150, 0x250, 0x17पूर्ण;
अटल स्थिर u16 asb100_reg_temp_max[]	= अणु0, 0x39, 0x155, 0x255, 0x18पूर्ण;
अटल स्थिर u16 asb100_reg_temp_hyst[]	= अणु0, 0x3a, 0x153, 0x253, 0x19पूर्ण;

#घोषणा ASB100_REG_TEMP(nr) (asb100_reg_temp[nr])
#घोषणा ASB100_REG_TEMP_MAX(nr) (asb100_reg_temp_max[nr])
#घोषणा ASB100_REG_TEMP_HYST(nr) (asb100_reg_temp_hyst[nr])

#घोषणा ASB100_REG_TEMP2_CONFIG	0x0152
#घोषणा ASB100_REG_TEMP3_CONFIG	0x0252


#घोषणा ASB100_REG_CONFIG	0x40
#घोषणा ASB100_REG_ALARM1	0x41
#घोषणा ASB100_REG_ALARM2	0x42
#घोषणा ASB100_REG_SMIM1	0x43
#घोषणा ASB100_REG_SMIM2	0x44
#घोषणा ASB100_REG_VID_FANDIV	0x47
#घोषणा ASB100_REG_I2C_ADDR	0x48
#घोषणा ASB100_REG_CHIPID	0x49
#घोषणा ASB100_REG_I2C_SUBADDR	0x4a
#घोषणा ASB100_REG_PIN		0x4b
#घोषणा ASB100_REG_IRQ		0x4c
#घोषणा ASB100_REG_BANK		0x4e
#घोषणा ASB100_REG_CHIPMAN	0x4f

#घोषणा ASB100_REG_WCHIPID	0x58

/* bit 7 -> enable, bits 0-3 -> duty cycle */
#घोषणा ASB100_REG_PWM1		0x59

/*
 * CONVERSIONS
 * Rounding and limit checking is only करोne on the TO_REG variants.
 */

/* These स्थिरants are a guess, consistent w/ w83781d */
#घोषणा ASB100_IN_MIN		0
#घोषणा ASB100_IN_MAX		4080

/*
 * IN: 1/1000 V (0V to 4.08V)
 * REG: 16mV/bit
 */
अटल u8 IN_TO_REG(अचिन्हित val)
अणु
	अचिन्हित nval = clamp_val(val, ASB100_IN_MIN, ASB100_IN_MAX);
	वापस (nval + 8) / 16;
पूर्ण

अटल अचिन्हित IN_FROM_REG(u8 reg)
अणु
	वापस reg * 16;
पूर्ण

अटल u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == -1)
		वापस 0;
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

अटल पूर्णांक FAN_FROM_REG(u8 val, पूर्णांक भाग)
अणु
	वापस val == 0 ? -1 : val == 255 ? 0 : 1350000 / (val * भाग);
पूर्ण

/* These स्थिरants are a guess, consistent w/ w83781d */
#घोषणा ASB100_TEMP_MIN		-128000
#घोषणा ASB100_TEMP_MAX		127000

/*
 * TEMP: 0.001C/bit (-128C to +127C)
 * REG: 1C/bit, two's complement
 */
अटल u8 TEMP_TO_REG(दीर्घ temp)
अणु
	पूर्णांक ntemp = clamp_val(temp, ASB100_TEMP_MIN, ASB100_TEMP_MAX);
	ntemp += (ntemp < 0 ? -500 : 500);
	वापस (u8)(ntemp / 1000);
पूर्ण

अटल पूर्णांक TEMP_FROM_REG(u8 reg)
अणु
	वापस (s8)reg * 1000;
पूर्ण

/*
 * PWM: 0 - 255 per sensors करोcumentation
 * REG: (6.25% duty cycle per bit)
 */
अटल u8 ASB100_PWM_TO_REG(पूर्णांक pwm)
अणु
	pwm = clamp_val(pwm, 0, 255);
	वापस (u8)(pwm / 16);
पूर्ण

अटल पूर्णांक ASB100_PWM_FROM_REG(u8 reg)
अणु
	वापस reg * 16;
पूर्ण

#घोषणा DIV_FROM_REG(val) (1 << (val))

/*
 * FAN DIV: 1, 2, 4, or 8 (शेषs to 2)
 * REG: 0, 1, 2, or 3 (respectively) (शेषs to 1)
 */
अटल u8 DIV_TO_REG(दीर्घ val)
अणु
	वापस val == 8 ? 3 : val == 4 ? 2 : val == 1 ? 0 : 1;
पूर्ण

/*
 * For each रेजिस्टरed client, we need to keep some data in memory. That
 * data is poपूर्णांकed to by client->data. The काष्ठाure itself is
 * dynamically allocated, at the same समय the client itself is allocated.
 */
काष्ठा asb100_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;

	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* array of 2 poपूर्णांकers to subclients */
	काष्ठा i2c_client *lm75[2];

	अक्षर valid;		/* !=0 अगर following fields are valid */
	u8 in[7];		/* Register value */
	u8 in_max[7];		/* Register value */
	u8 in_min[7];		/* Register value */
	u8 fan[3];		/* Register value */
	u8 fan_min[3];		/* Register value */
	u16 temp[4];		/* Register value (0 and 3 are u8 only) */
	u16 temp_max[4];	/* Register value (0 and 3 are u8 only) */
	u16 temp_hyst[4];	/* Register value (0 and 3 are u8 only) */
	u8 fan_भाग[3];		/* Register encoding, right justअगरied */
	u8 pwm;			/* Register encoding */
	u8 vid;			/* Register encoding, combined */
	u32 alarms;		/* Register encoding, combined */
	u8 vrm;
पूर्ण;

अटल पूर्णांक asb100_पढ़ो_value(काष्ठा i2c_client *client, u16 reg);
अटल व्योम asb100_ग_लिखो_value(काष्ठा i2c_client *client, u16 reg, u16 val);

अटल पूर्णांक asb100_probe(काष्ठा i2c_client *client);
अटल पूर्णांक asb100_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info);
अटल पूर्णांक asb100_हटाओ(काष्ठा i2c_client *client);
अटल काष्ठा asb100_data *asb100_update_device(काष्ठा device *dev);
अटल व्योम asb100_init_client(काष्ठा i2c_client *client);

अटल स्थिर काष्ठा i2c_device_id asb100_id[] = अणु
	अणु "asb100", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, asb100_id);

अटल काष्ठा i2c_driver asb100_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "asb100",
	पूर्ण,
	.probe_new	= asb100_probe,
	.हटाओ		= asb100_हटाओ,
	.id_table	= asb100_id,
	.detect		= asb100_detect,
	.address_list	= normal_i2c,
पूर्ण;

/* 7 Voltages */
#घोषणा show_in_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
		अक्षर *buf) \
अणु \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	काष्ठा asb100_data *data = asb100_update_device(dev); \
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->reg[nr])); \
पूर्ण

show_in_reg(in)
show_in_reg(in_min)
show_in_reg(in_max)

#घोषणा set_in_reg(REG, reg) \
अटल sमाप_प्रकार set_in_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
		स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	काष्ठा i2c_client *client = to_i2c_client(dev); \
	काष्ठा asb100_data *data = i2c_get_clientdata(client); \
	अचिन्हित दीर्घ val; \
	पूर्णांक err = kम_से_अदीर्घ(buf, 10, &val); \
	अगर (err) \
		वापस err; \
	mutex_lock(&data->update_lock); \
	data->in_##reg[nr] = IN_TO_REG(val); \
	asb100_ग_लिखो_value(client, ASB100_REG_IN_##REG(nr), \
		data->in_##reg[nr]); \
	mutex_unlock(&data->update_lock); \
	वापस count; \
पूर्ण

set_in_reg(MIN, min)
set_in_reg(MAX, max)

#घोषणा sysfs_in(offset) \
अटल SENSOR_DEVICE_ATTR(in##offset##_input, S_IRUGO, \
		show_in, शून्य, offset); \
अटल SENSOR_DEVICE_ATTR(in##offset##_min, S_IRUGO | S_IWUSR, \
		show_in_min, set_in_min, offset); \
अटल SENSOR_DEVICE_ATTR(in##offset##_max, S_IRUGO | S_IWUSR, \
		show_in_max, set_in_max, offset)

sysfs_in(0);
sysfs_in(1);
sysfs_in(2);
sysfs_in(3);
sysfs_in(4);
sysfs_in(5);
sysfs_in(6);

/* 3 Fans */
अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
		DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार show_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr],
		DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार show_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार set_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	asb100_ग_लिखो_value(client, ASB100_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार set_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ min;
	पूर्णांक reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	min = FAN_FROM_REG(data->fan_min[nr],
			DIV_FROM_REG(data->fan_भाग[nr]));
	data->fan_भाग[nr] = DIV_TO_REG(val);

	चयन (nr) अणु
	हाल 0:	/* fan 1 */
		reg = asb100_पढ़ो_value(client, ASB100_REG_VID_FANDIV);
		reg = (reg & 0xcf) | (data->fan_भाग[0] << 4);
		asb100_ग_लिखो_value(client, ASB100_REG_VID_FANDIV, reg);
		अवरोध;

	हाल 1:	/* fan 2 */
		reg = asb100_पढ़ो_value(client, ASB100_REG_VID_FANDIV);
		reg = (reg & 0x3f) | (data->fan_भाग[1] << 6);
		asb100_ग_लिखो_value(client, ASB100_REG_VID_FANDIV, reg);
		अवरोध;

	हाल 2:	/* fan 3 */
		reg = asb100_पढ़ो_value(client, ASB100_REG_PIN);
		reg = (reg & 0x3f) | (data->fan_भाग[2] << 6);
		asb100_ग_लिखो_value(client, ASB100_REG_PIN, reg);
		अवरोध;
	पूर्ण

	data->fan_min[nr] =
		FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	asb100_ग_लिखो_value(client, ASB100_REG_FAN_MIN(nr), data->fan_min[nr]);

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

#घोषणा sysfs_fan(offset) \
अटल SENSOR_DEVICE_ATTR(fan##offset##_input, S_IRUGO, \
		show_fan, शून्य, offset - 1); \
अटल SENSOR_DEVICE_ATTR(fan##offset##_min, S_IRUGO | S_IWUSR, \
		show_fan_min, set_fan_min, offset - 1); \
अटल SENSOR_DEVICE_ATTR(fan##offset##_भाग, S_IRUGO | S_IWUSR, \
		show_fan_भाग, set_fan_भाग, offset - 1)

sysfs_fan(1);
sysfs_fan(2);
sysfs_fan(3);

/* 4 Temp. Sensors */
अटल पूर्णांक प्र_लिखो_temp_from_reg(u16 reg, अक्षर *buf, पूर्णांक nr)
अणु
	पूर्णांक ret = 0;

	चयन (nr) अणु
	हाल 1: हाल 2:
		ret = प्र_लिखो(buf, "%d\n", LM75_TEMP_FROM_REG(reg));
		अवरोध;
	हाल 0: हाल 3: शेष:
		ret = प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(reg));
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा show_temp_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
		अक्षर *buf) \
अणु \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	काष्ठा asb100_data *data = asb100_update_device(dev); \
	वापस प्र_लिखो_temp_from_reg(data->reg[nr], buf, nr); \
पूर्ण

show_temp_reg(temp);
show_temp_reg(temp_max);
show_temp_reg(temp_hyst);

#घोषणा set_temp_reg(REG, reg) \
अटल sमाप_प्रकार set_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
		स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	काष्ठा i2c_client *client = to_i2c_client(dev); \
	काष्ठा asb100_data *data = i2c_get_clientdata(client); \
	दीर्घ val; \
	पूर्णांक err = kम_से_दीर्घ(buf, 10, &val); \
	अगर (err) \
		वापस err; \
	mutex_lock(&data->update_lock); \
	चयन (nr) अणु \
	हाल 1: हाल 2: \
		data->reg[nr] = LM75_TEMP_TO_REG(val); \
		अवरोध; \
	हाल 0: हाल 3: शेष: \
		data->reg[nr] = TEMP_TO_REG(val); \
		अवरोध; \
	पूर्ण \
	asb100_ग_लिखो_value(client, ASB100_REG_TEMP_##REG(nr+1), \
			data->reg[nr]); \
	mutex_unlock(&data->update_lock); \
	वापस count; \
पूर्ण

set_temp_reg(MAX, temp_max);
set_temp_reg(HYST, temp_hyst);

#घोषणा sysfs_temp(num) \
अटल SENSOR_DEVICE_ATTR(temp##num##_input, S_IRUGO, \
		show_temp, शून्य, num - 1); \
अटल SENSOR_DEVICE_ATTR(temp##num##_max, S_IRUGO | S_IWUSR, \
		show_temp_max, set_temp_max, num - 1); \
अटल SENSOR_DEVICE_ATTR(temp##num##_max_hyst, S_IRUGO | S_IWUSR, \
		show_temp_hyst, set_temp_hyst, num - 1)

sysfs_temp(1);
sysfs_temp(2);
sysfs_temp(3);
sysfs_temp(4);

/* VID */
अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण

अटल DEVICE_ATTR_RO(cpu0_vid);

/* VRM */
अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा asb100_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asb100_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 255)
		वापस -EINVAL;

	data->vrm = val;
	वापस count;
पूर्ण

/* Alarms */
अटल DEVICE_ATTR_RW(vrm);

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR(in0_alarm, S_IRUGO, show_alarm, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in1_alarm, S_IRUGO, show_alarm, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in2_alarm, S_IRUGO, show_alarm, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(in3_alarm, S_IRUGO, show_alarm, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(in4_alarm, S_IRUGO, show_alarm, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(fan1_alarm, S_IRUGO, show_alarm, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(fan2_alarm, S_IRUGO, show_alarm, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(fan3_alarm, S_IRUGO, show_alarm, शून्य, 11);
अटल SENSOR_DEVICE_ATTR(temp1_alarm, S_IRUGO, show_alarm, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(temp2_alarm, S_IRUGO, show_alarm, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(temp3_alarm, S_IRUGO, show_alarm, शून्य, 13);

/* 1 PWM */
अटल sमाप_प्रकार pwm1_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", ASB100_PWM_FROM_REG(data->pwm & 0x0f));
पूर्ण

अटल sमाप_प्रकार pwm1_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm &= 0x80; /* keep the enable bit */
	data->pwm |= (0x0f & ASB100_PWM_TO_REG(val));
	asb100_ग_लिखो_value(client, ASB100_REG_PWM1, data->pwm);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm1_enable_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा asb100_data *data = asb100_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->pwm & 0x80) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm &= 0x0f; /* keep the duty cycle bits */
	data->pwm |= (val ? 0x80 : 0x00);
	asb100_ग_लिखो_value(client, ASB100_REG_PWM1, data->pwm);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(pwm1);
अटल DEVICE_ATTR_RW(pwm1_enable);

अटल काष्ठा attribute *asb100_attributes[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,

	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_भाग.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp4_max_hyst.dev_attr.attr,

	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,

	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	&dev_attr_alarms.attr,
	&dev_attr_pwm1.attr,
	&dev_attr_pwm1_enable.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group asb100_group = अणु
	.attrs = asb100_attributes,
पूर्ण;

अटल पूर्णांक asb100_detect_subclients(काष्ठा i2c_client *client)
अणु
	पूर्णांक i, id, err;
	पूर्णांक address = client->addr;
	अचिन्हित लघु sc_addr[2];
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	काष्ठा i2c_adapter *adapter = client->adapter;

	id = i2c_adapter_id(adapter);

	अगर (क्रमce_subclients[0] == id && क्रमce_subclients[1] == address) अणु
		क्रम (i = 2; i <= 3; i++) अणु
			अगर (क्रमce_subclients[i] < 0x48 ||
			    क्रमce_subclients[i] > 0x4f) अणु
				dev_err(&client->dev,
					"invalid subclient address %d; must be 0x48-0x4f\n",
					क्रमce_subclients[i]);
				err = -ENODEV;
				जाओ ERROR_SC_2;
			पूर्ण
		पूर्ण
		asb100_ग_लिखो_value(client, ASB100_REG_I2C_SUBADDR,
					(क्रमce_subclients[2] & 0x07) |
					((क्रमce_subclients[3] & 0x07) << 4));
		sc_addr[0] = क्रमce_subclients[2];
		sc_addr[1] = क्रमce_subclients[3];
	पूर्ण अन्यथा अणु
		पूर्णांक val = asb100_पढ़ो_value(client, ASB100_REG_I2C_SUBADDR);
		sc_addr[0] = 0x48 + (val & 0x07);
		sc_addr[1] = 0x48 + ((val >> 4) & 0x07);
	पूर्ण

	अगर (sc_addr[0] == sc_addr[1]) अणु
		dev_err(&client->dev,
			"duplicate addresses 0x%x for subclients\n",
			sc_addr[0]);
		err = -ENODEV;
		जाओ ERROR_SC_2;
	पूर्ण

	data->lm75[0] = i2c_new_dummy_device(adapter, sc_addr[0]);
	अगर (IS_ERR(data->lm75[0])) अणु
		dev_err(&client->dev,
			"subclient %d registration at address 0x%x failed.\n",
			1, sc_addr[0]);
		err = PTR_ERR(data->lm75[0]);
		जाओ ERROR_SC_2;
	पूर्ण

	data->lm75[1] = i2c_new_dummy_device(adapter, sc_addr[1]);
	अगर (IS_ERR(data->lm75[1])) अणु
		dev_err(&client->dev,
			"subclient %d registration at address 0x%x failed.\n",
			2, sc_addr[1]);
		err = PTR_ERR(data->lm75[1]);
		जाओ ERROR_SC_3;
	पूर्ण

	वापस 0;

/* Unकरो inits in हाल of errors */
ERROR_SC_3:
	i2c_unरेजिस्टर_device(data->lm75[0]);
ERROR_SC_2:
	वापस err;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक asb100_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक val1, val2;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		pr_debug("detect failed, smbus byte data not supported!\n");
		वापस -ENODEV;
	पूर्ण

	val1 = i2c_smbus_पढ़ो_byte_data(client, ASB100_REG_BANK);
	val2 = i2c_smbus_पढ़ो_byte_data(client, ASB100_REG_CHIPMAN);

	/* If we're in bank 0 */
	अगर ((!(val1 & 0x07)) &&
			/* Check क्रम ASB100 ID (low byte) */
			(((!(val1 & 0x80)) && (val2 != 0x94)) ||
			/* Check क्रम ASB100 ID (high byte ) */
			((val1 & 0x80) && (val2 != 0x06)))) अणु
		pr_debug("detect failed, bad chip id 0x%02x!\n", val2);
		वापस -ENODEV;
	पूर्ण

	/* Put it now पूर्णांकo bank 0 and Venकरोr ID High Byte */
	i2c_smbus_ग_लिखो_byte_data(client, ASB100_REG_BANK,
		(i2c_smbus_पढ़ो_byte_data(client, ASB100_REG_BANK) & 0x78)
		| 0x80);

	/* Determine the chip type. */
	val1 = i2c_smbus_पढ़ो_byte_data(client, ASB100_REG_WCHIPID);
	val2 = i2c_smbus_पढ़ो_byte_data(client, ASB100_REG_CHIPMAN);

	अगर (val1 != 0x31 || val2 != 0x06)
		वापस -ENODEV;

	strlcpy(info->type, "asb100", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक asb100_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक err;
	काष्ठा asb100_data *data;

	data = devm_kzalloc(&client->dev, माप(काष्ठा asb100_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);

	/* Attach secondary lm75 clients */
	err = asb100_detect_subclients(client);
	अगर (err)
		वापस err;

	/* Initialize the chip */
	asb100_init_client(client);

	/* A few vars need to be filled upon startup */
	data->fan_min[0] = asb100_पढ़ो_value(client, ASB100_REG_FAN_MIN(0));
	data->fan_min[1] = asb100_पढ़ो_value(client, ASB100_REG_FAN_MIN(1));
	data->fan_min[2] = asb100_पढ़ो_value(client, ASB100_REG_FAN_MIN(2));

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &asb100_group);
	अगर (err)
		जाओ ERROR3;

	data->hwmon_dev = hwmon_device_रेजिस्टर(&client->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ ERROR4;
	पूर्ण

	वापस 0;

ERROR4:
	sysfs_हटाओ_group(&client->dev.kobj, &asb100_group);
ERROR3:
	i2c_unरेजिस्टर_device(data->lm75[1]);
	i2c_unरेजिस्टर_device(data->lm75[0]);
	वापस err;
पूर्ण

अटल पूर्णांक asb100_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा asb100_data *data = i2c_get_clientdata(client);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&client->dev.kobj, &asb100_group);

	i2c_unरेजिस्टर_device(data->lm75[1]);
	i2c_unरेजिस्टर_device(data->lm75[0]);

	वापस 0;
पूर्ण

/*
 * The SMBus locks itself, usually, but nothing may access the chip between
 * bank चयनes.
 */
अटल पूर्णांक asb100_पढ़ो_value(काष्ठा i2c_client *client, u16 reg)
अणु
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	काष्ठा i2c_client *cl;
	पूर्णांक res, bank;

	mutex_lock(&data->lock);

	bank = (reg >> 8) & 0x0f;
	अगर (bank > 2)
		/* चयन banks */
		i2c_smbus_ग_लिखो_byte_data(client, ASB100_REG_BANK, bank);

	अगर (bank == 0 || bank > 2) अणु
		res = i2c_smbus_पढ़ो_byte_data(client, reg & 0xff);
	पूर्ण अन्यथा अणु
		/* चयन to subclient */
		cl = data->lm75[bank - 1];

		/* convert from ISA to LM75 I2C addresses */
		चयन (reg & 0xff) अणु
		हाल 0x50: /* TEMP */
			res = i2c_smbus_पढ़ो_word_swapped(cl, 0);
			अवरोध;
		हाल 0x52: /* CONFIG */
			res = i2c_smbus_पढ़ो_byte_data(cl, 1);
			अवरोध;
		हाल 0x53: /* HYST */
			res = i2c_smbus_पढ़ो_word_swapped(cl, 2);
			अवरोध;
		हाल 0x55: /* MAX */
		शेष:
			res = i2c_smbus_पढ़ो_word_swapped(cl, 3);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bank > 2)
		i2c_smbus_ग_लिखो_byte_data(client, ASB100_REG_BANK, 0);

	mutex_unlock(&data->lock);

	वापस res;
पूर्ण

अटल व्योम asb100_ग_लिखो_value(काष्ठा i2c_client *client, u16 reg, u16 value)
अणु
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	काष्ठा i2c_client *cl;
	पूर्णांक bank;

	mutex_lock(&data->lock);

	bank = (reg >> 8) & 0x0f;
	अगर (bank > 2)
		/* चयन banks */
		i2c_smbus_ग_लिखो_byte_data(client, ASB100_REG_BANK, bank);

	अगर (bank == 0 || bank > 2) अणु
		i2c_smbus_ग_लिखो_byte_data(client, reg & 0xff, value & 0xff);
	पूर्ण अन्यथा अणु
		/* चयन to subclient */
		cl = data->lm75[bank - 1];

		/* convert from ISA to LM75 I2C addresses */
		चयन (reg & 0xff) अणु
		हाल 0x52: /* CONFIG */
			i2c_smbus_ग_लिखो_byte_data(cl, 1, value & 0xff);
			अवरोध;
		हाल 0x53: /* HYST */
			i2c_smbus_ग_लिखो_word_swapped(cl, 2, value);
			अवरोध;
		हाल 0x55: /* MAX */
			i2c_smbus_ग_लिखो_word_swapped(cl, 3, value);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bank > 2)
		i2c_smbus_ग_लिखो_byte_data(client, ASB100_REG_BANK, 0);

	mutex_unlock(&data->lock);
पूर्ण

अटल व्योम asb100_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा asb100_data *data = i2c_get_clientdata(client);

	data->vrm = vid_which_vrm();

	/* Start monitoring */
	asb100_ग_लिखो_value(client, ASB100_REG_CONFIG,
		(asb100_पढ़ो_value(client, ASB100_REG_CONFIG) & 0xf7) | 0x01);
पूर्ण

अटल काष्ठा asb100_data *asb100_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा asb100_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
		|| !data->valid) अणु

		dev_dbg(&client->dev, "starting device update...\n");

		/* 7 voltage inमाला_दो */
		क्रम (i = 0; i < 7; i++) अणु
			data->in[i] = asb100_पढ़ो_value(client,
				ASB100_REG_IN(i));
			data->in_min[i] = asb100_पढ़ो_value(client,
				ASB100_REG_IN_MIN(i));
			data->in_max[i] = asb100_पढ़ो_value(client,
				ASB100_REG_IN_MAX(i));
		पूर्ण

		/* 3 fan inमाला_दो */
		क्रम (i = 0; i < 3; i++) अणु
			data->fan[i] = asb100_पढ़ो_value(client,
					ASB100_REG_FAN(i));
			data->fan_min[i] = asb100_पढ़ो_value(client,
					ASB100_REG_FAN_MIN(i));
		पूर्ण

		/* 4 temperature inमाला_दो */
		क्रम (i = 1; i <= 4; i++) अणु
			data->temp[i-1] = asb100_पढ़ो_value(client,
					ASB100_REG_TEMP(i));
			data->temp_max[i-1] = asb100_पढ़ो_value(client,
					ASB100_REG_TEMP_MAX(i));
			data->temp_hyst[i-1] = asb100_पढ़ो_value(client,
					ASB100_REG_TEMP_HYST(i));
		पूर्ण

		/* VID and fan भागisors */
		i = asb100_पढ़ो_value(client, ASB100_REG_VID_FANDIV);
		data->vid = i & 0x0f;
		data->vid |= (asb100_पढ़ो_value(client,
				ASB100_REG_CHIPID) & 0x01) << 4;
		data->fan_भाग[0] = (i >> 4) & 0x03;
		data->fan_भाग[1] = (i >> 6) & 0x03;
		data->fan_भाग[2] = (asb100_पढ़ो_value(client,
				ASB100_REG_PIN) >> 6) & 0x03;

		/* PWM */
		data->pwm = asb100_पढ़ो_value(client, ASB100_REG_PWM1);

		/* alarms */
		data->alarms = asb100_पढ़ो_value(client, ASB100_REG_ALARM1) +
			(asb100_पढ़ो_value(client, ASB100_REG_ALARM2) << 8);

		data->last_updated = jअगरfies;
		data->valid = 1;

		dev_dbg(&client->dev, "... device update complete\n");
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

module_i2c_driver(asb100_driver);

MODULE_AUTHOR("Mark M. Hoffman <mhoffman@lightlink.com>");
MODULE_DESCRIPTION("ASB100 Bach driver");
MODULE_LICENSE("GPL");
