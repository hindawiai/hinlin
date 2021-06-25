<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm78.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	    monitoring
 * Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl>
 * Copyright (c) 2007, 2011  Jean Delvare <jdelvare@suse.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>

#अगर_घोषित CONFIG_ISA
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#पूर्ण_अगर

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CLIENT_END पूर्ण;
क्रमागत chips अणु lm78, lm79 पूर्ण;

/* Many LM78 स्थिरants specअगरied below */

/* Length of ISA address segment */
#घोषणा LM78_EXTENT 8

/* Where are the ISA address/data रेजिस्टरs relative to the base address */
#घोषणा LM78_ADDR_REG_OFFSET 5
#घोषणा LM78_DATA_REG_OFFSET 6

/* The LM78 रेजिस्टरs */
#घोषणा LM78_REG_IN_MAX(nr) (0x2b + (nr) * 2)
#घोषणा LM78_REG_IN_MIN(nr) (0x2c + (nr) * 2)
#घोषणा LM78_REG_IN(nr) (0x20 + (nr))

#घोषणा LM78_REG_FAN_MIN(nr) (0x3b + (nr))
#घोषणा LM78_REG_FAN(nr) (0x28 + (nr))

#घोषणा LM78_REG_TEMP 0x27
#घोषणा LM78_REG_TEMP_OVER 0x39
#घोषणा LM78_REG_TEMP_HYST 0x3a

#घोषणा LM78_REG_ALARM1 0x41
#घोषणा LM78_REG_ALARM2 0x42

#घोषणा LM78_REG_VID_FANDIV 0x47

#घोषणा LM78_REG_CONFIG 0x40
#घोषणा LM78_REG_CHIPID 0x49
#घोषणा LM78_REG_I2C_ADDR 0x48

/*
 * Conversions. Rounding and limit checking is only करोne on the TO_REG
 * variants.
 */

/*
 * IN: mV (0V to 4.08V)
 * REG: 16mV/bit
 */
अटल अंतरभूत u8 IN_TO_REG(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ nval = clamp_val(val, 0, 4080);
	वापस (nval + 8) / 16;
पूर्ण
#घोषणा IN_FROM_REG(val) ((val) *  16)

अटल अंतरभूत u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm <= 0)
		वापस 255;
	अगर (rpm > 1350000)
		वापस 1;
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

अटल अंतरभूत पूर्णांक FAN_FROM_REG(u8 val, पूर्णांक भाग)
अणु
	वापस val == 0 ? -1 : val == 255 ? 0 : 1350000 / (val * भाग);
पूर्ण

/*
 * TEMP: mC (-128C to +127C)
 * REG: 1C/bit, two's complement
 */
अटल अंतरभूत s8 TEMP_TO_REG(दीर्घ val)
अणु
	पूर्णांक nval = clamp_val(val, -128000, 127000) ;
	वापस nval < 0 ? (nval - 500) / 1000 : (nval + 500) / 1000;
पूर्ण

अटल अंतरभूत पूर्णांक TEMP_FROM_REG(s8 val)
अणु
	वापस val * 1000;
पूर्ण

#घोषणा DIV_FROM_REG(val) (1 << (val))

काष्ठा lm78_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	क्रमागत chips type;

	/* For ISA device only */
	स्थिर अक्षर *name;
	पूर्णांक isa_addr;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 in[7];		/* Register value */
	u8 in_max[7];		/* Register value */
	u8 in_min[7];		/* Register value */
	u8 fan[3];		/* Register value */
	u8 fan_min[3];		/* Register value */
	s8 temp;		/* Register value */
	s8 temp_over;		/* Register value */
	s8 temp_hyst;		/* Register value */
	u8 fan_भाग[3];		/* Register encoding, shअगरted right */
	u8 vid;			/* Register encoding, combined */
	u16 alarms;		/* Register encoding, combined */
पूर्ण;

