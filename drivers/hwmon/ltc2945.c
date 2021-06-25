<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Linear Technology LTC2945 I2C Power Monitor
 *
 * Copyright (c) 2014 Guenter Roeck
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/regmap.h>

/* chip रेजिस्टरs */
#घोषणा LTC2945_CONTROL			0x00
#घोषणा LTC2945_ALERT			0x01
#घोषणा LTC2945_STATUS			0x02
#घोषणा LTC2945_FAULT			0x03
#घोषणा LTC2945_POWER_H			0x05
#घोषणा LTC2945_MAX_POWER_H		0x08
#घोषणा LTC2945_MIN_POWER_H		0x0b
#घोषणा LTC2945_MAX_POWER_THRES_H	0x0e
#घोषणा LTC2945_MIN_POWER_THRES_H	0x11
#घोषणा LTC2945_SENSE_H			0x14
#घोषणा LTC2945_MAX_SENSE_H		0x16
#घोषणा LTC2945_MIN_SENSE_H		0x18
#घोषणा LTC2945_MAX_SENSE_THRES_H	0x1a
#घोषणा LTC2945_MIN_SENSE_THRES_H	0x1c
#घोषणा LTC2945_VIN_H			0x1e
#घोषणा LTC2945_MAX_VIN_H		0x20
#घोषणा LTC2945_MIN_VIN_H		0x22
#घोषणा LTC2945_MAX_VIN_THRES_H		0x24
#घोषणा LTC2945_MIN_VIN_THRES_H		0x26
#घोषणा LTC2945_ADIN_H			0x28
#घोषणा LTC2945_MAX_ADIN_H		0x2a
#घोषणा LTC2945_MIN_ADIN_H		0x2c
#घोषणा LTC2945_MAX_ADIN_THRES_H	0x2e
#घोषणा LTC2945_MIN_ADIN_THRES_H	0x30
#घोषणा LTC2945_MIN_ADIN_THRES_L	0x31

/* Fault रेजिस्टर bits */

#घोषणा FAULT_ADIN_UV		(1 << 0)
#घोषणा FAULT_ADIN_OV		(1 << 1)
#घोषणा FAULT_VIN_UV		(1 << 2)
#घोषणा FAULT_VIN_OV		(1 << 3)
#घोषणा FAULT_SENSE_UV		(1 << 4)
#घोषणा FAULT_SENSE_OV		(1 << 5)
#घोषणा FAULT_POWER_UV		(1 << 6)
#घोषणा FAULT_POWER_OV		(1 << 7)

/* Control रेजिस्टर bits */

#घोषणा CONTROL_MULT_SELECT	(1 << 0)
#घोषणा CONTROL_TEST_MODE	(1 << 4)

अटल अंतरभूत bool is_घातer_reg(u8 reg)
अणु
	वापस reg < LTC2945_SENSE_H;
पूर्ण

