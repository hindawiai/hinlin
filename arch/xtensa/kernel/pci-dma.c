<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DMA coherent memory allocation.
 *
 * Copyright (C) 2002 - 2005 Tensilica Inc.
 * Copyright (C) 2015 Cadence Design Systems Inc.
 *
 * Based on version क्रम i386.
 *
 * Chris Zankel <chris@zankel.net>
 * Joe Taylor <joe@tensilica.com, joetylr@yahoo.com>
 */

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/platक्रमm.h>

अटल व्योम करो_cache_op(phys_addr_t paddr, माप_प्रकार size,
			व्योम (*fn)(अचिन्हित दीर्घ, अचिन्हित दीर्घ))
अणु
	अचिन्हित दीर्घ off = paddr & (PAGE_SIZE - 1);
	अचिन्हित दीर्घ pfn = PFN_DOWN(paddr);
	काष्ठा page *page = pfn_to_page(pfn);

	अगर (!PageHighMem(page))
		fn((अचिन्हित दीर्घ)phys_to_virt(paddr), size);
	अन्यथा
		जबतक (size > 0) अणु
			माप_प्रकार sz = min_t(माप_प्रकार, size, PAGE_SIZE - off);
			व्योम *vaddr = kmap_atomic(page);

			fn((अचिन्हित दीर्घ)vaddr + off, sz);
			kunmap_atomic(vaddr);
			off = 0;
			++page;
			size -= sz;
		पूर्ण
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_BIसूचीECTIONAL:
	हाल DMA_FROM_DEVICE:
		करो_cache_op(paddr, size, __invalidate_dcache_range);
		अवरोध;

	हाल DMA_NONE:
		BUG();
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_BIसूचीECTIONAL:
	हाल DMA_TO_DEVICE:
		अगर (XCHAL_DCACHE_IS_WRITEBACK)
			करो_cache_op(paddr, size, __flush_dcache_range);
		अवरोध;

	हाल DMA_NONE:
		BUG();
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	__invalidate_dcache_range((अचिन्हित दीर्घ)page_address(page), size);
पूर्ण

/*
 * Memory caching is platक्रमm-dependent in noMMU xtensa configurations.
 * This function should be implemented in platक्रमm code in order to enable
 * coherent DMA memory operations when CONFIG_MMU is not enabled.
 */
#अगर_घोषित CONFIG_MMU
व्योम *arch_dma_set_uncached(व्योम *p, माप_प्रकार size)
अणु
	वापस p + XCHAL_KSEG_BYPASS_VADDR - XCHAL_KSEG_CACHED_VADDR;
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */
