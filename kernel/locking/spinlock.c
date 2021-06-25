<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (2004) Linus Torvalds
 *
 * Author: Zwane Mwaikambo <zwane@fsmद_असल.com>
 *
 * Copyright (2004, 2005) Ingo Molnar
 *
 * This file contains the spinlock/rwlock implementations क्रम the
 * SMP and the DEBUG_SPINLOCK हालs. (UP-nondebug अंतरभूतs them)
 *
 * Note that some architectures have special knowledge about the
 * stack frames of these functions in their profile_pc. If you
 * change anything signअगरicant here that could change the stack
 * frame contact the architecture मुख्यtainers.
 */

#समावेश <linux/linkage.h>
#समावेश <linux/preempt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/export.h>

#अगर_घोषित CONFIG_MMIOWB
#अगर_अघोषित arch_mmiowb_state
DEFINE_PER_CPU(काष्ठा mmiowb_state, __mmiowb_state);
EXPORT_PER_CPU_SYMBOL(__mmiowb_state);
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * If lockdep is enabled then we use the non-preemption spin-ops
 * even on CONFIG_PREEMPT, because lockdep assumes that पूर्णांकerrupts are
 * not re-enabled during lock-acquire (which the preempt-spin-ops करो):
 */
#अगर !defined(CONFIG_GENERIC_LOCKBREAK) || defined(CONFIG_DEBUG_LOCK_ALLOC)
/*
 * The __lock_function अंतरभूतs are taken from
 * spinlock : include/linux/spinlock_api_smp.h
 * rwlock   : include/linux/rwlock_api_smp.h
 */
#अन्यथा

/*
 * Some architectures can relax in favour of the CPU owning the lock.
 */
#अगर_अघोषित arch_पढ़ो_relax
# define arch_पढ़ो_relax(l)	cpu_relax()
#पूर्ण_अगर
#अगर_अघोषित arch_ग_लिखो_relax
# define arch_ग_लिखो_relax(l)	cpu_relax()
#पूर्ण_अगर
#अगर_अघोषित arch_spin_relax
# define arch_spin_relax(l)	cpu_relax()
#पूर्ण_अगर

/*
 * We build the __lock_function अंतरभूतs here. They are too large क्रम
 * inlining all over the place, but here is only one user per function
 * which embeds them पूर्णांकo the calling _lock_function below.
 *
 * This could be a दीर्घ-held lock. We both prepare to spin क्रम a दीर्घ
 * समय (making _this_ CPU preemptible अगर possible), and we also संकेत
 * towards that other CPU that it should अवरोध the lock ASAP.
 */
