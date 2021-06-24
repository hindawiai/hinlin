<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * smsc47m192.c - Support क्रम hardware monitoring block of
 *		  SMSC LPC47M192 and compatible Super I/O chips
 *
 * Copyright (C) 2006  Harपंचांगut Rick <linux@rick.claranet.de>
 *
 * Derived from lm78.c and other chip drivers.
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
#समावेश <linux/sysfs.h>
#समावेश <linux/mutex.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, I2C_CLIENT_END पूर्ण;

/* SMSC47M192 रेजिस्टरs */
#घोषणा SMSC47M192_REG_IN(nr)		((nr) < 6 ? (0x20 + (nr)) : \
					(0x50 + (nr) - 6))
#घोषणा SMSC47M192_REG_IN_MAX(nr)	((nr) < 6 ? (0x2b + (nr) * 2) : \
					(0x54 + (((nr) - 6) * 2)))
#घोषणा SMSC47M192_REG_IN_MIN(nr)	((nr) < 6 ? (0x2c + (nr) * 2) : \
					(0x55 + (((nr) - 6) * 2)))
अटल u8 SMSC47M192_REG_TEMP[3] =	अणु 0x27, 0x26, 0x52 पूर्ण;
अटल u8 SMSC47M192_REG_TEMP_MAX[3] =	अणु 0x39, 0x37, 0x58 पूर्ण;
अटल u8 SMSC47M192_REG_TEMP_MIN[3] =	अणु 0x3A, 0x38, 0x59 पूर्ण;
#घोषणा SMSC47M192_REG_TEMP_OFFSET(nr)	((nr) == 2 ? 0x1e : 0x1f)
#घोषणा SMSC47M192_REG_ALARM1		0x41
#घोषणा SMSC47M192_REG_ALARM2		0x42
#घोषणा SMSC47M192_REG_VID		0x47
#घोषणा SMSC47M192_REG_VID4		0x49
#घोषणा SMSC47M192_REG_CONFIG		0x40
#घोषणा SMSC47M192_REG_SFR		0x4f
#घोषणा SMSC47M192_REG_COMPANY_ID	0x3e
#घोषणा SMSC47M192_REG_VERSION		0x3f

/* generalised scaling with पूर्णांकeger rounding */
अटल अंतरभूत पूर्णांक SCALE(दीर्घ val, पूर्णांक mul, पूर्णांक भाग)
अणु
	अगर (val < 0)
		वापस (val * mul - भाग / 2) / भाग;
	अन्यथा
		वापस (val * mul + भाग / 2) / भाग;
पूर्ण

/* Conversions */

/* smsc47m192 पूर्णांकernally scales voltage measurements */
अटल स्थिर u16 nom_mv[] = अणु 2500, 2250, 3300, 5000, 12000, 3300, 1500, 1800 पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक IN_FROM_REG(u8 reg, पूर्णांक n)
अणु
	वापस SCALE(reg, nom_mv[n], 192);
पूर्ण

अटल अंतरभूत u8 IN_TO_REG(अचिन्हित दीर्घ val, पूर्णांक n)
अणु
	val = clamp_val(val, 0, nom_mv[n] * 255 / 192);
	वापस SCALE(val, 192, nom_mv[n]);
पूर्ण

/*
 * TEMP: 0.001 degC units (-128C to +127C)
 * REG: 1C/bit, two's complement
 */
अटल अंतरभूत s8 TEMP_TO_REG(दीर्घ val)
अणु
	वापस SCALE(clamp_val(val, -128000, 127000), 1, 1000);
पूर्ण

अटल अंतरभूत पूर्णांक TEMP_FROM_REG(s8 val)
अणु
	वापस val * 1000;
पूर्ण

काष्ठा smsc47m192_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 in[8];		/* Register value */
	u8 in_max[8];		/* Register value */
	u8 in_min[8];		/* Register value */
	s8 temp[3];		/* Register value */
	s8 temp_max[3];		/* Register value */
	s8 temp_min[3];		/* Register value */
	s8 temp_offset[3];	/* Register value */
	u16 alarms;		/* Register encoding, combined */
	u8 vid;			/* Register encoding, combined */
	u8 vrm;
पूर्ण;

