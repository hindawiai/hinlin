<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम the ADT7411 (I2C/SPI 8 channel 10 bit ADC & temperature-sensor)
 *
 *  Copyright (C) 2008, 2010 Pengutronix
 *
 *  TODO: SPI, use घातer-करोwn mode क्रम suspend?, पूर्णांकerrupt handling?
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/slab.h>

#घोषणा ADT7411_REG_STAT_1			0x00
#घोषणा ADT7411_STAT_1_INT_TEMP_HIGH		BIT(0)
#घोषणा ADT7411_STAT_1_INT_TEMP_LOW		BIT(1)
#घोषणा ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1	BIT(2)
#घोषणा ADT7411_STAT_1_EXT_TEMP_LOW		BIT(3)
#घोषणा ADT7411_STAT_1_EXT_TEMP_FAULT		BIT(4)
#घोषणा ADT7411_STAT_1_AIN2			BIT(5)
#घोषणा ADT7411_STAT_1_AIN3			BIT(6)
#घोषणा ADT7411_STAT_1_AIN4			BIT(7)
#घोषणा ADT7411_REG_STAT_2			0x01
#घोषणा ADT7411_STAT_2_AIN5			BIT(0)
#घोषणा ADT7411_STAT_2_AIN6			BIT(1)
#घोषणा ADT7411_STAT_2_AIN7			BIT(2)
#घोषणा ADT7411_STAT_2_AIN8			BIT(3)
#घोषणा ADT7411_STAT_2_VDD			BIT(4)
#घोषणा ADT7411_REG_INT_TEMP_VDD_LSB		0x03
#घोषणा ADT7411_REG_EXT_TEMP_AIN14_LSB		0x04
#घोषणा ADT7411_REG_VDD_MSB			0x06
#घोषणा ADT7411_REG_INT_TEMP_MSB		0x07
#घोषणा ADT7411_REG_EXT_TEMP_AIN1_MSB		0x08

#घोषणा ADT7411_REG_CFG1			0x18
#घोषणा ADT7411_CFG1_START_MONITOR		BIT(0)
#घोषणा ADT7411_CFG1_RESERVED_BIT1		BIT(1)
#घोषणा ADT7411_CFG1_EXT_TDM			BIT(2)
#घोषणा ADT7411_CFG1_RESERVED_BIT3		BIT(3)

#घोषणा ADT7411_REG_CFG2			0x19
#घोषणा ADT7411_CFG2_DISABLE_AVG		BIT(5)

#घोषणा ADT7411_REG_CFG3			0x1a
#घोषणा ADT7411_CFG3_ADC_CLK_225		BIT(0)
#घोषणा ADT7411_CFG3_RESERVED_BIT1		BIT(1)
#घोषणा ADT7411_CFG3_RESERVED_BIT2		BIT(2)
#घोषणा ADT7411_CFG3_RESERVED_BIT3		BIT(3)
#घोषणा ADT7411_CFG3_REF_VDD			BIT(4)

#घोषणा ADT7411_REG_VDD_HIGH			0x23
#घोषणा ADT7411_REG_VDD_LOW			0x24
#घोषणा ADT7411_REG_TEMP_HIGH(nr)		(0x25 + 2 * (nr))
#घोषणा ADT7411_REG_TEMP_LOW(nr)		(0x26 + 2 * (nr))
#घोषणा ADT7411_REG_IN_HIGH(nr)		((nr) > 1 \
						  ? 0x2b + 2 * ((nr)-2) \
						  : 0x27)
#घोषणा ADT7411_REG_IN_LOW(nr)			((nr) > 1 \
						  ? 0x2c + 2 * ((nr)-2) \
						  : 0x28)

#घोषणा ADT7411_REG_DEVICE_ID			0x4d
#घोषणा ADT7411_REG_MANUFACTURER_ID		0x4e

#घोषणा ADT7411_DEVICE_ID			0x2
#घोषणा ADT7411_MANUFACTURER_ID			0x41

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x48, 0x4a, 0x4b, I2C_CLIENT_END पूर्ण;

अटल स्थिर u8 adt7411_in_alarm_reg[] = अणु
	ADT7411_REG_STAT_2,
	ADT7411_REG_STAT_1,
	ADT7411_REG_STAT_1,
	ADT7411_REG_STAT_1,
	ADT7411_REG_STAT_1,
	ADT7411_REG_STAT_2,
	ADT7411_REG_STAT_2,
	ADT7411_REG_STAT_2,
	ADT7411_REG_STAT_2,
