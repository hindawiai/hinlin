<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* पंचांगp401.c
 *
 * Copyright (C) 2007,2008 Hans de Goede <hdegoede@redhat.com>
 * Preliminary पंचांगp411 support by:
 * Gabriel Konat, Sander Leget, Wouter Willems
 * Copyright (C) 2009 Andre Prendel <andre.prendel@gmx.de>
 *
 * Cleanup and support क्रम TMP431 and TMP432 by Guenter Roeck
 * Copyright (c) 2013 Guenter Roeck <linux@roeck-us.net>
 */

/*
 * Driver क्रम the Texas Instruments TMP401 SMBUS temperature sensor IC.
 *
 * Note this IC is in some aspect similar to the LM90, but it has quite a
 * few dअगरferences too, क्रम example the local temp has a higher resolution
 * and thus has 16 bits रेजिस्टरs क्रम its value and limit instead of 8 bits.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x48, 0x49, 0x4a, 0x4c, 0x4d,
	0x4e, 0x4f, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु पंचांगp401, पंचांगp411, पंचांगp431, पंचांगp432, पंचांगp435, पंचांगp461 पूर्ण;

/*
 * The TMP401 रेजिस्टरs, note some रेजिस्टरs have dअगरferent addresses क्रम
 * पढ़ोing and writing
 */
#घोषणा TMP401_STATUS				0x02
#घोषणा TMP401_CONFIG_READ			0x03
#घोषणा TMP401_CONFIG_WRITE			0x09
#घोषणा TMP401_CONVERSION_RATE_READ		0x04
#घोषणा TMP401_CONVERSION_RATE_WRITE		0x0A
#घोषणा TMP401_TEMP_CRIT_HYST			0x21
#घोषणा TMP401_MANUFACTURER_ID_REG		0xFE
#घोषणा TMP401_DEVICE_ID_REG			0xFF

अटल स्थिर u8 TMP401_TEMP_MSB_READ[7][2] = अणु
	अणु 0x00, 0x01 पूर्ण,	/* temp */
	अणु 0x06, 0x08 पूर्ण,	/* low limit */
	अणु 0x05, 0x07 पूर्ण,	/* high limit */
	अणु 0x20, 0x19 पूर्ण,	/* therm (crit) limit */
	अणु 0x30, 0x34 पूर्ण,	/* lowest */
	अणु 0x32, 0x36 पूर्ण,	/* highest */
	अणु 0, 0x11 पूर्ण,	/* offset */
पूर्ण;

अटल स्थिर u8 TMP401_TEMP_MSB_WRITE[7][2] = अणु
	अणु 0, 0 पूर्ण,	/* temp (unused) */
	अणु 0x0C, 0x0E पूर्ण,	/* low limit */
	अणु 0x0B, 0x0D पूर्ण,	/* high limit */
	अणु 0x20, 0x19 पूर्ण,	/* therm (crit) limit */
	अणु 0x30, 0x34 पूर्ण,	/* lowest */
	अणु 0x32, 0x36 पूर्ण,	/* highest */
	अणु 0, 0x11 पूर्ण,	/* offset */
पूर्ण;

अटल स्थिर u8 TMP432_TEMP_MSB_READ[4][3] = अणु
	अणु 0x00, 0x01, 0x23 पूर्ण,	/* temp */
	अणु 0x06, 0x08, 0x16 पूर्ण,	/* low limit */
	अणु 0x05, 0x07, 0x15 पूर्ण,	/* high limit */
	अणु 0x20, 0x19, 0x1A पूर्ण,	/* therm (crit) limit */
पूर्ण;

अटल स्थिर u8 TMP432_TEMP_MSB_WRITE[4][3] = अणु
	अणु 0, 0, 0 पूर्ण,		/* temp  - unused */
	अणु 0x0C, 0x0E, 0x16 पूर्ण,	/* low limit */
	अणु 0x0B, 0x0D, 0x15 पूर्ण,	/* high limit */
	अणु 0x20, 0x19, 0x1A पूर्ण,	/* therm (crit) limit */
पूर्ण;

/* [0] = fault, [1] = low, [2] = high, [3] = therm/crit */
अटल स्थिर u8 TMP432_STATUS_REG[] = अणु
	0x1b, 0x36, 0x35, 0x37 पूर्ण;

