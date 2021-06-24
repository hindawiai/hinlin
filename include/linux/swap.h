<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SWAP_H
#घोषणा _LINUX_SWAP_H

#समावेश <linux/spinlock.h>
#समावेश <linux/linkage.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/list.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/sched.h>
#समावेश <linux/node.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/atomic.h>
#समावेश <linux/page-flags.h>
#समावेश <uapi/linux/mempolicy.h>
#समावेश <यंत्र/page.h>

काष्ठा notअगरier_block;

काष्ठा bio;

काष्ठा pagevec;

#घोषणा SWAP_FLAG_PREFER	0x8000	/* set अगर swap priority specअगरied */
#घोषणा SWAP_FLAG_PRIO_MASK	0x7fff
#घोषणा SWAP_FLAG_PRIO_SHIFT	0
#घोषणा SWAP_FLAG_DISCARD	0x10000 /* enable discard क्रम swap */
#घोषणा SWAP_FLAG_DISCARD_ONCE	0x20000 /* discard swap area at swapon-समय */
#घोषणा SWAP_FLAG_DISCARD_PAGES 0x40000 /* discard page-clusters after use */

#घोषणा SWAP_FLAGS_VALID	(SWAP_FLAG_PRIO_MASK | SWAP_FLAG_PREFER | \
				 SWAP_FLAG_DISCARD | SWAP_FLAG_DISCARD_ONCE | \
				 SWAP_FLAG_DISCARD_PAGES)
#घोषणा SWAP_BATCH 64

अटल अंतरभूत पूर्णांक current_is_kswapd(व्योम)
अणु
	वापस current->flags & PF_KSWAPD;
पूर्ण

/*
 * MAX_SWAPखाताS defines the maximum number of swaptypes: things which can
 * be swapped to.  The swap type and the offset पूर्णांकo that swap type are
 * encoded पूर्णांकo pte's and into pgoff_t's in the swapcache.  Using five bits
 * क्रम the type means that the maximum number of swapcache pages is 27 bits
 * on 32-bit-pgoff_t architectures.  And that assumes that the architecture packs
 * the type/offset पूर्णांकo the pte as 5/27 as well.
 */
#घोषणा MAX_SWAPखाताS_SHIFT	5

/*
 * Use some of the swap files numbers क्रम other purposes. This
 * is a convenient way to hook पूर्णांकo the VM to trigger special
 * actions on faults.
 */

/*
 * Unaddressable device memory support. See include/linux/hmm.h and
 * Documentation/vm/hmm.rst. Short description is we need काष्ठा pages क्रम
 * device memory that is unaddressable (inaccessible) by CPU, so that we can
 * migrate part of a process memory to device memory.
 *
 * When a page is migrated from CPU to device, we set the CPU page table entry
 * to a special SWP_DEVICE_* entry.
 */
#अगर_घोषित CONFIG_DEVICE_PRIVATE
#घोषणा SWP_DEVICE_NUM 2
#घोषणा SWP_DEVICE_WRITE (MAX_SWAPखाताS+SWP_HWPOISON_NUM+SWP_MIGRATION_NUM)
#घोषणा SWP_DEVICE_READ (MAX_SWAPखाताS+SWP_HWPOISON_NUM+SWP_MIGRATION_NUM+1)
#अन्यथा
#घोषणा SWP_DEVICE_NUM 0
#पूर्ण_अगर

/*
 * NUMA node memory migration support
 */
#अगर_घोषित CONFIG_MIGRATION
#घोषणा SWP_MIGRATION_NUM 2
#घोषणा SWP_MIGRATION_READ	(MAX_SWAPखाताS + SWP_HWPOISON_NUM)
#घोषणा SWP_MIGRATION_WRITE	(MAX_SWAPखाताS + SWP_HWPOISON_NUM + 1)
#अन्यथा
#घोषणा SWP_MIGRATION_NUM 0
#पूर्ण_अगर

/*
 * Handling of hardware poisoned pages with memory corruption.
 */
#अगर_घोषित CONFIG_MEMORY_FAILURE
#घोषणा SWP_HWPOISON_NUM 1
#घोषणा SWP_HWPOISON		MAX_SWAPखाताS
#अन्यथा
#घोषणा SWP_HWPOISON_NUM 0
#पूर्ण_अगर

