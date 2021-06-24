<शैली गुरु>
#अगर_अघोषित __LINUX_SPINLOCK_API_UP_H
#घोषणा __LINUX_SPINLOCK_API_UP_H

#अगर_अघोषित __LINUX_SPINLOCK_H
# error "please don't include this file directly"
#पूर्ण_अगर

/*
 * include/linux/spinlock_api_up.h
 *
 * spinlock API implementation on UP-nondebug (अंतरभूतd implementation)
 *
 * portions Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 */

#घोषणा in_lock_functions(ADDR)		0

#घोषणा निश्चित_raw_spin_locked(lock)	करो अणु (व्योम)(lock); पूर्ण जबतक (0)

/*
 * In the UP-nondebug हाल there's no real locking going on, so the
 * only thing we have to करो is to keep the preempt counts and irq
 * flags straight, to suppress compiler warnings of unused lock
 * variables, and to add the proper checker annotations:
 */
#घोषणा ___LOCK(lock) \
  करो अणु __acquire(lock); (व्योम)(lock); पूर्ण जबतक (0)

#घोषणा __LOCK(lock) \
  करो अणु preempt_disable(); ___LOCK(lock); पूर्ण जबतक (0)

#घोषणा __LOCK_BH(lock) \
  करो अणु __local_bh_disable_ip(_THIS_IP_, SOFTIRQ_LOCK_OFFSET); ___LOCK(lock); पूर्ण जबतक (0)

#घोषणा __LOCK_IRQ(lock) \
  करो अणु local_irq_disable(); __LOCK(lock); पूर्ण जबतक (0)

#घोषणा __LOCK_IRQSAVE(lock, flags) \
  करो अणु local_irq_save(flags); __LOCK(lock); पूर्ण जबतक (0)

#घोषणा ___UNLOCK(lock) \
  करो अणु __release(lock); (व्योम)(lock); पूर्ण जबतक (0)

#घोषणा __UNLOCK(lock) \
  करो अणु preempt_enable(); ___UNLOCK(lock); पूर्ण जबतक (0)

#घोषणा __UNLOCK_BH(lock) \
  करो अणु __local_bh_enable_ip(_THIS_IP_, SOFTIRQ_LOCK_OFFSET); \
       ___UNLOCK(lock); पूर्ण जबतक (0)

#घोषणा __UNLOCK_IRQ(lock) \
  करो अणु local_irq_enable(); __UNLOCK(lock); पूर्ण जबतक (0)

#घोषणा __UNLOCK_IRQRESTORE(lock, flags) \
  करो अणु local_irq_restore(flags); __UNLOCK(lock); पूर्ण जबतक (0)

#घोषणा _raw_spin_lock(lock)			__LOCK(lock)
#घोषणा _raw_spin_lock_nested(lock, subclass)	__LOCK(lock)
#घोषणा _raw_पढ़ो_lock(lock)			__LOCK(lock)
#घोषणा _raw_ग_लिखो_lock(lock)			__LOCK(lock)
#घोषणा _raw_spin_lock_bh(lock)			__LOCK_BH(lock)
#घोषणा _raw_पढ़ो_lock_bh(lock)			__LOCK_BH(lock)
#घोषणा _raw_ग_लिखो_lock_bh(lock)		__LOCK_BH(lock)
#घोषणा _raw_spin_lock_irq(lock)		__LOCK_IRQ(lock)
#घोषणा _raw_पढ़ो_lock_irq(lock)		__LOCK_IRQ(lock)
#घोषणा _raw_ग_लिखो_lock_irq(lock)		__LOCK_IRQ(lock)
#घोषणा _raw_spin_lock_irqsave(lock, flags)	__LOCK_IRQSAVE(lock, flags)
#घोषणा _raw_पढ़ो_lock_irqsave(lock, flags)	__LOCK_IRQSAVE(lock, flags)
#घोषणा _raw_ग_लिखो_lock_irqsave(lock, flags)	__LOCK_IRQSAVE(lock, flags)
#घोषणा _raw_spin_trylock(lock)			(अणु __LOCK(lock); 1; पूर्ण)
#घोषणा _raw_पढ़ो_trylock(lock)			(अणु __LOCK(lock); 1; पूर्ण)
#घोषणा _raw_ग_लिखो_trylock(lock)			(अणु __LOCK(lock); 1; पूर्ण)
#घोषणा _raw_spin_trylock_bh(lock)		(अणु __LOCK_BH(lock); 1; पूर्ण)
#घोषणा _raw_spin_unlock(lock)			__UNLOCK(lock)
#घोषणा _raw_पढ़ो_unlock(lock)			__UNLOCK(lock)
#घोषणा _raw_ग_लिखो_unlock(lock)			__UNLOCK(lock)
#घोषणा _raw_spin_unlock_bh(lock)		__UNLOCK_BH(lock)
#घोषणा _raw_ग_लिखो_unlock_bh(lock)		__UNLOCK_BH(lock)
#घोषणा _raw_पढ़ो_unlock_bh(lock)		__UNLOCK_BH(lock)
#घोषणा _raw_spin_unlock_irq(lock)		__UNLOCK_IRQ(lock)
#घोषणा _raw_पढ़ो_unlock_irq(lock)		__UNLOCK_IRQ(lock)
#घोषणा _raw_ग_लिखो_unlock_irq(lock)		__UNLOCK_IRQ(lock)
#घोषणा _raw_spin_unlock_irqrestore(lock, flags) \
					__UNLOCK_IRQRESTORE(lock, flags)
#घोषणा _raw_पढ़ो_unlock_irqrestore(lock, flags) \
					__UNLOCK_IRQRESTORE(lock, flags)
#घोषणा _raw_ग_लिखो_unlock_irqrestore(lock, flags) \
					__UNLOCK_IRQRESTORE(lock, flags)

#पूर्ण_अगर /* __LINUX_SPINLOCK_API_UP_H */
