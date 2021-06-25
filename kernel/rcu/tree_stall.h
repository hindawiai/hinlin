<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * RCU CPU stall warnings क्रम normal RCU grace periods
 *
 * Copyright IBM Corporation, 2019
 *
 * Author: Paul E. McKenney <paulmck@linux.ibm.com>
 */

//////////////////////////////////////////////////////////////////////////////
//
// Controlling CPU stall warnings, including delay calculation.

/* panic() on RCU Stall sysctl. */
पूर्णांक sysctl_panic_on_rcu_stall __पढ़ो_mostly;
पूर्णांक sysctl_max_rcu_stall_to_panic __पढ़ो_mostly;

#अगर_घोषित CONFIG_PROVE_RCU
#घोषणा RCU_STALL_DELAY_DELTA		(5 * HZ)
#अन्यथा
#घोषणा RCU_STALL_DELAY_DELTA		0
#पूर्ण_अगर
#घोषणा RCU_STALL_MIGHT_DIV		8
#घोषणा RCU_STALL_MIGHT_MIN		(2 * HZ)

/* Limit-check stall समयouts specअगरied at bootसमय and runसमय. */
पूर्णांक rcu_jअगरfies_till_stall_check(व्योम)
अणु
	पूर्णांक till_stall_check = READ_ONCE(rcu_cpu_stall_समयout);

	/*
	 * Limit check must be consistent with the Kconfig limits
	 * क्रम CONFIG_RCU_CPU_STALL_TIMEOUT.
	 */
	अगर (till_stall_check < 3) अणु
		WRITE_ONCE(rcu_cpu_stall_समयout, 3);
		till_stall_check = 3;
	पूर्ण अन्यथा अगर (till_stall_check > 300) अणु
		WRITE_ONCE(rcu_cpu_stall_समयout, 300);
		till_stall_check = 300;
	पूर्ण
	वापस till_stall_check * HZ + RCU_STALL_DELAY_DELTA;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_jअगरfies_till_stall_check);

/**
 * rcu_gp_might_be_stalled - Is it likely that the grace period is stalled?
 *
 * Returns @true अगर the current grace period is sufficiently old that
 * it is reasonable to assume that it might be stalled.  This can be
 * useful when deciding whether to allocate memory to enable RCU-mediated
 * मुक्तing on the one hand or just invoking synchronize_rcu() on the other.
 * The latter is preferable when the grace period is stalled.
 *
 * Note that sampling of the .gp_start and .gp_seq fields must be करोne
 * carefully to aव्योम false positives at the beginnings and ends of
 * grace periods.
 */
bool rcu_gp_might_be_stalled(व्योम)
अणु
	अचिन्हित दीर्घ d = rcu_jअगरfies_till_stall_check() / RCU_STALL_MIGHT_DIV;
	अचिन्हित दीर्घ j = jअगरfies;

	अगर (d < RCU_STALL_MIGHT_MIN)
		d = RCU_STALL_MIGHT_MIN;
	smp_mb(); // jअगरfies beक्रमe .gp_seq to aव्योम false positives.
	अगर (!rcu_gp_in_progress())
		वापस false;
	// Long delays at this poपूर्णांक aव्योमs false positive, but a delay
	// of अच_दीर्घ_उच्च/4 jअगरfies व्योमs your no-false-positive warranty.
	smp_mb(); // .gp_seq beक्रमe second .gp_start
	// And ditto here.
	वापस !समय_beक्रमe(j, READ_ONCE(rcu_state.gp_start) + d);
पूर्ण

/* Don't करो RCU CPU stall warnings during दीर्घ sysrq prपूर्णांकouts. */
व्योम rcu_sysrq_start(व्योम)
अणु
	अगर (!rcu_cpu_stall_suppress)
		rcu_cpu_stall_suppress = 2;
पूर्ण

व्योम rcu_sysrq_end(व्योम)
अणु
	अगर (rcu_cpu_stall_suppress == 2)
		rcu_cpu_stall_suppress = 0;
पूर्ण

/* Don't prपूर्णांक RCU CPU stall warnings during a kernel panic. */
अटल पूर्णांक rcu_panic(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ ev, व्योम *ptr)
अणु
	rcu_cpu_stall_suppress = 1;
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rcu_panic_block = अणु
	.notअगरier_call = rcu_panic,
पूर्ण;

अटल पूर्णांक __init check_cpu_stall_init(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &rcu_panic_block);
	वापस 0;
पूर्ण
early_initcall(check_cpu_stall_init);

/* If so specअगरied via sysctl, panic, yielding cleaner stall-warning output. */
अटल व्योम panic_on_rcu_stall(व्योम)
अणु
	अटल पूर्णांक cpu_stall;

	अगर (++cpu_stall < sysctl_max_rcu_stall_to_panic)
		वापस;

	अगर (sysctl_panic_on_rcu_stall)
		panic("RCU Stall\n");
पूर्ण

/**
 * rcu_cpu_stall_reset - prevent further stall warnings in current grace period
 *
 * Set the stall-warning समयout way off पूर्णांकo the future, thus preventing
 * any RCU CPU stall-warning messages from appearing in the current set of
 * RCU grace periods.
 *
 * The caller must disable hard irqs.
 */
