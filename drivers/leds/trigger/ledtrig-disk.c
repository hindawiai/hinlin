<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Disk Activity Trigger
 *
 * Copyright 2006 Openedhand Ltd.
 *
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>

#घोषणा BLINK_DELAY 30

DEFINE_LED_TRIGGER(ledtrig_disk);
DEFINE_LED_TRIGGER(ledtrig_disk_पढ़ो);
DEFINE_LED_TRIGGER(ledtrig_disk_ग_लिखो);
DEFINE_LED_TRIGGER(ledtrig_ide);

व्योम ledtrig_disk_activity(bool ग_लिखो)
अणु
	अचिन्हित दीर्घ blink_delay = BLINK_DELAY;

	led_trigger_blink_oneshot(ledtrig_disk,
				  &blink_delay, &blink_delay, 0);
	led_trigger_blink_oneshot(ledtrig_ide,
				  &blink_delay, &blink_delay, 0);
	अगर (ग_लिखो)
		led_trigger_blink_oneshot(ledtrig_disk_ग_लिखो,
					  &blink_delay, &blink_delay, 0);
	अन्यथा
		led_trigger_blink_oneshot(ledtrig_disk_पढ़ो,
					  &blink_delay, &blink_delay, 0);
पूर्ण
EXPORT_SYMBOL(ledtrig_disk_activity);

अटल पूर्णांक __init ledtrig_disk_init(व्योम)
अणु
	led_trigger_रेजिस्टर_simple("disk-activity", &ledtrig_disk);
	led_trigger_रेजिस्टर_simple("disk-read", &ledtrig_disk_पढ़ो);
	led_trigger_रेजिस्टर_simple("disk-write", &ledtrig_disk_ग_लिखो);
	led_trigger_रेजिस्टर_simple("ide-disk", &ledtrig_ide);

	वापस 0;
पूर्ण
device_initcall(ledtrig_disk_init);
