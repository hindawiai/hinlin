<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MEMORY_HOTPLUG_H
#घोषणा __LINUX_MEMORY_HOTPLUG_H

#समावेश <linux/mmzone.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/bug.h>

काष्ठा page;
काष्ठा zone;
काष्ठा pglist_data;
काष्ठा mem_section;
काष्ठा memory_block;
काष्ठा resource;
काष्ठा vmem_alपंचांगap;

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
काष्ठा page *pfn_to_online_page(अचिन्हित दीर्घ pfn);

/*
 * Types क्रम मुक्त booपंचांगem stored in page->lru.next. These have to be in
 * some अक्रमom range in अचिन्हित दीर्घ space क्रम debugging purposes.
 */
क्रमागत अणु
	MEMORY_HOTPLUG_MIN_BOOTMEM_TYPE = 12,
	SECTION_INFO = MEMORY_HOTPLUG_MIN_BOOTMEM_TYPE,
	MIX_SECTION_INFO,
	NODE_INFO,
	MEMORY_HOTPLUG_MAX_BOOTMEM_TYPE = NODE_INFO,
पूर्ण;

/* Types क्रम control the zone type of onlined and offlined memory */
क्रमागत अणु
	/* Offline the memory. */
	MMOP_OFFLINE = 0,
	/* Online the memory. Zone depends, see शेष_zone_क्रम_pfn(). */
	MMOP_ONLINE,
	/* Online the memory to ZONE_NORMAL. */
	MMOP_ONLINE_KERNEL,
	/* Online the memory to ZONE_MOVABLE. */
	MMOP_ONLINE_MOVABLE,
पूर्ण;

/* Flags क्रम add_memory() and मित्रs to specअगरy memory hotplug details. */
प्रकार पूर्णांक __bitwise mhp_t;

/* No special request */
#घोषणा MHP_NONE		((__क्रमce mhp_t)0)
/*
 * Allow merging of the added System RAM resource with adjacent,
 * mergeable resources. After a successful call to add_memory_resource()
 * with this flag set, the resource poपूर्णांकer must no दीर्घer be used as it
 * might be stale, or the resource might have changed.
 */
#घोषणा MHP_MERGE_RESOURCE	((__क्रमce mhp_t)BIT(0))

/*
 * We want memmap (काष्ठा page array) to be self contained.
 * To करो so, we will use the beginning of the hot-added range to build
 * the page tables क्रम the memmap array that describes the entire range.
 * Only selected architectures support it with SPARSE_VMEMMAP.
 */
#घोषणा MHP_MEMMAP_ON_MEMORY   ((__क्रमce mhp_t)BIT(1))

/*
 * Extended parameters क्रम memory hotplug:
 * alपंचांगap: alternative allocator क्रम memmap array (optional)
 * pgprot: page protection flags to apply to newly created page tables
 *	(required)
 */
काष्ठा mhp_params अणु
	काष्ठा vmem_alपंचांगap *alपंचांगap;
	pgprot_t pgprot;
पूर्ण;

bool mhp_range_allowed(u64 start, u64 size, bool need_mapping);
काष्ठा range mhp_get_pluggable_range(bool need_mapping);

/*
 * Zone resizing functions
 *
 * Note: any attempt to resize a zone should has pgdat_resize_lock()
 * zone_span_ग_लिखोlock() both held. This ensure the size of a zone
 * can't be changed जबतक pgdat_resize_lock() held.
 */
अटल अंतरभूत अचिन्हित zone_span_seqbegin(काष्ठा zone *zone)
अणु
	वापस पढ़ो_seqbegin(&zone->span_seqlock);
पूर्ण
अटल अंतरभूत पूर्णांक zone_span_seqretry(काष्ठा zone *zone, अचिन्हित iv)
अणु
	वापस पढ़ो_seqretry(&zone->span_seqlock, iv);
पूर्ण
अटल अंतरभूत व्योम zone_span_ग_लिखोlock(काष्ठा zone *zone)
अणु
	ग_लिखो_seqlock(&zone->span_seqlock);
पूर्ण
अटल अंतरभूत व्योम zone_span_ग_लिखोunlock(काष्ठा zone *zone)
अणु
	ग_लिखो_sequnlock(&zone->span_seqlock);
पूर्ण
अटल अंतरभूत व्योम zone_seqlock_init(काष्ठा zone *zone)
अणु
	seqlock_init(&zone->span_seqlock);
