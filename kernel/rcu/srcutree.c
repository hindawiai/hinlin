<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Sleepable Read-Copy Update mechanism क्रम mutual exclusion.
 *
 * Copyright (C) IBM Corporation, 2006
 * Copyright (C) Fujitsu, 2012
 *
 * Authors: Paul McKenney <paulmck@linux.ibm.com>
 *	   Lai Jiangshan <laijs@cn.fujitsu.com>
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *		Documentation/RCU/ *.txt
 *
 */

#घोषणा pr_fmt(fmt) "rcu: " fmt

#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/percpu.h>
#समावेश <linux/preempt.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/srcu.h>

#समावेश "rcu.h"
#समावेश "rcu_segcblist.h"

/* Holकरोff in nanoseconds क्रम स्वतः-expediting. */
#घोषणा DEFAULT_SRCU_EXP_HOLDOFF (25 * 1000)
अटल uदीर्घ exp_holकरोff = DEFAULT_SRCU_EXP_HOLDOFF;
module_param(exp_holकरोff, uदीर्घ, 0444);

/* Overflow-check frequency.  N bits roughly says every 2**N grace periods. */
अटल uदीर्घ counter_wrap_check = (अच_दीर्घ_उच्च >> 2);
module_param(counter_wrap_check, uदीर्घ, 0444);

/* Early-boot callback-management, so early that no lock is required! */
अटल LIST_HEAD(srcu_boot_list);
अटल bool __पढ़ो_mostly srcu_init_करोne;

अटल व्योम srcu_invoke_callbacks(काष्ठा work_काष्ठा *work);
अटल व्योम srcu_reschedule(काष्ठा srcu_काष्ठा *ssp, अचिन्हित दीर्घ delay);
अटल व्योम process_srcu(काष्ठा work_काष्ठा *work);
अटल व्योम srcu_delay_समयr(काष्ठा समयr_list *t);

/* Wrappers क्रम lock acquisition and release, see raw_spin_lock_rcu_node(). */
#घोषणा spin_lock_rcu_node(p)					\
करो अणु									\
	spin_lock(&ACCESS_PRIVATE(p, lock));			\
	smp_mb__after_unlock_lock();					\
पूर्ण जबतक (0)

#घोषणा spin_unlock_rcu_node(p) spin_unlock(&ACCESS_PRIVATE(p, lock))

#घोषणा spin_lock_irq_rcu_node(p)					\
करो अणु									\
	spin_lock_irq(&ACCESS_PRIVATE(p, lock));			\
	smp_mb__after_unlock_lock();					\
पूर्ण जबतक (0)

#घोषणा spin_unlock_irq_rcu_node(p)					\
	spin_unlock_irq(&ACCESS_PRIVATE(p, lock))

#घोषणा spin_lock_irqsave_rcu_node(p, flags)			\
करो अणु									\
	spin_lock_irqsave(&ACCESS_PRIVATE(p, lock), flags);	\
	smp_mb__after_unlock_lock();					\
पूर्ण जबतक (0)

#घोषणा spin_unlock_irqrestore_rcu_node(p, flags)			\
	spin_unlock_irqrestore(&ACCESS_PRIVATE(p, lock), flags)	\

/*
 * Initialize SRCU combining tree.  Note that अटलally allocated
 * srcu_काष्ठा काष्ठाures might alपढ़ोy have srcu_पढ़ो_lock() and
 * srcu_पढ़ो_unlock() running against them.  So अगर the is_अटल parameter
 * is set, करोn't initialize ->srcu_lock_count[] and ->srcu_unlock_count[].
 */
अटल व्योम init_srcu_काष्ठा_nodes(काष्ठा srcu_काष्ठा *ssp, bool is_अटल)
अणु
	पूर्णांक cpu;
	पूर्णांक i;
	पूर्णांक level = 0;
	पूर्णांक levelspपढ़ो[RCU_NUM_LVLS];
	काष्ठा srcu_data *sdp;
	काष्ठा srcu_node *snp;
	काष्ठा srcu_node *snp_first;

	/* Work out the overall tree geometry. */
	ssp->level[0] = &ssp->node[0];
	क्रम (i = 1; i < rcu_num_lvls; i++)
		ssp->level[i] = ssp->level[i - 1] + num_rcu_lvl[i - 1];
	rcu_init_levelspपढ़ो(levelspपढ़ो, num_rcu_lvl);

	/* Each pass through this loop initializes one srcu_node काष्ठाure. */
	srcu_क्रम_each_node_bपढ़ोth_first(ssp, snp) अणु
		spin_lock_init(&ACCESS_PRIVATE(snp, lock));
		WARN_ON_ONCE(ARRAY_SIZE(snp->srcu_have_cbs) !=
			     ARRAY_SIZE(snp->srcu_data_have_cbs));
		क्रम (i = 0; i < ARRAY_SIZE(snp->srcu_have_cbs); i++) अणु
			snp->srcu_have_cbs[i] = 0;
			snp->srcu_data_have_cbs[i] = 0;
		पूर्ण
		snp->srcu_gp_seq_needed_exp = 0;
		snp->grplo = -1;
		snp->grphi = -1;
		अगर (snp == &ssp->node[0]) अणु
			/* Root node, special हाल. */
			snp->srcu_parent = शून्य;
			जारी;
		पूर्ण

		/* Non-root node. */
		अगर (snp == ssp->level[level + 1])
			level++;
		snp->srcu_parent = ssp->level[level - 1] +
				   (snp - ssp->level[level]) /
				   levelspपढ़ो[level - 1];
	पूर्ण

	/*
	 * Initialize the per-CPU srcu_data array, which feeds पूर्णांकo the
	 * leaves of the srcu_node tree.
	 */
	WARN_ON_ONCE(ARRAY_SIZE(sdp->srcu_lock_count) !=
		     ARRAY_SIZE(sdp->srcu_unlock_count));
	level = rcu_num_lvls - 1;
	snp_first = ssp->level[level];
	क्रम_each_possible_cpu(cpu) अणु
		sdp = per_cpu_ptr(ssp->sda, cpu);
		spin_lock_init(&ACCESS_PRIVATE(sdp, lock));
		rcu_segcblist_init(&sdp->srcu_cblist);
		sdp->srcu_cblist_invoking = false;
		sdp->srcu_gp_seq_needed = ssp->srcu_gp_seq;
		sdp->srcu_gp_seq_needed_exp = ssp->srcu_gp_seq;
		sdp->mynode = &snp_first[cpu / levelspपढ़ो[level]];
		क्रम (snp = sdp->mynode; snp != शून्य; snp = snp->srcu_parent) अणु
			अगर (snp->grplo < 0)
				snp->grplo = cpu;
			snp->grphi = cpu;
		पूर्ण
		sdp->cpu = cpu;
		INIT_WORK(&sdp->work, srcu_invoke_callbacks);
		समयr_setup(&sdp->delay_work, srcu_delay_समयr, 0);
		sdp->ssp = ssp;
		sdp->grpmask = 1 << (cpu - sdp->mynode->grplo);
		अगर (is_अटल)
			जारी;

		/* Dynamically allocated, better be no srcu_पढ़ो_locks()! */
		क्रम (i = 0; i < ARRAY_SIZE(sdp->srcu_lock_count); i++) अणु
			sdp->srcu_lock_count[i] = 0;
			sdp->srcu_unlock_count[i] = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Initialize non-compile-समय initialized fields, including the
 * associated srcu_node and srcu_data काष्ठाures.  The is_अटल
 * parameter is passed through to init_srcu_काष्ठा_nodes(), and
 * also tells us that ->sda has alपढ़ोy been wired up to srcu_data.
 */
अटल पूर्णांक init_srcu_काष्ठा_fields(काष्ठा srcu_काष्ठा *ssp, bool is_अटल)
अणु
	mutex_init(&ssp->srcu_cb_mutex);
	mutex_init(&ssp->srcu_gp_mutex);
	ssp->srcu_idx = 0;
	ssp->srcu_gp_seq = 0;
	ssp->srcu_barrier_seq = 0;
	mutex_init(&ssp->srcu_barrier_mutex);
	atomic_set(&ssp->srcu_barrier_cpu_cnt, 0);
	INIT_DELAYED_WORK(&ssp->work, process_srcu);
	अगर (!is_अटल)
		ssp->sda = alloc_percpu(काष्ठा srcu_data);
	अगर (!ssp->sda)
		वापस -ENOMEM;
	init_srcu_काष्ठा_nodes(ssp, is_अटल);
	ssp->srcu_gp_seq_needed_exp = 0;
	ssp->srcu_last_gp_end = kसमय_get_mono_fast_ns();
	smp_store_release(&ssp->srcu_gp_seq_needed, 0); /* Init करोne. */
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

