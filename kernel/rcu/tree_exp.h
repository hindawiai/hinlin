<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * RCU expedited grace periods
 *
 * Copyright IBM Corporation, 2016
 *
 * Authors: Paul E. McKenney <paulmck@linux.ibm.com>
 */

#समावेश <linux/lockdep.h>

अटल व्योम rcu_exp_handler(व्योम *unused);
अटल पूर्णांक rcu_prपूर्णांक_task_exp_stall(काष्ठा rcu_node *rnp);

/*
 * Record the start of an expedited grace period.
 */
अटल व्योम rcu_exp_gp_seq_start(व्योम)
अणु
	rcu_seq_start(&rcu_state.expedited_sequence);
पूर्ण

/*
 * Return the value that the expedited-grace-period counter will have
 * at the end of the current grace period.
 */
अटल __maybe_unused अचिन्हित दीर्घ rcu_exp_gp_seq_endval(व्योम)
अणु
	वापस rcu_seq_endval(&rcu_state.expedited_sequence);
पूर्ण

/*
 * Record the end of an expedited grace period.
 */
अटल व्योम rcu_exp_gp_seq_end(व्योम)
अणु
	rcu_seq_end(&rcu_state.expedited_sequence);
	smp_mb(); /* Ensure that consecutive grace periods serialize. */
पूर्ण

/*
 * Take a snapshot of the expedited-grace-period counter, which is the
 * earliest value that will indicate that a full grace period has
 * elapsed since the current समय.
 */
अटल अचिन्हित दीर्घ rcu_exp_gp_seq_snap(व्योम)
अणु
	अचिन्हित दीर्घ s;

	smp_mb(); /* Caller's modअगरications seen first by other CPUs. */
	s = rcu_seq_snap(&rcu_state.expedited_sequence);
	trace_rcu_exp_grace_period(rcu_state.name, s, TPS("snap"));
	वापस s;
पूर्ण

/*
 * Given a counter snapshot from rcu_exp_gp_seq_snap(), वापस true
 * अगर a full expedited grace period has elapsed since that snapshot
 * was taken.
 */
अटल bool rcu_exp_gp_seq_करोne(अचिन्हित दीर्घ s)
अणु
	वापस rcu_seq_करोne(&rcu_state.expedited_sequence, s);
पूर्ण

/*
 * Reset the ->expmaskinit values in the rcu_node tree to reflect any
 * recent CPU-online activity.  Note that these masks are not cleared
 * when CPUs go offline, so they reflect the जोड़ of all CPUs that have
 * ever been online.  This means that this function normally takes its
 * no-work-to-करो fastpath.
 */
अटल व्योम sync_exp_reset_tree_hotplug(व्योम)
अणु
	bool करोne;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ oldmask;
	पूर्णांक ncpus = smp_load_acquire(&rcu_state.ncpus); /* Order vs. locking. */
	काष्ठा rcu_node *rnp;
	काष्ठा rcu_node *rnp_up;

	/* If no new CPUs onlined since last समय, nothing to करो. */
	अगर (likely(ncpus == rcu_state.ncpus_snap))
		वापस;
	rcu_state.ncpus_snap = ncpus;

	/*
	 * Each pass through the following loop propagates newly onlined
	 * CPUs क्रम the current rcu_node काष्ठाure up the rcu_node tree.
	 */
	rcu_क्रम_each_leaf_node(rnp) अणु
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		अगर (rnp->expmaskinit == rnp->expmaskinitnext) अणु
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
			जारी;  /* No new CPUs, nothing to करो. */
		पूर्ण

		/* Update this node's mask, track old value क्रम propagation. */
		oldmask = rnp->expmaskinit;
		rnp->expmaskinit = rnp->expmaskinitnext;
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);

		/* If was alपढ़ोy nonzero, nothing to propagate. */
		अगर (oldmask)
			जारी;

		/* Propagate the new CPU up the tree. */
		mask = rnp->grpmask;
		rnp_up = rnp->parent;
		करोne = false;
		जबतक (rnp_up) अणु
			raw_spin_lock_irqsave_rcu_node(rnp_up, flags);
			अगर (rnp_up->expmaskinit)
				करोne = true;
			rnp_up->expmaskinit |= mask;
			raw_spin_unlock_irqrestore_rcu_node(rnp_up, flags);
			अगर (करोne)
				अवरोध;
			mask = rnp_up->grpmask;
			rnp_up = rnp_up->parent;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Reset the ->expmask values in the rcu_node tree in preparation क्रम
 * a new expedited grace period.
 */
