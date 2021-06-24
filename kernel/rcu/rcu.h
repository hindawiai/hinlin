<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Read-Copy Update definitions shared among RCU implementations.
 *
 * Copyright IBM Corporation, 2011
 *
 * Author: Paul E. McKenney <paulmck@linux.ibm.com>
 */

#अगर_अघोषित __LINUX_RCU_H
#घोषणा __LINUX_RCU_H

#समावेश <trace/events/rcu.h>

/* Offset to allow distinguishing irq vs. task-based idle entry/निकास. */
#घोषणा DYNTICK_IRQ_NONIDLE	((दीर्घ_उच्च / 2) + 1)


/*
 * Grace-period counter management.
 */

#घोषणा RCU_SEQ_CTR_SHIFT	2
#घोषणा RCU_SEQ_STATE_MASK	((1 << RCU_SEQ_CTR_SHIFT) - 1)

/*
 * Return the counter portion of a sequence number previously वापसed
 * by rcu_seq_snap() or rcu_seq_current().
 */
अटल अंतरभूत अचिन्हित दीर्घ rcu_seq_ctr(अचिन्हित दीर्घ s)
अणु
	वापस s >> RCU_SEQ_CTR_SHIFT;
पूर्ण

/*
 * Return the state portion of a sequence number previously वापसed
 * by rcu_seq_snap() or rcu_seq_current().
 */
अटल अंतरभूत पूर्णांक rcu_seq_state(अचिन्हित दीर्घ s)
अणु
	वापस s & RCU_SEQ_STATE_MASK;
पूर्ण

/*
 * Set the state portion of the poपूर्णांकed-to sequence number.
 * The caller is responsible क्रम preventing conflicting updates.
 */
अटल अंतरभूत व्योम rcu_seq_set_state(अचिन्हित दीर्घ *sp, पूर्णांक newstate)
अणु
	WARN_ON_ONCE(newstate & ~RCU_SEQ_STATE_MASK);
	WRITE_ONCE(*sp, (*sp & ~RCU_SEQ_STATE_MASK) + newstate);
पूर्ण

/* Adjust sequence number क्रम start of update-side operation. */
अटल अंतरभूत व्योम rcu_seq_start(अचिन्हित दीर्घ *sp)
अणु
	WRITE_ONCE(*sp, *sp + 1);
	smp_mb(); /* Ensure update-side operation after counter increment. */
	WARN_ON_ONCE(rcu_seq_state(*sp) != 1);
पूर्ण

/* Compute the end-of-grace-period value क्रम the specअगरied sequence number. */
अटल अंतरभूत अचिन्हित दीर्घ rcu_seq_endval(अचिन्हित दीर्घ *sp)
अणु
	वापस (*sp | RCU_SEQ_STATE_MASK) + 1;
पूर्ण

/* Adjust sequence number क्रम end of update-side operation. */
अटल अंतरभूत व्योम rcu_seq_end(अचिन्हित दीर्घ *sp)
अणु
	smp_mb(); /* Ensure update-side operation beक्रमe counter increment. */
	WARN_ON_ONCE(!rcu_seq_state(*sp));
	WRITE_ONCE(*sp, rcu_seq_endval(sp));
पूर्ण

/*
 * rcu_seq_snap - Take a snapshot of the update side's sequence number.
 *
 * This function वापसs the earliest value of the grace-period sequence number
 * that will indicate that a full grace period has elapsed since the current
 * समय.  Once the grace-period sequence number has reached this value, it will
 * be safe to invoke all callbacks that have been रेजिस्टरed prior to the
 * current समय. This value is the current grace-period number plus two to the
 * घातer of the number of low-order bits reserved क्रम state, then rounded up to
 * the next value in which the state bits are all zero.
 */
अटल अंतरभूत अचिन्हित दीर्घ rcu_seq_snap(अचिन्हित दीर्घ *sp)
अणु
	अचिन्हित दीर्घ s;

	s = (READ_ONCE(*sp) + 2 * RCU_SEQ_STATE_MASK + 1) & ~RCU_SEQ_STATE_MASK;
	smp_mb(); /* Above access must not bleed पूर्णांकo critical section. */
	वापस s;
पूर्ण

/* Return the current value the update side's sequence number, no ordering. */
अटल अंतरभूत अचिन्हित दीर्घ rcu_seq_current(अचिन्हित दीर्घ *sp)
अणु
	वापस READ_ONCE(*sp);
पूर्ण

