<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Mutexes: blocking mutual exclusion locks
 *
 * started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * This file contains the मुख्य data काष्ठाure and API definitions.
 */
#अगर_अघोषित __LINUX_MUTEX_H
#घोषणा __LINUX_MUTEX_H

#समावेश <यंत्र/current.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/osq_lock.h>
#समावेश <linux/debug_locks.h>

काष्ठा ww_class;
काष्ठा ww_acquire_ctx;

/*
 * Simple, straightक्रमward mutexes with strict semantics:
 *
 * - only one task can hold the mutex at a समय
 * - only the owner can unlock the mutex
 * - multiple unlocks are not permitted
 * - recursive locking is not permitted
 * - a mutex object must be initialized via the API
 * - a mutex object must not be initialized via स_रखो or copying
 * - task may not निकास with mutex held
 * - memory areas where held locks reside must not be मुक्तd
 * - held mutexes must not be reinitialized
 * - mutexes may not be used in hardware or software पूर्णांकerrupt
 *   contexts such as tasklets and समयrs
 *
 * These semantics are fully enक्रमced when DEBUG_MUTEXES is
 * enabled. Furthermore, besides enक्रमcing the above rules, the mutex
 * debugging code also implements a number of additional features
 * that make lock debugging easier and faster:
 *
 * - uses symbolic names of mutexes, whenever they are prपूर्णांकed in debug output
 * - poपूर्णांक-of-acquire tracking, symbolic lookup of function names
 * - list of all locks held in the प्रणाली, prपूर्णांकout of them
 * - owner tracking
 * - detects self-recursing locks and prपूर्णांकs out all relevant info
 * - detects multi-task circular deadlocks and prपूर्णांकs out all affected
 *   locks and tasks (and only those tasks)
 */
काष्ठा mutex अणु
	atomic_दीर्घ_t		owner;
	spinlock_t		रुको_lock;
#अगर_घोषित CONFIG_MUTEX_SPIN_ON_OWNER
	काष्ठा optimistic_spin_queue osq; /* Spinner MCS lock */
#पूर्ण_अगर
	काष्ठा list_head	रुको_list;
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	व्योम			*magic;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	dep_map;
#पूर्ण_अगर
पूर्ण;

काष्ठा ww_mutex अणु
	काष्ठा mutex base;
	काष्ठा ww_acquire_ctx *ctx;
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	काष्ठा ww_class *ww_class;
#पूर्ण_अगर
पूर्ण;

/*
 * This is the control काष्ठाure क्रम tasks blocked on mutex,
 * which resides on the blocked task's kernel stack:
 */
काष्ठा mutex_रुकोer अणु
	काष्ठा list_head	list;
	काष्ठा task_काष्ठा	*task;
	काष्ठा ww_acquire_ctx	*ww_ctx;
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	व्योम			*magic;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_MUTEXES

#घोषणा __DEBUG_MUTEX_INITIALIZER(lockname)				\
	, .magic = &lockname

बाह्य व्योम mutex_destroy(काष्ठा mutex *lock);

#अन्यथा

# define __DEBUG_MUTEX_INITIALIZER(lockname)

अटल अंतरभूत व्योम mutex_destroy(काष्ठा mutex *lock) अणुपूर्ण

#पूर्ण_अगर

/**
 * mutex_init - initialize the mutex
 * @mutex: the mutex to be initialized
 *
 * Initialize the mutex to unlocked state.
 *
 * It is not allowed to initialize an alपढ़ोy locked mutex.
 */
