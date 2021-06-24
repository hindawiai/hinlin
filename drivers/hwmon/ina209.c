<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Texas Instruments / Burr Brown INA209
 * Bidirectional Current/Power Monitor
 *
 * Copyright (C) 2012 Guenter Roeck <linux@roeck-us.net>
 *
 * Derived from Ira W. Snyder's original driver submission
 *	Copyright (C) 2008 Paul Hays <Paul.Hays@cattail.ca>
 *	Copyright (C) 2008-2009 Ira W. Snyder <iws@ovro.caltech.edu>
 *
 * Aligned with ina2xx driver
 *	Copyright (C) 2012 Lothar Felten <l-felten@ti.com>
 *	Thanks to Jan Volkering
 *
 * Datasheet:
 * https://www.ti.com/lit/gpn/ina209
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/bug.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>

#समावेश <linux/platक्रमm_data/ina2xx.h>

/* रेजिस्टर definitions */
#घोषणा INA209_CONFIGURATION		0x00
#घोषणा INA209_STATUS			0x01
#घोषणा INA209_STATUS_MASK		0x02
#घोषणा INA209_SHUNT_VOLTAGE		0x03
#घोषणा INA209_BUS_VOLTAGE		0x04
#घोषणा INA209_POWER			0x05
#घोषणा INA209_CURRENT			0x06
#घोषणा INA209_SHUNT_VOLTAGE_POS_PEAK	0x07
#घोषणा INA209_SHUNT_VOLTAGE_NEG_PEAK	0x08
#घोषणा INA209_BUS_VOLTAGE_MAX_PEAK	0x09
#घोषणा INA209_BUS_VOLTAGE_MIN_PEAK	0x0a
#घोषणा INA209_POWER_PEAK		0x0b
#घोषणा INA209_SHUNT_VOLTAGE_POS_WARN	0x0c
#घोषणा INA209_SHUNT_VOLTAGE_NEG_WARN	0x0d
#घोषणा INA209_POWER_WARN		0x0e
#घोषणा INA209_BUS_VOLTAGE_OVER_WARN	0x0f
#घोषणा INA209_BUS_VOLTAGE_UNDER_WARN	0x10
#घोषणा INA209_POWER_OVER_LIMIT		0x11
#घोषणा INA209_BUS_VOLTAGE_OVER_LIMIT	0x12
#घोषणा INA209_BUS_VOLTAGE_UNDER_LIMIT	0x13
#घोषणा INA209_CRITICAL_DAC_POS		0x14
#घोषणा INA209_CRITICAL_DAC_NEG		0x15
#घोषणा INA209_CALIBRATION		0x16

#घोषणा INA209_REGISTERS		0x17

#घोषणा INA209_CONFIG_DEFAULT		0x3c47	/* PGA=8, full range */
#घोषणा INA209_SHUNT_DEFAULT		10000	/* uOhm */

काष्ठा ina209_data अणु
	काष्ठा i2c_client *client;

	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */

	u16 regs[INA209_REGISTERS];	/* All chip रेजिस्टरs */

	u16 config_orig;		/* Original configuration */
	u16 calibration_orig;		/* Original calibration */
	u16 update_पूर्णांकerval;
पूर्ण;

अटल काष्ठा ina209_data *ina209_update_device(काष्ठा device *dev)
अणु
	काष्ठा ina209_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा ina209_data *ret = data;
	s32 val;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (!data->valid ||
	    समय_after(jअगरfies, data->last_updated + data->update_पूर्णांकerval)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(data->regs); i++) अणु
			val = i2c_smbus_पढ़ो_word_swapped(client, i);
			अगर (val < 0) अणु
				ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			data->regs[i] = val;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

/*
 * Read a value from a device रेजिस्टर and convert it to the
 * appropriate sysfs units
 */
