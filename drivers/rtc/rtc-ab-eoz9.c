<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real Time Clock driver क्रम AB-RTCMC-32.768kHz-EOZ9 chip.
 * Copyright (C) 2019 Orolia
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>

#घोषणा ABEOZ9_REG_CTRL1		0x00
#घोषणा ABEOZ9_REG_CTRL1_MASK		GENMASK(7, 0)
#घोषणा ABEOZ9_REG_CTRL1_WE		BIT(0)
#घोषणा ABEOZ9_REG_CTRL1_TE		BIT(1)
#घोषणा ABEOZ9_REG_CTRL1_TAR		BIT(2)
#घोषणा ABEOZ9_REG_CTRL1_EERE		BIT(3)
#घोषणा ABEOZ9_REG_CTRL1_SRON		BIT(4)
#घोषणा ABEOZ9_REG_CTRL1_TD0		BIT(5)
#घोषणा ABEOZ9_REG_CTRL1_TD1		BIT(6)
#घोषणा ABEOZ9_REG_CTRL1_CLKINT		BIT(7)

#घोषणा ABEOZ9_REG_CTRL_INT		0x01
#घोषणा ABEOZ9_REG_CTRL_INT_AIE		BIT(0)
#घोषणा ABEOZ9_REG_CTRL_INT_TIE		BIT(1)
#घोषणा ABEOZ9_REG_CTRL_INT_V1IE	BIT(2)
#घोषणा ABEOZ9_REG_CTRL_INT_V2IE	BIT(3)
#घोषणा ABEOZ9_REG_CTRL_INT_SRIE	BIT(4)

#घोषणा ABEOZ9_REG_CTRL_INT_FLAG	0x02
#घोषणा ABEOZ9_REG_CTRL_INT_FLAG_AF	BIT(0)
#घोषणा ABEOZ9_REG_CTRL_INT_FLAG_TF	BIT(1)
#घोषणा ABEOZ9_REG_CTRL_INT_FLAG_V1IF	BIT(2)
#घोषणा ABEOZ9_REG_CTRL_INT_FLAG_V2IF	BIT(3)
#घोषणा ABEOZ9_REG_CTRL_INT_FLAG_SRF	BIT(4)

#घोषणा ABEOZ9_REG_CTRL_STATUS		0x03
#घोषणा ABEOZ9_REG_CTRL_STATUS_V1F	BIT(2)
#घोषणा ABEOZ9_REG_CTRL_STATUS_V2F	BIT(3)
#घोषणा ABEOZ9_REG_CTRL_STATUS_SR	BIT(4)
#घोषणा ABEOZ9_REG_CTRL_STATUS_PON	BIT(5)
#घोषणा ABEOZ9_REG_CTRL_STATUS_EEBUSY	BIT(7)

#घोषणा ABEOZ9_REG_SEC			0x08
#घोषणा ABEOZ9_REG_MIN			0x09
#घोषणा ABEOZ9_REG_HOURS		0x0A
#घोषणा ABEOZ9_HOURS_PM			BIT(6)
#घोषणा ABEOZ9_REG_DAYS			0x0B
#घोषणा ABEOZ9_REG_WEEKDAYS		0x0C
#घोषणा ABEOZ9_REG_MONTHS		0x0D
#घोषणा ABEOZ9_REG_YEARS		0x0E

#घोषणा ABEOZ9_SEC_LEN			7

#घोषणा ABEOZ9_REG_ALARM_SEC		0x10
#घोषणा ABEOZ9_BIT_ALARM_SEC		GENMASK(6, 0)
#घोषणा ABEOZ9_REG_ALARM_MIN		0x11
#घोषणा ABEOZ9_BIT_ALARM_MIN		GENMASK(6, 0)
#घोषणा ABEOZ9_REG_ALARM_HOURS		0x12
#घोषणा ABEOZ9_BIT_ALARM_HOURS_PM	BIT(5)
#घोषणा ABEOZ9_BIT_ALARM_HOURS		GENMASK(4, 0)
#घोषणा ABEOZ9_REG_ALARM_DAYS		0x13
#घोषणा ABEOZ9_BIT_ALARM_DAYS		GENMASK(5, 0)
#घोषणा ABEOZ9_REG_ALARM_WEEKDAYS	0x14
#घोषणा ABEOZ9_BIT_ALARM_WEEKDAYS	GENMASK(2, 0)
#घोषणा ABEOZ9_REG_ALARM_MONTHS		0x15
#घोषणा ABEOZ9_BIT_ALARM_MONTHS		GENMASK(4, 0)
#घोषणा ABEOZ9_REG_ALARM_YEARS		0x16

