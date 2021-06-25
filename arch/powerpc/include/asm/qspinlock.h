<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_QSPINLOCK_H
#घोषणा _ASM_POWERPC_QSPINLOCK_H

#समावेश <यंत्र-generic/qspinlock_types.h>
#समावेश <यंत्र/paravirt.h>

#घोषणा _Q_PENDING_LOOPS	(1 << 9) /* not tuned */

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
बाह्य व्योम native_queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val);
बाह्य व्योम __pv_queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val);
बाह्य व्योम __pv_queued_spin_unlock(काष्ठा qspinlock *lock);

अटल __always_अंतरभूत व्योम queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val)
अणु
	अगर (!is_shared_processor())
		native_queued_spin_lock_slowpath(lock, val);
	अन्यथा
		__pv_queued_spin_lock_slowpath(lock, val);
पूर्ण

#घोषणा queued_spin_unlock queued_spin_unlock
अटल अंतरभूत व्योम queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	अगर (!is_shared_processor())
		smp_store_release(&lock->locked, 0);
	अन्यथा
		__pv_queued_spin_unlock(lock);
पूर्ण

#अन्यथा
बाह्य व्योम queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val);
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम queued_spin_lock(काष्ठा qspinlock *lock)
अणु
	u32 val = 0;

	अगर (likely(atomic_try_cmpxchg_lock(&lock->val, &val, _Q_LOCKED_VAL)))
		वापस;

	queued_spin_lock_slowpath(lock, val);
पूर्ण
#घोषणा queued_spin_lock queued_spin_lock

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
#घोषणा SPIN_THRESHOLD (1<<15) /* not tuned */

अटल __always_अंतरभूत व्योम pv_रुको(u8 *ptr, u8 val)
अणु
	अगर (*ptr != val)
		वापस;
	yield_to_any();
	/*
	 * We could pass in a CPU here अगर रुकोing in the queue and yield to
	 * the previous CPU in the queue.
	 */
पूर्ण

अटल __always_अंतरभूत व्योम pv_kick(पूर्णांक cpu)
अणु
	prod_cpu(cpu);
पूर्ण

बाह्य व्योम __pv_init_lock_hash(व्योम);

अटल अंतरभूत व्योम pv_spinlocks_init(व्योम)
अणु
	__pv_init_lock_hash();
पूर्ण

#पूर्ण_अगर

/*
 * Queued spinlocks rely heavily on smp_cond_load_relaxed() to busy-रुको,
 * which was found to have perक्रमmance problems अगर implemented with
 * the preferred spin_begin()/spin_end() SMT priority pattern. Use the
 * generic version instead.
 */

#समावेश <यंत्र-generic/qspinlock.h>

#पूर्ण_अगर /* _ASM_POWERPC_QSPINLOCK_H */
