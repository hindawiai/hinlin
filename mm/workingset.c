<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Workingset detection
 *
 * Copyright (C) 2013 Red Hat, Inc., Johannes Weiner
 */

#समावेश <linux/memcontrol.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/atomic.h>
#समावेश <linux/module.h>
#समावेश <linux/swap.h>
#समावेश <linux/dax.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>

/*
 *		Double CLOCK lists
 *
 * Per node, two घड़ी lists are मुख्यtained क्रम file pages: the
 * inactive and the active list.  Freshly faulted pages start out at
 * the head of the inactive list and page reclaim scans pages from the
 * tail.  Pages that are accessed multiple बार on the inactive list
 * are promoted to the active list, to protect them from reclaim,
 * whereas active pages are demoted to the inactive list when the
 * active list grows too big.
 *
 *   fault ------------------------+
 *                                 |
 *              +--------------+   |            +-------------+
 *   reclaim <- |   inactive   | <-+-- demotion |    active   | <--+
 *              +--------------+                +-------------+    |
 *                     |                                           |
 *                     +-------------- promotion ------------------+
 *
 *
 *		Access frequency and refault distance
 *
 * A workload is thrashing when its pages are frequently used but they
 * are evicted from the inactive list every समय beक्रमe another access
 * would have promoted them to the active list.
 *
 * In हालs where the average access distance between thrashing pages
 * is bigger than the size of memory there is nothing that can be
 * करोne - the thrashing set could never fit पूर्णांकo memory under any
 * circumstance.
 *
 * However, the average access distance could be bigger than the
 * inactive list, yet smaller than the size of memory.  In this हाल,
 * the set could fit पूर्णांकo memory अगर it weren't क्रम the currently
 * active pages - which may be used more, hopefully less frequently:
 *
 *      +-memory available to cache-+
 *      |                           |
 *      +-inactive------+-active----+
 *  a b | c d e f g h i | J K L M N |
 *      +---------------+-----------+
 *
 * It is prohibitively expensive to accurately track access frequency
 * of pages.  But a reasonable approximation can be made to measure
 * thrashing on the inactive list, after which refaulting pages can be
 * activated optimistically to compete with the existing active pages.
 *
 * Approximating inactive page access frequency - Observations:
 *
 * 1. When a page is accessed क्रम the first समय, it is added to the
 *    head of the inactive list, slides every existing inactive page
 *    towards the tail by one slot, and pushes the current tail page
 *    out of memory.
 *
 * 2. When a page is accessed क्रम the second समय, it is promoted to
 *    the active list, shrinking the inactive list by one slot.  This
 *    also slides all inactive pages that were faulted पूर्णांकo the cache
 *    more recently than the activated page towards the tail of the
 *    inactive list.
 *
 * Thus:
 *
 * 1. The sum of evictions and activations between any two poपूर्णांकs in
 *    समय indicate the minimum number of inactive pages accessed in
 *    between.
 *
 * 2. Moving one inactive page N page slots towards the tail of the
 *    list requires at least N inactive page accesses.
 *
 * Combining these:
 *
 * 1. When a page is finally evicted from memory, the number of
 *    inactive pages accessed जबतक the page was in cache is at least
 *    the number of page slots on the inactive list.
 *
 * 2. In addition, measuring the sum of evictions and activations (E)
 *    at the समय of a page's eviction, and comparing it to another
 *    पढ़ोing (R) at the समय the page faults back पूर्णांकo memory tells
 *    the minimum number of accesses जबतक the page was not cached.
 *    This is called the refault distance.
 *
 * Because the first access of the page was the fault and the second
 * access the refault, we combine the in-cache distance with the
 * out-of-cache distance to get the complete minimum access distance
 * of this page:
 *
 *      NR_inactive + (R - E)
 *
 * And knowing the minimum access distance of a page, we can easily
 * tell अगर the page would be able to stay in cache assuming all page
 * slots in the cache were available:
 *
 *   NR_inactive + (R - E) <= NR_inactive + NR_active
 *
 * which can be further simplअगरied to
 *
 *   (R - E) <= NR_active
 *
 * Put पूर्णांकo words, the refault distance (out-of-cache) can be seen as
 * a deficit in inactive list space (in-cache).  If the inactive list
 * had (R - E) more page slots, the page would not have been evicted
 * in between accesses, but activated instead.  And on a full प्रणाली,
 * the only thing eating पूर्णांकo inactive list space is active pages.
 *
 *
 *		Refaulting inactive pages
 *
 * All that is known about the active list is that the pages have been
 * accessed more than once in the past.  This means that at any given
 * समय there is actually a good chance that pages on the active list
 * are no दीर्घer in active use.
 *
 * So when a refault distance of (R - E) is observed and there are at
 * least (R - E) active pages, the refaulting page is activated
 * optimistically in the hope that (R - E) active pages are actually
 * used less frequently than the refaulting page - or even not used at
 * all anymore.
 *
 * That means अगर inactive cache is refaulting with a suitable refault
 * distance, we assume the cache workingset is transitioning and put
 * pressure on the current active list.
 *
 * If this is wrong and demotion kicks in, the pages which are truly
 * used more frequently will be reactivated जबतक the less frequently
 * used once will be evicted from memory.
 *
 * But अगर this is right, the stale pages will be pushed out of memory
 * and the used pages get to stay in cache.
 *
 *		Refaulting active pages
 *
 * If on the other hand the refaulting pages have recently been
 * deactivated, it means that the active list is no दीर्घer protecting
 * actively used cache from reclaim. The cache is NOT transitioning to
 * a dअगरferent workingset; the existing workingset is thrashing in the
 * space allocated to the page cache.
 *
 *
 *		Implementation
 *
 * For each node's LRU lists, a counter क्रम inactive evictions and
 * activations is मुख्यtained (node->nonresident_age).
 *
 * On eviction, a snapshot of this counter (aदीर्घ with some bits to
 * identअगरy the node) is stored in the now empty page cache
 * slot of the evicted page.  This is called a shaकरोw entry.
 *
 * On cache misses क्रम which there are shaकरोw entries, an eligible
 * refault distance will immediately activate the refaulting page.
 */

