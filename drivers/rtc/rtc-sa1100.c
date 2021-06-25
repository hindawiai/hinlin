<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Real Time Clock पूर्णांकerface क्रम StrongARM SA1x00 and XScale PXA2xx
 *
 * Copyright (c) 2000 Nils Faerber
 *
 * Based on rtc.c by Paul Gorपंचांगaker
 *
 * Original Driver by Nils Faerber <nils@kernelconcepts.de>
 *
 * Modअगरications from:
 *   CIH <cih@coventive.com>
 *   Nicolas Pitre <nico@fluxnic.net>
 *   Andrew Christian <andrew.christian@hp.com>
 *
 * Converted to the RTC subप्रणाली and Driver Model
 *   by Riअक्षरd Purdie <rpurdie@rpsys.net>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>

#घोषणा RTSR_HZE		BIT(3)	/* HZ पूर्णांकerrupt enable */
#घोषणा RTSR_ALE		BIT(2)	/* RTC alarm पूर्णांकerrupt enable */
#घोषणा RTSR_HZ			BIT(1)	/* HZ rising-edge detected */
#घोषणा RTSR_AL			BIT(0)	/* RTC alarm detected */

#समावेश "rtc-sa1100.h"

#घोषणा RTC_DEF_DIVIDER		(32768 - 1)
#घोषणा RTC_DEF_TRIM		0
#घोषणा RTC_FREQ		1024


अटल irqवापस_t sa1100_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev_id);
	काष्ठा rtc_device *rtc = info->rtc;
	अचिन्हित पूर्णांक rtsr;
	अचिन्हित दीर्घ events = 0;

	spin_lock(&info->lock);

	rtsr = पढ़ोl_relaxed(info->rtsr);
	/* clear पूर्णांकerrupt sources */
	ग_लिखोl_relaxed(0, info->rtsr);
	/* Fix क्रम a nasty initialization problem the in SA11xx RTSR रेजिस्टर.
	 * See also the comments in sa1100_rtc_probe(). */
	अगर (rtsr & (RTSR_ALE | RTSR_HZE)) अणु
		/* This is the original code, beक्रमe there was the अगर test
		 * above. This code करोes not clear पूर्णांकerrupts that were not
		 * enabled. */
		ग_लिखोl_relaxed((RTSR_AL | RTSR_HZ) & (rtsr >> 2), info->rtsr);
	पूर्ण अन्यथा अणु
		/* For some reason, it is possible to enter this routine
		 * without पूर्णांकerruptions enabled, it has been tested with
		 * several units (Bug in SA11xx chip?).
		 *
		 * This situation leads to an infinite "loop" of पूर्णांकerrupt
		 * routine calling and as a result the processor seems to
		 * lock on its first call to खोलो(). */
		ग_लिखोl_relaxed(RTSR_AL | RTSR_HZ, info->rtsr);
	पूर्ण

	/* clear alarm पूर्णांकerrupt अगर it has occurred */
	अगर (rtsr & RTSR_AL)
		rtsr &= ~RTSR_ALE;
	ग_लिखोl_relaxed(rtsr & (RTSR_ALE | RTSR_HZE), info->rtsr);

	/* update irq data & counter */
	अगर (rtsr & RTSR_AL)
		events |= RTC_AF | RTC_IRQF;
	अगर (rtsr & RTSR_HZ)
		events |= RTC_UF | RTC_IRQF;

	rtc_update_irq(rtc, 1, events);

	spin_unlock(&info->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sa1100_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	u32 rtsr;
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);

	spin_lock_irq(&info->lock);
	rtsr = पढ़ोl_relaxed(info->rtsr);
	अगर (enabled)
		rtsr |= RTSR_ALE;
	अन्यथा
		rtsr &= ~RTSR_ALE;
	ग_लिखोl_relaxed(rtsr, info->rtsr);
	spin_unlock_irq(&info->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl_relaxed(info->rcnr), पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);

	ग_लिखोl_relaxed(rtc_पंचांग_to_समय64(पंचांग), info->rcnr);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	u32	rtsr;
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);

	rtsr = पढ़ोl_relaxed(info->rtsr);
	alrm->enabled = (rtsr & RTSR_ALE) ? 1 : 0;
	alrm->pending = (rtsr & RTSR_AL) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);

	spin_lock_irq(&info->lock);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(info->rtsr) &
		(RTSR_HZE | RTSR_ALE | RTSR_AL), info->rtsr);
	ग_लिखोl_relaxed(rtc_पंचांग_to_समय64(&alrm->समय), info->rtar);
	अगर (alrm->enabled)
		ग_लिखोl_relaxed(पढ़ोl_relaxed(info->rtsr) | RTSR_ALE, info->rtsr);
	अन्यथा
		ग_लिखोl_relaxed(पढ़ोl_relaxed(info->rtsr) & ~RTSR_ALE, info->rtsr);
	spin_unlock_irq(&info->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);

	seq_म_लिखो(seq, "trim/divider\t\t: 0x%08x\n", पढ़ोl_relaxed(info->rttr));
	seq_म_लिखो(seq, "RTSR\t\t\t: 0x%08x\n", पढ़ोl_relaxed(info->rtsr));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sa1100_rtc_ops = अणु
	.पढ़ो_समय = sa1100_rtc_पढ़ो_समय,
	.set_समय = sa1100_rtc_set_समय,
	.पढ़ो_alarm = sa1100_rtc_पढ़ो_alarm,
	.set_alarm = sa1100_rtc_set_alarm,
	.proc = sa1100_rtc_proc,
	.alarm_irq_enable = sa1100_rtc_alarm_irq_enable,
