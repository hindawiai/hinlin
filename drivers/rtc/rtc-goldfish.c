<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* drivers/rtc/rtc-goldfish.c
 *
 * Copyright (C) 2007 Google, Inc.
 * Copyright (C) 2017 Imagination Technologies Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#घोषणा TIMER_TIME_LOW		0x00	/* get low bits of current समय  */
					/*   and update TIMER_TIME_HIGH  */
#घोषणा TIMER_TIME_HIGH	0x04	/* get high bits of समय at last */
					/*   TIMER_TIME_LOW पढ़ो         */
#घोषणा TIMER_ALARM_LOW	0x08	/* set low bits of alarm and     */
					/*   activate it                 */
#घोषणा TIMER_ALARM_HIGH	0x0c	/* set high bits of next alarm   */
#घोषणा TIMER_IRQ_ENABLED	0x10
#घोषणा TIMER_CLEAR_ALARM	0x14
#घोषणा TIMER_ALARM_STATUS	0x18
#घोषणा TIMER_CLEAR_INTERRUPT	0x1c

काष्ठा goldfish_rtc अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा rtc_device *rtc;
पूर्ण;

अटल पूर्णांक goldfish_rtc_पढ़ो_alarm(काष्ठा device *dev,
				   काष्ठा rtc_wkalrm *alrm)
अणु
	u64 rtc_alarm;
	u64 rtc_alarm_low;
	u64 rtc_alarm_high;
	व्योम __iomem *base;
	काष्ठा goldfish_rtc *rtcdrv;

	rtcdrv = dev_get_drvdata(dev);
	base = rtcdrv->base;

	rtc_alarm_low = पढ़ोl(base + TIMER_ALARM_LOW);
	rtc_alarm_high = पढ़ोl(base + TIMER_ALARM_HIGH);
	rtc_alarm = (rtc_alarm_high << 32) | rtc_alarm_low;

	करो_भाग(rtc_alarm, NSEC_PER_SEC);
	स_रखो(alrm, 0, माप(काष्ठा rtc_wkalrm));

	rtc_समय64_to_पंचांग(rtc_alarm, &alrm->समय);

	अगर (पढ़ोl(base + TIMER_ALARM_STATUS))
		alrm->enabled = 1;
	अन्यथा
		alrm->enabled = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक goldfish_rtc_set_alarm(काष्ठा device *dev,
				  काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा goldfish_rtc *rtcdrv;
	u64 rtc_alarm64;
	u64 rtc_status_reg;
	व्योम __iomem *base;

	rtcdrv = dev_get_drvdata(dev);
	base = rtcdrv->base;

	अगर (alrm->enabled) अणु
		rtc_alarm64 = rtc_पंचांग_to_समय64(&alrm->समय) * NSEC_PER_SEC;
		ग_लिखोl((rtc_alarm64 >> 32), base + TIMER_ALARM_HIGH);
		ग_लिखोl(rtc_alarm64, base + TIMER_ALARM_LOW);
		ग_लिखोl(1, base + TIMER_IRQ_ENABLED);
	पूर्ण अन्यथा अणु
		/*
		 * अगर this function was called with enabled=0
		 * then it could mean that the application is
		 * trying to cancel an ongoing alarm
		 */
		rtc_status_reg = पढ़ोl(base + TIMER_ALARM_STATUS);
		अगर (rtc_status_reg)
			ग_लिखोl(1, base + TIMER_CLEAR_ALARM);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goldfish_rtc_alarm_irq_enable(काष्ठा device *dev,
					 अचिन्हित पूर्णांक enabled)
अणु
	व्योम __iomem *base;
	काष्ठा goldfish_rtc *rtcdrv;

	rtcdrv = dev_get_drvdata(dev);
	base = rtcdrv->base;

	अगर (enabled)
		ग_लिखोl(1, base + TIMER_IRQ_ENABLED);
	अन्यथा
		ग_लिखोl(0, base + TIMER_IRQ_ENABLED);

	वापस 0;
पूर्ण

अटल irqवापस_t goldfish_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा goldfish_rtc *rtcdrv = dev_id;
	व्योम __iomem *base = rtcdrv->base;

	ग_लिखोl(1, base + TIMER_CLEAR_INTERRUPT);

	rtc_update_irq(rtcdrv->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक goldfish_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा goldfish_rtc *rtcdrv;
	व्योम __iomem *base;
	u64 समय_high;
	u64 समय_low;
	u64 समय;

	rtcdrv = dev_get_drvdata(dev);
	base = rtcdrv->base;

	समय_low = पढ़ोl(base + TIMER_TIME_LOW);
	समय_high = पढ़ोl(base + TIMER_TIME_HIGH);
	समय = (समय_high << 32) | समय_low;

	करो_भाग(समय, NSEC_PER_SEC);

	rtc_समय64_to_पंचांग(समय, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक goldfish_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा goldfish_rtc *rtcdrv;
	व्योम __iomem *base;
	u64 now64;

	rtcdrv = dev_get_drvdata(dev);
	base = rtcdrv->base;

	now64 = rtc_पंचांग_to_समय64(पंचांग) * NSEC_PER_SEC;
	ग_लिखोl((now64 >> 32), base + TIMER_TIME_HIGH);
	ग_लिखोl(now64, base + TIMER_TIME_LOW);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops goldfish_rtc_ops = अणु
	.पढ़ो_समय	= goldfish_rtc_पढ़ो_समय,
	.set_समय	= goldfish_rtc_set_समय,
	.पढ़ो_alarm	= goldfish_rtc_पढ़ो_alarm,
	.set_alarm	= goldfish_rtc_set_alarm,
	.alarm_irq_enable = goldfish_rtc_alarm_irq_enable
पूर्ण;

अटल पूर्णांक goldfish_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा goldfish_rtc *rtcdrv;
	पूर्णांक err;

	rtcdrv = devm_kzalloc(&pdev->dev, माप(*rtcdrv), GFP_KERNEL);
	अगर (!rtcdrv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, rtcdrv);
	rtcdrv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtcdrv->base))
		वापस PTR_ERR(rtcdrv->base);

	rtcdrv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rtcdrv->irq < 0)
		वापस -ENODEV;

	rtcdrv->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtcdrv->rtc))
		वापस PTR_ERR(rtcdrv->rtc);

	rtcdrv->rtc->ops = &goldfish_rtc_ops;
	rtcdrv->rtc->range_max = U64_MAX / NSEC_PER_SEC;

	err = devm_request_irq(&pdev->dev, rtcdrv->irq,
			       goldfish_rtc_पूर्णांकerrupt,
			       0, pdev->name, rtcdrv);
	अगर (err)
		वापस err;

	वापस devm_rtc_रेजिस्टर_device(rtcdrv->rtc);
पूर्ण

अटल स्थिर काष्ठा of_device_id goldfish_rtc_of_match[] = अणु
	अणु .compatible = "google,goldfish-rtc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, goldfish_rtc_of_match);

अटल काष्ठा platक्रमm_driver goldfish_rtc = अणु
	.probe = goldfish_rtc_probe,
	.driver = अणु
		.name = "goldfish_rtc",
		.of_match_table = goldfish_rtc_of_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(goldfish_rtc);

MODULE_LICENSE("GPL v2");
