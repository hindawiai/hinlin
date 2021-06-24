<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * adm1025.c
 *
 * Copyright (C) 2000       Chen-Yuan Wu <gwu@esoft.com>
 * Copyright (C) 2003-2009  Jean Delvare <jdelvare@suse.de>
 *
 * The ADM1025 is a sensor chip made by Analog Devices. It reports up to 6
 * voltages (including its own घातer source) and up to two temperatures
 * (its own plus up to one बाह्यal one). Voltages are scaled पूर्णांकernally
 * (which is not the common way) with ratios such that the nominal value
 * of each voltage correspond to a रेजिस्टर value of 192 (which means a
 * resolution of about 0.5% of the nominal value). Temperature values are
 * reported with a 1 deg resolution and a 3 deg accuracy. Complete
 * datasheet can be obtained from Analog's website at:
 *   https://www.onsemi.com/PowerSolutions/product.करो?id=ADM1025
 *
 * This driver also supports the ADM1025A, which dअगरfers from the ADM1025
 * only in that it has "खोलो-drain VID inमाला_दो जबतक the ADM1025 has
 * on-chip 100k pull-ups on the VID inमाला_दो". It करोesn't make any
 * dअगरference क्रम us.
 *
 * This driver also supports the NE1619, a sensor chip made by Philips.
 * That chip is similar to the ADM1025A, with a few dअगरferences. The only
 * dअगरference that matters to us is that the NE1619 has only two possible
 * addresses जबतक the ADM1025A has a third one. Complete datasheet can be
 * obtained from Philips's website at:
 *   http://www.semiconductors.philips.com/pip/NE1619DS.hपंचांगl
 *
 * Since the ADM1025 was the first chipset supported by this driver, most
 * comments will refer to this chipset, but are actually general and
 * concern all supported chipsets, unless mentioned otherwise.
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

/*
 * Addresses to scan
 * ADM1025 and ADM1025A have three possible addresses: 0x2c, 0x2d and 0x2e.
 * NE1619 has two possible addresses: 0x2c and 0x2d.
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु adm1025, ne1619 पूर्ण;

/*
 * The ADM1025 रेजिस्टरs
 */

#घोषणा ADM1025_REG_MAN_ID		0x3E
#घोषणा ADM1025_REG_CHIP_ID		0x3F
#घोषणा ADM1025_REG_CONFIG		0x40
#घोषणा ADM1025_REG_STATUS1		0x41
#घोषणा ADM1025_REG_STATUS2		0x42
#घोषणा ADM1025_REG_IN(nr)		(0x20 + (nr))
#घोषणा ADM1025_REG_IN_MAX(nr)		(0x2B + (nr) * 2)
#घोषणा ADM1025_REG_IN_MIN(nr)		(0x2C + (nr) * 2)
#घोषणा ADM1025_REG_TEMP(nr)		(0x26 + (nr))
#घोषणा ADM1025_REG_TEMP_HIGH(nr)	(0x37 + (nr) * 2)
#घोषणा ADM1025_REG_TEMP_LOW(nr)	(0x38 + (nr) * 2)
#घोषणा ADM1025_REG_VID			0x47
#घोषणा ADM1025_REG_VID4		0x49

/*
 * Conversions and various macros
 * The ADM1025 uses चिन्हित 8-bit values क्रम temperatures.
 */

अटल स्थिर पूर्णांक in_scale[6] = अणु 2500, 2250, 3300, 5000, 12000, 3300 पूर्ण;

#घोषणा IN_FROM_REG(reg, scale)	(((reg) * (scale) + 96) / 192)
#घोषणा IN_TO_REG(val, scale)	((val) <= 0 ? 0 : \
				 (val) >= (scale) * 255 / 192 ? 255 : \
				 ((val) * 192 + (scale) / 2) / (scale))

