<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PowerPC version derived from arch/arm/mm/consistent.c
 *    Copyright (C) 2001 Dan Malek (dmalek@jlc.net)
 *
 *  Copyright (C) 2000 Russell King
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/dma.h>

/*
 * make an area consistent.
 */
अटल व्योम __dma_sync(व्योम *vaddr, माप_प्रकार size, पूर्णांक direction)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)vaddr;
	अचिन्हित दीर्घ end   = start + size;

	चयन (direction) अणु
	हाल DMA_NONE:
		BUG();
	हाल DMA_FROM_DEVICE:
		/*
		 * invalidate only when cache-line aligned otherwise there is
		 * the potential क्रम discarding uncommitted data from the cache
		 */
		अगर ((start | end) & (L1_CACHE_BYTES - 1))
			flush_dcache_range(start, end);
		अन्यथा
			invalidate_dcache_range(start, end);
		अवरोध;
	हाल DMA_TO_DEVICE:		/* ग_लिखोback only */
		clean_dcache_range(start, end);
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:	/* ग_लिखोback and invalidate */
		flush_dcache_range(start, end);
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
/*
 * __dma_sync_page() implementation क्रम प्रणालीs using highmem.
 * In this हाल, each page of a buffer must be kmapped/kunmapped
 * in order to have a भव address क्रम __dma_sync(). This must
 * not sleep so kmap_atomic()/kunmap_atomic() are used.
 *
 * Note: yes, it is possible and correct to have a buffer extend
 * beyond the first page.
 */
अटल अंतरभूत व्योम __dma_sync_page_highmem(काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार size, पूर्णांक direction)
अणु
	माप_प्रकार seg_size = min((माप_प्रकार)(PAGE_SIZE - offset), size);
	माप_प्रकार cur_size = seg_size;
	अचिन्हित दीर्घ flags, start, seg_offset = offset;
	पूर्णांक nr_segs = 1 + ((size - seg_size) + PAGE_SIZE - 1)/PAGE_SIZE;
	पूर्णांक seg_nr = 0;

	local_irq_save(flags);

	करो अणु
		start = (अचिन्हित दीर्घ)kmap_atomic(page + seg_nr) + seg_offset;

		/* Sync this buffer segment */
		__dma_sync((व्योम *)start, seg_size, direction);
		kunmap_atomic((व्योम *)start);
		seg_nr++;

		/* Calculate next buffer segment size */
		seg_size = min((माप_प्रकार)PAGE_SIZE, size - cur_size);

		/* Add the segment size to our running total */
		cur_size += seg_size;
		seg_offset = 0;
	पूर्ण जबतक (seg_nr < nr_segs);

	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

/*
 * __dma_sync_page makes memory consistent. identical to __dma_sync, but
 * takes a काष्ठा page instead of a भव address
 */
अटल व्योम __dma_sync_page(phys_addr_t paddr, माप_प्रकार size, पूर्णांक dir)
अणु
	काष्ठा page *page = pfn_to_page(paddr >> PAGE_SHIFT);
	अचिन्हित offset = paddr & ~PAGE_MASK;

#अगर_घोषित CONFIG_HIGHMEM
	__dma_sync_page_highmem(page, offset, size, dir);
#अन्यथा
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)page_address(page) + offset;
	__dma_sync((व्योम *)start, size, dir);
#पूर्ण_अगर
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_sync_page(paddr, size, dir);
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_sync_page(paddr, size, dir);
पूर्ण

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ kaddr = (अचिन्हित दीर्घ)page_address(page);

	flush_dcache_range(kaddr, kaddr + size);
पूर्ण
