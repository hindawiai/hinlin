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
 * This file contains the खुला data काष्ठाure and API definitions.
 */

#अगर_अघोषित __LINUX_RT_MUTEX_H
#घोषणा __LINUX_RT_MUTEX_H

#समावेश <linux/linkage.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock_types.h>

बाह्य पूर्णांक max_lock_depth; /* क्रम sysctl */

/**
 * The rt_mutex काष्ठाure
 *
 * @रुको_lock:	spinlock to protect the काष्ठाure
 * @रुकोers:	rbtree root to enqueue रुकोers in priority order;
 *              caches top-रुकोer (lefपंचांगost node).
 * @owner:	the mutex owner
 */
काष्ठा rt_mutex अणु
	raw_spinlock_t		रुको_lock;
	काष्ठा rb_root_cached   रुकोers;
	काष्ठा task_काष्ठा	*owner;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	dep_map;
#पूर्ण_अगर
पूर्ण;

काष्ठा rt_mutex_रुकोer;
काष्ठा hrसमयr_sleeper;

#अगर_घोषित CONFIG_DEBUG_RT_MUTEXES
बाह्य व्योम rt_mutex_debug_task_मुक्त(काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत व्योम rt_mutex_debug_task_मुक्त(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
#पूर्ण_अगर

#घोषणा rt_mutex_init(mutex) \
करो अणु \
	अटल काष्ठा lock_class_key __key; \
	__rt_mutex_init(mutex, __func__, &__key); \
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
#घोषणा __DEP_MAP_RT_MUTEX_INITIALIZER(mutexname) \
	, .dep_map = अणु .name = #mutexname पूर्ण
#अन्यथा
#घोषणा __DEP_MAP_RT_MUTEX_INITIALIZER(mutexname)
#पूर्ण_अगर

#घोषणा __RT_MUTEX_INITIALIZER(mutexname) \
	अणु .रुको_lock = __RAW_SPIN_LOCK_UNLOCKED(mutexname.रुको_lock) \
	, .रुकोers = RB_ROOT_CACHED \
	, .owner = शून्य \
	__DEP_MAP_RT_MUTEX_INITIALIZER(mutexname)पूर्ण

#घोषणा DEFINE_RT_MUTEX(mutexname) \
	काष्ठा rt_mutex mutexname = __RT_MUTEX_INITIALIZER(mutexname)

/**
 * rt_mutex_is_locked - is the mutex locked
 * @lock: the mutex to be queried
 *
 * Returns 1 अगर the mutex is locked, 0 अगर unlocked.
 */
अटल अंतरभूत पूर्णांक rt_mutex_is_locked(काष्ठा rt_mutex *lock)
अणु
	वापस lock->owner != शून्य;
पूर्ण

बाह्य व्योम __rt_mutex_init(काष्ठा rt_mutex *lock, स्थिर अक्षर *name, काष्ठा lock_class_key *key);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
बाह्य व्योम rt_mutex_lock_nested(काष्ठा rt_mutex *lock, अचिन्हित पूर्णांक subclass);
#घोषणा rt_mutex_lock(lock) rt_mutex_lock_nested(lock, 0)
#अन्यथा
बाह्य व्योम rt_mutex_lock(काष्ठा rt_mutex *lock);
#घोषणा rt_mutex_lock_nested(lock, subclass) rt_mutex_lock(lock)
#पूर्ण_अगर

बाह्य पूर्णांक rt_mutex_lock_पूर्णांकerruptible(काष्ठा rt_mutex *lock);
बाह्य पूर्णांक rt_mutex_trylock(काष्ठा rt_mutex *lock);

बाह्य व्योम rt_mutex_unlock(काष्ठा rt_mutex *lock);

#पूर्ण_अगर
