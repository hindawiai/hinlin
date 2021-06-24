<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2012
 *
 * Author(s):
 *   Jan Glauber <jang@linux.vnet.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/pci_dma.h>

अटल काष्ठा kmem_cache *dma_region_table_cache;
अटल काष्ठा kmem_cache *dma_page_table_cache;
अटल पूर्णांक s390_iommu_strict;

अटल पूर्णांक zpci_refresh_global(काष्ठा zpci_dev *zdev)
अणु
	वापस zpci_refresh_trans((u64) zdev->fh << 32, zdev->start_dma,
				  zdev->iommu_pages * PAGE_SIZE);
पूर्ण

अचिन्हित दीर्घ *dma_alloc_cpu_table(व्योम)
अणु
	अचिन्हित दीर्घ *table, *entry;

	table = kmem_cache_alloc(dma_region_table_cache, GFP_ATOMIC);
	अगर (!table)
		वापस शून्य;

	क्रम (entry = table; entry < table + ZPCI_TABLE_ENTRIES; entry++)
		*entry = ZPCI_TABLE_INVALID;
	वापस table;
पूर्ण

अटल व्योम dma_मुक्त_cpu_table(व्योम *table)
अणु
	kmem_cache_मुक्त(dma_region_table_cache, table);
पूर्ण

अटल अचिन्हित दीर्घ *dma_alloc_page_table(व्योम)
अणु
	अचिन्हित दीर्घ *table, *entry;

	table = kmem_cache_alloc(dma_page_table_cache, GFP_ATOMIC);
	अगर (!table)
		वापस शून्य;

	क्रम (entry = table; entry < table + ZPCI_PT_ENTRIES; entry++)
		*entry = ZPCI_PTE_INVALID;
	वापस table;
पूर्ण

अटल व्योम dma_मुक्त_page_table(व्योम *table)
अणु
	kmem_cache_मुक्त(dma_page_table_cache, table);
पूर्ण

अटल अचिन्हित दीर्घ *dma_get_seg_table_origin(अचिन्हित दीर्घ *entry)
अणु
	अचिन्हित दीर्घ *sto;

	अगर (reg_entry_isvalid(*entry))
		sto = get_rt_sto(*entry);
	अन्यथा अणु
		sto = dma_alloc_cpu_table();
		अगर (!sto)
			वापस शून्य;

		set_rt_sto(entry, sto);
		validate_rt_entry(entry);
		entry_clr_रक्षित(entry);
	पूर्ण
	वापस sto;
पूर्ण

अटल अचिन्हित दीर्घ *dma_get_page_table_origin(अचिन्हित दीर्घ *entry)
अणु
	अचिन्हित दीर्घ *pto;

	अगर (reg_entry_isvalid(*entry))
		pto = get_st_pto(*entry);
	अन्यथा अणु
		pto = dma_alloc_page_table();
		अगर (!pto)
			वापस शून्य;
		set_st_pto(entry, pto);
		validate_st_entry(entry);
		entry_clr_रक्षित(entry);
	पूर्ण
	वापस pto;
पूर्ण

अचिन्हित दीर्घ *dma_walk_cpu_trans(अचिन्हित दीर्घ *rto, dma_addr_t dma_addr)
अणु
	अचिन्हित दीर्घ *sto, *pto;
	अचिन्हित पूर्णांक rtx, sx, px;

	rtx = calc_rtx(dma_addr);
	sto = dma_get_seg_table_origin(&rto[rtx]);
	अगर (!sto)
		वापस शून्य;

	sx = calc_sx(dma_addr);
	pto = dma_get_page_table_origin(&sto[sx]);
	अगर (!pto)
		वापस शून्य;

	px = calc_px(dma_addr);
	वापस &pto[px];
पूर्ण

व्योम dma_update_cpu_trans(अचिन्हित दीर्घ *entry, व्योम *page_addr, पूर्णांक flags)
अणु
	अगर (flags & ZPCI_PTE_INVALID) अणु
		invalidate_pt_entry(entry);
	पूर्ण अन्यथा अणु
		set_pt_pfaa(entry, page_addr);
		validate_pt_entry(entry);
	पूर्ण

	अगर (flags & ZPCI_TABLE_PROTECTED)
		entry_set_रक्षित(entry);
	अन्यथा
		entry_clr_रक्षित(entry);
