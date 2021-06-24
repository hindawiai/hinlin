<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Read-Copy Update mechanism क्रम mutual exclusion (tree-based version)
 * Internal non-खुला definitions that provide either classic
 * or preemptible semantics.
 *
 * Copyright Red Hat, 2009
 * Copyright IBM Corporation, 2009
 *
 * Author: Ingo Molnar <mingo@elte.hu>
 *	   Paul E. McKenney <paulmck@linux.ibm.com>
 */

#समावेश "../locking/rtmutex_common.h"

#अगर_घोषित CONFIG_RCU_NOCB_CPU
अटल cpumask_var_t rcu_nocb_mask; /* CPUs to have callbacks offloaded. */
अटल bool __पढ़ो_mostly rcu_nocb_poll;    /* Offload kthपढ़ो are to poll. */
अटल अंतरभूत पूर्णांक rcu_lockdep_is_held_nocb(काष्ठा rcu_data *rdp)
अणु
	वापस lockdep_is_held(&rdp->nocb_lock);
पूर्ण

अटल अंतरभूत bool rcu_current_is_nocb_kthपढ़ो(काष्ठा rcu_data *rdp)
अणु
	/* Race on early boot between thपढ़ो creation and assignment */
	अगर (!rdp->nocb_cb_kthपढ़ो || !rdp->nocb_gp_kthपढ़ो)
		वापस true;

	अगर (current == rdp->nocb_cb_kthपढ़ो || current == rdp->nocb_gp_kthपढ़ो)
		अगर (in_task())
			वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool rcu_running_nocb_समयr(काष्ठा rcu_data *rdp)
अणु
	वापस (समयr_curr_running(&rdp->nocb_समयr) && !in_irq());
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक rcu_lockdep_is_held_nocb(काष्ठा rcu_data *rdp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool rcu_current_is_nocb_kthपढ़ो(काष्ठा rcu_data *rdp)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool rcu_running_nocb_समयr(काष्ठा rcu_data *rdp)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* #अगर_घोषित CONFIG_RCU_NOCB_CPU */

अटल bool rcu_rdp_is_offloaded(काष्ठा rcu_data *rdp)
अणु
	/*
	 * In order to पढ़ो the offloaded state of an rdp is a safe
	 * and stable way and prevent from its value to be changed
	 * under us, we must either hold the barrier mutex, the cpu
	 * hotplug lock (पढ़ो or ग_लिखो) or the nocb lock. Local
	 * non-preemptible पढ़ोs are also safe. NOCB kthपढ़ोs and
	 * समयrs have their own means of synchronization against the
	 * offloaded state updaters.
	 */
	RCU_LOCKDEP_WARN(
		!(lockdep_is_held(&rcu_state.barrier_mutex) ||
		  (IS_ENABLED(CONFIG_HOTPLUG_CPU) && lockdep_is_cpus_held()) ||
		  rcu_lockdep_is_held_nocb(rdp) ||
		  (rdp == this_cpu_ptr(&rcu_data) &&
		   !(IS_ENABLED(CONFIG_PREEMPT_COUNT) && preemptible())) ||
		  rcu_current_is_nocb_kthपढ़ो(rdp) ||
		  rcu_running_nocb_समयr(rdp)),
		"Unsafe read of RCU_NOCB offloaded state"
	);

	वापस rcu_segcblist_is_offloaded(&rdp->cblist);
पूर्ण

/*
 * Check the RCU kernel configuration parameters and prपूर्णांक inक्रमmative
 * messages about anything out of the ordinary.
 */
अटल व्योम __init rcu_bootup_announce_oddness(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_RCU_TRACE))
		pr_info("\tRCU event tracing is enabled.\n");
	अगर ((IS_ENABLED(CONFIG_64BIT) && RCU_FANOUT != 64) ||
	    (!IS_ENABLED(CONFIG_64BIT) && RCU_FANOUT != 32))
		pr_info("\tCONFIG_RCU_FANOUT set to non-default value of %d.\n",
			RCU_FANOUT);
	अगर (rcu_fanout_exact)
		pr_info("\tHierarchical RCU autobalancing is disabled.\n");
	अगर (IS_ENABLED(CONFIG_RCU_FAST_NO_HZ))
		pr_info("\tRCU dyntick-idle grace-period acceleration is enabled.\n");
	अगर (IS_ENABLED(CONFIG_PROVE_RCU))
		pr_info("\tRCU lockdep checking is enabled.\n");
	अगर (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD))
		pr_info("\tRCU strict (and thus non-scalable) grace periods enabled.\n");
	अगर (RCU_NUM_LVLS >= 4)
		pr_info("\tFour(or more)-level hierarchy is enabled.\n");
	अगर (RCU_FANOUT_LEAF != 16)
		pr_info("\tBuild-time adjustment of leaf fanout to %d.\n",
			RCU_FANOUT_LEAF);
	अगर (rcu_fanout_leaf != RCU_FANOUT_LEAF)
		pr_info("\tBoot-time adjustment of leaf fanout to %d.\n",
			rcu_fanout_leaf);
	अगर (nr_cpu_ids != NR_CPUS)
		pr_info("\tRCU restricting CPUs from NR_CPUS=%d to nr_cpu_ids=%u.\n", NR_CPUS, nr_cpu_ids);
#अगर_घोषित CONFIG_RCU_BOOST
	pr_info("\tRCU priority boosting: priority %d delay %d ms.\n",
		kthपढ़ो_prio, CONFIG_RCU_BOOST_DELAY);
#पूर्ण_अगर
	अगर (blimit != DEFAULT_RCU_BLIMIT)
		pr_info("\tBoot-time adjustment of callback invocation limit to %ld.\n", blimit);
	अगर (qhimark != DEFAULT_RCU_QHIMARK)
		pr_info("\tBoot-time adjustment of callback high-water mark to %ld.\n", qhimark);
	अगर (qlowmark != DEFAULT_RCU_QLOMARK)
		pr_info("\tBoot-time adjustment of callback low-water mark to %ld.\n", qlowmark);
	अगर (qovld != DEFAULT_RCU_QOVLD)
		pr_info("\tBoot-time adjustment of callback overload level to %ld.\n", qovld);
	अगर (jअगरfies_till_first_fqs != अच_दीर्घ_उच्च)
		pr_info("\tBoot-time adjustment of first FQS scan delay to %ld jiffies.\n", jअगरfies_till_first_fqs);
	अगर (jअगरfies_till_next_fqs != अच_दीर्घ_उच्च)
		pr_info("\tBoot-time adjustment of subsequent FQS scan delay to %ld jiffies.\n", jअगरfies_till_next_fqs);
	अगर (jअगरfies_till_sched_qs != अच_दीर्घ_उच्च)
		pr_info("\tBoot-time adjustment of scheduler-enlistment delay to %ld jiffies.\n", jअगरfies_till_sched_qs);
	अगर (rcu_kick_kthपढ़ोs)
		pr_info("\tKick kthreads if too-long grace period.\n");
	अगर (IS_ENABLED(CONFIG_DEBUG_OBJECTS_RCU_HEAD))
		pr_info("\tRCU callback double-/use-after-free debug enabled.\n");
	अगर (gp_preinit_delay)
		pr_info("\tRCU debug GP pre-init slowdown %d jiffies.\n", gp_preinit_delay);
	अगर (gp_init_delay)
		pr_info("\tRCU debug GP init slowdown %d jiffies.\n", gp_init_delay);
	अगर (gp_cleanup_delay)
		pr_info("\tRCU debug GP init slowdown %d jiffies.\n", gp_cleanup_delay);
	अगर (!use_softirq)
		pr_info("\tRCU_SOFTIRQ processing moved to rcuc kthreads.\n");
	अगर (IS_ENABLED(CONFIG_RCU_EQS_DEBUG))
		pr_info("\tRCU debug extended QS entry/exit.\n");
	rcupdate_announce_bootup_oddness();
पूर्ण

#अगर_घोषित CONFIG_PREEMPT_RCU

अटल व्योम rcu_report_exp_rnp(काष्ठा rcu_node *rnp, bool wake);
अटल व्योम rcu_पढ़ो_unlock_special(काष्ठा task_काष्ठा *t);

/*
 * Tell them what RCU they are running.
 */
अटल व्योम __init rcu_bootup_announce(व्योम)
अणु
	pr_info("Preemptible hierarchical RCU implementation.\n");
	rcu_bootup_announce_oddness();
पूर्ण

/* Flags क्रम rcu_preempt_ctxt_queue() decision table. */
#घोषणा RCU_GP_TASKS	0x8
#घोषणा RCU_EXP_TASKS	0x4
#घोषणा RCU_GP_BLKD	0x2
#घोषणा RCU_EXP_BLKD	0x1

/*
 * Queues a task preempted within an RCU-preempt पढ़ो-side critical
 * section पूर्णांकo the appropriate location within the ->blkd_tasks list,
 * depending on the states of any ongoing normal and expedited grace
 * periods.  The ->gp_tasks poपूर्णांकer indicates which element the normal
 * grace period is रुकोing on (शून्य अगर none), and the ->exp_tasks poपूर्णांकer
 * indicates which element the expedited grace period is रुकोing on (again,
 * शून्य अगर none).  If a grace period is रुकोing on a given element in the
 * ->blkd_tasks list, it also रुकोs on all subsequent elements.  Thus,
 * adding a task to the tail of the list blocks any grace period that is
 * alपढ़ोy रुकोing on one of the elements.  In contrast, adding a task
 * to the head of the list won't block any grace period that is alपढ़ोy
 * रुकोing on one of the elements.
 *
 * This queuing is imprecise, and can someबार make an ongoing grace
 * period रुको क्रम a task that is not strictly speaking blocking it.
 * Given the choice, we needlessly block a normal grace period rather than
 * blocking an expedited grace period.
 *
 * Note that an endless sequence of expedited grace periods still cannot
 * indefinitely postpone a normal grace period.  Eventually, all of the
 * fixed number of preempted tasks blocking the normal grace period that are
 * not also blocking the expedited grace period will resume and complete
 * their RCU पढ़ो-side critical sections.  At that poपूर्णांक, the ->gp_tasks
 * poपूर्णांकer will equal the ->exp_tasks poपूर्णांकer, at which poपूर्णांक the end of
 * the corresponding expedited grace period will also be the end of the
 * normal grace period.
 */
अटल व्योम rcu_preempt_ctxt_queue(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp)
	__releases(rnp->lock) /* But leaves rrupts disabled. */
अणु
	पूर्णांक blkd_state = (rnp->gp_tasks ? RCU_GP_TASKS : 0) +
			 (rnp->exp_tasks ? RCU_EXP_TASKS : 0) +
			 (rnp->qsmask & rdp->grpmask ? RCU_GP_BLKD : 0) +
			 (rnp->expmask & rdp->grpmask ? RCU_EXP_BLKD : 0);
	काष्ठा task_काष्ठा *t = current;

	raw_lockdep_निश्चित_held_rcu_node(rnp);
	WARN_ON_ONCE(rdp->mynode != rnp);
	WARN_ON_ONCE(!rcu_is_leaf_node(rnp));
	/* RCU better not be रुकोing on newly onlined CPUs! */
	WARN_ON_ONCE(rnp->qsmaskinitnext & ~rnp->qsmaskinit & rnp->qsmask &
		     rdp->grpmask);

	/*
	 * Decide where to queue the newly blocked task.  In theory,
	 * this could be an अगर-statement.  In practice, when I tried
	 * that, it was quite messy.
	 */
	चयन (blkd_state) अणु
	हाल 0:
	हाल                RCU_EXP_TASKS:
	हाल                RCU_EXP_TASKS + RCU_GP_BLKD:
	हाल RCU_GP_TASKS:
	हाल RCU_GP_TASKS + RCU_EXP_TASKS:

		/*
		 * Blocking neither GP, or first task blocking the normal
		 * GP but not blocking the alपढ़ोy-रुकोing expedited GP.
		 * Queue at the head of the list to aव्योम unnecessarily
		 * blocking the alपढ़ोy-रुकोing GPs.
		 */
		list_add(&t->rcu_node_entry, &rnp->blkd_tasks);
		अवरोध;

	हाल                                              RCU_EXP_BLKD:
	हाल                                RCU_GP_BLKD:
	हाल                                RCU_GP_BLKD + RCU_EXP_BLKD:
	हाल RCU_GP_TASKS +                               RCU_EXP_BLKD:
	हाल RCU_GP_TASKS +                 RCU_GP_BLKD + RCU_EXP_BLKD:
	हाल RCU_GP_TASKS + RCU_EXP_TASKS + RCU_GP_BLKD + RCU_EXP_BLKD:

		/*
		 * First task arriving that blocks either GP, or first task
		 * arriving that blocks the expedited GP (with the normal
		 * GP alपढ़ोy रुकोing), or a task arriving that blocks
		 * both GPs with both GPs alपढ़ोy रुकोing.  Queue at the
		 * tail of the list to aव्योम any GP रुकोing on any of the
		 * alपढ़ोy queued tasks that are not blocking it.
		 */
		list_add_tail(&t->rcu_node_entry, &rnp->blkd_tasks);
		अवरोध;

	हाल                RCU_EXP_TASKS +               RCU_EXP_BLKD:
	हाल                RCU_EXP_TASKS + RCU_GP_BLKD + RCU_EXP_BLKD:
	हाल RCU_GP_TASKS + RCU_EXP_TASKS +               RCU_EXP_BLKD:

		/*
		 * Second or subsequent task blocking the expedited GP.
		 * The task either करोes not block the normal GP, or is the
		 * first task blocking the normal GP.  Queue just after
		 * the first task blocking the expedited GP.
		 */
		list_add(&t->rcu_node_entry, rnp->exp_tasks);
		अवरोध;

	हाल RCU_GP_TASKS +                 RCU_GP_BLKD:
	हाल RCU_GP_TASKS + RCU_EXP_TASKS + RCU_GP_BLKD:

		/*
		 * Second or subsequent task blocking the normal GP.
		 * The task करोes not block the expedited GP. Queue just
		 * after the first task blocking the normal GP.
		 */
		list_add(&t->rcu_node_entry, rnp->gp_tasks);
		अवरोध;

	शेष:

		/* Yet another exercise in excessive paranoia. */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	/*
	 * We have now queued the task.  If it was the first one to
	 * block either grace period, update the ->gp_tasks and/or
	 * ->exp_tasks poपूर्णांकers, respectively, to reference the newly
	 * blocked tasks.
	 */
	अगर (!rnp->gp_tasks && (blkd_state & RCU_GP_BLKD)) अणु
		WRITE_ONCE(rnp->gp_tasks, &t->rcu_node_entry);
		WARN_ON_ONCE(rnp->completedqs == rnp->gp_seq);
	पूर्ण
	अगर (!rnp->exp_tasks && (blkd_state & RCU_EXP_BLKD))
		WRITE_ONCE(rnp->exp_tasks, &t->rcu_node_entry);
	WARN_ON_ONCE(!(blkd_state & RCU_GP_BLKD) !=
		     !(rnp->qsmask & rdp->grpmask));
	WARN_ON_ONCE(!(blkd_state & RCU_EXP_BLKD) !=
		     !(rnp->expmask & rdp->grpmask));
	raw_spin_unlock_rcu_node(rnp); /* पूर्णांकerrupts reमुख्य disabled. */

	/*
	 * Report the quiescent state क्रम the expedited GP.  This expedited
	 * GP should not be able to end until we report, so there should be
	 * no need to check क्रम a subsequent expedited GP.  (Though we are
	 * still in a quiescent state in any हाल.)
	 */
	अगर (blkd_state & RCU_EXP_BLKD && rdp->exp_deferred_qs)
		rcu_report_exp_rdp(rdp);
	अन्यथा
		WARN_ON_ONCE(rdp->exp_deferred_qs);
पूर्ण

/*
 * Record a preemptible-RCU quiescent state क्रम the specअगरied CPU.
 * Note that this करोes not necessarily mean that the task currently running
 * on the CPU is in a quiescent state:  Instead, it means that the current
 * grace period need not रुको on any RCU पढ़ो-side critical section that
 * starts later on this CPU.  It also means that अगर the current task is
 * in an RCU पढ़ो-side critical section, it has alपढ़ोy added itself to
 * some leaf rcu_node काष्ठाure's ->blkd_tasks list.  In addition to the
 * current task, there might be any number of other tasks blocked जबतक
 * in an RCU पढ़ो-side critical section.
 *
 * Callers to this function must disable preemption.
 */
अटल व्योम rcu_qs(व्योम)
अणु
	RCU_LOCKDEP_WARN(preemptible(), "rcu_qs() invoked with preemption enabled!!!\n");
	अगर (__this_cpu_पढ़ो(rcu_data.cpu_no_qs.s)) अणु
		trace_rcu_grace_period(TPS("rcu_preempt"),
				       __this_cpu_पढ़ो(rcu_data.gp_seq),
				       TPS("cpuqs"));
		__this_cpu_ग_लिखो(rcu_data.cpu_no_qs.b.norm, false);
		barrier(); /* Coordinate with rcu_flavor_sched_घड़ी_irq(). */
		WRITE_ONCE(current->rcu_पढ़ो_unlock_special.b.need_qs, false);
	पूर्ण
