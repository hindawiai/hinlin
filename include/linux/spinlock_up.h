<शैली गुरु>
#अगर_अघोषित __LINUX_SPINLOCK_UP_H
#घोषणा __LINUX_SPINLOCK_UP_H

#अगर_अघोषित __LINUX_SPINLOCK_H
# error "please don't include this file directly"
#पूर्ण_अगर

#समावेश <यंत्र/processor.h>	/* क्रम cpu_relax() */
#समावेश <यंत्र/barrier.h>

/*
 * include/linux/spinlock_up.h - UP-debug version of spinlocks.
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 *
 * In the debug हाल, 1 means unlocked, 0 means locked. (the values
 * are inverted, to catch initialization bugs)
 *
 * No atomicity anywhere, we are on UP. However, we still need
 * the compiler barriers, because we करो not want the compiler to
 * move potentially faulting inकाष्ठाions (notably user accesses)
 * पूर्णांकo the locked sequence, resulting in non-atomic execution.
 */

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
#घोषणा arch_spin_is_locked(x)		((x)->slock == 0)

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	lock->slock = 0;
	barrier();
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	अक्षर oldval = lock->slock;

	lock->slock = 0;
	barrier();

	वापस oldval > 0;
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	barrier();
	lock->slock = 1;
पूर्ण

/*
 * Read-ग_लिखो spinlocks. No debug version.
 */
#घोषणा arch_पढ़ो_lock(lock)		करो अणु barrier(); (व्योम)(lock); पूर्ण जबतक (0)
#घोषणा arch_ग_लिखो_lock(lock)		करो अणु barrier(); (व्योम)(lock); पूर्ण जबतक (0)
#घोषणा arch_पढ़ो_trylock(lock)	(अणु barrier(); (व्योम)(lock); 1; पूर्ण)
#घोषणा arch_ग_लिखो_trylock(lock)	(अणु barrier(); (व्योम)(lock); 1; पूर्ण)
#घोषणा arch_पढ़ो_unlock(lock)		करो अणु barrier(); (व्योम)(lock); पूर्ण जबतक (0)
#घोषणा arch_ग_लिखो_unlock(lock)	करो अणु barrier(); (व्योम)(lock); पूर्ण जबतक (0)

#अन्यथा /* DEBUG_SPINLOCK */
#घोषणा arch_spin_is_locked(lock)	((व्योम)(lock), 0)
/* क्रम sched/core.c and kernel_lock.c: */
# define arch_spin_lock(lock)		करो अणु barrier(); (व्योम)(lock); पूर्ण जबतक (0)
# define arch_spin_lock_flags(lock, flags)	करो अणु barrier(); (व्योम)(lock); पूर्ण जबतक (0)
# define arch_spin_unlock(lock)	करो अणु barrier(); (व्योम)(lock); पूर्ण जबतक (0)
# define arch_spin_trylock(lock)	(अणु barrier(); (व्योम)(lock); 1; पूर्ण)
#पूर्ण_अगर /* DEBUG_SPINLOCK */

#घोषणा arch_spin_is_contended(lock)	(((व्योम)(lock), 0))

#पूर्ण_अगर /* __LINUX_SPINLOCK_UP_H */
