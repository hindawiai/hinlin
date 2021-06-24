<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTC driver क्रम Maxim MAX8925
 *
 * Copyright (C) 2009-2010 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/max8925.h>

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

#घोषणा MAX8925_RTC_SEC			0x00
#घोषणा MAX8925_RTC_MIN			0x01
#घोषणा MAX8925_RTC_HOUR		0x02
#घोषणा MAX8925_RTC_WEEKDAY		0x03
#घोषणा MAX8925_RTC_DATE		0x04
#घोषणा MAX8925_RTC_MONTH		0x05
#घोषणा MAX8925_RTC_YEAR1		0x06
#घोषणा MAX8925_RTC_YEAR2		0x07
#घोषणा MAX8925_ALARM0_SEC		0x08
#घोषणा MAX8925_ALARM0_MIN		0x09
#घोषणा MAX8925_ALARM0_HOUR		0x0a
#घोषणा MAX8925_ALARM0_WEEKDAY		0x0b
#घोषणा MAX8925_ALARM0_DATE		0x0c
#घोषणा MAX8925_ALARM0_MON		0x0d
#घोषणा MAX8925_ALARM0_YEAR1		0x0e
#घोषणा MAX8925_ALARM0_YEAR2		0x0f
#घोषणा MAX8925_ALARM1_SEC		0x10
#घोषणा MAX8925_ALARM1_MIN		0x11
#घोषणा MAX8925_ALARM1_HOUR		0x12
#घोषणा MAX8925_ALARM1_WEEKDAY		0x13
#घोषणा MAX8925_ALARM1_DATE		0x14
#घोषणा MAX8925_ALARM1_MON		0x15
#घोषणा MAX8925_ALARM1_YEAR1		0x16
#घोषणा MAX8925_ALARM1_YEAR2		0x17
#घोषणा MAX8925_RTC_CNTL		0x1b
#घोषणा MAX8925_RTC_STATUS		0x20

#घोषणा TIME_NUM			8
#घोषणा ALARM_1SEC			(1 << 7)
#घोषणा HOUR_12				(1 << 7)
#घोषणा HOUR_AM_PM			(1 << 5)
#घोषणा ALARM0_IRQ			(1 << 3)
#घोषणा ALARM1_IRQ			(1 << 2)
#घोषणा ALARM0_STATUS			(1 << 2)
#घोषणा ALARM1_STATUS			(1 << 1)


काष्ठा max8925_rtc_info अणु
	काष्ठा rtc_device	*rtc_dev;
	काष्ठा max8925_chip	*chip;
	काष्ठा i2c_client	*rtc;
	काष्ठा device		*dev;
	पूर्णांक			irq;
पूर्ण;

