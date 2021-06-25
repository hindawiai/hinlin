<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC driver क्रम the Micro Crystal RV3028
 *
 * Copyright (C) 2019 Micro Crystal SA
 *
 * Alexandre Belloni <alexandre.belloni@bootlin.com>
 *
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/bcd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>

#घोषणा RV3028_SEC			0x00
#घोषणा RV3028_MIN			0x01
#घोषणा RV3028_HOUR			0x02
#घोषणा RV3028_WDAY			0x03
#घोषणा RV3028_DAY			0x04
#घोषणा RV3028_MONTH			0x05
#घोषणा RV3028_YEAR			0x06
#घोषणा RV3028_ALARM_MIN		0x07
#घोषणा RV3028_ALARM_HOUR		0x08
#घोषणा RV3028_ALARM_DAY		0x09
#घोषणा RV3028_STATUS			0x0E
#घोषणा RV3028_CTRL1			0x0F
#घोषणा RV3028_CTRL2			0x10
#घोषणा RV3028_EVT_CTRL			0x13
#घोषणा RV3028_TS_COUNT			0x14
#घोषणा RV3028_TS_SEC			0x15
#घोषणा RV3028_RAM1			0x1F
#घोषणा RV3028_EEPROM_ADDR		0x25
#घोषणा RV3028_EEPROM_DATA		0x26
#घोषणा RV3028_EEPROM_CMD		0x27
#घोषणा RV3028_CLKOUT			0x35
#घोषणा RV3028_OFFSET			0x36
#घोषणा RV3028_BACKUP			0x37

#घोषणा RV3028_STATUS_PORF		BIT(0)
#घोषणा RV3028_STATUS_EVF		BIT(1)
#घोषणा RV3028_STATUS_AF		BIT(2)
#घोषणा RV3028_STATUS_TF		BIT(3)
#घोषणा RV3028_STATUS_UF		BIT(4)
#घोषणा RV3028_STATUS_BSF		BIT(5)
#घोषणा RV3028_STATUS_CLKF		BIT(6)
#घोषणा RV3028_STATUS_EEBUSY		BIT(7)

#घोषणा RV3028_CLKOUT_FD_MASK		GENMASK(2, 0)
#घोषणा RV3028_CLKOUT_PORIE		BIT(3)
#घोषणा RV3028_CLKOUT_CLKSY		BIT(6)
#घोषणा RV3028_CLKOUT_CLKOE		BIT(7)

#घोषणा RV3028_CTRL1_EERD		BIT(3)
#घोषणा RV3028_CTRL1_WADA		BIT(5)

#घोषणा RV3028_CTRL2_RESET		BIT(0)
#घोषणा RV3028_CTRL2_12_24		BIT(1)
#घोषणा RV3028_CTRL2_EIE		BIT(2)
#घोषणा RV3028_CTRL2_AIE		BIT(3)
#घोषणा RV3028_CTRL2_TIE		BIT(4)
#घोषणा RV3028_CTRL2_UIE		BIT(5)
#घोषणा RV3028_CTRL2_TSE		BIT(7)

#घोषणा RV3028_EVT_CTRL_TSR		BIT(2)

#घोषणा RV3028_EEPROM_CMD_UPDATE	0x11
#घोषणा RV3028_EEPROM_CMD_WRITE		0x21
#घोषणा RV3028_EEPROM_CMD_READ		0x22

#घोषणा RV3028_EEBUSY_POLL		10000
#घोषणा RV3028_EEBUSY_TIMEOUT		100000

#घोषणा RV3028_BACKUP_TCE		BIT(5)
#घोषणा RV3028_BACKUP_TCR_MASK		GENMASK(1,0)

#घोषणा OFFSET_STEP_PPT			953674

क्रमागत rv3028_type अणु
	rv_3028,
पूर्ण;

काष्ठा rv3028_data अणु
	काष्ठा regmap *regmap;
	काष्ठा rtc_device *rtc;
	क्रमागत rv3028_type type;
#अगर_घोषित CONFIG_COMMON_CLK
	काष्ठा clk_hw clkout_hw;
#पूर्ण_अगर
पूर्ण;

