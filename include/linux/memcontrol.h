<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* memcontrol.h - Memory Controller
 *
 * Copyright IBM Corporation, 2007
 * Author Balbir Singh <balbir@linux.vnet.ibm.com>
 *
 * Copyright 2007 OpenVZ SWsoft Inc
 * Author: Pavel Emelianov <xemul@खोलोvz.org>
 */

#अगर_अघोषित _LINUX_MEMCONTROL_H
#घोषणा _LINUX_MEMCONTROL_H
#समावेश <linux/cgroup.h>
#समावेश <linux/vm_event_item.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/page_counter.h>
#समावेश <linux/vmpressure.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/mm.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/page-flags.h>

काष्ठा mem_cgroup;
काष्ठा obj_cgroup;
काष्ठा page;
काष्ठा mm_काष्ठा;
काष्ठा kmem_cache;

/* Cgroup-specअगरic page state, on top of universal node page state */
क्रमागत memcg_stat_item अणु
	MEMCG_SWAP = NR_VM_NODE_STAT_ITEMS,
	MEMCG_SOCK,
	MEMCG_PERCPU_B,
	MEMCG_NR_STAT,
पूर्ण;

क्रमागत memcg_memory_event अणु
	MEMCG_LOW,
	MEMCG_HIGH,
	MEMCG_MAX,
	MEMCG_OOM,
	MEMCG_OOM_KILL,
	MEMCG_SWAP_HIGH,
	MEMCG_SWAP_MAX,
	MEMCG_SWAP_FAIL,
	MEMCG_NR_MEMORY_EVENTS,
पूर्ण;

काष्ठा mem_cgroup_reclaim_cookie अणु
	pg_data_t *pgdat;
	अचिन्हित पूर्णांक generation;
पूर्ण;

#अगर_घोषित CONFIG_MEMCG

#घोषणा MEM_CGROUP_ID_SHIFT	16
#घोषणा MEM_CGROUP_ID_MAX	अच_लघु_उच्च

काष्ठा mem_cgroup_id अणु
	पूर्णांक id;
	refcount_t ref;
पूर्ण;

/*
 * Per memcg event counter is incremented at every pagein/pageout. With THP,
 * it will be incremented by the number of pages. This counter is used
 * to trigger some periodic events. This is straightक्रमward and better
 * than using jअगरfies etc. to handle periodic memcg event.
 */
क्रमागत mem_cgroup_events_target अणु
	MEM_CGROUP_TARGET_THRESH,
	MEM_CGROUP_TARGET_SOFTLIMIT,
	MEM_CGROUP_NTARGETS,
पूर्ण;

काष्ठा memcg_vmstats_percpu अणु
	/* Local (CPU and cgroup) page state & events */
	दीर्घ			state[MEMCG_NR_STAT];
	अचिन्हित दीर्घ		events[NR_VM_EVENT_ITEMS];

	/* Delta calculation क्रम lockless upward propagation */
	दीर्घ			state_prev[MEMCG_NR_STAT];
	अचिन्हित दीर्घ		events_prev[NR_VM_EVENT_ITEMS];

	/* Cgroup1: threshold notअगरications & softlimit tree updates */
	अचिन्हित दीर्घ		nr_page_events;
	अचिन्हित दीर्घ		tarमाला_लो[MEM_CGROUP_NTARGETS];
पूर्ण;

काष्ठा memcg_vmstats अणु
	/* Aggregated (CPU and subtree) page state & events */
	दीर्घ			state[MEMCG_NR_STAT];
	अचिन्हित दीर्घ		events[NR_VM_EVENT_ITEMS];

	/* Pending child counts during tree propagation */
	दीर्घ			state_pending[MEMCG_NR_STAT];
	अचिन्हित दीर्घ		events_pending[NR_VM_EVENT_ITEMS];
पूर्ण;

काष्ठा mem_cgroup_reclaim_iter अणु
	काष्ठा mem_cgroup *position;
	/* scan generation, increased every round-trip */
	अचिन्हित पूर्णांक generation;
पूर्ण;

काष्ठा lruvec_stat अणु
	दीर्घ count[NR_VM_NODE_STAT_ITEMS];
पूर्ण;

काष्ठा batched_lruvec_stat अणु
	s32 count[NR_VM_NODE_STAT_ITEMS];
पूर्ण;

/*
 * Biपंचांगap and deferred work of shrinker::id corresponding to memcg-aware
 * shrinkers, which have elements अक्षरged to this memcg.
 */
काष्ठा shrinker_info अणु
	काष्ठा rcu_head rcu;
	atomic_दीर्घ_t *nr_deferred;
	अचिन्हित दीर्घ *map;
पूर्ण;

/*
 * per-node inक्रमmation in memory controller.
 */
काष्ठा mem_cgroup_per_node अणु
	काष्ठा lruvec		lruvec;

	/*
	 * Legacy local VM stats. This should be काष्ठा lruvec_stat and
	 * cannot be optimized to काष्ठा batched_lruvec_stat. Because
	 * the threshold of the lruvec_stat_cpu can be as big as
	 * MEMCG_CHARGE_BATCH * PAGE_SIZE. It can fit पूर्णांकo s32. But this
	 * filed has no upper limit.
	 */
	काष्ठा lruvec_stat __percpu *lruvec_stat_local;

	/* Subtree VM stats (batched updates) */
	काष्ठा batched_lruvec_stat __percpu *lruvec_stat_cpu;
	atomic_दीर्घ_t		lruvec_stat[NR_VM_NODE_STAT_ITEMS];

	अचिन्हित दीर्घ		lru_zone_size[MAX_NR_ZONES][NR_LRU_LISTS];

	काष्ठा mem_cgroup_reclaim_iter	iter;

	काष्ठा shrinker_info __rcu	*shrinker_info;

	काष्ठा rb_node		tree_node;	/* RB tree node */
	अचिन्हित दीर्घ		usage_in_excess;/* Set to the value by which */
						/* the soft limit is exceeded*/
	bool			on_tree;
	काष्ठा mem_cgroup	*memcg;		/* Back poपूर्णांकer, we cannot */
						/* use container_of	   */
पूर्ण;

काष्ठा mem_cgroup_threshold अणु
	काष्ठा eventfd_ctx *eventfd;
	अचिन्हित दीर्घ threshold;
पूर्ण;

/* For threshold */
काष्ठा mem_cgroup_threshold_ary अणु
	/* An array index poपूर्णांकs to threshold just below or equal to usage. */
	पूर्णांक current_threshold;
	/* Size of entries[] */
	अचिन्हित पूर्णांक size;
	/* Array of thresholds */
	काष्ठा mem_cgroup_threshold entries[];
पूर्ण;

काष्ठा mem_cgroup_thresholds अणु
	/* Primary thresholds array */
	काष्ठा mem_cgroup_threshold_ary *primary;
	/*
	 * Spare threshold array.
	 * This is needed to make mem_cgroup_unरेजिस्टर_event() "never fail".
	 * It must be able to store at least primary->size - 1 entries.
	 */
	काष्ठा mem_cgroup_threshold_ary *spare;
पूर्ण;

क्रमागत memcg_kmem_state अणु
	KMEM_NONE,
	KMEM_ALLOCATED,
	KMEM_ONLINE,
पूर्ण;

#अगर defined(CONFIG_SMP)
काष्ठा memcg_padding अणु
	अक्षर x[0];
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;
#घोषणा MEMCG_PADDING(name)      काष्ठा memcg_padding name;
#अन्यथा
#घोषणा MEMCG_PADDING(name)
#पूर्ण_अगर