#घोषणा MAX_SWAPखाताS \
	((1 << MAX_SWAPखाताS_SHIFT) - SWP_DEVICE_NUM - \
	SWP_MIGRATION_NUM - SWP_HWPOISON_NUM)

/*
 * Magic header क्रम a swap area. The first part of the जोड़ is
 * what the swap magic looks like क्रम the old (limited to 128MB)
 * swap area क्रमmat, the second part of the जोड़ adds - in the
 * old reserved area - some extra inक्रमmation. Note that the first
 * kilobyte is reserved क्रम boot loader or disk label stuff...
 *
 * Having the magic at the end of the PAGE_SIZE makes detecting swap
 * areas somewhat tricky on machines that support multiple page sizes.
 * For 2.5 we'll probably want to move the magic to just beyond the
 * bootbits...
 */
जोड़ swap_header अणु
	काष्ठा अणु
		अक्षर reserved[PAGE_SIZE - 10];
		अक्षर magic[10];			/* SWAP-SPACE or SWAPSPACE2 */
	पूर्ण magic;
	काष्ठा अणु
		अक्षर		bootbits[1024];	/* Space क्रम disklabel etc. */
		__u32		version;
		__u32		last_page;
		__u32		nr_badpages;
		अचिन्हित अक्षर	sws_uuid[16];
		अचिन्हित अक्षर	sws_volume[16];
		__u32		padding[117];
		__u32		badpages[1];
	पूर्ण info;
पूर्ण;

/*
 * current->reclaim_state poपूर्णांकs to one of these when a task is running
 * memory reclaim
 */
काष्ठा reclaim_state अणु
	अचिन्हित दीर्घ reclaimed_slab;
पूर्ण;

#अगर_घोषित __KERNEL__

काष्ठा address_space;
काष्ठा sysinfo;
काष्ठा ग_लिखोback_control;
काष्ठा zone;

/*
 * A swap extent maps a range of a swapfile's PAGE_SIZE pages onto a range of
 * disk blocks.  A list of swap extents maps the entire swapfile.  (Where the
 * term `swapfile' refers to either a blockdevice or an IS_REG file.  Apart
 * from setup, they're handled identically.
 *
 * We always assume that blocks are of size PAGE_SIZE.
 */
काष्ठा swap_extent अणु
	काष्ठा rb_node rb_node;
	pgoff_t start_page;
	pgoff_t nr_pages;
	sector_t start_block;
पूर्ण;

/*
 * Max bad pages in the new क्रमmat..
 */
#घोषणा MAX_SWAP_BADPAGES \
	((दुरत्व(जोड़ swap_header, magic.magic) - \
	  दुरत्व(जोड़ swap_header, info.badpages)) / माप(पूर्णांक))

क्रमागत अणु
	SWP_USED	= (1 << 0),	/* is slot in swap_info[] used? */
	SWP_WRITEOK	= (1 << 1),	/* ok to ग_लिखो to this swap?	*/
	SWP_DISCARDABLE = (1 << 2),	/* blkdev support discard */
	SWP_DISCARDING	= (1 << 3),	/* now discarding a मुक्त cluster */
	SWP_SOLIDSTATE	= (1 << 4),	/* blkdev seeks are cheap */
	SWP_CONTINUED	= (1 << 5),	/* swap_map has count continuation */
	SWP_BLKDEV	= (1 << 6),	/* its a block device */
	SWP_ACTIVATED	= (1 << 7),	/* set after swap_activate success */
	SWP_FS_OPS	= (1 << 8),	/* swapfile operations go through fs */
	SWP_AREA_DISCARD = (1 << 9),	/* single-समय swap area discards */
	SWP_PAGE_DISCARD = (1 << 10),	/* मुक्तd swap page-cluster discards */
	SWP_STABLE_WRITES = (1 << 11),	/* no overग_लिखो PG_ग_लिखोback pages */
	SWP_SYNCHRONOUS_IO = (1 << 12),	/* synchronous IO is efficient */
	SWP_VALID	= (1 << 13),	/* swap is valid to be operated on? */
					/* add others here beक्रमe... */
	SWP_SCANNING	= (1 << 14),	/* refcount in scan_swap_map */