पूर्ण

अटल पूर्णांक __dma_update_trans(काष्ठा zpci_dev *zdev, अचिन्हित दीर्घ pa,
			      dma_addr_t dma_addr, माप_प्रकार size, पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	u8 *page_addr = (u8 *) (pa & PAGE_MASK);
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित दीर्घ *entry;
	पूर्णांक i, rc = 0;

	अगर (!nr_pages)
		वापस -EINVAL;

	spin_lock_irqsave(&zdev->dma_table_lock, irq_flags);
	अगर (!zdev->dma_table) अणु
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++) अणु
		entry = dma_walk_cpu_trans(zdev->dma_table, dma_addr);
		अगर (!entry) अणु
			rc = -ENOMEM;
			जाओ unकरो_cpu_trans;
		पूर्ण
		dma_update_cpu_trans(entry, page_addr, flags);
		page_addr += PAGE_SIZE;
		dma_addr += PAGE_SIZE;
	पूर्ण

unकरो_cpu_trans:
	अगर (rc && ((flags & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID)) अणु
		flags = ZPCI_PTE_INVALID;
		जबतक (i-- > 0) अणु
			page_addr -= PAGE_SIZE;
			dma_addr -= PAGE_SIZE;
			entry = dma_walk_cpu_trans(zdev->dma_table, dma_addr);
			अगर (!entry)
				अवरोध;
			dma_update_cpu_trans(entry, page_addr, flags);
		पूर्ण
	पूर्ण
out_unlock:
	spin_unlock_irqrestore(&zdev->dma_table_lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक __dma_purge_tlb(काष्ठा zpci_dev *zdev, dma_addr_t dma_addr,
			   माप_प्रकार size, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret;

	/*
	 * With zdev->tlb_refresh == 0, rpcit is not required to establish new
	 * translations when previously invalid translation-table entries are
	 * validated. With lazy unmap, rpcit is skipped क्रम previously valid
	 * entries, but a global rpcit is then required beक्रमe any address can
	 * be re-used, i.e. after each iommu biपंचांगap wrap-around.
	 */
	अगर ((flags & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID) अणु
		अगर (!zdev->tlb_refresh)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!s390_iommu_strict)
			वापस 0;
	पूर्ण

	ret = zpci_refresh_trans((u64) zdev->fh << 32, dma_addr,
				 PAGE_ALIGN(size));
	अगर (ret == -ENOMEM && !s390_iommu_strict) अणु
		/* enable the hypervisor to मुक्त some resources */
		अगर (zpci_refresh_global(zdev))
			जाओ out;

		spin_lock_irqsave(&zdev->iommu_biपंचांगap_lock, irqflags);
		biपंचांगap_andnot(zdev->iommu_biपंचांगap, zdev->iommu_biपंचांगap,
			      zdev->lazy_biपंचांगap, zdev->iommu_pages);
		biपंचांगap_zero(zdev->lazy_biपंचांगap, zdev->iommu_pages);
		spin_unlock_irqrestore(&zdev->iommu_biपंचांगap_lock, irqflags);
		ret = 0;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक dma_update_trans(काष्ठा zpci_dev *zdev, अचिन्हित दीर्घ pa,
			    dma_addr_t dma_addr, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक rc;

	rc = __dma_update_trans(zdev, pa, dma_addr, size, flags);
	अगर (rc)
		वापस rc;

	rc = __dma_purge_tlb(zdev, dma_addr, size, flags);
	अगर (rc && ((flags & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID))
		__dma_update_trans(zdev, pa, dma_addr, size, ZPCI_PTE_INVALID);

	वापस rc;
पूर्ण

व्योम dma_मुक्त_seg_table(अचिन्हित दीर्घ entry)
अणु
	अचिन्हित दीर्घ *sto = get_rt_sto(entry);
	पूर्णांक sx;

	क्रम (sx = 0; sx < ZPCI_TABLE_ENTRIES; sx++)
		अगर (reg_entry_isvalid(sto[sx]))
			dma_मुक्त_page_table(get_st_pto(sto[sx]));

	dma_मुक्त_cpu_table(sto);
पूर्ण

व्योम dma_cleanup_tables(अचिन्हित दीर्घ *table)
अणु
	पूर्णांक rtx;

	अगर (!table)
		वापस;

	क्रम (rtx = 0; rtx < ZPCI_TABLE_ENTRIES; rtx++)
		अगर (reg_entry_isvalid(table[rtx]))
			dma_मुक्त_seg_table(table[rtx]);

	dma_मुक्त_cpu_table(table);
पूर्ण

अटल अचिन्हित दीर्घ __dma_alloc_iommu(काष्ठा device *dev,
				       अचिन्हित दीर्घ start, पूर्णांक size)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));

	वापस iommu_area_alloc(zdev->iommu_biपंचांगap, zdev->iommu_pages,
				start, size, zdev->start_dma >> PAGE_SHIFT,
				dma_get_seg_boundary_nr_pages(dev, PAGE_SHIFT),
				0);
पूर्ण

अटल dma_addr_t dma_alloc_address(काष्ठा device *dev, पूर्णांक size)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	अचिन्हित दीर्घ offset, flags;

	spin_lock_irqsave(&zdev->iommu_biपंचांगap_lock, flags);
	offset = __dma_alloc_iommu(dev, zdev->next_bit, size);
	अगर (offset == -1) अणु
		अगर (!s390_iommu_strict) अणु
			/* global flush beक्रमe DMA addresses are reused */
			अगर (zpci_refresh_global(zdev))
				जाओ out_error;

			biपंचांगap_andnot(zdev->iommu_biपंचांगap, zdev->iommu_biपंचांगap,
				      zdev->lazy_biपंचांगap, zdev->iommu_pages);
			biपंचांगap_zero(zdev->lazy_biपंचांगap, zdev->iommu_pages);
		पूर्ण
		/* wrap-around */
		offset = __dma_alloc_iommu(dev, 0, size);
		अगर (offset == -1)
			जाओ out_error;
	पूर्ण
	zdev->next_bit = offset + size;
	spin_unlock_irqrestore(&zdev->iommu_biपंचांगap_lock, flags);

	वापस zdev->start_dma + offset * PAGE_SIZE;

out_error:
	spin_unlock_irqrestore(&zdev->iommu_biपंचांगap_lock, flags);
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल व्योम dma_मुक्त_address(काष्ठा device *dev, dma_addr_t dma_addr, पूर्णांक size)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	अचिन्हित दीर्घ flags, offset;

	offset = (dma_addr - zdev->start_dma) >> PAGE_SHIFT;

	spin_lock_irqsave(&zdev->iommu_biपंचांगap_lock, flags);
	अगर (!zdev->iommu_biपंचांगap)
		जाओ out;

	अगर (s390_iommu_strict)
		biपंचांगap_clear(zdev->iommu_biपंचांगap, offset, size);
	अन्यथा
		biपंचांगap_set(zdev->lazy_biपंचांगap, offset, size);

out:
	spin_unlock_irqrestore(&zdev->iommu_biपंचांगap_lock, flags);
पूर्ण

अटल अंतरभूत व्योम zpci_err_dma(अचिन्हित दीर्घ rc, अचिन्हित दीर्घ addr)
अणु
	काष्ठा अणु
		अचिन्हित दीर्घ rc;
		अचिन्हित दीर्घ addr;
	पूर्ण __packed data = अणुrc, addrपूर्ण;

	zpci_err_hex(&data, माप(data));
पूर्ण

अटल dma_addr_t s390_dma_map_pages(काष्ठा device *dev, काष्ठा page *page,
				     अचिन्हित दीर्घ offset, माप_प्रकार size,
				     क्रमागत dma_data_direction direction,
				     अचिन्हित दीर्घ attrs)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	अचिन्हित दीर्घ pa = page_to_phys(page) + offset;
	पूर्णांक flags = ZPCI_PTE_VALID;
	अचिन्हित दीर्घ nr_pages;
	dma_addr_t dma_addr;
	पूर्णांक ret;

	/* This rounds up number of pages based on size and offset */
	nr_pages = iommu_num_pages(pa, size, PAGE_SIZE);
	dma_addr = dma_alloc_address(dev, nr_pages);
	अगर (dma_addr == DMA_MAPPING_ERROR) अणु
		ret = -ENOSPC;
		जाओ out_err;
	पूर्ण

	/* Use rounded up size */
	size = nr_pages * PAGE_SIZE;

	अगर (direction == DMA_NONE || direction == DMA_TO_DEVICE)
		flags |= ZPCI_TABLE_PROTECTED;

	ret = dma_update_trans(zdev, pa, dma_addr, size, flags);
	अगर (ret)
		जाओ out_मुक्त;

	atomic64_add(nr_pages, &zdev->mapped_pages);
	वापस dma_addr + (offset & ~PAGE_MASK);

out_मुक्त:
	dma_मुक्त_address(dev, dma_addr, nr_pages);
out_err:
	zpci_err("map error:\n");
	zpci_err_dma(ret, pa);
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल व्योम s390_dma_unmap_pages(काष्ठा device *dev, dma_addr_t dma_addr,
				 माप_प्रकार size, क्रमागत dma_data_direction direction,
				 अचिन्हित दीर्घ attrs)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	पूर्णांक npages, ret;

	npages = iommu_num_pages(dma_addr, size, PAGE_SIZE);
	dma_addr = dma_addr & PAGE_MASK;
	ret = dma_update_trans(zdev, 0, dma_addr, npages * PAGE_SIZE,
			       ZPCI_PTE_INVALID);
	अगर (ret) अणु
		zpci_err("unmap error:\n");
		zpci_err_dma(ret, dma_addr);
		वापस;
	पूर्ण

	atomic64_add(npages, &zdev->unmapped_pages);
	dma_मुक्त_address(dev, dma_addr, npages);
पूर्ण

अटल व्योम *s390_dma_alloc(काष्ठा device *dev, माप_प्रकार size,
			    dma_addr_t *dma_handle, gfp_t flag,
			    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	काष्ठा page *page;
	अचिन्हित दीर्घ pa;
	dma_addr_t map;

	size = PAGE_ALIGN(size);
	page = alloc_pages(flag | __GFP_ZERO, get_order(size));
	अगर (!page)
		वापस शून्य;

	pa = page_to_phys(page);
	map = s390_dma_map_pages(dev, page, 0, size, DMA_BIसूचीECTIONAL, 0);
	अगर (dma_mapping_error(dev, map)) अणु
		मुक्त_pages(pa, get_order(size));
		वापस शून्य;
	पूर्ण

	atomic64_add(size / PAGE_SIZE, &zdev->allocated_pages);
	अगर (dma_handle)
		*dma_handle = map;
	वापस (व्योम *) pa;
पूर्ण

अटल व्योम s390_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size,
			  व्योम *pa, dma_addr_t dma_handle,
			  अचिन्हित दीर्घ attrs)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));

	size = PAGE_ALIGN(size);
	atomic64_sub(size / PAGE_SIZE, &zdev->allocated_pages);
	s390_dma_unmap_pages(dev, dma_handle, size, DMA_BIसूचीECTIONAL, 0);
	मुक्त_pages((अचिन्हित दीर्घ) pa, get_order(size));
पूर्ण

/* Map a segment पूर्णांकo a contiguous dma address area */
अटल पूर्णांक __s390_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
			     माप_प्रकार size, dma_addr_t *handle,
			     क्रमागत dma_data_direction dir)
