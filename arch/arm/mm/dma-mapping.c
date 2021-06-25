<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/dma-mapping.c
 *
 *  Copyright (C) 2000-2004 Russell King
 *
 *  DMA uncached mapping support.
 */
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/gfp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/iommu.h>
#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sizes.h>
#समावेश <linux/cma.h>

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/highस्मृति.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/dma-iommu.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <xen/swiotlb-xen.h>

#समावेश "dma.h"
#समावेश "mm.h"

काष्ठा arm_dma_alloc_args अणु
	काष्ठा device *dev;
	माप_प्रकार size;
	gfp_t gfp;
	pgprot_t prot;
	स्थिर व्योम *caller;
	bool want_vaddr;
	पूर्णांक coherent_flag;
पूर्ण;

काष्ठा arm_dma_मुक्त_args अणु
	काष्ठा device *dev;
	माप_प्रकार size;
	व्योम *cpu_addr;
	काष्ठा page *page;
	bool want_vaddr;
पूर्ण;

#घोषणा NORMAL	    0
#घोषणा COHERENT    1

काष्ठा arm_dma_allocator अणु
	व्योम *(*alloc)(काष्ठा arm_dma_alloc_args *args,
		       काष्ठा page **ret_page);
	व्योम (*मुक्त)(काष्ठा arm_dma_मुक्त_args *args);
पूर्ण;

काष्ठा arm_dma_buffer अणु
	काष्ठा list_head list;
	व्योम *virt;
	काष्ठा arm_dma_allocator *allocator;
पूर्ण;

अटल LIST_HEAD(arm_dma_bufs);
अटल DEFINE_SPINLOCK(arm_dma_bufs_lock);

अटल काष्ठा arm_dma_buffer *arm_dma_buffer_find(व्योम *virt)
अणु
	काष्ठा arm_dma_buffer *buf, *found = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&arm_dma_bufs_lock, flags);
	list_क्रम_each_entry(buf, &arm_dma_bufs, list) अणु
		अगर (buf->virt == virt) अणु
			list_del(&buf->list);
			found = buf;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&arm_dma_bufs_lock, flags);
	वापस found;
पूर्ण

/*
 * The DMA API is built upon the notion of "buffer ownership".  A buffer
 * is either exclusively owned by the CPU (and thereक्रमe may be accessed
 * by it) or exclusively owned by the DMA device.  These helper functions
 * represent the transitions between these two ownership states.
 *
 * Note, however, that on later ARMs, this notion करोes not work due to
 * speculative prefetches.  We model our approach on the assumption that
 * the CPU करोes करो speculative prefetches, which means we clean caches
 * beक्रमe transfers and delay cache invalidation until transfer completion.
 *
 */
अटल व्योम __dma_page_cpu_to_dev(काष्ठा page *, अचिन्हित दीर्घ,
		माप_प्रकार, क्रमागत dma_data_direction);
अटल व्योम __dma_page_dev_to_cpu(काष्ठा page *, अचिन्हित दीर्घ,
		माप_प्रकार, क्रमागत dma_data_direction);

/**
 * arm_dma_map_page - map a portion of a page क्रम streaming DMA
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @page: page that buffer resides in
 * @offset: offset पूर्णांकo page क्रम start of buffer
 * @size: size of buffer to map
 * @dir: DMA transfer direction
 *
 * Ensure that any data held in the cache is appropriately discarded
 * or written back.
 *
 * The device owns this memory once this call has completed.  The CPU
 * can regain ownership by calling dma_unmap_page().
 */
अटल dma_addr_t arm_dma_map_page(काष्ठा device *dev, काष्ठा page *page,
	     अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
	     अचिन्हित दीर्घ attrs)
