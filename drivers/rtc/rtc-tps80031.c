<शैली गुरु>
/*
 * rtc-tps80031.c -- TI TPS80031/TPS80032 RTC driver
 *
 * RTC driver क्रम TI TPS80031/TPS80032 Fully Integrated
 * Power Management with Power Path and Battery Charger
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/bcd.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/tps80031.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

#घोषणा ENABLE_ALARM_INT			0x08
#घोषणा ALARM_INT_STATUS			0x40

/**
 * Setting bit to 1 in STOP_RTC will run the RTC and
 * setting this bit to 0 will मुक्तze RTC.
 */
#घोषणा STOP_RTC				0x1

/* Power on reset Values of RTC रेजिस्टरs */
#घोषणा TPS80031_RTC_POR_YEAR			0
#घोषणा TPS80031_RTC_POR_MONTH			1
#घोषणा TPS80031_RTC_POR_DAY			1

/* Numbers of रेजिस्टरs क्रम समय and alarms */
#घोषणा TPS80031_RTC_TIME_NUM_REGS		7
#घोषणा TPS80031_RTC_ALARM_NUM_REGS		6

/**
 * PMU RTC have only 2 nibbles to store year inक्रमmation, so using an
 * offset of 100 to set the base year as 2000 क्रम our driver.
 */
#घोषणा RTC_YEAR_OFFSET 100

काष्ठा tps80031_rtc अणु
	काष्ठा rtc_device	*rtc;
	पूर्णांक			irq;
पूर्ण;

