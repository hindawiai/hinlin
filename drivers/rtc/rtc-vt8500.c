<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/rtc/rtc-vt8500.c
 *
 *  Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 *
 * Based on rtc-pxa.c
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

/*
 * Register definitions
 */
#घोषणा VT8500_RTC_TS		0x00	/* Time set */
#घोषणा VT8500_RTC_DS		0x04	/* Date set */
#घोषणा VT8500_RTC_AS		0x08	/* Alarm set */
#घोषणा VT8500_RTC_CR		0x0c	/* Control */
#घोषणा VT8500_RTC_TR		0x10	/* Time पढ़ो */
#घोषणा VT8500_RTC_DR		0x14	/* Date पढ़ो */
#घोषणा VT8500_RTC_WS		0x18	/* Write status */
#घोषणा VT8500_RTC_CL		0x20	/* Calibration */
#घोषणा VT8500_RTC_IS		0x24	/* Interrupt status */
#घोषणा VT8500_RTC_ST		0x28	/* Status */

#घोषणा INVALID_TIME_BIT	(1 << 31)

#घोषणा DATE_CENTURY_S		19
#घोषणा DATE_YEAR_S		11
#घोषणा DATE_YEAR_MASK		(0xff << DATE_YEAR_S)
#घोषणा DATE_MONTH_S		6
#घोषणा DATE_MONTH_MASK		(0x1f << DATE_MONTH_S)
#घोषणा DATE_DAY_MASK		0x3f

#घोषणा TIME_DOW_S		20
#घोषणा TIME_DOW_MASK		(0x07 << TIME_DOW_S)
#घोषणा TIME_HOUR_S		14
#घोषणा TIME_HOUR_MASK		(0x3f << TIME_HOUR_S)
#घोषणा TIME_MIN_S		7
#घोषणा TIME_MIN_MASK		(0x7f << TIME_MIN_S)
#घोषणा TIME_SEC_MASK		0x7f

#घोषणा ALARM_DAY_S		20
#घोषणा ALARM_DAY_MASK		(0x3f << ALARM_DAY_S)

#घोषणा ALARM_DAY_BIT		(1 << 29)
#घोषणा ALARM_HOUR_BIT		(1 << 28)
#घोषणा ALARM_MIN_BIT		(1 << 27)
#घोषणा ALARM_SEC_BIT		(1 << 26)

#घोषणा ALARM_ENABLE_MASK	(ALARM_DAY_BIT \
				| ALARM_HOUR_BIT \
				| ALARM_MIN_BIT \
				| ALARM_SEC_BIT)

#घोषणा VT8500_RTC_CR_ENABLE	(1 << 0)	/* Enable RTC */
#घोषणा VT8500_RTC_CR_12H	(1 << 1)	/* 12h समय क्रमmat */
#घोषणा VT8500_RTC_CR_SM_ENABLE	(1 << 2)	/* Enable periodic irqs */
#घोषणा VT8500_RTC_CR_SM_SEC	(1 << 3)	/* 0: 1Hz/60, 1: 1Hz */
#घोषणा VT8500_RTC_CR_CALIB	(1 << 4)	/* Enable calibration */

#घोषणा VT8500_RTC_IS_ALARM	(1 << 0)	/* Alarm पूर्णांकerrupt status */

काष्ठा vt8500_rtc अणु
	व्योम __iomem		*regbase;
	पूर्णांक			irq_alarm;
	काष्ठा rtc_device	*rtc;
	spinlock_t		lock;		/* Protects this काष्ठाure */
पूर्ण;

अटल irqवापस_t vt8500_rtc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc = dev_id;
	u32 isr;
	अचिन्हित दीर्घ events = 0;

	spin_lock(&vt8500_rtc->lock);

	/* clear पूर्णांकerrupt sources */
	isr = पढ़ोl(vt8500_rtc->regbase + VT8500_RTC_IS);
	ग_लिखोl(isr, vt8500_rtc->regbase + VT8500_RTC_IS);

	spin_unlock(&vt8500_rtc->lock);

	अगर (isr & VT8500_RTC_IS_ALARM)
		events |= RTC_AF | RTC_IRQF;

	rtc_update_irq(vt8500_rtc->rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vt8500_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);
	u32 date, समय;

	date = पढ़ोl(vt8500_rtc->regbase + VT8500_RTC_DR);
	समय = पढ़ोl(vt8500_rtc->regbase + VT8500_RTC_TR);

	पंचांग->पंचांग_sec = bcd2bin(समय & TIME_SEC_MASK);
	पंचांग->पंचांग_min = bcd2bin((समय & TIME_MIN_MASK) >> TIME_MIN_S);
	पंचांग->पंचांग_hour = bcd2bin((समय & TIME_HOUR_MASK) >> TIME_HOUR_S);
	पंचांग->पंचांग_mday = bcd2bin(date & DATE_DAY_MASK);
	पंचांग->पंचांग_mon = bcd2bin((date & DATE_MONTH_MASK) >> DATE_MONTH_S) - 1;
	पंचांग->पंचांग_year = bcd2bin((date & DATE_YEAR_MASK) >> DATE_YEAR_S)
			+ ((date >> DATE_CENTURY_S) & 1 ? 200 : 100);
	पंचांग->पंचांग_wday = (समय & TIME_DOW_MASK) >> TIME_DOW_S;

	वापस 0;
पूर्ण