/* Flags */
#घोषणा TMP401_CONFIG_RANGE			BIT(2)
#घोषणा TMP401_CONFIG_SHUTDOWN			BIT(6)
#घोषणा TMP401_STATUS_LOCAL_CRIT		BIT(0)
#घोषणा TMP401_STATUS_REMOTE_CRIT		BIT(1)
#घोषणा TMP401_STATUS_REMOTE_OPEN		BIT(2)
#घोषणा TMP401_STATUS_REMOTE_LOW		BIT(3)
#घोषणा TMP401_STATUS_REMOTE_HIGH		BIT(4)
#घोषणा TMP401_STATUS_LOCAL_LOW			BIT(5)
#घोषणा TMP401_STATUS_LOCAL_HIGH		BIT(6)

/* On TMP432, each status has its own रेजिस्टर */
#घोषणा TMP432_STATUS_LOCAL			BIT(0)
#घोषणा TMP432_STATUS_REMOTE1			BIT(1)
#घोषणा TMP432_STATUS_REMOTE2			BIT(2)

/* Manufacturer / Device ID's */
#घोषणा TMP401_MANUFACTURER_ID			0x55
#घोषणा TMP401_DEVICE_ID			0x11
#घोषणा TMP411A_DEVICE_ID			0x12
#घोषणा TMP411B_DEVICE_ID			0x13
#घोषणा TMP411C_DEVICE_ID			0x10
#घोषणा TMP431_DEVICE_ID			0x31
#घोषणा TMP432_DEVICE_ID			0x32
#घोषणा TMP435_DEVICE_ID			0x35

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id पंचांगp401_id[] = अणु
	अणु "tmp401", पंचांगp401 पूर्ण,
	अणु "tmp411", पंचांगp411 पूर्ण,
	अणु "tmp431", पंचांगp431 पूर्ण,
	अणु "tmp432", पंचांगp432 पूर्ण,
	अणु "tmp435", पंचांगp435 पूर्ण,
	अणु "tmp461", पंचांगp461 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp401_id);

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा पंचांगp401_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];
	काष्ठा mutex update_lock;
	अक्षर valid; /* zero until following fields are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	क्रमागत chips kind;

	अचिन्हित पूर्णांक update_पूर्णांकerval;	/* in milliseconds */

	/* रेजिस्टर values */
	u8 status[4];
	u8 config;
	u16 temp[7][3];
	u8 temp_crit_hyst;
पूर्ण;

/*
 * Sysfs attr show / store functions
 */

अटल पूर्णांक पंचांगp401_रेजिस्टर_to_temp(u16 reg, u8 config)
अणु
	पूर्णांक temp = reg;

	अगर (config & TMP401_CONFIG_RANGE)
		temp -= 64 * 256;

	वापस DIV_ROUND_CLOSEST(temp * 125, 32);
पूर्ण

अटल u16 पंचांगp401_temp_to_रेजिस्टर(दीर्घ temp, u8 config, पूर्णांक zbits)
अणु
	अगर (config & TMP401_CONFIG_RANGE) अणु
		temp = clamp_val(temp, -64000, 191000);
		temp += 64000;
	पूर्ण अन्यथा
		temp = clamp_val(temp, 0, 127000);

	वापस DIV_ROUND_CLOSEST(temp * (1 << (8 - zbits)), 1000) << zbits;
पूर्ण

अटल पूर्णांक पंचांगp401_update_device_reg16(काष्ठा i2c_client *client,
				      काष्ठा पंचांगp401_data *data)
अणु
	पूर्णांक i, j, val;
	पूर्णांक num_regs = data->kind == पंचांगp411 ? 6 : 4;
	पूर्णांक num_sensors = data->kind == पंचांगp432 ? 3 : 2;

	क्रम (i = 0; i < num_sensors; i++) अणु		/* local / r1 / r2 */
		क्रम (j = 0; j < num_regs; j++) अणु	/* temp / low / ... */
			u8 regaddr;

			regaddr = data->kind == पंचांगp432 ?
						TMP432_TEMP_MSB_READ[j][i] :
						TMP401_TEMP_MSB_READ[j][i];
			अगर (j == 3) अणु /* crit is msb only */
				val = i2c_smbus_पढ़ो_byte_data(client, regaddr);
			पूर्ण अन्यथा अणु
				val = i2c_smbus_पढ़ो_word_swapped(client,
								  regaddr);
			पूर्ण
			अगर (val < 0)
				वापस val;

			data->temp[j][i] = j == 3 ? val << 8 : val;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा पंचांगp401_data *पंचांगp401_update_device(काष्ठा device *dev)