अटल काष्ठा smsc47m192_data *smsc47m192_update_device(काष्ठा device *dev)
अणु
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i, config;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	 || !data->valid) अणु
		u8 sfr = i2c_smbus_पढ़ो_byte_data(client, SMSC47M192_REG_SFR);

		dev_dbg(&client->dev, "Starting smsc47m192 update\n");

		क्रम (i = 0; i <= 7; i++) अणु
			data->in[i] = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_IN(i));
			data->in_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_IN_MIN(i));
			data->in_max[i] = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_IN_MAX(i));
		पूर्ण
		क्रम (i = 0; i < 3; i++) अणु
			data->temp[i] = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_TEMP[i]);
			data->temp_max[i] = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_TEMP_MAX[i]);
			data->temp_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_TEMP_MIN[i]);
		पूर्ण
		क्रम (i = 1; i < 3; i++)
			data->temp_offset[i] = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_TEMP_OFFSET(i));
		/*
		 * first offset is temp_offset[0] अगर SFR bit 4 is set,
		 * temp_offset[1] otherwise
		 */
		अगर (sfr & 0x10) अणु
			data->temp_offset[0] = data->temp_offset[1];
			data->temp_offset[1] = 0;
		पूर्ण अन्यथा
			data->temp_offset[0] = 0;

		data->vid = i2c_smbus_पढ़ो_byte_data(client, SMSC47M192_REG_VID)
			    & 0x0f;
		config = i2c_smbus_पढ़ो_byte_data(client,
						  SMSC47M192_REG_CONFIG);
		अगर (config & 0x20)
			data->vid |= (i2c_smbus_पढ़ो_byte_data(client,
					SMSC47M192_REG_VID4) & 0x01) << 4;
		data->alarms = i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_ALARM1) |
			       (i2c_smbus_पढ़ो_byte_data(client,
						SMSC47M192_REG_ALARM2) << 8);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* Voltages */
अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in[nr], nr));
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in_min[nr], nr));
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in_max[nr], nr));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val, nr);
	i2c_smbus_ग_लिखो_byte_data(client, SMSC47M192_REG_IN_MIN(nr),
							data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = IN_TO_REG(val, nr);
	i2c_smbus_ग_लिखो_byte_data(client, SMSC47M192_REG_IN_MAX(nr),
							data->in_max[nr]);
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
अटल SENSOR_DEVICE_ATTR_RO(in7_input, in, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_min, in_min, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_max, in_max, 7);

/* Temperatures */
अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[nr]));
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_min[nr]));
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[nr]));
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_min[nr] = TEMP_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client, SMSC47M192_REG_TEMP_MIN[nr],
						data->temp_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[nr] = TEMP_TO_REG(val);
	i2c_smbus_ग_लिखो_byte_data(client, SMSC47M192_REG_TEMP_MAX[nr],
						data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_offset_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_offset[nr]));
पूर्ण

अटल sमाप_प्रकार temp_offset_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 sfr = i2c_smbus_पढ़ो_byte_data(client, SMSC47M192_REG_SFR);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_offset[nr] = TEMP_TO_REG(val);
	अगर (nr > 1)
		i2c_smbus_ग_लिखो_byte_data(client,
			SMSC47M192_REG_TEMP_OFFSET(nr), data->temp_offset[nr]);
	अन्यथा अगर (data->temp_offset[nr] != 0) अणु
		/*
		 * offset[0] and offset[1] share the same रेजिस्टर,
		 * SFR bit 4 activates offset[0]
		 */
		i2c_smbus_ग_लिखो_byte_data(client, SMSC47M192_REG_SFR,
					(sfr & 0xef) | (nr == 0 ? 0x10 : 0));
		data->temp_offset[1-nr] = 0;
		i2c_smbus_ग_लिखो_byte_data(client,
			SMSC47M192_REG_TEMP_OFFSET(nr), data->temp_offset[nr]);
	पूर्ण अन्यथा अगर ((sfr & 0x10) == (nr == 0 ? 0x10 : 0))
		i2c_smbus_ग_लिखो_byte_data(client,
					SMSC47M192_REG_TEMP_OFFSET(nr), 0);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_offset, temp_offset, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_offset, temp_offset, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_offset, temp_offset, 2);

/* VID */
अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा smsc47m192_data *data = dev_get_drvdata(dev);
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

