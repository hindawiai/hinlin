<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2013-2014 Samsung Electronics Co., Ltd
//	http://www.samsung.com
//
//  Copyright (C) 2013 Google, Inc

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/samsung/core.h>
#समावेश <linux/mfd/samsung/irq.h>
#समावेश <linux/mfd/samsung/rtc.h>
#समावेश <linux/mfd/samsung/s2mps14.h>

/*
 * Maximum number of retries क्रम checking changes in UDR field
 * of S5M_RTC_UDR_CON रेजिस्टर (to limit possible endless loop).
 *
 * After writing to RTC रेजिस्टरs (setting समय or alarm) पढ़ो the UDR field
 * in S5M_RTC_UDR_CON रेजिस्टर. UDR is स्वतः-cleared when data have
 * been transferred.
 */
#घोषणा UDR_READ_RETRY_CNT	5

क्रमागत अणु
	RTC_SEC = 0,
	RTC_MIN,
	RTC_HOUR,
	RTC_WEEKDAY,
	RTC_DATE,
	RTC_MONTH,
	RTC_YEAR1,
	RTC_YEAR2,
	/* Make sure this is always the last क्रमागत name. */
	RTC_MAX_NUM_TIME_REGS
पूर्ण;

/*
 * Registers used by the driver which are dअगरferent between chipsets.
 *
 * Operations like पढ़ो समय and ग_लिखो alarm/समय require updating
 * specअगरic fields in UDR रेजिस्टर. These fields usually are स्वतः-cleared
 * (with some exceptions).
 *
 * Table of operations per device:
 *
 * Device     | Write समय | Read समय | Write alarm
 * =================================================
 * S5M8767    | UDR + TIME |           | UDR
 * S2MPS11/14 | WUDR       | RUDR      | WUDR + RUDR
 * S2MPS13    | WUDR       | RUDR      | WUDR + AUDR
 * S2MPS15    | WUDR       | RUDR      | AUDR
 */
काष्ठा s5m_rtc_reg_config अणु
	/* Number of रेजिस्टरs used क्रम setting समय/alarm0/alarm1 */
	अचिन्हित पूर्णांक regs_count;
	/* First रेजिस्टर क्रम समय, seconds */
	अचिन्हित पूर्णांक समय;
	/* RTC control रेजिस्टर */
	अचिन्हित पूर्णांक ctrl;
	/* First रेजिस्टर क्रम alarm 0, seconds */
	अचिन्हित पूर्णांक alarm0;
	/* First रेजिस्टर क्रम alarm 1, seconds */
	अचिन्हित पूर्णांक alarm1;
	/*
	 * Register क्रम update flag (UDR). Typically setting UDR field to 1
	 * will enable update of समय or alarm रेजिस्टर. Then it will be
	 * स्वतः-cleared after successful update.
	 */
	अचिन्हित पूर्णांक udr_update;
	/* Auto-cleared mask in UDR field क्रम writing समय and alarm */
	अचिन्हित पूर्णांक स्वतःclear_udr_mask;
	/*
	 * Masks in UDR field क्रम समय and alarm operations.
	 * The पढ़ो समय mask can be 0. Rest should not.
	 */
	अचिन्हित पूर्णांक पढ़ो_समय_udr_mask;
	अचिन्हित पूर्णांक ग_लिखो_समय_udr_mask;
	अचिन्हित पूर्णांक ग_लिखो_alarm_udr_mask;
पूर्ण;

/* Register map क्रम S5M8763 and S5M8767 */
अटल स्थिर काष्ठा s5m_rtc_reg_config s5m_rtc_regs = अणु
	.regs_count		= 8,
	.समय			= S5M_RTC_SEC,
	.ctrl			= S5M_ALARM1_CONF,
	.alarm0			= S5M_ALARM0_SEC,
	.alarm1			= S5M_ALARM1_SEC,
	.udr_update		= S5M_RTC_UDR_CON,
	.स्वतःclear_udr_mask	= S5M_RTC_UDR_MASK,
	.पढ़ो_समय_udr_mask	= 0, /* Not needed */
	.ग_लिखो_समय_udr_mask	= S5M_RTC_UDR_MASK | S5M_RTC_TIME_EN_MASK,
	.ग_लिखो_alarm_udr_mask	= S5M_RTC_UDR_MASK,
