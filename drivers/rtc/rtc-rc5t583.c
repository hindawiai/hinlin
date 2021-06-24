<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rtc-rc5t583.c -- RICOH RC5T583 Real Time Clock
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Venu Byravarasu <vbyravarasu@nvidia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/rc5t583.h>

काष्ठा rc5t583_rtc अणु
	काष्ठा rtc_device	*rtc;
	/* To store the list of enabled पूर्णांकerrupts, during प्रणाली suspend */
	u32 irqen;
पूर्ण;

/* Total number of RTC रेजिस्टरs needed to set समय*/
#घोषणा NUM_TIME_REGS	(RC5T583_RTC_YEAR - RC5T583_RTC_SEC + 1)

/* Total number of RTC रेजिस्टरs needed to set Y-Alarm*/
#घोषणा NUM_YAL_REGS	(RC5T583_RTC_AY_YEAR - RC5T583_RTC_AY_MIN + 1)

/* Set Y-Alarm पूर्णांकerrupt */
#घोषणा SET_YAL BIT(5)

/* Get Y-Alarm पूर्णांकerrupt status*/
#घोषणा GET_YAL_STATUS BIT(3)

अटल पूर्णांक rc5t583_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित enabled)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	u8 val;

	/* Set Y-Alarm, based on 'enabled' */
	val = enabled ? SET_YAL : 0;

	वापस regmap_update_bits(rc5t583->regmap, RC5T583_RTC_CTL1, SET_YAL,
		val);
पूर्ण

/*
 * Gets current rc5t583 RTC समय and date parameters.
 *
 * The RTC's समय/alarm representation is not what स_जमट(3) requires
 * Linux to use:
 *
 *  - Months are 1..12 vs Linux 0-11
 *  - Years are 0..99 vs Linux 1900..N (we assume 21st century)
 */
अटल पूर्णांक rc5t583_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	u8 rtc_data[NUM_TIME_REGS];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rc5t583->regmap, RC5T583_RTC_SEC, rtc_data,
		NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC read time failed with err:%d\n", ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(rtc_data[0]);
	पंचांग->पंचांग_min = bcd2bin(rtc_data[1]);
	पंचांग->पंचांग_hour = bcd2bin(rtc_data[2]);
	पंचांग->पंचांग_wday = bcd2bin(rtc_data[3]);
	पंचांग->पंचांग_mday = bcd2bin(rtc_data[4]);
	पंचांग->पंचांग_mon = bcd2bin(rtc_data[5]) - 1;
	पंचांग->पंचांग_year = bcd2bin(rtc_data[6]) + 100;

	वापस ret;
पूर्ण

