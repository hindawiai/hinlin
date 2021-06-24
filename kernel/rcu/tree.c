<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Read-Copy Update mechanism क्रम mutual exclusion (tree-based version)
 *
 * Copyright IBM Corporation, 2008
 *
 * Authors: Dipankar Sarma <dipankar@in.ibm.com>
 *	    Manfred Spraul <manfred@colorfullअगरe.com>
 *	    Paul E. McKenney <paulmck@linux.ibm.com>
 *
 * Based on the original work by Paul McKenney <paulmck@linux.ibm.com>
 * and inमाला_दो from Rusty Russell, Andrea Arcangeli and Andi Kleen.
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *	Documentation/RCU
 */

#घोषणा pr_fmt(fmt) "rcu: " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/nmi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <linux/completion.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समय.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/रुको.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/suspend.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/tick.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/gfp.h>
#समावेश <linux/oom.h>
#समावेश <linux/smpboot.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/kasan.h>
#समावेश "../time/tick-internal.h"

#समावेश "tree.h"
#समावेश "rcu.h"

#अगर_घोषित MODULE_PARAM_PREFIX
#अघोषित MODULE_PARAM_PREFIX
#पूर्ण_अगर
#घोषणा MODULE_PARAM_PREFIX "rcutree."

/* Data काष्ठाures. */

/*
 * Steal a bit from the bottom of ->dynticks क्रम idle entry/निकास
 * control.  Initially this is क्रम TLB flushing.
 */
#घोषणा RCU_DYNTICK_CTRL_MASK 0x1
#घोषणा RCU_DYNTICK_CTRL_CTR  (RCU_DYNTICK_CTRL_MASK + 1)

अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा rcu_data, rcu_data) = अणु
	.dynticks_nesting = 1,
	.dynticks_nmi_nesting = DYNTICK_IRQ_NONIDLE,
	.dynticks = ATOMIC_INIT(RCU_DYNTICK_CTRL_CTR),
#अगर_घोषित CONFIG_RCU_NOCB_CPU
	.cblist.flags = SEGCBLIST_SOFTIRQ_ONLY,
#पूर्ण_अगर
पूर्ण;
अटल काष्ठा rcu_state rcu_state = अणु
	.level = अणु &rcu_state.node[0] पूर्ण,
	.gp_state = RCU_GP_IDLE,
	.gp_seq = (0UL - 300UL) << RCU_SEQ_CTR_SHIFT,
	.barrier_mutex = __MUTEX_INITIALIZER(rcu_state.barrier_mutex),
	.name = RCU_NAME,
	.abbr = RCU_ABBR,
	.exp_mutex = __MUTEX_INITIALIZER(rcu_state.exp_mutex),
	.exp_wake_mutex = __MUTEX_INITIALIZER(rcu_state.exp_wake_mutex),
	.ofl_lock = __RAW_SPIN_LOCK_UNLOCKED(rcu_state.ofl_lock),
पूर्ण;

/* Dump rcu_node combining tree at boot to verअगरy correct setup. */
अटल bool dump_tree;
module_param(dump_tree, bool, 0444);
/* By शेष, use RCU_SOFTIRQ instead of rcuc kthपढ़ोs. */
अटल bool use_softirq = !IS_ENABLED(CONFIG_PREEMPT_RT);
#अगर_अघोषित CONFIG_PREEMPT_RT
module_param(use_softirq, bool, 0444);
#पूर्ण_अगर
/* Control rcu_node-tree स्वतः-balancing at boot समय. */
अटल bool rcu_fanout_exact;
module_param(rcu_fanout_exact, bool, 0444);
/* Increase (but not decrease) the RCU_FANOUT_LEAF at boot समय. */
अटल पूर्णांक rcu_fanout_leaf = RCU_FANOUT_LEAF;
module_param(rcu_fanout_leaf, पूर्णांक, 0444);
पूर्णांक rcu_num_lvls __पढ़ो_mostly = RCU_NUM_LVLS;
/* Number of rcu_nodes at specअगरied level. */
पूर्णांक num_rcu_lvl[] = NUM_RCU_LVL_INIT;
पूर्णांक rcu_num_nodes __पढ़ो_mostly = NUM_RCU_NODES; /* Total # rcu_nodes in use. */

/*
 * The rcu_scheduler_active variable is initialized to the value
 * RCU_SCHEDULER_INACTIVE and transitions RCU_SCHEDULER_INIT just beक्रमe the
 * first task is spawned.  So when this variable is RCU_SCHEDULER_INACTIVE,
 * RCU can assume that there is but one task, allowing RCU to (क्रम example)
 * optimize synchronize_rcu() to a simple barrier().  When this variable
 * is RCU_SCHEDULER_INIT, RCU must actually करो all the hard work required
 * to detect real grace periods.  This variable is also used to suppress
 * boot-समय false positives from lockdep-RCU error checking.  Finally, it
 * transitions from RCU_SCHEDULER_INIT to RCU_SCHEDULER_RUNNING after RCU
 * is fully initialized, including all of its kthपढ़ोs having been spawned.
 */
पूर्णांक rcu_scheduler_active __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(rcu_scheduler_active);

/*
 * The rcu_scheduler_fully_active variable transitions from zero to one
 * during the early_initcall() processing, which is after the scheduler
 * is capable of creating new tasks.  So RCU processing (क्रम example,
 * creating tasks क्रम RCU priority boosting) must be delayed until after
 * rcu_scheduler_fully_active transitions from zero to one.  We also
 * currently delay invocation of any RCU callbacks until after this poपूर्णांक.
 *
 * It might later prove better क्रम people रेजिस्टरing RCU callbacks during
 * early boot to take responsibility क्रम these callbacks, but one step at
 * a समय.
 */
अटल पूर्णांक rcu_scheduler_fully_active __पढ़ो_mostly;

अटल व्योम rcu_report_qs_rnp(अचिन्हित दीर्घ mask, काष्ठा rcu_node *rnp,
			      अचिन्हित दीर्घ gps, अचिन्हित दीर्घ flags);
अटल व्योम rcu_init_new_rnp(काष्ठा rcu_node *rnp_leaf);
अटल व्योम rcu_cleanup_dead_rnp(काष्ठा rcu_node *rnp_leaf);
अटल व्योम rcu_boost_kthपढ़ो_setaffinity(काष्ठा rcu_node *rnp, पूर्णांक outgoingcpu);
अटल व्योम invoke_rcu_core(व्योम);
अटल व्योम rcu_report_exp_rdp(काष्ठा rcu_data *rdp);
अटल व्योम sync_sched_exp_online_cleanup(पूर्णांक cpu);
अटल व्योम check_cb_ovld_locked(काष्ठा rcu_data *rdp, काष्ठा rcu_node *rnp);
अटल bool rcu_rdp_is_offloaded(काष्ठा rcu_data *rdp);

/* rcuc/rcub kthपढ़ो realसमय priority */
अटल पूर्णांक kthपढ़ो_prio = IS_ENABLED(CONFIG_RCU_BOOST) ? 1 : 0;
module_param(kthपढ़ो_prio, पूर्णांक, 0444);

/* Delay in jअगरfies क्रम grace-period initialization delays, debug only. */

अटल पूर्णांक gp_preinit_delay;
module_param(gp_preinit_delay, पूर्णांक, 0444);
अटल पूर्णांक gp_init_delay;
module_param(gp_init_delay, पूर्णांक, 0444);
अटल पूर्णांक gp_cleanup_delay;
module_param(gp_cleanup_delay, पूर्णांक, 0444);

// Add delay to rcu_पढ़ो_unlock() क्रम strict grace periods.
अटल पूर्णांक rcu_unlock_delay;
#अगर_घोषित CONFIG_RCU_STRICT_GRACE_PERIOD
module_param(rcu_unlock_delay, पूर्णांक, 0444);
#पूर्ण_अगर

/*
 * This rcu parameter is runसमय-पढ़ो-only. It reflects
 * a minimum allowed number of objects which can be cached
 * per-CPU. Object size is equal to one page. This value
 * can be changed at boot समय.
 */
अटल पूर्णांक rcu_min_cached_objs = 5;
module_param(rcu_min_cached_objs, पूर्णांक, 0444);

/* Retrieve RCU kthपढ़ोs priority क्रम rcutorture */
पूर्णांक rcu_get_gp_kthपढ़ोs_prio(व्योम)
अणु
	वापस kthपढ़ो_prio;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_get_gp_kthपढ़ोs_prio);

/*
 * Number of grace periods between delays, normalized by the duration of
 * the delay.  The दीर्घer the delay, the more the grace periods between
 * each delay.  The reason क्रम this normalization is that it means that,
 * क्रम non-zero delays, the overall slowकरोwn of grace periods is स्थिरant
 * regardless of the duration of the delay.  This arrangement balances
 * the need क्रम दीर्घ delays to increase some race probabilities with the
 * need क्रम fast grace periods to increase other race probabilities.
 */
#घोषणा PER_RCU_NODE_PERIOD 3	/* Number of grace periods between delays. */

/*
 * Compute the mask of online CPUs क्रम the specअगरied rcu_node काष्ठाure.
 * This will not be stable unless the rcu_node काष्ठाure's ->lock is
 * held, but the bit corresponding to the current CPU will be stable
 * in most contexts.
 */
अटल अचिन्हित दीर्घ rcu_rnp_online_cpus(काष्ठा rcu_node *rnp)
अणु
	वापस READ_ONCE(rnp->qsmaskinitnext);
पूर्ण

/*
 * Return true अगर an RCU grace period is in progress.  The READ_ONCE()s
 * permit this function to be invoked without holding the root rcu_node
 * काष्ठाure's ->lock, but of course results can be subject to change.
 */
अटल पूर्णांक rcu_gp_in_progress(व्योम)
अणु
	वापस rcu_seq_state(rcu_seq_current(&rcu_state.gp_seq));
पूर्ण

/*
 * Return the number of callbacks queued on the specअगरied CPU.
 * Handles both the nocbs and normal हालs.
 */
अटल दीर्घ rcu_get_n_cbs_cpu(पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);

	अगर (rcu_segcblist_is_enabled(&rdp->cblist))
		वापस rcu_segcblist_n_cbs(&rdp->cblist);
	वापस 0;
पूर्ण

व्योम rcu_softirq_qs(व्योम)
अणु
	rcu_qs();
	rcu_preempt_deferred_qs(current);
पूर्ण

/*
 * Record entry पूर्णांकo an extended quiescent state.  This is only to be
 * called when not alपढ़ोy in an extended quiescent state, that is,
 * RCU is watching prior to the call to this function and is no दीर्घer
 * watching upon वापस.
 */
अटल noinstr व्योम rcu_dynticks_eqs_enter(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	पूर्णांक seq;

	/*
	 * CPUs seeing atomic_add_वापस() must see prior RCU पढ़ो-side
	 * critical sections, and we also must क्रमce ordering with the
	 * next idle sojourn.
	 */
	rcu_dynticks_task_trace_enter();  // Beक्रमe ->dynticks update!
	seq = arch_atomic_add_वापस(RCU_DYNTICK_CTRL_CTR, &rdp->dynticks);
	// RCU is no दीर्घer watching.  Better be in extended quiescent state!
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     (seq & RCU_DYNTICK_CTRL_CTR));
	/* Better not have special action (TLB flush) pending! */
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     (seq & RCU_DYNTICK_CTRL_MASK));
पूर्ण

/*
 * Record निकास from an extended quiescent state.  This is only to be
 * called from an extended quiescent state, that is, RCU is not watching
 * prior to the call to this function and is watching upon वापस.
 */
अटल noinstr व्योम rcu_dynticks_eqs_निकास(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	पूर्णांक seq;

	/*
	 * CPUs seeing atomic_add_वापस() must see prior idle sojourns,
	 * and we also must क्रमce ordering with the next RCU पढ़ो-side
	 * critical section.
	 */
	seq = arch_atomic_add_वापस(RCU_DYNTICK_CTRL_CTR, &rdp->dynticks);
	// RCU is now watching.  Better not be in an extended quiescent state!
	rcu_dynticks_task_trace_निकास();  // After ->dynticks update!
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     !(seq & RCU_DYNTICK_CTRL_CTR));
	अगर (seq & RCU_DYNTICK_CTRL_MASK) अणु
		arch_atomic_andnot(RCU_DYNTICK_CTRL_MASK, &rdp->dynticks);
		smp_mb__after_atomic(); /* _निकास after clearing mask. */
	पूर्ण
पूर्ण

/*
 * Reset the current CPU's ->dynticks counter to indicate that the
 * newly onlined CPU is no दीर्घer in an extended quiescent state.
 * This will either leave the counter unchanged, or increment it
 * to the next non-quiescent value.
 *
 * The non-atomic test/increment sequence works because the upper bits
 * of the ->dynticks counter are manipulated only by the corresponding CPU,
 * or when the corresponding CPU is offline.
 */
अटल व्योम rcu_dynticks_eqs_online(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	अगर (atomic_पढ़ो(&rdp->dynticks) & RCU_DYNTICK_CTRL_CTR)
		वापस;
	atomic_add(RCU_DYNTICK_CTRL_CTR, &rdp->dynticks);
पूर्ण

/*
 * Is the current CPU in an extended quiescent state?
 *
 * No ordering, as we are sampling CPU-local inक्रमmation.
 */
अटल __always_अंतरभूत bool rcu_dynticks_curr_cpu_in_eqs(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	वापस !(arch_atomic_पढ़ो(&rdp->dynticks) & RCU_DYNTICK_CTRL_CTR);
पूर्ण

/*
 * Snapshot the ->dynticks counter with full ordering so as to allow
 * stable comparison of this counter with past and future snapshots.
 */
अटल पूर्णांक rcu_dynticks_snap(काष्ठा rcu_data *rdp)
अणु
	पूर्णांक snap = atomic_add_वापस(0, &rdp->dynticks);

	वापस snap & ~RCU_DYNTICK_CTRL_MASK;
पूर्ण

/*
 * Return true अगर the snapshot वापसed from rcu_dynticks_snap()
 * indicates that RCU is in an extended quiescent state.
 */
अटल bool rcu_dynticks_in_eqs(पूर्णांक snap)
अणु
	वापस !(snap & RCU_DYNTICK_CTRL_CTR);
पूर्ण

/* Return true अगर the specअगरied CPU is currently idle from an RCU viewpoपूर्णांक.  */
bool rcu_is_idle_cpu(पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);

	वापस rcu_dynticks_in_eqs(rcu_dynticks_snap(rdp));
पूर्ण

/*
 * Return true अगर the CPU corresponding to the specअगरied rcu_data
 * काष्ठाure has spent some समय in an extended quiescent state since
 * rcu_dynticks_snap() वापसed the specअगरied snapshot.
 */
अटल bool rcu_dynticks_in_eqs_since(काष्ठा rcu_data *rdp, पूर्णांक snap)
अणु
	वापस snap != rcu_dynticks_snap(rdp);
पूर्ण

/*
 * Return true अगर the referenced पूर्णांकeger is zero जबतक the specअगरied
 * CPU reमुख्यs within a single extended quiescent state.
 */
bool rcu_dynticks_zero_in_eqs(पूर्णांक cpu, पूर्णांक *vp)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	पूर्णांक snap;

	// If not quiescent, क्रमce back to earlier extended quiescent state.
	snap = atomic_पढ़ो(&rdp->dynticks) & ~(RCU_DYNTICK_CTRL_MASK |
					       RCU_DYNTICK_CTRL_CTR);

	smp_rmb(); // Order ->dynticks and *vp पढ़ोs.
	अगर (READ_ONCE(*vp))
		वापस false;  // Non-zero, so report failure;
	smp_rmb(); // Order *vp पढ़ो and ->dynticks re-पढ़ो.

	// If still in the same extended quiescent state, we are good!
	वापस snap == (atomic_पढ़ो(&rdp->dynticks) & ~RCU_DYNTICK_CTRL_MASK);
पूर्ण

/*
 * Set the special (bottom) bit of the specअगरied CPU so that it
 * will take special action (such as flushing its TLB) on the
 * next निकास from an extended quiescent state.  Returns true अगर
 * the bit was successfully set, or false अगर the CPU was not in
 * an extended quiescent state.
 */
bool rcu_eqs_special_set(पूर्णांक cpu)
अणु
	पूर्णांक old;
	पूर्णांक new;
	पूर्णांक new_old;
	काष्ठा rcu_data *rdp = &per_cpu(rcu_data, cpu);

	new_old = atomic_पढ़ो(&rdp->dynticks);
	करो अणु
		old = new_old;
		अगर (old & RCU_DYNTICK_CTRL_CTR)
			वापस false;
		new = old | RCU_DYNTICK_CTRL_MASK;
		new_old = atomic_cmpxchg(&rdp->dynticks, old, new);
	पूर्ण जबतक (new_old != old);
	वापस true;
पूर्ण

/*
 * Let the RCU core know that this CPU has gone through the scheduler,
 * which is a quiescent state.  This is called when the need क्रम a
 * quiescent state is urgent, so we burn an atomic operation and full
 * memory barriers to let the RCU core know about it, regardless of what
 * this CPU might (or might not) करो in the near future.
 *
 * We inक्रमm the RCU core by emulating a zero-duration dyntick-idle period.
 *
 * The caller must have disabled पूर्णांकerrupts and must not be idle.
 */
notrace व्योम rcu_momentary_dyntick_idle(व्योम)
अणु
	पूर्णांक special;

	raw_cpu_ग_लिखो(rcu_data.rcu_need_heavy_qs, false);
	special = atomic_add_वापस(2 * RCU_DYNTICK_CTRL_CTR,
				    &this_cpu_ptr(&rcu_data)->dynticks);
	/* It is illegal to call this from idle state. */
	WARN_ON_ONCE(!(special & RCU_DYNTICK_CTRL_CTR));
	rcu_preempt_deferred_qs(current);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_momentary_dyntick_idle);

/**
 * rcu_is_cpu_rrupt_from_idle - see अगर 'interrupted' from idle
 *
 * If the current CPU is idle and running at a first-level (not nested)
 * पूर्णांकerrupt, or directly, from idle, वापस true.
 *
 * The caller must have at least disabled IRQs.
 */
अटल पूर्णांक rcu_is_cpu_rrupt_from_idle(व्योम)
अणु
	दीर्घ nesting;

	/*
	 * Usually called from the tick; but also used from smp_function_call()
	 * क्रम expedited grace periods. This latter can result in running from
	 * the idle task, instead of an actual IPI.
	 */
	lockdep_निश्चित_irqs_disabled();

	/* Check क्रम counter underflows */
	RCU_LOCKDEP_WARN(__this_cpu_पढ़ो(rcu_data.dynticks_nesting) < 0,
			 "RCU dynticks_nesting counter underflow!");
	RCU_LOCKDEP_WARN(__this_cpu_पढ़ो(rcu_data.dynticks_nmi_nesting) <= 0,
			 "RCU dynticks_nmi_nesting counter underflow/zero!");

	/* Are we at first पूर्णांकerrupt nesting level? */
	nesting = __this_cpu_पढ़ो(rcu_data.dynticks_nmi_nesting);
	अगर (nesting > 1)
		वापस false;

	/*
	 * If we're not in an पूर्णांकerrupt, we must be in the idle task!
	 */
	WARN_ON_ONCE(!nesting && !is_idle_task(current));

	/* Does CPU appear to be idle from an RCU standpoपूर्णांक? */
	वापस __this_cpu_पढ़ो(rcu_data.dynticks_nesting) == 0;
पूर्ण

#घोषणा DEFAULT_RCU_BLIMIT (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD) ? 1000 : 10)
				// Maximum callbacks per rcu_करो_batch ...
#घोषणा DEFAULT_MAX_RCU_BLIMIT 10000 // ... even during callback flood.
अटल दीर्घ blimit = DEFAULT_RCU_BLIMIT;
#घोषणा DEFAULT_RCU_QHIMARK 10000 // If this many pending, ignore blimit.
अटल दीर्घ qhimark = DEFAULT_RCU_QHIMARK;
#घोषणा DEFAULT_RCU_QLOMARK 100   // Once only this many pending, use blimit.
अटल दीर्घ qlowmark = DEFAULT_RCU_QLOMARK;
#घोषणा DEFAULT_RCU_QOVLD_MULT 2
#घोषणा DEFAULT_RCU_QOVLD (DEFAULT_RCU_QOVLD_MULT * DEFAULT_RCU_QHIMARK)
अटल दीर्घ qovld = DEFAULT_RCU_QOVLD; // If this many pending, hammer QS.
अटल दीर्घ qovld_calc = -1;	  // No pre-initialization lock acquisitions!

module_param(blimit, दीर्घ, 0444);
module_param(qhimark, दीर्घ, 0444);
module_param(qlowmark, दीर्घ, 0444);
module_param(qovld, दीर्घ, 0444);

अटल uदीर्घ jअगरfies_till_first_fqs = IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD) ? 0 : अच_दीर्घ_उच्च;
अटल uदीर्घ jअगरfies_till_next_fqs = अच_दीर्घ_उच्च;
अटल bool rcu_kick_kthपढ़ोs;
अटल पूर्णांक rcu_भागisor = 7;
module_param(rcu_भागisor, पूर्णांक, 0644);

/* Force an निकास from rcu_करो_batch() after 3 milliseconds. */
अटल दीर्घ rcu_resched_ns = 3 * NSEC_PER_MSEC;
module_param(rcu_resched_ns, दीर्घ, 0644);

/*
 * How दीर्घ the grace period must be beक्रमe we start recruiting
 * quiescent-state help from rcu_note_context_चयन().
 */
अटल uदीर्घ jअगरfies_till_sched_qs = अच_दीर्घ_उच्च;
module_param(jअगरfies_till_sched_qs, uदीर्घ, 0444);
अटल uदीर्घ jअगरfies_to_sched_qs; /* See adjust_jअगरfies_till_sched_qs(). */
module_param(jअगरfies_to_sched_qs, uदीर्घ, 0444); /* Display only! */

/*
 * Make sure that we give the grace-period kthपढ़ो समय to detect any
 * idle CPUs beक्रमe taking active measures to क्रमce quiescent states.
 * However, करोn't go below 100 milliseconds, adjusted upwards क्रम really
 * large प्रणालीs.
 */
अटल व्योम adjust_jअगरfies_till_sched_qs(व्योम)
अणु
	अचिन्हित दीर्घ j;

	/* If jअगरfies_till_sched_qs was specअगरied, respect the request. */
	अगर (jअगरfies_till_sched_qs != अच_दीर्घ_उच्च) अणु
		WRITE_ONCE(jअगरfies_to_sched_qs, jअगरfies_till_sched_qs);
		वापस;
	पूर्ण
	/* Otherwise, set to third fqs scan, but bound below on large प्रणाली. */
	j = READ_ONCE(jअगरfies_till_first_fqs) +
		      2 * READ_ONCE(jअगरfies_till_next_fqs);
	अगर (j < HZ / 10 + nr_cpu_ids / RCU_JIFFIES_FQS_DIV)
		j = HZ / 10 + nr_cpu_ids / RCU_JIFFIES_FQS_DIV;
	pr_info("RCU calculated value of scheduler-enlistment delay is %ld jiffies.\n", j);
	WRITE_ONCE(jअगरfies_to_sched_qs, j);
पूर्ण

अटल पूर्णांक param_set_first_fqs_jअगरfies(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	uदीर्घ j;
	पूर्णांक ret = kम_से_अदीर्घ(val, 0, &j);

	अगर (!ret) अणु
		WRITE_ONCE(*(uदीर्घ *)kp->arg, (j > HZ) ? HZ : j);
		adjust_jअगरfies_till_sched_qs();
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक param_set_next_fqs_jअगरfies(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	uदीर्घ j;
	पूर्णांक ret = kम_से_अदीर्घ(val, 0, &j);

	अगर (!ret) अणु
		WRITE_ONCE(*(uदीर्घ *)kp->arg, (j > HZ) ? HZ : (j ?: 1));
		adjust_jअगरfies_till_sched_qs();
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops first_fqs_jअगरfies_ops = अणु
	.set = param_set_first_fqs_jअगरfies,
	.get = param_get_uदीर्घ,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops next_fqs_jअगरfies_ops = अणु
	.set = param_set_next_fqs_jअगरfies,
	.get = param_get_uदीर्घ,
पूर्ण;

module_param_cb(jअगरfies_till_first_fqs, &first_fqs_jअगरfies_ops, &jअगरfies_till_first_fqs, 0644);
module_param_cb(jअगरfies_till_next_fqs, &next_fqs_jअगरfies_ops, &jअगरfies_till_next_fqs, 0644);
module_param(rcu_kick_kthपढ़ोs, bool, 0644);

अटल व्योम क्रमce_qs_rnp(पूर्णांक (*f)(काष्ठा rcu_data *rdp));
अटल पूर्णांक rcu_pending(पूर्णांक user);

/*
 * Return the number of RCU GPs completed thus far क्रम debug & stats.
 */
अचिन्हित दीर्घ rcu_get_gp_seq(व्योम)
अणु
	वापस READ_ONCE(rcu_state.gp_seq);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_get_gp_seq);

/*
 * Return the number of RCU expedited batches completed thus far क्रम
 * debug & stats.  Odd numbers mean that a batch is in progress, even
 * numbers mean idle.  The value वापसed will thus be roughly द्विगुन
 * the cumulative batches since boot.
 */
अचिन्हित दीर्घ rcu_exp_batches_completed(व्योम)
अणु
	वापस rcu_state.expedited_sequence;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_exp_batches_completed);

/*
 * Return the root node of the rcu_state काष्ठाure.
 */
अटल काष्ठा rcu_node *rcu_get_root(व्योम)
अणु
	वापस &rcu_state.node[0];
पूर्ण

/*
 * Send aदीर्घ grace-period-related data क्रम rcutorture diagnostics.
 */
व्योम rcutorture_get_gp_data(क्रमागत rcutorture_type test_type, पूर्णांक *flags,
			    अचिन्हित दीर्घ *gp_seq)
