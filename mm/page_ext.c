<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/memblock.h>
#समावेश <linux/page_ext.h>
#समावेश <linux/memory.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/page_owner.h>
#समावेश <linux/page_idle.h>

/*
 * काष्ठा page extension
 *
 * This is the feature to manage memory क्रम extended data per page.
 *
 * Until now, we must modअगरy काष्ठा page itself to store extra data per page.
 * This requires rebuilding the kernel and it is really समय consuming process.
 * And, someबार, rebuild is impossible due to third party module dependency.
 * At last, enlarging काष्ठा page could cause un-wanted प्रणाली behaviour change.
 *
 * This feature is पूर्णांकended to overcome above mentioned problems. This feature
 * allocates memory क्रम extended data per page in certain place rather than
 * the काष्ठा page itself. This memory can be accessed by the accessor
 * functions provided by this code. During the boot process, it checks whether
 * allocation of huge chunk of memory is needed or not. If not, it aव्योमs
 * allocating memory at all. With this advantage, we can include this feature
 * पूर्णांकo the kernel in शेष and can aव्योम rebuild and solve related problems.
 *
 * To help these things to work well, there are two callbacks क्रम clients. One
 * is the need callback which is mandatory अगर user wants to aव्योम useless
 * memory allocation at boot-समय. The other is optional, init callback, which
 * is used to करो proper initialization after memory is allocated.
 *
 * The need callback is used to decide whether extended memory allocation is
 * needed or not. Someबार users want to deactivate some features in this
 * boot and extra memory would be unnecessary. In this हाल, to aव्योम
 * allocating huge chunk of memory, each clients represent their need of
 * extra memory through the need callback. If one of the need callbacks
 * वापसs true, it means that someone needs extra memory so that
 * page extension core should allocates memory क्रम page extension. If
 * none of need callbacks वापस true, memory isn't needed at all in this boot
 * and page extension core can skip to allocate memory. As result,
 * none of memory is wasted.
 *
 * When need callback वापसs true, page_ext checks अगर there is a request क्रम
 * extra memory through size in काष्ठा page_ext_operations. If it is non-zero,
 * extra space is allocated क्रम each page_ext entry and offset is वापसed to
 * user through offset in काष्ठा page_ext_operations.
 *
 * The init callback is used to करो proper initialization after page extension
 * is completely initialized. In sparse memory प्रणाली, extra memory is
 * allocated some समय later than memmap is allocated. In other words, lअगरeसमय
 * of memory क्रम page extension isn't same with memmap क्रम काष्ठा page.
 * Thereक्रमe, clients can't store extra data until page extension is
 * initialized, even अगर pages are allocated and used मुक्तly. This could
 * cause inadequate state of extra data per page, so, to prevent it, client
 * can utilize this callback to initialize the state of it correctly.
 */

अटल काष्ठा page_ext_operations *page_ext_ops[] = अणु
#अगर_घोषित CONFIG_PAGE_OWNER
	&page_owner_ops,
#पूर्ण_अगर
#अगर defined(CONFIG_IDLE_PAGE_TRACKING) && !defined(CONFIG_64BIT)
	&page_idle_ops,
#पूर्ण_अगर
पूर्ण;

अचिन्हित दीर्घ page_ext_size = माप(काष्ठा page_ext);

अटल अचिन्हित दीर्घ total_usage;