/* Return the value from the given रेजिस्टर in uW, mV, or mA */
अटल दीर्घ दीर्घ ltc2945_reg_to_val(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक control;
	u8 buf[3];
	दीर्घ दीर्घ val;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(regmap, reg, buf,
			       is_घातer_reg(reg) ? 3 : 2);
	अगर (ret < 0)
		वापस ret;

	अगर (is_घातer_reg(reg)) अणु
		/* घातer */
		val = (buf[0] << 16) + (buf[1] << 8) + buf[2];
	पूर्ण अन्यथा अणु
		/* current, voltage */
		val = (buf[0] << 4) + (buf[1] >> 4);
	पूर्ण

	चयन (reg) अणु
	हाल LTC2945_POWER_H:
	हाल LTC2945_MAX_POWER_H:
	हाल LTC2945_MIN_POWER_H:
	हाल LTC2945_MAX_POWER_THRES_H:
	हाल LTC2945_MIN_POWER_THRES_H:
		/*
		 * Convert to uW by assuming current is measured with
		 * an 1mOhm sense resistor, similar to current
		 * measurements.
		 * Control रेजिस्टर bit 0 selects अगर voltage at SENSE+/VDD
		 * or voltage at ADIN is used to measure घातer.
		 */
		ret = regmap_पढ़ो(regmap, LTC2945_CONTROL, &control);
		अगर (ret < 0)
			वापस ret;
		अगर (control & CONTROL_MULT_SELECT) अणु
			/* 25 mV * 25 uV = 0.625 uV resolution. */
			val *= 625LL;
		पूर्ण अन्यथा अणु
			/* 0.5 mV * 25 uV = 0.0125 uV resolution. */
			val = (val * 25LL) >> 1;
		पूर्ण
		अवरोध;
	हाल LTC2945_VIN_H:
	हाल LTC2945_MAX_VIN_H:
	हाल LTC2945_MIN_VIN_H:
	हाल LTC2945_MAX_VIN_THRES_H:
	हाल LTC2945_MIN_VIN_THRES_H:
		/* 25 mV resolution. Convert to mV. */
		val *= 25;
		अवरोध;
	हाल LTC2945_ADIN_H:
	हाल LTC2945_MAX_ADIN_H:
	हाल LTC2945_MIN_ADIN_THRES_H:
	हाल LTC2945_MAX_ADIN_THRES_H:
	हाल LTC2945_MIN_ADIN_H:
		/* 0.5mV resolution. Convert to mV. */
		val = val >> 1;
		अवरोध;
	हाल LTC2945_SENSE_H:
	हाल LTC2945_MAX_SENSE_H:
	हाल LTC2945_MIN_SENSE_H:
	हाल LTC2945_MAX_SENSE_THRES_H:
	हाल LTC2945_MIN_SENSE_THRES_H:
		/*
		 * 25 uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a dअगरferent sense
		 * resistor is installed, calculate the actual current by
		 * भागiding the reported current by the sense resistor value
		 * in mOhm.
		 */
		val *= 25;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक ltc2945_val_to_reg(काष्ठा device *dev, u8 reg,
			      अचिन्हित दीर्घ val)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक control;
	पूर्णांक ret;

	चयन (reg) अणु
	हाल LTC2945_POWER_H:
	हाल LTC2945_MAX_POWER_H:
	हाल LTC2945_MIN_POWER_H:
	हाल LTC2945_MAX_POWER_THRES_H:
	हाल LTC2945_MIN_POWER_THRES_H:
		/*
		 * Convert to रेजिस्टर value by assuming current is measured
		 * with an 1mOhm sense resistor, similar to current
		 * measurements.
		 * Control रेजिस्टर bit 0 selects अगर voltage at SENSE+/VDD
		 * or voltage at ADIN is used to measure घातer, which in turn
		 * determines रेजिस्टर calculations.
		 */
		ret = regmap_पढ़ो(regmap, LTC2945_CONTROL, &control);
		अगर (ret < 0)
			वापस ret;
		अगर (control & CONTROL_MULT_SELECT) अणु
			/* 25 mV * 25 uV = 0.625 uV resolution. */
			val = DIV_ROUND_CLOSEST(val, 625);
		पूर्ण अन्यथा अणु
			/*
			 * 0.5 mV * 25 uV = 0.0125 uV resolution.
			 * Divide first to aव्योम overflow;
			 * accept loss of accuracy.
			 */
			val = DIV_ROUND_CLOSEST(val, 25) * 2;
		पूर्ण
		अवरोध;
	हाल LTC2945_VIN_H:
	हाल LTC2945_MAX_VIN_H:
	हाल LTC2945_MIN_VIN_H:
	हाल LTC2945_MAX_VIN_THRES_H:
	हाल LTC2945_MIN_VIN_THRES_H:
		/* 25 mV resolution. */
		val /= 25;
		अवरोध;
	हाल LTC2945_ADIN_H:
	हाल LTC2945_MAX_ADIN_H:
	हाल LTC2945_MIN_ADIN_THRES_H:
	हाल LTC2945_MAX_ADIN_THRES_H:
	हाल LTC2945_MIN_ADIN_H:
		/* 0.5mV resolution. */
		val *= 2;
		अवरोध;
	हाल LTC2945_SENSE_H:
	हाल LTC2945_MAX_SENSE_H:
	हाल LTC2945_MIN_SENSE_H:
	हाल LTC2945_MAX_SENSE_THRES_H:
	हाल LTC2945_MIN_SENSE_THRES_H:
		/*
		 * 25 uV resolution. Convert to current as measured with
		 * an 1 mOhm sense resistor, in mA. If a dअगरferent sense
		 * resistor is installed, calculate the actual current by
		 * भागiding the reported current by the sense resistor value
		 * in mOhm.
		 */
		val = DIV_ROUND_CLOSEST(val, 25);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस val;
पूर्ण

अटल sमाप_प्रकार ltc2945_value_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	दीर्घ दीर्घ value;

	value = ltc2945_reg_to_val(dev, attr->index);
	अगर (value < 0)
		वापस value;
	वापस sysfs_emit(buf, "%lld\n", value);
पूर्ण

अटल sमाप_प्रकार ltc2945_value_store(काष्ठा device *dev,
				   काष्ठा device_attribute *da,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	u8 reg = attr->index;
	अचिन्हित दीर्घ val;
	u8 regbuf[3];
	पूर्णांक num_regs;
	पूर्णांक regval;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	/* convert to रेजिस्टर value, then clamp and ग_लिखो result */
	regval = ltc2945_val_to_reg(dev, reg, val);
	अगर (is_घातer_reg(reg)) अणु
		regval = clamp_val(regval, 0, 0xffffff);
		regbuf[0] = regval >> 16;
		regbuf[1] = (regval >> 8) & 0xff;
		regbuf[2] = regval;
		num_regs = 3;
	पूर्ण अन्यथा अणु
		regval = clamp_val(regval, 0, 0xfff) << 4;
		regbuf[0] = regval >> 8;
		regbuf[1] = regval & 0xff;
		num_regs = 2;
	पूर्ण
	ret = regmap_bulk_ग_लिखो(regmap, reg, regbuf, num_regs);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार ltc2945_history_store(काष्ठा device *dev,
				     काष्ठा device_attribute *da,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	u8 reg = attr->index;
	पूर्णांक num_regs = is_घातer_reg(reg) ? 3 : 2;
	u8 buf_min[3] = अणु 0xff, 0xff, 0xff पूर्ण;
	u8 buf_max[3] = अणु 0, 0, 0 पूर्ण;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;
	अगर (val != 1)
		वापस -EINVAL;

	ret = regmap_update_bits(regmap, LTC2945_CONTROL, CONTROL_TEST_MODE,
				 CONTROL_TEST_MODE);

	/* Reset minimum */
	ret = regmap_bulk_ग_लिखो(regmap, reg, buf_min, num_regs);
	अगर (ret)
		वापस ret;

	चयन (reg) अणु
	हाल LTC2945_MIN_POWER_H:
		reg = LTC2945_MAX_POWER_H;
		अवरोध;
	हाल LTC2945_MIN_SENSE_H:
		reg = LTC2945_MAX_SENSE_H;
		अवरोध;
	हाल LTC2945_MIN_VIN_H:
		reg = LTC2945_MAX_VIN_H;
		अवरोध;
	हाल LTC2945_MIN_ADIN_H:
		reg = LTC2945_MAX_ADIN_H;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Bad register: 0x%x\n", reg);
		वापस -EINVAL;
	पूर्ण
	/* Reset maximum */
	ret = regmap_bulk_ग_लिखो(regmap, reg, buf_max, num_regs);

	/* Try resetting test mode even अगर there was an error */
	regmap_update_bits(regmap, LTC2945_CONTROL, CONTROL_TEST_MODE, 0);

	वापस ret ? : count;
पूर्ण

अटल sमाप_प्रकार ltc2945_bool_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक fault;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, LTC2945_FAULT, &fault);
	अगर (ret < 0)
		वापस ret;

	fault &= attr->index;
	अगर (fault)		/* Clear reported faults in chip रेजिस्टर */
		regmap_update_bits(regmap, LTC2945_FAULT, attr->index, 0);

	वापस sysfs_emit(buf, "%d\n", !!fault);
पूर्ण

/* Input voltages */

अटल SENSOR_DEVICE_ATTR_RO(in1_input, ltc2945_value, LTC2945_VIN_H);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, ltc2945_value, LTC2945_MIN_VIN_THRES_H);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, ltc2945_value, LTC2945_MAX_VIN_THRES_H);
अटल SENSOR_DEVICE_ATTR_RO(in1_lowest, ltc2945_value, LTC2945_MIN_VIN_H);
अटल SENSOR_DEVICE_ATTR_RO(in1_highest, ltc2945_value, LTC2945_MAX_VIN_H);
अटल SENSOR_DEVICE_ATTR_WO(in1_reset_history, ltc2945_history,
			     LTC2945_MIN_VIN_H);

