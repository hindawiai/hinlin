<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * nct7802 - Driver क्रम Nuvoton NCT7802Y
 *
 * Copyright (C) 2014  Guenter Roeck <linux@roeck-us.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा DRVNAME "nct7802"

अटल स्थिर u8 REG_VOLTAGE[5] = अणु 0x09, 0x0a, 0x0c, 0x0d, 0x0e पूर्ण;

अटल स्थिर u8 REG_VOLTAGE_LIMIT_LSB[2][5] = अणु
	अणु 0x46, 0x00, 0x40, 0x42, 0x44 पूर्ण,
	अणु 0x45, 0x00, 0x3f, 0x41, 0x43 पूर्ण,
पूर्ण;

अटल स्थिर u8 REG_VOLTAGE_LIMIT_MSB[5] = अणु 0x48, 0x00, 0x47, 0x47, 0x48 पूर्ण;

अटल स्थिर u8 REG_VOLTAGE_LIMIT_MSB_SHIFT[2][5] = अणु
	अणु 0, 0, 4, 0, 4 पूर्ण,
	अणु 2, 0, 6, 2, 6 पूर्ण,
पूर्ण;

#घोषणा REG_BANK		0x00
#घोषणा REG_TEMP_LSB		0x05
#घोषणा REG_TEMP_PECI_LSB	0x08
#घोषणा REG_VOLTAGE_LOW		0x0f
#घोषणा REG_FANCOUNT_LOW	0x13
#घोषणा REG_START		0x21
#घोषणा REG_MODE		0x22 /* 7.2.32 Mode Selection Register */
#घोषणा REG_PECI_ENABLE		0x23
#घोषणा REG_FAN_ENABLE		0x24
#घोषणा REG_VMON_ENABLE		0x25
#घोषणा REG_PWM(x)		(0x60 + (x))
#घोषणा REG_SMARTFAN_EN(x)      (0x64 + (x) / 2)
#घोषणा SMARTFAN_EN_SHIFT(x)    ((x) % 2 * 4)
#घोषणा REG_VENDOR_ID		0xfd
#घोषणा REG_CHIP_ID		0xfe
#घोषणा REG_VERSION_ID		0xff

/*
 * Data काष्ठाures and manipulation thereof
 */

काष्ठा nct7802_data अणु
	काष्ठा regmap *regmap;
	काष्ठा mutex access_lock; /* क्रम multi-byte पढ़ो and ग_लिखो operations */
	u8 in_status;
	काष्ठा mutex in_alarm_lock;
पूर्ण;

अटल sमाप_प्रकार temp_type_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, REG_MODE, &mode);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", (mode >> (2 * sattr->index) & 3) + 2);
पूर्ण

अटल sमाप_प्रकार temp_type_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	अचिन्हित पूर्णांक type;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 0, &type);
	अगर (err < 0)
		वापस err;
	अगर (sattr->index == 2 && type != 4) /* RD3 */
		वापस -EINVAL;
	अगर (type < 3 || type > 4)
		वापस -EINVAL;
	err = regmap_update_bits(data->regmap, REG_MODE,
			3 << 2 * sattr->index, (type - 2) << 2 * sattr->index);
	वापस err ? : count;
पूर्ण

अटल sमाप_प्रकार pwm_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	अगर (sattr->index > 1)
		वापस प्र_लिखो(buf, "1\n");

	ret = regmap_पढ़ो(data->regmap, 0x5E, &regval);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", !(regval & (1 << sattr->index)));
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!attr->index)
		वापस प्र_लिखो(buf, "255\n");

	ret = regmap_पढ़ो(data->regmap, attr->index, &val);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक err;
	u8 val;

	err = kstrtou8(buf, 0, &val);
	अगर (err < 0)
		वापस err;

	err = regmap_ग_लिखो(data->regmap, attr->index, val);
	वापस err ? : count;
पूर्ण