/*
 * Remember four most recent क्रमeign ग_लिखोbacks with dirty pages in this
 * cgroup.  Inode sharing is expected to be uncommon and, even अगर we miss
 * one in a given round, we're likely to catch it later अगर it keeps
 * क्रमeign-dirtying, so a fairly low count should be enough.
 *
 * See mem_cgroup_track_क्रमeign_dirty_slowpath() क्रम details.
 */
#घोषणा MEMCG_CGWB_FRN_CNT	4

काष्ठा memcg_cgwb_frn अणु
	u64 bdi_id;			/* bdi->id of the क्रमeign inode */
	पूर्णांक memcg_id;			/* memcg->css.id of क्रमeign inode */
	u64 at;				/* jअगरfies_64 at the समय of dirtying */
	काष्ठा wb_completion करोne;	/* tracks in-flight क्रमeign ग_लिखोbacks */
पूर्ण;

/*
 * Bucket क्रम arbitrarily byte-sized objects अक्षरged to a memory
 * cgroup. The bucket can be reparented in one piece when the cgroup
 * is destroyed, without having to round up the inभागidual references
 * of all live memory objects in the wild.
 */
काष्ठा obj_cgroup अणु
	काष्ठा percpu_ref refcnt;
	काष्ठा mem_cgroup *memcg;
	atomic_t nr_अक्षरged_bytes;
	जोड़ अणु
		काष्ठा list_head list;
		काष्ठा rcu_head rcu;
	पूर्ण;
पूर्ण;

/*
 * The memory controller data काष्ठाure. The memory controller controls both
 * page cache and RSS per cgroup. We would eventually like to provide
 * statistics based on the statistics developed by Rik Van Riel क्रम घड़ी-pro,
 * to help the administrator determine what knobs to tune.
 */
काष्ठा mem_cgroup अणु
	काष्ठा cgroup_subsys_state css;

	/* Private memcg ID. Used to ID objects that outlive the cgroup */
	काष्ठा mem_cgroup_id id;

	/* Accounted resources */
	काष्ठा page_counter memory;		/* Both v1 & v2 */

	जोड़ अणु
		काष्ठा page_counter swap;	/* v2 only */
		काष्ठा page_counter memsw;	/* v1 only */
	पूर्ण;

	/* Legacy consumer-oriented counters */
	काष्ठा page_counter kmem;		/* v1 only */
	काष्ठा page_counter tcpmem;		/* v1 only */

	/* Range enक्रमcement क्रम पूर्णांकerrupt अक्षरges */
	काष्ठा work_काष्ठा high_work;

	अचिन्हित दीर्घ soft_limit;

	/* vmpressure notअगरications */
	काष्ठा vmpressure vmpressure;

	/*
	 * Should the OOM समाप्तer समाप्त all beदीर्घing tasks, had it समाप्त one?
	 */
	bool oom_group;

	/* रक्षित by memcg_oom_lock */
	bool		oom_lock;
	पूर्णांक		under_oom;

	पूर्णांक	swappiness;
	/* OOM-Killer disable */
	पूर्णांक		oom_समाप्त_disable;

	/* memory.events and memory.events.local */
	काष्ठा cgroup_file events_file;
	काष्ठा cgroup_file events_local_file;

	/* handle क्रम "memory.swap.events" */
	काष्ठा cgroup_file swap_events_file;

	/* protect arrays of thresholds */
	काष्ठा mutex thresholds_lock;

	/* thresholds क्रम memory usage. RCU-रक्षित */
	काष्ठा mem_cgroup_thresholds thresholds;

	/* thresholds क्रम mem+swap usage. RCU-रक्षित */
	काष्ठा mem_cgroup_thresholds memsw_thresholds;

	/* For oom notअगरier event fd */
	काष्ठा list_head oom_notअगरy;

	/*
	 * Should we move अक्षरges of a task when a task is moved पूर्णांकo this
	 * mem_cgroup ? And what type of अक्षरges should we move ?
	 */
	अचिन्हित दीर्घ move_अक्षरge_at_immigrate;
	/* taken only जबतक moving_account > 0 */
	spinlock_t		move_lock;
	अचिन्हित दीर्घ		move_lock_flags;

	MEMCG_PADDING(_pad1_);

	/* memory.stat */
	काष्ठा memcg_vmstats	vmstats;

	/* memory.events */
	atomic_दीर्घ_t		memory_events[MEMCG_NR_MEMORY_EVENTS];
	atomic_दीर्घ_t		memory_events_local[MEMCG_NR_MEMORY_EVENTS];

	अचिन्हित दीर्घ		socket_pressure;

	/* Legacy tcp memory accounting */
	bool			tcpmem_active;
	पूर्णांक			tcpmem_pressure;

#अगर_घोषित CONFIG_MEMCG_KMEM
	पूर्णांक kmemcg_id;
	क्रमागत memcg_kmem_state kmem_state;
	काष्ठा obj_cgroup __rcu *objcg;
	काष्ठा list_head objcg_list; /* list of inherited objcgs */
#पूर्ण_अगर

	MEMCG_PADDING(_pad2_);

	/*
	 * set > 0 अगर pages under this cgroup are moving to other cgroup.
	 */
	atomic_t		moving_account;
	काष्ठा task_काष्ठा	*move_lock_task;

	काष्ठा memcg_vmstats_percpu __percpu *vmstats_percpu;

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	काष्ठा list_head cgwb_list;
	काष्ठा wb_करोमुख्य cgwb_करोमुख्य;
	काष्ठा memcg_cgwb_frn cgwb_frn[MEMCG_CGWB_FRN_CNT];
#पूर्ण_अगर

	/* List of events which userspace want to receive */
	काष्ठा list_head event_list;
	spinlock_t event_list_lock;

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	काष्ठा deferred_split deferred_split_queue;
#पूर्ण_अगर

	काष्ठा mem_cgroup_per_node *nodeinfo[0];
	/* WARNING: nodeinfo must be the last member here */
पूर्ण;

/*
 * size of first अक्षरge trial. "32" comes from vmscan.c's magic value.
 * TODO: maybe necessary to use big numbers in big irons.
 */
#घोषणा MEMCG_CHARGE_BATCH 32U

बाह्य काष्ठा mem_cgroup *root_mem_cgroup;

क्रमागत page_memcg_data_flags अणु
	/* page->memcg_data is a poपूर्णांकer to an objcgs vector */
	MEMCG_DATA_OBJCGS = (1UL << 0),
	/* page has been accounted as a non-slab kernel page */
	MEMCG_DATA_KMEM = (1UL << 1),
	/* the next bit after the last actual flag */
	__NR_MEMCG_DATA_FLAGS  = (1UL << 2),
पूर्ण;

#घोषणा MEMCG_DATA_FLAGS_MASK (__NR_MEMCG_DATA_FLAGS - 1)

अटल अंतरभूत bool PageMemcgKmem(काष्ठा page *page);

/*
 * After the initialization objcg->memcg is always poपूर्णांकing at
 * a valid memcg, but can be atomically swapped to the parent memcg.
 *
 * The caller must ensure that the वापसed memcg won't be released:
 * e.g. acquire the rcu_पढ़ो_lock or css_set_lock.
 */
अटल अंतरभूत काष्ठा mem_cgroup *obj_cgroup_memcg(काष्ठा obj_cgroup *objcg)
अणु
	वापस READ_ONCE(objcg->memcg);
पूर्ण

/*
 * __page_memcg - get the memory cgroup associated with a non-kmem page
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Returns a poपूर्णांकer to the memory cgroup associated with the page,
 * or शून्य. This function assumes that the page is known to have a
 * proper memory cgroup poपूर्णांकer. It's not safe to call this function
 * against some type of pages, e.g. slab pages or ex-slab pages or
 * kmem pages.
 */