अणु
	काष्ठा पंचांगp401_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा पंचांगp401_data *ret = data;
	पूर्णांक i, val;
	अचिन्हित दीर्घ next_update;

	mutex_lock(&data->update_lock);

	next_update = data->last_updated +
		      msecs_to_jअगरfies(data->update_पूर्णांकerval);
	अगर (समय_after(jअगरfies, next_update) || !data->valid) अणु
		अगर (data->kind != पंचांगp432) अणु
			/*
			 * The driver uses the TMP432 status क्रमmat पूर्णांकernally.
			 * Convert status to TMP432 क्रमmat क्रम other chips.
			 */
			val = i2c_smbus_पढ़ो_byte_data(client, TMP401_STATUS);
			अगर (val < 0) अणु
				ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			data->status[0] =
			  (val & TMP401_STATUS_REMOTE_OPEN) >> 1;
			data->status[1] =
			  ((val & TMP401_STATUS_REMOTE_LOW) >> 2) |
			  ((val & TMP401_STATUS_LOCAL_LOW) >> 5);
			data->status[2] =
			  ((val & TMP401_STATUS_REMOTE_HIGH) >> 3) |
			  ((val & TMP401_STATUS_LOCAL_HIGH) >> 6);
			data->status[3] = val & (TMP401_STATUS_LOCAL_CRIT
						| TMP401_STATUS_REMOTE_CRIT);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < ARRAY_SIZE(data->status); i++) अणु
				val = i2c_smbus_पढ़ो_byte_data(client,
							TMP432_STATUS_REG[i]);
				अगर (val < 0) अणु
					ret = ERR_PTR(val);
					जाओ पात;
				पूर्ण
				data->status[i] = val;
			पूर्ण
		पूर्ण

		val = i2c_smbus_पढ़ो_byte_data(client, TMP401_CONFIG_READ);
		अगर (val < 0) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->config = val;
		val = पंचांगp401_update_device_reg16(client, data);
		अगर (val < 0) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		val = i2c_smbus_पढ़ो_byte_data(client, TMP401_TEMP_CRIT_HYST);
		अगर (val < 0) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp_crit_hyst = val;

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक index = to_sensor_dev_attr_2(devattr)->index;
	काष्ठा पंचांगp401_data *data = पंचांगp401_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n",
		पंचांगp401_रेजिस्टर_to_temp(data->temp[nr][index], data->config));
पूर्ण

अटल sमाप_प्रकार temp_crit_hyst_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	पूर्णांक temp, index = to_sensor_dev_attr(devattr)->index;
	काष्ठा पंचांगp401_data *data = पंचांगp401_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	temp = पंचांगp401_रेजिस्टर_to_temp(data->temp[3][index], data->config);
	temp -= data->temp_crit_hyst * 1000;
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार status_show(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक mask = to_sensor_dev_attr_2(devattr)->index;
	काष्ठा पंचांगp401_data *data = पंचांगp401_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", !!(data->status[nr] & mask));
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr_2(devattr)->nr;
	पूर्णांक index = to_sensor_dev_attr_2(devattr)->index;
	काष्ठा पंचांगp401_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	u16 reg;
	u8 regaddr;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	reg = पंचांगp401_temp_to_रेजिस्टर(val, data->config, nr == 3 ? 8 : 4);

	mutex_lock(&data->update_lock);

	regaddr = data->kind == पंचांगp432 ? TMP432_TEMP_MSB_WRITE[nr][index]
				       : TMP401_TEMP_MSB_WRITE[nr][index];
	अगर (nr == 3) अणु /* crit is msb only */
		i2c_smbus_ग_लिखो_byte_data(client, regaddr, reg >> 8);
	पूर्ण अन्यथा अणु
		/* Hardware expects big endian data --> use _swapped */
		i2c_smbus_ग_लिखो_word_swapped(client, regaddr, reg);
	पूर्ण
	data->temp[nr][index] = reg;

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_crit_hyst_store(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक temp, index = to_sensor_dev_attr(devattr)->index;
	काष्ठा पंचांगp401_data *data = पंचांगp401_update_device(dev);
	दीर्घ val;
	u8 reg;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (data->config & TMP401_CONFIG_RANGE)
		val = clamp_val(val, -64000, 191000);
	अन्यथा
		val = clamp_val(val, 0, 127000);

	mutex_lock(&data->update_lock);
	temp = पंचांगp401_रेजिस्टर_to_temp(data->temp[3][index], data->config);
	val = clamp_val(val, temp - 255000, temp);
	reg = ((temp - val) + 500) / 1000;

	i2c_smbus_ग_लिखो_byte_data(data->client, TMP401_TEMP_CRIT_HYST,
				  reg);

	data->temp_crit_hyst = reg;

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/*
 * Resets the historical measurements of minimum and maximum temperatures.
 * This is करोne by writing any value to any of the minimum/maximum रेजिस्टरs
 * (0x30-0x37).
 */
अटल sमाप_प्रकार reset_temp_history_store(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पंचांगp401_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	अगर (val != 1) अणु
		dev_err(dev,
			"temp_reset_history value %ld not supported. Use 1 to reset the history!\n",
			val);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&data->update_lock);
	i2c_smbus_ग_लिखो_byte_data(client, TMP401_TEMP_MSB_WRITE[5][0], val);
	data->valid = 0;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पंचांगp401_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", data->update_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पंचांगp401_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err, rate;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	/*
	 * For valid rates, पूर्णांकerval can be calculated as
	 *	पूर्णांकerval = (1 << (7 - rate)) * 125;
	 * Rounded rate is thereक्रमe
	 *	rate = 7 - __fls(पूर्णांकerval * 4 / (125 * 3));
	 * Use clamp_val() to aव्योम overflows, and to ensure valid input
	 * क्रम __fls.
	 */
	val = clamp_val(val, 125, 16000);
	rate = 7 - __fls(val * 4 / (125 * 3));
	mutex_lock(&data->update_lock);
	i2c_smbus_ग_लिखो_byte_data(client, TMP401_CONVERSION_RATE_WRITE, rate);
	data->update_पूर्णांकerval = (1 << (7 - rate)) * 125;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_2_RO(temp1_input, temp, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_min, temp, 1, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_max, temp, 2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_crit, temp, 3, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit_hyst, temp_crit_hyst, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_min_alarm, status, 1,
			       TMP432_STATUS_LOCAL);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_max_alarm, status, 2,
			       TMP432_STATUS_LOCAL);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_crit_alarm, status, 3,
			       TMP432_STATUS_LOCAL);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_input, temp, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_min, temp, 1, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_max, temp, 2, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_crit, temp, 3, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_hyst, temp_crit_hyst, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_fault, status, 0, TMP432_STATUS_REMOTE1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_min_alarm, status, 1,
			       TMP432_STATUS_REMOTE1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_max_alarm, status, 2,
			       TMP432_STATUS_REMOTE1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_crit_alarm, status, 3,
			       TMP432_STATUS_REMOTE1);

