<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm87.c
 *
 * Copyright (C) 2000       Froकरो Looijaard <froकरोl@dds.nl>
 *                          Philip Edelbrock <phil@netroedge.com>
 *                          Stephen Rousset <stephen.rousset@rocketlogix.com>
 *                          Dan Eaton <dan.eaton@rocketlogix.com>
 * Copyright (C) 2004-2008  Jean Delvare <jdelvare@suse.de>
 *
 * Original port to Linux 2.6 by Jeff Oliver.
 *
 * The LM87 is a sensor chip made by National Semiconductor. It monitors up
 * to 8 voltages (including its own घातer source), up to three temperatures
 * (its own plus up to two बाह्यal ones) and up to two fans. The शेष
 * configuration is 6 voltages, two temperatures and two fans (see below).
 * Voltages are scaled पूर्णांकernally with ratios such that the nominal value of
 * each voltage correspond to a रेजिस्टर value of 192 (which means a
 * resolution of about 0.5% of the nominal value). Temperature values are
 * reported with a 1 deg resolution and a 3-4 deg accuracy. Complete
 * datasheet can be obtained from National's website at:
 *   http://www.national.com/pf/LM/LM87.hपंचांगl
 *
 * Some functions share pins, so not all functions are available at the same
 * समय. Which are depends on the hardware setup. This driver normally
 * assumes that firmware configured the chip correctly. Where this is not
 * the हाल, platक्रमm code must set the I2C client's platक्रमm_data to poपूर्णांक
 * to a u8 value to be written to the channel रेजिस्टर.
 * For reference, here is the list of exclusive functions:
 *  - in0+in5 (शेष) or temp3
 *  - fan1 (शेष) or in6
 *  - fan2 (शेष) or in7
 *  - VID lines (शेष) or IRQ lines (not handled by this driver)
 *
 * The LM87 additionally features an analog output, supposedly usable to
 * control the speed of a fan. All new chips use pulse width modulation
 * instead. The LM87 is the only hardware monitoring chipset I know of
 * which uses amplitude modulation. Be careful when using this feature.
 *
 * This driver also supports the ADM1024, a sensor chip made by Analog
 * Devices. That chip is fully compatible with the LM87. Complete
 * datasheet can be obtained from Analog's website at:
 *   https://www.analog.com/en/prod/0,2877,ADM1024,00.hपंचांगl
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
#समावेश <linux/regulator/consumer.h>

/*
 * Addresses to scan
 * LM87 has three possible addresses: 0x2c, 0x2d and 0x2e.
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

/*
 * The LM87 रेजिस्टरs
 */

/* nr in 0..5 */
#घोषणा LM87_REG_IN(nr)			(0x20 + (nr))
#घोषणा LM87_REG_IN_MAX(nr)		(0x2B + (nr) * 2)
#घोषणा LM87_REG_IN_MIN(nr)		(0x2C + (nr) * 2)
/* nr in 0..1 */
#घोषणा LM87_REG_AIN(nr)		(0x28 + (nr))
#घोषणा LM87_REG_AIN_MIN(nr)		(0x1A + (nr))
#घोषणा LM87_REG_AIN_MAX(nr)		(0x3B + (nr))

अटल u8 LM87_REG_TEMP[3] = अणु 0x27, 0x26, 0x20 पूर्ण;
अटल u8 LM87_REG_TEMP_HIGH[3] = अणु 0x39, 0x37, 0x2B पूर्ण;
अटल u8 LM87_REG_TEMP_LOW[3] = अणु 0x3A, 0x38, 0x2C पूर्ण;

#घोषणा LM87_REG_TEMP_HW_INT_LOCK	0x13
#घोषणा LM87_REG_TEMP_HW_EXT_LOCK	0x14
#घोषणा LM87_REG_TEMP_HW_INT		0x17
#घोषणा LM87_REG_TEMP_HW_EXT		0x18

