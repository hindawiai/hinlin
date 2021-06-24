<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A fairly generic DMA-API to IOMMU-API glue layer.
 *
 * Copyright (C) 2014-2015 ARM Ltd.
 *
 * based in part on arch/arm/mm/dma-mapping.c:
 * Copyright (C) 2000-2004 Russell King
 */

#समावेश <linux/acpi_iort.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/gfp.h>
#समावेश <linux/huge_mm.h>
#समावेश <linux/iommu.h>
#समावेश <linux/iova.h>
#समावेश <linux/irq.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/dma-direct.h>

काष्ठा iommu_dma_msi_page अणु
	काष्ठा list_head	list;
	dma_addr_t		iova;
	phys_addr_t		phys;
पूर्ण;

क्रमागत iommu_dma_cookie_type अणु
	IOMMU_DMA_IOVA_COOKIE,
	IOMMU_DMA_MSI_COOKIE,
पूर्ण;

काष्ठा iommu_dma_cookie अणु
	क्रमागत iommu_dma_cookie_type	type;
	जोड़ अणु
		/* Full allocator क्रम IOMMU_DMA_IOVA_COOKIE */
		काष्ठा iova_करोमुख्य	iovad;
		/* Trivial linear page allocator क्रम IOMMU_DMA_MSI_COOKIE */
		dma_addr_t		msi_iova;
	पूर्ण;
	काष्ठा list_head		msi_page_list;

	/* Doमुख्य क्रम flush queue callback; शून्य अगर flush queue not in use */
	काष्ठा iommu_करोमुख्य		*fq_करोमुख्य;
पूर्ण;

अटल DEFINE_STATIC_KEY_FALSE(iommu_deferred_attach_enabled);
bool iommu_dma_क्रमcedac __पढ़ो_mostly;

अटल पूर्णांक __init iommu_dma_क्रमcedac_setup(अक्षर *str)
अणु
	पूर्णांक ret = kstrtobool(str, &iommu_dma_क्रमcedac);

	अगर (!ret && iommu_dma_क्रमcedac)
		pr_info("Forcing DAC for PCI devices\n");
	वापस ret;
पूर्ण
early_param("iommu.forcedac", iommu_dma_क्रमcedac_setup);

अटल व्योम iommu_dma_entry_dtor(अचिन्हित दीर्घ data)
अणु
	काष्ठा page *मुक्तlist = (काष्ठा page *)data;

	जबतक (मुक्तlist) अणु
		अचिन्हित दीर्घ p = (अचिन्हित दीर्घ)page_address(मुक्तlist);

		मुक्तlist = मुक्तlist->मुक्तlist;
		मुक्त_page(p);
	पूर्ण
पूर्ण

अटल अंतरभूत माप_प्रकार cookie_msi_granule(काष्ठा iommu_dma_cookie *cookie)
अणु
	अगर (cookie->type == IOMMU_DMA_IOVA_COOKIE)
		वापस cookie->iovad.granule;
	वापस PAGE_SIZE;
पूर्ण

अटल काष्ठा iommu_dma_cookie *cookie_alloc(क्रमागत iommu_dma_cookie_type type)
अणु
	काष्ठा iommu_dma_cookie *cookie;

	cookie = kzalloc(माप(*cookie), GFP_KERNEL);
	अगर (cookie) अणु
		INIT_LIST_HEAD(&cookie->msi_page_list);
		cookie->type = type;
	पूर्ण
	वापस cookie;
पूर्ण

/**
 * iommu_get_dma_cookie - Acquire DMA-API resources क्रम a करोमुख्य
 * @करोमुख्य: IOMMU करोमुख्य to prepare क्रम DMA-API usage
 *
 * IOMMU drivers should normally call this from their करोमुख्य_alloc
 * callback when करोमुख्य->type == IOMMU_DOMAIN_DMA.
 */
पूर्णांक iommu_get_dma_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	अगर (करोमुख्य->iova_cookie)
		वापस -EEXIST;

	करोमुख्य->iova_cookie = cookie_alloc(IOMMU_DMA_IOVA_COOKIE);
	अगर (!करोमुख्य->iova_cookie)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iommu_get_dma_cookie);

/**
 * iommu_get_msi_cookie - Acquire just MSI remapping resources
 * @करोमुख्य: IOMMU करोमुख्य to prepare
 * @base: Start address of IOVA region क्रम MSI mappings
 *
 * Users who manage their own IOVA allocation and करो not want DMA API support,
 * but would still like to take advantage of स्वतःmatic MSI remapping, can use
 * this to initialise their own करोमुख्य appropriately. Users should reserve a
 * contiguous IOVA region, starting at @base, large enough to accommodate the
 * number of PAGE_SIZE mappings necessary to cover every MSI करोorbell address
 * used by the devices attached to @करोमुख्य.
 */
पूर्णांक iommu_get_msi_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t base)
अणु
	काष्ठा iommu_dma_cookie *cookie;

	अगर (करोमुख्य->type != IOMMU_DOMAIN_UNMANAGED)
		वापस -EINVAL;

	अगर (करोमुख्य->iova_cookie)
		वापस -EEXIST;

	cookie = cookie_alloc(IOMMU_DMA_MSI_COOKIE);
	अगर (!cookie)
		वापस -ENOMEM;

	cookie->msi_iova = base;
	करोमुख्य->iova_cookie = cookie;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(iommu_get_msi_cookie);

/**
 * iommu_put_dma_cookie - Release a करोमुख्य's DMA mapping resources
 * @करोमुख्य: IOMMU करोमुख्य previously prepared by iommu_get_dma_cookie() or
 *          iommu_get_msi_cookie()
 *
 * IOMMU drivers should normally call this from their करोमुख्य_मुक्त callback.
 */
व्योम iommu_put_dma_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iommu_dma_msi_page *msi, *पंचांगp;

	अगर (!cookie)
		वापस;

	अगर (cookie->type == IOMMU_DMA_IOVA_COOKIE && cookie->iovad.granule)
		put_iova_करोमुख्य(&cookie->iovad);

	list_क्रम_each_entry_safe(msi, पंचांगp, &cookie->msi_page_list, list) अणु
		list_del(&msi->list);
		kमुक्त(msi);
	पूर्ण
	kमुक्त(cookie);
	करोमुख्य->iova_cookie = शून्य;
पूर्ण
EXPORT_SYMBOL(iommu_put_dma_cookie);

/**
 * iommu_dma_get_resv_regions - Reserved region driver helper
 * @dev: Device from iommu_get_resv_regions()
 * @list: Reserved region list from iommu_get_resv_regions()
 *
 * IOMMU drivers can use this to implement their .get_resv_regions callback
 * क्रम general non-IOMMU-specअगरic reservations. Currently, this covers GICv3
 * ITS region reservation on ACPI based ARM platक्रमms that may require HW MSI
 * reservation.
 */
