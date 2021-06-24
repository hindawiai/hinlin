<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * w83l786ng.c - Linux kernel driver क्रम hardware monitoring
 * Copyright (c) 2007 Kevin Lo <kevlo@kevlo.org>
 */

/*
 * Supports following chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83l786ng	3	2	2	2	0x7b	0x5ca3	yes	no
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2e, 0x2f, I2C_CLIENT_END पूर्ण;

/* Insmod parameters */

अटल bool reset;
module_param(reset, bool, 0);
MODULE_PARM_DESC(reset, "Set to 1 to reset chip, not recommended");

#घोषणा W83L786NG_REG_IN_MIN(nr)	(0x2C + (nr) * 2)
#घोषणा W83L786NG_REG_IN_MAX(nr)	(0x2B + (nr) * 2)
#घोषणा W83L786NG_REG_IN(nr)		((nr) + 0x20)

#घोषणा W83L786NG_REG_FAN(nr)		((nr) + 0x28)
#घोषणा W83L786NG_REG_FAN_MIN(nr)	((nr) + 0x3B)

#घोषणा W83L786NG_REG_CONFIG		0x40
#घोषणा W83L786NG_REG_ALARM1		0x41
#घोषणा W83L786NG_REG_ALARM2		0x42
#घोषणा W83L786NG_REG_GPIO_EN		0x47
#घोषणा W83L786NG_REG_MAN_ID2		0x4C
#घोषणा W83L786NG_REG_MAN_ID1		0x4D
#घोषणा W83L786NG_REG_CHIP_ID		0x4E

#घोषणा W83L786NG_REG_DIODE		0x53
#घोषणा W83L786NG_REG_FAN_DIV		0x54
#घोषणा W83L786NG_REG_FAN_CFG		0x80

#घोषणा W83L786NG_REG_TOLERANCE		0x8D

अटल स्थिर u8 W83L786NG_REG_TEMP[2][3] = अणु
	अणु 0x25,		/* TEMP 0 in DataSheet */
	  0x35,		/* TEMP 0 Over in DataSheet */
	  0x36 पूर्ण,	/* TEMP 0 Hyst in DataSheet */
	अणु 0x26,		/* TEMP 1 in DataSheet */
	  0x37,		/* TEMP 1 Over in DataSheet */
	  0x38 पूर्ण	/* TEMP 1 Hyst in DataSheet */
पूर्ण;

अटल स्थिर u8 W83L786NG_PWM_MODE_SHIFT[] = अणु6, 7पूर्ण;
अटल स्थिर u8 W83L786NG_PWM_ENABLE_SHIFT[] = अणु2, 4पूर्ण;

/* FAN Duty Cycle, be used to control */
अटल स्थिर u8 W83L786NG_REG_PWM[] = अणु0x81, 0x87पूर्ण;


अटल अंतरभूत u8
FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

#घोषणा FAN_FROM_REG(val, भाग)	((val) == 0   ? -1 : \
				((val) == 255 ? 0 : \
				1350000 / ((val) * (भाग))))

/* क्रम temp */
#घोषणा TEMP_TO_REG(val)	(clamp_val(((val) < 0 ? (val) + 0x100 * 1000 \
						      : (val)) / 1000, 0, 0xff))
#घोषणा TEMP_FROM_REG(val)	(((val) & 0x80 ? \
				  (val) - 0x100 : (val)) * 1000)

/*
 * The analog voltage inमाला_दो have 8mV LSB. Since the sysfs output is
 * in mV as would be measured on the chip input pin, need to just
 * multiply/भागide by 8 to translate from/to रेजिस्टर values.
 */
#घोषणा IN_TO_REG(val)		(clamp_val((((val) + 4) / 8), 0, 255))
#घोषणा IN_FROM_REG(val)	((val) * 8)

#घोषणा DIV_FROM_REG(val)	(1 << (val))

अटल अंतरभूत u8
DIV_TO_REG(दीर्घ val)
अणु
	पूर्णांक i;
	val = clamp_val(val, 1, 128) >> 1;
	क्रम (i = 0; i < 7; i++) अणु
		अगर (val == 0)
			अवरोध;
		val >>= 1;
	पूर्ण
	वापस (u8)i;
पूर्ण

