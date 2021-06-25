<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/cache.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/types.h>
#समावेश <linux/version.h>
#समावेश <यंत्र/cache.h>

अटल अंतरभूत व्योम cache_op(phys_addr_t paddr, माप_प्रकार size,
			    व्योम (*fn)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end))
अणु
	काष्ठा page *page    = phys_to_page(paddr);
	व्योम *start          = __va(page_to_phys(page));
	अचिन्हित दीर्घ offset = offset_in_page(paddr);
	माप_प्रकार left          = size;

	करो अणु
		माप_प्रकार len = left;

		अगर (offset + len > PAGE_SIZE)
			len = PAGE_SIZE - offset;

		अगर (PageHighMem(page)) अणु
			start = kmap_atomic(page);

			fn((अचिन्हित दीर्घ)start + offset,
					(अचिन्हित दीर्घ)start + offset + len);

			kunmap_atomic(start);
		पूर्ण अन्यथा अणु
			fn((अचिन्हित दीर्घ)start + offset,
					(अचिन्हित दीर्घ)start + offset + len);
		पूर्ण
		offset = 0;

		page++;
		start += PAGE_SIZE;
		left -= len;
	पूर्ण जबतक (left);
पूर्ण

अटल व्योम dma_wbinv_set_zero_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	स_रखो((व्योम *)start, 0, end - start);
	dma_wbinv_range(start, end);
पूर्ण

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	cache_op(page_to_phys(page), size, dma_wbinv_set_zero_range);
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		cache_op(paddr, size, dma_wb_range);
		अवरोध;
	हाल DMA_FROM_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		cache_op(paddr, size, dma_wbinv_range);
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
		वापस;
	हाल DMA_FROM_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		cache_op(paddr, size, dma_inv_range);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
