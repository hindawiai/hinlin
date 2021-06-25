<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2019 Cadence
 *
 * Authors:
 *  Jan Kotas <jank@cadence.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/rtc.h>
#समावेश <linux/clk.h>
#समावेश <linux/bcd.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_wakeirq.h>

/* Registers */
#घोषणा CDNS_RTC_CTLR		0x00
#घोषणा CDNS_RTC_HMR		0x04
#घोषणा CDNS_RTC_TIMR		0x08
#घोषणा CDNS_RTC_CALR		0x0C
#घोषणा CDNS_RTC_TIMAR		0x10
#घोषणा CDNS_RTC_CALAR		0x14
#घोषणा CDNS_RTC_AENR		0x18
#घोषणा CDNS_RTC_EFLR		0x1C
#घोषणा CDNS_RTC_IENR		0x20
#घोषणा CDNS_RTC_IDISR		0x24
#घोषणा CDNS_RTC_IMSKR		0x28
#घोषणा CDNS_RTC_STSR		0x2C
#घोषणा CDNS_RTC_KRTCR		0x30

/* Control */
#घोषणा CDNS_RTC_CTLR_TIME	BIT(0)
#घोषणा CDNS_RTC_CTLR_CAL	BIT(1)
#घोषणा CDNS_RTC_CTLR_TIME_CAL	(CDNS_RTC_CTLR_TIME | CDNS_RTC_CTLR_CAL)

/* Status */
#घोषणा CDNS_RTC_STSR_VT	BIT(0)
#घोषणा CDNS_RTC_STSR_VC	BIT(1)
#घोषणा CDNS_RTC_STSR_VTA	BIT(2)
#घोषणा CDNS_RTC_STSR_VCA	BIT(3)
#घोषणा CDNS_RTC_STSR_VT_VC	(CDNS_RTC_STSR_VT | CDNS_RTC_STSR_VC)
#घोषणा CDNS_RTC_STSR_VTA_VCA	(CDNS_RTC_STSR_VTA | CDNS_RTC_STSR_VCA)

/* Keep RTC */
#घोषणा CDNS_RTC_KRTCR_KRTC	BIT(0)

/* Alarm, Event, Interrupt */
#घोषणा CDNS_RTC_AEI_HOS	BIT(0)
#घोषणा CDNS_RTC_AEI_SEC	BIT(1)
#घोषणा CDNS_RTC_AEI_MIN	BIT(2)
#घोषणा CDNS_RTC_AEI_HOUR	BIT(3)
#घोषणा CDNS_RTC_AEI_DATE	BIT(4)
#घोषणा CDNS_RTC_AEI_MNTH	BIT(5)
#घोषणा CDNS_RTC_AEI_ALRM	BIT(6)

/* Time */
#घोषणा CDNS_RTC_TIME_H		GENMASK(7, 0)
#घोषणा CDNS_RTC_TIME_S		GENMASK(14, 8)
#घोषणा CDNS_RTC_TIME_M		GENMASK(22, 16)
#घोषणा CDNS_RTC_TIME_HR	GENMASK(29, 24)
#घोषणा CDNS_RTC_TIME_PM	BIT(30)
#घोषणा CDNS_RTC_TIME_CH	BIT(31)

/* Calendar */
#घोषणा CDNS_RTC_CAL_DAY	GENMASK(2, 0)
#घोषणा CDNS_RTC_CAL_M		GENMASK(7, 3)
#घोषणा CDNS_RTC_CAL_D		GENMASK(13, 8)
#घोषणा CDNS_RTC_CAL_Y		GENMASK(23, 16)
#घोषणा CDNS_RTC_CAL_C		GENMASK(29, 24)
#घोषणा CDNS_RTC_CAL_CH		BIT(31)

#घोषणा CDNS_RTC_MAX_REGS_TRIES	3

काष्ठा cdns_rtc अणु
	काष्ठा rtc_device *rtc_dev;
	काष्ठा clk *pclk;
	काष्ठा clk *ref_clk;
	व्योम __iomem *regs;
	पूर्णांक irq;
