<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 RTC Driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 *
 * Broken करोwn from monstrous PCF50633 driver मुख्यly by
 * Harald Welte, Andy Green and Werner Almesberger
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/err.h>

#समावेश <linux/mfd/pcf50633/core.h>

#घोषणा PCF50633_REG_RTCSC	0x59 /* Second */
#घोषणा PCF50633_REG_RTCMN	0x5a /* Minute */
#घोषणा PCF50633_REG_RTCHR	0x5b /* Hour */
#घोषणा PCF50633_REG_RTCWD	0x5c /* Weekday */
#घोषणा PCF50633_REG_RTCDT	0x5d /* Day */
#घोषणा PCF50633_REG_RTCMT	0x5e /* Month */
#घोषणा PCF50633_REG_RTCYR	0x5f /* Year */
#घोषणा PCF50633_REG_RTCSCA	0x60 /* Alarm Second */
#घोषणा PCF50633_REG_RTCMNA	0x61 /* Alarm Minute */
#घोषणा PCF50633_REG_RTCHRA	0x62 /* Alarm Hour */
#घोषणा PCF50633_REG_RTCWDA	0x63 /* Alarm Weekday */
#घोषणा PCF50633_REG_RTCDTA	0x64 /* Alarm Day */
#घोषणा PCF50633_REG_RTCMTA	0x65 /* Alarm Month */
#घोषणा PCF50633_REG_RTCYRA	0x66 /* Alarm Year */

क्रमागत pcf50633_समय_indexes अणु
	PCF50633_TI_SEC,
	PCF50633_TI_MIN,
	PCF50633_TI_HOUR,
	PCF50633_TI_WKDAY,
	PCF50633_TI_DAY,
	PCF50633_TI_MONTH,
	PCF50633_TI_YEAR,
	PCF50633_TI_EXTENT /* always last */
पूर्ण;

काष्ठा pcf50633_समय अणु
	u_पूर्णांक8_t समय[PCF50633_TI_EXTENT];
पूर्ण;

काष्ठा pcf50633_rtc अणु
	पूर्णांक alarm_enabled;
	पूर्णांक alarm_pending;

	काष्ठा pcf50633 *pcf;
	काष्ठा rtc_device *rtc_dev;
पूर्ण;

अटल व्योम pcf2rtc_समय(काष्ठा rtc_समय *rtc, काष्ठा pcf50633_समय *pcf)
अणु
	rtc->पंचांग_sec = bcd2bin(pcf->समय[PCF50633_TI_SEC]);
	rtc->पंचांग_min = bcd2bin(pcf->समय[PCF50633_TI_MIN]);
	rtc->पंचांग_hour = bcd2bin(pcf->समय[PCF50633_TI_HOUR]);
	rtc->पंचांग_wday = bcd2bin(pcf->समय[PCF50633_TI_WKDAY]);
	rtc->पंचांग_mday = bcd2bin(pcf->समय[PCF50633_TI_DAY]);
	rtc->पंचांग_mon = bcd2bin(pcf->समय[PCF50633_TI_MONTH]) - 1;
	rtc->पंचांग_year = bcd2bin(pcf->समय[PCF50633_TI_YEAR]) + 100;
पूर्ण

अटल व्योम rtc2pcf_समय(काष्ठा pcf50633_समय *pcf, काष्ठा rtc_समय *rtc)
अणु
	pcf->समय[PCF50633_TI_SEC] = bin2bcd(rtc->पंचांग_sec);
	pcf->समय[PCF50633_TI_MIN] = bin2bcd(rtc->पंचांग_min);
	pcf->समय[PCF50633_TI_HOUR] = bin2bcd(rtc->पंचांग_hour);
	pcf->समय[PCF50633_TI_WKDAY] = bin2bcd(rtc->पंचांग_wday);
	pcf->समय[PCF50633_TI_DAY] = bin2bcd(rtc->पंचांग_mday);
	pcf->समय[PCF50633_TI_MONTH] = bin2bcd(rtc->पंचांग_mon + 1);
	pcf->समय[PCF50633_TI_YEAR] = bin2bcd(rtc->पंचांग_year % 100);
पूर्ण