अटल u16 rv3028_trickle_resistors[] = अणु3000, 5000, 9000, 15000पूर्ण;

अटल sमाप_प्रकार बारtamp0_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev->parent);

	regmap_update_bits(rv3028->regmap, RV3028_EVT_CTRL, RV3028_EVT_CTRL_TSR,
			   RV3028_EVT_CTRL_TSR);

	वापस count;
पूर्ण;

अटल sमाप_प्रकार बारtamp0_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev->parent);
	काष्ठा rtc_समय पंचांग;
	पूर्णांक ret, count;
	u8 date[6];

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_TS_COUNT, &count);
	अगर (ret)
		वापस ret;

	अगर (!count)
		वापस 0;

	ret = regmap_bulk_पढ़ो(rv3028->regmap, RV3028_TS_SEC, date,
			       माप(date));
	अगर (ret)
		वापस ret;

	पंचांग.पंचांग_sec = bcd2bin(date[0]);
	पंचांग.पंचांग_min = bcd2bin(date[1]);
	पंचांग.पंचांग_hour = bcd2bin(date[2]);
	पंचांग.पंचांग_mday = bcd2bin(date[3]);
	पंचांग.पंचांग_mon = bcd2bin(date[4]) - 1;
	पंचांग.पंचांग_year = bcd2bin(date[5]) + 100;

	ret = rtc_valid_पंचांग(&पंचांग);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)rtc_पंचांग_to_समय64(&पंचांग));
पूर्ण;

अटल DEVICE_ATTR_RW(बारtamp0);

अटल sमाप_प्रकार बारtamp0_count_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev->parent);
	पूर्णांक ret, count;

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_TS_COUNT, &count);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", count);
पूर्ण;

अटल DEVICE_ATTR_RO(बारtamp0_count);

अटल काष्ठा attribute *rv3028_attrs[] = अणु
	&dev_attr_बारtamp0.attr,
	&dev_attr_बारtamp0_count.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rv3028_attr_group = अणु
	.attrs	= rv3028_attrs,
पूर्ण;

अटल पूर्णांक rv3028_निकास_eerd(काष्ठा rv3028_data *rv3028, u32 eerd)
अणु
	अगर (eerd)
		वापस 0;

	वापस regmap_update_bits(rv3028->regmap, RV3028_CTRL1, RV3028_CTRL1_EERD, 0);
पूर्ण

अटल पूर्णांक rv3028_enter_eerd(काष्ठा rv3028_data *rv3028, u32 *eerd)
अणु
	u32 ctrl1, status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_CTRL1, &ctrl1);
	अगर (ret)
		वापस ret;

	*eerd = ctrl1 & RV3028_CTRL1_EERD;
	अगर (*eerd)
		वापस 0;

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL1,
				 RV3028_CTRL1_EERD, RV3028_CTRL1_EERD);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(rv3028->regmap, RV3028_STATUS, status,
				       !(status & RV3028_STATUS_EEBUSY),
				       RV3028_EEBUSY_POLL, RV3028_EEBUSY_TIMEOUT);
	अगर (ret) अणु
		rv3028_निकास_eerd(rv3028, *eerd);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv3028_update_eeprom(काष्ठा rv3028_data *rv3028, u32 eerd)
अणु
	u32 status;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_CMD, 0x0);
	अगर (ret)
		जाओ निकास_eerd;

	ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_CMD, RV3028_EEPROM_CMD_UPDATE);
	अगर (ret)
		जाओ निकास_eerd;

	usleep_range(63000, RV3028_EEBUSY_TIMEOUT);

	ret = regmap_पढ़ो_poll_समयout(rv3028->regmap, RV3028_STATUS, status,
				       !(status & RV3028_STATUS_EEBUSY),
				       RV3028_EEBUSY_POLL, RV3028_EEBUSY_TIMEOUT);