#घोषणा ABEOZ9_ALARM_LEN		7
#घोषणा ABEOZ9_BIT_ALARM_AE		BIT(7)

#घोषणा ABEOZ9_REG_REG_TEMP		0x20
#घोषणा ABEOZ953_TEMP_MAX		120
#घोषणा ABEOZ953_TEMP_MIN		-60

#घोषणा ABEOZ9_REG_EEPROM		0x30
#घोषणा ABEOZ9_REG_EEPROM_MASK		GENMASK(8, 0)
#घोषणा ABEOZ9_REG_EEPROM_THP		BIT(0)
#घोषणा ABEOZ9_REG_EEPROM_THE		BIT(1)
#घोषणा ABEOZ9_REG_EEPROM_FD0		BIT(2)
#घोषणा ABEOZ9_REG_EEPROM_FD1		BIT(3)
#घोषणा ABEOZ9_REG_EEPROM_R1K		BIT(4)
#घोषणा ABEOZ9_REG_EEPROM_R5K		BIT(5)
#घोषणा ABEOZ9_REG_EEPROM_R20K		BIT(6)
#घोषणा ABEOZ9_REG_EEPROM_R80K		BIT(7)

काष्ठा abeoz9_rtc_data अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap *regmap;
	काष्ठा device *hwmon_dev;
पूर्ण;

अटल पूर्णांक abeoz9_check_validity(काष्ठा device *dev)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	पूर्णांक ret;
	पूर्णांक val;

	ret = regmap_पढ़ो(regmap, ABEOZ9_REG_CTRL_STATUS, &val);
	अगर (ret < 0) अणु
		dev_err(dev,
			"unable to get CTRL_STATUS register (%d)\n", ret);
		वापस ret;
	पूर्ण

	अगर (val & ABEOZ9_REG_CTRL_STATUS_PON) अणु
		dev_warn(dev, "power-on reset detected, date is invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (val & ABEOZ9_REG_CTRL_STATUS_V1F) अणु
		dev_warn(dev,
			 "voltage drops below VLOW1 threshold, date is invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((val & ABEOZ9_REG_CTRL_STATUS_V2F)) अणु
		dev_warn(dev,
			 "voltage drops below VLOW2 threshold, date is invalid\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक abeoz9_reset_validity(काष्ठा regmap *regmap)
अणु
	वापस regmap_update_bits(regmap, ABEOZ9_REG_CTRL_STATUS,
				  ABEOZ9_REG_CTRL_STATUS_V1F |
				  ABEOZ9_REG_CTRL_STATUS_V2F |
				  ABEOZ9_REG_CTRL_STATUS_PON,
				  0);
पूर्ण

अटल पूर्णांक abeoz9_rtc_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	u8 regs[ABEOZ9_SEC_LEN];
	पूर्णांक ret;

	ret = abeoz9_check_validity(dev);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, ABEOZ9_REG_SEC,
			       regs,
			       माप(regs));
	अगर (ret) अणु
		dev_err(dev, "reading RTC time failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(regs[ABEOZ9_REG_SEC - ABEOZ9_REG_SEC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(regs[ABEOZ9_REG_MIN - ABEOZ9_REG_SEC] & 0x7F);

	अगर (regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] & ABEOZ9_HOURS_PM) अणु
		पंचांग->पंचांग_hour =
			bcd2bin(regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] & 0x1f);
		अगर (regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] & ABEOZ9_HOURS_PM)
			पंचांग->पंचांग_hour += 12;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_hour = bcd2bin(regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC]);
	पूर्ण

	पंचांग->पंचांग_mday = bcd2bin(regs[ABEOZ9_REG_DAYS - ABEOZ9_REG_SEC]);
	पंचांग->पंचांग_wday = bcd2bin(regs[ABEOZ9_REG_WEEKDAYS - ABEOZ9_REG_SEC]);
	पंचांग->पंचांग_mon  = bcd2bin(regs[ABEOZ9_REG_MONTHS - ABEOZ9_REG_SEC]) - 1;
	पंचांग->पंचांग_year = bcd2bin(regs[ABEOZ9_REG_YEARS - ABEOZ9_REG_SEC]) + 100;

	वापस ret;