अटल irqवापस_t rtc_update_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8925_rtc_info *info = (काष्ठा max8925_rtc_info *)data;

	/* disable ALARM0 except क्रम 1SEC alarm */
	max8925_set_bits(info->rtc, MAX8925_ALARM0_CNTL, 0x7f, 0);
	rtc_update_irq(info->rtc_dev, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक पंचांग_calc(काष्ठा rtc_समय *पंचांग, अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	अगर (len < TIME_NUM)
		वापस -EINVAL;
	पंचांग->पंचांग_year = (buf[RTC_YEAR2] >> 4) * 1000
			+ (buf[RTC_YEAR2] & 0xf) * 100
			+ (buf[RTC_YEAR1] >> 4) * 10
			+ (buf[RTC_YEAR1] & 0xf);
	पंचांग->पंचांग_year -= 1900;
	पंचांग->पंचांग_mon = ((buf[RTC_MONTH] >> 4) & 0x01) * 10
			+ (buf[RTC_MONTH] & 0x0f);
	पंचांग->पंचांग_mday = ((buf[RTC_DATE] >> 4) & 0x03) * 10
			+ (buf[RTC_DATE] & 0x0f);
	पंचांग->पंचांग_wday = buf[RTC_WEEKDAY] & 0x07;
	अगर (buf[RTC_HOUR] & HOUR_12) अणु
		पंचांग->पंचांग_hour = ((buf[RTC_HOUR] >> 4) & 0x1) * 10
				+ (buf[RTC_HOUR] & 0x0f);
		अगर (buf[RTC_HOUR] & HOUR_AM_PM)
			पंचांग->पंचांग_hour += 12;
	पूर्ण अन्यथा
		पंचांग->पंचांग_hour = ((buf[RTC_HOUR] >> 4) & 0x03) * 10
				+ (buf[RTC_HOUR] & 0x0f);
	पंचांग->पंचांग_min = ((buf[RTC_MIN] >> 4) & 0x7) * 10
			+ (buf[RTC_MIN] & 0x0f);
	पंचांग->पंचांग_sec = ((buf[RTC_SEC] >> 4) & 0x7) * 10
			+ (buf[RTC_SEC] & 0x0f);
	वापस 0;
पूर्ण

अटल पूर्णांक data_calc(अचिन्हित अक्षर *buf, काष्ठा rtc_समय *पंचांग, पूर्णांक len)
अणु
	अचिन्हित अक्षर high, low;

	अगर (len < TIME_NUM)
		वापस -EINVAL;

	high = (पंचांग->पंचांग_year + 1900) / 1000;
	low = (पंचांग->पंचांग_year + 1900) / 100;
	low = low - high * 10;
	buf[RTC_YEAR2] = (high << 4) + low;
	high = (पंचांग->पंचांग_year + 1900) / 10;
	low = पंचांग->पंचांग_year + 1900;
	low = low - high * 10;
	high = high - (high / 10) * 10;
	buf[RTC_YEAR1] = (high << 4) + low;
	high = पंचांग->पंचांग_mon / 10;
	low = पंचांग->पंचांग_mon;
	low = low - high * 10;
	buf[RTC_MONTH] = (high << 4) + low;
	high = पंचांग->पंचांग_mday / 10;
	low = पंचांग->पंचांग_mday;
	low = low - high * 10;
	buf[RTC_DATE] = (high << 4) + low;
	buf[RTC_WEEKDAY] = पंचांग->पंचांग_wday;
	high = पंचांग->पंचांग_hour / 10;
	low = पंचांग->पंचांग_hour;
	low = low - high * 10;
	buf[RTC_HOUR] = (high << 4) + low;
	high = पंचांग->पंचांग_min / 10;
	low = पंचांग->पंचांग_min;
	low = low - high * 10;
	buf[RTC_MIN] = (high << 4) + low;
	high = पंचांग->पंचांग_sec / 10;
	low = पंचांग->पंचांग_sec;
	low = low - high * 10;
	buf[RTC_SEC] = (high << 4) + low;
	वापस 0;
पूर्ण

अटल पूर्णांक max8925_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8925_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[TIME_NUM];
	पूर्णांक ret;

	ret = max8925_bulk_पढ़ो(info->rtc, MAX8925_RTC_SEC, TIME_NUM, buf);
	अगर (ret < 0)
		जाओ out;
	ret = पंचांग_calc(पंचांग, buf, TIME_NUM);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक max8925_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8925_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[TIME_NUM];
	पूर्णांक ret;

	ret = data_calc(buf, पंचांग, TIME_NUM);
	अगर (ret < 0)
		जाओ out;
	ret = max8925_bulk_ग_लिखो(info->rtc, MAX8925_RTC_SEC, TIME_NUM, buf);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक max8925_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8925_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[TIME_NUM];
	पूर्णांक ret;

	ret = max8925_bulk_पढ़ो(info->rtc, MAX8925_ALARM0_SEC, TIME_NUM, buf);
	अगर (ret < 0)
		जाओ out;
	ret = पंचांग_calc(&alrm->समय, buf, TIME_NUM);
	अगर (ret < 0)
		जाओ out;
	ret = max8925_reg_पढ़ो(info->rtc, MAX8925_RTC_IRQ_MASK);
	अगर (ret < 0)
		जाओ out;
	अगर (ret & ALARM0_IRQ) अणु
		alrm->enabled = 0;
	पूर्ण अन्यथा अणु
		ret = max8925_reg_पढ़ो(info->rtc, MAX8925_ALARM0_CNTL);
		अगर (ret < 0)
			जाओ out;
		अगर (!ret)
			alrm->enabled = 0;
		अन्यथा
			alrm->enabled = 1;
	पूर्ण
	ret = max8925_reg_पढ़ो(info->rtc, MAX8925_RTC_STATUS);
	अगर (ret < 0)
		जाओ out;
	अगर (ret & ALARM0_STATUS)
		alrm->pending = 1;
	अन्यथा
		alrm->pending = 0;
	वापस 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक max8925_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8925_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[TIME_NUM];
	पूर्णांक ret;

	ret = data_calc(buf, &alrm->समय, TIME_NUM);
	अगर (ret < 0)
		जाओ out;
	ret = max8925_bulk_ग_लिखो(info->rtc, MAX8925_ALARM0_SEC, TIME_NUM, buf);
	अगर (ret < 0)
		जाओ out;
	अगर (alrm->enabled)
		/* only enable alarm on year/month/day/hour/min/sec */
		ret = max8925_reg_ग_लिखो(info->rtc, MAX8925_ALARM0_CNTL, 0x77);
	अन्यथा
		ret = max8925_reg_ग_लिखो(info->rtc, MAX8925_ALARM0_CNTL, 0x0);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max8925_rtc_ops = अणु
	.पढ़ो_समय	= max8925_rtc_पढ़ो_समय,
	.set_समय	= max8925_rtc_set_समय,
	.पढ़ो_alarm	= max8925_rtc_पढ़ो_alarm,
	.set_alarm	= max8925_rtc_set_alarm,
पूर्ण;

अटल पूर्णांक max8925_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8925_rtc_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max8925_rtc_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->chip = chip;
	info->rtc = chip->rtc;
	info->dev = &pdev->dev;
	info->irq = platक्रमm_get_irq(pdev, 0);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq, शून्य,
					rtc_update_handler, IRQF_ONESHOT,
					"rtc-alarm0", info);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&pdev->dev, info);
	/* XXX - isn't this redundant? */
	platक्रमm_set_drvdata(pdev, info);

	device_init_wakeup(&pdev->dev, 1);

	info->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, "max8925-rtc",
					&max8925_rtc_ops, THIS_MODULE);
	ret = PTR_ERR(info->rtc_dev);
	अगर (IS_ERR(info->rtc_dev)) अणु
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max8925_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag |= 1 << MAX8925_IRQ_RTC_ALARM0;
	वापस 0;
पूर्ण
अटल पूर्णांक max8925_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag &= ~(1 << MAX8925_IRQ_RTC_ALARM0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(max8925_rtc_pm_ops, max8925_rtc_suspend, max8925_rtc_resume);

अटल काष्ठा platक्रमm_driver max8925_rtc_driver = अणु
	.driver		= अणु
		.name	= "max8925-rtc",
		.pm     = &max8925_rtc_pm_ops,
	पूर्ण,
	.probe		= max8925_rtc_probe,
पूर्ण;

module_platक्रमm_driver(max8925_rtc_driver);

MODULE_DESCRIPTION("Maxim MAX8925 RTC driver");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");

