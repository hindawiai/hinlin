<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright 2010
 *  by Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
 *
 * This code provides a IOMMU क्रम Xen PV guests with PCI passthrough.
 *
 * PV guests under Xen are running in an non-contiguous memory architecture.
 *
 * When PCI pass-through is utilized, this necessitates an IOMMU क्रम
 * translating bus (DMA) to भव and vice-versa and also providing a
 * mechanism to have contiguous pages क्रम device drivers operations (say DMA
 * operations).
 *
 * Specअगरically, under Xen the Linux idea of pages is an illusion. It
 * assumes that pages start at zero and go up to the available memory. To
 * help with that, the Linux Xen MMU provides a lookup mechanism to
 * translate the page frame numbers (PFN) to machine frame numbers (MFN)
 * and vice-versa. The MFN are the "real" frame numbers. Furthermore
 * memory is not contiguous. Xen hypervisor stitches memory क्रम guests
 * from dअगरferent pools, which means there is no guarantee that PFN==MFN
 * and PFN+1==MFN+1. Lastly with Xen 4.0, pages (in debug mode) are
 * allocated in descending order (high to low), meaning the guest might
 * never get any MFN's under the 4GB mark.
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/memblock.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/export.h>
#समावेश <xen/swiotlb-xen.h>
#समावेश <xen/page.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/hvc-console.h>

#समावेश <यंत्र/dma-mapping.h>
#समावेश <यंत्र/xen/page-coherent.h>

#समावेश <trace/events/swiotlb.h>
#घोषणा MAX_DMA_BITS 32

/*
 * Quick lookup value of the bus address of the IOTLB.
 */

अटल अंतरभूत phys_addr_t xen_phys_to_bus(काष्ठा device *dev, phys_addr_t paddr)
अणु
	अचिन्हित दीर्घ bfn = pfn_to_bfn(XEN_PFN_DOWN(paddr));
	phys_addr_t baddr = (phys_addr_t)bfn << XEN_PAGE_SHIFT;

	baddr |= paddr & ~XEN_PAGE_MASK;
	वापस baddr;
पूर्ण

अटल अंतरभूत dma_addr_t xen_phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	वापस phys_to_dma(dev, xen_phys_to_bus(dev, paddr));
पूर्ण

अटल अंतरभूत phys_addr_t xen_bus_to_phys(काष्ठा device *dev,
					  phys_addr_t baddr)
अणु
	अचिन्हित दीर्घ xen_pfn = bfn_to_pfn(XEN_PFN_DOWN(baddr));
	phys_addr_t paddr = (xen_pfn << XEN_PAGE_SHIFT) |
			    (baddr & ~XEN_PAGE_MASK);

	वापस paddr;
पूर्ण

अटल अंतरभूत phys_addr_t xen_dma_to_phys(काष्ठा device *dev,
					  dma_addr_t dma_addr)
अणु
	वापस xen_bus_to_phys(dev, dma_to_phys(dev, dma_addr));
पूर्ण

