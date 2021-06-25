<शैली गुरु>
/* rtc-starfire.c: Starfire platक्रमm RTC driver.
 *
 * Author: David S. Miller
 * License: GPL
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/oplib.h>

अटल u32 starfire_get_समय(व्योम)
अणु
	अटल अक्षर obp_gettod[32];
	अटल u32 unix_tod;

	प्र_लिखो(obp_gettod, "h# %08x unix-gettod",
		(अचिन्हित पूर्णांक) (दीर्घ) &unix_tod);
	prom_feval(obp_gettod);

	वापस unix_tod;
पूर्ण

अटल पूर्णांक starfire_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	rtc_समय64_to_पंचांग(starfire_get_समय(), पंचांग);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops starfire_rtc_ops = अणु
	.पढ़ो_समय	= starfire_पढ़ो_समय,
पूर्ण;

अटल पूर्णांक __init starfire_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &starfire_rtc_ops;
	rtc->range_max = U32_MAX;

	platक्रमm_set_drvdata(pdev, rtc);

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver starfire_rtc_driver = अणु
	.driver		= अणु
		.name	= "rtc-starfire",
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver_probe(starfire_rtc_driver, starfire_rtc_probe);