अटल व्योम __maybe_unused sync_exp_reset_tree(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_node *rnp;

	sync_exp_reset_tree_hotplug();
	rcu_क्रम_each_node_bपढ़ोth_first(rnp) अणु
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		WARN_ON_ONCE(rnp->expmask);
		WRITE_ONCE(rnp->expmask, rnp->expmaskinit);
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	पूर्ण
पूर्ण

/*
 * Return non-zero अगर there is no RCU expedited grace period in progress
 * क्रम the specअगरied rcu_node काष्ठाure, in other words, अगर all CPUs and
 * tasks covered by the specअगरied rcu_node काष्ठाure have करोne their bit
 * क्रम the current expedited grace period.
 */
अटल bool sync_rcu_exp_करोne(काष्ठा rcu_node *rnp)
अणु
	raw_lockdep_निश्चित_held_rcu_node(rnp);
	वापस READ_ONCE(rnp->exp_tasks) == शून्य &&
	       READ_ONCE(rnp->expmask) == 0;
पूर्ण

/*
 * Like sync_rcu_exp_करोne(), but where the caller करोes not hold the
 * rcu_node's ->lock.
 */
अटल bool sync_rcu_exp_करोne_unlocked(काष्ठा rcu_node *rnp)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	ret = sync_rcu_exp_करोne(rnp);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);

	वापस ret;
पूर्ण


/*
 * Report the निकास from RCU पढ़ो-side critical section क्रम the last task
 * that queued itself during or beक्रमe the current expedited preemptible-RCU
 * grace period.  This event is reported either to the rcu_node काष्ठाure on
 * which the task was queued or to one of that rcu_node काष्ठाure's ancestors,
 * recursively up the tree.  (Calm करोwn, calm करोwn, we करो the recursion
 * iteratively!)
 */
अटल व्योम __rcu_report_exp_rnp(काष्ठा rcu_node *rnp,
				 bool wake, अचिन्हित दीर्घ flags)
	__releases(rnp->lock)
अणु
	अचिन्हित दीर्घ mask;

	raw_lockdep_निश्चित_held_rcu_node(rnp);
	क्रम (;;) अणु
		अगर (!sync_rcu_exp_करोne(rnp)) अणु
			अगर (!rnp->expmask)
				rcu_initiate_boost(rnp, flags);
			अन्यथा
				raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
			अवरोध;
		पूर्ण
		अगर (rnp->parent == शून्य) अणु
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
			अगर (wake) अणु
				smp_mb(); /* EGP करोne beक्रमe wake_up(). */
				swake_up_one(&rcu_state.expedited_wq);
			पूर्ण
			अवरोध;
		पूर्ण
		mask = rnp->grpmask;
		raw_spin_unlock_rcu_node(rnp); /* irqs reमुख्य disabled */
		rnp = rnp->parent;
		raw_spin_lock_rcu_node(rnp); /* irqs alपढ़ोy disabled */
		WARN_ON_ONCE(!(rnp->expmask & mask));
		WRITE_ONCE(rnp->expmask, rnp->expmask & ~mask);
	पूर्ण
पूर्ण

/*
 * Report expedited quiescent state क्रम specअगरied node.  This is a
 * lock-acquisition wrapper function क्रम __rcu_report_exp_rnp().
 */
अटल व्योम __maybe_unused rcu_report_exp_rnp(काष्ठा rcu_node *rnp, bool wake)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	__rcu_report_exp_rnp(rnp, wake, flags);
पूर्ण

/*
 * Report expedited quiescent state क्रम multiple CPUs, all covered by the
 * specअगरied leaf rcu_node काष्ठाure.
 */
अटल व्योम rcu_report_exp_cpu_mult(काष्ठा rcu_node *rnp,
				    अचिन्हित दीर्घ mask, bool wake)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp;

	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	अगर (!(rnp->expmask & mask)) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;
	पूर्ण
	WRITE_ONCE(rnp->expmask, rnp->expmask & ~mask);
	क्रम_each_leaf_node_cpu_mask(rnp, cpu, mask) अणु
		rdp = per_cpu_ptr(&rcu_data, cpu);
		अगर (!IS_ENABLED(CONFIG_NO_HZ_FULL) || !rdp->rcu_क्रमced_tick_exp)
			जारी;
		rdp->rcu_क्रमced_tick_exp = false;
		tick_dep_clear_cpu(cpu, TICK_DEP_BIT_RCU_EXP);
	पूर्ण
	__rcu_report_exp_rnp(rnp, wake, flags); /* Releases rnp->lock. */
