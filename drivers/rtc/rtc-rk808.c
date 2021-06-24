<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTC driver क्रम Rockchip RK808
 *
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Chris Zhong <zyw@rock-chips.com>
 * Author: Zhang Qing <zhangqing@rock-chips.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/mfd/rk808.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>

/* RTC_CTRL_REG bitfields */
#घोषणा BIT_RTC_CTRL_REG_STOP_RTC_M		BIT(0)

/* RK808 has a shaकरोwed रेजिस्टर क्रम saving a "frozen" RTC समय.
 * When user setting "GET_TIME" to 1, the समय will save in this shaकरोwed
 * रेजिस्टर. If set "READSEL" to 1, user पढ़ो rtc समय रेजिस्टर, actually
 * get the समय of that moment. If we need the real समय, clr this bit.
 */
#घोषणा BIT_RTC_CTRL_REG_RTC_GET_TIME		BIT(6)
#घोषणा BIT_RTC_CTRL_REG_RTC_READSEL_M		BIT(7)
#घोषणा BIT_RTC_INTERRUPTS_REG_IT_ALARM_M	BIT(3)
#घोषणा RTC_STATUS_MASK		0xFE

#घोषणा SECONDS_REG_MSK		0x7F
#घोषणा MINUTES_REG_MAK		0x7F
#घोषणा HOURS_REG_MSK		0x3F
#घोषणा DAYS_REG_MSK		0x3F
#घोषणा MONTHS_REG_MSK		0x1F
#घोषणा YEARS_REG_MSK		0xFF
#घोषणा WEEKS_REG_MSK		0x7

/* REG_SECONDS_REG through REG_YEARS_REG is how many रेजिस्टरs? */

#घोषणा NUM_TIME_REGS	(RK808_WEEKS_REG - RK808_SECONDS_REG + 1)
#घोषणा NUM_ALARM_REGS	(RK808_ALARM_YEARS_REG - RK808_ALARM_SECONDS_REG + 1)

काष्ठा rk_rtc_compat_reg अणु
	अचिन्हित पूर्णांक ctrl_reg;
	अचिन्हित पूर्णांक status_reg;
	अचिन्हित पूर्णांक alarm_seconds_reg;
	अचिन्हित पूर्णांक पूर्णांक_reg;
	अचिन्हित पूर्णांक seconds_reg;
पूर्ण;

काष्ठा rk808_rtc अणु
	काष्ठा rk808 *rk808;
	काष्ठा rtc_device *rtc;
	काष्ठा rk_rtc_compat_reg *creg;
	पूर्णांक irq;
पूर्ण;

/*
 * The Rockchip calendar used by the RK808 counts November with 31 days. We use
 * these translation functions to convert its dates to/from the Gregorian
 * calendar used by the rest of the world. We arbitrarily define Jan 1st, 2016
 * as the day when both calendars were in sync, and treat all other dates
 * relative to that.
 * NOTE: Other प्रणाली software (e.g. firmware) that पढ़ोs the same hardware must
 * implement this exact same conversion algorithm, with the same anchor date.
 */
अटल समय64_t nov2dec_transitions(काष्ठा rtc_समय *पंचांग)
अणु
	वापस (पंचांग->पंचांग_year + 1900) - 2016 + (पंचांग->पंचांग_mon + 1 > 11 ? 1 : 0);
पूर्ण

अटल व्योम rockchip_to_gregorian(काष्ठा rtc_समय *पंचांग)
अणु
	/* If it's Nov 31st, rtc_पंचांग_to_समय64() will count that like Dec 1st */
	समय64_t समय = rtc_पंचांग_to_समय64(पंचांग);
	rtc_समय64_to_पंचांग(समय + nov2dec_transitions(पंचांग) * 86400, पंचांग);
पूर्ण

अटल व्योम gregorian_to_rockchip(काष्ठा rtc_समय *पंचांग)
अणु
	समय64_t extra_days = nov2dec_transitions(पंचांग);
	समय64_t समय = rtc_पंचांग_to_समय64(पंचांग);
	rtc_समय64_to_पंचांग(समय - extra_days * 86400, पंचांग);

	/* Compensate अगर we went back over Nov 31st (will work up to 2381) */
	अगर (nov2dec_transitions(पंचांग) < extra_days) अणु
		अगर (पंचांग->पंचांग_mon + 1 == 11)
			पंचांग->पंचांग_mday++;	/* This may result in 31! */
		अन्यथा
			rtc_समय64_to_पंचांग(समय - (extra_days - 1) * 86400, पंचांग);
	पूर्ण