अटल पूर्णांक rc5t583_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	अचिन्हित अक्षर rtc_data[NUM_TIME_REGS];
	पूर्णांक ret;

	rtc_data[0] = bin2bcd(पंचांग->पंचांग_sec);
	rtc_data[1] = bin2bcd(पंचांग->पंचांग_min);
	rtc_data[2] = bin2bcd(पंचांग->पंचांग_hour);
	rtc_data[3] = bin2bcd(पंचांग->पंचांग_wday);
	rtc_data[4] = bin2bcd(पंचांग->पंचांग_mday);
	rtc_data[5] = bin2bcd(पंचांग->पंचांग_mon + 1);
	rtc_data[6] = bin2bcd(पंचांग->पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(rc5t583->regmap, RC5T583_RTC_SEC, rtc_data,
		NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC set time failed with error %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rc5t583_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	अचिन्हित अक्षर alarm_data[NUM_YAL_REGS];
	u32 पूर्णांकerrupt_enable;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rc5t583->regmap, RC5T583_RTC_AY_MIN, alarm_data,
		NUM_YAL_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "rtc_read_alarm error %d\n", ret);
		वापस ret;
	पूर्ण

	alm->समय.पंचांग_sec = 0;
	alm->समय.पंचांग_min = bcd2bin(alarm_data[0]);
	alm->समय.पंचांग_hour = bcd2bin(alarm_data[1]);
	alm->समय.पंचांग_mday = bcd2bin(alarm_data[2]);
	alm->समय.पंचांग_mon = bcd2bin(alarm_data[3]) - 1;
	alm->समय.पंचांग_year = bcd2bin(alarm_data[4]) + 100;

	ret = regmap_पढ़ो(rc5t583->regmap, RC5T583_RTC_CTL1, &पूर्णांकerrupt_enable);
	अगर (ret < 0)
		वापस ret;

	/* check अगर YALE is set */
	अगर (पूर्णांकerrupt_enable & SET_YAL)
		alm->enabled = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक rc5t583_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	अचिन्हित अक्षर alarm_data[NUM_YAL_REGS];
	पूर्णांक ret;

	ret = rc5t583_rtc_alarm_irq_enable(dev, 0);
	अगर (ret)
		वापस ret;

	alarm_data[0] = bin2bcd(alm->समय.पंचांग_min);
	alarm_data[1] = bin2bcd(alm->समय.पंचांग_hour);
	alarm_data[2] = bin2bcd(alm->समय.पंचांग_mday);
	alarm_data[3] = bin2bcd(alm->समय.पंचांग_mon + 1);
	alarm_data[4] = bin2bcd(alm->समय.पंचांग_year - 100);

	ret = regmap_bulk_ग_लिखो(rc5t583->regmap, RC5T583_RTC_AY_MIN, alarm_data,
		NUM_YAL_REGS);
	अगर (ret) अणु
		dev_err(dev, "rtc_set_alarm error %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (alm->enabled)
		ret = rc5t583_rtc_alarm_irq_enable(dev, 1);

	वापस ret;
पूर्ण

अटल irqवापस_t rc5t583_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *rtc)
अणु
	काष्ठा device *dev = rtc;
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	काष्ठा rc5t583_rtc *rc5t583_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ events = 0;
	पूर्णांक ret;
	u32 rtc_reg;

	ret = regmap_पढ़ो(rc5t583->regmap, RC5T583_RTC_CTL2, &rtc_reg);
	अगर (ret < 0)
		वापस IRQ_NONE;

	अगर (rtc_reg & GET_YAL_STATUS) अणु
		events = RTC_IRQF | RTC_AF;
		/* clear pending Y-alarm पूर्णांकerrupt bit */
		rtc_reg &= ~GET_YAL_STATUS;
	पूर्ण

	ret = regmap_ग_लिखो(rc5t583->regmap, RC5T583_RTC_CTL2, rtc_reg);
	अगर (ret)
		वापस IRQ_NONE;

	/* Notअगरy RTC core on event */
	rtc_update_irq(rc5t583_rtc->rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rc5t583_rtc_ops = अणु
	.पढ़ो_समय	= rc5t583_rtc_पढ़ो_समय,
	.set_समय	= rc5t583_rtc_set_समय,
	.पढ़ो_alarm	= rc5t583_rtc_पढ़ो_alarm,
	.set_alarm	= rc5t583_rtc_set_alarm,
	.alarm_irq_enable = rc5t583_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक rc5t583_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा rc5t583_rtc *ricoh_rtc;
	काष्ठा rc5t583_platक्रमm_data *pmic_plat_data;
	पूर्णांक ret;
	पूर्णांक irq;

	ricoh_rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा rc5t583_rtc),
			GFP_KERNEL);
	अगर (!ricoh_rtc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ricoh_rtc);

	/* Clear pending पूर्णांकerrupts */
	ret = regmap_ग_लिखो(rc5t583->regmap, RC5T583_RTC_CTL2, 0);
	अगर (ret < 0)
		वापस ret;

	/* clear RTC Adjust रेजिस्टर */
	ret = regmap_ग_लिखो(rc5t583->regmap, RC5T583_RTC_ADJ, 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to program rtc_adjust reg\n");
		वापस -EBUSY;
	पूर्ण

	pmic_plat_data = dev_get_platdata(rc5t583->dev);
	irq = pmic_plat_data->irq_base;
	अगर (irq <= 0) अणु
		dev_warn(&pdev->dev, "Wake up is not possible as irq = %d\n",
			irq);
		वापस ret;
	पूर्ण

	irq += RC5T583_IRQ_YALE;
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
		rc5t583_rtc_पूर्णांकerrupt, IRQF_TRIGGER_LOW,
		"rtc-rc5t583", &pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "IRQ is not free.\n");
		वापस ret;
	पूर्ण
	device_init_wakeup(&pdev->dev, 1);

	ricoh_rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
		&rc5t583_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(ricoh_rtc->rtc)) अणु
		ret = PTR_ERR(ricoh_rtc->rtc);
		dev_err(&pdev->dev, "RTC device register: err %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Disable rc5t583 RTC पूर्णांकerrupts.
 * Sets status flag to मुक्त.
 */
अटल पूर्णांक rc5t583_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rc5t583_rtc *rc5t583_rtc = platक्रमm_get_drvdata(pdev);

	rc5t583_rtc_alarm_irq_enable(&rc5t583_rtc->rtc->dev, 0);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rc5t583_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	काष्ठा rc5t583_rtc *rc5t583_rtc = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Store current list of enabled पूर्णांकerrupts*/
	ret = regmap_पढ़ो(rc5t583->regmap, RC5T583_RTC_CTL1,
		&rc5t583_rtc->irqen);
	वापस ret;
पूर्ण

अटल पूर्णांक rc5t583_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	काष्ठा rc5t583_rtc *rc5t583_rtc = dev_get_drvdata(dev);

	/* Restore list of enabled पूर्णांकerrupts beक्रमe suspend */
	वापस regmap_ग_लिखो(rc5t583->regmap, RC5T583_RTC_CTL1,
		rc5t583_rtc->irqen);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rc5t583_rtc_pm_ops, rc5t583_rtc_suspend,
			rc5t583_rtc_resume);

अटल काष्ठा platक्रमm_driver rc5t583_rtc_driver = अणु
	.probe		= rc5t583_rtc_probe,
	.हटाओ		= rc5t583_rtc_हटाओ,
	.driver		= अणु
		.name	= "rtc-rc5t583",
		.pm	= &rc5t583_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rc5t583_rtc_driver);
MODULE_ALIAS("platform:rtc-rc5t583");
MODULE_AUTHOR("Venu Byravarasu <vbyravarasu@nvidia.com>");
MODULE_LICENSE("GPL v2");
