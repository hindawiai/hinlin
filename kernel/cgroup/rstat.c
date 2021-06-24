<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश "cgroup-internal.h"

#समावेश <linux/sched/cpuसमय.स>

अटल DEFINE_SPINLOCK(cgroup_rstat_lock);
अटल DEFINE_PER_CPU(raw_spinlock_t, cgroup_rstat_cpu_lock);

अटल व्योम cgroup_base_stat_flush(काष्ठा cgroup *cgrp, पूर्णांक cpu);

अटल काष्ठा cgroup_rstat_cpu *cgroup_rstat_cpu(काष्ठा cgroup *cgrp, पूर्णांक cpu)
अणु
	वापस per_cpu_ptr(cgrp->rstat_cpu, cpu);
पूर्ण

/**
 * cgroup_rstat_updated - keep track of updated rstat_cpu
 * @cgrp: target cgroup
 * @cpu: cpu on which rstat_cpu was updated
 *
 * @cgrp's rstat_cpu on @cpu was updated.  Put it on the parent's matching
 * rstat_cpu->updated_children list.  See the comment on top of
 * cgroup_rstat_cpu definition क्रम details.
 */
व्योम cgroup_rstat_updated(काष्ठा cgroup *cgrp, पूर्णांक cpu)
अणु
	raw_spinlock_t *cpu_lock = per_cpu_ptr(&cgroup_rstat_cpu_lock, cpu);
	अचिन्हित दीर्घ flags;

	/*
	 * Speculative alपढ़ोy-on-list test. This may race leading to
	 * temporary inaccuracies, which is fine.
	 *
	 * Because @parent's updated_children is terminated with @parent
	 * instead of शून्य, we can tell whether @cgrp is on the list by
	 * testing the next poपूर्णांकer क्रम शून्य.
	 */
	अगर (cgroup_rstat_cpu(cgrp, cpu)->updated_next)
		वापस;

	raw_spin_lock_irqsave(cpu_lock, flags);

	/* put @cgrp and all ancestors on the corresponding updated lists */
	जबतक (true) अणु
		काष्ठा cgroup_rstat_cpu *rstatc = cgroup_rstat_cpu(cgrp, cpu);
		काष्ठा cgroup *parent = cgroup_parent(cgrp);
		काष्ठा cgroup_rstat_cpu *prstatc;

		/*
		 * Both additions and removals are bottom-up.  If a cgroup
		 * is alपढ़ोy in the tree, all ancestors are.
		 */
		अगर (rstatc->updated_next)
			अवरोध;

		/* Root has no parent to link it to, but mark it busy */
		अगर (!parent) अणु
			rstatc->updated_next = cgrp;
			अवरोध;
		पूर्ण

		prstatc = cgroup_rstat_cpu(parent, cpu);
		rstatc->updated_next = prstatc->updated_children;
		prstatc->updated_children = cgrp;

		cgrp = parent;
	पूर्ण

	raw_spin_unlock_irqrestore(cpu_lock, flags);
पूर्ण

/**
 * cgroup_rstat_cpu_pop_updated - iterate and dismantle rstat_cpu updated tree
 * @pos: current position
 * @root: root of the tree to traversal
 * @cpu: target cpu
 *
 * Walks the updated rstat_cpu tree on @cpu from @root.  %शून्य @pos starts
 * the traversal and %शून्य वापस indicates the end.  During traversal,
 * each वापसed cgroup is unlinked from the tree.  Must be called with the
 * matching cgroup_rstat_cpu_lock held.
 *
 * The only ordering guarantee is that, क्रम a parent and a child pair
 * covered by a given traversal, अगर a child is visited, its parent is
 * guaranteed to be visited afterwards.
 */
अटल काष्ठा cgroup *cgroup_rstat_cpu_pop_updated(काष्ठा cgroup *pos,
						   काष्ठा cgroup *root, पूर्णांक cpu)
