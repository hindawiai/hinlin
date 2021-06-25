<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LOCAL_LOCK_H
#घोषणा _LINUX_LOCAL_LOCK_H

#समावेश <linux/local_lock_पूर्णांकernal.h>

/**
 * local_lock_init - Runसमय initialize a lock instance
 */
#घोषणा local_lock_init(lock)		__local_lock_init(lock)

/**
 * local_lock - Acquire a per CPU local lock
 * @lock:	The lock variable
 */
#घोषणा local_lock(lock)		__local_lock(lock)

/**
 * local_lock_irq - Acquire a per CPU local lock and disable पूर्णांकerrupts
 * @lock:	The lock variable
 */
#घोषणा local_lock_irq(lock)		__local_lock_irq(lock)

/**
 * local_lock_irqsave - Acquire a per CPU local lock, save and disable
 *			 पूर्णांकerrupts
 * @lock:	The lock variable
 * @flags:	Storage क्रम पूर्णांकerrupt flags
 */
#घोषणा local_lock_irqsave(lock, flags)				\
	__local_lock_irqsave(lock, flags)

/**
 * local_unlock - Release a per CPU local lock
 * @lock:	The lock variable
 */
#घोषणा local_unlock(lock)		__local_unlock(lock)

/**
 * local_unlock_irq - Release a per CPU local lock and enable पूर्णांकerrupts
 * @lock:	The lock variable
 */
#घोषणा local_unlock_irq(lock)		__local_unlock_irq(lock)

/**
 * local_unlock_irqrestore - Release a per CPU local lock and restore
 *			      पूर्णांकerrupt flags
 * @lock:	The lock variable
 * @flags:      Interrupt flags to restore
 */
#घोषणा local_unlock_irqrestore(lock, flags)			\
	__local_unlock_irqrestore(lock, flags)

#पूर्ण_अगर