पूर्ण

अटल पूर्णांक abeoz9_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	u8 regs[ABEOZ9_SEC_LEN];
	पूर्णांक ret;

	regs[ABEOZ9_REG_SEC - ABEOZ9_REG_SEC] = bin2bcd(पंचांग->पंचांग_sec);
	regs[ABEOZ9_REG_MIN - ABEOZ9_REG_SEC] = bin2bcd(पंचांग->पंचांग_min);
	regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] = bin2bcd(पंचांग->पंचांग_hour);
	regs[ABEOZ9_REG_DAYS - ABEOZ9_REG_SEC] = bin2bcd(पंचांग->पंचांग_mday);
	regs[ABEOZ9_REG_WEEKDAYS - ABEOZ9_REG_SEC] = bin2bcd(पंचांग->पंचांग_wday);
	regs[ABEOZ9_REG_MONTHS - ABEOZ9_REG_SEC] = bin2bcd(पंचांग->पंचांग_mon + 1);
	regs[ABEOZ9_REG_YEARS - ABEOZ9_REG_SEC] = bin2bcd(पंचांग->पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(data->regmap, ABEOZ9_REG_SEC,
				regs,
				माप(regs));

	अगर (ret) अणु
		dev_err(dev, "set RTC time failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस abeoz9_reset_validity(regmap);
पूर्ण

अटल पूर्णांक abeoz9_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	u8 regs[ABEOZ9_ALARM_LEN];
	u8 val[2];
	पूर्णांक ret;

	ret = abeoz9_check_validity(dev);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(regmap, ABEOZ9_REG_CTRL_INT, val, माप(val));
	अगर (ret)
		वापस ret;

	alarm->enabled = val[0] & ABEOZ9_REG_CTRL_INT_AIE;
	alarm->pending = val[1] & ABEOZ9_REG_CTRL_INT_FLAG_AF;

	ret = regmap_bulk_पढ़ो(regmap, ABEOZ9_REG_ALARM_SEC, regs, माप(regs));
	अगर (ret)
		वापस ret;

	alarm->समय.पंचांग_sec = bcd2bin(FIELD_GET(ABEOZ9_BIT_ALARM_SEC, regs[0]));
	alarm->समय.पंचांग_min = bcd2bin(FIELD_GET(ABEOZ9_BIT_ALARM_MIN, regs[1]));
	alarm->समय.पंचांग_hour = bcd2bin(FIELD_GET(ABEOZ9_BIT_ALARM_HOURS, regs[2]));
	अगर (FIELD_GET(ABEOZ9_BIT_ALARM_HOURS_PM, regs[2]))
		alarm->समय.पंचांग_hour += 12;

	alarm->समय.पंचांग_mday = bcd2bin(FIELD_GET(ABEOZ9_BIT_ALARM_DAYS, regs[3]));

	वापस 0;
पूर्ण

अटल पूर्णांक abeoz9_rtc_alarm_irq_enable(काष्ठा device *dev, u32 enable)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);

	वापस regmap_update_bits(data->regmap, ABEOZ9_REG_CTRL_INT,
				  ABEOZ9_REG_CTRL_INT_AIE,
				  FIELD_PREP(ABEOZ9_REG_CTRL_INT_AIE, enable));
पूर्ण

अटल पूर्णांक abeoz9_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	u8 regs[ABEOZ9_ALARM_LEN] = अणु0पूर्ण;
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, ABEOZ9_REG_CTRL_INT_FLAG,
				 ABEOZ9_REG_CTRL_INT_FLAG_AF, 0);
	अगर (ret)
		वापस ret;

	regs[0] = ABEOZ9_BIT_ALARM_AE | FIELD_PREP(ABEOZ9_BIT_ALARM_SEC,
						   bin2bcd(alarm->समय.पंचांग_sec));
	regs[1] = ABEOZ9_BIT_ALARM_AE | FIELD_PREP(ABEOZ9_BIT_ALARM_MIN,
						   bin2bcd(alarm->समय.पंचांग_min));
	regs[2] = ABEOZ9_BIT_ALARM_AE | FIELD_PREP(ABEOZ9_BIT_ALARM_HOURS,
						   bin2bcd(alarm->समय.पंचांग_hour));
	regs[3] = ABEOZ9_BIT_ALARM_AE | FIELD_PREP(ABEOZ9_BIT_ALARM_DAYS,
						   bin2bcd(alarm->समय.पंचांग_mday));

	ret = regmap_bulk_ग_लिखो(data->regmap, ABEOZ9_REG_ALARM_SEC, regs,
				माप(regs));
	अगर (ret)
		वापस ret;

	वापस abeoz9_rtc_alarm_irq_enable(dev, alarm->enabled);
