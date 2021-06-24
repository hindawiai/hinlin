<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/rtc/rtc-pl030.c
 *
 *  Copyright (C) 2000-2001 Deep Blue Solutions Ltd.
 */
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#घोषणा RTC_DR		(0)
#घोषणा RTC_MR		(4)
#घोषणा RTC_STAT	(8)
#घोषणा RTC_EOI		(8)
#घोषणा RTC_LR		(12)
#घोषणा RTC_CR		(16)
#घोषणा RTC_CR_MIE	(1 << 0)

काष्ठा pl030_rtc अणु
	काष्ठा rtc_device	*rtc;
	व्योम __iomem		*base;
पूर्ण;

अटल irqवापस_t pl030_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pl030_rtc *rtc = dev_id;
	ग_लिखोl(0, rtc->base + RTC_EOI);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pl030_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pl030_rtc *rtc = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl(rtc->base + RTC_MR), &alrm->समय);
	वापस 0;
पूर्ण

अटल पूर्णांक pl030_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pl030_rtc *rtc = dev_get_drvdata(dev);

	ग_लिखोl(rtc_पंचांग_to_समय64(&alrm->समय), rtc->base + RTC_MR);

	वापस 0;
पूर्ण

अटल पूर्णांक pl030_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pl030_rtc *rtc = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl(rtc->base + RTC_DR), पंचांग);

	वापस 0;
पूर्ण

/*
 * Set the RTC समय.  Unक्रमtunately, we can't accurately set
 * the poपूर्णांक at which the counter updates.
 *
 * Also, since RTC_LR is transferred to RTC_CR on next rising
 * edge of the 1Hz घड़ी, we must ग_लिखो the समय one second
 * in advance.
 */
अटल पूर्णांक pl030_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pl030_rtc *rtc = dev_get_drvdata(dev);

	ग_लिखोl(rtc_पंचांग_to_समय64(पंचांग) + 1, rtc->base + RTC_LR);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pl030_ops = अणु
	.पढ़ो_समय	= pl030_पढ़ो_समय,
	.set_समय	= pl030_set_समय,
	.पढ़ो_alarm	= pl030_पढ़ो_alarm,
	.set_alarm	= pl030_set_alarm,
पूर्ण;

अटल पूर्णांक pl030_probe(काष्ठा amba_device *dev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा pl030_rtc *rtc;
	पूर्णांक ret;

	ret = amba_request_regions(dev, शून्य);
	अगर (ret)
		जाओ err_req;

	rtc = devm_kzalloc(&dev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc) अणु
		ret = -ENOMEM;
		जाओ err_rtc;
	पूर्ण

	rtc->rtc = devm_rtc_allocate_device(&dev->dev);
	अगर (IS_ERR(rtc->rtc)) अणु
		ret = PTR_ERR(rtc->rtc);
		जाओ err_rtc;
	पूर्ण

	rtc->rtc->ops = &pl030_ops;
	rtc->rtc->range_max = U32_MAX;
	rtc->base = ioremap(dev->res.start, resource_size(&dev->res));
	अगर (!rtc->base) अणु
		ret = -ENOMEM;
		जाओ err_rtc;
	पूर्ण

	__raw_ग_लिखोl(0, rtc->base + RTC_CR);
	__raw_ग_लिखोl(0, rtc->base + RTC_EOI);

	amba_set_drvdata(dev, rtc);

	ret = request_irq(dev->irq[0], pl030_पूर्णांकerrupt, 0,
			  "rtc-pl030", rtc);
	अगर (ret)
		जाओ err_irq;

	ret = devm_rtc_रेजिस्टर_device(rtc->rtc);
	अगर (ret)
		जाओ err_reg;

	वापस 0;

 err_reg:
	मुक्त_irq(dev->irq[0], rtc);
 err_irq:
	iounmap(rtc->base);
 err_rtc:
	amba_release_regions(dev);
 err_req:
	वापस ret;
पूर्ण

अटल व्योम pl030_हटाओ(काष्ठा amba_device *dev)
अणु
	काष्ठा pl030_rtc *rtc = amba_get_drvdata(dev);

	ग_लिखोl(0, rtc->base + RTC_CR);

	मुक्त_irq(dev->irq[0], rtc);
	iounmap(rtc->base);
	amba_release_regions(dev);
पूर्ण

अटल काष्ठा amba_id pl030_ids[] = अणु
	अणु
		.id	= 0x00041030,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl030_ids);

अटल काष्ठा amba_driver pl030_driver = अणु
	.drv		= अणु
		.name	= "rtc-pl030",
	पूर्ण,
	.probe		= pl030_probe,
	.हटाओ		= pl030_हटाओ,
	.id_table	= pl030_ids,
पूर्ण;

module_amba_driver(pl030_driver);

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("ARM AMBA PL030 RTC Driver");
MODULE_LICENSE("GPL");
