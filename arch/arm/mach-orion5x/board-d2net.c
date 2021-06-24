<शैली गुरु>
/*
 * arch/arm/mach-orion5x/board-d2net.c
 *
 * LaCie d2Network and Big Disk Network NAS setup
 *
 * Copyright (C) 2009 Simon Guinot <sguinot@lacie.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <plat/orion-gpपन.स>
#समावेश "common.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * LaCie d2 Network Info
 ****************************************************************************/

/*****************************************************************************
 * GPIO LED's
 ****************************************************************************/

/*
 * The blue front LED is wired to the CPLD and can blink in relation with the
 * SATA activity.
 *
 * The following array detail the dअगरferent LED रेजिस्टरs and the combination
 * of their possible values:
 *
 * led_off   | blink_ctrl | SATA active | LED state
 *           |            |             |
 *    1      |     x      |      x      |  off
 *    0      |     0      |      0      |  off
 *    0      |     1      |      0      |  blink (rate 300ms)
 *    0      |     x      |      1      |  on
 *
 * Notes: The blue and the red front LED's can't be on at the same समय.
 *        Red LED have priority.
 */

#घोषणा D2NET_GPIO_RED_LED		6
#घोषणा D2NET_GPIO_BLUE_LED_BLINK_CTRL	16
#घोषणा D2NET_GPIO_BLUE_LED_OFF		23

अटल काष्ठा gpio_led d2net_leds[] = अणु
	अणु
		.name = "d2net:blue:sata",
		.शेष_trigger = "default-on",
		.gpio = D2NET_GPIO_BLUE_LED_OFF,
		.active_low = 1,
	पूर्ण,
	अणु
		.name = "d2net:red:fail",
		.gpio = D2NET_GPIO_RED_LED,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data d2net_led_data = अणु
	.num_leds = ARRAY_SIZE(d2net_leds),
	.leds = d2net_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device d2net_gpio_leds = अणु
	.name           = "leds-gpio",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data  = &d2net_led_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init d2net_gpio_leds_init(व्योम)
अणु
	पूर्णांक err;

	/* Configure रेजिस्टर blink_ctrl to allow SATA activity LED blinking. */
	err = gpio_request(D2NET_GPIO_BLUE_LED_BLINK_CTRL, "blue LED blink");
	अगर (err == 0) अणु
		err = gpio_direction_output(D2NET_GPIO_BLUE_LED_BLINK_CTRL, 1);
		अगर (err)
			gpio_मुक्त(D2NET_GPIO_BLUE_LED_BLINK_CTRL);
	पूर्ण
	अगर (err)
		pr_err("d2net: failed to configure blue LED blink GPIO\n");

	platक्रमm_device_रेजिस्टर(&d2net_gpio_leds);
पूर्ण

/*****************************************************************************
 * General Setup
 ****************************************************************************/

व्योम __init d2net_init(व्योम)
अणु
	d2net_gpio_leds_init();

	pr_notice("d2net: Flash write are not yet supported.\n");
पूर्ण
