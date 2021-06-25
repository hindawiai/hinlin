<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RSK+SH7264 Support.
 *
 * Copyright (C) 2012 Renesas Electronics Europe
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/smsc911x.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/पन.स>

अटल काष्ठा smsc911x_platक्रमm_config smsc911x_config = अणु
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_16BIT | SMSC911X_SWAP_FIFO,
पूर्ण;

अटल काष्ठा resource smsc911x_resources[] = अणु
	[0] = अणु
		.start		= 0x28000000,
		.end		= 0x280000ff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start		= 65,
		.end		= 65,
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

अटल काष्ठा platक्रमm_device *rsk7264_devices[] __initdata = अणु
	&smsc911x_device,
पूर्ण;

अटल पूर्णांक __init rsk7264_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(rsk7264_devices,
				    ARRAY_SIZE(rsk7264_devices));
पूर्ण
device_initcall(rsk7264_devices_setup);
