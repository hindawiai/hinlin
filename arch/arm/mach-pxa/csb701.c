<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>

#समावेश <यंत्र/mach-types.h>

अटल काष्ठा gpio_keys_button csb701_buttons[] = अणु
	अणु
		.code	= 0x7,
		.gpio	= 1,
		.active_low = 1,
		.desc	= "SW2",
		.type	= EV_SW,
		.wakeup = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data csb701_gpio_keys_data = अणु
	.buttons = csb701_buttons,
	.nbuttons = ARRAY_SIZE(csb701_buttons),
पूर्ण;

अटल काष्ठा gpio_led csb701_leds[] = अणु
	अणु
		.name	= "csb701:yellow:heartbeat",
		.शेष_trigger = "heartbeat",
		.gpio	= 11,
		.active_low = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device csb701_gpio_keys = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.dev.platक्रमm_data = &csb701_gpio_keys_data,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data csb701_leds_gpio_data = अणु
	.leds		= csb701_leds,
	.num_leds	= ARRAY_SIZE(csb701_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device csb701_leds_gpio = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev.platक्रमm_data = &csb701_leds_gpio_data,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&csb701_gpio_keys,
	&csb701_leds_gpio,
पूर्ण;

अटल पूर्णांक __init csb701_init(व्योम)
अणु
	अगर (!machine_is_csb726())
		वापस -ENODEV;

	वापस platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण

module_init(csb701_init);