पूर्णांक __init_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp, स्थिर अक्षर *name,
		       काष्ठा lock_class_key *key)
अणु
	/* Don't re-initialize a lock जबतक it is held. */
	debug_check_no_locks_मुक्तd((व्योम *)ssp, माप(*ssp));
	lockdep_init_map(&ssp->dep_map, name, key, 0);
	spin_lock_init(&ACCESS_PRIVATE(ssp, lock));
	वापस init_srcu_काष्ठा_fields(ssp, false);
पूर्ण
EXPORT_SYMBOL_GPL(__init_srcu_काष्ठा);

#अन्यथा /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

/**
 * init_srcu_काष्ठा - initialize a sleep-RCU काष्ठाure
 * @ssp: काष्ठाure to initialize.
 *
 * Must invoke this on a given srcu_काष्ठा beक्रमe passing that srcu_काष्ठा
 * to any other function.  Each srcu_काष्ठा represents a separate करोमुख्य
 * of SRCU protection.
 */
पूर्णांक init_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp)
अणु
	spin_lock_init(&ACCESS_PRIVATE(ssp, lock));
	वापस init_srcu_काष्ठा_fields(ssp, false);
पूर्ण
EXPORT_SYMBOL_GPL(init_srcu_काष्ठा);

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

/*
 * First-use initialization of अटलally allocated srcu_काष्ठा
 * काष्ठाure.  Wiring up the combining tree is more than can be
 * करोne with compile-समय initialization, so this check is added
 * to each update-side SRCU primitive.  Use ssp->lock, which -is-
 * compile-समय initialized, to resolve races involving multiple
 * CPUs trying to garner first-use privileges.
 */
अटल व्योम check_init_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp)
अणु
	अचिन्हित दीर्घ flags;

	/* The smp_load_acquire() pairs with the smp_store_release(). */
	अगर (!rcu_seq_state(smp_load_acquire(&ssp->srcu_gp_seq_needed))) /*^^^*/
		वापस; /* Alपढ़ोy initialized. */
	spin_lock_irqsave_rcu_node(ssp, flags);
	अगर (!rcu_seq_state(ssp->srcu_gp_seq_needed)) अणु
		spin_unlock_irqrestore_rcu_node(ssp, flags);
		वापस;
	पूर्ण
	init_srcu_काष्ठा_fields(ssp, true);
	spin_unlock_irqrestore_rcu_node(ssp, flags);
पूर्ण

/*
 * Returns approximate total of the पढ़ोers' ->srcu_lock_count[] values
 * क्रम the rank of per-CPU counters specअगरied by idx.
 */
अटल अचिन्हित दीर्घ srcu_पढ़ोers_lock_idx(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ sum = 0;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा srcu_data *cpuc = per_cpu_ptr(ssp->sda, cpu);

		sum += READ_ONCE(cpuc->srcu_lock_count[idx]);
	पूर्ण
	वापस sum;
पूर्ण

/*
 * Returns approximate total of the पढ़ोers' ->srcu_unlock_count[] values
 * क्रम the rank of per-CPU counters specअगरied by idx.
 */
अटल अचिन्हित दीर्घ srcu_पढ़ोers_unlock_idx(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ sum = 0;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा srcu_data *cpuc = per_cpu_ptr(ssp->sda, cpu);

		sum += READ_ONCE(cpuc->srcu_unlock_count[idx]);
	पूर्ण
	वापस sum;
पूर्ण

/*
 * Return true अगर the number of pre-existing पढ़ोers is determined to
 * be zero.
 */
अटल bool srcu_पढ़ोers_active_idx_check(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx)
अणु
	अचिन्हित दीर्घ unlocks;

	unlocks = srcu_पढ़ोers_unlock_idx(ssp, idx);

	/*
	 * Make sure that a lock is always counted अगर the corresponding
	 * unlock is counted. Needs to be a smp_mb() as the पढ़ो side may
	 * contain a पढ़ो from a variable that is written to beक्रमe the
	 * synchronize_srcu() in the ग_लिखो side. In this हाल smp_mb()s
	 * A and B act like the store buffering pattern.
	 *
	 * This smp_mb() also pairs with smp_mb() C to prevent accesses
	 * after the synchronize_srcu() from being executed beक्रमe the
	 * grace period ends.
	 */
	smp_mb(); /* A */

	/*
	 * If the locks are the same as the unlocks, then there must have
	 * been no पढ़ोers on this index at some समय in between. This करोes
	 * not mean that there are no more पढ़ोers, as one could have पढ़ो
	 * the current index but not have incremented the lock counter yet.
	 *
	 * So suppose that the updater is preempted here क्रम so दीर्घ
	 * that more than अच_दीर्घ_उच्च non-nested पढ़ोers come and go in
	 * the meanसमय.  It turns out that this cannot result in overflow
	 * because अगर a पढ़ोer modअगरies its unlock count after we पढ़ो it
	 * above, then that पढ़ोer's next load of ->srcu_idx is guaranteed
	 * to get the new value, which will cause it to operate on the
	 * other bank of counters, where it cannot contribute to the
	 * overflow of these counters.  This means that there is a maximum
	 * of 2*NR_CPUS increments, which cannot overflow given current
	 * प्रणालीs, especially not on 64-bit प्रणालीs.
	 *
	 * OK, how about nesting?  This करोes impose a limit on nesting
	 * of न्यूनमान(अच_दीर्घ_उच्च/NR_CPUS/2), which should be sufficient,
	 * especially on 64-bit प्रणालीs.
	 */
	वापस srcu_पढ़ोers_lock_idx(ssp, idx) == unlocks;
पूर्ण

/**
 * srcu_पढ़ोers_active - वापसs true अगर there are पढ़ोers. and false
 *                       otherwise
 * @ssp: which srcu_काष्ठा to count active पढ़ोers (holding srcu_पढ़ो_lock).
 *
 * Note that this is not an atomic primitive, and can thereक्रमe suffer
 * severe errors when invoked on an active srcu_काष्ठा.  That said, it
 * can be useful as an error check at cleanup समय.
 */
अटल bool srcu_पढ़ोers_active(काष्ठा srcu_काष्ठा *ssp)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ sum = 0;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा srcu_data *cpuc = per_cpu_ptr(ssp->sda, cpu);

		sum += READ_ONCE(cpuc->srcu_lock_count[0]);
		sum += READ_ONCE(cpuc->srcu_lock_count[1]);
		sum -= READ_ONCE(cpuc->srcu_unlock_count[0]);
		sum -= READ_ONCE(cpuc->srcu_unlock_count[1]);
	पूर्ण
	वापस sum;
पूर्ण

#घोषणा SRCU_INTERVAL		1

/*
 * Return grace-period delay, zero अगर there are expedited grace
 * periods pending, SRCU_INTERVAL otherwise.
 */
अटल अचिन्हित दीर्घ srcu_get_delay(काष्ठा srcu_काष्ठा *ssp)
अणु
	अगर (ULONG_CMP_LT(READ_ONCE(ssp->srcu_gp_seq),
			 READ_ONCE(ssp->srcu_gp_seq_needed_exp)))
		वापस 0;
	वापस SRCU_INTERVAL;
पूर्ण

/**
 * cleanup_srcu_काष्ठा - deस्थिरruct a sleep-RCU काष्ठाure
 * @ssp: काष्ठाure to clean up.
 *
 * Must invoke this after you are finished using a given srcu_काष्ठा that
 * was initialized via init_srcu_काष्ठा(), अन्यथा you leak memory.
 */
व्योम cleanup_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp)
अणु
	पूर्णांक cpu;

	अगर (WARN_ON(!srcu_get_delay(ssp)))
		वापस; /* Just leak it! */
	अगर (WARN_ON(srcu_पढ़ोers_active(ssp)))
		वापस; /* Just leak it! */
	flush_delayed_work(&ssp->work);
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा srcu_data *sdp = per_cpu_ptr(ssp->sda, cpu);

		del_समयr_sync(&sdp->delay_work);
		flush_work(&sdp->work);
		अगर (WARN_ON(rcu_segcblist_n_cbs(&sdp->srcu_cblist)))
			वापस; /* Forgot srcu_barrier(), so just leak it! */
	पूर्ण
	अगर (WARN_ON(rcu_seq_state(READ_ONCE(ssp->srcu_gp_seq)) != SRCU_STATE_IDLE) ||
	    WARN_ON(srcu_पढ़ोers_active(ssp))) अणु
		pr_info("%s: Active srcu_struct %p state: %d\n",
			__func__, ssp, rcu_seq_state(READ_ONCE(ssp->srcu_gp_seq)));
		वापस; /* Caller क्रमgot to stop करोing call_srcu()? */
	पूर्ण
	मुक्त_percpu(ssp->sda);
	ssp->sda = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cleanup_srcu_काष्ठा);

