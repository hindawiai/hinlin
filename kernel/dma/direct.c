<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018-2020 Christoph Hellwig.
 *
 * DMA operations that map physical memory directly without using an IOMMU.
 */
#समावेश <linux/memblock.h> /* क्रम max_pfn */
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/pfn.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/slab.h>
#समावेश "direct.h"

/*
 * Most architectures use ZONE_DMA क्रम the first 16 Megabytes, but some use
 * it क्रम entirely dअगरferent regions. In that हाल the arch code needs to
 * override the variable below क्रम dma-direct to work properly.
 */
अचिन्हित पूर्णांक zone_dma_bits __ro_after_init = 24;

अटल अंतरभूत dma_addr_t phys_to_dma_direct(काष्ठा device *dev,
		phys_addr_t phys)
अणु
	अगर (क्रमce_dma_unencrypted(dev))
		वापस phys_to_dma_unencrypted(dev, phys);
	वापस phys_to_dma(dev, phys);
पूर्ण

अटल अंतरभूत काष्ठा page *dma_direct_to_page(काष्ठा device *dev,
		dma_addr_t dma_addr)
अणु
	वापस pfn_to_page(PHYS_PFN(dma_to_phys(dev, dma_addr)));
पूर्ण

u64 dma_direct_get_required_mask(काष्ठा device *dev)
अणु
	phys_addr_t phys = (phys_addr_t)(max_pfn - 1) << PAGE_SHIFT;
	u64 max_dma = phys_to_dma_direct(dev, phys);

	वापस (1ULL << (fls64(max_dma) - 1)) * 2 - 1;
पूर्ण

अटल gfp_t dma_direct_optimal_gfp_mask(काष्ठा device *dev, u64 dma_mask,
				  u64 *phys_limit)
अणु
	u64 dma_limit = min_not_zero(dma_mask, dev->bus_dma_limit);

	/*
	 * Optimistically try the zone that the physical address mask falls
	 * पूर्णांकo first.  If that वापसs memory that isn't actually addressable
	 * we will fallback to the next lower zone and try again.
	 *
	 * Note that GFP_DMA32 and GFP_DMA are no ops without the corresponding
	 * zones.
	 */
	*phys_limit = dma_to_phys(dev, dma_limit);
	अगर (*phys_limit <= DMA_BIT_MASK(zone_dma_bits))
		वापस GFP_DMA;
	अगर (*phys_limit <= DMA_BIT_MASK(32))
		वापस GFP_DMA32;
	वापस 0;
पूर्ण

अटल bool dma_coherent_ok(काष्ठा device *dev, phys_addr_t phys, माप_प्रकार size)
अणु
	dma_addr_t dma_addr = phys_to_dma_direct(dev, phys);

	अगर (dma_addr == DMA_MAPPING_ERROR)
		वापस false;
	वापस dma_addr + size - 1 <=
		min_not_zero(dev->coherent_dma_mask, dev->bus_dma_limit);
पूर्ण

अटल काष्ठा page *__dma_direct_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		gfp_t gfp)
अणु
	पूर्णांक node = dev_to_node(dev);
	काष्ठा page *page = शून्य;
	u64 phys_limit;

	WARN_ON_ONCE(!PAGE_ALIGNED(size));

	gfp |= dma_direct_optimal_gfp_mask(dev, dev->coherent_dma_mask,
					   &phys_limit);
	page = dma_alloc_contiguous(dev, size, gfp);
	अगर (page && !dma_coherent_ok(dev, page_to_phys(page), size)) अणु
		dma_मुक्त_contiguous(dev, page, size);
		page = शून्य;
	पूर्ण
again:
	अगर (!page)
		page = alloc_pages_node(node, gfp, get_order(size));
	अगर (page && !dma_coherent_ok(dev, page_to_phys(page), size)) अणु
		dma_मुक्त_contiguous(dev, page, size);
		page = शून्य;

		अगर (IS_ENABLED(CONFIG_ZONE_DMA32) &&
		    phys_limit < DMA_BIT_MASK(64) &&
		    !(gfp & (GFP_DMA32 | GFP_DMA))) अणु
			gfp |= GFP_DMA32;
			जाओ again;
		पूर्ण

		अगर (IS_ENABLED(CONFIG_ZONE_DMA) && !(gfp & GFP_DMA)) अणु
			gfp = (gfp & ~GFP_DMA32) | GFP_DMA;
			जाओ again;
		पूर्ण
	पूर्ण

	वापस page;