/*
 * Given a snapshot from rcu_seq_snap(), determine whether or not the
 * corresponding update-side operation has started.
 */
अटल अंतरभूत bool rcu_seq_started(अचिन्हित दीर्घ *sp, अचिन्हित दीर्घ s)
अणु
	वापस ULONG_CMP_LT((s - 1) & ~RCU_SEQ_STATE_MASK, READ_ONCE(*sp));
पूर्ण

/*
 * Given a snapshot from rcu_seq_snap(), determine whether or not a
 * full update-side operation has occurred.
 */
अटल अंतरभूत bool rcu_seq_करोne(अचिन्हित दीर्घ *sp, अचिन्हित दीर्घ s)
अणु
	वापस ULONG_CMP_GE(READ_ONCE(*sp), s);
पूर्ण

/*
 * Has a grace period completed since the समय the old gp_seq was collected?
 */
अटल अंतरभूत bool rcu_seq_completed_gp(अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	वापस ULONG_CMP_LT(old, new & ~RCU_SEQ_STATE_MASK);
पूर्ण

/*
 * Has a grace period started since the समय the old gp_seq was collected?
 */
अटल अंतरभूत bool rcu_seq_new_gp(अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	वापस ULONG_CMP_LT((old + RCU_SEQ_STATE_MASK) & ~RCU_SEQ_STATE_MASK,
			    new);
पूर्ण

/*
 * Roughly how many full grace periods have elapsed between the collection
 * of the two specअगरied grace periods?
 */
अटल अंतरभूत अचिन्हित दीर्घ rcu_seq_dअगरf(अचिन्हित दीर्घ new, अचिन्हित दीर्घ old)
अणु
	अचिन्हित दीर्घ rnd_dअगरf;

	अगर (old == new)
		वापस 0;
	/*
	 * Compute the number of grace periods (still shअगरted up), plus
	 * one अगर either of new and old is not an exact grace period.
	 */
	rnd_dअगरf = (new & ~RCU_SEQ_STATE_MASK) -
		   ((old + RCU_SEQ_STATE_MASK) & ~RCU_SEQ_STATE_MASK) +
		   ((new & RCU_SEQ_STATE_MASK) || (old & RCU_SEQ_STATE_MASK));
	अगर (ULONG_CMP_GE(RCU_SEQ_STATE_MASK, rnd_dअगरf))
		वापस 1; /* Definitely no grace period has elapsed. */
	वापस ((rnd_dअगरf - RCU_SEQ_STATE_MASK - 1) >> RCU_SEQ_CTR_SHIFT) + 2;
पूर्ण

/*
 * debug_rcu_head_queue()/debug_rcu_head_unqueue() are used पूर्णांकernally
 * by call_rcu() and rcu callback execution, and are thereक्रमe not part
 * of the RCU API. These are in rcupdate.h because they are used by all
 * RCU implementations.
 */

#अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD
# define STATE_RCU_HEAD_READY	0
# define STATE_RCU_HEAD_QUEUED	1

बाह्य स्थिर काष्ठा debug_obj_descr rcuhead_debug_descr;

अटल अंतरभूत पूर्णांक debug_rcu_head_queue(काष्ठा rcu_head *head)
अणु
	पूर्णांक r1;

	r1 = debug_object_activate(head, &rcuhead_debug_descr);
	debug_object_active_state(head, &rcuhead_debug_descr,
				  STATE_RCU_HEAD_READY,
				  STATE_RCU_HEAD_QUEUED);
	वापस r1;
पूर्ण

अटल अंतरभूत व्योम debug_rcu_head_unqueue(काष्ठा rcu_head *head)
अणु
	debug_object_active_state(head, &rcuhead_debug_descr,
				  STATE_RCU_HEAD_QUEUED,
				  STATE_RCU_HEAD_READY);
	debug_object_deactivate(head, &rcuhead_debug_descr);
पूर्ण
#अन्यथा	/* !CONFIG_DEBUG_OBJECTS_RCU_HEAD */
अटल अंतरभूत पूर्णांक debug_rcu_head_queue(काष्ठा rcu_head *head)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम debug_rcu_head_unqueue(काष्ठा rcu_head *head)
अणु
पूर्ण
#पूर्ण_अगर	/* #अन्यथा !CONFIG_DEBUG_OBJECTS_RCU_HEAD */

बाह्य पूर्णांक rcu_cpu_stall_suppress_at_boot;

अटल अंतरभूत bool rcu_stall_is_suppressed_at_boot(व्योम)
अणु
	वापस rcu_cpu_stall_suppress_at_boot && !rcu_inkernel_boot_has_ended();
पूर्ण

#अगर_घोषित CONFIG_RCU_STALL_COMMON

बाह्य पूर्णांक rcu_cpu_stall_ftrace_dump;
बाह्य पूर्णांक rcu_cpu_stall_suppress;
बाह्य पूर्णांक rcu_cpu_stall_समयout;
पूर्णांक rcu_jअगरfies_till_stall_check(व्योम);

अटल अंतरभूत bool rcu_stall_is_suppressed(व्योम)
अणु
	वापस rcu_stall_is_suppressed_at_boot() || rcu_cpu_stall_suppress;
पूर्ण

#घोषणा rcu_ftrace_dump_stall_suppress() \
करो अणु \
	अगर (!rcu_cpu_stall_suppress) \
		rcu_cpu_stall_suppress = 3; \
पूर्ण जबतक (0)

#घोषणा rcu_ftrace_dump_stall_unsuppress() \
करो अणु \
	अगर (rcu_cpu_stall_suppress == 3) \
		rcu_cpu_stall_suppress = 0; \
पूर्ण जबतक (0)

#अन्यथा /* #पूर्ण_अगर #अगर_घोषित CONFIG_RCU_STALL_COMMON */

अटल अंतरभूत bool rcu_stall_is_suppressed(व्योम)
अणु
	वापस rcu_stall_is_suppressed_at_boot();
पूर्ण
#घोषणा rcu_ftrace_dump_stall_suppress()
#घोषणा rcu_ftrace_dump_stall_unsuppress()
#पूर्ण_अगर /* #अगर_घोषित CONFIG_RCU_STALL_COMMON */

/*
 * Strings used in tracepoपूर्णांकs need to be exported via the
 * tracing प्रणाली such that tools like perf and trace-cmd can
 * translate the string address poपूर्णांकers to actual text.
 */
#घोषणा TPS(x)  tracepoपूर्णांक_string(x)

/*
 * Dump the ftrace buffer, but only one समय per callsite per boot.
 */
#घोषणा rcu_ftrace_dump(oops_dump_mode) \
करो अणु \
	अटल atomic_t ___rfd_beenhere = ATOMIC_INIT(0); \
	\
	अगर (!atomic_पढ़ो(&___rfd_beenhere) && \
	    !atomic_xchg(&___rfd_beenhere, 1)) अणु \
		tracing_off(); \
		rcu_ftrace_dump_stall_suppress(); \
		ftrace_dump(oops_dump_mode); \
		rcu_ftrace_dump_stall_unsuppress(); \
	पूर्ण \
पूर्ण जबतक (0)

व्योम rcu_early_boot_tests(व्योम);
व्योम rcu_test_sync_prims(व्योम);

/*
 * This function really isn't क्रम खुला consumption, but RCU is special in
 * that context चयनes can allow the state machine to make progress.
 */
बाह्य व्योम resched_cpu(पूर्णांक cpu);

#अगर defined(CONFIG_SRCU) || !defined(CONFIG_TINY_RCU)

#समावेश <linux/rcu_node_tree.h>

बाह्य पूर्णांक rcu_num_lvls;
बाह्य पूर्णांक num_rcu_lvl[];
बाह्य पूर्णांक rcu_num_nodes;
अटल bool rcu_fanout_exact;
अटल पूर्णांक rcu_fanout_leaf;

/*
 * Compute the per-level fanout, either using the exact fanout specअगरied
 * or balancing the tree, depending on the rcu_fanout_exact boot parameter.
 */
अटल अंतरभूत व्योम rcu_init_levelspपढ़ो(पूर्णांक *levelspपढ़ो, स्थिर पूर्णांक *levelcnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RCU_NUM_LVLS; i++)
		levelspपढ़ो[i] = पूर्णांक_न्यून;
	अगर (rcu_fanout_exact) अणु
		levelspपढ़ो[rcu_num_lvls - 1] = rcu_fanout_leaf;
		क्रम (i = rcu_num_lvls - 2; i >= 0; i--)
			levelspपढ़ो[i] = RCU_FANOUT;
	पूर्ण अन्यथा अणु
		पूर्णांक ccur;
		पूर्णांक cprv;

		cprv = nr_cpu_ids;
		क्रम (i = rcu_num_lvls - 1; i >= 0; i--) अणु
			ccur = levelcnt[i];
			levelspपढ़ो[i] = (cprv + ccur - 1) / ccur;
			cprv = ccur;
		पूर्ण
	पूर्ण
पूर्ण

/* Returns a poपूर्णांकer to the first leaf rcu_node काष्ठाure. */
#घोषणा rcu_first_leaf_node() (rcu_state.level[rcu_num_lvls - 1])

/* Is this rcu_node a leaf? */
#घोषणा rcu_is_leaf_node(rnp) ((rnp)->level == rcu_num_lvls - 1)

/* Is this rcu_node the last leaf? */
#घोषणा rcu_is_last_leaf_node(rnp) ((rnp) == &rcu_state.node[rcu_num_nodes - 1])

/*
 * Do a full bपढ़ोth-first scan of the अणुs,पूर्णrcu_node काष्ठाures क्रम the
 * specअगरied state काष्ठाure (क्रम SRCU) or the only rcu_state काष्ठाure
 * (क्रम RCU).
 */
#घोषणा srcu_क्रम_each_node_bपढ़ोth_first(sp, rnp) \
	क्रम ((rnp) = &(sp)->node[0]; \
	     (rnp) < &(sp)->node[rcu_num_nodes]; (rnp)++)
#घोषणा rcu_क्रम_each_node_bपढ़ोth_first(rnp) \
	srcu_क्रम_each_node_bपढ़ोth_first(&rcu_state, rnp)

/*
 * Scan the leaves of the rcu_node hierarchy क्रम the rcu_state काष्ठाure.
 * Note that अगर there is a singleton rcu_node tree with but one rcu_node
 * काष्ठाure, this loop -will- visit the rcu_node काष्ठाure.  It is still
 * a leaf node, even अगर it is also the root node.
 */
#घोषणा rcu_क्रम_each_leaf_node(rnp) \
	क्रम ((rnp) = rcu_first_leaf_node(); \
	     (rnp) < &rcu_state.node[rcu_num_nodes]; (rnp)++)

/*
 * Iterate over all possible CPUs in a leaf RCU node.
 */
#घोषणा क्रम_each_leaf_node_possible_cpu(rnp, cpu) \
	क्रम (WARN_ON_ONCE(!rcu_is_leaf_node(rnp)), \
	     (cpu) = cpumask_next((rnp)->grplo - 1, cpu_possible_mask); \
	     (cpu) <= rnp->grphi; \
	     (cpu) = cpumask_next((cpu), cpu_possible_mask))

/*
 * Iterate over all CPUs in a leaf RCU node's specअगरied mask.
 */
#घोषणा rcu_find_next_bit(rnp, cpu, mask) \
	((rnp)->grplo + find_next_bit(&(mask), BITS_PER_LONG, (cpu)))
#घोषणा क्रम_each_leaf_node_cpu_mask(rnp, cpu, mask) \
	क्रम (WARN_ON_ONCE(!rcu_is_leaf_node(rnp)), \
	     (cpu) = rcu_find_next_bit((rnp), 0, (mask)); \
	     (cpu) <= rnp->grphi; \
	     (cpu) = rcu_find_next_bit((rnp), (cpu) + 1 - (rnp->grplo), (mask)))

/*
 * Wrappers क्रम the rcu_node::lock acquire and release.
 *
 * Because the rcu_nodes क्रमm a tree, the tree traversal locking will observe
 * dअगरferent lock values, this in turn means that an UNLOCK of one level
 * followed by a LOCK of another level करोes not imply a full memory barrier;
 * and most importantly transitivity is lost.
 *
 * In order to restore full ordering between tree levels, augment the regular
 * lock acquire functions with smp_mb__after_unlock_lock().
 *
 * As ->lock of काष्ठा rcu_node is a __निजी field, thereक्रमe one should use
 * these wrappers rather than directly call raw_spin_अणुlock,unlockपूर्ण* on ->lock.
 */
#घोषणा raw_spin_lock_rcu_node(p)					\
करो अणु									\
	raw_spin_lock(&ACCESS_PRIVATE(p, lock));			\
	smp_mb__after_unlock_lock();					\
पूर्ण जबतक (0)

#घोषणा raw_spin_unlock_rcu_node(p)					\
करो अणु									\
	lockdep_निश्चित_irqs_disabled();					\
	raw_spin_unlock(&ACCESS_PRIVATE(p, lock));			\
पूर्ण जबतक (0)

#घोषणा raw_spin_lock_irq_rcu_node(p)					\
करो अणु									\
	raw_spin_lock_irq(&ACCESS_PRIVATE(p, lock));			\
	smp_mb__after_unlock_lock();					\
पूर्ण जबतक (0)

#घोषणा raw_spin_unlock_irq_rcu_node(p)					\
करो अणु									\
	lockdep_निश्चित_irqs_disabled();					\
	raw_spin_unlock_irq(&ACCESS_PRIVATE(p, lock));			\
पूर्ण जबतक (0)

#घोषणा raw_spin_lock_irqsave_rcu_node(p, flags)			\
करो अणु									\
	raw_spin_lock_irqsave(&ACCESS_PRIVATE(p, lock), flags);	\
	smp_mb__after_unlock_lock();					\
पूर्ण जबतक (0)

#घोषणा raw_spin_unlock_irqrestore_rcu_node(p, flags)			\
करो अणु									\
	lockdep_निश्चित_irqs_disabled();					\
	raw_spin_unlock_irqrestore(&ACCESS_PRIVATE(p, lock), flags);	\
पूर्ण जबतक (0)

#घोषणा raw_spin_trylock_rcu_node(p)					\
(अणु									\
	bool ___locked = raw_spin_trylock(&ACCESS_PRIVATE(p, lock));	\
									\
	अगर (___locked)							\
		smp_mb__after_unlock_lock();				\
	___locked;							\
पूर्ण)

#घोषणा raw_lockdep_निश्चित_held_rcu_node(p)				\
	lockdep_निश्चित_held(&ACCESS_PRIVATE(p, lock))

#पूर्ण_अगर /* #अगर defined(CONFIG_SRCU) || !defined(CONFIG_TINY_RCU) */

#अगर_घोषित CONFIG_SRCU
व्योम srcu_init(व्योम);
#अन्यथा /* #अगर_घोषित CONFIG_SRCU */
अटल अंतरभूत व्योम srcu_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_SRCU */

#अगर_घोषित CONFIG_TINY_RCU
/* Tiny RCU करोesn't expedite, as its purpose in lअगरe is instead to be tiny. */
अटल अंतरभूत bool rcu_gp_is_normal(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत bool rcu_gp_is_expedited(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम rcu_expedite_gp(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_unexpedite_gp(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_request_urgent_qs_task(काष्ठा task_काष्ठा *t) अणु पूर्ण
#अन्यथा /* #अगर_घोषित CONFIG_TINY_RCU */
bool rcu_gp_is_normal(व्योम);     /* Internal RCU use. */
bool rcu_gp_is_expedited(व्योम);  /* Internal RCU use. */
व्योम rcu_expedite_gp(व्योम);
व्योम rcu_unexpedite_gp(व्योम);
व्योम rcupdate_announce_bootup_oddness(व्योम);
व्योम show_rcu_tasks_gp_kthपढ़ोs(व्योम);
व्योम rcu_request_urgent_qs_task(काष्ठा task_काष्ठा *t);
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_TINY_RCU */

#घोषणा RCU_SCHEDULER_INACTIVE	0
#घोषणा RCU_SCHEDULER_INIT	1
#घोषणा RCU_SCHEDULER_RUNNING	2

क्रमागत rcutorture_type अणु
	RCU_FLAVOR,
	RCU_TASKS_FLAVOR,
	RCU_TASKS_RUDE_FLAVOR,
	RCU_TASKS_TRACING_FLAVOR,
	RCU_TRIVIAL_FLAVOR,
	SRCU_FLAVOR,
	INVALID_RCU_FLAVOR
पूर्ण;

#अगर defined(CONFIG_TREE_RCU)
व्योम rcutorture_get_gp_data(क्रमागत rcutorture_type test_type, पूर्णांक *flags,
			    अचिन्हित दीर्घ *gp_seq);
व्योम करो_trace_rcu_torture_पढ़ो(स्थिर अक्षर *rcutortuनाम,
			       काष्ठा rcu_head *rhp,
			       अचिन्हित दीर्घ secs,
			       अचिन्हित दीर्घ c_old,
			       अचिन्हित दीर्घ c);
व्योम rcu_gp_set_torture_रुको(पूर्णांक duration);
#अन्यथा
अटल अंतरभूत व्योम rcutorture_get_gp_data(क्रमागत rcutorture_type test_type,
					  पूर्णांक *flags, अचिन्हित दीर्घ *gp_seq)
अणु
	*flags = 0;
	*gp_seq = 0;
पूर्ण
#अगर_घोषित CONFIG_RCU_TRACE
व्योम करो_trace_rcu_torture_पढ़ो(स्थिर अक्षर *rcutortuनाम,
			       काष्ठा rcu_head *rhp,
			       अचिन्हित दीर्घ secs,
			       अचिन्हित दीर्घ c_old,
			       अचिन्हित दीर्घ c);
#अन्यथा
#घोषणा करो_trace_rcu_torture_पढ़ो(rcutortuनाम, rhp, secs, c_old, c) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
अटल अंतरभूत व्योम rcu_gp_set_torture_रुको(पूर्णांक duration) अणु पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_RCU_TORTURE_TEST) || IS_MODULE(CONFIG_RCU_TORTURE_TEST)
दीर्घ rcutorture_sched_setaffinity(pid_t pid, स्थिर काष्ठा cpumask *in_mask);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TINY_SRCU

अटल अंतरभूत व्योम srcutorture_get_gp_data(क्रमागत rcutorture_type test_type,
					   काष्ठा srcu_काष्ठा *sp, पूर्णांक *flags,
					   अचिन्हित दीर्घ *gp_seq)
अणु
	अगर (test_type != SRCU_FLAVOR)
		वापस;
	*flags = 0;
	*gp_seq = sp->srcu_idx;
पूर्ण

#या_अगर defined(CONFIG_TREE_SRCU)

व्योम srcutorture_get_gp_data(क्रमागत rcutorture_type test_type,
			     काष्ठा srcu_काष्ठा *sp, पूर्णांक *flags,
			     अचिन्हित दीर्घ *gp_seq);

#पूर्ण_अगर

#अगर_घोषित CONFIG_TINY_RCU
अटल अंतरभूत bool rcu_dynticks_zero_in_eqs(पूर्णांक cpu, पूर्णांक *vp) अणु वापस false; पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ rcu_get_gp_seq(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ rcu_exp_batches_completed(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ
srcu_batches_completed(काष्ठा srcu_काष्ठा *sp) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम rcu_क्रमce_quiescent_state(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम show_rcu_gp_kthपढ़ोs(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक rcu_get_gp_kthपढ़ोs_prio(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम rcu_fwd_progress_check(अचिन्हित दीर्घ j) अणु पूर्ण
#अन्यथा /* #अगर_घोषित CONFIG_TINY_RCU */
bool rcu_dynticks_zero_in_eqs(पूर्णांक cpu, पूर्णांक *vp);
अचिन्हित दीर्घ rcu_get_gp_seq(व्योम);
अचिन्हित दीर्घ rcu_exp_batches_completed(व्योम);
अचिन्हित दीर्घ srcu_batches_completed(काष्ठा srcu_काष्ठा *sp);
व्योम show_rcu_gp_kthपढ़ोs(व्योम);
पूर्णांक rcu_get_gp_kthपढ़ोs_prio(व्योम);
व्योम rcu_fwd_progress_check(अचिन्हित दीर्घ j);
व्योम rcu_क्रमce_quiescent_state(व्योम);
बाह्य काष्ठा workqueue_काष्ठा *rcu_gp_wq;
बाह्य काष्ठा workqueue_काष्ठा *rcu_par_gp_wq;
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_TINY_RCU */

#अगर_घोषित CONFIG_RCU_NOCB_CPU
bool rcu_is_nocb_cpu(पूर्णांक cpu);
व्योम rcu_bind_current_to_nocb(व्योम);
#अन्यथा
अटल अंतरभूत bool rcu_is_nocb_cpu(पूर्णांक cpu) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम rcu_bind_current_to_nocb(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर !defined(CONFIG_TINY_RCU) && defined(CONFIG_TASKS_RCU)
व्योम show_rcu_tasks_classic_gp_kthपढ़ो(व्योम);
#अन्यथा
अटल अंतरभूत व्योम show_rcu_tasks_classic_gp_kthपढ़ो(व्योम) अणुपूर्ण
#पूर्ण_अगर
#अगर !defined(CONFIG_TINY_RCU) && defined(CONFIG_TASKS_RUDE_RCU)
व्योम show_rcu_tasks_rude_gp_kthपढ़ो(व्योम);
#अन्यथा
अटल अंतरभूत व्योम show_rcu_tasks_rude_gp_kthपढ़ो(व्योम) अणुपूर्ण
#पूर्ण_अगर
#अगर !defined(CONFIG_TINY_RCU) && defined(CONFIG_TASKS_TRACE_RCU)
व्योम show_rcu_tasks_trace_gp_kthपढ़ो(व्योम);
#अन्यथा
अटल अंतरभूत व्योम show_rcu_tasks_trace_gp_kthपढ़ो(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_RCU_H */