अणु
	चयन (test_type) अणु
	हाल RCU_FLAVOR:
		*flags = READ_ONCE(rcu_state.gp_flags);
		*gp_seq = rcu_seq_current(&rcu_state.gp_seq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rcutorture_get_gp_data);

/*
 * Enter an RCU extended quiescent state, which can be either the
 * idle loop or adaptive-tickless usermode execution.
 *
 * We crowbar the ->dynticks_nmi_nesting field to zero to allow क्रम
 * the possibility of usermode upcalls having messed up our count
 * of पूर्णांकerrupt nesting level during the prior busy period.
 */
अटल noinstr व्योम rcu_eqs_enter(bool user)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	WARN_ON_ONCE(rdp->dynticks_nmi_nesting != DYNTICK_IRQ_NONIDLE);
	WRITE_ONCE(rdp->dynticks_nmi_nesting, 0);
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) &&
		     rdp->dynticks_nesting == 0);
	अगर (rdp->dynticks_nesting != 1) अणु
		// RCU will still be watching, so just करो accounting and leave.
		rdp->dynticks_nesting--;
		वापस;
	पूर्ण

	lockdep_निश्चित_irqs_disabled();
	instrumentation_begin();
	trace_rcu_dyntick(TPS("Start"), rdp->dynticks_nesting, 0, atomic_पढ़ो(&rdp->dynticks));
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) && !user && !is_idle_task(current));
	rcu_prepare_क्रम_idle();
	rcu_preempt_deferred_qs(current);

	// instrumentation क्रम the noinstr rcu_dynticks_eqs_enter()
	instrument_atomic_ग_लिखो(&rdp->dynticks, माप(rdp->dynticks));

	instrumentation_end();
	WRITE_ONCE(rdp->dynticks_nesting, 0); /* Aव्योम irq-access tearing. */
	// RCU is watching here ...
	rcu_dynticks_eqs_enter();
	// ... but is no दीर्घer watching here.
	rcu_dynticks_task_enter();
पूर्ण

/**
 * rcu_idle_enter - inक्रमm RCU that current CPU is entering idle
 *
 * Enter idle mode, in other words, -leave- the mode in which RCU
 * पढ़ो-side critical sections can occur.  (Though RCU पढ़ो-side
 * critical sections can occur in irq handlers in idle, a possibility
 * handled by irq_enter() and irq_निकास().)
 *
 * If you add or हटाओ a call to rcu_idle_enter(), be sure to test with
 * CONFIG_RCU_EQS_DEBUG=y.
 */
व्योम rcu_idle_enter(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	rcu_eqs_enter(false);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_idle_enter);

#अगर_घोषित CONFIG_NO_HZ_FULL

#अगर !defined(CONFIG_GENERIC_ENTRY) || !defined(CONFIG_KVM_XFER_TO_GUEST_WORK)
/*
 * An empty function that will trigger a reschedule on
 * IRQ tail once IRQs get re-enabled on userspace/guest resume.
 */
अटल व्योम late_wakeup_func(काष्ठा irq_work *work)
अणु
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा irq_work, late_wakeup_work) =
	IRQ_WORK_INIT(late_wakeup_func);

/*
 * If either:
 *
 * 1) the task is about to enter in guest mode and $ARCH करोesn't support KVM generic work
 * 2) the task is about to enter in user mode and $ARCH करोesn't support generic entry.
 *
 * In these हालs the late RCU wake ups aren't supported in the resched loops and our
 * last resort is to fire a local irq_work that will trigger a reschedule once IRQs
 * get re-enabled again.
 */