पूर्ण

/*
 * Report expedited quiescent state क्रम specअगरied rcu_data (CPU).
 */
अटल व्योम rcu_report_exp_rdp(काष्ठा rcu_data *rdp)
अणु
	WRITE_ONCE(rdp->exp_deferred_qs, false);
	rcu_report_exp_cpu_mult(rdp->mynode, rdp->grpmask, true);
पूर्ण

/* Common code क्रम work-करोne checking. */
अटल bool sync_exp_work_करोne(अचिन्हित दीर्घ s)
अणु
	अगर (rcu_exp_gp_seq_करोne(s)) अणु
		trace_rcu_exp_grace_period(rcu_state.name, s, TPS("done"));
		smp_mb(); /* Ensure test happens beक्रमe caller kमुक्त(). */
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Funnel-lock acquisition क्रम expedited grace periods.  Returns true
 * अगर some other task completed an expedited grace period that this task
 * can piggy-back on, and with no mutex held.  Otherwise, वापसs false
 * with the mutex held, indicating that the caller must actually करो the
 * expedited grace period.
 */
अटल bool exp_funnel_lock(अचिन्हित दीर्घ s)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, raw_smp_processor_id());
	काष्ठा rcu_node *rnp = rdp->mynode;
	काष्ठा rcu_node *rnp_root = rcu_get_root();

	/* Low-contention fastpath. */
	अगर (ULONG_CMP_LT(READ_ONCE(rnp->exp_seq_rq), s) &&
	    (rnp == rnp_root ||
	     ULONG_CMP_LT(READ_ONCE(rnp_root->exp_seq_rq), s)) &&
	    mutex_trylock(&rcu_state.exp_mutex))
		जाओ fastpath;

	/*
	 * Each pass through the following loop works its way up
	 * the rcu_node tree, वापसing अगर others have करोne the work or
	 * otherwise falls through to acquire ->exp_mutex.  The mapping
	 * from CPU to rcu_node काष्ठाure can be inexact, as it is just
	 * promoting locality and is not strictly needed क्रम correctness.
	 */
	क्रम (; rnp != शून्य; rnp = rnp->parent) अणु
		अगर (sync_exp_work_करोne(s))
			वापस true;

		/* Work not करोne, either रुको here or go up. */
		spin_lock(&rnp->exp_lock);
		अगर (ULONG_CMP_GE(rnp->exp_seq_rq, s)) अणु

			/* Someone अन्यथा करोing GP, so रुको क्रम them. */
			spin_unlock(&rnp->exp_lock);
			trace_rcu_exp_funnel_lock(rcu_state.name, rnp->level,
						  rnp->grplo, rnp->grphi,
						  TPS("wait"));
			रुको_event(rnp->exp_wq[rcu_seq_ctr(s) & 0x3],
				   sync_exp_work_करोne(s));
			वापस true;
		पूर्ण
		WRITE_ONCE(rnp->exp_seq_rq, s); /* Followers can रुको on us. */
		spin_unlock(&rnp->exp_lock);
		trace_rcu_exp_funnel_lock(rcu_state.name, rnp->level,
					  rnp->grplo, rnp->grphi, TPS("nxtlvl"));
	पूर्ण
	mutex_lock(&rcu_state.exp_mutex);
fastpath:
	अगर (sync_exp_work_करोne(s)) अणु
		mutex_unlock(&rcu_state.exp_mutex);
		वापस true;
	पूर्ण
	rcu_exp_gp_seq_start();
	trace_rcu_exp_grace_period(rcu_state.name, s, TPS("start"));
	वापस false;
पूर्ण

/*
 * Select the CPUs within the specअगरied rcu_node that the upcoming
 * expedited grace period needs to रुको क्रम.
 */