पूर्ण;

अटल व्योम cdns_rtc_set_enabled(काष्ठा cdns_rtc *crtc, bool enabled)
अणु
	u32 reg = enabled ? 0x0 : CDNS_RTC_CTLR_TIME_CAL;

	ग_लिखोl(reg, crtc->regs + CDNS_RTC_CTLR);
पूर्ण

अटल bool cdns_rtc_get_enabled(काष्ठा cdns_rtc *crtc)
अणु
	वापस !(पढ़ोl(crtc->regs + CDNS_RTC_CTLR) & CDNS_RTC_CTLR_TIME_CAL);
पूर्ण

अटल irqवापस_t cdns_rtc_irq_handler(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा device *dev = id;
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);

	/* Reading the रेजिस्टर clears it */
	अगर (!(पढ़ोl(crtc->regs + CDNS_RTC_EFLR) & CDNS_RTC_AEI_ALRM))
		वापस IRQ_NONE;

	rtc_update_irq(crtc->rtc_dev, 1, RTC_IRQF | RTC_AF);
	वापस IRQ_HANDLED;
पूर्ण

अटल u32 cdns_rtc_समय2reg(काष्ठा rtc_समय *पंचांग)
अणु
	वापस FIELD_PREP(CDNS_RTC_TIME_S,  bin2bcd(पंचांग->पंचांग_sec))
	     | FIELD_PREP(CDNS_RTC_TIME_M,  bin2bcd(पंचांग->पंचांग_min))
	     | FIELD_PREP(CDNS_RTC_TIME_HR, bin2bcd(पंचांग->पंचांग_hour));
पूर्ण

अटल व्योम cdns_rtc_reg2समय(u32 reg, काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_sec  = bcd2bin(FIELD_GET(CDNS_RTC_TIME_S, reg));
	पंचांग->पंचांग_min  = bcd2bin(FIELD_GET(CDNS_RTC_TIME_M, reg));
	पंचांग->पंचांग_hour = bcd2bin(FIELD_GET(CDNS_RTC_TIME_HR, reg));
पूर्ण

अटल पूर्णांक cdns_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);
	u32 reg;

	/* If the RTC is disabled, assume the values are invalid */
	अगर (!cdns_rtc_get_enabled(crtc))
		वापस -EINVAL;

	cdns_rtc_set_enabled(crtc, false);

	reg = पढ़ोl(crtc->regs + CDNS_RTC_TIMR);
	cdns_rtc_reg2समय(reg, पंचांग);

	reg = पढ़ोl(crtc->regs + CDNS_RTC_CALR);
	पंचांग->पंचांग_mday = bcd2bin(FIELD_GET(CDNS_RTC_CAL_D, reg));
	पंचांग->पंचांग_mon  = bcd2bin(FIELD_GET(CDNS_RTC_CAL_M, reg)) - 1;
	पंचांग->पंचांग_year = bcd2bin(FIELD_GET(CDNS_RTC_CAL_Y, reg))
		    + bcd2bin(FIELD_GET(CDNS_RTC_CAL_C, reg)) * 100 - 1900;
	पंचांग->पंचांग_wday = bcd2bin(FIELD_GET(CDNS_RTC_CAL_DAY, reg)) - 1;

	cdns_rtc_set_enabled(crtc, true);
	वापस 0;
पूर्ण

