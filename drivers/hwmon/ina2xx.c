<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Texas Instruments INA219, INA226 घातer monitor chips
 *
 * INA219:
 * Zero Drअगरt Bi-Directional Current/Power Monitor with I2C Interface
 * Datasheet: https://www.ti.com/product/ina219
 *
 * INA220:
 * Bi-Directional Current/Power Monitor with I2C Interface
 * Datasheet: https://www.ti.com/product/ina220
 *
 * INA226:
 * Bi-Directional Current/Power Monitor with I2C Interface
 * Datasheet: https://www.ti.com/product/ina226
 *
 * INA230:
 * Bi-directional Current/Power Monitor with I2C Interface
 * Datasheet: https://www.ti.com/product/ina230
 *
 * Copyright (C) 2012 Lothar Felten <lothar.felten@gmail.com>
 * Thanks to Jan Volkering
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/util_macros.h>
#समावेश <linux/regmap.h>

#समावेश <linux/platक्रमm_data/ina2xx.h>

/* common रेजिस्टर definitions */
#घोषणा INA2XX_CONFIG			0x00
#घोषणा INA2XX_SHUNT_VOLTAGE		0x01 /* पढ़ोonly */
#घोषणा INA2XX_BUS_VOLTAGE		0x02 /* पढ़ोonly */
#घोषणा INA2XX_POWER			0x03 /* पढ़ोonly */
#घोषणा INA2XX_CURRENT			0x04 /* पढ़ोonly */
#घोषणा INA2XX_CALIBRATION		0x05

/* INA226 रेजिस्टर definitions */
#घोषणा INA226_MASK_ENABLE		0x06
#घोषणा INA226_ALERT_LIMIT		0x07
#घोषणा INA226_DIE_ID			0xFF

/* रेजिस्टर count */
#घोषणा INA219_REGISTERS		6
#घोषणा INA226_REGISTERS		8

#घोषणा INA2XX_MAX_REGISTERS		8

/* settings - depend on use हाल */
#घोषणा INA219_CONFIG_DEFAULT		0x399F	/* PGA=8 */
#घोषणा INA226_CONFIG_DEFAULT		0x4527	/* averages=16 */

/* worst हाल is 68.10 ms (~14.6Hz, ina219) */
#घोषणा INA2XX_CONVERSION_RATE		15
#घोषणा INA2XX_MAX_DELAY		69 /* worst हाल delay in ms */

#घोषणा INA2XX_RSHUNT_DEFAULT		10000

/* bit mask क्रम पढ़ोing the averaging setting in the configuration रेजिस्टर */
#घोषणा INA226_AVG_RD_MASK		0x0E00

#घोषणा INA226_READ_AVG(reg)		(((reg) & INA226_AVG_RD_MASK) >> 9)
#घोषणा INA226_SHIFT_AVG(val)		((val) << 9)

/* bit number of alert functions in Mask/Enable Register */
#घोषणा INA226_SHUNT_OVER_VOLTAGE_BIT	15
#घोषणा INA226_SHUNT_UNDER_VOLTAGE_BIT	14
#घोषणा INA226_BUS_OVER_VOLTAGE_BIT	13
#घोषणा INA226_BUS_UNDER_VOLTAGE_BIT	12
#घोषणा INA226_POWER_OVER_LIMIT_BIT	11

/* bit mask क्रम alert config bits of Mask/Enable Register */
#घोषणा INA226_ALERT_CONFIG_MASK	0xFC00
#घोषणा INA226_ALERT_FUNCTION_FLAG	BIT(4)

/* common attrs, ina226 attrs and शून्य */
#घोषणा INA2XX_MAX_ATTRIBUTE_GROUPS	3

/*
 * Both bus voltage and shunt voltage conversion बार क्रम ina226 are set
 * to 0b0100 on POR, which translates to 2200 microseconds in total.
 */
#घोषणा INA226_TOTAL_CONV_TIME_DEFAULT	2200

अटल काष्ठा regmap_config ina2xx_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
पूर्ण;

क्रमागत ina2xx_ids अणु ina219, ina226 पूर्ण;

