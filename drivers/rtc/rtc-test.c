<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * An RTC test device/driver
 * Copyright (C) 2005 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MAX_RTC_TEST 3

काष्ठा rtc_test_data अणु
	काष्ठा rtc_device *rtc;
	समय64_t offset;
	काष्ठा समयr_list alarm;
	bool alarm_en;
पूर्ण;

अटल काष्ठा platक्रमm_device *pdev[MAX_RTC_TEST];

अटल पूर्णांक test_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_test_data *rtd = dev_get_drvdata(dev);
	समय64_t alarm;

	alarm = (rtd->alarm.expires - jअगरfies) / HZ;
	alarm += kसमय_get_real_seconds() + rtd->offset;

	rtc_समय64_to_पंचांग(alarm, &alrm->समय);
	alrm->enabled = rtd->alarm_en;

	वापस 0;
पूर्ण

अटल पूर्णांक test_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rtc_test_data *rtd = dev_get_drvdata(dev);
	kसमय_प्रकार समयout;
	u64 expires;

	समयout = rtc_पंचांग_to_समय64(&alrm->समय) - kसमय_get_real_seconds();
	समयout -= rtd->offset;

	del_समयr(&rtd->alarm);

	expires = jअगरfies + समयout * HZ;
	अगर (expires > U32_MAX)
		expires = U32_MAX;

	rtd->alarm.expires = expires;

	अगर (alrm->enabled)
		add_समयr(&rtd->alarm);

	rtd->alarm_en = alrm->enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक test_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_test_data *rtd = dev_get_drvdata(dev);

	rtc_समय64_to_पंचांग(kसमय_get_real_seconds() + rtd->offset, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक test_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_test_data *rtd = dev_get_drvdata(dev);

	rtd->offset = rtc_पंचांग_to_समय64(पंचांग) - kसमय_get_real_seconds();

	वापस 0;
पूर्ण

अटल पूर्णांक test_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	काष्ठा rtc_test_data *rtd = dev_get_drvdata(dev);

	rtd->alarm_en = enable;
	अगर (enable)
		add_समयr(&rtd->alarm);
	अन्यथा
		del_समयr(&rtd->alarm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops test_rtc_ops_noalm = अणु
	.पढ़ो_समय = test_rtc_पढ़ो_समय,
	.set_समय = test_rtc_set_समय,
	.alarm_irq_enable = test_rtc_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा rtc_class_ops test_rtc_ops = अणु
	.पढ़ो_समय = test_rtc_पढ़ो_समय,
	.set_समय = test_rtc_set_समय,
	.पढ़ो_alarm = test_rtc_पढ़ो_alarm,
	.set_alarm = test_rtc_set_alarm,
	.alarm_irq_enable = test_rtc_alarm_irq_enable,
पूर्ण;

अटल व्योम test_rtc_alarm_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा rtc_test_data *rtd = from_समयr(rtd, t, alarm);

	rtc_update_irq(rtd->rtc, 1, RTC_AF | RTC_IRQF);
पूर्ण

अटल पूर्णांक test_probe(काष्ठा platक्रमm_device *plat_dev)
अणु
	काष्ठा rtc_test_data *rtd;

	rtd = devm_kzalloc(&plat_dev->dev, माप(*rtd), GFP_KERNEL);
	अगर (!rtd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(plat_dev, rtd);

	rtd->rtc = devm_rtc_allocate_device(&plat_dev->dev);
	अगर (IS_ERR(rtd->rtc))
		वापस PTR_ERR(rtd->rtc);

	चयन (plat_dev->id) अणु
	हाल 0:
		rtd->rtc->ops = &test_rtc_ops_noalm;
		अवरोध;
	शेष:
		rtd->rtc->ops = &test_rtc_ops;
		device_init_wakeup(&plat_dev->dev, 1);
	पूर्ण

	समयr_setup(&rtd->alarm, test_rtc_alarm_handler, 0);
	rtd->alarm.expires = 0;

	वापस devm_rtc_रेजिस्टर_device(rtd->rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver test_driver = अणु
	.probe	= test_probe,
	.driver = अणु
		.name = "rtc-test",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init test_init(व्योम)
अणु
	पूर्णांक i, err;

	err = platक्रमm_driver_रेजिस्टर(&test_driver);
	अगर (err)
		वापस err;

	err = -ENOMEM;
	क्रम (i = 0; i < MAX_RTC_TEST; i++) अणु
		pdev[i] = platक्रमm_device_alloc("rtc-test", i);
		अगर (!pdev[i])
			जाओ निकास_मुक्त_mem;
	पूर्ण

	क्रम (i = 0; i < MAX_RTC_TEST; i++) अणु
		err = platक्रमm_device_add(pdev[i]);
		अगर (err)
			जाओ निकास_device_del;
	पूर्ण

	वापस 0;

निकास_device_del:
	क्रम (; i > 0; i--)
		platक्रमm_device_del(pdev[i - 1]);

निकास_मुक्त_mem:
	क्रम (i = 0; i < MAX_RTC_TEST; i++)
		platक्रमm_device_put(pdev[i]);

	platक्रमm_driver_unरेजिस्टर(&test_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास test_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_RTC_TEST; i++)
		platक्रमm_device_unरेजिस्टर(pdev[i]);

	platक्रमm_driver_unरेजिस्टर(&test_driver);
पूर्ण

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("RTC test driver/device");
MODULE_LICENSE("GPL v2");

module_init(test_init);
module_निकास(test_निकास);