पूर्ण

/* Read current समय and date in RTC */
अटल पूर्णांक rk808_rtc_पढ़ोसमय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	काष्ठा rk808 *rk808 = rk808_rtc->rk808;
	u8 rtc_data[NUM_TIME_REGS];
	पूर्णांक ret;

	/* Force an update of the shaकरोwed रेजिस्टरs right now */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_RTC_GET_TIME,
				 BIT_RTC_CTRL_REG_RTC_GET_TIME);
	अगर (ret) अणु
		dev_err(dev, "Failed to update bits rtc_ctrl: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * After we set the GET_TIME bit, the rtc समय can't be पढ़ो
	 * immediately. So we should रुको up to 31.25 us, about one cycle of
	 * 32khz. If we clear the GET_TIME bit here, the समय of i2c transfer
	 * certainly more than 31.25us: 16 * 2.5us at 400kHz bus frequency.
	 */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_RTC_GET_TIME,
				 0);
	अगर (ret) अणु
		dev_err(dev, "Failed to update bits rtc_ctrl: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_bulk_पढ़ो(rk808->regmap, rk808_rtc->creg->seconds_reg,
			       rtc_data, NUM_TIME_REGS);
	अगर (ret) अणु
		dev_err(dev, "Failed to bulk read rtc_data: %d\n", ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(rtc_data[0] & SECONDS_REG_MSK);
	पंचांग->पंचांग_min = bcd2bin(rtc_data[1] & MINUTES_REG_MAK);
	पंचांग->पंचांग_hour = bcd2bin(rtc_data[2] & HOURS_REG_MSK);
	पंचांग->पंचांग_mday = bcd2bin(rtc_data[3] & DAYS_REG_MSK);
	पंचांग->पंचांग_mon = (bcd2bin(rtc_data[4] & MONTHS_REG_MSK)) - 1;
	पंचांग->पंचांग_year = (bcd2bin(rtc_data[5] & YEARS_REG_MSK)) + 100;
	पंचांग->पंचांग_wday = bcd2bin(rtc_data[6] & WEEKS_REG_MSK);
	rockchip_to_gregorian(पंचांग);
	dev_dbg(dev, "RTC date/time %ptRd(%d) %ptRt\n", पंचांग, पंचांग->पंचांग_wday, पंचांग);

	वापस ret;
पूर्ण

/* Set current समय and date in RTC */
अटल पूर्णांक rk808_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	काष्ठा rk808 *rk808 = rk808_rtc->rk808;
	u8 rtc_data[NUM_TIME_REGS];
	पूर्णांक ret;

	dev_dbg(dev, "set RTC date/time %ptRd(%d) %ptRt\n", पंचांग, पंचांग->पंचांग_wday, पंचांग);
	gregorian_to_rockchip(पंचांग);
	rtc_data[0] = bin2bcd(पंचांग->पंचांग_sec);
	rtc_data[1] = bin2bcd(पंचांग->पंचांग_min);
	rtc_data[2] = bin2bcd(पंचांग->पंचांग_hour);
	rtc_data[3] = bin2bcd(पंचांग->पंचांग_mday);
	rtc_data[4] = bin2bcd(पंचांग->पंचांग_mon + 1);
	rtc_data[5] = bin2bcd(पंचांग->पंचांग_year - 100);
	rtc_data[6] = bin2bcd(पंचांग->पंचांग_wday);

	/* Stop RTC जबतक updating the RTC रेजिस्टरs */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_STOP_RTC_M,
				 BIT_RTC_CTRL_REG_STOP_RTC_M);
	अगर (ret) अणु
		dev_err(dev, "Failed to update RTC control: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_bulk_ग_लिखो(rk808->regmap, rk808_rtc->creg->seconds_reg,
				rtc_data, NUM_TIME_REGS);
	अगर (ret) अणु
		dev_err(dev, "Failed to bull write rtc_data: %d\n", ret);
		वापस ret;
	पूर्ण
	/* Start RTC again */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_STOP_RTC_M, 0);
	अगर (ret) अणु
		dev_err(dev, "Failed to update RTC control: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Read alarm समय and date in RTC */
अटल पूर्णांक rk808_rtc_पढ़ोalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	काष्ठा rk808 *rk808 = rk808_rtc->rk808;
	u8 alrm_data[NUM_ALARM_REGS];
	uपूर्णांक32_t पूर्णांक_reg;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rk808->regmap,
			       rk808_rtc->creg->alarm_seconds_reg,
			       alrm_data, NUM_ALARM_REGS);
	अगर (ret) अणु
		dev_err(dev, "Failed to read RTC alarm date REG: %d\n", ret);
		वापस ret;
	पूर्ण

	alrm->समय.पंचांग_sec = bcd2bin(alrm_data[0] & SECONDS_REG_MSK);
	alrm->समय.पंचांग_min = bcd2bin(alrm_data[1] & MINUTES_REG_MAK);
	alrm->समय.पंचांग_hour = bcd2bin(alrm_data[2] & HOURS_REG_MSK);
	alrm->समय.पंचांग_mday = bcd2bin(alrm_data[3] & DAYS_REG_MSK);
	alrm->समय.पंचांग_mon = (bcd2bin(alrm_data[4] & MONTHS_REG_MSK)) - 1;
	alrm->समय.पंचांग_year = (bcd2bin(alrm_data[5] & YEARS_REG_MSK)) + 100;
	rockchip_to_gregorian(&alrm->समय);

	ret = regmap_पढ़ो(rk808->regmap, rk808_rtc->creg->पूर्णांक_reg, &पूर्णांक_reg);
	अगर (ret) अणु
		dev_err(dev, "Failed to read RTC INT REG: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "alrm read RTC date/time %ptRd(%d) %ptRt\n",
		&alrm->समय, alrm->समय.पंचांग_wday, &alrm->समय);

	alrm->enabled = (पूर्णांक_reg & BIT_RTC_INTERRUPTS_REG_IT_ALARM_M) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rk808_rtc_stop_alarm(काष्ठा rk808_rtc *rk808_rtc)