पूर्ण

/*
 * We have entered the scheduler, and the current task might soon be
 * context-चयनed away from.  If this task is in an RCU पढ़ो-side
 * critical section, we will no दीर्घer be able to rely on the CPU to
 * record that fact, so we enqueue the task on the blkd_tasks list.
 * The task will dequeue itself when it निकासs the outermost enclosing
 * RCU पढ़ो-side critical section.  Thereक्रमe, the current grace period
 * cannot be permitted to complete until the blkd_tasks list entries
 * predating the current grace period drain, in other words, until
 * rnp->gp_tasks becomes शून्य.
 *
 * Caller must disable पूर्णांकerrupts.
 */
व्योम rcu_note_context_चयन(bool preempt)
अणु
	काष्ठा task_काष्ठा *t = current;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp;

	trace_rcu_utilization(TPS("Start context switch"));
	lockdep_निश्चित_irqs_disabled();
	WARN_ON_ONCE(!preempt && rcu_preempt_depth() > 0);
	अगर (rcu_preempt_depth() > 0 &&
	    !t->rcu_पढ़ो_unlock_special.b.blocked) अणु

		/* Possibly blocking in an RCU पढ़ो-side critical section. */
		rnp = rdp->mynode;
		raw_spin_lock_rcu_node(rnp);
		t->rcu_पढ़ो_unlock_special.b.blocked = true;
		t->rcu_blocked_node = rnp;

		/*
		 * Verअगरy the CPU's sanity, trace the preemption, and
		 * then queue the task as required based on the states
		 * of any ongoing and expedited grace periods.
		 */
		WARN_ON_ONCE((rdp->grpmask & rcu_rnp_online_cpus(rnp)) == 0);
		WARN_ON_ONCE(!list_empty(&t->rcu_node_entry));
		trace_rcu_preempt_task(rcu_state.name,
				       t->pid,
				       (rnp->qsmask & rdp->grpmask)
				       ? rnp->gp_seq
				       : rcu_seq_snap(&rnp->gp_seq));
		rcu_preempt_ctxt_queue(rnp, rdp);
	पूर्ण अन्यथा अणु
		rcu_preempt_deferred_qs(t);
	पूर्ण

	/*
	 * Either we were not in an RCU पढ़ो-side critical section to
	 * begin with, or we have now recorded that critical section
	 * globally.  Either way, we can now note a quiescent state
	 * क्रम this CPU.  Again, अगर we were in an RCU पढ़ो-side critical
	 * section, and अगर that critical section was blocking the current
	 * grace period, then the fact that the task has been enqueued
	 * means that we जारी to block the current grace period.
	 */
	rcu_qs();
	अगर (rdp->exp_deferred_qs)
		rcu_report_exp_rdp(rdp);
	rcu_tasks_qs(current, preempt);
	trace_rcu_utilization(TPS("End context switch"));
पूर्ण
EXPORT_SYMBOL_GPL(rcu_note_context_चयन);

/*
 * Check क्रम preempted RCU पढ़ोers blocking the current grace period
 * क्रम the specअगरied rcu_node काष्ठाure.  If the caller needs a reliable
 * answer, it must hold the rcu_node's ->lock.
 */
अटल पूर्णांक rcu_preempt_blocked_पढ़ोers_cgp(काष्ठा rcu_node *rnp)
अणु
	वापस READ_ONCE(rnp->gp_tasks) != शून्य;
पूर्ण

/* limit value क्रम ->rcu_पढ़ो_lock_nesting. */
#घोषणा RCU_NEST_PMAX (पूर्णांक_उच्च / 2)

अटल व्योम rcu_preempt_पढ़ो_enter(व्योम)
अणु
	current->rcu_पढ़ो_lock_nesting++;
पूर्ण

अटल पूर्णांक rcu_preempt_पढ़ो_निकास(व्योम)
अणु
	वापस --current->rcu_पढ़ो_lock_nesting;
पूर्ण

अटल व्योम rcu_preempt_depth_set(पूर्णांक val)
अणु
	current->rcu_पढ़ो_lock_nesting = val;
पूर्ण

/*
 * Preemptible RCU implementation क्रम rcu_पढ़ो_lock().
 * Just increment ->rcu_पढ़ो_lock_nesting, shared state will be updated
 * अगर we block.
 */
व्योम __rcu_पढ़ो_lock(व्योम)
अणु
	rcu_preempt_पढ़ो_enter();
	अगर (IS_ENABLED(CONFIG_PROVE_LOCKING))
		WARN_ON_ONCE(rcu_preempt_depth() > RCU_NEST_PMAX);
	अगर (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD) && rcu_state.gp_kthपढ़ो)
		WRITE_ONCE(current->rcu_पढ़ो_unlock_special.b.need_qs, true);
	barrier();  /* critical section after entry code. */
पूर्ण
EXPORT_SYMBOL_GPL(__rcu_पढ़ो_lock);

/*
 * Preemptible RCU implementation क्रम rcu_पढ़ो_unlock().
 * Decrement ->rcu_पढ़ो_lock_nesting.  If the result is zero (outermost
 * rcu_पढ़ो_unlock()) and ->rcu_पढ़ो_unlock_special is non-zero, then
 * invoke rcu_पढ़ो_unlock_special() to clean up after a context चयन
 * in an RCU पढ़ो-side critical section and other special हालs.
 */
व्योम __rcu_पढ़ो_unlock(व्योम)
अणु
	काष्ठा task_काष्ठा *t = current;

	barrier();  // critical section beक्रमe निकास code.
	अगर (rcu_preempt_पढ़ो_निकास() == 0) अणु
		barrier();  // critical-section निकास beक्रमe .s check.
		अगर (unlikely(READ_ONCE(t->rcu_पढ़ो_unlock_special.s)))
			rcu_पढ़ो_unlock_special(t);
	पूर्ण
	अगर (IS_ENABLED(CONFIG_PROVE_LOCKING)) अणु
		पूर्णांक rrln = rcu_preempt_depth();

		WARN_ON_ONCE(rrln < 0 || rrln > RCU_NEST_PMAX);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__rcu_पढ़ो_unlock);

/*
 * Advance a ->blkd_tasks-list poपूर्णांकer to the next entry, instead
 * वापसing शून्य अगर at the end of the list.
 */
अटल काष्ठा list_head *rcu_next_node_entry(काष्ठा task_काष्ठा *t,
					     काष्ठा rcu_node *rnp)
अणु
	काष्ठा list_head *np;

	np = t->rcu_node_entry.next;
	अगर (np == &rnp->blkd_tasks)
		np = शून्य;
	वापस np;
पूर्ण

/*
 * Return true अगर the specअगरied rcu_node काष्ठाure has tasks that were
 * preempted within an RCU पढ़ो-side critical section.
 */
अटल bool rcu_preempt_has_tasks(काष्ठा rcu_node *rnp)
अणु
	वापस !list_empty(&rnp->blkd_tasks);
पूर्ण

/*
 * Report deferred quiescent states.  The deferral समय can
 * be quite लघु, क्रम example, in the हाल of the call from
 * rcu_पढ़ो_unlock_special().
 */
अटल व्योम
rcu_preempt_deferred_qs_irqrestore(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ flags)
अणु
	bool empty_exp;
	bool empty_norm;
	bool empty_exp_now;
	काष्ठा list_head *np;
	bool drop_boost_mutex = false;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;
	जोड़ rcu_special special;

	/*
	 * If RCU core is रुकोing क्रम this CPU to निकास its critical section,
	 * report the fact that it has निकासed.  Because irqs are disabled,
	 * t->rcu_पढ़ो_unlock_special cannot change.
	 */
	special = t->rcu_पढ़ो_unlock_special;
	rdp = this_cpu_ptr(&rcu_data);
	अगर (!special.s && !rdp->exp_deferred_qs) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण
	t->rcu_पढ़ो_unlock_special.s = 0;
	अगर (special.b.need_qs) अणु
		अगर (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD)) अणु
			rcu_report_qs_rdp(rdp);
			udelay(rcu_unlock_delay);
		पूर्ण अन्यथा अणु
			rcu_qs();
		पूर्ण
	पूर्ण

	/*
	 * Respond to a request by an expedited grace period क्रम a
	 * quiescent state from this CPU.  Note that requests from
	 * tasks are handled when removing the task from the
	 * blocked-tasks list below.
	 */
	अगर (rdp->exp_deferred_qs)
		rcu_report_exp_rdp(rdp);

	/* Clean up अगर blocked during RCU पढ़ो-side critical section. */
	अगर (special.b.blocked) अणु

		/*
		 * Remove this task from the list it blocked on.  The task
		 * now reमुख्यs queued on the rcu_node corresponding to the
		 * CPU it first blocked on, so there is no दीर्घer any need
		 * to loop.  Retain a WARN_ON_ONCE() out of sheer paranoia.
		 */
		rnp = t->rcu_blocked_node;
		raw_spin_lock_rcu_node(rnp); /* irqs alपढ़ोy disabled. */
		WARN_ON_ONCE(rnp != t->rcu_blocked_node);
		WARN_ON_ONCE(!rcu_is_leaf_node(rnp));
		empty_norm = !rcu_preempt_blocked_पढ़ोers_cgp(rnp);
		WARN_ON_ONCE(rnp->completedqs == rnp->gp_seq &&
			     (!empty_norm || rnp->qsmask));
		empty_exp = sync_rcu_exp_करोne(rnp);
		smp_mb(); /* ensure expedited fastpath sees end of RCU c-s. */
		np = rcu_next_node_entry(t, rnp);
		list_del_init(&t->rcu_node_entry);
		t->rcu_blocked_node = शून्य;
		trace_rcu_unlock_preempted_task(TPS("rcu_preempt"),
						rnp->gp_seq, t->pid);
		अगर (&t->rcu_node_entry == rnp->gp_tasks)
			WRITE_ONCE(rnp->gp_tasks, np);
		अगर (&t->rcu_node_entry == rnp->exp_tasks)
			WRITE_ONCE(rnp->exp_tasks, np);
		अगर (IS_ENABLED(CONFIG_RCU_BOOST)) अणु
			/* Snapshot ->boost_mtx ownership w/rnp->lock held. */
			drop_boost_mutex = rt_mutex_owner(&rnp->boost_mtx) == t;
			अगर (&t->rcu_node_entry == rnp->boost_tasks)
				WRITE_ONCE(rnp->boost_tasks, np);
		पूर्ण

		/*
		 * If this was the last task on the current list, and अगर
		 * we aren't रुकोing on any CPUs, report the quiescent state.
		 * Note that rcu_report_unblock_qs_rnp() releases rnp->lock,
		 * so we must take a snapshot of the expedited state.
		 */
		empty_exp_now = sync_rcu_exp_करोne(rnp);
		अगर (!empty_norm && !rcu_preempt_blocked_पढ़ोers_cgp(rnp)) अणु
			trace_rcu_quiescent_state_report(TPS("preempt_rcu"),
							 rnp->gp_seq,
							 0, rnp->qsmask,
							 rnp->level,
							 rnp->grplo,
							 rnp->grphi,
							 !!rnp->gp_tasks);
			rcu_report_unblock_qs_rnp(rnp, flags);
		पूर्ण अन्यथा अणु
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		पूर्ण

		/* Unboost अगर we were boosted. */
		अगर (IS_ENABLED(CONFIG_RCU_BOOST) && drop_boost_mutex)
			rt_mutex_futex_unlock(&rnp->boost_mtx);

		/*
		 * If this was the last task on the expedited lists,
		 * then we need to report up the rcu_node hierarchy.
		 */
		अगर (!empty_exp && empty_exp_now)
			rcu_report_exp_rnp(rnp, true);
	पूर्ण अन्यथा अणु
		local_irq_restore(flags);
	पूर्ण
पूर्ण

/*
 * Is a deferred quiescent-state pending, and are we also not in
 * an RCU पढ़ो-side critical section?  It is the caller's responsibility
 * to ensure it is otherwise safe to report any deferred quiescent
 * states.  The reason क्रम this is that it is safe to report a
 * quiescent state during context चयन even though preemption
 * is disabled.  This function cannot be expected to understand these
 * nuances, so the caller must handle them.
 */
अटल bool rcu_preempt_need_deferred_qs(काष्ठा task_काष्ठा *t)
अणु
	वापस (__this_cpu_पढ़ो(rcu_data.exp_deferred_qs) ||
		READ_ONCE(t->rcu_पढ़ो_unlock_special.s)) &&
	       rcu_preempt_depth() == 0;
पूर्ण

/*
 * Report a deferred quiescent state अगर needed and safe to करो so.
 * As with rcu_preempt_need_deferred_qs(), "safe" involves only
 * not being in an RCU पढ़ो-side critical section.  The caller must
 * evaluate safety in terms of पूर्णांकerrupt, softirq, and preemption
 * disabling.
 */
अटल व्योम rcu_preempt_deferred_qs(काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!rcu_preempt_need_deferred_qs(t))
		वापस;
	local_irq_save(flags);
	rcu_preempt_deferred_qs_irqrestore(t, flags);
पूर्ण

/*
 * Minimal handler to give the scheduler a chance to re-evaluate.
 */
अटल व्योम rcu_preempt_deferred_qs_handler(काष्ठा irq_work *iwp)
अणु
	काष्ठा rcu_data *rdp;

	rdp = container_of(iwp, काष्ठा rcu_data, defer_qs_iw);
	rdp->defer_qs_iw_pending = false;
पूर्ण

/*
 * Handle special हालs during rcu_पढ़ो_unlock(), such as needing to
 * notअगरy RCU core processing or task having blocked during the RCU
 * पढ़ो-side critical section.
 */
अटल व्योम rcu_पढ़ो_unlock_special(काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ flags;
	bool irqs_were_disabled;
	bool preempt_bh_were_disabled =
			!!(preempt_count() & (PREEMPT_MASK | SOFTIRQ_MASK));

	/* NMI handlers cannot block and cannot safely manipulate state. */
	अगर (in_nmi())
		वापस;

	local_irq_save(flags);
	irqs_were_disabled = irqs_disabled_flags(flags);
	अगर (preempt_bh_were_disabled || irqs_were_disabled) अणु
		bool expboost; // Expedited GP in flight or possible boosting.
		काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
		काष्ठा rcu_node *rnp = rdp->mynode;

		expboost = (t->rcu_blocked_node && READ_ONCE(t->rcu_blocked_node->exp_tasks)) ||
			   (rdp->grpmask & READ_ONCE(rnp->expmask)) ||
			   IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD) ||
			   (IS_ENABLED(CONFIG_RCU_BOOST) && irqs_were_disabled &&
			    t->rcu_blocked_node);
		// Need to defer quiescent state until everything is enabled.
		अगर (use_softirq && (in_irq() || (expboost && !irqs_were_disabled))) अणु
			// Using softirq, safe to awaken, and either the
			// wakeup is मुक्त or there is either an expedited
			// GP in flight or a potential need to deboost.
			उठाओ_softirq_irqoff(RCU_SOFTIRQ);
		पूर्ण अन्यथा अणु
			// Enabling BH or preempt करोes reschedule, so...
			// Also अगर no expediting and no possible deboosting,
			// slow is OK.  Plus nohz_full CPUs eventually get
			// tick enabled.
			set_tsk_need_resched(current);
			set_preempt_need_resched();
			अगर (IS_ENABLED(CONFIG_IRQ_WORK) && irqs_were_disabled &&
			    expboost && !rdp->defer_qs_iw_pending && cpu_online(rdp->cpu)) अणु
				// Get scheduler to re-evaluate and call hooks.
				// If !IRQ_WORK, FQS scan will eventually IPI.
				init_irq_work(&rdp->defer_qs_iw, rcu_preempt_deferred_qs_handler);
				rdp->defer_qs_iw_pending = true;
				irq_work_queue_on(&rdp->defer_qs_iw, rdp->cpu);
			पूर्ण
		पूर्ण
		local_irq_restore(flags);
		वापस;
	पूर्ण
	rcu_preempt_deferred_qs_irqrestore(t, flags);
पूर्ण

/*
 * Check that the list of blocked tasks क्रम the newly completed grace
 * period is in fact empty.  It is a serious bug to complete a grace
 * period that still has RCU पढ़ोers blocked!  This function must be
 * invoked -beक्रमe- updating this rnp's ->gp_seq.
 *
 * Also, अगर there are blocked tasks on the list, they स्वतःmatically
 * block the newly created grace period, so set up ->gp_tasks accordingly.
 */
अटल व्योम rcu_preempt_check_blocked_tasks(काष्ठा rcu_node *rnp)
अणु
	काष्ठा task_काष्ठा *t;

	RCU_LOCKDEP_WARN(preemptible(), "rcu_preempt_check_blocked_tasks() invoked with preemption enabled!!!\n");
	raw_lockdep_निश्चित_held_rcu_node(rnp);
	अगर (WARN_ON_ONCE(rcu_preempt_blocked_पढ़ोers_cgp(rnp)))
		dump_blkd_tasks(rnp, 10);
	अगर (rcu_preempt_has_tasks(rnp) &&
	    (rnp->qsmaskinit || rnp->रुको_blkd_tasks)) अणु
		WRITE_ONCE(rnp->gp_tasks, rnp->blkd_tasks.next);
		t = container_of(rnp->gp_tasks, काष्ठा task_काष्ठा,
				 rcu_node_entry);
		trace_rcu_unlock_preempted_task(TPS("rcu_preempt-GPS"),
						rnp->gp_seq, t->pid);
	पूर्ण
	WARN_ON_ONCE(rnp->qsmask);
