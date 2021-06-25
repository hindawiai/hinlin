<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * RCU segmented callback lists, function definitions
 *
 * Copyright IBM Corporation, 2017
 *
 * Authors: Paul E. McKenney <paulmck@linux.ibm.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "rcu_segcblist.h"

/* Initialize simple callback list. */
व्योम rcu_cblist_init(काष्ठा rcu_cblist *rclp)
अणु
	rclp->head = शून्य;
	rclp->tail = &rclp->head;
	rclp->len = 0;
पूर्ण

/*
 * Enqueue an rcu_head काष्ठाure onto the specअगरied callback list.
 */
व्योम rcu_cblist_enqueue(काष्ठा rcu_cblist *rclp, काष्ठा rcu_head *rhp)
अणु
	*rclp->tail = rhp;
	rclp->tail = &rhp->next;
	WRITE_ONCE(rclp->len, rclp->len + 1);
पूर्ण

/*
 * Flush the second rcu_cblist काष्ठाure onto the first one, obliterating
 * any contents of the first.  If rhp is non-शून्य, enqueue it as the sole
 * element of the second rcu_cblist काष्ठाure, but ensuring that the second
 * rcu_cblist काष्ठाure, अगर initially non-empty, always appears non-empty
 * throughout the process.  If rdp is शून्य, the second rcu_cblist काष्ठाure
 * is instead initialized to empty.
 */
व्योम rcu_cblist_flush_enqueue(काष्ठा rcu_cblist *drclp,
			      काष्ठा rcu_cblist *srclp,
			      काष्ठा rcu_head *rhp)
अणु
	drclp->head = srclp->head;
	अगर (drclp->head)
		drclp->tail = srclp->tail;
	अन्यथा
		drclp->tail = &drclp->head;
	drclp->len = srclp->len;
	अगर (!rhp) अणु
		rcu_cblist_init(srclp);
	पूर्ण अन्यथा अणु
		rhp->next = शून्य;
		srclp->head = rhp;
		srclp->tail = &rhp->next;
		WRITE_ONCE(srclp->len, 1);
	पूर्ण
पूर्ण

/*
 * Dequeue the oldest rcu_head काष्ठाure from the specअगरied callback
 * list.
 */
काष्ठा rcu_head *rcu_cblist_dequeue(काष्ठा rcu_cblist *rclp)
अणु
	काष्ठा rcu_head *rhp;

	rhp = rclp->head;
	अगर (!rhp)
		वापस शून्य;
	rclp->len--;
	rclp->head = rhp->next;
	अगर (!rclp->head)
		rclp->tail = &rclp->head;
	वापस rhp;
पूर्ण

/* Set the length of an rcu_segcblist काष्ठाure. */
अटल व्योम rcu_segcblist_set_len(काष्ठा rcu_segcblist *rsclp, दीर्घ v)
अणु
#अगर_घोषित CONFIG_RCU_NOCB_CPU
	atomic_दीर्घ_set(&rsclp->len, v);
#अन्यथा
	WRITE_ONCE(rsclp->len, v);
#पूर्ण_अगर
पूर्ण

/* Get the length of a segment of the rcu_segcblist काष्ठाure. */
अटल दीर्घ rcu_segcblist_get_seglen(काष्ठा rcu_segcblist *rsclp, पूर्णांक seg)
अणु
	वापस READ_ONCE(rsclp->seglen[seg]);
पूर्ण

/* Return number of callbacks in segmented callback list by summing seglen. */
दीर्घ rcu_segcblist_n_segment_cbs(काष्ठा rcu_segcblist *rsclp)
अणु
	दीर्घ len = 0;
	पूर्णांक i;

	क्रम (i = RCU_DONE_TAIL; i < RCU_CBLIST_NSEGS; i++)
		len += rcu_segcblist_get_seglen(rsclp, i);

	वापस len;
पूर्ण

/* Set the length of a segment of the rcu_segcblist काष्ठाure. */
अटल व्योम rcu_segcblist_set_seglen(काष्ठा rcu_segcblist *rsclp, पूर्णांक seg, दीर्घ v)
अणु
	WRITE_ONCE(rsclp->seglen[seg], v);
पूर्ण

