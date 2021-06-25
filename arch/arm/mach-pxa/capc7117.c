<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/capc7117.c
 *
 * Support क्रम the Embedian CAPC-7117 Evaluation Kit
 * based on the Embedian MXM-8x10 Computer on Module
 *
 * Copyright (C) 2009 Embedian Inc.
 * Copyright (C) 2009 TMT Services & Supplies (Pty) Ltd.
 *
 * 2007-09-04: eric miao <eric.y.miao@gmail.com>
 *             reग_लिखो to align with latest kernel
 *
 * 2010-01-09: Edwin Peer <epeer@पंचांगtservices.co.za>
 *             Hennie van der Merwe <hvdmerwe@पंचांगtservices.co.za>
 *             rework क्रम upstream merge
 */

#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/machine.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa320.h"
#समावेश "mxm8x10.h"

#समावेश "generic.h"

/* IDE (PATA) Support */
अटल काष्ठा pata_platक्रमm_info pata_platक्रमm_data = अणु
	.ioport_shअगरt = 1
पूर्ण;

अटल काष्ठा resource capc7117_ide_resources[] = अणु
	[0] = अणु
	       .start = 0x11000020,
	       .end = 0x1100003f,
	       .flags = IORESOURCE_MEM
	पूर्ण,
	[1] = अणु
	       .start = 0x1100001c,
	       .end = 0x1100001c,
	       .flags = IORESOURCE_MEM
	पूर्ण,
	[2] = अणु
	       .start = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO76)),
	       .end = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO76)),
	       .flags = IORESOURCE_IRQ | IRQF_TRIGGER_RISING
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device capc7117_ide_device = अणु
	.name = "pata_platform",
	.num_resources = ARRAY_SIZE(capc7117_ide_resources),
	.resource = capc7117_ide_resources,
	.dev = अणु
		.platक्रमm_data = &pata_platक्रमm_data,
		.coherent_dma_mask = ~0		/* grumble */
	पूर्ण
पूर्ण;

अटल व्योम __init capc7117_ide_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&capc7117_ide_device);
पूर्ण

/* TI16C752 UART support */
#घोषणा	TI16C752_FLAGS		(UPF_BOOT_AUTOCONF | \
					UPF_IOREMAP | \
					UPF_BUGGY_UART | \
					UPF_SKIP_TEST)
#घोषणा	TI16C752_UARTCLK	(22118400)
अटल काष्ठा plat_serial8250_port ti16c752_platक्रमm_data[] = अणु
	[0] = अणु
	       .mapbase = 0x14000000,
	       .irq = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO78)),
	       .irqflags = IRQF_TRIGGER_RISING,
	       .flags = TI16C752_FLAGS,
	       .iotype = UPIO_MEM,
	       .regshअगरt = 1,
	       .uartclk = TI16C752_UARTCLK
	पूर्ण,
	[1] = अणु
	       .mapbase = 0x14000040,
	       .irq = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO79)),
	       .irqflags = IRQF_TRIGGER_RISING,
	       .flags = TI16C752_FLAGS,
	       .iotype = UPIO_MEM,
	       .regshअगरt = 1,
	       .uartclk = TI16C752_UARTCLK
	पूर्ण,
	[2] = अणु
	       .mapbase = 0x14000080,
	       .irq = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO80)),
	       .irqflags = IRQF_TRIGGER_RISING,
	       .flags = TI16C752_FLAGS,
	       .iotype = UPIO_MEM,
	       .regshअगरt = 1,
	       .uartclk = TI16C752_UARTCLK
	पूर्ण,
	[3] = अणु
	       .mapbase = 0x140000c0,
	       .irq = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO81)),
	       .irqflags = IRQF_TRIGGER_RISING,
	       .flags = TI16C752_FLAGS,
	       .iotype = UPIO_MEM,
	       .regshअगरt = 1,
	       .uartclk = TI16C752_UARTCLK
	पूर्ण,
	[4] = अणु
	       /* end of array */
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device ti16c752_device = अणु
	.name = "serial8250",
	.id = PLAT8250_DEV_PLATFORM,
	.dev = अणु
		.platक्रमm_data = ti16c752_platक्रमm_data
	पूर्ण
पूर्ण;

अटल व्योम __init capc7117_uarts_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&ti16c752_device);
पूर्ण

अटल व्योम __init capc7117_init(व्योम)
अणु
	/* Init CoM */
	mxm_8x10_barebones_init();

	/* Init evaluation board peripherals */
	mxm_8x10_ac97_init();
	mxm_8x10_usb_host_init();
	mxm_8x10_mmc_init();

	capc7117_uarts_init();
	capc7117_ide_init();

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

MACHINE_START(CAPC7117,
	      "Embedian CAPC-7117 evaluation kit based on the MXM-8x10 CoM")
	.atag_offset = 0x100,
	.map_io = pxa3xx_map_io,
	.nr_irqs = PXA_NR_IRQS,
	.init_irq = pxa3xx_init_irq,
	.handle_irq = pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine = capc7117_init,
	.restart	= pxa_restart,
MACHINE_END