पूर्ण

/*
 * Check क्रम a quiescent state from the current CPU, including voluntary
 * context चयनes क्रम Tasks RCU.  When a task blocks, the task is
 * recorded in the corresponding CPU's rcu_node काष्ठाure, which is checked
 * अन्यथाwhere, hence this function need only check क्रम quiescent states
 * related to the current CPU, not to those related to tasks.
 */
अटल व्योम rcu_flavor_sched_घड़ी_irq(पूर्णांक user)
अणु
	काष्ठा task_काष्ठा *t = current;

	lockdep_निश्चित_irqs_disabled();
	अगर (user || rcu_is_cpu_rrupt_from_idle()) अणु
		rcu_note_voluntary_context_चयन(current);
	पूर्ण
	अगर (rcu_preempt_depth() > 0 ||
	    (preempt_count() & (PREEMPT_MASK | SOFTIRQ_MASK))) अणु
		/* No QS, क्रमce context चयन अगर deferred. */
		अगर (rcu_preempt_need_deferred_qs(t)) अणु
			set_tsk_need_resched(t);
			set_preempt_need_resched();
		पूर्ण
	पूर्ण अन्यथा अगर (rcu_preempt_need_deferred_qs(t)) अणु
		rcu_preempt_deferred_qs(t); /* Report deferred QS. */
		वापस;
	पूर्ण अन्यथा अगर (!WARN_ON_ONCE(rcu_preempt_depth())) अणु
		rcu_qs(); /* Report immediate QS. */
		वापस;
	पूर्ण

	/* If GP is oldish, ask क्रम help from rcu_पढ़ो_unlock_special(). */
	अगर (rcu_preempt_depth() > 0 &&
	    __this_cpu_पढ़ो(rcu_data.core_needs_qs) &&
	    __this_cpu_पढ़ो(rcu_data.cpu_no_qs.b.norm) &&
	    !t->rcu_पढ़ो_unlock_special.b.need_qs &&
	    समय_after(jअगरfies, rcu_state.gp_start + HZ))
		t->rcu_पढ़ो_unlock_special.b.need_qs = true;
पूर्ण

/*
 * Check क्रम a task निकासing जबतक in a preemptible-RCU पढ़ो-side
 * critical section, clean up अगर so.  No need to issue warnings, as
 * debug_check_no_locks_held() alपढ़ोy करोes this अगर lockdep is enabled.
 * Besides, अगर this function करोes anything other than just immediately
 * वापस, there was a bug of some sort.  Spewing warnings from this
 * function is like as not to simply obscure important prior warnings.
 */
व्योम निकास_rcu(व्योम)
अणु
	काष्ठा task_काष्ठा *t = current;

	अगर (unlikely(!list_empty(&current->rcu_node_entry))) अणु
		rcu_preempt_depth_set(1);
		barrier();
		WRITE_ONCE(t->rcu_पढ़ो_unlock_special.b.blocked, true);
	पूर्ण अन्यथा अगर (unlikely(rcu_preempt_depth())) अणु
		rcu_preempt_depth_set(1);
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
	__rcu_पढ़ो_unlock();
	rcu_preempt_deferred_qs(current);
पूर्ण

/*
 * Dump the blocked-tasks state, but limit the list dump to the
 * specअगरied number of elements.
 */
अटल व्योम
dump_blkd_tasks(काष्ठा rcu_node *rnp, पूर्णांक ncheck)
अणु
	पूर्णांक cpu;
	पूर्णांक i;
	काष्ठा list_head *lhp;
	bool onl;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp1;

	raw_lockdep_निश्चित_held_rcu_node(rnp);
	pr_info("%s: grp: %d-%d level: %d ->gp_seq %ld ->completedqs %ld\n",
		__func__, rnp->grplo, rnp->grphi, rnp->level,
		(दीर्घ)READ_ONCE(rnp->gp_seq), (दीर्घ)rnp->completedqs);
	क्रम (rnp1 = rnp; rnp1; rnp1 = rnp1->parent)
		pr_info("%s: %d:%d ->qsmask %#lx ->qsmaskinit %#lx ->qsmaskinitnext %#lx\n",
			__func__, rnp1->grplo, rnp1->grphi, rnp1->qsmask, rnp1->qsmaskinit, rnp1->qsmaskinitnext);
	pr_info("%s: ->gp_tasks %p ->boost_tasks %p ->exp_tasks %p\n",
		__func__, READ_ONCE(rnp->gp_tasks), data_race(rnp->boost_tasks),
		READ_ONCE(rnp->exp_tasks));
	pr_info("%s: ->blkd_tasks", __func__);
	i = 0;
	list_क्रम_each(lhp, &rnp->blkd_tasks) अणु
		pr_cont(" %p", lhp);
		अगर (++i >= ncheck)
			अवरोध;
	पूर्ण
	pr_cont("\n");
	क्रम (cpu = rnp->grplo; cpu <= rnp->grphi; cpu++) अणु
		rdp = per_cpu_ptr(&rcu_data, cpu);
		onl = !!(rdp->grpmask & rcu_rnp_online_cpus(rnp));
		pr_info("\t%d: %c online: %ld(%d) offline: %ld(%d)\n",
			cpu, ".o"[onl],
			(दीर्घ)rdp->rcu_onl_gp_seq, rdp->rcu_onl_gp_flags,
			(दीर्घ)rdp->rcu_ofl_gp_seq, rdp->rcu_ofl_gp_flags);
	पूर्ण
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_PREEMPT_RCU */

/*
 * If strict grace periods are enabled, and अगर the calling
 * __rcu_पढ़ो_unlock() marks the beginning of a quiescent state, immediately
 * report that quiescent state and, अगर requested, spin क्रम a bit.
 */
व्योम rcu_पढ़ो_unlock_strict(व्योम)
अणु
	काष्ठा rcu_data *rdp;

	अगर (!IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD) ||
	   irqs_disabled() || preempt_count() || !rcu_state.gp_kthपढ़ो)
		वापस;
	rdp = this_cpu_ptr(&rcu_data);
	rcu_report_qs_rdp(rdp);
	udelay(rcu_unlock_delay);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_पढ़ो_unlock_strict);

/*
 * Tell them what RCU they are running.
 */
अटल व्योम __init rcu_bootup_announce(व्योम)
अणु
	pr_info("Hierarchical RCU implementation.\n");
	rcu_bootup_announce_oddness();
पूर्ण

/*
 * Note a quiescent state क्रम PREEMPTION=n.  Because we करो not need to know
 * how many quiescent states passed, just अगर there was at least one since
 * the start of the grace period, this just sets a flag.  The caller must
 * have disabled preemption.
 */
अटल व्योम rcu_qs(व्योम)
अणु
	RCU_LOCKDEP_WARN(preemptible(), "rcu_qs() invoked with preemption enabled!!!");
	अगर (!__this_cpu_पढ़ो(rcu_data.cpu_no_qs.s))
		वापस;
	trace_rcu_grace_period(TPS("rcu_sched"),
			       __this_cpu_पढ़ो(rcu_data.gp_seq), TPS("cpuqs"));
	__this_cpu_ग_लिखो(rcu_data.cpu_no_qs.b.norm, false);
	अगर (!__this_cpu_पढ़ो(rcu_data.cpu_no_qs.b.exp))
		वापस;
	__this_cpu_ग_लिखो(rcu_data.cpu_no_qs.b.exp, false);
	rcu_report_exp_rdp(this_cpu_ptr(&rcu_data));
पूर्ण

/*
 * Register an urgently needed quiescent state.  If there is an
 * emergency, invoke rcu_momentary_dyntick_idle() to करो a heavy-weight
 * dyntick-idle quiescent state visible to other CPUs, which will in
 * some हालs serve क्रम expedited as well as normal grace periods.
 * Either way, रेजिस्टर a lightweight quiescent state.
 */
व्योम rcu_all_qs(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!raw_cpu_पढ़ो(rcu_data.rcu_urgent_qs))
		वापस;
	preempt_disable();
	/* Load rcu_urgent_qs beक्रमe other flags. */
	अगर (!smp_load_acquire(this_cpu_ptr(&rcu_data.rcu_urgent_qs))) अणु
		preempt_enable();
		वापस;
	पूर्ण
	this_cpu_ग_लिखो(rcu_data.rcu_urgent_qs, false);
	अगर (unlikely(raw_cpu_पढ़ो(rcu_data.rcu_need_heavy_qs))) अणु
		local_irq_save(flags);
		rcu_momentary_dyntick_idle();
		local_irq_restore(flags);
	पूर्ण
	rcu_qs();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(rcu_all_qs);

/*
 * Note a PREEMPTION=n context चयन. The caller must have disabled पूर्णांकerrupts.
 */
व्योम rcu_note_context_चयन(bool preempt)
अणु
	trace_rcu_utilization(TPS("Start context switch"));
	rcu_qs();
	/* Load rcu_urgent_qs beक्रमe other flags. */
	अगर (!smp_load_acquire(this_cpu_ptr(&rcu_data.rcu_urgent_qs)))
		जाओ out;
	this_cpu_ग_लिखो(rcu_data.rcu_urgent_qs, false);
	अगर (unlikely(raw_cpu_पढ़ो(rcu_data.rcu_need_heavy_qs)))
		rcu_momentary_dyntick_idle();
	rcu_tasks_qs(current, preempt);
out:
	trace_rcu_utilization(TPS("End context switch"));
पूर्ण
EXPORT_SYMBOL_GPL(rcu_note_context_चयन);

/*
 * Because preemptible RCU करोes not exist, there are never any preempted
 * RCU पढ़ोers.
 */
अटल पूर्णांक rcu_preempt_blocked_पढ़ोers_cgp(काष्ठा rcu_node *rnp)
अणु
	वापस 0;
पूर्ण

/*
 * Because there is no preemptible RCU, there can be no पढ़ोers blocked.
 */
अटल bool rcu_preempt_has_tasks(काष्ठा rcu_node *rnp)
अणु
	वापस false;
पूर्ण

/*
 * Because there is no preemptible RCU, there can be no deferred quiescent
 * states.
 */
अटल bool rcu_preempt_need_deferred_qs(काष्ठा task_काष्ठा *t)
अणु
	वापस false;
पूर्ण
अटल व्योम rcu_preempt_deferred_qs(काष्ठा task_काष्ठा *t) अणु पूर्ण

/*
 * Because there is no preemptible RCU, there can be no पढ़ोers blocked,
 * so there is no need to check क्रम blocked tasks.  So check only क्रम
 * bogus qsmask values.
 */
अटल व्योम rcu_preempt_check_blocked_tasks(काष्ठा rcu_node *rnp)
अणु
	WARN_ON_ONCE(rnp->qsmask);
पूर्ण

/*
 * Check to see अगर this CPU is in a non-context-चयन quiescent state,
 * namely user mode and idle loop.
 */
अटल व्योम rcu_flavor_sched_घड़ी_irq(पूर्णांक user)
अणु
	अगर (user || rcu_is_cpu_rrupt_from_idle()) अणु

		/*
		 * Get here अगर this CPU took its पूर्णांकerrupt from user
		 * mode or from the idle loop, and अगर this is not a
		 * nested पूर्णांकerrupt.  In this हाल, the CPU is in
		 * a quiescent state, so note it.
		 *
		 * No memory barrier is required here because rcu_qs()
		 * references only CPU-local variables that other CPUs
		 * neither access nor modअगरy, at least not जबतक the
		 * corresponding CPU is online.
		 */

		rcu_qs();
	पूर्ण
पूर्ण

/*
 * Because preemptible RCU करोes not exist, tasks cannot possibly निकास
 * जबतक in preemptible RCU पढ़ो-side critical sections.
 */
व्योम निकास_rcu(व्योम)
अणु
पूर्ण

/*
 * Dump the guaranteed-empty blocked-tasks state.  Trust but verअगरy.
 */
अटल व्योम
dump_blkd_tasks(काष्ठा rcu_node *rnp, पूर्णांक ncheck)
अणु
	WARN_ON_ONCE(!list_empty(&rnp->blkd_tasks));
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PREEMPT_RCU */

/*
 * If boosting, set rcuc kthपढ़ोs to realसमय priority.
 */