अटल पूर्णांक lm78_पढ़ो_value(काष्ठा lm78_data *data, u8 reg);
अटल पूर्णांक lm78_ग_लिखो_value(काष्ठा lm78_data *data, u8 reg, u8 value);
अटल काष्ठा lm78_data *lm78_update_device(काष्ठा device *dev);
अटल व्योम lm78_init_device(काष्ठा lm78_data *data);

/* 7 Voltages */
अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *da,
		       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in[attr->index]));
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in_min[attr->index]));
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in_max[attr->index]));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val);
	lm78_ग_लिखो_value(data, LM78_REG_IN_MIN(nr), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = IN_TO_REG(val);
	lm78_ग_लिखो_value(data, LM78_REG_IN_MAX(nr), data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, in, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_min, in_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_max, in_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, in, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_min, in_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_max, in_max, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, in, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_min, in_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_max, in_max, 6);

/* Temperature */
अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp));
पूर्ण

अटल sमाप_प्रकार temp1_max_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			      अक्षर *buf)
अणु
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_over));
पूर्ण

अटल sमाप_प्रकार temp1_max_store(काष्ठा device *dev,
			       काष्ठा device_attribute *da, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा lm78_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_over = TEMP_TO_REG(val);
	lm78_ग_लिखो_value(data, LM78_REG_TEMP_OVER, data->temp_over);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp1_max_hyst_show(काष्ठा device *dev,
				   काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_hyst));
पूर्ण

अटल sमाप_प्रकार temp1_max_hyst_store(काष्ठा device *dev,
				    काष्ठा device_attribute *da,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm78_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_hyst = TEMP_TO_REG(val);
	lm78_ग_लिखो_value(data, LM78_REG_TEMP_HYST, data->temp_hyst);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(temp1_input);
अटल DEVICE_ATTR_RW(temp1_max);
अटल DEVICE_ATTR_RW(temp1_max_hyst);

/* 3 Fans */
अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = lm78_update_device(dev);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
		DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = lm78_update_device(dev);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr],
		DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	lm78_ग_लिखो_value(data, LM78_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[attr->index]));
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा lm78_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ min;
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan_min[nr],
			   DIV_FROM_REG(data->fan_भाग[nr]));

	चयन (val) अणु
	हाल 1:
		data->fan_भाग[nr] = 0;
		अवरोध;
	हाल 2:
		data->fan_भाग[nr] = 1;
		अवरोध;
	हाल 4:
		data->fan_भाग[nr] = 2;
		अवरोध;
	हाल 8:
		data->fan_भाग[nr] = 3;
		अवरोध;
	शेष:
		dev_err(dev,
			"fan_div value %ld not supported. Choose one of 1, 2, 4 or 8!\n",
			val);
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	reg = lm78_पढ़ो_value(data, LM78_REG_VID_FANDIV);
	चयन (nr) अणु
	हाल 0:
		reg = (reg & 0xcf) | (data->fan_भाग[nr] << 4);
		अवरोध;
	हाल 1:
		reg = (reg & 0x3f) | (data->fan_भाग[nr] << 6);
		अवरोध;
	पूर्ण
	lm78_ग_लिखो_value(data, LM78_REG_VID_FANDIV, reg);

	data->fan_min[nr] =
		FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	lm78_ग_लिखो_value(data, LM78_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);

/* Fan 3 भागisor is locked in H/W */
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_भाग, fan_भाग, 2);

/* VID */
अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			     अक्षर *buf)
अणु
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, 82));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

/* Alarms */
अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf)
अणु
	काष्ठा lm78_data *data = lm78_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			  अक्षर *buf)
अणु
	काष्ठा lm78_data *data = lm78_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> nr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);

अटल काष्ठा attribute *lm78_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&dev_attr_temp1_input.attr,
	&dev_attr_temp1_max.attr,
	&dev_attr_temp1_max_hyst.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_भाग.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&dev_attr_alarms.attr,
	&dev_attr_cpu0_vid.attr,

	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(lm78);

/*
 * ISA related code
 */
#अगर_घोषित CONFIG_ISA

/* ISA device, अगर found */
अटल काष्ठा platक्रमm_device *pdev;