अटल व्योम sync_rcu_exp_select_node_cpus(काष्ठा work_काष्ठा *wp)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask_ofl_test;
	अचिन्हित दीर्घ mask_ofl_ipi;
	पूर्णांक ret;
	काष्ठा rcu_exp_work *rewp =
		container_of(wp, काष्ठा rcu_exp_work, rew_work);
	काष्ठा rcu_node *rnp = container_of(rewp, काष्ठा rcu_node, rew);

	raw_spin_lock_irqsave_rcu_node(rnp, flags);

	/* Each pass checks a CPU क्रम identity, offline, and idle. */
	mask_ofl_test = 0;
	क्रम_each_leaf_node_cpu_mask(rnp, cpu, rnp->expmask) अणु
		काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
		अचिन्हित दीर्घ mask = rdp->grpmask;
		पूर्णांक snap;

		अगर (raw_smp_processor_id() == cpu ||
		    !(rnp->qsmaskinitnext & mask)) अणु
			mask_ofl_test |= mask;
		पूर्ण अन्यथा अणु
			snap = rcu_dynticks_snap(rdp);
			अगर (rcu_dynticks_in_eqs(snap))
				mask_ofl_test |= mask;
			अन्यथा
				rdp->exp_dynticks_snap = snap;
		पूर्ण
	पूर्ण
	mask_ofl_ipi = rnp->expmask & ~mask_ofl_test;

	/*
	 * Need to रुको क्रम any blocked tasks as well.	Note that
	 * additional blocking tasks will also block the expedited GP
	 * until such समय as the ->expmask bits are cleared.
	 */
	अगर (rcu_preempt_has_tasks(rnp))
		WRITE_ONCE(rnp->exp_tasks, rnp->blkd_tasks.next);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);

	/* IPI the reमुख्यing CPUs क्रम expedited quiescent state. */
	क्रम_each_leaf_node_cpu_mask(rnp, cpu, mask_ofl_ipi) अणु
		काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
		अचिन्हित दीर्घ mask = rdp->grpmask;

retry_ipi:
		अगर (rcu_dynticks_in_eqs_since(rdp, rdp->exp_dynticks_snap)) अणु
			mask_ofl_test |= mask;
			जारी;
		पूर्ण
		अगर (get_cpu() == cpu) अणु
			put_cpu();
			जारी;
		पूर्ण
		ret = smp_call_function_single(cpu, rcu_exp_handler, शून्य, 0);
		put_cpu();
		/* The CPU will report the QS in response to the IPI. */
		अगर (!ret)
			जारी;

		/* Failed, raced with CPU hotplug operation. */
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		अगर ((rnp->qsmaskinitnext & mask) &&
		    (rnp->expmask & mask)) अणु
			/* Online, so delay क्रम a bit and try again. */
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
			trace_rcu_exp_grace_period(rcu_state.name, rcu_exp_gp_seq_endval(), TPS("selectofl"));
			schedule_समयout_idle(1);
			जाओ retry_ipi;
		पूर्ण
		/* CPU really is offline, so we must report its QS. */
		अगर (rnp->expmask & mask)
			mask_ofl_test |= mask;
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	पूर्ण
	/* Report quiescent states क्रम those that went offline. */
	अगर (mask_ofl_test)
		rcu_report_exp_cpu_mult(rnp, mask_ofl_test, false);
पूर्ण

/*
 * Select the nodes that the upcoming expedited grace period needs
 * to रुको क्रम.
 */
