<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Swap reorganised 29.12.95, Stephen Tweedie.
 *  kswapd added: 7.1.96  sct
 *  Removed kswapd_ctl limits, and swap out as many pages as needed
 *  to bring the प्रणाली back to मुक्तpages.high: 2.4.97, Rik van Riel.
 *  Zone aware kswapd started 02/00, Kanoj Sarcar (kanoj@sgi.com).
 *  Multiqueue VM started 5.8.00, Rik van Riel.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/vmpressure.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/file.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/buffer_head.h>	/* क्रम try_to_release_page(),
					buffer_heads_over_limit */
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/rmap.h>
#समावेश <linux/topology.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/compaction.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/oom.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/dax.h>
#समावेश <linux/psi.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <linux/swapops.h>
#समावेश <linux/balloon_compaction.h>

#समावेश "internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/vmscan.h>

काष्ठा scan_control अणु
	/* How many pages shrink_list() should reclaim */
	अचिन्हित दीर्घ nr_to_reclaim;

	/*
	 * Nodemask of nodes allowed by the caller. If शून्य, all nodes
	 * are scanned.
	 */
	nodemask_t	*nodemask;

	/*
	 * The memory cgroup that hit its limit and as a result is the
	 * primary target of this reclaim invocation.
	 */
	काष्ठा mem_cgroup *target_mem_cgroup;

	/*
	 * Scan pressure balancing between anon and file LRUs
	 */
	अचिन्हित दीर्घ	anon_cost;
	अचिन्हित दीर्घ	file_cost;

	/* Can active pages be deactivated as part of reclaim? */
#घोषणा DEACTIVATE_ANON 1
#घोषणा DEACTIVATE_खाता 2
	अचिन्हित पूर्णांक may_deactivate:2;
	अचिन्हित पूर्णांक क्रमce_deactivate:1;
	अचिन्हित पूर्णांक skipped_deactivate:1;

	/* Writepage batching in laptop mode; RECLAIM_WRITE */
	अचिन्हित पूर्णांक may_ग_लिखोpage:1;

	/* Can mapped pages be reclaimed? */
	अचिन्हित पूर्णांक may_unmap:1;

	/* Can pages be swapped as part of reclaim? */
	अचिन्हित पूर्णांक may_swap:1;

	/*
	 * Cgroups are not reclaimed below their configured memory.low,
	 * unless we threaten to OOM. If any cgroups are skipped due to
	 * memory.low and nothing was reclaimed, go back क्रम memory.low.
	 */
	अचिन्हित पूर्णांक memcg_low_reclaim:1;
	अचिन्हित पूर्णांक memcg_low_skipped:1;

	अचिन्हित पूर्णांक hibernation_mode:1;

	/* One of the zones is पढ़ोy क्रम compaction */
	अचिन्हित पूर्णांक compaction_पढ़ोy:1;

	/* There is easily reclaimable cold cache in the current node */
	अचिन्हित पूर्णांक cache_trim_mode:1;

	/* The file pages on the current node are dangerously low */
	अचिन्हित पूर्णांक file_is_tiny:1;

	/* Allocation order */
	s8 order;

	/* Scan (total_size >> priority) pages at once */
	s8 priority;

	/* The highest zone to isolate pages क्रम reclaim from */
	s8 reclaim_idx;

	/* This context's GFP mask */
	gfp_t gfp_mask;

	/* Incremented by the number of inactive pages that were scanned */
	अचिन्हित दीर्घ nr_scanned;

	/* Number of pages मुक्तd so far during a call to shrink_zones() */
	अचिन्हित दीर्घ nr_reclaimed;

	काष्ठा अणु
		अचिन्हित पूर्णांक dirty;
		अचिन्हित पूर्णांक unqueued_dirty;
		अचिन्हित पूर्णांक congested;
		अचिन्हित पूर्णांक ग_लिखोback;
		अचिन्हित पूर्णांक immediate;
		अचिन्हित पूर्णांक file_taken;
		अचिन्हित पूर्णांक taken;
	पूर्ण nr;

	/* क्रम recording the reclaimed slab by now */
	काष्ठा reclaim_state reclaim_state;
पूर्ण;

#अगर_घोषित ARCH_HAS_PREFETCHW
#घोषणा prefetchw_prev_lru_page(_page, _base, _field)			\
	करो अणु								\
		अगर ((_page)->lru.prev != _base) अणु			\
			काष्ठा page *prev;				\
									\
			prev = lru_to_page(&(_page->lru));		\
			prefetchw(&prev->_field);			\
		पूर्ण							\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा prefetchw_prev_lru_page(_page, _base, _field) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * From 0 .. 200.  Higher means more swappy.
 */
पूर्णांक vm_swappiness = 60;

अटल व्योम set_task_reclaim_state(काष्ठा task_काष्ठा *task,
				   काष्ठा reclaim_state *rs)
अणु
	/* Check क्रम an overग_लिखो */
	WARN_ON_ONCE(rs && task->reclaim_state);

	/* Check क्रम the nulling of an alपढ़ोy-nulled member */
	WARN_ON_ONCE(!rs && !task->reclaim_state);

	task->reclaim_state = rs;
पूर्ण

अटल LIST_HEAD(shrinker_list);
अटल DECLARE_RWSEM(shrinker_rwsem);

#अगर_घोषित CONFIG_MEMCG
अटल पूर्णांक shrinker_nr_max;

/* The shrinker_info is expanded in a batch of BITS_PER_LONG */
अटल अंतरभूत पूर्णांक shrinker_map_size(पूर्णांक nr_items)
अणु
	वापस (DIV_ROUND_UP(nr_items, BITS_PER_LONG) * माप(अचिन्हित दीर्घ));
पूर्ण

अटल अंतरभूत पूर्णांक shrinker_defer_size(पूर्णांक nr_items)
अणु
	वापस (round_up(nr_items, BITS_PER_LONG) * माप(atomic_दीर्घ_t));
पूर्ण

अटल काष्ठा shrinker_info *shrinker_info_रक्षित(काष्ठा mem_cgroup *memcg,
						     पूर्णांक nid)
अणु
	वापस rcu_dereference_रक्षित(memcg->nodeinfo[nid]->shrinker_info,
					 lockdep_is_held(&shrinker_rwsem));
पूर्ण

अटल पूर्णांक expand_one_shrinker_info(काष्ठा mem_cgroup *memcg,
				    पूर्णांक map_size, पूर्णांक defer_size,
				    पूर्णांक old_map_size, पूर्णांक old_defer_size)
अणु
	काष्ठा shrinker_info *new, *old;
	काष्ठा mem_cgroup_per_node *pn;
	पूर्णांक nid;
	पूर्णांक size = map_size + defer_size;

	क्रम_each_node(nid) अणु
		pn = memcg->nodeinfo[nid];
		old = shrinker_info_रक्षित(memcg, nid);
		/* Not yet online memcg */
		अगर (!old)
			वापस 0;

		new = kvदो_स्मृति_node(माप(*new) + size, GFP_KERNEL, nid);
		अगर (!new)
			वापस -ENOMEM;

		new->nr_deferred = (atomic_दीर्घ_t *)(new + 1);
		new->map = (व्योम *)new->nr_deferred + defer_size;

		/* map: set all old bits, clear all new bits */
		स_रखो(new->map, (पूर्णांक)0xff, old_map_size);
		स_रखो((व्योम *)new->map + old_map_size, 0, map_size - old_map_size);
		/* nr_deferred: copy old values, clear all new values */
		स_नकल(new->nr_deferred, old->nr_deferred, old_defer_size);
		स_रखो((व्योम *)new->nr_deferred + old_defer_size, 0,
		       defer_size - old_defer_size);

		rcu_assign_poपूर्णांकer(pn->shrinker_info, new);
		kvमुक्त_rcu(old, rcu);
	पूर्ण

	वापस 0;
पूर्ण

