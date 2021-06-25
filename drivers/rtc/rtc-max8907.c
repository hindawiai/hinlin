<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTC driver क्रम Maxim MAX8907
 *
 * Copyright (c) 2011-2012, NVIDIA Corporation.
 *
 * Based on drivers/rtc/rtc-max8925.c,
 * Copyright (C) 2009-2010 Marvell International Ltd.
 */

#समावेश <linux/bcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/max8907.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

क्रमागत अणु
	RTC_SEC = 0,
	RTC_MIN,
	RTC_HOUR,
	RTC_WEEKDAY,
	RTC_DATE,
	RTC_MONTH,
	RTC_YEAR1,
	RTC_YEAR2,
पूर्ण;

#घोषणा TIME_NUM			8
#घोषणा ALARM_1SEC			(1 << 7)
#घोषणा HOUR_12				(1 << 7)
#घोषणा HOUR_AM_PM			(1 << 5)
#घोषणा ALARM0_IRQ			(1 << 3)
#घोषणा ALARM1_IRQ			(1 << 2)
#घोषणा ALARM0_STATUS			(1 << 2)
#घोषणा ALARM1_STATUS			(1 << 1)

काष्ठा max8907_rtc अणु
	काष्ठा max8907		*max8907;
	काष्ठा regmap		*regmap;
	काष्ठा rtc_device	*rtc_dev;
	पूर्णांक			irq;
पूर्ण;

अटल irqवापस_t max8907_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8907_rtc *rtc = data;

	regmap_ग_लिखो(rtc->regmap, MAX8907_REG_ALARM0_CNTL, 0);

	rtc_update_irq(rtc->rtc_dev, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम regs_to_पंचांग(u8 *regs, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_year = bcd2bin(regs[RTC_YEAR2]) * 100 +
		bcd2bin(regs[RTC_YEAR1]) - 1900;
	पंचांग->पंचांग_mon = bcd2bin(regs[RTC_MONTH] & 0x1f) - 1;
	पंचांग->पंचांग_mday = bcd2bin(regs[RTC_DATE] & 0x3f);
	पंचांग->पंचांग_wday = (regs[RTC_WEEKDAY] & 0x07);
	अगर (regs[RTC_HOUR] & HOUR_12) अणु
		पंचांग->पंचांग_hour = bcd2bin(regs[RTC_HOUR] & 0x01f);
		अगर (पंचांग->पंचांग_hour == 12)
			पंचांग->पंचांग_hour = 0;
		अगर (regs[RTC_HOUR] & HOUR_AM_PM)
			पंचांग->पंचांग_hour += 12;
	पूर्ण अन्यथा अणु
		पंचांग->पंचांग_hour = bcd2bin(regs[RTC_HOUR] & 0x03f);
	पूर्ण
	पंचांग->पंचांग_min = bcd2bin(regs[RTC_MIN] & 0x7f);
	पंचांग->पंचांग_sec = bcd2bin(regs[RTC_SEC] & 0x7f);
पूर्ण

अटल व्योम पंचांग_to_regs(काष्ठा rtc_समय *पंचांग, u8 *regs)
अणु
	u8 high, low;

	high = (पंचांग->पंचांग_year + 1900) / 100;
	low = पंचांग->पंचांग_year % 100;
	regs[RTC_YEAR2] = bin2bcd(high);
	regs[RTC_YEAR1] = bin2bcd(low);
	regs[RTC_MONTH] = bin2bcd(पंचांग->पंचांग_mon + 1);
	regs[RTC_DATE] = bin2bcd(पंचांग->पंचांग_mday);
	regs[RTC_WEEKDAY] = पंचांग->पंचांग_wday;
	regs[RTC_HOUR] = bin2bcd(पंचांग->पंचांग_hour);
	regs[RTC_MIN] = bin2bcd(पंचांग->पंचांग_min);
	regs[RTC_SEC] = bin2bcd(पंचांग->पंचांग_sec);
पूर्ण

अटल पूर्णांक max8907_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8907_rtc *rtc = dev_get_drvdata(dev);
	u8 regs[TIME_NUM];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rtc->regmap, MAX8907_REG_RTC_SEC, regs,
			       TIME_NUM);
	अगर (ret < 0)
		वापस ret;

	regs_to_पंचांग(regs, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक max8907_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8907_rtc *rtc = dev_get_drvdata(dev);
	u8 regs[TIME_NUM];

	पंचांग_to_regs(पंचांग, regs);

	वापस regmap_bulk_ग_लिखो(rtc->regmap, MAX8907_REG_RTC_SEC, regs,
				 TIME_NUM);
पूर्ण

अटल पूर्णांक max8907_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8907_rtc *rtc = dev_get_drvdata(dev);
	u8 regs[TIME_NUM];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rtc->regmap, MAX8907_REG_ALARM0_SEC, regs,
			       TIME_NUM);
	अगर (ret < 0)
		वापस ret;

	regs_to_पंचांग(regs, &alrm->समय);

	ret = regmap_पढ़ो(rtc->regmap, MAX8907_REG_ALARM0_CNTL, &val);
	अगर (ret < 0)
		वापस ret;

	alrm->enabled = !!(val & 0x7f);

	वापस 0;
पूर्ण

अटल पूर्णांक max8907_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8907_rtc *rtc = dev_get_drvdata(dev);
	u8 regs[TIME_NUM];
	पूर्णांक ret;

	पंचांग_to_regs(&alrm->समय, regs);

	/* Disable alarm जबतक we update the target समय */
	ret = regmap_ग_लिखो(rtc->regmap, MAX8907_REG_ALARM0_CNTL, 0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_ग_लिखो(rtc->regmap, MAX8907_REG_ALARM0_SEC, regs,
				TIME_NUM);
	अगर (ret < 0)
		वापस ret;

	अगर (alrm->enabled)
		ret = regmap_ग_लिखो(rtc->regmap, MAX8907_REG_ALARM0_CNTL, 0x77);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max8907_rtc_ops = अणु
	.पढ़ो_समय	= max8907_rtc_पढ़ो_समय,
	.set_समय	= max8907_rtc_set_समय,
	.पढ़ो_alarm	= max8907_rtc_पढ़ो_alarm,
	.set_alarm	= max8907_rtc_set_alarm,
पूर्ण;

अटल पूर्णांक max8907_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8907 *max8907 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8907_rtc *rtc;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, rtc);

	rtc->max8907 = max8907;
	rtc->regmap = max8907->regmap_rtc;

	rtc->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, "max8907-rtc",
					&max8907_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc->rtc_dev)) अणु
		ret = PTR_ERR(rtc->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		वापस ret;
	पूर्ण

	rtc->irq = regmap_irq_get_virq(max8907->irqc_rtc,
				       MAX8907_IRQ_RTC_ALARM0);
	अगर (rtc->irq < 0)
		वापस rtc->irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq, शून्य,
				max8907_irq_handler,
				IRQF_ONESHOT, "max8907-alarm0", rtc);
	अगर (ret < 0)
		dev_err(&pdev->dev, "Failed to request IRQ%d: %d\n",
			rtc->irq, ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver max8907_rtc_driver = अणु
	.driver = अणु
		.name = "max8907-rtc",
	पूर्ण,
	.probe = max8907_rtc_probe,
पूर्ण;
module_platक्रमm_driver(max8907_rtc_driver);

MODULE_DESCRIPTION("Maxim MAX8907 RTC driver");
MODULE_LICENSE("GPL v2");
