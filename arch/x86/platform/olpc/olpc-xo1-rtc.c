<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम OLPC XO-1 Real Time Clock (RTC)
 *
 * Copyright (C) 2011 One Laptop per Child
 */

#समावेश <linux/mc146818rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/olpc.h>
#समावेश <यंत्र/x86_init.h>

अटल व्योम rtc_wake_on(काष्ठा device *dev)
अणु
	olpc_xo1_pm_wakeup_set(CS5536_PM_RTC);
पूर्ण

अटल व्योम rtc_wake_off(काष्ठा device *dev)
अणु
	olpc_xo1_pm_wakeup_clear(CS5536_PM_RTC);
पूर्ण

अटल काष्ठा resource rtc_platक्रमm_resource[] = अणु
	[0] = अणु
		.start	= RTC_PORT(0),
		.end	= RTC_PORT(1),
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start	= RTC_IRQ,
		.end	= RTC_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा cmos_rtc_board_info rtc_info = अणु
	.rtc_day_alarm = 0,
	.rtc_mon_alarm = 0,
	.rtc_century = 0,
	.wake_on = rtc_wake_on,
	.wake_off = rtc_wake_off,
पूर्ण;

अटल काष्ठा platक्रमm_device xo1_rtc_device = अणु
	.name = "rtc_cmos",
	.id = -1,
	.num_resources = ARRAY_SIZE(rtc_platक्रमm_resource),
	.dev.platक्रमm_data = &rtc_info,
	.resource = rtc_platक्रमm_resource,
पूर्ण;

अटल पूर्णांक __init xo1_rtc_init(व्योम)
अणु
	पूर्णांक r;
	काष्ठा device_node *node;

	node = of_find_compatible_node(शून्य, शून्य, "olpc,xo1-rtc");
	अगर (!node)
		वापस 0;
	of_node_put(node);

	pr_info("olpc-xo1-rtc: Initializing OLPC XO-1 RTC\n");
	rdmsrl(MSR_RTC_DOMA_OFFSET, rtc_info.rtc_day_alarm);
	rdmsrl(MSR_RTC_MONA_OFFSET, rtc_info.rtc_mon_alarm);
	rdmsrl(MSR_RTC_CEN_OFFSET, rtc_info.rtc_century);

	r = platक्रमm_device_रेजिस्टर(&xo1_rtc_device);
	अगर (r)
		वापस r;

	x86_platक्रमm.legacy.rtc = 0;

	device_init_wakeup(&xo1_rtc_device.dev, 1);
	वापस 0;
पूर्ण
arch_initcall(xo1_rtc_init);
