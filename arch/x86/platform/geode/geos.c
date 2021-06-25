<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System Specअगरic setup क्रम Traverse Technologies GEOS.
 * At the moment this means setup of GPIO control of LEDs.
 *
 * Copyright (C) 2008 Constantin Baranov <स्थिर@mimas.ru>
 * Copyright (C) 2011 Ed Wildgoose <kernel@wildgooses.com>
 *                and Philip Prindeville <philipp@redfish-solutions.com>
 *
 * TODO: There are large similarities with leds-net5501.c
 * by Alessandro Zummo <a.zummo@towertech.it>
 * In the future leds-net5501.c should be migrated over to platक्रमm
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/माला.स>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/dmi.h>

#समावेश <यंत्र/geode.h>

अटल काष्ठा gpio_keys_button geos_gpio_buttons[] = अणु
	अणु
		.code = KEY_RESTART,
		.gpio = 3,
		.active_low = 1,
		.desc = "Reset button",
		.type = EV_KEY,
		.wakeup = 0,
		.debounce_पूर्णांकerval = 100,
		.can_disable = 0,
	पूर्ण
पूर्ण;
अटल काष्ठा gpio_keys_platक्रमm_data geos_buttons_data = अणु
	.buttons = geos_gpio_buttons,
	.nbuttons = ARRAY_SIZE(geos_gpio_buttons),
	.poll_पूर्णांकerval = 20,
पूर्ण;

अटल काष्ठा platक्रमm_device geos_buttons_dev = अणु
	.name = "gpio-keys-polled",
	.id = 1,
	.dev = अणु
		.platक्रमm_data = &geos_buttons_data,
	पूर्ण
पूर्ण;

अटल काष्ठा gpio_led geos_leds[] = अणु
	अणु
		.name = "geos:1",
		.शेष_trigger = "default-on",
	पूर्ण,
	अणु
		.name = "geos:2",
		.शेष_trigger = "default-off",
	पूर्ण,
	अणु
		.name = "geos:3",
		.शेष_trigger = "default-off",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data geos_leds_data = अणु
	.num_leds = ARRAY_SIZE(geos_leds),
	.leds = geos_leds,
पूर्ण;

अटल काष्ठा gpiod_lookup_table geos_leds_gpio_table = अणु
	.dev_id = "leds-gpio",
	.table = अणु
		/* The Geode GPIOs should be on the CS5535 companion chip */
		GPIO_LOOKUP_IDX("cs5535-gpio", 6, शून्य, 0, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("cs5535-gpio", 25, शून्य, 1, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("cs5535-gpio", 27, शून्य, 2, GPIO_ACTIVE_LOW),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device geos_leds_dev = अणु
	.name = "leds-gpio",
	.id = -1,
	.dev.platक्रमm_data = &geos_leds_data,
पूर्ण;

अटल काष्ठा platक्रमm_device *geos_devs[] __initdata = अणु
	&geos_buttons_dev,
	&geos_leds_dev,
पूर्ण;

अटल व्योम __init रेजिस्टर_geos(व्योम)
अणु
	/* Setup LED control through leds-gpio driver */
	gpiod_add_lookup_table(&geos_leds_gpio_table);
	platक्रमm_add_devices(geos_devs, ARRAY_SIZE(geos_devs));
पूर्ण

अटल पूर्णांक __init geos_init(व्योम)
अणु
	स्थिर अक्षर *venकरोr, *product;

	अगर (!is_geode())
		वापस 0;

	venकरोr = dmi_get_प्रणाली_info(DMI_SYS_VENDOR);
	अगर (!venकरोr || म_भेद(venकरोr, "Traverse Technologies"))
		वापस 0;

	product = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (!product || म_भेद(product, "Geos"))
		वापस 0;

	prपूर्णांकk(KERN_INFO "%s: system is recognized as \"%s %s\"\n",
	       KBUILD_MODNAME, venकरोr, product);

	रेजिस्टर_geos();

	वापस 0;
पूर्ण
device_initcall(geos_init);