/* nr in 0..1 */
#घोषणा LM87_REG_FAN(nr)		(0x28 + (nr))
#घोषणा LM87_REG_FAN_MIN(nr)		(0x3B + (nr))
#घोषणा LM87_REG_AOUT			0x19

#घोषणा LM87_REG_CONFIG			0x40
#घोषणा LM87_REG_CHANNEL_MODE		0x16
#घोषणा LM87_REG_VID_FAN_DIV		0x47
#घोषणा LM87_REG_VID4			0x49

#घोषणा LM87_REG_ALARMS1		0x41
#घोषणा LM87_REG_ALARMS2		0x42

#घोषणा LM87_REG_COMPANY_ID		0x3E
#घोषणा LM87_REG_REVISION		0x3F

/*
 * Conversions and various macros
 * The LM87 uses चिन्हित 8-bit values क्रम temperatures.
 */

#घोषणा IN_FROM_REG(reg, scale)	(((reg) * (scale) + 96) / 192)
#घोषणा IN_TO_REG(val, scale)	((val) <= 0 ? 0 : \
				 (val) >= (scale) * 255 / 192 ? 255 : \
				 ((val) * 192 + (scale) / 2) / (scale))

#घोषणा TEMP_FROM_REG(reg)	((reg) * 1000)
#घोषणा TEMP_TO_REG(val)	((val) <= -127500 ? -128 : \
				 (val) >= 126500 ? 127 : \
				 (((val) < 0 ? (val) - 500 : \
				   (val) + 500) / 1000))

#घोषणा FAN_FROM_REG(reg, भाग)	((reg) == 255 || (reg) == 0 ? 0 : \
				 (1350000 + (reg)*(भाग) / 2) / ((reg) * (भाग)))
#घोषणा FAN_TO_REG(val, भाग)	((val) * (भाग) * 255 <= 1350000 ? 255 : \
				 (1350000 + (val)*(भाग) / 2) / ((val) * (भाग)))

#घोषणा FAN_DIV_FROM_REG(reg)	(1 << (reg))

/* analog out is 9.80mV/LSB */
#घोषणा AOUT_FROM_REG(reg)	(((reg) * 98 + 5) / 10)
#घोषणा AOUT_TO_REG(val)	((val) <= 0 ? 0 : \
				 (val) >= 2500 ? 255 : \
				 ((val) * 10 + 49) / 98)

/* nr in 0..1 */
#घोषणा CHAN_NO_FAN(nr)		(1 << (nr))
#घोषणा CHAN_TEMP3		(1 << 2)
#घोषणा CHAN_VCC_5V		(1 << 3)
#घोषणा CHAN_NO_VID		(1 << 7)

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा lm87_data अणु
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* In jअगरfies */

	u8 channel;		/* रेजिस्टर value */
	u8 config;		/* original रेजिस्टर value */

	u8 in[8];		/* रेजिस्टर value */
	u8 in_max[8];		/* रेजिस्टर value */
	u8 in_min[8];		/* रेजिस्टर value */
	u16 in_scale[8];

	s8 temp[3];		/* रेजिस्टर value */
	s8 temp_high[3];	/* रेजिस्टर value */
	s8 temp_low[3];		/* रेजिस्टर value */
	s8 temp_crit_पूर्णांक;	/* min of two रेजिस्टर values */
	s8 temp_crit_ext;	/* min of two रेजिस्टर values */

	u8 fan[2];		/* रेजिस्टर value */
	u8 fan_min[2];		/* रेजिस्टर value */
	u8 fan_भाग[2];		/* रेजिस्टर value, shअगरted right */
	u8 aout;		/* रेजिस्टर value */

	u16 alarms;		/* रेजिस्टर values, combined */
	u8 vid;			/* रेजिस्टर values, combined */
	u8 vrm;

	स्थिर काष्ठा attribute_group *attr_groups[6];
पूर्ण;

