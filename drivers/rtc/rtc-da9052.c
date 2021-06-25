<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Real समय घड़ी driver क्रम DA9052
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: Dajun Dajun Chen <dajun.chen@diasemi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>

#घोषणा rtc_err(rtc, fmt, ...) \
		dev_err(rtc->da9052->dev, "%s: " fmt, __func__, ##__VA_ARGS__)

#घोषणा DA9052_GET_TIME_RETRIES 5

काष्ठा da9052_rtc अणु
	काष्ठा rtc_device *rtc;
	काष्ठा da9052 *da9052;
पूर्ण;

अटल पूर्णांक da9052_rtc_enable_alarm(काष्ठा da9052_rtc *rtc, bool enable)
अणु
	पूर्णांक ret;
	अगर (enable) अणु
		ret = da9052_reg_update(rtc->da9052, DA9052_ALARM_Y_REG,
				DA9052_ALARM_Y_ALARM_ON|DA9052_ALARM_Y_TICK_ON,
				DA9052_ALARM_Y_ALARM_ON);
		अगर (ret != 0)
			rtc_err(rtc, "Failed to enable ALM: %d\n", ret);
	पूर्ण अन्यथा अणु
		ret = da9052_reg_update(rtc->da9052, DA9052_ALARM_Y_REG,
			DA9052_ALARM_Y_ALARM_ON|DA9052_ALARM_Y_TICK_ON, 0);
		अगर (ret != 0)
			rtc_err(rtc, "Write error: %d\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल irqवापस_t da9052_rtc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9052_rtc *rtc = data;

	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9052_पढ़ो_alarm(काष्ठा da9052_rtc *rtc, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t v[2][5];
	पूर्णांक idx = 1;
	पूर्णांक समयout = DA9052_GET_TIME_RETRIES;

	ret = da9052_group_पढ़ो(rtc->da9052, DA9052_ALARM_MI_REG, 5, &v[0][0]);
	अगर (ret) अणु
		rtc_err(rtc, "Failed to group read ALM: %d\n", ret);
		वापस ret;
	पूर्ण

	करो अणु
		ret = da9052_group_पढ़ो(rtc->da9052,
					DA9052_ALARM_MI_REG, 5, &v[idx][0]);
		अगर (ret) अणु
			rtc_err(rtc, "Failed to group read ALM: %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (स_भेद(&v[0][0], &v[1][0], 5) == 0) अणु
			rtc_पंचांग->पंचांग_year = (v[0][4] & DA9052_RTC_YEAR) + 100;
			rtc_पंचांग->पंचांग_mon  = (v[0][3] & DA9052_RTC_MONTH) - 1;
			rtc_पंचांग->पंचांग_mday = v[0][2] & DA9052_RTC_DAY;
			rtc_पंचांग->पंचांग_hour = v[0][1] & DA9052_RTC_HOUR;
			rtc_पंचांग->पंचांग_min  = v[0][0] & DA9052_RTC_MIN;
			rtc_पंचांग->पंचांग_sec = 0;

			ret = rtc_valid_पंचांग(rtc_पंचांग);
			वापस ret;
		पूर्ण

		idx = (1-idx);
		msleep(20);

	पूर्ण जबतक (समयout--);

	rtc_err(rtc, "Timed out reading alarm time\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक da9052_set_alarm(काष्ठा da9052_rtc *rtc, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा da9052 *da9052 = rtc->da9052;
	अचिन्हित दीर्घ alm_समय;
	पूर्णांक ret;
	uपूर्णांक8_t v[3];

	alm_समय = rtc_पंचांग_to_समय64(rtc_पंचांग);

	अगर (rtc_पंचांग->पंचांग_sec > 0) अणु
		alm_समय += 60 - rtc_पंचांग->पंचांग_sec;
		rtc_समय64_to_पंचांग(alm_समय, rtc_पंचांग);
	पूर्ण
	BUG_ON(rtc_पंचांग->पंचांग_sec); /* it will cause repeated irqs अगर not zero */

	rtc_पंचांग->पंचांग_year -= 100;
	rtc_पंचांग->पंचांग_mon += 1;

	ret = da9052_reg_update(da9052, DA9052_ALARM_MI_REG,
				DA9052_RTC_MIN, rtc_पंचांग->पंचांग_min);
	अगर (ret != 0) अणु
		rtc_err(rtc, "Failed to write ALRM MIN: %d\n", ret);
		वापस ret;
	पूर्ण

	v[0] = rtc_पंचांग->पंचांग_hour;
	v[1] = rtc_पंचांग->पंचांग_mday;
	v[2] = rtc_पंचांग->पंचांग_mon;

	ret = da9052_group_ग_लिखो(da9052, DA9052_ALARM_H_REG, 3, v);
	अगर (ret < 0)
		वापस ret;

	ret = da9052_reg_update(da9052, DA9052_ALARM_Y_REG,
				DA9052_RTC_YEAR, rtc_पंचांग->पंचांग_year);
	अगर (ret != 0)
		rtc_err(rtc, "Failed to write ALRM YEAR: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9052_rtc_get_alarm_status(काष्ठा da9052_rtc *rtc)
अणु
	पूर्णांक ret;

	ret = da9052_reg_पढ़ो(rtc->da9052, DA9052_ALARM_Y_REG);
	अगर (ret < 0) अणु
		rtc_err(rtc, "Failed to read ALM: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस !!(ret&DA9052_ALARM_Y_ALARM_ON);
पूर्ण

अटल पूर्णांक da9052_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा da9052_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक ret;
	uपूर्णांक8_t v[2][6];
	पूर्णांक idx = 1;
	पूर्णांक समयout = DA9052_GET_TIME_RETRIES;

	ret = da9052_group_पढ़ो(rtc->da9052, DA9052_COUNT_S_REG, 6, &v[0][0]);
	अगर (ret) अणु
		rtc_err(rtc, "Failed to read RTC time : %d\n", ret);
		वापस ret;
	पूर्ण

	करो अणु
		ret = da9052_group_पढ़ो(rtc->da9052,
					DA9052_COUNT_S_REG, 6, &v[idx][0]);
		अगर (ret) अणु
			rtc_err(rtc, "Failed to read RTC time : %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (स_भेद(&v[0][0], &v[1][0], 6) == 0) अणु
			rtc_पंचांग->पंचांग_year = (v[0][5] & DA9052_RTC_YEAR) + 100;
			rtc_पंचांग->पंचांग_mon  = (v[0][4] & DA9052_RTC_MONTH) - 1;
			rtc_पंचांग->पंचांग_mday = v[0][3] & DA9052_RTC_DAY;
			rtc_पंचांग->पंचांग_hour = v[0][2] & DA9052_RTC_HOUR;
			rtc_पंचांग->पंचांग_min  = v[0][1] & DA9052_RTC_MIN;
			rtc_पंचांग->पंचांग_sec  = v[0][0] & DA9052_RTC_SEC;

			वापस 0;
		पूर्ण

		idx = (1-idx);
		msleep(20);

	पूर्ण जबतक (समयout--);

	rtc_err(rtc, "Timed out reading time\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक da9052_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा da9052_rtc *rtc;
	uपूर्णांक8_t v[6];
	पूर्णांक ret;

	/* DA9052 only has 6 bits क्रम year - to represent 2000-2063 */
	अगर ((पंचांग->पंचांग_year < 100) || (पंचांग->पंचांग_year > 163))
		वापस -EINVAL;

	rtc = dev_get_drvdata(dev);

	v[0] = पंचांग->पंचांग_sec;
	v[1] = पंचांग->पंचांग_min;
	v[2] = पंचांग->पंचांग_hour;
	v[3] = पंचांग->पंचांग_mday;
	v[4] = पंचांग->पंचांग_mon + 1;
	v[5] = पंचांग->पंचांग_year - 100;

	ret = da9052_group_ग_लिखो(rtc->da9052, DA9052_COUNT_S_REG, 6, v);
	अगर (ret < 0)
		rtc_err(rtc, "failed to set RTC time: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक da9052_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	पूर्णांक ret;
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	काष्ठा da9052_rtc *rtc = dev_get_drvdata(dev);

	ret = da9052_पढ़ो_alarm(rtc, पंचांग);
	अगर (ret < 0) अणु
		rtc_err(rtc, "failed to read RTC alarm: %d\n", ret);
		वापस ret;
	पूर्ण

	alrm->enabled = da9052_rtc_get_alarm_status(rtc);
	वापस 0;
पूर्ण

अटल पूर्णांक da9052_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	पूर्णांक ret;
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	काष्ठा da9052_rtc *rtc = dev_get_drvdata(dev);

	/* DA9052 only has 6 bits क्रम year - to represent 2000-2063 */
	अगर ((पंचांग->पंचांग_year < 100) || (पंचांग->पंचांग_year > 163))
		वापस -EINVAL;

	ret = da9052_rtc_enable_alarm(rtc, 0);
	अगर (ret < 0)
		वापस ret;

	ret = da9052_set_alarm(rtc, पंचांग);
	अगर (ret < 0)
		वापस ret;

	ret = da9052_rtc_enable_alarm(rtc, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक da9052_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा da9052_rtc *rtc = dev_get_drvdata(dev);

	वापस da9052_rtc_enable_alarm(rtc, enabled);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops da9052_rtc_ops = अणु
	.पढ़ो_समय	= da9052_rtc_पढ़ो_समय,
	.set_समय	= da9052_rtc_set_समय,
	.पढ़ो_alarm	= da9052_rtc_पढ़ो_alarm,
	.set_alarm	= da9052_rtc_set_alarm,
	.alarm_irq_enable = da9052_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक da9052_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_rtc *rtc;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा da9052_rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->da9052 = dev_get_drvdata(pdev->dev.parent);
	platक्रमm_set_drvdata(pdev, rtc);

	ret = da9052_reg_ग_लिखो(rtc->da9052, DA9052_BBAT_CONT_REG, 0xFE);
	अगर (ret < 0) अणु
		rtc_err(rtc,
			"Failed to setup RTC battery charging: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = da9052_reg_update(rtc->da9052, DA9052_ALARM_Y_REG,
				DA9052_ALARM_Y_TICK_ON, 0);
	अगर (ret != 0)
		rtc_err(rtc, "Failed to disable TICKS: %d\n", ret);

	device_init_wakeup(&pdev->dev, true);
	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc))
		वापस PTR_ERR(rtc->rtc);

	rtc->rtc->ops = &da9052_rtc_ops;
	rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->rtc->range_max = RTC_TIMESTAMP_END_2063;

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (ret)
		वापस ret;

	ret = da9052_request_irq(rtc->da9052, DA9052_IRQ_ALARM, "ALM",
				da9052_rtc_irq, rtc);
	अगर (ret != 0) अणु
		rtc_err(rtc, "irq registration failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_rtc_driver = अणु
	.probe	= da9052_rtc_probe,
	.driver = अणु
		.name	= "da9052-rtc",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9052_rtc_driver);

MODULE_AUTHOR("Anthony Olech <Anthony.Olech@diasemi.com>");
MODULE_DESCRIPTION("RTC driver for Dialog DA9052 PMIC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-rtc");
