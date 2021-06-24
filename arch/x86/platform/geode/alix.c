<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System Specअगरic setup क्रम PCEngines ALIX.
 * At the moment this means setup of GPIO control of LEDs
 * on Alix.2/3/6 boards.
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
#समावेश <linux/moduleparam.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/dmi.h>

#समावेश <यंत्र/geode.h>

#घोषणा BIOS_SIGNATURE_TINYBIOS		0xf0000
#घोषणा BIOS_SIGNATURE_COREBOOT		0x500
#घोषणा BIOS_REGION_SIZE		0x10000

/*
 * This driver is not modular, but to keep back compatibility
 * with existing use हालs, continuing with module_param is
 * the easiest way क्रमward.
 */
अटल bool क्रमce = 0;
module_param(क्रमce, bool, 0444);
/* FIXME: Award bios is not स्वतःmatically detected as Alix platक्रमm */
MODULE_PARM_DESC(क्रमce, "Force detection as ALIX.2/ALIX.3 platform");

अटल काष्ठा gpio_keys_button alix_gpio_buttons[] = अणु
	अणु
		.code			= KEY_RESTART,
		.gpio			= 24,
		.active_low		= 1,
		.desc			= "Reset button",
		.type			= EV_KEY,
		.wakeup			= 0,
		.debounce_पूर्णांकerval	= 100,
		.can_disable		= 0,
	पूर्ण
पूर्ण;
अटल काष्ठा gpio_keys_platक्रमm_data alix_buttons_data = अणु
	.buttons			= alix_gpio_buttons,
	.nbuttons			= ARRAY_SIZE(alix_gpio_buttons),
	.poll_पूर्णांकerval			= 20,
पूर्ण;

अटल काष्ठा platक्रमm_device alix_buttons_dev = अणु
	.name				= "gpio-keys-polled",
	.id				= 1,
	.dev = अणु
		.platक्रमm_data		= &alix_buttons_data,
	पूर्ण
पूर्ण;

अटल काष्ठा gpio_led alix_leds[] = अणु
	अणु
		.name = "alix:1",
		.शेष_trigger = "default-on",
	पूर्ण,
	अणु
		.name = "alix:2",
		.शेष_trigger = "default-off",
	पूर्ण,
	अणु
		.name = "alix:3",
		.शेष_trigger = "default-off",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data alix_leds_data = अणु
	.num_leds = ARRAY_SIZE(alix_leds),
	.leds = alix_leds,
पूर्ण;

अटल काष्ठा gpiod_lookup_table alix_leds_gpio_table = अणु
	.dev_id = "leds-gpio",
	.table = अणु
		/* The Geode GPIOs should be on the CS5535 companion chip */
		GPIO_LOOKUP_IDX("cs5535-gpio", 6, शून्य, 0, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("cs5535-gpio", 25, शून्य, 1, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("cs5535-gpio", 27, शून्य, 2, GPIO_ACTIVE_LOW),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device alix_leds_dev = अणु
	.name = "leds-gpio",
	.id = -1,
	.dev.platक्रमm_data = &alix_leds_data,
पूर्ण;

अटल काष्ठा platक्रमm_device *alix_devs[] __initdata = अणु
	&alix_buttons_dev,
	&alix_leds_dev,
पूर्ण;

अटल व्योम __init रेजिस्टर_alix(व्योम)
अणु
	/* Setup LED control through leds-gpio driver */
	gpiod_add_lookup_table(&alix_leds_gpio_table);
	platक्रमm_add_devices(alix_devs, ARRAY_SIZE(alix_devs));
पूर्ण

अटल bool __init alix_present(अचिन्हित दीर्घ bios_phys,
				स्थिर अक्षर *alix_sig,
				माप_प्रकार alix_sig_len)
अणु
	स्थिर माप_प्रकार bios_len = BIOS_REGION_SIZE;
	स्थिर अक्षर *bios_virt;
	स्थिर अक्षर *scan_end;
	स्थिर अक्षर *p;
	अक्षर name[64];

	अगर (क्रमce) अणु
		prपूर्णांकk(KERN_NOTICE "%s: forced to skip BIOS test, "
		       "assume system is ALIX.2/ALIX.3\n",
		       KBUILD_MODNAME);
		वापस true;
	पूर्ण

	bios_virt = phys_to_virt(bios_phys);
	scan_end = bios_virt + bios_len - (alix_sig_len + 2);
	क्रम (p = bios_virt; p < scan_end; p++) अणु
		स्थिर अक्षर *tail;
		अक्षर *a;

		अगर (स_भेद(p, alix_sig, alix_sig_len) != 0)
			जारी;

		स_नकल(name, p, माप(name));

		/* हटाओ the first \0 अक्षरacter from string */
		a = म_अक्षर(name, '\0');
		अगर (a)
			*a = ' ';

		/* cut the string at a newline */
		a = म_अक्षर(name, '\r');
		अगर (a)
			*a = '\0';

		tail = p + alix_sig_len;
		अगर ((tail[0] == '2' || tail[0] == '3' || tail[0] == '6')) अणु
			prपूर्णांकk(KERN_INFO
			       "%s: system is recognized as \"%s\"\n",
			       KBUILD_MODNAME, name);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool __init alix_present_dmi(व्योम)
अणु
	स्थिर अक्षर *venकरोr, *product;

	venकरोr = dmi_get_प्रणाली_info(DMI_SYS_VENDOR);
	अगर (!venकरोr || म_भेद(venकरोr, "PC Engines"))
		वापस false;

	product = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (!product || (म_भेद(product, "ALIX.2D") && म_भेद(product, "ALIX.6")))
		वापस false;

	prपूर्णांकk(KERN_INFO "%s: system is recognized as \"%s %s\"\n",
	       KBUILD_MODNAME, venकरोr, product);

	वापस true;
पूर्ण

अटल पूर्णांक __init alix_init(व्योम)
अणु
	स्थिर अक्षर tinybios_sig[] = "PC Engines ALIX.";
	स्थिर अक्षर coreboot_sig[] = "PC Engines\0ALIX.";

	अगर (!is_geode())
		वापस 0;

	अगर (alix_present(BIOS_SIGNATURE_TINYBIOS, tinybios_sig, माप(tinybios_sig) - 1) ||
	    alix_present(BIOS_SIGNATURE_COREBOOT, coreboot_sig, माप(coreboot_sig) - 1) ||
	    alix_present_dmi())
		रेजिस्टर_alix();

	वापस 0;
पूर्ण
device_initcall(alix_init);
