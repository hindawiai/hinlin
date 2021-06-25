<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Faraday Technology FTRTC010 driver
 *
 *  Copyright (C) 2009 Janos Laube <janos.dev@gmail.com>
 *
 * Original code क्रम older kernel 2.6.15 are from Stormlinksemi
 * first update from Janos Laube क्रम > 2.6.29 kernels
 *
 * checkpatch fixes and usage of rtc-lib code
 * Hans Ulli Kroll <ulli.kroll@googlemail.com>
 */

#समावेश <linux/rtc.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/clk.h>

#घोषणा DRV_NAME        "rtc-ftrtc010"

MODULE_AUTHOR("Hans Ulli Kroll <ulli.kroll@googlemail.com>");
MODULE_DESCRIPTION("RTC driver for Gemini SoC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);

काष्ठा ftrtc010_rtc अणु
	काष्ठा rtc_device	*rtc_dev;
	व्योम __iomem		*rtc_base;
	पूर्णांक			rtc_irq;
	काष्ठा clk		*pclk;
	काष्ठा clk		*extclk;
पूर्ण;

क्रमागत ftrtc010_rtc_offsets अणु
	FTRTC010_RTC_SECOND		= 0x00,
	FTRTC010_RTC_MINUTE		= 0x04,
	FTRTC010_RTC_HOUR		= 0x08,
	FTRTC010_RTC_DAYS		= 0x0C,
	FTRTC010_RTC_ALARM_SECOND	= 0x10,
	FTRTC010_RTC_ALARM_MINUTE	= 0x14,
	FTRTC010_RTC_ALARM_HOUR		= 0x18,
	FTRTC010_RTC_RECORD		= 0x1C,
	FTRTC010_RTC_CR			= 0x20,
पूर्ण;

अटल irqवापस_t ftrtc010_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Looks like the RTC in the Gemini SoC is (totaly) broken
 * We can't पढ़ो/ग_लिखो directly the समय from RTC रेजिस्टरs.
 * We must करो some "offset" calculation to get the real समय
 *
 * This FIX works pretty fine and Stormlinksemi aka Cortina-Networks करोes
 * the same thing, without the rtc-lib.c calls.
 */

अटल पूर्णांक ftrtc010_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ftrtc010_rtc *rtc = dev_get_drvdata(dev);

	u32 days, hour, min, sec, offset;
	समयu64_t समय;

	sec  = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_SECOND);
	min  = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_MINUTE);
	hour = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_HOUR);
	days = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_DAYS);
	offset = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_RECORD);

	समय = offset + days * 86400 + hour * 3600 + min * 60 + sec;

	rtc_समय64_to_पंचांग(समय, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक ftrtc010_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ftrtc010_rtc *rtc = dev_get_drvdata(dev);
	u32 sec, min, hour, day, offset;
	समयu64_t समय;

	समय = rtc_पंचांग_to_समय64(पंचांग);

	sec = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_SECOND);
	min = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_MINUTE);
	hour = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_HOUR);
	day = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_DAYS);

	offset = समय - (day * 86400 + hour * 3600 + min * 60 + sec);

	ग_लिखोl(offset, rtc->rtc_base + FTRTC010_RTC_RECORD);
	ग_लिखोl(0x01, rtc->rtc_base + FTRTC010_RTC_CR);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ftrtc010_rtc_ops = अणु
	.पढ़ो_समय     = ftrtc010_rtc_पढ़ो_समय,
	.set_समय      = ftrtc010_rtc_set_समय,
पूर्ण;

अटल पूर्णांक ftrtc010_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 days, hour, min, sec;
	काष्ठा ftrtc010_rtc *rtc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (unlikely(!rtc))
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, rtc);

	rtc->pclk = devm_clk_get(dev, "PCLK");
	अगर (IS_ERR(rtc->pclk)) अणु
		dev_err(dev, "could not get PCLK\n");
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(rtc->pclk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable PCLK\n");
			वापस ret;
		पूर्ण
	पूर्ण
	rtc->extclk = devm_clk_get(dev, "EXTCLK");
	अगर (IS_ERR(rtc->extclk)) अणु
		dev_err(dev, "could not get EXTCLK\n");
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(rtc->extclk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable EXTCLK\n");
			वापस ret;
		पूर्ण
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res)
		वापस -ENODEV;

	rtc->rtc_irq = res->start;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	rtc->rtc_base = devm_ioremap(dev, res->start,
				     resource_size(res));
	अगर (!rtc->rtc_base)
		वापस -ENOMEM;

	rtc->rtc_dev = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	rtc->rtc_dev->ops = &ftrtc010_rtc_ops;

	sec  = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_SECOND);
	min  = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_MINUTE);
	hour = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_HOUR);
	days = पढ़ोl(rtc->rtc_base + FTRTC010_RTC_DAYS);

	rtc->rtc_dev->range_min = (u64)days * 86400 + hour * 3600 +
				  min * 60 + sec;
	rtc->rtc_dev->range_max = U32_MAX + rtc->rtc_dev->range_min;

	ret = devm_request_irq(dev, rtc->rtc_irq, ftrtc010_rtc_पूर्णांकerrupt,
			       IRQF_SHARED, pdev->name, dev);
	अगर (unlikely(ret))
		वापस ret;

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
पूर्ण

अटल पूर्णांक ftrtc010_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ftrtc010_rtc *rtc = platक्रमm_get_drvdata(pdev);

	अगर (!IS_ERR(rtc->extclk))
		clk_disable_unprepare(rtc->extclk);
	अगर (!IS_ERR(rtc->pclk))
		clk_disable_unprepare(rtc->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ftrtc010_rtc_dt_match[] = अणु
	अणु .compatible = "cortina,gemini-rtc" पूर्ण,
	अणु .compatible = "faraday,ftrtc010" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ftrtc010_rtc_dt_match);

अटल काष्ठा platक्रमm_driver ftrtc010_rtc_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = ftrtc010_rtc_dt_match,
	पूर्ण,
	.probe		= ftrtc010_rtc_probe,
	.हटाओ		= ftrtc010_rtc_हटाओ,
पूर्ण;

module_platक्रमm_driver_probe(ftrtc010_rtc_driver, ftrtc010_rtc_probe);