अटल दीर्घ ina209_from_reg(स्थिर u8 reg, स्थिर u16 val)
अणु
	चयन (reg) अणु
	हाल INA209_SHUNT_VOLTAGE:
	हाल INA209_SHUNT_VOLTAGE_POS_PEAK:
	हाल INA209_SHUNT_VOLTAGE_NEG_PEAK:
	हाल INA209_SHUNT_VOLTAGE_POS_WARN:
	हाल INA209_SHUNT_VOLTAGE_NEG_WARN:
		/* LSB=10 uV. Convert to mV. */
		वापस DIV_ROUND_CLOSEST((s16)val, 100);

	हाल INA209_BUS_VOLTAGE:
	हाल INA209_BUS_VOLTAGE_MAX_PEAK:
	हाल INA209_BUS_VOLTAGE_MIN_PEAK:
	हाल INA209_BUS_VOLTAGE_OVER_WARN:
	हाल INA209_BUS_VOLTAGE_UNDER_WARN:
	हाल INA209_BUS_VOLTAGE_OVER_LIMIT:
	हाल INA209_BUS_VOLTAGE_UNDER_LIMIT:
		/* LSB=4 mV, last 3 bits unused */
		वापस (val >> 3) * 4;

	हाल INA209_CRITICAL_DAC_POS:
		/* LSB=1 mV, in the upper 8 bits */
		वापस val >> 8;

	हाल INA209_CRITICAL_DAC_NEG:
		/* LSB=1 mV, in the upper 8 bits */
		वापस -1 * (val >> 8);

	हाल INA209_POWER:
	हाल INA209_POWER_PEAK:
	हाल INA209_POWER_WARN:
	हाल INA209_POWER_OVER_LIMIT:
		/* LSB=20 mW. Convert to uW */
		वापस val * 20 * 1000L;

	हाल INA209_CURRENT:
		/* LSB=1 mA (selected). Is in mA */
		वापस (s16)val;
	पूर्ण

	/* programmer goofed */
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

/*
 * Take a value and convert it to रेजिस्टर क्रमmat, clamping the value
 * to the appropriate range.
 */
अटल पूर्णांक ina209_to_reg(u8 reg, u16 old, दीर्घ val)
अणु
	चयन (reg) अणु
	हाल INA209_SHUNT_VOLTAGE_POS_WARN:
	हाल INA209_SHUNT_VOLTAGE_NEG_WARN:
		/* Limit to +- 320 mV, 10 uV LSB */
		वापस clamp_val(val, -320, 320) * 100;

	हाल INA209_BUS_VOLTAGE_OVER_WARN:
	हाल INA209_BUS_VOLTAGE_UNDER_WARN:
	हाल INA209_BUS_VOLTAGE_OVER_LIMIT:
	हाल INA209_BUS_VOLTAGE_UNDER_LIMIT:
		/*
		 * Limit to 0-32000 mV, 4 mV LSB
		 *
		 * The last three bits aren't part of the value, but we'll
		 * preserve them in their original state.
		 */
		वापस (DIV_ROUND_CLOSEST(clamp_val(val, 0, 32000), 4) << 3)
		  | (old & 0x7);

	हाल INA209_CRITICAL_DAC_NEG:
		/*
		 * Limit to -255-0 mV, 1 mV LSB
		 * Convert the value to a positive value क्रम the रेजिस्टर
		 *
		 * The value lives in the top 8 bits only, be careful
		 * and keep original value of other bits.
		 */
		वापस (clamp_val(-val, 0, 255) << 8) | (old & 0xff);

	हाल INA209_CRITICAL_DAC_POS:
		/*
		 * Limit to 0-255 mV, 1 mV LSB
		 *
		 * The value lives in the top 8 bits only, be careful
		 * and keep original value of other bits.
		 */
		वापस (clamp_val(val, 0, 255) << 8) | (old & 0xff);

	हाल INA209_POWER_WARN:
	हाल INA209_POWER_OVER_LIMIT:
		/* 20 mW LSB */
		वापस DIV_ROUND_CLOSEST(val, 20 * 1000);
	पूर्ण

	/* Other रेजिस्टरs are पढ़ो-only, वापस access error */
	वापस -EACCES;
पूर्ण

अटल पूर्णांक ina209_पूर्णांकerval_from_reg(u16 reg)
अणु
	वापस 68 >> (15 - ((reg >> 3) & 0x0f));
पूर्ण

अटल u16 ina209_reg_from_पूर्णांकerval(u16 config, दीर्घ पूर्णांकerval)
अणु
	पूर्णांक i, adc;

	अगर (पूर्णांकerval <= 0) अणु
		adc = 8;
	पूर्ण अन्यथा अणु
		adc = 15;
		क्रम (i = 34 + 34 / 2; i; i >>= 1) अणु
			अगर (i < पूर्णांकerval)
				अवरोध;
			adc--;
		पूर्ण
	पूर्ण
	वापस (config & 0xf807) | (adc << 3) | (adc << 7);