अटल व्योम rcu_cpu_kthपढ़ो_setup(अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_RCU_BOOST
	काष्ठा sched_param sp;

	sp.sched_priority = kthपढ़ो_prio;
	sched_setscheduler_nocheck(current, SCHED_FIFO, &sp);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_RCU_BOOST */
पूर्ण

#अगर_घोषित CONFIG_RCU_BOOST

/*
 * Carry out RCU priority boosting on the task indicated by ->exp_tasks
 * or ->boost_tasks, advancing the poपूर्णांकer to the next task in the
 * ->blkd_tasks list.
 *
 * Note that irqs must be enabled: boosting the task can block.
 * Returns 1 अगर there are more tasks needing to be boosted.
 */
अटल पूर्णांक rcu_boost(काष्ठा rcu_node *rnp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा task_काष्ठा *t;
	काष्ठा list_head *tb;

	अगर (READ_ONCE(rnp->exp_tasks) == शून्य &&
	    READ_ONCE(rnp->boost_tasks) == शून्य)
		वापस 0;  /* Nothing left to boost. */

	raw_spin_lock_irqsave_rcu_node(rnp, flags);

	/*
	 * Recheck under the lock: all tasks in need of boosting
	 * might निकास their RCU पढ़ो-side critical sections on their own.
	 */
	अगर (rnp->exp_tasks == शून्य && rnp->boost_tasks == शून्य) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस 0;
	पूर्ण

	/*
	 * Preferentially boost tasks blocking expedited grace periods.
	 * This cannot starve the normal grace periods because a second
	 * expedited grace period must boost all blocked tasks, including
	 * those blocking the pre-existing normal grace period.
	 */
	अगर (rnp->exp_tasks != शून्य)
		tb = rnp->exp_tasks;
	अन्यथा
		tb = rnp->boost_tasks;

	/*
	 * We boost task t by manufacturing an rt_mutex that appears to
	 * be held by task t.  We leave a poपूर्णांकer to that rt_mutex where
	 * task t can find it, and task t will release the mutex when it
	 * निकासs its outermost RCU पढ़ो-side critical section.  Then
	 * simply acquiring this artअगरicial rt_mutex will boost task
	 * t's priority.  (Thanks to tglx क्रम suggesting this approach!)
	 *
	 * Note that task t must acquire rnp->lock to हटाओ itself from
	 * the ->blkd_tasks list, which it will करो from निकास() अगर from
	 * nowhere अन्यथा.  We thereक्रमe are guaranteed that task t will
	 * stay around at least until we drop rnp->lock.  Note that
	 * rnp->lock also resolves races between our priority boosting
	 * and task t's निकासing its outermost RCU पढ़ो-side critical
	 * section.
	 */
	t = container_of(tb, काष्ठा task_काष्ठा, rcu_node_entry);
	rt_mutex_init_proxy_locked(&rnp->boost_mtx, t);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	/* Lock only क्रम side effect: boosts task t's priority. */
	rt_mutex_lock(&rnp->boost_mtx);
	rt_mutex_unlock(&rnp->boost_mtx);  /* Then keep lockdep happy. */

	वापस READ_ONCE(rnp->exp_tasks) != शून्य ||
	       READ_ONCE(rnp->boost_tasks) != शून्य;
पूर्ण

/*
 * Priority-boosting kthपढ़ो, one per leaf rcu_node.
 */
अटल पूर्णांक rcu_boost_kthपढ़ो(व्योम *arg)
अणु
	काष्ठा rcu_node *rnp = (काष्ठा rcu_node *)arg;
	पूर्णांक spincnt = 0;
	पूर्णांक more2boost;

	trace_rcu_utilization(TPS("Start boost kthread@init"));
	क्रम (;;) अणु
		WRITE_ONCE(rnp->boost_kthपढ़ो_status, RCU_KTHREAD_WAITING);
		trace_rcu_utilization(TPS("End boost kthread@rcu_wait"));
		rcu_रुको(READ_ONCE(rnp->boost_tasks) ||
			 READ_ONCE(rnp->exp_tasks));
		trace_rcu_utilization(TPS("Start boost kthread@rcu_wait"));
		WRITE_ONCE(rnp->boost_kthपढ़ो_status, RCU_KTHREAD_RUNNING);
		more2boost = rcu_boost(rnp);
		अगर (more2boost)
			spincnt++;
		अन्यथा
			spincnt = 0;
		अगर (spincnt > 10) अणु
			WRITE_ONCE(rnp->boost_kthपढ़ो_status, RCU_KTHREAD_YIELDING);
			trace_rcu_utilization(TPS("End boost kthread@rcu_yield"));
			schedule_समयout_idle(2);
			trace_rcu_utilization(TPS("Start boost kthread@rcu_yield"));
			spincnt = 0;
		पूर्ण
	पूर्ण
	/* NOTREACHED */
	trace_rcu_utilization(TPS("End boost kthread@notreached"));
	वापस 0;
पूर्ण

/*
 * Check to see अगर it is समय to start boosting RCU पढ़ोers that are
 * blocking the current grace period, and, अगर so, tell the per-rcu_node
 * kthपढ़ो to start boosting them.  If there is an expedited grace
 * period in progress, it is always समय to boost.
 *
 * The caller must hold rnp->lock, which this function releases.
 * The ->boost_kthपढ़ो_task is immortal, so we करोn't need to worry
 * about it going away.
 */
अटल व्योम rcu_initiate_boost(काष्ठा rcu_node *rnp, अचिन्हित दीर्घ flags)
	__releases(rnp->lock)
अणु
	raw_lockdep_निश्चित_held_rcu_node(rnp);
	अगर (!rcu_preempt_blocked_पढ़ोers_cgp(rnp) && rnp->exp_tasks == शून्य) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;
	पूर्ण
	अगर (rnp->exp_tasks != शून्य ||
	    (rnp->gp_tasks != शून्य &&
	     rnp->boost_tasks == शून्य &&
	     rnp->qsmask == 0 &&
	     (!समय_after(rnp->boost_समय, jअगरfies) || rcu_state.cbovld))) अणु
		अगर (rnp->exp_tasks == शून्य)
			WRITE_ONCE(rnp->boost_tasks, rnp->gp_tasks);
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		rcu_wake_cond(rnp->boost_kthपढ़ो_task,
			      READ_ONCE(rnp->boost_kthपढ़ो_status));
	पूर्ण अन्यथा अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	पूर्ण
पूर्ण

/*
 * Is the current CPU running the RCU-callbacks kthपढ़ो?
 * Caller must have preemption disabled.
 */
अटल bool rcu_is_callbacks_kthपढ़ो(व्योम)
अणु
	वापस __this_cpu_पढ़ो(rcu_data.rcu_cpu_kthपढ़ो_task) == current;
पूर्ण

#घोषणा RCU_BOOST_DELAY_JIFFIES DIV_ROUND_UP(CONFIG_RCU_BOOST_DELAY * HZ, 1000)

/*
 * Do priority-boost accounting क्रम the start of a new grace period.
 */
अटल व्योम rcu_preempt_boost_start_gp(काष्ठा rcu_node *rnp)
अणु
	rnp->boost_समय = jअगरfies + RCU_BOOST_DELAY_JIFFIES;
पूर्ण

/*
 * Create an RCU-boost kthपढ़ो क्रम the specअगरied node अगर one करोes not
 * alपढ़ोy exist.  We only create this kthपढ़ो क्रम preemptible RCU.
 * Returns zero अगर all is well, a negated त्रुटि_सं otherwise.
 */
अटल व्योम rcu_spawn_one_boost_kthपढ़ो(काष्ठा rcu_node *rnp)
अणु
	पूर्णांक rnp_index = rnp - rcu_get_root();
	अचिन्हित दीर्घ flags;
	काष्ठा sched_param sp;
	काष्ठा task_काष्ठा *t;

	अगर (!IS_ENABLED(CONFIG_PREEMPT_RCU))
		वापस;

	अगर (!rcu_scheduler_fully_active || rcu_rnp_online_cpus(rnp) == 0)
		वापस;

	rcu_state.boost = 1;

	अगर (rnp->boost_kthपढ़ो_task != शून्य)
		वापस;

	t = kthपढ़ो_create(rcu_boost_kthपढ़ो, (व्योम *)rnp,
			   "rcub/%d", rnp_index);
	अगर (WARN_ON_ONCE(IS_ERR(t)))
		वापस;

	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	rnp->boost_kthपढ़ो_task = t;
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	sp.sched_priority = kthपढ़ो_prio;
	sched_setscheduler_nocheck(t, SCHED_FIFO, &sp);
	wake_up_process(t); /* get to TASK_INTERRUPTIBLE quickly. */
पूर्ण

/*
 * Set the per-rcu_node kthपढ़ो's affinity to cover all CPUs that are
 * served by the rcu_node in question.  The CPU hotplug lock is still
 * held, so the value of rnp->qsmaskinit will be stable.
 *
 * We करोn't include outgoingcpu in the affinity set, use -1 अगर there is
 * no outgoing CPU.  If there are no CPUs left in the affinity set,
 * this function allows the kthपढ़ो to execute on any CPU.
 */
अटल व्योम rcu_boost_kthपढ़ो_setaffinity(काष्ठा rcu_node *rnp, पूर्णांक outgoingcpu)
अणु
	काष्ठा task_काष्ठा *t = rnp->boost_kthपढ़ो_task;
	अचिन्हित दीर्घ mask = rcu_rnp_online_cpus(rnp);
	cpumask_var_t cm;
	पूर्णांक cpu;

	अगर (!t)
		वापस;
	अगर (!zalloc_cpumask_var(&cm, GFP_KERNEL))
		वापस;
	क्रम_each_leaf_node_possible_cpu(rnp, cpu)
		अगर ((mask & leaf_node_cpu_bit(rnp, cpu)) &&
		    cpu != outgoingcpu)
			cpumask_set_cpu(cpu, cm);
	अगर (cpumask_weight(cm) == 0)
		cpumask_setall(cm);
	set_cpus_allowed_ptr(t, cm);
	मुक्त_cpumask_var(cm);
पूर्ण

/*
 * Spawn boost kthपढ़ोs -- called as soon as the scheduler is running.
 */
अटल व्योम __init rcu_spawn_boost_kthपढ़ोs(व्योम)
अणु
	काष्ठा rcu_node *rnp;

	rcu_क्रम_each_leaf_node(rnp)
		rcu_spawn_one_boost_kthपढ़ो(rnp);
पूर्ण

अटल व्योम rcu_prepare_kthपढ़ोs(पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	काष्ठा rcu_node *rnp = rdp->mynode;

	/* Fire up the incoming CPU's kthपढ़ो and leaf rcu_node kthपढ़ो. */
	अगर (rcu_scheduler_fully_active)
		rcu_spawn_one_boost_kthपढ़ो(rnp);
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_RCU_BOOST */

अटल व्योम rcu_initiate_boost(काष्ठा rcu_node *rnp, अचिन्हित दीर्घ flags)
	__releases(rnp->lock)
अणु
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
पूर्ण

अटल bool rcu_is_callbacks_kthपढ़ो(व्योम)
अणु
	वापस false;
पूर्ण

अटल व्योम rcu_preempt_boost_start_gp(काष्ठा rcu_node *rnp)
अणु
पूर्ण

अटल व्योम rcu_boost_kthपढ़ो_setaffinity(काष्ठा rcu_node *rnp, पूर्णांक outgoingcpu)
अणु
पूर्ण

अटल व्योम __init rcu_spawn_boost_kthपढ़ोs(व्योम)
अणु
पूर्ण

अटल व्योम rcu_prepare_kthपढ़ोs(पूर्णांक cpu)
अणु
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_BOOST */

#अगर !defined(CONFIG_RCU_FAST_NO_HZ)

/*
 * Check to see अगर any future non-offloaded RCU-related work will need
 * to be करोne by the current CPU, even अगर none need be करोne immediately,
 * वापसing 1 अगर so.  This function is part of the RCU implementation;
 * it is -not- an exported member of the RCU API.
 *
 * Because we not have RCU_FAST_NO_HZ, just check whether or not this
 * CPU has RCU callbacks queued.
 */
पूर्णांक rcu_needs_cpu(u64 basemono, u64 *nextevt)
अणु
	*nextevt = KTIME_MAX;
	वापस !rcu_segcblist_empty(&this_cpu_ptr(&rcu_data)->cblist) &&
		!rcu_rdp_is_offloaded(this_cpu_ptr(&rcu_data));
पूर्ण

/*
 * Because we करो not have RCU_FAST_NO_HZ, करोn't bother cleaning up
 * after it.
 */
अटल व्योम rcu_cleanup_after_idle(व्योम)
अणु
पूर्ण

/*
 * Do the idle-entry grace-period work, which, because CONFIG_RCU_FAST_NO_HZ=n,
 * is nothing.
 */
अटल व्योम rcu_prepare_क्रम_idle(व्योम)
अणु
पूर्ण

#अन्यथा /* #अगर !defined(CONFIG_RCU_FAST_NO_HZ) */

/*
 * This code is invoked when a CPU goes idle, at which poपूर्णांक we want
 * to have the CPU करो everything required क्रम RCU so that it can enter
 * the energy-efficient dyntick-idle mode.
 *
 * The following preprocessor symbol controls this:
 *
 * RCU_IDLE_GP_DELAY gives the number of jअगरfies that a CPU is permitted
 *	to sleep in dyntick-idle mode with RCU callbacks pending.  This
 *	is sized to be roughly one RCU grace period.  Those energy-efficiency
 *	benchmarkers who might otherwise be tempted to set this to a large
 *	number, be warned: Setting RCU_IDLE_GP_DELAY too high can hang your
 *	प्रणाली.  And अगर you are -that- concerned about energy efficiency,
 *	just घातer the प्रणाली करोwn and be करोne with it!
 *
 * The value below works well in practice.  If future workloads require
 * adjusपंचांगent, they can be converted पूर्णांकo kernel config parameters, though
 * making the state machine smarter might be a better option.
 */
#घोषणा RCU_IDLE_GP_DELAY 4		/* Roughly one grace period. */

अटल पूर्णांक rcu_idle_gp_delay = RCU_IDLE_GP_DELAY;
module_param(rcu_idle_gp_delay, पूर्णांक, 0644);

/*
 * Try to advance callbacks on the current CPU, but only अगर it has been
 * aजबतक since the last समय we did so.  Afterwards, अगर there are any
 * callbacks पढ़ोy क्रम immediate invocation, वापस true.
 */
अटल bool __maybe_unused rcu_try_advance_all_cbs(व्योम)
अणु
	bool cbs_पढ़ोy = false;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp;

	/* Exit early अगर we advanced recently. */
	अगर (jअगरfies == rdp->last_advance_all)
		वापस false;
	rdp->last_advance_all = jअगरfies;

	rnp = rdp->mynode;

	/*
	 * Don't bother checking unless a grace period has
	 * completed since we last checked and there are
	 * callbacks not yet पढ़ोy to invoke.
	 */
	अगर ((rcu_seq_completed_gp(rdp->gp_seq,
				  rcu_seq_current(&rnp->gp_seq)) ||
	     unlikely(READ_ONCE(rdp->gpwrap))) &&
	    rcu_segcblist_pend_cbs(&rdp->cblist))
		note_gp_changes(rdp);

	अगर (rcu_segcblist_पढ़ोy_cbs(&rdp->cblist))
		cbs_पढ़ोy = true;
	वापस cbs_पढ़ोy;
पूर्ण

/*
 * Allow the CPU to enter dyntick-idle mode unless it has callbacks पढ़ोy
 * to invoke.  If the CPU has callbacks, try to advance them.  Tell the
 * caller about what to set the समयout.
 *
 * The caller must have disabled पूर्णांकerrupts.
 */
पूर्णांक rcu_needs_cpu(u64 basemono, u64 *nextevt)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	अचिन्हित दीर्घ dj;

	lockdep_निश्चित_irqs_disabled();

	/* If no non-offloaded callbacks, RCU करोesn't need the CPU. */
	अगर (rcu_segcblist_empty(&rdp->cblist) ||
	    rcu_rdp_is_offloaded(rdp)) अणु
		*nextevt = KTIME_MAX;
		वापस 0;
	पूर्ण

	/* Attempt to advance callbacks. */
	अगर (rcu_try_advance_all_cbs()) अणु
		/* Some पढ़ोy to invoke, so initiate later invocation. */
		invoke_rcu_core();
		वापस 1;
	पूर्ण
	rdp->last_accelerate = jअगरfies;

	/* Request समयr and round. */
	dj = round_up(rcu_idle_gp_delay + jअगरfies, rcu_idle_gp_delay) - jअगरfies;

	*nextevt = basemono + dj * TICK_NSEC;
	वापस 0;
पूर्ण

/*
 * Prepare a CPU क्रम idle from an RCU perspective.  The first major task is to
 * sense whether nohz mode has been enabled or disabled via sysfs.  The second
 * major task is to accelerate (that is, assign grace-period numbers to) any
 * recently arrived callbacks.
 *
 * The caller must have disabled पूर्णांकerrupts.
 */
अटल व्योम rcu_prepare_क्रम_idle(व्योम)
अणु
	bool needwake;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp;
	पूर्णांक tne;

	lockdep_निश्चित_irqs_disabled();
	अगर (rcu_rdp_is_offloaded(rdp))
		वापस;

	/* Handle nohz enablement चयनes conservatively. */
	tne = READ_ONCE(tick_nohz_active);
	अगर (tne != rdp->tick_nohz_enabled_snap) अणु
		अगर (!rcu_segcblist_empty(&rdp->cblist))
			invoke_rcu_core(); /* क्रमce nohz to see update. */
		rdp->tick_nohz_enabled_snap = tne;
		वापस;
	पूर्ण
	अगर (!tne)
		वापस;

	/*
	 * If we have not yet accelerated this jअगरfy, accelerate all
	 * callbacks on this CPU.
	 */
	अगर (rdp->last_accelerate == jअगरfies)
		वापस;
	rdp->last_accelerate = jअगरfies;
	अगर (rcu_segcblist_pend_cbs(&rdp->cblist)) अणु
		rnp = rdp->mynode;
		raw_spin_lock_rcu_node(rnp); /* irqs alपढ़ोy disabled. */
		needwake = rcu_accelerate_cbs(rnp, rdp);
		raw_spin_unlock_rcu_node(rnp); /* irqs reमुख्य disabled. */
		अगर (needwake)
			rcu_gp_kthपढ़ो_wake();
	पूर्ण
पूर्ण

/*
 * Clean up क्रम निकास from idle.  Attempt to advance callbacks based on
 * any grace periods that elapsed जबतक the CPU was idle, and अगर any
 * callbacks are now पढ़ोy to invoke, initiate invocation.
 */
अटल व्योम rcu_cleanup_after_idle(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	lockdep_निश्चित_irqs_disabled();
	अगर (rcu_rdp_is_offloaded(rdp))
		वापस;
	अगर (rcu_try_advance_all_cbs())
		invoke_rcu_core();
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर !defined(CONFIG_RCU_FAST_NO_HZ) */

#अगर_घोषित CONFIG_RCU_NOCB_CPU

/*
 * Offload callback processing from the boot-समय-specअगरied set of CPUs
 * specअगरied by rcu_nocb_mask.  For the CPUs in the set, there are kthपढ़ोs
 * created that pull the callbacks from the corresponding CPU, रुको क्रम
 * a grace period to elapse, and invoke the callbacks.  These kthपढ़ोs
 * are organized पूर्णांकo GP kthपढ़ोs, which manage incoming callbacks, रुको क्रम
 * grace periods, and awaken CB kthपढ़ोs, and the CB kthपढ़ोs, which only
 * invoke callbacks.  Each GP kthपढ़ो invokes its own CBs.  The no-CBs CPUs
 * करो a wake_up() on their GP kthपढ़ो when they insert a callback पूर्णांकo any
 * empty list, unless the rcu_nocb_poll boot parameter has been specअगरied,
 * in which हाल each kthपढ़ो actively polls its CPU.  (Which isn't so great
 * क्रम energy efficiency, but which करोes reduce RCU's overhead on that CPU.)
 *
 * This is पूर्णांकended to be used in conjunction with Frederic Weisbecker's
 * adaptive-idle work, which would seriously reduce OS jitter on CPUs
 * running CPU-bound user-mode computations.
 *
 * Offloading of callbacks can also be used as an energy-efficiency
 * measure because CPUs with no RCU callbacks queued are more aggressive
 * about entering dyntick-idle mode.
 */


/*
 * Parse the boot-समय rcu_nocb_mask CPU list from the kernel parameters.
 * If the list is invalid, a warning is emitted and all CPUs are offloaded.
 */
अटल पूर्णांक __init rcu_nocb_setup(अक्षर *str)
अणु
	alloc_booपंचांगem_cpumask_var(&rcu_nocb_mask);
	अगर (!strहालcmp(str, "all"))		/* legacy: use "0-N" instead */
		cpumask_setall(rcu_nocb_mask);
	अन्यथा
		अगर (cpulist_parse(str, rcu_nocb_mask)) अणु
			pr_warn("rcu_nocbs= bad CPU range, all CPUs set\n");
			cpumask_setall(rcu_nocb_mask);
		पूर्ण
	वापस 1;
पूर्ण
__setup("rcu_nocbs=", rcu_nocb_setup);

अटल पूर्णांक __init parse_rcu_nocb_poll(अक्षर *arg)
अणु
	rcu_nocb_poll = true;
	वापस 0;
पूर्ण
early_param("rcu_nocb_poll", parse_rcu_nocb_poll);

/*
 * Don't bother bypassing ->cblist अगर the call_rcu() rate is low.
 * After all, the मुख्य poपूर्णांक of bypassing is to aव्योम lock contention
 * on ->nocb_lock, which only can happen at high call_rcu() rates.
 */
अटल पूर्णांक nocb_nobypass_lim_per_jअगरfy = 16 * 1000 / HZ;
module_param(nocb_nobypass_lim_per_jअगरfy, पूर्णांक, 0);

/*
 * Acquire the specअगरied rcu_data काष्ठाure's ->nocb_bypass_lock.  If the
 * lock isn't immediately available, increment ->nocb_lock_contended to
 * flag the contention.
 */
अटल व्योम rcu_nocb_bypass_lock(काष्ठा rcu_data *rdp)
	__acquires(&rdp->nocb_bypass_lock)
अणु
	lockdep_निश्चित_irqs_disabled();
	अगर (raw_spin_trylock(&rdp->nocb_bypass_lock))
		वापस;
	atomic_inc(&rdp->nocb_lock_contended);
	WARN_ON_ONCE(smp_processor_id() != rdp->cpu);
	smp_mb__after_atomic(); /* atomic_inc() beक्रमe lock. */
	raw_spin_lock(&rdp->nocb_bypass_lock);
	smp_mb__beक्रमe_atomic(); /* atomic_dec() after lock. */
	atomic_dec(&rdp->nocb_lock_contended);
पूर्ण

/*
 * Spinरुको until the specअगरied rcu_data काष्ठाure's ->nocb_lock is
 * not contended.  Please note that this is extremely special-purpose,
 * relying on the fact that at most two kthपढ़ोs and one CPU contend क्रम
 * this lock, and also that the two kthपढ़ोs are guaranteed to have frequent
 * grace-period-duration समय पूर्णांकervals between successive acquisitions
 * of the lock.  This allows us to use an extremely simple throttling
 * mechanism, and further to apply it only to the CPU करोing floods of
 * call_rcu() invocations.  Don't try this at home!
 */
अटल व्योम rcu_nocb_रुको_contended(काष्ठा rcu_data *rdp)
अणु
	WARN_ON_ONCE(smp_processor_id() != rdp->cpu);
	जबतक (WARN_ON_ONCE(atomic_पढ़ो(&rdp->nocb_lock_contended)))
		cpu_relax();
पूर्ण

/*
 * Conditionally acquire the specअगरied rcu_data काष्ठाure's
 * ->nocb_bypass_lock.
 */
अटल bool rcu_nocb_bypass_trylock(काष्ठा rcu_data *rdp)
अणु
	lockdep_निश्चित_irqs_disabled();
	वापस raw_spin_trylock(&rdp->nocb_bypass_lock);
पूर्ण

/*
 * Release the specअगरied rcu_data काष्ठाure's ->nocb_bypass_lock.
 */
अटल व्योम rcu_nocb_bypass_unlock(काष्ठा rcu_data *rdp)
	__releases(&rdp->nocb_bypass_lock)
अणु
	lockdep_निश्चित_irqs_disabled();
	raw_spin_unlock(&rdp->nocb_bypass_lock);
पूर्ण

/*
 * Acquire the specअगरied rcu_data काष्ठाure's ->nocb_lock, but only
 * अगर it corresponds to a no-CBs CPU.
 */
अटल व्योम rcu_nocb_lock(काष्ठा rcu_data *rdp)
अणु
	lockdep_निश्चित_irqs_disabled();
	अगर (!rcu_rdp_is_offloaded(rdp))
		वापस;
	raw_spin_lock(&rdp->nocb_lock);
पूर्ण

/*
 * Release the specअगरied rcu_data काष्ठाure's ->nocb_lock, but only
 * अगर it corresponds to a no-CBs CPU.
 */
अटल व्योम rcu_nocb_unlock(काष्ठा rcu_data *rdp)
अणु
	अगर (rcu_rdp_is_offloaded(rdp)) अणु
		lockdep_निश्चित_irqs_disabled();
		raw_spin_unlock(&rdp->nocb_lock);
	पूर्ण
पूर्ण

/*
 * Release the specअगरied rcu_data काष्ठाure's ->nocb_lock and restore
 * पूर्णांकerrupts, but only अगर it corresponds to a no-CBs CPU.
 */
अटल व्योम rcu_nocb_unlock_irqrestore(काष्ठा rcu_data *rdp,
				       अचिन्हित दीर्घ flags)
अणु
	अगर (rcu_rdp_is_offloaded(rdp)) अणु
		lockdep_निश्चित_irqs_disabled();
		raw_spin_unlock_irqrestore(&rdp->nocb_lock, flags);
	पूर्ण अन्यथा अणु
		local_irq_restore(flags);
	पूर्ण
पूर्ण

/* Lockdep check that ->cblist may be safely accessed. */
अटल व्योम rcu_lockdep_निश्चित_cblist_रक्षित(काष्ठा rcu_data *rdp)
अणु
	lockdep_निश्चित_irqs_disabled();
	अगर (rcu_rdp_is_offloaded(rdp))
		lockdep_निश्चित_held(&rdp->nocb_lock);
पूर्ण

/*
 * Wake up any no-CBs CPUs' kthपढ़ोs that were रुकोing on the just-ended
 * grace period.
 */
अटल व्योम rcu_nocb_gp_cleanup(काष्ठा sरुको_queue_head *sq)
अणु
	swake_up_all(sq);
पूर्ण

अटल काष्ठा sरुको_queue_head *rcu_nocb_gp_get(काष्ठा rcu_node *rnp)
अणु
	वापस &rnp->nocb_gp_wq[rcu_seq_ctr(rnp->gp_seq) & 0x1];
पूर्ण

अटल व्योम rcu_init_one_nocb(काष्ठा rcu_node *rnp)
अणु
	init_sरुको_queue_head(&rnp->nocb_gp_wq[0]);
	init_sरुको_queue_head(&rnp->nocb_gp_wq[1]);
पूर्ण

/* Is the specअगरied CPU a no-CBs CPU? */
bool rcu_is_nocb_cpu(पूर्णांक cpu)
अणु
	अगर (cpumask_available(rcu_nocb_mask))
		वापस cpumask_test_cpu(cpu, rcu_nocb_mask);
	वापस false;
पूर्ण

/*
 * Kick the GP kthपढ़ो क्रम this NOCB group.  Caller holds ->nocb_lock
 * and this function releases it.
 */
अटल bool wake_nocb_gp(काष्ठा rcu_data *rdp, bool क्रमce,
			 अचिन्हित दीर्घ flags)
	__releases(rdp->nocb_lock)
अणु
	bool needwake = false;
	काष्ठा rcu_data *rdp_gp = rdp->nocb_gp_rdp;

	lockdep_निश्चित_held(&rdp->nocb_lock);
	अगर (!READ_ONCE(rdp_gp->nocb_gp_kthपढ़ो)) अणु
		rcu_nocb_unlock_irqrestore(rdp, flags);
		trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
				    TPS("AlreadyAwake"));
		वापस false;
	पूर्ण

	अगर (READ_ONCE(rdp->nocb_defer_wakeup) > RCU_NOCB_WAKE_NOT) अणु
		WRITE_ONCE(rdp->nocb_defer_wakeup, RCU_NOCB_WAKE_NOT);
		del_समयr(&rdp->nocb_समयr);
	पूर्ण
	rcu_nocb_unlock_irqrestore(rdp, flags);
	raw_spin_lock_irqsave(&rdp_gp->nocb_gp_lock, flags);
	अगर (क्रमce || READ_ONCE(rdp_gp->nocb_gp_sleep)) अणु
		WRITE_ONCE(rdp_gp->nocb_gp_sleep, false);
		needwake = true;
		trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("DoWake"));
	पूर्ण
	raw_spin_unlock_irqrestore(&rdp_gp->nocb_gp_lock, flags);
	अगर (needwake)
		wake_up_process(rdp_gp->nocb_gp_kthपढ़ो);

	वापस needwake;
पूर्ण

/*
 * Arrange to wake the GP kthपढ़ो क्रम this NOCB group at some future
 * समय when it is safe to करो so.
 */
अटल व्योम wake_nocb_gp_defer(काष्ठा rcu_data *rdp, पूर्णांक waketype,
			       स्थिर अक्षर *reason)
अणु
	अगर (rdp->nocb_defer_wakeup == RCU_NOCB_WAKE_OFF)
		वापस;
	अगर (rdp->nocb_defer_wakeup == RCU_NOCB_WAKE_NOT)
		mod_समयr(&rdp->nocb_समयr, jअगरfies + 1);
	अगर (rdp->nocb_defer_wakeup < waketype)
		WRITE_ONCE(rdp->nocb_defer_wakeup, waketype);
	trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, reason);
पूर्ण

/*
 * Flush the ->nocb_bypass queue पूर्णांकo ->cblist, enqueuing rhp अगर non-शून्य.
 * However, अगर there is a callback to be enqueued and अगर ->nocb_bypass
 * proves to be initially empty, just वापस false because the no-CB GP
 * kthपढ़ो may need to be awakened in this हाल.
 *
 * Note that this function always वापसs true अगर rhp is शून्य.
 */
अटल bool rcu_nocb_करो_flush_bypass(काष्ठा rcu_data *rdp, काष्ठा rcu_head *rhp,
				     अचिन्हित दीर्घ j)
अणु
	काष्ठा rcu_cblist rcl;

	WARN_ON_ONCE(!rcu_rdp_is_offloaded(rdp));
	rcu_lockdep_निश्चित_cblist_रक्षित(rdp);
	lockdep_निश्चित_held(&rdp->nocb_bypass_lock);
	अगर (rhp && !rcu_cblist_n_cbs(&rdp->nocb_bypass)) अणु
		raw_spin_unlock(&rdp->nocb_bypass_lock);
		वापस false;
	पूर्ण
	/* Note: ->cblist.len alपढ़ोy accounts क्रम ->nocb_bypass contents. */
	अगर (rhp)
		rcu_segcblist_inc_len(&rdp->cblist); /* Must precede enqueue. */
	rcu_cblist_flush_enqueue(&rcl, &rdp->nocb_bypass, rhp);
	rcu_segcblist_insert_pend_cbs(&rdp->cblist, &rcl);
	WRITE_ONCE(rdp->nocb_bypass_first, j);
	rcu_nocb_bypass_unlock(rdp);
	वापस true;
पूर्ण

/*
 * Flush the ->nocb_bypass queue पूर्णांकo ->cblist, enqueuing rhp अगर non-शून्य.
 * However, अगर there is a callback to be enqueued and अगर ->nocb_bypass
 * proves to be initially empty, just वापस false because the no-CB GP
 * kthपढ़ो may need to be awakened in this हाल.
 *
 * Note that this function always वापसs true अगर rhp is शून्य.
 */
अटल bool rcu_nocb_flush_bypass(काष्ठा rcu_data *rdp, काष्ठा rcu_head *rhp,
				  अचिन्हित दीर्घ j)
अणु
	अगर (!rcu_rdp_is_offloaded(rdp))
		वापस true;
	rcu_lockdep_निश्चित_cblist_रक्षित(rdp);
	rcu_nocb_bypass_lock(rdp);
	वापस rcu_nocb_करो_flush_bypass(rdp, rhp, j);
पूर्ण

/*
 * If the ->nocb_bypass_lock is immediately available, flush the
 * ->nocb_bypass queue पूर्णांकo ->cblist.
 */
अटल व्योम rcu_nocb_try_flush_bypass(काष्ठा rcu_data *rdp, अचिन्हित दीर्घ j)
अणु
	rcu_lockdep_निश्चित_cblist_रक्षित(rdp);
	अगर (!rcu_rdp_is_offloaded(rdp) ||
	    !rcu_nocb_bypass_trylock(rdp))
		वापस;
	WARN_ON_ONCE(!rcu_nocb_करो_flush_bypass(rdp, शून्य, j));
पूर्ण

/*
 * See whether it is appropriate to use the ->nocb_bypass list in order
 * to control contention on ->nocb_lock.  A limited number of direct
 * enqueues are permitted पूर्णांकo ->cblist per jअगरfy.  If ->nocb_bypass
 * is non-empty, further callbacks must be placed पूर्णांकo ->nocb_bypass,
 * otherwise rcu_barrier() अवरोधs.  Use rcu_nocb_flush_bypass() to चयन
 * back to direct use of ->cblist.  However, ->nocb_bypass should not be
 * used अगर ->cblist is empty, because otherwise callbacks can be stअक्रमed
 * on ->nocb_bypass because we cannot count on the current CPU ever again
 * invoking call_rcu().  The general rule is that अगर ->nocb_bypass is
 * non-empty, the corresponding no-CBs grace-period kthपढ़ो must not be
 * in an indefinite sleep state.
 *
 * Finally, it is not permitted to use the bypass during early boot,
 * as करोing so would confuse the स्वतः-initialization code.  Besides
 * which, there is no poपूर्णांक in worrying about lock contention जबतक
 * there is only one CPU in operation.
 */
अटल bool rcu_nocb_try_bypass(काष्ठा rcu_data *rdp, काष्ठा rcu_head *rhp,
				bool *was_allकरोne, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ c;
	अचिन्हित दीर्घ cur_gp_seq;
	अचिन्हित दीर्घ j = jअगरfies;
	दीर्घ ncbs = rcu_cblist_n_cbs(&rdp->nocb_bypass);

	lockdep_निश्चित_irqs_disabled();

	// Pure softirq/rcuc based processing: no bypassing, no
	// locking.
	अगर (!rcu_rdp_is_offloaded(rdp)) अणु
		*was_allकरोne = !rcu_segcblist_pend_cbs(&rdp->cblist);
		वापस false;
	पूर्ण

	// In the process of (de-)offloading: no bypassing, but
	// locking.
	अगर (!rcu_segcblist_completely_offloaded(&rdp->cblist)) अणु
		rcu_nocb_lock(rdp);
		*was_allकरोne = !rcu_segcblist_pend_cbs(&rdp->cblist);
		वापस false; /* Not offloaded, no bypassing. */
	पूर्ण

	// Don't use ->nocb_bypass during early boot.
	अगर (rcu_scheduler_active != RCU_SCHEDULER_RUNNING) अणु
		rcu_nocb_lock(rdp);
		WARN_ON_ONCE(rcu_cblist_n_cbs(&rdp->nocb_bypass));
		*was_allकरोne = !rcu_segcblist_pend_cbs(&rdp->cblist);
		वापस false;
	पूर्ण

	// If we have advanced to a new jअगरfy, reset counts to allow
	// moving back from ->nocb_bypass to ->cblist.
	अगर (j == rdp->nocb_nobypass_last) अणु
		c = rdp->nocb_nobypass_count + 1;
	पूर्ण अन्यथा अणु
		WRITE_ONCE(rdp->nocb_nobypass_last, j);
		c = rdp->nocb_nobypass_count - nocb_nobypass_lim_per_jअगरfy;
		अगर (ULONG_CMP_LT(rdp->nocb_nobypass_count,
				 nocb_nobypass_lim_per_jअगरfy))
			c = 0;
		अन्यथा अगर (c > nocb_nobypass_lim_per_jअगरfy)
			c = nocb_nobypass_lim_per_jअगरfy;
	पूर्ण
	WRITE_ONCE(rdp->nocb_nobypass_count, c);

	// If there hasn't yet been all that many ->cblist enqueues
	// this jअगरfy, tell the caller to enqueue onto ->cblist.  But flush
	// ->nocb_bypass first.
	अगर (rdp->nocb_nobypass_count < nocb_nobypass_lim_per_jअगरfy) अणु
		rcu_nocb_lock(rdp);
		*was_allकरोne = !rcu_segcblist_pend_cbs(&rdp->cblist);
		अगर (*was_allकरोne)
			trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
					    TPS("FirstQ"));
		WARN_ON_ONCE(!rcu_nocb_flush_bypass(rdp, शून्य, j));
		WARN_ON_ONCE(rcu_cblist_n_cbs(&rdp->nocb_bypass));
		वापस false; // Caller must enqueue the callback.
	पूर्ण

	// If ->nocb_bypass has been used too दीर्घ or is too full,
	// flush ->nocb_bypass to ->cblist.
	अगर ((ncbs && j != READ_ONCE(rdp->nocb_bypass_first)) ||
	    ncbs >= qhimark) अणु
		rcu_nocb_lock(rdp);
		अगर (!rcu_nocb_flush_bypass(rdp, rhp, j)) अणु
			*was_allकरोne = !rcu_segcblist_pend_cbs(&rdp->cblist);
			अगर (*was_allकरोne)
				trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
						    TPS("FirstQ"));
			WARN_ON_ONCE(rcu_cblist_n_cbs(&rdp->nocb_bypass));
			वापस false; // Caller must enqueue the callback.
		पूर्ण
		अगर (j != rdp->nocb_gp_adv_समय &&
		    rcu_segcblist_nextgp(&rdp->cblist, &cur_gp_seq) &&
		    rcu_seq_करोne(&rdp->mynode->gp_seq, cur_gp_seq)) अणु
			rcu_advance_cbs_nowake(rdp->mynode, rdp);
			rdp->nocb_gp_adv_समय = j;
		पूर्ण
		rcu_nocb_unlock_irqrestore(rdp, flags);
		वापस true; // Callback alपढ़ोy enqueued.
	पूर्ण

	// We need to use the bypass.
	rcu_nocb_रुको_contended(rdp);
	rcu_nocb_bypass_lock(rdp);
	ncbs = rcu_cblist_n_cbs(&rdp->nocb_bypass);
	rcu_segcblist_inc_len(&rdp->cblist); /* Must precede enqueue. */
	rcu_cblist_enqueue(&rdp->nocb_bypass, rhp);
	अगर (!ncbs) अणु
		WRITE_ONCE(rdp->nocb_bypass_first, j);
		trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("FirstBQ"));
	पूर्ण
	rcu_nocb_bypass_unlock(rdp);
	smp_mb(); /* Order enqueue beक्रमe wake. */
	अगर (ncbs) अणु
		local_irq_restore(flags);
	पूर्ण अन्यथा अणु
		// No-CBs GP kthपढ़ो might be indefinitely asleep, अगर so, wake.
		rcu_nocb_lock(rdp); // Rare during call_rcu() flood.
		अगर (!rcu_segcblist_pend_cbs(&rdp->cblist)) अणु
			trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
					    TPS("FirstBQwake"));
			__call_rcu_nocb_wake(rdp, true, flags);
		पूर्ण अन्यथा अणु
			trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
					    TPS("FirstBQnoWake"));
			rcu_nocb_unlock_irqrestore(rdp, flags);
		पूर्ण
	पूर्ण
	वापस true; // Callback alपढ़ोy enqueued.
