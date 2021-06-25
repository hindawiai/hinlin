<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - rtc driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

/* रेजिस्टर address */
#घोषणा LP8788_INTEN_3			0x05
#घोषणा LP8788_RTC_UNLOCK		0x64
#घोषणा LP8788_RTC_SEC			0x70
#घोषणा LP8788_ALM1_SEC			0x77
#घोषणा LP8788_ALM1_EN			0x7D
#घोषणा LP8788_ALM2_SEC			0x7E
#घोषणा LP8788_ALM2_EN			0x84

/* mask/shअगरt bits */
#घोषणा LP8788_INT_RTC_ALM1_M		BIT(1)	/* Addr 05h */
#घोषणा LP8788_INT_RTC_ALM1_S		1
#घोषणा LP8788_INT_RTC_ALM2_M		BIT(2)	/* Addr 05h */
#घोषणा LP8788_INT_RTC_ALM2_S		2
#घोषणा LP8788_ALM_EN_M			BIT(7)	/* Addr 7Dh or 84h */
#घोषणा LP8788_ALM_EN_S			7

#घोषणा DEFAULT_ALARM_SEL		LP8788_ALARM_1
#घोषणा LP8788_MONTH_OFFSET		1
#घोषणा LP8788_BASE_YEAR		2000
#घोषणा MAX_WDAY_BITS			7
#घोषणा LP8788_WDAY_SET			1
#घोषणा RTC_UNLOCK			0x1
#घोषणा RTC_LATCH			0x2
#घोषणा ALARM_IRQ_FLAG			(RTC_IRQF | RTC_AF)

क्रमागत lp8788_समय अणु
	LPTIME_SEC,
	LPTIME_MIN,
	LPTIME_HOUR,
	LPTIME_MDAY,
	LPTIME_MON,
	LPTIME_YEAR,
	LPTIME_WDAY,
	LPTIME_MAX,
पूर्ण;

काष्ठा lp8788_rtc अणु
	काष्ठा lp8788 *lp;
	काष्ठा rtc_device *rdev;
	क्रमागत lp8788_alarm_sel alarm;
	पूर्णांक irq;
पूर्ण;

अटल स्थिर u8 addr_alarm_sec[LP8788_ALARM_MAX] = अणु
	LP8788_ALM1_SEC,
	LP8788_ALM2_SEC,
पूर्ण;

अटल स्थिर u8 addr_alarm_en[LP8788_ALARM_MAX] = अणु
	LP8788_ALM1_EN,
	LP8788_ALM2_EN,
पूर्ण;

अटल स्थिर u8 mask_alarm_en[LP8788_ALARM_MAX] = अणु
	LP8788_INT_RTC_ALM1_M,
	LP8788_INT_RTC_ALM2_M,
पूर्ण;

अटल स्थिर u8 shअगरt_alarm_en[LP8788_ALARM_MAX] = अणु
	LP8788_INT_RTC_ALM1_S,
	LP8788_INT_RTC_ALM2_S,
पूर्ण;

अटल पूर्णांक _to_पंचांग_wday(u8 lp8788_wday)
अणु
	पूर्णांक i;

	अगर (lp8788_wday == 0)
		वापस 0;

	/* lookup defined weekday from पढ़ो रेजिस्टर value */
	क्रम (i = 0; i < MAX_WDAY_BITS; i++) अणु
		अगर ((lp8788_wday >> i) == LP8788_WDAY_SET)
			अवरोध;
	पूर्ण

	वापस i + 1;
पूर्ण

अटल अंतरभूत पूर्णांक _to_lp8788_wday(पूर्णांक पंचांग_wday)
अणु
	वापस LP8788_WDAY_SET << (पंचांग_wday - 1);
पूर्ण

अटल व्योम lp8788_rtc_unlock(काष्ठा lp8788 *lp)
अणु
	lp8788_ग_लिखो_byte(lp, LP8788_RTC_UNLOCK, RTC_UNLOCK);
	lp8788_ग_लिखो_byte(lp, LP8788_RTC_UNLOCK, RTC_LATCH);
