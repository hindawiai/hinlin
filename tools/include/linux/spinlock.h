<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SPINLOCK_H_
#घोषणा __LINUX_SPINLOCK_H_

#समावेश <pthपढ़ो.h>
#समावेश <stdbool.h>

#घोषणा spinlock_t		pthपढ़ो_mutex_t
#घोषणा DEFINE_SPINLOCK(x)	pthपढ़ो_mutex_t x = PTHREAD_MUTEX_INITIALIZER
#घोषणा __SPIN_LOCK_UNLOCKED(x)	(pthपढ़ो_mutex_t)PTHREAD_MUTEX_INITIALIZER
#घोषणा spin_lock_init(x)	pthपढ़ो_mutex_init(x, शून्य)

#घोषणा spin_lock(x)			pthपढ़ो_mutex_lock(x)
#घोषणा spin_unlock(x)			pthपढ़ो_mutex_unlock(x)
#घोषणा spin_lock_bh(x)			pthपढ़ो_mutex_lock(x)
#घोषणा spin_unlock_bh(x)		pthपढ़ो_mutex_unlock(x)
#घोषणा spin_lock_irq(x)		pthपढ़ो_mutex_lock(x)
#घोषणा spin_unlock_irq(x)		pthपढ़ो_mutex_unlock(x)
#घोषणा spin_lock_irqsave(x, f)		(व्योम)f, pthपढ़ो_mutex_lock(x)
#घोषणा spin_unlock_irqrestore(x, f)	(व्योम)f, pthपढ़ो_mutex_unlock(x)

#घोषणा arch_spinlock_t pthपढ़ो_mutex_t
#घोषणा __ARCH_SPIN_LOCK_UNLOCKED PTHREAD_MUTEX_INITIALIZER

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *mutex)
अणु
	pthपढ़ो_mutex_lock(mutex);
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *mutex)
अणु
	pthपढ़ो_mutex_unlock(mutex);
पूर्ण

अटल अंतरभूत bool arch_spin_is_locked(arch_spinlock_t *mutex)
अणु
	वापस true;
पूर्ण

#समावेश <linux/lockdep.h>

#पूर्ण_अगर