noinstr अटल व्योम rcu_irq_work_resched(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	अगर (IS_ENABLED(CONFIG_GENERIC_ENTRY) && !(current->flags & PF_VCPU))
		वापस;

	अगर (IS_ENABLED(CONFIG_KVM_XFER_TO_GUEST_WORK) && (current->flags & PF_VCPU))
		वापस;

	instrumentation_begin();
	अगर (करो_nocb_deferred_wakeup(rdp) && need_resched()) अणु
		irq_work_queue(this_cpu_ptr(&late_wakeup_work));
	पूर्ण
	instrumentation_end();
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम rcu_irq_work_resched(व्योम) अणु पूर्ण
#पूर्ण_अगर

/**
 * rcu_user_enter - inक्रमm RCU that we are resuming userspace.
 *
 * Enter RCU idle mode right beक्रमe resuming userspace.  No use of RCU
 * is permitted between this call and rcu_user_निकास(). This way the
 * CPU करोesn't need to मुख्यtain the tick क्रम RCU मुख्यtenance purposes
 * when the CPU runs in userspace.
 *
 * If you add or हटाओ a call to rcu_user_enter(), be sure to test with
 * CONFIG_RCU_EQS_DEBUG=y.
 */
noinstr व्योम rcu_user_enter(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();

	/*
	 * Other than generic entry implementation, we may be past the last
	 * rescheduling opportunity in the entry code. Trigger a self IPI
	 * that will fire and reschedule once we resume in user/guest mode.
	 */
	rcu_irq_work_resched();
	rcu_eqs_enter(true);
पूर्ण

#पूर्ण_अगर /* CONFIG_NO_HZ_FULL */

/**
 * rcu_nmi_निकास - inक्रमm RCU of निकास from NMI context
 *
 * If we are वापसing from the outermost NMI handler that पूर्णांकerrupted an
 * RCU-idle period, update rdp->dynticks and rdp->dynticks_nmi_nesting
 * to let the RCU grace-period handling know that the CPU is back to
 * being RCU-idle.
 *
 * If you add or हटाओ a call to rcu_nmi_निकास(), be sure to test
 * with CONFIG_RCU_EQS_DEBUG=y.
 */
noinstr व्योम rcu_nmi_निकास(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	instrumentation_begin();
	/*
	 * Check क्रम ->dynticks_nmi_nesting underflow and bad ->dynticks.
	 * (We are निकासing an NMI handler, so RCU better be paying attention
	 * to us!)
	 */
	WARN_ON_ONCE(rdp->dynticks_nmi_nesting <= 0);
	WARN_ON_ONCE(rcu_dynticks_curr_cpu_in_eqs());

	/*
	 * If the nesting level is not 1, the CPU wasn't RCU-idle, so
	 * leave it in non-RCU-idle state.
	 */
	अगर (rdp->dynticks_nmi_nesting != 1) अणु
		trace_rcu_dyntick(TPS("--="), rdp->dynticks_nmi_nesting, rdp->dynticks_nmi_nesting - 2,
				  atomic_पढ़ो(&rdp->dynticks));
		WRITE_ONCE(rdp->dynticks_nmi_nesting, /* No store tearing. */
			   rdp->dynticks_nmi_nesting - 2);
		instrumentation_end();
		वापस;
	पूर्ण

	/* This NMI पूर्णांकerrupted an RCU-idle CPU, restore RCU-idleness. */
	trace_rcu_dyntick(TPS("Startirq"), rdp->dynticks_nmi_nesting, 0, atomic_पढ़ो(&rdp->dynticks));
	WRITE_ONCE(rdp->dynticks_nmi_nesting, 0); /* Aव्योम store tearing. */

	अगर (!in_nmi())
		rcu_prepare_क्रम_idle();

	// instrumentation क्रम the noinstr rcu_dynticks_eqs_enter()
	instrument_atomic_ग_लिखो(&rdp->dynticks, माप(rdp->dynticks));
	instrumentation_end();

	// RCU is watching here ...
	rcu_dynticks_eqs_enter();
	// ... but is no दीर्घer watching here.

	अगर (!in_nmi())
		rcu_dynticks_task_enter();
पूर्ण

/**
 * rcu_irq_निकास - inक्रमm RCU that current CPU is निकासing irq towards idle
 *
 * Exit from an पूर्णांकerrupt handler, which might possibly result in entering
 * idle mode, in other words, leaving the mode in which पढ़ो-side critical
 * sections can occur.  The caller must have disabled पूर्णांकerrupts.
 *
 * This code assumes that the idle loop never करोes anything that might
 * result in unbalanced calls to irq_enter() and irq_निकास().  If your
 * architecture's idle loop violates this assumption, RCU will give you what
 * you deserve, good and hard.  But very infrequently and irreproducibly.
 *
 * Use things like work queues to work around this limitation.
 *
 * You have been warned.
 *
 * If you add or हटाओ a call to rcu_irq_निकास(), be sure to test with
 * CONFIG_RCU_EQS_DEBUG=y.
 */
व्योम noinstr rcu_irq_निकास(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	rcu_nmi_निकास();
पूर्ण

/**
 * rcu_irq_निकास_preempt - Inक्रमm RCU that current CPU is निकासing irq
 *			  towards in kernel preemption
 *
 * Same as rcu_irq_निकास() but has a sanity check that scheduling is safe
 * from RCU poपूर्णांक of view. Invoked from वापस from पूर्णांकerrupt beक्रमe kernel
 * preemption.
 */
व्योम rcu_irq_निकास_preempt(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	rcu_nmi_निकास();

	RCU_LOCKDEP_WARN(__this_cpu_पढ़ो(rcu_data.dynticks_nesting) <= 0,
			 "RCU dynticks_nesting counter underflow/zero!");
	RCU_LOCKDEP_WARN(__this_cpu_पढ़ो(rcu_data.dynticks_nmi_nesting) !=
			 DYNTICK_IRQ_NONIDLE,
			 "Bad RCU  dynticks_nmi_nesting counter\n");
	RCU_LOCKDEP_WARN(rcu_dynticks_curr_cpu_in_eqs(),
			 "RCU in extended quiescent state!");
पूर्ण

#अगर_घोषित CONFIG_PROVE_RCU
/**
 * rcu_irq_निकास_check_preempt - Validate that scheduling is possible
 */
व्योम rcu_irq_निकास_check_preempt(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();

	RCU_LOCKDEP_WARN(__this_cpu_पढ़ो(rcu_data.dynticks_nesting) <= 0,
			 "RCU dynticks_nesting counter underflow/zero!");
	RCU_LOCKDEP_WARN(__this_cpu_पढ़ो(rcu_data.dynticks_nmi_nesting) !=
			 DYNTICK_IRQ_NONIDLE,
			 "Bad RCU  dynticks_nmi_nesting counter\n");
	RCU_LOCKDEP_WARN(rcu_dynticks_curr_cpu_in_eqs(),
			 "RCU in extended quiescent state!");
पूर्ण
#पूर्ण_अगर /* #अगर_घोषित CONFIG_PROVE_RCU */

/*
 * Wrapper क्रम rcu_irq_निकास() where पूर्णांकerrupts are enabled.
 *
 * If you add or हटाओ a call to rcu_irq_निकास_irqson(), be sure to test
 * with CONFIG_RCU_EQS_DEBUG=y.
 */
व्योम rcu_irq_निकास_irqson(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	rcu_irq_निकास();
	local_irq_restore(flags);
पूर्ण

/*
 * Exit an RCU extended quiescent state, which can be either the
 * idle loop or adaptive-tickless usermode execution.
 *
 * We crowbar the ->dynticks_nmi_nesting field to DYNTICK_IRQ_NONIDLE to
 * allow क्रम the possibility of usermode upcalls messing up our count of
 * पूर्णांकerrupt nesting level during the busy period that is just now starting.
 */
अटल व्योम noinstr rcu_eqs_निकास(bool user)
अणु
	काष्ठा rcu_data *rdp;
	दीर्घ oldval;

	lockdep_निश्चित_irqs_disabled();
	rdp = this_cpu_ptr(&rcu_data);
	oldval = rdp->dynticks_nesting;
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) && oldval < 0);
	अगर (oldval) अणु
		// RCU was alपढ़ोy watching, so just करो accounting and leave.
		rdp->dynticks_nesting++;
		वापस;
	पूर्ण
	rcu_dynticks_task_निकास();
	// RCU is not watching here ...
	rcu_dynticks_eqs_निकास();
	// ... but is watching here.
	instrumentation_begin();

	// instrumentation क्रम the noinstr rcu_dynticks_eqs_निकास()
	instrument_atomic_ग_लिखो(&rdp->dynticks, माप(rdp->dynticks));

	rcu_cleanup_after_idle();
	trace_rcu_dyntick(TPS("End"), rdp->dynticks_nesting, 1, atomic_पढ़ो(&rdp->dynticks));
	WARN_ON_ONCE(IS_ENABLED(CONFIG_RCU_EQS_DEBUG) && !user && !is_idle_task(current));
	WRITE_ONCE(rdp->dynticks_nesting, 1);
	WARN_ON_ONCE(rdp->dynticks_nmi_nesting);
	WRITE_ONCE(rdp->dynticks_nmi_nesting, DYNTICK_IRQ_NONIDLE);
	instrumentation_end();
पूर्ण

/**
 * rcu_idle_निकास - inक्रमm RCU that current CPU is leaving idle
 *
 * Exit idle mode, in other words, -enter- the mode in which RCU
 * पढ़ो-side critical sections can occur.
 *
 * If you add or हटाओ a call to rcu_idle_निकास(), be sure to test with
 * CONFIG_RCU_EQS_DEBUG=y.
 */
व्योम rcu_idle_निकास(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	rcu_eqs_निकास(false);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_idle_निकास);

#अगर_घोषित CONFIG_NO_HZ_FULL
/**
 * rcu_user_निकास - inक्रमm RCU that we are निकासing userspace.
 *
 * Exit RCU idle mode जबतक entering the kernel because it can
 * run a RCU पढ़ो side critical section anyसमय.
 *
 * If you add or हटाओ a call to rcu_user_निकास(), be sure to test with
 * CONFIG_RCU_EQS_DEBUG=y.
 */
व्योम noinstr rcu_user_निकास(व्योम)
अणु
	rcu_eqs_निकास(1);
पूर्ण

/**
 * __rcu_irq_enter_check_tick - Enable scheduler tick on CPU अगर RCU needs it.
 *
 * The scheduler tick is not normally enabled when CPUs enter the kernel
 * from nohz_full userspace execution.  After all, nohz_full userspace
 * execution is an RCU quiescent state and the समय executing in the kernel
 * is quite लघु.  Except of course when it isn't.  And it is not hard to
 * cause a large प्रणाली to spend tens of seconds or even minutes looping
 * in the kernel, which can cause a number of problems, include RCU CPU
 * stall warnings.
 *
 * Thereक्रमe, अगर a nohz_full CPU fails to report a quiescent state
 * in a समयly manner, the RCU grace-period kthपढ़ो sets that CPU's
 * ->rcu_urgent_qs flag with the expectation that the next पूर्णांकerrupt or
 * exception will invoke this function, which will turn on the scheduler
 * tick, which will enable RCU to detect that CPU's quiescent states,
 * क्रम example, due to cond_resched() calls in CONFIG_PREEMPT=n kernels.
 * The tick will be disabled once a quiescent state is reported क्रम
 * this CPU.
 *
 * Of course, in carefully tuned प्रणालीs, there might never be an
 * पूर्णांकerrupt or exception.  In that हाल, the RCU grace-period kthपढ़ो
 * will eventually cause one to happen.  However, in less carefully
 * controlled environments, this function allows RCU to get what it
 * needs without creating otherwise useless पूर्णांकerruptions.
 */
व्योम __rcu_irq_enter_check_tick(व्योम)
अणु
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	// If we're here from NMI there's nothing to करो.
	अगर (in_nmi())
		वापस;

	RCU_LOCKDEP_WARN(rcu_dynticks_curr_cpu_in_eqs(),
			 "Illegal rcu_irq_enter_check_tick() from extended quiescent state");

	अगर (!tick_nohz_full_cpu(rdp->cpu) ||
	    !READ_ONCE(rdp->rcu_urgent_qs) ||
	    READ_ONCE(rdp->rcu_क्रमced_tick)) अणु
		// RCU करोesn't need nohz_full help from this CPU, or it is
		// alपढ़ोy getting that help.
		वापस;
	पूर्ण

	// We get here only when not in an extended quiescent state and
	// from पूर्णांकerrupts (as opposed to NMIs).  Thereक्रमe, (1) RCU is
	// alपढ़ोy watching and (2) The fact that we are in an पूर्णांकerrupt
	// handler and that the rcu_node lock is an irq-disabled lock
	// prevents self-deadlock.  So we can safely recheck under the lock.
	// Note that the nohz_full state currently cannot change.
	raw_spin_lock_rcu_node(rdp->mynode);
	अगर (rdp->rcu_urgent_qs && !rdp->rcu_क्रमced_tick) अणु
		// A nohz_full CPU is in the kernel and RCU needs a
		// quiescent state.  Turn on the tick!
		WRITE_ONCE(rdp->rcu_क्रमced_tick, true);
		tick_dep_set_cpu(rdp->cpu, TICK_DEP_BIT_RCU);
	पूर्ण
	raw_spin_unlock_rcu_node(rdp->mynode);
पूर्ण
#पूर्ण_अगर /* CONFIG_NO_HZ_FULL */

/**
 * rcu_nmi_enter - inक्रमm RCU of entry to NMI context
 *
 * If the CPU was idle from RCU's viewpoपूर्णांक, update rdp->dynticks and
 * rdp->dynticks_nmi_nesting to let the RCU grace-period handling know
 * that the CPU is active.  This implementation permits nested NMIs, as
 * दीर्घ as the nesting level करोes not overflow an पूर्णांक.  (You will probably
 * run out of stack space first.)
 *
 * If you add or हटाओ a call to rcu_nmi_enter(), be sure to test
 * with CONFIG_RCU_EQS_DEBUG=y.
 */
noinstr व्योम rcu_nmi_enter(व्योम)
अणु
	दीर्घ incby = 2;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	/* Complain about underflow. */
	WARN_ON_ONCE(rdp->dynticks_nmi_nesting < 0);

	/*
	 * If idle from RCU viewpoपूर्णांक, atomically increment ->dynticks
	 * to mark non-idle and increment ->dynticks_nmi_nesting by one.
	 * Otherwise, increment ->dynticks_nmi_nesting by two.  This means
	 * अगर ->dynticks_nmi_nesting is equal to one, we are guaranteed
	 * to be in the outermost NMI handler that पूर्णांकerrupted an RCU-idle
	 * period (observation due to Andy Lutomirski).
	 */
	अगर (rcu_dynticks_curr_cpu_in_eqs()) अणु

		अगर (!in_nmi())
			rcu_dynticks_task_निकास();

		// RCU is not watching here ...
		rcu_dynticks_eqs_निकास();
		// ... but is watching here.

		अगर (!in_nmi()) अणु
			instrumentation_begin();
			rcu_cleanup_after_idle();
			instrumentation_end();
		पूर्ण

		instrumentation_begin();
		// instrumentation क्रम the noinstr rcu_dynticks_curr_cpu_in_eqs()
		instrument_atomic_पढ़ो(&rdp->dynticks, माप(rdp->dynticks));
		// instrumentation क्रम the noinstr rcu_dynticks_eqs_निकास()
		instrument_atomic_ग_लिखो(&rdp->dynticks, माप(rdp->dynticks));

		incby = 1;
	पूर्ण अन्यथा अगर (!in_nmi()) अणु
		instrumentation_begin();
		rcu_irq_enter_check_tick();
	पूर्ण अन्यथा  अणु
		instrumentation_begin();
	पूर्ण

	trace_rcu_dyntick(incby == 1 ? TPS("Endirq") : TPS("++="),
			  rdp->dynticks_nmi_nesting,
			  rdp->dynticks_nmi_nesting + incby, atomic_पढ़ो(&rdp->dynticks));
	instrumentation_end();
	WRITE_ONCE(rdp->dynticks_nmi_nesting, /* Prevent store tearing. */
		   rdp->dynticks_nmi_nesting + incby);
	barrier();
पूर्ण

/**
 * rcu_irq_enter - inक्रमm RCU that current CPU is entering irq away from idle
 *
 * Enter an पूर्णांकerrupt handler, which might possibly result in निकासing
 * idle mode, in other words, entering the mode in which पढ़ो-side critical
 * sections can occur.  The caller must have disabled पूर्णांकerrupts.
 *
 * Note that the Linux kernel is fully capable of entering an पूर्णांकerrupt
 * handler that it never निकासs, क्रम example when करोing upcalls to user mode!
 * This code assumes that the idle loop never करोes upcalls to user mode.
 * If your architecture's idle loop करोes करो upcalls to user mode (or करोes
 * anything अन्यथा that results in unbalanced calls to the irq_enter() and
 * irq_निकास() functions), RCU will give you what you deserve, good and hard.
 * But very infrequently and irreproducibly.
 *
 * Use things like work queues to work around this limitation.
 *
 * You have been warned.
 *
 * If you add or हटाओ a call to rcu_irq_enter(), be sure to test with
 * CONFIG_RCU_EQS_DEBUG=y.
 */
noinstr व्योम rcu_irq_enter(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	rcu_nmi_enter();
पूर्ण

/*
 * Wrapper क्रम rcu_irq_enter() where पूर्णांकerrupts are enabled.
 *
 * If you add or हटाओ a call to rcu_irq_enter_irqson(), be sure to test
 * with CONFIG_RCU_EQS_DEBUG=y.
 */
व्योम rcu_irq_enter_irqson(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	rcu_irq_enter();
	local_irq_restore(flags);
पूर्ण

/*
 * If any sort of urgency was applied to the current CPU (क्रम example,
 * the scheduler-घड़ी पूर्णांकerrupt was enabled on a nohz_full CPU) in order
 * to get to a quiescent state, disable it.
 */
अटल व्योम rcu_disable_urgency_upon_qs(काष्ठा rcu_data *rdp)
अणु
	raw_lockdep_निश्चित_held_rcu_node(rdp->mynode);
	WRITE_ONCE(rdp->rcu_urgent_qs, false);
	WRITE_ONCE(rdp->rcu_need_heavy_qs, false);
	अगर (tick_nohz_full_cpu(rdp->cpu) && rdp->rcu_क्रमced_tick) अणु
		tick_dep_clear_cpu(rdp->cpu, TICK_DEP_BIT_RCU);
		WRITE_ONCE(rdp->rcu_क्रमced_tick, false);
	पूर्ण
पूर्ण

/**
 * rcu_is_watching - see अगर RCU thinks that the current CPU is not idle
 *
 * Return true अगर RCU is watching the running CPU, which means that this
 * CPU can safely enter RCU पढ़ो-side critical sections.  In other words,
 * अगर the current CPU is not in its idle loop or is in an पूर्णांकerrupt or
 * NMI handler, वापस true.
 *
 * Make notrace because it can be called by the पूर्णांकernal functions of
 * ftrace, and making this notrace हटाओs unnecessary recursion calls.
 */
notrace bool rcu_is_watching(व्योम)
अणु
	bool ret;

	preempt_disable_notrace();
	ret = !rcu_dynticks_curr_cpu_in_eqs();
	preempt_enable_notrace();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_is_watching);

/*
 * If a holकरोut task is actually running, request an urgent quiescent
 * state from its CPU.  This is unsynchronized, so migrations can cause
 * the request to go to the wrong CPU.  Which is OK, all that will happen
 * is that the CPU's next context चयन will be a bit slower and next
 * समय around this task will generate another request.
 */
व्योम rcu_request_urgent_qs_task(काष्ठा task_काष्ठा *t)
अणु
	पूर्णांक cpu;

	barrier();
	cpu = task_cpu(t);
	अगर (!task_curr(t))
		वापस; /* This task is not running on that CPU. */
	smp_store_release(per_cpu_ptr(&rcu_data.rcu_urgent_qs, cpu), true);
पूर्ण

#अगर defined(CONFIG_PROVE_RCU) && defined(CONFIG_HOTPLUG_CPU)

/*
 * Is the current CPU online as far as RCU is concerned?
 *
 * Disable preemption to aव्योम false positives that could otherwise
 * happen due to the current CPU number being sampled, this task being
 * preempted, its old CPU being taken offline, resuming on some other CPU,
 * then determining that its old CPU is now offline.
 *
 * Disable checking अगर in an NMI handler because we cannot safely
 * report errors from NMI handlers anyway.  In addition, it is OK to use
 * RCU on an offline processor during initial boot, hence the check क्रम
 * rcu_scheduler_fully_active.
 */
bool rcu_lockdep_current_cpu_online(व्योम)
अणु
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;
	bool ret = false;

	अगर (in_nmi() || !rcu_scheduler_fully_active)
		वापस true;
	preempt_disable_notrace();
	rdp = this_cpu_ptr(&rcu_data);
	rnp = rdp->mynode;
	अगर (rdp->grpmask & rcu_rnp_online_cpus(rnp) || READ_ONCE(rnp->ofl_seq) & 0x1)
		ret = true;
	preempt_enable_notrace();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rcu_lockdep_current_cpu_online);

#पूर्ण_अगर /* #अगर defined(CONFIG_PROVE_RCU) && defined(CONFIG_HOTPLUG_CPU) */

/*
 * We are reporting a quiescent state on behalf of some other CPU, so
 * it is our responsibility to check क्रम and handle potential overflow
 * of the rcu_node ->gp_seq counter with respect to the rcu_data counters.
 * After all, the CPU might be in deep idle state, and thus executing no
 * code whatsoever.
 */
अटल व्योम rcu_gpnum_ovf(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp)
अणु
	raw_lockdep_निश्चित_held_rcu_node(rnp);
	अगर (ULONG_CMP_LT(rcu_seq_current(&rdp->gp_seq) + अच_दीर्घ_उच्च / 4,
			 rnp->gp_seq))
		WRITE_ONCE(rdp->gpwrap, true);
	अगर (ULONG_CMP_LT(rdp->rcu_iw_gp_seq + अच_दीर्घ_उच्च / 4, rnp->gp_seq))
		rdp->rcu_iw_gp_seq = rnp->gp_seq + अच_दीर्घ_उच्च / 4;
पूर्ण

/*
 * Snapshot the specअगरied CPU's dynticks counter so that we can later
 * credit them with an implicit quiescent state.  Return 1 अगर this CPU
 * is in dynticks idle mode, which is an extended quiescent state.
 */
अटल पूर्णांक dyntick_save_progress_counter(काष्ठा rcu_data *rdp)
अणु
	rdp->dynticks_snap = rcu_dynticks_snap(rdp);
	अगर (rcu_dynticks_in_eqs(rdp->dynticks_snap)) अणु
		trace_rcu_fqs(rcu_state.name, rdp->gp_seq, rdp->cpu, TPS("dti"));
		rcu_gpnum_ovf(rdp->mynode, rdp);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return true अगर the specअगरied CPU has passed through a quiescent
 * state by virtue of being in or having passed through an dynticks
 * idle state since the last call to dyntick_save_progress_counter()
 * क्रम this same CPU, or by virtue of having been offline.
 */
अटल पूर्णांक rcu_implicit_dynticks_qs(काष्ठा rcu_data *rdp)
अणु
	अचिन्हित दीर्घ jtsq;
	bool *rnhqp;
	bool *ruqp;
	काष्ठा rcu_node *rnp = rdp->mynode;

	/*
	 * If the CPU passed through or entered a dynticks idle phase with
	 * no active irq/NMI handlers, then we can safely pretend that the CPU
	 * alपढ़ोy acknowledged the request to pass through a quiescent
	 * state.  Either way, that CPU cannot possibly be in an RCU
	 * पढ़ो-side critical section that started beक्रमe the beginning
	 * of the current RCU grace period.
	 */
	अगर (rcu_dynticks_in_eqs_since(rdp, rdp->dynticks_snap)) अणु
		trace_rcu_fqs(rcu_state.name, rdp->gp_seq, rdp->cpu, TPS("dti"));
		rcu_gpnum_ovf(rnp, rdp);
		वापस 1;
	पूर्ण

	/*
	 * Complain अगर a CPU that is considered to be offline from RCU's
	 * perspective has not yet reported a quiescent state.  After all,
	 * the offline CPU should have reported a quiescent state during
	 * the CPU-offline process, or, failing that, by rcu_gp_init()
	 * अगर it ran concurrently with either the CPU going offline or the
	 * last task on a leaf rcu_node काष्ठाure निकासing its RCU पढ़ो-side
	 * critical section जबतक all CPUs corresponding to that काष्ठाure
	 * are offline.  This added warning detects bugs in any of these
	 * code paths.
	 *
	 * The rcu_node काष्ठाure's ->lock is held here, which excludes
	 * the relevant portions the CPU-hotplug code, the grace-period
	 * initialization code, and the rcu_पढ़ो_unlock() code paths.
	 *
	 * For more detail, please refer to the "Hotplug CPU" section
	 * of RCU's Requirements करोcumentation.
	 */
	अगर (WARN_ON_ONCE(!(rdp->grpmask & rcu_rnp_online_cpus(rnp)))) अणु
		bool onl;
		काष्ठा rcu_node *rnp1;

		pr_info("%s: grp: %d-%d level: %d ->gp_seq %ld ->completedqs %ld\n",
			__func__, rnp->grplo, rnp->grphi, rnp->level,
			(दीर्घ)rnp->gp_seq, (दीर्घ)rnp->completedqs);
		क्रम (rnp1 = rnp; rnp1; rnp1 = rnp1->parent)
			pr_info("%s: %d:%d ->qsmask %#lx ->qsmaskinit %#lx ->qsmaskinitnext %#lx ->rcu_gp_init_mask %#lx\n",
				__func__, rnp1->grplo, rnp1->grphi, rnp1->qsmask, rnp1->qsmaskinit, rnp1->qsmaskinitnext, rnp1->rcu_gp_init_mask);
		onl = !!(rdp->grpmask & rcu_rnp_online_cpus(rnp));
		pr_info("%s %d: %c online: %ld(%d) offline: %ld(%d)\n",
			__func__, rdp->cpu, ".o"[onl],
			(दीर्घ)rdp->rcu_onl_gp_seq, rdp->rcu_onl_gp_flags,
			(दीर्घ)rdp->rcu_ofl_gp_seq, rdp->rcu_ofl_gp_flags);
		वापस 1; /* Break things loose after complaining. */
	पूर्ण

	/*
	 * A CPU running क्रम an extended समय within the kernel can
	 * delay RCU grace periods: (1) At age jअगरfies_to_sched_qs,
	 * set .rcu_urgent_qs, (2) At age 2*jअगरfies_to_sched_qs, set
	 * both .rcu_need_heavy_qs and .rcu_urgent_qs.  Note that the
	 * unsynchronized assignments to the per-CPU rcu_need_heavy_qs
	 * variable are safe because the assignments are repeated अगर this
	 * CPU failed to pass through a quiescent state.  This code
	 * also checks .jअगरfies_resched in हाल jअगरfies_to_sched_qs
	 * is set way high.
	 */
	jtsq = READ_ONCE(jअगरfies_to_sched_qs);
	ruqp = per_cpu_ptr(&rcu_data.rcu_urgent_qs, rdp->cpu);
	rnhqp = &per_cpu(rcu_data.rcu_need_heavy_qs, rdp->cpu);
	अगर (!READ_ONCE(*rnhqp) &&
	    (समय_after(jअगरfies, rcu_state.gp_start + jtsq * 2) ||
	     समय_after(jअगरfies, rcu_state.jअगरfies_resched) ||
	     rcu_state.cbovld)) अणु
		WRITE_ONCE(*rnhqp, true);
		/* Store rcu_need_heavy_qs beक्रमe rcu_urgent_qs. */
		smp_store_release(ruqp, true);
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, rcu_state.gp_start + jtsq)) अणु
		WRITE_ONCE(*ruqp, true);
	पूर्ण

	/*
	 * NO_HZ_FULL CPUs can run in-kernel without rcu_sched_घड़ी_irq!
	 * The above code handles this, but only क्रम straight cond_resched().
	 * And some in-kernel loops check need_resched() beक्रमe calling
	 * cond_resched(), which defeats the above code क्रम CPUs that are
	 * running in-kernel with scheduling-घड़ी पूर्णांकerrupts disabled.
	 * So hit them over the head with the resched_cpu() hammer!
	 */
	अगर (tick_nohz_full_cpu(rdp->cpu) &&
	    (समय_after(jअगरfies, READ_ONCE(rdp->last_fqs_resched) + jtsq * 3) ||
	     rcu_state.cbovld)) अणु
		WRITE_ONCE(*ruqp, true);
		resched_cpu(rdp->cpu);
		WRITE_ONCE(rdp->last_fqs_resched, jअगरfies);
	पूर्ण

	/*
	 * If more than halfway to RCU CPU stall-warning समय, invoke
	 * resched_cpu() more frequently to try to loosen things up a bit.
	 * Also check to see अगर the CPU is getting hammered with पूर्णांकerrupts,
	 * but only once per grace period, just to keep the IPIs करोwn to
	 * a dull roar.
	 */
	अगर (समय_after(jअगरfies, rcu_state.jअगरfies_resched)) अणु
		अगर (समय_after(jअगरfies,
			       READ_ONCE(rdp->last_fqs_resched) + jtsq)) अणु
			resched_cpu(rdp->cpu);
			WRITE_ONCE(rdp->last_fqs_resched, jअगरfies);
		पूर्ण
		अगर (IS_ENABLED(CONFIG_IRQ_WORK) &&
		    !rdp->rcu_iw_pending && rdp->rcu_iw_gp_seq != rnp->gp_seq &&
		    (rnp->ffmask & rdp->grpmask)) अणु
			rdp->rcu_iw_pending = true;
			rdp->rcu_iw_gp_seq = rnp->gp_seq;
			irq_work_queue_on(&rdp->rcu_iw, rdp->cpu);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Trace-event wrapper function क्रम trace_rcu_future_grace_period.  */
अटल व्योम trace_rcu_this_gp(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp,
			      अचिन्हित दीर्घ gp_seq_req, स्थिर अक्षर *s)
अणु
	trace_rcu_future_grace_period(rcu_state.name, READ_ONCE(rnp->gp_seq),
				      gp_seq_req, rnp->level,
				      rnp->grplo, rnp->grphi, s);
पूर्ण

/*
 * rcu_start_this_gp - Request the start of a particular grace period
 * @rnp_start: The leaf node of the CPU from which to start.
 * @rdp: The rcu_data corresponding to the CPU from which to start.
 * @gp_seq_req: The gp_seq of the grace period to start.
 *
 * Start the specअगरied grace period, as needed to handle newly arrived
 * callbacks.  The required future grace periods are recorded in each
 * rcu_node काष्ठाure's ->gp_seq_needed field.  Returns true अगर there
 * is reason to awaken the grace-period kthपढ़ो.
 *
 * The caller must hold the specअगरied rcu_node काष्ठाure's ->lock, which
 * is why the caller is responsible क्रम waking the grace-period kthपढ़ो.
 *
 * Returns true अगर the GP thपढ़ो needs to be awakened अन्यथा false.
 */
अटल bool rcu_start_this_gp(काष्ठा rcu_node *rnp_start, काष्ठा rcu_data *rdp,
			      अचिन्हित दीर्घ gp_seq_req)
अणु
	bool ret = false;
	काष्ठा rcu_node *rnp;

	/*
	 * Use funnel locking to either acquire the root rcu_node
	 * काष्ठाure's lock or bail out अगर the need क्रम this grace period
	 * has alपढ़ोy been recorded -- or अगर that grace period has in
	 * fact alपढ़ोy started.  If there is alपढ़ोy a grace period in
	 * progress in a non-leaf node, no recording is needed because the
	 * end of the grace period will scan the leaf rcu_node काष्ठाures.
	 * Note that rnp_start->lock must not be released.
	 */
	raw_lockdep_निश्चित_held_rcu_node(rnp_start);
	trace_rcu_this_gp(rnp_start, rdp, gp_seq_req, TPS("Startleaf"));
	क्रम (rnp = rnp_start; 1; rnp = rnp->parent) अणु
		अगर (rnp != rnp_start)
			raw_spin_lock_rcu_node(rnp);
		अगर (ULONG_CMP_GE(rnp->gp_seq_needed, gp_seq_req) ||
		    rcu_seq_started(&rnp->gp_seq, gp_seq_req) ||
		    (rnp != rnp_start &&
		     rcu_seq_state(rcu_seq_current(&rnp->gp_seq)))) अणु
			trace_rcu_this_gp(rnp, rdp, gp_seq_req,
					  TPS("Prestarted"));
			जाओ unlock_out;
		पूर्ण
		WRITE_ONCE(rnp->gp_seq_needed, gp_seq_req);
		अगर (rcu_seq_state(rcu_seq_current(&rnp->gp_seq))) अणु
			/*
			 * We just marked the leaf or पूर्णांकernal node, and a
			 * grace period is in progress, which means that
			 * rcu_gp_cleanup() will see the marking.  Bail to
			 * reduce contention.
			 */
			trace_rcu_this_gp(rnp_start, rdp, gp_seq_req,
					  TPS("Startedleaf"));
			जाओ unlock_out;
		पूर्ण
		अगर (rnp != rnp_start && rnp->parent != शून्य)
			raw_spin_unlock_rcu_node(rnp);
		अगर (!rnp->parent)
			अवरोध;  /* At root, and perhaps also leaf. */
	पूर्ण

	/* If GP alपढ़ोy in progress, just leave, otherwise start one. */
	अगर (rcu_gp_in_progress()) अणु
		trace_rcu_this_gp(rnp, rdp, gp_seq_req, TPS("Startedleafroot"));
		जाओ unlock_out;
	पूर्ण
	trace_rcu_this_gp(rnp, rdp, gp_seq_req, TPS("Startedroot"));
	WRITE_ONCE(rcu_state.gp_flags, rcu_state.gp_flags | RCU_GP_FLAG_INIT);
	WRITE_ONCE(rcu_state.gp_req_activity, jअगरfies);
	अगर (!READ_ONCE(rcu_state.gp_kthपढ़ो)) अणु
		trace_rcu_this_gp(rnp, rdp, gp_seq_req, TPS("NoGPkthread"));
		जाओ unlock_out;
	पूर्ण
	trace_rcu_grace_period(rcu_state.name, data_race(rcu_state.gp_seq), TPS("newreq"));
	ret = true;  /* Caller must wake GP kthपढ़ो. */
unlock_out:
	/* Push furthest requested GP to leaf node and rcu_data काष्ठाure. */
	अगर (ULONG_CMP_LT(gp_seq_req, rnp->gp_seq_needed)) अणु
		WRITE_ONCE(rnp_start->gp_seq_needed, rnp->gp_seq_needed);
		WRITE_ONCE(rdp->gp_seq_needed, rnp->gp_seq_needed);
	पूर्ण
	अगर (rnp != rnp_start)
		raw_spin_unlock_rcu_node(rnp);
	वापस ret;
पूर्ण

/*
 * Clean up any old requests क्रम the just-ended grace period.  Also वापस
 * whether any additional grace periods have been requested.
 */
अटल bool rcu_future_gp_cleanup(काष्ठा rcu_node *rnp)
अणु
	bool needmore;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);

	needmore = ULONG_CMP_LT(rnp->gp_seq, rnp->gp_seq_needed);
	अगर (!needmore)
		rnp->gp_seq_needed = rnp->gp_seq; /* Aव्योम counter wrap. */
	trace_rcu_this_gp(rnp, rdp, rnp->gp_seq,
			  needmore ? TPS("CleanupMore") : TPS("Cleanup"));
	वापस needmore;
पूर्ण

/*
 * Awaken the grace-period kthपढ़ो.  Don't करो a self-awaken (unless in an
 * पूर्णांकerrupt or softirq handler, in which हाल we just might immediately
 * sleep upon वापस, resulting in a grace-period hang), and करोn't bother
 * awakening when there is nothing क्रम the grace-period kthपढ़ो to करो
 * (as in several CPUs raced to awaken, we lost), and finally करोn't try
 * to awaken a kthपढ़ो that has not yet been created.  If all those checks
 * are passed, track some debug inक्रमmation and awaken.
 *
 * So why करो the self-wakeup when in an पूर्णांकerrupt or softirq handler
 * in the grace-period kthपढ़ो's context?  Because the kthपढ़ो might have
 * been पूर्णांकerrupted just as it was going to sleep, and just after the final
 * pre-sleep check of the awaken condition.  In this हाल, a wakeup really
 * is required, and is thereक्रमe supplied.
 */
अटल व्योम rcu_gp_kthपढ़ो_wake(व्योम)
अणु
	काष्ठा task_काष्ठा *t = READ_ONCE(rcu_state.gp_kthपढ़ो);

	अगर ((current == t && !in_irq() && !in_serving_softirq()) ||
	    !READ_ONCE(rcu_state.gp_flags) || !t)
		वापस;
	WRITE_ONCE(rcu_state.gp_wake_समय, jअगरfies);
	WRITE_ONCE(rcu_state.gp_wake_seq, READ_ONCE(rcu_state.gp_seq));
	swake_up_one(&rcu_state.gp_wq);
पूर्ण

/*
 * If there is room, assign a ->gp_seq number to any callbacks on this
 * CPU that have not alपढ़ोy been asचिन्हित.  Also accelerate any callbacks
 * that were previously asचिन्हित a ->gp_seq number that has since proven
 * to be too conservative, which can happen अगर callbacks get asचिन्हित a
 * ->gp_seq number जबतक RCU is idle, but with reference to a non-root
 * rcu_node काष्ठाure.  This function is idempotent, so it करोes not hurt
 * to call it repeatedly.  Returns an flag saying that we should awaken
 * the RCU grace-period kthपढ़ो.
 *
 * The caller must hold rnp->lock with पूर्णांकerrupts disabled.
 */
अटल bool rcu_accelerate_cbs(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp)
अणु
	अचिन्हित दीर्घ gp_seq_req;
	bool ret = false;

	rcu_lockdep_निश्चित_cblist_रक्षित(rdp);
	raw_lockdep_निश्चित_held_rcu_node(rnp);

	/* If no pending (not yet पढ़ोy to invoke) callbacks, nothing to करो. */
	अगर (!rcu_segcblist_pend_cbs(&rdp->cblist))
		वापस false;

	trace_rcu_segcb_stats(&rdp->cblist, TPS("SegCbPreAcc"));

	/*
	 * Callbacks are often रेजिस्टरed with incomplete grace-period
	 * inक्रमmation.  Something about the fact that getting exact
	 * inक्रमmation requires acquiring a global lock...  RCU thereक्रमe
	 * makes a conservative estimate of the grace period number at which
	 * a given callback will become पढ़ोy to invoke.	The following
	 * code checks this estimate and improves it when possible, thus
	 * accelerating callback invocation to an earlier grace-period
	 * number.
	 */
	gp_seq_req = rcu_seq_snap(&rcu_state.gp_seq);
	अगर (rcu_segcblist_accelerate(&rdp->cblist, gp_seq_req))
		ret = rcu_start_this_gp(rnp, rdp, gp_seq_req);

	/* Trace depending on how much we were able to accelerate. */
	अगर (rcu_segcblist_restempty(&rdp->cblist, RCU_WAIT_TAIL))
		trace_rcu_grace_period(rcu_state.name, gp_seq_req, TPS("AccWaitCB"));
	अन्यथा
		trace_rcu_grace_period(rcu_state.name, gp_seq_req, TPS("AccReadyCB"));

	trace_rcu_segcb_stats(&rdp->cblist, TPS("SegCbPostAcc"));

	वापस ret;
पूर्ण

/*
 * Similar to rcu_accelerate_cbs(), but करोes not require that the leaf
 * rcu_node काष्ठाure's ->lock be held.  It consults the cached value
 * of ->gp_seq_needed in the rcu_data काष्ठाure, and अगर that indicates
 * that a new grace-period request be made, invokes rcu_accelerate_cbs()
 * जबतक holding the leaf rcu_node काष्ठाure's ->lock.
 */
अटल व्योम rcu_accelerate_cbs_unlocked(काष्ठा rcu_node *rnp,
					काष्ठा rcu_data *rdp)
अणु
	अचिन्हित दीर्घ c;
	bool needwake;

	rcu_lockdep_निश्चित_cblist_रक्षित(rdp);
	c = rcu_seq_snap(&rcu_state.gp_seq);
	अगर (!READ_ONCE(rdp->gpwrap) && ULONG_CMP_GE(rdp->gp_seq_needed, c)) अणु
		/* Old request still live, so mark recent callbacks. */
		(व्योम)rcu_segcblist_accelerate(&rdp->cblist, c);
		वापस;
	पूर्ण
	raw_spin_lock_rcu_node(rnp); /* irqs alपढ़ोy disabled. */
	needwake = rcu_accelerate_cbs(rnp, rdp);
	raw_spin_unlock_rcu_node(rnp); /* irqs reमुख्य disabled. */
	अगर (needwake)
		rcu_gp_kthपढ़ो_wake();
पूर्ण

/*
 * Move any callbacks whose grace period has completed to the
 * RCU_DONE_TAIL sublist, then compact the reमुख्यing sublists and
 * assign ->gp_seq numbers to any callbacks in the RCU_NEXT_TAIL
 * sublist.  This function is idempotent, so it करोes not hurt to
 * invoke it repeatedly.  As दीर्घ as it is not invoked -too- often...
 * Returns true अगर the RCU grace-period kthपढ़ो needs to be awakened.
 *
 * The caller must hold rnp->lock with पूर्णांकerrupts disabled.
 */
अटल bool rcu_advance_cbs(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp)
अणु
	rcu_lockdep_निश्चित_cblist_रक्षित(rdp);
	raw_lockdep_निश्चित_held_rcu_node(rnp);

	/* If no pending (not yet पढ़ोy to invoke) callbacks, nothing to करो. */
	अगर (!rcu_segcblist_pend_cbs(&rdp->cblist))
		वापस false;

	/*
	 * Find all callbacks whose ->gp_seq numbers indicate that they
	 * are पढ़ोy to invoke, and put them पूर्णांकo the RCU_DONE_TAIL sublist.
	 */
	rcu_segcblist_advance(&rdp->cblist, rnp->gp_seq);

	/* Classअगरy any reमुख्यing callbacks. */
	वापस rcu_accelerate_cbs(rnp, rdp);
पूर्ण

/*
 * Move and classअगरy callbacks, but only अगर करोing so won't require
 * that the RCU grace-period kthपढ़ो be awakened.
 */
अटल व्योम __maybe_unused rcu_advance_cbs_nowake(काष्ठा rcu_node *rnp,
						  काष्ठा rcu_data *rdp)
अणु
	rcu_lockdep_निश्चित_cblist_रक्षित(rdp);
	अगर (!rcu_seq_state(rcu_seq_current(&rnp->gp_seq)) ||
	    !raw_spin_trylock_rcu_node(rnp))
		वापस;
	WARN_ON_ONCE(rcu_advance_cbs(rnp, rdp));
	raw_spin_unlock_rcu_node(rnp);
पूर्ण

/*
 * In CONFIG_RCU_STRICT_GRACE_PERIOD=y kernels, attempt to generate a
 * quiescent state.  This is पूर्णांकended to be invoked when the CPU notices
 * a new grace period.
 */
अटल व्योम rcu_strict_gp_check_qs(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD)) अणु
		rcu_पढ़ो_lock();
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/*
 * Update CPU-local rcu_data state to record the beginnings and ends of
 * grace periods.  The caller must hold the ->lock of the leaf rcu_node
 * काष्ठाure corresponding to the current CPU, and must have irqs disabled.
 * Returns true अगर the grace-period kthपढ़ो needs to be awakened.
 */
अटल bool __note_gp_changes(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp)
अणु
	bool ret = false;
	bool need_qs;
	स्थिर bool offloaded = rcu_rdp_is_offloaded(rdp);

	raw_lockdep_निश्चित_held_rcu_node(rnp);

	अगर (rdp->gp_seq == rnp->gp_seq)
		वापस false; /* Nothing to करो. */

	/* Handle the ends of any preceding grace periods first. */
	अगर (rcu_seq_completed_gp(rdp->gp_seq, rnp->gp_seq) ||
	    unlikely(READ_ONCE(rdp->gpwrap))) अणु
		अगर (!offloaded)
			ret = rcu_advance_cbs(rnp, rdp); /* Advance CBs. */
		rdp->core_needs_qs = false;
		trace_rcu_grace_period(rcu_state.name, rdp->gp_seq, TPS("cpuend"));
	पूर्ण अन्यथा अणु
		अगर (!offloaded)
			ret = rcu_accelerate_cbs(rnp, rdp); /* Recent CBs. */
		अगर (rdp->core_needs_qs)
			rdp->core_needs_qs = !!(rnp->qsmask & rdp->grpmask);
	पूर्ण

	/* Now handle the beginnings of any new-to-this-CPU grace periods. */
	अगर (rcu_seq_new_gp(rdp->gp_seq, rnp->gp_seq) ||
	    unlikely(READ_ONCE(rdp->gpwrap))) अणु
		/*
		 * If the current grace period is रुकोing क्रम this CPU,
		 * set up to detect a quiescent state, otherwise करोn't
		 * go looking क्रम one.
		 */
		trace_rcu_grace_period(rcu_state.name, rnp->gp_seq, TPS("cpustart"));
		need_qs = !!(rnp->qsmask & rdp->grpmask);
		rdp->cpu_no_qs.b.norm = need_qs;
		rdp->core_needs_qs = need_qs;
		zero_cpu_stall_ticks(rdp);
	पूर्ण
	rdp->gp_seq = rnp->gp_seq;  /* Remember new grace-period state. */
	अगर (ULONG_CMP_LT(rdp->gp_seq_needed, rnp->gp_seq_needed) || rdp->gpwrap)
		WRITE_ONCE(rdp->gp_seq_needed, rnp->gp_seq_needed);
	WRITE_ONCE(rdp->gpwrap, false);
	rcu_gpnum_ovf(rnp, rdp);
	वापस ret;
पूर्ण

अटल व्योम note_gp_changes(काष्ठा rcu_data *rdp)
अणु
	अचिन्हित दीर्घ flags;
	bool needwake;
	काष्ठा rcu_node *rnp;

	local_irq_save(flags);
	rnp = rdp->mynode;
	अगर ((rdp->gp_seq == rcu_seq_current(&rnp->gp_seq) &&
	     !unlikely(READ_ONCE(rdp->gpwrap))) || /* w/out lock. */
	    !raw_spin_trylock_rcu_node(rnp)) अणु /* irqs alपढ़ोy off, so later. */
		local_irq_restore(flags);
		वापस;
	पूर्ण
	needwake = __note_gp_changes(rnp, rdp);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	rcu_strict_gp_check_qs();
	अगर (needwake)
		rcu_gp_kthपढ़ो_wake();
पूर्ण

अटल व्योम rcu_gp_slow(पूर्णांक delay)
अणु
	अगर (delay > 0 &&
	    !(rcu_seq_ctr(rcu_state.gp_seq) %
	      (rcu_num_nodes * PER_RCU_NODE_PERIOD * delay)))
		schedule_समयout_idle(delay);
पूर्ण

अटल अचिन्हित दीर्घ sleep_duration;

/* Allow rcutorture to stall the grace-period kthपढ़ो. */
व्योम rcu_gp_set_torture_रुको(पूर्णांक duration)
अणु
	अगर (IS_ENABLED(CONFIG_RCU_TORTURE_TEST) && duration > 0)
		WRITE_ONCE(sleep_duration, duration);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_gp_set_torture_रुको);

/* Actually implement the aक्रमementioned रुको. */
अटल व्योम rcu_gp_torture_रुको(व्योम)
अणु
	अचिन्हित दीर्घ duration;

	अगर (!IS_ENABLED(CONFIG_RCU_TORTURE_TEST))
		वापस;
	duration = xchg(&sleep_duration, 0UL);
	अगर (duration > 0) अणु
		pr_alert("%s: Waiting %lu jiffies\n", __func__, duration);
		schedule_समयout_idle(duration);
		pr_alert("%s: Wait complete\n", __func__);
	पूर्ण
