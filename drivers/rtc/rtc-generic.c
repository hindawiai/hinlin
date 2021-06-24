<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* rtc-generic: RTC driver using the generic RTC असलtraction
 *
 * Copyright (C) 2008 Kyle McMartin <kyle@mcmartin.ca>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>

अटल पूर्णांक __init generic_rtc_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rtc_device *rtc;
	स्थिर काष्ठा rtc_class_ops *ops = dev_get_platdata(&dev->dev);

	rtc = devm_rtc_device_रेजिस्टर(&dev->dev, "rtc-generic",
					ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	platक्रमm_set_drvdata(dev, rtc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver generic_rtc_driver = अणु
	.driver = अणु
		.name = "rtc-generic",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(generic_rtc_driver, generic_rtc_probe);

MODULE_AUTHOR("Kyle McMartin <kyle@mcmartin.ca>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Generic RTC driver");
MODULE_ALIAS("platform:rtc-generic");
