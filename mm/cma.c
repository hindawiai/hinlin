<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Contiguous Memory Allocator
 *
 * Copyright (c) 2010-2011 by Samsung Electronics.
 * Copyright IBM Corporation, 2013
 * Copyright LG Electronics Inc., 2014
 * Written by:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *	Michal Nazarewicz <mina86@mina86.com>
 *	Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 *	Joonsoo Kim <iamjoonsoo.kim@lge.com>
 */

#घोषणा pr_fmt(fmt) "cma: " fmt

#अगर_घोषित CONFIG_CMA_DEBUG
#अगर_अघोषित DEBUG
#  define DEBUG
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा CREATE_TRACE_POINTS

#समावेश <linux/memblock.h>
#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>
#समावेश <linux/cma.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/kmemleak.h>
#समावेश <trace/events/cma.h>

#समावेश "cma.h"

काष्ठा cma cma_areas[MAX_CMA_AREAS];
अचिन्हित cma_area_count;

phys_addr_t cma_get_base(स्थिर काष्ठा cma *cma)
अणु
	वापस PFN_PHYS(cma->base_pfn);
पूर्ण

अचिन्हित दीर्घ cma_get_size(स्थिर काष्ठा cma *cma)
अणु
	वापस cma->count << PAGE_SHIFT;
पूर्ण

स्थिर अक्षर *cma_get_name(स्थिर काष्ठा cma *cma)
अणु
	वापस cma->name;
पूर्ण

अटल अचिन्हित दीर्घ cma_biपंचांगap_aligned_mask(स्थिर काष्ठा cma *cma,
					     अचिन्हित पूर्णांक align_order)
अणु
	अगर (align_order <= cma->order_per_bit)
		वापस 0;
	वापस (1UL << (align_order - cma->order_per_bit)) - 1;
पूर्ण

/*
 * Find the offset of the base PFN from the specअगरied align_order.
 * The value वापसed is represented in order_per_bits.
 */
अटल अचिन्हित दीर्घ cma_biपंचांगap_aligned_offset(स्थिर काष्ठा cma *cma,
					       अचिन्हित पूर्णांक align_order)
अणु
	वापस (cma->base_pfn & ((1UL << align_order) - 1))
		>> cma->order_per_bit;
पूर्ण

अटल अचिन्हित दीर्घ cma_biपंचांगap_pages_to_bits(स्थिर काष्ठा cma *cma,
					      अचिन्हित दीर्घ pages)
अणु
	वापस ALIGN(pages, 1UL << cma->order_per_bit) >> cma->order_per_bit;
पूर्ण

