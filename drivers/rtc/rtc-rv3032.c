<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC driver क्रम the Micro Crystal RV3032
 *
 * Copyright (C) 2020 Micro Crystal SA
 *
 * Alexandre Belloni <alexandre.belloni@bootlin.com>
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/bcd.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>

#घोषणा RV3032_SEC			0x01
#घोषणा RV3032_MIN			0x02
#घोषणा RV3032_HOUR			0x03
#घोषणा RV3032_WDAY			0x04
#घोषणा RV3032_DAY			0x05
#घोषणा RV3032_MONTH			0x06
#घोषणा RV3032_YEAR			0x07
#घोषणा RV3032_ALARM_MIN		0x08
#घोषणा RV3032_ALARM_HOUR		0x09
#घोषणा RV3032_ALARM_DAY		0x0A
#घोषणा RV3032_STATUS			0x0D
#घोषणा RV3032_TLSB			0x0E
#घोषणा RV3032_TMSB			0x0F
#घोषणा RV3032_CTRL1			0x10
#घोषणा RV3032_CTRL2			0x11
#घोषणा RV3032_CTRL3			0x12
#घोषणा RV3032_TS_CTRL			0x13
#घोषणा RV3032_CLK_IRQ			0x14
#घोषणा RV3032_EEPROM_ADDR		0x3D
#घोषणा RV3032_EEPROM_DATA		0x3E
#घोषणा RV3032_EEPROM_CMD		0x3F
#घोषणा RV3032_RAM1			0x40
#घोषणा RV3032_PMU			0xC0
#घोषणा RV3032_OFFSET			0xC1
#घोषणा RV3032_CLKOUT1			0xC2
#घोषणा RV3032_CLKOUT2			0xC3
#घोषणा RV3032_TREF0			0xC4
#घोषणा RV3032_TREF1			0xC5

#घोषणा RV3032_STATUS_VLF		BIT(0)
#घोषणा RV3032_STATUS_PORF		BIT(1)
#घोषणा RV3032_STATUS_EVF		BIT(2)
#घोषणा RV3032_STATUS_AF		BIT(3)
#घोषणा RV3032_STATUS_TF		BIT(4)
#घोषणा RV3032_STATUS_UF		BIT(5)
#घोषणा RV3032_STATUS_TLF		BIT(6)
#घोषणा RV3032_STATUS_THF		BIT(7)

#घोषणा RV3032_TLSB_CLKF		BIT(1)
#घोषणा RV3032_TLSB_EEBUSY		BIT(2)
#घोषणा RV3032_TLSB_TEMP		GENMASK(7, 4)

#घोषणा RV3032_CLKOUT2_HFD_MSK		GENMASK(4, 0)
#घोषणा RV3032_CLKOUT2_FD_MSK		GENMASK(6, 5)
#घोषणा RV3032_CLKOUT2_OS		BIT(7)

#घोषणा RV3032_CTRL1_EERD		BIT(3)
#घोषणा RV3032_CTRL1_WADA		BIT(5)

#घोषणा RV3032_CTRL2_STOP		BIT(0)
#घोषणा RV3032_CTRL2_EIE		BIT(2)
#घोषणा RV3032_CTRL2_AIE		BIT(3)
#घोषणा RV3032_CTRL2_TIE		BIT(4)
#घोषणा RV3032_CTRL2_UIE		BIT(5)
#घोषणा RV3032_CTRL2_CLKIE		BIT(6)
#घोषणा RV3032_CTRL2_TSE		BIT(7)

#घोषणा RV3032_PMU_TCM			GENMASK(1, 0)
#घोषणा RV3032_PMU_TCR			GENMASK(3, 2)
#घोषणा RV3032_PMU_BSM			GENMASK(5, 4)
#घोषणा RV3032_PMU_NCLKE		BIT(6)

#घोषणा RV3032_PMU_BSM_DSM		1
#घोषणा RV3032_PMU_BSM_LSM		2

