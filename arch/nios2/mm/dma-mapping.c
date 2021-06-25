<शैली गुरु>
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 *  Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 *
 * Based on DMA code from MIPS.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/cache.h>
#समावेश <यंत्र/cacheflush.h>

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	व्योम *vaddr = phys_to_virt(paddr);

	चयन (dir) अणु
	हाल DMA_FROM_DEVICE:
		invalidate_dcache_range((अचिन्हित दीर्घ)vaddr,
			(अचिन्हित दीर्घ)(vaddr + size));
		अवरोध;
	हाल DMA_TO_DEVICE:
		/*
		 * We just need to flush the caches here , but Nios2 flush
		 * inकाष्ठाion will करो both ग_लिखोback and invalidate.
		 */
	हाल DMA_BIसूचीECTIONAL: /* flush and invalidate */
		flush_dcache_range((अचिन्हित दीर्घ)vaddr,
			(अचिन्हित दीर्घ)(vaddr + size));
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	व्योम *vaddr = phys_to_virt(paddr);

	चयन (dir) अणु
	हाल DMA_BIसूचीECTIONAL:
	हाल DMA_FROM_DEVICE:
		invalidate_dcache_range((अचिन्हित दीर्घ)vaddr,
			(अचिन्हित दीर्घ)(vaddr + size));
		अवरोध;
	हाल DMA_TO_DEVICE:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)page_address(page);

	flush_dcache_range(start, start + size);
पूर्ण

व्योम *arch_dma_set_uncached(व्योम *ptr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)ptr;

	addr |= CONFIG_NIOS2_IO_REGION_BASE;

	वापस (व्योम *)ptr;
पूर्ण
