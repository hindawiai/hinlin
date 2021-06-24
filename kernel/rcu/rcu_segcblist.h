<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * RCU segmented callback lists, पूर्णांकernal-to-rcu header file
 *
 * Copyright IBM Corporation, 2017
 *
 * Authors: Paul E. McKenney <paulmck@linux.ibm.com>
 */

#समावेश <linux/rcu_segcblist.h>

/* Return number of callbacks in the specअगरied callback list. */
अटल अंतरभूत दीर्घ rcu_cblist_n_cbs(काष्ठा rcu_cblist *rclp)
अणु
	वापस READ_ONCE(rclp->len);
पूर्ण

/* Return number of callbacks in segmented callback list by summing seglen. */
दीर्घ rcu_segcblist_n_segment_cbs(काष्ठा rcu_segcblist *rsclp);

व्योम rcu_cblist_init(काष्ठा rcu_cblist *rclp);
व्योम rcu_cblist_enqueue(काष्ठा rcu_cblist *rclp, काष्ठा rcu_head *rhp);
व्योम rcu_cblist_flush_enqueue(काष्ठा rcu_cblist *drclp,
			      काष्ठा rcu_cblist *srclp,
			      काष्ठा rcu_head *rhp);
काष्ठा rcu_head *rcu_cblist_dequeue(काष्ठा rcu_cblist *rclp);

/*
 * Is the specअगरied rcu_segcblist काष्ठाure empty?
 *
 * But careful!  The fact that the ->head field is शून्य करोes not
 * necessarily imply that there are no callbacks associated with
 * this काष्ठाure.  When callbacks are being invoked, they are
 * हटाओd as a group.  If callback invocation must be preempted,
 * the reमुख्यing callbacks will be added back to the list.  Either
 * way, the counts are updated later.
 *
 * So it is often the हाल that rcu_segcblist_n_cbs() should be used
 * instead.
 */
अटल अंतरभूत bool rcu_segcblist_empty(काष्ठा rcu_segcblist *rsclp)
अणु
	वापस !READ_ONCE(rsclp->head);
पूर्ण

/* Return number of callbacks in segmented callback list. */
अटल अंतरभूत दीर्घ rcu_segcblist_n_cbs(काष्ठा rcu_segcblist *rsclp)
अणु
#अगर_घोषित CONFIG_RCU_NOCB_CPU
	वापस atomic_दीर्घ_पढ़ो(&rsclp->len);
#अन्यथा
	वापस READ_ONCE(rsclp->len);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम rcu_segcblist_set_flags(काष्ठा rcu_segcblist *rsclp,
					   पूर्णांक flags)
अणु
	rsclp->flags |= flags;
पूर्ण

अटल अंतरभूत व्योम rcu_segcblist_clear_flags(काष्ठा rcu_segcblist *rsclp,
					     पूर्णांक flags)
अणु
	rsclp->flags &= ~flags;
पूर्ण

अटल अंतरभूत bool rcu_segcblist_test_flags(काष्ठा rcu_segcblist *rsclp,
					    पूर्णांक flags)
अणु
	वापस READ_ONCE(rsclp->flags) & flags;
पूर्ण

/*
 * Is the specअगरied rcu_segcblist enabled, क्रम example, not corresponding
 * to an offline CPU?
 */
अटल अंतरभूत bool rcu_segcblist_is_enabled(काष्ठा rcu_segcblist *rsclp)
अणु
	वापस rcu_segcblist_test_flags(rsclp, SEGCBLIST_ENABLED);
पूर्ण

/* Is the specअगरied rcu_segcblist offloaded, or is SEGCBLIST_SOFTIRQ_ONLY set? */
अटल अंतरभूत bool rcu_segcblist_is_offloaded(काष्ठा rcu_segcblist *rsclp)
अणु
	अगर (IS_ENABLED(CONFIG_RCU_NOCB_CPU) &&
	    !rcu_segcblist_test_flags(rsclp, SEGCBLIST_SOFTIRQ_ONLY))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool rcu_segcblist_completely_offloaded(काष्ठा rcu_segcblist *rsclp)