अटल bool __init invoke_need_callbacks(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक entries = ARRAY_SIZE(page_ext_ops);
	bool need = false;

	क्रम (i = 0; i < entries; i++) अणु
		अगर (page_ext_ops[i]->need && page_ext_ops[i]->need()) अणु
			page_ext_ops[i]->offset = page_ext_size;
			page_ext_size += page_ext_ops[i]->size;
			need = true;
		पूर्ण
	पूर्ण

	वापस need;
पूर्ण

अटल व्योम __init invoke_init_callbacks(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक entries = ARRAY_SIZE(page_ext_ops);

	क्रम (i = 0; i < entries; i++) अणु
		अगर (page_ext_ops[i]->init)
			page_ext_ops[i]->init();
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_SPARSEMEM
व्योम __init page_ext_init_flaपंचांगem_late(व्योम)
अणु
	invoke_init_callbacks();
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा page_ext *get_entry(व्योम *base, अचिन्हित दीर्घ index)
अणु
	वापस base + page_ext_size * index;
पूर्ण

#अगर_अघोषित CONFIG_SPARSEMEM


व्योम __meminit pgdat_page_ext_init(काष्ठा pglist_data *pgdat)
अणु
	pgdat->node_page_ext = शून्य;
पूर्ण

काष्ठा page_ext *lookup_page_ext(स्थिर काष्ठा page *page)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	अचिन्हित दीर्घ index;
	काष्ठा page_ext *base;

	base = NODE_DATA(page_to_nid(page))->node_page_ext;
	/*
	 * The sanity checks the page allocator करोes upon मुक्तing a
	 * page can reach here beक्रमe the page_ext arrays are
	 * allocated when feeding a range of pages to the allocator
	 * क्रम the first समय during bootup or memory hotplug.
	 */
	अगर (unlikely(!base))
		वापस शून्य;
	index = pfn - round_करोwn(node_start_pfn(page_to_nid(page)),
					MAX_ORDER_NR_PAGES);
	वापस get_entry(base, index);
पूर्ण

अटल पूर्णांक __init alloc_node_page_ext(पूर्णांक nid)
अणु
	काष्ठा page_ext *base;
	अचिन्हित दीर्घ table_size;
	अचिन्हित दीर्घ nr_pages;

	nr_pages = NODE_DATA(nid)->node_spanned_pages;
	अगर (!nr_pages)
		वापस 0;

	/*
	 * Need extra space अगर node range is not aligned with
	 * MAX_ORDER_NR_PAGES. When page allocator's buddy algorithm
	 * checks buddy's status, range could be out of exact node range.
	 */
	अगर (!IS_ALIGNED(node_start_pfn(nid), MAX_ORDER_NR_PAGES) ||
		!IS_ALIGNED(node_end_pfn(nid), MAX_ORDER_NR_PAGES))
		nr_pages += MAX_ORDER_NR_PAGES;

	table_size = page_ext_size * nr_pages;

	base = memblock_alloc_try_nid(
			table_size, PAGE_SIZE, __pa(MAX_DMA_ADDRESS),
			MEMBLOCK_ALLOC_ACCESSIBLE, nid);
	अगर (!base)
		वापस -ENOMEM;
	NODE_DATA(nid)->node_page_ext = base;
	total_usage += table_size;
	वापस 0;
पूर्ण

व्योम __init page_ext_init_flaपंचांगem(व्योम)
अणु

	पूर्णांक nid, fail;

	अगर (!invoke_need_callbacks())
		वापस;

	क्रम_each_online_node(nid)  अणु
		fail = alloc_node_page_ext(nid);
		अगर (fail)
			जाओ fail;
	पूर्ण
	pr_info("allocated %ld bytes of page_ext\n", total_usage);
	वापस;

fail:
	pr_crit("allocation of page_ext failed.\n");
	panic("Out of memory");
पूर्ण

#अन्यथा /* CONFIG_FLAT_NODE_MEM_MAP */

काष्ठा page_ext *lookup_page_ext(स्थिर काष्ठा page *page)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	काष्ठा mem_section *section = __pfn_to_section(pfn);
	/*
	 * The sanity checks the page allocator करोes upon मुक्तing a
	 * page can reach here beक्रमe the page_ext arrays are
	 * allocated when feeding a range of pages to the allocator
	 * क्रम the first समय during bootup or memory hotplug.
	 */
	अगर (!section->page_ext)
		वापस शून्य;
	वापस get_entry(section->page_ext, pfn);
पूर्ण

अटल व्योम *__meminit alloc_page_ext(माप_प्रकार size, पूर्णांक nid)
अणु
	gfp_t flags = GFP_KERNEL | __GFP_ZERO | __GFP_NOWARN;
	व्योम *addr = शून्य;

	addr = alloc_pages_exact_nid(nid, size, flags);
	अगर (addr) अणु
		kmemleak_alloc(addr, size, 1, flags);
		वापस addr;
	पूर्ण

	addr = vzalloc_node(size, nid);

	वापस addr;
पूर्ण

अटल पूर्णांक __meminit init_section_page_ext(अचिन्हित दीर्घ pfn, पूर्णांक nid)
अणु
	काष्ठा mem_section *section;
	काष्ठा page_ext *base;
	अचिन्हित दीर्घ table_size;

	section = __pfn_to_section(pfn);

	अगर (section->page_ext)
		वापस 0;

	table_size = page_ext_size * PAGES_PER_SECTION;
	base = alloc_page_ext(table_size, nid);

	/*
	 * The value stored in section->page_ext is (base - pfn)
	 * and it करोes not poपूर्णांक to the memory block allocated above,
	 * causing kmemleak false positives.
	 */
	kmemleak_not_leak(base);

	अगर (!base) अणु
		pr_err("page ext allocation failure\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * The passed "pfn" may not be aligned to SECTION.  For the calculation
	 * we need to apply a mask.
	 */
	pfn &= PAGE_SECTION_MASK;
	section->page_ext = (व्योम *)base - page_ext_size * pfn;
	total_usage += table_size;
	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल व्योम मुक्त_page_ext(व्योम *addr)
अणु
	अगर (is_vदो_स्मृति_addr(addr)) अणु
		vमुक्त(addr);
	पूर्ण अन्यथा अणु
		काष्ठा page *page = virt_to_page(addr);
		माप_प्रकार table_size;

		table_size = page_ext_size * PAGES_PER_SECTION;

		BUG_ON(PageReserved(page));
		kmemleak_मुक्त(addr);
		मुक्त_pages_exact(addr, table_size);
	पूर्ण
पूर्ण

अटल व्योम __मुक्त_page_ext(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा mem_section *ms;
	काष्ठा page_ext *base;

	ms = __pfn_to_section(pfn);
	अगर (!ms || !ms->page_ext)
		वापस;
	base = get_entry(ms->page_ext, pfn);
	मुक्त_page_ext(base);
	ms->page_ext = शून्य;
पूर्ण

अटल पूर्णांक __meminit online_page_ext(अचिन्हित दीर्घ start_pfn,
				अचिन्हित दीर्घ nr_pages,
				पूर्णांक nid)
अणु
	अचिन्हित दीर्घ start, end, pfn;
	पूर्णांक fail = 0;

	start = SECTION_ALIGN_DOWN(start_pfn);
	end = SECTION_ALIGN_UP(start_pfn + nr_pages);

	अगर (nid == NUMA_NO_NODE) अणु
		/*
		 * In this हाल, "nid" alपढ़ोy exists and contains valid memory.
		 * "start_pfn" passed to us is a pfn which is an arg क्रम
		 * online__pages(), and start_pfn should exist.
		 */
		nid = pfn_to_nid(start_pfn);
		VM_BUG_ON(!node_state(nid, N_ONLINE));
	पूर्ण

	क्रम (pfn = start; !fail && pfn < end; pfn += PAGES_PER_SECTION)
		fail = init_section_page_ext(pfn, nid);
	अगर (!fail)
		वापस 0;

	/* rollback */
	क्रम (pfn = start; pfn < end; pfn += PAGES_PER_SECTION)
		__मुक्त_page_ext(pfn);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __meminit offline_page_ext(अचिन्हित दीर्घ start_pfn,
				अचिन्हित दीर्घ nr_pages, पूर्णांक nid)
अणु
	अचिन्हित दीर्घ start, end, pfn;

	start = SECTION_ALIGN_DOWN(start_pfn);
	end = SECTION_ALIGN_UP(start_pfn + nr_pages);

	क्रम (pfn = start; pfn < end; pfn += PAGES_PER_SECTION)
		__मुक्त_page_ext(pfn);
	वापस 0;

पूर्ण

अटल पूर्णांक __meminit page_ext_callback(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा memory_notअगरy *mn = arg;
	पूर्णांक ret = 0;

	चयन (action) अणु
	हाल MEM_GOING_ONLINE:
		ret = online_page_ext(mn->start_pfn,
				   mn->nr_pages, mn->status_change_nid);
		अवरोध;
	हाल MEM_OFFLINE:
		offline_page_ext(mn->start_pfn,
				mn->nr_pages, mn->status_change_nid);
		अवरोध;
	हाल MEM_CANCEL_ONLINE:
		offline_page_ext(mn->start_pfn,
				mn->nr_pages, mn->status_change_nid);
		अवरोध;
	हाल MEM_GOING_OFFLINE:
		अवरोध;
	हाल MEM_ONLINE:
	हाल MEM_CANCEL_OFFLINE:
		अवरोध;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

#पूर्ण_अगर

व्योम __init page_ext_init(व्योम)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक nid;

	अगर (!invoke_need_callbacks())
		वापस;

	क्रम_each_node_state(nid, N_MEMORY) अणु
		अचिन्हित दीर्घ start_pfn, end_pfn;

		start_pfn = node_start_pfn(nid);
		end_pfn = node_end_pfn(nid);
		/*
		 * start_pfn and end_pfn may not be aligned to SECTION and the
		 * page->flags of out of node pages are not initialized.  So we
		 * scan [start_pfn, the biggest section's pfn < end_pfn) here.
		 */
		क्रम (pfn = start_pfn; pfn < end_pfn;
			pfn = ALIGN(pfn + 1, PAGES_PER_SECTION)) अणु

			अगर (!pfn_valid(pfn))
				जारी;
			/*
			 * Nodes's pfns can be overlapping.
			 * We know some arch can have a nodes layout such as
			 * -------------pfn-------------->
			 * N0 | N1 | N2 | N0 | N1 | N2|....
			 */
			अगर (pfn_to_nid(pfn) != nid)
				जारी;
			अगर (init_section_page_ext(pfn, nid))
				जाओ oom;
			cond_resched();
		पूर्ण
	पूर्ण
	hotplug_memory_notअगरier(page_ext_callback, 0);
	pr_info("allocated %ld bytes of page_ext\n", total_usage);
	invoke_init_callbacks();
	वापस;

oom:
	panic("Out of memory");
पूर्ण

व्योम __meminit pgdat_page_ext_init(काष्ठा pglist_data *pgdat)
अणु
पूर्ण

#पूर्ण_अगर
