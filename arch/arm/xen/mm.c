<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/cpu.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/swiotlb.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/page.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/swiotlb-xen.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/पूर्णांकerface.h>

अचिन्हित दीर्घ xen_get_swiotlb_मुक्त_pages(अचिन्हित पूर्णांक order)
अणु
	phys_addr_t base;
	gfp_t flags = __GFP_NOWARN|__GFP_KSWAPD_RECLAIM;
	u64 i;

	क्रम_each_mem_range(i, &base, शून्य) अणु
		अगर (base < (phys_addr_t)0xffffffff) अणु
			अगर (IS_ENABLED(CONFIG_ZONE_DMA32))
				flags |= __GFP_DMA32;
			अन्यथा
				flags |= __GFP_DMA;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस __get_मुक्त_pages(flags, order);
पूर्ण

अटल bool hypercall_cflush = false;

/* buffers in highmem or क्रमeign pages cannot cross page boundaries */
अटल व्योम dma_cache_मुख्यt(काष्ठा device *dev, dma_addr_t handle,
			    माप_प्रकार size, u32 op)
अणु
	काष्ठा gnttab_cache_flush cflush;

	cflush.offset = xen_offset_in_page(handle);
	cflush.op = op;
	handle &= XEN_PAGE_MASK;

	करो अणु
		cflush.a.dev_bus_addr = dma_to_phys(dev, handle);

		अगर (size + cflush.offset > XEN_PAGE_SIZE)
			cflush.length = XEN_PAGE_SIZE - cflush.offset;
		अन्यथा
			cflush.length = size;

		HYPERVISOR_grant_table_op(GNTTABOP_cache_flush, &cflush, 1);

		cflush.offset = 0;
		handle += cflush.length;
		size -= cflush.length;
	पूर्ण जबतक (size);
पूर्ण

/*
 * Dom0 is mapped 1:1, and जबतक the Linux page can span across multiple Xen
 * pages, it is not possible क्रम it to contain a mix of local and क्रमeign Xen
 * pages.  Calling pfn_valid on a क्रमeign mfn will always वापस false, so अगर
 * pfn_valid वापसs true the pages is local and we can use the native
 * dma-direct functions, otherwise we call the Xen specअगरic version.
 */
व्योम xen_dma_sync_क्रम_cpu(काष्ठा device *dev, dma_addr_t handle,
			  माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अगर (dir != DMA_TO_DEVICE)
		dma_cache_मुख्यt(dev, handle, size, GNTTAB_CACHE_INVAL);
पूर्ण

व्योम xen_dma_sync_क्रम_device(काष्ठा device *dev, dma_addr_t handle,
			     माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अगर (dir == DMA_FROM_DEVICE)
		dma_cache_मुख्यt(dev, handle, size, GNTTAB_CACHE_INVAL);
	अन्यथा
		dma_cache_मुख्यt(dev, handle, size, GNTTAB_CACHE_CLEAN);
पूर्ण

bool xen_arch_need_swiotlb(काष्ठा device *dev,
			   phys_addr_t phys,
			   dma_addr_t dev_addr)
अणु
	अचिन्हित पूर्णांक xen_pfn = XEN_PFN_DOWN(phys);
	अचिन्हित पूर्णांक bfn = XEN_PFN_DOWN(dma_to_phys(dev, dev_addr));

	/*
	 * The swiotlb buffer should be used अगर
	 *	- Xen करोesn't have the cache flush hypercall
	 *	- The Linux page refers to क्रमeign memory
	 *	- The device करोesn't support coherent DMA request
	 *
	 * The Linux page may be spanned acrros multiple Xen page, although
	 * it's not possible to have a mix of local and क्रमeign Xen page.
	 * Furthermore, range_straddles_page_boundary is alपढ़ोy checking
	 * अगर buffer is physically contiguous in the host RAM.
	 *
	 * Thereक्रमe we only need to check the first Xen page to know अगर we
	 * require a bounce buffer because the device करोesn't support coherent
	 * memory and we are not able to flush the cache.
	 */
	वापस (!hypercall_cflush && (xen_pfn != bfn) &&
		!dev_is_dma_coherent(dev));
पूर्ण

पूर्णांक xen_create_contiguous_region(phys_addr_t pstart, अचिन्हित पूर्णांक order,
				 अचिन्हित पूर्णांक address_bits,
				 dma_addr_t *dma_handle)
अणु
	अगर (!xen_initial_करोमुख्य())
		वापस -EINVAL;

	/* we assume that करोm0 is mapped 1:1 क्रम now */
	*dma_handle = pstart;
	वापस 0;
पूर्ण

व्योम xen_destroy_contiguous_region(phys_addr_t pstart, अचिन्हित पूर्णांक order)
अणु
	वापस;
पूर्ण

अटल पूर्णांक __init xen_mm_init(व्योम)
अणु
	काष्ठा gnttab_cache_flush cflush;
	पूर्णांक rc;

	अगर (!xen_swiotlb_detect())
		वापस 0;

	rc = xen_swiotlb_init();
	/* we can work with the शेष swiotlb */
	अगर (rc < 0 && rc != -EEXIST)
		वापस rc;

	cflush.op = 0;
	cflush.a.dev_bus_addr = 0;
	cflush.offset = 0;
	cflush.length = 0;
	अगर (HYPERVISOR_grant_table_op(GNTTABOP_cache_flush, &cflush, 1) != -ENOSYS)
		hypercall_cflush = true;
	वापस 0;
पूर्ण
arch_initcall(xen_mm_init);
