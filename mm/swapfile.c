<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/swapfile.c
 *
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *  Swap reorganised 29.12.95, Stephen Tweedie
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/mman.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/swap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/namei.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/ksm.h>
#समावेश <linux/rmap.h>
#समावेश <linux/security.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/capability.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/poll.h>
#समावेश <linux/oom.h>
#समावेश <linux/frontswap.h>
#समावेश <linux/swapfile.h>
#समावेश <linux/export.h>
#समावेश <linux/swap_slots.h>
#समावेश <linux/sort.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/swapops.h>
#समावेश <linux/swap_cgroup.h>

अटल bool swap_count_जारीd(काष्ठा swap_info_काष्ठा *, pgoff_t,
				 अचिन्हित अक्षर);
अटल व्योम मुक्त_swap_count_continuations(काष्ठा swap_info_काष्ठा *);

DEFINE_SPINLOCK(swap_lock);
अटल अचिन्हित पूर्णांक nr_swapfiles;
atomic_दीर्घ_t nr_swap_pages;
/*
 * Some modules use swappable objects and may try to swap them out under
 * memory pressure (via the shrinker). Beक्रमe करोing so, they may wish to
 * check to see अगर any swap space is available.
 */
EXPORT_SYMBOL_GPL(nr_swap_pages);
/* रक्षित with swap_lock. पढ़ोing in vm_swap_full() करोesn't need lock */
दीर्घ total_swap_pages;
अटल पूर्णांक least_priority = -1;

अटल स्थिर अक्षर Bad_file[] = "Bad swap file entry ";
अटल स्थिर अक्षर Unused_file[] = "Unused swap file entry ";
अटल स्थिर अक्षर Bad_offset[] = "Bad swap offset entry ";
अटल स्थिर अक्षर Unused_offset[] = "Unused swap offset entry ";

/*
 * all active swap_info_काष्ठाs
 * रक्षित with swap_lock, and ordered by priority.
 */
PLIST_HEAD(swap_active_head);

/*
 * all available (active, not full) swap_info_काष्ठाs
 * रक्षित with swap_avail_lock, ordered by priority.
 * This is used by get_swap_page() instead of swap_active_head
 * because swap_active_head includes all swap_info_काष्ठाs,
 * but get_swap_page() करोesn't need to look at full ones.
 * This uses its own lock instead of swap_lock because when a
 * swap_info_काष्ठा changes between not-full/full, it needs to
 * add/हटाओ itself to/from this list, but the swap_info_काष्ठा->lock
 * is held and the locking order requires swap_lock to be taken
 * beक्रमe any swap_info_काष्ठा->lock.
 */
अटल काष्ठा plist_head *swap_avail_heads;
अटल DEFINE_SPINLOCK(swap_avail_lock);

काष्ठा swap_info_काष्ठा *swap_info[MAX_SWAPखाताS];

अटल DEFINE_MUTEX(swapon_mutex);

अटल DECLARE_WAIT_QUEUE_HEAD(proc_poll_रुको);
/* Activity counter to indicate that a swapon or swapoff has occurred */
अटल atomic_t proc_poll_event = ATOMIC_INIT(0);

atomic_t nr_rotate_swap = ATOMIC_INIT(0);

अटल काष्ठा swap_info_काष्ठा *swap_type_to_swap_info(पूर्णांक type)
अणु
	अगर (type >= READ_ONCE(nr_swapfiles))
		वापस शून्य;

	smp_rmb();	/* Pairs with smp_wmb in alloc_swap_info. */
	वापस READ_ONCE(swap_info[type]);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर swap_count(अचिन्हित अक्षर ent)
अणु
	वापस ent & ~SWAP_HAS_CACHE;	/* may include COUNT_CONTINUED flag */
पूर्ण

/* Reclaim the swap entry anyway अगर possible */
#घोषणा TTRS_ANYWAY		0x1
/*
 * Reclaim the swap entry अगर there are no more mappings of the
 * corresponding page
 */
#घोषणा TTRS_UNMAPPED		0x2
/* Reclaim the swap entry अगर swap is getting full*/
#घोषणा TTRS_FULL		0x4

/* वापसs 1 अगर swap entry is मुक्तd */
अटल पूर्णांक __try_to_reclaim_swap(काष्ठा swap_info_काष्ठा *si,
				 अचिन्हित दीर्घ offset, अचिन्हित दीर्घ flags)
अणु
	swp_entry_t entry = swp_entry(si->type, offset);
	काष्ठा page *page;
	पूर्णांक ret = 0;

	page = find_get_page(swap_address_space(entry), offset);
	अगर (!page)
		वापस 0;
	/*
	 * When this function is called from scan_swap_map_slots() and it's
	 * called by vmscan.c at reclaiming pages. So, we hold a lock on a page,
	 * here. We have to use trylock क्रम aव्योमing deadlock. This is a special
	 * हाल and you should use try_to_मुक्त_swap() with explicit lock_page()
	 * in usual operations.
	 */
	अगर (trylock_page(page)) अणु
		अगर ((flags & TTRS_ANYWAY) ||
		    ((flags & TTRS_UNMAPPED) && !page_mapped(page)) ||
		    ((flags & TTRS_FULL) && mem_cgroup_swap_full(page)))
			ret = try_to_मुक्त_swap(page);
		unlock_page(page);
	पूर्ण
	put_page(page);
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा swap_extent *first_se(काष्ठा swap_info_काष्ठा *sis)
अणु
	काष्ठा rb_node *rb = rb_first(&sis->swap_extent_root);
	वापस rb_entry(rb, काष्ठा swap_extent, rb_node);
पूर्ण

अटल अंतरभूत काष्ठा swap_extent *next_se(काष्ठा swap_extent *se)
अणु
	काष्ठा rb_node *rb = rb_next(&se->rb_node);
	वापस rb ? rb_entry(rb, काष्ठा swap_extent, rb_node) : शून्य;
पूर्ण

/*
 * swapon tell device that all the old swap contents can be discarded,
 * to allow the swap device to optimize its wear-levelling.
 */
अटल पूर्णांक discard_swap(काष्ठा swap_info_काष्ठा *si)
अणु
	काष्ठा swap_extent *se;
	sector_t start_block;
	sector_t nr_blocks;
	पूर्णांक err = 0;

	/* Do not discard the swap header page! */
	se = first_se(si);
	start_block = (se->start_block + 1) << (PAGE_SHIFT - 9);
	nr_blocks = ((sector_t)se->nr_pages - 1) << (PAGE_SHIFT - 9);
	अगर (nr_blocks) अणु
		err = blkdev_issue_discard(si->bdev, start_block,
				nr_blocks, GFP_KERNEL, 0);
		अगर (err)
			वापस err;
		cond_resched();
	पूर्ण

	क्रम (se = next_se(se); se; se = next_se(se)) अणु
		start_block = se->start_block << (PAGE_SHIFT - 9);
		nr_blocks = (sector_t)se->nr_pages << (PAGE_SHIFT - 9);

		err = blkdev_issue_discard(si->bdev, start_block,
				nr_blocks, GFP_KERNEL, 0);
		अगर (err)
			अवरोध;

		cond_resched();
	पूर्ण
	वापस err;		/* That will often be -EOPNOTSUPP */
पूर्ण

अटल काष्ठा swap_extent *
offset_to_swap_extent(काष्ठा swap_info_काष्ठा *sis, अचिन्हित दीर्घ offset)
अणु
	काष्ठा swap_extent *se;
	काष्ठा rb_node *rb;

	rb = sis->swap_extent_root.rb_node;
	जबतक (rb) अणु
		se = rb_entry(rb, काष्ठा swap_extent, rb_node);
		अगर (offset < se->start_page)
			rb = rb->rb_left;
		अन्यथा अगर (offset >= se->start_page + se->nr_pages)
			rb = rb->rb_right;
		अन्यथा
			वापस se;
	पूर्ण
	/* It *must* be present */
	BUG();
पूर्ण

sector_t swap_page_sector(काष्ठा page *page)
अणु
	काष्ठा swap_info_काष्ठा *sis = page_swap_info(page);
	काष्ठा swap_extent *se;
	sector_t sector;
	pgoff_t offset;

	offset = __page_file_index(page);
	se = offset_to_swap_extent(sis, offset);
	sector = se->start_block + (offset - se->start_page);
	वापस sector << (PAGE_SHIFT - 9);
पूर्ण

/*
 * swap allocation tell device that a cluster of swap can now be discarded,
 * to allow the swap device to optimize its wear-levelling.
 */
अटल व्योम discard_swap_cluster(काष्ठा swap_info_काष्ठा *si,
				 pgoff_t start_page, pgoff_t nr_pages)
अणु
	काष्ठा swap_extent *se = offset_to_swap_extent(si, start_page);

	जबतक (nr_pages) अणु
		pgoff_t offset = start_page - se->start_page;
		sector_t start_block = se->start_block + offset;
		sector_t nr_blocks = se->nr_pages - offset;

		अगर (nr_blocks > nr_pages)
			nr_blocks = nr_pages;
		start_page += nr_blocks;
		nr_pages -= nr_blocks;

		start_block <<= PAGE_SHIFT - 9;
		nr_blocks <<= PAGE_SHIFT - 9;
		अगर (blkdev_issue_discard(si->bdev, start_block,
					nr_blocks, GFP_NOIO, 0))
			अवरोध;

		se = next_se(se);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_THP_SWAP
#घोषणा SWAPखाता_CLUSTER	HPAGE_PMD_NR

#घोषणा swap_entry_size(size)	(size)
#अन्यथा
#घोषणा SWAPखाता_CLUSTER	256

/*
 * Define swap_entry_size() as स्थिरant to let compiler to optimize
 * out some code अगर !CONFIG_THP_SWAP
 */
#घोषणा swap_entry_size(size)	1
#पूर्ण_अगर
#घोषणा LATENCY_LIMIT		256

अटल अंतरभूत व्योम cluster_set_flag(काष्ठा swap_cluster_info *info,
	अचिन्हित पूर्णांक flag)
अणु
	info->flags = flag;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cluster_count(काष्ठा swap_cluster_info *info)
अणु
	वापस info->data;
पूर्ण

अटल अंतरभूत व्योम cluster_set_count(काष्ठा swap_cluster_info *info,
				     अचिन्हित पूर्णांक c)
अणु
	info->data = c;
पूर्ण

अटल अंतरभूत व्योम cluster_set_count_flag(काष्ठा swap_cluster_info *info,
					 अचिन्हित पूर्णांक c, अचिन्हित पूर्णांक f)
अणु
	info->flags = f;
	info->data = c;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cluster_next(काष्ठा swap_cluster_info *info)
अणु
	वापस info->data;
पूर्ण

अटल अंतरभूत व्योम cluster_set_next(काष्ठा swap_cluster_info *info,
				    अचिन्हित पूर्णांक n)
अणु
	info->data = n;
पूर्ण

अटल अंतरभूत व्योम cluster_set_next_flag(काष्ठा swap_cluster_info *info,
					 अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक f)
अणु
	info->flags = f;
	info->data = n;
पूर्ण

अटल अंतरभूत bool cluster_is_मुक्त(काष्ठा swap_cluster_info *info)
अणु
	वापस info->flags & CLUSTER_FLAG_FREE;
पूर्ण

अटल अंतरभूत bool cluster_is_null(काष्ठा swap_cluster_info *info)
अणु
	वापस info->flags & CLUSTER_FLAG_NEXT_शून्य;
पूर्ण

अटल अंतरभूत व्योम cluster_set_null(काष्ठा swap_cluster_info *info)
अणु
	info->flags = CLUSTER_FLAG_NEXT_शून्य;
	info->data = 0;
पूर्ण

अटल अंतरभूत bool cluster_is_huge(काष्ठा swap_cluster_info *info)
अणु
	अगर (IS_ENABLED(CONFIG_THP_SWAP))
		वापस info->flags & CLUSTER_FLAG_HUGE;
	वापस false;
पूर्ण

अटल अंतरभूत व्योम cluster_clear_huge(काष्ठा swap_cluster_info *info)
अणु
	info->flags &= ~CLUSTER_FLAG_HUGE;
पूर्ण

अटल अंतरभूत काष्ठा swap_cluster_info *lock_cluster(काष्ठा swap_info_काष्ठा *si,
						     अचिन्हित दीर्घ offset)
अणु
	काष्ठा swap_cluster_info *ci;

	ci = si->cluster_info;
	अगर (ci) अणु
		ci += offset / SWAPखाता_CLUSTER;
		spin_lock(&ci->lock);
	पूर्ण
	वापस ci;
पूर्ण

अटल अंतरभूत व्योम unlock_cluster(काष्ठा swap_cluster_info *ci)
अणु
	अगर (ci)
		spin_unlock(&ci->lock);
पूर्ण

/*
 * Determine the locking method in use क्रम this device.  Return
 * swap_cluster_info अगर SSD-style cluster-based locking is in place.
 */
अटल अंतरभूत काष्ठा swap_cluster_info *lock_cluster_or_swap_info(
		काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ offset)
अणु
	काष्ठा swap_cluster_info *ci;

	/* Try to use fine-grained SSD-style locking अगर available: */
	ci = lock_cluster(si, offset);
	/* Otherwise, fall back to traditional, coarse locking: */
	अगर (!ci)
		spin_lock(&si->lock);

	वापस ci;
पूर्ण

अटल अंतरभूत व्योम unlock_cluster_or_swap_info(काष्ठा swap_info_काष्ठा *si,
					       काष्ठा swap_cluster_info *ci)
अणु
	अगर (ci)
		unlock_cluster(ci);
	अन्यथा
		spin_unlock(&si->lock);
पूर्ण

अटल अंतरभूत bool cluster_list_empty(काष्ठा swap_cluster_list *list)
अणु
	वापस cluster_is_null(&list->head);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cluster_list_first(काष्ठा swap_cluster_list *list)
अणु
	वापस cluster_next(&list->head);
पूर्ण

अटल व्योम cluster_list_init(काष्ठा swap_cluster_list *list)
अणु
	cluster_set_null(&list->head);
	cluster_set_null(&list->tail);
पूर्ण

अटल व्योम cluster_list_add_tail(काष्ठा swap_cluster_list *list,
				  काष्ठा swap_cluster_info *ci,
				  अचिन्हित पूर्णांक idx)
अणु
	अगर (cluster_list_empty(list)) अणु
		cluster_set_next_flag(&list->head, idx, 0);
		cluster_set_next_flag(&list->tail, idx, 0);
	पूर्ण अन्यथा अणु
		काष्ठा swap_cluster_info *ci_tail;
		अचिन्हित पूर्णांक tail = cluster_next(&list->tail);

		/*
		 * Nested cluster lock, but both cluster locks are
		 * only acquired when we held swap_info_काष्ठा->lock
		 */
		ci_tail = ci + tail;
		spin_lock_nested(&ci_tail->lock, SINGLE_DEPTH_NESTING);
		cluster_set_next(ci_tail, idx);
		spin_unlock(&ci_tail->lock);
		cluster_set_next_flag(&list->tail, idx, 0);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक cluster_list_del_first(काष्ठा swap_cluster_list *list,
					   काष्ठा swap_cluster_info *ci)
अणु
	अचिन्हित पूर्णांक idx;

	idx = cluster_next(&list->head);
	अगर (cluster_next(&list->tail) == idx) अणु
		cluster_set_null(&list->head);
		cluster_set_null(&list->tail);
	पूर्ण अन्यथा
		cluster_set_next_flag(&list->head,
				      cluster_next(&ci[idx]), 0);

	वापस idx;
पूर्ण

/* Add a cluster to discard list and schedule it to करो discard */
अटल व्योम swap_cluster_schedule_discard(काष्ठा swap_info_काष्ठा *si,
		अचिन्हित पूर्णांक idx)
अणु
	/*
	 * If scan_swap_map() can't find a मुक्त cluster, it will check
	 * si->swap_map directly. To make sure the discarding cluster isn't
	 * taken by scan_swap_map(), mark the swap entries bad (occupied). It
	 * will be cleared after discard
	 */
	स_रखो(si->swap_map + idx * SWAPखाता_CLUSTER,
			SWAP_MAP_BAD, SWAPखाता_CLUSTER);

	cluster_list_add_tail(&si->discard_clusters, si->cluster_info, idx);

	schedule_work(&si->discard_work);
पूर्ण

अटल व्योम __मुक्त_cluster(काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ idx)
अणु
	काष्ठा swap_cluster_info *ci = si->cluster_info;

	cluster_set_flag(ci + idx, CLUSTER_FLAG_FREE);
	cluster_list_add_tail(&si->मुक्त_clusters, ci, idx);
पूर्ण