पूर्ण
बाह्य पूर्णांक zone_grow_मुक्त_lists(काष्ठा zone *zone, अचिन्हित दीर्घ new_nr_pages);
बाह्य पूर्णांक zone_grow_रुकोqueues(काष्ठा zone *zone, अचिन्हित दीर्घ nr_pages);
बाह्य पूर्णांक add_one_highpage(काष्ठा page *page, पूर्णांक pfn, पूर्णांक bad_ppro);
बाह्य व्योम adjust_present_page_count(काष्ठा zone *zone, दीर्घ nr_pages);
/* VM पूर्णांकerface that may be used by firmware पूर्णांकerface */
बाह्य पूर्णांक mhp_init_memmap_on_memory(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
				     काष्ठा zone *zone);
बाह्य व्योम mhp_deinit_memmap_on_memory(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages);
बाह्य पूर्णांक online_pages(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
			काष्ठा zone *zone);
बाह्य काष्ठा zone *test_pages_in_a_zone(अचिन्हित दीर्घ start_pfn,
					 अचिन्हित दीर्घ end_pfn);
बाह्य व्योम __offline_isolated_pages(अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ end_pfn);

प्रकार व्योम (*online_page_callback_t)(काष्ठा page *page, अचिन्हित पूर्णांक order);

बाह्य व्योम generic_online_page(काष्ठा page *page, अचिन्हित पूर्णांक order);
बाह्य पूर्णांक set_online_page_callback(online_page_callback_t callback);
बाह्य पूर्णांक restore_online_page_callback(online_page_callback_t callback);

बाह्य पूर्णांक try_online_node(पूर्णांक nid);

बाह्य पूर्णांक arch_add_memory(पूर्णांक nid, u64 start, u64 size,
			   काष्ठा mhp_params *params);
बाह्य u64 max_mem_size;

बाह्य पूर्णांक mhp_online_type_from_str(स्थिर अक्षर *str);

/* Default online_type (MMOP_*) when new memory blocks are added. */
बाह्य पूर्णांक mhp_शेष_online_type;
/* If movable_node boot option specअगरied */
बाह्य bool movable_node_enabled;
अटल अंतरभूत bool movable_node_is_enabled(व्योम)
अणु
	वापस movable_node_enabled;
पूर्ण

बाह्य व्योम arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			       काष्ठा vmem_alपंचांगap *alपंचांगap);
बाह्य व्योम __हटाओ_pages(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
			   काष्ठा vmem_alपंचांगap *alपंचांगap);

/* reasonably generic पूर्णांकerface to expand the physical pages */
बाह्य पूर्णांक __add_pages(पूर्णांक nid, अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
		       काष्ठा mhp_params *params);

#अगर_अघोषित CONFIG_ARCH_HAS_ADD_PAGES
अटल अंतरभूत पूर्णांक add_pages(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ nr_pages, काष्ठा mhp_params *params)
अणु
	वापस __add_pages(nid, start_pfn, nr_pages, params);
पूर्ण
#अन्यथा /* ARCH_HAS_ADD_PAGES */
पूर्णांक add_pages(पूर्णांक nid, अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
	      काष्ठा mhp_params *params);
#पूर्ण_अगर /* ARCH_HAS_ADD_PAGES */

#अगर_घोषित CONFIG_HAVE_ARCH_NODEDATA_EXTENSION
/*
 * For supporting node-hotadd, we have to allocate a new pgdat.
 *
 * If an arch has generic style NODE_DATA(),
 * node_data[nid] = kzalloc() works well. But it depends on the architecture.
 *
 * In general, generic_alloc_nodedata() is used.
 * Now, arch_मुक्त_nodedata() is just defined क्रम error path of node_hot_add.
 *
 */
बाह्य pg_data_t *arch_alloc_nodedata(पूर्णांक nid);
बाह्य व्योम arch_मुक्त_nodedata(pg_data_t *pgdat);
बाह्य व्योम arch_refresh_nodedata(पूर्णांक nid, pg_data_t *pgdat);

#अन्यथा /* CONFIG_HAVE_ARCH_NODEDATA_EXTENSION */

#घोषणा arch_alloc_nodedata(nid)	generic_alloc_nodedata(nid)
#घोषणा arch_मुक्त_nodedata(pgdat)	generic_मुक्त_nodedata(pgdat)

#अगर_घोषित CONFIG_NUMA
/*
 * If ARCH_HAS_NODEDATA_EXTENSION=n, this func is used to allocate pgdat.
 * XXX: kदो_स्मृति_node() can't work well to get new node's memory at this समय.
 *	Because, pgdat क्रम the new node is not allocated/initialized yet itself.
 *	To use new node's memory, more consideration will be necessary.
 */