अटल sमाप_प्रकार pwm_enable_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	अचिन्हित पूर्णांक reg, enabled;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, REG_SMARTFAN_EN(sattr->index), &reg);
	अगर (ret < 0)
		वापस ret;
	enabled = reg >> SMARTFAN_EN_SHIFT(sattr->index) & 1;
	वापस प्र_लिखो(buf, "%u\n", enabled + 1);
पूर्ण

अटल sमाप_प्रकार pwm_enable_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val < 1 || val > 2)
		वापस -EINVAL;
	ret = regmap_update_bits(data->regmap, REG_SMARTFAN_EN(sattr->index),
				 1 << SMARTFAN_EN_SHIFT(sattr->index),
				 (val - 1) << SMARTFAN_EN_SHIFT(sattr->index));
	वापस ret ? : count;
पूर्ण

अटल पूर्णांक nct7802_पढ़ो_temp(काष्ठा nct7802_data *data,
			     u8 reg_temp, u8 reg_temp_low, पूर्णांक *temp)
अणु
	अचिन्हित पूर्णांक t1, t2 = 0;
	पूर्णांक err;

	*temp = 0;

	mutex_lock(&data->access_lock);
	err = regmap_पढ़ो(data->regmap, reg_temp, &t1);
	अगर (err < 0)
		जाओ पात;
	t1 <<= 8;
	अगर (reg_temp_low) अणु	/* 11 bit data */
		err = regmap_पढ़ो(data->regmap, reg_temp_low, &t2);
		अगर (err < 0)
			जाओ पात;
	पूर्ण
	t1 |= t2 & 0xe0;
	*temp = (s16)t1 / 32 * 125;
पात:
	mutex_unlock(&data->access_lock);
	वापस err;
पूर्ण

अटल पूर्णांक nct7802_पढ़ो_fan(काष्ठा nct7802_data *data, u8 reg_fan)
अणु
	अचिन्हित पूर्णांक f1, f2;
	पूर्णांक ret;

	mutex_lock(&data->access_lock);
	ret = regmap_पढ़ो(data->regmap, reg_fan, &f1);
	अगर (ret < 0)
		जाओ पात;
	ret = regmap_पढ़ो(data->regmap, REG_FANCOUNT_LOW, &f2);
	अगर (ret < 0)
		जाओ पात;
	ret = (f1 << 5) | (f2 >> 3);
	/* convert fan count to rpm */
	अगर (ret == 0x1fff)	/* maximum value, assume fan is stopped */
		ret = 0;
	अन्यथा अगर (ret)
		ret = DIV_ROUND_CLOSEST(1350000U, ret);
