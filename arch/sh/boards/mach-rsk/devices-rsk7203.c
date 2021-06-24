<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Technology Europe RSK+ 7203 Support.
 *
 * Copyright (C) 2008 - 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/input.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/leds.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/पन.स>
#समावेश <cpu/sh7203.h>

अटल काष्ठा smsc911x_platक्रमm_config smsc911x_config = अणु
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_32BIT | SMSC911X_SWAP_FIFO,
पूर्ण;

अटल काष्ठा resource smsc911x_resources[] = अणु
	[0] = अणु
		.start		= 0x24000000,
		.end		= 0x240000ff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start		= 64,
		.end		= 64,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smsc911x_device = अणु
	.name		= "smsc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev		= अणु
		.platक्रमm_data = &smsc911x_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led rsk7203_gpio_leds[] = अणु
	अणु
		.name			= "green",
		.gpio			= GPIO_PE10,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "orange",
		.शेष_trigger	= "nand-disk",
		.gpio			= GPIO_PE12,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "red:timer",
		.शेष_trigger	= "timer",
		.gpio			= GPIO_PC14,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "red:heartbeat",
		.शेष_trigger	= "heartbeat",
		.gpio			= GPIO_PE11,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data rsk7203_gpio_leds_info = अणु
	.leds		= rsk7203_gpio_leds,
	.num_leds	= ARRAY_SIZE(rsk7203_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device led_device = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &rsk7203_gpio_leds_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_button rsk7203_gpio_keys_table[] = अणु
	अणु
		.code		= BTN_0,
		.gpio		= GPIO_PB0,
		.active_low	= 1,
		.desc		= "SW1",
	पूर्ण, अणु
		.code		= BTN_1,
		.gpio		= GPIO_PB1,
		.active_low	= 1,
		.desc		= "SW2",
	पूर्ण, अणु
		.code		= BTN_2,
		.gpio		= GPIO_PB2,
		.active_low	= 1,
		.desc		= "SW3",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data rsk7203_gpio_keys_info = अणु
	.buttons	= rsk7203_gpio_keys_table,
	.nbuttons	= ARRAY_SIZE(rsk7203_gpio_keys_table),
	.poll_पूर्णांकerval	= 50, /* शेष to 50ms */
पूर्ण;

अटल काष्ठा platक्रमm_device keys_device = अणु
	.name		= "gpio-keys-polled",
	.dev		= अणु
		.platक्रमm_data	= &rsk7203_gpio_keys_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *rsk7203_devices[] __initdata = अणु
	&smsc911x_device,
	&led_device,
	&keys_device,
पूर्ण;

अटल पूर्णांक __init rsk7203_devices_setup(व्योम)
अणु
	/* Select pins क्रम SCIF0 */
	gpio_request(GPIO_FN_TXD0, शून्य);
	gpio_request(GPIO_FN_RXD0, शून्य);

	/* Setup LAN9118: CS1 in 16-bit Big Endian Mode, IRQ0 at Port B */
	__raw_ग_लिखोl(0x36db0400, 0xfffc0008); /* CS1BCR */
	gpio_request(GPIO_FN_IRQ0_PB, शून्य);

	वापस platक्रमm_add_devices(rsk7203_devices,
				    ARRAY_SIZE(rsk7203_devices));
पूर्ण
device_initcall(rsk7203_devices_setup);
