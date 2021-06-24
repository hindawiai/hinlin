<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "include/asm-i386/spinlock.h"
 */

#अगर_अघोषित __ASM_SPINLOCK_H
#घोषणा __ASM_SPINLOCK_H

#समावेश <linux/smp.h>
#समावेश <यंत्र/atomic_ops.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/alternative.h>

#घोषणा SPINLOCK_LOCKVAL (S390_lowcore.spinlock_lockval)

बाह्य पूर्णांक spin_retry;

bool arch_vcpu_is_preempted(पूर्णांक cpu);

#घोषणा vcpu_is_preempted arch_vcpu_is_preempted

/*
 * Simple spin lock operations.  There are two variants, one clears IRQ's
 * on the local processor, one करोes not.
 *
 * We make no fairness assumptions. They have a cost.
 *
 * (the type definitions are in यंत्र/spinlock_types.h)
 */

व्योम arch_spin_relax(arch_spinlock_t *lock);
#घोषणा arch_spin_relax	arch_spin_relax

व्योम arch_spin_lock_रुको(arch_spinlock_t *);
पूर्णांक arch_spin_trylock_retry(arch_spinlock_t *);
व्योम arch_spin_lock_setup(पूर्णांक cpu);

अटल अंतरभूत u32 arch_spin_lockval(पूर्णांक cpu)
अणु
	वापस cpu + 1;
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_value_unlocked(arch_spinlock_t lock)
अणु
	वापस lock.lock == 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_is_locked(arch_spinlock_t *lp)
अणु
	वापस READ_ONCE(lp->lock) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock_once(arch_spinlock_t *lp)
अणु
	barrier();
	वापस likely(__atomic_cmpxchg_bool(&lp->lock, 0, SPINLOCK_LOCKVAL));
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lp)
अणु
	अगर (!arch_spin_trylock_once(lp))
		arch_spin_lock_रुको(lp);
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock_flags(arch_spinlock_t *lp,
					अचिन्हित दीर्घ flags)
अणु
	अगर (!arch_spin_trylock_once(lp))
		arch_spin_lock_रुको(lp);
पूर्ण
#घोषणा arch_spin_lock_flags	arch_spin_lock_flags

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lp)
अणु
	अगर (!arch_spin_trylock_once(lp))
		वापस arch_spin_trylock_retry(lp);
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lp)
अणु
	typecheck(पूर्णांक, lp->lock);
	यंत्र_अंतरभूत अस्थिर(
		ALTERNATIVE("", ".long 0xb2fa0070", 49)	/* NIAI 7 */
		"	sth	%1,%0\n"
		: "=R" (((अचिन्हित लघु *) &lp->lock)[1])
		: "d" (0) : "cc", "memory");
पूर्ण

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers
 * but only one ग_लिखोr.
 *
 * NOTE! it is quite common to have पढ़ोers in पूर्णांकerrupts
 * but no पूर्णांकerrupt ग_लिखोrs. For those circumstances we
 * can "mix" irq-safe locks - any ग_लिखोr needs to get a
 * irq-safe ग_लिखो-lock, but पढ़ोers can get non-irqsafe
 * पढ़ो-locks.
 */

#घोषणा arch_पढ़ो_relax(rw) barrier()
#घोषणा arch_ग_लिखो_relax(rw) barrier()

व्योम arch_पढ़ो_lock_रुको(arch_rwlock_t *lp);
व्योम arch_ग_लिखो_lock_रुको(arch_rwlock_t *lp);

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	पूर्णांक old;

	old = __atomic_add(1, &rw->cnts);
	अगर (old & 0xffff0000)
		arch_पढ़ो_lock_रुको(rw);
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	__atomic_add_स्थिर_barrier(-1, &rw->cnts);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	अगर (!__atomic_cmpxchg_bool(&rw->cnts, 0, 0x30000))
		arch_ग_लिखो_lock_रुको(rw);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	__atomic_add_barrier(-0x30000, &rw->cnts);
पूर्ण


अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	पूर्णांक old;

	old = READ_ONCE(rw->cnts);
	वापस (!(old & 0xffff0000) &&
		__atomic_cmpxchg_bool(&rw->cnts, old, old + 1));
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	पूर्णांक old;

	old = READ_ONCE(rw->cnts);
	वापस !old && __atomic_cmpxchg_bool(&rw->cnts, 0, 0x30000);
पूर्ण

#पूर्ण_अगर /* __ASM_SPINLOCK_H */