निकास_eerd:
	rv3028_निकास_eerd(rv3028, eerd);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3028_update_cfg(काष्ठा rv3028_data *rv3028, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	u32 eerd;
	पूर्णांक ret;

	ret = rv3028_enter_eerd(rv3028, &eerd);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(rv3028->regmap, reg, mask, val);
	अगर (ret) अणु
		rv3028_निकास_eerd(rv3028, eerd);
		वापस ret;
	पूर्ण

	वापस rv3028_update_eeprom(rv3028, eerd);
पूर्ण

अटल irqवापस_t rv3028_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rv3028_data *rv3028 = dev_id;
	अचिन्हित दीर्घ events = 0;
	u32 status = 0, ctrl = 0;

	अगर (regmap_पढ़ो(rv3028->regmap, RV3028_STATUS, &status) < 0 ||
	   status == 0) अणु
		वापस IRQ_NONE;
	पूर्ण

	status &= ~RV3028_STATUS_PORF;

	अगर (status & RV3028_STATUS_TF) अणु
		status |= RV3028_STATUS_TF;
		ctrl |= RV3028_CTRL2_TIE;
		events |= RTC_PF;
	पूर्ण

	अगर (status & RV3028_STATUS_AF) अणु
		status |= RV3028_STATUS_AF;
		ctrl |= RV3028_CTRL2_AIE;
		events |= RTC_AF;
	पूर्ण

	अगर (status & RV3028_STATUS_UF) अणु
		status |= RV3028_STATUS_UF;
		ctrl |= RV3028_CTRL2_UIE;
		events |= RTC_UF;
	पूर्ण

	अगर (events) अणु
		rtc_update_irq(rv3028->rtc, 1, events);
		regmap_update_bits(rv3028->regmap, RV3028_STATUS, status, 0);
		regmap_update_bits(rv3028->regmap, RV3028_CTRL2, ctrl, 0);
	पूर्ण

	अगर (status & RV3028_STATUS_EVF) अणु
		sysfs_notअगरy(&rv3028->rtc->dev.kobj, शून्य,
			     dev_attr_बारtamp0.attr.name);
		dev_warn(&rv3028->rtc->dev, "event detected");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rv3028_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	u8 date[7];
	पूर्णांक ret, status;

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	अगर (status & RV3028_STATUS_PORF)
		वापस -EINVAL;

	ret = regmap_bulk_पढ़ो(rv3028->regmap, RV3028_SEC, date, माप(date));
	अगर (ret)
		वापस ret;

	पंचांग->पंचांग_sec  = bcd2bin(date[RV3028_SEC] & 0x7f);
	पंचांग->पंचांग_min  = bcd2bin(date[RV3028_MIN] & 0x7f);
	पंचांग->पंचांग_hour = bcd2bin(date[RV3028_HOUR] & 0x3f);
	पंचांग->पंचांग_wday = date[RV3028_WDAY] & 0x7f;
	पंचांग->पंचांग_mday = bcd2bin(date[RV3028_DAY] & 0x3f);
	पंचांग->पंचांग_mon  = bcd2bin(date[RV3028_MONTH] & 0x1f) - 1;
	पंचांग->पंचांग_year = bcd2bin(date[RV3028_YEAR]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3028_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	u8 date[7];
	पूर्णांक ret;

	date[RV3028_SEC]   = bin2bcd(पंचांग->पंचांग_sec);
	date[RV3028_MIN]   = bin2bcd(पंचांग->पंचांग_min);
	date[RV3028_HOUR]  = bin2bcd(पंचांग->पंचांग_hour);
	date[RV3028_WDAY]  = पंचांग->पंचांग_wday;
	date[RV3028_DAY]   = bin2bcd(पंचांग->पंचांग_mday);
	date[RV3028_MONTH] = bin2bcd(पंचांग->पंचांग_mon + 1);
	date[RV3028_YEAR]  = bin2bcd(पंचांग->पंचांग_year - 100);

	/*
	 * Writing to the Seconds रेजिस्टर has the same effect as setting RESET
	 * bit to 1
	 */
	ret = regmap_bulk_ग_लिखो(rv3028->regmap, RV3028_SEC, date,
				माप(date));
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(rv3028->regmap, RV3028_STATUS,
				 RV3028_STATUS_PORF, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3028_get_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	पूर्णांक status, ctrl, ret;

	ret = regmap_bulk_पढ़ो(rv3028->regmap, RV3028_ALARM_MIN, alarmvals,
			       माप(alarmvals));
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_CTRL2, &ctrl);
	अगर (ret < 0)
		वापस ret;

	alrm->समय.पंचांग_sec  = 0;
	alrm->समय.पंचांग_min  = bcd2bin(alarmvals[0] & 0x7f);
	alrm->समय.पंचांग_hour = bcd2bin(alarmvals[1] & 0x3f);
	alrm->समय.पंचांग_mday = bcd2bin(alarmvals[2] & 0x3f);

	alrm->enabled = !!(ctrl & RV3028_CTRL2_AIE);
	alrm->pending = (status & RV3028_STATUS_AF) && alrm->enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3028_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	u8 ctrl = 0;
	पूर्णांक ret;

	/* The alarm has no seconds, round up to nearest minute */
	अगर (alrm->समय.पंचांग_sec) अणु
		समय64_t alarm_समय = rtc_पंचांग_to_समय64(&alrm->समय);

		alarm_समय += 60 - alrm->समय.पंचांग_sec;
		rtc_समय64_to_पंचांग(alarm_समय, &alrm->समय);
	पूर्ण

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL2,
				 RV3028_CTRL2_AIE | RV3028_CTRL2_UIE, 0);
	अगर (ret)
		वापस ret;

	alarmvals[0] = bin2bcd(alrm->समय.पंचांग_min);
	alarmvals[1] = bin2bcd(alrm->समय.पंचांग_hour);
	alarmvals[2] = bin2bcd(alrm->समय.पंचांग_mday);

	ret = regmap_update_bits(rv3028->regmap, RV3028_STATUS,
				 RV3028_STATUS_AF, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_ग_लिखो(rv3028->regmap, RV3028_ALARM_MIN, alarmvals,
				माप(alarmvals));
	अगर (ret)
		वापस ret;

	अगर (alrm->enabled) अणु
		अगर (rv3028->rtc->uie_rtस_समयr.enabled)
			ctrl |= RV3028_CTRL2_UIE;
		अगर (rv3028->rtc->aie_समयr.enabled)
			ctrl |= RV3028_CTRL2_AIE;
	पूर्ण

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL2,
				 RV3028_CTRL2_UIE | RV3028_CTRL2_AIE, ctrl);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3028_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	पूर्णांक ctrl = 0, ret;

	अगर (enabled) अणु
		अगर (rv3028->rtc->uie_rtस_समयr.enabled)
			ctrl |= RV3028_CTRL2_UIE;
		अगर (rv3028->rtc->aie_समयr.enabled)
			ctrl |= RV3028_CTRL2_AIE;
	पूर्ण

	ret = regmap_update_bits(rv3028->regmap, RV3028_STATUS,
				 RV3028_STATUS_AF | RV3028_STATUS_UF, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL2,
				 RV3028_CTRL2_UIE | RV3028_CTRL2_AIE, ctrl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3028_पढ़ो_offset(काष्ठा device *dev, दीर्घ *offset)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	पूर्णांक ret, value, steps;

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_OFFSET, &value);
	अगर (ret < 0)
		वापस ret;

	steps = sign_extend32(value << 1, 8);

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_BACKUP, &value);
	अगर (ret < 0)
		वापस ret;

	steps += value >> 7;

	*offset = DIV_ROUND_CLOSEST(steps * OFFSET_STEP_PPT, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक rv3028_set_offset(काष्ठा device *dev, दीर्घ offset)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	u32 eerd;
	पूर्णांक ret;

	offset = clamp(offset, -244141L, 243187L) * 1000;
	offset = DIV_ROUND_CLOSEST(offset, OFFSET_STEP_PPT);

	ret = rv3028_enter_eerd(rv3028, &eerd);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(rv3028->regmap, RV3028_OFFSET, offset >> 1);
	अगर (ret < 0)
		जाओ निकास_eerd;

	ret = regmap_update_bits(rv3028->regmap, RV3028_BACKUP, BIT(7),
				 offset << 7);
	अगर (ret < 0)
		जाओ निकास_eerd;

	वापस rv3028_update_eeprom(rv3028, eerd);

निकास_eerd:
	rv3028_निकास_eerd(rv3028, eerd);

	वापस ret;

पूर्ण

अटल पूर्णांक rv3028_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rv3028_data *rv3028 = dev_get_drvdata(dev);
	पूर्णांक status, ret = 0;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		ret = regmap_पढ़ो(rv3028->regmap, RV3028_STATUS, &status);
		अगर (ret < 0)
			वापस ret;

		status = status & RV3028_STATUS_PORF ? RTC_VL_DATA_INVALID : 0;
		वापस put_user(status, (अचिन्हित पूर्णांक __user *)arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक rv3028_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	वापस regmap_bulk_ग_लिखो(priv, RV3028_RAM1 + offset, val, bytes);
पूर्ण

अटल पूर्णांक rv3028_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार bytes)
अणु
	वापस regmap_bulk_पढ़ो(priv, RV3028_RAM1 + offset, val, bytes);
पूर्ण

अटल पूर्णांक rv3028_eeprom_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			       माप_प्रकार bytes)
अणु
	काष्ठा rv3028_data *rv3028 = priv;
	u32 status, eerd;
	पूर्णांक i, ret;
	u8 *buf = val;

	ret = rv3028_enter_eerd(rv3028, &eerd);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < bytes; i++) अणु
		ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_ADDR, offset + i);
		अगर (ret)
			जाओ restore_eerd;

		ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_DATA, buf[i]);
		अगर (ret)
			जाओ restore_eerd;

		ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_CMD, 0x0);
		अगर (ret)
			जाओ restore_eerd;

		ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_CMD,
				   RV3028_EEPROM_CMD_WRITE);
		अगर (ret)
			जाओ restore_eerd;

		usleep_range(RV3028_EEBUSY_POLL, RV3028_EEBUSY_TIMEOUT);

		ret = regmap_पढ़ो_poll_समयout(rv3028->regmap, RV3028_STATUS, status,
					       !(status & RV3028_STATUS_EEBUSY),
					       RV3028_EEBUSY_POLL,
					       RV3028_EEBUSY_TIMEOUT);
		अगर (ret)
			जाओ restore_eerd;
	पूर्ण

