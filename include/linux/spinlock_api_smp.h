<शैली गुरु>
#अगर_अघोषित __LINUX_SPINLOCK_API_SMP_H
#घोषणा __LINUX_SPINLOCK_API_SMP_H

#अगर_अघोषित __LINUX_SPINLOCK_H
# error "please don't include this file directly"
#पूर्ण_अगर

/*
 * include/linux/spinlock_api_smp.h
 *
 * spinlock API declarations on SMP (and debug)
 * (implemented in kernel/spinlock.c)
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

पूर्णांक in_lock_functions(अचिन्हित दीर्घ addr);

#घोषणा निश्चित_raw_spin_locked(x)	BUG_ON(!raw_spin_is_locked(x))

व्योम __lockfunc _raw_spin_lock(raw_spinlock_t *lock)		__acquires(lock);
व्योम __lockfunc _raw_spin_lock_nested(raw_spinlock_t *lock, पूर्णांक subclass)
								__acquires(lock);
व्योम __lockfunc
_raw_spin_lock_nest_lock(raw_spinlock_t *lock, काष्ठा lockdep_map *map)
								__acquires(lock);
व्योम __lockfunc _raw_spin_lock_bh(raw_spinlock_t *lock)		__acquires(lock);
व्योम __lockfunc _raw_spin_lock_irq(raw_spinlock_t *lock)
								__acquires(lock);

अचिन्हित दीर्घ __lockfunc _raw_spin_lock_irqsave(raw_spinlock_t *lock)
								__acquires(lock);
अचिन्हित दीर्घ __lockfunc
_raw_spin_lock_irqsave_nested(raw_spinlock_t *lock, पूर्णांक subclass)
								__acquires(lock);
पूर्णांक __lockfunc _raw_spin_trylock(raw_spinlock_t *lock);
पूर्णांक __lockfunc _raw_spin_trylock_bh(raw_spinlock_t *lock);
व्योम __lockfunc _raw_spin_unlock(raw_spinlock_t *lock)		__releases(lock);
व्योम __lockfunc _raw_spin_unlock_bh(raw_spinlock_t *lock)	__releases(lock);
व्योम __lockfunc _raw_spin_unlock_irq(raw_spinlock_t *lock)	__releases(lock);
व्योम __lockfunc
_raw_spin_unlock_irqrestore(raw_spinlock_t *lock, अचिन्हित दीर्घ flags)
								__releases(lock);

#अगर_घोषित CONFIG_INLINE_SPIN_LOCK
#घोषणा _raw_spin_lock(lock) __raw_spin_lock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_LOCK_BH
#घोषणा _raw_spin_lock_bh(lock) __raw_spin_lock_bh(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_LOCK_IRQ
#घोषणा _raw_spin_lock_irq(lock) __raw_spin_lock_irq(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_LOCK_IRQSAVE
#घोषणा _raw_spin_lock_irqsave(lock) __raw_spin_lock_irqsave(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_TRYLOCK
#घोषणा _raw_spin_trylock(lock) __raw_spin_trylock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_TRYLOCK_BH
#घोषणा _raw_spin_trylock_bh(lock) __raw_spin_trylock_bh(lock)
#पूर्ण_अगर

#अगर_अघोषित CONFIG_UNINLINE_SPIN_UNLOCK
#घोषणा _raw_spin_unlock(lock) __raw_spin_unlock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_UNLOCK_BH
#घोषणा _raw_spin_unlock_bh(lock) __raw_spin_unlock_bh(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_UNLOCK_IRQ
#घोषणा _raw_spin_unlock_irq(lock) __raw_spin_unlock_irq(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_SPIN_UNLOCK_IRQRESTORE
#घोषणा _raw_spin_unlock_irqrestore(lock, flags) __raw_spin_unlock_irqrestore(lock, flags)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक __raw_spin_trylock(raw_spinlock_t *lock)
अणु
	preempt_disable();
	अगर (करो_raw_spin_trylock(lock)) अणु
		spin_acquire(&lock->dep_map, 0, 1, _RET_IP_);
		वापस 1;
	पूर्ण
	preempt_enable();
	वापस 0;
पूर्ण

/*
 * If lockdep is enabled then we use the non-preemption spin-ops
 * even on CONFIG_PREEMPTION, because lockdep assumes that पूर्णांकerrupts are
 * not re-enabled during lock-acquire (which the preempt-spin-ops करो):
 */
#अगर !defined(CONFIG_GENERIC_LOCKBREAK) || defined(CONFIG_DEBUG_LOCK_ALLOC)

अटल अंतरभूत अचिन्हित दीर्घ __raw_spin_lock_irqsave(raw_spinlock_t *lock)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	preempt_disable();
	spin_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	/*
	 * On lockdep we करोnt want the hand-coded irq-enable of
	 * करो_raw_spin_lock_flags() code, because lockdep assumes
	 * that पूर्णांकerrupts are not re-enabled during lock-acquire:
	 */
#अगर_घोषित CONFIG_LOCKDEP
	LOCK_CONTENDED(lock, करो_raw_spin_trylock, करो_raw_spin_lock);
#अन्यथा
	करो_raw_spin_lock_flags(lock, &flags);
#पूर्ण_अगर
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम __raw_spin_lock_irq(raw_spinlock_t *lock)
अणु
	local_irq_disable();
	preempt_disable();
	spin_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_spin_trylock, करो_raw_spin_lock);
पूर्ण

अटल अंतरभूत व्योम __raw_spin_lock_bh(raw_spinlock_t *lock)
अणु
	__local_bh_disable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
	spin_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_spin_trylock, करो_raw_spin_lock);
पूर्ण

अटल अंतरभूत व्योम __raw_spin_lock(raw_spinlock_t *lock)
अणु
	preempt_disable();
	spin_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_spin_trylock, करो_raw_spin_lock);
पूर्ण

#पूर्ण_अगर /* !CONFIG_GENERIC_LOCKBREAK || CONFIG_DEBUG_LOCK_ALLOC */

अटल अंतरभूत व्योम __raw_spin_unlock(raw_spinlock_t *lock)
अणु
	spin_release(&lock->dep_map, _RET_IP_);
	करो_raw_spin_unlock(lock);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_spin_unlock_irqrestore(raw_spinlock_t *lock,
					    अचिन्हित दीर्घ flags)
अणु
	spin_release(&lock->dep_map, _RET_IP_);
	करो_raw_spin_unlock(lock);
	local_irq_restore(flags);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_spin_unlock_irq(raw_spinlock_t *lock)
अणु
	spin_release(&lock->dep_map, _RET_IP_);
	करो_raw_spin_unlock(lock);
	local_irq_enable();
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_spin_unlock_bh(raw_spinlock_t *lock)
अणु
	spin_release(&lock->dep_map, _RET_IP_);
	करो_raw_spin_unlock(lock);
	__local_bh_enable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
पूर्ण

अटल अंतरभूत पूर्णांक __raw_spin_trylock_bh(raw_spinlock_t *lock)
अणु
	__local_bh_disable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
	अगर (करो_raw_spin_trylock(lock)) अणु
		spin_acquire(&lock->dep_map, 0, 1, _RET_IP_);
		वापस 1;
	पूर्ण
	__local_bh_enable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
	वापस 0;
पूर्ण

#समावेश <linux/rwlock_api_smp.h>

#पूर्ण_अगर /* __LINUX_SPINLOCK_API_SMP_H */