पात:
	mutex_unlock(&data->access_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक nct7802_पढ़ो_fan_min(काष्ठा nct7802_data *data, u8 reg_fan_low,
				u8 reg_fan_high)
अणु
	अचिन्हित पूर्णांक f1, f2;
	पूर्णांक ret;

	mutex_lock(&data->access_lock);
	ret = regmap_पढ़ो(data->regmap, reg_fan_low, &f1);
	अगर (ret < 0)
		जाओ पात;
	ret = regmap_पढ़ो(data->regmap, reg_fan_high, &f2);
	अगर (ret < 0)
		जाओ पात;
	ret = f1 | ((f2 & 0xf8) << 5);
	/* convert fan count to rpm */
	अगर (ret == 0x1fff)	/* maximum value, assume no limit */
		ret = 0;
	अन्यथा अगर (ret)
		ret = DIV_ROUND_CLOSEST(1350000U, ret);
	अन्यथा
		ret = 1350000U;
पात:
	mutex_unlock(&data->access_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक nct7802_ग_लिखो_fan_min(काष्ठा nct7802_data *data, u8 reg_fan_low,
				 u8 reg_fan_high, अचिन्हित दीर्घ limit)
अणु
	पूर्णांक err;

	अगर (limit)
		limit = DIV_ROUND_CLOSEST(1350000U, limit);
	अन्यथा
		limit = 0x1fff;
	limit = clamp_val(limit, 0, 0x1fff);

	mutex_lock(&data->access_lock);
	err = regmap_ग_लिखो(data->regmap, reg_fan_low, limit & 0xff);
	अगर (err < 0)
		जाओ पात;

	err = regmap_ग_लिखो(data->regmap, reg_fan_high, (limit & 0x1f00) >> 5);
पात:
	mutex_unlock(&data->access_lock);
	वापस err;
पूर्ण

अटल u8 nct7802_vmul[] = अणु 4, 2, 2, 2, 2 पूर्ण;

अटल पूर्णांक nct7802_पढ़ो_voltage(काष्ठा nct7802_data *data, पूर्णांक nr, पूर्णांक index)
अणु
	अचिन्हित पूर्णांक v1, v2;
	पूर्णांक ret;

	mutex_lock(&data->access_lock);
	अगर (index == 0) अणु	/* voltage */
		ret = regmap_पढ़ो(data->regmap, REG_VOLTAGE[nr], &v1);
		अगर (ret < 0)
			जाओ पात;
		ret = regmap_पढ़ो(data->regmap, REG_VOLTAGE_LOW, &v2);
		अगर (ret < 0)
			जाओ पात;
		ret = ((v1 << 2) | (v2 >> 6)) * nct7802_vmul[nr];
	पूर्ण  अन्यथा अणु	/* limit */
		पूर्णांक shअगरt = 8 - REG_VOLTAGE_LIMIT_MSB_SHIFT[index - 1][nr];

		ret = regmap_पढ़ो(data->regmap,
				  REG_VOLTAGE_LIMIT_LSB[index - 1][nr], &v1);
		अगर (ret < 0)
			जाओ पात;
		ret = regmap_पढ़ो(data->regmap, REG_VOLTAGE_LIMIT_MSB[nr],
				  &v2);
		अगर (ret < 0)
			जाओ पात;
		ret = (v1 | ((v2 << shअगरt) & 0x300)) * nct7802_vmul[nr];
	पूर्ण
पात:
	mutex_unlock(&data->access_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक nct7802_ग_लिखो_voltage(काष्ठा nct7802_data *data, पूर्णांक nr, पूर्णांक index,
				 अचिन्हित दीर्घ voltage)
अणु
	पूर्णांक shअगरt = 8 - REG_VOLTAGE_LIMIT_MSB_SHIFT[index - 1][nr];
	पूर्णांक err;

	voltage = clamp_val(voltage, 0, 0x3ff * nct7802_vmul[nr]);
	voltage = DIV_ROUND_CLOSEST(voltage, nct7802_vmul[nr]);

	mutex_lock(&data->access_lock);
	err = regmap_ग_लिखो(data->regmap,
			   REG_VOLTAGE_LIMIT_LSB[index - 1][nr],
			   voltage & 0xff);
	अगर (err < 0)
		जाओ पात;

	err = regmap_update_bits(data->regmap, REG_VOLTAGE_LIMIT_MSB[nr],
				 0x0300 >> shअगरt, (voltage & 0x0300) >> shअगरt);
पात:
	mutex_unlock(&data->access_lock);
	वापस err;
पूर्ण

अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक voltage;

	voltage = nct7802_पढ़ो_voltage(data, sattr->nr, sattr->index);
	अगर (voltage < 0)
		वापस voltage;

	वापस प्र_लिखो(buf, "%d\n", voltage);
पूर्ण

अटल sमाप_प्रकार in_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक index = sattr->index;
	पूर्णांक nr = sattr->nr;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	err = nct7802_ग_लिखो_voltage(data, nr, index, val);
	वापस err ? : count;
पूर्ण

अटल sमाप_प्रकार in_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक volt, min, max, ret;
	अचिन्हित पूर्णांक val;

	mutex_lock(&data->in_alarm_lock);

	/*
	 * The SMI Voltage status रेजिस्टर is the only रेजिस्टर giving a status
	 * क्रम voltages. A bit is set क्रम each input crossing a threshold, in
	 * both direction, but the "inside" or "outside" limits info is not
	 * available. Also this रेजिस्टर is cleared on पढ़ो.
	 * Note: this is not explicitly spelled out in the datasheet, but
	 * from experiment.
	 * To deal with this we use a status cache with one validity bit and
	 * one status bit क्रम each input. Validity is cleared at startup and
	 * each समय the रेजिस्टर reports a change, and the status is processed
	 * by software based on current input value and limits.
	 */
	ret = regmap_पढ़ो(data->regmap, 0x1e, &val); /* SMI Voltage status */
	अगर (ret < 0)
		जाओ पात;

	/* invalidate cached status क्रम all inमाला_दो crossing a threshold */
	data->in_status &= ~((val & 0x0f) << 4);

	/* अगर cached status क्रम requested input is invalid, update it */
	अगर (!(data->in_status & (0x10 << sattr->index))) अणु
		ret = nct7802_पढ़ो_voltage(data, sattr->nr, 0);
		अगर (ret < 0)
			जाओ पात;
		volt = ret;

		ret = nct7802_पढ़ो_voltage(data, sattr->nr, 1);
		अगर (ret < 0)
			जाओ पात;
		min = ret;

		ret = nct7802_पढ़ो_voltage(data, sattr->nr, 2);
		अगर (ret < 0)
			जाओ पात;
		max = ret;

		अगर (volt < min || volt > max)
			data->in_status |= (1 << sattr->index);
		अन्यथा
			data->in_status &= ~(1 << sattr->index);

		data->in_status |= 0x10 << sattr->index;
	पूर्ण

	ret = प्र_लिखो(buf, "%u\n", !!(data->in_status & (1 << sattr->index)));
पात:
	mutex_unlock(&data->in_alarm_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक err, temp;

	err = nct7802_पढ़ो_temp(data, sattr->nr, sattr->index, &temp);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = sattr->nr;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	val = DIV_ROUND_CLOSEST(clamp_val(val, -128000, 127000), 1000);

	err = regmap_ग_लिखो(data->regmap, nr, val & 0xff);
	वापस err ? : count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक speed;

	speed = nct7802_पढ़ो_fan(data, sattr->index);
	अगर (speed < 0)
		वापस speed;

	वापस प्र_लिखो(buf, "%d\n", speed);
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक speed;

	speed = nct7802_पढ़ो_fan_min(data, sattr->nr, sattr->index);
	अगर (speed < 0)
		वापस speed;

	वापस प्र_लिखो(buf, "%d\n", speed);
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	err = nct7802_ग_लिखो_fan_min(data, sattr->nr, sattr->index, val);
	वापस err ? : count;
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक bit = sattr->index;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, sattr->nr, &val);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", !!(val & (1 << bit)));
पूर्ण

अटल sमाप_प्रकार
beep_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, sattr->nr, &regval);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", !!(regval & (1 << sattr->index)));
पूर्ण

अटल sमाप_प्रकार
beep_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	   माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;
	अगर (val > 1)
		वापस -EINVAL;

	err = regmap_update_bits(data->regmap, sattr->nr, 1 << sattr->index,
				 val ? 1 << sattr->index : 0);
	वापस err ? : count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_type, temp_type, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_input, temp, 0x01, REG_TEMP_LSB);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_min, temp, 0x31, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_max, temp, 0x30, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_crit, temp, 0x3a, 0);