अटल अचिन्हित लघु isa_address = 0x290;

अटल काष्ठा lm78_data *lm78_data_अगर_isa(व्योम)
अणु
	वापस pdev ? platक्रमm_get_drvdata(pdev) : शून्य;
पूर्ण

/* Returns 1 अगर the I2C chip appears to be an alias of the ISA chip */
अटल पूर्णांक lm78_alias_detect(काष्ठा i2c_client *client, u8 chipid)
अणु
	काष्ठा lm78_data *isa;
	पूर्णांक i;

	अगर (!pdev)	/* No ISA chip */
		वापस 0;
	isa = platक्रमm_get_drvdata(pdev);

	अगर (lm78_पढ़ो_value(isa, LM78_REG_I2C_ADDR) != client->addr)
		वापस 0;	/* Address करोesn't match */
	अगर ((lm78_पढ़ो_value(isa, LM78_REG_CHIPID) & 0xfe) != (chipid & 0xfe))
		वापस 0;	/* Chip type करोesn't match */

	/*
	 * We compare all the limit रेजिस्टरs, the config रेजिस्टर and the
	 * पूर्णांकerrupt mask रेजिस्टरs
	 */
	क्रम (i = 0x2b; i <= 0x3d; i++) अणु
		अगर (lm78_पढ़ो_value(isa, i) !=
		    i2c_smbus_पढ़ो_byte_data(client, i))
			वापस 0;
	पूर्ण
	अगर (lm78_पढ़ो_value(isa, LM78_REG_CONFIG) !=
	    i2c_smbus_पढ़ो_byte_data(client, LM78_REG_CONFIG))
		वापस 0;
	क्रम (i = 0x43; i <= 0x46; i++) अणु
		अगर (lm78_पढ़ो_value(isa, i) !=
		    i2c_smbus_पढ़ो_byte_data(client, i))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
#अन्यथा /* !CONFIG_ISA */

अटल पूर्णांक lm78_alias_detect(काष्ठा i2c_client *client, u8 chipid)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा lm78_data *lm78_data_अगर_isa(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_ISA */

अटल पूर्णांक lm78_i2c_detect(काष्ठा i2c_client *client,
			   काष्ठा i2c_board_info *info)
अणु
	पूर्णांक i;
	काष्ठा lm78_data *isa = lm78_data_अगर_isa();
	स्थिर अक्षर *client_name;
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक address = client->addr;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/*
	 * We block updates of the ISA device to minimize the risk of
	 * concurrent access to the same LM78 chip through dअगरferent
	 * पूर्णांकerfaces.
	 */
	अगर (isa)
		mutex_lock(&isa->update_lock);

	अगर ((i2c_smbus_पढ़ो_byte_data(client, LM78_REG_CONFIG) & 0x80)
	 || i2c_smbus_पढ़ो_byte_data(client, LM78_REG_I2C_ADDR) != address)
		जाओ err_nodev;

	/* Explicitly prevent the misdetection of Winbond chips */
	i = i2c_smbus_पढ़ो_byte_data(client, 0x4f);
	अगर (i == 0xa3 || i == 0x5c)
		जाओ err_nodev;

	/* Determine the chip type. */
	i = i2c_smbus_पढ़ो_byte_data(client, LM78_REG_CHIPID);
	अगर (i == 0x00 || i == 0x20	/* LM78 */
	 || i == 0x40)			/* LM78-J */
		client_name = "lm78";
	अन्यथा अगर ((i & 0xfe) == 0xc0)
		client_name = "lm79";
	अन्यथा
		जाओ err_nodev;

	अगर (lm78_alias_detect(client, i)) अणु
		dev_dbg(&adapter->dev,
			"Device at 0x%02x appears to be the same as ISA device\n",
			address);
		जाओ err_nodev;
	पूर्ण

	अगर (isa)
		mutex_unlock(&isa->update_lock);

	strlcpy(info->type, client_name, I2C_NAME_SIZE);

	वापस 0;

 err_nodev:
	अगर (isa)
		mutex_unlock(&isa->update_lock);
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm78_i2c_id[];

अटल पूर्णांक lm78_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm78_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा lm78_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->type = i2c_match_id(lm78_i2c_id, client)->driver_data;

	/* Initialize the LM78 chip */
	lm78_init_device(data);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, lm78_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm78_i2c_id[] = अणु
	अणु "lm78", lm78 पूर्ण,
	अणु "lm79", lm79 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm78_i2c_id);

