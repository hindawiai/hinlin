<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RTC driver क्रम NXP LPC178x/18xx/43xx Real-Time Clock (RTC)
 *
 * Copyright (C) 2011 NXP Semiconductors
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

/* LPC24xx RTC रेजिस्टर offsets and bits */
#घोषणा LPC24XX_ILR		0x00
#घोषणा  LPC24XX_RTCCIF		BIT(0)
#घोषणा  LPC24XX_RTCALF		BIT(1)
#घोषणा LPC24XX_CTC		0x04
#घोषणा LPC24XX_CCR		0x08
#घोषणा  LPC24XX_CLKEN		BIT(0)
#घोषणा  LPC178X_CCALEN		BIT(4)
#घोषणा LPC24XX_CIIR		0x0c
#घोषणा LPC24XX_AMR		0x10
#घोषणा  LPC24XX_ALARM_DISABLE	0xff
#घोषणा LPC24XX_CTIME0		0x14
#घोषणा LPC24XX_CTIME1		0x18
#घोषणा LPC24XX_CTIME2		0x1c
#घोषणा LPC24XX_SEC		0x20
#घोषणा LPC24XX_MIN		0x24
#घोषणा LPC24XX_HOUR		0x28
#घोषणा LPC24XX_DOM		0x2c
#घोषणा LPC24XX_DOW		0x30
#घोषणा LPC24XX_DOY		0x34
#घोषणा LPC24XX_MONTH		0x38
#घोषणा LPC24XX_YEAR		0x3c
#घोषणा LPC24XX_ALSEC		0x60
#घोषणा LPC24XX_ALMIN		0x64
#घोषणा LPC24XX_ALHOUR		0x68
#घोषणा LPC24XX_ALDOM		0x6c
#घोषणा LPC24XX_ALDOW		0x70
#घोषणा LPC24XX_ALDOY		0x74
#घोषणा LPC24XX_ALMON		0x78
#घोषणा LPC24XX_ALYEAR		0x7c

/* Macros to पढ़ो fields in consolidated समय (CT) रेजिस्टरs */
#घोषणा CT0_SECS(x)		(((x) >> 0)  & 0x3f)
#घोषणा CT0_MINS(x)		(((x) >> 8)  & 0x3f)
#घोषणा CT0_HOURS(x)		(((x) >> 16) & 0x1f)
#घोषणा CT0_DOW(x)		(((x) >> 24) & 0x07)
#घोषणा CT1_DOM(x)		(((x) >> 0)  & 0x1f)
#घोषणा CT1_MONTH(x)		(((x) >> 8)  & 0x0f)
#घोषणा CT1_YEAR(x)		(((x) >> 16) & 0xfff)
#घोषणा CT2_DOY(x)		(((x) >> 0)  & 0xfff)

#घोषणा rtc_पढ़ोl(dev, reg)		पढ़ोl((dev)->rtc_base + (reg))
#घोषणा rtc_ग_लिखोl(dev, reg, val)	ग_लिखोl((val), (dev)->rtc_base + (reg))

काष्ठा lpc24xx_rtc अणु
	व्योम __iomem *rtc_base;
	काष्ठा rtc_device *rtc;
	काष्ठा clk *clk_rtc;
	काष्ठा clk *clk_reg;
पूर्ण;