अणु
	अचिन्हित दीर्घ nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	काष्ठा zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	dma_addr_t dma_addr_base, dma_addr;
	पूर्णांक flags = ZPCI_PTE_VALID;
	काष्ठा scatterlist *s;
	अचिन्हित दीर्घ pa = 0;
	पूर्णांक ret;

	dma_addr_base = dma_alloc_address(dev, nr_pages);
	अगर (dma_addr_base == DMA_MAPPING_ERROR)
		वापस -ENOMEM;

	dma_addr = dma_addr_base;
	अगर (dir == DMA_NONE || dir == DMA_TO_DEVICE)
		flags |= ZPCI_TABLE_PROTECTED;

	क्रम (s = sg; dma_addr < dma_addr_base + size; s = sg_next(s)) अणु
		pa = page_to_phys(sg_page(s));
		ret = __dma_update_trans(zdev, pa, dma_addr,
					 s->offset + s->length, flags);
		अगर (ret)
			जाओ unmap;

		dma_addr += s->offset + s->length;
	पूर्ण
	ret = __dma_purge_tlb(zdev, dma_addr_base, size, flags);
	अगर (ret)
		जाओ unmap;

	*handle = dma_addr_base;
	atomic64_add(nr_pages, &zdev->mapped_pages);

	वापस ret;

