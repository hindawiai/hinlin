<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Completely Fair Scheduling (CFS) Class (SCHED_NORMAL/SCHED_BATCH)
 *
 *  Copyright (C) 2007 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 *  Interactivity improvements by Mike Galbraith
 *  (C) 2007 Mike Galbraith <efault@gmx.de>
 *
 *  Various enhancements by Dmitry Adamushko.
 *  (C) 2007 Dmitry Adamushko <dmitry.adamushko@gmail.com>
 *
 *  Group scheduling enhancements by Srivatsa Vaddagiri
 *  Copyright IBM Corporation, 2007
 *  Author: Srivatsa Vaddagiri <vatsa@linux.vnet.ibm.com>
 *
 *  Scaled math optimizations by Thomas Gleixner
 *  Copyright (C) 2007, Thomas Gleixner <tglx@linutronix.de>
 *
 *  Adaptive scheduling granularity, math enhancements by Peter Zijlstra
 *  Copyright (C) 2007 Red Hat, Inc., Peter Zijlstra
 */
#समावेश "sched.h"

/*
 * Targeted preemption latency क्रम CPU-bound tasks:
 *
 * NOTE: this latency value is not the same as the concept of
 * 'timeslice length' - बारlices in CFS are of variable length
 * and have no persistent notion like in traditional, समय-slice
 * based scheduling concepts.
 *
 * (to see the precise effective बारlice length of your workload,
 *  run vmstat and monitor the context-चयनes (cs) field)
 *
 * (शेष: 6ms * (1 + ilog(ncpus)), units: nanoseconds)
 */
अचिन्हित पूर्णांक sysctl_sched_latency			= 6000000ULL;
अटल अचिन्हित पूर्णांक normalized_sysctl_sched_latency	= 6000000ULL;

/*
 * The initial- and re-scaling of tunables is configurable
 *
 * Options are:
 *
 *   SCHED_TUNABLESCALING_NONE - unscaled, always *1
 *   SCHED_TUNABLESCALING_LOG - scaled logarithmical, *1+ilog(ncpus)
 *   SCHED_TUNABLESCALING_LINEAR - scaled linear, *ncpus
 *
 * (शेष SCHED_TUNABLESCALING_LOG = *(1+ilog(ncpus))
 */
अचिन्हित पूर्णांक sysctl_sched_tunable_scaling = SCHED_TUNABLESCALING_LOG;

/*
 * Minimal preemption granularity क्रम CPU-bound tasks:
 *
 * (शेष: 0.75 msec * (1 + ilog(ncpus)), units: nanoseconds)
 */
अचिन्हित पूर्णांक sysctl_sched_min_granularity			= 750000ULL;
अटल अचिन्हित पूर्णांक normalized_sysctl_sched_min_granularity	= 750000ULL;

/*
 * This value is kept at sysctl_sched_latency/sysctl_sched_min_granularity
 */
अटल अचिन्हित पूर्णांक sched_nr_latency = 8;

/*
 * After विभाजन, child runs first. If set to 0 (शेष) then
 * parent will (try to) run first.
 */
अचिन्हित पूर्णांक sysctl_sched_child_runs_first __पढ़ो_mostly;

/*
 * SCHED_OTHER wake-up granularity.
 *
 * This option delays the preemption effects of decoupled workloads
 * and reduces their over-scheduling. Synchronous workloads will still
 * have immediate wakeup/sleep latencies.
 *
 * (शेष: 1 msec * (1 + ilog(ncpus)), units: nanoseconds)
 */
अचिन्हित पूर्णांक sysctl_sched_wakeup_granularity			= 1000000UL;
अटल अचिन्हित पूर्णांक normalized_sysctl_sched_wakeup_granularity	= 1000000UL;

स्थिर_debug अचिन्हित पूर्णांक sysctl_sched_migration_cost	= 500000UL;

पूर्णांक sched_thermal_decay_shअगरt;
अटल पूर्णांक __init setup_sched_thermal_decay_shअगरt(अक्षर *str)
अणु
	पूर्णांक _shअगरt = 0;

	अगर (kstrtoपूर्णांक(str, 0, &_shअगरt))
		pr_warn("Unable to set scheduler thermal pressure decay shift parameter\n");

	sched_thermal_decay_shअगरt = clamp(_shअगरt, 0, 10);
	वापस 1;
पूर्ण
__setup("sched_thermal_decay_shift=", setup_sched_thermal_decay_shअगरt);

#अगर_घोषित CONFIG_SMP
/*
 * For asym packing, by शेष the lower numbered CPU has higher priority.
 */
पूर्णांक __weak arch_asym_cpu_priority(पूर्णांक cpu)
अणु
	वापस -cpu;
पूर्ण

/*
 * The margin used when comparing utilization with CPU capacity.
 *
 * (शेष: ~20%)
 */
#घोषणा fits_capacity(cap, max)	((cap) * 1280 < (max) * 1024)

/*
 * The margin used when comparing CPU capacities.
 * is 'cap1' noticeably greater than 'cap2'
 *
 * (शेष: ~5%)
 */
#घोषणा capacity_greater(cap1, cap2) ((cap1) * 1024 > (cap2) * 1078)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CFS_BANDWIDTH
/*
 * Amount of runसमय to allocate from global (tg) to local (per-cfs_rq) pool
 * each समय a cfs_rq requests quota.
 *
 * Note: in the हाल that the slice exceeds the runसमय reमुख्यing (either due
 * to consumption or the quota being specअगरied to be smaller than the slice)
 * we will always only issue the reमुख्यing available समय.
 *
 * (शेष: 5 msec, units: microseconds)
 */
अचिन्हित पूर्णांक sysctl_sched_cfs_bandwidth_slice		= 5000UL;
#पूर्ण_अगर

अटल अंतरभूत व्योम update_load_add(काष्ठा load_weight *lw, अचिन्हित दीर्घ inc)
अणु
	lw->weight += inc;
	lw->inv_weight = 0;
पूर्ण

अटल अंतरभूत व्योम update_load_sub(काष्ठा load_weight *lw, अचिन्हित दीर्घ dec)
अणु
	lw->weight -= dec;
	lw->inv_weight = 0;
पूर्ण

अटल अंतरभूत व्योम update_load_set(काष्ठा load_weight *lw, अचिन्हित दीर्घ w)
अणु
	lw->weight = w;
	lw->inv_weight = 0;
पूर्ण

/*
 * Increase the granularity value when there are more CPUs,
 * because with more CPUs the 'effective latency' as visible
 * to users decreases. But the relationship is not linear,
 * so pick a second-best guess by going with the log2 of the
 * number of CPUs.
 *
 * This idea comes from the SD scheduler of Con Kolivas:
 */
अटल अचिन्हित पूर्णांक get_update_sysctl_factor(व्योम)
अणु
	अचिन्हित पूर्णांक cpus = min_t(अचिन्हित पूर्णांक, num_online_cpus(), 8);
	अचिन्हित पूर्णांक factor;

	चयन (sysctl_sched_tunable_scaling) अणु
	हाल SCHED_TUNABLESCALING_NONE:
		factor = 1;
		अवरोध;
	हाल SCHED_TUNABLESCALING_LINEAR:
		factor = cpus;
		अवरोध;
	हाल SCHED_TUNABLESCALING_LOG:
	शेष:
		factor = 1 + ilog2(cpus);
		अवरोध;
	पूर्ण

	वापस factor;
पूर्ण

अटल व्योम update_sysctl(व्योम)
अणु
	अचिन्हित पूर्णांक factor = get_update_sysctl_factor();

#घोषणा SET_SYSCTL(name) \
	(sysctl_##name = (factor) * normalized_sysctl_##name)
	SET_SYSCTL(sched_min_granularity);
	SET_SYSCTL(sched_latency);
	SET_SYSCTL(sched_wakeup_granularity);
#अघोषित SET_SYSCTL
पूर्ण

व्योम __init sched_init_granularity(व्योम)
अणु
	update_sysctl();
पूर्ण

#घोषणा WMULT_CONST	(~0U)
#घोषणा WMULT_SHIFT	32

अटल व्योम __update_inv_weight(काष्ठा load_weight *lw)
अणु
	अचिन्हित दीर्घ w;

	अगर (likely(lw->inv_weight))
		वापस;

	w = scale_load_करोwn(lw->weight);

	अगर (BITS_PER_LONG > 32 && unlikely(w >= WMULT_CONST))
		lw->inv_weight = 1;
	अन्यथा अगर (unlikely(!w))
		lw->inv_weight = WMULT_CONST;
	अन्यथा
		lw->inv_weight = WMULT_CONST / w;
पूर्ण

/*
 * delta_exec * weight / lw.weight
 *   OR
 * (delta_exec * (weight * lw->inv_weight)) >> WMULT_SHIFT
 *
 * Either weight := NICE_0_LOAD and lw \e sched_prio_to_wmult[], in which हाल
 * we're guaranteed shअगरt stays positive because inv_weight is guaranteed to
 * fit 32 bits, and NICE_0_LOAD gives another 10 bits; thereक्रमe shअगरt >= 22.
 *
 * Or, weight =< lw.weight (because lw.weight is the runqueue weight), thus
 * weight/lw.weight <= 1, and thereक्रमe our shअगरt will also be positive.
 */
अटल u64 __calc_delta(u64 delta_exec, अचिन्हित दीर्घ weight, काष्ठा load_weight *lw)
अणु
	u64 fact = scale_load_करोwn(weight);
	u32 fact_hi = (u32)(fact >> 32);
	पूर्णांक shअगरt = WMULT_SHIFT;
	पूर्णांक fs;

	__update_inv_weight(lw);

	अगर (unlikely(fact_hi)) अणु
		fs = fls(fact_hi);
		shअगरt -= fs;
		fact >>= fs;
	पूर्ण

	fact = mul_u32_u32(fact, lw->inv_weight);

	fact_hi = (u32)(fact >> 32);
	अगर (fact_hi) अणु
		fs = fls(fact_hi);
		shअगरt -= fs;
		fact >>= fs;
	पूर्ण

	वापस mul_u64_u32_shr(delta_exec, fact, shअगरt);
पूर्ण


स्थिर काष्ठा sched_class fair_sched_class;

/**************************************************************
 * CFS operations on generic schedulable entities:
 */

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
अटल अंतरभूत काष्ठा task_काष्ठा *task_of(काष्ठा sched_entity *se)
अणु
	SCHED_WARN_ON(!entity_is_task(se));
	वापस container_of(se, काष्ठा task_काष्ठा, se);
पूर्ण

/* Walk up scheduling entities hierarchy */
#घोषणा क्रम_each_sched_entity(se) \
		क्रम (; se; se = se->parent)

अटल अंतरभूत काष्ठा cfs_rq *task_cfs_rq(काष्ठा task_काष्ठा *p)
अणु
	वापस p->se.cfs_rq;
पूर्ण

/* runqueue on which this entity is (to be) queued */
अटल अंतरभूत काष्ठा cfs_rq *cfs_rq_of(काष्ठा sched_entity *se)
अणु
	वापस se->cfs_rq;
पूर्ण

/* runqueue "owned" by this group */
अटल अंतरभूत काष्ठा cfs_rq *group_cfs_rq(काष्ठा sched_entity *grp)
अणु
	वापस grp->my_q;
पूर्ण

अटल अंतरभूत व्योम cfs_rq_tg_path(काष्ठा cfs_rq *cfs_rq, अक्षर *path, पूर्णांक len)
अणु
	अगर (!path)
		वापस;

	अगर (cfs_rq && task_group_is_स्वतःgroup(cfs_rq->tg))
		स्वतःgroup_path(cfs_rq->tg, path, len);
	अन्यथा अगर (cfs_rq && cfs_rq->tg->css.cgroup)
		cgroup_path(cfs_rq->tg->css.cgroup, path, len);
	अन्यथा
		strlcpy(path, "(null)", len);
पूर्ण

अटल अंतरभूत bool list_add_leaf_cfs_rq(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा rq *rq = rq_of(cfs_rq);
	पूर्णांक cpu = cpu_of(rq);

	अगर (cfs_rq->on_list)
		वापस rq->पंचांगp_alone_branch == &rq->leaf_cfs_rq_list;

	cfs_rq->on_list = 1;

	/*
	 * Ensure we either appear beक्रमe our parent (अगर alपढ़ोy
	 * enqueued) or क्रमce our parent to appear after us when it is
	 * enqueued. The fact that we always enqueue bottom-up
	 * reduces this to two हालs and a special हाल क्रम the root
	 * cfs_rq. Furthermore, it also means that we will always reset
	 * पंचांगp_alone_branch either when the branch is connected
	 * to a tree or when we reach the top of the tree
	 */
	अगर (cfs_rq->tg->parent &&
	    cfs_rq->tg->parent->cfs_rq[cpu]->on_list) अणु
		/*
		 * If parent is alपढ़ोy on the list, we add the child
		 * just beक्रमe. Thanks to circular linked property of
		 * the list, this means to put the child at the tail
		 * of the list that starts by parent.
		 */
		list_add_tail_rcu(&cfs_rq->leaf_cfs_rq_list,
			&(cfs_rq->tg->parent->cfs_rq[cpu]->leaf_cfs_rq_list));
		/*
		 * The branch is now connected to its tree so we can
		 * reset पंचांगp_alone_branch to the beginning of the
		 * list.
		 */
		rq->पंचांगp_alone_branch = &rq->leaf_cfs_rq_list;
		वापस true;
	पूर्ण

	अगर (!cfs_rq->tg->parent) अणु
		/*
		 * cfs rq without parent should be put
		 * at the tail of the list.
		 */
		list_add_tail_rcu(&cfs_rq->leaf_cfs_rq_list,
			&rq->leaf_cfs_rq_list);
		/*
		 * We have reach the top of a tree so we can reset
		 * पंचांगp_alone_branch to the beginning of the list.
		 */
		rq->पंचांगp_alone_branch = &rq->leaf_cfs_rq_list;
		वापस true;
	पूर्ण

	/*
	 * The parent has not alपढ़ोy been added so we want to
	 * make sure that it will be put after us.
	 * पंचांगp_alone_branch poपूर्णांकs to the begin of the branch
	 * where we will add parent.
	 */
	list_add_rcu(&cfs_rq->leaf_cfs_rq_list, rq->पंचांगp_alone_branch);
	/*
	 * update पंचांगp_alone_branch to poपूर्णांकs to the new begin
	 * of the branch
	 */
	rq->पंचांगp_alone_branch = &cfs_rq->leaf_cfs_rq_list;
	वापस false;
पूर्ण

अटल अंतरभूत व्योम list_del_leaf_cfs_rq(काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (cfs_rq->on_list) अणु
		काष्ठा rq *rq = rq_of(cfs_rq);

		/*
		 * With cfs_rq being unthrottled/throttled during an enqueue,
		 * it can happen the पंचांगp_alone_branch poपूर्णांकs the a leaf that
		 * we finally want to del. In this हाल, पंचांगp_alone_branch moves
		 * to the prev element but it will poपूर्णांक to rq->leaf_cfs_rq_list
		 * at the end of the enqueue.
		 */
		अगर (rq->पंचांगp_alone_branch == &cfs_rq->leaf_cfs_rq_list)
			rq->पंचांगp_alone_branch = cfs_rq->leaf_cfs_rq_list.prev;

		list_del_rcu(&cfs_rq->leaf_cfs_rq_list);
		cfs_rq->on_list = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम निश्चित_list_leaf_cfs_rq(काष्ठा rq *rq)
अणु
	SCHED_WARN_ON(rq->पंचांगp_alone_branch != &rq->leaf_cfs_rq_list);
पूर्ण

/* Iterate thr' all leaf cfs_rq's on a runqueue */
#घोषणा क्रम_each_leaf_cfs_rq_safe(rq, cfs_rq, pos)			\
	list_क्रम_each_entry_safe(cfs_rq, pos, &rq->leaf_cfs_rq_list,	\
				 leaf_cfs_rq_list)

/* Do the two (enqueued) entities beदीर्घ to the same group ? */
अटल अंतरभूत काष्ठा cfs_rq *
is_same_group(काष्ठा sched_entity *se, काष्ठा sched_entity *pse)
अणु
	अगर (se->cfs_rq == pse->cfs_rq)
		वापस se->cfs_rq;

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा sched_entity *parent_entity(काष्ठा sched_entity *se)
अणु
	वापस se->parent;
पूर्ण

अटल व्योम
find_matching_se(काष्ठा sched_entity **se, काष्ठा sched_entity **pse)
अणु
	पूर्णांक se_depth, pse_depth;

	/*
	 * preemption test can be made between sibling entities who are in the
	 * same cfs_rq i.e who have a common parent. Walk up the hierarchy of
	 * both tasks until we find their ancestors who are siblings of common
	 * parent.
	 */

	/* First walk up until both entities are at same depth */
	se_depth = (*se)->depth;
	pse_depth = (*pse)->depth;

	जबतक (se_depth > pse_depth) अणु
		se_depth--;
		*se = parent_entity(*se);
	पूर्ण

	जबतक (pse_depth > se_depth) अणु
		pse_depth--;
		*pse = parent_entity(*pse);
	पूर्ण

	जबतक (!is_same_group(*se, *pse)) अणु
		*se = parent_entity(*se);
		*pse = parent_entity(*pse);
	पूर्ण
पूर्ण

#अन्यथा	/* !CONFIG_FAIR_GROUP_SCHED */

अटल अंतरभूत काष्ठा task_काष्ठा *task_of(काष्ठा sched_entity *se)
अणु
	वापस container_of(se, काष्ठा task_काष्ठा, se);
पूर्ण

#घोषणा क्रम_each_sched_entity(se) \
		क्रम (; se; se = शून्य)

अटल अंतरभूत काष्ठा cfs_rq *task_cfs_rq(काष्ठा task_काष्ठा *p)
अणु
	वापस &task_rq(p)->cfs;
पूर्ण

अटल अंतरभूत काष्ठा cfs_rq *cfs_rq_of(काष्ठा sched_entity *se)
अणु
	काष्ठा task_काष्ठा *p = task_of(se);
	काष्ठा rq *rq = task_rq(p);

	वापस &rq->cfs;
पूर्ण

/* runqueue "owned" by this group */
अटल अंतरभूत काष्ठा cfs_rq *group_cfs_rq(काष्ठा sched_entity *grp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम cfs_rq_tg_path(काष्ठा cfs_rq *cfs_rq, अक्षर *path, पूर्णांक len)
अणु
	अगर (path)
		strlcpy(path, "(null)", len);
पूर्ण

अटल अंतरभूत bool list_add_leaf_cfs_rq(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम list_del_leaf_cfs_rq(काष्ठा cfs_rq *cfs_rq)
अणु
पूर्ण

अटल अंतरभूत व्योम निश्चित_list_leaf_cfs_rq(काष्ठा rq *rq)
अणु
पूर्ण

#घोषणा क्रम_each_leaf_cfs_rq_safe(rq, cfs_rq, pos)	\
		क्रम (cfs_rq = &rq->cfs, pos = शून्य; cfs_rq; cfs_rq = pos)

अटल अंतरभूत काष्ठा sched_entity *parent_entity(काष्ठा sched_entity *se)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
find_matching_se(काष्ठा sched_entity **se, काष्ठा sched_entity **pse)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_FAIR_GROUP_SCHED */

अटल __always_अंतरभूत
व्योम account_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq, u64 delta_exec);

/**************************************************************
 * Scheduling class tree data काष्ठाure manipulation methods:
 */

अटल अंतरभूत u64 max_vrunसमय(u64 max_vrunसमय, u64 vrunसमय)
अणु
	s64 delta = (s64)(vrunसमय - max_vrunसमय);
	अगर (delta > 0)
		max_vrunसमय = vrunसमय;

	वापस max_vrunसमय;
पूर्ण

अटल अंतरभूत u64 min_vrunसमय(u64 min_vrunसमय, u64 vrunसमय)
अणु
	s64 delta = (s64)(vrunसमय - min_vrunसमय);
	अगर (delta < 0)
		min_vrunसमय = vrunसमय;

	वापस min_vrunसमय;
पूर्ण

अटल अंतरभूत bool entity_beक्रमe(काष्ठा sched_entity *a,
				काष्ठा sched_entity *b)
अणु
	वापस (s64)(a->vrunसमय - b->vrunसमय) < 0;
पूर्ण

#घोषणा __node_2_se(node) \
	rb_entry((node), काष्ठा sched_entity, run_node)

अटल व्योम update_min_vrunसमय(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा sched_entity *curr = cfs_rq->curr;
	काष्ठा rb_node *lefपंचांगost = rb_first_cached(&cfs_rq->tasks_समयline);

	u64 vrunसमय = cfs_rq->min_vrunसमय;

	अगर (curr) अणु
		अगर (curr->on_rq)
			vrunसमय = curr->vrunसमय;
		अन्यथा
			curr = शून्य;
	पूर्ण

	अगर (lefपंचांगost) अणु /* non-empty tree */
		काष्ठा sched_entity *se = __node_2_se(lefपंचांगost);

		अगर (!curr)
			vrunसमय = se->vrunसमय;
		अन्यथा
			vrunसमय = min_vrunसमय(vrunसमय, se->vrunसमय);
	पूर्ण

	/* ensure we never gain समय by being placed backwards. */
	cfs_rq->min_vrunसमय = max_vrunसमय(cfs_rq->min_vrunसमय, vrunसमय);
#अगर_अघोषित CONFIG_64BIT
	smp_wmb();
	cfs_rq->min_vrunसमय_copy = cfs_rq->min_vrunसमय;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool __entity_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	वापस entity_beक्रमe(__node_2_se(a), __node_2_se(b));
पूर्ण

/*
 * Enqueue an entity पूर्णांकo the rb-tree:
 */
अटल व्योम __enqueue_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	rb_add_cached(&se->run_node, &cfs_rq->tasks_समयline, __entity_less);
पूर्ण

अटल व्योम __dequeue_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	rb_erase_cached(&se->run_node, &cfs_rq->tasks_समयline);
पूर्ण

काष्ठा sched_entity *__pick_first_entity(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा rb_node *left = rb_first_cached(&cfs_rq->tasks_समयline);

	अगर (!left)
		वापस शून्य;

	वापस __node_2_se(left);
पूर्ण

अटल काष्ठा sched_entity *__pick_next_entity(काष्ठा sched_entity *se)
अणु
	काष्ठा rb_node *next = rb_next(&se->run_node);

	अगर (!next)
		वापस शून्य;

	वापस __node_2_se(next);
पूर्ण

#अगर_घोषित CONFIG_SCHED_DEBUG
काष्ठा sched_entity *__pick_last_entity(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा rb_node *last = rb_last(&cfs_rq->tasks_समयline.rb_root);

	अगर (!last)
		वापस शून्य;

	वापस __node_2_se(last);
पूर्ण

/**************************************************************
 * Scheduling class statistics methods:
 */

पूर्णांक sched_update_scaling(व्योम)
अणु
	अचिन्हित पूर्णांक factor = get_update_sysctl_factor();

	sched_nr_latency = DIV_ROUND_UP(sysctl_sched_latency,
					sysctl_sched_min_granularity);

#घोषणा WRT_SYSCTL(name) \
	(normalized_sysctl_##name = sysctl_##name / (factor))
	WRT_SYSCTL(sched_min_granularity);
	WRT_SYSCTL(sched_latency);
	WRT_SYSCTL(sched_wakeup_granularity);
#अघोषित WRT_SYSCTL

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * delta /= w
 */
अटल अंतरभूत u64 calc_delta_fair(u64 delta, काष्ठा sched_entity *se)
अणु
	अगर (unlikely(se->load.weight != NICE_0_LOAD))
		delta = __calc_delta(delta, NICE_0_LOAD, &se->load);

	वापस delta;
पूर्ण

/*
 * The idea is to set a period in which each task runs once.
 *
 * When there are too many tasks (sched_nr_latency) we have to stretch
 * this period because otherwise the slices get too small.
 *
 * p = (nr <= nl) ? l : l*nr/nl
 */
अटल u64 __sched_period(अचिन्हित दीर्घ nr_running)
अणु
	अगर (unlikely(nr_running > sched_nr_latency))
		वापस nr_running * sysctl_sched_min_granularity;
	अन्यथा
		वापस sysctl_sched_latency;
पूर्ण

/*
 * We calculate the wall-समय slice from the period by taking a part
 * proportional to the weight.
 *
 * s = p*P[w/rw]
 */
अटल u64 sched_slice(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	अचिन्हित पूर्णांक nr_running = cfs_rq->nr_running;
	u64 slice;

	अगर (sched_feat(ALT_PERIOD))
		nr_running = rq_of(cfs_rq)->cfs.h_nr_running;

	slice = __sched_period(nr_running + !se->on_rq);

	क्रम_each_sched_entity(se) अणु
		काष्ठा load_weight *load;
		काष्ठा load_weight lw;

		cfs_rq = cfs_rq_of(se);
		load = &cfs_rq->load;

		अगर (unlikely(!se->on_rq)) अणु
			lw = cfs_rq->load;

			update_load_add(&lw, se->load.weight);
			load = &lw;
		पूर्ण
		slice = __calc_delta(slice, se->load.weight, load);
	पूर्ण

	अगर (sched_feat(BASE_SLICE))
		slice = max(slice, (u64)sysctl_sched_min_granularity);

	वापस slice;
पूर्ण

/*
 * We calculate the vrunसमय slice of a to-be-inserted task.
 *
 * vs = s/w
 */
अटल u64 sched_vslice(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	वापस calc_delta_fair(sched_slice(cfs_rq, se), se);
पूर्ण

#समावेश "pelt.h"
#अगर_घोषित CONFIG_SMP

अटल पूर्णांक select_idle_sibling(काष्ठा task_काष्ठा *p, पूर्णांक prev_cpu, पूर्णांक cpu);
अटल अचिन्हित दीर्घ task_h_load(काष्ठा task_काष्ठा *p);
अटल अचिन्हित दीर्घ capacity_of(पूर्णांक cpu);

/* Give new sched_entity start runnable values to heavy its load in infant समय */
व्योम init_entity_runnable_average(काष्ठा sched_entity *se)
अणु
	काष्ठा sched_avg *sa = &se->avg;

	स_रखो(sa, 0, माप(*sa));

	/*
	 * Tasks are initialized with full load to be seen as heavy tasks until
	 * they get a chance to stabilize to their real load level.
	 * Group entities are initialized with zero load to reflect the fact that
	 * nothing has been attached to the task group yet.
	 */
	अगर (entity_is_task(se))
		sa->load_avg = scale_load_करोwn(se->load.weight);

	/* when this task enqueue'ed, it will contribute to its cfs_rq's load_avg */
पूर्ण

अटल व्योम attach_entity_cfs_rq(काष्ठा sched_entity *se);

/*
 * With new tasks being created, their initial util_avgs are extrapolated
 * based on the cfs_rq's current util_avg:
 *
 *   util_avg = cfs_rq->util_avg / (cfs_rq->load_avg + 1) * se.load.weight
 *
 * However, in many हालs, the above util_avg करोes not give a desired
 * value. Moreover, the sum of the util_avgs may be भागergent, such
 * as when the series is a harmonic series.
 *
 * To solve this problem, we also cap the util_avg of successive tasks to
 * only 1/2 of the left utilization budget:
 *
 *   util_avg_cap = (cpu_scale - cfs_rq->avg.util_avg) / 2^n
 *
 * where n denotes the nth task and cpu_scale the CPU capacity.
 *
 * For example, क्रम a CPU with 1024 of capacity, a simplest series from
 * the beginning would be like:
 *
 *  task  util_avg: 512, 256, 128,  64,  32,   16,    8, ...
 * cfs_rq util_avg: 512, 768, 896, 960, 992, 1008, 1016, ...
 *
 * Finally, that extrapolated util_avg is clamped to the cap (util_avg_cap)
 * अगर util_avg > util_avg_cap.
 */
व्योम post_init_entity_util_avg(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_entity *se = &p->se;
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
	काष्ठा sched_avg *sa = &se->avg;
	दीर्घ cpu_scale = arch_scale_cpu_capacity(cpu_of(rq_of(cfs_rq)));
	दीर्घ cap = (दीर्घ)(cpu_scale - cfs_rq->avg.util_avg) / 2;

	अगर (cap > 0) अणु
		अगर (cfs_rq->avg.util_avg != 0) अणु
			sa->util_avg  = cfs_rq->avg.util_avg * se->load.weight;
			sa->util_avg /= (cfs_rq->avg.load_avg + 1);

			अगर (sa->util_avg > cap)
				sa->util_avg = cap;
		पूर्ण अन्यथा अणु
			sa->util_avg = cap;
		पूर्ण
	पूर्ण

	sa->runnable_avg = sa->util_avg;

	अगर (p->sched_class != &fair_sched_class) अणु
		/*
		 * For !fair tasks करो:
		 *
		update_cfs_rq_load_avg(now, cfs_rq);
		attach_entity_load_avg(cfs_rq, se);
		चयनed_from_fair(rq, p);
		 *
		 * such that the next चयनed_to_fair() has the
		 * expected state.
		 */
		se->avg.last_update_समय = cfs_rq_घड़ी_pelt(cfs_rq);
		वापस;
	पूर्ण

	attach_entity_cfs_rq(se);
पूर्ण

#अन्यथा /* !CONFIG_SMP */
व्योम init_entity_runnable_average(काष्ठा sched_entity *se)
अणु
पूर्ण
व्योम post_init_entity_util_avg(काष्ठा task_काष्ठा *p)
अणु
पूर्ण
अटल व्योम update_tg_load_avg(काष्ठा cfs_rq *cfs_rq)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Update the current task's runसमय statistics.
 */
अटल व्योम update_curr(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा sched_entity *curr = cfs_rq->curr;
	u64 now = rq_घड़ी_प्रकारask(rq_of(cfs_rq));
	u64 delta_exec;

	अगर (unlikely(!curr))
		वापस;

	delta_exec = now - curr->exec_start;
	अगर (unlikely((s64)delta_exec <= 0))
		वापस;

	curr->exec_start = now;

	schedstat_set(curr->statistics.exec_max,
		      max(delta_exec, curr->statistics.exec_max));

	curr->sum_exec_runसमय += delta_exec;
	schedstat_add(cfs_rq->exec_घड़ी, delta_exec);

	curr->vrunसमय += calc_delta_fair(delta_exec, curr);
	update_min_vrunसमय(cfs_rq);

	अगर (entity_is_task(curr)) अणु
		काष्ठा task_काष्ठा *curtask = task_of(curr);

		trace_sched_stat_runसमय(curtask, delta_exec, curr->vrunसमय);
		cgroup_account_cpuसमय(curtask, delta_exec);
		account_group_exec_runसमय(curtask, delta_exec);
	पूर्ण

	account_cfs_rq_runसमय(cfs_rq, delta_exec);
पूर्ण

अटल व्योम update_curr_fair(काष्ठा rq *rq)
अणु
	update_curr(cfs_rq_of(&rq->curr->se));
पूर्ण

अटल अंतरभूत व्योम
update_stats_रुको_start(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	u64 रुको_start, prev_रुको_start;

	अगर (!schedstat_enabled())
		वापस;

	रुको_start = rq_घड़ी(rq_of(cfs_rq));
	prev_रुको_start = schedstat_val(se->statistics.रुको_start);

	अगर (entity_is_task(se) && task_on_rq_migrating(task_of(se)) &&
	    likely(रुको_start > prev_रुको_start))
		रुको_start -= prev_रुको_start;

	__schedstat_set(se->statistics.रुको_start, रुको_start);
पूर्ण

अटल अंतरभूत व्योम
update_stats_रुको_end(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	काष्ठा task_काष्ठा *p;
	u64 delta;

	अगर (!schedstat_enabled())
		वापस;

	/*
	 * When the sched_schedstat changes from 0 to 1, some sched se
	 * maybe alपढ़ोy in the runqueue, the se->statistics.रुको_start
	 * will be 0.So it will let the delta wrong. We need to aव्योम this
	 * scenario.
	 */
	अगर (unlikely(!schedstat_val(se->statistics.रुको_start)))
		वापस;

	delta = rq_घड़ी(rq_of(cfs_rq)) - schedstat_val(se->statistics.रुको_start);

	अगर (entity_is_task(se)) अणु
		p = task_of(se);
		अगर (task_on_rq_migrating(p)) अणु
			/*
			 * Preserve migrating task's रुको समय so रुको_start
			 * समय stamp can be adjusted to accumulate रुको समय
			 * prior to migration.
			 */
			__schedstat_set(se->statistics.रुको_start, delta);
			वापस;
		पूर्ण
		trace_sched_stat_रुको(p, delta);
	पूर्ण

	__schedstat_set(se->statistics.रुको_max,
		      max(schedstat_val(se->statistics.रुको_max), delta));
	__schedstat_inc(se->statistics.रुको_count);
	__schedstat_add(se->statistics.रुको_sum, delta);
	__schedstat_set(se->statistics.रुको_start, 0);
पूर्ण

अटल अंतरभूत व्योम
update_stats_enqueue_sleeper(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	काष्ठा task_काष्ठा *tsk = शून्य;
	u64 sleep_start, block_start;

	अगर (!schedstat_enabled())
		वापस;

	sleep_start = schedstat_val(se->statistics.sleep_start);
	block_start = schedstat_val(se->statistics.block_start);

	अगर (entity_is_task(se))
		tsk = task_of(se);

	अगर (sleep_start) अणु
		u64 delta = rq_घड़ी(rq_of(cfs_rq)) - sleep_start;

		अगर ((s64)delta < 0)
			delta = 0;

		अगर (unlikely(delta > schedstat_val(se->statistics.sleep_max)))
			__schedstat_set(se->statistics.sleep_max, delta);

		__schedstat_set(se->statistics.sleep_start, 0);
		__schedstat_add(se->statistics.sum_sleep_runसमय, delta);

		अगर (tsk) अणु
			account_scheduler_latency(tsk, delta >> 10, 1);
			trace_sched_stat_sleep(tsk, delta);
		पूर्ण
	पूर्ण
	अगर (block_start) अणु
		u64 delta = rq_घड़ी(rq_of(cfs_rq)) - block_start;

		अगर ((s64)delta < 0)
			delta = 0;

		अगर (unlikely(delta > schedstat_val(se->statistics.block_max)))
			__schedstat_set(se->statistics.block_max, delta);

		__schedstat_set(se->statistics.block_start, 0);
		__schedstat_add(se->statistics.sum_sleep_runसमय, delta);

		अगर (tsk) अणु
			अगर (tsk->in_ioरुको) अणु
				__schedstat_add(se->statistics.ioरुको_sum, delta);
				__schedstat_inc(se->statistics.ioरुको_count);
				trace_sched_stat_ioरुको(tsk, delta);
			पूर्ण

			trace_sched_stat_blocked(tsk, delta);

			/*
			 * Blocking समय is in units of nanosecs, so shअगरt by
			 * 20 to get a milliseconds-range estimation of the
			 * amount of समय that the task spent sleeping:
			 */
			अगर (unlikely(prof_on == SLEEP_PROFILING)) अणु
				profile_hits(SLEEP_PROFILING,
						(व्योम *)get_wchan(tsk),
						delta >> 20);
			पूर्ण
			account_scheduler_latency(tsk, delta >> 10, 0);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Task is being enqueued - update stats:
 */
अटल अंतरभूत व्योम
update_stats_enqueue(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, पूर्णांक flags)
अणु
	अगर (!schedstat_enabled())
		वापस;

	/*
	 * Are we enqueueing a रुकोing task? (क्रम current tasks
	 * a dequeue/enqueue event is a NOP)
	 */
	अगर (se != cfs_rq->curr)
		update_stats_रुको_start(cfs_rq, se);

	अगर (flags & ENQUEUE_WAKEUP)
		update_stats_enqueue_sleeper(cfs_rq, se);
पूर्ण

अटल अंतरभूत व्योम
update_stats_dequeue(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, पूर्णांक flags)
अणु

	अगर (!schedstat_enabled())
		वापस;

	/*
	 * Mark the end of the रुको period अगर dequeueing a
	 * रुकोing task:
	 */
	अगर (se != cfs_rq->curr)
		update_stats_रुको_end(cfs_rq, se);

	अगर ((flags & DEQUEUE_SLEEP) && entity_is_task(se)) अणु
		काष्ठा task_काष्ठा *tsk = task_of(se);

		अगर (tsk->state & TASK_INTERRUPTIBLE)
			__schedstat_set(se->statistics.sleep_start,
				      rq_घड़ी(rq_of(cfs_rq)));
		अगर (tsk->state & TASK_UNINTERRUPTIBLE)
			__schedstat_set(se->statistics.block_start,
				      rq_घड़ी(rq_of(cfs_rq)));
	पूर्ण
पूर्ण

/*
 * We are picking a new current task - update its stats:
 */
अटल अंतरभूत व्योम
update_stats_curr_start(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	/*
	 * We are starting a new run period:
	 */
	se->exec_start = rq_घड़ी_प्रकारask(rq_of(cfs_rq));
पूर्ण

/**************************************************
 * Scheduling class queueing methods:
 */

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * Approximate समय to scan a full NUMA task in ms. The task scan period is
 * calculated based on the tasks भव memory size and
 * numa_balancing_scan_size.
 */
अचिन्हित पूर्णांक sysctl_numa_balancing_scan_period_min = 1000;
अचिन्हित पूर्णांक sysctl_numa_balancing_scan_period_max = 60000;

/* Portion of address space to scan in MB */
अचिन्हित पूर्णांक sysctl_numa_balancing_scan_size = 256;

/* Scan @scan_size MB every @scan_period after an initial @scan_delay in ms */
अचिन्हित पूर्णांक sysctl_numa_balancing_scan_delay = 1000;

काष्ठा numa_group अणु
	refcount_t refcount;

	spinlock_t lock; /* nr_tasks, tasks */
	पूर्णांक nr_tasks;
	pid_t gid;
	पूर्णांक active_nodes;

	काष्ठा rcu_head rcu;
	अचिन्हित दीर्घ total_faults;
	अचिन्हित दीर्घ max_faults_cpu;
	/*
	 * Faults_cpu is used to decide whether memory should move
	 * towards the CPU. As a consequence, these stats are weighted
	 * more by CPU use than by memory faults.
	 */
	अचिन्हित दीर्घ *faults_cpu;
	अचिन्हित दीर्घ faults[];
पूर्ण;

/*
 * For functions that can be called in multiple contexts that permit पढ़ोing
 * ->numa_group (see काष्ठा task_काष्ठा क्रम locking rules).
 */
अटल काष्ठा numa_group *deref_task_numa_group(काष्ठा task_काष्ठा *p)
अणु
	वापस rcu_dereference_check(p->numa_group, p == current ||
		(lockdep_is_held(&task_rq(p)->lock) && !READ_ONCE(p->on_cpu)));
पूर्ण

अटल काष्ठा numa_group *deref_curr_numa_group(काष्ठा task_काष्ठा *p)
अणु
	वापस rcu_dereference_रक्षित(p->numa_group, p == current);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ group_faults_priv(काष्ठा numa_group *ng);
अटल अंतरभूत अचिन्हित दीर्घ group_faults_shared(काष्ठा numa_group *ng);

अटल अचिन्हित पूर्णांक task_nr_scan_winकरोws(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ rss = 0;
	अचिन्हित दीर्घ nr_scan_pages;

	/*
	 * Calculations based on RSS as non-present and empty pages are skipped
	 * by the PTE scanner and NUMA hपूर्णांकing faults should be trapped based
	 * on resident pages
	 */
	nr_scan_pages = sysctl_numa_balancing_scan_size << (20 - PAGE_SHIFT);
	rss = get_mm_rss(p->mm);
	अगर (!rss)
		rss = nr_scan_pages;

	rss = round_up(rss, nr_scan_pages);
	वापस rss / nr_scan_pages;
पूर्ण

/* For sanity's sake, never scan more PTEs than MAX_SCAN_WINDOW MB/sec. */
#घोषणा MAX_SCAN_WINDOW 2560

अटल अचिन्हित पूर्णांक task_scan_min(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक scan_size = READ_ONCE(sysctl_numa_balancing_scan_size);
	अचिन्हित पूर्णांक scan, न्यूनमान;
	अचिन्हित पूर्णांक winकरोws = 1;

	अगर (scan_size < MAX_SCAN_WINDOW)
		winकरोws = MAX_SCAN_WINDOW / scan_size;
	न्यूनमान = 1000 / winकरोws;

	scan = sysctl_numa_balancing_scan_period_min / task_nr_scan_winकरोws(p);
	वापस max_t(अचिन्हित पूर्णांक, न्यूनमान, scan);
पूर्ण

अटल अचिन्हित पूर्णांक task_scan_start(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ smin = task_scan_min(p);
	अचिन्हित दीर्घ period = smin;
	काष्ठा numa_group *ng;

	/* Scale the maximum scan period with the amount of shared memory. */
	rcu_पढ़ो_lock();
	ng = rcu_dereference(p->numa_group);
	अगर (ng) अणु
		अचिन्हित दीर्घ shared = group_faults_shared(ng);
		अचिन्हित दीर्घ निजी = group_faults_priv(ng);

		period *= refcount_पढ़ो(&ng->refcount);
		period *= shared + 1;
		period /= निजी + shared + 1;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस max(smin, period);
पूर्ण

अटल अचिन्हित पूर्णांक task_scan_max(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ smin = task_scan_min(p);
	अचिन्हित दीर्घ smax;
	काष्ठा numa_group *ng;

	/* Watch क्रम min being lower than max due to न्यूनमान calculations */
	smax = sysctl_numa_balancing_scan_period_max / task_nr_scan_winकरोws(p);

	/* Scale the maximum scan period with the amount of shared memory. */
	ng = deref_curr_numa_group(p);
	अगर (ng) अणु
		अचिन्हित दीर्घ shared = group_faults_shared(ng);
		अचिन्हित दीर्घ निजी = group_faults_priv(ng);
		अचिन्हित दीर्घ period = smax;

		period *= refcount_पढ़ो(&ng->refcount);
		period *= shared + 1;
		period /= निजी + shared + 1;

		smax = max(smax, period);
	पूर्ण

	वापस max(smin, smax);
पूर्ण

अटल व्योम account_numa_enqueue(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	rq->nr_numa_running += (p->numa_preferred_nid != NUMA_NO_NODE);
	rq->nr_preferred_running += (p->numa_preferred_nid == task_node(p));
पूर्ण

अटल व्योम account_numa_dequeue(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	rq->nr_numa_running -= (p->numa_preferred_nid != NUMA_NO_NODE);
	rq->nr_preferred_running -= (p->numa_preferred_nid == task_node(p));
पूर्ण

/* Shared or निजी faults. */
#घोषणा NR_NUMA_HINT_FAULT_TYPES 2

/* Memory and CPU locality */
#घोषणा NR_NUMA_HINT_FAULT_STATS (NR_NUMA_HINT_FAULT_TYPES * 2)

/* Averaged statistics, and temporary buffers. */
#घोषणा NR_NUMA_HINT_FAULT_BUCKETS (NR_NUMA_HINT_FAULT_STATS * 2)

pid_t task_numa_group_id(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा numa_group *ng;
	pid_t gid = 0;

	rcu_पढ़ो_lock();
	ng = rcu_dereference(p->numa_group);
	अगर (ng)
		gid = ng->gid;
	rcu_पढ़ो_unlock();

	वापस gid;
पूर्ण

/*
 * The averaged statistics, shared & निजी, memory & CPU,
 * occupy the first half of the array. The second half of the
 * array is क्रम current counters, which are averaged पूर्णांकo the
 * first set by task_numa_placement.
 */
अटल अंतरभूत पूर्णांक task_faults_idx(क्रमागत numa_faults_stats s, पूर्णांक nid, पूर्णांक priv)
अणु
	वापस NR_NUMA_HINT_FAULT_TYPES * (s * nr_node_ids + nid) + priv;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ task_faults(काष्ठा task_काष्ठा *p, पूर्णांक nid)
अणु
	अगर (!p->numa_faults)
		वापस 0;

	वापस p->numa_faults[task_faults_idx(NUMA_MEM, nid, 0)] +
		p->numa_faults[task_faults_idx(NUMA_MEM, nid, 1)];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ group_faults(काष्ठा task_काष्ठा *p, पूर्णांक nid)
अणु
	काष्ठा numa_group *ng = deref_task_numa_group(p);

	अगर (!ng)
		वापस 0;

	वापस ng->faults[task_faults_idx(NUMA_MEM, nid, 0)] +
		ng->faults[task_faults_idx(NUMA_MEM, nid, 1)];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ group_faults_cpu(काष्ठा numa_group *group, पूर्णांक nid)
अणु
	वापस group->faults_cpu[task_faults_idx(NUMA_MEM, nid, 0)] +
		group->faults_cpu[task_faults_idx(NUMA_MEM, nid, 1)];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ group_faults_priv(काष्ठा numa_group *ng)
अणु
	अचिन्हित दीर्घ faults = 0;
	पूर्णांक node;

	क्रम_each_online_node(node) अणु
		faults += ng->faults[task_faults_idx(NUMA_MEM, node, 1)];
	पूर्ण

	वापस faults;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ group_faults_shared(काष्ठा numa_group *ng)
अणु
	अचिन्हित दीर्घ faults = 0;
	पूर्णांक node;

	क्रम_each_online_node(node) अणु
		faults += ng->faults[task_faults_idx(NUMA_MEM, node, 0)];
	पूर्ण

	वापस faults;
पूर्ण

/*
 * A node triggering more than 1/3 as many NUMA faults as the maximum is
 * considered part of a numa group's pseuकरो-पूर्णांकerleaving set. Migrations
 * between these nodes are slowed करोwn, to allow things to settle करोwn.
 */
#घोषणा ACTIVE_NODE_FRACTION 3

अटल bool numa_is_active_node(पूर्णांक nid, काष्ठा numa_group *ng)
अणु
	वापस group_faults_cpu(ng, nid) * ACTIVE_NODE_FRACTION > ng->max_faults_cpu;
पूर्ण

/* Handle placement on प्रणालीs where not all nodes are directly connected. */
अटल अचिन्हित दीर्घ score_nearby_nodes(काष्ठा task_काष्ठा *p, पूर्णांक nid,
					पूर्णांक maxdist, bool task)
अणु
	अचिन्हित दीर्घ score = 0;
	पूर्णांक node;

	/*
	 * All nodes are directly connected, and the same distance
	 * from each other. No need क्रम fancy placement algorithms.
	 */
	अगर (sched_numa_topology_type == NUMA_सूचीECT)
		वापस 0;

	/*
	 * This code is called क्रम each node, पूर्णांकroducing N^2 complनिकासy,
	 * which should be ok given the number of nodes rarely exceeds 8.
	 */
	क्रम_each_online_node(node) अणु
		अचिन्हित दीर्घ faults;
		पूर्णांक dist = node_distance(nid, node);

		/*
		 * The furthest away nodes in the प्रणाली are not पूर्णांकeresting
		 * क्रम placement; nid was alपढ़ोy counted.
		 */
		अगर (dist == sched_max_numa_distance || node == nid)
			जारी;

		/*
		 * On प्रणालीs with a backplane NUMA topology, compare groups
		 * of nodes, and move tasks towards the group with the most
		 * memory accesses. When comparing two nodes at distance
		 * "hoplimit", only nodes बंदr by than "hoplimit" are part
		 * of each group. Skip other nodes.
		 */
		अगर (sched_numa_topology_type == NUMA_BACKPLANE &&
					dist >= maxdist)
			जारी;

		/* Add up the faults from nearby nodes. */
		अगर (task)
			faults = task_faults(p, node);
		अन्यथा
			faults = group_faults(p, node);

		/*
		 * On प्रणालीs with a glueless mesh NUMA topology, there are
		 * no fixed "groups of nodes". Instead, nodes that are not
		 * directly connected bounce traffic through पूर्णांकermediate
		 * nodes; a numa_group can occupy any set of nodes.
		 * The further away a node is, the less the faults count.
		 * This seems to result in good task placement.
		 */
		अगर (sched_numa_topology_type == NUMA_GLUELESS_MESH) अणु
			faults *= (sched_max_numa_distance - dist);
			faults /= (sched_max_numa_distance - LOCAL_DISTANCE);
		पूर्ण

		score += faults;
	पूर्ण

	वापस score;
पूर्ण

/*
 * These वापस the fraction of accesses करोne by a particular task, or
 * task group, on a particular numa node.  The group weight is given a
 * larger multiplier, in order to group tasks together that are almost
 * evenly spपढ़ो out between numa nodes.
 */
अटल अंतरभूत अचिन्हित दीर्घ task_weight(काष्ठा task_काष्ठा *p, पूर्णांक nid,
					पूर्णांक dist)
अणु
	अचिन्हित दीर्घ faults, total_faults;

	अगर (!p->numa_faults)
		वापस 0;

	total_faults = p->total_numa_faults;

	अगर (!total_faults)
		वापस 0;

	faults = task_faults(p, nid);
	faults += score_nearby_nodes(p, nid, dist, true);

	वापस 1000 * faults / total_faults;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ group_weight(काष्ठा task_काष्ठा *p, पूर्णांक nid,
					 पूर्णांक dist)
अणु
	काष्ठा numa_group *ng = deref_task_numa_group(p);
	अचिन्हित दीर्घ faults, total_faults;

	अगर (!ng)
		वापस 0;

	total_faults = ng->total_faults;

	अगर (!total_faults)
		वापस 0;

	faults = group_faults(p, nid);
	faults += score_nearby_nodes(p, nid, dist, false);

	वापस 1000 * faults / total_faults;
पूर्ण

bool should_numa_migrate_memory(काष्ठा task_काष्ठा *p, काष्ठा page * page,
				पूर्णांक src_nid, पूर्णांक dst_cpu)
अणु
	काष्ठा numa_group *ng = deref_curr_numa_group(p);
	पूर्णांक dst_nid = cpu_to_node(dst_cpu);
	पूर्णांक last_cpupid, this_cpupid;

	this_cpupid = cpu_pid_to_cpupid(dst_cpu, current->pid);
	last_cpupid = page_cpupid_xchg_last(page, this_cpupid);

	/*
	 * Allow first faults or निजी faults to migrate immediately early in
	 * the lअगरeसमय of a task. The magic number 4 is based on रुकोing क्रम
	 * two full passes of the "multi-stage node selection" test that is
	 * executed below.
	 */
	अगर ((p->numa_preferred_nid == NUMA_NO_NODE || p->numa_scan_seq <= 4) &&
	    (cpupid_pid_unset(last_cpupid) || cpupid_match_pid(p, last_cpupid)))
		वापस true;

	/*
	 * Multi-stage node selection is used in conjunction with a periodic
	 * migration fault to build a temporal task<->page relation. By using
	 * a two-stage filter we हटाओ लघु/unlikely relations.
	 *
	 * Using P(p) ~ n_p / n_t as per frequentist probability, we can equate
	 * a task's usage of a particular page (n_p) per total usage of this
	 * page (n_t) (in a given समय-span) to a probability.
	 *
	 * Our periodic faults will sample this probability and getting the
	 * same result twice in a row, given these samples are fully
	 * independent, is then given by P(n)^2, provided our sample period
	 * is sufficiently लघु compared to the usage pattern.
	 *
	 * This quadric squishes small probabilities, making it less likely we
	 * act on an unlikely task<->page relation.
	 */
	अगर (!cpupid_pid_unset(last_cpupid) &&
				cpupid_to_nid(last_cpupid) != dst_nid)
		वापस false;

	/* Always allow migrate on निजी faults */
	अगर (cpupid_match_pid(p, last_cpupid))
		वापस true;

	/* A shared fault, but p->numa_group has not been set up yet. */
	अगर (!ng)
		वापस true;

	/*
	 * Destination node is much more heavily used than the source
	 * node? Allow migration.
	 */
	अगर (group_faults_cpu(ng, dst_nid) > group_faults_cpu(ng, src_nid) *
					ACTIVE_NODE_FRACTION)
		वापस true;

	/*
	 * Distribute memory according to CPU & memory use on each node,
	 * with 3/4 hysteresis to aव्योम unnecessary memory migrations:
	 *
	 * faults_cpu(dst)   3   faults_cpu(src)
	 * --------------- * - > ---------------
	 * faults_mem(dst)   4   faults_mem(src)
	 */
	वापस group_faults_cpu(ng, dst_nid) * group_faults(p, src_nid) * 3 >
	       group_faults_cpu(ng, src_nid) * group_faults(p, dst_nid) * 4;
पूर्ण

/*
 * 'numa_type' describes the node at the moment of load balancing.
 */
क्रमागत numa_type अणु
	/* The node has spare capacity that can be used to run more tasks.  */
	node_has_spare = 0,
	/*
	 * The node is fully used and the tasks करोn't compete क्रम more CPU
	 * cycles. Nevertheless, some tasks might रुको beक्रमe running.
	 */
	node_fully_busy,
	/*
	 * The node is overloaded and can't provide expected CPU cycles to all
	 * tasks.
	 */
	node_overloaded
पूर्ण;

/* Cached statistics क्रम all CPUs within a node */
काष्ठा numa_stats अणु
	अचिन्हित दीर्घ load;
	अचिन्हित दीर्घ runnable;
	अचिन्हित दीर्घ util;
	/* Total compute capacity of CPUs on a node */
	अचिन्हित दीर्घ compute_capacity;
	अचिन्हित पूर्णांक nr_running;
	अचिन्हित पूर्णांक weight;
	क्रमागत numa_type node_type;
	पूर्णांक idle_cpu;
पूर्ण;

अटल अंतरभूत bool is_core_idle(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SCHED_SMT
	पूर्णांक sibling;

	क्रम_each_cpu(sibling, cpu_smt_mask(cpu)) अणु
		अगर (cpu == sibling)
			जारी;

		अगर (!idle_cpu(cpu))
			वापस false;
	पूर्ण
#पूर्ण_अगर

	वापस true;
पूर्ण

काष्ठा task_numa_env अणु
	काष्ठा task_काष्ठा *p;

	पूर्णांक src_cpu, src_nid;
	पूर्णांक dst_cpu, dst_nid;

	काष्ठा numa_stats src_stats, dst_stats;

	पूर्णांक imbalance_pct;
	पूर्णांक dist;

	काष्ठा task_काष्ठा *best_task;
	दीर्घ best_imp;
	पूर्णांक best_cpu;
पूर्ण;

अटल अचिन्हित दीर्घ cpu_load(काष्ठा rq *rq);
अटल अचिन्हित दीर्घ cpu_runnable(काष्ठा rq *rq);
अटल अचिन्हित दीर्घ cpu_util(पूर्णांक cpu);
अटल अंतरभूत दीर्घ adjust_numa_imbalance(पूर्णांक imbalance,
					पूर्णांक dst_running, पूर्णांक dst_weight);

अटल अंतरभूत क्रमागत
numa_type numa_classअगरy(अचिन्हित पूर्णांक imbalance_pct,
			 काष्ठा numa_stats *ns)
अणु
	अगर ((ns->nr_running > ns->weight) &&
	    (((ns->compute_capacity * 100) < (ns->util * imbalance_pct)) ||
	     ((ns->compute_capacity * imbalance_pct) < (ns->runnable * 100))))
		वापस node_overloaded;

	अगर ((ns->nr_running < ns->weight) ||
	    (((ns->compute_capacity * 100) > (ns->util * imbalance_pct)) &&
	     ((ns->compute_capacity * imbalance_pct) > (ns->runnable * 100))))
		वापस node_has_spare;

	वापस node_fully_busy;
पूर्ण

#अगर_घोषित CONFIG_SCHED_SMT
/* Forward declarations of select_idle_sibling helpers */
अटल अंतरभूत bool test_idle_cores(पूर्णांक cpu, bool def);
अटल अंतरभूत पूर्णांक numa_idle_core(पूर्णांक idle_core, पूर्णांक cpu)
अणु
	अगर (!अटल_branch_likely(&sched_smt_present) ||
	    idle_core >= 0 || !test_idle_cores(cpu, false))
		वापस idle_core;

	/*
	 * Prefer cores instead of packing HT siblings
	 * and triggering future load balancing.
	 */
	अगर (is_core_idle(cpu))
		idle_core = cpu;

	वापस idle_core;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक numa_idle_core(पूर्णांक idle_core, पूर्णांक cpu)
अणु
	वापस idle_core;
पूर्ण
#पूर्ण_अगर

/*
 * Gather all necessary inक्रमmation to make NUMA balancing placement
 * decisions that are compatible with standard load balancer. This
 * borrows code and logic from update_sg_lb_stats but sharing a
 * common implementation is impractical.
 */
अटल व्योम update_numa_stats(काष्ठा task_numa_env *env,
			      काष्ठा numa_stats *ns, पूर्णांक nid,
			      bool find_idle)
अणु
	पूर्णांक cpu, idle_core = -1;

	स_रखो(ns, 0, माप(*ns));
	ns->idle_cpu = -1;

	rcu_पढ़ो_lock();
	क्रम_each_cpu(cpu, cpumask_of_node(nid)) अणु
		काष्ठा rq *rq = cpu_rq(cpu);

		ns->load += cpu_load(rq);
		ns->runnable += cpu_runnable(rq);
		ns->util += cpu_util(cpu);
		ns->nr_running += rq->cfs.h_nr_running;
		ns->compute_capacity += capacity_of(cpu);

		अगर (find_idle && !rq->nr_running && idle_cpu(cpu)) अणु
			अगर (READ_ONCE(rq->numa_migrate_on) ||
			    !cpumask_test_cpu(cpu, env->p->cpus_ptr))
				जारी;

			अगर (ns->idle_cpu == -1)
				ns->idle_cpu = cpu;

			idle_core = numa_idle_core(idle_core, cpu);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	ns->weight = cpumask_weight(cpumask_of_node(nid));

	ns->node_type = numa_classअगरy(env->imbalance_pct, ns);

	अगर (idle_core >= 0)
		ns->idle_cpu = idle_core;
पूर्ण

अटल व्योम task_numa_assign(काष्ठा task_numa_env *env,
			     काष्ठा task_काष्ठा *p, दीर्घ imp)
अणु
	काष्ठा rq *rq = cpu_rq(env->dst_cpu);

	/* Check अगर run-queue part of active NUMA balance. */
	अगर (env->best_cpu != env->dst_cpu && xchg(&rq->numa_migrate_on, 1)) अणु
		पूर्णांक cpu;
		पूर्णांक start = env->dst_cpu;

		/* Find alternative idle CPU. */
		क्रम_each_cpu_wrap(cpu, cpumask_of_node(env->dst_nid), start) अणु
			अगर (cpu == env->best_cpu || !idle_cpu(cpu) ||
			    !cpumask_test_cpu(cpu, env->p->cpus_ptr)) अणु
				जारी;
			पूर्ण

			env->dst_cpu = cpu;
			rq = cpu_rq(env->dst_cpu);
			अगर (!xchg(&rq->numa_migrate_on, 1))
				जाओ assign;
		पूर्ण

		/* Failed to find an alternative idle CPU */
		वापस;
	पूर्ण

assign:
	/*
	 * Clear previous best_cpu/rq numa-migrate flag, since task now
	 * found a better CPU to move/swap.
	 */
	अगर (env->best_cpu != -1 && env->best_cpu != env->dst_cpu) अणु
		rq = cpu_rq(env->best_cpu);
		WRITE_ONCE(rq->numa_migrate_on, 0);
	पूर्ण

	अगर (env->best_task)
		put_task_काष्ठा(env->best_task);
	अगर (p)
		get_task_काष्ठा(p);

	env->best_task = p;
	env->best_imp = imp;
	env->best_cpu = env->dst_cpu;
पूर्ण

अटल bool load_too_imbalanced(दीर्घ src_load, दीर्घ dst_load,
				काष्ठा task_numa_env *env)
अणु
	दीर्घ imb, old_imb;
	दीर्घ orig_src_load, orig_dst_load;
	दीर्घ src_capacity, dst_capacity;

	/*
	 * The load is corrected क्रम the CPU capacity available on each node.
	 *
	 * src_load        dst_load
	 * ------------ vs ---------
	 * src_capacity    dst_capacity
	 */
	src_capacity = env->src_stats.compute_capacity;
	dst_capacity = env->dst_stats.compute_capacity;

	imb = असल(dst_load * src_capacity - src_load * dst_capacity);

	orig_src_load = env->src_stats.load;
	orig_dst_load = env->dst_stats.load;

	old_imb = असल(orig_dst_load * src_capacity - orig_src_load * dst_capacity);

	/* Would this change make things worse? */
	वापस (imb > old_imb);
पूर्ण

/*
 * Maximum NUMA importance can be 1998 (2*999);
 * SMALLIMP @ 30 would be बंद to 1998/64.
 * Used to deter task migration.
 */
#घोषणा SMALLIMP	30

/*
 * This checks अगर the overall compute and NUMA accesses of the प्रणाली would
 * be improved अगर the source tasks was migrated to the target dst_cpu taking
 * पूर्णांकo account that it might be best अगर task running on the dst_cpu should
 * be exchanged with the source task
 */
अटल bool task_numa_compare(काष्ठा task_numa_env *env,
			      दीर्घ taskimp, दीर्घ groupimp, bool maymove)
अणु
	काष्ठा numa_group *cur_ng, *p_ng = deref_curr_numa_group(env->p);
	काष्ठा rq *dst_rq = cpu_rq(env->dst_cpu);
	दीर्घ imp = p_ng ? groupimp : taskimp;
	काष्ठा task_काष्ठा *cur;
	दीर्घ src_load, dst_load;
	पूर्णांक dist = env->dist;
	दीर्घ moveimp = imp;
	दीर्घ load;
	bool stopsearch = false;

	अगर (READ_ONCE(dst_rq->numa_migrate_on))
		वापस false;

	rcu_पढ़ो_lock();
	cur = rcu_dereference(dst_rq->curr);
	अगर (cur && ((cur->flags & PF_EXITING) || is_idle_task(cur)))
		cur = शून्य;

	/*
	 * Because we have preemption enabled we can get migrated around and
	 * end try selecting ourselves (current == env->p) as a swap candidate.
	 */
	अगर (cur == env->p) अणु
		stopsearch = true;
		जाओ unlock;
	पूर्ण

	अगर (!cur) अणु
		अगर (maymove && moveimp >= env->best_imp)
			जाओ assign;
		अन्यथा
			जाओ unlock;
	पूर्ण

	/* Skip this swap candidate अगर cannot move to the source cpu. */
	अगर (!cpumask_test_cpu(env->src_cpu, cur->cpus_ptr))
		जाओ unlock;

	/*
	 * Skip this swap candidate अगर it is not moving to its preferred
	 * node and the best task is.
	 */
	अगर (env->best_task &&
	    env->best_task->numa_preferred_nid == env->src_nid &&
	    cur->numa_preferred_nid != env->src_nid) अणु
		जाओ unlock;
	पूर्ण

	/*
	 * "imp" is the fault dअगरferential क्रम the source task between the
	 * source and destination node. Calculate the total dअगरferential क्रम
	 * the source task and potential destination task. The more negative
	 * the value is, the more remote accesses that would be expected to
	 * be incurred अगर the tasks were swapped.
	 *
	 * If dst and source tasks are in the same NUMA group, or not
	 * in any group then look only at task weights.
	 */
	cur_ng = rcu_dereference(cur->numa_group);
	अगर (cur_ng == p_ng) अणु
		imp = taskimp + task_weight(cur, env->src_nid, dist) -
		      task_weight(cur, env->dst_nid, dist);
		/*
		 * Add some hysteresis to prevent swapping the
		 * tasks within a group over tiny dअगरferences.
		 */
		अगर (cur_ng)
			imp -= imp / 16;
	पूर्ण अन्यथा अणु
		/*
		 * Compare the group weights. If a task is all by itself
		 * (not part of a group), use the task weight instead.
		 */
		अगर (cur_ng && p_ng)
			imp += group_weight(cur, env->src_nid, dist) -
			       group_weight(cur, env->dst_nid, dist);
		अन्यथा
			imp += task_weight(cur, env->src_nid, dist) -
			       task_weight(cur, env->dst_nid, dist);
	पूर्ण

	/* Discourage picking a task alपढ़ोy on its preferred node */
	अगर (cur->numa_preferred_nid == env->dst_nid)
		imp -= imp / 16;

	/*
	 * Encourage picking a task that moves to its preferred node.
	 * This potentially makes imp larger than it's maximum of
	 * 1998 (see SMALLIMP and task_weight क्रम why) but in this
	 * हाल, it करोes not matter.
	 */
	अगर (cur->numa_preferred_nid == env->src_nid)
		imp += imp / 8;

	अगर (maymove && moveimp > imp && moveimp > env->best_imp) अणु
		imp = moveimp;
		cur = शून्य;
		जाओ assign;
	पूर्ण

	/*
	 * Prefer swapping with a task moving to its preferred node over a
	 * task that is not.
	 */
	अगर (env->best_task && cur->numa_preferred_nid == env->src_nid &&
	    env->best_task->numa_preferred_nid != env->src_nid) अणु
		जाओ assign;
	पूर्ण

	/*
	 * If the NUMA importance is less than SMALLIMP,
	 * task migration might only result in ping pong
	 * of tasks and also hurt perक्रमmance due to cache
	 * misses.
	 */
	अगर (imp < SMALLIMP || imp <= env->best_imp + SMALLIMP / 2)
		जाओ unlock;

	/*
	 * In the overloaded हाल, try and keep the load balanced.
	 */
	load = task_h_load(env->p) - task_h_load(cur);
	अगर (!load)
		जाओ assign;

	dst_load = env->dst_stats.load + load;
	src_load = env->src_stats.load - load;

	अगर (load_too_imbalanced(src_load, dst_load, env))
		जाओ unlock;

assign:
	/* Evaluate an idle CPU क्रम a task numa move. */
	अगर (!cur) अणु
		पूर्णांक cpu = env->dst_stats.idle_cpu;

		/* Nothing cached so current CPU went idle since the search. */
		अगर (cpu < 0)
			cpu = env->dst_cpu;

		/*
		 * If the CPU is no दीर्घer truly idle and the previous best CPU
		 * is, keep using it.
		 */
		अगर (!idle_cpu(cpu) && env->best_cpu >= 0 &&
		    idle_cpu(env->best_cpu)) अणु
			cpu = env->best_cpu;
		पूर्ण

		env->dst_cpu = cpu;
	पूर्ण

	task_numa_assign(env, cur, imp);

	/*
	 * If a move to idle is allowed because there is capacity or load
	 * balance improves then stop the search. While a better swap
	 * candidate may exist, a search is not मुक्त.
	 */
	अगर (maymove && !cur && env->best_cpu >= 0 && idle_cpu(env->best_cpu))
		stopsearch = true;

	/*
	 * If a swap candidate must be identअगरied and the current best task
	 * moves its preferred node then stop the search.
	 */
	अगर (!maymove && env->best_task &&
	    env->best_task->numa_preferred_nid == env->src_nid) अणु
		stopsearch = true;
	पूर्ण
unlock:
	rcu_पढ़ो_unlock();

	वापस stopsearch;
पूर्ण

अटल व्योम task_numa_find_cpu(काष्ठा task_numa_env *env,
				दीर्घ taskimp, दीर्घ groupimp)
अणु
	bool maymove = false;
	पूर्णांक cpu;

	/*
	 * If dst node has spare capacity, then check अगर there is an
	 * imbalance that would be overruled by the load balancer.
	 */
	अगर (env->dst_stats.node_type == node_has_spare) अणु
		अचिन्हित पूर्णांक imbalance;
		पूर्णांक src_running, dst_running;

		/*
		 * Would movement cause an imbalance? Note that अगर src has
		 * more running tasks that the imbalance is ignored as the
		 * move improves the imbalance from the perspective of the
		 * CPU load balancer.
		 * */
		src_running = env->src_stats.nr_running - 1;
		dst_running = env->dst_stats.nr_running + 1;
		imbalance = max(0, dst_running - src_running);
		imbalance = adjust_numa_imbalance(imbalance, dst_running,
							env->dst_stats.weight);

		/* Use idle CPU अगर there is no imbalance */
		अगर (!imbalance) अणु
			maymove = true;
			अगर (env->dst_stats.idle_cpu >= 0) अणु
				env->dst_cpu = env->dst_stats.idle_cpu;
				task_numa_assign(env, शून्य, 0);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		दीर्घ src_load, dst_load, load;
		/*
		 * If the improvement from just moving env->p direction is better
		 * than swapping tasks around, check अगर a move is possible.
		 */
		load = task_h_load(env->p);
		dst_load = env->dst_stats.load + load;
		src_load = env->src_stats.load - load;
		maymove = !load_too_imbalanced(src_load, dst_load, env);
	पूर्ण

	क्रम_each_cpu(cpu, cpumask_of_node(env->dst_nid)) अणु
		/* Skip this CPU अगर the source task cannot migrate */
		अगर (!cpumask_test_cpu(cpu, env->p->cpus_ptr))
			जारी;

		env->dst_cpu = cpu;
		अगर (task_numa_compare(env, taskimp, groupimp, maymove))
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक task_numa_migrate(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा task_numa_env env = अणु
		.p = p,

		.src_cpu = task_cpu(p),
		.src_nid = task_node(p),

		.imbalance_pct = 112,

		.best_task = शून्य,
		.best_imp = 0,
		.best_cpu = -1,
	पूर्ण;
	अचिन्हित दीर्घ taskweight, groupweight;
	काष्ठा sched_करोमुख्य *sd;
	दीर्घ taskimp, groupimp;
	काष्ठा numa_group *ng;
	काष्ठा rq *best_rq;
	पूर्णांक nid, ret, dist;

	/*
	 * Pick the lowest SD_NUMA करोमुख्य, as that would have the smallest
	 * imbalance and would be the first to start moving tasks about.
	 *
	 * And we want to aव्योम any moving of tasks about, as that would create
	 * अक्रमom movement of tasks -- counter the numa conditions we're trying
	 * to satisfy here.
	 */
	rcu_पढ़ो_lock();
	sd = rcu_dereference(per_cpu(sd_numa, env.src_cpu));
	अगर (sd)
		env.imbalance_pct = 100 + (sd->imbalance_pct - 100) / 2;
	rcu_पढ़ो_unlock();

	/*
	 * Cpusets can अवरोध the scheduler करोमुख्य tree पूर्णांकo smaller
	 * balance करोमुख्यs, some of which करो not cross NUMA boundaries.
	 * Tasks that are "trapped" in such करोमुख्यs cannot be migrated
	 * अन्यथाwhere, so there is no poपूर्णांक in (re)trying.
	 */
	अगर (unlikely(!sd)) अणु
		sched_setnuma(p, task_node(p));
		वापस -EINVAL;
	पूर्ण

	env.dst_nid = p->numa_preferred_nid;
	dist = env.dist = node_distance(env.src_nid, env.dst_nid);
	taskweight = task_weight(p, env.src_nid, dist);
	groupweight = group_weight(p, env.src_nid, dist);
	update_numa_stats(&env, &env.src_stats, env.src_nid, false);
	taskimp = task_weight(p, env.dst_nid, dist) - taskweight;
	groupimp = group_weight(p, env.dst_nid, dist) - groupweight;
	update_numa_stats(&env, &env.dst_stats, env.dst_nid, true);

	/* Try to find a spot on the preferred nid. */
	task_numa_find_cpu(&env, taskimp, groupimp);

	/*
	 * Look at other nodes in these हालs:
	 * - there is no space available on the preferred_nid
	 * - the task is part of a numa_group that is पूर्णांकerleaved across
	 *   multiple NUMA nodes; in order to better consolidate the group,
	 *   we need to check other locations.
	 */
	ng = deref_curr_numa_group(p);
	अगर (env.best_cpu == -1 || (ng && ng->active_nodes > 1)) अणु
		क्रम_each_online_node(nid) अणु
			अगर (nid == env.src_nid || nid == p->numa_preferred_nid)
				जारी;

			dist = node_distance(env.src_nid, env.dst_nid);
			अगर (sched_numa_topology_type == NUMA_BACKPLANE &&
						dist != env.dist) अणु
				taskweight = task_weight(p, env.src_nid, dist);
				groupweight = group_weight(p, env.src_nid, dist);
			पूर्ण

			/* Only consider nodes where both task and groups benefit */
			taskimp = task_weight(p, nid, dist) - taskweight;
			groupimp = group_weight(p, nid, dist) - groupweight;
			अगर (taskimp < 0 && groupimp < 0)
				जारी;

			env.dist = dist;
			env.dst_nid = nid;
			update_numa_stats(&env, &env.dst_stats, env.dst_nid, true);
			task_numa_find_cpu(&env, taskimp, groupimp);
		पूर्ण
	पूर्ण

	/*
	 * If the task is part of a workload that spans multiple NUMA nodes,
	 * and is migrating पूर्णांकo one of the workload's active nodes, remember
	 * this node as the task's preferred numa node, so the workload can
	 * settle करोwn.
	 * A task that migrated to a second choice node will be better off
	 * trying क्रम a better one later. Do not set the preferred node here.
	 */
	अगर (ng) अणु
		अगर (env.best_cpu == -1)
			nid = env.src_nid;
		अन्यथा
			nid = cpu_to_node(env.best_cpu);

		अगर (nid != p->numa_preferred_nid)
			sched_setnuma(p, nid);
	पूर्ण

	/* No better CPU than the current one was found. */
	अगर (env.best_cpu == -1) अणु
		trace_sched_stick_numa(p, env.src_cpu, शून्य, -1);
		वापस -EAGAIN;
	पूर्ण

	best_rq = cpu_rq(env.best_cpu);
	अगर (env.best_task == शून्य) अणु
		ret = migrate_task_to(p, env.best_cpu);
		WRITE_ONCE(best_rq->numa_migrate_on, 0);
		अगर (ret != 0)
			trace_sched_stick_numa(p, env.src_cpu, शून्य, env.best_cpu);
		वापस ret;
	पूर्ण

	ret = migrate_swap(p, env.best_task, env.best_cpu, env.src_cpu);
	WRITE_ONCE(best_rq->numa_migrate_on, 0);

	अगर (ret != 0)
		trace_sched_stick_numa(p, env.src_cpu, env.best_task, env.best_cpu);
	put_task_काष्ठा(env.best_task);
	वापस ret;
पूर्ण

/* Attempt to migrate a task to a CPU on the preferred node. */
अटल व्योम numa_migrate_preferred(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = HZ;

	/* This task has no NUMA fault statistics yet */
	अगर (unlikely(p->numa_preferred_nid == NUMA_NO_NODE || !p->numa_faults))
		वापस;

	/* Periodically retry migrating the task to the preferred node */
	पूर्णांकerval = min(पूर्णांकerval, msecs_to_jअगरfies(p->numa_scan_period) / 16);
	p->numa_migrate_retry = jअगरfies + पूर्णांकerval;

	/* Success अगर task is alपढ़ोy running on preferred CPU */
	अगर (task_node(p) == p->numa_preferred_nid)
		वापस;

	/* Otherwise, try migrate to a CPU on the preferred node */
	task_numa_migrate(p);
पूर्ण

/*
 * Find out how many nodes on the workload is actively running on. Do this by
 * tracking the nodes from which NUMA hपूर्णांकing faults are triggered. This can
 * be dअगरferent from the set of nodes where the workload's memory is currently
 * located.
 */
अटल व्योम numa_group_count_active_nodes(काष्ठा numa_group *numa_group)
अणु
	अचिन्हित दीर्घ faults, max_faults = 0;
	पूर्णांक nid, active_nodes = 0;

	क्रम_each_online_node(nid) अणु
		faults = group_faults_cpu(numa_group, nid);
		अगर (faults > max_faults)
			max_faults = faults;
	पूर्ण

	क्रम_each_online_node(nid) अणु
		faults = group_faults_cpu(numa_group, nid);
		अगर (faults * ACTIVE_NODE_FRACTION > max_faults)
			active_nodes++;
	पूर्ण

	numa_group->max_faults_cpu = max_faults;
	numa_group->active_nodes = active_nodes;
पूर्ण

/*
 * When adapting the scan rate, the period is भागided पूर्णांकo NUMA_PERIOD_SLOTS
 * increments. The more local the fault statistics are, the higher the scan
 * period will be क्रम the next scan winकरोw. If local/(local+remote) ratio is
 * below NUMA_PERIOD_THRESHOLD (where range of ratio is 1..NUMA_PERIOD_SLOTS)
 * the scan period will decrease. Aim क्रम 70% local accesses.
 */
#घोषणा NUMA_PERIOD_SLOTS 10
#घोषणा NUMA_PERIOD_THRESHOLD 7

/*
 * Increase the scan period (slow करोwn scanning) अगर the majority of
 * our memory is alपढ़ोy on our local node, or अगर the majority of
 * the page accesses are shared with other processes.
 * Otherwise, decrease the scan period.
 */
अटल व्योम update_task_scan_period(काष्ठा task_काष्ठा *p,
			अचिन्हित दीर्घ shared, अचिन्हित दीर्घ निजी)
अणु
	अचिन्हित पूर्णांक period_slot;
	पूर्णांक lr_ratio, ps_ratio;
	पूर्णांक dअगरf;

	अचिन्हित दीर्घ remote = p->numa_faults_locality[0];
	अचिन्हित दीर्घ local = p->numa_faults_locality[1];

	/*
	 * If there were no record hपूर्णांकing faults then either the task is
	 * completely idle or all activity is areas that are not of पूर्णांकerest
	 * to स्वतःmatic numa balancing. Related to that, अगर there were failed
	 * migration then it implies we are migrating too quickly or the local
	 * node is overloaded. In either हाल, scan slower
	 */
	अगर (local + shared == 0 || p->numa_faults_locality[2]) अणु
		p->numa_scan_period = min(p->numa_scan_period_max,
			p->numa_scan_period << 1);

		p->mm->numa_next_scan = jअगरfies +
			msecs_to_jअगरfies(p->numa_scan_period);

		वापस;
	पूर्ण

	/*
	 * Prepare to scale scan period relative to the current period.
	 *	 == NUMA_PERIOD_THRESHOLD scan period stays the same
	 *       <  NUMA_PERIOD_THRESHOLD scan period decreases (scan faster)
	 *	 >= NUMA_PERIOD_THRESHOLD scan period increases (scan slower)
	 */
	period_slot = DIV_ROUND_UP(p->numa_scan_period, NUMA_PERIOD_SLOTS);
	lr_ratio = (local * NUMA_PERIOD_SLOTS) / (local + remote);
	ps_ratio = (निजी * NUMA_PERIOD_SLOTS) / (निजी + shared);

	अगर (ps_ratio >= NUMA_PERIOD_THRESHOLD) अणु
		/*
		 * Most memory accesses are local. There is no need to
		 * करो fast NUMA scanning, since memory is alपढ़ोy local.
		 */
		पूर्णांक slot = ps_ratio - NUMA_PERIOD_THRESHOLD;
		अगर (!slot)
			slot = 1;
		dअगरf = slot * period_slot;
	पूर्ण अन्यथा अगर (lr_ratio >= NUMA_PERIOD_THRESHOLD) अणु
		/*
		 * Most memory accesses are shared with other tasks.
		 * There is no poपूर्णांक in continuing fast NUMA scanning,
		 * since other tasks may just move the memory अन्यथाwhere.
		 */
		पूर्णांक slot = lr_ratio - NUMA_PERIOD_THRESHOLD;
		अगर (!slot)
			slot = 1;
		dअगरf = slot * period_slot;
	पूर्ण अन्यथा अणु
		/*
		 * Private memory faults exceed (SLOTS-THRESHOLD)/SLOTS,
		 * yet they are not on the local NUMA node. Speed up
		 * NUMA scanning to get the memory moved over.
		 */
		पूर्णांक ratio = max(lr_ratio, ps_ratio);
		dअगरf = -(NUMA_PERIOD_THRESHOLD - ratio) * period_slot;
	पूर्ण

	p->numa_scan_period = clamp(p->numa_scan_period + dअगरf,
			task_scan_min(p), task_scan_max(p));
	स_रखो(p->numa_faults_locality, 0, माप(p->numa_faults_locality));
पूर्ण

/*
 * Get the fraction of समय the task has been running since the last
 * NUMA placement cycle. The scheduler keeps similar statistics, but
 * decays those on a 32ms period, which is orders of magnitude off
 * from the करोzens-of-seconds NUMA balancing period. Use the scheduler
 * stats only अगर the task is so new there are no NUMA statistics yet.
 */
अटल u64 numa_get_avg_runसमय(काष्ठा task_काष्ठा *p, u64 *period)
अणु
	u64 runसमय, delta, now;
	/* Use the start of this समय slice to aव्योम calculations. */
	now = p->se.exec_start;
	runसमय = p->se.sum_exec_runसमय;

	अगर (p->last_task_numa_placement) अणु
		delta = runसमय - p->last_sum_exec_runसमय;
		*period = now - p->last_task_numa_placement;

		/* Aव्योम समय going backwards, prevent potential भागide error: */
		अगर (unlikely((s64)*period < 0))
			*period = 0;
	पूर्ण अन्यथा अणु
		delta = p->se.avg.load_sum;
		*period = LOAD_AVG_MAX;
	पूर्ण

	p->last_sum_exec_runसमय = runसमय;
	p->last_task_numa_placement = now;

	वापस delta;
पूर्ण

/*
 * Determine the preferred nid क्रम a task in a numa_group. This needs to
 * be करोne in a way that produces consistent results with group_weight,
 * otherwise workloads might not converge.
 */
अटल पूर्णांक preferred_group_nid(काष्ठा task_काष्ठा *p, पूर्णांक nid)
अणु
	nodemask_t nodes;
	पूर्णांक dist;

	/* Direct connections between all NUMA nodes. */
	अगर (sched_numa_topology_type == NUMA_सूचीECT)
		वापस nid;

	/*
	 * On a प्रणाली with glueless mesh NUMA topology, group_weight
	 * scores nodes according to the number of NUMA hपूर्णांकing faults on
	 * both the node itself, and on nearby nodes.
	 */
	अगर (sched_numa_topology_type == NUMA_GLUELESS_MESH) अणु
		अचिन्हित दीर्घ score, max_score = 0;
		पूर्णांक node, max_node = nid;

		dist = sched_max_numa_distance;

		क्रम_each_online_node(node) अणु
			score = group_weight(p, node, dist);
			अगर (score > max_score) अणु
				max_score = score;
				max_node = node;
			पूर्ण
		पूर्ण
		वापस max_node;
	पूर्ण

	/*
	 * Finding the preferred nid in a प्रणाली with NUMA backplane
	 * पूर्णांकerconnect topology is more involved. The goal is to locate
	 * tasks from numa_groups near each other in the प्रणाली, and
	 * untangle workloads from dअगरferent sides of the प्रणाली. This requires
	 * searching करोwn the hierarchy of node groups, recursively searching
	 * inside the highest scoring group of nodes. The nodemask tricks
	 * keep the complनिकासy of the search करोwn.
	 */
	nodes = node_online_map;
	क्रम (dist = sched_max_numa_distance; dist > LOCAL_DISTANCE; dist--) अणु
		अचिन्हित दीर्घ max_faults = 0;
		nodemask_t max_group = NODE_MASK_NONE;
		पूर्णांक a, b;

		/* Are there nodes at this distance from each other? */
		अगर (!find_numa_distance(dist))
			जारी;

		क्रम_each_node_mask(a, nodes) अणु
			अचिन्हित दीर्घ faults = 0;
			nodemask_t this_group;
			nodes_clear(this_group);

			/* Sum group's NUMA faults; includes a==b हाल. */
			क्रम_each_node_mask(b, nodes) अणु
				अगर (node_distance(a, b) < dist) अणु
					faults += group_faults(p, b);
					node_set(b, this_group);
					node_clear(b, nodes);
				पूर्ण
			पूर्ण

			/* Remember the top group. */
			अगर (faults > max_faults) अणु
				max_faults = faults;
				max_group = this_group;
				/*
				 * subtle: at the smallest distance there is
				 * just one node left in each "group", the
				 * winner is the preferred nid.
				 */
				nid = a;
			पूर्ण
		पूर्ण
		/* Next round, evaluate the nodes within max_group. */
		अगर (!max_faults)
			अवरोध;
		nodes = max_group;
	पूर्ण
	वापस nid;
पूर्ण

अटल व्योम task_numa_placement(काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक seq, nid, max_nid = NUMA_NO_NODE;
	अचिन्हित दीर्घ max_faults = 0;
	अचिन्हित दीर्घ fault_types[2] = अणु 0, 0 पूर्ण;
	अचिन्हित दीर्घ total_faults;
	u64 runसमय, period;
	spinlock_t *group_lock = शून्य;
	काष्ठा numa_group *ng;

	/*
	 * The p->mm->numa_scan_seq field माला_लो updated without
	 * exclusive access. Use READ_ONCE() here to ensure
	 * that the field is पढ़ो in a single access:
	 */
	seq = READ_ONCE(p->mm->numa_scan_seq);
	अगर (p->numa_scan_seq == seq)
		वापस;
	p->numa_scan_seq = seq;
	p->numa_scan_period_max = task_scan_max(p);

	total_faults = p->numa_faults_locality[0] +
		       p->numa_faults_locality[1];
	runसमय = numa_get_avg_runसमय(p, &period);

	/* If the task is part of a group prevent parallel updates to group stats */
	ng = deref_curr_numa_group(p);
	अगर (ng) अणु
		group_lock = &ng->lock;
		spin_lock_irq(group_lock);
	पूर्ण

	/* Find the node with the highest number of faults */
	क्रम_each_online_node(nid) अणु
		/* Keep track of the offsets in numa_faults array */
		पूर्णांक mem_idx, membuf_idx, cpu_idx, cpubuf_idx;
		अचिन्हित दीर्घ faults = 0, group_faults = 0;
		पूर्णांक priv;

		क्रम (priv = 0; priv < NR_NUMA_HINT_FAULT_TYPES; priv++) अणु
			दीर्घ dअगरf, f_dअगरf, f_weight;

			mem_idx = task_faults_idx(NUMA_MEM, nid, priv);
			membuf_idx = task_faults_idx(NUMA_MEMBUF, nid, priv);
			cpu_idx = task_faults_idx(NUMA_CPU, nid, priv);
			cpubuf_idx = task_faults_idx(NUMA_CPUBUF, nid, priv);

			/* Decay existing winकरोw, copy faults since last scan */
			dअगरf = p->numa_faults[membuf_idx] - p->numa_faults[mem_idx] / 2;
			fault_types[priv] += p->numa_faults[membuf_idx];
			p->numa_faults[membuf_idx] = 0;

			/*
			 * Normalize the faults_from, so all tasks in a group
			 * count according to CPU use, instead of by the raw
			 * number of faults. Tasks with little runसमय have
			 * little over-all impact on throughput, and thus their
			 * faults are less important.
			 */
			f_weight = भाग64_u64(runसमय << 16, period + 1);
			f_weight = (f_weight * p->numa_faults[cpubuf_idx]) /
				   (total_faults + 1);
			f_dअगरf = f_weight - p->numa_faults[cpu_idx] / 2;
			p->numa_faults[cpubuf_idx] = 0;

			p->numa_faults[mem_idx] += dअगरf;
			p->numa_faults[cpu_idx] += f_dअगरf;
			faults += p->numa_faults[mem_idx];
			p->total_numa_faults += dअगरf;
			अगर (ng) अणु
				/*
				 * safe because we can only change our own group
				 *
				 * mem_idx represents the offset क्रम a given
				 * nid and priv in a specअगरic region because it
				 * is at the beginning of the numa_faults array.
				 */
				ng->faults[mem_idx] += dअगरf;
				ng->faults_cpu[mem_idx] += f_dअगरf;
				ng->total_faults += dअगरf;
				group_faults += ng->faults[mem_idx];
			पूर्ण
		पूर्ण

		अगर (!ng) अणु
			अगर (faults > max_faults) अणु
				max_faults = faults;
				max_nid = nid;
			पूर्ण
		पूर्ण अन्यथा अगर (group_faults > max_faults) अणु
			max_faults = group_faults;
			max_nid = nid;
		पूर्ण
	पूर्ण

	अगर (ng) अणु
		numa_group_count_active_nodes(ng);
		spin_unlock_irq(group_lock);
		max_nid = preferred_group_nid(p, max_nid);
	पूर्ण

	अगर (max_faults) अणु
		/* Set the new preferred node */
		अगर (max_nid != p->numa_preferred_nid)
			sched_setnuma(p, max_nid);
	पूर्ण

	update_task_scan_period(p, fault_types[0], fault_types[1]);
पूर्ण

अटल अंतरभूत पूर्णांक get_numa_group(काष्ठा numa_group *grp)
अणु
	वापस refcount_inc_not_zero(&grp->refcount);
पूर्ण

अटल अंतरभूत व्योम put_numa_group(काष्ठा numa_group *grp)
अणु
	अगर (refcount_dec_and_test(&grp->refcount))
		kमुक्त_rcu(grp, rcu);
पूर्ण

अटल व्योम task_numa_group(काष्ठा task_काष्ठा *p, पूर्णांक cpupid, पूर्णांक flags,
			पूर्णांक *priv)
अणु
	काष्ठा numa_group *grp, *my_grp;
	काष्ठा task_काष्ठा *tsk;
	bool join = false;
	पूर्णांक cpu = cpupid_to_cpu(cpupid);
	पूर्णांक i;

	अगर (unlikely(!deref_curr_numa_group(p))) अणु
		अचिन्हित पूर्णांक size = माप(काष्ठा numa_group) +
				    4*nr_node_ids*माप(अचिन्हित दीर्घ);

		grp = kzalloc(size, GFP_KERNEL | __GFP_NOWARN);
		अगर (!grp)
			वापस;

		refcount_set(&grp->refcount, 1);
		grp->active_nodes = 1;
		grp->max_faults_cpu = 0;
		spin_lock_init(&grp->lock);
		grp->gid = p->pid;
		/* Second half of the array tracks nids where faults happen */
		grp->faults_cpu = grp->faults + NR_NUMA_HINT_FAULT_TYPES *
						nr_node_ids;

		क्रम (i = 0; i < NR_NUMA_HINT_FAULT_STATS * nr_node_ids; i++)
			grp->faults[i] = p->numa_faults[i];

		grp->total_faults = p->total_numa_faults;

		grp->nr_tasks++;
		rcu_assign_poपूर्णांकer(p->numa_group, grp);
	पूर्ण

	rcu_पढ़ो_lock();
	tsk = READ_ONCE(cpu_rq(cpu)->curr);

	अगर (!cpupid_match_pid(tsk, cpupid))
		जाओ no_join;

	grp = rcu_dereference(tsk->numa_group);
	अगर (!grp)
		जाओ no_join;

	my_grp = deref_curr_numa_group(p);
	अगर (grp == my_grp)
		जाओ no_join;

	/*
	 * Only join the other group अगर its bigger; अगर we're the bigger group,
	 * the other task will join us.
	 */
	अगर (my_grp->nr_tasks > grp->nr_tasks)
		जाओ no_join;

	/*
	 * Tie-अवरोध on the grp address.
	 */
	अगर (my_grp->nr_tasks == grp->nr_tasks && my_grp > grp)
		जाओ no_join;

	/* Always join thपढ़ोs in the same process. */
	अगर (tsk->mm == current->mm)
		join = true;

	/* Simple filter to aव्योम false positives due to PID collisions */
	अगर (flags & TNF_SHARED)
		join = true;

	/* Update priv based on whether false sharing was detected */
	*priv = !join;

	अगर (join && !get_numa_group(grp))
		जाओ no_join;

	rcu_पढ़ो_unlock();

	अगर (!join)
		वापस;

	BUG_ON(irqs_disabled());
	द्विगुन_lock_irq(&my_grp->lock, &grp->lock);

	क्रम (i = 0; i < NR_NUMA_HINT_FAULT_STATS * nr_node_ids; i++) अणु
		my_grp->faults[i] -= p->numa_faults[i];
		grp->faults[i] += p->numa_faults[i];
	पूर्ण
	my_grp->total_faults -= p->total_numa_faults;
	grp->total_faults += p->total_numa_faults;

	my_grp->nr_tasks--;
	grp->nr_tasks++;

	spin_unlock(&my_grp->lock);
	spin_unlock_irq(&grp->lock);

	rcu_assign_poपूर्णांकer(p->numa_group, grp);

	put_numa_group(my_grp);
	वापस;

no_join:
	rcu_पढ़ो_unlock();
	वापस;
पूर्ण

/*
 * Get rid of NUMA statistics associated with a task (either current or dead).
 * If @final is set, the task is dead and has reached refcount zero, so we can
 * safely मुक्त all relevant data काष्ठाures. Otherwise, there might be
 * concurrent पढ़ोs from places like load balancing and procfs, and we should
 * reset the data back to शेष state without मुक्तing ->numa_faults.
 */
व्योम task_numa_मुक्त(काष्ठा task_काष्ठा *p, bool final)
अणु
	/* safe: p either is current or is being मुक्तd by current */
	काष्ठा numa_group *grp = rcu_dereference_raw(p->numa_group);
	अचिन्हित दीर्घ *numa_faults = p->numa_faults;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (!numa_faults)
		वापस;

	अगर (grp) अणु
		spin_lock_irqsave(&grp->lock, flags);
		क्रम (i = 0; i < NR_NUMA_HINT_FAULT_STATS * nr_node_ids; i++)
			grp->faults[i] -= p->numa_faults[i];
		grp->total_faults -= p->total_numa_faults;

		grp->nr_tasks--;
		spin_unlock_irqrestore(&grp->lock, flags);
		RCU_INIT_POINTER(p->numa_group, शून्य);
		put_numa_group(grp);
	पूर्ण

	अगर (final) अणु
		p->numa_faults = शून्य;
		kमुक्त(numa_faults);
	पूर्ण अन्यथा अणु
		p->total_numa_faults = 0;
		क्रम (i = 0; i < NR_NUMA_HINT_FAULT_STATS * nr_node_ids; i++)
			numa_faults[i] = 0;
	पूर्ण
पूर्ण

/*
 * Got a PROT_NONE fault क्रम a page on @node.
 */
व्योम task_numa_fault(पूर्णांक last_cpupid, पूर्णांक mem_node, पूर्णांक pages, पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *p = current;
	bool migrated = flags & TNF_MIGRATED;
	पूर्णांक cpu_node = task_node(current);
	पूर्णांक local = !!(flags & TNF_FAULT_LOCAL);
	काष्ठा numa_group *ng;
	पूर्णांक priv;

	अगर (!अटल_branch_likely(&sched_numa_balancing))
		वापस;

	/* क्रम example, ksmd faulting in a user's mm */
	अगर (!p->mm)
		वापस;

	/* Allocate buffer to track faults on a per-node basis */
	अगर (unlikely(!p->numa_faults)) अणु
		पूर्णांक size = माप(*p->numa_faults) *
			   NR_NUMA_HINT_FAULT_BUCKETS * nr_node_ids;

		p->numa_faults = kzalloc(size, GFP_KERNEL|__GFP_NOWARN);
		अगर (!p->numa_faults)
			वापस;

		p->total_numa_faults = 0;
		स_रखो(p->numa_faults_locality, 0, माप(p->numa_faults_locality));
	पूर्ण

	/*
	 * First accesses are treated as निजी, otherwise consider accesses
	 * to be निजी अगर the accessing pid has not changed
	 */
	अगर (unlikely(last_cpupid == (-1 & LAST_CPUPID_MASK))) अणु
		priv = 1;
	पूर्ण अन्यथा अणु
		priv = cpupid_match_pid(p, last_cpupid);
		अगर (!priv && !(flags & TNF_NO_GROUP))
			task_numa_group(p, last_cpupid, flags, &priv);
	पूर्ण

	/*
	 * If a workload spans multiple NUMA nodes, a shared fault that
	 * occurs wholly within the set of nodes that the workload is
	 * actively using should be counted as local. This allows the
	 * scan rate to slow करोwn when a workload has settled करोwn.
	 */
	ng = deref_curr_numa_group(p);
	अगर (!priv && !local && ng && ng->active_nodes > 1 &&
				numa_is_active_node(cpu_node, ng) &&
				numa_is_active_node(mem_node, ng))
		local = 1;

	/*
	 * Retry to migrate task to preferred node periodically, in हाल it
	 * previously failed, or the scheduler moved us.
	 */
	अगर (समय_after(jअगरfies, p->numa_migrate_retry)) अणु
		task_numa_placement(p);
		numa_migrate_preferred(p);
	पूर्ण

	अगर (migrated)
		p->numa_pages_migrated += pages;
	अगर (flags & TNF_MIGRATE_FAIL)
		p->numa_faults_locality[2] += pages;

	p->numa_faults[task_faults_idx(NUMA_MEMBUF, mem_node, priv)] += pages;
	p->numa_faults[task_faults_idx(NUMA_CPUBUF, cpu_node, priv)] += pages;
	p->numa_faults_locality[local] += pages;
पूर्ण

अटल व्योम reset_ptक्रमागतa_scan(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * We only did a पढ़ो acquisition of the mmap sem, so
	 * p->mm->numa_scan_seq is written to without exclusive access
	 * and the update is not guaranteed to be atomic. That's not
	 * much of an issue though, since this is just used क्रम
	 * statistical sampling. Use READ_ONCE/WRITE_ONCE, which are not
	 * expensive, to aव्योम any क्रमm of compiler optimizations:
	 */
	WRITE_ONCE(p->mm->numa_scan_seq, READ_ONCE(p->mm->numa_scan_seq) + 1);
	p->mm->numa_scan_offset = 0;
पूर्ण

/*
 * The expensive part of numa migration is करोne from task_work context.
 * Triggered from task_tick_numa().
 */
अटल व्योम task_numa_work(काष्ठा callback_head *work)
अणु
	अचिन्हित दीर्घ migrate, next_scan, now = jअगरfies;
	काष्ठा task_काष्ठा *p = current;
	काष्ठा mm_काष्ठा *mm = p->mm;
	u64 runसमय = p->se.sum_exec_runसमय;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ nr_pte_updates = 0;
	दीर्घ pages, virtpages;

	SCHED_WARN_ON(p != container_of(work, काष्ठा task_काष्ठा, numa_work));

	work->next = work;
	/*
	 * Who cares about NUMA placement when they're dying.
	 *
	 * NOTE: make sure not to dereference p->mm beक्रमe this check,
	 * निकास_task_work() happens _after_ निकास_mm() so we could be called
	 * without p->mm even though we still had it when we enqueued this
	 * work.
	 */
	अगर (p->flags & PF_EXITING)
		वापस;

	अगर (!mm->numa_next_scan) अणु
		mm->numa_next_scan = now +
			msecs_to_jअगरfies(sysctl_numa_balancing_scan_delay);
	पूर्ण

	/*
	 * Enक्रमce maximal scan/migration frequency..
	 */
	migrate = mm->numa_next_scan;
	अगर (समय_beक्रमe(now, migrate))
		वापस;

	अगर (p->numa_scan_period == 0) अणु
		p->numa_scan_period_max = task_scan_max(p);
		p->numa_scan_period = task_scan_start(p);
	पूर्ण

	next_scan = now + msecs_to_jअगरfies(p->numa_scan_period);
	अगर (cmpxchg(&mm->numa_next_scan, migrate, next_scan) != migrate)
		वापस;

	/*
	 * Delay this task enough that another task of this mm will likely win
	 * the next समय around.
	 */
	p->node_stamp += 2 * TICK_NSEC;

	start = mm->numa_scan_offset;
	pages = sysctl_numa_balancing_scan_size;
	pages <<= 20 - PAGE_SHIFT; /* MB in pages */
	virtpages = pages * 8;	   /* Scan up to this much भव space */
	अगर (!pages)
		वापस;


	अगर (!mmap_पढ़ो_trylock(mm))
		वापस;
	vma = find_vma(mm, start);
	अगर (!vma) अणु
		reset_ptक्रमागतa_scan(p);
		start = 0;
		vma = mm->mmap;
	पूर्ण
	क्रम (; vma; vma = vma->vm_next) अणु
		अगर (!vma_migratable(vma) || !vma_policy_mof(vma) ||
			is_vm_hugetlb_page(vma) || (vma->vm_flags & VM_MIXEDMAP)) अणु
			जारी;
		पूर्ण

		/*
		 * Shared library pages mapped by multiple processes are not
		 * migrated as it is expected they are cache replicated. Aव्योम
		 * hपूर्णांकing faults in पढ़ो-only file-backed mappings or the vdso
		 * as migrating the pages will be of marginal benefit.
		 */
		अगर (!vma->vm_mm ||
		    (vma->vm_file && (vma->vm_flags & (VM_READ|VM_WRITE)) == (VM_READ)))
			जारी;

		/*
		 * Skip inaccessible VMAs to aव्योम any confusion between
		 * PROT_NONE and NUMA hपूर्णांकing ptes
		 */
		अगर (!vma_is_accessible(vma))
			जारी;

		करो अणु
			start = max(start, vma->vm_start);
			end = ALIGN(start + (pages << PAGE_SHIFT), HPAGE_SIZE);
			end = min(end, vma->vm_end);
			nr_pte_updates = change_prot_numa(vma, start, end);

			/*
			 * Try to scan sysctl_numa_balancing_size worth of
			 * hpages that have at least one present PTE that
			 * is not alपढ़ोy pte-numa. If the VMA contains
			 * areas that are unused or alपढ़ोy full of prot_numa
			 * PTEs, scan up to virtpages, to skip through those
			 * areas faster.
			 */
			अगर (nr_pte_updates)
				pages -= (end - start) >> PAGE_SHIFT;
			virtpages -= (end - start) >> PAGE_SHIFT;

			start = end;
			अगर (pages <= 0 || virtpages <= 0)
				जाओ out;

			cond_resched();
		पूर्ण जबतक (end != vma->vm_end);
	पूर्ण

out:
	/*
	 * It is possible to reach the end of the VMA list but the last few
	 * VMAs are not guaranteed to the vma_migratable. If they are not, we
	 * would find the !migratable VMA on the next scan but not reset the
	 * scanner to the start so check it now.
	 */
	अगर (vma)
		mm->numa_scan_offset = start;
	अन्यथा
		reset_ptक्रमागतa_scan(p);
	mmap_पढ़ो_unlock(mm);

	/*
	 * Make sure tasks use at least 32x as much समय to run other code
	 * than they used here, to limit NUMA PTE scanning overhead to 3% max.
	 * Usually update_task_scan_period slows करोwn scanning enough; on an
	 * overloaded प्रणाली we need to limit overhead on a per task basis.
	 */
	अगर (unlikely(p->se.sum_exec_runसमय != runसमय)) अणु
		u64 dअगरf = p->se.sum_exec_runसमय - runसमय;
		p->node_stamp += 32 * dअगरf;
	पूर्ण
पूर्ण

व्योम init_numa_balancing(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक mm_users = 0;
	काष्ठा mm_काष्ठा *mm = p->mm;

	अगर (mm) अणु
		mm_users = atomic_पढ़ो(&mm->mm_users);
		अगर (mm_users == 1) अणु
			mm->numa_next_scan = jअगरfies + msecs_to_jअगरfies(sysctl_numa_balancing_scan_delay);
			mm->numa_scan_seq = 0;
		पूर्ण
	पूर्ण
	p->node_stamp			= 0;
	p->numa_scan_seq		= mm ? mm->numa_scan_seq : 0;
	p->numa_scan_period		= sysctl_numa_balancing_scan_delay;
	/* Protect against द्विगुन add, see task_tick_numa and task_numa_work */
	p->numa_work.next		= &p->numa_work;
	p->numa_faults			= शून्य;
	RCU_INIT_POINTER(p->numa_group, शून्य);
	p->last_task_numa_placement	= 0;
	p->last_sum_exec_runसमय	= 0;

	init_task_work(&p->numa_work, task_numa_work);

	/* New address space, reset the preferred nid */
	अगर (!(clone_flags & CLONE_VM)) अणु
		p->numa_preferred_nid = NUMA_NO_NODE;
		वापस;
	पूर्ण

	/*
	 * New thपढ़ो, keep existing numa_preferred_nid which should be copied
	 * alपढ़ोy by arch_dup_task_काष्ठा but stagger when scans start.
	 */
	अगर (mm) अणु
		अचिन्हित पूर्णांक delay;

		delay = min_t(अचिन्हित पूर्णांक, task_scan_max(current),
			current->numa_scan_period * mm_users * NSEC_PER_MSEC);
		delay += 2 * TICK_NSEC;
		p->node_stamp = delay;
	पूर्ण
पूर्ण

/*
 * Drive the periodic memory faults..
 */
अटल व्योम task_tick_numa(काष्ठा rq *rq, काष्ठा task_काष्ठा *curr)
अणु
	काष्ठा callback_head *work = &curr->numa_work;
	u64 period, now;

	/*
	 * We करोn't care about NUMA placement if we don't have memory.
	 */
	अगर ((curr->flags & (PF_EXITING | PF_KTHREAD)) || work->next != work)
		वापस;

	/*
	 * Using runसमय rather than wallसमय has the dual advantage that
	 * we (mostly) drive the selection from busy thपढ़ोs and that the
	 * task needs to have करोne some actual work beक्रमe we bother with
	 * NUMA placement.
	 */
	now = curr->se.sum_exec_runसमय;
	period = (u64)curr->numa_scan_period * NSEC_PER_MSEC;

	अगर (now > curr->node_stamp + period) अणु
		अगर (!curr->node_stamp)
			curr->numa_scan_period = task_scan_start(curr);
		curr->node_stamp += period;

		अगर (!समय_beक्रमe(jअगरfies, curr->mm->numa_next_scan))
			task_work_add(curr, work, TWA_RESUME);
	पूर्ण
पूर्ण

अटल व्योम update_scan_period(काष्ठा task_काष्ठा *p, पूर्णांक new_cpu)
अणु
	पूर्णांक src_nid = cpu_to_node(task_cpu(p));
	पूर्णांक dst_nid = cpu_to_node(new_cpu);

	अगर (!अटल_branch_likely(&sched_numa_balancing))
		वापस;

	अगर (!p->mm || !p->numa_faults || (p->flags & PF_EXITING))
		वापस;

	अगर (src_nid == dst_nid)
		वापस;

	/*
	 * Allow resets अगर faults have been trapped beक्रमe one scan
	 * has completed. This is most likely due to a new task that
	 * is pulled cross-node due to wakeups or load balancing.
	 */
	अगर (p->numa_scan_seq) अणु
		/*
		 * Aव्योम scan adjusपंचांगents अगर moving to the preferred
		 * node or अगर the task was not previously running on
		 * the preferred node.
		 */
		अगर (dst_nid == p->numa_preferred_nid ||
		    (p->numa_preferred_nid != NUMA_NO_NODE &&
			src_nid != p->numa_preferred_nid))
			वापस;
	पूर्ण

	p->numa_scan_period = task_scan_start(p);
पूर्ण

#अन्यथा
अटल व्योम task_tick_numa(काष्ठा rq *rq, काष्ठा task_काष्ठा *curr)
अणु
पूर्ण

अटल अंतरभूत व्योम account_numa_enqueue(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत व्योम account_numa_dequeue(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत व्योम update_scan_period(काष्ठा task_काष्ठा *p, पूर्णांक new_cpu)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

अटल व्योम
account_entity_enqueue(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	update_load_add(&cfs_rq->load, se->load.weight);
#अगर_घोषित CONFIG_SMP
	अगर (entity_is_task(se)) अणु
		काष्ठा rq *rq = rq_of(cfs_rq);

		account_numa_enqueue(rq, task_of(se));
		list_add(&se->group_node, &rq->cfs_tasks);
	पूर्ण
#पूर्ण_अगर
	cfs_rq->nr_running++;
पूर्ण

अटल व्योम
account_entity_dequeue(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	update_load_sub(&cfs_rq->load, se->load.weight);
#अगर_घोषित CONFIG_SMP
	अगर (entity_is_task(se)) अणु
		account_numa_dequeue(rq_of(cfs_rq), task_of(se));
		list_del_init(&se->group_node);
	पूर्ण
#पूर्ण_अगर
	cfs_rq->nr_running--;
पूर्ण

/*
 * Signed add and clamp on underflow.
 *
 * Explicitly करो a load-store to ensure the पूर्णांकermediate value never hits
 * memory. This allows lockless observations without ever seeing the negative
 * values.
 */
#घोषणा add_positive(_ptr, _val) करो अणु                           \
	typeof(_ptr) ptr = (_ptr);                              \
	typeof(_val) val = (_val);                              \
	typeof(*ptr) res, var = READ_ONCE(*ptr);                \
								\
	res = var + val;                                        \
								\
	अगर (val < 0 && res > var)                               \
		res = 0;                                        \
								\
	WRITE_ONCE(*ptr, res);                                  \
पूर्ण जबतक (0)

/*
 * Unचिन्हित subtract and clamp on underflow.
 *
 * Explicitly करो a load-store to ensure the पूर्णांकermediate value never hits
 * memory. This allows lockless observations without ever seeing the negative
 * values.
 */
#घोषणा sub_positive(_ptr, _val) करो अणु				\
	typeof(_ptr) ptr = (_ptr);				\
	typeof(*ptr) val = (_val);				\
	typeof(*ptr) res, var = READ_ONCE(*ptr);		\
	res = var - val;					\
	अगर (res > var)						\
		res = 0;					\
	WRITE_ONCE(*ptr, res);					\
पूर्ण जबतक (0)

/*
 * Remove and clamp on negative, from a local variable.
 *
 * A variant of sub_positive(), which करोes not use explicit load-store
 * and is thus optimized क्रम local variable updates.
 */
#घोषणा lsub_positive(_ptr, _val) करो अणु				\
	typeof(_ptr) ptr = (_ptr);				\
	*ptr -= min_t(typeof(*ptr), *ptr, _val);		\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत व्योम
enqueue_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	cfs_rq->avg.load_avg += se->avg.load_avg;
	cfs_rq->avg.load_sum += se_weight(se) * se->avg.load_sum;
पूर्ण

अटल अंतरभूत व्योम
dequeue_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	sub_positive(&cfs_rq->avg.load_avg, se->avg.load_avg);
	sub_positive(&cfs_rq->avg.load_sum, se_weight(se) * se->avg.load_sum);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
enqueue_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se) अणु पूर्ण
अटल अंतरभूत व्योम
dequeue_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम reweight_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se,
			    अचिन्हित दीर्घ weight)
अणु
	अगर (se->on_rq) अणु
		/* commit outstanding execution समय */
		अगर (cfs_rq->curr == se)
			update_curr(cfs_rq);
		update_load_sub(&cfs_rq->load, se->load.weight);
	पूर्ण
	dequeue_load_avg(cfs_rq, se);

	update_load_set(&se->load, weight);

#अगर_घोषित CONFIG_SMP
	करो अणु
		u32 भागider = get_pelt_भागider(&se->avg);

		se->avg.load_avg = भाग_u64(se_weight(se) * se->avg.load_sum, भागider);
	पूर्ण जबतक (0);
#पूर्ण_अगर

	enqueue_load_avg(cfs_rq, se);
	अगर (se->on_rq)
		update_load_add(&cfs_rq->load, se->load.weight);

पूर्ण

व्योम reweight_task(काष्ठा task_काष्ठा *p, पूर्णांक prio)
अणु
	काष्ठा sched_entity *se = &p->se;
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
	काष्ठा load_weight *load = &se->load;
	अचिन्हित दीर्घ weight = scale_load(sched_prio_to_weight[prio]);

	reweight_entity(cfs_rq, se, weight);
	load->inv_weight = sched_prio_to_wmult[prio];
पूर्ण

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
#अगर_घोषित CONFIG_SMP
/*
 * All this करोes is approximate the hierarchical proportion which includes that
 * global sum we all love to hate.
 *
 * That is, the weight of a group entity, is the proportional share of the
 * group weight based on the group runqueue weights. That is:
 *
 *                     tg->weight * grq->load.weight
 *   ge->load.weight = -----------------------------               (1)
 *			  \Sum grq->load.weight
 *
 * Now, because computing that sum is prohibitively expensive to compute (been
 * there, करोne that) we approximate it with this average stuff. The average
 * moves slower and thereक्रमe the approximation is cheaper and more stable.
 *
 * So instead of the above, we substitute:
 *
 *   grq->load.weight -> grq->avg.load_avg                         (2)
 *
 * which yields the following:
 *
 *                     tg->weight * grq->avg.load_avg
 *   ge->load.weight = ------------------------------              (3)
 *				tg->load_avg
 *
 * Where: tg->load_avg ~= \Sum grq->avg.load_avg
 *
 * That is shares_avg, and it is right (given the approximation (2)).
 *
 * The problem with it is that because the average is slow -- it was deचिन्हित
 * to be exactly that of course -- this leads to transients in boundary
 * conditions. In specअगरic, the हाल where the group was idle and we start the
 * one task. It takes समय क्रम our CPU's grq->avg.load_avg to build up,
 * yielding bad latency etc..
 *
 * Now, in that special हाल (1) reduces to:
 *
 *                     tg->weight * grq->load.weight
 *   ge->load.weight = ----------------------------- = tg->weight   (4)
 *			    grp->load.weight
 *
 * That is, the sum collapses because all other CPUs are idle; the UP scenario.
 *
 * So what we करो is modअगरy our approximation (3) to approach (4) in the (near)
 * UP हाल, like:
 *
 *   ge->load.weight =
 *
 *              tg->weight * grq->load.weight
 *     ---------------------------------------------------         (5)
 *     tg->load_avg - grq->avg.load_avg + grq->load.weight
 *
 * But because grq->load.weight can drop to 0, resulting in a भागide by zero,
 * we need to use grq->avg.load_avg as its lower bound, which then gives:
 *
 *
 *                     tg->weight * grq->load.weight
 *   ge->load.weight = -----------------------------		   (6)
 *				tg_load_avg'
 *
 * Where:
 *
 *   tg_load_avg' = tg->load_avg - grq->avg.load_avg +
 *                  max(grq->load.weight, grq->avg.load_avg)
 *
 * And that is shares_weight and is icky. In the (near) UP हाल it approaches
 * (4) जबतक in the normal हाल it approaches (3). It consistently
 * overestimates the ge->load.weight and thereक्रमe:
 *
 *   \Sum ge->load.weight >= tg->weight
 *
 * hence icky!
 */
अटल दीर्घ calc_group_shares(काष्ठा cfs_rq *cfs_rq)
अणु
	दीर्घ tg_weight, tg_shares, load, shares;
	काष्ठा task_group *tg = cfs_rq->tg;

	tg_shares = READ_ONCE(tg->shares);

	load = max(scale_load_करोwn(cfs_rq->load.weight), cfs_rq->avg.load_avg);

	tg_weight = atomic_दीर्घ_पढ़ो(&tg->load_avg);

	/* Ensure tg_weight >= load */
	tg_weight -= cfs_rq->tg_load_avg_contrib;
	tg_weight += load;

	shares = (tg_shares * load);
	अगर (tg_weight)
		shares /= tg_weight;

	/*
	 * MIN_SHARES has to be unscaled here to support per-CPU partitioning
	 * of a group with small tg->shares value. It is a न्यूनमान value which is
	 * asचिन्हित as a minimum load.weight to the sched_entity representing
	 * the group on a CPU.
	 *
	 * E.g. on 64-bit क्रम a group with tg->shares of scale_load(15)=15*1024
	 * on an 8-core प्रणाली with 8 tasks each runnable on one CPU shares has
	 * to be 15*1024*1/8=1920 instead of scale_load(MIN_SHARES)=2*1024. In
	 * हाल no task is runnable on a CPU MIN_SHARES=2 should be वापसed
	 * instead of 0.
	 */
	वापस clamp_t(दीर्घ, shares, MIN_SHARES, tg_shares);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल अंतरभूत पूर्णांक throttled_hierarchy(काष्ठा cfs_rq *cfs_rq);

/*
 * Recomputes the group entity based on the current state of its group
 * runqueue.
 */
अटल व्योम update_cfs_group(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *gcfs_rq = group_cfs_rq(se);
	दीर्घ shares;

	अगर (!gcfs_rq)
		वापस;

	अगर (throttled_hierarchy(gcfs_rq))
		वापस;

#अगर_अघोषित CONFIG_SMP
	shares = READ_ONCE(gcfs_rq->tg->shares);

	अगर (likely(se->load.weight == shares))
		वापस;
#अन्यथा
	shares   = calc_group_shares(gcfs_rq);
#पूर्ण_अगर

	reweight_entity(cfs_rq_of(se), se, shares);
पूर्ण

#अन्यथा /* CONFIG_FAIR_GROUP_SCHED */
अटल अंतरभूत व्योम update_cfs_group(काष्ठा sched_entity *se)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */

अटल अंतरभूत व्योम cfs_rq_util_change(काष्ठा cfs_rq *cfs_rq, पूर्णांक flags)
अणु
	काष्ठा rq *rq = rq_of(cfs_rq);

	अगर (&rq->cfs == cfs_rq) अणु
		/*
		 * There are a few boundary हालs this might miss but it should
		 * get called often enough that that should (hopefully) not be
		 * a real problem.
		 *
		 * It will not get called when we go idle, because the idle
		 * thपढ़ो is a dअगरferent class (!fair), nor will the utilization
		 * number include things like RT tasks.
		 *
		 * As is, the util number is not freq-invariant (we'd have to
		 * implement arch_scale_freq_capacity() क्रम that).
		 *
		 * See cpu_util().
		 */
		cpufreq_update_util(rq, flags);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
#अगर_घोषित CONFIG_FAIR_GROUP_SCHED

अटल अंतरभूत bool cfs_rq_is_decayed(काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (cfs_rq->load.weight)
		वापस false;

	अगर (cfs_rq->avg.load_sum)
		वापस false;

	अगर (cfs_rq->avg.util_sum)
		वापस false;

	अगर (cfs_rq->avg.runnable_sum)
		वापस false;

	वापस true;
पूर्ण

/**
 * update_tg_load_avg - update the tg's load avg
 * @cfs_rq: the cfs_rq whose avg changed
 *
 * This function 'ensures': tg->load_avg := \Sum tg->cfs_rq[]->avg.load.
 * However, because tg->load_avg is a global value there are perक्रमmance
 * considerations.
 *
 * In order to aव्योम having to look at the other cfs_rq's, we use a
 * dअगरferential update where we store the last value we propagated. This in
 * turn allows skipping updates अगर the dअगरferential is 'small'.
 *
 * Updating tg's load_avg is necessary beक्रमe update_cfs_share().
 */
अटल अंतरभूत व्योम update_tg_load_avg(काष्ठा cfs_rq *cfs_rq)
अणु
	दीर्घ delta = cfs_rq->avg.load_avg - cfs_rq->tg_load_avg_contrib;

	/*
	 * No need to update load_avg क्रम root_task_group as it is not used.
	 */
	अगर (cfs_rq->tg == &root_task_group)
		वापस;

	अगर (असल(delta) > cfs_rq->tg_load_avg_contrib / 64) अणु
		atomic_दीर्घ_add(delta, &cfs_rq->tg->load_avg);
		cfs_rq->tg_load_avg_contrib = cfs_rq->avg.load_avg;
	पूर्ण
पूर्ण

/*
 * Called within set_task_rq() right beक्रमe setting a task's CPU. The
 * caller only guarantees p->pi_lock is held; no other assumptions,
 * including the state of rq->lock, should be made.
 */
व्योम set_task_rq_fair(काष्ठा sched_entity *se,
		      काष्ठा cfs_rq *prev, काष्ठा cfs_rq *next)
अणु
	u64 p_last_update_समय;
	u64 n_last_update_समय;

	अगर (!sched_feat(ATTACH_AGE_LOAD))
		वापस;

	/*
	 * We are supposed to update the task to "current" समय, then its up to
	 * date and पढ़ोy to go to new CPU/cfs_rq. But we have dअगरficulty in
	 * getting what current समय is, so simply throw away the out-of-date
	 * समय. This will result in the wakee task is less decayed, but giving
	 * the wakee more load sounds not bad.
	 */
	अगर (!(se->avg.last_update_समय && prev))
		वापस;

#अगर_अघोषित CONFIG_64BIT
	अणु
		u64 p_last_update_समय_copy;
		u64 n_last_update_समय_copy;

		करो अणु
			p_last_update_समय_copy = prev->load_last_update_समय_copy;
			n_last_update_समय_copy = next->load_last_update_समय_copy;

			smp_rmb();

			p_last_update_समय = prev->avg.last_update_समय;
			n_last_update_समय = next->avg.last_update_समय;

		पूर्ण जबतक (p_last_update_समय != p_last_update_समय_copy ||
			 n_last_update_समय != n_last_update_समय_copy);
	पूर्ण
#अन्यथा
	p_last_update_समय = prev->avg.last_update_समय;
	n_last_update_समय = next->avg.last_update_समय;
#पूर्ण_अगर
	__update_load_avg_blocked_se(p_last_update_समय, se);
	se->avg.last_update_समय = n_last_update_समय;
पूर्ण


/*
 * When on migration a sched_entity joins/leaves the PELT hierarchy, we need to
 * propagate its contribution. The key to this propagation is the invariant
 * that क्रम each group:
 *
 *   ge->avg == grq->avg						(1)
 *
 * _IFF_ we look at the pure running and runnable sums. Because they
 * represent the very same entity, just at dअगरferent poपूर्णांकs in the hierarchy.
 *
 * Per the above update_tg_cfs_util() and update_tg_cfs_runnable() are trivial
 * and simply copies the running/runnable sum over (but still wrong, because
 * the group entity and group rq करो not have their PELT winकरोws aligned).
 *
 * However, update_tg_cfs_load() is more complex. So we have:
 *
 *   ge->avg.load_avg = ge->load.weight * ge->avg.runnable_avg		(2)
 *
 * And since, like util, the runnable part should be directly transferable,
 * the following would _appear_ to be the straight क्रमward approach:
 *
 *   grq->avg.load_avg = grq->load.weight * grq->avg.runnable_avg	(3)
 *
 * And per (1) we have:
 *
 *   ge->avg.runnable_avg == grq->avg.runnable_avg
 *
 * Which gives:
 *
 *                      ge->load.weight * grq->avg.load_avg
 *   ge->avg.load_avg = -----------------------------------		(4)
 *                               grq->load.weight
 *
 * Except that is wrong!
 *
 * Because जबतक क्रम entities historical weight is not important and we
 * really only care about our future and thereक्रमe can consider a pure
 * runnable sum, runqueues can NOT करो this.
 *
 * We specअगरically want runqueues to have a load_avg that includes
 * historical weights. Those represent the blocked load, the load we expect
 * to (लघुly) वापस to us. This only works by keeping the weights as
 * पूर्णांकegral part of the sum. We thereक्रमe cannot decompose as per (3).
 *
 * Another reason this करोesn't work is that runnable isn't a 0-sum entity.
 * Imagine a rq with 2 tasks that each are runnable 2/3 of the समय. Then the
 * rq itself is runnable anywhere between 2/3 and 1 depending on how the
 * runnable section of these tasks overlap (or not). If they were to perfectly
 * align the rq as a whole would be runnable 2/3 of the समय. If however we
 * always have at least 1 runnable task, the rq as a whole is always runnable.
 *
 * So we'll have to approximate.. :/
 *
 * Given the स्थिरraपूर्णांक:
 *
 *   ge->avg.running_sum <= ge->avg.runnable_sum <= LOAD_AVG_MAX
 *
 * We can स्थिरruct a rule that adds runnable to a rq by assuming minimal
 * overlap.
 *
 * On removal, we'll assume each task is equally runnable; which yields:
 *
 *   grq->avg.runnable_sum = grq->avg.load_sum / grq->load.weight
 *
 * XXX: only करो this क्रम the part of runnable > running ?
 *
 */

अटल अंतरभूत व्योम
update_tg_cfs_util(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, काष्ठा cfs_rq *gcfs_rq)
अणु
	दीर्घ delta = gcfs_rq->avg.util_avg - se->avg.util_avg;
	u32 भागider;

	/* Nothing to update */
	अगर (!delta)
		वापस;

	/*
	 * cfs_rq->avg.period_contrib can be used क्रम both cfs_rq and se.
	 * See ___update_load_avg() क्रम details.
	 */
	भागider = get_pelt_भागider(&cfs_rq->avg);

	/* Set new sched_entity's utilization */
	se->avg.util_avg = gcfs_rq->avg.util_avg;
	se->avg.util_sum = se->avg.util_avg * भागider;

	/* Update parent cfs_rq utilization */
	add_positive(&cfs_rq->avg.util_avg, delta);
	cfs_rq->avg.util_sum = cfs_rq->avg.util_avg * भागider;
पूर्ण

अटल अंतरभूत व्योम
update_tg_cfs_runnable(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, काष्ठा cfs_rq *gcfs_rq)
अणु
	दीर्घ delta = gcfs_rq->avg.runnable_avg - se->avg.runnable_avg;
	u32 भागider;

	/* Nothing to update */
	अगर (!delta)
		वापस;

	/*
	 * cfs_rq->avg.period_contrib can be used क्रम both cfs_rq and se.
	 * See ___update_load_avg() क्रम details.
	 */
	भागider = get_pelt_भागider(&cfs_rq->avg);

	/* Set new sched_entity's runnable */
	se->avg.runnable_avg = gcfs_rq->avg.runnable_avg;
	se->avg.runnable_sum = se->avg.runnable_avg * भागider;

	/* Update parent cfs_rq runnable */
	add_positive(&cfs_rq->avg.runnable_avg, delta);
	cfs_rq->avg.runnable_sum = cfs_rq->avg.runnable_avg * भागider;
पूर्ण

अटल अंतरभूत व्योम
update_tg_cfs_load(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, काष्ठा cfs_rq *gcfs_rq)
अणु
	दीर्घ delta, running_sum, runnable_sum = gcfs_rq->prop_runnable_sum;
	अचिन्हित दीर्घ load_avg;
	u64 load_sum = 0;
	u32 भागider;

	अगर (!runnable_sum)
		वापस;

	gcfs_rq->prop_runnable_sum = 0;

	/*
	 * cfs_rq->avg.period_contrib can be used क्रम both cfs_rq and se.
	 * See ___update_load_avg() क्रम details.
	 */
	भागider = get_pelt_भागider(&cfs_rq->avg);

	अगर (runnable_sum >= 0) अणु
		/*
		 * Add runnable; clip at LOAD_AVG_MAX. Reflects that until
		 * the CPU is saturated running == runnable.
		 */
		runnable_sum += se->avg.load_sum;
		runnable_sum = min_t(दीर्घ, runnable_sum, भागider);
	पूर्ण अन्यथा अणु
		/*
		 * Estimate the new unweighted runnable_sum of the gcfs_rq by
		 * assuming all tasks are equally runnable.
		 */
		अगर (scale_load_करोwn(gcfs_rq->load.weight)) अणु
			load_sum = भाग_s64(gcfs_rq->avg.load_sum,
				scale_load_करोwn(gcfs_rq->load.weight));
		पूर्ण

		/* But make sure to not inflate se's runnable */
		runnable_sum = min(se->avg.load_sum, load_sum);
	पूर्ण

	/*
	 * runnable_sum can't be lower than running_sum
	 * Rescale running sum to be in the same range as runnable sum
	 * running_sum is in [0 : LOAD_AVG_MAX <<  SCHED_CAPACITY_SHIFT]
	 * runnable_sum is in [0 : LOAD_AVG_MAX]
	 */
	running_sum = se->avg.util_sum >> SCHED_CAPACITY_SHIFT;
	runnable_sum = max(runnable_sum, running_sum);

	load_sum = (s64)se_weight(se) * runnable_sum;
	load_avg = भाग_s64(load_sum, भागider);

	delta = load_avg - se->avg.load_avg;

	se->avg.load_sum = runnable_sum;
	se->avg.load_avg = load_avg;

	add_positive(&cfs_rq->avg.load_avg, delta);
	cfs_rq->avg.load_sum = cfs_rq->avg.load_avg * भागider;
पूर्ण

अटल अंतरभूत व्योम add_tg_cfs_propagate(काष्ठा cfs_rq *cfs_rq, दीर्घ runnable_sum)
अणु
	cfs_rq->propagate = 1;
	cfs_rq->prop_runnable_sum += runnable_sum;
पूर्ण

/* Update task and its cfs_rq load average */
अटल अंतरभूत पूर्णांक propagate_entity_load_avg(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *cfs_rq, *gcfs_rq;

	अगर (entity_is_task(se))
		वापस 0;

	gcfs_rq = group_cfs_rq(se);
	अगर (!gcfs_rq->propagate)
		वापस 0;

	gcfs_rq->propagate = 0;

	cfs_rq = cfs_rq_of(se);

	add_tg_cfs_propagate(cfs_rq, gcfs_rq->prop_runnable_sum);

	update_tg_cfs_util(cfs_rq, se, gcfs_rq);
	update_tg_cfs_runnable(cfs_rq, se, gcfs_rq);
	update_tg_cfs_load(cfs_rq, se, gcfs_rq);

	trace_pelt_cfs_tp(cfs_rq);
	trace_pelt_se_tp(se);

	वापस 1;
पूर्ण

/*
 * Check अगर we need to update the load and the utilization of a blocked
 * group_entity:
 */
अटल अंतरभूत bool skip_blocked_update(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *gcfs_rq = group_cfs_rq(se);

	/*
	 * If sched_entity still have not zero load or utilization, we have to
	 * decay it:
	 */
	अगर (se->avg.load_avg || se->avg.util_avg)
		वापस false;

	/*
	 * If there is a pending propagation, we have to update the load and
	 * the utilization of the sched_entity:
	 */
	अगर (gcfs_rq->propagate)
		वापस false;

	/*
	 * Otherwise, the load and the utilization of the sched_entity is
	 * alपढ़ोy zero and there is no pending propagation, so it will be a
	 * waste of समय to try to decay it:
	 */
	वापस true;
पूर्ण

#अन्यथा /* CONFIG_FAIR_GROUP_SCHED */

अटल अंतरभूत व्योम update_tg_load_avg(काष्ठा cfs_rq *cfs_rq) अणुपूर्ण

अटल अंतरभूत पूर्णांक propagate_entity_load_avg(काष्ठा sched_entity *se)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम add_tg_cfs_propagate(काष्ठा cfs_rq *cfs_rq, दीर्घ runnable_sum) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */

/**
 * update_cfs_rq_load_avg - update the cfs_rq's load/util averages
 * @now: current समय, as per cfs_rq_घड़ी_pelt()
 * @cfs_rq: cfs_rq to update
 *
 * The cfs_rq avg is the direct sum of all its entities (blocked and runnable)
 * avg. The immediate corollary is that all (fair) tasks must be attached, see
 * post_init_entity_util_avg().
 *
 * cfs_rq->avg is used क्रम task_h_load() and update_cfs_share() क्रम example.
 *
 * Returns true अगर the load decayed or we हटाओd load.
 *
 * Since both these conditions indicate a changed cfs_rq->avg.load we should
 * call update_tg_load_avg() when this function वापसs true.
 */
अटल अंतरभूत पूर्णांक
update_cfs_rq_load_avg(u64 now, काष्ठा cfs_rq *cfs_rq)
अणु
	अचिन्हित दीर्घ हटाओd_load = 0, हटाओd_util = 0, हटाओd_runnable = 0;
	काष्ठा sched_avg *sa = &cfs_rq->avg;
	पूर्णांक decayed = 0;

	अगर (cfs_rq->हटाओd.nr) अणु
		अचिन्हित दीर्घ r;
		u32 भागider = get_pelt_भागider(&cfs_rq->avg);

		raw_spin_lock(&cfs_rq->हटाओd.lock);
		swap(cfs_rq->हटाओd.util_avg, हटाओd_util);
		swap(cfs_rq->हटाओd.load_avg, हटाओd_load);
		swap(cfs_rq->हटाओd.runnable_avg, हटाओd_runnable);
		cfs_rq->हटाओd.nr = 0;
		raw_spin_unlock(&cfs_rq->हटाओd.lock);

		r = हटाओd_load;
		sub_positive(&sa->load_avg, r);
		sub_positive(&sa->load_sum, r * भागider);

		r = हटाओd_util;
		sub_positive(&sa->util_avg, r);
		sub_positive(&sa->util_sum, r * भागider);

		r = हटाओd_runnable;
		sub_positive(&sa->runnable_avg, r);
		sub_positive(&sa->runnable_sum, r * भागider);

		/*
		 * हटाओd_runnable is the unweighted version of हटाओd_load so we
		 * can use it to estimate हटाओd_load_sum.
		 */
		add_tg_cfs_propagate(cfs_rq,
			-(दीर्घ)(हटाओd_runnable * भागider) >> SCHED_CAPACITY_SHIFT);

		decayed = 1;
	पूर्ण

	decayed |= __update_load_avg_cfs_rq(now, cfs_rq);

#अगर_अघोषित CONFIG_64BIT
	smp_wmb();
	cfs_rq->load_last_update_समय_copy = sa->last_update_समय;
#पूर्ण_अगर

	वापस decayed;
पूर्ण

/**
 * attach_entity_load_avg - attach this entity to its cfs_rq load avg
 * @cfs_rq: cfs_rq to attach to
 * @se: sched_entity to attach
 *
 * Must call update_cfs_rq_load_avg() beक्रमe this, since we rely on
 * cfs_rq->avg.last_update_समय being current.
 */
अटल व्योम attach_entity_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	/*
	 * cfs_rq->avg.period_contrib can be used क्रम both cfs_rq and se.
	 * See ___update_load_avg() क्रम details.
	 */
	u32 भागider = get_pelt_भागider(&cfs_rq->avg);

	/*
	 * When we attach the @se to the @cfs_rq, we must align the decay
	 * winकरोw because without that, really weird and wonderful things can
	 * happen.
	 *
	 * XXX illustrate
	 */
	se->avg.last_update_समय = cfs_rq->avg.last_update_समय;
	se->avg.period_contrib = cfs_rq->avg.period_contrib;

	/*
	 * Hell(o) Nasty stuff.. we need to recompute _sum based on the new
	 * period_contrib. This isn't strictly correct, but since we're
	 * entirely outside of the PELT hierarchy, nobody cares अगर we truncate
	 * _sum a little.
	 */
	se->avg.util_sum = se->avg.util_avg * भागider;

	se->avg.runnable_sum = se->avg.runnable_avg * भागider;

	se->avg.load_sum = भागider;
	अगर (se_weight(se)) अणु
		se->avg.load_sum =
			भाग_u64(se->avg.load_avg * se->avg.load_sum, se_weight(se));
	पूर्ण

	enqueue_load_avg(cfs_rq, se);
	cfs_rq->avg.util_avg += se->avg.util_avg;
	cfs_rq->avg.util_sum += se->avg.util_sum;
	cfs_rq->avg.runnable_avg += se->avg.runnable_avg;
	cfs_rq->avg.runnable_sum += se->avg.runnable_sum;

	add_tg_cfs_propagate(cfs_rq, se->avg.load_sum);

	cfs_rq_util_change(cfs_rq, 0);

	trace_pelt_cfs_tp(cfs_rq);
पूर्ण

/**
 * detach_entity_load_avg - detach this entity from its cfs_rq load avg
 * @cfs_rq: cfs_rq to detach from
 * @se: sched_entity to detach
 *
 * Must call update_cfs_rq_load_avg() beक्रमe this, since we rely on
 * cfs_rq->avg.last_update_समय being current.
 */
अटल व्योम detach_entity_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	/*
	 * cfs_rq->avg.period_contrib can be used क्रम both cfs_rq and se.
	 * See ___update_load_avg() क्रम details.
	 */
	u32 भागider = get_pelt_भागider(&cfs_rq->avg);

	dequeue_load_avg(cfs_rq, se);
	sub_positive(&cfs_rq->avg.util_avg, se->avg.util_avg);
	cfs_rq->avg.util_sum = cfs_rq->avg.util_avg * भागider;
	sub_positive(&cfs_rq->avg.runnable_avg, se->avg.runnable_avg);
	cfs_rq->avg.runnable_sum = cfs_rq->avg.runnable_avg * भागider;

	add_tg_cfs_propagate(cfs_rq, -se->avg.load_sum);

	cfs_rq_util_change(cfs_rq, 0);

	trace_pelt_cfs_tp(cfs_rq);
पूर्ण

/*
 * Optional action to be करोne जबतक updating the load average
 */
#घोषणा UPDATE_TG	0x1
#घोषणा SKIP_AGE_LOAD	0x2
#घोषणा DO_ATTACH	0x4

/* Update task and its cfs_rq load average */
अटल अंतरभूत व्योम update_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, पूर्णांक flags)
अणु
	u64 now = cfs_rq_घड़ी_pelt(cfs_rq);
	पूर्णांक decayed;

	/*
	 * Track task load average क्रम carrying it to new CPU after migrated, and
	 * track group sched_entity load average क्रम task_h_load calc in migration
	 */
	अगर (se->avg.last_update_समय && !(flags & SKIP_AGE_LOAD))
		__update_load_avg_se(now, cfs_rq, se);

	decayed  = update_cfs_rq_load_avg(now, cfs_rq);
	decayed |= propagate_entity_load_avg(se);

	अगर (!se->avg.last_update_समय && (flags & DO_ATTACH)) अणु

		/*
		 * DO_ATTACH means we're here from enqueue_entity().
		 * !last_update_समय means we've passed through
		 * migrate_task_rq_fair() indicating we migrated.
		 *
		 * IOW we're enqueueing a task on a new CPU.
		 */
		attach_entity_load_avg(cfs_rq, se);
		update_tg_load_avg(cfs_rq);

	पूर्ण अन्यथा अगर (decayed) अणु
		cfs_rq_util_change(cfs_rq, 0);

		अगर (flags & UPDATE_TG)
			update_tg_load_avg(cfs_rq);
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_64BIT
अटल अंतरभूत u64 cfs_rq_last_update_समय(काष्ठा cfs_rq *cfs_rq)
अणु
	u64 last_update_समय_copy;
	u64 last_update_समय;

	करो अणु
		last_update_समय_copy = cfs_rq->load_last_update_समय_copy;
		smp_rmb();
		last_update_समय = cfs_rq->avg.last_update_समय;
	पूर्ण जबतक (last_update_समय != last_update_समय_copy);

	वापस last_update_समय;
पूर्ण
#अन्यथा
अटल अंतरभूत u64 cfs_rq_last_update_समय(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस cfs_rq->avg.last_update_समय;
पूर्ण
#पूर्ण_अगर

/*
 * Synchronize entity load avg of dequeued entity without locking
 * the previous rq.
 */
अटल व्योम sync_entity_load_avg(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
	u64 last_update_समय;

	last_update_समय = cfs_rq_last_update_समय(cfs_rq);
	__update_load_avg_blocked_se(last_update_समय, se);
पूर्ण

/*
 * Task first catches up with cfs_rq, and then subtract
 * itself from the cfs_rq (task must be off the queue now).
 */
अटल व्योम हटाओ_entity_load_avg(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
	अचिन्हित दीर्घ flags;

	/*
	 * tasks cannot निकास without having gone through wake_up_new_task() ->
	 * post_init_entity_util_avg() which will have added things to the
	 * cfs_rq, so we can हटाओ unconditionally.
	 */

	sync_entity_load_avg(se);

	raw_spin_lock_irqsave(&cfs_rq->हटाओd.lock, flags);
	++cfs_rq->हटाओd.nr;
	cfs_rq->हटाओd.util_avg	+= se->avg.util_avg;
	cfs_rq->हटाओd.load_avg	+= se->avg.load_avg;
	cfs_rq->हटाओd.runnable_avg	+= se->avg.runnable_avg;
	raw_spin_unlock_irqrestore(&cfs_rq->हटाओd.lock, flags);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cfs_rq_runnable_avg(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस cfs_rq->avg.runnable_avg;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cfs_rq_load_avg(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस cfs_rq->avg.load_avg;
पूर्ण

अटल पूर्णांक newidle_balance(काष्ठा rq *this_rq, काष्ठा rq_flags *rf);

अटल अंतरभूत अचिन्हित दीर्घ task_util(काष्ठा task_काष्ठा *p)
अणु
	वापस READ_ONCE(p->se.avg.util_avg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ _task_util_est(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा util_est ue = READ_ONCE(p->se.avg.util_est);

	वापस max(ue.ewma, (ue.enqueued & ~UTIL_AVG_UNCHANGED));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ task_util_est(काष्ठा task_काष्ठा *p)
अणु
	वापस max(task_util(p), _task_util_est(p));
पूर्ण

#अगर_घोषित CONFIG_UCLAMP_TASK
अटल अंतरभूत अचिन्हित दीर्घ uclamp_task_util(काष्ठा task_काष्ठा *p)
अणु
	वापस clamp(task_util_est(p),
		     uclamp_eff_value(p, UCLAMP_MIN),
		     uclamp_eff_value(p, UCLAMP_MAX));
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ uclamp_task_util(काष्ठा task_काष्ठा *p)
अणु
	वापस task_util_est(p);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम util_est_enqueue(काष्ठा cfs_rq *cfs_rq,
				    काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक enqueued;

	अगर (!sched_feat(UTIL_EST))
		वापस;

	/* Update root cfs_rq's estimated utilization */
	enqueued  = cfs_rq->avg.util_est.enqueued;
	enqueued += _task_util_est(p);
	WRITE_ONCE(cfs_rq->avg.util_est.enqueued, enqueued);

	trace_sched_util_est_cfs_tp(cfs_rq);
पूर्ण

अटल अंतरभूत व्योम util_est_dequeue(काष्ठा cfs_rq *cfs_rq,
				    काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक enqueued;

	अगर (!sched_feat(UTIL_EST))
		वापस;

	/* Update root cfs_rq's estimated utilization */
	enqueued  = cfs_rq->avg.util_est.enqueued;
	enqueued -= min_t(अचिन्हित पूर्णांक, enqueued, _task_util_est(p));
	WRITE_ONCE(cfs_rq->avg.util_est.enqueued, enqueued);

	trace_sched_util_est_cfs_tp(cfs_rq);
पूर्ण

#घोषणा UTIL_EST_MARGIN (SCHED_CAPACITY_SCALE / 100)

/*
 * Check अगर a (चिन्हित) value is within a specअगरied (अचिन्हित) margin,
 * based on the observation that:
 *
 *     असल(x) < y := (अचिन्हित)(x + y - 1) < (2 * y - 1)
 *
 * NOTE: this only works when value + margin < पूर्णांक_उच्च.
 */
अटल अंतरभूत bool within_margin(पूर्णांक value, पूर्णांक margin)
अणु
	वापस ((अचिन्हित पूर्णांक)(value + margin - 1) < (2 * margin - 1));
पूर्ण

अटल अंतरभूत व्योम util_est_update(काष्ठा cfs_rq *cfs_rq,
				   काष्ठा task_काष्ठा *p,
				   bool task_sleep)
अणु
	दीर्घ last_ewma_dअगरf, last_enqueued_dअगरf;
	काष्ठा util_est ue;

	अगर (!sched_feat(UTIL_EST))
		वापस;

	/*
	 * Skip update of task's estimated utilization when the task has not
	 * yet completed an activation, e.g. being migrated.
	 */
	अगर (!task_sleep)
		वापस;

	/*
	 * If the PELT values haven't changed since enqueue समय,
	 * skip the util_est update.
	 */
	ue = p->se.avg.util_est;
	अगर (ue.enqueued & UTIL_AVG_UNCHANGED)
		वापस;

	last_enqueued_dअगरf = ue.enqueued;

	/*
	 * Reset EWMA on utilization increases, the moving average is used only
	 * to smooth utilization decreases.
	 */
	ue.enqueued = task_util(p);
	अगर (sched_feat(UTIL_EST_FASTUP)) अणु
		अगर (ue.ewma < ue.enqueued) अणु
			ue.ewma = ue.enqueued;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Skip update of task's estimated utilization when its members are
	 * alपढ़ोy ~1% बंद to its last activation value.
	 */
	last_ewma_dअगरf = ue.enqueued - ue.ewma;
	last_enqueued_dअगरf -= ue.enqueued;
	अगर (within_margin(last_ewma_dअगरf, UTIL_EST_MARGIN)) अणु
		अगर (!within_margin(last_enqueued_dअगरf, UTIL_EST_MARGIN))
			जाओ करोne;

		वापस;
	पूर्ण

	/*
	 * To aव्योम overestimation of actual task utilization, skip updates अगर
	 * we cannot grant there is idle समय in this CPU.
	 */
	अगर (task_util(p) > capacity_orig_of(cpu_of(rq_of(cfs_rq))))
		वापस;

	/*
	 * Update Task's estimated utilization
	 *
	 * When *p completes an activation we can consolidate another sample
	 * of the task size. This is करोne by storing the current PELT value
	 * as ue.enqueued and by using this value to update the Exponential
	 * Weighted Moving Average (EWMA):
	 *
	 *  ewma(t) = w *  task_util(p) + (1-w) * ewma(t-1)
	 *          = w *  task_util(p) +         ewma(t-1)  - w * ewma(t-1)
	 *          = w * (task_util(p) -         ewma(t-1)) +     ewma(t-1)
	 *          = w * (      last_ewma_dअगरf            ) +     ewma(t-1)
	 *          = w * (last_ewma_dअगरf  +  ewma(t-1) / w)
	 *
	 * Where 'w' is the weight of new samples, which is configured to be
	 * 0.25, thus making w=1/4 ( >>= UTIL_EST_WEIGHT_SHIFT)
	 */
	ue.ewma <<= UTIL_EST_WEIGHT_SHIFT;
	ue.ewma  += last_ewma_dअगरf;
	ue.ewma >>= UTIL_EST_WEIGHT_SHIFT;
करोne:
	ue.enqueued |= UTIL_AVG_UNCHANGED;
	WRITE_ONCE(p->se.avg.util_est, ue);

	trace_sched_util_est_se_tp(&p->se);
पूर्ण

अटल अंतरभूत पूर्णांक task_fits_capacity(काष्ठा task_काष्ठा *p, दीर्घ capacity)
अणु
	वापस fits_capacity(uclamp_task_util(p), capacity);
पूर्ण

अटल अंतरभूत व्योम update_misfit_status(काष्ठा task_काष्ठा *p, काष्ठा rq *rq)
अणु
	अगर (!अटल_branch_unlikely(&sched_asym_cpucapacity))
		वापस;

	अगर (!p || p->nr_cpus_allowed == 1) अणु
		rq->misfit_task_load = 0;
		वापस;
	पूर्ण

	अगर (task_fits_capacity(p, capacity_of(cpu_of(rq)))) अणु
		rq->misfit_task_load = 0;
		वापस;
	पूर्ण

	/*
	 * Make sure that misfit_task_load will not be null even अगर
	 * task_h_load() वापसs 0.
	 */
	rq->misfit_task_load = max_t(अचिन्हित दीर्घ, task_h_load(p), 1);
पूर्ण

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत bool cfs_rq_is_decayed(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस true;
पूर्ण

#घोषणा UPDATE_TG	0x0
#घोषणा SKIP_AGE_LOAD	0x0
#घोषणा DO_ATTACH	0x0

अटल अंतरभूत व्योम update_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, पूर्णांक not_used1)
अणु
	cfs_rq_util_change(cfs_rq, 0);
पूर्ण

अटल अंतरभूत व्योम हटाओ_entity_load_avg(काष्ठा sched_entity *se) अणुपूर्ण

अटल अंतरभूत व्योम
attach_entity_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se) अणुपूर्ण
अटल अंतरभूत व्योम
detach_entity_load_avg(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se) अणुपूर्ण

अटल अंतरभूत पूर्णांक newidle_balance(काष्ठा rq *rq, काष्ठा rq_flags *rf)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
util_est_enqueue(काष्ठा cfs_rq *cfs_rq, काष्ठा task_काष्ठा *p) अणुपूर्ण

अटल अंतरभूत व्योम
util_est_dequeue(काष्ठा cfs_rq *cfs_rq, काष्ठा task_काष्ठा *p) अणुपूर्ण

अटल अंतरभूत व्योम
util_est_update(काष्ठा cfs_rq *cfs_rq, काष्ठा task_काष्ठा *p,
		bool task_sleep) अणुपूर्ण
अटल अंतरभूत व्योम update_misfit_status(काष्ठा task_काष्ठा *p, काष्ठा rq *rq) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम check_spपढ़ो(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
#अगर_घोषित CONFIG_SCHED_DEBUG
	s64 d = se->vrunसमय - cfs_rq->min_vrunसमय;

	अगर (d < 0)
		d = -d;

	अगर (d > 3*sysctl_sched_latency)
		schedstat_inc(cfs_rq->nr_spपढ़ो_over);
#पूर्ण_अगर
पूर्ण

अटल व्योम
place_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, पूर्णांक initial)
अणु
	u64 vrunसमय = cfs_rq->min_vrunसमय;

	/*
	 * The 'current' period is alपढ़ोy promised to the current tasks,
	 * however the extra weight of the new task will slow them करोwn a
	 * little, place the new task so that it fits in the slot that
	 * stays खोलो at the end.
	 */
	अगर (initial && sched_feat(START_DEBIT))
		vrunसमय += sched_vslice(cfs_rq, se);

	/* sleeps up to a single latency करोn't count. */
	अगर (!initial) अणु
		अचिन्हित दीर्घ thresh = sysctl_sched_latency;

		/*
		 * Halve their sleep समय's effect, to allow
		 * क्रम a gentler effect of sleepers:
		 */
		अगर (sched_feat(GENTLE_FAIR_SLEEPERS))
			thresh >>= 1;

		vrunसमय -= thresh;
	पूर्ण

	/* ensure we never gain समय by being placed backwards. */
	se->vrunसमय = max_vrunसमय(se->vrunसमय, vrunसमय);
पूर्ण

अटल व्योम check_enqueue_throttle(काष्ठा cfs_rq *cfs_rq);

अटल अंतरभूत व्योम check_schedstat_required(व्योम)
अणु
#अगर_घोषित CONFIG_SCHEDSTATS
	अगर (schedstat_enabled())
		वापस;

	/* Force schedstat enabled अगर a dependent tracepoपूर्णांक is active */
	अगर (trace_sched_stat_रुको_enabled()    ||
			trace_sched_stat_sleep_enabled()   ||
			trace_sched_stat_ioरुको_enabled()  ||
			trace_sched_stat_blocked_enabled() ||
			trace_sched_stat_runसमय_enabled())  अणु
		prपूर्णांकk_deferred_once("Scheduler tracepoints stat_sleep, stat_iowait, "
			     "stat_blocked and stat_runtime require the "
			     "kernel parameter schedstats=enable or "
			     "kernel.sched_schedstats=1\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool cfs_bandwidth_used(व्योम);

/*
 * MIGRATION
 *
 *	dequeue
 *	  update_curr()
 *	    update_min_vrunसमय()
 *	  vrunसमय -= min_vrunसमय
 *
 *	enqueue
 *	  update_curr()
 *	    update_min_vrunसमय()
 *	  vrunसमय += min_vrunसमय
 *
 * this way the vrunसमय transition between RQs is करोne when both
 * min_vrunसमय are up-to-date.
 *
 * WAKEUP (remote)
 *
 *	->migrate_task_rq_fair() (p->state == TASK_WAKING)
 *	  vrunसमय -= min_vrunसमय
 *
 *	enqueue
 *	  update_curr()
 *	    update_min_vrunसमय()
 *	  vrunसमय += min_vrunसमय
 *
 * this way we करोn't have the most up-to-date min_vrunसमय on the originating
 * CPU and an up-to-date min_vrunसमय on the destination CPU.
 */

अटल व्योम
enqueue_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, पूर्णांक flags)
अणु
	bool renorm = !(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_MIGRATED);
	bool curr = cfs_rq->curr == se;

	/*
	 * If we're the current task, we must renormalise beक्रमe calling
	 * update_curr().
	 */
	अगर (renorm && curr)
		se->vrunसमय += cfs_rq->min_vrunसमय;

	update_curr(cfs_rq);

	/*
	 * Otherwise, renormalise after, such that we're placed at the current
	 * moment in समय, instead of some अक्रमom moment in the past. Being
	 * placed in the past could signअगरicantly boost this task to the
	 * fairness detriment of existing tasks.
	 */
	अगर (renorm && !curr)
		se->vrunसमय += cfs_rq->min_vrunसमय;

	/*
	 * When enqueuing a sched_entity, we must:
	 *   - Update loads to have both entity and cfs_rq synced with now.
	 *   - Add its load to cfs_rq->runnable_avg
	 *   - For group_entity, update its weight to reflect the new share of
	 *     its group cfs_rq
	 *   - Add its new weight to cfs_rq->load.weight
	 */
	update_load_avg(cfs_rq, se, UPDATE_TG | DO_ATTACH);
	se_update_runnable(se);
	update_cfs_group(se);
	account_entity_enqueue(cfs_rq, se);

	अगर (flags & ENQUEUE_WAKEUP)
		place_entity(cfs_rq, se, 0);

	check_schedstat_required();
	update_stats_enqueue(cfs_rq, se, flags);
	check_spपढ़ो(cfs_rq, se);
	अगर (!curr)
		__enqueue_entity(cfs_rq, se);
	se->on_rq = 1;

	/*
	 * When bandwidth control is enabled, cfs might have been हटाओd
	 * because of a parent been throttled but cfs->nr_running > 1. Try to
	 * add it unconditionally.
	 */
	अगर (cfs_rq->nr_running == 1 || cfs_bandwidth_used())
		list_add_leaf_cfs_rq(cfs_rq);

	अगर (cfs_rq->nr_running == 1)
		check_enqueue_throttle(cfs_rq);
पूर्ण

अटल व्योम __clear_buddies_last(काष्ठा sched_entity *se)
अणु
	क्रम_each_sched_entity(se) अणु
		काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
		अगर (cfs_rq->last != se)
			अवरोध;

		cfs_rq->last = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __clear_buddies_next(काष्ठा sched_entity *se)
अणु
	क्रम_each_sched_entity(se) अणु
		काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
		अगर (cfs_rq->next != se)
			अवरोध;

		cfs_rq->next = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __clear_buddies_skip(काष्ठा sched_entity *se)
अणु
	क्रम_each_sched_entity(se) अणु
		काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
		अगर (cfs_rq->skip != se)
			अवरोध;

		cfs_rq->skip = शून्य;
	पूर्ण
पूर्ण

अटल व्योम clear_buddies(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	अगर (cfs_rq->last == se)
		__clear_buddies_last(se);

	अगर (cfs_rq->next == se)
		__clear_buddies_next(se);

	अगर (cfs_rq->skip == se)
		__clear_buddies_skip(se);
पूर्ण

अटल __always_अंतरभूत व्योम वापस_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq);

अटल व्योम
dequeue_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se, पूर्णांक flags)
अणु
	/*
	 * Update run-समय statistics of the 'current'.
	 */
	update_curr(cfs_rq);

	/*
	 * When dequeuing a sched_entity, we must:
	 *   - Update loads to have both entity and cfs_rq synced with now.
	 *   - Subtract its load from the cfs_rq->runnable_avg.
	 *   - Subtract its previous weight from cfs_rq->load.weight.
	 *   - For group entity, update its weight to reflect the new share
	 *     of its group cfs_rq.
	 */
	update_load_avg(cfs_rq, se, UPDATE_TG);
	se_update_runnable(se);

	update_stats_dequeue(cfs_rq, se, flags);

	clear_buddies(cfs_rq, se);

	अगर (se != cfs_rq->curr)
		__dequeue_entity(cfs_rq, se);
	se->on_rq = 0;
	account_entity_dequeue(cfs_rq, se);

	/*
	 * Normalize after update_curr(); which will also have moved
	 * min_vrunसमय अगर @se is the one holding it back. But beक्रमe करोing
	 * update_min_vrunसमय() again, which will discount @se's position and
	 * can move min_vrunसमय क्रमward still more.
	 */
	अगर (!(flags & DEQUEUE_SLEEP))
		se->vrunसमय -= cfs_rq->min_vrunसमय;

	/* वापस excess runसमय on last dequeue */
	वापस_cfs_rq_runसमय(cfs_rq);

	update_cfs_group(se);

	/*
	 * Now advance min_vrunसमय अगर @se was the entity holding it back,
	 * except when: DEQUEUE_SAVE && !DEQUEUE_MOVE, in this हाल we'll be
	 * put back on, and अगर we advance min_vrunसमय, we'll be placed back
	 * further than we started -- ie. we'll be penalized.
	 */
	अगर ((flags & (DEQUEUE_SAVE | DEQUEUE_MOVE)) != DEQUEUE_SAVE)
		update_min_vrunसमय(cfs_rq);
पूर्ण

/*
 * Preempt the current task with a newly woken task अगर needed:
 */
अटल व्योम
check_preempt_tick(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *curr)
अणु
	अचिन्हित दीर्घ ideal_runसमय, delta_exec;
	काष्ठा sched_entity *se;
	s64 delta;

	ideal_runसमय = sched_slice(cfs_rq, curr);
	delta_exec = curr->sum_exec_runसमय - curr->prev_sum_exec_runसमय;
	अगर (delta_exec > ideal_runसमय) अणु
		resched_curr(rq_of(cfs_rq));
		/*
		 * The current task ran दीर्घ enough, ensure it करोesn't get
		 * re-elected due to buddy favours.
		 */
		clear_buddies(cfs_rq, curr);
		वापस;
	पूर्ण

	/*
	 * Ensure that a task that missed wakeup preemption by a
	 * narrow margin करोesn't have to रुको क्रम a full slice.
	 * This also mitigates buddy induced latencies under load.
	 */
	अगर (delta_exec < sysctl_sched_min_granularity)
		वापस;

	se = __pick_first_entity(cfs_rq);
	delta = curr->vrunसमय - se->vrunसमय;

	अगर (delta < 0)
		वापस;

	अगर (delta > ideal_runसमय)
		resched_curr(rq_of(cfs_rq));
पूर्ण

अटल व्योम
set_next_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *se)
अणु
	/* 'current' is not kept within the tree. */
	अगर (se->on_rq) अणु
		/*
		 * Any task has to be enqueued beक्रमe it get to execute on
		 * a CPU. So account क्रम the समय it spent रुकोing on the
		 * runqueue.
		 */
		update_stats_रुको_end(cfs_rq, se);
		__dequeue_entity(cfs_rq, se);
		update_load_avg(cfs_rq, se, UPDATE_TG);
	पूर्ण

	update_stats_curr_start(cfs_rq, se);
	cfs_rq->curr = se;

	/*
	 * Track our maximum slice length, अगर the CPU's load is at
	 * least twice that of our own weight (i.e. करोnt track it
	 * when there are only lesser-weight tasks around):
	 */
	अगर (schedstat_enabled() &&
	    rq_of(cfs_rq)->cfs.load.weight >= 2*se->load.weight) अणु
		schedstat_set(se->statistics.slice_max,
			max((u64)schedstat_val(se->statistics.slice_max),
			    se->sum_exec_runसमय - se->prev_sum_exec_runसमय));
	पूर्ण

	se->prev_sum_exec_runसमय = se->sum_exec_runसमय;
पूर्ण

अटल पूर्णांक
wakeup_preempt_entity(काष्ठा sched_entity *curr, काष्ठा sched_entity *se);

/*
 * Pick the next process, keeping these things in mind, in this order:
 * 1) keep things fair between processes/task groups
 * 2) pick the "next" process, since someone really wants that to run
 * 3) pick the "last" process, क्रम cache locality
 * 4) करो not run the "skip" process, अगर something अन्यथा is available
 */
अटल काष्ठा sched_entity *
pick_next_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *curr)
अणु
	काष्ठा sched_entity *left = __pick_first_entity(cfs_rq);
	काष्ठा sched_entity *se;

	/*
	 * If curr is set we have to see अगर its left of the lefपंचांगost entity
	 * still in the tree, provided there was anything in the tree at all.
	 */
	अगर (!left || (curr && entity_beक्रमe(curr, left)))
		left = curr;

	se = left; /* ideally we run the lefपंचांगost entity */

	/*
	 * Aव्योम running the skip buddy, अगर running something अन्यथा can
	 * be करोne without getting too unfair.
	 */
	अगर (cfs_rq->skip == se) अणु
		काष्ठा sched_entity *second;

		अगर (se == curr) अणु
			second = __pick_first_entity(cfs_rq);
		पूर्ण अन्यथा अणु
			second = __pick_next_entity(se);
			अगर (!second || (curr && entity_beक्रमe(curr, second)))
				second = curr;
		पूर्ण

		अगर (second && wakeup_preempt_entity(second, left) < 1)
			se = second;
	पूर्ण

	अगर (cfs_rq->next && wakeup_preempt_entity(cfs_rq->next, left) < 1) अणु
		/*
		 * Someone really wants this to run. If it's not unfair, run it.
		 */
		se = cfs_rq->next;
	पूर्ण अन्यथा अगर (cfs_rq->last && wakeup_preempt_entity(cfs_rq->last, left) < 1) अणु
		/*
		 * Prefer last buddy, try to वापस the CPU to a preempted task.
		 */
		se = cfs_rq->last;
	पूर्ण

	clear_buddies(cfs_rq, se);

	वापस se;
पूर्ण

अटल bool check_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq);

अटल व्योम put_prev_entity(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *prev)
अणु
	/*
	 * If still on the runqueue then deactivate_task()
	 * was not called and update_curr() has to be करोne:
	 */
	अगर (prev->on_rq)
		update_curr(cfs_rq);

	/* throttle cfs_rqs exceeding runसमय */
	check_cfs_rq_runसमय(cfs_rq);

	check_spपढ़ो(cfs_rq, prev);

	अगर (prev->on_rq) अणु
		update_stats_रुको_start(cfs_rq, prev);
		/* Put 'current' back पूर्णांकo the tree. */
		__enqueue_entity(cfs_rq, prev);
		/* in !on_rq हाल, update occurred at dequeue */
		update_load_avg(cfs_rq, prev, 0);
	पूर्ण
	cfs_rq->curr = शून्य;
पूर्ण

अटल व्योम
entity_tick(काष्ठा cfs_rq *cfs_rq, काष्ठा sched_entity *curr, पूर्णांक queued)
अणु
	/*
	 * Update run-समय statistics of the 'current'.
	 */
	update_curr(cfs_rq);

	/*
	 * Ensure that runnable average is periodically updated.
	 */
	update_load_avg(cfs_rq, curr, UPDATE_TG);
	update_cfs_group(curr);

#अगर_घोषित CONFIG_SCHED_HRTICK
	/*
	 * queued ticks are scheduled to match the slice, so करोn't bother
	 * validating it and just reschedule.
	 */
	अगर (queued) अणु
		resched_curr(rq_of(cfs_rq));
		वापस;
	पूर्ण
	/*
	 * करोn't let the period tick पूर्णांकerfere with the hrtick preemption
	 */
	अगर (!sched_feat(DOUBLE_TICK) &&
			hrसमयr_active(&rq_of(cfs_rq)->hrtick_समयr))
		वापस;
#पूर्ण_अगर

	अगर (cfs_rq->nr_running > 1)
		check_preempt_tick(cfs_rq, curr);
पूर्ण


/**************************************************
 * CFS bandwidth control machinery
 */

#अगर_घोषित CONFIG_CFS_BANDWIDTH

#अगर_घोषित CONFIG_JUMP_LABEL
अटल काष्ठा अटल_key __cfs_bandwidth_used;

अटल अंतरभूत bool cfs_bandwidth_used(व्योम)
अणु
	वापस अटल_key_false(&__cfs_bandwidth_used);
पूर्ण

व्योम cfs_bandwidth_usage_inc(व्योम)
अणु
	अटल_key_slow_inc_cpuslocked(&__cfs_bandwidth_used);
पूर्ण

व्योम cfs_bandwidth_usage_dec(व्योम)
अणु
	अटल_key_slow_dec_cpuslocked(&__cfs_bandwidth_used);
पूर्ण
#अन्यथा /* CONFIG_JUMP_LABEL */
अटल bool cfs_bandwidth_used(व्योम)
अणु
	वापस true;
पूर्ण

व्योम cfs_bandwidth_usage_inc(व्योम) अणुपूर्ण
व्योम cfs_bandwidth_usage_dec(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_JUMP_LABEL */

/*
 * शेष period क्रम cfs group bandwidth.
 * शेष: 0.1s, units: nanoseconds
 */
अटल अंतरभूत u64 शेष_cfs_period(व्योम)
अणु
	वापस 100000000ULL;
पूर्ण

अटल अंतरभूत u64 sched_cfs_bandwidth_slice(व्योम)
अणु
	वापस (u64)sysctl_sched_cfs_bandwidth_slice * NSEC_PER_USEC;
पूर्ण

/*
 * Replenish runसमय according to asचिन्हित quota. We use sched_घड़ी_cpu
 * directly instead of rq->घड़ी to aव्योम adding additional synchronization
 * around rq->lock.
 *
 * requires cfs_b->lock
 */
व्योम __refill_cfs_bandwidth_runसमय(काष्ठा cfs_bandwidth *cfs_b)
अणु
	अगर (cfs_b->quota != RUNTIME_INF)
		cfs_b->runसमय = cfs_b->quota;
पूर्ण

अटल अंतरभूत काष्ठा cfs_bandwidth *tg_cfs_bandwidth(काष्ठा task_group *tg)
अणु
	वापस &tg->cfs_bandwidth;
पूर्ण

/* वापसs 0 on failure to allocate runसमय */
अटल पूर्णांक __assign_cfs_rq_runसमय(काष्ठा cfs_bandwidth *cfs_b,
				   काष्ठा cfs_rq *cfs_rq, u64 target_runसमय)
अणु
	u64 min_amount, amount = 0;

	lockdep_निश्चित_held(&cfs_b->lock);

	/* note: this is a positive sum as runसमय_reमुख्यing <= 0 */
	min_amount = target_runसमय - cfs_rq->runसमय_reमुख्यing;

	अगर (cfs_b->quota == RUNTIME_INF)
		amount = min_amount;
	अन्यथा अणु
		start_cfs_bandwidth(cfs_b);

		अगर (cfs_b->runसमय > 0) अणु
			amount = min(cfs_b->runसमय, min_amount);
			cfs_b->runसमय -= amount;
			cfs_b->idle = 0;
		पूर्ण
	पूर्ण

	cfs_rq->runसमय_reमुख्यing += amount;

	वापस cfs_rq->runसमय_reमुख्यing > 0;
पूर्ण

/* वापसs 0 on failure to allocate runसमय */
अटल पूर्णांक assign_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_rq->tg);
	पूर्णांक ret;

	raw_spin_lock(&cfs_b->lock);
	ret = __assign_cfs_rq_runसमय(cfs_b, cfs_rq, sched_cfs_bandwidth_slice());
	raw_spin_unlock(&cfs_b->lock);

	वापस ret;
पूर्ण

अटल व्योम __account_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq, u64 delta_exec)
अणु
	/* करोck delta_exec beक्रमe expiring quota (as it could span periods) */
	cfs_rq->runसमय_reमुख्यing -= delta_exec;

	अगर (likely(cfs_rq->runसमय_reमुख्यing > 0))
		वापस;

	अगर (cfs_rq->throttled)
		वापस;
	/*
	 * अगर we're unable to extend our runसमय we resched so that the active
	 * hierarchy can be throttled
	 */
	अगर (!assign_cfs_rq_runसमय(cfs_rq) && likely(cfs_rq->curr))
		resched_curr(rq_of(cfs_rq));
पूर्ण

अटल __always_अंतरभूत
व्योम account_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq, u64 delta_exec)
अणु
	अगर (!cfs_bandwidth_used() || !cfs_rq->runसमय_enabled)
		वापस;

	__account_cfs_rq_runसमय(cfs_rq, delta_exec);
पूर्ण

अटल अंतरभूत पूर्णांक cfs_rq_throttled(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस cfs_bandwidth_used() && cfs_rq->throttled;
पूर्ण

/* check whether cfs_rq, or any parent, is throttled */
अटल अंतरभूत पूर्णांक throttled_hierarchy(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस cfs_bandwidth_used() && cfs_rq->throttle_count;
पूर्ण

/*
 * Ensure that neither of the group entities corresponding to src_cpu or
 * dest_cpu are members of a throttled hierarchy when perक्रमming group
 * load-balance operations.
 */
अटल अंतरभूत पूर्णांक throttled_lb_pair(काष्ठा task_group *tg,
				    पूर्णांक src_cpu, पूर्णांक dest_cpu)
अणु
	काष्ठा cfs_rq *src_cfs_rq, *dest_cfs_rq;

	src_cfs_rq = tg->cfs_rq[src_cpu];
	dest_cfs_rq = tg->cfs_rq[dest_cpu];

	वापस throttled_hierarchy(src_cfs_rq) ||
	       throttled_hierarchy(dest_cfs_rq);
पूर्ण

अटल पूर्णांक tg_unthrottle_up(काष्ठा task_group *tg, व्योम *data)
अणु
	काष्ठा rq *rq = data;
	काष्ठा cfs_rq *cfs_rq = tg->cfs_rq[cpu_of(rq)];

	cfs_rq->throttle_count--;
	अगर (!cfs_rq->throttle_count) अणु
		cfs_rq->throttled_घड़ी_प्रकारask_समय += rq_घड़ी_प्रकारask(rq) -
					     cfs_rq->throttled_घड़ी_प्रकारask;

		/* Add cfs_rq with load or one or more alपढ़ोy running entities to the list */
		अगर (!cfs_rq_is_decayed(cfs_rq) || cfs_rq->nr_running)
			list_add_leaf_cfs_rq(cfs_rq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tg_throttle_करोwn(काष्ठा task_group *tg, व्योम *data)
अणु
	काष्ठा rq *rq = data;
	काष्ठा cfs_rq *cfs_rq = tg->cfs_rq[cpu_of(rq)];

	/* group is entering throttled state, stop समय */
	अगर (!cfs_rq->throttle_count) अणु
		cfs_rq->throttled_घड़ी_प्रकारask = rq_घड़ी_प्रकारask(rq);
		list_del_leaf_cfs_rq(cfs_rq);
	पूर्ण
	cfs_rq->throttle_count++;

	वापस 0;
पूर्ण

अटल bool throttle_cfs_rq(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा rq *rq = rq_of(cfs_rq);
	काष्ठा cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_rq->tg);
	काष्ठा sched_entity *se;
	दीर्घ task_delta, idle_task_delta, dequeue = 1;

	raw_spin_lock(&cfs_b->lock);
	/* This will start the period समयr अगर necessary */
	अगर (__assign_cfs_rq_runसमय(cfs_b, cfs_rq, 1)) अणु
		/*
		 * We have raced with bandwidth becoming available, and अगर we
		 * actually throttled the समयr might not unthrottle us क्रम an
		 * entire period. We additionally needed to make sure that any
		 * subsequent check_cfs_rq_runसमय calls agree not to throttle
		 * us, as we may commit to करो cfs put_prev+pick_next, so we ask
		 * क्रम 1ns of runसमय rather than just check cfs_b.
		 */
		dequeue = 0;
	पूर्ण अन्यथा अणु
		list_add_tail_rcu(&cfs_rq->throttled_list,
				  &cfs_b->throttled_cfs_rq);
	पूर्ण
	raw_spin_unlock(&cfs_b->lock);

	अगर (!dequeue)
		वापस false;  /* Throttle no दीर्घer required. */

	se = cfs_rq->tg->se[cpu_of(rq_of(cfs_rq))];

	/* मुक्तze hierarchy runnable averages जबतक throttled */
	rcu_पढ़ो_lock();
	walk_tg_tree_from(cfs_rq->tg, tg_throttle_करोwn, tg_nop, (व्योम *)rq);
	rcu_पढ़ो_unlock();

	task_delta = cfs_rq->h_nr_running;
	idle_task_delta = cfs_rq->idle_h_nr_running;
	क्रम_each_sched_entity(se) अणु
		काष्ठा cfs_rq *qcfs_rq = cfs_rq_of(se);
		/* throttled entity or throttle-on-deactivate */
		अगर (!se->on_rq)
			जाओ करोne;

		dequeue_entity(qcfs_rq, se, DEQUEUE_SLEEP);

		qcfs_rq->h_nr_running -= task_delta;
		qcfs_rq->idle_h_nr_running -= idle_task_delta;

		अगर (qcfs_rq->load.weight) अणु
			/* Aव्योम re-evaluating load क्रम this entity: */
			se = parent_entity(se);
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम_each_sched_entity(se) अणु
		काष्ठा cfs_rq *qcfs_rq = cfs_rq_of(se);
		/* throttled entity or throttle-on-deactivate */
		अगर (!se->on_rq)
			जाओ करोne;

		update_load_avg(qcfs_rq, se, 0);
		se_update_runnable(se);

		qcfs_rq->h_nr_running -= task_delta;
		qcfs_rq->idle_h_nr_running -= idle_task_delta;
	पूर्ण

	/* At this poपूर्णांक se is शून्य and we are at root level*/
	sub_nr_running(rq, task_delta);

करोne:
	/*
	 * Note: distribution will alपढ़ोy see us throttled via the
	 * throttled-list.  rq->lock protects completion.
	 */
	cfs_rq->throttled = 1;
	cfs_rq->throttled_घड़ी = rq_घड़ी(rq);
	वापस true;
पूर्ण

व्योम unthrottle_cfs_rq(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा rq *rq = rq_of(cfs_rq);
	काष्ठा cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_rq->tg);
	काष्ठा sched_entity *se;
	दीर्घ task_delta, idle_task_delta;

	se = cfs_rq->tg->se[cpu_of(rq)];

	cfs_rq->throttled = 0;

	update_rq_घड़ी(rq);

	raw_spin_lock(&cfs_b->lock);
	cfs_b->throttled_समय += rq_घड़ी(rq) - cfs_rq->throttled_घड़ी;
	list_del_rcu(&cfs_rq->throttled_list);
	raw_spin_unlock(&cfs_b->lock);

	/* update hierarchical throttle state */
	walk_tg_tree_from(cfs_rq->tg, tg_nop, tg_unthrottle_up, (व्योम *)rq);

	अगर (!cfs_rq->load.weight)
		वापस;

	task_delta = cfs_rq->h_nr_running;
	idle_task_delta = cfs_rq->idle_h_nr_running;
	क्रम_each_sched_entity(se) अणु
		अगर (se->on_rq)
			अवरोध;
		cfs_rq = cfs_rq_of(se);
		enqueue_entity(cfs_rq, se, ENQUEUE_WAKEUP);

		cfs_rq->h_nr_running += task_delta;
		cfs_rq->idle_h_nr_running += idle_task_delta;

		/* end evaluation on encountering a throttled cfs_rq */
		अगर (cfs_rq_throttled(cfs_rq))
			जाओ unthrottle_throttle;
	पूर्ण

	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);

		update_load_avg(cfs_rq, se, UPDATE_TG);
		se_update_runnable(se);

		cfs_rq->h_nr_running += task_delta;
		cfs_rq->idle_h_nr_running += idle_task_delta;


		/* end evaluation on encountering a throttled cfs_rq */
		अगर (cfs_rq_throttled(cfs_rq))
			जाओ unthrottle_throttle;

		/*
		 * One parent has been throttled and cfs_rq हटाओd from the
		 * list. Add it back to not अवरोध the leaf list.
		 */
		अगर (throttled_hierarchy(cfs_rq))
			list_add_leaf_cfs_rq(cfs_rq);
	पूर्ण

	/* At this poपूर्णांक se is शून्य and we are at root level*/
	add_nr_running(rq, task_delta);

unthrottle_throttle:
	/*
	 * The cfs_rq_throttled() अवरोधs in the above iteration can result in
	 * incomplete leaf list मुख्यtenance, resulting in triggering the
	 * निश्चितion below.
	 */
	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);

		अगर (list_add_leaf_cfs_rq(cfs_rq))
			अवरोध;
	पूर्ण

	निश्चित_list_leaf_cfs_rq(rq);

	/* Determine whether we need to wake up potentially idle CPU: */
	अगर (rq->curr == rq->idle && rq->cfs.nr_running)
		resched_curr(rq);
पूर्ण

अटल व्योम distribute_cfs_runसमय(काष्ठा cfs_bandwidth *cfs_b)
अणु
	काष्ठा cfs_rq *cfs_rq;
	u64 runसमय, reमुख्यing = 1;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(cfs_rq, &cfs_b->throttled_cfs_rq,
				throttled_list) अणु
		काष्ठा rq *rq = rq_of(cfs_rq);
		काष्ठा rq_flags rf;

		rq_lock_irqsave(rq, &rf);
		अगर (!cfs_rq_throttled(cfs_rq))
			जाओ next;

		/* By the above check, this should never be true */
		SCHED_WARN_ON(cfs_rq->runसमय_reमुख्यing > 0);

		raw_spin_lock(&cfs_b->lock);
		runसमय = -cfs_rq->runसमय_reमुख्यing + 1;
		अगर (runसमय > cfs_b->runसमय)
			runसमय = cfs_b->runसमय;
		cfs_b->runसमय -= runसमय;
		reमुख्यing = cfs_b->runसमय;
		raw_spin_unlock(&cfs_b->lock);

		cfs_rq->runसमय_reमुख्यing += runसमय;

		/* we check whether we're throttled above */
		अगर (cfs_rq->runसमय_reमुख्यing > 0)
			unthrottle_cfs_rq(cfs_rq);

next:
		rq_unlock_irqrestore(rq, &rf);

		अगर (!reमुख्यing)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Responsible क्रम refilling a task_group's bandwidth and unthrottling its
 * cfs_rqs as appropriate. If there has been no activity within the last
 * period the समयr is deactivated until scheduling resumes; cfs_b->idle is
 * used to track this state.
 */
अटल पूर्णांक करो_sched_cfs_period_समयr(काष्ठा cfs_bandwidth *cfs_b, पूर्णांक overrun, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक throttled;

	/* no need to जारी the समयr with no bandwidth स्थिरraपूर्णांक */
	अगर (cfs_b->quota == RUNTIME_INF)
		जाओ out_deactivate;

	throttled = !list_empty(&cfs_b->throttled_cfs_rq);
	cfs_b->nr_periods += overrun;

	/*
	 * idle depends on !throttled (क्रम the हाल of a large deficit), and अगर
	 * we're going inactive then everything अन्यथा can be deferred
	 */
	अगर (cfs_b->idle && !throttled)
		जाओ out_deactivate;

	__refill_cfs_bandwidth_runसमय(cfs_b);

	अगर (!throttled) अणु
		/* mark as potentially idle क्रम the upcoming period */
		cfs_b->idle = 1;
		वापस 0;
	पूर्ण

	/* account preceding periods in which throttling occurred */
	cfs_b->nr_throttled += overrun;

	/*
	 * This check is repeated as we release cfs_b->lock जबतक we unthrottle.
	 */
	जबतक (throttled && cfs_b->runसमय > 0) अणु
		raw_spin_unlock_irqrestore(&cfs_b->lock, flags);
		/* we can't nest cfs_b->lock जबतक distributing bandwidth */
		distribute_cfs_runसमय(cfs_b);
		raw_spin_lock_irqsave(&cfs_b->lock, flags);

		throttled = !list_empty(&cfs_b->throttled_cfs_rq);
	पूर्ण

	/*
	 * While we are ensured activity in the period following an
	 * unthrottle, this also covers the हाल in which the new bandwidth is
	 * insufficient to cover the existing bandwidth deficit.  (Forcing the
	 * समयr to reमुख्य active जबतक there are any throttled entities.)
	 */
	cfs_b->idle = 0;

	वापस 0;

out_deactivate:
	वापस 1;
पूर्ण

/* a cfs_rq won't करोnate quota below this amount */
अटल स्थिर u64 min_cfs_rq_runसमय = 1 * NSEC_PER_MSEC;
/* minimum reमुख्यing period समय to redistribute slack quota */
अटल स्थिर u64 min_bandwidth_expiration = 2 * NSEC_PER_MSEC;
/* how दीर्घ we रुको to gather additional slack beक्रमe distributing */
अटल स्थिर u64 cfs_bandwidth_slack_period = 5 * NSEC_PER_MSEC;

/*
 * Are we near the end of the current quota period?
 *
 * Requires cfs_b->lock क्रम hrसमयr_expires_reमुख्यing to be safe against the
 * hrसमयr base being cleared by hrसमयr_start. In the हाल of
 * migrate_hrसमयrs, base is never cleared, so we are fine.
 */
अटल पूर्णांक runसमय_refresh_within(काष्ठा cfs_bandwidth *cfs_b, u64 min_expire)
अणु
	काष्ठा hrसमयr *refresh_समयr = &cfs_b->period_समयr;
	u64 reमुख्यing;

	/* अगर the call-back is running a quota refresh is alपढ़ोy occurring */
	अगर (hrसमयr_callback_running(refresh_समयr))
		वापस 1;

	/* is a quota refresh about to occur? */
	reमुख्यing = kसमय_प्रकारo_ns(hrसमयr_expires_reमुख्यing(refresh_समयr));
	अगर (reमुख्यing < min_expire)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम start_cfs_slack_bandwidth(काष्ठा cfs_bandwidth *cfs_b)
अणु
	u64 min_left = cfs_bandwidth_slack_period + min_bandwidth_expiration;

	/* अगर there's a quota refresh soon don't bother with slack */
	अगर (runसमय_refresh_within(cfs_b, min_left))
		वापस;

	/* करोn't push क्रमwards an existing deferred unthrottle */
	अगर (cfs_b->slack_started)
		वापस;
	cfs_b->slack_started = true;

	hrसमयr_start(&cfs_b->slack_समयr,
			ns_to_kसमय(cfs_bandwidth_slack_period),
			HRTIMER_MODE_REL);
पूर्ण

/* we know any runसमय found here is valid as update_curr() precedes वापस */
अटल व्योम __वापस_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा cfs_bandwidth *cfs_b = tg_cfs_bandwidth(cfs_rq->tg);
	s64 slack_runसमय = cfs_rq->runसमय_reमुख्यing - min_cfs_rq_runसमय;

	अगर (slack_runसमय <= 0)
		वापस;

	raw_spin_lock(&cfs_b->lock);
	अगर (cfs_b->quota != RUNTIME_INF) अणु
		cfs_b->runसमय += slack_runसमय;

		/* we are under rq->lock, defer unthrottling using a समयr */
		अगर (cfs_b->runसमय > sched_cfs_bandwidth_slice() &&
		    !list_empty(&cfs_b->throttled_cfs_rq))
			start_cfs_slack_bandwidth(cfs_b);
	पूर्ण
	raw_spin_unlock(&cfs_b->lock);

	/* even अगर it's not valid for return we don't want to try again */
	cfs_rq->runसमय_reमुख्यing -= slack_runसमय;
पूर्ण

अटल __always_अंतरभूत व्योम वापस_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (!cfs_bandwidth_used())
		वापस;

	अगर (!cfs_rq->runसमय_enabled || cfs_rq->nr_running)
		वापस;

	__वापस_cfs_rq_runसमय(cfs_rq);
पूर्ण

/*
 * This is करोne with a समयr (instead of अंतरभूत with bandwidth वापस) since
 * it's necessary to juggle rq->locks to unthrottle their respective cfs_rqs.
 */
अटल व्योम करो_sched_cfs_slack_समयr(काष्ठा cfs_bandwidth *cfs_b)
अणु
	u64 runसमय = 0, slice = sched_cfs_bandwidth_slice();
	अचिन्हित दीर्घ flags;

	/* confirm we're still not at a refresh boundary */
	raw_spin_lock_irqsave(&cfs_b->lock, flags);
	cfs_b->slack_started = false;

	अगर (runसमय_refresh_within(cfs_b, min_bandwidth_expiration)) अणु
		raw_spin_unlock_irqrestore(&cfs_b->lock, flags);
		वापस;
	पूर्ण

	अगर (cfs_b->quota != RUNTIME_INF && cfs_b->runसमय > slice)
		runसमय = cfs_b->runसमय;

	raw_spin_unlock_irqrestore(&cfs_b->lock, flags);

	अगर (!runसमय)
		वापस;

	distribute_cfs_runसमय(cfs_b);
पूर्ण

/*
 * When a group wakes up we want to make sure that its quota is not alपढ़ोy
 * expired/exceeded, otherwise it may be allowed to steal additional ticks of
 * runसमय as update_curr() throttling can not trigger until it's on-rq.
 */
अटल व्योम check_enqueue_throttle(काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (!cfs_bandwidth_used())
		वापस;

	/* an active group must be handled by the update_curr()->put() path */
	अगर (!cfs_rq->runसमय_enabled || cfs_rq->curr)
		वापस;

	/* ensure the group is not alपढ़ोy throttled */
	अगर (cfs_rq_throttled(cfs_rq))
		वापस;

	/* update runसमय allocation */
	account_cfs_rq_runसमय(cfs_rq, 0);
	अगर (cfs_rq->runसमय_reमुख्यing <= 0)
		throttle_cfs_rq(cfs_rq);
पूर्ण

अटल व्योम sync_throttle(काष्ठा task_group *tg, पूर्णांक cpu)
अणु
	काष्ठा cfs_rq *pcfs_rq, *cfs_rq;

	अगर (!cfs_bandwidth_used())
		वापस;

	अगर (!tg->parent)
		वापस;

	cfs_rq = tg->cfs_rq[cpu];
	pcfs_rq = tg->parent->cfs_rq[cpu];

	cfs_rq->throttle_count = pcfs_rq->throttle_count;
	cfs_rq->throttled_घड़ी_प्रकारask = rq_घड़ी_प्रकारask(cpu_rq(cpu));
पूर्ण

/* conditionally throttle active cfs_rq's from put_prev_entity() */
अटल bool check_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (!cfs_bandwidth_used())
		वापस false;

	अगर (likely(!cfs_rq->runसमय_enabled || cfs_rq->runसमय_reमुख्यing > 0))
		वापस false;

	/*
	 * it's possible क्रम a throttled entity to be क्रमced पूर्णांकo a running
	 * state (e.g. set_curr_task), in this हाल we're finished.
	 */
	अगर (cfs_rq_throttled(cfs_rq))
		वापस true;

	वापस throttle_cfs_rq(cfs_rq);
पूर्ण

अटल क्रमागत hrसमयr_restart sched_cfs_slack_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा cfs_bandwidth *cfs_b =
		container_of(समयr, काष्ठा cfs_bandwidth, slack_समयr);

	करो_sched_cfs_slack_समयr(cfs_b);

	वापस HRTIMER_NORESTART;
पूर्ण

बाह्य स्थिर u64 max_cfs_quota_period;

अटल क्रमागत hrसमयr_restart sched_cfs_period_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा cfs_bandwidth *cfs_b =
		container_of(समयr, काष्ठा cfs_bandwidth, period_समयr);
	अचिन्हित दीर्घ flags;
	पूर्णांक overrun;
	पूर्णांक idle = 0;
	पूर्णांक count = 0;

	raw_spin_lock_irqsave(&cfs_b->lock, flags);
	क्रम (;;) अणु
		overrun = hrसमयr_क्रमward_now(समयr, cfs_b->period);
		अगर (!overrun)
			अवरोध;

		idle = करो_sched_cfs_period_समयr(cfs_b, overrun, flags);

		अगर (++count > 3) अणु
			u64 new, old = kसमय_प्रकारo_ns(cfs_b->period);

			/*
			 * Grow period by a factor of 2 to aव्योम losing precision.
			 * Precision loss in the quota/period ratio can cause __cfs_schedulable
			 * to fail.
			 */
			new = old * 2;
			अगर (new < max_cfs_quota_period) अणु
				cfs_b->period = ns_to_kसमय(new);
				cfs_b->quota *= 2;

				pr_warn_ratelimited(
	"cfs_period_timer[cpu%d]: period too short, scaling up (new cfs_period_us = %lld, cfs_quota_us = %lld)\n",
					smp_processor_id(),
					भाग_u64(new, NSEC_PER_USEC),
					भाग_u64(cfs_b->quota, NSEC_PER_USEC));
			पूर्ण अन्यथा अणु
				pr_warn_ratelimited(
	"cfs_period_timer[cpu%d]: period too short, but cannot scale up without losing precision (cfs_period_us = %lld, cfs_quota_us = %lld)\n",
					smp_processor_id(),
					भाग_u64(old, NSEC_PER_USEC),
					भाग_u64(cfs_b->quota, NSEC_PER_USEC));
			पूर्ण

			/* reset count so we करोn't come right back in here */
			count = 0;
		पूर्ण
	पूर्ण
	अगर (idle)
		cfs_b->period_active = 0;
	raw_spin_unlock_irqrestore(&cfs_b->lock, flags);

	वापस idle ? HRTIMER_NORESTART : HRTIMER_RESTART;
पूर्ण

व्योम init_cfs_bandwidth(काष्ठा cfs_bandwidth *cfs_b)
अणु
	raw_spin_lock_init(&cfs_b->lock);
	cfs_b->runसमय = 0;
	cfs_b->quota = RUNTIME_INF;
	cfs_b->period = ns_to_kसमय(शेष_cfs_period());

	INIT_LIST_HEAD(&cfs_b->throttled_cfs_rq);
	hrसमयr_init(&cfs_b->period_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_PINNED);
	cfs_b->period_समयr.function = sched_cfs_period_समयr;
	hrसमयr_init(&cfs_b->slack_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	cfs_b->slack_समयr.function = sched_cfs_slack_समयr;
	cfs_b->slack_started = false;
पूर्ण

अटल व्योम init_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq)
अणु
	cfs_rq->runसमय_enabled = 0;
	INIT_LIST_HEAD(&cfs_rq->throttled_list);
पूर्ण

व्योम start_cfs_bandwidth(काष्ठा cfs_bandwidth *cfs_b)
अणु
	lockdep_निश्चित_held(&cfs_b->lock);

	अगर (cfs_b->period_active)
		वापस;

	cfs_b->period_active = 1;
	hrसमयr_क्रमward_now(&cfs_b->period_समयr, cfs_b->period);
	hrसमयr_start_expires(&cfs_b->period_समयr, HRTIMER_MODE_ABS_PINNED);
पूर्ण

अटल व्योम destroy_cfs_bandwidth(काष्ठा cfs_bandwidth *cfs_b)
अणु
	/* init_cfs_bandwidth() was not called */
	अगर (!cfs_b->throttled_cfs_rq.next)
		वापस;

	hrसमयr_cancel(&cfs_b->period_समयr);
	hrसमयr_cancel(&cfs_b->slack_समयr);
पूर्ण

/*
 * Both these CPU hotplug callbacks race against unरेजिस्टर_fair_sched_group()
 *
 * The race is harmless, since modअगरying bandwidth settings of unhooked group
 * bits करोesn't करो much.
 */

/* cpu online callback */
अटल व्योम __maybe_unused update_runसमय_enabled(काष्ठा rq *rq)
अणु
	काष्ठा task_group *tg;

	lockdep_निश्चित_held(&rq->lock);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(tg, &task_groups, list) अणु
		काष्ठा cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;
		काष्ठा cfs_rq *cfs_rq = tg->cfs_rq[cpu_of(rq)];

		raw_spin_lock(&cfs_b->lock);
		cfs_rq->runसमय_enabled = cfs_b->quota != RUNTIME_INF;
		raw_spin_unlock(&cfs_b->lock);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* cpu offline callback */
अटल व्योम __maybe_unused unthrottle_offline_cfs_rqs(काष्ठा rq *rq)
अणु
	काष्ठा task_group *tg;

	lockdep_निश्चित_held(&rq->lock);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(tg, &task_groups, list) अणु
		काष्ठा cfs_rq *cfs_rq = tg->cfs_rq[cpu_of(rq)];

		अगर (!cfs_rq->runसमय_enabled)
			जारी;

		/*
		 * घड़ी_प्रकारask is not advancing so we just need to make sure
		 * there's some valid quota amount
		 */
		cfs_rq->runसमय_reमुख्यing = 1;
		/*
		 * Offline rq is schedulable till CPU is completely disabled
		 * in take_cpu_करोwn(), so we prevent new cfs throttling here.
		 */
		cfs_rq->runसमय_enabled = 0;

		अगर (cfs_rq_throttled(cfs_rq))
			unthrottle_cfs_rq(cfs_rq);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

#अन्यथा /* CONFIG_CFS_BANDWIDTH */

अटल अंतरभूत bool cfs_bandwidth_used(व्योम)
अणु
	वापस false;
पूर्ण

अटल व्योम account_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq, u64 delta_exec) अणुपूर्ण
अटल bool check_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq) अणु वापस false; पूर्ण
अटल व्योम check_enqueue_throttle(काष्ठा cfs_rq *cfs_rq) अणुपूर्ण
अटल अंतरभूत व्योम sync_throttle(काष्ठा task_group *tg, पूर्णांक cpu) अणुपूर्ण
अटल __always_अंतरभूत व्योम वापस_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq) अणुपूर्ण

अटल अंतरभूत पूर्णांक cfs_rq_throttled(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक throttled_hierarchy(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक throttled_lb_pair(काष्ठा task_group *tg,
				    पूर्णांक src_cpu, पूर्णांक dest_cpu)
अणु
	वापस 0;
पूर्ण

व्योम init_cfs_bandwidth(काष्ठा cfs_bandwidth *cfs_b) अणुपूर्ण

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
अटल व्योम init_cfs_rq_runसमय(काष्ठा cfs_rq *cfs_rq) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा cfs_bandwidth *tg_cfs_bandwidth(काष्ठा task_group *tg)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम destroy_cfs_bandwidth(काष्ठा cfs_bandwidth *cfs_b) अणुपूर्ण
अटल अंतरभूत व्योम update_runसमय_enabled(काष्ठा rq *rq) अणुपूर्ण
अटल अंतरभूत व्योम unthrottle_offline_cfs_rqs(काष्ठा rq *rq) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_CFS_BANDWIDTH */

/**************************************************
 * CFS operations on tasks:
 */

#अगर_घोषित CONFIG_SCHED_HRTICK
अटल व्योम hrtick_start_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_entity *se = &p->se;
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);

	SCHED_WARN_ON(task_rq(p) != rq);

	अगर (rq->cfs.h_nr_running > 1) अणु
		u64 slice = sched_slice(cfs_rq, se);
		u64 ran = se->sum_exec_runसमय - se->prev_sum_exec_runसमय;
		s64 delta = slice - ran;

		अगर (delta < 0) अणु
			अगर (task_current(rq, p))
				resched_curr(rq);
			वापस;
		पूर्ण
		hrtick_start(rq, delta);
	पूर्ण
पूर्ण

/*
 * called from enqueue/dequeue and updates the hrtick when the
 * current task is from our class and nr_running is low enough
 * to matter.
 */
अटल व्योम hrtick_update(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *curr = rq->curr;

	अगर (!hrtick_enabled_fair(rq) || curr->sched_class != &fair_sched_class)
		वापस;

	अगर (cfs_rq_of(&curr->se)->nr_running < sched_nr_latency)
		hrtick_start_fair(rq, curr);
पूर्ण
#अन्यथा /* !CONFIG_SCHED_HRTICK */
अटल अंतरभूत व्योम
hrtick_start_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
पूर्ण

अटल अंतरभूत व्योम hrtick_update(काष्ठा rq *rq)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत अचिन्हित दीर्घ cpu_util(पूर्णांक cpu);

अटल अंतरभूत bool cpu_overutilized(पूर्णांक cpu)
अणु
	वापस !fits_capacity(cpu_util(cpu), capacity_of(cpu));
पूर्ण

अटल अंतरभूत व्योम update_overutilized_status(काष्ठा rq *rq)
अणु
	अगर (!READ_ONCE(rq->rd->overutilized) && cpu_overutilized(rq->cpu)) अणु
		WRITE_ONCE(rq->rd->overutilized, SG_OVERUTILIZED);
		trace_sched_overutilized_tp(rq->rd, SG_OVERUTILIZED);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम update_overutilized_status(काष्ठा rq *rq) अणु पूर्ण
#पूर्ण_अगर

/* Runqueue only has SCHED_IDLE tasks enqueued */
अटल पूर्णांक sched_idle_rq(काष्ठा rq *rq)
अणु
	वापस unlikely(rq->nr_running == rq->cfs.idle_h_nr_running &&
			rq->nr_running);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक sched_idle_cpu(पूर्णांक cpu)
अणु
	वापस sched_idle_rq(cpu_rq(cpu));
पूर्ण
#पूर्ण_अगर

/*
 * The enqueue_task method is called beक्रमe nr_running is
 * increased. Here we update the fair scheduling stats and
 * then put the task पूर्णांकo the rbtree:
 */
अटल व्योम
enqueue_task_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	काष्ठा cfs_rq *cfs_rq;
	काष्ठा sched_entity *se = &p->se;
	पूर्णांक idle_h_nr_running = task_has_idle_policy(p);
	पूर्णांक task_new = !(flags & ENQUEUE_WAKEUP);

	/*
	 * The code below (indirectly) updates schedutil which looks at
	 * the cfs_rq utilization to select a frequency.
	 * Let's add the task's estimated utilization to the cfs_rq's
	 * estimated utilization, beक्रमe we update schedutil.
	 */
	util_est_enqueue(&rq->cfs, p);

	/*
	 * If in_ioरुको is set, the code below may not trigger any cpufreq
	 * utilization updates, so करो it here explicitly with the IOWAIT flag
	 * passed.
	 */
	अगर (p->in_ioरुको)
		cpufreq_update_util(rq, SCHED_CPUFREQ_IOWAIT);

	क्रम_each_sched_entity(se) अणु
		अगर (se->on_rq)
			अवरोध;
		cfs_rq = cfs_rq_of(se);
		enqueue_entity(cfs_rq, se, flags);

		cfs_rq->h_nr_running++;
		cfs_rq->idle_h_nr_running += idle_h_nr_running;

		/* end evaluation on encountering a throttled cfs_rq */
		अगर (cfs_rq_throttled(cfs_rq))
			जाओ enqueue_throttle;

		flags = ENQUEUE_WAKEUP;
	पूर्ण

	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);

		update_load_avg(cfs_rq, se, UPDATE_TG);
		se_update_runnable(se);
		update_cfs_group(se);

		cfs_rq->h_nr_running++;
		cfs_rq->idle_h_nr_running += idle_h_nr_running;

		/* end evaluation on encountering a throttled cfs_rq */
		अगर (cfs_rq_throttled(cfs_rq))
			जाओ enqueue_throttle;

               /*
                * One parent has been throttled and cfs_rq हटाओd from the
                * list. Add it back to not अवरोध the leaf list.
                */
               अगर (throttled_hierarchy(cfs_rq))
                       list_add_leaf_cfs_rq(cfs_rq);
	पूर्ण

	/* At this poपूर्णांक se is शून्य and we are at root level*/
	add_nr_running(rq, 1);

	/*
	 * Since new tasks are asचिन्हित an initial util_avg equal to
	 * half of the spare capacity of their CPU, tiny tasks have the
	 * ability to cross the overutilized threshold, which will
	 * result in the load balancer ruining all the task placement
	 * करोne by EAS. As a way to mitigate that effect, करो not account
	 * क्रम the first enqueue operation of new tasks during the
	 * overutilized flag detection.
	 *
	 * A better way of solving this problem would be to रुको क्रम
	 * the PELT संकेतs of tasks to converge beक्रमe taking them
	 * पूर्णांकo account, but that is not straightक्रमward to implement,
	 * and the following generally works well enough in practice.
	 */
	अगर (!task_new)
		update_overutilized_status(rq);

enqueue_throttle:
	अगर (cfs_bandwidth_used()) अणु
		/*
		 * When bandwidth control is enabled; the cfs_rq_throttled()
		 * अवरोधs in the above iteration can result in incomplete
		 * leaf list मुख्यtenance, resulting in triggering the निश्चितion
		 * below.
		 */
		क्रम_each_sched_entity(se) अणु
			cfs_rq = cfs_rq_of(se);

			अगर (list_add_leaf_cfs_rq(cfs_rq))
				अवरोध;
		पूर्ण
	पूर्ण

	निश्चित_list_leaf_cfs_rq(rq);

	hrtick_update(rq);
पूर्ण

अटल व्योम set_next_buddy(काष्ठा sched_entity *se);

/*
 * The dequeue_task method is called beक्रमe nr_running is
 * decreased. We हटाओ the task from the rbtree and
 * update the fair scheduling stats:
 */
अटल व्योम dequeue_task_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	काष्ठा cfs_rq *cfs_rq;
	काष्ठा sched_entity *se = &p->se;
	पूर्णांक task_sleep = flags & DEQUEUE_SLEEP;
	पूर्णांक idle_h_nr_running = task_has_idle_policy(p);
	bool was_sched_idle = sched_idle_rq(rq);

	util_est_dequeue(&rq->cfs, p);

	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);
		dequeue_entity(cfs_rq, se, flags);

		cfs_rq->h_nr_running--;
		cfs_rq->idle_h_nr_running -= idle_h_nr_running;

		/* end evaluation on encountering a throttled cfs_rq */
		अगर (cfs_rq_throttled(cfs_rq))
			जाओ dequeue_throttle;

		/* Don't dequeue parent अगर it has other entities besides us */
		अगर (cfs_rq->load.weight) अणु
			/* Aव्योम re-evaluating load क्रम this entity: */
			se = parent_entity(se);
			/*
			 * Bias pick_next to pick a task from this cfs_rq, as
			 * p is sleeping when it is within its sched_slice.
			 */
			अगर (task_sleep && se && !throttled_hierarchy(cfs_rq))
				set_next_buddy(se);
			अवरोध;
		पूर्ण
		flags |= DEQUEUE_SLEEP;
	पूर्ण

	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);

		update_load_avg(cfs_rq, se, UPDATE_TG);
		se_update_runnable(se);
		update_cfs_group(se);

		cfs_rq->h_nr_running--;
		cfs_rq->idle_h_nr_running -= idle_h_nr_running;

		/* end evaluation on encountering a throttled cfs_rq */
		अगर (cfs_rq_throttled(cfs_rq))
			जाओ dequeue_throttle;

	पूर्ण

	/* At this poपूर्णांक se is शून्य and we are at root level*/
	sub_nr_running(rq, 1);

	/* balance early to pull high priority tasks */
	अगर (unlikely(!was_sched_idle && sched_idle_rq(rq)))
		rq->next_balance = jअगरfies;

dequeue_throttle:
	util_est_update(&rq->cfs, p, task_sleep);
	hrtick_update(rq);
पूर्ण

#अगर_घोषित CONFIG_SMP

/* Working cpumask क्रम: load_balance, load_balance_newidle. */
DEFINE_PER_CPU(cpumask_var_t, load_balance_mask);
DEFINE_PER_CPU(cpumask_var_t, select_idle_mask);

#अगर_घोषित CONFIG_NO_HZ_COMMON

अटल काष्ठा अणु
	cpumask_var_t idle_cpus_mask;
	atomic_t nr_cpus;
	पूर्णांक has_blocked;		/* Idle CPUS has blocked load */
	अचिन्हित दीर्घ next_balance;     /* in jअगरfy units */
	अचिन्हित दीर्घ next_blocked;	/* Next update of blocked load in jअगरfies */
पूर्ण nohz ____cacheline_aligned;

#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

अटल अचिन्हित दीर्घ cpu_load(काष्ठा rq *rq)
अणु
	वापस cfs_rq_load_avg(&rq->cfs);
पूर्ण

/*
 * cpu_load_without - compute CPU load without any contributions from *p
 * @cpu: the CPU which load is requested
 * @p: the task which load should be discounted
 *
 * The load of a CPU is defined by the load of tasks currently enqueued on that
 * CPU as well as tasks which are currently sleeping after an execution on that
 * CPU.
 *
 * This method वापसs the load of the specअगरied CPU by discounting the load of
 * the specअगरied task, whenever the task is currently contributing to the CPU
 * load.
 */
अटल अचिन्हित दीर्घ cpu_load_without(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा cfs_rq *cfs_rq;
	अचिन्हित पूर्णांक load;

	/* Task has no contribution or is new */
	अगर (cpu_of(rq) != task_cpu(p) || !READ_ONCE(p->se.avg.last_update_समय))
		वापस cpu_load(rq);

	cfs_rq = &rq->cfs;
	load = READ_ONCE(cfs_rq->avg.load_avg);

	/* Discount task's util from CPU's util */
	lsub_positive(&load, task_h_load(p));

	वापस load;
पूर्ण

अटल अचिन्हित दीर्घ cpu_runnable(काष्ठा rq *rq)
अणु
	वापस cfs_rq_runnable_avg(&rq->cfs);
पूर्ण

अटल अचिन्हित दीर्घ cpu_runnable_without(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा cfs_rq *cfs_rq;
	अचिन्हित पूर्णांक runnable;

	/* Task has no contribution or is new */
	अगर (cpu_of(rq) != task_cpu(p) || !READ_ONCE(p->se.avg.last_update_समय))
		वापस cpu_runnable(rq);

	cfs_rq = &rq->cfs;
	runnable = READ_ONCE(cfs_rq->avg.runnable_avg);

	/* Discount task's runnable from CPU's runnable */
	lsub_positive(&runnable, p->se.avg.runnable_avg);

	वापस runnable;
पूर्ण

अटल अचिन्हित दीर्घ capacity_of(पूर्णांक cpu)
अणु
	वापस cpu_rq(cpu)->cpu_capacity;
पूर्ण

अटल व्योम record_wakee(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * Only decay a single समय; tasks that have less then 1 wakeup per
	 * jअगरfy will not have built up many flips.
	 */
	अगर (समय_after(jअगरfies, current->wakee_flip_decay_ts + HZ)) अणु
		current->wakee_flips >>= 1;
		current->wakee_flip_decay_ts = jअगरfies;
	पूर्ण

	अगर (current->last_wakee != p) अणु
		current->last_wakee = p;
		current->wakee_flips++;
	पूर्ण
पूर्ण

/*
 * Detect M:N waker/wakee relationships via a चयनing-frequency heuristic.
 *
 * A waker of many should wake a dअगरferent task than the one last awakened
 * at a frequency roughly N बार higher than one of its wakees.
 *
 * In order to determine whether we should let the load spपढ़ो vs consolidating
 * to shared cache, we look क्रम a minimum 'flip' frequency of llc_size in one
 * partner, and a factor of lls_size higher frequency in the other.
 *
 * With both conditions met, we can be relatively sure that the relationship is
 * non-monogamous, with partner count exceeding socket size.
 *
 * Waker/wakee being client/server, worker/dispatcher, पूर्णांकerrupt source or
 * whatever is irrelevant, spपढ़ो criteria is apparent partner count exceeds
 * socket size.
 */
अटल पूर्णांक wake_wide(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक master = current->wakee_flips;
	अचिन्हित पूर्णांक slave = p->wakee_flips;
	पूर्णांक factor = __this_cpu_पढ़ो(sd_llc_size);

	अगर (master < slave)
		swap(master, slave);
	अगर (slave < factor || master < slave * factor)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * The purpose of wake_affine() is to quickly determine on which CPU we can run
 * soonest. For the purpose of speed we only consider the waking and previous
 * CPU.
 *
 * wake_affine_idle() - only considers 'now', it check अगर the waking CPU is
 *			cache-affine and is (or	will be) idle.
 *
 * wake_affine_weight() - considers the weight to reflect the average
 *			  scheduling latency of the CPUs. This seems to work
 *			  क्रम the overloaded हाल.
 */
अटल पूर्णांक
wake_affine_idle(पूर्णांक this_cpu, पूर्णांक prev_cpu, पूर्णांक sync)
अणु
	/*
	 * If this_cpu is idle, it implies the wakeup is from पूर्णांकerrupt
	 * context. Only allow the move अगर cache is shared. Otherwise an
	 * पूर्णांकerrupt पूर्णांकensive workload could क्रमce all tasks onto one
	 * node depending on the IO topology or IRQ affinity settings.
	 *
	 * If the prev_cpu is idle and cache affine then aव्योम a migration.
	 * There is no guarantee that the cache hot data from an पूर्णांकerrupt
	 * is more important than cache hot data on the prev_cpu and from
	 * a cpufreq perspective, it's better to have higher utilisation
	 * on one CPU.
	 */
	अगर (available_idle_cpu(this_cpu) && cpus_share_cache(this_cpu, prev_cpu))
		वापस available_idle_cpu(prev_cpu) ? prev_cpu : this_cpu;

	अगर (sync && cpu_rq(this_cpu)->nr_running == 1)
		वापस this_cpu;

	अगर (available_idle_cpu(prev_cpu))
		वापस prev_cpu;

	वापस nr_cpumask_bits;
पूर्ण

अटल पूर्णांक
wake_affine_weight(काष्ठा sched_करोमुख्य *sd, काष्ठा task_काष्ठा *p,
		   पूर्णांक this_cpu, पूर्णांक prev_cpu, पूर्णांक sync)
अणु
	s64 this_eff_load, prev_eff_load;
	अचिन्हित दीर्घ task_load;

	this_eff_load = cpu_load(cpu_rq(this_cpu));

	अगर (sync) अणु
		अचिन्हित दीर्घ current_load = task_h_load(current);

		अगर (current_load > this_eff_load)
			वापस this_cpu;

		this_eff_load -= current_load;
	पूर्ण

	task_load = task_h_load(p);

	this_eff_load += task_load;
	अगर (sched_feat(WA_BIAS))
		this_eff_load *= 100;
	this_eff_load *= capacity_of(prev_cpu);

	prev_eff_load = cpu_load(cpu_rq(prev_cpu));
	prev_eff_load -= task_load;
	अगर (sched_feat(WA_BIAS))
		prev_eff_load *= 100 + (sd->imbalance_pct - 100) / 2;
	prev_eff_load *= capacity_of(this_cpu);

	/*
	 * If sync, adjust the weight of prev_eff_load such that अगर
	 * prev_eff == this_eff that select_idle_sibling() will consider
	 * stacking the wakee on top of the waker अगर no other CPU is
	 * idle.
	 */
	अगर (sync)
		prev_eff_load += 1;

	वापस this_eff_load < prev_eff_load ? this_cpu : nr_cpumask_bits;
पूर्ण

अटल पूर्णांक wake_affine(काष्ठा sched_करोमुख्य *sd, काष्ठा task_काष्ठा *p,
		       पूर्णांक this_cpu, पूर्णांक prev_cpu, पूर्णांक sync)
अणु
	पूर्णांक target = nr_cpumask_bits;

	अगर (sched_feat(WA_IDLE))
		target = wake_affine_idle(this_cpu, prev_cpu, sync);

	अगर (sched_feat(WA_WEIGHT) && target == nr_cpumask_bits)
		target = wake_affine_weight(sd, p, this_cpu, prev_cpu, sync);

	schedstat_inc(p->se.statistics.nr_wakeups_affine_attempts);
	अगर (target == nr_cpumask_bits)
		वापस prev_cpu;

	schedstat_inc(sd->ttwu_move_affine);
	schedstat_inc(p->se.statistics.nr_wakeups_affine);
	वापस target;
पूर्ण

अटल काष्ठा sched_group *
find_idlest_group(काष्ठा sched_करोमुख्य *sd, काष्ठा task_काष्ठा *p, पूर्णांक this_cpu);

/*
 * find_idlest_group_cpu - find the idlest CPU among the CPUs in the group.
 */
अटल पूर्णांक
find_idlest_group_cpu(काष्ठा sched_group *group, काष्ठा task_काष्ठा *p, पूर्णांक this_cpu)
अणु
	अचिन्हित दीर्घ load, min_load = अच_दीर्घ_उच्च;
	अचिन्हित पूर्णांक min_निकास_latency = अच_पूर्णांक_उच्च;
	u64 latest_idle_बारtamp = 0;
	पूर्णांक least_loaded_cpu = this_cpu;
	पूर्णांक shallowest_idle_cpu = -1;
	पूर्णांक i;

	/* Check अगर we have any choice: */
	अगर (group->group_weight == 1)
		वापस cpumask_first(sched_group_span(group));

	/* Traverse only the allowed CPUs */
	क्रम_each_cpu_and(i, sched_group_span(group), p->cpus_ptr) अणु
		अगर (sched_idle_cpu(i))
			वापस i;

		अगर (available_idle_cpu(i)) अणु
			काष्ठा rq *rq = cpu_rq(i);
			काष्ठा cpuidle_state *idle = idle_get_state(rq);
			अगर (idle && idle->निकास_latency < min_निकास_latency) अणु
				/*
				 * We give priority to a CPU whose idle state
				 * has the smallest निकास latency irrespective
				 * of any idle बारtamp.
				 */
				min_निकास_latency = idle->निकास_latency;
				latest_idle_बारtamp = rq->idle_stamp;
				shallowest_idle_cpu = i;
			पूर्ण अन्यथा अगर ((!idle || idle->निकास_latency == min_निकास_latency) &&
				   rq->idle_stamp > latest_idle_बारtamp) अणु
				/*
				 * If equal or no active idle state, then
				 * the most recently idled CPU might have
				 * a warmer cache.
				 */
				latest_idle_बारtamp = rq->idle_stamp;
				shallowest_idle_cpu = i;
			पूर्ण
		पूर्ण अन्यथा अगर (shallowest_idle_cpu == -1) अणु
			load = cpu_load(cpu_rq(i));
			अगर (load < min_load) अणु
				min_load = load;
				least_loaded_cpu = i;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस shallowest_idle_cpu != -1 ? shallowest_idle_cpu : least_loaded_cpu;
पूर्ण

अटल अंतरभूत पूर्णांक find_idlest_cpu(काष्ठा sched_करोमुख्य *sd, काष्ठा task_काष्ठा *p,
				  पूर्णांक cpu, पूर्णांक prev_cpu, पूर्णांक sd_flag)
अणु
	पूर्णांक new_cpu = cpu;

	अगर (!cpumask_पूर्णांकersects(sched_करोमुख्य_span(sd), p->cpus_ptr))
		वापस prev_cpu;

	/*
	 * We need task's util क्रम cpu_util_without, sync it up to
	 * prev_cpu's last_update_समय.
	 */
	अगर (!(sd_flag & SD_BALANCE_FORK))
		sync_entity_load_avg(&p->se);

	जबतक (sd) अणु
		काष्ठा sched_group *group;
		काष्ठा sched_करोमुख्य *पंचांगp;
		पूर्णांक weight;

		अगर (!(sd->flags & sd_flag)) अणु
			sd = sd->child;
			जारी;
		पूर्ण

		group = find_idlest_group(sd, p, cpu);
		अगर (!group) अणु
			sd = sd->child;
			जारी;
		पूर्ण

		new_cpu = find_idlest_group_cpu(group, p, cpu);
		अगर (new_cpu == cpu) अणु
			/* Now try balancing at a lower करोमुख्य level of 'cpu': */
			sd = sd->child;
			जारी;
		पूर्ण

		/* Now try balancing at a lower करोमुख्य level of 'new_cpu': */
		cpu = new_cpu;
		weight = sd->span_weight;
		sd = शून्य;
		क्रम_each_करोमुख्य(cpu, पंचांगp) अणु
			अगर (weight <= पंचांगp->span_weight)
				अवरोध;
			अगर (पंचांगp->flags & sd_flag)
				sd = पंचांगp;
		पूर्ण
	पूर्ण

	वापस new_cpu;
पूर्ण

अटल अंतरभूत पूर्णांक __select_idle_cpu(पूर्णांक cpu)
अणु
	अगर (available_idle_cpu(cpu) || sched_idle_cpu(cpu))
		वापस cpu;

	वापस -1;
पूर्ण

#अगर_घोषित CONFIG_SCHED_SMT
DEFINE_STATIC_KEY_FALSE(sched_smt_present);
EXPORT_SYMBOL_GPL(sched_smt_present);

अटल अंतरभूत व्योम set_idle_cores(पूर्णांक cpu, पूर्णांक val)
अणु
	काष्ठा sched_करोमुख्य_shared *sds;

	sds = rcu_dereference(per_cpu(sd_llc_shared, cpu));
	अगर (sds)
		WRITE_ONCE(sds->has_idle_cores, val);
पूर्ण

अटल अंतरभूत bool test_idle_cores(पूर्णांक cpu, bool def)
अणु
	काष्ठा sched_करोमुख्य_shared *sds;

	sds = rcu_dereference(per_cpu(sd_llc_shared, cpu));
	अगर (sds)
		वापस READ_ONCE(sds->has_idle_cores);

	वापस def;
पूर्ण

/*
 * Scans the local SMT mask to see अगर the entire core is idle, and records this
 * inक्रमmation in sd_llc_shared->has_idle_cores.
 *
 * Since SMT siblings share all cache levels, inspecting this limited remote
 * state should be fairly cheap.
 */
व्योम __update_idle_core(काष्ठा rq *rq)
अणु
	पूर्णांक core = cpu_of(rq);
	पूर्णांक cpu;

	rcu_पढ़ो_lock();
	अगर (test_idle_cores(core, true))
		जाओ unlock;

	क्रम_each_cpu(cpu, cpu_smt_mask(core)) अणु
		अगर (cpu == core)
			जारी;

		अगर (!available_idle_cpu(cpu))
			जाओ unlock;
	पूर्ण

	set_idle_cores(core, 1);
unlock:
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Scan the entire LLC करोमुख्य क्रम idle cores; this dynamically चयनes off अगर
 * there are no idle cores left in the प्रणाली; tracked through
 * sd_llc->shared->has_idle_cores and enabled through update_idle_core() above.
 */
अटल पूर्णांक select_idle_core(काष्ठा task_काष्ठा *p, पूर्णांक core, काष्ठा cpumask *cpus, पूर्णांक *idle_cpu)
अणु
	bool idle = true;
	पूर्णांक cpu;

	अगर (!अटल_branch_likely(&sched_smt_present))
		वापस __select_idle_cpu(core);

	क्रम_each_cpu(cpu, cpu_smt_mask(core)) अणु
		अगर (!available_idle_cpu(cpu)) अणु
			idle = false;
			अगर (*idle_cpu == -1) अणु
				अगर (sched_idle_cpu(cpu) && cpumask_test_cpu(cpu, p->cpus_ptr)) अणु
					*idle_cpu = cpu;
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (*idle_cpu == -1 && cpumask_test_cpu(cpu, p->cpus_ptr))
			*idle_cpu = cpu;
	पूर्ण

	अगर (idle)
		वापस core;

	cpumask_andnot(cpus, cpus, cpu_smt_mask(core));
	वापस -1;
पूर्ण

/*
 * Scan the local SMT mask क्रम idle CPUs.
 */
अटल पूर्णांक select_idle_smt(काष्ठा task_काष्ठा *p, काष्ठा sched_करोमुख्य *sd, पूर्णांक target)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, cpu_smt_mask(target)) अणु
		अगर (!cpumask_test_cpu(cpu, p->cpus_ptr) ||
		    !cpumask_test_cpu(cpu, sched_करोमुख्य_span(sd)))
			जारी;
		अगर (available_idle_cpu(cpu) || sched_idle_cpu(cpu))
			वापस cpu;
	पूर्ण

	वापस -1;
पूर्ण

#अन्यथा /* CONFIG_SCHED_SMT */

अटल अंतरभूत व्योम set_idle_cores(पूर्णांक cpu, पूर्णांक val)
अणु
पूर्ण

अटल अंतरभूत bool test_idle_cores(पूर्णांक cpu, bool def)
अणु
	वापस def;
पूर्ण

अटल अंतरभूत पूर्णांक select_idle_core(काष्ठा task_काष्ठा *p, पूर्णांक core, काष्ठा cpumask *cpus, पूर्णांक *idle_cpu)
अणु
	वापस __select_idle_cpu(core);
पूर्ण

अटल अंतरभूत पूर्णांक select_idle_smt(काष्ठा task_काष्ठा *p, काष्ठा sched_करोमुख्य *sd, पूर्णांक target)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर /* CONFIG_SCHED_SMT */

/*
 * Scan the LLC करोमुख्य क्रम idle CPUs; this is dynamically regulated by
 * comparing the average scan cost (tracked in sd->avg_scan_cost) against the
 * average idle समय क्रम this rq (as found in rq->avg_idle).
 */
अटल पूर्णांक select_idle_cpu(काष्ठा task_काष्ठा *p, काष्ठा sched_करोमुख्य *sd, bool has_idle_core, पूर्णांक target)
अणु
	काष्ठा cpumask *cpus = this_cpu_cpumask_var_ptr(select_idle_mask);
	पूर्णांक i, cpu, idle_cpu = -1, nr = पूर्णांक_उच्च;
	पूर्णांक this = smp_processor_id();
	काष्ठा sched_करोमुख्य *this_sd;
	u64 समय;

	this_sd = rcu_dereference(*this_cpu_ptr(&sd_llc));
	अगर (!this_sd)
		वापस -1;

	cpumask_and(cpus, sched_करोमुख्य_span(sd), p->cpus_ptr);

	अगर (sched_feat(SIS_PROP) && !has_idle_core) अणु
		u64 avg_cost, avg_idle, span_avg;

		/*
		 * Due to large variance we need a large fuzz factor;
		 * hackbench in particularly is sensitive here.
		 */
		avg_idle = this_rq()->avg_idle / 512;
		avg_cost = this_sd->avg_scan_cost + 1;

		span_avg = sd->span_weight * avg_idle;
		अगर (span_avg > 4*avg_cost)
			nr = भाग_u64(span_avg, avg_cost);
		अन्यथा
			nr = 4;

		समय = cpu_घड़ी(this);
	पूर्ण

	क्रम_each_cpu_wrap(cpu, cpus, target) अणु
		अगर (has_idle_core) अणु
			i = select_idle_core(p, cpu, cpus, &idle_cpu);
			अगर ((अचिन्हित पूर्णांक)i < nr_cpumask_bits)
				वापस i;

		पूर्ण अन्यथा अणु
			अगर (!--nr)
				वापस -1;
			idle_cpu = __select_idle_cpu(cpu);
			अगर ((अचिन्हित पूर्णांक)idle_cpu < nr_cpumask_bits)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (has_idle_core)
		set_idle_cores(target, false);

	अगर (sched_feat(SIS_PROP) && !has_idle_core) अणु
		समय = cpu_घड़ी(this) - समय;
		update_avg(&this_sd->avg_scan_cost, समय);
	पूर्ण

	वापस idle_cpu;
पूर्ण

/*
 * Scan the asym_capacity करोमुख्य क्रम idle CPUs; pick the first idle one on which
 * the task fits. If no CPU is big enough, but there are idle ones, try to
 * maximize capacity.
 */
अटल पूर्णांक
select_idle_capacity(काष्ठा task_काष्ठा *p, काष्ठा sched_करोमुख्य *sd, पूर्णांक target)
अणु
	अचिन्हित दीर्घ task_util, best_cap = 0;
	पूर्णांक cpu, best_cpu = -1;
	काष्ठा cpumask *cpus;

	cpus = this_cpu_cpumask_var_ptr(select_idle_mask);
	cpumask_and(cpus, sched_करोमुख्य_span(sd), p->cpus_ptr);

	task_util = uclamp_task_util(p);

	क्रम_each_cpu_wrap(cpu, cpus, target) अणु
		अचिन्हित दीर्घ cpu_cap = capacity_of(cpu);

		अगर (!available_idle_cpu(cpu) && !sched_idle_cpu(cpu))
			जारी;
		अगर (fits_capacity(task_util, cpu_cap))
			वापस cpu;

		अगर (cpu_cap > best_cap) अणु
			best_cap = cpu_cap;
			best_cpu = cpu;
		पूर्ण
	पूर्ण

	वापस best_cpu;
पूर्ण

अटल अंतरभूत bool asym_fits_capacity(पूर्णांक task_util, पूर्णांक cpu)
अणु
	अगर (अटल_branch_unlikely(&sched_asym_cpucapacity))
		वापस fits_capacity(task_util, capacity_of(cpu));

	वापस true;
पूर्ण

/*
 * Try and locate an idle core/thपढ़ो in the LLC cache करोमुख्य.
 */
अटल पूर्णांक select_idle_sibling(काष्ठा task_काष्ठा *p, पूर्णांक prev, पूर्णांक target)
अणु
	bool has_idle_core = false;
	काष्ठा sched_करोमुख्य *sd;
	अचिन्हित दीर्घ task_util;
	पूर्णांक i, recent_used_cpu;

	/*
	 * On asymmetric प्रणाली, update task utilization because we will check
	 * that the task fits with cpu's capacity.
	 */
	अगर (अटल_branch_unlikely(&sched_asym_cpucapacity)) अणु
		sync_entity_load_avg(&p->se);
		task_util = uclamp_task_util(p);
	पूर्ण

	अगर ((available_idle_cpu(target) || sched_idle_cpu(target)) &&
	    asym_fits_capacity(task_util, target))
		वापस target;

	/*
	 * If the previous CPU is cache affine and idle, करोn't be stupid:
	 */
	अगर (prev != target && cpus_share_cache(prev, target) &&
	    (available_idle_cpu(prev) || sched_idle_cpu(prev)) &&
	    asym_fits_capacity(task_util, prev))
		वापस prev;

	/*
	 * Allow a per-cpu kthपढ़ो to stack with the wakee अगर the
	 * kworker thपढ़ो and the tasks previous CPUs are the same.
	 * The assumption is that the wakee queued work क्रम the
	 * per-cpu kthपढ़ो that is now complete and the wakeup is
	 * essentially a sync wakeup. An obvious example of this
	 * pattern is IO completions.
	 */
	अगर (is_per_cpu_kthपढ़ो(current) &&
	    prev == smp_processor_id() &&
	    this_rq()->nr_running <= 1) अणु
		वापस prev;
	पूर्ण

	/* Check a recently used CPU as a potential idle candidate: */
	recent_used_cpu = p->recent_used_cpu;
	अगर (recent_used_cpu != prev &&
	    recent_used_cpu != target &&
	    cpus_share_cache(recent_used_cpu, target) &&
	    (available_idle_cpu(recent_used_cpu) || sched_idle_cpu(recent_used_cpu)) &&
	    cpumask_test_cpu(p->recent_used_cpu, p->cpus_ptr) &&
	    asym_fits_capacity(task_util, recent_used_cpu)) अणु
		/*
		 * Replace recent_used_cpu with prev as it is a potential
		 * candidate क्रम the next wake:
		 */
		p->recent_used_cpu = prev;
		वापस recent_used_cpu;
	पूर्ण

	/*
	 * For asymmetric CPU capacity प्रणालीs, our करोमुख्य of पूर्णांकerest is
	 * sd_asym_cpucapacity rather than sd_llc.
	 */
	अगर (अटल_branch_unlikely(&sched_asym_cpucapacity)) अणु
		sd = rcu_dereference(per_cpu(sd_asym_cpucapacity, target));
		/*
		 * On an asymmetric CPU capacity प्रणाली where an exclusive
		 * cpuset defines a symmetric island (i.e. one unique
		 * capacity_orig value through the cpuset), the key will be set
		 * but the CPUs within that cpuset will not have a करोमुख्य with
		 * SD_ASYM_CPUCAPACITY. These should follow the usual symmetric
		 * capacity path.
		 */
		अगर (sd) अणु
			i = select_idle_capacity(p, sd, target);
			वापस ((अचिन्हित)i < nr_cpumask_bits) ? i : target;
		पूर्ण
	पूर्ण

	sd = rcu_dereference(per_cpu(sd_llc, target));
	अगर (!sd)
		वापस target;

	अगर (sched_smt_active()) अणु
		has_idle_core = test_idle_cores(target, false);

		अगर (!has_idle_core && cpus_share_cache(prev, target)) अणु
			i = select_idle_smt(p, sd, prev);
			अगर ((अचिन्हित पूर्णांक)i < nr_cpumask_bits)
				वापस i;
		पूर्ण
	पूर्ण

	i = select_idle_cpu(p, sd, has_idle_core, target);
	अगर ((अचिन्हित)i < nr_cpumask_bits)
		वापस i;

	वापस target;
पूर्ण

/**
 * cpu_util - Estimates the amount of capacity of a CPU used by CFS tasks.
 * @cpu: the CPU to get the utilization of
 *
 * The unit of the वापस value must be the one of capacity so we can compare
 * the utilization with the capacity of the CPU that is available क्रम CFS task
 * (ie cpu_capacity).
 *
 * cfs_rq.avg.util_avg is the sum of running समय of runnable tasks plus the
 * recent utilization of currently non-runnable tasks on a CPU. It represents
 * the amount of utilization of a CPU in the range [0..capacity_orig] where
 * capacity_orig is the cpu_capacity available at the highest frequency
 * (arch_scale_freq_capacity()).
 * The utilization of a CPU converges towards a sum equal to or less than the
 * current capacity (capacity_curr <= capacity_orig) of the CPU because it is
 * the running समय on this CPU scaled by capacity_curr.
 *
 * The estimated utilization of a CPU is defined to be the maximum between its
 * cfs_rq.avg.util_avg and the sum of the estimated utilization of the tasks
 * currently RUNNABLE on that CPU.
 * This allows to properly represent the expected utilization of a CPU which
 * has just got a big task running since a दीर्घ sleep period. At the same समय
 * however it preserves the benefits of the "blocked utilization" in
 * describing the potential क्रम other tasks waking up on the same CPU.
 *
 * Nevertheless, cfs_rq.avg.util_avg can be higher than capacity_curr or even
 * higher than capacity_orig because of unक्रमtunate rounding in
 * cfs.avg.util_avg or just after migrating tasks and new task wakeups until
 * the average stabilizes with the new running समय. We need to check that the
 * utilization stays within the range of [0..capacity_orig] and cap it अगर
 * necessary. Without utilization capping, a group could be seen as overloaded
 * (CPU0 utilization at 121% + CPU1 utilization at 80%) whereas CPU1 has 20% of
 * available capacity. We allow utilization to overshoot capacity_curr (but not
 * capacity_orig) as it useful क्रम predicting the capacity required after task
 * migrations (scheduler-driven DVFS).
 *
 * Return: the (estimated) utilization क्रम the specअगरied CPU
 */
अटल अंतरभूत अचिन्हित दीर्घ cpu_util(पूर्णांक cpu)
अणु
	काष्ठा cfs_rq *cfs_rq;
	अचिन्हित पूर्णांक util;

	cfs_rq = &cpu_rq(cpu)->cfs;
	util = READ_ONCE(cfs_rq->avg.util_avg);

	अगर (sched_feat(UTIL_EST))
		util = max(util, READ_ONCE(cfs_rq->avg.util_est.enqueued));

	वापस min_t(अचिन्हित दीर्घ, util, capacity_orig_of(cpu));
पूर्ण

/*
 * cpu_util_without: compute cpu utilization without any contributions from *p
 * @cpu: the CPU which utilization is requested
 * @p: the task which utilization should be discounted
 *
 * The utilization of a CPU is defined by the utilization of tasks currently
 * enqueued on that CPU as well as tasks which are currently sleeping after an
 * execution on that CPU.
 *
 * This method वापसs the utilization of the specअगरied CPU by discounting the
 * utilization of the specअगरied task, whenever the task is currently
 * contributing to the CPU utilization.
 */
अटल अचिन्हित दीर्घ cpu_util_without(पूर्णांक cpu, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा cfs_rq *cfs_rq;
	अचिन्हित पूर्णांक util;

	/* Task has no contribution or is new */
	अगर (cpu != task_cpu(p) || !READ_ONCE(p->se.avg.last_update_समय))
		वापस cpu_util(cpu);

	cfs_rq = &cpu_rq(cpu)->cfs;
	util = READ_ONCE(cfs_rq->avg.util_avg);

	/* Discount task's util from CPU's util */
	lsub_positive(&util, task_util(p));

	/*
	 * Covered हालs:
	 *
	 * a) अगर *p is the only task sleeping on this CPU, then:
	 *      cpu_util (== task_util) > util_est (== 0)
	 *    and thus we वापस:
	 *      cpu_util_without = (cpu_util - task_util) = 0
	 *
	 * b) अगर other tasks are SLEEPING on this CPU, which is now निकासing
	 *    IDLE, then:
	 *      cpu_util >= task_util
	 *      cpu_util > util_est (== 0)
	 *    and thus we discount *p's blocked utilization to वापस:
	 *      cpu_util_without = (cpu_util - task_util) >= 0
	 *
	 * c) अगर other tasks are RUNNABLE on that CPU and
	 *      util_est > cpu_util
	 *    then we use util_est since it वापसs a more restrictive
	 *    estimation of the spare capacity on that CPU, by just
	 *    considering the expected utilization of tasks alपढ़ोy
	 *    runnable on that CPU.
	 *
	 * Cases a) and b) are covered by the above code, जबतक हाल c) is
	 * covered by the following code when estimated utilization is
	 * enabled.
	 */
	अगर (sched_feat(UTIL_EST)) अणु
		अचिन्हित पूर्णांक estimated =
			READ_ONCE(cfs_rq->avg.util_est.enqueued);

		/*
		 * Despite the following checks we still have a small winकरोw
		 * क्रम a possible race, when an execl's select_task_rq_fair()
		 * races with LB's detach_task():
		 *
		 *   detach_task()
		 *     p->on_rq = TASK_ON_RQ_MIGRATING;
		 *     ---------------------------------- A
		 *     deactivate_task()                   \
		 *       dequeue_task()                     + RaceTime
		 *         util_est_dequeue()              /
		 *     ---------------------------------- B
		 *
		 * The additional check on "current == p" it's required to
		 * properly fix the execl regression and it helps in further
		 * reducing the chances क्रम the above race.
		 */
		अगर (unlikely(task_on_rq_queued(p) || current == p))
			lsub_positive(&estimated, _task_util_est(p));

		util = max(util, estimated);
	पूर्ण

	/*
	 * Utilization (estimated) can exceed the CPU capacity, thus let's
	 * clamp to the maximum CPU capacity to ensure consistency with
	 * the cpu_util call.
	 */
	वापस min_t(अचिन्हित दीर्घ, util, capacity_orig_of(cpu));
पूर्ण

/*
 * Predicts what cpu_util(@cpu) would वापस अगर @p was migrated (and enqueued)
 * to @dst_cpu.
 */
अटल अचिन्हित दीर्घ cpu_util_next(पूर्णांक cpu, काष्ठा task_काष्ठा *p, पूर्णांक dst_cpu)
अणु
	काष्ठा cfs_rq *cfs_rq = &cpu_rq(cpu)->cfs;
	अचिन्हित दीर्घ util_est, util = READ_ONCE(cfs_rq->avg.util_avg);

	/*
	 * If @p migrates from @cpu to another, हटाओ its contribution. Or,
	 * अगर @p migrates from another CPU to @cpu, add its contribution. In
	 * the other हालs, @cpu is not impacted by the migration, so the
	 * util_avg should alपढ़ोy be correct.
	 */
	अगर (task_cpu(p) == cpu && dst_cpu != cpu)
		lsub_positive(&util, task_util(p));
	अन्यथा अगर (task_cpu(p) != cpu && dst_cpu == cpu)
		util += task_util(p);

	अगर (sched_feat(UTIL_EST)) अणु
		util_est = READ_ONCE(cfs_rq->avg.util_est.enqueued);

		/*
		 * During wake-up, the task isn't enqueued yet and doesn't
		 * appear in the cfs_rq->avg.util_est.enqueued of any rq,
		 * so just add it (अगर needed) to "simulate" what will be
		 * cpu_util() after the task has been enqueued.
		 */
		अगर (dst_cpu == cpu)
			util_est += _task_util_est(p);

		util = max(util, util_est);
	पूर्ण

	वापस min(util, capacity_orig_of(cpu));
पूर्ण

/*
 * compute_energy(): Estimates the energy that @pd would consume अगर @p was
 * migrated to @dst_cpu. compute_energy() predicts what will be the utilization
 * landscape of @pd's CPUs after the task migration, and uses the Energy Model
 * to compute what would be the energy अगर we decided to actually migrate that
 * task.
 */
अटल दीर्घ
compute_energy(काष्ठा task_काष्ठा *p, पूर्णांक dst_cpu, काष्ठा perf_करोमुख्य *pd)
अणु
	काष्ठा cpumask *pd_mask = perf_करोमुख्य_span(pd);
	अचिन्हित दीर्घ cpu_cap = arch_scale_cpu_capacity(cpumask_first(pd_mask));
	अचिन्हित दीर्घ max_util = 0, sum_util = 0;
	पूर्णांक cpu;

	/*
	 * The capacity state of CPUs of the current rd can be driven by CPUs
	 * of another rd अगर they beदीर्घ to the same pd. So, account क्रम the
	 * utilization of these CPUs too by masking pd with cpu_online_mask
	 * instead of the rd span.
	 *
	 * If an entire pd is outside of the current rd, it will not appear in
	 * its pd list and will not be accounted by compute_energy().
	 */
	क्रम_each_cpu_and(cpu, pd_mask, cpu_online_mask) अणु
		अचिन्हित दीर्घ util_freq = cpu_util_next(cpu, p, dst_cpu);
		अचिन्हित दीर्घ cpu_util, util_running = util_freq;
		काष्ठा task_काष्ठा *tsk = शून्य;

		/*
		 * When @p is placed on @cpu:
		 *
		 * util_running = max(cpu_util, cpu_util_est) +
		 *		  max(task_util, _task_util_est)
		 *
		 * जबतक cpu_util_next is: max(cpu_util + task_util,
		 *			       cpu_util_est + _task_util_est)
		 */
		अगर (cpu == dst_cpu) अणु
			tsk = p;
			util_running =
				cpu_util_next(cpu, p, -1) + task_util_est(p);
		पूर्ण

		/*
		 * Busy समय computation: utilization clamping is not
		 * required since the ratio (sum_util / cpu_capacity)
		 * is alपढ़ोy enough to scale the EM reported घातer
		 * consumption at the (eventually clamped) cpu_capacity.
		 */
		sum_util += effective_cpu_util(cpu, util_running, cpu_cap,
					       ENERGY_UTIL, शून्य);

		/*
		 * Perक्रमmance करोमुख्य frequency: utilization clamping
		 * must be considered since it affects the selection
		 * of the perक्रमmance करोमुख्य frequency.
		 * NOTE: in हाल RT tasks are running, by शेष the
		 * FREQUENCY_UTIL's utilization can be max OPP.
		 */
		cpu_util = effective_cpu_util(cpu, util_freq, cpu_cap,
					      FREQUENCY_UTIL, tsk);
		max_util = max(max_util, cpu_util);
	पूर्ण

	वापस em_cpu_energy(pd->em_pd, max_util, sum_util);
पूर्ण

/*
 * find_energy_efficient_cpu(): Find most energy-efficient target CPU क्रम the
 * waking task. find_energy_efficient_cpu() looks क्रम the CPU with maximum
 * spare capacity in each perक्रमmance करोमुख्य and uses it as a potential
 * candidate to execute the task. Then, it uses the Energy Model to figure
 * out which of the CPU candidates is the most energy-efficient.
 *
 * The rationale क्रम this heuristic is as follows. In a perक्रमmance करोमुख्य,
 * all the most energy efficient CPU candidates (according to the Energy
 * Model) are those क्रम which we'll request a low frequency. When there are
 * several CPUs क्रम which the frequency request will be the same, we करोn't
 * have enough data to अवरोध the tie between them, because the Energy Model
 * only includes active घातer costs. With this model, अगर we assume that
 * frequency requests follow utilization (e.g. using schedutil), the CPU with
 * the maximum spare capacity in a perक्रमmance करोमुख्य is guaranteed to be among
 * the best candidates of the perक्रमmance करोमुख्य.
 *
 * In practice, it could be preferable from an energy standpoपूर्णांक to pack
 * small tasks on a CPU in order to let other CPUs go in deeper idle states,
 * but that could also hurt our chances to go cluster idle, and we have no
 * ways to tell with the current Energy Model अगर this is actually a good
 * idea or not. So, find_energy_efficient_cpu() basically favors
 * cluster-packing, and spपढ़ोing inside a cluster. That should at least be
 * a good thing क्रम latency, and this is consistent with the idea that most
 * of the energy savings of EAS come from the asymmetry of the प्रणाली, and
 * not so much from अवरोधing the tie between identical CPUs. That's also the
 * reason why EAS is enabled in the topology code only क्रम प्रणालीs where
 * SD_ASYM_CPUCAPACITY is set.
 *
 * NOTE: Forkees are not accepted in the energy-aware wake-up path because
 * they करोn't have any useful utilization data yet and it's not possible to
 * क्रमecast their impact on energy consumption. Consequently, they will be
 * placed by find_idlest_cpu() on the least loaded CPU, which might turn out
 * to be energy-inefficient in some use-हालs. The alternative would be to
 * bias new tasks towards specअगरic types of CPUs first, or to try to infer
 * their util_avg from the parent task, but those heuristics could hurt
 * other use-हालs too. So, until someone finds a better way to solve this,
 * let's keep things simple by re-using the existing slow path.
 */
अटल पूर्णांक find_energy_efficient_cpu(काष्ठा task_काष्ठा *p, पूर्णांक prev_cpu)
अणु
	अचिन्हित दीर्घ prev_delta = अच_दीर्घ_उच्च, best_delta = अच_दीर्घ_उच्च;
	काष्ठा root_करोमुख्य *rd = cpu_rq(smp_processor_id())->rd;
	अचिन्हित दीर्घ cpu_cap, util, base_energy = 0;
	पूर्णांक cpu, best_energy_cpu = prev_cpu;
	काष्ठा sched_करोमुख्य *sd;
	काष्ठा perf_करोमुख्य *pd;

	rcu_पढ़ो_lock();
	pd = rcu_dereference(rd->pd);
	अगर (!pd || READ_ONCE(rd->overutilized))
		जाओ fail;

	/*
	 * Energy-aware wake-up happens on the lowest sched_करोमुख्य starting
	 * from sd_asym_cpucapacity spanning over this_cpu and prev_cpu.
	 */
	sd = rcu_dereference(*this_cpu_ptr(&sd_asym_cpucapacity));
	जबतक (sd && !cpumask_test_cpu(prev_cpu, sched_करोमुख्य_span(sd)))
		sd = sd->parent;
	अगर (!sd)
		जाओ fail;

	sync_entity_load_avg(&p->se);
	अगर (!task_util_est(p))
		जाओ unlock;

	क्रम (; pd; pd = pd->next) अणु
		अचिन्हित दीर्घ cur_delta, spare_cap, max_spare_cap = 0;
		अचिन्हित दीर्घ base_energy_pd;
		पूर्णांक max_spare_cap_cpu = -1;

		/* Compute the 'base' energy of the pd, without @p */
		base_energy_pd = compute_energy(p, -1, pd);
		base_energy += base_energy_pd;

		क्रम_each_cpu_and(cpu, perf_करोमुख्य_span(pd), sched_करोमुख्य_span(sd)) अणु
			अगर (!cpumask_test_cpu(cpu, p->cpus_ptr))
				जारी;

			util = cpu_util_next(cpu, p, cpu);
			cpu_cap = capacity_of(cpu);
			spare_cap = cpu_cap;
			lsub_positive(&spare_cap, util);

			/*
			 * Skip CPUs that cannot satisfy the capacity request.
			 * IOW, placing the task there would make the CPU
			 * overutilized. Take uclamp पूर्णांकo account to see how
			 * much capacity we can get out of the CPU; this is
			 * aligned with sched_cpu_util().
			 */
			util = uclamp_rq_util_with(cpu_rq(cpu), util, p);
			अगर (!fits_capacity(util, cpu_cap))
				जारी;

			/* Always use prev_cpu as a candidate. */
			अगर (cpu == prev_cpu) अणु
				prev_delta = compute_energy(p, prev_cpu, pd);
				prev_delta -= base_energy_pd;
				best_delta = min(best_delta, prev_delta);
			पूर्ण

			/*
			 * Find the CPU with the maximum spare capacity in
			 * the perक्रमmance करोमुख्य
			 */
			अगर (spare_cap > max_spare_cap) अणु
				max_spare_cap = spare_cap;
				max_spare_cap_cpu = cpu;
			पूर्ण
		पूर्ण

		/* Evaluate the energy impact of using this CPU. */
		अगर (max_spare_cap_cpu >= 0 && max_spare_cap_cpu != prev_cpu) अणु
			cur_delta = compute_energy(p, max_spare_cap_cpu, pd);
			cur_delta -= base_energy_pd;
			अगर (cur_delta < best_delta) अणु
				best_delta = cur_delta;
				best_energy_cpu = max_spare_cap_cpu;
			पूर्ण
		पूर्ण
	पूर्ण
unlock:
	rcu_पढ़ो_unlock();

	/*
	 * Pick the best CPU अगर prev_cpu cannot be used, or अगर it saves at
	 * least 6% of the energy used by prev_cpu.
	 */
	अगर (prev_delta == अच_दीर्घ_उच्च)
		वापस best_energy_cpu;

	अगर ((prev_delta - best_delta) > ((prev_delta + base_energy) >> 4))
		वापस best_energy_cpu;

	वापस prev_cpu;

fail:
	rcu_पढ़ो_unlock();

	वापस -1;
पूर्ण

/*
 * select_task_rq_fair: Select target runqueue क्रम the waking task in करोमुख्यs
 * that have the relevant SD flag set. In practice, this is SD_BALANCE_WAKE,
 * SD_BALANCE_FORK, or SD_BALANCE_EXEC.
 *
 * Balances load by selecting the idlest CPU in the idlest group, or under
 * certain conditions an idle sibling CPU अगर the करोमुख्य has SD_WAKE_AFFINE set.
 *
 * Returns the target CPU number.
 *
 * preempt must be disabled.
 */
अटल पूर्णांक
select_task_rq_fair(काष्ठा task_काष्ठा *p, पूर्णांक prev_cpu, पूर्णांक wake_flags)
अणु
	पूर्णांक sync = (wake_flags & WF_SYNC) && !(current->flags & PF_EXITING);
	काष्ठा sched_करोमुख्य *पंचांगp, *sd = शून्य;
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक new_cpu = prev_cpu;
	पूर्णांक want_affine = 0;
	/* SD_flags and WF_flags share the first nibble */
	पूर्णांक sd_flag = wake_flags & 0xF;

	अगर (wake_flags & WF_TTWU) अणु
		record_wakee(p);

		अगर (sched_energy_enabled()) अणु
			new_cpu = find_energy_efficient_cpu(p, prev_cpu);
			अगर (new_cpu >= 0)
				वापस new_cpu;
			new_cpu = prev_cpu;
		पूर्ण

		want_affine = !wake_wide(p) && cpumask_test_cpu(cpu, p->cpus_ptr);
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम_each_करोमुख्य(cpu, पंचांगp) अणु
		/*
		 * If both 'cpu' and 'prev_cpu' are part of this करोमुख्य,
		 * cpu is a valid SD_WAKE_AFFINE target.
		 */
		अगर (want_affine && (पंचांगp->flags & SD_WAKE_AFFINE) &&
		    cpumask_test_cpu(prev_cpu, sched_करोमुख्य_span(पंचांगp))) अणु
			अगर (cpu != prev_cpu)
				new_cpu = wake_affine(पंचांगp, p, cpu, prev_cpu, sync);

			sd = शून्य; /* Prefer wake_affine over balance flags */
			अवरोध;
		पूर्ण

		अगर (पंचांगp->flags & sd_flag)
			sd = पंचांगp;
		अन्यथा अगर (!want_affine)
			अवरोध;
	पूर्ण

	अगर (unlikely(sd)) अणु
		/* Slow path */
		new_cpu = find_idlest_cpu(sd, p, cpu, prev_cpu, sd_flag);
	पूर्ण अन्यथा अगर (wake_flags & WF_TTWU) अणु /* XXX always ? */
		/* Fast path */
		new_cpu = select_idle_sibling(p, prev_cpu, new_cpu);

		अगर (want_affine)
			current->recent_used_cpu = cpu;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस new_cpu;
पूर्ण

अटल व्योम detach_entity_cfs_rq(काष्ठा sched_entity *se);

/*
 * Called immediately beक्रमe a task is migrated to a new CPU; task_cpu(p) and
 * cfs_rq_of(p) references at समय of call are still valid and identअगरy the
 * previous CPU. The caller guarantees p->pi_lock or task_rq(p)->lock is held.
 */
अटल व्योम migrate_task_rq_fair(काष्ठा task_काष्ठा *p, पूर्णांक new_cpu)
अणु
	/*
	 * As blocked tasks retain असलolute vrunसमय the migration needs to
	 * deal with this by subtracting the old and adding the new
	 * min_vrunसमय -- the latter is करोne by enqueue_entity() when placing
	 * the task on the new runqueue.
	 */
	अगर (p->state == TASK_WAKING) अणु
		काष्ठा sched_entity *se = &p->se;
		काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);
		u64 min_vrunसमय;

#अगर_अघोषित CONFIG_64BIT
		u64 min_vrunसमय_copy;

		करो अणु
			min_vrunसमय_copy = cfs_rq->min_vrunसमय_copy;
			smp_rmb();
			min_vrunसमय = cfs_rq->min_vrunसमय;
		पूर्ण जबतक (min_vrunसमय != min_vrunसमय_copy);
#अन्यथा
		min_vrunसमय = cfs_rq->min_vrunसमय;
#पूर्ण_अगर

		se->vrunसमय -= min_vrunसमय;
	पूर्ण

	अगर (p->on_rq == TASK_ON_RQ_MIGRATING) अणु
		/*
		 * In हाल of TASK_ON_RQ_MIGRATING we in fact hold the 'old'
		 * rq->lock and can modअगरy state directly.
		 */
		lockdep_निश्चित_held(&task_rq(p)->lock);
		detach_entity_cfs_rq(&p->se);

	पूर्ण अन्यथा अणु
		/*
		 * We are supposed to update the task to "current" समय, then
		 * its up to date and पढ़ोy to go to new CPU/cfs_rq. But we
		 * have dअगरficulty in getting what current समय is, so simply
		 * throw away the out-of-date समय. This will result in the
		 * wakee task is less decayed, but giving the wakee more load
		 * sounds not bad.
		 */
		हटाओ_entity_load_avg(&p->se);
	पूर्ण

	/* Tell new CPU we are migrated */
	p->se.avg.last_update_समय = 0;

	/* We have migrated, no दीर्घer consider this task hot */
	p->se.exec_start = 0;

	update_scan_period(p, new_cpu);
पूर्ण

अटल व्योम task_dead_fair(काष्ठा task_काष्ठा *p)
अणु
	हटाओ_entity_load_avg(&p->se);
पूर्ण

अटल पूर्णांक
balance_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा rq_flags *rf)
अणु
	अगर (rq->nr_running)
		वापस 1;

	वापस newidle_balance(rq, rf) != 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल अचिन्हित दीर्घ wakeup_gran(काष्ठा sched_entity *se)
अणु
	अचिन्हित दीर्घ gran = sysctl_sched_wakeup_granularity;

	/*
	 * Since its curr running now, convert the gran from real-समय
	 * to भव-समय in his units.
	 *
	 * By using 'se' instead of 'curr' we penalize light tasks, so
	 * they get preempted easier. That is, अगर 'se' < 'curr' then
	 * the resulting gran will be larger, thereक्रमe penalizing the
	 * lighter, अगर otoh 'se' > 'curr' then the resulting gran will
	 * be smaller, again penalizing the lighter task.
	 *
	 * This is especially important क्रम buddies when the lefपंचांगost
	 * task is higher priority than the buddy.
	 */
	वापस calc_delta_fair(gran, se);
पूर्ण

/*
 * Should 'se' preempt 'curr'.
 *
 *             |s1
 *        |s2
 *   |s3
 *         g
 *      |<--->|c
 *
 *  w(c, s1) = -1
 *  w(c, s2) =  0
 *  w(c, s3) =  1
 *
 */
अटल पूर्णांक
wakeup_preempt_entity(काष्ठा sched_entity *curr, काष्ठा sched_entity *se)
अणु
	s64 gran, vdअगरf = curr->vrunसमय - se->vrunसमय;

	अगर (vdअगरf <= 0)
		वापस -1;

	gran = wakeup_gran(se);
	अगर (vdअगरf > gran)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम set_last_buddy(काष्ठा sched_entity *se)
अणु
	अगर (entity_is_task(se) && unlikely(task_has_idle_policy(task_of(se))))
		वापस;

	क्रम_each_sched_entity(se) अणु
		अगर (SCHED_WARN_ON(!se->on_rq))
			वापस;
		cfs_rq_of(se)->last = se;
	पूर्ण
पूर्ण

अटल व्योम set_next_buddy(काष्ठा sched_entity *se)
अणु
	अगर (entity_is_task(se) && unlikely(task_has_idle_policy(task_of(se))))
		वापस;

	क्रम_each_sched_entity(se) अणु
		अगर (SCHED_WARN_ON(!se->on_rq))
			वापस;
		cfs_rq_of(se)->next = se;
	पूर्ण
पूर्ण

अटल व्योम set_skip_buddy(काष्ठा sched_entity *se)
अणु
	क्रम_each_sched_entity(se)
		cfs_rq_of(se)->skip = se;
पूर्ण

/*
 * Preempt the current task with a newly woken task अगर needed:
 */
अटल व्योम check_preempt_wakeup(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक wake_flags)
अणु
	काष्ठा task_काष्ठा *curr = rq->curr;
	काष्ठा sched_entity *se = &curr->se, *pse = &p->se;
	काष्ठा cfs_rq *cfs_rq = task_cfs_rq(curr);
	पूर्णांक scale = cfs_rq->nr_running >= sched_nr_latency;
	पूर्णांक next_buddy_marked = 0;

	अगर (unlikely(se == pse))
		वापस;

	/*
	 * This is possible from callers such as attach_tasks(), in which we
	 * unconditionally check_preempt_curr() after an enqueue (which may have
	 * lead to a throttle).  This both saves work and prevents false
	 * next-buddy nomination below.
	 */
	अगर (unlikely(throttled_hierarchy(cfs_rq_of(pse))))
		वापस;

	अगर (sched_feat(NEXT_BUDDY) && scale && !(wake_flags & WF_FORK)) अणु
		set_next_buddy(pse);
		next_buddy_marked = 1;
	पूर्ण

	/*
	 * We can come here with TIF_NEED_RESCHED alपढ़ोy set from new task
	 * wake up path.
	 *
	 * Note: this also catches the edge-हाल of curr being in a throttled
	 * group (e.g. via set_curr_task), since update_curr() (in the
	 * enqueue of curr) will have resulted in resched being set.  This
	 * prevents us from potentially nominating it as a false LAST_BUDDY
	 * below.
	 */
	अगर (test_tsk_need_resched(curr))
		वापस;

	/* Idle tasks are by definition preempted by non-idle tasks. */
	अगर (unlikely(task_has_idle_policy(curr)) &&
	    likely(!task_has_idle_policy(p)))
		जाओ preempt;

	/*
	 * Batch and idle tasks करो not preempt non-idle tasks (their preemption
	 * is driven by the tick):
	 */
	अगर (unlikely(p->policy != SCHED_NORMAL) || !sched_feat(WAKEUP_PREEMPTION))
		वापस;

	find_matching_se(&se, &pse);
	update_curr(cfs_rq_of(se));
	BUG_ON(!pse);
	अगर (wakeup_preempt_entity(se, pse) == 1) अणु
		/*
		 * Bias pick_next to pick the sched entity that is
		 * triggering this preemption.
		 */
		अगर (!next_buddy_marked)
			set_next_buddy(pse);
		जाओ preempt;
	पूर्ण

	वापस;

preempt:
	resched_curr(rq);
	/*
	 * Only set the backward buddy when the current task is still
	 * on the rq. This can happen when a wakeup माला_लो पूर्णांकerleaved
	 * with schedule on the ->pre_schedule() or idle_balance()
	 * poपूर्णांक, either of which can * drop the rq lock.
	 *
	 * Also, during early boot the idle thपढ़ो is in the fair class,
	 * क्रम obvious reasons its a bad idea to schedule back to it.
	 */
	अगर (unlikely(!se->on_rq || curr == rq->idle))
		वापस;

	अगर (sched_feat(LAST_BUDDY) && scale && entity_is_task(se))
		set_last_buddy(se);
पूर्ण

काष्ठा task_काष्ठा *
pick_next_task_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा rq_flags *rf)
अणु
	काष्ठा cfs_rq *cfs_rq = &rq->cfs;
	काष्ठा sched_entity *se;
	काष्ठा task_काष्ठा *p;
	पूर्णांक new_tasks;

again:
	अगर (!sched_fair_runnable(rq))
		जाओ idle;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	अगर (!prev || prev->sched_class != &fair_sched_class)
		जाओ simple;

	/*
	 * Because of the set_next_buddy() in dequeue_task_fair() it is rather
	 * likely that a next task is from the same cgroup as the current.
	 *
	 * Thereक्रमe attempt to aव्योम putting and setting the entire cgroup
	 * hierarchy, only change the part that actually changes.
	 */

	करो अणु
		काष्ठा sched_entity *curr = cfs_rq->curr;

		/*
		 * Since we got here without करोing put_prev_entity() we also
		 * have to consider cfs_rq->curr. If it is still a runnable
		 * entity, update_curr() will update its vrunसमय, otherwise
		 * क्रमget we've ever seen it.
		 */
		अगर (curr) अणु
			अगर (curr->on_rq)
				update_curr(cfs_rq);
			अन्यथा
				curr = शून्य;

			/*
			 * This call to check_cfs_rq_runसमय() will करो the
			 * throttle and dequeue its entity in the parent(s).
			 * Thereक्रमe the nr_running test will indeed
			 * be correct.
			 */
			अगर (unlikely(check_cfs_rq_runसमय(cfs_rq))) अणु
				cfs_rq = &rq->cfs;

				अगर (!cfs_rq->nr_running)
					जाओ idle;

				जाओ simple;
			पूर्ण
		पूर्ण

		se = pick_next_entity(cfs_rq, curr);
		cfs_rq = group_cfs_rq(se);
	पूर्ण जबतक (cfs_rq);

	p = task_of(se);

	/*
	 * Since we haven't yet करोne put_prev_entity and अगर the selected task
	 * is a dअगरferent task than we started out with, try and touch the
	 * least amount of cfs_rqs.
	 */
	अगर (prev != p) अणु
		काष्ठा sched_entity *pse = &prev->se;

		जबतक (!(cfs_rq = is_same_group(se, pse))) अणु
			पूर्णांक se_depth = se->depth;
			पूर्णांक pse_depth = pse->depth;

			अगर (se_depth <= pse_depth) अणु
				put_prev_entity(cfs_rq_of(pse), pse);
				pse = parent_entity(pse);
			पूर्ण
			अगर (se_depth >= pse_depth) अणु
				set_next_entity(cfs_rq_of(se), se);
				se = parent_entity(se);
			पूर्ण
		पूर्ण

		put_prev_entity(cfs_rq, pse);
		set_next_entity(cfs_rq, se);
	पूर्ण

	जाओ करोne;
simple:
#पूर्ण_अगर
	अगर (prev)
		put_prev_task(rq, prev);

	करो अणु
		se = pick_next_entity(cfs_rq, शून्य);
		set_next_entity(cfs_rq, se);
		cfs_rq = group_cfs_rq(se);
	पूर्ण जबतक (cfs_rq);

	p = task_of(se);

करोne: __maybe_unused;
#अगर_घोषित CONFIG_SMP
	/*
	 * Move the next running task to the front of
	 * the list, so our cfs_tasks list becomes MRU
	 * one.
	 */
	list_move(&p->se.group_node, &rq->cfs_tasks);
#पूर्ण_अगर

	अगर (hrtick_enabled_fair(rq))
		hrtick_start_fair(rq, p);

	update_misfit_status(p, rq);

	वापस p;

idle:
	अगर (!rf)
		वापस शून्य;

	new_tasks = newidle_balance(rq, rf);

	/*
	 * Because newidle_balance() releases (and re-acquires) rq->lock, it is
	 * possible क्रम any higher priority task to appear. In that हाल we
	 * must re-start the pick_next_entity() loop.
	 */
	अगर (new_tasks < 0)
		वापस RETRY_TASK;

	अगर (new_tasks > 0)
		जाओ again;

	/*
	 * rq is about to be idle, check अगर we need to update the
	 * lost_idle_समय of घड़ी_pelt
	 */
	update_idle_rq_घड़ी_pelt(rq);

	वापस शून्य;
पूर्ण

अटल काष्ठा task_काष्ठा *__pick_next_task_fair(काष्ठा rq *rq)
अणु
	वापस pick_next_task_fair(rq, शून्य, शून्य);
पूर्ण

/*
 * Account क्रम a descheduled task:
 */
अटल व्योम put_prev_task_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
	काष्ठा sched_entity *se = &prev->se;
	काष्ठा cfs_rq *cfs_rq;

	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);
		put_prev_entity(cfs_rq, se);
	पूर्ण
पूर्ण

/*
 * sched_yield() is very simple
 *
 * The magic of dealing with the ->skip buddy is in pick_next_entity.
 */
अटल व्योम yield_task_fair(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *curr = rq->curr;
	काष्ठा cfs_rq *cfs_rq = task_cfs_rq(curr);
	काष्ठा sched_entity *se = &curr->se;

	/*
	 * Are we the only task in the tree?
	 */
	अगर (unlikely(rq->nr_running == 1))
		वापस;

	clear_buddies(cfs_rq, se);

	अगर (curr->policy != SCHED_BATCH) अणु
		update_rq_घड़ी(rq);
		/*
		 * Update run-समय statistics of the 'current'.
		 */
		update_curr(cfs_rq);
		/*
		 * Tell update_rq_घड़ी() that we've just updated,
		 * so we करोn't करो microscopic update in schedule()
		 * and द्विगुन the fastpath cost.
		 */
		rq_घड़ी_skip_update(rq);
	पूर्ण

	set_skip_buddy(se);
पूर्ण

अटल bool yield_to_task_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_entity *se = &p->se;

	/* throttled hierarchies are not runnable */
	अगर (!se->on_rq || throttled_hierarchy(cfs_rq_of(se)))
		वापस false;

	/* Tell the scheduler that we'd really like pse to run next. */
	set_next_buddy(se);

	yield_task_fair(rq);

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_SMP
/**************************************************
 * Fair scheduling class load-balancing methods.
 *
 * BASICS
 *
 * The purpose of load-balancing is to achieve the same basic fairness the
 * per-CPU scheduler provides, namely provide a proportional amount of compute
 * समय to each task. This is expressed in the following equation:
 *
 *   W_i,n/P_i == W_j,n/P_j क्रम all i,j                               (1)
 *
 * Where W_i,n is the n-th weight average क्रम CPU i. The instantaneous weight
 * W_i,0 is defined as:
 *
 *   W_i,0 = \Sum_j w_i,j                                             (2)
 *
 * Where w_i,j is the weight of the j-th runnable task on CPU i. This weight
 * is derived from the nice value as per sched_prio_to_weight[].
 *
 * The weight average is an exponential decay average of the instantaneous
 * weight:
 *
 *   W'_i,n = (2^n - 1) / 2^n * W_i,n + 1 / 2^n * W_i,0               (3)
 *
 * C_i is the compute capacity of CPU i, typically it is the
 * fraction of 'recent' समय available क्रम SCHED_OTHER task execution. But it
 * can also include other factors [XXX].
 *
 * To achieve this balance we define a measure of imbalance which follows
 * directly from (1):
 *
 *   imb_i,j = maxअणु avg(W/C), W_i/C_i पूर्ण - minअणु avg(W/C), W_j/C_j पूर्ण    (4)
 *
 * We them move tasks around to minimize the imbalance. In the continuous
 * function space it is obvious this converges, in the discrete हाल we get
 * a few fun हालs generally called infeasible weight scenarios.
 *
 * [XXX expand on:
 *     - infeasible weights;
 *     - local vs global optima in the discrete हाल. ]
 *
 *
 * SCHED DOMAINS
 *
 * In order to solve the imbalance equation (4), and aव्योम the obvious O(n^2)
 * क्रम all i,j solution, we create a tree of CPUs that follows the hardware
 * topology where each level pairs two lower groups (or better). This results
 * in O(log n) layers. Furthermore we reduce the number of CPUs going up the
 * tree to only the first of the previous level and we decrease the frequency
 * of load-balance at each level inv. proportional to the number of CPUs in
 * the groups.
 *
 * This yields:
 *
 *     log_2 n     1     n
 *   \Sum       अणु --- * --- * 2^i पूर्ण = O(n)                            (5)
 *     i = 0      2^i   2^i
 *                               `- size of each group
 *         |         |     `- number of CPUs करोing load-balance
 *         |         `- freq
 *         `- sum over all levels
 *
 * Coupled with a limit on how many tasks we can migrate every balance pass,
 * this makes (5) the runसमय complनिकासy of the balancer.
 *
 * An important property here is that each CPU is still (indirectly) connected
 * to every other CPU in at most O(log n) steps:
 *
 * The adjacency matrix of the resulting graph is given by:
 *
 *             log_2 n
 *   A_i,j = \Union     (i % 2^k == 0) && i / 2^(k+1) == j / 2^(k+1)  (6)
 *             k = 0
 *
 * And you'll find that:
 *
 *   A^(log_2 n)_i,j != 0  क्रम all i,j                                (7)
 *
 * Showing there's indeed a path between every CPU in at most O(log n) steps.
 * The task movement gives a factor of O(m), giving a convergence complनिकासy
 * of:
 *
 *   O(nm log n),  n := nr_cpus, m := nr_tasks                        (8)
 *
 *
 * WORK CONSERVING
 *
 * In order to aव्योम CPUs going idle जबतक there's still work to करो, new idle
 * balancing is more aggressive and has the newly idle CPU iterate up the करोमुख्य
 * tree itself instead of relying on other CPUs to bring it work.
 *
 * This adds some complनिकासy to both (5) and (8) but it reduces the total idle
 * समय.
 *
 * [XXX more?]
 *
 *
 * CGROUPS
 *
 * Cgroups make a horror show out of (2), instead of a simple sum we get:
 *
 *                                s_k,i
 *   W_i,0 = \Sum_j \Prod_k w_k * -----                               (9)
 *                                 S_k
 *
 * Where
 *
 *   s_k,i = \Sum_j w_i,j,k  and  S_k = \Sum_i s_k,i                 (10)
 *
 * w_i,j,k is the weight of the j-th runnable task in the k-th cgroup on CPU i.
 *
 * The big problem is S_k, its a global sum needed to compute a local (W_i)
 * property.
 *
 * [XXX ग_लिखो more on how we solve this.. _after_ merging pjt's patches that
 *      reग_लिखो all of this once again.]
 */

अटल अचिन्हित दीर्घ __पढ़ो_mostly max_load_balance_पूर्णांकerval = HZ/10;

क्रमागत fbq_type अणु regular, remote, all पूर्ण;

/*
 * 'group_type' describes the group of CPUs at the moment of load balancing.
 *
 * The क्रमागत is ordered by pulling priority, with the group with lowest priority
 * first so the group_type can simply be compared when selecting the busiest
 * group. See update_sd_pick_busiest().
 */
क्रमागत group_type अणु
	/* The group has spare capacity that can be used to run more tasks.  */
	group_has_spare = 0,
	/*
	 * The group is fully used and the tasks करोn't compete क्रम more CPU
	 * cycles. Nevertheless, some tasks might रुको beक्रमe running.
	 */
	group_fully_busy,
	/*
	 * SD_ASYM_CPUCAPACITY only: One task करोesn't fit with CPU's capacity
	 * and must be migrated to a more घातerful CPU.
	 */
	group_misfit_task,
	/*
	 * SD_ASYM_PACKING only: One local CPU with higher capacity is available,
	 * and the task should be migrated to it instead of running on the
	 * current CPU.
	 */
	group_asym_packing,
	/*
	 * The tasks' affinity स्थिरraपूर्णांकs previously prevented the scheduler
	 * from balancing the load across the प्रणाली.
	 */
	group_imbalanced,
	/*
	 * The CPU is overloaded and can't provide expected CPU cycles to all
	 * tasks.
	 */
	group_overloaded
पूर्ण;

क्रमागत migration_type अणु
	migrate_load = 0,
	migrate_util,
	migrate_task,
	migrate_misfit
पूर्ण;

#घोषणा LBF_ALL_PINNED	0x01
#घोषणा LBF_NEED_BREAK	0x02
#घोषणा LBF_DST_PINNED  0x04
#घोषणा LBF_SOME_PINNED	0x08
#घोषणा LBF_ACTIVE_LB	0x10

काष्ठा lb_env अणु
	काष्ठा sched_करोमुख्य	*sd;

	काष्ठा rq		*src_rq;
	पूर्णांक			src_cpu;

	पूर्णांक			dst_cpu;
	काष्ठा rq		*dst_rq;

	काष्ठा cpumask		*dst_grpmask;
	पूर्णांक			new_dst_cpu;
	क्रमागत cpu_idle_type	idle;
	दीर्घ			imbalance;
	/* The set of CPUs under consideration क्रम load-balancing */
	काष्ठा cpumask		*cpus;

	अचिन्हित पूर्णांक		flags;

	अचिन्हित पूर्णांक		loop;
	अचिन्हित पूर्णांक		loop_अवरोध;
	अचिन्हित पूर्णांक		loop_max;

	क्रमागत fbq_type		fbq_type;
	क्रमागत migration_type	migration_type;
	काष्ठा list_head	tasks;
पूर्ण;

/*
 * Is this task likely cache-hot:
 */
अटल पूर्णांक task_hot(काष्ठा task_काष्ठा *p, काष्ठा lb_env *env)
अणु
	s64 delta;

	lockdep_निश्चित_held(&env->src_rq->lock);

	अगर (p->sched_class != &fair_sched_class)
		वापस 0;

	अगर (unlikely(task_has_idle_policy(p)))
		वापस 0;

	/* SMT siblings share cache */
	अगर (env->sd->flags & SD_SHARE_CPUCAPACITY)
		वापस 0;

	/*
	 * Buddy candidates are cache hot:
	 */
	अगर (sched_feat(CACHE_HOT_BUDDY) && env->dst_rq->nr_running &&
			(&p->se == cfs_rq_of(&p->se)->next ||
			 &p->se == cfs_rq_of(&p->se)->last))
		वापस 1;

	अगर (sysctl_sched_migration_cost == -1)
		वापस 1;
	अगर (sysctl_sched_migration_cost == 0)
		वापस 0;

	delta = rq_घड़ी_प्रकारask(env->src_rq) - p->se.exec_start;

	वापस delta < (s64)sysctl_sched_migration_cost;
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * Returns 1, अगर task migration degrades locality
 * Returns 0, अगर task migration improves locality i.e migration preferred.
 * Returns -1, अगर task migration is not affected by locality.
 */
अटल पूर्णांक migrate_degrades_locality(काष्ठा task_काष्ठा *p, काष्ठा lb_env *env)
अणु
	काष्ठा numa_group *numa_group = rcu_dereference(p->numa_group);
	अचिन्हित दीर्घ src_weight, dst_weight;
	पूर्णांक src_nid, dst_nid, dist;

	अगर (!अटल_branch_likely(&sched_numa_balancing))
		वापस -1;

	अगर (!p->numa_faults || !(env->sd->flags & SD_NUMA))
		वापस -1;

	src_nid = cpu_to_node(env->src_cpu);
	dst_nid = cpu_to_node(env->dst_cpu);

	अगर (src_nid == dst_nid)
		वापस -1;

	/* Migrating away from the preferred node is always bad. */
	अगर (src_nid == p->numa_preferred_nid) अणु
		अगर (env->src_rq->nr_running > env->src_rq->nr_preferred_running)
			वापस 1;
		अन्यथा
			वापस -1;
	पूर्ण

	/* Encourage migration to the preferred node. */
	अगर (dst_nid == p->numa_preferred_nid)
		वापस 0;

	/* Leaving a core idle is often worse than degrading locality. */
	अगर (env->idle == CPU_IDLE)
		वापस -1;

	dist = node_distance(src_nid, dst_nid);
	अगर (numa_group) अणु
		src_weight = group_weight(p, src_nid, dist);
		dst_weight = group_weight(p, dst_nid, dist);
	पूर्ण अन्यथा अणु
		src_weight = task_weight(p, src_nid, dist);
		dst_weight = task_weight(p, dst_nid, dist);
	पूर्ण

	वापस dst_weight < src_weight;
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक migrate_degrades_locality(काष्ठा task_काष्ठा *p,
					     काष्ठा lb_env *env)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

/*
 * can_migrate_task - may task p from runqueue rq be migrated to this_cpu?
 */
अटल
पूर्णांक can_migrate_task(काष्ठा task_काष्ठा *p, काष्ठा lb_env *env)
अणु
	पूर्णांक tsk_cache_hot;

	lockdep_निश्चित_held(&env->src_rq->lock);

	/*
	 * We करो not migrate tasks that are:
	 * 1) throttled_lb_pair, or
	 * 2) cannot be migrated to this CPU due to cpus_ptr, or
	 * 3) running (obviously), or
	 * 4) are cache-hot on their current CPU.
	 */
	अगर (throttled_lb_pair(task_group(p), env->src_cpu, env->dst_cpu))
		वापस 0;

	/* Disregard pcpu kthपढ़ोs; they are where they need to be. */
	अगर (kthपढ़ो_is_per_cpu(p))
		वापस 0;

	अगर (!cpumask_test_cpu(env->dst_cpu, p->cpus_ptr)) अणु
		पूर्णांक cpu;

		schedstat_inc(p->se.statistics.nr_failed_migrations_affine);

		env->flags |= LBF_SOME_PINNED;

		/*
		 * Remember अगर this task can be migrated to any other CPU in
		 * our sched_group. We may want to revisit it अगर we couldn't
		 * meet load balance goals by pulling other tasks on src_cpu.
		 *
		 * Aव्योम computing new_dst_cpu
		 * - क्रम NEWLY_IDLE
		 * - अगर we have alपढ़ोy computed one in current iteration
		 * - अगर it's an active balance
		 */
		अगर (env->idle == CPU_NEWLY_IDLE ||
		    env->flags & (LBF_DST_PINNED | LBF_ACTIVE_LB))
			वापस 0;

		/* Prevent to re-select dst_cpu via env's CPUs: */
		क्रम_each_cpu_and(cpu, env->dst_grpmask, env->cpus) अणु
			अगर (cpumask_test_cpu(cpu, p->cpus_ptr)) अणु
				env->flags |= LBF_DST_PINNED;
				env->new_dst_cpu = cpu;
				अवरोध;
			पूर्ण
		पूर्ण

		वापस 0;
	पूर्ण

	/* Record that we found at least one task that could run on dst_cpu */
	env->flags &= ~LBF_ALL_PINNED;

	अगर (task_running(env->src_rq, p)) अणु
		schedstat_inc(p->se.statistics.nr_failed_migrations_running);
		वापस 0;
	पूर्ण

	/*
	 * Aggressive migration अगर:
	 * 1) active balance
	 * 2) destination numa is preferred
	 * 3) task is cache cold, or
	 * 4) too many balance attempts have failed.
	 */
	अगर (env->flags & LBF_ACTIVE_LB)
		वापस 1;

	tsk_cache_hot = migrate_degrades_locality(p, env);
	अगर (tsk_cache_hot == -1)
		tsk_cache_hot = task_hot(p, env);

	अगर (tsk_cache_hot <= 0 ||
	    env->sd->nr_balance_failed > env->sd->cache_nice_tries) अणु
		अगर (tsk_cache_hot == 1) अणु
			schedstat_inc(env->sd->lb_hot_gained[env->idle]);
			schedstat_inc(p->se.statistics.nr_क्रमced_migrations);
		पूर्ण
		वापस 1;
	पूर्ण

	schedstat_inc(p->se.statistics.nr_failed_migrations_hot);
	वापस 0;
पूर्ण

/*
 * detach_task() -- detach the task क्रम the migration specअगरied in env
 */
अटल व्योम detach_task(काष्ठा task_काष्ठा *p, काष्ठा lb_env *env)
अणु
	lockdep_निश्चित_held(&env->src_rq->lock);

	deactivate_task(env->src_rq, p, DEQUEUE_NOCLOCK);
	set_task_cpu(p, env->dst_cpu);
पूर्ण

/*
 * detach_one_task() -- tries to dequeue exactly one task from env->src_rq, as
 * part of active balancing operations within "domain".
 *
 * Returns a task अगर successful and शून्य otherwise.
 */
अटल काष्ठा task_काष्ठा *detach_one_task(काष्ठा lb_env *env)
अणु
	काष्ठा task_काष्ठा *p;

	lockdep_निश्चित_held(&env->src_rq->lock);

	list_क्रम_each_entry_reverse(p,
			&env->src_rq->cfs_tasks, se.group_node) अणु
		अगर (!can_migrate_task(p, env))
			जारी;

		detach_task(p, env);

		/*
		 * Right now, this is only the second place where
		 * lb_gained[env->idle] is updated (other is detach_tasks)
		 * so we can safely collect stats here rather than
		 * inside detach_tasks().
		 */
		schedstat_inc(env->sd->lb_gained[env->idle]);
		वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक sched_nr_migrate_अवरोध = 32;

/*
 * detach_tasks() -- tries to detach up to imbalance load/util/tasks from
 * busiest_rq, as part of a balancing operation within करोमुख्य "sd".
 *
 * Returns number of detached tasks अगर successful and 0 otherwise.
 */
अटल पूर्णांक detach_tasks(काष्ठा lb_env *env)
अणु
	काष्ठा list_head *tasks = &env->src_rq->cfs_tasks;
	अचिन्हित दीर्घ util, load;
	काष्ठा task_काष्ठा *p;
	पूर्णांक detached = 0;

	lockdep_निश्चित_held(&env->src_rq->lock);

	/*
	 * Source run queue has been emptied by another CPU, clear
	 * LBF_ALL_PINNED flag as we will not test any task.
	 */
	अगर (env->src_rq->nr_running <= 1) अणु
		env->flags &= ~LBF_ALL_PINNED;
		वापस 0;
	पूर्ण

	अगर (env->imbalance <= 0)
		वापस 0;

	जबतक (!list_empty(tasks)) अणु
		/*
		 * We करोn't want to steal all, otherwise we may be treated likewise,
		 * which could at worst lead to a livelock crash.
		 */
		अगर (env->idle != CPU_NOT_IDLE && env->src_rq->nr_running <= 1)
			अवरोध;

		p = list_last_entry(tasks, काष्ठा task_काष्ठा, se.group_node);

		env->loop++;
		/* We've more or less seen every task there is, call it quits */
		अगर (env->loop > env->loop_max)
			अवरोध;

		/* take a breather every nr_migrate tasks */
		अगर (env->loop > env->loop_अवरोध) अणु
			env->loop_अवरोध += sched_nr_migrate_अवरोध;
			env->flags |= LBF_NEED_BREAK;
			अवरोध;
		पूर्ण

		अगर (!can_migrate_task(p, env))
			जाओ next;

		चयन (env->migration_type) अणु
		हाल migrate_load:
			/*
			 * Depending of the number of CPUs and tasks and the
			 * cgroup hierarchy, task_h_load() can वापस a null
			 * value. Make sure that env->imbalance decreases
			 * otherwise detach_tasks() will stop only after
			 * detaching up to loop_max tasks.
			 */
			load = max_t(अचिन्हित दीर्घ, task_h_load(p), 1);

			अगर (sched_feat(LB_MIN) &&
			    load < 16 && !env->sd->nr_balance_failed)
				जाओ next;

			/*
			 * Make sure that we करोn't migrate too much load.
			 * Nevertheless, let relax the स्थिरraपूर्णांक अगर
			 * scheduler fails to find a good रुकोing task to
			 * migrate.
			 */
			अगर (shr_bound(load, env->sd->nr_balance_failed) > env->imbalance)
				जाओ next;

			env->imbalance -= load;
			अवरोध;

		हाल migrate_util:
			util = task_util_est(p);

			अगर (util > env->imbalance)
				जाओ next;

			env->imbalance -= util;
			अवरोध;

		हाल migrate_task:
			env->imbalance--;
			अवरोध;

		हाल migrate_misfit:
			/* This is not a misfit task */
			अगर (task_fits_capacity(p, capacity_of(env->src_cpu)))
				जाओ next;

			env->imbalance = 0;
			अवरोध;
		पूर्ण

		detach_task(p, env);
		list_add(&p->se.group_node, &env->tasks);

		detached++;

#अगर_घोषित CONFIG_PREEMPTION
		/*
		 * NEWIDLE balancing is a source of latency, so preemptible
		 * kernels will stop after the first task is detached to minimize
		 * the critical section.
		 */
		अगर (env->idle == CPU_NEWLY_IDLE)
			अवरोध;
#पूर्ण_अगर

		/*
		 * We only want to steal up to the prescribed amount of
		 * load/util/tasks.
		 */
		अगर (env->imbalance <= 0)
			अवरोध;

		जारी;
next:
		list_move(&p->se.group_node, tasks);
	पूर्ण

	/*
	 * Right now, this is one of only two places we collect this stat
	 * so we can safely collect detach_one_task() stats here rather
	 * than inside detach_one_task().
	 */
	schedstat_add(env->sd->lb_gained[env->idle], detached);

	वापस detached;
पूर्ण

/*
 * attach_task() -- attach the task detached by detach_task() to its new rq.
 */
अटल व्योम attach_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	lockdep_निश्चित_held(&rq->lock);

	BUG_ON(task_rq(p) != rq);
	activate_task(rq, p, ENQUEUE_NOCLOCK);
	check_preempt_curr(rq, p, 0);
पूर्ण

/*
 * attach_one_task() -- attaches the task वापसed from detach_one_task() to
 * its new rq.
 */
अटल व्योम attach_one_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rq_flags rf;

	rq_lock(rq, &rf);
	update_rq_घड़ी(rq);
	attach_task(rq, p);
	rq_unlock(rq, &rf);
पूर्ण

/*
 * attach_tasks() -- attaches all tasks detached by detach_tasks() to their
 * new rq.
 */
अटल व्योम attach_tasks(काष्ठा lb_env *env)
अणु
	काष्ठा list_head *tasks = &env->tasks;
	काष्ठा task_काष्ठा *p;
	काष्ठा rq_flags rf;

	rq_lock(env->dst_rq, &rf);
	update_rq_घड़ी(env->dst_rq);

	जबतक (!list_empty(tasks)) अणु
		p = list_first_entry(tasks, काष्ठा task_काष्ठा, se.group_node);
		list_del_init(&p->se.group_node);

		attach_task(env->dst_rq, p);
	पूर्ण

	rq_unlock(env->dst_rq, &rf);
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_COMMON
अटल अंतरभूत bool cfs_rq_has_blocked(काष्ठा cfs_rq *cfs_rq)
अणु
	अगर (cfs_rq->avg.load_avg)
		वापस true;

	अगर (cfs_rq->avg.util_avg)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool others_have_blocked(काष्ठा rq *rq)
अणु
	अगर (READ_ONCE(rq->avg_rt.util_avg))
		वापस true;

	अगर (READ_ONCE(rq->avg_dl.util_avg))
		वापस true;

	अगर (thermal_load_avg(rq))
		वापस true;

#अगर_घोषित CONFIG_HAVE_SCHED_AVG_IRQ
	अगर (READ_ONCE(rq->avg_irq.util_avg))
		वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

अटल अंतरभूत व्योम update_blocked_load_tick(काष्ठा rq *rq)
अणु
	WRITE_ONCE(rq->last_blocked_load_update_tick, jअगरfies);
पूर्ण

अटल अंतरभूत व्योम update_blocked_load_status(काष्ठा rq *rq, bool has_blocked)
अणु
	अगर (!has_blocked)
		rq->has_blocked_load = 0;
पूर्ण
#अन्यथा
अटल अंतरभूत bool cfs_rq_has_blocked(काष्ठा cfs_rq *cfs_rq) अणु वापस false; पूर्ण
अटल अंतरभूत bool others_have_blocked(काष्ठा rq *rq) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम update_blocked_load_tick(काष्ठा rq *rq) अणुपूर्ण
अटल अंतरभूत व्योम update_blocked_load_status(काष्ठा rq *rq, bool has_blocked) अणुपूर्ण
#पूर्ण_अगर

अटल bool __update_blocked_others(काष्ठा rq *rq, bool *करोne)
अणु
	स्थिर काष्ठा sched_class *curr_class;
	u64 now = rq_घड़ी_pelt(rq);
	अचिन्हित दीर्घ thermal_pressure;
	bool decayed;

	/*
	 * update_load_avg() can call cpufreq_update_util(). Make sure that RT,
	 * DL and IRQ संकेतs have been updated beक्रमe updating CFS.
	 */
	curr_class = rq->curr->sched_class;

	thermal_pressure = arch_scale_thermal_pressure(cpu_of(rq));

	decayed = update_rt_rq_load_avg(now, rq, curr_class == &rt_sched_class) |
		  update_dl_rq_load_avg(now, rq, curr_class == &dl_sched_class) |
		  update_thermal_load_avg(rq_घड़ी_प्रकारhermal(rq), rq, thermal_pressure) |
		  update_irq_load_avg(rq, 0);

	अगर (others_have_blocked(rq))
		*करोne = false;

	वापस decayed;
पूर्ण

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED

अटल bool __update_blocked_fair(काष्ठा rq *rq, bool *करोne)
अणु
	काष्ठा cfs_rq *cfs_rq, *pos;
	bool decayed = false;
	पूर्णांक cpu = cpu_of(rq);

	/*
	 * Iterates the task_group tree in a bottom up fashion, see
	 * list_add_leaf_cfs_rq() क्रम details.
	 */
	क्रम_each_leaf_cfs_rq_safe(rq, cfs_rq, pos) अणु
		काष्ठा sched_entity *se;

		अगर (update_cfs_rq_load_avg(cfs_rq_घड़ी_pelt(cfs_rq), cfs_rq)) अणु
			update_tg_load_avg(cfs_rq);

			अगर (cfs_rq == &rq->cfs)
				decayed = true;
		पूर्ण

		/* Propagate pending load changes to the parent, अगर any: */
		se = cfs_rq->tg->se[cpu];
		अगर (se && !skip_blocked_update(se))
			update_load_avg(cfs_rq_of(se), se, UPDATE_TG);

		/*
		 * There can be a lot of idle CPU cgroups.  Don't let fully
		 * decayed cfs_rqs linger on the list.
		 */
		अगर (cfs_rq_is_decayed(cfs_rq))
			list_del_leaf_cfs_rq(cfs_rq);

		/* Don't need periodic decay once load/util_avg are null */
		अगर (cfs_rq_has_blocked(cfs_rq))
			*करोne = false;
	पूर्ण

	वापस decayed;
पूर्ण

/*
 * Compute the hierarchical load factor क्रम cfs_rq and all its ascendants.
 * This needs to be करोne in a top-करोwn fashion because the load of a child
 * group is a fraction of its parents load.
 */
अटल व्योम update_cfs_rq_h_load(काष्ठा cfs_rq *cfs_rq)
अणु
	काष्ठा rq *rq = rq_of(cfs_rq);
	काष्ठा sched_entity *se = cfs_rq->tg->se[cpu_of(rq)];
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ load;

	अगर (cfs_rq->last_h_load_update == now)
		वापस;

	WRITE_ONCE(cfs_rq->h_load_next, शून्य);
	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);
		WRITE_ONCE(cfs_rq->h_load_next, se);
		अगर (cfs_rq->last_h_load_update == now)
			अवरोध;
	पूर्ण

	अगर (!se) अणु
		cfs_rq->h_load = cfs_rq_load_avg(cfs_rq);
		cfs_rq->last_h_load_update = now;
	पूर्ण

	जबतक ((se = READ_ONCE(cfs_rq->h_load_next)) != शून्य) अणु
		load = cfs_rq->h_load;
		load = भाग64_ul(load * se->avg.load_avg,
			cfs_rq_load_avg(cfs_rq) + 1);
		cfs_rq = group_cfs_rq(se);
		cfs_rq->h_load = load;
		cfs_rq->last_h_load_update = now;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ task_h_load(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा cfs_rq *cfs_rq = task_cfs_rq(p);

	update_cfs_rq_h_load(cfs_rq);
	वापस भाग64_ul(p->se.avg.load_avg * cfs_rq->h_load,
			cfs_rq_load_avg(cfs_rq) + 1);
पूर्ण
#अन्यथा
अटल bool __update_blocked_fair(काष्ठा rq *rq, bool *करोne)
अणु
	काष्ठा cfs_rq *cfs_rq = &rq->cfs;
	bool decayed;

	decayed = update_cfs_rq_load_avg(cfs_rq_घड़ी_pelt(cfs_rq), cfs_rq);
	अगर (cfs_rq_has_blocked(cfs_rq))
		*करोne = false;

	वापस decayed;
पूर्ण

अटल अचिन्हित दीर्घ task_h_load(काष्ठा task_काष्ठा *p)
अणु
	वापस p->se.avg.load_avg;
पूर्ण
#पूर्ण_अगर

अटल व्योम update_blocked_averages(पूर्णांक cpu)
अणु
	bool decayed = false, करोne = true;
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा rq_flags rf;

	rq_lock_irqsave(rq, &rf);
	update_blocked_load_tick(rq);
	update_rq_घड़ी(rq);

	decayed |= __update_blocked_others(rq, &करोne);
	decayed |= __update_blocked_fair(rq, &करोne);

	update_blocked_load_status(rq, !करोne);
	अगर (decayed)
		cpufreq_update_util(rq, 0);
	rq_unlock_irqrestore(rq, &rf);
पूर्ण

/********** Helpers क्रम find_busiest_group ************************/

/*
 * sg_lb_stats - stats of a sched_group required क्रम load_balancing
 */
काष्ठा sg_lb_stats अणु
	अचिन्हित दीर्घ avg_load; /*Avg load across the CPUs of the group */
	अचिन्हित दीर्घ group_load; /* Total load over the CPUs of the group */
	अचिन्हित दीर्घ group_capacity;
	अचिन्हित दीर्घ group_util; /* Total utilization over the CPUs of the group */
	अचिन्हित दीर्घ group_runnable; /* Total runnable समय over the CPUs of the group */
	अचिन्हित पूर्णांक sum_nr_running; /* Nr of tasks running in the group */
	अचिन्हित पूर्णांक sum_h_nr_running; /* Nr of CFS tasks running in the group */
	अचिन्हित पूर्णांक idle_cpus;
	अचिन्हित पूर्णांक group_weight;
	क्रमागत group_type group_type;
	अचिन्हित पूर्णांक group_asym_packing; /* Tasks should be moved to preferred CPU */
	अचिन्हित दीर्घ group_misfit_task_load; /* A CPU has a task too big क्रम its capacity */
#अगर_घोषित CONFIG_NUMA_BALANCING
	अचिन्हित पूर्णांक nr_numa_running;
	अचिन्हित पूर्णांक nr_preferred_running;
#पूर्ण_अगर
पूर्ण;

/*
 * sd_lb_stats - Structure to store the statistics of a sched_करोमुख्य
 *		 during load balancing.
 */
काष्ठा sd_lb_stats अणु
	काष्ठा sched_group *busiest;	/* Busiest group in this sd */
	काष्ठा sched_group *local;	/* Local group in this sd */
	अचिन्हित दीर्घ total_load;	/* Total load of all groups in sd */
	अचिन्हित दीर्घ total_capacity;	/* Total capacity of all groups in sd */
	अचिन्हित दीर्घ avg_load;	/* Average load across all groups in sd */
	अचिन्हित पूर्णांक prefer_sibling; /* tasks should go to sibling first */

	काष्ठा sg_lb_stats busiest_stat;/* Statistics of the busiest group */
	काष्ठा sg_lb_stats local_stat;	/* Statistics of the local group */
पूर्ण;

अटल अंतरभूत व्योम init_sd_lb_stats(काष्ठा sd_lb_stats *sds)
अणु
	/*
	 * Skimp on the clearing to aव्योम duplicate work. We can aव्योम clearing
	 * local_stat because update_sg_lb_stats() करोes a full clear/assignment.
	 * We must however set busiest_stat::group_type and
	 * busiest_stat::idle_cpus to the worst busiest group because
	 * update_sd_pick_busiest() पढ़ोs these beक्रमe assignment.
	 */
	*sds = (काष्ठा sd_lb_stats)अणु
		.busiest = शून्य,
		.local = शून्य,
		.total_load = 0UL,
		.total_capacity = 0UL,
		.busiest_stat = अणु
			.idle_cpus = अच_पूर्णांक_उच्च,
			.group_type = group_has_spare,
		पूर्ण,
	पूर्ण;
पूर्ण

अटल अचिन्हित दीर्घ scale_rt_capacity(पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	अचिन्हित दीर्घ max = arch_scale_cpu_capacity(cpu);
	अचिन्हित दीर्घ used, मुक्त;
	अचिन्हित दीर्घ irq;

	irq = cpu_util_irq(rq);

	अगर (unlikely(irq >= max))
		वापस 1;

	/*
	 * avg_rt.util_avg and avg_dl.util_avg track binary संकेतs
	 * (running and not running) with weights 0 and 1024 respectively.
	 * avg_thermal.load_avg tracks thermal pressure and the weighted
	 * average uses the actual delta max capacity(load).
	 */
	used = READ_ONCE(rq->avg_rt.util_avg);
	used += READ_ONCE(rq->avg_dl.util_avg);
	used += thermal_load_avg(rq);

	अगर (unlikely(used >= max))
		वापस 1;

	मुक्त = max - used;

	वापस scale_irq_capacity(मुक्त, irq, max);
पूर्ण

अटल व्योम update_cpu_capacity(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ capacity = scale_rt_capacity(cpu);
	काष्ठा sched_group *sdg = sd->groups;

	cpu_rq(cpu)->cpu_capacity_orig = arch_scale_cpu_capacity(cpu);

	अगर (!capacity)
		capacity = 1;

	cpu_rq(cpu)->cpu_capacity = capacity;
	trace_sched_cpu_capacity_tp(cpu_rq(cpu));

	sdg->sgc->capacity = capacity;
	sdg->sgc->min_capacity = capacity;
	sdg->sgc->max_capacity = capacity;
पूर्ण

व्योम update_group_capacity(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu)
अणु
	काष्ठा sched_करोमुख्य *child = sd->child;
	काष्ठा sched_group *group, *sdg = sd->groups;
	अचिन्हित दीर्घ capacity, min_capacity, max_capacity;
	अचिन्हित दीर्घ पूर्णांकerval;

	पूर्णांकerval = msecs_to_jअगरfies(sd->balance_पूर्णांकerval);
	पूर्णांकerval = clamp(पूर्णांकerval, 1UL, max_load_balance_पूर्णांकerval);
	sdg->sgc->next_update = jअगरfies + पूर्णांकerval;

	अगर (!child) अणु
		update_cpu_capacity(sd, cpu);
		वापस;
	पूर्ण

	capacity = 0;
	min_capacity = अच_दीर्घ_उच्च;
	max_capacity = 0;

	अगर (child->flags & SD_OVERLAP) अणु
		/*
		 * SD_OVERLAP करोमुख्यs cannot assume that child groups
		 * span the current group.
		 */

		क्रम_each_cpu(cpu, sched_group_span(sdg)) अणु
			अचिन्हित दीर्घ cpu_cap = capacity_of(cpu);

			capacity += cpu_cap;
			min_capacity = min(cpu_cap, min_capacity);
			max_capacity = max(cpu_cap, max_capacity);
		पूर्ण
	पूर्ण अन्यथा  अणु
		/*
		 * !SD_OVERLAP करोमुख्यs can assume that child groups
		 * span the current group.
		 */

		group = child->groups;
		करो अणु
			काष्ठा sched_group_capacity *sgc = group->sgc;

			capacity += sgc->capacity;
			min_capacity = min(sgc->min_capacity, min_capacity);
			max_capacity = max(sgc->max_capacity, max_capacity);
			group = group->next;
		पूर्ण जबतक (group != child->groups);
	पूर्ण

	sdg->sgc->capacity = capacity;
	sdg->sgc->min_capacity = min_capacity;
	sdg->sgc->max_capacity = max_capacity;
पूर्ण

/*
 * Check whether the capacity of the rq has been noticeably reduced by side
 * activity. The imbalance_pct is used क्रम the threshold.
 * Return true is the capacity is reduced
 */
अटल अंतरभूत पूर्णांक
check_cpu_capacity(काष्ठा rq *rq, काष्ठा sched_करोमुख्य *sd)
अणु
	वापस ((rq->cpu_capacity * sd->imbalance_pct) <
				(rq->cpu_capacity_orig * 100));
पूर्ण

/*
 * Check whether a rq has a misfit task and अगर it looks like we can actually
 * help that task: we can migrate the task to a CPU of higher capacity, or
 * the task's current CPU is heavily pressured.
 */
अटल अंतरभूत पूर्णांक check_misfit_status(काष्ठा rq *rq, काष्ठा sched_करोमुख्य *sd)
अणु
	वापस rq->misfit_task_load &&
		(rq->cpu_capacity_orig < rq->rd->max_cpu_capacity ||
		 check_cpu_capacity(rq, sd));
पूर्ण

/*
 * Group imbalance indicates (and tries to solve) the problem where balancing
 * groups is inadequate due to ->cpus_ptr स्थिरraपूर्णांकs.
 *
 * Imagine a situation of two groups of 4 CPUs each and 4 tasks each with a
 * cpumask covering 1 CPU of the first group and 3 CPUs of the second group.
 * Something like:
 *
 *	अणु 0 1 2 3 पूर्ण अणु 4 5 6 7 पूर्ण
 *	        *     * * *
 *
 * If we were to balance group-wise we'd place two tasks in the first group and
 * two tasks in the second group. Clearly this is undesired as it will overload
 * cpu 3 and leave one of the CPUs in the second group unused.
 *
 * The current solution to this issue is detecting the skew in the first group
 * by noticing the lower करोमुख्य failed to reach balance and had dअगरficulty
 * moving tasks due to affinity स्थिरraपूर्णांकs.
 *
 * When this is so detected; this group becomes a candidate क्रम busiest; see
 * update_sd_pick_busiest(). And calculate_imbalance() and
 * find_busiest_group() aव्योम some of the usual balance conditions to allow it
 * to create an effective group imbalance.
 *
 * This is a somewhat tricky proposition since the next run might not find the
 * group imbalance and decide the groups need to be balanced again. A most
 * subtle and fragile situation.
 */

अटल अंतरभूत पूर्णांक sg_imbalanced(काष्ठा sched_group *group)
अणु
	वापस group->sgc->imbalance;
पूर्ण

/*
 * group_has_capacity वापसs true अगर the group has spare capacity that could
 * be used by some tasks.
 * We consider that a group has spare capacity अगर the  * number of task is
 * smaller than the number of CPUs or अगर the utilization is lower than the
 * available capacity क्रम CFS tasks.
 * For the latter, we use a threshold to stabilize the state, to take पूर्णांकo
 * account the variance of the tasks' load and to वापस true अगर the available
 * capacity in meaningful क्रम the load balancer.
 * As an example, an available capacity of 1% can appear but it करोesn't make
 * any benefit क्रम the load balance.
 */
अटल अंतरभूत bool
group_has_capacity(अचिन्हित पूर्णांक imbalance_pct, काष्ठा sg_lb_stats *sgs)
अणु
	अगर (sgs->sum_nr_running < sgs->group_weight)
		वापस true;

	अगर ((sgs->group_capacity * imbalance_pct) <
			(sgs->group_runnable * 100))
		वापस false;

	अगर ((sgs->group_capacity * 100) >
			(sgs->group_util * imbalance_pct))
		वापस true;

	वापस false;
पूर्ण

/*
 *  group_is_overloaded वापसs true अगर the group has more tasks than it can
 *  handle.
 *  group_is_overloaded is not equals to !group_has_capacity because a group
 *  with the exact right number of tasks, has no more spare capacity but is not
 *  overloaded so both group_has_capacity and group_is_overloaded वापस
 *  false.
 */
अटल अंतरभूत bool
group_is_overloaded(अचिन्हित पूर्णांक imbalance_pct, काष्ठा sg_lb_stats *sgs)
अणु
	अगर (sgs->sum_nr_running <= sgs->group_weight)
		वापस false;

	अगर ((sgs->group_capacity * 100) <
			(sgs->group_util * imbalance_pct))
		वापस true;

	अगर ((sgs->group_capacity * imbalance_pct) <
			(sgs->group_runnable * 100))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत क्रमागत
group_type group_classअगरy(अचिन्हित पूर्णांक imbalance_pct,
			  काष्ठा sched_group *group,
			  काष्ठा sg_lb_stats *sgs)
अणु
	अगर (group_is_overloaded(imbalance_pct, sgs))
		वापस group_overloaded;

	अगर (sg_imbalanced(group))
		वापस group_imbalanced;

	अगर (sgs->group_asym_packing)
		वापस group_asym_packing;

	अगर (sgs->group_misfit_task_load)
		वापस group_misfit_task;

	अगर (!group_has_capacity(imbalance_pct, sgs))
		वापस group_fully_busy;

	वापस group_has_spare;
पूर्ण

/**
 * update_sg_lb_stats - Update sched_group's statistics क्रम load balancing.
 * @env: The load balancing environment.
 * @group: sched_group whose statistics are to be updated.
 * @sgs: variable to hold the statistics क्रम this group.
 * @sg_status: Holds flag indicating the status of the sched_group
 */
अटल अंतरभूत व्योम update_sg_lb_stats(काष्ठा lb_env *env,
				      काष्ठा sched_group *group,
				      काष्ठा sg_lb_stats *sgs,
				      पूर्णांक *sg_status)
अणु
	पूर्णांक i, nr_running, local_group;

	स_रखो(sgs, 0, माप(*sgs));

	local_group = cpumask_test_cpu(env->dst_cpu, sched_group_span(group));

	क्रम_each_cpu_and(i, sched_group_span(group), env->cpus) अणु
		काष्ठा rq *rq = cpu_rq(i);

		sgs->group_load += cpu_load(rq);
		sgs->group_util += cpu_util(i);
		sgs->group_runnable += cpu_runnable(rq);
		sgs->sum_h_nr_running += rq->cfs.h_nr_running;

		nr_running = rq->nr_running;
		sgs->sum_nr_running += nr_running;

		अगर (nr_running > 1)
			*sg_status |= SG_OVERLOAD;

		अगर (cpu_overutilized(i))
			*sg_status |= SG_OVERUTILIZED;

#अगर_घोषित CONFIG_NUMA_BALANCING
		sgs->nr_numa_running += rq->nr_numa_running;
		sgs->nr_preferred_running += rq->nr_preferred_running;
#पूर्ण_अगर
		/*
		 * No need to call idle_cpu() अगर nr_running is not 0
		 */
		अगर (!nr_running && idle_cpu(i)) अणु
			sgs->idle_cpus++;
			/* Idle cpu can't have misfit task */
			जारी;
		पूर्ण

		अगर (local_group)
			जारी;

		/* Check क्रम a misfit task on the cpu */
		अगर (env->sd->flags & SD_ASYM_CPUCAPACITY &&
		    sgs->group_misfit_task_load < rq->misfit_task_load) अणु
			sgs->group_misfit_task_load = rq->misfit_task_load;
			*sg_status |= SG_OVERLOAD;
		पूर्ण
	पूर्ण

	/* Check अगर dst CPU is idle and preferred to this group */
	अगर (env->sd->flags & SD_ASYM_PACKING &&
	    env->idle != CPU_NOT_IDLE &&
	    sgs->sum_h_nr_running &&
	    sched_asym_prefer(env->dst_cpu, group->asym_prefer_cpu)) अणु
		sgs->group_asym_packing = 1;
	पूर्ण

	sgs->group_capacity = group->sgc->capacity;

	sgs->group_weight = group->group_weight;

	sgs->group_type = group_classअगरy(env->sd->imbalance_pct, group, sgs);

	/* Computing avg_load makes sense only when group is overloaded */
	अगर (sgs->group_type == group_overloaded)
		sgs->avg_load = (sgs->group_load * SCHED_CAPACITY_SCALE) /
				sgs->group_capacity;
पूर्ण

/**
 * update_sd_pick_busiest - वापस 1 on busiest group
 * @env: The load balancing environment.
 * @sds: sched_करोमुख्य statistics
 * @sg: sched_group candidate to be checked क्रम being the busiest
 * @sgs: sched_group statistics
 *
 * Determine अगर @sg is a busier group than the previously selected
 * busiest group.
 *
 * Return: %true अगर @sg is a busier group than the previously selected
 * busiest group. %false otherwise.
 */
अटल bool update_sd_pick_busiest(काष्ठा lb_env *env,
				   काष्ठा sd_lb_stats *sds,
				   काष्ठा sched_group *sg,
				   काष्ठा sg_lb_stats *sgs)
अणु
	काष्ठा sg_lb_stats *busiest = &sds->busiest_stat;

	/* Make sure that there is at least one task to pull */
	अगर (!sgs->sum_h_nr_running)
		वापस false;

	/*
	 * Don't try to pull misfit tasks we can't help.
	 * We can use max_capacity here as reduction in capacity on some
	 * CPUs in the group should either be possible to resolve
	 * पूर्णांकernally or be covered by avg_load imbalance (eventually).
	 */
	अगर (sgs->group_type == group_misfit_task &&
	    (!capacity_greater(capacity_of(env->dst_cpu), sg->sgc->max_capacity) ||
	     sds->local_stat.group_type != group_has_spare))
		वापस false;

	अगर (sgs->group_type > busiest->group_type)
		वापस true;

	अगर (sgs->group_type < busiest->group_type)
		वापस false;

	/*
	 * The candidate and the current busiest group are the same type of
	 * group. Let check which one is the busiest according to the type.
	 */

	चयन (sgs->group_type) अणु
	हाल group_overloaded:
		/* Select the overloaded group with highest avg_load. */
		अगर (sgs->avg_load <= busiest->avg_load)
			वापस false;
		अवरोध;

	हाल group_imbalanced:
		/*
		 * Select the 1st imbalanced group as we करोn't have any way to
		 * choose one more than another.
		 */
		वापस false;

	हाल group_asym_packing:
		/* Prefer to move from lowest priority CPU's work */
		अगर (sched_asym_prefer(sg->asym_prefer_cpu, sds->busiest->asym_prefer_cpu))
			वापस false;
		अवरोध;

	हाल group_misfit_task:
		/*
		 * If we have more than one misfit sg go with the biggest
		 * misfit.
		 */
		अगर (sgs->group_misfit_task_load < busiest->group_misfit_task_load)
			वापस false;
		अवरोध;

	हाल group_fully_busy:
		/*
		 * Select the fully busy group with highest avg_load. In
		 * theory, there is no need to pull task from such kind of
		 * group because tasks have all compute capacity that they need
		 * but we can still improve the overall throughput by reducing
		 * contention when accessing shared HW resources.
		 *
		 * XXX क्रम now avg_load is not computed and always 0 so we
		 * select the 1st one.
		 */
		अगर (sgs->avg_load <= busiest->avg_load)
			वापस false;
		अवरोध;

	हाल group_has_spare:
		/*
		 * Select not overloaded group with lowest number of idle cpus
		 * and highest number of running tasks. We could also compare
		 * the spare capacity which is more stable but it can end up
		 * that the group has less spare capacity but finally more idle
		 * CPUs which means less opportunity to pull tasks.
		 */
		अगर (sgs->idle_cpus > busiest->idle_cpus)
			वापस false;
		अन्यथा अगर ((sgs->idle_cpus == busiest->idle_cpus) &&
			 (sgs->sum_nr_running <= busiest->sum_nr_running))
			वापस false;

		अवरोध;
	पूर्ण

	/*
	 * Candidate sg has no more than one task per CPU and has higher
	 * per-CPU capacity. Migrating tasks to less capable CPUs may harm
	 * throughput. Maximize throughput, घातer/energy consequences are not
	 * considered.
	 */
	अगर ((env->sd->flags & SD_ASYM_CPUCAPACITY) &&
	    (sgs->group_type <= group_fully_busy) &&
	    (capacity_greater(sg->sgc->min_capacity, capacity_of(env->dst_cpu))))
		वापस false;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
अटल अंतरभूत क्रमागत fbq_type fbq_classअगरy_group(काष्ठा sg_lb_stats *sgs)
अणु
	अगर (sgs->sum_h_nr_running > sgs->nr_numa_running)
		वापस regular;
	अगर (sgs->sum_h_nr_running > sgs->nr_preferred_running)
		वापस remote;
	वापस all;
पूर्ण

अटल अंतरभूत क्रमागत fbq_type fbq_classअगरy_rq(काष्ठा rq *rq)
अणु
	अगर (rq->nr_running > rq->nr_numa_running)
		वापस regular;
	अगर (rq->nr_running > rq->nr_preferred_running)
		वापस remote;
	वापस all;
पूर्ण
#अन्यथा
अटल अंतरभूत क्रमागत fbq_type fbq_classअगरy_group(काष्ठा sg_lb_stats *sgs)
अणु
	वापस all;
पूर्ण

अटल अंतरभूत क्रमागत fbq_type fbq_classअगरy_rq(काष्ठा rq *rq)
अणु
	वापस regular;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */


काष्ठा sg_lb_stats;

/*
 * task_running_on_cpu - वापस 1 अगर @p is running on @cpu.
 */

अटल अचिन्हित पूर्णांक task_running_on_cpu(पूर्णांक cpu, काष्ठा task_काष्ठा *p)
अणु
	/* Task has no contribution or is new */
	अगर (cpu != task_cpu(p) || !READ_ONCE(p->se.avg.last_update_समय))
		वापस 0;

	अगर (task_on_rq_queued(p))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * idle_cpu_without - would a given CPU be idle without p ?
 * @cpu: the processor on which idleness is tested.
 * @p: task which should be ignored.
 *
 * Return: 1 अगर the CPU would be idle. 0 otherwise.
 */
अटल पूर्णांक idle_cpu_without(पूर्णांक cpu, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	अगर (rq->curr != rq->idle && rq->curr != p)
		वापस 0;

	/*
	 * rq->nr_running can't be used but an updated version without the
	 * impact of p on cpu must be used instead. The updated nr_running
	 * be computed and tested beक्रमe calling idle_cpu_without().
	 */

#अगर_घोषित CONFIG_SMP
	अगर (rq->ttwu_pending)
		वापस 0;
#पूर्ण_अगर

	वापस 1;
पूर्ण

/*
 * update_sg_wakeup_stats - Update sched_group's statistics क्रम wakeup.
 * @sd: The sched_करोमुख्य level to look क्रम idlest group.
 * @group: sched_group whose statistics are to be updated.
 * @sgs: variable to hold the statistics क्रम this group.
 * @p: The task क्रम which we look क्रम the idlest group/CPU.
 */
अटल अंतरभूत व्योम update_sg_wakeup_stats(काष्ठा sched_करोमुख्य *sd,
					  काष्ठा sched_group *group,
					  काष्ठा sg_lb_stats *sgs,
					  काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक i, nr_running;

	स_रखो(sgs, 0, माप(*sgs));

	क्रम_each_cpu(i, sched_group_span(group)) अणु
		काष्ठा rq *rq = cpu_rq(i);
		अचिन्हित पूर्णांक local;

		sgs->group_load += cpu_load_without(rq, p);
		sgs->group_util += cpu_util_without(i, p);
		sgs->group_runnable += cpu_runnable_without(rq, p);
		local = task_running_on_cpu(i, p);
		sgs->sum_h_nr_running += rq->cfs.h_nr_running - local;

		nr_running = rq->nr_running - local;
		sgs->sum_nr_running += nr_running;

		/*
		 * No need to call idle_cpu_without() अगर nr_running is not 0
		 */
		अगर (!nr_running && idle_cpu_without(i, p))
			sgs->idle_cpus++;

	पूर्ण

	/* Check अगर task fits in the group */
	अगर (sd->flags & SD_ASYM_CPUCAPACITY &&
	    !task_fits_capacity(p, group->sgc->max_capacity)) अणु
		sgs->group_misfit_task_load = 1;
	पूर्ण

	sgs->group_capacity = group->sgc->capacity;

	sgs->group_weight = group->group_weight;

	sgs->group_type = group_classअगरy(sd->imbalance_pct, group, sgs);

	/*
	 * Computing avg_load makes sense only when group is fully busy or
	 * overloaded
	 */
	अगर (sgs->group_type == group_fully_busy ||
		sgs->group_type == group_overloaded)
		sgs->avg_load = (sgs->group_load * SCHED_CAPACITY_SCALE) /
				sgs->group_capacity;
पूर्ण

अटल bool update_pick_idlest(काष्ठा sched_group *idlest,
			       काष्ठा sg_lb_stats *idlest_sgs,
			       काष्ठा sched_group *group,
			       काष्ठा sg_lb_stats *sgs)
अणु
	अगर (sgs->group_type < idlest_sgs->group_type)
		वापस true;

	अगर (sgs->group_type > idlest_sgs->group_type)
		वापस false;

	/*
	 * The candidate and the current idlest group are the same type of
	 * group. Let check which one is the idlest according to the type.
	 */

	चयन (sgs->group_type) अणु
	हाल group_overloaded:
	हाल group_fully_busy:
		/* Select the group with lowest avg_load. */
		अगर (idlest_sgs->avg_load <= sgs->avg_load)
			वापस false;
		अवरोध;

	हाल group_imbalanced:
	हाल group_asym_packing:
		/* Those types are not used in the slow wakeup path */
		वापस false;

	हाल group_misfit_task:
		/* Select group with the highest max capacity */
		अगर (idlest->sgc->max_capacity >= group->sgc->max_capacity)
			वापस false;
		अवरोध;

	हाल group_has_spare:
		/* Select group with most idle CPUs */
		अगर (idlest_sgs->idle_cpus > sgs->idle_cpus)
			वापस false;

		/* Select group with lowest group_util */
		अगर (idlest_sgs->idle_cpus == sgs->idle_cpus &&
			idlest_sgs->group_util <= sgs->group_util)
			वापस false;

		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Allow a NUMA imbalance अगर busy CPUs is less than 25% of the करोमुख्य.
 * This is an approximation as the number of running tasks may not be
 * related to the number of busy CPUs due to sched_setaffinity.
 */
अटल अंतरभूत bool allow_numa_imbalance(पूर्णांक dst_running, पूर्णांक dst_weight)
अणु
	वापस (dst_running < (dst_weight >> 2));
पूर्ण

/*
 * find_idlest_group() finds and वापसs the least busy CPU group within the
 * करोमुख्य.
 *
 * Assumes p is allowed on at least one CPU in sd.
 */
अटल काष्ठा sched_group *
find_idlest_group(काष्ठा sched_करोमुख्य *sd, काष्ठा task_काष्ठा *p, पूर्णांक this_cpu)
अणु
	काष्ठा sched_group *idlest = शून्य, *local = शून्य, *group = sd->groups;
	काष्ठा sg_lb_stats local_sgs, पंचांगp_sgs;
	काष्ठा sg_lb_stats *sgs;
	अचिन्हित दीर्घ imbalance;
	काष्ठा sg_lb_stats idlest_sgs = अणु
			.avg_load = अच_पूर्णांक_उच्च,
			.group_type = group_overloaded,
	पूर्ण;

	करो अणु
		पूर्णांक local_group;

		/* Skip over this group अगर it has no CPUs allowed */
		अगर (!cpumask_पूर्णांकersects(sched_group_span(group),
					p->cpus_ptr))
			जारी;

		local_group = cpumask_test_cpu(this_cpu,
					       sched_group_span(group));

		अगर (local_group) अणु
			sgs = &local_sgs;
			local = group;
		पूर्ण अन्यथा अणु
			sgs = &पंचांगp_sgs;
		पूर्ण

		update_sg_wakeup_stats(sd, group, sgs, p);

		अगर (!local_group && update_pick_idlest(idlest, &idlest_sgs, group, sgs)) अणु
			idlest = group;
			idlest_sgs = *sgs;
		पूर्ण

	पूर्ण जबतक (group = group->next, group != sd->groups);


	/* There is no idlest group to push tasks to */
	अगर (!idlest)
		वापस शून्य;

	/* The local group has been skipped because of CPU affinity */
	अगर (!local)
		वापस idlest;

	/*
	 * If the local group is idler than the selected idlest group
	 * करोn't try and push the task.
	 */
	अगर (local_sgs.group_type < idlest_sgs.group_type)
		वापस शून्य;

	/*
	 * If the local group is busier than the selected idlest group
	 * try and push the task.
	 */
	अगर (local_sgs.group_type > idlest_sgs.group_type)
		वापस idlest;

	चयन (local_sgs.group_type) अणु
	हाल group_overloaded:
	हाल group_fully_busy:

		/* Calculate allowed imbalance based on load */
		imbalance = scale_load_करोwn(NICE_0_LOAD) *
				(sd->imbalance_pct-100) / 100;

		/*
		 * When comparing groups across NUMA करोमुख्यs, it's possible क्रम
		 * the local करोमुख्य to be very lightly loaded relative to the
		 * remote करोमुख्यs but "imbalance" skews the comparison making
		 * remote CPUs look much more favourable. When considering
		 * cross-करोमुख्य, add imbalance to the load on the remote node
		 * and consider staying local.
		 */

		अगर ((sd->flags & SD_NUMA) &&
		    ((idlest_sgs.avg_load + imbalance) >= local_sgs.avg_load))
			वापस शून्य;

		/*
		 * If the local group is less loaded than the selected
		 * idlest group करोn't try and push any tasks.
		 */
		अगर (idlest_sgs.avg_load >= (local_sgs.avg_load + imbalance))
			वापस शून्य;

		अगर (100 * local_sgs.avg_load <= sd->imbalance_pct * idlest_sgs.avg_load)
			वापस शून्य;
		अवरोध;

	हाल group_imbalanced:
	हाल group_asym_packing:
		/* Those type are not used in the slow wakeup path */
		वापस शून्य;

	हाल group_misfit_task:
		/* Select group with the highest max capacity */
		अगर (local->sgc->max_capacity >= idlest->sgc->max_capacity)
			वापस शून्य;
		अवरोध;

	हाल group_has_spare:
		अगर (sd->flags & SD_NUMA) अणु
#अगर_घोषित CONFIG_NUMA_BALANCING
			पूर्णांक idlest_cpu;
			/*
			 * If there is spare capacity at NUMA, try to select
			 * the preferred node
			 */
			अगर (cpu_to_node(this_cpu) == p->numa_preferred_nid)
				वापस शून्य;

			idlest_cpu = cpumask_first(sched_group_span(idlest));
			अगर (cpu_to_node(idlest_cpu) == p->numa_preferred_nid)
				वापस idlest;
#पूर्ण_अगर
			/*
			 * Otherwise, keep the task on this node to stay बंद
			 * its wakeup source and improve locality. If there is
			 * a real need of migration, periodic load balance will
			 * take care of it.
			 */
			अगर (allow_numa_imbalance(local_sgs.sum_nr_running, sd->span_weight))
				वापस शून्य;
		पूर्ण

		/*
		 * Select group with highest number of idle CPUs. We could also
		 * compare the utilization which is more stable but it can end
		 * up that the group has less spare capacity but finally more
		 * idle CPUs which means more opportunity to run task.
		 */
		अगर (local_sgs.idle_cpus >= idlest_sgs.idle_cpus)
			वापस शून्य;
		अवरोध;
	पूर्ण

	वापस idlest;
पूर्ण

/**
 * update_sd_lb_stats - Update sched_करोमुख्य's statistics क्रम load balancing.
 * @env: The load balancing environment.
 * @sds: variable to hold the statistics क्रम this sched_करोमुख्य.
 */

अटल अंतरभूत व्योम update_sd_lb_stats(काष्ठा lb_env *env, काष्ठा sd_lb_stats *sds)
अणु
	काष्ठा sched_करोमुख्य *child = env->sd->child;
	काष्ठा sched_group *sg = env->sd->groups;
	काष्ठा sg_lb_stats *local = &sds->local_stat;
	काष्ठा sg_lb_stats पंचांगp_sgs;
	पूर्णांक sg_status = 0;

	करो अणु
		काष्ठा sg_lb_stats *sgs = &पंचांगp_sgs;
		पूर्णांक local_group;

		local_group = cpumask_test_cpu(env->dst_cpu, sched_group_span(sg));
		अगर (local_group) अणु
			sds->local = sg;
			sgs = local;

			अगर (env->idle != CPU_NEWLY_IDLE ||
			    समय_after_eq(jअगरfies, sg->sgc->next_update))
				update_group_capacity(env->sd, env->dst_cpu);
		पूर्ण

		update_sg_lb_stats(env, sg, sgs, &sg_status);

		अगर (local_group)
			जाओ next_group;


		अगर (update_sd_pick_busiest(env, sds, sg, sgs)) अणु
			sds->busiest = sg;
			sds->busiest_stat = *sgs;
		पूर्ण

next_group:
		/* Now, start updating sd_lb_stats */
		sds->total_load += sgs->group_load;
		sds->total_capacity += sgs->group_capacity;

		sg = sg->next;
	पूर्ण जबतक (sg != env->sd->groups);

	/* Tag करोमुख्य that child करोमुख्य prefers tasks go to siblings first */
	sds->prefer_sibling = child && child->flags & SD_PREFER_SIBLING;


	अगर (env->sd->flags & SD_NUMA)
		env->fbq_type = fbq_classअगरy_group(&sds->busiest_stat);

	अगर (!env->sd->parent) अणु
		काष्ठा root_करोमुख्य *rd = env->dst_rq->rd;

		/* update overload indicator अगर we are at root करोमुख्य */
		WRITE_ONCE(rd->overload, sg_status & SG_OVERLOAD);

		/* Update over-utilization (tipping poपूर्णांक, U >= 0) indicator */
		WRITE_ONCE(rd->overutilized, sg_status & SG_OVERUTILIZED);
		trace_sched_overutilized_tp(rd, sg_status & SG_OVERUTILIZED);
	पूर्ण अन्यथा अगर (sg_status & SG_OVERUTILIZED) अणु
		काष्ठा root_करोमुख्य *rd = env->dst_rq->rd;

		WRITE_ONCE(rd->overutilized, SG_OVERUTILIZED);
		trace_sched_overutilized_tp(rd, SG_OVERUTILIZED);
	पूर्ण
पूर्ण

#घोषणा NUMA_IMBALANCE_MIN 2

अटल अंतरभूत दीर्घ adjust_numa_imbalance(पूर्णांक imbalance,
				पूर्णांक dst_running, पूर्णांक dst_weight)
अणु
	अगर (!allow_numa_imbalance(dst_running, dst_weight))
		वापस imbalance;

	/*
	 * Allow a small imbalance based on a simple pair of communicating
	 * tasks that reमुख्य local when the destination is lightly loaded.
	 */
	अगर (imbalance <= NUMA_IMBALANCE_MIN)
		वापस 0;

	वापस imbalance;
पूर्ण

/**
 * calculate_imbalance - Calculate the amount of imbalance present within the
 *			 groups of a given sched_करोमुख्य during load balance.
 * @env: load balance environment
 * @sds: statistics of the sched_करोमुख्य whose imbalance is to be calculated.
 */
अटल अंतरभूत व्योम calculate_imbalance(काष्ठा lb_env *env, काष्ठा sd_lb_stats *sds)
अणु
	काष्ठा sg_lb_stats *local, *busiest;

	local = &sds->local_stat;
	busiest = &sds->busiest_stat;

	अगर (busiest->group_type == group_misfit_task) अणु
		/* Set imbalance to allow misfit tasks to be balanced. */
		env->migration_type = migrate_misfit;
		env->imbalance = 1;
		वापस;
	पूर्ण

	अगर (busiest->group_type == group_asym_packing) अणु
		/*
		 * In हाल of asym capacity, we will try to migrate all load to
		 * the preferred CPU.
		 */
		env->migration_type = migrate_task;
		env->imbalance = busiest->sum_h_nr_running;
		वापस;
	पूर्ण

	अगर (busiest->group_type == group_imbalanced) अणु
		/*
		 * In the group_imb हाल we cannot rely on group-wide averages
		 * to ensure CPU-load equilibrium, try to move any task to fix
		 * the imbalance. The next load balance will take care of
		 * balancing back the प्रणाली.
		 */
		env->migration_type = migrate_task;
		env->imbalance = 1;
		वापस;
	पूर्ण

	/*
	 * Try to use spare capacity of local group without overloading it or
	 * emptying busiest.
	 */
	अगर (local->group_type == group_has_spare) अणु
		अगर ((busiest->group_type > group_fully_busy) &&
		    !(env->sd->flags & SD_SHARE_PKG_RESOURCES)) अणु
			/*
			 * If busiest is overloaded, try to fill spare
			 * capacity. This might end up creating spare capacity
			 * in busiest or busiest still being overloaded but
			 * there is no simple way to directly compute the
			 * amount of load to migrate in order to balance the
			 * प्रणाली.
			 */
			env->migration_type = migrate_util;
			env->imbalance = max(local->group_capacity, local->group_util) -
					 local->group_util;

			/*
			 * In some हालs, the group's utilization is max or even
			 * higher than capacity because of migrations but the
			 * local CPU is (newly) idle. There is at least one
			 * रुकोing task in this overloaded busiest group. Let's
			 * try to pull it.
			 */
			अगर (env->idle != CPU_NOT_IDLE && env->imbalance == 0) अणु
				env->migration_type = migrate_task;
				env->imbalance = 1;
			पूर्ण

			वापस;
		पूर्ण

		अगर (busiest->group_weight == 1 || sds->prefer_sibling) अणु
			अचिन्हित पूर्णांक nr_dअगरf = busiest->sum_nr_running;
			/*
			 * When prefer sibling, evenly spपढ़ो running tasks on
			 * groups.
			 */
			env->migration_type = migrate_task;
			lsub_positive(&nr_dअगरf, local->sum_nr_running);
			env->imbalance = nr_dअगरf >> 1;
		पूर्ण अन्यथा अणु

			/*
			 * If there is no overload, we just want to even the number of
			 * idle cpus.
			 */
			env->migration_type = migrate_task;
			env->imbalance = max_t(दीर्घ, 0, (local->idle_cpus -
						 busiest->idle_cpus) >> 1);
		पूर्ण

		/* Consider allowing a small imbalance between NUMA groups */
		अगर (env->sd->flags & SD_NUMA) अणु
			env->imbalance = adjust_numa_imbalance(env->imbalance,
				busiest->sum_nr_running, busiest->group_weight);
		पूर्ण

		वापस;
	पूर्ण

	/*
	 * Local is fully busy but has to take more load to relieve the
	 * busiest group
	 */
	अगर (local->group_type < group_overloaded) अणु
		/*
		 * Local will become overloaded so the avg_load metrics are
		 * finally needed.
		 */

		local->avg_load = (local->group_load * SCHED_CAPACITY_SCALE) /
				  local->group_capacity;

		sds->avg_load = (sds->total_load * SCHED_CAPACITY_SCALE) /
				sds->total_capacity;
		/*
		 * If the local group is more loaded than the selected
		 * busiest group करोn't try to pull any tasks.
		 */
		अगर (local->avg_load >= busiest->avg_load) अणु
			env->imbalance = 0;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Both group are or will become overloaded and we're trying to get all
	 * the CPUs to the average_load, so we करोn't want to push ourselves
	 * above the average load, nor करो we wish to reduce the max loaded CPU
	 * below the average load. At the same समय, we also करोn't want to
	 * reduce the group load below the group capacity. Thus we look क्रम
	 * the minimum possible imbalance.
	 */
	env->migration_type = migrate_load;
	env->imbalance = min(
		(busiest->avg_load - sds->avg_load) * busiest->group_capacity,
		(sds->avg_load - local->avg_load) * local->group_capacity
	) / SCHED_CAPACITY_SCALE;
पूर्ण

/******* find_busiest_group() helpers end here *********************/

/*
 * Decision matrix according to the local and busiest group type:
 *
 * busiest \ local has_spare fully_busy misfit asym imbalanced overloaded
 * has_spare        nr_idle   balanced   N/A    N/A  balanced   balanced
 * fully_busy       nr_idle   nr_idle    N/A    N/A  balanced   balanced
 * misfit_task      क्रमce     N/A        N/A    N/A  क्रमce      क्रमce
 * asym_packing     क्रमce     क्रमce      N/A    N/A  क्रमce      क्रमce
 * imbalanced       क्रमce     क्रमce      N/A    N/A  क्रमce      क्रमce
 * overloaded       क्रमce     क्रमce      N/A    N/A  क्रमce      avg_load
 *
 * N/A :      Not Applicable because alपढ़ोy filtered जबतक updating
 *            statistics.
 * balanced : The प्रणाली is balanced क्रम these 2 groups.
 * क्रमce :    Calculate the imbalance as load migration is probably needed.
 * avg_load : Only अगर imbalance is signअगरicant enough.
 * nr_idle :  dst_cpu is not busy and the number of idle CPUs is quite
 *            dअगरferent in groups.
 */

/**
 * find_busiest_group - Returns the busiest group within the sched_करोमुख्य
 * अगर there is an imbalance.
 *
 * Also calculates the amount of runnable load which should be moved
 * to restore balance.
 *
 * @env: The load balancing environment.
 *
 * Return:	- The busiest group अगर imbalance exists.
 */
अटल काष्ठा sched_group *find_busiest_group(काष्ठा lb_env *env)
अणु
	काष्ठा sg_lb_stats *local, *busiest;
	काष्ठा sd_lb_stats sds;

	init_sd_lb_stats(&sds);

	/*
	 * Compute the various statistics relevant क्रम load balancing at
	 * this level.
	 */
	update_sd_lb_stats(env, &sds);

	अगर (sched_energy_enabled()) अणु
		काष्ठा root_करोमुख्य *rd = env->dst_rq->rd;

		अगर (rcu_dereference(rd->pd) && !READ_ONCE(rd->overutilized))
			जाओ out_balanced;
	पूर्ण

	local = &sds.local_stat;
	busiest = &sds.busiest_stat;

	/* There is no busy sibling group to pull tasks from */
	अगर (!sds.busiest)
		जाओ out_balanced;

	/* Misfit tasks should be dealt with regardless of the avg load */
	अगर (busiest->group_type == group_misfit_task)
		जाओ क्रमce_balance;

	/* ASYM feature bypasses nice load balance check */
	अगर (busiest->group_type == group_asym_packing)
		जाओ क्रमce_balance;

	/*
	 * If the busiest group is imbalanced the below checks करोn't
	 * work because they assume all things are equal, which typically
	 * isn't true due to cpus_ptr स्थिरraपूर्णांकs and the like.
	 */
	अगर (busiest->group_type == group_imbalanced)
		जाओ क्रमce_balance;

	/*
	 * If the local group is busier than the selected busiest group
	 * करोn't try and pull any tasks.
	 */
	अगर (local->group_type > busiest->group_type)
		जाओ out_balanced;

	/*
	 * When groups are overloaded, use the avg_load to ensure fairness
	 * between tasks.
	 */
	अगर (local->group_type == group_overloaded) अणु
		/*
		 * If the local group is more loaded than the selected
		 * busiest group करोn't try to pull any tasks.
		 */
		अगर (local->avg_load >= busiest->avg_load)
			जाओ out_balanced;

		/* XXX broken क्रम overlapping NUMA groups */
		sds.avg_load = (sds.total_load * SCHED_CAPACITY_SCALE) /
				sds.total_capacity;

		/*
		 * Don't pull any tasks अगर this group is alपढ़ोy above the
		 * करोमुख्य average load.
		 */
		अगर (local->avg_load >= sds.avg_load)
			जाओ out_balanced;

		/*
		 * If the busiest group is more loaded, use imbalance_pct to be
		 * conservative.
		 */
		अगर (100 * busiest->avg_load <=
				env->sd->imbalance_pct * local->avg_load)
			जाओ out_balanced;
	पूर्ण

	/* Try to move all excess tasks to child's sibling करोमुख्य */
	अगर (sds.prefer_sibling && local->group_type == group_has_spare &&
	    busiest->sum_nr_running > local->sum_nr_running + 1)
		जाओ क्रमce_balance;

	अगर (busiest->group_type != group_overloaded) अणु
		अगर (env->idle == CPU_NOT_IDLE)
			/*
			 * If the busiest group is not overloaded (and as a
			 * result the local one too) but this CPU is alपढ़ोy
			 * busy, let another idle CPU try to pull task.
			 */
			जाओ out_balanced;

		अगर (busiest->group_weight > 1 &&
		    local->idle_cpus <= (busiest->idle_cpus + 1))
			/*
			 * If the busiest group is not overloaded
			 * and there is no imbalance between this and busiest
			 * group wrt idle CPUs, it is balanced. The imbalance
			 * becomes signअगरicant अगर the dअगरf is greater than 1
			 * otherwise we might end up to just move the imbalance
			 * on another group. Of course this applies only अगर
			 * there is more than 1 CPU per group.
			 */
			जाओ out_balanced;

		अगर (busiest->sum_h_nr_running == 1)
			/*
			 * busiest करोesn't have any tasks रुकोing to run
			 */
			जाओ out_balanced;
	पूर्ण

क्रमce_balance:
	/* Looks like there is an imbalance. Compute it */
	calculate_imbalance(env, &sds);
	वापस env->imbalance ? sds.busiest : शून्य;

out_balanced:
	env->imbalance = 0;
	वापस शून्य;
पूर्ण

/*
 * find_busiest_queue - find the busiest runqueue among the CPUs in the group.
 */
अटल काष्ठा rq *find_busiest_queue(काष्ठा lb_env *env,
				     काष्ठा sched_group *group)
अणु
	काष्ठा rq *busiest = शून्य, *rq;
	अचिन्हित दीर्घ busiest_util = 0, busiest_load = 0, busiest_capacity = 1;
	अचिन्हित पूर्णांक busiest_nr = 0;
	पूर्णांक i;

	क्रम_each_cpu_and(i, sched_group_span(group), env->cpus) अणु
		अचिन्हित दीर्घ capacity, load, util;
		अचिन्हित पूर्णांक nr_running;
		क्रमागत fbq_type rt;

		rq = cpu_rq(i);
		rt = fbq_classअगरy_rq(rq);

		/*
		 * We classअगरy groups/runqueues पूर्णांकo three groups:
		 *  - regular: there are !numa tasks
		 *  - remote:  there are numa tasks that run on the 'wrong' node
		 *  - all:     there is no distinction
		 *
		 * In order to aव्योम migrating ideally placed numa tasks,
		 * ignore those when there's better options.
		 *
		 * If we ignore the actual busiest queue to migrate another
		 * task, the next balance pass can still reduce the busiest
		 * queue by moving tasks around inside the node.
		 *
		 * If we cannot move enough load due to this classअगरication
		 * the next pass will adjust the group classअगरication and
		 * allow migration of more tasks.
		 *
		 * Both हालs only affect the total convergence complनिकासy.
		 */
		अगर (rt > env->fbq_type)
			जारी;

		nr_running = rq->cfs.h_nr_running;
		अगर (!nr_running)
			जारी;

		capacity = capacity_of(i);

		/*
		 * For ASYM_CPUCAPACITY करोमुख्यs, करोn't pick a CPU that could
		 * eventually lead to active_balancing high->low capacity.
		 * Higher per-CPU capacity is considered better than balancing
		 * average load.
		 */
		अगर (env->sd->flags & SD_ASYM_CPUCAPACITY &&
		    !capacity_greater(capacity_of(env->dst_cpu), capacity) &&
		    nr_running == 1)
			जारी;

		चयन (env->migration_type) अणु
		हाल migrate_load:
			/*
			 * When comparing with load imbalance, use cpu_load()
			 * which is not scaled with the CPU capacity.
			 */
			load = cpu_load(rq);

			अगर (nr_running == 1 && load > env->imbalance &&
			    !check_cpu_capacity(rq, env->sd))
				अवरोध;

			/*
			 * For the load comparisons with the other CPUs,
			 * consider the cpu_load() scaled with the CPU
			 * capacity, so that the load can be moved away
			 * from the CPU that is potentially running at a
			 * lower capacity.
			 *
			 * Thus we're looking क्रम max(load_i / capacity_i),
			 * crosswise multiplication to rid ourselves of the
			 * भागision works out to:
			 * load_i * capacity_j > load_j * capacity_i;
			 * where j is our previous maximum.
			 */
			अगर (load * busiest_capacity > busiest_load * capacity) अणु
				busiest_load = load;
				busiest_capacity = capacity;
				busiest = rq;
			पूर्ण
			अवरोध;

		हाल migrate_util:
			util = cpu_util(cpu_of(rq));

			/*
			 * Don't try to pull utilization from a CPU with one
			 * running task. Whatever its utilization, we will fail
			 * detach the task.
			 */
			अगर (nr_running <= 1)
				जारी;

			अगर (busiest_util < util) अणु
				busiest_util = util;
				busiest = rq;
			पूर्ण
			अवरोध;

		हाल migrate_task:
			अगर (busiest_nr < nr_running) अणु
				busiest_nr = nr_running;
				busiest = rq;
			पूर्ण
			अवरोध;

		हाल migrate_misfit:
			/*
			 * For ASYM_CPUCAPACITY करोमुख्यs with misfit tasks we
			 * simply seek the "biggest" misfit task.
			 */
			अगर (rq->misfit_task_load > busiest_load) अणु
				busiest_load = rq->misfit_task_load;
				busiest = rq;
			पूर्ण

			अवरोध;

		पूर्ण
	पूर्ण

	वापस busiest;
पूर्ण

/*
 * Max backoff अगर we encounter pinned tasks. Pretty arbitrary value, but
 * so दीर्घ as it is large enough.
 */
#घोषणा MAX_PINNED_INTERVAL	512

अटल अंतरभूत bool
asym_active_balance(काष्ठा lb_env *env)
अणु
	/*
	 * ASYM_PACKING needs to क्रमce migrate tasks from busy but
	 * lower priority CPUs in order to pack all tasks in the
	 * highest priority CPUs.
	 */
	वापस env->idle != CPU_NOT_IDLE && (env->sd->flags & SD_ASYM_PACKING) &&
	       sched_asym_prefer(env->dst_cpu, env->src_cpu);
पूर्ण

अटल अंतरभूत bool
imbalanced_active_balance(काष्ठा lb_env *env)
अणु
	काष्ठा sched_करोमुख्य *sd = env->sd;

	/*
	 * The imbalanced हाल includes the हाल of pinned tasks preventing a fair
	 * distribution of the load on the प्रणाली but also the even distribution of the
	 * thपढ़ोs on a प्रणाली with spare capacity
	 */
	अगर ((env->migration_type == migrate_task) &&
	    (sd->nr_balance_failed > sd->cache_nice_tries+2))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक need_active_balance(काष्ठा lb_env *env)
अणु
	काष्ठा sched_करोमुख्य *sd = env->sd;

	अगर (asym_active_balance(env))
		वापस 1;

	अगर (imbalanced_active_balance(env))
		वापस 1;

	/*
	 * The dst_cpu is idle and the src_cpu CPU has only 1 CFS task.
	 * It's worth migrating the task if the src_cpu's capacity is reduced
	 * because of other sched_class or IRQs अगर more capacity stays
	 * available on dst_cpu.
	 */
	अगर ((env->idle != CPU_NOT_IDLE) &&
	    (env->src_rq->cfs.h_nr_running == 1)) अणु
		अगर ((check_cpu_capacity(env->src_rq, sd)) &&
		    (capacity_of(env->src_cpu)*sd->imbalance_pct < capacity_of(env->dst_cpu)*100))
			वापस 1;
	पूर्ण

	अगर (env->migration_type == migrate_misfit)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक active_load_balance_cpu_stop(व्योम *data);

अटल पूर्णांक should_we_balance(काष्ठा lb_env *env)
अणु
	काष्ठा sched_group *sg = env->sd->groups;
	पूर्णांक cpu;

	/*
	 * Ensure the balancing environment is consistent; can happen
	 * when the softirq triggers 'during' hotplug.
	 */
	अगर (!cpumask_test_cpu(env->dst_cpu, env->cpus))
		वापस 0;

	/*
	 * In the newly idle हाल, we will allow all the CPUs
	 * to करो the newly idle load balance.
	 */
	अगर (env->idle == CPU_NEWLY_IDLE)
		वापस 1;

	/* Try to find first idle CPU */
	क्रम_each_cpu_and(cpu, group_balance_mask(sg), env->cpus) अणु
		अगर (!idle_cpu(cpu))
			जारी;

		/* Are we the first idle CPU? */
		वापस cpu == env->dst_cpu;
	पूर्ण

	/* Are we the first CPU of this group ? */
	वापस group_balance_cpu(sg) == env->dst_cpu;
पूर्ण

/*
 * Check this_cpu to ensure it is balanced within करोमुख्य. Attempt to move
 * tasks अगर there is an imbalance.
 */
अटल पूर्णांक load_balance(पूर्णांक this_cpu, काष्ठा rq *this_rq,
			काष्ठा sched_करोमुख्य *sd, क्रमागत cpu_idle_type idle,
			पूर्णांक *जारी_balancing)
अणु
	पूर्णांक ld_moved, cur_ld_moved, active_balance = 0;
	काष्ठा sched_करोमुख्य *sd_parent = sd->parent;
	काष्ठा sched_group *group;
	काष्ठा rq *busiest;
	काष्ठा rq_flags rf;
	काष्ठा cpumask *cpus = this_cpu_cpumask_var_ptr(load_balance_mask);

	काष्ठा lb_env env = अणु
		.sd		= sd,
		.dst_cpu	= this_cpu,
		.dst_rq		= this_rq,
		.dst_grpmask    = sched_group_span(sd->groups),
		.idle		= idle,
		.loop_अवरोध	= sched_nr_migrate_अवरोध,
		.cpus		= cpus,
		.fbq_type	= all,
		.tasks		= LIST_HEAD_INIT(env.tasks),
	पूर्ण;

	cpumask_and(cpus, sched_करोमुख्य_span(sd), cpu_active_mask);

	schedstat_inc(sd->lb_count[idle]);

reकरो:
	अगर (!should_we_balance(&env)) अणु
		*जारी_balancing = 0;
		जाओ out_balanced;
	पूर्ण

	group = find_busiest_group(&env);
	अगर (!group) अणु
		schedstat_inc(sd->lb_nobusyg[idle]);
		जाओ out_balanced;
	पूर्ण

	busiest = find_busiest_queue(&env, group);
	अगर (!busiest) अणु
		schedstat_inc(sd->lb_nobusyq[idle]);
		जाओ out_balanced;
	पूर्ण

	BUG_ON(busiest == env.dst_rq);

	schedstat_add(sd->lb_imbalance[idle], env.imbalance);

	env.src_cpu = busiest->cpu;
	env.src_rq = busiest;

	ld_moved = 0;
	/* Clear this flag as soon as we find a pullable task */
	env.flags |= LBF_ALL_PINNED;
	अगर (busiest->nr_running > 1) अणु
		/*
		 * Attempt to move tasks. If find_busiest_group has found
		 * an imbalance but busiest->nr_running <= 1, the group is
		 * still unbalanced. ld_moved simply stays zero, so it is
		 * correctly treated as an imbalance.
		 */
		env.loop_max  = min(sysctl_sched_nr_migrate, busiest->nr_running);

more_balance:
		rq_lock_irqsave(busiest, &rf);
		update_rq_घड़ी(busiest);

		/*
		 * cur_ld_moved - load moved in current iteration
		 * ld_moved     - cumulative load moved across iterations
		 */
		cur_ld_moved = detach_tasks(&env);

		/*
		 * We've detached some tasks from busiest_rq. Every
		 * task is masked "TASK_ON_RQ_MIGRATING", so we can safely
		 * unlock busiest->lock, and we are able to be sure
		 * that nobody can manipulate the tasks in parallel.
		 * See task_rq_lock() family क्रम the details.
		 */

		rq_unlock(busiest, &rf);

		अगर (cur_ld_moved) अणु
			attach_tasks(&env);
			ld_moved += cur_ld_moved;
		पूर्ण

		local_irq_restore(rf.flags);

		अगर (env.flags & LBF_NEED_BREAK) अणु
			env.flags &= ~LBF_NEED_BREAK;
			जाओ more_balance;
		पूर्ण

		/*
		 * Revisit (affine) tasks on src_cpu that couldn't be moved to
		 * us and move them to an alternate dst_cpu in our sched_group
		 * where they can run. The upper limit on how many बार we
		 * iterate on same src_cpu is dependent on number of CPUs in our
		 * sched_group.
		 *
		 * This changes load balance semantics a bit on who can move
		 * load to a given_cpu. In addition to the given_cpu itself
		 * (or a ilb_cpu acting on its behalf where given_cpu is
		 * nohz-idle), we now have balance_cpu in a position to move
		 * load to given_cpu. In rare situations, this may cause
		 * conflicts (balance_cpu and given_cpu/ilb_cpu deciding
		 * _independently_ and at _same_ समय to move some load to
		 * given_cpu) causing excess load to be moved to given_cpu.
		 * This however should not happen so much in practice and
		 * moreover subsequent load balance cycles should correct the
		 * excess load moved.
		 */
		अगर ((env.flags & LBF_DST_PINNED) && env.imbalance > 0) अणु

			/* Prevent to re-select dst_cpu via env's CPUs */
			__cpumask_clear_cpu(env.dst_cpu, env.cpus);

			env.dst_rq	 = cpu_rq(env.new_dst_cpu);
			env.dst_cpu	 = env.new_dst_cpu;
			env.flags	&= ~LBF_DST_PINNED;
			env.loop	 = 0;
			env.loop_अवरोध	 = sched_nr_migrate_अवरोध;

			/*
			 * Go back to "more_balance" rather than "redo" since we
			 * need to जारी with same src_cpu.
			 */
			जाओ more_balance;
		पूर्ण

		/*
		 * We failed to reach balance because of affinity.
		 */
		अगर (sd_parent) अणु
			पूर्णांक *group_imbalance = &sd_parent->groups->sgc->imbalance;

			अगर ((env.flags & LBF_SOME_PINNED) && env.imbalance > 0)
				*group_imbalance = 1;
		पूर्ण

		/* All tasks on this runqueue were pinned by CPU affinity */
		अगर (unlikely(env.flags & LBF_ALL_PINNED)) अणु
			__cpumask_clear_cpu(cpu_of(busiest), cpus);
			/*
			 * Attempting to जारी load balancing at the current
			 * sched_करोमुख्य level only makes sense अगर there are
			 * active CPUs reमुख्यing as possible busiest CPUs to
			 * pull load from which are not contained within the
			 * destination group that is receiving any migrated
			 * load.
			 */
			अगर (!cpumask_subset(cpus, env.dst_grpmask)) अणु
				env.loop = 0;
				env.loop_अवरोध = sched_nr_migrate_अवरोध;
				जाओ reकरो;
			पूर्ण
			जाओ out_all_pinned;
		पूर्ण
	पूर्ण

	अगर (!ld_moved) अणु
		schedstat_inc(sd->lb_failed[idle]);
		/*
		 * Increment the failure counter only on periodic balance.
		 * We करो not want newidle balance, which can be very
		 * frequent, pollute the failure counter causing
		 * excessive cache_hot migrations and active balances.
		 */
		अगर (idle != CPU_NEWLY_IDLE)
			sd->nr_balance_failed++;

		अगर (need_active_balance(&env)) अणु
			अचिन्हित दीर्घ flags;

			raw_spin_lock_irqsave(&busiest->lock, flags);

			/*
			 * Don't kick the active_load_balance_cpu_stop,
			 * अगर the curr task on busiest CPU can't be
			 * moved to this_cpu:
			 */
			अगर (!cpumask_test_cpu(this_cpu, busiest->curr->cpus_ptr)) अणु
				raw_spin_unlock_irqrestore(&busiest->lock,
							    flags);
				जाओ out_one_pinned;
			पूर्ण

			/* Record that we found at least one task that could run on this_cpu */
			env.flags &= ~LBF_ALL_PINNED;

			/*
			 * ->active_balance synchronizes accesses to
			 * ->active_balance_work.  Once set, it's cleared
			 * only after active load balance is finished.
			 */
			अगर (!busiest->active_balance) अणु
				busiest->active_balance = 1;
				busiest->push_cpu = this_cpu;
				active_balance = 1;
			पूर्ण
			raw_spin_unlock_irqrestore(&busiest->lock, flags);

			अगर (active_balance) अणु
				stop_one_cpu_noरुको(cpu_of(busiest),
					active_load_balance_cpu_stop, busiest,
					&busiest->active_balance_work);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		sd->nr_balance_failed = 0;
	पूर्ण

	अगर (likely(!active_balance) || need_active_balance(&env)) अणु
		/* We were unbalanced, so reset the balancing पूर्णांकerval */
		sd->balance_पूर्णांकerval = sd->min_पूर्णांकerval;
	पूर्ण

	जाओ out;

out_balanced:
	/*
	 * We reach balance although we may have faced some affinity
	 * स्थिरraपूर्णांकs. Clear the imbalance flag only अगर other tasks got
	 * a chance to move and fix the imbalance.
	 */
	अगर (sd_parent && !(env.flags & LBF_ALL_PINNED)) अणु
		पूर्णांक *group_imbalance = &sd_parent->groups->sgc->imbalance;

		अगर (*group_imbalance)
			*group_imbalance = 0;
	पूर्ण

out_all_pinned:
	/*
	 * We reach balance because all tasks are pinned at this level so
	 * we can't migrate them. Let the imbalance flag set so parent level
	 * can try to migrate them.
	 */
	schedstat_inc(sd->lb_balanced[idle]);

	sd->nr_balance_failed = 0;

out_one_pinned:
	ld_moved = 0;

	/*
	 * newidle_balance() disregards balance पूर्णांकervals, so we could
	 * repeatedly reach this code, which would lead to balance_पूर्णांकerval
	 * skyrocketing in a लघु amount of समय. Skip the balance_पूर्णांकerval
	 * increase logic to aव्योम that.
	 */
	अगर (env.idle == CPU_NEWLY_IDLE)
		जाओ out;

	/* tune up the balancing पूर्णांकerval */
	अगर ((env.flags & LBF_ALL_PINNED &&
	     sd->balance_पूर्णांकerval < MAX_PINNED_INTERVAL) ||
	    sd->balance_पूर्णांकerval < sd->max_पूर्णांकerval)
		sd->balance_पूर्णांकerval *= 2;
out:
	वापस ld_moved;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
get_sd_balance_पूर्णांकerval(काष्ठा sched_करोमुख्य *sd, पूर्णांक cpu_busy)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = sd->balance_पूर्णांकerval;

	अगर (cpu_busy)
		पूर्णांकerval *= sd->busy_factor;

	/* scale ms to jअगरfies */
	पूर्णांकerval = msecs_to_jअगरfies(पूर्णांकerval);

	/*
	 * Reduce likelihood of busy balancing at higher करोमुख्यs racing with
	 * balancing at lower करोमुख्यs by preventing their balancing periods
	 * from being multiples of each other.
	 */
	अगर (cpu_busy)
		पूर्णांकerval -= 1;

	पूर्णांकerval = clamp(पूर्णांकerval, 1UL, max_load_balance_पूर्णांकerval);

	वापस पूर्णांकerval;
पूर्ण

अटल अंतरभूत व्योम
update_next_balance(काष्ठा sched_करोमुख्य *sd, अचिन्हित दीर्घ *next_balance)
अणु
	अचिन्हित दीर्घ पूर्णांकerval, next;

	/* used by idle balance, so cpu_busy = 0 */
	पूर्णांकerval = get_sd_balance_पूर्णांकerval(sd, 0);
	next = sd->last_balance + पूर्णांकerval;

	अगर (समय_after(*next_balance, next))
		*next_balance = next;
पूर्ण

/*
 * active_load_balance_cpu_stop is run by the CPU stopper. It pushes
 * running tasks off the busiest CPU onto idle CPUs. It requires at
 * least 1 task to be running on each physical CPU where possible, and
 * aव्योमs physical / logical imbalances.
 */
अटल पूर्णांक active_load_balance_cpu_stop(व्योम *data)
अणु
	काष्ठा rq *busiest_rq = data;
	पूर्णांक busiest_cpu = cpu_of(busiest_rq);
	पूर्णांक target_cpu = busiest_rq->push_cpu;
	काष्ठा rq *target_rq = cpu_rq(target_cpu);
	काष्ठा sched_करोमुख्य *sd;
	काष्ठा task_काष्ठा *p = शून्य;
	काष्ठा rq_flags rf;

	rq_lock_irq(busiest_rq, &rf);
	/*
	 * Between queueing the stop-work and running it is a hole in which
	 * CPUs can become inactive. We should not move tasks from or to
	 * inactive CPUs.
	 */
	अगर (!cpu_active(busiest_cpu) || !cpu_active(target_cpu))
		जाओ out_unlock;

	/* Make sure the requested CPU hasn't gone करोwn in the meanसमय: */
	अगर (unlikely(busiest_cpu != smp_processor_id() ||
		     !busiest_rq->active_balance))
		जाओ out_unlock;

	/* Is there any task to move? */
	अगर (busiest_rq->nr_running <= 1)
		जाओ out_unlock;

	/*
	 * This condition is "impossible", अगर it occurs
	 * we need to fix it. Originally reported by
	 * Bjorn Helgaas on a 128-CPU setup.
	 */
	BUG_ON(busiest_rq == target_rq);

	/* Search क्रम an sd spanning us and the target CPU. */
	rcu_पढ़ो_lock();
	क्रम_each_करोमुख्य(target_cpu, sd) अणु
		अगर (cpumask_test_cpu(busiest_cpu, sched_करोमुख्य_span(sd)))
			अवरोध;
	पूर्ण

	अगर (likely(sd)) अणु
		काष्ठा lb_env env = अणु
			.sd		= sd,
			.dst_cpu	= target_cpu,
			.dst_rq		= target_rq,
			.src_cpu	= busiest_rq->cpu,
			.src_rq		= busiest_rq,
			.idle		= CPU_IDLE,
			.flags		= LBF_ACTIVE_LB,
		पूर्ण;

		schedstat_inc(sd->alb_count);
		update_rq_घड़ी(busiest_rq);

		p = detach_one_task(&env);
		अगर (p) अणु
			schedstat_inc(sd->alb_pushed);
			/* Active balancing करोne, reset the failure counter. */
			sd->nr_balance_failed = 0;
		पूर्ण अन्यथा अणु
			schedstat_inc(sd->alb_failed);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
out_unlock:
	busiest_rq->active_balance = 0;
	rq_unlock(busiest_rq, &rf);

	अगर (p)
		attach_one_task(target_rq, p);

	local_irq_enable();

	वापस 0;
पूर्ण

अटल DEFINE_SPINLOCK(balancing);

/*
 * Scale the max load_balance पूर्णांकerval with the number of CPUs in the प्रणाली.
 * This trades load-balance latency on larger machines क्रम less cross talk.
 */
व्योम update_max_पूर्णांकerval(व्योम)
अणु
	max_load_balance_पूर्णांकerval = HZ*num_online_cpus()/10;
पूर्ण

/*
 * It checks each scheduling करोमुख्य to see अगर it is due to be balanced,
 * and initiates a balancing operation अगर so.
 *
 * Balancing parameters are set up in init_sched_करोमुख्यs.
 */
अटल व्योम rebalance_करोमुख्यs(काष्ठा rq *rq, क्रमागत cpu_idle_type idle)
अणु
	पूर्णांक जारी_balancing = 1;
	पूर्णांक cpu = rq->cpu;
	पूर्णांक busy = idle != CPU_IDLE && !sched_idle_cpu(cpu);
	अचिन्हित दीर्घ पूर्णांकerval;
	काष्ठा sched_करोमुख्य *sd;
	/* Earliest समय when we have to करो rebalance again */
	अचिन्हित दीर्घ next_balance = jअगरfies + 60*HZ;
	पूर्णांक update_next_balance = 0;
	पूर्णांक need_serialize, need_decay = 0;
	u64 max_cost = 0;

	rcu_पढ़ो_lock();
	क्रम_each_करोमुख्य(cpu, sd) अणु
		/*
		 * Decay the newidle max बार here because this is a regular
		 * visit to all the करोमुख्यs. Decay ~1% per second.
		 */
		अगर (समय_after(jअगरfies, sd->next_decay_max_lb_cost)) अणु
			sd->max_newidle_lb_cost =
				(sd->max_newidle_lb_cost * 253) / 256;
			sd->next_decay_max_lb_cost = jअगरfies + HZ;
			need_decay = 1;
		पूर्ण
		max_cost += sd->max_newidle_lb_cost;

		/*
		 * Stop the load balance at this level. There is another
		 * CPU in our sched group which is करोing load balancing more
		 * actively.
		 */
		अगर (!जारी_balancing) अणु
			अगर (need_decay)
				जारी;
			अवरोध;
		पूर्ण

		पूर्णांकerval = get_sd_balance_पूर्णांकerval(sd, busy);

		need_serialize = sd->flags & SD_SERIALIZE;
		अगर (need_serialize) अणु
			अगर (!spin_trylock(&balancing))
				जाओ out;
		पूर्ण

		अगर (समय_after_eq(jअगरfies, sd->last_balance + पूर्णांकerval)) अणु
			अगर (load_balance(cpu, rq, sd, idle, &जारी_balancing)) अणु
				/*
				 * The LBF_DST_PINNED logic could have changed
				 * env->dst_cpu, so we can't know our idle
				 * state even अगर we migrated tasks. Update it.
				 */
				idle = idle_cpu(cpu) ? CPU_IDLE : CPU_NOT_IDLE;
				busy = idle != CPU_IDLE && !sched_idle_cpu(cpu);
			पूर्ण
			sd->last_balance = jअगरfies;
			पूर्णांकerval = get_sd_balance_पूर्णांकerval(sd, busy);
		पूर्ण
		अगर (need_serialize)
			spin_unlock(&balancing);
out:
		अगर (समय_after(next_balance, sd->last_balance + पूर्णांकerval)) अणु
			next_balance = sd->last_balance + पूर्णांकerval;
			update_next_balance = 1;
		पूर्ण
	पूर्ण
	अगर (need_decay) अणु
		/*
		 * Ensure the rq-wide value also decays but keep it at a
		 * reasonable न्यूनमान to aव्योम funnies with rq->avg_idle.
		 */
		rq->max_idle_balance_cost =
			max((u64)sysctl_sched_migration_cost, max_cost);
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * next_balance will be updated only when there is a need.
	 * When the cpu is attached to null करोमुख्य क्रम ex, it will not be
	 * updated.
	 */
	अगर (likely(update_next_balance))
		rq->next_balance = next_balance;

पूर्ण

अटल अंतरभूत पूर्णांक on_null_करोमुख्य(काष्ठा rq *rq)
अणु
	वापस unlikely(!rcu_dereference_sched(rq->sd));
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_COMMON
/*
 * idle load balancing details
 * - When one of the busy CPUs notice that there may be an idle rebalancing
 *   needed, they will kick the idle load balancer, which then करोes idle
 *   load balancing क्रम all the idle CPUs.
 * - HK_FLAG_MISC CPUs are used क्रम this task, because HK_FLAG_SCHED not set
 *   anywhere yet.
 */

अटल अंतरभूत पूर्णांक find_new_ilb(व्योम)
अणु
	पूर्णांक ilb;

	क्रम_each_cpu_and(ilb, nohz.idle_cpus_mask,
			      housekeeping_cpumask(HK_FLAG_MISC)) अणु

		अगर (ilb == smp_processor_id())
			जारी;

		अगर (idle_cpu(ilb))
			वापस ilb;
	पूर्ण

	वापस nr_cpu_ids;
पूर्ण

/*
 * Kick a CPU to करो the nohz balancing, अगर it is समय क्रम it. We pick any
 * idle CPU in the HK_FLAG_MISC housekeeping set (अगर there is one).
 */
अटल व्योम kick_ilb(अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ilb_cpu;

	/*
	 * Increase nohz.next_balance only when अगर full ilb is triggered but
	 * not अगर we only update stats.
	 */
	अगर (flags & NOHZ_BALANCE_KICK)
		nohz.next_balance = jअगरfies+1;

	ilb_cpu = find_new_ilb();

	अगर (ilb_cpu >= nr_cpu_ids)
		वापस;

	/*
	 * Access to rq::nohz_csd is serialized by NOHZ_KICK_MASK; he who sets
	 * the first flag owns it; cleared by nohz_csd_func().
	 */
	flags = atomic_fetch_or(flags, nohz_flags(ilb_cpu));
	अगर (flags & NOHZ_KICK_MASK)
		वापस;

	/*
	 * This way we generate an IPI on the target CPU which
	 * is idle. And the softirq perक्रमming nohz idle load balance
	 * will be run beक्रमe वापसing from the IPI.
	 */
	smp_call_function_single_async(ilb_cpu, &cpu_rq(ilb_cpu)->nohz_csd);
पूर्ण

/*
 * Current decision poपूर्णांक क्रम kicking the idle load balancer in the presence
 * of idle CPUs in the प्रणाली.
 */
अटल व्योम nohz_balancer_kick(काष्ठा rq *rq)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा sched_करोमुख्य_shared *sds;
	काष्ठा sched_करोमुख्य *sd;
	पूर्णांक nr_busy, i, cpu = rq->cpu;
	अचिन्हित पूर्णांक flags = 0;

	अगर (unlikely(rq->idle_balance))
		वापस;

	/*
	 * We may be recently in ticked or tickless idle mode. At the first
	 * busy tick after वापसing from idle, we will update the busy stats.
	 */
	nohz_balance_निकास_idle(rq);

	/*
	 * None are in tickless mode and hence no need क्रम NOHZ idle load
	 * balancing.
	 */
	अगर (likely(!atomic_पढ़ो(&nohz.nr_cpus)))
		वापस;

	अगर (READ_ONCE(nohz.has_blocked) &&
	    समय_after(now, READ_ONCE(nohz.next_blocked)))
		flags = NOHZ_STATS_KICK;

	अगर (समय_beक्रमe(now, nohz.next_balance))
		जाओ out;

	अगर (rq->nr_running >= 2) अणु
		flags = NOHZ_KICK_MASK;
		जाओ out;
	पूर्ण

	rcu_पढ़ो_lock();

	sd = rcu_dereference(rq->sd);
	अगर (sd) अणु
		/*
		 * If there's a CFS task and the current CPU has reduced
		 * capacity; kick the ILB to see अगर there's a better CPU to run
		 * on.
		 */
		अगर (rq->cfs.h_nr_running >= 1 && check_cpu_capacity(rq, sd)) अणु
			flags = NOHZ_KICK_MASK;
			जाओ unlock;
		पूर्ण
	पूर्ण

	sd = rcu_dereference(per_cpu(sd_asym_packing, cpu));
	अगर (sd) अणु
		/*
		 * When ASYM_PACKING; see अगर there's a more preferred CPU
		 * currently idle; in which हाल, kick the ILB to move tasks
		 * around.
		 */
		क्रम_each_cpu_and(i, sched_करोमुख्य_span(sd), nohz.idle_cpus_mask) अणु
			अगर (sched_asym_prefer(i, cpu)) अणु
				flags = NOHZ_KICK_MASK;
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	sd = rcu_dereference(per_cpu(sd_asym_cpucapacity, cpu));
	अगर (sd) अणु
		/*
		 * When ASYM_CPUCAPACITY; see अगर there's a higher capacity CPU
		 * to run the misfit task on.
		 */
		अगर (check_misfit_status(rq, sd)) अणु
			flags = NOHZ_KICK_MASK;
			जाओ unlock;
		पूर्ण

		/*
		 * For asymmetric प्रणालीs, we करो not want to nicely balance
		 * cache use, instead we want to embrace asymmetry and only
		 * ensure tasks have enough CPU capacity.
		 *
		 * Skip the LLC logic because it's not relevant in that हाल.
		 */
		जाओ unlock;
	पूर्ण

	sds = rcu_dereference(per_cpu(sd_llc_shared, cpu));
	अगर (sds) अणु
		/*
		 * If there is an imbalance between LLC करोमुख्यs (IOW we could
		 * increase the overall cache use), we need some less-loaded LLC
		 * करोमुख्य to pull some load. Likewise, we may need to spपढ़ो
		 * load within the current LLC करोमुख्य (e.g. packed SMT cores but
		 * other CPUs are idle). We can't really know from here how busy
		 * the others are - so just get a nohz balance going अगर it looks
		 * like this LLC करोमुख्य has tasks we could move.
		 */
		nr_busy = atomic_पढ़ो(&sds->nr_busy_cpus);
		अगर (nr_busy > 1) अणु
			flags = NOHZ_KICK_MASK;
			जाओ unlock;
		पूर्ण
	पूर्ण
unlock:
	rcu_पढ़ो_unlock();
out:
	अगर (flags)
		kick_ilb(flags);
पूर्ण

अटल व्योम set_cpu_sd_state_busy(पूर्णांक cpu)
अणु
	काष्ठा sched_करोमुख्य *sd;

	rcu_पढ़ो_lock();
	sd = rcu_dereference(per_cpu(sd_llc, cpu));

	अगर (!sd || !sd->nohz_idle)
		जाओ unlock;
	sd->nohz_idle = 0;

	atomic_inc(&sd->shared->nr_busy_cpus);
unlock:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम nohz_balance_निकास_idle(काष्ठा rq *rq)
अणु
	SCHED_WARN_ON(rq != this_rq());

	अगर (likely(!rq->nohz_tick_stopped))
		वापस;

	rq->nohz_tick_stopped = 0;
	cpumask_clear_cpu(rq->cpu, nohz.idle_cpus_mask);
	atomic_dec(&nohz.nr_cpus);

	set_cpu_sd_state_busy(rq->cpu);
पूर्ण

अटल व्योम set_cpu_sd_state_idle(पूर्णांक cpu)
अणु
	काष्ठा sched_करोमुख्य *sd;

	rcu_पढ़ो_lock();
	sd = rcu_dereference(per_cpu(sd_llc, cpu));

	अगर (!sd || sd->nohz_idle)
		जाओ unlock;
	sd->nohz_idle = 1;

	atomic_dec(&sd->shared->nr_busy_cpus);
unlock:
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * This routine will record that the CPU is going idle with tick stopped.
 * This info will be used in perक्रमming idle load balancing in the future.
 */
व्योम nohz_balance_enter_idle(पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	SCHED_WARN_ON(cpu != smp_processor_id());

	/* If this CPU is going करोwn, then nothing needs to be करोne: */
	अगर (!cpu_active(cpu))
		वापस;

	/* Spare idle load balancing on CPUs that करोn't want to be disturbed: */
	अगर (!housekeeping_cpu(cpu, HK_FLAG_SCHED))
		वापस;

	/*
	 * Can be set safely without rq->lock held
	 * If a clear happens, it will have evaluated last additions because
	 * rq->lock is held during the check and the clear
	 */
	rq->has_blocked_load = 1;

	/*
	 * The tick is still stopped but load could have been added in the
	 * meanसमय. We set the nohz.has_blocked flag to trig a check of the
	 * *_avg. The CPU is alपढ़ोy part of nohz.idle_cpus_mask so the clear
	 * of nohz.has_blocked can only happen after checking the new load
	 */
	अगर (rq->nohz_tick_stopped)
		जाओ out;

	/* If we're a completely isolated CPU, we don't play: */
	अगर (on_null_करोमुख्य(rq))
		वापस;

	rq->nohz_tick_stopped = 1;

	cpumask_set_cpu(cpu, nohz.idle_cpus_mask);
	atomic_inc(&nohz.nr_cpus);

	/*
	 * Ensures that अगर nohz_idle_balance() fails to observe our
	 * @idle_cpus_mask store, it must observe the @has_blocked
	 * store.
	 */
	smp_mb__after_atomic();

	set_cpu_sd_state_idle(cpu);

out:
	/*
	 * Each समय a cpu enter idle, we assume that it has blocked load and
	 * enable the periodic update of the load of idle cpus
	 */
	WRITE_ONCE(nohz.has_blocked, 1);
पूर्ण

अटल bool update_nohz_stats(काष्ठा rq *rq)
अणु
	अचिन्हित पूर्णांक cpu = rq->cpu;

	अगर (!rq->has_blocked_load)
		वापस false;

	अगर (!cpumask_test_cpu(cpu, nohz.idle_cpus_mask))
		वापस false;

	अगर (!समय_after(jअगरfies, READ_ONCE(rq->last_blocked_load_update_tick)))
		वापस true;

	update_blocked_averages(cpu);

	वापस rq->has_blocked_load;
पूर्ण

/*
 * Internal function that runs load balance क्रम all idle cpus. The load balance
 * can be a simple update of blocked load or a complete load balance with
 * tasks movement depending of flags.
 */
अटल व्योम _nohz_idle_balance(काष्ठा rq *this_rq, अचिन्हित पूर्णांक flags,
			       क्रमागत cpu_idle_type idle)
अणु
	/* Earliest समय when we have to करो rebalance again */
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ next_balance = now + 60*HZ;
	bool has_blocked_load = false;
	पूर्णांक update_next_balance = 0;
	पूर्णांक this_cpu = this_rq->cpu;
	पूर्णांक balance_cpu;
	काष्ठा rq *rq;

	SCHED_WARN_ON((flags & NOHZ_KICK_MASK) == NOHZ_BALANCE_KICK);

	/*
	 * We assume there will be no idle load after this update and clear
	 * the has_blocked flag. If a cpu enters idle in the mean समय, it will
	 * set the has_blocked flag and trig another update of idle load.
	 * Because a cpu that becomes idle, is added to idle_cpus_mask beक्रमe
	 * setting the flag, we are sure to not clear the state and not
	 * check the load of an idle cpu.
	 */
	WRITE_ONCE(nohz.has_blocked, 0);

	/*
	 * Ensures that अगर we miss the CPU, we must see the has_blocked
	 * store from nohz_balance_enter_idle().
	 */
	smp_mb();

	/*
	 * Start with the next CPU after this_cpu so we will end with this_cpu and let a
	 * chance क्रम other idle cpu to pull load.
	 */
	क्रम_each_cpu_wrap(balance_cpu,  nohz.idle_cpus_mask, this_cpu+1) अणु
		अगर (!idle_cpu(balance_cpu))
			जारी;

		/*
		 * If this CPU माला_लो work to करो, stop the load balancing
		 * work being करोne क्रम other CPUs. Next load
		 * balancing owner will pick it up.
		 */
		अगर (need_resched()) अणु
			has_blocked_load = true;
			जाओ पात;
		पूर्ण

		rq = cpu_rq(balance_cpu);

		has_blocked_load |= update_nohz_stats(rq);

		/*
		 * If समय क्रम next balance is due,
		 * करो the balance.
		 */
		अगर (समय_after_eq(jअगरfies, rq->next_balance)) अणु
			काष्ठा rq_flags rf;

			rq_lock_irqsave(rq, &rf);
			update_rq_घड़ी(rq);
			rq_unlock_irqrestore(rq, &rf);

			अगर (flags & NOHZ_BALANCE_KICK)
				rebalance_करोमुख्यs(rq, CPU_IDLE);
		पूर्ण

		अगर (समय_after(next_balance, rq->next_balance)) अणु
			next_balance = rq->next_balance;
			update_next_balance = 1;
		पूर्ण
	पूर्ण

	/*
	 * next_balance will be updated only when there is a need.
	 * When the CPU is attached to null करोमुख्य क्रम ex, it will not be
	 * updated.
	 */
	अगर (likely(update_next_balance))
		nohz.next_balance = next_balance;

	WRITE_ONCE(nohz.next_blocked,
		now + msecs_to_jअगरfies(LOAD_AVG_PERIOD));

पात:
	/* There is still blocked load, enable periodic update */
	अगर (has_blocked_load)
		WRITE_ONCE(nohz.has_blocked, 1);
पूर्ण

/*
 * In CONFIG_NO_HZ_COMMON हाल, the idle balance kickee will करो the
 * rebalancing क्रम all the cpus क्रम whom scheduler ticks are stopped.
 */
अटल bool nohz_idle_balance(काष्ठा rq *this_rq, क्रमागत cpu_idle_type idle)
अणु
	अचिन्हित पूर्णांक flags = this_rq->nohz_idle_balance;

	अगर (!flags)
		वापस false;

	this_rq->nohz_idle_balance = 0;

	अगर (idle != CPU_IDLE)
		वापस false;

	_nohz_idle_balance(this_rq, flags, idle);

	वापस true;
पूर्ण

/*
 * Check अगर we need to run the ILB क्रम updating blocked load beक्रमe entering
 * idle state.
 */
व्योम nohz_run_idle_balance(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक flags;

	flags = atomic_fetch_andnot(NOHZ_NEWILB_KICK, nohz_flags(cpu));

	/*
	 * Update the blocked load only अगर no SCHED_SOFTIRQ is about to happen
	 * (ie NOHZ_STATS_KICK set) and will करो the same.
	 */
	अगर ((flags == NOHZ_NEWILB_KICK) && !need_resched())
		_nohz_idle_balance(cpu_rq(cpu), NOHZ_STATS_KICK, CPU_IDLE);
पूर्ण

अटल व्योम nohz_newidle_balance(काष्ठा rq *this_rq)
अणु
	पूर्णांक this_cpu = this_rq->cpu;

	/*
	 * This CPU करोesn't want to be disturbed by scheduler
	 * housekeeping
	 */
	अगर (!housekeeping_cpu(this_cpu, HK_FLAG_SCHED))
		वापस;

	/* Will wake up very soon. No समय क्रम करोing anything अन्यथा*/
	अगर (this_rq->avg_idle < sysctl_sched_migration_cost)
		वापस;

	/* Don't need to update blocked load of idle CPUs*/
	अगर (!READ_ONCE(nohz.has_blocked) ||
	    समय_beक्रमe(jअगरfies, READ_ONCE(nohz.next_blocked)))
		वापस;

	/*
	 * Set the need to trigger ILB in order to update blocked load
	 * beक्रमe entering idle state.
	 */
	atomic_or(NOHZ_NEWILB_KICK, nohz_flags(this_cpu));
पूर्ण

#अन्यथा /* !CONFIG_NO_HZ_COMMON */
अटल अंतरभूत व्योम nohz_balancer_kick(काष्ठा rq *rq) अणु पूर्ण

अटल अंतरभूत bool nohz_idle_balance(काष्ठा rq *this_rq, क्रमागत cpu_idle_type idle)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम nohz_newidle_balance(काष्ठा rq *this_rq) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

/*
 * newidle_balance is called by schedule() अगर this_cpu is about to become
 * idle. Attempts to pull tasks from other CPUs.
 *
 * Returns:
 *   < 0 - we released the lock and there are !fair tasks present
 *     0 - failed, no new tasks
 *   > 0 - success, new (fair) tasks present
 */
अटल पूर्णांक newidle_balance(काष्ठा rq *this_rq, काष्ठा rq_flags *rf)
अणु
	अचिन्हित दीर्घ next_balance = jअगरfies + HZ;
	पूर्णांक this_cpu = this_rq->cpu;
	काष्ठा sched_करोमुख्य *sd;
	पूर्णांक pulled_task = 0;
	u64 curr_cost = 0;

	update_misfit_status(शून्य, this_rq);
	/*
	 * We must set idle_stamp _beक्रमe_ calling idle_balance(), such that we
	 * measure the duration of idle_balance() as idle समय.
	 */
	this_rq->idle_stamp = rq_घड़ी(this_rq);

	/*
	 * Do not pull tasks towards !active CPUs...
	 */
	अगर (!cpu_active(this_cpu))
		वापस 0;

	/*
	 * This is OK, because current is on_cpu, which aव्योमs it being picked
	 * क्रम load-balance and preemption/IRQs are still disabled aव्योमing
	 * further scheduler activity on it and we're being very careful to
	 * re-start the picking loop.
	 */
	rq_unpin_lock(this_rq, rf);

	अगर (this_rq->avg_idle < sysctl_sched_migration_cost ||
	    !READ_ONCE(this_rq->rd->overload)) अणु

		rcu_पढ़ो_lock();
		sd = rcu_dereference_check_sched_करोमुख्य(this_rq->sd);
		अगर (sd)
			update_next_balance(sd, &next_balance);
		rcu_पढ़ो_unlock();

		जाओ out;
	पूर्ण

	raw_spin_unlock(&this_rq->lock);

	update_blocked_averages(this_cpu);
	rcu_पढ़ो_lock();
	क्रम_each_करोमुख्य(this_cpu, sd) अणु
		पूर्णांक जारी_balancing = 1;
		u64 t0, करोमुख्य_cost;

		अगर (this_rq->avg_idle < curr_cost + sd->max_newidle_lb_cost) अणु
			update_next_balance(sd, &next_balance);
			अवरोध;
		पूर्ण

		अगर (sd->flags & SD_BALANCE_NEWIDLE) अणु
			t0 = sched_घड़ी_cpu(this_cpu);

			pulled_task = load_balance(this_cpu, this_rq,
						   sd, CPU_NEWLY_IDLE,
						   &जारी_balancing);

			करोमुख्य_cost = sched_घड़ी_cpu(this_cpu) - t0;
			अगर (करोमुख्य_cost > sd->max_newidle_lb_cost)
				sd->max_newidle_lb_cost = करोमुख्य_cost;

			curr_cost += करोमुख्य_cost;
		पूर्ण

		update_next_balance(sd, &next_balance);

		/*
		 * Stop searching क्रम tasks to pull अगर there are
		 * now runnable tasks on this rq.
		 */
		अगर (pulled_task || this_rq->nr_running > 0)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	raw_spin_lock(&this_rq->lock);

	अगर (curr_cost > this_rq->max_idle_balance_cost)
		this_rq->max_idle_balance_cost = curr_cost;

	/*
	 * While browsing the करोमुख्यs, we released the rq lock, a task could
	 * have been enqueued in the meanसमय. Since we're not going idle,
	 * pretend we pulled a task.
	 */
	अगर (this_rq->cfs.h_nr_running && !pulled_task)
		pulled_task = 1;

	/* Is there a task of a high priority class? */
	अगर (this_rq->nr_running != this_rq->cfs.h_nr_running)
		pulled_task = -1;

out:
	/* Move the next balance क्रमward */
	अगर (समय_after(this_rq->next_balance, next_balance))
		this_rq->next_balance = next_balance;

	अगर (pulled_task)
		this_rq->idle_stamp = 0;
	अन्यथा
		nohz_newidle_balance(this_rq);

	rq_repin_lock(this_rq, rf);

	वापस pulled_task;
पूर्ण

/*
 * run_rebalance_करोमुख्यs is triggered when needed from the scheduler tick.
 * Also triggered क्रम nohz idle balancing (with nohz_balancing_kick set).
 */
अटल __latent_entropy व्योम run_rebalance_करोमुख्यs(काष्ठा softirq_action *h)
अणु
	काष्ठा rq *this_rq = this_rq();
	क्रमागत cpu_idle_type idle = this_rq->idle_balance ?
						CPU_IDLE : CPU_NOT_IDLE;

	/*
	 * If this CPU has a pending nohz_balance_kick, then करो the
	 * balancing on behalf of the other idle CPUs whose ticks are
	 * stopped. Do nohz_idle_balance *beक्रमe* rebalance_करोमुख्यs to
	 * give the idle CPUs a chance to load balance. Else we may
	 * load balance only within the local sched_करोमुख्य hierarchy
	 * and पात nohz_idle_balance altogether अगर we pull some load.
	 */
	अगर (nohz_idle_balance(this_rq, idle))
		वापस;

	/* normal load balance */
	update_blocked_averages(this_rq->cpu);
	rebalance_करोमुख्यs(this_rq, idle);
पूर्ण

/*
 * Trigger the SCHED_SOFTIRQ अगर it is समय to करो periodic load balancing.
 */
व्योम trigger_load_balance(काष्ठा rq *rq)
अणु
	/*
	 * Don't need to rebalance जबतक attached to शून्य करोमुख्य or
	 * runqueue CPU is not active
	 */
	अगर (unlikely(on_null_करोमुख्य(rq) || !cpu_active(cpu_of(rq))))
		वापस;

	अगर (समय_after_eq(jअगरfies, rq->next_balance))
		उठाओ_softirq(SCHED_SOFTIRQ);

	nohz_balancer_kick(rq);
पूर्ण

अटल व्योम rq_online_fair(काष्ठा rq *rq)
अणु
	update_sysctl();

	update_runसमय_enabled(rq);
पूर्ण

अटल व्योम rq_offline_fair(काष्ठा rq *rq)
अणु
	update_sysctl();

	/* Ensure any throttled groups are reachable by pick_next_task */
	unthrottle_offline_cfs_rqs(rq);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

/*
 * scheduler tick hitting a task of our scheduling class.
 *
 * NOTE: This function can be called remotely by the tick offload that
 * goes aदीर्घ full dynticks. Thereक्रमe no local assumption can be made
 * and everything must be accessed through the @rq and @curr passed in
 * parameters.
 */
अटल व्योम task_tick_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *curr, पूर्णांक queued)
अणु
	काष्ठा cfs_rq *cfs_rq;
	काष्ठा sched_entity *se = &curr->se;

	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);
		entity_tick(cfs_rq, se, queued);
	पूर्ण

	अगर (अटल_branch_unlikely(&sched_numa_balancing))
		task_tick_numa(rq, curr);

	update_misfit_status(curr, rq);
	update_overutilized_status(task_rq(curr));
पूर्ण

/*
 * called on विभाजन with the child task as argument from the parent's context
 *  - child not yet on the tasklist
 *  - preemption disabled
 */
अटल व्योम task_विभाजन_fair(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा cfs_rq *cfs_rq;
	काष्ठा sched_entity *se = &p->se, *curr;
	काष्ठा rq *rq = this_rq();
	काष्ठा rq_flags rf;

	rq_lock(rq, &rf);
	update_rq_घड़ी(rq);

	cfs_rq = task_cfs_rq(current);
	curr = cfs_rq->curr;
	अगर (curr) अणु
		update_curr(cfs_rq);
		se->vrunसमय = curr->vrunसमय;
	पूर्ण
	place_entity(cfs_rq, se, 1);

	अगर (sysctl_sched_child_runs_first && curr && entity_beक्रमe(curr, se)) अणु
		/*
		 * Upon rescheduling, sched_class::put_prev_task() will place
		 * 'current' within the tree based on its new key value.
		 */
		swap(curr->vrunसमय, se->vrunसमय);
		resched_curr(rq);
	पूर्ण

	se->vrunसमय -= cfs_rq->min_vrunसमय;
	rq_unlock(rq, &rf);
पूर्ण

/*
 * Priority of the task has changed. Check to see अगर we preempt
 * the current task.
 */
अटल व्योम
prio_changed_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक oldprio)
अणु
	अगर (!task_on_rq_queued(p))
		वापस;

	अगर (rq->cfs.nr_running == 1)
		वापस;

	/*
	 * Reschedule अगर we are currently running on this runqueue and
	 * our priority decreased, or अगर we are not currently running on
	 * this runqueue and our priority is higher than the current's
	 */
	अगर (task_current(rq, p)) अणु
		अगर (p->prio > oldprio)
			resched_curr(rq);
	पूर्ण अन्यथा
		check_preempt_curr(rq, p, 0);
पूर्ण

अटल अंतरभूत bool vrunसमय_normalized(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_entity *se = &p->se;

	/*
	 * In both the TASK_ON_RQ_QUEUED and TASK_ON_RQ_MIGRATING हालs,
	 * the dequeue_entity(.flags=0) will alपढ़ोy have normalized the
	 * vrunसमय.
	 */
	अगर (p->on_rq)
		वापस true;

	/*
	 * When !on_rq, vrunसमय of the task has usually NOT been normalized.
	 * But there are some हालs where it has alपढ़ोy been normalized:
	 *
	 * - A विभाजनed child which is रुकोing क्रम being woken up by
	 *   wake_up_new_task().
	 * - A task which has been woken up by try_to_wake_up() and
	 *   रुकोing क्रम actually being woken up by sched_ttwu_pending().
	 */
	अगर (!se->sum_exec_runसमय ||
	    (p->state == TASK_WAKING && p->sched_remote_wakeup))
		वापस true;

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
/*
 * Propagate the changes of the sched_entity across the tg tree to make it
 * visible to the root
 */
अटल व्योम propagate_entity_cfs_rq(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *cfs_rq;

	list_add_leaf_cfs_rq(cfs_rq_of(se));

	/* Start to propagate at parent */
	se = se->parent;

	क्रम_each_sched_entity(se) अणु
		cfs_rq = cfs_rq_of(se);

		अगर (!cfs_rq_throttled(cfs_rq))अणु
			update_load_avg(cfs_rq, se, UPDATE_TG);
			list_add_leaf_cfs_rq(cfs_rq);
			जारी;
		पूर्ण

		अगर (list_add_leaf_cfs_rq(cfs_rq))
			अवरोध;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम propagate_entity_cfs_rq(काष्ठा sched_entity *se) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम detach_entity_cfs_rq(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);

	/* Catch up with the cfs_rq and हटाओ our load when we leave */
	update_load_avg(cfs_rq, se, 0);
	detach_entity_load_avg(cfs_rq, se);
	update_tg_load_avg(cfs_rq);
	propagate_entity_cfs_rq(se);
पूर्ण

अटल व्योम attach_entity_cfs_rq(काष्ठा sched_entity *se)
अणु
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	/*
	 * Since the real-depth could have been changed (only FAIR
	 * class मुख्यtain depth value), reset depth properly.
	 */
	se->depth = se->parent ? se->parent->depth + 1 : 0;
#पूर्ण_अगर

	/* Synchronize entity with its cfs_rq */
	update_load_avg(cfs_rq, se, sched_feat(ATTACH_AGE_LOAD) ? 0 : SKIP_AGE_LOAD);
	attach_entity_load_avg(cfs_rq, se);
	update_tg_load_avg(cfs_rq);
	propagate_entity_cfs_rq(se);
पूर्ण

अटल व्योम detach_task_cfs_rq(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_entity *se = &p->se;
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);

	अगर (!vrunसमय_normalized(p)) अणु
		/*
		 * Fix up our vrunसमय so that the current sleep करोesn't
		 * cause 'unlimited' sleep bonus.
		 */
		place_entity(cfs_rq, se, 0);
		se->vrunसमय -= cfs_rq->min_vrunसमय;
	पूर्ण

	detach_entity_cfs_rq(se);
पूर्ण

अटल व्योम attach_task_cfs_rq(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_entity *se = &p->se;
	काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);

	attach_entity_cfs_rq(se);

	अगर (!vrunसमय_normalized(p))
		se->vrunसमय += cfs_rq->min_vrunसमय;
पूर्ण

अटल व्योम चयनed_from_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	detach_task_cfs_rq(p);
पूर्ण

अटल व्योम चयनed_to_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	attach_task_cfs_rq(p);

	अगर (task_on_rq_queued(p)) अणु
		/*
		 * We were most likely चयनed from sched_rt, so
		 * kick off the schedule अगर running, otherwise just see
		 * अगर we can still preempt the current task.
		 */
		अगर (task_current(rq, p))
			resched_curr(rq);
		अन्यथा
			check_preempt_curr(rq, p, 0);
	पूर्ण
पूर्ण

/* Account क्रम a task changing its policy or group.
 *
 * This routine is mostly called to set cfs_rq->curr field when a task
 * migrates between groups/classes.
 */
अटल व्योम set_next_task_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, bool first)
अणु
	काष्ठा sched_entity *se = &p->se;

#अगर_घोषित CONFIG_SMP
	अगर (task_on_rq_queued(p)) अणु
		/*
		 * Move the next running task to the front of the list, so our
		 * cfs_tasks list becomes MRU one.
		 */
		list_move(&se->group_node, &rq->cfs_tasks);
	पूर्ण
#पूर्ण_अगर

	क्रम_each_sched_entity(se) अणु
		काष्ठा cfs_rq *cfs_rq = cfs_rq_of(se);

		set_next_entity(cfs_rq, se);
		/* ensure bandwidth has been allocated on our new cfs_rq */
		account_cfs_rq_runसमय(cfs_rq, 0);
	पूर्ण
पूर्ण

व्योम init_cfs_rq(काष्ठा cfs_rq *cfs_rq)
अणु
	cfs_rq->tasks_समयline = RB_ROOT_CACHED;
	cfs_rq->min_vrunसमय = (u64)(-(1LL << 20));
#अगर_अघोषित CONFIG_64BIT
	cfs_rq->min_vrunसमय_copy = cfs_rq->min_vrunसमय;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	raw_spin_lock_init(&cfs_rq->हटाओd.lock);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
अटल व्योम task_set_group_fair(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_entity *se = &p->se;

	set_task_rq(p, task_cpu(p));
	se->depth = se->parent ? se->parent->depth + 1 : 0;
पूर्ण

अटल व्योम task_move_group_fair(काष्ठा task_काष्ठा *p)
अणु
	detach_task_cfs_rq(p);
	set_task_rq(p, task_cpu(p));

#अगर_घोषित CONFIG_SMP
	/* Tell se's cfs_rq has been changed -- migrated */
	p->se.avg.last_update_समय = 0;
#पूर्ण_अगर
	attach_task_cfs_rq(p);
पूर्ण

अटल व्योम task_change_group_fair(काष्ठा task_काष्ठा *p, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल TASK_SET_GROUP:
		task_set_group_fair(p);
		अवरोध;

	हाल TASK_MOVE_GROUP:
		task_move_group_fair(p);
		अवरोध;
	पूर्ण
पूर्ण

व्योम मुक्त_fair_sched_group(काष्ठा task_group *tg)
अणु
	पूर्णांक i;

	destroy_cfs_bandwidth(tg_cfs_bandwidth(tg));

	क्रम_each_possible_cpu(i) अणु
		अगर (tg->cfs_rq)
			kमुक्त(tg->cfs_rq[i]);
		अगर (tg->se)
			kमुक्त(tg->se[i]);
	पूर्ण

	kमुक्त(tg->cfs_rq);
	kमुक्त(tg->se);
पूर्ण

पूर्णांक alloc_fair_sched_group(काष्ठा task_group *tg, काष्ठा task_group *parent)
अणु
	काष्ठा sched_entity *se;
	काष्ठा cfs_rq *cfs_rq;
	पूर्णांक i;

	tg->cfs_rq = kसुस्मृति(nr_cpu_ids, माप(cfs_rq), GFP_KERNEL);
	अगर (!tg->cfs_rq)
		जाओ err;
	tg->se = kसुस्मृति(nr_cpu_ids, माप(se), GFP_KERNEL);
	अगर (!tg->se)
		जाओ err;

	tg->shares = NICE_0_LOAD;

	init_cfs_bandwidth(tg_cfs_bandwidth(tg));

	क्रम_each_possible_cpu(i) अणु
		cfs_rq = kzalloc_node(माप(काष्ठा cfs_rq),
				      GFP_KERNEL, cpu_to_node(i));
		अगर (!cfs_rq)
			जाओ err;

		se = kzalloc_node(माप(काष्ठा sched_entity),
				  GFP_KERNEL, cpu_to_node(i));
		अगर (!se)
			जाओ err_मुक्त_rq;

		init_cfs_rq(cfs_rq);
		init_tg_cfs_entry(tg, cfs_rq, se, i, parent->se[i]);
		init_entity_runnable_average(se);
	पूर्ण

	वापस 1;

err_मुक्त_rq:
	kमुक्त(cfs_rq);
err:
	वापस 0;
पूर्ण

व्योम online_fair_sched_group(काष्ठा task_group *tg)
अणु
	काष्ठा sched_entity *se;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		rq = cpu_rq(i);
		se = tg->se[i];
		rq_lock_irq(rq, &rf);
		update_rq_घड़ी(rq);
		attach_entity_cfs_rq(se);
		sync_throttle(tg, i);
		rq_unlock_irq(rq, &rf);
	पूर्ण
पूर्ण

व्योम unरेजिस्टर_fair_sched_group(काष्ठा task_group *tg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rq *rq;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (tg->se[cpu])
			हटाओ_entity_load_avg(tg->se[cpu]);

		/*
		 * Only empty task groups can be destroyed; so we can speculatively
		 * check on_list without danger of it being re-added.
		 */
		अगर (!tg->cfs_rq[cpu]->on_list)
			जारी;

		rq = cpu_rq(cpu);

		raw_spin_lock_irqsave(&rq->lock, flags);
		list_del_leaf_cfs_rq(tg->cfs_rq[cpu]);
		raw_spin_unlock_irqrestore(&rq->lock, flags);
	पूर्ण
पूर्ण

व्योम init_tg_cfs_entry(काष्ठा task_group *tg, काष्ठा cfs_rq *cfs_rq,
			काष्ठा sched_entity *se, पूर्णांक cpu,
			काष्ठा sched_entity *parent)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	cfs_rq->tg = tg;
	cfs_rq->rq = rq;
	init_cfs_rq_runसमय(cfs_rq);

	tg->cfs_rq[cpu] = cfs_rq;
	tg->se[cpu] = se;

	/* se could be शून्य क्रम root_task_group */
	अगर (!se)
		वापस;

	अगर (!parent) अणु
		se->cfs_rq = &rq->cfs;
		se->depth = 0;
	पूर्ण अन्यथा अणु
		se->cfs_rq = parent->my_q;
		se->depth = parent->depth + 1;
	पूर्ण

	se->my_q = cfs_rq;
	/* guarantee group entities always have weight */
	update_load_set(&se->load, NICE_0_LOAD);
	se->parent = parent;
पूर्ण

अटल DEFINE_MUTEX(shares_mutex);

पूर्णांक sched_group_set_shares(काष्ठा task_group *tg, अचिन्हित दीर्घ shares)
अणु
	पूर्णांक i;

	/*
	 * We can't change the weight of the root cgroup.
	 */
	अगर (!tg->se[0])
		वापस -EINVAL;

	shares = clamp(shares, scale_load(MIN_SHARES), scale_load(MAX_SHARES));

	mutex_lock(&shares_mutex);
	अगर (tg->shares == shares)
		जाओ करोne;

	tg->shares = shares;
	क्रम_each_possible_cpu(i) अणु
		काष्ठा rq *rq = cpu_rq(i);
		काष्ठा sched_entity *se = tg->se[i];
		काष्ठा rq_flags rf;

		/* Propagate contribution to hierarchy */
		rq_lock_irqsave(rq, &rf);
		update_rq_घड़ी(rq);
		क्रम_each_sched_entity(se) अणु
			update_load_avg(cfs_rq_of(se), se, UPDATE_TG);
			update_cfs_group(se);
		पूर्ण
		rq_unlock_irqrestore(rq, &rf);
	पूर्ण

करोne:
	mutex_unlock(&shares_mutex);
	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_FAIR_GROUP_SCHED */

व्योम मुक्त_fair_sched_group(काष्ठा task_group *tg) अणु पूर्ण

पूर्णांक alloc_fair_sched_group(काष्ठा task_group *tg, काष्ठा task_group *parent)
अणु
	वापस 1;
पूर्ण

व्योम online_fair_sched_group(काष्ठा task_group *tg) अणु पूर्ण

व्योम unरेजिस्टर_fair_sched_group(काष्ठा task_group *tg) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */


अटल अचिन्हित पूर्णांक get_rr_पूर्णांकerval_fair(काष्ठा rq *rq, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा sched_entity *se = &task->se;
	अचिन्हित पूर्णांक rr_पूर्णांकerval = 0;

	/*
	 * Time slice is 0 क्रम SCHED_OTHER tasks that are on an otherwise
	 * idle runqueue:
	 */
	अगर (rq->cfs.load.weight)
		rr_पूर्णांकerval = NS_TO_JIFFIES(sched_slice(cfs_rq_of(se), se));

	वापस rr_पूर्णांकerval;
पूर्ण

/*
 * All the scheduling class methods:
 */
DEFINE_SCHED_CLASS(fair) = अणु

	.enqueue_task		= enqueue_task_fair,
	.dequeue_task		= dequeue_task_fair,
	.yield_task		= yield_task_fair,
	.yield_to_task		= yield_to_task_fair,

	.check_preempt_curr	= check_preempt_wakeup,

	.pick_next_task		= __pick_next_task_fair,
	.put_prev_task		= put_prev_task_fair,
	.set_next_task          = set_next_task_fair,

#अगर_घोषित CONFIG_SMP
	.balance		= balance_fair,
	.select_task_rq		= select_task_rq_fair,
	.migrate_task_rq	= migrate_task_rq_fair,

	.rq_online		= rq_online_fair,
	.rq_offline		= rq_offline_fair,

	.task_dead		= task_dead_fair,
	.set_cpus_allowed	= set_cpus_allowed_common,
#पूर्ण_अगर

	.task_tick		= task_tick_fair,
	.task_विभाजन		= task_विभाजन_fair,

	.prio_changed		= prio_changed_fair,
	.चयनed_from		= चयनed_from_fair,
	.चयनed_to		= चयनed_to_fair,

	.get_rr_पूर्णांकerval	= get_rr_पूर्णांकerval_fair,

	.update_curr		= update_curr_fair,

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	.task_change_group	= task_change_group_fair,
#पूर्ण_अगर

#अगर_घोषित CONFIG_UCLAMP_TASK
	.uclamp_enabled		= 1,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SCHED_DEBUG
व्योम prपूर्णांक_cfs_stats(काष्ठा seq_file *m, पूर्णांक cpu)
अणु
	काष्ठा cfs_rq *cfs_rq, *pos;

	rcu_पढ़ो_lock();
	क्रम_each_leaf_cfs_rq_safe(cpu_rq(cpu), cfs_rq, pos)
		prपूर्णांक_cfs_rq(m, cpu, cfs_rq);
	rcu_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
व्योम show_numa_stats(काष्ठा task_काष्ठा *p, काष्ठा seq_file *m)
अणु
	पूर्णांक node;
	अचिन्हित दीर्घ tsf = 0, tpf = 0, gsf = 0, gpf = 0;
	काष्ठा numa_group *ng;

	rcu_पढ़ो_lock();
	ng = rcu_dereference(p->numa_group);
	क्रम_each_online_node(node) अणु
		अगर (p->numa_faults) अणु
			tsf = p->numa_faults[task_faults_idx(NUMA_MEM, node, 0)];
			tpf = p->numa_faults[task_faults_idx(NUMA_MEM, node, 1)];
		पूर्ण
		अगर (ng) अणु
			gsf = ng->faults[task_faults_idx(NUMA_MEM, node, 0)],
			gpf = ng->faults[task_faults_idx(NUMA_MEM, node, 1)];
		पूर्ण
		prपूर्णांक_numa_stats(m, node, tsf, tpf, gsf, gpf);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */

__init व्योम init_sched_fair_class(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	खोलो_softirq(SCHED_SOFTIRQ, run_rebalance_करोमुख्यs);

#अगर_घोषित CONFIG_NO_HZ_COMMON
	nohz.next_balance = jअगरfies;
	nohz.next_blocked = jअगरfies;
	zalloc_cpumask_var(&nohz.idle_cpus_mask, GFP_NOWAIT);
#पूर्ण_अगर
#पूर्ण_अगर /* SMP */

पूर्ण

/*
 * Helper functions to facilitate extracting info from tracepoपूर्णांकs.
 */

स्थिर काष्ठा sched_avg *sched_trace_cfs_rq_avg(काष्ठा cfs_rq *cfs_rq)
अणु
#अगर_घोषित CONFIG_SMP
	वापस cfs_rq ? &cfs_rq->avg : शून्य;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_cfs_rq_avg);

अक्षर *sched_trace_cfs_rq_path(काष्ठा cfs_rq *cfs_rq, अक्षर *str, पूर्णांक len)
अणु
	अगर (!cfs_rq) अणु
		अगर (str)
			strlcpy(str, "(null)", len);
		अन्यथा
			वापस शून्य;
	पूर्ण

	cfs_rq_tg_path(cfs_rq, str, len);
	वापस str;
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_cfs_rq_path);

पूर्णांक sched_trace_cfs_rq_cpu(काष्ठा cfs_rq *cfs_rq)
अणु
	वापस cfs_rq ? cpu_of(rq_of(cfs_rq)) : -1;
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_cfs_rq_cpu);

स्थिर काष्ठा sched_avg *sched_trace_rq_avg_rt(काष्ठा rq *rq)
अणु
#अगर_घोषित CONFIG_SMP
	वापस rq ? &rq->avg_rt : शून्य;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_rq_avg_rt);

स्थिर काष्ठा sched_avg *sched_trace_rq_avg_dl(काष्ठा rq *rq)
अणु
#अगर_घोषित CONFIG_SMP
	वापस rq ? &rq->avg_dl : शून्य;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_rq_avg_dl);

स्थिर काष्ठा sched_avg *sched_trace_rq_avg_irq(काष्ठा rq *rq)
अणु
#अगर defined(CONFIG_SMP) && defined(CONFIG_HAVE_SCHED_AVG_IRQ)
	वापस rq ? &rq->avg_irq : शून्य;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_rq_avg_irq);

पूर्णांक sched_trace_rq_cpu(काष्ठा rq *rq)
अणु
	वापस rq ? cpu_of(rq) : -1;
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_rq_cpu);

पूर्णांक sched_trace_rq_cpu_capacity(काष्ठा rq *rq)
अणु
	वापस rq ?
#अगर_घोषित CONFIG_SMP
		rq->cpu_capacity
#अन्यथा
		SCHED_CAPACITY_SCALE
#पूर्ण_अगर
		: -1;
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_rq_cpu_capacity);

स्थिर काष्ठा cpumask *sched_trace_rd_span(काष्ठा root_करोमुख्य *rd)
अणु
#अगर_घोषित CONFIG_SMP
	वापस rd ? rd->span : शून्य;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_rd_span);

पूर्णांक sched_trace_rq_nr_running(काष्ठा rq *rq)
अणु
        वापस rq ? rq->nr_running : -1;
पूर्ण
EXPORT_SYMBOL_GPL(sched_trace_rq_nr_running);
