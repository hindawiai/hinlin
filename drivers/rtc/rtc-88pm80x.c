<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real Time Clock driver क्रम Marvell 88PM80x PMIC
 *
 * Copyright (c) 2012 Marvell International Ltd.
 *  Wenzeng Chen<wzch@marvell.com>
 *  Qiao Zhou <zhouqiao@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/88pm80x.h>
#समावेश <linux/rtc.h>

#घोषणा PM800_RTC_COUNTER1		(0xD1)
#घोषणा PM800_RTC_COUNTER2		(0xD2)
#घोषणा PM800_RTC_COUNTER3		(0xD3)
#घोषणा PM800_RTC_COUNTER4		(0xD4)
#घोषणा PM800_RTC_EXPIRE1_1		(0xD5)
#घोषणा PM800_RTC_EXPIRE1_2		(0xD6)
#घोषणा PM800_RTC_EXPIRE1_3		(0xD7)
#घोषणा PM800_RTC_EXPIRE1_4		(0xD8)
#घोषणा PM800_RTC_TRIM1			(0xD9)
#घोषणा PM800_RTC_TRIM2			(0xDA)
#घोषणा PM800_RTC_TRIM3			(0xDB)
#घोषणा PM800_RTC_TRIM4			(0xDC)
#घोषणा PM800_RTC_EXPIRE2_1		(0xDD)
#घोषणा PM800_RTC_EXPIRE2_2		(0xDE)
#घोषणा PM800_RTC_EXPIRE2_3		(0xDF)
#घोषणा PM800_RTC_EXPIRE2_4		(0xE0)

#घोषणा PM800_POWER_DOWN_LOG1	(0xE5)
#घोषणा PM800_POWER_DOWN_LOG2	(0xE6)

काष्ठा pm80x_rtc_info अणु
	काष्ठा pm80x_chip *chip;
	काष्ठा regmap *map;
	काष्ठा rtc_device *rtc_dev;
	काष्ठा device *dev;

	पूर्णांक irq;
पूर्ण;

