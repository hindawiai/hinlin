<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Camera Flash and Torch On/Off Trigger
 *
 * based on ledtrig-ide-disk.c
 *
 * Copyright 2013 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>

DEFINE_LED_TRIGGER(ledtrig_flash);
DEFINE_LED_TRIGGER(ledtrig_torch);

व्योम ledtrig_flash_ctrl(bool on)
अणु
	क्रमागत led_brightness brt = on ? LED_FULL : LED_OFF;

	led_trigger_event(ledtrig_flash, brt);
पूर्ण
EXPORT_SYMBOL_GPL(ledtrig_flash_ctrl);

व्योम ledtrig_torch_ctrl(bool on)
अणु
	क्रमागत led_brightness brt = on ? LED_FULL : LED_OFF;

	led_trigger_event(ledtrig_torch, brt);
पूर्ण
EXPORT_SYMBOL_GPL(ledtrig_torch_ctrl);

अटल पूर्णांक __init ledtrig_camera_init(व्योम)
अणु
	led_trigger_रेजिस्टर_simple("flash", &ledtrig_flash);
	led_trigger_रेजिस्टर_simple("torch", &ledtrig_torch);
	वापस 0;
पूर्ण
module_init(ledtrig_camera_init);

अटल व्योम __निकास ledtrig_camera_निकास(व्योम)
अणु
	led_trigger_unरेजिस्टर_simple(ledtrig_torch);
	led_trigger_unरेजिस्टर_simple(ledtrig_flash);
पूर्ण
module_निकास(ledtrig_camera_निकास);

MODULE_DESCRIPTION("LED Trigger for Camera Flash/Torch Control");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL v2");
