<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Real Time Clock पूर्णांकerface क्रम XScale PXA27x and PXA3xx
 *
 * Copyright (C) 2008 Robert Jarzmik
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <mach/hardware.h>

#समावेश "rtc-sa1100.h"

#घोषणा RTC_DEF_DIVIDER		(32768 - 1)
#घोषणा RTC_DEF_TRIM		0
#घोषणा MAXFREQ_PERIODIC	1000

/*
 * PXA Registers and bits definitions
 */
#घोषणा RTSR_PICE	(1 << 15)	/* Periodic पूर्णांकerrupt count enable */
#घोषणा RTSR_PIALE	(1 << 14)	/* Periodic पूर्णांकerrupt Alarm enable */
#घोषणा RTSR_PIAL	(1 << 13)	/* Periodic पूर्णांकerrupt detected */
#घोषणा RTSR_SWALE2	(1 << 11)	/* RTC stopwatch alarm2 enable */
#घोषणा RTSR_SWAL2	(1 << 10)	/* RTC stopwatch alarm2 detected */
#घोषणा RTSR_SWALE1	(1 << 9)	/* RTC stopwatch alarm1 enable */
#घोषणा RTSR_SWAL1	(1 << 8)	/* RTC stopwatch alarm1 detected */
#घोषणा RTSR_RDALE2	(1 << 7)	/* RTC alarm2 enable */
#घोषणा RTSR_RDAL2	(1 << 6)	/* RTC alarm2 detected */
#घोषणा RTSR_RDALE1	(1 << 5)	/* RTC alarm1 enable */
#घोषणा RTSR_RDAL1	(1 << 4)	/* RTC alarm1 detected */
#घोषणा RTSR_HZE	(1 << 3)	/* HZ पूर्णांकerrupt enable */
#घोषणा RTSR_ALE	(1 << 2)	/* RTC alarm पूर्णांकerrupt enable */
#घोषणा RTSR_HZ		(1 << 1)	/* HZ rising-edge detected */
#घोषणा RTSR_AL		(1 << 0)	/* RTC alarm detected */
#घोषणा RTSR_TRIG_MASK	(RTSR_AL | RTSR_HZ | RTSR_RDAL1 | RTSR_RDAL2\
			 | RTSR_SWAL1 | RTSR_SWAL2)
#घोषणा RYxR_YEAR_S	9
#घोषणा RYxR_YEAR_MASK	(0xfff << RYxR_YEAR_S)
#घोषणा RYxR_MONTH_S	5
#घोषणा RYxR_MONTH_MASK	(0xf << RYxR_MONTH_S)
#घोषणा RYxR_DAY_MASK	0x1f
#घोषणा RDxR_WOM_S     20
#घोषणा RDxR_WOM_MASK  (0x7 << RDxR_WOM_S)
#घोषणा RDxR_DOW_S     17
#घोषणा RDxR_DOW_MASK  (0x7 << RDxR_DOW_S)
#घोषणा RDxR_HOUR_S	12
#घोषणा RDxR_HOUR_MASK	(0x1f << RDxR_HOUR_S)
#घोषणा RDxR_MIN_S	6
#घोषणा RDxR_MIN_MASK	(0x3f << RDxR_MIN_S)
#घोषणा RDxR_SEC_MASK	0x3f

#घोषणा RTSR		0x08
#घोषणा RTTR		0x0c
#घोषणा RDCR		0x10
#घोषणा RYCR		0x14
#घोषणा RDAR1		0x18
#घोषणा RYAR1		0x1c
#घोषणा RTCPICR		0x34
#घोषणा PIAR		0x38

#घोषणा rtc_पढ़ोl(pxa_rtc, reg)	\
	__raw_पढ़ोl((pxa_rtc)->base + (reg))
#घोषणा rtc_ग_लिखोl(pxa_rtc, reg, value)	\
	__raw_ग_लिखोl((value), (pxa_rtc)->base + (reg))

काष्ठा pxa_rtc अणु
	काष्ठा sa1100_rtc sa1100_rtc;
	काष्ठा resource	*ress;
	व्योम __iomem		*base;
	काष्ठा rtc_device	*rtc;
	spinlock_t		lock;		/* Protects this काष्ठाure */