अटल SENSOR_DEVICE_ATTR_RW(temp2_type, temp_type, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_input, temp, 0x02, REG_TEMP_LSB);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_min, temp, 0x33, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_max, temp, 0x32, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_crit, temp, 0x3b, 0);

अटल SENSOR_DEVICE_ATTR_RW(temp3_type, temp_type, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_input, temp, 0x03, REG_TEMP_LSB);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_min, temp, 0x35, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_max, temp, 0x34, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_crit, temp, 0x3c, 0);

अटल SENSOR_DEVICE_ATTR_2_RO(temp4_input, temp, 0x04, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_min, temp, 0x37, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_max, temp, 0x36, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_crit, temp, 0x3d, 0);

अटल SENSOR_DEVICE_ATTR_2_RO(temp5_input, temp, 0x06, REG_TEMP_PECI_LSB);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_min, temp, 0x39, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_max, temp, 0x38, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_crit, temp, 0x3e, 0);

अटल SENSOR_DEVICE_ATTR_2_RO(temp6_input, temp, 0x07, REG_TEMP_PECI_LSB);

अटल SENSOR_DEVICE_ATTR_2_RO(temp1_min_alarm, alarm, 0x18, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_min_alarm, alarm, 0x18, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_min_alarm, alarm, 0x18, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_min_alarm, alarm, 0x18, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(temp5_min_alarm, alarm, 0x18, 4);

अटल SENSOR_DEVICE_ATTR_2_RO(temp1_max_alarm, alarm, 0x19, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_max_alarm, alarm, 0x19, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_max_alarm, alarm, 0x19, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_max_alarm, alarm, 0x19, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(temp5_max_alarm, alarm, 0x19, 4);

अटल SENSOR_DEVICE_ATTR_2_RO(temp1_crit_alarm, alarm, 0x1b, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_crit_alarm, alarm, 0x1b, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_crit_alarm, alarm, 0x1b, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_crit_alarm, alarm, 0x1b, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(temp5_crit_alarm, alarm, 0x1b, 4);

अटल SENSOR_DEVICE_ATTR_2_RO(temp1_fault, alarm, 0x17, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_fault, alarm, 0x17, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_fault, alarm, 0x17, 2);

अटल SENSOR_DEVICE_ATTR_2_RW(temp1_beep, beep, 0x5c, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_beep, beep, 0x5c, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_beep, beep, 0x5c, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp4_beep, beep, 0x5c, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(temp5_beep, beep, 0x5c, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(temp6_beep, beep, 0x5c, 5);

अटल काष्ठा attribute *nct7802_temp_attrs[] = अणु
	&sensor_dev_attr_temp1_type.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_temp1_beep.dev_attr.attr,

	&sensor_dev_attr_temp2_type.dev_attr.attr,		/* 10 */
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_beep.dev_attr.attr,

	&sensor_dev_attr_temp3_type.dev_attr.attr,		/* 20 */
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_beep.dev_attr.attr,

	&sensor_dev_attr_temp4_input.dev_attr.attr,		/* 30 */
	&sensor_dev_attr_temp4_min.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp4_crit.dev_attr.attr,
	&sensor_dev_attr_temp4_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_beep.dev_attr.attr,

	&sensor_dev_attr_temp5_input.dev_attr.attr,		/* 38 */
	&sensor_dev_attr_temp5_min.dev_attr.attr,
	&sensor_dev_attr_temp5_max.dev_attr.attr,
	&sensor_dev_attr_temp5_crit.dev_attr.attr,
	&sensor_dev_attr_temp5_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_beep.dev_attr.attr,

	&sensor_dev_attr_temp6_input.dev_attr.attr,		/* 46 */
	&sensor_dev_attr_temp6_beep.dev_attr.attr,

	शून्य
पूर्ण;

अटल umode_t nct7802_temp_is_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, REG_MODE, &reg);
	अगर (err < 0)
		वापस 0;

	अगर (index < 10 &&
	    (reg & 03) != 0x01 && (reg & 0x03) != 0x02)		/* RD1 */
		वापस 0;

	अगर (index >= 10 && index < 20 &&
	    (reg & 0x0c) != 0x04 && (reg & 0x0c) != 0x08)	/* RD2 */
		वापस 0;
	अगर (index >= 20 && index < 30 && (reg & 0x30) != 0x20)	/* RD3 */
		वापस 0;

	अगर (index >= 30 && index < 38)				/* local */
		वापस attr->mode;

	err = regmap_पढ़ो(data->regmap, REG_PECI_ENABLE, &reg);
	अगर (err < 0)
		वापस 0;

	अगर (index >= 38 && index < 46 && !(reg & 0x01))		/* PECI 0 */
		वापस 0;

	अगर (index >= 0x46 && (!(reg & 0x02)))			/* PECI 1 */
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group nct7802_temp_group = अणु
	.attrs = nct7802_temp_attrs,
	.is_visible = nct7802_temp_is_visible,
पूर्ण;

अटल SENSOR_DEVICE_ATTR_2_RO(in0_input, in, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_min, in, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_max, in, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in0_alarm, in_alarm, 0, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_beep, beep, 0x5a, 3);

अटल SENSOR_DEVICE_ATTR_2_RO(in1_input, in, 1, 0);

अटल SENSOR_DEVICE_ATTR_2_RO(in2_input, in, 2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_min, in, 2, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_max, in, 2, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_alarm, in_alarm, 2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_beep, beep, 0x5a, 0);

अटल SENSOR_DEVICE_ATTR_2_RO(in3_input, in, 3, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_min, in, 3, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_max, in, 3, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in3_alarm, in_alarm, 3, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_beep, beep, 0x5a, 1);

अटल SENSOR_DEVICE_ATTR_2_RO(in4_input, in, 4, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_min, in, 4, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_max, in, 4, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in4_alarm, in_alarm, 4, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_beep, beep, 0x5a, 2);

अटल काष्ठा attribute *nct7802_in_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in0_beep.dev_attr.attr,

	&sensor_dev_attr_in1_input.dev_attr.attr,	/* 5 */

	&sensor_dev_attr_in2_input.dev_attr.attr,	/* 6 */
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_beep.dev_attr.attr,

	&sensor_dev_attr_in3_input.dev_attr.attr,	/* 11 */
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_beep.dev_attr.attr,

	&sensor_dev_attr_in4_input.dev_attr.attr,	/* 16 */
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_beep.dev_attr.attr,

	शून्य,
पूर्ण;

अटल umode_t nct7802_in_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;
	पूर्णांक err;

	अगर (index < 6)						/* VCC, VCORE */
		वापस attr->mode;

	err = regmap_पढ़ो(data->regmap, REG_MODE, &reg);
	अगर (err < 0)
		वापस 0;

	अगर (index >= 6 && index < 11 && (reg & 0x03) != 0x03)	/* VSEN1 */
		वापस 0;
	अगर (index >= 11 && index < 16 && (reg & 0x0c) != 0x0c)	/* VSEN2 */
		वापस 0;
	अगर (index >= 16 && (reg & 0x30) != 0x30)		/* VSEN3 */
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group nct7802_in_group = अणु
	.attrs = nct7802_in_attrs,
	.is_visible = nct7802_in_is_visible,
पूर्ण;

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0x10);
अटल SENSOR_DEVICE_ATTR_2_RW(fan1_min, fan_min, 0x49, 0x4c);
अटल SENSOR_DEVICE_ATTR_2_RO(fan1_alarm, alarm, 0x1a, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(fan1_beep, beep, 0x5b, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 0x11);
अटल SENSOR_DEVICE_ATTR_2_RW(fan2_min, fan_min, 0x4a, 0x4d);
अटल SENSOR_DEVICE_ATTR_2_RO(fan2_alarm, alarm, 0x1a, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(fan2_beep, beep, 0x5b, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan, 0x12);
अटल SENSOR_DEVICE_ATTR_2_RW(fan3_min, fan_min, 0x4b, 0x4e);
अटल SENSOR_DEVICE_ATTR_2_RO(fan3_alarm, alarm, 0x1a, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(fan3_beep, beep, 0x5b, 2);

/* 7.2.89 Fan Control Output Type */
अटल SENSOR_DEVICE_ATTR_RO(pwm1_mode, pwm_mode, 0);
अटल SENSOR_DEVICE_ATTR_RO(pwm2_mode, pwm_mode, 1);
अटल SENSOR_DEVICE_ATTR_RO(pwm3_mode, pwm_mode, 2);

/* 7.2.91... Fan Control Output Value */
अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, REG_PWM(0));
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, REG_PWM(1));
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, REG_PWM(2));

/* 7.2.95... Temperature to Fan mapping Relationships Register */
अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_enable, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_enable, pwm_enable, 2);

अटल काष्ठा attribute *nct7802_fan_attrs[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_beep.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_beep.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_beep.dev_attr.attr,

	शून्य
पूर्ण;

अटल umode_t nct7802_fan_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा nct7802_data *data = dev_get_drvdata(dev);
	पूर्णांक fan = index / 4;	/* 4 attributes per fan */
	अचिन्हित पूर्णांक reg;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, REG_FAN_ENABLE, &reg);
	अगर (err < 0 || !(reg & (1 << fan)))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group nct7802_fan_group = अणु
	.attrs = nct7802_fan_attrs,
	.is_visible = nct7802_fan_is_visible,
पूर्ण;

अटल काष्ठा attribute *nct7802_pwm_attrs[] = अणु
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_mode.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_mode.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_mode.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group nct7802_pwm_group = अणु
	.attrs = nct7802_pwm_attrs,
पूर्ण;

/* 7.2.115... 0x80-0x83, 0x84 Temperature (X-axis) transition */
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_poपूर्णांक1_temp, temp, 0x80, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_poपूर्णांक2_temp, temp, 0x81, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_poपूर्णांक3_temp, temp, 0x82, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_poपूर्णांक4_temp, temp, 0x83, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_poपूर्णांक5_temp, temp, 0x84, 0);

/* 7.2.120... 0x85-0x88 PWM (Y-axis) transition */
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक1_pwm, pwm, 0x85);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक2_pwm, pwm, 0x86);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक3_pwm, pwm, 0x87);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक4_pwm, pwm, 0x88);
अटल SENSOR_DEVICE_ATTR_RO(pwm1_स्वतः_poपूर्णांक5_pwm, pwm, 0);