पूर्ण

अटल sमाप_प्रकार ina209_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *da,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ina209_data *data = ina209_update_device(dev);
	दीर्घ val;
	u16 regval;
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);
	regval = ina209_reg_from_पूर्णांकerval(data->regs[INA209_CONFIGURATION],
					  val);
	i2c_smbus_ग_लिखो_word_swapped(data->client, INA209_CONFIGURATION,
				     regval);
	data->regs[INA209_CONFIGURATION] = regval;
	data->update_पूर्णांकerval = ina209_पूर्णांकerval_from_reg(regval);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार ina209_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा ina209_data *data = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", data->update_पूर्णांकerval);
पूर्ण

/*
 * History is reset by writing 1 पूर्णांकo bit 0 of the respective peak रेजिस्टर.
 * Since more than one peak रेजिस्टर may be affected by the scope of a
 * reset_history attribute ग_लिखो, use a bit mask in attr->index to identअगरy
 * which रेजिस्टरs are affected.
 */
अटल u16 ina209_reset_history_regs[] = अणु
	INA209_SHUNT_VOLTAGE_POS_PEAK,
	INA209_SHUNT_VOLTAGE_NEG_PEAK,
	INA209_BUS_VOLTAGE_MAX_PEAK,
	INA209_BUS_VOLTAGE_MIN_PEAK,
	INA209_POWER_PEAK
पूर्ण;

अटल sमाप_प्रकार ina209_history_store(काष्ठा device *dev,
				    काष्ठा device_attribute *da,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ina209_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u32 mask = attr->index;
	दीर्घ val;
	पूर्णांक i, ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);
	क्रम (i = 0; i < ARRAY_SIZE(ina209_reset_history_regs); i++) अणु
		अगर (mask & (1 << i))
			i2c_smbus_ग_लिखो_word_swapped(client,
					ina209_reset_history_regs[i], 1);
	पूर्ण
	data->valid = false;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार ina209_value_store(काष्ठा device *dev,
				  काष्ठा device_attribute *da,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ina209_data *data = ina209_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक reg = attr->index;
	दीर्घ val;
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&data->update_lock);
	ret = ina209_to_reg(reg, data->regs[reg], val);
	अगर (ret < 0) अणु
		count = ret;
		जाओ पात;
	पूर्ण
	i2c_smbus_ग_लिखो_word_swapped(data->client, reg, ret);
	data->regs[reg] = ret;
पात:
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार ina209_value_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ina209_data *data = ina209_update_device(dev);
	दीर्घ val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = ina209_from_reg(attr->index, data->regs[attr->index]);
	वापस sysfs_emit(buf, "%ld\n", val);
पूर्ण

अटल sमाप_प्रकार ina209_alarm_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ina209_data *data = ina209_update_device(dev);
	स्थिर अचिन्हित पूर्णांक mask = attr->index;
	u16 status;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	status = data->regs[INA209_STATUS];

	/*
	 * All alarms are in the INA209_STATUS रेजिस्टर. To aव्योम a दीर्घ
	 * चयन statement, the mask is passed in attr->index
	 */
	वापस sysfs_emit(buf, "%u\n", !!(status & mask));
पूर्ण

/* Shunt voltage, history, limits, alarms */
अटल SENSOR_DEVICE_ATTR_RO(in0_input, ina209_value, INA209_SHUNT_VOLTAGE);
अटल SENSOR_DEVICE_ATTR_RO(in0_input_highest, ina209_value,
			     INA209_SHUNT_VOLTAGE_POS_PEAK);
अटल SENSOR_DEVICE_ATTR_RO(in0_input_lowest, ina209_value,
			     INA209_SHUNT_VOLTAGE_NEG_PEAK);
अटल SENSOR_DEVICE_ATTR_WO(in0_reset_history, ina209_history,
			     (1 << 0) | (1 << 1));
अटल SENSOR_DEVICE_ATTR_RW(in0_max, ina209_value,
			     INA209_SHUNT_VOLTAGE_POS_WARN);
