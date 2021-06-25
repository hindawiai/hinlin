<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * gl520sm.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 * Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl>,
 *			     Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>
 * Copyright (c) 2005	Maarten Deprez <maartendeprez@users.sourceक्रमge.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>

/* Type of the extra sensor */
अटल अचिन्हित लघु extra_sensor_type;
module_param(extra_sensor_type, uलघु, 0);
MODULE_PARM_DESC(extra_sensor_type, "Type of extra sensor (0=autodetect, 1=temperature, 2=voltage)");

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, I2C_CLIENT_END पूर्ण;

/*
 * Many GL520 स्थिरants specअगरied below
 * One of the inमाला_दो can be configured as either temp or voltage.
 * That's why _TEMP2 and _IN4 access the same रेजिस्टर
 */

/* The GL520 रेजिस्टरs */
#घोषणा GL520_REG_CHIP_ID		0x00
#घोषणा GL520_REG_REVISION		0x01
#घोषणा GL520_REG_CONF			0x03
#घोषणा GL520_REG_MASK			0x11

#घोषणा GL520_REG_VID_INPUT		0x02

अटल स्थिर u8 GL520_REG_IN_INPUT[]	= अणु 0x15, 0x14, 0x13, 0x0d, 0x0e पूर्ण;
अटल स्थिर u8 GL520_REG_IN_LIMIT[]	= अणु 0x0c, 0x09, 0x0a, 0x0b पूर्ण;
अटल स्थिर u8 GL520_REG_IN_MIN[]	= अणु 0x0c, 0x09, 0x0a, 0x0b, 0x18 पूर्ण;
अटल स्थिर u8 GL520_REG_IN_MAX[]	= अणु 0x0c, 0x09, 0x0a, 0x0b, 0x17 पूर्ण;

अटल स्थिर u8 GL520_REG_TEMP_INPUT[]		= अणु 0x04, 0x0e पूर्ण;
अटल स्थिर u8 GL520_REG_TEMP_MAX[]		= अणु 0x05, 0x17 पूर्ण;
अटल स्थिर u8 GL520_REG_TEMP_MAX_HYST[]	= अणु 0x06, 0x18 पूर्ण;

#घोषणा GL520_REG_FAN_INPUT		0x07
#घोषणा GL520_REG_FAN_MIN		0x08
#घोषणा GL520_REG_FAN_DIV		0x0f
#घोषणा GL520_REG_FAN_OFF		GL520_REG_FAN_DIV

#घोषणा GL520_REG_ALARMS		0x12
#घोषणा GL520_REG_BEEP_MASK		0x10
#घोषणा GL520_REG_BEEP_ENABLE		GL520_REG_CONF

/* Client data */
काष्ठा gl520_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	काष्ठा mutex update_lock;
	अक्षर valid;		/* zero until the following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */

	u8 vid;
	u8 vrm;
	u8 in_input[5];		/* [0] = VVD */
	u8 in_min[5];		/* [0] = VDD */
	u8 in_max[5];		/* [0] = VDD */
	u8 fan_input[2];
	u8 fan_min[2];
	u8 fan_भाग[2];
	u8 fan_off;
	u8 temp_input[2];
	u8 temp_max[2];
	u8 temp_max_hyst[2];
	u8 alarms;
	u8 beep_enable;
	u8 beep_mask;
	u8 alarm_mask;
	u8 two_temps;
पूर्ण;

/*
 * Registers 0x07 to 0x0c are word-sized, others are byte-sized
 * GL520 uses a high-byte first convention
 */
अटल पूर्णांक gl520_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	अगर ((reg >= 0x07) && (reg <= 0x0c))
		वापस i2c_smbus_पढ़ो_word_swapped(client, reg);
	अन्यथा
		वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक gl520_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, u16 value)
