<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Ran Bi <ran.bi@mediatek.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#घोषणा MT2712_BBPU		0x0000
#घोषणा MT2712_BBPU_CLRPKY	BIT(4)
#घोषणा MT2712_BBPU_RELOAD	BIT(5)
#घोषणा MT2712_BBPU_CBUSY	BIT(6)
#घोषणा MT2712_BBPU_KEY		(0x43 << 8)

#घोषणा MT2712_IRQ_STA		0x0004
#घोषणा MT2712_IRQ_STA_AL	BIT(0)
#घोषणा MT2712_IRQ_STA_TC	BIT(1)

#घोषणा MT2712_IRQ_EN		0x0008
#घोषणा MT2712_IRQ_EN_AL	BIT(0)
#घोषणा MT2712_IRQ_EN_TC	BIT(1)
#घोषणा MT2712_IRQ_EN_ONESHOT	BIT(2)

#घोषणा MT2712_CII_EN		0x000c

#घोषणा MT2712_AL_MASK		0x0010
#घोषणा MT2712_AL_MASK_DOW	BIT(4)

#घोषणा MT2712_TC_SEC		0x0014
#घोषणा MT2712_TC_MIN		0x0018
#घोषणा MT2712_TC_HOU		0x001c
#घोषणा MT2712_TC_DOM		0x0020
#घोषणा MT2712_TC_DOW		0x0024
#घोषणा MT2712_TC_MTH		0x0028
#घोषणा MT2712_TC_YEA		0x002c

#घोषणा MT2712_AL_SEC		0x0030
#घोषणा MT2712_AL_MIN		0x0034
#घोषणा MT2712_AL_HOU		0x0038
#घोषणा MT2712_AL_DOM		0x003c
#घोषणा MT2712_AL_DOW		0x0040
#घोषणा MT2712_AL_MTH		0x0044
#घोषणा MT2712_AL_YEA		0x0048

#घोषणा MT2712_SEC_MASK		0x003f
#घोषणा MT2712_MIN_MASK		0x003f
#घोषणा MT2712_HOU_MASK		0x001f
#घोषणा MT2712_DOM_MASK		0x001f
#घोषणा MT2712_DOW_MASK		0x0007
#घोषणा MT2712_MTH_MASK		0x000f
#घोषणा MT2712_YEA_MASK		0x007f

#घोषणा MT2712_POWERKEY1	0x004c
#घोषणा MT2712_POWERKEY2	0x0050
#घोषणा MT2712_POWERKEY1_KEY	0xa357
#घोषणा MT2712_POWERKEY2_KEY	0x67d2

#घोषणा MT2712_CON0		0x005c
#घोषणा MT2712_CON1		0x0060

#घोषणा MT2712_PROT		0x0070
#घोषणा MT2712_PROT_UNLOCK1	0x9136
#घोषणा MT2712_PROT_UNLOCK2	0x586a

#घोषणा MT2712_WRTGR		0x0078

#घोषणा MT2712_RTC_TIMESTAMP_END_2127	4985971199LL

काष्ठा mt2712_rtc अणु
	काष्ठा rtc_device	*rtc;
	व्योम __iomem		*base;
	पूर्णांक			irq;
	u8			irq_wake_enabled;
	u8			घातerlost;
पूर्ण;

अटल अंतरभूत u32 mt2712_पढ़ोl(काष्ठा mt2712_rtc *mt2712_rtc, u32 reg)
अणु
	वापस पढ़ोl(mt2712_rtc->base + reg);
पूर्ण

अटल अंतरभूत व्योम mt2712_ग_लिखोl(काष्ठा mt2712_rtc *mt2712_rtc,
				 u32 reg, u32 val)
अणु
	ग_लिखोl(val, mt2712_rtc->base + reg);
पूर्ण

अटल व्योम mt2712_rtc_ग_लिखो_trigger(काष्ठा mt2712_rtc *mt2712_rtc)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ / 10;

	mt2712_ग_लिखोl(mt2712_rtc, MT2712_WRTGR, 1);
	जबतक (1) अणु
		अगर (!(mt2712_पढ़ोl(mt2712_rtc, MT2712_BBPU)
					& MT2712_BBPU_CBUSY))
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&mt2712_rtc->rtc->dev,
				"%s time out!\n", __func__);
			अवरोध;
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