अटल SENSOR_DEVICE_ATTR_RW(in0_min, ina209_value,
			     INA209_SHUNT_VOLTAGE_NEG_WARN);
अटल SENSOR_DEVICE_ATTR_RW(in0_crit_max, ina209_value,
			     INA209_CRITICAL_DAC_POS);
अटल SENSOR_DEVICE_ATTR_RW(in0_crit_min, ina209_value,
			     INA209_CRITICAL_DAC_NEG);

अटल SENSOR_DEVICE_ATTR_RO(in0_min_alarm, ina209_alarm, 1 << 11);
अटल SENSOR_DEVICE_ATTR_RO(in0_max_alarm, ina209_alarm, 1 << 12);
अटल SENSOR_DEVICE_ATTR_RO(in0_crit_min_alarm, ina209_alarm, 1 << 6);
अटल SENSOR_DEVICE_ATTR_RO(in0_crit_max_alarm, ina209_alarm, 1 << 7);

/* Bus voltage, history, limits, alarms */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ina209_value, INA209_BUS_VOLTAGE);
अटल SENSOR_DEVICE_ATTR_RO(in1_input_highest, ina209_value,
			     INA209_BUS_VOLTAGE_MAX_PEAK);
अटल SENSOR_DEVICE_ATTR_RO(in1_input_lowest, ina209_value,
			     INA209_BUS_VOLTAGE_MIN_PEAK);
अटल SENSOR_DEVICE_ATTR_WO(in1_reset_history, ina209_history,
			     (1 << 2) | (1 << 3));
अटल SENSOR_DEVICE_ATTR_RW(in1_max, ina209_value,
			     INA209_BUS_VOLTAGE_OVER_WARN);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, ina209_value,
			     INA209_BUS_VOLTAGE_UNDER_WARN);
अटल SENSOR_DEVICE_ATTR_RW(in1_crit_max, ina209_value,
			     INA209_BUS_VOLTAGE_OVER_LIMIT);
अटल SENSOR_DEVICE_ATTR_RW(in1_crit_min, ina209_value,
			     INA209_BUS_VOLTAGE_UNDER_LIMIT);

अटल SENSOR_DEVICE_ATTR_RO(in1_min_alarm, ina209_alarm, 1 << 14);
अटल SENSOR_DEVICE_ATTR_RO(in1_max_alarm, ina209_alarm, 1 << 15);
अटल SENSOR_DEVICE_ATTR_RO(in1_crit_min_alarm, ina209_alarm, 1 << 9);
अटल SENSOR_DEVICE_ATTR_RO(in1_crit_max_alarm, ina209_alarm, 1 << 10);

/* Power */
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input, ina209_value, INA209_POWER);
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input_highest, ina209_value,
			     INA209_POWER_PEAK);
अटल SENSOR_DEVICE_ATTR_WO(घातer1_reset_history, ina209_history, 1 << 4);
अटल SENSOR_DEVICE_ATTR_RW(घातer1_max, ina209_value, INA209_POWER_WARN);
अटल SENSOR_DEVICE_ATTR_RW(घातer1_crit, ina209_value,
			     INA209_POWER_OVER_LIMIT);

अटल SENSOR_DEVICE_ATTR_RO(घातer1_max_alarm, ina209_alarm, 1 << 13);
अटल SENSOR_DEVICE_ATTR_RO(घातer1_crit_alarm, ina209_alarm, 1 << 8);

/* Current */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ina209_value, INA209_CURRENT);

अटल SENSOR_DEVICE_ATTR_RW(update_पूर्णांकerval, ina209_पूर्णांकerval, 0);

/*
 * Finally, स्थिरruct an array of poपूर्णांकers to members of the above objects,
 * as required क्रम sysfs_create_group()
 */
