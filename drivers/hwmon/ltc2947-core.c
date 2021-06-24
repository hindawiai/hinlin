<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices LTC2947 high precision घातer and energy monitor
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "ltc2947.h"

/* रेजिस्टर's */
#घोषणा LTC2947_REG_PAGE_CTRL		0xFF
#घोषणा LTC2947_REG_CTRL		0xF0
#घोषणा LTC2947_REG_TBCTL		0xE9
#घोषणा LTC2947_CONT_MODE_MASK		BIT(3)
#घोषणा LTC2947_CONT_MODE(x)		FIELD_PREP(LTC2947_CONT_MODE_MASK, x)
#घोषणा LTC2947_PRE_MASK		GENMASK(2, 0)
#घोषणा LTC2947_PRE(x)			FIELD_PREP(LTC2947_PRE_MASK, x)
#घोषणा LTC2947_DIV_MASK		GENMASK(7, 3)
#घोषणा LTC2947_DIV(x)			FIELD_PREP(LTC2947_DIV_MASK, x)
#घोषणा LTC2947_SHUTDOWN_MASK		BIT(0)
#घोषणा LTC2947_REG_ACCUM_POL		0xE1
#घोषणा LTC2947_ACCUM_POL_1_MASK	GENMASK(1, 0)
#घोषणा LTC2947_ACCUM_POL_1(x)		FIELD_PREP(LTC2947_ACCUM_POL_1_MASK, x)
#घोषणा LTC2947_ACCUM_POL_2_MASK	GENMASK(3, 2)
#घोषणा LTC2947_ACCUM_POL_2(x)		FIELD_PREP(LTC2947_ACCUM_POL_2_MASK, x)
#घोषणा LTC2947_REG_ACCUM_DEADBAND	0xE4
#घोषणा LTC2947_REG_GPIOSTATCTL		0x67
#घोषणा LTC2947_GPIO_EN_MASK		BIT(0)
#घोषणा LTC2947_GPIO_EN(x)		FIELD_PREP(LTC2947_GPIO_EN_MASK, x)
#घोषणा LTC2947_GPIO_FAN_EN_MASK	BIT(6)
#घोषणा LTC2947_GPIO_FAN_EN(x)		FIELD_PREP(LTC2947_GPIO_FAN_EN_MASK, x)
#घोषणा LTC2947_GPIO_FAN_POL_MASK	BIT(7)
#घोषणा LTC2947_GPIO_FAN_POL(x)		FIELD_PREP(LTC2947_GPIO_FAN_POL_MASK, x)
#घोषणा LTC2947_REG_GPIO_ACCUM		0xE3
/* 200Khz */
#घोषणा LTC2947_CLK_MIN			200000
/* 25Mhz */
#घोषणा LTC2947_CLK_MAX			25000000
#घोषणा LTC2947_PAGE0			0
#घोषणा LTC2947_PAGE1			1
/* Voltage रेजिस्टरs */
#घोषणा LTC2947_REG_VOLTAGE		0xA0
#घोषणा LTC2947_REG_VOLTAGE_MAX		0x50
#घोषणा LTC2947_REG_VOLTAGE_MIN		0x52
#घोषणा LTC2947_REG_VOLTAGE_THRE_H	0x90
#घोषणा LTC2947_REG_VOLTAGE_THRE_L	0x92
#घोषणा LTC2947_REG_DVCC		0xA4
#घोषणा LTC2947_REG_DVCC_MAX		0x58
#घोषणा LTC2947_REG_DVCC_MIN		0x5A
#घोषणा LTC2947_REG_DVCC_THRE_H		0x98
#घोषणा LTC2947_REG_DVCC_THRE_L		0x9A
#घोषणा LTC2947_VOLTAGE_GEN_CHAN	0
#घोषणा LTC2947_VOLTAGE_DVCC_CHAN	1
/* in mV */
#घोषणा VOLTAGE_MAX			15500
#घोषणा VOLTAGE_MIN			-300
#घोषणा VDVCC_MAX			15000
#घोषणा VDVCC_MIN			4750
/* Current रेजिस्टरs */
#घोषणा LTC2947_REG_CURRENT		0x90
#घोषणा LTC2947_REG_CURRENT_MAX		0x40
#घोषणा LTC2947_REG_CURRENT_MIN		0x42
#घोषणा LTC2947_REG_CURRENT_THRE_H	0x80
#घोषणा LTC2947_REG_CURRENT_THRE_L	0x82
/* in mA */
#घोषणा CURRENT_MAX			30000
#घोषणा CURRENT_MIN			-30000
/* Power रेजिस्टरs */
#घोषणा LTC2947_REG_POWER		0x93
#घोषणा LTC2947_REG_POWER_MAX		0x44
#घोषणा LTC2947_REG_POWER_MIN		0x46
#घोषणा LTC2947_REG_POWER_THRE_H	0x84
#घोषणा LTC2947_REG_POWER_THRE_L	0x86
/* in uW */
#घोषणा POWER_MAX			450000000
#घोषणा POWER_MIN			-450000000
/* Temperature रेजिस्टरs */
#घोषणा LTC2947_REG_TEMP		0xA2
#घोषणा LTC2947_REG_TEMP_MAX		0x54
#घोषणा LTC2947_REG_TEMP_MIN		0x56
#घोषणा LTC2947_REG_TEMP_THRE_H		0x94
#घोषणा LTC2947_REG_TEMP_THRE_L		0x96
#घोषणा LTC2947_REG_TEMP_FAN_THRE_H	0x9C
#घोषणा LTC2947_REG_TEMP_FAN_THRE_L	0x9E
#घोषणा LTC2947_TEMP_FAN_CHAN		1
/* in millidegress Celsius */
#घोषणा TEMP_MAX			85000
#घोषणा TEMP_MIN			-40000
/* Energy रेजिस्टरs */
#घोषणा LTC2947_REG_ENERGY1		0x06
#घोषणा LTC2947_REG_ENERGY2		0x16
/* Status/Alarm/Overflow रेजिस्टरs */
#घोषणा LTC2947_REG_STATUS		0x80
#घोषणा LTC2947_REG_STATVT		0x81
#घोषणा LTC2947_REG_STATIP		0x82
#घोषणा LTC2947_REG_STATVDVCC		0x87