/*
 * Counts the new पढ़ोer in the appropriate per-CPU element of the
 * srcu_काष्ठा.
 * Returns an index that must be passed to the matching srcu_पढ़ो_unlock().
 */
पूर्णांक __srcu_पढ़ो_lock(काष्ठा srcu_काष्ठा *ssp)
अणु
	पूर्णांक idx;

	idx = READ_ONCE(ssp->srcu_idx) & 0x1;
	this_cpu_inc(ssp->sda->srcu_lock_count[idx]);
	smp_mb(); /* B */  /* Aव्योम leaking the critical section. */
	वापस idx;
पूर्ण
EXPORT_SYMBOL_GPL(__srcu_पढ़ो_lock);

/*
 * Removes the count क्रम the old पढ़ोer from the appropriate per-CPU
 * element of the srcu_काष्ठा.  Note that this may well be a dअगरferent
 * CPU than that which was incremented by the corresponding srcu_पढ़ो_lock().
 */
व्योम __srcu_पढ़ो_unlock(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx)
अणु
	smp_mb(); /* C */  /* Aव्योम leaking the critical section. */
	this_cpu_inc(ssp->sda->srcu_unlock_count[idx]);
पूर्ण
EXPORT_SYMBOL_GPL(__srcu_पढ़ो_unlock);

/*
 * We use an adaptive strategy क्रम synchronize_srcu() and especially क्रम
 * synchronize_srcu_expedited().  We spin क्रम a fixed समय period
 * (defined below) to allow SRCU पढ़ोers to निकास their पढ़ो-side critical
 * sections.  If there are still some पढ़ोers after a few microseconds,
 * we repeatedly block क्रम 1-millisecond समय periods.
 */
#घोषणा SRCU_RETRY_CHECK_DELAY		5

/*
 * Start an SRCU grace period.
 */
अटल व्योम srcu_gp_start(काष्ठा srcu_काष्ठा *ssp)
अणु
	काष्ठा srcu_data *sdp = this_cpu_ptr(ssp->sda);
	पूर्णांक state;

	lockdep_निश्चित_held(&ACCESS_PRIVATE(ssp, lock));
	WARN_ON_ONCE(ULONG_CMP_GE(ssp->srcu_gp_seq, ssp->srcu_gp_seq_needed));
	spin_lock_rcu_node(sdp);  /* Interrupts alपढ़ोy disabled. */
	rcu_segcblist_advance(&sdp->srcu_cblist,
			      rcu_seq_current(&ssp->srcu_gp_seq));
	(व्योम)rcu_segcblist_accelerate(&sdp->srcu_cblist,
				       rcu_seq_snap(&ssp->srcu_gp_seq));
	spin_unlock_rcu_node(sdp);  /* Interrupts reमुख्य disabled. */
	smp_mb(); /* Order prior store to ->srcu_gp_seq_needed vs. GP start. */
	rcu_seq_start(&ssp->srcu_gp_seq);
	state = rcu_seq_state(ssp->srcu_gp_seq);
	WARN_ON_ONCE(state != SRCU_STATE_SCAN1);
पूर्ण


अटल व्योम srcu_delay_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा srcu_data *sdp = container_of(t, काष्ठा srcu_data, delay_work);

	queue_work_on(sdp->cpu, rcu_gp_wq, &sdp->work);
पूर्ण

अटल व्योम srcu_queue_delayed_work_on(काष्ठा srcu_data *sdp,
				       अचिन्हित दीर्घ delay)
अणु
	अगर (!delay) अणु
		queue_work_on(sdp->cpu, rcu_gp_wq, &sdp->work);
		वापस;
	पूर्ण

	समयr_reduce(&sdp->delay_work, jअगरfies + delay);
पूर्ण

/*
 * Schedule callback invocation क्रम the specअगरied srcu_data काष्ठाure,
 * अगर possible, on the corresponding CPU.
 */
अटल व्योम srcu_schedule_cbs_sdp(काष्ठा srcu_data *sdp, अचिन्हित दीर्घ delay)
अणु
	srcu_queue_delayed_work_on(sdp, delay);
पूर्ण

/*
 * Schedule callback invocation क्रम all srcu_data काष्ठाures associated
 * with the specअगरied srcu_node काष्ठाure that have callbacks क्रम the
 * just-completed grace period, the one corresponding to idx.  If possible,
 * schedule this invocation on the corresponding CPUs.
 */
अटल व्योम srcu_schedule_cbs_snp(काष्ठा srcu_काष्ठा *ssp, काष्ठा srcu_node *snp,
				  अचिन्हित दीर्घ mask, अचिन्हित दीर्घ delay)
अणु
	पूर्णांक cpu;

	क्रम (cpu = snp->grplo; cpu <= snp->grphi; cpu++) अणु
		अगर (!(mask & (1 << (cpu - snp->grplo))))
			जारी;
		srcu_schedule_cbs_sdp(per_cpu_ptr(ssp->sda, cpu), delay);
	पूर्ण
पूर्ण

/*
 * Note the end of an SRCU grace period.  Initiates callback invocation
 * and starts a new grace period अगर needed.
 *
 * The ->srcu_cb_mutex acquisition करोes not protect any data, but
 * instead prevents more than one grace period from starting जबतक we
 * are initiating callback invocation.  This allows the ->srcu_have_cbs[]
 * array to have a finite number of elements.
 */
अटल व्योम srcu_gp_end(काष्ठा srcu_काष्ठा *ssp)
अणु
	अचिन्हित दीर्घ cbdelay;
	bool cbs;
	bool last_lvl;
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ gpseq;
	पूर्णांक idx;
	अचिन्हित दीर्घ mask;
	काष्ठा srcu_data *sdp;
	काष्ठा srcu_node *snp;

	/* Prevent more than one additional grace period. */
	mutex_lock(&ssp->srcu_cb_mutex);

	/* End the current grace period. */
	spin_lock_irq_rcu_node(ssp);
	idx = rcu_seq_state(ssp->srcu_gp_seq);
	WARN_ON_ONCE(idx != SRCU_STATE_SCAN2);
	cbdelay = srcu_get_delay(ssp);
	WRITE_ONCE(ssp->srcu_last_gp_end, kसमय_get_mono_fast_ns());
	rcu_seq_end(&ssp->srcu_gp_seq);
	gpseq = rcu_seq_current(&ssp->srcu_gp_seq);
	अगर (ULONG_CMP_LT(ssp->srcu_gp_seq_needed_exp, gpseq))
		WRITE_ONCE(ssp->srcu_gp_seq_needed_exp, gpseq);
	spin_unlock_irq_rcu_node(ssp);
	mutex_unlock(&ssp->srcu_gp_mutex);
	/* A new grace period can start at this poपूर्णांक.  But only one. */

	/* Initiate callback invocation as needed. */
	idx = rcu_seq_ctr(gpseq) % ARRAY_SIZE(snp->srcu_have_cbs);
	srcu_क्रम_each_node_bपढ़ोth_first(ssp, snp) अणु
		spin_lock_irq_rcu_node(snp);
		cbs = false;
		last_lvl = snp >= ssp->level[rcu_num_lvls - 1];
		अगर (last_lvl)
			cbs = snp->srcu_have_cbs[idx] == gpseq;
		snp->srcu_have_cbs[idx] = gpseq;
		rcu_seq_set_state(&snp->srcu_have_cbs[idx], 1);
		अगर (ULONG_CMP_LT(snp->srcu_gp_seq_needed_exp, gpseq))
			WRITE_ONCE(snp->srcu_gp_seq_needed_exp, gpseq);
		mask = snp->srcu_data_have_cbs[idx];
		snp->srcu_data_have_cbs[idx] = 0;
		spin_unlock_irq_rcu_node(snp);
		अगर (cbs)
			srcu_schedule_cbs_snp(ssp, snp, mask, cbdelay);

		/* Occasionally prevent srcu_data counter wrap. */
		अगर (!(gpseq & counter_wrap_check) && last_lvl)
			क्रम (cpu = snp->grplo; cpu <= snp->grphi; cpu++) अणु
				sdp = per_cpu_ptr(ssp->sda, cpu);
				spin_lock_irqsave_rcu_node(sdp, flags);
				अगर (ULONG_CMP_GE(gpseq,
						 sdp->srcu_gp_seq_needed + 100))
					sdp->srcu_gp_seq_needed = gpseq;
				अगर (ULONG_CMP_GE(gpseq,
						 sdp->srcu_gp_seq_needed_exp + 100))
					sdp->srcu_gp_seq_needed_exp = gpseq;
				spin_unlock_irqrestore_rcu_node(sdp, flags);
			पूर्ण
	पूर्ण

	/* Callback initiation करोne, allow grace periods after next. */
	mutex_unlock(&ssp->srcu_cb_mutex);

	/* Start a new grace period अगर needed. */
	spin_lock_irq_rcu_node(ssp);
	gpseq = rcu_seq_current(&ssp->srcu_gp_seq);
	अगर (!rcu_seq_state(gpseq) &&
	    ULONG_CMP_LT(gpseq, ssp->srcu_gp_seq_needed)) अणु
		srcu_gp_start(ssp);
		spin_unlock_irq_rcu_node(ssp);
		srcu_reschedule(ssp, 0);
	पूर्ण अन्यथा अणु
		spin_unlock_irq_rcu_node(ssp);
	पूर्ण