अटल काष्ठा attribute *ina209_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_input_highest.dev_attr.attr,
	&sensor_dev_attr_in0_input_lowest.dev_attr.attr,
	&sensor_dev_attr_in0_reset_history.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_crit_max.dev_attr.attr,
	&sensor_dev_attr_in0_crit_min.dev_attr.attr,
	&sensor_dev_attr_in0_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_crit_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_crit_min_alarm.dev_attr.attr,

	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_input_highest.dev_attr.attr,
	&sensor_dev_attr_in1_input_lowest.dev_attr.attr,
	&sensor_dev_attr_in1_reset_history.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_crit_max.dev_attr.attr,
	&sensor_dev_attr_in1_crit_min.dev_attr.attr,
	&sensor_dev_attr_in1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_crit_max_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_crit_min_alarm.dev_attr.attr,

	&sensor_dev_attr_घातer1_input.dev_attr.attr,
	&sensor_dev_attr_घातer1_input_highest.dev_attr.attr,
	&sensor_dev_attr_घातer1_reset_history.dev_attr.attr,
	&sensor_dev_attr_घातer1_max.dev_attr.attr,
	&sensor_dev_attr_घातer1_crit.dev_attr.attr,
	&sensor_dev_attr_घातer1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_घातer1_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_curr1_input.dev_attr.attr,

	&sensor_dev_attr_update_पूर्णांकerval.dev_attr.attr,

	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ina209);

अटल व्योम ina209_restore_conf(काष्ठा i2c_client *client,
				काष्ठा ina209_data *data)
अणु
	/* Restore initial configuration */
	i2c_smbus_ग_लिखो_word_swapped(client, INA209_CONFIGURATION,
				     data->config_orig);
	i2c_smbus_ग_लिखो_word_swapped(client, INA209_CALIBRATION,
				     data->calibration_orig);
पूर्ण

अटल पूर्णांक ina209_init_client(काष्ठा i2c_client *client,
			      काष्ठा ina209_data *data)
अणु
	काष्ठा ina2xx_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	u32 shunt;
	पूर्णांक reg;

	reg = i2c_smbus_पढ़ो_word_swapped(client, INA209_CALIBRATION);
	अगर (reg < 0)
		वापस reg;
	data->calibration_orig = reg;

	reg = i2c_smbus_पढ़ो_word_swapped(client, INA209_CONFIGURATION);
	अगर (reg < 0)
		वापस reg;
	data->config_orig = reg;

	अगर (pdata) अणु
		अगर (pdata->shunt_uohms <= 0)
			वापस -EINVAL;
		shunt = pdata->shunt_uohms;
	पूर्ण अन्यथा अगर (!of_property_पढ़ो_u32(client->dev.of_node, "shunt-resistor",
					 &shunt)) अणु
		अगर (shunt == 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		shunt = data->calibration_orig ?
		  40960000 / data->calibration_orig : INA209_SHUNT_DEFAULT;
	पूर्ण

	i2c_smbus_ग_लिखो_word_swapped(client, INA209_CONFIGURATION,
				     INA209_CONFIG_DEFAULT);
	data->update_पूर्णांकerval = ina209_पूर्णांकerval_from_reg(INA209_CONFIG_DEFAULT);

	/*
	 * Calibrate current LSB to 1mA. Shunt is in uOhms.
	 * See equation 13 in datasheet.
	 */
	i2c_smbus_ग_लिखो_word_swapped(client, INA209_CALIBRATION,
				     clamp_val(40960000 / shunt, 1, 65535));

	/* Clear status रेजिस्टर */
	i2c_smbus_पढ़ो_word_swapped(client, INA209_STATUS);

	वापस 0;
पूर्ण

अटल पूर्णांक ina209_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा ina209_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	ret = ina209_init_client(client, data);
	अगर (ret)
		वापस ret;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   client->name,
							   data, ina209_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		ret = PTR_ERR(hwmon_dev);
		जाओ out_restore_conf;
	पूर्ण

	वापस 0;

out_restore_conf:
	ina209_restore_conf(client, data);
	वापस ret;
पूर्ण

अटल पूर्णांक ina209_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ina209_data *data = i2c_get_clientdata(client);

	ina209_restore_conf(client, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ina209_id[] = अणु
	अणु "ina209", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ina209_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ina209_of_match[] = अणु
	अणु .compatible = "ti,ina209" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ina209_of_match);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ina209_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "ina209",
		.of_match_table = of_match_ptr(ina209_of_match),
	पूर्ण,
	.probe_new	= ina209_probe,
	.हटाओ		= ina209_हटाओ,
	.id_table	= ina209_id,
पूर्ण;

module_i2c_driver(ina209_driver);

MODULE_AUTHOR("Ira W. Snyder <iws@ovro.caltech.edu>, Paul Hays <Paul.Hays@cattail.ca>, Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("INA209 driver");
MODULE_LICENSE("GPL");