पूर्ण;

अटल स्थिर u8 adt7411_in_alarm_bits[] = अणु
	ADT7411_STAT_2_VDD,
	ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1,
	ADT7411_STAT_1_AIN2,
	ADT7411_STAT_1_AIN3,
	ADT7411_STAT_1_AIN4,
	ADT7411_STAT_2_AIN5,
	ADT7411_STAT_2_AIN6,
	ADT7411_STAT_2_AIN7,
	ADT7411_STAT_2_AIN8,
पूर्ण;

काष्ठा adt7411_data अणु
	काष्ठा mutex device_lock;	/* क्रम "atomic" device accesses */
	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ next_update;
	दीर्घ vref_cached;
	काष्ठा i2c_client *client;
	bool use_ext_temp;
पूर्ण;

/*
 * When पढ़ोing a रेजिस्टर containing (up to 4) lsb, all associated
 * msb-रेजिस्टरs get locked by the hardware. After _one_ of those msb is पढ़ो,
 * _all_ are unlocked. In order to use this locking correctly, पढ़ोing lsb/msb
 * is रक्षित here with a mutex, too.
 */
अटल पूर्णांक adt7411_पढ़ो_10_bit(काष्ठा i2c_client *client, u8 lsb_reg,
				u8 msb_reg, u8 lsb_shअगरt)
अणु
	काष्ठा adt7411_data *data = i2c_get_clientdata(client);
	पूर्णांक val, पंचांगp;

	mutex_lock(&data->device_lock);

	val = i2c_smbus_पढ़ो_byte_data(client, lsb_reg);
	अगर (val < 0)
		जाओ निकास_unlock;

	पंचांगp = (val >> lsb_shअगरt) & 3;
	val = i2c_smbus_पढ़ो_byte_data(client, msb_reg);

	अगर (val >= 0)
		val = (val << 2) | पंचांगp;

 निकास_unlock:
	mutex_unlock(&data->device_lock);

	वापस val;
पूर्ण

अटल पूर्णांक adt7411_modअगरy_bit(काष्ठा i2c_client *client, u8 reg, u8 bit,
				bool flag)