अटल व्योम mt2712_rtc_ग_लिखोअगर_unlock(काष्ठा mt2712_rtc *mt2712_rtc)
अणु
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_PROT, MT2712_PROT_UNLOCK1);
	mt2712_rtc_ग_लिखो_trigger(mt2712_rtc);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_PROT, MT2712_PROT_UNLOCK2);
	mt2712_rtc_ग_लिखो_trigger(mt2712_rtc);
पूर्ण

अटल irqवापस_t rtc_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mt2712_rtc *mt2712_rtc = data;
	u16 irqsta;

	/* Clear पूर्णांकerrupt */
	irqsta = mt2712_पढ़ोl(mt2712_rtc, MT2712_IRQ_STA);
	अगर (irqsta & MT2712_IRQ_STA_AL) अणु
		rtc_update_irq(mt2712_rtc->rtc, 1, RTC_IRQF | RTC_AF);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम __mt2712_rtc_पढ़ो_समय(काष्ठा mt2712_rtc *mt2712_rtc,
				   काष्ठा rtc_समय *पंचांग, पूर्णांक *sec)
अणु
	पंचांग->पंचांग_sec  = mt2712_पढ़ोl(mt2712_rtc, MT2712_TC_SEC)
			& MT2712_SEC_MASK;
	पंचांग->पंचांग_min  = mt2712_पढ़ोl(mt2712_rtc, MT2712_TC_MIN)
			& MT2712_MIN_MASK;
	पंचांग->पंचांग_hour = mt2712_पढ़ोl(mt2712_rtc, MT2712_TC_HOU)
			& MT2712_HOU_MASK;
	पंचांग->पंचांग_mday = mt2712_पढ़ोl(mt2712_rtc, MT2712_TC_DOM)
			& MT2712_DOM_MASK;
	पंचांग->पंचांग_mon  = (mt2712_पढ़ोl(mt2712_rtc, MT2712_TC_MTH) - 1)
			& MT2712_MTH_MASK;
	पंचांग->पंचांग_year = (mt2712_पढ़ोl(mt2712_rtc, MT2712_TC_YEA) + 100)
			& MT2712_YEA_MASK;

	*sec = mt2712_पढ़ोl(mt2712_rtc, MT2712_TC_SEC) & MT2712_SEC_MASK;
पूर्ण

अटल पूर्णांक mt2712_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mt2712_rtc *mt2712_rtc = dev_get_drvdata(dev);
	पूर्णांक sec;

	अगर (mt2712_rtc->घातerlost)
		वापस -EINVAL;

	करो अणु
		__mt2712_rtc_पढ़ो_समय(mt2712_rtc, पंचांग, &sec);
	पूर्ण जबतक (sec < पंचांग->पंचांग_sec);	/* SEC has carried */

	वापस 0;
पूर्ण

अटल पूर्णांक mt2712_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mt2712_rtc *mt2712_rtc = dev_get_drvdata(dev);

	mt2712_ग_लिखोl(mt2712_rtc, MT2712_TC_SEC, पंचांग->पंचांग_sec  & MT2712_SEC_MASK);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_TC_MIN, पंचांग->पंचांग_min  & MT2712_MIN_MASK);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_TC_HOU, पंचांग->पंचांग_hour & MT2712_HOU_MASK);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_TC_DOM, पंचांग->पंचांग_mday & MT2712_DOM_MASK);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_TC_MTH,
		      (पंचांग->पंचांग_mon + 1) & MT2712_MTH_MASK);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_TC_YEA,
		      (पंचांग->पंचांग_year - 100) & MT2712_YEA_MASK);

	mt2712_rtc_ग_लिखो_trigger(mt2712_rtc);

	अगर (mt2712_rtc->घातerlost)
		mt2712_rtc->घातerlost = false;

	वापस 0;
पूर्ण