काष्ठा ina2xx_config अणु
	u16 config_शेष;
	पूर्णांक calibration_value;
	पूर्णांक रेजिस्टरs;
	पूर्णांक shunt_भाग;
	पूर्णांक bus_voltage_shअगरt;
	पूर्णांक bus_voltage_lsb;	/* uV */
	पूर्णांक घातer_lsb_factor;
पूर्ण;

काष्ठा ina2xx_data अणु
	स्थिर काष्ठा ina2xx_config *config;

	दीर्घ rshunt;
	दीर्घ current_lsb_uA;
	दीर्घ घातer_lsb_uW;
	काष्ठा mutex config_lock;
	काष्ठा regmap *regmap;

	स्थिर काष्ठा attribute_group *groups[INA2XX_MAX_ATTRIBUTE_GROUPS];
पूर्ण;

अटल स्थिर काष्ठा ina2xx_config ina2xx_config[] = अणु
	[ina219] = अणु
		.config_शेष = INA219_CONFIG_DEFAULT,
		.calibration_value = 4096,
		.रेजिस्टरs = INA219_REGISTERS,
		.shunt_भाग = 100,
		.bus_voltage_shअगरt = 3,
		.bus_voltage_lsb = 4000,
		.घातer_lsb_factor = 20,
	पूर्ण,
	[ina226] = अणु
		.config_शेष = INA226_CONFIG_DEFAULT,
		.calibration_value = 2048,
		.रेजिस्टरs = INA226_REGISTERS,
		.shunt_भाग = 400,
		.bus_voltage_shअगरt = 0,
		.bus_voltage_lsb = 1250,
		.घातer_lsb_factor = 25,
	पूर्ण,
पूर्ण;

/*
 * Available averaging rates क्रम ina226. The indices correspond with
 * the bit values expected by the chip (according to the ina226 datasheet,
 * table 3 AVG bit settings, found at
 * https://www.ti.com/lit/ds/symlink/ina226.pdf.
 */
अटल स्थिर पूर्णांक ina226_avg_tab[] = अणु 1, 4, 16, 64, 128, 256, 512, 1024 पूर्ण;

अटल पूर्णांक ina226_reg_to_पूर्णांकerval(u16 config)
अणु
	पूर्णांक avg = ina226_avg_tab[INA226_READ_AVG(config)];

	/*
	 * Multiply the total conversion समय by the number of averages.
	 * Return the result in milliseconds.
	 */
	वापस DIV_ROUND_CLOSEST(avg * INA226_TOTAL_CONV_TIME_DEFAULT, 1000);
पूर्ण

/*
 * Return the new, shअगरted AVG field value of CONFIG रेजिस्टर,
 * to use with regmap_update_bits
 */
अटल u16 ina226_पूर्णांकerval_to_reg(पूर्णांक पूर्णांकerval)
अणु
	पूर्णांक avg, avg_bits;

	avg = DIV_ROUND_CLOSEST(पूर्णांकerval * 1000,
				INA226_TOTAL_CONV_TIME_DEFAULT);
	avg_bits = find_बंदst(avg, ina226_avg_tab,
				ARRAY_SIZE(ina226_avg_tab));

	वापस INA226_SHIFT_AVG(avg_bits);
पूर्ण

/*
 * Calibration रेजिस्टर is set to the best value, which eliminates
 * truncation errors on calculating current रेजिस्टर in hardware.
 * According to datasheet (eq. 3) the best values are 2048 क्रम
 * ina226 and 4096 क्रम ina219. They are hardcoded as calibration_value.
 */
अटल पूर्णांक ina2xx_calibrate(काष्ठा ina2xx_data *data)
अणु
	वापस regmap_ग_लिखो(data->regmap, INA2XX_CALIBRATION,
			    data->config->calibration_value);
पूर्ण

/*
 * Initialize the configuration and calibration रेजिस्टरs.
 */
अटल पूर्णांक ina2xx_init(काष्ठा ina2xx_data *data)
अणु
	पूर्णांक ret = regmap_ग_लिखो(data->regmap, INA2XX_CONFIG,
			       data->config->config_शेष);
	अगर (ret < 0)
		वापस ret;

	वापस ina2xx_calibrate(data);
पूर्ण

