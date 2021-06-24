<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rtc-as3722.c - Real Time Clock driver क्रम ams AS3722 PMICs
 *
 * Copyright (C) 2013 ams AG
 * Copyright (c) 2013, NVIDIA Corporation. All rights reserved.
 *
 * Author: Florian Lobmaier <florian.lobmaier@ams.com>
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/bcd.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/as3722.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/समय.स>

#घोषणा AS3722_RTC_START_YEAR	  2000
काष्ठा as3722_rtc अणु
	काष्ठा rtc_device	*rtc;
	काष्ठा device		*dev;
	काष्ठा as3722		*as3722;
	पूर्णांक			alarm_irq;
	bool			irq_enable;
पूर्ण;

अटल व्योम as3722_समय_प्रकारo_reg(u8 *rbuff, काष्ठा rtc_समय *पंचांग)
अणु
	rbuff[0] = bin2bcd(पंचांग->पंचांग_sec);
	rbuff[1] = bin2bcd(पंचांग->पंचांग_min);
	rbuff[2] = bin2bcd(पंचांग->पंचांग_hour);
	rbuff[3] = bin2bcd(पंचांग->पंचांग_mday);
	rbuff[4] = bin2bcd(पंचांग->पंचांग_mon + 1);
	rbuff[5] = bin2bcd(पंचांग->पंचांग_year - (AS3722_RTC_START_YEAR - 1900));
पूर्ण

