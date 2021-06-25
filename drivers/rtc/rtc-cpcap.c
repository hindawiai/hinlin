<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Motorola CPCAP PMIC RTC driver
 *
 * Based on cpcap-regulator.c from Motorola Linux kernel tree
 * Copyright (C) 2009 Motorola, Inc.
 *
 * Rewritten क्रम मुख्यline kernel
 *  - use DT
 *  - use regmap
 *  - use standard पूर्णांकerrupt framework
 *  - use managed device resources
 *  - हटाओ custom "secure clock daemon" helpers
 *
 * Copyright (C) 2017 Sebastian Reichel <sre@kernel.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/motorola-cpcap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

#घोषणा SECS_PER_DAY 86400
#घोषणा DAY_MASK  0x7FFF
#घोषणा TOD1_MASK 0x00FF
#घोषणा TOD2_MASK 0x01FF

काष्ठा cpcap_समय अणु
	पूर्णांक day;
	पूर्णांक tod1;
	पूर्णांक tod2;
पूर्ण;

काष्ठा cpcap_rtc अणु
	काष्ठा regmap *regmap;
	काष्ठा rtc_device *rtc_dev;
	u16 venकरोr;
	पूर्णांक alarm_irq;
	bool alarm_enabled;
	पूर्णांक update_irq;
	bool update_enabled;
पूर्ण;

अटल व्योम cpcap2rtc_समय(काष्ठा rtc_समय *rtc, काष्ठा cpcap_समय *cpcap)
अणु
	अचिन्हित दीर्घ पूर्णांक tod;
	अचिन्हित दीर्घ पूर्णांक समय;

	tod = (cpcap->tod1 & TOD1_MASK) | ((cpcap->tod2 & TOD2_MASK) << 8);
	समय = tod + ((cpcap->day & DAY_MASK) * SECS_PER_DAY);

	rtc_समय64_to_पंचांग(समय, rtc);
पूर्ण

अटल व्योम rtc2cpcap_समय(काष्ठा cpcap_समय *cpcap, काष्ठा rtc_समय *rtc)
अणु
	अचिन्हित दीर्घ समय;

	समय = rtc_पंचांग_to_समय64(rtc);

	cpcap->day = समय / SECS_PER_DAY;
	समय %= SECS_PER_DAY;
	cpcap->tod2 = (समय >> 8) & TOD2_MASK;
	cpcap->tod1 = समय & TOD1_MASK;
पूर्ण

अटल पूर्णांक cpcap_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा cpcap_rtc *rtc = dev_get_drvdata(dev);

	अगर (rtc->alarm_enabled == enabled)
		वापस 0;

	अगर (enabled)
		enable_irq(rtc->alarm_irq);
	अन्यथा
		disable_irq(rtc->alarm_irq);

	rtc->alarm_enabled = !!enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा cpcap_rtc *rtc;
	काष्ठा cpcap_समय cpcap_पंचांग;
	पूर्णांक temp_tod2;
	पूर्णांक ret;

	rtc = dev_get_drvdata(dev);

	ret = regmap_पढ़ो(rtc->regmap, CPCAP_REG_TOD2, &temp_tod2);
	ret |= regmap_पढ़ो(rtc->regmap, CPCAP_REG_DAY, &cpcap_पंचांग.day);
	ret |= regmap_पढ़ो(rtc->regmap, CPCAP_REG_TOD1, &cpcap_पंचांग.tod1);
	ret |= regmap_पढ़ो(rtc->regmap, CPCAP_REG_TOD2, &cpcap_पंचांग.tod2);

	अगर (temp_tod2 > cpcap_पंचांग.tod2)
		ret |= regmap_पढ़ो(rtc->regmap, CPCAP_REG_DAY, &cpcap_पंचांग.day);

	अगर (ret) अणु
		dev_err(dev, "Failed to read time\n");
		वापस -EIO;
	पूर्ण

	cpcap2rtc_समय(पंचांग, &cpcap_पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा cpcap_rtc *rtc;
	काष्ठा cpcap_समय cpcap_पंचांग;
	पूर्णांक ret = 0;

	rtc = dev_get_drvdata(dev);

	rtc2cpcap_समय(&cpcap_पंचांग, पंचांग);

	अगर (rtc->alarm_enabled)
		disable_irq(rtc->alarm_irq);
	अगर (rtc->update_enabled)
		disable_irq(rtc->update_irq);

	अगर (rtc->venकरोr == CPCAP_VENDOR_ST) अणु
		/* The TOD1 and TOD2 रेजिस्टरs MUST be written in this order
		 * क्रम the change to properly set.
		 */
		ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_TOD1,
					  TOD1_MASK, cpcap_पंचांग.tod1);
		ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_TOD2,
					  TOD2_MASK, cpcap_पंचांग.tod2);
		ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_DAY,
					  DAY_MASK, cpcap_पंचांग.day);
	पूर्ण अन्यथा अणु
		/* Clearing the upper lower 8 bits of the TOD guarantees that
		 * the upper half of TOD (TOD2) will not increment क्रम 0xFF RTC
		 * ticks (255 seconds).  During this समय we can safely ग_लिखो
		 * to DAY, TOD2, then TOD1 (in that order) and expect RTC to be
		 * synchronized to the exact समय requested upon the final ग_लिखो
		 * to TOD1.
		 */
		ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_TOD1,
					  TOD1_MASK, 0);
		ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_DAY,
					  DAY_MASK, cpcap_पंचांग.day);
		ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_TOD2,
					  TOD2_MASK, cpcap_पंचांग.tod2);
		ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_TOD1,
					  TOD1_MASK, cpcap_पंचांग.tod1);
	पूर्ण

	अगर (rtc->update_enabled)
		enable_irq(rtc->update_irq);
	अगर (rtc->alarm_enabled)
		enable_irq(rtc->alarm_irq);

	वापस ret;
