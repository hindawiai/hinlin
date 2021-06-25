<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* rtc-sun4v.c: Hypervisor based RTC क्रम SUN4V प्रणालीs.
 *
 * Author: David S. Miller
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/hypervisor.h>

अटल अचिन्हित दीर्घ hypervisor_get_समय(व्योम)
अणु
	अचिन्हित दीर्घ ret, समय;
	पूर्णांक retries = 10000;

retry:
	ret = sun4v_tod_get(&समय);
	अगर (ret == HV_EOK)
		वापस समय;
	अगर (ret == HV_EWOULDBLOCK) अणु
		अगर (--retries > 0) अणु
			udelay(100);
			जाओ retry;
		पूर्ण
		pr_warn("tod_get() timed out.\n");
		वापस 0;
	पूर्ण
	pr_warn("tod_get() not supported.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sun4v_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	rtc_समय64_to_पंचांग(hypervisor_get_समय(), पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक hypervisor_set_समय(अचिन्हित दीर्घ secs)
अणु
	अचिन्हित दीर्घ ret;
	पूर्णांक retries = 10000;

retry:
	ret = sun4v_tod_set(secs);
	अगर (ret == HV_EOK)
		वापस 0;
	अगर (ret == HV_EWOULDBLOCK) अणु
		अगर (--retries > 0) अणु
			udelay(100);
			जाओ retry;
		पूर्ण
		pr_warn("tod_set() timed out.\n");
		वापस -EAGAIN;
	पूर्ण
	pr_warn("tod_set() not supported.\n");
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sun4v_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	वापस hypervisor_set_समय(rtc_पंचांग_to_समय64(पंचांग));
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sun4v_rtc_ops = अणु
	.पढ़ो_समय	= sun4v_पढ़ो_समय,
	.set_समय	= sun4v_set_समय,
पूर्ण;

अटल पूर्णांक __init sun4v_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &sun4v_rtc_ops;
	rtc->range_max = U64_MAX;
	platक्रमm_set_drvdata(pdev, rtc);

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver sun4v_rtc_driver = अणु
	.driver		= अणु
		.name	= "rtc-sun4v",
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver_probe(sun4v_rtc_driver, sun4v_rtc_probe);