अणु
	अगर ((reg >= 0x07) && (reg <= 0x0c))
		वापस i2c_smbus_ग_लिखो_word_swapped(client, reg, value);
	अन्यथा
		वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल काष्ठा gl520_data *gl520_update_device(काष्ठा device *dev)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक val, i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + 2 * HZ) || !data->valid) अणु

		dev_dbg(&client->dev, "Starting gl520sm update\n");

		data->alarms = gl520_पढ़ो_value(client, GL520_REG_ALARMS);
		data->beep_mask = gl520_पढ़ो_value(client, GL520_REG_BEEP_MASK);
		data->vid = gl520_पढ़ो_value(client,
					     GL520_REG_VID_INPUT) & 0x1f;

		क्रम (i = 0; i < 4; i++) अणु
			data->in_input[i] = gl520_पढ़ो_value(client,
							GL520_REG_IN_INPUT[i]);
			val = gl520_पढ़ो_value(client, GL520_REG_IN_LIMIT[i]);
			data->in_min[i] = val & 0xff;
			data->in_max[i] = (val >> 8) & 0xff;
		पूर्ण

		val = gl520_पढ़ो_value(client, GL520_REG_FAN_INPUT);
		data->fan_input[0] = (val >> 8) & 0xff;
		data->fan_input[1] = val & 0xff;

		val = gl520_पढ़ो_value(client, GL520_REG_FAN_MIN);
		data->fan_min[0] = (val >> 8) & 0xff;
		data->fan_min[1] = val & 0xff;

		data->temp_input[0] = gl520_पढ़ो_value(client,
						GL520_REG_TEMP_INPUT[0]);
		data->temp_max[0] = gl520_पढ़ो_value(client,
						GL520_REG_TEMP_MAX[0]);
		data->temp_max_hyst[0] = gl520_पढ़ो_value(client,
						GL520_REG_TEMP_MAX_HYST[0]);

		val = gl520_पढ़ो_value(client, GL520_REG_FAN_DIV);
		data->fan_भाग[0] = (val >> 6) & 0x03;
		data->fan_भाग[1] = (val >> 4) & 0x03;
		data->fan_off = (val >> 2) & 0x01;

		data->alarms &= data->alarm_mask;

		val = gl520_पढ़ो_value(client, GL520_REG_CONF);
		data->beep_enable = !((val >> 2) & 1);

		/* Temp1 and Vin4 are the same input */
		अगर (data->two_temps) अणु
			data->temp_input[1] = gl520_पढ़ो_value(client,
						GL520_REG_TEMP_INPUT[1]);
			data->temp_max[1] = gl520_पढ़ो_value(client,
						GL520_REG_TEMP_MAX[1]);
			data->temp_max_hyst[1] = gl520_पढ़ो_value(client,
						GL520_REG_TEMP_MAX_HYST[1]);
		पूर्ण अन्यथा अणु
			data->in_input[4] = gl520_पढ़ो_value(client,
						GL520_REG_IN_INPUT[4]);
			data->in_min[4] = gl520_पढ़ो_value(client,
						GL520_REG_IN_MIN[4]);
			data->in_max[4] = gl520_पढ़ो_value(client,
						GL520_REG_IN_MAX[4]);
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gl520_data *data = gl520_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", vid_from_reg(data->vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

#घोषणा VDD_FROM_REG(val)	DIV_ROUND_CLOSEST((val) * 95, 4)
#घोषणा VDD_CLAMP(val)		clamp_val(val, 0, 255 * 95 / 4)
#घोषणा VDD_TO_REG(val)		DIV_ROUND_CLOSEST(VDD_CLAMP(val) * 4, 95)

#घोषणा IN_FROM_REG(val)	((val) * 19)
#घोषणा IN_CLAMP(val)		clamp_val(val, 0, 255 * 19)
#घोषणा IN_TO_REG(val)		DIV_ROUND_CLOSEST(IN_CLAMP(val), 19)