व्योम iommu_dma_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *list)
अणु

	अगर (!is_of_node(dev_iommu_fwspec_get(dev)->iommu_fwnode))
		iort_iommu_msi_get_resv_regions(dev, list);

पूर्ण
EXPORT_SYMBOL(iommu_dma_get_resv_regions);

अटल पूर्णांक cookie_init_hw_msi_region(काष्ठा iommu_dma_cookie *cookie,
		phys_addr_t start, phys_addr_t end)
अणु
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	काष्ठा iommu_dma_msi_page *msi_page;
	पूर्णांक i, num_pages;

	start -= iova_offset(iovad, start);
	num_pages = iova_align(iovad, end - start) >> iova_shअगरt(iovad);

	क्रम (i = 0; i < num_pages; i++) अणु
		msi_page = kदो_स्मृति(माप(*msi_page), GFP_KERNEL);
		अगर (!msi_page)
			वापस -ENOMEM;

		msi_page->phys = start;
		msi_page->iova = start;
		INIT_LIST_HEAD(&msi_page->list);
		list_add(&msi_page->list, &cookie->msi_page_list);
		start += iovad->granule;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iova_reserve_pci_winकरोws(काष्ठा pci_dev *dev,
		काष्ठा iova_करोमुख्य *iovad)
अणु
	काष्ठा pci_host_bridge *bridge = pci_find_host_bridge(dev->bus);
	काष्ठा resource_entry *winकरोw;
	अचिन्हित दीर्घ lo, hi;
	phys_addr_t start = 0, end;

	resource_list_क्रम_each_entry(winकरोw, &bridge->winकरोws) अणु
		अगर (resource_type(winकरोw->res) != IORESOURCE_MEM)
			जारी;

		lo = iova_pfn(iovad, winकरोw->res->start - winकरोw->offset);
		hi = iova_pfn(iovad, winकरोw->res->end - winकरोw->offset);
		reserve_iova(iovad, lo, hi);
	पूर्ण

	/* Get reserved DMA winकरोws from host bridge */
	resource_list_क्रम_each_entry(winकरोw, &bridge->dma_ranges) अणु
		end = winकरोw->res->start - winकरोw->offset;
