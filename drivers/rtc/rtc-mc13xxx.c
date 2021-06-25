<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real Time Clock driver क्रम Freescale MC13XXX PMIC
 *
 * (C) 2009 Sascha Hauer, Pengutronix
 * (C) 2009 Uwe Kleine-Koenig, Pengutronix
 */

#समावेश <linux/mfd/mc13xxx.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>

#घोषणा DRIVER_NAME "mc13xxx-rtc"

#घोषणा MC13XXX_RTCTOD	20
#घोषणा MC13XXX_RTCTODA	21
#घोषणा MC13XXX_RTCDAY	22
#घोषणा MC13XXX_RTCDAYA	23

#घोषणा SEC_PER_DAY	(24 * 60 * 60)

काष्ठा mc13xxx_rtc अणु
	काष्ठा rtc_device *rtc;
	काष्ठा mc13xxx *mc13xxx;
	पूर्णांक valid;
पूर्ण;

अटल पूर्णांक mc13xxx_rtc_irq_enable_unlocked(काष्ठा device *dev,
		अचिन्हित पूर्णांक enabled, पूर्णांक irq)
अणु
	काष्ठा mc13xxx_rtc *priv = dev_get_drvdata(dev);
	पूर्णांक (*func)(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq);

	अगर (!priv->valid)
		वापस -ENODATA;

	func = enabled ? mc13xxx_irq_unmask : mc13xxx_irq_mask;
	वापस func(priv->mc13xxx, irq);
पूर्ण

अटल पूर्णांक mc13xxx_rtc_alarm_irq_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा mc13xxx_rtc *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	mc13xxx_lock(priv->mc13xxx);

	ret = mc13xxx_rtc_irq_enable_unlocked(dev, enabled, MC13XXX_IRQ_TODA);

	mc13xxx_unlock(priv->mc13xxx);

	वापस ret;
पूर्ण

अटल पूर्णांक mc13xxx_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mc13xxx_rtc *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक seconds, days1, days2;

	अगर (!priv->valid)
		वापस -ENODATA;

	करो अणु
		पूर्णांक ret;

		ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, MC13XXX_RTCDAY, &days1);
		अगर (ret)
			वापस ret;

		ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, MC13XXX_RTCTOD, &seconds);
		अगर (ret)
			वापस ret;

		ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, MC13XXX_RTCDAY, &days2);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (days1 != days2);

	rtc_समय64_to_पंचांग((समय64_t)days1 * SEC_PER_DAY + seconds, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक mc13xxx_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा mc13xxx_rtc *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक seconds, days;
	अचिन्हित पूर्णांक alarmseconds;
	पूर्णांक ret;

	days = भाग_s64_rem(rtc_पंचांग_to_समय64(पंचांग), SEC_PER_DAY, &seconds);

	mc13xxx_lock(priv->mc13xxx);

	/*
	 * temporarily invalidate alarm to prevent triggering it when the day is
	 * alपढ़ोy updated जबतक the समय isn't yet.
	 */
	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, MC13XXX_RTCTODA, &alarmseconds);
	अगर (unlikely(ret))
		जाओ out;

	अगर (alarmseconds < SEC_PER_DAY) अणु
		ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx,
				MC13XXX_RTCTODA, 0x1ffff);
		अगर (unlikely(ret))
			जाओ out;
	पूर्ण

	/*
	 * ग_लिखो seconds=0 to prevent a day चयन between writing days
	 * and seconds below
	 */
	ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13XXX_RTCTOD, 0);
	अगर (unlikely(ret))
		जाओ out;

	ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13XXX_RTCDAY, days);
	अगर (unlikely(ret))
		जाओ out;

	ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13XXX_RTCTOD, seconds);
	अगर (unlikely(ret))
		जाओ out;

	/* restore alarm */
	अगर (alarmseconds < SEC_PER_DAY) अणु
		ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx,
				MC13XXX_RTCTODA, alarmseconds);
		अगर (unlikely(ret))
			जाओ out;
	पूर्ण

	अगर (!priv->valid) अणु
		ret = mc13xxx_irq_ack(priv->mc13xxx, MC13XXX_IRQ_RTCRST);
		अगर (unlikely(ret))
			जाओ out;

		ret = mc13xxx_irq_unmask(priv->mc13xxx, MC13XXX_IRQ_RTCRST);
	पूर्ण

out:
	priv->valid = !ret;

	mc13xxx_unlock(priv->mc13xxx);

	वापस ret;
पूर्ण

अटल पूर्णांक mc13xxx_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा mc13xxx_rtc *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक seconds, days;
	समय64_t s1970;
	पूर्णांक enabled, pending;
	पूर्णांक ret;

	mc13xxx_lock(priv->mc13xxx);

	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, MC13XXX_RTCTODA, &seconds);
	अगर (unlikely(ret))
		जाओ out;
	अगर (seconds >= SEC_PER_DAY) अणु
		ret = -ENODATA;
		जाओ out;
	पूर्ण

	ret = mc13xxx_reg_पढ़ो(priv->mc13xxx, MC13XXX_RTCDAY, &days);
	अगर (unlikely(ret))
		जाओ out;

	ret = mc13xxx_irq_status(priv->mc13xxx, MC13XXX_IRQ_TODA,
			&enabled, &pending);

out:
	mc13xxx_unlock(priv->mc13xxx);

	अगर (ret)
		वापस ret;

	alarm->enabled = enabled;
	alarm->pending = pending;

	s1970 = (समय64_t)days * SEC_PER_DAY + seconds;

	rtc_समय64_to_पंचांग(s1970, &alarm->समय);
	dev_dbg(dev, "%s: %lld\n", __func__, (दीर्घ दीर्घ)s1970);

	वापस 0;