पूर्ण;

/* Register map क्रम S2MPS13 */
अटल स्थिर काष्ठा s5m_rtc_reg_config s2mps13_rtc_regs = अणु
	.regs_count		= 7,
	.समय			= S2MPS_RTC_SEC,
	.ctrl			= S2MPS_RTC_CTRL,
	.alarm0			= S2MPS_ALARM0_SEC,
	.alarm1			= S2MPS_ALARM1_SEC,
	.udr_update		= S2MPS_RTC_UDR_CON,
	.स्वतःclear_udr_mask	= S2MPS_RTC_WUDR_MASK,
	.पढ़ो_समय_udr_mask	= S2MPS_RTC_RUDR_MASK,
	.ग_लिखो_समय_udr_mask	= S2MPS_RTC_WUDR_MASK,
	.ग_लिखो_alarm_udr_mask	= S2MPS_RTC_WUDR_MASK | S2MPS13_RTC_AUDR_MASK,
पूर्ण;

/* Register map क्रम S2MPS11/14 */
अटल स्थिर काष्ठा s5m_rtc_reg_config s2mps14_rtc_regs = अणु
	.regs_count		= 7,
	.समय			= S2MPS_RTC_SEC,
	.ctrl			= S2MPS_RTC_CTRL,
	.alarm0			= S2MPS_ALARM0_SEC,
	.alarm1			= S2MPS_ALARM1_SEC,
	.udr_update		= S2MPS_RTC_UDR_CON,
	.स्वतःclear_udr_mask	= S2MPS_RTC_WUDR_MASK,
	.पढ़ो_समय_udr_mask	= S2MPS_RTC_RUDR_MASK,
	.ग_लिखो_समय_udr_mask	= S2MPS_RTC_WUDR_MASK,
	.ग_लिखो_alarm_udr_mask	= S2MPS_RTC_WUDR_MASK | S2MPS_RTC_RUDR_MASK,
पूर्ण;

/*
 * Register map क्रम S2MPS15 - in comparison to S2MPS14 the WUDR and AUDR bits
 * are swapped.
 */
अटल स्थिर काष्ठा s5m_rtc_reg_config s2mps15_rtc_regs = अणु
	.regs_count		= 7,
	.समय			= S2MPS_RTC_SEC,
	.ctrl			= S2MPS_RTC_CTRL,
	.alarm0			= S2MPS_ALARM0_SEC,
	.alarm1			= S2MPS_ALARM1_SEC,
	.udr_update		= S2MPS_RTC_UDR_CON,
	.स्वतःclear_udr_mask	= S2MPS_RTC_WUDR_MASK,
	.पढ़ो_समय_udr_mask	= S2MPS_RTC_RUDR_MASK,
	.ग_लिखो_समय_udr_mask	= S2MPS15_RTC_WUDR_MASK,
	.ग_लिखो_alarm_udr_mask	= S2MPS15_RTC_AUDR_MASK,
पूर्ण;

काष्ठा s5m_rtc_info अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c;
	काष्ठा sec_pmic_dev *s5m87xx;
	काष्ठा regmap *regmap;
	काष्ठा rtc_device *rtc_dev;
	पूर्णांक irq;
	क्रमागत sec_device_type device_type;
	पूर्णांक rtc_24hr_mode;
	स्थिर काष्ठा s5m_rtc_reg_config	*regs;
पूर्ण;

अटल स्थिर काष्ठा regmap_config s5m_rtc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S5M_RTC_REG_MAX,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s2mps14_rtc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S2MPS_RTC_REG_MAX,
पूर्ण;

अटल व्योम s5m8767_data_to_पंचांग(u8 *data, काष्ठा rtc_समय *पंचांग,
			       पूर्णांक rtc_24hr_mode)