पूर्ण;

#घोषणा SWAP_CLUSTER_MAX 32UL
#घोषणा COMPACT_CLUSTER_MAX SWAP_CLUSTER_MAX

/* Bit flag in swap_map */
#घोषणा SWAP_HAS_CACHE	0x40	/* Flag page is cached, in first swap_map */
#घोषणा COUNT_CONTINUED	0x80	/* Flag swap_map continuation क्रम full count */

/* Special value in first swap_map */
#घोषणा SWAP_MAP_MAX	0x3e	/* Max count */
#घोषणा SWAP_MAP_BAD	0x3f	/* Note page is bad */
#घोषणा SWAP_MAP_SHMEM	0xbf	/* Owned by shmem/पंचांगpfs */

/* Special value in each swap_map continuation */
#घोषणा SWAP_CONT_MAX	0x7f	/* Max count */

/*
 * We use this to track usage of a cluster. A cluster is a block of swap disk
 * space with SWAPखाता_CLUSTER pages दीर्घ and naturally aligns in disk. All
 * मुक्त clusters are organized पूर्णांकo a list. We fetch an entry from the list to
 * get a मुक्त cluster.
 *
 * The data field stores next cluster अगर the cluster is मुक्त or cluster usage
 * counter otherwise. The flags field determines अगर a cluster is मुक्त. This is
 * रक्षित by swap_info_काष्ठा.lock.
 */
काष्ठा swap_cluster_info अणु
	spinlock_t lock;	/*
				 * Protect swap_cluster_info fields
				 * and swap_info_काष्ठा->swap_map
				 * elements correspond to the swap
				 * cluster
				 */
	अचिन्हित पूर्णांक data:24;
	अचिन्हित पूर्णांक flags:8;
पूर्ण;
#घोषणा CLUSTER_FLAG_FREE 1 /* This cluster is मुक्त */
#घोषणा CLUSTER_FLAG_NEXT_शून्य 2 /* This cluster has no next cluster */
#घोषणा CLUSTER_FLAG_HUGE 4 /* This cluster is backing a transparent huge page */

/*
 * We assign a cluster to each CPU, so each CPU can allocate swap entry from
 * its own cluster and swapout sequentially. The purpose is to optimize swapout
 * throughput.
 */
काष्ठा percpu_cluster अणु
	काष्ठा swap_cluster_info index; /* Current cluster index */
	अचिन्हित पूर्णांक next; /* Likely next allocation offset */
पूर्ण;

काष्ठा swap_cluster_list अणु
	काष्ठा swap_cluster_info head;
	काष्ठा swap_cluster_info tail;
पूर्ण;

/*
 * The in-memory काष्ठाure used to track swap areas.
 */
काष्ठा swap_info_काष्ठा अणु
	अचिन्हित दीर्घ	flags;		/* SWP_USED etc: see above */
	चिन्हित लघु	prio;		/* swap priority of this type */
	काष्ठा plist_node list;		/* entry in swap_active_head */
	चिन्हित अक्षर	type;		/* strange name क्रम an index */
	अचिन्हित पूर्णांक	max;		/* extent of the swap_map */
	अचिन्हित अक्षर *swap_map;	/* vदो_स्मृति'ed array of usage counts */
	काष्ठा swap_cluster_info *cluster_info; /* cluster info. Only क्रम SSD */
	काष्ठा swap_cluster_list मुक्त_clusters; /* मुक्त clusters list */
	अचिन्हित पूर्णांक lowest_bit;	/* index of first मुक्त in swap_map */
	अचिन्हित पूर्णांक highest_bit;	/* index of last मुक्त in swap_map */
	अचिन्हित पूर्णांक pages;		/* total of usable pages of swap */
	अचिन्हित पूर्णांक inuse_pages;	/* number of those currently in use */
	अचिन्हित पूर्णांक cluster_next;	/* likely index क्रम next allocation */
	अचिन्हित पूर्णांक cluster_nr;	/* countकरोwn to next cluster search */
	अचिन्हित पूर्णांक __percpu *cluster_next_cpu; /*percpu index क्रम next allocation */
	काष्ठा percpu_cluster __percpu *percpu_cluster; /* per cpu's swap location */
	काष्ठा rb_root swap_extent_root;/* root of the swap extent rbtree */
	काष्ठा block_device *bdev;	/* swap device or bdev of swap file */
	काष्ठा file *swap_file;		/* selकरोm referenced */
	अचिन्हित पूर्णांक old_block_size;	/* selकरोm referenced */
