<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rtc-tps65910.c -- TPS65910 Real Time Clock पूर्णांकerface
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 * Author: Venu Byravarasu <vbyravarasu@nvidia.com>
 *
 * Based on original TI driver rtc-twl.c
 *   Copyright (C) 2007 MontaVista Software, Inc
 *   Author: Alexandre Rusev <source@mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/math64.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/tps65910.h>

काष्ठा tps65910_rtc अणु
	काष्ठा rtc_device	*rtc;
	पूर्णांक irq;
पूर्ण;

/* Total number of RTC रेजिस्टरs needed to set समय*/
#घोषणा NUM_TIME_REGS	(TPS65910_YEARS - TPS65910_SECONDS + 1)

/* Total number of RTC रेजिस्टरs needed to set compensation रेजिस्टरs */
#घोषणा NUM_COMP_REGS	(TPS65910_RTC_COMP_MSB - TPS65910_RTC_COMP_LSB + 1)

/* Min and max values supported with 'offset' पूर्णांकerface (swapped sign) */
#घोषणा MIN_OFFSET	(-277761)
#घोषणा MAX_OFFSET	(277778)

/* Number of ticks per hour */
#घोषणा TICKS_PER_HOUR	(32768 * 3600)

/* Multiplier क्रम ppb conversions */
#घोषणा PPB_MULT	(1000000000LL)

