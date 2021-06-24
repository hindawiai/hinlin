<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2020 Google LLC
 */
#समावेश <linux/cma.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/init.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/set_memory.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

अटल काष्ठा gen_pool *atomic_pool_dma __ro_after_init;
अटल अचिन्हित दीर्घ pool_size_dma;
अटल काष्ठा gen_pool *atomic_pool_dma32 __ro_after_init;
अटल अचिन्हित दीर्घ pool_size_dma32;
अटल काष्ठा gen_pool *atomic_pool_kernel __ro_after_init;
अटल अचिन्हित दीर्घ pool_size_kernel;

/* Size can be defined by the coherent_pool command line */
अटल माप_प्रकार atomic_pool_size;

/* Dynamic background expansion when the atomic pool is near capacity */
अटल काष्ठा work_काष्ठा atomic_pool_work;

अटल पूर्णांक __init early_coherent_pool(अक्षर *p)
अणु
	atomic_pool_size = memparse(p, &p);
	वापस 0;
पूर्ण
early_param("coherent_pool", early_coherent_pool);

अटल व्योम __init dma_atomic_pool_debugfs_init(व्योम)
अणु
	काष्ठा dentry *root;

	root = debugfs_create_dir("dma_pools", शून्य);
	debugfs_create_uदीर्घ("pool_size_dma", 0400, root, &pool_size_dma);
	debugfs_create_uदीर्घ("pool_size_dma32", 0400, root, &pool_size_dma32);
	debugfs_create_uदीर्घ("pool_size_kernel", 0400, root, &pool_size_kernel);
पूर्ण

अटल व्योम dma_atomic_pool_size_add(gfp_t gfp, माप_प्रकार size)
अणु
	अगर (gfp & __GFP_DMA)
		pool_size_dma += size;
	अन्यथा अगर (gfp & __GFP_DMA32)
		pool_size_dma32 += size;
	अन्यथा
		pool_size_kernel += size;
पूर्ण

अटल bool cma_in_zone(gfp_t gfp)
अणु
	अचिन्हित दीर्घ size;
	phys_addr_t end;
	काष्ठा cma *cma;

	cma = dev_get_cma_area(शून्य);
	अगर (!cma)
		वापस false;

	size = cma_get_size(cma);
	अगर (!size)
		वापस false;

	/* CMA can't cross zone boundaries, see cma_activate_area() */
	end = cma_get_base(cma) + size - 1;
	अगर (IS_ENABLED(CONFIG_ZONE_DMA) && (gfp & GFP_DMA))
		वापस end <= DMA_BIT_MASK(zone_dma_bits);
	अगर (IS_ENABLED(CONFIG_ZONE_DMA32) && (gfp & GFP_DMA32))
		वापस end <= DMA_BIT_MASK(32);
	वापस true;
पूर्ण

अटल पूर्णांक atomic_pool_expand(काष्ठा gen_pool *pool, माप_प्रकार pool_size,
			      gfp_t gfp)
अणु
	अचिन्हित पूर्णांक order;
	काष्ठा page *page = शून्य;
	व्योम *addr;
	पूर्णांक ret = -ENOMEM;

	/* Cannot allocate larger than MAX_ORDER-1 */
	order = min(get_order(pool_size), MAX_ORDER-1);

	करो अणु
		pool_size = 1 << (PAGE_SHIFT + order);
		अगर (cma_in_zone(gfp))
			page = dma_alloc_from_contiguous(शून्य, 1 << order,
							 order, false);
		अगर (!page)
			page = alloc_pages(gfp, order);
	पूर्ण जबतक (!page && order-- > 0);
	अगर (!page)
		जाओ out;

	arch_dma_prep_coherent(page, pool_size);

#अगर_घोषित CONFIG_DMA_सूचीECT_REMAP
	addr = dma_common_contiguous_remap(page, pool_size,
					   pgprot_dmacoherent(PAGE_KERNEL),
					   __builtin_वापस_address(0));
	अगर (!addr)
		जाओ मुक्त_page;
