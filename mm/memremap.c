<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2015 Intel Corporation. All rights reserved. */
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kasan.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/mm.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/swap.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/swapops.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको_bit.h>
#समावेश <linux/xarray.h>

अटल DEFINE_XARRAY(pgmap_array);

/*
 * The memremap() and memremap_pages() पूर्णांकerfaces are alternately used
 * to map persistent memory namespaces. These पूर्णांकerfaces place dअगरferent
 * स्थिरraपूर्णांकs on the alignment and size of the mapping (namespace).
 * memremap() can map inभागidual PAGE_SIZE pages. memremap_pages() can
 * only map subsections (2MB), and at least one architecture (PowerPC)
 * the minimum mapping granularity of memremap_pages() is 16MB.
 *
 * The role of memremap_compat_align() is to communicate the minimum
 * arch supported alignment of a namespace such that it can मुक्तly
 * चयन modes without violating the arch स्थिरraपूर्णांक. Namely, करो not
 * allow a namespace to be PAGE_SIZE aligned since that namespace may be
 * reconfigured पूर्णांकo a mode that requires SUBSECTION_SIZE alignment.
 */
#अगर_अघोषित CONFIG_ARCH_HAS_MEMREMAP_COMPAT_ALIGN
अचिन्हित दीर्घ memremap_compat_align(व्योम)
अणु
	वापस SUBSECTION_SIZE;
पूर्ण
EXPORT_SYMBOL_GPL(memremap_compat_align);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEV_PAGEMAP_OPS
DEFINE_STATIC_KEY_FALSE(devmap_managed_key);
EXPORT_SYMBOL(devmap_managed_key);

अटल व्योम devmap_managed_enable_put(काष्ठा dev_pagemap *pgmap)
अणु
	अगर (pgmap->type == MEMORY_DEVICE_PRIVATE ||
	    pgmap->type == MEMORY_DEVICE_FS_DAX)
		अटल_branch_dec(&devmap_managed_key);
पूर्ण

अटल व्योम devmap_managed_enable_get(काष्ठा dev_pagemap *pgmap)
अणु
	अगर (pgmap->type == MEMORY_DEVICE_PRIVATE ||
	    pgmap->type == MEMORY_DEVICE_FS_DAX)
		अटल_branch_inc(&devmap_managed_key);
पूर्ण
#अन्यथा
अटल व्योम devmap_managed_enable_get(काष्ठा dev_pagemap *pgmap)
अणु
पूर्ण
अटल व्योम devmap_managed_enable_put(काष्ठा dev_pagemap *pgmap)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEV_PAGEMAP_OPS */

अटल व्योम pgmap_array_delete(काष्ठा range *range)
अणु
	xa_store_range(&pgmap_array, PHYS_PFN(range->start), PHYS_PFN(range->end),
			शून्य, GFP_KERNEL);
	synchronize_rcu();
पूर्ण

अटल अचिन्हित दीर्घ pfn_first(काष्ठा dev_pagemap *pgmap, पूर्णांक range_id)
अणु
	काष्ठा range *range = &pgmap->ranges[range_id];
	अचिन्हित दीर्घ pfn = PHYS_PFN(range->start);

	अगर (range_id)
		वापस pfn;
	वापस pfn + vmem_alपंचांगap_offset(pgmap_alपंचांगap(pgmap));
पूर्ण

bool pgmap_pfn_valid(काष्ठा dev_pagemap *pgmap, अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pgmap->nr_range; i++) अणु
		काष्ठा range *range = &pgmap->ranges[i];

		अगर (pfn >= PHYS_PFN(range->start) &&
		    pfn <= PHYS_PFN(range->end))
			वापस pfn >= pfn_first(pgmap, i);
	पूर्ण

	वापस false;
पूर्ण

अटल अचिन्हित दीर्घ pfn_end(काष्ठा dev_pagemap *pgmap, पूर्णांक range_id)
अणु
	स्थिर काष्ठा range *range = &pgmap->ranges[range_id];

	वापस (range->start + range_len(range)) >> PAGE_SHIFT;
पूर्ण

अटल अचिन्हित दीर्घ pfn_next(अचिन्हित दीर्घ pfn)
अणु
	अगर (pfn % 1024 == 0)
		cond_resched();
	वापस pfn + 1;
