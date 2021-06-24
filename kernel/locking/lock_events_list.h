<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * Authors: Waiman Long <दीर्घman@redhat.com>
 */

#अगर_अघोषित LOCK_EVENT
#घोषणा LOCK_EVENT(name)	LOCKEVENT_ ## name,
#पूर्ण_अगर

#अगर_घोषित CONFIG_QUEUED_SPINLOCKS
#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
/*
 * Locking events क्रम PV qspinlock.
 */
LOCK_EVENT(pv_hash_hops)	/* Average # of hops per hashing operation */
LOCK_EVENT(pv_kick_unlock)	/* # of vCPU kicks issued at unlock समय   */
LOCK_EVENT(pv_kick_wake)	/* # of vCPU kicks क्रम pv_latency_wake	   */
LOCK_EVENT(pv_latency_kick)	/* Average latency (ns) of vCPU kick	   */
LOCK_EVENT(pv_latency_wake)	/* Average latency (ns) of kick-to-wakeup  */
LOCK_EVENT(pv_lock_stealing)	/* # of lock stealing operations	   */
LOCK_EVENT(pv_spurious_wakeup)	/* # of spurious wakeups in non-head vCPUs */
LOCK_EVENT(pv_रुको_again)	/* # of रुको's after queue head vCPU kick  */
LOCK_EVENT(pv_रुको_early)	/* # of early vCPU रुको's		   */
LOCK_EVENT(pv_रुको_head)	/* # of vCPU रुको's at the queue head	   */
LOCK_EVENT(pv_रुको_node)	/* # of vCPU रुको's at non-head queue node */
#पूर्ण_अगर /* CONFIG_PARAVIRT_SPINLOCKS */

/*
 * Locking events क्रम qspinlock
 *
 * Subtracting lock_use_node[234] from lock_slowpath will give you
 * lock_use_node1.
 */
LOCK_EVENT(lock_pending)	/* # of locking ops via pending code	     */
LOCK_EVENT(lock_slowpath)	/* # of locking ops via MCS lock queue	     */
LOCK_EVENT(lock_use_node2)	/* # of locking ops that use 2nd percpu node */
LOCK_EVENT(lock_use_node3)	/* # of locking ops that use 3rd percpu node */
LOCK_EVENT(lock_use_node4)	/* # of locking ops that use 4th percpu node */
LOCK_EVENT(lock_no_node)	/* # of locking ops w/o using percpu node    */
#पूर्ण_अगर /* CONFIG_QUEUED_SPINLOCKS */

/*
 * Locking events क्रम rwsem
 */
LOCK_EVENT(rwsem_sleep_पढ़ोer)	/* # of पढ़ोer sleeps			*/
LOCK_EVENT(rwsem_sleep_ग_लिखोr)	/* # of ग_लिखोr sleeps			*/
LOCK_EVENT(rwsem_wake_पढ़ोer)	/* # of पढ़ोer wakeups			*/
LOCK_EVENT(rwsem_wake_ग_लिखोr)	/* # of ग_लिखोr wakeups			*/
LOCK_EVENT(rwsem_opt_lock)	/* # of opt-acquired ग_लिखो locks	*/
LOCK_EVENT(rwsem_opt_fail)	/* # of failed optspins			*/
LOCK_EVENT(rwsem_opt_nospin)	/* # of disabled optspins		*/
LOCK_EVENT(rwsem_rlock)		/* # of पढ़ो locks acquired		*/
LOCK_EVENT(rwsem_rlock_steal)	/* # of पढ़ो locks by lock stealing	*/
LOCK_EVENT(rwsem_rlock_fast)	/* # of fast पढ़ो locks acquired	*/
LOCK_EVENT(rwsem_rlock_fail)	/* # of failed पढ़ो lock acquisitions	*/
LOCK_EVENT(rwsem_rlock_hanकरोff)	/* # of पढ़ो lock hanकरोffs		*/
LOCK_EVENT(rwsem_wlock)		/* # of ग_लिखो locks acquired		*/
LOCK_EVENT(rwsem_wlock_fail)	/* # of failed ग_लिखो lock acquisitions	*/
LOCK_EVENT(rwsem_wlock_hanकरोff)	/* # of ग_लिखो lock hanकरोffs		*/
