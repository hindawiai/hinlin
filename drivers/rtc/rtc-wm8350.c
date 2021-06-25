<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Real Time Clock driver क्रम Wolfson Microelectronics WM8350
 *
 *	Copyright (C) 2007, 2008 Wolfson Microelectronics PLC.
 *
 *  Author: Liam Girdwood
 *          linux@wolfsonmicro.com
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/completion.h>
#समावेश <linux/mfd/wm8350/rtc.h>
#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा WM8350_SET_ALM_RETRIES	5
#घोषणा WM8350_SET_TIME_RETRIES	5
#घोषणा WM8350_GET_TIME_RETRIES	5

/*
 * Read current समय and date in RTC
 */
अटल पूर्णांक wm8350_rtc_पढ़ोसमय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	u16 समय1[4], समय2[4];
	पूर्णांक retries = WM8350_GET_TIME_RETRIES, ret;

	/*
	 * Read the समय twice and compare.
	 * If समय1 == समय2, then समय is valid अन्यथा retry.
	 */
	करो अणु
		ret = wm8350_block_पढ़ो(wm8350, WM8350_RTC_SECONDS_MINUTES,
					4, समय1);
		अगर (ret < 0)
			वापस ret;
		ret = wm8350_block_पढ़ो(wm8350, WM8350_RTC_SECONDS_MINUTES,
					4, समय2);
		अगर (ret < 0)
			वापस ret;

		अगर (स_भेद(समय1, समय2, माप(समय1)) == 0) अणु
			पंचांग->पंचांग_sec = समय1[0] & WM8350_RTC_SECS_MASK;

			पंचांग->पंचांग_min = (समय1[0] & WM8350_RTC_MINS_MASK)
			    >> WM8350_RTC_MINS_SHIFT;

			पंचांग->पंचांग_hour = समय1[1] & WM8350_RTC_HRS_MASK;

			पंचांग->पंचांग_wday = ((समय1[1] >> WM8350_RTC_DAY_SHIFT)
				       & 0x7) - 1;

			पंचांग->पंचांग_mon = ((समय1[2] & WM8350_RTC_MTH_MASK)
				      >> WM8350_RTC_MTH_SHIFT) - 1;

			पंचांग->पंचांग_mday = (समय1[2] & WM8350_RTC_DATE_MASK);

			पंचांग->पंचांग_year = ((समय1[3] & WM8350_RTC_YHUNDREDS_MASK)
				       >> WM8350_RTC_YHUNDREDS_SHIFT) * 100;
			पंचांग->पंचांग_year += समय1[3] & WM8350_RTC_YUNITS_MASK;

			पंचांग->पंचांग_yday = rtc_year_days(पंचांग->पंचांग_mday, पंचांग->पंचांग_mon,
						    पंचांग->पंचांग_year);
			पंचांग->पंचांग_year -= 1900;

			dev_dbg(dev, "Read (%d left): %04x %04x %04x %04x\n",
				retries,
				समय1[0], समय1[1], समय1[2], समय1[3]);

			वापस 0;
		पूर्ण
	पूर्ण जबतक (retries--);

	dev_err(dev, "timed out reading RTC time\n");
	वापस -EIO;
पूर्ण

/*
 * Set current समय and date in RTC
 */