/* 7.2.124 Table 2 X-axis Transition Poपूर्णांक 1 Register */
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_poपूर्णांक1_temp, temp, 0x90, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_poपूर्णांक2_temp, temp, 0x91, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_poपूर्णांक3_temp, temp, 0x92, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_poपूर्णांक4_temp, temp, 0x93, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_poपूर्णांक5_temp, temp, 0x94, 0);

/* 7.2.129 Table 2 Y-axis Transition Poपूर्णांक 1 Register */
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक1_pwm, pwm, 0x95);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक2_pwm, pwm, 0x96);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक3_pwm, pwm, 0x97);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक4_pwm, pwm, 0x98);
अटल SENSOR_DEVICE_ATTR_RO(pwm2_स्वतः_poपूर्णांक5_pwm, pwm, 0);

/* 7.2.133 Table 3 X-axis Transition Poपूर्णांक 1 Register */
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_poपूर्णांक1_temp, temp, 0xA0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_poपूर्णांक2_temp, temp, 0xA1, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_poपूर्णांक3_temp, temp, 0xA2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_poपूर्णांक4_temp, temp, 0xA3, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_poपूर्णांक5_temp, temp, 0xA4, 0);

/* 7.2.138 Table 3 Y-axis Transition Poपूर्णांक 1 Register */
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक1_pwm, pwm, 0xA5);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक2_pwm, pwm, 0xA6);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक3_pwm, pwm, 0xA7);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक4_pwm, pwm, 0xA8);
अटल SENSOR_DEVICE_ATTR_RO(pwm3_स्वतः_poपूर्णांक5_pwm, pwm, 0);

