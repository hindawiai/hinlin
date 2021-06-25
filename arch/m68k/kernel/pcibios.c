<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pci.c -- basic PCI support code
 *
 * (C) Copyright 2011, Greg Ungerer <gerg@uclinux.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

/*
 * From arch/i386/kernel/pci-i386.c:
 *
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
 * which might be mirrored at 0x0100-0x03ff..
 */
resource_माप_प्रकार pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
	resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	resource_माप_प्रकार start = res->start;

	अगर ((res->flags & IORESOURCE_IO) && (start & 0x300))
		start = (start + 0x3ff) & ~0x3ff;

	start = (start + align - 1) & ~(align - 1);

	वापस start;
पूर्ण

/*
 * This is taken from the ARM code क्रम this.
 */
पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	काष्ठा resource *r;
	u16 cmd, newcmd;
	पूर्णांक idx;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	newcmd = cmd;

	क्रम (idx = 0; idx < 6; idx++) अणु
		/* Only set up the requested stuff */
		अगर (!(mask & (1 << idx)))
			जारी;

		r = dev->resource + idx;
		अगर (!r->start && r->end) अणु
			pr_err("PCI: Device %s not available because of resource collisions\n",
				pci_name(dev));
			वापस -EINVAL;
		पूर्ण
		अगर (r->flags & IORESOURCE_IO)
			newcmd |= PCI_COMMAND_IO;
		अगर (r->flags & IORESOURCE_MEM)
			newcmd |= PCI_COMMAND_MEMORY;
	पूर्ण

	/*
	 * Bridges (eg, cardbus bridges) need to be fully enabled
	 */
	अगर ((dev->class >> 16) == PCI_BASE_CLASS_BRIDGE)
		newcmd |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY;


	अगर (newcmd != cmd) अणु
		pr_info("PCI: enabling device %s (0x%04x -> 0x%04x)\n",
			pci_name(dev), cmd, newcmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, newcmd);
	पूर्ण
	वापस 0;
पूर्ण

व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, 8);
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 32);
	पूर्ण
पूर्ण

अक्षर *pcibios_setup(अक्षर *str)
अणु
	वापस str;
पूर्ण

