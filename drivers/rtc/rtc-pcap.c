<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  pcap rtc code क्रम Motorola EZX phones
 *
 *  Copyright (c) 2008 guiming zhuo <gmzhuo@gmail.com>
 *  Copyright (c) 2009 Daniel Ribeiro <drwyrm@gmail.com>
 *
 *  Based on Motorola's rtc.c Copyright (c) 2003-2005 Motorola
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/ezx-pcap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा pcap_rtc अणु
	काष्ठा pcap_chip *pcap;
	काष्ठा rtc_device *rtc;
पूर्ण;

अटल irqवापस_t pcap_rtc_irq(पूर्णांक irq, व्योम *_pcap_rtc)
अणु
	काष्ठा pcap_rtc *pcap_rtc = _pcap_rtc;
	अचिन्हित दीर्घ rtc_events;

	अगर (irq == pcap_to_irq(pcap_rtc->pcap, PCAP_IRQ_1HZ))
		rtc_events = RTC_IRQF | RTC_UF;
	अन्यथा अगर (irq == pcap_to_irq(pcap_rtc->pcap, PCAP_IRQ_TODA))
		rtc_events = RTC_IRQF | RTC_AF;
	अन्यथा
		rtc_events = 0;

	rtc_update_irq(pcap_rtc->rtc, 1, rtc_events);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pcap_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcap_rtc *pcap_rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alrm->समय;
	अचिन्हित दीर्घ secs;
	u32 tod;	/* समय of day, seconds since midnight */
	u32 days;	/* days since 1/1/1970 */

	ezx_pcap_पढ़ो(pcap_rtc->pcap, PCAP_REG_RTC_TODA, &tod);
	secs = tod & PCAP_RTC_TOD_MASK;

	ezx_pcap_पढ़ो(pcap_rtc->pcap, PCAP_REG_RTC_DAYA, &days);
	secs += (days & PCAP_RTC_DAY_MASK) * SEC_PER_DAY;

	rtc_समय64_to_पंचांग(secs, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pcap_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcap_rtc *pcap_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ secs = rtc_पंचांग_to_समय64(&alrm->समय);
	u32 tod, days;

	tod = secs % SEC_PER_DAY;
	ezx_pcap_ग_लिखो(pcap_rtc->pcap, PCAP_REG_RTC_TODA, tod);

	days = secs / SEC_PER_DAY;
	ezx_pcap_ग_लिखो(pcap_rtc->pcap, PCAP_REG_RTC_DAYA, days);

	वापस 0;
पूर्ण

अटल पूर्णांक pcap_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcap_rtc *pcap_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ secs;
	u32 tod, days;

	ezx_pcap_पढ़ो(pcap_rtc->pcap, PCAP_REG_RTC_TOD, &tod);
	secs = tod & PCAP_RTC_TOD_MASK;

	ezx_pcap_पढ़ो(pcap_rtc->pcap, PCAP_REG_RTC_DAY, &days);
	secs += (days & PCAP_RTC_DAY_MASK) * SEC_PER_DAY;

	rtc_समय64_to_पंचांग(secs, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pcap_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcap_rtc *pcap_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ secs = rtc_पंचांग_to_समय64(पंचांग);
	u32 tod, days;

	tod = secs % SEC_PER_DAY;
	ezx_pcap_ग_लिखो(pcap_rtc->pcap, PCAP_REG_RTC_TOD, tod);

	days = secs / SEC_PER_DAY;
	ezx_pcap_ग_लिखो(pcap_rtc->pcap, PCAP_REG_RTC_DAY, days);

	वापस 0;
पूर्ण

अटल पूर्णांक pcap_rtc_irq_enable(काष्ठा device *dev, पूर्णांक pirq, अचिन्हित पूर्णांक en)
अणु
	काष्ठा pcap_rtc *pcap_rtc = dev_get_drvdata(dev);

	अगर (en)
		enable_irq(pcap_to_irq(pcap_rtc->pcap, pirq));
	अन्यथा
		disable_irq(pcap_to_irq(pcap_rtc->pcap, pirq));

	वापस 0;
पूर्ण

अटल पूर्णांक pcap_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक en)
अणु
	वापस pcap_rtc_irq_enable(dev, PCAP_IRQ_TODA, en);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pcap_rtc_ops = अणु
	.पढ़ो_समय = pcap_rtc_पढ़ो_समय,
	.set_समय = pcap_rtc_set_समय,
	.पढ़ो_alarm = pcap_rtc_पढ़ो_alarm,
	.set_alarm = pcap_rtc_set_alarm,
	.alarm_irq_enable = pcap_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक __init pcap_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcap_rtc *pcap_rtc;
	पूर्णांक समयr_irq, alarm_irq;
	पूर्णांक err = -ENOMEM;

	pcap_rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा pcap_rtc),
				GFP_KERNEL);
	अगर (!pcap_rtc)
		वापस err;

	pcap_rtc->pcap = dev_get_drvdata(pdev->dev.parent);

	platक्रमm_set_drvdata(pdev, pcap_rtc);

	pcap_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pcap_rtc->rtc))
		वापस PTR_ERR(pcap_rtc->rtc);

	pcap_rtc->rtc->ops = &pcap_rtc_ops;
	pcap_rtc->rtc->range_max = (1 << 14) * 86400ULL - 1;

	समयr_irq = pcap_to_irq(pcap_rtc->pcap, PCAP_IRQ_1HZ);
	alarm_irq = pcap_to_irq(pcap_rtc->pcap, PCAP_IRQ_TODA);

	err = devm_request_irq(&pdev->dev, समयr_irq, pcap_rtc_irq, 0,
				"RTC Timer", pcap_rtc);
	अगर (err)
		वापस err;

	err = devm_request_irq(&pdev->dev, alarm_irq, pcap_rtc_irq, 0,
				"RTC Alarm", pcap_rtc);
	अगर (err)
		वापस err;

	वापस devm_rtc_रेजिस्टर_device(pcap_rtc->rtc);
पूर्ण

अटल पूर्णांक __निकास pcap_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcap_rtc_driver = अणु
	.हटाओ = __निकास_p(pcap_rtc_हटाओ),
	.driver = अणु
		.name  = "pcap-rtc",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(pcap_rtc_driver, pcap_rtc_probe);

MODULE_DESCRIPTION("Motorola pcap rtc driver");
MODULE_AUTHOR("guiming zhuo <gmzhuo@gmail.com>");
MODULE_LICENSE("GPL");
