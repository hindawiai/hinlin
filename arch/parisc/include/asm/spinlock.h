<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SPINLOCK_H
#घोषणा __ASM_SPINLOCK_H

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/ldcw.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/spinlock_types.h>

अटल अंतरभूत पूर्णांक arch_spin_is_locked(arch_spinlock_t *x)
अणु
	अस्थिर अचिन्हित पूर्णांक *a = __ldcw_align(x);
	वापस READ_ONCE(*a) == 0;
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *x)
अणु
	अस्थिर अचिन्हित पूर्णांक *a;

	a = __ldcw_align(x);
	जबतक (__ldcw(a) == 0)
		जबतक (*a == 0)
			जारी;
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock_flags(arch_spinlock_t *x,
					अचिन्हित दीर्घ flags)
अणु
	अस्थिर अचिन्हित पूर्णांक *a;

	a = __ldcw_align(x);
	जबतक (__ldcw(a) == 0)
		जबतक (*a == 0)
			अगर (flags & PSW_SM_I) अणु
				local_irq_enable();
				local_irq_disable();
			पूर्ण
पूर्ण
#घोषणा arch_spin_lock_flags arch_spin_lock_flags

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *x)
अणु
	अस्थिर अचिन्हित पूर्णांक *a;

	a = __ldcw_align(x);
	/* Release with ordered store. */
	__यंत्र__ __अस्थिर__("stw,ma %0,0(%1)" : : "r"(1), "r"(a) : "memory");
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *x)
अणु
	अस्थिर अचिन्हित पूर्णांक *a;

	a = __ldcw_align(x);
	वापस __ldcw(a) != 0;
पूर्ण

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers but only one ग_लिखोr.
 * Unfair locking as Writers could be starved indefinitely by Reader(s)
 *
 * The spinlock itself is contained in @counter and access to it is
 * serialized with @lock_mutex.
 */

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));

	/*
	 * zero means ग_लिखोr holds the lock exclusively, deny Reader.
	 * Otherwise grant lock to first/subseq पढ़ोer
	 */
	अगर (rw->counter > 0) अणु
		rw->counter--;
		ret = 1;
	पूर्ण

	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);

	वापस ret;
पूर्ण

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));

	/*
	 * If पढ़ोer(s) hold lock (lock < __ARCH_RW_LOCK_UNLOCKED__),
	 * deny ग_लिखोr. Otherwise अगर unlocked grant to ग_लिखोr
	 * Hence the claim that Linux rwlocks are unfair to ग_लिखोrs.
	 * (can be starved क्रम an indefinite समय by पढ़ोers).
	 */
	अगर (rw->counter == __ARCH_RW_LOCK_UNLOCKED__) अणु
		rw->counter = 0;
		ret = 1;
	पूर्ण
	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	जबतक (!arch_पढ़ो_trylock(rw))
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	जबतक (!arch_ग_लिखो_trylock(rw))
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));
	rw->counter++;
	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));
	rw->counter = __ARCH_RW_LOCK_UNLOCKED__;
	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर /* __ASM_SPINLOCK_H */
