<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Contiguous Memory Allocator क्रम DMA mapping framework
 * Copyright (c) 2010-2011 by Samsung Electronics.
 * Written by:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *	Michal Nazarewicz <mina86@mina86.com>
 *
 * Contiguous Memory Allocator
 *
 *   The Contiguous Memory Allocator (CMA) makes it possible to
 *   allocate big contiguous chunks of memory after the प्रणाली has
 *   booted.
 *
 * Why is it needed?
 *
 *   Various devices on embedded प्रणालीs have no scatter-getter and/or
 *   IO map support and require contiguous blocks of memory to
 *   operate.  They include devices such as cameras, hardware video
 *   coders, etc.
 *
 *   Such devices often require big memory buffers (a full HD frame
 *   is, क्रम instance, more than 2 mega pixels large, i.e. more than 6
 *   MB of memory), which makes mechanisms such as kदो_स्मृति() or
 *   alloc_page() ineffective.
 *
 *   At the same समय, a solution where a big memory region is
 *   reserved क्रम a device is suboptimal since often more memory is
 *   reserved then strictly required and, moreover, the memory is
 *   inaccessible to page प्रणाली even अगर device drivers करोn't use it.
 *
 *   CMA tries to solve this issue by operating on memory regions
 *   where only movable pages can be allocated from.  This way, kernel
 *   can use the memory क्रम pagecache and when device driver requests
 *   it, allocated pages can be migrated.
 */

#घोषणा pr_fmt(fmt) "cma: " fmt

#अगर_घोषित CONFIG_CMA_DEBUG
#अगर_अघोषित DEBUG
#  define DEBUG
#पूर्ण_अगर
#पूर्ण_अगर

#समावेश <यंत्र/page.h>

#समावेश <linux/memblock.h>
#समावेश <linux/err.h>
#समावेश <linux/sizes.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/cma.h>

#अगर_घोषित CONFIG_CMA_SIZE_MBYTES
#घोषणा CMA_SIZE_MBYTES CONFIG_CMA_SIZE_MBYTES
#अन्यथा
#घोषणा CMA_SIZE_MBYTES 0
#पूर्ण_अगर

काष्ठा cma *dma_contiguous_शेष_area;

/*
 * Default global CMA area size can be defined in kernel's .config.
 * This is useful मुख्यly क्रम distro मुख्यtainers to create a kernel
 * that works correctly क्रम most supported प्रणालीs.
 * The size can be set in bytes or as a percentage of the total memory
 * in the प्रणाली.
 *
 * Users, who want to set the size of global CMA area क्रम their प्रणाली
 * should use cma= kernel parameter.
 */
अटल स्थिर phys_addr_t size_bytes __initस्थिर =
	(phys_addr_t)CMA_SIZE_MBYTES * SZ_1M;
अटल phys_addr_t  size_cmdline __initdata = -1;
अटल phys_addr_t base_cmdline __initdata;
अटल phys_addr_t limit_cmdline __initdata;

अटल पूर्णांक __init early_cma(अक्षर *p)
अणु
	अगर (!p) अणु
		pr_err("Config string not provided\n");
		वापस -EINVAL;
	पूर्ण

	size_cmdline = memparse(p, &p);
	अगर (*p != '@')
		वापस 0;
	base_cmdline = memparse(p + 1, &p);
	अगर (*p != '-') अणु
		limit_cmdline = base_cmdline + size_cmdline;
		वापस 0;
	पूर्ण
	limit_cmdline = memparse(p + 1, &p);

	वापस 0;
पूर्ण
early_param("cma", early_cma);

#अगर_घोषित CONFIG_DMA_PERNUMA_CMA

अटल काष्ठा cma *dma_contiguous_pernuma_area[MAX_NUMNODES];
अटल phys_addr_t pernuma_size_bytes __initdata;

अटल पूर्णांक __init early_cma_pernuma(अक्षर *p)
अणु
	pernuma_size_bytes = memparse(p, &p);
	वापस 0;
पूर्ण
early_param("cma_pernuma", early_cma_pernuma);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CMA_SIZE_PERCENTAGE

अटल phys_addr_t __init __maybe_unused cma_early_percent_memory(व्योम)
अणु
	अचिन्हित दीर्घ total_pages = PHYS_PFN(memblock_phys_mem_size());

	वापस (total_pages * CONFIG_CMA_SIZE_PERCENTAGE / 100) << PAGE_SHIFT;
