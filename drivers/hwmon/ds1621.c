<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ds1621.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	      monitoring
 * Christian W. Zuckschwerdt  <zany@triq.net>  2000-11-23
 * based on lm75.c by Froकरो Looijaard <froकरोl@dds.nl>
 * Ported to Linux 2.6 by Aurelien Jarno <aurelien@aurel32.net> with
 * the help of Jean Delvare <jdelvare@suse.de>
 *
 * The DS1621 device is a digital temperature/thermometer with 9-bit
 * resolution, a thermal alarm output (Tout), and user-defined minimum
 * and maximum temperature thresholds (TH and TL).
 *
 * The DS1625, DS1631, DS1721, and DS1731 are pin compatible with the DS1621
 * and similar in operation, with slight variations as noted in the device
 * datasheets (please refer to www.maximपूर्णांकegrated.com क्रम specअगरic
 * device inक्रमmation).
 *
 * Since the DS1621 was the first chipset supported by this driver,
 * most comments will refer to this chipset, but are actually general
 * and concern all supported chipsets, unless mentioned otherwise.
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
#समावेश <linux/kernel.h>

/* Supported devices */
क्रमागत chips अणु ds1621, ds1625, ds1631, ds1721, ds1731 पूर्ण;

/* Insmod parameters */
अटल पूर्णांक polarity = -1;
module_param(polarity, पूर्णांक, 0);
MODULE_PARM_DESC(polarity, "Output's polarity: 0 = active high, 1 = active low");

/*
 * The Configuration/Status रेजिस्टर
 *
 * - DS1621:
 *   7    6    5    4    3    2    1    0
 * |Done|THF |TLF |NVB | X  | X  |POL |1SHOT|
 *
 * - DS1625:
 *   7    6    5    4    3    2    1    0
 * |Done|THF |TLF |NVB | 1  | 0  |POL |1SHOT|
 *
 * - DS1631, DS1731:
 *   7    6    5    4    3    2    1    0
 * |Done|THF |TLF |NVB | R1 | R0 |POL |1SHOT|
 *
 * - DS1721:
 *   7    6    5    4    3    2    1    0
 * |Done| X  | X  | U  | R1 | R0 |POL |1SHOT|
 *
 * Where:
 * - 'X' is Reserved
 * - 'U' is Undefined
 */
#घोषणा DS1621_REG_CONFIG_NVB		0x10
#घोषणा DS1621_REG_CONFIG_RESOL		0x0C
#घोषणा DS1621_REG_CONFIG_POLARITY	0x02
#घोषणा DS1621_REG_CONFIG_1SHOT		0x01
#घोषणा DS1621_REG_CONFIG_DONE		0x80

#घोषणा DS1621_REG_CONFIG_RESOL_SHIFT	2

/* ds1721 conversion rates: अणुC/LSB, समय(ms), resolution bit settingपूर्ण */
अटल स्थिर अचिन्हित लघु ds1721_convrates[] = अणु
	94,	/*  9-bits (0.5,  93.75, RES[0..1] = 0 */
	188,	/* 10-bits (0.25, 187.5, RES[0..1] = 1 */
	375,	/* 11-bits (0.125,  375, RES[0..1] = 2 */
	750,	/* 12-bits (0.0625, 750, RES[0..1] = 3 */
पूर्ण;

#घोषणा DS1621_CONVERSION_MAX	750
#घोषणा DS1625_CONVERSION_MAX	500

#घोषणा DS1621_TEMP_MAX	125000
#घोषणा DS1621_TEMP_MIN	(-55000)

/* The DS1621 temperature रेजिस्टरs */
अटल स्थिर u8 DS1621_REG_TEMP[3] = अणु
	0xAA,		/* input, word, RO */
	0xA2,		/* min, word, RW */
	0xA1,		/* max, word, RW */
पूर्ण;
#घोषणा DS1621_REG_CONF			0xAC /* byte, RW */
#घोषणा DS1621_COM_START		0xEE /* no data */
#घोषणा DS1721_COM_START		0x51 /* no data */
#घोषणा DS1621_COM_STOP			0x22 /* no data */