अटल पूर्णांक ina2xx_पढ़ो_reg(काष्ठा device *dev, पूर्णांक reg, अचिन्हित पूर्णांक *regval)
अणु
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret, retry;

	dev_dbg(dev, "Starting register %d read\n", reg);

	क्रम (retry = 5; retry; retry--) अणु

		ret = regmap_पढ़ो(data->regmap, reg, regval);
		अगर (ret < 0)
			वापस ret;

		dev_dbg(dev, "read %d, val = 0x%04x\n", reg, *regval);

		/*
		 * If the current value in the calibration रेजिस्टर is 0, the
		 * घातer and current रेजिस्टरs will also reमुख्य at 0. In हाल
		 * the chip has been reset let's check the calibration
		 * रेजिस्टर and reinitialize अगर needed.
		 * We करो that extra पढ़ो of the calibration रेजिस्टर अगर there
		 * is some hपूर्णांक of a chip reset.
		 */
		अगर (*regval == 0) अणु
			अचिन्हित पूर्णांक cal;

			ret = regmap_पढ़ो(data->regmap, INA2XX_CALIBRATION,
					  &cal);
			अगर (ret < 0)
				वापस ret;

			अगर (cal == 0) अणु
				dev_warn(dev, "chip not calibrated, reinitializing\n");

				ret = ina2xx_init(data);
				अगर (ret < 0)
					वापस ret;
				/*
				 * Let's make sure the घातer and current
				 * रेजिस्टरs have been updated beक्रमe trying
				 * again.
				 */
				msleep(INA2XX_MAX_DELAY);
				जारी;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * If we're here then although all ग_लिखो operations succeeded, the
	 * chip still वापसs 0 in the calibration रेजिस्टर. Nothing more we
	 * can करो here.
	 */
	dev_err(dev, "unable to reinitialize the chip\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ina2xx_get_value(काष्ठा ina2xx_data *data, u8 reg,
			    अचिन्हित पूर्णांक regval)
अणु
	पूर्णांक val;

	चयन (reg) अणु
	हाल INA2XX_SHUNT_VOLTAGE:
		/* चिन्हित रेजिस्टर */
		val = DIV_ROUND_CLOSEST((s16)regval, data->config->shunt_भाग);
		अवरोध;
	हाल INA2XX_BUS_VOLTAGE:
		val = (regval >> data->config->bus_voltage_shअगरt)
		  * data->config->bus_voltage_lsb;
		val = DIV_ROUND_CLOSEST(val, 1000);
		अवरोध;
	हाल INA2XX_POWER:
		val = regval * data->घातer_lsb_uW;
		अवरोध;
	हाल INA2XX_CURRENT:
		/* चिन्हित रेजिस्टर, result in mA */
		val = (s16)regval * data->current_lsb_uA;
		val = DIV_ROUND_CLOSEST(val, 1000);
		अवरोध;
	हाल INA2XX_CALIBRATION:
		val = regval;
		अवरोध;
	शेष:
		/* programmer goofed */
		WARN_ON_ONCE(1);
		val = 0;
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल sमाप_प्रकार ina2xx_value_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;

	पूर्णांक err = ina2xx_पढ़ो_reg(dev, attr->index, &regval);

	अगर (err < 0)
		वापस err;

	वापस sysfs_emit(buf, "%d\n", ina2xx_get_value(data, attr->index, regval));
पूर्ण

अटल पूर्णांक ina226_reg_to_alert(काष्ठा ina2xx_data *data, u8 bit, u16 regval)
अणु
	पूर्णांक reg;

	चयन (bit) अणु
	हाल INA226_SHUNT_OVER_VOLTAGE_BIT:
	हाल INA226_SHUNT_UNDER_VOLTAGE_BIT:
		reg = INA2XX_SHUNT_VOLTAGE;
		अवरोध;
	हाल INA226_BUS_OVER_VOLTAGE_BIT:
	हाल INA226_BUS_UNDER_VOLTAGE_BIT:
		reg = INA2XX_BUS_VOLTAGE;
		अवरोध;
	हाल INA226_POWER_OVER_LIMIT_BIT:
		reg = INA2XX_POWER;
		अवरोध;
	शेष:
		/* programmer goofed */
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	वापस ina2xx_get_value(data, reg, regval);
पूर्ण