अटल sमाप_प्रकार in_input_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);
	u8 r = data->in_input[n];

	अगर (n == 0)
		वापस प्र_लिखो(buf, "%d\n", VDD_FROM_REG(r));
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(r));
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);
	u8 r = data->in_min[n];

	अगर (n == 0)
		वापस प्र_लिखो(buf, "%d\n", VDD_FROM_REG(r));
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(r));
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);
	u8 r = data->in_max[n];

	अगर (n == 0)
		वापस प्र_लिखो(buf, "%d\n", VDD_FROM_REG(r));
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(r));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	u8 r;
	दीर्घ v;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	अगर (n == 0)
		r = VDD_TO_REG(v);
	अन्यथा
		r = IN_TO_REG(v);

	data->in_min[n] = r;

	अगर (n < 4)
		gl520_ग_लिखो_value(client, GL520_REG_IN_MIN[n],
				  (gl520_पढ़ो_value(client, GL520_REG_IN_MIN[n])
				   & ~0xff) | r);
	अन्यथा
		gl520_ग_लिखो_value(client, GL520_REG_IN_MIN[n], r);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	u8 r;
	दीर्घ v;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	अगर (n == 0)
		r = VDD_TO_REG(v);
	अन्यथा
		r = IN_TO_REG(v);

	mutex_lock(&data->update_lock);

	data->in_max[n] = r;

	अगर (n < 4)
		gl520_ग_लिखो_value(client, GL520_REG_IN_MAX[n],
				  (gl520_पढ़ो_value(client, GL520_REG_IN_MAX[n])
				   & ~0xff00) | (r << 8));
	अन्यथा
		gl520_ग_लिखो_value(client, GL520_REG_IN_MAX[n], r);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, in_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in_input, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in_input, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in_input, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in_input, 4);
अटल SENSOR_DEVICE_ATTR_RW(in0_min, in_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in0_max, in_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 4);

#घोषणा DIV_FROM_REG(val) (1 << (val))
#घोषणा FAN_FROM_REG(val, भाग) ((val) == 0 ? 0 : (480000 / ((val) << (भाग))))

#घोषणा FAN_BASE(भाग)		(480000 >> (भाग))
#घोषणा FAN_CLAMP(val, भाग)	clamp_val(val, FAN_BASE(भाग) / 255, \
					  FAN_BASE(भाग))
#घोषणा FAN_TO_REG(val, भाग)	((val) == 0 ? 0 : \
				 DIV_ROUND_CLOSEST(480000, \
						FAN_CLAMP(val, भाग) << (भाग)))

अटल sमाप_प्रकार fan_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_input[n],
						 data->fan_भाग[n]));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[n],
						 data->fan_भाग[n]));
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[n]));
पूर्ण

