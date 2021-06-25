<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// RTC driver क्रम Maxim MAX77686 and MAX77802
//
// Copyright (C) 2012 Samsung Electronics Co.Ltd
//
//  based on rtc-max8997.c

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/max77686-निजी.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/regmap.h>

#घोषणा MAX77686_I2C_ADDR_RTC		(0x0C >> 1)
#घोषणा MAX77620_I2C_ADDR_RTC		0x68
#घोषणा MAX77686_INVALID_I2C_ADDR	(-1)

/* Define non existing रेजिस्टर */
#घोषणा MAX77686_INVALID_REG		(-1)

/* RTC Control Register */
#घोषणा BCD_EN_SHIFT			0
#घोषणा BCD_EN_MASK			BIT(BCD_EN_SHIFT)
#घोषणा MODEL24_SHIFT			1
#घोषणा MODEL24_MASK			BIT(MODEL24_SHIFT)
/* RTC Update Register1 */
#घोषणा RTC_UDR_SHIFT			0
#घोषणा RTC_UDR_MASK			BIT(RTC_UDR_SHIFT)
#घोषणा RTC_RBUDR_SHIFT			4
#घोषणा RTC_RBUDR_MASK			BIT(RTC_RBUDR_SHIFT)
/* RTC Hour रेजिस्टर */
#घोषणा HOUR_PM_SHIFT			6
#घोषणा HOUR_PM_MASK			BIT(HOUR_PM_SHIFT)
/* RTC Alarm Enable */
#घोषणा ALARM_ENABLE_SHIFT		7
#घोषणा ALARM_ENABLE_MASK		BIT(ALARM_ENABLE_SHIFT)

#घोषणा REG_RTC_NONE			0xdeadbeef

/*
 * MAX77802 has separate रेजिस्टर (RTCAE1) क्रम alarm enable instead
 * using 1 bit from रेजिस्टरs RTCअणुSEC,MIN,HOUR,DAY,MONTH,YEAR,DATEपूर्ण
 * as in करोne in MAX77686.
 */
#घोषणा MAX77802_ALARM_ENABLE_VALUE	0x77

क्रमागत अणु
	RTC_SEC = 0,
	RTC_MIN,
	RTC_HOUR,
	RTC_WEEKDAY,
	RTC_MONTH,
	RTC_YEAR,
	RTC_DATE,
	RTC_NR_TIME
पूर्ण;

काष्ठा max77686_rtc_driver_data अणु
	/* Minimum usecs needed क्रम a RTC update */
	अचिन्हित दीर्घ		delay;
	/* Mask used to पढ़ो RTC रेजिस्टरs value */
	u8			mask;
	/* Registers offset to I2C addresses map */
	स्थिर अचिन्हित पूर्णांक	*map;
	/* Has a separate alarm enable रेजिस्टर? */
	bool			alarm_enable_reg;
	/* I2C address क्रम RTC block */
	पूर्णांक			rtc_i2c_addr;
	/* RTC पूर्णांकerrupt via platक्रमm resource */
	bool			rtc_irq_from_platक्रमm;
	/* Pending alarm status रेजिस्टर */
	पूर्णांक			alarm_pending_status_reg;
	/* RTC IRQ CHIP क्रम regmap */
	स्थिर काष्ठा regmap_irq_chip *rtc_irq_chip;
	/* regmap configuration क्रम the chip */
	स्थिर काष्ठा regmap_config *regmap_config;
पूर्ण;

काष्ठा max77686_rtc_info अणु
	काष्ठा device		*dev;
	काष्ठा i2c_client	*rtc;
	काष्ठा rtc_device	*rtc_dev;
	काष्ठा mutex		lock;

	काष्ठा regmap		*regmap;
	काष्ठा regmap		*rtc_regmap;

	स्थिर काष्ठा max77686_rtc_driver_data *drv_data;
	काष्ठा regmap_irq_chip_data *rtc_irq_data;

	पूर्णांक rtc_irq;
	पूर्णांक virq;
	पूर्णांक rtc_24hr_mode;