/* Increase the numeric length of a segment by a specअगरied amount. */
अटल व्योम rcu_segcblist_add_seglen(काष्ठा rcu_segcblist *rsclp, पूर्णांक seg, दीर्घ v)
अणु
	WRITE_ONCE(rsclp->seglen[seg], rsclp->seglen[seg] + v);
पूर्ण

/* Move from's segment length to to's segment. */
अटल व्योम rcu_segcblist_move_seglen(काष्ठा rcu_segcblist *rsclp, पूर्णांक from, पूर्णांक to)
अणु
	दीर्घ len;

	अगर (from == to)
		वापस;

	len = rcu_segcblist_get_seglen(rsclp, from);
	अगर (!len)
		वापस;

	rcu_segcblist_add_seglen(rsclp, to, len);
	rcu_segcblist_set_seglen(rsclp, from, 0);
पूर्ण

/* Increment segment's length. */
अटल व्योम rcu_segcblist_inc_seglen(काष्ठा rcu_segcblist *rsclp, पूर्णांक seg)
अणु
	rcu_segcblist_add_seglen(rsclp, seg, 1);
पूर्ण

/*
 * Increase the numeric length of an rcu_segcblist काष्ठाure by the
 * specअगरied amount, which can be negative.  This can cause the ->len
 * field to disagree with the actual number of callbacks on the काष्ठाure.
 * This increase is fully ordered with respect to the callers accesses
 * both beक्रमe and after.
 *
 * So why on earth is a memory barrier required both beक्रमe and after
 * the update to the ->len field???
 *
 * The reason is that rcu_barrier() locklessly samples each CPU's ->len
 * field, and अगर a given CPU's field is zero, aव्योमs IPIing that CPU.
 * This can of course race with both queuing and invoking of callbacks.
 * Failing to correctly handle either of these races could result in
 * rcu_barrier() failing to IPI a CPU that actually had callbacks queued
 * which rcu_barrier() was obligated to रुको on.  And अगर rcu_barrier()
 * failed to रुको on such a callback, unloading certain kernel modules
 * would result in calls to functions whose code was no दीर्घer present in
 * the kernel, क्रम but one example.
 *
 * Thereक्रमe, ->len transitions from 1->0 and 0->1 have to be carefully
 * ordered with respect with both list modअगरications and the rcu_barrier().
 *
 * The queuing हाल is CASE 1 and the invoking हाल is CASE 2.
 *
 * CASE 1: Suppose that CPU 0 has no callbacks queued, but invokes
 * call_rcu() just as CPU 1 invokes rcu_barrier().  CPU 0's ->len field
 * will transition from 0->1, which is one of the transitions that must
 * be handled carefully.  Without the full memory barriers after the ->len
 * update and at the beginning of rcu_barrier(), the following could happen:
 *
 * CPU 0				CPU 1
 *
 * call_rcu().
 *					rcu_barrier() sees ->len as 0.
 * set ->len = 1.
 *					rcu_barrier() करोes nothing.
 *					module is unloaded.
 * callback invokes unloaded function!
 *
 * With the full barriers, any हाल where rcu_barrier() sees ->len as 0 will
 * have unambiguously preceded the वापस from the racing call_rcu(), which
 * means that this call_rcu() invocation is OK to not रुको on.  After all,
 * you are supposed to make sure that any problematic call_rcu() invocations
 * happen beक्रमe the rcu_barrier().
 *
 *
 * CASE 2: Suppose that CPU 0 is invoking its last callback just as
 * CPU 1 invokes rcu_barrier().  CPU 0's ->len field will transition from
 * 1->0, which is one of the transitions that must be handled carefully.
 * Without the full memory barriers beक्रमe the ->len update and at the
 * end of rcu_barrier(), the following could happen:
 *
 * CPU 0				CPU 1
 *
 * start invoking last callback
 * set ->len = 0 (reordered)
 *					rcu_barrier() sees ->len as 0
 *					rcu_barrier() करोes nothing.
 *					module is unloaded
 * callback executing after unloaded!
 *
 * With the full barriers, any हाल where rcu_barrier() sees ->len as 0
 * will be fully ordered after the completion of the callback function,
 * so that the module unloading operation is completely safe.
 *
 */
