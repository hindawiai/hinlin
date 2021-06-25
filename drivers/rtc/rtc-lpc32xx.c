<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2010 NXP Semiconductors
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

/*
 * Clock and Power control रेजिस्टर offsets
 */
#घोषणा LPC32XX_RTC_UCOUNT		0x00
#घोषणा LPC32XX_RTC_DCOUNT		0x04
#घोषणा LPC32XX_RTC_MATCH0		0x08
#घोषणा LPC32XX_RTC_MATCH1		0x0C
#घोषणा LPC32XX_RTC_CTRL		0x10
#घोषणा LPC32XX_RTC_INTSTAT		0x14
#घोषणा LPC32XX_RTC_KEY			0x18
#घोषणा LPC32XX_RTC_SRAM		0x80

#घोषणा LPC32XX_RTC_CTRL_MATCH0		(1 << 0)
#घोषणा LPC32XX_RTC_CTRL_MATCH1		(1 << 1)
#घोषणा LPC32XX_RTC_CTRL_ONSW_MATCH0	(1 << 2)
#घोषणा LPC32XX_RTC_CTRL_ONSW_MATCH1	(1 << 3)
#घोषणा LPC32XX_RTC_CTRL_SW_RESET	(1 << 4)
#घोषणा LPC32XX_RTC_CTRL_CNTR_DIS	(1 << 6)
#घोषणा LPC32XX_RTC_CTRL_ONSW_FORCE_HI	(1 << 7)

#घोषणा LPC32XX_RTC_INTSTAT_MATCH0	(1 << 0)
#घोषणा LPC32XX_RTC_INTSTAT_MATCH1	(1 << 1)
#घोषणा LPC32XX_RTC_INTSTAT_ONSW	(1 << 2)

#घोषणा LPC32XX_RTC_KEY_ONSW_LOADVAL	0xB5C13F27

#घोषणा rtc_पढ़ोl(dev, reg) \
	__raw_पढ़ोl((dev)->rtc_base + (reg))
#घोषणा rtc_ग_लिखोl(dev, reg, val) \
	__raw_ग_लिखोl((val), (dev)->rtc_base + (reg))

काष्ठा lpc32xx_rtc अणु
	व्योम __iomem *rtc_base;
	पूर्णांक irq;
	अचिन्हित अक्षर alarm_enabled;
	काष्ठा rtc_device *rtc;
	spinlock_t lock;
पूर्ण;