पूर्ण

/*
 * Handler क्रम on_each_cpu() to invoke the target CPU's RCU core
 * processing.
 */
अटल व्योम rcu_strict_gp_boundary(व्योम *unused)
अणु
	invoke_rcu_core();
पूर्ण

/*
 * Initialize a new grace period.  Return false अगर no grace period required.
 */
अटल bool rcu_gp_init(व्योम)
अणु
	अचिन्हित दीर्घ firstseq;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ oldmask;
	अचिन्हित दीर्घ mask;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp = rcu_get_root();

	WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
	raw_spin_lock_irq_rcu_node(rnp);
	अगर (!READ_ONCE(rcu_state.gp_flags)) अणु
		/* Spurious wakeup, tell caller to go back to sleep.  */
		raw_spin_unlock_irq_rcu_node(rnp);
		वापस false;
	पूर्ण
	WRITE_ONCE(rcu_state.gp_flags, 0); /* Clear all flags: New GP. */

	अगर (WARN_ON_ONCE(rcu_gp_in_progress())) अणु
		/*
		 * Grace period alपढ़ोy in progress, करोn't start another.
		 * Not supposed to be able to happen.
		 */
		raw_spin_unlock_irq_rcu_node(rnp);
		वापस false;
	पूर्ण

	/* Advance to a new grace period and initialize state. */
	record_gp_stall_check_समय();
	/* Record GP बार beक्रमe starting GP, hence rcu_seq_start(). */
	rcu_seq_start(&rcu_state.gp_seq);
	ASSERT_EXCLUSIVE_WRITER(rcu_state.gp_seq);
	trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq, TPS("start"));
	raw_spin_unlock_irq_rcu_node(rnp);

	/*
	 * Apply per-leaf buffered online and offline operations to
	 * the rcu_node tree. Note that this new grace period need not
	 * रुको क्रम subsequent online CPUs, and that RCU hooks in the CPU
	 * offlining path, when combined with checks in this function,
	 * will handle CPUs that are currently going offline or that will
	 * go offline later.  Please also refer to "Hotplug CPU" section
	 * of RCU's Requirements करोcumentation.
	 */
	WRITE_ONCE(rcu_state.gp_state, RCU_GP_ONOFF);
	rcu_क्रम_each_leaf_node(rnp) अणु
		smp_mb(); // Pair with barriers used when updating ->ofl_seq to odd values.
		firstseq = READ_ONCE(rnp->ofl_seq);
		अगर (firstseq & 0x1)
			जबतक (firstseq == READ_ONCE(rnp->ofl_seq))
				schedule_समयout_idle(1);  // Can't wake unless RCU is watching.
		smp_mb(); // Pair with barriers used when updating ->ofl_seq to even values.
		raw_spin_lock(&rcu_state.ofl_lock);
		raw_spin_lock_irq_rcu_node(rnp);
		अगर (rnp->qsmaskinit == rnp->qsmaskinitnext &&
		    !rnp->रुको_blkd_tasks) अणु
			/* Nothing to करो on this leaf rcu_node काष्ठाure. */
			raw_spin_unlock_irq_rcu_node(rnp);
			raw_spin_unlock(&rcu_state.ofl_lock);
			जारी;
		पूर्ण

		/* Record old state, apply changes to ->qsmaskinit field. */
		oldmask = rnp->qsmaskinit;
		rnp->qsmaskinit = rnp->qsmaskinitnext;

		/* If zero-ness of ->qsmaskinit changed, propagate up tree. */
		अगर (!oldmask != !rnp->qsmaskinit) अणु
			अगर (!oldmask) अणु /* First online CPU क्रम rcu_node. */
				अगर (!rnp->रुको_blkd_tasks) /* Ever offline? */
					rcu_init_new_rnp(rnp);
			पूर्ण अन्यथा अगर (rcu_preempt_has_tasks(rnp)) अणु
				rnp->रुको_blkd_tasks = true; /* blocked tasks */
			पूर्ण अन्यथा अणु /* Last offline CPU and can propagate. */
				rcu_cleanup_dead_rnp(rnp);
			पूर्ण
		पूर्ण

		/*
		 * If all रुकोed-on tasks from prior grace period are
		 * करोne, and अगर all this rcu_node काष्ठाure's CPUs are
		 * still offline, propagate up the rcu_node tree and
		 * clear ->रुको_blkd_tasks.  Otherwise, अगर one of this
		 * rcu_node काष्ठाure's CPUs has since come back online,
		 * simply clear ->रुको_blkd_tasks.
		 */
		अगर (rnp->रुको_blkd_tasks &&
		    (!rcu_preempt_has_tasks(rnp) || rnp->qsmaskinit)) अणु
			rnp->रुको_blkd_tasks = false;
			अगर (!rnp->qsmaskinit)
				rcu_cleanup_dead_rnp(rnp);
		पूर्ण

		raw_spin_unlock_irq_rcu_node(rnp);
		raw_spin_unlock(&rcu_state.ofl_lock);
	पूर्ण
	rcu_gp_slow(gp_preinit_delay); /* Races with CPU hotplug. */

	/*
	 * Set the quiescent-state-needed bits in all the rcu_node
	 * काष्ठाures क्रम all currently online CPUs in bपढ़ोth-first
	 * order, starting from the root rcu_node काष्ठाure, relying on the
	 * layout of the tree within the rcu_state.node[] array.  Note that
	 * other CPUs will access only the leaves of the hierarchy, thus
	 * seeing that no grace period is in progress, at least until the
	 * corresponding leaf node has been initialized.
	 *
	 * The grace period cannot complete until the initialization
	 * process finishes, because this kthपढ़ो handles both.
	 */
	WRITE_ONCE(rcu_state.gp_state, RCU_GP_INIT);
	rcu_क्रम_each_node_bपढ़ोth_first(rnp) अणु
		rcu_gp_slow(gp_init_delay);
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		rdp = this_cpu_ptr(&rcu_data);
		rcu_preempt_check_blocked_tasks(rnp);
		rnp->qsmask = rnp->qsmaskinit;
		WRITE_ONCE(rnp->gp_seq, rcu_state.gp_seq);
		अगर (rnp == rdp->mynode)
			(व्योम)__note_gp_changes(rnp, rdp);
		rcu_preempt_boost_start_gp(rnp);
		trace_rcu_grace_period_init(rcu_state.name, rnp->gp_seq,
					    rnp->level, rnp->grplo,
					    rnp->grphi, rnp->qsmask);
		/* Quiescent states क्रम tasks on any now-offline CPUs. */
		mask = rnp->qsmask & ~rnp->qsmaskinitnext;
		rnp->rcu_gp_init_mask = mask;
		अगर ((mask || rnp->रुको_blkd_tasks) && rcu_is_leaf_node(rnp))
			rcu_report_qs_rnp(mask, rnp, rnp->gp_seq, flags);
		अन्यथा
			raw_spin_unlock_irq_rcu_node(rnp);
		cond_resched_tasks_rcu_qs();
		WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
	पूर्ण

	// If strict, make all CPUs aware of new grace period.
	अगर (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD))
		on_each_cpu(rcu_strict_gp_boundary, शून्य, 0);

	वापस true;
पूर्ण

/*
 * Helper function क्रम sरुको_event_idle_exclusive() wakeup at क्रमce-quiescent-state
 * समय.
 */
अटल bool rcu_gp_fqs_check_wake(पूर्णांक *gfp)
अणु
	काष्ठा rcu_node *rnp = rcu_get_root();

	// If under overload conditions, क्रमce an immediate FQS scan.
	अगर (*gfp & RCU_GP_FLAG_OVLD)
		वापस true;

	// Someone like call_rcu() requested a क्रमce-quiescent-state scan.
	*gfp = READ_ONCE(rcu_state.gp_flags);
	अगर (*gfp & RCU_GP_FLAG_FQS)
		वापस true;

	// The current grace period has completed.
	अगर (!READ_ONCE(rnp->qsmask) && !rcu_preempt_blocked_पढ़ोers_cgp(rnp))
		वापस true;

	वापस false;
पूर्ण

/*
 * Do one round of quiescent-state क्रमcing.
 */
अटल व्योम rcu_gp_fqs(bool first_समय)
अणु
	काष्ठा rcu_node *rnp = rcu_get_root();

	WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
	rcu_state.n_क्रमce_qs++;
	अगर (first_समय) अणु
		/* Collect dyntick-idle snapshots. */
		क्रमce_qs_rnp(dyntick_save_progress_counter);
	पूर्ण अन्यथा अणु
		/* Handle dyntick-idle and offline CPUs. */
		क्रमce_qs_rnp(rcu_implicit_dynticks_qs);
	पूर्ण
	/* Clear flag to prevent immediate re-entry. */
	अगर (READ_ONCE(rcu_state.gp_flags) & RCU_GP_FLAG_FQS) अणु
		raw_spin_lock_irq_rcu_node(rnp);
		WRITE_ONCE(rcu_state.gp_flags,
			   READ_ONCE(rcu_state.gp_flags) & ~RCU_GP_FLAG_FQS);
		raw_spin_unlock_irq_rcu_node(rnp);
	पूर्ण
पूर्ण

/*
 * Loop करोing repeated quiescent-state क्रमcing until the grace period ends.
 */
अटल व्योम rcu_gp_fqs_loop(व्योम)
अणु
	bool first_gp_fqs;
	पूर्णांक gf = 0;
	अचिन्हित दीर्घ j;
	पूर्णांक ret;
	काष्ठा rcu_node *rnp = rcu_get_root();

	first_gp_fqs = true;
	j = READ_ONCE(jअगरfies_till_first_fqs);
	अगर (rcu_state.cbovld)
		gf = RCU_GP_FLAG_OVLD;
	ret = 0;
	क्रम (;;) अणु
		अगर (!ret) अणु
			WRITE_ONCE(rcu_state.jअगरfies_क्रमce_qs, jअगरfies + j);
			/*
			 * jअगरfies_क्रमce_qs beक्रमe RCU_GP_WAIT_FQS state
			 * update; required क्रम stall checks.
			 */
			smp_wmb();
			WRITE_ONCE(rcu_state.jअगरfies_kick_kthपढ़ोs,
				   jअगरfies + (j ? 3 * j : 2));
		पूर्ण
		trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq,
				       TPS("fqswait"));
		WRITE_ONCE(rcu_state.gp_state, RCU_GP_WAIT_FQS);
		ret = sरुको_event_idle_समयout_exclusive(
				rcu_state.gp_wq, rcu_gp_fqs_check_wake(&gf), j);
		rcu_gp_torture_रुको();
		WRITE_ONCE(rcu_state.gp_state, RCU_GP_DOING_FQS);
		/* Locking provides needed memory barriers. */
		/* If grace period करोne, leave loop. */
		अगर (!READ_ONCE(rnp->qsmask) &&
		    !rcu_preempt_blocked_पढ़ोers_cgp(rnp))
			अवरोध;
		/* If समय क्रम quiescent-state क्रमcing, करो it. */
		अगर (!समय_after(rcu_state.jअगरfies_क्रमce_qs, jअगरfies) ||
		    (gf & (RCU_GP_FLAG_FQS | RCU_GP_FLAG_OVLD))) अणु
			trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq,
					       TPS("fqsstart"));
			rcu_gp_fqs(first_gp_fqs);
			gf = 0;
			अगर (first_gp_fqs) अणु
				first_gp_fqs = false;
				gf = rcu_state.cbovld ? RCU_GP_FLAG_OVLD : 0;
			पूर्ण
			trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq,
					       TPS("fqsend"));
			cond_resched_tasks_rcu_qs();
			WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
			ret = 0; /* Force full रुको till next FQS. */
			j = READ_ONCE(jअगरfies_till_next_fqs);
		पूर्ण अन्यथा अणु
			/* Deal with stray संकेत. */
			cond_resched_tasks_rcu_qs();
			WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
			WARN_ON(संकेत_pending(current));
			trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq,
					       TPS("fqswaitsig"));
			ret = 1; /* Keep old FQS timing. */
			j = jअगरfies;
			अगर (समय_after(jअगरfies, rcu_state.jअगरfies_क्रमce_qs))
				j = 1;
			अन्यथा
				j = rcu_state.jअगरfies_क्रमce_qs - j;
			gf = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Clean up after the old grace period.
 */
अटल व्योम rcu_gp_cleanup(व्योम)
अणु
	पूर्णांक cpu;
	bool needgp = false;
	अचिन्हित दीर्घ gp_duration;
	अचिन्हित दीर्घ new_gp_seq;
	bool offloaded;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp = rcu_get_root();
	काष्ठा sरुको_queue_head *sq;

	WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
	raw_spin_lock_irq_rcu_node(rnp);
	rcu_state.gp_end = jअगरfies;
	gp_duration = rcu_state.gp_end - rcu_state.gp_start;
	अगर (gp_duration > rcu_state.gp_max)
		rcu_state.gp_max = gp_duration;

	/*
	 * We know the grace period is complete, but to everyone अन्यथा
	 * it appears to still be ongoing.  But it is also the हाल
	 * that to everyone अन्यथा it looks like there is nothing that
	 * they can करो to advance the grace period.  It is thereक्रमe
	 * safe क्रम us to drop the lock in order to mark the grace
	 * period as completed in all of the rcu_node काष्ठाures.
	 */
	raw_spin_unlock_irq_rcu_node(rnp);

	/*
	 * Propagate new ->gp_seq value to rcu_node काष्ठाures so that
	 * other CPUs करोn't have to रुको until the start of the next grace
	 * period to process their callbacks.  This also aव्योमs some nasty
	 * RCU grace-period initialization races by क्रमcing the end of
	 * the current grace period to be completely recorded in all of
	 * the rcu_node काष्ठाures beक्रमe the beginning of the next grace
	 * period is recorded in any of the rcu_node काष्ठाures.
	 */
	new_gp_seq = rcu_state.gp_seq;
	rcu_seq_end(&new_gp_seq);
	rcu_क्रम_each_node_bपढ़ोth_first(rnp) अणु
		raw_spin_lock_irq_rcu_node(rnp);
		अगर (WARN_ON_ONCE(rcu_preempt_blocked_पढ़ोers_cgp(rnp)))
			dump_blkd_tasks(rnp, 10);
		WARN_ON_ONCE(rnp->qsmask);
		WRITE_ONCE(rnp->gp_seq, new_gp_seq);
		rdp = this_cpu_ptr(&rcu_data);
		अगर (rnp == rdp->mynode)
			needgp = __note_gp_changes(rnp, rdp) || needgp;
		/* smp_mb() provided by prior unlock-lock pair. */
		needgp = rcu_future_gp_cleanup(rnp) || needgp;
		// Reset overload indication क्रम CPUs no दीर्घer overloaded
		अगर (rcu_is_leaf_node(rnp))
			क्रम_each_leaf_node_cpu_mask(rnp, cpu, rnp->cbovldmask) अणु
				rdp = per_cpu_ptr(&rcu_data, cpu);
				check_cb_ovld_locked(rdp, rnp);
			पूर्ण
		sq = rcu_nocb_gp_get(rnp);
		raw_spin_unlock_irq_rcu_node(rnp);
		rcu_nocb_gp_cleanup(sq);
		cond_resched_tasks_rcu_qs();
		WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
		rcu_gp_slow(gp_cleanup_delay);
	पूर्ण
	rnp = rcu_get_root();
	raw_spin_lock_irq_rcu_node(rnp); /* GP beक्रमe ->gp_seq update. */

	/* Declare grace period करोne, trace first to use old GP number. */
	trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq, TPS("end"));
	rcu_seq_end(&rcu_state.gp_seq);
	ASSERT_EXCLUSIVE_WRITER(rcu_state.gp_seq);
	WRITE_ONCE(rcu_state.gp_state, RCU_GP_IDLE);
	/* Check क्रम GP requests since above loop. */
	rdp = this_cpu_ptr(&rcu_data);
	अगर (!needgp && ULONG_CMP_LT(rnp->gp_seq, rnp->gp_seq_needed)) अणु
		trace_rcu_this_gp(rnp, rdp, rnp->gp_seq_needed,
				  TPS("CleanupMore"));
		needgp = true;
	पूर्ण
	/* Advance CBs to reduce false positives below. */
	offloaded = rcu_rdp_is_offloaded(rdp);
	अगर ((offloaded || !rcu_accelerate_cbs(rnp, rdp)) && needgp) अणु
		WRITE_ONCE(rcu_state.gp_flags, RCU_GP_FLAG_INIT);
		WRITE_ONCE(rcu_state.gp_req_activity, jअगरfies);
		trace_rcu_grace_period(rcu_state.name,
				       rcu_state.gp_seq,
				       TPS("newreq"));
	पूर्ण अन्यथा अणु
		WRITE_ONCE(rcu_state.gp_flags,
			   rcu_state.gp_flags & RCU_GP_FLAG_INIT);
	पूर्ण
	raw_spin_unlock_irq_rcu_node(rnp);

	// If strict, make all CPUs aware of the end of the old grace period.
	अगर (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD))
		on_each_cpu(rcu_strict_gp_boundary, शून्य, 0);
पूर्ण

/*
 * Body of kthपढ़ो that handles grace periods.
 */
अटल पूर्णांक __noवापस rcu_gp_kthपढ़ो(व्योम *unused)
अणु
	rcu_bind_gp_kthपढ़ो();
	क्रम (;;) अणु

		/* Handle grace-period start. */
		क्रम (;;) अणु
			trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq,
					       TPS("reqwait"));
			WRITE_ONCE(rcu_state.gp_state, RCU_GP_WAIT_GPS);
			sरुको_event_idle_exclusive(rcu_state.gp_wq,
					 READ_ONCE(rcu_state.gp_flags) &
					 RCU_GP_FLAG_INIT);
			rcu_gp_torture_रुको();
			WRITE_ONCE(rcu_state.gp_state, RCU_GP_DONE_GPS);
			/* Locking provides needed memory barrier. */
			अगर (rcu_gp_init())
				अवरोध;
			cond_resched_tasks_rcu_qs();
			WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
			WARN_ON(संकेत_pending(current));
			trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq,
					       TPS("reqwaitsig"));
		पूर्ण

		/* Handle quiescent-state क्रमcing. */
		rcu_gp_fqs_loop();

		/* Handle grace-period end. */
		WRITE_ONCE(rcu_state.gp_state, RCU_GP_CLEANUP);
		rcu_gp_cleanup();
		WRITE_ONCE(rcu_state.gp_state, RCU_GP_CLEANED);
	पूर्ण
पूर्ण

/*
 * Report a full set of quiescent states to the rcu_state data काष्ठाure.
 * Invoke rcu_gp_kthपढ़ो_wake() to awaken the grace-period kthपढ़ो अगर
 * another grace period is required.  Whether we wake the grace-period
 * kthपढ़ो or it awakens itself क्रम the next round of quiescent-state
 * क्रमcing, that kthपढ़ो will clean up after the just-completed grace
 * period.  Note that the caller must hold rnp->lock, which is released
 * beक्रमe वापस.
 */
अटल व्योम rcu_report_qs_rsp(अचिन्हित दीर्घ flags)
	__releases(rcu_get_root()->lock)
अणु
	raw_lockdep_निश्चित_held_rcu_node(rcu_get_root());
	WARN_ON_ONCE(!rcu_gp_in_progress());
	WRITE_ONCE(rcu_state.gp_flags,
		   READ_ONCE(rcu_state.gp_flags) | RCU_GP_FLAG_FQS);
	raw_spin_unlock_irqrestore_rcu_node(rcu_get_root(), flags);
	rcu_gp_kthपढ़ो_wake();
पूर्ण

/*
 * Similar to rcu_report_qs_rdp(), क्रम which it is a helper function.
 * Allows quiescent states क्रम a group of CPUs to be reported at one go
 * to the specअगरied rcu_node काष्ठाure, though all the CPUs in the group
 * must be represented by the same rcu_node काष्ठाure (which need not be a
 * leaf rcu_node काष्ठाure, though it often will be).  The gps parameter
 * is the grace-period snapshot, which means that the quiescent states
 * are valid only अगर rnp->gp_seq is equal to gps.  That काष्ठाure's lock
 * must be held upon entry, and it is released beक्रमe वापस.
 *
 * As a special हाल, अगर mask is zero, the bit-alपढ़ोy-cleared check is
 * disabled.  This allows propagating quiescent state due to resumed tasks
 * during grace-period initialization.
 */
अटल व्योम rcu_report_qs_rnp(अचिन्हित दीर्घ mask, काष्ठा rcu_node *rnp,
			      अचिन्हित दीर्घ gps, अचिन्हित दीर्घ flags)
	__releases(rnp->lock)
अणु
	अचिन्हित दीर्घ oldmask = 0;
	काष्ठा rcu_node *rnp_c;

	raw_lockdep_निश्चित_held_rcu_node(rnp);

	/* Walk up the rcu_node hierarchy. */
	क्रम (;;) अणु
		अगर ((!(rnp->qsmask & mask) && mask) || rnp->gp_seq != gps) अणु

			/*
			 * Our bit has alपढ़ोy been cleared, or the
			 * relevant grace period is alपढ़ोy over, so करोne.
			 */
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
			वापस;
		पूर्ण
		WARN_ON_ONCE(oldmask); /* Any child must be all zeroed! */
		WARN_ON_ONCE(!rcu_is_leaf_node(rnp) &&
			     rcu_preempt_blocked_पढ़ोers_cgp(rnp));
		WRITE_ONCE(rnp->qsmask, rnp->qsmask & ~mask);
		trace_rcu_quiescent_state_report(rcu_state.name, rnp->gp_seq,
						 mask, rnp->qsmask, rnp->level,
						 rnp->grplo, rnp->grphi,
						 !!rnp->gp_tasks);
		अगर (rnp->qsmask != 0 || rcu_preempt_blocked_पढ़ोers_cgp(rnp)) अणु

			/* Other bits still set at this level, so करोne. */
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
			वापस;
		पूर्ण
		rnp->completedqs = rnp->gp_seq;
		mask = rnp->grpmask;
		अगर (rnp->parent == शून्य) अणु

			/* No more levels.  Exit loop holding root lock. */

			अवरोध;
		पूर्ण
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		rnp_c = rnp;
		rnp = rnp->parent;
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		oldmask = READ_ONCE(rnp_c->qsmask);
	पूर्ण

	/*
	 * Get here अगर we are the last CPU to pass through a quiescent
	 * state क्रम this grace period.  Invoke rcu_report_qs_rsp()
	 * to clean up and start the next grace period अगर one is needed.
	 */
	rcu_report_qs_rsp(flags); /* releases rnp->lock. */
पूर्ण

/*
 * Record a quiescent state क्रम all tasks that were previously queued
 * on the specअगरied rcu_node काष्ठाure and that were blocking the current
 * RCU grace period.  The caller must hold the corresponding rnp->lock with
 * irqs disabled, and this lock is released upon वापस, but irqs reमुख्य
 * disabled.
 */
अटल व्योम __maybe_unused
rcu_report_unblock_qs_rnp(काष्ठा rcu_node *rnp, अचिन्हित दीर्घ flags)
	__releases(rnp->lock)
अणु
	अचिन्हित दीर्घ gps;
	अचिन्हित दीर्घ mask;
	काष्ठा rcu_node *rnp_p;

	raw_lockdep_निश्चित_held_rcu_node(rnp);
	अगर (WARN_ON_ONCE(!IS_ENABLED(CONFIG_PREEMPT_RCU)) ||
	    WARN_ON_ONCE(rcu_preempt_blocked_पढ़ोers_cgp(rnp)) ||
	    rnp->qsmask != 0) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;  /* Still need more quiescent states! */
	पूर्ण

	rnp->completedqs = rnp->gp_seq;
	rnp_p = rnp->parent;
	अगर (rnp_p == शून्य) अणु
		/*
		 * Only one rcu_node काष्ठाure in the tree, so करोn't
		 * try to report up to its nonexistent parent!
		 */
		rcu_report_qs_rsp(flags);
		वापस;
	पूर्ण

	/* Report up the rest of the hierarchy, tracking current ->gp_seq. */
	gps = rnp->gp_seq;
	mask = rnp->grpmask;
	raw_spin_unlock_rcu_node(rnp);	/* irqs reमुख्य disabled. */
	raw_spin_lock_rcu_node(rnp_p);	/* irqs alपढ़ोy disabled. */
	rcu_report_qs_rnp(mask, rnp_p, gps, flags);
पूर्ण

/*
 * Record a quiescent state क्रम the specअगरied CPU to that CPU's rcu_data
 * काष्ठाure.  This must be called from the specअगरied CPU.
 */
अटल व्योम
rcu_report_qs_rdp(काष्ठा rcu_data *rdp)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask;
	bool needwake = false;
	स्थिर bool offloaded = rcu_rdp_is_offloaded(rdp);
	काष्ठा rcu_node *rnp;

	WARN_ON_ONCE(rdp->cpu != smp_processor_id());
	rnp = rdp->mynode;
	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	अगर (rdp->cpu_no_qs.b.norm || rdp->gp_seq != rnp->gp_seq ||
	    rdp->gpwrap) अणु

		/*
		 * The grace period in which this quiescent state was
		 * recorded has ended, so करोn't report it upwards.
		 * We will instead need a new quiescent state that lies
		 * within the current grace period.
		 */
		rdp->cpu_no_qs.b.norm = true;	/* need qs क्रम new gp. */
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		वापस;
	पूर्ण
	mask = rdp->grpmask;
	rdp->core_needs_qs = false;
	अगर ((rnp->qsmask & mask) == 0) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	पूर्ण अन्यथा अणु
		/*
		 * This GP can't end until cpu checks in, so all of our
		 * callbacks can be processed during the next GP.
		 */
		अगर (!offloaded)
			needwake = rcu_accelerate_cbs(rnp, rdp);

		rcu_disable_urgency_upon_qs(rdp);
		rcu_report_qs_rnp(mask, rnp, rnp->gp_seq, flags);
		/* ^^^ Released rnp->lock */
		अगर (needwake)
			rcu_gp_kthपढ़ो_wake();
	पूर्ण