पूर्ण;

क्रमागत MAX77686_RTC_OP अणु
	MAX77686_RTC_WRITE,
	MAX77686_RTC_READ,
पूर्ण;

/* These are not रेजिस्टरs but just offsets that are mapped to addresses */
क्रमागत max77686_rtc_reg_offset अणु
	REG_RTC_CONTROLM = 0,
	REG_RTC_CONTROL,
	REG_RTC_UPDATE0,
	REG_WTSR_SMPL_CNTL,
	REG_RTC_SEC,
	REG_RTC_MIN,
	REG_RTC_HOUR,
	REG_RTC_WEEKDAY,
	REG_RTC_MONTH,
	REG_RTC_YEAR,
	REG_RTC_DATE,
	REG_ALARM1_SEC,
	REG_ALARM1_MIN,
	REG_ALARM1_HOUR,
	REG_ALARM1_WEEKDAY,
	REG_ALARM1_MONTH,
	REG_ALARM1_YEAR,
	REG_ALARM1_DATE,
	REG_ALARM2_SEC,
	REG_ALARM2_MIN,
	REG_ALARM2_HOUR,
	REG_ALARM2_WEEKDAY,
	REG_ALARM2_MONTH,
	REG_ALARM2_YEAR,
	REG_ALARM2_DATE,
	REG_RTC_AE1,
	REG_RTC_END,
पूर्ण;