#अगर_घोषित CONFIG_FRONTSWAP
	अचिन्हित दीर्घ *frontswap_map;	/* frontswap in-use, one bit per page */
	atomic_t frontswap_pages;	/* frontswap pages in-use counter */
#पूर्ण_अगर
	spinlock_t lock;		/*
					 * protect map scan related fields like
					 * swap_map, lowest_bit, highest_bit,
					 * inuse_pages, cluster_next,
					 * cluster_nr, lowest_alloc,
					 * highest_alloc, मुक्त/discard cluster
					 * list. other fields are only changed
					 * at swapon/swapoff, so are रक्षित
					 * by swap_lock. changing flags need
					 * hold this lock and swap_lock. If
					 * both locks need hold, hold swap_lock
					 * first.
					 */
	spinlock_t cont_lock;		/*
					 * protect swap count continuation page
					 * list.
					 */
	काष्ठा work_काष्ठा discard_work; /* discard worker */
	काष्ठा swap_cluster_list discard_clusters; /* discard clusters list */
	काष्ठा plist_node avail_lists[]; /*
					   * entries in swap_avail_heads, one
					   * entry per node.
					   * Must be last as the number of the
					   * array is nr_node_ids, which is not
					   * a fixed value so have to allocate
					   * dynamically.
					   * And it has to be an array so that
					   * plist_क्रम_each_* can work.
					   */
पूर्ण;

#अगर_घोषित CONFIG_64BIT
#घोषणा SWAP_RA_ORDER_CEILING	5
#अन्यथा
/* Aव्योम stack overflow, because we need to save part of page table */
#घोषणा SWAP_RA_ORDER_CEILING	3
#घोषणा SWAP_RA_PTE_CACHE_SIZE	(1 << SWAP_RA_ORDER_CEILING)
#पूर्ण_अगर

काष्ठा vma_swap_पढ़ोahead अणु
	अचिन्हित लघु win;
	अचिन्हित लघु offset;
	अचिन्हित लघु nr_pte;
#अगर_घोषित CONFIG_64BIT
	pte_t *ptes;
#अन्यथा
	pte_t ptes[SWAP_RA_PTE_CACHE_SIZE];
#पूर्ण_अगर
पूर्ण;

/* linux/mm/workingset.c */
व्योम workingset_age_nonresident(काष्ठा lruvec *lruvec, अचिन्हित दीर्घ nr_pages);
व्योम *workingset_eviction(काष्ठा page *page, काष्ठा mem_cgroup *target_memcg);
व्योम workingset_refault(काष्ठा page *page, व्योम *shaकरोw);
व्योम workingset_activation(काष्ठा page *page);

/* Only track the nodes of mappings with shaकरोw entries */
व्योम workingset_update_node(काष्ठा xa_node *node);
#घोषणा mapping_set_update(xas, mapping) करो अणु				\
	अगर (!dax_mapping(mapping) && !shmem_mapping(mapping))		\
		xas_set_update(xas, workingset_update_node);		\
पूर्ण जबतक (0)

/* linux/mm/page_alloc.c */
बाह्य अचिन्हित दीर्घ totalreserve_pages;
बाह्य अचिन्हित दीर्घ nr_मुक्त_buffer_pages(व्योम);

/* Definition of global_zone_page_state not available yet */
#घोषणा nr_मुक्त_pages() global_zone_page_state(NR_FREE_PAGES)


/* linux/mm/swap.c */
बाह्य व्योम lru_note_cost(काष्ठा lruvec *lruvec, bool file,
			  अचिन्हित पूर्णांक nr_pages);
बाह्य व्योम lru_note_cost_page(काष्ठा page *);
बाह्य व्योम lru_cache_add(काष्ठा page *);
बाह्य व्योम mark_page_accessed(काष्ठा page *);