#घोषणा BUILD_LOCK_OPS(op, locktype)					\
व्योम __lockfunc __raw_##op##_lock(locktype##_t *lock)			\
अणु									\
	क्रम (;;) अणु							\
		preempt_disable();					\
		अगर (likely(करो_raw_##op##_trylock(lock)))		\
			अवरोध;						\
		preempt_enable();					\
									\
		arch_##op##_relax(&lock->raw_lock);			\
	पूर्ण								\
पूर्ण									\
									\
अचिन्हित दीर्घ __lockfunc __raw_##op##_lock_irqsave(locktype##_t *lock)	\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	क्रम (;;) अणु							\
		preempt_disable();					\
		local_irq_save(flags);					\
		अगर (likely(करो_raw_##op##_trylock(lock)))		\
			अवरोध;						\
		local_irq_restore(flags);				\
		preempt_enable();					\
									\
		arch_##op##_relax(&lock->raw_lock);			\
	पूर्ण								\
									\
	वापस flags;							\
पूर्ण									\
									\
व्योम __lockfunc __raw_##op##_lock_irq(locktype##_t *lock)		\
अणु									\
	_raw_##op##_lock_irqsave(lock);					\
पूर्ण									\
									\
व्योम __lockfunc __raw_##op##_lock_bh(locktype##_t *lock)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	/*							*/	\
	/* Careful: we must exclude softirqs too, hence the	*/	\
	/* irq-disabling. We use the generic preemption-aware	*/	\
	/* function:						*/	\
	/**/								\
	flags = _raw_##op##_lock_irqsave(lock);				\
	local_bh_disable();						\
	local_irq_restore(flags);					\
पूर्ण									\

/*
 * Build preemption-मित्रly versions of the following
 * lock-spinning functions:
 *
 *         __[spin|पढ़ो|ग_लिखो]_lock()
 *         __[spin|पढ़ो|ग_लिखो]_lock_irq()
 *         __[spin|पढ़ो|ग_लिखो]_lock_irqsave()
 *         __[spin|पढ़ो|ग_लिखो]_lock_bh()
 */
BUILD_LOCK_OPS(spin, raw_spinlock);
BUILD_LOCK_OPS(पढ़ो, rwlock);
BUILD_LOCK_OPS(ग_लिखो, rwlock);

#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_TRYLOCK
पूर्णांक __lockfunc _raw_spin_trylock(raw_spinlock_t *lock)
अणु
	वापस __raw_spin_trylock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_trylock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_TRYLOCK_BH
पूर्णांक __lockfunc _raw_spin_trylock_bh(raw_spinlock_t *lock)
अणु
	वापस __raw_spin_trylock_bh(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_trylock_bh);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_LOCK
व्योम __lockfunc _raw_spin_lock(raw_spinlock_t *lock)
अणु
	__raw_spin_lock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_lock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_LOCK_IRQSAVE
अचिन्हित दीर्घ __lockfunc _raw_spin_lock_irqsave(raw_spinlock_t *lock)
अणु
	वापस __raw_spin_lock_irqsave(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_lock_irqsave);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_LOCK_IRQ
व्योम __lockfunc _raw_spin_lock_irq(raw_spinlock_t *lock)
अणु
	__raw_spin_lock_irq(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_lock_irq);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_LOCK_BH
व्योम __lockfunc _raw_spin_lock_bh(raw_spinlock_t *lock)
अणु
	__raw_spin_lock_bh(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_lock_bh);
#पूर्ण_अगर

#अगर_घोषित CONFIG_UNINLINE_SPIN_UNLOCK
व्योम __lockfunc _raw_spin_unlock(raw_spinlock_t *lock)
अणु
	__raw_spin_unlock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_unlock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_UNLOCK_IRQRESTORE
व्योम __lockfunc _raw_spin_unlock_irqrestore(raw_spinlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	__raw_spin_unlock_irqrestore(lock, flags);
पूर्ण
EXPORT_SYMBOL(_raw_spin_unlock_irqrestore);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_UNLOCK_IRQ
व्योम __lockfunc _raw_spin_unlock_irq(raw_spinlock_t *lock)
अणु
	__raw_spin_unlock_irq(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_unlock_irq);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_SPIN_UNLOCK_BH
व्योम __lockfunc _raw_spin_unlock_bh(raw_spinlock_t *lock)
अणु
	__raw_spin_unlock_bh(lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_unlock_bh);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_TRYLOCK
पूर्णांक __lockfunc _raw_पढ़ो_trylock(rwlock_t *lock)
अणु
	वापस __raw_पढ़ो_trylock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_trylock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_LOCK
व्योम __lockfunc _raw_पढ़ो_lock(rwlock_t *lock)
अणु
	__raw_पढ़ो_lock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_lock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_LOCK_IRQSAVE
अचिन्हित दीर्घ __lockfunc _raw_पढ़ो_lock_irqsave(rwlock_t *lock)
अणु
	वापस __raw_पढ़ो_lock_irqsave(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_lock_irqsave);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_LOCK_IRQ
व्योम __lockfunc _raw_पढ़ो_lock_irq(rwlock_t *lock)
अणु
	__raw_पढ़ो_lock_irq(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_lock_irq);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_LOCK_BH
व्योम __lockfunc _raw_पढ़ो_lock_bh(rwlock_t *lock)
अणु
	__raw_पढ़ो_lock_bh(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_lock_bh);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_UNLOCK
व्योम __lockfunc _raw_पढ़ो_unlock(rwlock_t *lock)
अणु
	__raw_पढ़ो_unlock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_unlock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_UNLOCK_IRQRESTORE
व्योम __lockfunc _raw_पढ़ो_unlock_irqrestore(rwlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	__raw_पढ़ो_unlock_irqrestore(lock, flags);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_unlock_irqrestore);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_UNLOCK_IRQ
व्योम __lockfunc _raw_पढ़ो_unlock_irq(rwlock_t *lock)
अणु
	__raw_पढ़ो_unlock_irq(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_unlock_irq);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_READ_UNLOCK_BH
व्योम __lockfunc _raw_पढ़ो_unlock_bh(rwlock_t *lock)
अणु
	__raw_पढ़ो_unlock_bh(lock);
पूर्ण
EXPORT_SYMBOL(_raw_पढ़ो_unlock_bh);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_TRYLOCK
पूर्णांक __lockfunc _raw_ग_लिखो_trylock(rwlock_t *lock)
अणु
	वापस __raw_ग_लिखो_trylock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_trylock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_LOCK
व्योम __lockfunc _raw_ग_लिखो_lock(rwlock_t *lock)
अणु
	__raw_ग_लिखो_lock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_lock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_LOCK_IRQSAVE
अचिन्हित दीर्घ __lockfunc _raw_ग_लिखो_lock_irqsave(rwlock_t *lock)
अणु
	वापस __raw_ग_लिखो_lock_irqsave(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_lock_irqsave);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_LOCK_IRQ
व्योम __lockfunc _raw_ग_लिखो_lock_irq(rwlock_t *lock)
अणु
	__raw_ग_लिखो_lock_irq(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_lock_irq);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_LOCK_BH
व्योम __lockfunc _raw_ग_लिखो_lock_bh(rwlock_t *lock)
अणु
	__raw_ग_लिखो_lock_bh(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_lock_bh);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_UNLOCK
व्योम __lockfunc _raw_ग_लिखो_unlock(rwlock_t *lock)
अणु
	__raw_ग_लिखो_unlock(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_unlock);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_UNLOCK_IRQRESTORE
व्योम __lockfunc _raw_ग_लिखो_unlock_irqrestore(rwlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	__raw_ग_लिखो_unlock_irqrestore(lock, flags);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_unlock_irqrestore);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_UNLOCK_IRQ
व्योम __lockfunc _raw_ग_लिखो_unlock_irq(rwlock_t *lock)
अणु
	__raw_ग_लिखो_unlock_irq(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_unlock_irq);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_INLINE_WRITE_UNLOCK_BH
व्योम __lockfunc _raw_ग_लिखो_unlock_bh(rwlock_t *lock)
अणु
	__raw_ग_लिखो_unlock_bh(lock);
पूर्ण
EXPORT_SYMBOL(_raw_ग_लिखो_unlock_bh);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

व्योम __lockfunc _raw_spin_lock_nested(raw_spinlock_t *lock, पूर्णांक subclass)
अणु
	preempt_disable();
	spin_acquire(&lock->dep_map, subclass, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_spin_trylock, करो_raw_spin_lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_lock_nested);

अचिन्हित दीर्घ __lockfunc _raw_spin_lock_irqsave_nested(raw_spinlock_t *lock,
						   पूर्णांक subclass)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	preempt_disable();
	spin_acquire(&lock->dep_map, subclass, 0, _RET_IP_);
	LOCK_CONTENDED_FLAGS(lock, करो_raw_spin_trylock, करो_raw_spin_lock,
				करो_raw_spin_lock_flags, &flags);
	वापस flags;
पूर्ण
EXPORT_SYMBOL(_raw_spin_lock_irqsave_nested);

व्योम __lockfunc _raw_spin_lock_nest_lock(raw_spinlock_t *lock,
				     काष्ठा lockdep_map *nest_lock)
अणु
	preempt_disable();
	spin_acquire_nest(&lock->dep_map, 0, 0, nest_lock, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_spin_trylock, करो_raw_spin_lock);
पूर्ण
EXPORT_SYMBOL(_raw_spin_lock_nest_lock);

#पूर्ण_अगर

notrace पूर्णांक in_lock_functions(अचिन्हित दीर्घ addr)
अणु
	/* Linker adds these: start and end of __lockfunc functions */
	बाह्य अक्षर __lock_text_start[], __lock_text_end[];

	वापस addr >= (अचिन्हित दीर्घ)__lock_text_start
	&& addr < (अचिन्हित दीर्घ)__lock_text_end;
पूर्ण
EXPORT_SYMBOL(in_lock_functions);