पूर्ण

अटल व्योम *dma_direct_alloc_from_pool(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp)
अणु
	काष्ठा page *page;
	u64 phys_mask;
	व्योम *ret;

	gfp |= dma_direct_optimal_gfp_mask(dev, dev->coherent_dma_mask,
					   &phys_mask);
	page = dma_alloc_from_pool(dev, size, &ret, gfp, dma_coherent_ok);
	अगर (!page)
		वापस शून्य;
	*dma_handle = phys_to_dma_direct(dev, page_to_phys(page));
	वापस ret;
पूर्ण

व्योम *dma_direct_alloc(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page *page;
	व्योम *ret;
	पूर्णांक err;

	size = PAGE_ALIGN(size);
	अगर (attrs & DMA_ATTR_NO_WARN)
		gfp |= __GFP_NOWARN;

	अगर ((attrs & DMA_ATTR_NO_KERNEL_MAPPING) &&
	    !क्रमce_dma_unencrypted(dev)) अणु
		page = __dma_direct_alloc_pages(dev, size, gfp & ~__GFP_ZERO);
		अगर (!page)
			वापस शून्य;
		/* हटाओ any dirty cache lines on the kernel alias */
		अगर (!PageHighMem(page))
			arch_dma_prep_coherent(page, size);
		*dma_handle = phys_to_dma_direct(dev, page_to_phys(page));
		/* वापस the page poपूर्णांकer as the opaque cookie */
		वापस page;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_ARCH_HAS_DMA_SET_UNCACHED) &&
	    !IS_ENABLED(CONFIG_DMA_सूचीECT_REMAP) &&
	    !dev_is_dma_coherent(dev))
		वापस arch_dma_alloc(dev, size, dma_handle, gfp, attrs);

	/*
	 * Remapping or decrypting memory may block. If either is required and
	 * we can't block, allocate the memory from the atomic pools.
	 */
	अगर (IS_ENABLED(CONFIG_DMA_COHERENT_POOL) &&
	    !gfpflags_allow_blocking(gfp) &&
	    (क्रमce_dma_unencrypted(dev) ||
	     (IS_ENABLED(CONFIG_DMA_सूचीECT_REMAP) && !dev_is_dma_coherent(dev))))
		वापस dma_direct_alloc_from_pool(dev, size, dma_handle, gfp);

	/* we always manually zero the memory once we are करोne */
	page = __dma_direct_alloc_pages(dev, size, gfp & ~__GFP_ZERO);
	अगर (!page)
		वापस शून्य;

	अगर ((IS_ENABLED(CONFIG_DMA_सूचीECT_REMAP) &&
	     !dev_is_dma_coherent(dev)) ||
	    (IS_ENABLED(CONFIG_DMA_REMAP) && PageHighMem(page))) अणु
		/* हटाओ any dirty cache lines on the kernel alias */
		arch_dma_prep_coherent(page, size);

		/* create a coherent mapping */
		ret = dma_common_contiguous_remap(page, size,
				dma_pgprot(dev, PAGE_KERNEL, attrs),
				__builtin_वापस_address(0));
		अगर (!ret)
			जाओ out_मुक्त_pages;
		अगर (क्रमce_dma_unencrypted(dev)) अणु
			err = set_memory_decrypted((अचिन्हित दीर्घ)ret,
						   1 << get_order(size));
			अगर (err)
				जाओ out_मुक्त_pages;
		पूर्ण
		स_रखो(ret, 0, size);
		जाओ करोne;
	पूर्ण

	अगर (PageHighMem(page)) अणु
		/*
		 * Depending on the cma= arguments and per-arch setup
		 * dma_alloc_contiguous could वापस highmem pages.
		 * Without remapping there is no way to वापस them here,
		 * so log an error and fail.
		 */
		dev_info(dev, "Rejecting highmem page from CMA.\n");
		जाओ out_मुक्त_pages;
	पूर्ण

	ret = page_address(page);
	अगर (क्रमce_dma_unencrypted(dev)) अणु
		err = set_memory_decrypted((अचिन्हित दीर्घ)ret,
					   1 << get_order(size));
		अगर (err)
			जाओ out_मुक्त_pages;
	पूर्ण

	स_रखो(ret, 0, size);

	अगर (IS_ENABLED(CONFIG_ARCH_HAS_DMA_SET_UNCACHED) &&
	    !dev_is_dma_coherent(dev)) अणु
		arch_dma_prep_coherent(page, size);
		ret = arch_dma_set_uncached(ret, size);
		अगर (IS_ERR(ret))
			जाओ out_encrypt_pages;
	पूर्ण