पूर्ण

/*
 * Funnel-locking scheme to scalably mediate many concurrent expedited
 * grace-period requests.  This function is invoked क्रम the first known
 * expedited request क्रम a grace period that has alपढ़ोy been requested,
 * but without expediting.  To start a completely new grace period,
 * whether expedited or not, use srcu_funnel_gp_start() instead.
 */
अटल व्योम srcu_funnel_exp_start(काष्ठा srcu_काष्ठा *ssp, काष्ठा srcu_node *snp,
				  अचिन्हित दीर्घ s)
अणु
	अचिन्हित दीर्घ flags;

	क्रम (; snp != शून्य; snp = snp->srcu_parent) अणु
		अगर (rcu_seq_करोne(&ssp->srcu_gp_seq, s) ||
		    ULONG_CMP_GE(READ_ONCE(snp->srcu_gp_seq_needed_exp), s))
			वापस;
		spin_lock_irqsave_rcu_node(snp, flags);
		अगर (ULONG_CMP_GE(snp->srcu_gp_seq_needed_exp, s)) अणु
			spin_unlock_irqrestore_rcu_node(snp, flags);
			वापस;
		पूर्ण
		WRITE_ONCE(snp->srcu_gp_seq_needed_exp, s);
		spin_unlock_irqrestore_rcu_node(snp, flags);
	पूर्ण
	spin_lock_irqsave_rcu_node(ssp, flags);
	अगर (ULONG_CMP_LT(ssp->srcu_gp_seq_needed_exp, s))
		WRITE_ONCE(ssp->srcu_gp_seq_needed_exp, s);
	spin_unlock_irqrestore_rcu_node(ssp, flags);
पूर्ण

/*
 * Funnel-locking scheme to scalably mediate many concurrent grace-period
 * requests.  The winner has to करो the work of actually starting grace
 * period s.  Losers must either ensure that their desired grace-period
 * number is recorded on at least their leaf srcu_node काष्ठाure, or they
 * must take steps to invoke their own callbacks.
 *
 * Note that this function also करोes the work of srcu_funnel_exp_start(),
 * in some हालs by directly invoking it.
 */
अटल व्योम srcu_funnel_gp_start(काष्ठा srcu_काष्ठा *ssp, काष्ठा srcu_data *sdp,
				 अचिन्हित दीर्घ s, bool करो_norm)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक idx = rcu_seq_ctr(s) % ARRAY_SIZE(sdp->mynode->srcu_have_cbs);
	काष्ठा srcu_node *snp = sdp->mynode;
	अचिन्हित दीर्घ snp_seq;

	/* Each pass through the loop करोes one level of the srcu_node tree. */
	क्रम (; snp != शून्य; snp = snp->srcu_parent) अणु
		अगर (rcu_seq_करोne(&ssp->srcu_gp_seq, s) && snp != sdp->mynode)
			वापस; /* GP alपढ़ोy करोne and CBs recorded. */
		spin_lock_irqsave_rcu_node(snp, flags);
		अगर (ULONG_CMP_GE(snp->srcu_have_cbs[idx], s)) अणु
			snp_seq = snp->srcu_have_cbs[idx];
			अगर (snp == sdp->mynode && snp_seq == s)
				snp->srcu_data_have_cbs[idx] |= sdp->grpmask;
			spin_unlock_irqrestore_rcu_node(snp, flags);
			अगर (snp == sdp->mynode && snp_seq != s) अणु
				srcu_schedule_cbs_sdp(sdp, करो_norm
							   ? SRCU_INTERVAL
							   : 0);
				वापस;
			पूर्ण
			अगर (!करो_norm)
				srcu_funnel_exp_start(ssp, snp, s);
			वापस;
		पूर्ण
		snp->srcu_have_cbs[idx] = s;
		अगर (snp == sdp->mynode)
			snp->srcu_data_have_cbs[idx] |= sdp->grpmask;
		अगर (!करो_norm && ULONG_CMP_LT(snp->srcu_gp_seq_needed_exp, s))
			WRITE_ONCE(snp->srcu_gp_seq_needed_exp, s);
		spin_unlock_irqrestore_rcu_node(snp, flags);
	पूर्ण

	/* Top of tree, must ensure the grace period will be started. */
	spin_lock_irqsave_rcu_node(ssp, flags);
	अगर (ULONG_CMP_LT(ssp->srcu_gp_seq_needed, s)) अणु
		/*
		 * Record need क्रम grace period s.  Pair with load
		 * acquire setting up क्रम initialization.
		 */
		smp_store_release(&ssp->srcu_gp_seq_needed, s); /*^^^*/
	पूर्ण
	अगर (!करो_norm && ULONG_CMP_LT(ssp->srcu_gp_seq_needed_exp, s))
		WRITE_ONCE(ssp->srcu_gp_seq_needed_exp, s);

	/* If grace period not alपढ़ोy करोne and none in progress, start it. */
	अगर (!rcu_seq_करोne(&ssp->srcu_gp_seq, s) &&
	    rcu_seq_state(ssp->srcu_gp_seq) == SRCU_STATE_IDLE) अणु
		WARN_ON_ONCE(ULONG_CMP_GE(ssp->srcu_gp_seq, ssp->srcu_gp_seq_needed));
		srcu_gp_start(ssp);
		अगर (likely(srcu_init_करोne))
			queue_delayed_work(rcu_gp_wq, &ssp->work,
					   srcu_get_delay(ssp));
		अन्यथा अगर (list_empty(&ssp->work.work.entry))
			list_add(&ssp->work.work.entry, &srcu_boot_list);
	पूर्ण
	spin_unlock_irqrestore_rcu_node(ssp, flags);
पूर्ण

/*
 * Wait until all पढ़ोers counted by array index idx complete, but
 * loop an additional समय अगर there is an expedited grace period pending.
 * The caller must ensure that ->srcu_idx is not changed जबतक checking.
 */
अटल bool try_check_zero(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx, पूर्णांक trycount)
अणु
	क्रम (;;) अणु
		अगर (srcu_पढ़ोers_active_idx_check(ssp, idx))
			वापस true;
		अगर (--trycount + !srcu_get_delay(ssp) <= 0)
			वापस false;
		udelay(SRCU_RETRY_CHECK_DELAY);
	पूर्ण
पूर्ण

/*
 * Increment the ->srcu_idx counter so that future SRCU पढ़ोers will
 * use the other rank of the ->srcu_(un)lock_count[] arrays.  This allows
 * us to रुको क्रम pre-existing पढ़ोers in a starvation-मुक्त manner.
 */
अटल व्योम srcu_flip(काष्ठा srcu_काष्ठा *ssp)
अणु
	/*
	 * Ensure that अगर this updater saw a given पढ़ोer's increment
	 * from __srcu_पढ़ो_lock(), that पढ़ोer was using an old value
	 * of ->srcu_idx.  Also ensure that अगर a given पढ़ोer sees the
	 * new value of ->srcu_idx, this updater's earlier scans cannot
	 * have seen that पढ़ोer's increments (which is OK, because this
	 * grace period need not रुको on that पढ़ोer).
	 */
	smp_mb(); /* E */  /* Pairs with B and C. */

	WRITE_ONCE(ssp->srcu_idx, ssp->srcu_idx + 1);

	/*
	 * Ensure that अगर the updater misses an __srcu_पढ़ो_unlock()
	 * increment, that task's next __srcu_पढ़ो_lock() will see the
	 * above counter update.  Note that both this memory barrier
	 * and the one in srcu_पढ़ोers_active_idx_check() provide the
	 * guarantee क्रम __srcu_पढ़ो_lock().
	 */
	smp_mb(); /* D */  /* Pairs with C. */