अणु
	काष्ठा cgroup_rstat_cpu *rstatc;

	अगर (pos == root)
		वापस शून्य;

	/*
	 * We're gonna walk करोwn to the first leaf and visit/हटाओ it.  We
	 * can pick whatever unvisited node as the starting poपूर्णांक.
	 */
	अगर (!pos)
		pos = root;
	अन्यथा
		pos = cgroup_parent(pos);

	/* walk करोwn to the first leaf */
	जबतक (true) अणु
		rstatc = cgroup_rstat_cpu(pos, cpu);
		अगर (rstatc->updated_children == pos)
			अवरोध;
		pos = rstatc->updated_children;
	पूर्ण

	/*
	 * Unlink @pos from the tree.  As the updated_children list is
	 * singly linked, we have to walk it to find the removal poपूर्णांक.
	 * However, due to the way we traverse, @pos will be the first
	 * child in most हालs. The only exception is @root.
	 */
	अगर (rstatc->updated_next) अणु
		काष्ठा cgroup *parent = cgroup_parent(pos);

		अगर (parent) अणु
			काष्ठा cgroup_rstat_cpu *prstatc;
			काष्ठा cgroup **nextp;

			prstatc = cgroup_rstat_cpu(parent, cpu);
			nextp = &prstatc->updated_children;
			जबतक (true) अणु
				काष्ठा cgroup_rstat_cpu *nrstatc;

				nrstatc = cgroup_rstat_cpu(*nextp, cpu);
				अगर (*nextp == pos)
					अवरोध;
				WARN_ON_ONCE(*nextp == parent);
				nextp = &nrstatc->updated_next;
			पूर्ण
			*nextp = rstatc->updated_next;
		पूर्ण

		rstatc->updated_next = शून्य;
		वापस pos;
	पूर्ण

	/* only happens क्रम @root */
	वापस शून्य;
पूर्ण

/* see cgroup_rstat_flush() */
अटल व्योम cgroup_rstat_flush_locked(काष्ठा cgroup *cgrp, bool may_sleep)
	__releases(&cgroup_rstat_lock) __acquires(&cgroup_rstat_lock)
अणु
	पूर्णांक cpu;

	lockdep_निश्चित_held(&cgroup_rstat_lock);

	क्रम_each_possible_cpu(cpu) अणु
		raw_spinlock_t *cpu_lock = per_cpu_ptr(&cgroup_rstat_cpu_lock,
						       cpu);
		काष्ठा cgroup *pos = शून्य;

		raw_spin_lock(cpu_lock);
		जबतक ((pos = cgroup_rstat_cpu_pop_updated(pos, cgrp, cpu))) अणु
			काष्ठा cgroup_subsys_state *css;

			cgroup_base_stat_flush(pos, cpu);

			rcu_पढ़ो_lock();
			list_क्रम_each_entry_rcu(css, &pos->rstat_css_list,
						rstat_css_node)
				css->ss->css_rstat_flush(css, cpu);
			rcu_पढ़ो_unlock();
		पूर्ण
		raw_spin_unlock(cpu_lock);

		/* अगर @may_sleep, play nice and yield अगर necessary */
		अगर (may_sleep && (need_resched() ||
				  spin_needअवरोध(&cgroup_rstat_lock))) अणु
			spin_unlock_irq(&cgroup_rstat_lock);
			अगर (!cond_resched())
				cpu_relax();
			spin_lock_irq(&cgroup_rstat_lock);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cgroup_rstat_flush - flush stats in @cgrp's subtree
 * @cgrp: target cgroup
 *
 * Collect all per-cpu stats in @cgrp's subtree पूर्णांकo the global counters
 * and propagate them upwards.  After this function वापसs, all cgroups in
 * the subtree have up-to-date ->stat.
 *
 * This also माला_लो all cgroups in the subtree including @cgrp off the
 * ->updated_children lists.
 *
 * This function may block.
 */
व्योम cgroup_rstat_flush(काष्ठा cgroup *cgrp)
अणु
	might_sleep();

	spin_lock_irq(&cgroup_rstat_lock);
	cgroup_rstat_flush_locked(cgrp, true);
	spin_unlock_irq(&cgroup_rstat_lock);
पूर्ण

/**
 * cgroup_rstat_flush_irqsafe - irqsafe version of cgroup_rstat_flush()
 * @cgrp: target cgroup
 *
 * This function can be called from any context.
 */
व्योम cgroup_rstat_flush_irqsafe(काष्ठा cgroup *cgrp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cgroup_rstat_lock, flags);
	cgroup_rstat_flush_locked(cgrp, false);
	spin_unlock_irqrestore(&cgroup_rstat_lock, flags);
पूर्ण

/**
 * cgroup_rstat_flush_begin - flush stats in @cgrp's subtree and hold
 * @cgrp: target cgroup
 *
 * Flush stats in @cgrp's subtree and prevent further flushes.  Must be
 * paired with cgroup_rstat_flush_release().
 *
 * This function may block.
 */
व्योम cgroup_rstat_flush_hold(काष्ठा cgroup *cgrp)
	__acquires(&cgroup_rstat_lock)
अणु
	might_sleep();
	spin_lock_irq(&cgroup_rstat_lock);
	cgroup_rstat_flush_locked(cgrp, true);
पूर्ण

/**
 * cgroup_rstat_flush_release - release cgroup_rstat_flush_hold()
 */
व्योम cgroup_rstat_flush_release(व्योम)
	__releases(&cgroup_rstat_lock)