पूर्ण

अटल पूर्णांक mc13xxx_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा mc13xxx_rtc *priv = dev_get_drvdata(dev);
	समय64_t s1970;
	u32 seconds, days;
	पूर्णांक ret;

	mc13xxx_lock(priv->mc13xxx);

	/* disable alarm to prevent false triggering */
	ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13XXX_RTCTODA, 0x1ffff);
	अगर (unlikely(ret))
		जाओ out;

	ret = mc13xxx_irq_ack(priv->mc13xxx, MC13XXX_IRQ_TODA);
	अगर (unlikely(ret))
		जाओ out;

	s1970 = rtc_पंचांग_to_समय64(&alarm->समय);

	dev_dbg(dev, "%s: %s %lld\n", __func__, alarm->enabled ? "on" : "off",
			(दीर्घ दीर्घ)s1970);

	ret = mc13xxx_rtc_irq_enable_unlocked(dev, alarm->enabled,
			MC13XXX_IRQ_TODA);
	अगर (unlikely(ret))
		जाओ out;

	days = भाग_s64_rem(s1970, SEC_PER_DAY, &seconds);

	ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13XXX_RTCDAYA, days);
	अगर (unlikely(ret))
		जाओ out;

	ret = mc13xxx_reg_ग_लिखो(priv->mc13xxx, MC13XXX_RTCTODA, seconds);

out:
	mc13xxx_unlock(priv->mc13xxx);

	वापस ret;
पूर्ण

अटल irqवापस_t mc13xxx_rtc_alarm_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mc13xxx_rtc *priv = dev;
	काष्ठा mc13xxx *mc13xxx = priv->mc13xxx;

	rtc_update_irq(priv->rtc, 1, RTC_IRQF | RTC_AF);

	mc13xxx_irq_ack(mc13xxx, irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops mc13xxx_rtc_ops = अणु
	.पढ़ो_समय = mc13xxx_rtc_पढ़ो_समय,
	.set_समय = mc13xxx_rtc_set_समय,
	.पढ़ो_alarm = mc13xxx_rtc_पढ़ो_alarm,
	.set_alarm = mc13xxx_rtc_set_alarm,
	.alarm_irq_enable = mc13xxx_rtc_alarm_irq_enable,
पूर्ण;

अटल irqवापस_t mc13xxx_rtc_reset_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mc13xxx_rtc *priv = dev;
	काष्ठा mc13xxx *mc13xxx = priv->mc13xxx;

	priv->valid = 0;

	mc13xxx_irq_mask(mc13xxx, irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init mc13xxx_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा mc13xxx_rtc *priv;
	काष्ठा mc13xxx *mc13xxx;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mc13xxx = dev_get_drvdata(pdev->dev.parent);
	priv->mc13xxx = mc13xxx;
	priv->valid = 1;

	priv->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(priv->rtc))
		वापस PTR_ERR(priv->rtc);
	platक्रमm_set_drvdata(pdev, priv);

	priv->rtc->ops = &mc13xxx_rtc_ops;
	/* 15bit days + hours, minutes, seconds */
	priv->rtc->range_max = (समयu64_t)(1 << 15) * SEC_PER_DAY - 1;

	mc13xxx_lock(mc13xxx);

	mc13xxx_irq_ack(mc13xxx, MC13XXX_IRQ_RTCRST);

	ret = mc13xxx_irq_request(mc13xxx, MC13XXX_IRQ_RTCRST,
			mc13xxx_rtc_reset_handler, DRIVER_NAME, priv);
	अगर (ret)
		जाओ err_irq_request;

	ret = mc13xxx_irq_request_nounmask(mc13xxx, MC13XXX_IRQ_TODA,
			mc13xxx_rtc_alarm_handler, DRIVER_NAME, priv);
	अगर (ret)
		जाओ err_irq_request;

	mc13xxx_unlock(mc13xxx);

	ret = devm_rtc_रेजिस्टर_device(priv->rtc);
	अगर (ret) अणु
		mc13xxx_lock(mc13xxx);
		जाओ err_irq_request;
	पूर्ण

	वापस 0;

err_irq_request:
	mc13xxx_irq_मुक्त(mc13xxx, MC13XXX_IRQ_TODA, priv);
	mc13xxx_irq_मुक्त(mc13xxx, MC13XXX_IRQ_RTCRST, priv);

	mc13xxx_unlock(mc13xxx);

	वापस ret;
पूर्ण

अटल पूर्णांक mc13xxx_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13xxx_rtc *priv = platक्रमm_get_drvdata(pdev);

	mc13xxx_lock(priv->mc13xxx);

	mc13xxx_irq_मुक्त(priv->mc13xxx, MC13XXX_IRQ_TODA, priv);
	mc13xxx_irq_मुक्त(priv->mc13xxx, MC13XXX_IRQ_RTCRST, priv);

	mc13xxx_unlock(priv->mc13xxx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mc13xxx_rtc_idtable[] = अणु
	अणु
		.name = "mc13783-rtc",
	पूर्ण, अणु
		.name = "mc13892-rtc",
	पूर्ण, अणु
		.name = "mc34708-rtc",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mc13xxx_rtc_idtable);

अटल काष्ठा platक्रमm_driver mc13xxx_rtc_driver = अणु
	.id_table = mc13xxx_rtc_idtable,
	.हटाओ = mc13xxx_rtc_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(mc13xxx_rtc_driver, &mc13xxx_rtc_probe);

MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_DESCRIPTION("RTC driver for Freescale MC13XXX PMIC");
MODULE_LICENSE("GPL v2");