करोne:
	*dma_handle = phys_to_dma_direct(dev, page_to_phys(page));
	वापस ret;

out_encrypt_pages:
	अगर (क्रमce_dma_unencrypted(dev)) अणु
		err = set_memory_encrypted((अचिन्हित दीर्घ)page_address(page),
					   1 << get_order(size));
		/* If memory cannot be re-encrypted, it must be leaked */
		अगर (err)
			वापस शून्य;
	पूर्ण
out_मुक्त_pages:
	dma_मुक्त_contiguous(dev, page, size);
	वापस शून्य;
पूर्ण

व्योम dma_direct_मुक्त(काष्ठा device *dev, माप_प्रकार size,
		व्योम *cpu_addr, dma_addr_t dma_addr, अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित पूर्णांक page_order = get_order(size);

	अगर ((attrs & DMA_ATTR_NO_KERNEL_MAPPING) &&
	    !क्रमce_dma_unencrypted(dev)) अणु
		/* cpu_addr is a काष्ठा page cookie, not a kernel address */
		dma_मुक्त_contiguous(dev, cpu_addr, size);
		वापस;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_ARCH_HAS_DMA_SET_UNCACHED) &&
	    !IS_ENABLED(CONFIG_DMA_सूचीECT_REMAP) &&
	    !dev_is_dma_coherent(dev)) अणु
		arch_dma_मुक्त(dev, size, cpu_addr, dma_addr, attrs);
		वापस;
	पूर्ण

	/* If cpu_addr is not from an atomic pool, dma_मुक्त_from_pool() fails */
	अगर (IS_ENABLED(CONFIG_DMA_COHERENT_POOL) &&
	    dma_मुक्त_from_pool(dev, cpu_addr, PAGE_ALIGN(size)))
		वापस;

	अगर (क्रमce_dma_unencrypted(dev))
		set_memory_encrypted((अचिन्हित दीर्घ)cpu_addr, 1 << page_order);

	अगर (IS_ENABLED(CONFIG_DMA_REMAP) && is_vदो_स्मृति_addr(cpu_addr))
		vunmap(cpu_addr);
	अन्यथा अगर (IS_ENABLED(CONFIG_ARCH_HAS_DMA_CLEAR_UNCACHED))
		arch_dma_clear_uncached(cpu_addr, size);

	dma_मुक्त_contiguous(dev, dma_direct_to_page(dev, dma_addr), size);
पूर्ण

काष्ठा page *dma_direct_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp)
अणु
	काष्ठा page *page;
	व्योम *ret;

	अगर (IS_ENABLED(CONFIG_DMA_COHERENT_POOL) &&
	    क्रमce_dma_unencrypted(dev) && !gfpflags_allow_blocking(gfp))
		वापस dma_direct_alloc_from_pool(dev, size, dma_handle, gfp);

	page = __dma_direct_alloc_pages(dev, size, gfp);
	अगर (!page)
		वापस शून्य;
	अगर (PageHighMem(page)) अणु
		/*
		 * Depending on the cma= arguments and per-arch setup
		 * dma_alloc_contiguous could वापस highmem pages.
		 * Without remapping there is no way to वापस them here,
		 * so log an error and fail.
		 */
		dev_info(dev, "Rejecting highmem page from CMA.\n");
		जाओ out_मुक्त_pages;
	पूर्ण

	ret = page_address(page);
	अगर (क्रमce_dma_unencrypted(dev)) अणु
		अगर (set_memory_decrypted((अचिन्हित दीर्घ)ret,
				1 << get_order(size)))
			जाओ out_मुक्त_pages;
	पूर्ण
	स_रखो(ret, 0, size);
	*dma_handle = phys_to_dma_direct(dev, page_to_phys(page));
	वापस page;
