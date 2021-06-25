<शैली गुरु>
/*
 * kernel/mutex-debug.c
 *
 * Debugging code क्रम mutexes
 *
 * Started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * lock debugging, locking tree, deadlock detection started by:
 *
 *  Copyright (C) 2004, LynuxWorks, Inc., Igor Manyilov, Bill Huey
 *  Released under the General Public License (GPL).
 */
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/poison.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debug_locks.h>

#समावेश "mutex-debug.h"

/*
 * Must be called with lock->रुको_lock held.
 */
व्योम debug_mutex_lock_common(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer)
अणु
	स_रखो(रुकोer, MUTEX_DEBUG_INIT, माप(*रुकोer));
	रुकोer->magic = रुकोer;
	INIT_LIST_HEAD(&रुकोer->list);
पूर्ण

व्योम debug_mutex_wake_रुकोer(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer)
अणु
	lockdep_निश्चित_held(&lock->रुको_lock);
	DEBUG_LOCKS_WARN_ON(list_empty(&lock->रुको_list));
	DEBUG_LOCKS_WARN_ON(रुकोer->magic != रुकोer);
	DEBUG_LOCKS_WARN_ON(list_empty(&रुकोer->list));
पूर्ण

व्योम debug_mutex_मुक्त_रुकोer(काष्ठा mutex_रुकोer *रुकोer)
अणु
	DEBUG_LOCKS_WARN_ON(!list_empty(&रुकोer->list));
	स_रखो(रुकोer, MUTEX_DEBUG_FREE, माप(*रुकोer));
पूर्ण

व्योम debug_mutex_add_रुकोer(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer,
			    काष्ठा task_काष्ठा *task)
अणु
	lockdep_निश्चित_held(&lock->रुको_lock);

	/* Mark the current thपढ़ो as blocked on the lock: */
	task->blocked_on = रुकोer;
पूर्ण

व्योम debug_mutex_हटाओ_रुकोer(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer,
			 काष्ठा task_काष्ठा *task)
अणु
	DEBUG_LOCKS_WARN_ON(list_empty(&रुकोer->list));
	DEBUG_LOCKS_WARN_ON(रुकोer->task != task);
	DEBUG_LOCKS_WARN_ON(task->blocked_on != रुकोer);
	task->blocked_on = शून्य;

	INIT_LIST_HEAD(&रुकोer->list);
	रुकोer->task = शून्य;
पूर्ण

व्योम debug_mutex_unlock(काष्ठा mutex *lock)
अणु
	अगर (likely(debug_locks)) अणु
		DEBUG_LOCKS_WARN_ON(lock->magic != lock);
		DEBUG_LOCKS_WARN_ON(!lock->रुको_list.prev && !lock->रुको_list.next);
	पूर्ण
पूर्ण

व्योम debug_mutex_init(काष्ठा mutex *lock, स्थिर अक्षर *name,
		      काष्ठा lock_class_key *key)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	/*
	 * Make sure we are not reinitializing a held lock:
	 */
	debug_check_no_locks_मुक्तd((व्योम *)lock, माप(*lock));
	lockdep_init_map_रुको(&lock->dep_map, name, key, 0, LD_WAIT_SLEEP);
#पूर्ण_अगर
	lock->magic = lock;
पूर्ण

/***
 * mutex_destroy - mark a mutex unusable
 * @lock: the mutex to be destroyed
 *
 * This function marks the mutex uninitialized, and any subsequent
 * use of the mutex is क्रमbidden. The mutex must not be locked when
 * this function is called.
 */
व्योम mutex_destroy(काष्ठा mutex *lock)
अणु
	DEBUG_LOCKS_WARN_ON(mutex_is_locked(lock));
	lock->magic = शून्य;
पूर्ण

EXPORT_SYMBOL_GPL(mutex_destroy);