पूर्ण;


अटल u32 ryxr_calc(काष्ठा rtc_समय *पंचांग)
अणु
	वापस ((पंचांग->पंचांग_year + 1900) << RYxR_YEAR_S)
		| ((पंचांग->पंचांग_mon + 1) << RYxR_MONTH_S)
		| पंचांग->पंचांग_mday;
पूर्ण

अटल u32 rdxr_calc(काष्ठा rtc_समय *पंचांग)
अणु
	वापस ((((पंचांग->पंचांग_mday + 6) / 7) << RDxR_WOM_S) & RDxR_WOM_MASK)
		| (((पंचांग->पंचांग_wday + 1) << RDxR_DOW_S) & RDxR_DOW_MASK)
		| (पंचांग->पंचांग_hour << RDxR_HOUR_S)
		| (पंचांग->पंचांग_min << RDxR_MIN_S)
		| पंचांग->पंचांग_sec;
पूर्ण

अटल व्योम पंचांग_calc(u32 rycr, u32 rdcr, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_year = ((rycr & RYxR_YEAR_MASK) >> RYxR_YEAR_S) - 1900;
	पंचांग->पंचांग_mon = (((rycr & RYxR_MONTH_MASK) >> RYxR_MONTH_S)) - 1;
	पंचांग->पंचांग_mday = (rycr & RYxR_DAY_MASK);
	पंचांग->पंचांग_wday = ((rycr & RDxR_DOW_MASK) >> RDxR_DOW_S) - 1;
	पंचांग->पंचांग_hour = (rdcr & RDxR_HOUR_MASK) >> RDxR_HOUR_S;
	पंचांग->पंचांग_min = (rdcr & RDxR_MIN_MASK) >> RDxR_MIN_S;
	पंचांग->पंचांग_sec = rdcr & RDxR_SEC_MASK;
पूर्ण

अटल व्योम rtsr_clear_bits(काष्ठा pxa_rtc *pxa_rtc, u32 mask)
अणु
	u32 rtsr;

	rtsr = rtc_पढ़ोl(pxa_rtc, RTSR);
	rtsr &= ~RTSR_TRIG_MASK;
	rtsr &= ~mask;
	rtc_ग_लिखोl(pxa_rtc, RTSR, rtsr);
पूर्ण

अटल व्योम rtsr_set_bits(काष्ठा pxa_rtc *pxa_rtc, u32 mask)
अणु
	u32 rtsr;

	rtsr = rtc_पढ़ोl(pxa_rtc, RTSR);
	rtsr &= ~RTSR_TRIG_MASK;
	rtsr |= mask;
	rtc_ग_लिखोl(pxa_rtc, RTSR, rtsr);
पूर्ण

अटल irqवापस_t pxa_rtc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev_id);
	u32 rtsr;
	अचिन्हित दीर्घ events = 0;

	spin_lock(&pxa_rtc->lock);

	/* clear पूर्णांकerrupt sources */
	rtsr = rtc_पढ़ोl(pxa_rtc, RTSR);
	rtc_ग_लिखोl(pxa_rtc, RTSR, rtsr);

	/* temporary disable rtc पूर्णांकerrupts */
	rtsr_clear_bits(pxa_rtc, RTSR_RDALE1 | RTSR_PIALE | RTSR_HZE);

	/* clear alarm पूर्णांकerrupt अगर it has occurred */
	अगर (rtsr & RTSR_RDAL1)
		rtsr &= ~RTSR_RDALE1;

	/* update irq data & counter */
	अगर (rtsr & RTSR_RDAL1)
		events |= RTC_AF | RTC_IRQF;
	अगर (rtsr & RTSR_HZ)
		events |= RTC_UF | RTC_IRQF;
	अगर (rtsr & RTSR_PIAL)
		events |= RTC_PF | RTC_IRQF;

	rtc_update_irq(pxa_rtc->rtc, 1, events);

	/* enable back rtc पूर्णांकerrupts */
	rtc_ग_लिखोl(pxa_rtc, RTSR, rtsr & ~RTSR_TRIG_MASK);

	spin_unlock(&pxa_rtc->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pxa_rtc_खोलो(काष्ठा device *dev)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = request_irq(pxa_rtc->sa1100_rtc.irq_1hz, pxa_rtc_irq, 0,
			  "rtc 1Hz", dev);
	अगर (ret < 0) अणु
		dev_err(dev, "can't get irq %i, err %d\n",
			pxa_rtc->sa1100_rtc.irq_1hz, ret);
		जाओ err_irq_1Hz;
	पूर्ण
	ret = request_irq(pxa_rtc->sa1100_rtc.irq_alarm, pxa_rtc_irq, 0,
			  "rtc Alrm", dev);
	अगर (ret < 0) अणु
		dev_err(dev, "can't get irq %i, err %d\n",
			pxa_rtc->sa1100_rtc.irq_alarm, ret);
		जाओ err_irq_Alrm;
	पूर्ण

	वापस 0;

err_irq_Alrm:
	मुक्त_irq(pxa_rtc->sa1100_rtc.irq_1hz, dev);
err_irq_1Hz:
	वापस ret;
पूर्ण

अटल व्योम pxa_rtc_release(काष्ठा device *dev)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	spin_lock_irq(&pxa_rtc->lock);
	rtsr_clear_bits(pxa_rtc, RTSR_PIALE | RTSR_RDALE1 | RTSR_HZE);
	spin_unlock_irq(&pxa_rtc->lock);

	मुक्त_irq(pxa_rtc->sa1100_rtc.irq_1hz, dev);
	मुक्त_irq(pxa_rtc->sa1100_rtc.irq_alarm, dev);
पूर्ण

अटल पूर्णांक pxa_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	spin_lock_irq(&pxa_rtc->lock);

	अगर (enabled)
		rtsr_set_bits(pxa_rtc, RTSR_RDALE1);
	अन्यथा
		rtsr_clear_bits(pxa_rtc, RTSR_RDALE1);

	spin_unlock_irq(&pxa_rtc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	u32 rycr, rdcr;

	rycr = rtc_पढ़ोl(pxa_rtc, RYCR);
	rdcr = rtc_पढ़ोl(pxa_rtc, RDCR);

	पंचांग_calc(rycr, rdcr, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	rtc_ग_लिखोl(pxa_rtc, RYCR, ryxr_calc(पंचांग));
	rtc_ग_लिखोl(pxa_rtc, RDCR, rdxr_calc(पंचांग));

	वापस 0;
पूर्ण

अटल पूर्णांक pxa_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	u32 rtsr, ryar, rdar;

	ryar = rtc_पढ़ोl(pxa_rtc, RYAR1);
	rdar = rtc_पढ़ोl(pxa_rtc, RDAR1);
	पंचांग_calc(ryar, rdar, &alrm->समय);

	rtsr = rtc_पढ़ोl(pxa_rtc, RTSR);
	alrm->enabled = (rtsr & RTSR_RDALE1) ? 1 : 0;
	alrm->pending = (rtsr & RTSR_RDAL1) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	u32 rtsr;

	spin_lock_irq(&pxa_rtc->lock);

	rtc_ग_लिखोl(pxa_rtc, RYAR1, ryxr_calc(&alrm->समय));
	rtc_ग_लिखोl(pxa_rtc, RDAR1, rdxr_calc(&alrm->समय));

	rtsr = rtc_पढ़ोl(pxa_rtc, RTSR);
	अगर (alrm->enabled)
		rtsr |= RTSR_RDALE1;
	अन्यथा
		rtsr &= ~RTSR_RDALE1;
	rtc_ग_लिखोl(pxa_rtc, RTSR, rtsr);

	spin_unlock_irq(&pxa_rtc->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	seq_म_लिखो(seq, "trim/divider\t: 0x%08x\n", rtc_पढ़ोl(pxa_rtc, RTTR));
	seq_म_लिखो(seq, "update_IRQ\t: %s\n",
		   (rtc_पढ़ोl(pxa_rtc, RTSR) & RTSR_HZE) ? "yes" : "no");
	seq_म_लिखो(seq, "periodic_IRQ\t: %s\n",
		   (rtc_पढ़ोl(pxa_rtc, RTSR) & RTSR_PIALE) ? "yes" : "no");
	seq_म_लिखो(seq, "periodic_freq\t: %u\n", rtc_पढ़ोl(pxa_rtc, PIAR));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pxa_rtc_ops = अणु
	.पढ़ो_समय = pxa_rtc_पढ़ो_समय,
	.set_समय = pxa_rtc_set_समय,
	.पढ़ो_alarm = pxa_rtc_पढ़ो_alarm,
	.set_alarm = pxa_rtc_set_alarm,
	.alarm_irq_enable = pxa_alarm_irq_enable,
	.proc = pxa_rtc_proc,
पूर्ण;

अटल पूर्णांक __init pxa_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pxa_rtc *pxa_rtc;
	काष्ठा sa1100_rtc *sa1100_rtc;
	पूर्णांक ret;

	pxa_rtc = devm_kzalloc(dev, माप(*pxa_rtc), GFP_KERNEL);
	अगर (!pxa_rtc)
		वापस -ENOMEM;
	sa1100_rtc = &pxa_rtc->sa1100_rtc;

	spin_lock_init(&pxa_rtc->lock);
	platक्रमm_set_drvdata(pdev, pxa_rtc);

	pxa_rtc->ress = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!pxa_rtc->ress) अणु
		dev_err(dev, "No I/O memory resource defined\n");
		वापस -ENXIO;
	पूर्ण

	sa1100_rtc->irq_1hz = platक्रमm_get_irq(pdev, 0);
	अगर (sa1100_rtc->irq_1hz < 0)
		वापस -ENXIO;
	sa1100_rtc->irq_alarm = platक्रमm_get_irq(pdev, 1);
	अगर (sa1100_rtc->irq_alarm < 0)
		वापस -ENXIO;

	pxa_rtc->base = devm_ioremap(dev, pxa_rtc->ress->start,
				resource_size(pxa_rtc->ress));
	अगर (!pxa_rtc->base) अणु
		dev_err(dev, "Unable to map pxa RTC I/O memory\n");
		वापस -ENOMEM;
	पूर्ण

	pxa_rtc_खोलो(dev);

	sa1100_rtc->rcnr = pxa_rtc->base + 0x0;
	sa1100_rtc->rtsr = pxa_rtc->base + 0x8;
	sa1100_rtc->rtar = pxa_rtc->base + 0x4;
	sa1100_rtc->rttr = pxa_rtc->base + 0xc;
	ret = sa1100_rtc_init(pdev, sa1100_rtc);
	अगर (ret) अणु
		dev_err(dev, "Unable to init SA1100 RTC sub-device\n");
		वापस ret;
	पूर्ण

	rtsr_clear_bits(pxa_rtc, RTSR_PIALE | RTSR_RDALE1 | RTSR_HZE);

	pxa_rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "pxa-rtc",
						&pxa_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(pxa_rtc->rtc)) अणु
		ret = PTR_ERR(pxa_rtc->rtc);
		dev_err(dev, "Failed to register RTC device -> %d\n", ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास pxa_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	pxa_rtc_release(dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa_rtc_dt_ids[] = अणु
	अणु .compatible = "marvell,pxa-rtc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa_rtc_dt_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pxa_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(pxa_rtc->sa1100_rtc.irq_alarm);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(pxa_rtc->sa1100_rtc.irq_alarm);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pxa_rtc_pm_ops, pxa_rtc_suspend, pxa_rtc_resume);

अटल काष्ठा platक्रमm_driver pxa_rtc_driver = अणु
	.हटाओ		= __निकास_p(pxa_rtc_हटाओ),
	.driver		= अणु
		.name	= "pxa-rtc",
		.of_match_table = of_match_ptr(pxa_rtc_dt_ids),
		.pm	= &pxa_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(pxa_rtc_driver, pxa_rtc_probe);

MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
MODULE_DESCRIPTION("PXA27x/PXA3xx Realtime Clock Driver (RTC)");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa-rtc");
