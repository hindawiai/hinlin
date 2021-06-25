<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/rtc/rtc-pl031.c
 *
 * Real Time Clock पूर्णांकerface क्रम ARM AMBA PrimeCell 031 RTC
 *
 * Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Copyright 2006 (c) MontaVista Software, Inc.
 *
 * Author: Mian Yousaf Kaukab <mian.yousaf.kaukab@stericsson.com>
 * Copyright 2010 (c) ST-Ericsson AB
 */
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/पन.स>
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/slab.h>

/*
 * Register definitions
 */
#घोषणा	RTC_DR		0x00	/* Data पढ़ो रेजिस्टर */
#घोषणा	RTC_MR		0x04	/* Match रेजिस्टर */
#घोषणा	RTC_LR		0x08	/* Data load रेजिस्टर */
#घोषणा	RTC_CR		0x0c	/* Control रेजिस्टर */
#घोषणा	RTC_IMSC	0x10	/* Interrupt mask and set रेजिस्टर */
#घोषणा	RTC_RIS		0x14	/* Raw पूर्णांकerrupt status रेजिस्टर */
#घोषणा	RTC_MIS		0x18	/* Masked पूर्णांकerrupt status रेजिस्टर */
#घोषणा	RTC_ICR		0x1c	/* Interrupt clear रेजिस्टर */
/* ST variants have additional समयr functionality */
#घोषणा RTC_TDR		0x20	/* Timer data पढ़ो रेजिस्टर */
#घोषणा RTC_TLR		0x24	/* Timer data load रेजिस्टर */
#घोषणा RTC_TCR		0x28	/* Timer control रेजिस्टर */
#घोषणा RTC_YDR		0x30	/* Year data पढ़ो रेजिस्टर */
#घोषणा RTC_YMR		0x34	/* Year match रेजिस्टर */
#घोषणा RTC_YLR		0x38	/* Year data load रेजिस्टर */

#घोषणा RTC_CR_EN	(1 << 0)	/* counter enable bit */
#घोषणा RTC_CR_CWEN	(1 << 26)	/* Clockwatch enable bit */

#घोषणा RTC_TCR_EN	(1 << 1) /* Periodic समयr enable bit */

/* Common bit definitions क्रम Interrupt status and control रेजिस्टरs */
#घोषणा RTC_BIT_AI	(1 << 0) /* Alarm पूर्णांकerrupt bit */
#घोषणा RTC_BIT_PI	(1 << 1) /* Periodic पूर्णांकerrupt bit. ST variants only. */

/* Common bit definations क्रम ST v2 क्रम पढ़ोing/writing समय */
#घोषणा RTC_SEC_SHIFT 0
#घोषणा RTC_SEC_MASK (0x3F << RTC_SEC_SHIFT) /* Second [0-59] */
#घोषणा RTC_MIN_SHIFT 6
#घोषणा RTC_MIN_MASK (0x3F << RTC_MIN_SHIFT) /* Minute [0-59] */
#घोषणा RTC_HOUR_SHIFT 12
#घोषणा RTC_HOUR_MASK (0x1F << RTC_HOUR_SHIFT) /* Hour [0-23] */
#घोषणा RTC_WDAY_SHIFT 17
#घोषणा RTC_WDAY_MASK (0x7 << RTC_WDAY_SHIFT) /* Day of Week [1-7] 1=Sunday */
#घोषणा RTC_MDAY_SHIFT 20
#घोषणा RTC_MDAY_MASK (0x1F << RTC_MDAY_SHIFT) /* Day of Month [1-31] */
#घोषणा RTC_MON_SHIFT 25
#घोषणा RTC_MON_MASK (0xF << RTC_MON_SHIFT) /* Month [1-12] 1=January */

#घोषणा RTC_TIMER_FREQ 32768

/**
 * काष्ठा pl031_venकरोr_data - per-venकरोr variations
 * @ops: the venकरोr-specअगरic operations used on this silicon version
 * @घड़ीwatch: अगर this is an ST Microelectronics silicon version with a
 *	घड़ीwatch function
 * @st_weekday: अगर this is an ST Microelectronics silicon version that need
 *	the weekday fix
 * @irqflags: special IRQ flags per variant
 */
काष्ठा pl031_venकरोr_data अणु
	काष्ठा rtc_class_ops ops;
	bool घड़ीwatch;
	bool st_weekday;
	अचिन्हित दीर्घ irqflags;
	समय64_t range_min;
	समयu64_t range_max;
पूर्ण;