बाह्य atomic_t lru_disable_count;

अटल अंतरभूत bool lru_cache_disabled(व्योम)
अणु
	वापस atomic_पढ़ो(&lru_disable_count);
पूर्ण

अटल अंतरभूत व्योम lru_cache_enable(व्योम)
अणु
	atomic_dec(&lru_disable_count);
पूर्ण

बाह्य व्योम lru_cache_disable(व्योम);
बाह्य व्योम lru_add_drain(व्योम);
बाह्य व्योम lru_add_drain_cpu(पूर्णांक cpu);
बाह्य व्योम lru_add_drain_cpu_zone(काष्ठा zone *zone);
बाह्य व्योम lru_add_drain_all(व्योम);
बाह्य व्योम rotate_reclaimable_page(काष्ठा page *page);
बाह्य व्योम deactivate_file_page(काष्ठा page *page);
बाह्य व्योम deactivate_page(काष्ठा page *page);
बाह्य व्योम mark_page_lazyमुक्त(काष्ठा page *page);
बाह्य व्योम swap_setup(व्योम);

बाह्य व्योम lru_cache_add_inactive_or_unevictable(काष्ठा page *page,
						काष्ठा vm_area_काष्ठा *vma);

/* linux/mm/vmscan.c */
बाह्य अचिन्हित दीर्घ zone_reclaimable_pages(काष्ठा zone *zone);
बाह्य अचिन्हित दीर्घ try_to_मुक्त_pages(काष्ठा zonelist *zonelist, पूर्णांक order,
					gfp_t gfp_mask, nodemask_t *mask);
बाह्य bool __isolate_lru_page_prepare(काष्ठा page *page, isolate_mode_t mode);
बाह्य अचिन्हित दीर्घ try_to_मुक्त_mem_cgroup_pages(काष्ठा mem_cgroup *memcg,
						  अचिन्हित दीर्घ nr_pages,
						  gfp_t gfp_mask,
						  bool may_swap);
बाह्य अचिन्हित दीर्घ mem_cgroup_shrink_node(काष्ठा mem_cgroup *mem,
						gfp_t gfp_mask, bool noswap,
						pg_data_t *pgdat,
						अचिन्हित दीर्घ *nr_scanned);
बाह्य अचिन्हित दीर्घ shrink_all_memory(अचिन्हित दीर्घ nr_pages);
बाह्य पूर्णांक vm_swappiness;
बाह्य पूर्णांक हटाओ_mapping(काष्ठा address_space *mapping, काष्ठा page *page);

बाह्य अचिन्हित दीर्घ reclaim_pages(काष्ठा list_head *page_list);
#अगर_घोषित CONFIG_NUMA
बाह्य पूर्णांक node_reclaim_mode;
बाह्य पूर्णांक sysctl_min_unmapped_ratio;
बाह्य पूर्णांक sysctl_min_slab_ratio;
#अन्यथा
#घोषणा node_reclaim_mode 0
#पूर्ण_अगर

अटल अंतरभूत bool node_reclaim_enabled(व्योम)
अणु
	/* Is any node_reclaim_mode bit set? */
	वापस node_reclaim_mode & (RECLAIM_ZONE|RECLAIM_WRITE|RECLAIM_UNMAP);
पूर्ण

बाह्य व्योम check_move_unevictable_pages(काष्ठा pagevec *pvec);

बाह्य पूर्णांक kswapd_run(पूर्णांक nid);
बाह्य व्योम kswapd_stop(पूर्णांक nid);

#अगर_घोषित CONFIG_SWAP

#समावेश <linux/blk_types.h> /* क्रम bio_end_io_t */

/* linux/mm/page_io.c */
बाह्य पूर्णांक swap_पढ़ोpage(काष्ठा page *page, bool करो_poll);
बाह्य पूर्णांक swap_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc);
बाह्य व्योम end_swap_bio_ग_लिखो(काष्ठा bio *bio);
बाह्य पूर्णांक __swap_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
	bio_end_io_t end_ग_लिखो_func);
बाह्य पूर्णांक swap_set_page_dirty(काष्ठा page *page);