पूर्ण;

पूर्णांक sa1100_rtc_init(काष्ठा platक्रमm_device *pdev, काष्ठा sa1100_rtc *info)
अणु
	पूर्णांक ret;

	spin_lock_init(&info->lock);

	info->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(info->clk)) अणु
		dev_err(&pdev->dev, "failed to find rtc clock source\n");
		वापस PTR_ERR(info->clk);
	पूर्ण

	ret = clk_prepare_enable(info->clk);
	अगर (ret)
		वापस ret;
	/*
	 * According to the manual we should be able to let RTTR be zero
	 * and then a शेष भागiser क्रम a 32.768KHz घड़ी is used.
	 * Apparently this करोesn't work, at least क्रम my SA1110 rev 5.
	 * If the घड़ी भागider is uninitialized then reset it to the
	 * शेष value to get the 1Hz घड़ी.
	 */
	अगर (पढ़ोl_relaxed(info->rttr) == 0) अणु
		ग_लिखोl_relaxed(RTC_DEF_DIVIDER + (RTC_DEF_TRIM << 16), info->rttr);
		dev_warn(&pdev->dev, "warning: "
			"initializing default clock divider/trim value\n");
		/* The current RTC value probably करोesn't make sense either */
		ग_लिखोl_relaxed(0, info->rcnr);
	पूर्ण

	info->rtc->ops = &sa1100_rtc_ops;
	info->rtc->max_user_freq = RTC_FREQ;
	info->rtc->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(info->rtc);
	अगर (ret) अणु
		clk_disable_unprepare(info->clk);
		वापस ret;
	पूर्ण

	/* Fix क्रम a nasty initialization problem the in SA11xx RTSR रेजिस्टर.
	 * See also the comments in sa1100_rtc_पूर्णांकerrupt().
	 *
	 * Someबार bit 1 of the RTSR (RTSR_HZ) will wake up 1, which means an
	 * पूर्णांकerrupt pending, even though पूर्णांकerrupts were never enabled.
	 * In this हाल, this bit it must be reset beक्रमe enabling
	 * पूर्णांकerruptions to aव्योम a nonexistent पूर्णांकerrupt to occur.
	 *
	 * In principle, the same problem would apply to bit 0, although it has
	 * never been observed to happen.
	 *
	 * This issue is addressed both here and in sa1100_rtc_पूर्णांकerrupt().
	 * If the issue is not addressed here, in the बार when the processor
	 * wakes up with the bit set there will be one spurious पूर्णांकerrupt.
	 *
	 * The issue is also dealt with in sa1100_rtc_पूर्णांकerrupt() to be on the
	 * safe side, once the condition that lead to this strange
	 * initialization is unknown and could in principle happen during
	 * normal processing.
	 *
	 * Notice that clearing bit 1 and 0 is accomplished by writting ONES to
	 * the corresponding bits in RTSR. */
	ग_लिखोl_relaxed(RTSR_AL | RTSR_HZ, info->rtsr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sa1100_rtc_init);

