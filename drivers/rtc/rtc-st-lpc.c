<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rtc-st-lpc.c - ST's LPC RTC, घातered by the Low Power Timer
 *
 * Copyright (C) 2014 STMicroelectronics Limited
 *
 * Author: David Paris <david.paris@st.com> क्रम STMicroelectronics
 *         Lee Jones <lee.jones@linaro.org> क्रम STMicroelectronics
 *
 * Based on the original driver written by Stuart Menefy.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#समावेश <dt-bindings/mfd/st-lpc.h>

/* Low Power Timer */
#घोषणा LPC_LPT_LSB_OFF		0x400
#घोषणा LPC_LPT_MSB_OFF		0x404
#घोषणा LPC_LPT_START_OFF	0x408

/* Low Power Alarm */
#घोषणा LPC_LPA_LSB_OFF		0x410
#घोषणा LPC_LPA_MSB_OFF		0x414
#घोषणा LPC_LPA_START_OFF	0x418

/* LPC as WDT */
#घोषणा LPC_WDT_OFF		0x510
#घोषणा LPC_WDT_FLAG_OFF	0x514

काष्ठा st_rtc अणु
	काष्ठा rtc_device *rtc_dev;
	काष्ठा rtc_wkalrm alarm;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clkrate;
	व्योम __iomem *ioaddr;
	bool irq_enabled:1;
	spinlock_t lock;
	लघु irq;
पूर्ण;

अटल व्योम st_rtc_set_hw_alarm(काष्ठा st_rtc *rtc,
				अचिन्हित दीर्घ msb, अचिन्हित दीर्घ  lsb)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc->lock, flags);

	ग_लिखोl_relaxed(1, rtc->ioaddr + LPC_WDT_OFF);

	ग_लिखोl_relaxed(msb, rtc->ioaddr + LPC_LPA_MSB_OFF);
	ग_लिखोl_relaxed(lsb, rtc->ioaddr + LPC_LPA_LSB_OFF);
	ग_लिखोl_relaxed(1, rtc->ioaddr + LPC_LPA_START_OFF);

	ग_लिखोl_relaxed(0, rtc->ioaddr + LPC_WDT_OFF);

	spin_unlock_irqrestore(&rtc->lock, flags);
पूर्ण

