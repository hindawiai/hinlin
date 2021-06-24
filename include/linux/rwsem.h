<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* rwsem.h: R/W semaphores, खुला पूर्णांकerface
 *
 * Written by David Howells (dhowells@redhat.com).
 * Derived from यंत्र-i386/semaphore.h
 */

#अगर_अघोषित _LINUX_RWSEM_H
#घोषणा _LINUX_RWSEM_H

#समावेश <linux/linkage.h>

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/err.h>
#अगर_घोषित CONFIG_RWSEM_SPIN_ON_OWNER
#समावेश <linux/osq_lock.h>
#पूर्ण_अगर

/*
 * For an uncontended rwsem, count and owner are the only fields a task
 * needs to touch when acquiring the rwsem. So they are put next to each
 * other to increase the chance that they will share the same cacheline.
 *
 * In a contended rwsem, the owner is likely the most frequently accessed
 * field in the काष्ठाure as the optimistic रुकोer that holds the osq lock
 * will spin on owner. For an embedded rwsem, other hot fields in the
 * containing काष्ठाure should be moved further away from the rwsem to
 * reduce the chance that they will share the same cacheline causing
 * cacheline bouncing problem.
 */
काष्ठा rw_semaphore अणु
	atomic_दीर्घ_t count;
	/*
	 * Write owner or one of the पढ़ो owners as well flags regarding
	 * the current state of the rwsem. Can be used as a speculative
	 * check to see अगर the ग_लिखो owner is running on the cpu.
	 */
	atomic_दीर्घ_t owner;
#अगर_घोषित CONFIG_RWSEM_SPIN_ON_OWNER
	काष्ठा optimistic_spin_queue osq; /* spinner MCS lock */
#पूर्ण_अगर
	raw_spinlock_t रुको_lock;
	काष्ठा list_head रुको_list;
#अगर_घोषित CONFIG_DEBUG_RWSEMS
	व्योम *magic;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	dep_map;
#पूर्ण_अगर
पूर्ण;

/* In all implementations count != 0 means locked */
अटल अंतरभूत पूर्णांक rwsem_is_locked(काष्ठा rw_semaphore *sem)
अणु
	वापस atomic_दीर्घ_पढ़ो(&sem->count) != 0;
पूर्ण

#घोषणा RWSEM_UNLOCKED_VALUE		0L
#घोषणा __RWSEM_COUNT_INIT(name)	.count = ATOMIC_LONG_INIT(RWSEM_UNLOCKED_VALUE)

/* Common initializer macros and functions */

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define __RWSEM_DEP_MAP_INIT(lockname)			\
	.dep_map = अणु					\
		.name = #lockname,			\
		.रुको_type_inner = LD_WAIT_SLEEP,	\
	पूर्ण,
#अन्यथा
# define __RWSEM_DEP_MAP_INIT(lockname)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_RWSEMS
# define __RWSEM_DEBUG_INIT(lockname) .magic = &lockname,
#अन्यथा
# define __RWSEM_DEBUG_INIT(lockname)
#पूर्ण_अगर

#अगर_घोषित CONFIG_RWSEM_SPIN_ON_OWNER
#घोषणा __RWSEM_OPT_INIT(lockname) .osq = OSQ_LOCK_UNLOCKED,
#अन्यथा
#घोषणा __RWSEM_OPT_INIT(lockname)
#पूर्ण_अगर

#घोषणा __RWSEM_INITIALIZER(name)				\
	अणु __RWSEM_COUNT_INIT(name),				\
	  .owner = ATOMIC_LONG_INIT(0),				\
	  __RWSEM_OPT_INIT(name)				\
	  .रुको_lock = __RAW_SPIN_LOCK_UNLOCKED(name.रुको_lock),\
	  .रुको_list = LIST_HEAD_INIT((name).रुको_list),	\
	  __RWSEM_DEBUG_INIT(name)				\
	  __RWSEM_DEP_MAP_INIT(name) पूर्ण

#घोषणा DECLARE_RWSEM(name) \
	काष्ठा rw_semaphore name = __RWSEM_INITIALIZER(name)

बाह्य व्योम __init_rwsem(काष्ठा rw_semaphore *sem, स्थिर अक्षर *name,
			 काष्ठा lock_class_key *key);

