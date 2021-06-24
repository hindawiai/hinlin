<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001,2002,2005 Broadcom Corporation
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 */

/*
 * BCM1480/1455-specअगरic HT support (looking like PCI)
 *
 * This module provides the glue between Linux's PCI subप्रणाली
 * and the hardware.  We basically provide glue क्रम accessing
 * configuration space, and set up the translation क्रम I/O
 * space accesses.
 *
 * To access configuration space, we use ioremap.  In the 32-bit
 * kernel, this consumes either 4 or 8 page table pages, and 16MB of
 * kernel mapped memory.  Hopefully neither of these should be a huge
 * problem.
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>

#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_scd.h>
#समावेश <यंत्र/sibyte/board.h>
#समावेश <यंत्र/पन.स>

/*
 * Macros क्रम calculating offsets पूर्णांकo config space given a device
 * काष्ठाure or dev/fun/reg
 */
#घोषणा CFGOFFSET(bus, devfn, where) (((bus)<<16)+((devfn)<<8)+(where))
#घोषणा CFGADDR(bus, devfn, where)   CFGOFFSET((bus)->number, (devfn), where)

अटल व्योम *ht_cfg_space;

#घोषणा PCI_BUS_ENABLED 1
#घोषणा PCI_DEVICE_MODE 2

अटल पूर्णांक bcm1480ht_bus_status;

#घोषणा PCI_BRIDGE_DEVICE  0
#घोषणा HT_BRIDGE_DEVICE   1

/*
 * HT's level-sensitive पूर्णांकerrupts require EOI, which is generated
 * through a 4MB memory-mapped region
 */
अचिन्हित दीर्घ ht_eoi_space;

/*
 * Read/ग_लिखो 32-bit values in config space.
 */
अटल अंतरभूत u32 READCFG32(u32 addr)
अणु
	वापस *(u32 *)(ht_cfg_space + (addr&~3));
पूर्ण

अटल अंतरभूत व्योम WRITECFG32(u32 addr, u32 data)
अणु
	*(u32 *)(ht_cfg_space + (addr & ~3)) = data;
पूर्ण

/*
 * Some checks beक्रमe करोing config cycles:
 * In PCI Device Mode, hide everything on bus 0 except the LDT host
 * bridge.  Otherwise, access is controlled by bridge MasterEn bits.
 */
अटल पूर्णांक bcm1480ht_can_access(काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	u32 devno;

	अगर (!(bcm1480ht_bus_status & (PCI_BUS_ENABLED | PCI_DEVICE_MODE)))
		वापस 0;

	अगर (bus->number == 0) अणु
		devno = PCI_SLOT(devfn);
		अगर (bcm1480ht_bus_status & PCI_DEVICE_MODE)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Read/ग_लिखो access functions क्रम various sizes of values
 * in config space.  Return all 1's क्रम disallowed accesses
 * क्रम a kludgy but adequate simulation of master पातs.
 */

अटल पूर्णांक bcm1480ht_pcibios_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 * val)
अणु
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (bcm1480ht_can_access(bus, devfn))
		data = READCFG32(CFGADDR(bus, devfn, where));
	अन्यथा
		data = 0xFFFFFFFF;

	अगर (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (data >> ((where & 3) << 3)) & 0xffff;
	अन्यथा
		*val = data;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक bcm1480ht_pcibios_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 cfgaddr = CFGADDR(bus, devfn, where);
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (!bcm1480ht_can_access(bus, devfn))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	data = READCFG32(cfgaddr);

	अगर (size == 1)
		data = (data & ~(0xff << ((where & 3) << 3))) |
		    (val << ((where & 3) << 3));
	अन्यथा अगर (size == 2)
		data = (data & ~(0xffff << ((where & 3) << 3))) |
		    (val << ((where & 3) << 3));
	अन्यथा
		data = val;

	WRITECFG32(cfgaddr, data);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक bcm1480ht_pcibios_get_busno(व्योम)
अणु
	वापस 0;
पूर्ण

काष्ठा pci_ops bcm1480ht_pci_ops = अणु
	.पढ़ो	= bcm1480ht_pcibios_पढ़ो,
	.ग_लिखो	= bcm1480ht_pcibios_ग_लिखो,
पूर्ण;

अटल काष्ठा resource bcm1480ht_mem_resource = अणु
	.name	= "BCM1480 HT MEM",
	.start	= A_BCM1480_PHYS_HT_MEM_MATCH_BYTES,
	.end	= A_BCM1480_PHYS_HT_MEM_MATCH_BYTES + 0x1fffffffUL,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource bcm1480ht_io_resource = अणु
	.name	= "BCM1480 HT I/O",
	.start	= A_BCM1480_PHYS_HT_IO_MATCH_BYTES,
	.end	= A_BCM1480_PHYS_HT_IO_MATCH_BYTES + 0x01ffffffUL,
	.flags	= IORESOURCE_IO,
पूर्ण;

काष्ठा pci_controller bcm1480ht_controller = अणु
	.pci_ops	= &bcm1480ht_pci_ops,
	.mem_resource	= &bcm1480ht_mem_resource,
	.io_resource	= &bcm1480ht_io_resource,
	.index		= 1,
	.get_busno	= bcm1480ht_pcibios_get_busno,
	.io_offset	= A_BCM1480_PHYS_HT_IO_MATCH_BYTES,
पूर्ण;

अटल पूर्णांक __init bcm1480ht_pcibios_init(व्योम)
अणु
	ht_cfg_space = ioremap(A_BCM1480_PHYS_HT_CFG_MATCH_BITS, 16*1024*1024);

	/* CFE करोesn't always init all HT paths, so we always scan */
	bcm1480ht_bus_status |= PCI_BUS_ENABLED;

	ht_eoi_space = (अचिन्हित दीर्घ)
		ioremap(A_BCM1480_PHYS_HT_SPECIAL_MATCH_BYTES,
			4 * 1024 * 1024);
	bcm1480ht_controller.io_map_base = (अचिन्हित दीर्घ)
		ioremap(A_BCM1480_PHYS_HT_IO_MATCH_BYTES, 65536);
	bcm1480ht_controller.io_map_base -= bcm1480ht_controller.io_offset;

	रेजिस्टर_pci_controller(&bcm1480ht_controller);

	वापस 0;
पूर्ण

arch_initcall(bcm1480ht_pcibios_init);
