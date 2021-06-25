<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel Panic LED Trigger
 *
 * Copyright 2016 Ezequiel Garcia <ezequiel@vanguardiasur.com.ar>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/leds.h>
#समावेश "../leds.h"

अटल काष्ठा led_trigger *trigger;

/*
 * This is called in a special context by the atomic panic
 * notअगरier. This means the trigger can be changed without
 * worrying about locking.
 */
अटल व्योम led_trigger_set_panic(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा led_trigger *trig;

	list_क्रम_each_entry(trig, &trigger_list, next_trig) अणु
		अगर (म_भेद("panic", trig->name))
			जारी;
		अगर (led_cdev->trigger)
			list_del(&led_cdev->trig_list);
		list_add_tail(&led_cdev->trig_list, &trig->led_cdevs);

		/* Aव्योम the delayed blink path */
		led_cdev->blink_delay_on = 0;
		led_cdev->blink_delay_off = 0;

		led_cdev->trigger = trig;
		अगर (trig->activate)
			trig->activate(led_cdev);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक led_trigger_panic_notअगरier(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ code, व्योम *unused)
अणु
	काष्ठा led_classdev *led_cdev;

	list_क्रम_each_entry(led_cdev, &leds_list, node)
		अगर (led_cdev->flags & LED_PANIC_INDICATOR)
			led_trigger_set_panic(led_cdev);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block led_trigger_panic_nb = अणु
	.notअगरier_call = led_trigger_panic_notअगरier,
पूर्ण;

अटल दीर्घ led_panic_blink(पूर्णांक state)
अणु
	led_trigger_event(trigger, state ? LED_FULL : LED_OFF);
	वापस 0;
पूर्ण

अटल पूर्णांक __init ledtrig_panic_init(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &led_trigger_panic_nb);

	led_trigger_रेजिस्टर_simple("panic", &trigger);
	panic_blink = led_panic_blink;
	वापस 0;
पूर्ण
device_initcall(ledtrig_panic_init);
