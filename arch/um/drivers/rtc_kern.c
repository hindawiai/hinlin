<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Intel Corporation
 * Author: Johannes Berg <johannes@sipsolutions.net>
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समय-पूर्णांकernal.h>
#समावेश <linux/suspend.h>
#समावेश <linux/err.h>
#समावेश <linux/rtc.h>
#समावेश <kern_util.h>
#समावेश <irq_kern.h>
#समावेश <os.h>
#समावेश "rtc.h"

अटल समय64_t uml_rtc_alarm_समय;
अटल bool uml_rtc_alarm_enabled;
अटल काष्ठा rtc_device *uml_rtc;
अटल पूर्णांक uml_rtc_irq_fd, uml_rtc_irq;

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT

अटल व्योम uml_rtc_समय_प्रकारravel_alarm(काष्ठा समय_प्रकारravel_event *ev)
अणु
	uml_rtc_send_समयtravel_alarm();
पूर्ण

अटल काष्ठा समय_प्रकारravel_event uml_rtc_alarm_event = अणु
	.fn = uml_rtc_समय_प्रकारravel_alarm,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक uml_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा बारpec64 ts;

	/* Use this to get correct समय in समय-travel mode */
	पढ़ो_persistent_घड़ी64(&ts);
	rtc_समय64_to_पंचांग(बारpec64_to_kसमय(ts) / NSEC_PER_SEC, पंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक uml_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	rtc_समय64_to_पंचांग(uml_rtc_alarm_समय, &alrm->समय);
	alrm->enabled = uml_rtc_alarm_enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक uml_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित दीर्घ दीर्घ secs;

	अगर (!enable && !uml_rtc_alarm_enabled)
		वापस 0;

	uml_rtc_alarm_enabled = enable;

	secs = uml_rtc_alarm_समय - kसमय_get_real_seconds();

	अगर (समय_प्रकारravel_mode == TT_MODE_OFF) अणु
		अगर (!enable) अणु
			uml_rtc_disable_alarm();
			वापस 0;
		पूर्ण

		/* enable or update */
		वापस uml_rtc_enable_alarm(secs);
	पूर्ण अन्यथा अणु
		समय_प्रकारravel_del_event(&uml_rtc_alarm_event);

		अगर (enable)
			समय_प्रकारravel_add_event_rel(&uml_rtc_alarm_event,
						  secs * NSEC_PER_SEC);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uml_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	uml_rtc_alarm_irq_enable(dev, 0);
	uml_rtc_alarm_समय = rtc_पंचांग_to_समय64(&alrm->समय);
	uml_rtc_alarm_irq_enable(dev, alrm->enabled);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops uml_rtc_ops = अणु
	.पढ़ो_समय = uml_rtc_पढ़ो_समय,
	.पढ़ो_alarm = uml_rtc_पढ़ो_alarm,
	.alarm_irq_enable = uml_rtc_alarm_irq_enable,
	.set_alarm = uml_rtc_set_alarm,
पूर्ण;

अटल irqवापस_t uml_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ दीर्घ c = 0;

	/* alarm triggered, it's now off */
	uml_rtc_alarm_enabled = false;

	os_पढ़ो_file(uml_rtc_irq_fd, &c, माप(c));
	WARN_ON(c == 0);

	pm_प्रणाली_wakeup();
	rtc_update_irq(uml_rtc, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uml_rtc_setup(व्योम)
अणु
	पूर्णांक err;

	err = uml_rtc_start(समय_प्रकारravel_mode != TT_MODE_OFF);
	अगर (WARN(err < 0, "err = %d\n", err))
		वापस err;

	uml_rtc_irq_fd = err;

	err = um_request_irq(UM_IRQ_ALLOC, uml_rtc_irq_fd, IRQ_READ,
			     uml_rtc_पूर्णांकerrupt, 0, "rtc", शून्य);
	अगर (err < 0) अणु
		uml_rtc_stop(समय_प्रकारravel_mode != TT_MODE_OFF);
		वापस err;
	पूर्ण

	irq_set_irq_wake(err, 1);

	uml_rtc_irq = err;
	वापस 0;
पूर्ण

अटल व्योम uml_rtc_cleanup(व्योम)
अणु
	um_मुक्त_irq(uml_rtc_irq, शून्य);
	uml_rtc_stop(समय_प्रकारravel_mode != TT_MODE_OFF);
पूर्ण

अटल पूर्णांक uml_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;

	err = uml_rtc_setup();
	अगर (err)
		वापस err;

	uml_rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(uml_rtc)) अणु
		err = PTR_ERR(uml_rtc);
		जाओ cleanup;
	पूर्ण

	uml_rtc->ops = &uml_rtc_ops;

	device_init_wakeup(&pdev->dev, 1);

	err = devm_rtc_रेजिस्टर_device(uml_rtc);
	अगर (err)
		जाओ cleanup;

	वापस 0;
cleanup:
	uml_rtc_cleanup();
	वापस err;
पूर्ण

अटल पूर्णांक uml_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	device_init_wakeup(&pdev->dev, 0);
	uml_rtc_cleanup();
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver uml_rtc_driver = अणु
	.probe = uml_rtc_probe,
	.हटाओ = uml_rtc_हटाओ,
	.driver = अणु
		.name = "uml-rtc",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init uml_rtc_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक err;

	err = platक्रमm_driver_रेजिस्टर(&uml_rtc_driver);
	अगर (err)
		वापस err;

	pdev = platक्रमm_device_alloc("uml-rtc", 0);
	अगर (!pdev) अणु
		err = -ENOMEM;
		जाओ unरेजिस्टर;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err)
		जाओ unरेजिस्टर;
	वापस 0;

unरेजिस्टर:
	platक्रमm_device_put(pdev);
	platक्रमm_driver_unरेजिस्टर(&uml_rtc_driver);
	वापस err;
पूर्ण
device_initcall(uml_rtc_init);