/* The DS1621 configuration रेजिस्टर */
#घोषणा DS1621_ALARM_TEMP_HIGH		0x40
#घोषणा DS1621_ALARM_TEMP_LOW		0x20

/* Conversions */
#घोषणा ALARMS_FROM_REG(val) ((val) & \
			(DS1621_ALARM_TEMP_HIGH | DS1621_ALARM_TEMP_LOW))

/* Each client has this additional data */
काष्ठा ds1621_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अक्षर valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	क्रमागत chips kind;		/* device type */

	u16 temp[3];			/* Register values, word */
	u8 conf;			/* Register encoding, combined */
	u8 zbits;			/* Resolution encoded as number of
					 * zero bits */
	u16 update_पूर्णांकerval;		/* Conversion rate in milliseconds */
पूर्ण;

अटल अंतरभूत पूर्णांक DS1621_TEMP_FROM_REG(u16 reg)
अणु
	वापस DIV_ROUND_CLOSEST(((s16)reg / 16) * 625, 10);
पूर्ण

/*
 * TEMP: 0.001C/bit (-55C to +125C)
 * REG:
 *  - 1621, 1625: 0.5C/bit, 7 zero-bits
 *  - 1631, 1721, 1731: 0.0625C/bit, 4 zero-bits
 */
अटल अंतरभूत u16 DS1621_TEMP_TO_REG(दीर्घ temp, u8 zbits)
अणु
	temp = clamp_val(temp, DS1621_TEMP_MIN, DS1621_TEMP_MAX);
	temp = DIV_ROUND_CLOSEST(temp * (1 << (8 - zbits)), 1000) << zbits;
	वापस temp;
पूर्ण

अटल व्योम ds1621_init_client(काष्ठा ds1621_data *data,
			       काष्ठा i2c_client *client)
अणु
	u8 conf, new_conf, sreg, resol;

	new_conf = conf = i2c_smbus_पढ़ो_byte_data(client, DS1621_REG_CONF);
	/* चयन to continuous conversion mode */
	new_conf &= ~DS1621_REG_CONFIG_1SHOT;

	/* setup output polarity */
	अगर (polarity == 0)
		new_conf &= ~DS1621_REG_CONFIG_POLARITY;
	अन्यथा अगर (polarity == 1)
		new_conf |= DS1621_REG_CONFIG_POLARITY;

	अगर (conf != new_conf)
		i2c_smbus_ग_लिखो_byte_data(client, DS1621_REG_CONF, new_conf);

	चयन (data->kind) अणु
	हाल ds1625:
		data->update_पूर्णांकerval = DS1625_CONVERSION_MAX;
		data->zbits = 7;
		sreg = DS1621_COM_START;
		अवरोध;
	हाल ds1631:
	हाल ds1721:
	हाल ds1731:
		resol = (new_conf & DS1621_REG_CONFIG_RESOL) >>
			 DS1621_REG_CONFIG_RESOL_SHIFT;
		data->update_पूर्णांकerval = ds1721_convrates[resol];
		data->zbits = 7 - resol;
		sreg = DS1721_COM_START;
		अवरोध;
	शेष:
		data->update_पूर्णांकerval = DS1621_CONVERSION_MAX;
		data->zbits = 7;
		sreg = DS1621_COM_START;
		अवरोध;
	पूर्ण

	/* start conversion */
	i2c_smbus_ग_लिखो_byte(client, sreg);
पूर्ण

