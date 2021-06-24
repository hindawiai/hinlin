<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011-2016 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/leds.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/sizes.h>

#समावेश <loongson1.h>
#समावेश <dma.h>
#समावेश <nand.h>
#समावेश <platक्रमm.h>

अटल स्थिर काष्ठा gpio_led ls1x_gpio_leds[] __initस्थिर = अणु
	अणु
		.name			= "LED9",
		.शेष_trigger	= "heartbeat",
		.gpio			= 38,
		.active_low		= 1,
		.शेष_state		= LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण, अणु
		.name			= "LED6",
		.शेष_trigger	= "nand-disk",
		.gpio			= 39,
		.active_low		= 1,
		.शेष_state		= LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data ls1x_led_pdata __initस्थिर = अणु
	.num_leds	= ARRAY_SIZE(ls1x_gpio_leds),
	.leds		= ls1x_gpio_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device *ls1b_platक्रमm_devices[] __initdata = अणु
	&ls1x_uart_pdev,
	&ls1x_cpufreq_pdev,
	&ls1x_eth0_pdev,
	&ls1x_eth1_pdev,
	&ls1x_ehci_pdev,
	&ls1x_gpio0_pdev,
	&ls1x_gpio1_pdev,
	&ls1x_rtc_pdev,
	&ls1x_wdt_pdev,
पूर्ण;

अटल पूर्णांक __init ls1b_platक्रमm_init(व्योम)
अणु
	ls1x_serial_set_uartclk(&ls1x_uart_pdev);

	gpio_led_रेजिस्टर_device(-1, &ls1x_led_pdata);

	वापस platक्रमm_add_devices(ls1b_platक्रमm_devices,
				   ARRAY_SIZE(ls1b_platक्रमm_devices));
पूर्ण

arch_initcall(ls1b_platक्रमm_init);