अटल पूर्णांक mt2712_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा mt2712_rtc *mt2712_rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alm->समय;
	u16 irqen;

	irqen = mt2712_पढ़ोl(mt2712_rtc, MT2712_IRQ_EN);
	alm->enabled = !!(irqen & MT2712_IRQ_EN_AL);

	पंचांग->पंचांग_sec  = mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_SEC) & MT2712_SEC_MASK;
	पंचांग->पंचांग_min  = mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_MIN) & MT2712_MIN_MASK;
	पंचांग->पंचांग_hour = mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_HOU) & MT2712_HOU_MASK;
	पंचांग->पंचांग_mday = mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_DOM) & MT2712_DOM_MASK;
	पंचांग->पंचांग_mon  = (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_MTH) - 1)
		      & MT2712_MTH_MASK;
	पंचांग->पंचांग_year = (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_YEA) + 100)
		      & MT2712_YEA_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक mt2712_rtc_alarm_irq_enable(काष्ठा device *dev,
				       अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा mt2712_rtc *mt2712_rtc = dev_get_drvdata(dev);
	u16 irqen;

	irqen = mt2712_पढ़ोl(mt2712_rtc, MT2712_IRQ_EN);
	अगर (enabled)
		irqen |= MT2712_IRQ_EN_AL;
	अन्यथा
		irqen &= ~MT2712_IRQ_EN_AL;
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_IRQ_EN, irqen);
	mt2712_rtc_ग_लिखो_trigger(mt2712_rtc);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2712_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा mt2712_rtc *mt2712_rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &alm->समय;

	dev_dbg(&mt2712_rtc->rtc->dev, "set al time: %ptR, alm en: %d\n",
		पंचांग, alm->enabled);

	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_SEC,
		      (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_SEC)
		       & ~(MT2712_SEC_MASK)) | (पंचांग->पंचांग_sec  & MT2712_SEC_MASK));
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_MIN,
		      (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_MIN)
		       & ~(MT2712_MIN_MASK)) | (पंचांग->पंचांग_min  & MT2712_MIN_MASK));
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_HOU,
		      (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_HOU)
		       & ~(MT2712_HOU_MASK)) | (पंचांग->पंचांग_hour & MT2712_HOU_MASK));
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_DOM,
		      (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_DOM)
		       & ~(MT2712_DOM_MASK)) | (पंचांग->पंचांग_mday & MT2712_DOM_MASK));
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_MTH,
		      (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_MTH)
		       & ~(MT2712_MTH_MASK))
		      | ((पंचांग->पंचांग_mon + 1) & MT2712_MTH_MASK));
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_YEA,
		      (mt2712_पढ़ोl(mt2712_rtc, MT2712_AL_YEA)
		       & ~(MT2712_YEA_MASK))
		      | ((पंचांग->पंचांग_year - 100) & MT2712_YEA_MASK));

	/* mask day of week */
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_MASK, MT2712_AL_MASK_DOW);
	mt2712_rtc_ग_लिखो_trigger(mt2712_rtc);

	mt2712_rtc_alarm_irq_enable(dev, alm->enabled);

	वापस 0;
पूर्ण

