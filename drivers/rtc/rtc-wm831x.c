<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Real Time Clock driver क्रम Wolfson Microelectronics WM831x
 *
 *	Copyright (C) 2009 Wolfson Microelectronics PLC.
 *
 *  Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/bcd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/completion.h>
#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अक्रमom.h>

/*
 * R16416 (0x4020) - RTC Write Counter
 */
#घोषणा WM831X_RTC_WR_CNT_MASK                  0xFFFF  /* RTC_WR_CNT - [15:0] */
#घोषणा WM831X_RTC_WR_CNT_SHIFT                      0  /* RTC_WR_CNT - [15:0] */
#घोषणा WM831X_RTC_WR_CNT_WIDTH                     16  /* RTC_WR_CNT - [15:0] */

/*
 * R16417 (0x4021) - RTC Time 1
 */
#घोषणा WM831X_RTC_TIME_MASK                    0xFFFF  /* RTC_TIME - [15:0] */
#घोषणा WM831X_RTC_TIME_SHIFT                        0  /* RTC_TIME - [15:0] */
#घोषणा WM831X_RTC_TIME_WIDTH                       16  /* RTC_TIME - [15:0] */

/*
 * R16418 (0x4022) - RTC Time 2
 */
#घोषणा WM831X_RTC_TIME_MASK                    0xFFFF  /* RTC_TIME - [15:0] */
#घोषणा WM831X_RTC_TIME_SHIFT                        0  /* RTC_TIME - [15:0] */
#घोषणा WM831X_RTC_TIME_WIDTH                       16  /* RTC_TIME - [15:0] */

/*
 * R16419 (0x4023) - RTC Alarm 1
 */
#घोषणा WM831X_RTC_ALM_MASK                     0xFFFF  /* RTC_ALM - [15:0] */
#घोषणा WM831X_RTC_ALM_SHIFT                         0  /* RTC_ALM - [15:0] */
#घोषणा WM831X_RTC_ALM_WIDTH                        16  /* RTC_ALM - [15:0] */

/*
 * R16420 (0x4024) - RTC Alarm 2
 */
#घोषणा WM831X_RTC_ALM_MASK                     0xFFFF  /* RTC_ALM - [15:0] */
#घोषणा WM831X_RTC_ALM_SHIFT                         0  /* RTC_ALM - [15:0] */
#घोषणा WM831X_RTC_ALM_WIDTH                        16  /* RTC_ALM - [15:0] */

/*
 * R16421 (0x4025) - RTC Control
 */
#घोषणा WM831X_RTC_VALID                        0x8000  /* RTC_VALID */
#घोषणा WM831X_RTC_VALID_MASK                   0x8000  /* RTC_VALID */
#घोषणा WM831X_RTC_VALID_SHIFT                      15  /* RTC_VALID */
#घोषणा WM831X_RTC_VALID_WIDTH                       1  /* RTC_VALID */
#घोषणा WM831X_RTC_SYNC_BUSY                    0x4000  /* RTC_SYNC_BUSY */
#घोषणा WM831X_RTC_SYNC_BUSY_MASK               0x4000  /* RTC_SYNC_BUSY */
#घोषणा WM831X_RTC_SYNC_BUSY_SHIFT                  14  /* RTC_SYNC_BUSY */
#घोषणा WM831X_RTC_SYNC_BUSY_WIDTH                   1  /* RTC_SYNC_BUSY */
#घोषणा WM831X_RTC_ALM_ENA                      0x0400  /* RTC_ALM_ENA */
#घोषणा WM831X_RTC_ALM_ENA_MASK                 0x0400  /* RTC_ALM_ENA */
#घोषणा WM831X_RTC_ALM_ENA_SHIFT                    10  /* RTC_ALM_ENA */
#घोषणा WM831X_RTC_ALM_ENA_WIDTH                     1  /* RTC_ALM_ENA */
#घोषणा WM831X_RTC_PINT_FREQ_MASK               0x0070  /* RTC_PINT_FREQ - [6:4] */
#घोषणा WM831X_RTC_PINT_FREQ_SHIFT                   4  /* RTC_PINT_FREQ - [6:4] */
#घोषणा WM831X_RTC_PINT_FREQ_WIDTH                   3  /* RTC_PINT_FREQ - [6:4] */