unmap:
	dma_update_trans(zdev, 0, dma_addr_base, dma_addr - dma_addr_base,
			 ZPCI_PTE_INVALID);
	dma_मुक्त_address(dev, dma_addr_base, nr_pages);
	zpci_err("map error:\n");
	zpci_err_dma(ret, pa);
	वापस ret;
पूर्ण

अटल पूर्णांक s390_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
			   पूर्णांक nr_elements, क्रमागत dma_data_direction dir,
			   अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s = sg, *start = sg, *dma = sg;
	अचिन्हित पूर्णांक max = dma_get_max_seg_size(dev);
	अचिन्हित पूर्णांक size = s->offset + s->length;
	अचिन्हित पूर्णांक offset = s->offset;
	पूर्णांक count = 0, i;

	क्रम (i = 1; i < nr_elements; i++) अणु
		s = sg_next(s);

		s->dma_address = DMA_MAPPING_ERROR;
		s->dma_length = 0;

		अगर (s->offset || (size & ~PAGE_MASK) ||
		    size + s->length > max) अणु
			अगर (__s390_dma_map_sg(dev, start, size,
					      &dma->dma_address, dir))
				जाओ unmap;

			dma->dma_address += offset;
			dma->dma_length = size - offset;

			size = offset = s->offset;
			start = s;
			dma = sg_next(dma);
			count++;
		पूर्ण
		size += s->length;
	पूर्ण
	अगर (__s390_dma_map_sg(dev, start, size, &dma->dma_address, dir))
		जाओ unmap;

	dma->dma_address += offset;
	dma->dma_length = size - offset;

	वापस count + 1;