#घोषणा EVICTION_SHIFT	((BITS_PER_LONG - BITS_PER_XA_VALUE) +	\
			 1 + NODES_SHIFT + MEM_CGROUP_ID_SHIFT)
#घोषणा EVICTION_MASK	(~0UL >> EVICTION_SHIFT)

/*
 * Eviction बारtamps need to be able to cover the full range of
 * actionable refaults. However, bits are tight in the xarray
 * entry, and after storing the identअगरier क्रम the lruvec there might
 * not be enough left to represent every single actionable refault. In
 * that हाल, we have to sacrअगरice granularity क्रम distance, and group
 * evictions पूर्णांकo coarser buckets by shaving off lower बारtamp bits.
 */
अटल अचिन्हित पूर्णांक bucket_order __पढ़ो_mostly;

अटल व्योम *pack_shaकरोw(पूर्णांक memcgid, pg_data_t *pgdat, अचिन्हित दीर्घ eviction,
			 bool workingset)
अणु
	eviction >>= bucket_order;
	eviction &= EVICTION_MASK;
	eviction = (eviction << MEM_CGROUP_ID_SHIFT) | memcgid;
	eviction = (eviction << NODES_SHIFT) | pgdat->node_id;
	eviction = (eviction << 1) | workingset;

	वापस xa_mk_value(eviction);
पूर्ण

अटल व्योम unpack_shaकरोw(व्योम *shaकरोw, पूर्णांक *memcgidp, pg_data_t **pgdat,
			  अचिन्हित दीर्घ *evictionp, bool *workingsetp)
अणु
	अचिन्हित दीर्घ entry = xa_to_value(shaकरोw);
	पूर्णांक memcgid, nid;
	bool workingset;

	workingset = entry & 1;
	entry >>= 1;
	nid = entry & ((1UL << NODES_SHIFT) - 1);
	entry >>= NODES_SHIFT;
	memcgid = entry & ((1UL << MEM_CGROUP_ID_SHIFT) - 1);
	entry >>= MEM_CGROUP_ID_SHIFT;

	*memcgidp = memcgid;
	*pgdat = NODE_DATA(nid);
	*evictionp = entry << bucket_order;
	*workingsetp = workingset;
पूर्ण