/*
 * Turns alert limit values पूर्णांकo रेजिस्टर values.
 * Opposite of the क्रमmula in ina2xx_get_value().
 */
अटल s16 ina226_alert_to_reg(काष्ठा ina2xx_data *data, u8 bit, पूर्णांक val)
अणु
	चयन (bit) अणु
	हाल INA226_SHUNT_OVER_VOLTAGE_BIT:
	हाल INA226_SHUNT_UNDER_VOLTAGE_BIT:
		val *= data->config->shunt_भाग;
		वापस clamp_val(val, लघु_न्यून, लघु_उच्च);
	हाल INA226_BUS_OVER_VOLTAGE_BIT:
	हाल INA226_BUS_UNDER_VOLTAGE_BIT:
		val = (val * 1000) << data->config->bus_voltage_shअगरt;
		val = DIV_ROUND_CLOSEST(val, data->config->bus_voltage_lsb);
		वापस clamp_val(val, 0, लघु_उच्च);
	हाल INA226_POWER_OVER_LIMIT_BIT:
		val = DIV_ROUND_CLOSEST(val, data->घातer_lsb_uW);
		वापस clamp_val(val, 0, अच_लघु_उच्च);
	शेष:
		/* programmer goofed */
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ina226_alert_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);
	पूर्णांक regval;
	पूर्णांक val = 0;
	पूर्णांक ret;

	mutex_lock(&data->config_lock);
	ret = regmap_पढ़ो(data->regmap, INA226_MASK_ENABLE, &regval);
	अगर (ret)
		जाओ पात;

	अगर (regval & BIT(attr->index)) अणु
		ret = regmap_पढ़ो(data->regmap, INA226_ALERT_LIMIT, &regval);
		अगर (ret)
			जाओ पात;
		val = ina226_reg_to_alert(data, attr->index, regval);
	पूर्ण

	ret = sysfs_emit(buf, "%d\n", val);
