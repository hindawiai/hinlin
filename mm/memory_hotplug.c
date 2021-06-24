<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/memory_hotplug.c
 *
 *  Copyright (C)
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/swap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/cpu.h>
#समावेश <linux/memory.h>
#समावेश <linux/memremap.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/migrate.h>
#समावेश <linux/page-isolation.h>
#समावेश <linux/pfn.h>
#समावेश <linux/suspend.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/firmware-map.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/memblock.h>
#समावेश <linux/compaction.h>
#समावेश <linux/rmap.h>

#समावेश <यंत्र/tlbflush.h>

#समावेश "internal.h"
#समावेश "shuffle.h"


/*
 * memory_hotplug.memmap_on_memory parameter
 */
अटल bool memmap_on_memory __ro_after_init;
#अगर_घोषित CONFIG_MHP_MEMMAP_ON_MEMORY
module_param(memmap_on_memory, bool, 0444);
MODULE_PARM_DESC(memmap_on_memory, "Enable memmap on memory for memory hotplug");
#पूर्ण_अगर

/*
 * online_page_callback contains poपूर्णांकer to current page onlining function.
 * Initially it is generic_online_page(). If it is required it could be
 * changed by calling set_online_page_callback() क्रम callback registration
 * and restore_online_page_callback() क्रम generic callback restore.
 */

अटल online_page_callback_t online_page_callback = generic_online_page;
अटल DEFINE_MUTEX(online_page_callback_lock);

DEFINE_STATIC_PERCPU_RWSEM(mem_hotplug_lock);

व्योम get_online_mems(व्योम)
अणु
	percpu_करोwn_पढ़ो(&mem_hotplug_lock);
पूर्ण

व्योम put_online_mems(व्योम)
अणु
	percpu_up_पढ़ो(&mem_hotplug_lock);
पूर्ण

bool movable_node_enabled = false;

#अगर_अघोषित CONFIG_MEMORY_HOTPLUG_DEFAULT_ONLINE
पूर्णांक mhp_शेष_online_type = MMOP_OFFLINE;
#अन्यथा
पूर्णांक mhp_शेष_online_type = MMOP_ONLINE;
#पूर्ण_अगर

अटल पूर्णांक __init setup_memhp_शेष_state(अक्षर *str)
अणु
	स्थिर पूर्णांक online_type = mhp_online_type_from_str(str);

	अगर (online_type >= 0)
		mhp_शेष_online_type = online_type;

	वापस 1;
पूर्ण
__setup("memhp_default_state=", setup_memhp_शेष_state);

व्योम mem_hotplug_begin(व्योम)
अणु
	cpus_पढ़ो_lock();
	percpu_करोwn_ग_लिखो(&mem_hotplug_lock);
पूर्ण

व्योम mem_hotplug_करोne(व्योम)
अणु
	percpu_up_ग_लिखो(&mem_hotplug_lock);
	cpus_पढ़ो_unlock();
पूर्ण

u64 max_mem_size = U64_MAX;

/* add this memory to iomem resource */
अटल काष्ठा resource *रेजिस्टर_memory_resource(u64 start, u64 size,
						 स्थिर अक्षर *resource_name)
अणु
	काष्ठा resource *res;
	अचिन्हित दीर्घ flags =  IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	अगर (म_भेद(resource_name, "System RAM"))
		flags |= IORESOURCE_SYSRAM_DRIVER_MANAGED;

	अगर (!mhp_range_allowed(start, size, true))
		वापस ERR_PTR(-E2BIG);

	/*
	 * Make sure value parsed from 'mem=' only restricts memory adding
	 * जबतक booting, so that memory hotplug won't be impacted. Please
	 * refer to करोcument of 'mem=' in kernel-parameters.txt क्रम more
	 * details.
	 */
	अगर (start + size > max_mem_size && प्रणाली_state < SYSTEM_RUNNING)
		वापस ERR_PTR(-E2BIG);

	/*
	 * Request ownership of the new memory range.  This might be
	 * a child of an existing resource that was present but
	 * not marked as busy.
	 */
	res = __request_region(&iomem_resource, start, size,
			       resource_name, flags);

	अगर (!res) अणु
		pr_debug("Unable to reserve System RAM region: %016llx->%016llx\n",
				start, start + size);
		वापस ERR_PTR(-EEXIST);
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम release_memory_resource(काष्ठा resource *res)
अणु
	अगर (!res)
		वापस;
	release_resource(res);
	kमुक्त(res);
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG_SPARSE
व्योम get_page_booपंचांगem(अचिन्हित दीर्घ info,  काष्ठा page *page,
		      अचिन्हित दीर्घ type)
अणु
	page->मुक्तlist = (व्योम *)type;
	SetPagePrivate(page);
	set_page_निजी(page, info);
	page_ref_inc(page);
पूर्ण