अटल काष्ठा attribute *nct7802_स्वतः_poपूर्णांक_attrs[] = अणु
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक5_temp.dev_attr.attr,

	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक5_pwm.dev_attr.attr,

	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक5_temp.dev_attr.attr,

	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक5_pwm.dev_attr.attr,

	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक4_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक5_temp.dev_attr.attr,

	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक3_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक4_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक5_pwm.dev_attr.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group nct7802_स्वतः_poपूर्णांक_group = अणु
	.attrs = nct7802_स्वतः_poपूर्णांक_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nct7802_groups[] = अणु
	&nct7802_temp_group,
	&nct7802_in_group,
	&nct7802_fan_group,
	&nct7802_pwm_group,
	&nct7802_स्वतः_poपूर्णांक_group,
	शून्य
पूर्ण;

अटल पूर्णांक nct7802_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	पूर्णांक reg;

	/*
	 * Chip identअगरication रेजिस्टरs are only available in bank 0,
	 * so only attempt chip detection अगर bank 0 is selected
	 */
	reg = i2c_smbus_पढ़ो_byte_data(client, REG_BANK);
	अगर (reg != 0x00)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, REG_VENDOR_ID);
	अगर (reg != 0x50)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, REG_CHIP_ID);
	अगर (reg != 0xc3)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, REG_VERSION_ID);
	अगर (reg < 0 || (reg & 0xf0) != 0x20)
		वापस -ENODEV;

	/* Also validate lower bits of voltage and temperature रेजिस्टरs */
	reg = i2c_smbus_पढ़ो_byte_data(client, REG_TEMP_LSB);
	अगर (reg < 0 || (reg & 0x1f))
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, REG_TEMP_PECI_LSB);
	अगर (reg < 0 || (reg & 0x3f))
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, REG_VOLTAGE_LOW);
	अगर (reg < 0 || (reg & 0x3f))
		वापस -ENODEV;

	strlcpy(info->type, "nct7802", I2C_NAME_SIZE);
	वापस 0;
