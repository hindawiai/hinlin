<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PERCPU_RWSEM_H
#घोषणा _LINUX_PERCPU_RWSEM_H

#समावेश <linux/atomic.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcuरुको.h>
#समावेश <linux/रुको.h>
#समावेश <linux/rcu_sync.h>
#समावेश <linux/lockdep.h>

काष्ठा percpu_rw_semaphore अणु
	काष्ठा rcu_sync		rss;
	अचिन्हित पूर्णांक __percpu	*पढ़ो_count;
	काष्ठा rcuरुको		ग_लिखोr;
	रुको_queue_head_t	रुकोers;
	atomic_t		block;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	dep_map;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
#घोषणा __PERCPU_RWSEM_DEP_MAP_INIT(lockname)	.dep_map = अणु .name = #lockname पूर्ण,
#अन्यथा
#घोषणा __PERCPU_RWSEM_DEP_MAP_INIT(lockname)
#पूर्ण_अगर

#घोषणा __DEFINE_PERCPU_RWSEM(name, is_अटल)				\
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, __percpu_rwsem_rc_##name);		\
is_अटल काष्ठा percpu_rw_semaphore name = अणु				\
	.rss = __RCU_SYNC_INITIALIZER(name.rss),			\
	.पढ़ो_count = &__percpu_rwsem_rc_##name,			\
	.ग_लिखोr = __RCUWAIT_INITIALIZER(name.ग_लिखोr),			\
	.रुकोers = __WAIT_QUEUE_HEAD_INITIALIZER(name.रुकोers),		\
	.block = ATOMIC_INIT(0),					\
	__PERCPU_RWSEM_DEP_MAP_INIT(name)				\
पूर्ण

#घोषणा DEFINE_PERCPU_RWSEM(name)		\
	__DEFINE_PERCPU_RWSEM(name, /* not अटल */)
#घोषणा DEFINE_STATIC_PERCPU_RWSEM(name)	\
	__DEFINE_PERCPU_RWSEM(name, अटल)

बाह्य bool __percpu_करोwn_पढ़ो(काष्ठा percpu_rw_semaphore *, bool);

अटल अंतरभूत व्योम percpu_करोwn_पढ़ो(काष्ठा percpu_rw_semaphore *sem)
अणु
	might_sleep();

	rwsem_acquire_पढ़ो(&sem->dep_map, 0, 0, _RET_IP_);

	preempt_disable();
	/*
	 * We are in an RCU-sched पढ़ो-side critical section, so the ग_लिखोr
	 * cannot both change sem->state from पढ़ोers_fast and start checking
	 * counters जबतक we are here. So अगर we see !sem->state, we know that
	 * the ग_लिखोr won't be checking until we're past the preempt_enable()
	 * and that once the synchronize_rcu() is करोne, the ग_लिखोr will see
	 * anything we did within this RCU-sched पढ़ो-size critical section.
	 */
	अगर (likely(rcu_sync_is_idle(&sem->rss)))
		this_cpu_inc(*sem->पढ़ो_count);
	अन्यथा
		__percpu_करोwn_पढ़ो(sem, false); /* Unconditional memory barrier */
	/*
	 * The preempt_enable() prevents the compiler from
	 * bleeding the critical section out.
	 */
	preempt_enable();
पूर्ण

अटल अंतरभूत bool percpu_करोwn_पढ़ो_trylock(काष्ठा percpu_rw_semaphore *sem)
अणु
	bool ret = true;

	preempt_disable();
	/*
	 * Same as in percpu_करोwn_पढ़ो().
	 */
	अगर (likely(rcu_sync_is_idle(&sem->rss)))
		this_cpu_inc(*sem->पढ़ो_count);
	अन्यथा
		ret = __percpu_करोwn_पढ़ो(sem, true); /* Unconditional memory barrier */
	preempt_enable();
	/*
	 * The barrier() from preempt_enable() prevents the compiler from
	 * bleeding the critical section out.
	 */

	अगर (ret)
		rwsem_acquire_पढ़ो(&sem->dep_map, 0, 1, _RET_IP_);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम percpu_up_पढ़ो(काष्ठा percpu_rw_semaphore *sem)
अणु
	rwsem_release(&sem->dep_map, _RET_IP_);

	preempt_disable();
	/*
	 * Same as in percpu_करोwn_पढ़ो().
	 */
	अगर (likely(rcu_sync_is_idle(&sem->rss))) अणु
		this_cpu_dec(*sem->पढ़ो_count);
	पूर्ण अन्यथा अणु
		/*
		 * slowpath; पढ़ोer will only ever wake a single blocked
		 * ग_लिखोr.
		 */
		smp_mb(); /* B matches C */
		/*
		 * In other words, अगर they see our decrement (presumably to
		 * aggregate zero, as that is the only समय it matters) they
		 * will also see our critical section.
		 */
		this_cpu_dec(*sem->पढ़ो_count);
		rcuरुको_wake_up(&sem->ग_लिखोr);
	पूर्ण
	preempt_enable();
पूर्ण

बाह्य व्योम percpu_करोwn_ग_लिखो(काष्ठा percpu_rw_semaphore *);
बाह्य व्योम percpu_up_ग_लिखो(काष्ठा percpu_rw_semaphore *);

बाह्य पूर्णांक __percpu_init_rwsem(काष्ठा percpu_rw_semaphore *,
				स्थिर अक्षर *, काष्ठा lock_class_key *);

बाह्य व्योम percpu_मुक्त_rwsem(काष्ठा percpu_rw_semaphore *);

#घोषणा percpu_init_rwsem(sem)					\
(अणु								\
	अटल काष्ठा lock_class_key rwsem_key;			\
	__percpu_init_rwsem(sem, #sem, &rwsem_key);		\
पूर्ण)

#घोषणा percpu_rwsem_is_held(sem)	lockdep_is_held(sem)
#घोषणा percpu_rwsem_निश्चित_held(sem)	lockdep_निश्चित_held(sem)

अटल अंतरभूत व्योम percpu_rwsem_release(काष्ठा percpu_rw_semaphore *sem,
					bool पढ़ो, अचिन्हित दीर्घ ip)
अणु
	lock_release(&sem->dep_map, ip);
पूर्ण

अटल अंतरभूत व्योम percpu_rwsem_acquire(काष्ठा percpu_rw_semaphore *sem,
					bool पढ़ो, अचिन्हित दीर्घ ip)
अणु
	lock_acquire(&sem->dep_map, 0, 1, पढ़ो, 1, शून्य, ip);
पूर्ण

#पूर्ण_अगर