अणु
	पंचांग->पंचांग_sec = data[RTC_SEC] & 0x7f;
	पंचांग->पंचांग_min = data[RTC_MIN] & 0x7f;
	अगर (rtc_24hr_mode) अणु
		पंचांग->पंचांग_hour = data[RTC_HOUR] & 0x1f;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_hour = data[RTC_HOUR] & 0x0f;
		अगर (data[RTC_HOUR] & HOUR_PM_MASK)
			पंचांग->पंचांग_hour += 12;
	पूर्ण

	पंचांग->पंचांग_wday = ffs(data[RTC_WEEKDAY] & 0x7f);
	पंचांग->पंचांग_mday = data[RTC_DATE] & 0x1f;
	पंचांग->पंचांग_mon = (data[RTC_MONTH] & 0x0f) - 1;
	पंचांग->पंचांग_year = (data[RTC_YEAR1] & 0x7f) + 100;
	पंचांग->पंचांग_yday = 0;
	पंचांग->पंचांग_isdst = 0;
पूर्ण

अटल पूर्णांक s5m8767_पंचांग_to_data(काष्ठा rtc_समय *पंचांग, u8 *data)
अणु
	data[RTC_SEC] = पंचांग->पंचांग_sec;
	data[RTC_MIN] = पंचांग->पंचांग_min;

	अगर (पंचांग->पंचांग_hour >= 12)
		data[RTC_HOUR] = पंचांग->पंचांग_hour | HOUR_PM_MASK;
	अन्यथा
		data[RTC_HOUR] = पंचांग->पंचांग_hour & ~HOUR_PM_MASK;

	data[RTC_WEEKDAY] = 1 << पंचांग->पंचांग_wday;
	data[RTC_DATE] = पंचांग->पंचांग_mday;
	data[RTC_MONTH] = पंचांग->पंचांग_mon + 1;
	data[RTC_YEAR1] = पंचांग->पंचांग_year > 100 ? (पंचांग->पंचांग_year - 100) : 0;

	अगर (पंचांग->पंचांग_year < 100) अणु
		pr_err("RTC cannot handle the year %d\n",
		       1900 + पंचांग->पंचांग_year);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Read RTC_UDR_CON रेजिस्टर and रुको till UDR field is cleared.
 * This indicates that समय/alarm update ended.
 */
अटल पूर्णांक s5m8767_रुको_क्रम_udr_update(काष्ठा s5m_rtc_info *info)
अणु
	पूर्णांक ret, retry = UDR_READ_RETRY_CNT;
	अचिन्हित पूर्णांक data;

	करो अणु
		ret = regmap_पढ़ो(info->regmap, info->regs->udr_update, &data);
	पूर्ण जबतक (--retry && (data & info->regs->स्वतःclear_udr_mask) && !ret);

	अगर (!retry)
		dev_err(info->dev, "waiting for UDR update, reached max number of retries\n");

	वापस ret;
पूर्ण