अटल अंतरभूत पूर्णांक range_straddles_page_boundary(phys_addr_t p, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ next_bfn, xen_pfn = XEN_PFN_DOWN(p);
	अचिन्हित पूर्णांक i, nr_pages = XEN_PFN_UP(xen_offset_in_page(p) + size);

	next_bfn = pfn_to_bfn(xen_pfn);

	क्रम (i = 1; i < nr_pages; i++)
		अगर (pfn_to_bfn(++xen_pfn) != ++next_bfn)
			वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक is_xen_swiotlb_buffer(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	अचिन्हित दीर्घ bfn = XEN_PFN_DOWN(dma_to_phys(dev, dma_addr));
	अचिन्हित दीर्घ xen_pfn = bfn_to_local_pfn(bfn);
	phys_addr_t paddr = (phys_addr_t)xen_pfn << XEN_PAGE_SHIFT;

	/* If the address is outside our करोमुख्य, it CAN
	 * have the same भव address as another address
	 * in our करोमुख्य. Thereक्रमe _only_ check address within our करोमुख्य.
	 */
	अगर (pfn_valid(PFN_DOWN(paddr)))
		वापस is_swiotlb_buffer(paddr);
	वापस 0;
पूर्ण

अटल पूर्णांक xen_swiotlb_fixup(व्योम *buf, अचिन्हित दीर्घ nsद_असल)
अणु
	पूर्णांक i, rc;
	पूर्णांक dma_bits;
	dma_addr_t dma_handle;
	phys_addr_t p = virt_to_phys(buf);

	dma_bits = get_order(IO_TLB_SEGSIZE << IO_TLB_SHIFT) + PAGE_SHIFT;

	i = 0;
	करो अणु
		पूर्णांक sद_असल = min(nsद_असल - i, (अचिन्हित दीर्घ)IO_TLB_SEGSIZE);

		करो अणु
			rc = xen_create_contiguous_region(
				p + (i << IO_TLB_SHIFT),
				get_order(sद_असल << IO_TLB_SHIFT),
				dma_bits, &dma_handle);
		पूर्ण जबतक (rc && dma_bits++ < MAX_DMA_BITS);
		अगर (rc)
			वापस rc;

		i += sद_असल;
	पूर्ण जबतक (i < nsद_असल);
	वापस 0;
पूर्ण

क्रमागत xen_swiotlb_err अणु
	XEN_SWIOTLB_UNKNOWN = 0,
	XEN_SWIOTLB_ENOMEM,
	XEN_SWIOTLB_EFIXUP
पूर्ण;

अटल स्थिर अक्षर *xen_swiotlb_error(क्रमागत xen_swiotlb_err err)
अणु
	चयन (err) अणु
	हाल XEN_SWIOTLB_ENOMEM:
		वापस "Cannot allocate Xen-SWIOTLB buffer\n";
	हाल XEN_SWIOTLB_EFIXUP:
		वापस "Failed to get contiguous memory for DMA from Xen!\n"\
		    "You either: don't have the permissions, do not have"\
		    " enough free memory under 4GB, or the hypervisor memory"\
		    " is too fragmented!";
	शेष:
		अवरोध;
	पूर्ण
	वापस "";
पूर्ण

#घोषणा DEFAULT_NSLABS		ALIGN(SZ_64M >> IO_TLB_SHIFT, IO_TLB_SEGSIZE)

पूर्णांक __ref xen_swiotlb_init(व्योम)
अणु
	क्रमागत xen_swiotlb_err m_ret = XEN_SWIOTLB_UNKNOWN;
	अचिन्हित दीर्घ bytes = swiotlb_size_or_शेष();
	अचिन्हित दीर्घ nsद_असल = bytes >> IO_TLB_SHIFT;
	अचिन्हित पूर्णांक order, repeat = 3;
	पूर्णांक rc = -ENOMEM;
	अक्षर *start;

	अगर (io_tlb_शेष_mem != शून्य) अणु
		pr_warn("swiotlb buffer already initialized\n");
		वापस -EEXIST;
	पूर्ण

retry:
	m_ret = XEN_SWIOTLB_ENOMEM;
	order = get_order(bytes);

	/*
	 * Get IO TLB memory from any location.
	 */
#घोषणा SLABS_PER_PAGE (1 << (PAGE_SHIFT - IO_TLB_SHIFT))
#घोषणा IO_TLB_MIN_SLABS ((1<<20) >> IO_TLB_SHIFT)
	जबतक ((SLABS_PER_PAGE << order) > IO_TLB_MIN_SLABS) अणु
		start = (व्योम *)xen_get_swiotlb_मुक्त_pages(order);
		अगर (start)
			अवरोध;
		order--;
	पूर्ण
	अगर (!start)
		जाओ error;
	अगर (order != get_order(bytes)) अणु
		pr_warn("Warning: only able to allocate %ld MB for software IO TLB\n",
			(PAGE_SIZE << order) >> 20);
		nsद_असल = SLABS_PER_PAGE << order;
		bytes = nsद_असल << IO_TLB_SHIFT;
	पूर्ण

	/*
	 * And replace that memory with pages under 4GB.
	 */
	rc = xen_swiotlb_fixup(start, nsद_असल);
	अगर (rc) अणु
		मुक्त_pages((अचिन्हित दीर्घ)start, order);
		m_ret = XEN_SWIOTLB_EFIXUP;
		जाओ error;
	पूर्ण
	rc = swiotlb_late_init_with_tbl(start, nsद_असल);
	अगर (rc)
		वापस rc;
	swiotlb_set_max_segment(PAGE_SIZE);
	वापस 0;
error:
	अगर (repeat--) अणु
		/* Min is 2MB */
		nsद_असल = max(1024UL, (nsद_असल >> 1));
		pr_info("Lowering to %luMB\n",
			(nsद_असल << IO_TLB_SHIFT) >> 20);
		जाओ retry;
	पूर्ण
	pr_err("%s (rc:%d)\n", xen_swiotlb_error(m_ret), rc);
	मुक्त_pages((अचिन्हित दीर्घ)start, order);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_X86
व्योम __init xen_swiotlb_init_early(व्योम)
अणु
	अचिन्हित दीर्घ bytes = swiotlb_size_or_शेष();
	अचिन्हित दीर्घ nsद_असल = bytes >> IO_TLB_SHIFT;
	अचिन्हित पूर्णांक repeat = 3;
	अक्षर *start;
	पूर्णांक rc;

retry:
	/*
	 * Get IO TLB memory from any location.
	 */
	start = memblock_alloc(PAGE_ALIGN(bytes), PAGE_SIZE);
	अगर (!start)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_ALIGN(bytes), PAGE_SIZE);

	/*
	 * And replace that memory with pages under 4GB.
	 */
	rc = xen_swiotlb_fixup(start, nsद_असल);
	अगर (rc) अणु
		memblock_मुक्त(__pa(start), PAGE_ALIGN(bytes));
		अगर (repeat--) अणु
			/* Min is 2MB */
			nsद_असल = max(1024UL, (nsद_असल >> 1));
			bytes = nsद_असल << IO_TLB_SHIFT;
			pr_info("Lowering to %luMB\n", bytes >> 20);
			जाओ retry;
		पूर्ण
		panic("%s (rc:%d)", xen_swiotlb_error(XEN_SWIOTLB_EFIXUP), rc);
	पूर्ण

	अगर (swiotlb_init_with_tbl(start, nsद_असल, false))
		panic("Cannot allocate SWIOTLB buffer");
	swiotlb_set_max_segment(PAGE_SIZE);
पूर्ण
#पूर्ण_अगर /* CONFIG_X86 */

अटल व्योम *
xen_swiotlb_alloc_coherent(काष्ठा device *hwdev, माप_प्रकार size,
			   dma_addr_t *dma_handle, gfp_t flags,
			   अचिन्हित दीर्घ attrs)
अणु
	व्योम *ret;
	पूर्णांक order = get_order(size);
	u64 dma_mask = DMA_BIT_MASK(32);
	phys_addr_t phys;
	dma_addr_t dev_addr;

	/*
	* Ignore region specअगरiers - the kernel's ideas of
	* pseuकरो-phys memory layout has nothing to करो with the
	* machine physical layout.  We can't allocate highmem
	* because we can't वापस a poपूर्णांकer to it.
	*/
	flags &= ~(__GFP_DMA | __GFP_HIGHMEM);

	/* Convert the size to actually allocated. */
	size = 1UL << (order + XEN_PAGE_SHIFT);

	/* On ARM this function वापसs an ioremap'ped भव address क्रम
	 * which virt_to_phys करोesn't वापस the corresponding physical
	 * address. In fact on ARM virt_to_phys only works क्रम kernel direct
	 * mapped RAM memory. Also see comment below.
	 */
	ret = xen_alloc_coherent_pages(hwdev, size, dma_handle, flags, attrs);

	अगर (!ret)
		वापस ret;

	अगर (hwdev && hwdev->coherent_dma_mask)
		dma_mask = hwdev->coherent_dma_mask;

	/* At this poपूर्णांक dma_handle is the dma address, next we are
	 * going to set it to the machine address.
	 * Do not use virt_to_phys(ret) because on ARM it करोesn't correspond
	 * to *dma_handle. */
	phys = dma_to_phys(hwdev, *dma_handle);
	dev_addr = xen_phys_to_dma(hwdev, phys);
	अगर (((dev_addr + size - 1 <= dma_mask)) &&
	    !range_straddles_page_boundary(phys, size))
		*dma_handle = dev_addr;
	अन्यथा अणु
		अगर (xen_create_contiguous_region(phys, order,
						 fls64(dma_mask), dma_handle) != 0) अणु
			xen_मुक्त_coherent_pages(hwdev, size, ret, (dma_addr_t)phys, attrs);
			वापस शून्य;
		पूर्ण
		*dma_handle = phys_to_dma(hwdev, *dma_handle);
		SetPageXenRemapped(virt_to_page(ret));
	पूर्ण
	स_रखो(ret, 0, size);
	वापस ret;
पूर्ण

अटल व्योम
xen_swiotlb_मुक्त_coherent(काष्ठा device *hwdev, माप_प्रकार size, व्योम *vaddr,
			  dma_addr_t dev_addr, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक order = get_order(size);
	phys_addr_t phys;
	u64 dma_mask = DMA_BIT_MASK(32);
	काष्ठा page *page;

	अगर (hwdev && hwdev->coherent_dma_mask)
		dma_mask = hwdev->coherent_dma_mask;

	/* करो not use virt_to_phys because on ARM it करोesn't वापस you the
	 * physical address */
	phys = xen_dma_to_phys(hwdev, dev_addr);

	/* Convert the size to actually allocated. */
	size = 1UL << (order + XEN_PAGE_SHIFT);

	अगर (is_vदो_स्मृति_addr(vaddr))
		page = vदो_स्मृति_to_page(vaddr);
	अन्यथा
		page = virt_to_page(vaddr);

	अगर (!WARN_ON((dev_addr + size - 1 > dma_mask) ||
		     range_straddles_page_boundary(phys, size)) &&
	    TestClearPageXenRemapped(page))
		xen_destroy_contiguous_region(phys, order);

	xen_मुक्त_coherent_pages(hwdev, size, vaddr, phys_to_dma(hwdev, phys),
				attrs);
पूर्ण

/*
 * Map a single buffer of the indicated size क्रम DMA in streaming mode.  The
 * physical address to use is वापसed.
 *
 * Once the device is given the dma address, the device owns this memory until
 * either xen_swiotlb_unmap_page or xen_swiotlb_dma_sync_single is perक्रमmed.
 */
अटल dma_addr_t xen_swiotlb_map_page(काष्ठा device *dev, काष्ठा page *page,
				अचिन्हित दीर्घ offset, माप_प्रकार size,
				क्रमागत dma_data_direction dir,
				अचिन्हित दीर्घ attrs)
अणु
	phys_addr_t map, phys = page_to_phys(page) + offset;
	dma_addr_t dev_addr = xen_phys_to_dma(dev, phys);

	BUG_ON(dir == DMA_NONE);
	/*
	 * If the address happens to be in the device's DMA winकरोw,
	 * we can safely वापस the device addr and not worry about bounce
	 * buffering it.
	 */
	अगर (dma_capable(dev, dev_addr, size, true) &&
	    !range_straddles_page_boundary(phys, size) &&
		!xen_arch_need_swiotlb(dev, phys, dev_addr) &&
		swiotlb_क्रमce != SWIOTLB_FORCE)
		जाओ करोne;

	/*
	 * Oh well, have to allocate and map a bounce buffer.
	 */
	trace_swiotlb_bounced(dev, dev_addr, size, swiotlb_क्रमce);

	map = swiotlb_tbl_map_single(dev, phys, size, size, dir, attrs);
	अगर (map == (phys_addr_t)DMA_MAPPING_ERROR)
		वापस DMA_MAPPING_ERROR;

	phys = map;
	dev_addr = xen_phys_to_dma(dev, map);

	/*
	 * Ensure that the address वापसed is DMA'ble
	 */
	अगर (unlikely(!dma_capable(dev, dev_addr, size, true))) अणु
		swiotlb_tbl_unmap_single(dev, map, size, dir,
				attrs | DMA_ATTR_SKIP_CPU_SYNC);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

करोne:
	अगर (!dev_is_dma_coherent(dev) && !(attrs & DMA_ATTR_SKIP_CPU_SYNC)) अणु
		अगर (pfn_valid(PFN_DOWN(dma_to_phys(dev, dev_addr))))
			arch_sync_dma_क्रम_device(phys, size, dir);
		अन्यथा
			xen_dma_sync_क्रम_device(dev, dev_addr, size, dir);
	पूर्ण
	वापस dev_addr;
पूर्ण

/*
 * Unmap a single streaming mode DMA translation.  The dma_addr and size must
 * match what was provided क्रम in a previous xen_swiotlb_map_page call.  All
 * other usages are undefined.
 *
 * After this call, पढ़ोs by the cpu to the buffer are guaranteed to see
 * whatever the device wrote there.
 */
अटल व्योम xen_swiotlb_unmap_page(काष्ठा device *hwdev, dma_addr_t dev_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	phys_addr_t paddr = xen_dma_to_phys(hwdev, dev_addr);

	BUG_ON(dir == DMA_NONE);

	अगर (!dev_is_dma_coherent(hwdev) && !(attrs & DMA_ATTR_SKIP_CPU_SYNC)) अणु
		अगर (pfn_valid(PFN_DOWN(dma_to_phys(hwdev, dev_addr))))
			arch_sync_dma_क्रम_cpu(paddr, size, dir);
		अन्यथा
			xen_dma_sync_क्रम_cpu(hwdev, dev_addr, size, dir);
	पूर्ण

	/* NOTE: We use dev_addr here, not paddr! */
	अगर (is_xen_swiotlb_buffer(hwdev, dev_addr))
		swiotlb_tbl_unmap_single(hwdev, paddr, size, dir, attrs);
पूर्ण

अटल व्योम
xen_swiotlb_sync_single_क्रम_cpu(काष्ठा device *dev, dma_addr_t dma_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t paddr = xen_dma_to_phys(dev, dma_addr);

	अगर (!dev_is_dma_coherent(dev)) अणु
		अगर (pfn_valid(PFN_DOWN(dma_to_phys(dev, dma_addr))))
			arch_sync_dma_क्रम_cpu(paddr, size, dir);
		अन्यथा
			xen_dma_sync_क्रम_cpu(dev, dma_addr, size, dir);
	पूर्ण

	अगर (is_xen_swiotlb_buffer(dev, dma_addr))
		swiotlb_sync_single_क्रम_cpu(dev, paddr, size, dir);
पूर्ण

अटल व्योम
xen_swiotlb_sync_single_क्रम_device(काष्ठा device *dev, dma_addr_t dma_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t paddr = xen_dma_to_phys(dev, dma_addr);

	अगर (is_xen_swiotlb_buffer(dev, dma_addr))
		swiotlb_sync_single_क्रम_device(dev, paddr, size, dir);

	अगर (!dev_is_dma_coherent(dev)) अणु
		अगर (pfn_valid(PFN_DOWN(dma_to_phys(dev, dma_addr))))
			arch_sync_dma_क्रम_device(paddr, size, dir);
		अन्यथा
			xen_dma_sync_क्रम_device(dev, dma_addr, size, dir);
	पूर्ण
पूर्ण

/*
 * Unmap a set of streaming mode DMA translations.  Again, cpu पढ़ो rules
 * concerning calls here are the same as क्रम swiotlb_unmap_page() above.
 */
अटल व्योम
xen_swiotlb_unmap_sg(काष्ठा device *hwdev, काष्ठा scatterlist *sgl, पूर्णांक nelems,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	BUG_ON(dir == DMA_NONE);

	क्रम_each_sg(sgl, sg, nelems, i)
		xen_swiotlb_unmap_page(hwdev, sg->dma_address, sg_dma_len(sg),
				dir, attrs);

पूर्ण

अटल पूर्णांक
xen_swiotlb_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl, पूर्णांक nelems,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	BUG_ON(dir == DMA_NONE);

	क्रम_each_sg(sgl, sg, nelems, i) अणु
		sg->dma_address = xen_swiotlb_map_page(dev, sg_page(sg),
				sg->offset, sg->length, dir, attrs);
		अगर (sg->dma_address == DMA_MAPPING_ERROR)
			जाओ out_unmap;
		sg_dma_len(sg) = sg->length;
	पूर्ण

	वापस nelems;
out_unmap:
	xen_swiotlb_unmap_sg(dev, sgl, i, dir, attrs | DMA_ATTR_SKIP_CPU_SYNC);
	sg_dma_len(sgl) = 0;
	वापस 0;
पूर्ण

अटल व्योम
xen_swiotlb_sync_sg_क्रम_cpu(काष्ठा device *dev, काष्ठा scatterlist *sgl,
			    पूर्णांक nelems, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nelems, i) अणु
		xen_swiotlb_sync_single_क्रम_cpu(dev, sg->dma_address,
				sg->length, dir);
	पूर्ण
पूर्ण

अटल व्योम
xen_swiotlb_sync_sg_क्रम_device(काष्ठा device *dev, काष्ठा scatterlist *sgl,
			       पूर्णांक nelems, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nelems, i) अणु
		xen_swiotlb_sync_single_क्रम_device(dev, sg->dma_address,
				sg->length, dir);
	पूर्ण
पूर्ण

/*
 * Return whether the given device DMA address mask can be supported
 * properly.  For example, अगर your device can only drive the low 24-bits
 * during bus mastering, then you would pass 0x00ffffff as the mask to
 * this function.
 */
अटल पूर्णांक
xen_swiotlb_dma_supported(काष्ठा device *hwdev, u64 mask)
अणु
	वापस xen_phys_to_dma(hwdev, io_tlb_शेष_mem->end - 1) <= mask;
पूर्ण

स्थिर काष्ठा dma_map_ops xen_swiotlb_dma_ops = अणु
	.alloc = xen_swiotlb_alloc_coherent,
	.मुक्त = xen_swiotlb_मुक्त_coherent,
	.sync_single_क्रम_cpu = xen_swiotlb_sync_single_क्रम_cpu,
	.sync_single_क्रम_device = xen_swiotlb_sync_single_क्रम_device,
	.sync_sg_क्रम_cpu = xen_swiotlb_sync_sg_क्रम_cpu,
	.sync_sg_क्रम_device = xen_swiotlb_sync_sg_क्रम_device,
	.map_sg = xen_swiotlb_map_sg,
	.unmap_sg = xen_swiotlb_unmap_sg,
	.map_page = xen_swiotlb_map_page,
	.unmap_page = xen_swiotlb_unmap_page,
	.dma_supported = xen_swiotlb_dma_supported,
	.mmap = dma_common_mmap,
	.get_sgtable = dma_common_get_sgtable,
	.alloc_pages = dma_common_alloc_pages,
	.मुक्त_pages = dma_common_मुक्त_pages,
पूर्ण;