#घोषणा mutex_init(mutex)						\
करो अणु									\
	अटल काष्ठा lock_class_key __key;				\
									\
	__mutex_init((mutex), #mutex, &__key);				\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define __DEP_MAP_MUTEX_INITIALIZER(lockname)			\
		, .dep_map = अणु					\
			.name = #lockname,			\
			.रुको_type_inner = LD_WAIT_SLEEP,	\
		पूर्ण
#अन्यथा
# define __DEP_MAP_MUTEX_INITIALIZER(lockname)
#पूर्ण_अगर

#घोषणा __MUTEX_INITIALIZER(lockname) \
		अणु .owner = ATOMIC_LONG_INIT(0) \
		, .रुको_lock = __SPIN_LOCK_UNLOCKED(lockname.रुको_lock) \
		, .रुको_list = LIST_HEAD_INIT(lockname.रुको_list) \
		__DEBUG_MUTEX_INITIALIZER(lockname) \
		__DEP_MAP_MUTEX_INITIALIZER(lockname) पूर्ण

#घोषणा DEFINE_MUTEX(mutexname) \
	काष्ठा mutex mutexname = __MUTEX_INITIALIZER(mutexname)

बाह्य व्योम __mutex_init(काष्ठा mutex *lock, स्थिर अक्षर *name,
			 काष्ठा lock_class_key *key);

/**
 * mutex_is_locked - is the mutex locked
 * @lock: the mutex to be queried
 *
 * Returns true अगर the mutex is locked, false अगर unlocked.
 */
बाह्य bool mutex_is_locked(काष्ठा mutex *lock);

/*
 * See kernel/locking/mutex.c क्रम detailed करोcumentation of these APIs.
 * Also see Documentation/locking/mutex-design.rst.
 */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
बाह्य व्योम mutex_lock_nested(काष्ठा mutex *lock, अचिन्हित पूर्णांक subclass);
बाह्य व्योम _mutex_lock_nest_lock(काष्ठा mutex *lock, काष्ठा lockdep_map *nest_lock);

बाह्य पूर्णांक __must_check mutex_lock_पूर्णांकerruptible_nested(काष्ठा mutex *lock,
					अचिन्हित पूर्णांक subclass);
बाह्य पूर्णांक __must_check mutex_lock_समाप्तable_nested(काष्ठा mutex *lock,
					अचिन्हित पूर्णांक subclass);
बाह्य व्योम mutex_lock_io_nested(काष्ठा mutex *lock, अचिन्हित पूर्णांक subclass);

#घोषणा mutex_lock(lock) mutex_lock_nested(lock, 0)
#घोषणा mutex_lock_पूर्णांकerruptible(lock) mutex_lock_पूर्णांकerruptible_nested(lock, 0)
#घोषणा mutex_lock_समाप्तable(lock) mutex_lock_समाप्तable_nested(lock, 0)
#घोषणा mutex_lock_io(lock) mutex_lock_io_nested(lock, 0)

#घोषणा mutex_lock_nest_lock(lock, nest_lock)				\
करो अणु									\
	typecheck(काष्ठा lockdep_map *, &(nest_lock)->dep_map);	\
	_mutex_lock_nest_lock(lock, &(nest_lock)->dep_map);		\
पूर्ण जबतक (0)

#अन्यथा
बाह्य व्योम mutex_lock(काष्ठा mutex *lock);
बाह्य पूर्णांक __must_check mutex_lock_पूर्णांकerruptible(काष्ठा mutex *lock);
बाह्य पूर्णांक __must_check mutex_lock_समाप्तable(काष्ठा mutex *lock);
बाह्य व्योम mutex_lock_io(काष्ठा mutex *lock);

# define mutex_lock_nested(lock, subclass) mutex_lock(lock)
# define mutex_lock_पूर्णांकerruptible_nested(lock, subclass) mutex_lock_पूर्णांकerruptible(lock)
# define mutex_lock_समाप्तable_nested(lock, subclass) mutex_lock_समाप्तable(lock)
# define mutex_lock_nest_lock(lock, nest_lock) mutex_lock(lock)
# define mutex_lock_io_nested(lock, subclass) mutex_lock_io(lock)
#पूर्ण_अगर

/*
 * NOTE: mutex_trylock() follows the spin_trylock() convention,
 *       not the करोwn_trylock() convention!
 *
 * Returns 1 अगर the mutex has been acquired successfully, and 0 on contention.
 */
बाह्य पूर्णांक mutex_trylock(काष्ठा mutex *lock);
बाह्य व्योम mutex_unlock(काष्ठा mutex *lock);

बाह्य पूर्णांक atomic_dec_and_mutex_lock(atomic_t *cnt, काष्ठा mutex *lock);

#पूर्ण_अगर /* __LINUX_MUTEX_H */