restore_eerd:
	rv3028_निकास_eerd(rv3028, eerd);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3028_eeprom_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा rv3028_data *rv3028 = priv;
	u32 status, eerd, data;
	पूर्णांक i, ret;
	u8 *buf = val;

	ret = rv3028_enter_eerd(rv3028, &eerd);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < bytes; i++) अणु
		ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_ADDR, offset + i);
		अगर (ret)
			जाओ restore_eerd;

		ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_CMD, 0x0);
		अगर (ret)
			जाओ restore_eerd;

		ret = regmap_ग_लिखो(rv3028->regmap, RV3028_EEPROM_CMD,
				   RV3028_EEPROM_CMD_READ);
		अगर (ret)
			जाओ restore_eerd;

		ret = regmap_पढ़ो_poll_समयout(rv3028->regmap, RV3028_STATUS, status,
					       !(status & RV3028_STATUS_EEBUSY),
					       RV3028_EEBUSY_POLL,
					       RV3028_EEBUSY_TIMEOUT);
		अगर (ret)
			जाओ restore_eerd;

		ret = regmap_पढ़ो(rv3028->regmap, RV3028_EEPROM_DATA, &data);
		अगर (ret)
			जाओ restore_eerd;
		buf[i] = data;
	पूर्ण

restore_eerd:
	rv3028_निकास_eerd(rv3028, eerd);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