काष्ठा w83l786ng_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ last_nonअस्थिर;	/* In jअगरfies, last समय we update the
					 * nonअस्थिर रेजिस्टरs */

	u8 in[3];
	u8 in_max[3];
	u8 in_min[3];
	u8 fan[2];
	u8 fan_भाग[2];
	u8 fan_min[2];
	u8 temp_type[2];
	u8 temp[2][3];
	u8 pwm[2];
	u8 pwm_mode[2];	/* 0->DC variable voltage
			 * 1->PWM variable duty cycle */

	u8 pwm_enable[2]; /* 1->manual
			   * 2->thermal cruise (also called SmartFan I) */
	u8 tolerance[2];
पूर्ण;

अटल u8
w83l786ng_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक
w83l786ng_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल काष्ठा w83l786ng_data *w83l786ng_update_device(काष्ठा device *dev)
अणु
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i, j;
	u8 reg_पंचांगp, pwmcfg;

	mutex_lock(&data->update_lock);
	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		dev_dbg(&client->dev, "Updating w83l786ng data.\n");

		/* Update the voltages measured value and limits */
		क्रम (i = 0; i < 3; i++) अणु
			data->in[i] = w83l786ng_पढ़ो_value(client,
			    W83L786NG_REG_IN(i));
			data->in_min[i] = w83l786ng_पढ़ो_value(client,
			    W83L786NG_REG_IN_MIN(i));
			data->in_max[i] = w83l786ng_पढ़ो_value(client,
			    W83L786NG_REG_IN_MAX(i));
		पूर्ण

		/* Update the fan counts and limits */
		क्रम (i = 0; i < 2; i++) अणु
			data->fan[i] = w83l786ng_पढ़ो_value(client,
			    W83L786NG_REG_FAN(i));
			data->fan_min[i] = w83l786ng_पढ़ो_value(client,
			    W83L786NG_REG_FAN_MIN(i));
		पूर्ण

		/* Update the fan भागisor */
		reg_पंचांगp = w83l786ng_पढ़ो_value(client, W83L786NG_REG_FAN_DIV);
		data->fan_भाग[0] = reg_पंचांगp & 0x07;
		data->fan_भाग[1] = (reg_पंचांगp >> 4) & 0x07;

		pwmcfg = w83l786ng_पढ़ो_value(client, W83L786NG_REG_FAN_CFG);
		क्रम (i = 0; i < 2; i++) अणु
			data->pwm_mode[i] =
			    ((pwmcfg >> W83L786NG_PWM_MODE_SHIFT[i]) & 1)
			    ? 0 : 1;
			data->pwm_enable[i] =
			    ((pwmcfg >> W83L786NG_PWM_ENABLE_SHIFT[i]) & 3) + 1;
			data->pwm[i] =
			    (w83l786ng_पढ़ो_value(client, W83L786NG_REG_PWM[i])
			     & 0x0f) * 0x11;
		पूर्ण


		/* Update the temperature sensors */
		क्रम (i = 0; i < 2; i++) अणु
			क्रम (j = 0; j < 3; j++) अणु
				data->temp[i][j] = w83l786ng_पढ़ो_value(client,
				    W83L786NG_REG_TEMP[i][j]);
			पूर्ण
		पूर्ण

		/* Update Smart Fan I/II tolerance */
		reg_पंचांगp = w83l786ng_पढ़ो_value(client, W83L786NG_REG_TOLERANCE);
		data->tolerance[0] = reg_पंचांगp & 0x0f;
		data->tolerance[1] = (reg_पंचांगp >> 4) & 0x0f;

		data->last_updated = jअगरfies;
		data->valid = 1;

	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* following are the sysfs callback functions */
#घोषणा show_in_reg(reg) \
अटल sमाप_प्रकार \
show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
	   अक्षर *buf) \
अणु \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	काष्ठा w83l786ng_data *data = w83l786ng_update_device(dev); \
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->reg[nr])); \
पूर्ण

show_in_reg(in)
show_in_reg(in_min)
show_in_reg(in_max)

#घोषणा store_in_reg(REG, reg) \
अटल sमाप_प्रकार \
store_in_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
	       स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev); \
	काष्ठा i2c_client *client = data->client; \
	अचिन्हित दीर्घ val; \
	पूर्णांक err = kम_से_अदीर्घ(buf, 10, &val); \
	अगर (err) \
		वापस err; \
	mutex_lock(&data->update_lock); \
	data->in_##reg[nr] = IN_TO_REG(val); \
	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_IN_##REG(nr), \
			      data->in_##reg[nr]); \
	mutex_unlock(&data->update_lock); \
	वापस count; \
पूर्ण

store_in_reg(MIN, min)
store_in_reg(MAX, max)