out_मुक्त_pages:
	dma_मुक्त_contiguous(dev, page, size);
	वापस शून्य;
पूर्ण

व्योम dma_direct_मुक्त_pages(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा page *page, dma_addr_t dma_addr,
		क्रमागत dma_data_direction dir)
अणु
	अचिन्हित पूर्णांक page_order = get_order(size);
	व्योम *vaddr = page_address(page);

	/* If cpu_addr is not from an atomic pool, dma_मुक्त_from_pool() fails */
	अगर (IS_ENABLED(CONFIG_DMA_COHERENT_POOL) &&
	    dma_मुक्त_from_pool(dev, vaddr, size))
		वापस;

	अगर (क्रमce_dma_unencrypted(dev))
		set_memory_encrypted((अचिन्हित दीर्घ)vaddr, 1 << page_order);

	dma_मुक्त_contiguous(dev, page, size);
पूर्ण

#अगर defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_DEVICE) || \
    defined(CONFIG_SWIOTLB)
व्योम dma_direct_sync_sg_क्रम_device(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		phys_addr_t paddr = dma_to_phys(dev, sg_dma_address(sg));

		अगर (unlikely(is_swiotlb_buffer(paddr)))
			swiotlb_sync_single_क्रम_device(dev, paddr, sg->length,
						       dir);

		अगर (!dev_is_dma_coherent(dev))
			arch_sync_dma_क्रम_device(paddr, sg->length,
					dir);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU) || \
    defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL) || \
    defined(CONFIG_SWIOTLB)
व्योम dma_direct_sync_sg_क्रम_cpu(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		phys_addr_t paddr = dma_to_phys(dev, sg_dma_address(sg));

		अगर (!dev_is_dma_coherent(dev))
			arch_sync_dma_क्रम_cpu(paddr, sg->length, dir);

		अगर (unlikely(is_swiotlb_buffer(paddr)))
			swiotlb_sync_single_क्रम_cpu(dev, paddr, sg->length,
						    dir);

		अगर (dir == DMA_FROM_DEVICE)
			arch_dma_mark_clean(paddr, sg->length);
	पूर्ण

	अगर (!dev_is_dma_coherent(dev))
		arch_sync_dma_क्रम_cpu_all();
पूर्ण

व्योम dma_direct_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i)
		dma_direct_unmap_page(dev, sg->dma_address, sg_dma_len(sg), dir,
			     attrs);
पूर्ण
#पूर्ण_अगर

पूर्णांक dma_direct_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl, पूर्णांक nents,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		sg->dma_address = dma_direct_map_page(dev, sg_page(sg),
				sg->offset, sg->length, dir, attrs);
		अगर (sg->dma_address == DMA_MAPPING_ERROR)
			जाओ out_unmap;
		sg_dma_len(sg) = sg->length;
	पूर्ण

	वापस nents;

out_unmap:
	dma_direct_unmap_sg(dev, sgl, i, dir, attrs | DMA_ATTR_SKIP_CPU_SYNC);
	वापस 0;
पूर्ण

