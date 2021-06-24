<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Real समय घड़ी driver क्रम DA9055
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: Dajun Dajun Chen <dajun.chen@diasemi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#समावेश <linux/mfd/da9055/core.h>
#समावेश <linux/mfd/da9055/reg.h>
#समावेश <linux/mfd/da9055/pdata.h>

काष्ठा da9055_rtc अणु
	काष्ठा rtc_device *rtc;
	काष्ठा da9055 *da9055;
	पूर्णांक alarm_enable;
पूर्ण;

अटल पूर्णांक da9055_rtc_enable_alarm(काष्ठा da9055_rtc *rtc, bool enable)
अणु
	पूर्णांक ret;
	अगर (enable) अणु
		ret = da9055_reg_update(rtc->da9055, DA9055_REG_ALARM_Y,
					DA9055_RTC_ALM_EN,
					DA9055_RTC_ALM_EN);
		अगर (ret != 0)
			dev_err(rtc->da9055->dev, "Failed to enable ALM: %d\n",
				ret);
		rtc->alarm_enable = 1;
	पूर्ण अन्यथा अणु
		ret = da9055_reg_update(rtc->da9055, DA9055_REG_ALARM_Y,
					DA9055_RTC_ALM_EN, 0);
		अगर (ret != 0)
			dev_err(rtc->da9055->dev,
				"Failed to disable ALM: %d\n", ret);
		rtc->alarm_enable = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल irqवापस_t da9055_rtc_alm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9055_rtc *rtc = data;

	da9055_rtc_enable_alarm(rtc, 0);
	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9055_पढ़ो_alarm(काष्ठा da9055 *da9055, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t v[5];

	ret = da9055_group_पढ़ो(da9055, DA9055_REG_ALARM_MI, 5, v);
	अगर (ret != 0) अणु
		dev_err(da9055->dev, "Failed to group read ALM: %d\n", ret);
		वापस ret;
	पूर्ण

	rtc_पंचांग->पंचांग_year = (v[4] & DA9055_RTC_ALM_YEAR) + 100;
	rtc_पंचांग->पंचांग_mon  = (v[3] & DA9055_RTC_ALM_MONTH) - 1;
	rtc_पंचांग->पंचांग_mday = v[2] & DA9055_RTC_ALM_DAY;
	rtc_पंचांग->पंचांग_hour = v[1] & DA9055_RTC_ALM_HOUR;
	rtc_पंचांग->पंचांग_min  = v[0] & DA9055_RTC_ALM_MIN;
	rtc_पंचांग->पंचांग_sec = 0;

	वापस rtc_valid_पंचांग(rtc_पंचांग);
पूर्ण

अटल पूर्णांक da9055_set_alarm(काष्ठा da9055 *da9055, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t v[2];

	rtc_पंचांग->पंचांग_year -= 100;
	rtc_पंचांग->पंचांग_mon += 1;

	ret = da9055_reg_update(da9055, DA9055_REG_ALARM_MI,
				DA9055_RTC_ALM_MIN, rtc_पंचांग->पंचांग_min);
	अगर (ret != 0) अणु
		dev_err(da9055->dev, "Failed to write ALRM MIN: %d\n", ret);
		वापस ret;
	पूर्ण

	v[0] = rtc_पंचांग->पंचांग_hour;
	v[1] = rtc_पंचांग->पंचांग_mday;

	ret = da9055_group_ग_लिखो(da9055, DA9055_REG_ALARM_H, 2, v);
	अगर (ret < 0)
		वापस ret;

	ret = da9055_reg_update(da9055, DA9055_REG_ALARM_MO,
				DA9055_RTC_ALM_MONTH, rtc_पंचांग->पंचांग_mon);
	अगर (ret < 0)
		dev_err(da9055->dev, "Failed to write ALM Month:%d\n", ret);

	ret = da9055_reg_update(da9055, DA9055_REG_ALARM_Y,
				DA9055_RTC_ALM_YEAR, rtc_पंचांग->पंचांग_year);
	अगर (ret < 0)
		dev_err(da9055->dev, "Failed to write ALM Year:%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9055_rtc_get_alarm_status(काष्ठा da9055 *da9055)
अणु
	पूर्णांक ret;

	ret = da9055_reg_पढ़ो(da9055, DA9055_REG_ALARM_Y);
	अगर (ret < 0) अणु
		dev_err(da9055->dev, "Failed to read ALM: %d\n", ret);
		वापस ret;
	पूर्ण
	ret &= DA9055_RTC_ALM_EN;
	वापस (ret > 0) ? 1 : 0;
पूर्ण

अटल पूर्णांक da9055_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा da9055_rtc *rtc = dev_get_drvdata(dev);
	uपूर्णांक8_t v[6];
	पूर्णांक ret;

	ret = da9055_reg_पढ़ो(rtc->da9055, DA9055_REG_COUNT_S);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Registers are only valid when RTC_READ
	 * status bit is निश्चितed
	 */
	अगर (!(ret & DA9055_RTC_READ))
		वापस -EBUSY;

	ret = da9055_group_पढ़ो(rtc->da9055, DA9055_REG_COUNT_S, 6, v);
	अगर (ret < 0) अणु
		dev_err(rtc->da9055->dev, "Failed to read RTC time : %d\n",
			ret);
		वापस ret;
	पूर्ण

	rtc_पंचांग->पंचांग_year = (v[5] & DA9055_RTC_YEAR) + 100;
	rtc_पंचांग->पंचांग_mon  = (v[4] & DA9055_RTC_MONTH) - 1;
	rtc_पंचांग->पंचांग_mday = v[3] & DA9055_RTC_DAY;
	rtc_पंचांग->पंचांग_hour = v[2] & DA9055_RTC_HOUR;
	rtc_पंचांग->पंचांग_min  = v[1] & DA9055_RTC_MIN;
	rtc_पंचांग->पंचांग_sec  = v[0] & DA9055_RTC_SEC;

	वापस 0;
पूर्ण

अटल पूर्णांक da9055_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा da9055_rtc *rtc;
	uपूर्णांक8_t v[6];

	rtc = dev_get_drvdata(dev);

	v[0] = पंचांग->पंचांग_sec;
	v[1] = पंचांग->पंचांग_min;
	v[2] = पंचांग->पंचांग_hour;
	v[3] = पंचांग->पंचांग_mday;
	v[4] = पंचांग->पंचांग_mon + 1;
	v[5] = पंचांग->पंचांग_year - 100;

	वापस da9055_group_ग_लिखो(rtc->da9055, DA9055_REG_COUNT_S, 6, v);
पूर्ण

अटल पूर्णांक da9055_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	पूर्णांक ret;
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	काष्ठा da9055_rtc *rtc = dev_get_drvdata(dev);

	ret = da9055_पढ़ो_alarm(rtc->da9055, पंचांग);

	अगर (ret)
		वापस ret;

	alrm->enabled = da9055_rtc_get_alarm_status(rtc->da9055);

	वापस 0;
पूर्ण

अटल पूर्णांक da9055_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	पूर्णांक ret;
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	काष्ठा da9055_rtc *rtc = dev_get_drvdata(dev);

	ret = da9055_rtc_enable_alarm(rtc, 0);
	अगर (ret < 0)
		वापस ret;

	ret = da9055_set_alarm(rtc->da9055, पंचांग);
	अगर (ret)
		वापस ret;

	ret = da9055_rtc_enable_alarm(rtc, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक da9055_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा da9055_rtc *rtc = dev_get_drvdata(dev);

	वापस da9055_rtc_enable_alarm(rtc, enabled);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops da9055_rtc_ops = अणु
	.पढ़ो_समय	= da9055_rtc_पढ़ो_समय,
	.set_समय	= da9055_rtc_set_समय,
	.पढ़ो_alarm	= da9055_rtc_पढ़ो_alarm,
	.set_alarm	= da9055_rtc_set_alarm,
	.alarm_irq_enable = da9055_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक da9055_rtc_device_init(काष्ठा da9055 *da9055,
					काष्ठा da9055_pdata *pdata)
अणु
	पूर्णांक ret;

	/* Enable RTC and the पूर्णांकernal Crystal */
	ret = da9055_reg_update(da9055, DA9055_REG_CONTROL_B,
				DA9055_RTC_EN, DA9055_RTC_EN);
	अगर (ret < 0)
		वापस ret;
	ret = da9055_reg_update(da9055, DA9055_REG_EN_32K,
				DA9055_CRYSTAL_EN, DA9055_CRYSTAL_EN);
	अगर (ret < 0)
		वापस ret;

	/* Enable RTC in Power Down mode */
	ret = da9055_reg_update(da9055, DA9055_REG_CONTROL_B,
				DA9055_RTC_MODE_PD, DA9055_RTC_MODE_PD);
	अगर (ret < 0)
		वापस ret;

	/* Enable RTC in Reset mode */
	अगर (pdata && pdata->reset_enable) अणु
		ret = da9055_reg_update(da9055, DA9055_REG_CONTROL_B,
					DA9055_RTC_MODE_SD,
					DA9055_RTC_MODE_SD <<
					DA9055_RTC_MODE_SD_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Disable the RTC TICK ALM */
	ret = da9055_reg_update(da9055, DA9055_REG_ALARM_MO,
				DA9055_RTC_TICK_WAKE_MASK, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक da9055_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9055_rtc *rtc;
	काष्ठा da9055_pdata *pdata = शून्य;
	पूर्णांक ret, alm_irq;

	rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा da9055_rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->da9055 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(rtc->da9055->dev);
	platक्रमm_set_drvdata(pdev, rtc);

	ret = da9055_rtc_device_init(rtc->da9055, pdata);
	अगर (ret < 0)
		जाओ err_rtc;

	ret = da9055_reg_पढ़ो(rtc->da9055, DA9055_REG_ALARM_Y);
	अगर (ret < 0)
		जाओ err_rtc;

	अगर (ret & DA9055_RTC_ALM_EN)
		rtc->alarm_enable = 1;

	device_init_wakeup(&pdev->dev, 1);

	rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
					&da9055_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc->rtc)) अणु
		ret = PTR_ERR(rtc->rtc);
		जाओ err_rtc;
	पूर्ण

	alm_irq = platक्रमm_get_irq_byname(pdev, "ALM");
	अगर (alm_irq < 0)
		वापस alm_irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, alm_irq, शून्य,
					da9055_rtc_alm_irq,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"ALM", rtc);
	अगर (ret != 0)
		dev_err(rtc->da9055->dev, "irq registration failed: %d\n", ret);

err_rtc:
	वापस ret;

पूर्ण

#अगर_घोषित CONFIG_PM
/* Turn off the alarm अगर it should not be a wake source. */
अटल पूर्णांक da9055_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा da9055_rtc *rtc = dev_get_drvdata(&pdev->dev);
	पूर्णांक ret;

	अगर (!device_may_wakeup(&pdev->dev)) अणु
		/* Disable the ALM IRQ */
		ret = da9055_rtc_enable_alarm(rtc, 0);
		अगर (ret < 0)
			dev_err(&pdev->dev, "Failed to disable RTC ALM\n");
	पूर्ण

	वापस 0;
पूर्ण

/* Enable the alarm अगर it should be enabled (in हाल it was disabled to
 * prevent use as a wake source).
 */
अटल पूर्णांक da9055_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा da9055_rtc *rtc = dev_get_drvdata(&pdev->dev);
	पूर्णांक ret;

	अगर (!device_may_wakeup(&pdev->dev)) अणु
		अगर (rtc->alarm_enable) अणु
			ret = da9055_rtc_enable_alarm(rtc, 1);
			अगर (ret < 0)
				dev_err(&pdev->dev,
					"Failed to restart RTC ALM\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Unconditionally disable the alarm */
अटल पूर्णांक da9055_rtc_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा da9055_rtc *rtc = dev_get_drvdata(&pdev->dev);
	पूर्णांक ret;

	ret = da9055_rtc_enable_alarm(rtc, 0);
	अगर (ret < 0)
		dev_err(&pdev->dev, "Failed to freeze RTC ALMs\n");

	वापस 0;

पूर्ण
#अन्यथा
#घोषणा da9055_rtc_suspend शून्य
#घोषणा da9055_rtc_resume शून्य
#घोषणा da9055_rtc_मुक्तze शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops da9055_rtc_pm_ops = अणु
	.suspend = da9055_rtc_suspend,
	.resume = da9055_rtc_resume,

	.मुक्तze = da9055_rtc_मुक्तze,
	.thaw = da9055_rtc_resume,
	.restore = da9055_rtc_resume,

	.घातeroff = da9055_rtc_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver da9055_rtc_driver = अणु
	.probe  = da9055_rtc_probe,
	.driver = अणु
		.name   = "da9055-rtc",
		.pm = &da9055_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9055_rtc_driver);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("RTC driver for Dialog DA9055 PMIC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9055-rtc");
