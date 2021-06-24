<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// RTC driver क्रम Maxim MAX8998
//
// Copyright (C) 2010 Samsung Electronics Co.Ltd
// Author: Minkyu Kang <mk7.kang@samsung.com>
// Author: Joonyoung Shim <jy0922.shim@samsung.com>

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/bcd.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/max8998.h>
#समावेश <linux/mfd/max8998-निजी.h>
#समावेश <linux/delay.h>

#घोषणा MAX8998_RTC_SEC			0x00
#घोषणा MAX8998_RTC_MIN			0x01
#घोषणा MAX8998_RTC_HOUR		0x02
#घोषणा MAX8998_RTC_WEEKDAY		0x03
#घोषणा MAX8998_RTC_DATE		0x04
#घोषणा MAX8998_RTC_MONTH		0x05
#घोषणा MAX8998_RTC_YEAR1		0x06
#घोषणा MAX8998_RTC_YEAR2		0x07
#घोषणा MAX8998_ALARM0_SEC		0x08
#घोषणा MAX8998_ALARM0_MIN		0x09
#घोषणा MAX8998_ALARM0_HOUR		0x0a
#घोषणा MAX8998_ALARM0_WEEKDAY		0x0b
#घोषणा MAX8998_ALARM0_DATE		0x0c
#घोषणा MAX8998_ALARM0_MONTH		0x0d
#घोषणा MAX8998_ALARM0_YEAR1		0x0e
#घोषणा MAX8998_ALARM0_YEAR2		0x0f
#घोषणा MAX8998_ALARM1_SEC		0x10
#घोषणा MAX8998_ALARM1_MIN		0x11
#घोषणा MAX8998_ALARM1_HOUR		0x12
#घोषणा MAX8998_ALARM1_WEEKDAY		0x13
#घोषणा MAX8998_ALARM1_DATE		0x14
#घोषणा MAX8998_ALARM1_MONTH		0x15
#घोषणा MAX8998_ALARM1_YEAR1		0x16
#घोषणा MAX8998_ALARM1_YEAR2		0x17
#घोषणा MAX8998_ALARM0_CONF		0x18
#घोषणा MAX8998_ALARM1_CONF		0x19
#घोषणा MAX8998_RTC_STATUS		0x1a
#घोषणा MAX8998_WTSR_SMPL_CNTL		0x1b
#घोषणा MAX8998_TEST			0x1f

#घोषणा HOUR_12				(1 << 7)
#घोषणा HOUR_PM				(1 << 5)
#घोषणा ALARM0_STATUS			(1 << 1)
#घोषणा ALARM1_STATUS			(1 << 2)

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

काष्ठा max8998_rtc_info अणु
	काष्ठा device		*dev;
	काष्ठा max8998_dev	*max8998;
	काष्ठा i2c_client	*rtc;
	काष्ठा rtc_device	*rtc_dev;
	पूर्णांक irq;
	bool lp3974_bug_workaround;
पूर्ण;