/**
 * workingset_age_nonresident - age non-resident entries as LRU ages
 * @lruvec: the lruvec that was aged
 * @nr_pages: the number of pages to count
 *
 * As in-memory pages are aged, non-resident pages need to be aged as
 * well, in order क्रम the refault distances later on to be comparable
 * to the in-memory dimensions. This function allows reclaim and LRU
 * operations to drive the non-resident aging aदीर्घ in parallel.
 */
व्योम workingset_age_nonresident(काष्ठा lruvec *lruvec, अचिन्हित दीर्घ nr_pages)
अणु
	/*
	 * Reclaiming a cgroup means reclaiming all its children in a
	 * round-robin fashion. That means that each cgroup has an LRU
	 * order that is composed of the LRU orders of its child
	 * cgroups; and every page has an LRU position not just in the
	 * cgroup that owns it, but in all of that group's ancestors.
	 *
	 * So when the physical inactive list of a leaf cgroup ages,
	 * the भव inactive lists of all its parents, including
	 * the root cgroup's, age as well.
	 */
	करो अणु
		atomic_दीर्घ_add(nr_pages, &lruvec->nonresident_age);
	पूर्ण जबतक ((lruvec = parent_lruvec(lruvec)));
पूर्ण

/**
 * workingset_eviction - note the eviction of a page from memory
 * @target_memcg: the cgroup that is causing the reclaim
 * @page: the page being evicted
 *
 * Returns a shaकरोw entry to be stored in @page->mapping->i_pages in place
 * of the evicted @page so that a later refault can be detected.
 */
व्योम *workingset_eviction(काष्ठा page *page, काष्ठा mem_cgroup *target_memcg)
अणु
	काष्ठा pglist_data *pgdat = page_pgdat(page);
	अचिन्हित दीर्घ eviction;
	काष्ठा lruvec *lruvec;
	पूर्णांक memcgid;

	/* Page is fully exclusive and pins page's memory cgroup poपूर्णांकer */
	VM_BUG_ON_PAGE(PageLRU(page), page);
	VM_BUG_ON_PAGE(page_count(page), page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);

	lruvec = mem_cgroup_lruvec(target_memcg, pgdat);
	/* XXX: target_memcg can be शून्य, go through lruvec */
	memcgid = mem_cgroup_id(lruvec_memcg(lruvec));
	eviction = atomic_दीर्घ_पढ़ो(&lruvec->nonresident_age);
	workingset_age_nonresident(lruvec, thp_nr_pages(page));
	वापस pack_shaकरोw(memcgid, pgdat, eviction, PageWorkingset(page));
पूर्ण

/**
 * workingset_refault - evaluate the refault of a previously evicted page
 * @page: the freshly allocated replacement page
 * @shaकरोw: shaकरोw entry of the evicted page
 *
 * Calculates and evaluates the refault distance of the previously
 * evicted page in the context of the node and the memcg whose memory
 * pressure caused the eviction.
 */