पूर्णांक add_swap_extent(काष्ठा swap_info_काष्ठा *sis, अचिन्हित दीर्घ start_page,
		अचिन्हित दीर्घ nr_pages, sector_t start_block);
पूर्णांक generic_swapfile_activate(काष्ठा swap_info_काष्ठा *, काष्ठा file *,
		sector_t *);

/* linux/mm/swap_state.c */
/* One swap address space क्रम each 64M swap space */
#घोषणा SWAP_ADDRESS_SPACE_SHIFT	14
#घोषणा SWAP_ADDRESS_SPACE_PAGES	(1 << SWAP_ADDRESS_SPACE_SHIFT)
बाह्य काष्ठा address_space *swapper_spaces[];
#घोषणा swap_address_space(entry)			    \
	(&swapper_spaces[swp_type(entry)][swp_offset(entry) \
		>> SWAP_ADDRESS_SPACE_SHIFT])
अटल अंतरभूत अचिन्हित दीर्घ total_swapcache_pages(व्योम)
अणु
	वापस global_node_page_state(NR_SWAPCACHE);
पूर्ण

बाह्य व्योम show_swap_cache_info(व्योम);
बाह्य पूर्णांक add_to_swap(काष्ठा page *page);
बाह्य व्योम *get_shaकरोw_from_swap_cache(swp_entry_t entry);
बाह्य पूर्णांक add_to_swap_cache(काष्ठा page *page, swp_entry_t entry,
			gfp_t gfp, व्योम **shaकरोwp);
बाह्य व्योम __delete_from_swap_cache(काष्ठा page *page,
			swp_entry_t entry, व्योम *shaकरोw);
बाह्य व्योम delete_from_swap_cache(काष्ठा page *);
बाह्य व्योम clear_shaकरोw_from_swap_cache(पूर्णांक type, अचिन्हित दीर्घ begin,
				अचिन्हित दीर्घ end);
बाह्य व्योम मुक्त_page_and_swap_cache(काष्ठा page *);
बाह्य व्योम मुक्त_pages_and_swap_cache(काष्ठा page **, पूर्णांक);
बाह्य काष्ठा page *lookup_swap_cache(swp_entry_t entry,
				      काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ addr);
काष्ठा page *find_get_incore_page(काष्ठा address_space *mapping, pgoff_t index);
बाह्य काष्ठा page *पढ़ो_swap_cache_async(swp_entry_t, gfp_t,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			bool करो_poll);
बाह्य काष्ठा page *__पढ़ो_swap_cache_async(swp_entry_t, gfp_t,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			bool *new_page_allocated);
बाह्य काष्ठा page *swap_cluster_पढ़ोahead(swp_entry_t entry, gfp_t flag,
				काष्ठा vm_fault *vmf);
बाह्य काष्ठा page *swapin_पढ़ोahead(swp_entry_t entry, gfp_t flag,
				काष्ठा vm_fault *vmf);

/* linux/mm/swapfile.c */
बाह्य atomic_दीर्घ_t nr_swap_pages;
बाह्य दीर्घ total_swap_pages;
बाह्य atomic_t nr_rotate_swap;
बाह्य bool has_usable_swap(व्योम);

/* Swap 50% full? Release swapcache more aggressively.. */
अटल अंतरभूत bool vm_swap_full(व्योम)
अणु
	वापस atomic_दीर्घ_पढ़ो(&nr_swap_pages) * 2 < total_swap_pages;
पूर्ण

अटल अंतरभूत दीर्घ get_nr_swap_pages(व्योम)
अणु
	वापस atomic_दीर्घ_पढ़ो(&nr_swap_pages);
पूर्ण