#घोषणा generic_alloc_nodedata(nid)				\
(अणु								\
	kzalloc(माप(pg_data_t), GFP_KERNEL);			\
पूर्ण)
/*
 * This definition is just क्रम error path in node hotadd.
 * For node hotहटाओ, we have to replace this.
 */
#घोषणा generic_मुक्त_nodedata(pgdat)	kमुक्त(pgdat)

बाह्य pg_data_t *node_data[];
अटल अंतरभूत व्योम arch_refresh_nodedata(पूर्णांक nid, pg_data_t *pgdat)
अणु
	node_data[nid] = pgdat;
पूर्ण

#अन्यथा /* !CONFIG_NUMA */

/* never called */
अटल अंतरभूत pg_data_t *generic_alloc_nodedata(पूर्णांक nid)
अणु
	BUG();
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम generic_मुक्त_nodedata(pg_data_t *pgdat)
अणु
पूर्ण
अटल अंतरभूत व्योम arch_refresh_nodedata(पूर्णांक nid, pg_data_t *pgdat)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_NODEDATA_EXTENSION */

#अगर_घोषित CONFIG_HAVE_BOOTMEM_INFO_NODE
बाह्य व्योम __init रेजिस्टर_page_booपंचांगem_info_node(काष्ठा pglist_data *pgdat);
#अन्यथा
अटल अंतरभूत व्योम रेजिस्टर_page_booपंचांगem_info_node(काष्ठा pglist_data *pgdat)
अणु
पूर्ण
#पूर्ण_अगर
बाह्य व्योम put_page_booपंचांगem(काष्ठा page *page);
बाह्य व्योम get_page_booपंचांगem(अचिन्हित दीर्घ ingo, काष्ठा page *page,
			     अचिन्हित दीर्घ type);

व्योम get_online_mems(व्योम);
व्योम put_online_mems(व्योम);

व्योम mem_hotplug_begin(व्योम);
व्योम mem_hotplug_करोne(व्योम);

#अन्यथा /* ! CONFIG_MEMORY_HOTPLUG */
#घोषणा pfn_to_online_page(pfn)			\
(अणु						\
	काष्ठा page *___page = शून्य;		\
	अगर (pfn_valid(pfn))			\
		___page = pfn_to_page(pfn);	\
	___page;				\
 पूर्ण)

अटल अंतरभूत अचिन्हित zone_span_seqbegin(काष्ठा zone *zone)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक zone_span_seqretry(काष्ठा zone *zone, अचिन्हित iv)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम zone_span_ग_लिखोlock(काष्ठा zone *zone) अणुपूर्ण
अटल अंतरभूत व्योम zone_span_ग_लिखोunlock(काष्ठा zone *zone) अणुपूर्ण
अटल अंतरभूत व्योम zone_seqlock_init(काष्ठा zone *zone) अणुपूर्ण