व्योम rcu_segcblist_add_len(काष्ठा rcu_segcblist *rsclp, दीर्घ v)
अणु
#अगर_घोषित CONFIG_RCU_NOCB_CPU
	smp_mb__beक्रमe_atomic(); // Read header comment above.
	atomic_दीर्घ_add(v, &rsclp->len);
	smp_mb__after_atomic();  // Read header comment above.
#अन्यथा
	smp_mb(); // Read header comment above.
	WRITE_ONCE(rsclp->len, rsclp->len + v);
	smp_mb(); // Read header comment above.
#पूर्ण_अगर
पूर्ण

/*
 * Increase the numeric length of an rcu_segcblist काष्ठाure by one.
 * This can cause the ->len field to disagree with the actual number of
 * callbacks on the काष्ठाure.  This increase is fully ordered with respect
 * to the callers accesses both beक्रमe and after.
 */
व्योम rcu_segcblist_inc_len(काष्ठा rcu_segcblist *rsclp)
अणु
	rcu_segcblist_add_len(rsclp, 1);
पूर्ण

/*
 * Initialize an rcu_segcblist काष्ठाure.
 */
व्योम rcu_segcblist_init(काष्ठा rcu_segcblist *rsclp)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(RCU_NEXT_TAIL + 1 != ARRAY_SIZE(rsclp->gp_seq));
	BUILD_BUG_ON(ARRAY_SIZE(rsclp->tails) != ARRAY_SIZE(rsclp->gp_seq));
	rsclp->head = शून्य;
	क्रम (i = 0; i < RCU_CBLIST_NSEGS; i++) अणु
		rsclp->tails[i] = &rsclp->head;
		rcu_segcblist_set_seglen(rsclp, i, 0);
	पूर्ण
	rcu_segcblist_set_len(rsclp, 0);
	rcu_segcblist_set_flags(rsclp, SEGCBLIST_ENABLED);
पूर्ण

/*
 * Disable the specअगरied rcu_segcblist काष्ठाure, so that callbacks can
 * no दीर्घer be posted to it.  This काष्ठाure must be empty.
 */
व्योम rcu_segcblist_disable(काष्ठा rcu_segcblist *rsclp)
अणु
	WARN_ON_ONCE(!rcu_segcblist_empty(rsclp));
	WARN_ON_ONCE(rcu_segcblist_n_cbs(rsclp));
	rcu_segcblist_clear_flags(rsclp, SEGCBLIST_ENABLED);
पूर्ण

/*
 * Mark the specअगरied rcu_segcblist काष्ठाure as offloaded.
 */
व्योम rcu_segcblist_offload(काष्ठा rcu_segcblist *rsclp, bool offload)
अणु
	अगर (offload) अणु
		rcu_segcblist_clear_flags(rsclp, SEGCBLIST_SOFTIRQ_ONLY);
		rcu_segcblist_set_flags(rsclp, SEGCBLIST_OFFLOADED);
	पूर्ण अन्यथा अणु
		rcu_segcblist_clear_flags(rsclp, SEGCBLIST_OFFLOADED);
	पूर्ण
पूर्ण

/*
 * Does the specअगरied rcu_segcblist काष्ठाure contain callbacks that
 * are पढ़ोy to be invoked?
 */
bool rcu_segcblist_पढ़ोy_cbs(काष्ठा rcu_segcblist *rsclp)
अणु
	वापस rcu_segcblist_is_enabled(rsclp) &&
	       &rsclp->head != READ_ONCE(rsclp->tails[RCU_DONE_TAIL]);
पूर्ण

/*
 * Does the specअगरied rcu_segcblist काष्ठाure contain callbacks that
 * are still pending, that is, not yet पढ़ोy to be invoked?
 */
bool rcu_segcblist_pend_cbs(काष्ठा rcu_segcblist *rsclp)
अणु
	वापस rcu_segcblist_is_enabled(rsclp) &&
	       !rcu_segcblist_restempty(rsclp, RCU_DONE_TAIL);
पूर्ण

/*
 * Return a poपूर्णांकer to the first callback in the specअगरied rcu_segcblist
 * काष्ठाure.  This is useful क्रम diagnostics.
 */