अटल पूर्णांक
pcf50633_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा pcf50633_rtc *rtc = dev_get_drvdata(dev);
	पूर्णांक err;

	अगर (enabled)
		err = pcf50633_irq_unmask(rtc->pcf, PCF50633_IRQ_ALARM);
	अन्यथा
		err = pcf50633_irq_mask(rtc->pcf, PCF50633_IRQ_ALARM);

	अगर (err < 0)
		वापस err;

	rtc->alarm_enabled = enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf50633_rtc *rtc;
	काष्ठा pcf50633_समय pcf_पंचांग;
	पूर्णांक ret;

	rtc = dev_get_drvdata(dev);

	ret = pcf50633_पढ़ो_block(rtc->pcf, PCF50633_REG_RTCSC,
					    PCF50633_TI_EXTENT,
					    &pcf_पंचांग.समय[0]);
	अगर (ret != PCF50633_TI_EXTENT) अणु
		dev_err(dev, "Failed to read time\n");
		वापस -EIO;
	पूर्ण

	dev_dbg(dev, "PCF_TIME: %02x.%02x.%02x %02x:%02x:%02x\n",
		pcf_पंचांग.समय[PCF50633_TI_DAY],
		pcf_पंचांग.समय[PCF50633_TI_MONTH],
		pcf_पंचांग.समय[PCF50633_TI_YEAR],
		pcf_पंचांग.समय[PCF50633_TI_HOUR],
		pcf_पंचांग.समय[PCF50633_TI_MIN],
		pcf_पंचांग.समय[PCF50633_TI_SEC]);

	pcf2rtc_समय(पंचांग, &pcf_पंचांग);

	dev_dbg(dev, "RTC_TIME: %ptRr\n", पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf50633_rtc *rtc;
	काष्ठा pcf50633_समय pcf_पंचांग;
	पूर्णांक alarm_masked, ret = 0;

	rtc = dev_get_drvdata(dev);

	dev_dbg(dev, "RTC_TIME: %ptRr\n", पंचांग);

	rtc2pcf_समय(&pcf_पंचांग, पंचांग);

	dev_dbg(dev, "PCF_TIME: %02x.%02x.%02x %02x:%02x:%02x\n",
		pcf_पंचांग.समय[PCF50633_TI_DAY],
		pcf_पंचांग.समय[PCF50633_TI_MONTH],
		pcf_पंचांग.समय[PCF50633_TI_YEAR],
		pcf_पंचांग.समय[PCF50633_TI_HOUR],
		pcf_पंचांग.समय[PCF50633_TI_MIN],
		pcf_पंचांग.समय[PCF50633_TI_SEC]);


	alarm_masked = pcf50633_irq_mask_get(rtc->pcf, PCF50633_IRQ_ALARM);

	अगर (!alarm_masked)
		pcf50633_irq_mask(rtc->pcf, PCF50633_IRQ_ALARM);

	/* Returns 0 on success */
	ret = pcf50633_ग_लिखो_block(rtc->pcf, PCF50633_REG_RTCSC,
					     PCF50633_TI_EXTENT,
					     &pcf_पंचांग.समय[0]);

	अगर (!alarm_masked)
		pcf50633_irq_unmask(rtc->pcf, PCF50633_IRQ_ALARM);

	वापस ret;
पूर्ण

अटल पूर्णांक pcf50633_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcf50633_rtc *rtc;
	काष्ठा pcf50633_समय pcf_पंचांग;
	पूर्णांक ret = 0;

	rtc = dev_get_drvdata(dev);

	alrm->enabled = rtc->alarm_enabled;
	alrm->pending = rtc->alarm_pending;

	ret = pcf50633_पढ़ो_block(rtc->pcf, PCF50633_REG_RTCSCA,
				PCF50633_TI_EXTENT, &pcf_पंचांग.समय[0]);
	अगर (ret != PCF50633_TI_EXTENT) अणु
		dev_err(dev, "Failed to read time\n");
		वापस -EIO;
	पूर्ण

	pcf2rtc_समय(&alrm->समय, &pcf_पंचांग);

	वापस rtc_valid_पंचांग(&alrm->समय);
पूर्ण

अटल पूर्णांक pcf50633_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcf50633_rtc *rtc;
	काष्ठा pcf50633_समय pcf_पंचांग;
	पूर्णांक alarm_masked, ret = 0;

	rtc = dev_get_drvdata(dev);

	rtc2pcf_समय(&pcf_पंचांग, &alrm->समय);

	/* करो like स_गढ़ो करोes and ignore पंचांग_wday */
	pcf_पंचांग.समय[PCF50633_TI_WKDAY] = 7;

	alarm_masked = pcf50633_irq_mask_get(rtc->pcf, PCF50633_IRQ_ALARM);

	/* disable alarm पूर्णांकerrupt */
	अगर (!alarm_masked)
		pcf50633_irq_mask(rtc->pcf, PCF50633_IRQ_ALARM);

	/* Returns 0 on success */
	ret = pcf50633_ग_लिखो_block(rtc->pcf, PCF50633_REG_RTCSCA,
				PCF50633_TI_EXTENT, &pcf_पंचांग.समय[0]);
	अगर (!alrm->enabled)
		rtc->alarm_pending = 0;

	अगर (!alarm_masked || alrm->enabled)
		pcf50633_irq_unmask(rtc->pcf, PCF50633_IRQ_ALARM);
	rtc->alarm_enabled = alrm->enabled;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pcf50633_rtc_ops = अणु
	.पढ़ो_समय		= pcf50633_rtc_पढ़ो_समय,
	.set_समय		= pcf50633_rtc_set_समय,
	.पढ़ो_alarm		= pcf50633_rtc_पढ़ो_alarm,
	.set_alarm		= pcf50633_rtc_set_alarm,
	.alarm_irq_enable	= pcf50633_rtc_alarm_irq_enable,
पूर्ण;

अटल व्योम pcf50633_rtc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pcf50633_rtc *rtc = data;

	rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);
	rtc->alarm_pending = 1;
पूर्ण

अटल पूर्णांक pcf50633_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_rtc *rtc;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->pcf = dev_to_pcf50633(pdev->dev.parent);
	platक्रमm_set_drvdata(pdev, rtc);
	rtc->rtc_dev = devm_rtc_device_रेजिस्टर(&pdev->dev, "pcf50633-rtc",
				&pcf50633_rtc_ops, THIS_MODULE);

	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	pcf50633_रेजिस्टर_irq(rtc->pcf, PCF50633_IRQ_ALARM,
					pcf50633_rtc_irq, rtc);
	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_rtc *rtc;

	rtc = platक्रमm_get_drvdata(pdev);
	pcf50633_मुक्त_irq(rtc->pcf, PCF50633_IRQ_ALARM);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcf50633_rtc_driver = अणु
	.driver = अणु
		.name = "pcf50633-rtc",
	पूर्ण,
	.probe = pcf50633_rtc_probe,
	.हटाओ = pcf50633_rtc_हटाओ,
पूर्ण;

module_platक्रमm_driver(pcf50633_rtc_driver);

MODULE_DESCRIPTION("PCF50633 RTC driver");
MODULE_AUTHOR("Balaji Rao <balajirrao@openmoko.org>");
MODULE_LICENSE("GPL");