unmap:
	क्रम_each_sg(sg, s, count, i)
		s390_dma_unmap_pages(dev, sg_dma_address(s), sg_dma_len(s),
				     dir, attrs);

	वापस 0;
पूर्ण

अटल व्योम s390_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
			      पूर्णांक nr_elements, क्रमागत dma_data_direction dir,
			      अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nr_elements, i) अणु
		अगर (s->dma_length)
			s390_dma_unmap_pages(dev, s->dma_address, s->dma_length,
					     dir, attrs);
		s->dma_address = 0;
		s->dma_length = 0;
	पूर्ण
पूर्ण
	
पूर्णांक zpci_dma_init_device(काष्ठा zpci_dev *zdev)
अणु
	पूर्णांक rc;

	/*
	 * At this poपूर्णांक, अगर the device is part of an IOMMU करोमुख्य, this would
	 * be a strong hपूर्णांक towards a bug in the IOMMU API (common) code and/or
	 * simultaneous access via IOMMU and DMA API. So let's issue a warning.
	 */
	WARN_ON(zdev->s390_करोमुख्य);

	spin_lock_init(&zdev->iommu_biपंचांगap_lock);
	spin_lock_init(&zdev->dma_table_lock);

	zdev->dma_table = dma_alloc_cpu_table();
	अगर (!zdev->dma_table) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Restrict the iommu biपंचांगap size to the minimum of the following:
	 * - मुख्य memory size
	 * - 3-level pagetable address limit minus start_dma offset
	 * - DMA address range allowed by the hardware (clp query pci fn)
	 *
	 * Also set zdev->end_dma to the actual end address of the usable
	 * range, instead of the theoretical maximum as reported by hardware.
	 */
	zdev->start_dma = PAGE_ALIGN(zdev->start_dma);
	zdev->iommu_size = min3((u64) high_memory,
				ZPCI_TABLE_SIZE_RT - zdev->start_dma,
				zdev->end_dma - zdev->start_dma + 1);
	zdev->end_dma = zdev->start_dma + zdev->iommu_size - 1;
	zdev->iommu_pages = zdev->iommu_size >> PAGE_SHIFT;
	zdev->iommu_biपंचांगap = vzalloc(zdev->iommu_pages / 8);
	अगर (!zdev->iommu_biपंचांगap) अणु
		rc = -ENOMEM;
		जाओ मुक्त_dma_table;
	पूर्ण
	अगर (!s390_iommu_strict) अणु
		zdev->lazy_biपंचांगap = vzalloc(zdev->iommu_pages / 8);
		अगर (!zdev->lazy_biपंचांगap) अणु
			rc = -ENOMEM;
			जाओ मुक्त_biपंचांगap;
		पूर्ण

	पूर्ण
	rc = zpci_रेजिस्टर_ioat(zdev, 0, zdev->start_dma, zdev->end_dma,
				(u64) zdev->dma_table);
	अगर (rc)
		जाओ मुक्त_biपंचांगap;

	वापस 0;
