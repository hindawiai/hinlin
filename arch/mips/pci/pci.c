<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2003, 04, 11 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2011 Wind River Systems,
 *   written by Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cpu-info.h>

अचिन्हित दीर्घ PCIBIOS_MIN_IO;
EXPORT_SYMBOL(PCIBIOS_MIN_IO);

अचिन्हित दीर्घ PCIBIOS_MIN_MEM;
EXPORT_SYMBOL(PCIBIOS_MIN_MEM);

अटल पूर्णांक __init pcibios_set_cache_line_size(व्योम)
अणु
	अचिन्हित पूर्णांक lsize;

	/*
	 * Set PCI cacheline size to that of the highest level in the
	 * cache hierarchy.
	 */
	lsize = cpu_dcache_line_size();
	lsize = cpu_scache_line_size() ? : lsize;
	lsize = cpu_tcache_line_size() ? : lsize;

	BUG_ON(!lsize);

	pci_dfl_cache_line_size = lsize >> 2;

	pr_debug("PCI: pci_cache_line_size set to %d bytes\n", lsize);
	वापस 0;
पूर्ण
arch_initcall(pcibios_set_cache_line_size);

व्योम pci_resource_to_user(स्थिर काष्ठा pci_dev *dev, पूर्णांक bar,
			  स्थिर काष्ठा resource *rsrc, resource_माप_प्रकार *start,
			  resource_माप_प्रकार *end)
अणु
	phys_addr_t size = resource_size(rsrc);

	*start = fixup_bigphys_addr(rsrc->start, size);
	*end = rsrc->start + size - 1;
पूर्ण