काष्ठा rcu_head *rcu_segcblist_first_cb(काष्ठा rcu_segcblist *rsclp)
अणु
	अगर (rcu_segcblist_is_enabled(rsclp))
		वापस rsclp->head;
	वापस शून्य;
पूर्ण

/*
 * Return a poपूर्णांकer to the first pending callback in the specअगरied
 * rcu_segcblist काष्ठाure.  This is useful just after posting a given
 * callback -- अगर that callback is the first pending callback, then
 * you cannot rely on someone अन्यथा having alपढ़ोy started up the required
 * grace period.
 */
काष्ठा rcu_head *rcu_segcblist_first_pend_cb(काष्ठा rcu_segcblist *rsclp)
अणु
	अगर (rcu_segcblist_is_enabled(rsclp))
		वापस *rsclp->tails[RCU_DONE_TAIL];
	वापस शून्य;
पूर्ण

/*
 * Return false अगर there are no CBs aरुकोing grace periods, otherwise,
 * वापस true and store the nearest रुकोed-upon grace period पूर्णांकo *lp.
 */
bool rcu_segcblist_nextgp(काष्ठा rcu_segcblist *rsclp, अचिन्हित दीर्घ *lp)
अणु
	अगर (!rcu_segcblist_pend_cbs(rsclp))
		वापस false;
	*lp = rsclp->gp_seq[RCU_WAIT_TAIL];
	वापस true;
पूर्ण

/*
 * Enqueue the specअगरied callback onto the specअगरied rcu_segcblist
 * काष्ठाure, updating accounting as needed.  Note that the ->len
 * field may be accessed locklessly, hence the WRITE_ONCE().
 * The ->len field is used by rcu_barrier() and मित्रs to determine
 * अगर it must post a callback on this काष्ठाure, and it is OK
 * क्रम rcu_barrier() to someबार post callbacks needlessly, but
 * असलolutely not OK क्रम it to ever miss posting a callback.
 */
व्योम rcu_segcblist_enqueue(काष्ठा rcu_segcblist *rsclp,
			   काष्ठा rcu_head *rhp)
अणु
	rcu_segcblist_inc_len(rsclp);
	rcu_segcblist_inc_seglen(rsclp, RCU_NEXT_TAIL);
	rhp->next = शून्य;
	WRITE_ONCE(*rsclp->tails[RCU_NEXT_TAIL], rhp);
	WRITE_ONCE(rsclp->tails[RCU_NEXT_TAIL], &rhp->next);
पूर्ण

/*
 * Entrain the specअगरied callback onto the specअगरied rcu_segcblist at
 * the end of the last non-empty segment.  If the entire rcu_segcblist
 * is empty, make no change, but वापस false.
 *
 * This is पूर्णांकended क्रम use by rcu_barrier()-like primitives, -not-
 * क्रम normal grace-period use.  IMPORTANT:  The callback you enqueue
 * will रुको क्रम all prior callbacks, NOT necessarily क्रम a grace
 * period.  You have been warned.
 */
bool rcu_segcblist_entrain(काष्ठा rcu_segcblist *rsclp,
			   काष्ठा rcu_head *rhp)
अणु
	पूर्णांक i;

	अगर (rcu_segcblist_n_cbs(rsclp) == 0)
		वापस false;
	rcu_segcblist_inc_len(rsclp);
	smp_mb(); /* Ensure counts are updated beक्रमe callback is entrained. */
	rhp->next = शून्य;
	क्रम (i = RCU_NEXT_TAIL; i > RCU_DONE_TAIL; i--)
		अगर (rsclp->tails[i] != rsclp->tails[i - 1])
			अवरोध;
	rcu_segcblist_inc_seglen(rsclp, i);
	WRITE_ONCE(*rsclp->tails[i], rhp);
	क्रम (; i <= RCU_NEXT_TAIL; i++)
		WRITE_ONCE(rsclp->tails[i], &rhp->next);
	वापस true;
पूर्ण

/*
 * Extract only those callbacks पढ़ोy to be invoked from the specअगरied
 * rcu_segcblist काष्ठाure and place them in the specअगरied rcu_cblist
 * काष्ठाure.
 */
व्योम rcu_segcblist_extract_करोne_cbs(काष्ठा rcu_segcblist *rsclp,
				    काष्ठा rcu_cblist *rclp)
