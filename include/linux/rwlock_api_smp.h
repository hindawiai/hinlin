<शैली गुरु>
#अगर_अघोषित __LINUX_RWLOCK_API_SMP_H
#घोषणा __LINUX_RWLOCK_API_SMP_H

#अगर_अघोषित __LINUX_SPINLOCK_API_SMP_H
# error "please don't include this file directly"
#पूर्ण_अगर

/*
 * include/linux/rwlock_api_smp.h
 *
 * spinlock API declarations on SMP (and debug)
 * (implemented in kernel/spinlock.c)
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

व्योम __lockfunc _raw_पढ़ो_lock(rwlock_t *lock)		__acquires(lock);
व्योम __lockfunc _raw_ग_लिखो_lock(rwlock_t *lock)		__acquires(lock);
व्योम __lockfunc _raw_पढ़ो_lock_bh(rwlock_t *lock)	__acquires(lock);
व्योम __lockfunc _raw_ग_लिखो_lock_bh(rwlock_t *lock)	__acquires(lock);
व्योम __lockfunc _raw_पढ़ो_lock_irq(rwlock_t *lock)	__acquires(lock);
व्योम __lockfunc _raw_ग_लिखो_lock_irq(rwlock_t *lock)	__acquires(lock);
अचिन्हित दीर्घ __lockfunc _raw_पढ़ो_lock_irqsave(rwlock_t *lock)
							__acquires(lock);
अचिन्हित दीर्घ __lockfunc _raw_ग_लिखो_lock_irqsave(rwlock_t *lock)
							__acquires(lock);
पूर्णांक __lockfunc _raw_पढ़ो_trylock(rwlock_t *lock);
पूर्णांक __lockfunc _raw_ग_लिखो_trylock(rwlock_t *lock);
व्योम __lockfunc _raw_पढ़ो_unlock(rwlock_t *lock)	__releases(lock);
व्योम __lockfunc _raw_ग_लिखो_unlock(rwlock_t *lock)	__releases(lock);
व्योम __lockfunc _raw_पढ़ो_unlock_bh(rwlock_t *lock)	__releases(lock);
व्योम __lockfunc _raw_ग_लिखो_unlock_bh(rwlock_t *lock)	__releases(lock);
व्योम __lockfunc _raw_पढ़ो_unlock_irq(rwlock_t *lock)	__releases(lock);
व्योम __lockfunc _raw_ग_लिखो_unlock_irq(rwlock_t *lock)	__releases(lock);
व्योम __lockfunc
_raw_पढ़ो_unlock_irqrestore(rwlock_t *lock, अचिन्हित दीर्घ flags)
							__releases(lock);
व्योम __lockfunc
_raw_ग_लिखो_unlock_irqrestore(rwlock_t *lock, अचिन्हित दीर्घ flags)
							__releases(lock);

#अगर_घोषित CONFIG_INLINE_READ_LOCK
#घोषणा _raw_पढ़ो_lock(lock) __raw_पढ़ो_lock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_LOCK
#घोषणा _raw_ग_लिखो_lock(lock) __raw_ग_लिखो_lock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_LOCK_BH
#घोषणा _raw_पढ़ो_lock_bh(lock) __raw_पढ़ो_lock_bh(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_LOCK_BH
#घोषणा _raw_ग_लिखो_lock_bh(lock) __raw_ग_लिखो_lock_bh(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_LOCK_IRQ
#घोषणा _raw_पढ़ो_lock_irq(lock) __raw_पढ़ो_lock_irq(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_LOCK_IRQ
#घोषणा _raw_ग_लिखो_lock_irq(lock) __raw_ग_लिखो_lock_irq(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_LOCK_IRQSAVE
#घोषणा _raw_पढ़ो_lock_irqsave(lock) __raw_पढ़ो_lock_irqsave(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_LOCK_IRQSAVE
#घोषणा _raw_ग_लिखो_lock_irqsave(lock) __raw_ग_लिखो_lock_irqsave(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_TRYLOCK
#घोषणा _raw_पढ़ो_trylock(lock) __raw_पढ़ो_trylock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_TRYLOCK
#घोषणा _raw_ग_लिखो_trylock(lock) __raw_ग_लिखो_trylock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_UNLOCK
#घोषणा _raw_पढ़ो_unlock(lock) __raw_पढ़ो_unlock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_UNLOCK
#घोषणा _raw_ग_लिखो_unlock(lock) __raw_ग_लिखो_unlock(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_UNLOCK_BH
#घोषणा _raw_पढ़ो_unlock_bh(lock) __raw_पढ़ो_unlock_bh(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_UNLOCK_BH
#घोषणा _raw_ग_लिखो_unlock_bh(lock) __raw_ग_लिखो_unlock_bh(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_UNLOCK_IRQ
#घोषणा _raw_पढ़ो_unlock_irq(lock) __raw_पढ़ो_unlock_irq(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_UNLOCK_IRQ
#घोषणा _raw_ग_लिखो_unlock_irq(lock) __raw_ग_लिखो_unlock_irq(lock)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_READ_UNLOCK_IRQRESTORE
#घोषणा _raw_पढ़ो_unlock_irqrestore(lock, flags) \
	__raw_पढ़ो_unlock_irqrestore(lock, flags)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INLINE_WRITE_UNLOCK_IRQRESTORE
#घोषणा _raw_ग_लिखो_unlock_irqrestore(lock, flags) \
	__raw_ग_लिखो_unlock_irqrestore(lock, flags)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक __raw_पढ़ो_trylock(rwlock_t *lock)
अणु
	preempt_disable();
	अगर (करो_raw_पढ़ो_trylock(lock)) अणु
		rwlock_acquire_पढ़ो(&lock->dep_map, 0, 1, _RET_IP_);
		वापस 1;
	पूर्ण
	preempt_enable();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __raw_ग_लिखो_trylock(rwlock_t *lock)
अणु
	preempt_disable();
	अगर (करो_raw_ग_लिखो_trylock(lock)) अणु
		rwlock_acquire(&lock->dep_map, 0, 1, _RET_IP_);
		वापस 1;
	पूर्ण
	preempt_enable();
	वापस 0;
पूर्ण

/*
 * If lockdep is enabled then we use the non-preemption spin-ops
 * even on CONFIG_PREEMPT, because lockdep assumes that पूर्णांकerrupts are
 * not re-enabled during lock-acquire (which the preempt-spin-ops करो):
 */
