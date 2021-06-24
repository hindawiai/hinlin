<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED MTD trigger
 *
 * Copyright 2016 Ezequiel Garcia <ezequiel@vanguardiasur.com.ar>
 *
 * Based on LED IDE-Disk Activity Trigger
 *
 * Copyright 2006 Openedhand Ltd.
 *
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>

#घोषणा BLINK_DELAY 30

DEFINE_LED_TRIGGER(ledtrig_mtd);
DEFINE_LED_TRIGGER(ledtrig_nand);

व्योम ledtrig_mtd_activity(व्योम)
अणु
	अचिन्हित दीर्घ blink_delay = BLINK_DELAY;

	led_trigger_blink_oneshot(ledtrig_mtd,
				  &blink_delay, &blink_delay, 0);
	led_trigger_blink_oneshot(ledtrig_nand,
				  &blink_delay, &blink_delay, 0);
पूर्ण
EXPORT_SYMBOL(ledtrig_mtd_activity);

अटल पूर्णांक __init ledtrig_mtd_init(व्योम)
अणु
	led_trigger_रेजिस्टर_simple("mtd", &ledtrig_mtd);
	led_trigger_रेजिस्टर_simple("nand-disk", &ledtrig_nand);

	वापस 0;
पूर्ण
device_initcall(ledtrig_mtd_init);