अणु
	पूर्णांक i;

	अगर (!rcu_segcblist_पढ़ोy_cbs(rsclp))
		वापस; /* Nothing to करो. */
	rclp->len = rcu_segcblist_get_seglen(rsclp, RCU_DONE_TAIL);
	*rclp->tail = rsclp->head;
	WRITE_ONCE(rsclp->head, *rsclp->tails[RCU_DONE_TAIL]);
	WRITE_ONCE(*rsclp->tails[RCU_DONE_TAIL], शून्य);
	rclp->tail = rsclp->tails[RCU_DONE_TAIL];
	क्रम (i = RCU_CBLIST_NSEGS - 1; i >= RCU_DONE_TAIL; i--)
		अगर (rsclp->tails[i] == rsclp->tails[RCU_DONE_TAIL])
			WRITE_ONCE(rsclp->tails[i], &rsclp->head);
	rcu_segcblist_set_seglen(rsclp, RCU_DONE_TAIL, 0);
पूर्ण

/*
 * Extract only those callbacks still pending (not yet पढ़ोy to be
 * invoked) from the specअगरied rcu_segcblist काष्ठाure and place them in
 * the specअगरied rcu_cblist काष्ठाure.  Note that this loses inक्रमmation
 * about any callbacks that might have been partway करोne रुकोing क्रम
 * their grace period.  Too bad!  They will have to start over.
 */
व्योम rcu_segcblist_extract_pend_cbs(काष्ठा rcu_segcblist *rsclp,
				    काष्ठा rcu_cblist *rclp)
अणु
	पूर्णांक i;

	अगर (!rcu_segcblist_pend_cbs(rsclp))
		वापस; /* Nothing to करो. */
	rclp->len = 0;
	*rclp->tail = *rsclp->tails[RCU_DONE_TAIL];
	rclp->tail = rsclp->tails[RCU_NEXT_TAIL];
	WRITE_ONCE(*rsclp->tails[RCU_DONE_TAIL], शून्य);
	क्रम (i = RCU_DONE_TAIL + 1; i < RCU_CBLIST_NSEGS; i++) अणु
		rclp->len += rcu_segcblist_get_seglen(rsclp, i);
		WRITE_ONCE(rsclp->tails[i], rsclp->tails[RCU_DONE_TAIL]);
		rcu_segcblist_set_seglen(rsclp, i, 0);
	पूर्ण
पूर्ण

/*
 * Insert counts from the specअगरied rcu_cblist काष्ठाure in the
 * specअगरied rcu_segcblist काष्ठाure.
 */
व्योम rcu_segcblist_insert_count(काष्ठा rcu_segcblist *rsclp,
				काष्ठा rcu_cblist *rclp)
अणु
	rcu_segcblist_add_len(rsclp, rclp->len);
पूर्ण

/*
 * Move callbacks from the specअगरied rcu_cblist to the beginning of the
 * करोne-callbacks segment of the specअगरied rcu_segcblist.
 */
व्योम rcu_segcblist_insert_करोne_cbs(काष्ठा rcu_segcblist *rsclp,
				   काष्ठा rcu_cblist *rclp)
अणु
	पूर्णांक i;

	अगर (!rclp->head)
		वापस; /* No callbacks to move. */
	rcu_segcblist_add_seglen(rsclp, RCU_DONE_TAIL, rclp->len);
	*rclp->tail = rsclp->head;
	WRITE_ONCE(rsclp->head, rclp->head);
	क्रम (i = RCU_DONE_TAIL; i < RCU_CBLIST_NSEGS; i++)
		अगर (&rsclp->head == rsclp->tails[i])
			WRITE_ONCE(rsclp->tails[i], rclp->tail);
		अन्यथा
			अवरोध;
	rclp->head = शून्य;
	rclp->tail = &rclp->head;
पूर्ण

/*
 * Move callbacks from the specअगरied rcu_cblist to the end of the
 * new-callbacks segment of the specअगरied rcu_segcblist.
 */
व्योम rcu_segcblist_insert_pend_cbs(काष्ठा rcu_segcblist *rsclp,
				   काष्ठा rcu_cblist *rclp)
