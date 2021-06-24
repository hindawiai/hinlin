<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/xtensa/kernel/pci.c
 *
 * PCI bios-type initialisation क्रम PCI machines
 *
 * Copyright (C) 2001-2005 Tensilica Inc.
 *
 * Based largely on work from Cort (ppc/kernel/pci.c)
 * IO functions copied from sparc.
 *
 * Chris Zankel <chris@zankel.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/platक्रमm.h>

/*
 * We need to aव्योम collisions with `mirrored' VGA ports
 * and other strange ISA hardware, so we always want the
 * addresses to be allocated in the 0x000-0x0ff region
 * modulo 0x400.
 *
 * Why? Because some silly बाह्यal IO cards only decode
 * the low 10 bits of the IO address. The 0x00-0xff region
 * is reserved क्रम motherboard devices that decode all 16
 * bits, so it's ok to allocate at, say, 0x2800-0x28ff,
 * but we want to try to aव्योम allocating at 0x2900-0x2bff
 * which might have be mirrored at 0x0100-0x03ff..
 */
resource_माप_प्रकार
pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
		       resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pci_dev *dev = data;
	resource_माप_प्रकार start = res->start;

	अगर (res->flags & IORESOURCE_IO) अणु
		अगर (size > 0x100) अणु
			pr_err("PCI: I/O Region %s/%d too large (%u bytes)\n",
					pci_name(dev), dev->resource - res,
					size);
		पूर्ण

		अगर (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	पूर्ण

	वापस start;
पूर्ण

व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	अगर (bus->parent) अणु
		/* This is a subordinate bridge */
		pci_पढ़ो_bridge_bases(bus);
	पूर्ण
पूर्ण

/*
 * Platक्रमm support क्रम /proc/bus/pci/X/Y mmap()s.
 *  -- paulus.
 */

पूर्णांक pci_iobar_pfn(काष्ठा pci_dev *pdev, पूर्णांक bar, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा pci_controller *pci_ctrl = (काष्ठा pci_controller*) pdev->sysdata;
	resource_माप_प्रकार ioaddr = pci_resource_start(pdev, bar);

	अगर (!pci_ctrl)
		वापस -EINVAL;		/* should never happen */

	/* Convert to an offset within this PCI controller */
	ioaddr -= (अचिन्हित दीर्घ)pci_ctrl->io_space.base;

	vma->vm_pgoff += (ioaddr + pci_ctrl->io_space.start) >> PAGE_SHIFT;
	वापस 0;
पूर्ण