#घोषणा RV3032_OFFSET_MSK		GENMASK(5, 0)

#घोषणा RV3032_EVT_CTRL_TSR		BIT(2)

#घोषणा RV3032_EEPROM_CMD_UPDATE	0x11
#घोषणा RV3032_EEPROM_CMD_WRITE		0x21
#घोषणा RV3032_EEPROM_CMD_READ		0x22

#घोषणा RV3032_EEPROM_USER		0xCB

#घोषणा RV3032_EEBUSY_POLL		10000
#घोषणा RV3032_EEBUSY_TIMEOUT		100000

#घोषणा OFFSET_STEP_PPT			238419

काष्ठा rv3032_data अणु
	काष्ठा regmap *regmap;
	काष्ठा rtc_device *rtc;
#अगर_घोषित CONFIG_COMMON_CLK
	काष्ठा clk_hw clkout_hw;
#पूर्ण_अगर
पूर्ण;

अटल u16 rv3032_trickle_resistors[] = अणु1000, 2000, 7000, 11000पूर्ण;
अटल u16 rv3032_trickle_voltages[] = अणु0, 1750, 3000, 4400पूर्ण;

अटल पूर्णांक rv3032_निकास_eerd(काष्ठा rv3032_data *rv3032, u32 eerd)
अणु
	अगर (eerd)
		वापस 0;

	वापस regmap_update_bits(rv3032->regmap, RV3032_CTRL1, RV3032_CTRL1_EERD, 0);
पूर्ण