/*
 * Doing discard actually. After a cluster discard is finished, the cluster
 * will be added to मुक्त cluster list. caller should hold si->lock.
*/
अटल व्योम swap_करो_scheduled_discard(काष्ठा swap_info_काष्ठा *si)
अणु
	काष्ठा swap_cluster_info *info, *ci;
	अचिन्हित पूर्णांक idx;

	info = si->cluster_info;

	जबतक (!cluster_list_empty(&si->discard_clusters)) अणु
		idx = cluster_list_del_first(&si->discard_clusters, info);
		spin_unlock(&si->lock);

		discard_swap_cluster(si, idx * SWAPखाता_CLUSTER,
				SWAPखाता_CLUSTER);

		spin_lock(&si->lock);
		ci = lock_cluster(si, idx * SWAPखाता_CLUSTER);
		__मुक्त_cluster(si, idx);
		स_रखो(si->swap_map + idx * SWAPखाता_CLUSTER,
				0, SWAPखाता_CLUSTER);
		unlock_cluster(ci);
	पूर्ण
पूर्ण

अटल व्योम swap_discard_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा swap_info_काष्ठा *si;

	si = container_of(work, काष्ठा swap_info_काष्ठा, discard_work);

	spin_lock(&si->lock);
	swap_करो_scheduled_discard(si);
	spin_unlock(&si->lock);
पूर्ण

अटल व्योम alloc_cluster(काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ idx)
अणु
	काष्ठा swap_cluster_info *ci = si->cluster_info;

	VM_BUG_ON(cluster_list_first(&si->मुक्त_clusters) != idx);
	cluster_list_del_first(&si->मुक्त_clusters, ci);
	cluster_set_count_flag(ci + idx, 0, 0);
पूर्ण

अटल व्योम मुक्त_cluster(काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ idx)
अणु
	काष्ठा swap_cluster_info *ci = si->cluster_info + idx;

	VM_BUG_ON(cluster_count(ci) != 0);
	/*
	 * If the swap is discardable, prepare discard the cluster
	 * instead of मुक्त it immediately. The cluster will be मुक्तd
	 * after discard.
	 */
	अगर ((si->flags & (SWP_WRITEOK | SWP_PAGE_DISCARD)) ==
	    (SWP_WRITEOK | SWP_PAGE_DISCARD)) अणु
		swap_cluster_schedule_discard(si, idx);
		वापस;
	पूर्ण

	__मुक्त_cluster(si, idx);
पूर्ण

/*
 * The cluster corresponding to page_nr will be used. The cluster will be
 * हटाओd from मुक्त cluster list and its usage counter will be increased.
 */
अटल व्योम inc_cluster_info_page(काष्ठा swap_info_काष्ठा *p,
	काष्ठा swap_cluster_info *cluster_info, अचिन्हित दीर्घ page_nr)
अणु
	अचिन्हित दीर्घ idx = page_nr / SWAPखाता_CLUSTER;

	अगर (!cluster_info)
		वापस;
	अगर (cluster_is_मुक्त(&cluster_info[idx]))
		alloc_cluster(p, idx);

	VM_BUG_ON(cluster_count(&cluster_info[idx]) >= SWAPखाता_CLUSTER);
	cluster_set_count(&cluster_info[idx],
		cluster_count(&cluster_info[idx]) + 1);
पूर्ण

/*
 * The cluster corresponding to page_nr decreases one usage. If the usage
 * counter becomes 0, which means no page in the cluster is in using, we can
 * optionally discard the cluster and add it to मुक्त cluster list.
 */
अटल व्योम dec_cluster_info_page(काष्ठा swap_info_काष्ठा *p,
	काष्ठा swap_cluster_info *cluster_info, अचिन्हित दीर्घ page_nr)
अणु
	अचिन्हित दीर्घ idx = page_nr / SWAPखाता_CLUSTER;

	अगर (!cluster_info)
		वापस;

	VM_BUG_ON(cluster_count(&cluster_info[idx]) == 0);
	cluster_set_count(&cluster_info[idx],
		cluster_count(&cluster_info[idx]) - 1);

	अगर (cluster_count(&cluster_info[idx]) == 0)
		मुक्त_cluster(p, idx);
पूर्ण

/*
 * It's possible scan_swap_map() uses a मुक्त cluster in the middle of मुक्त
 * cluster list. Aव्योमing such abuse to aव्योम list corruption.
 */
अटल bool
scan_swap_map_ssd_cluster_conflict(काष्ठा swap_info_काष्ठा *si,
	अचिन्हित दीर्घ offset)
अणु
	काष्ठा percpu_cluster *percpu_cluster;
	bool conflict;

	offset /= SWAPखाता_CLUSTER;
	conflict = !cluster_list_empty(&si->मुक्त_clusters) &&
		offset != cluster_list_first(&si->मुक्त_clusters) &&
		cluster_is_मुक्त(&si->cluster_info[offset]);

	अगर (!conflict)
		वापस false;

	percpu_cluster = this_cpu_ptr(si->percpu_cluster);
	cluster_set_null(&percpu_cluster->index);
	वापस true;
पूर्ण

/*
 * Try to get a swap entry from current cpu's swap entry pool (a cluster). This
 * might involve allocating a new cluster क्रम current CPU too.
 */
अटल bool scan_swap_map_try_ssd_cluster(काष्ठा swap_info_काष्ठा *si,
	अचिन्हित दीर्घ *offset, अचिन्हित दीर्घ *scan_base)
अणु
	काष्ठा percpu_cluster *cluster;
	काष्ठा swap_cluster_info *ci;
	अचिन्हित दीर्घ पंचांगp, max;

new_cluster:
	cluster = this_cpu_ptr(si->percpu_cluster);
	अगर (cluster_is_null(&cluster->index)) अणु
		अगर (!cluster_list_empty(&si->मुक्त_clusters)) अणु
			cluster->index = si->मुक्त_clusters.head;
			cluster->next = cluster_next(&cluster->index) *
					SWAPखाता_CLUSTER;
		पूर्ण अन्यथा अगर (!cluster_list_empty(&si->discard_clusters)) अणु
			/*
			 * we करोn't have मुक्त cluster but have some clusters in
			 * discarding, करो discard now and reclaim them, then
			 * reपढ़ो cluster_next_cpu since we dropped si->lock
			 */
			swap_करो_scheduled_discard(si);
			*scan_base = this_cpu_पढ़ो(*si->cluster_next_cpu);
			*offset = *scan_base;
			जाओ new_cluster;
		पूर्ण अन्यथा
			वापस false;
	पूर्ण

	/*
	 * Other CPUs can use our cluster अगर they can't find a मुक्त cluster,
	 * check अगर there is still मुक्त entry in the cluster
	 */
	पंचांगp = cluster->next;
	max = min_t(अचिन्हित दीर्घ, si->max,
		    (cluster_next(&cluster->index) + 1) * SWAPखाता_CLUSTER);
	अगर (पंचांगp < max) अणु
		ci = lock_cluster(si, पंचांगp);
		जबतक (पंचांगp < max) अणु
			अगर (!si->swap_map[पंचांगp])
				अवरोध;
			पंचांगp++;
		पूर्ण
		unlock_cluster(ci);
	पूर्ण
	अगर (पंचांगp >= max) अणु
		cluster_set_null(&cluster->index);
		जाओ new_cluster;
	पूर्ण
	cluster->next = पंचांगp + 1;
	*offset = पंचांगp;
	*scan_base = पंचांगp;
	वापस true;
पूर्ण

अटल व्योम __del_from_avail_list(काष्ठा swap_info_काष्ठा *p)
अणु
	पूर्णांक nid;

	क्रम_each_node(nid)
		plist_del(&p->avail_lists[nid], &swap_avail_heads[nid]);
पूर्ण

अटल व्योम del_from_avail_list(काष्ठा swap_info_काष्ठा *p)
अणु
	spin_lock(&swap_avail_lock);
	__del_from_avail_list(p);
	spin_unlock(&swap_avail_lock);
पूर्ण

अटल व्योम swap_range_alloc(काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ offset,
			     अचिन्हित पूर्णांक nr_entries)
अणु
	अचिन्हित पूर्णांक end = offset + nr_entries - 1;

	अगर (offset == si->lowest_bit)
		si->lowest_bit += nr_entries;
	अगर (end == si->highest_bit)
		WRITE_ONCE(si->highest_bit, si->highest_bit - nr_entries);
	si->inuse_pages += nr_entries;
	अगर (si->inuse_pages == si->pages) अणु
		si->lowest_bit = si->max;
		si->highest_bit = 0;
		del_from_avail_list(si);
	पूर्ण
पूर्ण

अटल व्योम add_to_avail_list(काष्ठा swap_info_काष्ठा *p)
अणु
	पूर्णांक nid;

	spin_lock(&swap_avail_lock);
	क्रम_each_node(nid) अणु
		WARN_ON(!plist_node_empty(&p->avail_lists[nid]));
		plist_add(&p->avail_lists[nid], &swap_avail_heads[nid]);
	पूर्ण
	spin_unlock(&swap_avail_lock);
पूर्ण

अटल व्योम swap_range_मुक्त(काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ offset,
			    अचिन्हित पूर्णांक nr_entries)
अणु
	अचिन्हित दीर्घ begin = offset;
	अचिन्हित दीर्घ end = offset + nr_entries - 1;
	व्योम (*swap_slot_मुक्त_notअगरy)(काष्ठा block_device *, अचिन्हित दीर्घ);

	अगर (offset < si->lowest_bit)
		si->lowest_bit = offset;
	अगर (end > si->highest_bit) अणु
		bool was_full = !si->highest_bit;

		WRITE_ONCE(si->highest_bit, end);
		अगर (was_full && (si->flags & SWP_WRITEOK))
			add_to_avail_list(si);
	पूर्ण
	atomic_दीर्घ_add(nr_entries, &nr_swap_pages);
	si->inuse_pages -= nr_entries;
	अगर (si->flags & SWP_BLKDEV)
		swap_slot_मुक्त_notअगरy =
			si->bdev->bd_disk->fops->swap_slot_मुक्त_notअगरy;
	अन्यथा
		swap_slot_मुक्त_notअगरy = शून्य;
	जबतक (offset <= end) अणु
		arch_swap_invalidate_page(si->type, offset);
		frontswap_invalidate_page(si->type, offset);
		अगर (swap_slot_मुक्त_notअगरy)
			swap_slot_मुक्त_notअगरy(si->bdev, offset);
		offset++;
	पूर्ण
	clear_shaकरोw_from_swap_cache(si->type, begin, end);
पूर्ण

अटल व्योम set_cluster_next(काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ next)
अणु
	अचिन्हित दीर्घ prev;

	अगर (!(si->flags & SWP_SOLIDSTATE)) अणु
		si->cluster_next = next;
		वापस;
	पूर्ण

	prev = this_cpu_पढ़ो(*si->cluster_next_cpu);
	/*
	 * Cross the swap address space size aligned trunk, choose
	 * another trunk अक्रमomly to aव्योम lock contention on swap
	 * address space अगर possible.
	 */
	अगर ((prev >> SWAP_ADDRESS_SPACE_SHIFT) !=
	    (next >> SWAP_ADDRESS_SPACE_SHIFT)) अणु
		/* No मुक्त swap slots available */
		अगर (si->highest_bit <= si->lowest_bit)
			वापस;
		next = si->lowest_bit +
			pअक्रमom_u32_max(si->highest_bit - si->lowest_bit + 1);
		next = ALIGN_DOWN(next, SWAP_ADDRESS_SPACE_PAGES);
		next = max_t(अचिन्हित पूर्णांक, next, si->lowest_bit);
	पूर्ण
	this_cpu_ग_लिखो(*si->cluster_next_cpu, next);
पूर्ण

अटल पूर्णांक scan_swap_map_slots(काष्ठा swap_info_काष्ठा *si,
			       अचिन्हित अक्षर usage, पूर्णांक nr,
			       swp_entry_t slots[])
अणु
	काष्ठा swap_cluster_info *ci;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ scan_base;
	अचिन्हित दीर्घ last_in_cluster = 0;
	पूर्णांक latency_ration = LATENCY_LIMIT;
	पूर्णांक n_ret = 0;
	bool scanned_many = false;

	/*
	 * We try to cluster swap pages by allocating them sequentially
	 * in swap.  Once we've allocated SWAPखाता_CLUSTER pages this
	 * way, however, we resort to first-मुक्त allocation, starting
	 * a new cluster.  This prevents us from scattering swap pages
	 * all over the entire swap partition, so that we reduce
	 * overall disk seek बार between swap pages.  -- sct
	 * But we करो now try to find an empty cluster.  -Andrea
	 * And we let swap pages go all over an SSD partition.  Hugh
	 */

	si->flags += SWP_SCANNING;
	/*
	 * Use percpu scan base क्रम SSD to reduce lock contention on
	 * cluster and swap cache.  For HDD, sequential access is more
	 * important.
	 */
	अगर (si->flags & SWP_SOLIDSTATE)
		scan_base = this_cpu_पढ़ो(*si->cluster_next_cpu);
	अन्यथा
		scan_base = si->cluster_next;
	offset = scan_base;

	/* SSD algorithm */
	अगर (si->cluster_info) अणु
		अगर (!scan_swap_map_try_ssd_cluster(si, &offset, &scan_base))
			जाओ scan;
	पूर्ण अन्यथा अगर (unlikely(!si->cluster_nr--)) अणु
		अगर (si->pages - si->inuse_pages < SWAPखाता_CLUSTER) अणु
			si->cluster_nr = SWAPखाता_CLUSTER - 1;
			जाओ checks;
		पूर्ण

		spin_unlock(&si->lock);

		/*
		 * If seek is expensive, start searching क्रम new cluster from
		 * start of partition, to minimize the span of allocated swap.
		 * If seek is cheap, that is the SWP_SOLIDSTATE si->cluster_info
		 * हाल, just handled by scan_swap_map_try_ssd_cluster() above.
		 */
		scan_base = offset = si->lowest_bit;
		last_in_cluster = offset + SWAPखाता_CLUSTER - 1;

		/* Locate the first empty (unaligned) cluster */
		क्रम (; last_in_cluster <= si->highest_bit; offset++) अणु
			अगर (si->swap_map[offset])
				last_in_cluster = offset + SWAPखाता_CLUSTER;
			अन्यथा अगर (offset == last_in_cluster) अणु
				spin_lock(&si->lock);
				offset -= SWAPखाता_CLUSTER - 1;
				si->cluster_next = offset;
				si->cluster_nr = SWAPखाता_CLUSTER - 1;
				जाओ checks;
			पूर्ण
			अगर (unlikely(--latency_ration < 0)) अणु
				cond_resched();
				latency_ration = LATENCY_LIMIT;
			पूर्ण
		पूर्ण

		offset = scan_base;
		spin_lock(&si->lock);
		si->cluster_nr = SWAPखाता_CLUSTER - 1;
	पूर्ण

checks:
	अगर (si->cluster_info) अणु
		जबतक (scan_swap_map_ssd_cluster_conflict(si, offset)) अणु
		/* take a अवरोध अगर we alपढ़ोy got some slots */
			अगर (n_ret)
				जाओ करोne;
			अगर (!scan_swap_map_try_ssd_cluster(si, &offset,
							&scan_base))
				जाओ scan;
		पूर्ण
	पूर्ण
	अगर (!(si->flags & SWP_WRITEOK))
		जाओ no_page;
	अगर (!si->highest_bit)
		जाओ no_page;
	अगर (offset > si->highest_bit)
		scan_base = offset = si->lowest_bit;

	ci = lock_cluster(si, offset);
	/* reuse swap entry of cache-only swap अगर not busy. */
	अगर (vm_swap_full() && si->swap_map[offset] == SWAP_HAS_CACHE) अणु
		पूर्णांक swap_was_मुक्तd;
		unlock_cluster(ci);
		spin_unlock(&si->lock);
		swap_was_मुक्तd = __try_to_reclaim_swap(si, offset, TTRS_ANYWAY);
		spin_lock(&si->lock);
		/* entry was मुक्तd successfully, try to use this again */
		अगर (swap_was_मुक्तd)
			जाओ checks;
		जाओ scan; /* check next one */
	पूर्ण

	अगर (si->swap_map[offset]) अणु
		unlock_cluster(ci);
		अगर (!n_ret)
			जाओ scan;
		अन्यथा
			जाओ करोne;
	पूर्ण
	WRITE_ONCE(si->swap_map[offset], usage);
	inc_cluster_info_page(si, si->cluster_info, offset);
	unlock_cluster(ci);

	swap_range_alloc(si, offset, 1);
	slots[n_ret++] = swp_entry(si->type, offset);

	/* got enough slots or reach max slots? */
	अगर ((n_ret == nr) || (offset >= si->highest_bit))
		जाओ करोne;

	/* search क्रम next available slot */

	/* समय to take a अवरोध? */
	अगर (unlikely(--latency_ration < 0)) अणु
		अगर (n_ret)
			जाओ करोne;
		spin_unlock(&si->lock);
		cond_resched();
		spin_lock(&si->lock);
		latency_ration = LATENCY_LIMIT;
	पूर्ण

	/* try to get more slots in cluster */
	अगर (si->cluster_info) अणु
		अगर (scan_swap_map_try_ssd_cluster(si, &offset, &scan_base))
			जाओ checks;
	पूर्ण अन्यथा अगर (si->cluster_nr && !si->swap_map[++offset]) अणु
		/* non-ssd हाल, still more slots in cluster? */
		--si->cluster_nr;
		जाओ checks;
	पूर्ण

	/*
	 * Even अगर there's no मुक्त clusters available (fragmented),
	 * try to scan a little more quickly with lock held unless we
	 * have scanned too many slots alपढ़ोy.
	 */
	अगर (!scanned_many) अणु
		अचिन्हित दीर्घ scan_limit;

		अगर (offset < scan_base)
			scan_limit = scan_base;
		अन्यथा
			scan_limit = si->highest_bit;
		क्रम (; offset <= scan_limit && --latency_ration > 0;
		     offset++) अणु
			अगर (!si->swap_map[offset])
				जाओ checks;
		पूर्ण
	पूर्ण

