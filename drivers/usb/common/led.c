<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * LED Triggers क्रम USB Activity
 *
 * Copyright 2014 Michal Sojka <sojka@merica.cz>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/usb.h>
#समावेश "common.h"

#घोषणा BLINK_DELAY 30

अटल अचिन्हित दीर्घ usb_blink_delay = BLINK_DELAY;

DEFINE_LED_TRIGGER(ledtrig_usb_gadget);
DEFINE_LED_TRIGGER(ledtrig_usb_host);

व्योम usb_led_activity(क्रमागत usb_led_event ev)
अणु
	काष्ठा led_trigger *trig = शून्य;

	चयन (ev) अणु
	हाल USB_LED_EVENT_GADGET:
		trig = ledtrig_usb_gadget;
		अवरोध;
	हाल USB_LED_EVENT_HOST:
		trig = ledtrig_usb_host;
		अवरोध;
	पूर्ण
	/* led_trigger_blink_oneshot() handles trig == शून्य gracefully */
	led_trigger_blink_oneshot(trig, &usb_blink_delay, &usb_blink_delay, 0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_led_activity);


व्योम __init ledtrig_usb_init(व्योम)
अणु
	led_trigger_रेजिस्टर_simple("usb-gadget", &ledtrig_usb_gadget);
	led_trigger_रेजिस्टर_simple("usb-host", &ledtrig_usb_host);
पूर्ण

व्योम __निकास ledtrig_usb_निकास(व्योम)
अणु
	led_trigger_unरेजिस्टर_simple(ledtrig_usb_gadget);
	led_trigger_unरेजिस्टर_simple(ledtrig_usb_host);
पूर्ण