अटल पूर्णांक rv3032_enter_eerd(काष्ठा rv3032_data *rv3032, u32 *eerd)
अणु
	u32 ctrl1, status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_CTRL1, &ctrl1);
	अगर (ret)
		वापस ret;

	*eerd = ctrl1 & RV3032_CTRL1_EERD;
	अगर (*eerd)
		वापस 0;

	ret = regmap_update_bits(rv3032->regmap, RV3032_CTRL1,
				 RV3032_CTRL1_EERD, RV3032_CTRL1_EERD);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(rv3032->regmap, RV3032_TLSB, status,
				       !(status & RV3032_TLSB_EEBUSY),
				       RV3032_EEBUSY_POLL, RV3032_EEBUSY_TIMEOUT);
	अगर (ret) अणु
		rv3032_निकास_eerd(rv3032, *eerd);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv3032_update_cfg(काष्ठा rv3032_data *rv3032, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	u32 status, eerd;
	पूर्णांक ret;

	ret = rv3032_enter_eerd(rv3032, &eerd);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(rv3032->regmap, reg, mask, val);
	अगर (ret)
		जाओ निकास_eerd;

	ret = regmap_ग_लिखो(rv3032->regmap, RV3032_EEPROM_CMD, RV3032_EEPROM_CMD_UPDATE);
	अगर (ret)
		जाओ निकास_eerd;

	usleep_range(46000, RV3032_EEBUSY_TIMEOUT);

	ret = regmap_पढ़ो_poll_समयout(rv3032->regmap, RV3032_TLSB, status,
				       !(status & RV3032_TLSB_EEBUSY),
				       RV3032_EEBUSY_POLL, RV3032_EEBUSY_TIMEOUT);

निकास_eerd:
	rv3032_निकास_eerd(rv3032, eerd);

	वापस ret;
पूर्ण

अटल irqवापस_t rv3032_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rv3032_data *rv3032 = dev_id;
	अचिन्हित दीर्घ events = 0;
	u32 status = 0, ctrl = 0;

	अगर (regmap_पढ़ो(rv3032->regmap, RV3032_STATUS, &status) < 0 ||
	    status == 0) अणु
		वापस IRQ_NONE;
	पूर्ण

	अगर (status & RV3032_STATUS_TF) अणु
		status |= RV3032_STATUS_TF;
		ctrl |= RV3032_CTRL2_TIE;
		events |= RTC_PF;
	पूर्ण

	अगर (status & RV3032_STATUS_AF) अणु
		status |= RV3032_STATUS_AF;
		ctrl |= RV3032_CTRL2_AIE;
		events |= RTC_AF;
	पूर्ण

	अगर (status & RV3032_STATUS_UF) अणु
		status |= RV3032_STATUS_UF;
		ctrl |= RV3032_CTRL2_UIE;
		events |= RTC_UF;
	पूर्ण

	अगर (events) अणु
		rtc_update_irq(rv3032->rtc, 1, events);
		regmap_update_bits(rv3032->regmap, RV3032_STATUS, status, 0);
		regmap_update_bits(rv3032->regmap, RV3032_CTRL2, ctrl, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rv3032_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	u8 date[7];
	पूर्णांक ret, status;

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	अगर (status & (RV3032_STATUS_PORF | RV3032_STATUS_VLF))
		वापस -EINVAL;

	ret = regmap_bulk_पढ़ो(rv3032->regmap, RV3032_SEC, date, माप(date));
	अगर (ret)
		वापस ret;

	पंचांग->पंचांग_sec  = bcd2bin(date[0] & 0x7f);
	पंचांग->पंचांग_min  = bcd2bin(date[1] & 0x7f);
	पंचांग->पंचांग_hour = bcd2bin(date[2] & 0x3f);
	पंचांग->पंचांग_wday = date[3] & 0x7;
	पंचांग->पंचांग_mday = bcd2bin(date[4] & 0x3f);
	पंचांग->पंचांग_mon  = bcd2bin(date[5] & 0x1f) - 1;
	पंचांग->पंचांग_year = bcd2bin(date[6]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3032_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	u8 date[7];
	पूर्णांक ret;

	date[0] = bin2bcd(पंचांग->पंचांग_sec);
	date[1] = bin2bcd(पंचांग->पंचांग_min);
	date[2] = bin2bcd(पंचांग->पंचांग_hour);
	date[3] = पंचांग->पंचांग_wday;
	date[4] = bin2bcd(पंचांग->पंचांग_mday);
	date[5] = bin2bcd(पंचांग->पंचांग_mon + 1);
	date[6] = bin2bcd(पंचांग->पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(rv3032->regmap, RV3032_SEC, date,
				माप(date));
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(rv3032->regmap, RV3032_STATUS,
				 RV3032_STATUS_PORF | RV3032_STATUS_VLF, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3032_get_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	पूर्णांक status, ctrl, ret;

	ret = regmap_bulk_पढ़ो(rv3032->regmap, RV3032_ALARM_MIN, alarmvals,
			       माप(alarmvals));
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_CTRL2, &ctrl);
	अगर (ret < 0)
		वापस ret;

	alrm->समय.पंचांग_sec  = 0;
	alrm->समय.पंचांग_min  = bcd2bin(alarmvals[0] & 0x7f);
	alrm->समय.पंचांग_hour = bcd2bin(alarmvals[1] & 0x3f);
	alrm->समय.पंचांग_mday = bcd2bin(alarmvals[2] & 0x3f);

	alrm->enabled = !!(ctrl & RV3032_CTRL2_AIE);
	alrm->pending = (status & RV3032_STATUS_AF) && alrm->enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3032_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	u8 ctrl = 0;
	पूर्णांक ret;

	/* The alarm has no seconds, round up to nearest minute */
	अगर (alrm->समय.पंचांग_sec) अणु
		समय64_t alarm_समय = rtc_पंचांग_to_समय64(&alrm->समय);

		alarm_समय += 60 - alrm->समय.पंचांग_sec;
		rtc_समय64_to_पंचांग(alarm_समय, &alrm->समय);
	पूर्ण

	ret = regmap_update_bits(rv3032->regmap, RV3032_CTRL2,
				 RV3032_CTRL2_AIE | RV3032_CTRL2_UIE, 0);
	अगर (ret)
		वापस ret;

	alarmvals[0] = bin2bcd(alrm->समय.पंचांग_min);
	alarmvals[1] = bin2bcd(alrm->समय.पंचांग_hour);
	alarmvals[2] = bin2bcd(alrm->समय.पंचांग_mday);

	ret = regmap_update_bits(rv3032->regmap, RV3032_STATUS,
				 RV3032_STATUS_AF, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_ग_लिखो(rv3032->regmap, RV3032_ALARM_MIN, alarmvals,
				माप(alarmvals));
	अगर (ret)
		वापस ret;

	अगर (alrm->enabled) अणु
		अगर (rv3032->rtc->uie_rtस_समयr.enabled)
			ctrl |= RV3032_CTRL2_UIE;
		अगर (rv3032->rtc->aie_समयr.enabled)
			ctrl |= RV3032_CTRL2_AIE;
	पूर्ण

	ret = regmap_update_bits(rv3032->regmap, RV3032_CTRL2,
				 RV3032_CTRL2_UIE | RV3032_CTRL2_AIE, ctrl);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3032_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	पूर्णांक ctrl = 0, ret;

	अगर (enabled) अणु
		अगर (rv3032->rtc->uie_rtस_समयr.enabled)
			ctrl |= RV3032_CTRL2_UIE;
		अगर (rv3032->rtc->aie_समयr.enabled)
			ctrl |= RV3032_CTRL2_AIE;
	पूर्ण

	ret = regmap_update_bits(rv3032->regmap, RV3032_STATUS,
				 RV3032_STATUS_AF | RV3032_STATUS_UF, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(rv3032->regmap, RV3032_CTRL2,
				 RV3032_CTRL2_UIE | RV3032_CTRL2_AIE, ctrl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rv3032_पढ़ो_offset(काष्ठा device *dev, दीर्घ *offset)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	पूर्णांक ret, value, steps;

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_OFFSET, &value);
	अगर (ret < 0)
		वापस ret;

	steps = sign_extend32(FIELD_GET(RV3032_OFFSET_MSK, value), 5);

	*offset = DIV_ROUND_CLOSEST(steps * OFFSET_STEP_PPT, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक rv3032_set_offset(काष्ठा device *dev, दीर्घ offset)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);

	offset = clamp(offset, -7629L, 7391L) * 1000;
	offset = DIV_ROUND_CLOSEST(offset, OFFSET_STEP_PPT);

	वापस rv3032_update_cfg(rv3032, RV3032_OFFSET, RV3032_OFFSET_MSK,
				 FIELD_PREP(RV3032_OFFSET_MSK, offset));
पूर्ण

अटल पूर्णांक rv3032_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	पूर्णांक status, val = 0, ret = 0;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		ret = regmap_पढ़ो(rv3032->regmap, RV3032_STATUS, &status);
		अगर (ret < 0)
			वापस ret;

		अगर (status & (RV3032_STATUS_PORF | RV3032_STATUS_VLF))
			val = RTC_VL_DATA_INVALID;
		वापस put_user(val, (अचिन्हित पूर्णांक __user *)arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक rv3032_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val, माप_प्रकार bytes)
अणु
	वापस regmap_bulk_ग_लिखो(priv, RV3032_RAM1 + offset, val, bytes);
पूर्ण

अटल पूर्णांक rv3032_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val, माप_प्रकार bytes)
अणु
	वापस regmap_bulk_पढ़ो(priv, RV3032_RAM1 + offset, val, bytes);
पूर्ण

अटल पूर्णांक rv3032_eeprom_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा rv3032_data *rv3032 = priv;
	u32 status, eerd;
	पूर्णांक i, ret;
	u8 *buf = val;

	ret = rv3032_enter_eerd(rv3032, &eerd);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < bytes; i++) अणु
		ret = regmap_ग_लिखो(rv3032->regmap, RV3032_EEPROM_ADDR,
				   RV3032_EEPROM_USER + offset + i);
		अगर (ret)
			जाओ निकास_eerd;

		ret = regmap_ग_लिखो(rv3032->regmap, RV3032_EEPROM_DATA, buf[i]);
		अगर (ret)
			जाओ निकास_eerd;

		ret = regmap_ग_लिखो(rv3032->regmap, RV3032_EEPROM_CMD,
				   RV3032_EEPROM_CMD_WRITE);
		अगर (ret)
			जाओ निकास_eerd;

		usleep_range(RV3032_EEBUSY_POLL, RV3032_EEBUSY_TIMEOUT);

		ret = regmap_पढ़ो_poll_समयout(rv3032->regmap, RV3032_TLSB, status,
					       !(status & RV3032_TLSB_EEBUSY),
					       RV3032_EEBUSY_POLL, RV3032_EEBUSY_TIMEOUT);
		अगर (ret)
			जाओ निकास_eerd;
	पूर्ण

निकास_eerd:
	rv3032_निकास_eerd(rv3032, eerd);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3032_eeprom_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा rv3032_data *rv3032 = priv;
	u32 status, eerd, data;
	पूर्णांक i, ret;
	u8 *buf = val;

	ret = rv3032_enter_eerd(rv3032, &eerd);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < bytes; i++) अणु
		ret = regmap_ग_लिखो(rv3032->regmap, RV3032_EEPROM_ADDR,
				   RV3032_EEPROM_USER + offset + i);
		अगर (ret)
			जाओ निकास_eerd;

		ret = regmap_ग_लिखो(rv3032->regmap, RV3032_EEPROM_CMD,
				   RV3032_EEPROM_CMD_READ);
		अगर (ret)
			जाओ निकास_eerd;

		ret = regmap_पढ़ो_poll_समयout(rv3032->regmap, RV3032_TLSB, status,
					       !(status & RV3032_TLSB_EEBUSY),
					       RV3032_EEBUSY_POLL, RV3032_EEBUSY_TIMEOUT);
		अगर (ret)
			जाओ निकास_eerd;

		ret = regmap_पढ़ो(rv3032->regmap, RV3032_EEPROM_DATA, &data);
		अगर (ret)
			जाओ निकास_eerd;
		buf[i] = data;
	पूर्ण

निकास_eerd:
	rv3032_निकास_eerd(rv3032, eerd);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3032_trickle_अक्षरger_setup(काष्ठा device *dev, काष्ठा rv3032_data *rv3032)
अणु
	u32 val, ohms, voltage;
	पूर्णांक i;

	val = FIELD_PREP(RV3032_PMU_TCM, 1) | FIELD_PREP(RV3032_PMU_BSM, RV3032_PMU_BSM_DSM);
	अगर (!device_property_पढ़ो_u32(dev, "trickle-voltage-millivolt", &voltage)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(rv3032_trickle_voltages); i++)
			अगर (voltage == rv3032_trickle_voltages[i])
				अवरोध;
		अगर (i < ARRAY_SIZE(rv3032_trickle_voltages))
			val = FIELD_PREP(RV3032_PMU_TCM, i) |
			      FIELD_PREP(RV3032_PMU_BSM, RV3032_PMU_BSM_LSM);
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "trickle-resistor-ohms", &ohms))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(rv3032_trickle_resistors); i++)
		अगर (ohms == rv3032_trickle_resistors[i])
			अवरोध;

	अगर (i >= ARRAY_SIZE(rv3032_trickle_resistors)) अणु
		dev_warn(dev, "invalid trickle resistor value\n");

		वापस 0;
	पूर्ण

	वापस rv3032_update_cfg(rv3032, RV3032_PMU,
				 RV3032_PMU_TCR | RV3032_PMU_TCM | RV3032_PMU_BSM,
				 val | FIELD_PREP(RV3032_PMU_TCR, i));
पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
#घोषणा clkout_hw_to_rv3032(hw) container_of(hw, काष्ठा rv3032_data, clkout_hw)

अटल पूर्णांक clkout_xtal_rates[] = अणु
	32768,
	1024,
	64,
	1,
पूर्ण;

#घोषणा RV3032_HFD_STEP 8192

अटल अचिन्हित दीर्घ rv3032_clkout_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक clkout, ret;
	काष्ठा rv3032_data *rv3032 = clkout_hw_to_rv3032(hw);

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_CLKOUT2, &clkout);
	अगर (ret < 0)
		वापस 0;

	अगर (clkout & RV3032_CLKOUT2_OS) अणु
		अचिन्हित दीर्घ rate = FIELD_GET(RV3032_CLKOUT2_HFD_MSK, clkout) << 8;

		ret = regmap_पढ़ो(rv3032->regmap, RV3032_CLKOUT1, &clkout);
		अगर (ret < 0)
			वापस 0;

		rate += clkout + 1;

		वापस rate * RV3032_HFD_STEP;
	पूर्ण

	वापस clkout_xtal_rates[FIELD_GET(RV3032_CLKOUT2_FD_MSK, clkout)];
पूर्ण

अटल दीर्घ rv3032_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i, hfd;

	अगर (rate < RV3032_HFD_STEP)
		क्रम (i = 0; i < ARRAY_SIZE(clkout_xtal_rates); i++)
			अगर (clkout_xtal_rates[i] <= rate)
				वापस clkout_xtal_rates[i];

	hfd = DIV_ROUND_CLOSEST(rate, RV3032_HFD_STEP);

	वापस RV3032_HFD_STEP * clamp(hfd, 0, 8192);
