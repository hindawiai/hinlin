<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Read-Copy Update mechanism क्रम mutual exclusion, the Bloatwatch edition.
 *
 * Copyright IBM Corporation, 2008
 *
 * Author: Paul E. McKenney <paulmck@linux.ibm.com>
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *		Documentation/RCU
 */
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/cpu.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश "rcu.h"

/* Global control variables क्रम rcupdate callback mechanism. */
काष्ठा rcu_ctrlblk अणु
	काष्ठा rcu_head *rcucblist;	/* List of pending callbacks (CBs). */
	काष्ठा rcu_head **करोnetail;	/* ->next poपूर्णांकer of last "done" CB. */
	काष्ठा rcu_head **curtail;	/* ->next poपूर्णांकer of last CB. */
	अचिन्हित दीर्घ gp_seq;		/* Grace-period counter. */
पूर्ण;

/* Definition क्रम rcupdate control block. */
अटल काष्ठा rcu_ctrlblk rcu_ctrlblk = अणु
	.करोnetail	= &rcu_ctrlblk.rcucblist,
	.curtail	= &rcu_ctrlblk.rcucblist,
	.gp_seq		= 0 - 300UL,
पूर्ण;

व्योम rcu_barrier(व्योम)
अणु
	रुको_rcu_gp(call_rcu);
पूर्ण
EXPORT_SYMBOL(rcu_barrier);

/* Record an rcu quiescent state.  */
व्योम rcu_qs(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (rcu_ctrlblk.करोnetail != rcu_ctrlblk.curtail) अणु
		rcu_ctrlblk.करोnetail = rcu_ctrlblk.curtail;
		उठाओ_softirq_irqoff(RCU_SOFTIRQ);
	पूर्ण
	WRITE_ONCE(rcu_ctrlblk.gp_seq, rcu_ctrlblk.gp_seq + 1);
	local_irq_restore(flags);
पूर्ण

/*
 * Check to see अगर the scheduling-घड़ी पूर्णांकerrupt came from an extended
 * quiescent state, and, अगर so, tell RCU about it.  This function must
 * be called from hardirq context.  It is normally called from the
 * scheduling-घड़ी पूर्णांकerrupt.
 */
व्योम rcu_sched_घड़ी_irq(पूर्णांक user)
अणु
	अगर (user) अणु
		rcu_qs();
	पूर्ण अन्यथा अगर (rcu_ctrlblk.करोnetail != rcu_ctrlblk.curtail) अणु
		set_tsk_need_resched(current);
		set_preempt_need_resched();
	पूर्ण
पूर्ण

/*
 * Reclaim the specअगरied callback, either by invoking it क्रम non-kमुक्त हालs or
 * मुक्तing it directly (क्रम kमुक्त). Return true अगर kमुक्तing, false otherwise.
 */
अटल अंतरभूत bool rcu_reclaim_tiny(काष्ठा rcu_head *head)
अणु
	rcu_callback_t f;
	अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)head->func;

	rcu_lock_acquire(&rcu_callback_map);
	अगर (__is_kvमुक्त_rcu_offset(offset)) अणु
		trace_rcu_invoke_kvमुक्त_callback("", head, offset);
		kvमुक्त((व्योम *)head - offset);
		rcu_lock_release(&rcu_callback_map);
		वापस true;
	पूर्ण

	trace_rcu_invoke_callback("", head);
	f = head->func;
	WRITE_ONCE(head->func, (rcu_callback_t)0L);
	f(head);
	rcu_lock_release(&rcu_callback_map);
	वापस false;
पूर्ण