अणु
	अगर (!rclp->head)
		वापस; /* Nothing to करो. */

	rcu_segcblist_add_seglen(rsclp, RCU_NEXT_TAIL, rclp->len);
	WRITE_ONCE(*rsclp->tails[RCU_NEXT_TAIL], rclp->head);
	WRITE_ONCE(rsclp->tails[RCU_NEXT_TAIL], rclp->tail);
पूर्ण

/*
 * Advance the callbacks in the specअगरied rcu_segcblist काष्ठाure based
 * on the current value passed in क्रम the grace-period counter.
 */
व्योम rcu_segcblist_advance(काष्ठा rcu_segcblist *rsclp, अचिन्हित दीर्घ seq)
अणु
	पूर्णांक i, j;

	WARN_ON_ONCE(!rcu_segcblist_is_enabled(rsclp));
	अगर (rcu_segcblist_restempty(rsclp, RCU_DONE_TAIL))
		वापस;

	/*
	 * Find all callbacks whose ->gp_seq numbers indicate that they
	 * are पढ़ोy to invoke, and put them पूर्णांकo the RCU_DONE_TAIL segment.
	 */
	क्रम (i = RCU_WAIT_TAIL; i < RCU_NEXT_TAIL; i++) अणु
		अगर (ULONG_CMP_LT(seq, rsclp->gp_seq[i]))
			अवरोध;
		WRITE_ONCE(rsclp->tails[RCU_DONE_TAIL], rsclp->tails[i]);
		rcu_segcblist_move_seglen(rsclp, i, RCU_DONE_TAIL);
	पूर्ण

	/* If no callbacks moved, nothing more need be करोne. */
	अगर (i == RCU_WAIT_TAIL)
		वापस;

	/* Clean up tail poपूर्णांकers that might have been misordered above. */
	क्रम (j = RCU_WAIT_TAIL; j < i; j++)
		WRITE_ONCE(rsclp->tails[j], rsclp->tails[RCU_DONE_TAIL]);

	/*
	 * Callbacks moved, so clean up the misordered ->tails[] poपूर्णांकers
	 * that now poपूर्णांक पूर्णांकo the middle of the list of पढ़ोy-to-invoke
	 * callbacks.  The overall effect is to copy करोwn the later poपूर्णांकers
	 * पूर्णांकo the gap that was created by the now-पढ़ोy segments.
	 */
	क्रम (j = RCU_WAIT_TAIL; i < RCU_NEXT_TAIL; i++, j++) अणु
		अगर (rsclp->tails[j] == rsclp->tails[RCU_NEXT_TAIL])
			अवरोध;  /* No more callbacks. */
		WRITE_ONCE(rsclp->tails[j], rsclp->tails[i]);
		rcu_segcblist_move_seglen(rsclp, i, j);
		rsclp->gp_seq[j] = rsclp->gp_seq[i];
	पूर्ण
पूर्ण

/*
 * "Accelerate" callbacks based on more-accurate grace-period inक्रमmation.
 * The reason क्रम this is that RCU करोes not synchronize the beginnings and
 * ends of grace periods, and that callbacks are posted locally.  This in
 * turn means that the callbacks must be labelled conservatively early
 * on, as getting exact inक्रमmation would degrade both perक्रमmance and
 * scalability.  When more accurate grace-period inक्रमmation becomes
 * available, previously posted callbacks can be "accelerated", marking
 * them to complete at the end of the earlier grace period.
 *
 * This function operates on an rcu_segcblist काष्ठाure, and also the
 * grace-period sequence number seq at which new callbacks would become
 * पढ़ोy to invoke.  Returns true अगर there are callbacks that won't be
 * पढ़ोy to invoke until seq, false otherwise.
 */