dma_addr_t dma_direct_map_resource(काष्ठा device *dev, phys_addr_t paddr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t dma_addr = paddr;

	अगर (unlikely(!dma_capable(dev, dma_addr, size, false))) अणु
		dev_err_once(dev,
			     "DMA addr %pad+%zu overflow (mask %llx, bus limit %llx).\n",
			     &dma_addr, size, *dev->dma_mask, dev->bus_dma_limit);
		WARN_ON_ONCE(1);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	वापस dma_addr;
पूर्ण

पूर्णांक dma_direct_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page *page = dma_direct_to_page(dev, dma_addr);
	पूर्णांक ret;

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
	अगर (!ret)
		sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	वापस ret;
पूर्ण

bool dma_direct_can_mmap(काष्ठा device *dev)
अणु
	वापस dev_is_dma_coherent(dev) ||
		IS_ENABLED(CONFIG_DMA_NONCOHERENT_MMAP);
पूर्ण

पूर्णांक dma_direct_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ user_count = vma_pages(vma);
	अचिन्हित दीर्घ count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	अचिन्हित दीर्घ pfn = PHYS_PFN(dma_to_phys(dev, dma_addr));
	पूर्णांक ret = -ENXIO;

	vma->vm_page_prot = dma_pgprot(dev, vma->vm_page_prot, attrs);

	अगर (dma_mmap_from_dev_coherent(dev, vma, cpu_addr, size, &ret))
		वापस ret;

	अगर (vma->vm_pgoff >= count || user_count > count - vma->vm_pgoff)
		वापस -ENXIO;
	वापस remap_pfn_range(vma, vma->vm_start, pfn + vma->vm_pgoff,
			user_count << PAGE_SHIFT, vma->vm_page_prot);
पूर्ण

पूर्णांक dma_direct_supported(काष्ठा device *dev, u64 mask)
अणु
	u64 min_mask = (max_pfn - 1) << PAGE_SHIFT;

	/*
	 * Because 32-bit DMA masks are so common we expect every architecture
	 * to be able to satisfy them - either by not supporting more physical
	 * memory, or by providing a ZONE_DMA32.  If neither is the हाल, the
	 * architecture needs to use an IOMMU instead of the direct mapping.
	 */
	अगर (mask >= DMA_BIT_MASK(32))
		वापस 1;

	/*
	 * This check needs to be against the actual bit mask value, so use
	 * phys_to_dma_unencrypted() here so that the SME encryption mask isn't
	 * part of the check.
	 */
	अगर (IS_ENABLED(CONFIG_ZONE_DMA))
		min_mask = min_t(u64, min_mask, DMA_BIT_MASK(zone_dma_bits));
	वापस mask >= phys_to_dma_unencrypted(dev, min_mask);
पूर्ण

माप_प्रकार dma_direct_max_mapping_size(काष्ठा device *dev)
अणु
	/* If SWIOTLB is active, use its maximum mapping size */
	अगर (is_swiotlb_active() &&
	    (dma_addressing_limited(dev) || swiotlb_क्रमce == SWIOTLB_FORCE))
		वापस swiotlb_max_mapping_size(dev);
	वापस SIZE_MAX;
पूर्ण

bool dma_direct_need_sync(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	वापस !dev_is_dma_coherent(dev) ||
		is_swiotlb_buffer(dma_to_phys(dev, dma_addr));
पूर्ण

/**
 * dma_direct_set_offset - Assign scalar offset क्रम a single DMA range.
 * @dev:	device poपूर्णांकer; needed to "own" the alloced memory.
 * @cpu_start:  beginning of memory region covered by this offset.
 * @dma_start:  beginning of DMA/PCI region covered by this offset.
 * @size:	size of the region.
 *
 * This is क्रम the simple हाल of a unअगरorm offset which cannot
 * be discovered by "dma-ranges".
 *
 * It वापसs -ENOMEM अगर out of memory, -EINVAL अगर a map
 * alपढ़ोy exists, 0 otherwise.
 *
 * Note: any call to this from a driver is a bug.  The mapping needs
 * to be described by the device tree or other firmware पूर्णांकerfaces.
 */
पूर्णांक dma_direct_set_offset(काष्ठा device *dev, phys_addr_t cpu_start,
			 dma_addr_t dma_start, u64 size)
अणु
	काष्ठा bus_dma_region *map;
	u64 offset = (u64)cpu_start - (u64)dma_start;

	अगर (dev->dma_range_map) अणु
		dev_err(dev, "attempt to add DMA range to existing map\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!offset)
		वापस 0;

	map = kसुस्मृति(2, माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;
	map[0].cpu_start = cpu_start;
	map[0].dma_start = dma_start;
	map[0].offset = offset;
	map[0].size = size;
	dev->dma_range_map = map;
	वापस 0;
पूर्ण