पूर्ण

/*
 * If SRCU is likely idle, वापस true, otherwise वापस false.
 *
 * Note that it is OK क्रम several current from-idle requests क्रम a new
 * grace period from idle to specअगरy expediting because they will all end
 * up requesting the same grace period anyhow.  So no loss.
 *
 * Note also that अगर any CPU (including the current one) is still invoking
 * callbacks, this function will nevertheless say "idle".  This is not
 * ideal, but the overhead of checking all CPUs' callback lists is even
 * less ideal, especially on large प्रणालीs.  Furthermore, the wakeup
 * can happen beक्रमe the callback is fully हटाओd, so we have no choice
 * but to accept this type of error.
 *
 * This function is also subject to counter-wrap errors, but let's face
 * it, अगर this function was preempted क्रम enough समय क्रम the counters
 * to wrap, it really करोesn't matter whether or not we expedite the grace
 * period.  The extra overhead of a needlessly expedited grace period is
 * negligible when amortized over that समय period, and the extra latency
 * of a needlessly non-expedited grace period is similarly negligible.
 */
अटल bool srcu_might_be_idle(काष्ठा srcu_काष्ठा *ssp)
अणु
	अचिन्हित दीर्घ curseq;
	अचिन्हित दीर्घ flags;
	काष्ठा srcu_data *sdp;
	अचिन्हित दीर्घ t;
	अचिन्हित दीर्घ tlast;

	check_init_srcu_काष्ठा(ssp);
	/* If the local srcu_data काष्ठाure has callbacks, not idle.  */
	sdp = raw_cpu_ptr(ssp->sda);
	spin_lock_irqsave_rcu_node(sdp, flags);
	अगर (rcu_segcblist_pend_cbs(&sdp->srcu_cblist)) अणु
		spin_unlock_irqrestore_rcu_node(sdp, flags);
		वापस false; /* Callbacks alपढ़ोy present, so not idle. */
	पूर्ण
	spin_unlock_irqrestore_rcu_node(sdp, flags);

	/*
	 * No local callbacks, so probabalistically probe global state.
	 * Exact inक्रमmation would require acquiring locks, which would
	 * समाप्त scalability, hence the probabalistic nature of the probe.
	 */

	/* First, see अगर enough समय has passed since the last GP. */
	t = kसमय_get_mono_fast_ns();
	tlast = READ_ONCE(ssp->srcu_last_gp_end);
	अगर (exp_holकरोff == 0 ||
	    समय_in_range_खोलो(t, tlast, tlast + exp_holकरोff))
		वापस false; /* Too soon after last GP. */

	/* Next, check क्रम probable idleness. */
	curseq = rcu_seq_current(&ssp->srcu_gp_seq);
	smp_mb(); /* Order ->srcu_gp_seq with ->srcu_gp_seq_needed. */
	अगर (ULONG_CMP_LT(curseq, READ_ONCE(ssp->srcu_gp_seq_needed)))
		वापस false; /* Grace period in progress, so not idle. */
	smp_mb(); /* Order ->srcu_gp_seq with prior access. */
	अगर (curseq != rcu_seq_current(&ssp->srcu_gp_seq))
		वापस false; /* GP # changed, so not idle. */
	वापस true; /* With reasonable probability, idle! */
पूर्ण

/*
 * SRCU callback function to leak a callback.
 */
अटल व्योम srcu_leak_callback(काष्ठा rcu_head *rhp)
अणु
पूर्ण

/*
 * Start an SRCU grace period, and also queue the callback अगर non-शून्य.
 */
अटल अचिन्हित दीर्घ srcu_gp_start_अगर_needed(काष्ठा srcu_काष्ठा *ssp,
					     काष्ठा rcu_head *rhp, bool करो_norm)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;
	bool needexp = false;
	bool needgp = false;
	अचिन्हित दीर्घ s;
	काष्ठा srcu_data *sdp;

	check_init_srcu_काष्ठा(ssp);
	idx = srcu_पढ़ो_lock(ssp);
	sdp = raw_cpu_ptr(ssp->sda);
	spin_lock_irqsave_rcu_node(sdp, flags);
	अगर (rhp)
		rcu_segcblist_enqueue(&sdp->srcu_cblist, rhp);
	rcu_segcblist_advance(&sdp->srcu_cblist,
			      rcu_seq_current(&ssp->srcu_gp_seq));
	s = rcu_seq_snap(&ssp->srcu_gp_seq);
	(व्योम)rcu_segcblist_accelerate(&sdp->srcu_cblist, s);
	अगर (ULONG_CMP_LT(sdp->srcu_gp_seq_needed, s)) अणु
		sdp->srcu_gp_seq_needed = s;
		needgp = true;
	पूर्ण
	अगर (!करो_norm && ULONG_CMP_LT(sdp->srcu_gp_seq_needed_exp, s)) अणु
		sdp->srcu_gp_seq_needed_exp = s;
		needexp = true;
	पूर्ण
	spin_unlock_irqrestore_rcu_node(sdp, flags);
	अगर (needgp)
		srcu_funnel_gp_start(ssp, sdp, s, करो_norm);
	अन्यथा अगर (needexp)
		srcu_funnel_exp_start(ssp, sdp->mynode, s);
	srcu_पढ़ो_unlock(ssp, idx);
	वापस s;
पूर्ण

/*
 * Enqueue an SRCU callback on the srcu_data काष्ठाure associated with
 * the current CPU and the specअगरied srcu_काष्ठा काष्ठाure, initiating
 * grace-period processing अगर it is not alपढ़ोy running.
 *
 * Note that all CPUs must agree that the grace period extended beyond
 * all pre-existing SRCU पढ़ो-side critical section.  On प्रणालीs with
 * more than one CPU, this means that when "func()" is invoked, each CPU
 * is guaranteed to have executed a full memory barrier since the end of
 * its last corresponding SRCU पढ़ो-side critical section whose beginning
 * preceded the call to call_srcu().  It also means that each CPU executing
 * an SRCU पढ़ो-side critical section that जारीs beyond the start of
 * "func()" must have executed a memory barrier after the call_srcu()
 * but beक्रमe the beginning of that SRCU पढ़ो-side critical section.
 * Note that these guarantees include CPUs that are offline, idle, or
 * executing in user mode, as well as CPUs that are executing in the kernel.
 *
 * Furthermore, अगर CPU A invoked call_srcu() and CPU B invoked the
 * resulting SRCU callback function "func()", then both CPU A and CPU
 * B are guaranteed to execute a full memory barrier during the समय
 * पूर्णांकerval between the call to call_srcu() and the invocation of "func()".
 * This guarantee applies even अगर CPU A and CPU B are the same CPU (but
 * again only अगर the प्रणाली has more than one CPU).
 *
 * Of course, these guarantees apply only क्रम invocations of call_srcu(),
 * srcu_पढ़ो_lock(), and srcu_पढ़ो_unlock() that are all passed the same
 * srcu_काष्ठा काष्ठाure.
 */
अटल व्योम __call_srcu(काष्ठा srcu_काष्ठा *ssp, काष्ठा rcu_head *rhp,
			rcu_callback_t func, bool करो_norm)
अणु
	अगर (debug_rcu_head_queue(rhp)) अणु
		/* Probable द्विगुन call_srcu(), so leak the callback. */
		WRITE_ONCE(rhp->func, srcu_leak_callback);
		WARN_ONCE(1, "call_srcu(): Leaked duplicate callback\n");
		वापस;
	पूर्ण
	rhp->func = func;
	(व्योम)srcu_gp_start_अगर_needed(ssp, rhp, करो_norm);
पूर्ण

/**
 * call_srcu() - Queue a callback क्रम invocation after an SRCU grace period
 * @ssp: srcu_काष्ठा in queue the callback
 * @rhp: काष्ठाure to be used क्रम queueing the SRCU callback.
 * @func: function to be invoked after the SRCU grace period
 *
 * The callback function will be invoked some समय after a full SRCU
 * grace period elapses, in other words after all pre-existing SRCU
 * पढ़ो-side critical sections have completed.  However, the callback
 * function might well execute concurrently with other SRCU पढ़ो-side
 * critical sections that started after call_srcu() was invoked.  SRCU
 * पढ़ो-side critical sections are delimited by srcu_पढ़ो_lock() and
 * srcu_पढ़ो_unlock(), and may be nested.
 *
 * The callback will be invoked from process context, but must nevertheless
 * be fast and must not block.
 */