व्योम rcu_cpu_stall_reset(व्योम)
अणु
	WRITE_ONCE(rcu_state.jअगरfies_stall, jअगरfies + अच_दीर्घ_उच्च / 2);
पूर्ण

//////////////////////////////////////////////////////////////////////////////
//
// Interaction with RCU grace periods

/* Start of new grace period, so record stall समय (and क्रमcing बार). */
अटल व्योम record_gp_stall_check_समय(व्योम)
अणु
	अचिन्हित दीर्घ j = jअगरfies;
	अचिन्हित दीर्घ j1;

	WRITE_ONCE(rcu_state.gp_start, j);
	j1 = rcu_jअगरfies_till_stall_check();
	smp_mb(); // ->gp_start beक्रमe ->jअगरfies_stall and caller's ->gp_seq.
	WRITE_ONCE(rcu_state.jअगरfies_stall, j + j1);
	rcu_state.jअगरfies_resched = j + j1 / 2;
	rcu_state.n_क्रमce_qs_gpstart = READ_ONCE(rcu_state.n_क्रमce_qs);
पूर्ण

/* Zero ->ticks_this_gp and snapshot the number of RCU softirq handlers. */
अटल व्योम zero_cpu_stall_ticks(काष्ठा rcu_data *rdp)
अणु
	rdp->ticks_this_gp = 0;
	rdp->softirq_snap = kstat_softirqs_cpu(RCU_SOFTIRQ, smp_processor_id());
	WRITE_ONCE(rdp->last_fqs_resched, jअगरfies);
पूर्ण

/*
 * If too much समय has passed in the current grace period, and अगर
 * so configured, go kick the relevant kthपढ़ोs.
 */
अटल व्योम rcu_stall_kick_kthपढ़ोs(व्योम)
अणु
	अचिन्हित दीर्घ j;

	अगर (!READ_ONCE(rcu_kick_kthपढ़ोs))
		वापस;
	j = READ_ONCE(rcu_state.jअगरfies_kick_kthपढ़ोs);
	अगर (समय_after(jअगरfies, j) && rcu_state.gp_kthपढ़ो &&
	    (rcu_gp_in_progress() || READ_ONCE(rcu_state.gp_flags))) अणु
		WARN_ONCE(1, "Kicking %s grace-period kthread\n",
			  rcu_state.name);
		rcu_ftrace_dump(DUMP_ALL);
		wake_up_process(rcu_state.gp_kthपढ़ो);
		WRITE_ONCE(rcu_state.jअगरfies_kick_kthपढ़ोs, j + HZ);
	पूर्ण
पूर्ण

/*
 * Handler क्रम the irq_work request posted about halfway पूर्णांकo the RCU CPU
 * stall समयout, and used to detect excessive irq disabling.  Set state
 * appropriately, but just complain अगर there is unexpected state on entry.
 */
अटल व्योम rcu_iw_handler(काष्ठा irq_work *iwp)
अणु
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;

	rdp = container_of(iwp, काष्ठा rcu_data, rcu_iw);
	rnp = rdp->mynode;
	raw_spin_lock_rcu_node(rnp);
	अगर (!WARN_ON_ONCE(!rdp->rcu_iw_pending)) अणु
		rdp->rcu_iw_gp_seq = rnp->gp_seq;
		rdp->rcu_iw_pending = false;
	पूर्ण
	raw_spin_unlock_rcu_node(rnp);
पूर्ण

//////////////////////////////////////////////////////////////////////////////
//
// Prपूर्णांकing RCU CPU stall warnings

#अगर_घोषित CONFIG_PREEMPT_RCU

/*
 * Dump detailed inक्रमmation क्रम all tasks blocking the current RCU
 * grace period on the specअगरied rcu_node काष्ठाure.
 */
