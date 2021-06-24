<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/arch/arm/mach-sa1100/pci-nanoengine.c
 *
 * PCI functions क्रम BSE nanoEngine PCI
 *
 * Copyright (C) 2010 Marcelo Roberto Jimenez <mroberto@cpti.cetuc.puc-rio.br>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <mach/nanoengine.h>
#समावेश <mach/hardware.h>

अटल व्योम __iomem *nanoengine_pci_map_bus(काष्ठा pci_bus *bus,
					    अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	अगर (bus->number != 0 || (devfn >> 3) != 0)
		वापस शून्य;

	वापस (व्योम __iomem *)न_अंकO_PCI_CONFIG_SPACE_VIRT +
		((bus->number << 16) | (devfn << 8) | (where & ~3));
पूर्ण

अटल काष्ठा pci_ops pci_nano_ops = अणु
	.map_bus = nanoengine_pci_map_bus,
	.पढ़ो	= pci_generic_config_पढ़ो32,
	.ग_लिखो	= pci_generic_config_ग_लिखो32,
पूर्ण;

अटल पूर्णांक __init pci_nanoengine_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot,
	u8 pin)
अणु
	वापस न_अंकOENGINE_IRQ_GPIO_PCI;
पूर्ण

अटल काष्ठा resource pci_io_ports =
	DEFINE_RES_IO_NAMED(0x400, 0x400, "PCI IO");

अटल काष्ठा resource pci_non_prefetchable_memory = अणु
	.name	= "PCI non-prefetchable",
	.start	= न_अंकO_PCI_MEM_RW_PHYS,
	/* nanoEngine करोcumentation says there is a 1 Megabyte winकरोw here,
	 * but PCI reports just 128 + 8 kbytes. */
	.end	= न_अंकO_PCI_MEM_RW_PHYS + न_अंकO_PCI_MEM_RW_SIZE - 1,
/*	.end	= न_अंकO_PCI_MEM_RW_PHYS + SZ_128K + SZ_8K - 1,*/
	.flags	= IORESOURCE_MEM,
पूर्ण;

/*
 * nanoEngine PCI reports 1 Megabyte of prefetchable memory, but it
 * overlaps with previously defined memory.
 *
 * Here is what happens:
 *
# dmesg
...
pci 0000:00:00.0: [8086:1209] type 0 class 0x000200
pci 0000:00:00.0: reg 10: [mem 0x00021000-0x00021fff]
pci 0000:00:00.0: reg 14: [io  0x0000-0x003f]
pci 0000:00:00.0: reg 18: [mem 0x00000000-0x0001ffff]
pci 0000:00:00.0: reg 30: [mem 0x00000000-0x000fffff pref]
pci 0000:00:00.0: supports D1 D2
pci 0000:00:00.0: PME# supported from D0 D1 D2 D3hot
pci 0000:00:00.0: PME# disabled
PCI: bus0: Fast back to back transfers enabled
pci 0000:00:00.0: BAR 6: can't assign mem pref (size 0x100000)
pci 0000:00:00.0: BAR 2: asचिन्हित [mem 0x18600000-0x1861ffff]
pci 0000:00:00.0: BAR 2: set to [mem 0x18600000-0x1861ffff] (PCI address [0x0-0x1ffff])
pci 0000:00:00.0: BAR 0: asचिन्हित [mem 0x18620000-0x18620fff]
pci 0000:00:00.0: BAR 0: set to [mem 0x18620000-0x18620fff] (PCI address [0x20000-0x20fff])
pci 0000:00:00.0: BAR 1: asचिन्हित [io  0x0400-0x043f]
pci 0000:00:00.0: BAR 1: set to [io  0x0400-0x043f] (PCI address [0x0-0x3f])
 *
 * On the other hand, अगर we करो not request the prefetchable memory resource,
 * linux will alloc it first and the two non-prefetchable memory areas that
 * are our real पूर्णांकerest will not be mapped. So we choose to map it to an
 * unused area. It माला_लो recognized as expansion ROM, but becomes disabled.
 *
 * Here is what happens then:
 *
# dmesg
...
pci 0000:00:00.0: [8086:1209] type 0 class 0x000200
pci 0000:00:00.0: reg 10: [mem 0x00021000-0x00021fff]
pci 0000:00:00.0: reg 14: [io  0x0000-0x003f]
pci 0000:00:00.0: reg 18: [mem 0x00000000-0x0001ffff]
pci 0000:00:00.0: reg 30: [mem 0x00000000-0x000fffff pref]
pci 0000:00:00.0: supports D1 D2
pci 0000:00:00.0: PME# supported from D0 D1 D2 D3hot
pci 0000:00:00.0: PME# disabled
PCI: bus0: Fast back to back transfers enabled
pci 0000:00:00.0: BAR 6: asचिन्हित [mem 0x78000000-0x780fffff pref]
pci 0000:00:00.0: BAR 2: asचिन्हित [mem 0x18600000-0x1861ffff]
pci 0000:00:00.0: BAR 2: set to [mem 0x18600000-0x1861ffff] (PCI address [0x0-0x1ffff])
pci 0000:00:00.0: BAR 0: asचिन्हित [mem 0x18620000-0x18620fff]
pci 0000:00:00.0: BAR 0: set to [mem 0x18620000-0x18620fff] (PCI address [0x20000-0x20fff])
pci 0000:00:00.0: BAR 1: asचिन्हित [io  0x0400-0x043f]
pci 0000:00:00.0: BAR 1: set to [io  0x0400-0x043f] (PCI address [0x0-0x3f])

# lspci -vv -s 0000:00:00.0
00:00.0 Class 0200: Device 8086:1209 (rev 09)
        Control: I/O+ Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr+ Stepping- SERR+ FastB2B- DisINTx-
        Status: Cap+ 66MHz- UDF- FastB2B+ ParErr- DEVSEL=medium >TAbort- <TAbort- <MAbort- >SERR+ <PERR+ INTx-
        Latency: 0 (2000ns min, 14000ns max), Cache Line Size: 32 bytes
        Interrupt: pin A routed to IRQ 0
        Region 0: Memory at 18620000 (32-bit, non-prefetchable) [size=4K]
        Region 1: I/O ports at 0400 [size=64]
        Region 2: [भव] Memory at 18600000 (32-bit, non-prefetchable) [size=128K]
        [भव] Expansion ROM at 78000000 [disabled] [size=1M]
        Capabilities: [dc] Power Management version 2
                Flags: PMEClk- DSI+ D1+ D2+ AuxCurrent=0mA PME(D0+,D1+,D2+,D3hot+,D3cold-)
                Status: D0 NoSoftRst- PME-Enable- DSel=0 DScale=2 PME-
        Kernel driver in use: e100
        Kernel modules: e100
 *
 */