#अन्यथा
	addr = page_to_virt(page);
#पूर्ण_अगर
	/*
	 * Memory in the atomic DMA pools must be unencrypted, the pools करो not
	 * shrink so no re-encryption occurs in dma_direct_मुक्त().
	 */
	ret = set_memory_decrypted((अचिन्हित दीर्घ)page_to_virt(page),
				   1 << order);
	अगर (ret)
		जाओ हटाओ_mapping;
	ret = gen_pool_add_virt(pool, (अचिन्हित दीर्घ)addr, page_to_phys(page),
				pool_size, NUMA_NO_NODE);
	अगर (ret)
		जाओ encrypt_mapping;

	dma_atomic_pool_size_add(gfp, pool_size);
	वापस 0;

encrypt_mapping:
	ret = set_memory_encrypted((अचिन्हित दीर्घ)page_to_virt(page),
				   1 << order);
	अगर (WARN_ON_ONCE(ret)) अणु
		/* Decrypt succeeded but encrypt failed, purposely leak */
		जाओ out;
	पूर्ण
हटाओ_mapping:
#अगर_घोषित CONFIG_DMA_सूचीECT_REMAP
	dma_common_मुक्त_remap(addr, pool_size);
#पूर्ण_अगर
मुक्त_page: __maybe_unused
	__मुक्त_pages(page, order);
out:
	वापस ret;
पूर्ण

अटल व्योम atomic_pool_resize(काष्ठा gen_pool *pool, gfp_t gfp)
अणु
	अगर (pool && gen_pool_avail(pool) < atomic_pool_size)
		atomic_pool_expand(pool, gen_pool_size(pool), gfp);
पूर्ण

अटल व्योम atomic_pool_work_fn(काष्ठा work_काष्ठा *work)
अणु
	अगर (IS_ENABLED(CONFIG_ZONE_DMA))
		atomic_pool_resize(atomic_pool_dma,
				   GFP_KERNEL | GFP_DMA);
	अगर (IS_ENABLED(CONFIG_ZONE_DMA32))
		atomic_pool_resize(atomic_pool_dma32,
				   GFP_KERNEL | GFP_DMA32);
	atomic_pool_resize(atomic_pool_kernel, GFP_KERNEL);
पूर्ण

अटल __init काष्ठा gen_pool *__dma_atomic_pool_init(माप_प्रकार pool_size,
						      gfp_t gfp)
अणु
	काष्ठा gen_pool *pool;
	पूर्णांक ret;

	pool = gen_pool_create(PAGE_SHIFT, NUMA_NO_NODE);
	अगर (!pool)
		वापस शून्य;

	gen_pool_set_algo(pool, gen_pool_first_fit_order_align, शून्य);

	ret = atomic_pool_expand(pool, pool_size, gfp);
	अगर (ret) अणु
		gen_pool_destroy(pool);
		pr_err("DMA: failed to allocate %zu KiB %pGg pool for atomic allocation\n",
		       pool_size >> 10, &gfp);
		वापस शून्य;
	पूर्ण

	pr_info("DMA: preallocated %zu KiB %pGg pool for atomic allocations\n",
		gen_pool_size(pool) >> 10, &gfp);
	वापस pool;
पूर्ण