अटल व्योम as3722_reg_to_समय(u8 *rbuff, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec = bcd2bin(rbuff[0] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(rbuff[1] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(rbuff[2] & 0x3F);
	पंचांग->पंचांग_mday = bcd2bin(rbuff[3] & 0x3F);
	पंचांग->पंचांग_mon = bcd2bin(rbuff[4] & 0x1F) - 1;
	पंचांग->पंचांग_year = (AS3722_RTC_START_YEAR - 1900) + bcd2bin(rbuff[5] & 0x7F);
	वापस;
पूर्ण

अटल पूर्णांक as3722_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा as3722_rtc *as3722_rtc = dev_get_drvdata(dev);
	काष्ठा as3722 *as3722 = as3722_rtc->as3722;
	u8 as_समय_array[6];
	पूर्णांक ret;

	ret = as3722_block_पढ़ो(as3722, AS3722_RTC_SECOND_REG,
			6, as_समय_array);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_SECOND reg block read failed %d\n", ret);
		वापस ret;
	पूर्ण
	as3722_reg_to_समय(as_समय_array, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा as3722_rtc *as3722_rtc = dev_get_drvdata(dev);
	काष्ठा as3722 *as3722 = as3722_rtc->as3722;
	u8 as_समय_array[6];
	पूर्णांक ret;

	अगर (पंचांग->पंचांग_year < (AS3722_RTC_START_YEAR - 1900))
		वापस -EINVAL;

	as3722_समय_प्रकारo_reg(as_समय_array, पंचांग);
	ret = as3722_block_ग_लिखो(as3722, AS3722_RTC_SECOND_REG, 6,
			as_समय_array);
	अगर (ret < 0)
		dev_err(dev, "RTC_SECOND reg block write failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक as3722_rtc_alarm_irq_enable(काष्ठा device *dev,
		अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा as3722_rtc *as3722_rtc = dev_get_drvdata(dev);

	अगर (enabled && !as3722_rtc->irq_enable) अणु
		enable_irq(as3722_rtc->alarm_irq);
		as3722_rtc->irq_enable = true;
	पूर्ण अन्यथा अगर (!enabled && as3722_rtc->irq_enable)  अणु
		disable_irq(as3722_rtc->alarm_irq);
		as3722_rtc->irq_enable = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा as3722_rtc *as3722_rtc = dev_get_drvdata(dev);
	काष्ठा as3722 *as3722 = as3722_rtc->as3722;
	u8 as_समय_array[6];
	पूर्णांक ret;

	ret = as3722_block_पढ़ो(as3722, AS3722_RTC_ALARM_SECOND_REG, 6,
			as_समय_array);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_ALARM_SECOND block read failed %d\n", ret);
		वापस ret;
	पूर्ण

	as3722_reg_to_समय(as_समय_array, &alrm->समय);
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा as3722_rtc *as3722_rtc = dev_get_drvdata(dev);
	काष्ठा as3722 *as3722 = as3722_rtc->as3722;
	u8 as_समय_array[6];
	पूर्णांक ret;

	अगर (alrm->समय.पंचांग_year < (AS3722_RTC_START_YEAR - 1900))
		वापस -EINVAL;

	ret = as3722_rtc_alarm_irq_enable(dev, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "Disable RTC alarm failed\n");
		वापस ret;
	पूर्ण

	as3722_समय_प्रकारo_reg(as_समय_array, &alrm->समय);
	ret = as3722_block_ग_लिखो(as3722, AS3722_RTC_ALARM_SECOND_REG, 6,
			as_समय_array);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC_ALARM_SECOND block write failed %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (alrm->enabled)
		ret = as3722_rtc_alarm_irq_enable(dev, alrm->enabled);
	वापस ret;
पूर्ण

अटल irqवापस_t as3722_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा as3722_rtc *as3722_rtc = data;

	rtc_update_irq(as3722_rtc->rtc, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops as3722_rtc_ops = अणु
	.पढ़ो_समय = as3722_rtc_पढ़ो_समय,
	.set_समय = as3722_rtc_set_समय,
	.पढ़ो_alarm = as3722_rtc_पढ़ो_alarm,
	.set_alarm = as3722_rtc_set_alarm,
	.alarm_irq_enable = as3722_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक as3722_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा as3722 *as3722 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा as3722_rtc *as3722_rtc;
	पूर्णांक ret;

	as3722_rtc = devm_kzalloc(&pdev->dev, माप(*as3722_rtc), GFP_KERNEL);
	अगर (!as3722_rtc)
		वापस -ENOMEM;

	as3722_rtc->as3722 = as3722;
	as3722_rtc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, as3722_rtc);

	/* Enable the RTC to make sure it is running. */
	ret = as3722_update_bits(as3722, AS3722_RTC_CONTROL_REG,
			AS3722_RTC_ON | AS3722_RTC_ALARM_WAKEUP_EN,
			AS3722_RTC_ON | AS3722_RTC_ALARM_WAKEUP_EN);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "RTC_CONTROL reg write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);

	as3722_rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "as3722-rtc",
				&as3722_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(as3722_rtc->rtc)) अणु
		ret = PTR_ERR(as3722_rtc->rtc);
		dev_err(&pdev->dev, "RTC register failed: %d\n", ret);
		वापस ret;
	पूर्ण

	as3722_rtc->alarm_irq = platक्रमm_get_irq(pdev, 0);
	dev_info(&pdev->dev, "RTC interrupt %d\n", as3722_rtc->alarm_irq);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, as3722_rtc->alarm_irq, शून्य,
			as3722_alarm_irq, IRQF_ONESHOT,
			"rtc-alarm", as3722_rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request alarm IRQ %d: %d\n",
				as3722_rtc->alarm_irq, ret);
		वापस ret;
	पूर्ण
	disable_irq(as3722_rtc->alarm_irq);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक as3722_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा as3722_rtc *as3722_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(as3722_rtc->alarm_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक as3722_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा as3722_rtc *as3722_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(as3722_rtc->alarm_irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(as3722_rtc_pm_ops, as3722_rtc_suspend,
			 as3722_rtc_resume);

अटल काष्ठा platक्रमm_driver as3722_rtc_driver = अणु
	.probe = as3722_rtc_probe,
	.driver = अणु
		.name = "as3722-rtc",
		.pm = &as3722_rtc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(as3722_rtc_driver);

MODULE_DESCRIPTION("RTC driver for AS3722 PMICs");
MODULE_ALIAS("platform:as3722-rtc");
MODULE_AUTHOR("Florian Lobmaier <florian.lobmaier@ams.com>");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL");