अटल व्योम sync_rcu_exp_select_cpus(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा rcu_node *rnp;

	trace_rcu_exp_grace_period(rcu_state.name, rcu_exp_gp_seq_endval(), TPS("reset"));
	sync_exp_reset_tree();
	trace_rcu_exp_grace_period(rcu_state.name, rcu_exp_gp_seq_endval(), TPS("select"));

	/* Schedule work क्रम each leaf rcu_node काष्ठाure. */
	rcu_क्रम_each_leaf_node(rnp) अणु
		rnp->exp_need_flush = false;
		अगर (!READ_ONCE(rnp->expmask))
			जारी; /* Aव्योम early boot non-existent wq. */
		अगर (!READ_ONCE(rcu_par_gp_wq) ||
		    rcu_scheduler_active != RCU_SCHEDULER_RUNNING ||
		    rcu_is_last_leaf_node(rnp)) अणु
			/* No workqueues yet or last leaf, करो direct call. */
			sync_rcu_exp_select_node_cpus(&rnp->rew.rew_work);
			जारी;
		पूर्ण
		INIT_WORK(&rnp->rew.rew_work, sync_rcu_exp_select_node_cpus);
		cpu = find_next_bit(&rnp->ffmask, BITS_PER_LONG, -1);
		/* If all offline, queue the work on an unbound CPU. */
		अगर (unlikely(cpu > rnp->grphi - rnp->grplo))
			cpu = WORK_CPU_UNBOUND;
		अन्यथा
			cpu += rnp->grplo;
		queue_work_on(cpu, rcu_par_gp_wq, &rnp->rew.rew_work);
		rnp->exp_need_flush = true;
	पूर्ण

	/* Wait क्रम workqueue jobs (अगर any) to complete. */
	rcu_क्रम_each_leaf_node(rnp)
		अगर (rnp->exp_need_flush)
			flush_work(&rnp->rew.rew_work);
पूर्ण

/*
 * Wait क्रम the expedited grace period to elapse, within समय limit.
 * If the समय limit is exceeded without the grace period elapsing,
 * वापस false, otherwise वापस true.
 */
अटल bool synchronize_rcu_expedited_रुको_once(दीर्घ tlimit)
अणु
	पूर्णांक t;
	काष्ठा rcu_node *rnp_root = rcu_get_root();

	t = sरुको_event_समयout_exclusive(rcu_state.expedited_wq,
					  sync_rcu_exp_करोne_unlocked(rnp_root),
					  tlimit);
	// Workqueues should not be संकेतed.
	अगर (t > 0 || sync_rcu_exp_करोne_unlocked(rnp_root))
		वापस true;
	WARN_ON(t < 0);  /* workqueues should not be संकेतed. */
	वापस false;
पूर्ण

/*
 * Wait क्रम the expedited grace period to elapse, issuing any needed
 * RCU CPU stall warnings aदीर्घ the way.
 */
अटल व्योम synchronize_rcu_expedited_रुको(व्योम)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ j;
	अचिन्हित दीर्घ jअगरfies_stall;
	अचिन्हित दीर्घ jअगरfies_start;
	अचिन्हित दीर्घ mask;
	पूर्णांक ndetected;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;
	काष्ठा rcu_node *rnp_root = rcu_get_root();

	trace_rcu_exp_grace_period(rcu_state.name, rcu_exp_gp_seq_endval(), TPS("startwait"));
	jअगरfies_stall = rcu_jअगरfies_till_stall_check();
	jअगरfies_start = jअगरfies;
	अगर (tick_nohz_full_enabled() && rcu_inkernel_boot_has_ended()) अणु
		अगर (synchronize_rcu_expedited_रुको_once(1))
			वापस;
		rcu_क्रम_each_leaf_node(rnp) अणु
			क्रम_each_leaf_node_cpu_mask(rnp, cpu, rnp->expmask) अणु
				rdp = per_cpu_ptr(&rcu_data, cpu);
				अगर (rdp->rcu_क्रमced_tick_exp)
					जारी;
				rdp->rcu_क्रमced_tick_exp = true;
				tick_dep_set_cpu(cpu, TICK_DEP_BIT_RCU_EXP);
			पूर्ण
		पूर्ण
		j = READ_ONCE(jअगरfies_till_first_fqs);
		अगर (synchronize_rcu_expedited_रुको_once(j + HZ))
			वापस;
		WARN_ON_ONCE(IS_ENABLED(CONFIG_PREEMPT_RT));
	पूर्ण

	क्रम (;;) अणु
		अगर (synchronize_rcu_expedited_रुको_once(jअगरfies_stall))
			वापस;
		अगर (rcu_stall_is_suppressed())
			जारी;
		panic_on_rcu_stall();
		trace_rcu_stall_warning(rcu_state.name, TPS("ExpeditedStall"));
		pr_err("INFO: %s detected expedited stalls on CPUs/tasks: {",
		       rcu_state.name);
		ndetected = 0;
		rcu_क्रम_each_leaf_node(rnp) अणु
			ndetected += rcu_prपूर्णांक_task_exp_stall(rnp);
			क्रम_each_leaf_node_possible_cpu(rnp, cpu) अणु
				काष्ठा rcu_data *rdp;

				mask = leaf_node_cpu_bit(rnp, cpu);
				अगर (!(READ_ONCE(rnp->expmask) & mask))
					जारी;
				ndetected++;
				rdp = per_cpu_ptr(&rcu_data, cpu);
				pr_cont(" %d-%c%c%c", cpu,
					"O."[!!cpu_online(cpu)],
					"o."[!!(rdp->grpmask & rnp->expmaskinit)],
					"N."[!!(rdp->grpmask & rnp->expmaskinitnext)]);
			पूर्ण
		पूर्ण
		pr_cont(" } %lu jiffies s: %lu root: %#lx/%c\n",
			jअगरfies - jअगरfies_start, rcu_state.expedited_sequence,
			data_race(rnp_root->expmask),
			".T"[!!data_race(rnp_root->exp_tasks)]);
		अगर (ndetected) अणु
			pr_err("blocking rcu_node structures (internal RCU debug):");
			rcu_क्रम_each_node_bपढ़ोth_first(rnp) अणु
				अगर (rnp == rnp_root)
					जारी; /* prपूर्णांकed unconditionally */
				अगर (sync_rcu_exp_करोne_unlocked(rnp))
					जारी;
				pr_cont(" l=%u:%d-%d:%#lx/%c",
					rnp->level, rnp->grplo, rnp->grphi,
					data_race(rnp->expmask),
					".T"[!!data_race(rnp->exp_tasks)]);
			पूर्ण
			pr_cont("\n");
		पूर्ण
		rcu_क्रम_each_leaf_node(rnp) अणु
			क्रम_each_leaf_node_possible_cpu(rnp, cpu) अणु
				mask = leaf_node_cpu_bit(rnp, cpu);
				अगर (!(READ_ONCE(rnp->expmask) & mask))
					जारी;
				dump_cpu_task(cpu);
			पूर्ण
		पूर्ण
		jअगरfies_stall = 3 * rcu_jअगरfies_till_stall_check() + 3;
	पूर्ण
पूर्ण

/*
 * Wait क्रम the current expedited grace period to complete, and then
 * wake up everyone who piggybacked on the just-completed expedited
 * grace period.  Also update all the ->exp_seq_rq counters as needed
 * in order to aव्योम counter-wrap problems.
 */
अटल व्योम rcu_exp_रुको_wake(अचिन्हित दीर्घ s)
अणु
	काष्ठा rcu_node *rnp;

	synchronize_rcu_expedited_रुको();

	// Switch over to wakeup mode, allowing the next GP to proceed.
	// End the previous grace period only after acquiring the mutex
	// to ensure that only one GP runs concurrently with wakeups.
	mutex_lock(&rcu_state.exp_wake_mutex);
	rcu_exp_gp_seq_end();
	trace_rcu_exp_grace_period(rcu_state.name, s, TPS("end"));

	rcu_क्रम_each_node_bपढ़ोth_first(rnp) अणु
		अगर (ULONG_CMP_LT(READ_ONCE(rnp->exp_seq_rq), s)) अणु
			spin_lock(&rnp->exp_lock);
			/* Recheck, aव्योम hang in हाल someone just arrived. */
			अगर (ULONG_CMP_LT(rnp->exp_seq_rq, s))
				WRITE_ONCE(rnp->exp_seq_rq, s);
			spin_unlock(&rnp->exp_lock);
		पूर्ण
		smp_mb(); /* All above changes beक्रमe wakeup. */
		wake_up_all(&rnp->exp_wq[rcu_seq_ctr(s) & 0x3]);
	पूर्ण
	trace_rcu_exp_grace_period(rcu_state.name, s, TPS("endwake"));
	mutex_unlock(&rcu_state.exp_wake_mutex);
पूर्ण

/*
 * Common code to drive an expedited grace period क्रमward, used by
 * workqueues and mid-boot-समय tasks.
 */
अटल व्योम rcu_exp_sel_रुको_wake(अचिन्हित दीर्घ s)
अणु
	/* Initialize the rcu_node tree in preparation क्रम the रुको. */
	sync_rcu_exp_select_cpus();

	/* Wait and clean up, including waking everyone. */
	rcu_exp_रुको_wake(s);
पूर्ण

/*
 * Work-queue handler to drive an expedited grace period क्रमward.
 */
अटल व्योम रुको_rcu_exp_gp(काष्ठा work_काष्ठा *wp)
अणु
	काष्ठा rcu_exp_work *rewp;

	rewp = container_of(wp, काष्ठा rcu_exp_work, rew_work);
	rcu_exp_sel_रुको_wake(rewp->rew_s);
पूर्ण

#अगर_घोषित CONFIG_PREEMPT_RCU

/*
 * Remote handler क्रम smp_call_function_single().  If there is an
 * RCU पढ़ो-side critical section in effect, request that the
 * next rcu_पढ़ो_unlock() record the quiescent state up the
 * ->expmask fields in the rcu_node tree.  Otherwise, immediately
 * report the quiescent state.
 */
अटल व्योम rcu_exp_handler(व्योम *unused)
अणु
	पूर्णांक depth = rcu_preempt_depth();
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp = rdp->mynode;
	काष्ठा task_काष्ठा *t = current;

	/*
	 * First, the common हाल of not being in an RCU पढ़ो-side
	 * critical section.  If also enabled or idle, immediately
	 * report the quiescent state, otherwise defer.
	 */
	अगर (!depth) अणु
		अगर (!(preempt_count() & (PREEMPT_MASK | SOFTIRQ_MASK)) ||
		    rcu_dynticks_curr_cpu_in_eqs()) अणु
			rcu_report_exp_rdp(rdp);
		पूर्ण अन्यथा अणु
			rdp->exp_deferred_qs = true;
			set_tsk_need_resched(t);
			set_preempt_need_resched();
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Second, the less-common हाल of being in an RCU पढ़ो-side
	 * critical section.  In this हाल we can count on a future
	 * rcu_पढ़ो_unlock().  However, this rcu_पढ़ो_unlock() might
	 * execute on some other CPU, but in that हाल there will be
	 * a future context चयन.  Either way, अगर the expedited
	 * grace period is still रुकोing on this CPU, set ->deferred_qs
	 * so that the eventual quiescent state will be reported.
	 * Note that there is a large group of race conditions that
	 * can have caused this quiescent state to alपढ़ोy have been
	 * reported, so we really करो need to check ->expmask.
	 */
	अगर (depth > 0) अणु
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		अगर (rnp->expmask & rdp->grpmask) अणु
			rdp->exp_deferred_qs = true;
			t->rcu_पढ़ो_unlock_special.b.exp_hपूर्णांक = true;
		पूर्ण
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;
	पूर्ण

	// Finally, negative nesting depth should not happen.
	WARN_ON_ONCE(1);
पूर्ण

/* PREEMPTION=y, so no PREEMPTION=n expedited grace period to clean up after. */
अटल व्योम sync_sched_exp_online_cleanup(पूर्णांक cpu)
अणु
पूर्ण

/*
 * Scan the current list of tasks blocked within RCU पढ़ो-side critical
 * sections, prपूर्णांकing out the tid of each that is blocking the current
 * expedited grace period.
 */
अटल पूर्णांक rcu_prपूर्णांक_task_exp_stall(काष्ठा rcu_node *rnp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ndetected = 0;
	काष्ठा task_काष्ठा *t;

	अगर (!READ_ONCE(rnp->exp_tasks))
		वापस 0;
	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	t = list_entry(rnp->exp_tasks->prev,
		       काष्ठा task_काष्ठा, rcu_node_entry);
	list_क्रम_each_entry_जारी(t, &rnp->blkd_tasks, rcu_node_entry) अणु
		pr_cont(" P%d", t->pid);
		ndetected++;
	पूर्ण
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	वापस ndetected;
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_PREEMPT_RCU */

/* Request an expedited quiescent state. */
अटल व्योम rcu_exp_need_qs(व्योम)
अणु
	__this_cpu_ग_लिखो(rcu_data.cpu_no_qs.b.exp, true);
	/* Store .exp beक्रमe .rcu_urgent_qs. */
	smp_store_release(this_cpu_ptr(&rcu_data.rcu_urgent_qs), true);
	set_tsk_need_resched(current);
	set_preempt_need_resched();
पूर्ण

/* Invoked on each online non-idle CPU क्रम expedited quiescent state. */
अटल व्योम rcu_exp_handler(व्योम *unused)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp = rdp->mynode;

	अगर (!(READ_ONCE(rnp->expmask) & rdp->grpmask) ||
	    __this_cpu_पढ़ो(rcu_data.cpu_no_qs.b.exp))
		वापस;
	अगर (rcu_is_cpu_rrupt_from_idle()) अणु
		rcu_report_exp_rdp(this_cpu_ptr(&rcu_data));
		वापस;
	पूर्ण
	rcu_exp_need_qs();
पूर्ण

/* Send IPI क्रम expedited cleanup अगर needed at end of CPU-hotplug operation. */
अटल व्योम sync_sched_exp_online_cleanup(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक my_cpu;
	काष्ठा rcu_data *rdp;
	पूर्णांक ret;
	काष्ठा rcu_node *rnp;

	rdp = per_cpu_ptr(&rcu_data, cpu);
	rnp = rdp->mynode;
	my_cpu = get_cpu();
	/* Quiescent state either not needed or alपढ़ोy requested, leave. */
	अगर (!(READ_ONCE(rnp->expmask) & rdp->grpmask) ||
	    __this_cpu_पढ़ो(rcu_data.cpu_no_qs.b.exp)) अणु
		put_cpu();
		वापस;
	पूर्ण
	/* Quiescent state needed on current CPU, so set it up locally. */
	अगर (my_cpu == cpu) अणु
		local_irq_save(flags);
		rcu_exp_need_qs();
		local_irq_restore(flags);
		put_cpu();
		वापस;
	पूर्ण
	/* Quiescent state needed on some other CPU, send IPI. */
	ret = smp_call_function_single(cpu, rcu_exp_handler, शून्य, 0);
	put_cpu();
	WARN_ON_ONCE(ret);
पूर्ण

/*
 * Because preemptible RCU करोes not exist, we never have to check क्रम
 * tasks blocked within RCU पढ़ो-side critical sections that are
 * blocking the current expedited grace period.
 */
अटल पूर्णांक rcu_prपूर्णांक_task_exp_stall(काष्ठा rcu_node *rnp)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PREEMPT_RCU */

/**
 * synchronize_rcu_expedited - Brute-क्रमce RCU grace period
 *
 * Wait क्रम an RCU grace period, but expedite it.  The basic idea is to
 * IPI all non-idle non-nohz online CPUs.  The IPI handler checks whether
 * the CPU is in an RCU critical section, and अगर so, it sets a flag that
 * causes the outermost rcu_पढ़ो_unlock() to report the quiescent state
 * क्रम RCU-preempt or asks the scheduler क्रम help क्रम RCU-sched.  On the
 * other hand, अगर the CPU is not in an RCU पढ़ो-side critical section,
 * the IPI handler reports the quiescent state immediately.
 *
 * Although this is a great improvement over previous expedited
 * implementations, it is still unमित्रly to real-समय workloads, so is
 * thus not recommended क्रम any sort of common-हाल code.  In fact, अगर
 * you are using synchronize_rcu_expedited() in a loop, please reकाष्ठाure
 * your code to batch your updates, and then use a single synchronize_rcu()
 * instead.
 *
 * This has the same semantics as (but is more brutal than) synchronize_rcu().
 */
व्योम synchronize_rcu_expedited(व्योम)
अणु
	bool bootसमय = (rcu_scheduler_active == RCU_SCHEDULER_INIT);
	काष्ठा rcu_exp_work rew;
	काष्ठा rcu_node *rnp;
	अचिन्हित दीर्घ s;

	RCU_LOCKDEP_WARN(lock_is_held(&rcu_bh_lock_map) ||
			 lock_is_held(&rcu_lock_map) ||
			 lock_is_held(&rcu_sched_lock_map),
			 "Illegal synchronize_rcu_expedited() in RCU read-side critical section");

	/* Is the state is such that the call is a grace period? */
	अगर (rcu_blocking_is_gp())
		वापस;

	/* If expedited grace periods are prohibited, fall back to normal. */
	अगर (rcu_gp_is_normal()) अणु
		रुको_rcu_gp(call_rcu);
		वापस;
	पूर्ण

	/* Take a snapshot of the sequence number.  */
	s = rcu_exp_gp_seq_snap();
	अगर (exp_funnel_lock(s))
		वापस;  /* Someone अन्यथा did our work क्रम us. */

	/* Ensure that load happens beक्रमe action based on it. */
	अगर (unlikely(bootसमय)) अणु
		/* Direct call during scheduler init and early_initcalls(). */
		rcu_exp_sel_रुको_wake(s);
	पूर्ण अन्यथा अणु
		/* Marshall arguments & schedule the expedited grace period. */
		rew.rew_s = s;
		INIT_WORK_ONSTACK(&rew.rew_work, रुको_rcu_exp_gp);
		queue_work(rcu_gp_wq, &rew.rew_work);
	पूर्ण

	/* Wait क्रम expedited grace period to complete. */
	rnp = rcu_get_root();
	रुको_event(rnp->exp_wq[rcu_seq_ctr(s) & 0x3],
		   sync_exp_work_करोne(s));
	smp_mb(); /* Workqueue actions happen beक्रमe वापस. */

	/* Let the next expedited grace period start. */
	mutex_unlock(&rcu_state.exp_mutex);

	अगर (likely(!bootसमय))
		destroy_work_on_stack(&rew.rew_work);
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_rcu_expedited);