/*
 * R16422 (0x4026) - RTC Trim
 */
#घोषणा WM831X_RTC_TRIM_MASK                    0x03FF  /* RTC_TRIM - [9:0] */
#घोषणा WM831X_RTC_TRIM_SHIFT                        0  /* RTC_TRIM - [9:0] */
#घोषणा WM831X_RTC_TRIM_WIDTH                       10  /* RTC_TRIM - [9:0] */

#घोषणा WM831X_SET_TIME_RETRIES	5
#घोषणा WM831X_GET_TIME_RETRIES	5

काष्ठा wm831x_rtc अणु
	काष्ठा wm831x *wm831x;
	काष्ठा rtc_device *rtc;
	अचिन्हित पूर्णांक alarm_enabled:1;
पूर्ण;

अटल व्योम wm831x_rtc_add_अक्रमomness(काष्ठा wm831x *wm831x)
अणु
	पूर्णांक ret;
	u16 reg;

	/*
	 * The ग_लिखो counter contains a pseuकरो-अक्रमom number which is
	 * regenerated every समय we set the RTC so it should be a
	 * useful per-प्रणाली source of entropy.
	 */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_RTC_WRITE_COUNTER);
	अगर (ret >= 0) अणु
		reg = ret;
		add_device_अक्रमomness(&reg, माप(reg));
	पूर्ण अन्यथा अणु
		dev_warn(wm831x->dev, "Failed to read RTC write counter: %d\n",
			 ret);
	पूर्ण
पूर्ण

/*
 * Read current समय and date in RTC
 */
अटल पूर्णांक wm831x_rtc_पढ़ोसमय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	काष्ठा wm831x *wm831x = wm831x_rtc->wm831x;
	u16 समय1[2], समय2[2];
	पूर्णांक ret;
	पूर्णांक count = 0;

	/* Has the RTC been programmed? */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_RTC_CONTROL);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read RTC control: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (!(ret & WM831X_RTC_VALID)) अणु
		dev_dbg(dev, "RTC not yet configured\n");
		वापस -EINVAL;
	पूर्ण

	/* Read twice to make sure we करोn't पढ़ो a corrupt, partially
	 * incremented, value.
	 */
	करो अणु
		ret = wm831x_bulk_पढ़ो(wm831x, WM831X_RTC_TIME_1,
				       2, समय1);
		अगर (ret != 0)
			जारी;

		ret = wm831x_bulk_पढ़ो(wm831x, WM831X_RTC_TIME_1,
				       2, समय2);
		अगर (ret != 0)
			जारी;

		अगर (स_भेद(समय1, समय2, माप(समय1)) == 0) अणु
			u32 समय = (समय1[0] << 16) | समय1[1];

			rtc_समय64_to_पंचांग(समय, पंचांग);
			वापस 0;
		पूर्ण

	पूर्ण जबतक (++count < WM831X_GET_TIME_RETRIES);

	dev_err(dev, "Timed out reading current time\n");

	वापस -EIO;
पूर्ण

/*
 * Set current समय and date in RTC
 */
