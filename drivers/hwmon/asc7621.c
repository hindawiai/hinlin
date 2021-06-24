<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * asc7621.c - Part of lm_sensors, Linux kernel modules क्रम hardware monitoring
 * Copyright (c) 2007, 2010 George Joseph  <george.joseph@fairview5.com>
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
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x2c, 0x2d, 0x2e, I2C_CLIENT_END
पूर्ण;

क्रमागत asc7621_type अणु
	asc7621,
	asc7621a
पूर्ण;

#घोषणा INTERVAL_HIGH   (HZ + HZ / 2)
#घोषणा INTERVAL_LOW    (1 * 60 * HZ)
#घोषणा PRI_NONE        0
#घोषणा PRI_LOW         1
#घोषणा PRI_HIGH        2
#घोषणा FIRST_CHIP      asc7621
#घोषणा LAST_CHIP       asc7621a

काष्ठा asc7621_chip अणु
	अक्षर *name;
	क्रमागत asc7621_type chip_type;
	u8 company_reg;
	u8 company_id;
	u8 verstep_reg;
	u8 verstep_id;
	स्थिर अचिन्हित लघु *addresses;
पूर्ण;

अटल काष्ठा asc7621_chip asc7621_chips[] = अणु
	अणु
		.name = "asc7621",
		.chip_type = asc7621,
		.company_reg = 0x3e,
		.company_id = 0x61,
		.verstep_reg = 0x3f,
		.verstep_id = 0x6c,
		.addresses = normal_i2c,
	 पूर्ण,
	अणु
		.name = "asc7621a",
		.chip_type = asc7621a,
		.company_reg = 0x3e,
		.company_id = 0x61,
		.verstep_reg = 0x3f,
		.verstep_id = 0x6d,
		.addresses = normal_i2c,
	 पूर्ण,
पूर्ण;

/*
 * Defines the highest रेजिस्टर to be used, not the count.
 * The actual count will probably be smaller because of gaps
 * in the implementation (unused रेजिस्टर locations).
 * This define will safely set the array size of both the parameter
 * and data arrays.
 * This comes from the data sheet रेजिस्टर description table.
 */
#घोषणा LAST_REGISTER 0xff

काष्ठा asc7621_data अणु
	काष्ठा i2c_client client;
	काष्ठा device *class_dev;
	काष्ठा mutex update_lock;
	पूर्णांक valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_high_पढ़ोing;	/* In jअगरfies */
	अचिन्हित दीर्घ last_low_पढ़ोing;		/* In jअगरfies */
	/*
	 * Registers we care about occupy the corresponding index
	 * in the array.  Registers we करोn't care about are left
	 * at 0.
	 */
	u8 reg[LAST_REGISTER + 1];
पूर्ण;

/*
 * Macro to get the parent asc7621_param काष्ठाure
 * from a sensor_device_attribute passed पूर्णांकo the
 * show/store functions.
 */
#घोषणा to_asc7621_param(_sda) \
	container_of(_sda, काष्ठा asc7621_param, sda)

/*
 * Each parameter to be retrieved needs an asc7621_param काष्ठाure
 * allocated.  It contains the sensor_device_attribute काष्ठाure
 * and the control info needed to retrieve the value from the रेजिस्टर map.
 */
काष्ठा asc7621_param अणु
	काष्ठा sensor_device_attribute sda;
	u8 priority;
	u8 msb[3];
	u8 lsb[3];
	u8 mask[3];
	u8 shअगरt[3];
पूर्ण;

/*
 * This is the map that ultimately indicates whether we'll be
 * retrieving a रेजिस्टर value or not, and at what frequency.
 */
अटल u8 asc7621_रेजिस्टर_priorities[255];

अटल काष्ठा asc7621_data *asc7621_update_device(काष्ठा device *dev);