पूर्ण

/*
 * Awaken the no-CBs grace-period kthead अगर needed, either due to it
 * legitimately being asleep or due to overload conditions.
 *
 * If warranted, also wake up the kthपढ़ो servicing this CPUs queues.
 */
अटल व्योम __call_rcu_nocb_wake(काष्ठा rcu_data *rdp, bool was_allकरोne,
				 अचिन्हित दीर्घ flags)
				 __releases(rdp->nocb_lock)
अणु
	अचिन्हित दीर्घ cur_gp_seq;
	अचिन्हित दीर्घ j;
	दीर्घ len;
	काष्ठा task_काष्ठा *t;

	// If we are being polled or there is no kthपढ़ो, just leave.
	t = READ_ONCE(rdp->nocb_gp_kthपढ़ो);
	अगर (rcu_nocb_poll || !t) अणु
		rcu_nocb_unlock_irqrestore(rdp, flags);
		trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
				    TPS("WakeNotPoll"));
		वापस;
	पूर्ण
	// Need to actually to a wakeup.
	len = rcu_segcblist_n_cbs(&rdp->cblist);
	अगर (was_allकरोne) अणु
		rdp->qlen_last_fqs_check = len;
		अगर (!irqs_disabled_flags(flags)) अणु
			/* ... अगर queue was empty ... */
			wake_nocb_gp(rdp, false, flags);
			trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
					    TPS("WakeEmpty"));
		पूर्ण अन्यथा अणु
			wake_nocb_gp_defer(rdp, RCU_NOCB_WAKE,
					   TPS("WakeEmptyIsDeferred"));
			rcu_nocb_unlock_irqrestore(rdp, flags);
		पूर्ण
	पूर्ण अन्यथा अगर (len > rdp->qlen_last_fqs_check + qhimark) अणु
		/* ... or अगर many callbacks queued. */
		rdp->qlen_last_fqs_check = len;
		j = jअगरfies;
		अगर (j != rdp->nocb_gp_adv_समय &&
		    rcu_segcblist_nextgp(&rdp->cblist, &cur_gp_seq) &&
		    rcu_seq_करोne(&rdp->mynode->gp_seq, cur_gp_seq)) अणु
			rcu_advance_cbs_nowake(rdp->mynode, rdp);
			rdp->nocb_gp_adv_समय = j;
		पूर्ण
		smp_mb(); /* Enqueue beक्रमe समयr_pending(). */
		अगर ((rdp->nocb_cb_sleep ||
		     !rcu_segcblist_पढ़ोy_cbs(&rdp->cblist)) &&
		    !समयr_pending(&rdp->nocb_bypass_समयr))
			wake_nocb_gp_defer(rdp, RCU_NOCB_WAKE_FORCE,
					   TPS("WakeOvfIsDeferred"));
		rcu_nocb_unlock_irqrestore(rdp, flags);
	पूर्ण अन्यथा अणु
		rcu_nocb_unlock_irqrestore(rdp, flags);
		trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("WakeNot"));
	पूर्ण
	वापस;
