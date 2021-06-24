<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/mach-x3proto/setup.c
 *
 * Renesas SH-X3 Prototype Board Support.
 *
 * Copyright (C) 2007 - 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/smc91x.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/usb/r8a66597.h>
#समावेश <linux/usb/m66592.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <mach/ilsel.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/smp-ops.h>

अटल काष्ठा resource heartbeat_resources[] = अणु
	[0] = अणु
		.start	= 0xb8140020,
		.end	= 0xb8140020,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(heartbeat_resources),
	.resource	= heartbeat_resources,
पूर्ण;

अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start		= 0x18000300,
		.end		= 0x18000300 + 0x10 - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* Filled in by ilsel */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= -1,
	.resource	= smc91x_resources,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.dev	= अणु
		.platक्रमm_data = &smc91x_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा r8a66597_platdata r8a66597_data = अणु
	.xtal = R8A66597_PLATDATA_XTAL_12MHZ,
	.vअगर = 1,
पूर्ण;

अटल काष्ठा resource r8a66597_usb_host_resources[] = अणु
	[0] = अणु
		.start	= 0x18040000,
		.end	= 0x18080000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* Filled in by ilsel */
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device r8a66597_usb_host_device = अणु
	.name		= "r8a66597_hcd",
	.id		= -1,
	.dev = अणु
		.dma_mask		= शून्य,		/* करोn't use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &r8a66597_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(r8a66597_usb_host_resources),
	.resource	= r8a66597_usb_host_resources,
पूर्ण;

अटल काष्ठा m66592_platdata usbf_platdata = अणु
	.xtal = M66592_PLATDATA_XTAL_24MHZ,
	.vअगर = 1,
पूर्ण;

अटल काष्ठा resource m66592_usb_peripheral_resources[] = अणु
	[0] = अणु
		.name	= "m66592_udc",
		.start	= 0x18080000,
		.end	= 0x180c0000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "m66592_udc",
		/* Filled in by ilsel */
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device m66592_usb_peripheral_device = अणु
	.name		= "m66592_udc",
	.id		= -1,
	.dev = अणु
		.dma_mask		= शून्य,		/* करोn't use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &usbf_platdata,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(m66592_usb_peripheral_resources),
	.resource	= m66592_usb_peripheral_resources,
पूर्ण;

अटल काष्ठा gpio_keys_button baseboard_buttons[NR_BASEBOARD_GPIOS] = अणु
	अणु
		.desc		= "key44",
		.code		= KEY_POWER,
		.active_low	= 1,
		.wakeup		= 1,
	पूर्ण, अणु
		.desc		= "key43",
		.code		= KEY_SUSPEND,
		.active_low	= 1,
		.wakeup		= 1,
	पूर्ण, अणु
		.desc		= "key42",
		.code		= KEY_KATAKANAHIRAGANA,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key41",
		.code		= KEY_SWITCHVIDEOMODE,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key34",
		.code		= KEY_F12,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key33",
		.code		= KEY_F11,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key32",
		.code		= KEY_F10,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key31",
		.code		= KEY_F9,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key24",
		.code		= KEY_F8,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key23",
		.code		= KEY_F7,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key22",
		.code		= KEY_F6,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key21",
		.code		= KEY_F5,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key14",
		.code		= KEY_F4,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key13",
		.code		= KEY_F3,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key12",
		.code		= KEY_F2,
		.active_low	= 1,
	पूर्ण, अणु
		.desc		= "key11",
		.code		= KEY_F1,
		.active_low	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data baseboard_buttons_data = अणु
	.buttons	= baseboard_buttons,
	.nbuttons	= ARRAY_SIZE(baseboard_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device baseboard_buttons_device = अणु
	.name		= "gpio-keys",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &baseboard_buttons_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *x3proto_devices[] __initdata = अणु
	&heartbeat_device,
	&smc91x_device,
	&r8a66597_usb_host_device,
	&m66592_usb_peripheral_device,
	&baseboard_buttons_device,
पूर्ण;

अटल व्योम __init x3proto_init_irq(व्योम)
अणु
	plat_irq_setup_pins(IRQ_MODE_IRL3210);

	/* Set ICR0.LVLMODE */
	__raw_ग_लिखोl(__raw_पढ़ोl(0xfe410000) | (1 << 21), 0xfe410000);
पूर्ण

अटल पूर्णांक __init x3proto_devices_setup(व्योम)
अणु
	पूर्णांक ret, i;

	/*
	 * IRLs are only needed क्रम ILSEL mappings, so flip over the INTC
	 * pins at a later poपूर्णांक to enable the GPIOs to settle.
	 */
	x3proto_init_irq();

	/*
	 * Now that ILSELs are available, set up the baseboard GPIOs.
	 */
	ret = x3proto_gpio_setup();
	अगर (unlikely(ret))
		वापस ret;

	/*
	 * Propagate dynamic GPIOs क्रम the baseboard button device.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(baseboard_buttons); i++)
		baseboard_buttons[i].gpio = x3proto_gpio_chip.base + i;

	r8a66597_usb_host_resources[1].start =
		r8a66597_usb_host_resources[1].end = ilsel_enable(ILSEL_USBH_I);

	m66592_usb_peripheral_resources[1].start =
		m66592_usb_peripheral_resources[1].end = ilsel_enable(ILSEL_USBP_I);

	smc91x_resources[1].start =
		smc91x_resources[1].end = ilsel_enable(ILSEL_LAN);

	वापस platक्रमm_add_devices(x3proto_devices,
				    ARRAY_SIZE(x3proto_devices));
पूर्ण
device_initcall(x3proto_devices_setup);

अटल व्योम __init x3proto_setup(अक्षर **cmdline_p)
अणु
	रेजिस्टर_smp_ops(&shx3_smp_ops);
पूर्ण

अटल काष्ठा sh_machine_vector mv_x3proto __iniपंचांगv = अणु
	.mv_name		= "x3proto",
	.mv_setup		= x3proto_setup,
पूर्ण;
