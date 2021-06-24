<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2015 IBM Corp.

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/पन.स>

काष्ठा aspeed_rtc अणु
	काष्ठा rtc_device *rtc_dev;
	व्योम __iomem *base;
पूर्ण;

#घोषणा RTC_TIME	0x00
#घोषणा RTC_YEAR	0x04
#घोषणा RTC_CTRL	0x10

#घोषणा RTC_UNLOCK	BIT(1)
#घोषणा RTC_ENABLE	BIT(0)

अटल पूर्णांक aspeed_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा aspeed_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक cent, year;
	u32 reg1, reg2;

	अगर (!(पढ़ोl(rtc->base + RTC_CTRL) & RTC_ENABLE)) अणु
		dev_dbg(dev, "%s failing as rtc disabled\n", __func__);
		वापस -EINVAL;
	पूर्ण

	करो अणु
		reg2 = पढ़ोl(rtc->base + RTC_YEAR);
		reg1 = पढ़ोl(rtc->base + RTC_TIME);
	पूर्ण जबतक (reg2 != पढ़ोl(rtc->base + RTC_YEAR));

	पंचांग->पंचांग_mday = (reg1 >> 24) & 0x1f;
	पंचांग->पंचांग_hour = (reg1 >> 16) & 0x1f;
	पंचांग->पंचांग_min = (reg1 >> 8) & 0x3f;
	पंचांग->पंचांग_sec = (reg1 >> 0) & 0x3f;

	cent = (reg2 >> 16) & 0x1f;
	year = (reg2 >> 8) & 0x7f;
	पंचांग->पंचांग_mon = ((reg2 >>  0) & 0x0f) - 1;
	पंचांग->पंचांग_year = year + (cent * 100) - 1900;

	dev_dbg(dev, "%s %ptR", __func__, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा aspeed_rtc *rtc = dev_get_drvdata(dev);
	u32 reg1, reg2, ctrl;
	पूर्णांक year, cent;

	cent = (पंचांग->पंचांग_year + 1900) / 100;
	year = पंचांग->पंचांग_year % 100;

	reg1 = (पंचांग->पंचांग_mday << 24) | (पंचांग->पंचांग_hour << 16) | (पंचांग->पंचांग_min << 8) |
		पंचांग->पंचांग_sec;

	reg2 = ((cent & 0x1f) << 16) | ((year & 0x7f) << 8) |
		((पंचांग->पंचांग_mon + 1) & 0xf);

	ctrl = पढ़ोl(rtc->base + RTC_CTRL);
	ग_लिखोl(ctrl | RTC_UNLOCK, rtc->base + RTC_CTRL);

	ग_लिखोl(reg1, rtc->base + RTC_TIME);
	ग_लिखोl(reg2, rtc->base + RTC_YEAR);

	/* Re-lock and ensure enable is set now that a समय is programmed */
	ग_लिखोl(ctrl | RTC_ENABLE, rtc->base + RTC_CTRL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops aspeed_rtc_ops = अणु
	.पढ़ो_समय = aspeed_rtc_पढ़ो_समय,
	.set_समय = aspeed_rtc_set_समय,
पूर्ण;

अटल पूर्णांक aspeed_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_rtc *rtc;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rtc->base))
		वापस PTR_ERR(rtc->base);

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc_dev->ops = &aspeed_rtc_ops;
	rtc->rtc_dev->range_min = RTC_TIMESTAMP_BEGIN_1900;
	rtc->rtc_dev->range_max = 38814989399LL; /* 3199-12-31 23:59:59 */

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_rtc_match[] = अणु
	अणु .compatible = "aspeed,ast2400-rtc", पूर्ण,
	अणु .compatible = "aspeed,ast2500-rtc", पूर्ण,
	अणु .compatible = "aspeed,ast2600-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_rtc_match);

अटल काष्ठा platक्रमm_driver aspeed_rtc_driver = अणु
	.driver = अणु
		.name = "aspeed-rtc",
		.of_match_table = of_match_ptr(aspeed_rtc_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(aspeed_rtc_driver, aspeed_rtc_probe);

MODULE_DESCRIPTION("ASPEED RTC driver");
MODULE_AUTHOR("Joel Stanley <joel@jms.id.au>");
MODULE_LICENSE("GPL");