पूर्ण

/* Wake up the no-CBs GP kthपढ़ो to flush ->nocb_bypass. */
अटल व्योम करो_nocb_bypass_wakeup_समयr(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp = from_समयr(rdp, t, nocb_bypass_समयr);

	trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("Timer"));
	rcu_nocb_lock_irqsave(rdp, flags);
	smp_mb__after_spinlock(); /* Timer expire beक्रमe wakeup. */
	__call_rcu_nocb_wake(rdp, true, flags);
पूर्ण

/*
 * Check अगर we ignore this rdp.
 *
 * We check that without holding the nocb lock but
 * we make sure not to miss a freshly offloaded rdp
 * with the current ordering:
 *
 *  rdp_offload_toggle()        nocb_gp_enabled_cb()
 * -------------------------   ----------------------------
 *    WRITE flags                 LOCK nocb_gp_lock
 *    LOCK nocb_gp_lock           READ/WRITE nocb_gp_sleep
 *    READ/WRITE nocb_gp_sleep    UNLOCK nocb_gp_lock
 *    UNLOCK nocb_gp_lock         READ flags
 */
अटल अंतरभूत bool nocb_gp_enabled_cb(काष्ठा rcu_data *rdp)
अणु
	u8 flags = SEGCBLIST_OFFLOADED | SEGCBLIST_KTHREAD_GP;

	वापस rcu_segcblist_test_flags(&rdp->cblist, flags);
पूर्ण

अटल अंतरभूत bool nocb_gp_update_state_deoffloading(काष्ठा rcu_data *rdp,
						     bool *needwake_state)
अणु
	काष्ठा rcu_segcblist *cblist = &rdp->cblist;

	अगर (rcu_segcblist_test_flags(cblist, SEGCBLIST_OFFLOADED)) अणु
		अगर (!rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_GP)) अणु
			rcu_segcblist_set_flags(cblist, SEGCBLIST_KTHREAD_GP);
			अगर (rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_CB))
				*needwake_state = true;
		पूर्ण
		वापस false;
	पूर्ण

	/*
	 * De-offloading. Clear our flag and notअगरy the de-offload worker.
	 * We will ignore this rdp until it ever माला_लो re-offloaded.
	 */
	WARN_ON_ONCE(!rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_GP));
	rcu_segcblist_clear_flags(cblist, SEGCBLIST_KTHREAD_GP);
	अगर (!rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_CB))
		*needwake_state = true;
	वापस true;
पूर्ण


/*
 * No-CBs GP kthपढ़ोs come here to रुको क्रम additional callbacks to show up
 * or क्रम grace periods to end.
 */
अटल व्योम nocb_gp_रुको(काष्ठा rcu_data *my_rdp)
अणु
	bool bypass = false;
	दीर्घ bypass_ncbs;
	पूर्णांक __maybe_unused cpu = my_rdp->cpu;
	अचिन्हित दीर्घ cur_gp_seq;
	अचिन्हित दीर्घ flags;
	bool gotcbs = false;
	अचिन्हित दीर्घ j = jअगरfies;
	bool needरुको_gp = false; // This prevents actual uninitialized use.
	bool needwake;
	bool needwake_gp;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;
	अचिन्हित दीर्घ रुको_gp_seq = 0; // Suppress "use uninitialized" warning.
	bool wasempty = false;

	/*
	 * Each pass through the following loop checks क्रम CBs and क्रम the
	 * nearest grace period (अगर any) to रुको क्रम next.  The CB kthपढ़ोs
	 * and the global grace-period kthपढ़ो are awakened अगर needed.
	 */
	WARN_ON_ONCE(my_rdp->nocb_gp_rdp != my_rdp);
	क्रम (rdp = my_rdp; rdp; rdp = rdp->nocb_next_cb_rdp) अणु
		bool needwake_state = false;

		अगर (!nocb_gp_enabled_cb(rdp))
			जारी;
		trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("Check"));
		rcu_nocb_lock_irqsave(rdp, flags);
		अगर (nocb_gp_update_state_deoffloading(rdp, &needwake_state)) अणु
			rcu_nocb_unlock_irqrestore(rdp, flags);
			अगर (needwake_state)
				swake_up_one(&rdp->nocb_state_wq);
			जारी;
		पूर्ण
		bypass_ncbs = rcu_cblist_n_cbs(&rdp->nocb_bypass);
		अगर (bypass_ncbs &&
		    (समय_after(j, READ_ONCE(rdp->nocb_bypass_first) + 1) ||
		     bypass_ncbs > 2 * qhimark)) अणु
			// Bypass full or old, so flush it.
			(व्योम)rcu_nocb_try_flush_bypass(rdp, j);
			bypass_ncbs = rcu_cblist_n_cbs(&rdp->nocb_bypass);
		पूर्ण अन्यथा अगर (!bypass_ncbs && rcu_segcblist_empty(&rdp->cblist)) अणु
			rcu_nocb_unlock_irqrestore(rdp, flags);
			अगर (needwake_state)
				swake_up_one(&rdp->nocb_state_wq);
			जारी; /* No callbacks here, try next. */
		पूर्ण
		अगर (bypass_ncbs) अणु
			trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
					    TPS("Bypass"));
			bypass = true;
		पूर्ण
		rnp = rdp->mynode;
		अगर (bypass) अणु  // Aव्योम race with first bypass CB.
			WRITE_ONCE(my_rdp->nocb_defer_wakeup,
				   RCU_NOCB_WAKE_NOT);
			del_समयr(&my_rdp->nocb_समयr);
		पूर्ण
		// Advance callbacks अगर helpful and low contention.
		needwake_gp = false;
		अगर (!rcu_segcblist_restempty(&rdp->cblist,
					     RCU_NEXT_READY_TAIL) ||
		    (rcu_segcblist_nextgp(&rdp->cblist, &cur_gp_seq) &&
		     rcu_seq_करोne(&rnp->gp_seq, cur_gp_seq))) अणु
			raw_spin_lock_rcu_node(rnp); /* irqs disabled. */
			needwake_gp = rcu_advance_cbs(rnp, rdp);
			wasempty = rcu_segcblist_restempty(&rdp->cblist,
							   RCU_NEXT_READY_TAIL);
			raw_spin_unlock_rcu_node(rnp); /* irqs disabled. */
		पूर्ण
		// Need to रुको on some grace period?
		WARN_ON_ONCE(wasempty &&
			     !rcu_segcblist_restempty(&rdp->cblist,
						      RCU_NEXT_READY_TAIL));
		अगर (rcu_segcblist_nextgp(&rdp->cblist, &cur_gp_seq)) अणु
			अगर (!needरुको_gp ||
			    ULONG_CMP_LT(cur_gp_seq, रुको_gp_seq))
				रुको_gp_seq = cur_gp_seq;
			needरुको_gp = true;
			trace_rcu_nocb_wake(rcu_state.name, rdp->cpu,
					    TPS("NeedWaitGP"));
		पूर्ण
		अगर (rcu_segcblist_पढ़ोy_cbs(&rdp->cblist)) अणु
			needwake = rdp->nocb_cb_sleep;
			WRITE_ONCE(rdp->nocb_cb_sleep, false);
			smp_mb(); /* CB invocation -after- GP end. */
		पूर्ण अन्यथा अणु
			needwake = false;
		पूर्ण
		rcu_nocb_unlock_irqrestore(rdp, flags);
		अगर (needwake) अणु
			swake_up_one(&rdp->nocb_cb_wq);
			gotcbs = true;
		पूर्ण
		अगर (needwake_gp)
			rcu_gp_kthपढ़ो_wake();
		अगर (needwake_state)
			swake_up_one(&rdp->nocb_state_wq);
	पूर्ण

	my_rdp->nocb_gp_bypass = bypass;
	my_rdp->nocb_gp_gp = needरुको_gp;
	my_rdp->nocb_gp_seq = needरुको_gp ? रुको_gp_seq : 0;
	अगर (bypass && !rcu_nocb_poll) अणु
		// At least one child with non-empty ->nocb_bypass, so set
		// समयr in order to aव्योम stअक्रमing its callbacks.
		raw_spin_lock_irqsave(&my_rdp->nocb_gp_lock, flags);
		mod_समयr(&my_rdp->nocb_bypass_समयr, j + 2);
		raw_spin_unlock_irqrestore(&my_rdp->nocb_gp_lock, flags);
	पूर्ण
	अगर (rcu_nocb_poll) अणु
		/* Polling, so trace अगर first poll in the series. */
		अगर (gotcbs)
			trace_rcu_nocb_wake(rcu_state.name, cpu, TPS("Poll"));
		schedule_समयout_idle(1);
	पूर्ण अन्यथा अगर (!needरुको_gp) अणु
		/* Wait क्रम callbacks to appear. */
		trace_rcu_nocb_wake(rcu_state.name, cpu, TPS("Sleep"));
		sरुको_event_पूर्णांकerruptible_exclusive(my_rdp->nocb_gp_wq,
				!READ_ONCE(my_rdp->nocb_gp_sleep));
		trace_rcu_nocb_wake(rcu_state.name, cpu, TPS("EndSleep"));
	पूर्ण अन्यथा अणु
		rnp = my_rdp->mynode;
		trace_rcu_this_gp(rnp, my_rdp, रुको_gp_seq, TPS("StartWait"));
		sरुको_event_पूर्णांकerruptible_exclusive(
			rnp->nocb_gp_wq[rcu_seq_ctr(रुको_gp_seq) & 0x1],
			rcu_seq_करोne(&rnp->gp_seq, रुको_gp_seq) ||
			!READ_ONCE(my_rdp->nocb_gp_sleep));
		trace_rcu_this_gp(rnp, my_rdp, रुको_gp_seq, TPS("EndWait"));
	पूर्ण
	अगर (!rcu_nocb_poll) अणु
		raw_spin_lock_irqsave(&my_rdp->nocb_gp_lock, flags);
		अगर (bypass)
			del_समयr(&my_rdp->nocb_bypass_समयr);
		WRITE_ONCE(my_rdp->nocb_gp_sleep, true);
		raw_spin_unlock_irqrestore(&my_rdp->nocb_gp_lock, flags);
	पूर्ण
	my_rdp->nocb_gp_seq = -1;
	WARN_ON(संकेत_pending(current));
पूर्ण

/*
 * No-CBs grace-period-रुको kthपढ़ो.  There is one of these per group
 * of CPUs, but only once at least one CPU in that group has come online
 * at least once since boot.  This kthपढ़ो checks क्रम newly posted
 * callbacks from any of the CPUs it is responsible क्रम, रुकोs क्रम a
 * grace period, then awakens all of the rcu_nocb_cb_kthपढ़ो() instances
 * that then have callback-invocation work to करो.
 */
अटल पूर्णांक rcu_nocb_gp_kthपढ़ो(व्योम *arg)
अणु
	काष्ठा rcu_data *rdp = arg;

	क्रम (;;) अणु
		WRITE_ONCE(rdp->nocb_gp_loops, rdp->nocb_gp_loops + 1);
		nocb_gp_रुको(rdp);
		cond_resched_tasks_rcu_qs();
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool nocb_cb_can_run(काष्ठा rcu_data *rdp)
अणु
	u8 flags = SEGCBLIST_OFFLOADED | SEGCBLIST_KTHREAD_CB;
	वापस rcu_segcblist_test_flags(&rdp->cblist, flags);
पूर्ण

अटल अंतरभूत bool nocb_cb_रुको_cond(काष्ठा rcu_data *rdp)
अणु
	वापस nocb_cb_can_run(rdp) && !READ_ONCE(rdp->nocb_cb_sleep);
पूर्ण

/*
 * Invoke any पढ़ोy callbacks from the corresponding no-CBs CPU,
 * then, अगर there are no more, रुको क्रम more to appear.
 */