बाह्य व्योम si_swapinfo(काष्ठा sysinfo *);
बाह्य swp_entry_t get_swap_page(काष्ठा page *page);
बाह्य व्योम put_swap_page(काष्ठा page *page, swp_entry_t entry);
बाह्य swp_entry_t get_swap_page_of_type(पूर्णांक);
बाह्य पूर्णांक get_swap_pages(पूर्णांक n, swp_entry_t swp_entries[], पूर्णांक entry_size);
बाह्य पूर्णांक add_swap_count_continuation(swp_entry_t, gfp_t);
बाह्य व्योम swap_shmem_alloc(swp_entry_t);
बाह्य पूर्णांक swap_duplicate(swp_entry_t);
बाह्य पूर्णांक swapcache_prepare(swp_entry_t);
बाह्य व्योम swap_मुक्त(swp_entry_t);
बाह्य व्योम swapcache_मुक्त_entries(swp_entry_t *entries, पूर्णांक n);
बाह्य पूर्णांक मुक्त_swap_and_cache(swp_entry_t);
पूर्णांक swap_type_of(dev_t device, sector_t offset);
पूर्णांक find_first_swap(dev_t *device);
बाह्य अचिन्हित पूर्णांक count_swap_pages(पूर्णांक, पूर्णांक);
बाह्य sector_t swapdev_block(पूर्णांक, pgoff_t);
बाह्य पूर्णांक page_swapcount(काष्ठा page *);
बाह्य पूर्णांक __swap_count(swp_entry_t entry);
बाह्य पूर्णांक __swp_swapcount(swp_entry_t entry);
बाह्य पूर्णांक swp_swapcount(swp_entry_t entry);
बाह्य काष्ठा swap_info_काष्ठा *page_swap_info(काष्ठा page *);
बाह्य काष्ठा swap_info_काष्ठा *swp_swap_info(swp_entry_t entry);
बाह्य bool reuse_swap_page(काष्ठा page *, पूर्णांक *);
बाह्य पूर्णांक try_to_मुक्त_swap(काष्ठा page *);
काष्ठा backing_dev_info;
बाह्य पूर्णांक init_swap_address_space(अचिन्हित पूर्णांक type, अचिन्हित दीर्घ nr_pages);
बाह्य व्योम निकास_swap_address_space(अचिन्हित पूर्णांक type);
बाह्य काष्ठा swap_info_काष्ठा *get_swap_device(swp_entry_t entry);
sector_t swap_page_sector(काष्ठा page *page);

अटल अंतरभूत व्योम put_swap_device(काष्ठा swap_info_काष्ठा *si)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

#अन्यथा /* CONFIG_SWAP */

अटल अंतरभूत पूर्णांक swap_पढ़ोpage(काष्ठा page *page, bool करो_poll)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा swap_info_काष्ठा *swp_swap_info(swp_entry_t entry)
अणु
	वापस शून्य;
पूर्ण

#घोषणा swap_address_space(entry)		(शून्य)
#घोषणा get_nr_swap_pages()			0L
#घोषणा total_swap_pages			0L
#घोषणा total_swapcache_pages()			0UL
#घोषणा vm_swap_full()				0

#घोषणा si_swapinfo(val) \
	करो अणु (val)->मुक्तswap = (val)->totalswap = 0; पूर्ण जबतक (0)
/* only sparc can not include linux/pagemap.h in this file
 * so leave put_page and release_pages undeclared... */
#घोषणा मुक्त_page_and_swap_cache(page) \
	put_page(page)
#घोषणा मुक्त_pages_and_swap_cache(pages, nr) \
	release_pages((pages), (nr));

अटल अंतरभूत व्योम show_swap_cache_info(व्योम)
अणु
पूर्ण

#घोषणा मुक्त_swap_and_cache(e) (अणु(is_migration_entry(e) || is_device_निजी_entry(e));पूर्ण)
#घोषणा swapcache_prepare(e) (अणु(is_migration_entry(e) || is_device_निजी_entry(e));पूर्ण)

