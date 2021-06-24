<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/pci/fixups-dreamcast.c
 *
 * PCI fixups क्रम the Sega Dreamcast
 *
 * Copyright (C) 2001, 2002  M. R. Brown
 * Copyright (C) 2002, 2003, 2006  Paul Mundt
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
#समावेश <linux/dma-map-ops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <mach/pci.h>

अटल व्योम gapspci_fixup_resources(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_channel *p = dev->sysdata;
	काष्ठा resource res;
	काष्ठा pci_bus_region region;

	prपूर्णांकk(KERN_NOTICE "PCI: Fixing up device %s\n", pci_name(dev));

	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_SEGA_BBA:
		/*
		 * We also assume that dev->devfn == 0
		 */
		dev->resource[1].start	= p->resources[0].start  + 0x100;
		dev->resource[1].end	= dev->resource[1].start + 0x200 - 1;

		/*
		 * This is not a normal BAR, prevent any attempts to move
		 * the BAR, as this will result in a bus lock.
		 */
		dev->resource[1].flags |= IORESOURCE_PCI_FIXED;

		/*
		 * Redirect dma memory allocations to special memory winकरोw.
		 *
		 * If this GAPSPCI region were mapped by a BAR, the CPU
		 * phys_addr_t would be pci_resource_start(), and the bus
		 * address would be pci_bus_address(pci_resource_start()).
		 * But apparently there's no BAR mapping it, so we just
		 * "know" its CPU address is GAPSPCI_DMA_BASE.
		 */
		res.start = GAPSPCI_DMA_BASE;
		res.end = GAPSPCI_DMA_BASE + GAPSPCI_DMA_SIZE - 1;
		res.flags = IORESOURCE_MEM;
		pcibios_resource_to_bus(dev->bus, &region, &res);
		BUG_ON(dma_declare_coherent_memory(&dev->dev,
						res.start,
						region.start,
						resource_size(&res)));
		अवरोध;
	शेष:
		prपूर्णांकk("PCI: Failed resource fixup\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, gapspci_fixup_resources);

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	/*
	 * The पूर्णांकerrupt routing semantics here are quite trivial.
	 *
	 * We basically only support one पूर्णांकerrupt, so we only bother
	 * updating a device's पूर्णांकerrupt line with this single shared
	 * पूर्णांकerrupt. Keeps routing quite simple, करोesn't it?
	 */
	वापस GAPSPCI_IRQ;
पूर्ण
