<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Sleepable Read-Copy Update mechanism क्रम mutual exclusion,
 *	tiny version क्रम non-preemptible single-CPU use.
 *
 * Copyright (C) IBM Corporation, 2017
 *
 * Author: Paul McKenney <paulmck@linux.ibm.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/preempt.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/srcu.h>

#समावेश <linux/rcu_node_tree.h>
#समावेश "rcu_segcblist.h"
#समावेश "rcu.h"

पूर्णांक rcu_scheduler_active __पढ़ो_mostly;
अटल LIST_HEAD(srcu_boot_list);
अटल bool srcu_init_करोne;

अटल पूर्णांक init_srcu_काष्ठा_fields(काष्ठा srcu_काष्ठा *ssp)
अणु
	ssp->srcu_lock_nesting[0] = 0;
	ssp->srcu_lock_nesting[1] = 0;
	init_sरुको_queue_head(&ssp->srcu_wq);
	ssp->srcu_cb_head = शून्य;
	ssp->srcu_cb_tail = &ssp->srcu_cb_head;
	ssp->srcu_gp_running = false;
	ssp->srcu_gp_रुकोing = false;
	ssp->srcu_idx = 0;
	ssp->srcu_idx_max = 0;
	INIT_WORK(&ssp->srcu_work, srcu_drive_gp);
	INIT_LIST_HEAD(&ssp->srcu_work.entry);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

पूर्णांक __init_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp, स्थिर अक्षर *name,
		       काष्ठा lock_class_key *key)
अणु
	/* Don't re-initialize a lock जबतक it is held. */
	debug_check_no_locks_मुक्तd((व्योम *)ssp, माप(*ssp));
	lockdep_init_map(&ssp->dep_map, name, key, 0);
	वापस init_srcu_काष्ठा_fields(ssp);
पूर्ण
EXPORT_SYMBOL_GPL(__init_srcu_काष्ठा);

#अन्यथा /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

/*
 * init_srcu_काष्ठा - initialize a sleep-RCU काष्ठाure
 * @ssp: काष्ठाure to initialize.
 *
 * Must invoke this on a given srcu_काष्ठा beक्रमe passing that srcu_काष्ठा
 * to any other function.  Each srcu_काष्ठा represents a separate करोमुख्य
 * of SRCU protection.
 */
पूर्णांक init_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp)
अणु
	वापस init_srcu_काष्ठा_fields(ssp);
पूर्ण
EXPORT_SYMBOL_GPL(init_srcu_काष्ठा);

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

/*
 * cleanup_srcu_काष्ठा - deस्थिरruct a sleep-RCU काष्ठाure
 * @ssp: काष्ठाure to clean up.
 *
 * Must invoke this after you are finished using a given srcu_काष्ठा that
 * was initialized via init_srcu_काष्ठा(), अन्यथा you leak memory.
 */
व्योम cleanup_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp)
अणु
	WARN_ON(ssp->srcu_lock_nesting[0] || ssp->srcu_lock_nesting[1]);
	flush_work(&ssp->srcu_work);
	WARN_ON(ssp->srcu_gp_running);
	WARN_ON(ssp->srcu_gp_रुकोing);
	WARN_ON(ssp->srcu_cb_head);
	WARN_ON(&ssp->srcu_cb_head != ssp->srcu_cb_tail);
	WARN_ON(ssp->srcu_idx != ssp->srcu_idx_max);
	WARN_ON(ssp->srcu_idx & 0x1);
पूर्ण
EXPORT_SYMBOL_GPL(cleanup_srcu_काष्ठा);

/*
 * Removes the count क्रम the old पढ़ोer from the appropriate element of
 * the srcu_काष्ठा.
 */
व्योम __srcu_पढ़ो_unlock(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx)
अणु
	पूर्णांक newval = ssp->srcu_lock_nesting[idx] - 1;

	WRITE_ONCE(ssp->srcu_lock_nesting[idx], newval);
	अगर (!newval && READ_ONCE(ssp->srcu_gp_रुकोing))
		swake_up_one(&ssp->srcu_wq);
पूर्ण
EXPORT_SYMBOL_GPL(__srcu_पढ़ो_unlock);

/*
 * Workqueue handler to drive one grace period and invoke any callbacks
 * that become पढ़ोy as a result.  Single-CPU and !PREEMPTION operation
 * means that we get away with murder on synchronization.  ;-)
 */
व्योम srcu_drive_gp(काष्ठा work_काष्ठा *wp)
अणु
	पूर्णांक idx;
	काष्ठा rcu_head *lh;
	काष्ठा rcu_head *rhp;
	काष्ठा srcu_काष्ठा *ssp;

	ssp = container_of(wp, काष्ठा srcu_काष्ठा, srcu_work);
	अगर (ssp->srcu_gp_running || USHORT_CMP_GE(ssp->srcu_idx, READ_ONCE(ssp->srcu_idx_max)))
		वापस; /* Alपढ़ोy running or nothing to करो. */

	/* Remove recently arrived callbacks and रुको क्रम पढ़ोers. */
	WRITE_ONCE(ssp->srcu_gp_running, true);
	local_irq_disable();
	lh = ssp->srcu_cb_head;
	ssp->srcu_cb_head = शून्य;
	ssp->srcu_cb_tail = &ssp->srcu_cb_head;
	local_irq_enable();
	idx = (ssp->srcu_idx & 0x2) / 2;
	WRITE_ONCE(ssp->srcu_idx, ssp->srcu_idx + 1);
	WRITE_ONCE(ssp->srcu_gp_रुकोing, true);  /* srcu_पढ़ो_unlock() wakes! */
	sरुको_event_exclusive(ssp->srcu_wq, !READ_ONCE(ssp->srcu_lock_nesting[idx]));
	WRITE_ONCE(ssp->srcu_gp_रुकोing, false); /* srcu_पढ़ो_unlock() cheap. */
	WRITE_ONCE(ssp->srcu_idx, ssp->srcu_idx + 1);

	/* Invoke the callbacks we हटाओd above. */
	जबतक (lh) अणु
		rhp = lh;
		lh = lh->next;
		local_bh_disable();
		rhp->func(rhp);
		local_bh_enable();
	पूर्ण

	/*
	 * Enable rescheduling, and अगर there are more callbacks,
	 * reschedule ourselves.  This can race with a call_srcu()
	 * at पूर्णांकerrupt level, but the ->srcu_gp_running checks will
	 * straighten that out.
	 */
	WRITE_ONCE(ssp->srcu_gp_running, false);
	अगर (USHORT_CMP_LT(ssp->srcu_idx, READ_ONCE(ssp->srcu_idx_max)))
		schedule_work(&ssp->srcu_work);
