<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 * DMA mapping callbacks...
 */

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/pagewalk.h>

#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/spr_defs.h>
#समावेश <यंत्र/tlbflush.h>

अटल पूर्णांक
page_set_nocache(pte_t *pte, अचिन्हित दीर्घ addr,
		 अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	अचिन्हित दीर्घ cl;
	काष्ठा cpuinfo_or1k *cpuinfo = &cpuinfo_or1k[smp_processor_id()];

	pte_val(*pte) |= _PAGE_CI;

	/*
	 * Flush the page out of the TLB so that the new page flags get
	 * picked up next समय there's an access
	 */
	flush_tlb_page(शून्य, addr);

	/* Flush page out of dcache */
	क्रम (cl = __pa(addr); cl < __pa(next); cl += cpuinfo->dcache_block_size)
		mtspr(SPR_DCBFR, cl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops set_nocache_walk_ops = अणु
	.pte_entry		= page_set_nocache,
पूर्ण;

अटल पूर्णांक
page_clear_nocache(pte_t *pte, अचिन्हित दीर्घ addr,
		   अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	pte_val(*pte) &= ~_PAGE_CI;

	/*
	 * Flush the page out of the TLB so that the new page flags get
	 * picked up next समय there's an access
	 */
	flush_tlb_page(शून्य, addr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops clear_nocache_walk_ops = अणु
	.pte_entry		= page_clear_nocache,
पूर्ण;

व्योम *arch_dma_set_uncached(व्योम *cpu_addr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ va = (अचिन्हित दीर्घ)cpu_addr;
	पूर्णांक error;

	/*
	 * We need to iterate through the pages, clearing the dcache क्रम
	 * them and setting the cache-inhibit bit.
	 */
	mmap_पढ़ो_lock(&init_mm);
	error = walk_page_range(&init_mm, va, va + size, &set_nocache_walk_ops,
			शून्य);
	mmap_पढ़ो_unlock(&init_mm);

	अगर (error)
		वापस ERR_PTR(error);
	वापस cpu_addr;
पूर्ण

व्योम arch_dma_clear_uncached(व्योम *cpu_addr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ va = (अचिन्हित दीर्घ)cpu_addr;

	mmap_पढ़ो_lock(&init_mm);
	/* walk_page_range shouldn't be able to fail here */
	WARN_ON(walk_page_range(&init_mm, va, va + size,
			&clear_nocache_walk_ops, शून्य));
	mmap_पढ़ो_unlock(&init_mm);
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	अचिन्हित दीर्घ cl;
	काष्ठा cpuinfo_or1k *cpuinfo = &cpuinfo_or1k[smp_processor_id()];

	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		/* Flush the dcache क्रम the requested range */
		क्रम (cl = addr; cl < addr + size;
		     cl += cpuinfo->dcache_block_size)
			mtspr(SPR_DCBFR, cl);
		अवरोध;
	हाल DMA_FROM_DEVICE:
		/* Invalidate the dcache क्रम the requested range */
		क्रम (cl = addr; cl < addr + size;
		     cl += cpuinfo->dcache_block_size)
			mtspr(SPR_DCBIR, cl);
		अवरोध;
	शेष:
		/*
		 * NOTE: If dir == DMA_BIसूचीECTIONAL then there's no need to
		 * flush nor invalidate the cache here as the area will need
		 * to be manually synced anyway.
		 */
		अवरोध;
	पूर्ण
पूर्ण