अटल पूर्णांक cdns_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);
	u32 timr, calr, stsr;
	पूर्णांक ret = -EIO;
	पूर्णांक year = पंचांग->पंचांग_year + 1900;
	पूर्णांक tries;

	cdns_rtc_set_enabled(crtc, false);

	timr = cdns_rtc_समय2reg(पंचांग);

	calr = FIELD_PREP(CDNS_RTC_CAL_D, bin2bcd(पंचांग->पंचांग_mday))
	     | FIELD_PREP(CDNS_RTC_CAL_M, bin2bcd(पंचांग->पंचांग_mon + 1))
	     | FIELD_PREP(CDNS_RTC_CAL_Y, bin2bcd(year % 100))
	     | FIELD_PREP(CDNS_RTC_CAL_C, bin2bcd(year / 100))
	     | FIELD_PREP(CDNS_RTC_CAL_DAY, पंचांग->पंचांग_wday + 1);

	/* Update रेजिस्टरs, check valid flags */
	क्रम (tries = 0; tries < CDNS_RTC_MAX_REGS_TRIES; tries++) अणु
		ग_लिखोl(timr, crtc->regs + CDNS_RTC_TIMR);
		ग_लिखोl(calr, crtc->regs + CDNS_RTC_CALR);
		stsr = पढ़ोl(crtc->regs + CDNS_RTC_STSR);

		अगर ((stsr & CDNS_RTC_STSR_VT_VC) == CDNS_RTC_STSR_VT_VC) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	cdns_rtc_set_enabled(crtc, true);
	वापस ret;
पूर्ण