/* Invoke the RCU callbacks whose grace period has elapsed.  */
अटल __latent_entropy व्योम rcu_process_callbacks(काष्ठा softirq_action *unused)
अणु
	काष्ठा rcu_head *next, *list;
	अचिन्हित दीर्घ flags;

	/* Move the पढ़ोy-to-invoke callbacks to a local list. */
	local_irq_save(flags);
	अगर (rcu_ctrlblk.करोnetail == &rcu_ctrlblk.rcucblist) अणु
		/* No callbacks पढ़ोy, so just leave. */
		local_irq_restore(flags);
		वापस;
	पूर्ण
	list = rcu_ctrlblk.rcucblist;
	rcu_ctrlblk.rcucblist = *rcu_ctrlblk.करोnetail;
	*rcu_ctrlblk.करोnetail = शून्य;
	अगर (rcu_ctrlblk.curtail == rcu_ctrlblk.करोnetail)
		rcu_ctrlblk.curtail = &rcu_ctrlblk.rcucblist;
	rcu_ctrlblk.करोnetail = &rcu_ctrlblk.rcucblist;
	local_irq_restore(flags);

	/* Invoke the callbacks on the local list. */
	जबतक (list) अणु
		next = list->next;
		prefetch(next);
		debug_rcu_head_unqueue(list);
		local_bh_disable();
		rcu_reclaim_tiny(list);
		local_bh_enable();
		list = next;
	पूर्ण
पूर्ण

/*
 * Wait क्रम a grace period to elapse.  But it is illegal to invoke
 * synchronize_rcu() from within an RCU पढ़ो-side critical section.
 * Thereक्रमe, any legal call to synchronize_rcu() is a quiescent
 * state, and so on a UP प्रणाली, synchronize_rcu() need करो nothing.
 * (But Lai Jiangshan poपूर्णांकs out the benefits of करोing might_sleep()
 * to reduce latency.)
 *
 * Cool, huh?  (Due to Josh Triplett.)
 */
व्योम synchronize_rcu(व्योम)
अणु
	RCU_LOCKDEP_WARN(lock_is_held(&rcu_bh_lock_map) ||
			 lock_is_held(&rcu_lock_map) ||
			 lock_is_held(&rcu_sched_lock_map),
			 "Illegal synchronize_rcu() in RCU read-side critical section");
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_rcu);

/*
 * Post an RCU callback to be invoked after the end of an RCU grace
 * period.  But since we have but one CPU, that would be after any
 * quiescent state.
 */
व्योम call_rcu(काष्ठा rcu_head *head, rcu_callback_t func)
अणु
	अचिन्हित दीर्घ flags;

	debug_rcu_head_queue(head);
	head->func = func;
	head->next = शून्य;

	local_irq_save(flags);
	*rcu_ctrlblk.curtail = head;
	rcu_ctrlblk.curtail = &head->next;
	local_irq_restore(flags);

	अगर (unlikely(is_idle_task(current))) अणु
		/* क्रमce scheduling क्रम rcu_qs() */
		resched_cpu(0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(call_rcu);

/*
 * Return a grace-period-counter "cookie".  For more inक्रमmation,
 * see the Tree RCU header comment.
 */
अचिन्हित दीर्घ get_state_synchronize_rcu(व्योम)
अणु
	वापस READ_ONCE(rcu_ctrlblk.gp_seq);
पूर्ण
EXPORT_SYMBOL_GPL(get_state_synchronize_rcu);

/*
 * Return a grace-period-counter "cookie" and ensure that a future grace
 * period completes.  For more inक्रमmation, see the Tree RCU header comment.
 */
अचिन्हित दीर्घ start_poll_synchronize_rcu(व्योम)
अणु
	अचिन्हित दीर्घ gp_seq = get_state_synchronize_rcu();

	अगर (unlikely(is_idle_task(current))) अणु
		/* क्रमce scheduling क्रम rcu_qs() */
		resched_cpu(0);
	पूर्ण
	वापस gp_seq;
पूर्ण
EXPORT_SYMBOL_GPL(start_poll_synchronize_rcu);

/*
 * Return true अगर the grace period corresponding to oldstate has completed
 * and false otherwise.  For more inक्रमmation, see the Tree RCU header
 * comment.
 */
bool poll_state_synchronize_rcu(अचिन्हित दीर्घ oldstate)
अणु
	वापस READ_ONCE(rcu_ctrlblk.gp_seq) != oldstate;
पूर्ण
EXPORT_SYMBOL_GPL(poll_state_synchronize_rcu);

व्योम __init rcu_init(व्योम)
अणु
	खोलो_softirq(RCU_SOFTIRQ, rcu_process_callbacks);
	rcu_early_boot_tests();
	srcu_init();
पूर्ण