अटल काष्ठा ds1621_data *ds1621_update_client(काष्ठा device *dev)
अणु
	काष्ठा ds1621_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 new_conf;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + data->update_पूर्णांकerval) ||
	    !data->valid) अणु
		पूर्णांक i;

		dev_dbg(&client->dev, "Starting ds1621 update\n");

		data->conf = i2c_smbus_पढ़ो_byte_data(client, DS1621_REG_CONF);

		क्रम (i = 0; i < ARRAY_SIZE(data->temp); i++)
			data->temp[i] = i2c_smbus_पढ़ो_word_swapped(client,
							 DS1621_REG_TEMP[i]);

		/* reset alarms अगर necessary */
		new_conf = data->conf;
		अगर (data->temp[0] > data->temp[1])	/* input > min */
			new_conf &= ~DS1621_ALARM_TEMP_LOW;
		अगर (data->temp[0] < data->temp[2])	/* input < max */
			new_conf &= ~DS1621_ALARM_TEMP_HIGH;
		अगर (data->conf != new_conf)
			i2c_smbus_ग_लिखो_byte_data(client, DS1621_REG_CONF,
						  new_conf);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ds1621_data *data = ds1621_update_client(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       DS1621_TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ds1621_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[attr->index] = DS1621_TEMP_TO_REG(val, data->zbits);
	i2c_smbus_ग_लिखो_word_swapped(data->client, DS1621_REG_TEMP[attr->index],
				     data->temp[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf)
अणु
	काष्ठा ds1621_data *data = ds1621_update_client(dev);
	वापस प्र_लिखो(buf, "%d\n", ALARMS_FROM_REG(data->conf));
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ds1621_data *data = ds1621_update_client(dev);
	वापस प्र_लिखो(buf, "%d\n", !!(data->conf & attr->index));
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा ds1621_data *data = dev_get_drvdata(dev);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%hu\n", data->update_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *da,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ds1621_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ convrate;
	s32 err;
	पूर्णांक resol = 0;

	err = kम_से_अदीर्घ(buf, 10, &convrate);
	अगर (err)
		वापस err;

	/* Convert rate पूर्णांकo resolution bits */
	जबतक (resol < (ARRAY_SIZE(ds1721_convrates) - 1) &&
	       convrate > ds1721_convrates[resol])
		resol++;

	mutex_lock(&data->update_lock);
	data->conf = i2c_smbus_पढ़ो_byte_data(client, DS1621_REG_CONF);
	data->conf &= ~DS1621_REG_CONFIG_RESOL;
	data->conf |= (resol << DS1621_REG_CONFIG_RESOL_SHIFT);
	i2c_smbus_ग_लिखो_byte_data(client, DS1621_REG_CONF, data->conf);
	data->update_पूर्णांकerval = ds1721_convrates[resol];
	data->zbits = 7 - resol;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(alarms);
अटल DEVICE_ATTR_RW(update_पूर्णांकerval);

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, alarm, DS1621_ALARM_TEMP_LOW);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, alarm, DS1621_ALARM_TEMP_HIGH);

अटल काष्ठा attribute *ds1621_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&dev_attr_alarms.attr,
	&dev_attr_update_पूर्णांकerval.attr,
	शून्य
पूर्ण;

अटल umode_t ds1621_attribute_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा ds1621_data *data = dev_get_drvdata(dev);

	अगर (attr == &dev_attr_update_पूर्णांकerval.attr)
		अगर (data->kind == ds1621 || data->kind == ds1625)
			/* shhh, we're hiding update_पूर्णांकerval */
			वापस 0;
	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group ds1621_group = अणु
	.attrs = ds1621_attributes,
	.is_visible = ds1621_attribute_visible
पूर्ण;
__ATTRIBUTE_GROUPS(ds1621);

अटल स्थिर काष्ठा i2c_device_id ds1621_id[];

अटल पूर्णांक ds1621_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ds1621_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(&client->dev, माप(काष्ठा ds1621_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->update_lock);

	data->kind = i2c_match_id(ds1621_id, client)->driver_data;
	data->client = client;

	/* Initialize the DS1621 chip */
	ds1621_init_client(data, client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   client->name, data,
							   ds1621_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ds1621_id[] = अणु
	अणु "ds1621", ds1621 पूर्ण,
	अणु "ds1625", ds1625 पूर्ण,
	अणु "ds1631", ds1631 पूर्ण,
	अणु "ds1721", ds1721 पूर्ण,
	अणु "ds1731", ds1731 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds1621_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ds1621_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "ds1621",
	पूर्ण,
	.probe_new	= ds1621_probe,
	.id_table	= ds1621_id,
पूर्ण;

module_i2c_driver(ds1621_driver);

MODULE_AUTHOR("Christian W. Zuckschwerdt <zany@triq.net>");
MODULE_DESCRIPTION("DS1621 driver");
MODULE_LICENSE("GPL");