अटल व्योम nocb_cb_रुको(काष्ठा rcu_data *rdp)
अणु
	काष्ठा rcu_segcblist *cblist = &rdp->cblist;
	अचिन्हित दीर्घ cur_gp_seq;
	अचिन्हित दीर्घ flags;
	bool needwake_state = false;
	bool needwake_gp = false;
	bool can_sleep = true;
	काष्ठा rcu_node *rnp = rdp->mynode;

	local_irq_save(flags);
	rcu_momentary_dyntick_idle();
	local_irq_restore(flags);
	/*
	 * Disable BH to provide the expected environment.  Also, when
	 * transitioning to/from NOCB mode, a self-requeuing callback might
	 * be invoked from softirq.  A लघु grace period could cause both
	 * instances of this callback would execute concurrently.
	 */
	local_bh_disable();
	rcu_करो_batch(rdp);
	local_bh_enable();
	lockdep_निश्चित_irqs_enabled();
	rcu_nocb_lock_irqsave(rdp, flags);
	अगर (rcu_segcblist_nextgp(cblist, &cur_gp_seq) &&
	    rcu_seq_करोne(&rnp->gp_seq, cur_gp_seq) &&
	    raw_spin_trylock_rcu_node(rnp)) अणु /* irqs alपढ़ोy disabled. */
		needwake_gp = rcu_advance_cbs(rdp->mynode, rdp);
		raw_spin_unlock_rcu_node(rnp); /* irqs reमुख्य disabled. */
	पूर्ण

	अगर (rcu_segcblist_test_flags(cblist, SEGCBLIST_OFFLOADED)) अणु
		अगर (!rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_CB)) अणु
			rcu_segcblist_set_flags(cblist, SEGCBLIST_KTHREAD_CB);
			अगर (rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_GP))
				needwake_state = true;
		पूर्ण
		अगर (rcu_segcblist_पढ़ोy_cbs(cblist))
			can_sleep = false;
	पूर्ण अन्यथा अणु
		/*
		 * De-offloading. Clear our flag and notअगरy the de-offload worker.
		 * We won't touch the callbacks and keep sleeping until we ever
		 * get re-offloaded.
		 */
		WARN_ON_ONCE(!rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_CB));
		rcu_segcblist_clear_flags(cblist, SEGCBLIST_KTHREAD_CB);
		अगर (!rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_GP))
			needwake_state = true;
	पूर्ण

	WRITE_ONCE(rdp->nocb_cb_sleep, can_sleep);

	अगर (rdp->nocb_cb_sleep)
		trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("CBSleep"));

	rcu_nocb_unlock_irqrestore(rdp, flags);
	अगर (needwake_gp)
		rcu_gp_kthपढ़ो_wake();

	अगर (needwake_state)
		swake_up_one(&rdp->nocb_state_wq);

	करो अणु
		sरुको_event_पूर्णांकerruptible_exclusive(rdp->nocb_cb_wq,
						    nocb_cb_रुको_cond(rdp));

		// VVV Ensure CB invocation follows _sleep test.
		अगर (smp_load_acquire(&rdp->nocb_cb_sleep)) अणु // ^^^
			WARN_ON(संकेत_pending(current));
			trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("WokeEmpty"));
		पूर्ण
	पूर्ण जबतक (!nocb_cb_can_run(rdp));
पूर्ण

/*
 * Per-rcu_data kthपढ़ो, but only क्रम no-CBs CPUs.  Repeatedly invoke
 * nocb_cb_रुको() to करो the dirty work.
 */
अटल पूर्णांक rcu_nocb_cb_kthपढ़ो(व्योम *arg)
अणु
	काष्ठा rcu_data *rdp = arg;

	// Each pass through this loop करोes one callback batch, and,
	// अगर there are no more पढ़ोy callbacks, रुकोs क्रम them.
	क्रम (;;) अणु
		nocb_cb_रुको(rdp);
		cond_resched_tasks_rcu_qs();
	पूर्ण
	वापस 0;
पूर्ण

/* Is a deferred wakeup of rcu_nocb_kthपढ़ो() required? */
अटल पूर्णांक rcu_nocb_need_deferred_wakeup(काष्ठा rcu_data *rdp)
अणु
	वापस READ_ONCE(rdp->nocb_defer_wakeup) > RCU_NOCB_WAKE_NOT;
पूर्ण

/* Do a deferred wakeup of rcu_nocb_kthपढ़ो(). */
अटल bool करो_nocb_deferred_wakeup_common(काष्ठा rcu_data *rdp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ndw;
	पूर्णांक ret;

	rcu_nocb_lock_irqsave(rdp, flags);
	अगर (!rcu_nocb_need_deferred_wakeup(rdp)) अणु
		rcu_nocb_unlock_irqrestore(rdp, flags);
		वापस false;
	पूर्ण
	ndw = READ_ONCE(rdp->nocb_defer_wakeup);
	ret = wake_nocb_gp(rdp, ndw == RCU_NOCB_WAKE_FORCE, flags);
	trace_rcu_nocb_wake(rcu_state.name, rdp->cpu, TPS("DeferredWake"));

	वापस ret;
पूर्ण

/* Do a deferred wakeup of rcu_nocb_kthपढ़ो() from a समयr handler. */
अटल व्योम करो_nocb_deferred_wakeup_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rcu_data *rdp = from_समयr(rdp, t, nocb_समयr);

	करो_nocb_deferred_wakeup_common(rdp);
पूर्ण

/*
 * Do a deferred wakeup of rcu_nocb_kthपढ़ो() from fastpath.
 * This means we करो an inexact common-हाल check.  Note that अगर
 * we miss, ->nocb_समयr will eventually clean things up.
 */
अटल bool करो_nocb_deferred_wakeup(काष्ठा rcu_data *rdp)
अणु
	अगर (rcu_nocb_need_deferred_wakeup(rdp))
		वापस करो_nocb_deferred_wakeup_common(rdp);
	वापस false;
पूर्ण

व्योम rcu_nocb_flush_deferred_wakeup(व्योम)
अणु
	करो_nocb_deferred_wakeup(this_cpu_ptr(&rcu_data));
पूर्ण
EXPORT_SYMBOL_GPL(rcu_nocb_flush_deferred_wakeup);

अटल पूर्णांक rdp_offload_toggle(काष्ठा rcu_data *rdp,
			       bool offload, अचिन्हित दीर्घ flags)
	__releases(rdp->nocb_lock)
अणु
	काष्ठा rcu_segcblist *cblist = &rdp->cblist;
	काष्ठा rcu_data *rdp_gp = rdp->nocb_gp_rdp;
	bool wake_gp = false;

	rcu_segcblist_offload(cblist, offload);

	अगर (rdp->nocb_cb_sleep)
		rdp->nocb_cb_sleep = false;
	rcu_nocb_unlock_irqrestore(rdp, flags);

	/*
	 * Ignore क्रमmer value of nocb_cb_sleep and क्रमce wake up as it could
	 * have been spuriously set to false alपढ़ोy.
	 */
	swake_up_one(&rdp->nocb_cb_wq);

	raw_spin_lock_irqsave(&rdp_gp->nocb_gp_lock, flags);
	अगर (rdp_gp->nocb_gp_sleep) अणु
		rdp_gp->nocb_gp_sleep = false;
		wake_gp = true;
	पूर्ण
	raw_spin_unlock_irqrestore(&rdp_gp->nocb_gp_lock, flags);

	अगर (wake_gp)
		wake_up_process(rdp_gp->nocb_gp_kthपढ़ो);

	वापस 0;
पूर्ण

अटल दीर्घ rcu_nocb_rdp_deoffload(व्योम *arg)
अणु
	काष्ठा rcu_data *rdp = arg;
	काष्ठा rcu_segcblist *cblist = &rdp->cblist;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	WARN_ON_ONCE(rdp->cpu != raw_smp_processor_id());

	pr_info("De-offloading %d\n", rdp->cpu);

	rcu_nocb_lock_irqsave(rdp, flags);
	/*
	 * Flush once and क्रम all now. This suffices because we are
	 * running on the target CPU holding ->nocb_lock (thus having
	 * पूर्णांकerrupts disabled), and because rdp_offload_toggle()
	 * invokes rcu_segcblist_offload(), which clears SEGCBLIST_OFFLOADED.
	 * Thus future calls to rcu_segcblist_completely_offloaded() will
	 * वापस false, which means that future calls to rcu_nocb_try_bypass()
	 * will refuse to put anything पूर्णांकo the bypass.
	 */
	WARN_ON_ONCE(!rcu_nocb_flush_bypass(rdp, शून्य, jअगरfies));
	ret = rdp_offload_toggle(rdp, false, flags);
	sरुको_event_exclusive(rdp->nocb_state_wq,
			      !rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_CB |
							SEGCBLIST_KTHREAD_GP));
	rcu_nocb_lock_irqsave(rdp, flags);
	/* Make sure nocb समयr won't stay around */
	WRITE_ONCE(rdp->nocb_defer_wakeup, RCU_NOCB_WAKE_OFF);
	rcu_nocb_unlock_irqrestore(rdp, flags);
	del_समयr_sync(&rdp->nocb_समयr);

	/*
	 * Theoretically we could set SEGCBLIST_SOFTIRQ_ONLY with CB unlocked
	 * and IRQs disabled but let's be paranoid.
	 */
	rcu_nocb_lock_irqsave(rdp, flags);
	rcu_segcblist_set_flags(cblist, SEGCBLIST_SOFTIRQ_ONLY);
	/*
	 * With SEGCBLIST_SOFTIRQ_ONLY, we can't use
	 * rcu_nocb_unlock_irqrestore() anymore.
	 */
	raw_spin_unlock_irqrestore(&rdp->nocb_lock, flags);

	/* Sanity check */
	WARN_ON_ONCE(rcu_cblist_n_cbs(&rdp->nocb_bypass));


	वापस ret;
पूर्ण

