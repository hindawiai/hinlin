<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI support क्रम the Sega Dreamcast
 *
 * Copyright (C) 2001, 2002  M. R. Brown
 * Copyright (C) 2002, 2003  Paul Mundt
 *
 * This file originally bore the message (with enबंदd-$):
 *	Id: pci.c,v 1.3 2003/05/04 19:29:46 lethal Exp
 *	Dreamcast PCI: Supports SEGA Broadband Adaptor only.
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <mach/pci.h>

अटल काष्ठा resource gapspci_resources[] = अणु
	अणु
		.name	= "GAPSPCI IO",
		.start	= GAPSPCI_BBA_CONFIG,
		.end	= GAPSPCI_BBA_CONFIG + GAPSPCI_BBA_CONFIG_SIZE - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,  अणु
		.name	= "GAPSPCI mem",
		.start	= GAPSPCI_DMA_BASE,
		.end	= GAPSPCI_DMA_BASE + GAPSPCI_DMA_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा pci_channel dreamcast_pci_controller = अणु
	.pci_ops	= &gapspci_pci_ops,
	.resources	= gapspci_resources,
	.nr_resources	= ARRAY_SIZE(gapspci_resources),
	.io_offset	= 0x00000000,
	.mem_offset	= 0x00000000,
पूर्ण;

/*
 * gapspci init
 */

अटल पूर्णांक __init gapspci_init(व्योम)
अणु
	अक्षर idbuf[16];
	पूर्णांक i;

	/*
	 * FIXME: All of this wants करोcumenting to some degree,
	 * even some basic रेजिस्टर definitions would be nice.
	 *
	 * I haven't seen anything this ugly since.. maple.
	 */

	क्रम (i=0; i<16; i++)
		idbuf[i] = inb(GAPSPCI_REGS+i);

	अगर (म_भेदन(idbuf, "GAPSPCI_BRIDGE_2", 16))
		वापस -ENODEV;

	outl(0x5a14a501, GAPSPCI_REGS+0x18);

	क्रम (i=0; i<1000000; i++)
		cpu_relax();

	अगर (inl(GAPSPCI_REGS+0x18) != 1)
		वापस -EINVAL;

	outl(0x01000000, GAPSPCI_REGS+0x20);
	outl(0x01000000, GAPSPCI_REGS+0x24);

	outl(GAPSPCI_DMA_BASE, GAPSPCI_REGS+0x28);
	outl(GAPSPCI_DMA_BASE+GAPSPCI_DMA_SIZE, GAPSPCI_REGS+0x2c);

	outl(1, GAPSPCI_REGS+0x14);
	outl(1, GAPSPCI_REGS+0x34);

	/* Setting Broadband Adapter */
	outw(0xf900, GAPSPCI_BBA_CONFIG+0x06);
	outl(0x00000000, GAPSPCI_BBA_CONFIG+0x30);
	outb(0x00, GAPSPCI_BBA_CONFIG+0x3c);
	outb(0xf0, GAPSPCI_BBA_CONFIG+0x0d);
	outw(0x0006, GAPSPCI_BBA_CONFIG+0x04);
	outl(0x00002001, GAPSPCI_BBA_CONFIG+0x10);
	outl(0x01000000, GAPSPCI_BBA_CONFIG+0x14);

	वापस रेजिस्टर_pci_controller(&dreamcast_pci_controller);
पूर्ण
arch_initcall(gapspci_init);