पूर्ण

/*
 * Check to see अगर there is a new grace period of which this CPU
 * is not yet aware, and अगर so, set up local rcu_data state क्रम it.
 * Otherwise, see अगर this CPU has just passed through its first
 * quiescent state क्रम this grace period, and record that fact अगर so.
 */
अटल व्योम
rcu_check_quiescent_state(काष्ठा rcu_data *rdp)
अणु
	/* Check क्रम grace-period ends and beginnings. */
	note_gp_changes(rdp);

	/*
	 * Does this CPU still need to करो its part क्रम current grace period?
	 * If no, वापस and let the other CPUs करो their part as well.
	 */
	अगर (!rdp->core_needs_qs)
		वापस;

	/*
	 * Was there a quiescent state since the beginning of the grace
	 * period? If no, then निकास and रुको क्रम the next call.
	 */
	अगर (rdp->cpu_no_qs.b.norm)
		वापस;

	/*
	 * Tell RCU we are करोne (but rcu_report_qs_rdp() will be the
	 * judge of that).
	 */
	rcu_report_qs_rdp(rdp);
पूर्ण

/*
 * Near the end of the offline process.  Trace the fact that this CPU
 * is going offline.
 */
पूर्णांक rcutree_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	bool blkd;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp = rdp->mynode;

	अगर (!IS_ENABLED(CONFIG_HOTPLUG_CPU))
		वापस 0;

	blkd = !!(rnp->qsmask & rdp->grpmask);
	trace_rcu_grace_period(rcu_state.name, READ_ONCE(rnp->gp_seq),
			       blkd ? TPS("cpuofl-bgp") : TPS("cpuofl"));
	वापस 0;
पूर्ण

/*
 * All CPUs क्रम the specअगरied rcu_node काष्ठाure have gone offline,
 * and all tasks that were preempted within an RCU पढ़ो-side critical
 * section जबतक running on one of those CPUs have since निकासed their RCU
 * पढ़ो-side critical section.  Some other CPU is reporting this fact with
 * the specअगरied rcu_node काष्ठाure's ->lock held and पूर्णांकerrupts disabled.
 * This function thereक्रमe goes up the tree of rcu_node काष्ठाures,
 * clearing the corresponding bits in the ->qsmaskinit fields.  Note that
 * the leaf rcu_node काष्ठाure's ->qsmaskinit field has alपढ़ोy been
 * updated.
 *
 * This function करोes check that the specअगरied rcu_node काष्ठाure has
 * all CPUs offline and no blocked tasks, so it is OK to invoke it
 * prematurely.  That said, invoking it after the fact will cost you
 * a needless lock acquisition.  So once it has करोne its work, करोn't
 * invoke it again.
 */
अटल व्योम rcu_cleanup_dead_rnp(काष्ठा rcu_node *rnp_leaf)
अणु
	दीर्घ mask;
	काष्ठा rcu_node *rnp = rnp_leaf;

	raw_lockdep_निश्चित_held_rcu_node(rnp_leaf);
	अगर (!IS_ENABLED(CONFIG_HOTPLUG_CPU) ||
	    WARN_ON_ONCE(rnp_leaf->qsmaskinit) ||
	    WARN_ON_ONCE(rcu_preempt_has_tasks(rnp_leaf)))
		वापस;
	क्रम (;;) अणु
		mask = rnp->grpmask;
		rnp = rnp->parent;
		अगर (!rnp)
			अवरोध;
		raw_spin_lock_rcu_node(rnp); /* irqs alपढ़ोy disabled. */
		rnp->qsmaskinit &= ~mask;
		/* Between grace periods, so better alपढ़ोy be zero! */
		WARN_ON_ONCE(rnp->qsmask);
		अगर (rnp->qsmaskinit) अणु
			raw_spin_unlock_rcu_node(rnp);
			/* irqs reमुख्य disabled. */
			वापस;
		पूर्ण
		raw_spin_unlock_rcu_node(rnp); /* irqs reमुख्य disabled. */
	पूर्ण
पूर्ण

/*
 * The CPU has been completely हटाओd, and some other CPU is reporting
 * this fact from process context.  Do the reमुख्यder of the cleanup.
 * There can only be one CPU hotplug operation at a समय, so no need क्रम
 * explicit locking.
 */
पूर्णांक rcutree_dead_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	काष्ठा rcu_node *rnp = rdp->mynode;  /* Outgoing CPU's rdp & rnp. */

	अगर (!IS_ENABLED(CONFIG_HOTPLUG_CPU))
		वापस 0;

	WRITE_ONCE(rcu_state.n_online_cpus, rcu_state.n_online_cpus - 1);
	/* Adjust any no-दीर्घer-needed kthपढ़ोs. */
	rcu_boost_kthपढ़ो_setaffinity(rnp, -1);
	/* Do any needed no-CB deferred wakeups from this CPU. */
	करो_nocb_deferred_wakeup(per_cpu_ptr(&rcu_data, cpu));

	// Stop-machine करोne, so allow nohz_full to disable tick.
	tick_dep_clear(TICK_DEP_BIT_RCU);
	वापस 0;
पूर्ण

/*
 * Invoke any RCU callbacks that have made it to the end of their grace
 * period.  Thottle as specअगरied by rdp->blimit.
 */
अटल व्योम rcu_करो_batch(काष्ठा rcu_data *rdp)
अणु
	पूर्णांक भाग;
	bool __maybe_unused empty;
	अचिन्हित दीर्घ flags;
	स्थिर bool offloaded = rcu_rdp_is_offloaded(rdp);
	काष्ठा rcu_head *rhp;
	काष्ठा rcu_cblist rcl = RCU_CBLIST_INITIALIZER(rcl);
	दीर्घ bl, count = 0;
	दीर्घ pending, tlimit = 0;

	/* If no callbacks are पढ़ोy, just वापस. */
	अगर (!rcu_segcblist_पढ़ोy_cbs(&rdp->cblist)) अणु
		trace_rcu_batch_start(rcu_state.name,
				      rcu_segcblist_n_cbs(&rdp->cblist), 0);
		trace_rcu_batch_end(rcu_state.name, 0,
				    !rcu_segcblist_empty(&rdp->cblist),
				    need_resched(), is_idle_task(current),
				    rcu_is_callbacks_kthपढ़ो());
		वापस;
	पूर्ण

	/*
	 * Extract the list of पढ़ोy callbacks, disabling to prevent
	 * races with call_rcu() from पूर्णांकerrupt handlers.  Leave the
	 * callback counts, as rcu_barrier() needs to be conservative.
	 */
	local_irq_save(flags);
	rcu_nocb_lock(rdp);
	WARN_ON_ONCE(cpu_is_offline(smp_processor_id()));
	pending = rcu_segcblist_n_cbs(&rdp->cblist);
	भाग = READ_ONCE(rcu_भागisor);
	भाग = भाग < 0 ? 7 : भाग > माप(दीर्घ) * 8 - 2 ? माप(दीर्घ) * 8 - 2 : भाग;
	bl = max(rdp->blimit, pending >> भाग);
	अगर (unlikely(bl > 100)) अणु
		दीर्घ rrn = READ_ONCE(rcu_resched_ns);

		rrn = rrn < NSEC_PER_MSEC ? NSEC_PER_MSEC : rrn > NSEC_PER_SEC ? NSEC_PER_SEC : rrn;
		tlimit = local_घड़ी() + rrn;
	पूर्ण
	trace_rcu_batch_start(rcu_state.name,
			      rcu_segcblist_n_cbs(&rdp->cblist), bl);
	rcu_segcblist_extract_करोne_cbs(&rdp->cblist, &rcl);
	अगर (offloaded)
		rdp->qlen_last_fqs_check = rcu_segcblist_n_cbs(&rdp->cblist);

	trace_rcu_segcb_stats(&rdp->cblist, TPS("SegCbDequeued"));
	rcu_nocb_unlock_irqrestore(rdp, flags);

	/* Invoke callbacks. */
	tick_dep_set_task(current, TICK_DEP_BIT_RCU);
	rhp = rcu_cblist_dequeue(&rcl);

	क्रम (; rhp; rhp = rcu_cblist_dequeue(&rcl)) अणु
		rcu_callback_t f;

		count++;
		debug_rcu_head_unqueue(rhp);

		rcu_lock_acquire(&rcu_callback_map);
		trace_rcu_invoke_callback(rcu_state.name, rhp);

		f = rhp->func;
		WRITE_ONCE(rhp->func, (rcu_callback_t)0L);
		f(rhp);

		rcu_lock_release(&rcu_callback_map);

		/*
		 * Stop only अगर limit reached and CPU has something to करो.
		 */
		अगर (count >= bl && !offloaded &&
		    (need_resched() ||
		     (!is_idle_task(current) && !rcu_is_callbacks_kthपढ़ो())))
			अवरोध;
		अगर (unlikely(tlimit)) अणु
			/* only call local_घड़ी() every 32 callbacks */
			अगर (likely((count & 31) || local_घड़ी() < tlimit))
				जारी;
			/* Exceeded the समय limit, so leave. */
			अवरोध;
		पूर्ण
		अगर (!in_serving_softirq()) अणु
			local_bh_enable();
			lockdep_निश्चित_irqs_enabled();
			cond_resched_tasks_rcu_qs();
			lockdep_निश्चित_irqs_enabled();
			local_bh_disable();
		पूर्ण
	पूर्ण

	local_irq_save(flags);
	rcu_nocb_lock(rdp);
	rdp->n_cbs_invoked += count;
	trace_rcu_batch_end(rcu_state.name, count, !!rcl.head, need_resched(),
			    is_idle_task(current), rcu_is_callbacks_kthपढ़ो());

	/* Update counts and requeue any reमुख्यing callbacks. */
	rcu_segcblist_insert_करोne_cbs(&rdp->cblist, &rcl);
	rcu_segcblist_add_len(&rdp->cblist, -count);

	/* Reinstate batch limit अगर we have worked करोwn the excess. */
	count = rcu_segcblist_n_cbs(&rdp->cblist);
	अगर (rdp->blimit >= DEFAULT_MAX_RCU_BLIMIT && count <= qlowmark)
		rdp->blimit = blimit;

	/* Reset ->qlen_last_fqs_check trigger अगर enough CBs have drained. */
	अगर (count == 0 && rdp->qlen_last_fqs_check != 0) अणु
		rdp->qlen_last_fqs_check = 0;
		rdp->n_क्रमce_qs_snap = rcu_state.n_क्रमce_qs;
	पूर्ण अन्यथा अगर (count < rdp->qlen_last_fqs_check - qhimark)
		rdp->qlen_last_fqs_check = count;

	/*
	 * The following usually indicates a द्विगुन call_rcu().  To track
	 * this करोwn, try building with CONFIG_DEBUG_OBJECTS_RCU_HEAD=y.
	 */
	empty = rcu_segcblist_empty(&rdp->cblist);
	WARN_ON_ONCE(count == 0 && !empty);
	WARN_ON_ONCE(!IS_ENABLED(CONFIG_RCU_NOCB_CPU) &&
		     count != 0 && empty);
	WARN_ON_ONCE(count == 0 && rcu_segcblist_n_segment_cbs(&rdp->cblist) != 0);
	WARN_ON_ONCE(!empty && rcu_segcblist_n_segment_cbs(&rdp->cblist) == 0);

	rcu_nocb_unlock_irqrestore(rdp, flags);

	/* Re-invoke RCU core processing अगर there are callbacks reमुख्यing. */
	अगर (!offloaded && rcu_segcblist_पढ़ोy_cbs(&rdp->cblist))
		invoke_rcu_core();
	tick_dep_clear_task(current, TICK_DEP_BIT_RCU);
पूर्ण

/*
 * This function is invoked from each scheduling-घड़ी पूर्णांकerrupt,
 * and checks to see अगर this CPU is in a non-context-चयन quiescent
 * state, क्रम example, user mode or idle loop.  It also schedules RCU
 * core processing.  If the current grace period has gone on too दीर्घ,
 * it will ask the scheduler to manufacture a context चयन क्रम the sole
 * purpose of providing a providing the needed quiescent state.
 */
व्योम rcu_sched_घड़ी_irq(पूर्णांक user)
अणु
	trace_rcu_utilization(TPS("Start scheduler-tick"));
	lockdep_निश्चित_irqs_disabled();
	raw_cpu_inc(rcu_data.ticks_this_gp);
	/* The load-acquire pairs with the store-release setting to true. */
	अगर (smp_load_acquire(this_cpu_ptr(&rcu_data.rcu_urgent_qs))) अणु
		/* Idle and userspace execution alपढ़ोy are quiescent states. */
		अगर (!rcu_is_cpu_rrupt_from_idle() && !user) अणु
			set_tsk_need_resched(current);
			set_preempt_need_resched();
		पूर्ण
		__this_cpu_ग_लिखो(rcu_data.rcu_urgent_qs, false);
	पूर्ण
	rcu_flavor_sched_घड़ी_irq(user);
	अगर (rcu_pending(user))
		invoke_rcu_core();
	lockdep_निश्चित_irqs_disabled();

	trace_rcu_utilization(TPS("End scheduler-tick"));
पूर्ण

/*
 * Scan the leaf rcu_node काष्ठाures.  For each काष्ठाure on which all
 * CPUs have reported a quiescent state and on which there are tasks
 * blocking the current grace period, initiate RCU priority boosting.
 * Otherwise, invoke the specअगरied function to check dyntick state क्रम
 * each CPU that has not yet reported a quiescent state.
 */
अटल व्योम क्रमce_qs_rnp(पूर्णांक (*f)(काष्ठा rcu_data *rdp))
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;

	rcu_state.cbovld = rcu_state.cbovldnext;
	rcu_state.cbovldnext = false;
	rcu_क्रम_each_leaf_node(rnp) अणु
		cond_resched_tasks_rcu_qs();
		mask = 0;
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
		rcu_state.cbovldnext |= !!rnp->cbovldmask;
		अगर (rnp->qsmask == 0) अणु
			अगर (rcu_preempt_blocked_पढ़ोers_cgp(rnp)) अणु
				/*
				 * No poपूर्णांक in scanning bits because they
				 * are all zero.  But we might need to
				 * priority-boost blocked पढ़ोers.
				 */
				rcu_initiate_boost(rnp, flags);
				/* rcu_initiate_boost() releases rnp->lock */
				जारी;
			पूर्ण
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
			जारी;
		पूर्ण
		क्रम_each_leaf_node_cpu_mask(rnp, cpu, rnp->qsmask) अणु
			rdp = per_cpu_ptr(&rcu_data, cpu);
			अगर (f(rdp)) अणु
				mask |= rdp->grpmask;
				rcu_disable_urgency_upon_qs(rdp);
			पूर्ण
		पूर्ण
		अगर (mask != 0) अणु
			/* Idle/offline CPUs, report (releases rnp->lock). */
			rcu_report_qs_rnp(mask, rnp, rnp->gp_seq, flags);
		पूर्ण अन्यथा अणु
			/* Nothing to करो here, so just drop the lock. */
			raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Force quiescent states on reluctant CPUs, and also detect which
 * CPUs are in dyntick-idle mode.
 */
व्योम rcu_क्रमce_quiescent_state(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;
	काष्ठा rcu_node *rnp;
	काष्ठा rcu_node *rnp_old = शून्य;

	/* Funnel through hierarchy to reduce memory contention. */
	rnp = __this_cpu_पढ़ो(rcu_data.mynode);
	क्रम (; rnp != शून्य; rnp = rnp->parent) अणु
		ret = (READ_ONCE(rcu_state.gp_flags) & RCU_GP_FLAG_FQS) ||
		       !raw_spin_trylock(&rnp->fqslock);
		अगर (rnp_old != शून्य)
			raw_spin_unlock(&rnp_old->fqslock);
		अगर (ret)
			वापस;
		rnp_old = rnp;
	पूर्ण
	/* rnp_old == rcu_get_root(), rnp == शून्य. */

	/* Reached the root of the rcu_node tree, acquire lock. */
	raw_spin_lock_irqsave_rcu_node(rnp_old, flags);
	raw_spin_unlock(&rnp_old->fqslock);
	अगर (READ_ONCE(rcu_state.gp_flags) & RCU_GP_FLAG_FQS) अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp_old, flags);
		वापस;  /* Someone beat us to it. */
	पूर्ण
	WRITE_ONCE(rcu_state.gp_flags,
		   READ_ONCE(rcu_state.gp_flags) | RCU_GP_FLAG_FQS);
	raw_spin_unlock_irqrestore_rcu_node(rnp_old, flags);
	rcu_gp_kthपढ़ो_wake();
पूर्ण
EXPORT_SYMBOL_GPL(rcu_क्रमce_quiescent_state);

// Workqueue handler क्रम an RCU पढ़ोer क्रम kernels enक्रमcing काष्ठा RCU
// grace periods.
अटल व्योम strict_work_handler(काष्ठा work_काष्ठा *work)
अणु
	rcu_पढ़ो_lock();
	rcu_पढ़ो_unlock();
पूर्ण

