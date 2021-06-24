<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * APM X-Gene SoC Real Time Clock Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Rameshwar Prasad Sahu <rsahu@apm.com>
 *         Loc Ho <lho@apm.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

/* RTC CSR Registers */
#घोषणा RTC_CCVR		0x00
#घोषणा RTC_CMR			0x04
#घोषणा RTC_CLR			0x08
#घोषणा RTC_CCR			0x0C
#घोषणा  RTC_CCR_IE		BIT(0)
#घोषणा  RTC_CCR_MASK		BIT(1)
#घोषणा  RTC_CCR_EN		BIT(2)
#घोषणा  RTC_CCR_WEN		BIT(3)
#घोषणा RTC_STAT		0x10
#घोषणा  RTC_STAT_BIT		BIT(0)
#घोषणा RTC_RSTAT		0x14
#घोषणा RTC_EOI			0x18
#घोषणा RTC_VER			0x1C

काष्ठा xgene_rtc_dev अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *csr_base;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक irq_wake;
	अचिन्हित पूर्णांक irq_enabled;
पूर्ण;

अटल पूर्णांक xgene_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा xgene_rtc_dev *pdata = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl(pdata->csr_base + RTC_CCVR), पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक xgene_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा xgene_rtc_dev *pdata = dev_get_drvdata(dev);

	/*
	 * NOTE: After the following ग_लिखो, the RTC_CCVR is only reflected
	 *       after the update cycle of 1 seconds.
	 */
	ग_लिखोl((u32)rtc_पंचांग_to_समय64(पंचांग), pdata->csr_base + RTC_CLR);
	पढ़ोl(pdata->csr_base + RTC_CLR); /* Force a barrier */

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा xgene_rtc_dev *pdata = dev_get_drvdata(dev);

	/* If possible, CMR should be पढ़ो here */
	rtc_समय64_to_पंचांग(0, &alrm->समय);
	alrm->enabled = पढ़ोl(pdata->csr_base + RTC_CCR) & RTC_CCR_IE;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_rtc_alarm_irq_enable(काष्ठा device *dev, u32 enabled)
अणु
	काष्ठा xgene_rtc_dev *pdata = dev_get_drvdata(dev);
	u32 ccr;

	ccr = पढ़ोl(pdata->csr_base + RTC_CCR);
	अगर (enabled) अणु
		ccr &= ~RTC_CCR_MASK;
		ccr |= RTC_CCR_IE;
	पूर्ण अन्यथा अणु
		ccr &= ~RTC_CCR_IE;
		ccr |= RTC_CCR_MASK;
	पूर्ण
	ग_लिखोl(ccr, pdata->csr_base + RTC_CCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_rtc_alarm_irq_enabled(काष्ठा device *dev)
अणु
	काष्ठा xgene_rtc_dev *pdata = dev_get_drvdata(dev);

	वापस पढ़ोl(pdata->csr_base + RTC_CCR) & RTC_CCR_IE ? 1 : 0;
पूर्ण

अटल पूर्णांक xgene_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा xgene_rtc_dev *pdata = dev_get_drvdata(dev);

	ग_लिखोl((u32)rtc_पंचांग_to_समय64(&alrm->समय), pdata->csr_base + RTC_CMR);

	xgene_rtc_alarm_irq_enable(dev, alrm->enabled);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops xgene_rtc_ops = अणु
	.पढ़ो_समय	= xgene_rtc_पढ़ो_समय,
	.set_समय	= xgene_rtc_set_समय,
	.पढ़ो_alarm	= xgene_rtc_पढ़ो_alarm,
	.set_alarm	= xgene_rtc_set_alarm,
	.alarm_irq_enable = xgene_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t xgene_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा xgene_rtc_dev *pdata = id;

	/* Check अगर पूर्णांकerrupt निश्चितed */
	अगर (!(पढ़ोl(pdata->csr_base + RTC_STAT) & RTC_STAT_BIT))
		वापस IRQ_NONE;

	/* Clear पूर्णांकerrupt */
	पढ़ोl(pdata->csr_base + RTC_EOI);

	rtc_update_irq(pdata->rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xgene_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_rtc_dev *pdata;
	पूर्णांक ret;
	पूर्णांक irq;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, pdata);

	pdata->csr_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdata->csr_base))
		वापस PTR_ERR(pdata->csr_base);

	pdata->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(pdata->rtc))
		वापस PTR_ERR(pdata->rtc);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	ret = devm_request_irq(&pdev->dev, irq, xgene_rtc_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), pdata);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not request IRQ\n");
		वापस ret;
	पूर्ण

	pdata->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pdata->clk)) अणु
		dev_err(&pdev->dev, "Couldn't get the clock for RTC\n");
		वापस -ENODEV;
	पूर्ण
	ret = clk_prepare_enable(pdata->clk);
	अगर (ret)
		वापस ret;

	/* Turn on the घड़ी and the crystal */
	ग_लिखोl(RTC_CCR_EN, pdata->csr_base + RTC_CCR);

	ret = device_init_wakeup(&pdev->dev, 1);
	अगर (ret) अणु
		clk_disable_unprepare(pdata->clk);
		वापस ret;
	पूर्ण

	/* HW करोes not support update faster than 1 seconds */
	pdata->rtc->uie_unsupported = 1;
	pdata->rtc->ops = &xgene_rtc_ops;
	pdata->rtc->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(pdata->rtc);
	अगर (ret) अणु
		clk_disable_unprepare(pdata->clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_rtc_dev *pdata = platक्रमm_get_drvdata(pdev);

	xgene_rtc_alarm_irq_enable(&pdev->dev, 0);
	device_init_wakeup(&pdev->dev, 0);
	clk_disable_unprepare(pdata->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xgene_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा xgene_rtc_dev *pdata = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);

	/*
	 * If this RTC alarm will be used क्रम waking the प्रणाली up,
	 * करोn't disable it of course. Else we just disable the alarm
	 * and aरुको suspension.
	 */
	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (!enable_irq_wake(irq))
			pdata->irq_wake = 1;
	पूर्ण अन्यथा अणु
		pdata->irq_enabled = xgene_rtc_alarm_irq_enabled(dev);
		xgene_rtc_alarm_irq_enable(dev, 0);
		clk_disable_unprepare(pdata->clk);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xgene_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा xgene_rtc_dev *pdata = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq;
	पूर्णांक rc;

	irq = platक्रमm_get_irq(pdev, 0);

	अगर (device_may_wakeup(&pdev->dev)) अणु
		अगर (pdata->irq_wake) अणु
			disable_irq_wake(irq);
			pdata->irq_wake = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = clk_prepare_enable(pdata->clk);
		अगर (rc) अणु
			dev_err(dev, "Unable to enable clock error %d\n", rc);
			वापस rc;
		पूर्ण
		xgene_rtc_alarm_irq_enable(dev, pdata->irq_enabled);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(xgene_rtc_pm_ops, xgene_rtc_suspend, xgene_rtc_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id xgene_rtc_of_match[] = अणु
	अणु.compatible = "apm,xgene-rtc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_rtc_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver xgene_rtc_driver = अणु
	.probe		= xgene_rtc_probe,
	.हटाओ		= xgene_rtc_हटाओ,
	.driver		= अणु
		.name	= "xgene-rtc",
		.pm = &xgene_rtc_pm_ops,
		.of_match_table	= of_match_ptr(xgene_rtc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xgene_rtc_driver);

MODULE_DESCRIPTION("APM X-Gene SoC RTC driver");
MODULE_AUTHOR("Rameshwar Sahu <rsahu@apm.com>");
MODULE_LICENSE("GPL");