व्योम call_srcu(काष्ठा srcu_काष्ठा *ssp, काष्ठा rcu_head *rhp,
	       rcu_callback_t func)
अणु
	__call_srcu(ssp, rhp, func, true);
पूर्ण
EXPORT_SYMBOL_GPL(call_srcu);

/*
 * Helper function क्रम synchronize_srcu() and synchronize_srcu_expedited().
 */
अटल व्योम __synchronize_srcu(काष्ठा srcu_काष्ठा *ssp, bool करो_norm)
अणु
	काष्ठा rcu_synchronize rcu;

	RCU_LOCKDEP_WARN(lockdep_is_held(ssp) ||
			 lock_is_held(&rcu_bh_lock_map) ||
			 lock_is_held(&rcu_lock_map) ||
			 lock_is_held(&rcu_sched_lock_map),
			 "Illegal synchronize_srcu() in same-type SRCU (or in RCU) read-side critical section");

	अगर (rcu_scheduler_active == RCU_SCHEDULER_INACTIVE)
		वापस;
	might_sleep();
	check_init_srcu_काष्ठा(ssp);
	init_completion(&rcu.completion);
	init_rcu_head_on_stack(&rcu.head);
	__call_srcu(ssp, &rcu.head, wakeme_after_rcu, करो_norm);
	रुको_क्रम_completion(&rcu.completion);
	destroy_rcu_head_on_stack(&rcu.head);

	/*
	 * Make sure that later code is ordered after the SRCU grace
	 * period.  This pairs with the spin_lock_irq_rcu_node()
	 * in srcu_invoke_callbacks().  Unlike Tree RCU, this is needed
	 * because the current CPU might have been totally uninvolved with
	 * (and thus unordered against) that grace period.
	 */
	smp_mb();
पूर्ण

/**
 * synchronize_srcu_expedited - Brute-क्रमce SRCU grace period
 * @ssp: srcu_काष्ठा with which to synchronize.
 *
 * Wait क्रम an SRCU grace period to elapse, but be more aggressive about
 * spinning rather than blocking when रुकोing.
 *
 * Note that synchronize_srcu_expedited() has the same deadlock and
 * memory-ordering properties as करोes synchronize_srcu().
 */
व्योम synchronize_srcu_expedited(काष्ठा srcu_काष्ठा *ssp)
अणु
	__synchronize_srcu(ssp, rcu_gp_is_normal());
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_srcu_expedited);

/**
 * synchronize_srcu - रुको क्रम prior SRCU पढ़ो-side critical-section completion
 * @ssp: srcu_काष्ठा with which to synchronize.
 *
 * Wait क्रम the count to drain to zero of both indexes. To aव्योम the
 * possible starvation of synchronize_srcu(), it रुकोs क्रम the count of
 * the index=((->srcu_idx & 1) ^ 1) to drain to zero at first,
 * and then flip the srcu_idx and रुको क्रम the count of the other index.
 *
 * Can block; must be called from process context.
 *
 * Note that it is illegal to call synchronize_srcu() from the corresponding
 * SRCU पढ़ो-side critical section; करोing so will result in deadlock.
 * However, it is perfectly legal to call synchronize_srcu() on one
 * srcu_काष्ठा from some other srcu_काष्ठा's पढ़ो-side critical section,
 * as दीर्घ as the resulting graph of srcu_काष्ठाs is acyclic.
 *
 * There are memory-ordering स्थिरraपूर्णांकs implied by synchronize_srcu().
 * On प्रणालीs with more than one CPU, when synchronize_srcu() वापसs,
 * each CPU is guaranteed to have executed a full memory barrier since
 * the end of its last corresponding SRCU पढ़ो-side critical section
 * whose beginning preceded the call to synchronize_srcu().  In addition,
 * each CPU having an SRCU पढ़ो-side critical section that extends beyond
 * the वापस from synchronize_srcu() is guaranteed to have executed a
 * full memory barrier after the beginning of synchronize_srcu() and beक्रमe
 * the beginning of that SRCU पढ़ो-side critical section.  Note that these
 * guarantees include CPUs that are offline, idle, or executing in user mode,
 * as well as CPUs that are executing in the kernel.
 *
 * Furthermore, अगर CPU A invoked synchronize_srcu(), which वापसed
 * to its caller on CPU B, then both CPU A and CPU B are guaranteed
 * to have executed a full memory barrier during the execution of
 * synchronize_srcu().  This guarantee applies even अगर CPU A and CPU B
 * are the same CPU, but again only अगर the प्रणाली has more than one CPU.
 *
 * Of course, these memory-ordering guarantees apply only when
 * synchronize_srcu(), srcu_पढ़ो_lock(), and srcu_पढ़ो_unlock() are
 * passed the same srcu_काष्ठा काष्ठाure.
 *
 * If SRCU is likely idle, expedite the first request.  This semantic
 * was provided by Classic SRCU, and is relied upon by its users, so TREE
 * SRCU must also provide it.  Note that detecting idleness is heuristic
 * and subject to both false positives and negatives.
 */
व्योम synchronize_srcu(काष्ठा srcu_काष्ठा *ssp)
अणु
	अगर (srcu_might_be_idle(ssp) || rcu_gp_is_expedited())
		synchronize_srcu_expedited(ssp);
	अन्यथा
		__synchronize_srcu(ssp, true);
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_srcu);

/**
 * get_state_synchronize_srcu - Provide an end-of-grace-period cookie
 * @ssp: srcu_काष्ठा to provide cookie क्रम.
 *
 * This function वापसs a cookie that can be passed to
 * poll_state_synchronize_srcu(), which will वापस true अगर a full grace
 * period has elapsed in the meanसमय.  It is the caller's responsibility
 * to make sure that grace period happens, क्रम example, by invoking
 * call_srcu() after वापस from get_state_synchronize_srcu().
 */
अचिन्हित दीर्घ get_state_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp)
अणु
	// Any prior manipulation of SRCU-रक्षित data must happen
	// beक्रमe the load from ->srcu_gp_seq.
	smp_mb();
	वापस rcu_seq_snap(&ssp->srcu_gp_seq);
पूर्ण
EXPORT_SYMBOL_GPL(get_state_synchronize_srcu);

/**
 * start_poll_synchronize_srcu - Provide cookie and start grace period
 * @ssp: srcu_काष्ठा to provide cookie क्रम.
 *
 * This function वापसs a cookie that can be passed to
 * poll_state_synchronize_srcu(), which will वापस true अगर a full grace
 * period has elapsed in the meanसमय.  Unlike get_state_synchronize_srcu(),
 * this function also ensures that any needed SRCU grace period will be
 * started.  This convenience करोes come at a cost in terms of CPU overhead.
 */
अचिन्हित दीर्घ start_poll_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp)
अणु
	वापस srcu_gp_start_अगर_needed(ssp, शून्य, true);
पूर्ण
EXPORT_SYMBOL_GPL(start_poll_synchronize_srcu);

/**
 * poll_state_synchronize_srcu - Has cookie's grace period ended?
 * @ssp: srcu_काष्ठा to provide cookie क्रम.
 * @cookie: Return value from get_state_synchronize_srcu() or start_poll_synchronize_srcu().
 *
 * This function takes the cookie that was वापसed from either
 * get_state_synchronize_srcu() or start_poll_synchronize_srcu(), and
 * वापसs @true अगर an SRCU grace period elapsed since the समय that the
 * cookie was created.
 *
 * Because cookies are finite in size, wrapping/overflow is possible.
 * This is more pronounced on 32-bit प्रणालीs where cookies are 32 bits,
 * where in theory wrapping could happen in about 14 hours assuming
 * 25-microsecond expedited SRCU grace periods.  However, a more likely
 * overflow lower bound is on the order of 24 days in the हाल of
 * one-millisecond SRCU grace periods.  Of course, wrapping in a 64-bit
 * प्रणाली requires geologic बारpans, as in more than seven million years
 * even क्रम expedited SRCU grace periods.
 *
 * Wrapping/overflow is much more of an issue क्रम CONFIG_SMP=n प्रणालीs
 * that also have CONFIG_PREEMPTION=n, which selects Tiny SRCU.  This uses
 * a 16-bit cookie, which rcutorture routinely wraps in a matter of a
 * few minutes.  If this proves to be a problem, this counter will be
 * expanded to the same size as क्रम Tree SRCU.
 */