/* Perक्रमm RCU core processing work क्रम the current CPU.  */
अटल __latent_entropy व्योम rcu_core(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp = raw_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp = rdp->mynode;
	स्थिर bool करो_batch = !rcu_segcblist_completely_offloaded(&rdp->cblist);

	अगर (cpu_is_offline(smp_processor_id()))
		वापस;
	trace_rcu_utilization(TPS("Start RCU core"));
	WARN_ON_ONCE(!rdp->beenonline);

	/* Report any deferred quiescent states अगर preemption enabled. */
	अगर (!(preempt_count() & PREEMPT_MASK)) अणु
		rcu_preempt_deferred_qs(current);
	पूर्ण अन्यथा अगर (rcu_preempt_need_deferred_qs(current)) अणु
		set_tsk_need_resched(current);
		set_preempt_need_resched();
	पूर्ण

	/* Update RCU state based on any recent quiescent states. */
	rcu_check_quiescent_state(rdp);

	/* No grace period and unरेजिस्टरed callbacks? */
	अगर (!rcu_gp_in_progress() &&
	    rcu_segcblist_is_enabled(&rdp->cblist) && करो_batch) अणु
		rcu_nocb_lock_irqsave(rdp, flags);
		अगर (!rcu_segcblist_restempty(&rdp->cblist, RCU_NEXT_READY_TAIL))
			rcu_accelerate_cbs_unlocked(rnp, rdp);
		rcu_nocb_unlock_irqrestore(rdp, flags);
	पूर्ण

	rcu_check_gp_start_stall(rnp, rdp, rcu_jअगरfies_till_stall_check());

	/* If there are callbacks पढ़ोy, invoke them. */
	अगर (करो_batch && rcu_segcblist_पढ़ोy_cbs(&rdp->cblist) &&
	    likely(READ_ONCE(rcu_scheduler_fully_active)))
		rcu_करो_batch(rdp);

	/* Do any needed deferred wakeups of rcuo kthपढ़ोs. */
	करो_nocb_deferred_wakeup(rdp);
	trace_rcu_utilization(TPS("End RCU core"));

	// If strict GPs, schedule an RCU पढ़ोer in a clean environment.
	अगर (IS_ENABLED(CONFIG_RCU_STRICT_GRACE_PERIOD))
		queue_work_on(rdp->cpu, rcu_gp_wq, &rdp->strict_work);
पूर्ण

अटल व्योम rcu_core_si(काष्ठा softirq_action *h)
अणु
	rcu_core();
पूर्ण

अटल व्योम rcu_wake_cond(काष्ठा task_काष्ठा *t, पूर्णांक status)
अणु
	/*
	 * If the thपढ़ो is yielding, only wake it when this
	 * is invoked from idle
	 */
	अगर (t && (status != RCU_KTHREAD_YIELDING || is_idle_task(current)))
		wake_up_process(t);
पूर्ण

अटल व्योम invoke_rcu_core_kthपढ़ो(व्योम)
अणु
	काष्ठा task_काष्ठा *t;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__this_cpu_ग_लिखो(rcu_data.rcu_cpu_has_work, 1);
	t = __this_cpu_पढ़ो(rcu_data.rcu_cpu_kthपढ़ो_task);
	अगर (t != शून्य && t != current)
		rcu_wake_cond(t, __this_cpu_पढ़ो(rcu_data.rcu_cpu_kthपढ़ो_status));
	local_irq_restore(flags);
पूर्ण

/*
 * Wake up this CPU's rcuc kthपढ़ो to करो RCU core processing.
 */
अटल व्योम invoke_rcu_core(व्योम)
अणु
	अगर (!cpu_online(smp_processor_id()))
		वापस;
	अगर (use_softirq)
		उठाओ_softirq(RCU_SOFTIRQ);
	अन्यथा
		invoke_rcu_core_kthपढ़ो();
पूर्ण

अटल व्योम rcu_cpu_kthपढ़ो_park(अचिन्हित पूर्णांक cpu)
अणु
	per_cpu(rcu_data.rcu_cpu_kthपढ़ो_status, cpu) = RCU_KTHREAD_OFFCPU;
पूर्ण

अटल पूर्णांक rcu_cpu_kthपढ़ो_should_run(अचिन्हित पूर्णांक cpu)
अणु
	वापस __this_cpu_पढ़ो(rcu_data.rcu_cpu_has_work);
पूर्ण

/*
 * Per-CPU kernel thपढ़ो that invokes RCU callbacks.  This replaces
 * the RCU softirq used in configurations of RCU that करो not support RCU
 * priority boosting.
 */
अटल व्योम rcu_cpu_kthपढ़ो(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक *statusp = this_cpu_ptr(&rcu_data.rcu_cpu_kthपढ़ो_status);
	अक्षर work, *workp = this_cpu_ptr(&rcu_data.rcu_cpu_has_work);
	पूर्णांक spincnt;

	trace_rcu_utilization(TPS("Start CPU kthread@rcu_run"));
	क्रम (spincnt = 0; spincnt < 10; spincnt++) अणु
		local_bh_disable();
		*statusp = RCU_KTHREAD_RUNNING;
		local_irq_disable();
		work = *workp;
		*workp = 0;
		local_irq_enable();
		अगर (work)
			rcu_core();
		local_bh_enable();
		अगर (*workp == 0) अणु
			trace_rcu_utilization(TPS("End CPU kthread@rcu_wait"));
			*statusp = RCU_KTHREAD_WAITING;
			वापस;
		पूर्ण
	पूर्ण
	*statusp = RCU_KTHREAD_YIELDING;
	trace_rcu_utilization(TPS("Start CPU kthread@rcu_yield"));
	schedule_समयout_idle(2);
	trace_rcu_utilization(TPS("End CPU kthread@rcu_yield"));
	*statusp = RCU_KTHREAD_WAITING;
पूर्ण

अटल काष्ठा smp_hotplug_thपढ़ो rcu_cpu_thपढ़ो_spec = अणु
	.store			= &rcu_data.rcu_cpu_kthपढ़ो_task,
	.thपढ़ो_should_run	= rcu_cpu_kthपढ़ो_should_run,
	.thपढ़ो_fn		= rcu_cpu_kthपढ़ो,
	.thपढ़ो_comm		= "rcuc/%u",
	.setup			= rcu_cpu_kthपढ़ो_setup,
	.park			= rcu_cpu_kthपढ़ो_park,
पूर्ण;

/*
 * Spawn per-CPU RCU core processing kthपढ़ोs.
 */
अटल पूर्णांक __init rcu_spawn_core_kthपढ़ोs(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		per_cpu(rcu_data.rcu_cpu_has_work, cpu) = 0;
	अगर (!IS_ENABLED(CONFIG_RCU_BOOST) && use_softirq)
		वापस 0;
	WARN_ONCE(smpboot_रेजिस्टर_percpu_thपढ़ो(&rcu_cpu_thपढ़ो_spec),
		  "%s: Could not start rcuc kthread, OOM is now expected behavior\n", __func__);
	वापस 0;
पूर्ण
early_initcall(rcu_spawn_core_kthपढ़ोs);

/*
 * Handle any core-RCU processing required by a call_rcu() invocation.
 */
अटल व्योम __call_rcu_core(काष्ठा rcu_data *rdp, काष्ठा rcu_head *head,
			    अचिन्हित दीर्घ flags)
अणु
	/*
	 * If called from an extended quiescent state, invoke the RCU
	 * core in order to क्रमce a re-evaluation of RCU's idleness.
	 */
	अगर (!rcu_is_watching())
		invoke_rcu_core();

	/* If पूर्णांकerrupts were disabled or CPU offline, करोn't invoke RCU core. */
	अगर (irqs_disabled_flags(flags) || cpu_is_offline(smp_processor_id()))
		वापस;

	/*
	 * Force the grace period अगर too many callbacks or too दीर्घ रुकोing.
	 * Enक्रमce hysteresis, and करोn't invoke rcu_क्रमce_quiescent_state()
	 * अगर some other CPU has recently करोne so.  Also, करोn't bother
	 * invoking rcu_क्रमce_quiescent_state() अगर the newly enqueued callback
	 * is the only one रुकोing क्रम a grace period to complete.
	 */
	अगर (unlikely(rcu_segcblist_n_cbs(&rdp->cblist) >
		     rdp->qlen_last_fqs_check + qhimark)) अणु

		/* Are we ignoring a completed grace period? */
		note_gp_changes(rdp);

		/* Start a new grace period अगर one not alपढ़ोy started. */
		अगर (!rcu_gp_in_progress()) अणु
			rcu_accelerate_cbs_unlocked(rdp->mynode, rdp);
		पूर्ण अन्यथा अणु
			/* Give the grace period a kick. */
			rdp->blimit = DEFAULT_MAX_RCU_BLIMIT;
			अगर (rcu_state.n_क्रमce_qs == rdp->n_क्रमce_qs_snap &&
			    rcu_segcblist_first_pend_cb(&rdp->cblist) != head)
				rcu_क्रमce_quiescent_state();
			rdp->n_क्रमce_qs_snap = rcu_state.n_क्रमce_qs;
			rdp->qlen_last_fqs_check = rcu_segcblist_n_cbs(&rdp->cblist);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * RCU callback function to leak a callback.
 */
अटल व्योम rcu_leak_callback(काष्ठा rcu_head *rhp)
अणु
पूर्ण

/*
 * Check and अगर necessary update the leaf rcu_node काष्ठाure's
 * ->cbovldmask bit corresponding to the current CPU based on that CPU's
 * number of queued RCU callbacks.  The caller must hold the leaf rcu_node
 * काष्ठाure's ->lock.
 */
अटल व्योम check_cb_ovld_locked(काष्ठा rcu_data *rdp, काष्ठा rcu_node *rnp)
अणु
	raw_lockdep_निश्चित_held_rcu_node(rnp);
	अगर (qovld_calc <= 0)
		वापस; // Early boot and wildcard value set.
	अगर (rcu_segcblist_n_cbs(&rdp->cblist) >= qovld_calc)
		WRITE_ONCE(rnp->cbovldmask, rnp->cbovldmask | rdp->grpmask);
	अन्यथा
		WRITE_ONCE(rnp->cbovldmask, rnp->cbovldmask & ~rdp->grpmask);
पूर्ण

/*
 * Check and अगर necessary update the leaf rcu_node काष्ठाure's
 * ->cbovldmask bit corresponding to the current CPU based on that CPU's
 * number of queued RCU callbacks.  No locks need be held, but the
 * caller must have disabled पूर्णांकerrupts.
 *
 * Note that this function ignores the possibility that there are a lot
 * of callbacks all of which have alपढ़ोy seen the end of their respective
 * grace periods.  This omission is due to the need क्रम no-CBs CPUs to
 * be holding ->nocb_lock to करो this check, which is too heavy क्रम a
 * common-हाल operation.
 */
अटल व्योम check_cb_ovld(काष्ठा rcu_data *rdp)
अणु
	काष्ठा rcu_node *स्थिर rnp = rdp->mynode;

	अगर (qovld_calc <= 0 ||
	    ((rcu_segcblist_n_cbs(&rdp->cblist) >= qovld_calc) ==
	     !!(READ_ONCE(rnp->cbovldmask) & rdp->grpmask)))
		वापस; // Early boot wildcard value or alपढ़ोy set correctly.
	raw_spin_lock_rcu_node(rnp);
	check_cb_ovld_locked(rdp, rnp);
	raw_spin_unlock_rcu_node(rnp);
पूर्ण

/* Helper function क्रम call_rcu() and मित्रs.  */
अटल व्योम
__call_rcu(काष्ठा rcu_head *head, rcu_callback_t func)
अणु
	अटल atomic_t द्विगुनमुक्तs;
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp;
	bool was_allकरोne;

	/* Misaligned rcu_head! */
	WARN_ON_ONCE((अचिन्हित दीर्घ)head & (माप(व्योम *) - 1));

	अगर (debug_rcu_head_queue(head)) अणु
		/*
		 * Probable द्विगुन call_rcu(), so leak the callback.
		 * Use rcu:rcu_callback trace event to find the previous
		 * समय callback was passed to __call_rcu().
		 */
		अगर (atomic_inc_वापस(&द्विगुनमुक्तs) < 4) अणु
			pr_err("%s(): Double-freed CB %p->%pS()!!!  ", __func__, head, head->func);
			mem_dump_obj(head);
		पूर्ण
		WRITE_ONCE(head->func, rcu_leak_callback);
		वापस;
	पूर्ण
	head->func = func;
	head->next = शून्य;
	local_irq_save(flags);
	kasan_record_aux_stack(head);
	rdp = this_cpu_ptr(&rcu_data);

	/* Add the callback to our list. */
	अगर (unlikely(!rcu_segcblist_is_enabled(&rdp->cblist))) अणु
		// This can trigger due to call_rcu() from offline CPU:
		WARN_ON_ONCE(rcu_scheduler_active != RCU_SCHEDULER_INACTIVE);
		WARN_ON_ONCE(!rcu_is_watching());
		// Very early boot, beक्रमe rcu_init().  Initialize अगर needed
		// and then drop through to queue the callback.
		अगर (rcu_segcblist_empty(&rdp->cblist))
			rcu_segcblist_init(&rdp->cblist);
	पूर्ण

	check_cb_ovld(rdp);
	अगर (rcu_nocb_try_bypass(rdp, head, &was_allकरोne, flags))
		वापस; // Enqueued onto ->nocb_bypass, so just leave.
	// If no-CBs CPU माला_लो here, rcu_nocb_try_bypass() acquired ->nocb_lock.
	rcu_segcblist_enqueue(&rdp->cblist, head);
	अगर (__is_kvमुक्त_rcu_offset((अचिन्हित दीर्घ)func))
		trace_rcu_kvमुक्त_callback(rcu_state.name, head,
					 (अचिन्हित दीर्घ)func,
					 rcu_segcblist_n_cbs(&rdp->cblist));
	अन्यथा
		trace_rcu_callback(rcu_state.name, head,
				   rcu_segcblist_n_cbs(&rdp->cblist));

	trace_rcu_segcb_stats(&rdp->cblist, TPS("SegCBQueued"));

	/* Go handle any RCU core processing required. */
	अगर (unlikely(rcu_rdp_is_offloaded(rdp))) अणु
		__call_rcu_nocb_wake(rdp, was_allकरोne, flags); /* unlocks */
	पूर्ण अन्यथा अणु
		__call_rcu_core(rdp, head, flags);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

/**
 * call_rcu() - Queue an RCU callback क्रम invocation after a grace period.
 * @head: काष्ठाure to be used क्रम queueing the RCU updates.
 * @func: actual callback function to be invoked after the grace period
 *
 * The callback function will be invoked some समय after a full grace
 * period elapses, in other words after all pre-existing RCU पढ़ो-side
 * critical sections have completed.  However, the callback function
 * might well execute concurrently with RCU पढ़ो-side critical sections
 * that started after call_rcu() was invoked.  RCU पढ़ो-side critical
 * sections are delimited by rcu_पढ़ो_lock() and rcu_पढ़ो_unlock(), and
 * may be nested.  In addition, regions of code across which पूर्णांकerrupts,
 * preemption, or softirqs have been disabled also serve as RCU पढ़ो-side
 * critical sections.  This includes hardware पूर्णांकerrupt handlers, softirq
 * handlers, and NMI handlers.
 *
 * Note that all CPUs must agree that the grace period extended beyond
 * all pre-existing RCU पढ़ो-side critical section.  On प्रणालीs with more
 * than one CPU, this means that when "func()" is invoked, each CPU is
 * guaranteed to have executed a full memory barrier since the end of its
 * last RCU पढ़ो-side critical section whose beginning preceded the call
 * to call_rcu().  It also means that each CPU executing an RCU पढ़ो-side
 * critical section that जारीs beyond the start of "func()" must have
 * executed a memory barrier after the call_rcu() but beक्रमe the beginning
 * of that RCU पढ़ो-side critical section.  Note that these guarantees
 * include CPUs that are offline, idle, or executing in user mode, as
 * well as CPUs that are executing in the kernel.
 *
 * Furthermore, अगर CPU A invoked call_rcu() and CPU B invoked the
 * resulting RCU callback function "func()", then both CPU A and CPU B are
 * guaranteed to execute a full memory barrier during the समय पूर्णांकerval
 * between the call to call_rcu() and the invocation of "func()" -- even
 * अगर CPU A and CPU B are the same CPU (but again only अगर the प्रणाली has
 * more than one CPU).
 */
व्योम call_rcu(काष्ठा rcu_head *head, rcu_callback_t func)
अणु
	__call_rcu(head, func);
पूर्ण
EXPORT_SYMBOL_GPL(call_rcu);


/* Maximum number of jअगरfies to रुको beक्रमe draining a batch. */
#घोषणा KFREE_DRAIN_JIFFIES (HZ / 50)
#घोषणा KFREE_N_BATCHES 2
#घोषणा FREE_N_CHANNELS 2

/**
 * काष्ठा kvमुक्त_rcu_bulk_data - single block to store kvमुक्त_rcu() poपूर्णांकers
 * @nr_records: Number of active poपूर्णांकers in the array
 * @next: Next bulk object in the block chain
 * @records: Array of the kvमुक्त_rcu() poपूर्णांकers
 */
काष्ठा kvमुक्त_rcu_bulk_data अणु
	अचिन्हित दीर्घ nr_records;
	काष्ठा kvमुक्त_rcu_bulk_data *next;
	व्योम *records[];
पूर्ण;

/*
 * This macro defines how many entries the "records" array
 * will contain. It is based on the fact that the size of
 * kvमुक्त_rcu_bulk_data काष्ठाure becomes exactly one page.
 */
#घोषणा KVFREE_BULK_MAX_ENTR \
	((PAGE_SIZE - माप(काष्ठा kvमुक्त_rcu_bulk_data)) / माप(व्योम *))

/**
 * काष्ठा kमुक्त_rcu_cpu_work - single batch of kमुक्त_rcu() requests
 * @rcu_work: Let queue_rcu_work() invoke workqueue handler after grace period
 * @head_मुक्त: List of kमुक्त_rcu() objects रुकोing क्रम a grace period
 * @bkvhead_मुक्त: Bulk-List of kvमुक्त_rcu() objects रुकोing क्रम a grace period
 * @krcp: Poपूर्णांकer to @kमुक्त_rcu_cpu काष्ठाure
 */

काष्ठा kमुक्त_rcu_cpu_work अणु
	काष्ठा rcu_work rcu_work;
	काष्ठा rcu_head *head_मुक्त;
	काष्ठा kvमुक्त_rcu_bulk_data *bkvhead_मुक्त[FREE_N_CHANNELS];
	काष्ठा kमुक्त_rcu_cpu *krcp;
पूर्ण;

/**
 * काष्ठा kमुक्त_rcu_cpu - batch up kमुक्त_rcu() requests क्रम RCU grace period
 * @head: List of kमुक्त_rcu() objects not yet रुकोing क्रम a grace period
 * @bkvhead: Bulk-List of kvमुक्त_rcu() objects not yet रुकोing क्रम a grace period
 * @krw_arr: Array of batches of kमुक्त_rcu() objects रुकोing क्रम a grace period
 * @lock: Synchronize access to this काष्ठाure
 * @monitor_work: Promote @head to @head_मुक्त after KFREE_DRAIN_JIFFIES
 * @monitor_toकरो: Tracks whether a @monitor_work delayed work is pending
 * @initialized: The @rcu_work fields have been initialized
 * @count: Number of objects क्रम which GP not started
 * @bkvcache:
 *	A simple cache list that contains objects क्रम reuse purpose.
 *	In order to save some per-cpu space the list is singular.
 *	Even though it is lockless an access has to be रक्षित by the
 *	per-cpu lock.
 * @page_cache_work: A work to refill the cache when it is empty
 * @work_in_progress: Indicates that page_cache_work is running
 * @hrसमयr: A hrसमयr क्रम scheduling a page_cache_work
 * @nr_bkv_objs: number of allocated objects at @bkvcache.
 *
 * This is a per-CPU काष्ठाure.  The reason that it is not included in
 * the rcu_data काष्ठाure is to permit this code to be extracted from
 * the RCU files.  Such extraction could allow further optimization of
 * the पूर्णांकeractions with the slab allocators.
 */
काष्ठा kमुक्त_rcu_cpu अणु
	काष्ठा rcu_head *head;
	काष्ठा kvमुक्त_rcu_bulk_data *bkvhead[FREE_N_CHANNELS];
	काष्ठा kमुक्त_rcu_cpu_work krw_arr[KFREE_N_BATCHES];
	raw_spinlock_t lock;
	काष्ठा delayed_work monitor_work;
	bool monitor_toकरो;
	bool initialized;
	पूर्णांक count;

	काष्ठा work_काष्ठा page_cache_work;
	atomic_t work_in_progress;
	काष्ठा hrसमयr hrसमयr;

	काष्ठा llist_head bkvcache;
	पूर्णांक nr_bkv_objs;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा kमुक्त_rcu_cpu, krc) = अणु
	.lock = __RAW_SPIN_LOCK_UNLOCKED(krc.lock),
पूर्ण;

अटल __always_अंतरभूत व्योम
debug_rcu_bhead_unqueue(काष्ठा kvमुक्त_rcu_bulk_data *bhead)
अणु
#अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD
	पूर्णांक i;

	क्रम (i = 0; i < bhead->nr_records; i++)
		debug_rcu_head_unqueue((काष्ठा rcu_head *)(bhead->records[i]));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा kमुक्त_rcu_cpu *
krc_this_cpu_lock(अचिन्हित दीर्घ *flags)
अणु
	काष्ठा kमुक्त_rcu_cpu *krcp;

	local_irq_save(*flags);	// For safely calling this_cpu_ptr().
	krcp = this_cpu_ptr(&krc);
	raw_spin_lock(&krcp->lock);

	वापस krcp;
पूर्ण

अटल अंतरभूत व्योम
krc_this_cpu_unlock(काष्ठा kमुक्त_rcu_cpu *krcp, अचिन्हित दीर्घ flags)
अणु
	raw_spin_unlock_irqrestore(&krcp->lock, flags);
पूर्ण

अटल अंतरभूत काष्ठा kvमुक्त_rcu_bulk_data *
get_cached_bnode(काष्ठा kमुक्त_rcu_cpu *krcp)
अणु
	अगर (!krcp->nr_bkv_objs)
		वापस शून्य;

	krcp->nr_bkv_objs--;
	वापस (काष्ठा kvमुक्त_rcu_bulk_data *)
		llist_del_first(&krcp->bkvcache);
पूर्ण

अटल अंतरभूत bool
put_cached_bnode(काष्ठा kमुक्त_rcu_cpu *krcp,
	काष्ठा kvमुक्त_rcu_bulk_data *bnode)
अणु
	// Check the limit.
	अगर (krcp->nr_bkv_objs >= rcu_min_cached_objs)
		वापस false;

	llist_add((काष्ठा llist_node *) bnode, &krcp->bkvcache);
	krcp->nr_bkv_objs++;
	वापस true;

पूर्ण

/*
 * This function is invoked in workqueue context after a grace period.
 * It मुक्तs all the objects queued on ->bhead_मुक्त or ->head_मुक्त.
 */
अटल व्योम kमुक्त_rcu_work(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kvमुक्त_rcu_bulk_data *bkvhead[FREE_N_CHANNELS], *bnext;
	काष्ठा rcu_head *head, *next;
	काष्ठा kमुक्त_rcu_cpu *krcp;
	काष्ठा kमुक्त_rcu_cpu_work *krwp;
	पूर्णांक i, j;

	krwp = container_of(to_rcu_work(work),
			    काष्ठा kमुक्त_rcu_cpu_work, rcu_work);
	krcp = krwp->krcp;

	raw_spin_lock_irqsave(&krcp->lock, flags);
	// Channels 1 and 2.
	क्रम (i = 0; i < FREE_N_CHANNELS; i++) अणु
		bkvhead[i] = krwp->bkvhead_मुक्त[i];
		krwp->bkvhead_मुक्त[i] = शून्य;
	पूर्ण

	// Channel 3.
	head = krwp->head_मुक्त;
	krwp->head_मुक्त = शून्य;
	raw_spin_unlock_irqrestore(&krcp->lock, flags);

	// Handle two first channels.
	क्रम (i = 0; i < FREE_N_CHANNELS; i++) अणु
		क्रम (; bkvhead[i]; bkvhead[i] = bnext) अणु
			bnext = bkvhead[i]->next;
			debug_rcu_bhead_unqueue(bkvhead[i]);

			rcu_lock_acquire(&rcu_callback_map);
			अगर (i == 0) अणु // kदो_स्मृति() / kमुक्त().
				trace_rcu_invoke_kमुक्त_bulk_callback(
					rcu_state.name, bkvhead[i]->nr_records,
					bkvhead[i]->records);

				kमुक्त_bulk(bkvhead[i]->nr_records,
					bkvhead[i]->records);
			पूर्ण अन्यथा अणु // vदो_स्मृति() / vमुक्त().
				क्रम (j = 0; j < bkvhead[i]->nr_records; j++) अणु
					trace_rcu_invoke_kvमुक्त_callback(
						rcu_state.name,
						bkvhead[i]->records[j], 0);

					vमुक्त(bkvhead[i]->records[j]);
				पूर्ण
			पूर्ण
			rcu_lock_release(&rcu_callback_map);

			raw_spin_lock_irqsave(&krcp->lock, flags);
			अगर (put_cached_bnode(krcp, bkvhead[i]))
				bkvhead[i] = शून्य;
			raw_spin_unlock_irqrestore(&krcp->lock, flags);

			अगर (bkvhead[i])
				मुक्त_page((अचिन्हित दीर्घ) bkvhead[i]);

			cond_resched_tasks_rcu_qs();
		पूर्ण
	पूर्ण

	/*
	 * Emergency हाल only. It can happen under low memory
	 * condition when an allocation माला_लो failed, so the "bulk"
	 * path can not be temporary मुख्यtained.
	 */
	क्रम (; head; head = next) अणु
		अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)head->func;
		व्योम *ptr = (व्योम *)head - offset;

		next = head->next;
		debug_rcu_head_unqueue((काष्ठा rcu_head *)ptr);
		rcu_lock_acquire(&rcu_callback_map);
		trace_rcu_invoke_kvमुक्त_callback(rcu_state.name, head, offset);

		अगर (!WARN_ON_ONCE(!__is_kvमुक्त_rcu_offset(offset)))
			kvमुक्त(ptr);

		rcu_lock_release(&rcu_callback_map);
		cond_resched_tasks_rcu_qs();
	पूर्ण
पूर्ण

/*
 * Schedule the kमुक्त batch RCU work to run in workqueue context after a GP.
 *
 * This function is invoked by kमुक्त_rcu_monitor() when the KFREE_DRAIN_JIFFIES
 * समयout has been reached.
 */
अटल अंतरभूत bool queue_kमुक्त_rcu_work(काष्ठा kमुक्त_rcu_cpu *krcp)
अणु
	काष्ठा kमुक्त_rcu_cpu_work *krwp;
	bool repeat = false;
	पूर्णांक i, j;

	lockdep_निश्चित_held(&krcp->lock);

	क्रम (i = 0; i < KFREE_N_BATCHES; i++) अणु
		krwp = &(krcp->krw_arr[i]);

		/*
		 * Try to detach bkvhead or head and attach it over any
		 * available corresponding मुक्त channel. It can be that
		 * a previous RCU batch is in progress, it means that
		 * immediately to queue another one is not possible so
		 * वापस false to tell caller to retry.
		 */
		अगर ((krcp->bkvhead[0] && !krwp->bkvhead_मुक्त[0]) ||
			(krcp->bkvhead[1] && !krwp->bkvhead_मुक्त[1]) ||
				(krcp->head && !krwp->head_मुक्त)) अणु
			// Channel 1 corresponds to SLAB ptrs.
			// Channel 2 corresponds to vदो_स्मृति ptrs.
			क्रम (j = 0; j < FREE_N_CHANNELS; j++) अणु
				अगर (!krwp->bkvhead_मुक्त[j]) अणु
					krwp->bkvhead_मुक्त[j] = krcp->bkvhead[j];
					krcp->bkvhead[j] = शून्य;
				पूर्ण
			पूर्ण

			// Channel 3 corresponds to emergency path.
			अगर (!krwp->head_मुक्त) अणु
				krwp->head_मुक्त = krcp->head;
				krcp->head = शून्य;
			पूर्ण

			WRITE_ONCE(krcp->count, 0);

			/*
			 * One work is per one batch, so there are three
			 * "free channels", the batch can handle. It can
			 * be that the work is in the pending state when
			 * channels have been detached following by each
			 * other.
			 */
			queue_rcu_work(प्रणाली_wq, &krwp->rcu_work);
		पूर्ण

		// Repeat अगर any "free" corresponding channel is still busy.
		अगर (krcp->bkvhead[0] || krcp->bkvhead[1] || krcp->head)
			repeat = true;
	पूर्ण

	वापस !repeat;
पूर्ण

अटल अंतरभूत व्योम kमुक्त_rcu_drain_unlock(काष्ठा kमुक्त_rcu_cpu *krcp,
					  अचिन्हित दीर्घ flags)
अणु
	// Attempt to start a new batch.
	krcp->monitor_toकरो = false;
	अगर (queue_kमुक्त_rcu_work(krcp)) अणु
		// Success! Our job is करोne here.
		raw_spin_unlock_irqrestore(&krcp->lock, flags);
		वापस;
	पूर्ण

	// Previous RCU batch still in progress, try again later.
	krcp->monitor_toकरो = true;
	schedule_delayed_work(&krcp->monitor_work, KFREE_DRAIN_JIFFIES);
	raw_spin_unlock_irqrestore(&krcp->lock, flags);
पूर्ण

/*
 * This function is invoked after the KFREE_DRAIN_JIFFIES समयout.
 * It invokes kमुक्त_rcu_drain_unlock() to attempt to start another batch.
 */
अटल व्योम kमुक्त_rcu_monitor(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kमुक्त_rcu_cpu *krcp = container_of(work, काष्ठा kमुक्त_rcu_cpu,
						 monitor_work.work);

	raw_spin_lock_irqsave(&krcp->lock, flags);
	अगर (krcp->monitor_toकरो)
		kमुक्त_rcu_drain_unlock(krcp, flags);
	अन्यथा
		raw_spin_unlock_irqrestore(&krcp->lock, flags);
पूर्ण

अटल क्रमागत hrसमयr_restart
schedule_page_work_fn(काष्ठा hrसमयr *t)
अणु
	काष्ठा kमुक्त_rcu_cpu *krcp =
		container_of(t, काष्ठा kमुक्त_rcu_cpu, hrसमयr);

	queue_work(प्रणाली_highpri_wq, &krcp->page_cache_work);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम fill_page_cache_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kvमुक्त_rcu_bulk_data *bnode;
	काष्ठा kमुक्त_rcu_cpu *krcp =
		container_of(work, काष्ठा kमुक्त_rcu_cpu,
			page_cache_work);
	अचिन्हित दीर्घ flags;
	bool pushed;
	पूर्णांक i;

	क्रम (i = 0; i < rcu_min_cached_objs; i++) अणु
		bnode = (काष्ठा kvमुक्त_rcu_bulk_data *)
			__get_मुक्त_page(GFP_KERNEL | __GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN);

		अगर (bnode) अणु
			raw_spin_lock_irqsave(&krcp->lock, flags);
			pushed = put_cached_bnode(krcp, bnode);
			raw_spin_unlock_irqrestore(&krcp->lock, flags);

			अगर (!pushed) अणु
				मुक्त_page((अचिन्हित दीर्घ) bnode);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	atomic_set(&krcp->work_in_progress, 0);
पूर्ण

अटल व्योम
run_page_cache_worker(काष्ठा kमुक्त_rcu_cpu *krcp)
अणु
	अगर (rcu_scheduler_active == RCU_SCHEDULER_RUNNING &&
			!atomic_xchg(&krcp->work_in_progress, 1)) अणु
		hrसमयr_init(&krcp->hrसमयr, CLOCK_MONOTONIC,
			HRTIMER_MODE_REL);
		krcp->hrसमयr.function = schedule_page_work_fn;
		hrसमयr_start(&krcp->hrसमयr, 0, HRTIMER_MODE_REL);
	पूर्ण
पूर्ण

// Record ptr in a page managed by krcp, with the pre-krc_this_cpu_lock()
// state specअगरied by flags.  If can_alloc is true, the caller must
// be schedulable and not be holding any locks or mutexes that might be
// acquired by the memory allocator or anything that it might invoke.
// Returns true अगर ptr was successfully recorded, अन्यथा the caller must
// use a fallback.
अटल अंतरभूत bool
add_ptr_to_bulk_krc_lock(काष्ठा kमुक्त_rcu_cpu **krcp,
	अचिन्हित दीर्घ *flags, व्योम *ptr, bool can_alloc)
अणु
	काष्ठा kvमुक्त_rcu_bulk_data *bnode;
	पूर्णांक idx;

	*krcp = krc_this_cpu_lock(flags);
	अगर (unlikely(!(*krcp)->initialized))
		वापस false;

	idx = !!is_vदो_स्मृति_addr(ptr);

	/* Check अगर a new block is required. */
	अगर (!(*krcp)->bkvhead[idx] ||
			(*krcp)->bkvhead[idx]->nr_records == KVFREE_BULK_MAX_ENTR) अणु
		bnode = get_cached_bnode(*krcp);
		अगर (!bnode && can_alloc) अणु
			krc_this_cpu_unlock(*krcp, *flags);

			// __GFP_NORETRY - allows a light-weight direct reclaim
			// what is OK from minimizing of fallback hitting poपूर्णांक of
			// view. Apart of that it क्रमbids any OOM invoking what is
			// also beneficial since we are about to release memory soon.
			//
			// __GFP_NOMEMALLOC - prevents from consuming of all the
			// memory reserves. Please note we have a fallback path.
			//
			// __GFP_NOWARN - it is supposed that an allocation can
			// be failed under low memory or high memory pressure
			// scenarios.
			bnode = (काष्ठा kvमुक्त_rcu_bulk_data *)
				__get_मुक्त_page(GFP_KERNEL | __GFP_NORETRY | __GFP_NOMEMALLOC | __GFP_NOWARN);
			*krcp = krc_this_cpu_lock(flags);
		पूर्ण

		अगर (!bnode)
			वापस false;

		/* Initialize the new block. */
		bnode->nr_records = 0;
		bnode->next = (*krcp)->bkvhead[idx];

		/* Attach it to the head. */
		(*krcp)->bkvhead[idx] = bnode;
	पूर्ण

	/* Finally insert. */
	(*krcp)->bkvhead[idx]->records
		[(*krcp)->bkvhead[idx]->nr_records++] = ptr;

	वापस true;
पूर्ण

/*
 * Queue a request क्रम lazy invocation of appropriate मुक्त routine after a
 * grace period. Please note there are three paths are मुख्यtained, two are the
 * मुख्य ones that use array of poपूर्णांकers पूर्णांकerface and third one is emergency
 * one, that is used only when the मुख्य path can not be मुख्यtained temporary,
 * due to memory pressure.
 *
 * Each kvमुक्त_call_rcu() request is added to a batch. The batch will be drained
 * every KFREE_DRAIN_JIFFIES number of jअगरfies. All the objects in the batch will
 * be मुक्त'd in workqueue context. This allows us to: batch requests together to
 * reduce the number of grace periods during heavy kमुक्त_rcu()/kvमुक्त_rcu() load.
 */
व्योम kvमुक्त_call_rcu(काष्ठा rcu_head *head, rcu_callback_t func)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kमुक्त_rcu_cpu *krcp;
	bool success;
	व्योम *ptr;

	अगर (head) अणु
		ptr = (व्योम *) head - (अचिन्हित दीर्घ) func;
	पूर्ण अन्यथा अणु
		/*
		 * Please note there is a limitation क्रम the head-less
		 * variant, that is why there is a clear rule क्रम such
		 * objects: it can be used from might_sleep() context
		 * only. For other places please embed an rcu_head to
		 * your data.
		 */
		might_sleep();
		ptr = (अचिन्हित दीर्घ *) func;
	पूर्ण

	// Queue the object but करोn't yet schedule the batch.
	अगर (debug_rcu_head_queue(ptr)) अणु
		// Probable द्विगुन kमुक्त_rcu(), just leak.
		WARN_ONCE(1, "%s(): Double-freed call. rcu_head %p\n",
			  __func__, head);

		// Mark as success and leave.
		वापस;
	पूर्ण

	kasan_record_aux_stack(ptr);
	success = add_ptr_to_bulk_krc_lock(&krcp, &flags, ptr, !head);
	अगर (!success) अणु
		run_page_cache_worker(krcp);

		अगर (head == शून्य)
			// Inline अगर kvमुक्त_rcu(one_arg) call.
			जाओ unlock_वापस;

		head->func = func;
		head->next = krcp->head;
		krcp->head = head;
		success = true;
	पूर्ण

	WRITE_ONCE(krcp->count, krcp->count + 1);

	// Set समयr to drain after KFREE_DRAIN_JIFFIES.
	अगर (rcu_scheduler_active == RCU_SCHEDULER_RUNNING &&
	    !krcp->monitor_toकरो) अणु
		krcp->monitor_toकरो = true;
		schedule_delayed_work(&krcp->monitor_work, KFREE_DRAIN_JIFFIES);
	पूर्ण

unlock_वापस:
	krc_this_cpu_unlock(krcp, flags);

	/*
	 * Inline kvमुक्त() after synchronize_rcu(). We can करो
	 * it from might_sleep() context only, so the current
	 * CPU can pass the QS state.
	 */
	अगर (!success) अणु
		debug_rcu_head_unqueue((काष्ठा rcu_head *) ptr);
		synchronize_rcu();
		kvमुक्त(ptr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvमुक्त_call_rcu);

अटल अचिन्हित दीर्घ
kमुक्त_rcu_shrink_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ count = 0;

	/* Snapshot count of all CPUs */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा kमुक्त_rcu_cpu *krcp = per_cpu_ptr(&krc, cpu);

		count += READ_ONCE(krcp->count);
	पूर्ण

	वापस count;
पूर्ण

अटल अचिन्हित दीर्घ
kमुक्त_rcu_shrink_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	पूर्णांक cpu, मुक्तd = 0;
	अचिन्हित दीर्घ flags;

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक count;
		काष्ठा kमुक्त_rcu_cpu *krcp = per_cpu_ptr(&krc, cpu);

		count = krcp->count;
		raw_spin_lock_irqsave(&krcp->lock, flags);
		अगर (krcp->monitor_toकरो)
			kमुक्त_rcu_drain_unlock(krcp, flags);
		अन्यथा
			raw_spin_unlock_irqrestore(&krcp->lock, flags);

		sc->nr_to_scan -= count;
		मुक्तd += count;

		अगर (sc->nr_to_scan <= 0)
			अवरोध;
	पूर्ण

	वापस मुक्तd == 0 ? SHRINK_STOP : मुक्तd;
पूर्ण

अटल काष्ठा shrinker kमुक्त_rcu_shrinker = अणु
	.count_objects = kमुक्त_rcu_shrink_count,
	.scan_objects = kमुक्त_rcu_shrink_scan,
	.batch = 0,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

व्योम __init kमुक्त_rcu_scheduler_running(व्योम)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा kमुक्त_rcu_cpu *krcp = per_cpu_ptr(&krc, cpu);

		raw_spin_lock_irqsave(&krcp->lock, flags);
		अगर (!krcp->head || krcp->monitor_toकरो) अणु
			raw_spin_unlock_irqrestore(&krcp->lock, flags);
			जारी;
		पूर्ण
		krcp->monitor_toकरो = true;
		schedule_delayed_work_on(cpu, &krcp->monitor_work,
					 KFREE_DRAIN_JIFFIES);
		raw_spin_unlock_irqrestore(&krcp->lock, flags);
	पूर्ण
पूर्ण

/*
 * During early boot, any blocking grace-period रुको स्वतःmatically
 * implies a grace period.  Later on, this is never the हाल क्रम PREEMPTION.
 *
 * However, because a context चयन is a grace period क्रम !PREEMPTION, any
 * blocking grace-period रुको स्वतःmatically implies a grace period अगर
 * there is only one CPU online at any poपूर्णांक समय during execution of
 * either synchronize_rcu() or synchronize_rcu_expedited().  It is OK to
 * occasionally incorrectly indicate that there are multiple CPUs online
 * when there was in fact only one the whole समय, as this just adds some
 * overhead: RCU still operates correctly.
 */
अटल पूर्णांक rcu_blocking_is_gp(व्योम)
अणु
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_PREEMPTION))
		वापस rcu_scheduler_active == RCU_SCHEDULER_INACTIVE;
	might_sleep();  /* Check क्रम RCU पढ़ो-side critical section. */
	preempt_disable();
	/*
	 * If the rcu_state.n_online_cpus counter is equal to one,
	 * there is only one CPU, and that CPU sees all prior accesses
	 * made by any CPU that was online at the समय of its access.
	 * Furthermore, अगर this counter is equal to one, its value cannot
	 * change until after the preempt_enable() below.
	 *
	 * Furthermore, अगर rcu_state.n_online_cpus is equal to one here,
	 * all later CPUs (both this one and any that come online later
	 * on) are guaranteed to see all accesses prior to this poपूर्णांक
	 * in the code, without the need क्रम additional memory barriers.
	 * Those memory barriers are provided by CPU-hotplug code.
	 */
	ret = READ_ONCE(rcu_state.n_online_cpus) <= 1;
	preempt_enable();
	वापस ret;
पूर्ण

/**
 * synchronize_rcu - रुको until a grace period has elapsed.
 *
 * Control will वापस to the caller some समय after a full grace
 * period has elapsed, in other words after all currently executing RCU
 * पढ़ो-side critical sections have completed.  Note, however, that
 * upon वापस from synchronize_rcu(), the caller might well be executing
 * concurrently with new RCU पढ़ो-side critical sections that began जबतक
 * synchronize_rcu() was रुकोing.  RCU पढ़ो-side critical sections are
 * delimited by rcu_पढ़ो_lock() and rcu_पढ़ो_unlock(), and may be nested.
 * In addition, regions of code across which पूर्णांकerrupts, preemption, or
 * softirqs have been disabled also serve as RCU पढ़ो-side critical
 * sections.  This includes hardware पूर्णांकerrupt handlers, softirq handlers,
 * and NMI handlers.
 *
 * Note that this guarantee implies further memory-ordering guarantees.
 * On प्रणालीs with more than one CPU, when synchronize_rcu() वापसs,
 * each CPU is guaranteed to have executed a full memory barrier since
 * the end of its last RCU पढ़ो-side critical section whose beginning
 * preceded the call to synchronize_rcu().  In addition, each CPU having
 * an RCU पढ़ो-side critical section that extends beyond the वापस from
 * synchronize_rcu() is guaranteed to have executed a full memory barrier
 * after the beginning of synchronize_rcu() and beक्रमe the beginning of
 * that RCU पढ़ो-side critical section.  Note that these guarantees include
 * CPUs that are offline, idle, or executing in user mode, as well as CPUs
 * that are executing in the kernel.
 *
 * Furthermore, अगर CPU A invoked synchronize_rcu(), which वापसed
 * to its caller on CPU B, then both CPU A and CPU B are guaranteed
 * to have executed a full memory barrier during the execution of
 * synchronize_rcu() -- even अगर CPU A and CPU B are the same CPU (but
 * again only अगर the प्रणाली has more than one CPU).
 */
व्योम synchronize_rcu(व्योम)
अणु
	RCU_LOCKDEP_WARN(lock_is_held(&rcu_bh_lock_map) ||
			 lock_is_held(&rcu_lock_map) ||
			 lock_is_held(&rcu_sched_lock_map),
			 "Illegal synchronize_rcu() in RCU read-side critical section");
	अगर (rcu_blocking_is_gp())
		वापस;  // Context allows vacuous grace periods.
	अगर (rcu_gp_is_expedited())
		synchronize_rcu_expedited();
	अन्यथा
		रुको_rcu_gp(call_rcu);
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_rcu);