काष्ठा pl031_local अणु
	काष्ठा pl031_venकरोr_data *venकरोr;
	काष्ठा rtc_device *rtc;
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक pl031_alarm_irq_enable(काष्ठा device *dev,
	अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);
	अचिन्हित दीर्घ imsc;

	/* Clear any pending alarm पूर्णांकerrupts. */
	ग_लिखोl(RTC_BIT_AI, ldata->base + RTC_ICR);

	imsc = पढ़ोl(ldata->base + RTC_IMSC);

	अगर (enabled == 1)
		ग_लिखोl(imsc | RTC_BIT_AI, ldata->base + RTC_IMSC);
	अन्यथा
		ग_लिखोl(imsc & ~RTC_BIT_AI, ldata->base + RTC_IMSC);

	वापस 0;
पूर्ण

/*
 * Convert Gregorian date to ST v2 RTC क्रमmat.
 */
अटल पूर्णांक pl031_stv2_पंचांग_to_समय(काष्ठा device *dev,
				 काष्ठा rtc_समय *पंचांग, अचिन्हित दीर्घ *st_समय,
	अचिन्हित दीर्घ *bcd_year)
अणु
	पूर्णांक year = पंचांग->पंचांग_year + 1900;
	पूर्णांक wday = पंचांग->पंचांग_wday;

	/* wday masking is not working in hardware so wday must be valid */
	अगर (wday < -1 || wday > 6) अणु
		dev_err(dev, "invalid wday value %d\n", पंचांग->पंचांग_wday);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (wday == -1) अणु
		/* wday is not provided, calculate it here */
		काष्ठा rtc_समय calc_पंचांग;

		rtc_समय64_to_पंचांग(rtc_पंचांग_to_समय64(पंचांग), &calc_पंचांग);
		wday = calc_पंचांग.पंचांग_wday;
	पूर्ण

	*bcd_year = (bin2bcd(year % 100) | bin2bcd(year / 100) << 8);

	*st_समय = ((पंचांग->पंचांग_mon + 1) << RTC_MON_SHIFT)
			|	(पंचांग->पंचांग_mday << RTC_MDAY_SHIFT)
			|	((wday + 1) << RTC_WDAY_SHIFT)
			|	(पंचांग->पंचांग_hour << RTC_HOUR_SHIFT)
			|	(पंचांग->पंचांग_min << RTC_MIN_SHIFT)
			|	(पंचांग->पंचांग_sec << RTC_SEC_SHIFT);

	वापस 0;
पूर्ण

/*
 * Convert ST v2 RTC क्रमmat to Gregorian date.
 */
अटल पूर्णांक pl031_stv2_समय_प्रकारo_पंचांग(अचिन्हित दीर्घ st_समय, अचिन्हित दीर्घ bcd_year,
	काष्ठा rtc_समय *पंचांग)
अणु
	पंचांग->पंचांग_year = bcd2bin(bcd_year) + (bcd2bin(bcd_year >> 8) * 100);
	पंचांग->पंचांग_mon  = ((st_समय & RTC_MON_MASK) >> RTC_MON_SHIFT) - 1;
	पंचांग->पंचांग_mday = ((st_समय & RTC_MDAY_MASK) >> RTC_MDAY_SHIFT);
	पंचांग->पंचांग_wday = ((st_समय & RTC_WDAY_MASK) >> RTC_WDAY_SHIFT) - 1;
	पंचांग->पंचांग_hour = ((st_समय & RTC_HOUR_MASK) >> RTC_HOUR_SHIFT);
	पंचांग->पंचांग_min  = ((st_समय & RTC_MIN_MASK) >> RTC_MIN_SHIFT);
	पंचांग->पंचांग_sec  = ((st_समय & RTC_SEC_MASK) >> RTC_SEC_SHIFT);

	पंचांग->पंचांग_yday = rtc_year_days(पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year);
	पंचांग->पंचांग_year -= 1900;

	वापस 0;
पूर्ण