अटल पूर्णांक wm831x_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	काष्ठा wm831x *wm831x = wm831x_rtc->wm831x;
	काष्ठा rtc_समय new_पंचांग;
	अचिन्हित दीर्घ समय, new_समय;
	पूर्णांक ret;
	पूर्णांक count = 0;

	समय = rtc_पंचांग_to_समय64(पंचांग);

	ret = wm831x_reg_ग_लिखो(wm831x, WM831X_RTC_TIME_1,
			       (समय >> 16) & 0xffff);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to write TIME_1: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm831x_reg_ग_लिखो(wm831x, WM831X_RTC_TIME_2, समय & 0xffff);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to write TIME_2: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Wait क्रम the update to complete - should happen first समय
	 * round but be conservative.
	 */
	करो अणु
		msleep(1);

		ret = wm831x_reg_पढ़ो(wm831x, WM831X_RTC_CONTROL);
		अगर (ret < 0)
			ret = WM831X_RTC_SYNC_BUSY;
	पूर्ण जबतक (!(ret & WM831X_RTC_SYNC_BUSY) &&
		 ++count < WM831X_SET_TIME_RETRIES);

	अगर (ret & WM831X_RTC_SYNC_BUSY) अणु
		dev_err(dev, "Timed out writing RTC update\n");
		वापस -EIO;
	पूर्ण

	/* Check that the update was accepted; security features may
	 * have caused the update to be ignored.
	 */
	ret = wm831x_rtc_पढ़ोसमय(dev, &new_पंचांग);
	अगर (ret < 0)
		वापस ret;

	new_समय = rtc_पंचांग_to_समय64(&new_पंचांग);

	/* Allow a second of change in हाल of tick */
	अगर (new_समय - समय > 1) अणु
		dev_err(dev, "RTC update not permitted by hardware\n");
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Read alarm समय and date in RTC
 */
अटल पूर्णांक wm831x_rtc_पढ़ोalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	पूर्णांक ret;
	u16 data[2];
	u32 समय;

	ret = wm831x_bulk_पढ़ो(wm831x_rtc->wm831x, WM831X_RTC_ALARM_1,
			       2, data);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to read alarm time: %d\n", ret);
		वापस ret;
	पूर्ण

	समय = (data[0] << 16) | data[1];

	rtc_समय64_to_पंचांग(समय, &alrm->समय);

	ret = wm831x_reg_पढ़ो(wm831x_rtc->wm831x, WM831X_RTC_CONTROL);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read RTC control: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ret & WM831X_RTC_ALM_ENA)
		alrm->enabled = 1;
	अन्यथा
		alrm->enabled = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_rtc_stop_alarm(काष्ठा wm831x_rtc *wm831x_rtc)
अणु
	wm831x_rtc->alarm_enabled = 0;

	वापस wm831x_set_bits(wm831x_rtc->wm831x, WM831X_RTC_CONTROL,
			       WM831X_RTC_ALM_ENA, 0);
पूर्ण

अटल पूर्णांक wm831x_rtc_start_alarm(काष्ठा wm831x_rtc *wm831x_rtc)
अणु
	wm831x_rtc->alarm_enabled = 1;

	वापस wm831x_set_bits(wm831x_rtc->wm831x, WM831X_RTC_CONTROL,
			       WM831X_RTC_ALM_ENA, WM831X_RTC_ALM_ENA);
पूर्ण

अटल पूर्णांक wm831x_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	काष्ठा wm831x *wm831x = wm831x_rtc->wm831x;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय;

	समय = rtc_पंचांग_to_समय64(&alrm->समय);

	ret = wm831x_rtc_stop_alarm(wm831x_rtc);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to stop alarm: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm831x_reg_ग_लिखो(wm831x, WM831X_RTC_ALARM_1,
			       (समय >> 16) & 0xffff);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to write ALARM_1: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm831x_reg_ग_लिखो(wm831x, WM831X_RTC_ALARM_2, समय & 0xffff);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to write ALARM_2: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (alrm->enabled) अणु
		ret = wm831x_rtc_start_alarm(wm831x_rtc);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to start alarm: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_rtc_alarm_irq_enable(काष्ठा device *dev,
				       अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);

	अगर (enabled)
		वापस wm831x_rtc_start_alarm(wm831x_rtc);
	अन्यथा
		वापस wm831x_rtc_stop_alarm(wm831x_rtc);
पूर्ण