अटल पूर्णांक tps80031_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	u8 buff[TPS80031_RTC_TIME_NUM_REGS];
	पूर्णांक ret;

	ret = tps80031_पढ़ोs(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_SECONDS_REG, TPS80031_RTC_TIME_NUM_REGS, buff);
	अगर (ret < 0) अणु
		dev_err(dev, "reading RTC_SECONDS_REG failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(buff[0]);
	पंचांग->पंचांग_min = bcd2bin(buff[1]);
	पंचांग->पंचांग_hour = bcd2bin(buff[2]);
	पंचांग->पंचांग_mday = bcd2bin(buff[3]);
	पंचांग->पंचांग_mon = bcd2bin(buff[4]) - 1;
	पंचांग->पंचांग_year = bcd2bin(buff[5]) + RTC_YEAR_OFFSET;
	पंचांग->पंचांग_wday = bcd2bin(buff[6]);
	वापस 0;
पूर्ण

अटल पूर्णांक tps80031_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	u8 buff[7];
	पूर्णांक ret;

	buff[0] = bin2bcd(पंचांग->पंचांग_sec);
	buff[1] = bin2bcd(पंचांग->पंचांग_min);
	buff[2] = bin2bcd(पंचांग->पंचांग_hour);
	buff[3] = bin2bcd(पंचांग->पंचांग_mday);
	buff[4] = bin2bcd(पंचांग->पंचांग_mon + 1);
	buff[5] = bin2bcd(पंचांग->पंचांग_year % RTC_YEAR_OFFSET);
	buff[6] = bin2bcd(पंचांग->पंचांग_wday);

	/* Stop RTC जबतक updating the RTC समय रेजिस्टरs */
	ret = tps80031_clr_bits(dev->parent, TPS80031_SLAVE_ID1,
				TPS80031_RTC_CTRL_REG, STOP_RTC);
	अगर (ret < 0) अणु
		dev_err(dev->parent, "Stop RTC failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tps80031_ग_लिखोs(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_SECONDS_REG,
			TPS80031_RTC_TIME_NUM_REGS, buff);
	अगर (ret < 0) अणु
		dev_err(dev, "writing RTC_SECONDS_REG failed, err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tps80031_set_bits(dev->parent, TPS80031_SLAVE_ID1,
				TPS80031_RTC_CTRL_REG, STOP_RTC);
	अगर (ret < 0)
		dev_err(dev->parent, "Start RTC failed, err = %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tps80031_rtc_alarm_irq_enable(काष्ठा device *dev,
					 अचिन्हित पूर्णांक enable)
अणु
	पूर्णांक ret;

	अगर (enable)
		ret = tps80031_set_bits(dev->parent, TPS80031_SLAVE_ID1,
				TPS80031_RTC_INTERRUPTS_REG, ENABLE_ALARM_INT);
	अन्यथा
		ret = tps80031_clr_bits(dev->parent, TPS80031_SLAVE_ID1,
				TPS80031_RTC_INTERRUPTS_REG, ENABLE_ALARM_INT);
	अगर (ret < 0) अणु
		dev_err(dev, "Update on RTC_INT failed, err = %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps80031_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	u8 buff[TPS80031_RTC_ALARM_NUM_REGS];
	पूर्णांक ret;

	buff[0] = bin2bcd(alrm->समय.पंचांग_sec);
	buff[1] = bin2bcd(alrm->समय.पंचांग_min);
	buff[2] = bin2bcd(alrm->समय.पंचांग_hour);
	buff[3] = bin2bcd(alrm->समय.पंचांग_mday);
	buff[4] = bin2bcd(alrm->समय.पंचांग_mon + 1);
	buff[5] = bin2bcd(alrm->समय.पंचांग_year % RTC_YEAR_OFFSET);
	ret = tps80031_ग_लिखोs(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_ALARM_SECONDS_REG,
			TPS80031_RTC_ALARM_NUM_REGS, buff);
	अगर (ret < 0) अणु
		dev_err(dev, "Writing RTC_ALARM failed, err %d\n", ret);
		वापस ret;
	पूर्ण
	वापस tps80031_rtc_alarm_irq_enable(dev, alrm->enabled);
पूर्ण

अटल पूर्णांक tps80031_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	u8 buff[6];
	पूर्णांक ret;

	ret = tps80031_पढ़ोs(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_ALARM_SECONDS_REG,
			TPS80031_RTC_ALARM_NUM_REGS, buff);
	अगर (ret < 0) अणु
		dev_err(dev->parent,
			"reading RTC_ALARM failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	alrm->समय.पंचांग_sec = bcd2bin(buff[0]);
	alrm->समय.पंचांग_min = bcd2bin(buff[1]);
	alrm->समय.पंचांग_hour = bcd2bin(buff[2]);
	alrm->समय.पंचांग_mday = bcd2bin(buff[3]);
	alrm->समय.पंचांग_mon = bcd2bin(buff[4]) - 1;
	alrm->समय.पंचांग_year = bcd2bin(buff[5]) + RTC_YEAR_OFFSET;
	वापस 0;
पूर्ण

अटल पूर्णांक clear_alarm_पूर्णांक_status(काष्ठा device *dev, काष्ठा tps80031_rtc *rtc)
अणु
	पूर्णांक ret;
	u8 buf;

	/**
	 * As per datasheet, A dummy पढ़ो of this  RTC_STATUS_REG रेजिस्टर
	 * is necessary beक्रमe each I2C पढ़ो in order to update the status
	 * रेजिस्टर value.
	 */
	ret = tps80031_पढ़ो(dev->parent, TPS80031_SLAVE_ID1,
				TPS80031_RTC_STATUS_REG, &buf);
	अगर (ret < 0) अणु
		dev_err(dev, "reading RTC_STATUS failed. err = %d\n", ret);
		वापस ret;
	पूर्ण

	/* clear Alarm status bits.*/
	ret = tps80031_set_bits(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_RTC_STATUS_REG, ALARM_INT_STATUS);
	अगर (ret < 0) अणु
		dev_err(dev, "clear Alarm INT failed, err = %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t tps80031_rtc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा tps80031_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clear_alarm_पूर्णांक_status(dev, rtc);
	अगर (ret < 0)
		वापस ret;

	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops tps80031_rtc_ops = अणु
	.पढ़ो_समय = tps80031_rtc_पढ़ो_समय,
	.set_समय = tps80031_rtc_set_समय,
	.set_alarm = tps80031_rtc_set_alarm,
	.पढ़ो_alarm = tps80031_rtc_पढ़ो_alarm,
	.alarm_irq_enable = tps80031_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक tps80031_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps80031_rtc *rtc;
	काष्ठा rtc_समय पंचांग;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->irq = platक्रमm_get_irq(pdev, 0);
	platक्रमm_set_drvdata(pdev, rtc);

	/* Start RTC */
	ret = tps80031_set_bits(pdev->dev.parent, TPS80031_SLAVE_ID1,
			TPS80031_RTC_CTRL_REG, STOP_RTC);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to start RTC. err = %d\n", ret);
		वापस ret;
	पूर्ण

	/* If RTC have POR values, set समय 01:01:2000 */
	tps80031_rtc_पढ़ो_समय(&pdev->dev, &पंचांग);
	अगर ((पंचांग.पंचांग_year == RTC_YEAR_OFFSET + TPS80031_RTC_POR_YEAR) &&
		(पंचांग.पंचांग_mon == (TPS80031_RTC_POR_MONTH - 1)) &&
		(पंचांग.पंचांग_mday == TPS80031_RTC_POR_DAY)) अणु
		पंचांग.पंचांग_year = 2000;
		पंचांग.पंचांग_mday = 1;
		पंचांग.पंचांग_mon = 1;
		ret = tps80031_rtc_set_समय(&pdev->dev, &पंचांग);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"RTC set time failed, err = %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Clear alarm पूर्णांकretupt status अगर it is there */
	ret = clear_alarm_पूर्णांक_status(&pdev->dev, rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Clear alarm int failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
			       &tps80031_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc->rtc)) अणु
		ret = PTR_ERR(rtc->rtc);
		dev_err(&pdev->dev, "RTC registration failed, err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq, शून्य,
			tps80031_rtc_irq,
			IRQF_ONESHOT,
			dev_name(&pdev->dev), rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request IRQ:%d failed, err = %d\n",
			 rtc->irq, ret);
		वापस ret;
	पूर्ण
	device_set_wakeup_capable(&pdev->dev, 1);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tps80031_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tps80031_rtc *rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(rtc->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक tps80031_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा tps80031_rtc *rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(rtc->irq);
	वापस 0;
पूर्ण;
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tps80031_pm_ops, tps80031_rtc_suspend,
			tps80031_rtc_resume);

अटल काष्ठा platक्रमm_driver tps80031_rtc_driver = अणु
	.driver	= अणु
		.name	= "tps80031-rtc",
		.pm	= &tps80031_pm_ops,
	पूर्ण,
	.probe	= tps80031_rtc_probe,
पूर्ण;

module_platक्रमm_driver(tps80031_rtc_driver);

MODULE_ALIAS("platform:tps80031-rtc");
MODULE_DESCRIPTION("TI TPS80031/TPS80032 RTC driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
