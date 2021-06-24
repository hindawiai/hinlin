<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Copyright (c) 2014-2015 MediaTek Inc.
* Author: Tianping.Fang <tianping.fang@mediatek.com>
*/

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/mfd/mt6397/rtc.h>
#समावेश <linux/mod_devicetable.h>

अटल पूर्णांक mtk_rtc_ग_लिखो_trigger(काष्ठा mt6397_rtc *rtc)
अणु
	पूर्णांक ret;
	u32 data;

	ret = regmap_ग_लिखो(rtc->regmap, rtc->addr_base + rtc->data->wrtgr, 1);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(rtc->regmap,
					rtc->addr_base + RTC_BBPU, data,
					!(data & RTC_BBPU_CBUSY),
					MTK_RTC_POLL_DELAY_US,
					MTK_RTC_POLL_TIMEOUT);
	अगर (ret < 0)
		dev_err(rtc->rtc_dev->dev.parent,
			"failed to write WRTGR: %d\n", ret);

	वापस ret;
पूर्ण

अटल irqवापस_t mtk_rtc_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mt6397_rtc *rtc = data;
	u32 irqsta, irqen;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rtc->regmap, rtc->addr_base + RTC_IRQ_STA, &irqsta);
	अगर ((ret >= 0) && (irqsta & RTC_IRQ_STA_AL)) अणु
		rtc_update_irq(rtc->rtc_dev, 1, RTC_IRQF | RTC_AF);
		irqen = irqsta & ~RTC_IRQ_EN_AL;
		mutex_lock(&rtc->lock);
		अगर (regmap_ग_लिखो(rtc->regmap, rtc->addr_base + RTC_IRQ_EN,
				 irqen) == 0)
			mtk_rtc_ग_लिखो_trigger(rtc);
		mutex_unlock(&rtc->lock);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक __mtk_rtc_पढ़ो_समय(काष्ठा mt6397_rtc *rtc,
			       काष्ठा rtc_समय *पंचांग, पूर्णांक *sec)
अणु
	पूर्णांक ret;
	u16 data[RTC_OFFSET_COUNT];

	mutex_lock(&rtc->lock);
	ret = regmap_bulk_पढ़ो(rtc->regmap, rtc->addr_base + RTC_TC_SEC,
			       data, RTC_OFFSET_COUNT);
	अगर (ret < 0)
		जाओ निकास;

	पंचांग->पंचांग_sec = data[RTC_OFFSET_SEC];
	पंचांग->पंचांग_min = data[RTC_OFFSET_MIN];
	पंचांग->पंचांग_hour = data[RTC_OFFSET_HOUR];
	पंचांग->पंचांग_mday = data[RTC_OFFSET_DOM];
	पंचांग->पंचांग_mon = data[RTC_OFFSET_MTH];
	पंचांग->पंचांग_year = data[RTC_OFFSET_YEAR];

	ret = regmap_पढ़ो(rtc->regmap, rtc->addr_base + RTC_TC_SEC, sec);
