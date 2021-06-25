<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 *
 * pcibios_align_resource taken from arch/arm/kernel/bios32.c.
 */

#समावेश <linux/pci.h>

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
resource_माप_प्रकार pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
				resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pci_dev *dev = data;
	resource_माप_प्रकार start = res->start;
	काष्ठा pci_host_bridge *host_bridge;

	अगर (res->flags & IORESOURCE_IO && start & 0x300)
		start = (start + 0x3ff) & ~0x3ff;

	start = (start + align - 1) & ~(align - 1);

	host_bridge = pci_find_host_bridge(dev->bus);

	अगर (host_bridge->align_resource)
		वापस host_bridge->align_resource(dev, res,
				start, size, align);

	वापस start;
पूर्ण

व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	pci_पढ़ो_bridge_bases(bus);
पूर्ण