पूर्ण
EXPORT_SYMBOL_GPL(srcu_drive_gp);

अटल व्योम srcu_gp_start_अगर_needed(काष्ठा srcu_काष्ठा *ssp)
अणु
	अचिन्हित लघु cookie;

	cookie = get_state_synchronize_srcu(ssp);
	अगर (USHORT_CMP_GE(READ_ONCE(ssp->srcu_idx_max), cookie))
		वापस;
	WRITE_ONCE(ssp->srcu_idx_max, cookie);
	अगर (!READ_ONCE(ssp->srcu_gp_running)) अणु
		अगर (likely(srcu_init_करोne))
			schedule_work(&ssp->srcu_work);
		अन्यथा अगर (list_empty(&ssp->srcu_work.entry))
			list_add(&ssp->srcu_work.entry, &srcu_boot_list);
	पूर्ण
पूर्ण

/*
 * Enqueue an SRCU callback on the specअगरied srcu_काष्ठा काष्ठाure,
 * initiating grace-period processing अगर it is not alपढ़ोy running.
 */
व्योम call_srcu(काष्ठा srcu_काष्ठा *ssp, काष्ठा rcu_head *rhp,
	       rcu_callback_t func)
अणु
	अचिन्हित दीर्घ flags;

	rhp->func = func;
	rhp->next = शून्य;
	local_irq_save(flags);
	*ssp->srcu_cb_tail = rhp;
	ssp->srcu_cb_tail = &rhp->next;
	local_irq_restore(flags);
	srcu_gp_start_अगर_needed(ssp);
पूर्ण
EXPORT_SYMBOL_GPL(call_srcu);

/*
 * synchronize_srcu - रुको क्रम prior SRCU पढ़ो-side critical-section completion
 */
व्योम synchronize_srcu(काष्ठा srcu_काष्ठा *ssp)
अणु
	काष्ठा rcu_synchronize rs;

	init_rcu_head_on_stack(&rs.head);
	init_completion(&rs.completion);
	call_srcu(ssp, &rs.head, wakeme_after_rcu);
	रुको_क्रम_completion(&rs.completion);
	destroy_rcu_head_on_stack(&rs.head);
पूर्ण
EXPORT_SYMBOL_GPL(synchronize_srcu);

/*
 * get_state_synchronize_srcu - Provide an end-of-grace-period cookie
 */
अचिन्हित दीर्घ get_state_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp)
अणु
	अचिन्हित दीर्घ ret;

	barrier();
	ret = (READ_ONCE(ssp->srcu_idx) + 3) & ~0x1;
	barrier();
	वापस ret & अच_लघु_उच्च;
पूर्ण
EXPORT_SYMBOL_GPL(get_state_synchronize_srcu);

/*
 * start_poll_synchronize_srcu - Provide cookie and start grace period
 *
 * The dअगरference between this and get_state_synchronize_srcu() is that
 * this function ensures that the poll_state_synchronize_srcu() will
 * eventually वापस the value true.
 */
अचिन्हित दीर्घ start_poll_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp)
अणु
	अचिन्हित दीर्घ ret = get_state_synchronize_srcu(ssp);

	srcu_gp_start_अगर_needed(ssp);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(start_poll_synchronize_srcu);

/*
 * poll_state_synchronize_srcu - Has cookie's grace period ended?
 */
bool poll_state_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp, अचिन्हित दीर्घ cookie)
अणु
	bool ret = USHORT_CMP_GE(READ_ONCE(ssp->srcu_idx), cookie);

	barrier();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(poll_state_synchronize_srcu);

/* Lockdep diagnostics.  */
व्योम __init rcu_scheduler_starting(व्योम)
अणु
	rcu_scheduler_active = RCU_SCHEDULER_RUNNING;
पूर्ण

/*
 * Queue work क्रम srcu_काष्ठा काष्ठाures with early boot callbacks.
 * The work won't actually execute until the workqueue initialization
 * phase that takes place after the scheduler starts.
 */
व्योम __init srcu_init(व्योम)
अणु
	काष्ठा srcu_काष्ठा *ssp;

	srcu_init_करोne = true;
	जबतक (!list_empty(&srcu_boot_list)) अणु
		ssp = list_first_entry(&srcu_boot_list,
				      काष्ठा srcu_काष्ठा, srcu_work.entry);
		list_del_init(&ssp->srcu_work.entry);
		schedule_work(&ssp->srcu_work);
	पूर्ण
पूर्ण