#घोषणा init_rwsem(sem)						\
करो अणु								\
	अटल काष्ठा lock_class_key __key;			\
								\
	__init_rwsem((sem), #sem, &__key);			\
पूर्ण जबतक (0)

/*
 * This is the same regardless of which rwsem implementation that is being used.
 * It is just a heuristic meant to be called by somebody alपढ़ोy holding the
 * rwsem to see अगर somebody from an incompatible type is wanting access to the
 * lock.
 */
अटल अंतरभूत पूर्णांक rwsem_is_contended(काष्ठा rw_semaphore *sem)
अणु
	वापस !list_empty(&sem->रुको_list);
पूर्ण

/*
 * lock क्रम पढ़ोing
 */
बाह्य व्योम करोwn_पढ़ो(काष्ठा rw_semaphore *sem);
बाह्य पूर्णांक __must_check करोwn_पढ़ो_पूर्णांकerruptible(काष्ठा rw_semaphore *sem);
बाह्य पूर्णांक __must_check करोwn_पढ़ो_समाप्तable(काष्ठा rw_semaphore *sem);

/*
 * trylock क्रम पढ़ोing -- वापसs 1 अगर successful, 0 अगर contention
 */
बाह्य पूर्णांक करोwn_पढ़ो_trylock(काष्ठा rw_semaphore *sem);

/*
 * lock क्रम writing
 */
बाह्य व्योम करोwn_ग_लिखो(काष्ठा rw_semaphore *sem);
बाह्य पूर्णांक __must_check करोwn_ग_लिखो_समाप्तable(काष्ठा rw_semaphore *sem);

/*
 * trylock क्रम writing -- वापसs 1 अगर successful, 0 अगर contention
 */
बाह्य पूर्णांक करोwn_ग_लिखो_trylock(काष्ठा rw_semaphore *sem);

/*
 * release a पढ़ो lock
 */
बाह्य व्योम up_पढ़ो(काष्ठा rw_semaphore *sem);

/*
 * release a ग_लिखो lock
 */
बाह्य व्योम up_ग_लिखो(काष्ठा rw_semaphore *sem);

/*
 * करोwngrade ग_लिखो lock to पढ़ो lock
 */
बाह्य व्योम करोwngrade_ग_लिखो(काष्ठा rw_semaphore *sem);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
/*
 * nested locking. NOTE: rwsems are not allowed to recurse
 * (which occurs अगर the same task tries to acquire the same
 * lock instance multiple बार), but multiple locks of the
 * same lock class might be taken, अगर the order of the locks
 * is always the same. This ordering rule can be expressed
 * to lockdep via the _nested() APIs, but क्रमागतerating the
 * subclasses that are used. (If the nesting relationship is
 * अटल then another method क्रम expressing nested locking is
 * the explicit definition of lock class keys and the use of
 * lockdep_set_class() at lock initialization समय.
 * See Documentation/locking/lockdep-design.rst क्रम more details.)
 */
बाह्य व्योम करोwn_पढ़ो_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass);
बाह्य पूर्णांक __must_check करोwn_पढ़ो_समाप्तable_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass);
बाह्य व्योम करोwn_ग_लिखो_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass);
बाह्य पूर्णांक करोwn_ग_लिखो_समाप्तable_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass);
बाह्य व्योम _करोwn_ग_लिखो_nest_lock(काष्ठा rw_semaphore *sem, काष्ठा lockdep_map *nest_lock);

# define करोwn_ग_लिखो_nest_lock(sem, nest_lock)			\
करो अणु								\
	typecheck(काष्ठा lockdep_map *, &(nest_lock)->dep_map);	\
	_करोwn_ग_लिखो_nest_lock(sem, &(nest_lock)->dep_map);	\
पूर्ण जबतक (0);

/*
 * Take/release a lock when not the owner will release it.
 *
 * [ This API should be aव्योमed as much as possible - the
 *   proper असलtraction क्रम this हाल is completions. ]
 */
बाह्य व्योम करोwn_पढ़ो_non_owner(काष्ठा rw_semaphore *sem);
बाह्य व्योम up_पढ़ो_non_owner(काष्ठा rw_semaphore *sem);
#अन्यथा
# define करोwn_पढ़ो_nested(sem, subclass)		करोwn_पढ़ो(sem)
# define करोwn_पढ़ो_समाप्तable_nested(sem, subclass)	करोwn_पढ़ो_समाप्तable(sem)
# define करोwn_ग_लिखो_nest_lock(sem, nest_lock)	करोwn_ग_लिखो(sem)
# define करोwn_ग_लिखो_nested(sem, subclass)	करोwn_ग_लिखो(sem)
# define करोwn_ग_लिखो_समाप्तable_nested(sem, subclass)	करोwn_ग_लिखो_समाप्तable(sem)
# define करोwn_पढ़ो_non_owner(sem)		करोwn_पढ़ो(sem)
# define up_पढ़ो_non_owner(sem)			up_पढ़ो(sem)
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_RWSEM_H */
