<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Kernel Default ON Trigger
 *
 * Copyright 2008 Nick Forbes <nick.क्रमbes@incepta.com>
 *
 * Based on Riअक्षरd Purdie's ledtrig-समयr.c.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश "../leds.h"

अटल पूर्णांक defon_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	led_set_brightness_nosleep(led_cdev, led_cdev->max_brightness);
	वापस 0;
पूर्ण

अटल काष्ठा led_trigger defon_led_trigger = अणु
	.name     = "default-on",
	.activate = defon_trig_activate,
पूर्ण;
module_led_trigger(defon_led_trigger);

MODULE_AUTHOR("Nick Forbes <nick.forbes@incepta.com>");
MODULE_DESCRIPTION("Default-ON LED trigger");
MODULE_LICENSE("GPL v2");