पूर्ण

अटल पूर्णांक rv3032_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा rv3032_data *rv3032 = clkout_hw_to_rv3032(hw);
	u32 status, eerd;
	पूर्णांक i, hfd, ret;

	क्रम (i = 0; i < ARRAY_SIZE(clkout_xtal_rates); i++) अणु
		अगर (clkout_xtal_rates[i] == rate) अणु
			वापस rv3032_update_cfg(rv3032, RV3032_CLKOUT2, 0xff,
						 FIELD_PREP(RV3032_CLKOUT2_FD_MSK, i));
		पूर्ण
	पूर्ण

	hfd = DIV_ROUND_CLOSEST(rate, RV3032_HFD_STEP);
	hfd = clamp(hfd, 1, 8192) - 1;

	ret = rv3032_enter_eerd(rv3032, &eerd);
	अगर (ret)
		जाओ निकास_eerd;

	ret = regmap_ग_लिखो(rv3032->regmap, RV3032_CLKOUT1, hfd & 0xff);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(rv3032->regmap, RV3032_CLKOUT2, RV3032_CLKOUT2_OS |
			    FIELD_PREP(RV3032_CLKOUT2_HFD_MSK, hfd >> 8));
	अगर (ret)
		जाओ निकास_eerd;

	ret = regmap_ग_लिखो(rv3032->regmap, RV3032_EEPROM_CMD, RV3032_EEPROM_CMD_UPDATE);
	अगर (ret)
		जाओ निकास_eerd;

	usleep_range(46000, RV3032_EEBUSY_TIMEOUT);

	ret = regmap_पढ़ो_poll_समयout(rv3032->regmap, RV3032_TLSB, status,
				       !(status & RV3032_TLSB_EEBUSY),
				       RV3032_EEBUSY_POLL, RV3032_EEBUSY_TIMEOUT);

