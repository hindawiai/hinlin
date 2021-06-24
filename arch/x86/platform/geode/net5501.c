<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System Specअगरic setup क्रम Soekris net5501
 * At the moment this means setup of GPIO control of LEDs and buttons
 * on net5501 boards.
 *
 * Copyright (C) 2008-2009 Tower Technologies
 * Written by Alessandro Zummo <a.zummo@towertech.it>
 *
 * Copyright (C) 2008 Constantin Baranov <स्थिर@mimas.ru>
 * Copyright (C) 2011 Ed Wildgoose <kernel@wildgooses.com>
 *                and Philip Prindeville <philipp@redfish-solutions.com>
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

#समावेश <यंत्र/geode.h>

#घोषणा BIOS_REGION_BASE		0xffff0000
#घोषणा BIOS_REGION_SIZE		0x00010000

अटल काष्ठा gpio_keys_button net5501_gpio_buttons[] = अणु
	अणु
		.code = KEY_RESTART,
		.gpio = 24,
		.active_low = 1,
		.desc = "Reset button",
		.type = EV_KEY,
		.wakeup = 0,
		.debounce_पूर्णांकerval = 100,
		.can_disable = 0,
	पूर्ण
पूर्ण;
अटल काष्ठा gpio_keys_platक्रमm_data net5501_buttons_data = अणु
	.buttons = net5501_gpio_buttons,
	.nbuttons = ARRAY_SIZE(net5501_gpio_buttons),
	.poll_पूर्णांकerval = 20,
पूर्ण;

अटल काष्ठा platक्रमm_device net5501_buttons_dev = अणु
	.name = "gpio-keys-polled",
	.id = 1,
	.dev = अणु
		.platक्रमm_data = &net5501_buttons_data,
	पूर्ण
पूर्ण;

अटल काष्ठा gpio_led net5501_leds[] = अणु
	अणु
		.name = "net5501:1",
		.शेष_trigger = "default-on",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data net5501_leds_data = अणु
	.num_leds = ARRAY_SIZE(net5501_leds),
	.leds = net5501_leds,
पूर्ण;

अटल काष्ठा gpiod_lookup_table net5501_leds_gpio_table = अणु
	.dev_id = "leds-gpio",
	.table = अणु
		/* The Geode GPIOs should be on the CS5535 companion chip */
		GPIO_LOOKUP_IDX("cs5535-gpio", 6, शून्य, 0, GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device net5501_leds_dev = अणु
	.name = "leds-gpio",
	.id = -1,
	.dev.platक्रमm_data = &net5501_leds_data,
पूर्ण;

अटल काष्ठा platक्रमm_device *net5501_devs[] __initdata = अणु
	&net5501_buttons_dev,
	&net5501_leds_dev,
पूर्ण;

अटल व्योम __init रेजिस्टर_net5501(व्योम)
अणु
	/* Setup LED control through leds-gpio driver */
	gpiod_add_lookup_table(&net5501_leds_gpio_table);
	platक्रमm_add_devices(net5501_devs, ARRAY_SIZE(net5501_devs));
पूर्ण

काष्ठा net5501_board अणु
	u16	offset;
	u16	len;
	अक्षर	*sig;
पूर्ण;

अटल काष्ठा net5501_board __initdata boards[] = अणु
	अणु 0xb7b, 7, "net5501" पूर्ण,	/* net5501 v1.33/1.33c */
	अणु 0xb1f, 7, "net5501" पूर्ण,	/* net5501 v1.32i */
पूर्ण;

अटल bool __init net5501_present(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *rombase, *bios;
	bool found = false;

	rombase = ioremap(BIOS_REGION_BASE, BIOS_REGION_SIZE - 1);
	अगर (!rombase) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to get rombase\n", KBUILD_MODNAME);
		वापस found;
	पूर्ण

	bios = rombase + 0x20;	/* null terminated */

	अगर (स_भेद(bios, "comBIOS", 7))
		जाओ unmap;

	क्रम (i = 0; i < ARRAY_SIZE(boards); i++) अणु
		अचिन्हित अक्षर *model = rombase + boards[i].offset;

		अगर (!स_भेद(model, boards[i].sig, boards[i].len)) अणु
			prपूर्णांकk(KERN_INFO "%s: system is recognized as \"%s\"\n",
			       KBUILD_MODNAME, model);

			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

unmap:
	iounmap(rombase);
	वापस found;
पूर्ण

अटल पूर्णांक __init net5501_init(व्योम)
अणु
	अगर (!is_geode())
		वापस 0;

	अगर (!net5501_present())
		वापस 0;

	रेजिस्टर_net5501();

	वापस 0;
पूर्ण
device_initcall(net5501_init);
