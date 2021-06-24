<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * RCU segmented callback lists
 *
 * This seemingly RCU-निजी file must be available to SRCU users
 * because the size of the TREE SRCU srcu_काष्ठा काष्ठाure depends
 * on these definitions.
 *
 * Copyright IBM Corporation, 2017
 *
 * Authors: Paul E. McKenney <paulmck@linux.net.ibm.com>
 */

#अगर_अघोषित __INCLUDE_LINUX_RCU_SEGCBLIST_H
#घोषणा __INCLUDE_LINUX_RCU_SEGCBLIST_H

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>

/* Simple unsegmented callback lists. */
काष्ठा rcu_cblist अणु
	काष्ठा rcu_head *head;
	काष्ठा rcu_head **tail;
	दीर्घ len;
पूर्ण;

#घोषणा RCU_CBLIST_INITIALIZER(n) अणु .head = शून्य, .tail = &n.head पूर्ण

/* Complicated segmented callback lists.  ;-) */

/*
 * Index values क्रम segments in rcu_segcblist काष्ठाure.
 *
 * The segments are as follows:
 *
 * [head, *tails[RCU_DONE_TAIL]):
 *	Callbacks whose grace period has elapsed, and thus can be invoked.
 * [*tails[RCU_DONE_TAIL], *tails[RCU_WAIT_TAIL]):
 *	Callbacks रुकोing क्रम the current GP from the current CPU's viewpoपूर्णांक.
 * [*tails[RCU_WAIT_TAIL], *tails[RCU_NEXT_READY_TAIL]):
 *	Callbacks that arrived beक्रमe the next GP started, again from
 *	the current CPU's viewpoपूर्णांक.  These can be handled by the next GP.
 * [*tails[RCU_NEXT_READY_TAIL], *tails[RCU_NEXT_TAIL]):
 *	Callbacks that might have arrived after the next GP started.
 *	There is some uncertaपूर्णांकy as to when a given GP starts and
 *	ends, but a CPU knows the exact बार अगर it is the one starting
 *	or ending the GP.  Other CPUs know that the previous GP ends
 *	beक्रमe the next one starts.
 *
 * Note that RCU_WAIT_TAIL cannot be empty unless RCU_NEXT_READY_TAIL is also
 * empty.
 *
 * The ->gp_seq[] array contains the grace-period number at which the
 * corresponding segment of callbacks will be पढ़ोy to invoke.  A given
 * element of this array is meaningful only when the corresponding segment
 * is non-empty, and it is never valid क्रम RCU_DONE_TAIL (whose callbacks
 * are alपढ़ोy पढ़ोy to invoke) or क्रम RCU_NEXT_TAIL (whose callbacks have
 * not yet been asचिन्हित a grace-period number).
 */
#घोषणा RCU_DONE_TAIL		0	/* Also RCU_WAIT head. */
#घोषणा RCU_WAIT_TAIL		1	/* Also RCU_NEXT_READY head. */
#घोषणा RCU_NEXT_READY_TAIL	2	/* Also RCU_NEXT head. */
#घोषणा RCU_NEXT_TAIL		3
#घोषणा RCU_CBLIST_NSEGS	4


/*
 *                     ==NOCB Offloading state machine==
 *
 *
 *  ----------------------------------------------------------------------------
 *  |                         SEGCBLIST_SOFTIRQ_ONLY                           |
 *  |                                                                          |
 *  |  Callbacks processed by rcu_core() from softirqs or local                |
 *  |  rcuc kthपढ़ो, without holding nocb_lock.                                |
 *  ----------------------------------------------------------------------------
 *                                         |
 *                                         v
 *  ----------------------------------------------------------------------------
 *  |                        SEGCBLIST_OFFLOADED                               |
 *  |                                                                          |
 *  | Callbacks processed by rcu_core() from softirqs or local                 |
 *  | rcuc kthपढ़ो, जबतक holding nocb_lock. Waking up CB and GP kthपढ़ोs,     |
 *  | allowing nocb_समयr to be armed.                                         |
 *  ----------------------------------------------------------------------------
 *                                         |
 *                                         v
 *                        -----------------------------------
 *                        |                                 |
 *                        v                                 v
 *  ---------------------------------------  ----------------------------------|
 *  |        SEGCBLIST_OFFLOADED |        |  |     SEGCBLIST_OFFLOADED |       |
 *  |        SEGCBLIST_KTHREAD_CB         |  |     SEGCBLIST_KTHREAD_GP        |
 *  |                                     |  |                                 |
 *  |                                     |  |                                 |
 *  | CB kthपढ़ो woke up and              |  | GP kthपढ़ो woke up and          |
 *  | acknowledged SEGCBLIST_OFFLOADED.   |  | acknowledged SEGCBLIST_OFFLOADED|
 *  | Processes callbacks concurrently    |  |                                 |
 *  | with rcu_core(), holding            |  |                                 |
 *  | nocb_lock.                          |  |                                 |
 *  ---------------------------------------  -----------------------------------
 *                        |                                 |
 *                        -----------------------------------
 *                                         |
 *                                         v
 *  |--------------------------------------------------------------------------|
 *  |                           SEGCBLIST_OFFLOADED |                          |
 *  |                           SEGCBLIST_KTHREAD_CB |                         |
 *  |                           SEGCBLIST_KTHREAD_GP                           |
 *  |                                                                          |
 *  |   Kthपढ़ोs handle callbacks holding nocb_lock, local rcu_core() stops    |
 *  |   handling callbacks. Enable bypass queueing.                            |
 *  ----------------------------------------------------------------------------
 */