अटल sमाप_प्रकार fan1_off_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gl520_data *data = gl520_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->fan_off);
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	u8 r;
	अचिन्हित दीर्घ v;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	r = FAN_TO_REG(v, data->fan_भाग[n]);
	data->fan_min[n] = r;

	अगर (n == 0)
		gl520_ग_लिखो_value(client, GL520_REG_FAN_MIN,
				  (gl520_पढ़ो_value(client, GL520_REG_FAN_MIN)
				   & ~0xff00) | (r << 8));
	अन्यथा
		gl520_ग_लिखो_value(client, GL520_REG_FAN_MIN,
				  (gl520_पढ़ो_value(client, GL520_REG_FAN_MIN)
				   & ~0xff) | r);

	data->beep_mask = gl520_पढ़ो_value(client, GL520_REG_BEEP_MASK);
	अगर (data->fan_min[n] == 0)
		data->alarm_mask &= (n == 0) ? ~0x20 : ~0x40;
	अन्यथा
		data->alarm_mask |= (n == 0) ? 0x20 : 0x40;
	data->beep_mask &= data->alarm_mask;
	gl520_ग_लिखो_value(client, GL520_REG_BEEP_MASK, data->beep_mask);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	u8 r;
	अचिन्हित दीर्घ v;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	चयन (v) अणु
	हाल 1:
		r = 0;
		अवरोध;
	हाल 2:
		r = 1;
		अवरोध;
	हाल 4:
		r = 2;
		अवरोध;
	हाल 8:
		r = 3;
		अवरोध;
	शेष:
		dev_err(&client->dev,
	"fan_div value %ld not supported. Choose one of 1, 2, 4 or 8!\n", v);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->fan_भाग[n] = r;

	अगर (n == 0)
		gl520_ग_लिखो_value(client, GL520_REG_FAN_DIV,
				  (gl520_पढ़ो_value(client, GL520_REG_FAN_DIV)
				   & ~0xc0) | (r << 6));
	अन्यथा
		gl520_ग_लिखो_value(client, GL520_REG_FAN_DIV,
				  (gl520_पढ़ो_value(client, GL520_REG_FAN_DIV)
				   & ~0x30) | (r << 4));

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan1_off_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 r;
	अचिन्हित दीर्घ v;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	r = (v ? 1 : 0);

	mutex_lock(&data->update_lock);
	data->fan_off = r;
	gl520_ग_लिखो_value(client, GL520_REG_FAN_OFF,
			  (gl520_पढ़ो_value(client, GL520_REG_FAN_OFF)
			   & ~0x0c) | (r << 2));
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);
अटल DEVICE_ATTR_RW(fan1_off);

#घोषणा TEMP_FROM_REG(val)	(((val) - 130) * 1000)
#घोषणा TEMP_CLAMP(val)		clamp_val(val, -130000, 125000)
#घोषणा TEMP_TO_REG(val)	(DIV_ROUND_CLOSEST(TEMP_CLAMP(val), 1000) + 130)

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_input[n]));
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[n]));
पूर्ण

अटल sमाप_प्रकार temp_max_hyst_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max_hyst[n]));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	दीर्घ v;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[n] = TEMP_TO_REG(v);
	gl520_ग_लिखो_value(client, GL520_REG_TEMP_MAX[n], data->temp_max[n]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_hyst_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक n = to_sensor_dev_attr(attr)->index;
	दीर्घ v;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max_hyst[n] = TEMP_TO_REG(v);
	gl520_ग_लिखो_value(client, GL520_REG_TEMP_MAX_HYST[n],
			  data->temp_max_hyst[n]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, temp_max_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max_hyst, temp_max_hyst, 1);

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा gl520_data *data = gl520_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार beep_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gl520_data *data = gl520_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->beep_enable);
पूर्ण

अटल sमाप_प्रकार beep_mask_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा gl520_data *data = gl520_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->beep_mask);
पूर्ण

अटल sमाप_प्रकार beep_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 r;
	अचिन्हित दीर्घ v;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &v);
	अगर (err)
		वापस err;

	r = (v ? 0 : 1);

	mutex_lock(&data->update_lock);
	data->beep_enable = !r;
	gl520_ग_लिखो_value(client, GL520_REG_BEEP_ENABLE,
			  (gl520_पढ़ो_value(client, GL520_REG_BEEP_ENABLE)
			   & ~0x04) | (r << 2));
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार beep_mask_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ r;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &r);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	r &= data->alarm_mask;
	data->beep_mask = r;
	gl520_ग_लिखो_value(client, GL520_REG_BEEP_MASK, r);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(alarms);
अटल DEVICE_ATTR_RW(beep_enable);
अटल DEVICE_ATTR_RW(beep_mask);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक bit_nr = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", (data->alarms >> bit_nr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 7);

अटल sमाप_प्रकार beep_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा gl520_data *data = gl520_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", (data->beep_mask >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार beep_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gl520_data *data = dev_get_drvdata(dev);
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
	data->beep_mask = gl520_पढ़ो_value(client, GL520_REG_BEEP_MASK);
	अगर (bit)
		data->beep_mask |= (1 << bitnr);
	अन्यथा
		data->beep_mask &= ~(1 << bitnr);
	gl520_ग_लिखो_value(client, GL520_REG_BEEP_MASK, data->beep_mask);
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
अटल SENSOR_DEVICE_ATTR_RW(temp2_beep, beep, 7);
अटल SENSOR_DEVICE_ATTR_RW(in4_beep, beep, 7);

