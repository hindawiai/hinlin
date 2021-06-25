<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Lemote, Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */
#समावेश <linux/pci.h>

#समावेश <pci.h>
#समावेश <loongson.h>

अटल काष्ठा resource loongson_pci_mem_resource = अणु
	.name	= "pci memory space",
	.start	= LOONGSON_PCI_MEM_START,
	.end	= LOONGSON_PCI_MEM_END,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource loongson_pci_io_resource = अणु
	.name	= "pci io space",
	.start	= LOONGSON_PCI_IO_START,
	.end	= IO_SPACE_LIMIT,
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा pci_controller  loongson_pci_controller = अणु
	.pci_ops	= &loongson_pci_ops,
	.io_resource	= &loongson_pci_io_resource,
	.mem_resource	= &loongson_pci_mem_resource,
	.mem_offset	= 0x00000000UL,
	.io_offset	= 0x00000000UL,
पूर्ण;

अटल व्योम __init setup_pcimap(व्योम)
अणु
	/*
	 * local to PCI mapping क्रम CPU accessing PCI space
	 * CPU address space [256M,448M] is winकरोw क्रम accessing pci space
	 * we set pcimap_lo[0,1,2] to map it to pci space[0M,64M], [320M,448M]
	 *
	 * pcimap: PCI_MAP2  PCI_Mem_Lo2 PCI_Mem_Lo1 PCI_Mem_Lo0
	 *	     [<2G]   [384M,448M] [320M,384M] [0M,64M]
	 */
	LOONGSON_PCIMAP = LOONGSON_PCIMAP_PCIMAP_2 |
		LOONGSON_PCIMAP_WIN(2, LOONGSON_PCILO2_BASE) |
		LOONGSON_PCIMAP_WIN(1, LOONGSON_PCILO1_BASE) |
		LOONGSON_PCIMAP_WIN(0, 0);

	/*
	 * PCI-DMA to local mapping: [2G,2G+256M] -> [0M,256M]
	 */
	LOONGSON_PCIBASE0 = 0x80000000ul;   /* base: 2G -> mmap: 0M */
	/* size: 256M, burst transmission, pre-fetch enable, 64bit */
	LOONGSON_PCI_HIT0_SEL_L = 0xc000000cul;
	LOONGSON_PCI_HIT0_SEL_H = 0xfffffffful;
	LOONGSON_PCI_HIT1_SEL_L = 0x00000006ul; /* set this BAR as invalid */
	LOONGSON_PCI_HIT1_SEL_H = 0x00000000ul;
	LOONGSON_PCI_HIT2_SEL_L = 0x00000006ul; /* set this BAR as invalid */
	LOONGSON_PCI_HIT2_SEL_H = 0x00000000ul;

	/* aव्योम deadlock of PCI पढ़ोing/writing lock operation */
	LOONGSON_PCI_ISR4C = 0xd2000001ul;

	/* can not change gnt to अवरोध pci transfer when device's gnt not
	deनिश्चित क्रम some broken device */
	LOONGSON_PXARB_CFG = 0x00fe0105ul;

#अगर_घोषित CONFIG_CPU_SUPPORTS_ADDRWINCFG
	/*
	 * set cpu addr winकरोw2 to map CPU address space to PCI address space
	 */
	LOONGSON_ADDRWIN_CPUTOPCI(ADDRWIN_WIN2, LOONGSON_CPU_MEM_SRC,
		LOONGSON_PCI_MEM_DST, MMAP_CPUTOPCI_SIZE);
#पूर्ण_अगर
पूर्ण

बाह्य पूर्णांक sbx00_acpi_init(व्योम);

अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	setup_pcimap();

	loongson_pci_controller.io_map_base = mips_io_port_base;
	रेजिस्टर_pci_controller(&loongson_pci_controller);


	वापस 0;
पूर्ण

arch_initcall(pcibios_init);