पात:
	mutex_unlock(&data->config_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ina226_alert_store(काष्ठा device *dev,
				  काष्ठा device_attribute *da,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Clear all alerts first to aव्योम accidentally triggering ALERT pin
	 * due to रेजिस्टर ग_लिखो sequence. Then, only enable the alert
	 * अगर the value is non-zero.
	 */
	mutex_lock(&data->config_lock);
	ret = regmap_update_bits(data->regmap, INA226_MASK_ENABLE,
				 INA226_ALERT_CONFIG_MASK, 0);
	अगर (ret < 0)
		जाओ पात;

	ret = regmap_ग_लिखो(data->regmap, INA226_ALERT_LIMIT,
			   ina226_alert_to_reg(data, attr->index, val));
	अगर (ret < 0)
		जाओ पात;

	अगर (val != 0) अणु
		ret = regmap_update_bits(data->regmap, INA226_MASK_ENABLE,
					 INA226_ALERT_CONFIG_MASK,
					 BIT(attr->index));
		अगर (ret < 0)
			जाओ पात;
	पूर्ण

	ret = count;
पात:
	mutex_unlock(&data->config_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ina226_alarm_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);
	पूर्णांक regval;
	पूर्णांक alarm = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, INA226_MASK_ENABLE, &regval);
	अगर (ret)
		वापस ret;

	alarm = (regval & BIT(attr->index)) &&
		(regval & INA226_ALERT_FUNCTION_FLAG);
	वापस sysfs_emit(buf, "%d\n", alarm);
पूर्ण

/*
 * In order to keep calibration रेजिस्टर value fixed, the product
 * of current_lsb and shunt_resistor should also be fixed and equal
 * to shunt_voltage_lsb = 1 / shunt_भाग multiplied by 10^9 in order
 * to keep the scale.
 */
अटल पूर्णांक ina2xx_set_shunt(काष्ठा ina2xx_data *data, दीर्घ val)
अणु
	अचिन्हित पूर्णांक भागidend = DIV_ROUND_CLOSEST(1000000000,
						  data->config->shunt_भाग);
	अगर (val <= 0 || val > भागidend)
		वापस -EINVAL;

	mutex_lock(&data->config_lock);
	data->rshunt = val;
	data->current_lsb_uA = DIV_ROUND_CLOSEST(भागidend, val);
	data->घातer_lsb_uW = data->config->घातer_lsb_factor *
			     data->current_lsb_uA;
	mutex_unlock(&data->config_lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ina2xx_shunt_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%li\n", data->rshunt);
पूर्ण

अटल sमाप_प्रकार ina2xx_shunt_store(काष्ठा device *dev,
				  काष्ठा device_attribute *da,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक status;
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);

	status = kम_से_अदीर्घ(buf, 10, &val);
	अगर (status < 0)
		वापस status;

	status = ina2xx_set_shunt(data, val);
	अगर (status < 0)
		वापस status;
	वापस count;
पूर्ण

अटल sमाप_प्रकार ina226_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *da,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक status;

	status = kम_से_अदीर्घ(buf, 10, &val);
	अगर (status < 0)
		वापस status;

	अगर (val > पूर्णांक_उच्च || val == 0)
		वापस -EINVAL;

	status = regmap_update_bits(data->regmap, INA2XX_CONFIG,
				    INA226_AVG_RD_MASK,
				    ina226_पूर्णांकerval_to_reg(val));
	अगर (status < 0)
		वापस status;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ina226_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा ina2xx_data *data = dev_get_drvdata(dev);
	पूर्णांक status;
	अचिन्हित पूर्णांक regval;

	status = regmap_पढ़ो(data->regmap, INA2XX_CONFIG, &regval);
	अगर (status)
		वापस status;

	वापस sysfs_emit(buf, "%d\n", ina226_reg_to_पूर्णांकerval(regval));
पूर्ण

/* shunt voltage */
अटल SENSOR_DEVICE_ATTR_RO(in0_input, ina2xx_value, INA2XX_SHUNT_VOLTAGE);
/* shunt voltage over/under voltage alert setting and alarm */
अटल SENSOR_DEVICE_ATTR_RW(in0_crit, ina226_alert,
			     INA226_SHUNT_OVER_VOLTAGE_BIT);
अटल SENSOR_DEVICE_ATTR_RW(in0_lcrit, ina226_alert,
			     INA226_SHUNT_UNDER_VOLTAGE_BIT);
अटल SENSOR_DEVICE_ATTR_RO(in0_crit_alarm, ina226_alarm,
			     INA226_SHUNT_OVER_VOLTAGE_BIT);
अटल SENSOR_DEVICE_ATTR_RO(in0_lcrit_alarm, ina226_alarm,
			     INA226_SHUNT_UNDER_VOLTAGE_BIT);

/* bus voltage */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ina2xx_value, INA2XX_BUS_VOLTAGE);
/* bus voltage over/under voltage alert setting and alarm */
अटल SENSOR_DEVICE_ATTR_RW(in1_crit, ina226_alert,
			     INA226_BUS_OVER_VOLTAGE_BIT);
अटल SENSOR_DEVICE_ATTR_RW(in1_lcrit, ina226_alert,
			     INA226_BUS_UNDER_VOLTAGE_BIT);
अटल SENSOR_DEVICE_ATTR_RO(in1_crit_alarm, ina226_alarm,
			     INA226_BUS_OVER_VOLTAGE_BIT);
अटल SENSOR_DEVICE_ATTR_RO(in1_lcrit_alarm, ina226_alarm,
			     INA226_BUS_UNDER_VOLTAGE_BIT);

/* calculated current */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ina2xx_value, INA2XX_CURRENT);

/* calculated घातer */
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input, ina2xx_value, INA2XX_POWER);
/* over-limit घातer alert setting and alarm */
अटल SENSOR_DEVICE_ATTR_RW(घातer1_crit, ina226_alert,
			     INA226_POWER_OVER_LIMIT_BIT);
अटल SENSOR_DEVICE_ATTR_RO(घातer1_crit_alarm, ina226_alarm,
			     INA226_POWER_OVER_LIMIT_BIT);

/* shunt resistance */
अटल SENSOR_DEVICE_ATTR_RW(shunt_resistor, ina2xx_shunt, INA2XX_CALIBRATION);