अटल अंतरभूत पूर्णांक lm87_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक lm87_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल काष्ठा lm87_data *lm87_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		पूर्णांक i, j;

		dev_dbg(&client->dev, "Updating data.\n");

		i = (data->channel & CHAN_TEMP3) ? 1 : 0;
		j = (data->channel & CHAN_TEMP3) ? 5 : 6;
		क्रम (; i < j; i++) अणु
			data->in[i] = lm87_पढ़ो_value(client,
				      LM87_REG_IN(i));
			data->in_min[i] = lm87_पढ़ो_value(client,
					  LM87_REG_IN_MIN(i));
			data->in_max[i] = lm87_पढ़ो_value(client,
					  LM87_REG_IN_MAX(i));
		पूर्ण

		क्रम (i = 0; i < 2; i++) अणु
			अगर (data->channel & CHAN_NO_FAN(i)) अणु
				data->in[6+i] = lm87_पढ़ो_value(client,
						LM87_REG_AIN(i));
				data->in_max[6+i] = lm87_पढ़ो_value(client,
						    LM87_REG_AIN_MAX(i));
				data->in_min[6+i] = lm87_पढ़ो_value(client,
						    LM87_REG_AIN_MIN(i));

			पूर्ण अन्यथा अणु
				data->fan[i] = lm87_पढ़ो_value(client,
					       LM87_REG_FAN(i));
				data->fan_min[i] = lm87_पढ़ो_value(client,
						   LM87_REG_FAN_MIN(i));
			पूर्ण
		पूर्ण

		j = (data->channel & CHAN_TEMP3) ? 3 : 2;
		क्रम (i = 0 ; i < j; i++) अणु
			data->temp[i] = lm87_पढ़ो_value(client,
					LM87_REG_TEMP[i]);
			data->temp_high[i] = lm87_पढ़ो_value(client,
					     LM87_REG_TEMP_HIGH[i]);
			data->temp_low[i] = lm87_पढ़ो_value(client,
					    LM87_REG_TEMP_LOW[i]);
		पूर्ण

		i = lm87_पढ़ो_value(client, LM87_REG_TEMP_HW_INT_LOCK);
		j = lm87_पढ़ो_value(client, LM87_REG_TEMP_HW_INT);
		data->temp_crit_पूर्णांक = min(i, j);

		i = lm87_पढ़ो_value(client, LM87_REG_TEMP_HW_EXT_LOCK);
		j = lm87_पढ़ो_value(client, LM87_REG_TEMP_HW_EXT);
		data->temp_crit_ext = min(i, j);

		i = lm87_पढ़ो_value(client, LM87_REG_VID_FAN_DIV);
		data->fan_भाग[0] = (i >> 4) & 0x03;
		data->fan_भाग[1] = (i >> 6) & 0x03;
		data->vid = (i & 0x0F)
			  | (lm87_पढ़ो_value(client, LM87_REG_VID4) & 0x01)
			     << 4;

		data->alarms = lm87_पढ़ो_value(client, LM87_REG_ALARMS1)
			     | (lm87_पढ़ो_value(client, LM87_REG_ALARMS2)
				<< 8);
		data->aout = lm87_पढ़ो_value(client, LM87_REG_AOUT);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार in_input_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in[nr],
		       data->in_scale[nr]));
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_min[nr],
		       data->in_scale[nr]));
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_max[nr],
		       data->in_scale[nr]));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val, data->in_scale[nr]);
	lm87_ग_लिखो_value(client, nr < 6 ? LM87_REG_IN_MIN(nr) :
			 LM87_REG_AIN_MIN(nr - 6), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = IN_TO_REG(val, data->in_scale[nr]);
	lm87_ग_लिखो_value(client, nr < 6 ? LM87_REG_IN_MAX(nr) :
			 LM87_REG_AIN_MAX(nr - 6), data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, in_input, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_min, in_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_max, in_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in_input, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in_input, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in_input, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, in_input, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_min, in_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_max, in_max, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, in_input, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_min, in_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_max, in_max, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, in_input, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_min, in_min, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_max, in_max, 7);

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[nr]));
पूर्ण

