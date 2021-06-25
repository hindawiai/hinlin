<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DMA implementation क्रम Hexagon
 *
 * Copyright (c) 2010-2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/memblock.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/module.h>
#समावेश <यंत्र/page.h>

अटल काष्ठा gen_pool *coherent_pool;


/* Allocates from a pool of uncached memory that was reserved at boot समय */

व्योम *arch_dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_addr,
		gfp_t flag, अचिन्हित दीर्घ attrs)
अणु
	व्योम *ret;

	/*
	 * Our max_low_pfn should have been backed off by 16MB in
	 * mm/init.c to create DMA coherent space.  Use that as the VA
	 * क्रम the pool.
	 */

	अगर (coherent_pool == शून्य) अणु
		coherent_pool = gen_pool_create(PAGE_SHIFT, -1);

		अगर (coherent_pool == शून्य)
			panic("Can't create %s() memory pool!", __func__);
		अन्यथा
			gen_pool_add(coherent_pool,
				(अचिन्हित दीर्घ)pfn_to_virt(max_low_pfn),
				hexagon_coherent_pool_size, -1);
	पूर्ण

	ret = (व्योम *) gen_pool_alloc(coherent_pool, size);

	अगर (ret) अणु
		स_रखो(ret, 0, size);
		*dma_addr = (dma_addr_t) virt_to_phys(ret);
	पूर्ण अन्यथा
		*dma_addr = ~0;

	वापस ret;
पूर्ण

व्योम arch_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
		dma_addr_t dma_addr, अचिन्हित दीर्घ attrs)
अणु
	gen_pool_मुक्त(coherent_pool, (अचिन्हित दीर्घ) vaddr, size);
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	व्योम *addr = phys_to_virt(paddr);

	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		hexagon_clean_dcache_range((अचिन्हित दीर्घ) addr,
		(अचिन्हित दीर्घ) addr + size);
		अवरोध;
	हाल DMA_FROM_DEVICE:
		hexagon_inv_dcache_range((अचिन्हित दीर्घ) addr,
		(अचिन्हित दीर्घ) addr + size);
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		flush_dcache_range((अचिन्हित दीर्घ) addr,
		(अचिन्हित दीर्घ) addr + size);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