#अगर !defined(CONFIG_GENERIC_LOCKBREAK) || defined(CONFIG_DEBUG_LOCK_ALLOC)

अटल अंतरभूत व्योम __raw_पढ़ो_lock(rwlock_t *lock)
अणु
	preempt_disable();
	rwlock_acquire_पढ़ो(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_पढ़ो_trylock, करो_raw_पढ़ो_lock);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __raw_पढ़ो_lock_irqsave(rwlock_t *lock)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	preempt_disable();
	rwlock_acquire_पढ़ो(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED_FLAGS(lock, करो_raw_पढ़ो_trylock, करो_raw_पढ़ो_lock,
			     करो_raw_पढ़ो_lock_flags, &flags);
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम __raw_पढ़ो_lock_irq(rwlock_t *lock)
अणु
	local_irq_disable();
	preempt_disable();
	rwlock_acquire_पढ़ो(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_पढ़ो_trylock, करो_raw_पढ़ो_lock);
पूर्ण

अटल अंतरभूत व्योम __raw_पढ़ो_lock_bh(rwlock_t *lock)
अणु
	__local_bh_disable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
	rwlock_acquire_पढ़ो(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_पढ़ो_trylock, करो_raw_पढ़ो_lock);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __raw_ग_लिखो_lock_irqsave(rwlock_t *lock)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	preempt_disable();
	rwlock_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED_FLAGS(lock, करो_raw_ग_लिखो_trylock, करो_raw_ग_लिखो_lock,
			     करो_raw_ग_लिखो_lock_flags, &flags);
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम __raw_ग_लिखो_lock_irq(rwlock_t *lock)
अणु
	local_irq_disable();
	preempt_disable();
	rwlock_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_ग_लिखो_trylock, करो_raw_ग_लिखो_lock);
पूर्ण

अटल अंतरभूत व्योम __raw_ग_लिखो_lock_bh(rwlock_t *lock)
अणु
	__local_bh_disable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
	rwlock_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_ग_लिखो_trylock, करो_raw_ग_लिखो_lock);
पूर्ण

अटल अंतरभूत व्योम __raw_ग_लिखो_lock(rwlock_t *lock)
अणु
	preempt_disable();
	rwlock_acquire(&lock->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(lock, करो_raw_ग_लिखो_trylock, करो_raw_ग_लिखो_lock);
पूर्ण

#पूर्ण_अगर /* !CONFIG_GENERIC_LOCKBREAK || CONFIG_DEBUG_LOCK_ALLOC */

अटल अंतरभूत व्योम __raw_ग_लिखो_unlock(rwlock_t *lock)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_ग_लिखो_unlock(lock);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_पढ़ो_unlock(rwlock_t *lock)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_पढ़ो_unlock(lock);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम
__raw_पढ़ो_unlock_irqrestore(rwlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_पढ़ो_unlock(lock);
	local_irq_restore(flags);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_पढ़ो_unlock_irq(rwlock_t *lock)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_पढ़ो_unlock(lock);
	local_irq_enable();
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_पढ़ो_unlock_bh(rwlock_t *lock)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_पढ़ो_unlock(lock);
	__local_bh_enable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम __raw_ग_लिखो_unlock_irqrestore(rwlock_t *lock,
					     अचिन्हित दीर्घ flags)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_ग_लिखो_unlock(lock);
	local_irq_restore(flags);
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_ग_लिखो_unlock_irq(rwlock_t *lock)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_ग_लिखो_unlock(lock);
	local_irq_enable();
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __raw_ग_लिखो_unlock_bh(rwlock_t *lock)
अणु
	rwlock_release(&lock->dep_map, _RET_IP_);
	करो_raw_ग_लिखो_unlock(lock);
	__local_bh_enable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);
पूर्ण

#पूर्ण_अगर /* __LINUX_RWLOCK_API_SMP_H */
