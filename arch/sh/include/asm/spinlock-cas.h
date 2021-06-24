<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/spinlock-cas.h
 *
 * Copyright (C) 2015 SEI
 */
#अगर_अघोषित __ASM_SH_SPINLOCK_CAS_H
#घोषणा __ASM_SH_SPINLOCK_CAS_H

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>

अटल अंतरभूत अचिन्हित __sl_cas(अस्थिर अचिन्हित *p, अचिन्हित old, अचिन्हित new)
अणु
	__यंत्र__ __अस्थिर__("cas.l %1,%0,@r0"
		: "+r"(new)
		: "r"(old), "z"(p)
		: "t", "memory" );
	वापस new;
पूर्ण

/*
 * Your basic SMP spinlocks, allowing only a single CPU anywhere
 */

#घोषणा arch_spin_is_locked(x)		((x)->lock <= 0)

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	जबतक (!__sl_cas(&lock->lock, 1, 0));
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	__sl_cas(&lock->lock, 0, 1);
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	वापस __sl_cas(&lock->lock, 1, 0);
पूर्ण

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers but only one ग_लिखोr.
 *
 * NOTE! it is quite common to have पढ़ोers in पूर्णांकerrupts but no पूर्णांकerrupt
 * ग_लिखोrs. For those circumstances we can "mix" irq-safe locks - any ग_लिखोr
 * needs to get a irq-safe ग_लिखो-lock, but पढ़ोers can get non-irqsafe
 * पढ़ो-locks.
 */

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	अचिन्हित old;
	करो old = rw->lock;
	जबतक (!old || __sl_cas(&rw->lock, old, old-1) != old);
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित old;
	करो old = rw->lock;
	जबतक (__sl_cas(&rw->lock, old, old+1) != old);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	जबतक (__sl_cas(&rw->lock, RW_LOCK_BIAS, 0) != RW_LOCK_BIAS);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	__sl_cas(&rw->lock, 0, RW_LOCK_BIAS);
पूर्ण

अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित old;
	करो old = rw->lock;
	जबतक (old && __sl_cas(&rw->lock, old, old-1) != old);
	वापस !!old;
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	वापस __sl_cas(&rw->lock, RW_LOCK_BIAS, 0) == RW_LOCK_BIAS;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_SPINLOCK_CAS_H */
