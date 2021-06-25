<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Registration of Cobalt RTC platक्रमm device.
 *
 *  Copyright (C) 2007  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/platक्रमm_device.h>

अटल काष्ठा resource cobalt_rtc_resource[] __initdata = अणु
	अणु
		.start	= 0x70,
		.end	= 0x77,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	अणु
		.start	= RTC_IRQ,
		.end	= RTC_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक cobalt_rtc_add(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक retval;

	pdev = platक्रमm_device_alloc("rtc_cmos", -1);
	अगर (!pdev)
		वापस -ENOMEM;

	retval = platक्रमm_device_add_resources(pdev, cobalt_rtc_resource,
					       ARRAY_SIZE(cobalt_rtc_resource));
	अगर (retval)
		जाओ err_मुक्त_device;

	retval = platक्रमm_device_add(pdev);
	अगर (retval)
		जाओ err_मुक्त_device;

	वापस 0;

err_मुक्त_device:
	platक्रमm_device_put(pdev);

	वापस retval;
पूर्ण
device_initcall(cobalt_rtc_add);
