<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm80.c - From lm_sensors, Linux kernel modules क्रम hardware
 *	    monitoring
 * Copyright (C) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl>
 *			     and Philip Edelbrock <phil@netroedge.com>
 *
 * Ported to Linux 2.6 by Tiago Sousa <mirage@kaotik.org>
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

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CLIENT_END पूर्ण;

/* Many LM80 स्थिरants specअगरied below */

/* The LM80 रेजिस्टरs */
#घोषणा LM80_REG_IN_MAX(nr)		(0x2a + (nr) * 2)
#घोषणा LM80_REG_IN_MIN(nr)		(0x2b + (nr) * 2)
#घोषणा LM80_REG_IN(nr)			(0x20 + (nr))

#घोषणा LM80_REG_FAN1			0x28
#घोषणा LM80_REG_FAN2			0x29
#घोषणा LM80_REG_FAN_MIN(nr)		(0x3b + (nr))

#घोषणा LM80_REG_TEMP			0x27
#घोषणा LM80_REG_TEMP_HOT_MAX		0x38
#घोषणा LM80_REG_TEMP_HOT_HYST		0x39
#घोषणा LM80_REG_TEMP_OS_MAX		0x3a
#घोषणा LM80_REG_TEMP_OS_HYST		0x3b

#घोषणा LM80_REG_CONFIG			0x00
#घोषणा LM80_REG_ALARM1			0x01
#घोषणा LM80_REG_ALARM2			0x02
#घोषणा LM80_REG_MASK1			0x03
#घोषणा LM80_REG_MASK2			0x04
#घोषणा LM80_REG_FANDIV			0x05
#घोषणा LM80_REG_RES			0x06

#घोषणा LM96080_REG_CONV_RATE		0x07
#घोषणा LM96080_REG_MAN_ID		0x3e
#घोषणा LM96080_REG_DEV_ID		0x3f


/*
 * Conversions. Rounding and limit checking is only करोne on the TO_REG
 * variants. Note that you should be a bit careful with which arguments
 * these macros are called: arguments may be evaluated more than once.
 * Fixing this is just not worth it.
 */

#घोषणा IN_TO_REG(val)		(clamp_val(((val) + 5) / 10, 0, 255))
#घोषणा IN_FROM_REG(val)	((val) * 10)

अटल अंतरभूत अचिन्हित अक्षर FAN_TO_REG(अचिन्हित rpm, अचिन्हित भाग)
अणु
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

#घोषणा FAN_FROM_REG(val, भाग)	((val) == 0 ? -1 : \
				(val) == 255 ? 0 : 1350000/((भाग) * (val)))

#घोषणा TEMP_FROM_REG(reg)	((reg) * 125 / 32)
#घोषणा TEMP_TO_REG(temp)	(DIV_ROUND_CLOSEST(clamp_val((temp), \
					-128000, 127000), 1000) << 8)

#घोषणा DIV_FROM_REG(val)		(1 << (val))

क्रमागत temp_index अणु
	t_input = 0,
	t_hot_max,
	t_hot_hyst,
	t_os_max,
	t_os_hyst,
	t_num_temp
पूर्ण;

अटल स्थिर u8 temp_regs[t_num_temp] = अणु
	[t_input] = LM80_REG_TEMP,
	[t_hot_max] = LM80_REG_TEMP_HOT_MAX,
	[t_hot_hyst] = LM80_REG_TEMP_HOT_HYST,
	[t_os_max] = LM80_REG_TEMP_OS_MAX,
	[t_os_hyst] = LM80_REG_TEMP_OS_HYST,
पूर्ण;

क्रमागत in_index अणु
	i_input = 0,
	i_max,
	i_min,
	i_num_in
पूर्ण;

क्रमागत fan_index अणु
	f_input,
	f_min,
	f_num_fan
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा lm80_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर error;		/* !=0 अगर error occurred during last update */
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 in[i_num_in][7];	/* Register value, 1st index is क्रमागत in_index */
	u8 fan[f_num_fan][2];	/* Register value, 1st index क्रमागत fan_index */
	u8 fan_भाग[2];		/* Register encoding, shअगरted right */
	s16 temp[t_num_temp];	/* Register values, normalized to 16 bit */
	u16 alarms;		/* Register encoding, combined */
पूर्ण;

अटल पूर्णांक lm80_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक lm80_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

/* Called when we have found a new LM80 and after पढ़ो errors */
अटल व्योम lm80_init_client(काष्ठा i2c_client *client)
अणु
	/*
	 * Reset all except Watchकरोg values and last conversion values
	 * This sets fan-भागs to 2, among others. This makes most other
	 * initializations unnecessary
	 */
	lm80_ग_लिखो_value(client, LM80_REG_CONFIG, 0x80);
	/* Set 11-bit temperature resolution */
	lm80_ग_लिखो_value(client, LM80_REG_RES, 0x08);

	/* Start monitoring */
	lm80_ग_लिखो_value(client, LM80_REG_CONFIG, 0x01);