अटल व्योम max8998_data_to_पंचांग(u8 *data, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bcd2bin(data[RTC_SEC]);
	पंचांग->पंचांग_min = bcd2bin(data[RTC_MIN]);
	अगर (data[RTC_HOUR] & HOUR_12) अणु
		पंचांग->पंचांग_hour = bcd2bin(data[RTC_HOUR] & 0x1f);
		अगर (data[RTC_HOUR] & HOUR_PM)
			पंचांग->पंचांग_hour += 12;
	पूर्ण अन्यथा
		पंचांग->पंचांग_hour = bcd2bin(data[RTC_HOUR] & 0x3f);

	पंचांग->पंचांग_wday = data[RTC_WEEKDAY] & 0x07;
	पंचांग->पंचांग_mday = bcd2bin(data[RTC_DATE]);
	पंचांग->पंचांग_mon = bcd2bin(data[RTC_MONTH]);
	पंचांग->पंचांग_year = bcd2bin(data[RTC_YEAR1]) + bcd2bin(data[RTC_YEAR2]) * 100;
	पंचांग->पंचांग_year -= 1900;
पूर्ण

अटल व्योम max8998_पंचांग_to_data(काष्ठा rtc_समय *पंचांग, u8 *data)
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

अटल पूर्णांक max8998_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	पूर्णांक ret;

	ret = max8998_bulk_पढ़ो(info->rtc, MAX8998_RTC_SEC, 8, data);
	अगर (ret < 0)
		वापस ret;

	max8998_data_to_पंचांग(data, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक max8998_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	पूर्णांक ret;

	max8998_पंचांग_to_data(पंचांग, data);

	ret = max8998_bulk_ग_लिखो(info->rtc, MAX8998_RTC_SEC, 8, data);

	अगर (info->lp3974_bug_workaround)
		msleep(2000);

	वापस ret;
पूर्ण

अटल पूर्णांक max8998_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	u8 val;
	पूर्णांक ret;

	ret = max8998_bulk_पढ़ो(info->rtc, MAX8998_ALARM0_SEC, 8, data);
	अगर (ret < 0)
		वापस ret;

	max8998_data_to_पंचांग(data, &alrm->समय);

	ret = max8998_पढ़ो_reg(info->rtc, MAX8998_ALARM0_CONF, &val);
	अगर (ret < 0)
		वापस ret;

	alrm->enabled = !!val;

	ret = max8998_पढ़ो_reg(info->rtc, MAX8998_RTC_STATUS, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val & ALARM0_STATUS)
		alrm->pending = 1;
	अन्यथा
		alrm->pending = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक max8998_rtc_stop_alarm(काष्ठा max8998_rtc_info *info)
अणु
	पूर्णांक ret = max8998_ग_लिखो_reg(info->rtc, MAX8998_ALARM0_CONF, 0);

	अगर (info->lp3974_bug_workaround)
		msleep(2000);

	वापस ret;
पूर्ण

अटल पूर्णांक max8998_rtc_start_alarm(काष्ठा max8998_rtc_info *info)
अणु
	पूर्णांक ret;
	u8 alarm0_conf = 0x77;

	/* LP3974 with delay bug chips has rtc alarm bugs with "MONTH" field */
	अगर (info->lp3974_bug_workaround)
		alarm0_conf = 0x57;

	ret = max8998_ग_लिखो_reg(info->rtc, MAX8998_ALARM0_CONF, alarm0_conf);

	अगर (info->lp3974_bug_workaround)
		msleep(2000);

	वापस ret;
पूर्ण

अटल पूर्णांक max8998_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	पूर्णांक ret;

	max8998_पंचांग_to_data(&alrm->समय, data);

	ret = max8998_rtc_stop_alarm(info);
	अगर (ret < 0)
		वापस ret;

	ret = max8998_bulk_ग_लिखो(info->rtc, MAX8998_ALARM0_SEC, 8, data);
	अगर (ret < 0)
		वापस ret;

	अगर (info->lp3974_bug_workaround)
		msleep(2000);

	अगर (alrm->enabled)
		ret = max8998_rtc_start_alarm(info);

	वापस ret;
पूर्ण

अटल पूर्णांक max8998_rtc_alarm_irq_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा max8998_rtc_info *info = dev_get_drvdata(dev);

	अगर (enabled)
		वापस max8998_rtc_start_alarm(info);
	अन्यथा
		वापस max8998_rtc_stop_alarm(info);
पूर्ण

अटल irqवापस_t max8998_rtc_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8998_rtc_info *info = data;

	rtc_update_irq(info->rtc_dev, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops max8998_rtc_ops = अणु
	.पढ़ो_समय = max8998_rtc_पढ़ो_समय,
	.set_समय = max8998_rtc_set_समय,
	.पढ़ो_alarm = max8998_rtc_पढ़ो_alarm,
	.set_alarm = max8998_rtc_set_alarm,
	.alarm_irq_enable = max8998_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक max8998_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8998_dev *max8998 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8998_platक्रमm_data *pdata = max8998->pdata;
	काष्ठा max8998_rtc_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा max8998_rtc_info),
			GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->max8998 = max8998;
	info->rtc = max8998->rtc;

	platक्रमm_set_drvdata(pdev, info);

	info->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, "max8998-rtc",
			&max8998_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(info->rtc_dev)) अणु
		ret = PTR_ERR(info->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!max8998->irq_करोमुख्य)
		जाओ no_irq;

	info->irq = irq_create_mapping(max8998->irq_करोमुख्य, MAX8998_IRQ_ALARM0);
	अगर (!info->irq) अणु
		dev_warn(&pdev->dev, "Failed to map alarm IRQ\n");
		जाओ no_irq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq, शून्य,
				max8998_rtc_alarm_irq, 0, "rtc-alarm0", info);

	अगर (ret < 0)
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			info->irq, ret);

no_irq:
	dev_info(&pdev->dev, "RTC CHIP NAME: %s\n", pdev->id_entry->name);
	अगर (pdata && pdata->rtc_delay) अणु
		info->lp3974_bug_workaround = true;
		dev_warn(&pdev->dev, "LP3974 with RTC REGERR option."
				" RTC updates will be extremely slow.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max8998_rtc_id[] = अणु
	अणु "max8998-rtc", TYPE_MAX8998 पूर्ण,
	अणु "lp3974-rtc", TYPE_LP3974 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max8998_rtc_id);

अटल काष्ठा platक्रमm_driver max8998_rtc_driver = अणु
	.driver		= अणु
		.name	= "max8998-rtc",
	पूर्ण,
	.probe		= max8998_rtc_probe,
	.id_table	= max8998_rtc_id,
पूर्ण;

module_platक्रमm_driver(max8998_rtc_driver);

MODULE_AUTHOR("Minkyu Kang <mk7.kang@samsung.com>");
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_DESCRIPTION("Maxim MAX8998 RTC driver");
MODULE_LICENSE("GPL");