पूर्ण

#घोषणा क्रम_each_device_pfn(pfn, map, i) \
	क्रम (pfn = pfn_first(map, i); pfn < pfn_end(map, i); pfn = pfn_next(pfn))

अटल व्योम dev_pagemap_समाप्त(काष्ठा dev_pagemap *pgmap)
अणु
	अगर (pgmap->ops && pgmap->ops->समाप्त)
		pgmap->ops->समाप्त(pgmap);
	अन्यथा
		percpu_ref_समाप्त(pgmap->ref);
पूर्ण

अटल व्योम dev_pagemap_cleanup(काष्ठा dev_pagemap *pgmap)
अणु
	अगर (pgmap->ops && pgmap->ops->cleanup) अणु
		pgmap->ops->cleanup(pgmap);
	पूर्ण अन्यथा अणु
		रुको_क्रम_completion(&pgmap->करोne);
		percpu_ref_निकास(pgmap->ref);
	पूर्ण
	/*
	 * Unकरो the pgmap ref assignment क्रम the पूर्णांकernal हाल as the
	 * caller may re-enable the same pgmap.
	 */
	अगर (pgmap->ref == &pgmap->पूर्णांकernal_ref)
		pgmap->ref = शून्य;
पूर्ण

अटल व्योम pageunmap_range(काष्ठा dev_pagemap *pgmap, पूर्णांक range_id)
अणु
	काष्ठा range *range = &pgmap->ranges[range_id];
	काष्ठा page *first_page;
	पूर्णांक nid;

	/* make sure to access a memmap that was actually initialized */
	first_page = pfn_to_page(pfn_first(pgmap, range_id));

	/* pages are dead and unused, unकरो the arch mapping */
	nid = page_to_nid(first_page);

	mem_hotplug_begin();
	हटाओ_pfn_range_from_zone(page_zone(first_page), PHYS_PFN(range->start),
				   PHYS_PFN(range_len(range)));
	अगर (pgmap->type == MEMORY_DEVICE_PRIVATE) अणु
		__हटाओ_pages(PHYS_PFN(range->start),
			       PHYS_PFN(range_len(range)), शून्य);
	पूर्ण अन्यथा अणु
		arch_हटाओ_memory(nid, range->start, range_len(range),
				pgmap_alपंचांगap(pgmap));
		kasan_हटाओ_zero_shaकरोw(__va(range->start), range_len(range));
	पूर्ण
	mem_hotplug_करोne();

	untrack_pfn(शून्य, PHYS_PFN(range->start), range_len(range));
	pgmap_array_delete(range);
पूर्ण

व्योम memunmap_pages(काष्ठा dev_pagemap *pgmap)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक i;

	dev_pagemap_समाप्त(pgmap);
	क्रम (i = 0; i < pgmap->nr_range; i++)
		क्रम_each_device_pfn(pfn, pgmap, i)
			put_page(pfn_to_page(pfn));
	dev_pagemap_cleanup(pgmap);

	क्रम (i = 0; i < pgmap->nr_range; i++)
		pageunmap_range(pgmap, i);

	WARN_ONCE(pgmap->alपंचांगap.alloc, "failed to free all reserved pages\n");
	devmap_managed_enable_put(pgmap);
पूर्ण
EXPORT_SYMBOL_GPL(memunmap_pages);

अटल व्योम devm_memremap_pages_release(व्योम *data)
अणु
	memunmap_pages(data);
पूर्ण

अटल व्योम dev_pagemap_percpu_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा dev_pagemap *pgmap =
		container_of(ref, काष्ठा dev_pagemap, पूर्णांकernal_ref);

	complete(&pgmap->करोne);
पूर्ण

अटल पूर्णांक pagemap_range(काष्ठा dev_pagemap *pgmap, काष्ठा mhp_params *params,
		पूर्णांक range_id, पूर्णांक nid)