#घोषणा LTC2947_ALERTS_SIZE	(LTC2947_REG_STATVDVCC - LTC2947_REG_STATUS)
#घोषणा LTC2947_MAX_VOLTAGE_MASK	BIT(0)
#घोषणा LTC2947_MIN_VOLTAGE_MASK	BIT(1)
#घोषणा LTC2947_MAX_CURRENT_MASK	BIT(0)
#घोषणा LTC2947_MIN_CURRENT_MASK	BIT(1)
#घोषणा LTC2947_MAX_POWER_MASK		BIT(2)
#घोषणा LTC2947_MIN_POWER_MASK		BIT(3)
#घोषणा LTC2947_MAX_TEMP_MASK		BIT(2)
#घोषणा LTC2947_MIN_TEMP_MASK		BIT(3)
#घोषणा LTC2947_MAX_TEMP_FAN_MASK	BIT(4)
#घोषणा LTC2947_MIN_TEMP_FAN_MASK	BIT(5)

काष्ठा ltc2947_data अणु
	काष्ठा regmap *map;
	काष्ठा device *dev;
	/*
	 * The mutex is needed because the device has 2 memory pages. When
	 * पढ़ोing/writing the correct page needs to be set so that, the
	 * complete sequence select_page->पढ़ो/ग_लिखो needs to be रक्षित.
	 */
	काष्ठा mutex lock;
	u32 lsb_energy;
	bool gpio_out;
पूर्ण;

अटल पूर्णांक __ltc2947_val_पढ़ो16(स्थिर काष्ठा ltc2947_data *st, स्थिर u8 reg,
				u64 *val)
अणु
	__be16 __val = 0;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(st->map, reg, &__val, 2);
	अगर (ret)
		वापस ret;

	*val = be16_to_cpu(__val);

	वापस 0;
पूर्ण

अटल पूर्णांक __ltc2947_val_पढ़ो24(स्थिर काष्ठा ltc2947_data *st, स्थिर u8 reg,
				u64 *val)
अणु
	__be32 __val = 0;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(st->map, reg, &__val, 3);
	अगर (ret)
		वापस ret;

	*val = be32_to_cpu(__val) >> 8;

	वापस 0;
पूर्ण

अटल पूर्णांक __ltc2947_val_पढ़ो64(स्थिर काष्ठा ltc2947_data *st, स्थिर u8 reg,
				u64 *val)
अणु
	__be64 __val = 0;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(st->map, reg, &__val, 6);
	अगर (ret)
		वापस ret;

	*val = be64_to_cpu(__val) >> 16;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2947_val_पढ़ो(काष्ठा ltc2947_data *st, स्थिर u8 reg,
			    स्थिर u8 page, स्थिर माप_प्रकार size, s64 *val)
अणु
	पूर्णांक ret;
	u64 __val = 0;

	mutex_lock(&st->lock);

	ret = regmap_ग_लिखो(st->map, LTC2947_REG_PAGE_CTRL, page);
	अगर (ret) अणु
		mutex_unlock(&st->lock);
		वापस ret;
	पूर्ण

	dev_dbg(st->dev, "Read val, reg:%02X, p:%d sz:%zu\n", reg, page,
		size);

	चयन (size) अणु
	हाल 2:
		ret = __ltc2947_val_पढ़ो16(st, reg, &__val);
		अवरोध;
	हाल 3:
		ret = __ltc2947_val_पढ़ो24(st, reg, &__val);
		अवरोध;
	हाल 6:
		ret = __ltc2947_val_पढ़ो64(st, reg, &__val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&st->lock);

	अगर (ret)
		वापस ret;

	*val = sign_extend64(__val, (8 * size) - 1);

	dev_dbg(st->dev, "Got s:%lld, u:%016llX\n", *val, __val);

	वापस 0;
पूर्ण

अटल पूर्णांक __ltc2947_val_ग_लिखो64(स्थिर काष्ठा ltc2947_data *st, स्थिर u8 reg,
				 स्थिर u64 val)
अणु
	__be64 __val;

	__val = cpu_to_be64(val << 16);
	वापस regmap_bulk_ग_लिखो(st->map, reg, &__val, 6);
