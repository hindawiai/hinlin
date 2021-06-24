<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008 Intel Corporation
 * Author: Matthew Wilcox <willy@linux.पूर्णांकel.com>
 *
 * This file implements counting semaphores.
 * A counting semaphore may be acquired 'n' बार beक्रमe sleeping.
 * See mutex.c क्रम single-acquisition sleeping locks which enक्रमce
 * rules which allow code to be debugged more easily.
 */

/*
 * Some notes on the implementation:
 *
 * The spinlock controls access to the other members of the semaphore.
 * करोwn_trylock() and up() can be called from पूर्णांकerrupt context, so we
 * have to disable पूर्णांकerrupts when taking the lock.  It turns out various
 * parts of the kernel expect to be able to use करोwn() on a semaphore in
 * पूर्णांकerrupt context when they know it will succeed, so we have to use
 * irqsave variants क्रम करोwn(), करोwn_पूर्णांकerruptible() and करोwn_समाप्तable()
 * too.
 *
 * The ->count variable represents how many more tasks can acquire this
 * semaphore.  If it's zero, there may be tasks रुकोing on the रुको_list.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ftrace.h>

अटल noअंतरभूत व्योम __करोwn(काष्ठा semaphore *sem);
अटल noअंतरभूत पूर्णांक __करोwn_पूर्णांकerruptible(काष्ठा semaphore *sem);
अटल noअंतरभूत पूर्णांक __करोwn_समाप्तable(काष्ठा semaphore *sem);
अटल noअंतरभूत पूर्णांक __करोwn_समयout(काष्ठा semaphore *sem, दीर्घ समयout);
अटल noअंतरभूत व्योम __up(काष्ठा semaphore *sem);

/**
 * करोwn - acquire the semaphore
 * @sem: the semaphore to be acquired
 *
 * Acquires the semaphore.  If no more tasks are allowed to acquire the
 * semaphore, calling this function will put the task to sleep until the
 * semaphore is released.
 *
 * Use of this function is deprecated, please use करोwn_पूर्णांकerruptible() or
 * करोwn_समाप्तable() instead.
 */
व्योम करोwn(काष्ठा semaphore *sem)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&sem->lock, flags);
	अगर (likely(sem->count > 0))
		sem->count--;
	अन्यथा
		__करोwn(sem);
	raw_spin_unlock_irqrestore(&sem->lock, flags);
पूर्ण
EXPORT_SYMBOL(करोwn);

/**
 * करोwn_पूर्णांकerruptible - acquire the semaphore unless पूर्णांकerrupted
 * @sem: the semaphore to be acquired
 *
 * Attempts to acquire the semaphore.  If no more tasks are allowed to
 * acquire the semaphore, calling this function will put the task to sleep.
 * If the sleep is पूर्णांकerrupted by a संकेत, this function will वापस -EINTR.
 * If the semaphore is successfully acquired, this function वापसs 0.
 */
पूर्णांक करोwn_पूर्णांकerruptible(काष्ठा semaphore *sem)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0;

	raw_spin_lock_irqsave(&sem->lock, flags);
	अगर (likely(sem->count > 0))
		sem->count--;
	अन्यथा
		result = __करोwn_पूर्णांकerruptible(sem);
	raw_spin_unlock_irqrestore(&sem->lock, flags);

	वापस result;
पूर्ण
EXPORT_SYMBOL(करोwn_पूर्णांकerruptible);

/**
 * करोwn_समाप्तable - acquire the semaphore unless समाप्तed
 * @sem: the semaphore to be acquired
 *
 * Attempts to acquire the semaphore.  If no more tasks are allowed to
 * acquire the semaphore, calling this function will put the task to sleep.
 * If the sleep is पूर्णांकerrupted by a fatal संकेत, this function will वापस
 * -EINTR.  If the semaphore is successfully acquired, this function वापसs
 * 0.
 */
पूर्णांक करोwn_समाप्तable(काष्ठा semaphore *sem)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0;

	raw_spin_lock_irqsave(&sem->lock, flags);
	अगर (likely(sem->count > 0))
		sem->count--;
	अन्यथा
		result = __करोwn_समाप्तable(sem);
	raw_spin_unlock_irqrestore(&sem->lock, flags);

	वापस result;
पूर्ण
EXPORT_SYMBOL(करोwn_समाप्तable);

/**
 * करोwn_trylock - try to acquire the semaphore, without रुकोing
 * @sem: the semaphore to be acquired
 *
 * Try to acquire the semaphore atomically.  Returns 0 अगर the semaphore has
 * been acquired successfully or 1 अगर it cannot be acquired.
 *
 * NOTE: This वापस value is inverted from both spin_trylock and
 * mutex_trylock!  Be careful about this when converting code.
 *
 * Unlike mutex_trylock, this function can be used from पूर्णांकerrupt context,
 * and the semaphore can be released by any task or पूर्णांकerrupt.
 */