/**
 * get_state_synchronize_rcu - Snapshot current RCU state
 *
 * Returns a cookie that is used by a later call to cond_synchronize_rcu()
 * or poll_state_synchronize_rcu() to determine whether or not a full
 * grace period has elapsed in the meanसमय.
 */
अचिन्हित दीर्घ get_state_synchronize_rcu(व्योम)
अणु
	/*
	 * Any prior manipulation of RCU-रक्षित data must happen
	 * beक्रमe the load from ->gp_seq.
	 */
	smp_mb();  /* ^^^ */
	वापस rcu_seq_snap(&rcu_state.gp_seq);
पूर्ण
EXPORT_SYMBOL_GPL(get_state_synchronize_rcu);

/**
 * start_poll_synchronize_rcu - Snapshot and start RCU grace period
 *
 * Returns a cookie that is used by a later call to cond_synchronize_rcu()
 * or poll_state_synchronize_rcu() to determine whether or not a full
 * grace period has elapsed in the meanसमय.  If the needed grace period
 * is not alपढ़ोy slated to start, notअगरies RCU core of the need क्रम that
 * grace period.
 *
 * Interrupts must be enabled क्रम the हाल where it is necessary to awaken
 * the grace-period kthपढ़ो.
 */
अचिन्हित दीर्घ start_poll_synchronize_rcu(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ gp_seq = get_state_synchronize_rcu();
	bool needwake;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;

	lockdep_निश्चित_irqs_enabled();
	local_irq_save(flags);
	rdp = this_cpu_ptr(&rcu_data);
	rnp = rdp->mynode;
	raw_spin_lock_rcu_node(rnp); // irqs alपढ़ोy disabled.
	needwake = rcu_start_this_gp(rnp, rdp, gp_seq);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	अगर (needwake)
		rcu_gp_kthपढ़ो_wake();
	वापस gp_seq;
पूर्ण
EXPORT_SYMBOL_GPL(start_poll_synchronize_rcu);

/**
 * poll_state_synchronize_rcu - Conditionally रुको क्रम an RCU grace period
 *
 * @oldstate: वापस from call to get_state_synchronize_rcu() or start_poll_synchronize_rcu()
 *
 * If a full RCU grace period has elapsed since the earlier call from
 * which oldstate was obtained, वापस @true, otherwise वापस @false.
 * If @false is वापसed, it is the caller's responsibilty to invoke this
 * function later on until it करोes वापस @true.  Alternatively, the caller
 * can explicitly रुको क्रम a grace period, क्रम example, by passing @oldstate
 * to cond_synchronize_rcu() or by directly invoking synchronize_rcu().
 *
 * Yes, this function करोes not take counter wrap पूर्णांकo account.
 * But counter wrap is harmless.  If the counter wraps, we have रुकोed क्रम
 * more than 2 billion grace periods (and way more on a 64-bit प्रणाली!).
 * Those needing to keep oldstate values क्रम very दीर्घ समय periods
 * (many hours even on 32-bit प्रणालीs) should check them occasionally
 * and either refresh them or set a flag indicating that the grace period
 * has completed.
 */
bool poll_state_synchronize_rcu(अचिन्हित दीर्घ oldstate)
अणु
	अगर (rcu_seq_करोne(&rcu_state.gp_seq, oldstate)) अणु
		smp_mb(); /* Ensure GP ends beक्रमe subsequent accesses. */
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(poll_state_synchronize_rcu);

/**
 * cond_synchronize_rcu - Conditionally रुको क्रम an RCU grace period
 *
 * @oldstate: वापस value from earlier call to get_state_synchronize_rcu()
 *
 * If a full RCU grace period has elapsed since the earlier call to
 * get_state_synchronize_rcu() or start_poll_synchronize_rcu(), just वापस.
 * Otherwise, invoke synchronize_rcu() to रुको क्रम a full grace period.
 *
 * Yes, this function करोes not take counter wrap पूर्णांकo account.  But
 * counter wrap is harmless.  If the counter wraps, we have रुकोed क्रम
 * more than 2 billion grace periods (and way more on a 64-bit प्रणाली!),
 * so रुकोing क्रम one additional grace period should be just fine.
 */
व्योम cond_synchronize_rcu(अचिन्हित दीर्घ oldstate)
अणु
	अगर (!poll_state_synchronize_rcu(oldstate))
		synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(cond_synchronize_rcu);

/*
 * Check to see अगर there is any immediate RCU-related work to be करोne by
 * the current CPU, वापसing 1 अगर so and zero otherwise.  The checks are
 * in order of increasing expense: checks that can be carried out against
 * CPU-local state are perक्रमmed first.  However, we must check क्रम CPU
 * stalls first, अन्यथा we might not get a chance.
 */
अटल पूर्णांक rcu_pending(पूर्णांक user)
अणु
	bool gp_in_progress;
	काष्ठा rcu_data *rdp = this_cpu_ptr(&rcu_data);
	काष्ठा rcu_node *rnp = rdp->mynode;

	lockdep_निश्चित_irqs_disabled();

	/* Check क्रम CPU stalls, अगर enabled. */
	check_cpu_stall(rdp);

	/* Does this CPU need a deferred NOCB wakeup? */
	अगर (rcu_nocb_need_deferred_wakeup(rdp))
		वापस 1;

	/* Is this a nohz_full CPU in userspace or idle?  (Ignore RCU अगर so.) */
	अगर ((user || rcu_is_cpu_rrupt_from_idle()) && rcu_nohz_full_cpu())
		वापस 0;

	/* Is the RCU core रुकोing क्रम a quiescent state from this CPU? */
	gp_in_progress = rcu_gp_in_progress();
	अगर (rdp->core_needs_qs && !rdp->cpu_no_qs.b.norm && gp_in_progress)
		वापस 1;

	/* Does this CPU have callbacks पढ़ोy to invoke? */
	अगर (!rcu_rdp_is_offloaded(rdp) &&
	    rcu_segcblist_पढ़ोy_cbs(&rdp->cblist))
		वापस 1;

	/* Has RCU gone idle with this CPU needing another grace period? */
	अगर (!gp_in_progress && rcu_segcblist_is_enabled(&rdp->cblist) &&
	    !rcu_rdp_is_offloaded(rdp) &&
	    !rcu_segcblist_restempty(&rdp->cblist, RCU_NEXT_READY_TAIL))
		वापस 1;

	/* Have RCU grace period completed or started?  */
	अगर (rcu_seq_current(&rnp->gp_seq) != rdp->gp_seq ||
	    unlikely(READ_ONCE(rdp->gpwrap))) /* outside lock */
		वापस 1;

	/* nothing to करो */
	वापस 0;
पूर्ण

/*
 * Helper function क्रम rcu_barrier() tracing.  If tracing is disabled,
 * the compiler is expected to optimize this away.
 */
अटल व्योम rcu_barrier_trace(स्थिर अक्षर *s, पूर्णांक cpu, अचिन्हित दीर्घ करोne)
अणु
	trace_rcu_barrier(rcu_state.name, s, cpu,
			  atomic_पढ़ो(&rcu_state.barrier_cpu_count), करोne);
पूर्ण

/*
 * RCU callback function क्रम rcu_barrier().  If we are last, wake
 * up the task executing rcu_barrier().
 *
 * Note that the value of rcu_state.barrier_sequence must be captured
 * beक्रमe the atomic_dec_and_test().  Otherwise, अगर this CPU is not last,
 * other CPUs might count the value करोwn to zero beक्रमe this CPU माला_लो
 * around to invoking rcu_barrier_trace(), which might result in bogus
 * data from the next instance of rcu_barrier().
 */
अटल व्योम rcu_barrier_callback(काष्ठा rcu_head *rhp)
अणु
	अचिन्हित दीर्घ __maybe_unused s = rcu_state.barrier_sequence;

	अगर (atomic_dec_and_test(&rcu_state.barrier_cpu_count)) अणु
		rcu_barrier_trace(TPS("LastCB"), -1, s);
		complete(&rcu_state.barrier_completion);
	पूर्ण अन्यथा अणु
		rcu_barrier_trace(TPS("CB"), -1, s);
	पूर्ण
पूर्ण

/*
 * Called with preemption disabled, and from cross-cpu IRQ context.
 */
अटल व्योम rcu_barrier_func(व्योम *cpu_in)
अणु
	uपूर्णांकptr_t cpu = (uपूर्णांकptr_t)cpu_in;
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);

	rcu_barrier_trace(TPS("IRQ"), -1, rcu_state.barrier_sequence);
	rdp->barrier_head.func = rcu_barrier_callback;
	debug_rcu_head_queue(&rdp->barrier_head);
	rcu_nocb_lock(rdp);
	WARN_ON_ONCE(!rcu_nocb_flush_bypass(rdp, शून्य, jअगरfies));
	अगर (rcu_segcblist_entrain(&rdp->cblist, &rdp->barrier_head)) अणु
		atomic_inc(&rcu_state.barrier_cpu_count);
	पूर्ण अन्यथा अणु
		debug_rcu_head_unqueue(&rdp->barrier_head);
		rcu_barrier_trace(TPS("IRQNQ"), -1,
				  rcu_state.barrier_sequence);
	पूर्ण
	rcu_nocb_unlock(rdp);
पूर्ण

/**
 * rcu_barrier - Wait until all in-flight call_rcu() callbacks complete.
 *
 * Note that this primitive करोes not necessarily रुको क्रम an RCU grace period
 * to complete.  For example, अगर there are no RCU callbacks queued anywhere
 * in the प्रणाली, then rcu_barrier() is within its rights to वापस
 * immediately, without रुकोing क्रम anything, much less an RCU grace period.
 */
व्योम rcu_barrier(व्योम)
अणु
	uपूर्णांकptr_t cpu;
	काष्ठा rcu_data *rdp;
	अचिन्हित दीर्घ s = rcu_seq_snap(&rcu_state.barrier_sequence);

	rcu_barrier_trace(TPS("Begin"), -1, s);

	/* Take mutex to serialize concurrent rcu_barrier() requests. */
	mutex_lock(&rcu_state.barrier_mutex);

	/* Did someone अन्यथा करो our work क्रम us? */
	अगर (rcu_seq_करोne(&rcu_state.barrier_sequence, s)) अणु
		rcu_barrier_trace(TPS("EarlyExit"), -1,
				  rcu_state.barrier_sequence);
		smp_mb(); /* caller's subsequent code after above check. */
		mutex_unlock(&rcu_state.barrier_mutex);
		वापस;
	पूर्ण

	/* Mark the start of the barrier operation. */
	rcu_seq_start(&rcu_state.barrier_sequence);
	rcu_barrier_trace(TPS("Inc1"), -1, rcu_state.barrier_sequence);

	/*
	 * Initialize the count to two rather than to zero in order
	 * to aव्योम a too-soon वापस to zero in हाल of an immediate
	 * invocation of the just-enqueued callback (or preemption of
	 * this task).  Exclude CPU-hotplug operations to ensure that no
	 * offline non-offloaded CPU has callbacks queued.
	 */
	init_completion(&rcu_state.barrier_completion);
	atomic_set(&rcu_state.barrier_cpu_count, 2);
	get_online_cpus();

	/*
	 * Force each CPU with callbacks to रेजिस्टर a new callback.
	 * When that callback is invoked, we will know that all of the
	 * corresponding CPU's preceding callbacks have been invoked.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		rdp = per_cpu_ptr(&rcu_data, cpu);
		अगर (cpu_is_offline(cpu) &&
		    !rcu_rdp_is_offloaded(rdp))
			जारी;
		अगर (rcu_segcblist_n_cbs(&rdp->cblist) && cpu_online(cpu)) अणु
			rcu_barrier_trace(TPS("OnlineQ"), cpu,
					  rcu_state.barrier_sequence);
			smp_call_function_single(cpu, rcu_barrier_func, (व्योम *)cpu, 1);
		पूर्ण अन्यथा अगर (rcu_segcblist_n_cbs(&rdp->cblist) &&
			   cpu_is_offline(cpu)) अणु
			rcu_barrier_trace(TPS("OfflineNoCBQ"), cpu,
					  rcu_state.barrier_sequence);
			local_irq_disable();
			rcu_barrier_func((व्योम *)cpu);
			local_irq_enable();
		पूर्ण अन्यथा अगर (cpu_is_offline(cpu)) अणु
			rcu_barrier_trace(TPS("OfflineNoCBNoQ"), cpu,
					  rcu_state.barrier_sequence);
		पूर्ण अन्यथा अणु
			rcu_barrier_trace(TPS("OnlineNQ"), cpu,
					  rcu_state.barrier_sequence);
		पूर्ण
	पूर्ण
	put_online_cpus();

	/*
	 * Now that we have an rcu_barrier_callback() callback on each
	 * CPU, and thus each counted, हटाओ the initial count.
	 */
	अगर (atomic_sub_and_test(2, &rcu_state.barrier_cpu_count))
		complete(&rcu_state.barrier_completion);

	/* Wait क्रम all rcu_barrier_callback() callbacks to be invoked. */
	रुको_क्रम_completion(&rcu_state.barrier_completion);

	/* Mark the end of the barrier operation. */
	rcu_barrier_trace(TPS("Inc2"), -1, rcu_state.barrier_sequence);
	rcu_seq_end(&rcu_state.barrier_sequence);

	/* Other rcu_barrier() invocations can now safely proceed. */
	mutex_unlock(&rcu_state.barrier_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(rcu_barrier);

/*
 * Propagate ->qsiniपंचांगask bits up the rcu_node tree to account क्रम the
 * first CPU in a given leaf rcu_node काष्ठाure coming online.  The caller
 * must hold the corresponding leaf rcu_node ->lock with पूर्णांकerrrupts
 * disabled.
 */
अटल व्योम rcu_init_new_rnp(काष्ठा rcu_node *rnp_leaf)
अणु
	दीर्घ mask;
	दीर्घ oldmask;
	काष्ठा rcu_node *rnp = rnp_leaf;

	raw_lockdep_निश्चित_held_rcu_node(rnp_leaf);
	WARN_ON_ONCE(rnp->रुको_blkd_tasks);
	क्रम (;;) अणु
		mask = rnp->grpmask;
		rnp = rnp->parent;
		अगर (rnp == शून्य)
			वापस;
		raw_spin_lock_rcu_node(rnp); /* Interrupts alपढ़ोy disabled. */
		oldmask = rnp->qsmaskinit;
		rnp->qsmaskinit |= mask;
		raw_spin_unlock_rcu_node(rnp); /* Interrupts reमुख्य disabled. */
		अगर (oldmask)
			वापस;
	पूर्ण
पूर्ण

/*
 * Do boot-समय initialization of a CPU's per-CPU RCU data.
 */
अटल व्योम __init
rcu_boot_init_percpu_data(पूर्णांक cpu)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);

	/* Set up local state, ensuring consistent view of global state. */
	rdp->grpmask = leaf_node_cpu_bit(rdp->mynode, cpu);
	INIT_WORK(&rdp->strict_work, strict_work_handler);
	WARN_ON_ONCE(rdp->dynticks_nesting != 1);
	WARN_ON_ONCE(rcu_dynticks_in_eqs(rcu_dynticks_snap(rdp)));
	rdp->rcu_ofl_gp_seq = rcu_state.gp_seq;
	rdp->rcu_ofl_gp_flags = RCU_GP_CLEANED;
	rdp->rcu_onl_gp_seq = rcu_state.gp_seq;
	rdp->rcu_onl_gp_flags = RCU_GP_CLEANED;
	rdp->cpu = cpu;
	rcu_boot_init_nocb_percpu_data(rdp);
पूर्ण

/*
 * Invoked early in the CPU-online process, when pretty much all services
 * are available.  The incoming CPU is not present.
 *
 * Initializes a CPU's per-CPU RCU data.  Note that only one online or
 * offline event can be happening at a given समय.  Note also that we can
 * accept some slop in the rsp->gp_seq access due to the fact that this
 * CPU cannot possibly have any non-offloaded RCU callbacks in flight yet.
 * And any offloaded callbacks are being numbered अन्यथाwhere.
 */