पूर्ण

अटल पूर्णांक cpcap_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा cpcap_rtc *rtc;
	काष्ठा cpcap_समय cpcap_पंचांग;
	पूर्णांक ret;

	rtc = dev_get_drvdata(dev);

	alrm->enabled = rtc->alarm_enabled;

	ret = regmap_पढ़ो(rtc->regmap, CPCAP_REG_DAYA, &cpcap_पंचांग.day);
	ret |= regmap_पढ़ो(rtc->regmap, CPCAP_REG_TODA2, &cpcap_पंचांग.tod2);
	ret |= regmap_पढ़ो(rtc->regmap, CPCAP_REG_TODA1, &cpcap_पंचांग.tod1);

	अगर (ret) अणु
		dev_err(dev, "Failed to read time\n");
		वापस -EIO;
	पूर्ण

	cpcap2rtc_समय(&alrm->समय, &cpcap_पंचांग);
	वापस rtc_valid_पंचांग(&alrm->समय);
पूर्ण

अटल पूर्णांक cpcap_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा cpcap_rtc *rtc;
	काष्ठा cpcap_समय cpcap_पंचांग;
	पूर्णांक ret;

	rtc = dev_get_drvdata(dev);

	rtc2cpcap_समय(&cpcap_पंचांग, &alrm->समय);

	अगर (rtc->alarm_enabled)
		disable_irq(rtc->alarm_irq);

	ret = regmap_update_bits(rtc->regmap, CPCAP_REG_DAYA, DAY_MASK,
				 cpcap_पंचांग.day);
	ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_TODA2, TOD2_MASK,
				  cpcap_पंचांग.tod2);
	ret |= regmap_update_bits(rtc->regmap, CPCAP_REG_TODA1, TOD1_MASK,
				  cpcap_पंचांग.tod1);

	अगर (!ret) अणु
		enable_irq(rtc->alarm_irq);
		rtc->alarm_enabled = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops cpcap_rtc_ops = अणु
	.पढ़ो_समय		= cpcap_rtc_पढ़ो_समय,
	.set_समय		= cpcap_rtc_set_समय,
	.पढ़ो_alarm		= cpcap_rtc_पढ़ो_alarm,
	.set_alarm		= cpcap_rtc_set_alarm,
	.alarm_irq_enable	= cpcap_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t cpcap_rtc_alarm_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cpcap_rtc *rtc = data;

	rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cpcap_rtc_update_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cpcap_rtc *rtc = data;

	rtc_update_irq(rtc->rtc_dev, 1, RTC_UF | RTC_IRQF);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cpcap_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cpcap_rtc *rtc;
	पूर्णांक err;

	rtc = devm_kzalloc(dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!rtc->regmap)
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, rtc);
	rtc->rtc_dev = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	rtc->rtc_dev->ops = &cpcap_rtc_ops;
	rtc->rtc_dev->range_max = (समयu64_t) (DAY_MASK + 1) * SECS_PER_DAY - 1;

	err = cpcap_get_venकरोr(dev, rtc->regmap, &rtc->venकरोr);
	अगर (err)
		वापस err;

	rtc->alarm_irq = platक्रमm_get_irq(pdev, 0);
	err = devm_request_thपढ़ोed_irq(dev, rtc->alarm_irq, शून्य,
					cpcap_rtc_alarm_irq,
					IRQF_TRIGGER_NONE | IRQF_ONESHOT,
					"rtc_alarm", rtc);
	अगर (err) अणु
		dev_err(dev, "Could not request alarm irq: %d\n", err);
		वापस err;
	पूर्ण
	disable_irq(rtc->alarm_irq);

	/* Stock Android uses the 1 Hz पूर्णांकerrupt क्रम "secure clock daemon",
	 * which is not supported by the मुख्यline kernel. The मुख्यline kernel
	 * करोes not use the irq at the moment, but we explicitly request and
	 * disable it, so that its masked and करोes not wake up the processor
	 * every second.
	 */
	rtc->update_irq = platक्रमm_get_irq(pdev, 1);
	err = devm_request_thपढ़ोed_irq(dev, rtc->update_irq, शून्य,
					cpcap_rtc_update_irq,
					IRQF_TRIGGER_NONE | IRQF_ONESHOT,
					"rtc_1hz", rtc);
	अगर (err) अणु
		dev_err(dev, "Could not request update irq: %d\n", err);
		वापस err;
	पूर्ण
	disable_irq(rtc->update_irq);

	err = device_init_wakeup(dev, 1);
	अगर (err) अणु
		dev_err(dev, "wakeup initialization failed (%d)\n", err);
		/* ignore error and जारी without wakeup support */
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id cpcap_rtc_of_match[] = अणु
	अणु .compatible = "motorola,cpcap-rtc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_rtc_of_match);

अटल काष्ठा platक्रमm_driver cpcap_rtc_driver = अणु
	.probe		= cpcap_rtc_probe,
	.driver		= अणु
		.name	= "cpcap-rtc",
		.of_match_table = cpcap_rtc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cpcap_rtc_driver);

MODULE_ALIAS("platform:cpcap-rtc");
MODULE_DESCRIPTION("CPCAP RTC driver");
MODULE_AUTHOR("Sebastian Reichel <sre@kernel.org>");
MODULE_LICENSE("GPL");
