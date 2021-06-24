<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Re-map IO memory to kernel address space so that we can access it.
 *
 * These functions should only be used when it is necessary to map a
 * physical address space पूर्णांकo the kernel address space beक्रमe ioremap()
 * can be used, e.g. early in boot beक्रमe paging_init().
 *
 * Copyright (C) 2009  Matt Fleming
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/proc_fs.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश "ioremap.h"

काष्ठा ioremap_map अणु
	व्योम __iomem *addr;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ fixmap_addr;
पूर्ण;

अटल काष्ठा ioremap_map ioremap_maps[FIX_N_IOREMAPS];

व्योम __init ioremap_fixed_init(व्योम)
अणु
	काष्ठा ioremap_map *map;
	पूर्णांक i;

	क्रम (i = 0; i < FIX_N_IOREMAPS; i++) अणु
		map = &ioremap_maps[i];
		map->fixmap_addr = __fix_to_virt(FIX_IOREMAP_BEGIN + i);
	पूर्ण
पूर्ण

व्योम __init __iomem *
ioremap_fixed(phys_addr_t phys_addr, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	क्रमागत fixed_addresses idx0, idx;
	काष्ठा ioremap_map *map;
	अचिन्हित पूर्णांक nrpages;
	अचिन्हित दीर्घ offset;
	पूर्णांक i, slot;

	/*
	 * Mappings have to be page-aligned
	 */
	offset = phys_addr & ~PAGE_MASK;
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(phys_addr + size) - phys_addr;

	slot = -1;
	क्रम (i = 0; i < FIX_N_IOREMAPS; i++) अणु
		map = &ioremap_maps[i];
		अगर (!map->addr) अणु
			map->size = size;
			slot = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (slot < 0)
		वापस शून्य;

	/*
	 * Mappings have to fit in the FIX_IOREMAP area.
	 */
	nrpages = size >> PAGE_SHIFT;
	अगर (nrpages > FIX_N_IOREMAPS)
		वापस शून्य;

	/*
	 * Ok, go क्रम it..
	 */
	idx0 = FIX_IOREMAP_BEGIN + slot;
	idx = idx0;
	जबतक (nrpages > 0) अणु
		pgprot_val(prot) |= _PAGE_WIRED;
		__set_fixmap(idx, phys_addr, prot);
		phys_addr += PAGE_SIZE;
		idx++;
		--nrpages;
	पूर्ण

	map->addr = (व्योम __iomem *)(offset + map->fixmap_addr);
	वापस map->addr;
पूर्ण

पूर्णांक iounmap_fixed(व्योम __iomem *addr)
अणु
	क्रमागत fixed_addresses idx;
	काष्ठा ioremap_map *map;
	अचिन्हित पूर्णांक nrpages;
	पूर्णांक i, slot;

	slot = -1;
	क्रम (i = 0; i < FIX_N_IOREMAPS; i++) अणु
		map = &ioremap_maps[i];
		अगर (map->addr == addr) अणु
			slot = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If we करोn't match, it's not क्रम us.
	 */
	अगर (slot < 0)
		वापस -EINVAL;

	nrpages = map->size >> PAGE_SHIFT;

	idx = FIX_IOREMAP_BEGIN + slot + nrpages - 1;
	जबतक (nrpages > 0) अणु
		__clear_fixmap(idx, __pgprot(_PAGE_WIRED));
		--idx;
		--nrpages;
	पूर्ण

	map->size = 0;
	map->addr = शून्य;

	वापस 0;
पूर्ण