अटल SENSOR_DEVICE_ATTR_RO(in2_input, ltc2945_value, LTC2945_ADIN_H);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, ltc2945_value, LTC2945_MIN_ADIN_THRES_H);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, ltc2945_value, LTC2945_MAX_ADIN_THRES_H);
अटल SENSOR_DEVICE_ATTR_RO(in2_lowest, ltc2945_value, LTC2945_MIN_ADIN_H);
अटल SENSOR_DEVICE_ATTR_RO(in2_highest, ltc2945_value, LTC2945_MAX_ADIN_H);
अटल SENSOR_DEVICE_ATTR_WO(in2_reset_history, ltc2945_history,
			     LTC2945_MIN_ADIN_H);

/* Voltage alarms */

अटल SENSOR_DEVICE_ATTR_RO(in1_min_alarm, ltc2945_bool, FAULT_VIN_UV);
अटल SENSOR_DEVICE_ATTR_RO(in1_max_alarm, ltc2945_bool, FAULT_VIN_OV);
अटल SENSOR_DEVICE_ATTR_RO(in2_min_alarm, ltc2945_bool, FAULT_ADIN_UV);
अटल SENSOR_DEVICE_ATTR_RO(in2_max_alarm, ltc2945_bool, FAULT_ADIN_OV);