पूर्णांक rcutree_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	काष्ठा rcu_node *rnp = rcu_get_root();

	/* Set up local state, ensuring consistent view of global state. */
	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	rdp->qlen_last_fqs_check = 0;
	rdp->n_क्रमce_qs_snap = rcu_state.n_क्रमce_qs;
	rdp->blimit = blimit;
	rdp->dynticks_nesting = 1;	/* CPU not up, no tearing. */
	rcu_dynticks_eqs_online();
	raw_spin_unlock_rcu_node(rnp);		/* irqs reमुख्य disabled. */

	/*
	 * Only non-NOCB CPUs that didn't have early-boot callbacks need to be
	 * (re-)initialized.
	 */
	अगर (!rcu_segcblist_is_enabled(&rdp->cblist))
		rcu_segcblist_init(&rdp->cblist);  /* Re-enable callbacks. */

	/*
	 * Add CPU to leaf rcu_node pending-online biपंचांगask.  Any needed
	 * propagation up the rcu_node tree will happen at the beginning
	 * of the next grace period.
	 */
	rnp = rdp->mynode;
	raw_spin_lock_rcu_node(rnp);		/* irqs alपढ़ोy disabled. */
	rdp->beenonline = true;	 /* We have now been online. */
	rdp->gp_seq = READ_ONCE(rnp->gp_seq);
	rdp->gp_seq_needed = rdp->gp_seq;
	rdp->cpu_no_qs.b.norm = true;
	rdp->core_needs_qs = false;
	rdp->rcu_iw_pending = false;
	rdp->rcu_iw = IRQ_WORK_INIT_HARD(rcu_iw_handler);
	rdp->rcu_iw_gp_seq = rdp->gp_seq - 1;
	trace_rcu_grace_period(rcu_state.name, rdp->gp_seq, TPS("cpuonl"));
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	rcu_prepare_kthपढ़ोs(cpu);
	rcu_spawn_cpu_nocb_kthपढ़ो(cpu);
	WRITE_ONCE(rcu_state.n_online_cpus, rcu_state.n_online_cpus + 1);

	वापस 0;
पूर्ण

/*
 * Update RCU priority boot kthपढ़ो affinity क्रम CPU-hotplug changes.
 */
अटल व्योम rcutree_affinity_setting(अचिन्हित पूर्णांक cpu, पूर्णांक outgoing)
अणु
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);

	rcu_boost_kthपढ़ो_setaffinity(rdp->mynode, outgoing);
पूर्ण

/*
 * Near the end of the CPU-online process.  Pretty much all services
 * enabled, and the CPU is now very much alive.
 */
पूर्णांक rcutree_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;

	rdp = per_cpu_ptr(&rcu_data, cpu);
	rnp = rdp->mynode;
	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	rnp->ffmask |= rdp->grpmask;
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	अगर (rcu_scheduler_active == RCU_SCHEDULER_INACTIVE)
		वापस 0; /* Too early in boot क्रम scheduler work. */
	sync_sched_exp_online_cleanup(cpu);
	rcutree_affinity_setting(cpu, -1);

	// Stop-machine करोne, so allow nohz_full to disable tick.
	tick_dep_clear(TICK_DEP_BIT_RCU);
	वापस 0;
पूर्ण

/*
 * Near the beginning of the process.  The CPU is still very much alive
 * with pretty much all services enabled.
 */
पूर्णांक rcutree_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;

	rdp = per_cpu_ptr(&rcu_data, cpu);
	rnp = rdp->mynode;
	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	rnp->ffmask &= ~rdp->grpmask;
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);

	rcutree_affinity_setting(cpu, cpu);

	// nohz_full CPUs need the tick क्रम stop-machine to work quickly
	tick_dep_set(TICK_DEP_BIT_RCU);
	वापस 0;
पूर्ण

/*
 * Mark the specअगरied CPU as being online so that subsequent grace periods
 * (both expedited and normal) will रुको on it.  Note that this means that
 * incoming CPUs are not allowed to use RCU पढ़ो-side critical sections
 * until this function is called.  Failing to observe this restriction
 * will result in lockdep splats.
 *
 * Note that this function is special in that it is invoked directly
 * from the incoming CPU rather than from the cpuhp_step mechanism.
 * This is because this function must be invoked at a precise location.
 */
व्योम rcu_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask;
	काष्ठा rcu_data *rdp;
	काष्ठा rcu_node *rnp;
	bool newcpu;

	rdp = per_cpu_ptr(&rcu_data, cpu);
	अगर (rdp->cpu_started)
		वापस;
	rdp->cpu_started = true;

	rnp = rdp->mynode;
	mask = rdp->grpmask;
	WRITE_ONCE(rnp->ofl_seq, rnp->ofl_seq + 1);
	WARN_ON_ONCE(!(rnp->ofl_seq & 0x1));
	smp_mb(); // Pair with rcu_gp_cleanup()'s ->ofl_seq barrier().
	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	WRITE_ONCE(rnp->qsmaskinitnext, rnp->qsmaskinitnext | mask);
	newcpu = !(rnp->expmaskinitnext & mask);
	rnp->expmaskinitnext |= mask;
	/* Allow lockless access क्रम expedited grace periods. */
	smp_store_release(&rcu_state.ncpus, rcu_state.ncpus + newcpu); /* ^^^ */
	ASSERT_EXCLUSIVE_WRITER(rcu_state.ncpus);
	rcu_gpnum_ovf(rnp, rdp); /* Offline-induced counter wrap? */
	rdp->rcu_onl_gp_seq = READ_ONCE(rcu_state.gp_seq);
	rdp->rcu_onl_gp_flags = READ_ONCE(rcu_state.gp_flags);

	/* An incoming CPU should never be blocking a grace period. */
	अगर (WARN_ON_ONCE(rnp->qsmask & mask)) अणु /* RCU रुकोing on incoming CPU? */
		rcu_disable_urgency_upon_qs(rdp);
		/* Report QS -after- changing ->qsmaskinitnext! */
		rcu_report_qs_rnp(mask, rnp, rnp->gp_seq, flags);
	पूर्ण अन्यथा अणु
		raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	पूर्ण
	smp_mb(); // Pair with rcu_gp_cleanup()'s ->ofl_seq barrier().
	WRITE_ONCE(rnp->ofl_seq, rnp->ofl_seq + 1);
	WARN_ON_ONCE(rnp->ofl_seq & 0x1);
	smp_mb(); /* Ensure RCU पढ़ो-side usage follows above initialization. */
पूर्ण

/*
 * The outgoing function has no further need of RCU, so हटाओ it from
 * the rcu_node tree's ->qsmaskinitnext bit masks.
 *
 * Note that this function is special in that it is invoked directly
 * from the outgoing CPU rather than from the cpuhp_step mechanism.
 * This is because this function must be invoked at a precise location.
 */
व्योम rcu_report_dead(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ mask;
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	काष्ठा rcu_node *rnp = rdp->mynode;  /* Outgoing CPU's rdp & rnp. */

	// Do any dangling deferred wakeups.
	करो_nocb_deferred_wakeup(rdp);

	/* QS क्रम any half-करोne expedited grace period. */
	preempt_disable();
	rcu_report_exp_rdp(this_cpu_ptr(&rcu_data));
	preempt_enable();
	rcu_preempt_deferred_qs(current);

	/* Remove outgoing CPU from mask in the leaf rcu_node काष्ठाure. */
	mask = rdp->grpmask;
	WRITE_ONCE(rnp->ofl_seq, rnp->ofl_seq + 1);
	WARN_ON_ONCE(!(rnp->ofl_seq & 0x1));
	smp_mb(); // Pair with rcu_gp_cleanup()'s ->ofl_seq barrier().
	raw_spin_lock(&rcu_state.ofl_lock);
	raw_spin_lock_irqsave_rcu_node(rnp, flags); /* Enक्रमce GP memory-order guarantee. */
	rdp->rcu_ofl_gp_seq = READ_ONCE(rcu_state.gp_seq);
	rdp->rcu_ofl_gp_flags = READ_ONCE(rcu_state.gp_flags);
	अगर (rnp->qsmask & mask) अणु /* RCU रुकोing on outgoing CPU? */
		/* Report quiescent state -beक्रमe- changing ->qsmaskinitnext! */
		rcu_report_qs_rnp(mask, rnp, rnp->gp_seq, flags);
		raw_spin_lock_irqsave_rcu_node(rnp, flags);
	पूर्ण
	WRITE_ONCE(rnp->qsmaskinitnext, rnp->qsmaskinitnext & ~mask);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	raw_spin_unlock(&rcu_state.ofl_lock);
	smp_mb(); // Pair with rcu_gp_cleanup()'s ->ofl_seq barrier().
	WRITE_ONCE(rnp->ofl_seq, rnp->ofl_seq + 1);
	WARN_ON_ONCE(rnp->ofl_seq & 0x1);

	rdp->cpu_started = false;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * The outgoing CPU has just passed through the dying-idle state, and we
 * are being invoked from the CPU that was IPIed to जारी the offline
 * operation.  Migrate the outgoing CPU's callbacks to the current CPU.
 */
व्योम rcutree_migrate_callbacks(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rcu_data *my_rdp;
	काष्ठा rcu_node *my_rnp;
	काष्ठा rcu_data *rdp = per_cpu_ptr(&rcu_data, cpu);
	bool needwake;

	अगर (rcu_rdp_is_offloaded(rdp) ||
	    rcu_segcblist_empty(&rdp->cblist))
		वापस;  /* No callbacks to migrate. */

	local_irq_save(flags);
	my_rdp = this_cpu_ptr(&rcu_data);
	my_rnp = my_rdp->mynode;
	rcu_nocb_lock(my_rdp); /* irqs alपढ़ोy disabled. */
	WARN_ON_ONCE(!rcu_nocb_flush_bypass(my_rdp, शून्य, jअगरfies));
	raw_spin_lock_rcu_node(my_rnp); /* irqs alपढ़ोy disabled. */
	/* Leverage recent GPs and set GP क्रम new callbacks. */
	needwake = rcu_advance_cbs(my_rnp, rdp) ||
		   rcu_advance_cbs(my_rnp, my_rdp);
	rcu_segcblist_merge(&my_rdp->cblist, &rdp->cblist);
	needwake = needwake || rcu_advance_cbs(my_rnp, my_rdp);
	rcu_segcblist_disable(&rdp->cblist);
	WARN_ON_ONCE(rcu_segcblist_empty(&my_rdp->cblist) !=
		     !rcu_segcblist_n_cbs(&my_rdp->cblist));
	अगर (rcu_rdp_is_offloaded(my_rdp)) अणु
		raw_spin_unlock_rcu_node(my_rnp); /* irqs reमुख्य disabled. */
		__call_rcu_nocb_wake(my_rdp, true, flags);
	पूर्ण अन्यथा अणु
		rcu_nocb_unlock(my_rdp); /* irqs reमुख्य disabled. */
		raw_spin_unlock_irqrestore_rcu_node(my_rnp, flags);
	पूर्ण
	अगर (needwake)
		rcu_gp_kthपढ़ो_wake();
	lockdep_निश्चित_irqs_enabled();
	WARN_ONCE(rcu_segcblist_n_cbs(&rdp->cblist) != 0 ||
		  !rcu_segcblist_empty(&rdp->cblist),
		  "rcu_cleanup_dead_cpu: Callbacks on offline CPU %d: qlen=%lu, 1stCB=%p\n",
		  cpu, rcu_segcblist_n_cbs(&rdp->cblist),
		  rcu_segcblist_first_cb(&rdp->cblist));
पूर्ण
#पूर्ण_अगर

/*
 * On non-huge प्रणालीs, use expedited RCU grace periods to make suspend
 * and hibernation run faster.
 */
अटल पूर्णांक rcu_pm_notअगरy(काष्ठा notअगरier_block *self,
			 अचिन्हित दीर्घ action, व्योम *hcpu)
अणु
	चयन (action) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
		rcu_expedite_gp();
		अवरोध;
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_SUSPEND:
		rcu_unexpedite_gp();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

/*
 * Spawn the kthपढ़ोs that handle RCU's grace periods.
 */
अटल पूर्णांक __init rcu_spawn_gp_kthपढ़ो(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक kthपढ़ो_prio_in = kthपढ़ो_prio;
	काष्ठा rcu_node *rnp;
	काष्ठा sched_param sp;
	काष्ठा task_काष्ठा *t;

	/* Force priority पूर्णांकo range. */
	अगर (IS_ENABLED(CONFIG_RCU_BOOST) && kthपढ़ो_prio < 2
	    && IS_BUILTIN(CONFIG_RCU_TORTURE_TEST))
		kthपढ़ो_prio = 2;
	अन्यथा अगर (IS_ENABLED(CONFIG_RCU_BOOST) && kthपढ़ो_prio < 1)
		kthपढ़ो_prio = 1;
	अन्यथा अगर (kthपढ़ो_prio < 0)
		kthपढ़ो_prio = 0;
	अन्यथा अगर (kthपढ़ो_prio > 99)
		kthपढ़ो_prio = 99;

	अगर (kthपढ़ो_prio != kthपढ़ो_prio_in)
		pr_alert("rcu_spawn_gp_kthread(): Limited prio to %d from %d\n",
			 kthपढ़ो_prio, kthपढ़ो_prio_in);

	rcu_scheduler_fully_active = 1;
	t = kthपढ़ो_create(rcu_gp_kthपढ़ो, शून्य, "%s", rcu_state.name);
	अगर (WARN_ONCE(IS_ERR(t), "%s: Could not start grace-period kthread, OOM is now expected behavior\n", __func__))
		वापस 0;
	अगर (kthपढ़ो_prio) अणु
		sp.sched_priority = kthपढ़ो_prio;
		sched_setscheduler_nocheck(t, SCHED_FIFO, &sp);
	पूर्ण
	rnp = rcu_get_root();
	raw_spin_lock_irqsave_rcu_node(rnp, flags);
	WRITE_ONCE(rcu_state.gp_activity, jअगरfies);
	WRITE_ONCE(rcu_state.gp_req_activity, jअगरfies);
	// Reset .gp_activity and .gp_req_activity beक्रमe setting .gp_kthपढ़ो.
	smp_store_release(&rcu_state.gp_kthपढ़ो, t);  /* ^^^ */
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	wake_up_process(t);
	rcu_spawn_nocb_kthपढ़ोs();
	rcu_spawn_boost_kthपढ़ोs();
	वापस 0;
पूर्ण
early_initcall(rcu_spawn_gp_kthपढ़ो);

/*
 * This function is invoked towards the end of the scheduler's
 * initialization process.  Beक्रमe this is called, the idle task might
 * contain synchronous grace-period primitives (during which समय, this idle
 * task is booting the प्रणाली, and such primitives are no-ops).  After this
 * function is called, any synchronous grace-period primitives are run as
 * expedited, with the requesting task driving the grace period क्रमward.
 * A later core_initcall() rcu_set_runसमय_mode() will चयन to full
 * runसमय RCU functionality.
 */
व्योम rcu_scheduler_starting(व्योम)
अणु
	WARN_ON(num_online_cpus() != 1);
	WARN_ON(nr_context_चयनes() > 0);
	rcu_test_sync_prims();
	rcu_scheduler_active = RCU_SCHEDULER_INIT;
	rcu_test_sync_prims();
पूर्ण

/*
 * Helper function क्रम rcu_init() that initializes the rcu_state काष्ठाure.
 */
अटल व्योम __init rcu_init_one(व्योम)
अणु
	अटल स्थिर अक्षर * स्थिर buf[] = RCU_NODE_NAME_INIT;
	अटल स्थिर अक्षर * स्थिर fqs[] = RCU_FQS_NAME_INIT;
	अटल काष्ठा lock_class_key rcu_node_class[RCU_NUM_LVLS];
	अटल काष्ठा lock_class_key rcu_fqs_class[RCU_NUM_LVLS];

	पूर्णांक levelspपढ़ो[RCU_NUM_LVLS];		/* kids/node in each level. */
	पूर्णांक cpustride = 1;
	पूर्णांक i;
	पूर्णांक j;
	काष्ठा rcu_node *rnp;

	BUILD_BUG_ON(RCU_NUM_LVLS > ARRAY_SIZE(buf));  /* Fix buf[] init! */

	/* Silence gcc 4.8 false positive about array index out of range. */
	अगर (rcu_num_lvls <= 0 || rcu_num_lvls > RCU_NUM_LVLS)
		panic("rcu_init_one: rcu_num_lvls out of range");

	/* Initialize the level-tracking arrays. */

	क्रम (i = 1; i < rcu_num_lvls; i++)
		rcu_state.level[i] =
			rcu_state.level[i - 1] + num_rcu_lvl[i - 1];
	rcu_init_levelspपढ़ो(levelspपढ़ो, num_rcu_lvl);

	/* Initialize the elements themselves, starting from the leaves. */

	क्रम (i = rcu_num_lvls - 1; i >= 0; i--) अणु
		cpustride *= levelspपढ़ो[i];
		rnp = rcu_state.level[i];
		क्रम (j = 0; j < num_rcu_lvl[i]; j++, rnp++) अणु
			raw_spin_lock_init(&ACCESS_PRIVATE(rnp, lock));
			lockdep_set_class_and_name(&ACCESS_PRIVATE(rnp, lock),
						   &rcu_node_class[i], buf[i]);
			raw_spin_lock_init(&rnp->fqslock);
			lockdep_set_class_and_name(&rnp->fqslock,
						   &rcu_fqs_class[i], fqs[i]);
			rnp->gp_seq = rcu_state.gp_seq;
			rnp->gp_seq_needed = rcu_state.gp_seq;
			rnp->completedqs = rcu_state.gp_seq;
			rnp->qsmask = 0;
			rnp->qsmaskinit = 0;
			rnp->grplo = j * cpustride;
			rnp->grphi = (j + 1) * cpustride - 1;
			अगर (rnp->grphi >= nr_cpu_ids)
				rnp->grphi = nr_cpu_ids - 1;
			अगर (i == 0) अणु
				rnp->grpnum = 0;
				rnp->grpmask = 0;
				rnp->parent = शून्य;
			पूर्ण अन्यथा अणु
				rnp->grpnum = j % levelspपढ़ो[i - 1];
				rnp->grpmask = BIT(rnp->grpnum);
				rnp->parent = rcu_state.level[i - 1] +
					      j / levelspपढ़ो[i - 1];
			पूर्ण
			rnp->level = i;
			INIT_LIST_HEAD(&rnp->blkd_tasks);
			rcu_init_one_nocb(rnp);
			init_रुकोqueue_head(&rnp->exp_wq[0]);
			init_रुकोqueue_head(&rnp->exp_wq[1]);
			init_रुकोqueue_head(&rnp->exp_wq[2]);
			init_रुकोqueue_head(&rnp->exp_wq[3]);
			spin_lock_init(&rnp->exp_lock);
		पूर्ण
	पूर्ण

	init_sरुको_queue_head(&rcu_state.gp_wq);
	init_sरुको_queue_head(&rcu_state.expedited_wq);
	rnp = rcu_first_leaf_node();
	क्रम_each_possible_cpu(i) अणु
		जबतक (i > rnp->grphi)
			rnp++;
		per_cpu_ptr(&rcu_data, i)->mynode = rnp;
		rcu_boot_init_percpu_data(i);
	पूर्ण
पूर्ण

/*
 * Compute the rcu_node tree geometry from kernel parameters.  This cannot
 * replace the definitions in tree.h because those are needed to size
 * the ->node array in the rcu_state काष्ठाure.
 */
अटल व्योम __init rcu_init_geometry(व्योम)
अणु
	uदीर्घ d;
	पूर्णांक i;
	पूर्णांक rcu_capacity[RCU_NUM_LVLS];

	/*
	 * Initialize any unspecअगरied boot parameters.
	 * The शेष values of jअगरfies_till_first_fqs and
	 * jअगरfies_till_next_fqs are set to the RCU_JIFFIES_TILL_FORCE_QS
	 * value, which is a function of HZ, then adding one क्रम each
	 * RCU_JIFFIES_FQS_DIV CPUs that might be on the प्रणाली.
	 */
	d = RCU_JIFFIES_TILL_FORCE_QS + nr_cpu_ids / RCU_JIFFIES_FQS_DIV;
	अगर (jअगरfies_till_first_fqs == अच_दीर्घ_उच्च)
		jअगरfies_till_first_fqs = d;
	अगर (jअगरfies_till_next_fqs == अच_दीर्घ_उच्च)
		jअगरfies_till_next_fqs = d;
	adjust_jअगरfies_till_sched_qs();

	/* If the compile-समय values are accurate, just leave. */
	अगर (rcu_fanout_leaf == RCU_FANOUT_LEAF &&
	    nr_cpu_ids == NR_CPUS)
		वापस;
	pr_info("Adjusting geometry for rcu_fanout_leaf=%d, nr_cpu_ids=%u\n",
		rcu_fanout_leaf, nr_cpu_ids);

	/*
	 * The boot-समय rcu_fanout_leaf parameter must be at least two
	 * and cannot exceed the number of bits in the rcu_node masks.
	 * Complain and fall back to the compile-समय values अगर this
	 * limit is exceeded.
	 */
	अगर (rcu_fanout_leaf < 2 ||
	    rcu_fanout_leaf > माप(अचिन्हित दीर्घ) * 8) अणु
		rcu_fanout_leaf = RCU_FANOUT_LEAF;
		WARN_ON(1);
		वापस;
	पूर्ण

	/*
	 * Compute number of nodes that can be handled an rcu_node tree
	 * with the given number of levels.
	 */
	rcu_capacity[0] = rcu_fanout_leaf;
	क्रम (i = 1; i < RCU_NUM_LVLS; i++)
		rcu_capacity[i] = rcu_capacity[i - 1] * RCU_FANOUT;

	/*
	 * The tree must be able to accommodate the configured number of CPUs.
	 * If this limit is exceeded, fall back to the compile-समय values.
	 */
	अगर (nr_cpu_ids > rcu_capacity[RCU_NUM_LVLS - 1]) अणु
		rcu_fanout_leaf = RCU_FANOUT_LEAF;
		WARN_ON(1);
		वापस;
	पूर्ण

	/* Calculate the number of levels in the tree. */
	क्रम (i = 0; nr_cpu_ids > rcu_capacity[i]; i++) अणु
	पूर्ण
	rcu_num_lvls = i + 1;

	/* Calculate the number of rcu_nodes at each level of the tree. */
	क्रम (i = 0; i < rcu_num_lvls; i++) अणु
		पूर्णांक cap = rcu_capacity[(rcu_num_lvls - 1) - i];
		num_rcu_lvl[i] = DIV_ROUND_UP(nr_cpu_ids, cap);
	पूर्ण

	/* Calculate the total number of rcu_node काष्ठाures. */
	rcu_num_nodes = 0;
	क्रम (i = 0; i < rcu_num_lvls; i++)
		rcu_num_nodes += num_rcu_lvl[i];
पूर्ण

/*
 * Dump out the काष्ठाure of the rcu_node combining tree associated
 * with the rcu_state काष्ठाure.
 */
अटल व्योम __init rcu_dump_rcu_node_tree(व्योम)
अणु
	पूर्णांक level = 0;
	काष्ठा rcu_node *rnp;

	pr_info("rcu_node tree layout dump\n");
	pr_info(" ");
	rcu_क्रम_each_node_bपढ़ोth_first(rnp) अणु
		अगर (rnp->level != level) अणु
			pr_cont("\n");
			pr_info(" ");
			level = rnp->level;
		पूर्ण
		pr_cont("%d:%d ^%d  ", rnp->grplo, rnp->grphi, rnp->grpnum);
	पूर्ण
	pr_cont("\n");
पूर्ण

काष्ठा workqueue_काष्ठा *rcu_gp_wq;
काष्ठा workqueue_काष्ठा *rcu_par_gp_wq;

अटल व्योम __init kमुक्त_rcu_batch_init(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक i;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा kमुक्त_rcu_cpu *krcp = per_cpu_ptr(&krc, cpu);

		क्रम (i = 0; i < KFREE_N_BATCHES; i++) अणु
			INIT_RCU_WORK(&krcp->krw_arr[i].rcu_work, kमुक्त_rcu_work);
			krcp->krw_arr[i].krcp = krcp;
		पूर्ण

		INIT_DELAYED_WORK(&krcp->monitor_work, kमुक्त_rcu_monitor);
		INIT_WORK(&krcp->page_cache_work, fill_page_cache_func);
		krcp->initialized = true;
	पूर्ण
	अगर (रेजिस्टर_shrinker(&kमुक्त_rcu_shrinker))
		pr_err("Failed to register kfree_rcu() shrinker!\n");
पूर्ण

व्योम __init rcu_init(व्योम)
अणु
	पूर्णांक cpu;

	rcu_early_boot_tests();

	kमुक्त_rcu_batch_init();
	rcu_bootup_announce();
	rcu_init_geometry();
	rcu_init_one();
	अगर (dump_tree)
		rcu_dump_rcu_node_tree();
	अगर (use_softirq)
		खोलो_softirq(RCU_SOFTIRQ, rcu_core_si);

	/*
	 * We करोn't need protection against CPU-hotplug here because
	 * this is called early in boot, beक्रमe either पूर्णांकerrupts
	 * or the scheduler are operational.
	 */
	pm_notअगरier(rcu_pm_notअगरy, 0);
	क्रम_each_online_cpu(cpu) अणु
		rcutree_prepare_cpu(cpu);
		rcu_cpu_starting(cpu);
		rcutree_online_cpu(cpu);
	पूर्ण

	/* Create workqueue क्रम expedited GPs and क्रम Tree SRCU. */
	rcu_gp_wq = alloc_workqueue("rcu_gp", WQ_MEM_RECLAIM, 0);
	WARN_ON(!rcu_gp_wq);
	rcu_par_gp_wq = alloc_workqueue("rcu_par_gp", WQ_MEM_RECLAIM, 0);
	WARN_ON(!rcu_par_gp_wq);
	srcu_init();

	/* Fill in शेष value क्रम rcutree.qovld boot parameter. */
	/* -After- the rcu_node ->lock fields are initialized! */
	अगर (qovld < 0)
		qovld_calc = DEFAULT_RCU_QOVLD_MULT * qhimark;
	अन्यथा
		qovld_calc = qovld;
पूर्ण

#समावेश "tree_stall.h"
#समावेश "tree_exp.h"
#समावेश "tree_plugin.h"