अणु
	काष्ठा adt7411_data *data = i2c_get_clientdata(client);
	पूर्णांक ret, val;

	mutex_lock(&data->device_lock);

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0)
		जाओ निकास_unlock;

	अगर (flag)
		val = ret | bit;
	अन्यथा
		val = ret & ~bit;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);

 निकास_unlock:
	mutex_unlock(&data->device_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार adt7411_show_bit(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(attr);
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, attr2->index);

	वापस ret < 0 ? ret : प्र_लिखो(buf, "%u\n", !!(ret & attr2->nr));
पूर्ण

अटल sमाप_प्रकार adt7411_set_bit(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *s_attr2 = to_sensor_dev_attr_2(attr);
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;
	अचिन्हित दीर्घ flag;

	ret = kम_से_अदीर्घ(buf, 0, &flag);
	अगर (ret || flag > 1)
		वापस -EINVAL;

	ret = adt7411_modअगरy_bit(client, s_attr2->index, s_attr2->nr, flag);

	/* क्रमce update */
	mutex_lock(&data->update_lock);
	data->next_update = jअगरfies;
	mutex_unlock(&data->update_lock);

	वापस ret < 0 ? ret : count;
पूर्ण

#घोषणा ADT7411_BIT_ATTR(__name, __reg, __bit) \
	SENSOR_DEVICE_ATTR_2(__name, S_IRUGO | S_IWUSR, adt7411_show_bit, \
	adt7411_set_bit, __bit, __reg)

अटल ADT7411_BIT_ATTR(no_average, ADT7411_REG_CFG2, ADT7411_CFG2_DISABLE_AVG);
अटल ADT7411_BIT_ATTR(fast_sampling, ADT7411_REG_CFG3, ADT7411_CFG3_ADC_CLK_225);
अटल ADT7411_BIT_ATTR(adc_ref_vdd, ADT7411_REG_CFG3, ADT7411_CFG3_REF_VDD);

अटल काष्ठा attribute *adt7411_attrs[] = अणु
	&sensor_dev_attr_no_average.dev_attr.attr,
	&sensor_dev_attr_fast_sampling.dev_attr.attr,
	&sensor_dev_attr_adc_ref_vdd.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(adt7411);

अटल पूर्णांक adt7411_पढ़ो_in_alarm(काष्ठा device *dev, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, adt7411_in_alarm_reg[channel]);
	अगर (ret < 0)
		वापस ret;
	*val = !!(ret & adt7411_in_alarm_bits[channel]);
	वापस 0;
पूर्ण

अटल पूर्णांक adt7411_पढ़ो_in_vdd(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	चयन (attr) अणु
	हाल hwmon_in_input:
		ret = adt7411_पढ़ो_10_bit(client, ADT7411_REG_INT_TEMP_VDD_LSB,
					  ADT7411_REG_VDD_MSB, 2);
		अगर (ret < 0)
			वापस ret;
		*val = ret * 7000 / 1024;
		वापस 0;
	हाल hwmon_in_min:
		ret = i2c_smbus_पढ़ो_byte_data(client, ADT7411_REG_VDD_LOW);
		अगर (ret < 0)
			वापस ret;
		*val = ret * 7000 / 256;
		वापस 0;
	हाल hwmon_in_max:
		ret = i2c_smbus_पढ़ो_byte_data(client, ADT7411_REG_VDD_HIGH);
		अगर (ret < 0)
			वापस ret;
		*val = ret * 7000 / 256;
		वापस 0;
	हाल hwmon_in_alarm:
		वापस adt7411_पढ़ो_in_alarm(dev, 0, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक adt7411_update_vref(काष्ठा device *dev)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक val;

	अगर (समय_after_eq(jअगरfies, data->next_update)) अणु
		val = i2c_smbus_पढ़ो_byte_data(client, ADT7411_REG_CFG3);
		अगर (val < 0)
			वापस val;

		अगर (val & ADT7411_CFG3_REF_VDD) अणु
			val = adt7411_पढ़ो_in_vdd(dev, hwmon_in_input,
						  &data->vref_cached);
			अगर (val < 0)
				वापस val;
		पूर्ण अन्यथा अणु
			data->vref_cached = 2250;
		पूर्ण

		data->next_update = jअगरfies + HZ;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adt7411_पढ़ो_in_chan(काष्ठा device *dev, u32 attr, पूर्णांक channel,
				दीर्घ *val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	पूर्णांक ret;
	पूर्णांक reg, lsb_reg, lsb_shअगरt;
	पूर्णांक nr = channel - 1;

	mutex_lock(&data->update_lock);
	ret = adt7411_update_vref(dev);
	अगर (ret < 0)
		जाओ निकास_unlock;

	चयन (attr) अणु
	हाल hwmon_in_input:
		lsb_reg = ADT7411_REG_EXT_TEMP_AIN14_LSB + (nr >> 2);
		lsb_shअगरt = 2 * (nr & 0x03);
		ret = adt7411_पढ़ो_10_bit(client, lsb_reg,
					  ADT7411_REG_EXT_TEMP_AIN1_MSB + nr,
					  lsb_shअगरt);
		अगर (ret < 0)
			जाओ निकास_unlock;
		*val = ret * data->vref_cached / 1024;
		ret = 0;
		अवरोध;
	हाल hwmon_in_min:
	हाल hwmon_in_max:
		reg = (attr == hwmon_in_min)
			? ADT7411_REG_IN_LOW(channel)
			: ADT7411_REG_IN_HIGH(channel);
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (ret < 0)
			जाओ निकास_unlock;
		*val = ret * data->vref_cached / 256;
		ret = 0;
		अवरोध;
	हाल hwmon_in_alarm:
		ret = adt7411_पढ़ो_in_alarm(dev, channel, val);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
 निकास_unlock:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adt7411_पढ़ो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			   दीर्घ *val)
अणु
	अगर (channel == 0)
		वापस adt7411_पढ़ो_in_vdd(dev, attr, val);
	अन्यथा
		वापस adt7411_पढ़ो_in_chan(dev, attr, channel, val);
पूर्ण


अटल पूर्णांक adt7411_पढ़ो_temp_alarm(काष्ठा device *dev, u32 attr, पूर्णांक channel,
				   दीर्घ *val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret, bit;

	ret = i2c_smbus_पढ़ो_byte_data(client, ADT7411_REG_STAT_1);
	अगर (ret < 0)
		वापस ret;

	चयन (attr) अणु
	हाल hwmon_temp_min_alarm:
		bit = channel ? ADT7411_STAT_1_EXT_TEMP_LOW
			      : ADT7411_STAT_1_INT_TEMP_LOW;
		अवरोध;
	हाल hwmon_temp_max_alarm:
		bit = channel ? ADT7411_STAT_1_EXT_TEMP_HIGH_AIN1
			      : ADT7411_STAT_1_INT_TEMP_HIGH;
		अवरोध;
	हाल hwmon_temp_fault:
		bit = ADT7411_STAT_1_EXT_TEMP_FAULT;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	*val = !!(ret & bit);
	वापस 0;
पूर्ण

अटल पूर्णांक adt7411_पढ़ो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret, reg, regl, regh;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		regl = channel ? ADT7411_REG_EXT_TEMP_AIN14_LSB :
				 ADT7411_REG_INT_TEMP_VDD_LSB;
		regh = channel ? ADT7411_REG_EXT_TEMP_AIN1_MSB :
				 ADT7411_REG_INT_TEMP_MSB;
		ret = adt7411_पढ़ो_10_bit(client, regl, regh, 0);
		अगर (ret < 0)
			वापस ret;
		ret = ret & 0x200 ? ret - 0x400 : ret; /* 10 bit चिन्हित */
		*val = ret * 250;
		वापस 0;
	हाल hwmon_temp_min:
	हाल hwmon_temp_max:
		reg = (attr == hwmon_temp_min)
			? ADT7411_REG_TEMP_LOW(channel)
			: ADT7411_REG_TEMP_HIGH(channel);
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (ret < 0)
			वापस ret;
		ret = ret & 0x80 ? ret - 0x100 : ret; /* 8 bit चिन्हित */
		*val = ret * 1000;
		वापस 0;
	हाल hwmon_temp_min_alarm:
	हाल hwmon_temp_max_alarm:
	हाल hwmon_temp_fault:
		वापस adt7411_पढ़ो_temp_alarm(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक adt7411_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस adt7411_पढ़ो_in(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस adt7411_पढ़ो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक adt7411_ग_लिखो_in_vdd(काष्ठा device *dev, u32 attr, दीर्घ val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक reg;

	val = clamp_val(val, 0, 255 * 7000 / 256);
	val = DIV_ROUND_CLOSEST(val * 256, 7000);

	चयन (attr) अणु
	हाल hwmon_in_min:
		reg = ADT7411_REG_VDD_LOW;
		अवरोध;
	हाल hwmon_in_max:
		reg = ADT7411_REG_VDD_HIGH;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक adt7411_ग_लिखो_in_chan(काष्ठा device *dev, u32 attr, पूर्णांक channel,
				 दीर्घ val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret, reg;

	mutex_lock(&data->update_lock);
	ret = adt7411_update_vref(dev);
	अगर (ret < 0)
		जाओ निकास_unlock;
	val = clamp_val(val, 0, 255 * data->vref_cached / 256);
	val = DIV_ROUND_CLOSEST(val * 256, data->vref_cached);

	चयन (attr) अणु
	हाल hwmon_in_min:
		reg = ADT7411_REG_IN_LOW(channel);
		अवरोध;
	हाल hwmon_in_max:
		reg = ADT7411_REG_IN_HIGH(channel);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		जाओ निकास_unlock;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
 निकास_unlock:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adt7411_ग_लिखो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			    दीर्घ val)
अणु
	अगर (channel == 0)
		वापस adt7411_ग_लिखो_in_vdd(dev, attr, val);
	अन्यथा
		वापस adt7411_ग_लिखो_in_chan(dev, attr, channel, val);
पूर्ण

अटल पूर्णांक adt7411_ग_लिखो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा adt7411_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक reg;

	val = clamp_val(val, -128000, 127000);
	val = DIV_ROUND_CLOSEST(val, 1000);

	चयन (attr) अणु
	हाल hwmon_temp_min:
		reg = ADT7411_REG_TEMP_LOW(channel);
		अवरोध;
	हाल hwmon_temp_max:
		reg = ADT7411_REG_TEMP_HIGH(channel);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक adt7411_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस adt7411_ग_लिखो_in(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस adt7411_ग_लिखो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t adt7411_is_visible(स्थिर व्योम *_data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा adt7411_data *data = _data;
	bool visible;

	चयन (type) अणु
	हाल hwmon_in:
		visible = channel == 0 || channel >= 3 || !data->use_ext_temp;
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_alarm:
			वापस visible ? S_IRUGO : 0;
		हाल hwmon_in_min:
		हाल hwmon_in_max:
			वापस visible ? S_IRUGO | S_IWUSR : 0;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		visible = channel == 0 || data->use_ext_temp;
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_min_alarm:
		हाल hwmon_temp_max_alarm:
		हाल hwmon_temp_fault:
			वापस visible ? S_IRUGO : 0;
		हाल hwmon_temp_min:
		हाल hwmon_temp_max:
			वापस visible ? S_IRUGO | S_IWUSR : 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adt7411_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	पूर्णांक val;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	val = i2c_smbus_पढ़ो_byte_data(client, ADT7411_REG_MANUFACTURER_ID);
	अगर (val < 0 || val != ADT7411_MANUFACTURER_ID) अणु
		dev_dbg(&client->dev,
			"Wrong manufacturer ID. Got %d, expected %d\n",
			val, ADT7411_MANUFACTURER_ID);
		वापस -ENODEV;
	पूर्ण

	val = i2c_smbus_पढ़ो_byte_data(client, ADT7411_REG_DEVICE_ID);
	अगर (val < 0 || val != ADT7411_DEVICE_ID) अणु
		dev_dbg(&client->dev,
			"Wrong device ID. Got %d, expected %d\n",
			val, ADT7411_DEVICE_ID);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "adt7411", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक adt7411_init_device(काष्ठा adt7411_data *data)
अणु
	पूर्णांक ret;
	u8 val;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, ADT7411_REG_CFG3);
	अगर (ret < 0)
		वापस ret;

	/*
	 * We must only ग_लिखो zero to bit 1 and bit 2 and only one to bit 3
	 * according to the datasheet.
	 */
	val = ret;
	val &= ~(ADT7411_CFG3_RESERVED_BIT1 | ADT7411_CFG3_RESERVED_BIT2);
	val |= ADT7411_CFG3_RESERVED_BIT3;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, ADT7411_REG_CFG3, val);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, ADT7411_REG_CFG1);
	अगर (ret < 0)
		वापस ret;

	data->use_ext_temp = ret & ADT7411_CFG1_EXT_TDM;

	/*
	 * We must only ग_लिखो zero to bit 1 and only one to bit 3 according to
	 * the datasheet.
	 */
	val = ret;
	val &= ~ADT7411_CFG1_RESERVED_BIT1;
	val |= ADT7411_CFG1_RESERVED_BIT3;

	/* enable monitoring */
	val |= ADT7411_CFG1_START_MONITOR;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, ADT7411_REG_CFG1, val);
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *adt7411_info[] = अणु
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MIN_ALARM |
			   HWMON_T_MAX | HWMON_T_MAX_ALARM,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MIN_ALARM |
			   HWMON_T_MAX | HWMON_T_MAX_ALARM | HWMON_T_FAULT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops adt7411_hwmon_ops = अणु
	.is_visible = adt7411_is_visible,
	.पढ़ो = adt7411_पढ़ो,
	.ग_लिखो = adt7411_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info adt7411_chip_info = अणु
	.ops = &adt7411_hwmon_ops,
	.info = adt7411_info,
पूर्ण;

अटल पूर्णांक adt7411_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा adt7411_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->device_lock);
	mutex_init(&data->update_lock);

	ret = adt7411_init_device(data);
	अगर (ret < 0)
		वापस ret;

	/* क्रमce update on first occasion */
	data->next_update = jअगरfies;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data,
							 &adt7411_chip_info,
							 adt7411_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adt7411_id[] = अणु
	अणु "adt7411", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adt7411_id);

अटल काष्ठा i2c_driver adt7411_driver = अणु
	.driver		= अणु
		.name		= "adt7411",
	पूर्ण,
	.probe_new = adt7411_probe,
	.id_table = adt7411_id,
	.detect = adt7411_detect,
	.address_list = normal_i2c,
	.class = I2C_CLASS_HWMON,
पूर्ण;

module_i2c_driver(adt7411_driver);

MODULE_AUTHOR("Sascha Hauer, Wolfram Sang <kernel@pengutronix.de>");
MODULE_DESCRIPTION("ADT7411 driver");
MODULE_LICENSE("GPL v2");