अटल अंतरभूत काष्ठा mem_cgroup *__page_memcg(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ memcg_data = page->memcg_data;

	VM_BUG_ON_PAGE(PageSlab(page), page);
	VM_BUG_ON_PAGE(memcg_data & MEMCG_DATA_OBJCGS, page);
	VM_BUG_ON_PAGE(memcg_data & MEMCG_DATA_KMEM, page);

	वापस (काष्ठा mem_cgroup *)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
पूर्ण

/*
 * __page_objcg - get the object cgroup associated with a kmem page
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Returns a poपूर्णांकer to the object cgroup associated with the page,
 * or शून्य. This function assumes that the page is known to have a
 * proper object cgroup poपूर्णांकer. It's not safe to call this function
 * against some type of pages, e.g. slab pages or ex-slab pages or
 * LRU pages.
 */
अटल अंतरभूत काष्ठा obj_cgroup *__page_objcg(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ memcg_data = page->memcg_data;

	VM_BUG_ON_PAGE(PageSlab(page), page);
	VM_BUG_ON_PAGE(memcg_data & MEMCG_DATA_OBJCGS, page);
	VM_BUG_ON_PAGE(!(memcg_data & MEMCG_DATA_KMEM), page);

	वापस (काष्ठा obj_cgroup *)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
पूर्ण

/*
 * page_memcg - get the memory cgroup associated with a page
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Returns a poपूर्णांकer to the memory cgroup associated with the page,
 * or शून्य. This function assumes that the page is known to have a
 * proper memory cgroup poपूर्णांकer. It's not safe to call this function
 * against some type of pages, e.g. slab pages or ex-slab pages.
 *
 * For a non-kmem page any of the following ensures page and memcg binding
 * stability:
 *
 * - the page lock
 * - LRU isolation
 * - lock_page_memcg()
 * - exclusive reference
 *
 * For a kmem page a caller should hold an rcu पढ़ो lock to protect memcg
 * associated with a kmem page from being released.
 */
अटल अंतरभूत काष्ठा mem_cgroup *page_memcg(काष्ठा page *page)
अणु
	अगर (PageMemcgKmem(page))
		वापस obj_cgroup_memcg(__page_objcg(page));
	अन्यथा
		वापस __page_memcg(page);
पूर्ण

/*
 * page_memcg_rcu - locklessly get the memory cgroup associated with a page
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Returns a poपूर्णांकer to the memory cgroup associated with the page,
 * or शून्य. This function assumes that the page is known to have a
 * proper memory cgroup poपूर्णांकer. It's not safe to call this function
 * against some type of pages, e.g. slab pages or ex-slab pages.
 */
अटल अंतरभूत काष्ठा mem_cgroup *page_memcg_rcu(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ memcg_data = READ_ONCE(page->memcg_data);

	VM_BUG_ON_PAGE(PageSlab(page), page);
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	अगर (memcg_data & MEMCG_DATA_KMEM) अणु
		काष्ठा obj_cgroup *objcg;

		objcg = (व्योम *)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
		वापस obj_cgroup_memcg(objcg);
	पूर्ण

	वापस (काष्ठा mem_cgroup *)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
पूर्ण

/*
 * page_memcg_check - get the memory cgroup associated with a page
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Returns a poपूर्णांकer to the memory cgroup associated with the page,
 * or शून्य. This function unlike page_memcg() can take any page
 * as an argument. It has to be used in हालs when it's not known अगर a page
 * has an associated memory cgroup poपूर्णांकer or an object cgroups vector or
 * an object cgroup.
 *
 * For a non-kmem page any of the following ensures page and memcg binding
 * stability:
 *
 * - the page lock
 * - LRU isolation
 * - lock_page_memcg()
 * - exclusive reference
 *
 * For a kmem page a caller should hold an rcu पढ़ो lock to protect memcg
 * associated with a kmem page from being released.
 */
अटल अंतरभूत काष्ठा mem_cgroup *page_memcg_check(काष्ठा page *page)
अणु
	/*
	 * Because page->memcg_data might be changed asynchronously
	 * क्रम slab pages, READ_ONCE() should be used here.
	 */
	अचिन्हित दीर्घ memcg_data = READ_ONCE(page->memcg_data);

	अगर (memcg_data & MEMCG_DATA_OBJCGS)
		वापस शून्य;

	अगर (memcg_data & MEMCG_DATA_KMEM) अणु
		काष्ठा obj_cgroup *objcg;

		objcg = (व्योम *)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
		वापस obj_cgroup_memcg(objcg);
	पूर्ण

	वापस (काष्ठा mem_cgroup *)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
/*
 * PageMemcgKmem - check अगर the page has MemcgKmem flag set
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Checks अगर the page has MemcgKmem flag set. The caller must ensure that
 * the page has an associated memory cgroup. It's not safe to call this function
 * against some types of pages, e.g. slab pages.
 */
अटल अंतरभूत bool PageMemcgKmem(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(page->memcg_data & MEMCG_DATA_OBJCGS, page);
	वापस page->memcg_data & MEMCG_DATA_KMEM;
पूर्ण

/*
 * page_objcgs - get the object cgroups vector associated with a page
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Returns a poपूर्णांकer to the object cgroups vector associated with the page,
 * or शून्य. This function assumes that the page is known to have an
 * associated object cgroups vector. It's not safe to call this function
 * against pages, which might have an associated memory cgroup: e.g.
 * kernel stack pages.
 */
अटल अंतरभूत काष्ठा obj_cgroup **page_objcgs(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ memcg_data = READ_ONCE(page->memcg_data);

	VM_BUG_ON_PAGE(memcg_data && !(memcg_data & MEMCG_DATA_OBJCGS), page);
	VM_BUG_ON_PAGE(memcg_data & MEMCG_DATA_KMEM, page);

	वापस (काष्ठा obj_cgroup **)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
पूर्ण

/*
 * page_objcgs_check - get the object cgroups vector associated with a page
 * @page: a poपूर्णांकer to the page काष्ठा
 *
 * Returns a poपूर्णांकer to the object cgroups vector associated with the page,
 * or शून्य. This function is safe to use अगर the page can be directly associated
 * with a memory cgroup.
 */
अटल अंतरभूत काष्ठा obj_cgroup **page_objcgs_check(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ memcg_data = READ_ONCE(page->memcg_data);

	अगर (!memcg_data || !(memcg_data & MEMCG_DATA_OBJCGS))
		वापस शून्य;

	VM_BUG_ON_PAGE(memcg_data & MEMCG_DATA_KMEM, page);

	वापस (काष्ठा obj_cgroup **)(memcg_data & ~MEMCG_DATA_FLAGS_MASK);
पूर्ण

#अन्यथा
अटल अंतरभूत bool PageMemcgKmem(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा obj_cgroup **page_objcgs(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा obj_cgroup **page_objcgs_check(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत bool memcg_stat_item_in_bytes(पूर्णांक idx)
अणु
	अगर (idx == MEMCG_PERCPU_B)
		वापस true;
	वापस vmstat_item_in_bytes(idx);
पूर्ण

अटल अंतरभूत bool mem_cgroup_is_root(काष्ठा mem_cgroup *memcg)
अणु
	वापस (memcg == root_mem_cgroup);
पूर्ण

अटल अंतरभूत bool mem_cgroup_disabled(व्योम)
अणु
	वापस !cgroup_subsys_enabled(memory_cgrp_subsys);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mem_cgroup_protection(काष्ठा mem_cgroup *root,
						  काष्ठा mem_cgroup *memcg,
						  bool in_low_reclaim)
अणु
	अगर (mem_cgroup_disabled())
		वापस 0;

	/*
	 * There is no reclaim protection applied to a targeted reclaim.
	 * We are special casing this specअगरic हाल here because
	 * mem_cgroup_रक्षित calculation is not robust enough to keep
	 * the protection invariant क्रम calculated effective values क्रम
	 * parallel reclaimers with dअगरferent reclaim target. This is
	 * especially a problem क्रम tail memcgs (as they have pages on LRU)
	 * which would want to have effective values 0 क्रम targeted reclaim
	 * but a dअगरferent value क्रम बाह्यal reclaim.
	 *
	 * Example
	 * Let's have global and A's reclaim in parallel:
	 *  |
	 *  A (low=2G, usage = 3G, max = 3G, children_low_usage = 1.5G)
	 *  |\
	 *  | C (low = 1G, usage = 2.5G)
	 *  B (low = 1G, usage = 0.5G)
	 *
	 * For the global reclaim
	 * A.elow = A.low
	 * B.elow = min(B.usage, B.low) because children_low_usage <= A.elow
	 * C.elow = min(C.usage, C.low)
	 *
	 * With the effective values resetting we have A reclaim
	 * A.elow = 0
	 * B.elow = B.low
	 * C.elow = C.low
	 *
	 * If the global reclaim races with A's reclaim then
	 * B.elow = C.elow = 0 because children_low_usage > A.elow)
	 * is possible and reclaiming B would be violating the protection.
	 *
	 */
	अगर (root == memcg)
		वापस 0;

	अगर (in_low_reclaim)
		वापस READ_ONCE(memcg->memory.emin);

	वापस max(READ_ONCE(memcg->memory.emin),
		   READ_ONCE(memcg->memory.elow));
पूर्ण

व्योम mem_cgroup_calculate_protection(काष्ठा mem_cgroup *root,
				     काष्ठा mem_cgroup *memcg);

अटल अंतरभूत bool mem_cgroup_supports_protection(काष्ठा mem_cgroup *memcg)
अणु
	/*
	 * The root memcg करोesn't account charges, and doesn't support
	 * protection.
	 */
	वापस !mem_cgroup_disabled() && !mem_cgroup_is_root(memcg);

पूर्ण

अटल अंतरभूत bool mem_cgroup_below_low(काष्ठा mem_cgroup *memcg)
अणु
	अगर (!mem_cgroup_supports_protection(memcg))
		वापस false;

	वापस READ_ONCE(memcg->memory.elow) >=
		page_counter_पढ़ो(&memcg->memory);
पूर्ण

अटल अंतरभूत bool mem_cgroup_below_min(काष्ठा mem_cgroup *memcg)
अणु
	अगर (!mem_cgroup_supports_protection(memcg))
		वापस false;

	वापस READ_ONCE(memcg->memory.emin) >=
		page_counter_पढ़ो(&memcg->memory);
पूर्ण

पूर्णांक mem_cgroup_अक्षरge(काष्ठा page *page, काष्ठा mm_काष्ठा *mm, gfp_t gfp_mask);
पूर्णांक mem_cgroup_swapin_अक्षरge_page(काष्ठा page *page, काष्ठा mm_काष्ठा *mm,
				  gfp_t gfp, swp_entry_t entry);
व्योम mem_cgroup_swapin_unअक्षरge_swap(swp_entry_t entry);

व्योम mem_cgroup_unअक्षरge(काष्ठा page *page);
व्योम mem_cgroup_unअक्षरge_list(काष्ठा list_head *page_list);

व्योम mem_cgroup_migrate(काष्ठा page *oldpage, काष्ठा page *newpage);

/**
 * mem_cgroup_lruvec - get the lru list vector क्रम a memcg & node
 * @memcg: memcg of the wanted lruvec
 * @pgdat: pglist_data
 *
 * Returns the lru list vector holding pages क्रम a given @memcg &
 * @pgdat combination. This can be the node lruvec, अगर the memory
 * controller is disabled.
 */
अटल अंतरभूत काष्ठा lruvec *mem_cgroup_lruvec(काष्ठा mem_cgroup *memcg,
					       काष्ठा pglist_data *pgdat)
अणु
	काष्ठा mem_cgroup_per_node *mz;
	काष्ठा lruvec *lruvec;

	अगर (mem_cgroup_disabled()) अणु
		lruvec = &pgdat->__lruvec;
		जाओ out;
	पूर्ण

	अगर (!memcg)
		memcg = root_mem_cgroup;

	mz = memcg->nodeinfo[pgdat->node_id];
	lruvec = &mz->lruvec;
out:
	/*
	 * Since a node can be onlined after the mem_cgroup was created,
	 * we have to be prepared to initialize lruvec->pgdat here;
	 * and अगर offlined then reonlined, we need to reinitialize it.
	 */
	अगर (unlikely(lruvec->pgdat != pgdat))
		lruvec->pgdat = pgdat;
	वापस lruvec;
पूर्ण

/**
 * mem_cgroup_page_lruvec - वापस lruvec क्रम isolating/putting an LRU page
 * @page: the page
 * @pgdat: pgdat of the page
 *
 * This function relies on page->mem_cgroup being stable.
 */
अटल अंतरभूत काष्ठा lruvec *mem_cgroup_page_lruvec(काष्ठा page *page,
						काष्ठा pglist_data *pgdat)
अणु
	काष्ठा mem_cgroup *memcg = page_memcg(page);

	VM_WARN_ON_ONCE_PAGE(!memcg && !mem_cgroup_disabled(), page);
	वापस mem_cgroup_lruvec(memcg, pgdat);
पूर्ण

अटल अंतरभूत bool lruvec_holds_page_lru_lock(काष्ठा page *page,
					      काष्ठा lruvec *lruvec)
अणु
	pg_data_t *pgdat = page_pgdat(page);
	स्थिर काष्ठा mem_cgroup *memcg;
	काष्ठा mem_cgroup_per_node *mz;

	अगर (mem_cgroup_disabled())
		वापस lruvec == &pgdat->__lruvec;

	mz = container_of(lruvec, काष्ठा mem_cgroup_per_node, lruvec);
	memcg = page_memcg(page) ? : root_mem_cgroup;

	वापस lruvec->pgdat == pgdat && mz->memcg == memcg;
पूर्ण

काष्ठा mem_cgroup *mem_cgroup_from_task(काष्ठा task_काष्ठा *p);

काष्ठा mem_cgroup *get_mem_cgroup_from_mm(काष्ठा mm_काष्ठा *mm);

काष्ठा lruvec *lock_page_lruvec(काष्ठा page *page);
काष्ठा lruvec *lock_page_lruvec_irq(काष्ठा page *page);
काष्ठा lruvec *lock_page_lruvec_irqsave(काष्ठा page *page,
						अचिन्हित दीर्घ *flags);

#अगर_घोषित CONFIG_DEBUG_VM
व्योम lruvec_memcg_debug(काष्ठा lruvec *lruvec, काष्ठा page *page);
#अन्यथा
अटल अंतरभूत व्योम lruvec_memcg_debug(काष्ठा lruvec *lruvec, काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत
काष्ठा mem_cgroup *mem_cgroup_from_css(काष्ठा cgroup_subsys_state *css)अणु
	वापस css ? container_of(css, काष्ठा mem_cgroup, css) : शून्य;
पूर्ण

अटल अंतरभूत bool obj_cgroup_tryget(काष्ठा obj_cgroup *objcg)
अणु
	वापस percpu_ref_tryget(&objcg->refcnt);
पूर्ण

अटल अंतरभूत व्योम obj_cgroup_get(काष्ठा obj_cgroup *objcg)
अणु
	percpu_ref_get(&objcg->refcnt);
पूर्ण

अटल अंतरभूत व्योम obj_cgroup_get_many(काष्ठा obj_cgroup *objcg,
				       अचिन्हित दीर्घ nr)
अणु
	percpu_ref_get_many(&objcg->refcnt, nr);
पूर्ण

अटल अंतरभूत व्योम obj_cgroup_put(काष्ठा obj_cgroup *objcg)
अणु
	percpu_ref_put(&objcg->refcnt);
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_put(काष्ठा mem_cgroup *memcg)
अणु
	अगर (memcg)
		css_put(&memcg->css);
पूर्ण

#घोषणा mem_cgroup_from_counter(counter, member)	\
	container_of(counter, काष्ठा mem_cgroup, member)

काष्ठा mem_cgroup *mem_cgroup_iter(काष्ठा mem_cgroup *,
				   काष्ठा mem_cgroup *,
				   काष्ठा mem_cgroup_reclaim_cookie *);
व्योम mem_cgroup_iter_अवरोध(काष्ठा mem_cgroup *, काष्ठा mem_cgroup *);
पूर्णांक mem_cgroup_scan_tasks(काष्ठा mem_cgroup *,
			  पूर्णांक (*)(काष्ठा task_काष्ठा *, व्योम *), व्योम *);

अटल अंतरभूत अचिन्हित लघु mem_cgroup_id(काष्ठा mem_cgroup *memcg)
अणु
	अगर (mem_cgroup_disabled())
		वापस 0;

	वापस memcg->id.id;
पूर्ण
काष्ठा mem_cgroup *mem_cgroup_from_id(अचिन्हित लघु id);

अटल अंतरभूत काष्ठा mem_cgroup *mem_cgroup_from_seq(काष्ठा seq_file *m)
अणु
	वापस mem_cgroup_from_css(seq_css(m));
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *lruvec_memcg(काष्ठा lruvec *lruvec)
अणु
	काष्ठा mem_cgroup_per_node *mz;

	अगर (mem_cgroup_disabled())
		वापस शून्य;

	mz = container_of(lruvec, काष्ठा mem_cgroup_per_node, lruvec);
	वापस mz->memcg;
पूर्ण

/**
 * parent_mem_cgroup - find the accounting parent of a memcg
 * @memcg: memcg whose parent to find
 *
 * Returns the parent memcg, or शून्य अगर this is the root or the memory
 * controller is in legacy no-hierarchy mode.
 */
अटल अंतरभूत काष्ठा mem_cgroup *parent_mem_cgroup(काष्ठा mem_cgroup *memcg)
अणु
	अगर (!memcg->memory.parent)
		वापस शून्य;
	वापस mem_cgroup_from_counter(memcg->memory.parent, memory);
पूर्ण

अटल अंतरभूत bool mem_cgroup_is_descendant(काष्ठा mem_cgroup *memcg,
			      काष्ठा mem_cgroup *root)
अणु
	अगर (root == memcg)
		वापस true;
	वापस cgroup_is_descendant(memcg->css.cgroup, root->css.cgroup);
पूर्ण

अटल अंतरभूत bool mm_match_cgroup(काष्ठा mm_काष्ठा *mm,
				   काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *task_memcg;
	bool match = false;

	rcu_पढ़ो_lock();
	task_memcg = mem_cgroup_from_task(rcu_dereference(mm->owner));
	अगर (task_memcg)
		match = mem_cgroup_is_descendant(task_memcg, memcg);
	rcu_पढ़ो_unlock();
	वापस match;
पूर्ण

काष्ठा cgroup_subsys_state *mem_cgroup_css_from_page(काष्ठा page *page);
ino_t page_cgroup_ino(काष्ठा page *page);

अटल अंतरभूत bool mem_cgroup_online(काष्ठा mem_cgroup *memcg)
अणु
	अगर (mem_cgroup_disabled())
		वापस true;
	वापस !!(memcg->css.flags & CSS_ONLINE);
पूर्ण

/*
 * For memory reclaim.
 */
पूर्णांक mem_cgroup_select_victim_node(काष्ठा mem_cgroup *memcg);

व्योम mem_cgroup_update_lru_size(काष्ठा lruvec *lruvec, क्रमागत lru_list lru,
		पूर्णांक zid, पूर्णांक nr_pages);

अटल अंतरभूत
अचिन्हित दीर्घ mem_cgroup_get_zone_lru_size(काष्ठा lruvec *lruvec,
		क्रमागत lru_list lru, पूर्णांक zone_idx)
अणु
	काष्ठा mem_cgroup_per_node *mz;

	mz = container_of(lruvec, काष्ठा mem_cgroup_per_node, lruvec);
	वापस READ_ONCE(mz->lru_zone_size[zone_idx][lru]);
पूर्ण

व्योम mem_cgroup_handle_over_high(व्योम);

अचिन्हित दीर्घ mem_cgroup_get_max(काष्ठा mem_cgroup *memcg);

अचिन्हित दीर्घ mem_cgroup_size(काष्ठा mem_cgroup *memcg);

व्योम mem_cgroup_prपूर्णांक_oom_context(काष्ठा mem_cgroup *memcg,
				काष्ठा task_काष्ठा *p);

व्योम mem_cgroup_prपूर्णांक_oom_meminfo(काष्ठा mem_cgroup *memcg);

अटल अंतरभूत व्योम mem_cgroup_enter_user_fault(व्योम)
अणु
	WARN_ON(current->in_user_fault);
	current->in_user_fault = 1;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_निकास_user_fault(व्योम)
अणु
	WARN_ON(!current->in_user_fault);
	current->in_user_fault = 0;
पूर्ण

अटल अंतरभूत bool task_in_memcg_oom(काष्ठा task_काष्ठा *p)
अणु
	वापस p->memcg_in_oom;
पूर्ण

bool mem_cgroup_oom_synchronize(bool रुको);
काष्ठा mem_cgroup *mem_cgroup_get_oom_group(काष्ठा task_काष्ठा *victim,
					    काष्ठा mem_cgroup *oom_करोमुख्य);
व्योम mem_cgroup_prपूर्णांक_oom_group(काष्ठा mem_cgroup *memcg);

#अगर_घोषित CONFIG_MEMCG_SWAP
बाह्य bool cgroup_memory_noswap;
#पूर्ण_अगर

व्योम lock_page_memcg(काष्ठा page *page);
व्योम unlock_page_memcg(काष्ठा page *page);

व्योम __mod_memcg_state(काष्ठा mem_cgroup *memcg, पूर्णांक idx, पूर्णांक val);

/* idx can be of type क्रमागत memcg_stat_item or node_stat_item */
अटल अंतरभूत व्योम mod_memcg_state(काष्ठा mem_cgroup *memcg,
				   पूर्णांक idx, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__mod_memcg_state(memcg, idx, val);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ lruvec_page_state(काष्ठा lruvec *lruvec,
					      क्रमागत node_stat_item idx)
अणु
	काष्ठा mem_cgroup_per_node *pn;
	दीर्घ x;

	अगर (mem_cgroup_disabled())
		वापस node_page_state(lruvec_pgdat(lruvec), idx);

	pn = container_of(lruvec, काष्ठा mem_cgroup_per_node, lruvec);
	x = atomic_दीर्घ_पढ़ो(&pn->lruvec_stat[idx]);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ lruvec_page_state_local(काष्ठा lruvec *lruvec,
						    क्रमागत node_stat_item idx)
अणु
	काष्ठा mem_cgroup_per_node *pn;
	दीर्घ x = 0;
	पूर्णांक cpu;

	अगर (mem_cgroup_disabled())
		वापस node_page_state(lruvec_pgdat(lruvec), idx);

	pn = container_of(lruvec, काष्ठा mem_cgroup_per_node, lruvec);
	क्रम_each_possible_cpu(cpu)
		x += per_cpu(pn->lruvec_stat_local->count[idx], cpu);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

व्योम __mod_memcg_lruvec_state(काष्ठा lruvec *lruvec, क्रमागत node_stat_item idx,
			      पूर्णांक val);
व्योम __mod_lruvec_kmem_state(व्योम *p, क्रमागत node_stat_item idx, पूर्णांक val);

अटल अंतरभूत व्योम mod_lruvec_kmem_state(व्योम *p, क्रमागत node_stat_item idx,
					 पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__mod_lruvec_kmem_state(p, idx, val);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम mod_memcg_lruvec_state(काष्ठा lruvec *lruvec,
					  क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__mod_memcg_lruvec_state(lruvec, idx, val);
	local_irq_restore(flags);
पूर्ण

व्योम __count_memcg_events(काष्ठा mem_cgroup *memcg, क्रमागत vm_event_item idx,
			  अचिन्हित दीर्घ count);

अटल अंतरभूत व्योम count_memcg_events(काष्ठा mem_cgroup *memcg,
				      क्रमागत vm_event_item idx,
				      अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__count_memcg_events(memcg, idx, count);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम count_memcg_page_event(काष्ठा page *page,
					  क्रमागत vm_event_item idx)
अणु
	काष्ठा mem_cgroup *memcg = page_memcg(page);

	अगर (memcg)
		count_memcg_events(memcg, idx, 1);
पूर्ण

अटल अंतरभूत व्योम count_memcg_event_mm(काष्ठा mm_काष्ठा *mm,
					क्रमागत vm_event_item idx)
अणु
	काष्ठा mem_cgroup *memcg;

	अगर (mem_cgroup_disabled())
		वापस;

	rcu_पढ़ो_lock();
	memcg = mem_cgroup_from_task(rcu_dereference(mm->owner));
	अगर (likely(memcg))
		count_memcg_events(memcg, idx, 1);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम memcg_memory_event(काष्ठा mem_cgroup *memcg,
				      क्रमागत memcg_memory_event event)
अणु
	bool swap_event = event == MEMCG_SWAP_HIGH || event == MEMCG_SWAP_MAX ||
			  event == MEMCG_SWAP_FAIL;

	atomic_दीर्घ_inc(&memcg->memory_events_local[event]);
	अगर (!swap_event)
		cgroup_file_notअगरy(&memcg->events_local_file);

	करो अणु
		atomic_दीर्घ_inc(&memcg->memory_events[event]);
		अगर (swap_event)
			cgroup_file_notअगरy(&memcg->swap_events_file);
		अन्यथा
			cgroup_file_notअगरy(&memcg->events_file);

		अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys))
			अवरोध;
		अगर (cgrp_dfl_root.flags & CGRP_ROOT_MEMORY_LOCAL_EVENTS)
			अवरोध;
	पूर्ण जबतक ((memcg = parent_mem_cgroup(memcg)) &&
		 !mem_cgroup_is_root(memcg));
पूर्ण

अटल अंतरभूत व्योम memcg_memory_event_mm(काष्ठा mm_काष्ठा *mm,
					 क्रमागत memcg_memory_event event)
अणु
	काष्ठा mem_cgroup *memcg;

	अगर (mem_cgroup_disabled())
		वापस;

	rcu_पढ़ो_lock();
	memcg = mem_cgroup_from_task(rcu_dereference(mm->owner));
	अगर (likely(memcg))
		memcg_memory_event(memcg, event);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम split_page_memcg(काष्ठा page *head, अचिन्हित पूर्णांक nr);

अचिन्हित दीर्घ mem_cgroup_soft_limit_reclaim(pg_data_t *pgdat, पूर्णांक order,
						gfp_t gfp_mask,
						अचिन्हित दीर्घ *total_scanned);

#अन्यथा /* CONFIG_MEMCG */

#घोषणा MEM_CGROUP_ID_SHIFT	0
#घोषणा MEM_CGROUP_ID_MAX	0

अटल अंतरभूत काष्ठा mem_cgroup *page_memcg(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *page_memcg_rcu(काष्ठा page *page)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *page_memcg_check(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool PageMemcgKmem(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool mem_cgroup_is_root(काष्ठा mem_cgroup *memcg)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool mem_cgroup_disabled(व्योम)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम memcg_memory_event(काष्ठा mem_cgroup *memcg,
				      क्रमागत memcg_memory_event event)
अणु
पूर्ण

अटल अंतरभूत व्योम memcg_memory_event_mm(काष्ठा mm_काष्ठा *mm,
					 क्रमागत memcg_memory_event event)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mem_cgroup_protection(काष्ठा mem_cgroup *root,
						  काष्ठा mem_cgroup *memcg,
						  bool in_low_reclaim)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_calculate_protection(काष्ठा mem_cgroup *root,
						   काष्ठा mem_cgroup *memcg)
अणु
पूर्ण

अटल अंतरभूत bool mem_cgroup_below_low(काष्ठा mem_cgroup *memcg)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool mem_cgroup_below_min(काष्ठा mem_cgroup *memcg)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक mem_cgroup_अक्षरge(काष्ठा page *page, काष्ठा mm_काष्ठा *mm,
				    gfp_t gfp_mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mem_cgroup_swapin_अक्षरge_page(काष्ठा page *page,
			काष्ठा mm_काष्ठा *mm, gfp_t gfp, swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_swapin_unअक्षरge_swap(swp_entry_t entry)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_unअक्षरge(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_unअक्षरge_list(काष्ठा list_head *page_list)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_migrate(काष्ठा page *old, काष्ठा page *new)
अणु
पूर्ण

अटल अंतरभूत काष्ठा lruvec *mem_cgroup_lruvec(काष्ठा mem_cgroup *memcg,
					       काष्ठा pglist_data *pgdat)
अणु
	वापस &pgdat->__lruvec;
पूर्ण

अटल अंतरभूत काष्ठा lruvec *mem_cgroup_page_lruvec(काष्ठा page *page,
						    काष्ठा pglist_data *pgdat)
अणु
	वापस &pgdat->__lruvec;
पूर्ण

अटल अंतरभूत bool lruvec_holds_page_lru_lock(काष्ठा page *page,
					      काष्ठा lruvec *lruvec)
अणु
	pg_data_t *pgdat = page_pgdat(page);

	वापस lruvec == &pgdat->__lruvec;
पूर्ण

अटल अंतरभूत व्योम lruvec_memcg_debug(काष्ठा lruvec *lruvec, काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *parent_mem_cgroup(काष्ठा mem_cgroup *memcg)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool mm_match_cgroup(काष्ठा mm_काष्ठा *mm,
		काष्ठा mem_cgroup *memcg)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *get_mem_cgroup_from_mm(काष्ठा mm_काष्ठा *mm)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_put(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण

अटल अंतरभूत काष्ठा lruvec *lock_page_lruvec(काष्ठा page *page)
अणु
	काष्ठा pglist_data *pgdat = page_pgdat(page);

	spin_lock(&pgdat->__lruvec.lru_lock);
	वापस &pgdat->__lruvec;
पूर्ण

अटल अंतरभूत काष्ठा lruvec *lock_page_lruvec_irq(काष्ठा page *page)
अणु
	काष्ठा pglist_data *pgdat = page_pgdat(page);

	spin_lock_irq(&pgdat->__lruvec.lru_lock);
	वापस &pgdat->__lruvec;
पूर्ण

अटल अंतरभूत काष्ठा lruvec *lock_page_lruvec_irqsave(काष्ठा page *page,
		अचिन्हित दीर्घ *flagsp)
अणु
	काष्ठा pglist_data *pgdat = page_pgdat(page);

	spin_lock_irqsave(&pgdat->__lruvec.lru_lock, *flagsp);
	वापस &pgdat->__lruvec;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *
mem_cgroup_iter(काष्ठा mem_cgroup *root,
		काष्ठा mem_cgroup *prev,
		काष्ठा mem_cgroup_reclaim_cookie *reclaim)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_iter_अवरोध(काष्ठा mem_cgroup *root,
					 काष्ठा mem_cgroup *prev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mem_cgroup_scan_tasks(काष्ठा mem_cgroup *memcg,
		पूर्णांक (*fn)(काष्ठा task_काष्ठा *, व्योम *), व्योम *arg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित लघु mem_cgroup_id(काष्ठा mem_cgroup *memcg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *mem_cgroup_from_id(अचिन्हित लघु id)
अणु
	WARN_ON_ONCE(id);
	/* XXX: This should always वापस root_mem_cgroup */
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *mem_cgroup_from_seq(काष्ठा seq_file *m)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *lruvec_memcg(काष्ठा lruvec *lruvec)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool mem_cgroup_online(काष्ठा mem_cgroup *memcg)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ mem_cgroup_get_zone_lru_size(काष्ठा lruvec *lruvec,
		क्रमागत lru_list lru, पूर्णांक zone_idx)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mem_cgroup_get_max(काष्ठा mem_cgroup *memcg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mem_cgroup_size(काष्ठा mem_cgroup *memcg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
mem_cgroup_prपूर्णांक_oom_context(काष्ठा mem_cgroup *memcg, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत व्योम
mem_cgroup_prपूर्णांक_oom_meminfo(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण

अटल अंतरभूत व्योम lock_page_memcg(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम unlock_page_memcg(काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_handle_over_high(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_enter_user_fault(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_निकास_user_fault(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool task_in_memcg_oom(काष्ठा task_काष्ठा *p)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool mem_cgroup_oom_synchronize(bool रुको)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *mem_cgroup_get_oom_group(
	काष्ठा task_काष्ठा *victim, काष्ठा mem_cgroup *oom_करोमुख्य)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_prपूर्णांक_oom_group(काष्ठा mem_cgroup *memcg)
अणु
पूर्ण

अटल अंतरभूत व्योम __mod_memcg_state(काष्ठा mem_cgroup *memcg,
				     पूर्णांक idx,
				     पूर्णांक nr)
अणु
पूर्ण

अटल अंतरभूत व्योम mod_memcg_state(काष्ठा mem_cgroup *memcg,
				   पूर्णांक idx,
				   पूर्णांक nr)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ lruvec_page_state(काष्ठा lruvec *lruvec,
					      क्रमागत node_stat_item idx)
अणु
	वापस node_page_state(lruvec_pgdat(lruvec), idx);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ lruvec_page_state_local(काष्ठा lruvec *lruvec,
						    क्रमागत node_stat_item idx)
अणु
	वापस node_page_state(lruvec_pgdat(lruvec), idx);
पूर्ण

अटल अंतरभूत व्योम __mod_memcg_lruvec_state(काष्ठा lruvec *lruvec,
					    क्रमागत node_stat_item idx, पूर्णांक val)
अणु
पूर्ण

अटल अंतरभूत व्योम __mod_lruvec_kmem_state(व्योम *p, क्रमागत node_stat_item idx,
					   पूर्णांक val)
अणु
	काष्ठा page *page = virt_to_head_page(p);

	__mod_node_page_state(page_pgdat(page), idx, val);
पूर्ण

अटल अंतरभूत व्योम mod_lruvec_kmem_state(व्योम *p, क्रमागत node_stat_item idx,
					 पूर्णांक val)
अणु
	काष्ठा page *page = virt_to_head_page(p);

	mod_node_page_state(page_pgdat(page), idx, val);
पूर्ण

अटल अंतरभूत व्योम count_memcg_events(काष्ठा mem_cgroup *memcg,
				      क्रमागत vm_event_item idx,
				      अचिन्हित दीर्घ count)
अणु
पूर्ण

अटल अंतरभूत व्योम __count_memcg_events(काष्ठा mem_cgroup *memcg,
					क्रमागत vm_event_item idx,
					अचिन्हित दीर्घ count)
अणु
पूर्ण

अटल अंतरभूत व्योम count_memcg_page_event(काष्ठा page *page,
					  पूर्णांक idx)
अणु
पूर्ण

अटल अंतरभूत
व्योम count_memcg_event_mm(काष्ठा mm_काष्ठा *mm, क्रमागत vm_event_item idx)
अणु
पूर्ण

अटल अंतरभूत व्योम split_page_memcg(काष्ठा page *head, अचिन्हित पूर्णांक nr)
अणु
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ mem_cgroup_soft_limit_reclaim(pg_data_t *pgdat, पूर्णांक order,
					    gfp_t gfp_mask,
					    अचिन्हित दीर्घ *total_scanned)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG */

अटल अंतरभूत व्योम __inc_lruvec_kmem_state(व्योम *p, क्रमागत node_stat_item idx)
अणु
	__mod_lruvec_kmem_state(p, idx, 1);
पूर्ण

अटल अंतरभूत व्योम __dec_lruvec_kmem_state(व्योम *p, क्रमागत node_stat_item idx)
अणु
	__mod_lruvec_kmem_state(p, idx, -1);
पूर्ण

अटल अंतरभूत काष्ठा lruvec *parent_lruvec(काष्ठा lruvec *lruvec)
अणु
	काष्ठा mem_cgroup *memcg;

	memcg = lruvec_memcg(lruvec);
	अगर (!memcg)
		वापस शून्य;
	memcg = parent_mem_cgroup(memcg);
	अगर (!memcg)
		वापस शून्य;
	वापस mem_cgroup_lruvec(memcg, lruvec_pgdat(lruvec));
पूर्ण

अटल अंतरभूत व्योम unlock_page_lruvec(काष्ठा lruvec *lruvec)
अणु
	spin_unlock(&lruvec->lru_lock);
पूर्ण

अटल अंतरभूत व्योम unlock_page_lruvec_irq(काष्ठा lruvec *lruvec)
अणु
	spin_unlock_irq(&lruvec->lru_lock);
पूर्ण

अटल अंतरभूत व्योम unlock_page_lruvec_irqrestore(काष्ठा lruvec *lruvec,
		अचिन्हित दीर्घ flags)
अणु
	spin_unlock_irqrestore(&lruvec->lru_lock, flags);
पूर्ण

/* Don't lock again iff page's lruvec locked */
अटल अंतरभूत काष्ठा lruvec *relock_page_lruvec_irq(काष्ठा page *page,
		काष्ठा lruvec *locked_lruvec)
अणु
	अगर (locked_lruvec) अणु
		अगर (lruvec_holds_page_lru_lock(page, locked_lruvec))
			वापस locked_lruvec;

		unlock_page_lruvec_irq(locked_lruvec);
	पूर्ण

	वापस lock_page_lruvec_irq(page);
पूर्ण

/* Don't lock again iff page's lruvec locked */
अटल अंतरभूत काष्ठा lruvec *relock_page_lruvec_irqsave(काष्ठा page *page,
		काष्ठा lruvec *locked_lruvec, अचिन्हित दीर्घ *flags)
अणु
	अगर (locked_lruvec) अणु
		अगर (lruvec_holds_page_lru_lock(page, locked_lruvec))
			वापस locked_lruvec;

		unlock_page_lruvec_irqrestore(locked_lruvec, *flags);
	पूर्ण

	वापस lock_page_lruvec_irqsave(page, flags);
पूर्ण

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

काष्ठा wb_करोमुख्य *mem_cgroup_wb_करोमुख्य(काष्ठा bdi_ग_लिखोback *wb);
व्योम mem_cgroup_wb_stats(काष्ठा bdi_ग_लिखोback *wb, अचिन्हित दीर्घ *pfilepages,
			 अचिन्हित दीर्घ *pheadroom, अचिन्हित दीर्घ *pdirty,
			 अचिन्हित दीर्घ *pग_लिखोback);

व्योम mem_cgroup_track_क्रमeign_dirty_slowpath(काष्ठा page *page,
					     काष्ठा bdi_ग_लिखोback *wb);

अटल अंतरभूत व्योम mem_cgroup_track_क्रमeign_dirty(काष्ठा page *page,
						  काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (mem_cgroup_disabled())
		वापस;

	अगर (unlikely(&page_memcg(page)->css != wb->memcg_css))
		mem_cgroup_track_क्रमeign_dirty_slowpath(page, wb);
पूर्ण

व्योम mem_cgroup_flush_क्रमeign(काष्ठा bdi_ग_लिखोback *wb);

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

अटल अंतरभूत काष्ठा wb_करोमुख्य *mem_cgroup_wb_करोमुख्य(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_wb_stats(काष्ठा bdi_ग_लिखोback *wb,
				       अचिन्हित दीर्घ *pfilepages,
				       अचिन्हित दीर्घ *pheadroom,
				       अचिन्हित दीर्घ *pdirty,
				       अचिन्हित दीर्घ *pग_लिखोback)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_track_क्रमeign_dirty(काष्ठा page *page,
						  काष्ठा bdi_ग_लिखोback *wb)
अणु
पूर्ण

अटल अंतरभूत व्योम mem_cgroup_flush_क्रमeign(काष्ठा bdi_ग_लिखोback *wb)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

काष्ठा sock;
bool mem_cgroup_अक्षरge_skmem(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक nr_pages);
व्योम mem_cgroup_unअक्षरge_skmem(काष्ठा mem_cgroup *memcg, अचिन्हित पूर्णांक nr_pages);
#अगर_घोषित CONFIG_MEMCG
बाह्य काष्ठा अटल_key_false memcg_sockets_enabled_key;
#घोषणा mem_cgroup_sockets_enabled अटल_branch_unlikely(&memcg_sockets_enabled_key)
व्योम mem_cgroup_sk_alloc(काष्ठा sock *sk);
व्योम mem_cgroup_sk_मुक्त(काष्ठा sock *sk);
अटल अंतरभूत bool mem_cgroup_under_socket_pressure(काष्ठा mem_cgroup *memcg)
अणु
	अगर (!cgroup_subsys_on_dfl(memory_cgrp_subsys) && memcg->tcpmem_pressure)
		वापस true;
	करो अणु
		अगर (समय_beक्रमe(jअगरfies, memcg->socket_pressure))
			वापस true;
	पूर्ण जबतक ((memcg = parent_mem_cgroup(memcg)));
	वापस false;
पूर्ण

पूर्णांक alloc_shrinker_info(काष्ठा mem_cgroup *memcg);
व्योम मुक्त_shrinker_info(काष्ठा mem_cgroup *memcg);
व्योम set_shrinker_bit(काष्ठा mem_cgroup *memcg, पूर्णांक nid, पूर्णांक shrinker_id);
व्योम reparent_shrinker_deferred(काष्ठा mem_cgroup *memcg);
#अन्यथा
#घोषणा mem_cgroup_sockets_enabled 0
अटल अंतरभूत व्योम mem_cgroup_sk_alloc(काष्ठा sock *sk) अणु पूर्ण;
अटल अंतरभूत व्योम mem_cgroup_sk_मुक्त(काष्ठा sock *sk) अणु पूर्ण;
अटल अंतरभूत bool mem_cgroup_under_socket_pressure(काष्ठा mem_cgroup *memcg)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम set_shrinker_bit(काष्ठा mem_cgroup *memcg,
				    पूर्णांक nid, पूर्णांक shrinker_id)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMCG_KMEM
पूर्णांक __memcg_kmem_अक्षरge_page(काष्ठा page *page, gfp_t gfp, पूर्णांक order);
व्योम __memcg_kmem_unअक्षरge_page(काष्ठा page *page, पूर्णांक order);

काष्ठा obj_cgroup *get_obj_cgroup_from_current(व्योम);

पूर्णांक obj_cgroup_अक्षरge(काष्ठा obj_cgroup *objcg, gfp_t gfp, माप_प्रकार size);
व्योम obj_cgroup_unअक्षरge(काष्ठा obj_cgroup *objcg, माप_प्रकार size);

बाह्य काष्ठा अटल_key_false memcg_kmem_enabled_key;

बाह्य पूर्णांक memcg_nr_cache_ids;
व्योम memcg_get_cache_ids(व्योम);
व्योम memcg_put_cache_ids(व्योम);

/*
 * Helper macro to loop through all memcg-specअगरic caches. Callers must still
 * check अगर the cache is valid (it is either valid or शून्य).
 * the slab_mutex must be held when looping through those caches
 */
#घोषणा क्रम_each_memcg_cache_index(_idx)	\
	क्रम ((_idx) = 0; (_idx) < memcg_nr_cache_ids; (_idx)++)

अटल अंतरभूत bool memcg_kmem_enabled(व्योम)
अणु
	वापस अटल_branch_likely(&memcg_kmem_enabled_key);
पूर्ण

अटल अंतरभूत पूर्णांक memcg_kmem_अक्षरge_page(काष्ठा page *page, gfp_t gfp,
					 पूर्णांक order)
अणु
	अगर (memcg_kmem_enabled())
		वापस __memcg_kmem_अक्षरge_page(page, gfp, order);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम memcg_kmem_unअक्षरge_page(काष्ठा page *page, पूर्णांक order)
अणु
	अगर (memcg_kmem_enabled())
		__memcg_kmem_unअक्षरge_page(page, order);
पूर्ण

/*
 * A helper क्रम accessing memcg's kmem_id, used क्रम getting
 * corresponding LRU lists.
 */
अटल अंतरभूत पूर्णांक memcg_cache_id(काष्ठा mem_cgroup *memcg)
अणु
	वापस memcg ? memcg->kmemcg_id : -1;
पूर्ण

काष्ठा mem_cgroup *mem_cgroup_from_obj(व्योम *p);

#अन्यथा

अटल अंतरभूत पूर्णांक memcg_kmem_अक्षरge_page(काष्ठा page *page, gfp_t gfp,
					 पूर्णांक order)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम memcg_kmem_unअक्षरge_page(काष्ठा page *page, पूर्णांक order)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __memcg_kmem_अक्षरge_page(काष्ठा page *page, gfp_t gfp,
					   पूर्णांक order)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __memcg_kmem_unअक्षरge_page(काष्ठा page *page, पूर्णांक order)
अणु
पूर्ण

#घोषणा क्रम_each_memcg_cache_index(_idx)	\
	क्रम (; शून्य; )

अटल अंतरभूत bool memcg_kmem_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक memcg_cache_id(काष्ठा mem_cgroup *memcg)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम memcg_get_cache_ids(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम memcg_put_cache_ids(व्योम)
अणु
पूर्ण

अटल अंतरभूत काष्ठा mem_cgroup *mem_cgroup_from_obj(व्योम *p)
अणु
       वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_MEMCG_KMEM */

#पूर्ण_अगर /* _LINUX_MEMCONTROL_H */