अटल irqवापस_t wm831x_alm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = data;

	rtc_update_irq(wm831x_rtc->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops wm831x_rtc_ops = अणु
	.पढ़ो_समय = wm831x_rtc_पढ़ोसमय,
	.set_समय = wm831x_rtc_समय_रखो,
	.पढ़ो_alarm = wm831x_rtc_पढ़ोalarm,
	.set_alarm = wm831x_rtc_setalarm,
	.alarm_irq_enable = wm831x_rtc_alarm_irq_enable,
पूर्ण;

#अगर_घोषित CONFIG_PM
/* Turn off the alarm अगर it should not be a wake source. */
अटल पूर्णांक wm831x_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	पूर्णांक ret, enable;

	अगर (wm831x_rtc->alarm_enabled && device_may_wakeup(dev))
		enable = WM831X_RTC_ALM_ENA;
	अन्यथा
		enable = 0;

	ret = wm831x_set_bits(wm831x_rtc->wm831x, WM831X_RTC_CONTROL,
			      WM831X_RTC_ALM_ENA, enable);
	अगर (ret != 0)
		dev_err(dev, "Failed to update RTC alarm: %d\n", ret);

	वापस 0;
पूर्ण

/* Enable the alarm अगर it should be enabled (in हाल it was disabled to
 * prevent use as a wake source).
 */
अटल पूर्णांक wm831x_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (wm831x_rtc->alarm_enabled) अणु
		ret = wm831x_rtc_start_alarm(wm831x_rtc);
		अगर (ret != 0)
			dev_err(dev, "Failed to restart RTC alarm: %d\n", ret);
	पूर्ण

	वापस 0;
पूर्ण

/* Unconditionally disable the alarm */
अटल पूर्णांक wm831x_rtc_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = wm831x_set_bits(wm831x_rtc->wm831x, WM831X_RTC_CONTROL,
			      WM831X_RTC_ALM_ENA, 0);
	अगर (ret != 0)
		dev_err(dev, "Failed to stop RTC alarm: %d\n", ret);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा wm831x_rtc_suspend शून्य
#घोषणा wm831x_rtc_resume शून्य
#घोषणा wm831x_rtc_मुक्तze शून्य
#पूर्ण_अगर

अटल पूर्णांक wm831x_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_rtc *wm831x_rtc;
	पूर्णांक alm_irq = wm831x_irq(wm831x, platक्रमm_get_irq_byname(pdev, "ALM"));
	पूर्णांक ret = 0;

	wm831x_rtc = devm_kzalloc(&pdev->dev, माप(*wm831x_rtc), GFP_KERNEL);
	अगर (wm831x_rtc == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, wm831x_rtc);
	wm831x_rtc->wm831x = wm831x;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_RTC_CONTROL);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to read RTC control: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (ret & WM831X_RTC_ALM_ENA)
		wm831x_rtc->alarm_enabled = 1;

	device_init_wakeup(&pdev->dev, 1);

	wm831x_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(wm831x_rtc->rtc))
		वापस PTR_ERR(wm831x_rtc->rtc);

	wm831x_rtc->rtc->ops = &wm831x_rtc_ops;
	wm831x_rtc->rtc->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(wm831x_rtc->rtc);
	अगर (ret)
		वापस ret;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, alm_irq, शून्य,
				wm831x_alm_irq,
				IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				"RTC alarm",
				wm831x_rtc);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request alarm IRQ %d: %d\n",
			alm_irq, ret);
	पूर्ण

	wm831x_rtc_add_अक्रमomness(wm831x);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wm831x_rtc_pm_ops = अणु
	.suspend = wm831x_rtc_suspend,
	.resume = wm831x_rtc_resume,

	.मुक्तze = wm831x_rtc_मुक्तze,
	.thaw = wm831x_rtc_resume,
	.restore = wm831x_rtc_resume,

	.घातeroff = wm831x_rtc_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver wm831x_rtc_driver = अणु
	.probe = wm831x_rtc_probe,
	.driver = अणु
		.name = "wm831x-rtc",
		.pm = &wm831x_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm831x_rtc_driver);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("RTC driver for the WM831x series PMICs");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-rtc");
