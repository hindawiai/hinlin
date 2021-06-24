<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/mp900.c
 *
 *  Support क्रम the NEC MobilePro900/C platक्रमm
 *
 *  Based on mach-pxa/gumstix.c
 *
 *  2007, 2008 Kristoffer Ericson <kristoffer.ericson@gmail.com>
 *  2007, 2008 Michael Petchkovsky <mkpetch@पूर्णांकernode.on.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/isp116x.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa25x.h"
#समावेश "generic.h"

अटल व्योम isp116x_pfm_delay(काष्ठा device *dev, पूर्णांक delay)
अणु

	/* 400MHz PXA2 = 2.5ns / inकाष्ठाion */

	पूर्णांक cyc = delay / 10;

	/* 4 Inकाष्ठाions = 4 x 2.5ns = 10ns */
	__यंत्र__ अस्थिर ("0:\n"
		"subs %0, %1, #1\n"
		"bge 0b\n"
		:"=r" (cyc)
		:"0"(cyc)
	);
पूर्ण

अटल काष्ठा isp116x_platक्रमm_data isp116x_pfm_data = अणु
	.remote_wakeup_enable = 1,
	.delay = isp116x_pfm_delay,
पूर्ण;

अटल काष्ठा resource isp116x_pfm_resources[] = अणु
	[0] =	अणु
		.start	= 0x0d000000,
		.end	= 0x0d000000 + 1,
		.flags	= IORESOURCE_MEM,
		पूर्ण,
	[1] =	अणु
		.start  = 0x0d000000 + 4,
		.end	= 0x0d000000 + 5,
		.flags  = IORESOURCE_MEM,
		पूर्ण,
	[2] =	अणु
		.start	= 61,
		.end	= 61,
		.flags	= IORESOURCE_IRQ,
		पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mp900c_dummy_device = अणु
	.name		= "mp900c_dummy",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device mp900c_usb = अणु
	.name		= "isp116x-hcd",
	.num_resources	= ARRAY_SIZE(isp116x_pfm_resources),
	.resource	= isp116x_pfm_resources,
	.dev.platक्रमm_data = &isp116x_pfm_data,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&mp900c_dummy_device,
	&mp900c_usb,
पूर्ण;

अटल व्योम __init mp900c_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "MobilePro 900/C machine init\n");
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण

/* Maपूर्णांकainer - Michael Petchkovsky <mkpetch@पूर्णांकernode.on.net> */
MACHINE_START(NEC_MP900, "MobilePro900/C")
	.atag_offset	= 0x220100,
	.init_समय	= pxa_समयr_init,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_machine	= mp900c_init,
	.restart	= pxa_restart,
MACHINE_END

