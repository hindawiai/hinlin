<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001,2002,2005 Broadcom Corporation
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 */

/*
 * BCM1x80/1x55-specअगरic PCI support
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
 * XXX: AT THIS TIME, ONLY the NATIVE PCI-X INTERFACE IS SUPPORTED.
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/console.h>
#समावेश <linux/tty.h>
#समावेश <linux/vt.h>

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

अटल व्योम *cfg_space;

#घोषणा PCI_BUS_ENABLED 1
#घोषणा PCI_DEVICE_MODE 2

अटल पूर्णांक bcm1480_bus_status;

#घोषणा PCI_BRIDGE_DEVICE  0

/*
 * Read/ग_लिखो 32-bit values in config space.
 */
अटल अंतरभूत u32 READCFG32(u32 addr)
अणु
	वापस *(u32 *)(cfg_space + (addr&~3));
पूर्ण

अटल अंतरभूत व्योम WRITECFG32(u32 addr, u32 data)
अणु
	*(u32 *)(cfg_space + (addr & ~3)) = data;
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (pin == 0)
		वापस -1;

	वापस K_BCM1480_INT_PCI_INTA - 1 + pin;
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

/*
 * Some checks beक्रमe करोing config cycles:
 * In PCI Device Mode, hide everything on bus 0 except the LDT host
 * bridge.  Otherwise, access is controlled by bridge MasterEn bits.
 */
अटल पूर्णांक bcm1480_pci_can_access(काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	u32 devno;

	अगर (!(bcm1480_bus_status & (PCI_BUS_ENABLED | PCI_DEVICE_MODE)))
		वापस 0;

	अगर (bus->number == 0) अणु
		devno = PCI_SLOT(devfn);
		अगर (bcm1480_bus_status & PCI_DEVICE_MODE)
			वापस 0;
		अन्यथा
			वापस 1;
	पूर्ण अन्यथा
		वापस 1;
पूर्ण

/*
 * Read/ग_लिखो access functions क्रम various sizes of values
 * in config space.  Return all 1's क्रम disallowed accesses
 * क्रम a kludgy but adequate simulation of master पातs.
 */

अटल पूर्णांक bcm1480_pcibios_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 * val)
अणु
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (bcm1480_pci_can_access(bus, devfn))
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

अटल पूर्णांक bcm1480_pcibios_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 cfgaddr = CFGADDR(bus, devfn, where);
	u32 data = 0;

	अगर ((size == 2) && (where & 1))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	अन्यथा अगर ((size == 4) && (where & 3))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (!bcm1480_pci_can_access(bus, devfn))
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

काष्ठा pci_ops bcm1480_pci_ops = अणु
	.पढ़ो	= bcm1480_pcibios_पढ़ो,
	.ग_लिखो	= bcm1480_pcibios_ग_लिखो,
पूर्ण;

अटल काष्ठा resource bcm1480_mem_resource = अणु
	.name	= "BCM1480 PCI MEM",
	.start	= A_BCM1480_PHYS_PCI_MEM_MATCH_BYTES,
	.end	= A_BCM1480_PHYS_PCI_MEM_MATCH_BYTES + 0xfffffffUL,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource bcm1480_io_resource = अणु
	.name	= "BCM1480 PCI I/O",
	.start	= A_BCM1480_PHYS_PCI_IO_MATCH_BYTES,
	.end	= A_BCM1480_PHYS_PCI_IO_MATCH_BYTES + 0x1ffffffUL,
	.flags	= IORESOURCE_IO,
पूर्ण;

काष्ठा pci_controller bcm1480_controller = अणु
	.pci_ops	= &bcm1480_pci_ops,
	.mem_resource	= &bcm1480_mem_resource,
	.io_resource	= &bcm1480_io_resource,
	.io_offset	= A_BCM1480_PHYS_PCI_IO_MATCH_BYTES,
पूर्ण;


अटल पूर्णांक __init bcm1480_pcibios_init(व्योम)
अणु
	uपूर्णांक32_t cmdreg;
	uपूर्णांक64_t reg;

	/* CFE will assign PCI resources */
	pci_set_flags(PCI_PROBE_ONLY);

	/* Aव्योम ISA compat ranges.  */
	PCIBIOS_MIN_IO = 0x00008000UL;
	PCIBIOS_MIN_MEM = 0x01000000UL;

	/* Set I/O resource limits. - unlimited क्रम now to accommodate HT */
	ioport_resource.end = 0xffffffffUL;
	iomem_resource.end = 0xffffffffUL;

	cfg_space = ioremap(A_BCM1480_PHYS_PCI_CFG_MATCH_BITS, 16*1024*1024);

	/*
	 * See अगर the PCI bus has been configured by the firmware.
	 */
	reg = __raw_पढ़ोq(IOADDR(A_SCD_SYSTEM_CFG));
	अगर (!(reg & M_BCM1480_SYS_PCI_HOST)) अणु
		bcm1480_bus_status |= PCI_DEVICE_MODE;
	पूर्ण अन्यथा अणु
		cmdreg = READCFG32(CFGOFFSET(0, PCI_DEVFN(PCI_BRIDGE_DEVICE, 0),
					     PCI_COMMAND));
		अगर (!(cmdreg & PCI_COMMAND_MASTER)) अणु
			prपूर्णांकk
			    ("PCI: Skipping PCI probe.	Bus is not initialized.\n");
			iounmap(cfg_space);
			वापस 1; /* XXX */
		पूर्ण
		bcm1480_bus_status |= PCI_BUS_ENABLED;
	पूर्ण

	/* turn on ExpMemEn */
	cmdreg = READCFG32(CFGOFFSET(0, PCI_DEVFN(PCI_BRIDGE_DEVICE, 0), 0x40));
	WRITECFG32(CFGOFFSET(0, PCI_DEVFN(PCI_BRIDGE_DEVICE, 0), 0x40),
			cmdreg | 0x10);
	cmdreg = READCFG32(CFGOFFSET(0, PCI_DEVFN(PCI_BRIDGE_DEVICE, 0), 0x40));

	/*
	 * Establish mappings in KSEG2 (kernel भव) to PCI I/O
	 * space.  Use "match bytes" policy to make everything look
	 * little-endian.  So, you need to also set
	 * CONFIG_SWAP_IO_SPACE, but this is the combination that
	 * works correctly with most of Linux's drivers.
	 * XXX ehs: Should this happen in PCI Device mode?
	 */

	bcm1480_controller.io_map_base = (अचिन्हित दीर्घ)
		ioremap(A_BCM1480_PHYS_PCI_IO_MATCH_BYTES, 65536);
	bcm1480_controller.io_map_base -= bcm1480_controller.io_offset;
	set_io_port_base(bcm1480_controller.io_map_base);

	रेजिस्टर_pci_controller(&bcm1480_controller);

#अगर_घोषित CONFIG_VGA_CONSOLE
	console_lock();
	करो_take_over_console(&vga_con, 0, MAX_NR_CONSOLES-1, 1);
	console_unlock();
#पूर्ण_अगर
	वापस 0;
पूर्ण

arch_initcall(bcm1480_pcibios_init);