अणु
	काष्ठा rk808 *rk808 = rk808_rtc->rk808;
	पूर्णांक ret;

	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->पूर्णांक_reg,
				 BIT_RTC_INTERRUPTS_REG_IT_ALARM_M, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक rk808_rtc_start_alarm(काष्ठा rk808_rtc *rk808_rtc)
अणु
	काष्ठा rk808 *rk808 = rk808_rtc->rk808;
	पूर्णांक ret;

	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->पूर्णांक_reg,
				 BIT_RTC_INTERRUPTS_REG_IT_ALARM_M,
				 BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);

	वापस ret;
पूर्ण

अटल पूर्णांक rk808_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	काष्ठा rk808 *rk808 = rk808_rtc->rk808;
	u8 alrm_data[NUM_ALARM_REGS];
	पूर्णांक ret;

	ret = rk808_rtc_stop_alarm(rk808_rtc);
	अगर (ret) अणु
		dev_err(dev, "Failed to stop alarm: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_dbg(dev, "alrm set RTC date/time %ptRd(%d) %ptRt\n",
		&alrm->समय, alrm->समय.पंचांग_wday, &alrm->समय);

	gregorian_to_rockchip(&alrm->समय);
	alrm_data[0] = bin2bcd(alrm->समय.पंचांग_sec);
	alrm_data[1] = bin2bcd(alrm->समय.पंचांग_min);
	alrm_data[2] = bin2bcd(alrm->समय.पंचांग_hour);
	alrm_data[3] = bin2bcd(alrm->समय.पंचांग_mday);
	alrm_data[4] = bin2bcd(alrm->समय.पंचांग_mon + 1);
	alrm_data[5] = bin2bcd(alrm->समय.पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(rk808->regmap,
				rk808_rtc->creg->alarm_seconds_reg,
				alrm_data, NUM_ALARM_REGS);
	अगर (ret) अणु
		dev_err(dev, "Failed to bulk write: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (alrm->enabled) अणु
		ret = rk808_rtc_start_alarm(rk808_rtc);
		अगर (ret) अणु
			dev_err(dev, "Failed to start alarm: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rk808_rtc_alarm_irq_enable(काष्ठा device *dev,
				      अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rk808_rtc *rk808_rtc = dev_get_drvdata(dev);

	अगर (enabled)
		वापस rk808_rtc_start_alarm(rk808_rtc);

	वापस rk808_rtc_stop_alarm(rk808_rtc);
पूर्ण

/*
 * We will just handle setting the frequency and make use the framework क्रम
 * पढ़ोing the periodic पूर्णांकerupts.
 *
 * @freq: Current periodic IRQ freq:
 * bit 0: every second
 * bit 1: every minute
 * bit 2: every hour
 * bit 3: every day
 */
अटल irqवापस_t rk808_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rk808_rtc *rk808_rtc = data;
	काष्ठा rk808 *rk808 = rk808_rtc->rk808;
	काष्ठा i2c_client *client = rk808->i2c;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(rk808->regmap, rk808_rtc->creg->status_reg,
			   RTC_STATUS_MASK);
	अगर (ret) अणु
		dev_err(&client->dev,
			"%s:Failed to update RTC status: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	rtc_update_irq(rk808_rtc->rtc, 1, RTC_IRQF | RTC_AF);
	dev_dbg(&client->dev,
		 "%s:irq=%d\n", __func__, irq);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rk808_rtc_ops = अणु
	.पढ़ो_समय = rk808_rtc_पढ़ोसमय,
	.set_समय = rk808_rtc_set_समय,
	.पढ़ो_alarm = rk808_rtc_पढ़ोalarm,
	.set_alarm = rk808_rtc_setalarm,
	.alarm_irq_enable = rk808_rtc_alarm_irq_enable,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
/* Turn off the alarm अगर it should not be a wake source. */
अटल पूर्णांक rk808_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk808_rtc *rk808_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(rk808_rtc->irq);

	वापस 0;
पूर्ण

/* Enable the alarm अगर it should be enabled (in हाल it was disabled to
 * prevent use as a wake source).
 */
अटल पूर्णांक rk808_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा rk808_rtc *rk808_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(rk808_rtc->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rk808_rtc_pm_ops,
	rk808_rtc_suspend, rk808_rtc_resume);

अटल काष्ठा rk_rtc_compat_reg rk808_creg = अणु
	.ctrl_reg = RK808_RTC_CTRL_REG,
	.status_reg = RK808_RTC_STATUS_REG,
	.alarm_seconds_reg = RK808_ALARM_SECONDS_REG,
	.पूर्णांक_reg = RK808_RTC_INT_REG,
	.seconds_reg = RK808_SECONDS_REG,
पूर्ण;

अटल काष्ठा rk_rtc_compat_reg rk817_creg = अणु
	.ctrl_reg = RK817_RTC_CTRL_REG,
	.status_reg = RK817_RTC_STATUS_REG,
	.alarm_seconds_reg = RK817_ALARM_SECONDS_REG,
	.पूर्णांक_reg = RK817_RTC_INT_REG,
	.seconds_reg = RK817_SECONDS_REG,
पूर्ण;

अटल पूर्णांक rk808_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा rk808_rtc *rk808_rtc;
	पूर्णांक ret;

	rk808_rtc = devm_kzalloc(&pdev->dev, माप(*rk808_rtc), GFP_KERNEL);
	अगर (rk808_rtc == शून्य)
		वापस -ENOMEM;

	चयन (rk808->variant) अणु
	हाल RK809_ID:
	हाल RK817_ID:
		rk808_rtc->creg = &rk817_creg;
		अवरोध;
	शेष:
		rk808_rtc->creg = &rk808_creg;
		अवरोध;
	पूर्ण
	platक्रमm_set_drvdata(pdev, rk808_rtc);
	rk808_rtc->rk808 = rk808;

	/* start rtc running by शेष, and use shaकरोwed समयr. */
	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->ctrl_reg,
				 BIT_RTC_CTRL_REG_STOP_RTC_M |
				 BIT_RTC_CTRL_REG_RTC_READSEL_M,
				 BIT_RTC_CTRL_REG_RTC_READSEL_M);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to update RTC control: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(rk808->regmap, rk808_rtc->creg->status_reg,
			   RTC_STATUS_MASK);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to write RTC status: %d\n", ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);

	rk808_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rk808_rtc->rtc))
		वापस PTR_ERR(rk808_rtc->rtc);

	rk808_rtc->rtc->ops = &rk808_rtc_ops;

	rk808_rtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rk808_rtc->irq < 0)
		वापस rk808_rtc->irq;

	/* request alarm irq of rk808 */
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, rk808_rtc->irq, शून्य,
					rk808_alarm_irq, 0,
					"RTC alarm", rk808_rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request alarm IRQ %d: %d\n",
			rk808_rtc->irq, ret);
		वापस ret;
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(rk808_rtc->rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver rk808_rtc_driver = अणु
	.probe = rk808_rtc_probe,
	.driver = अणु
		.name = "rk808-rtc",
		.pm = &rk808_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rk808_rtc_driver);

MODULE_DESCRIPTION("RTC driver for the rk808 series PMICs");
MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_AUTHOR("Zhang Qing <zhangqing@rock-chips.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rk808-rtc");