पूर्णांक करोwn_trylock(काष्ठा semaphore *sem)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक count;

	raw_spin_lock_irqsave(&sem->lock, flags);
	count = sem->count - 1;
	अगर (likely(count >= 0))
		sem->count = count;
	raw_spin_unlock_irqrestore(&sem->lock, flags);

	वापस (count < 0);
पूर्ण
EXPORT_SYMBOL(करोwn_trylock);

/**
 * करोwn_समयout - acquire the semaphore within a specअगरied समय
 * @sem: the semaphore to be acquired
 * @समयout: how दीर्घ to रुको beक्रमe failing
 *
 * Attempts to acquire the semaphore.  If no more tasks are allowed to
 * acquire the semaphore, calling this function will put the task to sleep.
 * If the semaphore is not released within the specअगरied number of jअगरfies,
 * this function वापसs -ETIME.  It वापसs 0 अगर the semaphore was acquired.
 */
पूर्णांक करोwn_समयout(काष्ठा semaphore *sem, दीर्घ समयout)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result = 0;

	raw_spin_lock_irqsave(&sem->lock, flags);
	अगर (likely(sem->count > 0))
		sem->count--;
	अन्यथा
		result = __करोwn_समयout(sem, समयout);
	raw_spin_unlock_irqrestore(&sem->lock, flags);

	वापस result;
पूर्ण
EXPORT_SYMBOL(करोwn_समयout);

/**
 * up - release the semaphore
 * @sem: the semaphore to release
 *
 * Release the semaphore.  Unlike mutexes, up() may be called from any
 * context and even by tasks which have never called करोwn().
 */
व्योम up(काष्ठा semaphore *sem)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&sem->lock, flags);
	अगर (likely(list_empty(&sem->रुको_list)))
		sem->count++;
	अन्यथा
		__up(sem);
	raw_spin_unlock_irqrestore(&sem->lock, flags);
पूर्ण
EXPORT_SYMBOL(up);

/* Functions क्रम the contended हाल */

काष्ठा semaphore_रुकोer अणु
	काष्ठा list_head list;
	काष्ठा task_काष्ठा *task;
	bool up;
पूर्ण;

/*
 * Because this function is अंतरभूतd, the 'state' parameter will be
 * स्थिरant, and thus optimised away by the compiler.  Likewise the
 * 'timeout' parameter क्रम the हालs without समयouts.
 */
अटल अंतरभूत पूर्णांक __sched __करोwn_common(काष्ठा semaphore *sem, दीर्घ state,
								दीर्घ समयout)
अणु
	काष्ठा semaphore_रुकोer रुकोer;

	list_add_tail(&रुकोer.list, &sem->रुको_list);
	रुकोer.task = current;
	रुकोer.up = false;

	क्रम (;;) अणु
		अगर (संकेत_pending_state(state, current))
			जाओ पूर्णांकerrupted;
		अगर (unlikely(समयout <= 0))
			जाओ समयd_out;
		__set_current_state(state);
		raw_spin_unlock_irq(&sem->lock);
		समयout = schedule_समयout(समयout);
		raw_spin_lock_irq(&sem->lock);
		अगर (रुकोer.up)
			वापस 0;
	पूर्ण

 समयd_out:
	list_del(&रुकोer.list);
	वापस -ETIME;

 पूर्णांकerrupted:
	list_del(&रुकोer.list);
	वापस -EINTR;
पूर्ण

अटल noअंतरभूत व्योम __sched __करोwn(काष्ठा semaphore *sem)
अणु
	__करोwn_common(sem, TASK_UNINTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
पूर्ण

अटल noअंतरभूत पूर्णांक __sched __करोwn_पूर्णांकerruptible(काष्ठा semaphore *sem)
अणु
	वापस __करोwn_common(sem, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
पूर्ण

अटल noअंतरभूत पूर्णांक __sched __करोwn_समाप्तable(काष्ठा semaphore *sem)
अणु
	वापस __करोwn_common(sem, TASK_KILLABLE, MAX_SCHEDULE_TIMEOUT);
पूर्ण

अटल noअंतरभूत पूर्णांक __sched __करोwn_समयout(काष्ठा semaphore *sem, दीर्घ समयout)
अणु
	वापस __करोwn_common(sem, TASK_UNINTERRUPTIBLE, समयout);
पूर्ण

अटल noअंतरभूत व्योम __sched __up(काष्ठा semaphore *sem)
अणु
	काष्ठा semaphore_रुकोer *रुकोer = list_first_entry(&sem->रुको_list,
						काष्ठा semaphore_रुकोer, list);
	list_del(&रुकोer->list);
	रुकोer->up = true;
	wake_up_process(रुकोer->task);
पूर्ण