/*
 *                       ==NOCB De-Offloading state machine==
 *
 *
 *  |--------------------------------------------------------------------------|
 *  |                           SEGCBLIST_OFFLOADED |                          |
 *  |                           SEGCBLIST_KTHREAD_CB |                         |
 *  |                           SEGCBLIST_KTHREAD_GP                           |
 *  |                                                                          |
 *  |   CB/GP kthपढ़ोs handle callbacks holding nocb_lock, local rcu_core()    |
 *  |   ignores callbacks. Bypass enqueue is enabled.                          |
 *  ----------------------------------------------------------------------------
 *                                      |
 *                                      v
 *  |--------------------------------------------------------------------------|
 *  |                           SEGCBLIST_KTHREAD_CB |                         |
 *  |                           SEGCBLIST_KTHREAD_GP                           |
 *  |                                                                          |
 *  |   CB/GP kthपढ़ोs and local rcu_core() handle callbacks concurrently      |
 *  |   holding nocb_lock. Wake up CB and GP kthपढ़ोs अगर necessary. Disable    |
 *  |   bypass enqueue.                                                        |
 *  ----------------------------------------------------------------------------
 *                                      |
 *                                      v
 *                     -----------------------------------
 *                     |                                 |
 *                     v                                 v
 *  ---------------------------------------------------------------------------|
 *  |                                                                          |
 *  |        SEGCBLIST_KTHREAD_CB         |       SEGCBLIST_KTHREAD_GP         |
 *  |                                     |                                    |
 *  | GP kthपढ़ो woke up and              |   CB kthपढ़ो woke up and           |
 *  | acknowledged the fact that          |   acknowledged the fact that       |
 *  | SEGCBLIST_OFFLOADED got cleared.    |   SEGCBLIST_OFFLOADED got cleared. |
 *  |                                     |   The CB kthपढ़ो goes to sleep     |
 *  | The callbacks from the target CPU   |   until it ever माला_लो re-offloaded. |
 *  | will be ignored from the GP kthपढ़ो |                                    |
 *  | loop.                               |                                    |
 *  ----------------------------------------------------------------------------
 *                      |                                 |
 *                      -----------------------------------
 *                                      |
 *                                      v
 *  ----------------------------------------------------------------------------
 *  |                                   0                                      |
 *  |                                                                          |
 *  | Callbacks processed by rcu_core() from softirqs or local                 |
 *  | rcuc kthपढ़ो, जबतक holding nocb_lock. Forbid nocb_समयr to be armed.    |
 *  | Flush pending nocb_समयr. Flush nocb bypass callbacks.                   |
 *  ----------------------------------------------------------------------------
 *                                      |
 *                                      v
 *  ----------------------------------------------------------------------------
 *  |                         SEGCBLIST_SOFTIRQ_ONLY                           |
 *  |                                                                          |
 *  |  Callbacks processed by rcu_core() from softirqs or local                |
 *  |  rcuc kthपढ़ो, without holding nocb_lock.                                |
 *  ----------------------------------------------------------------------------
 */
#घोषणा SEGCBLIST_ENABLED	BIT(0)
#घोषणा SEGCBLIST_SOFTIRQ_ONLY	BIT(1)
#घोषणा SEGCBLIST_KTHREAD_CB	BIT(2)
#घोषणा SEGCBLIST_KTHREAD_GP	BIT(3)
#घोषणा SEGCBLIST_OFFLOADED	BIT(4)

काष्ठा rcu_segcblist अणु
	काष्ठा rcu_head *head;
	काष्ठा rcu_head **tails[RCU_CBLIST_NSEGS];
	अचिन्हित दीर्घ gp_seq[RCU_CBLIST_NSEGS];
#अगर_घोषित CONFIG_RCU_NOCB_CPU
	atomic_दीर्घ_t len;
#अन्यथा
	दीर्घ len;
#पूर्ण_अगर
	दीर्घ seglen[RCU_CBLIST_NSEGS];
	u8 flags;
पूर्ण;

#घोषणा RCU_SEGCBLIST_INITIALIZER(n) \
अणु \
	.head = शून्य, \
	.tails[RCU_DONE_TAIL] = &n.head, \
	.tails[RCU_WAIT_TAIL] = &n.head, \
	.tails[RCU_NEXT_READY_TAIL] = &n.head, \
	.tails[RCU_NEXT_TAIL] = &n.head, \
पूर्ण

#पूर्ण_अगर /* __INCLUDE_LINUX_RCU_SEGCBLIST_H */