अटल पूर्णांक sa1100_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa1100_rtc *info;
	व्योम __iomem *base;
	पूर्णांक irq_1hz, irq_alarm;
	पूर्णांक ret;

	irq_1hz = platक्रमm_get_irq_byname(pdev, "rtc 1Hz");
	irq_alarm = platक्रमm_get_irq_byname(pdev, "rtc alarm");
	अगर (irq_1hz < 0 || irq_alarm < 0)
		वापस -ENODEV;

	info = devm_kzalloc(&pdev->dev, माप(काष्ठा sa1100_rtc), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->irq_1hz = irq_1hz;
	info->irq_alarm = irq_alarm;

	info->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(info->rtc))
		वापस PTR_ERR(info->rtc);

	ret = devm_request_irq(&pdev->dev, irq_1hz, sa1100_rtc_पूर्णांकerrupt, 0,
			       "rtc 1Hz", &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IRQ %d already in use.\n", irq_1hz);
		वापस ret;
	पूर्ण
	ret = devm_request_irq(&pdev->dev, irq_alarm, sa1100_rtc_पूर्णांकerrupt, 0,
			       "rtc Alrm", &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "IRQ %d already in use.\n", irq_alarm);
		वापस ret;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	अगर (IS_ENABLED(CONFIG_ARCH_SA1100) ||
	    of_device_is_compatible(pdev->dev.of_node, "mrvl,sa1100-rtc")) अणु
		info->rcnr = base + 0x04;
		info->rtsr = base + 0x10;
		info->rtar = base + 0x00;
		info->rttr = base + 0x08;
	पूर्ण अन्यथा अणु
		info->rcnr = base + 0x0;
		info->rtsr = base + 0x8;
		info->rtar = base + 0x4;
		info->rttr = base + 0xc;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	वापस sa1100_rtc_init(pdev, info);
पूर्ण

अटल पूर्णांक sa1100_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa1100_rtc *info = platक्रमm_get_drvdata(pdev);

	अगर (info) अणु
		spin_lock_irq(&info->lock);
		ग_लिखोl_relaxed(0, info->rtsr);
		spin_unlock_irq(&info->lock);
		clk_disable_unprepare(info->clk);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sa1100_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);
	अगर (device_may_wakeup(dev))
		enable_irq_wake(info->irq_alarm);
	वापस 0;
पूर्ण

अटल पूर्णांक sa1100_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा sa1100_rtc *info = dev_get_drvdata(dev);
	अगर (device_may_wakeup(dev))
		disable_irq_wake(info->irq_alarm);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sa1100_rtc_pm_ops, sa1100_rtc_suspend,
			sa1100_rtc_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sa1100_rtc_dt_ids[] = अणु
	अणु .compatible = "mrvl,sa1100-rtc", पूर्ण,
	अणु .compatible = "mrvl,mmp-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sa1100_rtc_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sa1100_rtc_driver = अणु
	.probe		= sa1100_rtc_probe,
	.हटाओ		= sa1100_rtc_हटाओ,
	.driver		= अणु
		.name	= "sa1100-rtc",
		.pm	= &sa1100_rtc_pm_ops,
		.of_match_table = of_match_ptr(sa1100_rtc_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sa1100_rtc_driver);

MODULE_AUTHOR("Richard Purdie <rpurdie@rpsys.net>");
MODULE_DESCRIPTION("SA11x0/PXA2xx Realtime Clock Driver (RTC)");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sa1100-rtc");