निकास_eerd:
	rv3032_निकास_eerd(rv3032, eerd);

	वापस ret;
पूर्ण

अटल पूर्णांक rv3032_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rv3032_data *rv3032 = clkout_hw_to_rv3032(hw);

	वापस rv3032_update_cfg(rv3032, RV3032_PMU, RV3032_PMU_NCLKE, 0);
पूर्ण

अटल व्योम rv3032_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rv3032_data *rv3032 = clkout_hw_to_rv3032(hw);

	rv3032_update_cfg(rv3032, RV3032_PMU, RV3032_PMU_NCLKE, RV3032_PMU_NCLKE);
पूर्ण

अटल पूर्णांक rv3032_clkout_is_prepared(काष्ठा clk_hw *hw)
अणु
	पूर्णांक val, ret;
	काष्ठा rv3032_data *rv3032 = clkout_hw_to_rv3032(hw);

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_PMU, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !(val & RV3032_PMU_NCLKE);
पूर्ण

अटल स्थिर काष्ठा clk_ops rv3032_clkout_ops = अणु
	.prepare = rv3032_clkout_prepare,
	.unprepare = rv3032_clkout_unprepare,
	.is_prepared = rv3032_clkout_is_prepared,
	.recalc_rate = rv3032_clkout_recalc_rate,
	.round_rate = rv3032_clkout_round_rate,
	.set_rate = rv3032_clkout_set_rate,