अटल irqवापस_t rtc_update_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm80x_rtc_info *info = (काष्ठा pm80x_rtc_info *)data;
	पूर्णांक mask;

	mask = PM800_ALARM | PM800_ALARM_WAKEUP;
	regmap_update_bits(info->map, PM800_RTC_CONTROL, mask | PM800_ALARM1_EN,
			   mask);
	rtc_update_irq(info->rtc_dev, 1, RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pm80x_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा pm80x_rtc_info *info = dev_get_drvdata(dev);

	अगर (enabled)
		regmap_update_bits(info->map, PM800_RTC_CONTROL,
				   PM800_ALARM1_EN, PM800_ALARM1_EN);
	अन्यथा
		regmap_update_bits(info->map, PM800_RTC_CONTROL,
				   PM800_ALARM1_EN, 0);
	वापस 0;
पूर्ण

/*
 * Calculate the next alarm समय given the requested alarm समय mask
 * and the current समय.
 */
अटल व्योम rtc_next_alarm_समय(काष्ठा rtc_समय *next, काष्ठा rtc_समय *now,
				काष्ठा rtc_समय *alrm)
अणु
	अचिन्हित दीर्घ next_समय;
	अचिन्हित दीर्घ now_समय;

	next->पंचांग_year = now->पंचांग_year;
	next->पंचांग_mon = now->पंचांग_mon;
	next->पंचांग_mday = now->पंचांग_mday;
	next->पंचांग_hour = alrm->पंचांग_hour;
	next->पंचांग_min = alrm->पंचांग_min;
	next->पंचांग_sec = alrm->पंचांग_sec;

	now_समय = rtc_पंचांग_to_समय64(now);
	next_समय = rtc_पंचांग_to_समय64(next);

	अगर (next_समय < now_समय) अणु
		/* Advance one day */
		next_समय += 60 * 60 * 24;
		rtc_समय64_to_पंचांग(next_समय, next);
	पूर्ण
पूर्ण

अटल पूर्णांक pm80x_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pm80x_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[4];
	अचिन्हित दीर्घ ticks, base, data;
	regmap_raw_पढ़ो(info->map, PM800_RTC_EXPIRE2_1, buf, 4);
	base = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	dev_dbg(info->dev, "%x-%x-%x-%x\n", buf[0], buf[1], buf[2], buf[3]);

	/* load 32-bit पढ़ो-only counter */
	regmap_raw_पढ़ो(info->map, PM800_RTC_COUNTER1, buf, 4);
	data = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);
	rtc_समय64_to_पंचांग(ticks, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक pm80x_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pm80x_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[4];
	अचिन्हित दीर्घ ticks, base, data;

	ticks = rtc_पंचांग_to_समय64(पंचांग);

	/* load 32-bit पढ़ो-only counter */
	regmap_raw_पढ़ो(info->map, PM800_RTC_COUNTER1, buf, 4);
	data = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	base = ticks - data;
	dev_dbg(info->dev, "set base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);
	buf[0] = base & 0xFF;
	buf[1] = (base >> 8) & 0xFF;
	buf[2] = (base >> 16) & 0xFF;
	buf[3] = (base >> 24) & 0xFF;
	regmap_raw_ग_लिखो(info->map, PM800_RTC_EXPIRE2_1, buf, 4);

	वापस 0;
पूर्ण

अटल पूर्णांक pm80x_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pm80x_rtc_info *info = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[4];
	अचिन्हित दीर्घ ticks, base, data;
	पूर्णांक ret;

	regmap_raw_पढ़ो(info->map, PM800_RTC_EXPIRE2_1, buf, 4);
	base = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	dev_dbg(info->dev, "%x-%x-%x-%x\n", buf[0], buf[1], buf[2], buf[3]);

	regmap_raw_पढ़ो(info->map, PM800_RTC_EXPIRE1_1, buf, 4);
	data = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);

	rtc_समय64_to_पंचांग(ticks, &alrm->समय);
	regmap_पढ़ो(info->map, PM800_RTC_CONTROL, &ret);
	alrm->enabled = (ret & PM800_ALARM1_EN) ? 1 : 0;
	alrm->pending = (ret & (PM800_ALARM | PM800_ALARM_WAKEUP)) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक pm80x_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pm80x_rtc_info *info = dev_get_drvdata(dev);
	काष्ठा rtc_समय now_पंचांग, alarm_पंचांग;
	अचिन्हित दीर्घ ticks, base, data;
	अचिन्हित अक्षर buf[4];
	पूर्णांक mask;

	regmap_update_bits(info->map, PM800_RTC_CONTROL, PM800_ALARM1_EN, 0);

	regmap_raw_पढ़ो(info->map, PM800_RTC_EXPIRE2_1, buf, 4);
	base = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	dev_dbg(info->dev, "%x-%x-%x-%x\n", buf[0], buf[1], buf[2], buf[3]);

	/* load 32-bit पढ़ो-only counter */
	regmap_raw_पढ़ो(info->map, PM800_RTC_COUNTER1, buf, 4);
	data = ((अचिन्हित दीर्घ)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);

	rtc_समय64_to_पंचांग(ticks, &now_पंचांग);
	dev_dbg(info->dev, "%s, now time : %lu\n", __func__, ticks);
	rtc_next_alarm_समय(&alarm_पंचांग, &now_पंचांग, &alrm->समय);
	/* get new ticks क्रम alarm in 24 hours */
	ticks = rtc_पंचांग_to_समय64(&alarm_पंचांग);
	dev_dbg(info->dev, "%s, alarm time: %lu\n", __func__, ticks);
	data = ticks - base;

	buf[0] = data & 0xff;
	buf[1] = (data >> 8) & 0xff;
	buf[2] = (data >> 16) & 0xff;
	buf[3] = (data >> 24) & 0xff;
	regmap_raw_ग_लिखो(info->map, PM800_RTC_EXPIRE1_1, buf, 4);
	अगर (alrm->enabled) अणु
		mask = PM800_ALARM | PM800_ALARM_WAKEUP | PM800_ALARM1_EN;
		regmap_update_bits(info->map, PM800_RTC_CONTROL, mask, mask);
	पूर्ण अन्यथा अणु
		mask = PM800_ALARM | PM800_ALARM_WAKEUP | PM800_ALARM1_EN;
		regmap_update_bits(info->map, PM800_RTC_CONTROL, mask,
				   PM800_ALARM | PM800_ALARM_WAKEUP);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pm80x_rtc_ops = अणु
	.पढ़ो_समय = pm80x_rtc_पढ़ो_समय,
	.set_समय = pm80x_rtc_set_समय,
	.पढ़ो_alarm = pm80x_rtc_पढ़ो_alarm,
	.set_alarm = pm80x_rtc_set_alarm,
	.alarm_irq_enable = pm80x_rtc_alarm_irq_enable,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pm80x_rtc_suspend(काष्ठा device *dev)
अणु
	वापस pm80x_dev_suspend(dev);
पूर्ण

अटल पूर्णांक pm80x_rtc_resume(काष्ठा device *dev)
अणु
	वापस pm80x_dev_resume(dev);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pm80x_rtc_pm_ops, pm80x_rtc_suspend, pm80x_rtc_resume);

