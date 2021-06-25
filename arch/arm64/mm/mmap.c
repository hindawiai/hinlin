<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/mmap.c
 *
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/page.h>

/*
 * You really shouldn't be using पढ़ो() or ग_लिखो() on /dev/mem.  This might go
 * away in the future.
 */
पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार size)
अणु
	/*
	 * Check whether addr is covered by a memory region without the
	 * MEMBLOCK_NOMAP attribute, and whether that region covers the
	 * entire range. In theory, this could lead to false negatives
	 * अगर the range is covered by distinct but adjacent memory regions
	 * that only dअगरfer in other attributes. However, few of such
	 * attributes have been defined, and it is debatable whether it
	 * follows that /dev/mem पढ़ो() calls should be able traverse
	 * such boundaries.
	 */
	वापस memblock_is_region_memory(addr, size) &&
	       memblock_is_map_memory(addr);
पूर्ण

/*
 * Do not allow /dev/mem mappings beyond the supported physical range.
 */
पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size)
अणु
	वापस !(((pfn << PAGE_SHIFT) + size) & ~PHYS_MASK);
पूर्ण