अटल DEVICE_ATTR_RW(update_पूर्णांकerval);

अटल काष्ठा attribute *पंचांगp401_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,

	&dev_attr_update_पूर्णांकerval.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पंचांगp401_group = अणु
	.attrs = पंचांगp401_attributes,
पूर्ण;

/*
 * Additional features of the TMP411 chip.
 * The TMP411 stores the minimum and maximum
 * temperature measured since घातer-on, chip-reset, or
 * minimum and maximum रेजिस्टर reset क्रम both the local
 * and remote channels.
 */
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_lowest, temp, 4, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_highest, temp, 5, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_lowest, temp, 4, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_highest, temp, 5, 1);
अटल SENSOR_DEVICE_ATTR_WO(temp_reset_history, reset_temp_history, 0);

अटल काष्ठा attribute *पंचांगp411_attributes[] = अणु
	&sensor_dev_attr_temp1_highest.dev_attr.attr,
	&sensor_dev_attr_temp1_lowest.dev_attr.attr,
	&sensor_dev_attr_temp2_highest.dev_attr.attr,
	&sensor_dev_attr_temp2_lowest.dev_attr.attr,
	&sensor_dev_attr_temp_reset_history.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पंचांगp411_group = अणु
	.attrs = पंचांगp411_attributes,
पूर्ण;

अटल SENSOR_DEVICE_ATTR_2_RO(temp3_input, temp, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_min, temp, 1, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_max, temp, 2, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_crit, temp, 3, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_hyst, temp_crit_hyst, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_fault, status, 0, TMP432_STATUS_REMOTE2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_min_alarm, status, 1,
			       TMP432_STATUS_REMOTE2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_max_alarm, status, 2,
			       TMP432_STATUS_REMOTE2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_crit_alarm, status, 3,
			       TMP432_STATUS_REMOTE2);

अटल काष्ठा attribute *पंचांगp432_attributes[] = अणु
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पंचांगp432_group = अणु
	.attrs = पंचांगp432_attributes,
पूर्ण;

/*
 * Additional features of the TMP461 chip.
 * The TMP461 temperature offset क्रम the remote channel.
 */
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_offset, temp, 6, 1);

अटल काष्ठा attribute *पंचांगp461_attributes[] = अणु
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पंचांगp461_group = अणु
	.attrs = पंचांगp461_attributes,