अणु
	अगर ((attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
		__dma_page_cpu_to_dev(page, offset, size, dir);
	वापस pfn_to_dma(dev, page_to_pfn(page)) + offset;
पूर्ण

अटल dma_addr_t arm_coherent_dma_map_page(काष्ठा device *dev, काष्ठा page *page,
	     अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
	     अचिन्हित दीर्घ attrs)
अणु
	वापस pfn_to_dma(dev, page_to_pfn(page)) + offset;
पूर्ण

/**
 * arm_dma_unmap_page - unmap a buffer previously mapped through dma_map_page()
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @handle: DMA address of buffer
 * @size: size of buffer (same as passed to dma_map_page)
 * @dir: DMA transfer direction (same as passed to dma_map_page)
 *
 * Unmap a page streaming mode DMA translation.  The handle and size
 * must match what was provided in the previous dma_map_page() call.
 * All other usages are undefined.
 *
 * After this call, पढ़ोs by the CPU to the buffer are guaranteed to see
 * whatever the device wrote there.
 */
अटल व्योम arm_dma_unmap_page(काष्ठा device *dev, dma_addr_t handle,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	अगर ((attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
		__dma_page_dev_to_cpu(pfn_to_page(dma_to_pfn(dev, handle)),
				      handle & ~PAGE_MASK, size, dir);
पूर्ण

अटल व्योम arm_dma_sync_single_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अचिन्हित पूर्णांक offset = handle & (PAGE_SIZE - 1);
	काष्ठा page *page = pfn_to_page(dma_to_pfn(dev, handle-offset));
	__dma_page_dev_to_cpu(page, offset, size, dir);
पूर्ण

अटल व्योम arm_dma_sync_single_क्रम_device(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अचिन्हित पूर्णांक offset = handle & (PAGE_SIZE - 1);
	काष्ठा page *page = pfn_to_page(dma_to_pfn(dev, handle-offset));
	__dma_page_cpu_to_dev(page, offset, size, dir);
पूर्ण

/*
 * Return whether the given device DMA address mask can be supported
 * properly.  For example, अगर your device can only drive the low 24-bits
 * during bus mastering, then you would pass 0x00ffffff as the mask
 * to this function.
 */
अटल पूर्णांक arm_dma_supported(काष्ठा device *dev, u64 mask)
अणु
	अचिन्हित दीर्घ max_dma_pfn = min(max_pfn - 1, arm_dma_pfn_limit);

	/*
	 * Translate the device's DMA mask to a PFN limit.  This
	 * PFN number includes the page which we can DMA to.
	 */
	वापस dma_to_pfn(dev, mask) >= max_dma_pfn;
पूर्ण

स्थिर काष्ठा dma_map_ops arm_dma_ops = अणु
	.alloc			= arm_dma_alloc,
	.मुक्त			= arm_dma_मुक्त,
	.alloc_pages		= dma_direct_alloc_pages,
	.मुक्त_pages		= dma_direct_मुक्त_pages,
	.mmap			= arm_dma_mmap,
	.get_sgtable		= arm_dma_get_sgtable,
	.map_page		= arm_dma_map_page,
	.unmap_page		= arm_dma_unmap_page,
	.map_sg			= arm_dma_map_sg,
	.unmap_sg		= arm_dma_unmap_sg,
	.map_resource		= dma_direct_map_resource,
	.sync_single_क्रम_cpu	= arm_dma_sync_single_क्रम_cpu,
	.sync_single_क्रम_device	= arm_dma_sync_single_क्रम_device,
	.sync_sg_क्रम_cpu	= arm_dma_sync_sg_क्रम_cpu,
	.sync_sg_क्रम_device	= arm_dma_sync_sg_क्रम_device,
	.dma_supported		= arm_dma_supported,
	.get_required_mask	= dma_direct_get_required_mask,
पूर्ण;
EXPORT_SYMBOL(arm_dma_ops);

अटल व्योम *arm_coherent_dma_alloc(काष्ठा device *dev, माप_प्रकार size,
	dma_addr_t *handle, gfp_t gfp, अचिन्हित दीर्घ attrs);
अटल व्योम arm_coherent_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
				  dma_addr_t handle, अचिन्हित दीर्घ attrs);
अटल पूर्णांक arm_coherent_dma_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		 व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		 अचिन्हित दीर्घ attrs);

स्थिर काष्ठा dma_map_ops arm_coherent_dma_ops = अणु
	.alloc			= arm_coherent_dma_alloc,
	.मुक्त			= arm_coherent_dma_मुक्त,
	.alloc_pages		= dma_direct_alloc_pages,
	.मुक्त_pages		= dma_direct_मुक्त_pages,
	.mmap			= arm_coherent_dma_mmap,
	.get_sgtable		= arm_dma_get_sgtable,
	.map_page		= arm_coherent_dma_map_page,
	.map_sg			= arm_dma_map_sg,
	.map_resource		= dma_direct_map_resource,
	.dma_supported		= arm_dma_supported,
	.get_required_mask	= dma_direct_get_required_mask,
पूर्ण;
EXPORT_SYMBOL(arm_coherent_dma_ops);

अटल व्योम __dma_clear_buffer(काष्ठा page *page, माप_प्रकार size, पूर्णांक coherent_flag)
अणु
	/*
	 * Ensure that the allocated pages are zeroed, and that any data
	 * lurking in the kernel direct-mapped region is invalidated.
	 */
	अगर (PageHighMem(page)) अणु
		phys_addr_t base = __pfn_to_phys(page_to_pfn(page));
		phys_addr_t end = base + size;
		जबतक (size > 0) अणु
			व्योम *ptr = kmap_atomic(page);
			स_रखो(ptr, 0, PAGE_SIZE);
			अगर (coherent_flag != COHERENT)
				dmac_flush_range(ptr, ptr + PAGE_SIZE);
			kunmap_atomic(ptr);
			page++;
			size -= PAGE_SIZE;
		पूर्ण
		अगर (coherent_flag != COHERENT)
			outer_flush_range(base, end);
	पूर्ण अन्यथा अणु
		व्योम *ptr = page_address(page);
		स_रखो(ptr, 0, size);
		अगर (coherent_flag != COHERENT) अणु
			dmac_flush_range(ptr, ptr + size);
			outer_flush_range(__pa(ptr), __pa(ptr) + size);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Allocate a DMA buffer क्रम 'dev' of size 'size' using the
 * specअगरied gfp mask.  Note that 'size' must be page aligned.
 */
अटल काष्ठा page *__dma_alloc_buffer(काष्ठा device *dev, माप_प्रकार size,
				       gfp_t gfp, पूर्णांक coherent_flag)
अणु
	अचिन्हित दीर्घ order = get_order(size);
	काष्ठा page *page, *p, *e;

	page = alloc_pages(gfp, order);
	अगर (!page)
		वापस शून्य;

	/*
	 * Now split the huge page and मुक्त the excess pages
	 */
	split_page(page, order);
	क्रम (p = page + (size >> PAGE_SHIFT), e = page + (1 << order); p < e; p++)
		__मुक्त_page(p);

	__dma_clear_buffer(page, size, coherent_flag);

	वापस page;
पूर्ण

/*
 * Free a DMA buffer.  'size' must be page aligned.
 */
अटल व्योम __dma_मुक्त_buffer(काष्ठा page *page, माप_प्रकार size)
अणु
	काष्ठा page *e = page + (size >> PAGE_SHIFT);

	जबतक (page < e) अणु
		__मुक्त_page(page);
		page++;
	पूर्ण
पूर्ण

अटल व्योम *__alloc_from_contiguous(काष्ठा device *dev, माप_प्रकार size,
				     pgprot_t prot, काष्ठा page **ret_page,
				     स्थिर व्योम *caller, bool want_vaddr,
				     पूर्णांक coherent_flag, gfp_t gfp);

अटल व्योम *__alloc_remap_buffer(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp,
				 pgprot_t prot, काष्ठा page **ret_page,
				 स्थिर व्योम *caller, bool want_vaddr);

#घोषणा DEFAULT_DMA_COHERENT_POOL_SIZE	SZ_256K
अटल काष्ठा gen_pool *atomic_pool __ro_after_init;

अटल माप_प्रकार atomic_pool_size __initdata = DEFAULT_DMA_COHERENT_POOL_SIZE;

अटल पूर्णांक __init early_coherent_pool(अक्षर *p)
अणु
	atomic_pool_size = memparse(p, &p);
	वापस 0;
पूर्ण
early_param("coherent_pool", early_coherent_pool);

/*
 * Initialise the coherent pool क्रम atomic allocations.
 */
अटल पूर्णांक __init atomic_pool_init(व्योम)
अणु
	pgprot_t prot = pgprot_dmacoherent(PAGE_KERNEL);
	gfp_t gfp = GFP_KERNEL | GFP_DMA;
	काष्ठा page *page;
	व्योम *ptr;

	atomic_pool = gen_pool_create(PAGE_SHIFT, -1);
	अगर (!atomic_pool)
		जाओ out;
	/*
	 * The atomic pool is only used क्रम non-coherent allocations
	 * so we must pass NORMAL क्रम coherent_flag.
	 */
	अगर (dev_get_cma_area(शून्य))
		ptr = __alloc_from_contiguous(शून्य, atomic_pool_size, prot,
				      &page, atomic_pool_init, true, NORMAL,
				      GFP_KERNEL);
	अन्यथा
		ptr = __alloc_remap_buffer(शून्य, atomic_pool_size, gfp, prot,
					   &page, atomic_pool_init, true);
	अगर (ptr) अणु
		पूर्णांक ret;

		ret = gen_pool_add_virt(atomic_pool, (अचिन्हित दीर्घ)ptr,
					page_to_phys(page),
					atomic_pool_size, -1);
		अगर (ret)
			जाओ destroy_genpool;

		gen_pool_set_algo(atomic_pool,
				gen_pool_first_fit_order_align,
				शून्य);
		pr_info("DMA: preallocated %zu KiB pool for atomic coherent allocations\n",
		       atomic_pool_size / 1024);
		वापस 0;
	पूर्ण

destroy_genpool:
	gen_pool_destroy(atomic_pool);
	atomic_pool = शून्य;
out:
	pr_err("DMA: failed to allocate %zu KiB pool for atomic coherent allocation\n",
	       atomic_pool_size / 1024);
	वापस -ENOMEM;
पूर्ण
/*
 * CMA is activated by core_initcall, so we must be called after it.
 */
postcore_initcall(atomic_pool_init);

काष्ठा dma_contig_early_reserve अणु
	phys_addr_t base;
	अचिन्हित दीर्घ size;
पूर्ण;

अटल काष्ठा dma_contig_early_reserve dma_mmu_remap[MAX_CMA_AREAS] __initdata;

अटल पूर्णांक dma_mmu_remap_num __initdata;

व्योम __init dma_contiguous_early_fixup(phys_addr_t base, अचिन्हित दीर्घ size)
अणु
	dma_mmu_remap[dma_mmu_remap_num].base = base;
	dma_mmu_remap[dma_mmu_remap_num].size = size;
	dma_mmu_remap_num++;
पूर्ण

व्योम __init dma_contiguous_remap(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < dma_mmu_remap_num; i++) अणु
		phys_addr_t start = dma_mmu_remap[i].base;
		phys_addr_t end = start + dma_mmu_remap[i].size;
		काष्ठा map_desc map;
		अचिन्हित दीर्घ addr;

		अगर (end > arm_lowmem_limit)
			end = arm_lowmem_limit;
		अगर (start >= end)
			जारी;

		map.pfn = __phys_to_pfn(start);
		map.भव = __phys_to_virt(start);
		map.length = end - start;
		map.type = MT_MEMORY_DMA_READY;

		/*
		 * Clear previous low-memory mapping to ensure that the
		 * TLB करोes not see any conflicting entries, then flush
		 * the TLB of the old entries beक्रमe creating new mappings.
		 *
		 * This ensures that any speculatively loaded TLB entries
		 * (even though they may be rare) can not cause any problems,
		 * and ensures that this code is architecturally compliant.
		 */
		क्रम (addr = __phys_to_virt(start); addr < __phys_to_virt(end);
		     addr += PMD_SIZE)
			pmd_clear(pmd_off_k(addr));

		flush_tlb_kernel_range(__phys_to_virt(start),
				       __phys_to_virt(end));

		iotable_init(&map, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक __dma_update_pte(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा page *page = virt_to_page(addr);
	pgprot_t prot = *(pgprot_t *)data;

	set_pte_ext(pte, mk_pte(page, prot), 0);
	वापस 0;
पूर्ण

अटल व्योम __dma_remap(काष्ठा page *page, माप_प्रकार size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) page_address(page);
	अचिन्हित end = start + size;

	apply_to_page_range(&init_mm, start, size, __dma_update_pte, &prot);
	flush_tlb_kernel_range(start, end);
पूर्ण

अटल व्योम *__alloc_remap_buffer(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp,
				 pgprot_t prot, काष्ठा page **ret_page,
				 स्थिर व्योम *caller, bool want_vaddr)
अणु
	काष्ठा page *page;
	व्योम *ptr = शून्य;
	/*
	 * __alloc_remap_buffer is only called when the device is
	 * non-coherent
	 */
	page = __dma_alloc_buffer(dev, size, gfp, NORMAL);
	अगर (!page)
		वापस शून्य;
	अगर (!want_vaddr)
		जाओ out;

	ptr = dma_common_contiguous_remap(page, size, prot, caller);
	अगर (!ptr) अणु
		__dma_मुक्त_buffer(page, size);
		वापस शून्य;
	पूर्ण

 out:
	*ret_page = page;
	वापस ptr;
पूर्ण

अटल व्योम *__alloc_from_pool(माप_प्रकार size, काष्ठा page **ret_page)
अणु
	अचिन्हित दीर्घ val;
	व्योम *ptr = शून्य;

	अगर (!atomic_pool) अणु
		WARN(1, "coherent pool not initialised!\n");
		वापस शून्य;
	पूर्ण

	val = gen_pool_alloc(atomic_pool, size);
	अगर (val) अणु
		phys_addr_t phys = gen_pool_virt_to_phys(atomic_pool, val);

		*ret_page = phys_to_page(phys);
		ptr = (व्योम *)val;
	पूर्ण

	वापस ptr;
पूर्ण

अटल bool __in_atomic_pool(व्योम *start, माप_प्रकार size)
अणु
	वापस gen_pool_has_addr(atomic_pool, (अचिन्हित दीर्घ)start, size);
पूर्ण

अटल पूर्णांक __मुक्त_from_pool(व्योम *start, माप_प्रकार size)
अणु
	अगर (!__in_atomic_pool(start, size))
		वापस 0;

	gen_pool_मुक्त(atomic_pool, (अचिन्हित दीर्घ)start, size);

	वापस 1;
पूर्ण

अटल व्योम *__alloc_from_contiguous(काष्ठा device *dev, माप_प्रकार size,
				     pgprot_t prot, काष्ठा page **ret_page,
				     स्थिर व्योम *caller, bool want_vaddr,
				     पूर्णांक coherent_flag, gfp_t gfp)
अणु
	अचिन्हित दीर्घ order = get_order(size);
	माप_प्रकार count = size >> PAGE_SHIFT;
	काष्ठा page *page;
	व्योम *ptr = शून्य;

	page = dma_alloc_from_contiguous(dev, count, order, gfp & __GFP_NOWARN);
	अगर (!page)
		वापस शून्य;

	__dma_clear_buffer(page, size, coherent_flag);

	अगर (!want_vaddr)
		जाओ out;

	अगर (PageHighMem(page)) अणु
		ptr = dma_common_contiguous_remap(page, size, prot, caller);
		अगर (!ptr) अणु
			dma_release_from_contiguous(dev, page, count);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		__dma_remap(page, size, prot);
		ptr = page_address(page);
	पूर्ण

 out:
	*ret_page = page;
	वापस ptr;
पूर्ण

अटल व्योम __मुक्त_from_contiguous(काष्ठा device *dev, काष्ठा page *page,
				   व्योम *cpu_addr, माप_प्रकार size, bool want_vaddr)
अणु
	अगर (want_vaddr) अणु
		अगर (PageHighMem(page))
			dma_common_मुक्त_remap(cpu_addr, size);
		अन्यथा
			__dma_remap(page, size, PAGE_KERNEL);
	पूर्ण
	dma_release_from_contiguous(dev, page, size >> PAGE_SHIFT);
पूर्ण

अटल अंतरभूत pgprot_t __get_dma_pgprot(अचिन्हित दीर्घ attrs, pgprot_t prot)
अणु
	prot = (attrs & DMA_ATTR_WRITE_COMBINE) ?
			pgprot_ग_लिखोcombine(prot) :
			pgprot_dmacoherent(prot);
	वापस prot;
पूर्ण

अटल व्योम *__alloc_simple_buffer(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp,
				   काष्ठा page **ret_page)
अणु
	काष्ठा page *page;
	/* __alloc_simple_buffer is only called when the device is coherent */
	page = __dma_alloc_buffer(dev, size, gfp, COHERENT);
	अगर (!page)
		वापस शून्य;

	*ret_page = page;
	वापस page_address(page);
पूर्ण

अटल व्योम *simple_allocator_alloc(काष्ठा arm_dma_alloc_args *args,
				    काष्ठा page **ret_page)
अणु
	वापस __alloc_simple_buffer(args->dev, args->size, args->gfp,
				     ret_page);
पूर्ण

अटल व्योम simple_allocator_मुक्त(काष्ठा arm_dma_मुक्त_args *args)
अणु
	__dma_मुक्त_buffer(args->page, args->size);
पूर्ण

अटल काष्ठा arm_dma_allocator simple_allocator = अणु
	.alloc = simple_allocator_alloc,
	.मुक्त = simple_allocator_मुक्त,
पूर्ण;

अटल व्योम *cma_allocator_alloc(काष्ठा arm_dma_alloc_args *args,
				 काष्ठा page **ret_page)
अणु
	वापस __alloc_from_contiguous(args->dev, args->size, args->prot,
				       ret_page, args->caller,
				       args->want_vaddr, args->coherent_flag,
				       args->gfp);
पूर्ण

अटल व्योम cma_allocator_मुक्त(काष्ठा arm_dma_मुक्त_args *args)
अणु
	__मुक्त_from_contiguous(args->dev, args->page, args->cpu_addr,
			       args->size, args->want_vaddr);
पूर्ण

अटल काष्ठा arm_dma_allocator cma_allocator = अणु
	.alloc = cma_allocator_alloc,
	.मुक्त = cma_allocator_मुक्त,
पूर्ण;

अटल व्योम *pool_allocator_alloc(काष्ठा arm_dma_alloc_args *args,
				  काष्ठा page **ret_page)
अणु
	वापस __alloc_from_pool(args->size, ret_page);
पूर्ण

अटल व्योम pool_allocator_मुक्त(काष्ठा arm_dma_मुक्त_args *args)
अणु
	__मुक्त_from_pool(args->cpu_addr, args->size);
पूर्ण

अटल काष्ठा arm_dma_allocator pool_allocator = अणु
	.alloc = pool_allocator_alloc,
	.मुक्त = pool_allocator_मुक्त,
पूर्ण;

अटल व्योम *remap_allocator_alloc(काष्ठा arm_dma_alloc_args *args,
				   काष्ठा page **ret_page)
अणु
	वापस __alloc_remap_buffer(args->dev, args->size, args->gfp,
				    args->prot, ret_page, args->caller,
				    args->want_vaddr);
पूर्ण

अटल व्योम remap_allocator_मुक्त(काष्ठा arm_dma_मुक्त_args *args)
अणु
	अगर (args->want_vaddr)
		dma_common_मुक्त_remap(args->cpu_addr, args->size);

	__dma_मुक्त_buffer(args->page, args->size);
पूर्ण

अटल काष्ठा arm_dma_allocator remap_allocator = अणु
	.alloc = remap_allocator_alloc,
	.मुक्त = remap_allocator_मुक्त,
पूर्ण;

अटल व्योम *__dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *handle,
			 gfp_t gfp, pgprot_t prot, bool is_coherent,
			 अचिन्हित दीर्घ attrs, स्थिर व्योम *caller)
अणु
	u64 mask = min_not_zero(dev->coherent_dma_mask, dev->bus_dma_limit);
	काष्ठा page *page = शून्य;
	व्योम *addr;
	bool allowblock, cma;
	काष्ठा arm_dma_buffer *buf;
	काष्ठा arm_dma_alloc_args args = अणु
		.dev = dev,
		.size = PAGE_ALIGN(size),
		.gfp = gfp,
		.prot = prot,
		.caller = caller,
		.want_vaddr = ((attrs & DMA_ATTR_NO_KERNEL_MAPPING) == 0),
		.coherent_flag = is_coherent ? COHERENT : NORMAL,
	पूर्ण;

#अगर_घोषित CONFIG_DMA_API_DEBUG
	u64 limit = (mask + 1) & ~mask;
	अगर (limit && size >= limit) अणु
		dev_warn(dev, "coherent allocation too big (requested %#x mask %#llx)\n",
			size, mask);
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर

	buf = kzalloc(माप(*buf),
		      gfp & ~(__GFP_DMA | __GFP_DMA32 | __GFP_HIGHMEM));
	अगर (!buf)
		वापस शून्य;

	अगर (mask < 0xffffffffULL)
		gfp |= GFP_DMA;

	/*
	 * Following is a work-around (a.k.a. hack) to prevent pages
	 * with __GFP_COMP being passed to split_page() which cannot
	 * handle them.  The real problem is that this flag probably
	 * should be 0 on ARM as it is not supported on this
	 * platक्रमm; see CONFIG_HUGETLBFS.
	 */
	gfp &= ~(__GFP_COMP);
	args.gfp = gfp;

	*handle = DMA_MAPPING_ERROR;
	allowblock = gfpflags_allow_blocking(gfp);
	cma = allowblock ? dev_get_cma_area(dev) : false;

	अगर (cma)
		buf->allocator = &cma_allocator;
	अन्यथा अगर (is_coherent)
		buf->allocator = &simple_allocator;
	अन्यथा अगर (allowblock)
		buf->allocator = &remap_allocator;
	अन्यथा
		buf->allocator = &pool_allocator;

	addr = buf->allocator->alloc(&args, &page);

	अगर (page) अणु
		अचिन्हित दीर्घ flags;

		*handle = pfn_to_dma(dev, page_to_pfn(page));
		buf->virt = args.want_vaddr ? addr : page;

		spin_lock_irqsave(&arm_dma_bufs_lock, flags);
		list_add(&buf->list, &arm_dma_bufs);
		spin_unlock_irqrestore(&arm_dma_bufs_lock, flags);
	पूर्ण अन्यथा अणु
		kमुक्त(buf);
	पूर्ण

	वापस args.want_vaddr ? addr : page;
पूर्ण

/*
 * Allocate DMA-coherent memory space and वापस both the kernel remapped
 * भव and bus address क्रम that space.
 */
व्योम *arm_dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *handle,
		    gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	pgprot_t prot = __get_dma_pgprot(attrs, PAGE_KERNEL);

	वापस __dma_alloc(dev, size, handle, gfp, prot, false,
			   attrs, __builtin_वापस_address(0));
पूर्ण

अटल व्योम *arm_coherent_dma_alloc(काष्ठा device *dev, माप_प्रकार size,
	dma_addr_t *handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	वापस __dma_alloc(dev, size, handle, gfp, PAGE_KERNEL, true,
			   attrs, __builtin_वापस_address(0));
पूर्ण

अटल पूर्णांक __arm_dma_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		 व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		 अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक ret = -ENXIO;
	अचिन्हित दीर्घ nr_vma_pages = vma_pages(vma);
	अचिन्हित दीर्घ nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	अचिन्हित दीर्घ pfn = dma_to_pfn(dev, dma_addr);
	अचिन्हित दीर्घ off = vma->vm_pgoff;

	अगर (dma_mmap_from_dev_coherent(dev, vma, cpu_addr, size, &ret))
		वापस ret;

	अगर (off < nr_pages && nr_vma_pages <= (nr_pages - off)) अणु
		ret = remap_pfn_range(vma, vma->vm_start,
				      pfn + off,
				      vma->vm_end - vma->vm_start,
				      vma->vm_page_prot);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Create userspace mapping क्रम the DMA-coherent memory.
 */
अटल पूर्णांक arm_coherent_dma_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		 व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		 अचिन्हित दीर्घ attrs)
अणु
	वापस __arm_dma_mmap(dev, vma, cpu_addr, dma_addr, size, attrs);
पूर्ण

पूर्णांक arm_dma_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		 व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		 अचिन्हित दीर्घ attrs)
अणु
	vma->vm_page_prot = __get_dma_pgprot(attrs, vma->vm_page_prot);
	वापस __arm_dma_mmap(dev, vma, cpu_addr, dma_addr, size, attrs);
पूर्ण

/*
 * Free a buffer as defined by the above mapping.
 */
अटल व्योम __arm_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
			   dma_addr_t handle, अचिन्हित दीर्घ attrs,
			   bool is_coherent)
अणु
	काष्ठा page *page = pfn_to_page(dma_to_pfn(dev, handle));
	काष्ठा arm_dma_buffer *buf;
	काष्ठा arm_dma_मुक्त_args args = अणु
		.dev = dev,
		.size = PAGE_ALIGN(size),
		.cpu_addr = cpu_addr,
		.page = page,
		.want_vaddr = ((attrs & DMA_ATTR_NO_KERNEL_MAPPING) == 0),
	पूर्ण;

	buf = arm_dma_buffer_find(cpu_addr);
	अगर (WARN(!buf, "Freeing invalid buffer %p\n", cpu_addr))
		वापस;

	buf->allocator->मुक्त(&args);
	kमुक्त(buf);
पूर्ण

व्योम arm_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		  dma_addr_t handle, अचिन्हित दीर्घ attrs)
अणु
	__arm_dma_मुक्त(dev, size, cpu_addr, handle, attrs, false);
पूर्ण

अटल व्योम arm_coherent_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
				  dma_addr_t handle, अचिन्हित दीर्घ attrs)
अणु
	__arm_dma_मुक्त(dev, size, cpu_addr, handle, attrs, true);
पूर्ण

पूर्णांक arm_dma_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		 व्योम *cpu_addr, dma_addr_t handle, माप_प्रकार size,
		 अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ pfn = dma_to_pfn(dev, handle);
	काष्ठा page *page;
	पूर्णांक ret;

	/* If the PFN is not valid, we करो not have a काष्ठा page */
	अगर (!pfn_valid(pfn))
		वापस -ENXIO;

	page = pfn_to_page(pfn);

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
	अगर (unlikely(ret))
		वापस ret;

	sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	वापस 0;
पूर्ण

अटल व्योम dma_cache_मुख्यt_page(काष्ठा page *page, अचिन्हित दीर्घ offset,
	माप_प्रकार size, क्रमागत dma_data_direction dir,
	व्योम (*op)(स्थिर व्योम *, माप_प्रकार, पूर्णांक))
अणु
	अचिन्हित दीर्घ pfn;
	माप_प्रकार left = size;

	pfn = page_to_pfn(page) + offset / PAGE_SIZE;
	offset %= PAGE_SIZE;

	/*
	 * A single sg entry may refer to multiple physically contiguous
	 * pages.  But we still need to process highmem pages inभागidually.
	 * If highmem is not configured then the bulk of this loop माला_लो
	 * optimized out.
	 */
	करो अणु
		माप_प्रकार len = left;
		व्योम *vaddr;

		page = pfn_to_page(pfn);

		अगर (PageHighMem(page)) अणु
			अगर (len + offset > PAGE_SIZE)
				len = PAGE_SIZE - offset;

			अगर (cache_is_vipt_nonaliasing()) अणु
				vaddr = kmap_atomic(page);
				op(vaddr + offset, len, dir);
				kunmap_atomic(vaddr);
			पूर्ण अन्यथा अणु
				vaddr = kmap_high_get(page);
				अगर (vaddr) अणु
					op(vaddr + offset, len, dir);
					kunmap_high(page);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			vaddr = page_address(page) + offset;
			op(vaddr, len, dir);
		पूर्ण
		offset = 0;
		pfn++;
		left -= len;
	पूर्ण जबतक (left);
पूर्ण

/*
 * Make an area consistent क्रम devices.
 * Note: Drivers should NOT use this function directly, as it will अवरोध
 * platक्रमms with CONFIG_DMABOUNCE.
 * Use the driver DMA support - see dma-mapping.h (dma_sync_*)
 */
अटल व्योम __dma_page_cpu_to_dev(काष्ठा page *page, अचिन्हित दीर्घ off,
	माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t paddr;

	dma_cache_मुख्यt_page(page, off, size, dir, dmac_map_area);

	paddr = page_to_phys(page) + off;
	अगर (dir == DMA_FROM_DEVICE) अणु
		outer_inv_range(paddr, paddr + size);
	पूर्ण अन्यथा अणु
		outer_clean_range(paddr, paddr + size);
	पूर्ण
	/* FIXME: non-speculating: flush on bidirectional mappings? */
पूर्ण

अटल व्योम __dma_page_dev_to_cpu(काष्ठा page *page, अचिन्हित दीर्घ off,
	माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	phys_addr_t paddr = page_to_phys(page) + off;

	/* FIXME: non-speculating: not required */
	/* in any हाल, करोn't bother invalidating अगर DMA to device */
	अगर (dir != DMA_TO_DEVICE) अणु
		outer_inv_range(paddr, paddr + size);

		dma_cache_मुख्यt_page(page, off, size, dir, dmac_unmap_area);
	पूर्ण

	/*
	 * Mark the D-cache clean क्रम these pages to aव्योम extra flushing.
	 */
	अगर (dir != DMA_TO_DEVICE && size >= PAGE_SIZE) अणु
		अचिन्हित दीर्घ pfn;
		माप_प्रकार left = size;

		pfn = page_to_pfn(page) + off / PAGE_SIZE;
		off %= PAGE_SIZE;
		अगर (off) अणु
			pfn++;
			left -= PAGE_SIZE - off;
		पूर्ण
		जबतक (left >= PAGE_SIZE) अणु
			page = pfn_to_page(pfn++);
			set_bit(PG_dcache_clean, &page->flags);
			left -= PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * arm_dma_map_sg - map a set of SG buffers क्रम streaming mode DMA
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @sg: list of buffers
 * @nents: number of buffers to map
 * @dir: DMA transfer direction
 *
 * Map a set of buffers described by scatterlist in streaming mode क्रम DMA.
 * This is the scatter-gather version of the dma_map_single पूर्णांकerface.
 * Here the scatter gather list elements are each tagged with the
 * appropriate dma address and length.  They are obtained via
 * sg_dma_अणुaddress,lengthपूर्ण.
 *
 * Device ownership issues as mentioned क्रम dma_map_single are the same
 * here.
 */
पूर्णांक arm_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	काष्ठा scatterlist *s;
	पूर्णांक i, j;

	क्रम_each_sg(sg, s, nents, i) अणु
#अगर_घोषित CONFIG_NEED_SG_DMA_LENGTH
		s->dma_length = s->length;
#पूर्ण_अगर
		s->dma_address = ops->map_page(dev, sg_page(s), s->offset,
						s->length, dir, attrs);
		अगर (dma_mapping_error(dev, s->dma_address))
			जाओ bad_mapping;
	पूर्ण
	वापस nents;

 bad_mapping:
	क्रम_each_sg(sg, s, i, j)
		ops->unmap_page(dev, sg_dma_address(s), sg_dma_len(s), dir, attrs);
	वापस 0;
पूर्ण

/**
 * arm_dma_unmap_sg - unmap a set of SG buffers mapped by dma_map_sg
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @sg: list of buffers
 * @nents: number of buffers to unmap (same as was passed to dma_map_sg)
 * @dir: DMA transfer direction (same as was passed to dma_map_sg)
 *
 * Unmap a set of streaming mode DMA translations.  Again, CPU access
 * rules concerning calls here are the same as क्रम dma_unmap_single().
 */
व्योम arm_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	काष्ठा scatterlist *s;

	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i)
		ops->unmap_page(dev, sg_dma_address(s), sg_dma_len(s), dir, attrs);
पूर्ण

/**
 * arm_dma_sync_sg_क्रम_cpu
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @sg: list of buffers
 * @nents: number of buffers to map (वापसed from dma_map_sg)
 * @dir: DMA transfer direction (same as was passed to dma_map_sg)
 */
व्योम arm_dma_sync_sg_क्रम_cpu(काष्ठा device *dev, काष्ठा scatterlist *sg,
			पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i)
		ops->sync_single_क्रम_cpu(dev, sg_dma_address(s), s->length,
					 dir);
पूर्ण

/**
 * arm_dma_sync_sg_क्रम_device
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @sg: list of buffers
 * @nents: number of buffers to map (वापसed from dma_map_sg)
 * @dir: DMA transfer direction (same as was passed to dma_map_sg)
 */
व्योम arm_dma_sync_sg_क्रम_device(काष्ठा device *dev, काष्ठा scatterlist *sg,
			पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i)
		ops->sync_single_क्रम_device(dev, sg_dma_address(s), s->length,
					    dir);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops *arm_get_dma_map_ops(bool coherent)
अणु
	/*
	 * When CONFIG_ARM_LPAE is set, physical address can extend above
	 * 32-bits, which then can't be addressed by devices that only support
	 * 32-bit DMA.
	 * Use the generic dma-direct / swiotlb ops code in that हाल, as that
	 * handles bounce buffering क्रम us.
	 */
	अगर (IS_ENABLED(CONFIG_ARM_LPAE))
		वापस शून्य;
	वापस coherent ? &arm_coherent_dma_ops : &arm_dma_ops;
पूर्ण

#अगर_घोषित CONFIG_ARM_DMA_USE_IOMMU

अटल पूर्णांक __dma_info_to_prot(क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक prot = 0;

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
		वापस prot;
	पूर्ण
पूर्ण

/* IOMMU */

अटल पूर्णांक extend_iommu_mapping(काष्ठा dma_iommu_mapping *mapping);

अटल अंतरभूत dma_addr_t __alloc_iova(काष्ठा dma_iommu_mapping *mapping,
				      माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	अचिन्हित पूर्णांक align = 0;
	अचिन्हित पूर्णांक count, start;
	माप_प्रकार mapping_size = mapping->bits << PAGE_SHIFT;
	अचिन्हित दीर्घ flags;
	dma_addr_t iova;
	पूर्णांक i;

	अगर (order > CONFIG_ARM_DMA_IOMMU_ALIGNMENT)
		order = CONFIG_ARM_DMA_IOMMU_ALIGNMENT;

	count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	align = (1 << order) - 1;

	spin_lock_irqsave(&mapping->lock, flags);
	क्रम (i = 0; i < mapping->nr_biपंचांगaps; i++) अणु
		start = biपंचांगap_find_next_zero_area(mapping->biपंचांगaps[i],
				mapping->bits, 0, count, align);

		अगर (start > mapping->bits)
			जारी;

		biपंचांगap_set(mapping->biपंचांगaps[i], start, count);
		अवरोध;
	पूर्ण

	/*
	 * No unused range found. Try to extend the existing mapping
	 * and perक्रमm a second attempt to reserve an IO भव
	 * address range of size bytes.
	 */
	अगर (i == mapping->nr_biपंचांगaps) अणु
		अगर (extend_iommu_mapping(mapping)) अणु
			spin_unlock_irqrestore(&mapping->lock, flags);
			वापस DMA_MAPPING_ERROR;
		पूर्ण

		start = biपंचांगap_find_next_zero_area(mapping->biपंचांगaps[i],
				mapping->bits, 0, count, align);

		अगर (start > mapping->bits) अणु
			spin_unlock_irqrestore(&mapping->lock, flags);
			वापस DMA_MAPPING_ERROR;
		पूर्ण

		biपंचांगap_set(mapping->biपंचांगaps[i], start, count);
	पूर्ण
	spin_unlock_irqrestore(&mapping->lock, flags);

	iova = mapping->base + (mapping_size * i);
	iova += start << PAGE_SHIFT;

	वापस iova;
पूर्ण

अटल अंतरभूत व्योम __मुक्त_iova(काष्ठा dma_iommu_mapping *mapping,
			       dma_addr_t addr, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक start, count;
	माप_प्रकार mapping_size = mapping->bits << PAGE_SHIFT;
	अचिन्हित दीर्घ flags;
	dma_addr_t biपंचांगap_base;
	u32 biपंचांगap_index;

	अगर (!size)
		वापस;

	biपंचांगap_index = (u32) (addr - mapping->base) / (u32) mapping_size;
	BUG_ON(addr < mapping->base || biपंचांगap_index > mapping->extensions);

	biपंचांगap_base = mapping->base + mapping_size * biपंचांगap_index;

	start = (addr - biपंचांगap_base) >>	PAGE_SHIFT;

	अगर (addr + size > biपंचांगap_base + mapping_size) अणु
		/*
		 * The address range to be मुक्तd reaches पूर्णांकo the iova
		 * range of the next biपंचांगap. This should not happen as
		 * we करोn't allow this in __alloc_iova (at the
		 * moment).
		 */
		BUG();
	पूर्ण अन्यथा
		count = size >> PAGE_SHIFT;

	spin_lock_irqsave(&mapping->lock, flags);
	biपंचांगap_clear(mapping->biपंचांगaps[biपंचांगap_index], start, count);
	spin_unlock_irqrestore(&mapping->lock, flags);
पूर्ण

/* We'll try 2M, 1M, 64K, and finally 4K; array must end with 0! */
अटल स्थिर पूर्णांक iommu_order_array[] = अणु 9, 8, 4, 0 पूर्ण;

अटल काष्ठा page **__iommu_alloc_buffer(काष्ठा device *dev, माप_प्रकार size,
					  gfp_t gfp, अचिन्हित दीर्घ attrs,
					  पूर्णांक coherent_flag)
अणु
	काष्ठा page **pages;
	पूर्णांक count = size >> PAGE_SHIFT;
	पूर्णांक array_size = count * माप(काष्ठा page *);
	पूर्णांक i = 0;
	पूर्णांक order_idx = 0;

	अगर (array_size <= PAGE_SIZE)
		pages = kzalloc(array_size, GFP_KERNEL);
	अन्यथा
		pages = vzalloc(array_size);
	अगर (!pages)
		वापस शून्य;

	अगर (attrs & DMA_ATTR_FORCE_CONTIGUOUS)
	अणु
		अचिन्हित दीर्घ order = get_order(size);
		काष्ठा page *page;

		page = dma_alloc_from_contiguous(dev, count, order,
						 gfp & __GFP_NOWARN);
		अगर (!page)
			जाओ error;

		__dma_clear_buffer(page, size, coherent_flag);

		क्रम (i = 0; i < count; i++)
			pages[i] = page + i;

		वापस pages;
	पूर्ण

	/* Go straight to 4K chunks अगर caller says it's OK. */
	अगर (attrs & DMA_ATTR_ALLOC_SINGLE_PAGES)
		order_idx = ARRAY_SIZE(iommu_order_array) - 1;

	/*
	 * IOMMU can map any pages, so himem can also be used here
	 */
	gfp |= __GFP_NOWARN | __GFP_HIGHMEM;

	जबतक (count) अणु
		पूर्णांक j, order;

		order = iommu_order_array[order_idx];

		/* Drop करोwn when we get small */
		अगर (__fls(count) < order) अणु
			order_idx++;
			जारी;
		पूर्ण

		अगर (order) अणु
			/* See अगर it's easy to allocate a high-order chunk */
			pages[i] = alloc_pages(gfp | __GFP_NORETRY, order);

			/* Go करोwn a notch at first sign of pressure */
			अगर (!pages[i]) अणु
				order_idx++;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			pages[i] = alloc_pages(gfp, 0);
			अगर (!pages[i])
				जाओ error;
		पूर्ण

		अगर (order) अणु
			split_page(pages[i], order);
			j = 1 << order;
			जबतक (--j)
				pages[i + j] = pages[i] + j;
		पूर्ण

		__dma_clear_buffer(pages[i], PAGE_SIZE << order, coherent_flag);
		i += 1 << order;
		count -= 1 << order;
	पूर्ण

	वापस pages;
error:
	जबतक (i--)
		अगर (pages[i])
			__मुक्त_pages(pages[i], 0);
	kvमुक्त(pages);
	वापस शून्य;
पूर्ण

अटल पूर्णांक __iommu_मुक्त_buffer(काष्ठा device *dev, काष्ठा page **pages,
			       माप_प्रकार size, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक count = size >> PAGE_SHIFT;
	पूर्णांक i;

	अगर (attrs & DMA_ATTR_FORCE_CONTIGUOUS) अणु
		dma_release_from_contiguous(dev, pages[0], count);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < count; i++)
			अगर (pages[i])
				__मुक्त_pages(pages[i], 0);
	पूर्ण

	kvमुक्त(pages);
	वापस 0;
पूर्ण

/*
 * Create a mapping in device IO address space क्रम specअगरied pages
 */
अटल dma_addr_t
__iommu_create_mapping(काष्ठा device *dev, काष्ठा page **pages, माप_प्रकार size,
		       अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	अचिन्हित पूर्णांक count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	dma_addr_t dma_addr, iova;
	पूर्णांक i;

	dma_addr = __alloc_iova(mapping, size);
	अगर (dma_addr == DMA_MAPPING_ERROR)
		वापस dma_addr;

	iova = dma_addr;
	क्रम (i = 0; i < count; ) अणु
		पूर्णांक ret;

		अचिन्हित पूर्णांक next_pfn = page_to_pfn(pages[i]) + 1;
		phys_addr_t phys = page_to_phys(pages[i]);
		अचिन्हित पूर्णांक len, j;

		क्रम (j = i + 1; j < count; j++, next_pfn++)
			अगर (page_to_pfn(pages[j]) != next_pfn)
				अवरोध;

		len = (j - i) << PAGE_SHIFT;
		ret = iommu_map(mapping->करोमुख्य, iova, phys, len,
				__dma_info_to_prot(DMA_BIसूचीECTIONAL, attrs));
		अगर (ret < 0)
			जाओ fail;
		iova += len;
		i = j;
	पूर्ण
	वापस dma_addr;
fail:
	iommu_unmap(mapping->करोमुख्य, dma_addr, iova-dma_addr);
	__मुक्त_iova(mapping, dma_addr, size);
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल पूर्णांक __iommu_हटाओ_mapping(काष्ठा device *dev, dma_addr_t iova, माप_प्रकार size)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);

	/*
	 * add optional in-page offset from iova to size and align
	 * result to page size
	 */
	size = PAGE_ALIGN((iova & ~PAGE_MASK) + size);
	iova &= PAGE_MASK;

	iommu_unmap(mapping->करोमुख्य, iova, size);
	__मुक्त_iova(mapping, iova, size);
	वापस 0;
पूर्ण

अटल काष्ठा page **__atomic_get_pages(व्योम *addr)
अणु
	काष्ठा page *page;
	phys_addr_t phys;

	phys = gen_pool_virt_to_phys(atomic_pool, (अचिन्हित दीर्घ)addr);
	page = phys_to_page(phys);

	वापस (काष्ठा page **)page;
पूर्ण

अटल काष्ठा page **__iommu_get_pages(व्योम *cpu_addr, अचिन्हित दीर्घ attrs)
अणु
	अगर (__in_atomic_pool(cpu_addr, PAGE_SIZE))
		वापस __atomic_get_pages(cpu_addr);

	अगर (attrs & DMA_ATTR_NO_KERNEL_MAPPING)
		वापस cpu_addr;

	वापस dma_common_find_pages(cpu_addr);
पूर्ण

अटल व्योम *__iommu_alloc_simple(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp,
				  dma_addr_t *handle, पूर्णांक coherent_flag,
				  अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page *page;
	व्योम *addr;

	अगर (coherent_flag  == COHERENT)
		addr = __alloc_simple_buffer(dev, size, gfp, &page);
	अन्यथा
		addr = __alloc_from_pool(size, &page);
	अगर (!addr)
		वापस शून्य;

	*handle = __iommu_create_mapping(dev, &page, size, attrs);
	अगर (*handle == DMA_MAPPING_ERROR)
		जाओ err_mapping;

	वापस addr;

err_mapping:
	__मुक्त_from_pool(addr, size);
	वापस शून्य;
पूर्ण

अटल व्योम __iommu_मुक्त_atomic(काष्ठा device *dev, व्योम *cpu_addr,
			dma_addr_t handle, माप_प्रकार size, पूर्णांक coherent_flag)
अणु
	__iommu_हटाओ_mapping(dev, handle, size);
	अगर (coherent_flag == COHERENT)
		__dma_मुक्त_buffer(virt_to_page(cpu_addr), size);
	अन्यथा
		__मुक्त_from_pool(cpu_addr, size);
पूर्ण

अटल व्योम *__arm_iommu_alloc_attrs(काष्ठा device *dev, माप_प्रकार size,
	    dma_addr_t *handle, gfp_t gfp, अचिन्हित दीर्घ attrs,
	    पूर्णांक coherent_flag)
अणु
	pgprot_t prot = __get_dma_pgprot(attrs, PAGE_KERNEL);
	काष्ठा page **pages;
	व्योम *addr = शून्य;

	*handle = DMA_MAPPING_ERROR;
	size = PAGE_ALIGN(size);

	अगर (coherent_flag  == COHERENT || !gfpflags_allow_blocking(gfp))
		वापस __iommu_alloc_simple(dev, size, gfp, handle,
					    coherent_flag, attrs);

	/*
	 * Following is a work-around (a.k.a. hack) to prevent pages
	 * with __GFP_COMP being passed to split_page() which cannot
	 * handle them.  The real problem is that this flag probably
	 * should be 0 on ARM as it is not supported on this
	 * platक्रमm; see CONFIG_HUGETLBFS.
	 */
	gfp &= ~(__GFP_COMP);

	pages = __iommu_alloc_buffer(dev, size, gfp, attrs, coherent_flag);
	अगर (!pages)
		वापस शून्य;

	*handle = __iommu_create_mapping(dev, pages, size, attrs);
	अगर (*handle == DMA_MAPPING_ERROR)
		जाओ err_buffer;

	अगर (attrs & DMA_ATTR_NO_KERNEL_MAPPING)
		वापस pages;

	addr = dma_common_pages_remap(pages, size, prot,
				   __builtin_वापस_address(0));
	अगर (!addr)
		जाओ err_mapping;

	वापस addr;

err_mapping:
	__iommu_हटाओ_mapping(dev, *handle, size);
err_buffer:
	__iommu_मुक्त_buffer(dev, pages, size, attrs);
	वापस शून्य;
पूर्ण

अटल व्योम *arm_iommu_alloc_attrs(काष्ठा device *dev, माप_प्रकार size,
	    dma_addr_t *handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	वापस __arm_iommu_alloc_attrs(dev, size, handle, gfp, attrs, NORMAL);
पूर्ण

अटल व्योम *arm_coherent_iommu_alloc_attrs(काष्ठा device *dev, माप_प्रकार size,
		    dma_addr_t *handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	वापस __arm_iommu_alloc_attrs(dev, size, handle, gfp, attrs, COHERENT);
पूर्ण

अटल पूर्णांक __arm_iommu_mmap_attrs(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		    व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page **pages = __iommu_get_pages(cpu_addr, attrs);
	अचिन्हित दीर्घ nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	पूर्णांक err;

	अगर (!pages)
		वापस -ENXIO;

	अगर (vma->vm_pgoff >= nr_pages)
		वापस -ENXIO;

	err = vm_map_pages(vma, pages, nr_pages);
	अगर (err)
		pr_err("Remapping memory failed: %d\n", err);

	वापस err;
पूर्ण
अटल पूर्णांक arm_iommu_mmap_attrs(काष्ठा device *dev,
		काष्ठा vm_area_काष्ठा *vma, व्योम *cpu_addr,
		dma_addr_t dma_addr, माप_प्रकार size, अचिन्हित दीर्घ attrs)
अणु
	vma->vm_page_prot = __get_dma_pgprot(attrs, vma->vm_page_prot);

	वापस __arm_iommu_mmap_attrs(dev, vma, cpu_addr, dma_addr, size, attrs);
पूर्ण

अटल पूर्णांक arm_coherent_iommu_mmap_attrs(काष्ठा device *dev,
		काष्ठा vm_area_काष्ठा *vma, व्योम *cpu_addr,
		dma_addr_t dma_addr, माप_प्रकार size, अचिन्हित दीर्घ attrs)
अणु
	वापस __arm_iommu_mmap_attrs(dev, vma, cpu_addr, dma_addr, size, attrs);
पूर्ण

/*
 * मुक्त a page as defined by the above mapping.
 * Must not be called with IRQs disabled.
 */
अटल व्योम __arm_iommu_मुक्त_attrs(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
	dma_addr_t handle, अचिन्हित दीर्घ attrs, पूर्णांक coherent_flag)
अणु
	काष्ठा page **pages;
	size = PAGE_ALIGN(size);

	अगर (coherent_flag == COHERENT || __in_atomic_pool(cpu_addr, size)) अणु
		__iommu_मुक्त_atomic(dev, cpu_addr, handle, size, coherent_flag);
		वापस;
	पूर्ण

	pages = __iommu_get_pages(cpu_addr, attrs);
	अगर (!pages) अणु
		WARN(1, "trying to free invalid coherent area: %p\n", cpu_addr);
		वापस;
	पूर्ण

	अगर ((attrs & DMA_ATTR_NO_KERNEL_MAPPING) == 0)
		dma_common_मुक्त_remap(cpu_addr, size);

	__iommu_हटाओ_mapping(dev, handle, size);
	__iommu_मुक्त_buffer(dev, pages, size, attrs);
पूर्ण

अटल व्योम arm_iommu_मुक्त_attrs(काष्ठा device *dev, माप_प्रकार size,
				 व्योम *cpu_addr, dma_addr_t handle,
				 अचिन्हित दीर्घ attrs)
अणु
	__arm_iommu_मुक्त_attrs(dev, size, cpu_addr, handle, attrs, NORMAL);
पूर्ण

अटल व्योम arm_coherent_iommu_मुक्त_attrs(काष्ठा device *dev, माप_प्रकार size,
		    व्योम *cpu_addr, dma_addr_t handle, अचिन्हित दीर्घ attrs)
अणु
	__arm_iommu_मुक्त_attrs(dev, size, cpu_addr, handle, attrs, COHERENT);
पूर्ण

अटल पूर्णांक arm_iommu_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
				 व्योम *cpu_addr, dma_addr_t dma_addr,
				 माप_प्रकार size, अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित पूर्णांक count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	काष्ठा page **pages = __iommu_get_pages(cpu_addr, attrs);

	अगर (!pages)
		वापस -ENXIO;

	वापस sg_alloc_table_from_pages(sgt, pages, count, 0, size,
					 GFP_KERNEL);
पूर्ण

/*
 * Map a part of the scatter-gather list पूर्णांकo contiguous io address space
 */
अटल पूर्णांक __map_sg_chunk(काष्ठा device *dev, काष्ठा scatterlist *sg,
			  माप_प्रकार size, dma_addr_t *handle,
			  क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs,
			  bool is_coherent)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t iova, iova_base;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक count;
	काष्ठा scatterlist *s;
	पूर्णांक prot;

	size = PAGE_ALIGN(size);
	*handle = DMA_MAPPING_ERROR;

	iova_base = iova = __alloc_iova(mapping, size);
	अगर (iova == DMA_MAPPING_ERROR)
		वापस -ENOMEM;

	क्रम (count = 0, s = sg; count < (size >> PAGE_SHIFT); s = sg_next(s)) अणु
		phys_addr_t phys = page_to_phys(sg_page(s));
		अचिन्हित पूर्णांक len = PAGE_ALIGN(s->offset + s->length);

		अगर (!is_coherent && (attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
			__dma_page_cpu_to_dev(sg_page(s), s->offset, s->length, dir);

		prot = __dma_info_to_prot(dir, attrs);

		ret = iommu_map(mapping->करोमुख्य, iova, phys, len, prot);
		अगर (ret < 0)
			जाओ fail;
		count += len >> PAGE_SHIFT;
		iova += len;
	पूर्ण
	*handle = iova_base;

	वापस 0;
fail:
	iommu_unmap(mapping->करोमुख्य, iova_base, count * PAGE_SIZE);
	__मुक्त_iova(mapping, iova_base, size);
	वापस ret;
पूर्ण

अटल पूर्णांक __iommu_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		     क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs,
		     bool is_coherent)
अणु
	काष्ठा scatterlist *s = sg, *dma = sg, *start = sg;
	पूर्णांक i, count = 0;
	अचिन्हित पूर्णांक offset = s->offset;
	अचिन्हित पूर्णांक size = s->offset + s->length;
	अचिन्हित पूर्णांक max = dma_get_max_seg_size(dev);

	क्रम (i = 1; i < nents; i++) अणु
		s = sg_next(s);

		s->dma_address = DMA_MAPPING_ERROR;
		s->dma_length = 0;

		अगर (s->offset || (size & ~PAGE_MASK) || size + s->length > max) अणु
			अगर (__map_sg_chunk(dev, start, size, &dma->dma_address,
			    dir, attrs, is_coherent) < 0)
				जाओ bad_mapping;

			dma->dma_address += offset;
			dma->dma_length = size - offset;

			size = offset = s->offset;
			start = s;
			dma = sg_next(dma);
			count += 1;
		पूर्ण
		size += s->length;
	पूर्ण
	अगर (__map_sg_chunk(dev, start, size, &dma->dma_address, dir, attrs,
		is_coherent) < 0)
		जाओ bad_mapping;

	dma->dma_address += offset;
	dma->dma_length = size - offset;

	वापस count+1;

bad_mapping:
	क्रम_each_sg(sg, s, count, i)
		__iommu_हटाओ_mapping(dev, sg_dma_address(s), sg_dma_len(s));
	वापस 0;
पूर्ण

/**
 * arm_coherent_iommu_map_sg - map a set of SG buffers क्रम streaming mode DMA
 * @dev: valid काष्ठा device poपूर्णांकer
 * @sg: list of buffers
 * @nents: number of buffers to map
 * @dir: DMA transfer direction
 *
 * Map a set of i/o coherent buffers described by scatterlist in streaming
 * mode क्रम DMA. The scatter gather list elements are merged together (अगर
 * possible) and tagged with the appropriate dma address and length. They are
 * obtained via sg_dma_अणुaddress,lengthपूर्ण.
 */
अटल पूर्णांक arm_coherent_iommu_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस __iommu_map_sg(dev, sg, nents, dir, attrs, true);
पूर्ण

/**
 * arm_iommu_map_sg - map a set of SG buffers क्रम streaming mode DMA
 * @dev: valid काष्ठा device poपूर्णांकer
 * @sg: list of buffers
 * @nents: number of buffers to map
 * @dir: DMA transfer direction
 *
 * Map a set of buffers described by scatterlist in streaming mode क्रम DMA.
 * The scatter gather list elements are merged together (अगर possible) and
 * tagged with the appropriate dma address and length. They are obtained via
 * sg_dma_अणुaddress,lengthपूर्ण.
 */
अटल पूर्णांक arm_iommu_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस __iommu_map_sg(dev, sg, nents, dir, attrs, false);
पूर्ण

अटल व्योम __iommu_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs, bool is_coherent)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i) अणु
		अगर (sg_dma_len(s))
			__iommu_हटाओ_mapping(dev, sg_dma_address(s),
					       sg_dma_len(s));
		अगर (!is_coherent && (attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
			__dma_page_dev_to_cpu(sg_page(s), s->offset,
					      s->length, dir);
	पूर्ण
पूर्ण

/**
 * arm_coherent_iommu_unmap_sg - unmap a set of SG buffers mapped by dma_map_sg
 * @dev: valid काष्ठा device poपूर्णांकer
 * @sg: list of buffers
 * @nents: number of buffers to unmap (same as was passed to dma_map_sg)
 * @dir: DMA transfer direction (same as was passed to dma_map_sg)
 *
 * Unmap a set of streaming mode DMA translations.  Again, CPU access
 * rules concerning calls here are the same as क्रम dma_unmap_single().
 */
अटल व्योम arm_coherent_iommu_unmap_sg(काष्ठा device *dev,
		काष्ठा scatterlist *sg, पूर्णांक nents, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	__iommu_unmap_sg(dev, sg, nents, dir, attrs, true);
पूर्ण

/**
 * arm_iommu_unmap_sg - unmap a set of SG buffers mapped by dma_map_sg
 * @dev: valid काष्ठा device poपूर्णांकer
 * @sg: list of buffers
 * @nents: number of buffers to unmap (same as was passed to dma_map_sg)
 * @dir: DMA transfer direction (same as was passed to dma_map_sg)
 *
 * Unmap a set of streaming mode DMA translations.  Again, CPU access
 * rules concerning calls here are the same as क्रम dma_unmap_single().
 */
अटल व्योम arm_iommu_unmap_sg(काष्ठा device *dev,
			       काष्ठा scatterlist *sg, पूर्णांक nents,
			       क्रमागत dma_data_direction dir,
			       अचिन्हित दीर्घ attrs)
अणु
	__iommu_unmap_sg(dev, sg, nents, dir, attrs, false);
पूर्ण

/**
 * arm_iommu_sync_sg_क्रम_cpu
 * @dev: valid काष्ठा device poपूर्णांकer
 * @sg: list of buffers
 * @nents: number of buffers to map (वापसed from dma_map_sg)
 * @dir: DMA transfer direction (same as was passed to dma_map_sg)
 */
अटल व्योम arm_iommu_sync_sg_क्रम_cpu(काष्ठा device *dev,
			काष्ठा scatterlist *sg,
			पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i)
		__dma_page_dev_to_cpu(sg_page(s), s->offset, s->length, dir);

पूर्ण

/**
 * arm_iommu_sync_sg_क्रम_device
 * @dev: valid काष्ठा device poपूर्णांकer
 * @sg: list of buffers
 * @nents: number of buffers to map (वापसed from dma_map_sg)
 * @dir: DMA transfer direction (same as was passed to dma_map_sg)
 */
अटल व्योम arm_iommu_sync_sg_क्रम_device(काष्ठा device *dev,
			काष्ठा scatterlist *sg,
			पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i)
		__dma_page_cpu_to_dev(sg_page(s), s->offset, s->length, dir);
पूर्ण


/**
 * arm_coherent_iommu_map_page
 * @dev: valid काष्ठा device poपूर्णांकer
 * @page: page that buffer resides in
 * @offset: offset पूर्णांकo page क्रम start of buffer
 * @size: size of buffer to map
 * @dir: DMA transfer direction
 *
 * Coherent IOMMU aware version of arm_dma_map_page()
 */
अटल dma_addr_t arm_coherent_iommu_map_page(काष्ठा device *dev, काष्ठा page *page,
	     अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
	     अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t dma_addr;
	पूर्णांक ret, prot, len = PAGE_ALIGN(size + offset);

	dma_addr = __alloc_iova(mapping, len);
	अगर (dma_addr == DMA_MAPPING_ERROR)
		वापस dma_addr;

	prot = __dma_info_to_prot(dir, attrs);

	ret = iommu_map(mapping->करोमुख्य, dma_addr, page_to_phys(page), len, prot);
	अगर (ret < 0)
		जाओ fail;

	वापस dma_addr + offset;
fail:
	__मुक्त_iova(mapping, dma_addr, len);
	वापस DMA_MAPPING_ERROR;
पूर्ण

/**
 * arm_iommu_map_page
 * @dev: valid काष्ठा device poपूर्णांकer
 * @page: page that buffer resides in
 * @offset: offset पूर्णांकo page क्रम start of buffer
 * @size: size of buffer to map
 * @dir: DMA transfer direction
 *
 * IOMMU aware version of arm_dma_map_page()
 */
अटल dma_addr_t arm_iommu_map_page(काष्ठा device *dev, काष्ठा page *page,
	     अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
	     अचिन्हित दीर्घ attrs)
अणु
	अगर ((attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
		__dma_page_cpu_to_dev(page, offset, size, dir);

	वापस arm_coherent_iommu_map_page(dev, page, offset, size, dir, attrs);
पूर्ण

/**
 * arm_coherent_iommu_unmap_page
 * @dev: valid काष्ठा device poपूर्णांकer
 * @handle: DMA address of buffer
 * @size: size of buffer (same as passed to dma_map_page)
 * @dir: DMA transfer direction (same as passed to dma_map_page)
 *
 * Coherent IOMMU aware version of arm_dma_unmap_page()
 */
अटल व्योम arm_coherent_iommu_unmap_page(काष्ठा device *dev, dma_addr_t handle,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t iova = handle & PAGE_MASK;
	पूर्णांक offset = handle & ~PAGE_MASK;
	पूर्णांक len = PAGE_ALIGN(size + offset);

	अगर (!iova)
		वापस;

	iommu_unmap(mapping->करोमुख्य, iova, len);
	__मुक्त_iova(mapping, iova, len);
पूर्ण

/**
 * arm_iommu_unmap_page
 * @dev: valid काष्ठा device poपूर्णांकer
 * @handle: DMA address of buffer
 * @size: size of buffer (same as passed to dma_map_page)
 * @dir: DMA transfer direction (same as passed to dma_map_page)
 *
 * IOMMU aware version of arm_dma_unmap_page()
 */
अटल व्योम arm_iommu_unmap_page(काष्ठा device *dev, dma_addr_t handle,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t iova = handle & PAGE_MASK;
	काष्ठा page *page = phys_to_page(iommu_iova_to_phys(mapping->करोमुख्य, iova));
	पूर्णांक offset = handle & ~PAGE_MASK;
	पूर्णांक len = PAGE_ALIGN(size + offset);

	अगर (!iova)
		वापस;

	अगर ((attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
		__dma_page_dev_to_cpu(page, offset, size, dir);

	iommu_unmap(mapping->करोमुख्य, iova, len);
	__मुक्त_iova(mapping, iova, len);
पूर्ण

/**
 * arm_iommu_map_resource - map a device resource क्रम DMA
 * @dev: valid काष्ठा device poपूर्णांकer
 * @phys_addr: physical address of resource
 * @size: size of resource to map
 * @dir: DMA transfer direction
 */
अटल dma_addr_t arm_iommu_map_resource(काष्ठा device *dev,
		phys_addr_t phys_addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t dma_addr;
	पूर्णांक ret, prot;
	phys_addr_t addr = phys_addr & PAGE_MASK;
	अचिन्हित पूर्णांक offset = phys_addr & ~PAGE_MASK;
	माप_प्रकार len = PAGE_ALIGN(size + offset);

	dma_addr = __alloc_iova(mapping, len);
	अगर (dma_addr == DMA_MAPPING_ERROR)
		वापस dma_addr;

	prot = __dma_info_to_prot(dir, attrs) | IOMMU_MMIO;

	ret = iommu_map(mapping->करोमुख्य, dma_addr, addr, len, prot);
	अगर (ret < 0)
		जाओ fail;

	वापस dma_addr + offset;
fail:
	__मुक्त_iova(mapping, dma_addr, len);
	वापस DMA_MAPPING_ERROR;
पूर्ण

/**
 * arm_iommu_unmap_resource - unmap a device DMA resource
 * @dev: valid काष्ठा device poपूर्णांकer
 * @dma_handle: DMA address to resource
 * @size: size of resource to map
 * @dir: DMA transfer direction
 */
अटल व्योम arm_iommu_unmap_resource(काष्ठा device *dev, dma_addr_t dma_handle,
		माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t iova = dma_handle & PAGE_MASK;
	अचिन्हित पूर्णांक offset = dma_handle & ~PAGE_MASK;
	माप_प्रकार len = PAGE_ALIGN(size + offset);

	अगर (!iova)
		वापस;

	iommu_unmap(mapping->करोमुख्य, iova, len);
	__मुक्त_iova(mapping, iova, len);
पूर्ण

अटल व्योम arm_iommu_sync_single_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t iova = handle & PAGE_MASK;
	काष्ठा page *page = phys_to_page(iommu_iova_to_phys(mapping->करोमुख्य, iova));
	अचिन्हित पूर्णांक offset = handle & ~PAGE_MASK;

	अगर (!iova)
		वापस;

	__dma_page_dev_to_cpu(page, offset, size, dir);
पूर्ण

अटल व्योम arm_iommu_sync_single_क्रम_device(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);
	dma_addr_t iova = handle & PAGE_MASK;
	काष्ठा page *page = phys_to_page(iommu_iova_to_phys(mapping->करोमुख्य, iova));
	अचिन्हित पूर्णांक offset = handle & ~PAGE_MASK;

	अगर (!iova)
		वापस;

	__dma_page_cpu_to_dev(page, offset, size, dir);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops iommu_ops = अणु
	.alloc		= arm_iommu_alloc_attrs,
	.मुक्त		= arm_iommu_मुक्त_attrs,
	.mmap		= arm_iommu_mmap_attrs,
	.get_sgtable	= arm_iommu_get_sgtable,

	.map_page		= arm_iommu_map_page,
	.unmap_page		= arm_iommu_unmap_page,
	.sync_single_क्रम_cpu	= arm_iommu_sync_single_क्रम_cpu,
	.sync_single_क्रम_device	= arm_iommu_sync_single_क्रम_device,

	.map_sg			= arm_iommu_map_sg,
	.unmap_sg		= arm_iommu_unmap_sg,
	.sync_sg_क्रम_cpu	= arm_iommu_sync_sg_क्रम_cpu,
	.sync_sg_क्रम_device	= arm_iommu_sync_sg_क्रम_device,

	.map_resource		= arm_iommu_map_resource,
	.unmap_resource		= arm_iommu_unmap_resource,

	.dma_supported		= arm_dma_supported,
पूर्ण;

अटल स्थिर काष्ठा dma_map_ops iommu_coherent_ops = अणु
	.alloc		= arm_coherent_iommu_alloc_attrs,
	.मुक्त		= arm_coherent_iommu_मुक्त_attrs,
	.mmap		= arm_coherent_iommu_mmap_attrs,
	.get_sgtable	= arm_iommu_get_sgtable,

	.map_page	= arm_coherent_iommu_map_page,
	.unmap_page	= arm_coherent_iommu_unmap_page,

	.map_sg		= arm_coherent_iommu_map_sg,
	.unmap_sg	= arm_coherent_iommu_unmap_sg,

	.map_resource	= arm_iommu_map_resource,
	.unmap_resource	= arm_iommu_unmap_resource,

	.dma_supported		= arm_dma_supported,
पूर्ण;

/**
 * arm_iommu_create_mapping
 * @bus: poपूर्णांकer to the bus holding the client device (क्रम IOMMU calls)
 * @base: start address of the valid IO address space
 * @size: maximum size of the valid IO address space
 *
 * Creates a mapping काष्ठाure which holds inक्रमmation about used/unused
 * IO address ranges, which is required to perक्रमm memory allocation and
 * mapping with IOMMU aware functions.
 *
 * The client device need to be attached to the mapping with
 * arm_iommu_attach_device function.
 */
काष्ठा dma_iommu_mapping *
arm_iommu_create_mapping(काष्ठा bus_type *bus, dma_addr_t base, u64 size)
अणु
	अचिन्हित पूर्णांक bits = size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक biपंचांगap_size = BITS_TO_LONGS(bits) * माप(दीर्घ);
	काष्ठा dma_iommu_mapping *mapping;
	पूर्णांक extensions = 1;
	पूर्णांक err = -ENOMEM;

	/* currently only 32-bit DMA address space is supported */
	अगर (size > DMA_BIT_MASK(32) + 1)
		वापस ERR_PTR(-दुस्फल);

	अगर (!biपंचांगap_size)
		वापस ERR_PTR(-EINVAL);

	अगर (biपंचांगap_size > PAGE_SIZE) अणु
		extensions = biपंचांगap_size / PAGE_SIZE;
		biपंचांगap_size = PAGE_SIZE;
	पूर्ण

	mapping = kzalloc(माप(काष्ठा dma_iommu_mapping), GFP_KERNEL);
	अगर (!mapping)
		जाओ err;

	mapping->biपंचांगap_size = biपंचांगap_size;
	mapping->biपंचांगaps = kसुस्मृति(extensions, माप(अचिन्हित दीर्घ *),
				   GFP_KERNEL);
	अगर (!mapping->biपंचांगaps)
		जाओ err2;

	mapping->biपंचांगaps[0] = kzalloc(biपंचांगap_size, GFP_KERNEL);
	अगर (!mapping->biपंचांगaps[0])
		जाओ err3;

	mapping->nr_biपंचांगaps = 1;
	mapping->extensions = extensions;
	mapping->base = base;
	mapping->bits = BITS_PER_BYTE * biपंचांगap_size;

	spin_lock_init(&mapping->lock);

	mapping->करोमुख्य = iommu_करोमुख्य_alloc(bus);
	अगर (!mapping->करोमुख्य)
		जाओ err4;

	kref_init(&mapping->kref);
	वापस mapping;
err4:
	kमुक्त(mapping->biपंचांगaps[0]);
err3:
	kमुक्त(mapping->biपंचांगaps);
err2:
	kमुक्त(mapping);
err:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(arm_iommu_create_mapping);

अटल व्योम release_iommu_mapping(काष्ठा kref *kref)
अणु
	पूर्णांक i;
	काष्ठा dma_iommu_mapping *mapping =
		container_of(kref, काष्ठा dma_iommu_mapping, kref);

	iommu_करोमुख्य_मुक्त(mapping->करोमुख्य);
	क्रम (i = 0; i < mapping->nr_biपंचांगaps; i++)
		kमुक्त(mapping->biपंचांगaps[i]);
	kमुक्त(mapping->biपंचांगaps);
	kमुक्त(mapping);
पूर्ण

अटल पूर्णांक extend_iommu_mapping(काष्ठा dma_iommu_mapping *mapping)
अणु
	पूर्णांक next_biपंचांगap;

	अगर (mapping->nr_biपंचांगaps >= mapping->extensions)
		वापस -EINVAL;

	next_biपंचांगap = mapping->nr_biपंचांगaps;
	mapping->biपंचांगaps[next_biपंचांगap] = kzalloc(mapping->biपंचांगap_size,
						GFP_ATOMIC);
	अगर (!mapping->biपंचांगaps[next_biपंचांगap])
		वापस -ENOMEM;

	mapping->nr_biपंचांगaps++;

	वापस 0;
पूर्ण

व्योम arm_iommu_release_mapping(काष्ठा dma_iommu_mapping *mapping)
अणु
	अगर (mapping)
		kref_put(&mapping->kref, release_iommu_mapping);
पूर्ण
EXPORT_SYMBOL_GPL(arm_iommu_release_mapping);

अटल पूर्णांक __arm_iommu_attach_device(काष्ठा device *dev,
				     काष्ठा dma_iommu_mapping *mapping)
अणु
	पूर्णांक err;

	err = iommu_attach_device(mapping->करोमुख्य, dev);
	अगर (err)
		वापस err;

	kref_get(&mapping->kref);
	to_dma_iommu_mapping(dev) = mapping;

	pr_debug("Attached IOMMU controller to %s device.\n", dev_name(dev));
	वापस 0;
पूर्ण

/**
 * arm_iommu_attach_device
 * @dev: valid काष्ठा device poपूर्णांकer
 * @mapping: io address space mapping काष्ठाure (वापसed from
 *	arm_iommu_create_mapping)
 *
 * Attaches specअगरied io address space mapping to the provided device.
 * This replaces the dma operations (dma_map_ops poपूर्णांकer) with the
 * IOMMU aware version.
 *
 * More than one client might be attached to the same io address space
 * mapping.
 */
पूर्णांक arm_iommu_attach_device(काष्ठा device *dev,
			    काष्ठा dma_iommu_mapping *mapping)
अणु
	पूर्णांक err;

	err = __arm_iommu_attach_device(dev, mapping);
	अगर (err)
		वापस err;

	set_dma_ops(dev, &iommu_ops);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arm_iommu_attach_device);

/**
 * arm_iommu_detach_device
 * @dev: valid काष्ठा device poपूर्णांकer
 *
 * Detaches the provided device from a previously attached map.
 * This overग_लिखोs the dma_ops poपूर्णांकer with appropriate non-IOMMU ops.
 */
व्योम arm_iommu_detach_device(काष्ठा device *dev)
अणु
	काष्ठा dma_iommu_mapping *mapping;

	mapping = to_dma_iommu_mapping(dev);
	अगर (!mapping) अणु
		dev_warn(dev, "Not attached\n");
		वापस;
	पूर्ण

	iommu_detach_device(mapping->करोमुख्य, dev);
	kref_put(&mapping->kref, release_iommu_mapping);
	to_dma_iommu_mapping(dev) = शून्य;
	set_dma_ops(dev, arm_get_dma_map_ops(dev->archdata.dma_coherent));

	pr_debug("Detached IOMMU controller from %s device.\n", dev_name(dev));
पूर्ण
EXPORT_SYMBOL_GPL(arm_iommu_detach_device);

अटल स्थिर काष्ठा dma_map_ops *arm_get_iommu_dma_map_ops(bool coherent)
अणु
	वापस coherent ? &iommu_coherent_ops : &iommu_ops;
पूर्ण

अटल bool arm_setup_iommu_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
				    स्थिर काष्ठा iommu_ops *iommu)
अणु
	काष्ठा dma_iommu_mapping *mapping;

	अगर (!iommu)
		वापस false;

	mapping = arm_iommu_create_mapping(dev->bus, dma_base, size);
	अगर (IS_ERR(mapping)) अणु
		pr_warn("Failed to create %llu-byte IOMMU mapping for device %s\n",
				size, dev_name(dev));
		वापस false;
	पूर्ण

	अगर (__arm_iommu_attach_device(dev, mapping)) अणु
		pr_warn("Failed to attached device %s to IOMMU_mapping\n",
				dev_name(dev));
		arm_iommu_release_mapping(mapping);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम arm_tearकरोwn_iommu_dma_ops(काष्ठा device *dev)
अणु
	काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);

	अगर (!mapping)
		वापस;

	arm_iommu_detach_device(dev);
	arm_iommu_release_mapping(mapping);
पूर्ण

#अन्यथा

अटल bool arm_setup_iommu_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
				    स्थिर काष्ठा iommu_ops *iommu)
अणु
	वापस false;
पूर्ण

अटल व्योम arm_tearकरोwn_iommu_dma_ops(काष्ठा device *dev) अणु पूर्ण

#घोषणा arm_get_iommu_dma_map_ops arm_get_dma_map_ops

#पूर्ण_अगर	/* CONFIG_ARM_DMA_USE_IOMMU */

व्योम arch_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
			स्थिर काष्ठा iommu_ops *iommu, bool coherent)
अणु
	स्थिर काष्ठा dma_map_ops *dma_ops;

	dev->archdata.dma_coherent = coherent;
#अगर_घोषित CONFIG_SWIOTLB
	dev->dma_coherent = coherent;
#पूर्ण_अगर

	/*
	 * Don't override the dma_ops अगर they have alपढ़ोy been set. Ideally
	 * this should be the only location where dma_ops are set, हटाओ this
	 * check when all other callers of set_dma_ops will have disappeared.
	 */
	अगर (dev->dma_ops)
		वापस;

	अगर (arm_setup_iommu_dma_ops(dev, dma_base, size, iommu))
		dma_ops = arm_get_iommu_dma_map_ops(coherent);
	अन्यथा
		dma_ops = arm_get_dma_map_ops(coherent);

	set_dma_ops(dev, dma_ops);

#अगर_घोषित CONFIG_XEN
	अगर (xen_initial_करोमुख्य())
		dev->dma_ops = &xen_swiotlb_dma_ops;
#पूर्ण_अगर
	dev->archdata.dma_ops_setup = true;
पूर्ण

व्योम arch_tearकरोwn_dma_ops(काष्ठा device *dev)
अणु
	अगर (!dev->archdata.dma_ops_setup)
		वापस;

	arm_tearकरोwn_iommu_dma_ops(dev);
	/* Let arch_setup_dma_ops() start again from scratch upon re-probe */
	set_dma_ops(dev, शून्य);
पूर्ण

#अगर_घोषित CONFIG_SWIOTLB
व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_page_cpu_to_dev(phys_to_page(paddr), paddr & (PAGE_SIZE - 1),
			      size, dir);
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_page_dev_to_cpu(phys_to_page(paddr), paddr & (PAGE_SIZE - 1),
			      size, dir);
पूर्ण

व्योम *arch_dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	वापस __dma_alloc(dev, size, dma_handle, gfp,
			   __get_dma_pgprot(attrs, PAGE_KERNEL), false,
			   attrs, __builtin_वापस_address(0));
पूर्ण

व्योम arch_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	__arm_dma_मुक्त(dev, size, cpu_addr, dma_handle, attrs, false);
पूर्ण
#पूर्ण_अगर /* CONFIG_SWIOTLB */