पूर्ण

अटल bool nct7802_regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg != REG_BANK && reg <= 0x20) ||
		(reg >= REG_PWM(0) && reg <= REG_PWM(2));
पूर्ण

अटल स्थिर काष्ठा regmap_config nct7802_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = nct7802_regmap_is_अस्थिर,
पूर्ण;

अटल पूर्णांक nct7802_init_chip(काष्ठा nct7802_data *data)
अणु
	पूर्णांक err;

	/* Enable ADC */
	err = regmap_update_bits(data->regmap, REG_START, 0x01, 0x01);
	अगर (err)
		वापस err;

	/* Enable local temperature sensor */
	err = regmap_update_bits(data->regmap, REG_MODE, 0x40, 0x40);
	अगर (err)
		वापस err;

	/* Enable Vcore and VCC voltage monitoring */
	वापस regmap_update_bits(data->regmap, REG_VMON_ENABLE, 0x03, 0x03);
पूर्ण

अटल पूर्णांक nct7802_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा nct7802_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	data->regmap = devm_regmap_init_i2c(client, &nct7802_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	mutex_init(&data->access_lock);
	mutex_init(&data->in_alarm_lock);

	ret = nct7802_init_chip(data);
	अगर (ret < 0)
		वापस ret;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   nct7802_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर अचिन्हित लघु nct7802_address_list[] = अणु
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, I2C_CLIENT_END
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id nct7802_idtable[] = अणु
	अणु "nct7802", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nct7802_idtable);

अटल काष्ठा i2c_driver nct7802_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = DRVNAME,
	पूर्ण,
	.detect = nct7802_detect,
	.probe_new = nct7802_probe,
	.id_table = nct7802_idtable,
	.address_list = nct7802_address_list,
पूर्ण;

module_i2c_driver(nct7802_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("NCT7802Y Hardware Monitoring Driver");
MODULE_LICENSE("GPL v2");