/* update पूर्णांकerval (ina226 only) */
अटल SENSOR_DEVICE_ATTR_RW(update_पूर्णांकerval, ina226_पूर्णांकerval, 0);

/* poपूर्णांकers to created device attributes */
अटल काष्ठा attribute *ina2xx_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_घातer1_input.dev_attr.attr,
	&sensor_dev_attr_shunt_resistor.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ina2xx_group = अणु
	.attrs = ina2xx_attrs,
पूर्ण;

अटल काष्ठा attribute *ina226_attrs[] = अणु
	&sensor_dev_attr_in0_crit.dev_attr.attr,
	&sensor_dev_attr_in0_lcrit.dev_attr.attr,
	&sensor_dev_attr_in0_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_lcrit_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_crit.dev_attr.attr,
	&sensor_dev_attr_in1_lcrit.dev_attr.attr,
	&sensor_dev_attr_in1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_lcrit_alarm.dev_attr.attr,
	&sensor_dev_attr_घातer1_crit.dev_attr.attr,
	&sensor_dev_attr_घातer1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_update_पूर्णांकerval.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ina226_group = अणु
	.attrs = ina226_attrs,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ina2xx_id[];

अटल पूर्णांक ina2xx_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ina2xx_data *data;
	काष्ठा device *hwmon_dev;
	u32 val;
	पूर्णांक ret, group = 0;
	क्रमागत ina2xx_ids chip;

	अगर (client->dev.of_node)
		chip = (क्रमागत ina2xx_ids)of_device_get_match_data(&client->dev);
	अन्यथा
		chip = i2c_match_id(ina2xx_id, client)->driver_data;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* set the device type */
	data->config = &ina2xx_config[chip];
	mutex_init(&data->config_lock);

	अगर (of_property_पढ़ो_u32(dev->of_node, "shunt-resistor", &val) < 0) अणु
		काष्ठा ina2xx_platक्रमm_data *pdata = dev_get_platdata(dev);

		अगर (pdata)
			val = pdata->shunt_uohms;
		अन्यथा
			val = INA2XX_RSHUNT_DEFAULT;
	पूर्ण

	ina2xx_set_shunt(data, val);

	ina2xx_regmap_config.max_रेजिस्टर = data->config->रेजिस्टरs;

	data->regmap = devm_regmap_init_i2c(client, &ina2xx_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	ret = ina2xx_init(data);
	अगर (ret < 0) अणु
		dev_err(dev, "error configuring the device: %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	data->groups[group++] = &ina2xx_group;
	अगर (chip == ina226)
		data->groups[group++] = &ina226_group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(dev, "power monitor %s (Rshunt = %li uOhm)\n",
		 client->name, data->rshunt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ina2xx_id[] = अणु
	अणु "ina219", ina219 पूर्ण,
	अणु "ina220", ina219 पूर्ण,
	अणु "ina226", ina226 पूर्ण,
	अणु "ina230", ina226 पूर्ण,
	अणु "ina231", ina226 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ina2xx_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ina2xx_of_match[] = अणु
	अणु
		.compatible = "ti,ina219",
		.data = (व्योम *)ina219
	पूर्ण,
	अणु
		.compatible = "ti,ina220",
		.data = (व्योम *)ina219
	पूर्ण,
	अणु
		.compatible = "ti,ina226",
		.data = (व्योम *)ina226
	पूर्ण,
	अणु
		.compatible = "ti,ina230",
		.data = (व्योम *)ina226
	पूर्ण,
	अणु
		.compatible = "ti,ina231",
		.data = (व्योम *)ina226
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ina2xx_of_match);

अटल काष्ठा i2c_driver ina2xx_driver = अणु
	.driver = अणु
		.name	= "ina2xx",
		.of_match_table = of_match_ptr(ina2xx_of_match),
	पूर्ण,
	.probe_new	= ina2xx_probe,
	.id_table	= ina2xx_id,
पूर्ण;

module_i2c_driver(ina2xx_driver);

MODULE_AUTHOR("Lothar Felten <l-felten@ti.com>");
MODULE_DESCRIPTION("ina2xx driver");
MODULE_LICENSE("GPL");