bool rcu_segcblist_accelerate(काष्ठा rcu_segcblist *rsclp, अचिन्हित दीर्घ seq)
अणु
	पूर्णांक i, j;

	WARN_ON_ONCE(!rcu_segcblist_is_enabled(rsclp));
	अगर (rcu_segcblist_restempty(rsclp, RCU_DONE_TAIL))
		वापस false;

	/*
	 * Find the segment preceding the oldest segment of callbacks
	 * whose ->gp_seq[] completion is at or after that passed in via
	 * "seq", skipping any empty segments.  This oldest segment, aदीर्घ
	 * with any later segments, can be merged in with any newly arrived
	 * callbacks in the RCU_NEXT_TAIL segment, and asचिन्हित "seq"
	 * as their ->gp_seq[] grace-period completion sequence number.
	 */
	क्रम (i = RCU_NEXT_READY_TAIL; i > RCU_DONE_TAIL; i--)
		अगर (rsclp->tails[i] != rsclp->tails[i - 1] &&
		    ULONG_CMP_LT(rsclp->gp_seq[i], seq))
			अवरोध;

	/*
	 * If all the segments contain callbacks that correspond to
	 * earlier grace-period sequence numbers than "seq", leave.
	 * Assuming that the rcu_segcblist काष्ठाure has enough
	 * segments in its arrays, this can only happen अगर some of
	 * the non-करोne segments contain callbacks that really are
	 * पढ़ोy to invoke.  This situation will get straightened
	 * out by the next call to rcu_segcblist_advance().
	 *
	 * Also advance to the oldest segment of callbacks whose
	 * ->gp_seq[] completion is at or after that passed in via "seq",
	 * skipping any empty segments.
	 *
	 * Note that segment "i" (and any lower-numbered segments
	 * containing older callbacks) will be unaffected, and their
	 * grace-period numbers reमुख्य unchanged.  For example, अगर i ==
	 * WAIT_TAIL, then neither WAIT_TAIL nor DONE_TAIL will be touched.
	 * Instead, the CBs in NEXT_TAIL will be merged with those in
	 * NEXT_READY_TAIL and the grace-period number of NEXT_READY_TAIL
	 * would be updated.  NEXT_TAIL would then be empty.
	 */
	अगर (rcu_segcblist_restempty(rsclp, i) || ++i >= RCU_NEXT_TAIL)
		वापस false;

	/* Accounting: everything below i is about to get merged पूर्णांकo i. */
	क्रम (j = i + 1; j <= RCU_NEXT_TAIL; j++)
		rcu_segcblist_move_seglen(rsclp, j, i);

	/*
	 * Merge all later callbacks, including newly arrived callbacks,
	 * पूर्णांकo the segment located by the क्रम-loop above.  Assign "seq"
	 * as the ->gp_seq[] value in order to correctly handle the हाल
	 * where there were no pending callbacks in the rcu_segcblist
	 * काष्ठाure other than in the RCU_NEXT_TAIL segment.
	 */
	क्रम (; i < RCU_NEXT_TAIL; i++) अणु
		WRITE_ONCE(rsclp->tails[i], rsclp->tails[RCU_NEXT_TAIL]);
		rsclp->gp_seq[i] = seq;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Merge the source rcu_segcblist काष्ठाure पूर्णांकo the destination
 * rcu_segcblist काष्ठाure, then initialize the source.  Any pending
 * callbacks from the source get to start over.  It is best to
 * advance and accelerate both the destination and the source
 * beक्रमe merging.
 */
व्योम rcu_segcblist_merge(काष्ठा rcu_segcblist *dst_rsclp,
			 काष्ठा rcu_segcblist *src_rsclp)
अणु
	काष्ठा rcu_cblist करोnecbs;
	काष्ठा rcu_cblist pendcbs;

	lockdep_निश्चित_cpus_held();

	rcu_cblist_init(&करोnecbs);
	rcu_cblist_init(&pendcbs);

	rcu_segcblist_extract_करोne_cbs(src_rsclp, &करोnecbs);
	rcu_segcblist_extract_pend_cbs(src_rsclp, &pendcbs);

	/*
	 * No need smp_mb() beक्रमe setting length to 0, because CPU hotplug
	 * lock excludes rcu_barrier.
	 */
	rcu_segcblist_set_len(src_rsclp, 0);

	rcu_segcblist_insert_count(dst_rsclp, &करोnecbs);
	rcu_segcblist_insert_count(dst_rsclp, &pendcbs);
	rcu_segcblist_insert_करोne_cbs(dst_rsclp, &करोnecbs);
	rcu_segcblist_insert_pend_cbs(dst_rsclp, &pendcbs);

	rcu_segcblist_init(src_rsclp);
पूर्ण