पूर्ण

अटल काष्ठा lm80_data *lm80_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm80_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;
	पूर्णांक rv;
	पूर्णांक prev_rv;
	काष्ठा lm80_data *ret = data;

	mutex_lock(&data->update_lock);

	अगर (data->error)
		lm80_init_client(client);

	अगर (समय_after(jअगरfies, data->last_updated + 2 * HZ) || !data->valid) अणु
		dev_dbg(dev, "Starting lm80 update\n");
		क्रम (i = 0; i <= 6; i++) अणु
			rv = lm80_पढ़ो_value(client, LM80_REG_IN(i));
			अगर (rv < 0)
				जाओ पात;
			data->in[i_input][i] = rv;

			rv = lm80_पढ़ो_value(client, LM80_REG_IN_MIN(i));
			अगर (rv < 0)
				जाओ पात;
			data->in[i_min][i] = rv;

			rv = lm80_पढ़ो_value(client, LM80_REG_IN_MAX(i));
			अगर (rv < 0)
				जाओ पात;
			data->in[i_max][i] = rv;
		पूर्ण

		rv = lm80_पढ़ो_value(client, LM80_REG_FAN1);
		अगर (rv < 0)
			जाओ पात;
		data->fan[f_input][0] = rv;

		rv = lm80_पढ़ो_value(client, LM80_REG_FAN_MIN(1));
		अगर (rv < 0)
			जाओ पात;
		data->fan[f_min][0] = rv;

		rv = lm80_पढ़ो_value(client, LM80_REG_FAN2);
		अगर (rv < 0)
			जाओ पात;
		data->fan[f_input][1] = rv;

		rv = lm80_पढ़ो_value(client, LM80_REG_FAN_MIN(2));
		अगर (rv < 0)
			जाओ पात;
		data->fan[f_min][1] = rv;

		prev_rv = rv = lm80_पढ़ो_value(client, LM80_REG_TEMP);
		अगर (rv < 0)
			जाओ पात;
		rv = lm80_पढ़ो_value(client, LM80_REG_RES);
		अगर (rv < 0)
			जाओ पात;
		data->temp[t_input] = (prev_rv << 8) | (rv & 0xf0);

		क्रम (i = t_input + 1; i < t_num_temp; i++) अणु
			rv = lm80_पढ़ो_value(client, temp_regs[i]);
			अगर (rv < 0)
				जाओ पात;
			data->temp[i] = rv << 8;
		पूर्ण

		rv = lm80_पढ़ो_value(client, LM80_REG_FANDIV);
		अगर (rv < 0)
			जाओ पात;
		data->fan_भाग[0] = (rv >> 2) & 0x03;
		data->fan_भाग[1] = (rv >> 4) & 0x03;

		prev_rv = rv = lm80_पढ़ो_value(client, LM80_REG_ALARM1);
		अगर (rv < 0)
			जाओ पात;
		rv = lm80_पढ़ो_value(client, LM80_REG_ALARM2);
		अगर (rv < 0)
			जाओ पात;
		data->alarms = prev_rv + (rv << 8);

		data->last_updated = jअगरfies;
		data->valid = 1;
		data->error = 0;
	पूर्ण
	जाओ करोne;

पात:
	ret = ERR_PTR(rv);
	data->valid = 0;
	data->error = 1;

करोne:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा lm80_data *data = lm80_update_device(dev);
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in[nr][index]));
पूर्ण