अटल पूर्णांक pm80x_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm80x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm80x_rtc_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा pm80x_rtc_info *info;
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (!pdata && !node) अणु
		dev_err(&pdev->dev,
			"pm80x-rtc requires platform data or of_node\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata) अणु
		pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata) अणु
			dev_err(&pdev->dev, "failed to allocate memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	info =
	    devm_kzalloc(&pdev->dev, माप(काष्ठा pm80x_rtc_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->irq = platक्रमm_get_irq(pdev, 0);
	अगर (info->irq < 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	info->chip = chip;
	info->map = chip->regmap;
	अगर (!info->map) अणु
		dev_err(&pdev->dev, "no regmap!\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	info->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, info);

	info->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(info->rtc_dev))
		वापस PTR_ERR(info->rtc_dev);

	ret = pm80x_request_irq(chip, info->irq, rtc_update_handler,
				IRQF_ONESHOT, "rtc", info);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq, ret);
		जाओ out;
	पूर्ण

	info->rtc_dev->ops = &pm80x_rtc_ops;
	info->rtc_dev->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(info->rtc_dev);
	अगर (ret)
		जाओ out_rtc;

	/*
	 * enable पूर्णांकernal XO instead of पूर्णांकernal 3.25MHz घड़ी since it can
	 * मुक्त running in PMIC घातer-करोwn state.
	 */
	regmap_update_bits(info->map, PM800_RTC_CONTROL, PM800_RTC1_USE_XO,
			   PM800_RTC1_USE_XO);

	/* remember whether this घातer up is caused by PMIC RTC or not */
	info->rtc_dev->dev.platक्रमm_data = &pdata->rtc_wakeup;

	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
out_rtc:
	pm80x_मुक्त_irq(chip, info->irq, info);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pm80x_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm80x_rtc_info *info = platक्रमm_get_drvdata(pdev);
	pm80x_मुक्त_irq(info->chip, info->irq, info);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm80x_rtc_driver = अणु
	.driver = अणु
		   .name = "88pm80x-rtc",
		   .pm = &pm80x_rtc_pm_ops,
		   पूर्ण,
	.probe = pm80x_rtc_probe,
	.हटाओ = pm80x_rtc_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm80x_rtc_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Marvell 88PM80x RTC driver");
MODULE_AUTHOR("Qiao Zhou <zhouqiao@marvell.com>");
MODULE_ALIAS("platform:88pm80x-rtc");