व्योम workingset_refault(काष्ठा page *page, व्योम *shaकरोw)
अणु
	bool file = page_is_file_lru(page);
	काष्ठा mem_cgroup *eviction_memcg;
	काष्ठा lruvec *eviction_lruvec;
	अचिन्हित दीर्घ refault_distance;
	अचिन्हित दीर्घ workingset_size;
	काष्ठा pglist_data *pgdat;
	काष्ठा mem_cgroup *memcg;
	अचिन्हित दीर्घ eviction;
	काष्ठा lruvec *lruvec;
	अचिन्हित दीर्घ refault;
	bool workingset;
	पूर्णांक memcgid;

	unpack_shaकरोw(shaकरोw, &memcgid, &pgdat, &eviction, &workingset);

	rcu_पढ़ो_lock();
	/*
	 * Look up the memcg associated with the stored ID. It might
	 * have been deleted since the page's eviction.
	 *
	 * Note that in rare events the ID could have been recycled
	 * क्रम a new cgroup that refaults a shared page. This is
	 * impossible to tell from the available data. However, this
	 * should be a rare and limited disturbance, and activations
	 * are always speculative anyway. Ultimately, it's the aging
	 * algorithm's job to shake out the minimum access frequency
	 * क्रम the active cache.
	 *
	 * XXX: On !CONFIG_MEMCG, this will always वापस शून्य; it
	 * would be better अगर the root_mem_cgroup existed in all
	 * configurations instead.
	 */
	eviction_memcg = mem_cgroup_from_id(memcgid);
	अगर (!mem_cgroup_disabled() && !eviction_memcg)
		जाओ out;
	eviction_lruvec = mem_cgroup_lruvec(eviction_memcg, pgdat);
	refault = atomic_दीर्घ_पढ़ो(&eviction_lruvec->nonresident_age);

	/*
	 * Calculate the refault distance
	 *
	 * The अचिन्हित subtraction here gives an accurate distance
	 * across nonresident_age overflows in most हालs. There is a
	 * special हाल: usually, shaकरोw entries have a लघु lअगरeसमय
	 * and are either refaulted or reclaimed aदीर्घ with the inode
	 * beक्रमe they get too old.  But it is not impossible क्रम the
	 * nonresident_age to lap a shaकरोw entry in the field, which
	 * can then result in a false small refault distance, leading
	 * to a false activation should this old entry actually
	 * refault again.  However, earlier kernels used to deactivate
	 * unconditionally with *every* reclaim invocation क्रम the
	 * दीर्घest समय, so the occasional inappropriate activation
	 * leading to pressure on the active list is not a problem.
	 */
	refault_distance = (refault - eviction) & EVICTION_MASK;

	/*
	 * The activation decision क्रम this page is made at the level
	 * where the eviction occurred, as that is where the LRU order
	 * during page reclaim is being determined.
	 *
	 * However, the cgroup that will own the page is the one that
	 * is actually experiencing the refault event.
	 */
	memcg = page_memcg(page);
	lruvec = mem_cgroup_lruvec(memcg, pgdat);

	inc_lruvec_state(lruvec, WORKINGSET_REFAULT_BASE + file);

	/*
	 * Compare the distance to the existing workingset size. We
	 * करोn't activate pages that couldn't stay resident even अगर
	 * all the memory was available to the workingset. Whether
	 * workingset competition needs to consider anon or not depends
	 * on having swap.
	 */
	workingset_size = lruvec_page_state(eviction_lruvec, NR_ACTIVE_खाता);
	अगर (!file) अणु
		workingset_size += lruvec_page_state(eviction_lruvec,
						     NR_INACTIVE_खाता);
	पूर्ण
	अगर (mem_cgroup_get_nr_swap_pages(memcg) > 0) अणु
		workingset_size += lruvec_page_state(eviction_lruvec,
						     NR_ACTIVE_ANON);
		अगर (file) अणु
			workingset_size += lruvec_page_state(eviction_lruvec,
						     NR_INACTIVE_ANON);
		पूर्ण
	पूर्ण
	अगर (refault_distance > workingset_size)
		जाओ out;

	SetPageActive(page);
	workingset_age_nonresident(lruvec, thp_nr_pages(page));
	inc_lruvec_state(lruvec, WORKINGSET_ACTIVATE_BASE + file);

	/* Page was active prior to eviction */
	अगर (workingset) अणु
		SetPageWorkingset(page);
		/* XXX: Move to lru_cache_add() when it supports new vs putback */
		lru_note_cost_page(page);
		inc_lruvec_state(lruvec, WORKINGSET_RESTORE_BASE + file);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * workingset_activation - note a page activation
 * @page: page that is being activated
 */
व्योम workingset_activation(काष्ठा page *page)
अणु
	काष्ठा mem_cgroup *memcg;
	काष्ठा lruvec *lruvec;

	rcu_पढ़ो_lock();
	/*
	 * Filter non-memcg pages here, e.g. unmap can call
	 * mark_page_accessed() on VDSO pages.
	 *
	 * XXX: See workingset_refault() - this should वापस
	 * root_mem_cgroup even क्रम !CONFIG_MEMCG.
	 */
	memcg = page_memcg_rcu(page);
	अगर (!mem_cgroup_disabled() && !memcg)
		जाओ out;
	lruvec = mem_cgroup_page_lruvec(page, page_pgdat(page));
	workingset_age_nonresident(lruvec, thp_nr_pages(page));
out:
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Shaकरोw entries reflect the share of the working set that करोes not
 * fit पूर्णांकo memory, so their number depends on the access pattern of
 * the workload.  In most हालs, they will refault or get reclaimed
 * aदीर्घ with the inode, but a (malicious) workload that streams
 * through files with a total size several बार that of available
 * memory, जबतक preventing the inodes from being reclaimed, can
 * create excessive amounts of shaकरोw nodes.  To keep a lid on this,
 * track shaकरोw nodes and reclaim them when they grow way past the
 * poपूर्णांक where they would still be useful.
 */