अटल sमाप_प्रकार temp_low_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%d\n",
		       TEMP_FROM_REG(data->temp_low[nr]));
पूर्ण

अटल sमाप_प्रकार temp_high_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%d\n",
		       TEMP_FROM_REG(data->temp_high[nr]));
पूर्ण

अटल sमाप_प्रकार temp_low_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_low[nr] = TEMP_TO_REG(val);
	lm87_ग_लिखो_value(client, LM87_REG_TEMP_LOW[nr], data->temp_low[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_high_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_high[nr] = TEMP_TO_REG(val);
	lm87_ग_लिखो_value(client, LM87_REG_TEMP_HIGH[nr], data->temp_high[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_input, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_low, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_high, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_low, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_high, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp_input, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_low, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_high, 2);

अटल sमाप_प्रकार temp1_crit_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_crit_पूर्णांक));
पूर्ण

अटल sमाप_प्रकार temp2_crit_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_crit_ext));
पूर्ण

अटल DEVICE_ATTR_RO(temp1_crit);
अटल DEVICE_ATTR_RO(temp2_crit);
अटल DEVICE_ATTR(temp3_crit, 0444, temp2_crit_show, शून्य);

अटल sमाप_प्रकार fan_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
		       FAN_DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr],
		       FAN_DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;

	वापस प्र_लिखो(buf, "%d\n",
		       FAN_DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val,
			    FAN_DIV_FROM_REG(data->fan_भाग[nr]));
	lm87_ग_लिखो_value(client, LM87_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan घड़ी भागider.  This follows the principle
 * of least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागider changed.
 */
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	दीर्घ val;
	पूर्णांक err;
	अचिन्हित दीर्घ min;
	u8 reg;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan_min[nr],
			   FAN_DIV_FROM_REG(data->fan_भाग[nr]));

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
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	reg = lm87_पढ़ो_value(client, LM87_REG_VID_FAN_DIV);
	चयन (nr) अणु
	हाल 0:
	    reg = (reg & 0xCF) | (data->fan_भाग[0] << 4);
	    अवरोध;
	हाल 1:
	    reg = (reg & 0x3F) | (data->fan_भाग[1] << 6);
	    अवरोध;
	पूर्ण
	lm87_ग_लिखो_value(client, LM87_REG_VID_FAN_DIV, reg);

	data->fan_min[nr] = FAN_TO_REG(min, val);
	lm87_ग_लिखो_value(client, LM87_REG_FAN_MIN(nr),
			 data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_input, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_input, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा lm87_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण
अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm87_data *data = dev_get_drvdata(dev);
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
अटल DEVICE_ATTR_RW(vrm);

अटल sमाप_प्रकार aout_output_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", AOUT_FROM_REG(data->aout));
पूर्ण
अटल sमाप_प्रकार aout_output_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = dev_get_drvdata(dev);
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->aout = AOUT_TO_REG(val);
	lm87_ग_लिखो_value(client, LM87_REG_AOUT, data->aout);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(aout_output);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा lm87_data *data = lm87_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 14);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, 15);

/*
 * Real code
 */

अटल काष्ठा attribute *lm87_attributes[] = अणु
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

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&dev_attr_temp1_crit.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&dev_attr_temp2_crit.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,

	&dev_attr_alarms.attr,
	&dev_attr_aout_output.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group = अणु
	.attrs = lm87_attributes,
पूर्ण;

अटल काष्ठा attribute *lm87_attributes_in6[] = अणु
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group_in6 = अणु
	.attrs = lm87_attributes_in6,
पूर्ण;