resv_iova:
		अगर (end > start) अणु
			lo = iova_pfn(iovad, start);
			hi = iova_pfn(iovad, end);
			reserve_iova(iovad, lo, hi);
		पूर्ण अन्यथा अणु
			/* dma_ranges list should be sorted */
			dev_err(&dev->dev, "Failed to reserve IOVA\n");
			वापस -EINVAL;
		पूर्ण

		start = winकरोw->res->end - winकरोw->offset + 1;
		/* If winकरोw is last entry */
		अगर (winकरोw->node.next == &bridge->dma_ranges &&
		    end != ~(phys_addr_t)0) अणु
			end = ~(phys_addr_t)0;
			जाओ resv_iova;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iova_reserve_iommu_regions(काष्ठा device *dev,
		काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	काष्ठा iommu_resv_region *region;
	LIST_HEAD(resv_regions);
	पूर्णांक ret = 0;

	अगर (dev_is_pci(dev)) अणु
		ret = iova_reserve_pci_winकरोws(to_pci_dev(dev), iovad);
		अगर (ret)
			वापस ret;
	पूर्ण

	iommu_get_resv_regions(dev, &resv_regions);
	list_क्रम_each_entry(region, &resv_regions, list) अणु
		अचिन्हित दीर्घ lo, hi;

		/* We ARE the software that manages these! */
		अगर (region->type == IOMMU_RESV_SW_MSI)
			जारी;

		lo = iova_pfn(iovad, region->start);
		hi = iova_pfn(iovad, region->start + region->length - 1);
		reserve_iova(iovad, lo, hi);

		अगर (region->type == IOMMU_RESV_MSI)
			ret = cookie_init_hw_msi_region(cookie, region->start,
					region->start + region->length);
		अगर (ret)
			अवरोध;
	पूर्ण
	iommu_put_resv_regions(dev, &resv_regions);

	वापस ret;
पूर्ण

अटल व्योम iommu_dma_flush_iotlb_all(काष्ठा iova_करोमुख्य *iovad)
अणु
	काष्ठा iommu_dma_cookie *cookie;
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	cookie = container_of(iovad, काष्ठा iommu_dma_cookie, iovad);
	करोमुख्य = cookie->fq_करोमुख्य;

	करोमुख्य->ops->flush_iotlb_all(करोमुख्य);
पूर्ण

अटल bool dev_is_untrusted(काष्ठा device *dev)
अणु
	वापस dev_is_pci(dev) && to_pci_dev(dev)->untrusted;
पूर्ण

/**
 * iommu_dma_init_करोमुख्य - Initialise a DMA mapping करोमुख्य
 * @करोमुख्य: IOMMU करोमुख्य previously prepared by iommu_get_dma_cookie()
 * @base: IOVA at which the mappable address space starts
 * @size: Size of IOVA space
 * @dev: Device the करोमुख्य is being initialised क्रम
 *
 * @base and @size should be exact multiples of IOMMU page granularity to
 * aव्योम rounding surprises. If necessary, we reserve the page at address 0
 * to ensure it is an invalid IOVA. It is safe to reinitialise a करोमुख्य, but
 * any change which could make prior IOVAs invalid will fail.
 */
अटल पूर्णांक iommu_dma_init_करोमुख्य(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t base,
		u64 size, काष्ठा device *dev)
अणु
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	अचिन्हित दीर्घ order, base_pfn;
	काष्ठा iova_करोमुख्य *iovad;

	अगर (!cookie || cookie->type != IOMMU_DMA_IOVA_COOKIE)
		वापस -EINVAL;

	iovad = &cookie->iovad;

	/* Use the smallest supported page size क्रम IOVA granularity */
	order = __ffs(करोमुख्य->pgsize_biपंचांगap);
	base_pfn = max_t(अचिन्हित दीर्घ, 1, base >> order);

	/* Check the करोमुख्य allows at least some access to the device... */
	अगर (करोमुख्य->geometry.क्रमce_aperture) अणु
		अगर (base > करोमुख्य->geometry.aperture_end ||
		    base + size <= करोमुख्य->geometry.aperture_start) अणु
			pr_warn("specified DMA range outside IOMMU capability\n");
			वापस -EFAULT;
		पूर्ण
		/* ...then finally give it a kicking to make sure it fits */
		base_pfn = max_t(अचिन्हित दीर्घ, base_pfn,
				करोमुख्य->geometry.aperture_start >> order);
	पूर्ण

	/* start_pfn is always nonzero क्रम an alपढ़ोy-initialised करोमुख्य */
	अगर (iovad->start_pfn) अणु
		अगर (1UL << order != iovad->granule ||
		    base_pfn != iovad->start_pfn) अणु
			pr_warn("Incompatible range for DMA domain\n");
			वापस -EFAULT;
		पूर्ण

		वापस 0;
	पूर्ण

	init_iova_करोमुख्य(iovad, 1UL << order, base_pfn);

	अगर (!cookie->fq_करोमुख्य && (!dev || !dev_is_untrusted(dev)) &&
	    करोमुख्य->ops->flush_iotlb_all && !iommu_get_dma_strict(करोमुख्य)) अणु
		अगर (init_iova_flush_queue(iovad, iommu_dma_flush_iotlb_all,
					  iommu_dma_entry_dtor))
			pr_warn("iova flush queue initialization failed\n");
		अन्यथा
			cookie->fq_करोमुख्य = करोमुख्य;
	पूर्ण

	अगर (!dev)
		वापस 0;

	वापस iova_reserve_iommu_regions(dev, करोमुख्य);
पूर्ण

/**
 * dma_info_to_prot - Translate DMA API directions and attributes to IOMMU API
 *                    page flags.
 * @dir: Direction of DMA transfer
 * @coherent: Is the DMA master cache-coherent?
 * @attrs: DMA attributes क्रम the mapping
 *
 * Return: corresponding IOMMU API page protection flags
 */
अटल पूर्णांक dma_info_to_prot(क्रमागत dma_data_direction dir, bool coherent,
		     अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक prot = coherent ? IOMMU_CACHE : 0;

	अगर (attrs & DMA_ATTR_PRIVILEGED)
		prot |= IOMMU_PRIV;

	चयन (dir) अणु
	हाल DMA_BIसूचीECTIONAL:
		वापस prot | IOMMU_READ | IOMMU_WRITE;
	हाल DMA_TO_DEVICE:
		वापस prot | IOMMU_READ;
	हाल DMA_FROM_DEVICE:
		वापस prot | IOMMU_WRITE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल dma_addr_t iommu_dma_alloc_iova(काष्ठा iommu_करोमुख्य *करोमुख्य,
		माप_प्रकार size, u64 dma_limit, काष्ठा device *dev)
अणु
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	अचिन्हित दीर्घ shअगरt, iova_len, iova = 0;

	अगर (cookie->type == IOMMU_DMA_MSI_COOKIE) अणु
		cookie->msi_iova += size;
		वापस cookie->msi_iova - size;
	पूर्ण

	shअगरt = iova_shअगरt(iovad);
	iova_len = size >> shअगरt;
	/*
	 * Freeing non-घातer-of-two-sized allocations back पूर्णांकo the IOVA caches
	 * will come back to bite us badly, so we have to waste a bit of space
	 * rounding up anything cacheable to make sure that can't happen. The
	 * order of the unadjusted size will still match upon मुक्तing.
	 */
	अगर (iova_len < (1 << (IOVA_RANGE_CACHE_MAX_SIZE - 1)))
		iova_len = roundup_घात_of_two(iova_len);

	dma_limit = min_not_zero(dma_limit, dev->bus_dma_limit);

	अगर (करोमुख्य->geometry.क्रमce_aperture)
		dma_limit = min(dma_limit, (u64)करोमुख्य->geometry.aperture_end);

	/* Try to get PCI devices a SAC address */
	अगर (dma_limit > DMA_BIT_MASK(32) && !iommu_dma_क्रमcedac && dev_is_pci(dev))
		iova = alloc_iova_fast(iovad, iova_len,
				       DMA_BIT_MASK(32) >> shअगरt, false);

	अगर (!iova)
		iova = alloc_iova_fast(iovad, iova_len, dma_limit >> shअगरt,
				       true);

	वापस (dma_addr_t)iova << shअगरt;
पूर्ण

अटल व्योम iommu_dma_मुक्त_iova(काष्ठा iommu_dma_cookie *cookie,
		dma_addr_t iova, माप_प्रकार size, काष्ठा page *मुक्तlist)
अणु
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;

	/* The MSI हाल is only ever cleaning up its most recent allocation */
	अगर (cookie->type == IOMMU_DMA_MSI_COOKIE)
		cookie->msi_iova -= size;
	अन्यथा अगर (cookie->fq_करोमुख्य)	/* non-strict mode */
		queue_iova(iovad, iova_pfn(iovad, iova),
				size >> iova_shअगरt(iovad),
				(अचिन्हित दीर्घ)मुक्तlist);
	अन्यथा
		मुक्त_iova_fast(iovad, iova_pfn(iovad, iova),
				size >> iova_shअगरt(iovad));
पूर्ण

अटल व्योम __iommu_dma_unmap(काष्ठा device *dev, dma_addr_t dma_addr,
		माप_प्रकार size)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_dma_करोमुख्य(dev);
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	माप_प्रकार iova_off = iova_offset(iovad, dma_addr);
	काष्ठा iommu_iotlb_gather iotlb_gather;
	माप_प्रकार unmapped;

	dma_addr -= iova_off;
	size = iova_align(iovad, size + iova_off);
	iommu_iotlb_gather_init(&iotlb_gather);

	unmapped = iommu_unmap_fast(करोमुख्य, dma_addr, size, &iotlb_gather);
	WARN_ON(unmapped != size);

	अगर (!cookie->fq_करोमुख्य)
		iommu_iotlb_sync(करोमुख्य, &iotlb_gather);
	iommu_dma_मुक्त_iova(cookie, dma_addr, size, iotlb_gather.मुक्तlist);
पूर्ण

अटल व्योम __iommu_dma_unmap_swiotlb(काष्ठा device *dev, dma_addr_t dma_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_dma_करोमुख्य(dev);
	phys_addr_t phys;

	phys = iommu_iova_to_phys(करोमुख्य, dma_addr);
	अगर (WARN_ON(!phys))
		वापस;

	__iommu_dma_unmap(dev, dma_addr, size);

	अगर (unlikely(is_swiotlb_buffer(phys)))
		swiotlb_tbl_unmap_single(dev, phys, size, dir, attrs);
पूर्ण

अटल dma_addr_t __iommu_dma_map(काष्ठा device *dev, phys_addr_t phys,
		माप_प्रकार size, पूर्णांक prot, u64 dma_mask)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_dma_करोमुख्य(dev);
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	माप_प्रकार iova_off = iova_offset(iovad, phys);
	dma_addr_t iova;

	अगर (अटल_branch_unlikely(&iommu_deferred_attach_enabled) &&
	    iommu_deferred_attach(dev, करोमुख्य))
		वापस DMA_MAPPING_ERROR;

	size = iova_align(iovad, size + iova_off);

	iova = iommu_dma_alloc_iova(करोमुख्य, size, dma_mask, dev);
	अगर (!iova)
		वापस DMA_MAPPING_ERROR;

	अगर (iommu_map_atomic(करोमुख्य, iova, phys - iova_off, size, prot)) अणु
		iommu_dma_मुक्त_iova(cookie, iova, size, शून्य);
		वापस DMA_MAPPING_ERROR;
	पूर्ण
	वापस iova + iova_off;
पूर्ण

अटल dma_addr_t __iommu_dma_map_swiotlb(काष्ठा device *dev, phys_addr_t phys,
		माप_प्रकार org_size, dma_addr_t dma_mask, bool coherent,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक prot = dma_info_to_prot(dir, coherent, attrs);
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_dma_करोमुख्य(dev);
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	माप_प्रकार aligned_size = org_size;
	व्योम *padding_start;
	माप_प्रकार padding_size;
	dma_addr_t iova;

	/*
	 * If both the physical buffer start address and size are
	 * page aligned, we करोn't need to use a bounce page.
	 */
	अगर (IS_ENABLED(CONFIG_SWIOTLB) && dev_is_untrusted(dev) &&
	    iova_offset(iovad, phys | org_size)) अणु
		aligned_size = iova_align(iovad, org_size);
		phys = swiotlb_tbl_map_single(dev, phys, org_size,
					      aligned_size, dir, attrs);

		अगर (phys == DMA_MAPPING_ERROR)
			वापस DMA_MAPPING_ERROR;

		/* Cleanup the padding area. */
		padding_start = phys_to_virt(phys);
		padding_size = aligned_size;

		अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC) &&
		    (dir == DMA_TO_DEVICE ||
		     dir == DMA_BIसूचीECTIONAL)) अणु
			padding_start += org_size;
			padding_size -= org_size;
		पूर्ण

		स_रखो(padding_start, 0, padding_size);
	पूर्ण

	iova = __iommu_dma_map(dev, phys, aligned_size, prot, dma_mask);
	अगर (iova == DMA_MAPPING_ERROR && is_swiotlb_buffer(phys))
		swiotlb_tbl_unmap_single(dev, phys, org_size, dir, attrs);
	वापस iova;
पूर्ण

अटल व्योम __iommu_dma_मुक्त_pages(काष्ठा page **pages, पूर्णांक count)
अणु
	जबतक (count--)
		__मुक्त_page(pages[count]);
	kvमुक्त(pages);
पूर्ण

अटल काष्ठा page **__iommu_dma_alloc_pages(काष्ठा device *dev,
		अचिन्हित पूर्णांक count, अचिन्हित दीर्घ order_mask, gfp_t gfp)
अणु
	काष्ठा page **pages;
	अचिन्हित पूर्णांक i = 0, nid = dev_to_node(dev);

	order_mask &= (2U << MAX_ORDER) - 1;
	अगर (!order_mask)
		वापस शून्य;

	pages = kvzalloc(count * माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस शून्य;

	/* IOMMU can map any pages, so himem can also be used here */
	gfp |= __GFP_NOWARN | __GFP_HIGHMEM;

	/* It makes no sense to muck about with huge pages */
	gfp &= ~__GFP_COMP;

	जबतक (count) अणु
		काष्ठा page *page = शून्य;
		अचिन्हित पूर्णांक order_size;

		/*
		 * Higher-order allocations are a convenience rather
		 * than a necessity, hence using __GFP_NORETRY until
		 * falling back to minimum-order allocations.
		 */
		क्रम (order_mask &= (2U << __fls(count)) - 1;
		     order_mask; order_mask &= ~order_size) अणु
			अचिन्हित पूर्णांक order = __fls(order_mask);
			gfp_t alloc_flags = gfp;

			order_size = 1U << order;
			अगर (order_mask > order_size)
				alloc_flags |= __GFP_NORETRY;
			page = alloc_pages_node(nid, alloc_flags, order);
			अगर (!page)
				जारी;
			अगर (order)
				split_page(page, order);
			अवरोध;
		पूर्ण
		अगर (!page) अणु
			__iommu_dma_मुक्त_pages(pages, i);
			वापस शून्य;
		पूर्ण
		count -= order_size;
		जबतक (order_size--)
			pages[i++] = page++;
	पूर्ण
	वापस pages;
पूर्ण

/*
 * If size is less than PAGE_SIZE, then a full CPU page will be allocated,
 * but an IOMMU which supports smaller pages might not map the whole thing.
 */
अटल काष्ठा page **__iommu_dma_alloc_noncontiguous(काष्ठा device *dev,
		माप_प्रकार size, काष्ठा sg_table *sgt, gfp_t gfp, pgprot_t prot,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_dma_करोमुख्य(dev);
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	bool coherent = dev_is_dma_coherent(dev);
	पूर्णांक ioprot = dma_info_to_prot(DMA_BIसूचीECTIONAL, coherent, attrs);
	अचिन्हित पूर्णांक count, min_size, alloc_sizes = करोमुख्य->pgsize_biपंचांगap;
	काष्ठा page **pages;
	dma_addr_t iova;

	अगर (अटल_branch_unlikely(&iommu_deferred_attach_enabled) &&
	    iommu_deferred_attach(dev, करोमुख्य))
		वापस शून्य;

	min_size = alloc_sizes & -alloc_sizes;
	अगर (min_size < PAGE_SIZE) अणु
		min_size = PAGE_SIZE;
		alloc_sizes |= PAGE_SIZE;
	पूर्ण अन्यथा अणु
		size = ALIGN(size, min_size);
	पूर्ण
	अगर (attrs & DMA_ATTR_ALLOC_SINGLE_PAGES)
		alloc_sizes = min_size;

	count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	pages = __iommu_dma_alloc_pages(dev, count, alloc_sizes >> PAGE_SHIFT,
					gfp);
	अगर (!pages)
		वापस शून्य;

	size = iova_align(iovad, size);
	iova = iommu_dma_alloc_iova(करोमुख्य, size, dev->coherent_dma_mask, dev);
	अगर (!iova)
		जाओ out_मुक्त_pages;

	अगर (sg_alloc_table_from_pages(sgt, pages, count, 0, size, GFP_KERNEL))
		जाओ out_मुक्त_iova;

	अगर (!(ioprot & IOMMU_CACHE)) अणु
		काष्ठा scatterlist *sg;
		पूर्णांक i;

		क्रम_each_sg(sgt->sgl, sg, sgt->orig_nents, i)
			arch_dma_prep_coherent(sg_page(sg), sg->length);
	पूर्ण

	अगर (iommu_map_sg_atomic(करोमुख्य, iova, sgt->sgl, sgt->orig_nents, ioprot)
			< size)
		जाओ out_मुक्त_sg;

	sgt->sgl->dma_address = iova;
	sgt->sgl->dma_length = size;
	वापस pages;

out_मुक्त_sg:
	sg_मुक्त_table(sgt);
out_मुक्त_iova:
	iommu_dma_मुक्त_iova(cookie, iova, size, शून्य);
out_मुक्त_pages:
	__iommu_dma_मुक्त_pages(pages, count);
	वापस शून्य;
पूर्ण

अटल व्योम *iommu_dma_alloc_remap(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp, pgprot_t prot,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page **pages;
	काष्ठा sg_table sgt;
	व्योम *vaddr;

	pages = __iommu_dma_alloc_noncontiguous(dev, size, &sgt, gfp, prot,
						attrs);
	अगर (!pages)
		वापस शून्य;
	*dma_handle = sgt.sgl->dma_address;
	sg_मुक्त_table(&sgt);
	vaddr = dma_common_pages_remap(pages, size, prot,
			__builtin_वापस_address(0));
	अगर (!vaddr)
		जाओ out_unmap;
	वापस vaddr;

out_unmap:
	__iommu_dma_unmap(dev, *dma_handle, size);
	__iommu_dma_मुक्त_pages(pages, PAGE_ALIGN(size) >> PAGE_SHIFT);
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_DMA_REMAP
अटल काष्ठा sg_table *iommu_dma_alloc_noncontiguous(काष्ठा device *dev,
		माप_प्रकार size, क्रमागत dma_data_direction dir, gfp_t gfp,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_sgt_handle *sh;

	sh = kदो_स्मृति(माप(*sh), gfp);
	अगर (!sh)
		वापस शून्य;

	sh->pages = __iommu_dma_alloc_noncontiguous(dev, size, &sh->sgt, gfp,
						    PAGE_KERNEL, attrs);
	अगर (!sh->pages) अणु
		kमुक्त(sh);
		वापस शून्य;
	पूर्ण
	वापस &sh->sgt;
पूर्ण

अटल व्योम iommu_dma_मुक्त_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
	काष्ठा dma_sgt_handle *sh = sgt_handle(sgt);

	__iommu_dma_unmap(dev, sgt->sgl->dma_address, size);
	__iommu_dma_मुक्त_pages(sh->pages, PAGE_ALIGN(size) >> PAGE_SHIFT);
	sg_मुक्त_table(&sh->sgt);
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_REMAP */

अटल व्योम iommu_dma_sync_single_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t dma_handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t phys;

	अगर (dev_is_dma_coherent(dev) && !dev_is_untrusted(dev))
		वापस;

	phys = iommu_iova_to_phys(iommu_get_dma_करोमुख्य(dev), dma_handle);
	अगर (!dev_is_dma_coherent(dev))
		arch_sync_dma_क्रम_cpu(phys, size, dir);

	अगर (is_swiotlb_buffer(phys))
		swiotlb_sync_single_क्रम_cpu(dev, phys, size, dir);
पूर्ण

अटल व्योम iommu_dma_sync_single_क्रम_device(काष्ठा device *dev,
		dma_addr_t dma_handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t phys;

	अगर (dev_is_dma_coherent(dev) && !dev_is_untrusted(dev))
		वापस;

	phys = iommu_iova_to_phys(iommu_get_dma_करोमुख्य(dev), dma_handle);
	अगर (is_swiotlb_buffer(phys))
		swiotlb_sync_single_क्रम_device(dev, phys, size, dir);

	अगर (!dev_is_dma_coherent(dev))
		arch_sync_dma_क्रम_device(phys, size, dir);
पूर्ण

अटल व्योम iommu_dma_sync_sg_क्रम_cpu(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nelems,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	अगर (dev_is_dma_coherent(dev) && !dev_is_untrusted(dev))
		वापस;

	क्रम_each_sg(sgl, sg, nelems, i) अणु
		अगर (!dev_is_dma_coherent(dev))
			arch_sync_dma_क्रम_cpu(sg_phys(sg), sg->length, dir);

		अगर (is_swiotlb_buffer(sg_phys(sg)))
			swiotlb_sync_single_क्रम_cpu(dev, sg_phys(sg),
						    sg->length, dir);
	पूर्ण
पूर्ण

अटल व्योम iommu_dma_sync_sg_क्रम_device(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nelems,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	अगर (dev_is_dma_coherent(dev) && !dev_is_untrusted(dev))
		वापस;

	क्रम_each_sg(sgl, sg, nelems, i) अणु
		अगर (is_swiotlb_buffer(sg_phys(sg)))
			swiotlb_sync_single_क्रम_device(dev, sg_phys(sg),
						       sg->length, dir);

		अगर (!dev_is_dma_coherent(dev))
			arch_sync_dma_क्रम_device(sg_phys(sg), sg->length, dir);
	पूर्ण
पूर्ण

अटल dma_addr_t iommu_dma_map_page(काष्ठा device *dev, काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	phys_addr_t phys = page_to_phys(page) + offset;
	bool coherent = dev_is_dma_coherent(dev);
	dma_addr_t dma_handle;

	dma_handle = __iommu_dma_map_swiotlb(dev, phys, size, dma_get_mask(dev),
			coherent, dir, attrs);
	अगर (!coherent && !(attrs & DMA_ATTR_SKIP_CPU_SYNC) &&
	    dma_handle != DMA_MAPPING_ERROR)
		arch_sync_dma_क्रम_device(phys, size, dir);
	वापस dma_handle;
पूर्ण

अटल व्योम iommu_dma_unmap_page(काष्ठा device *dev, dma_addr_t dma_handle,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		iommu_dma_sync_single_क्रम_cpu(dev, dma_handle, size, dir);
	__iommu_dma_unmap_swiotlb(dev, dma_handle, size, dir, attrs);
पूर्ण

/*
 * Prepare a successfully-mapped scatterlist to give back to the caller.
 *
 * At this poपूर्णांक the segments are alपढ़ोy laid out by iommu_dma_map_sg() to
 * aव्योम inभागidually crossing any boundaries, so we merely need to check a
 * segment's start address to aव्योम concatenating across one.
 */
अटल पूर्णांक __finalise_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		dma_addr_t dma_addr)
अणु
	काष्ठा scatterlist *s, *cur = sg;
	अचिन्हित दीर्घ seg_mask = dma_get_seg_boundary(dev);
	अचिन्हित पूर्णांक cur_len = 0, max_len = dma_get_max_seg_size(dev);
	पूर्णांक i, count = 0;

	क्रम_each_sg(sg, s, nents, i) अणु
		/* Restore this segment's original unaligned fields first */
		अचिन्हित पूर्णांक s_iova_off = sg_dma_address(s);
		अचिन्हित पूर्णांक s_length = sg_dma_len(s);
		अचिन्हित पूर्णांक s_iova_len = s->length;

		s->offset += s_iova_off;
		s->length = s_length;
		sg_dma_address(s) = DMA_MAPPING_ERROR;
		sg_dma_len(s) = 0;

		/*
		 * Now fill in the real DMA data. If...
		 * - there is a valid output segment to append to
		 * - and this segment starts on an IOVA page boundary
		 * - but करोesn't fall at a segment boundary
		 * - and wouldn't make the resulting output segment too दीर्घ
		 */
		अगर (cur_len && !s_iova_off && (dma_addr & seg_mask) &&
		    (max_len - cur_len >= s_length)) अणु
			/* ...then concatenate it with the previous one */
			cur_len += s_length;
		पूर्ण अन्यथा अणु
			/* Otherwise start the next output segment */
			अगर (i > 0)
				cur = sg_next(cur);
			cur_len = s_length;
			count++;

			sg_dma_address(cur) = dma_addr + s_iova_off;
		पूर्ण

		sg_dma_len(cur) = cur_len;
		dma_addr += s_iova_len;

		अगर (s_length + s_iova_off < s_iova_len)
			cur_len = 0;
	पूर्ण
	वापस count;
पूर्ण

/*
 * If mapping failed, then just restore the original list,
 * but making sure the DMA fields are invalidated.
 */
अटल व्योम __invalidate_sg(काष्ठा scatterlist *sg, पूर्णांक nents)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i) अणु
		अगर (sg_dma_address(s) != DMA_MAPPING_ERROR)
			s->offset += sg_dma_address(s);
		अगर (sg_dma_len(s))
			s->length = sg_dma_len(s);
		sg_dma_address(s) = DMA_MAPPING_ERROR;
		sg_dma_len(s) = 0;
	पूर्ण
पूर्ण

अटल व्योम iommu_dma_unmap_sg_swiotlb(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i)
		__iommu_dma_unmap_swiotlb(dev, sg_dma_address(s),
				sg_dma_len(s), dir, attrs);
पूर्ण

अटल पूर्णांक iommu_dma_map_sg_swiotlb(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i) अणु
		sg_dma_address(s) = __iommu_dma_map_swiotlb(dev, sg_phys(s),
				s->length, dma_get_mask(dev),
				dev_is_dma_coherent(dev), dir, attrs);
		अगर (sg_dma_address(s) == DMA_MAPPING_ERROR)
			जाओ out_unmap;
		sg_dma_len(s) = s->length;
	पूर्ण

	वापस nents;

out_unmap:
	iommu_dma_unmap_sg_swiotlb(dev, sg, i, dir, attrs | DMA_ATTR_SKIP_CPU_SYNC);
	वापस 0;
पूर्ण

/*
 * The DMA API client is passing in a scatterlist which could describe
 * any old buffer layout, but the IOMMU API requires everything to be
 * aligned to IOMMU pages. Hence the need क्रम this complicated bit of
 * impedance-matching, to be able to hand off a suitably-aligned list,
 * but still preserve the original offsets and sizes क्रम the caller.
 */
अटल पूर्णांक iommu_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_dma_करोमुख्य(dev);
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iova_करोमुख्य *iovad = &cookie->iovad;
	काष्ठा scatterlist *s, *prev = शून्य;
	पूर्णांक prot = dma_info_to_prot(dir, dev_is_dma_coherent(dev), attrs);
	dma_addr_t iova;
	माप_प्रकार iova_len = 0;
	अचिन्हित दीर्घ mask = dma_get_seg_boundary(dev);
	पूर्णांक i;

	अगर (अटल_branch_unlikely(&iommu_deferred_attach_enabled) &&
	    iommu_deferred_attach(dev, करोमुख्य))
		वापस 0;

	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		iommu_dma_sync_sg_क्रम_device(dev, sg, nents, dir);

	अगर (dev_is_untrusted(dev))
		वापस iommu_dma_map_sg_swiotlb(dev, sg, nents, dir, attrs);

	/*
	 * Work out how much IOVA space we need, and align the segments to
	 * IOVA granules क्रम the IOMMU driver to handle. With some clever
	 * trickery we can modअगरy the list in-place, but reversibly, by
	 * stashing the unaligned parts in the as-yet-unused DMA fields.
	 */
	क्रम_each_sg(sg, s, nents, i) अणु
		माप_प्रकार s_iova_off = iova_offset(iovad, s->offset);
		माप_प्रकार s_length = s->length;
		माप_प्रकार pad_len = (mask - iova_len + 1) & mask;

		sg_dma_address(s) = s_iova_off;
		sg_dma_len(s) = s_length;
		s->offset -= s_iova_off;
		s_length = iova_align(iovad, s_length + s_iova_off);
		s->length = s_length;

		/*
		 * Due to the alignment of our single IOVA allocation, we can
		 * depend on these assumptions about the segment boundary mask:
		 * - If mask size >= IOVA size, then the IOVA range cannot
		 *   possibly fall across a boundary, so we करोn't care.
		 * - If mask size < IOVA size, then the IOVA range must start
		 *   exactly on a boundary, thereक्रमe we can lay things out
		 *   based purely on segment lengths without needing to know
		 *   the actual addresses beक्रमehand.
		 * - The mask must be a घातer of 2, so pad_len == 0 अगर
		 *   iova_len == 0, thus we cannot dereference prev the first
		 *   समय through here (i.e. beक्रमe it has a meaningful value).
		 */
		अगर (pad_len && pad_len < s_length - 1) अणु
			prev->length += pad_len;
			iova_len += pad_len;
		पूर्ण

		iova_len += s_length;
		prev = s;
	पूर्ण

	iova = iommu_dma_alloc_iova(करोमुख्य, iova_len, dma_get_mask(dev), dev);
	अगर (!iova)
		जाओ out_restore_sg;

	/*
	 * We'll leave any physical concatenation to the IOMMU driver's
	 * implementation - it knows better than we करो.
	 */
	अगर (iommu_map_sg_atomic(करोमुख्य, iova, sg, nents, prot) < iova_len)
		जाओ out_मुक्त_iova;

	वापस __finalise_sg(dev, sg, nents, iova);

out_मुक्त_iova:
	iommu_dma_मुक्त_iova(cookie, iova, iova_len, शून्य);
out_restore_sg:
	__invalidate_sg(sg, nents);
	वापस 0;
पूर्ण

अटल व्योम iommu_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t start, end;
	काष्ठा scatterlist *पंचांगp;
	पूर्णांक i;

	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		iommu_dma_sync_sg_क्रम_cpu(dev, sg, nents, dir);

	अगर (dev_is_untrusted(dev)) अणु
		iommu_dma_unmap_sg_swiotlb(dev, sg, nents, dir, attrs);
		वापस;
	पूर्ण

	/*
	 * The scatterlist segments are mapped पूर्णांकo a single
	 * contiguous IOVA allocation, so this is incredibly easy.
	 */
	start = sg_dma_address(sg);
	क्रम_each_sg(sg_next(sg), पंचांगp, nents - 1, i) अणु
		अगर (sg_dma_len(पंचांगp) == 0)
			अवरोध;
		sg = पंचांगp;
	पूर्ण
	end = sg_dma_address(sg) + sg_dma_len(sg);
	__iommu_dma_unmap(dev, start, end - start);
पूर्ण

अटल dma_addr_t iommu_dma_map_resource(काष्ठा device *dev, phys_addr_t phys,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस __iommu_dma_map(dev, phys, size,
			dma_info_to_prot(dir, false, attrs) | IOMMU_MMIO,
			dma_get_mask(dev));
पूर्ण

अटल व्योम iommu_dma_unmap_resource(काष्ठा device *dev, dma_addr_t handle,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	__iommu_dma_unmap(dev, handle, size);
पूर्ण

अटल व्योम __iommu_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr)
अणु
	माप_प्रकार alloc_size = PAGE_ALIGN(size);
	पूर्णांक count = alloc_size >> PAGE_SHIFT;
	काष्ठा page *page = शून्य, **pages = शून्य;

	/* Non-coherent atomic allocation? Easy */
	अगर (IS_ENABLED(CONFIG_DMA_सूचीECT_REMAP) &&
	    dma_मुक्त_from_pool(dev, cpu_addr, alloc_size))
		वापस;

	अगर (IS_ENABLED(CONFIG_DMA_REMAP) && is_vदो_स्मृति_addr(cpu_addr)) अणु
		/*
		 * If it the address is remapped, then it's either non-coherent
		 * or highmem CMA, or an iommu_dma_alloc_remap() स्थिरruction.
		 */
		pages = dma_common_find_pages(cpu_addr);
		अगर (!pages)
			page = vदो_स्मृति_to_page(cpu_addr);
		dma_common_मुक्त_remap(cpu_addr, alloc_size);
	पूर्ण अन्यथा अणु
		/* Lowmem means a coherent atomic or CMA allocation */
		page = virt_to_page(cpu_addr);
	पूर्ण

	अगर (pages)
		__iommu_dma_मुक्त_pages(pages, count);
	अगर (page)
		dma_मुक्त_contiguous(dev, page, alloc_size);
पूर्ण

अटल व्योम iommu_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t handle, अचिन्हित दीर्घ attrs)
अणु
	__iommu_dma_unmap(dev, handle, size);
	__iommu_dma_मुक्त(dev, size, cpu_addr);
पूर्ण

अटल व्योम *iommu_dma_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा page **pagep, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	bool coherent = dev_is_dma_coherent(dev);
	माप_प्रकार alloc_size = PAGE_ALIGN(size);
	पूर्णांक node = dev_to_node(dev);
	काष्ठा page *page = शून्य;
	व्योम *cpu_addr;

	page = dma_alloc_contiguous(dev, alloc_size, gfp);
	अगर (!page)
		page = alloc_pages_node(node, gfp, get_order(alloc_size));
	अगर (!page)
		वापस शून्य;

	अगर (IS_ENABLED(CONFIG_DMA_REMAP) && (!coherent || PageHighMem(page))) अणु
		pgprot_t prot = dma_pgprot(dev, PAGE_KERNEL, attrs);

		cpu_addr = dma_common_contiguous_remap(page, alloc_size,
				prot, __builtin_वापस_address(0));
		अगर (!cpu_addr)
			जाओ out_मुक्त_pages;

		अगर (!coherent)
			arch_dma_prep_coherent(page, size);
	पूर्ण अन्यथा अणु
		cpu_addr = page_address(page);
	पूर्ण

	*pagep = page;
	स_रखो(cpu_addr, 0, alloc_size);
	वापस cpu_addr;
out_मुक्त_pages:
	dma_मुक्त_contiguous(dev, page, alloc_size);
	वापस शून्य;
पूर्ण

अटल व्योम *iommu_dma_alloc(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	bool coherent = dev_is_dma_coherent(dev);
	पूर्णांक ioprot = dma_info_to_prot(DMA_BIसूचीECTIONAL, coherent, attrs);
	काष्ठा page *page = शून्य;
	व्योम *cpu_addr;

	gfp |= __GFP_ZERO;

	अगर (IS_ENABLED(CONFIG_DMA_REMAP) && gfpflags_allow_blocking(gfp) &&
	    !(attrs & DMA_ATTR_FORCE_CONTIGUOUS)) अणु
		वापस iommu_dma_alloc_remap(dev, size, handle, gfp,
				dma_pgprot(dev, PAGE_KERNEL, attrs), attrs);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_DMA_सूचीECT_REMAP) &&
	    !gfpflags_allow_blocking(gfp) && !coherent)
		page = dma_alloc_from_pool(dev, PAGE_ALIGN(size), &cpu_addr,
					       gfp, शून्य);
	अन्यथा
		cpu_addr = iommu_dma_alloc_pages(dev, size, &page, gfp, attrs);
	अगर (!cpu_addr)
		वापस शून्य;

	*handle = __iommu_dma_map(dev, page_to_phys(page), size, ioprot,
			dev->coherent_dma_mask);
	अगर (*handle == DMA_MAPPING_ERROR) अणु
		__iommu_dma_मुक्त(dev, size, cpu_addr);
		वापस शून्य;
	पूर्ण

	वापस cpu_addr;
पूर्ण

अटल पूर्णांक iommu_dma_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	अचिन्हित दीर्घ pfn, off = vma->vm_pgoff;
	पूर्णांक ret;

	vma->vm_page_prot = dma_pgprot(dev, vma->vm_page_prot, attrs);

	अगर (dma_mmap_from_dev_coherent(dev, vma, cpu_addr, size, &ret))
		वापस ret;

	अगर (off >= nr_pages || vma_pages(vma) > nr_pages - off)
		वापस -ENXIO;

	अगर (IS_ENABLED(CONFIG_DMA_REMAP) && is_vदो_स्मृति_addr(cpu_addr)) अणु
		काष्ठा page **pages = dma_common_find_pages(cpu_addr);

		अगर (pages)
			वापस vm_map_pages(vma, pages, nr_pages);
		pfn = vदो_स्मृति_to_pfn(cpu_addr);
	पूर्ण अन्यथा अणु
		pfn = page_to_pfn(virt_to_page(cpu_addr));
	पूर्ण

	वापस remap_pfn_range(vma, vma->vm_start, pfn + off,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
पूर्ण

अटल पूर्णांक iommu_dma_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page *page;
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_DMA_REMAP) && is_vदो_स्मृति_addr(cpu_addr)) अणु
		काष्ठा page **pages = dma_common_find_pages(cpu_addr);

		अगर (pages) अणु
			वापस sg_alloc_table_from_pages(sgt, pages,
					PAGE_ALIGN(size) >> PAGE_SHIFT,
					0, size, GFP_KERNEL);
		पूर्ण

		page = vदो_स्मृति_to_page(cpu_addr);
	पूर्ण अन्यथा अणु
		page = virt_to_page(cpu_addr);
	पूर्ण

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
	अगर (!ret)
		sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ iommu_dma_get_merge_boundary(काष्ठा device *dev)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_dma_करोमुख्य(dev);

	वापस (1UL << __ffs(करोमुख्य->pgsize_biपंचांगap)) - 1;
पूर्ण

अटल स्थिर काष्ठा dma_map_ops iommu_dma_ops = अणु
	.alloc			= iommu_dma_alloc,
	.मुक्त			= iommu_dma_मुक्त,
	.alloc_pages		= dma_common_alloc_pages,
	.मुक्त_pages		= dma_common_मुक्त_pages,
#अगर_घोषित CONFIG_DMA_REMAP
	.alloc_noncontiguous	= iommu_dma_alloc_noncontiguous,
	.मुक्त_noncontiguous	= iommu_dma_मुक्त_noncontiguous,
#पूर्ण_अगर
	.mmap			= iommu_dma_mmap,
	.get_sgtable		= iommu_dma_get_sgtable,
	.map_page		= iommu_dma_map_page,
	.unmap_page		= iommu_dma_unmap_page,
	.map_sg			= iommu_dma_map_sg,
	.unmap_sg		= iommu_dma_unmap_sg,
	.sync_single_क्रम_cpu	= iommu_dma_sync_single_क्रम_cpu,
	.sync_single_क्रम_device	= iommu_dma_sync_single_क्रम_device,
	.sync_sg_क्रम_cpu	= iommu_dma_sync_sg_क्रम_cpu,
	.sync_sg_क्रम_device	= iommu_dma_sync_sg_क्रम_device,
	.map_resource		= iommu_dma_map_resource,
	.unmap_resource		= iommu_dma_unmap_resource,
	.get_merge_boundary	= iommu_dma_get_merge_boundary,
पूर्ण;

/*
 * The IOMMU core code allocates the शेष DMA करोमुख्य, which the underlying
 * IOMMU driver needs to support via the dma-iommu layer.
 */
व्योम iommu_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	अगर (!करोमुख्य)
		जाओ out_err;

	/*
	 * The IOMMU core code allocates the शेष DMA करोमुख्य, which the
	 * underlying IOMMU driver needs to support via the dma-iommu layer.
	 */
	अगर (करोमुख्य->type == IOMMU_DOMAIN_DMA) अणु
		अगर (iommu_dma_init_करोमुख्य(करोमुख्य, dma_base, size, dev))
			जाओ out_err;
		dev->dma_ops = &iommu_dma_ops;
	पूर्ण

	वापस;
out_err:
	 pr_warn("Failed to set up IOMMU for device %s; retaining platform DMA ops\n",
		 dev_name(dev));
पूर्ण

अटल काष्ठा iommu_dma_msi_page *iommu_dma_get_msi_page(काष्ठा device *dev,
		phys_addr_t msi_addr, काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा iommu_dma_cookie *cookie = करोमुख्य->iova_cookie;
	काष्ठा iommu_dma_msi_page *msi_page;
	dma_addr_t iova;
	पूर्णांक prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;
	माप_प्रकार size = cookie_msi_granule(cookie);

	msi_addr &= ~(phys_addr_t)(size - 1);
	list_क्रम_each_entry(msi_page, &cookie->msi_page_list, list)
		अगर (msi_page->phys == msi_addr)
			वापस msi_page;

	msi_page = kzalloc(माप(*msi_page), GFP_KERNEL);
	अगर (!msi_page)
		वापस शून्य;

	iova = iommu_dma_alloc_iova(करोमुख्य, size, dma_get_mask(dev), dev);
	अगर (!iova)
		जाओ out_मुक्त_page;

	अगर (iommu_map(करोमुख्य, iova, msi_addr, size, prot))
		जाओ out_मुक्त_iova;

	INIT_LIST_HEAD(&msi_page->list);
	msi_page->phys = msi_addr;
	msi_page->iova = iova;
	list_add(&msi_page->list, &cookie->msi_page_list);
	वापस msi_page;

out_मुक्त_iova:
	iommu_dma_मुक्त_iova(cookie, iova, size, शून्य);
out_मुक्त_page:
	kमुक्त(msi_page);
	वापस शून्य;
पूर्ण

पूर्णांक iommu_dma_prepare_msi(काष्ठा msi_desc *desc, phys_addr_t msi_addr)
अणु
	काष्ठा device *dev = msi_desc_to_dev(desc);
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	काष्ठा iommu_dma_msi_page *msi_page;
	अटल DEFINE_MUTEX(msi_prepare_lock); /* see below */

	अगर (!करोमुख्य || !करोमुख्य->iova_cookie) अणु
		desc->iommu_cookie = शून्य;
		वापस 0;
	पूर्ण

	/*
	 * In fact the whole prepare operation should alपढ़ोy be serialised by
	 * irq_करोमुख्य_mutex further up the callchain, but that's pretty subtle
	 * on its own, so consider this locking as failsafe करोcumentation...
	 */
	mutex_lock(&msi_prepare_lock);
	msi_page = iommu_dma_get_msi_page(dev, msi_addr, करोमुख्य);
	mutex_unlock(&msi_prepare_lock);

	msi_desc_set_iommu_cookie(desc, msi_page);

	अगर (!msi_page)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम iommu_dma_compose_msi_msg(काष्ठा msi_desc *desc,
			       काष्ठा msi_msg *msg)
अणु
	काष्ठा device *dev = msi_desc_to_dev(desc);
	स्थिर काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	स्थिर काष्ठा iommu_dma_msi_page *msi_page;

	msi_page = msi_desc_get_iommu_cookie(desc);

	अगर (!करोमुख्य || !करोमुख्य->iova_cookie || WARN_ON(!msi_page))
		वापस;

	msg->address_hi = upper_32_bits(msi_page->iova);
	msg->address_lo &= cookie_msi_granule(करोमुख्य->iova_cookie) - 1;
	msg->address_lo += lower_32_bits(msi_page->iova);
पूर्ण

अटल पूर्णांक iommu_dma_init(व्योम)
अणु
	अगर (is_kdump_kernel())
		अटल_branch_enable(&iommu_deferred_attach_enabled);

	वापस iova_cache_get();
पूर्ण
arch_initcall(iommu_dma_init);