अटल पूर्णांक tps65910_rtc_alarm_irq_enable(काष्ठा device *dev,
					 अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	u8 val = 0;

	अगर (enabled)
		val = TPS65910_RTC_INTERRUPTS_IT_ALARM;

	वापस regmap_ग_लिखो(tps->regmap, TPS65910_RTC_INTERRUPTS, val);
पूर्ण

/*
 * Gets current tps65910 RTC समय and date parameters.
 *
 * The RTC's समय/alarm representation is not what स_जमट(3) requires
 * Linux to use:
 *
 *  - Months are 1..12 vs Linux 0-11
 *  - Years are 0..99 vs Linux 1900..N (we assume 21st century)
 */
अटल पूर्णांक tps65910_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर rtc_data[NUM_TIME_REGS];
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	/* Copy RTC counting रेजिस्टरs to अटल रेजिस्टरs or latches */
	ret = regmap_update_bits(tps->regmap, TPS65910_RTC_CTRL,
		TPS65910_RTC_CTRL_GET_TIME, TPS65910_RTC_CTRL_GET_TIME);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC CTRL reg update failed with err:%d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_bulk_पढ़ो(tps->regmap, TPS65910_SECONDS, rtc_data,
		NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "reading from RTC failed with err:%d\n", ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(rtc_data[0]);
	पंचांग->पंचांग_min = bcd2bin(rtc_data[1]);
	पंचांग->पंचांग_hour = bcd2bin(rtc_data[2]);
	पंचांग->पंचांग_mday = bcd2bin(rtc_data[3]);
	पंचांग->पंचांग_mon = bcd2bin(rtc_data[4]) - 1;
	पंचांग->पंचांग_year = bcd2bin(rtc_data[5]) + 100;

	वापस ret;
पूर्ण

अटल पूर्णांक tps65910_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित अक्षर rtc_data[NUM_TIME_REGS];
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	rtc_data[0] = bin2bcd(पंचांग->पंचांग_sec);
	rtc_data[1] = bin2bcd(पंचांग->पंचांग_min);
	rtc_data[2] = bin2bcd(पंचांग->पंचांग_hour);
	rtc_data[3] = bin2bcd(पंचांग->पंचांग_mday);
	rtc_data[4] = bin2bcd(पंचांग->पंचांग_mon + 1);
	rtc_data[5] = bin2bcd(पंचांग->पंचांग_year - 100);

	/* Stop RTC जबतक updating the RTC समय रेजिस्टरs */
	ret = regmap_update_bits(tps->regmap, TPS65910_RTC_CTRL,
		TPS65910_RTC_CTRL_STOP_RTC, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "RTC stop failed with err:%d\n", ret);
		वापस ret;
	पूर्ण

	/* update all the समय रेजिस्टरs in one shot */
	ret = regmap_bulk_ग_लिखो(tps->regmap, TPS65910_SECONDS, rtc_data,
		NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "rtc_set_time error %d\n", ret);
		वापस ret;
	पूर्ण

	/* Start back RTC */
	ret = regmap_update_bits(tps->regmap, TPS65910_RTC_CTRL,
		TPS65910_RTC_CTRL_STOP_RTC, 1);
	अगर (ret < 0)
		dev_err(dev, "RTC start failed with err:%d\n", ret);

	वापस ret;
पूर्ण

/*
 * Gets current tps65910 RTC alarm समय.
 */
अटल पूर्णांक tps65910_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	अचिन्हित अक्षर alarm_data[NUM_TIME_REGS];
	u32 पूर्णांक_val;
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(tps->regmap, TPS65910_ALARM_SECONDS, alarm_data,
		NUM_TIME_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "rtc_read_alarm error %d\n", ret);
		वापस ret;
	पूर्ण

	alm->समय.पंचांग_sec = bcd2bin(alarm_data[0]);
	alm->समय.पंचांग_min = bcd2bin(alarm_data[1]);
	alm->समय.पंचांग_hour = bcd2bin(alarm_data[2]);
	alm->समय.पंचांग_mday = bcd2bin(alarm_data[3]);
	alm->समय.पंचांग_mon = bcd2bin(alarm_data[4]) - 1;
	alm->समय.पंचांग_year = bcd2bin(alarm_data[5]) + 100;

	ret = regmap_पढ़ो(tps->regmap, TPS65910_RTC_INTERRUPTS, &पूर्णांक_val);
	अगर (ret < 0)
		वापस ret;

	अगर (पूर्णांक_val & TPS65910_RTC_INTERRUPTS_IT_ALARM)
		alm->enabled = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक tps65910_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	अचिन्हित अक्षर alarm_data[NUM_TIME_REGS];
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	ret = tps65910_rtc_alarm_irq_enable(dev, 0);
	अगर (ret)
		वापस ret;

	alarm_data[0] = bin2bcd(alm->समय.पंचांग_sec);
	alarm_data[1] = bin2bcd(alm->समय.पंचांग_min);
	alarm_data[2] = bin2bcd(alm->समय.पंचांग_hour);
	alarm_data[3] = bin2bcd(alm->समय.पंचांग_mday);
	alarm_data[4] = bin2bcd(alm->समय.पंचांग_mon + 1);
	alarm_data[5] = bin2bcd(alm->समय.पंचांग_year - 100);

	/* update all the alarm रेजिस्टरs in one shot */
	ret = regmap_bulk_ग_लिखो(tps->regmap, TPS65910_ALARM_SECONDS,
		alarm_data, NUM_TIME_REGS);
	अगर (ret) अणु
		dev_err(dev, "rtc_set_alarm error %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (alm->enabled)
		ret = tps65910_rtc_alarm_irq_enable(dev, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक tps65910_rtc_set_calibration(काष्ठा device *dev, पूर्णांक calibration)
अणु
	अचिन्हित अक्षर comp_data[NUM_COMP_REGS];
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	s16 value;
	पूर्णांक ret;

	/*
	 * TPS65910 uses two's complement 16 bit value क्रम compensation क्रम RTC
	 * crystal inaccuracies. One समय every hour when seconds counter
	 * increments from 0 to 1 compensation value will be added to पूर्णांकernal
	 * RTC counter value.
	 *
	 * Compensation value 0x7FFF is prohibited value.
	 *
	 * Valid range क्रम compensation value: [-32768 .. 32766]
	 */
	अगर ((calibration < -32768) || (calibration > 32766)) अणु
		dev_err(dev, "RTC calibration value out of range: %d\n",
			calibration);
		वापस -EINVAL;
	पूर्ण

	value = (s16)calibration;

	comp_data[0] = (u16)value & 0xFF;
	comp_data[1] = ((u16)value >> 8) & 0xFF;

	/* Update all the compensation रेजिस्टरs in one shot */
	ret = regmap_bulk_ग_लिखो(tps->regmap, TPS65910_RTC_COMP_LSB,
		comp_data, NUM_COMP_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "rtc_set_calibration error: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable स्वतःmatic compensation */
	ret = regmap_update_bits(tps->regmap, TPS65910_RTC_CTRL,
		TPS65910_RTC_CTRL_AUTO_COMP, TPS65910_RTC_CTRL_AUTO_COMP);
	अगर (ret < 0)
		dev_err(dev, "auto_comp enable failed with error: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tps65910_rtc_get_calibration(काष्ठा device *dev, पूर्णांक *calibration)
अणु
	अचिन्हित अक्षर comp_data[NUM_COMP_REGS];
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	अचिन्हित पूर्णांक ctrl;
	u16 value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps->regmap, TPS65910_RTC_CTRL, &ctrl);
	अगर (ret < 0)
		वापस ret;

	/* If स्वतःmatic compensation is not enabled report back zero */
	अगर (!(ctrl & TPS65910_RTC_CTRL_AUTO_COMP)) अणु
		*calibration = 0;
		वापस 0;
	पूर्ण

	ret = regmap_bulk_पढ़ो(tps->regmap, TPS65910_RTC_COMP_LSB, comp_data,
		NUM_COMP_REGS);
	अगर (ret < 0) अणु
		dev_err(dev, "rtc_get_calibration error: %d\n", ret);
		वापस ret;
	पूर्ण

	value = (u16)comp_data[0] | ((u16)comp_data[1] << 8);

	*calibration = (s16)value;

	वापस 0;
पूर्ण

अटल पूर्णांक tps65910_पढ़ो_offset(काष्ठा device *dev, दीर्घ *offset)
अणु
	पूर्णांक calibration;
	s64 पंचांगp;
	पूर्णांक ret;

	ret = tps65910_rtc_get_calibration(dev, &calibration);
	अगर (ret < 0)
		वापस ret;

	/* Convert from RTC calibration रेजिस्टर क्रमmat to ppb क्रमmat */
	पंचांगp = calibration * (s64)PPB_MULT;
	अगर (पंचांगp < 0)
		पंचांगp -= TICKS_PER_HOUR / 2LL;
	अन्यथा
		पंचांगp += TICKS_PER_HOUR / 2LL;
	पंचांगp = भाग_s64(पंचांगp, TICKS_PER_HOUR);

	/* Offset value operates in negative way, so swap sign */
	*offset = (दीर्घ)-पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक tps65910_set_offset(काष्ठा device *dev, दीर्घ offset)
अणु
	पूर्णांक calibration;
	s64 पंचांगp;
	पूर्णांक ret;

	/* Make sure offset value is within supported range */
	अगर (offset < MIN_OFFSET || offset > MAX_OFFSET)
		वापस -दुस्फल;

	/* Convert from ppb क्रमmat to RTC calibration रेजिस्टर क्रमmat */
	पंचांगp = offset * (s64)TICKS_PER_HOUR;
	अगर (पंचांगp < 0)
		पंचांगp -= PPB_MULT / 2LL;
	अन्यथा
		पंचांगp += PPB_MULT / 2LL;
	पंचांगp = भाग_s64(पंचांगp, PPB_MULT);

	/* Offset value operates in negative way, so swap sign */
	calibration = (पूर्णांक)-पंचांगp;

	ret = tps65910_rtc_set_calibration(dev, calibration);

	वापस ret;
पूर्ण

अटल irqवापस_t tps65910_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *rtc)
अणु
	काष्ठा device *dev = rtc;
	अचिन्हित दीर्घ events = 0;
	काष्ठा tps65910 *tps = dev_get_drvdata(dev->parent);
	काष्ठा tps65910_rtc *tps_rtc = dev_get_drvdata(dev);
	पूर्णांक ret;
	u32 rtc_reg;

	ret = regmap_पढ़ो(tps->regmap, TPS65910_RTC_STATUS, &rtc_reg);
	अगर (ret)
		वापस IRQ_NONE;

	अगर (rtc_reg & TPS65910_RTC_STATUS_ALARM)
		events = RTC_IRQF | RTC_AF;

	ret = regmap_ग_लिखो(tps->regmap, TPS65910_RTC_STATUS, rtc_reg);
	अगर (ret)
		वापस IRQ_NONE;

	/* Notअगरy RTC core on event */
	rtc_update_irq(tps_rtc->rtc, 1, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops tps65910_rtc_ops = अणु
	.पढ़ो_समय	= tps65910_rtc_पढ़ो_समय,
	.set_समय	= tps65910_rtc_set_समय,
	.पढ़ो_alarm	= tps65910_rtc_पढ़ो_alarm,
	.set_alarm	= tps65910_rtc_set_alarm,
	.alarm_irq_enable = tps65910_rtc_alarm_irq_enable,
	.पढ़ो_offset	= tps65910_पढ़ो_offset,
	.set_offset	= tps65910_set_offset,
पूर्ण;

अटल पूर्णांक tps65910_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65910 *tps65910 = शून्य;
	काष्ठा tps65910_rtc *tps_rtc = शून्य;
	पूर्णांक ret;
	पूर्णांक irq;
	u32 rtc_reg;

	tps65910 = dev_get_drvdata(pdev->dev.parent);

	tps_rtc = devm_kzalloc(&pdev->dev, माप(काष्ठा tps65910_rtc),
			GFP_KERNEL);
	अगर (!tps_rtc)
		वापस -ENOMEM;

	tps_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(tps_rtc->rtc))
		वापस PTR_ERR(tps_rtc->rtc);

	/* Clear pending पूर्णांकerrupts */
	ret = regmap_पढ़ो(tps65910->regmap, TPS65910_RTC_STATUS, &rtc_reg);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(tps65910->regmap, TPS65910_RTC_STATUS, rtc_reg);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&pdev->dev, "Enabling rtc-tps65910.\n");

	/* Enable RTC digital घातer करोमुख्य */
	ret = regmap_update_bits(tps65910->regmap, TPS65910_DEVCTRL,
		DEVCTRL_RTC_PWDN_MASK, 0 << DEVCTRL_RTC_PWDN_SHIFT);
	अगर (ret < 0)
		वापस ret;

	rtc_reg = TPS65910_RTC_CTRL_STOP_RTC;
	ret = regmap_ग_लिखो(tps65910->regmap, TPS65910_RTC_CTRL, rtc_reg);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, tps_rtc);

	irq  = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		dev_warn(&pdev->dev, "Wake up is not possible as irq = %d\n",
			irq);
		वापस -ENXIO;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
		tps65910_rtc_पूर्णांकerrupt, IRQF_TRIGGER_LOW,
		dev_name(&pdev->dev), &pdev->dev);
	अगर (ret < 0)
		irq = -1;

	tps_rtc->irq = irq;
	अगर (irq != -1) अणु
		अगर (device_property_present(tps65910->dev, "wakeup-source"))
			device_init_wakeup(&pdev->dev, 1);
		अन्यथा
			device_set_wakeup_capable(&pdev->dev, 1);
	पूर्ण अन्यथा अणु
		clear_bit(RTC_FEATURE_ALARM, tps_rtc->rtc->features);
	पूर्ण

	tps_rtc->rtc->ops = &tps65910_rtc_ops;
	tps_rtc->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	tps_rtc->rtc->range_max = RTC_TIMESTAMP_END_2099;

	वापस devm_rtc_रेजिस्टर_device(tps_rtc->rtc);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tps65910_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा tps65910_rtc *tps_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(tps_rtc->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक tps65910_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा tps65910_rtc *tps_rtc = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(tps_rtc->irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tps65910_rtc_pm_ops, tps65910_rtc_suspend,
			tps65910_rtc_resume);

अटल काष्ठा platक्रमm_driver tps65910_rtc_driver = अणु
	.probe		= tps65910_rtc_probe,
	.driver		= अणु
		.name	= "tps65910-rtc",
		.pm	= &tps65910_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tps65910_rtc_driver);
MODULE_ALIAS("platform:rtc-tps65910");
MODULE_AUTHOR("Venu Byravarasu <vbyravarasu@nvidia.com>");
MODULE_LICENSE("GPL");
