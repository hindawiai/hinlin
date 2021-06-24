<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PS3 RTC Driver
 *
 * Copyright 2009 Sony Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3.h>


अटल u64 पढ़ो_rtc(व्योम)
अणु
	पूर्णांक result;
	u64 rtc_val;
	u64 tb_val;

	result = lv1_get_rtc(&rtc_val, &tb_val);
	BUG_ON(result);

	वापस rtc_val;
पूर्ण

अटल पूर्णांक ps3_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	rtc_समय64_to_पंचांग(पढ़ो_rtc() + ps3_os_area_get_rtc_dअगरf(), पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक ps3_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	ps3_os_area_set_rtc_dअगरf(rtc_पंचांग_to_समय64(पंचांग) - पढ़ो_rtc());
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ps3_rtc_ops = अणु
	.पढ़ो_समय = ps3_get_समय,
	.set_समय = ps3_set_समय,
पूर्ण;

अटल पूर्णांक __init ps3_rtc_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rtc_device *rtc;

	rtc = devm_rtc_allocate_device(&dev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &ps3_rtc_ops;
	rtc->range_max = U64_MAX;

	platक्रमm_set_drvdata(dev, rtc);

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver ps3_rtc_driver = अणु
	.driver = अणु
		.name = "rtc-ps3",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(ps3_rtc_driver, ps3_rtc_probe);

MODULE_AUTHOR("Sony Corporation");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ps3 RTC driver");
MODULE_ALIAS("platform:rtc-ps3");
