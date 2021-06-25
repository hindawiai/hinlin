<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	DEC platक्रमm devices.
 *
 *	Copyright (c) 2014  Maciej W. Rozycki
 */

#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/platक्रमm_device.h>

अटल काष्ठा resource dec_rtc_resources[] = अणु
	अणु
		.name = "rtc",
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा cmos_rtc_board_info dec_rtc_info = अणु
	.flags = CMOS_RTC_FLAGS_NOFREQ,
	.address_space = 64,
पूर्ण;

अटल काष्ठा platक्रमm_device dec_rtc_device = अणु
	.name = "rtc_cmos",
	.id = PLATFORM_DEVID_NONE,
	.dev.platक्रमm_data = &dec_rtc_info,
	.resource = dec_rtc_resources,
	.num_resources = ARRAY_SIZE(dec_rtc_resources),
पूर्ण;

अटल पूर्णांक __init dec_add_devices(व्योम)
अणु
	dec_rtc_resources[0].start = RTC_PORT(0);
	dec_rtc_resources[0].end = RTC_PORT(0) + dec_kn_slot_size - 1;
	वापस platक्रमm_device_रेजिस्टर(&dec_rtc_device);
पूर्ण

device_initcall(dec_add_devices);