अणु
	स्थिर bool is_निजी = pgmap->type == MEMORY_DEVICE_PRIVATE;
	काष्ठा range *range = &pgmap->ranges[range_id];
	काष्ठा dev_pagemap *conflict_pgmap;
	पूर्णांक error, is_ram;

	अगर (WARN_ONCE(pgmap_alपंचांगap(pgmap) && range_id > 0,
				"altmap not supported for multiple ranges\n"))
		वापस -EINVAL;

	conflict_pgmap = get_dev_pagemap(PHYS_PFN(range->start), शून्य);
	अगर (conflict_pgmap) अणु
		WARN(1, "Conflicting mapping in same section\n");
		put_dev_pagemap(conflict_pgmap);
		वापस -ENOMEM;
	पूर्ण

	conflict_pgmap = get_dev_pagemap(PHYS_PFN(range->end), शून्य);
	अगर (conflict_pgmap) अणु
		WARN(1, "Conflicting mapping in same section\n");
		put_dev_pagemap(conflict_pgmap);
		वापस -ENOMEM;
	पूर्ण

	is_ram = region_पूर्णांकersects(range->start, range_len(range),
		IORESOURCE_SYSTEM_RAM, IORES_DESC_NONE);

	अगर (is_ram != REGION_DISJOINT) अणु
		WARN_ONCE(1, "attempted on %s region %#llx-%#llx\n",
				is_ram == REGION_MIXED ? "mixed" : "ram",
				range->start, range->end);
		वापस -ENXIO;
	पूर्ण

	error = xa_err(xa_store_range(&pgmap_array, PHYS_PFN(range->start),
				PHYS_PFN(range->end), pgmap, GFP_KERNEL));
	अगर (error)
		वापस error;

	अगर (nid < 0)
		nid = numa_mem_id();

	error = track_pfn_remap(शून्य, &params->pgprot, PHYS_PFN(range->start), 0,
			range_len(range));
	अगर (error)
		जाओ err_pfn_remap;

	अगर (!mhp_range_allowed(range->start, range_len(range), !is_निजी)) अणु
		error = -EINVAL;
		जाओ err_pfn_remap;
	पूर्ण

	mem_hotplug_begin();

	/*
	 * For device निजी memory we call add_pages() as we only need to
	 * allocate and initialize काष्ठा page क्रम the device memory. More-
	 * over the device memory is un-accessible thus we करो not want to
	 * create a linear mapping क्रम the memory like arch_add_memory()
	 * would करो.
	 *
	 * For all other device memory types, which are accessible by
	 * the CPU, we करो want the linear mapping and thus use
	 * arch_add_memory().
	 */
	अगर (is_निजी) अणु
		error = add_pages(nid, PHYS_PFN(range->start),
				PHYS_PFN(range_len(range)), params);
	पूर्ण अन्यथा अणु
		error = kasan_add_zero_shaकरोw(__va(range->start), range_len(range));
		अगर (error) अणु
			mem_hotplug_करोne();
			जाओ err_kasan;
		पूर्ण

		error = arch_add_memory(nid, range->start, range_len(range),
					params);
	पूर्ण

	अगर (!error) अणु
		काष्ठा zone *zone;

		zone = &NODE_DATA(nid)->node_zones[ZONE_DEVICE];
		move_pfn_range_to_zone(zone, PHYS_PFN(range->start),
				PHYS_PFN(range_len(range)), params->alपंचांगap,
				MIGRATE_MOVABLE);
	पूर्ण

	mem_hotplug_करोne();
	अगर (error)
		जाओ err_add_memory;

	/*
	 * Initialization of the pages has been deferred until now in order
	 * to allow us to करो the work जबतक not holding the hotplug lock.
	 */
	memmap_init_zone_device(&NODE_DATA(nid)->node_zones[ZONE_DEVICE],
				PHYS_PFN(range->start),
				PHYS_PFN(range_len(range)), pgmap);
	percpu_ref_get_many(pgmap->ref, pfn_end(pgmap, range_id)
			- pfn_first(pgmap, range_id));
	वापस 0;

err_add_memory:
	kasan_हटाओ_zero_shaकरोw(__va(range->start), range_len(range));
err_kasan:
	untrack_pfn(शून्य, PHYS_PFN(range->start), range_len(range));
err_pfn_remap:
	pgmap_array_delete(range);
	वापस error;
पूर्ण


/*
 * Not device managed version of dev_memremap_pages, unकरोne by
 * memunmap_pages().  Please use dev_memremap_pages अगर you have a काष्ठा
 * device available.
 */