अटल काष्ठा sensor_device_attribute sda_in_input[] = अणु
	SENSOR_ATTR(in0_input, S_IRUGO, show_in, शून्य, 0),
	SENSOR_ATTR(in1_input, S_IRUGO, show_in, शून्य, 1),
	SENSOR_ATTR(in2_input, S_IRUGO, show_in, शून्य, 2),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_in_min[] = अणु
	SENSOR_ATTR(in0_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 0),
	SENSOR_ATTR(in1_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 1),
	SENSOR_ATTR(in2_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 2),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_in_max[] = अणु
	SENSOR_ATTR(in0_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 0),
	SENSOR_ATTR(in1_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 1),
	SENSOR_ATTR(in2_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 2),
पूर्ण;

#घोषणा show_fan_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			  अक्षर *buf) \
अणु \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	काष्ठा w83l786ng_data *data = w83l786ng_update_device(dev); \
	वापस प्र_लिखो(buf, "%d\n", \
		FAN_FROM_REG(data->reg[nr], DIV_FROM_REG(data->fan_भाग[nr]))); \
पूर्ण

show_fan_reg(fan);
show_fan_reg(fan_min);

अटल sमाप_प्रकार
store_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_FAN_MIN(nr),
			      data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
	     अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = w83l786ng_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार
store_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	अचिन्हित दीर्घ min;
	u8 पंचांगp_fan_भाग;
	u8 fan_भाग_reg;
	u8 keep_mask = 0;
	u8 new_shअगरt = 0;

	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	/* Save fan_min */
	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan_min[nr], DIV_FROM_REG(data->fan_भाग[nr]));

	data->fan_भाग[nr] = DIV_TO_REG(val);

	चयन (nr) अणु
	हाल 0:
		keep_mask = 0xf8;
		new_shअगरt = 0;
		अवरोध;
	हाल 1:
		keep_mask = 0x8f;
		new_shअगरt = 4;
		अवरोध;
	पूर्ण

	fan_भाग_reg = w83l786ng_पढ़ो_value(client, W83L786NG_REG_FAN_DIV)
					   & keep_mask;

	पंचांगp_fan_भाग = (data->fan_भाग[nr] << new_shअगरt) & ~keep_mask;

	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_FAN_DIV,
			      fan_भाग_reg | पंचांगp_fan_भाग);

	/* Restore fan_min */
	data->fan_min[nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_FAN_MIN(nr),
			      data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_fan_input[] = अणु
	SENSOR_ATTR(fan1_input, S_IRUGO, show_fan, शून्य, 0),
	SENSOR_ATTR(fan2_input, S_IRUGO, show_fan, शून्य, 1),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_fan_min[] = अणु
	SENSOR_ATTR(fan1_min, S_IWUSR | S_IRUGO, show_fan_min,
		    store_fan_min, 0),
	SENSOR_ATTR(fan2_min, S_IWUSR | S_IRUGO, show_fan_min,
		    store_fan_min, 1),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_fan_भाग[] = अणु
	SENSOR_ATTR(fan1_भाग, S_IWUSR | S_IRUGO, show_fan_भाग,
		    store_fan_भाग, 0),
	SENSOR_ATTR(fan2_भाग, S_IWUSR | S_IRUGO, show_fan_भाग,
		    store_fan_भाग, 1),
पूर्ण;


/* पढ़ो/ग_लिखो the temperature, includes measured value and limits */

अटल sमाप_प्रकार
show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83l786ng_data *data = w83l786ng_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[nr][index]));
पूर्ण

अटल sमाप_प्रकार
store_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[nr][index] = TEMP_TO_REG(val);
	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_TEMP[nr][index],
			      data->temp[nr][index]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute_2 sda_temp_input[] = अणु
	SENSOR_ATTR_2(temp1_input, S_IRUGO, show_temp, शून्य, 0, 0),
	SENSOR_ATTR_2(temp2_input, S_IRUGO, show_temp, शून्य, 1, 0),
पूर्ण;

अटल काष्ठा sensor_device_attribute_2 sda_temp_max[] = अणु
	SENSOR_ATTR_2(temp1_max, S_IRUGO | S_IWUSR,
		      show_temp, store_temp, 0, 1),
	SENSOR_ATTR_2(temp2_max, S_IRUGO | S_IWUSR,
		      show_temp, store_temp, 1, 1),
पूर्ण;

