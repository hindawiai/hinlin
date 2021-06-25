<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Read-Copy Update mechanism क्रम mutual exclusion, adapted क्रम tracing.
 *
 * Copyright (C) 2020 Paul E. McKenney.
 */

#अगर_अघोषित __LINUX_RCUPDATE_TRACE_H
#घोषणा __LINUX_RCUPDATE_TRACE_H

#समावेश <linux/sched.h>
#समावेश <linux/rcupdate.h>

बाह्य काष्ठा lockdep_map rcu_trace_lock_map;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

अटल अंतरभूत पूर्णांक rcu_पढ़ो_lock_trace_held(व्योम)
अणु
	वापस lock_is_held(&rcu_trace_lock_map);
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

अटल अंतरभूत पूर्णांक rcu_पढ़ो_lock_trace_held(व्योम)
अणु
	वापस 1;
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

#अगर_घोषित CONFIG_TASKS_TRACE_RCU

व्योम rcu_पढ़ो_unlock_trace_special(काष्ठा task_काष्ठा *t, पूर्णांक nesting);

/**
 * rcu_पढ़ो_lock_trace - mark beginning of RCU-trace पढ़ो-side critical section
 *
 * When synchronize_rcu_tasks_trace() is invoked by one task, then that
 * task is guaranteed to block until all other tasks निकास their पढ़ो-side
 * critical sections.  Similarly, अगर call_rcu_trace() is invoked on one
 * task जबतक other tasks are within RCU पढ़ो-side critical sections,
 * invocation of the corresponding RCU callback is deferred until after
 * the all the other tasks निकास their critical sections.
 *
 * For more details, please see the करोcumentation क्रम rcu_पढ़ो_lock().
 */
अटल अंतरभूत व्योम rcu_पढ़ो_lock_trace(व्योम)
अणु
	काष्ठा task_काष्ठा *t = current;

	WRITE_ONCE(t->trc_पढ़ोer_nesting, READ_ONCE(t->trc_पढ़ोer_nesting) + 1);
	barrier();
	अगर (IS_ENABLED(CONFIG_TASKS_TRACE_RCU_READ_MB) &&
	    t->trc_पढ़ोer_special.b.need_mb)
		smp_mb(); // Pairs with update-side barriers
	rcu_lock_acquire(&rcu_trace_lock_map);
पूर्ण

/**
 * rcu_पढ़ो_unlock_trace - mark end of RCU-trace पढ़ो-side critical section
 *
 * Pairs with a preceding call to rcu_पढ़ो_lock_trace(), and nesting is
 * allowed.  Invoking a rcu_पढ़ो_unlock_trace() when there is no matching
 * rcu_पढ़ो_lock_trace() is verboten, and will result in lockdep complaपूर्णांकs.
 *
 * For more details, please see the करोcumentation क्रम rcu_पढ़ो_unlock().
 */
अटल अंतरभूत व्योम rcu_पढ़ो_unlock_trace(व्योम)
अणु
	पूर्णांक nesting;
	काष्ठा task_काष्ठा *t = current;

	rcu_lock_release(&rcu_trace_lock_map);
	nesting = READ_ONCE(t->trc_पढ़ोer_nesting) - 1;
	barrier(); // Critical section beक्रमe disabling.
	// Disable IPI-based setting of .need_qs.
	WRITE_ONCE(t->trc_पढ़ोer_nesting, पूर्णांक_न्यून);
	अगर (likely(!READ_ONCE(t->trc_पढ़ोer_special.s)) || nesting) अणु
		WRITE_ONCE(t->trc_पढ़ोer_nesting, nesting);
		वापस;  // We assume shallow पढ़ोer nesting.
	पूर्ण
	rcu_पढ़ो_unlock_trace_special(t, nesting);
पूर्ण

व्योम call_rcu_tasks_trace(काष्ठा rcu_head *rhp, rcu_callback_t func);
व्योम synchronize_rcu_tasks_trace(व्योम);
व्योम rcu_barrier_tasks_trace(व्योम);
#अन्यथा
/*
 * The BPF JIT क्रमms these addresses even when it करोesn't call these
 * functions, so provide definitions that result in runसमय errors.
 */
अटल अंतरभूत व्योम call_rcu_tasks_trace(काष्ठा rcu_head *rhp, rcu_callback_t func) अणु BUG(); पूर्ण
अटल अंतरभूत व्योम rcu_पढ़ो_lock_trace(व्योम) अणु BUG(); पूर्ण
अटल अंतरभूत व्योम rcu_पढ़ो_unlock_trace(व्योम) अणु BUG(); पूर्ण
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_TRACE_RCU */

#पूर्ण_अगर /* __LINUX_RCUPDATE_TRACE_H */