अटल व्योम rcu_prपूर्णांक_detail_task_stall_rnp(काष्ठा rcu_node *rnp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा task_काष्ठा *t;

	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	अगर (!rcu_preempt_blocked_पढ़ोers_cgp(rnp)) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;
	पूर्ण
	t = list_entry(rnp->gp_tasks->prev,
		       काष्ठा task_काष्ठा, rcu_node_entry);
	list_क्रम_each_entry_जारी(t, &rnp->blkd_tasks, rcu_node_entry) अणु
		/*
		 * We could be prपूर्णांकing a lot जबतक holding a spinlock.
		 * Aव्योम triggering hard lockup.
		 */
		touch_nmi_watchकरोg();
		sched_show_task(t);
	पूर्ण
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
पूर्ण

// Communicate task state back to the RCU CPU stall warning request.
काष्ठा rcu_stall_chk_rdr अणु
	पूर्णांक nesting;
	जोड़ rcu_special rs;
	bool on_blkd_list;
पूर्ण;

/*
 * Report out the state of a not-running task that is stalling the
 * current RCU grace period.
 */
अटल bool check_slow_task(काष्ठा task_काष्ठा *t, व्योम *arg)
अणु
	काष्ठा rcu_stall_chk_rdr *rscrp = arg;

	अगर (task_curr(t))
		वापस false; // It is running, so decline to inspect it.
	rscrp->nesting = t->rcu_पढ़ो_lock_nesting;
	rscrp->rs = t->rcu_पढ़ो_unlock_special;
	rscrp->on_blkd_list = !list_empty(&t->rcu_node_entry);
	वापस true;
पूर्ण

/*
 * Scan the current list of tasks blocked within RCU पढ़ो-side critical
 * sections, prपूर्णांकing out the tid of each of the first few of them.
 */
अटल पूर्णांक rcu_prपूर्णांक_task_stall(काष्ठा rcu_node *rnp, अचिन्हित दीर्घ flags)
	__releases(rnp->lock)
अणु
	पूर्णांक i = 0;
	पूर्णांक ndetected = 0;
	काष्ठा rcu_stall_chk_rdr rscr;
	काष्ठा task_काष्ठा *t;
	काष्ठा task_काष्ठा *ts[8];

	lockdep_निश्चित_irqs_disabled();
	अगर (!rcu_preempt_blocked_पढ़ोers_cgp(rnp))
		वापस 0;
	pr_err("\tTasks blocked on level-%d rcu_node (CPUs %d-%d):",
	       rnp->level, rnp->grplo, rnp->grphi);
	t = list_entry(rnp->gp_tasks->prev,
		       काष्ठा task_काष्ठा, rcu_node_entry);
	list_क्रम_each_entry_जारी(t, &rnp->blkd_tasks, rcu_node_entry) अणु
		get_task_काष्ठा(t);
		ts[i++] = t;
		अगर (i >= ARRAY_SIZE(ts))
			अवरोध;
	पूर्ण
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	क्रम (i--; i; i--) अणु
		t = ts[i];
		अगर (!try_invoke_on_locked_करोwn_task(t, check_slow_task, &rscr))
			pr_cont(" P%d", t->pid);
		अन्यथा
			pr_cont(" P%d/%d:%c%c%c%c",
				t->pid, rscr.nesting,
				".b"[rscr.rs.b.blocked],
				".q"[rscr.rs.b.need_qs],
				".e"[rscr.rs.b.exp_hपूर्णांक],
				".l"[rscr.on_blkd_list]);
		lockdep_निश्चित_irqs_disabled();
		put_task_काष्ठा(t);
		ndetected++;
	पूर्ण
	pr_cont("\n");
	वापस ndetected;
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_PREEMPT_RCU */

/*
 * Because preemptible RCU करोes not exist, we never have to check क्रम
 * tasks blocked within RCU पढ़ो-side critical sections.
 */
अटल व्योम rcu_prपूर्णांक_detail_task_stall_rnp(काष्ठा rcu_node *rnp)
अणु
पूर्ण

/*
 * Because preemptible RCU करोes not exist, we never have to check क्रम
 * tasks blocked within RCU पढ़ो-side critical sections.
 */
अटल पूर्णांक rcu_prपूर्णांक_task_stall(काष्ठा rcu_node *rnp, अचिन्हित दीर्घ flags)
अणु
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PREEMPT_RCU */

/*
 * Dump stacks of all tasks running on stalled CPUs.  First try using
 * NMIs, but fall back to manual remote stack tracing on architectures
 * that करोn't support NMI-based stack dumps.  The NMI-triggered stack
 * traces are more accurate because they are prपूर्णांकed by the target CPU.
 */
अटल व्योम rcu_dump_cpu_stacks(व्योम)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_node *rnp;

	rcu_क्रम_each_leaf_node(rnp) अणु
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		क्रम_each_leaf_node_possible_cpu(rnp, cpu)
			अगर (rnp->qsmask & leaf_node_cpu_bit(rnp, cpu)) अणु
				अगर (cpu_is_offline(cpu))
					pr_err("Offline CPU %d blocking current GP.\n", cpu);
				अन्यथा अगर (!trigger_single_cpu_backtrace(cpu))
					dump_cpu_task(cpu);
			पूर्ण
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_RCU_FAST_NO_HZ

अटल व्योम prपूर्णांक_cpu_stall_fast_no_hz(अक्षर *cp, पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = &per_cpu(rcu_data, cpu);

	प्र_लिखो(cp, "last_accelerate: %04lx/%04lx dyntick_enabled: %d",
		rdp->last_accelerate & 0xffff, jअगरfies & 0xffff,
		!!rdp->tick_nohz_enabled_snap);
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_RCU_FAST_NO_HZ */

अटल व्योम prपूर्णांक_cpu_stall_fast_no_hz(अक्षर *cp, पूर्णांक cpu)
अणु
	*cp = '\0';
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_FAST_NO_HZ */

अटल स्थिर अक्षर * स्थिर gp_state_names[] = अणु
	[RCU_GP_IDLE] = "RCU_GP_IDLE",
	[RCU_GP_WAIT_GPS] = "RCU_GP_WAIT_GPS",
	[RCU_GP_DONE_GPS] = "RCU_GP_DONE_GPS",
	[RCU_GP_ONOFF] = "RCU_GP_ONOFF",
	[RCU_GP_INIT] = "RCU_GP_INIT",
	[RCU_GP_WAIT_FQS] = "RCU_GP_WAIT_FQS",
	[RCU_GP_DOING_FQS] = "RCU_GP_DOING_FQS",
	[RCU_GP_CLEANUP] = "RCU_GP_CLEANUP",
	[RCU_GP_CLEANED] = "RCU_GP_CLEANED",
पूर्ण;

/*
 * Convert a ->gp_state value to a अक्षरacter string.
 */
अटल स्थिर अक्षर *gp_state_getname(लघु gs)
अणु
	अगर (gs < 0 || gs >= ARRAY_SIZE(gp_state_names))
		वापस "???";
	वापस gp_state_names[gs];
पूर्ण

/* Is the RCU grace-period kthपढ़ो being starved of CPU समय? */
अटल bool rcu_is_gp_kthपढ़ो_starving(अचिन्हित दीर्घ *jp)
अणु
	अचिन्हित दीर्घ j = jअगरfies - READ_ONCE(rcu_state.gp_activity);

	अगर (jp)
		*jp = j;
	वापस j > 2 * HZ;
पूर्ण

/*
 * Prपूर्णांक out diagnostic inक्रमmation क्रम the specअगरied stalled CPU.
 *
 * If the specअगरied CPU is aware of the current RCU grace period, then
 * prपूर्णांक the number of scheduling घड़ी पूर्णांकerrupts the CPU has taken
 * during the समय that it has been aware.  Otherwise, prपूर्णांक the number
 * of RCU grace periods that this CPU is ignorant of, क्रम example, "1"
 * अगर the CPU was aware of the previous grace period.
 *
 * Also prपूर्णांक out idle and (अगर CONFIG_RCU_FAST_NO_HZ) idle-entry info.
 */
अटल व्योम prपूर्णांक_cpu_stall_info(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ delta;
	bool falsepositive;
	अक्षर fast_no_hz[72];
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	अक्षर *ticks_title;
	अचिन्हित दीर्घ ticks_value;

	/*
	 * We could be prपूर्णांकing a lot जबतक holding a spinlock.  Aव्योम
	 * triggering hard lockup.
	 */
	touch_nmi_watchकरोg();

	ticks_value = rcu_seq_ctr(rcu_state.gp_seq - rdp->gp_seq);
	अगर (ticks_value) अणु
		ticks_title = "GPs behind";
	पूर्ण अन्यथा अणु
		ticks_title = "ticks this GP";
		ticks_value = rdp->ticks_this_gp;
	पूर्ण
	prपूर्णांक_cpu_stall_fast_no_hz(fast_no_hz, cpu);
	delta = rcu_seq_ctr(rdp->mynode->gp_seq - rdp->rcu_iw_gp_seq);
	falsepositive = rcu_is_gp_kthपढ़ो_starving(शून्य) &&
			rcu_dynticks_in_eqs(rcu_dynticks_snap(rdp));
	pr_err("\t%d-%c%c%c%c: (%lu %s) idle=%03x/%ld/%#lx softirq=%u/%u fqs=%ld %s%s\n",
	       cpu,
	       "O."[!!cpu_online(cpu)],
	       "o."[!!(rdp->grpmask & rdp->mynode->qsmaskinit)],
	       "N."[!!(rdp->grpmask & rdp->mynode->qsmaskinitnext)],
	       !IS_ENABLED(CONFIG_IRQ_WORK) ? '?' :
			rdp->rcu_iw_pending ? (पूर्णांक)min(delta, 9UL) + '0' :
				"!."[!delta],
	       ticks_value, ticks_title,
	       rcu_dynticks_snap(rdp) & 0xfff,
	       rdp->dynticks_nesting, rdp->dynticks_nmi_nesting,
	       rdp->softirq_snap, kstat_softirqs_cpu(RCU_SOFTIRQ, cpu),
	       data_race(rcu_state.n_क्रमce_qs) - rcu_state.n_क्रमce_qs_gpstart,
	       fast_no_hz,
	       falsepositive ? " (false positive?)" : "");
पूर्ण

/* Complain about starvation of grace-period kthपढ़ो.  */
अटल व्योम rcu_check_gp_kthपढ़ो_starvation(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा task_काष्ठा *gpk = rcu_state.gp_kthपढ़ो;
	अचिन्हित दीर्घ j;

	अगर (rcu_is_gp_kthपढ़ो_starving(&j)) अणु
		cpu = gpk ? task_cpu(gpk) : -1;
		pr_err("%s kthread starved for %ld jiffies! g%ld f%#x %s(%d) ->state=%#lx ->cpu=%d\n",
		       rcu_state.name, j,
		       (दीर्घ)rcu_seq_current(&rcu_state.gp_seq),
		       data_race(rcu_state.gp_flags),
		       gp_state_getname(rcu_state.gp_state), rcu_state.gp_state,
		       gpk ? gpk->state : ~0, cpu);
		अगर (gpk) अणु
			pr_err("\tUnless %s kthread gets sufficient CPU time, OOM is now expected behavior.\n", rcu_state.name);
			pr_err("RCU grace-period kthread stack dump:\n");
			sched_show_task(gpk);
			अगर (cpu >= 0) अणु
				अगर (cpu_is_offline(cpu)) अणु
					pr_err("RCU GP kthread last ran on offline CPU %d.\n", cpu);
				पूर्ण अन्यथा  अणु
					pr_err("Stack dump where RCU GP kthread last ran:\n");
					अगर (!trigger_single_cpu_backtrace(cpu))
						dump_cpu_task(cpu);
				पूर्ण
			पूर्ण
			wake_up_process(gpk);
		पूर्ण
	पूर्ण
पूर्ण

/* Complain about missing wakeups from expired fqs रुको समयr */
अटल व्योम rcu_check_gp_kthपढ़ो_expired_fqs_समयr(व्योम)
अणु
	काष्ठा task_काष्ठा *gpk = rcu_state.gp_kthपढ़ो;
	लघु gp_state;
	अचिन्हित दीर्घ jअगरfies_fqs;
	पूर्णांक cpu;

	/*
	 * Order पढ़ोs of .gp_state and .jअगरfies_क्रमce_qs.
	 * Matching smp_wmb() is present in rcu_gp_fqs_loop().
	 */
	gp_state = smp_load_acquire(&rcu_state.gp_state);
	jअगरfies_fqs = READ_ONCE(rcu_state.jअगरfies_क्रमce_qs);

	अगर (gp_state == RCU_GP_WAIT_FQS &&
	    समय_after(jअगरfies, jअगरfies_fqs + RCU_STALL_MIGHT_MIN) &&
	    gpk && !READ_ONCE(gpk->on_rq)) अणु
		cpu = task_cpu(gpk);
		pr_err("%s kthread timer wakeup didn't happen for %ld jiffies! g%ld f%#x %s(%d) ->state=%#lx\n",
		       rcu_state.name, (jअगरfies - jअगरfies_fqs),
		       (दीर्घ)rcu_seq_current(&rcu_state.gp_seq),
		       data_race(rcu_state.gp_flags),
		       gp_state_getname(RCU_GP_WAIT_FQS), RCU_GP_WAIT_FQS,
		       gpk->state);
		pr_err("\tPossible timer handling issue on cpu=%d timer-softirq=%u\n",
		       cpu, kstat_softirqs_cpu(TIMER_SOFTIRQ, cpu));
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_other_cpu_stall(अचिन्हित दीर्घ gp_seq, अचिन्हित दीर्घ gps)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ gpa;
	अचिन्हित दीर्घ j;
	पूर्णांक ndetected = 0;
	काष्ठा rcu_node *rnp;
	दीर्घ totqlen = 0;

	lockdep_निश्चित_irqs_disabled();

	/* Kick and suppress, अगर so configured. */
	rcu_stall_kick_kthपढ़ोs();
	अगर (rcu_stall_is_suppressed())
		वापस;

	/*
	 * OK, समय to rat on our buddy...
	 * See Documentation/RCU/stallwarn.rst क्रम info on how to debug
	 * RCU CPU stall warnings.
	 */
	trace_rcu_stall_warning(rcu_state.name, TPS("StallDetected"));
	pr_err("INFO: %s detected stalls on CPUs/tasks:\n", rcu_state.name);
	rcu_क्रम_each_leaf_node(rnp) अणु
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		अगर (rnp->qsmask != 0) अणु
			क्रम_each_leaf_node_possible_cpu(rnp, cpu)
				अगर (rnp->qsmask & leaf_node_cpu_bit(rnp, cpu)) अणु
					prपूर्णांक_cpu_stall_info(cpu);
					ndetected++;
				पूर्ण
		पूर्ण
		ndetected += rcu_prपूर्णांक_task_stall(rnp, flags); // Releases rnp->lock.
		lockdep_निश्चित_irqs_disabled();
	पूर्ण

	क्रम_each_possible_cpu(cpu)
		totqlen += rcu_get_n_cbs_cpu(cpu);
	pr_cont("\t(detected by %d, t=%ld jiffies, g=%ld, q=%lu)\n",
	       smp_processor_id(), (दीर्घ)(jअगरfies - gps),
	       (दीर्घ)rcu_seq_current(&rcu_state.gp_seq), totqlen);
	अगर (ndetected) अणु
		rcu_dump_cpu_stacks();

		/* Complain about tasks blocking the grace period. */
		rcu_क्रम_each_leaf_node(rnp)
			rcu_prपूर्णांक_detail_task_stall_rnp(rnp);
	पूर्ण अन्यथा अणु
		अगर (rcu_seq_current(&rcu_state.gp_seq) != gp_seq) अणु
			pr_err("INFO: Stall ended before state dump start\n");
		पूर्ण अन्यथा अणु
			j = jअगरfies;
			gpa = data_race(rcu_state.gp_activity);
			pr_err("All QSes seen, last %s kthread activity %ld (%ld-%ld), jiffies_till_next_fqs=%ld, root ->qsmask %#lx\n",
			       rcu_state.name, j - gpa, j, gpa,
			       data_race(jअगरfies_till_next_fqs),
			       rcu_get_root()->qsmask);
		पूर्ण
	पूर्ण
	/* Reग_लिखो अगर needed in हाल of slow consoles. */
	अगर (ULONG_CMP_GE(jअगरfies, READ_ONCE(rcu_state.jअगरfies_stall)))
		WRITE_ONCE(rcu_state.jअगरfies_stall,
			   jअगरfies + 3 * rcu_jअगरfies_till_stall_check() + 3);

	rcu_check_gp_kthपढ़ो_expired_fqs_समयr();
	rcu_check_gp_kthपढ़ो_starvation();

	panic_on_rcu_stall();

	rcu_क्रमce_quiescent_state();  /* Kick them all. */
पूर्ण

अटल व्योम prपूर्णांक_cpu_stall(अचिन्हित दीर्घ gps)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp = rcu_get_root();
	दीर्घ totqlen = 0;

	lockdep_निश्चित_irqs_disabled();

	/* Kick and suppress, अगर so configured. */
	rcu_stall_kick_kthपढ़ोs();
	अगर (rcu_stall_is_suppressed())
		वापस;

	/*
	 * OK, समय to rat on ourselves...
	 * See Documentation/RCU/stallwarn.rst क्रम info on how to debug
	 * RCU CPU stall warnings.
	 */
	trace_rcu_stall_warning(rcu_state.name, TPS("SelfDetected"));
	pr_err("INFO: %s self-detected stall on CPU\n", rcu_state.name);
	raw_spin_lock_irqsave_rcu_node(rdp->mynode, flags);
	prपूर्णांक_cpu_stall_info(smp_processor_id());
	raw_spin_unlock_irqrestore_rcu_node(rdp->mynode, flags);
	क्रम_each_possible_cpu(cpu)
		totqlen += rcu_get_n_cbs_cpu(cpu);
	pr_cont("\t(t=%lu jiffies g=%ld q=%lu)\n",
		jअगरfies - gps,
		(दीर्घ)rcu_seq_current(&rcu_state.gp_seq), totqlen);

	rcu_check_gp_kthपढ़ो_expired_fqs_समयr();
	rcu_check_gp_kthपढ़ो_starvation();

	rcu_dump_cpu_stacks();

	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	/* Reग_लिखो अगर needed in हाल of slow consoles. */
	अगर (ULONG_CMP_GE(jअगरfies, READ_ONCE(rcu_state.jअगरfies_stall)))
		WRITE_ONCE(rcu_state.jअगरfies_stall,
			   jअगरfies + 3 * rcu_jअगरfies_till_stall_check() + 3);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);

	panic_on_rcu_stall();

	/*
	 * Attempt to revive the RCU machinery by क्रमcing a context चयन.
	 *
	 * A context चयन would normally allow the RCU state machine to make
	 * progress and it could be we're stuck in kernel space without context
	 * चयनes क्रम an entirely unreasonable amount of समय.
	 */
	set_tsk_need_resched(current);
	set_preempt_need_resched();
पूर्ण

अटल व्योम check_cpu_stall(काष्ठा rcu_data *rdp)
अणु
	अचिन्हित दीर्घ gs1;
	अचिन्हित दीर्घ gs2;
	अचिन्हित दीर्घ gps;
	अचिन्हित दीर्घ j;
	अचिन्हित दीर्घ jn;
	अचिन्हित दीर्घ js;
	काष्ठा rcu_node *rnp;

	lockdep_निश्चित_irqs_disabled();
	अगर ((rcu_stall_is_suppressed() && !READ_ONCE(rcu_kick_kthपढ़ोs)) ||
	    !rcu_gp_in_progress())
		वापस;
	rcu_stall_kick_kthपढ़ोs();
	j = jअगरfies;

	/*
	 * Lots of memory barriers to reject false positives.
	 *
	 * The idea is to pick up rcu_state.gp_seq, then
	 * rcu_state.jअगरfies_stall, then rcu_state.gp_start, and finally
	 * another copy of rcu_state.gp_seq.  These values are updated in
	 * the opposite order with memory barriers (or equivalent) during
	 * grace-period initialization and cleanup.  Now, a false positive
	 * can occur अगर we get an new value of rcu_state.gp_start and a old
	 * value of rcu_state.jअगरfies_stall.  But given the memory barriers,
	 * the only way that this can happen is अगर one grace period ends
	 * and another starts between these two fetches.  This is detected
	 * by comparing the second fetch of rcu_state.gp_seq with the
	 * previous fetch from rcu_state.gp_seq.
	 *
	 * Given this check, comparisons of jअगरfies, rcu_state.jअगरfies_stall,
	 * and rcu_state.gp_start suffice to क्रमestall false positives.
	 */
	gs1 = READ_ONCE(rcu_state.gp_seq);
	smp_rmb(); /* Pick up ->gp_seq first... */
	js = READ_ONCE(rcu_state.jअगरfies_stall);
	smp_rmb(); /* ...then ->jअगरfies_stall beक्रमe the rest... */
	gps = READ_ONCE(rcu_state.gp_start);
	smp_rmb(); /* ...and finally ->gp_start beक्रमe ->gp_seq again. */
	gs2 = READ_ONCE(rcu_state.gp_seq);
	अगर (gs1 != gs2 ||
	    ULONG_CMP_LT(j, js) ||
	    ULONG_CMP_GE(gps, js))
		वापस; /* No stall or GP completed since entering function. */
	rnp = rdp->mynode;
	jn = jअगरfies + 3 * rcu_jअगरfies_till_stall_check() + 3;
	अगर (rcu_gp_in_progress() &&
	    (READ_ONCE(rnp->qsmask) & rdp->grpmask) &&
	    cmpxchg(&rcu_state.jअगरfies_stall, js, jn) == js) अणु

		/* We haven't checked in, so go dump stack. */
		prपूर्णांक_cpu_stall(gps);
		अगर (READ_ONCE(rcu_cpu_stall_ftrace_dump))
			rcu_ftrace_dump(DUMP_ALL);

	पूर्ण अन्यथा अगर (rcu_gp_in_progress() &&
		   ULONG_CMP_GE(j, js + RCU_STALL_RAT_DELAY) &&
		   cmpxchg(&rcu_state.jअगरfies_stall, js, jn) == js) अणु

		/* They had a few समय units to dump stack, so complain. */
		prपूर्णांक_other_cpu_stall(gs2, gps);
		अगर (READ_ONCE(rcu_cpu_stall_ftrace_dump))
			rcu_ftrace_dump(DUMP_ALL);
	पूर्ण
पूर्ण

//////////////////////////////////////////////////////////////////////////////
//
// RCU क्रमward-progress mechanisms, including of callback invocation.


/*
 * Show the state of the grace-period kthपढ़ोs.
 */
व्योम show_rcu_gp_kthपढ़ोs(व्योम)
अणु
	अचिन्हित दीर्घ cbs = 0;
	पूर्णांक cpu;
	अचिन्हित दीर्घ j;
	अचिन्हित दीर्घ ja;
	अचिन्हित दीर्घ jr;
	अचिन्हित दीर्घ jw;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;
	काष्ठा task_काष्ठा *t = READ_ONCE(rcu_state.gp_kthपढ़ो);

	j = jअगरfies;
	ja = j - data_race(rcu_state.gp_activity);
	jr = j - data_race(rcu_state.gp_req_activity);
	jw = j - data_race(rcu_state.gp_wake_समय);
	pr_info("%s: wait state: %s(%d) ->state: %#lx delta ->gp_activity %lu ->gp_req_activity %lu ->gp_wake_time %lu ->gp_wake_seq %ld ->gp_seq %ld ->gp_seq_needed %ld ->gp_flags %#x\n",
		rcu_state.name, gp_state_getname(rcu_state.gp_state),
		rcu_state.gp_state, t ? t->state : 0x1ffffL,
		ja, jr, jw, (दीर्घ)data_race(rcu_state.gp_wake_seq),
		(दीर्घ)data_race(rcu_state.gp_seq),
		(दीर्घ)data_race(rcu_get_root()->gp_seq_needed),
		data_race(rcu_state.gp_flags));
	rcu_क्रम_each_node_bपढ़ोth_first(rnp) अणु
		अगर (ULONG_CMP_GE(READ_ONCE(rcu_state.gp_seq),
				 READ_ONCE(rnp->gp_seq_needed)))
			जारी;
		pr_info("\trcu_node %d:%d ->gp_seq %ld ->gp_seq_needed %ld\n",
			rnp->grplo, rnp->grphi, (दीर्घ)data_race(rnp->gp_seq),
			(दीर्घ)data_race(rnp->gp_seq_needed));
		अगर (!rcu_is_leaf_node(rnp))
			जारी;
		क्रम_each_leaf_node_possible_cpu(rnp, cpu) अणु
			rdp = per_cpu_ptr(&rcu_data, cpu);
			अगर (READ_ONCE(rdp->gpwrap) ||
			    ULONG_CMP_GE(READ_ONCE(rcu_state.gp_seq),
					 READ_ONCE(rdp->gp_seq_needed)))
				जारी;
			pr_info("\tcpu %d ->gp_seq_needed %ld\n",
				cpu, (दीर्घ)data_race(rdp->gp_seq_needed));
		पूर्ण
	पूर्ण
	क्रम_each_possible_cpu(cpu) अणु
		rdp = per_cpu_ptr(&rcu_data, cpu);
		cbs += data_race(rdp->n_cbs_invoked);
		अगर (rcu_segcblist_is_offloaded(&rdp->cblist))
			show_rcu_nocb_state(rdp);
	पूर्ण
	pr_info("RCU callbacks invoked since boot: %lu\n", cbs);
	show_rcu_tasks_gp_kthपढ़ोs();
पूर्ण
EXPORT_SYMBOL_GPL(show_rcu_gp_kthपढ़ोs);

/*
 * This function checks क्रम grace-period requests that fail to motivate
 * RCU to come out of its idle mode.
 */
अटल व्योम rcu_check_gp_start_stall(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp,
				     स्थिर अचिन्हित दीर्घ gpssdelay)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ j;
	काष्ठा rcu_node *rnp_root = rcu_get_root();
	अटल atomic_t warned = ATOMIC_INIT(0);

	अगर (!IS_ENABLED(CONFIG_PROVE_RCU) || rcu_gp_in_progress() ||
	    ULONG_CMP_GE(READ_ONCE(rnp_root->gp_seq),
			 READ_ONCE(rnp_root->gp_seq_needed)) ||
	    !smp_load_acquire(&rcu_state.gp_kthपढ़ो)) // Get stable kthपढ़ो.
		वापस;
	j = jअगरfies; /* Expensive access, and in common हाल करोn't get here. */
	अगर (समय_beक्रमe(j, READ_ONCE(rcu_state.gp_req_activity) + gpssdelay) ||
	    समय_beक्रमe(j, READ_ONCE(rcu_state.gp_activity) + gpssdelay) ||
	    atomic_पढ़ो(&warned))
		वापस;

	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	j = jअगरfies;
	अगर (rcu_gp_in_progress() ||
	    ULONG_CMP_GE(READ_ONCE(rnp_root->gp_seq),
			 READ_ONCE(rnp_root->gp_seq_needed)) ||
	    समय_beक्रमe(j, READ_ONCE(rcu_state.gp_req_activity) + gpssdelay) ||
	    समय_beक्रमe(j, READ_ONCE(rcu_state.gp_activity) + gpssdelay) ||
	    atomic_पढ़ो(&warned)) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;
	पूर्ण
	/* Hold onto the leaf lock to make others see warned==1. */

	अगर (rnp_root != rnp)
		raw_spin_lock_rcu_node(rnp_root); /* irqs alपढ़ोy disabled. */
	j = jअगरfies;
	अगर (rcu_gp_in_progress() ||
	    ULONG_CMP_GE(READ_ONCE(rnp_root->gp_seq),
			 READ_ONCE(rnp_root->gp_seq_needed)) ||
	    समय_beक्रमe(j, READ_ONCE(rcu_state.gp_req_activity) + gpssdelay) ||
	    समय_beक्रमe(j, READ_ONCE(rcu_state.gp_activity) + gpssdelay) ||
	    atomic_xchg(&warned, 1)) अणु
		अगर (rnp_root != rnp)
			/* irqs reमुख्य disabled. */
			raw_spin_unlock_rcu_node(rnp_root);
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;
	पूर्ण
	WARN_ON(1);
	अगर (rnp_root != rnp)
		raw_spin_unlock_rcu_node(rnp_root);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	show_rcu_gp_kthपढ़ोs();
पूर्ण

/*
 * Do a क्रमward-progress check क्रम rcutorture.  This is normally invoked
 * due to an OOM event.  The argument "j" gives the समय period during
 * which rcutorture would like progress to have been made.
 */
व्योम rcu_fwd_progress_check(अचिन्हित दीर्घ j)
अणु
	अचिन्हित दीर्घ cbs;
	पूर्णांक cpu;
	अचिन्हित दीर्घ max_cbs = 0;
	पूर्णांक max_cpu = -1;
	काष्ठा rcu_data *rdp;

	अगर (rcu_gp_in_progress()) अणु
		pr_info("%s: GP age %lu jiffies\n",
			__func__, jअगरfies - rcu_state.gp_start);
		show_rcu_gp_kthपढ़ोs();
	पूर्ण अन्यथा अणु
		pr_info("%s: Last GP end %lu jiffies ago\n",
			__func__, jअगरfies - rcu_state.gp_end);
		preempt_disable();
		rdp = this_cpu_ptr(&rcu_data);
		rcu_check_gp_start_stall(rdp->mynode, rdp, j);
		preempt_enable();
	पूर्ण
	क्रम_each_possible_cpu(cpu) अणु
		cbs = rcu_get_n_cbs_cpu(cpu);
		अगर (!cbs)
			जारी;
		अगर (max_cpu < 0)
			pr_info("%s: callbacks", __func__);
		pr_cont(" %d: %lu", cpu, cbs);
		अगर (cbs <= max_cbs)
			जारी;
		max_cbs = cbs;
		max_cpu = cpu;
	पूर्ण
	अगर (max_cpu >= 0)
		pr_cont("\n");
पूर्ण
EXPORT_SYMBOL_GPL(rcu_fwd_progress_check);

/* Commandeer a sysrq key to dump RCU's tree. */
अटल bool sysrq_rcu;
module_param(sysrq_rcu, bool, 0444);

/* Dump grace-period-request inक्रमmation due to commandeered sysrq. */
अटल व्योम sysrq_show_rcu(पूर्णांक key)
अणु
	show_rcu_gp_kthपढ़ोs();
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_rcudump_op = अणु
	.handler = sysrq_show_rcu,
	.help_msg = "show-rcu(y)",
	.action_msg = "Show RCU tree",
	.enable_mask = SYSRQ_ENABLE_DUMP,
पूर्ण;

अटल पूर्णांक __init rcu_sysrq_init(व्योम)
अणु
	अगर (sysrq_rcu)
		वापस रेजिस्टर_sysrq_key('y', &sysrq_rcudump_op);
	वापस 0;
पूर्ण
early_initcall(rcu_sysrq_init);