अटल काष्ठा sensor_device_attribute_2 sda_temp_max_hyst[] = अणु
	SENSOR_ATTR_2(temp1_max_hyst, S_IRUGO | S_IWUSR,
		      show_temp, store_temp, 0, 2),
	SENSOR_ATTR_2(temp2_max_hyst, S_IRUGO | S_IWUSR,
		      show_temp, store_temp, 1, 2),
पूर्ण;

#घोषणा show_pwm_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			  अक्षर *buf) \
अणु \
	काष्ठा w83l786ng_data *data = w83l786ng_update_device(dev); \
	पूर्णांक nr = to_sensor_dev_attr(attr)->index; \
	वापस प्र_लिखो(buf, "%d\n", data->reg[nr]); \
पूर्ण

show_pwm_reg(pwm_mode)
show_pwm_reg(pwm_enable)
show_pwm_reg(pwm)

अटल sमाप_प्रकार
store_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;
	mutex_lock(&data->update_lock);
	data->pwm_mode[nr] = val;
	reg = w83l786ng_पढ़ो_value(client, W83L786NG_REG_FAN_CFG);
	reg &= ~(1 << W83L786NG_PWM_MODE_SHIFT[nr]);
	अगर (!val)
		reg |= 1 << W83L786NG_PWM_MODE_SHIFT[nr];
	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_FAN_CFG, reg);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
store_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	val = clamp_val(val, 0, 255);
	val = DIV_ROUND_CLOSEST(val, 0x11);

	mutex_lock(&data->update_lock);
	data->pwm[nr] = val * 0x11;
	val |= w83l786ng_पढ़ो_value(client, W83L786NG_REG_PWM[nr]) & 0xf0;
	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_PWM[nr], val);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
store_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (!val || val > 2)  /* only modes 1 and 2 are supported */
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	reg = w83l786ng_पढ़ो_value(client, W83L786NG_REG_FAN_CFG);
	data->pwm_enable[nr] = val;
	reg &= ~(0x03 << W83L786NG_PWM_ENABLE_SHIFT[nr]);
	reg |= (val - 1) << W83L786NG_PWM_ENABLE_SHIFT[nr];
	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_FAN_CFG, reg);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_pwm[] = अणु
	SENSOR_ATTR(pwm1, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 0),
	SENSOR_ATTR(pwm2, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 1),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_pwm_mode[] = अणु
	SENSOR_ATTR(pwm1_mode, S_IWUSR | S_IRUGO, show_pwm_mode,
		    store_pwm_mode, 0),
	SENSOR_ATTR(pwm2_mode, S_IWUSR | S_IRUGO, show_pwm_mode,
		    store_pwm_mode, 1),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_pwm_enable[] = अणु
	SENSOR_ATTR(pwm1_enable, S_IWUSR | S_IRUGO, show_pwm_enable,
		    store_pwm_enable, 0),
	SENSOR_ATTR(pwm2_enable, S_IWUSR | S_IRUGO, show_pwm_enable,
		    store_pwm_enable, 1),
पूर्ण;

/* For Smart Fan I/Thermal Cruise and Smart Fan II */
अटल sमाप_प्रकार
show_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = w83l786ng_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)data->tolerance[nr]);
पूर्ण