अटल अंतरभूत व्योम रेजिस्टर_page_booपंचांगem_info_node(काष्ठा pglist_data *pgdat)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक try_online_node(पूर्णांक nid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम get_online_mems(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम put_online_mems(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम mem_hotplug_begin(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम mem_hotplug_करोne(व्योम) अणुपूर्ण

अटल अंतरभूत bool movable_node_is_enabled(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* ! CONFIG_MEMORY_HOTPLUG */

/*
 * Keep this declaration outside CONFIG_MEMORY_HOTPLUG as some
 * platक्रमms might override and use arch_get_mappable_range()
 * क्रम पूर्णांकernal non memory hotplug purposes.
 */
काष्ठा range arch_get_mappable_range(व्योम);

#अगर defined(CONFIG_MEMORY_HOTPLUG) || defined(CONFIG_DEFERRED_STRUCT_PAGE_INIT)
/*
 * pgdat resizing functions
 */
अटल अंतरभूत
व्योम pgdat_resize_lock(काष्ठा pglist_data *pgdat, अचिन्हित दीर्घ *flags)
अणु
	spin_lock_irqsave(&pgdat->node_size_lock, *flags);
पूर्ण
अटल अंतरभूत
व्योम pgdat_resize_unlock(काष्ठा pglist_data *pgdat, अचिन्हित दीर्घ *flags)
अणु
	spin_unlock_irqrestore(&pgdat->node_size_lock, *flags);
पूर्ण
अटल अंतरभूत
व्योम pgdat_resize_init(काष्ठा pglist_data *pgdat)
अणु
	spin_lock_init(&pgdat->node_size_lock);
पूर्ण
#अन्यथा /* !(CONFIG_MEMORY_HOTPLUG || CONFIG_DEFERRED_STRUCT_PAGE_INIT) */
/*
 * Stub functions क्रम when hotplug is off
 */
अटल अंतरभूत व्योम pgdat_resize_lock(काष्ठा pglist_data *p, अचिन्हित दीर्घ *f) अणुपूर्ण
अटल अंतरभूत व्योम pgdat_resize_unlock(काष्ठा pglist_data *p, अचिन्हित दीर्घ *f) अणुपूर्ण
अटल अंतरभूत व्योम pgdat_resize_init(काष्ठा pglist_data *pgdat) अणुपूर्ण
#पूर्ण_अगर /* !(CONFIG_MEMORY_HOTPLUG || CONFIG_DEFERRED_STRUCT_PAGE_INIT) */

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE

बाह्य व्योम try_offline_node(पूर्णांक nid);
बाह्य पूर्णांक offline_pages(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages);
बाह्य पूर्णांक हटाओ_memory(पूर्णांक nid, u64 start, u64 size);
बाह्य व्योम __हटाओ_memory(पूर्णांक nid, u64 start, u64 size);
बाह्य पूर्णांक offline_and_हटाओ_memory(पूर्णांक nid, u64 start, u64 size);

#अन्यथा
अटल अंतरभूत व्योम try_offline_node(पूर्णांक nid) अणुपूर्ण

अटल अंतरभूत पूर्णांक offline_pages(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक हटाओ_memory(पूर्णांक nid, u64 start, u64 size)
अणु
	वापस -EBUSY;
पूर्ण

अटल अंतरभूत व्योम __हटाओ_memory(पूर्णांक nid, u64 start, u64 size) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTREMOVE */

बाह्य व्योम set_zone_contiguous(काष्ठा zone *zone);
बाह्य व्योम clear_zone_contiguous(काष्ठा zone *zone);

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
बाह्य व्योम __ref मुक्त_area_init_core_hotplug(पूर्णांक nid);
बाह्य पूर्णांक __add_memory(पूर्णांक nid, u64 start, u64 size, mhp_t mhp_flags);
बाह्य पूर्णांक add_memory(पूर्णांक nid, u64 start, u64 size, mhp_t mhp_flags);
बाह्य पूर्णांक add_memory_resource(पूर्णांक nid, काष्ठा resource *resource,
			       mhp_t mhp_flags);
बाह्य पूर्णांक add_memory_driver_managed(पूर्णांक nid, u64 start, u64 size,
				     स्थिर अक्षर *resource_name,
				     mhp_t mhp_flags);
बाह्य व्योम move_pfn_range_to_zone(काष्ठा zone *zone, अचिन्हित दीर्घ start_pfn,
				   अचिन्हित दीर्घ nr_pages,
				   काष्ठा vmem_alपंचांगap *alपंचांगap, पूर्णांक migratetype);
बाह्य व्योम हटाओ_pfn_range_from_zone(काष्ठा zone *zone,
				       अचिन्हित दीर्घ start_pfn,
				       अचिन्हित दीर्घ nr_pages);
बाह्य bool is_memblock_offlined(काष्ठा memory_block *mem);
बाह्य पूर्णांक sparse_add_section(पूर्णांक nid, अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, काष्ठा vmem_alपंचांगap *alपंचांगap);
बाह्य व्योम sparse_हटाओ_section(काष्ठा mem_section *ms,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages,
		अचिन्हित दीर्घ map_offset, काष्ठा vmem_alपंचांगap *alपंचांगap);
बाह्य काष्ठा page *sparse_decode_mem_map(अचिन्हित दीर्घ coded_mem_map,
					  अचिन्हित दीर्घ pnum);
बाह्य काष्ठा zone *zone_क्रम_pfn_range(पूर्णांक online_type, पूर्णांक nid, अचिन्हित start_pfn,
		अचिन्हित दीर्घ nr_pages);
बाह्य पूर्णांक arch_create_linear_mapping(पूर्णांक nid, u64 start, u64 size,
				      काष्ठा mhp_params *params);
व्योम arch_हटाओ_linear_mapping(u64 start, u64 size);
बाह्य bool mhp_supports_memmap_on_memory(अचिन्हित दीर्घ size);
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

#पूर्ण_अगर /* __LINUX_MEMORY_HOTPLUG_H */