पूर्ण;

अटल पूर्णांक rv3032_clkout_रेजिस्टर_clk(काष्ठा rv3032_data *rv3032,
				      काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	काष्ठा device_node *node = client->dev.of_node;

	ret = regmap_update_bits(rv3032->regmap, RV3032_TLSB, RV3032_TLSB_CLKF, 0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(rv3032->regmap, RV3032_CTRL2, RV3032_CTRL2_CLKIE, 0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(rv3032->regmap, RV3032_CLK_IRQ, 0);
	अगर (ret < 0)
		वापस ret;

	init.name = "rv3032-clkout";
	init.ops = &rv3032_clkout_ops;
	init.flags = 0;
	init.parent_names = शून्य;
	init.num_parents = 0;
	rv3032->clkout_hw.init = &init;

	of_property_पढ़ो_string(node, "clock-output-names", &init.name);

	clk = devm_clk_रेजिस्टर(&client->dev, &rv3032->clkout_hw);
	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rv3032_hwmon_पढ़ो_temp(काष्ठा device *dev, दीर्घ *mC)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);
	u8 buf[2];
	पूर्णांक temp, prev = 0;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rv3032->regmap, RV3032_TLSB, buf, माप(buf));
	अगर (ret)
		वापस ret;

	temp = sign_extend32(buf[1], 7) << 4;
	temp |= FIELD_GET(RV3032_TLSB_TEMP, buf[0]);

	/* No blocking or shaकरोwing on RV3032_TLSB and RV3032_TMSB */
	करो अणु
		prev = temp;

		ret = regmap_bulk_पढ़ो(rv3032->regmap, RV3032_TLSB, buf, माप(buf));
		अगर (ret)
			वापस ret;

		temp = sign_extend32(buf[1], 7) << 4;
		temp |= FIELD_GET(RV3032_TLSB_TEMP, buf[0]);
	पूर्ण जबतक (temp != prev);

	*mC = (temp * 1000) / 16;

	वापस 0;
पूर्ण

अटल umode_t rv3032_hwmon_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				       u32 attr, पूर्णांक channel)
अणु
	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक rv3032_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			     u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		err = rv3032_hwmon_पढ़ो_temp(dev, temp);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *rv3032_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops rv3032_hwmon_hwmon_ops = अणु
	.is_visible = rv3032_hwmon_is_visible,
	.पढ़ो = rv3032_hwmon_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info rv3032_hwmon_chip_info = अणु
	.ops = &rv3032_hwmon_hwmon_ops,
	.info = rv3032_hwmon_info,
पूर्ण;