अटल अंतरभूत u8 पढ़ो_byte(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक res = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (res < 0) अणु
		dev_err(&client->dev,
			"Unable to read from register 0x%02x.\n", reg);
		वापस 0;
	पूर्ण
	वापस res & 0xff;
पूर्ण

अटल अंतरभूत पूर्णांक ग_लिखो_byte(काष्ठा i2c_client *client, u8 reg, u8 data)
अणु
	पूर्णांक res = i2c_smbus_ग_लिखो_byte_data(client, reg, data);
	अगर (res < 0) अणु
		dev_err(&client->dev,
			"Unable to write value 0x%02x to register 0x%02x.\n",
			data, reg);
	पूर्ण
	वापस res;
पूर्ण

/*
 * Data Handlers
 * Each function handles the क्रमmatting, storage
 * and retrieval of like parameters.
 */

#घोषणा SETUP_SHOW_DATA_PARAM(d, a) \
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(a); \
	काष्ठा asc7621_data *data = asc7621_update_device(d); \
	काष्ठा asc7621_param *param = to_asc7621_param(sda)

#घोषणा SETUP_STORE_DATA_PARAM(d, a) \
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(a); \
	काष्ठा i2c_client *client = to_i2c_client(d); \
	काष्ठा asc7621_data *data = i2c_get_clientdata(client); \
	काष्ठा asc7621_param *param = to_asc7621_param(sda)

/*
 * u8 is just what it sounds like...an अचिन्हित byte with no
 * special क्रमmatting.
 */
अटल sमाप_प्रकार show_u8(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);

	वापस प्र_लिखो(buf, "%u\n", data->reg[param->msb[0]]);
पूर्ण

अटल sमाप_प्रकार store_u8(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	reqval = clamp_val(reqval, 0, 255);

	mutex_lock(&data->update_lock);
	data->reg[param->msb[0]] = reqval;
	ग_लिखो_byte(client, param->msb[0], reqval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Many of the config values occupy only a few bits of a रेजिस्टर.
 */
अटल sमाप_प्रकार show_biपंचांगask(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);

	वापस प्र_लिखो(buf, "%u\n",
		       (data->reg[param->msb[0]] >> param->
			shअगरt[0]) & param->mask[0]);
पूर्ण

अटल sमाप_प्रकार store_biपंचांगask(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;
	u8 currval;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	reqval = clamp_val(reqval, 0, param->mask[0]);

	reqval = (reqval & param->mask[0]) << param->shअगरt[0];

	mutex_lock(&data->update_lock);
	currval = पढ़ो_byte(client, param->msb[0]);
	reqval |= (currval & ~(param->mask[0] << param->shअगरt[0]));
	data->reg[param->msb[0]] = reqval;
	ग_लिखो_byte(client, param->msb[0], reqval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * 16 bit fan rpm values
 * reported by the device as the number of 11.111us periods (90khz)
 * between full fan rotations.  Thereक्रमe...
 * RPM = (90000 * 60) / रेजिस्टर value
 */
अटल sमाप_प्रकार show_fan16(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u16 regval;

	mutex_lock(&data->update_lock);
	regval = (data->reg[param->msb[0]] << 8) | data->reg[param->lsb[0]];
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%u\n",
		       (regval == 0 ? -1 : (regval) ==
			0xffff ? 0 : 5400000 / regval));
पूर्ण

अटल sमाप_प्रकार store_fan16(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	/*
	 * If a minimum RPM of zero is requested, then we set the रेजिस्टर to
	 * 0xffff. This value allows the fan to be stopped completely without
	 * generating an alarm.
	 */
	reqval =
	    (reqval <= 0 ? 0xffff : clamp_val(5400000 / reqval, 0, 0xfffe));

	mutex_lock(&data->update_lock);
	data->reg[param->msb[0]] = (reqval >> 8) & 0xff;
	data->reg[param->lsb[0]] = reqval & 0xff;
	ग_लिखो_byte(client, param->msb[0], data->reg[param->msb[0]]);
	ग_लिखो_byte(client, param->lsb[0], data->reg[param->lsb[0]]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/*
 * Voltages are scaled in the device so that the nominal voltage
 * is 3/4ths of the 0-255 range (i.e. 192).
 * If all voltages are 'normal' then all voltage रेजिस्टरs will
 * पढ़ो 0xC0.
 *
 * The data sheet provides us with the 3/4 scale value क्रम each voltage
 * which is stored in in_scaling.  The sda->index parameter value provides
 * the index पूर्णांकo in_scaling.
 *
 * NOTE: The chip expects the first 2 inमाला_दो be 2.5 and 2.25 volts
 * respectively. That करोesn't mean that's what the motherboard provides. :)
 */

अटल स्थिर पूर्णांक asc7621_in_scaling[] = अणु
	2500, 2250, 3300, 5000, 12000
पूर्ण;

अटल sमाप_प्रकार show_in10(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u16 regval;
	u8 nr = sda->index;

	mutex_lock(&data->update_lock);
	regval = (data->reg[param->msb[0]] << 8) | (data->reg[param->lsb[0]]);
	mutex_unlock(&data->update_lock);

	/* The LSB value is a 2-bit scaling of the MSB's LSbit value. */
	regval = (regval >> 6) * asc7621_in_scaling[nr] / (0xc0 << 2);

	वापस प्र_लिखो(buf, "%u\n", regval);
पूर्ण

/* 8 bit voltage values (the mins and maxs) */
अटल sमाप_प्रकार show_in8(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 nr = sda->index;

	वापस प्र_लिखो(buf, "%u\n",
		       ((data->reg[param->msb[0]] *
			 asc7621_in_scaling[nr]) / 0xc0));
पूर्ण

अटल sमाप_प्रकार store_in8(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;
	u8 nr = sda->index;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	reqval = clamp_val(reqval, 0, 0xffff);

	reqval = reqval * 0xc0 / asc7621_in_scaling[nr];

	reqval = clamp_val(reqval, 0, 0xff);

	mutex_lock(&data->update_lock);
	data->reg[param->msb[0]] = reqval;
	ग_लिखो_byte(client, param->msb[0], reqval);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_temp8(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);

	वापस प्र_लिखो(buf, "%d\n", ((s8) data->reg[param->msb[0]]) * 1000);
पूर्ण

अटल sमाप_प्रकार store_temp8(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;
	s8 temp;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	reqval = clamp_val(reqval, -127000, 127000);

	temp = reqval / 1000;

	mutex_lock(&data->update_lock);
	data->reg[param->msb[0]] = temp;
	ग_लिखो_byte(client, param->msb[0], temp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Temperatures that occupy 2 bytes always have the whole
 * number of degrees in the MSB with some part of the LSB
 * indicating fractional degrees.
 */

/*   mmmmmmmm.llxxxxxx */
अटल sमाप_प्रकार show_temp10(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 msb, lsb;
	पूर्णांक temp;

	mutex_lock(&data->update_lock);
	msb = data->reg[param->msb[0]];
	lsb = (data->reg[param->lsb[0]] >> 6) & 0x03;
	temp = (((s8) msb) * 1000) + (lsb * 250);
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

/*   mmmmmm.ll */
अटल sमाप_प्रकार show_temp62(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 regval = data->reg[param->msb[0]];
	पूर्णांक temp = ((s8) (regval & 0xfc) * 1000) + ((regval & 0x03) * 250);

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार store_temp62(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval, i, f;
	s8 temp;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	reqval = clamp_val(reqval, -32000, 31750);
	i = reqval / 1000;
	f = reqval - (i * 1000);
	temp = i << 2;
	temp |= f / 250;

	mutex_lock(&data->update_lock);
	data->reg[param->msb[0]] = temp;
	ग_लिखो_byte(client, param->msb[0], temp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * The aSC7621 करोesn't provide an "auto_point2".  Instead, you
 * specअगरy the स्वतः_poपूर्णांक1 and a range.  To keep with the sysfs
 * hwmon specs, we synthesize the स्वतः_poपूर्णांक_2 from them.
 */

अटल स्थिर u32 asc7621_range_map[] = अणु
	2000, 2500, 3330, 4000, 5000, 6670, 8000, 10000,
	13330, 16000, 20000, 26670, 32000, 40000, 53330, 80000,
पूर्ण;

अटल sमाप_प्रकार show_ap2_temp(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	दीर्घ स्वतः_poपूर्णांक1;
	u8 regval;
	पूर्णांक temp;

	mutex_lock(&data->update_lock);
	स्वतः_poपूर्णांक1 = ((s8) data->reg[param->msb[1]]) * 1000;
	regval =
	    ((data->reg[param->msb[0]] >> param->shअगरt[0]) & param->mask[0]);
	temp = स्वतः_poपूर्णांक1 + asc7621_range_map[clamp_val(regval, 0, 15)];
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", temp);

पूर्ण

अटल sमाप_प्रकार store_ap2_temp(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval, स्वतः_poपूर्णांक1;
	पूर्णांक i;
	u8 currval, newval = 0;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	स्वतः_poपूर्णांक1 = data->reg[param->msb[1]] * 1000;
	reqval = clamp_val(reqval, स्वतः_poपूर्णांक1 + 2000, स्वतः_poपूर्णांक1 + 80000);

	क्रम (i = ARRAY_SIZE(asc7621_range_map) - 1; i >= 0; i--) अणु
		अगर (reqval >= स्वतः_poपूर्णांक1 + asc7621_range_map[i]) अणु
			newval = i;
			अवरोध;
		पूर्ण
	पूर्ण

	newval = (newval & param->mask[0]) << param->shअगरt[0];
	currval = पढ़ो_byte(client, param->msb[0]);
	newval |= (currval & ~(param->mask[0] << param->shअगरt[0]));
	data->reg[param->msb[0]] = newval;
	ग_लिखो_byte(client, param->msb[0], newval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_ac(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 config, altbit, regval;
	अटल स्थिर u8 map[] = अणु
		0x01, 0x02, 0x04, 0x1f, 0x00, 0x06, 0x07, 0x10,
		0x08, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
	पूर्ण;

	mutex_lock(&data->update_lock);
	config = (data->reg[param->msb[0]] >> param->shअगरt[0]) & param->mask[0];
	altbit = (data->reg[param->msb[1]] >> param->shअगरt[1]) & param->mask[1];
	regval = config | (altbit << 3);
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%u\n", map[clamp_val(regval, 0, 15)]);
पूर्ण

अटल sमाप_प्रकार store_pwm_ac(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	अचिन्हित दीर्घ reqval;
	u8 currval, config, altbit, newval;
	अटल स्थिर u16 map[] = अणु
		0x04, 0x00, 0x01, 0xff, 0x02, 0xff, 0x05, 0x06,
		0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f,
		0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
	पूर्ण;

	अगर (kम_से_अदीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	अगर (reqval > 31)
		वापस -EINVAL;

	reqval = map[reqval];
	अगर (reqval == 0xff)
		वापस -EINVAL;

	config = reqval & 0x07;
	altbit = (reqval >> 3) & 0x01;

	config = (config & param->mask[0]) << param->shअगरt[0];
	altbit = (altbit & param->mask[1]) << param->shअगरt[1];

	mutex_lock(&data->update_lock);
	currval = पढ़ो_byte(client, param->msb[0]);
	newval = config | (currval & ~(param->mask[0] << param->shअगरt[0]));
	newval = altbit | (newval & ~(param->mask[1] << param->shअगरt[1]));
	data->reg[param->msb[0]] = newval;
	ग_लिखो_byte(client, param->msb[0], newval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_enable(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 config, altbit, minoff, val, newval;

	mutex_lock(&data->update_lock);
	config = (data->reg[param->msb[0]] >> param->shअगरt[0]) & param->mask[0];
	altbit = (data->reg[param->msb[1]] >> param->shअगरt[1]) & param->mask[1];
	minoff = (data->reg[param->msb[2]] >> param->shअगरt[2]) & param->mask[2];
	mutex_unlock(&data->update_lock);

	val = config | (altbit << 3);

	अगर (val == 3 || val >= 10)
		newval = 255;
	अन्यथा अगर (val == 4)
		newval = 0;
	अन्यथा अगर (val == 7)
		newval = 1;
	अन्यथा अगर (minoff == 1)
		newval = 2;
	अन्यथा
		newval = 3;

	वापस प्र_लिखो(buf, "%u\n", newval);
पूर्ण

अटल sमाप_प्रकार store_pwm_enable(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;
	u8 currval, config, altbit, newval, minoff = 255;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	चयन (reqval) अणु
	हाल 0:
		newval = 0x04;
		अवरोध;
	हाल 1:
		newval = 0x07;
		अवरोध;
	हाल 2:
		newval = 0x00;
		minoff = 1;
		अवरोध;
	हाल 3:
		newval = 0x00;
		minoff = 0;
		अवरोध;
	हाल 255:
		newval = 0x03;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	config = newval & 0x07;
	altbit = (newval >> 3) & 0x01;

	mutex_lock(&data->update_lock);
	config = (config & param->mask[0]) << param->shअगरt[0];
	altbit = (altbit & param->mask[1]) << param->shअगरt[1];
	currval = पढ़ो_byte(client, param->msb[0]);
	newval = config | (currval & ~(param->mask[0] << param->shअगरt[0]));
	newval = altbit | (newval & ~(param->mask[1] << param->shअगरt[1]));
	data->reg[param->msb[0]] = newval;
	ग_लिखो_byte(client, param->msb[0], newval);
	अगर (minoff < 255) अणु
		minoff = (minoff & param->mask[2]) << param->shअगरt[2];
		currval = पढ़ो_byte(client, param->msb[2]);
		newval =
		    minoff | (currval & ~(param->mask[2] << param->shअगरt[2]));
		data->reg[param->msb[2]] = newval;
		ग_लिखो_byte(client, param->msb[2], newval);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल स्थिर u32 asc7621_pwm_freq_map[] = अणु
	10, 15, 23, 30, 38, 47, 62, 94,
	23000, 24000, 25000, 26000, 27000, 28000, 29000, 30000
पूर्ण;

अटल sमाप_प्रकार show_pwm_freq(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 regval =
	    (data->reg[param->msb[0]] >> param->shअगरt[0]) & param->mask[0];

	regval = clamp_val(regval, 0, 15);

	वापस प्र_लिखो(buf, "%u\n", asc7621_pwm_freq_map[regval]);
पूर्ण

अटल sमाप_प्रकार store_pwm_freq(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	अचिन्हित दीर्घ reqval;
	u8 currval, newval = 255;
	पूर्णांक i;

	अगर (kम_से_अदीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(asc7621_pwm_freq_map); i++) अणु
		अगर (reqval == asc7621_pwm_freq_map[i]) अणु
			newval = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (newval == 255)
		वापस -EINVAL;

	newval = (newval & param->mask[0]) << param->shअगरt[0];

	mutex_lock(&data->update_lock);
	currval = पढ़ो_byte(client, param->msb[0]);
	newval |= (currval & ~(param->mask[0] << param->shअगरt[0]));
	data->reg[param->msb[0]] = newval;
	ग_लिखो_byte(client, param->msb[0], newval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल स्थिर u32 asc7621_pwm_स्वतः_spinup_map[] =  अणु
	0, 100, 250, 400, 700, 1000, 2000, 4000
पूर्ण;

अटल sमाप_प्रकार show_pwm_ast(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 regval =
	    (data->reg[param->msb[0]] >> param->shअगरt[0]) & param->mask[0];

	regval = clamp_val(regval, 0, 7);

	वापस प्र_लिखो(buf, "%u\n", asc7621_pwm_स्वतः_spinup_map[regval]);

पूर्ण

अटल sमाप_प्रकार store_pwm_ast(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;
	u8 currval, newval = 255;
	u32 i;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(asc7621_pwm_स्वतः_spinup_map); i++) अणु
		अगर (reqval == asc7621_pwm_स्वतः_spinup_map[i]) अणु
			newval = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (newval == 255)
		वापस -EINVAL;

	newval = (newval & param->mask[0]) << param->shअगरt[0];

	mutex_lock(&data->update_lock);
	currval = पढ़ो_byte(client, param->msb[0]);
	newval |= (currval & ~(param->mask[0] << param->shअगरt[0]));
	data->reg[param->msb[0]] = newval;
	ग_लिखो_byte(client, param->msb[0], newval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल स्थिर u32 asc7621_temp_smoothing_समय_map[] = अणु
	35000, 17600, 11800, 7000, 4400, 3000, 1600, 800
पूर्ण;

अटल sमाप_प्रकार show_temp_st(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 regval =
	    (data->reg[param->msb[0]] >> param->shअगरt[0]) & param->mask[0];
	regval = clamp_val(regval, 0, 7);

	वापस प्र_लिखो(buf, "%u\n", asc7621_temp_smoothing_समय_map[regval]);
पूर्ण

अटल sमाप_प्रकार store_temp_st(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	SETUP_STORE_DATA_PARAM(dev, attr);
	दीर्घ reqval;
	u8 currval, newval = 255;
	u32 i;

	अगर (kम_से_दीर्घ(buf, 10, &reqval))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(asc7621_temp_smoothing_समय_map); i++) अणु
		अगर (reqval == asc7621_temp_smoothing_समय_map[i]) अणु
			newval = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (newval == 255)
		वापस -EINVAL;

	newval = (newval & param->mask[0]) << param->shअगरt[0];

	mutex_lock(&data->update_lock);
	currval = पढ़ो_byte(client, param->msb[0]);
	newval |= (currval & ~(param->mask[0] << param->shअगरt[0]));
	data->reg[param->msb[0]] = newval;
	ग_लिखो_byte(client, param->msb[0], newval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * End of data handlers
 *
 * These defines करो nothing more than make the table easier
 * to पढ़ो when wrapped at column 80.
 */

/*
 * Creates a variable length array inititalizer.
 * VAA(1,3,5,7) would produce अणु1,3,5,7पूर्ण
 */
#घोषणा VAA(args...) अणुargsपूर्ण

#घोषणा PREAD(name, n, pri, rm, rl, m, s, r) \
	अणु.sda = SENSOR_ATTR(name, S_IRUGO, show_##r, शून्य, n), \
	  .priority = pri, .msb[0] = rm, .lsb[0] = rl, .mask[0] = m, \
	  .shअगरt[0] = s,पूर्ण

#घोषणा PWRITE(name, n, pri, rm, rl, m, s, r) \
	अणु.sda = SENSOR_ATTR(name, S_IRUGO | S_IWUSR, show_##r, store_##r, n), \
	  .priority = pri, .msb[0] = rm, .lsb[0] = rl, .mask[0] = m, \
	  .shअगरt[0] = s,पूर्ण

/*
 * PWRITEM assumes that the initializers क्रम the .msb, .lsb, .mask and .shअगरt
 * were created using the VAA macro.
 */
#घोषणा PWRITEM(name, n, pri, rm, rl, m, s, r) \
	अणु.sda = SENSOR_ATTR(name, S_IRUGO | S_IWUSR, show_##r, store_##r, n), \
	  .priority = pri, .msb = rm, .lsb = rl, .mask = m, .shअगरt = s,पूर्ण

अटल काष्ठा asc7621_param asc7621_params[] = अणु
	PREAD(in0_input, 0, PRI_HIGH, 0x20, 0x13, 0, 0, in10),
	PREAD(in1_input, 1, PRI_HIGH, 0x21, 0x18, 0, 0, in10),
	PREAD(in2_input, 2, PRI_HIGH, 0x22, 0x11, 0, 0, in10),
	PREAD(in3_input, 3, PRI_HIGH, 0x23, 0x12, 0, 0, in10),
	PREAD(in4_input, 4, PRI_HIGH, 0x24, 0x14, 0, 0, in10),

	PWRITE(in0_min, 0, PRI_LOW, 0x44, 0, 0, 0, in8),
	PWRITE(in1_min, 1, PRI_LOW, 0x46, 0, 0, 0, in8),
	PWRITE(in2_min, 2, PRI_LOW, 0x48, 0, 0, 0, in8),
	PWRITE(in3_min, 3, PRI_LOW, 0x4a, 0, 0, 0, in8),
	PWRITE(in4_min, 4, PRI_LOW, 0x4c, 0, 0, 0, in8),

	PWRITE(in0_max, 0, PRI_LOW, 0x45, 0, 0, 0, in8),
	PWRITE(in1_max, 1, PRI_LOW, 0x47, 0, 0, 0, in8),
	PWRITE(in2_max, 2, PRI_LOW, 0x49, 0, 0, 0, in8),
	PWRITE(in3_max, 3, PRI_LOW, 0x4b, 0, 0, 0, in8),
	PWRITE(in4_max, 4, PRI_LOW, 0x4d, 0, 0, 0, in8),

	PREAD(in0_alarm, 0, PRI_HIGH, 0x41, 0, 0x01, 0, biपंचांगask),
	PREAD(in1_alarm, 1, PRI_HIGH, 0x41, 0, 0x01, 1, biपंचांगask),
	PREAD(in2_alarm, 2, PRI_HIGH, 0x41, 0, 0x01, 2, biपंचांगask),
	PREAD(in3_alarm, 3, PRI_HIGH, 0x41, 0, 0x01, 3, biपंचांगask),
	PREAD(in4_alarm, 4, PRI_HIGH, 0x42, 0, 0x01, 0, biपंचांगask),

	PREAD(fan1_input, 0, PRI_HIGH, 0x29, 0x28, 0, 0, fan16),
	PREAD(fan2_input, 1, PRI_HIGH, 0x2b, 0x2a, 0, 0, fan16),
	PREAD(fan3_input, 2, PRI_HIGH, 0x2d, 0x2c, 0, 0, fan16),
	PREAD(fan4_input, 3, PRI_HIGH, 0x2f, 0x2e, 0, 0, fan16),

	PWRITE(fan1_min, 0, PRI_LOW, 0x55, 0x54, 0, 0, fan16),
	PWRITE(fan2_min, 1, PRI_LOW, 0x57, 0x56, 0, 0, fan16),
	PWRITE(fan3_min, 2, PRI_LOW, 0x59, 0x58, 0, 0, fan16),
	PWRITE(fan4_min, 3, PRI_LOW, 0x5b, 0x5a, 0, 0, fan16),

	PREAD(fan1_alarm, 0, PRI_HIGH, 0x42, 0, 0x01, 2, biपंचांगask),
	PREAD(fan2_alarm, 1, PRI_HIGH, 0x42, 0, 0x01, 3, biपंचांगask),
	PREAD(fan3_alarm, 2, PRI_HIGH, 0x42, 0, 0x01, 4, biपंचांगask),
	PREAD(fan4_alarm, 3, PRI_HIGH, 0x42, 0, 0x01, 5, biपंचांगask),

	PREAD(temp1_input, 0, PRI_HIGH, 0x25, 0x10, 0, 0, temp10),
	PREAD(temp2_input, 1, PRI_HIGH, 0x26, 0x15, 0, 0, temp10),
	PREAD(temp3_input, 2, PRI_HIGH, 0x27, 0x16, 0, 0, temp10),
	PREAD(temp4_input, 3, PRI_HIGH, 0x33, 0x17, 0, 0, temp10),
	PREAD(temp5_input, 4, PRI_HIGH, 0xf7, 0xf6, 0, 0, temp10),
	PREAD(temp6_input, 5, PRI_HIGH, 0xf9, 0xf8, 0, 0, temp10),
	PREAD(temp7_input, 6, PRI_HIGH, 0xfb, 0xfa, 0, 0, temp10),
	PREAD(temp8_input, 7, PRI_HIGH, 0xfd, 0xfc, 0, 0, temp10),

	PWRITE(temp1_min, 0, PRI_LOW, 0x4e, 0, 0, 0, temp8),
	PWRITE(temp2_min, 1, PRI_LOW, 0x50, 0, 0, 0, temp8),
	PWRITE(temp3_min, 2, PRI_LOW, 0x52, 0, 0, 0, temp8),
	PWRITE(temp4_min, 3, PRI_LOW, 0x34, 0, 0, 0, temp8),

	PWRITE(temp1_max, 0, PRI_LOW, 0x4f, 0, 0, 0, temp8),
	PWRITE(temp2_max, 1, PRI_LOW, 0x51, 0, 0, 0, temp8),
	PWRITE(temp3_max, 2, PRI_LOW, 0x53, 0, 0, 0, temp8),
	PWRITE(temp4_max, 3, PRI_LOW, 0x35, 0, 0, 0, temp8),

	PREAD(temp1_alarm, 0, PRI_HIGH, 0x41, 0, 0x01, 4, biपंचांगask),
	PREAD(temp2_alarm, 1, PRI_HIGH, 0x41, 0, 0x01, 5, biपंचांगask),
	PREAD(temp3_alarm, 2, PRI_HIGH, 0x41, 0, 0x01, 6, biपंचांगask),
	PREAD(temp4_alarm, 3, PRI_HIGH, 0x43, 0, 0x01, 0, biपंचांगask),

	PWRITE(temp1_source, 0, PRI_LOW, 0x02, 0, 0x07, 4, biपंचांगask),
	PWRITE(temp2_source, 1, PRI_LOW, 0x02, 0, 0x07, 0, biपंचांगask),
	PWRITE(temp3_source, 2, PRI_LOW, 0x03, 0, 0x07, 4, biपंचांगask),
	PWRITE(temp4_source, 3, PRI_LOW, 0x03, 0, 0x07, 0, biपंचांगask),

	PWRITE(temp1_smoothing_enable, 0, PRI_LOW, 0x62, 0, 0x01, 3, biपंचांगask),
	PWRITE(temp2_smoothing_enable, 1, PRI_LOW, 0x63, 0, 0x01, 7, biपंचांगask),
	PWRITE(temp3_smoothing_enable, 2, PRI_LOW, 0x63, 0, 0x01, 3, biपंचांगask),
	PWRITE(temp4_smoothing_enable, 3, PRI_LOW, 0x3c, 0, 0x01, 3, biपंचांगask),

	PWRITE(temp1_smoothing_समय, 0, PRI_LOW, 0x62, 0, 0x07, 0, temp_st),
	PWRITE(temp2_smoothing_समय, 1, PRI_LOW, 0x63, 0, 0x07, 4, temp_st),
	PWRITE(temp3_smoothing_समय, 2, PRI_LOW, 0x63, 0, 0x07, 0, temp_st),
	PWRITE(temp4_smoothing_समय, 3, PRI_LOW, 0x3c, 0, 0x07, 0, temp_st),

	PWRITE(temp1_स्वतः_poपूर्णांक1_temp_hyst, 0, PRI_LOW, 0x6d, 0, 0x0f, 4,
	       biपंचांगask),
	PWRITE(temp2_स्वतः_poपूर्णांक1_temp_hyst, 1, PRI_LOW, 0x6d, 0, 0x0f, 0,
	       biपंचांगask),
	PWRITE(temp3_स्वतः_poपूर्णांक1_temp_hyst, 2, PRI_LOW, 0x6e, 0, 0x0f, 4,
	       biपंचांगask),
	PWRITE(temp4_स्वतः_poपूर्णांक1_temp_hyst, 3, PRI_LOW, 0x6e, 0, 0x0f, 0,
	       biपंचांगask),

	PREAD(temp1_स्वतः_poपूर्णांक2_temp_hyst, 0, PRI_LOW, 0x6d, 0, 0x0f, 4,
	      biपंचांगask),
	PREAD(temp2_स्वतः_poपूर्णांक2_temp_hyst, 1, PRI_LOW, 0x6d, 0, 0x0f, 0,
	      biपंचांगask),
	PREAD(temp3_स्वतः_poपूर्णांक2_temp_hyst, 2, PRI_LOW, 0x6e, 0, 0x0f, 4,
	      biपंचांगask),
	PREAD(temp4_स्वतः_poपूर्णांक2_temp_hyst, 3, PRI_LOW, 0x6e, 0, 0x0f, 0,
	      biपंचांगask),

	PWRITE(temp1_स्वतः_poपूर्णांक1_temp, 0, PRI_LOW, 0x67, 0, 0, 0, temp8),
	PWRITE(temp2_स्वतः_poपूर्णांक1_temp, 1, PRI_LOW, 0x68, 0, 0, 0, temp8),
	PWRITE(temp3_स्वतः_poपूर्णांक1_temp, 2, PRI_LOW, 0x69, 0, 0, 0, temp8),
	PWRITE(temp4_स्वतः_poपूर्णांक1_temp, 3, PRI_LOW, 0x3b, 0, 0, 0, temp8),

	PWRITEM(temp1_स्वतः_poपूर्णांक2_temp, 0, PRI_LOW, VAA(0x5f, 0x67), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),
	PWRITEM(temp2_स्वतः_poपूर्णांक2_temp, 1, PRI_LOW, VAA(0x60, 0x68), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),
	PWRITEM(temp3_स्वतः_poपूर्णांक2_temp, 2, PRI_LOW, VAA(0x61, 0x69), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),
	PWRITEM(temp4_स्वतः_poपूर्णांक2_temp, 3, PRI_LOW, VAA(0x3c, 0x3b), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),

	PWRITE(temp1_crit, 0, PRI_LOW, 0x6a, 0, 0, 0, temp8),
	PWRITE(temp2_crit, 1, PRI_LOW, 0x6b, 0, 0, 0, temp8),
	PWRITE(temp3_crit, 2, PRI_LOW, 0x6c, 0, 0, 0, temp8),
	PWRITE(temp4_crit, 3, PRI_LOW, 0x3d, 0, 0, 0, temp8),

	PWRITE(temp5_enable, 4, PRI_LOW, 0x0e, 0, 0x01, 0, biपंचांगask),
	PWRITE(temp6_enable, 5, PRI_LOW, 0x0e, 0, 0x01, 1, biपंचांगask),
	PWRITE(temp7_enable, 6, PRI_LOW, 0x0e, 0, 0x01, 2, biपंचांगask),
	PWRITE(temp8_enable, 7, PRI_LOW, 0x0e, 0, 0x01, 3, biपंचांगask),

	PWRITE(remote1_offset, 0, PRI_LOW, 0x1c, 0, 0, 0, temp62),
	PWRITE(remote2_offset, 1, PRI_LOW, 0x1d, 0, 0, 0, temp62),

	PWRITE(pwm1, 0, PRI_HIGH, 0x30, 0, 0, 0, u8),
	PWRITE(pwm2, 1, PRI_HIGH, 0x31, 0, 0, 0, u8),
	PWRITE(pwm3, 2, PRI_HIGH, 0x32, 0, 0, 0, u8),

	PWRITE(pwm1_invert, 0, PRI_LOW, 0x5c, 0, 0x01, 4, biपंचांगask),
	PWRITE(pwm2_invert, 1, PRI_LOW, 0x5d, 0, 0x01, 4, biपंचांगask),
	PWRITE(pwm3_invert, 2, PRI_LOW, 0x5e, 0, 0x01, 4, biपंचांगask),

	PWRITEM(pwm1_enable, 0, PRI_LOW, VAA(0x5c, 0x5c, 0x62), VAA(0, 0, 0),
		VAA(0x07, 0x01, 0x01), VAA(5, 3, 5), pwm_enable),
	PWRITEM(pwm2_enable, 1, PRI_LOW, VAA(0x5d, 0x5d, 0x62), VAA(0, 0, 0),
		VAA(0x07, 0x01, 0x01), VAA(5, 3, 6), pwm_enable),
	PWRITEM(pwm3_enable, 2, PRI_LOW, VAA(0x5e, 0x5e, 0x62), VAA(0, 0, 0),
		VAA(0x07, 0x01, 0x01), VAA(5, 3, 7), pwm_enable),

	PWRITEM(pwm1_स्वतः_channels, 0, PRI_LOW, VAA(0x5c, 0x5c), VAA(0, 0),
		VAA(0x07, 0x01), VAA(5, 3), pwm_ac),
	PWRITEM(pwm2_स्वतः_channels, 1, PRI_LOW, VAA(0x5d, 0x5d), VAA(0, 0),
		VAA(0x07, 0x01), VAA(5, 3), pwm_ac),
	PWRITEM(pwm3_स्वतः_channels, 2, PRI_LOW, VAA(0x5e, 0x5e), VAA(0, 0),
		VAA(0x07, 0x01), VAA(5, 3), pwm_ac),

	PWRITE(pwm1_स्वतः_poपूर्णांक1_pwm, 0, PRI_LOW, 0x64, 0, 0, 0, u8),
	PWRITE(pwm2_स्वतः_poपूर्णांक1_pwm, 1, PRI_LOW, 0x65, 0, 0, 0, u8),
	PWRITE(pwm3_स्वतः_poपूर्णांक1_pwm, 2, PRI_LOW, 0x66, 0, 0, 0, u8),

	PWRITE(pwm1_स्वतः_poपूर्णांक2_pwm, 0, PRI_LOW, 0x38, 0, 0, 0, u8),
	PWRITE(pwm2_स्वतः_poपूर्णांक2_pwm, 1, PRI_LOW, 0x39, 0, 0, 0, u8),
	PWRITE(pwm3_स्वतः_poपूर्णांक2_pwm, 2, PRI_LOW, 0x3a, 0, 0, 0, u8),

	PWRITE(pwm1_freq, 0, PRI_LOW, 0x5f, 0, 0x0f, 0, pwm_freq),
	PWRITE(pwm2_freq, 1, PRI_LOW, 0x60, 0, 0x0f, 0, pwm_freq),
	PWRITE(pwm3_freq, 2, PRI_LOW, 0x61, 0, 0x0f, 0, pwm_freq),

	PREAD(pwm1_स्वतः_zone_asचिन्हित, 0, PRI_LOW, 0, 0, 0x03, 2, biपंचांगask),
	PREAD(pwm2_स्वतः_zone_asचिन्हित, 1, PRI_LOW, 0, 0, 0x03, 4, biपंचांगask),
	PREAD(pwm3_स्वतः_zone_asचिन्हित, 2, PRI_LOW, 0, 0, 0x03, 6, biपंचांगask),

	PWRITE(pwm1_स्वतः_spinup_समय, 0, PRI_LOW, 0x5c, 0, 0x07, 0, pwm_ast),
	PWRITE(pwm2_स्वतः_spinup_समय, 1, PRI_LOW, 0x5d, 0, 0x07, 0, pwm_ast),
	PWRITE(pwm3_स्वतः_spinup_समय, 2, PRI_LOW, 0x5e, 0, 0x07, 0, pwm_ast),

	PWRITE(peci_enable, 0, PRI_LOW, 0x40, 0, 0x01, 4, biपंचांगask),
	PWRITE(peci_avg, 0, PRI_LOW, 0x36, 0, 0x07, 0, biपंचांगask),
	PWRITE(peci_करोमुख्य, 0, PRI_LOW, 0x36, 0, 0x01, 3, biपंचांगask),
	PWRITE(peci_legacy, 0, PRI_LOW, 0x36, 0, 0x01, 4, biपंचांगask),
	PWRITE(peci_diode, 0, PRI_LOW, 0x0e, 0, 0x07, 4, biपंचांगask),
	PWRITE(peci_4करोमुख्य, 0, PRI_LOW, 0x0e, 0, 0x01, 4, biपंचांगask),

पूर्ण;

अटल काष्ठा asc7621_data *asc7621_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा asc7621_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

/*
 * The asc7621 chips guarantee consistent पढ़ोs of multi-byte values
 * regardless of the order of the पढ़ोs.  No special logic is needed
 * so we can just पढ़ो the रेजिस्टरs in whatever  order they appear
 * in the asc7621_params array.
 */

	mutex_lock(&data->update_lock);

	/* Read all the high priority रेजिस्टरs */

	अगर (!data->valid ||
	    समय_after(jअगरfies, data->last_high_पढ़ोing + INTERVAL_HIGH)) अणु

		क्रम (i = 0; i < ARRAY_SIZE(asc7621_रेजिस्टर_priorities); i++) अणु
			अगर (asc7621_रेजिस्टर_priorities[i] == PRI_HIGH) अणु
				data->reg[i] =
				    i2c_smbus_पढ़ो_byte_data(client, i) & 0xff;
			पूर्ण
		पूर्ण
		data->last_high_पढ़ोing = jअगरfies;
	पूर्ण			/* last_पढ़ोing */

	/* Read all the low priority रेजिस्टरs. */

	अगर (!data->valid ||
	    समय_after(jअगरfies, data->last_low_पढ़ोing + INTERVAL_LOW)) अणु

		क्रम (i = 0; i < ARRAY_SIZE(asc7621_params); i++) अणु
			अगर (asc7621_रेजिस्टर_priorities[i] == PRI_LOW) अणु
				data->reg[i] =
				    i2c_smbus_पढ़ो_byte_data(client, i) & 0xff;
			पूर्ण
		पूर्ण
		data->last_low_पढ़ोing = jअगरfies;
	पूर्ण			/* last_पढ़ोing */

	data->valid = 1;

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Standard detection and initialization below
 *
 * Helper function that checks अगर an address is valid
 * क्रम a particular chip.
 */

अटल अंतरभूत पूर्णांक valid_address_क्रम_chip(पूर्णांक chip_type, पूर्णांक address)
अणु
	पूर्णांक i;

	क्रम (i = 0; asc7621_chips[chip_type].addresses[i] != I2C_CLIENT_END;
	     i++) अणु
		अगर (asc7621_chips[chip_type].addresses[i] == address)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम asc7621_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक value;

	/* Warn अगर part was not "READY" */

	value = पढ़ो_byte(client, 0x40);

	अगर (value & 0x02) अणु
		dev_err(&client->dev,
			"Client (%d,0x%02x) config is locked.\n",
			i2c_adapter_id(client->adapter), client->addr);
	पूर्ण
	अगर (!(value & 0x04)) अणु
		dev_err(&client->dev, "Client (%d,0x%02x) is not ready.\n",
			i2c_adapter_id(client->adapter), client->addr);
	पूर्ण

/*
 * Start monitoring
 *
 * Try to clear LOCK, Set START, save everything अन्यथा
 */
	value = (value & ~0x02) | 0x01;
	ग_लिखो_byte(client, 0x40, value & 0xff);

पूर्ण

अटल पूर्णांक
asc7621_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा asc7621_data *data;
	पूर्णांक i, err;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	data = devm_kzalloc(&client->dev, माप(काष्ठा asc7621_data),
			    GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the asc7621 chip */
	asc7621_init_client(client);

	/* Create the sysfs entries */
	क्रम (i = 0; i < ARRAY_SIZE(asc7621_params); i++) अणु
		err =
		    device_create_file(&client->dev,
				       &(asc7621_params[i].sda.dev_attr));
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण

	data->class_dev = hwmon_device_रेजिस्टर(&client->dev);
	अगर (IS_ERR(data->class_dev)) अणु
		err = PTR_ERR(data->class_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	वापस 0;

निकास_हटाओ:
	क्रम (i = 0; i < ARRAY_SIZE(asc7621_params); i++) अणु
		device_हटाओ_file(&client->dev,
				   &(asc7621_params[i].sda.dev_attr));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक asc7621_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक company, verstep, chip_index;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	क्रम (chip_index = FIRST_CHIP; chip_index <= LAST_CHIP; chip_index++) अणु

		अगर (!valid_address_क्रम_chip(chip_index, client->addr))
			जारी;

		company = पढ़ो_byte(client,
			asc7621_chips[chip_index].company_reg);
		verstep = पढ़ो_byte(client,
			asc7621_chips[chip_index].verstep_reg);

		अगर (company == asc7621_chips[chip_index].company_id &&
		    verstep == asc7621_chips[chip_index].verstep_id) अणु
			strlcpy(info->type, asc7621_chips[chip_index].name,
				I2C_NAME_SIZE);

			dev_info(&adapter->dev, "Matched %s at 0x%02x\n",
				 asc7621_chips[chip_index].name, client->addr);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक asc7621_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा asc7621_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	hwmon_device_unरेजिस्टर(data->class_dev);

	क्रम (i = 0; i < ARRAY_SIZE(asc7621_params); i++) अणु
		device_हटाओ_file(&client->dev,
				   &(asc7621_params[i].sda.dev_attr));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id asc7621_id[] = अणु
	अणु"asc7621", asc7621पूर्ण,
	अणु"asc7621a", asc7621aपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, asc7621_id);

अटल काष्ठा i2c_driver asc7621_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "asc7621",
	पूर्ण,
	.probe_new = asc7621_probe,
	.हटाओ = asc7621_हटाओ,
	.id_table = asc7621_id,
	.detect = asc7621_detect,
	.address_list = normal_i2c,
पूर्ण;

अटल पूर्णांक __init sm_asc7621_init(व्योम)
अणु
	पूर्णांक i, j;
/*
 * Collect all the रेजिस्टरs needed पूर्णांकo a single array.
 * This way, अगर a रेजिस्टर isn't actually used क्रम anything,
 * we करोn't retrieve it.
 */

	क्रम (i = 0; i < ARRAY_SIZE(asc7621_params); i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(asc7621_params[i].msb); j++)
			asc7621_रेजिस्टर_priorities[asc7621_params[i].msb[j]] =
			    asc7621_params[i].priority;
		क्रम (j = 0; j < ARRAY_SIZE(asc7621_params[i].lsb); j++)
			asc7621_रेजिस्टर_priorities[asc7621_params[i].lsb[j]] =
			    asc7621_params[i].priority;
	पूर्ण
	वापस i2c_add_driver(&asc7621_driver);
पूर्ण

अटल व्योम __निकास sm_asc7621_निकास(व्योम)
अणु
	i2c_del_driver(&asc7621_driver);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("George Joseph");
MODULE_DESCRIPTION("Andigilog aSC7621 and aSC7621a driver");

module_init(sm_asc7621_init);
module_निकास(sm_asc7621_निकास);