अटल पूर्णांक wm8350_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	u16 समय[4];
	u16 rtc_ctrl;
	पूर्णांक ret, retries = WM8350_SET_TIME_RETRIES;

	समय[0] = पंचांग->पंचांग_sec;
	समय[0] |= पंचांग->पंचांग_min << WM8350_RTC_MINS_SHIFT;
	समय[1] = पंचांग->पंचांग_hour;
	समय[1] |= (पंचांग->पंचांग_wday + 1) << WM8350_RTC_DAY_SHIFT;
	समय[2] = पंचांग->पंचांग_mday;
	समय[2] |= (पंचांग->पंचांग_mon + 1) << WM8350_RTC_MTH_SHIFT;
	समय[3] = ((पंचांग->पंचांग_year + 1900) / 100) << WM8350_RTC_YHUNDREDS_SHIFT;
	समय[3] |= (पंचांग->पंचांग_year + 1900) % 100;

	dev_dbg(dev, "Setting: %04x %04x %04x %04x\n",
		समय[0], समय[1], समय[2], समय[3]);

	/* Set RTC_SET to stop the घड़ी */
	ret = wm8350_set_bits(wm8350, WM8350_RTC_TIME_CONTROL, WM8350_RTC_SET);
	अगर (ret < 0)
		वापस ret;

	/* Wait until confirmation of stopping */
	करो अणु
		rtc_ctrl = wm8350_reg_पढ़ो(wm8350, WM8350_RTC_TIME_CONTROL);
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(1));
	पूर्ण जबतक (--retries && !(rtc_ctrl & WM8350_RTC_STS));

	अगर (!retries) अणु
		dev_err(dev, "timed out on set confirmation\n");
		वापस -EIO;
	पूर्ण

	/* Write समय to RTC */
	ret = wm8350_block_ग_लिखो(wm8350, WM8350_RTC_SECONDS_MINUTES, 4, समय);
	अगर (ret < 0)
		वापस ret;

	/* Clear RTC_SET to start the घड़ी */
	ret = wm8350_clear_bits(wm8350, WM8350_RTC_TIME_CONTROL,
				WM8350_RTC_SET);
	वापस ret;
पूर्ण

/*
 * Read alarm समय and date in RTC
 */
अटल पूर्णांक wm8350_rtc_पढ़ोalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	u16 समय[4];
	पूर्णांक ret;

	ret = wm8350_block_पढ़ो(wm8350, WM8350_ALARM_SECONDS_MINUTES, 4, समय);
	अगर (ret < 0)
		वापस ret;

	पंचांग->पंचांग_sec = समय[0] & WM8350_RTC_ALMSECS_MASK;
	अगर (पंचांग->पंचांग_sec == WM8350_RTC_ALMSECS_MASK)
		पंचांग->पंचांग_sec = -1;

	पंचांग->पंचांग_min = समय[0] & WM8350_RTC_ALMMINS_MASK;
	अगर (पंचांग->पंचांग_min == WM8350_RTC_ALMMINS_MASK)
		पंचांग->पंचांग_min = -1;
	अन्यथा
		पंचांग->पंचांग_min >>= WM8350_RTC_ALMMINS_SHIFT;

	पंचांग->पंचांग_hour = समय[1] & WM8350_RTC_ALMHRS_MASK;
	अगर (पंचांग->पंचांग_hour == WM8350_RTC_ALMHRS_MASK)
		पंचांग->पंचांग_hour = -1;

	पंचांग->पंचांग_wday = ((समय[1] >> WM8350_RTC_ALMDAY_SHIFT) & 0x7) - 1;
	अगर (पंचांग->पंचांग_wday > 7)
		पंचांग->पंचांग_wday = -1;

	पंचांग->पंचांग_mon = समय[2] & WM8350_RTC_ALMMTH_MASK;
	अगर (पंचांग->पंचांग_mon == WM8350_RTC_ALMMTH_MASK)
		पंचांग->पंचांग_mon = -1;
	अन्यथा
		पंचांग->पंचांग_mon = (पंचांग->पंचांग_mon >> WM8350_RTC_ALMMTH_SHIFT) - 1;

	पंचांग->पंचांग_mday = (समय[2] & WM8350_RTC_ALMDATE_MASK);
	अगर (पंचांग->पंचांग_mday == WM8350_RTC_ALMDATE_MASK)
		पंचांग->पंचांग_mday = -1;

	पंचांग->पंचांग_year = -1;

	alrm->enabled = !(समय[3] & WM8350_RTC_ALMSTS);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_rtc_stop_alarm(काष्ठा wm8350 *wm8350)
अणु
	पूर्णांक retries = WM8350_SET_ALM_RETRIES;
	u16 rtc_ctrl;
	पूर्णांक ret;

	/* Set RTC_SET to stop the घड़ी */
	ret = wm8350_set_bits(wm8350, WM8350_RTC_TIME_CONTROL,
			      WM8350_RTC_ALMSET);
	अगर (ret < 0)
		वापस ret;

	/* Wait until confirmation of stopping */
	करो अणु
		rtc_ctrl = wm8350_reg_पढ़ो(wm8350, WM8350_RTC_TIME_CONTROL);
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(1));
	पूर्ण जबतक (retries-- && !(rtc_ctrl & WM8350_RTC_ALMSTS));

	अगर (!(rtc_ctrl & WM8350_RTC_ALMSTS))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_rtc_start_alarm(काष्ठा wm8350 *wm8350)