/* Currents (via sense resistor) */

अटल SENSOR_DEVICE_ATTR_RO(curr1_input, ltc2945_value, LTC2945_SENSE_H);
अटल SENSOR_DEVICE_ATTR_RW(curr1_min, ltc2945_value,
			     LTC2945_MIN_SENSE_THRES_H);
अटल SENSOR_DEVICE_ATTR_RW(curr1_max, ltc2945_value,
			     LTC2945_MAX_SENSE_THRES_H);
अटल SENSOR_DEVICE_ATTR_RO(curr1_lowest, ltc2945_value, LTC2945_MIN_SENSE_H);
अटल SENSOR_DEVICE_ATTR_RO(curr1_highest, ltc2945_value,
			     LTC2945_MAX_SENSE_H);
अटल SENSOR_DEVICE_ATTR_WO(curr1_reset_history, ltc2945_history,
			     LTC2945_MIN_SENSE_H);

/* Current alarms */

अटल SENSOR_DEVICE_ATTR_RO(curr1_min_alarm, ltc2945_bool, FAULT_SENSE_UV);
अटल SENSOR_DEVICE_ATTR_RO(curr1_max_alarm, ltc2945_bool, FAULT_SENSE_OV);

/* Power */

अटल SENSOR_DEVICE_ATTR_RO(घातer1_input, ltc2945_value, LTC2945_POWER_H);
अटल SENSOR_DEVICE_ATTR_RW(घातer1_min, ltc2945_value,
			     LTC2945_MIN_POWER_THRES_H);
अटल SENSOR_DEVICE_ATTR_RW(घातer1_max, ltc2945_value,
			     LTC2945_MAX_POWER_THRES_H);
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input_lowest, ltc2945_value,
			     LTC2945_MIN_POWER_H);
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input_highest, ltc2945_value,
			     LTC2945_MAX_POWER_H);
अटल SENSOR_DEVICE_ATTR_WO(घातer1_reset_history, ltc2945_history,
			     LTC2945_MIN_POWER_H);

/* Power alarms */

अटल SENSOR_DEVICE_ATTR_RO(घातer1_min_alarm, ltc2945_bool, FAULT_POWER_UV);
अटल SENSOR_DEVICE_ATTR_RO(घातer1_max_alarm, ltc2945_bool, FAULT_POWER_OV);

अटल काष्ठा attribute *ltc2945_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_lowest.dev_attr.attr,
	&sensor_dev_attr_in1_highest.dev_attr.attr,
	&sensor_dev_attr_in1_reset_history.dev_attr.attr,
	&sensor_dev_attr_in1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_max_alarm.dev_attr.attr,

	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_lowest.dev_attr.attr,
	&sensor_dev_attr_in2_highest.dev_attr.attr,
	&sensor_dev_attr_in2_reset_history.dev_attr.attr,
	&sensor_dev_attr_in2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_max_alarm.dev_attr.attr,

	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_min.dev_attr.attr,
	&sensor_dev_attr_curr1_max.dev_attr.attr,
	&sensor_dev_attr_curr1_lowest.dev_attr.attr,
	&sensor_dev_attr_curr1_highest.dev_attr.attr,
	&sensor_dev_attr_curr1_reset_history.dev_attr.attr,
	&sensor_dev_attr_curr1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_curr1_max_alarm.dev_attr.attr,

	&sensor_dev_attr_घातer1_input.dev_attr.attr,
	&sensor_dev_attr_घातer1_min.dev_attr.attr,
	&sensor_dev_attr_घातer1_max.dev_attr.attr,
	&sensor_dev_attr_घातer1_input_lowest.dev_attr.attr,
	&sensor_dev_attr_घातer1_input_highest.dev_attr.attr,
	&sensor_dev_attr_घातer1_reset_history.dev_attr.attr,
	&sensor_dev_attr_घातer1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_घातer1_max_alarm.dev_attr.attr,

	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ltc2945);

अटल स्थिर काष्ठा regmap_config ltc2945_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LTC2945_MIN_ADIN_THRES_L,
पूर्ण;

अटल पूर्णांक ltc2945_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &ltc2945_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/* Clear faults */
	regmap_ग_लिखो(regmap, LTC2945_FAULT, 0x00);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   regmap,
							   ltc2945_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc2945_id[] = अणु
	अणु"ltc2945", 0पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ltc2945_id);

अटल काष्ठा i2c_driver ltc2945_driver = अणु
	.driver = अणु
		   .name = "ltc2945",
		   पूर्ण,
	.probe_new = ltc2945_probe,
	.id_table = ltc2945_id,
पूर्ण;

module_i2c_driver(ltc2945_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("LTC2945 driver");
MODULE_LICENSE("GPL");