/* Init RTC रेजिस्टर */
अटल व्योम mt2712_rtc_hw_init(काष्ठा mt2712_rtc *mt2712_rtc)
अणु
	u32 p1, p2;

	mt2712_ग_लिखोl(mt2712_rtc, MT2712_BBPU,
		      MT2712_BBPU_KEY | MT2712_BBPU_RELOAD);

	mt2712_ग_लिखोl(mt2712_rtc, MT2712_CII_EN, 0);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_AL_MASK, 0);
	/* necessary beक्रमe set MT2712_POWERKEY */
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_CON0, 0x4848);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_CON1, 0x0048);

	mt2712_rtc_ग_लिखो_trigger(mt2712_rtc);

	p1 = mt2712_पढ़ोl(mt2712_rtc, MT2712_POWERKEY1);
	p2 = mt2712_पढ़ोl(mt2712_rtc, MT2712_POWERKEY2);
	अगर (p1 != MT2712_POWERKEY1_KEY || p2 != MT2712_POWERKEY2_KEY) अणु
		mt2712_rtc->घातerlost = true;
		dev_dbg(&mt2712_rtc->rtc->dev,
			"powerkey not set (lost power)\n");
	पूर्ण अन्यथा अणु
		mt2712_rtc->घातerlost = false;
	पूर्ण

	/* RTC need POWERKEY1/2 match, then जाओ normal work mode */
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_POWERKEY1, MT2712_POWERKEY1_KEY);
	mt2712_ग_लिखोl(mt2712_rtc, MT2712_POWERKEY2, MT2712_POWERKEY2_KEY);
	mt2712_rtc_ग_लिखो_trigger(mt2712_rtc);

	mt2712_rtc_ग_लिखोअगर_unlock(mt2712_rtc);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mt2712_rtc_ops = अणु
	.पढ़ो_समय	= mt2712_rtc_पढ़ो_समय,
	.set_समय	= mt2712_rtc_set_समय,
	.पढ़ो_alarm	= mt2712_rtc_पढ़ो_alarm,
	.set_alarm	= mt2712_rtc_set_alarm,
	.alarm_irq_enable = mt2712_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक mt2712_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt2712_rtc *mt2712_rtc;
	पूर्णांक ret;

	mt2712_rtc = devm_kzalloc(&pdev->dev,
				  माप(काष्ठा mt2712_rtc), GFP_KERNEL);
	अगर (!mt2712_rtc)
		वापस -ENOMEM;

	mt2712_rtc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mt2712_rtc->base))
		वापस PTR_ERR(mt2712_rtc->base);

	/* rtc hw init */
	mt2712_rtc_hw_init(mt2712_rtc);

	mt2712_rtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mt2712_rtc->irq < 0)
		वापस mt2712_rtc->irq;

	platक्रमm_set_drvdata(pdev, mt2712_rtc);

	mt2712_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(mt2712_rtc->rtc))
		वापस PTR_ERR(mt2712_rtc->rtc);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, mt2712_rtc->irq, शून्य,
					rtc_irq_handler_thपढ़ो,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					dev_name(&mt2712_rtc->rtc->dev),
					mt2712_rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			mt2712_rtc->irq, ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);

	mt2712_rtc->rtc->ops = &mt2712_rtc_ops;
	mt2712_rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	mt2712_rtc->rtc->range_max = MT2712_RTC_TIMESTAMP_END_2127;

	वापस devm_rtc_रेजिस्टर_device(mt2712_rtc->rtc);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mt2712_rtc_suspend(काष्ठा device *dev)
अणु
	पूर्णांक wake_status = 0;
	काष्ठा mt2712_rtc *mt2712_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev)) अणु
		wake_status = enable_irq_wake(mt2712_rtc->irq);
		अगर (!wake_status)
			mt2712_rtc->irq_wake_enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt2712_rtc_resume(काष्ठा device *dev)
अणु
	पूर्णांक wake_status = 0;
	काष्ठा mt2712_rtc *mt2712_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev) && mt2712_rtc->irq_wake_enabled) अणु
		wake_status = disable_irq_wake(mt2712_rtc->irq);
		अगर (!wake_status)
			mt2712_rtc->irq_wake_enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mt2712_pm_ops, mt2712_rtc_suspend,
			 mt2712_rtc_resume);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id mt2712_rtc_of_match[] = अणु
	अणु .compatible = "mediatek,mt2712-rtc", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mt2712_rtc_of_match);

अटल काष्ठा platक्रमm_driver mt2712_rtc_driver = अणु
	.driver = अणु
		.name = "mt2712-rtc",
		.of_match_table = mt2712_rtc_of_match,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm = &mt2712_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe  = mt2712_rtc_probe,
पूर्ण;

module_platक्रमm_driver(mt2712_rtc_driver);

MODULE_DESCRIPTION("MediaTek MT2712 SoC based RTC Driver");
MODULE_AUTHOR("Ran Bi <ran.bi@mediatek.com>");
MODULE_LICENSE("GPL");