निकास:
	mutex_unlock(&rtc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	समय64_t समय;
	काष्ठा mt6397_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक days, sec, ret;

	करो अणु
		ret = __mtk_rtc_पढ़ो_समय(rtc, पंचांग, &sec);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण जबतक (sec < पंचांग->पंचांग_sec);

	/* HW रेजिस्टर use 7 bits to store year data, minus
	 * RTC_MIN_YEAR_OFFSET beक्रमe ग_लिखो year data to रेजिस्टर, and plus
	 * RTC_MIN_YEAR_OFFSET back after पढ़ो year from रेजिस्टर
	 */
	पंचांग->पंचांग_year += RTC_MIN_YEAR_OFFSET;

	/* HW रेजिस्टर start mon from one, but पंचांग_mon start from zero. */
	पंचांग->पंचांग_mon--;
	समय = rtc_पंचांग_to_समय64(पंचांग);

	/* rtc_पंचांग_to_समय64 covert Gregorian date to seconds since
	 * 01-01-1970 00:00:00, and this date is Thursday.
	 */
	days = भाग_s64(समय, 86400);
	पंचांग->पंचांग_wday = (days + 4) % 7;

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mt6397_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक ret;
	u16 data[RTC_OFFSET_COUNT];

	पंचांग->पंचांग_year -= RTC_MIN_YEAR_OFFSET;
	पंचांग->पंचांग_mon++;

	data[RTC_OFFSET_SEC] = पंचांग->पंचांग_sec;
	data[RTC_OFFSET_MIN] = पंचांग->पंचांग_min;
	data[RTC_OFFSET_HOUR] = पंचांग->पंचांग_hour;
	data[RTC_OFFSET_DOM] = पंचांग->पंचांग_mday;
	data[RTC_OFFSET_MTH] = पंचांग->पंचांग_mon;
	data[RTC_OFFSET_YEAR] = पंचांग->पंचांग_year;

	mutex_lock(&rtc->lock);
	ret = regmap_bulk_ग_लिखो(rtc->regmap, rtc->addr_base + RTC_TC_SEC,
				data, RTC_OFFSET_COUNT);
	अगर (ret < 0)
		जाओ निकास;

	/* Time रेजिस्टर ग_लिखो to hardware after call trigger function */
	ret = mtk_rtc_ग_लिखो_trigger(rtc);

निकास:
	mutex_unlock(&rtc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा rtc_समय *पंचांग = &alm->समय;
	काष्ठा mt6397_rtc *rtc = dev_get_drvdata(dev);
	u32 irqen, pdn2;
	पूर्णांक ret;
	u16 data[RTC_OFFSET_COUNT];

	mutex_lock(&rtc->lock);
	ret = regmap_पढ़ो(rtc->regmap, rtc->addr_base + RTC_IRQ_EN, &irqen);
	अगर (ret < 0)
		जाओ err_निकास;
	ret = regmap_पढ़ो(rtc->regmap, rtc->addr_base + RTC_PDN2, &pdn2);
	अगर (ret < 0)
		जाओ err_निकास;

	ret = regmap_bulk_पढ़ो(rtc->regmap, rtc->addr_base + RTC_AL_SEC,
			       data, RTC_OFFSET_COUNT);
	अगर (ret < 0)
		जाओ err_निकास;

	alm->enabled = !!(irqen & RTC_IRQ_EN_AL);
	alm->pending = !!(pdn2 & RTC_PDN2_PWRON_ALARM);
	mutex_unlock(&rtc->lock);

	पंचांग->पंचांग_sec = data[RTC_OFFSET_SEC] & RTC_AL_SEC_MASK;
	पंचांग->पंचांग_min = data[RTC_OFFSET_MIN] & RTC_AL_MIN_MASK;
	पंचांग->पंचांग_hour = data[RTC_OFFSET_HOUR] & RTC_AL_HOU_MASK;
	पंचांग->पंचांग_mday = data[RTC_OFFSET_DOM] & RTC_AL_DOM_MASK;
	पंचांग->पंचांग_mon = data[RTC_OFFSET_MTH] & RTC_AL_MTH_MASK;
	पंचांग->पंचांग_year = data[RTC_OFFSET_YEAR] & RTC_AL_YEA_MASK;

	पंचांग->पंचांग_year += RTC_MIN_YEAR_OFFSET;
	पंचांग->पंचांग_mon--;

	वापस 0;
err_निकास:
	mutex_unlock(&rtc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा rtc_समय *पंचांग = &alm->समय;
	काष्ठा mt6397_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक ret;
	u16 data[RTC_OFFSET_COUNT];

	पंचांग->पंचांग_year -= RTC_MIN_YEAR_OFFSET;
	पंचांग->पंचांग_mon++;

	mutex_lock(&rtc->lock);
	ret = regmap_bulk_पढ़ो(rtc->regmap, rtc->addr_base + RTC_AL_SEC,
			       data, RTC_OFFSET_COUNT);
	अगर (ret < 0)
		जाओ निकास;

	data[RTC_OFFSET_SEC] = ((data[RTC_OFFSET_SEC] & ~(RTC_AL_SEC_MASK)) |
				(पंचांग->पंचांग_sec & RTC_AL_SEC_MASK));
	data[RTC_OFFSET_MIN] = ((data[RTC_OFFSET_MIN] & ~(RTC_AL_MIN_MASK)) |
				(पंचांग->पंचांग_min & RTC_AL_MIN_MASK));
	data[RTC_OFFSET_HOUR] = ((data[RTC_OFFSET_HOUR] & ~(RTC_AL_HOU_MASK)) |
				(पंचांग->पंचांग_hour & RTC_AL_HOU_MASK));
	data[RTC_OFFSET_DOM] = ((data[RTC_OFFSET_DOM] & ~(RTC_AL_DOM_MASK)) |
				(पंचांग->पंचांग_mday & RTC_AL_DOM_MASK));
	data[RTC_OFFSET_MTH] = ((data[RTC_OFFSET_MTH] & ~(RTC_AL_MTH_MASK)) |
				(पंचांग->पंचांग_mon & RTC_AL_MTH_MASK));
	data[RTC_OFFSET_YEAR] = ((data[RTC_OFFSET_YEAR] & ~(RTC_AL_YEA_MASK)) |
				(पंचांग->पंचांग_year & RTC_AL_YEA_MASK));

	अगर (alm->enabled) अणु
		ret = regmap_bulk_ग_लिखो(rtc->regmap,
					rtc->addr_base + RTC_AL_SEC,
					data, RTC_OFFSET_COUNT);
		अगर (ret < 0)
			जाओ निकास;
		ret = regmap_ग_लिखो(rtc->regmap, rtc->addr_base + RTC_AL_MASK,
				   RTC_AL_MASK_DOW);
		अगर (ret < 0)
			जाओ निकास;
		ret = regmap_update_bits(rtc->regmap,
					 rtc->addr_base + RTC_IRQ_EN,
					 RTC_IRQ_EN_ONESHOT_AL,
					 RTC_IRQ_EN_ONESHOT_AL);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(rtc->regmap,
					 rtc->addr_base + RTC_IRQ_EN,
					 RTC_IRQ_EN_ONESHOT_AL, 0);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	/* All alarm समय रेजिस्टर ग_लिखो to hardware after calling
	 * mtk_rtc_ग_लिखो_trigger. This can aव्योम race condition अगर alarm
	 * occur happen during writing alarm समय रेजिस्टर.
	 */
	ret = mtk_rtc_ग_लिखो_trigger(rtc);
निकास:
	mutex_unlock(&rtc->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mtk_rtc_ops = अणु
	.पढ़ो_समय  = mtk_rtc_पढ़ो_समय,
	.set_समय   = mtk_rtc_set_समय,
	.पढ़ो_alarm = mtk_rtc_पढ़ो_alarm,
	.set_alarm  = mtk_rtc_set_alarm,
पूर्ण;

अटल पूर्णांक mtk_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा mt6397_chip *mt6397_chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा mt6397_rtc *rtc;
	पूर्णांक ret;

	rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा mt6397_rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->addr_base = res->start;

	rtc->data = of_device_get_match_data(&pdev->dev);

	rtc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rtc->irq < 0)
		वापस rtc->irq;

	rtc->regmap = mt6397_chip->regmap;
	mutex_init(&rtc->lock);

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq, शून्य,
					mtk_rtc_irq_handler_thपढ़ो,
					IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
					"mt6397-rtc", rtc);

	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			rtc->irq, ret);
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, 1);

	rtc->rtc_dev->ops = &mtk_rtc_ops;

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mt6397_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mt6397_rtc *rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(rtc->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक mt6397_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा mt6397_rtc *rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(rtc->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mt6397_pm_ops, mt6397_rtc_suspend,
			mt6397_rtc_resume);

अटल स्थिर काष्ठा mtk_rtc_data mt6358_rtc_data = अणु
	.wrtgr = RTC_WRTGR_MT6358,
पूर्ण;

अटल स्थिर काष्ठा mtk_rtc_data mt6397_rtc_data = अणु
	.wrtgr = RTC_WRTGR_MT6397,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mt6397_rtc_of_match[] = अणु
	अणु .compatible = "mediatek,mt6323-rtc", .data = &mt6397_rtc_data पूर्ण,
	अणु .compatible = "mediatek,mt6358-rtc", .data = &mt6358_rtc_data पूर्ण,
	अणु .compatible = "mediatek,mt6397-rtc", .data = &mt6397_rtc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6397_rtc_of_match);

अटल काष्ठा platक्रमm_driver mtk_rtc_driver = अणु
	.driver = अणु
		.name = "mt6397-rtc",
		.of_match_table = mt6397_rtc_of_match,
		.pm = &mt6397_pm_ops,
	पूर्ण,
	.probe	= mtk_rtc_probe,
पूर्ण;

module_platक्रमm_driver(mtk_rtc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Tianping Fang <tianping.fang@mediatek.com>");
MODULE_DESCRIPTION("RTC Driver for MediaTek MT6397 PMIC");