/* Maps RTC रेजिस्टरs offset to the MAX77686 रेजिस्टर addresses */
अटल स्थिर अचिन्हित पूर्णांक max77686_map[REG_RTC_END] = अणु
	[REG_RTC_CONTROLM]   = MAX77686_RTC_CONTROLM,
	[REG_RTC_CONTROL]    = MAX77686_RTC_CONTROL,
	[REG_RTC_UPDATE0]    = MAX77686_RTC_UPDATE0,
	[REG_WTSR_SMPL_CNTL] = MAX77686_WTSR_SMPL_CNTL,
	[REG_RTC_SEC]        = MAX77686_RTC_SEC,
	[REG_RTC_MIN]        = MAX77686_RTC_MIN,
	[REG_RTC_HOUR]       = MAX77686_RTC_HOUR,
	[REG_RTC_WEEKDAY]    = MAX77686_RTC_WEEKDAY,
	[REG_RTC_MONTH]      = MAX77686_RTC_MONTH,
	[REG_RTC_YEAR]       = MAX77686_RTC_YEAR,
	[REG_RTC_DATE]       = MAX77686_RTC_DATE,
	[REG_ALARM1_SEC]     = MAX77686_ALARM1_SEC,
	[REG_ALARM1_MIN]     = MAX77686_ALARM1_MIN,
	[REG_ALARM1_HOUR]    = MAX77686_ALARM1_HOUR,
	[REG_ALARM1_WEEKDAY] = MAX77686_ALARM1_WEEKDAY,
	[REG_ALARM1_MONTH]   = MAX77686_ALARM1_MONTH,
	[REG_ALARM1_YEAR]    = MAX77686_ALARM1_YEAR,
	[REG_ALARM1_DATE]    = MAX77686_ALARM1_DATE,
	[REG_ALARM2_SEC]     = MAX77686_ALARM2_SEC,
	[REG_ALARM2_MIN]     = MAX77686_ALARM2_MIN,
	[REG_ALARM2_HOUR]    = MAX77686_ALARM2_HOUR,
	[REG_ALARM2_WEEKDAY] = MAX77686_ALARM2_WEEKDAY,
	[REG_ALARM2_MONTH]   = MAX77686_ALARM2_MONTH,
	[REG_ALARM2_YEAR]    = MAX77686_ALARM2_YEAR,
	[REG_ALARM2_DATE]    = MAX77686_ALARM2_DATE,
	[REG_RTC_AE1]	     = REG_RTC_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77686_rtc_irqs[] = अणु
	/* RTC पूर्णांकerrupts */
	REGMAP_IRQ_REG(0, 0, MAX77686_RTCINT_RTC60S_MSK),
	REGMAP_IRQ_REG(1, 0, MAX77686_RTCINT_RTCA1_MSK),
	REGMAP_IRQ_REG(2, 0, MAX77686_RTCINT_RTCA2_MSK),
	REGMAP_IRQ_REG(3, 0, MAX77686_RTCINT_SMPL_MSK),
	REGMAP_IRQ_REG(4, 0, MAX77686_RTCINT_RTC1S_MSK),
	REGMAP_IRQ_REG(5, 0, MAX77686_RTCINT_WTSR_MSK),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77686_rtc_irq_chip = अणु
	.name		= "max77686-rtc",
	.status_base	= MAX77686_RTC_INT,
	.mask_base	= MAX77686_RTC_INTM,
	.num_regs	= 1,
	.irqs		= max77686_rtc_irqs,
	.num_irqs	= ARRAY_SIZE(max77686_rtc_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77686_rtc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा max77686_rtc_driver_data max77686_drv_data = अणु
	.delay = 16000,
	.mask  = 0x7f,
	.map   = max77686_map,
	.alarm_enable_reg  = false,
	.rtc_irq_from_platक्रमm = false,
	.alarm_pending_status_reg = MAX77686_REG_STATUS2,
	.rtc_i2c_addr = MAX77686_I2C_ADDR_RTC,
	.rtc_irq_chip = &max77686_rtc_irq_chip,
	.regmap_config = &max77686_rtc_regmap_config,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77620_rtc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा max77686_rtc_driver_data max77620_drv_data = अणु
	.delay = 16000,
	.mask  = 0x7f,
	.map   = max77686_map,
	.alarm_enable_reg  = false,
	.rtc_irq_from_platक्रमm = true,
	.alarm_pending_status_reg = MAX77686_INVALID_REG,
	.rtc_i2c_addr = MAX77620_I2C_ADDR_RTC,
	.rtc_irq_chip = &max77686_rtc_irq_chip,
	.regmap_config = &max77620_rtc_regmap_config,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max77802_map[REG_RTC_END] = अणु
	[REG_RTC_CONTROLM]   = MAX77802_RTC_CONTROLM,
	[REG_RTC_CONTROL]    = MAX77802_RTC_CONTROL,
	[REG_RTC_UPDATE0]    = MAX77802_RTC_UPDATE0,
	[REG_WTSR_SMPL_CNTL] = MAX77802_WTSR_SMPL_CNTL,
	[REG_RTC_SEC]        = MAX77802_RTC_SEC,
	[REG_RTC_MIN]        = MAX77802_RTC_MIN,
	[REG_RTC_HOUR]       = MAX77802_RTC_HOUR,
	[REG_RTC_WEEKDAY]    = MAX77802_RTC_WEEKDAY,
	[REG_RTC_MONTH]      = MAX77802_RTC_MONTH,
	[REG_RTC_YEAR]       = MAX77802_RTC_YEAR,
	[REG_RTC_DATE]       = MAX77802_RTC_DATE,
	[REG_ALARM1_SEC]     = MAX77802_ALARM1_SEC,
	[REG_ALARM1_MIN]     = MAX77802_ALARM1_MIN,
	[REG_ALARM1_HOUR]    = MAX77802_ALARM1_HOUR,
	[REG_ALARM1_WEEKDAY] = MAX77802_ALARM1_WEEKDAY,
	[REG_ALARM1_MONTH]   = MAX77802_ALARM1_MONTH,
	[REG_ALARM1_YEAR]    = MAX77802_ALARM1_YEAR,
	[REG_ALARM1_DATE]    = MAX77802_ALARM1_DATE,
	[REG_ALARM2_SEC]     = MAX77802_ALARM2_SEC,
	[REG_ALARM2_MIN]     = MAX77802_ALARM2_MIN,
	[REG_ALARM2_HOUR]    = MAX77802_ALARM2_HOUR,
	[REG_ALARM2_WEEKDAY] = MAX77802_ALARM2_WEEKDAY,
	[REG_ALARM2_MONTH]   = MAX77802_ALARM2_MONTH,
	[REG_ALARM2_YEAR]    = MAX77802_ALARM2_YEAR,
	[REG_ALARM2_DATE]    = MAX77802_ALARM2_DATE,
	[REG_RTC_AE1]	     = MAX77802_RTC_AE1,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77802_rtc_irq_chip = अणु
	.name		= "max77802-rtc",
	.status_base	= MAX77802_RTC_INT,
	.mask_base	= MAX77802_RTC_INTM,
	.num_regs	= 1,
	.irqs		= max77686_rtc_irqs, /* same masks as 77686 */
	.num_irqs	= ARRAY_SIZE(max77686_rtc_irqs),
पूर्ण;

अटल स्थिर काष्ठा max77686_rtc_driver_data max77802_drv_data = अणु
	.delay = 200,
	.mask  = 0xff,
	.map   = max77802_map,
	.alarm_enable_reg  = true,
	.rtc_irq_from_platक्रमm = false,
	.alarm_pending_status_reg = MAX77686_REG_STATUS2,
	.rtc_i2c_addr = MAX77686_INVALID_I2C_ADDR,
	.rtc_irq_chip = &max77802_rtc_irq_chip,
पूर्ण;

अटल व्योम max77686_rtc_data_to_पंचांग(u8 *data, काष्ठा rtc_समय *पंचांग,
				    काष्ठा max77686_rtc_info *info)
अणु
	u8 mask = info->drv_data->mask;

	पंचांग->पंचांग_sec = data[RTC_SEC] & mask;
	पंचांग->पंचांग_min = data[RTC_MIN] & mask;
	अगर (info->rtc_24hr_mode) अणु
		पंचांग->पंचांग_hour = data[RTC_HOUR] & 0x1f;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_hour = data[RTC_HOUR] & 0x0f;
		अगर (data[RTC_HOUR] & HOUR_PM_MASK)
			पंचांग->पंचांग_hour += 12;
	पूर्ण

	/* Only a single bit is set in data[], so fls() would be equivalent */
	पंचांग->पंचांग_wday = ffs(data[RTC_WEEKDAY] & mask) - 1;
	पंचांग->पंचांग_mday = data[RTC_DATE] & 0x1f;
	पंचांग->पंचांग_mon = (data[RTC_MONTH] & 0x0f) - 1;
	पंचांग->पंचांग_year = data[RTC_YEAR] & mask;
	पंचांग->पंचांग_yday = 0;
	पंचांग->पंचांग_isdst = 0;

	/*
	 * MAX77686 uses 1 bit from sec/min/hour/etc RTC रेजिस्टरs and the
	 * year values are just 0..99 so add 100 to support up to 2099.
	 */
	अगर (!info->drv_data->alarm_enable_reg)
		पंचांग->पंचांग_year += 100;
पूर्ण

अटल पूर्णांक max77686_rtc_पंचांग_to_data(काष्ठा rtc_समय *पंचांग, u8 *data,
				   काष्ठा max77686_rtc_info *info)
अणु
	data[RTC_SEC] = पंचांग->पंचांग_sec;
	data[RTC_MIN] = पंचांग->पंचांग_min;
	data[RTC_HOUR] = पंचांग->पंचांग_hour;
	data[RTC_WEEKDAY] = 1 << पंचांग->पंचांग_wday;
	data[RTC_DATE] = पंचांग->पंचांग_mday;
	data[RTC_MONTH] = पंचांग->पंचांग_mon + 1;

	अगर (info->drv_data->alarm_enable_reg) अणु
		data[RTC_YEAR] = पंचांग->पंचांग_year;
		वापस 0;
	पूर्ण

	data[RTC_YEAR] = पंचांग->पंचांग_year > 100 ? (पंचांग->पंचांग_year - 100) : 0;

	अगर (पंचांग->पंचांग_year < 100) अणु
		dev_err(info->dev, "RTC cannot handle the year %d.\n",
			1900 + पंचांग->पंचांग_year);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77686_rtc_update(काष्ठा max77686_rtc_info *info,
			       क्रमागत MAX77686_RTC_OP op)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;
	अचिन्हित दीर्घ delay = info->drv_data->delay;

	अगर (op == MAX77686_RTC_WRITE)
		data = 1 << RTC_UDR_SHIFT;
	अन्यथा
		data = 1 << RTC_RBUDR_SHIFT;

	ret = regmap_update_bits(info->rtc_regmap,
				 info->drv_data->map[REG_RTC_UPDATE0],
				 data, data);
	अगर (ret < 0)
		dev_err(info->dev, "Fail to write update reg(ret=%d, data=0x%x)\n",
			ret, data);
	अन्यथा अणु
		/* Minimum delay required beक्रमe RTC update. */
		usleep_range(delay, delay * 2);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	mutex_lock(&info->lock);

	ret = max77686_rtc_update(info, MAX77686_RTC_READ);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_bulk_पढ़ो(info->rtc_regmap,
			       info->drv_data->map[REG_RTC_SEC],
			       data, ARRAY_SIZE(data));
	अगर (ret < 0) अणु
		dev_err(info->dev, "Fail to read time reg(%d)\n", ret);
		जाओ out;
	पूर्ण

	max77686_rtc_data_to_पंचांग(data, पंचांग, info);

out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	ret = max77686_rtc_पंचांग_to_data(पंचांग, data, info);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&info->lock);

	ret = regmap_bulk_ग_लिखो(info->rtc_regmap,
				info->drv_data->map[REG_RTC_SEC],
				data, ARRAY_SIZE(data));
	अगर (ret < 0) अणु
		dev_err(info->dev, "Fail to write time reg(%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = max77686_rtc_update(info, MAX77686_RTC_WRITE);

out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	अचिन्हित पूर्णांक val;
	स्थिर अचिन्हित पूर्णांक *map = info->drv_data->map;
	पूर्णांक i, ret;

	mutex_lock(&info->lock);

	ret = max77686_rtc_update(info, MAX77686_RTC_READ);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_bulk_पढ़ो(info->rtc_regmap, map[REG_ALARM1_SEC],
			       data, ARRAY_SIZE(data));
	अगर (ret < 0) अणु
		dev_err(info->dev, "Fail to read alarm reg(%d)\n", ret);
		जाओ out;
	पूर्ण

	max77686_rtc_data_to_पंचांग(data, &alrm->समय, info);

	alrm->enabled = 0;

	अगर (info->drv_data->alarm_enable_reg) अणु
		अगर (map[REG_RTC_AE1] == REG_RTC_NONE) अणु
			ret = -EINVAL;
			dev_err(info->dev,
				"alarm enable register not set(%d)\n", ret);
			जाओ out;
		पूर्ण

		ret = regmap_पढ़ो(info->rtc_regmap, map[REG_RTC_AE1], &val);
		अगर (ret < 0) अणु
			dev_err(info->dev,
				"fail to read alarm enable(%d)\n", ret);
			जाओ out;
		पूर्ण

		अगर (val)
			alrm->enabled = 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
			अगर (data[i] & ALARM_ENABLE_MASK) अणु
				alrm->enabled = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	alrm->pending = 0;

	अगर (info->drv_data->alarm_pending_status_reg == MAX77686_INVALID_REG)
		जाओ out;

	ret = regmap_पढ़ो(info->regmap,
			  info->drv_data->alarm_pending_status_reg, &val);
	अगर (ret < 0) अणु
		dev_err(info->dev,
			"Fail to read alarm pending status reg(%d)\n", ret);
		जाओ out;
	पूर्ण

	अगर (val & (1 << 4)) /* RTCA1 */
		alrm->pending = 1;

out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_stop_alarm(काष्ठा max77686_rtc_info *info)
अणु
	u8 data[RTC_NR_TIME];
	पूर्णांक ret, i;
	काष्ठा rtc_समय पंचांग;
	स्थिर अचिन्हित पूर्णांक *map = info->drv_data->map;

	अगर (!mutex_is_locked(&info->lock))
		dev_warn(info->dev, "%s: should have mutex locked\n", __func__);

	ret = max77686_rtc_update(info, MAX77686_RTC_READ);
	अगर (ret < 0)
		जाओ out;

	अगर (info->drv_data->alarm_enable_reg) अणु
		अगर (map[REG_RTC_AE1] == REG_RTC_NONE) अणु
			ret = -EINVAL;
			dev_err(info->dev,
				"alarm enable register not set(%d)\n", ret);
			जाओ out;
		पूर्ण

		ret = regmap_ग_लिखो(info->rtc_regmap, map[REG_RTC_AE1], 0);
	पूर्ण अन्यथा अणु
		ret = regmap_bulk_पढ़ो(info->rtc_regmap, map[REG_ALARM1_SEC],
				       data, ARRAY_SIZE(data));
		अगर (ret < 0) अणु
			dev_err(info->dev, "Fail to read alarm reg(%d)\n", ret);
			जाओ out;
		पूर्ण

		max77686_rtc_data_to_पंचांग(data, &पंचांग, info);

		क्रम (i = 0; i < ARRAY_SIZE(data); i++)
			data[i] &= ~ALARM_ENABLE_MASK;

		ret = regmap_bulk_ग_लिखो(info->rtc_regmap, map[REG_ALARM1_SEC],
					data, ARRAY_SIZE(data));
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(info->dev, "Fail to write alarm reg(%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = max77686_rtc_update(info, MAX77686_RTC_WRITE);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_start_alarm(काष्ठा max77686_rtc_info *info)
अणु
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;
	काष्ठा rtc_समय पंचांग;
	स्थिर अचिन्हित पूर्णांक *map = info->drv_data->map;

	अगर (!mutex_is_locked(&info->lock))
		dev_warn(info->dev, "%s: should have mutex locked\n", __func__);

	ret = max77686_rtc_update(info, MAX77686_RTC_READ);
	अगर (ret < 0)
		जाओ out;

	अगर (info->drv_data->alarm_enable_reg) अणु
		ret = regmap_ग_लिखो(info->rtc_regmap, map[REG_RTC_AE1],
				   MAX77802_ALARM_ENABLE_VALUE);
	पूर्ण अन्यथा अणु
		ret = regmap_bulk_पढ़ो(info->rtc_regmap, map[REG_ALARM1_SEC],
				       data, ARRAY_SIZE(data));
		अगर (ret < 0) अणु
			dev_err(info->dev, "Fail to read alarm reg(%d)\n", ret);
			जाओ out;
		पूर्ण

		max77686_rtc_data_to_पंचांग(data, &पंचांग, info);

		data[RTC_SEC] |= (1 << ALARM_ENABLE_SHIFT);
		data[RTC_MIN] |= (1 << ALARM_ENABLE_SHIFT);
		data[RTC_HOUR] |= (1 << ALARM_ENABLE_SHIFT);
		data[RTC_WEEKDAY] &= ~ALARM_ENABLE_MASK;
		अगर (data[RTC_MONTH] & 0xf)
			data[RTC_MONTH] |= (1 << ALARM_ENABLE_SHIFT);
		अगर (data[RTC_YEAR] & info->drv_data->mask)
			data[RTC_YEAR] |= (1 << ALARM_ENABLE_SHIFT);
		अगर (data[RTC_DATE] & 0x1f)
			data[RTC_DATE] |= (1 << ALARM_ENABLE_SHIFT);

		ret = regmap_bulk_ग_लिखो(info->rtc_regmap, map[REG_ALARM1_SEC],
					data, ARRAY_SIZE(data));
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(info->dev, "Fail to write alarm reg(%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = max77686_rtc_update(info, MAX77686_RTC_WRITE);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	पूर्णांक ret;

	ret = max77686_rtc_पंचांग_to_data(&alrm->समय, data, info);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&info->lock);

	ret = max77686_rtc_stop_alarm(info);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_bulk_ग_लिखो(info->rtc_regmap,
				info->drv_data->map[REG_ALARM1_SEC],
				data, ARRAY_SIZE(data));

	अगर (ret < 0) अणु
		dev_err(info->dev, "Fail to write alarm reg(%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = max77686_rtc_update(info, MAX77686_RTC_WRITE);
	अगर (ret < 0)
		जाओ out;

	अगर (alrm->enabled)
		ret = max77686_rtc_start_alarm(info);
out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_alarm_irq_enable(काष्ठा device *dev,
					 अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&info->lock);
	अगर (enabled)
		ret = max77686_rtc_start_alarm(info);
	अन्यथा
		ret = max77686_rtc_stop_alarm(info);
	mutex_unlock(&info->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t max77686_rtc_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77686_rtc_info *info = data;

	dev_dbg(info->dev, "RTC alarm IRQ: %d\n", irq);

	rtc_update_irq(info->rtc_dev, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max77686_rtc_ops = अणु
	.पढ़ो_समय = max77686_rtc_पढ़ो_समय,
	.set_समय = max77686_rtc_set_समय,
	.पढ़ो_alarm = max77686_rtc_पढ़ो_alarm,
	.set_alarm = max77686_rtc_set_alarm,
	.alarm_irq_enable = max77686_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक max77686_rtc_init_reg(काष्ठा max77686_rtc_info *info)
अणु
	u8 data[2];
	पूर्णांक ret;

	/* Set RTC control रेजिस्टर : Binary mode, 24hour mकरोe */
	data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);
	data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);

	info->rtc_24hr_mode = 1;

	ret = regmap_bulk_ग_लिखो(info->rtc_regmap,
				info->drv_data->map[REG_RTC_CONTROLM],
				data, ARRAY_SIZE(data));
	अगर (ret < 0) अणु
		dev_err(info->dev, "Fail to write controlm reg(%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = max77686_rtc_update(info, MAX77686_RTC_WRITE);
	वापस ret;
पूर्ण

अटल पूर्णांक max77686_init_rtc_regmap(काष्ठा max77686_rtc_info *info)
अणु
	काष्ठा device *parent = info->dev->parent;
	काष्ठा i2c_client *parent_i2c = to_i2c_client(parent);
	पूर्णांक ret;

	अगर (info->drv_data->rtc_irq_from_platक्रमm) अणु
		काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(info->dev);

		info->rtc_irq = platक्रमm_get_irq(pdev, 0);
		अगर (info->rtc_irq < 0)
			वापस info->rtc_irq;
	पूर्ण अन्यथा अणु
		info->rtc_irq =  parent_i2c->irq;
	पूर्ण

	info->regmap = dev_get_regmap(parent, शून्य);
	अगर (!info->regmap) अणु
		dev_err(info->dev, "Failed to get rtc regmap\n");
		वापस -ENODEV;
	पूर्ण

	अगर (info->drv_data->rtc_i2c_addr == MAX77686_INVALID_I2C_ADDR) अणु
		info->rtc_regmap = info->regmap;
		जाओ add_rtc_irq;
	पूर्ण

	info->rtc = devm_i2c_new_dummy_device(info->dev, parent_i2c->adapter,
					      info->drv_data->rtc_i2c_addr);
	अगर (IS_ERR(info->rtc)) अणु
		dev_err(info->dev, "Failed to allocate I2C device for RTC\n");
		वापस PTR_ERR(info->rtc);
	पूर्ण

	info->rtc_regmap = devm_regmap_init_i2c(info->rtc,
						info->drv_data->regmap_config);
	अगर (IS_ERR(info->rtc_regmap)) अणु
		ret = PTR_ERR(info->rtc_regmap);
		dev_err(info->dev, "Failed to allocate RTC regmap: %d\n", ret);
		वापस ret;
	पूर्ण

add_rtc_irq:
	ret = regmap_add_irq_chip(info->rtc_regmap, info->rtc_irq,
				  IRQF_TRIGGER_FALLING | IRQF_ONESHOT |
				  IRQF_SHARED, 0, info->drv_data->rtc_irq_chip,
				  &info->rtc_irq_data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "Failed to add RTC irq chip: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77686_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77686_rtc_info *info;
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max77686_rtc_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	mutex_init(&info->lock);
	info->dev = &pdev->dev;
	info->drv_data = (स्थिर काष्ठा max77686_rtc_driver_data *)
		id->driver_data;

	ret = max77686_init_rtc_regmap(info);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, info);

	ret = max77686_rtc_init_reg(info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to initialize RTC reg:%d\n", ret);
		जाओ err_rtc;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);

	info->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, id->name,
					&max77686_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(info->rtc_dev)) अणु
		ret = PTR_ERR(info->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		अगर (ret == 0)
			ret = -EINVAL;
		जाओ err_rtc;
	पूर्ण

	info->virq = regmap_irq_get_virq(info->rtc_irq_data,
					 MAX77686_RTCIRQ_RTCA1);
	अगर (info->virq <= 0) अणु
		ret = -ENXIO;
		जाओ err_rtc;
	पूर्ण

	ret = request_thपढ़ोed_irq(info->virq, शून्य, max77686_rtc_alarm_irq, 0,
				   "rtc-alarm1", info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			info->virq, ret);
		जाओ err_rtc;
	पूर्ण

	वापस 0;

err_rtc:
	regmap_del_irq_chip(info->rtc_irq, info->rtc_irq_data);

	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77686_rtc_info *info = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(info->virq, info);
	regmap_del_irq_chip(info->rtc_irq, info->rtc_irq_data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max77686_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (device_may_wakeup(dev)) अणु
		काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);

		ret = enable_irq_wake(info->virq);
	पूर्ण

	/*
	 * If the मुख्य IRQ (not भव) is the parent IRQ, then it must be
	 * disabled during suspend because अगर it happens जबतक suspended it
	 * will be handled beक्रमe resuming I2C.
	 *
	 * Since Main IRQ is shared, all its users should disable it to be sure
	 * it won't fire जबतक one of them is still suspended.
	 */
	अगर (!info->drv_data->rtc_irq_from_platक्रमm)
		disable_irq(info->rtc_irq);

	वापस ret;
पूर्ण

अटल पूर्णांक max77686_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);

	अगर (!info->drv_data->rtc_irq_from_platक्रमm)
		enable_irq(info->rtc_irq);

	अगर (device_may_wakeup(dev)) अणु
		काष्ठा max77686_rtc_info *info = dev_get_drvdata(dev);

		वापस disable_irq_wake(info->virq);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(max77686_rtc_pm_ops,
			 max77686_rtc_suspend, max77686_rtc_resume);

अटल स्थिर काष्ठा platक्रमm_device_id rtc_id[] = अणु
	अणु "max77686-rtc", .driver_data = (kernel_uदीर्घ_t)&max77686_drv_data, पूर्ण,
	अणु "max77802-rtc", .driver_data = (kernel_uदीर्घ_t)&max77802_drv_data, पूर्ण,
	अणु "max77620-rtc", .driver_data = (kernel_uदीर्घ_t)&max77620_drv_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rtc_id);

अटल काष्ठा platक्रमm_driver max77686_rtc_driver = अणु
	.driver		= अणु
		.name	= "max77686-rtc",
		.pm	= &max77686_rtc_pm_ops,
	पूर्ण,
	.probe		= max77686_rtc_probe,
	.हटाओ		= max77686_rtc_हटाओ,
	.id_table	= rtc_id,
पूर्ण;

module_platक्रमm_driver(max77686_rtc_driver);

MODULE_DESCRIPTION("Maxim MAX77686 RTC driver");
MODULE_AUTHOR("Chiwoong Byun <woong.byun@samsung.com>");
MODULE_LICENSE("GPL");