अटल पूर्णांक s5m_check_peding_alarm_पूर्णांकerrupt(काष्ठा s5m_rtc_info *info,
		काष्ठा rtc_wkalrm *alarm)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	चयन (info->device_type) अणु
	हाल S5M8767X:
	हाल S5M8763X:
		ret = regmap_पढ़ो(info->regmap, S5M_RTC_STATUS, &val);
		val &= S5M_ALARM0_STATUS;
		अवरोध;
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		ret = regmap_पढ़ो(info->s5m87xx->regmap_pmic, S2MPS14_REG_ST2,
				&val);
		val &= S2MPS_ALARM0_STATUS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	अगर (val)
		alarm->pending = 1;
	अन्यथा
		alarm->pending = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक s5m8767_rtc_set_समय_reg(काष्ठा s5m_rtc_info *info)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(info->regmap, info->regs->udr_update, &data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to read update reg(%d)\n", ret);
		वापस ret;
	पूर्ण

	data |= info->regs->ग_लिखो_समय_udr_mask;

	ret = regmap_ग_लिखो(info->regmap, info->regs->udr_update, data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "failed to write update reg(%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = s5m8767_रुको_क्रम_udr_update(info);

	वापस ret;
पूर्ण

अटल पूर्णांक s5m8767_rtc_set_alarm_reg(काष्ठा s5m_rtc_info *info)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(info->regmap, info->regs->udr_update, &data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to read update reg(%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	data |= info->regs->ग_लिखो_alarm_udr_mask;
	चयन (info->device_type) अणु
	हाल S5M8763X:
	हाल S5M8767X:
		data &= ~S5M_RTC_TIME_EN_MASK;
		अवरोध;
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		/* No exceptions needed */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(info->regmap, info->regs->udr_update, data);
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to write update reg(%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = s5m8767_रुको_क्रम_udr_update(info);

	/* On S2MPS13 the AUDR is not स्वतः-cleared */
	अगर (info->device_type == S2MPS13X)
		regmap_update_bits(info->regmap, info->regs->udr_update,
				   S2MPS13_RTC_AUDR_MASK, 0);

	वापस ret;
पूर्ण

अटल व्योम s5m8763_data_to_पंचांग(u8 *data, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bcd2bin(data[RTC_SEC]);
	पंचांग->पंचांग_min = bcd2bin(data[RTC_MIN]);

	अगर (data[RTC_HOUR] & HOUR_12) अणु
		पंचांग->पंचांग_hour = bcd2bin(data[RTC_HOUR] & 0x1f);
		अगर (data[RTC_HOUR] & HOUR_PM)
			पंचांग->पंचांग_hour += 12;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_hour = bcd2bin(data[RTC_HOUR] & 0x3f);
	पूर्ण

	पंचांग->पंचांग_wday = data[RTC_WEEKDAY] & 0x07;
	पंचांग->पंचांग_mday = bcd2bin(data[RTC_DATE]);
	पंचांग->पंचांग_mon = bcd2bin(data[RTC_MONTH]);
	पंचांग->पंचांग_year = bcd2bin(data[RTC_YEAR1]) + bcd2bin(data[RTC_YEAR2]) * 100;
	पंचांग->पंचांग_year -= 1900;
पूर्ण

अटल व्योम s5m8763_पंचांग_to_data(काष्ठा rtc_समय *पंचांग, u8 *data)
अणु
	data[RTC_SEC] = bin2bcd(पंचांग->पंचांग_sec);
	data[RTC_MIN] = bin2bcd(पंचांग->पंचांग_min);
	data[RTC_HOUR] = bin2bcd(पंचांग->पंचांग_hour);
	data[RTC_WEEKDAY] = पंचांग->पंचांग_wday;
	data[RTC_DATE] = bin2bcd(पंचांग->पंचांग_mday);
	data[RTC_MONTH] = bin2bcd(पंचांग->पंचांग_mon);
	data[RTC_YEAR1] = bin2bcd(पंचांग->पंचांग_year % 100);
	data[RTC_YEAR2] = bin2bcd((पंचांग->पंचांग_year + 1900) / 100);
पूर्ण

अटल पूर्णांक s5m_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा s5m_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_MAX_NUM_TIME_REGS];
	पूर्णांक ret;

	अगर (info->regs->पढ़ो_समय_udr_mask) अणु
		ret = regmap_update_bits(info->regmap,
				info->regs->udr_update,
				info->regs->पढ़ो_समय_udr_mask,
				info->regs->पढ़ो_समय_udr_mask);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to prepare registers for time reading: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण
	ret = regmap_bulk_पढ़ो(info->regmap, info->regs->समय, data,
			info->regs->regs_count);
	अगर (ret < 0)
		वापस ret;

	चयन (info->device_type) अणु
	हाल S5M8763X:
		s5m8763_data_to_पंचांग(data, पंचांग);
		अवरोध;

	हाल S5M8767X:
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		s5m8767_data_to_पंचांग(data, पंचांग, info->rtc_24hr_mode);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "%s: %ptR(%d)\n", __func__, पंचांग, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक s5m_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा s5m_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_MAX_NUM_TIME_REGS];
	पूर्णांक ret = 0;

	चयन (info->device_type) अणु
	हाल S5M8763X:
		s5m8763_पंचांग_to_data(पंचांग, data);
		अवरोध;
	हाल S5M8767X:
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		ret = s5m8767_पंचांग_to_data(पंचांग, data);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	dev_dbg(dev, "%s: %ptR(%d)\n", __func__, पंचांग, पंचांग->पंचांग_wday);

	ret = regmap_raw_ग_लिखो(info->regmap, info->regs->समय, data,
			info->regs->regs_count);
	अगर (ret < 0)
		वापस ret;

	ret = s5m8767_rtc_set_समय_reg(info);

	वापस ret;
पूर्ण

अटल पूर्णांक s5m_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा s5m_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_MAX_NUM_TIME_REGS];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	ret = regmap_bulk_पढ़ो(info->regmap, info->regs->alarm0, data,
			info->regs->regs_count);
	अगर (ret < 0)
		वापस ret;

	चयन (info->device_type) अणु
	हाल S5M8763X:
		s5m8763_data_to_पंचांग(data, &alrm->समय);
		ret = regmap_पढ़ो(info->regmap, S5M_ALARM0_CONF, &val);
		अगर (ret < 0)
			वापस ret;

		alrm->enabled = !!val;
		अवरोध;

	हाल S5M8767X:
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		s5m8767_data_to_पंचांग(data, &alrm->समय, info->rtc_24hr_mode);
		alrm->enabled = 0;
		क्रम (i = 0; i < info->regs->regs_count; i++) अणु
			अगर (data[i] & ALARM_ENABLE_MASK) अणु
				alrm->enabled = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "%s: %ptR(%d)\n", __func__, &alrm->समय, alrm->समय.पंचांग_wday);

	ret = s5m_check_peding_alarm_पूर्णांकerrupt(info, alrm);

	वापस 0;
पूर्ण

अटल पूर्णांक s5m_rtc_stop_alarm(काष्ठा s5m_rtc_info *info)
अणु
	u8 data[RTC_MAX_NUM_TIME_REGS];
	पूर्णांक ret, i;
	काष्ठा rtc_समय पंचांग;

	ret = regmap_bulk_पढ़ो(info->regmap, info->regs->alarm0, data,
			info->regs->regs_count);
	अगर (ret < 0)
		वापस ret;

	s5m8767_data_to_पंचांग(data, &पंचांग, info->rtc_24hr_mode);
	dev_dbg(info->dev, "%s: %ptR(%d)\n", __func__, &पंचांग, पंचांग.पंचांग_wday);

	चयन (info->device_type) अणु
	हाल S5M8763X:
		ret = regmap_ग_लिखो(info->regmap, S5M_ALARM0_CONF, 0);
		अवरोध;

	हाल S5M8767X:
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		क्रम (i = 0; i < info->regs->regs_count; i++)
			data[i] &= ~ALARM_ENABLE_MASK;

		ret = regmap_raw_ग_लिखो(info->regmap, info->regs->alarm0, data,
				info->regs->regs_count);
		अगर (ret < 0)
			वापस ret;

		ret = s5m8767_rtc_set_alarm_reg(info);

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5m_rtc_start_alarm(काष्ठा s5m_rtc_info *info)
अणु
	पूर्णांक ret;
	u8 data[RTC_MAX_NUM_TIME_REGS];
	u8 alarm0_conf;
	काष्ठा rtc_समय पंचांग;

	ret = regmap_bulk_पढ़ो(info->regmap, info->regs->alarm0, data,
			info->regs->regs_count);
	अगर (ret < 0)
		वापस ret;

	s5m8767_data_to_पंचांग(data, &पंचांग, info->rtc_24hr_mode);
	dev_dbg(info->dev, "%s: %ptR(%d)\n", __func__, &पंचांग, पंचांग.पंचांग_wday);

	चयन (info->device_type) अणु
	हाल S5M8763X:
		alarm0_conf = 0x77;
		ret = regmap_ग_लिखो(info->regmap, S5M_ALARM0_CONF, alarm0_conf);
		अवरोध;

	हाल S5M8767X:
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		data[RTC_SEC] |= ALARM_ENABLE_MASK;
		data[RTC_MIN] |= ALARM_ENABLE_MASK;
		data[RTC_HOUR] |= ALARM_ENABLE_MASK;
		data[RTC_WEEKDAY] &= ~ALARM_ENABLE_MASK;
		अगर (data[RTC_DATE] & 0x1f)
			data[RTC_DATE] |= ALARM_ENABLE_MASK;
		अगर (data[RTC_MONTH] & 0xf)
			data[RTC_MONTH] |= ALARM_ENABLE_MASK;
		अगर (data[RTC_YEAR1] & 0x7f)
			data[RTC_YEAR1] |= ALARM_ENABLE_MASK;

		ret = regmap_raw_ग_लिखो(info->regmap, info->regs->alarm0, data,
				info->regs->regs_count);
		अगर (ret < 0)
			वापस ret;
		ret = s5m8767_rtc_set_alarm_reg(info);

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5m_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा s5m_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_MAX_NUM_TIME_REGS];
	पूर्णांक ret;

	चयन (info->device_type) अणु
	हाल S5M8763X:
		s5m8763_पंचांग_to_data(&alrm->समय, data);
		अवरोध;

	हाल S5M8767X:
	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		s5m8767_पंचांग_to_data(&alrm->समय, data);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "%s: %ptR(%d)\n", __func__, &alrm->समय, alrm->समय.पंचांग_wday);

	ret = s5m_rtc_stop_alarm(info);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_raw_ग_लिखो(info->regmap, info->regs->alarm0, data,
			info->regs->regs_count);
	अगर (ret < 0)
		वापस ret;

	ret = s5m8767_rtc_set_alarm_reg(info);
	अगर (ret < 0)
		वापस ret;

	अगर (alrm->enabled)
		ret = s5m_rtc_start_alarm(info);

	वापस ret;