अटल काष्ठा attribute *gl520_attributes[] = अणु
	&dev_attr_cpu0_vid.attr,

	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_beep.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_beep.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_beep.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_beep.dev_attr.attr,

	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_beep.dev_attr.attr,
	&dev_attr_fan1_off.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_beep.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_beep.dev_attr.attr,

	&dev_attr_alarms.attr,
	&dev_attr_beep_enable.attr,
	&dev_attr_beep_mask.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gl520_group = अणु
	.attrs = gl520_attributes,
पूर्ण;

अटल काष्ठा attribute *gl520_attributes_in4[] = अणु
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_beep.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *gl520_attributes_temp2[] = अणु
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_beep.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gl520_group_in4 = अणु
	.attrs = gl520_attributes_in4,
पूर्ण;

अटल स्थिर काष्ठा attribute_group gl520_group_temp2 = अणु
	.attrs = gl520_attributes_temp2,
पूर्ण;


/*
 * Real code
 */

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक gl520_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	/* Determine the chip type. */
	अगर ((gl520_पढ़ो_value(client, GL520_REG_CHIP_ID) != 0x20) ||
	    ((gl520_पढ़ो_value(client, GL520_REG_REVISION) & 0x7f) != 0x00) ||
	    ((gl520_पढ़ो_value(client, GL520_REG_CONF) & 0x80) != 0x00)) अणु
		dev_dbg(&client->dev, "Unknown chip type, skipping\n");
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "gl520sm", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

/* Called when we have found a new GL520SM. */
अटल व्योम gl520_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा gl520_data *data = i2c_get_clientdata(client);
	u8 oldconf, conf;

	conf = oldconf = gl520_पढ़ो_value(client, GL520_REG_CONF);

	data->alarm_mask = 0xff;
	data->vrm = vid_which_vrm();

	अगर (extra_sensor_type == 1)
		conf &= ~0x10;
	अन्यथा अगर (extra_sensor_type == 2)
		conf |= 0x10;
	data->two_temps = !(conf & 0x10);

	/* If IRQ# is disabled, we can safely क्रमce comparator mode */
	अगर (!(conf & 0x20))
		conf &= 0xf7;

	/* Enable monitoring अगर needed */
	conf |= 0x40;

	अगर (conf != oldconf)
		gl520_ग_लिखो_value(client, GL520_REG_CONF, conf);

	gl520_update_device(&(client->dev));

	अगर (data->fan_min[0] == 0)
		data->alarm_mask &= ~0x20;
	अगर (data->fan_min[1] == 0)
		data->alarm_mask &= ~0x40;

	data->beep_mask &= data->alarm_mask;
	gl520_ग_लिखो_value(client, GL520_REG_BEEP_MASK, data->beep_mask);
पूर्ण

अटल पूर्णांक gl520_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा gl520_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा gl520_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->client = client;

	/* Initialize the GL520SM chip */
	gl520_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &gl520_group;

	अगर (data->two_temps)
		data->groups[1] = &gl520_group_temp2;
	अन्यथा
		data->groups[1] = &gl520_group_in4;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id gl520_id[] = अणु
	अणु "gl520sm", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, gl520_id);

अटल काष्ठा i2c_driver gl520_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "gl520sm",
	पूर्ण,
	.probe_new	= gl520_probe,
	.id_table	= gl520_id,
	.detect		= gl520_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(gl520_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>, "
	"Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>, "
	"Maarten Deprez <maartendeprez@users.sourceforge.net>");
MODULE_DESCRIPTION("GL520SM driver");
MODULE_LICENSE("GPL");