पूर्ण

अटल irqवापस_t abeoz9_rtc_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, ABEOZ9_REG_CTRL_INT_FLAG, &val);
	अगर (ret)
		वापस IRQ_NONE;

	अगर (!FIELD_GET(ABEOZ9_REG_CTRL_INT_FLAG_AF, val))
		वापस IRQ_NONE;

	regmap_update_bits(data->regmap, ABEOZ9_REG_CTRL_INT_FLAG,
			   ABEOZ9_REG_CTRL_INT_FLAG_AF, 0);

	rtc_update_irq(data->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक abeoz9_trickle_parse_dt(काष्ठा device_node *node)
अणु
	u32 ohms = 0;

	अगर (of_property_पढ़ो_u32(node, "trickle-resistor-ohms", &ohms))
		वापस 0;

	चयन (ohms) अणु
	हाल 1000:
		वापस ABEOZ9_REG_EEPROM_R1K;
	हाल 5000:
		वापस ABEOZ9_REG_EEPROM_R5K;
	हाल 20000:
		वापस ABEOZ9_REG_EEPROM_R20K;
	हाल 80000:
		वापस ABEOZ9_REG_EEPROM_R80K;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक abeoz9_rtc_setup(काष्ठा device *dev, काष्ठा device_node *node)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	पूर्णांक ret;

	/* Enable Self Recovery, Clock क्रम Watch and EEPROM refresh functions */
	ret = regmap_update_bits(regmap, ABEOZ9_REG_CTRL1,
				 ABEOZ9_REG_CTRL1_MASK,
				 ABEOZ9_REG_CTRL1_WE |
				 ABEOZ9_REG_CTRL1_EERE |
				 ABEOZ9_REG_CTRL1_SRON);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to set CTRL_1 register (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(regmap, ABEOZ9_REG_CTRL_INT, 0);
	अगर (ret < 0) अणु
		dev_err(dev,
			"unable to set control CTRL_INT register (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(regmap, ABEOZ9_REG_CTRL_INT_FLAG, 0);
	अगर (ret < 0) अणु
		dev_err(dev,
			"unable to set control CTRL_INT_FLAG register (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = abeoz9_trickle_parse_dt(node);

	/* Enable built-in termometer */
	ret |= ABEOZ9_REG_EEPROM_THE;

	ret = regmap_update_bits(regmap, ABEOZ9_REG_EEPROM,
				 ABEOZ9_REG_EEPROM_MASK,
				 ret);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to set EEPROM register (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc_ops = अणु
	.पढ़ो_समय = abeoz9_rtc_get_समय,
	.set_समय = abeoz9_rtc_set_समय,
	.पढ़ो_alarm = abeoz9_rtc_पढ़ो_alarm,
	.set_alarm = abeoz9_rtc_set_alarm,
	.alarm_irq_enable = abeoz9_rtc_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा regmap_config abeoz9_rtc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x3f,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_HWMON)

अटल पूर्णांक abeoz9z3_temp_पढ़ो(काष्ठा device *dev,
			      क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	काष्ठा abeoz9_rtc_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(regmap, ABEOZ9_REG_CTRL_STATUS, &val);
	अगर (ret < 0)
		वापस ret;

	अगर ((val & ABEOZ9_REG_CTRL_STATUS_V1F) ||
	    (val & ABEOZ9_REG_CTRL_STATUS_V2F)) अणु
		dev_err(dev,
			"thermometer might be disabled due to low voltage\n");
		वापस -EINVAL;
	पूर्ण

	चयन (attr) अणु
	हाल hwmon_temp_input:
		ret = regmap_पढ़ो(regmap, ABEOZ9_REG_REG_TEMP, &val);
		अगर (ret < 0)
			वापस ret;
		*temp = 1000 * (val + ABEOZ953_TEMP_MIN);
		वापस 0;
	हाल hwmon_temp_max:
		*temp = 1000 * ABEOZ953_TEMP_MAX;
		वापस 0;
	हाल hwmon_temp_min:
		*temp = 1000 * ABEOZ953_TEMP_MIN;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t abeoz9_is_visible(स्थिर व्योम *data,
				 क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_max:
	हाल hwmon_temp_min:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर u32 abeoz9_chip_config[] = अणु
	HWMON_C_REGISTER_TZ,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info abeoz9_chip = अणु
	.type = hwmon_chip,
	.config = abeoz9_chip_config,
पूर्ण;

अटल स्थिर u32 abeoz9_temp_config[] = अणु
	HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info abeoz9_temp = अणु
	.type = hwmon_temp,
	.config = abeoz9_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *abeoz9_info[] = अणु
	&abeoz9_chip,
	&abeoz9_temp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops abeoz9_hwmon_ops = अणु
	.is_visible = abeoz9_is_visible,
	.पढ़ो = abeoz9z3_temp_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info abeoz9_chip_info = अणु
	.ops = &abeoz9_hwmon_ops,
	.info = abeoz9_info,
पूर्ण;

अटल व्योम abeoz9_hwmon_रेजिस्टर(काष्ठा device *dev,
				  काष्ठा abeoz9_rtc_data *data)
अणु
	data->hwmon_dev =
		devm_hwmon_device_रेजिस्टर_with_info(dev,
						     "abeoz9",
						     data,
						     &abeoz9_chip_info,
						     शून्य);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_warn(dev, "unable to register hwmon device %ld\n",
			 PTR_ERR(data->hwmon_dev));
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम abeoz9_hwmon_रेजिस्टर(काष्ठा device *dev,
				  काष्ठा abeoz9_rtc_data *data)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक abeoz9_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा abeoz9_rtc_data *data = शून्य;
	काष्ठा device *dev = &client->dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -ENODEV;

	regmap = devm_regmap_init_i2c(client, &abeoz9_rtc_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(dev, "regmap allocation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regmap = regmap;
	dev_set_drvdata(dev, data);

	ret = abeoz9_rtc_setup(dev, client->dev.of_node);
	अगर (ret)
		वापस ret;

	data->rtc = devm_rtc_allocate_device(dev);
	ret = PTR_ERR_OR_ZERO(data->rtc);
	अगर (ret)
		वापस ret;

	data->rtc->ops = &rtc_ops;
	data->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	data->rtc->range_max = RTC_TIMESTAMP_END_2099;
	data->rtc->uie_unsupported = 1;
	clear_bit(RTC_FEATURE_ALARM, data->rtc->features);

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						abeoz9_rtc_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						dev_name(dev), dev);
		अगर (ret) अणु
			dev_err(dev, "failed to request alarm irq\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (client->irq > 0 || device_property_पढ़ो_bool(dev, "wakeup-source")) अणु
		ret = device_init_wakeup(dev, true);
		set_bit(RTC_FEATURE_ALARM, data->rtc->features);
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(data->rtc);
	अगर (ret)
		वापस ret;

	abeoz9_hwmon_रेजिस्टर(dev, data);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id abeoz9_dt_match[] = अणु
	अणु .compatible = "abracon,abeoz9" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, abeoz9_dt_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id abeoz9_id[] = अणु
	अणु "abeoz9", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver abeoz9_driver = अणु
	.driver = अणु
		.name = "rtc-ab-eoz9",
		.of_match_table = of_match_ptr(abeoz9_dt_match),
	पूर्ण,
	.probe	  = abeoz9_probe,
	.id_table = abeoz9_id,
पूर्ण;

module_i2c_driver(abeoz9_driver);

MODULE_AUTHOR("Artem Panfilov <panfilov.artyom@gmail.com>");
MODULE_DESCRIPTION("Abracon AB-RTCMC-32.768kHz-EOZ9 RTC driver");
MODULE_LICENSE("GPL");