अटल पूर्णांक lpc24xx_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा lpc24xx_rtc *rtc = dev_get_drvdata(dev);

	/* Disable RTC during update */
	rtc_ग_लिखोl(rtc, LPC24XX_CCR, LPC178X_CCALEN);

	rtc_ग_लिखोl(rtc, LPC24XX_SEC,	पंचांग->पंचांग_sec);
	rtc_ग_लिखोl(rtc, LPC24XX_MIN,	पंचांग->पंचांग_min);
	rtc_ग_लिखोl(rtc, LPC24XX_HOUR,	पंचांग->पंचांग_hour);
	rtc_ग_लिखोl(rtc, LPC24XX_DOW,	पंचांग->पंचांग_wday);
	rtc_ग_लिखोl(rtc, LPC24XX_DOM,	पंचांग->पंचांग_mday);
	rtc_ग_लिखोl(rtc, LPC24XX_DOY,	पंचांग->पंचांग_yday);
	rtc_ग_लिखोl(rtc, LPC24XX_MONTH,	पंचांग->पंचांग_mon);
	rtc_ग_लिखोl(rtc, LPC24XX_YEAR,	पंचांग->पंचांग_year);

	rtc_ग_लिखोl(rtc, LPC24XX_CCR, LPC24XX_CLKEN | LPC178X_CCALEN);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc24xx_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा lpc24xx_rtc *rtc = dev_get_drvdata(dev);
	u32 ct0, ct1, ct2;

	ct0 = rtc_पढ़ोl(rtc, LPC24XX_CTIME0);
	ct1 = rtc_पढ़ोl(rtc, LPC24XX_CTIME1);
	ct2 = rtc_पढ़ोl(rtc, LPC24XX_CTIME2);

	पंचांग->पंचांग_sec  = CT0_SECS(ct0);
	पंचांग->पंचांग_min  = CT0_MINS(ct0);
	पंचांग->पंचांग_hour = CT0_HOURS(ct0);
	पंचांग->पंचांग_wday = CT0_DOW(ct0);
	पंचांग->पंचांग_mon  = CT1_MONTH(ct1);
	पंचांग->पंचांग_mday = CT1_DOM(ct1);
	पंचांग->पंचांग_year = CT1_YEAR(ct1);
	पंचांग->पंचांग_yday = CT2_DOY(ct2);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc24xx_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा lpc24xx_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &wkalrm->समय;

	पंचांग->पंचांग_sec  = rtc_पढ़ोl(rtc, LPC24XX_ALSEC);
	पंचांग->पंचांग_min  = rtc_पढ़ोl(rtc, LPC24XX_ALMIN);
	पंचांग->पंचांग_hour = rtc_पढ़ोl(rtc, LPC24XX_ALHOUR);
	पंचांग->पंचांग_mday = rtc_पढ़ोl(rtc, LPC24XX_ALDOM);
	पंचांग->पंचांग_wday = rtc_पढ़ोl(rtc, LPC24XX_ALDOW);
	पंचांग->पंचांग_yday = rtc_पढ़ोl(rtc, LPC24XX_ALDOY);
	पंचांग->पंचांग_mon  = rtc_पढ़ोl(rtc, LPC24XX_ALMON);
	पंचांग->पंचांग_year = rtc_पढ़ोl(rtc, LPC24XX_ALYEAR);

	wkalrm->enabled = rtc_पढ़ोl(rtc, LPC24XX_AMR) == 0;
	wkalrm->pending = !!(rtc_पढ़ोl(rtc, LPC24XX_ILR) & LPC24XX_RTCCIF);

	वापस rtc_valid_पंचांग(&wkalrm->समय);
पूर्ण