मुक्त_biपंचांगap:
	vमुक्त(zdev->iommu_biपंचांगap);
	zdev->iommu_biपंचांगap = शून्य;
	vमुक्त(zdev->lazy_biपंचांगap);
	zdev->lazy_biपंचांगap = शून्य;
मुक्त_dma_table:
	dma_मुक्त_cpu_table(zdev->dma_table);
	zdev->dma_table = शून्य;
out:
	वापस rc;
पूर्ण

व्योम zpci_dma_निकास_device(काष्ठा zpci_dev *zdev)
अणु
	/*
	 * At this poपूर्णांक, अगर the device is part of an IOMMU करोमुख्य, this would
	 * be a strong hपूर्णांक towards a bug in the IOMMU API (common) code and/or
	 * simultaneous access via IOMMU and DMA API. So let's issue a warning.
	 */
	WARN_ON(zdev->s390_करोमुख्य);

	अगर (zpci_unरेजिस्टर_ioat(zdev, 0))
		वापस;

	dma_cleanup_tables(zdev->dma_table);
	zdev->dma_table = शून्य;
	vमुक्त(zdev->iommu_biपंचांगap);
	zdev->iommu_biपंचांगap = शून्य;
	vमुक्त(zdev->lazy_biपंचांगap);
	zdev->lazy_biपंचांगap = शून्य;

	zdev->next_bit = 0;
पूर्ण

अटल पूर्णांक __init dma_alloc_cpu_table_caches(व्योम)
अणु
	dma_region_table_cache = kmem_cache_create("PCI_DMA_region_tables",
					ZPCI_TABLE_SIZE, ZPCI_TABLE_ALIGN,
					0, शून्य);
	अगर (!dma_region_table_cache)
		वापस -ENOMEM;

	dma_page_table_cache = kmem_cache_create("PCI_DMA_page_tables",
					ZPCI_PT_SIZE, ZPCI_PT_ALIGN,
					0, शून्य);
	अगर (!dma_page_table_cache) अणु
		kmem_cache_destroy(dma_region_table_cache);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init zpci_dma_init(व्योम)
अणु
	वापस dma_alloc_cpu_table_caches();
पूर्ण

व्योम zpci_dma_निकास(व्योम)
अणु
	kmem_cache_destroy(dma_page_table_cache);
	kmem_cache_destroy(dma_region_table_cache);
पूर्ण

स्थिर काष्ठा dma_map_ops s390_pci_dma_ops = अणु
	.alloc		= s390_dma_alloc,
	.मुक्त		= s390_dma_मुक्त,
	.map_sg		= s390_dma_map_sg,
	.unmap_sg	= s390_dma_unmap_sg,
	.map_page	= s390_dma_map_pages,
	.unmap_page	= s390_dma_unmap_pages,
	.mmap		= dma_common_mmap,
	.get_sgtable	= dma_common_get_sgtable,
	.alloc_pages	= dma_common_alloc_pages,
	.मुक्त_pages	= dma_common_मुक्त_pages,
	/* dma_supported is unconditionally true without a callback */
पूर्ण;
EXPORT_SYMBOL_GPL(s390_pci_dma_ops);

अटल पूर्णांक __init s390_iommu_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "strict"))
		s390_iommu_strict = 1;
	वापस 1;
पूर्ण

__setup("s390_iommu=", s390_iommu_setup);