/* Alarms */
अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा smsc47m192_data *data = smsc47m192_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms & nr) ? 1 : 0);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 0x0010);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 0x0020);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 0x0040);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 0x4000);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, 0x8000);
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0x0001);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 0x0002);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 0x0004);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 0x0008);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 0x0100);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 0x0200);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm, 0x0400);
अटल SENSOR_DEVICE_ATTR_RO(in7_alarm, alarm, 0x0800);

अटल काष्ठा attribute *smsc47m192_attributes[] = अणु
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
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_offset.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,

	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m192_group = अणु
	.attrs = smsc47m192_attributes,
पूर्ण;

अटल काष्ठा attribute *smsc47m192_attributes_in4[] = अणु
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m192_group_in4 = अणु
	.attrs = smsc47m192_attributes_in4,
पूर्ण;

अटल व्योम smsc47m192_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक i;
	u8 config = i2c_smbus_पढ़ो_byte_data(client, SMSC47M192_REG_CONFIG);
	u8 sfr = i2c_smbus_पढ़ो_byte_data(client, SMSC47M192_REG_SFR);

	/* select cycle mode (छोड़ो 1 sec between updates) */
	i2c_smbus_ग_लिखो_byte_data(client, SMSC47M192_REG_SFR,
						(sfr & 0xfd) | 0x02);
	अगर (!(config & 0x01)) अणु
		/* initialize alarm limits */
		क्रम (i = 0; i < 8; i++) अणु
			i2c_smbus_ग_लिखो_byte_data(client,
				SMSC47M192_REG_IN_MIN(i), 0);
			i2c_smbus_ग_लिखो_byte_data(client,
				SMSC47M192_REG_IN_MAX(i), 0xff);
		पूर्ण
		क्रम (i = 0; i < 3; i++) अणु
			i2c_smbus_ग_लिखो_byte_data(client,
				SMSC47M192_REG_TEMP_MIN[i], 0x80);
			i2c_smbus_ग_लिखो_byte_data(client,
				SMSC47M192_REG_TEMP_MAX[i], 0x7f);
		पूर्ण

		/* start monitoring */
		i2c_smbus_ग_लिखो_byte_data(client, SMSC47M192_REG_CONFIG,
						(config & 0xf7) | 0x01);
	पूर्ण
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक smsc47m192_detect(काष्ठा i2c_client *client,
			     काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक version;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Detection criteria from sensors_detect script */
	version = i2c_smbus_पढ़ो_byte_data(client, SMSC47M192_REG_VERSION);
	अगर (i2c_smbus_पढ़ो_byte_data(client,
				SMSC47M192_REG_COMPANY_ID) == 0x55
	 && (version & 0xf0) == 0x20
	 && (i2c_smbus_पढ़ो_byte_data(client,
				SMSC47M192_REG_VID) & 0x70) == 0x00
	 && (i2c_smbus_पढ़ो_byte_data(client,
				SMSC47M192_REG_VID4) & 0xfe) == 0x80) अणु
		dev_info(&adapter->dev,
			 "found SMSC47M192 or compatible, "
			 "version 2, stepping A%d\n", version & 0x0f);
	पूर्ण अन्यथा अणु
		dev_dbg(&adapter->dev,
			"SMSC47M192 detection failed at 0x%02x\n",
			client->addr);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "smsc47m192", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक smsc47m192_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा smsc47m192_data *data;
	पूर्णांक config;

	data = devm_kzalloc(dev, माप(काष्ठा smsc47m192_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->vrm = vid_which_vrm();
	mutex_init(&data->update_lock);

	/* Initialize the SMSC47M192 chip */
	smsc47m192_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &smsc47m192_group;
	/* Pin 110 is either in4 (+12V) or VID4 */
	config = i2c_smbus_पढ़ो_byte_data(client, SMSC47M192_REG_CONFIG);
	अगर (!(config & 0x20))
		data->groups[1] = &smsc47m192_group_in4;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id smsc47m192_id[] = अणु
	अणु "smsc47m192", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, smsc47m192_id);

अटल काष्ठा i2c_driver smsc47m192_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "smsc47m192",
	पूर्ण,
	.probe_new	= smsc47m192_probe,
	.id_table	= smsc47m192_id,
	.detect		= smsc47m192_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(smsc47m192_driver);

MODULE_AUTHOR("Hartmut Rick <linux@rick.claranet.de>");
MODULE_DESCRIPTION("SMSC47M192 driver");
MODULE_LICENSE("GPL");