पूर्ण;

/*
 * Begin non sysfs callback code (aka Real code)
 */

अटल पूर्णांक पंचांगp401_init_client(काष्ठा पंचांगp401_data *data,
			      काष्ठा i2c_client *client)
अणु
	पूर्णांक config, config_orig, status = 0;

	/* Set the conversion rate to 2 Hz */
	i2c_smbus_ग_लिखो_byte_data(client, TMP401_CONVERSION_RATE_WRITE, 5);
	data->update_पूर्णांकerval = 500;

	/* Start conversions (disable shutकरोwn अगर necessary) */
	config = i2c_smbus_पढ़ो_byte_data(client, TMP401_CONFIG_READ);
	अगर (config < 0)
		वापस config;

	config_orig = config;
	config &= ~TMP401_CONFIG_SHUTDOWN;

	अगर (config != config_orig)
		status = i2c_smbus_ग_लिखो_byte_data(client,
						   TMP401_CONFIG_WRITE,
						   config);

	वापस status;
पूर्ण

अटल पूर्णांक पंचांगp401_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	क्रमागत chips kind;
	काष्ठा i2c_adapter *adapter = client->adapter;
	u8 reg;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* Detect and identअगरy the chip */
	reg = i2c_smbus_पढ़ो_byte_data(client, TMP401_MANUFACTURER_ID_REG);
	अगर (reg != TMP401_MANUFACTURER_ID)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, TMP401_DEVICE_ID_REG);

	चयन (reg) अणु
	हाल TMP401_DEVICE_ID:
		अगर (client->addr != 0x4c)
			वापस -ENODEV;
		kind = पंचांगp401;
		अवरोध;
	हाल TMP411A_DEVICE_ID:
		अगर (client->addr != 0x4c)
			वापस -ENODEV;
		kind = पंचांगp411;
		अवरोध;
	हाल TMP411B_DEVICE_ID:
		अगर (client->addr != 0x4d)
			वापस -ENODEV;
		kind = पंचांगp411;
		अवरोध;
	हाल TMP411C_DEVICE_ID:
		अगर (client->addr != 0x4e)
			वापस -ENODEV;
		kind = पंचांगp411;
		अवरोध;
	हाल TMP431_DEVICE_ID:
		अगर (client->addr != 0x4c && client->addr != 0x4d)
			वापस -ENODEV;
		kind = पंचांगp431;
		अवरोध;
	हाल TMP432_DEVICE_ID:
		अगर (client->addr != 0x4c && client->addr != 0x4d)
			वापस -ENODEV;
		kind = पंचांगp432;
		अवरोध;
	हाल TMP435_DEVICE_ID:
		kind = पंचांगp435;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	reg = i2c_smbus_पढ़ो_byte_data(client, TMP401_CONFIG_READ);
	अगर (reg & 0x1b)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, TMP401_CONVERSION_RATE_READ);
	/* Datasheet says: 0x1-0x6 */
	अगर (reg > 15)
		वापस -ENODEV;

	strlcpy(info->type, पंचांगp401_id[kind].name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp401_probe(काष्ठा i2c_client *client)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"TMP401", "TMP411", "TMP431", "TMP432", "TMP435", "TMP461"
	पूर्ण;
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा पंचांगp401_data *data;
	पूर्णांक groups = 0, status;

	data = devm_kzalloc(dev, माप(काष्ठा पंचांगp401_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);
	data->kind = i2c_match_id(पंचांगp401_id, client)->driver_data;

	/* Initialize the TMP401 chip */
	status = पंचांगp401_init_client(data, client);
	अगर (status < 0)
		वापस status;

	/* Register sysfs hooks */
	data->groups[groups++] = &पंचांगp401_group;

	/* Register additional पंचांगp411 sysfs hooks */
	अगर (data->kind == पंचांगp411)
		data->groups[groups++] = &पंचांगp411_group;

	/* Register additional पंचांगp432 sysfs hooks */
	अगर (data->kind == पंचांगp432)
		data->groups[groups++] = &पंचांगp432_group;

	अगर (data->kind == पंचांगp461)
		data->groups[groups++] = &पंचांगp461_group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(dev, "Detected TI %s chip\n", names[data->kind]);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver पंचांगp401_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "tmp401",
	पूर्ण,
	.probe_new	= पंचांगp401_probe,
	.id_table	= पंचांगp401_id,
	.detect		= पंचांगp401_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(पंचांगp401_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Texas Instruments TMP401 temperature sensor driver");
MODULE_LICENSE("GPL");