#घोषणा clkout_hw_to_rv3028(hw) container_of(hw, काष्ठा rv3028_data, clkout_hw)

अटल पूर्णांक clkout_rates[] = अणु
	32768,
	8192,
	1024,
	64,
	32,
	1,
पूर्ण;

अटल अचिन्हित दीर्घ rv3028_clkout_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक clkout, ret;
	काष्ठा rv3028_data *rv3028 = clkout_hw_to_rv3028(hw);

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_CLKOUT, &clkout);
	अगर (ret < 0)
		वापस 0;

	clkout &= RV3028_CLKOUT_FD_MASK;
	वापस clkout_rates[clkout];
पूर्ण

अटल दीर्घ rv3028_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(clkout_rates); i++)
		अगर (clkout_rates[i] <= rate)
			वापस clkout_rates[i];

	वापस 0;
पूर्ण

अटल पूर्णांक rv3028_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक i, ret;
	u32 enabled;
	काष्ठा rv3028_data *rv3028 = clkout_hw_to_rv3028(hw);

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_CLKOUT, &enabled);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(rv3028->regmap, RV3028_CLKOUT, 0x0);
	अगर (ret < 0)
		वापस ret;

	enabled &= RV3028_CLKOUT_CLKOE;

	क्रम (i = 0; i < ARRAY_SIZE(clkout_rates); i++)
		अगर (clkout_rates[i] == rate)
			वापस rv3028_update_cfg(rv3028, RV3028_CLKOUT, 0xff,
						 RV3028_CLKOUT_CLKSY | enabled | i);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rv3028_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rv3028_data *rv3028 = clkout_hw_to_rv3028(hw);

	वापस regmap_ग_लिखो(rv3028->regmap, RV3028_CLKOUT,
			    RV3028_CLKOUT_CLKSY | RV3028_CLKOUT_CLKOE);