व्योम put_page_booपंचांगem(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ type;

	type = (अचिन्हित दीर्घ) page->मुक्तlist;
	BUG_ON(type < MEMORY_HOTPLUG_MIN_BOOTMEM_TYPE ||
	       type > MEMORY_HOTPLUG_MAX_BOOTMEM_TYPE);

	अगर (page_ref_dec_वापस(page) == 1) अणु
		page->मुक्तlist = शून्य;
		ClearPagePrivate(page);
		set_page_निजी(page, 0);
		INIT_LIST_HEAD(&page->lru);
		मुक्त_reserved_page(page);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HAVE_BOOTMEM_INFO_NODE
#अगर_अघोषित CONFIG_SPARSEMEM_VMEMMAP
अटल व्योम रेजिस्टर_page_booपंचांगem_info_section(अचिन्हित दीर्घ start_pfn)
अणु
	अचिन्हित दीर्घ mapsize, section_nr, i;
	काष्ठा mem_section *ms;
	काष्ठा page *page, *memmap;
	काष्ठा mem_section_usage *usage;

	section_nr = pfn_to_section_nr(start_pfn);
	ms = __nr_to_section(section_nr);

	/* Get section's memmap address */
	memmap = sparse_decode_mem_map(ms->section_mem_map, section_nr);

	/*
	 * Get page क्रम the memmap's phys address
	 * XXX: need more consideration क्रम sparse_vmemmap...
	 */
	page = virt_to_page(memmap);
	mapsize = माप(काष्ठा page) * PAGES_PER_SECTION;
	mapsize = PAGE_ALIGN(mapsize) >> PAGE_SHIFT;

	/* remember memmap's page */
	क्रम (i = 0; i < mapsize; i++, page++)
		get_page_booपंचांगem(section_nr, page, SECTION_INFO);

	usage = ms->usage;
	page = virt_to_page(usage);

	mapsize = PAGE_ALIGN(mem_section_usage_size()) >> PAGE_SHIFT;

	क्रम (i = 0; i < mapsize; i++, page++)
		get_page_booपंचांगem(section_nr, page, MIX_SECTION_INFO);

पूर्ण
#अन्यथा /* CONFIG_SPARSEMEM_VMEMMAP */
अटल व्योम रेजिस्टर_page_booपंचांगem_info_section(अचिन्हित दीर्घ start_pfn)
अणु
	अचिन्हित दीर्घ mapsize, section_nr, i;
	काष्ठा mem_section *ms;
	काष्ठा page *page, *memmap;
	काष्ठा mem_section_usage *usage;

	section_nr = pfn_to_section_nr(start_pfn);
	ms = __nr_to_section(section_nr);

	memmap = sparse_decode_mem_map(ms->section_mem_map, section_nr);

	रेजिस्टर_page_booपंचांगem_memmap(section_nr, memmap, PAGES_PER_SECTION);

	usage = ms->usage;
	page = virt_to_page(usage);

	mapsize = PAGE_ALIGN(mem_section_usage_size()) >> PAGE_SHIFT;

	क्रम (i = 0; i < mapsize; i++, page++)
		get_page_booपंचांगem(section_nr, page, MIX_SECTION_INFO);
पूर्ण
#पूर्ण_अगर /* !CONFIG_SPARSEMEM_VMEMMAP */

व्योम __init रेजिस्टर_page_booपंचांगem_info_node(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ i, pfn, end_pfn, nr_pages;
	पूर्णांक node = pgdat->node_id;
	काष्ठा page *page;

	nr_pages = PAGE_ALIGN(माप(काष्ठा pglist_data)) >> PAGE_SHIFT;
	page = virt_to_page(pgdat);

	क्रम (i = 0; i < nr_pages; i++, page++)
		get_page_booपंचांगem(node, page, NODE_INFO);

	pfn = pgdat->node_start_pfn;
	end_pfn = pgdat_end_pfn(pgdat);

	/* रेजिस्टर section info */
	क्रम (; pfn < end_pfn; pfn += PAGES_PER_SECTION) अणु
		/*
		 * Some platक्रमms can assign the same pfn to multiple nodes - on
		 * node0 as well as nodeN.  To aव्योम रेजिस्टरing a pfn against
		 * multiple nodes we check that this pfn करोes not alपढ़ोy
		 * reside in some other nodes.
		 */
		अगर (pfn_valid(pfn) && (early_pfn_to_nid(pfn) == node))
			रेजिस्टर_page_booपंचांगem_info_section(pfn);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_BOOTMEM_INFO_NODE */

अटल पूर्णांक check_pfn_span(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
		स्थिर अक्षर *reason)
अणु
	/*
	 * Disallow all operations smaller than a sub-section and only
	 * allow operations smaller than a section क्रम
	 * SPARSEMEM_VMEMMAP. Note that check_hotplug_memory_range()
	 * enक्रमces a larger memory_block_size_bytes() granularity क्रम
	 * memory that will be marked online, so this check should only
	 * fire क्रम direct arch_अणुadd,हटाओपूर्ण_memory() users outside of
	 * add_memory_resource().
	 */
	अचिन्हित दीर्घ min_align;

	अगर (IS_ENABLED(CONFIG_SPARSEMEM_VMEMMAP))
		min_align = PAGES_PER_SUBSECTION;
	अन्यथा
		min_align = PAGES_PER_SECTION;
	अगर (!IS_ALIGNED(pfn, min_align)
			|| !IS_ALIGNED(nr_pages, min_align)) अणु
		WARN(1, "Misaligned __%s_pages start: %#lx end: #%lx\n",
				reason, pfn, pfn + nr_pages - 1);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return page क्रम the valid pfn only अगर the page is online. All pfn
 * walkers which rely on the fully initialized page->flags and others
 * should use this rather than pfn_valid && pfn_to_page
 */
काष्ठा page *pfn_to_online_page(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ nr = pfn_to_section_nr(pfn);
	काष्ठा dev_pagemap *pgmap;
	काष्ठा mem_section *ms;

	अगर (nr >= NR_MEM_SECTIONS)
		वापस शून्य;

	ms = __nr_to_section(nr);
	अगर (!online_section(ms))
		वापस शून्य;

	/*
	 * Save some code text when online_section() +
	 * pfn_section_valid() are sufficient.
	 */
	अगर (IS_ENABLED(CONFIG_HAVE_ARCH_PFN_VALID) && !pfn_valid(pfn))
		वापस शून्य;

	अगर (!pfn_section_valid(ms, pfn))
		वापस शून्य;

	अगर (!online_device_section(ms))
		वापस pfn_to_page(pfn);

	/*
	 * Slowpath: when ZONE_DEVICE collides with
	 * ZONE_अणुNORMAL,MOVABLEपूर्ण within the same section some pfns in
	 * the section may be 'offline' but 'valid'. Only
	 * get_dev_pagemap() can determine sub-section online status.
	 */
	pgmap = get_dev_pagemap(pfn, शून्य);
	put_dev_pagemap(pgmap);

	/* The presence of a pgmap indicates ZONE_DEVICE offline pfn */
	अगर (pgmap)
		वापस शून्य;

	वापस pfn_to_page(pfn);
पूर्ण
EXPORT_SYMBOL_GPL(pfn_to_online_page);

/*
 * Reasonably generic function क्रम adding memory.  It is
 * expected that archs that support memory hotplug will
 * call this function after deciding the zone to which to
 * add the new pages.
 */
पूर्णांक __ref __add_pages(पूर्णांक nid, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
		काष्ठा mhp_params *params)
अणु
	स्थिर अचिन्हित दीर्घ end_pfn = pfn + nr_pages;
	अचिन्हित दीर्घ cur_nr_pages;
	पूर्णांक err;
	काष्ठा vmem_alपंचांगap *alपंचांगap = params->alपंचांगap;

	अगर (WARN_ON_ONCE(!params->pgprot.pgprot))
		वापस -EINVAL;

	VM_BUG_ON(!mhp_range_allowed(PFN_PHYS(pfn), nr_pages * PAGE_SIZE, false));

	अगर (alपंचांगap) अणु
		/*
		 * Validate alपंचांगap is within bounds of the total request
		 */
		अगर (alपंचांगap->base_pfn != pfn
				|| vmem_alपंचांगap_offset(alपंचांगap) > nr_pages) अणु
			pr_warn_once("memory add fail, invalid altmap\n");
			वापस -EINVAL;
		पूर्ण
		alपंचांगap->alloc = 0;
	पूर्ण

	err = check_pfn_span(pfn, nr_pages, "add");
	अगर (err)
		वापस err;

	क्रम (; pfn < end_pfn; pfn += cur_nr_pages) अणु
		/* Select all reमुख्यing pages up to the next section boundary */
		cur_nr_pages = min(end_pfn - pfn,
				   SECTION_ALIGN_UP(pfn + 1) - pfn);
		err = sparse_add_section(nid, pfn, cur_nr_pages, alपंचांगap);
		अगर (err)
			अवरोध;
		cond_resched();
	पूर्ण
	vmemmap_populate_prपूर्णांक_last();
	वापस err;
पूर्ण

/* find the smallest valid pfn in the range [start_pfn, end_pfn) */
अटल अचिन्हित दीर्घ find_smallest_section_pfn(पूर्णांक nid, काष्ठा zone *zone,
				     अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ end_pfn)
अणु
	क्रम (; start_pfn < end_pfn; start_pfn += PAGES_PER_SUBSECTION) अणु
		अगर (unlikely(!pfn_to_online_page(start_pfn)))
			जारी;

		अगर (unlikely(pfn_to_nid(start_pfn) != nid))
			जारी;

		अगर (zone != page_zone(pfn_to_page(start_pfn)))
			जारी;

		वापस start_pfn;
	पूर्ण

	वापस 0;
पूर्ण

/* find the biggest valid pfn in the range [start_pfn, end_pfn). */
अटल अचिन्हित दीर्घ find_biggest_section_pfn(पूर्णांक nid, काष्ठा zone *zone,
				    अचिन्हित दीर्घ start_pfn,
				    अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn;

	/* pfn is the end pfn of a memory section. */
	pfn = end_pfn - 1;
	क्रम (; pfn >= start_pfn; pfn -= PAGES_PER_SUBSECTION) अणु
		अगर (unlikely(!pfn_to_online_page(pfn)))
			जारी;

		अगर (unlikely(pfn_to_nid(pfn) != nid))
			जारी;

		अगर (zone != page_zone(pfn_to_page(pfn)))
			जारी;

		वापस pfn;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम shrink_zone_span(काष्ठा zone *zone, अचिन्हित दीर्घ start_pfn,
			     अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक nid = zone_to_nid(zone);

	zone_span_ग_लिखोlock(zone);
	अगर (zone->zone_start_pfn == start_pfn) अणु
		/*
		 * If the section is smallest section in the zone, it need
		 * shrink zone->zone_start_pfn and zone->zone_spanned_pages.
		 * In this हाल, we find second smallest valid mem_section
		 * क्रम shrinking zone.
		 */
		pfn = find_smallest_section_pfn(nid, zone, end_pfn,
						zone_end_pfn(zone));
		अगर (pfn) अणु
			zone->spanned_pages = zone_end_pfn(zone) - pfn;
			zone->zone_start_pfn = pfn;
		पूर्ण अन्यथा अणु
			zone->zone_start_pfn = 0;
			zone->spanned_pages = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (zone_end_pfn(zone) == end_pfn) अणु
		/*
		 * If the section is biggest section in the zone, it need
		 * shrink zone->spanned_pages.
		 * In this हाल, we find second biggest valid mem_section क्रम
		 * shrinking zone.
		 */
		pfn = find_biggest_section_pfn(nid, zone, zone->zone_start_pfn,
					       start_pfn);
		अगर (pfn)
			zone->spanned_pages = pfn - zone->zone_start_pfn + 1;
		अन्यथा अणु
			zone->zone_start_pfn = 0;
			zone->spanned_pages = 0;
		पूर्ण
	पूर्ण
	zone_span_ग_लिखोunlock(zone);
पूर्ण

अटल व्योम update_pgdat_span(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ node_start_pfn = 0, node_end_pfn = 0;
	काष्ठा zone *zone;

	क्रम (zone = pgdat->node_zones;
	     zone < pgdat->node_zones + MAX_NR_ZONES; zone++) अणु
		अचिन्हित दीर्घ end_pfn = zone_end_pfn(zone);

		/* No need to lock the zones, they can't change. */
		अगर (!zone->spanned_pages)
			जारी;
		अगर (!node_end_pfn) अणु
			node_start_pfn = zone->zone_start_pfn;
			node_end_pfn = end_pfn;
			जारी;
		पूर्ण

		अगर (end_pfn > node_end_pfn)
			node_end_pfn = end_pfn;
		अगर (zone->zone_start_pfn < node_start_pfn)
			node_start_pfn = zone->zone_start_pfn;
	पूर्ण

	pgdat->node_start_pfn = node_start_pfn;
	pgdat->node_spanned_pages = node_end_pfn - node_start_pfn;
पूर्ण

व्योम __ref हटाओ_pfn_range_from_zone(काष्ठा zone *zone,
				      अचिन्हित दीर्घ start_pfn,
				      अचिन्हित दीर्घ nr_pages)
अणु
	स्थिर अचिन्हित दीर्घ end_pfn = start_pfn + nr_pages;
	काष्ठा pglist_data *pgdat = zone->zone_pgdat;
	अचिन्हित दीर्घ pfn, cur_nr_pages, flags;

	/* Poison काष्ठा pages because they are now uninitialized again. */
	क्रम (pfn = start_pfn; pfn < end_pfn; pfn += cur_nr_pages) अणु
		cond_resched();

		/* Select all reमुख्यing pages up to the next section boundary */
		cur_nr_pages =
			min(end_pfn - pfn, SECTION_ALIGN_UP(pfn + 1) - pfn);
		page_init_poison(pfn_to_page(pfn),
				 माप(काष्ठा page) * cur_nr_pages);
	पूर्ण

#अगर_घोषित CONFIG_ZONE_DEVICE
	/*
	 * Zone shrinking code cannot properly deal with ZONE_DEVICE. So
	 * we will not try to shrink the zones - which is okay as
	 * set_zone_contiguous() cannot deal with ZONE_DEVICE either way.
	 */
	अगर (zone_idx(zone) == ZONE_DEVICE)
		वापस;
#पूर्ण_अगर

	clear_zone_contiguous(zone);

	pgdat_resize_lock(zone->zone_pgdat, &flags);
	shrink_zone_span(zone, start_pfn, start_pfn + nr_pages);
	update_pgdat_span(pgdat);
	pgdat_resize_unlock(zone->zone_pgdat, &flags);

	set_zone_contiguous(zone);
पूर्ण

अटल व्योम __हटाओ_section(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
			     अचिन्हित दीर्घ map_offset,
			     काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	काष्ठा mem_section *ms = __pfn_to_section(pfn);

	अगर (WARN_ON_ONCE(!valid_section(ms)))
		वापस;

	sparse_हटाओ_section(ms, pfn, nr_pages, map_offset, alपंचांगap);
पूर्ण

/**
 * __हटाओ_pages() - हटाओ sections of pages
 * @pfn: starting pageframe (must be aligned to start of a section)
 * @nr_pages: number of pages to हटाओ (must be multiple of section size)
 * @alपंचांगap: alternative device page map or %शून्य अगर शेष memmap is used
 *
 * Generic helper function to हटाओ section mappings and sysfs entries
 * क्रम the section of the memory we are removing. Caller needs to make
 * sure that pages are marked reserved and zones are adjust properly by
 * calling offline_pages().
 */
व्योम __हटाओ_pages(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
		    काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	स्थिर अचिन्हित दीर्घ end_pfn = pfn + nr_pages;
	अचिन्हित दीर्घ cur_nr_pages;
	अचिन्हित दीर्घ map_offset = 0;

	map_offset = vmem_alपंचांगap_offset(alपंचांगap);

	अगर (check_pfn_span(pfn, nr_pages, "remove"))
		वापस;

	क्रम (; pfn < end_pfn; pfn += cur_nr_pages) अणु
		cond_resched();
		/* Select all reमुख्यing pages up to the next section boundary */
		cur_nr_pages = min(end_pfn - pfn,
				   SECTION_ALIGN_UP(pfn + 1) - pfn);
		__हटाओ_section(pfn, cur_nr_pages, map_offset, alपंचांगap);
		map_offset = 0;
	पूर्ण
पूर्ण

पूर्णांक set_online_page_callback(online_page_callback_t callback)
अणु
	पूर्णांक rc = -EINVAL;

	get_online_mems();
	mutex_lock(&online_page_callback_lock);

	अगर (online_page_callback == generic_online_page) अणु
		online_page_callback = callback;
		rc = 0;
	पूर्ण

	mutex_unlock(&online_page_callback_lock);
	put_online_mems();

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(set_online_page_callback);

पूर्णांक restore_online_page_callback(online_page_callback_t callback)
अणु
	पूर्णांक rc = -EINVAL;

	get_online_mems();
	mutex_lock(&online_page_callback_lock);

	अगर (online_page_callback == callback) अणु
		online_page_callback = generic_online_page;
		rc = 0;
	पूर्ण

	mutex_unlock(&online_page_callback_lock);
	put_online_mems();

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(restore_online_page_callback);

व्योम generic_online_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	/*
	 * Freeing the page with debug_pagealloc enabled will try to unmap it,
	 * so we should map it first. This is better than पूर्णांकroducing a special
	 * हाल in page मुक्तing fast path.
	 */
	debug_pagealloc_map_pages(page, 1 << order);
	__मुक्त_pages_core(page, order);
	totalram_pages_add(1UL << order);
#अगर_घोषित CONFIG_HIGHMEM
	अगर (PageHighMem(page))
		totalhigh_pages_add(1UL << order);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(generic_online_page);

अटल व्योम online_pages_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages)
अणु
	स्थिर अचिन्हित दीर्घ end_pfn = start_pfn + nr_pages;
	अचिन्हित दीर्घ pfn;

	/*
	 * Online the pages in MAX_ORDER - 1 aligned chunks. The callback might
	 * decide to not expose all pages to the buddy (e.g., expose them
	 * later). We account all pages as being online and beदीर्घing to this
	 * zone ("present").
	 * When using memmap_on_memory, the range might not be aligned to
	 * MAX_ORDER_NR_PAGES - 1, but pageblock aligned. __ffs() will detect
	 * this and the first chunk to online will be pageblock_nr_pages.
	 */
	क्रम (pfn = start_pfn; pfn < end_pfn;) अणु
		पूर्णांक order = min(MAX_ORDER - 1UL, __ffs(pfn));

		(*online_page_callback)(pfn_to_page(pfn), order);
		pfn += (1UL << order);
	पूर्ण

	/* mark all involved sections as online */
	online_mem_sections(start_pfn, end_pfn);
पूर्ण

/* check which state of node_states will be changed when online memory */
अटल व्योम node_states_check_changes_online(अचिन्हित दीर्घ nr_pages,
	काष्ठा zone *zone, काष्ठा memory_notअगरy *arg)
अणु
	पूर्णांक nid = zone_to_nid(zone);

	arg->status_change_nid = NUMA_NO_NODE;
	arg->status_change_nid_normal = NUMA_NO_NODE;
	arg->status_change_nid_high = NUMA_NO_NODE;

	अगर (!node_state(nid, N_MEMORY))
		arg->status_change_nid = nid;
	अगर (zone_idx(zone) <= ZONE_NORMAL && !node_state(nid, N_NORMAL_MEMORY))
		arg->status_change_nid_normal = nid;
#अगर_घोषित CONFIG_HIGHMEM
	अगर (zone_idx(zone) <= ZONE_HIGHMEM && !node_state(nid, N_HIGH_MEMORY))
		arg->status_change_nid_high = nid;
#पूर्ण_अगर
पूर्ण

अटल व्योम node_states_set_node(पूर्णांक node, काष्ठा memory_notअगरy *arg)
अणु
	अगर (arg->status_change_nid_normal >= 0)
		node_set_state(node, N_NORMAL_MEMORY);

	अगर (arg->status_change_nid_high >= 0)
		node_set_state(node, N_HIGH_MEMORY);

	अगर (arg->status_change_nid >= 0)
		node_set_state(node, N_MEMORY);
पूर्ण

अटल व्योम __meminit resize_zone_range(काष्ठा zone *zone, अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ old_end_pfn = zone_end_pfn(zone);

	अगर (zone_is_empty(zone) || start_pfn < zone->zone_start_pfn)
		zone->zone_start_pfn = start_pfn;

	zone->spanned_pages = max(start_pfn + nr_pages, old_end_pfn) - zone->zone_start_pfn;
पूर्ण

अटल व्योम __meminit resize_pgdat_range(काष्ठा pglist_data *pgdat, अचिन्हित दीर्घ start_pfn,
                                     अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ old_end_pfn = pgdat_end_pfn(pgdat);

	अगर (!pgdat->node_spanned_pages || start_pfn < pgdat->node_start_pfn)
		pgdat->node_start_pfn = start_pfn;

	pgdat->node_spanned_pages = max(start_pfn + nr_pages, old_end_pfn) - pgdat->node_start_pfn;

पूर्ण

अटल व्योम section_taपूर्णांक_zone_device(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा mem_section *ms = __pfn_to_section(pfn);

	ms->section_mem_map |= SECTION_TAINT_ZONE_DEVICE;
पूर्ण

/*
 * Associate the pfn range with the given zone, initializing the memmaps
 * and resizing the pgdat/zone data to span the added pages. After this
 * call, all affected pages are PG_reserved.
 *
 * All aligned pageblocks are initialized to the specअगरied migratetype
 * (usually MIGRATE_MOVABLE). Besides setting the migratetype, no related
 * zone stats (e.g., nr_isolate_pageblock) are touched.
 */
व्योम __ref move_pfn_range_to_zone(काष्ठा zone *zone, अचिन्हित दीर्घ start_pfn,
				  अचिन्हित दीर्घ nr_pages,
				  काष्ठा vmem_alपंचांगap *alपंचांगap, पूर्णांक migratetype)
अणु
	काष्ठा pglist_data *pgdat = zone->zone_pgdat;
	पूर्णांक nid = pgdat->node_id;
	अचिन्हित दीर्घ flags;

	clear_zone_contiguous(zone);

	/* TODO Huh pgdat is irqsave जबतक zone is not. It used to be like that beक्रमe */
	pgdat_resize_lock(pgdat, &flags);
	zone_span_ग_लिखोlock(zone);
	अगर (zone_is_empty(zone))
		init_currently_empty_zone(zone, start_pfn, nr_pages);
	resize_zone_range(zone, start_pfn, nr_pages);
	zone_span_ग_लिखोunlock(zone);
	resize_pgdat_range(pgdat, start_pfn, nr_pages);
	pgdat_resize_unlock(pgdat, &flags);

	/*
	 * Subsection population requires care in pfn_to_online_page().
	 * Set the taपूर्णांक to enable the slow path detection of
	 * ZONE_DEVICE pages in an otherwise  ZONE_अणुNORMAL,MOVABLEपूर्ण
	 * section.
	 */
	अगर (zone_is_zone_device(zone)) अणु
		अगर (!IS_ALIGNED(start_pfn, PAGES_PER_SECTION))
			section_taपूर्णांक_zone_device(start_pfn);
		अगर (!IS_ALIGNED(start_pfn + nr_pages, PAGES_PER_SECTION))
			section_taपूर्णांक_zone_device(start_pfn + nr_pages);
	पूर्ण

	/*
	 * TODO now we have a visible range of pages which are not associated
	 * with their zone properly. Not nice but set_pfnblock_flags_mask
	 * expects the zone spans the pfn range. All the pages in the range
	 * are reserved so nobody should be touching them so we should be safe
	 */
	memmap_init_range(nr_pages, nid, zone_idx(zone), start_pfn, 0,
			 MEMINIT_HOTPLUG, alपंचांगap, migratetype);

	set_zone_contiguous(zone);
पूर्ण

/*
 * Returns a शेष kernel memory zone क्रम the given pfn range.
 * If no kernel zone covers this pfn range it will स्वतःmatically go
 * to the ZONE_NORMAL.
 */
अटल काष्ठा zone *शेष_kernel_zone_क्रम_pfn(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा pglist_data *pgdat = NODE_DATA(nid);
	पूर्णांक zid;

	क्रम (zid = 0; zid <= ZONE_NORMAL; zid++) अणु
		काष्ठा zone *zone = &pgdat->node_zones[zid];

		अगर (zone_पूर्णांकersects(zone, start_pfn, nr_pages))
			वापस zone;
	पूर्ण

	वापस &pgdat->node_zones[ZONE_NORMAL];
पूर्ण

अटल अंतरभूत काष्ठा zone *शेष_zone_क्रम_pfn(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ nr_pages)
अणु
	काष्ठा zone *kernel_zone = शेष_kernel_zone_क्रम_pfn(nid, start_pfn,
			nr_pages);
	काष्ठा zone *movable_zone = &NODE_DATA(nid)->node_zones[ZONE_MOVABLE];
	bool in_kernel = zone_पूर्णांकersects(kernel_zone, start_pfn, nr_pages);
	bool in_movable = zone_पूर्णांकersects(movable_zone, start_pfn, nr_pages);

	/*
	 * We inherit the existing zone in a simple हाल where zones करो not
	 * overlap in the given range
	 */
	अगर (in_kernel ^ in_movable)
		वापस (in_kernel) ? kernel_zone : movable_zone;

	/*
	 * If the range करोesn't beदीर्घ to any zone or two zones overlap in the
	 * given range then we use movable zone only अगर movable_node is
	 * enabled because we always online to a kernel zone by शेष.
	 */
	वापस movable_node_enabled ? movable_zone : kernel_zone;
पूर्ण

काष्ठा zone *zone_क्रम_pfn_range(पूर्णांक online_type, पूर्णांक nid, अचिन्हित start_pfn,
		अचिन्हित दीर्घ nr_pages)
अणु
	अगर (online_type == MMOP_ONLINE_KERNEL)
		वापस शेष_kernel_zone_क्रम_pfn(nid, start_pfn, nr_pages);

	अगर (online_type == MMOP_ONLINE_MOVABLE)
		वापस &NODE_DATA(nid)->node_zones[ZONE_MOVABLE];

	वापस शेष_zone_क्रम_pfn(nid, start_pfn, nr_pages);
पूर्ण

/*
 * This function should only be called by memory_block_अणुonline,offlineपूर्ण,
 * and अणुonline,offlineपूर्ण_pages.
 */
व्योम adjust_present_page_count(काष्ठा zone *zone, दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ flags;

	zone->present_pages += nr_pages;
	pgdat_resize_lock(zone->zone_pgdat, &flags);
	zone->zone_pgdat->node_present_pages += nr_pages;
	pgdat_resize_unlock(zone->zone_pgdat, &flags);
पूर्ण

पूर्णांक mhp_init_memmap_on_memory(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
			      काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ end_pfn = pfn + nr_pages;
	पूर्णांक ret;

	ret = kasan_add_zero_shaकरोw(__va(PFN_PHYS(pfn)), PFN_PHYS(nr_pages));
	अगर (ret)
		वापस ret;

	move_pfn_range_to_zone(zone, pfn, nr_pages, शून्य, MIGRATE_UNMOVABLE);

	/*
	 * It might be that the vmemmap_pages fully span sections. If that is
	 * the हाल, mark those sections online here as otherwise they will be
	 * left offline.
	 */
	अगर (nr_pages >= PAGES_PER_SECTION)
	        online_mem_sections(pfn, ALIGN_DOWN(end_pfn, PAGES_PER_SECTION));

	वापस ret;
पूर्ण

व्योम mhp_deinit_memmap_on_memory(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ end_pfn = pfn + nr_pages;

	/*
	 * It might be that the vmemmap_pages fully span sections. If that is
	 * the हाल, mark those sections offline here as otherwise they will be
	 * left online.
	 */
	अगर (nr_pages >= PAGES_PER_SECTION)
		offline_mem_sections(pfn, ALIGN_DOWN(end_pfn, PAGES_PER_SECTION));

        /*
	 * The pages associated with this vmemmap have been offlined, so
	 * we can reset its state here.
	 */
	हटाओ_pfn_range_from_zone(page_zone(pfn_to_page(pfn)), pfn, nr_pages);
	kasan_हटाओ_zero_shaकरोw(__va(PFN_PHYS(pfn)), PFN_PHYS(nr_pages));
पूर्ण

पूर्णांक __ref online_pages(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages, काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक need_zonelists_rebuild = 0;
	स्थिर पूर्णांक nid = zone_to_nid(zone);
	पूर्णांक ret;
	काष्ठा memory_notअगरy arg;

	/*
	 * अणुon,offपूर्णlining is स्थिरrained to full memory sections (or more
	 * precisly to memory blocks from the user space POV).
	 * memmap_on_memory is an exception because it reserves initial part
	 * of the physical memory space क्रम vmemmaps. That space is pageblock
	 * aligned.
	 */
	अगर (WARN_ON_ONCE(!nr_pages ||
			 !IS_ALIGNED(pfn, pageblock_nr_pages) ||
			 !IS_ALIGNED(pfn + nr_pages, PAGES_PER_SECTION)))
		वापस -EINVAL;

	mem_hotplug_begin();

	/* associate pfn range with the zone */
	move_pfn_range_to_zone(zone, pfn, nr_pages, शून्य, MIGRATE_ISOLATE);

	arg.start_pfn = pfn;
	arg.nr_pages = nr_pages;
	node_states_check_changes_online(nr_pages, zone, &arg);

	ret = memory_notअगरy(MEM_GOING_ONLINE, &arg);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret)
		जाओ failed_addition;

	/*
	 * Fixup the number of isolated pageblocks beक्रमe marking the sections
	 * onlining, such that unकरो_isolate_page_range() works correctly.
	 */
	spin_lock_irqsave(&zone->lock, flags);
	zone->nr_isolate_pageblock += nr_pages / pageblock_nr_pages;
	spin_unlock_irqrestore(&zone->lock, flags);

	/*
	 * If this zone is not populated, then it is not in zonelist.
	 * This means the page allocator ignores this zone.
	 * So, zonelist must be updated after online.
	 */
	अगर (!populated_zone(zone)) अणु
		need_zonelists_rebuild = 1;
		setup_zone_pageset(zone);
	पूर्ण

	online_pages_range(pfn, nr_pages);
	adjust_present_page_count(zone, nr_pages);

	node_states_set_node(nid, &arg);
	अगर (need_zonelists_rebuild)
		build_all_zonelists(शून्य);
	zone_pcp_update(zone);

	/* Basic onlining is complete, allow allocation of onlined pages. */
	unकरो_isolate_page_range(pfn, pfn + nr_pages, MIGRATE_MOVABLE);

	/*
	 * Freshly onlined pages aren't shuffled (e.g., all pages are placed to
	 * the tail of the मुक्तlist when unकरोing isolation). Shuffle the whole
	 * zone to make sure the just onlined pages are properly distributed
	 * across the whole मुक्तlist - to create an initial shuffle.
	 */
	shuffle_zone(zone);

	init_per_zone_wmark_min();

	kswapd_run(nid);
	kcompactd_run(nid);

	ग_लिखोback_set_ratelimit();

	memory_notअगरy(MEM_ONLINE, &arg);
	mem_hotplug_करोne();
	वापस 0;

failed_addition:
	pr_debug("online_pages [mem %#010llx-%#010llx] failed\n",
		 (अचिन्हित दीर्घ दीर्घ) pfn << PAGE_SHIFT,
		 (((अचिन्हित दीर्घ दीर्घ) pfn + nr_pages) << PAGE_SHIFT) - 1);
	memory_notअगरy(MEM_CANCEL_ONLINE, &arg);
	हटाओ_pfn_range_from_zone(zone, pfn, nr_pages);
	mem_hotplug_करोne();
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG_SPARSE */

अटल व्योम reset_node_present_pages(pg_data_t *pgdat)
अणु
	काष्ठा zone *z;

	क्रम (z = pgdat->node_zones; z < pgdat->node_zones + MAX_NR_ZONES; z++)
		z->present_pages = 0;

	pgdat->node_present_pages = 0;
पूर्ण

/* we are OK calling __meminit stuff here - we have CONFIG_MEMORY_HOTPLUG */
अटल pg_data_t __ref *hotadd_new_pgdat(पूर्णांक nid)
अणु
	काष्ठा pglist_data *pgdat;

	pgdat = NODE_DATA(nid);
	अगर (!pgdat) अणु
		pgdat = arch_alloc_nodedata(nid);
		अगर (!pgdat)
			वापस शून्य;

		pgdat->per_cpu_nodestats =
			alloc_percpu(काष्ठा per_cpu_nodestat);
		arch_refresh_nodedata(nid, pgdat);
	पूर्ण अन्यथा अणु
		पूर्णांक cpu;
		/*
		 * Reset the nr_zones, order and highest_zoneidx beक्रमe reuse.
		 * Note that kswapd will init kswapd_highest_zoneidx properly
		 * when it starts in the near future.
		 */
		pgdat->nr_zones = 0;
		pgdat->kswapd_order = 0;
		pgdat->kswapd_highest_zoneidx = 0;
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा per_cpu_nodestat *p;

			p = per_cpu_ptr(pgdat->per_cpu_nodestats, cpu);
			स_रखो(p, 0, माप(*p));
		पूर्ण
	पूर्ण

	/* we can use NODE_DATA(nid) from here */
	pgdat->node_id = nid;
	pgdat->node_start_pfn = 0;

	/* init node's zones as empty zones, we don't have any present pages.*/
	मुक्त_area_init_core_hotplug(nid);

	/*
	 * The node we allocated has no zone fallback lists. For aव्योमing
	 * to access not-initialized zonelist, build here.
	 */
	build_all_zonelists(pgdat);

	/*
	 * When memory is hot-added, all the memory is in offline state. So
	 * clear all zones' present_pages because they will be updated in
	 * online_pages() and offline_pages().
	 */
	reset_node_managed_pages(pgdat);
	reset_node_present_pages(pgdat);

	वापस pgdat;
पूर्ण

अटल व्योम rollback_node_hotadd(पूर्णांक nid)
अणु
	pg_data_t *pgdat = NODE_DATA(nid);

	arch_refresh_nodedata(nid, शून्य);
	मुक्त_percpu(pgdat->per_cpu_nodestats);
	arch_मुक्त_nodedata(pgdat);
पूर्ण


/**
 * try_online_node - online a node अगर offlined
 * @nid: the node ID
 * @set_node_online: Whether we want to online the node
 * called by cpu_up() to online a node without onlined memory.
 *
 * Returns:
 * 1 -> a new node has been allocated
 * 0 -> the node is alपढ़ोy online
 * -ENOMEM -> the node could not be allocated
 */
अटल पूर्णांक __try_online_node(पूर्णांक nid, bool set_node_online)
अणु
	pg_data_t *pgdat;
	पूर्णांक ret = 1;

	अगर (node_online(nid))
		वापस 0;

	pgdat = hotadd_new_pgdat(nid);
	अगर (!pgdat) अणु
		pr_err("Cannot online node %d due to NULL pgdat\n", nid);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (set_node_online) अणु
		node_set_online(nid);
		ret = रेजिस्टर_one_node(nid);
		BUG_ON(ret);
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * Users of this function always want to online/रेजिस्टर the node
 */
पूर्णांक try_online_node(पूर्णांक nid)
अणु
	पूर्णांक ret;

	mem_hotplug_begin();
	ret =  __try_online_node(nid, true);
	mem_hotplug_करोne();
	वापस ret;
पूर्ण

अटल पूर्णांक check_hotplug_memory_range(u64 start, u64 size)
अणु
	/* memory range must be block size aligned */
	अगर (!size || !IS_ALIGNED(start, memory_block_size_bytes()) ||
	    !IS_ALIGNED(size, memory_block_size_bytes())) अणु
		pr_err("Block size [%#lx] unaligned hotplug range: start %#llx, size %#llx",
		       memory_block_size_bytes(), start, size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक online_memory_block(काष्ठा memory_block *mem, व्योम *arg)
अणु
	mem->online_type = mhp_शेष_online_type;
	वापस device_online(&mem->dev);
पूर्ण

bool mhp_supports_memmap_on_memory(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ nr_vmemmap_pages = size / PAGE_SIZE;
	अचिन्हित दीर्घ vmemmap_size = nr_vmemmap_pages * माप(काष्ठा page);
	अचिन्हित दीर्घ reमुख्यing_size = size - vmemmap_size;

	/*
	 * Besides having arch support and the feature enabled at runसमय, we
	 * need a few more assumptions to hold true:
	 *
	 * a) We span a single memory block: memory onlining/offlinin;g happens
	 *    in memory block granularity. We करोn't want the vmemmap of online
	 *    memory blocks to reside on offline memory blocks. In the future,
	 *    we might want to support variable-sized memory blocks to make the
	 *    feature more versatile.
	 *
	 * b) The vmemmap pages span complete PMDs: We करोn't want vmemmap code
	 *    to populate memory from the alपंचांगap क्रम unrelated parts (i.e.,
	 *    other memory blocks)
	 *
	 * c) The vmemmap pages (and thereby the pages that will be exposed to
	 *    the buddy) have to cover full pageblocks: memory onlining/offlining
	 *    code requires applicable ranges to be page-aligned, क्रम example, to
	 *    set the migratetypes properly.
	 *
	 * TODO: Although we have a check here to make sure that vmemmap pages
	 *       fully populate a PMD, it is not the right place to check क्रम
	 *       this. A much better solution involves improving vmemmap code
	 *       to fallback to base pages when trying to populate vmemmap using
	 *       alपंचांगap as an alternative source of memory, and we करो not exactly
	 *       populate a single PMD.
	 */
	वापस memmap_on_memory &&
	       IS_ENABLED(CONFIG_MHP_MEMMAP_ON_MEMORY) &&
	       size == memory_block_size_bytes() &&
	       IS_ALIGNED(vmemmap_size, PMD_SIZE) &&
	       IS_ALIGNED(reमुख्यing_size, (pageblock_nr_pages << PAGE_SHIFT));
पूर्ण

/*
 * NOTE: The caller must call lock_device_hotplug() to serialize hotplug
 * and online/offline operations (triggered e.g. by sysfs).
 *
 * we are OK calling __meminit stuff here - we have CONFIG_MEMORY_HOTPLUG
 */
पूर्णांक __ref add_memory_resource(पूर्णांक nid, काष्ठा resource *res, mhp_t mhp_flags)
अणु
	काष्ठा mhp_params params = अणु .pgprot = pgprot_mhp(PAGE_KERNEL) पूर्ण;
	काष्ठा vmem_alपंचांगap mhp_alपंचांगap = अणुपूर्ण;
	u64 start, size;
	bool new_node = false;
	पूर्णांक ret;

	start = res->start;
	size = resource_size(res);

	ret = check_hotplug_memory_range(start, size);
	अगर (ret)
		वापस ret;

	अगर (!node_possible(nid)) अणु
		WARN(1, "node %d was absent from the node_possible_map\n", nid);
		वापस -EINVAL;
	पूर्ण

	mem_hotplug_begin();

	अगर (IS_ENABLED(CONFIG_ARCH_KEEP_MEMBLOCK))
		memblock_add_node(start, size, nid);

	ret = __try_online_node(nid, false);
	अगर (ret < 0)
		जाओ error;
	new_node = ret;

	/*
	 * Self hosted memmap array
	 */
	अगर (mhp_flags & MHP_MEMMAP_ON_MEMORY) अणु
		अगर (!mhp_supports_memmap_on_memory(size)) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		mhp_alपंचांगap.मुक्त = PHYS_PFN(size);
		mhp_alपंचांगap.base_pfn = PHYS_PFN(start);
		params.alपंचांगap = &mhp_alपंचांगap;
	पूर्ण

	/* call arch's memory hotadd */
	ret = arch_add_memory(nid, start, size, &params);
	अगर (ret < 0)
		जाओ error;

	/* create memory block devices after memory was added */
	ret = create_memory_block_devices(start, size, mhp_alपंचांगap.alloc);
	अगर (ret) अणु
		arch_हटाओ_memory(nid, start, size, शून्य);
		जाओ error;
	पूर्ण

	अगर (new_node) अणु
		/* If sysfs file of new node can't be created, cpu on the node
		 * can't be hot-added. There is no rollback way now.
		 * So, check by BUG_ON() to catch it reluctantly..
		 * We online node here. We can't roll back from here.
		 */
		node_set_online(nid);
		ret = __रेजिस्टर_one_node(nid);
		BUG_ON(ret);
	पूर्ण

	/* link memory sections under this node.*/
	link_mem_sections(nid, PFN_DOWN(start), PFN_UP(start + size - 1),
			  MEMINIT_HOTPLUG);

	/* create new memmap entry */
	अगर (!म_भेद(res->name, "System RAM"))
		firmware_map_add_hotplug(start, start + size, "System RAM");

	/* device_online() will take the lock when calling online_pages() */
	mem_hotplug_करोne();

	/*
	 * In हाल we're allowed to merge the resource, flag it and trigger
	 * merging now that adding succeeded.
	 */
	अगर (mhp_flags & MHP_MERGE_RESOURCE)
		merge_प्रणाली_ram_resource(res);

	/* online pages अगर requested */
	अगर (mhp_शेष_online_type != MMOP_OFFLINE)
		walk_memory_blocks(start, size, शून्य, online_memory_block);

	वापस ret;
error:
	/* rollback pgdat allocation and others */
	अगर (new_node)
		rollback_node_hotadd(nid);
	अगर (IS_ENABLED(CONFIG_ARCH_KEEP_MEMBLOCK))
		memblock_हटाओ(start, size);
	mem_hotplug_करोne();
	वापस ret;
पूर्ण

/* requires device_hotplug_lock, see add_memory_resource() */
पूर्णांक __ref __add_memory(पूर्णांक nid, u64 start, u64 size, mhp_t mhp_flags)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	res = रेजिस्टर_memory_resource(start, size, "System RAM");
	अगर (IS_ERR(res))
		वापस PTR_ERR(res);

	ret = add_memory_resource(nid, res, mhp_flags);
	अगर (ret < 0)
		release_memory_resource(res);
	वापस ret;
पूर्ण

पूर्णांक add_memory(पूर्णांक nid, u64 start, u64 size, mhp_t mhp_flags)
अणु
	पूर्णांक rc;

	lock_device_hotplug();
	rc = __add_memory(nid, start, size, mhp_flags);
	unlock_device_hotplug();

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(add_memory);

/*
 * Add special, driver-managed memory to the प्रणाली as प्रणाली RAM. Such
 * memory is not exposed via the raw firmware-provided memmap as प्रणाली
 * RAM, instead, it is detected and added by a driver - during cold boot,
 * after a reboot, and after kexec.
 *
 * Reasons why this memory should not be used क्रम the initial memmap of a
 * kexec kernel or क्रम placing kexec images:
 * - The booting kernel is in अक्षरge of determining how this memory will be
 *   used (e.g., use persistent memory as प्रणाली RAM)
 * - Coordination with a hypervisor is required beक्रमe this memory
 *   can be used (e.g., inaccessible parts).
 *
 * For this memory, no entries in /sys/firmware/memmap ("raw firmware-provided
 * memory map") are created. Also, the created memory resource is flagged
 * with IORESOURCE_SYSRAM_DRIVER_MANAGED, so in-kernel users can special-हाल
 * this memory as well (esp., not place kexec images onto it).
 *
 * The resource_name (visible via /proc/iomem) has to have the क्रमmat
 * "System RAM ($DRIVER)".
 */
पूर्णांक add_memory_driver_managed(पूर्णांक nid, u64 start, u64 size,
			      स्थिर अक्षर *resource_name, mhp_t mhp_flags)
अणु
	काष्ठा resource *res;
	पूर्णांक rc;

	अगर (!resource_name ||
	    म_माला(resource_name, "System RAM (") != resource_name ||
	    resource_name[म_माप(resource_name) - 1] != ')')
		वापस -EINVAL;

	lock_device_hotplug();

	res = रेजिस्टर_memory_resource(start, size, resource_name);
	अगर (IS_ERR(res)) अणु
		rc = PTR_ERR(res);
		जाओ out_unlock;
	पूर्ण

	rc = add_memory_resource(nid, res, mhp_flags);
	अगर (rc < 0)
		release_memory_resource(res);

out_unlock:
	unlock_device_hotplug();
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(add_memory_driver_managed);

/*
 * Platक्रमms should define arch_get_mappable_range() that provides
 * maximum possible addressable physical memory range क्रम which the
 * linear mapping could be created. The platक्रमm वापसed address
 * range must adhere to these following semantics.
 *
 * - range.start <= range.end
 * - Range includes both end poपूर्णांकs [range.start..range.end]
 *
 * There is also a fallback definition provided here, allowing the
 * entire possible physical address range in हाल any platक्रमm करोes
 * not define arch_get_mappable_range().
 */
काष्ठा range __weak arch_get_mappable_range(व्योम)
अणु
	काष्ठा range mhp_range = अणु
		.start = 0UL,
		.end = -1ULL,
	पूर्ण;
	वापस mhp_range;
पूर्ण

काष्ठा range mhp_get_pluggable_range(bool need_mapping)
अणु
	स्थिर u64 max_phys = (1ULL << MAX_PHYSMEM_BITS) - 1;
	काष्ठा range mhp_range;

	अगर (need_mapping) अणु
		mhp_range = arch_get_mappable_range();
		अगर (mhp_range.start > max_phys) अणु
			mhp_range.start = 0;
			mhp_range.end = 0;
		पूर्ण
		mhp_range.end = min_t(u64, mhp_range.end, max_phys);
	पूर्ण अन्यथा अणु
		mhp_range.start = 0;
		mhp_range.end = max_phys;
	पूर्ण
	वापस mhp_range;
पूर्ण
EXPORT_SYMBOL_GPL(mhp_get_pluggable_range);

bool mhp_range_allowed(u64 start, u64 size, bool need_mapping)
अणु
	काष्ठा range mhp_range = mhp_get_pluggable_range(need_mapping);
	u64 end = start + size;

	अगर (start < end && start >= mhp_range.start && (end - 1) <= mhp_range.end)
		वापस true;

	pr_warn("Hotplug memory [%#llx-%#llx] exceeds maximum addressable range [%#llx-%#llx]\n",
		start, end, mhp_range.start, mhp_range.end);
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
/*
 * Confirm all pages in a range [start, end) beदीर्घ to the same zone (skipping
 * memory holes). When true, वापस the zone.
 */
काष्ठा zone *test_pages_in_a_zone(अचिन्हित दीर्घ start_pfn,
				  अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn, sec_end_pfn;
	काष्ठा zone *zone = शून्य;
	काष्ठा page *page;
	पूर्णांक i;
	क्रम (pfn = start_pfn, sec_end_pfn = SECTION_ALIGN_UP(start_pfn + 1);
	     pfn < end_pfn;
	     pfn = sec_end_pfn, sec_end_pfn += PAGES_PER_SECTION) अणु
		/* Make sure the memory section is present first */
		अगर (!present_section_nr(pfn_to_section_nr(pfn)))
			जारी;
		क्रम (; pfn < sec_end_pfn && pfn < end_pfn;
		     pfn += MAX_ORDER_NR_PAGES) अणु
			i = 0;
			/* This is just a CONFIG_HOLES_IN_ZONE check.*/
			जबतक ((i < MAX_ORDER_NR_PAGES) &&
				!pfn_valid_within(pfn + i))
				i++;
			अगर (i == MAX_ORDER_NR_PAGES || pfn + i >= end_pfn)
				जारी;
			/* Check अगर we got outside of the zone */
			अगर (zone && !zone_spans_pfn(zone, pfn + i))
				वापस शून्य;
			page = pfn_to_page(pfn + i);
			अगर (zone && page_zone(page) != zone)
				वापस शून्य;
			zone = page_zone(page);
		पूर्ण
	पूर्ण

	वापस zone;
पूर्ण

/*
 * Scan pfn range [start,end) to find movable/migratable pages (LRU pages,
 * non-lru movable pages and hugepages). Will skip over most unmovable
 * pages (esp., pages that can be skipped when offlining), but bail out on
 * definitely unmovable pages.
 *
 * Returns:
 *	0 in हाल a movable page is found and movable_pfn was updated.
 *	-ENOENT in हाल no movable page was found.
 *	-EBUSY in हाल a definitely unmovable page was found.
 */
अटल पूर्णांक scan_movable_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			      अचिन्हित दीर्घ *movable_pfn)
अणु
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = start; pfn < end; pfn++) अणु
		काष्ठा page *page, *head;
		अचिन्हित दीर्घ skip;

		अगर (!pfn_valid(pfn))
			जारी;
		page = pfn_to_page(pfn);
		अगर (PageLRU(page))
			जाओ found;
		अगर (__PageMovable(page))
			जाओ found;

		/*
		 * PageOffline() pages that are not marked __PageMovable() and
		 * have a reference count > 0 (after MEM_GOING_OFFLINE) are
		 * definitely unmovable. If their reference count would be 0,
		 * they could at least be skipped when offlining memory.
		 */
		अगर (PageOffline(page) && page_count(page))
			वापस -EBUSY;

		अगर (!PageHuge(page))
			जारी;
		head = compound_head(page);
		/*
		 * This test is racy as we hold no reference or lock.  The
		 * hugetlb page could have been मुक्त'ed and head is no दीर्घer
		 * a hugetlb page beक्रमe the following check.  In such unlikely
		 * हालs false positives and negatives are possible.  Calling
		 * code must deal with these scenarios.
		 */
		अगर (HPageMigratable(head))
			जाओ found;
		skip = compound_nr(head) - (page - head);
		pfn += skip - 1;
	पूर्ण
	वापस -ENOENT;
found:
	*movable_pfn = pfn;
	वापस 0;
पूर्ण

अटल पूर्णांक
करो_migrate_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn;
	काष्ठा page *page, *head;
	पूर्णांक ret = 0;
	LIST_HEAD(source);

	क्रम (pfn = start_pfn; pfn < end_pfn; pfn++) अणु
		अगर (!pfn_valid(pfn))
			जारी;
		page = pfn_to_page(pfn);
		head = compound_head(page);

		अगर (PageHuge(page)) अणु
			pfn = page_to_pfn(head) + compound_nr(head) - 1;
			isolate_huge_page(head, &source);
			जारी;
		पूर्ण अन्यथा अगर (PageTransHuge(page))
			pfn = page_to_pfn(head) + thp_nr_pages(page) - 1;

		/*
		 * HWPoison pages have elevated reference counts so the migration would
		 * fail on them. It also करोesn't make any sense to migrate them in the
		 * first place. Still try to unmap such a page in हाल it is still mapped
		 * (e.g. current hwpoison implementation करोesn't unmap KSM pages but keep
		 * the unmap as the catch all safety net).
		 */
		अगर (PageHWPoison(page)) अणु
			अगर (WARN_ON(PageLRU(page)))
				isolate_lru_page(page);
			अगर (page_mapped(page))
				try_to_unmap(page, TTU_IGNORE_MLOCK);
			जारी;
		पूर्ण

		अगर (!get_page_unless_zero(page))
			जारी;
		/*
		 * We can skip मुक्त pages. And we can deal with pages on
		 * LRU and non-lru movable pages.
		 */
		अगर (PageLRU(page))
			ret = isolate_lru_page(page);
		अन्यथा
			ret = isolate_movable_page(page, ISOLATE_UNEVICTABLE);
		अगर (!ret) अणु /* Success */
			list_add_tail(&page->lru, &source);
			अगर (!__PageMovable(page))
				inc_node_page_state(page, NR_ISOLATED_ANON +
						    page_is_file_lru(page));

		पूर्ण अन्यथा अणु
			pr_warn("failed to isolate pfn %lx\n", pfn);
			dump_page(page, "isolation failed");
		पूर्ण
		put_page(page);
	पूर्ण
	अगर (!list_empty(&source)) अणु
		nodemask_t nmask = node_states[N_MEMORY];
		काष्ठा migration_target_control mtc = अणु
			.nmask = &nmask,
			.gfp_mask = GFP_USER | __GFP_MOVABLE | __GFP_RETRY_MAYFAIL,
		पूर्ण;

		/*
		 * We have checked that migration range is on a single zone so
		 * we can use the nid of the first page to all the others.
		 */
		mtc.nid = page_to_nid(list_first_entry(&source, काष्ठा page, lru));

		/*
		 * try to allocate from a dअगरferent node but reuse this node
		 * अगर there are no other online nodes to be used (e.g. we are
		 * offlining a part of the only existing node)
		 */
		node_clear(mtc.nid, nmask);
		अगर (nodes_empty(nmask))
			node_set(mtc.nid, nmask);
		ret = migrate_pages(&source, alloc_migration_target, शून्य,
			(अचिन्हित दीर्घ)&mtc, MIGRATE_SYNC, MR_MEMORY_HOTPLUG);
		अगर (ret) अणु
			list_क्रम_each_entry(page, &source, lru) अणु
				pr_warn("migrating pfn %lx failed ret:%d ",
				       page_to_pfn(page), ret);
				dump_page(page, "migration failure");
			पूर्ण
			putback_movable_pages(&source);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init cmdline_parse_movable_node(अक्षर *p)
अणु
	movable_node_enabled = true;
	वापस 0;
पूर्ण
early_param("movable_node", cmdline_parse_movable_node);

/* check which state of node_states will be changed when offline memory */
अटल व्योम node_states_check_changes_offline(अचिन्हित दीर्घ nr_pages,
		काष्ठा zone *zone, काष्ठा memory_notअगरy *arg)
अणु
	काष्ठा pglist_data *pgdat = zone->zone_pgdat;
	अचिन्हित दीर्घ present_pages = 0;
	क्रमागत zone_type zt;

	arg->status_change_nid = NUMA_NO_NODE;
	arg->status_change_nid_normal = NUMA_NO_NODE;
	arg->status_change_nid_high = NUMA_NO_NODE;

	/*
	 * Check whether node_states[N_NORMAL_MEMORY] will be changed.
	 * If the memory to be offline is within the range
	 * [0..ZONE_NORMAL], and it is the last present memory there,
	 * the zones in that range will become empty after the offlining,
	 * thus we can determine that we need to clear the node from
	 * node_states[N_NORMAL_MEMORY].
	 */
	क्रम (zt = 0; zt <= ZONE_NORMAL; zt++)
		present_pages += pgdat->node_zones[zt].present_pages;
	अगर (zone_idx(zone) <= ZONE_NORMAL && nr_pages >= present_pages)
		arg->status_change_nid_normal = zone_to_nid(zone);

#अगर_घोषित CONFIG_HIGHMEM
	/*
	 * node_states[N_HIGH_MEMORY] contains nodes which
	 * have normal memory or high memory.
	 * Here we add the present_pages beदीर्घing to ZONE_HIGHMEM.
	 * If the zone is within the range of [0..ZONE_HIGHMEM), and
	 * we determine that the zones in that range become empty,
	 * we need to clear the node क्रम N_HIGH_MEMORY.
	 */
	present_pages += pgdat->node_zones[ZONE_HIGHMEM].present_pages;
	अगर (zone_idx(zone) <= ZONE_HIGHMEM && nr_pages >= present_pages)
		arg->status_change_nid_high = zone_to_nid(zone);
#पूर्ण_अगर

	/*
	 * We have accounted the pages from [0..ZONE_NORMAL), and
	 * in हाल of CONFIG_HIGHMEM the pages from ZONE_HIGHMEM
	 * as well.
	 * Here we count the possible pages from ZONE_MOVABLE.
	 * If after having accounted all the pages, we see that the nr_pages
	 * to be offlined is over or equal to the accounted pages,
	 * we know that the node will become empty, and so, we can clear
	 * it क्रम N_MEMORY as well.
	 */
	present_pages += pgdat->node_zones[ZONE_MOVABLE].present_pages;

	अगर (nr_pages >= present_pages)
		arg->status_change_nid = zone_to_nid(zone);
पूर्ण

अटल व्योम node_states_clear_node(पूर्णांक node, काष्ठा memory_notअगरy *arg)
अणु
	अगर (arg->status_change_nid_normal >= 0)
		node_clear_state(node, N_NORMAL_MEMORY);

	अगर (arg->status_change_nid_high >= 0)
		node_clear_state(node, N_HIGH_MEMORY);

	अगर (arg->status_change_nid >= 0)
		node_clear_state(node, N_MEMORY);
पूर्ण

अटल पूर्णांक count_प्रणाली_ram_pages_cb(अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ nr_pages, व्योम *data)
अणु
	अचिन्हित दीर्घ *nr_प्रणाली_ram_pages = data;

	*nr_प्रणाली_ram_pages += nr_pages;
	वापस 0;
पूर्ण

पूर्णांक __ref offline_pages(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages)
अणु
	स्थिर अचिन्हित दीर्घ end_pfn = start_pfn + nr_pages;
	अचिन्हित दीर्घ pfn, प्रणाली_ram_pages = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा zone *zone;
	काष्ठा memory_notअगरy arg;
	पूर्णांक ret, node;
	अक्षर *reason;

	/*
	 * अणुon,offपूर्णlining is स्थिरrained to full memory sections (or more
	 * precisly to memory blocks from the user space POV).
	 * memmap_on_memory is an exception because it reserves initial part
	 * of the physical memory space क्रम vmemmaps. That space is pageblock
	 * aligned.
	 */
	अगर (WARN_ON_ONCE(!nr_pages ||
			 !IS_ALIGNED(start_pfn, pageblock_nr_pages) ||
			 !IS_ALIGNED(start_pfn + nr_pages, PAGES_PER_SECTION)))
		वापस -EINVAL;

	mem_hotplug_begin();

	/*
	 * Don't allow to offline memory blocks that contain holes.
	 * Consequently, memory blocks with holes can never get onlined
	 * via the hotplug path - online_pages() - as hotplugged memory has
	 * no holes. This way, we e.g., करोn't have to worry about marking
	 * memory holes PG_reserved, करोn't need pfn_valid() checks, and can
	 * aव्योम using walk_प्रणाली_ram_range() later.
	 */
	walk_प्रणाली_ram_range(start_pfn, nr_pages, &प्रणाली_ram_pages,
			      count_प्रणाली_ram_pages_cb);
	अगर (प्रणाली_ram_pages != nr_pages) अणु
		ret = -EINVAL;
		reason = "memory holes";
		जाओ failed_removal;
	पूर्ण

	/* This makes hotplug much easier...and पढ़ोable.
	   we assume this क्रम now. .*/
	zone = test_pages_in_a_zone(start_pfn, end_pfn);
	अगर (!zone) अणु
		ret = -EINVAL;
		reason = "multizone range";
		जाओ failed_removal;
	पूर्ण
	node = zone_to_nid(zone);

	/*
	 * Disable pcplists so that page isolation cannot race with मुक्तing
	 * in a way that pages from isolated pageblock are left on pcplists.
	 */
	zone_pcp_disable(zone);
	lru_cache_disable();

	/* set above range as isolated */
	ret = start_isolate_page_range(start_pfn, end_pfn,
				       MIGRATE_MOVABLE,
				       MEMORY_OFFLINE | REPORT_FAILURE);
	अगर (ret) अणु
		reason = "failure to isolate range";
		जाओ failed_removal_pcplists_disabled;
	पूर्ण

	arg.start_pfn = start_pfn;
	arg.nr_pages = nr_pages;
	node_states_check_changes_offline(nr_pages, zone, &arg);

	ret = memory_notअगरy(MEM_GOING_OFFLINE, &arg);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret) अणु
		reason = "notifier failure";
		जाओ failed_removal_isolated;
	पूर्ण

	करो अणु
		pfn = start_pfn;
		करो अणु
			अगर (संकेत_pending(current)) अणु
				ret = -EINTR;
				reason = "signal backoff";
				जाओ failed_removal_isolated;
			पूर्ण

			cond_resched();

			ret = scan_movable_pages(pfn, end_pfn, &pfn);
			अगर (!ret) अणु
				/*
				 * TODO: fatal migration failures should bail
				 * out
				 */
				करो_migrate_range(pfn, end_pfn);
			पूर्ण
		पूर्ण जबतक (!ret);

		अगर (ret != -ENOENT) अणु
			reason = "unmovable page";
			जाओ failed_removal_isolated;
		पूर्ण

		/*
		 * Dissolve मुक्त hugepages in the memory block beक्रमe करोing
		 * offlining actually in order to make hugetlbfs's object
		 * counting consistent.
		 */
		ret = dissolve_मुक्त_huge_pages(start_pfn, end_pfn);
		अगर (ret) अणु
			reason = "failure to dissolve huge pages";
			जाओ failed_removal_isolated;
		पूर्ण

		ret = test_pages_isolated(start_pfn, end_pfn, MEMORY_OFFLINE);

	पूर्ण जबतक (ret);

	/* Mark all sections offline and हटाओ मुक्त pages from the buddy. */
	__offline_isolated_pages(start_pfn, end_pfn);
	pr_debug("Offlined Pages %ld\n", nr_pages);

	/*
	 * The memory sections are marked offline, and the pageblock flags
	 * effectively stale; nobody should be touching them. Fixup the number
	 * of isolated pageblocks, memory onlining will properly revert this.
	 */
	spin_lock_irqsave(&zone->lock, flags);
	zone->nr_isolate_pageblock -= nr_pages / pageblock_nr_pages;
	spin_unlock_irqrestore(&zone->lock, flags);

	lru_cache_enable();
	zone_pcp_enable(zone);

	/* removal success */
	adjust_managed_page_count(pfn_to_page(start_pfn), -nr_pages);
	adjust_present_page_count(zone, -nr_pages);

	init_per_zone_wmark_min();

	अगर (!populated_zone(zone)) अणु
		zone_pcp_reset(zone);
		build_all_zonelists(शून्य);
	पूर्ण अन्यथा
		zone_pcp_update(zone);

	node_states_clear_node(node, &arg);
	अगर (arg.status_change_nid >= 0) अणु
		kswapd_stop(node);
		kcompactd_stop(node);
	पूर्ण

	ग_लिखोback_set_ratelimit();

	memory_notअगरy(MEM_OFFLINE, &arg);
	हटाओ_pfn_range_from_zone(zone, start_pfn, nr_pages);
	mem_hotplug_करोne();
	वापस 0;

failed_removal_isolated:
	unकरो_isolate_page_range(start_pfn, end_pfn, MIGRATE_MOVABLE);
	memory_notअगरy(MEM_CANCEL_OFFLINE, &arg);
failed_removal_pcplists_disabled:
	zone_pcp_enable(zone);
failed_removal:
	pr_debug("memory offlining [mem %#010llx-%#010llx] failed due to %s\n",
		 (अचिन्हित दीर्घ दीर्घ) start_pfn << PAGE_SHIFT,
		 ((अचिन्हित दीर्घ दीर्घ) end_pfn << PAGE_SHIFT) - 1,
		 reason);
	/* pushback to मुक्त area */
	mem_hotplug_करोne();
	वापस ret;
पूर्ण

अटल पूर्णांक check_memblock_offlined_cb(काष्ठा memory_block *mem, व्योम *arg)
अणु
	पूर्णांक ret = !is_memblock_offlined(mem);

	अगर (unlikely(ret)) अणु
		phys_addr_t beginpa, endpa;

		beginpa = PFN_PHYS(section_nr_to_pfn(mem->start_section_nr));
		endpa = beginpa + memory_block_size_bytes() - 1;
		pr_warn("removing memory fails, because memory [%pa-%pa] is onlined\n",
			&beginpa, &endpa);

		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_nr_vmemmap_pages_cb(काष्ठा memory_block *mem, व्योम *arg)
अणु
	/*
	 * If not set, जारी with the next block.
	 */
	वापस mem->nr_vmemmap_pages;
पूर्ण

अटल पूर्णांक check_cpu_on_node(pg_data_t *pgdat)
अणु
	पूर्णांक cpu;

	क्रम_each_present_cpu(cpu) अणु
		अगर (cpu_to_node(cpu) == pgdat->node_id)
			/*
			 * the cpu on this node isn't removed, and we can't
			 * offline this node.
			 */
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_no_memblock_क्रम_node_cb(काष्ठा memory_block *mem, व्योम *arg)
अणु
	पूर्णांक nid = *(पूर्णांक *)arg;

	/*
	 * If a memory block beदीर्घs to multiple nodes, the stored nid is not
	 * reliable. However, such blocks are always online (e.g., cannot get
	 * offlined) and, thereक्रमe, are still spanned by the node.
	 */
	वापस mem->nid == nid ? -EEXIST : 0;
पूर्ण

/**
 * try_offline_node
 * @nid: the node ID
 *
 * Offline a node अगर all memory sections and cpus of the node are हटाओd.
 *
 * NOTE: The caller must call lock_device_hotplug() to serialize hotplug
 * and online/offline operations beक्रमe this call.
 */
व्योम try_offline_node(पूर्णांक nid)
अणु
	pg_data_t *pgdat = NODE_DATA(nid);
	पूर्णांक rc;

	/*
	 * If the node still spans pages (especially ZONE_DEVICE), करोn't
	 * offline it. A node spans memory after move_pfn_range_to_zone(),
	 * e.g., after the memory block was onlined.
	 */
	अगर (pgdat->node_spanned_pages)
		वापस;

	/*
	 * Especially offline memory blocks might not be spanned by the
	 * node. They will get spanned by the node once they get onlined.
	 * However, they link to the node in sysfs and can get onlined later.
	 */
	rc = क्रम_each_memory_block(&nid, check_no_memblock_क्रम_node_cb);
	अगर (rc)
		वापस;

	अगर (check_cpu_on_node(pgdat))
		वापस;

	/*
	 * all memory/cpu of this node are हटाओd, we can offline this
	 * node now.
	 */
	node_set_offline(nid);
	unरेजिस्टर_one_node(nid);
पूर्ण
EXPORT_SYMBOL(try_offline_node);

अटल पूर्णांक __ref try_हटाओ_memory(पूर्णांक nid, u64 start, u64 size)
अणु
	पूर्णांक rc = 0;
	काष्ठा vmem_alपंचांगap mhp_alपंचांगap = अणुपूर्ण;
	काष्ठा vmem_alपंचांगap *alपंचांगap = शून्य;
	अचिन्हित दीर्घ nr_vmemmap_pages;

	BUG_ON(check_hotplug_memory_range(start, size));

	/*
	 * All memory blocks must be offlined beक्रमe removing memory.  Check
	 * whether all memory blocks in question are offline and वापस error
	 * अगर this is not the हाल.
	 */
	rc = walk_memory_blocks(start, size, शून्य, check_memblock_offlined_cb);
	अगर (rc)
		वापस rc;

	/*
	 * We only support removing memory added with MHP_MEMMAP_ON_MEMORY in
	 * the same granularity it was added - a single memory block.
	 */
	अगर (memmap_on_memory) अणु
		nr_vmemmap_pages = walk_memory_blocks(start, size, शून्य,
						      get_nr_vmemmap_pages_cb);
		अगर (nr_vmemmap_pages) अणु
			अगर (size != memory_block_size_bytes()) अणु
				pr_warn("Refuse to remove %#llx - %#llx,"
					"wrong granularity\n",
					start, start + size);
				वापस -EINVAL;
			पूर्ण

			/*
			 * Let हटाओ_pmd_table->मुक्त_hugepage_table करो the
			 * right thing अगर we used vmem_alपंचांगap when hot-adding
			 * the range.
			 */
			mhp_alपंचांगap.alloc = nr_vmemmap_pages;
			alपंचांगap = &mhp_alपंचांगap;
		पूर्ण
	पूर्ण

	/* हटाओ memmap entry */
	firmware_map_हटाओ(start, start + size, "System RAM");

	/*
	 * Memory block device removal under the device_hotplug_lock is
	 * a barrier against racing online attempts.
	 */
	हटाओ_memory_block_devices(start, size);

	mem_hotplug_begin();

	arch_हटाओ_memory(nid, start, size, alपंचांगap);

	अगर (IS_ENABLED(CONFIG_ARCH_KEEP_MEMBLOCK)) अणु
		memblock_मुक्त(start, size);
		memblock_हटाओ(start, size);
	पूर्ण

	release_mem_region_adjustable(start, size);

	try_offline_node(nid);

	mem_hotplug_करोne();
	वापस 0;
पूर्ण

/**
 * हटाओ_memory
 * @nid: the node ID
 * @start: physical address of the region to हटाओ
 * @size: size of the region to हटाओ
 *
 * NOTE: The caller must call lock_device_hotplug() to serialize hotplug
 * and online/offline operations beक्रमe this call, as required by
 * try_offline_node().
 */
व्योम __हटाओ_memory(पूर्णांक nid, u64 start, u64 size)
अणु

	/*
	 * trigger BUG() अगर some memory is not offlined prior to calling this
	 * function
	 */
	अगर (try_हटाओ_memory(nid, start, size))
		BUG();
पूर्ण

/*
 * Remove memory अगर every memory block is offline, otherwise वापस -EBUSY is
 * some memory is not offline
 */
पूर्णांक हटाओ_memory(पूर्णांक nid, u64 start, u64 size)
अणु
	पूर्णांक rc;

	lock_device_hotplug();
	rc  = try_हटाओ_memory(nid, start, size);
	unlock_device_hotplug();

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(हटाओ_memory);

अटल पूर्णांक try_offline_memory_block(काष्ठा memory_block *mem, व्योम *arg)
अणु
	uपूर्णांक8_t online_type = MMOP_ONLINE_KERNEL;
	uपूर्णांक8_t **online_types = arg;
	काष्ठा page *page;
	पूर्णांक rc;

	/*
	 * Sense the online_type via the zone of the memory block. Offlining
	 * with multiple zones within one memory block will be rejected
	 * by offlining code ... so we करोn't care about that.
	 */
	page = pfn_to_online_page(section_nr_to_pfn(mem->start_section_nr));
	अगर (page && zone_idx(page_zone(page)) == ZONE_MOVABLE)
		online_type = MMOP_ONLINE_MOVABLE;

	rc = device_offline(&mem->dev);
	/*
	 * Default is MMOP_OFFLINE - change it only अगर offlining succeeded,
	 * so try_reonline_memory_block() can करो the right thing.
	 */
	अगर (!rc)
		**online_types = online_type;

	(*online_types)++;
	/* Ignore अगर alपढ़ोy offline. */
	वापस rc < 0 ? rc : 0;
पूर्ण

अटल पूर्णांक try_reonline_memory_block(काष्ठा memory_block *mem, व्योम *arg)
अणु
	uपूर्णांक8_t **online_types = arg;
	पूर्णांक rc;

	अगर (**online_types != MMOP_OFFLINE) अणु
		mem->online_type = **online_types;
		rc = device_online(&mem->dev);
		अगर (rc < 0)
			pr_warn("%s: Failed to re-online memory: %d",
				__func__, rc);
	पूर्ण

	/* Continue processing all reमुख्यing memory blocks. */
	(*online_types)++;
	वापस 0;
पूर्ण

/*
 * Try to offline and हटाओ memory. Might take a दीर्घ समय to finish in हाल
 * memory is still in use. Primarily useful क्रम memory devices that logically
 * unplugged all memory (so it's no दीर्घer in use) and want to offline + हटाओ
 * that memory.
 */
पूर्णांक offline_and_हटाओ_memory(पूर्णांक nid, u64 start, u64 size)
अणु
	स्थिर अचिन्हित दीर्घ mb_count = size / memory_block_size_bytes();
	uपूर्णांक8_t *online_types, *पंचांगp;
	पूर्णांक rc;

	अगर (!IS_ALIGNED(start, memory_block_size_bytes()) ||
	    !IS_ALIGNED(size, memory_block_size_bytes()) || !size)
		वापस -EINVAL;

	/*
	 * We'll remember the old online type of each memory block, so we can
	 * try to revert whatever we did when offlining one memory block fails
	 * after offlining some others succeeded.
	 */
	online_types = kदो_स्मृति_array(mb_count, माप(*online_types),
				     GFP_KERNEL);
	अगर (!online_types)
		वापस -ENOMEM;
	/*
	 * Initialize all states to MMOP_OFFLINE, so when we पात processing in
	 * try_offline_memory_block(), we'll skip all unprocessed blocks in
	 * try_reonline_memory_block().
	 */
	स_रखो(online_types, MMOP_OFFLINE, mb_count);

	lock_device_hotplug();

	पंचांगp = online_types;
	rc = walk_memory_blocks(start, size, &पंचांगp, try_offline_memory_block);

	/*
	 * In हाल we succeeded to offline all memory, हटाओ it.
	 * This cannot fail as it cannot get onlined in the meanसमय.
	 */
	अगर (!rc) अणु
		rc = try_हटाओ_memory(nid, start, size);
		अगर (rc)
			pr_err("%s: Failed to remove memory: %d", __func__, rc);
	पूर्ण

	/*
	 * Rollback what we did. While memory onlining might theoretically fail
	 * (nacked by a notअगरier), it barely ever happens.
	 */
	अगर (rc) अणु
		पंचांगp = online_types;
		walk_memory_blocks(start, size, &पंचांगp,
				   try_reonline_memory_block);
	पूर्ण
	unlock_device_hotplug();

	kमुक्त(online_types);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(offline_and_हटाओ_memory);
#पूर्ण_अगर /* CONFIG_MEMORY_HOTREMOVE */
