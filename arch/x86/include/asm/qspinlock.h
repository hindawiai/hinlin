<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_QSPINLOCK_H
#घोषणा _ASM_X86_QSPINLOCK_H

#समावेश <linux/jump_label.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र-generic/qspinlock_types.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/rmwcc.h>

#घोषणा _Q_PENDING_LOOPS	(1 << 9)

#घोषणा queued_fetch_set_pending_acquire queued_fetch_set_pending_acquire
अटल __always_अंतरभूत u32 queued_fetch_set_pending_acquire(काष्ठा qspinlock *lock)
अणु
	u32 val;

	/*
	 * We can't use GEN_BINARY_RMWcc() inside an अगर() sपंचांगt because यंत्र जाओ
	 * and CONFIG_PROखाता_ALL_BRANCHES=y results in a label inside a
	 * statement expression, which GCC करोesn't like.
	 */
	val = GEN_BINARY_RMWcc(LOCK_PREFIX "btsl", lock->val.counter, c,
			       "I", _Q_PENDING_OFFSET) * _Q_PENDING_VAL;
	val |= atomic_पढ़ो(&lock->val) & ~_Q_PENDING_MASK;

	वापस val;
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
बाह्य व्योम native_queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val);
बाह्य व्योम __pv_init_lock_hash(व्योम);
बाह्य व्योम __pv_queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val);
बाह्य व्योम __raw_callee_save___pv_queued_spin_unlock(काष्ठा qspinlock *lock);
बाह्य bool nopvspin;

#घोषणा	queued_spin_unlock queued_spin_unlock
/**
 * queued_spin_unlock - release a queued spinlock
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 *
 * A smp_store_release() on the least-signअगरicant byte.
 */
अटल अंतरभूत व्योम native_queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	smp_store_release(&lock->locked, 0);
पूर्ण

अटल अंतरभूत व्योम queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val)
अणु
	pv_queued_spin_lock_slowpath(lock, val);
पूर्ण

अटल अंतरभूत व्योम queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	pv_queued_spin_unlock(lock);
पूर्ण

#घोषणा vcpu_is_preempted vcpu_is_preempted
अटल अंतरभूत bool vcpu_is_preempted(दीर्घ cpu)
अणु
	वापस pv_vcpu_is_preempted(cpu);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PARAVIRT
/*
 * virt_spin_lock_key - enables (by शेष) the virt_spin_lock() hijack.
 *
 * Native (and PV wanting native due to vCPU pinning) should disable this key.
 * It is करोne in this backwards fashion to only have a single direction change,
 * which हटाओs ordering between native_pv_spin_init() and HV setup.
 */
DECLARE_STATIC_KEY_TRUE(virt_spin_lock_key);

व्योम native_pv_lock_init(व्योम) __init;

/*
 * Shortcut क्रम the queued_spin_lock_slowpath() function that allows
 * virt to hijack it.
 *
 * Returns:
 *   true - lock has been negotiated, all करोne;
 *   false - queued_spin_lock_slowpath() will करो its thing.
 */
#घोषणा virt_spin_lock virt_spin_lock
अटल अंतरभूत bool virt_spin_lock(काष्ठा qspinlock *lock)
अणु
	अगर (!अटल_branch_likely(&virt_spin_lock_key))
		वापस false;

	/*
	 * On hypervisors without PARAVIRT_SPINLOCKS support we fall
	 * back to a Test-and-Set spinlock, because fair locks have
	 * horrible lock 'holder' preemption issues.
	 */

	करो अणु
		जबतक (atomic_पढ़ो(&lock->val) != 0)
			cpu_relax();
	पूर्ण जबतक (atomic_cmpxchg(&lock->val, 0, _Q_LOCKED_VAL) != 0);

	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम native_pv_lock_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PARAVIRT */

#समावेश <यंत्र-generic/qspinlock.h>

#पूर्ण_अगर /* _ASM_X86_QSPINLOCK_H */