पूर्ण

अटल पूर्णांक __ltc2947_val_ग_लिखो16(स्थिर काष्ठा ltc2947_data *st, स्थिर u8 reg,
				 स्थिर u16 val)
अणु
	__be16 __val;

	__val = cpu_to_be16(val);
	वापस regmap_bulk_ग_लिखो(st->map, reg, &__val, 2);
पूर्ण

अटल पूर्णांक ltc2947_val_ग_लिखो(काष्ठा ltc2947_data *st, स्थिर u8 reg,
			     स्थिर u8 page, स्थिर माप_प्रकार size, स्थिर u64 val)
अणु
	पूर्णांक ret;

	mutex_lock(&st->lock);
	/* set device on correct page */
	ret = regmap_ग_लिखो(st->map, LTC2947_REG_PAGE_CTRL, page);
	अगर (ret) अणु
		mutex_unlock(&st->lock);
		वापस ret;
	पूर्ण

	dev_dbg(st->dev, "Write val, r:%02X, p:%d, sz:%zu, val:%016llX\n",
		reg, page, size, val);

	चयन (size) अणु
	हाल 2:
		ret = __ltc2947_val_ग_लिखो16(st, reg, val);
		अवरोध;
	हाल 6:
		ret = __ltc2947_val_ग_लिखो64(st, reg, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ltc2947_reset_history(काष्ठा ltc2947_data *st, स्थिर u8 reg_h,
				 स्थिर u8 reg_l)
अणु
	पूर्णांक ret;
	/*
	 * let's reset the tracking register's. Tracking register's have all
	 * 2 bytes size
	 */
	ret = ltc2947_val_ग_लिखो(st, reg_h, LTC2947_PAGE0, 2, 0x8000U);
	अगर (ret)
		वापस ret;

	वापस ltc2947_val_ग_लिखो(st, reg_l, LTC2947_PAGE0, 2, 0x7FFFU);
पूर्ण

अटल पूर्णांक ltc2947_alarm_पढ़ो(काष्ठा ltc2947_data *st, स्थिर u8 reg,
			      स्थिर u32 mask, दीर्घ *val)
अणु
	u8 offset = reg - LTC2947_REG_STATUS;
	/* +1 to include status reg */
	अक्षर alarms[LTC2947_ALERTS_SIZE + 1];
	पूर्णांक ret = 0;

	स_रखो(alarms, 0, माप(alarms));

	mutex_lock(&st->lock);

	ret = regmap_ग_लिखो(st->map, LTC2947_REG_PAGE_CTRL, LTC2947_PAGE0);
	अगर (ret)
		जाओ unlock;

	dev_dbg(st->dev, "Read alarm, reg:%02X, mask:%02X\n", reg, mask);
	/*
	 * As stated in the datasheet, when Threshold and Overflow रेजिस्टरs
	 * are used, the status and all alert रेजिस्टरs must be पढ़ो in one
	 * multi-byte transaction.
	 */
	ret = regmap_bulk_पढ़ो(st->map, LTC2947_REG_STATUS, alarms,
			       माप(alarms));
	अगर (ret)
		जाओ unlock;

	/* get the alarm */
	*val = !!(alarms[offset] & mask);
unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ltc2947_show_value(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक ret;
	s64 val = 0;

	ret = ltc2947_val_पढ़ो(st, attr->index, LTC2947_PAGE0, 6, &val);
	अगर (ret)
		वापस ret;

	/* value in microJoule. st->lsb_energy was multiplied by 10E9 */
	val = भाग_s64(val * st->lsb_energy, 1000);

	वापस प्र_लिखो(buf, "%lld\n", val);
पूर्ण

अटल पूर्णांक ltc2947_पढ़ो_temp(काष्ठा device *dev, स्थिर u32 attr, दीर्घ *val,
			     स्थिर पूर्णांक channel)
अणु
	पूर्णांक ret;
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);
	s64 __val = 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_TEMP, LTC2947_PAGE0,
				       2, &__val);
		अवरोध;
	हाल hwmon_temp_highest:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_TEMP_MAX, LTC2947_PAGE0,
				       2, &__val);
		अवरोध;
	हाल hwmon_temp_lowest:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_TEMP_MIN, LTC2947_PAGE0,
				       2, &__val);
		अवरोध;
	हाल hwmon_temp_max_alarm:
		अगर (channel == LTC2947_TEMP_FAN_CHAN)
			वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVT,
						  LTC2947_MAX_TEMP_FAN_MASK,
						  val);

		वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVT,
					  LTC2947_MAX_TEMP_MASK, val);
	हाल hwmon_temp_min_alarm:
		अगर (channel == LTC2947_TEMP_FAN_CHAN)
			वापस	ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVT,
						   LTC2947_MIN_TEMP_FAN_MASK,
						   val);

		वापस	ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVT,
					   LTC2947_MIN_TEMP_MASK, val);
	हाल hwmon_temp_max:
		अगर (channel == LTC2947_TEMP_FAN_CHAN)
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_TEMP_FAN_THRE_H,
					       LTC2947_PAGE1, 2, &__val);
		अन्यथा
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_TEMP_THRE_H,
					       LTC2947_PAGE1, 2, &__val);
		अवरोध;
	हाल hwmon_temp_min:
		अगर (channel == LTC2947_TEMP_FAN_CHAN)
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_TEMP_FAN_THRE_L,
					       LTC2947_PAGE1, 2, &__val);
		अन्यथा
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_TEMP_THRE_L,
					       LTC2947_PAGE1, 2, &__val);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* in milidegrees celcius, temp is given by: */
	*val = (__val * 204) + 550;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2947_पढ़ो_घातer(काष्ठा device *dev, स्थिर u32 attr, दीर्घ *val)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);
	पूर्णांक ret;
	u32 lsb = 200000; /* in uW */
	s64 __val = 0;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_POWER, LTC2947_PAGE0,
				       3, &__val);
		lsb = 50000;
		अवरोध;
	हाल hwmon_घातer_input_highest:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_POWER_MAX, LTC2947_PAGE0,
				       2, &__val);
		अवरोध;
	हाल hwmon_घातer_input_lowest:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_POWER_MIN, LTC2947_PAGE0,
				       2, &__val);
		अवरोध;
	हाल hwmon_घातer_max_alarm:
		वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATIP,
					  LTC2947_MAX_POWER_MASK, val);
	हाल hwmon_घातer_min_alarm:
		वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATIP,
					  LTC2947_MIN_POWER_MASK, val);
	हाल hwmon_घातer_max:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_POWER_THRE_H,
				       LTC2947_PAGE1, 2, &__val);
		अवरोध;
	हाल hwmon_घातer_min:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_POWER_THRE_L,
				       LTC2947_PAGE1, 2, &__val);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (ret)
		वापस ret;

	*val = __val * lsb;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2947_पढ़ो_curr(काष्ठा device *dev, स्थिर u32 attr, दीर्घ *val)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);
	पूर्णांक ret;
	u8 lsb = 12; /* in mA */
	s64 __val = 0;

	चयन (attr) अणु
	हाल hwmon_curr_input:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_CURRENT,
				       LTC2947_PAGE0, 3, &__val);
		lsb = 3;
		अवरोध;
	हाल hwmon_curr_highest:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_CURRENT_MAX,
				       LTC2947_PAGE0, 2, &__val);
		अवरोध;
	हाल hwmon_curr_lowest:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_CURRENT_MIN,
				       LTC2947_PAGE0, 2, &__val);
		अवरोध;
	हाल hwmon_curr_max_alarm:
		वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATIP,
					  LTC2947_MAX_CURRENT_MASK, val);
	हाल hwmon_curr_min_alarm:
		वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATIP,
					  LTC2947_MIN_CURRENT_MASK, val);
	हाल hwmon_curr_max:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_CURRENT_THRE_H,
				       LTC2947_PAGE1, 2, &__val);
		अवरोध;
	हाल hwmon_curr_min:
		ret = ltc2947_val_पढ़ो(st, LTC2947_REG_CURRENT_THRE_L,
				       LTC2947_PAGE1, 2, &__val);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (ret)
		वापस ret;

	*val = __val * lsb;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2947_पढ़ो_in(काष्ठा device *dev, स्थिर u32 attr, दीर्घ *val,
			   स्थिर पूर्णांक channel)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);
	पूर्णांक ret;
	u8 lsb = 2; /* in mV */
	s64 __val = 0;

	अगर (channel < 0 || channel > LTC2947_VOLTAGE_DVCC_CHAN) अणु
		dev_err(st->dev, "Invalid chan%d for voltage", channel);
		वापस -EINVAL;
	पूर्ण

	चयन (attr) अणु
	हाल hwmon_in_input:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN) अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_DVCC,
					       LTC2947_PAGE0, 2, &__val);
			lsb = 145;
		पूर्ण अन्यथा अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_VOLTAGE,
					       LTC2947_PAGE0, 2, &__val);
		पूर्ण
		अवरोध;
	हाल hwmon_in_highest:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN) अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_DVCC_MAX,
					       LTC2947_PAGE0, 2, &__val);
			lsb = 145;
		पूर्ण अन्यथा अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_VOLTAGE_MAX,
					       LTC2947_PAGE0, 2, &__val);
		पूर्ण
		अवरोध;
	हाल hwmon_in_lowest:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN) अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_DVCC_MIN,
					       LTC2947_PAGE0, 2, &__val);
			lsb = 145;
		पूर्ण अन्यथा अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_VOLTAGE_MIN,
					       LTC2947_PAGE0, 2, &__val);
		पूर्ण
		अवरोध;
	हाल hwmon_in_max_alarm:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN)
			वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVDVCC,
						  LTC2947_MAX_VOLTAGE_MASK,
						  val);

		वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVT,
					  LTC2947_MAX_VOLTAGE_MASK, val);
	हाल hwmon_in_min_alarm:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN)
			वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVDVCC,
						  LTC2947_MIN_VOLTAGE_MASK,
						  val);

		वापस ltc2947_alarm_पढ़ो(st, LTC2947_REG_STATVT,
					  LTC2947_MIN_VOLTAGE_MASK, val);
	हाल hwmon_in_max:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN) अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_DVCC_THRE_H,
					       LTC2947_PAGE1, 2, &__val);
			lsb = 145;
		पूर्ण अन्यथा अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_VOLTAGE_THRE_H,
					       LTC2947_PAGE1, 2, &__val);
		पूर्ण
		अवरोध;
	हाल hwmon_in_min:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN) अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_DVCC_THRE_L,
					       LTC2947_PAGE1, 2, &__val);
			lsb = 145;
		पूर्ण अन्यथा अणु
			ret = ltc2947_val_पढ़ो(st, LTC2947_REG_VOLTAGE_THRE_L,
					       LTC2947_PAGE1, 2, &__val);
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (ret)
		वापस ret;

	*val = __val * lsb;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2947_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस ltc2947_पढ़ो_in(dev, attr, val, channel);
	हाल hwmon_curr:
		वापस ltc2947_पढ़ो_curr(dev, attr, val);
	हाल hwmon_घातer:
		वापस ltc2947_पढ़ो_घातer(dev, attr, val);
	हाल hwmon_temp:
		वापस ltc2947_पढ़ो_temp(dev, attr, val, channel);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_ग_लिखो_temp(काष्ठा device *dev, स्थिर u32 attr,
			      दीर्घ val, स्थिर पूर्णांक channel)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);

	अगर (channel < 0 || channel > LTC2947_TEMP_FAN_CHAN) अणु
		dev_err(st->dev, "Invalid chan%d for temperature", channel);
		वापस -EINVAL;
	पूर्ण

	चयन (attr) अणु
	हाल hwmon_temp_reset_history:
		अगर (val != 1)
			वापस -EINVAL;
		वापस ltc2947_reset_history(st, LTC2947_REG_TEMP_MAX,
					     LTC2947_REG_TEMP_MIN);
	हाल hwmon_temp_max:
		val = clamp_val(val, TEMP_MIN, TEMP_MAX);
		अगर (channel == LTC2947_TEMP_FAN_CHAN) अणु
			अगर (!st->gpio_out)
				वापस -ENOTSUPP;

			वापस ltc2947_val_ग_लिखो(st,
					LTC2947_REG_TEMP_FAN_THRE_H,
					LTC2947_PAGE1, 2,
					DIV_ROUND_CLOSEST(val - 550, 204));
		पूर्ण

		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_TEMP_THRE_H,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val - 550, 204));
	हाल hwmon_temp_min:
		val = clamp_val(val, TEMP_MIN, TEMP_MAX);
		अगर (channel == LTC2947_TEMP_FAN_CHAN) अणु
			अगर (!st->gpio_out)
				वापस -ENOTSUPP;

			वापस ltc2947_val_ग_लिखो(st,
					LTC2947_REG_TEMP_FAN_THRE_L,
					LTC2947_PAGE1, 2,
					DIV_ROUND_CLOSEST(val - 550, 204));
		पूर्ण

		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_TEMP_THRE_L,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val - 550, 204));
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_ग_लिखो_घातer(काष्ठा device *dev, स्थिर u32 attr,
			       दीर्घ val)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_घातer_reset_history:
		अगर (val != 1)
			वापस -EINVAL;
		वापस ltc2947_reset_history(st, LTC2947_REG_POWER_MAX,
					     LTC2947_REG_POWER_MIN);
	हाल hwmon_घातer_max:
		val = clamp_val(val, POWER_MIN, POWER_MAX);
		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_POWER_THRE_H,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val, 200000));
	हाल hwmon_घातer_min:
		val = clamp_val(val, POWER_MIN, POWER_MAX);
		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_POWER_THRE_L,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val, 200000));
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_ग_लिखो_curr(काष्ठा device *dev, स्थिर u32 attr,
			      दीर्घ val)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_curr_reset_history:
		अगर (val != 1)
			वापस -EINVAL;
		वापस ltc2947_reset_history(st, LTC2947_REG_CURRENT_MAX,
					     LTC2947_REG_CURRENT_MIN);
	हाल hwmon_curr_max:
		val = clamp_val(val, CURRENT_MIN, CURRENT_MAX);
		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_CURRENT_THRE_H,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val, 12));
	हाल hwmon_curr_min:
		val = clamp_val(val, CURRENT_MIN, CURRENT_MAX);
		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_CURRENT_THRE_L,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val, 12));
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_ग_लिखो_in(काष्ठा device *dev, स्थिर u32 attr, दीर्घ val,
			    स्थिर पूर्णांक channel)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);

	अगर (channel > LTC2947_VOLTAGE_DVCC_CHAN) अणु
		dev_err(st->dev, "Invalid chan%d for voltage", channel);
		वापस -EINVAL;
	पूर्ण

	चयन (attr) अणु
	हाल hwmon_in_reset_history:
		अगर (val != 1)
			वापस -EINVAL;

		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN)
			वापस ltc2947_reset_history(st, LTC2947_REG_DVCC_MAX,
						     LTC2947_REG_DVCC_MIN);

		वापस ltc2947_reset_history(st, LTC2947_REG_VOLTAGE_MAX,
					     LTC2947_REG_VOLTAGE_MIN);
	हाल hwmon_in_max:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN) अणु
			val = clamp_val(val, VDVCC_MIN, VDVCC_MAX);
			वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_DVCC_THRE_H,
						 LTC2947_PAGE1, 2,
						 DIV_ROUND_CLOSEST(val, 145));
		पूर्ण

		val = clamp_val(val, VOLTAGE_MIN, VOLTAGE_MAX);
		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_VOLTAGE_THRE_H,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val, 2));
	हाल hwmon_in_min:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN) अणु
			val = clamp_val(val, VDVCC_MIN, VDVCC_MAX);
			वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_DVCC_THRE_L,
						 LTC2947_PAGE1, 2,
						 DIV_ROUND_CLOSEST(val, 145));
		पूर्ण

		val = clamp_val(val, VOLTAGE_MIN, VOLTAGE_MAX);
		वापस ltc2947_val_ग_लिखो(st, LTC2947_REG_VOLTAGE_THRE_L,
					 LTC2947_PAGE1, 2,
					 DIV_ROUND_CLOSEST(val, 2));
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_ग_लिखो(काष्ठा device *dev,
			 क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस ltc2947_ग_लिखो_in(dev, attr, val, channel);
	हाल hwmon_curr:
		वापस ltc2947_ग_लिखो_curr(dev, attr, val);
	हाल hwmon_घातer:
		वापस ltc2947_ग_लिखो_घातer(dev, attr, val);
	हाल hwmon_temp:
		वापस ltc2947_ग_लिखो_temp(dev, attr, val, channel);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_पढ़ो_labels(काष्ठा device *dev,
			       क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		अगर (channel == LTC2947_VOLTAGE_DVCC_CHAN)
			*str = "DVCC";
		अन्यथा
			*str = "VP-VM";
		वापस 0;
	हाल hwmon_curr:
		*str = "IP-IM";
		वापस 0;
	हाल hwmon_temp:
		अगर (channel == LTC2947_TEMP_FAN_CHAN)
			*str = "TEMPFAN";
		अन्यथा
			*str = "Ambient";
		वापस 0;
	हाल hwmon_घातer:
		*str = "Power";
		वापस 0;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_in_is_visible(स्थिर u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_in_input:
	हाल hwmon_in_highest:
	हाल hwmon_in_lowest:
	हाल hwmon_in_max_alarm:
	हाल hwmon_in_min_alarm:
	हाल hwmon_in_label:
		वापस 0444;
	हाल hwmon_in_reset_history:
		वापस 0200;
	हाल hwmon_in_max:
	हाल hwmon_in_min:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_curr_is_visible(स्थिर u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_curr_input:
	हाल hwmon_curr_highest:
	हाल hwmon_curr_lowest:
	हाल hwmon_curr_max_alarm:
	हाल hwmon_curr_min_alarm:
	हाल hwmon_curr_label:
		वापस 0444;
	हाल hwmon_curr_reset_history:
		वापस 0200;
	हाल hwmon_curr_max:
	हाल hwmon_curr_min:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_घातer_is_visible(स्थिर u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_घातer_input:
	हाल hwmon_घातer_input_highest:
	हाल hwmon_घातer_input_lowest:
	हाल hwmon_घातer_label:
	हाल hwmon_घातer_max_alarm:
	हाल hwmon_घातer_min_alarm:
		वापस 0444;
	हाल hwmon_घातer_reset_history:
		वापस 0200;
	हाल hwmon_घातer_max:
	हाल hwmon_घातer_min:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2947_temp_is_visible(स्थिर u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_highest:
	हाल hwmon_temp_lowest:
	हाल hwmon_temp_max_alarm:
	हाल hwmon_temp_min_alarm:
	हाल hwmon_temp_label:
		वापस 0444;
	हाल hwmon_temp_reset_history:
		वापस 0200;
	हाल hwmon_temp_max:
	हाल hwmon_temp_min:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t ltc2947_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस ltc2947_in_is_visible(attr);
	हाल hwmon_curr:
		वापस ltc2947_curr_is_visible(attr);
	हाल hwmon_घातer:
		वापस ltc2947_घातer_is_visible(attr);
	हाल hwmon_temp:
		वापस ltc2947_temp_is_visible(attr);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *ltc2947_info[] = अणु
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST |
			   HWMON_I_MAX | HWMON_I_MIN | HWMON_I_RESET_HISTORY |
			   HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM |
			   HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST |
			   HWMON_I_MAX | HWMON_I_MIN | HWMON_I_RESET_HISTORY |
			   HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM |
			   HWMON_I_LABEL),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_LOWEST | HWMON_C_HIGHEST |
			   HWMON_C_MAX | HWMON_C_MIN | HWMON_C_RESET_HISTORY |
			   HWMON_C_MIN_ALARM | HWMON_C_MAX_ALARM |
			   HWMON_C_LABEL),
	HWMON_CHANNEL_INFO(घातer,
			   HWMON_P_INPUT | HWMON_P_INPUT_LOWEST |
			   HWMON_P_INPUT_HIGHEST | HWMON_P_MAX | HWMON_P_MIN |
			   HWMON_P_RESET_HISTORY | HWMON_P_MAX_ALARM |
			   HWMON_P_MIN_ALARM | HWMON_P_LABEL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_LOWEST | HWMON_T_HIGHEST |
			   HWMON_T_MAX | HWMON_T_MIN | HWMON_T_RESET_HISTORY |
			   HWMON_T_MIN_ALARM | HWMON_T_MAX_ALARM |
			   HWMON_T_LABEL,
			   HWMON_T_MAX_ALARM | HWMON_T_MIN_ALARM | HWMON_T_MAX |
			   HWMON_T_MIN | HWMON_T_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops ltc2947_hwmon_ops = अणु
	.is_visible = ltc2947_is_visible,
	.पढ़ो = ltc2947_पढ़ो,
	.ग_लिखो = ltc2947_ग_लिखो,
	.पढ़ो_string = ltc2947_पढ़ो_labels,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ltc2947_chip_info = अणु
	.ops = &ltc2947_hwmon_ops,
	.info = ltc2947_info,
पूर्ण;

/* energy attributes are 6bytes wide so we need u64 */
अटल SENSOR_DEVICE_ATTR(energy1_input, 0444, ltc2947_show_value, शून्य,
			  LTC2947_REG_ENERGY1);
अटल SENSOR_DEVICE_ATTR(energy2_input, 0444, ltc2947_show_value, शून्य,
			  LTC2947_REG_ENERGY2);

अटल काष्ठा attribute *ltc2947_attrs[] = अणु
	&sensor_dev_attr_energy1_input.dev_attr.attr,
	&sensor_dev_attr_energy2_input.dev_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ltc2947);

अटल व्योम ltc2947_clk_disable(व्योम *data)
अणु
	काष्ठा clk *extclk = data;

	clk_disable_unprepare(extclk);
पूर्ण

अटल पूर्णांक ltc2947_setup(काष्ठा ltc2947_data *st)
अणु
	पूर्णांक ret;
	काष्ठा clk *extclk;
	u32 dummy, deadband, pol;
	u32 accum[2];

	/* clear status रेजिस्टर by पढ़ोing it */
	ret = regmap_पढ़ो(st->map, LTC2947_REG_STATUS, &dummy);
	अगर (ret)
		वापस ret;
	/*
	 * Set max/min क्रम घातer here since the शेष values x scale
	 * would overflow on 32bit arch
	 */
	ret = ltc2947_val_ग_लिखो(st, LTC2947_REG_POWER_THRE_H, LTC2947_PAGE1, 2,
				POWER_MAX / 200000);
	अगर (ret)
		वापस ret;

	ret = ltc2947_val_ग_लिखो(st, LTC2947_REG_POWER_THRE_L, LTC2947_PAGE1, 2,
				POWER_MIN / 200000);
	अगर (ret)
		वापस ret;

	/* check बाह्यal घड़ी presence */
	extclk = devm_clk_get(st->dev, शून्य);
	अगर (!IS_ERR(extclk)) अणु
		अचिन्हित दीर्घ rate_hz;
		u8 pre = 0, भाग, tbctl;
		u64 aux;

		/* let's calculate and set the right valus in TBCTL */
		rate_hz = clk_get_rate(extclk);
		अगर (rate_hz < LTC2947_CLK_MIN || rate_hz > LTC2947_CLK_MAX) अणु
			dev_err(st->dev, "Invalid rate:%lu for external clock",
				rate_hz);
			वापस -EINVAL;
		पूर्ण

		ret = clk_prepare_enable(extclk);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(st->dev, ltc2947_clk_disable,
					       extclk);
		अगर (ret)
			वापस ret;
		/* as in table 1 of the datasheet */
		अगर (rate_hz >= LTC2947_CLK_MIN && rate_hz <= 1000000)
			pre = 0;
		अन्यथा अगर (rate_hz > 1000000 && rate_hz <= 2000000)
			pre = 1;
		अन्यथा अगर (rate_hz > 2000000 && rate_hz <= 4000000)
			pre = 2;
		अन्यथा अगर (rate_hz > 4000000 && rate_hz <= 8000000)
			pre = 3;
		अन्यथा अगर (rate_hz > 8000000 && rate_hz <= 16000000)
			pre = 4;
		अन्यथा अगर (rate_hz > 16000000 && rate_hz <= LTC2947_CLK_MAX)
			pre = 5;
		/*
		 * Div is given by:
		 *	न्यूनमान(fref / (2^PRE * 32768))
		 */
		भाग = rate_hz / ((1 << pre) * 32768);
		tbctl = LTC2947_PRE(pre) | LTC2947_DIV(भाग);

		ret = regmap_ग_लिखो(st->map, LTC2947_REG_TBCTL, tbctl);
		अगर (ret)
			वापस ret;
		/*
		 * The energy lsb is given by (in W*s):
		 *      06416 * (1/fref) * 2^PRE * (DIV + 1)
		 * The value is multiplied by 10E9
		 */
		aux = (भाग + 1) * ((1 << pre) * 641600000ULL);
		st->lsb_energy = DIV_ROUND_CLOSEST_ULL(aux, rate_hz);
	पूर्ण अन्यथा अणु
		/* 19.89E-6 * 10E9 */
		st->lsb_energy = 19890;
	पूर्ण
	ret = of_property_पढ़ो_u32_array(st->dev->of_node,
					 "adi,accumulator-ctl-pol", accum,
					  ARRAY_SIZE(accum));
	अगर (!ret) अणु
		u32 accum_reg = LTC2947_ACCUM_POL_1(accum[0]) |
				LTC2947_ACCUM_POL_2(accum[1]);

		ret = regmap_ग_लिखो(st->map, LTC2947_REG_ACCUM_POL, accum_reg);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(st->dev->of_node,
				   "adi,accumulation-deadband-microamp",
				   &deadband);
	अगर (!ret) अणु
		/* the LSB is the same as the current, so 3mA */
		ret = regmap_ग_लिखो(st->map, LTC2947_REG_ACCUM_DEADBAND,
				   deadband / (1000 * 3));
		अगर (ret)
			वापस ret;
	पूर्ण
	/* check gpio cfg */
	ret = of_property_पढ़ो_u32(st->dev->of_node, "adi,gpio-out-pol", &pol);
	अगर (!ret) अणु
		/* setup GPIO as output */
		u32 gpio_ctl = LTC2947_GPIO_EN(1) | LTC2947_GPIO_FAN_EN(1) |
			LTC2947_GPIO_FAN_POL(pol);

		st->gpio_out = true;
		ret = regmap_ग_लिखो(st->map, LTC2947_REG_GPIOSTATCTL, gpio_ctl);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32_array(st->dev->of_node, "adi,gpio-in-accum",
					 accum, ARRAY_SIZE(accum));
	अगर (!ret) अणु
		/*
		 * Setup the accum options. The gpioctl is alपढ़ोy defined as
		 * input by शेष.
		 */
		u32 accum_val = LTC2947_ACCUM_POL_1(accum[0]) |
				LTC2947_ACCUM_POL_2(accum[1]);

		अगर (st->gpio_out) अणु
			dev_err(st->dev,
				"Cannot have input gpio config if already configured as output");
			वापस -EINVAL;
		पूर्ण

		ret = regmap_ग_लिखो(st->map, LTC2947_REG_GPIO_ACCUM, accum_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* set continuos mode */
	वापस regmap_update_bits(st->map, LTC2947_REG_CTRL,
				  LTC2947_CONT_MODE_MASK, LTC2947_CONT_MODE(1));
पूर्ण

पूर्णांक ltc2947_core_probe(काष्ठा regmap *map, स्थिर अक्षर *name)
अणु
	काष्ठा ltc2947_data *st;
	काष्ठा device *dev = regmap_get_device(map);
	काष्ठा device *hwmon;
	पूर्णांक ret;

	st = devm_kzalloc(dev, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->map = map;
	st->dev = dev;
	dev_set_drvdata(dev, st);
	mutex_init(&st->lock);

	ret = ltc2947_setup(st);
	अगर (ret)
		वापस ret;

	hwmon = devm_hwmon_device_रेजिस्टर_with_info(dev, name, st,
						     &ltc2947_chip_info,
						     ltc2947_groups);
	वापस PTR_ERR_OR_ZERO(hwmon);
पूर्ण
EXPORT_SYMBOL_GPL(ltc2947_core_probe);

अटल पूर्णांक __maybe_unused ltc2947_resume(काष्ठा device *dev)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);
	u32 ctrl = 0;
	पूर्णांक ret;

	/* dummy पढ़ो to wake the device */
	ret = regmap_पढ़ो(st->map, LTC2947_REG_CTRL, &ctrl);
	अगर (ret)
		वापस ret;
	/*
	 * Wait क्रम the device. It takes 100ms to wake up so, 10ms extra
	 * should be enough.
	 */
	msleep(110);
	ret = regmap_पढ़ो(st->map, LTC2947_REG_CTRL, &ctrl);
	अगर (ret)
		वापस ret;
	/* ctrl should be 0 */
	अगर (ctrl != 0) अणु
		dev_err(st->dev, "Device failed to wake up, ctl:%02X\n", ctrl);
		वापस -ETIMEDOUT;
	पूर्ण

	/* set continuous mode */
	वापस regmap_update_bits(st->map, LTC2947_REG_CTRL,
				  LTC2947_CONT_MODE_MASK, LTC2947_CONT_MODE(1));
पूर्ण

अटल पूर्णांक __maybe_unused ltc2947_suspend(काष्ठा device *dev)
अणु
	काष्ठा ltc2947_data *st = dev_get_drvdata(dev);

	वापस regmap_update_bits(st->map, LTC2947_REG_CTRL,
				  LTC2947_SHUTDOWN_MASK, 1);
पूर्ण

SIMPLE_DEV_PM_OPS(ltc2947_pm_ops, ltc2947_suspend, ltc2947_resume);
EXPORT_SYMBOL_GPL(ltc2947_pm_ops);

स्थिर काष्ठा of_device_id ltc2947_of_match[] = अणु
	अणु .compatible = "adi,ltc2947" पूर्ण,
	अणुपूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(ltc2947_of_match);
MODULE_DEVICE_TABLE(of, ltc2947_of_match);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("LTC2947 power and energy monitor core driver");
MODULE_LICENSE("GPL");