अटल काष्ठा i2c_driver lm78_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm78",
	पूर्ण,
	.probe_new	= lm78_i2c_probe,
	.id_table	= lm78_i2c_id,
	.detect		= lm78_i2c_detect,
	.address_list	= normal_i2c,
पूर्ण;

/*
 * The SMBus locks itself, but ISA access must be locked explicitly!
 * We करोn't want to lock the whole ISA bus, so we lock each client
 * separately.
 * We ignore the LM78 BUSY flag at this moment - it could lead to deadlocks,
 * would slow करोwn the LM78 access and should not be necessary.
 */
अटल पूर्णांक lm78_पढ़ो_value(काष्ठा lm78_data *data, u8 reg)
अणु
	काष्ठा i2c_client *client = data->client;

#अगर_घोषित CONFIG_ISA
	अगर (!client) अणु /* ISA device */
		पूर्णांक res;
		mutex_lock(&data->lock);
		outb_p(reg, data->isa_addr + LM78_ADDR_REG_OFFSET);
		res = inb_p(data->isa_addr + LM78_DATA_REG_OFFSET);
		mutex_unlock(&data->lock);
		वापस res;
	पूर्ण अन्यथा
#पूर्ण_अगर
		वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक lm78_ग_लिखो_value(काष्ठा lm78_data *data, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = data->client;

#अगर_घोषित CONFIG_ISA
	अगर (!client) अणु /* ISA device */
		mutex_lock(&data->lock);
		outb_p(reg, data->isa_addr + LM78_ADDR_REG_OFFSET);
		outb_p(value, data->isa_addr + LM78_DATA_REG_OFFSET);
		mutex_unlock(&data->lock);
		वापस 0;
	पूर्ण अन्यथा
#पूर्ण_अगर
		वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल व्योम lm78_init_device(काष्ठा lm78_data *data)
अणु
	u8 config;
	पूर्णांक i;

	/* Start monitoring */
	config = lm78_पढ़ो_value(data, LM78_REG_CONFIG);
	अगर ((config & 0x09) != 0x01)
		lm78_ग_लिखो_value(data, LM78_REG_CONFIG,
				 (config & 0xf7) | 0x01);

	/* A few vars need to be filled upon startup */
	क्रम (i = 0; i < 3; i++) अणु
		data->fan_min[i] = lm78_पढ़ो_value(data,
					LM78_REG_FAN_MIN(i));
	पूर्ण

	mutex_init(&data->update_lock);
पूर्ण

अटल काष्ठा lm78_data *lm78_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm78_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु

		dev_dbg(dev, "Starting lm78 update\n");

		क्रम (i = 0; i <= 6; i++) अणु
			data->in[i] =
			    lm78_पढ़ो_value(data, LM78_REG_IN(i));
			data->in_min[i] =
			    lm78_पढ़ो_value(data, LM78_REG_IN_MIN(i));
			data->in_max[i] =
			    lm78_पढ़ो_value(data, LM78_REG_IN_MAX(i));
		पूर्ण
		क्रम (i = 0; i < 3; i++) अणु
			data->fan[i] =
			    lm78_पढ़ो_value(data, LM78_REG_FAN(i));
			data->fan_min[i] =
			    lm78_पढ़ो_value(data, LM78_REG_FAN_MIN(i));
		पूर्ण
		data->temp = lm78_पढ़ो_value(data, LM78_REG_TEMP);
		data->temp_over =
		    lm78_पढ़ो_value(data, LM78_REG_TEMP_OVER);
		data->temp_hyst =
		    lm78_पढ़ो_value(data, LM78_REG_TEMP_HYST);
		i = lm78_पढ़ो_value(data, LM78_REG_VID_FANDIV);
		data->vid = i & 0x0f;
		अगर (data->type == lm79)
			data->vid |=
			    (lm78_पढ़ो_value(data, LM78_REG_CHIPID) &
			     0x01) << 4;
		अन्यथा
			data->vid |= 0x10;
		data->fan_भाग[0] = (i >> 4) & 0x03;
		data->fan_भाग[1] = i >> 6;
		data->alarms = lm78_पढ़ो_value(data, LM78_REG_ALARM1) +
		    (lm78_पढ़ो_value(data, LM78_REG_ALARM2) << 8);
		data->last_updated = jअगरfies;
		data->valid = 1;

		data->fan_भाग[2] = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

#अगर_घोषित CONFIG_ISA
अटल पूर्णांक lm78_isa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm78_data *data;
	काष्ठा resource *res;

	/* Reserve the ISA region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(dev, res->start + LM78_ADDR_REG_OFFSET,
				 2, "lm78"))
		वापस -EBUSY;

	data = devm_kzalloc(dev, माप(काष्ठा lm78_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->lock);
	data->isa_addr = res->start;
	platक्रमm_set_drvdata(pdev, data);

	अगर (lm78_पढ़ो_value(data, LM78_REG_CHIPID) & 0x80) अणु
		data->type = lm79;
		data->name = "lm79";
	पूर्ण अन्यथा अणु
		data->type = lm78;
		data->name = "lm78";
	पूर्ण

	/* Initialize the LM78 chip */
	lm78_init_device(data);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, data->name,
							   data, lm78_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver lm78_isa_driver = अणु
	.driver = अणु
		.name	= "lm78",
	पूर्ण,
	.probe		= lm78_isa_probe,
पूर्ण;

/* वापस 1 अगर a supported chip is found, 0 otherwise */
अटल पूर्णांक __init lm78_isa_found(अचिन्हित लघु address)
अणु
	पूर्णांक val, save, found = 0;
	पूर्णांक port;

	/*
	 * Some boards declare base+0 to base+7 as a PNP device, some base+4
	 * to base+7 and some base+5 to base+6. So we better request each port
	 * inभागidually क्रम the probing phase.
	 */
	क्रम (port = address; port < address + LM78_EXTENT; port++) अणु
		अगर (!request_region(port, 1, "lm78")) अणु
			pr_debug("Failed to request port 0x%x\n", port);
			जाओ release;
		पूर्ण
	पूर्ण

#घोषणा REALLY_SLOW_IO
	/*
	 * We need the समयouts क्रम at least some LM78-like
	 * chips. But only अगर we पढ़ो 'undefined' रेजिस्टरs.
	 */
	val = inb_p(address + 1);
	अगर (inb_p(address + 2) != val
	 || inb_p(address + 3) != val
	 || inb_p(address + 7) != val)
		जाओ release;
#अघोषित REALLY_SLOW_IO

	/*
	 * We should be able to change the 7 LSB of the address port. The
	 * MSB (busy flag) should be clear initially, set after the ग_लिखो.
	 */
	save = inb_p(address + LM78_ADDR_REG_OFFSET);
	अगर (save & 0x80)
		जाओ release;
	val = ~save & 0x7f;
	outb_p(val, address + LM78_ADDR_REG_OFFSET);
	अगर (inb_p(address + LM78_ADDR_REG_OFFSET) != (val | 0x80)) अणु
		outb_p(save, address + LM78_ADDR_REG_OFFSET);
		जाओ release;
	पूर्ण

	/* We found a device, now see अगर it could be an LM78 */
	outb_p(LM78_REG_CONFIG, address + LM78_ADDR_REG_OFFSET);
	val = inb_p(address + LM78_DATA_REG_OFFSET);
	अगर (val & 0x80)
		जाओ release;
	outb_p(LM78_REG_I2C_ADDR, address + LM78_ADDR_REG_OFFSET);
	val = inb_p(address + LM78_DATA_REG_OFFSET);
	अगर (val < 0x03 || val > 0x77)	/* Not a valid I2C address */
		जाओ release;

	/* The busy flag should be clear again */
	अगर (inb_p(address + LM78_ADDR_REG_OFFSET) & 0x80)
		जाओ release;

	/* Explicitly prevent the misdetection of Winbond chips */
	outb_p(0x4f, address + LM78_ADDR_REG_OFFSET);
	val = inb_p(address + LM78_DATA_REG_OFFSET);
	अगर (val == 0xa3 || val == 0x5c)
		जाओ release;

	/* Explicitly prevent the misdetection of ITE chips */
	outb_p(0x58, address + LM78_ADDR_REG_OFFSET);
	val = inb_p(address + LM78_DATA_REG_OFFSET);
	अगर (val == 0x90)
		जाओ release;

	/* Determine the chip type */
	outb_p(LM78_REG_CHIPID, address + LM78_ADDR_REG_OFFSET);
	val = inb_p(address + LM78_DATA_REG_OFFSET);
	अगर (val == 0x00 || val == 0x20	/* LM78 */
	 || val == 0x40			/* LM78-J */
	 || (val & 0xfe) == 0xc0)	/* LM79 */
		found = 1;

	अगर (found)
		pr_info("Found an %s chip at %#x\n",
			val & 0x80 ? "LM79" : "LM78", (पूर्णांक)address);

 release:
	क्रम (port--; port >= address; port--)
		release_region(port, 1);
	वापस found;
पूर्ण

अटल पूर्णांक __init lm78_isa_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + LM78_EXTENT - 1,
		.name	= "lm78",
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	pdev = platक्रमm_device_alloc("lm78", address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

 निकास_device_put:
	platक्रमm_device_put(pdev);
 निकास:
	pdev = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक __init lm78_isa_रेजिस्टर(व्योम)
अणु
	पूर्णांक res;

	अगर (lm78_isa_found(isa_address)) अणु
		res = platक्रमm_driver_रेजिस्टर(&lm78_isa_driver);
		अगर (res)
			जाओ निकास;

		/* Sets global pdev as a side effect */
		res = lm78_isa_device_add(isa_address);
		अगर (res)
			जाओ निकास_unreg_isa_driver;
	पूर्ण

	वापस 0;

 निकास_unreg_isa_driver:
	platक्रमm_driver_unरेजिस्टर(&lm78_isa_driver);
 निकास:
	वापस res;
पूर्ण

अटल व्योम lm78_isa_unरेजिस्टर(व्योम)
अणु
	अगर (pdev) अणु
		platक्रमm_device_unरेजिस्टर(pdev);
		platक्रमm_driver_unरेजिस्टर(&lm78_isa_driver);
	पूर्ण
पूर्ण
#अन्यथा /* !CONFIG_ISA */

अटल पूर्णांक __init lm78_isa_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम lm78_isa_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ISA */

अटल पूर्णांक __init sm_lm78_init(व्योम)
अणु
	पूर्णांक res;

	/*
	 * We रेजिस्टर the ISA device first, so that we can skip the
	 * registration of an I2C पूर्णांकerface to the same device.
	 */
	res = lm78_isa_रेजिस्टर();
	अगर (res)
		जाओ निकास;

	res = i2c_add_driver(&lm78_driver);
	अगर (res)
		जाओ निकास_unreg_isa_device;

	वापस 0;

 निकास_unreg_isa_device:
	lm78_isa_unरेजिस्टर();
 निकास:
	वापस res;
पूर्ण

अटल व्योम __निकास sm_lm78_निकास(व्योम)
अणु
	lm78_isa_unरेजिस्टर();
	i2c_del_driver(&lm78_driver);
पूर्ण

MODULE_AUTHOR("Frodo Looijaard, Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("LM78/LM79 driver");
MODULE_LICENSE("GPL");

module_init(sm_lm78_init);
module_निकास(sm_lm78_निकास);