अणु
	spin_unlock_irq(&cgroup_rstat_lock);
पूर्ण

पूर्णांक cgroup_rstat_init(काष्ठा cgroup *cgrp)
अणु
	पूर्णांक cpu;

	/* the root cgrp has rstat_cpu pपुनः_स्मृतिated */
	अगर (!cgrp->rstat_cpu) अणु
		cgrp->rstat_cpu = alloc_percpu(काष्ठा cgroup_rstat_cpu);
		अगर (!cgrp->rstat_cpu)
			वापस -ENOMEM;
	पूर्ण

	/* ->updated_children list is self terminated */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cgroup_rstat_cpu *rstatc = cgroup_rstat_cpu(cgrp, cpu);

		rstatc->updated_children = cgrp;
		u64_stats_init(&rstatc->bsync);
	पूर्ण

	वापस 0;
पूर्ण

व्योम cgroup_rstat_निकास(काष्ठा cgroup *cgrp)
अणु
	पूर्णांक cpu;

	cgroup_rstat_flush(cgrp);

	/* sanity check */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cgroup_rstat_cpu *rstatc = cgroup_rstat_cpu(cgrp, cpu);

		अगर (WARN_ON_ONCE(rstatc->updated_children != cgrp) ||
		    WARN_ON_ONCE(rstatc->updated_next))
			वापस;
	पूर्ण

	मुक्त_percpu(cgrp->rstat_cpu);
	cgrp->rstat_cpu = शून्य;
पूर्ण