अटल पूर्णांक vt8500_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);

	ग_लिखोl((bin2bcd(पंचांग->पंचांग_year % 100) << DATE_YEAR_S)
		| (bin2bcd(पंचांग->पंचांग_mon + 1) << DATE_MONTH_S)
		| (bin2bcd(पंचांग->पंचांग_mday))
		| ((पंचांग->पंचांग_year >= 200) << DATE_CENTURY_S),
		vt8500_rtc->regbase + VT8500_RTC_DS);
	ग_लिखोl((bin2bcd(पंचांग->पंचांग_wday) << TIME_DOW_S)
		| (bin2bcd(पंचांग->पंचांग_hour) << TIME_HOUR_S)
		| (bin2bcd(पंचांग->पंचांग_min) << TIME_MIN_S)
		| (bin2bcd(पंचांग->पंचांग_sec)),
		vt8500_rtc->regbase + VT8500_RTC_TS);

	वापस 0;
पूर्ण

अटल पूर्णांक vt8500_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);
	u32 isr, alarm;

	alarm = पढ़ोl(vt8500_rtc->regbase + VT8500_RTC_AS);
	isr = पढ़ोl(vt8500_rtc->regbase + VT8500_RTC_IS);

	alrm->समय.पंचांग_mday = bcd2bin((alarm & ALARM_DAY_MASK) >> ALARM_DAY_S);
	alrm->समय.पंचांग_hour = bcd2bin((alarm & TIME_HOUR_MASK) >> TIME_HOUR_S);
	alrm->समय.पंचांग_min = bcd2bin((alarm & TIME_MIN_MASK) >> TIME_MIN_S);
	alrm->समय.पंचांग_sec = bcd2bin((alarm & TIME_SEC_MASK));

	alrm->enabled = (alarm & ALARM_ENABLE_MASK) ? 1 : 0;
	alrm->pending = (isr & VT8500_RTC_IS_ALARM) ? 1 : 0;

	वापस rtc_valid_पंचांग(&alrm->समय);
पूर्ण

अटल पूर्णांक vt8500_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);

	ग_लिखोl((alrm->enabled ? ALARM_ENABLE_MASK : 0)
		| (bin2bcd(alrm->समय.पंचांग_mday) << ALARM_DAY_S)
		| (bin2bcd(alrm->समय.पंचांग_hour) << TIME_HOUR_S)
		| (bin2bcd(alrm->समय.पंचांग_min) << TIME_MIN_S)
		| (bin2bcd(alrm->समय.पंचांग_sec)),
		vt8500_rtc->regbase + VT8500_RTC_AS);

	वापस 0;
पूर्ण

अटल पूर्णांक vt8500_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ पंचांगp = पढ़ोl(vt8500_rtc->regbase + VT8500_RTC_AS);

	अगर (enabled)
		पंचांगp |= ALARM_ENABLE_MASK;
	अन्यथा
		पंचांगp &= ~ALARM_ENABLE_MASK;

	ग_लिखोl(पंचांगp, vt8500_rtc->regbase + VT8500_RTC_AS);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops vt8500_rtc_ops = अणु
	.पढ़ो_समय = vt8500_rtc_पढ़ो_समय,
	.set_समय = vt8500_rtc_set_समय,
	.पढ़ो_alarm = vt8500_rtc_पढ़ो_alarm,
	.set_alarm = vt8500_rtc_set_alarm,
	.alarm_irq_enable = vt8500_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक vt8500_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc;
	पूर्णांक ret;

	vt8500_rtc = devm_kzalloc(&pdev->dev,
			   माप(काष्ठा vt8500_rtc), GFP_KERNEL);
	अगर (!vt8500_rtc)
		वापस -ENOMEM;

	spin_lock_init(&vt8500_rtc->lock);
	platक्रमm_set_drvdata(pdev, vt8500_rtc);

	vt8500_rtc->irq_alarm = platक्रमm_get_irq(pdev, 0);
	अगर (vt8500_rtc->irq_alarm < 0)
		वापस vt8500_rtc->irq_alarm;

	vt8500_rtc->regbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(vt8500_rtc->regbase))
		वापस PTR_ERR(vt8500_rtc->regbase);

	/* Enable RTC and set it to 24-hour mode */
	ग_लिखोl(VT8500_RTC_CR_ENABLE,
	       vt8500_rtc->regbase + VT8500_RTC_CR);

	vt8500_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(vt8500_rtc->rtc))
		वापस PTR_ERR(vt8500_rtc->rtc);

	vt8500_rtc->rtc->ops = &vt8500_rtc_ops;
	vt8500_rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	vt8500_rtc->rtc->range_max = RTC_TIMESTAMP_END_2199;

	ret = devm_request_irq(&pdev->dev, vt8500_rtc->irq_alarm,
				vt8500_rtc_irq, 0, "rtc alarm", vt8500_rtc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "can't get irq %i, err %d\n",
			vt8500_rtc->irq_alarm, ret);
		वापस ret;
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(vt8500_rtc->rtc);
पूर्ण

अटल पूर्णांक vt8500_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8500_rtc *vt8500_rtc = platक्रमm_get_drvdata(pdev);

	/* Disable alarm matching */
	ग_लिखोl(0, vt8500_rtc->regbase + VT8500_RTC_IS);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wmt_dt_ids[] = अणु
	अणु .compatible = "via,vt8500-rtc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wmt_dt_ids);

अटल काष्ठा platक्रमm_driver vt8500_rtc_driver = अणु
	.probe		= vt8500_rtc_probe,
	.हटाओ		= vt8500_rtc_हटाओ,
	.driver		= अणु
		.name	= "vt8500-rtc",
		.of_match_table = wmt_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vt8500_rtc_driver);

MODULE_AUTHOR("Alexey Charkov <alchark@gmail.com>");
MODULE_DESCRIPTION("VIA VT8500 SoC Realtime Clock Driver (RTC)");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:vt8500-rtc");