करोne:
	set_cluster_next(si, offset + 1);
	si->flags -= SWP_SCANNING;
	वापस n_ret;

scan:
	spin_unlock(&si->lock);
	जबतक (++offset <= READ_ONCE(si->highest_bit)) अणु
		अगर (data_race(!si->swap_map[offset])) अणु
			spin_lock(&si->lock);
			जाओ checks;
		पूर्ण
		अगर (vm_swap_full() &&
		    READ_ONCE(si->swap_map[offset]) == SWAP_HAS_CACHE) अणु
			spin_lock(&si->lock);
			जाओ checks;
		पूर्ण
		अगर (unlikely(--latency_ration < 0)) अणु
			cond_resched();
			latency_ration = LATENCY_LIMIT;
			scanned_many = true;
		पूर्ण
	पूर्ण
	offset = si->lowest_bit;
	जबतक (offset < scan_base) अणु
		अगर (data_race(!si->swap_map[offset])) अणु
			spin_lock(&si->lock);
			जाओ checks;
		पूर्ण
		अगर (vm_swap_full() &&
		    READ_ONCE(si->swap_map[offset]) == SWAP_HAS_CACHE) अणु
			spin_lock(&si->lock);
			जाओ checks;
		पूर्ण
		अगर (unlikely(--latency_ration < 0)) अणु
			cond_resched();
			latency_ration = LATENCY_LIMIT;
			scanned_many = true;
		पूर्ण
		offset++;
	पूर्ण
	spin_lock(&si->lock);

no_page:
	si->flags -= SWP_SCANNING;
	वापस n_ret;
पूर्ण

अटल पूर्णांक swap_alloc_cluster(काष्ठा swap_info_काष्ठा *si, swp_entry_t *slot)
अणु
	अचिन्हित दीर्घ idx;
	काष्ठा swap_cluster_info *ci;
	अचिन्हित दीर्घ offset;

	/*
	 * Should not even be attempting cluster allocations when huge
	 * page swap is disabled.  Warn and fail the allocation.
	 */
	अगर (!IS_ENABLED(CONFIG_THP_SWAP)) अणु
		VM_WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	अगर (cluster_list_empty(&si->मुक्त_clusters))
		वापस 0;

	idx = cluster_list_first(&si->मुक्त_clusters);
	offset = idx * SWAPखाता_CLUSTER;
	ci = lock_cluster(si, offset);
	alloc_cluster(si, idx);
	cluster_set_count_flag(ci, SWAPखाता_CLUSTER, CLUSTER_FLAG_HUGE);

	स_रखो(si->swap_map + offset, SWAP_HAS_CACHE, SWAPखाता_CLUSTER);
	unlock_cluster(ci);
	swap_range_alloc(si, offset, SWAPखाता_CLUSTER);
	*slot = swp_entry(si->type, offset);

	वापस 1;
पूर्ण

अटल व्योम swap_मुक्त_cluster(काष्ठा swap_info_काष्ठा *si, अचिन्हित दीर्घ idx)
अणु
	अचिन्हित दीर्घ offset = idx * SWAPखाता_CLUSTER;
	काष्ठा swap_cluster_info *ci;

	ci = lock_cluster(si, offset);
	स_रखो(si->swap_map + offset, 0, SWAPखाता_CLUSTER);
	cluster_set_count_flag(ci, 0, 0);
	मुक्त_cluster(si, idx);
	unlock_cluster(ci);
	swap_range_मुक्त(si, offset, SWAPखाता_CLUSTER);
पूर्ण

अटल अचिन्हित दीर्घ scan_swap_map(काष्ठा swap_info_काष्ठा *si,
				   अचिन्हित अक्षर usage)
अणु
	swp_entry_t entry;
	पूर्णांक n_ret;

	n_ret = scan_swap_map_slots(si, usage, 1, &entry);

	अगर (n_ret)
		वापस swp_offset(entry);
	अन्यथा
		वापस 0;

पूर्ण

पूर्णांक get_swap_pages(पूर्णांक n_goal, swp_entry_t swp_entries[], पूर्णांक entry_size)
अणु
	अचिन्हित दीर्घ size = swap_entry_size(entry_size);
	काष्ठा swap_info_काष्ठा *si, *next;
	दीर्घ avail_pgs;
	पूर्णांक n_ret = 0;
	पूर्णांक node;

	/* Only single cluster request supported */
	WARN_ON_ONCE(n_goal > 1 && size == SWAPखाता_CLUSTER);

	spin_lock(&swap_avail_lock);

	avail_pgs = atomic_दीर्घ_पढ़ो(&nr_swap_pages) / size;
	अगर (avail_pgs <= 0) अणु
		spin_unlock(&swap_avail_lock);
		जाओ noswap;
	पूर्ण

	n_goal = min3((दीर्घ)n_goal, (दीर्घ)SWAP_BATCH, avail_pgs);

	atomic_दीर्घ_sub(n_goal * size, &nr_swap_pages);

start_over:
	node = numa_node_id();
	plist_क्रम_each_entry_safe(si, next, &swap_avail_heads[node], avail_lists[node]) अणु
		/* requeue si to after same-priority siblings */
		plist_requeue(&si->avail_lists[node], &swap_avail_heads[node]);
		spin_unlock(&swap_avail_lock);
		spin_lock(&si->lock);
		अगर (!si->highest_bit || !(si->flags & SWP_WRITEOK)) अणु
			spin_lock(&swap_avail_lock);
			अगर (plist_node_empty(&si->avail_lists[node])) अणु
				spin_unlock(&si->lock);
				जाओ nextsi;
			पूर्ण
			WARN(!si->highest_bit,
			     "swap_info %d in list but !highest_bit\n",
			     si->type);
			WARN(!(si->flags & SWP_WRITEOK),
			     "swap_info %d in list but !SWP_WRITEOK\n",
			     si->type);
			__del_from_avail_list(si);
			spin_unlock(&si->lock);
			जाओ nextsi;
		पूर्ण
		अगर (size == SWAPखाता_CLUSTER) अणु
			अगर (si->flags & SWP_BLKDEV)
				n_ret = swap_alloc_cluster(si, swp_entries);
		पूर्ण अन्यथा
			n_ret = scan_swap_map_slots(si, SWAP_HAS_CACHE,
						    n_goal, swp_entries);
		spin_unlock(&si->lock);
		अगर (n_ret || size == SWAPखाता_CLUSTER)
			जाओ check_out;
		pr_debug("scan_swap_map of si %d failed to find offset\n",
			si->type);

		spin_lock(&swap_avail_lock);
nextsi:
		/*
		 * अगर we got here, it's likely that si was almost full beक्रमe,
		 * and since scan_swap_map() can drop the si->lock, multiple
		 * callers probably all tried to get a page from the same si
		 * and it filled up beक्रमe we could get one; or, the si filled
		 * up between us dropping swap_avail_lock and taking si->lock.
		 * Since we dropped the swap_avail_lock, the swap_avail_head
		 * list may have been modअगरied; so अगर next is still in the
		 * swap_avail_head list then try it, otherwise start over
		 * अगर we have not gotten any slots.
		 */
		अगर (plist_node_empty(&next->avail_lists[node]))
			जाओ start_over;
	पूर्ण

	spin_unlock(&swap_avail_lock);

check_out:
	अगर (n_ret < n_goal)
		atomic_दीर्घ_add((दीर्घ)(n_goal - n_ret) * size,
				&nr_swap_pages);
noswap:
	वापस n_ret;
पूर्ण

/* The only caller of this function is now suspend routine */
swp_entry_t get_swap_page_of_type(पूर्णांक type)
अणु
	काष्ठा swap_info_काष्ठा *si = swap_type_to_swap_info(type);
	pgoff_t offset;

	अगर (!si)
		जाओ fail;

	spin_lock(&si->lock);
	अगर (si->flags & SWP_WRITEOK) अणु
		/* This is called क्रम allocating swap entry, not cache */
		offset = scan_swap_map(si, 1);
		अगर (offset) अणु
			atomic_दीर्घ_dec(&nr_swap_pages);
			spin_unlock(&si->lock);
			वापस swp_entry(type, offset);
		पूर्ण
	पूर्ण
	spin_unlock(&si->lock);
fail:
	वापस (swp_entry_t) अणु0पूर्ण;
पूर्ण