अटल अंतरभूत पूर्णांक add_swap_count_continuation(swp_entry_t swp, gfp_t gfp_mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम swap_shmem_alloc(swp_entry_t swp)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक swap_duplicate(swp_entry_t swp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम swap_मुक्त(swp_entry_t swp)
अणु
पूर्ण

अटल अंतरभूत व्योम put_swap_page(काष्ठा page *page, swp_entry_t swp)
अणु
पूर्ण

अटल अंतरभूत काष्ठा page *swap_cluster_पढ़ोahead(swp_entry_t entry,
				gfp_t gfp_mask, काष्ठा vm_fault *vmf)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *swapin_पढ़ोahead(swp_entry_t swp, gfp_t gfp_mask,
			काष्ठा vm_fault *vmf)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक swap_ग_लिखोpage(काष्ठा page *p, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा page *lookup_swap_cache(swp_entry_t swp,
					     काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा page *find_get_incore_page(काष्ठा address_space *mapping, pgoff_t index)
अणु
	वापस find_get_page(mapping, index);
पूर्ण

अटल अंतरभूत पूर्णांक add_to_swap(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *get_shaकरोw_from_swap_cache(swp_entry_t entry)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक add_to_swap_cache(काष्ठा page *page, swp_entry_t entry,
					gfp_t gfp_mask, व्योम **shaकरोwp)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम __delete_from_swap_cache(काष्ठा page *page,
					swp_entry_t entry, व्योम *shaकरोw)
अणु
पूर्ण

अटल अंतरभूत व्योम delete_from_swap_cache(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम clear_shaकरोw_from_swap_cache(पूर्णांक type, अचिन्हित दीर्घ begin,
				अचिन्हित दीर्घ end)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक page_swapcount(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __swap_count(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __swp_swapcount(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक swp_swapcount(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

#घोषणा reuse_swap_page(page, total_map_swapcount) \
	(page_trans_huge_mapcount(page, total_map_swapcount) == 1)

अटल अंतरभूत पूर्णांक try_to_मुक्त_swap(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत swp_entry_t get_swap_page(काष्ठा page *page)
अणु
	swp_entry_t entry;
	entry.val = 0;
	वापस entry;
पूर्ण

#पूर्ण_अगर /* CONFIG_SWAP */

#अगर_घोषित CONFIG_THP_SWAP
बाह्य पूर्णांक split_swap_cluster(swp_entry_t entry);
#अन्यथा
अटल अंतरभूत पूर्णांक split_swap_cluster(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMCG
अटल अंतरभूत पूर्णांक mem_cgroup_swappiness(काष्ठा mem_cgroup *memcg)
अणु
	/* Cgroup2 करोesn't have per-cgroup swappiness */
	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस vm_swappiness;

	/* root ? */
	अगर (mem_cgroup_disabled() || mem_cgroup_is_root(memcg))
		वापस vm_swappiness;

	वापस memcg->swappiness;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mem_cgroup_swappiness(काष्ठा mem_cgroup *mem)
अणु
	वापस vm_swappiness;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SWAP) && defined(CONFIG_MEMCG) && defined(CONFIG_BLK_CGROUP)
बाह्य व्योम cgroup_throttle_swaprate(काष्ठा page *page, gfp_t gfp_mask);
#अन्यथा
अटल अंतरभूत व्योम cgroup_throttle_swaprate(काष्ठा page *page, gfp_t gfp_mask)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMCG_SWAP
बाह्य व्योम mem_cgroup_swapout(काष्ठा page *page, swp_entry_t entry);
बाह्य पूर्णांक mem_cgroup_try_अक्षरge_swap(काष्ठा page *page, swp_entry_t entry);
बाह्य व्योम mem_cgroup_unअक्षरge_swap(swp_entry_t entry, अचिन्हित पूर्णांक nr_pages);
बाह्य दीर्घ mem_cgroup_get_nr_swap_pages(काष्ठा mem_cgroup *memcg);
बाह्य bool mem_cgroup_swap_full(काष्ठा page *page);
#अन्यथा
अटल अंतरभूत व्योम mem_cgroup_swapout(काष्ठा page *page, swp_entry_t entry)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mem_cgroup_try_अक्षरge_swap(काष्ठा page *page,
					     swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_unअक्षरge_swap(swp_entry_t entry,
					    अचिन्हित पूर्णांक nr_pages)
अणु
पूर्ण

अटल अंतरभूत दीर्घ mem_cgroup_get_nr_swap_pages(काष्ठा mem_cgroup *memcg)
अणु
	वापस get_nr_swap_pages();
पूर्ण

अटल अंतरभूत bool mem_cgroup_swap_full(काष्ठा page *page)
अणु
	वापस vm_swap_full();
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__*/
#पूर्ण_अगर /* _LINUX_SWAP_H */