अटल व्योम cma_clear_biपंचांगap(काष्ठा cma *cma, अचिन्हित दीर्घ pfn,
			     अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ biपंचांगap_no, biपंचांगap_count;
	अचिन्हित दीर्घ flags;

	biपंचांगap_no = (pfn - cma->base_pfn) >> cma->order_per_bit;
	biपंचांगap_count = cma_biपंचांगap_pages_to_bits(cma, count);

	spin_lock_irqsave(&cma->lock, flags);
	biपंचांगap_clear(cma->biपंचांगap, biपंचांगap_no, biपंचांगap_count);
	spin_unlock_irqrestore(&cma->lock, flags);
पूर्ण

अटल व्योम __init cma_activate_area(काष्ठा cma *cma)
अणु
	अचिन्हित दीर्घ base_pfn = cma->base_pfn, pfn;
	काष्ठा zone *zone;

	cma->biपंचांगap = biपंचांगap_zalloc(cma_biपंचांगap_maxno(cma), GFP_KERNEL);
	अगर (!cma->biपंचांगap)
		जाओ out_error;

	/*
	 * alloc_contig_range() requires the pfn range specअगरied to be in the
	 * same zone. Simplअगरy by क्रमcing the entire CMA resv range to be in the
	 * same zone.
	 */
	WARN_ON_ONCE(!pfn_valid(base_pfn));
	zone = page_zone(pfn_to_page(base_pfn));
	क्रम (pfn = base_pfn + 1; pfn < base_pfn + cma->count; pfn++) अणु
		WARN_ON_ONCE(!pfn_valid(pfn));
		अगर (page_zone(pfn_to_page(pfn)) != zone)
			जाओ not_in_zone;
	पूर्ण

	क्रम (pfn = base_pfn; pfn < base_pfn + cma->count;
	     pfn += pageblock_nr_pages)
		init_cma_reserved_pageblock(pfn_to_page(pfn));

	spin_lock_init(&cma->lock);

#अगर_घोषित CONFIG_CMA_DEBUGFS
	INIT_HLIST_HEAD(&cma->mem_head);
	spin_lock_init(&cma->mem_head_lock);
#पूर्ण_अगर

	वापस;

not_in_zone:
	biपंचांगap_मुक्त(cma->biपंचांगap);
out_error:
	/* Expose all pages to the buddy, they are useless क्रम CMA. */
	क्रम (pfn = base_pfn; pfn < base_pfn + cma->count; pfn++)
		मुक्त_reserved_page(pfn_to_page(pfn));
	totalcma_pages -= cma->count;
	cma->count = 0;
	pr_err("CMA area %s could not be activated\n", cma->name);
	वापस;
पूर्ण

अटल पूर्णांक __init cma_init_reserved_areas(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cma_area_count; i++)
		cma_activate_area(&cma_areas[i]);

	वापस 0;
पूर्ण
core_initcall(cma_init_reserved_areas);

/**
 * cma_init_reserved_mem() - create custom contiguous area from reserved memory
 * @base: Base address of the reserved area
 * @size: Size of the reserved area (in bytes),
 * @order_per_bit: Order of pages represented by one bit on biपंचांगap.
 * @name: The name of the area. If this parameter is शून्य, the name of
 *        the area will be set to "cmaN", where N is a running counter of
 *        used areas.
 * @res_cma: Poपूर्णांकer to store the created cma region.
 *
 * This function creates custom contiguous area from alपढ़ोy reserved memory.
 */
पूर्णांक __init cma_init_reserved_mem(phys_addr_t base, phys_addr_t size,
				 अचिन्हित पूर्णांक order_per_bit,
				 स्थिर अक्षर *name,
				 काष्ठा cma **res_cma)
अणु
	काष्ठा cma *cma;
	phys_addr_t alignment;

	/* Sanity checks */
	अगर (cma_area_count == ARRAY_SIZE(cma_areas)) अणु
		pr_err("Not enough slots for CMA reserved regions!\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (!size || !memblock_is_region_reserved(base, size))
		वापस -EINVAL;

	/* ensure minimal alignment required by mm core */
	alignment = PAGE_SIZE <<
			max_t(अचिन्हित दीर्घ, MAX_ORDER - 1, pageblock_order);

	/* alignment should be aligned with order_per_bit */
	अगर (!IS_ALIGNED(alignment >> PAGE_SHIFT, 1 << order_per_bit))
		वापस -EINVAL;

	अगर (ALIGN(base, alignment) != base || ALIGN(size, alignment) != size)
		वापस -EINVAL;

	/*
	 * Each reserved area must be initialised later, when more kernel
	 * subप्रणालीs (like slab allocator) are available.
	 */
	cma = &cma_areas[cma_area_count];

	अगर (name)
		snम_लिखो(cma->name, CMA_MAX_NAME, name);
	अन्यथा
		snम_लिखो(cma->name, CMA_MAX_NAME,  "cma%d\n", cma_area_count);

	cma->base_pfn = PFN_DOWN(base);
	cma->count = size >> PAGE_SHIFT;
	cma->order_per_bit = order_per_bit;
	*res_cma = cma;
	cma_area_count++;
	totalcma_pages += (size / PAGE_SIZE);

	वापस 0;
पूर्ण

/**
 * cma_declare_contiguous_nid() - reserve custom contiguous area
 * @base: Base address of the reserved area optional, use 0 क्रम any
 * @size: Size of the reserved area (in bytes),
 * @limit: End address of the reserved memory (optional, 0 क्रम any).
 * @alignment: Alignment क्रम the CMA area, should be घातer of 2 or zero
 * @order_per_bit: Order of pages represented by one bit on biपंचांगap.
 * @fixed: hपूर्णांक about where to place the reserved area
 * @name: The name of the area. See function cma_init_reserved_mem()
 * @res_cma: Poपूर्णांकer to store the created cma region.
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specअगरic code once the early allocator (memblock or booपंचांगem)
 * has been activated and all other subप्रणालीs have alपढ़ोy allocated/reserved
 * memory. This function allows to create custom reserved areas.
 *
 * If @fixed is true, reserve contiguous area at exactly @base.  If false,
 * reserve in range from @base to @limit.
 */
पूर्णांक __init cma_declare_contiguous_nid(phys_addr_t base,
			phys_addr_t size, phys_addr_t limit,
			phys_addr_t alignment, अचिन्हित पूर्णांक order_per_bit,
			bool fixed, स्थिर अक्षर *name, काष्ठा cma **res_cma,
			पूर्णांक nid)
अणु
	phys_addr_t memblock_end = memblock_end_of_DRAM();
	phys_addr_t highmem_start;
	पूर्णांक ret = 0;

	/*
	 * We can't use __pa(high_memory) directly, since high_memory
	 * isn't a valid direct map VA, and DEBUG_VIRTUAL will (validly)
	 * complain. Find the boundary by adding one to the last valid
	 * address.
	 */
	highmem_start = __pa(high_memory - 1) + 1;
	pr_debug("%s(size %pa, base %pa, limit %pa alignment %pa)\n",
		__func__, &size, &base, &limit, &alignment);

	अगर (cma_area_count == ARRAY_SIZE(cma_areas)) अणु
		pr_err("Not enough slots for CMA reserved regions!\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (!size)
		वापस -EINVAL;

	अगर (alignment && !is_घातer_of_2(alignment))
		वापस -EINVAL;

	/*
	 * Sanitise input arguments.
	 * Pages both ends in CMA area could be merged पूर्णांकo adjacent unmovable
	 * migratetype page by page allocator's buddy algorithm. In the हाल,
	 * you couldn't get a contiguous memory, which is not what we want.
	 */
	alignment = max(alignment,  (phys_addr_t)PAGE_SIZE <<
			  max_t(अचिन्हित दीर्घ, MAX_ORDER - 1, pageblock_order));
	अगर (fixed && base & (alignment - 1)) अणु
		ret = -EINVAL;
		pr_err("Region at %pa must be aligned to %pa bytes\n",
			&base, &alignment);
		जाओ err;
	पूर्ण
	base = ALIGN(base, alignment);
	size = ALIGN(size, alignment);
	limit &= ~(alignment - 1);

	अगर (!base)
		fixed = false;

	/* size should be aligned with order_per_bit */
	अगर (!IS_ALIGNED(size >> PAGE_SHIFT, 1 << order_per_bit))
		वापस -EINVAL;

	/*
	 * If allocating at a fixed base the request region must not cross the
	 * low/high memory boundary.
	 */
	अगर (fixed && base < highmem_start && base + size > highmem_start) अणु
		ret = -EINVAL;
		pr_err("Region at %pa defined on low/high memory boundary (%pa)\n",
			&base, &highmem_start);
		जाओ err;
	पूर्ण

	/*
	 * If the limit is unspecअगरied or above the memblock end, its effective
	 * value will be the memblock end. Set it explicitly to simplअगरy further
	 * checks.
	 */
	अगर (limit == 0 || limit > memblock_end)
		limit = memblock_end;

	अगर (base + size > limit) अणु
		ret = -EINVAL;
		pr_err("Size (%pa) of region at %pa exceeds limit (%pa)\n",
			&size, &base, &limit);
		जाओ err;
	पूर्ण

	/* Reserve memory */
	अगर (fixed) अणु
		अगर (memblock_is_region_reserved(base, size) ||
		    memblock_reserve(base, size) < 0) अणु
			ret = -EBUSY;
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		phys_addr_t addr = 0;

		/*
		 * All pages in the reserved area must come from the same zone.
		 * If the requested region crosses the low/high memory boundary,
		 * try allocating from high memory first and fall back to low
		 * memory in हाल of failure.
		 */
		अगर (base < highmem_start && limit > highmem_start) अणु
			addr = memblock_alloc_range_nid(size, alignment,
					highmem_start, limit, nid, true);
			limit = highmem_start;
		पूर्ण

		/*
		 * If there is enough memory, try a bottom-up allocation first.
		 * It will place the new cma area बंद to the start of the node
		 * and guarantee that the compaction is moving pages out of the
		 * cma area and not पूर्णांकo it.
		 * Aव्योम using first 4GB to not पूर्णांकerfere with स्थिरrained zones
		 * like DMA/DMA32.
		 */
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
		अगर (!memblock_bottom_up() && memblock_end >= SZ_4G + size) अणु
			memblock_set_bottom_up(true);
			addr = memblock_alloc_range_nid(size, alignment, SZ_4G,
							limit, nid, true);
			memblock_set_bottom_up(false);
		पूर्ण
#पूर्ण_अगर

		अगर (!addr) अणु
			addr = memblock_alloc_range_nid(size, alignment, base,
					limit, nid, true);
			अगर (!addr) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण
		पूर्ण

		/*
		 * kmemleak scans/पढ़ोs tracked objects क्रम poपूर्णांकers to other
		 * objects but this address isn't mapped and accessible
		 */
		kmemleak_ignore_phys(addr);
		base = addr;
	पूर्ण

	ret = cma_init_reserved_mem(base, size, order_per_bit, name, res_cma);
	अगर (ret)
		जाओ मुक्त_mem;

	pr_info("Reserved %ld MiB at %pa\n", (अचिन्हित दीर्घ)size / SZ_1M,
		&base);
	वापस 0;

मुक्त_mem:
	memblock_मुक्त(base, size);
err:
	pr_err("Failed to reserve %ld MiB\n", (अचिन्हित दीर्घ)size / SZ_1M);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_CMA_DEBUG
अटल व्योम cma_debug_show_areas(काष्ठा cma *cma)
अणु
	अचिन्हित दीर्घ next_zero_bit, next_set_bit, nr_zero;
	अचिन्हित दीर्घ start = 0;
	अचिन्हित दीर्घ nr_part, nr_total = 0;
	अचिन्हित दीर्घ nbits = cma_biपंचांगap_maxno(cma);

	spin_lock_irq(&cma->lock);
	pr_info("number of available pages: ");
	क्रम (;;) अणु
		next_zero_bit = find_next_zero_bit(cma->biपंचांगap, nbits, start);
		अगर (next_zero_bit >= nbits)
			अवरोध;
		next_set_bit = find_next_bit(cma->biपंचांगap, nbits, next_zero_bit);
		nr_zero = next_set_bit - next_zero_bit;
		nr_part = nr_zero << cma->order_per_bit;
		pr_cont("%s%lu@%lu", nr_total ? "+" : "", nr_part,
			next_zero_bit);
		nr_total += nr_part;
		start = next_zero_bit + nr_zero;
	पूर्ण
	pr_cont("=> %lu free of %lu total pages\n", nr_total, cma->count);
	spin_unlock_irq(&cma->lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cma_debug_show_areas(काष्ठा cma *cma) अणु पूर्ण
#पूर्ण_अगर

/**
 * cma_alloc() - allocate pages from contiguous area
 * @cma:   Contiguous memory region क्रम which the allocation is perक्रमmed.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).
 * @no_warn: Aव्योम prपूर्णांकing message about failed allocation
 *
 * This function allocates part of contiguous memory on specअगरic
 * contiguous memory area.
 */
काष्ठा page *cma_alloc(काष्ठा cma *cma, अचिन्हित दीर्घ count,
		       अचिन्हित पूर्णांक align, bool no_warn)
अणु
	अचिन्हित दीर्घ mask, offset;
	अचिन्हित दीर्घ pfn = -1;
	अचिन्हित दीर्घ start = 0;
	अचिन्हित दीर्घ biपंचांगap_maxno, biपंचांगap_no, biपंचांगap_count;
	अचिन्हित दीर्घ i;
	काष्ठा page *page = शून्य;
	पूर्णांक ret = -ENOMEM;

	अगर (!cma || !cma->count || !cma->biपंचांगap)
		जाओ out;

	pr_debug("%s(cma %p, count %lu, align %d)\n", __func__, (व्योम *)cma,
		 count, align);

	अगर (!count)
		जाओ out;

	trace_cma_alloc_start(cma->name, count, align);

	mask = cma_biपंचांगap_aligned_mask(cma, align);
	offset = cma_biपंचांगap_aligned_offset(cma, align);
	biपंचांगap_maxno = cma_biपंचांगap_maxno(cma);
	biपंचांगap_count = cma_biपंचांगap_pages_to_bits(cma, count);

	अगर (biपंचांगap_count > biपंचांगap_maxno)
		जाओ out;

	क्रम (;;) अणु
		spin_lock_irq(&cma->lock);
		biपंचांगap_no = biपंचांगap_find_next_zero_area_off(cma->biपंचांगap,
				biपंचांगap_maxno, start, biपंचांगap_count, mask,
				offset);
		अगर (biपंचांगap_no >= biपंचांगap_maxno) अणु
			spin_unlock_irq(&cma->lock);
			अवरोध;
		पूर्ण
		biपंचांगap_set(cma->biपंचांगap, biपंचांगap_no, biपंचांगap_count);
		/*
		 * It's safe to drop the lock here. We've marked this region क्रम
		 * our exclusive use. If the migration fails we will take the
		 * lock again and unmark it.
		 */
		spin_unlock_irq(&cma->lock);

		pfn = cma->base_pfn + (biपंचांगap_no << cma->order_per_bit);
		ret = alloc_contig_range(pfn, pfn + count, MIGRATE_CMA,
				     GFP_KERNEL | (no_warn ? __GFP_NOWARN : 0));

		अगर (ret == 0) अणु
			page = pfn_to_page(pfn);
			अवरोध;
		पूर्ण

		cma_clear_biपंचांगap(cma, pfn, count);
		अगर (ret != -EBUSY)
			अवरोध;

		pr_debug("%s(): memory range at %p is busy, retrying\n",
			 __func__, pfn_to_page(pfn));

		trace_cma_alloc_busy_retry(cma->name, pfn, pfn_to_page(pfn),
					   count, align);
		/* try again with a bit dअगरferent memory target */
		start = biपंचांगap_no + mask + 1;
	पूर्ण

	trace_cma_alloc_finish(cma->name, pfn, page, count, align);

	/*
	 * CMA can allocate multiple page blocks, which results in dअगरferent
	 * blocks being marked with dअगरferent tags. Reset the tags to ignore
	 * those page blocks.
	 */
	अगर (page) अणु
		क्रम (i = 0; i < count; i++)
			page_kasan_tag_reset(page + i);
	पूर्ण

	अगर (ret && !no_warn) अणु
		pr_err_ratelimited("%s: %s: alloc failed, req-size: %lu pages, ret: %d\n",
				   __func__, cma->name, count, ret);
		cma_debug_show_areas(cma);
	पूर्ण

	pr_debug("%s(): returned %p\n", __func__, page);
out:
	अगर (page) अणु
		count_vm_event(CMA_ALLOC_SUCCESS);
		cma_sysfs_account_success_pages(cma, count);
	पूर्ण अन्यथा अणु
		count_vm_event(CMA_ALLOC_FAIL);
		अगर (cma)
			cma_sysfs_account_fail_pages(cma, count);
	पूर्ण

	वापस page;
पूर्ण

/**
 * cma_release() - release allocated pages
 * @cma:   Contiguous memory region क्रम which the allocation is perक्रमmed.
 * @pages: Allocated pages.
 * @count: Number of allocated pages.
 *
 * This function releases memory allocated by cma_alloc().
 * It वापसs false when provided pages करो not beदीर्घ to contiguous area and
 * true otherwise.
 */
bool cma_release(काष्ठा cma *cma, स्थिर काष्ठा page *pages,
		 अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ pfn;

	अगर (!cma || !pages)
		वापस false;

	pr_debug("%s(page %p, count %lu)\n", __func__, (व्योम *)pages, count);

	pfn = page_to_pfn(pages);

	अगर (pfn < cma->base_pfn || pfn >= cma->base_pfn + cma->count)
		वापस false;

	VM_BUG_ON(pfn + count > cma->base_pfn + cma->count);

	मुक्त_contig_range(pfn, count);
	cma_clear_biपंचांगap(cma, pfn, count);
	trace_cma_release(cma->name, pfn, pages, count);

	वापस true;
पूर्ण

पूर्णांक cma_क्रम_each_area(पूर्णांक (*it)(काष्ठा cma *cma, व्योम *data), व्योम *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cma_area_count; i++) अणु
		पूर्णांक ret = it(&cma_areas[i], data);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