अटल काष्ठा swap_info_काष्ठा *__swap_info_get(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *p;
	अचिन्हित दीर्घ offset;

	अगर (!entry.val)
		जाओ out;
	p = swp_swap_info(entry);
	अगर (!p)
		जाओ bad_nofile;
	अगर (data_race(!(p->flags & SWP_USED)))
		जाओ bad_device;
	offset = swp_offset(entry);
	अगर (offset >= p->max)
		जाओ bad_offset;
	वापस p;

bad_offset:
	pr_err("%s: %s%08lx\n", __func__, Bad_offset, entry.val);
	जाओ out;
bad_device:
	pr_err("%s: %s%08lx\n", __func__, Unused_file, entry.val);
	जाओ out;
bad_nofile:
	pr_err("%s: %s%08lx\n", __func__, Bad_file, entry.val);
out:
	वापस शून्य;
पूर्ण

अटल काष्ठा swap_info_काष्ठा *_swap_info_get(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *p;

	p = __swap_info_get(entry);
	अगर (!p)
		जाओ out;
	अगर (data_race(!p->swap_map[swp_offset(entry)]))
		जाओ bad_मुक्त;
	वापस p;

bad_मुक्त:
	pr_err("%s: %s%08lx\n", __func__, Unused_offset, entry.val);
out:
	वापस शून्य;
पूर्ण

अटल काष्ठा swap_info_काष्ठा *swap_info_get(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *p;

	p = _swap_info_get(entry);
	अगर (p)
		spin_lock(&p->lock);
	वापस p;
पूर्ण

अटल काष्ठा swap_info_काष्ठा *swap_info_get_cont(swp_entry_t entry,
					काष्ठा swap_info_काष्ठा *q)
अणु
	काष्ठा swap_info_काष्ठा *p;

	p = _swap_info_get(entry);

	अगर (p != q) अणु
		अगर (q != शून्य)
			spin_unlock(&q->lock);
		अगर (p != शून्य)
			spin_lock(&p->lock);
	पूर्ण
	वापस p;
पूर्ण

अटल अचिन्हित अक्षर __swap_entry_मुक्त_locked(काष्ठा swap_info_काष्ठा *p,
					      अचिन्हित दीर्घ offset,
					      अचिन्हित अक्षर usage)
अणु
	अचिन्हित अक्षर count;
	अचिन्हित अक्षर has_cache;

	count = p->swap_map[offset];

	has_cache = count & SWAP_HAS_CACHE;
	count &= ~SWAP_HAS_CACHE;

	अगर (usage == SWAP_HAS_CACHE) अणु
		VM_BUG_ON(!has_cache);
		has_cache = 0;
	पूर्ण अन्यथा अगर (count == SWAP_MAP_SHMEM) अणु
		/*
		 * Or we could insist on shmem.c using a special
		 * swap_shmem_मुक्त() and मुक्त_shmem_swap_and_cache()...
		 */
		count = 0;
	पूर्ण अन्यथा अगर ((count & ~COUNT_CONTINUED) <= SWAP_MAP_MAX) अणु
		अगर (count == COUNT_CONTINUED) अणु
			अगर (swap_count_जारीd(p, offset, count))
				count = SWAP_MAP_MAX | COUNT_CONTINUED;
			अन्यथा
				count = SWAP_MAP_MAX;
		पूर्ण अन्यथा
			count--;
	पूर्ण

	usage = count | has_cache;
	अगर (usage)
		WRITE_ONCE(p->swap_map[offset], usage);
	अन्यथा
		WRITE_ONCE(p->swap_map[offset], SWAP_HAS_CACHE);

	वापस usage;
पूर्ण

/*
 * Check whether swap entry is valid in the swap device.  If so,
 * वापस poपूर्णांकer to swap_info_काष्ठा, and keep the swap entry valid
 * via preventing the swap device from being swapoff, until
 * put_swap_device() is called.  Otherwise वापस शून्य.
 *
 * The entirety of the RCU पढ़ो critical section must come beक्रमe the
 * वापस from or after the call to synchronize_rcu() in
 * enable_swap_info() or swapoff().  So अगर "si->flags & SWP_VALID" is
 * true, the si->map, si->cluster_info, etc. must be valid in the
 * critical section.
 *
 * Notice that swapoff or swapoff+swapon can still happen beक्रमe the
 * rcu_पढ़ो_lock() in get_swap_device() or after the rcu_पढ़ो_unlock()
 * in put_swap_device() अगर there isn't any other way to prevent
 * swapoff, such as page lock, page table lock, etc.  The caller must
 * be prepared क्रम that.  For example, the following situation is
 * possible.
 *
 *   CPU1				CPU2
 *   करो_swap_page()
 *     ...				swapoff+swapon
 *     __पढ़ो_swap_cache_async()
 *       swapcache_prepare()
 *         __swap_duplicate()
 *           // check swap_map
 *     // verअगरy PTE not changed
 *
 * In __swap_duplicate(), the swap_map need to be checked beक्रमe
 * changing partly because the specअगरied swap entry may be क्रम another
 * swap device which has been swapoff.  And in करो_swap_page(), after
 * the page is पढ़ो from the swap device, the PTE is verअगरied not
 * changed with the page table locked to check whether the swap device
 * has been swapoff or swapoff+swapon.
 */
काष्ठा swap_info_काष्ठा *get_swap_device(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *si;
	अचिन्हित दीर्घ offset;

	अगर (!entry.val)
		जाओ out;
	si = swp_swap_info(entry);
	अगर (!si)
		जाओ bad_nofile;

	rcu_पढ़ो_lock();
	अगर (data_race(!(si->flags & SWP_VALID)))
		जाओ unlock_out;
	offset = swp_offset(entry);
	अगर (offset >= si->max)
		जाओ unlock_out;

	वापस si;
bad_nofile:
	pr_err("%s: %s%08lx\n", __func__, Bad_file, entry.val);
out:
	वापस शून्य;
unlock_out:
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अटल अचिन्हित अक्षर __swap_entry_मुक्त(काष्ठा swap_info_काष्ठा *p,
				       swp_entry_t entry)
अणु
	काष्ठा swap_cluster_info *ci;
	अचिन्हित दीर्घ offset = swp_offset(entry);
	अचिन्हित अक्षर usage;

	ci = lock_cluster_or_swap_info(p, offset);
	usage = __swap_entry_मुक्त_locked(p, offset, 1);
	unlock_cluster_or_swap_info(p, ci);
	अगर (!usage)
		मुक्त_swap_slot(entry);

	वापस usage;
पूर्ण

अटल व्योम swap_entry_मुक्त(काष्ठा swap_info_काष्ठा *p, swp_entry_t entry)
अणु
	काष्ठा swap_cluster_info *ci;
	अचिन्हित दीर्घ offset = swp_offset(entry);
	अचिन्हित अक्षर count;

	ci = lock_cluster(p, offset);
	count = p->swap_map[offset];
	VM_BUG_ON(count != SWAP_HAS_CACHE);
	p->swap_map[offset] = 0;
	dec_cluster_info_page(p, p->cluster_info, offset);
	unlock_cluster(ci);

	mem_cgroup_unअक्षरge_swap(entry, 1);
	swap_range_मुक्त(p, offset, 1);
पूर्ण

/*
 * Caller has made sure that the swap device corresponding to entry
 * is still around or has not been recycled.
 */
व्योम swap_मुक्त(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *p;

	p = _swap_info_get(entry);
	अगर (p)
		__swap_entry_मुक्त(p, entry);
पूर्ण

/*
 * Called after dropping swapcache to decrease refcnt to swap entries.
 */
व्योम put_swap_page(काष्ठा page *page, swp_entry_t entry)
अणु
	अचिन्हित दीर्घ offset = swp_offset(entry);
	अचिन्हित दीर्घ idx = offset / SWAPखाता_CLUSTER;
	काष्ठा swap_cluster_info *ci;
	काष्ठा swap_info_काष्ठा *si;
	अचिन्हित अक्षर *map;
	अचिन्हित पूर्णांक i, मुक्त_entries = 0;
	अचिन्हित अक्षर val;
	पूर्णांक size = swap_entry_size(thp_nr_pages(page));

	si = _swap_info_get(entry);
	अगर (!si)
		वापस;

	ci = lock_cluster_or_swap_info(si, offset);
	अगर (size == SWAPखाता_CLUSTER) अणु
		VM_BUG_ON(!cluster_is_huge(ci));
		map = si->swap_map + offset;
		क्रम (i = 0; i < SWAPखाता_CLUSTER; i++) अणु
			val = map[i];
			VM_BUG_ON(!(val & SWAP_HAS_CACHE));
			अगर (val == SWAP_HAS_CACHE)
				मुक्त_entries++;
		पूर्ण
		cluster_clear_huge(ci);
		अगर (मुक्त_entries == SWAPखाता_CLUSTER) अणु
			unlock_cluster_or_swap_info(si, ci);
			spin_lock(&si->lock);
			mem_cgroup_unअक्षरge_swap(entry, SWAPखाता_CLUSTER);
			swap_मुक्त_cluster(si, idx);
			spin_unlock(&si->lock);
			वापस;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < size; i++, entry.val++) अणु
		अगर (!__swap_entry_मुक्त_locked(si, offset + i, SWAP_HAS_CACHE)) अणु
			unlock_cluster_or_swap_info(si, ci);
			मुक्त_swap_slot(entry);
			अगर (i == size - 1)
				वापस;
			lock_cluster_or_swap_info(si, offset);
		पूर्ण
	पूर्ण
	unlock_cluster_or_swap_info(si, ci);
पूर्ण

#अगर_घोषित CONFIG_THP_SWAP
पूर्णांक split_swap_cluster(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *si;
	काष्ठा swap_cluster_info *ci;
	अचिन्हित दीर्घ offset = swp_offset(entry);

	si = _swap_info_get(entry);
	अगर (!si)
		वापस -EBUSY;
	ci = lock_cluster(si, offset);
	cluster_clear_huge(ci);
	unlock_cluster(ci);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक swp_entry_cmp(स्थिर व्योम *ent1, स्थिर व्योम *ent2)
अणु
	स्थिर swp_entry_t *e1 = ent1, *e2 = ent2;

	वापस (पूर्णांक)swp_type(*e1) - (पूर्णांक)swp_type(*e2);
पूर्ण

व्योम swapcache_मुक्त_entries(swp_entry_t *entries, पूर्णांक n)
अणु
	काष्ठा swap_info_काष्ठा *p, *prev;
	पूर्णांक i;

	अगर (n <= 0)
		वापस;

	prev = शून्य;
	p = शून्य;

	/*
	 * Sort swap entries by swap device, so each lock is only taken once.
	 * nr_swapfiles isn't असलolutely correct, but the overhead of sort() is
	 * so low that it isn't necessary to optimize further.
	 */
	अगर (nr_swapfiles > 1)
		sort(entries, n, माप(entries[0]), swp_entry_cmp, शून्य);
	क्रम (i = 0; i < n; ++i) अणु
		p = swap_info_get_cont(entries[i], prev);
		अगर (p)
			swap_entry_मुक्त(p, entries[i]);
		prev = p;
	पूर्ण
	अगर (p)
		spin_unlock(&p->lock);
पूर्ण

/*
 * How many references to page are currently swapped out?
 * This करोes not give an exact answer when swap count is जारीd,
 * but करोes include the high COUNT_CONTINUED flag to allow क्रम that.
 */
पूर्णांक page_swapcount(काष्ठा page *page)
अणु
	पूर्णांक count = 0;
	काष्ठा swap_info_काष्ठा *p;
	काष्ठा swap_cluster_info *ci;
	swp_entry_t entry;
	अचिन्हित दीर्घ offset;

	entry.val = page_निजी(page);
	p = _swap_info_get(entry);
	अगर (p) अणु
		offset = swp_offset(entry);
		ci = lock_cluster_or_swap_info(p, offset);
		count = swap_count(p->swap_map[offset]);
		unlock_cluster_or_swap_info(p, ci);
	पूर्ण
	वापस count;
पूर्ण

पूर्णांक __swap_count(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *si;
	pgoff_t offset = swp_offset(entry);
	पूर्णांक count = 0;

	si = get_swap_device(entry);
	अगर (si) अणु
		count = swap_count(si->swap_map[offset]);
		put_swap_device(si);
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक swap_swapcount(काष्ठा swap_info_काष्ठा *si, swp_entry_t entry)
अणु
	पूर्णांक count = 0;
	pgoff_t offset = swp_offset(entry);
	काष्ठा swap_cluster_info *ci;

	ci = lock_cluster_or_swap_info(si, offset);
	count = swap_count(si->swap_map[offset]);
	unlock_cluster_or_swap_info(si, ci);
	वापस count;
पूर्ण

/*
 * How many references to @entry are currently swapped out?
 * This करोes not give an exact answer when swap count is जारीd,
 * but करोes include the high COUNT_CONTINUED flag to allow क्रम that.
 */
पूर्णांक __swp_swapcount(swp_entry_t entry)
अणु
	पूर्णांक count = 0;
	काष्ठा swap_info_काष्ठा *si;

	si = get_swap_device(entry);
	अगर (si) अणु
		count = swap_swapcount(si, entry);
		put_swap_device(si);
	पूर्ण
	वापस count;
पूर्ण

/*
 * How many references to @entry are currently swapped out?
 * This considers COUNT_CONTINUED so it वापसs exact answer.
 */
पूर्णांक swp_swapcount(swp_entry_t entry)
अणु
	पूर्णांक count, पंचांगp_count, n;
	काष्ठा swap_info_काष्ठा *p;
	काष्ठा swap_cluster_info *ci;
	काष्ठा page *page;
	pgoff_t offset;
	अचिन्हित अक्षर *map;

	p = _swap_info_get(entry);
	अगर (!p)
		वापस 0;

	offset = swp_offset(entry);

	ci = lock_cluster_or_swap_info(p, offset);

	count = swap_count(p->swap_map[offset]);
	अगर (!(count & COUNT_CONTINUED))
		जाओ out;

	count &= ~COUNT_CONTINUED;
	n = SWAP_MAP_MAX + 1;

	page = vदो_स्मृति_to_page(p->swap_map + offset);
	offset &= ~PAGE_MASK;
	VM_BUG_ON(page_निजी(page) != SWP_CONTINUED);

	करो अणु
		page = list_next_entry(page, lru);
		map = kmap_atomic(page);
		पंचांगp_count = map[offset];
		kunmap_atomic(map);

		count += (पंचांगp_count & ~COUNT_CONTINUED) * n;
		n *= (SWAP_CONT_MAX + 1);
	पूर्ण जबतक (पंचांगp_count & COUNT_CONTINUED);
out:
	unlock_cluster_or_swap_info(p, ci);
	वापस count;
पूर्ण

अटल bool swap_page_trans_huge_swapped(काष्ठा swap_info_काष्ठा *si,
					 swp_entry_t entry)
अणु
	काष्ठा swap_cluster_info *ci;
	अचिन्हित अक्षर *map = si->swap_map;
	अचिन्हित दीर्घ roffset = swp_offset(entry);
	अचिन्हित दीर्घ offset = round_करोwn(roffset, SWAPखाता_CLUSTER);
	पूर्णांक i;
	bool ret = false;

	ci = lock_cluster_or_swap_info(si, offset);
	अगर (!ci || !cluster_is_huge(ci)) अणु
		अगर (swap_count(map[roffset]))
			ret = true;
		जाओ unlock_out;
	पूर्ण
	क्रम (i = 0; i < SWAPखाता_CLUSTER; i++) अणु
		अगर (swap_count(map[offset + i])) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
unlock_out:
	unlock_cluster_or_swap_info(si, ci);
	वापस ret;
पूर्ण

अटल bool page_swapped(काष्ठा page *page)
अणु
	swp_entry_t entry;
	काष्ठा swap_info_काष्ठा *si;

	अगर (!IS_ENABLED(CONFIG_THP_SWAP) || likely(!PageTransCompound(page)))
		वापस page_swapcount(page) != 0;

	page = compound_head(page);
	entry.val = page_निजी(page);
	si = _swap_info_get(entry);
	अगर (si)
		वापस swap_page_trans_huge_swapped(si, entry);
	वापस false;
पूर्ण

अटल पूर्णांक page_trans_huge_map_swapcount(काष्ठा page *page, पूर्णांक *total_mapcount,
					 पूर्णांक *total_swapcount)
अणु
	पूर्णांक i, map_swapcount, _total_mapcount, _total_swapcount;
	अचिन्हित दीर्घ offset = 0;
	काष्ठा swap_info_काष्ठा *si;
	काष्ठा swap_cluster_info *ci = शून्य;
	अचिन्हित अक्षर *map = शून्य;
	पूर्णांक mapcount, swapcount = 0;

	/* hugetlbfs shouldn't call it */
	VM_BUG_ON_PAGE(PageHuge(page), page);

	अगर (!IS_ENABLED(CONFIG_THP_SWAP) || likely(!PageTransCompound(page))) अणु
		mapcount = page_trans_huge_mapcount(page, total_mapcount);
		अगर (PageSwapCache(page))
			swapcount = page_swapcount(page);
		अगर (total_swapcount)
			*total_swapcount = swapcount;
		वापस mapcount + swapcount;
	पूर्ण

	page = compound_head(page);

	_total_mapcount = _total_swapcount = map_swapcount = 0;
	अगर (PageSwapCache(page)) अणु
		swp_entry_t entry;

		entry.val = page_निजी(page);
		si = _swap_info_get(entry);
		अगर (si) अणु
			map = si->swap_map;
			offset = swp_offset(entry);
		पूर्ण
	पूर्ण
	अगर (map)
		ci = lock_cluster(si, offset);
	क्रम (i = 0; i < HPAGE_PMD_NR; i++) अणु
		mapcount = atomic_पढ़ो(&page[i]._mapcount) + 1;
		_total_mapcount += mapcount;
		अगर (map) अणु
			swapcount = swap_count(map[offset + i]);
			_total_swapcount += swapcount;
		पूर्ण
		map_swapcount = max(map_swapcount, mapcount + swapcount);
	पूर्ण
	unlock_cluster(ci);
	अगर (PageDoubleMap(page)) अणु
		map_swapcount -= 1;
		_total_mapcount -= HPAGE_PMD_NR;
	पूर्ण
	mapcount = compound_mapcount(page);
	map_swapcount += mapcount;
	_total_mapcount += mapcount;
	अगर (total_mapcount)
		*total_mapcount = _total_mapcount;
	अगर (total_swapcount)
		*total_swapcount = _total_swapcount;

	वापस map_swapcount;
पूर्ण

/*
 * We can ग_लिखो to an anon page without COW अगर there are no other references
 * to it.  And as a side-effect, मुक्त up its swap: because the old content
 * on disk will never be पढ़ो, and seeking back there to ग_लिखो new content
 * later would only waste समय away from clustering.
 *
 * NOTE: total_map_swapcount should not be relied upon by the caller अगर
 * reuse_swap_page() वापसs false, but it may be always overwritten
 * (see the other implementation क्रम CONFIG_SWAP=n).
 */
bool reuse_swap_page(काष्ठा page *page, पूर्णांक *total_map_swapcount)
अणु
	पूर्णांक count, total_mapcount, total_swapcount;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	अगर (unlikely(PageKsm(page)))
		वापस false;
	count = page_trans_huge_map_swapcount(page, &total_mapcount,
					      &total_swapcount);
	अगर (total_map_swapcount)
		*total_map_swapcount = total_mapcount + total_swapcount;
	अगर (count == 1 && PageSwapCache(page) &&
	    (likely(!PageTransCompound(page)) ||
	     /* The reमुख्यing swap count will be मुक्तd soon */
	     total_swapcount == page_swapcount(page))) अणु
		अगर (!PageWriteback(page)) अणु
			page = compound_head(page);
			delete_from_swap_cache(page);
			SetPageDirty(page);
		पूर्ण अन्यथा अणु
			swp_entry_t entry;
			काष्ठा swap_info_काष्ठा *p;

			entry.val = page_निजी(page);
			p = swap_info_get(entry);
			अगर (p->flags & SWP_STABLE_WRITES) अणु
				spin_unlock(&p->lock);
				वापस false;
			पूर्ण
			spin_unlock(&p->lock);
		पूर्ण
	पूर्ण

	वापस count <= 1;
पूर्ण

/*
 * If swap is getting full, or अगर there are no more mappings of this page,
 * then try_to_मुक्त_swap is called to मुक्त its swap space.
 */
पूर्णांक try_to_मुक्त_swap(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageLocked(page), page);

	अगर (!PageSwapCache(page))
		वापस 0;
	अगर (PageWriteback(page))
		वापस 0;
	अगर (page_swapped(page))
		वापस 0;

	/*
	 * Once hibernation has begun to create its image of memory,
	 * there's a danger that one of the calls to try_to_मुक्त_swap()
	 * - most probably a call from __try_to_reclaim_swap() जबतक
	 * hibernation is allocating its own swap pages क्रम the image,
	 * but conceivably even a call from memory reclaim - will मुक्त
	 * the swap from a page which has alपढ़ोy been recorded in the
	 * image as a clean swapcache page, and then reuse its swap क्रम
	 * another page of the image.  On waking from hibernation, the
	 * original page might be मुक्तd under memory pressure, then
	 * later पढ़ो back in from swap, now with the wrong data.
	 *
	 * Hibernation suspends storage जबतक it is writing the image
	 * to disk so check that here.
	 */
	अगर (pm_suspended_storage())
		वापस 0;

	page = compound_head(page);
	delete_from_swap_cache(page);
	SetPageDirty(page);
	वापस 1;
पूर्ण

/*
 * Free the swap entry like above, but also try to
 * मुक्त the page cache entry अगर it is the last user.
 */
पूर्णांक मुक्त_swap_and_cache(swp_entry_t entry)
अणु
	काष्ठा swap_info_काष्ठा *p;
	अचिन्हित अक्षर count;

	अगर (non_swap_entry(entry))
		वापस 1;

	p = _swap_info_get(entry);
	अगर (p) अणु
		count = __swap_entry_मुक्त(p, entry);
		अगर (count == SWAP_HAS_CACHE &&
		    !swap_page_trans_huge_swapped(p, entry))
			__try_to_reclaim_swap(p, swp_offset(entry),
					      TTRS_UNMAPPED | TTRS_FULL);
	पूर्ण
	वापस p != शून्य;
पूर्ण

#अगर_घोषित CONFIG_HIBERNATION
/*
 * Find the swap type that corresponds to given device (अगर any).
 *
 * @offset - number of the PAGE_SIZE-sized block of the device, starting
 * from 0, in which the swap header is expected to be located.
 *
 * This is needed क्रम the suspend to disk (aka swsusp).
 */
पूर्णांक swap_type_of(dev_t device, sector_t offset)
अणु
	पूर्णांक type;

	अगर (!device)
		वापस -1;

	spin_lock(&swap_lock);
	क्रम (type = 0; type < nr_swapfiles; type++) अणु
		काष्ठा swap_info_काष्ठा *sis = swap_info[type];

		अगर (!(sis->flags & SWP_WRITEOK))
			जारी;

		अगर (device == sis->bdev->bd_dev) अणु
			काष्ठा swap_extent *se = first_se(sis);

			अगर (se->start_block == offset) अणु
				spin_unlock(&swap_lock);
				वापस type;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&swap_lock);
	वापस -ENODEV;
पूर्ण

पूर्णांक find_first_swap(dev_t *device)
अणु
	पूर्णांक type;

	spin_lock(&swap_lock);
	क्रम (type = 0; type < nr_swapfiles; type++) अणु
		काष्ठा swap_info_काष्ठा *sis = swap_info[type];

		अगर (!(sis->flags & SWP_WRITEOK))
			जारी;
		*device = sis->bdev->bd_dev;
		spin_unlock(&swap_lock);
		वापस type;
	पूर्ण
	spin_unlock(&swap_lock);
	वापस -ENODEV;
पूर्ण

/*
 * Get the (PAGE_SIZE) block corresponding to given offset on the swapdev
 * corresponding to given index in swap_info (swap type).
 */
sector_t swapdev_block(पूर्णांक type, pgoff_t offset)
अणु
	काष्ठा swap_info_काष्ठा *si = swap_type_to_swap_info(type);
	काष्ठा swap_extent *se;

	अगर (!si || !(si->flags & SWP_WRITEOK))
		वापस 0;
	se = offset_to_swap_extent(si, offset);
	वापस se->start_block + (offset - se->start_page);
पूर्ण

/*
 * Return either the total number of swap pages of given type, or the number
 * of मुक्त pages of that type (depending on @मुक्त)
 *
 * This is needed क्रम software suspend
 */
अचिन्हित पूर्णांक count_swap_pages(पूर्णांक type, पूर्णांक मुक्त)
अणु
	अचिन्हित पूर्णांक n = 0;

	spin_lock(&swap_lock);
	अगर ((अचिन्हित पूर्णांक)type < nr_swapfiles) अणु
		काष्ठा swap_info_काष्ठा *sis = swap_info[type];

		spin_lock(&sis->lock);
		अगर (sis->flags & SWP_WRITEOK) अणु
			n = sis->pages;
			अगर (मुक्त)
				n -= sis->inuse_pages;
		पूर्ण
		spin_unlock(&sis->lock);
	पूर्ण
	spin_unlock(&swap_lock);
	वापस n;
पूर्ण
#पूर्ण_अगर /* CONFIG_HIBERNATION */

अटल अंतरभूत पूर्णांक pte_same_as_swp(pte_t pte, pte_t swp_pte)
अणु
	वापस pte_same(pte_swp_clear_flags(pte), swp_pte);
पूर्ण

/*
 * No need to decide whether this PTE shares the swap entry with others,
 * just let करो_wp_page work it out अगर a ग_लिखो is requested later - to
 * क्रमce COW, vm_page_prot omits ग_लिखो permission from any निजी vma.
 */
अटल पूर्णांक unuse_pte(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		अचिन्हित दीर्घ addr, swp_entry_t entry, काष्ठा page *page)
अणु
	काष्ठा page *swapcache;
	spinlock_t *ptl;
	pte_t *pte;
	पूर्णांक ret = 1;

	swapcache = page;
	page = ksm_might_need_to_copy(page, vma, addr);
	अगर (unlikely(!page))
		वापस -ENOMEM;

	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	अगर (unlikely(!pte_same_as_swp(*pte, swp_entry_to_pte(entry)))) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	dec_mm_counter(vma->vm_mm, MM_SWAPENTS);
	inc_mm_counter(vma->vm_mm, MM_ANONPAGES);
	get_page(page);
	set_pte_at(vma->vm_mm, addr, pte,
		   pte_mkold(mk_pte(page, vma->vm_page_prot)));
	अगर (page == swapcache) अणु
		page_add_anon_rmap(page, vma, addr, false);
	पूर्ण अन्यथा अणु /* ksm created a completely new copy */
		page_add_new_anon_rmap(page, vma, addr, false);
		lru_cache_add_inactive_or_unevictable(page, vma);
	पूर्ण
	swap_मुक्त(entry);
out:
	pte_unmap_unlock(pte, ptl);
	अगर (page != swapcache) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक unuse_pte_range(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			अचिन्हित पूर्णांक type, bool frontswap,
			अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	काष्ठा page *page;
	swp_entry_t entry;
	pte_t *pte;
	काष्ठा swap_info_काष्ठा *si;
	अचिन्हित दीर्घ offset;
	पूर्णांक ret = 0;
	अस्थिर अचिन्हित अक्षर *swap_map;

	si = swap_info[type];
	pte = pte_offset_map(pmd, addr);
	करो अणु
		अगर (!is_swap_pte(*pte))
			जारी;

		entry = pte_to_swp_entry(*pte);
		अगर (swp_type(entry) != type)
			जारी;

		offset = swp_offset(entry);
		अगर (frontswap && !frontswap_test(si, offset))
			जारी;

		pte_unmap(pte);
		swap_map = &si->swap_map[offset];
		page = lookup_swap_cache(entry, vma, addr);
		अगर (!page) अणु
			काष्ठा vm_fault vmf = अणु
				.vma = vma,
				.address = addr,
				.pmd = pmd,
			पूर्ण;

			page = swapin_पढ़ोahead(entry, GFP_HIGHUSER_MOVABLE,
						&vmf);
		पूर्ण
		अगर (!page) अणु
			अगर (*swap_map == 0 || *swap_map == SWAP_MAP_BAD)
				जाओ try_next;
			वापस -ENOMEM;
		पूर्ण

		lock_page(page);
		रुको_on_page_ग_लिखोback(page);
		ret = unuse_pte(vma, pmd, addr, entry, page);
		अगर (ret < 0) अणु
			unlock_page(page);
			put_page(page);
			जाओ out;
		पूर्ण

		try_to_मुक्त_swap(page);
		unlock_page(page);
		put_page(page);

		अगर (*fs_pages_to_unuse && !--(*fs_pages_to_unuse)) अणु
			ret = FRONTSWAP_PAGES_UNUSED;
			जाओ out;
		पूर्ण
try_next:
		pte = pte_offset_map(pmd, addr);
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
	pte_unmap(pte - 1);

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक unuse_pmd_range(काष्ठा vm_area_काष्ठा *vma, pud_t *pud,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				अचिन्हित पूर्णांक type, bool frontswap,
				अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	पूर्णांक ret;

	pmd = pmd_offset(pud, addr);
	करो अणु
		cond_resched();
		next = pmd_addr_end(addr, end);
		अगर (pmd_none_or_trans_huge_or_clear_bad(pmd))
			जारी;
		ret = unuse_pte_range(vma, pmd, addr, next, type,
				      frontswap, fs_pages_to_unuse);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (pmd++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unuse_pud_range(काष्ठा vm_area_काष्ठा *vma, p4d_t *p4d,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				अचिन्हित पूर्णांक type, bool frontswap,
				अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	पूर्णांक ret;

	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_none_or_clear_bad(pud))
			जारी;
		ret = unuse_pmd_range(vma, pud, addr, next, type,
				      frontswap, fs_pages_to_unuse);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (pud++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unuse_p4d_range(काष्ठा vm_area_काष्ठा *vma, pgd_t *pgd,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				अचिन्हित पूर्णांक type, bool frontswap,
				अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	पूर्णांक ret;

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none_or_clear_bad(p4d))
			जारी;
		ret = unuse_pud_range(vma, p4d, addr, next, type,
				      frontswap, fs_pages_to_unuse);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (p4d++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक unuse_vma(काष्ठा vm_area_काष्ठा *vma, अचिन्हित पूर्णांक type,
		     bool frontswap, अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ addr, end, next;
	पूर्णांक ret;

	addr = vma->vm_start;
	end = vma->vm_end;

	pgd = pgd_offset(vma->vm_mm, addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none_or_clear_bad(pgd))
			जारी;
		ret = unuse_p4d_range(vma, pgd, addr, next, type,
				      frontswap, fs_pages_to_unuse);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (pgd++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल पूर्णांक unuse_mm(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक type,
		    bool frontswap, अचिन्हित दीर्घ *fs_pages_to_unuse)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret = 0;

	mmap_पढ़ो_lock(mm);
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (vma->anon_vma) अणु
			ret = unuse_vma(vma, type, frontswap,
					fs_pages_to_unuse);
			अगर (ret)
				अवरोध;
		पूर्ण
		cond_resched();
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	वापस ret;
पूर्ण

/*
 * Scan swap_map (or frontswap_map अगर frontswap parameter is true)
 * from current position to next entry still in use. Return 0
 * अगर there are no inuse entries after prev till end of the map.
 */
अटल अचिन्हित पूर्णांक find_next_to_unuse(काष्ठा swap_info_काष्ठा *si,
					अचिन्हित पूर्णांक prev, bool frontswap)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित अक्षर count;

	/*
	 * No need क्रम swap_lock here: we're just looking
	 * क्रम whether an entry is in use, not modअगरying it; false
	 * hits are okay, and sys_swapoff() has alपढ़ोy prevented new
	 * allocations from this area (जबतक holding swap_lock).
	 */
	क्रम (i = prev + 1; i < si->max; i++) अणु
		count = READ_ONCE(si->swap_map[i]);
		अगर (count && swap_count(count) != SWAP_MAP_BAD)
			अगर (!frontswap || frontswap_test(si, i))
				अवरोध;
		अगर ((i % LATENCY_LIMIT) == 0)
			cond_resched();
	पूर्ण

	अगर (i == si->max)
		i = 0;

	वापस i;
पूर्ण

/*
 * If the boolean frontswap is true, only unuse pages_to_unuse pages;
 * pages_to_unuse==0 means all pages; ignored अगर frontswap is false
 */
पूर्णांक try_to_unuse(अचिन्हित पूर्णांक type, bool frontswap,
		 अचिन्हित दीर्घ pages_to_unuse)
अणु
	काष्ठा mm_काष्ठा *prev_mm;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा list_head *p;
	पूर्णांक retval = 0;
	काष्ठा swap_info_काष्ठा *si = swap_info[type];
	काष्ठा page *page;
	swp_entry_t entry;
	अचिन्हित पूर्णांक i;

	अगर (!READ_ONCE(si->inuse_pages))
		वापस 0;

	अगर (!frontswap)
		pages_to_unuse = 0;

retry:
	retval = shmem_unuse(type, frontswap, &pages_to_unuse);
	अगर (retval)
		जाओ out;

	prev_mm = &init_mm;
	mmget(prev_mm);

	spin_lock(&mmlist_lock);
	p = &init_mm.mmlist;
	जबतक (READ_ONCE(si->inuse_pages) &&
	       !संकेत_pending(current) &&
	       (p = p->next) != &init_mm.mmlist) अणु

		mm = list_entry(p, काष्ठा mm_काष्ठा, mmlist);
		अगर (!mmget_not_zero(mm))
			जारी;
		spin_unlock(&mmlist_lock);
		mmput(prev_mm);
		prev_mm = mm;
		retval = unuse_mm(mm, type, frontswap, &pages_to_unuse);

		अगर (retval) अणु
			mmput(prev_mm);
			जाओ out;
		पूर्ण

		/*
		 * Make sure that we aren't completely समाप्तing
		 * पूर्णांकeractive perक्रमmance.
		 */
		cond_resched();
		spin_lock(&mmlist_lock);
	पूर्ण
	spin_unlock(&mmlist_lock);

	mmput(prev_mm);

	i = 0;
	जबतक (READ_ONCE(si->inuse_pages) &&
	       !संकेत_pending(current) &&
	       (i = find_next_to_unuse(si, i, frontswap)) != 0) अणु

		entry = swp_entry(type, i);
		page = find_get_page(swap_address_space(entry), i);
		अगर (!page)
			जारी;

		/*
		 * It is conceivable that a racing task हटाओd this page from
		 * swap cache just beक्रमe we acquired the page lock. The page
		 * might even be back in swap cache on another swap area. But
		 * that is okay, try_to_मुक्त_swap() only हटाओs stale pages.
		 */
		lock_page(page);
		रुको_on_page_ग_लिखोback(page);
		try_to_मुक्त_swap(page);
		unlock_page(page);
		put_page(page);

		/*
		 * For frontswap, we just need to unuse pages_to_unuse, अगर
		 * it was specअगरied. Need not check frontswap again here as
		 * we alपढ़ोy zeroed out pages_to_unuse अगर not frontswap.
		 */
		अगर (pages_to_unuse && --pages_to_unuse == 0)
			जाओ out;
	पूर्ण

	/*
	 * Lets check again to see अगर there are still swap entries in the map.
	 * If yes, we would need to करो retry the unuse logic again.
	 * Under global memory pressure, swap entries can be reinserted back
	 * पूर्णांकo process space after the mmlist loop above passes over them.
	 *
	 * Limit the number of retries? No: when mmget_not_zero() above fails,
	 * that mm is likely to be मुक्तing swap from निकास_mmap(), which proceeds
	 * at its own independent pace; and even shmem_ग_लिखोpage() could have
	 * been preempted after get_swap_page(), temporarily hiding that swap.
	 * It's easy and robust (though cpu-पूर्णांकensive) just to keep retrying.
	 */
	अगर (READ_ONCE(si->inuse_pages)) अणु
		अगर (!संकेत_pending(current))
			जाओ retry;
		retval = -EINTR;
	पूर्ण
out:
	वापस (retval == FRONTSWAP_PAGES_UNUSED) ? 0 : retval;
पूर्ण

/*
 * After a successful try_to_unuse, अगर no swap is now in use, we know
 * we can empty the mmlist.  swap_lock must be held on entry and निकास.
 * Note that mmlist_lock nests inside swap_lock, and an mm must be
 * added to the mmlist just after page_duplicate - beक्रमe would be racy.
 */
अटल व्योम drain_mmlist(व्योम)
अणु
	काष्ठा list_head *p, *next;
	अचिन्हित पूर्णांक type;

	क्रम (type = 0; type < nr_swapfiles; type++)
		अगर (swap_info[type]->inuse_pages)
			वापस;
	spin_lock(&mmlist_lock);
	list_क्रम_each_safe(p, next, &init_mm.mmlist)
		list_del_init(p);
	spin_unlock(&mmlist_lock);
पूर्ण

/*
 * Free all of a swapdev's extent inक्रमmation
 */
अटल व्योम destroy_swap_extents(काष्ठा swap_info_काष्ठा *sis)
अणु
	जबतक (!RB_EMPTY_ROOT(&sis->swap_extent_root)) अणु
		काष्ठा rb_node *rb = sis->swap_extent_root.rb_node;
		काष्ठा swap_extent *se = rb_entry(rb, काष्ठा swap_extent, rb_node);

		rb_erase(rb, &sis->swap_extent_root);
		kमुक्त(se);
	पूर्ण

	अगर (sis->flags & SWP_ACTIVATED) अणु
		काष्ठा file *swap_file = sis->swap_file;
		काष्ठा address_space *mapping = swap_file->f_mapping;

		sis->flags &= ~SWP_ACTIVATED;
		अगर (mapping->a_ops->swap_deactivate)
			mapping->a_ops->swap_deactivate(swap_file);
	पूर्ण
पूर्ण

/*
 * Add a block range (and the corresponding page range) पूर्णांकo this swapdev's
 * extent tree.
 *
 * This function rather assumes that it is called in ascending page order.
 */
पूर्णांक
add_swap_extent(काष्ठा swap_info_काष्ठा *sis, अचिन्हित दीर्घ start_page,
		अचिन्हित दीर्घ nr_pages, sector_t start_block)
अणु
	काष्ठा rb_node **link = &sis->swap_extent_root.rb_node, *parent = शून्य;
	काष्ठा swap_extent *se;
	काष्ठा swap_extent *new_se;

	/*
	 * place the new node at the right most since the
	 * function is called in ascending page order.
	 */
	जबतक (*link) अणु
		parent = *link;
		link = &parent->rb_right;
	पूर्ण

	अगर (parent) अणु
		se = rb_entry(parent, काष्ठा swap_extent, rb_node);
		BUG_ON(se->start_page + se->nr_pages != start_page);
		अगर (se->start_block + se->nr_pages == start_block) अणु
			/* Merge it */
			se->nr_pages += nr_pages;
			वापस 0;
		पूर्ण
	पूर्ण

	/* No merge, insert a new extent. */
	new_se = kदो_स्मृति(माप(*se), GFP_KERNEL);
	अगर (new_se == शून्य)
		वापस -ENOMEM;
	new_se->start_page = start_page;
	new_se->nr_pages = nr_pages;
	new_se->start_block = start_block;

	rb_link_node(&new_se->rb_node, parent, link);
	rb_insert_color(&new_se->rb_node, &sis->swap_extent_root);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(add_swap_extent);

/*
 * A `swap extent' is a simple thing which maps a contiguous range of pages
 * onto a contiguous range of disk blocks.  An ordered list of swap extents
 * is built at swapon समय and is then used at swap_ग_लिखोpage/swap_पढ़ोpage
 * समय क्रम locating where on disk a page beदीर्घs.
 *
 * If the swapfile is an S_ISBLK block device, a single extent is installed.
 * This is करोne so that the मुख्य operating code can treat S_ISBLK and S_ISREG
 * swap files identically.
 *
 * Whether the swapdev is an S_ISREG file or an S_ISBLK blockdev, the swap
 * extent list operates in PAGE_SIZE disk blocks.  Both S_ISREG and S_ISBLK
 * swapfiles are handled *identically* after swapon समय.
 *
 * For S_ISREG swapfiles, setup_swap_extents() will walk all the file's blocks
 * and will parse them पूर्णांकo an ordered extent list, in PAGE_SIZE chunks.  If
 * some stray blocks are found which करो not fall within the PAGE_SIZE alignment
 * requirements, they are simply tossed out - we will never use those blocks
 * क्रम swapping.
 *
 * For all swap devices we set S_SWAPखाता across the lअगरe of the swapon.  This
 * prevents users from writing to the swap device, which will corrupt memory.
 *
 * The amount of disk space which a single swap extent represents varies.
 * Typically it is in the 1-4 megabyte range.  So we can have hundreds of
 * extents in the list.  To aव्योम much list walking, we cache the previous
 * search location in `curr_swap_extent', and start new searches from there.
 * This is extremely effective.  The average number of iterations in
 * map_swap_page() has been measured at about 0.3 per page.  - akpm.
 */
अटल पूर्णांक setup_swap_extents(काष्ठा swap_info_काष्ठा *sis, sector_t *span)
अणु
	काष्ठा file *swap_file = sis->swap_file;
	काष्ठा address_space *mapping = swap_file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	पूर्णांक ret;

	अगर (S_ISBLK(inode->i_mode)) अणु
		ret = add_swap_extent(sis, 0, sis->max, 0);
		*span = sis->pages;
		वापस ret;
	पूर्ण

	अगर (mapping->a_ops->swap_activate) अणु
		ret = mapping->a_ops->swap_activate(sis, swap_file, span);
		अगर (ret >= 0)
			sis->flags |= SWP_ACTIVATED;
		अगर (!ret) अणु
			sis->flags |= SWP_FS_OPS;
			ret = add_swap_extent(sis, 0, sis->max, 0);
			*span = sis->pages;
		पूर्ण
		वापस ret;
	पूर्ण

	वापस generic_swapfile_activate(sis, swap_file, span);
पूर्ण

अटल पूर्णांक swap_node(काष्ठा swap_info_काष्ठा *p)
अणु
	काष्ठा block_device *bdev;

	अगर (p->bdev)
		bdev = p->bdev;
	अन्यथा
		bdev = p->swap_file->f_inode->i_sb->s_bdev;

	वापस bdev ? bdev->bd_disk->node_id : NUMA_NO_NODE;
पूर्ण

अटल व्योम setup_swap_info(काष्ठा swap_info_काष्ठा *p, पूर्णांक prio,
			    अचिन्हित अक्षर *swap_map,
			    काष्ठा swap_cluster_info *cluster_info)
अणु
	पूर्णांक i;

	अगर (prio >= 0)
		p->prio = prio;
	अन्यथा
		p->prio = --least_priority;
	/*
	 * the plist prio is negated because plist ordering is
	 * low-to-high, जबतक swap ordering is high-to-low
	 */
	p->list.prio = -p->prio;
	क्रम_each_node(i) अणु
		अगर (p->prio >= 0)
			p->avail_lists[i].prio = -p->prio;
		अन्यथा अणु
			अगर (swap_node(p) == i)
				p->avail_lists[i].prio = 1;
			अन्यथा
				p->avail_lists[i].prio = -p->prio;
		पूर्ण
	पूर्ण
	p->swap_map = swap_map;
	p->cluster_info = cluster_info;
पूर्ण

अटल व्योम _enable_swap_info(काष्ठा swap_info_काष्ठा *p)
अणु
	p->flags |= SWP_WRITEOK | SWP_VALID;
	atomic_दीर्घ_add(p->pages, &nr_swap_pages);
	total_swap_pages += p->pages;

	निश्चित_spin_locked(&swap_lock);
	/*
	 * both lists are plists, and thus priority ordered.
	 * swap_active_head needs to be priority ordered क्रम swapoff(),
	 * which on removal of any swap_info_काष्ठा with an स्वतः-asचिन्हित
	 * (i.e. negative) priority increments the स्वतः-asचिन्हित priority
	 * of any lower-priority swap_info_काष्ठाs.
	 * swap_avail_head needs to be priority ordered क्रम get_swap_page(),
	 * which allocates swap pages from the highest available priority
	 * swap_info_काष्ठा.
	 */
	plist_add(&p->list, &swap_active_head);
	add_to_avail_list(p);
पूर्ण

अटल व्योम enable_swap_info(काष्ठा swap_info_काष्ठा *p, पूर्णांक prio,
				अचिन्हित अक्षर *swap_map,
				काष्ठा swap_cluster_info *cluster_info,
				अचिन्हित दीर्घ *frontswap_map)
अणु
	frontswap_init(p->type, frontswap_map);
	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	setup_swap_info(p, prio, swap_map, cluster_info);
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
	/*
	 * Guarantee swap_map, cluster_info, etc. fields are valid
	 * between get/put_swap_device() अगर SWP_VALID bit is set
	 */
	synchronize_rcu();
	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	_enable_swap_info(p);
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
पूर्ण

अटल व्योम reinsert_swap_info(काष्ठा swap_info_काष्ठा *p)
अणु
	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	setup_swap_info(p, p->prio, p->swap_map, p->cluster_info);
	_enable_swap_info(p);
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
पूर्ण

bool has_usable_swap(व्योम)
अणु
	bool ret = true;

	spin_lock(&swap_lock);
	अगर (plist_head_empty(&swap_active_head))
		ret = false;
	spin_unlock(&swap_lock);
	वापस ret;
पूर्ण

SYSCALL_DEFINE1(swapoff, स्थिर अक्षर __user *, specialfile)
अणु
	काष्ठा swap_info_काष्ठा *p = शून्य;
	अचिन्हित अक्षर *swap_map;
	काष्ठा swap_cluster_info *cluster_info;
	अचिन्हित दीर्घ *frontswap_map;
	काष्ठा file *swap_file, *victim;
	काष्ठा address_space *mapping;
	काष्ठा inode *inode;
	काष्ठा filename *pathname;
	पूर्णांक err, found = 0;
	अचिन्हित पूर्णांक old_block_size;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	BUG_ON(!current->mm);

	pathname = getname(specialfile);
	अगर (IS_ERR(pathname))
		वापस PTR_ERR(pathname);

	victim = file_खोलो_name(pathname, O_RDWR|O_LARGEखाता, 0);
	err = PTR_ERR(victim);
	अगर (IS_ERR(victim))
		जाओ out;

	mapping = victim->f_mapping;
	spin_lock(&swap_lock);
	plist_क्रम_each_entry(p, &swap_active_head, list) अणु
		अगर (p->flags & SWP_WRITEOK) अणु
			अगर (p->swap_file->f_mapping == mapping) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		err = -EINVAL;
		spin_unlock(&swap_lock);
		जाओ out_dput;
	पूर्ण
	अगर (!security_vm_enough_memory_mm(current->mm, p->pages))
		vm_unacct_memory(p->pages);
	अन्यथा अणु
		err = -ENOMEM;
		spin_unlock(&swap_lock);
		जाओ out_dput;
	पूर्ण
	del_from_avail_list(p);
	spin_lock(&p->lock);
	अगर (p->prio < 0) अणु
		काष्ठा swap_info_काष्ठा *si = p;
		पूर्णांक nid;

		plist_क्रम_each_entry_जारी(si, &swap_active_head, list) अणु
			si->prio++;
			si->list.prio--;
			क्रम_each_node(nid) अणु
				अगर (si->avail_lists[nid].prio != 1)
					si->avail_lists[nid].prio--;
			पूर्ण
		पूर्ण
		least_priority++;
	पूर्ण
	plist_del(&p->list, &swap_active_head);
	atomic_दीर्घ_sub(p->pages, &nr_swap_pages);
	total_swap_pages -= p->pages;
	p->flags &= ~SWP_WRITEOK;
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);

	disable_swap_slots_cache_lock();

	set_current_oom_origin();
	err = try_to_unuse(p->type, false, 0); /* क्रमce unuse all pages */
	clear_current_oom_origin();

	अगर (err) अणु
		/* re-insert swap space back पूर्णांकo swap_list */
		reinsert_swap_info(p);
		reenable_swap_slots_cache_unlock();
		जाओ out_dput;
	पूर्ण

	reenable_swap_slots_cache_unlock();

	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	p->flags &= ~SWP_VALID;		/* mark swap device as invalid */
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
	/*
	 * रुको क्रम swap operations रक्षित by get/put_swap_device()
	 * to complete
	 */
	synchronize_rcu();

	flush_work(&p->discard_work);

	destroy_swap_extents(p);
	अगर (p->flags & SWP_CONTINUED)
		मुक्त_swap_count_continuations(p);

	अगर (!p->bdev || !blk_queue_nonrot(bdev_get_queue(p->bdev)))
		atomic_dec(&nr_rotate_swap);

	mutex_lock(&swapon_mutex);
	spin_lock(&swap_lock);
	spin_lock(&p->lock);
	drain_mmlist();

	/* रुको क्रम anyone still in scan_swap_map */
	p->highest_bit = 0;		/* cuts scans लघु */
	जबतक (p->flags >= SWP_SCANNING) अणु
		spin_unlock(&p->lock);
		spin_unlock(&swap_lock);
		schedule_समयout_unपूर्णांकerruptible(1);
		spin_lock(&swap_lock);
		spin_lock(&p->lock);
	पूर्ण

	swap_file = p->swap_file;
	old_block_size = p->old_block_size;
	p->swap_file = शून्य;
	p->max = 0;
	swap_map = p->swap_map;
	p->swap_map = शून्य;
	cluster_info = p->cluster_info;
	p->cluster_info = शून्य;
	frontswap_map = frontswap_map_get(p);
	spin_unlock(&p->lock);
	spin_unlock(&swap_lock);
	arch_swap_invalidate_area(p->type);
	frontswap_invalidate_area(p->type);
	frontswap_map_set(p, शून्य);
	mutex_unlock(&swapon_mutex);
	मुक्त_percpu(p->percpu_cluster);
	p->percpu_cluster = शून्य;
	मुक्त_percpu(p->cluster_next_cpu);
	p->cluster_next_cpu = शून्य;
	vमुक्त(swap_map);
	kvमुक्त(cluster_info);
	kvमुक्त(frontswap_map);
	/* Destroy swap account inक्रमmation */
	swap_cgroup_swapoff(p->type);
	निकास_swap_address_space(p->type);

	inode = mapping->host;
	अगर (S_ISBLK(inode->i_mode)) अणु
		काष्ठा block_device *bdev = I_BDEV(inode);

		set_blocksize(bdev, old_block_size);
		blkdev_put(bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
	पूर्ण

	inode_lock(inode);
	inode->i_flags &= ~S_SWAPखाता;
	inode_unlock(inode);
	filp_बंद(swap_file, शून्य);

	/*
	 * Clear the SWP_USED flag after all resources are मुक्तd so that swapon
	 * can reuse this swap_info in alloc_swap_info() safely.  It is ok to
	 * not hold p->lock after we cleared its SWP_WRITEOK.
	 */
	spin_lock(&swap_lock);
	p->flags = 0;
	spin_unlock(&swap_lock);

	err = 0;
	atomic_inc(&proc_poll_event);
	wake_up_पूर्णांकerruptible(&proc_poll_रुको);

out_dput:
	filp_बंद(victim, शून्य);
out:
	putname(pathname);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल __poll_t swaps_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा seq_file *seq = file->निजी_data;

	poll_रुको(file, &proc_poll_रुको, रुको);

	अगर (seq->poll_event != atomic_पढ़ो(&proc_poll_event)) अणु
		seq->poll_event = atomic_पढ़ो(&proc_poll_event);
		वापस EPOLLIN | EPOLLRDNORM | EPOLLERR | EPOLLPRI;
	पूर्ण

	वापस EPOLLIN | EPOLLRDNORM;
पूर्ण

/* iterator */
अटल व्योम *swap_start(काष्ठा seq_file *swap, loff_t *pos)
अणु
	काष्ठा swap_info_काष्ठा *si;
	पूर्णांक type;
	loff_t l = *pos;

	mutex_lock(&swapon_mutex);

	अगर (!l)
		वापस SEQ_START_TOKEN;

	क्रम (type = 0; (si = swap_type_to_swap_info(type)); type++) अणु
		अगर (!(si->flags & SWP_USED) || !si->swap_map)
			जारी;
		अगर (!--l)
			वापस si;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *swap_next(काष्ठा seq_file *swap, व्योम *v, loff_t *pos)
अणु
	काष्ठा swap_info_काष्ठा *si = v;
	पूर्णांक type;

	अगर (v == SEQ_START_TOKEN)
		type = 0;
	अन्यथा
		type = si->type + 1;

	++(*pos);
	क्रम (; (si = swap_type_to_swap_info(type)); type++) अणु
		अगर (!(si->flags & SWP_USED) || !si->swap_map)
			जारी;
		वापस si;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम swap_stop(काष्ठा seq_file *swap, व्योम *v)
अणु
	mutex_unlock(&swapon_mutex);
पूर्ण

अटल पूर्णांक swap_show(काष्ठा seq_file *swap, व्योम *v)
अणु
	काष्ठा swap_info_काष्ठा *si = v;
	काष्ठा file *file;
	पूर्णांक len;
	अचिन्हित पूर्णांक bytes, inuse;

	अगर (si == SEQ_START_TOKEN) अणु
		seq_माला_दो(swap, "Filename\t\t\t\tType\t\tSize\t\tUsed\t\tPriority\n");
		वापस 0;
	पूर्ण

	bytes = si->pages << (PAGE_SHIFT - 10);
	inuse = si->inuse_pages << (PAGE_SHIFT - 10);

	file = si->swap_file;
	len = seq_file_path(swap, file, " \t\n\\");
	seq_म_लिखो(swap, "%*s%s\t%u\t%s%u\t%s%d\n",
			len < 40 ? 40 - len : 1, " ",
			S_ISBLK(file_inode(file)->i_mode) ?
				"partition" : "file\t",
			bytes, bytes < 10000000 ? "\t" : "",
			inuse, inuse < 10000000 ? "\t" : "",
			si->prio);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations swaps_op = अणु
	.start =	swap_start,
	.next =		swap_next,
	.stop =		swap_stop,
	.show =		swap_show
पूर्ण;

अटल पूर्णांक swaps_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq;
	पूर्णांक ret;

	ret = seq_खोलो(file, &swaps_op);
	अगर (ret)
		वापस ret;

	seq = file->निजी_data;
	seq->poll_event = atomic_पढ़ो(&proc_poll_event);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops swaps_proc_ops = अणु
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_खोलो	= swaps_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
	.proc_poll	= swaps_poll,
पूर्ण;

अटल पूर्णांक __init procswaps_init(व्योम)
अणु
	proc_create("swaps", 0, शून्य, &swaps_proc_ops);
	वापस 0;
पूर्ण
__initcall(procswaps_init);
#पूर्ण_अगर /* CONFIG_PROC_FS */

#अगर_घोषित MAX_SWAPखाताS_CHECK
अटल पूर्णांक __init max_swapfiles_check(व्योम)
अणु
	MAX_SWAPखाताS_CHECK();
	वापस 0;
पूर्ण
late_initcall(max_swapfiles_check);
#पूर्ण_अगर

अटल काष्ठा swap_info_काष्ठा *alloc_swap_info(व्योम)
अणु
	काष्ठा swap_info_काष्ठा *p;
	काष्ठा swap_info_काष्ठा *defer = शून्य;
	अचिन्हित पूर्णांक type;
	पूर्णांक i;

	p = kvzalloc(काष्ठा_size(p, avail_lists, nr_node_ids), GFP_KERNEL);
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);

	spin_lock(&swap_lock);
	क्रम (type = 0; type < nr_swapfiles; type++) अणु
		अगर (!(swap_info[type]->flags & SWP_USED))
			अवरोध;
	पूर्ण
	अगर (type >= MAX_SWAPखाताS) अणु
		spin_unlock(&swap_lock);
		kvमुक्त(p);
		वापस ERR_PTR(-EPERM);
	पूर्ण
	अगर (type >= nr_swapfiles) अणु
		p->type = type;
		WRITE_ONCE(swap_info[type], p);
		/*
		 * Write swap_info[type] beक्रमe nr_swapfiles, in हाल a
		 * racing procfs swap_start() or swap_next() is पढ़ोing them.
		 * (We never shrink nr_swapfiles, we never मुक्त this entry.)
		 */
		smp_wmb();
		WRITE_ONCE(nr_swapfiles, nr_swapfiles + 1);
	पूर्ण अन्यथा अणु
		defer = p;
		p = swap_info[type];
		/*
		 * Do not स_रखो this entry: a racing procfs swap_next()
		 * would be relying on p->type to reमुख्य valid.
		 */
	पूर्ण
	p->swap_extent_root = RB_ROOT;
	plist_node_init(&p->list, 0);
	क्रम_each_node(i)
		plist_node_init(&p->avail_lists[i], 0);
	p->flags = SWP_USED;
	spin_unlock(&swap_lock);
	kvमुक्त(defer);
	spin_lock_init(&p->lock);
	spin_lock_init(&p->cont_lock);

	वापस p;
पूर्ण

अटल पूर्णांक claim_swapfile(काष्ठा swap_info_काष्ठा *p, काष्ठा inode *inode)
अणु
	पूर्णांक error;

	अगर (S_ISBLK(inode->i_mode)) अणु
		p->bdev = blkdev_get_by_dev(inode->i_rdev,
				   FMODE_READ | FMODE_WRITE | FMODE_EXCL, p);
		अगर (IS_ERR(p->bdev)) अणु
			error = PTR_ERR(p->bdev);
			p->bdev = शून्य;
			वापस error;
		पूर्ण
		p->old_block_size = block_size(p->bdev);
		error = set_blocksize(p->bdev, PAGE_SIZE);
		अगर (error < 0)
			वापस error;
		/*
		 * Zoned block devices contain zones that have a sequential
		 * ग_लिखो only restriction.  Hence zoned block devices are not
		 * suitable क्रम swapping.  Disallow them here.
		 */
		अगर (blk_queue_is_zoned(p->bdev->bd_disk->queue))
			वापस -EINVAL;
		p->flags |= SWP_BLKDEV;
	पूर्ण अन्यथा अगर (S_ISREG(inode->i_mode)) अणु
		p->bdev = inode->i_sb->s_bdev;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Find out how many pages are allowed क्रम a single swap device. There
 * are two limiting factors:
 * 1) the number of bits क्रम the swap offset in the swp_entry_t type, and
 * 2) the number of bits in the swap pte, as defined by the dअगरferent
 * architectures.
 *
 * In order to find the largest possible bit mask, a swap entry with
 * swap type 0 and swap offset ~0UL is created, encoded to a swap pte,
 * decoded to a swp_entry_t again, and finally the swap offset is
 * extracted.
 *
 * This will mask all the bits from the initial ~0UL mask that can't
 * be encoded in either the swp_entry_t or the architecture definition
 * of a swap pte.
 */
अचिन्हित दीर्घ generic_max_swapfile_size(व्योम)
अणु
	वापस swp_offset(pte_to_swp_entry(
			swp_entry_to_pte(swp_entry(0, ~0UL)))) + 1;
पूर्ण

/* Can be overridden by an architecture क्रम additional checks. */
__weak अचिन्हित दीर्घ max_swapfile_size(व्योम)
अणु
	वापस generic_max_swapfile_size();
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_swap_header(काष्ठा swap_info_काष्ठा *p,
					जोड़ swap_header *swap_header,
					काष्ठा inode *inode)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ maxpages;
	अचिन्हित दीर्घ swapfilepages;
	अचिन्हित दीर्घ last_page;

	अगर (स_भेद("SWAPSPACE2", swap_header->magic.magic, 10)) अणु
		pr_err("Unable to find swap-space signature\n");
		वापस 0;
	पूर्ण

	/* swap partition endianess hack... */
	अगर (swab32(swap_header->info.version) == 1) अणु
		swab32s(&swap_header->info.version);
		swab32s(&swap_header->info.last_page);
		swab32s(&swap_header->info.nr_badpages);
		अगर (swap_header->info.nr_badpages > MAX_SWAP_BADPAGES)
			वापस 0;
		क्रम (i = 0; i < swap_header->info.nr_badpages; i++)
			swab32s(&swap_header->info.badpages[i]);
	पूर्ण
	/* Check the swap header's sub-version */
	अगर (swap_header->info.version != 1) अणु
		pr_warn("Unable to handle swap header version %d\n",
			swap_header->info.version);
		वापस 0;
	पूर्ण

	p->lowest_bit  = 1;
	p->cluster_next = 1;
	p->cluster_nr = 0;

	maxpages = max_swapfile_size();
	last_page = swap_header->info.last_page;
	अगर (!last_page) अणु
		pr_warn("Empty swap-file\n");
		वापस 0;
	पूर्ण
	अगर (last_page > maxpages) अणु
		pr_warn("Truncating oversized swap area, only using %luk out of %luk\n",
			maxpages << (PAGE_SHIFT - 10),
			last_page << (PAGE_SHIFT - 10));
	पूर्ण
	अगर (maxpages > last_page) अणु
		maxpages = last_page + 1;
		/* p->max is an अचिन्हित पूर्णांक: करोn't overflow it */
		अगर ((अचिन्हित पूर्णांक)maxpages == 0)
			maxpages = अच_पूर्णांक_उच्च;
	पूर्ण
	p->highest_bit = maxpages - 1;

	अगर (!maxpages)
		वापस 0;
	swapfilepages = i_size_पढ़ो(inode) >> PAGE_SHIFT;
	अगर (swapfilepages && maxpages > swapfilepages) अणु
		pr_warn("Swap area shorter than signature indicates\n");
		वापस 0;
	पूर्ण
	अगर (swap_header->info.nr_badpages && S_ISREG(inode->i_mode))
		वापस 0;
	अगर (swap_header->info.nr_badpages > MAX_SWAP_BADPAGES)
		वापस 0;

	वापस maxpages;
पूर्ण

#घोषणा SWAP_CLUSTER_INFO_COLS						\
	DIV_ROUND_UP(L1_CACHE_BYTES, माप(काष्ठा swap_cluster_info))
#घोषणा SWAP_CLUSTER_SPACE_COLS						\
	DIV_ROUND_UP(SWAP_ADDRESS_SPACE_PAGES, SWAPखाता_CLUSTER)
#घोषणा SWAP_CLUSTER_COLS						\
	max_t(अचिन्हित पूर्णांक, SWAP_CLUSTER_INFO_COLS, SWAP_CLUSTER_SPACE_COLS)

अटल पूर्णांक setup_swap_map_and_extents(काष्ठा swap_info_काष्ठा *p,
					जोड़ swap_header *swap_header,
					अचिन्हित अक्षर *swap_map,
					काष्ठा swap_cluster_info *cluster_info,
					अचिन्हित दीर्घ maxpages,
					sector_t *span)
अणु
	अचिन्हित पूर्णांक j, k;
	अचिन्हित पूर्णांक nr_good_pages;
	पूर्णांक nr_extents;
	अचिन्हित दीर्घ nr_clusters = DIV_ROUND_UP(maxpages, SWAPखाता_CLUSTER);
	अचिन्हित दीर्घ col = p->cluster_next / SWAPखाता_CLUSTER % SWAP_CLUSTER_COLS;
	अचिन्हित दीर्घ i, idx;

	nr_good_pages = maxpages - 1;	/* omit header page */

	cluster_list_init(&p->मुक्त_clusters);
	cluster_list_init(&p->discard_clusters);

	क्रम (i = 0; i < swap_header->info.nr_badpages; i++) अणु
		अचिन्हित पूर्णांक page_nr = swap_header->info.badpages[i];
		अगर (page_nr == 0 || page_nr > swap_header->info.last_page)
			वापस -EINVAL;
		अगर (page_nr < maxpages) अणु
			swap_map[page_nr] = SWAP_MAP_BAD;
			nr_good_pages--;
			/*
			 * Haven't marked the cluster मुक्त yet, no list
			 * operation involved
			 */
			inc_cluster_info_page(p, cluster_info, page_nr);
		पूर्ण
	पूर्ण

	/* Haven't marked the cluster मुक्त yet, no list operation involved */
	क्रम (i = maxpages; i < round_up(maxpages, SWAPखाता_CLUSTER); i++)
		inc_cluster_info_page(p, cluster_info, i);

	अगर (nr_good_pages) अणु
		swap_map[0] = SWAP_MAP_BAD;
		/*
		 * Not mark the cluster मुक्त yet, no list
		 * operation involved
		 */
		inc_cluster_info_page(p, cluster_info, 0);
		p->max = maxpages;
		p->pages = nr_good_pages;
		nr_extents = setup_swap_extents(p, span);
		अगर (nr_extents < 0)
			वापस nr_extents;
		nr_good_pages = p->pages;
	पूर्ण
	अगर (!nr_good_pages) अणु
		pr_warn("Empty swap-file\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cluster_info)
		वापस nr_extents;


	/*
	 * Reduce false cache line sharing between cluster_info and
	 * sharing same address space.
	 */
	क्रम (k = 0; k < SWAP_CLUSTER_COLS; k++) अणु
		j = (k + col) % SWAP_CLUSTER_COLS;
		क्रम (i = 0; i < DIV_ROUND_UP(nr_clusters, SWAP_CLUSTER_COLS); i++) अणु
			idx = i * SWAP_CLUSTER_COLS + j;
			अगर (idx >= nr_clusters)
				जारी;
			अगर (cluster_count(&cluster_info[idx]))
				जारी;
			cluster_set_flag(&cluster_info[idx], CLUSTER_FLAG_FREE);
			cluster_list_add_tail(&p->मुक्त_clusters, cluster_info,
					      idx);
		पूर्ण
	पूर्ण
	वापस nr_extents;
पूर्ण

/*
 * Helper to sys_swapon determining अगर a given swap
 * backing device queue supports DISCARD operations.
 */
अटल bool swap_discardable(काष्ठा swap_info_काष्ठा *si)
अणु
	काष्ठा request_queue *q = bdev_get_queue(si->bdev);

	अगर (!q || !blk_queue_discard(q))
		वापस false;

	वापस true;
पूर्ण

SYSCALL_DEFINE2(swapon, स्थिर अक्षर __user *, specialfile, पूर्णांक, swap_flags)
अणु
	काष्ठा swap_info_काष्ठा *p;
	काष्ठा filename *name;
	काष्ठा file *swap_file = शून्य;
	काष्ठा address_space *mapping;
	पूर्णांक prio;
	पूर्णांक error;
	जोड़ swap_header *swap_header;
	पूर्णांक nr_extents;
	sector_t span;
	अचिन्हित दीर्घ maxpages;
	अचिन्हित अक्षर *swap_map = शून्य;
	काष्ठा swap_cluster_info *cluster_info = शून्य;
	अचिन्हित दीर्घ *frontswap_map = शून्य;
	काष्ठा page *page = शून्य;
	काष्ठा inode *inode = शून्य;
	bool inced_nr_rotate_swap = false;

	अगर (swap_flags & ~SWAP_FLAGS_VALID)
		वापस -EINVAL;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!swap_avail_heads)
		वापस -ENOMEM;

	p = alloc_swap_info();
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	INIT_WORK(&p->discard_work, swap_discard_work);

	name = getname(specialfile);
	अगर (IS_ERR(name)) अणु
		error = PTR_ERR(name);
		name = शून्य;
		जाओ bad_swap;
	पूर्ण
	swap_file = file_खोलो_name(name, O_RDWR|O_LARGEखाता, 0);
	अगर (IS_ERR(swap_file)) अणु
		error = PTR_ERR(swap_file);
		swap_file = शून्य;
		जाओ bad_swap;
	पूर्ण

	p->swap_file = swap_file;
	mapping = swap_file->f_mapping;
	inode = mapping->host;

	error = claim_swapfile(p, inode);
	अगर (unlikely(error))
		जाओ bad_swap;

	inode_lock(inode);
	अगर (IS_SWAPखाता(inode)) अणु
		error = -EBUSY;
		जाओ bad_swap_unlock_inode;
	पूर्ण

	/*
	 * Read the swap header.
	 */
	अगर (!mapping->a_ops->पढ़ोpage) अणु
		error = -EINVAL;
		जाओ bad_swap_unlock_inode;
	पूर्ण
	page = पढ़ो_mapping_page(mapping, 0, swap_file);
	अगर (IS_ERR(page)) अणु
		error = PTR_ERR(page);
		जाओ bad_swap_unlock_inode;
	पूर्ण
	swap_header = kmap(page);

	maxpages = पढ़ो_swap_header(p, swap_header, inode);
	अगर (unlikely(!maxpages)) अणु
		error = -EINVAL;
		जाओ bad_swap_unlock_inode;
	पूर्ण

	/* OK, set up the swap map and apply the bad block list */
	swap_map = vzalloc(maxpages);
	अगर (!swap_map) अणु
		error = -ENOMEM;
		जाओ bad_swap_unlock_inode;
	पूर्ण

	अगर (p->bdev && blk_queue_stable_ग_लिखोs(p->bdev->bd_disk->queue))
		p->flags |= SWP_STABLE_WRITES;

	अगर (p->bdev && p->bdev->bd_disk->fops->rw_page)
		p->flags |= SWP_SYNCHRONOUS_IO;

	अगर (p->bdev && blk_queue_nonrot(bdev_get_queue(p->bdev))) अणु
		पूर्णांक cpu;
		अचिन्हित दीर्घ ci, nr_cluster;

		p->flags |= SWP_SOLIDSTATE;
		p->cluster_next_cpu = alloc_percpu(अचिन्हित पूर्णांक);
		अगर (!p->cluster_next_cpu) अणु
			error = -ENOMEM;
			जाओ bad_swap_unlock_inode;
		पूर्ण
		/*
		 * select a अक्रमom position to start with to help wear leveling
		 * SSD
		 */
		क्रम_each_possible_cpu(cpu) अणु
			per_cpu(*p->cluster_next_cpu, cpu) =
				1 + pअक्रमom_u32_max(p->highest_bit);
		पूर्ण
		nr_cluster = DIV_ROUND_UP(maxpages, SWAPखाता_CLUSTER);

		cluster_info = kvसुस्मृति(nr_cluster, माप(*cluster_info),
					GFP_KERNEL);
		अगर (!cluster_info) अणु
			error = -ENOMEM;
			जाओ bad_swap_unlock_inode;
		पूर्ण

		क्रम (ci = 0; ci < nr_cluster; ci++)
			spin_lock_init(&((cluster_info + ci)->lock));

		p->percpu_cluster = alloc_percpu(काष्ठा percpu_cluster);
		अगर (!p->percpu_cluster) अणु
			error = -ENOMEM;
			जाओ bad_swap_unlock_inode;
		पूर्ण
		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा percpu_cluster *cluster;
			cluster = per_cpu_ptr(p->percpu_cluster, cpu);
			cluster_set_null(&cluster->index);
		पूर्ण
	पूर्ण अन्यथा अणु
		atomic_inc(&nr_rotate_swap);
		inced_nr_rotate_swap = true;
	पूर्ण

	error = swap_cgroup_swapon(p->type, maxpages);
	अगर (error)
		जाओ bad_swap_unlock_inode;

	nr_extents = setup_swap_map_and_extents(p, swap_header, swap_map,
		cluster_info, maxpages, &span);
	अगर (unlikely(nr_extents < 0)) अणु
		error = nr_extents;
		जाओ bad_swap_unlock_inode;
	पूर्ण
	/* frontswap enabled? set up bit-per-page map क्रम frontswap */
	अगर (IS_ENABLED(CONFIG_FRONTSWAP))
		frontswap_map = kvसुस्मृति(BITS_TO_LONGS(maxpages),
					 माप(दीर्घ),
					 GFP_KERNEL);

	अगर (p->bdev && (swap_flags & SWAP_FLAG_DISCARD) && swap_discardable(p)) अणु
		/*
		 * When discard is enabled क्रम swap with no particular
		 * policy flagged, we set all swap discard flags here in
		 * order to sustain backward compatibility with older
		 * swapon(8) releases.
		 */
		p->flags |= (SWP_DISCARDABLE | SWP_AREA_DISCARD |
			     SWP_PAGE_DISCARD);

		/*
		 * By flagging sys_swapon, a sysadmin can tell us to
		 * either करो single-समय area discards only, or to just
		 * perक्रमm discards क्रम released swap page-clusters.
		 * Now it's समय to adjust the p->flags accordingly.
		 */
		अगर (swap_flags & SWAP_FLAG_DISCARD_ONCE)
			p->flags &= ~SWP_PAGE_DISCARD;
		अन्यथा अगर (swap_flags & SWAP_FLAG_DISCARD_PAGES)
			p->flags &= ~SWP_AREA_DISCARD;

		/* issue a swapon-समय discard अगर it's still required */
		अगर (p->flags & SWP_AREA_DISCARD) अणु
			पूर्णांक err = discard_swap(p);
			अगर (unlikely(err))
				pr_err("swapon: discard_swap(%p): %d\n",
					p, err);
		पूर्ण
	पूर्ण

	error = init_swap_address_space(p->type, maxpages);
	अगर (error)
		जाओ bad_swap_unlock_inode;

	/*
	 * Flush any pending IO and dirty mappings beक्रमe we start using this
	 * swap device.
	 */
	inode->i_flags |= S_SWAPखाता;
	error = inode_drain_ग_लिखोs(inode);
	अगर (error) अणु
		inode->i_flags &= ~S_SWAPखाता;
		जाओ मुक्त_swap_address_space;
	पूर्ण

	mutex_lock(&swapon_mutex);
	prio = -1;
	अगर (swap_flags & SWAP_FLAG_PREFER)
		prio =
		  (swap_flags & SWAP_FLAG_PRIO_MASK) >> SWAP_FLAG_PRIO_SHIFT;
	enable_swap_info(p, prio, swap_map, cluster_info, frontswap_map);

	pr_info("Adding %uk swap on %s.  Priority:%d extents:%d across:%lluk %s%s%s%s%s\n",
		p->pages<<(PAGE_SHIFT-10), name->name, p->prio,
		nr_extents, (अचिन्हित दीर्घ दीर्घ)span<<(PAGE_SHIFT-10),
		(p->flags & SWP_SOLIDSTATE) ? "SS" : "",
		(p->flags & SWP_DISCARDABLE) ? "D" : "",
		(p->flags & SWP_AREA_DISCARD) ? "s" : "",
		(p->flags & SWP_PAGE_DISCARD) ? "c" : "",
		(frontswap_map) ? "FS" : "");

	mutex_unlock(&swapon_mutex);
	atomic_inc(&proc_poll_event);
	wake_up_पूर्णांकerruptible(&proc_poll_रुको);

	error = 0;
	जाओ out;
मुक्त_swap_address_space:
	निकास_swap_address_space(p->type);
bad_swap_unlock_inode:
	inode_unlock(inode);
bad_swap:
	मुक्त_percpu(p->percpu_cluster);
	p->percpu_cluster = शून्य;
	मुक्त_percpu(p->cluster_next_cpu);
	p->cluster_next_cpu = शून्य;
	अगर (inode && S_ISBLK(inode->i_mode) && p->bdev) अणु
		set_blocksize(p->bdev, p->old_block_size);
		blkdev_put(p->bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
	पूर्ण
	inode = शून्य;
	destroy_swap_extents(p);
	swap_cgroup_swapoff(p->type);
	spin_lock(&swap_lock);
	p->swap_file = शून्य;
	p->flags = 0;
	spin_unlock(&swap_lock);
	vमुक्त(swap_map);
	kvमुक्त(cluster_info);
	kvमुक्त(frontswap_map);
	अगर (inced_nr_rotate_swap)
		atomic_dec(&nr_rotate_swap);
	अगर (swap_file)
		filp_बंद(swap_file, शून्य);
out:
	अगर (page && !IS_ERR(page)) अणु
		kunmap(page);
		put_page(page);
	पूर्ण
	अगर (name)
		putname(name);
	अगर (inode)
		inode_unlock(inode);
	अगर (!error)
		enable_swap_slots_cache();
	वापस error;
पूर्ण

व्योम si_swapinfo(काष्ठा sysinfo *val)
अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित दीर्घ nr_to_be_unused = 0;

	spin_lock(&swap_lock);
	क्रम (type = 0; type < nr_swapfiles; type++) अणु
		काष्ठा swap_info_काष्ठा *si = swap_info[type];

		अगर ((si->flags & SWP_USED) && !(si->flags & SWP_WRITEOK))
			nr_to_be_unused += si->inuse_pages;
	पूर्ण
	val->मुक्तswap = atomic_दीर्घ_पढ़ो(&nr_swap_pages) + nr_to_be_unused;
	val->totalswap = total_swap_pages + nr_to_be_unused;
	spin_unlock(&swap_lock);
पूर्ण

/*
 * Verअगरy that a swap entry is valid and increment its swap map count.
 *
 * Returns error code in following हाल.
 * - success -> 0
 * - swp_entry is invalid -> EINVAL
 * - swp_entry is migration entry -> EINVAL
 * - swap-cache reference is requested but there is alपढ़ोy one. -> EEXIST
 * - swap-cache reference is requested but the entry is not used. -> ENOENT
 * - swap-mapped reference requested but needs जारीd swap count. -> ENOMEM
 */
अटल पूर्णांक __swap_duplicate(swp_entry_t entry, अचिन्हित अक्षर usage)
अणु
	काष्ठा swap_info_काष्ठा *p;
	काष्ठा swap_cluster_info *ci;
	अचिन्हित दीर्घ offset;
	अचिन्हित अक्षर count;
	अचिन्हित अक्षर has_cache;
	पूर्णांक err;

	p = get_swap_device(entry);
	अगर (!p)
		वापस -EINVAL;

	offset = swp_offset(entry);
	ci = lock_cluster_or_swap_info(p, offset);

	count = p->swap_map[offset];

	/*
	 * swapin_पढ़ोahead() करोesn't check अगर a swap entry is valid, so the
	 * swap entry could be SWAP_MAP_BAD. Check here with lock held.
	 */
	अगर (unlikely(swap_count(count) == SWAP_MAP_BAD)) अणु
		err = -ENOENT;
		जाओ unlock_out;
	पूर्ण

	has_cache = count & SWAP_HAS_CACHE;
	count &= ~SWAP_HAS_CACHE;
	err = 0;

	अगर (usage == SWAP_HAS_CACHE) अणु

		/* set SWAP_HAS_CACHE अगर there is no cache and entry is used */
		अगर (!has_cache && count)
			has_cache = SWAP_HAS_CACHE;
		अन्यथा अगर (has_cache)		/* someone अन्यथा added cache */
			err = -EEXIST;
		अन्यथा				/* no users reमुख्यing */
			err = -ENOENT;

	पूर्ण अन्यथा अगर (count || has_cache) अणु

		अगर ((count & ~COUNT_CONTINUED) < SWAP_MAP_MAX)
			count += usage;
		अन्यथा अगर ((count & ~COUNT_CONTINUED) > SWAP_MAP_MAX)
			err = -EINVAL;
		अन्यथा अगर (swap_count_जारीd(p, offset, count))
			count = COUNT_CONTINUED;
		अन्यथा
			err = -ENOMEM;
	पूर्ण अन्यथा
		err = -ENOENT;			/* unused swap entry */

	WRITE_ONCE(p->swap_map[offset], count | has_cache);

unlock_out:
	unlock_cluster_or_swap_info(p, ci);
	अगर (p)
		put_swap_device(p);
	वापस err;
पूर्ण

/*
 * Help swapoff by noting that swap entry beदीर्घs to shmem/पंचांगpfs
 * (in which हाल its reference count is never incremented).
 */
व्योम swap_shmem_alloc(swp_entry_t entry)
अणु
	__swap_duplicate(entry, SWAP_MAP_SHMEM);
पूर्ण

/*
 * Increase reference count of swap entry by 1.
 * Returns 0 क्रम success, or -ENOMEM अगर a swap_count_continuation is required
 * but could not be atomically allocated.  Returns 0, just as अगर it succeeded,
 * अगर __swap_duplicate() fails क्रम another reason (-EINVAL or -ENOENT), which
 * might occur अगर a page table entry has got corrupted.
 */
पूर्णांक swap_duplicate(swp_entry_t entry)
अणु
	पूर्णांक err = 0;

	जबतक (!err && __swap_duplicate(entry, 1) == -ENOMEM)
		err = add_swap_count_continuation(entry, GFP_ATOMIC);
	वापस err;
पूर्ण

/*
 * @entry: swap entry क्रम which we allocate swap cache.
 *
 * Called when allocating swap cache क्रम existing swap entry,
 * This can वापस error codes. Returns 0 at success.
 * -EEXIST means there is a swap cache.
 * Note: वापस code is dअगरferent from swap_duplicate().
 */
पूर्णांक swapcache_prepare(swp_entry_t entry)
अणु
	वापस __swap_duplicate(entry, SWAP_HAS_CACHE);
पूर्ण

काष्ठा swap_info_काष्ठा *swp_swap_info(swp_entry_t entry)
अणु
	वापस swap_type_to_swap_info(swp_type(entry));
पूर्ण

काष्ठा swap_info_काष्ठा *page_swap_info(काष्ठा page *page)
अणु
	swp_entry_t entry = अणु .val = page_निजी(page) पूर्ण;
	वापस swp_swap_info(entry);
पूर्ण

/*
 * out-of-line __page_file_ methods to aव्योम include hell.
 */
काष्ठा address_space *__page_file_mapping(काष्ठा page *page)
अणु
	वापस page_swap_info(page)->swap_file->f_mapping;
पूर्ण
EXPORT_SYMBOL_GPL(__page_file_mapping);

pgoff_t __page_file_index(काष्ठा page *page)
अणु
	swp_entry_t swap = अणु .val = page_निजी(page) पूर्ण;
	वापस swp_offset(swap);
पूर्ण
EXPORT_SYMBOL_GPL(__page_file_index);

/*
 * add_swap_count_continuation - called when a swap count is duplicated
 * beyond SWAP_MAP_MAX, it allocates a new page and links that to the entry's
 * page of the original vदो_स्मृति'ed swap_map, to hold the continuation count
 * (क्रम that entry and क्रम its neighbouring PAGE_SIZE swap entries).  Called
 * again when count is duplicated beyond SWAP_MAP_MAX * SWAP_CONT_MAX, etc.
 *
 * These continuation pages are selकरोm referenced: the common paths all work
 * on the original swap_map, only referring to a continuation page when the
 * low "digit" of a count is incremented or decremented through SWAP_MAP_MAX.
 *
 * add_swap_count_continuation(, GFP_ATOMIC) can be called जबतक holding
 * page table locks; अगर it fails, add_swap_count_continuation(, GFP_KERNEL)
 * can be called after dropping locks.
 */
पूर्णांक add_swap_count_continuation(swp_entry_t entry, gfp_t gfp_mask)
अणु
	काष्ठा swap_info_काष्ठा *si;
	काष्ठा swap_cluster_info *ci;
	काष्ठा page *head;
	काष्ठा page *page;
	काष्ठा page *list_page;
	pgoff_t offset;
	अचिन्हित अक्षर count;
	पूर्णांक ret = 0;

	/*
	 * When debugging, it's easier to use __GFP_ZERO here; but it's better
	 * क्रम latency not to zero a page जबतक GFP_ATOMIC and holding locks.
	 */
	page = alloc_page(gfp_mask | __GFP_HIGHMEM);

	si = get_swap_device(entry);
	अगर (!si) अणु
		/*
		 * An acceptable race has occurred since the failing
		 * __swap_duplicate(): the swap device may be swapoff
		 */
		जाओ outer;
	पूर्ण
	spin_lock(&si->lock);

	offset = swp_offset(entry);

	ci = lock_cluster(si, offset);

	count = swap_count(si->swap_map[offset]);

	अगर ((count & ~COUNT_CONTINUED) != SWAP_MAP_MAX) अणु
		/*
		 * The higher the swap count, the more likely it is that tasks
		 * will race to add swap count continuation: we need to aव्योम
		 * over-provisioning.
		 */
		जाओ out;
	पूर्ण

	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * We are क्रमtunate that although vदो_स्मृति_to_page uses pte_offset_map,
	 * no architecture is using highmem pages क्रम kernel page tables: so it
	 * will not corrupt the GFP_ATOMIC caller's atomic page table kmaps.
	 */
	head = vदो_स्मृति_to_page(si->swap_map + offset);
	offset &= ~PAGE_MASK;

	spin_lock(&si->cont_lock);
	/*
	 * Page allocation करोes not initialize the page's lru field,
	 * but it करोes always reset its निजी field.
	 */
	अगर (!page_निजी(head)) अणु
		BUG_ON(count & COUNT_CONTINUED);
		INIT_LIST_HEAD(&head->lru);
		set_page_निजी(head, SWP_CONTINUED);
		si->flags |= SWP_CONTINUED;
	पूर्ण

	list_क्रम_each_entry(list_page, &head->lru, lru) अणु
		अचिन्हित अक्षर *map;

		/*
		 * If the previous map said no continuation, but we've found
		 * a continuation page, मुक्त our allocation and use this one.
		 */
		अगर (!(count & COUNT_CONTINUED))
			जाओ out_unlock_cont;

		map = kmap_atomic(list_page) + offset;
		count = *map;
		kunmap_atomic(map);

		/*
		 * If this continuation count now has some space in it,
		 * मुक्त our allocation and use this one.
		 */
		अगर ((count & ~COUNT_CONTINUED) != SWAP_CONT_MAX)
			जाओ out_unlock_cont;
	पूर्ण

	list_add_tail(&page->lru, &head->lru);
	page = शून्य;			/* now it's attached, don't मुक्त it */
out_unlock_cont:
	spin_unlock(&si->cont_lock);
out:
	unlock_cluster(ci);
	spin_unlock(&si->lock);
	put_swap_device(si);
outer:
	अगर (page)
		__मुक्त_page(page);
	वापस ret;
पूर्ण

/*
 * swap_count_जारीd - when the original swap_map count is incremented
 * from SWAP_MAP_MAX, check अगर there is alपढ़ोy a continuation page to carry
 * पूर्णांकo, carry अगर so, or अन्यथा fail until a new continuation page is allocated;
 * when the original swap_map count is decremented from 0 with continuation,
 * borrow from the continuation and report whether it still holds more.
 * Called जबतक __swap_duplicate() or swap_entry_मुक्त() holds swap or cluster
 * lock.
 */
अटल bool swap_count_जारीd(काष्ठा swap_info_काष्ठा *si,
				 pgoff_t offset, अचिन्हित अक्षर count)
अणु
	काष्ठा page *head;
	काष्ठा page *page;
	अचिन्हित अक्षर *map;
	bool ret;

	head = vदो_स्मृति_to_page(si->swap_map + offset);
	अगर (page_निजी(head) != SWP_CONTINUED) अणु
		BUG_ON(count & COUNT_CONTINUED);
		वापस false;		/* need to add count continuation */
	पूर्ण

	spin_lock(&si->cont_lock);
	offset &= ~PAGE_MASK;
	page = list_next_entry(head, lru);
	map = kmap_atomic(page) + offset;

	अगर (count == SWAP_MAP_MAX)	/* initial increment from swap_map */
		जाओ init_map;		/* jump over SWAP_CONT_MAX checks */

	अगर (count == (SWAP_MAP_MAX | COUNT_CONTINUED)) अणु /* incrementing */
		/*
		 * Think of how you add 1 to 999
		 */
		जबतक (*map == (SWAP_CONT_MAX | COUNT_CONTINUED)) अणु
			kunmap_atomic(map);
			page = list_next_entry(page, lru);
			BUG_ON(page == head);
			map = kmap_atomic(page) + offset;
		पूर्ण
		अगर (*map == SWAP_CONT_MAX) अणु
			kunmap_atomic(map);
			page = list_next_entry(page, lru);
			अगर (page == head) अणु
				ret = false;	/* add count continuation */
				जाओ out;
			पूर्ण
			map = kmap_atomic(page) + offset;
init_map:		*map = 0;		/* we didn't zero the page */
		पूर्ण
		*map += 1;
		kunmap_atomic(map);
		जबतक ((page = list_prev_entry(page, lru)) != head) अणु
			map = kmap_atomic(page) + offset;
			*map = COUNT_CONTINUED;
			kunmap_atomic(map);
		पूर्ण
		ret = true;			/* incremented */

	पूर्ण अन्यथा अणु				/* decrementing */
		/*
		 * Think of how you subtract 1 from 1000
		 */
		BUG_ON(count != COUNT_CONTINUED);
		जबतक (*map == COUNT_CONTINUED) अणु
			kunmap_atomic(map);
			page = list_next_entry(page, lru);
			BUG_ON(page == head);
			map = kmap_atomic(page) + offset;
		पूर्ण
		BUG_ON(*map == 0);
		*map -= 1;
		अगर (*map == 0)
			count = 0;
		kunmap_atomic(map);
		जबतक ((page = list_prev_entry(page, lru)) != head) अणु
			map = kmap_atomic(page) + offset;
			*map = SWAP_CONT_MAX | count;
			count = COUNT_CONTINUED;
			kunmap_atomic(map);
		पूर्ण
		ret = count == COUNT_CONTINUED;
	पूर्ण
out:
	spin_unlock(&si->cont_lock);
	वापस ret;
पूर्ण

/*
 * मुक्त_swap_count_continuations - swapoff मुक्त all the continuation pages
 * appended to the swap_map, after swap_map is quiesced, beक्रमe vमुक्त'ing it.
 */
अटल व्योम मुक्त_swap_count_continuations(काष्ठा swap_info_काष्ठा *si)
अणु
	pgoff_t offset;

	क्रम (offset = 0; offset < si->max; offset += PAGE_SIZE) अणु
		काष्ठा page *head;
		head = vदो_स्मृति_to_page(si->swap_map + offset);
		अगर (page_निजी(head)) अणु
			काष्ठा page *page, *next;

			list_क्रम_each_entry_safe(page, next, &head->lru, lru) अणु
				list_del(&page->lru);
				__मुक्त_page(page);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#अगर defined(CONFIG_MEMCG) && defined(CONFIG_BLK_CGROUP)
व्योम cgroup_throttle_swaprate(काष्ठा page *page, gfp_t gfp_mask)
अणु
	काष्ठा swap_info_काष्ठा *si, *next;
	पूर्णांक nid = page_to_nid(page);

	अगर (!(gfp_mask & __GFP_IO))
		वापस;

	अगर (!blk_cgroup_congested())
		वापस;

	/*
	 * We've alपढ़ोy scheduled a throttle, aव्योम taking the global swap
	 * lock.
	 */
	अगर (current->throttle_queue)
		वापस;

	spin_lock(&swap_avail_lock);
	plist_क्रम_each_entry_safe(si, next, &swap_avail_heads[nid],
				  avail_lists[nid]) अणु
		अगर (si->bdev) अणु
			blkcg_schedule_throttle(bdev_get_queue(si->bdev), true);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&swap_avail_lock);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init swapfile_init(व्योम)
अणु
	पूर्णांक nid;

	swap_avail_heads = kदो_स्मृति_array(nr_node_ids, माप(काष्ठा plist_head),
					 GFP_KERNEL);
	अगर (!swap_avail_heads) अणु
		pr_emerg("Not enough memory for swap heads, swap is disabled\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_node(nid)
		plist_head_init(&swap_avail_heads[nid]);

	वापस 0;
पूर्ण
subsys_initcall(swapfile_init);