अटल पूर्णांक pl031_stv2_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);

	pl031_stv2_समय_प्रकारo_पंचांग(पढ़ोl(ldata->base + RTC_DR),
			पढ़ोl(ldata->base + RTC_YDR), पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pl031_stv2_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ समय;
	अचिन्हित दीर्घ bcd_year;
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pl031_stv2_पंचांग_to_समय(dev, पंचांग, &समय, &bcd_year);
	अगर (ret == 0) अणु
		ग_लिखोl(bcd_year, ldata->base + RTC_YLR);
		ग_लिखोl(समय, ldata->base + RTC_LR);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pl031_stv2_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pl031_stv2_समय_प्रकारo_पंचांग(पढ़ोl(ldata->base + RTC_MR),
			पढ़ोl(ldata->base + RTC_YMR), &alarm->समय);

	alarm->pending = पढ़ोl(ldata->base + RTC_RIS) & RTC_BIT_AI;
	alarm->enabled = पढ़ोl(ldata->base + RTC_IMSC) & RTC_BIT_AI;

	वापस ret;
पूर्ण

अटल पूर्णांक pl031_stv2_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;
	अचिन्हित दीर्घ bcd_year;
	पूर्णांक ret;

	ret = pl031_stv2_पंचांग_to_समय(dev, &alarm->समय,
				    &समय, &bcd_year);
	अगर (ret == 0) अणु
		ग_लिखोl(bcd_year, ldata->base + RTC_YMR);
		ग_लिखोl(समय, ldata->base + RTC_MR);

		pl031_alarm_irq_enable(dev, alarm->enabled);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t pl031_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pl031_local *ldata = dev_id;
	अचिन्हित दीर्घ rtcmis;
	अचिन्हित दीर्घ events = 0;

	rtcmis = पढ़ोl(ldata->base + RTC_MIS);
	अगर (rtcmis & RTC_BIT_AI) अणु
		ग_लिखोl(RTC_BIT_AI, ldata->base + RTC_ICR);
		events |= (RTC_AF | RTC_IRQF);
		rtc_update_irq(ldata->rtc, 1, events);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक pl031_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl(ldata->base + RTC_DR), पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pl031_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);

	ग_लिखोl(rtc_पंचांग_to_समय64(पंचांग), ldata->base + RTC_LR);

	वापस 0;
पूर्ण

अटल पूर्णांक pl031_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(पढ़ोl(ldata->base + RTC_MR), &alarm->समय);

	alarm->pending = पढ़ोl(ldata->base + RTC_RIS) & RTC_BIT_AI;
	alarm->enabled = पढ़ोl(ldata->base + RTC_IMSC) & RTC_BIT_AI;

	वापस 0;
पूर्ण

अटल पूर्णांक pl031_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(dev);

	ग_लिखोl(rtc_पंचांग_to_समय64(&alarm->समय), ldata->base + RTC_MR);
	pl031_alarm_irq_enable(dev, alarm->enabled);

	वापस 0;
पूर्ण

अटल व्योम pl031_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा pl031_local *ldata = dev_get_drvdata(&adev->dev);

	dev_pm_clear_wake_irq(&adev->dev);
	device_init_wakeup(&adev->dev, false);
	अगर (adev->irq[0])
		मुक्त_irq(adev->irq[0], ldata);
	amba_release_regions(adev);
पूर्ण

अटल पूर्णांक pl031_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret;
	काष्ठा pl031_local *ldata;
	काष्ठा pl031_venकरोr_data *venकरोr = id->data;
	काष्ठा rtc_class_ops *ops;
	अचिन्हित दीर्घ समय, data;

	ret = amba_request_regions(adev, शून्य);
	अगर (ret)
		जाओ err_req;

	ldata = devm_kzalloc(&adev->dev, माप(काष्ठा pl031_local),
			     GFP_KERNEL);
	ops = devm_kmemdup(&adev->dev, &venकरोr->ops, माप(venकरोr->ops),
			   GFP_KERNEL);
	अगर (!ldata || !ops) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ldata->venकरोr = venकरोr;
	ldata->base = devm_ioremap(&adev->dev, adev->res.start,
				   resource_size(&adev->res));
	अगर (!ldata->base) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	amba_set_drvdata(adev, ldata);

	dev_dbg(&adev->dev, "designer ID = 0x%02x\n", amba_manf(adev));
	dev_dbg(&adev->dev, "revision = 0x%01x\n", amba_rev(adev));

	data = पढ़ोl(ldata->base + RTC_CR);
	/* Enable the घड़ीwatch on ST Variants */
	अगर (venकरोr->घड़ीwatch)
		data |= RTC_CR_CWEN;
	अन्यथा
		data |= RTC_CR_EN;
	ग_लिखोl(data, ldata->base + RTC_CR);

	/*
	 * On ST PL031 variants, the RTC reset value करोes not provide correct
	 * weekday क्रम 2000-01-01. Correct the erroneous sunday to saturday.
	 */
	अगर (venकरोr->st_weekday) अणु
		अगर (पढ़ोl(ldata->base + RTC_YDR) == 0x2000) अणु
			समय = पढ़ोl(ldata->base + RTC_DR);
			अगर ((समय &
			     (RTC_MON_MASK | RTC_MDAY_MASK | RTC_WDAY_MASK))
			    == 0x02120000) अणु
				समय = समय | (0x7 << RTC_WDAY_SHIFT);
				ग_लिखोl(0x2000, ldata->base + RTC_YLR);
				ग_लिखोl(समय, ldata->base + RTC_LR);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!adev->irq[0])
		clear_bit(RTC_FEATURE_ALARM, ldata->rtc->features);

	device_init_wakeup(&adev->dev, true);
	ldata->rtc = devm_rtc_allocate_device(&adev->dev);
	अगर (IS_ERR(ldata->rtc)) अणु
		ret = PTR_ERR(ldata->rtc);
		जाओ out;
	पूर्ण

	ldata->rtc->ops = ops;
	ldata->rtc->range_min = venकरोr->range_min;
	ldata->rtc->range_max = venकरोr->range_max;

	ret = devm_rtc_रेजिस्टर_device(ldata->rtc);
	अगर (ret)
		जाओ out;

	अगर (adev->irq[0]) अणु
		ret = request_irq(adev->irq[0], pl031_पूर्णांकerrupt,
				  venकरोr->irqflags, "rtc-pl031", ldata);
		अगर (ret)
			जाओ out;
		dev_pm_set_wake_irq(&adev->dev, adev->irq[0]);
	पूर्ण
	वापस 0;