अटल irqवापस_t st_rtc_handler(पूर्णांक this_irq, व्योम *data)
अणु
	काष्ठा st_rtc *rtc = (काष्ठा st_rtc *)data;

	rtc_update_irq(rtc->rtc_dev, 1, RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक st_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा st_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ lpt_lsb, lpt_msb;
	अचिन्हित दीर्घ दीर्घ lpt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc->lock, flags);

	करो अणु
		lpt_msb = पढ़ोl_relaxed(rtc->ioaddr + LPC_LPT_MSB_OFF);
		lpt_lsb = पढ़ोl_relaxed(rtc->ioaddr + LPC_LPT_LSB_OFF);
	पूर्ण जबतक (पढ़ोl_relaxed(rtc->ioaddr + LPC_LPT_MSB_OFF) != lpt_msb);

	spin_unlock_irqrestore(&rtc->lock, flags);

	lpt = ((अचिन्हित दीर्घ दीर्घ)lpt_msb << 32) | lpt_lsb;
	करो_भाग(lpt, rtc->clkrate);
	rtc_समय64_to_पंचांग(lpt, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक st_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा st_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ दीर्घ lpt, secs;
	अचिन्हित दीर्घ flags;

	secs = rtc_पंचांग_to_समय64(पंचांग);

	lpt = (अचिन्हित दीर्घ दीर्घ)secs * rtc->clkrate;

	spin_lock_irqsave(&rtc->lock, flags);

	ग_लिखोl_relaxed(lpt >> 32, rtc->ioaddr + LPC_LPT_MSB_OFF);
	ग_लिखोl_relaxed(lpt, rtc->ioaddr + LPC_LPT_LSB_OFF);
	ग_लिखोl_relaxed(1, rtc->ioaddr + LPC_LPT_START_OFF);

	spin_unlock_irqrestore(&rtc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक st_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा st_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc->lock, flags);

	स_नकल(wkalrm, &rtc->alarm, माप(काष्ठा rtc_wkalrm));

	spin_unlock_irqrestore(&rtc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक st_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा st_rtc *rtc = dev_get_drvdata(dev);

	अगर (enabled && !rtc->irq_enabled) अणु
		enable_irq(rtc->irq);
		rtc->irq_enabled = true;
	पूर्ण अन्यथा अगर (!enabled && rtc->irq_enabled) अणु
		disable_irq(rtc->irq);
		rtc->irq_enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा st_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय now;
	अचिन्हित दीर्घ दीर्घ now_secs;
	अचिन्हित दीर्घ दीर्घ alarm_secs;
	अचिन्हित दीर्घ दीर्घ lpa;

	st_rtc_पढ़ो_समय(dev, &now);
	now_secs = rtc_पंचांग_to_समय64(&now);
	alarm_secs = rtc_पंचांग_to_समय64(&t->समय);

	स_नकल(&rtc->alarm, t, माप(काष्ठा rtc_wkalrm));

	/* Now many secs to fire */
	alarm_secs -= now_secs;
	lpa = (अचिन्हित दीर्घ दीर्घ)alarm_secs * rtc->clkrate;

	st_rtc_set_hw_alarm(rtc, lpa >> 32, lpa);
	st_rtc_alarm_irq_enable(dev, t->enabled);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops st_rtc_ops = अणु
	.पढ़ो_समय		= st_rtc_पढ़ो_समय,
	.set_समय		= st_rtc_set_समय,
	.पढ़ो_alarm		= st_rtc_पढ़ो_alarm,
	.set_alarm		= st_rtc_set_alarm,
	.alarm_irq_enable	= st_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक st_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा st_rtc *rtc;
	uपूर्णांक32_t mode;
	पूर्णांक ret = 0;

	ret = of_property_पढ़ो_u32(np, "st,lpc-mode", &mode);
	अगर (ret) अणु
		dev_err(&pdev->dev, "An LPC mode must be provided\n");
		वापस -EINVAL;
	पूर्ण

	/* LPC can either run as a Clocksource or in RTC or WDT mode */
	अगर (mode != ST_LPC_MODE_RTC)
		वापस -ENODEV;

	rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा st_rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	spin_lock_init(&rtc->lock);

	rtc->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->ioaddr))
		वापस PTR_ERR(rtc->ioaddr);

	rtc->irq = irq_of_parse_and_map(np, 0);
	अगर (!rtc->irq) अणु
		dev_err(&pdev->dev, "IRQ missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, rtc->irq, st_rtc_handler, 0,
			       pdev->name, rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq %i\n", rtc->irq);
		वापस ret;
	पूर्ण

	enable_irq_wake(rtc->irq);
	disable_irq(rtc->irq);

	rtc->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rtc->clk)) अणु
		dev_err(&pdev->dev, "Unable to request clock\n");
		वापस PTR_ERR(rtc->clk);
	पूर्ण

	clk_prepare_enable(rtc->clk);

	rtc->clkrate = clk_get_rate(rtc->clk);
	अगर (!rtc->clkrate) अणु
		dev_err(&pdev->dev, "Unable to fetch clock rate\n");
		वापस -EINVAL;
	पूर्ण

	device_set_wakeup_capable(&pdev->dev, 1);

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc_dev->ops = &st_rtc_ops;
	rtc->rtc_dev->range_max = U64_MAX;
	करो_भाग(rtc->rtc_dev->range_max, rtc->clkrate);

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
	अगर (ret) अणु
		clk_disable_unprepare(rtc->clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक st_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा st_rtc *rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		वापस 0;

	ग_लिखोl_relaxed(1, rtc->ioaddr + LPC_WDT_OFF);
	ग_लिखोl_relaxed(0, rtc->ioaddr + LPC_LPA_START_OFF);
	ग_लिखोl_relaxed(0, rtc->ioaddr + LPC_WDT_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक st_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा st_rtc *rtc = dev_get_drvdata(dev);

	rtc_alarm_irq_enable(rtc->rtc_dev, 0);

	/*
	 * clean 'rtc->alarm' to allow a new
	 * .set_alarm to the upper RTC layer
	 */
	स_रखो(&rtc->alarm, 0, माप(काष्ठा rtc_wkalrm));

	ग_लिखोl_relaxed(0, rtc->ioaddr + LPC_LPA_MSB_OFF);
	ग_लिखोl_relaxed(0, rtc->ioaddr + LPC_LPA_LSB_OFF);
	ग_लिखोl_relaxed(1, rtc->ioaddr + LPC_WDT_OFF);
	ग_लिखोl_relaxed(1, rtc->ioaddr + LPC_LPA_START_OFF);
	ग_लिखोl_relaxed(0, rtc->ioaddr + LPC_WDT_OFF);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(st_rtc_pm_ops, st_rtc_suspend, st_rtc_resume);

अटल स्थिर काष्ठा of_device_id st_rtc_match[] = अणु
	अणु .compatible = "st,stih407-lpc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st_rtc_match);

अटल काष्ठा platक्रमm_driver st_rtc_platक्रमm_driver = अणु
	.driver = अणु
		.name = "st-lpc-rtc",
		.pm = &st_rtc_pm_ops,
		.of_match_table = st_rtc_match,
	पूर्ण,
	.probe = st_rtc_probe,
पूर्ण;

module_platक्रमm_driver(st_rtc_platक्रमm_driver);

MODULE_DESCRIPTION("STMicroelectronics LPC RTC driver");
MODULE_AUTHOR("David Paris <david.paris@st.com>");
MODULE_LICENSE("GPL");