अटल पूर्णांक lpc32xx_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	अचिन्हित दीर्घ elapsed_sec;
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	elapsed_sec = rtc_पढ़ोl(rtc, LPC32XX_RTC_UCOUNT);
	rtc_समय64_to_पंचांग(elapsed_sec, समय);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);
	u32 secs = rtc_पंचांग_to_समय64(समय);
	u32 पंचांगp;

	spin_lock_irq(&rtc->lock);

	/* RTC must be disabled during count update */
	पंचांगp = rtc_पढ़ोl(rtc, LPC32XX_RTC_CTRL);
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL, पंचांगp | LPC32XX_RTC_CTRL_CNTR_DIS);
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_UCOUNT, secs);
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_DCOUNT, 0xFFFFFFFF - secs);
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL, पंचांगp &= ~LPC32XX_RTC_CTRL_CNTR_DIS);

	spin_unlock_irq(&rtc->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_rtc_पढ़ो_alarm(काष्ठा device *dev,
	काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(rtc_पढ़ोl(rtc, LPC32XX_RTC_MATCH0), &wkalrm->समय);
	wkalrm->enabled = rtc->alarm_enabled;
	wkalrm->pending = !!(rtc_पढ़ोl(rtc, LPC32XX_RTC_INTSTAT) &
		LPC32XX_RTC_INTSTAT_MATCH0);

	वापस rtc_valid_पंचांग(&wkalrm->समय);
पूर्ण

अटल पूर्णांक lpc32xx_rtc_set_alarm(काष्ठा device *dev,
	काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ alarmsecs;
	u32 पंचांगp;

	alarmsecs = rtc_पंचांग_to_समय64(&wkalrm->समय);

	spin_lock_irq(&rtc->lock);

	/* Disable alarm during update */
	पंचांगp = rtc_पढ़ोl(rtc, LPC32XX_RTC_CTRL);
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL, पंचांगp & ~LPC32XX_RTC_CTRL_MATCH0);

	rtc_ग_लिखोl(rtc, LPC32XX_RTC_MATCH0, alarmsecs);

	rtc->alarm_enabled = wkalrm->enabled;
	अगर (wkalrm->enabled) अणु
		rtc_ग_लिखोl(rtc, LPC32XX_RTC_INTSTAT,
			   LPC32XX_RTC_INTSTAT_MATCH0);
		rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL, पंचांगp |
			   LPC32XX_RTC_CTRL_MATCH0);
	पूर्ण

	spin_unlock_irq(&rtc->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_rtc_alarm_irq_enable(काष्ठा device *dev,
	अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);
	u32 पंचांगp;

	spin_lock_irq(&rtc->lock);
	पंचांगp = rtc_पढ़ोl(rtc, LPC32XX_RTC_CTRL);

	अगर (enabled) अणु
		rtc->alarm_enabled = 1;
		पंचांगp |= LPC32XX_RTC_CTRL_MATCH0;
	पूर्ण अन्यथा अणु
		rtc->alarm_enabled = 0;
		पंचांगp &= ~LPC32XX_RTC_CTRL_MATCH0;
	पूर्ण

	rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL, पंचांगp);
	spin_unlock_irq(&rtc->lock);

	वापस 0;
पूर्ण

अटल irqवापस_t lpc32xx_rtc_alarm_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev;

	spin_lock(&rtc->lock);

	/* Disable alarm पूर्णांकerrupt */
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL,
		rtc_पढ़ोl(rtc, LPC32XX_RTC_CTRL) &
			  ~LPC32XX_RTC_CTRL_MATCH0);
	rtc->alarm_enabled = 0;

	/*
	 * Write a large value to the match value so the RTC won't
	 * keep firing the match status
	 */
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_MATCH0, 0xFFFFFFFF);
	rtc_ग_लिखोl(rtc, LPC32XX_RTC_INTSTAT, LPC32XX_RTC_INTSTAT_MATCH0);

	spin_unlock(&rtc->lock);

	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops lpc32xx_rtc_ops = अणु
	.पढ़ो_समय		= lpc32xx_rtc_पढ़ो_समय,
	.set_समय		= lpc32xx_rtc_set_समय,
	.पढ़ो_alarm		= lpc32xx_rtc_पढ़ो_alarm,
	.set_alarm		= lpc32xx_rtc_set_alarm,
	.alarm_irq_enable	= lpc32xx_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक lpc32xx_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_rtc *rtc;
	पूर्णांक err;
	u32 पंचांगp;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (unlikely(!rtc))
		वापस -ENOMEM;

	rtc->rtc_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->rtc_base))
		वापस PTR_ERR(rtc->rtc_base);

	spin_lock_init(&rtc->lock);

	/*
	 * The RTC is on a separate घातer करोमुख्य and can keep it's state
	 * across a chip घातer cycle. If the RTC has never been previously
	 * setup, then set it up now क्रम the first समय.
	 */
	पंचांगp = rtc_पढ़ोl(rtc, LPC32XX_RTC_CTRL);
	अगर (rtc_पढ़ोl(rtc, LPC32XX_RTC_KEY) != LPC32XX_RTC_KEY_ONSW_LOADVAL) अणु
		पंचांगp &= ~(LPC32XX_RTC_CTRL_SW_RESET |
			LPC32XX_RTC_CTRL_CNTR_DIS |
			LPC32XX_RTC_CTRL_MATCH0 |
			LPC32XX_RTC_CTRL_MATCH1 |
			LPC32XX_RTC_CTRL_ONSW_MATCH0 |
			LPC32XX_RTC_CTRL_ONSW_MATCH1 |
			LPC32XX_RTC_CTRL_ONSW_FORCE_HI);
		rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL, पंचांगp);

		/* Clear latched पूर्णांकerrupt states */
		rtc_ग_लिखोl(rtc, LPC32XX_RTC_MATCH0, 0xFFFFFFFF);
		rtc_ग_लिखोl(rtc, LPC32XX_RTC_INTSTAT,
			   LPC32XX_RTC_INTSTAT_MATCH0 |
			   LPC32XX_RTC_INTSTAT_MATCH1 |
			   LPC32XX_RTC_INTSTAT_ONSW);

		/* Write key value to RTC so it won't reload on reset */
		rtc_ग_लिखोl(rtc, LPC32XX_RTC_KEY,
			   LPC32XX_RTC_KEY_ONSW_LOADVAL);
	पूर्ण अन्यथा अणु
		rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL,
			   पंचांगp & ~LPC32XX_RTC_CTRL_MATCH0);
	पूर्ण

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc))
		वापस PTR_ERR(rtc->rtc);

	rtc->rtc->ops = &lpc32xx_rtc_ops;
	rtc->rtc->range_max = U32_MAX;

	err = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (err)
		वापस err;

	/*
	 * IRQ is enabled after device registration in हाल alarm IRQ
	 * is pending upon suspend निकास.
	 */
	rtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rtc->irq < 0) अणु
		dev_warn(&pdev->dev, "Can't get interrupt resource\n");
	पूर्ण अन्यथा अणु
		अगर (devm_request_irq(&pdev->dev, rtc->irq,
				     lpc32xx_rtc_alarm_पूर्णांकerrupt,
				     0, pdev->name, rtc) < 0) अणु
			dev_warn(&pdev->dev, "Can't request interrupt.\n");
			rtc->irq = -1;
		पूर्ण अन्यथा अणु
			device_init_wakeup(&pdev->dev, 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lpc32xx_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	अगर (rtc->irq >= 0) अणु
		अगर (device_may_wakeup(dev))
			enable_irq_wake(rtc->irq);
		अन्यथा
			disable_irq_wake(rtc->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	अगर (rtc->irq >= 0 && device_may_wakeup(dev))
		disable_irq_wake(rtc->irq);

	वापस 0;
पूर्ण

/* Unconditionally disable the alarm */
अटल पूर्णांक lpc32xx_rtc_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	spin_lock_irq(&rtc->lock);

	rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL,
		rtc_पढ़ोl(rtc, LPC32XX_RTC_CTRL) &
			  ~LPC32XX_RTC_CTRL_MATCH0);

	spin_unlock_irq(&rtc->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_rtc_thaw(काष्ठा device *dev)
अणु
	काष्ठा lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	अगर (rtc->alarm_enabled) अणु
		spin_lock_irq(&rtc->lock);

		rtc_ग_लिखोl(rtc, LPC32XX_RTC_CTRL,
			   rtc_पढ़ोl(rtc, LPC32XX_RTC_CTRL) |
			   LPC32XX_RTC_CTRL_MATCH0);

		spin_unlock_irq(&rtc->lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lpc32xx_rtc_pm_ops = अणु
	.suspend = lpc32xx_rtc_suspend,
	.resume = lpc32xx_rtc_resume,
	.मुक्तze = lpc32xx_rtc_मुक्तze,
	.thaw = lpc32xx_rtc_thaw,
	.restore = lpc32xx_rtc_resume
पूर्ण;

#घोषणा LPC32XX_RTC_PM_OPS (&lpc32xx_rtc_pm_ops)
#अन्यथा
#घोषणा LPC32XX_RTC_PM_OPS शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lpc32xx_rtc_match[] = अणु
	अणु .compatible = "nxp,lpc3220-rtc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_rtc_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver lpc32xx_rtc_driver = अणु
	.probe		= lpc32xx_rtc_probe,
	.driver = अणु
		.name	= "rtc-lpc32xx",
		.pm	= LPC32XX_RTC_PM_OPS,
		.of_match_table = of_match_ptr(lpc32xx_rtc_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lpc32xx_rtc_driver);

MODULE_AUTHOR("Kevin Wells <wellsk40@gmail.com");
MODULE_DESCRIPTION("RTC driver for the LPC32xx SoC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-lpc32xx");