पूर्ण

#अन्यथा

अटल अंतरभूत __maybe_unused phys_addr_t cma_early_percent_memory(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_DMA_PERNUMA_CMA
व्योम __init dma_pernuma_cma_reserve(व्योम)
अणु
	पूर्णांक nid;

	अगर (!pernuma_size_bytes)
		वापस;

	क्रम_each_online_node(nid) अणु
		पूर्णांक ret;
		अक्षर name[CMA_MAX_NAME];
		काष्ठा cma **cma = &dma_contiguous_pernuma_area[nid];

		snम_लिखो(name, माप(name), "pernuma%d", nid);
		ret = cma_declare_contiguous_nid(0, pernuma_size_bytes, 0, 0,
						 0, false, name, cma, nid);
		अगर (ret) अणु
			pr_warn("%s: reservation failed: err %d, node %d", __func__,
				ret, nid);
			जारी;
		पूर्ण

		pr_debug("%s: reserved %llu MiB on node %d\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)pernuma_size_bytes / SZ_1M, nid);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * dma_contiguous_reserve() - reserve area(s) क्रम contiguous memory handling
 * @limit: End address of the reserved memory (optional, 0 क्रम any).
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specअगरic code once the early allocator (memblock or booपंचांगem)
 * has been activated and all other subप्रणालीs have alपढ़ोy allocated/reserved
 * memory.
 */
व्योम __init dma_contiguous_reserve(phys_addr_t limit)
अणु
	phys_addr_t selected_size = 0;
	phys_addr_t selected_base = 0;
	phys_addr_t selected_limit = limit;
	bool fixed = false;

	pr_debug("%s(limit %08lx)\n", __func__, (अचिन्हित दीर्घ)limit);

	अगर (size_cmdline != -1) अणु
		selected_size = size_cmdline;
		selected_base = base_cmdline;
		selected_limit = min_not_zero(limit_cmdline, limit);
		अगर (base_cmdline + size_cmdline == limit_cmdline)
			fixed = true;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_CMA_SIZE_SEL_MBYTES
		selected_size = size_bytes;
#या_अगर defined(CONFIG_CMA_SIZE_SEL_PERCENTAGE)
		selected_size = cma_early_percent_memory();
#या_अगर defined(CONFIG_CMA_SIZE_SEL_MIN)
		selected_size = min(size_bytes, cma_early_percent_memory());
#या_अगर defined(CONFIG_CMA_SIZE_SEL_MAX)
		selected_size = max(size_bytes, cma_early_percent_memory());
#पूर्ण_अगर
	पूर्ण

	अगर (selected_size && !dma_contiguous_शेष_area) अणु
		pr_debug("%s: reserving %ld MiB for global area\n", __func__,
			 (अचिन्हित दीर्घ)selected_size / SZ_1M);

		dma_contiguous_reserve_area(selected_size, selected_base,
					    selected_limit,
					    &dma_contiguous_शेष_area,
					    fixed);
	पूर्ण
पूर्ण

व्योम __weak
dma_contiguous_early_fixup(phys_addr_t base, अचिन्हित दीर्घ size)
अणु
पूर्ण

/**
 * dma_contiguous_reserve_area() - reserve custom contiguous area
 * @size: Size of the reserved area (in bytes),
 * @base: Base address of the reserved area optional, use 0 क्रम any
 * @limit: End address of the reserved memory (optional, 0 क्रम any).
 * @res_cma: Poपूर्णांकer to store the created cma region.
 * @fixed: hपूर्णांक about where to place the reserved area
 *
 * This function reserves memory from early allocator. It should be
 * called by arch specअगरic code once the early allocator (memblock or booपंचांगem)
 * has been activated and all other subप्रणालीs have alपढ़ोy allocated/reserved
 * memory. This function allows to create custom reserved areas क्रम specअगरic
 * devices.
 *
 * If @fixed is true, reserve contiguous area at exactly @base.  If false,
 * reserve in range from @base to @limit.
 */
पूर्णांक __init dma_contiguous_reserve_area(phys_addr_t size, phys_addr_t base,
				       phys_addr_t limit, काष्ठा cma **res_cma,
				       bool fixed)
अणु
	पूर्णांक ret;

	ret = cma_declare_contiguous(base, size, limit, 0, 0, fixed,
					"reserved", res_cma);
	अगर (ret)
		वापस ret;

	/* Architecture specअगरic contiguous memory fixup. */
	dma_contiguous_early_fixup(cma_get_base(*res_cma),
				cma_get_size(*res_cma));

	वापस 0;
पूर्ण

/**
 * dma_alloc_from_contiguous() - allocate pages from contiguous area
 * @dev:   Poपूर्णांकer to device क्रम which the allocation is perक्रमmed.
 * @count: Requested number of pages.
 * @align: Requested alignment of pages (in PAGE_SIZE order).
 * @no_warn: Aव्योम prपूर्णांकing message about failed allocation.
 *
 * This function allocates memory buffer क्रम specअगरied device. It uses
 * device specअगरic contiguous memory area अगर available or the शेष
 * global one. Requires architecture specअगरic dev_get_cma_area() helper
 * function.
 */
काष्ठा page *dma_alloc_from_contiguous(काष्ठा device *dev, माप_प्रकार count,
				       अचिन्हित पूर्णांक align, bool no_warn)
अणु
	अगर (align > CONFIG_CMA_ALIGNMENT)
		align = CONFIG_CMA_ALIGNMENT;

	वापस cma_alloc(dev_get_cma_area(dev), count, align, no_warn);
पूर्ण

/**
 * dma_release_from_contiguous() - release allocated pages
 * @dev:   Poपूर्णांकer to device क्रम which the pages were allocated.
 * @pages: Allocated pages.
 * @count: Number of allocated pages.
 *
 * This function releases memory allocated by dma_alloc_from_contiguous().
 * It वापसs false when provided pages करो not beदीर्घ to contiguous area and
 * true otherwise.
 */
bool dma_release_from_contiguous(काष्ठा device *dev, काष्ठा page *pages,
				 पूर्णांक count)
अणु
	वापस cma_release(dev_get_cma_area(dev), pages, count);
पूर्ण

अटल काष्ठा page *cma_alloc_aligned(काष्ठा cma *cma, माप_प्रकार size, gfp_t gfp)
अणु
	अचिन्हित पूर्णांक align = min(get_order(size), CONFIG_CMA_ALIGNMENT);

	वापस cma_alloc(cma, size >> PAGE_SHIFT, align, gfp & __GFP_NOWARN);
पूर्ण

/**
 * dma_alloc_contiguous() - allocate contiguous pages
 * @dev:   Poपूर्णांकer to device क्रम which the allocation is perक्रमmed.
 * @size:  Requested allocation size.
 * @gfp:   Allocation flags.
 *
 * tries to use device specअगरic contiguous memory area अगर available, or it
 * tries to use per-numa cma, अगर the allocation fails, it will fallback to
 * try शेष global one.
 *
 * Note that it bypass one-page size of allocations from the per-numa and
 * global area as the addresses within one page are always contiguous, so
 * there is no need to waste CMA pages क्रम that kind; it also helps reduce
 * fragmentations.
 */
काष्ठा page *dma_alloc_contiguous(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp)
अणु
#अगर_घोषित CONFIG_DMA_PERNUMA_CMA
	पूर्णांक nid = dev_to_node(dev);
#पूर्ण_अगर

	/* CMA can be used only in the context which permits sleeping */
	अगर (!gfpflags_allow_blocking(gfp))
		वापस शून्य;
	अगर (dev->cma_area)
		वापस cma_alloc_aligned(dev->cma_area, size, gfp);
	अगर (size <= PAGE_SIZE)
		वापस शून्य;

#अगर_घोषित CONFIG_DMA_PERNUMA_CMA
	अगर (nid != NUMA_NO_NODE && !(gfp & (GFP_DMA | GFP_DMA32))) अणु
		काष्ठा cma *cma = dma_contiguous_pernuma_area[nid];
		काष्ठा page *page;

		अगर (cma) अणु
			page = cma_alloc_aligned(cma, size, gfp);
			अगर (page)
				वापस page;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (!dma_contiguous_शेष_area)
		वापस शून्य;

	वापस cma_alloc_aligned(dma_contiguous_शेष_area, size, gfp);
पूर्ण

/**
 * dma_मुक्त_contiguous() - release allocated pages
 * @dev:   Poपूर्णांकer to device क्रम which the pages were allocated.
 * @page:  Poपूर्णांकer to the allocated pages.
 * @size:  Size of allocated pages.
 *
 * This function releases memory allocated by dma_alloc_contiguous(). As the
 * cma_release वापसs false when provided pages करो not beदीर्घ to contiguous
 * area and true otherwise, this function then करोes a fallback __मुक्त_pages()
 * upon a false-वापस.
 */
व्योम dma_मुक्त_contiguous(काष्ठा device *dev, काष्ठा page *page, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक count = PAGE_ALIGN(size) >> PAGE_SHIFT;

	/* अगर dev has its own cma, मुक्त page from there */
	अगर (dev->cma_area) अणु
		अगर (cma_release(dev->cma_area, page, count))
			वापस;
	पूर्ण अन्यथा अणु
		/*
		 * otherwise, page is from either per-numa cma or शेष cma
		 */
#अगर_घोषित CONFIG_DMA_PERNUMA_CMA
		अगर (cma_release(dma_contiguous_pernuma_area[page_to_nid(page)],
					page, count))
			वापस;
#पूर्ण_अगर
		अगर (cma_release(dma_contiguous_शेष_area, page, count))
			वापस;
	पूर्ण

	/* not in any cma, मुक्त from buddy */
	__मुक्त_pages(page, get_order(size));
पूर्ण

/*
 * Support क्रम reserved memory regions defined in device tree
 */
#अगर_घोषित CONFIG_OF_RESERVED_MEM
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_reserved_स्मृति.स>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) fmt

अटल पूर्णांक rmem_cma_device_init(काष्ठा reserved_mem *rmem, काष्ठा device *dev)
अणु
	dev->cma_area = rmem->priv;
	वापस 0;
पूर्ण

अटल व्योम rmem_cma_device_release(काष्ठा reserved_mem *rmem,
				    काष्ठा device *dev)
अणु
	dev->cma_area = शून्य;
पूर्ण

अटल स्थिर काष्ठा reserved_mem_ops rmem_cma_ops = अणु
	.device_init	= rmem_cma_device_init,
	.device_release = rmem_cma_device_release,
पूर्ण;

अटल पूर्णांक __init rmem_cma_setup(काष्ठा reserved_mem *rmem)
अणु
	phys_addr_t align = PAGE_SIZE << max(MAX_ORDER - 1, pageblock_order);
	phys_addr_t mask = align - 1;
	अचिन्हित दीर्घ node = rmem->fdt_node;
	bool शेष_cma = of_get_flat_dt_prop(node, "linux,cma-default", शून्य);
	काष्ठा cma *cma;
	पूर्णांक err;

	अगर (size_cmdline != -1 && शेष_cma) अणु
		pr_info("Reserved memory: bypass %s node, using cmdline CMA params instead\n",
			rmem->name);
		वापस -EBUSY;
	पूर्ण

	अगर (!of_get_flat_dt_prop(node, "reusable", शून्य) ||
	    of_get_flat_dt_prop(node, "no-map", शून्य))
		वापस -EINVAL;

	अगर ((rmem->base & mask) || (rmem->size & mask)) अणु
		pr_err("Reserved memory: incorrect alignment of CMA region\n");
		वापस -EINVAL;
	पूर्ण

	err = cma_init_reserved_mem(rmem->base, rmem->size, 0, rmem->name, &cma);
	अगर (err) अणु
		pr_err("Reserved memory: unable to setup CMA region\n");
		वापस err;
	पूर्ण
	/* Architecture specअगरic contiguous memory fixup. */
	dma_contiguous_early_fixup(rmem->base, rmem->size);

	अगर (शेष_cma)
		dma_contiguous_शेष_area = cma;

	rmem->ops = &rmem_cma_ops;
	rmem->priv = cma;

	pr_info("Reserved memory: created CMA memory pool at %pa, size %ld MiB\n",
		&rmem->base, (अचिन्हित दीर्घ)rmem->size / SZ_1M);

	वापस 0;
पूर्ण
RESERVEDMEM_OF_DECLARE(cma, "shared-dma-pool", rmem_cma_setup);
#पूर्ण_अगर