अटल काष्ठा resource pci_prefetchable_memory = अणु
	.name	= "PCI prefetchable",
	.start	= 0x78000000,
	.end	= 0x78000000 + न_अंकO_PCI_MEM_RW_SIZE - 1,
	.flags	= IORESOURCE_MEM  | IORESOURCE_PREFETCH,
पूर्ण;

अटल पूर्णांक __init pci_nanoengine_setup_resources(काष्ठा pci_sys_data *sys)
अणु
	अगर (request_resource(&ioport_resource, &pci_io_ports)) अणु
		prपूर्णांकk(KERN_ERR "PCI: unable to allocate io port region\n");
		वापस -EBUSY;
	पूर्ण
	अगर (request_resource(&iomem_resource, &pci_non_prefetchable_memory)) अणु
		release_resource(&pci_io_ports);
		prपूर्णांकk(KERN_ERR "PCI: unable to allocate non prefetchable\n");
		वापस -EBUSY;
	पूर्ण
	अगर (request_resource(&iomem_resource, &pci_prefetchable_memory)) अणु
		release_resource(&pci_io_ports);
		release_resource(&pci_non_prefetchable_memory);
		prपूर्णांकk(KERN_ERR "PCI: unable to allocate prefetchable\n");
		वापस -EBUSY;
	पूर्ण
	pci_add_resource_offset(&sys->resources, &pci_io_ports, sys->io_offset);
	pci_add_resource_offset(&sys->resources,
				&pci_non_prefetchable_memory, sys->mem_offset);
	pci_add_resource_offset(&sys->resources,
				&pci_prefetchable_memory, sys->mem_offset);

	वापस 1;
पूर्ण

पूर्णांक __init pci_nanoengine_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys)
अणु
	पूर्णांक ret = 0;

	pcibios_min_io = 0;
	pcibios_min_mem = 0;

	अगर (nr == 0) अणु
		sys->mem_offset = न_अंकO_PCI_MEM_RW_PHYS;
		sys->io_offset = 0x400;
		ret = pci_nanoengine_setup_resources(sys);
		/* Enable alternate memory bus master mode, see
		 * "Intel StrongARM SA1110 Developer's Manual",
		 * section 10.8, "Alternate Memory Bus Master Mode". */
		GPDR = (GPDR & ~GPIO_MBREQ) | GPIO_MBGNT;
		GAFR |= GPIO_MBGNT | GPIO_MBREQ;
		TUCR |= TUCR_MBGPIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा hw_pci nanoengine_pci __initdata = अणु
	.map_irq		= pci_nanoengine_map_irq,
	.nr_controllers		= 1,
	.ops			= &pci_nano_ops,
	.setup			= pci_nanoengine_setup,
पूर्ण;

अटल पूर्णांक __init nanoengine_pci_init(व्योम)
अणु
	अगर (machine_is_nanoengine())
		pci_common_init(&nanoengine_pci);
	वापस 0;
पूर्ण

subsys_initcall(nanoengine_pci_init);