अटल पूर्णांक lpc24xx_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा lpc24xx_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा rtc_समय *पंचांग = &wkalrm->समय;

	/* Disable alarm irq during update */
	rtc_ग_लिखोl(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);

	rtc_ग_लिखोl(rtc, LPC24XX_ALSEC,  पंचांग->पंचांग_sec);
	rtc_ग_लिखोl(rtc, LPC24XX_ALMIN,  पंचांग->पंचांग_min);
	rtc_ग_लिखोl(rtc, LPC24XX_ALHOUR, पंचांग->पंचांग_hour);
	rtc_ग_लिखोl(rtc, LPC24XX_ALDOM,  पंचांग->पंचांग_mday);
	rtc_ग_लिखोl(rtc, LPC24XX_ALDOW,  पंचांग->पंचांग_wday);
	rtc_ग_लिखोl(rtc, LPC24XX_ALDOY,  पंचांग->पंचांग_yday);
	rtc_ग_लिखोl(rtc, LPC24XX_ALMON,  पंचांग->पंचांग_mon);
	rtc_ग_लिखोl(rtc, LPC24XX_ALYEAR, पंचांग->पंचांग_year);

	अगर (wkalrm->enabled)
		rtc_ग_लिखोl(rtc, LPC24XX_AMR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc24xx_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा lpc24xx_rtc *rtc = dev_get_drvdata(dev);

	अगर (enable)
		rtc_ग_लिखोl(rtc, LPC24XX_AMR, 0);
	अन्यथा
		rtc_ग_लिखोl(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);

	वापस 0;
पूर्ण

अटल irqवापस_t lpc24xx_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ events = RTC_IRQF;
	काष्ठा lpc24xx_rtc *rtc = data;
	u32 rtc_iir;

	/* Check पूर्णांकerrupt cause */
	rtc_iir = rtc_पढ़ोl(rtc, LPC24XX_ILR);
	अगर (rtc_iir & LPC24XX_RTCALF) अणु
		events |= RTC_AF;
		rtc_ग_लिखोl(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);
	पूर्ण

	/* Clear पूर्णांकerrupt status and report event */
	rtc_ग_लिखोl(rtc, LPC24XX_ILR, rtc_iir);
	rtc_update_irq(rtc->rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops lpc24xx_rtc_ops = अणु
	.पढ़ो_समय		= lpc24xx_rtc_पढ़ो_समय,
	.set_समय		= lpc24xx_rtc_set_समय,
	.पढ़ो_alarm		= lpc24xx_rtc_पढ़ो_alarm,
	.set_alarm		= lpc24xx_rtc_set_alarm,
	.alarm_irq_enable	= lpc24xx_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक lpc24xx_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc24xx_rtc *rtc;
	पूर्णांक irq, ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->rtc_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->rtc_base))
		वापस PTR_ERR(rtc->rtc_base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	rtc->clk_rtc = devm_clk_get(&pdev->dev, "rtc");
	अगर (IS_ERR(rtc->clk_rtc)) अणु
		dev_err(&pdev->dev, "error getting rtc clock\n");
		वापस PTR_ERR(rtc->clk_rtc);
	पूर्ण

	rtc->clk_reg = devm_clk_get(&pdev->dev, "reg");
	अगर (IS_ERR(rtc->clk_reg)) अणु
		dev_err(&pdev->dev, "error getting reg clock\n");
		वापस PTR_ERR(rtc->clk_reg);
	पूर्ण

	ret = clk_prepare_enable(rtc->clk_rtc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable rtc clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(rtc->clk_reg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable reg clock\n");
		जाओ disable_rtc_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rtc);

	/* Clear any pending पूर्णांकerrupts */
	rtc_ग_लिखोl(rtc, LPC24XX_ILR, LPC24XX_RTCCIF | LPC24XX_RTCALF);

	/* Enable RTC count */
	rtc_ग_लिखोl(rtc, LPC24XX_CCR, LPC24XX_CLKEN | LPC178X_CCALEN);

	ret = devm_request_irq(&pdev->dev, irq, lpc24xx_rtc_पूर्णांकerrupt, 0,
			       pdev->name, rtc);
	अगर (ret < 0) अणु
		dev_warn(&pdev->dev, "can't request interrupt\n");
		जाओ disable_clks;
	पूर्ण

	rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "lpc24xx-rtc",
					    &lpc24xx_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc->rtc)) अणु
		dev_err(&pdev->dev, "can't register rtc device\n");
		ret = PTR_ERR(rtc->rtc);
		जाओ disable_clks;
	पूर्ण

	वापस 0;

disable_clks:
	clk_disable_unprepare(rtc->clk_reg);
disable_rtc_clk:
	clk_disable_unprepare(rtc->clk_rtc);
	वापस ret;
पूर्ण

अटल पूर्णांक lpc24xx_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc24xx_rtc *rtc = platक्रमm_get_drvdata(pdev);

	/* Ensure all पूर्णांकerrupt sources are masked */
	rtc_ग_लिखोl(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);
	rtc_ग_लिखोl(rtc, LPC24XX_CIIR, 0);

	rtc_ग_लिखोl(rtc, LPC24XX_CCR, LPC178X_CCALEN);

	clk_disable_unprepare(rtc->clk_rtc);
	clk_disable_unprepare(rtc->clk_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc24xx_rtc_match[] = अणु
	अणु .compatible = "nxp,lpc1788-rtc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc24xx_rtc_match);

अटल काष्ठा platक्रमm_driver lpc24xx_rtc_driver = अणु
	.probe	= lpc24xx_rtc_probe,
	.हटाओ	= lpc24xx_rtc_हटाओ,
	.driver	= अणु
		.name = "lpc24xx-rtc",
		.of_match_table	= lpc24xx_rtc_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc24xx_rtc_driver);

MODULE_AUTHOR("Kevin Wells <wellsk40@gmail.com>");
MODULE_DESCRIPTION("RTC driver for the LPC178x/18xx/408x/43xx SoCs");
MODULE_LICENSE("GPL");