अटल काष्ठा list_lru shaकरोw_nodes;

व्योम workingset_update_node(काष्ठा xa_node *node)
अणु
	/*
	 * Track non-empty nodes that contain only shaकरोw entries;
	 * unlink those that contain pages or are being मुक्तd.
	 *
	 * Aव्योम acquiring the list_lru lock when the nodes are
	 * alपढ़ोy where they should be. The list_empty() test is safe
	 * as node->निजी_list is रक्षित by the i_pages lock.
	 */
	VM_WARN_ON_ONCE(!irqs_disabled());  /* For __inc_lruvec_page_state */

	अगर (node->count && node->count == node->nr_values) अणु
		अगर (list_empty(&node->निजी_list)) अणु
			list_lru_add(&shaकरोw_nodes, &node->निजी_list);
			__inc_lruvec_kmem_state(node, WORKINGSET_NODES);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!list_empty(&node->निजी_list)) अणु
			list_lru_del(&shaकरोw_nodes, &node->निजी_list);
			__dec_lruvec_kmem_state(node, WORKINGSET_NODES);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ count_shaकरोw_nodes(काष्ठा shrinker *shrinker,
					काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ max_nodes;
	अचिन्हित दीर्घ nodes;
	अचिन्हित दीर्घ pages;

	nodes = list_lru_shrink_count(&shaकरोw_nodes, sc);
	अगर (!nodes)
		वापस SHRINK_EMPTY;

	/*
	 * Approximate a reasonable limit क्रम the nodes
	 * containing shaकरोw entries. We करोn't need to keep more
	 * shaकरोw entries than possible pages on the active list,
	 * since refault distances bigger than that are dismissed.
	 *
	 * The size of the active list converges toward 100% of
	 * overall page cache as memory grows, with only a tiny
	 * inactive list. Assume the total cache size क्रम that.
	 *
	 * Nodes might be sparsely populated, with only one shaकरोw
	 * entry in the extreme हाल. Obviously, we cannot keep one
	 * node क्रम every eligible shaकरोw entry, so compromise on a
	 * worst-हाल density of 1/8th. Below that, not all eligible
	 * refaults can be detected anymore.
	 *
	 * On 64-bit with 7 xa_nodes per page and 64 slots
	 * each, this will reclaim shaकरोw entries when they consume
	 * ~1.8% of available memory:
	 *
	 * PAGE_SIZE / xa_nodes / node_entries * 8 / PAGE_SIZE
	 */
#अगर_घोषित CONFIG_MEMCG
	अगर (sc->memcg) अणु
		काष्ठा lruvec *lruvec;
		पूर्णांक i;

		lruvec = mem_cgroup_lruvec(sc->memcg, NODE_DATA(sc->nid));
		क्रम (pages = 0, i = 0; i < NR_LRU_LISTS; i++)
			pages += lruvec_page_state_local(lruvec,
							 NR_LRU_BASE + i);
		pages += lruvec_page_state_local(
			lruvec, NR_SLAB_RECLAIMABLE_B) >> PAGE_SHIFT;
		pages += lruvec_page_state_local(
			lruvec, NR_SLAB_UNRECLAIMABLE_B) >> PAGE_SHIFT;
	पूर्ण अन्यथा
#पूर्ण_अगर
		pages = node_present_pages(sc->nid);

	max_nodes = pages >> (XA_CHUNK_SHIFT - 3);

	अगर (nodes <= max_nodes)
		वापस 0;
	वापस nodes - max_nodes;
पूर्ण

अटल क्रमागत lru_status shaकरोw_lru_isolate(काष्ठा list_head *item,
					  काष्ठा list_lru_one *lru,
					  spinlock_t *lru_lock,
					  व्योम *arg) __must_hold(lru_lock)
अणु
	काष्ठा xa_node *node = container_of(item, काष्ठा xa_node, निजी_list);
	काष्ठा address_space *mapping;
	पूर्णांक ret;

	/*
	 * Page cache insertions and deletions synchronously मुख्यtain
	 * the shaकरोw node LRU under the i_pages lock and the
	 * lru_lock.  Because the page cache tree is emptied beक्रमe
	 * the inode can be destroyed, holding the lru_lock pins any
	 * address_space that has nodes on the LRU.
	 *
	 * We can then safely transition to the i_pages lock to
	 * pin only the address_space of the particular node we want
	 * to reclaim, take the node off-LRU, and drop the lru_lock.
	 */

	mapping = container_of(node->array, काष्ठा address_space, i_pages);

	/* Coming from the list, invert the lock order */
	अगर (!xa_trylock(&mapping->i_pages)) अणु
		spin_unlock_irq(lru_lock);
		ret = LRU_RETRY;
		जाओ out;
	पूर्ण

	list_lru_isolate(lru, item);
	__dec_lruvec_kmem_state(node, WORKINGSET_NODES);

	spin_unlock(lru_lock);

	/*
	 * The nodes should only contain one or more shaकरोw entries,
	 * no pages, so we expect to be able to हटाओ them all and
	 * delete and मुक्त the empty node afterwards.
	 */
	अगर (WARN_ON_ONCE(!node->nr_values))
		जाओ out_invalid;
	अगर (WARN_ON_ONCE(node->count != node->nr_values))
		जाओ out_invalid;
	xa_delete_node(node, workingset_update_node);
	__inc_lruvec_kmem_state(node, WORKINGSET_NODERECLAIM);

out_invalid:
	xa_unlock_irq(&mapping->i_pages);
	ret = LRU_REMOVED_RETRY;
out:
	cond_resched();
	spin_lock_irq(lru_lock);
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ scan_shaकरोw_nodes(काष्ठा shrinker *shrinker,
				       काष्ठा shrink_control *sc)
अणु
	/* list_lru lock nests inside the IRQ-safe i_pages lock */
	वापस list_lru_shrink_walk_irq(&shaकरोw_nodes, sc, shaकरोw_lru_isolate,
					शून्य);
पूर्ण

अटल काष्ठा shrinker workingset_shaकरोw_shrinker = अणु
	.count_objects = count_shaकरोw_nodes,
	.scan_objects = scan_shaकरोw_nodes,
	.seeks = 0, /* ->count reports only fully expendable nodes */
	.flags = SHRINKER_NUMA_AWARE | SHRINKER_MEMCG_AWARE,
पूर्ण;

/*
 * Our list_lru->lock is IRQ-safe as it nests inside the IRQ-safe
 * i_pages lock.
 */
अटल काष्ठा lock_class_key shaकरोw_nodes_key;

अटल पूर्णांक __init workingset_init(व्योम)
अणु
	अचिन्हित पूर्णांक बारtamp_bits;
	अचिन्हित पूर्णांक max_order;
	पूर्णांक ret;

	BUILD_BUG_ON(BITS_PER_LONG < EVICTION_SHIFT);
	/*
	 * Calculate the eviction bucket size to cover the दीर्घest
	 * actionable refault distance, which is currently half of
	 * memory (totalram_pages/2). However, memory hotplug may add
	 * some more pages at runसमय, so keep working with up to
	 * द्विगुन the initial memory by using totalram_pages as-is.
	 */
	बारtamp_bits = BITS_PER_LONG - EVICTION_SHIFT;
	max_order = fls_दीर्घ(totalram_pages() - 1);
	अगर (max_order > बारtamp_bits)
		bucket_order = max_order - बारtamp_bits;
	pr_info("workingset: timestamp_bits=%d max_order=%d bucket_order=%u\n",
	       बारtamp_bits, max_order, bucket_order);

	ret = pपुनः_स्मृति_shrinker(&workingset_shaकरोw_shrinker);
	अगर (ret)
		जाओ err;
	ret = __list_lru_init(&shaकरोw_nodes, true, &shaकरोw_nodes_key,
			      &workingset_shaकरोw_shrinker);
	अगर (ret)
		जाओ err_list_lru;
	रेजिस्टर_shrinker_prepared(&workingset_shaकरोw_shrinker);
	वापस 0;
err_list_lru:
	मुक्त_pपुनः_स्मृतिed_shrinker(&workingset_shaकरोw_shrinker);
err:
	वापस ret;
पूर्ण
module_init(workingset_init);