पूर्ण

अटल पूर्णांक s5m_rtc_alarm_irq_enable(काष्ठा device *dev,
				    अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा s5m_rtc_info *info = dev_get_drvdata(dev);

	अगर (enabled)
		वापस s5m_rtc_start_alarm(info);
	अन्यथा
		वापस s5m_rtc_stop_alarm(info);
पूर्ण

अटल irqवापस_t s5m_rtc_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा s5m_rtc_info *info = data;

	rtc_update_irq(info->rtc_dev, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops s5m_rtc_ops = अणु
	.पढ़ो_समय = s5m_rtc_पढ़ो_समय,
	.set_समय = s5m_rtc_set_समय,
	.पढ़ो_alarm = s5m_rtc_पढ़ो_alarm,
	.set_alarm = s5m_rtc_set_alarm,
	.alarm_irq_enable = s5m_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक s5m8767_rtc_init_reg(काष्ठा s5m_rtc_info *info)
अणु
	u8 data[2];
	पूर्णांक ret;

	चयन (info->device_type) अणु
	हाल S5M8763X:
	हाल S5M8767X:
		/* UDR update समय. Default of 7.32 ms is too दीर्घ. */
		ret = regmap_update_bits(info->regmap, S5M_RTC_UDR_CON,
				S5M_RTC_UDR_T_MASK, S5M_RTC_UDR_T_450_US);
		अगर (ret < 0)
			dev_err(info->dev, "%s: fail to change UDR time: %d\n",
					__func__, ret);

		/* Set RTC control रेजिस्टर : Binary mode, 24hour mode */
		data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);
		data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);

		ret = regmap_raw_ग_लिखो(info->regmap, S5M_ALARM0_CONF, data, 2);
		अवरोध;

	हाल S2MPS15X:
	हाल S2MPS14X:
	हाल S2MPS13X:
		data[0] = (0 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);
		ret = regmap_ग_लिखो(info->regmap, info->regs->ctrl, data[0]);
		अगर (ret < 0)
			अवरोध;

		/*
		 * Should set WUDR & (RUDR or AUDR) bits to high after writing
		 * RTC_CTRL रेजिस्टर like writing Alarm रेजिस्टरs. We can't find
		 * the description from datasheet but venकरोr code करोes that
		 * really.
		 */
		ret = s5m8767_rtc_set_alarm_reg(info);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	info->rtc_24hr_mode = 1;
	अगर (ret < 0) अणु
		dev_err(info->dev, "%s: fail to write controlm reg(%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5m_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sec_pmic_dev *s5m87xx = dev_get_drvdata(pdev->dev.parent);
	काष्ठा s5m_rtc_info *info;
	स्थिर काष्ठा regmap_config *regmap_cfg;
	पूर्णांक ret, alarm_irq;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	चयन (platक्रमm_get_device_id(pdev)->driver_data) अणु
	हाल S2MPS15X:
		regmap_cfg = &s2mps14_rtc_regmap_config;
		info->regs = &s2mps15_rtc_regs;
		alarm_irq = S2MPS14_IRQ_RTCA0;
		अवरोध;
	हाल S2MPS14X:
		regmap_cfg = &s2mps14_rtc_regmap_config;
		info->regs = &s2mps14_rtc_regs;
		alarm_irq = S2MPS14_IRQ_RTCA0;
		अवरोध;
	हाल S2MPS13X:
		regmap_cfg = &s2mps14_rtc_regmap_config;
		info->regs = &s2mps13_rtc_regs;
		alarm_irq = S2MPS14_IRQ_RTCA0;
		अवरोध;
	हाल S5M8763X:
		regmap_cfg = &s5m_rtc_regmap_config;
		info->regs = &s5m_rtc_regs;
		alarm_irq = S5M8763_IRQ_ALARM0;
		अवरोध;
	हाल S5M8767X:
		regmap_cfg = &s5m_rtc_regmap_config;
		info->regs = &s5m_rtc_regs;
		alarm_irq = S5M8767_IRQ_RTCA1;
		अवरोध;
	शेष:
		dev_err(&pdev->dev,
				"Device type %lu is not supported by RTC driver\n",
				platक्रमm_get_device_id(pdev)->driver_data);
		वापस -ENODEV;
	पूर्ण

	info->i2c = devm_i2c_new_dummy_device(&pdev->dev, s5m87xx->i2c->adapter,
					      RTC_I2C_ADDR);
	अगर (IS_ERR(info->i2c)) अणु
		dev_err(&pdev->dev, "Failed to allocate I2C for RTC\n");
		वापस PTR_ERR(info->i2c);
	पूर्ण

	info->regmap = devm_regmap_init_i2c(info->i2c, regmap_cfg);
	अगर (IS_ERR(info->regmap)) अणु
		ret = PTR_ERR(info->regmap);
		dev_err(&pdev->dev, "Failed to allocate RTC register map: %d\n",
				ret);
		वापस ret;
	पूर्ण

	info->dev = &pdev->dev;
	info->s5m87xx = s5m87xx;
	info->device_type = platक्रमm_get_device_id(pdev)->driver_data;

	अगर (s5m87xx->irq_data) अणु
		info->irq = regmap_irq_get_virq(s5m87xx->irq_data, alarm_irq);
		अगर (info->irq <= 0) अणु
			dev_err(&pdev->dev, "Failed to get virtual IRQ %d\n",
				alarm_irq);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	ret = s5m8767_rtc_init_reg(info);
	अगर (ret)
		वापस ret;

	device_init_wakeup(&pdev->dev, 1);

	info->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, "s5m-rtc",
						 &s5m_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(info->rtc_dev))
		वापस PTR_ERR(info->rtc_dev);

	अगर (!info->irq) अणु
		dev_info(&pdev->dev, "Alarm IRQ not available\n");
		वापस 0;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq, शून्य,
					s5m_rtc_alarm_irq, 0, "rtc-alarm0",
					info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			info->irq, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक s5m_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा s5m_rtc_info *info = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (info->irq && device_may_wakeup(dev))
		ret = disable_irq_wake(info->irq);

	वापस ret;
पूर्ण

अटल पूर्णांक s5m_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा s5m_rtc_info *info = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (info->irq && device_may_wakeup(dev))
		ret = enable_irq_wake(info->irq);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(s5m_rtc_pm_ops, s5m_rtc_suspend, s5m_rtc_resume);

अटल स्थिर काष्ठा platक्रमm_device_id s5m_rtc_id[] = अणु
	अणु "s5m-rtc",		S5M8767X पूर्ण,
	अणु "s2mps13-rtc",	S2MPS13X पूर्ण,
	अणु "s2mps14-rtc",	S2MPS14X पूर्ण,
	अणु "s2mps15-rtc",	S2MPS15X पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s5m_rtc_id);

अटल काष्ठा platक्रमm_driver s5m_rtc_driver = अणु
	.driver		= अणु
		.name	= "s5m-rtc",
		.pm	= &s5m_rtc_pm_ops,
	पूर्ण,
	.probe		= s5m_rtc_probe,
	.id_table	= s5m_rtc_id,
पूर्ण;

module_platक्रमm_driver(s5m_rtc_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Sangbeom Kim <sbkim73@samsung.com>");
MODULE_DESCRIPTION("Samsung S5M/S2MPS14 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s5m-rtc");
