<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/cache.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/proc-fns.h>

अटल अंतरभूत व्योम cache_op(phys_addr_t paddr, माप_प्रकार size,
		व्योम (*fn)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end))
अणु
	काष्ठा page *page = pfn_to_page(paddr >> PAGE_SHIFT);
	अचिन्हित offset = paddr & ~PAGE_MASK;
	माप_प्रकार left = size;
	अचिन्हित दीर्घ start;

	करो अणु
		माप_प्रकार len = left;

		अगर (PageHighMem(page)) अणु
			व्योम *addr;

			अगर (offset + len > PAGE_SIZE) अणु
				अगर (offset >= PAGE_SIZE) अणु
					page += offset >> PAGE_SHIFT;
					offset &= ~PAGE_MASK;
				पूर्ण
				len = PAGE_SIZE - offset;
			पूर्ण

			addr = kmap_atomic(page);
			start = (अचिन्हित दीर्घ)(addr + offset);
			fn(start, start + len);
			kunmap_atomic(addr);
		पूर्ण अन्यथा अणु
			start = (अचिन्हित दीर्घ)phys_to_virt(paddr);
			fn(start, start + size);
		पूर्ण
		offset = 0;
		page++;
		left -= len;
	पूर्ण जबतक (left);
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_FROM_DEVICE:
		अवरोध;
	हाल DMA_TO_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		cache_op(paddr, size, cpu_dma_wb_range);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		अवरोध;
	हाल DMA_FROM_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		cache_op(paddr, size, cpu_dma_inval_range);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	cache_op(page_to_phys(page), size, cpu_dma_wbinval_range);
पूर्ण