व्योम __init cgroup_rstat_boot(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		raw_spin_lock_init(per_cpu_ptr(&cgroup_rstat_cpu_lock, cpu));
पूर्ण

/*
 * Functions क्रम cgroup basic resource statistics implemented on top of
 * rstat.
 */
अटल व्योम cgroup_base_stat_add(काष्ठा cgroup_base_stat *dst_bstat,
				 काष्ठा cgroup_base_stat *src_bstat)
अणु
	dst_bstat->cpuसमय.uसमय += src_bstat->cpuसमय.uसमय;
	dst_bstat->cpuसमय.sसमय += src_bstat->cpuसमय.sसमय;
	dst_bstat->cpuसमय.sum_exec_runसमय += src_bstat->cpuसमय.sum_exec_runसमय;
पूर्ण

अटल व्योम cgroup_base_stat_sub(काष्ठा cgroup_base_stat *dst_bstat,
				 काष्ठा cgroup_base_stat *src_bstat)
अणु
	dst_bstat->cpuसमय.uसमय -= src_bstat->cpuसमय.uसमय;
	dst_bstat->cpuसमय.sसमय -= src_bstat->cpuसमय.sसमय;
	dst_bstat->cpuसमय.sum_exec_runसमय -= src_bstat->cpuसमय.sum_exec_runसमय;
पूर्ण

अटल व्योम cgroup_base_stat_flush(काष्ठा cgroup *cgrp, पूर्णांक cpu)
अणु
	काष्ठा cgroup_rstat_cpu *rstatc = cgroup_rstat_cpu(cgrp, cpu);
	काष्ठा cgroup *parent = cgroup_parent(cgrp);
	काष्ठा cgroup_base_stat cur, delta;
	अचिन्हित seq;

	/* Root-level stats are sourced from प्रणाली-wide CPU stats */
	अगर (!parent)
		वापस;

	/* fetch the current per-cpu values */
	करो अणु
		seq = __u64_stats_fetch_begin(&rstatc->bsync);
		cur.cpuसमय = rstatc->bstat.cpuसमय;
	पूर्ण जबतक (__u64_stats_fetch_retry(&rstatc->bsync, seq));

	/* propagate percpu delta to global */
	delta = cur;
	cgroup_base_stat_sub(&delta, &rstatc->last_bstat);
	cgroup_base_stat_add(&cgrp->bstat, &delta);
	cgroup_base_stat_add(&rstatc->last_bstat, &delta);

	/* propagate global delta to parent (unless that's root) */
	अगर (cgroup_parent(parent)) अणु
		delta = cgrp->bstat;
		cgroup_base_stat_sub(&delta, &cgrp->last_bstat);
		cgroup_base_stat_add(&parent->bstat, &delta);
		cgroup_base_stat_add(&cgrp->last_bstat, &delta);
	पूर्ण
पूर्ण

अटल काष्ठा cgroup_rstat_cpu *
cgroup_base_stat_cpuसमय_account_begin(काष्ठा cgroup *cgrp)
अणु
	काष्ठा cgroup_rstat_cpu *rstatc;

	rstatc = get_cpu_ptr(cgrp->rstat_cpu);
	u64_stats_update_begin(&rstatc->bsync);
	वापस rstatc;
पूर्ण

अटल व्योम cgroup_base_stat_cpuसमय_account_end(काष्ठा cgroup *cgrp,
						 काष्ठा cgroup_rstat_cpu *rstatc)
अणु
	u64_stats_update_end(&rstatc->bsync);
	cgroup_rstat_updated(cgrp, smp_processor_id());
	put_cpu_ptr(rstatc);
पूर्ण

व्योम __cgroup_account_cpuसमय(काष्ठा cgroup *cgrp, u64 delta_exec)
अणु
	काष्ठा cgroup_rstat_cpu *rstatc;

	rstatc = cgroup_base_stat_cpuसमय_account_begin(cgrp);
	rstatc->bstat.cpuसमय.sum_exec_runसमय += delta_exec;
	cgroup_base_stat_cpuसमय_account_end(cgrp, rstatc);
पूर्ण

व्योम __cgroup_account_cpuसमय_field(काष्ठा cgroup *cgrp,
				    क्रमागत cpu_usage_stat index, u64 delta_exec)
अणु
	काष्ठा cgroup_rstat_cpu *rstatc;

	rstatc = cgroup_base_stat_cpuसमय_account_begin(cgrp);

	चयन (index) अणु
	हाल CPUTIME_USER:
	हाल CPUTIME_NICE:
		rstatc->bstat.cpuसमय.uसमय += delta_exec;
		अवरोध;
	हाल CPUTIME_SYSTEM:
	हाल CPUTIME_IRQ:
	हाल CPUTIME_SOFTIRQ:
		rstatc->bstat.cpuसमय.sसमय += delta_exec;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	cgroup_base_stat_cpuसमय_account_end(cgrp, rstatc);
पूर्ण

/*
 * compute the cpuसमय क्रम the root cgroup by getting the per cpu data
 * at a global level, then categorizing the fields in a manner consistent
 * with how it is करोne by __cgroup_account_cpuसमय_field क्रम each bit of
 * cpu समय attributed to a cgroup.
 */
अटल व्योम root_cgroup_cpuसमय(काष्ठा task_cpuसमय *cpuसमय)
अणु
	पूर्णांक i;

	cpuसमय->sसमय = 0;
	cpuसमय->uसमय = 0;
	cpuसमय->sum_exec_runसमय = 0;
	क्रम_each_possible_cpu(i) अणु
		काष्ठा kernel_cpustat kcpustat;
		u64 *cpustat = kcpustat.cpustat;
		u64 user = 0;
		u64 sys = 0;

		kcpustat_cpu_fetch(&kcpustat, i);

		user += cpustat[CPUTIME_USER];
		user += cpustat[CPUTIME_NICE];
		cpuसमय->uसमय += user;

		sys += cpustat[CPUTIME_SYSTEM];
		sys += cpustat[CPUTIME_IRQ];
		sys += cpustat[CPUTIME_SOFTIRQ];
		cpuसमय->sसमय += sys;

		cpuसमय->sum_exec_runसमय += user;
		cpuसमय->sum_exec_runसमय += sys;
		cpuसमय->sum_exec_runसमय += cpustat[CPUTIME_STEAL];
		cpuसमय->sum_exec_runसमय += cpustat[CPUTIME_GUEST];
		cpuसमय->sum_exec_runसमय += cpustat[CPUTIME_GUEST_NICE];
	पूर्ण
पूर्ण

व्योम cgroup_base_stat_cpuसमय_show(काष्ठा seq_file *seq)
अणु
	काष्ठा cgroup *cgrp = seq_css(seq)->cgroup;
	u64 usage, uसमय, sसमय;
	काष्ठा task_cpuसमय cpuसमय;

	अगर (cgroup_parent(cgrp)) अणु
		cgroup_rstat_flush_hold(cgrp);
		usage = cgrp->bstat.cpuसमय.sum_exec_runसमय;
		cpuसमय_adjust(&cgrp->bstat.cpuसमय, &cgrp->prev_cpuसमय,
			       &uसमय, &sसमय);
		cgroup_rstat_flush_release();
	पूर्ण अन्यथा अणु
		root_cgroup_cpuसमय(&cpuसमय);
		usage = cpuसमय.sum_exec_runसमय;
		uसमय = cpuसमय.uसमय;
		sसमय = cpuसमय.sसमय;
	पूर्ण

	करो_भाग(usage, NSEC_PER_USEC);
	करो_भाग(uसमय, NSEC_PER_USEC);
	करो_भाग(sसमय, NSEC_PER_USEC);

	seq_म_लिखो(seq, "usage_usec %llu\n"
		   "user_usec %llu\n"
		   "system_usec %llu\n",
		   usage, uसमय, sसमय);
पूर्ण