पूर्णांक rcu_nocb_cpu_deoffload(पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	पूर्णांक ret = 0;

	अगर (rdp == rdp->nocb_gp_rdp) अणु
		pr_info("Can't deoffload an rdp GP leader (yet)\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&rcu_state.barrier_mutex);
	cpus_पढ़ो_lock();
	अगर (rcu_rdp_is_offloaded(rdp)) अणु
		अगर (cpu_online(cpu)) अणु
			ret = work_on_cpu(cpu, rcu_nocb_rdp_deoffload, rdp);
			अगर (!ret)
				cpumask_clear_cpu(cpu, rcu_nocb_mask);
		पूर्ण अन्यथा अणु
			pr_info("NOCB: Can't CB-deoffload an offline CPU\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	cpus_पढ़ो_unlock();
	mutex_unlock(&rcu_state.barrier_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_nocb_cpu_deoffload);

अटल दीर्घ rcu_nocb_rdp_offload(व्योम *arg)
अणु
	काष्ठा rcu_data *rdp = arg;
	काष्ठा rcu_segcblist *cblist = &rdp->cblist;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	WARN_ON_ONCE(rdp->cpu != raw_smp_processor_id());
	/*
	 * For now we only support re-offload, ie: the rdp must have been
	 * offloaded on boot first.
	 */
	अगर (!rdp->nocb_gp_rdp)
		वापस -EINVAL;

	pr_info("Offloading %d\n", rdp->cpu);
	/*
	 * Can't use rcu_nocb_lock_irqsave() जबतक we are in
	 * SEGCBLIST_SOFTIRQ_ONLY mode.
	 */
	raw_spin_lock_irqsave(&rdp->nocb_lock, flags);
	/* Re-enable nocb समयr */
	WRITE_ONCE(rdp->nocb_defer_wakeup, RCU_NOCB_WAKE_NOT);
	/*
	 * We didn't take the nocb lock जबतक working on the
	 * rdp->cblist in SEGCBLIST_SOFTIRQ_ONLY mode.
	 * Every modअगरications that have been करोne previously on
	 * rdp->cblist must be visible remotely by the nocb kthपढ़ोs
	 * upon wake up after पढ़ोing the cblist flags.
	 *
	 * The layout against nocb_lock enक्रमces that ordering:
	 *
	 *  __rcu_nocb_rdp_offload()   nocb_cb_रुको()/nocb_gp_रुको()
	 * -------------------------   ----------------------------
	 *      WRITE callbacks           rcu_nocb_lock()
	 *      rcu_nocb_lock()           READ flags
	 *      WRITE flags               READ callbacks
	 *      rcu_nocb_unlock()         rcu_nocb_unlock()
	 */
	ret = rdp_offload_toggle(rdp, true, flags);
	sरुको_event_exclusive(rdp->nocb_state_wq,
			      rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_CB) &&
			      rcu_segcblist_test_flags(cblist, SEGCBLIST_KTHREAD_GP));

	वापस ret;
पूर्ण

पूर्णांक rcu_nocb_cpu_offload(पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	पूर्णांक ret = 0;

	mutex_lock(&rcu_state.barrier_mutex);
	cpus_पढ़ो_lock();
	अगर (!rcu_rdp_is_offloaded(rdp)) अणु
		अगर (cpu_online(cpu)) अणु
			ret = work_on_cpu(cpu, rcu_nocb_rdp_offload, rdp);
			अगर (!ret)
				cpumask_set_cpu(cpu, rcu_nocb_mask);
		पूर्ण अन्यथा अणु
			pr_info("NOCB: Can't CB-offload an offline CPU\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	cpus_पढ़ो_unlock();
	mutex_unlock(&rcu_state.barrier_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_nocb_cpu_offload);

व्योम __init rcu_init_nohz(व्योम)
अणु
	पूर्णांक cpu;
	bool need_rcu_nocb_mask = false;
	काष्ठा rcu_data *rdp;

#अगर defined(CONFIG_NO_HZ_FULL)
	अगर (tick_nohz_full_running && cpumask_weight(tick_nohz_full_mask))
		need_rcu_nocb_mask = true;
#पूर्ण_अगर /* #अगर defined(CONFIG_NO_HZ_FULL) */

	अगर (!cpumask_available(rcu_nocb_mask) && need_rcu_nocb_mask) अणु
		अगर (!zalloc_cpumask_var(&rcu_nocb_mask, GFP_KERNEL)) अणु
			pr_info("rcu_nocb_mask allocation failed, callback offloading disabled.\n");
			वापस;
		पूर्ण
	पूर्ण
	अगर (!cpumask_available(rcu_nocb_mask))
		वापस;

#अगर defined(CONFIG_NO_HZ_FULL)
	अगर (tick_nohz_full_running)
		cpumask_or(rcu_nocb_mask, rcu_nocb_mask, tick_nohz_full_mask);
#पूर्ण_अगर /* #अगर defined(CONFIG_NO_HZ_FULL) */

	अगर (!cpumask_subset(rcu_nocb_mask, cpu_possible_mask)) अणु
		pr_info("\tNote: kernel parameter 'rcu_nocbs=', 'nohz_full', or 'isolcpus=' contains nonexistent CPUs.\n");
		cpumask_and(rcu_nocb_mask, cpu_possible_mask,
			    rcu_nocb_mask);
	पूर्ण
	अगर (cpumask_empty(rcu_nocb_mask))
		pr_info("\tOffload RCU callbacks from CPUs: (none).\n");
	अन्यथा
		pr_info("\tOffload RCU callbacks from CPUs: %*pbl.\n",
			cpumask_pr_args(rcu_nocb_mask));
	अगर (rcu_nocb_poll)
		pr_info("\tPoll for callbacks from no-CBs CPUs.\n");

	क्रम_each_cpu(cpu, rcu_nocb_mask) अणु
		rdp = per_cpu_ptr(&rcu_data, cpu);
		अगर (rcu_segcblist_empty(&rdp->cblist))
			rcu_segcblist_init(&rdp->cblist);
		rcu_segcblist_offload(&rdp->cblist, true);
		rcu_segcblist_set_flags(&rdp->cblist, SEGCBLIST_KTHREAD_CB);
		rcu_segcblist_set_flags(&rdp->cblist, SEGCBLIST_KTHREAD_GP);
	पूर्ण
	rcu_organize_nocb_kthपढ़ोs();
पूर्ण

/* Initialize per-rcu_data variables क्रम no-CBs CPUs. */
अटल व्योम __init rcu_boot_init_nocb_percpu_data(काष्ठा rcu_data *rdp)
अणु
	init_sरुको_queue_head(&rdp->nocb_cb_wq);
	init_sरुको_queue_head(&rdp->nocb_gp_wq);
	init_sरुको_queue_head(&rdp->nocb_state_wq);
	raw_spin_lock_init(&rdp->nocb_lock);
	raw_spin_lock_init(&rdp->nocb_bypass_lock);
	raw_spin_lock_init(&rdp->nocb_gp_lock);
	समयr_setup(&rdp->nocb_समयr, करो_nocb_deferred_wakeup_समयr, 0);
	समयr_setup(&rdp->nocb_bypass_समयr, करो_nocb_bypass_wakeup_समयr, 0);
	rcu_cblist_init(&rdp->nocb_bypass);
पूर्ण

/*
 * If the specअगरied CPU is a no-CBs CPU that करोes not alपढ़ोy have its
 * rcuo CB kthपढ़ो, spawn it.  Additionally, अगर the rcuo GP kthपढ़ो
 * क्रम this CPU's group has not yet been created, spawn it as well.
 */
अटल व्योम rcu_spawn_one_nocb_kthपढ़ो(पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	काष्ठा rcu_data *rdp_gp;
	काष्ठा task_काष्ठा *t;

	/*
	 * If this isn't a no-CBs CPU or अगर it alपढ़ोy has an rcuo kthपढ़ो,
	 * then nothing to करो.
	 */
	अगर (!rcu_is_nocb_cpu(cpu) || rdp->nocb_cb_kthपढ़ो)
		वापस;

	/* If we didn't spawn the GP kthपढ़ो first, reorganize! */
	rdp_gp = rdp->nocb_gp_rdp;
	अगर (!rdp_gp->nocb_gp_kthपढ़ो) अणु
		t = kthपढ़ो_run(rcu_nocb_gp_kthपढ़ो, rdp_gp,
				"rcuog/%d", rdp_gp->cpu);
		अगर (WARN_ONCE(IS_ERR(t), "%s: Could not start rcuo GP kthread, OOM is now expected behavior\n", __func__))
			वापस;
		WRITE_ONCE(rdp_gp->nocb_gp_kthपढ़ो, t);
	पूर्ण

	/* Spawn the kthपढ़ो क्रम this CPU. */
	t = kthपढ़ो_run(rcu_nocb_cb_kthपढ़ो, rdp,
			"rcuo%c/%d", rcu_state.abbr, cpu);
	अगर (WARN_ONCE(IS_ERR(t), "%s: Could not start rcuo CB kthread, OOM is now expected behavior\n", __func__))
		वापस;
	WRITE_ONCE(rdp->nocb_cb_kthपढ़ो, t);
	WRITE_ONCE(rdp->nocb_gp_kthपढ़ो, rdp_gp->nocb_gp_kthपढ़ो);
पूर्ण

/*
 * If the specअगरied CPU is a no-CBs CPU that करोes not alपढ़ोy have its
 * rcuo kthपढ़ो, spawn it.
 */
अटल व्योम rcu_spawn_cpu_nocb_kthपढ़ो(पूर्णांक cpu)
अणु
	अगर (rcu_scheduler_fully_active)
		rcu_spawn_one_nocb_kthपढ़ो(cpu);
पूर्ण

/*
 * Once the scheduler is running, spawn rcuo kthपढ़ोs क्रम all online
 * no-CBs CPUs.  This assumes that the early_initcall()s happen beक्रमe
 * non-boot CPUs come online -- अगर this changes, we will need to add
 * some mutual exclusion.
 */
अटल व्योम __init rcu_spawn_nocb_kthपढ़ोs(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		rcu_spawn_cpu_nocb_kthपढ़ो(cpu);
पूर्ण

/* How many CB CPU IDs per GP kthपढ़ो?  Default of -1 क्रम वर्ग_मूल(nr_cpu_ids). */
अटल पूर्णांक rcu_nocb_gp_stride = -1;
module_param(rcu_nocb_gp_stride, पूर्णांक, 0444);

/*
 * Initialize GP-CB relationships क्रम all no-CBs CPU.
 */
अटल व्योम __init rcu_organize_nocb_kthपढ़ोs(व्योम)
अणु
	पूर्णांक cpu;
	bool firstसमय = true;
	bool gotnocbs = false;
	bool gotnocbscbs = true;
	पूर्णांक ls = rcu_nocb_gp_stride;
	पूर्णांक nl = 0;  /* Next GP kthपढ़ो. */
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_data *rdp_gp = शून्य;  /* Suppress misguided gcc warn. */
	काष्ठा rcu_data *rdp_prev = शून्य;

	अगर (!cpumask_available(rcu_nocb_mask))
		वापस;
	अगर (ls == -1) अणु
		ls = nr_cpu_ids / पूर्णांक_वर्ग_मूल(nr_cpu_ids);
		rcu_nocb_gp_stride = ls;
	पूर्ण

	/*
	 * Each pass through this loop sets up one rcu_data काष्ठाure.
	 * Should the corresponding CPU come online in the future, then
	 * we will spawn the needed set of rcu_nocb_kthपढ़ो() kthपढ़ोs.
	 */
	क्रम_each_cpu(cpu, rcu_nocb_mask) अणु
		rdp = per_cpu_ptr(&rcu_data, cpu);
		अगर (rdp->cpu >= nl) अणु
			/* New GP kthपढ़ो, set up क्रम CBs & next GP. */
			gotnocbs = true;
			nl = DIV_ROUND_UP(rdp->cpu + 1, ls) * ls;
			rdp->nocb_gp_rdp = rdp;
			rdp_gp = rdp;
			अगर (dump_tree) अणु
				अगर (!firstसमय)
					pr_cont("%s\n", gotnocbscbs
							? "" : " (self only)");
				gotnocbscbs = false;
				firstसमय = false;
				pr_alert("%s: No-CB GP kthread CPU %d:",
					 __func__, cpu);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Another CB kthपढ़ो, link to previous GP kthपढ़ो. */
			gotnocbscbs = true;
			rdp->nocb_gp_rdp = rdp_gp;
			rdp_prev->nocb_next_cb_rdp = rdp;
			अगर (dump_tree)
				pr_cont(" %d", cpu);
		पूर्ण
		rdp_prev = rdp;
	पूर्ण
	अगर (gotnocbs && dump_tree)
		pr_cont("%s\n", gotnocbscbs ? "" : " (self only)");
पूर्ण

/*
 * Bind the current task to the offloaded CPUs.  If there are no offloaded
 * CPUs, leave the task unbound.  Splat अगर the bind attempt fails.
 */
व्योम rcu_bind_current_to_nocb(व्योम)
अणु
	अगर (cpumask_available(rcu_nocb_mask) && cpumask_weight(rcu_nocb_mask))
		WARN_ON(sched_setaffinity(current->pid, rcu_nocb_mask));
पूर्ण
EXPORT_SYMBOL_GPL(rcu_bind_current_to_nocb);

// The ->on_cpu field is available only in CONFIG_SMP=y, so...
#अगर_घोषित CONFIG_SMP
अटल अक्षर *show_rcu_should_be_on_cpu(काष्ठा task_काष्ठा *tsp)
अणु
	वापस tsp && tsp->state == TASK_RUNNING && !tsp->on_cpu ? "!" : "";
पूर्ण
#अन्यथा // #अगर_घोषित CONFIG_SMP
अटल अक्षर *show_rcu_should_be_on_cpu(काष्ठा task_काष्ठा *tsp)
अणु
	वापस "";
पूर्ण
#पूर्ण_अगर // #अन्यथा #अगर_घोषित CONFIG_SMP

/*
 * Dump out nocb grace-period kthपढ़ो state क्रम the specअगरied rcu_data
 * काष्ठाure.
 */
अटल व्योम show_rcu_nocb_gp_state(काष्ठा rcu_data *rdp)
अणु
	काष्ठा rcu_node *rnp = rdp->mynode;

	pr_info("nocb GP %d %c%c%c%c%c%c %c[%c%c] %c%c:%ld rnp %d:%d %lu %c CPU %d%s\n",
		rdp->cpu,
		"kK"[!!rdp->nocb_gp_kthपढ़ो],
		"lL"[raw_spin_is_locked(&rdp->nocb_gp_lock)],
		"dD"[!!rdp->nocb_defer_wakeup],
		"tT"[समयr_pending(&rdp->nocb_समयr)],
		"bB"[समयr_pending(&rdp->nocb_bypass_समयr)],
		"sS"[!!rdp->nocb_gp_sleep],
		".W"[sरुको_active(&rdp->nocb_gp_wq)],
		".W"[sरुको_active(&rnp->nocb_gp_wq[0])],
		".W"[sरुको_active(&rnp->nocb_gp_wq[1])],
		".B"[!!rdp->nocb_gp_bypass],
		".G"[!!rdp->nocb_gp_gp],
		(दीर्घ)rdp->nocb_gp_seq,
		rnp->grplo, rnp->grphi, READ_ONCE(rdp->nocb_gp_loops),
		rdp->nocb_gp_kthपढ़ो ? task_state_to_अक्षर(rdp->nocb_gp_kthपढ़ो) : '.',
		rdp->nocb_cb_kthपढ़ो ? (पूर्णांक)task_cpu(rdp->nocb_gp_kthपढ़ो) : -1,
		show_rcu_should_be_on_cpu(rdp->nocb_cb_kthपढ़ो));
पूर्ण

/* Dump out nocb kthपढ़ो state क्रम the specअगरied rcu_data काष्ठाure. */
अटल व्योम show_rcu_nocb_state(काष्ठा rcu_data *rdp)
अणु
	अक्षर bufw[20];
	अक्षर bufr[20];
	काष्ठा rcu_segcblist *rsclp = &rdp->cblist;
	bool waslocked;
	bool wasसमयr;
	bool wassleep;

	अगर (rdp->nocb_gp_rdp == rdp)
		show_rcu_nocb_gp_state(rdp);

	प्र_लिखो(bufw, "%ld", rsclp->gp_seq[RCU_WAIT_TAIL]);
	प्र_लिखो(bufr, "%ld", rsclp->gp_seq[RCU_NEXT_READY_TAIL]);
	pr_info("   CB %d^%d->%d %c%c%c%c%c%c F%ld L%ld C%d %c%c%s%c%s%c%c q%ld %c CPU %d%s\न",
		rdp->cpu, rdp->nocb_gp_rdp->cpu,
		rdp->nocb_next_cb_rdp ? rdp->nocb_next_cb_rdp->cpu : -1,
		"kK"[!!rdp->nocb_cb_kthपढ़ो],
		"bB"[raw_spin_is_locked(&rdp->nocb_bypass_lock)],
		"cC"[!!atomic_पढ़ो(&rdp->nocb_lock_contended)],
		"lL"[raw_spin_is_locked(&rdp->nocb_lock)],
		"sS"[!!rdp->nocb_cb_sleep],
		".W"[sरुको_active(&rdp->nocb_cb_wq)],
		jअगरfies - rdp->nocb_bypass_first,
		jअगरfies - rdp->nocb_nobypass_last,
		rdp->nocb_nobypass_count,
		".D"[rcu_segcblist_पढ़ोy_cbs(rsclp)],
		".W"[!rcu_segcblist_segempty(rsclp, RCU_WAIT_TAIL)],
		rcu_segcblist_segempty(rsclp, RCU_WAIT_TAIL) ? "" : bufw,
		".R"[!rcu_segcblist_segempty(rsclp, RCU_NEXT_READY_TAIL)],
		rcu_segcblist_segempty(rsclp, RCU_NEXT_READY_TAIL) ? "" : bufr,
		".N"[!rcu_segcblist_segempty(rsclp, RCU_NEXT_TAIL)],
		".B"[!!rcu_cblist_n_cbs(&rdp->nocb_bypass)],
		rcu_segcblist_n_cbs(&rdp->cblist),
		rdp->nocb_cb_kthपढ़ो ? task_state_to_अक्षर(rdp->nocb_cb_kthपढ़ो) : '.',
		rdp->nocb_cb_kthपढ़ो ? (पूर्णांक)task_cpu(rdp->nocb_gp_kthपढ़ो) : -1,
		show_rcu_should_be_on_cpu(rdp->nocb_cb_kthपढ़ो));

	/* It is OK क्रम GP kthपढ़ोs to have GP state. */
	अगर (rdp->nocb_gp_rdp == rdp)
		वापस;

	waslocked = raw_spin_is_locked(&rdp->nocb_gp_lock);
	wasसमयr = समयr_pending(&rdp->nocb_bypass_समयr);
	wassleep = sरुको_active(&rdp->nocb_gp_wq);
	अगर (!rdp->nocb_gp_sleep && !waslocked && !wasसमयr && !wassleep)
		वापस;  /* Nothing untowards. */

	pr_info("   nocb GP activity on CB-only CPU!!! %c%c%c%c %c\n",
		"lL"[waslocked],
		"dD"[!!rdp->nocb_defer_wakeup],
		"tT"[wasसमयr],
		"sS"[!!rdp->nocb_gp_sleep],
		".W"[wassleep]);
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_RCU_NOCB_CPU */

/* No ->nocb_lock to acquire.  */
अटल व्योम rcu_nocb_lock(काष्ठा rcu_data *rdp)
अणु
पूर्ण

/* No ->nocb_lock to release.  */
अटल व्योम rcu_nocb_unlock(काष्ठा rcu_data *rdp)
अणु
पूर्ण

/* No ->nocb_lock to release.  */
अटल व्योम rcu_nocb_unlock_irqrestore(काष्ठा rcu_data *rdp,
				       अचिन्हित दीर्घ flags)
अणु
	local_irq_restore(flags);
पूर्ण

/* Lockdep check that ->cblist may be safely accessed. */
अटल व्योम rcu_lockdep_निश्चित_cblist_रक्षित(काष्ठा rcu_data *rdp)
अणु
	lockdep_निश्चित_irqs_disabled();
पूर्ण

अटल व्योम rcu_nocb_gp_cleanup(काष्ठा sरुको_queue_head *sq)
अणु
पूर्ण

अटल काष्ठा sरुको_queue_head *rcu_nocb_gp_get(काष्ठा rcu_node *rnp)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम rcu_init_one_nocb(काष्ठा rcu_node *rnp)
अणु
पूर्ण

अटल bool rcu_nocb_flush_bypass(काष्ठा rcu_data *rdp, काष्ठा rcu_head *rhp,
				  अचिन्हित दीर्घ j)
अणु
	वापस true;
पूर्ण

अटल bool rcu_nocb_try_bypass(काष्ठा rcu_data *rdp, काष्ठा rcu_head *rhp,
				bool *was_allकरोne, अचिन्हित दीर्घ flags)
अणु
	वापस false;
पूर्ण

अटल व्योम __call_rcu_nocb_wake(काष्ठा rcu_data *rdp, bool was_empty,
				 अचिन्हित दीर्घ flags)
अणु
	WARN_ON_ONCE(1);  /* Should be dead code! */
पूर्ण

अटल व्योम __init rcu_boot_init_nocb_percpu_data(काष्ठा rcu_data *rdp)
अणु
पूर्ण

अटल पूर्णांक rcu_nocb_need_deferred_wakeup(काष्ठा rcu_data *rdp)
अणु
	वापस false;
पूर्ण

अटल bool करो_nocb_deferred_wakeup(काष्ठा rcu_data *rdp)
अणु
	वापस false;
पूर्ण

अटल व्योम rcu_spawn_cpu_nocb_kthपढ़ो(पूर्णांक cpu)
अणु
पूर्ण

अटल व्योम __init rcu_spawn_nocb_kthपढ़ोs(व्योम)
अणु
पूर्ण

अटल व्योम show_rcu_nocb_state(काष्ठा rcu_data *rdp)
अणु
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_NOCB_CPU */

/*
 * Is this CPU a NO_HZ_FULL CPU that should ignore RCU so that the
 * grace-period kthपढ़ो will करो क्रमce_quiescent_state() processing?
 * The idea is to aव्योम waking up RCU core processing on such a
 * CPU unless the grace period has extended क्रम too दीर्घ.
 *
 * This code relies on the fact that all NO_HZ_FULL CPUs are also
 * CONFIG_RCU_NOCB_CPU CPUs.
 */
अटल bool rcu_nohz_full_cpu(व्योम)
अणु
#अगर_घोषित CONFIG_NO_HZ_FULL
	अगर (tick_nohz_full_cpu(smp_processor_id()) &&
	    (!rcu_gp_in_progress() ||
	     समय_beक्रमe(jअगरfies, READ_ONCE(rcu_state.gp_start) + HZ)))
		वापस true;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_NO_HZ_FULL */
	वापस false;
पूर्ण

/*
 * Bind the RCU grace-period kthपढ़ोs to the housekeeping CPU.
 */
अटल व्योम rcu_bind_gp_kthपढ़ो(व्योम)
अणु
	अगर (!tick_nohz_full_enabled())
		वापस;
	housekeeping_affine(current, HK_FLAG_RCU);
पूर्ण

/* Record the current task on dyntick-idle entry. */
अटल व्योम noinstr rcu_dynticks_task_enter(व्योम)
अणु
#अगर defined(CONFIG_TASKS_RCU) && defined(CONFIG_NO_HZ_FULL)
	WRITE_ONCE(current->rcu_tasks_idle_cpu, smp_processor_id());
#पूर्ण_अगर /* #अगर defined(CONFIG_TASKS_RCU) && defined(CONFIG_NO_HZ_FULL) */
पूर्ण

/* Record no current task on dyntick-idle निकास. */
अटल व्योम noinstr rcu_dynticks_task_निकास(व्योम)
अणु
#अगर defined(CONFIG_TASKS_RCU) && defined(CONFIG_NO_HZ_FULL)
	WRITE_ONCE(current->rcu_tasks_idle_cpu, -1);
#पूर्ण_अगर /* #अगर defined(CONFIG_TASKS_RCU) && defined(CONFIG_NO_HZ_FULL) */
पूर्ण

/* Turn on heavyweight RCU tasks trace पढ़ोers on idle/user entry. */
अटल व्योम rcu_dynticks_task_trace_enter(व्योम)
अणु
#अगर_घोषित CONFIG_TASKS_RCU_TRACE
	अगर (IS_ENABLED(CONFIG_TASKS_TRACE_RCU_READ_MB))
		current->trc_पढ़ोer_special.b.need_mb = true;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RCU_TRACE */
पूर्ण

/* Turn off heavyweight RCU tasks trace पढ़ोers on idle/user निकास. */
अटल व्योम rcu_dynticks_task_trace_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_TASKS_RCU_TRACE
	अगर (IS_ENABLED(CONFIG_TASKS_TRACE_RCU_READ_MB))
		current->trc_पढ़ोer_special.b.need_mb = false;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RCU_TRACE */
पूर्ण