#घोषणा TEMP_FROM_REG(reg)	((reg) * 1000)
#घोषणा TEMP_TO_REG(val)	((val) <= -127500 ? -128 : \
				 (val) >= 126500 ? 127 : \
				 (((val) < 0 ? (val) - 500 : \
				   (val) + 500) / 1000))

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा adm1025_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	u8 in[6];		/* रेजिस्टर value */
	u8 in_max[6];		/* रेजिस्टर value */
	u8 in_min[6];		/* रेजिस्टर value */
	s8 temp[2];		/* रेजिस्टर value */
	s8 temp_min[2];		/* रेजिस्टर value */
	s8 temp_max[2];		/* रेजिस्टर value */
	u16 alarms;		/* रेजिस्टर values, combined */
	u8 vid;			/* रेजिस्टर values, combined */
	u8 vrm;
पूर्ण;

अटल काष्ठा adm1025_data *adm1025_update_device(काष्ठा device *dev)
अणु
	काष्ठा adm1025_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ * 2) || !data->valid) अणु
		पूर्णांक i;

		dev_dbg(&client->dev, "Updating data.\n");
		क्रम (i = 0; i < 6; i++) अणु
			data->in[i] = i2c_smbus_पढ़ो_byte_data(client,
				      ADM1025_REG_IN(i));
			data->in_min[i] = i2c_smbus_पढ़ो_byte_data(client,
					  ADM1025_REG_IN_MIN(i));
			data->in_max[i] = i2c_smbus_पढ़ो_byte_data(client,
					  ADM1025_REG_IN_MAX(i));
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			data->temp[i] = i2c_smbus_पढ़ो_byte_data(client,
					ADM1025_REG_TEMP(i));
			data->temp_min[i] = i2c_smbus_पढ़ो_byte_data(client,
					    ADM1025_REG_TEMP_LOW(i));
			data->temp_max[i] = i2c_smbus_पढ़ो_byte_data(client,
					    ADM1025_REG_TEMP_HIGH(i));
		पूर्ण
		data->alarms = i2c_smbus_पढ़ो_byte_data(client,
			       ADM1025_REG_STATUS1)
			     | (i2c_smbus_पढ़ो_byte_data(client,
				ADM1025_REG_STATUS2) << 8);
		data->vid = (i2c_smbus_पढ़ो_byte_data(client,
			     ADM1025_REG_VID) & 0x0f)
			  | ((i2c_smbus_पढ़ो_byte_data(client,
			      ADM1025_REG_VID4) & 0x01) << 4);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार
in_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in[index],
		       in_scale[index]));
पूर्ण

अटल sमाप_प्रकार
in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_min[index],
		       in_scale[index]));
पूर्ण

अटल sमाप_प्रकार
in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_max[index],
		       in_scale[index]));
पूर्ण

अटल sमाप_प्रकार
temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[index]));
पूर्ण

अटल sमाप_प्रकार
temp_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_min[index]));
पूर्ण