out:
	amba_release_regions(adev);
err_req:

	वापस ret;
पूर्ण

/* Operations क्रम the original ARM version */
अटल काष्ठा pl031_venकरोr_data arm_pl031 = अणु
	.ops = अणु
		.पढ़ो_समय = pl031_पढ़ो_समय,
		.set_समय = pl031_set_समय,
		.पढ़ो_alarm = pl031_पढ़ो_alarm,
		.set_alarm = pl031_set_alarm,
		.alarm_irq_enable = pl031_alarm_irq_enable,
	पूर्ण,
	.range_max = U32_MAX,
पूर्ण;

/* The First ST derivative */
अटल काष्ठा pl031_venकरोr_data stv1_pl031 = अणु
	.ops = अणु
		.पढ़ो_समय = pl031_पढ़ो_समय,
		.set_समय = pl031_set_समय,
		.पढ़ो_alarm = pl031_पढ़ो_alarm,
		.set_alarm = pl031_set_alarm,
		.alarm_irq_enable = pl031_alarm_irq_enable,
	पूर्ण,
	.घड़ीwatch = true,
	.st_weekday = true,
	.range_max = U32_MAX,
पूर्ण;

/* And the second ST derivative */
अटल काष्ठा pl031_venकरोr_data stv2_pl031 = अणु
	.ops = अणु
		.पढ़ो_समय = pl031_stv2_पढ़ो_समय,
		.set_समय = pl031_stv2_set_समय,
		.पढ़ो_alarm = pl031_stv2_पढ़ो_alarm,
		.set_alarm = pl031_stv2_set_alarm,
		.alarm_irq_enable = pl031_alarm_irq_enable,
	पूर्ण,
	.घड़ीwatch = true,
	.st_weekday = true,
	/*
	 * This variant shares the IRQ with another block and must not
	 * suspend that IRQ line.
	 * TODO check अगर it shares with IRQF_NO_SUSPEND user, अन्यथा we can
	 * हटाओ IRQF_COND_SUSPEND
	 */
	.irqflags = IRQF_SHARED | IRQF_COND_SUSPEND,
	.range_min = RTC_TIMESTAMP_BEGIN_0000,
	.range_max = RTC_TIMESTAMP_END_9999,
पूर्ण;

अटल स्थिर काष्ठा amba_id pl031_ids[] = अणु
	अणु
		.id = 0x00041031,
		.mask = 0x000fffff,
		.data = &arm_pl031,
	पूर्ण,
	/* ST Micro variants */
	अणु
		.id = 0x00180031,
		.mask = 0x00ffffff,
		.data = &stv1_pl031,
	पूर्ण,
	अणु
		.id = 0x00280031,
		.mask = 0x00ffffff,
		.data = &stv2_pl031,
	पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl031_ids);

अटल काष्ठा amba_driver pl031_driver = अणु
	.drv = अणु
		.name = "rtc-pl031",
	पूर्ण,
	.id_table = pl031_ids,
	.probe = pl031_probe,
	.हटाओ = pl031_हटाओ,
पूर्ण;

module_amba_driver(pl031_driver);

MODULE_AUTHOR("Deepak Saxena <dsaxena@plexity.net>");
MODULE_DESCRIPTION("ARM AMBA PL031 RTC Driver");
MODULE_LICENSE("GPL");