पूर्ण

अटल पूर्णांक lp8788_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा lp8788_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा lp8788 *lp = rtc->lp;
	u8 data[LPTIME_MAX];
	पूर्णांक ret;

	lp8788_rtc_unlock(lp);

	ret = lp8788_पढ़ो_multi_bytes(lp, LP8788_RTC_SEC, data,	LPTIME_MAX);
	अगर (ret)
		वापस ret;

	पंचांग->पंचांग_sec  = data[LPTIME_SEC];
	पंचांग->पंचांग_min  = data[LPTIME_MIN];
	पंचांग->पंचांग_hour = data[LPTIME_HOUR];
	पंचांग->पंचांग_mday = data[LPTIME_MDAY];
	पंचांग->पंचांग_mon  = data[LPTIME_MON] - LP8788_MONTH_OFFSET;
	पंचांग->पंचांग_year = data[LPTIME_YEAR] + LP8788_BASE_YEAR - 1900;
	पंचांग->पंचांग_wday = _to_पंचांग_wday(data[LPTIME_WDAY]);

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा lp8788_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा lp8788 *lp = rtc->lp;
	u8 data[LPTIME_MAX - 1];
	पूर्णांक ret, i, year;

	year = पंचांग->पंचांग_year + 1900 - LP8788_BASE_YEAR;
	अगर (year < 0) अणु
		dev_err(lp->dev, "invalid year: %d\n", year);
		वापस -EINVAL;
	पूर्ण

	/* because rtc weekday is a पढ़ोonly रेजिस्टर, करो not update */
	data[LPTIME_SEC]  = पंचांग->पंचांग_sec;
	data[LPTIME_MIN]  = पंचांग->पंचांग_min;
	data[LPTIME_HOUR] = पंचांग->पंचांग_hour;
	data[LPTIME_MDAY] = पंचांग->पंचांग_mday;
	data[LPTIME_MON]  = पंचांग->पंचांग_mon + LP8788_MONTH_OFFSET;
	data[LPTIME_YEAR] = year;

	क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
		ret = lp8788_ग_लिखो_byte(lp, LP8788_RTC_SEC + i, data[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा lp8788_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा lp8788 *lp = rtc->lp;
	काष्ठा rtc_समय *पंचांग = &alarm->समय;
	u8 addr, data[LPTIME_MAX];
	पूर्णांक ret;

	addr = addr_alarm_sec[rtc->alarm];
	ret = lp8788_पढ़ो_multi_bytes(lp, addr, data, LPTIME_MAX);
	अगर (ret)
		वापस ret;

	पंचांग->पंचांग_sec  = data[LPTIME_SEC];
	पंचांग->पंचांग_min  = data[LPTIME_MIN];
	पंचांग->पंचांग_hour = data[LPTIME_HOUR];
	पंचांग->पंचांग_mday = data[LPTIME_MDAY];
	पंचांग->पंचांग_mon  = data[LPTIME_MON] - LP8788_MONTH_OFFSET;
	पंचांग->पंचांग_year = data[LPTIME_YEAR] + LP8788_BASE_YEAR - 1900;
	पंचांग->पंचांग_wday = _to_पंचांग_wday(data[LPTIME_WDAY]);
	alarm->enabled = data[LPTIME_WDAY] & LP8788_ALM_EN_M;

	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा lp8788_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा lp8788 *lp = rtc->lp;
	काष्ठा rtc_समय *पंचांग = &alarm->समय;
	u8 addr, data[LPTIME_MAX];
	पूर्णांक ret, i, year;

	year = पंचांग->पंचांग_year + 1900 - LP8788_BASE_YEAR;
	अगर (year < 0) अणु
		dev_err(lp->dev, "invalid year: %d\n", year);
		वापस -EINVAL;
	पूर्ण

	data[LPTIME_SEC]  = पंचांग->पंचांग_sec;
	data[LPTIME_MIN]  = पंचांग->पंचांग_min;
	data[LPTIME_HOUR] = पंचांग->पंचांग_hour;
	data[LPTIME_MDAY] = पंचांग->पंचांग_mday;
	data[LPTIME_MON]  = पंचांग->पंचांग_mon + LP8788_MONTH_OFFSET;
	data[LPTIME_YEAR] = year;
	data[LPTIME_WDAY] = _to_lp8788_wday(पंचांग->पंचांग_wday);

	क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
		addr = addr_alarm_sec[rtc->alarm] + i;
		ret = lp8788_ग_लिखो_byte(lp, addr, data[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	alarm->enabled = 1;
	addr = addr_alarm_en[rtc->alarm];

	वापस lp8788_update_bits(lp, addr, LP8788_ALM_EN_M,
				alarm->enabled << LP8788_ALM_EN_S);
पूर्ण

अटल पूर्णांक lp8788_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा lp8788_rtc *rtc = dev_get_drvdata(dev);
	काष्ठा lp8788 *lp = rtc->lp;
	u8 mask, shअगरt;

	अगर (!rtc->irq)
		वापस -EIO;

	mask = mask_alarm_en[rtc->alarm];
	shअगरt = shअगरt_alarm_en[rtc->alarm];

	वापस lp8788_update_bits(lp, LP8788_INTEN_3, mask, enable << shअगरt);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops lp8788_rtc_ops = अणु
	.पढ़ो_समय = lp8788_rtc_पढ़ो_समय,
	.set_समय = lp8788_rtc_set_समय,
	.पढ़ो_alarm = lp8788_पढ़ो_alarm,
	.set_alarm = lp8788_set_alarm,
	.alarm_irq_enable = lp8788_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t lp8788_alarm_irq_handler(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा lp8788_rtc *rtc = ptr;

	rtc_update_irq(rtc->rdev, 1, ALARM_IRQ_FLAG);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lp8788_alarm_irq_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				काष्ठा lp8788_rtc *rtc)
अणु
	काष्ठा resource *r;
	काष्ठा lp8788 *lp = rtc->lp;
	काष्ठा irq_करोमुख्य *irqdm = lp->irqdm;
	पूर्णांक irq;

	rtc->irq = 0;

	/* even the alarm IRQ number is not specअगरied, rtc समय should work */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, LP8788_ALM_IRQ);
	अगर (!r)
		वापस 0;

	अगर (rtc->alarm == LP8788_ALARM_1)
		irq = r->start;
	अन्यथा
		irq = r->end;

	rtc->irq = irq_create_mapping(irqdm, irq);

	वापस devm_request_thपढ़ोed_irq(&pdev->dev, rtc->irq, शून्य,
				lp8788_alarm_irq_handler,
				0, LP8788_ALM_IRQ, rtc);
पूर्ण

अटल पूर्णांक lp8788_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	काष्ठा lp8788_rtc *rtc;
	काष्ठा device *dev = &pdev->dev;

	rtc = devm_kzalloc(dev, माप(काष्ठा lp8788_rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->lp = lp;
	rtc->alarm = lp->pdata ? lp->pdata->alarm_sel : DEFAULT_ALARM_SEL;
	platक्रमm_set_drvdata(pdev, rtc);

	device_init_wakeup(dev, 1);

	rtc->rdev = devm_rtc_device_रेजिस्टर(dev, "lp8788_rtc",
					&lp8788_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc->rdev)) अणु
		dev_err(dev, "can not register rtc device\n");
		वापस PTR_ERR(rtc->rdev);
	पूर्ण

	अगर (lp8788_alarm_irq_रेजिस्टर(pdev, rtc))
		dev_warn(lp->dev, "no rtc irq handler\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_rtc_driver = अणु
	.probe = lp8788_rtc_probe,
	.driver = अणु
		.name = LP8788_DEV_RTC,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lp8788_rtc_driver);

MODULE_DESCRIPTION("Texas Instruments LP8788 RTC Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8788-rtc");