bool poll_state_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp, अचिन्हित दीर्घ cookie)
अणु
	अगर (!rcu_seq_करोne(&ssp->srcu_gp_seq, cookie))
		वापस false;
	// Ensure that the end of the SRCU grace period happens beक्रमe
	// any subsequent code that the caller might execute.
	smp_mb(); // ^^^
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(poll_state_synchronize_srcu);

/*
 * Callback function क्रम srcu_barrier() use.
 */
अटल व्योम srcu_barrier_cb(काष्ठा rcu_head *rhp)
अणु
	काष्ठा srcu_data *sdp;
	काष्ठा srcu_काष्ठा *ssp;

	sdp = container_of(rhp, काष्ठा srcu_data, srcu_barrier_head);
	ssp = sdp->ssp;
	अगर (atomic_dec_and_test(&ssp->srcu_barrier_cpu_cnt))
		complete(&ssp->srcu_barrier_completion);
पूर्ण

/**
 * srcu_barrier - Wait until all in-flight call_srcu() callbacks complete.
 * @ssp: srcu_काष्ठा on which to रुको क्रम in-flight callbacks.
 */
व्योम srcu_barrier(काष्ठा srcu_काष्ठा *ssp)
अणु
	पूर्णांक cpu;
	काष्ठा srcu_data *sdp;
	अचिन्हित दीर्घ s = rcu_seq_snap(&ssp->srcu_barrier_seq);

	check_init_srcu_काष्ठा(ssp);
	mutex_lock(&ssp->srcu_barrier_mutex);
	अगर (rcu_seq_करोne(&ssp->srcu_barrier_seq, s)) अणु
		smp_mb(); /* Force ordering following वापस. */
		mutex_unlock(&ssp->srcu_barrier_mutex);
		वापस; /* Someone अन्यथा did our work क्रम us. */
	पूर्ण
	rcu_seq_start(&ssp->srcu_barrier_seq);
	init_completion(&ssp->srcu_barrier_completion);

	/* Initial count prevents reaching zero until all CBs are posted. */
	atomic_set(&ssp->srcu_barrier_cpu_cnt, 1);

	/*
	 * Each pass through this loop enqueues a callback, but only
	 * on CPUs alपढ़ोy having callbacks enqueued.  Note that अगर
	 * a CPU alपढ़ोy has callbacks enqueue, it must have alपढ़ोy
	 * रेजिस्टरed the need क्रम a future grace period, so all we
	 * need करो is enqueue a callback that will use the same
	 * grace period as the last callback alपढ़ोy in the queue.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		sdp = per_cpu_ptr(ssp->sda, cpu);
		spin_lock_irq_rcu_node(sdp);
		atomic_inc(&ssp->srcu_barrier_cpu_cnt);
		sdp->srcu_barrier_head.func = srcu_barrier_cb;
		debug_rcu_head_queue(&sdp->srcu_barrier_head);
		अगर (!rcu_segcblist_entrain(&sdp->srcu_cblist,
					   &sdp->srcu_barrier_head)) अणु
			debug_rcu_head_unqueue(&sdp->srcu_barrier_head);
			atomic_dec(&ssp->srcu_barrier_cpu_cnt);
		पूर्ण
		spin_unlock_irq_rcu_node(sdp);
	पूर्ण

	/* Remove the initial count, at which poपूर्णांक reaching zero can happen. */
	अगर (atomic_dec_and_test(&ssp->srcu_barrier_cpu_cnt))
		complete(&ssp->srcu_barrier_completion);
	रुको_क्रम_completion(&ssp->srcu_barrier_completion);

	rcu_seq_end(&ssp->srcu_barrier_seq);
	mutex_unlock(&ssp->srcu_barrier_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(srcu_barrier);

/**
 * srcu_batches_completed - वापस batches completed.
 * @ssp: srcu_काष्ठा on which to report batch completion.
 *
 * Report the number of batches, correlated with, but not necessarily
 * precisely the same as, the number of grace periods that have elapsed.
 */
अचिन्हित दीर्घ srcu_batches_completed(काष्ठा srcu_काष्ठा *ssp)
अणु
	वापस READ_ONCE(ssp->srcu_idx);
पूर्ण
EXPORT_SYMBOL_GPL(srcu_batches_completed);

/*
 * Core SRCU state machine.  Push state bits of ->srcu_gp_seq
 * to SRCU_STATE_SCAN2, and invoke srcu_gp_end() when scan has
 * completed in that state.
 */
अटल व्योम srcu_advance_state(काष्ठा srcu_काष्ठा *ssp)
अणु
	पूर्णांक idx;

	mutex_lock(&ssp->srcu_gp_mutex);

	/*
	 * Because पढ़ोers might be delayed क्रम an extended period after
	 * fetching ->srcu_idx क्रम their index, at any poपूर्णांक in समय there
	 * might well be पढ़ोers using both idx=0 and idx=1.  We thereक्रमe
	 * need to रुको क्रम पढ़ोers to clear from both index values beक्रमe
	 * invoking a callback.
	 *
	 * The load-acquire ensures that we see the accesses perक्रमmed
	 * by the prior grace period.
	 */
	idx = rcu_seq_state(smp_load_acquire(&ssp->srcu_gp_seq)); /* ^^^ */
	अगर (idx == SRCU_STATE_IDLE) अणु
		spin_lock_irq_rcu_node(ssp);
		अगर (ULONG_CMP_GE(ssp->srcu_gp_seq, ssp->srcu_gp_seq_needed)) अणु
			WARN_ON_ONCE(rcu_seq_state(ssp->srcu_gp_seq));
			spin_unlock_irq_rcu_node(ssp);
			mutex_unlock(&ssp->srcu_gp_mutex);
			वापस;
		पूर्ण
		idx = rcu_seq_state(READ_ONCE(ssp->srcu_gp_seq));
		अगर (idx == SRCU_STATE_IDLE)
			srcu_gp_start(ssp);
		spin_unlock_irq_rcu_node(ssp);
		अगर (idx != SRCU_STATE_IDLE) अणु
			mutex_unlock(&ssp->srcu_gp_mutex);
			वापस; /* Someone अन्यथा started the grace period. */
		पूर्ण
	पूर्ण

	अगर (rcu_seq_state(READ_ONCE(ssp->srcu_gp_seq)) == SRCU_STATE_SCAN1) अणु
		idx = 1 ^ (ssp->srcu_idx & 1);
		अगर (!try_check_zero(ssp, idx, 1)) अणु
			mutex_unlock(&ssp->srcu_gp_mutex);
			वापस; /* पढ़ोers present, retry later. */
		पूर्ण
		srcu_flip(ssp);
		spin_lock_irq_rcu_node(ssp);
		rcu_seq_set_state(&ssp->srcu_gp_seq, SRCU_STATE_SCAN2);
		spin_unlock_irq_rcu_node(ssp);
	पूर्ण

	अगर (rcu_seq_state(READ_ONCE(ssp->srcu_gp_seq)) == SRCU_STATE_SCAN2) अणु

		/*
		 * SRCU पढ़ो-side critical sections are normally लघु,
		 * so check at least twice in quick succession after a flip.
		 */
		idx = 1 ^ (ssp->srcu_idx & 1);
		अगर (!try_check_zero(ssp, idx, 2)) अणु
			mutex_unlock(&ssp->srcu_gp_mutex);
			वापस; /* पढ़ोers present, retry later. */
		पूर्ण
		srcu_gp_end(ssp);  /* Releases ->srcu_gp_mutex. */
	पूर्ण
पूर्ण

/*
 * Invoke a limited number of SRCU callbacks that have passed through
 * their grace period.  If there are more to करो, SRCU will reschedule
 * the workqueue.  Note that needed memory barriers have been executed
 * in this task's context by srcu_पढ़ोers_active_idx_check().
 */
अटल व्योम srcu_invoke_callbacks(काष्ठा work_काष्ठा *work)
अणु
	दीर्घ len;
	bool more;
	काष्ठा rcu_cblist पढ़ोy_cbs;
	काष्ठा rcu_head *rhp;
	काष्ठा srcu_data *sdp;
	काष्ठा srcu_काष्ठा *ssp;

	sdp = container_of(work, काष्ठा srcu_data, work);

	ssp = sdp->ssp;
	rcu_cblist_init(&पढ़ोy_cbs);
	spin_lock_irq_rcu_node(sdp);
	rcu_segcblist_advance(&sdp->srcu_cblist,
			      rcu_seq_current(&ssp->srcu_gp_seq));
	अगर (sdp->srcu_cblist_invoking ||
	    !rcu_segcblist_पढ़ोy_cbs(&sdp->srcu_cblist)) अणु
		spin_unlock_irq_rcu_node(sdp);
		वापस;  /* Someone अन्यथा on the job or nothing to करो. */
	पूर्ण

	/* We are on the job!  Extract and invoke पढ़ोy callbacks. */
	sdp->srcu_cblist_invoking = true;
	rcu_segcblist_extract_करोne_cbs(&sdp->srcu_cblist, &पढ़ोy_cbs);
	len = पढ़ोy_cbs.len;
	spin_unlock_irq_rcu_node(sdp);
	rhp = rcu_cblist_dequeue(&पढ़ोy_cbs);
	क्रम (; rhp != शून्य; rhp = rcu_cblist_dequeue(&पढ़ोy_cbs)) अणु
		debug_rcu_head_unqueue(rhp);
		local_bh_disable();
		rhp->func(rhp);
		local_bh_enable();
	पूर्ण
	WARN_ON_ONCE(पढ़ोy_cbs.len);

	/*
	 * Update counts, accelerate new callbacks, and अगर needed,
	 * schedule another round of callback invocation.
	 */
	spin_lock_irq_rcu_node(sdp);
	rcu_segcblist_add_len(&sdp->srcu_cblist, -len);
	(व्योम)rcu_segcblist_accelerate(&sdp->srcu_cblist,
				       rcu_seq_snap(&ssp->srcu_gp_seq));
	sdp->srcu_cblist_invoking = false;
	more = rcu_segcblist_पढ़ोy_cbs(&sdp->srcu_cblist);
	spin_unlock_irq_rcu_node(sdp);
	अगर (more)
		srcu_schedule_cbs_sdp(sdp, 0);
पूर्ण

/*
 * Finished one round of SRCU grace period.  Start another अगर there are
 * more SRCU callbacks queued, otherwise put SRCU पूर्णांकo not-running state.
 */
अटल व्योम srcu_reschedule(काष्ठा srcu_काष्ठा *ssp, अचिन्हित दीर्घ delay)
अणु
	bool pushgp = true;

	spin_lock_irq_rcu_node(ssp);
	अगर (ULONG_CMP_GE(ssp->srcu_gp_seq, ssp->srcu_gp_seq_needed)) अणु
		अगर (!WARN_ON_ONCE(rcu_seq_state(ssp->srcu_gp_seq))) अणु
			/* All requests fulfilled, समय to go idle. */
			pushgp = false;
		पूर्ण
	पूर्ण अन्यथा अगर (!rcu_seq_state(ssp->srcu_gp_seq)) अणु
		/* Outstanding request and no GP.  Start one. */
		srcu_gp_start(ssp);
	पूर्ण
	spin_unlock_irq_rcu_node(ssp);

	अगर (pushgp)
		queue_delayed_work(rcu_gp_wq, &ssp->work, delay);
पूर्ण

/*
 * This is the work-queue function that handles SRCU grace periods.
 */
अटल व्योम process_srcu(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा srcu_काष्ठा *ssp;

	ssp = container_of(work, काष्ठा srcu_काष्ठा, work.work);

	srcu_advance_state(ssp);
	srcu_reschedule(ssp, srcu_get_delay(ssp));
पूर्ण

व्योम srcutorture_get_gp_data(क्रमागत rcutorture_type test_type,
			     काष्ठा srcu_काष्ठा *ssp, पूर्णांक *flags,
			     अचिन्हित दीर्घ *gp_seq)
अणु
	अगर (test_type != SRCU_FLAVOR)
		वापस;
	*flags = 0;
	*gp_seq = rcu_seq_current(&ssp->srcu_gp_seq);
पूर्ण
EXPORT_SYMBOL_GPL(srcutorture_get_gp_data);

व्योम srcu_torture_stats_prपूर्णांक(काष्ठा srcu_काष्ठा *ssp, अक्षर *tt, अक्षर *tf)
अणु
	पूर्णांक cpu;
	पूर्णांक idx;
	अचिन्हित दीर्घ s0 = 0, s1 = 0;

	idx = ssp->srcu_idx & 0x1;
	pr_alert("%s%s Tree SRCU g%ld per-CPU(idx=%d):",
		 tt, tf, rcu_seq_current(&ssp->srcu_gp_seq), idx);
	क्रम_each_possible_cpu(cpu) अणु
		अचिन्हित दीर्घ l0, l1;
		अचिन्हित दीर्घ u0, u1;
		दीर्घ c0, c1;
		काष्ठा srcu_data *sdp;

		sdp = per_cpu_ptr(ssp->sda, cpu);
		u0 = data_race(sdp->srcu_unlock_count[!idx]);
		u1 = data_race(sdp->srcu_unlock_count[idx]);

		/*
		 * Make sure that a lock is always counted अगर the corresponding
		 * unlock is counted.
		 */
		smp_rmb();

		l0 = data_race(sdp->srcu_lock_count[!idx]);
		l1 = data_race(sdp->srcu_lock_count[idx]);

		c0 = l0 - u0;
		c1 = l1 - u1;
		pr_cont(" %d(%ld,%ld %c)",
			cpu, c0, c1,
			"C."[rcu_segcblist_empty(&sdp->srcu_cblist)]);
		s0 += c0;
		s1 += c1;
	पूर्ण
	pr_cont(" T(%ld,%ld)\n", s0, s1);
पूर्ण
EXPORT_SYMBOL_GPL(srcu_torture_stats_prपूर्णांक);

अटल पूर्णांक __init srcu_bootup_announce(व्योम)
अणु
	pr_info("Hierarchical SRCU implementation.\n");
	अगर (exp_holकरोff != DEFAULT_SRCU_EXP_HOLDOFF)
		pr_info("\tNon-default auto-expedite holdoff of %lu ns.\n", exp_holकरोff);
	वापस 0;
पूर्ण
early_initcall(srcu_bootup_announce);

व्योम __init srcu_init(व्योम)
अणु
	काष्ठा srcu_काष्ठा *ssp;

	srcu_init_करोne = true;
	जबतक (!list_empty(&srcu_boot_list)) अणु
		ssp = list_first_entry(&srcu_boot_list, काष्ठा srcu_काष्ठा,
				      work.work.entry);
		check_init_srcu_काष्ठा(ssp);
		list_del_init(&ssp->work.work.entry);
		queue_work(rcu_gp_wq, &ssp->work.work);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MODULES

/* Initialize any global-scope srcu_काष्ठा काष्ठाures used by this module. */
अटल पूर्णांक srcu_module_coming(काष्ठा module *mod)
अणु
	पूर्णांक i;
	काष्ठा srcu_काष्ठा **sspp = mod->srcu_काष्ठा_ptrs;
	पूर्णांक ret;

	क्रम (i = 0; i < mod->num_srcu_काष्ठाs; i++) अणु
		ret = init_srcu_काष्ठा(*(sspp++));
		अगर (WARN_ON_ONCE(ret))
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Clean up any global-scope srcu_काष्ठा काष्ठाures used by this module. */
अटल व्योम srcu_module_going(काष्ठा module *mod)
अणु
	पूर्णांक i;
	काष्ठा srcu_काष्ठा **sspp = mod->srcu_काष्ठा_ptrs;

	क्रम (i = 0; i < mod->num_srcu_काष्ठाs; i++)
		cleanup_srcu_काष्ठा(*(sspp++));
पूर्ण

/* Handle one module, either coming or going. */
अटल पूर्णांक srcu_module_notअगरy(काष्ठा notअगरier_block *self,
			      अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;
	पूर्णांक ret = 0;

	चयन (val) अणु
	हाल MODULE_STATE_COMING:
		ret = srcu_module_coming(mod);
		अवरोध;
	हाल MODULE_STATE_GOING:
		srcu_module_going(mod);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block srcu_module_nb = अणु
	.notअगरier_call = srcu_module_notअगरy,
	.priority = 0,
पूर्ण;

अटल __init पूर्णांक init_srcu_module_notअगरier(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_module_notअगरier(&srcu_module_nb);
	अगर (ret)
		pr_warn("Failed to register srcu module notifier\n");
	वापस ret;
पूर्ण
late_initcall(init_srcu_module_notअगरier);

#पूर्ण_अगर /* #अगर_घोषित CONFIG_MODULES */
