<शैली गुरु>
/*
 * Register PCI controller.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 2004, 05 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2001, 2002, 2003 by Liam Davies (ldavies@agile.tv)
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/gt64120.h>

बाह्य काष्ठा pci_ops gt64xxx_pci0_ops;

अटल काष्ठा resource cobalt_mem_resource = अणु
	.start	= GT_DEF_PCI0_MEM0_BASE,
	.end	= GT_DEF_PCI0_MEM0_BASE + GT_DEF_PCI0_MEM0_SIZE - 1,
	.name	= "PCI memory",
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource cobalt_io_resource = अणु
	.start	= 0x1000,
	.end	= 0xffffffUL,
	.name	= "PCI I/O",
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा pci_controller cobalt_pci_controller = अणु
	.pci_ops	= &gt64xxx_pci0_ops,
	.mem_resource	= &cobalt_mem_resource,
	.io_resource	= &cobalt_io_resource,
	.io_offset	= 0 - GT_DEF_PCI0_IO_BASE,
	.io_map_base	= CKSEG1ADDR(GT_DEF_PCI0_IO_BASE),
पूर्ण;

अटल पूर्णांक __init cobalt_pci_init(व्योम)
अणु
	रेजिस्टर_pci_controller(&cobalt_pci_controller);

	वापस 0;
पूर्ण

arch_initcall(cobalt_pci_init);