अटल sमाप_प्रकार
store_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा w83l786ng_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 tol_पंचांगp, tol_mask;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	tol_mask = w83l786ng_पढ़ो_value(client,
	    W83L786NG_REG_TOLERANCE) & ((nr == 1) ? 0x0f : 0xf0);
	tol_पंचांगp = clamp_val(val, 0, 15);
	tol_पंचांगp &= 0x0f;
	data->tolerance[nr] = tol_पंचांगp;
	अगर (nr == 1)
		tol_पंचांगp <<= 4;

	w83l786ng_ग_लिखो_value(client, W83L786NG_REG_TOLERANCE,
			      tol_mask | tol_पंचांगp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_tolerance[] = अणु
	SENSOR_ATTR(pwm1_tolerance, S_IWUSR | S_IRUGO,
		    show_tolerance, store_tolerance, 0),
	SENSOR_ATTR(pwm2_tolerance, S_IWUSR | S_IRUGO,
		    show_tolerance, store_tolerance, 1),
पूर्ण;


#घोषणा IN_UNIT_ATTRS(X)	\
	&sda_in_input[X].dev_attr.attr,		\
	&sda_in_min[X].dev_attr.attr,		\
	&sda_in_max[X].dev_attr.attr

#घोषणा FAN_UNIT_ATTRS(X)	\
	&sda_fan_input[X].dev_attr.attr,	\
	&sda_fan_min[X].dev_attr.attr,		\
	&sda_fan_भाग[X].dev_attr.attr

#घोषणा TEMP_UNIT_ATTRS(X)	\
	&sda_temp_input[X].dev_attr.attr,	\
	&sda_temp_max[X].dev_attr.attr,		\
	&sda_temp_max_hyst[X].dev_attr.attr

#घोषणा PWM_UNIT_ATTRS(X)	\
	&sda_pwm[X].dev_attr.attr,		\
	&sda_pwm_mode[X].dev_attr.attr,		\
	&sda_pwm_enable[X].dev_attr.attr

#घोषणा TOLERANCE_UNIT_ATTRS(X)	\
	&sda_tolerance[X].dev_attr.attr

अटल काष्ठा attribute *w83l786ng_attrs[] = अणु
	IN_UNIT_ATTRS(0),
	IN_UNIT_ATTRS(1),
	IN_UNIT_ATTRS(2),
	FAN_UNIT_ATTRS(0),
	FAN_UNIT_ATTRS(1),
	TEMP_UNIT_ATTRS(0),
	TEMP_UNIT_ATTRS(1),
	PWM_UNIT_ATTRS(0),
	PWM_UNIT_ATTRS(1),
	TOLERANCE_UNIT_ATTRS(0),
	TOLERANCE_UNIT_ATTRS(1),
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(w83l786ng);

अटल पूर्णांक
w83l786ng_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	u16 man_id;
	u8 chip_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Detection */
	अगर ((w83l786ng_पढ़ो_value(client, W83L786NG_REG_CONFIG) & 0x80)) अणु
		dev_dbg(&adapter->dev, "W83L786NG detection failed at 0x%02x\n",
			client->addr);
		वापस -ENODEV;
	पूर्ण

	/* Identअगरication */
	man_id = (w83l786ng_पढ़ो_value(client, W83L786NG_REG_MAN_ID1) << 8) +
		 w83l786ng_पढ़ो_value(client, W83L786NG_REG_MAN_ID2);
	chip_id = w83l786ng_पढ़ो_value(client, W83L786NG_REG_CHIP_ID);

	अगर (man_id != 0x5CA3 ||		/* Winbond */
	    chip_id != 0x80) अणु		/* W83L786NG */
		dev_dbg(&adapter->dev,
			"Unsupported chip (man_id=0x%04X, chip_id=0x%02X)\n",
			man_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "w83l786ng", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम w83l786ng_init_client(काष्ठा i2c_client *client)
अणु
	u8 पंचांगp;

	अगर (reset)
		w83l786ng_ग_लिखो_value(client, W83L786NG_REG_CONFIG, 0x80);

	/* Start monitoring */
	पंचांगp = w83l786ng_पढ़ो_value(client, W83L786NG_REG_CONFIG);
	अगर (!(पंचांगp & 0x01))
		w83l786ng_ग_लिखो_value(client, W83L786NG_REG_CONFIG, पंचांगp | 0x01);
पूर्ण

अटल पूर्णांक
w83l786ng_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा w83l786ng_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक i;
	u8 reg_पंचांगp;

	data = devm_kzalloc(dev, माप(काष्ठा w83l786ng_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the chip */
	w83l786ng_init_client(client);

	/* A few vars need to be filled upon startup */
	क्रम (i = 0; i < 2; i++) अणु
		data->fan_min[i] = w83l786ng_पढ़ो_value(client,
		    W83L786NG_REG_FAN_MIN(i));
	पूर्ण

	/* Update the fan भागisor */
	reg_पंचांगp = w83l786ng_पढ़ो_value(client, W83L786NG_REG_FAN_DIV);
	data->fan_भाग[0] = reg_पंचांगp & 0x07;
	data->fan_भाग[1] = (reg_पंचांगp >> 4) & 0x07;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   w83l786ng_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id w83l786ng_id[] = अणु
	अणु "w83l786ng", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, w83l786ng_id);

अटल काष्ठा i2c_driver w83l786ng_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		   .name = "w83l786ng",
	पूर्ण,
	.probe_new	= w83l786ng_probe,
	.id_table	= w83l786ng_id,
	.detect		= w83l786ng_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(w83l786ng_driver);

MODULE_AUTHOR("Kevin Lo");
MODULE_DESCRIPTION("w83l786ng driver");
MODULE_LICENSE("GPL");
