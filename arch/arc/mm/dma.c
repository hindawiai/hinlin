<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/dma-map-ops.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * ARCH specअगरic callbacks क्रम generic noncoherent DMA ops
 *  - hardware IOC not available (or "dma-coherent" not set क्रम device in DT)
 *  - But still handle both coherent and non-coherent requests from caller
 *
 * For DMA coherent hardware (IOC) generic code suffices
 */

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	/*
	 * Evict any existing L1 and/or L2 lines क्रम the backing page
	 * in हाल it was used earlier as a normal "cached" page.
	 * Yeah this bit us - STAR 9000898266
	 *
	 * Although core करोes call flush_cache_vmap(), it माला_लो kvaddr hence
	 * can't be used to efficiently flush L1 and/or L2 which need paddr
	 * Currently flush_cache_vmap nukes the L1 cache completely which
	 * will be optimized as a separate commit
	 */
	dma_cache_wback_inv(page_to_phys(page), size);
पूर्ण

/*
 * Cache operations depending on function and direction argument, inspired by
 * https://lkml.org/lkml/2018/5/18/979
 * "dma_sync_*_क्रम_cpu and direction=TO_DEVICE (was Re: [PATCH 02/20]
 * dma-mapping: provide a generic dma-noncoherent implementation)"
 *
 *          |   map          ==  क्रम_device     |   unmap     ==  क्रम_cpu
 *          |----------------------------------------------------------------
 * TO_DEV   |   ग_लिखोback        ग_लिखोback      |   none          none
 * FROM_DEV |   invalidate       invalidate     |   invalidate*   invalidate*
 * BIसूची    |   ग_लिखोback+inv    ग_लिखोback+inv  |   invalidate    invalidate
 *
 *     [*] needed क्रम CPU speculative prefetches
 *
 * NOTE: we करोn't check the validity of direction argument as it is करोne in
 * upper layer functions (in include/linux/dma-mapping.h)
 */

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		dma_cache_wback(paddr, size);
		अवरोध;

	हाल DMA_FROM_DEVICE:
		dma_cache_inv(paddr, size);
		अवरोध;

	हाल DMA_BIसूचीECTIONAL:
		dma_cache_wback_inv(paddr, size);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	चयन (dir) अणु
	हाल DMA_TO_DEVICE:
		अवरोध;

	/* FROM_DEVICE invalidate needed अगर speculative CPU prefetch only */
	हाल DMA_FROM_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		dma_cache_inv(paddr, size);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Plug in direct dma map ops.
 */
व्योम arch_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
			स्थिर काष्ठा iommu_ops *iommu, bool coherent)
अणु
	/*
	 * IOC hardware snoops all DMA traffic keeping the caches consistent
	 * with memory - eliding need क्रम any explicit cache मुख्यtenance of
	 * DMA buffers.
	 */
	अगर (is_isa_arcv2() && ioc_enable && coherent)
		dev->dma_coherent = true;

	dev_info(dev, "use %scoherent DMA ops\n",
		 dev->dma_coherent ? "" : "non");
पूर्ण