अटल sमाप_प्रकार
temp_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[index]));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[index] = IN_TO_REG(val, in_scale[index]);
	i2c_smbus_ग_लिखो_byte_data(client, ADM1025_REG_IN_MIN(index),
				  data->in_min[index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[index] = IN_TO_REG(val, in_scale[index]);
	i2c_smbus_ग_लिखो_byte_data(client, ADM1025_REG_IN_MAX(index),
				  data->in_max[index]);
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

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_min[index] = TEMP_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client, ADM1025_REG_TEMP_LOW(index),
				  data->temp_min[index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[index] = TEMP_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client, ADM1025_REG_TEMP_HIGH(index),
				  data->temp_max[index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);

अटल sमाप_प्रकार
alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार
alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp1_fault, alarm, 14);

अटल sमाप_प्रकार
cpu0_vid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1025_data *data = adm1025_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", vid_from_reg(data->vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार
vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1025_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", data->vrm);
पूर्ण
अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1025_data *data = dev_get_drvdata(dev);
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

/*
 * Real code
 */

अटल काष्ठा attribute *adm1025_attributes[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&dev_attr_alarms.attr,
	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1025_group = अणु
	.attrs = adm1025_attributes,
पूर्ण;

अटल काष्ठा attribute *adm1025_attributes_in4[] = अणु
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1025_group_in4 = अणु
	.attrs = adm1025_attributes_in4,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adm1025_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	स्थिर अक्षर *name;
	u8 man_id, chip_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Check क्रम unused bits */
	अगर ((i2c_smbus_पढ़ो_byte_data(client, ADM1025_REG_CONFIG) & 0x80)
	 || (i2c_smbus_पढ़ो_byte_data(client, ADM1025_REG_STATUS1) & 0xC0)
	 || (i2c_smbus_पढ़ो_byte_data(client, ADM1025_REG_STATUS2) & 0xBC)) अणु
		dev_dbg(&adapter->dev, "ADM1025 detection failed at 0x%02x\n",
			client->addr);
		वापस -ENODEV;
	पूर्ण

	/* Identअगरication */
	chip_id = i2c_smbus_पढ़ो_byte_data(client, ADM1025_REG_CHIP_ID);
	अगर ((chip_id & 0xF0) != 0x20)
		वापस -ENODEV;

	man_id = i2c_smbus_पढ़ो_byte_data(client, ADM1025_REG_MAN_ID);
	अगर (man_id == 0x41)
		name = "adm1025";
	अन्यथा अगर (man_id == 0xA1 && client->addr != 0x2E)
		name = "ne1619";
	अन्यथा
		वापस -ENODEV;

	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम adm1025_init_client(काष्ठा i2c_client *client)
अणु
	u8 reg;
	काष्ठा adm1025_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	data->vrm = vid_which_vrm();

	/*
	 * Set high limits
	 * Usually we aव्योम setting limits on driver init, but it happens
	 * that the ADM1025 comes with stupid शेष limits (all रेजिस्टरs
	 * set to 0). In हाल the chip has not gone through any limit
	 * setting yet, we better set the high limits to the max so that
	 * no alarm triggers.
	 */
	क्रम (i = 0; i < 6; i++) अणु
		reg = i2c_smbus_पढ़ो_byte_data(client,
					       ADM1025_REG_IN_MAX(i));
		अगर (reg == 0)
			i2c_smbus_ग_लिखो_byte_data(client,
						  ADM1025_REG_IN_MAX(i),
						  0xFF);
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		reg = i2c_smbus_पढ़ो_byte_data(client,
					       ADM1025_REG_TEMP_HIGH(i));
		अगर (reg == 0)
			i2c_smbus_ग_लिखो_byte_data(client,
						  ADM1025_REG_TEMP_HIGH(i),
						  0x7F);
	पूर्ण

	/*
	 * Start the conversions
	 */
	reg = i2c_smbus_पढ़ो_byte_data(client, ADM1025_REG_CONFIG);
	अगर (!(reg & 0x01))
		i2c_smbus_ग_लिखो_byte_data(client, ADM1025_REG_CONFIG,
					  (reg&0x7E)|0x01);
पूर्ण

अटल पूर्णांक adm1025_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा adm1025_data *data;
	u8 config;

	data = devm_kzalloc(dev, माप(काष्ठा adm1025_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the ADM1025 chip */
	adm1025_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &adm1025_group;
	/* Pin 11 is either in4 (+12V) or VID4 */
	config = i2c_smbus_पढ़ो_byte_data(client, ADM1025_REG_CONFIG);
	अगर (!(config & 0x20))
		data->groups[1] = &adm1025_group_in4;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1025_id[] = अणु
	अणु "adm1025", adm1025 पूर्ण,
	अणु "ne1619", ne1619 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1025_id);

अटल काष्ठा i2c_driver adm1025_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adm1025",
	पूर्ण,
	.probe_new	= adm1025_probe,
	.id_table	= adm1025_id,
	.detect		= adm1025_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adm1025_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("ADM1025 driver");
MODULE_LICENSE("GPL");