अणु
	पूर्णांक ret;
	पूर्णांक retries = WM8350_SET_ALM_RETRIES;
	u16 rtc_ctrl;

	ret = wm8350_clear_bits(wm8350, WM8350_RTC_TIME_CONTROL,
				WM8350_RTC_ALMSET);
	अगर (ret < 0)
		वापस ret;

	/* Wait until confirmation */
	करो अणु
		rtc_ctrl = wm8350_reg_पढ़ो(wm8350, WM8350_RTC_TIME_CONTROL);
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(1));
	पूर्ण जबतक (retries-- && rtc_ctrl & WM8350_RTC_ALMSTS);

	अगर (rtc_ctrl & WM8350_RTC_ALMSTS)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_rtc_alarm_irq_enable(काष्ठा device *dev,
				       अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);

	अगर (enabled)
		वापस wm8350_rtc_start_alarm(wm8350);
	अन्यथा
		वापस wm8350_rtc_stop_alarm(wm8350);
पूर्ण

अटल पूर्णांक wm8350_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	u16 समय[3];
	पूर्णांक ret;

	स_रखो(समय, 0, माप(समय));

	अगर (पंचांग->पंचांग_sec != -1)
		समय[0] |= पंचांग->पंचांग_sec;
	अन्यथा
		समय[0] |= WM8350_RTC_ALMSECS_MASK;

	अगर (पंचांग->पंचांग_min != -1)
		समय[0] |= पंचांग->पंचांग_min << WM8350_RTC_ALMMINS_SHIFT;
	अन्यथा
		समय[0] |= WM8350_RTC_ALMMINS_MASK;

	अगर (पंचांग->पंचांग_hour != -1)
		समय[1] |= पंचांग->पंचांग_hour;
	अन्यथा
		समय[1] |= WM8350_RTC_ALMHRS_MASK;

	अगर (पंचांग->पंचांग_wday != -1)
		समय[1] |= (पंचांग->पंचांग_wday + 1) << WM8350_RTC_ALMDAY_SHIFT;
	अन्यथा
		समय[1] |= WM8350_RTC_ALMDAY_MASK;

	अगर (पंचांग->पंचांग_mday != -1)
		समय[2] |= पंचांग->पंचांग_mday;
	अन्यथा
		समय[2] |= WM8350_RTC_ALMDATE_MASK;

	अगर (पंचांग->पंचांग_mon != -1)
		समय[2] |= (पंचांग->पंचांग_mon + 1) << WM8350_RTC_ALMMTH_SHIFT;
	अन्यथा
		समय[2] |= WM8350_RTC_ALMMTH_MASK;

	ret = wm8350_rtc_stop_alarm(wm8350);
	अगर (ret < 0)
		वापस ret;

	/* Write समय to RTC */
	ret = wm8350_block_ग_लिखो(wm8350, WM8350_ALARM_SECONDS_MINUTES,
				 3, समय);
	अगर (ret < 0)
		वापस ret;

	अगर (alrm->enabled)
		ret = wm8350_rtc_start_alarm(wm8350);

	वापस ret;
पूर्ण

