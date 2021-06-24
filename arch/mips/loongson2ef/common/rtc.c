<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Lemote Fuloong platक्रमm support
 *
 *  Copyright(c) 2010 Arnaud Patard <apatard@mandriva.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mc146818rtc.h>

अटल काष्ठा resource loongson_rtc_resources[] = अणु
	अणु
		.start	= RTC_PORT(0),
		.end	= RTC_PORT(1),
		.flags	= IORESOURCE_IO,
	पूर्ण, अणु
		.start	= RTC_IRQ,
		.end	= RTC_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device loongson_rtc_device = अणु
	.name		= "rtc_cmos",
	.id		= -1,
	.resource	= loongson_rtc_resources,
	.num_resources	= ARRAY_SIZE(loongson_rtc_resources),
पूर्ण;


अटल पूर्णांक __init loongson_rtc_platक्रमm_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&loongson_rtc_device);
	वापस 0;
पूर्ण

device_initcall(loongson_rtc_platक्रमm_init);