व्योम *memremap_pages(काष्ठा dev_pagemap *pgmap, पूर्णांक nid)
अणु
	काष्ठा mhp_params params = अणु
		.alपंचांगap = pgmap_alपंचांगap(pgmap),
		.pgprot = PAGE_KERNEL,
	पूर्ण;
	स्थिर पूर्णांक nr_range = pgmap->nr_range;
	पूर्णांक error, i;

	अगर (WARN_ONCE(!nr_range, "nr_range must be specified\n"))
		वापस ERR_PTR(-EINVAL);

	चयन (pgmap->type) अणु
	हाल MEMORY_DEVICE_PRIVATE:
		अगर (!IS_ENABLED(CONFIG_DEVICE_PRIVATE)) अणु
			WARN(1, "Device private memory not supported\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अगर (!pgmap->ops || !pgmap->ops->migrate_to_ram) अणु
			WARN(1, "Missing migrate_to_ram method\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अगर (!pgmap->ops->page_मुक्त) अणु
			WARN(1, "Missing page_free method\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अगर (!pgmap->owner) अणु
			WARN(1, "Missing owner\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अवरोध;
	हाल MEMORY_DEVICE_FS_DAX:
		अगर (!IS_ENABLED(CONFIG_ZONE_DEVICE) ||
		    IS_ENABLED(CONFIG_FS_DAX_LIMITED)) अणु
			WARN(1, "File system DAX not supported\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		अवरोध;
	हाल MEMORY_DEVICE_GENERIC:
		अवरोध;
	हाल MEMORY_DEVICE_PCI_P2PDMA:
		params.pgprot = pgprot_noncached(params.pgprot);
		अवरोध;
	शेष:
		WARN(1, "Invalid pgmap type %d\n", pgmap->type);
		अवरोध;
	पूर्ण

	अगर (!pgmap->ref) अणु
		अगर (pgmap->ops && (pgmap->ops->समाप्त || pgmap->ops->cleanup))
			वापस ERR_PTR(-EINVAL);

		init_completion(&pgmap->करोne);
		error = percpu_ref_init(&pgmap->पूर्णांकernal_ref,
				dev_pagemap_percpu_release, 0, GFP_KERNEL);
		अगर (error)
			वापस ERR_PTR(error);
		pgmap->ref = &pgmap->पूर्णांकernal_ref;
	पूर्ण अन्यथा अणु
		अगर (!pgmap->ops || !pgmap->ops->समाप्त || !pgmap->ops->cleanup) अणु
			WARN(1, "Missing reference count teardown definition\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	devmap_managed_enable_get(pgmap);

	/*
	 * Clear the pgmap nr_range as it will be incremented क्रम each
	 * successfully processed range. This communicates how many
	 * regions to unwind in the पात हाल.
	 */
	pgmap->nr_range = 0;
	error = 0;
	क्रम (i = 0; i < nr_range; i++) अणु
		error = pagemap_range(pgmap, &params, i, nid);
		अगर (error)
			अवरोध;
		pgmap->nr_range++;
	पूर्ण

	अगर (i < nr_range) अणु
		memunmap_pages(pgmap);
		pgmap->nr_range = nr_range;
		वापस ERR_PTR(error);
	पूर्ण

	वापस __va(pgmap->ranges[0].start);
पूर्ण
EXPORT_SYMBOL_GPL(memremap_pages);

/**
 * devm_memremap_pages - remap and provide memmap backing क्रम the given resource
 * @dev: hosting device क्रम @res
 * @pgmap: poपूर्णांकer to a काष्ठा dev_pagemap
 *
 * Notes:
 * 1/ At a minimum the res and type members of @pgmap must be initialized
 *    by the caller beक्रमe passing it to this function
 *
 * 2/ The alपंचांगap field may optionally be initialized, in which हाल
 *    PGMAP_ALTMAP_VALID must be set in pgmap->flags.
 *
 * 3/ The ref field may optionally be provided, in which pgmap->ref must be
 *    'live' on entry and will be समाप्तed and reaped at
 *    devm_memremap_pages_release() समय, or अगर this routine fails.
 *
 * 4/ range is expected to be a host memory range that could feasibly be
 *    treated as a "System RAM" range, i.e. not a device mmio range, but
 *    this is not enक्रमced.
 */
व्योम *devm_memremap_pages(काष्ठा device *dev, काष्ठा dev_pagemap *pgmap)
अणु
	पूर्णांक error;
	व्योम *ret;

	ret = memremap_pages(pgmap, dev_to_node(dev));
	अगर (IS_ERR(ret))
		वापस ret;

	error = devm_add_action_or_reset(dev, devm_memremap_pages_release,
			pgmap);
	अगर (error)
		वापस ERR_PTR(error);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_memremap_pages);

व्योम devm_memunmap_pages(काष्ठा device *dev, काष्ठा dev_pagemap *pgmap)
अणु
	devm_release_action(dev, devm_memremap_pages_release, pgmap);
पूर्ण
EXPORT_SYMBOL_GPL(devm_memunmap_pages);

अचिन्हित दीर्घ vmem_alपंचांगap_offset(काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	/* number of pfns from base where pfn_to_page() is valid */
	अगर (alपंचांगap)
		वापस alपंचांगap->reserve + alपंचांगap->मुक्त;
	वापस 0;
पूर्ण

व्योम vmem_alपंचांगap_मुक्त(काष्ठा vmem_alपंचांगap *alपंचांगap, अचिन्हित दीर्घ nr_pfns)
अणु
	alपंचांगap->alloc -= nr_pfns;
पूर्ण

/**
 * get_dev_pagemap() - take a new live reference on the dev_pagemap क्रम @pfn
 * @pfn: page frame number to lookup page_map
 * @pgmap: optional known pgmap that alपढ़ोy has a reference
 *
 * If @pgmap is non-शून्य and covers @pfn it will be वापसed as-is.  If @pgmap
 * is non-शून्य but करोes not cover @pfn the reference to it will be released.
 */
काष्ठा dev_pagemap *get_dev_pagemap(अचिन्हित दीर्घ pfn,
		काष्ठा dev_pagemap *pgmap)
अणु
	resource_माप_प्रकार phys = PFN_PHYS(pfn);

	/*
	 * In the cached हाल we're alपढ़ोy holding a live reference.
	 */
	अगर (pgmap) अणु
		अगर (phys >= pgmap->range.start && phys <= pgmap->range.end)
			वापस pgmap;
		put_dev_pagemap(pgmap);
	पूर्ण

	/* fall back to slow path lookup */
	rcu_पढ़ो_lock();
	pgmap = xa_load(&pgmap_array, PHYS_PFN(phys));
	अगर (pgmap && !percpu_ref_tryget_live(pgmap->ref))
		pgmap = शून्य;
	rcu_पढ़ो_unlock();

	वापस pgmap;
पूर्ण
EXPORT_SYMBOL_GPL(get_dev_pagemap);

#अगर_घोषित CONFIG_DEV_PAGEMAP_OPS
व्योम मुक्त_devmap_managed_page(काष्ठा page *page)
अणु
	/* notअगरy page idle क्रम dax */
	अगर (!is_device_निजी_page(page)) अणु
		wake_up_var(&page->_refcount);
		वापस;
	पूर्ण

	__ClearPageWaiters(page);

	mem_cgroup_unअक्षरge(page);

	/*
	 * When a device_निजी page is मुक्तd, the page->mapping field
	 * may still contain a (stale) mapping value. For example, the
	 * lower bits of page->mapping may still identअगरy the page as an
	 * anonymous page. Ultimately, this entire field is just stale
	 * and wrong, and it will cause errors अगर not cleared.  One
	 * example is:
	 *
	 *  migrate_vma_pages()
	 *    migrate_vma_insert_page()
	 *      page_add_new_anon_rmap()
	 *        __page_set_anon_rmap()
	 *          ...checks page->mapping, via PageAnon(page) call,
	 *            and incorrectly concludes that the page is an
	 *            anonymous page. Thereक्रमe, it incorrectly,
	 *            silently fails to set up the new anon rmap.
	 *
	 * For other types of ZONE_DEVICE pages, migration is either
	 * handled dअगरferently or not करोne at all, so there is no need
	 * to clear page->mapping.
	 */
	page->mapping = शून्य;
	page->pgmap->ops->page_मुक्त(page);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEV_PAGEMAP_OPS */