पूर्ण

अटल व्योम rv3028_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rv3028_data *rv3028 = clkout_hw_to_rv3028(hw);

	regmap_ग_लिखो(rv3028->regmap, RV3028_CLKOUT, 0x0);
	regmap_update_bits(rv3028->regmap, RV3028_STATUS,
			   RV3028_STATUS_CLKF, 0);
पूर्ण

अटल पूर्णांक rv3028_clkout_is_prepared(काष्ठा clk_hw *hw)
अणु
	पूर्णांक clkout, ret;
	काष्ठा rv3028_data *rv3028 = clkout_hw_to_rv3028(hw);

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_CLKOUT, &clkout);
	अगर (ret < 0)
		वापस ret;

	वापस !!(clkout & RV3028_CLKOUT_CLKOE);
पूर्ण

अटल स्थिर काष्ठा clk_ops rv3028_clkout_ops = अणु
	.prepare = rv3028_clkout_prepare,
	.unprepare = rv3028_clkout_unprepare,
	.is_prepared = rv3028_clkout_is_prepared,
	.recalc_rate = rv3028_clkout_recalc_rate,
	.round_rate = rv3028_clkout_round_rate,
	.set_rate = rv3028_clkout_set_rate,
पूर्ण;

अटल पूर्णांक rv3028_clkout_रेजिस्टर_clk(काष्ठा rv3028_data *rv3028,
				      काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	काष्ठा device_node *node = client->dev.of_node;

	ret = regmap_update_bits(rv3028->regmap, RV3028_STATUS,
				 RV3028_STATUS_CLKF, 0);
	अगर (ret < 0)
		वापस ret;

	init.name = "rv3028-clkout";
	init.ops = &rv3028_clkout_ops;
	init.flags = 0;
	init.parent_names = शून्य;
	init.num_parents = 0;
	rv3028->clkout_hw.init = &init;

	/* optional override of the घड़ीname */
	of_property_पढ़ो_string(node, "clock-output-names", &init.name);

	/* रेजिस्टर the घड़ी */
	clk = devm_clk_रेजिस्टर(&client->dev, &rv3028->clkout_hw);
	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा rtc_class_ops rv3028_rtc_ops = अणु
	.पढ़ो_समय = rv3028_get_समय,
	.set_समय = rv3028_set_समय,
	.पढ़ो_alarm = rv3028_get_alarm,
	.set_alarm = rv3028_set_alarm,
	.alarm_irq_enable = rv3028_alarm_irq_enable,
	.पढ़ो_offset = rv3028_पढ़ो_offset,
	.set_offset = rv3028_set_offset,
	.ioctl = rv3028_ioctl,
पूर्ण;

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
        .reg_bits = 8,
        .val_bits = 8,
        .max_रेजिस्टर = 0x37,
पूर्ण;

अटल पूर्णांक rv3028_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा rv3028_data *rv3028;
	पूर्णांक ret, status;
	u32 ohms;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "rv3028_nvram",
		.word_size = 1,
		.stride = 1,
		.size = 2,
		.type = NVMEM_TYPE_BATTERY_BACKED,
		.reg_पढ़ो = rv3028_nvram_पढ़ो,
		.reg_ग_लिखो = rv3028_nvram_ग_लिखो,
	पूर्ण;
	काष्ठा nvmem_config eeprom_cfg = अणु
		.name = "rv3028_eeprom",
		.word_size = 1,
		.stride = 1,
		.size = 43,
		.type = NVMEM_TYPE_EEPROM,
		.reg_पढ़ो = rv3028_eeprom_पढ़ो,
		.reg_ग_लिखो = rv3028_eeprom_ग_लिखो,
	पूर्ण;

	rv3028 = devm_kzalloc(&client->dev, माप(काष्ठा rv3028_data),
			      GFP_KERNEL);
	अगर (!rv3028)
		वापस -ENOMEM;

	rv3028->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(rv3028->regmap))
		वापस PTR_ERR(rv3028->regmap);

	i2c_set_clientdata(client, rv3028);

	ret = regmap_पढ़ो(rv3028->regmap, RV3028_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	अगर (status & RV3028_STATUS_AF)
		dev_warn(&client->dev, "An alarm may have been missed.\n");

	rv3028->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(rv3028->rtc))
		वापस PTR_ERR(rv3028->rtc);

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, rv3028_handle_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"rv3028", rv3028);
		अगर (ret) अणु
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		पूर्ण
	पूर्ण
	अगर (!client->irq)
		clear_bit(RTC_FEATURE_ALARM, rv3028->rtc->features);

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL1,
				 RV3028_CTRL1_WADA, RV3028_CTRL1_WADA);
	अगर (ret)
		वापस ret;

	/* setup बारtamping */
	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL2,
				 RV3028_CTRL2_EIE | RV3028_CTRL2_TSE,
				 RV3028_CTRL2_EIE | RV3028_CTRL2_TSE);
	अगर (ret)
		वापस ret;

	/* setup trickle अक्षरger */
	अगर (!device_property_पढ़ो_u32(&client->dev, "trickle-resistor-ohms",
				      &ohms)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(rv3028_trickle_resistors); i++)
			अगर (ohms == rv3028_trickle_resistors[i])
				अवरोध;

		अगर (i < ARRAY_SIZE(rv3028_trickle_resistors)) अणु
			ret = rv3028_update_cfg(rv3028, RV3028_BACKUP, RV3028_BACKUP_TCE |
						 RV3028_BACKUP_TCR_MASK, RV3028_BACKUP_TCE | i);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			dev_warn(&client->dev, "invalid trickle resistor value\n");
		पूर्ण
	पूर्ण

	ret = rtc_add_group(rv3028->rtc, &rv3028_attr_group);
	अगर (ret)
		वापस ret;

	rv3028->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rv3028->rtc->range_max = RTC_TIMESTAMP_END_2099;
	rv3028->rtc->ops = &rv3028_rtc_ops;
	ret = devm_rtc_रेजिस्टर_device(rv3028->rtc);
	अगर (ret)
		वापस ret;

	nvmem_cfg.priv = rv3028->regmap;
	devm_rtc_nvmem_रेजिस्टर(rv3028->rtc, &nvmem_cfg);
	eeprom_cfg.priv = rv3028;
	devm_rtc_nvmem_रेजिस्टर(rv3028->rtc, &eeprom_cfg);

	rv3028->rtc->max_user_freq = 1;

#अगर_घोषित CONFIG_COMMON_CLK
	rv3028_clkout_रेजिस्टर_clk(rv3028, client);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल स्थिर __maybe_unused काष्ठा of_device_id rv3028_of_match[] = अणु
	अणु .compatible = "microcrystal,rv3028", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rv3028_of_match);

अटल काष्ठा i2c_driver rv3028_driver = अणु
	.driver = अणु
		.name = "rtc-rv3028",
		.of_match_table = of_match_ptr(rv3028_of_match),
	पूर्ण,
	.probe_new	= rv3028_probe,
पूर्ण;
module_i2c_driver(rv3028_driver);

MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@bootlin.com>");
MODULE_DESCRIPTION("Micro Crystal RV3028 RTC driver");
MODULE_LICENSE("GPL v2");