अणु
	पूर्णांक flags = SEGCBLIST_KTHREAD_CB | SEGCBLIST_KTHREAD_GP | SEGCBLIST_OFFLOADED;

	अगर (IS_ENABLED(CONFIG_RCU_NOCB_CPU) && (rsclp->flags & flags) == flags)
		वापस true;

	वापस false;
पूर्ण

/*
 * Are all segments following the specअगरied segment of the specअगरied
 * rcu_segcblist काष्ठाure empty of callbacks?  (The specअगरied
 * segment might well contain callbacks.)
 */
अटल अंतरभूत bool rcu_segcblist_restempty(काष्ठा rcu_segcblist *rsclp, पूर्णांक seg)
अणु
	वापस !READ_ONCE(*READ_ONCE(rsclp->tails[seg]));
पूर्ण

/*
 * Is the specअगरied segment of the specअगरied rcu_segcblist काष्ठाure
 * empty of callbacks?
 */
अटल अंतरभूत bool rcu_segcblist_segempty(काष्ठा rcu_segcblist *rsclp, पूर्णांक seg)
अणु
	अगर (seg == RCU_DONE_TAIL)
		वापस &rsclp->head == rsclp->tails[RCU_DONE_TAIL];
	वापस rsclp->tails[seg - 1] == rsclp->tails[seg];
पूर्ण

व्योम rcu_segcblist_inc_len(काष्ठा rcu_segcblist *rsclp);
व्योम rcu_segcblist_add_len(काष्ठा rcu_segcblist *rsclp, दीर्घ v);
व्योम rcu_segcblist_init(काष्ठा rcu_segcblist *rsclp);
व्योम rcu_segcblist_disable(काष्ठा rcu_segcblist *rsclp);
व्योम rcu_segcblist_offload(काष्ठा rcu_segcblist *rsclp, bool offload);
bool rcu_segcblist_पढ़ोy_cbs(काष्ठा rcu_segcblist *rsclp);
bool rcu_segcblist_pend_cbs(काष्ठा rcu_segcblist *rsclp);
काष्ठा rcu_head *rcu_segcblist_first_cb(काष्ठा rcu_segcblist *rsclp);
काष्ठा rcu_head *rcu_segcblist_first_pend_cb(काष्ठा rcu_segcblist *rsclp);
bool rcu_segcblist_nextgp(काष्ठा rcu_segcblist *rsclp, अचिन्हित दीर्घ *lp);
व्योम rcu_segcblist_enqueue(काष्ठा rcu_segcblist *rsclp,
			   काष्ठा rcu_head *rhp);
bool rcu_segcblist_entrain(काष्ठा rcu_segcblist *rsclp,
			   काष्ठा rcu_head *rhp);
व्योम rcu_segcblist_extract_करोne_cbs(काष्ठा rcu_segcblist *rsclp,
				    काष्ठा rcu_cblist *rclp);
व्योम rcu_segcblist_extract_pend_cbs(काष्ठा rcu_segcblist *rsclp,
				    काष्ठा rcu_cblist *rclp);
व्योम rcu_segcblist_insert_count(काष्ठा rcu_segcblist *rsclp,
				काष्ठा rcu_cblist *rclp);
व्योम rcu_segcblist_insert_करोne_cbs(काष्ठा rcu_segcblist *rsclp,
				   काष्ठा rcu_cblist *rclp);
व्योम rcu_segcblist_insert_pend_cbs(काष्ठा rcu_segcblist *rsclp,
				   काष्ठा rcu_cblist *rclp);
व्योम rcu_segcblist_advance(काष्ठा rcu_segcblist *rsclp, अचिन्हित दीर्घ seq);
bool rcu_segcblist_accelerate(काष्ठा rcu_segcblist *rsclp, अचिन्हित दीर्घ seq);
व्योम rcu_segcblist_merge(काष्ठा rcu_segcblist *dst_rsclp,
			 काष्ठा rcu_segcblist *src_rsclp);