अटल काष्ठा attribute *lm87_attributes_fan1[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group_fan1 = अणु
	.attrs = lm87_attributes_fan1,
पूर्ण;

अटल काष्ठा attribute *lm87_attributes_in7[] = अणु
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group_in7 = अणु
	.attrs = lm87_attributes_in7,
पूर्ण;

अटल काष्ठा attribute *lm87_attributes_fan2[] = अणु
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group_fan2 = अणु
	.attrs = lm87_attributes_fan2,
पूर्ण;

अटल काष्ठा attribute *lm87_attributes_temp3[] = अणु
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&dev_attr_temp3_crit.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group_temp3 = अणु
	.attrs = lm87_attributes_temp3,
पूर्ण;

अटल काष्ठा attribute *lm87_attributes_in0_5[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group_in0_5 = अणु
	.attrs = lm87_attributes_in0_5,
पूर्ण;

अटल काष्ठा attribute *lm87_attributes_vid[] = अणु
	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm87_group_vid = अणु
	.attrs = lm87_attributes_vid,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm87_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	स्थिर अक्षर *name;
	u8 cid, rev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	अगर (lm87_पढ़ो_value(client, LM87_REG_CONFIG) & 0x80)
		वापस -ENODEV;

	/* Now, we करो the reमुख्यing detection. */
	cid = lm87_पढ़ो_value(client, LM87_REG_COMPANY_ID);
	rev = lm87_पढ़ो_value(client, LM87_REG_REVISION);

	अगर (cid == 0x02			/* National Semiconductor */
	 && (rev >= 0x01 && rev <= 0x08))
		name = "lm87";
	अन्यथा अगर (cid == 0x41		/* Analog Devices */
	      && (rev & 0xf0) == 0x10)
		name = "adm1024";
	अन्यथा अणु
		dev_dbg(&adapter->dev, "LM87 detection failed at 0x%02x\n",
			client->addr);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम lm87_restore_config(व्योम *arg)
अणु
	काष्ठा i2c_client *client = arg;
	काष्ठा lm87_data *data = i2c_get_clientdata(client);

	lm87_ग_लिखो_value(client, LM87_REG_CONFIG, data->config);
पूर्ण

अटल पूर्णांक lm87_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा lm87_data *data = i2c_get_clientdata(client);
	पूर्णांक rc;
	काष्ठा device_node *of_node = client->dev.of_node;
	u8 val = 0;
	काष्ठा regulator *vcc = शून्य;

	अगर (of_node) अणु
		अगर (of_property_पढ़ो_bool(of_node, "has-temp3"))
			val |= CHAN_TEMP3;
		अगर (of_property_पढ़ो_bool(of_node, "has-in6"))
			val |= CHAN_NO_FAN(0);
		अगर (of_property_पढ़ो_bool(of_node, "has-in7"))
			val |= CHAN_NO_FAN(1);
		vcc = devm_regulator_get_optional(&client->dev, "vcc");
		अगर (!IS_ERR(vcc)) अणु
			अगर (regulator_get_voltage(vcc) == 5000000)
				val |= CHAN_VCC_5V;
		पूर्ण
		data->channel = val;
		lm87_ग_लिखो_value(client,
				LM87_REG_CHANNEL_MODE, data->channel);
	पूर्ण अन्यथा अगर (dev_get_platdata(&client->dev)) अणु
		data->channel = *(u8 *)dev_get_platdata(&client->dev);
		lm87_ग_लिखो_value(client,
				 LM87_REG_CHANNEL_MODE, data->channel);
	पूर्ण अन्यथा अणु
		data->channel = lm87_पढ़ो_value(client, LM87_REG_CHANNEL_MODE);
	पूर्ण
	data->config = lm87_पढ़ो_value(client, LM87_REG_CONFIG) & 0x6F;

	rc = devm_add_action(&client->dev, lm87_restore_config, client);
	अगर (rc)
		वापस rc;

	अगर (!(data->config & 0x01)) अणु
		पूर्णांक i;

		/* Limits are left uninitialized after घातer-up */
		क्रम (i = 1; i < 6; i++) अणु
			lm87_ग_लिखो_value(client, LM87_REG_IN_MIN(i), 0x00);
			lm87_ग_लिखो_value(client, LM87_REG_IN_MAX(i), 0xFF);
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			lm87_ग_लिखो_value(client, LM87_REG_TEMP_HIGH[i], 0x7F);
			lm87_ग_लिखो_value(client, LM87_REG_TEMP_LOW[i], 0x00);
			lm87_ग_लिखो_value(client, LM87_REG_AIN_MIN(i), 0x00);
			lm87_ग_लिखो_value(client, LM87_REG_AIN_MAX(i), 0xFF);
		पूर्ण
		अगर (data->channel & CHAN_TEMP3) अणु
			lm87_ग_लिखो_value(client, LM87_REG_TEMP_HIGH[2], 0x7F);
			lm87_ग_लिखो_value(client, LM87_REG_TEMP_LOW[2], 0x00);
		पूर्ण अन्यथा अणु
			lm87_ग_लिखो_value(client, LM87_REG_IN_MIN(0), 0x00);
			lm87_ग_लिखो_value(client, LM87_REG_IN_MAX(0), 0xFF);
		पूर्ण
	पूर्ण

	/* Make sure Start is set and INT#_Clear is clear */
	अगर ((data->config & 0x09) != 0x01)
		lm87_ग_लिखो_value(client, LM87_REG_CONFIG,
				 (data->config & 0x77) | 0x01);
	वापस 0;
पूर्ण

अटल पूर्णांक lm87_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा lm87_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;
	अचिन्हित पूर्णांक group_tail = 0;

	data = devm_kzalloc(&client->dev, माप(काष्ठा lm87_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the LM87 chip */
	err = lm87_init_client(client);
	अगर (err)
		वापस err;

	data->in_scale[0] = 2500;
	data->in_scale[1] = 2700;
	data->in_scale[2] = (data->channel & CHAN_VCC_5V) ? 5000 : 3300;
	data->in_scale[3] = 5000;
	data->in_scale[4] = 12000;
	data->in_scale[5] = 2700;
	data->in_scale[6] = 1875;
	data->in_scale[7] = 1875;

	/*
	 * Conकाष्ठा the list of attributes, the list depends on the
	 * configuration of the chip
	 */
	data->attr_groups[group_tail++] = &lm87_group;
	अगर (data->channel & CHAN_NO_FAN(0))
		data->attr_groups[group_tail++] = &lm87_group_in6;
	अन्यथा
		data->attr_groups[group_tail++] = &lm87_group_fan1;

	अगर (data->channel & CHAN_NO_FAN(1))
		data->attr_groups[group_tail++] = &lm87_group_in7;
	अन्यथा
		data->attr_groups[group_tail++] = &lm87_group_fan2;

	अगर (data->channel & CHAN_TEMP3)
		data->attr_groups[group_tail++] = &lm87_group_temp3;
	अन्यथा
		data->attr_groups[group_tail++] = &lm87_group_in0_5;

	अगर (!(data->channel & CHAN_NO_VID)) अणु
		data->vrm = vid_which_vrm();
		data->attr_groups[group_tail++] = &lm87_group_vid;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(
	    &client->dev, client->name, client, data->attr_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id lm87_id[] = अणु
	अणु "lm87", 0 पूर्ण,
	अणु "adm1024", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm87_id);

अटल स्थिर काष्ठा of_device_id lm87_of_match[] = अणु
	अणु .compatible = "ti,lm87" पूर्ण,
	अणु .compatible = "adi,adm1024" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lm87_of_match);

अटल काष्ठा i2c_driver lm87_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm87",
		.of_match_table = lm87_of_match,
	पूर्ण,
	.probe_new	= lm87_probe,
	.id_table	= lm87_id,
	.detect		= lm87_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm87_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de> and others");
MODULE_DESCRIPTION("LM87 driver");
MODULE_LICENSE("GPL");