अटल sमाप_प्रकार in_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm80_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;
	दीर्घ val;
	u8 reg;
	पूर्णांक err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	reg = nr == i_min ? LM80_REG_IN_MIN(index) : LM80_REG_IN_MAX(index);

	mutex_lock(&data->update_lock);
	data->in[nr][index] = IN_TO_REG(val);
	lm80_ग_लिखो_value(client, reg, data->in[nr][index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;
	काष्ठा lm80_data *data = lm80_update_device(dev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr][index],
		       DIV_FROM_REG(data->fan_भाग[index])));
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm80_data *data = lm80_update_device(dev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार fan_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	पूर्णांक nr = to_sensor_dev_attr_2(attr)->nr;
	काष्ठा lm80_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan[nr][index] = FAN_TO_REG(val,
					  DIV_FROM_REG(data->fan_भाग[index]));
	lm80_ग_लिखो_value(client, LM80_REG_FAN_MIN(index + 1),
			 data->fan[nr][index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm80_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ min, val;
	u8 reg;
	पूर्णांक rv;

	rv = kम_से_अदीर्घ(buf, 10, &val);
	अगर (rv < 0)
		वापस rv;

	/* Save fan_min */
	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan[f_min][nr],
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

	rv = lm80_पढ़ो_value(client, LM80_REG_FANDIV);
	अगर (rv < 0) अणु
		mutex_unlock(&data->update_lock);
		वापस rv;
	पूर्ण
	reg = (rv & ~(3 << (2 * (nr + 1))))
	    | (data->fan_भाग[nr] << (2 * (nr + 1)));
	lm80_ग_लिखो_value(client, LM80_REG_FANDIV, reg);

	/* Restore fan_min */
	data->fan[f_min][nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	lm80_ग_लिखो_value(client, LM80_REG_FAN_MIN(nr + 1),
			 data->fan[f_min][nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm80_data *data = lm80_update_device(dev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा lm80_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[nr] = TEMP_TO_REG(val);
	lm80_ग_लिखो_value(client, temp_regs[nr], data->temp[nr] >> 8);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm80_data *data = lm80_update_device(dev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm80_data *data = lm80_update_device(dev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_2_RW(in0_min, in, i_min, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_min, in, i_min, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_min, in, i_min, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_min, in, i_min, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_min, in, i_min, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_min, in, i_min, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_min, in, i_min, 6);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_max, in, i_max, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_max, in, i_max, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_max, in, i_max, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_max, in, i_max, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_max, in, i_max, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_max, in, i_max, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_max, in, i_max, 6);
अटल SENSOR_DEVICE_ATTR_2_RO(in0_input, in, i_input, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_input, in, i_input, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_input, in, i_input, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in3_input, in, i_input, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(in4_input, in, i_input, 4);
अटल SENSOR_DEVICE_ATTR_2_RO(in5_input, in, i_input, 5);
अटल SENSOR_DEVICE_ATTR_2_RO(in6_input, in, i_input, 6);
अटल SENSOR_DEVICE_ATTR_2_RW(fan1_min, fan, f_min, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(fan2_min, fan, f_min, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(fan1_input, fan, f_input, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(fan2_input, fan, f_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, t_input);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, t_hot_max);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, temp, t_hot_hyst);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp, t_os_max);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit_hyst, temp, t_os_hyst);
अटल DEVICE_ATTR_RO(alarms);
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, alarm, 13);

/*
 * Real code
 */

अटल काष्ठा attribute *lm80_attrs[] = अणु
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&dev_attr_alarms.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm80);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm80_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक i, cur, man_id, dev_id;
	स्थिर अक्षर *name = शून्य;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* First check क्रम unused bits, common to both chip types */
	अगर ((lm80_पढ़ो_value(client, LM80_REG_ALARM2) & 0xc0)
	 || (lm80_पढ़ो_value(client, LM80_REG_CONFIG) & 0x80))
		वापस -ENODEV;

	/*
	 * The LM96080 has manufacturer and stepping/die rev रेजिस्टरs so we
	 * can just check that. The LM80 करोes not have such रेजिस्टरs so we
	 * have to use a more expensive trick.
	 */
	man_id = lm80_पढ़ो_value(client, LM96080_REG_MAN_ID);
	dev_id = lm80_पढ़ो_value(client, LM96080_REG_DEV_ID);
	अगर (man_id == 0x01 && dev_id == 0x08) अणु
		/* Check more unused bits क्रम confirmation */
		अगर (lm80_पढ़ो_value(client, LM96080_REG_CONV_RATE) & 0xfe)
			वापस -ENODEV;

		name = "lm96080";
	पूर्ण अन्यथा अणु
		/* Check 6-bit addressing */
		क्रम (i = 0x2a; i <= 0x3d; i++) अणु
			cur = i2c_smbus_पढ़ो_byte_data(client, i);
			अगर ((i2c_smbus_पढ़ो_byte_data(client, i + 0x40) != cur)
			 || (i2c_smbus_पढ़ो_byte_data(client, i + 0x80) != cur)
			 || (i2c_smbus_पढ़ो_byte_data(client, i + 0xc0) != cur))
				वापस -ENODEV;
		पूर्ण

		name = "lm80";
	पूर्ण

	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक lm80_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm80_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा lm80_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the LM80 chip */
	lm80_init_client(client);

	/* A few vars need to be filled upon startup */
	data->fan[f_min][0] = lm80_पढ़ो_value(client, LM80_REG_FAN_MIN(1));
	data->fan[f_min][1] = lm80_पढ़ो_value(client, LM80_REG_FAN_MIN(2));

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, lm80_groups);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id lm80_id[] = अणु
	अणु "lm80", 0 पूर्ण,
	अणु "lm96080", 1 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm80_id);

अटल काष्ठा i2c_driver lm80_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm80",
	पूर्ण,
	.probe_new	= lm80_probe,
	.id_table	= lm80_id,
	.detect		= lm80_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm80_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl> and "
	"Philip Edelbrock <phil@netroedge.com>");
MODULE_DESCRIPTION("LM80 driver");
MODULE_LICENSE("GPL");