अटल पूर्णांक cdns_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);

	अगर (enabled) अणु
		ग_लिखोl((CDNS_RTC_AEI_SEC | CDNS_RTC_AEI_MIN | CDNS_RTC_AEI_HOUR
			| CDNS_RTC_AEI_DATE | CDNS_RTC_AEI_MNTH),
		       crtc->regs + CDNS_RTC_AENR);
		ग_लिखोl(CDNS_RTC_AEI_ALRM, crtc->regs + CDNS_RTC_IENR);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, crtc->regs + CDNS_RTC_AENR);
		ग_लिखोl(CDNS_RTC_AEI_ALRM, crtc->regs + CDNS_RTC_IDISR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);
	u32 reg;

	reg = पढ़ोl(crtc->regs + CDNS_RTC_TIMAR);
	cdns_rtc_reg2समय(reg, &alarm->समय);

	reg = पढ़ोl(crtc->regs + CDNS_RTC_CALAR);
	alarm->समय.पंचांग_mday = bcd2bin(FIELD_GET(CDNS_RTC_CAL_D, reg));
	alarm->समय.पंचांग_mon  = bcd2bin(FIELD_GET(CDNS_RTC_CAL_M, reg)) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);
	पूर्णांक ret = -EIO;
	पूर्णांक tries;
	u32 timar, calar, stsr;

	cdns_rtc_alarm_irq_enable(dev, 0);

	timar = cdns_rtc_समय2reg(&alarm->समय);
	calar = FIELD_PREP(CDNS_RTC_CAL_D, bin2bcd(alarm->समय.पंचांग_mday))
	      | FIELD_PREP(CDNS_RTC_CAL_M, bin2bcd(alarm->समय.पंचांग_mon + 1));

	/* Update रेजिस्टरs, check valid alarm flags */
	क्रम (tries = 0; tries < CDNS_RTC_MAX_REGS_TRIES; tries++) अणु
		ग_लिखोl(timar, crtc->regs + CDNS_RTC_TIMAR);
		ग_लिखोl(calar, crtc->regs + CDNS_RTC_CALAR);
		stsr = पढ़ोl(crtc->regs + CDNS_RTC_STSR);

		अगर ((stsr & CDNS_RTC_STSR_VTA_VCA) == CDNS_RTC_STSR_VTA_VCA) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret)
		cdns_rtc_alarm_irq_enable(dev, alarm->enabled);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops cdns_rtc_ops = अणु
	.पढ़ो_समय	= cdns_rtc_पढ़ो_समय,
	.set_समय	= cdns_rtc_set_समय,
	.पढ़ो_alarm	= cdns_rtc_पढ़ो_alarm,
	.set_alarm	= cdns_rtc_set_alarm,
	.alarm_irq_enable = cdns_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक cdns_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_rtc *crtc;
	पूर्णांक ret;
	अचिन्हित दीर्घ ref_clk_freq;

	crtc = devm_kzalloc(&pdev->dev, माप(*crtc), GFP_KERNEL);
	अगर (!crtc)
		वापस -ENOMEM;

	crtc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(crtc->regs))
		वापस PTR_ERR(crtc->regs);

	crtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (crtc->irq < 0)
		वापस -EINVAL;

	crtc->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(crtc->pclk)) अणु
		ret = PTR_ERR(crtc->pclk);
		dev_err(&pdev->dev,
			"Failed to retrieve the peripheral clock, %d\n", ret);
		वापस ret;
	पूर्ण

	crtc->ref_clk = devm_clk_get(&pdev->dev, "ref_clk");
	अगर (IS_ERR(crtc->ref_clk)) अणु
		ret = PTR_ERR(crtc->ref_clk);
		dev_err(&pdev->dev,
			"Failed to retrieve the reference clock, %d\n", ret);
		वापस ret;
	पूर्ण

	crtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(crtc->rtc_dev))
		वापस PTR_ERR(crtc->rtc_dev);

	platक्रमm_set_drvdata(pdev, crtc);

	ret = clk_prepare_enable(crtc->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to enable the peripheral clock, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(crtc->ref_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to enable the reference clock, %d\n", ret);
		जाओ err_disable_pclk;
	पूर्ण

	ref_clk_freq = clk_get_rate(crtc->ref_clk);
	अगर ((ref_clk_freq != 1) && (ref_clk_freq != 100)) अणु
		dev_err(&pdev->dev,
			"Invalid reference clock frequency %lu Hz.\n",
			ref_clk_freq);
		ret = -EINVAL;
		जाओ err_disable_ref_clk;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, crtc->irq,
			       cdns_rtc_irq_handler, 0,
			       dev_name(&pdev->dev), &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to request interrupt for the device, %d\n",
			ret);
		जाओ err_disable_ref_clk;
	पूर्ण

	/* The RTC supports 01.01.1900 - 31.12.2999 */
	crtc->rtc_dev->range_min = स_गढ़ो64(1900,  1,  1,  0,  0,  0);
	crtc->rtc_dev->range_max = स_गढ़ो64(2999, 12, 31, 23, 59, 59);

	crtc->rtc_dev->ops = &cdns_rtc_ops;
	device_init_wakeup(&pdev->dev, true);

	/* Always use 24-hour mode and keep the RTC values */
	ग_लिखोl(0, crtc->regs + CDNS_RTC_HMR);
	ग_लिखोl(CDNS_RTC_KRTCR_KRTC, crtc->regs + CDNS_RTC_KRTCR);

	ret = devm_rtc_रेजिस्टर_device(crtc->rtc_dev);
	अगर (ret)
		जाओ err_disable_wakeup;

	वापस 0;

err_disable_wakeup:
	device_init_wakeup(&pdev->dev, false);

err_disable_ref_clk:
	clk_disable_unprepare(crtc->ref_clk);

err_disable_pclk:
	clk_disable_unprepare(crtc->pclk);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_rtc *crtc = platक्रमm_get_drvdata(pdev);

	cdns_rtc_alarm_irq_enable(&pdev->dev, 0);
	device_init_wakeup(&pdev->dev, 0);

	clk_disable_unprepare(crtc->pclk);
	clk_disable_unprepare(crtc->ref_clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cdns_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(crtc->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा cdns_rtc *crtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(crtc->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cdns_rtc_pm_ops, cdns_rtc_suspend, cdns_rtc_resume);

अटल स्थिर काष्ठा of_device_id cdns_rtc_of_match[] = अणु
	अणु .compatible = "cdns,rtc-r109v3" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_rtc_of_match);

अटल काष्ठा platक्रमm_driver cdns_rtc_driver = अणु
	.driver = अणु
		.name = "cdns-rtc",
		.of_match_table = cdns_rtc_of_match,
		.pm = &cdns_rtc_pm_ops,
	पूर्ण,
	.probe = cdns_rtc_probe,
	.हटाओ = cdns_rtc_हटाओ,
पूर्ण;
module_platक्रमm_driver(cdns_rtc_driver);

MODULE_AUTHOR("Jan Kotas <jank@cadence.com>");
MODULE_DESCRIPTION("Cadence RTC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cdns-rtc");
