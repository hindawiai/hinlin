<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BIT_SPINLOCK_H
#घोषणा __LINUX_BIT_SPINLOCK_H

#समावेश <linux/kernel.h>
#समावेश <linux/preempt.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>

/*
 *  bit-based spin_lock()
 *
 * Don't use this unless you really need to: spin_lock() and spin_unlock()
 * are signअगरicantly faster.
 */
अटल अंतरभूत व्योम bit_spin_lock(पूर्णांक bitnum, अचिन्हित दीर्घ *addr)
अणु
	/*
	 * Assuming the lock is uncontended, this never enters
	 * the body of the outer loop. If it is contended, then
	 * within the inner loop a non-atomic test is used to
	 * busyरुको with less bus contention क्रम a good समय to
	 * attempt to acquire the lock bit.
	 */
	preempt_disable();
#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
	जबतक (unlikely(test_and_set_bit_lock(bitnum, addr))) अणु
		preempt_enable();
		करो अणु
			cpu_relax();
		पूर्ण जबतक (test_bit(bitnum, addr));
		preempt_disable();
	पूर्ण
#पूर्ण_अगर
	__acquire(bitlock);
पूर्ण

/*
 * Return true अगर it was acquired
 */
अटल अंतरभूत पूर्णांक bit_spin_trylock(पूर्णांक bitnum, अचिन्हित दीर्घ *addr)
अणु
	preempt_disable();
#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
	अगर (unlikely(test_and_set_bit_lock(bitnum, addr))) अणु
		preempt_enable();
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	__acquire(bitlock);
	वापस 1;
पूर्ण

/*
 *  bit-based spin_unlock()
 */
अटल अंतरभूत व्योम bit_spin_unlock(पूर्णांक bitnum, अचिन्हित दीर्घ *addr)
अणु
#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	BUG_ON(!test_bit(bitnum, addr));
#पूर्ण_अगर
#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
	clear_bit_unlock(bitnum, addr);
#पूर्ण_अगर
	preempt_enable();
	__release(bitlock);
पूर्ण

/*
 *  bit-based spin_unlock()
 *  non-atomic version, which can be used eg. अगर the bit lock itself is
 *  protecting the rest of the flags in the word.
 */
अटल अंतरभूत व्योम __bit_spin_unlock(पूर्णांक bitnum, अचिन्हित दीर्घ *addr)
अणु
#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	BUG_ON(!test_bit(bitnum, addr));
#पूर्ण_अगर
#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
	__clear_bit_unlock(bitnum, addr);
#पूर्ण_अगर
	preempt_enable();
	__release(bitlock);
पूर्ण

/*
 * Return true अगर the lock is held.
 */
अटल अंतरभूत पूर्णांक bit_spin_is_locked(पूर्णांक bitnum, अचिन्हित दीर्घ *addr)
अणु
#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
	वापस test_bit(bitnum, addr);
#या_अगर defined CONFIG_PREEMPT_COUNT
	वापस preempt_count();
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __LINUX_BIT_SPINLOCK_H */