अटल व्योम rv3032_hwmon_रेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा rv3032_data *rv3032 = dev_get_drvdata(dev);

	अगर (!IS_REACHABLE(CONFIG_HWMON))
		वापस;

	devm_hwmon_device_रेजिस्टर_with_info(dev, "rv3032", rv3032, &rv3032_hwmon_chip_info, शून्य);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rv3032_rtc_ops = अणु
	.पढ़ो_समय = rv3032_get_समय,
	.set_समय = rv3032_set_समय,
	.पढ़ो_offset = rv3032_पढ़ो_offset,
	.set_offset = rv3032_set_offset,
	.ioctl = rv3032_ioctl,
	.पढ़ो_alarm = rv3032_get_alarm,
	.set_alarm = rv3032_set_alarm,
	.alarm_irq_enable = rv3032_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xCA,
पूर्ण;

अटल पूर्णांक rv3032_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा rv3032_data *rv3032;
	पूर्णांक ret, status;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "rv3032_nvram",
		.word_size = 1,
		.stride = 1,
		.size = 16,
		.type = NVMEM_TYPE_BATTERY_BACKED,
		.reg_पढ़ो = rv3032_nvram_पढ़ो,
		.reg_ग_लिखो = rv3032_nvram_ग_लिखो,
	पूर्ण;
	काष्ठा nvmem_config eeprom_cfg = अणु
		.name = "rv3032_eeprom",
		.word_size = 1,
		.stride = 1,
		.size = 32,
		.type = NVMEM_TYPE_EEPROM,
		.reg_पढ़ो = rv3032_eeprom_पढ़ो,
		.reg_ग_लिखो = rv3032_eeprom_ग_लिखो,
	पूर्ण;

	rv3032 = devm_kzalloc(&client->dev, माप(काष्ठा rv3032_data),
			      GFP_KERNEL);
	अगर (!rv3032)
		वापस -ENOMEM;

	rv3032->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(rv3032->regmap))
		वापस PTR_ERR(rv3032->regmap);

	i2c_set_clientdata(client, rv3032);

	ret = regmap_पढ़ो(rv3032->regmap, RV3032_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	rv3032->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(rv3032->rtc))
		वापस PTR_ERR(rv3032->rtc);

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, rv3032_handle_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"rv3032", rv3032);
		अगर (ret) अणु
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		पूर्ण
	पूर्ण
	अगर (!client->irq)
		clear_bit(RTC_FEATURE_ALARM, rv3032->rtc->features);

	ret = regmap_update_bits(rv3032->regmap, RV3032_CTRL1,
				 RV3032_CTRL1_WADA, RV3032_CTRL1_WADA);
	अगर (ret)
		वापस ret;

	rv3032_trickle_अक्षरger_setup(&client->dev, rv3032);

	rv3032->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rv3032->rtc->range_max = RTC_TIMESTAMP_END_2099;
	rv3032->rtc->ops = &rv3032_rtc_ops;
	ret = devm_rtc_रेजिस्टर_device(rv3032->rtc);
	अगर (ret)
		वापस ret;

	nvmem_cfg.priv = rv3032->regmap;
	devm_rtc_nvmem_रेजिस्टर(rv3032->rtc, &nvmem_cfg);
	eeprom_cfg.priv = rv3032;
	devm_rtc_nvmem_रेजिस्टर(rv3032->rtc, &eeprom_cfg);

	rv3032->rtc->max_user_freq = 1;

#अगर_घोषित CONFIG_COMMON_CLK
	rv3032_clkout_रेजिस्टर_clk(rv3032, client);
#पूर्ण_अगर

	rv3032_hwmon_रेजिस्टर(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर __maybe_unused काष्ठा of_device_id rv3032_of_match[] = अणु
	अणु .compatible = "microcrystal,rv3032", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rv3032_of_match);

अटल काष्ठा i2c_driver rv3032_driver = अणु
	.driver = अणु
		.name = "rtc-rv3032",
		.of_match_table = of_match_ptr(rv3032_of_match),
	पूर्ण,
	.probe_new	= rv3032_probe,
पूर्ण;
module_i2c_driver(rv3032_driver);

MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@bootlin.com>");
MODULE_DESCRIPTION("Micro Crystal RV3032 RTC driver");
MODULE_LICENSE("GPL v2");