व्योम मुक्त_shrinker_info(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup_per_node *pn;
	काष्ठा shrinker_info *info;
	पूर्णांक nid;

	क्रम_each_node(nid) अणु
		pn = memcg->nodeinfo[nid];
		info = rcu_dereference_रक्षित(pn->shrinker_info, true);
		kvमुक्त(info);
		rcu_assign_poपूर्णांकer(pn->shrinker_info, शून्य);
	पूर्ण
पूर्ण

पूर्णांक alloc_shrinker_info(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा shrinker_info *info;
	पूर्णांक nid, size, ret = 0;
	पूर्णांक map_size, defer_size = 0;

	करोwn_ग_लिखो(&shrinker_rwsem);
	map_size = shrinker_map_size(shrinker_nr_max);
	defer_size = shrinker_defer_size(shrinker_nr_max);
	size = map_size + defer_size;
	क्रम_each_node(nid) अणु
		info = kvzalloc_node(माप(*info) + size, GFP_KERNEL, nid);
		अगर (!info) अणु
			मुक्त_shrinker_info(memcg);
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		info->nr_deferred = (atomic_दीर्घ_t *)(info + 1);
		info->map = (व्योम *)info->nr_deferred + defer_size;
		rcu_assign_poपूर्णांकer(memcg->nodeinfo[nid]->shrinker_info, info);
	पूर्ण
	up_ग_लिखो(&shrinker_rwsem);

	वापस ret;
पूर्ण

अटल अंतरभूत bool need_expand(पूर्णांक nr_max)
अणु
	वापस round_up(nr_max, BITS_PER_LONG) >
	       round_up(shrinker_nr_max, BITS_PER_LONG);
पूर्ण

अटल पूर्णांक expand_shrinker_info(पूर्णांक new_id)
अणु
	पूर्णांक ret = 0;
	पूर्णांक new_nr_max = new_id + 1;
	पूर्णांक map_size, defer_size = 0;
	पूर्णांक old_map_size, old_defer_size = 0;
	काष्ठा mem_cgroup *memcg;

	अगर (!need_expand(new_nr_max))
		जाओ out;

	अगर (!root_mem_cgroup)
		जाओ out;

	lockdep_निश्चित_held(&shrinker_rwsem);

	map_size = shrinker_map_size(new_nr_max);
	defer_size = shrinker_defer_size(new_nr_max);
	old_map_size = shrinker_map_size(shrinker_nr_max);
	old_defer_size = shrinker_defer_size(shrinker_nr_max);

	memcg = mem_cgroup_iter(शून्य, शून्य, शून्य);
	करो अणु
		ret = expand_one_shrinker_info(memcg, map_size, defer_size,
					       old_map_size, old_defer_size);
		अगर (ret) अणु
			mem_cgroup_iter_अवरोध(शून्य, memcg);
			जाओ out;
		पूर्ण
	पूर्ण जबतक ((memcg = mem_cgroup_iter(शून्य, memcg, शून्य)) != शून्य);
out:
	अगर (!ret)
		shrinker_nr_max = new_nr_max;

	वापस ret;
पूर्ण

व्योम set_shrinker_bit(काष्ठा mem_cgroup *memcg, पूर्णांक nid, पूर्णांक shrinker_id)
अणु
	अगर (shrinker_id >= 0 && memcg && !mem_cgroup_is_root(memcg)) अणु
		काष्ठा shrinker_info *info;

		rcu_पढ़ो_lock();
		info = rcu_dereference(memcg->nodeinfo[nid]->shrinker_info);
		/* Pairs with smp mb in shrink_slab() */
		smp_mb__beक्रमe_atomic();
		set_bit(shrinker_id, info->map);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल DEFINE_IDR(shrinker_idr);

अटल पूर्णांक pपुनः_स्मृति_memcg_shrinker(काष्ठा shrinker *shrinker)
अणु
	पूर्णांक id, ret = -ENOMEM;

	अगर (mem_cgroup_disabled())
		वापस -ENOSYS;

	करोwn_ग_लिखो(&shrinker_rwsem);
	/* This may call shrinker, so it must use करोwn_पढ़ो_trylock() */
	id = idr_alloc(&shrinker_idr, shrinker, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		जाओ unlock;

	अगर (id >= shrinker_nr_max) अणु
		अगर (expand_shrinker_info(id)) अणु
			idr_हटाओ(&shrinker_idr, id);
			जाओ unlock;
		पूर्ण
	पूर्ण
	shrinker->id = id;
	ret = 0;
unlock:
	up_ग_लिखो(&shrinker_rwsem);
	वापस ret;
पूर्ण

अटल व्योम unरेजिस्टर_memcg_shrinker(काष्ठा shrinker *shrinker)
अणु
	पूर्णांक id = shrinker->id;

	BUG_ON(id < 0);

	lockdep_निश्चित_held(&shrinker_rwsem);

	idr_हटाओ(&shrinker_idr, id);
पूर्ण

अटल दीर्घ xchg_nr_deferred_memcg(पूर्णांक nid, काष्ठा shrinker *shrinker,
				   काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा shrinker_info *info;

	info = shrinker_info_रक्षित(memcg, nid);
	वापस atomic_दीर्घ_xchg(&info->nr_deferred[shrinker->id], 0);
पूर्ण

अटल दीर्घ add_nr_deferred_memcg(दीर्घ nr, पूर्णांक nid, काष्ठा shrinker *shrinker,
				  काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा shrinker_info *info;

	info = shrinker_info_रक्षित(memcg, nid);
	वापस atomic_दीर्घ_add_वापस(nr, &info->nr_deferred[shrinker->id]);
पूर्ण

व्योम reparent_shrinker_deferred(काष्ठा mem_cgroup *memcg)
अणु
	पूर्णांक i, nid;
	दीर्घ nr;
	काष्ठा mem_cgroup *parent;
	काष्ठा shrinker_info *child_info, *parent_info;

	parent = parent_mem_cgroup(memcg);
	अगर (!parent)
		parent = root_mem_cgroup;

	/* Prevent from concurrent shrinker_info expand */
	करोwn_पढ़ो(&shrinker_rwsem);
	क्रम_each_node(nid) अणु
		child_info = shrinker_info_रक्षित(memcg, nid);
		parent_info = shrinker_info_रक्षित(parent, nid);
		क्रम (i = 0; i < shrinker_nr_max; i++) अणु
			nr = atomic_दीर्घ_पढ़ो(&child_info->nr_deferred[i]);
			atomic_दीर्घ_add(nr, &parent_info->nr_deferred[i]);
		पूर्ण
	पूर्ण
	up_पढ़ो(&shrinker_rwsem);
पूर्ण

अटल bool cgroup_reclaim(काष्ठा scan_control *sc)
अणु
	वापस sc->target_mem_cgroup;
पूर्ण

/**
 * ग_लिखोback_throttling_sane - is the usual dirty throttling mechanism available?
 * @sc: scan_control in question
 *
 * The normal page dirty throttling mechanism in balance_dirty_pages() is
 * completely broken with the legacy memcg and direct stalling in
 * shrink_page_list() is used क्रम throttling instead, which lacks all the
 * niceties such as fairness, adaptive pausing, bandwidth proportional
 * allocation and configurability.
 *
 * This function tests whether the vmscan currently in progress can assume
 * that the normal dirty throttling mechanism is operational.
 */
अटल bool ग_लिखोback_throttling_sane(काष्ठा scan_control *sc)
अणु
	अगर (!cgroup_reclaim(sc))
		वापस true;
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	अगर (cgroup_subsys_on_dfl(memory_cgrp_subsys))
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण
#अन्यथा
अटल पूर्णांक pपुनः_स्मृति_memcg_shrinker(काष्ठा shrinker *shrinker)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम unरेजिस्टर_memcg_shrinker(काष्ठा shrinker *shrinker)
अणु
पूर्ण

अटल दीर्घ xchg_nr_deferred_memcg(पूर्णांक nid, काष्ठा shrinker *shrinker,
				   काष्ठा mem_cgroup *memcg)
अणु
	वापस 0;
पूर्ण

अटल दीर्घ add_nr_deferred_memcg(दीर्घ nr, पूर्णांक nid, काष्ठा shrinker *shrinker,
				  काष्ठा mem_cgroup *memcg)
अणु
	वापस 0;
पूर्ण

अटल bool cgroup_reclaim(काष्ठा scan_control *sc)
अणु
	वापस false;
पूर्ण

अटल bool ग_लिखोback_throttling_sane(काष्ठा scan_control *sc)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल दीर्घ xchg_nr_deferred(काष्ठा shrinker *shrinker,
			     काष्ठा shrink_control *sc)
अणु
	पूर्णांक nid = sc->nid;

	अगर (!(shrinker->flags & SHRINKER_NUMA_AWARE))
		nid = 0;

	अगर (sc->memcg &&
	    (shrinker->flags & SHRINKER_MEMCG_AWARE))
		वापस xchg_nr_deferred_memcg(nid, shrinker,
					      sc->memcg);

	वापस atomic_दीर्घ_xchg(&shrinker->nr_deferred[nid], 0);
पूर्ण


अटल दीर्घ add_nr_deferred(दीर्घ nr, काष्ठा shrinker *shrinker,
			    काष्ठा shrink_control *sc)
अणु
	पूर्णांक nid = sc->nid;

	अगर (!(shrinker->flags & SHRINKER_NUMA_AWARE))
		nid = 0;

	अगर (sc->memcg &&
	    (shrinker->flags & SHRINKER_MEMCG_AWARE))
		वापस add_nr_deferred_memcg(nr, nid, shrinker,
					     sc->memcg);

	वापस atomic_दीर्घ_add_वापस(nr, &shrinker->nr_deferred[nid]);
पूर्ण

/*
 * This misses isolated pages which are not accounted क्रम to save counters.
 * As the data only determines अगर reclaim or compaction जारीs, it is
 * not expected that isolated pages will be a करोminating factor.
 */
अचिन्हित दीर्घ zone_reclaimable_pages(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ nr;

	nr = zone_page_state_snapshot(zone, NR_ZONE_INACTIVE_खाता) +
		zone_page_state_snapshot(zone, NR_ZONE_ACTIVE_खाता);
	अगर (get_nr_swap_pages() > 0)
		nr += zone_page_state_snapshot(zone, NR_ZONE_INACTIVE_ANON) +
			zone_page_state_snapshot(zone, NR_ZONE_ACTIVE_ANON);

	वापस nr;
पूर्ण

/**
 * lruvec_lru_size -  Returns the number of pages on the given LRU list.
 * @lruvec: lru vector
 * @lru: lru to use
 * @zone_idx: zones to consider (use MAX_NR_ZONES क्रम the whole LRU list)
 */
अटल अचिन्हित दीर्घ lruvec_lru_size(काष्ठा lruvec *lruvec, क्रमागत lru_list lru,
				     पूर्णांक zone_idx)
अणु
	अचिन्हित दीर्घ size = 0;
	पूर्णांक zid;

	क्रम (zid = 0; zid <= zone_idx && zid < MAX_NR_ZONES; zid++) अणु
		काष्ठा zone *zone = &lruvec_pgdat(lruvec)->node_zones[zid];

		अगर (!managed_zone(zone))
			जारी;

		अगर (!mem_cgroup_disabled())
			size += mem_cgroup_get_zone_lru_size(lruvec, lru, zid);
		अन्यथा
			size += zone_page_state(zone, NR_ZONE_LRU_BASE + lru);
	पूर्ण
	वापस size;
पूर्ण

/*
 * Add a shrinker callback to be called from the vm.
 */
पूर्णांक pपुनः_स्मृति_shrinker(काष्ठा shrinker *shrinker)
अणु
	अचिन्हित पूर्णांक size;
	पूर्णांक err;

	अगर (shrinker->flags & SHRINKER_MEMCG_AWARE) अणु
		err = pपुनः_स्मृति_memcg_shrinker(shrinker);
		अगर (err != -ENOSYS)
			वापस err;

		shrinker->flags &= ~SHRINKER_MEMCG_AWARE;
	पूर्ण

	size = माप(*shrinker->nr_deferred);
	अगर (shrinker->flags & SHRINKER_NUMA_AWARE)
		size *= nr_node_ids;

	shrinker->nr_deferred = kzalloc(size, GFP_KERNEL);
	अगर (!shrinker->nr_deferred)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम मुक्त_pपुनः_स्मृतिed_shrinker(काष्ठा shrinker *shrinker)
अणु
	अगर (shrinker->flags & SHRINKER_MEMCG_AWARE) अणु
		करोwn_ग_लिखो(&shrinker_rwsem);
		unरेजिस्टर_memcg_shrinker(shrinker);
		up_ग_लिखो(&shrinker_rwsem);
		वापस;
	पूर्ण

	kमुक्त(shrinker->nr_deferred);
	shrinker->nr_deferred = शून्य;
पूर्ण

व्योम रेजिस्टर_shrinker_prepared(काष्ठा shrinker *shrinker)
अणु
	करोwn_ग_लिखो(&shrinker_rwsem);
	list_add_tail(&shrinker->list, &shrinker_list);
	shrinker->flags |= SHRINKER_REGISTERED;
	up_ग_लिखो(&shrinker_rwsem);
पूर्ण

पूर्णांक रेजिस्टर_shrinker(काष्ठा shrinker *shrinker)
अणु
	पूर्णांक err = pपुनः_स्मृति_shrinker(shrinker);

	अगर (err)
		वापस err;
	रेजिस्टर_shrinker_prepared(shrinker);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_shrinker);

/*
 * Remove one
 */
व्योम unरेजिस्टर_shrinker(काष्ठा shrinker *shrinker)
अणु
	अगर (!(shrinker->flags & SHRINKER_REGISTERED))
		वापस;

	करोwn_ग_लिखो(&shrinker_rwsem);
	list_del(&shrinker->list);
	shrinker->flags &= ~SHRINKER_REGISTERED;
	अगर (shrinker->flags & SHRINKER_MEMCG_AWARE)
		unरेजिस्टर_memcg_shrinker(shrinker);
	up_ग_लिखो(&shrinker_rwsem);

	kमुक्त(shrinker->nr_deferred);
	shrinker->nr_deferred = शून्य;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_shrinker);

#घोषणा SHRINK_BATCH 128

अटल अचिन्हित दीर्घ करो_shrink_slab(काष्ठा shrink_control *shrinkctl,
				    काष्ठा shrinker *shrinker, पूर्णांक priority)
अणु
	अचिन्हित दीर्घ मुक्तd = 0;
	अचिन्हित दीर्घ दीर्घ delta;
	दीर्घ total_scan;
	दीर्घ मुक्तable;
	दीर्घ nr;
	दीर्घ new_nr;
	दीर्घ batch_size = shrinker->batch ? shrinker->batch
					  : SHRINK_BATCH;
	दीर्घ scanned = 0, next_deferred;

	मुक्तable = shrinker->count_objects(shrinker, shrinkctl);
	अगर (मुक्तable == 0 || मुक्तable == SHRINK_EMPTY)
		वापस मुक्तable;

	/*
	 * copy the current shrinker scan count पूर्णांकo a local variable
	 * and zero it so that other concurrent shrinker invocations
	 * करोn't also करो this scanning work.
	 */
	nr = xchg_nr_deferred(shrinker, shrinkctl);

	अगर (shrinker->seeks) अणु
		delta = मुक्तable >> priority;
		delta *= 4;
		करो_भाग(delta, shrinker->seeks);
	पूर्ण अन्यथा अणु
		/*
		 * These objects करोn't require any IO to create. Trim
		 * them aggressively under memory pressure to keep
		 * them from causing refetches in the IO caches.
		 */
		delta = मुक्तable / 2;
	पूर्ण

	total_scan = nr >> priority;
	total_scan += delta;
	total_scan = min(total_scan, (2 * मुक्तable));

	trace_mm_shrink_slab_start(shrinker, shrinkctl, nr,
				   मुक्तable, delta, total_scan, priority);

	/*
	 * Normally, we should not scan less than batch_size objects in one
	 * pass to aव्योम too frequent shrinker calls, but अगर the slab has less
	 * than batch_size objects in total and we are really tight on memory,
	 * we will try to reclaim all available objects, otherwise we can end
	 * up failing allocations although there are plenty of reclaimable
	 * objects spपढ़ो over several sद_असल with usage less than the
	 * batch_size.
	 *
	 * We detect the "tight on memory" situations by looking at the total
	 * number of objects we want to scan (total_scan). If it is greater
	 * than the total number of objects on slab (मुक्तable), we must be
	 * scanning at high prio and thereक्रमe should try to reclaim as much as
	 * possible.
	 */
	जबतक (total_scan >= batch_size ||
	       total_scan >= मुक्तable) अणु
		अचिन्हित दीर्घ ret;
		अचिन्हित दीर्घ nr_to_scan = min(batch_size, total_scan);

		shrinkctl->nr_to_scan = nr_to_scan;
		shrinkctl->nr_scanned = nr_to_scan;
		ret = shrinker->scan_objects(shrinker, shrinkctl);
		अगर (ret == SHRINK_STOP)
			अवरोध;
		मुक्तd += ret;

		count_vm_events(SLABS_SCANNED, shrinkctl->nr_scanned);
		total_scan -= shrinkctl->nr_scanned;
		scanned += shrinkctl->nr_scanned;

		cond_resched();
	पूर्ण

	/*
	 * The deferred work is increased by any new work (delta) that wasn't
	 * करोne, decreased by old deferred work that was करोne now.
	 *
	 * And it is capped to two बार of the मुक्तable items.
	 */
	next_deferred = max_t(दीर्घ, (nr + delta - scanned), 0);
	next_deferred = min(next_deferred, (2 * मुक्तable));

	/*
	 * move the unused scan count back पूर्णांकo the shrinker in a
	 * manner that handles concurrent updates.
	 */
	new_nr = add_nr_deferred(next_deferred, shrinker, shrinkctl);

	trace_mm_shrink_slab_end(shrinker, shrinkctl->nid, मुक्तd, nr, new_nr, total_scan);
	वापस मुक्तd;
पूर्ण

#अगर_घोषित CONFIG_MEMCG
अटल अचिन्हित दीर्घ shrink_slab_memcg(gfp_t gfp_mask, पूर्णांक nid,
			काष्ठा mem_cgroup *memcg, पूर्णांक priority)
अणु
	काष्ठा shrinker_info *info;
	अचिन्हित दीर्घ ret, मुक्तd = 0;
	पूर्णांक i;

	अगर (!mem_cgroup_online(memcg))
		वापस 0;

	अगर (!करोwn_पढ़ो_trylock(&shrinker_rwsem))
		वापस 0;

	info = shrinker_info_रक्षित(memcg, nid);
	अगर (unlikely(!info))
		जाओ unlock;

	क्रम_each_set_bit(i, info->map, shrinker_nr_max) अणु
		काष्ठा shrink_control sc = अणु
			.gfp_mask = gfp_mask,
			.nid = nid,
			.memcg = memcg,
		पूर्ण;
		काष्ठा shrinker *shrinker;

		shrinker = idr_find(&shrinker_idr, i);
		अगर (unlikely(!shrinker || !(shrinker->flags & SHRINKER_REGISTERED))) अणु
			अगर (!shrinker)
				clear_bit(i, info->map);
			जारी;
		पूर्ण

		/* Call non-slab shrinkers even though kmem is disabled */
		अगर (!memcg_kmem_enabled() &&
		    !(shrinker->flags & SHRINKER_NONSLAB))
			जारी;

		ret = करो_shrink_slab(&sc, shrinker, priority);
		अगर (ret == SHRINK_EMPTY) अणु
			clear_bit(i, info->map);
			/*
			 * After the shrinker reported that it had no objects to
			 * मुक्त, but beक्रमe we cleared the corresponding bit in
			 * the memcg shrinker map, a new object might have been
			 * added. To make sure, we have the bit set in this
			 * हाल, we invoke the shrinker one more समय and reset
			 * the bit अगर it reports that it is not empty anymore.
			 * The memory barrier here pairs with the barrier in
			 * set_shrinker_bit():
			 *
			 * list_lru_add()     shrink_slab_memcg()
			 *   list_add_tail()    clear_bit()
			 *   <MB>               <MB>
			 *   set_bit()          करो_shrink_slab()
			 */
			smp_mb__after_atomic();
			ret = करो_shrink_slab(&sc, shrinker, priority);
			अगर (ret == SHRINK_EMPTY)
				ret = 0;
			अन्यथा
				set_shrinker_bit(memcg, nid, i);
		पूर्ण
		मुक्तd += ret;

		अगर (rwsem_is_contended(&shrinker_rwsem)) अणु
			मुक्तd = मुक्तd ? : 1;
			अवरोध;
		पूर्ण
	पूर्ण
unlock:
	up_पढ़ो(&shrinker_rwsem);
	वापस मुक्तd;
पूर्ण
#अन्यथा /* CONFIG_MEMCG */
अटल अचिन्हित दीर्घ shrink_slab_memcg(gfp_t gfp_mask, पूर्णांक nid,
			काष्ठा mem_cgroup *memcg, पूर्णांक priority)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG */

/**
 * shrink_slab - shrink slab caches
 * @gfp_mask: allocation context
 * @nid: node whose slab caches to target
 * @memcg: memory cgroup whose slab caches to target
 * @priority: the reclaim priority
 *
 * Call the shrink functions to age shrinkable caches.
 *
 * @nid is passed aदीर्घ to shrinkers with SHRINKER_NUMA_AWARE set,
 * unaware shrinkers will receive a node id of 0 instead.
 *
 * @memcg specअगरies the memory cgroup to target. Unaware shrinkers
 * are called only अगर it is the root cgroup.
 *
 * @priority is sc->priority, we take the number of objects and >> by priority
 * in order to get the scan target.
 *
 * Returns the number of reclaimed slab objects.
 */
अटल अचिन्हित दीर्घ shrink_slab(gfp_t gfp_mask, पूर्णांक nid,
				 काष्ठा mem_cgroup *memcg,
				 पूर्णांक priority)
अणु
	अचिन्हित दीर्घ ret, मुक्तd = 0;
	काष्ठा shrinker *shrinker;

	/*
	 * The root memcg might be allocated even though memcg is disabled
	 * via "cgroup_disable=memory" boot parameter.  This could make
	 * mem_cgroup_is_root() वापस false, then just run memcg slab
	 * shrink, but skip global shrink.  This may result in premature
	 * oom.
	 */
	अगर (!mem_cgroup_disabled() && !mem_cgroup_is_root(memcg))
		वापस shrink_slab_memcg(gfp_mask, nid, memcg, priority);

	अगर (!करोwn_पढ़ो_trylock(&shrinker_rwsem))
		जाओ out;

	list_क्रम_each_entry(shrinker, &shrinker_list, list) अणु
		काष्ठा shrink_control sc = अणु
			.gfp_mask = gfp_mask,
			.nid = nid,
			.memcg = memcg,
		पूर्ण;

		ret = करो_shrink_slab(&sc, shrinker, priority);
		अगर (ret == SHRINK_EMPTY)
			ret = 0;
		मुक्तd += ret;
		/*
		 * Bail out अगर someone want to रेजिस्टर a new shrinker to
		 * prevent the registration from being stalled क्रम दीर्घ periods
		 * by parallel ongoing shrinking.
		 */
		अगर (rwsem_is_contended(&shrinker_rwsem)) अणु
			मुक्तd = मुक्तd ? : 1;
			अवरोध;
		पूर्ण
	पूर्ण

	up_पढ़ो(&shrinker_rwsem);
out:
	cond_resched();
	वापस मुक्तd;
पूर्ण

व्योम drop_slab_node(पूर्णांक nid)
अणु
	अचिन्हित दीर्घ मुक्तd;

	करो अणु
		काष्ठा mem_cgroup *memcg = शून्य;

		अगर (fatal_संकेत_pending(current))
			वापस;

		मुक्तd = 0;
		memcg = mem_cgroup_iter(शून्य, शून्य, शून्य);
		करो अणु
			मुक्तd += shrink_slab(GFP_KERNEL, nid, memcg, 0);
		पूर्ण जबतक ((memcg = mem_cgroup_iter(शून्य, memcg, शून्य)) != शून्य);
	पूर्ण जबतक (मुक्तd > 10);
पूर्ण

व्योम drop_slab(व्योम)
अणु
	पूर्णांक nid;

	क्रम_each_online_node(nid)
		drop_slab_node(nid);
पूर्ण

अटल अंतरभूत पूर्णांक is_page_cache_मुक्तable(काष्ठा page *page)
अणु
	/*
	 * A मुक्तable page cache page is referenced only by the caller
	 * that isolated the page, the page cache and optional buffer
	 * heads at page->निजी.
	 */
	पूर्णांक page_cache_pins = thp_nr_pages(page);
	वापस page_count(page) - page_has_निजी(page) == 1 + page_cache_pins;
पूर्ण

अटल पूर्णांक may_ग_लिखो_to_inode(काष्ठा inode *inode)
अणु
	अगर (current->flags & PF_SWAPWRITE)
		वापस 1;
	अगर (!inode_ग_लिखो_congested(inode))
		वापस 1;
	अगर (inode_to_bdi(inode) == current->backing_dev_info)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * We detected a synchronous ग_लिखो error writing a page out.  Probably
 * -ENOSPC.  We need to propagate that पूर्णांकo the address_space क्रम a subsequent
 * fsync(), msync() or बंद().
 *
 * The tricky part is that after ग_लिखोpage we cannot touch the mapping: nothing
 * prevents it from being मुक्तd up.  But we have a ref on the page and once
 * that page is locked, the mapping is pinned.
 *
 * We're allowed to run sleeping lock_page() here because we know the caller has
 * __GFP_FS.
 */
अटल व्योम handle_ग_लिखो_error(काष्ठा address_space *mapping,
				काष्ठा page *page, पूर्णांक error)
अणु
	lock_page(page);
	अगर (page_mapping(page) == mapping)
		mapping_set_error(mapping, error);
	unlock_page(page);
पूर्ण

/* possible outcome of pageout() */
प्रकार क्रमागत अणु
	/* failed to ग_लिखो page out, page is locked */
	PAGE_KEEP,
	/* move page to the active list, page is locked */
	PAGE_ACTIVATE,
	/* page has been sent to the disk successfully, page is unlocked */
	PAGE_SUCCESS,
	/* page is clean and locked */
	PAGE_CLEAN,
पूर्ण pageout_t;

/*
 * pageout is called by shrink_page_list() क्रम each dirty page.
 * Calls ->ग_लिखोpage().
 */
अटल pageout_t pageout(काष्ठा page *page, काष्ठा address_space *mapping)
अणु
	/*
	 * If the page is dirty, only perक्रमm ग_लिखोback अगर that ग_लिखो
	 * will be non-blocking.  To prevent this allocation from being
	 * stalled by pagecache activity.  But note that there may be
	 * stalls अगर we need to run get_block().  We could test
	 * PagePrivate क्रम that.
	 *
	 * If this process is currently in __generic_file_ग_लिखो_iter() against
	 * this page's queue, we can perक्रमm ग_लिखोback even अगर that
	 * will block.
	 *
	 * If the page is swapcache, ग_लिखो it back even अगर that would
	 * block, क्रम some throttling. This happens by accident, because
	 * swap_backing_dev_info is bust: it करोesn't reflect the
	 * congestion state of the swapdevs.  Easy to fix, अगर needed.
	 */
	अगर (!is_page_cache_मुक्तable(page))
		वापस PAGE_KEEP;
	अगर (!mapping) अणु
		/*
		 * Some data journaling orphaned pages can have
		 * page->mapping == शून्य जबतक being dirty with clean buffers.
		 */
		अगर (page_has_निजी(page)) अणु
			अगर (try_to_मुक्त_buffers(page)) अणु
				ClearPageDirty(page);
				pr_info("%s: orphaned page\n", __func__);
				वापस PAGE_CLEAN;
			पूर्ण
		पूर्ण
		वापस PAGE_KEEP;
	पूर्ण
	अगर (mapping->a_ops->ग_लिखोpage == शून्य)
		वापस PAGE_ACTIVATE;
	अगर (!may_ग_लिखो_to_inode(mapping->host))
		वापस PAGE_KEEP;

	अगर (clear_page_dirty_क्रम_io(page)) अणु
		पूर्णांक res;
		काष्ठा ग_लिखोback_control wbc = अणु
			.sync_mode = WB_SYNC_NONE,
			.nr_to_ग_लिखो = SWAP_CLUSTER_MAX,
			.range_start = 0,
			.range_end = Lदीर्घ_उच्च,
			.क्रम_reclaim = 1,
		पूर्ण;

		SetPageReclaim(page);
		res = mapping->a_ops->ग_लिखोpage(page, &wbc);
		अगर (res < 0)
			handle_ग_लिखो_error(mapping, page, res);
		अगर (res == AOP_WRITEPAGE_ACTIVATE) अणु
			ClearPageReclaim(page);
			वापस PAGE_ACTIVATE;
		पूर्ण

		अगर (!PageWriteback(page)) अणु
			/* synchronous ग_लिखो or broken a_ops? */
			ClearPageReclaim(page);
		पूर्ण
		trace_mm_vmscan_ग_लिखोpage(page);
		inc_node_page_state(page, NR_VMSCAN_WRITE);
		वापस PAGE_SUCCESS;
	पूर्ण

	वापस PAGE_CLEAN;
पूर्ण

/*
 * Same as हटाओ_mapping, but अगर the page is हटाओd from the mapping, it
 * माला_लो वापसed with a refcount of 0.
 */
अटल पूर्णांक __हटाओ_mapping(काष्ठा address_space *mapping, काष्ठा page *page,
			    bool reclaimed, काष्ठा mem_cgroup *target_memcg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक refcount;
	व्योम *shaकरोw = शून्य;

	BUG_ON(!PageLocked(page));
	BUG_ON(mapping != page_mapping(page));

	xa_lock_irqsave(&mapping->i_pages, flags);
	/*
	 * The non racy check क्रम a busy page.
	 *
	 * Must be careful with the order of the tests. When someone has
	 * a ref to the page, it may be possible that they dirty it then
	 * drop the reference. So अगर PageDirty is tested beक्रमe page_count
	 * here, then the following race may occur:
	 *
	 * get_user_pages(&page);
	 * [user mapping goes away]
	 * ग_लिखो_to(page);
	 *				!PageDirty(page)    [good]
	 * SetPageDirty(page);
	 * put_page(page);
	 *				!page_count(page)   [good, discard it]
	 *
	 * [oops, our ग_लिखो_to data is lost]
	 *
	 * Reversing the order of the tests ensures such a situation cannot
	 * escape unnoticed. The smp_rmb is needed to ensure the page->flags
	 * load is not satisfied beक्रमe that of page->_refcount.
	 *
	 * Note that अगर SetPageDirty is always perक्रमmed via set_page_dirty,
	 * and thus under the i_pages lock, then this ordering is not required.
	 */
	refcount = 1 + compound_nr(page);
	अगर (!page_ref_मुक्तze(page, refcount))
		जाओ cannot_मुक्त;
	/* note: atomic_cmpxchg in page_ref_मुक्तze provides the smp_rmb */
	अगर (unlikely(PageDirty(page))) अणु
		page_ref_unमुक्तze(page, refcount);
		जाओ cannot_मुक्त;
	पूर्ण

	अगर (PageSwapCache(page)) अणु
		swp_entry_t swap = अणु .val = page_निजी(page) पूर्ण;
		mem_cgroup_swapout(page, swap);
		अगर (reclaimed && !mapping_निकासing(mapping))
			shaकरोw = workingset_eviction(page, target_memcg);
		__delete_from_swap_cache(page, swap, shaकरोw);
		xa_unlock_irqrestore(&mapping->i_pages, flags);
		put_swap_page(page, swap);
	पूर्ण अन्यथा अणु
		व्योम (*मुक्तpage)(काष्ठा page *);

		मुक्तpage = mapping->a_ops->मुक्तpage;
		/*
		 * Remember a shaकरोw entry क्रम reclaimed file cache in
		 * order to detect refaults, thus thrashing, later on.
		 *
		 * But करोn't store shaकरोws in an address space that is
		 * alपढ़ोy निकासing.  This is not just an optimization,
		 * inode reclaim needs to empty out the radix tree or
		 * the nodes are lost.  Don't plant shaकरोws behind its
		 * back.
		 *
		 * We also करोn't store shaकरोws क्रम DAX mappings because the
		 * only page cache pages found in these are zero pages
		 * covering holes, and because we करोn't want to mix DAX
		 * exceptional entries and shaकरोw exceptional entries in the
		 * same address_space.
		 */
		अगर (reclaimed && page_is_file_lru(page) &&
		    !mapping_निकासing(mapping) && !dax_mapping(mapping))
			shaकरोw = workingset_eviction(page, target_memcg);
		__delete_from_page_cache(page, shaकरोw);
		xa_unlock_irqrestore(&mapping->i_pages, flags);

		अगर (मुक्तpage != शून्य)
			मुक्तpage(page);
	पूर्ण

	वापस 1;

cannot_मुक्त:
	xa_unlock_irqrestore(&mapping->i_pages, flags);
	वापस 0;
पूर्ण

/*
 * Attempt to detach a locked page from its ->mapping.  If it is dirty or अगर
 * someone अन्यथा has a ref on the page, पात and वापस 0.  If it was
 * successfully detached, वापस 1.  Assumes the caller has a single ref on
 * this page.
 */
पूर्णांक हटाओ_mapping(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	अगर (__हटाओ_mapping(mapping, page, false, शून्य)) अणु
		/*
		 * Unमुक्तzing the refcount with 1 rather than 2 effectively
		 * drops the pagecache ref क्रम us without requiring another
		 * atomic operation.
		 */
		page_ref_unमुक्तze(page, 1);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * putback_lru_page - put previously isolated page onto appropriate LRU list
 * @page: page to be put back to appropriate lru list
 *
 * Add previously isolated @page to appropriate LRU list.
 * Page may still be unevictable क्रम other reasons.
 *
 * lru_lock must not be held, पूर्णांकerrupts must be enabled.
 */
व्योम putback_lru_page(काष्ठा page *page)
अणु
	lru_cache_add(page);
	put_page(page);		/* drop ref from isolate */
पूर्ण

क्रमागत page_references अणु
	PAGEREF_RECLAIM,
	PAGEREF_RECLAIM_CLEAN,
	PAGEREF_KEEP,
	PAGEREF_ACTIVATE,
पूर्ण;

अटल क्रमागत page_references page_check_references(काष्ठा page *page,
						  काष्ठा scan_control *sc)
अणु
	पूर्णांक referenced_ptes, referenced_page;
	अचिन्हित दीर्घ vm_flags;

	referenced_ptes = page_referenced(page, 1, sc->target_mem_cgroup,
					  &vm_flags);
	referenced_page = TestClearPageReferenced(page);

	/*
	 * Mlock lost the isolation race with us.  Let try_to_unmap()
	 * move the page to the unevictable list.
	 */
	अगर (vm_flags & VM_LOCKED)
		वापस PAGEREF_RECLAIM;

	अगर (referenced_ptes) अणु
		/*
		 * All mapped pages start out with page table
		 * references from the instantiating fault, so we need
		 * to look twice अगर a mapped file page is used more
		 * than once.
		 *
		 * Mark it and spare it क्रम another trip around the
		 * inactive list.  Another page table reference will
		 * lead to its activation.
		 *
		 * Note: the mark is set क्रम activated pages as well
		 * so that recently deactivated but used pages are
		 * quickly recovered.
		 */
		SetPageReferenced(page);

		अगर (referenced_page || referenced_ptes > 1)
			वापस PAGEREF_ACTIVATE;

		/*
		 * Activate file-backed executable pages after first usage.
		 */
		अगर ((vm_flags & VM_EXEC) && !PageSwapBacked(page))
			वापस PAGEREF_ACTIVATE;

		वापस PAGEREF_KEEP;
	पूर्ण

	/* Reclaim अगर clean, defer dirty pages to ग_लिखोback */
	अगर (referenced_page && !PageSwapBacked(page))
		वापस PAGEREF_RECLAIM_CLEAN;

	वापस PAGEREF_RECLAIM;
पूर्ण

/* Check अगर a page is dirty or under ग_लिखोback */
अटल व्योम page_check_dirty_ग_लिखोback(काष्ठा page *page,
				       bool *dirty, bool *ग_लिखोback)
अणु
	काष्ठा address_space *mapping;

	/*
	 * Anonymous pages are not handled by flushers and must be written
	 * from reclaim context. Do not stall reclaim based on them
	 */
	अगर (!page_is_file_lru(page) ||
	    (PageAnon(page) && !PageSwapBacked(page))) अणु
		*dirty = false;
		*ग_लिखोback = false;
		वापस;
	पूर्ण

	/* By शेष assume that the page flags are accurate */
	*dirty = PageDirty(page);
	*ग_लिखोback = PageWriteback(page);

	/* Verअगरy dirty/ग_लिखोback state अगर the fileप्रणाली supports it */
	अगर (!page_has_निजी(page))
		वापस;

	mapping = page_mapping(page);
	अगर (mapping && mapping->a_ops->is_dirty_ग_लिखोback)
		mapping->a_ops->is_dirty_ग_लिखोback(page, dirty, ग_लिखोback);
पूर्ण

/*
 * shrink_page_list() वापसs the number of reclaimed pages
 */
अटल अचिन्हित पूर्णांक shrink_page_list(काष्ठा list_head *page_list,
				     काष्ठा pglist_data *pgdat,
				     काष्ठा scan_control *sc,
				     काष्ठा reclaim_stat *stat,
				     bool ignore_references)
अणु
	LIST_HEAD(ret_pages);
	LIST_HEAD(मुक्त_pages);
	अचिन्हित पूर्णांक nr_reclaimed = 0;
	अचिन्हित पूर्णांक pgactivate = 0;

	स_रखो(stat, 0, माप(*stat));
	cond_resched();

	जबतक (!list_empty(page_list)) अणु
		काष्ठा address_space *mapping;
		काष्ठा page *page;
		क्रमागत page_references references = PAGEREF_RECLAIM;
		bool dirty, ग_लिखोback, may_enter_fs;
		अचिन्हित पूर्णांक nr_pages;

		cond_resched();

		page = lru_to_page(page_list);
		list_del(&page->lru);

		अगर (!trylock_page(page))
			जाओ keep;

		VM_BUG_ON_PAGE(PageActive(page), page);

		nr_pages = compound_nr(page);

		/* Account the number of base pages even though THP */
		sc->nr_scanned += nr_pages;

		अगर (unlikely(!page_evictable(page)))
			जाओ activate_locked;

		अगर (!sc->may_unmap && page_mapped(page))
			जाओ keep_locked;

		may_enter_fs = (sc->gfp_mask & __GFP_FS) ||
			(PageSwapCache(page) && (sc->gfp_mask & __GFP_IO));

		/*
		 * The number of dirty pages determines अगर a node is marked
		 * reclaim_congested which affects रुको_अगरf_congested. kswapd
		 * will stall and start writing pages अगर the tail of the LRU
		 * is all dirty unqueued pages.
		 */
		page_check_dirty_ग_लिखोback(page, &dirty, &ग_लिखोback);
		अगर (dirty || ग_लिखोback)
			stat->nr_dirty++;

		अगर (dirty && !ग_लिखोback)
			stat->nr_unqueued_dirty++;

		/*
		 * Treat this page as congested अगर the underlying BDI is or अगर
		 * pages are cycling through the LRU so quickly that the
		 * pages marked क्रम immediate reclaim are making it to the
		 * end of the LRU a second समय.
		 */
		mapping = page_mapping(page);
		अगर (((dirty || ग_लिखोback) && mapping &&
		     inode_ग_लिखो_congested(mapping->host)) ||
		    (ग_लिखोback && PageReclaim(page)))
			stat->nr_congested++;

		/*
		 * If a page at the tail of the LRU is under ग_लिखोback, there
		 * are three हालs to consider.
		 *
		 * 1) If reclaim is encountering an excessive number of pages
		 *    under ग_लिखोback and this page is both under ग_लिखोback and
		 *    PageReclaim then it indicates that pages are being queued
		 *    क्रम IO but are being recycled through the LRU beक्रमe the
		 *    IO can complete. Waiting on the page itself risks an
		 *    indefinite stall अगर it is impossible to ग_लिखोback the
		 *    page due to IO error or disconnected storage so instead
		 *    note that the LRU is being scanned too quickly and the
		 *    caller can stall after page list has been processed.
		 *
		 * 2) Global or new memcg reclaim encounters a page that is
		 *    not marked क्रम immediate reclaim, or the caller करोes not
		 *    have __GFP_FS (or __GFP_IO अगर it's simply going to swap,
		 *    not to fs). In this हाल mark the page क्रम immediate
		 *    reclaim and जारी scanning.
		 *
		 *    Require may_enter_fs because we would रुको on fs, which
		 *    may not have submitted IO yet. And the loop driver might
		 *    enter reclaim, and deadlock अगर it रुकोs on a page क्रम
		 *    which it is needed to करो the ग_लिखो (loop masks off
		 *    __GFP_IO|__GFP_FS क्रम this reason); but more thought
		 *    would probably show more reasons.
		 *
		 * 3) Legacy memcg encounters a page that is alपढ़ोy marked
		 *    PageReclaim. memcg करोes not have any dirty pages
		 *    throttling so we could easily OOM just because too many
		 *    pages are in ग_लिखोback and there is nothing अन्यथा to
		 *    reclaim. Wait क्रम the ग_लिखोback to complete.
		 *
		 * In हालs 1) and 2) we activate the pages to get them out of
		 * the way जबतक we जारी scanning क्रम clean pages on the
		 * inactive list and refilling from the active list. The
		 * observation here is that रुकोing क्रम disk ग_लिखोs is more
		 * expensive than potentially causing reloads करोwn the line.
		 * Since they're marked for immediate reclaim, they won't put
		 * memory pressure on the cache working set any दीर्घer than it
		 * takes to ग_लिखो them to disk.
		 */
		अगर (PageWriteback(page)) अणु
			/* Case 1 above */
			अगर (current_is_kswapd() &&
			    PageReclaim(page) &&
			    test_bit(PGDAT_WRITEBACK, &pgdat->flags)) अणु
				stat->nr_immediate++;
				जाओ activate_locked;

			/* Case 2 above */
			पूर्ण अन्यथा अगर (ग_लिखोback_throttling_sane(sc) ||
			    !PageReclaim(page) || !may_enter_fs) अणु
				/*
				 * This is slightly racy - end_page_ग_लिखोback()
				 * might have just cleared PageReclaim, then
				 * setting PageReclaim here end up पूर्णांकerpreted
				 * as PageReadahead - but that करोes not matter
				 * enough to care.  What we करो want is क्रम this
				 * page to have PageReclaim set next समय memcg
				 * reclaim reaches the tests above, so it will
				 * then रुको_on_page_ग_लिखोback() to aव्योम OOM;
				 * and it's also appropriate in global reclaim.
				 */
				SetPageReclaim(page);
				stat->nr_ग_लिखोback++;
				जाओ activate_locked;

			/* Case 3 above */
			पूर्ण अन्यथा अणु
				unlock_page(page);
				रुको_on_page_ग_लिखोback(page);
				/* then go back and try same page again */
				list_add_tail(&page->lru, page_list);
				जारी;
			पूर्ण
		पूर्ण

		अगर (!ignore_references)
			references = page_check_references(page, sc);

		चयन (references) अणु
		हाल PAGEREF_ACTIVATE:
			जाओ activate_locked;
		हाल PAGEREF_KEEP:
			stat->nr_ref_keep += nr_pages;
			जाओ keep_locked;
		हाल PAGEREF_RECLAIM:
		हाल PAGEREF_RECLAIM_CLEAN:
			; /* try to reclaim the page below */
		पूर्ण

		/*
		 * Anonymous process memory has backing store?
		 * Try to allocate it some swap space here.
		 * Lazyमुक्त page could be मुक्तd directly
		 */
		अगर (PageAnon(page) && PageSwapBacked(page)) अणु
			अगर (!PageSwapCache(page)) अणु
				अगर (!(sc->gfp_mask & __GFP_IO))
					जाओ keep_locked;
				अगर (page_maybe_dma_pinned(page))
					जाओ keep_locked;
				अगर (PageTransHuge(page)) अणु
					/* cannot split THP, skip it */
					अगर (!can_split_huge_page(page, शून्य))
						जाओ activate_locked;
					/*
					 * Split pages without a PMD map right
					 * away. Chances are some or all of the
					 * tail pages can be मुक्तd without IO.
					 */
					अगर (!compound_mapcount(page) &&
					    split_huge_page_to_list(page,
								    page_list))
						जाओ activate_locked;
				पूर्ण
				अगर (!add_to_swap(page)) अणु
					अगर (!PageTransHuge(page))
						जाओ activate_locked_split;
					/* Fallback to swap normal pages */
					अगर (split_huge_page_to_list(page,
								    page_list))
						जाओ activate_locked;
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
					count_vm_event(THP_SWPOUT_FALLBACK);
#पूर्ण_अगर
					अगर (!add_to_swap(page))
						जाओ activate_locked_split;
				पूर्ण

				may_enter_fs = true;

				/* Adding to swap updated mapping */
				mapping = page_mapping(page);
			पूर्ण
		पूर्ण अन्यथा अगर (unlikely(PageTransHuge(page))) अणु
			/* Split file THP */
			अगर (split_huge_page_to_list(page, page_list))
				जाओ keep_locked;
		पूर्ण

		/*
		 * THP may get split above, need minus tail pages and update
		 * nr_pages to aव्योम accounting tail pages twice.
		 *
		 * The tail pages that are added पूर्णांकo swap cache successfully
		 * reach here.
		 */
		अगर ((nr_pages > 1) && !PageTransHuge(page)) अणु
			sc->nr_scanned -= (nr_pages - 1);
			nr_pages = 1;
		पूर्ण

		/*
		 * The page is mapped पूर्णांकo the page tables of one or more
		 * processes. Try to unmap it here.
		 */
		अगर (page_mapped(page)) अणु
			क्रमागत ttu_flags flags = TTU_BATCH_FLUSH;
			bool was_swapbacked = PageSwapBacked(page);

			अगर (unlikely(PageTransHuge(page)))
				flags |= TTU_SPLIT_HUGE_PMD;

			अगर (!try_to_unmap(page, flags)) अणु
				stat->nr_unmap_fail += nr_pages;
				अगर (!was_swapbacked && PageSwapBacked(page))
					stat->nr_lazyमुक्त_fail += nr_pages;
				जाओ activate_locked;
			पूर्ण
		पूर्ण

		अगर (PageDirty(page)) अणु
			/*
			 * Only kswapd can ग_लिखोback fileप्रणाली pages
			 * to aव्योम risk of stack overflow. But aव्योम
			 * injecting inefficient single-page IO पूर्णांकo
			 * flusher ग_लिखोback as much as possible: only
			 * ग_लिखो pages when we've encountered many
			 * dirty pages, and when we've alपढ़ोy scanned
			 * the rest of the LRU क्रम clean pages and see
			 * the same dirty pages again (PageReclaim).
			 */
			अगर (page_is_file_lru(page) &&
			    (!current_is_kswapd() || !PageReclaim(page) ||
			     !test_bit(PGDAT_सूचीTY, &pgdat->flags))) अणु
				/*
				 * Immediately reclaim when written back.
				 * Similar in principal to deactivate_page()
				 * except we alपढ़ोy have the page isolated
				 * and know it's dirty
				 */
				inc_node_page_state(page, NR_VMSCAN_IMMEDIATE);
				SetPageReclaim(page);

				जाओ activate_locked;
			पूर्ण

			अगर (references == PAGEREF_RECLAIM_CLEAN)
				जाओ keep_locked;
			अगर (!may_enter_fs)
				जाओ keep_locked;
			अगर (!sc->may_ग_लिखोpage)
				जाओ keep_locked;

			/*
			 * Page is dirty. Flush the TLB अगर a writable entry
			 * potentially exists to aव्योम CPU ग_लिखोs after IO
			 * starts and then ग_लिखो it out here.
			 */
			try_to_unmap_flush_dirty();
			चयन (pageout(page, mapping)) अणु
			हाल PAGE_KEEP:
				जाओ keep_locked;
			हाल PAGE_ACTIVATE:
				जाओ activate_locked;
			हाल PAGE_SUCCESS:
				stat->nr_pageout += thp_nr_pages(page);

				अगर (PageWriteback(page))
					जाओ keep;
				अगर (PageDirty(page))
					जाओ keep;

				/*
				 * A synchronous ग_लिखो - probably a ramdisk.  Go
				 * ahead and try to reclaim the page.
				 */
				अगर (!trylock_page(page))
					जाओ keep;
				अगर (PageDirty(page) || PageWriteback(page))
					जाओ keep_locked;
				mapping = page_mapping(page);
				fallthrough;
			हाल PAGE_CLEAN:
				; /* try to मुक्त the page below */
			पूर्ण
		पूर्ण

		/*
		 * If the page has buffers, try to मुक्त the buffer mappings
		 * associated with this page. If we succeed we try to मुक्त
		 * the page as well.
		 *
		 * We करो this even अगर the page is PageDirty().
		 * try_to_release_page() करोes not perक्रमm I/O, but it is
		 * possible क्रम a page to have PageDirty set, but it is actually
		 * clean (all its buffers are clean).  This happens अगर the
		 * buffers were written out directly, with submit_bh(). ext3
		 * will करो this, as well as the blockdev mapping.
		 * try_to_release_page() will discover that cleanness and will
		 * drop the buffers and mark the page clean - it can be मुक्तd.
		 *
		 * Rarely, pages can have buffers and no ->mapping.  These are
		 * the pages which were not successfully invalidated in
		 * truncate_cleanup_page().  We try to drop those buffers here
		 * and अगर that worked, and the page is no दीर्घer mapped पूर्णांकo
		 * process address space (page_count == 1) it can be मुक्तd.
		 * Otherwise, leave the page on the LRU so it is swappable.
		 */
		अगर (page_has_निजी(page)) अणु
			अगर (!try_to_release_page(page, sc->gfp_mask))
				जाओ activate_locked;
			अगर (!mapping && page_count(page) == 1) अणु
				unlock_page(page);
				अगर (put_page_testzero(page))
					जाओ मुक्त_it;
				अन्यथा अणु
					/*
					 * rare race with speculative reference.
					 * the speculative reference will मुक्त
					 * this page लघुly, so we may
					 * increment nr_reclaimed here (and
					 * leave it off the LRU).
					 */
					nr_reclaimed++;
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (PageAnon(page) && !PageSwapBacked(page)) अणु
			/* follow __हटाओ_mapping क्रम reference */
			अगर (!page_ref_मुक्तze(page, 1))
				जाओ keep_locked;
			अगर (PageDirty(page)) अणु
				page_ref_unमुक्तze(page, 1);
				जाओ keep_locked;
			पूर्ण

			count_vm_event(PGLAZYFREED);
			count_memcg_page_event(page, PGLAZYFREED);
		पूर्ण अन्यथा अगर (!mapping || !__हटाओ_mapping(mapping, page, true,
							 sc->target_mem_cgroup))
			जाओ keep_locked;

		unlock_page(page);
मुक्त_it:
		/*
		 * THP may get swapped out in a whole, need account
		 * all base pages.
		 */
		nr_reclaimed += nr_pages;

		/*
		 * Is there need to periodically मुक्त_page_list? It would
		 * appear not as the counts should be low
		 */
		अगर (unlikely(PageTransHuge(page)))
			destroy_compound_page(page);
		अन्यथा
			list_add(&page->lru, &मुक्त_pages);
		जारी;

activate_locked_split:
		/*
		 * The tail pages that are failed to add पूर्णांकo swap cache
		 * reach here.  Fixup nr_scanned and nr_pages.
		 */
		अगर (nr_pages > 1) अणु
			sc->nr_scanned -= (nr_pages - 1);
			nr_pages = 1;
		पूर्ण
activate_locked:
		/* Not a candidate क्रम swapping, so reclaim swap space. */
		अगर (PageSwapCache(page) && (mem_cgroup_swap_full(page) ||
						PageMlocked(page)))
			try_to_मुक्त_swap(page);
		VM_BUG_ON_PAGE(PageActive(page), page);
		अगर (!PageMlocked(page)) अणु
			पूर्णांक type = page_is_file_lru(page);
			SetPageActive(page);
			stat->nr_activate[type] += nr_pages;
			count_memcg_page_event(page, PGACTIVATE);
		पूर्ण
keep_locked:
		unlock_page(page);
keep:
		list_add(&page->lru, &ret_pages);
		VM_BUG_ON_PAGE(PageLRU(page) || PageUnevictable(page), page);
	पूर्ण

	pgactivate = stat->nr_activate[0] + stat->nr_activate[1];

	mem_cgroup_unअक्षरge_list(&मुक्त_pages);
	try_to_unmap_flush();
	मुक्त_unref_page_list(&मुक्त_pages);

	list_splice(&ret_pages, page_list);
	count_vm_events(PGACTIVATE, pgactivate);

	वापस nr_reclaimed;
पूर्ण

अचिन्हित पूर्णांक reclaim_clean_pages_from_list(काष्ठा zone *zone,
					    काष्ठा list_head *page_list)
अणु
	काष्ठा scan_control sc = अणु
		.gfp_mask = GFP_KERNEL,
		.priority = DEF_PRIORITY,
		.may_unmap = 1,
	पूर्ण;
	काष्ठा reclaim_stat stat;
	अचिन्हित पूर्णांक nr_reclaimed;
	काष्ठा page *page, *next;
	LIST_HEAD(clean_pages);

	list_क्रम_each_entry_safe(page, next, page_list, lru) अणु
		अगर (!PageHuge(page) && page_is_file_lru(page) &&
		    !PageDirty(page) && !__PageMovable(page) &&
		    !PageUnevictable(page)) अणु
			ClearPageActive(page);
			list_move(&page->lru, &clean_pages);
		पूर्ण
	पूर्ण

	nr_reclaimed = shrink_page_list(&clean_pages, zone->zone_pgdat, &sc,
					&stat, true);
	list_splice(&clean_pages, page_list);
	mod_node_page_state(zone->zone_pgdat, NR_ISOLATED_खाता,
			    -(दीर्घ)nr_reclaimed);
	/*
	 * Since lazyमुक्त pages are isolated from file LRU from the beginning,
	 * they will rotate back to anonymous LRU in the end अगर it failed to
	 * discard so isolated count will be mismatched.
	 * Compensate the isolated count क्रम both LRU lists.
	 */
	mod_node_page_state(zone->zone_pgdat, NR_ISOLATED_ANON,
			    stat.nr_lazyमुक्त_fail);
	mod_node_page_state(zone->zone_pgdat, NR_ISOLATED_खाता,
			    -(दीर्घ)stat.nr_lazyमुक्त_fail);
	वापस nr_reclaimed;
पूर्ण

/*
 * Attempt to हटाओ the specअगरied page from its LRU.  Only take this page
 * अगर it is of the appropriate PageActive status.  Pages which are being
 * मुक्तd अन्यथाwhere are also ignored.
 *
 * page:	page to consider
 * mode:	one of the LRU isolation modes defined above
 *
 * वापसs true on success, false on failure.
 */
bool __isolate_lru_page_prepare(काष्ठा page *page, isolate_mode_t mode)
अणु
	/* Only take pages on the LRU. */
	अगर (!PageLRU(page))
		वापस false;

	/* Compaction should not handle unevictable pages but CMA can करो so */
	अगर (PageUnevictable(page) && !(mode & ISOLATE_UNEVICTABLE))
		वापस false;

	/*
	 * To minimise LRU disruption, the caller can indicate that it only
	 * wants to isolate pages it will be able to operate on without
	 * blocking - clean pages क्रम the most part.
	 *
	 * ISOLATE_ASYNC_MIGRATE is used to indicate that it only wants to pages
	 * that it is possible to migrate without blocking
	 */
	अगर (mode & ISOLATE_ASYNC_MIGRATE) अणु
		/* All the caller can करो on PageWriteback is block */
		अगर (PageWriteback(page))
			वापस false;

		अगर (PageDirty(page)) अणु
			काष्ठा address_space *mapping;
			bool migrate_dirty;

			/*
			 * Only pages without mappings or that have a
			 * ->migratepage callback are possible to migrate
			 * without blocking. However, we can be racing with
			 * truncation so it's necessary to lock the page
			 * to stabilise the mapping as truncation holds
			 * the page lock until after the page is हटाओd
			 * from the page cache.
			 */
			अगर (!trylock_page(page))
				वापस false;

			mapping = page_mapping(page);
			migrate_dirty = !mapping || mapping->a_ops->migratepage;
			unlock_page(page);
			अगर (!migrate_dirty)
				वापस false;
		पूर्ण
	पूर्ण

	अगर ((mode & ISOLATE_UNMAPPED) && page_mapped(page))
		वापस false;

	वापस true;
पूर्ण

/*
 * Update LRU sizes after isolating pages. The LRU size updates must
 * be complete beक्रमe mem_cgroup_update_lru_size due to a sanity check.
 */
अटल __always_अंतरभूत व्योम update_lru_sizes(काष्ठा lruvec *lruvec,
			क्रमागत lru_list lru, अचिन्हित दीर्घ *nr_zone_taken)
अणु
	पूर्णांक zid;

	क्रम (zid = 0; zid < MAX_NR_ZONES; zid++) अणु
		अगर (!nr_zone_taken[zid])
			जारी;

		update_lru_size(lruvec, lru, zid, -nr_zone_taken[zid]);
	पूर्ण

पूर्ण

/**
 * Isolating page from the lruvec to fill in @dst list by nr_to_scan बार.
 *
 * lruvec->lru_lock is heavily contended.  Some of the functions that
 * shrink the lists perक्रमm better by taking out a batch of pages
 * and working on them outside the LRU lock.
 *
 * For pagecache पूर्णांकensive workloads, this function is the hottest
 * spot in the kernel (apart from copy_*_user functions).
 *
 * Lru_lock must be held beक्रमe calling this function.
 *
 * @nr_to_scan:	The number of eligible pages to look through on the list.
 * @lruvec:	The LRU vector to pull pages from.
 * @dst:	The temp list to put pages on to.
 * @nr_scanned:	The number of pages that were scanned.
 * @sc:		The scan_control काष्ठा क्रम this reclaim session
 * @lru:	LRU list id क्रम isolating
 *
 * वापसs how many pages were moved onto *@dst.
 */
अटल अचिन्हित दीर्घ isolate_lru_pages(अचिन्हित दीर्घ nr_to_scan,
		काष्ठा lruvec *lruvec, काष्ठा list_head *dst,
		अचिन्हित दीर्घ *nr_scanned, काष्ठा scan_control *sc,
		क्रमागत lru_list lru)
अणु
	काष्ठा list_head *src = &lruvec->lists[lru];
	अचिन्हित दीर्घ nr_taken = 0;
	अचिन्हित दीर्घ nr_zone_taken[MAX_NR_ZONES] = अणु 0 पूर्ण;
	अचिन्हित दीर्घ nr_skipped[MAX_NR_ZONES] = अणु 0, पूर्ण;
	अचिन्हित दीर्घ skipped = 0;
	अचिन्हित दीर्घ scan, total_scan, nr_pages;
	LIST_HEAD(pages_skipped);
	isolate_mode_t mode = (sc->may_unmap ? 0 : ISOLATE_UNMAPPED);

	total_scan = 0;
	scan = 0;
	जबतक (scan < nr_to_scan && !list_empty(src)) अणु
		काष्ठा page *page;

		page = lru_to_page(src);
		prefetchw_prev_lru_page(page, src, flags);

		nr_pages = compound_nr(page);
		total_scan += nr_pages;

		अगर (page_zonक्रमागत(page) > sc->reclaim_idx) अणु
			list_move(&page->lru, &pages_skipped);
			nr_skipped[page_zonक्रमागत(page)] += nr_pages;
			जारी;
		पूर्ण

		/*
		 * Do not count skipped pages because that makes the function
		 * वापस with no isolated pages अगर the LRU mostly contains
		 * ineligible pages.  This causes the VM to not reclaim any
		 * pages, triggering a premature OOM.
		 *
		 * Account all tail pages of THP.  This would not cause
		 * premature OOM since __isolate_lru_page() वापसs -EBUSY
		 * only when the page is being मुक्तd somewhere अन्यथा.
		 */
		scan += nr_pages;
		अगर (!__isolate_lru_page_prepare(page, mode)) अणु
			/* It is being मुक्तd अन्यथाwhere */
			list_move(&page->lru, src);
			जारी;
		पूर्ण
		/*
		 * Be careful not to clear PageLRU until after we're
		 * sure the page is not being मुक्तd अन्यथाwhere -- the
		 * page release code relies on it.
		 */
		अगर (unlikely(!get_page_unless_zero(page))) अणु
			list_move(&page->lru, src);
			जारी;
		पूर्ण

		अगर (!TestClearPageLRU(page)) अणु
			/* Another thपढ़ो is alपढ़ोy isolating this page */
			put_page(page);
			list_move(&page->lru, src);
			जारी;
		पूर्ण

		nr_taken += nr_pages;
		nr_zone_taken[page_zonक्रमागत(page)] += nr_pages;
		list_move(&page->lru, dst);
	पूर्ण

	/*
	 * Splice any skipped pages to the start of the LRU list. Note that
	 * this disrupts the LRU order when reclaiming क्रम lower zones but
	 * we cannot splice to the tail. If we did then the SWAP_CLUSTER_MAX
	 * scanning would soon rescan the same pages to skip and put the
	 * प्रणाली at risk of premature OOM.
	 */
	अगर (!list_empty(&pages_skipped)) अणु
		पूर्णांक zid;

		list_splice(&pages_skipped, src);
		क्रम (zid = 0; zid < MAX_NR_ZONES; zid++) अणु
			अगर (!nr_skipped[zid])
				जारी;

			__count_zid_vm_events(PGSCAN_SKIP, zid, nr_skipped[zid]);
			skipped += nr_skipped[zid];
		पूर्ण
	पूर्ण
	*nr_scanned = total_scan;
	trace_mm_vmscan_lru_isolate(sc->reclaim_idx, sc->order, nr_to_scan,
				    total_scan, skipped, nr_taken, mode, lru);
	update_lru_sizes(lruvec, lru, nr_zone_taken);
	वापस nr_taken;
पूर्ण

/**
 * isolate_lru_page - tries to isolate a page from its LRU list
 * @page: page to isolate from its LRU list
 *
 * Isolates a @page from an LRU list, clears PageLRU and adjusts the
 * vmstat statistic corresponding to whatever LRU list the page was on.
 *
 * Returns 0 अगर the page was हटाओd from an LRU list.
 * Returns -EBUSY अगर the page was not on an LRU list.
 *
 * The वापसed page will have PageLRU() cleared.  If it was found on
 * the active list, it will have PageActive set.  If it was found on
 * the unevictable list, it will have the PageUnevictable bit set. That flag
 * may need to be cleared by the caller beक्रमe letting the page go.
 *
 * The vmstat statistic corresponding to the list on which the page was
 * found will be decremented.
 *
 * Restrictions:
 *
 * (1) Must be called with an elevated refcount on the page. This is a
 *     fundamental dअगरference from isolate_lru_pages (which is called
 *     without a stable reference).
 * (2) the lru_lock must not be held.
 * (3) पूर्णांकerrupts must be enabled.
 */
पूर्णांक isolate_lru_page(काष्ठा page *page)
अणु
	पूर्णांक ret = -EBUSY;

	VM_BUG_ON_PAGE(!page_count(page), page);
	WARN_RATELIMIT(PageTail(page), "trying to isolate tail page");

	अगर (TestClearPageLRU(page)) अणु
		काष्ठा lruvec *lruvec;

		get_page(page);
		lruvec = lock_page_lruvec_irq(page);
		del_page_from_lru_list(page, lruvec);
		unlock_page_lruvec_irq(lruvec);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * A direct reclaimer may isolate SWAP_CLUSTER_MAX pages from the LRU list and
 * then get rescheduled. When there are massive number of tasks करोing page
 * allocation, such sleeping direct reclaimers may keep piling up on each CPU,
 * the LRU list will go small and be scanned faster than necessary, leading to
 * unnecessary swapping, thrashing and OOM.
 */
अटल पूर्णांक too_many_isolated(काष्ठा pglist_data *pgdat, पूर्णांक file,
		काष्ठा scan_control *sc)
अणु
	अचिन्हित दीर्घ inactive, isolated;

	अगर (current_is_kswapd())
		वापस 0;

	अगर (!ग_लिखोback_throttling_sane(sc))
		वापस 0;

	अगर (file) अणु
		inactive = node_page_state(pgdat, NR_INACTIVE_खाता);
		isolated = node_page_state(pgdat, NR_ISOLATED_खाता);
	पूर्ण अन्यथा अणु
		inactive = node_page_state(pgdat, NR_INACTIVE_ANON);
		isolated = node_page_state(pgdat, NR_ISOLATED_ANON);
	पूर्ण

	/*
	 * GFP_NOIO/GFP_NOFS callers are allowed to isolate more pages, so they
	 * won't get blocked by normal direct-reclaimers, क्रमming a circular
	 * deadlock.
	 */
	अगर ((sc->gfp_mask & (__GFP_IO | __GFP_FS)) == (__GFP_IO | __GFP_FS))
		inactive >>= 3;

	वापस isolated > inactive;
पूर्ण

/*
 * move_pages_to_lru() moves pages from निजी @list to appropriate LRU list.
 * On वापस, @list is reused as a list of pages to be मुक्तd by the caller.
 *
 * Returns the number of pages moved to the given lruvec.
 */
अटल अचिन्हित noअंतरभूत_क्रम_stack move_pages_to_lru(काष्ठा lruvec *lruvec,
						     काष्ठा list_head *list)
अणु
	पूर्णांक nr_pages, nr_moved = 0;
	LIST_HEAD(pages_to_मुक्त);
	काष्ठा page *page;

	जबतक (!list_empty(list)) अणु
		page = lru_to_page(list);
		VM_BUG_ON_PAGE(PageLRU(page), page);
		list_del(&page->lru);
		अगर (unlikely(!page_evictable(page))) अणु
			spin_unlock_irq(&lruvec->lru_lock);
			putback_lru_page(page);
			spin_lock_irq(&lruvec->lru_lock);
			जारी;
		पूर्ण

		/*
		 * The SetPageLRU needs to be kept here क्रम list पूर्णांकegrity.
		 * Otherwise:
		 *   #0 move_pages_to_lru             #1 release_pages
		 *   अगर !put_page_testzero
		 *				      अगर (put_page_testzero())
		 *				        !PageLRU //skip lru_lock
		 *     SetPageLRU()
		 *     list_add(&page->lru,)
		 *                                        list_add(&page->lru,)
		 */
		SetPageLRU(page);

		अगर (unlikely(put_page_testzero(page))) अणु
			__clear_page_lru_flags(page);

			अगर (unlikely(PageCompound(page))) अणु
				spin_unlock_irq(&lruvec->lru_lock);
				destroy_compound_page(page);
				spin_lock_irq(&lruvec->lru_lock);
			पूर्ण अन्यथा
				list_add(&page->lru, &pages_to_मुक्त);

			जारी;
		पूर्ण

		/*
		 * All pages were isolated from the same lruvec (and isolation
		 * inhibits memcg migration).
		 */
		VM_BUG_ON_PAGE(!lruvec_holds_page_lru_lock(page, lruvec), page);
		add_page_to_lru_list(page, lruvec);
		nr_pages = thp_nr_pages(page);
		nr_moved += nr_pages;
		अगर (PageActive(page))
			workingset_age_nonresident(lruvec, nr_pages);
	पूर्ण

	/*
	 * To save our caller's stack, now use input list क्रम pages to मुक्त.
	 */
	list_splice(&pages_to_मुक्त, list);

	वापस nr_moved;
पूर्ण

/*
 * If a kernel thपढ़ो (such as nfsd क्रम loop-back mounts) services
 * a backing device by writing to the page cache it sets PF_LOCAL_THROTTLE.
 * In that हाल we should only throttle अगर the backing device it is
 * writing to is congested.  In other हालs it is safe to throttle.
 */
अटल पूर्णांक current_may_throttle(व्योम)
अणु
	वापस !(current->flags & PF_LOCAL_THROTTLE) ||
		current->backing_dev_info == शून्य ||
		bdi_ग_लिखो_congested(current->backing_dev_info);
पूर्ण

/*
 * shrink_inactive_list() is a helper क्रम shrink_node().  It वापसs the number
 * of reclaimed pages
 */
अटल noअंतरभूत_क्रम_stack अचिन्हित दीर्घ
shrink_inactive_list(अचिन्हित दीर्घ nr_to_scan, काष्ठा lruvec *lruvec,
		     काष्ठा scan_control *sc, क्रमागत lru_list lru)
अणु
	LIST_HEAD(page_list);
	अचिन्हित दीर्घ nr_scanned;
	अचिन्हित पूर्णांक nr_reclaimed = 0;
	अचिन्हित दीर्घ nr_taken;
	काष्ठा reclaim_stat stat;
	bool file = is_file_lru(lru);
	क्रमागत vm_event_item item;
	काष्ठा pglist_data *pgdat = lruvec_pgdat(lruvec);
	bool stalled = false;

	जबतक (unlikely(too_many_isolated(pgdat, file, sc))) अणु
		अगर (stalled)
			वापस 0;

		/* रुको a bit क्रम the reclaimer. */
		msleep(100);
		stalled = true;

		/* We are about to die and मुक्त our memory. Return now. */
		अगर (fatal_संकेत_pending(current))
			वापस SWAP_CLUSTER_MAX;
	पूर्ण

	lru_add_drain();

	spin_lock_irq(&lruvec->lru_lock);

	nr_taken = isolate_lru_pages(nr_to_scan, lruvec, &page_list,
				     &nr_scanned, sc, lru);

	__mod_node_page_state(pgdat, NR_ISOLATED_ANON + file, nr_taken);
	item = current_is_kswapd() ? PGSCAN_KSWAPD : PGSCAN_सूचीECT;
	अगर (!cgroup_reclaim(sc))
		__count_vm_events(item, nr_scanned);
	__count_memcg_events(lruvec_memcg(lruvec), item, nr_scanned);
	__count_vm_events(PGSCAN_ANON + file, nr_scanned);

	spin_unlock_irq(&lruvec->lru_lock);

	अगर (nr_taken == 0)
		वापस 0;

	nr_reclaimed = shrink_page_list(&page_list, pgdat, sc, &stat, false);

	spin_lock_irq(&lruvec->lru_lock);
	move_pages_to_lru(lruvec, &page_list);

	__mod_node_page_state(pgdat, NR_ISOLATED_ANON + file, -nr_taken);
	item = current_is_kswapd() ? PGSTEAL_KSWAPD : PGSTEAL_सूचीECT;
	अगर (!cgroup_reclaim(sc))
		__count_vm_events(item, nr_reclaimed);
	__count_memcg_events(lruvec_memcg(lruvec), item, nr_reclaimed);
	__count_vm_events(PGSTEAL_ANON + file, nr_reclaimed);
	spin_unlock_irq(&lruvec->lru_lock);

	lru_note_cost(lruvec, file, stat.nr_pageout);
	mem_cgroup_unअक्षरge_list(&page_list);
	मुक्त_unref_page_list(&page_list);

	/*
	 * If dirty pages are scanned that are not queued क्रम IO, it
	 * implies that flushers are not करोing their job. This can
	 * happen when memory pressure pushes dirty pages to the end of
	 * the LRU beक्रमe the dirty limits are breached and the dirty
	 * data has expired. It can also happen when the proportion of
	 * dirty pages grows not through ग_लिखोs but through memory
	 * pressure reclaiming all the clean cache. And in some हालs,
	 * the flushers simply cannot keep up with the allocation
	 * rate. Nudge the flusher thपढ़ोs in हाल they are asleep.
	 */
	अगर (stat.nr_unqueued_dirty == nr_taken)
		wakeup_flusher_thपढ़ोs(WB_REASON_VMSCAN);

	sc->nr.dirty += stat.nr_dirty;
	sc->nr.congested += stat.nr_congested;
	sc->nr.unqueued_dirty += stat.nr_unqueued_dirty;
	sc->nr.ग_लिखोback += stat.nr_ग_लिखोback;
	sc->nr.immediate += stat.nr_immediate;
	sc->nr.taken += nr_taken;
	अगर (file)
		sc->nr.file_taken += nr_taken;

	trace_mm_vmscan_lru_shrink_inactive(pgdat->node_id,
			nr_scanned, nr_reclaimed, &stat, sc->priority, file);
	वापस nr_reclaimed;
पूर्ण

/*
 * shrink_active_list() moves pages from the active LRU to the inactive LRU.
 *
 * We move them the other way अगर the page is referenced by one or more
 * processes.
 *
 * If the pages are mostly unmapped, the processing is fast and it is
 * appropriate to hold lru_lock across the whole operation.  But अगर
 * the pages are mapped, the processing is slow (page_referenced()), so
 * we should drop lru_lock around each page.  It's impossible to balance
 * this, so instead we हटाओ the pages from the LRU जबतक processing them.
 * It is safe to rely on PG_active against the non-LRU pages in here because
 * nobody will play with that bit on a non-LRU page.
 *
 * The करोwnside is that we have to touch page->_refcount against each page.
 * But we had to alter page->flags anyway.
 */
अटल व्योम shrink_active_list(अचिन्हित दीर्घ nr_to_scan,
			       काष्ठा lruvec *lruvec,
			       काष्ठा scan_control *sc,
			       क्रमागत lru_list lru)
अणु
	अचिन्हित दीर्घ nr_taken;
	अचिन्हित दीर्घ nr_scanned;
	अचिन्हित दीर्घ vm_flags;
	LIST_HEAD(l_hold);	/* The pages which were snipped off */
	LIST_HEAD(l_active);
	LIST_HEAD(l_inactive);
	काष्ठा page *page;
	अचिन्हित nr_deactivate, nr_activate;
	अचिन्हित nr_rotated = 0;
	पूर्णांक file = is_file_lru(lru);
	काष्ठा pglist_data *pgdat = lruvec_pgdat(lruvec);

	lru_add_drain();

	spin_lock_irq(&lruvec->lru_lock);

	nr_taken = isolate_lru_pages(nr_to_scan, lruvec, &l_hold,
				     &nr_scanned, sc, lru);

	__mod_node_page_state(pgdat, NR_ISOLATED_ANON + file, nr_taken);

	अगर (!cgroup_reclaim(sc))
		__count_vm_events(PGREFILL, nr_scanned);
	__count_memcg_events(lruvec_memcg(lruvec), PGREFILL, nr_scanned);

	spin_unlock_irq(&lruvec->lru_lock);

	जबतक (!list_empty(&l_hold)) अणु
		cond_resched();
		page = lru_to_page(&l_hold);
		list_del(&page->lru);

		अगर (unlikely(!page_evictable(page))) अणु
			putback_lru_page(page);
			जारी;
		पूर्ण

		अगर (unlikely(buffer_heads_over_limit)) अणु
			अगर (page_has_निजी(page) && trylock_page(page)) अणु
				अगर (page_has_निजी(page))
					try_to_release_page(page, 0);
				unlock_page(page);
			पूर्ण
		पूर्ण

		अगर (page_referenced(page, 0, sc->target_mem_cgroup,
				    &vm_flags)) अणु
			/*
			 * Identअगरy referenced, file-backed active pages and
			 * give them one more trip around the active list. So
			 * that executable code get better chances to stay in
			 * memory under moderate memory pressure.  Anon pages
			 * are not likely to be evicted by use-once streaming
			 * IO, plus JVM can create lots of anon VM_EXEC pages,
			 * so we ignore them here.
			 */
			अगर ((vm_flags & VM_EXEC) && page_is_file_lru(page)) अणु
				nr_rotated += thp_nr_pages(page);
				list_add(&page->lru, &l_active);
				जारी;
			पूर्ण
		पूर्ण

		ClearPageActive(page);	/* we are de-activating */
		SetPageWorkingset(page);
		list_add(&page->lru, &l_inactive);
	पूर्ण

	/*
	 * Move pages back to the lru list.
	 */
	spin_lock_irq(&lruvec->lru_lock);

	nr_activate = move_pages_to_lru(lruvec, &l_active);
	nr_deactivate = move_pages_to_lru(lruvec, &l_inactive);
	/* Keep all मुक्त pages in l_active list */
	list_splice(&l_inactive, &l_active);

	__count_vm_events(PGDEACTIVATE, nr_deactivate);
	__count_memcg_events(lruvec_memcg(lruvec), PGDEACTIVATE, nr_deactivate);

	__mod_node_page_state(pgdat, NR_ISOLATED_ANON + file, -nr_taken);
	spin_unlock_irq(&lruvec->lru_lock);

	mem_cgroup_unअक्षरge_list(&l_active);
	मुक्त_unref_page_list(&l_active);
	trace_mm_vmscan_lru_shrink_active(pgdat->node_id, nr_taken, nr_activate,
			nr_deactivate, nr_rotated, sc->priority, file);
पूर्ण

अचिन्हित दीर्घ reclaim_pages(काष्ठा list_head *page_list)
अणु
	पूर्णांक nid = NUMA_NO_NODE;
	अचिन्हित पूर्णांक nr_reclaimed = 0;
	LIST_HEAD(node_page_list);
	काष्ठा reclaim_stat dummy_stat;
	काष्ठा page *page;
	काष्ठा scan_control sc = अणु
		.gfp_mask = GFP_KERNEL,
		.priority = DEF_PRIORITY,
		.may_ग_लिखोpage = 1,
		.may_unmap = 1,
		.may_swap = 1,
	पूर्ण;

	जबतक (!list_empty(page_list)) अणु
		page = lru_to_page(page_list);
		अगर (nid == NUMA_NO_NODE) अणु
			nid = page_to_nid(page);
			INIT_LIST_HEAD(&node_page_list);
		पूर्ण

		अगर (nid == page_to_nid(page)) अणु
			ClearPageActive(page);
			list_move(&page->lru, &node_page_list);
			जारी;
		पूर्ण

		nr_reclaimed += shrink_page_list(&node_page_list,
						NODE_DATA(nid),
						&sc, &dummy_stat, false);
		जबतक (!list_empty(&node_page_list)) अणु
			page = lru_to_page(&node_page_list);
			list_del(&page->lru);
			putback_lru_page(page);
		पूर्ण

		nid = NUMA_NO_NODE;
	पूर्ण

	अगर (!list_empty(&node_page_list)) अणु
		nr_reclaimed += shrink_page_list(&node_page_list,
						NODE_DATA(nid),
						&sc, &dummy_stat, false);
		जबतक (!list_empty(&node_page_list)) अणु
			page = lru_to_page(&node_page_list);
			list_del(&page->lru);
			putback_lru_page(page);
		पूर्ण
	पूर्ण

	वापस nr_reclaimed;
पूर्ण

अटल अचिन्हित दीर्घ shrink_list(क्रमागत lru_list lru, अचिन्हित दीर्घ nr_to_scan,
				 काष्ठा lruvec *lruvec, काष्ठा scan_control *sc)
अणु
	अगर (is_active_lru(lru)) अणु
		अगर (sc->may_deactivate & (1 << is_file_lru(lru)))
			shrink_active_list(nr_to_scan, lruvec, sc, lru);
		अन्यथा
			sc->skipped_deactivate = 1;
		वापस 0;
	पूर्ण

	वापस shrink_inactive_list(nr_to_scan, lruvec, sc, lru);
पूर्ण

/*
 * The inactive anon list should be small enough that the VM never has
 * to करो too much work.
 *
 * The inactive file list should be small enough to leave most memory
 * to the established workingset on the scan-resistant active list,
 * but large enough to aव्योम thrashing the aggregate पढ़ोahead winकरोw.
 *
 * Both inactive lists should also be large enough that each inactive
 * page has a chance to be referenced again beक्रमe it is reclaimed.
 *
 * If that fails and refaulting is observed, the inactive list grows.
 *
 * The inactive_ratio is the target ratio of ACTIVE to INACTIVE pages
 * on this LRU, मुख्यtained by the pageout code. An inactive_ratio
 * of 3 means 3:1 or 25% of the pages are kept on the inactive list.
 *
 * total     target    max
 * memory    ratio     inactive
 * -------------------------------------
 *   10MB       1         5MB
 *  100MB       1        50MB
 *    1GB       3       250MB
 *   10GB      10       0.9GB
 *  100GB      31         3GB
 *    1TB     101        10GB
 *   10TB     320        32GB
 */
अटल bool inactive_is_low(काष्ठा lruvec *lruvec, क्रमागत lru_list inactive_lru)
अणु
	क्रमागत lru_list active_lru = inactive_lru + LRU_ACTIVE;
	अचिन्हित दीर्घ inactive, active;
	अचिन्हित दीर्घ inactive_ratio;
	अचिन्हित दीर्घ gb;

	inactive = lruvec_page_state(lruvec, NR_LRU_BASE + inactive_lru);
	active = lruvec_page_state(lruvec, NR_LRU_BASE + active_lru);

	gb = (inactive + active) >> (30 - PAGE_SHIFT);
	अगर (gb)
		inactive_ratio = पूर्णांक_वर्ग_मूल(10 * gb);
	अन्यथा
		inactive_ratio = 1;

	वापस inactive * inactive_ratio < active;
पूर्ण

क्रमागत scan_balance अणु
	SCAN_EQUAL,
	SCAN_FRACT,
	SCAN_ANON,
	SCAN_खाता,
पूर्ण;

/*
 * Determine how aggressively the anon and file LRU lists should be
 * scanned.  The relative value of each set of LRU lists is determined
 * by looking at the fraction of the pages scanned we did rotate back
 * onto the active list instead of evict.
 *
 * nr[0] = anon inactive pages to scan; nr[1] = anon active pages to scan
 * nr[2] = file inactive pages to scan; nr[3] = file active pages to scan
 */
अटल व्योम get_scan_count(काष्ठा lruvec *lruvec, काष्ठा scan_control *sc,
			   अचिन्हित दीर्घ *nr)
अणु
	काष्ठा mem_cgroup *memcg = lruvec_memcg(lruvec);
	अचिन्हित दीर्घ anon_cost, file_cost, total_cost;
	पूर्णांक swappiness = mem_cgroup_swappiness(memcg);
	u64 fraction[ANON_AND_खाता];
	u64 denominator = 0;	/* gcc */
	क्रमागत scan_balance scan_balance;
	अचिन्हित दीर्घ ap, fp;
	क्रमागत lru_list lru;

	/* If we have no swap space, करो not bother scanning anon pages. */
	अगर (!sc->may_swap || mem_cgroup_get_nr_swap_pages(memcg) <= 0) अणु
		scan_balance = SCAN_खाता;
		जाओ out;
	पूर्ण

	/*
	 * Global reclaim will swap to prevent OOM even with no
	 * swappiness, but memcg users want to use this knob to
	 * disable swapping क्रम inभागidual groups completely when
	 * using the memory controller's swap limit feature would be
	 * too expensive.
	 */
	अगर (cgroup_reclaim(sc) && !swappiness) अणु
		scan_balance = SCAN_खाता;
		जाओ out;
	पूर्ण

	/*
	 * Do not apply any pressure balancing cleverness when the
	 * प्रणाली is बंद to OOM, scan both anon and file equally
	 * (unless the swappiness setting disagrees with swapping).
	 */
	अगर (!sc->priority && swappiness) अणु
		scan_balance = SCAN_EQUAL;
		जाओ out;
	पूर्ण

	/*
	 * If the प्रणाली is almost out of file pages, क्रमce-scan anon.
	 */
	अगर (sc->file_is_tiny) अणु
		scan_balance = SCAN_ANON;
		जाओ out;
	पूर्ण

	/*
	 * If there is enough inactive page cache, we करो not reclaim
	 * anything from the anonymous working right now.
	 */
	अगर (sc->cache_trim_mode) अणु
		scan_balance = SCAN_खाता;
		जाओ out;
	पूर्ण

	scan_balance = SCAN_FRACT;
	/*
	 * Calculate the pressure balance between anon and file pages.
	 *
	 * The amount of pressure we put on each LRU is inversely
	 * proportional to the cost of reclaiming each list, as
	 * determined by the share of pages that are refaulting, बार
	 * the relative IO cost of bringing back a swapped out
	 * anonymous page vs reloading a fileप्रणाली page (swappiness).
	 *
	 * Although we limit that influence to ensure no list माला_लो
	 * left behind completely: at least a third of the pressure is
	 * applied, beक्रमe swappiness.
	 *
	 * With swappiness at 100, anon and file have equal IO cost.
	 */
	total_cost = sc->anon_cost + sc->file_cost;
	anon_cost = total_cost + sc->anon_cost;
	file_cost = total_cost + sc->file_cost;
	total_cost = anon_cost + file_cost;

	ap = swappiness * (total_cost + 1);
	ap /= anon_cost + 1;

	fp = (200 - swappiness) * (total_cost + 1);
	fp /= file_cost + 1;

	fraction[0] = ap;
	fraction[1] = fp;
	denominator = ap + fp;
out:
	क्रम_each_evictable_lru(lru) अणु
		पूर्णांक file = is_file_lru(lru);
		अचिन्हित दीर्घ lruvec_size;
		अचिन्हित दीर्घ scan;
		अचिन्हित दीर्घ protection;

		lruvec_size = lruvec_lru_size(lruvec, lru, sc->reclaim_idx);
		protection = mem_cgroup_protection(sc->target_mem_cgroup,
						   memcg,
						   sc->memcg_low_reclaim);

		अगर (protection) अणु
			/*
			 * Scale a cgroup's reclaim pressure by proportioning
			 * its current usage to its memory.low or memory.min
			 * setting.
			 *
			 * This is important, as otherwise scanning aggression
			 * becomes extremely binary -- from nothing as we
			 * approach the memory protection threshold, to totally
			 * nominal as we exceed it.  This results in requiring
			 * setting extremely liberal protection thresholds. It
			 * also means we simply get no protection at all अगर we
			 * set it too low, which is not ideal.
			 *
			 * If there is any protection in place, we reduce scan
			 * pressure by how much of the total memory used is
			 * within protection thresholds.
			 *
			 * There is one special हाल: in the first reclaim pass,
			 * we skip over all groups that are within their low
			 * protection. If that fails to reclaim enough pages to
			 * satisfy the reclaim goal, we come back and override
			 * the best-efक्रमt low protection. However, we still
			 * ideally want to honor how well-behaved groups are in
			 * that हाल instead of simply punishing them all
			 * equally. As such, we reclaim them based on how much
			 * memory they are using, reducing the scan pressure
			 * again by how much of the total memory used is under
			 * hard protection.
			 */
			अचिन्हित दीर्घ cgroup_size = mem_cgroup_size(memcg);

			/* Aव्योम TOCTOU with earlier protection check */
			cgroup_size = max(cgroup_size, protection);

			scan = lruvec_size - lruvec_size * protection /
				cgroup_size;

			/*
			 * Minimally target SWAP_CLUSTER_MAX pages to keep
			 * reclaim moving क्रमwards, aव्योमing decrementing
			 * sc->priority further than desirable.
			 */
			scan = max(scan, SWAP_CLUSTER_MAX);
		पूर्ण अन्यथा अणु
			scan = lruvec_size;
		पूर्ण

		scan >>= sc->priority;

		/*
		 * If the cgroup's alपढ़ोy been deleted, make sure to
		 * scrape out the reमुख्यing cache.
		 */
		अगर (!scan && !mem_cgroup_online(memcg))
			scan = min(lruvec_size, SWAP_CLUSTER_MAX);

		चयन (scan_balance) अणु
		हाल SCAN_EQUAL:
			/* Scan lists relative to size */
			अवरोध;
		हाल SCAN_FRACT:
			/*
			 * Scan types proportional to swappiness and
			 * their relative recent reclaim efficiency.
			 * Make sure we करोn't miss the last page on
			 * the offlined memory cgroups because of a
			 * round-off error.
			 */
			scan = mem_cgroup_online(memcg) ?
			       भाग64_u64(scan * fraction[file], denominator) :
			       DIV64_U64_ROUND_UP(scan * fraction[file],
						  denominator);
			अवरोध;
		हाल SCAN_खाता:
		हाल SCAN_ANON:
			/* Scan one type exclusively */
			अगर ((scan_balance == SCAN_खाता) != file)
				scan = 0;
			अवरोध;
		शेष:
			/* Look ma, no brain */
			BUG();
		पूर्ण

		nr[lru] = scan;
	पूर्ण
पूर्ण

अटल व्योम shrink_lruvec(काष्ठा lruvec *lruvec, काष्ठा scan_control *sc)
अणु
	अचिन्हित दीर्घ nr[NR_LRU_LISTS];
	अचिन्हित दीर्घ tarमाला_लो[NR_LRU_LISTS];
	अचिन्हित दीर्घ nr_to_scan;
	क्रमागत lru_list lru;
	अचिन्हित दीर्घ nr_reclaimed = 0;
	अचिन्हित दीर्घ nr_to_reclaim = sc->nr_to_reclaim;
	काष्ठा blk_plug plug;
	bool scan_adjusted;

	get_scan_count(lruvec, sc, nr);

	/* Record the original scan target क्रम proportional adjusपंचांगents later */
	स_नकल(tarमाला_लो, nr, माप(nr));

	/*
	 * Global reclaiming within direct reclaim at DEF_PRIORITY is a normal
	 * event that can occur when there is little memory pressure e.g.
	 * multiple streaming पढ़ोers/ग_लिखोrs. Hence, we करो not पात scanning
	 * when the requested number of pages are reclaimed when scanning at
	 * DEF_PRIORITY on the assumption that the fact we are direct
	 * reclaiming implies that kswapd is not keeping up and it is best to
	 * करो a batch of work at once. For memcg reclaim one check is made to
	 * पात proportional reclaim अगर either the file or anon lru has alपढ़ोy
	 * dropped to zero at the first pass.
	 */
	scan_adjusted = (!cgroup_reclaim(sc) && !current_is_kswapd() &&
			 sc->priority == DEF_PRIORITY);

	blk_start_plug(&plug);
	जबतक (nr[LRU_INACTIVE_ANON] || nr[LRU_ACTIVE_खाता] ||
					nr[LRU_INACTIVE_खाता]) अणु
		अचिन्हित दीर्घ nr_anon, nr_file, percentage;
		अचिन्हित दीर्घ nr_scanned;

		क्रम_each_evictable_lru(lru) अणु
			अगर (nr[lru]) अणु
				nr_to_scan = min(nr[lru], SWAP_CLUSTER_MAX);
				nr[lru] -= nr_to_scan;

				nr_reclaimed += shrink_list(lru, nr_to_scan,
							    lruvec, sc);
			पूर्ण
		पूर्ण

		cond_resched();

		अगर (nr_reclaimed < nr_to_reclaim || scan_adjusted)
			जारी;

		/*
		 * For kswapd and memcg, reclaim at least the number of pages
		 * requested. Ensure that the anon and file LRUs are scanned
		 * proportionally what was requested by get_scan_count(). We
		 * stop reclaiming one LRU and reduce the amount scanning
		 * proportional to the original scan target.
		 */
		nr_file = nr[LRU_INACTIVE_खाता] + nr[LRU_ACTIVE_खाता];
		nr_anon = nr[LRU_INACTIVE_ANON] + nr[LRU_ACTIVE_ANON];

		/*
		 * It's just vindictive to attack the larger once the smaller
		 * has gone to zero.  And given the way we stop scanning the
		 * smaller below, this makes sure that we only make one nudge
		 * towards proportionality once we've got nr_to_reclaim.
		 */
		अगर (!nr_file || !nr_anon)
			अवरोध;

		अगर (nr_file > nr_anon) अणु
			अचिन्हित दीर्घ scan_target = tarमाला_लो[LRU_INACTIVE_ANON] +
						tarमाला_लो[LRU_ACTIVE_ANON] + 1;
			lru = LRU_BASE;
			percentage = nr_anon * 100 / scan_target;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ scan_target = tarमाला_लो[LRU_INACTIVE_खाता] +
						tarमाला_लो[LRU_ACTIVE_खाता] + 1;
			lru = LRU_खाता;
			percentage = nr_file * 100 / scan_target;
		पूर्ण

		/* Stop scanning the smaller of the LRU */
		nr[lru] = 0;
		nr[lru + LRU_ACTIVE] = 0;

		/*
		 * Recalculate the other LRU scan count based on its original
		 * scan target and the percentage scanning alपढ़ोy complete
		 */
		lru = (lru == LRU_खाता) ? LRU_BASE : LRU_खाता;
		nr_scanned = tarमाला_लो[lru] - nr[lru];
		nr[lru] = tarमाला_लो[lru] * (100 - percentage) / 100;
		nr[lru] -= min(nr[lru], nr_scanned);

		lru += LRU_ACTIVE;
		nr_scanned = tarमाला_लो[lru] - nr[lru];
		nr[lru] = tarमाला_लो[lru] * (100 - percentage) / 100;
		nr[lru] -= min(nr[lru], nr_scanned);

		scan_adjusted = true;
	पूर्ण
	blk_finish_plug(&plug);
	sc->nr_reclaimed += nr_reclaimed;

	/*
	 * Even अगर we did not try to evict anon pages at all, we want to
	 * rebalance the anon lru active/inactive ratio.
	 */
	अगर (total_swap_pages && inactive_is_low(lruvec, LRU_INACTIVE_ANON))
		shrink_active_list(SWAP_CLUSTER_MAX, lruvec,
				   sc, LRU_ACTIVE_ANON);
पूर्ण

/* Use reclaim/compaction क्रम costly allocs or under memory pressure */
अटल bool in_reclaim_compaction(काष्ठा scan_control *sc)
अणु
	अगर (IS_ENABLED(CONFIG_COMPACTION) && sc->order &&
			(sc->order > PAGE_ALLOC_COSTLY_ORDER ||
			 sc->priority < DEF_PRIORITY - 2))
		वापस true;

	वापस false;
पूर्ण

/*
 * Reclaim/compaction is used क्रम high-order allocation requests. It reclaims
 * order-0 pages beक्रमe compacting the zone. should_जारी_reclaim() वापसs
 * true अगर more pages should be reclaimed such that when the page allocator
 * calls try_to_compact_pages() that it will have enough मुक्त pages to succeed.
 * It will give up earlier than that अगर there is dअगरficulty reclaiming pages.
 */
अटल अंतरभूत bool should_जारी_reclaim(काष्ठा pglist_data *pgdat,
					अचिन्हित दीर्घ nr_reclaimed,
					काष्ठा scan_control *sc)
अणु
	अचिन्हित दीर्घ pages_क्रम_compaction;
	अचिन्हित दीर्घ inactive_lru_pages;
	पूर्णांक z;

	/* If not in reclaim/compaction mode, stop */
	अगर (!in_reclaim_compaction(sc))
		वापस false;

	/*
	 * Stop अगर we failed to reclaim any pages from the last SWAP_CLUSTER_MAX
	 * number of pages that were scanned. This will वापस to the caller
	 * with the risk reclaim/compaction and the resulting allocation attempt
	 * fails. In the past we have tried harder क्रम __GFP_RETRY_MAYFAIL
	 * allocations through requiring that the full LRU list has been scanned
	 * first, by assuming that zero delta of sc->nr_scanned means full LRU
	 * scan, but that approximation was wrong, and there were corner हालs
	 * where always a non-zero amount of pages were scanned.
	 */
	अगर (!nr_reclaimed)
		वापस false;

	/* If compaction would go ahead or the allocation would succeed, stop */
	क्रम (z = 0; z <= sc->reclaim_idx; z++) अणु
		काष्ठा zone *zone = &pgdat->node_zones[z];
		अगर (!managed_zone(zone))
			जारी;

		चयन (compaction_suitable(zone, sc->order, 0, sc->reclaim_idx)) अणु
		हाल COMPACT_SUCCESS:
		हाल COMPACT_CONTINUE:
			वापस false;
		शेष:
			/* check next zone */
			;
		पूर्ण
	पूर्ण

	/*
	 * If we have not reclaimed enough pages क्रम compaction and the
	 * inactive lists are large enough, जारी reclaiming
	 */
	pages_क्रम_compaction = compact_gap(sc->order);
	inactive_lru_pages = node_page_state(pgdat, NR_INACTIVE_खाता);
	अगर (get_nr_swap_pages() > 0)
		inactive_lru_pages += node_page_state(pgdat, NR_INACTIVE_ANON);

	वापस inactive_lru_pages > pages_क्रम_compaction;
पूर्ण

अटल व्योम shrink_node_memcgs(pg_data_t *pgdat, काष्ठा scan_control *sc)
अणु
	काष्ठा mem_cgroup *target_memcg = sc->target_mem_cgroup;
	काष्ठा mem_cgroup *memcg;

	memcg = mem_cgroup_iter(target_memcg, शून्य, शून्य);
	करो अणु
		काष्ठा lruvec *lruvec = mem_cgroup_lruvec(memcg, pgdat);
		अचिन्हित दीर्घ reclaimed;
		अचिन्हित दीर्घ scanned;

		/*
		 * This loop can become CPU-bound when target memcgs
		 * aren't eligible क्रम reclaim - either because they
		 * करोn't have any reclaimable pages, or because their
		 * memory is explicitly रक्षित. Aव्योम soft lockups.
		 */
		cond_resched();

		mem_cgroup_calculate_protection(target_memcg, memcg);

		अगर (mem_cgroup_below_min(memcg)) अणु
			/*
			 * Hard protection.
			 * If there is no reclaimable memory, OOM.
			 */
			जारी;
		पूर्ण अन्यथा अगर (mem_cgroup_below_low(memcg)) अणु
			/*
			 * Soft protection.
			 * Respect the protection only as दीर्घ as
			 * there is an unरक्षित supply
			 * of reclaimable memory from other cgroups.
			 */
			अगर (!sc->memcg_low_reclaim) अणु
				sc->memcg_low_skipped = 1;
				जारी;
			पूर्ण
			memcg_memory_event(memcg, MEMCG_LOW);
		पूर्ण

		reclaimed = sc->nr_reclaimed;
		scanned = sc->nr_scanned;

		shrink_lruvec(lruvec, sc);

		shrink_slab(sc->gfp_mask, pgdat->node_id, memcg,
			    sc->priority);

		/* Record the group's reclaim efficiency */
		vmpressure(sc->gfp_mask, memcg, false,
			   sc->nr_scanned - scanned,
			   sc->nr_reclaimed - reclaimed);

	पूर्ण जबतक ((memcg = mem_cgroup_iter(target_memcg, memcg, शून्य)));
पूर्ण

अटल व्योम shrink_node(pg_data_t *pgdat, काष्ठा scan_control *sc)
अणु
	काष्ठा reclaim_state *reclaim_state = current->reclaim_state;
	अचिन्हित दीर्घ nr_reclaimed, nr_scanned;
	काष्ठा lruvec *target_lruvec;
	bool reclaimable = false;
	अचिन्हित दीर्घ file;

	target_lruvec = mem_cgroup_lruvec(sc->target_mem_cgroup, pgdat);

again:
	स_रखो(&sc->nr, 0, माप(sc->nr));

	nr_reclaimed = sc->nr_reclaimed;
	nr_scanned = sc->nr_scanned;

	/*
	 * Determine the scan balance between anon and file LRUs.
	 */
	spin_lock_irq(&target_lruvec->lru_lock);
	sc->anon_cost = target_lruvec->anon_cost;
	sc->file_cost = target_lruvec->file_cost;
	spin_unlock_irq(&target_lruvec->lru_lock);

	/*
	 * Target desirable inactive:active list ratios क्रम the anon
	 * and file LRU lists.
	 */
	अगर (!sc->क्रमce_deactivate) अणु
		अचिन्हित दीर्घ refaults;

		refaults = lruvec_page_state(target_lruvec,
				WORKINGSET_ACTIVATE_ANON);
		अगर (refaults != target_lruvec->refaults[0] ||
			inactive_is_low(target_lruvec, LRU_INACTIVE_ANON))
			sc->may_deactivate |= DEACTIVATE_ANON;
		अन्यथा
			sc->may_deactivate &= ~DEACTIVATE_ANON;

		/*
		 * When refaults are being observed, it means a new
		 * workingset is being established. Deactivate to get
		 * rid of any stale active pages quickly.
		 */
		refaults = lruvec_page_state(target_lruvec,
				WORKINGSET_ACTIVATE_खाता);
		अगर (refaults != target_lruvec->refaults[1] ||
		    inactive_is_low(target_lruvec, LRU_INACTIVE_खाता))
			sc->may_deactivate |= DEACTIVATE_खाता;
		अन्यथा
			sc->may_deactivate &= ~DEACTIVATE_खाता;
	पूर्ण अन्यथा
		sc->may_deactivate = DEACTIVATE_ANON | DEACTIVATE_खाता;

	/*
	 * If we have plenty of inactive file pages that aren't
	 * thrashing, try to reclaim those first beक्रमe touching
	 * anonymous pages.
	 */
	file = lruvec_page_state(target_lruvec, NR_INACTIVE_खाता);
	अगर (file >> sc->priority && !(sc->may_deactivate & DEACTIVATE_खाता))
		sc->cache_trim_mode = 1;
	अन्यथा
		sc->cache_trim_mode = 0;

	/*
	 * Prevent the reclaimer from falling पूर्णांकo the cache trap: as
	 * cache pages start out inactive, every cache fault will tip
	 * the scan balance towards the file LRU.  And as the file LRU
	 * shrinks, so करोes the winकरोw क्रम rotation from references.
	 * This means we have a runaway feedback loop where a tiny
	 * thrashing file LRU becomes infinitely more attractive than
	 * anon pages.  Try to detect this based on file LRU size.
	 */
	अगर (!cgroup_reclaim(sc)) अणु
		अचिन्हित दीर्घ total_high_wmark = 0;
		अचिन्हित दीर्घ मुक्त, anon;
		पूर्णांक z;

		मुक्त = sum_zone_node_page_state(pgdat->node_id, NR_FREE_PAGES);
		file = node_page_state(pgdat, NR_ACTIVE_खाता) +
			   node_page_state(pgdat, NR_INACTIVE_खाता);

		क्रम (z = 0; z < MAX_NR_ZONES; z++) अणु
			काष्ठा zone *zone = &pgdat->node_zones[z];
			अगर (!managed_zone(zone))
				जारी;

			total_high_wmark += high_wmark_pages(zone);
		पूर्ण

		/*
		 * Consider anon: अगर that's low too, this isn't a
		 * runaway file reclaim problem, but rather just
		 * extreme pressure. Reclaim as per usual then.
		 */
		anon = node_page_state(pgdat, NR_INACTIVE_ANON);

		sc->file_is_tiny =
			file + मुक्त <= total_high_wmark &&
			!(sc->may_deactivate & DEACTIVATE_ANON) &&
			anon >> sc->priority;
	पूर्ण

	shrink_node_memcgs(pgdat, sc);

	अगर (reclaim_state) अणु
		sc->nr_reclaimed += reclaim_state->reclaimed_slab;
		reclaim_state->reclaimed_slab = 0;
	पूर्ण

	/* Record the subtree's reclaim efficiency */
	vmpressure(sc->gfp_mask, sc->target_mem_cgroup, true,
		   sc->nr_scanned - nr_scanned,
		   sc->nr_reclaimed - nr_reclaimed);

	अगर (sc->nr_reclaimed - nr_reclaimed)
		reclaimable = true;

	अगर (current_is_kswapd()) अणु
		/*
		 * If reclaim is isolating dirty pages under ग_लिखोback,
		 * it implies that the दीर्घ-lived page allocation rate
		 * is exceeding the page laundering rate. Either the
		 * global limits are not being effective at throttling
		 * processes due to the page distribution throughout
		 * zones or there is heavy usage of a slow backing
		 * device. The only option is to throttle from reclaim
		 * context which is not ideal as there is no guarantee
		 * the dirtying process is throttled in the same way
		 * balance_dirty_pages() manages.
		 *
		 * Once a node is flagged PGDAT_WRITEBACK, kswapd will
		 * count the number of pages under pages flagged क्रम
		 * immediate reclaim and stall अगर any are encountered
		 * in the nr_immediate check below.
		 */
		अगर (sc->nr.ग_लिखोback && sc->nr.ग_लिखोback == sc->nr.taken)
			set_bit(PGDAT_WRITEBACK, &pgdat->flags);

		/* Allow kswapd to start writing pages during reclaim.*/
		अगर (sc->nr.unqueued_dirty == sc->nr.file_taken)
			set_bit(PGDAT_सूचीTY, &pgdat->flags);

		/*
		 * If kswapd scans pages marked क्रम immediate
		 * reclaim and under ग_लिखोback (nr_immediate), it
		 * implies that pages are cycling through the LRU
		 * faster than they are written so also क्रमcibly stall.
		 */
		अगर (sc->nr.immediate)
			congestion_रुको(BLK_RW_ASYNC, HZ/10);
	पूर्ण

	/*
	 * Tag a node/memcg as congested अगर all the dirty pages
	 * scanned were backed by a congested BDI and
	 * रुको_अगरf_congested will stall.
	 *
	 * Legacy memcg will stall in page ग_लिखोback so aव्योम क्रमcibly
	 * stalling in रुको_अगरf_congested().
	 */
	अगर ((current_is_kswapd() ||
	     (cgroup_reclaim(sc) && ग_लिखोback_throttling_sane(sc))) &&
	    sc->nr.dirty && sc->nr.dirty == sc->nr.congested)
		set_bit(LRUVEC_CONGESTED, &target_lruvec->flags);

	/*
	 * Stall direct reclaim क्रम IO completions अगर underlying BDIs
	 * and node is congested. Allow kswapd to जारी until it
	 * starts encountering unqueued dirty pages or cycling through
	 * the LRU too quickly.
	 */
	अगर (!current_is_kswapd() && current_may_throttle() &&
	    !sc->hibernation_mode &&
	    test_bit(LRUVEC_CONGESTED, &target_lruvec->flags))
		रुको_अगरf_congested(BLK_RW_ASYNC, HZ/10);

	अगर (should_जारी_reclaim(pgdat, sc->nr_reclaimed - nr_reclaimed,
				    sc))
		जाओ again;

	/*
	 * Kswapd gives up on balancing particular nodes after too
	 * many failures to reclaim anything from them and goes to
	 * sleep. On reclaim progress, reset the failure counter. A
	 * successful direct reclaim run will revive a करोrmant kswapd.
	 */
	अगर (reclaimable)
		pgdat->kswapd_failures = 0;
पूर्ण

/*
 * Returns true अगर compaction should go ahead क्रम a costly-order request, or
 * the allocation would alपढ़ोy succeed without compaction. Return false अगर we
 * should reclaim first.
 */
अटल अंतरभूत bool compaction_पढ़ोy(काष्ठा zone *zone, काष्ठा scan_control *sc)
अणु
	अचिन्हित दीर्घ watermark;
	क्रमागत compact_result suitable;

	suitable = compaction_suitable(zone, sc->order, 0, sc->reclaim_idx);
	अगर (suitable == COMPACT_SUCCESS)
		/* Allocation should succeed alपढ़ोy. Don't reclaim. */
		वापस true;
	अगर (suitable == COMPACT_SKIPPED)
		/* Compaction cannot yet proceed. Do reclaim. */
		वापस false;

	/*
	 * Compaction is alपढ़ोy possible, but it takes समय to run and there
	 * are potentially other callers using the pages just मुक्तd. So proceed
	 * with reclaim to make a buffer of मुक्त pages available to give
	 * compaction a reasonable chance of completing and allocating the page.
	 * Note that we won't actually reclaim the whole buffer in one attempt
	 * as the target watermark in should_जारी_reclaim() is lower. But अगर
	 * we are alपढ़ोy above the high+gap watermark, करोn't reclaim at all.
	 */
	watermark = high_wmark_pages(zone) + compact_gap(sc->order);

	वापस zone_watermark_ok_safe(zone, 0, watermark, sc->reclaim_idx);
पूर्ण

/*
 * This is the direct reclaim path, क्रम page-allocating processes.  We only
 * try to reclaim pages from zones which will satisfy the caller's allocation
 * request.
 *
 * If a zone is deemed to be full of pinned pages then just give it a light
 * scan then give up on it.
 */
अटल व्योम shrink_zones(काष्ठा zonelist *zonelist, काष्ठा scan_control *sc)
अणु
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	अचिन्हित दीर्घ nr_soft_reclaimed;
	अचिन्हित दीर्घ nr_soft_scanned;
	gfp_t orig_mask;
	pg_data_t *last_pgdat = शून्य;

	/*
	 * If the number of buffer_heads in the machine exceeds the maximum
	 * allowed level, क्रमce direct reclaim to scan the highmem zone as
	 * highmem pages could be pinning lowmem pages storing buffer_heads
	 */
	orig_mask = sc->gfp_mask;
	अगर (buffer_heads_over_limit) अणु
		sc->gfp_mask |= __GFP_HIGHMEM;
		sc->reclaim_idx = gfp_zone(sc->gfp_mask);
	पूर्ण

	क्रम_each_zone_zonelist_nodemask(zone, z, zonelist,
					sc->reclaim_idx, sc->nodemask) अणु
		/*
		 * Take care memory controller reclaiming has small influence
		 * to global LRU.
		 */
		अगर (!cgroup_reclaim(sc)) अणु
			अगर (!cpuset_zone_allowed(zone,
						 GFP_KERNEL | __GFP_HARDWALL))
				जारी;

			/*
			 * If we alपढ़ोy have plenty of memory मुक्त क्रम
			 * compaction in this zone, करोn't मुक्त any more.
			 * Even though compaction is invoked क्रम any
			 * non-zero order, only frequent costly order
			 * reclamation is disruptive enough to become a
			 * noticeable problem, like transparent huge
			 * page allocations.
			 */
			अगर (IS_ENABLED(CONFIG_COMPACTION) &&
			    sc->order > PAGE_ALLOC_COSTLY_ORDER &&
			    compaction_पढ़ोy(zone, sc)) अणु
				sc->compaction_पढ़ोy = true;
				जारी;
			पूर्ण

			/*
			 * Shrink each node in the zonelist once. If the
			 * zonelist is ordered by zone (not the शेष) then a
			 * node may be shrunk multiple बार but in that हाल
			 * the user prefers lower zones being preserved.
			 */
			अगर (zone->zone_pgdat == last_pgdat)
				जारी;

			/*
			 * This steals pages from memory cgroups over softlimit
			 * and वापसs the number of reclaimed pages and
			 * scanned pages. This works क्रम global memory pressure
			 * and balancing, not क्रम a memcg's limit.
			 */
			nr_soft_scanned = 0;
			nr_soft_reclaimed = mem_cgroup_soft_limit_reclaim(zone->zone_pgdat,
						sc->order, sc->gfp_mask,
						&nr_soft_scanned);
			sc->nr_reclaimed += nr_soft_reclaimed;
			sc->nr_scanned += nr_soft_scanned;
			/* need some check क्रम aव्योम more shrink_zone() */
		पूर्ण

		/* See comment about same check क्रम global reclaim above */
		अगर (zone->zone_pgdat == last_pgdat)
			जारी;
		last_pgdat = zone->zone_pgdat;
		shrink_node(zone->zone_pgdat, sc);
	पूर्ण

	/*
	 * Restore to original mask to aव्योम the impact on the caller अगर we
	 * promoted it to __GFP_HIGHMEM.
	 */
	sc->gfp_mask = orig_mask;
पूर्ण

अटल व्योम snapshot_refaults(काष्ठा mem_cgroup *target_memcg, pg_data_t *pgdat)
अणु
	काष्ठा lruvec *target_lruvec;
	अचिन्हित दीर्घ refaults;

	target_lruvec = mem_cgroup_lruvec(target_memcg, pgdat);
	refaults = lruvec_page_state(target_lruvec, WORKINGSET_ACTIVATE_ANON);
	target_lruvec->refaults[0] = refaults;
	refaults = lruvec_page_state(target_lruvec, WORKINGSET_ACTIVATE_खाता);
	target_lruvec->refaults[1] = refaults;
पूर्ण

/*
 * This is the मुख्य entry poपूर्णांक to direct page reclaim.
 *
 * If a full scan of the inactive list fails to मुक्त enough memory then we
 * are "out of memory" and something needs to be समाप्तed.
 *
 * If the caller is !__GFP_FS then the probability of a failure is reasonably
 * high - the zone may be full of dirty or under-ग_लिखोback pages, which this
 * caller can't करो much about.  We kick the ग_लिखोback thपढ़ोs and take explicit
 * naps in the hope that some of these pages can be written.  But अगर the
 * allocating task holds fileप्रणाली locks which prevent ग_लिखोout this might not
 * work, and the allocation attempt will fail.
 *
 * वापसs:	0, अगर no pages reclaimed
 * 		अन्यथा, the number of pages reclaimed
 */
अटल अचिन्हित दीर्घ करो_try_to_मुक्त_pages(काष्ठा zonelist *zonelist,
					  काष्ठा scan_control *sc)
अणु
	पूर्णांक initial_priority = sc->priority;
	pg_data_t *last_pgdat;
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
retry:
	delayacct_मुक्तpages_start();

	अगर (!cgroup_reclaim(sc))
		__count_zid_vm_events(ALLOCSTALL, sc->reclaim_idx, 1);

	करो अणु
		vmpressure_prio(sc->gfp_mask, sc->target_mem_cgroup,
				sc->priority);
		sc->nr_scanned = 0;
		shrink_zones(zonelist, sc);

		अगर (sc->nr_reclaimed >= sc->nr_to_reclaim)
			अवरोध;

		अगर (sc->compaction_पढ़ोy)
			अवरोध;

		/*
		 * If we're getting trouble reclaiming, start करोing
		 * ग_लिखोpage even in laptop mode.
		 */
		अगर (sc->priority < DEF_PRIORITY - 2)
			sc->may_ग_लिखोpage = 1;
	पूर्ण जबतक (--sc->priority >= 0);

	last_pgdat = शून्य;
	क्रम_each_zone_zonelist_nodemask(zone, z, zonelist, sc->reclaim_idx,
					sc->nodemask) अणु
		अगर (zone->zone_pgdat == last_pgdat)
			जारी;
		last_pgdat = zone->zone_pgdat;

		snapshot_refaults(sc->target_mem_cgroup, zone->zone_pgdat);

		अगर (cgroup_reclaim(sc)) अणु
			काष्ठा lruvec *lruvec;

			lruvec = mem_cgroup_lruvec(sc->target_mem_cgroup,
						   zone->zone_pgdat);
			clear_bit(LRUVEC_CONGESTED, &lruvec->flags);
		पूर्ण
	पूर्ण

	delayacct_मुक्तpages_end();

	अगर (sc->nr_reclaimed)
		वापस sc->nr_reclaimed;

	/* Aborted reclaim to try compaction? करोn't OOM, then */
	अगर (sc->compaction_पढ़ोy)
		वापस 1;

	/*
	 * We make inactive:active ratio decisions based on the node's
	 * composition of memory, but a restrictive reclaim_idx or a
	 * memory.low cgroup setting can exempt large amounts of
	 * memory from reclaim. Neither of which are very common, so
	 * instead of करोing costly eligibility calculations of the
	 * entire cgroup subtree up front, we assume the estimates are
	 * good, and retry with क्रमcible deactivation अगर that fails.
	 */
	अगर (sc->skipped_deactivate) अणु
		sc->priority = initial_priority;
		sc->क्रमce_deactivate = 1;
		sc->skipped_deactivate = 0;
		जाओ retry;
	पूर्ण

	/* Untapped cgroup reserves?  Don't OOM, retry. */
	अगर (sc->memcg_low_skipped) अणु
		sc->priority = initial_priority;
		sc->क्रमce_deactivate = 0;
		sc->memcg_low_reclaim = 1;
		sc->memcg_low_skipped = 0;
		जाओ retry;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool allow_direct_reclaim(pg_data_t *pgdat)
अणु
	काष्ठा zone *zone;
	अचिन्हित दीर्घ pfmeदो_स्मृति_reserve = 0;
	अचिन्हित दीर्घ मुक्त_pages = 0;
	पूर्णांक i;
	bool wmark_ok;

	अगर (pgdat->kswapd_failures >= MAX_RECLAIM_RETRIES)
		वापस true;

	क्रम (i = 0; i <= ZONE_NORMAL; i++) अणु
		zone = &pgdat->node_zones[i];
		अगर (!managed_zone(zone))
			जारी;

		अगर (!zone_reclaimable_pages(zone))
			जारी;

		pfmeदो_स्मृति_reserve += min_wmark_pages(zone);
		मुक्त_pages += zone_page_state(zone, NR_FREE_PAGES);
	पूर्ण

	/* If there are no reserves (unexpected config) then करो not throttle */
	अगर (!pfmeदो_स्मृति_reserve)
		वापस true;

	wmark_ok = मुक्त_pages > pfmeदो_स्मृति_reserve / 2;

	/* kswapd must be awake अगर processes are being throttled */
	अगर (!wmark_ok && रुकोqueue_active(&pgdat->kswapd_रुको)) अणु
		अगर (READ_ONCE(pgdat->kswapd_highest_zoneidx) > ZONE_NORMAL)
			WRITE_ONCE(pgdat->kswapd_highest_zoneidx, ZONE_NORMAL);

		wake_up_पूर्णांकerruptible(&pgdat->kswapd_रुको);
	पूर्ण

	वापस wmark_ok;
पूर्ण

/*
 * Throttle direct reclaimers अगर backing storage is backed by the network
 * and the PFMEMALLOC reserve क्रम the preferred node is getting dangerously
 * depleted. kswapd will जारी to make progress and wake the processes
 * when the low watermark is reached.
 *
 * Returns true अगर a fatal संकेत was delivered during throttling. If this
 * happens, the page allocator should not consider triggering the OOM समाप्तer.
 */
अटल bool throttle_direct_reclaim(gfp_t gfp_mask, काष्ठा zonelist *zonelist,
					nodemask_t *nodemask)
अणु
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	pg_data_t *pgdat = शून्य;

	/*
	 * Kernel thपढ़ोs should not be throttled as they may be indirectly
	 * responsible क्रम cleaning pages necessary क्रम reclaim to make क्रमward
	 * progress. kjournald क्रम example may enter direct reclaim जबतक
	 * committing a transaction where throttling it could क्रमcing other
	 * processes to block on log_रुको_commit().
	 */
	अगर (current->flags & PF_KTHREAD)
		जाओ out;

	/*
	 * If a fatal संकेत is pending, this process should not throttle.
	 * It should वापस quickly so it can निकास and मुक्त its memory
	 */
	अगर (fatal_संकेत_pending(current))
		जाओ out;

	/*
	 * Check अगर the pfmeदो_स्मृति reserves are ok by finding the first node
	 * with a usable ZONE_NORMAL or lower zone. The expectation is that
	 * GFP_KERNEL will be required क्रम allocating network buffers when
	 * swapping over the network so ZONE_HIGHMEM is unusable.
	 *
	 * Throttling is based on the first usable node and throttled processes
	 * रुको on a queue until kswapd makes progress and wakes them. There
	 * is an affinity then between processes waking up and where reclaim
	 * progress has been made assuming the process wakes on the same node.
	 * More importantly, processes running on remote nodes will not compete
	 * क्रम remote pfmeदो_स्मृति reserves and processes on dअगरferent nodes
	 * should make reasonable progress.
	 */
	क्रम_each_zone_zonelist_nodemask(zone, z, zonelist,
					gfp_zone(gfp_mask), nodemask) अणु
		अगर (zone_idx(zone) > ZONE_NORMAL)
			जारी;

		/* Throttle based on the first usable node */
		pgdat = zone->zone_pgdat;
		अगर (allow_direct_reclaim(pgdat))
			जाओ out;
		अवरोध;
	पूर्ण

	/* If no zone was usable by the allocation flags then करो not throttle */
	अगर (!pgdat)
		जाओ out;

	/* Account क्रम the throttling */
	count_vm_event(PGSCAN_सूचीECT_THROTTLE);

	/*
	 * If the caller cannot enter the fileप्रणाली, it's possible that it
	 * is due to the caller holding an FS lock or perक्रमming a journal
	 * transaction in the हाल of a fileप्रणाली like ext[3|4]. In this हाल,
	 * it is not safe to block on pfmeदो_स्मृति_रुको as kswapd could be
	 * blocked रुकोing on the same lock. Instead, throttle क्रम up to a
	 * second beक्रमe continuing.
	 */
	अगर (!(gfp_mask & __GFP_FS)) अणु
		रुको_event_पूर्णांकerruptible_समयout(pgdat->pfmeदो_स्मृति_रुको,
			allow_direct_reclaim(pgdat), HZ);

		जाओ check_pending;
	पूर्ण

	/* Throttle until kswapd wakes the process */
	रुको_event_समाप्तable(zone->zone_pgdat->pfmeदो_स्मृति_रुको,
		allow_direct_reclaim(pgdat));

check_pending:
	अगर (fatal_संकेत_pending(current))
		वापस true;

out:
	वापस false;
पूर्ण

अचिन्हित दीर्घ try_to_मुक्त_pages(काष्ठा zonelist *zonelist, पूर्णांक order,
				gfp_t gfp_mask, nodemask_t *nodemask)
अणु
	अचिन्हित दीर्घ nr_reclaimed;
	काष्ठा scan_control sc = अणु
		.nr_to_reclaim = SWAP_CLUSTER_MAX,
		.gfp_mask = current_gfp_context(gfp_mask),
		.reclaim_idx = gfp_zone(gfp_mask),
		.order = order,
		.nodemask = nodemask,
		.priority = DEF_PRIORITY,
		.may_ग_लिखोpage = !laptop_mode,
		.may_unmap = 1,
		.may_swap = 1,
	पूर्ण;

	/*
	 * scan_control uses s8 fields क्रम order, priority, and reclaim_idx.
	 * Confirm they are large enough क्रम max values.
	 */
	BUILD_BUG_ON(MAX_ORDER > S8_MAX);
	BUILD_BUG_ON(DEF_PRIORITY > S8_MAX);
	BUILD_BUG_ON(MAX_NR_ZONES > S8_MAX);

	/*
	 * Do not enter reclaim अगर fatal संकेत was delivered जबतक throttled.
	 * 1 is वापसed so that the page allocator करोes not OOM समाप्त at this
	 * poपूर्णांक.
	 */
	अगर (throttle_direct_reclaim(sc.gfp_mask, zonelist, nodemask))
		वापस 1;

	set_task_reclaim_state(current, &sc.reclaim_state);
	trace_mm_vmscan_direct_reclaim_begin(order, sc.gfp_mask);

	nr_reclaimed = करो_try_to_मुक्त_pages(zonelist, &sc);

	trace_mm_vmscan_direct_reclaim_end(nr_reclaimed);
	set_task_reclaim_state(current, शून्य);

	वापस nr_reclaimed;
पूर्ण

#अगर_घोषित CONFIG_MEMCG

/* Only used by soft limit reclaim. Do not reuse क्रम anything अन्यथा. */
अचिन्हित दीर्घ mem_cgroup_shrink_node(काष्ठा mem_cgroup *memcg,
						gfp_t gfp_mask, bool noswap,
						pg_data_t *pgdat,
						अचिन्हित दीर्घ *nr_scanned)
अणु
	काष्ठा lruvec *lruvec = mem_cgroup_lruvec(memcg, pgdat);
	काष्ठा scan_control sc = अणु
		.nr_to_reclaim = SWAP_CLUSTER_MAX,
		.target_mem_cgroup = memcg,
		.may_ग_लिखोpage = !laptop_mode,
		.may_unmap = 1,
		.reclaim_idx = MAX_NR_ZONES - 1,
		.may_swap = !noswap,
	पूर्ण;

	WARN_ON_ONCE(!current->reclaim_state);

	sc.gfp_mask = (gfp_mask & GFP_RECLAIM_MASK) |
			(GFP_HIGHUSER_MOVABLE & ~GFP_RECLAIM_MASK);

	trace_mm_vmscan_memcg_softlimit_reclaim_begin(sc.order,
						      sc.gfp_mask);

	/*
	 * NOTE: Although we can get the priority field, using it
	 * here is not a good idea, since it limits the pages we can scan.
	 * अगर we करोn't reclaim here, the shrink_node from balance_pgdat
	 * will pick up pages from other mem cgroup's as well. We hack
	 * the priority and make it zero.
	 */
	shrink_lruvec(lruvec, &sc);

	trace_mm_vmscan_memcg_softlimit_reclaim_end(sc.nr_reclaimed);

	*nr_scanned = sc.nr_scanned;

	वापस sc.nr_reclaimed;
पूर्ण

अचिन्हित दीर्घ try_to_मुक्त_mem_cgroup_pages(काष्ठा mem_cgroup *memcg,
					   अचिन्हित दीर्घ nr_pages,
					   gfp_t gfp_mask,
					   bool may_swap)
अणु
	अचिन्हित दीर्घ nr_reclaimed;
	अचिन्हित पूर्णांक noreclaim_flag;
	काष्ठा scan_control sc = अणु
		.nr_to_reclaim = max(nr_pages, SWAP_CLUSTER_MAX),
		.gfp_mask = (current_gfp_context(gfp_mask) & GFP_RECLAIM_MASK) |
				(GFP_HIGHUSER_MOVABLE & ~GFP_RECLAIM_MASK),
		.reclaim_idx = MAX_NR_ZONES - 1,
		.target_mem_cgroup = memcg,
		.priority = DEF_PRIORITY,
		.may_ग_लिखोpage = !laptop_mode,
		.may_unmap = 1,
		.may_swap = may_swap,
	पूर्ण;
	/*
	 * Traverse the ZONELIST_FALLBACK zonelist of the current node to put
	 * equal pressure on all the nodes. This is based on the assumption that
	 * the reclaim करोes not bail out early.
	 */
	काष्ठा zonelist *zonelist = node_zonelist(numa_node_id(), sc.gfp_mask);

	set_task_reclaim_state(current, &sc.reclaim_state);
	trace_mm_vmscan_memcg_reclaim_begin(0, sc.gfp_mask);
	noreclaim_flag = meदो_स्मृति_noreclaim_save();

	nr_reclaimed = करो_try_to_मुक्त_pages(zonelist, &sc);

	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	trace_mm_vmscan_memcg_reclaim_end(nr_reclaimed);
	set_task_reclaim_state(current, शून्य);

	वापस nr_reclaimed;
पूर्ण
#पूर्ण_अगर

अटल व्योम age_active_anon(काष्ठा pglist_data *pgdat,
				काष्ठा scan_control *sc)
अणु
	काष्ठा mem_cgroup *memcg;
	काष्ठा lruvec *lruvec;

	अगर (!total_swap_pages)
		वापस;

	lruvec = mem_cgroup_lruvec(शून्य, pgdat);
	अगर (!inactive_is_low(lruvec, LRU_INACTIVE_ANON))
		वापस;

	memcg = mem_cgroup_iter(शून्य, शून्य, शून्य);
	करो अणु
		lruvec = mem_cgroup_lruvec(memcg, pgdat);
		shrink_active_list(SWAP_CLUSTER_MAX, lruvec,
				   sc, LRU_ACTIVE_ANON);
		memcg = mem_cgroup_iter(शून्य, memcg, शून्य);
	पूर्ण जबतक (memcg);
पूर्ण

अटल bool pgdat_watermark_boosted(pg_data_t *pgdat, पूर्णांक highest_zoneidx)
अणु
	पूर्णांक i;
	काष्ठा zone *zone;

	/*
	 * Check क्रम watermark boosts top-करोwn as the higher zones
	 * are more likely to be boosted. Both watermarks and boosts
	 * should not be checked at the same समय as reclaim would
	 * start prematurely when there is no boosting and a lower
	 * zone is balanced.
	 */
	क्रम (i = highest_zoneidx; i >= 0; i--) अणु
		zone = pgdat->node_zones + i;
		अगर (!managed_zone(zone))
			जारी;

		अगर (zone->watermark_boost)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Returns true अगर there is an eligible zone balanced क्रम the request order
 * and highest_zoneidx
 */
अटल bool pgdat_balanced(pg_data_t *pgdat, पूर्णांक order, पूर्णांक highest_zoneidx)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ mark = -1;
	काष्ठा zone *zone;

	/*
	 * Check watermarks bottom-up as lower zones are more likely to
	 * meet watermarks.
	 */
	क्रम (i = 0; i <= highest_zoneidx; i++) अणु
		zone = pgdat->node_zones + i;

		अगर (!managed_zone(zone))
			जारी;

		mark = high_wmark_pages(zone);
		अगर (zone_watermark_ok_safe(zone, order, mark, highest_zoneidx))
			वापस true;
	पूर्ण

	/*
	 * If a node has no populated zone within highest_zoneidx, it करोes not
	 * need balancing by definition. This can happen अगर a zone-restricted
	 * allocation tries to wake a remote kswapd.
	 */
	अगर (mark == -1)
		वापस true;

	वापस false;
पूर्ण

/* Clear pgdat state क्रम congested, dirty or under ग_लिखोback. */
अटल व्योम clear_pgdat_congested(pg_data_t *pgdat)
अणु
	काष्ठा lruvec *lruvec = mem_cgroup_lruvec(शून्य, pgdat);

	clear_bit(LRUVEC_CONGESTED, &lruvec->flags);
	clear_bit(PGDAT_सूचीTY, &pgdat->flags);
	clear_bit(PGDAT_WRITEBACK, &pgdat->flags);
पूर्ण

/*
 * Prepare kswapd क्रम sleeping. This verअगरies that there are no processes
 * रुकोing in throttle_direct_reclaim() and that watermarks have been met.
 *
 * Returns true अगर kswapd is पढ़ोy to sleep
 */
अटल bool prepare_kswapd_sleep(pg_data_t *pgdat, पूर्णांक order,
				पूर्णांक highest_zoneidx)
अणु
	/*
	 * The throttled processes are normally woken up in balance_pgdat() as
	 * soon as allow_direct_reclaim() is true. But there is a potential
	 * race between when kswapd checks the watermarks and a process माला_लो
	 * throttled. There is also a potential race अगर processes get
	 * throttled, kswapd wakes, a large process निकासs thereby balancing the
	 * zones, which causes kswapd to निकास balance_pgdat() beक्रमe reaching
	 * the wake up checks. If kswapd is going to sleep, no process should
	 * be sleeping on pfmeदो_स्मृति_रुको, so wake them now अगर necessary. If
	 * the wake up is premature, processes will wake kswapd and get
	 * throttled again. The dअगरference from wake ups in balance_pgdat() is
	 * that here we are under prepare_to_रुको().
	 */
	अगर (रुकोqueue_active(&pgdat->pfmeदो_स्मृति_रुको))
		wake_up_all(&pgdat->pfmeदो_स्मृति_रुको);

	/* Hopeless node, leave it to direct reclaim */
	अगर (pgdat->kswapd_failures >= MAX_RECLAIM_RETRIES)
		वापस true;

	अगर (pgdat_balanced(pgdat, order, highest_zoneidx)) अणु
		clear_pgdat_congested(pgdat);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * kswapd shrinks a node of pages that are at or below the highest usable
 * zone that is currently unbalanced.
 *
 * Returns true अगर kswapd scanned at least the requested number of pages to
 * reclaim or अगर the lack of progress was due to pages under ग_लिखोback.
 * This is used to determine अगर the scanning priority needs to be उठाओd.
 */
अटल bool kswapd_shrink_node(pg_data_t *pgdat,
			       काष्ठा scan_control *sc)
अणु
	काष्ठा zone *zone;
	पूर्णांक z;

	/* Reclaim a number of pages proportional to the number of zones */
	sc->nr_to_reclaim = 0;
	क्रम (z = 0; z <= sc->reclaim_idx; z++) अणु
		zone = pgdat->node_zones + z;
		अगर (!managed_zone(zone))
			जारी;

		sc->nr_to_reclaim += max(high_wmark_pages(zone), SWAP_CLUSTER_MAX);
	पूर्ण

	/*
	 * Historically care was taken to put equal pressure on all zones but
	 * now pressure is applied based on node LRU order.
	 */
	shrink_node(pgdat, sc);

	/*
	 * Fragmentation may mean that the प्रणाली cannot be rebalanced क्रम
	 * high-order allocations. If twice the allocation size has been
	 * reclaimed then recheck watermarks only at order-0 to prevent
	 * excessive reclaim. Assume that a process requested a high-order
	 * can direct reclaim/compact.
	 */
	अगर (sc->order && sc->nr_reclaimed >= compact_gap(sc->order))
		sc->order = 0;

	वापस sc->nr_scanned >= sc->nr_to_reclaim;
पूर्ण

/*
 * For kswapd, balance_pgdat() will reclaim pages across a node from zones
 * that are eligible क्रम use by the caller until at least one zone is
 * balanced.
 *
 * Returns the order kswapd finished reclaiming at.
 *
 * kswapd scans the zones in the highmem->normal->dma direction.  It skips
 * zones which have मुक्त_pages > high_wmark_pages(zone), but once a zone is
 * found to have मुक्त_pages <= high_wmark_pages(zone), any page in that zone
 * or lower is eligible क्रम reclaim until at least one usable zone is
 * balanced.
 */
अटल पूर्णांक balance_pgdat(pg_data_t *pgdat, पूर्णांक order, पूर्णांक highest_zoneidx)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ nr_soft_reclaimed;
	अचिन्हित दीर्घ nr_soft_scanned;
	अचिन्हित दीर्घ pflags;
	अचिन्हित दीर्घ nr_boost_reclaim;
	अचिन्हित दीर्घ zone_boosts[MAX_NR_ZONES] = अणु 0, पूर्ण;
	bool boosted;
	काष्ठा zone *zone;
	काष्ठा scan_control sc = अणु
		.gfp_mask = GFP_KERNEL,
		.order = order,
		.may_unmap = 1,
	पूर्ण;

	set_task_reclaim_state(current, &sc.reclaim_state);
	psi_memstall_enter(&pflags);
	__fs_reclaim_acquire();

	count_vm_event(PAGEOUTRUN);

	/*
	 * Account क्रम the reclaim boost. Note that the zone boost is left in
	 * place so that parallel allocations that are near the watermark will
	 * stall or direct reclaim until kswapd is finished.
	 */
	nr_boost_reclaim = 0;
	क्रम (i = 0; i <= highest_zoneidx; i++) अणु
		zone = pgdat->node_zones + i;
		अगर (!managed_zone(zone))
			जारी;

		nr_boost_reclaim += zone->watermark_boost;
		zone_boosts[i] = zone->watermark_boost;
	पूर्ण
	boosted = nr_boost_reclaim;

restart:
	sc.priority = DEF_PRIORITY;
	करो अणु
		अचिन्हित दीर्घ nr_reclaimed = sc.nr_reclaimed;
		bool उठाओ_priority = true;
		bool balanced;
		bool ret;

		sc.reclaim_idx = highest_zoneidx;

		/*
		 * If the number of buffer_heads exceeds the maximum allowed
		 * then consider reclaiming from all zones. This has a dual
		 * purpose -- on 64-bit प्रणालीs it is expected that
		 * buffer_heads are stripped during active rotation. On 32-bit
		 * प्रणालीs, highmem pages can pin lowmem memory and shrinking
		 * buffers can relieve lowmem pressure. Reclaim may still not
		 * go ahead अगर all eligible zones क्रम the original allocation
		 * request are balanced to aव्योम excessive reclaim from kswapd.
		 */
		अगर (buffer_heads_over_limit) अणु
			क्रम (i = MAX_NR_ZONES - 1; i >= 0; i--) अणु
				zone = pgdat->node_zones + i;
				अगर (!managed_zone(zone))
					जारी;

				sc.reclaim_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * If the pgdat is imbalanced then ignore boosting and preserve
		 * the watermarks क्रम a later समय and restart. Note that the
		 * zone watermarks will be still reset at the end of balancing
		 * on the grounds that the normal reclaim should be enough to
		 * re-evaluate अगर boosting is required when kswapd next wakes.
		 */
		balanced = pgdat_balanced(pgdat, sc.order, highest_zoneidx);
		अगर (!balanced && nr_boost_reclaim) अणु
			nr_boost_reclaim = 0;
			जाओ restart;
		पूर्ण

		/*
		 * If boosting is not active then only reclaim अगर there are no
		 * eligible zones. Note that sc.reclaim_idx is not used as
		 * buffer_heads_over_limit may have adjusted it.
		 */
		अगर (!nr_boost_reclaim && balanced)
			जाओ out;

		/* Limit the priority of boosting to aव्योम reclaim ग_लिखोback */
		अगर (nr_boost_reclaim && sc.priority == DEF_PRIORITY - 2)
			उठाओ_priority = false;

		/*
		 * Do not ग_लिखोback or swap pages क्रम boosted reclaim. The
		 * पूर्णांकent is to relieve pressure not issue sub-optimal IO
		 * from reclaim context. If no pages are reclaimed, the
		 * reclaim will be पातed.
		 */
		sc.may_ग_लिखोpage = !laptop_mode && !nr_boost_reclaim;
		sc.may_swap = !nr_boost_reclaim;

		/*
		 * Do some background aging of the anon list, to give
		 * pages a chance to be referenced beक्रमe reclaiming. All
		 * pages are rotated regardless of classzone as this is
		 * about consistent aging.
		 */
		age_active_anon(pgdat, &sc);

		/*
		 * If we're getting trouble reclaiming, start करोing ग_लिखोpage
		 * even in laptop mode.
		 */
		अगर (sc.priority < DEF_PRIORITY - 2)
			sc.may_ग_लिखोpage = 1;

		/* Call soft limit reclaim beक्रमe calling shrink_node. */
		sc.nr_scanned = 0;
		nr_soft_scanned = 0;
		nr_soft_reclaimed = mem_cgroup_soft_limit_reclaim(pgdat, sc.order,
						sc.gfp_mask, &nr_soft_scanned);
		sc.nr_reclaimed += nr_soft_reclaimed;

		/*
		 * There should be no need to उठाओ the scanning priority अगर
		 * enough pages are alपढ़ोy being scanned that that high
		 * watermark would be met at 100% efficiency.
		 */
		अगर (kswapd_shrink_node(pgdat, &sc))
			उठाओ_priority = false;

		/*
		 * If the low watermark is met there is no need क्रम processes
		 * to be throttled on pfmeदो_स्मृति_रुको as they should not be
		 * able to safely make क्रमward progress. Wake them
		 */
		अगर (रुकोqueue_active(&pgdat->pfmeदो_स्मृति_रुको) &&
				allow_direct_reclaim(pgdat))
			wake_up_all(&pgdat->pfmeदो_स्मृति_रुको);

		/* Check अगर kswapd should be suspending */
		__fs_reclaim_release();
		ret = try_to_मुक्तze();
		__fs_reclaim_acquire();
		अगर (ret || kthपढ़ो_should_stop())
			अवरोध;

		/*
		 * Raise priority अगर scanning rate is too low or there was no
		 * progress in reclaiming pages
		 */
		nr_reclaimed = sc.nr_reclaimed - nr_reclaimed;
		nr_boost_reclaim -= min(nr_boost_reclaim, nr_reclaimed);

		/*
		 * If reclaim made no progress क्रम a boost, stop reclaim as
		 * IO cannot be queued and it could be an infinite loop in
		 * extreme circumstances.
		 */
		अगर (nr_boost_reclaim && !nr_reclaimed)
			अवरोध;

		अगर (उठाओ_priority || !nr_reclaimed)
			sc.priority--;
	पूर्ण जबतक (sc.priority >= 1);

	अगर (!sc.nr_reclaimed)
		pgdat->kswapd_failures++;

out:
	/* If reclaim was boosted, account क्रम the reclaim करोne in this pass */
	अगर (boosted) अणु
		अचिन्हित दीर्घ flags;

		क्रम (i = 0; i <= highest_zoneidx; i++) अणु
			अगर (!zone_boosts[i])
				जारी;

			/* Increments are under the zone lock */
			zone = pgdat->node_zones + i;
			spin_lock_irqsave(&zone->lock, flags);
			zone->watermark_boost -= min(zone->watermark_boost, zone_boosts[i]);
			spin_unlock_irqrestore(&zone->lock, flags);
		पूर्ण

		/*
		 * As there is now likely space, wakeup kcompact to defragment
		 * pageblocks.
		 */
		wakeup_kcompactd(pgdat, pageblock_order, highest_zoneidx);
	पूर्ण

	snapshot_refaults(शून्य, pgdat);
	__fs_reclaim_release();
	psi_memstall_leave(&pflags);
	set_task_reclaim_state(current, शून्य);

	/*
	 * Return the order kswapd stopped reclaiming at as
	 * prepare_kswapd_sleep() takes it पूर्णांकo account. If another caller
	 * entered the allocator slow path जबतक kswapd was awake, order will
	 * reमुख्य at the higher level.
	 */
	वापस sc.order;
पूर्ण

/*
 * The pgdat->kswapd_highest_zoneidx is used to pass the highest zone index to
 * be reclaimed by kswapd from the waker. If the value is MAX_NR_ZONES which is
 * not a valid index then either kswapd runs क्रम first समय or kswapd couldn't
 * sleep after previous reclaim attempt (node is still unbalanced). In that
 * हाल वापस the zone index of the previous kswapd reclaim cycle.
 */
अटल क्रमागत zone_type kswapd_highest_zoneidx(pg_data_t *pgdat,
					   क्रमागत zone_type prev_highest_zoneidx)
अणु
	क्रमागत zone_type curr_idx = READ_ONCE(pgdat->kswapd_highest_zoneidx);

	वापस curr_idx == MAX_NR_ZONES ? prev_highest_zoneidx : curr_idx;
पूर्ण

अटल व्योम kswapd_try_to_sleep(pg_data_t *pgdat, पूर्णांक alloc_order, पूर्णांक reclaim_order,
				अचिन्हित पूर्णांक highest_zoneidx)
अणु
	दीर्घ reमुख्यing = 0;
	DEFINE_WAIT(रुको);

	अगर (मुक्तzing(current) || kthपढ़ो_should_stop())
		वापस;

	prepare_to_रुको(&pgdat->kswapd_रुको, &रुको, TASK_INTERRUPTIBLE);

	/*
	 * Try to sleep क्रम a लघु पूर्णांकerval. Note that kcompactd will only be
	 * woken अगर it is possible to sleep क्रम a लघु पूर्णांकerval. This is
	 * deliberate on the assumption that अगर reclaim cannot keep an
	 * eligible zone balanced that it's also unlikely that compaction will
	 * succeed.
	 */
	अगर (prepare_kswapd_sleep(pgdat, reclaim_order, highest_zoneidx)) अणु
		/*
		 * Compaction records what page blocks it recently failed to
		 * isolate pages from and skips them in the future scanning.
		 * When kswapd is going to sleep, it is reasonable to assume
		 * that pages and compaction may succeed so reset the cache.
		 */
		reset_isolation_suitable(pgdat);

		/*
		 * We have मुक्तd the memory, now we should compact it to make
		 * allocation of the requested order possible.
		 */
		wakeup_kcompactd(pgdat, alloc_order, highest_zoneidx);

		reमुख्यing = schedule_समयout(HZ/10);

		/*
		 * If woken prematurely then reset kswapd_highest_zoneidx and
		 * order. The values will either be from a wakeup request or
		 * the previous request that slept prematurely.
		 */
		अगर (reमुख्यing) अणु
			WRITE_ONCE(pgdat->kswapd_highest_zoneidx,
					kswapd_highest_zoneidx(pgdat,
							highest_zoneidx));

			अगर (READ_ONCE(pgdat->kswapd_order) < reclaim_order)
				WRITE_ONCE(pgdat->kswapd_order, reclaim_order);
		पूर्ण

		finish_रुको(&pgdat->kswapd_रुको, &रुको);
		prepare_to_रुको(&pgdat->kswapd_रुको, &रुको, TASK_INTERRUPTIBLE);
	पूर्ण

	/*
	 * After a लघु sleep, check अगर it was a premature sleep. If not, then
	 * go fully to sleep until explicitly woken up.
	 */
	अगर (!reमुख्यing &&
	    prepare_kswapd_sleep(pgdat, reclaim_order, highest_zoneidx)) अणु
		trace_mm_vmscan_kswapd_sleep(pgdat->node_id);

		/*
		 * vmstat counters are not perfectly accurate and the estimated
		 * value क्रम counters such as NR_FREE_PAGES can deviate from the
		 * true value by nr_online_cpus * threshold. To aव्योम the zone
		 * watermarks being breached जबतक under pressure, we reduce the
		 * per-cpu vmstat threshold जबतक kswapd is awake and restore
		 * them beक्रमe going back to sleep.
		 */
		set_pgdat_percpu_threshold(pgdat, calculate_normal_threshold);

		अगर (!kthपढ़ो_should_stop())
			schedule();

		set_pgdat_percpu_threshold(pgdat, calculate_pressure_threshold);
	पूर्ण अन्यथा अणु
		अगर (reमुख्यing)
			count_vm_event(KSWAPD_LOW_WMARK_HIT_QUICKLY);
		अन्यथा
			count_vm_event(KSWAPD_HIGH_WMARK_HIT_QUICKLY);
	पूर्ण
	finish_रुको(&pgdat->kswapd_रुको, &रुको);
पूर्ण

/*
 * The background pageout daemon, started as a kernel thपढ़ो
 * from the init process.
 *
 * This basically trickles out pages so that we have _some_
 * मुक्त memory available even अगर there is no other activity
 * that मुक्तs anything up. This is needed क्रम things like routing
 * etc, where we otherwise might have all activity going on in
 * asynchronous contexts that cannot page things out.
 *
 * If there are applications that are active memory-allocators
 * (most normal use), this basically shouldn't matter.
 */
अटल पूर्णांक kswapd(व्योम *p)
अणु
	अचिन्हित पूर्णांक alloc_order, reclaim_order;
	अचिन्हित पूर्णांक highest_zoneidx = MAX_NR_ZONES - 1;
	pg_data_t *pgdat = (pg_data_t *)p;
	काष्ठा task_काष्ठा *tsk = current;
	स्थिर काष्ठा cpumask *cpumask = cpumask_of_node(pgdat->node_id);

	अगर (!cpumask_empty(cpumask))
		set_cpus_allowed_ptr(tsk, cpumask);

	/*
	 * Tell the memory management that we're a "memory allocator",
	 * and that अगर we need more memory we should get access to it
	 * regardless (see "__alloc_pages()"). "kswapd" should
	 * never get caught in the normal page मुक्तing logic.
	 *
	 * (Kswapd normally करोesn't need memory anyway, but someबार
	 * you need a small amount of memory in order to be able to
	 * page out something अन्यथा, and this flag essentially protects
	 * us from recursively trying to मुक्त more memory as we're
	 * trying to मुक्त the first piece of memory in the first place).
	 */
	tsk->flags |= PF_MEMALLOC | PF_SWAPWRITE | PF_KSWAPD;
	set_मुक्तzable();

	WRITE_ONCE(pgdat->kswapd_order, 0);
	WRITE_ONCE(pgdat->kswapd_highest_zoneidx, MAX_NR_ZONES);
	क्रम ( ; ; ) अणु
		bool ret;

		alloc_order = reclaim_order = READ_ONCE(pgdat->kswapd_order);
		highest_zoneidx = kswapd_highest_zoneidx(pgdat,
							highest_zoneidx);

kswapd_try_sleep:
		kswapd_try_to_sleep(pgdat, alloc_order, reclaim_order,
					highest_zoneidx);

		/* Read the new order and highest_zoneidx */
		alloc_order = READ_ONCE(pgdat->kswapd_order);
		highest_zoneidx = kswapd_highest_zoneidx(pgdat,
							highest_zoneidx);
		WRITE_ONCE(pgdat->kswapd_order, 0);
		WRITE_ONCE(pgdat->kswapd_highest_zoneidx, MAX_NR_ZONES);

		ret = try_to_मुक्तze();
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/*
		 * We can speed up thawing tasks अगर we करोn't call balance_pgdat
		 * after वापसing from the refrigerator
		 */
		अगर (ret)
			जारी;

		/*
		 * Reclaim begins at the requested order but अगर a high-order
		 * reclaim fails then kswapd falls back to reclaiming क्रम
		 * order-0. If that happens, kswapd will consider sleeping
		 * क्रम the order it finished reclaiming at (reclaim_order)
		 * but kcompactd is woken to compact क्रम the original
		 * request (alloc_order).
		 */
		trace_mm_vmscan_kswapd_wake(pgdat->node_id, highest_zoneidx,
						alloc_order);
		reclaim_order = balance_pgdat(pgdat, alloc_order,
						highest_zoneidx);
		अगर (reclaim_order < alloc_order)
			जाओ kswapd_try_sleep;
	पूर्ण

	tsk->flags &= ~(PF_MEMALLOC | PF_SWAPWRITE | PF_KSWAPD);

	वापस 0;
पूर्ण

/*
 * A zone is low on मुक्त memory or too fragmented क्रम high-order memory.  If
 * kswapd should reclaim (direct reclaim is deferred), wake it up क्रम the zone's
 * pgdat.  It will wake up kcompactd after reclaiming memory.  If kswapd reclaim
 * has failed or is not needed, still wake up kcompactd अगर only compaction is
 * needed.
 */
व्योम wakeup_kswapd(काष्ठा zone *zone, gfp_t gfp_flags, पूर्णांक order,
		   क्रमागत zone_type highest_zoneidx)
अणु
	pg_data_t *pgdat;
	क्रमागत zone_type curr_idx;

	अगर (!managed_zone(zone))
		वापस;

	अगर (!cpuset_zone_allowed(zone, gfp_flags))
		वापस;

	pgdat = zone->zone_pgdat;
	curr_idx = READ_ONCE(pgdat->kswapd_highest_zoneidx);

	अगर (curr_idx == MAX_NR_ZONES || curr_idx < highest_zoneidx)
		WRITE_ONCE(pgdat->kswapd_highest_zoneidx, highest_zoneidx);

	अगर (READ_ONCE(pgdat->kswapd_order) < order)
		WRITE_ONCE(pgdat->kswapd_order, order);

	अगर (!रुकोqueue_active(&pgdat->kswapd_रुको))
		वापस;

	/* Hopeless node, leave it to direct reclaim अगर possible */
	अगर (pgdat->kswapd_failures >= MAX_RECLAIM_RETRIES ||
	    (pgdat_balanced(pgdat, order, highest_zoneidx) &&
	     !pgdat_watermark_boosted(pgdat, highest_zoneidx))) अणु
		/*
		 * There may be plenty of मुक्त memory available, but it's too
		 * fragmented क्रम high-order allocations.  Wake up kcompactd
		 * and rely on compaction_suitable() to determine अगर it's
		 * needed.  If it fails, it will defer subsequent attempts to
		 * ratelimit its work.
		 */
		अगर (!(gfp_flags & __GFP_सूचीECT_RECLAIM))
			wakeup_kcompactd(pgdat, order, highest_zoneidx);
		वापस;
	पूर्ण

	trace_mm_vmscan_wakeup_kswapd(pgdat->node_id, highest_zoneidx, order,
				      gfp_flags);
	wake_up_पूर्णांकerruptible(&pgdat->kswapd_रुको);
पूर्ण

#अगर_घोषित CONFIG_HIBERNATION
/*
 * Try to मुक्त `nr_to_reclaim' of memory, प्रणाली-wide, and वापस the number of
 * मुक्तd pages.
 *
 * Rather than trying to age LRUs the aim is to preserve the overall
 * LRU order by reclaiming preferentially
 * inactive > active > active referenced > active mapped
 */
अचिन्हित दीर्घ shrink_all_memory(अचिन्हित दीर्घ nr_to_reclaim)
अणु
	काष्ठा scan_control sc = अणु
		.nr_to_reclaim = nr_to_reclaim,
		.gfp_mask = GFP_HIGHUSER_MOVABLE,
		.reclaim_idx = MAX_NR_ZONES - 1,
		.priority = DEF_PRIORITY,
		.may_ग_लिखोpage = 1,
		.may_unmap = 1,
		.may_swap = 1,
		.hibernation_mode = 1,
	पूर्ण;
	काष्ठा zonelist *zonelist = node_zonelist(numa_node_id(), sc.gfp_mask);
	अचिन्हित दीर्घ nr_reclaimed;
	अचिन्हित पूर्णांक noreclaim_flag;

	fs_reclaim_acquire(sc.gfp_mask);
	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	set_task_reclaim_state(current, &sc.reclaim_state);

	nr_reclaimed = करो_try_to_मुक्त_pages(zonelist, &sc);

	set_task_reclaim_state(current, शून्य);
	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	fs_reclaim_release(sc.gfp_mask);

	वापस nr_reclaimed;
पूर्ण
#पूर्ण_अगर /* CONFIG_HIBERNATION */

/*
 * This kswapd start function will be called by init and node-hot-add.
 * On node-hot-add, kswapd will moved to proper cpus अगर cpus are hot-added.
 */
पूर्णांक kswapd_run(पूर्णांक nid)
अणु
	pg_data_t *pgdat = NODE_DATA(nid);
	पूर्णांक ret = 0;

	अगर (pgdat->kswapd)
		वापस 0;

	pgdat->kswapd = kthपढ़ो_run(kswapd, pgdat, "kswapd%d", nid);
	अगर (IS_ERR(pgdat->kswapd)) अणु
		/* failure at boot is fatal */
		BUG_ON(प्रणाली_state < SYSTEM_RUNNING);
		pr_err("Failed to start kswapd on node %d\n", nid);
		ret = PTR_ERR(pgdat->kswapd);
		pgdat->kswapd = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Called by memory hotplug when all memory in a node is offlined.  Caller must
 * hold mem_hotplug_begin/end().
 */
व्योम kswapd_stop(पूर्णांक nid)
अणु
	काष्ठा task_काष्ठा *kswapd = NODE_DATA(nid)->kswapd;

	अगर (kswapd) अणु
		kthपढ़ो_stop(kswapd);
		NODE_DATA(nid)->kswapd = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __init kswapd_init(व्योम)
अणु
	पूर्णांक nid;

	swap_setup();
	क्रम_each_node_state(nid, N_MEMORY)
 		kswapd_run(nid);
	वापस 0;
पूर्ण

module_init(kswapd_init)

#अगर_घोषित CONFIG_NUMA
/*
 * Node reclaim mode
 *
 * If non-zero call node_reclaim when the number of मुक्त pages falls below
 * the watermarks.
 */
पूर्णांक node_reclaim_mode __पढ़ो_mostly;

/*
 * Priority क्रम NODE_RECLAIM. This determines the fraction of pages
 * of a node considered क्रम each zone_reclaim. 4 scans 1/16th of
 * a zone.
 */
#घोषणा NODE_RECLAIM_PRIORITY 4

/*
 * Percentage of pages in a zone that must be unmapped क्रम node_reclaim to
 * occur.
 */
पूर्णांक sysctl_min_unmapped_ratio = 1;

/*
 * If the number of slab pages in a zone grows beyond this percentage then
 * slab reclaim needs to occur.
 */
पूर्णांक sysctl_min_slab_ratio = 5;

अटल अंतरभूत अचिन्हित दीर्घ node_unmapped_file_pages(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ file_mapped = node_page_state(pgdat, NR_खाता_MAPPED);
	अचिन्हित दीर्घ file_lru = node_page_state(pgdat, NR_INACTIVE_खाता) +
		node_page_state(pgdat, NR_ACTIVE_खाता);

	/*
	 * It's possible क्रम there to be more file mapped pages than
	 * accounted क्रम by the pages on the file LRU lists because
	 * पंचांगpfs pages accounted क्रम as ANON can also be खाता_MAPPED
	 */
	वापस (file_lru > file_mapped) ? (file_lru - file_mapped) : 0;
पूर्ण

/* Work out how many page cache pages we can reclaim in this reclaim_mode */
अटल अचिन्हित दीर्घ node_pagecache_reclaimable(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ nr_pagecache_reclaimable;
	अचिन्हित दीर्घ delta = 0;

	/*
	 * If RECLAIM_UNMAP is set, then all file pages are considered
	 * potentially reclaimable. Otherwise, we have to worry about
	 * pages like swapcache and node_unmapped_file_pages() provides
	 * a better estimate
	 */
	अगर (node_reclaim_mode & RECLAIM_UNMAP)
		nr_pagecache_reclaimable = node_page_state(pgdat, NR_खाता_PAGES);
	अन्यथा
		nr_pagecache_reclaimable = node_unmapped_file_pages(pgdat);

	/* If we can't clean pages, हटाओ dirty pages from consideration */
	अगर (!(node_reclaim_mode & RECLAIM_WRITE))
		delta += node_page_state(pgdat, NR_खाता_सूचीTY);

	/* Watch क्रम any possible underflows due to delta */
	अगर (unlikely(delta > nr_pagecache_reclaimable))
		delta = nr_pagecache_reclaimable;

	वापस nr_pagecache_reclaimable - delta;
पूर्ण

/*
 * Try to मुक्त up some pages from this node through reclaim.
 */
अटल पूर्णांक __node_reclaim(काष्ठा pglist_data *pgdat, gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	/* Minimum pages needed in order to stay on node */
	स्थिर अचिन्हित दीर्घ nr_pages = 1 << order;
	काष्ठा task_काष्ठा *p = current;
	अचिन्हित पूर्णांक noreclaim_flag;
	काष्ठा scan_control sc = अणु
		.nr_to_reclaim = max(nr_pages, SWAP_CLUSTER_MAX),
		.gfp_mask = current_gfp_context(gfp_mask),
		.order = order,
		.priority = NODE_RECLAIM_PRIORITY,
		.may_ग_लिखोpage = !!(node_reclaim_mode & RECLAIM_WRITE),
		.may_unmap = !!(node_reclaim_mode & RECLAIM_UNMAP),
		.may_swap = 1,
		.reclaim_idx = gfp_zone(gfp_mask),
	पूर्ण;

	trace_mm_vmscan_node_reclaim_begin(pgdat->node_id, order,
					   sc.gfp_mask);

	cond_resched();
	fs_reclaim_acquire(sc.gfp_mask);
	/*
	 * We need to be able to allocate from the reserves क्रम RECLAIM_UNMAP
	 * and we also need to be able to ग_लिखो out pages क्रम RECLAIM_WRITE
	 * and RECLAIM_UNMAP.
	 */
	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	p->flags |= PF_SWAPWRITE;
	set_task_reclaim_state(p, &sc.reclaim_state);

	अगर (node_pagecache_reclaimable(pgdat) > pgdat->min_unmapped_pages) अणु
		/*
		 * Free memory by calling shrink node with increasing
		 * priorities until we have enough memory मुक्तd.
		 */
		करो अणु
			shrink_node(pgdat, &sc);
		पूर्ण जबतक (sc.nr_reclaimed < nr_pages && --sc.priority >= 0);
	पूर्ण

	set_task_reclaim_state(p, शून्य);
	current->flags &= ~PF_SWAPWRITE;
	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	fs_reclaim_release(sc.gfp_mask);

	trace_mm_vmscan_node_reclaim_end(sc.nr_reclaimed);

	वापस sc.nr_reclaimed >= nr_pages;
पूर्ण

पूर्णांक node_reclaim(काष्ठा pglist_data *pgdat, gfp_t gfp_mask, अचिन्हित पूर्णांक order)
अणु
	पूर्णांक ret;

	/*
	 * Node reclaim reclaims unmapped file backed pages and
	 * slab pages अगर we are over the defined limits.
	 *
	 * A small portion of unmapped file backed pages is needed क्रम
	 * file I/O otherwise pages पढ़ो by file I/O will be immediately
	 * thrown out अगर the node is overallocated. So we करो not reclaim
	 * अगर less than a specअगरied percentage of the node is used by
	 * unmapped file backed pages.
	 */
	अगर (node_pagecache_reclaimable(pgdat) <= pgdat->min_unmapped_pages &&
	    node_page_state_pages(pgdat, NR_SLAB_RECLAIMABLE_B) <=
	    pgdat->min_slab_pages)
		वापस NODE_RECLAIM_FULL;

	/*
	 * Do not scan अगर the allocation should not be delayed.
	 */
	अगर (!gfpflags_allow_blocking(gfp_mask) || (current->flags & PF_MEMALLOC))
		वापस NODE_RECLAIM_NOSCAN;

	/*
	 * Only run node reclaim on the local node or on nodes that करो not
	 * have associated processors. This will favor the local processor
	 * over remote processors and spपढ़ो off node memory allocations
	 * as wide as possible.
	 */
	अगर (node_state(pgdat->node_id, N_CPU) && pgdat->node_id != numa_node_id())
		वापस NODE_RECLAIM_NOSCAN;

	अगर (test_and_set_bit(PGDAT_RECLAIM_LOCKED, &pgdat->flags))
		वापस NODE_RECLAIM_NOSCAN;

	ret = __node_reclaim(pgdat, gfp_mask, order);
	clear_bit(PGDAT_RECLAIM_LOCKED, &pgdat->flags);

	अगर (!ret)
		count_vm_event(PGSCAN_ZONE_RECLAIM_FAILED);

	वापस ret;
पूर्ण
#पूर्ण_अगर

/**
 * check_move_unevictable_pages - check pages क्रम evictability and move to
 * appropriate zone lru list
 * @pvec: pagevec with lru pages to check
 *
 * Checks pages क्रम evictability, अगर an evictable page is in the unevictable
 * lru list, moves it to the appropriate evictable lru list. This function
 * should be only used क्रम lru pages.
 */
व्योम check_move_unevictable_pages(काष्ठा pagevec *pvec)
अणु
	काष्ठा lruvec *lruvec = शून्य;
	पूर्णांक pgscanned = 0;
	पूर्णांक pgrescued = 0;
	पूर्णांक i;

	क्रम (i = 0; i < pvec->nr; i++) अणु
		काष्ठा page *page = pvec->pages[i];
		पूर्णांक nr_pages;

		अगर (PageTransTail(page))
			जारी;

		nr_pages = thp_nr_pages(page);
		pgscanned += nr_pages;

		/* block memcg migration during page moving between lru */
		अगर (!TestClearPageLRU(page))
			जारी;

		lruvec = relock_page_lruvec_irq(page, lruvec);
		अगर (page_evictable(page) && PageUnevictable(page)) अणु
			del_page_from_lru_list(page, lruvec);
			ClearPageUnevictable(page);
			add_page_to_lru_list(page, lruvec);
			pgrescued += nr_pages;
		पूर्ण
		SetPageLRU(page);
	पूर्ण

	अगर (lruvec) अणु
		__count_vm_events(UNEVICTABLE_PGRESCUED, pgrescued);
		__count_vm_events(UNEVICTABLE_PGSCANNED, pgscanned);
		unlock_page_lruvec_irq(lruvec);
	पूर्ण अन्यथा अगर (pgscanned) अणु
		count_vm_events(UNEVICTABLE_PGSCANNED, pgscanned);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(check_move_unevictable_pages);
