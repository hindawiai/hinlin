<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * RT Mutexes: blocking mutual exclusion locks with PI support
 *
 * started by Ingo Molnar and Thomas Gleixner:
 *
 *  Copyright (C) 2004-2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2006, Timesys Corp., Thomas Gleixner <tglx@बारys.com>
 *
 * This file contains the निजी data काष्ठाure and API definitions.
 */

#अगर_अघोषित __KERNEL_RTMUTEX_COMMON_H
#घोषणा __KERNEL_RTMUTEX_COMMON_H

#समावेश <linux/debug_locks.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/sched/wake_q.h>

/*
 * This is the control काष्ठाure क्रम tasks blocked on a rt_mutex,
 * which is allocated on the kernel stack on of the blocked task.
 *
 * @tree_entry:		pi node to enqueue पूर्णांकo the mutex रुकोers tree
 * @pi_tree_entry:	pi node to enqueue पूर्णांकo the mutex owner रुकोers tree
 * @task:		task reference to the blocked task
 * @lock:		Poपूर्णांकer to the rt_mutex on which the रुकोer blocks
 * @prio:		Priority of the रुकोer
 * @deadline:		Deadline of the रुकोer अगर applicable
 */
काष्ठा rt_mutex_रुकोer अणु
	काष्ठा rb_node		tree_entry;
	काष्ठा rb_node		pi_tree_entry;
	काष्ठा task_काष्ठा	*task;
	काष्ठा rt_mutex		*lock;
	पूर्णांक			prio;
	u64			deadline;
पूर्ण;

/*
 * Must be guarded because this header is included from rcu/tree_plugin.h
 * unconditionally.
 */
#अगर_घोषित CONFIG_RT_MUTEXES
अटल अंतरभूत पूर्णांक rt_mutex_has_रुकोers(काष्ठा rt_mutex *lock)
अणु
	वापस !RB_EMPTY_ROOT(&lock->रुकोers.rb_root);
पूर्ण

अटल अंतरभूत काष्ठा rt_mutex_रुकोer *rt_mutex_top_रुकोer(काष्ठा rt_mutex *lock)
अणु
	काष्ठा rb_node *lefपंचांगost = rb_first_cached(&lock->रुकोers);
	काष्ठा rt_mutex_रुकोer *w = शून्य;

	अगर (lefपंचांगost) अणु
		w = rb_entry(lefपंचांगost, काष्ठा rt_mutex_रुकोer, tree_entry);
		BUG_ON(w->lock != lock);
	पूर्ण
	वापस w;
पूर्ण

अटल अंतरभूत पूर्णांक task_has_pi_रुकोers(काष्ठा task_काष्ठा *p)
अणु
	वापस !RB_EMPTY_ROOT(&p->pi_रुकोers.rb_root);
पूर्ण

अटल अंतरभूत काष्ठा rt_mutex_रुकोer *task_top_pi_रुकोer(काष्ठा task_काष्ठा *p)
अणु
	वापस rb_entry(p->pi_रुकोers.rb_lefपंचांगost, काष्ठा rt_mutex_रुकोer,
			pi_tree_entry);
पूर्ण

#घोषणा RT_MUTEX_HAS_WAITERS	1UL

अटल अंतरभूत काष्ठा task_काष्ठा *rt_mutex_owner(काष्ठा rt_mutex *lock)
अणु
	अचिन्हित दीर्घ owner = (अचिन्हित दीर्घ) READ_ONCE(lock->owner);

	वापस (काष्ठा task_काष्ठा *) (owner & ~RT_MUTEX_HAS_WAITERS);
पूर्ण
#अन्यथा /* CONFIG_RT_MUTEXES */
/* Used in rcu/tree_plugin.h */
अटल अंतरभूत काष्ठा task_काष्ठा *rt_mutex_owner(काष्ठा rt_mutex *lock)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर  /* !CONFIG_RT_MUTEXES */

/*
 * Constants क्रम rt mutex functions which have a selectable deadlock
 * detection.
 *
 * RT_MUTEX_MIN_CHAINWALK:	Stops the lock chain walk when there are
 *				no further PI adjusपंचांगents to be made.
 *
 * RT_MUTEX_FULL_CHAINWALK:	Invoke deadlock detection with a full
 *				walk of the lock chain.
 */
क्रमागत rपंचांगutex_chainwalk अणु
	RT_MUTEX_MIN_CHAINWALK,
	RT_MUTEX_FULL_CHAINWALK,
पूर्ण;

अटल अंतरभूत व्योम __rt_mutex_basic_init(काष्ठा rt_mutex *lock)
अणु
	lock->owner = शून्य;
	raw_spin_lock_init(&lock->रुको_lock);
	lock->रुकोers = RB_ROOT_CACHED;
पूर्ण

/*
 * PI-futex support (proxy locking functions, etc.):
 */
बाह्य व्योम rt_mutex_init_proxy_locked(काष्ठा rt_mutex *lock,
				       काष्ठा task_काष्ठा *proxy_owner);
बाह्य व्योम rt_mutex_proxy_unlock(काष्ठा rt_mutex *lock);
बाह्य व्योम rt_mutex_init_रुकोer(काष्ठा rt_mutex_रुकोer *रुकोer);
बाह्य पूर्णांक __rt_mutex_start_proxy_lock(काष्ठा rt_mutex *lock,
				     काष्ठा rt_mutex_रुकोer *रुकोer,
				     काष्ठा task_काष्ठा *task);
बाह्य पूर्णांक rt_mutex_start_proxy_lock(काष्ठा rt_mutex *lock,
				     काष्ठा rt_mutex_रुकोer *रुकोer,
				     काष्ठा task_काष्ठा *task);
बाह्य पूर्णांक rt_mutex_रुको_proxy_lock(काष्ठा rt_mutex *lock,
			       काष्ठा hrसमयr_sleeper *to,
			       काष्ठा rt_mutex_रुकोer *रुकोer);
बाह्य bool rt_mutex_cleanup_proxy_lock(काष्ठा rt_mutex *lock,
				 काष्ठा rt_mutex_रुकोer *रुकोer);

बाह्य पूर्णांक rt_mutex_futex_trylock(काष्ठा rt_mutex *l);
बाह्य पूर्णांक __rt_mutex_futex_trylock(काष्ठा rt_mutex *l);

बाह्य व्योम rt_mutex_futex_unlock(काष्ठा rt_mutex *lock);
बाह्य bool __rt_mutex_futex_unlock(काष्ठा rt_mutex *lock,
				 काष्ठा wake_q_head *wqh);

बाह्य व्योम rt_mutex_postunlock(काष्ठा wake_q_head *wake_q);

/* Debug functions */
अटल अंतरभूत व्योम debug_rt_mutex_unlock(काष्ठा rt_mutex *lock)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_RT_MUTEXES))
		DEBUG_LOCKS_WARN_ON(rt_mutex_owner(lock) != current);
पूर्ण

अटल अंतरभूत व्योम debug_rt_mutex_proxy_unlock(काष्ठा rt_mutex *lock)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_RT_MUTEXES))
		DEBUG_LOCKS_WARN_ON(!rt_mutex_owner(lock));
पूर्ण

अटल अंतरभूत व्योम debug_rt_mutex_init_रुकोer(काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_RT_MUTEXES))
		स_रखो(रुकोer, 0x11, माप(*रुकोer));
पूर्ण

अटल अंतरभूत व्योम debug_rt_mutex_मुक्त_रुकोer(काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_RT_MUTEXES))
		स_रखो(रुकोer, 0x22, माप(*रुकोer));
पूर्ण

#पूर्ण_अगर