अटल पूर्णांक __init dma_atomic_pool_init(व्योम)
अणु
	पूर्णांक ret = 0;

	/*
	 * If coherent_pool was not used on the command line, शेष the pool
	 * sizes to 128KB per 1GB of memory, min 128KB, max MAX_ORDER-1.
	 */
	अगर (!atomic_pool_size) अणु
		अचिन्हित दीर्घ pages = totalram_pages() / (SZ_1G / SZ_128K);
		pages = min_t(अचिन्हित दीर्घ, pages, MAX_ORDER_NR_PAGES);
		atomic_pool_size = max_t(माप_प्रकार, pages << PAGE_SHIFT, SZ_128K);
	पूर्ण
	INIT_WORK(&atomic_pool_work, atomic_pool_work_fn);

	atomic_pool_kernel = __dma_atomic_pool_init(atomic_pool_size,
						    GFP_KERNEL);
	अगर (!atomic_pool_kernel)
		ret = -ENOMEM;
	अगर (IS_ENABLED(CONFIG_ZONE_DMA)) अणु
		atomic_pool_dma = __dma_atomic_pool_init(atomic_pool_size,
						GFP_KERNEL | GFP_DMA);
		अगर (!atomic_pool_dma)
			ret = -ENOMEM;
	पूर्ण
	अगर (IS_ENABLED(CONFIG_ZONE_DMA32)) अणु
		atomic_pool_dma32 = __dma_atomic_pool_init(atomic_pool_size,
						GFP_KERNEL | GFP_DMA32);
		अगर (!atomic_pool_dma32)
			ret = -ENOMEM;
	पूर्ण

	dma_atomic_pool_debugfs_init();
	वापस ret;
पूर्ण
postcore_initcall(dma_atomic_pool_init);

अटल अंतरभूत काष्ठा gen_pool *dma_guess_pool(काष्ठा gen_pool *prev, gfp_t gfp)
अणु
	अगर (prev == शून्य) अणु
		अगर (IS_ENABLED(CONFIG_ZONE_DMA32) && (gfp & GFP_DMA32))
			वापस atomic_pool_dma32;
		अगर (IS_ENABLED(CONFIG_ZONE_DMA) && (gfp & GFP_DMA))
			वापस atomic_pool_dma;
		वापस atomic_pool_kernel;
	पूर्ण
	अगर (prev == atomic_pool_kernel)
		वापस atomic_pool_dma32 ? atomic_pool_dma32 : atomic_pool_dma;
	अगर (prev == atomic_pool_dma32)
		वापस atomic_pool_dma;
	वापस शून्य;
पूर्ण

अटल काष्ठा page *__dma_alloc_from_pool(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा gen_pool *pool, व्योम **cpu_addr,
		bool (*phys_addr_ok)(काष्ठा device *, phys_addr_t, माप_प्रकार))
अणु
	अचिन्हित दीर्घ addr;
	phys_addr_t phys;

	addr = gen_pool_alloc(pool, size);
	अगर (!addr)
		वापस शून्य;

	phys = gen_pool_virt_to_phys(pool, addr);
	अगर (phys_addr_ok && !phys_addr_ok(dev, phys, size)) अणु
		gen_pool_मुक्त(pool, addr, size);
		वापस शून्य;
	पूर्ण

	अगर (gen_pool_avail(pool) < atomic_pool_size)
		schedule_work(&atomic_pool_work);

	*cpu_addr = (व्योम *)addr;
	स_रखो(*cpu_addr, 0, size);
	वापस pfn_to_page(__phys_to_pfn(phys));
पूर्ण

काष्ठा page *dma_alloc_from_pool(काष्ठा device *dev, माप_प्रकार size,
		व्योम **cpu_addr, gfp_t gfp,
		bool (*phys_addr_ok)(काष्ठा device *, phys_addr_t, माप_प्रकार))
अणु
	काष्ठा gen_pool *pool = शून्य;
	काष्ठा page *page;

	जबतक ((pool = dma_guess_pool(pool, gfp))) अणु
		page = __dma_alloc_from_pool(dev, size, pool, cpu_addr,
					     phys_addr_ok);
		अगर (page)
			वापस page;
	पूर्ण

	WARN(1, "Failed to get suitable pool for %s\n", dev_name(dev));
	वापस शून्य;
पूर्ण

bool dma_मुक्त_from_pool(काष्ठा device *dev, व्योम *start, माप_प्रकार size)
अणु
	काष्ठा gen_pool *pool = शून्य;

	जबतक ((pool = dma_guess_pool(pool, 0))) अणु
		अगर (!gen_pool_has_addr(pool, (अचिन्हित दीर्घ)start, size))
			जारी;
		gen_pool_मुक्त(pool, (अचिन्हित दीर्घ)start, size);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