अटल irqवापस_t wm8350_rtc_alarm_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8350 *wm8350 = data;
	काष्ठा rtc_device *rtc = wm8350->rtc.rtc;
	पूर्णांक ret;

	rtc_update_irq(rtc, 1, RTC_IRQF | RTC_AF);

	/* Make it one shot */
	ret = wm8350_set_bits(wm8350, WM8350_RTC_TIME_CONTROL,
			      WM8350_RTC_ALMSET);
	अगर (ret != 0) अणु
		dev_err(&(wm8350->rtc.pdev->dev),
			"Failed to disable alarm: %d\n", ret);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wm8350_rtc_update_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8350 *wm8350 = data;
	काष्ठा rtc_device *rtc = wm8350->rtc.rtc;

	rtc_update_irq(rtc, 1, RTC_IRQF | RTC_UF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops wm8350_rtc_ops = अणु
	.पढ़ो_समय = wm8350_rtc_पढ़ोसमय,
	.set_समय = wm8350_rtc_समय_रखो,
	.पढ़ो_alarm = wm8350_rtc_पढ़ोalarm,
	.set_alarm = wm8350_rtc_setalarm,
	.alarm_irq_enable = wm8350_rtc_alarm_irq_enable,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक wm8350_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	u16 reg;

	reg = wm8350_reg_पढ़ो(wm8350, WM8350_RTC_TIME_CONTROL);

	अगर (device_may_wakeup(&wm8350->rtc.pdev->dev) &&
	    reg & WM8350_RTC_ALMSTS) अणु
		ret = wm8350_rtc_stop_alarm(wm8350);
		अगर (ret != 0)
			dev_err(dev, "Failed to stop RTC alarm: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (wm8350->rtc.alarm_enabled) अणु
		ret = wm8350_rtc_start_alarm(wm8350);
		अगर (ret != 0)
			dev_err(dev, "Failed to restart RTC alarm: %d\n", ret);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक wm8350_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = platक्रमm_get_drvdata(pdev);
	काष्ठा wm8350_rtc *wm_rtc = &wm8350->rtc;
	पूर्णांक ret = 0;
	u16 समयctl, घातer5;

	समयctl = wm8350_reg_पढ़ो(wm8350, WM8350_RTC_TIME_CONTROL);
	अगर (समयctl & WM8350_RTC_BCD) अणु
		dev_err(&pdev->dev, "RTC BCD mode not supported\n");
		वापस -EINVAL;
	पूर्ण
	अगर (समयctl & WM8350_RTC_12HR) अणु
		dev_err(&pdev->dev, "RTC 12 hour mode not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* enable the RTC अगर it's not alपढ़ोy enabled */
	घातer5 = wm8350_reg_पढ़ो(wm8350, WM8350_POWER_MGMT_5);
	अगर (!(घातer5 &  WM8350_RTC_TICK_ENA)) अणु
		dev_info(wm8350->dev, "Starting RTC\n");

		wm8350_reg_unlock(wm8350);

		ret = wm8350_set_bits(wm8350, WM8350_POWER_MGMT_5,
				      WM8350_RTC_TICK_ENA);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to enable RTC: %d\n", ret);
			वापस ret;
		पूर्ण

		wm8350_reg_lock(wm8350);
	पूर्ण

	अगर (समयctl & WM8350_RTC_STS) अणु
		पूर्णांक retries;

		ret = wm8350_clear_bits(wm8350, WM8350_RTC_TIME_CONTROL,
					WM8350_RTC_SET);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to start: %d\n", ret);
			वापस ret;
		पूर्ण

		retries = WM8350_SET_TIME_RETRIES;
		करो अणु
			समयctl = wm8350_reg_पढ़ो(wm8350,
						  WM8350_RTC_TIME_CONTROL);
		पूर्ण जबतक (समयctl & WM8350_RTC_STS && --retries);

		अगर (retries == 0) अणु
			dev_err(&pdev->dev, "failed to start: timeout\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);

	wm_rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "wm8350",
					&wm8350_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(wm_rtc->rtc)) अणु
		ret = PTR_ERR(wm_rtc->rtc);
		dev_err(&pdev->dev, "failed to register RTC: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_RTC_SEC,
			    wm8350_rtc_update_handler, 0,
			    "RTC Seconds", wm8350);
	wm8350_mask_irq(wm8350, WM8350_IRQ_RTC_SEC);

	wm8350_रेजिस्टर_irq(wm8350, WM8350_IRQ_RTC_ALM,
			    wm8350_rtc_alarm_handler, 0,
			    "RTC Alarm", wm8350);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = platक्रमm_get_drvdata(pdev);

	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_RTC_SEC, wm8350);
	wm8350_मुक्त_irq(wm8350, WM8350_IRQ_RTC_ALM, wm8350);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(wm8350_rtc_pm_ops, wm8350_rtc_suspend,
			wm8350_rtc_resume);

अटल काष्ठा platक्रमm_driver wm8350_rtc_driver = अणु
	.probe = wm8350_rtc_probe,
	.हटाओ = wm8350_rtc_हटाओ,
	.driver = अणु
		.name = "wm8350-rtc",
		.pm = &wm8350_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm8350_rtc_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("RTC driver for the WM8350");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-rtc");
