<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ldisc rw semaphore
 *
 * The ldisc semaphore is semantically a rw_semaphore but which enक्रमces
 * an alternate policy, namely:
 *   1) Supports lock रुको समयouts
 *   2) Write रुकोer has priority
 *   3) Downgrading is not supported
 *
 * Implementation notes:
 *   1) Upper half of semaphore count is a रुको count (dअगरfers from rwsem
 *	in that rwsem normalizes the upper half to the रुको bias)
 *   2) Lacks overflow checking
 *
 * The generic counting was copied and modअगरied from include/यंत्र-generic/rwsem.h
 * by Paul Mackerras <paulus@samba.org>.
 *
 * The scheduling policy was copied and modअगरied from lib/rwsem.c
 * Written by David Howells (dhowells@redhat.com).
 *
 * This implementation incorporates the ग_लिखो lock stealing work of
 * Michel Lespinasse <walken@google.com>.
 *
 * Copyright (C) 2013 Peter Hurley <peter@hurleysoftware.com>
 */

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/tty.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>


#अगर BITS_PER_LONG == 64
# define LDSEM_ACTIVE_MASK	0xffffffffL
#अन्यथा
# define LDSEM_ACTIVE_MASK	0x0000ffffL
#पूर्ण_अगर

#घोषणा LDSEM_UNLOCKED		0L
#घोषणा LDSEM_ACTIVE_BIAS	1L
#घोषणा LDSEM_WAIT_BIAS		(-LDSEM_ACTIVE_MASK-1)
#घोषणा LDSEM_READ_BIAS		LDSEM_ACTIVE_BIAS
#घोषणा LDSEM_WRITE_BIAS	(LDSEM_WAIT_BIAS + LDSEM_ACTIVE_BIAS)

काष्ठा ldsem_रुकोer अणु
	काष्ठा list_head list;
	काष्ठा task_काष्ठा *task;
पूर्ण;

/*
 * Initialize an ldsem:
 */
व्योम __init_ldsem(काष्ठा ld_semaphore *sem, स्थिर अक्षर *name,
		  काष्ठा lock_class_key *key)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	/*
	 * Make sure we are not reinitializing a held semaphore:
	 */
	debug_check_no_locks_मुक्तd((व्योम *)sem, माप(*sem));
	lockdep_init_map(&sem->dep_map, name, key, 0);
#पूर्ण_अगर
	atomic_दीर्घ_set(&sem->count, LDSEM_UNLOCKED);
	sem->रुको_पढ़ोers = 0;
	raw_spin_lock_init(&sem->रुको_lock);
	INIT_LIST_HEAD(&sem->पढ़ो_रुको);
	INIT_LIST_HEAD(&sem->ग_लिखो_रुको);
पूर्ण

अटल व्योम __ldsem_wake_पढ़ोers(काष्ठा ld_semaphore *sem)
अणु
	काष्ठा ldsem_रुकोer *रुकोer, *next;
	काष्ठा task_काष्ठा *tsk;
	दीर्घ adjust, count;

	/*
	 * Try to grant पढ़ो locks to all पढ़ोers on the पढ़ो रुको list.
	 * Note the 'active part' of the count is incremented by
	 * the number of पढ़ोers beक्रमe waking any processes up.
	 */
	adjust = sem->रुको_पढ़ोers * (LDSEM_ACTIVE_BIAS - LDSEM_WAIT_BIAS);
	count = atomic_दीर्घ_add_वापस(adjust, &sem->count);
	करो अणु
		अगर (count > 0)
			अवरोध;
		अगर (atomic_दीर्घ_try_cmpxchg(&sem->count, &count, count - adjust))
			वापस;
	पूर्ण जबतक (1);

	list_क्रम_each_entry_safe(रुकोer, next, &sem->पढ़ो_रुको, list) अणु
		tsk = रुकोer->task;
		smp_store_release(&रुकोer->task, शून्य);
		wake_up_process(tsk);
		put_task_काष्ठा(tsk);
	पूर्ण
	INIT_LIST_HEAD(&sem->पढ़ो_रुको);
	sem->रुको_पढ़ोers = 0;
पूर्ण

अटल अंतरभूत पूर्णांक ग_लिखोr_trylock(काष्ठा ld_semaphore *sem)
अणु
	/*
	 * Only wake this ग_लिखोr अगर the active part of the count can be
	 * transitioned from 0 -> 1
	 */
	दीर्घ count = atomic_दीर्घ_add_वापस(LDSEM_ACTIVE_BIAS, &sem->count);
	करो अणु
		अगर ((count & LDSEM_ACTIVE_MASK) == LDSEM_ACTIVE_BIAS)
			वापस 1;
		अगर (atomic_दीर्घ_try_cmpxchg(&sem->count, &count, count - LDSEM_ACTIVE_BIAS))
			वापस 0;
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम __ldsem_wake_ग_लिखोr(काष्ठा ld_semaphore *sem)
अणु
	काष्ठा ldsem_रुकोer *रुकोer;

	रुकोer = list_entry(sem->ग_लिखो_रुको.next, काष्ठा ldsem_रुकोer, list);
	wake_up_process(रुकोer->task);
पूर्ण

/*
 * handle the lock release when processes blocked on it that can now run
 * - अगर we come here from up_xxxx(), then:
 *   - the 'active part' of count (&0x0000ffff) reached 0 (but may have changed)
 *   - the 'waiting part' of count (&0xffff0000) is -ve (and will still be so)
 * - the spinlock must be held by the caller
 * - woken process blocks are discarded from the list after having task zeroed
 */
अटल व्योम __ldsem_wake(काष्ठा ld_semaphore *sem)
अणु
	अगर (!list_empty(&sem->ग_लिखो_रुको))
		__ldsem_wake_ग_लिखोr(sem);
	अन्यथा अगर (!list_empty(&sem->पढ़ो_रुको))
		__ldsem_wake_पढ़ोers(sem);
पूर्ण

अटल व्योम ldsem_wake(काष्ठा ld_semaphore *sem)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&sem->रुको_lock, flags);
	__ldsem_wake(sem);
	raw_spin_unlock_irqrestore(&sem->रुको_lock, flags);
पूर्ण

/*
 * रुको क्रम the पढ़ो lock to be granted
 */
अटल काष्ठा ld_semaphore __sched *
करोwn_पढ़ो_failed(काष्ठा ld_semaphore *sem, दीर्घ count, दीर्घ समयout)
अणु
	काष्ठा ldsem_रुकोer रुकोer;
	दीर्घ adjust = -LDSEM_ACTIVE_BIAS + LDSEM_WAIT_BIAS;

	/* set up my own style of रुकोqueue */
	raw_spin_lock_irq(&sem->रुको_lock);

	/*
	 * Try to reverse the lock attempt but अगर the count has changed
	 * so that reversing fails, check अगर there are are no रुकोers,
	 * and early-out अगर not
	 */
	करो अणु
		अगर (atomic_दीर्घ_try_cmpxchg(&sem->count, &count, count + adjust)) अणु
			count += adjust;
			अवरोध;
		पूर्ण
		अगर (count > 0) अणु
			raw_spin_unlock_irq(&sem->रुको_lock);
			वापस sem;
		पूर्ण
	पूर्ण जबतक (1);

	list_add_tail(&रुकोer.list, &sem->पढ़ो_रुको);
	sem->रुको_पढ़ोers++;

	रुकोer.task = current;
	get_task_काष्ठा(current);

	/* अगर there are no active locks, wake the new lock owner(s) */
	अगर ((count & LDSEM_ACTIVE_MASK) == 0)
		__ldsem_wake(sem);

	raw_spin_unlock_irq(&sem->रुको_lock);

	/* रुको to be given the lock */
	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);

		अगर (!smp_load_acquire(&रुकोer.task))
			अवरोध;
		अगर (!समयout)
			अवरोध;
		समयout = schedule_समयout(समयout);
	पूर्ण

	__set_current_state(TASK_RUNNING);

	अगर (!समयout) अणु
		/*
		 * Lock समयd out but check अगर this task was just
		 * granted lock ownership - अगर so, pretend there
		 * was no समयout; otherwise, cleanup lock रुको.
		 */
		raw_spin_lock_irq(&sem->रुको_lock);
		अगर (रुकोer.task) अणु
			atomic_दीर्घ_add_वापस(-LDSEM_WAIT_BIAS, &sem->count);
			sem->रुको_पढ़ोers--;
			list_del(&रुकोer.list);
			raw_spin_unlock_irq(&sem->रुको_lock);
			put_task_काष्ठा(रुकोer.task);
			वापस शून्य;
		पूर्ण
		raw_spin_unlock_irq(&sem->रुको_lock);
	पूर्ण

	वापस sem;
पूर्ण

/*
 * रुको क्रम the ग_लिखो lock to be granted
 */
अटल काष्ठा ld_semaphore __sched *
करोwn_ग_लिखो_failed(काष्ठा ld_semaphore *sem, दीर्घ count, दीर्घ समयout)
अणु
	काष्ठा ldsem_रुकोer रुकोer;
	दीर्घ adjust = -LDSEM_ACTIVE_BIAS;
	पूर्णांक locked = 0;

	/* set up my own style of रुकोqueue */
	raw_spin_lock_irq(&sem->रुको_lock);

	/*
	 * Try to reverse the lock attempt but अगर the count has changed
	 * so that reversing fails, check अगर the lock is now owned,
	 * and early-out अगर so.
	 */
	करो अणु
		अगर (atomic_दीर्घ_try_cmpxchg(&sem->count, &count, count + adjust))
			अवरोध;
		अगर ((count & LDSEM_ACTIVE_MASK) == LDSEM_ACTIVE_BIAS) अणु
			raw_spin_unlock_irq(&sem->रुको_lock);
			वापस sem;
		पूर्ण
	पूर्ण जबतक (1);

	list_add_tail(&रुकोer.list, &sem->ग_लिखो_रुको);

	रुकोer.task = current;

	set_current_state(TASK_UNINTERRUPTIBLE);
	क्रम (;;) अणु
		अगर (!समयout)
			अवरोध;
		raw_spin_unlock_irq(&sem->रुको_lock);
		समयout = schedule_समयout(समयout);
		raw_spin_lock_irq(&sem->रुको_lock);
		set_current_state(TASK_UNINTERRUPTIBLE);
		locked = ग_लिखोr_trylock(sem);
		अगर (locked)
			अवरोध;
	पूर्ण

	अगर (!locked)
		atomic_दीर्घ_add_वापस(-LDSEM_WAIT_BIAS, &sem->count);
	list_del(&रुकोer.list);

	/*
	 * In हाल of समयout, wake up every पढ़ोer who gave the right of way
	 * to ग_लिखोr. Prevent separation पढ़ोers पूर्णांकo two groups:
	 * one that helds semaphore and another that sleeps.
	 * (in हाल of no contention with a ग_लिखोr)
	 */
	अगर (!locked && list_empty(&sem->ग_लिखो_रुको))
		__ldsem_wake_पढ़ोers(sem);

	raw_spin_unlock_irq(&sem->रुको_lock);

	__set_current_state(TASK_RUNNING);

	/* lock रुको may have समयd out */
	अगर (!locked)
		वापस शून्य;
	वापस sem;
पूर्ण



अटल पूर्णांक __ldsem_करोwn_पढ़ो_nested(काष्ठा ld_semaphore *sem,
					   पूर्णांक subclass, दीर्घ समयout)
अणु
	दीर्घ count;

	rwsem_acquire_पढ़ो(&sem->dep_map, subclass, 0, _RET_IP_);

	count = atomic_दीर्घ_add_वापस(LDSEM_READ_BIAS, &sem->count);
	अगर (count <= 0) अणु
		lock_contended(&sem->dep_map, _RET_IP_);
		अगर (!करोwn_पढ़ो_failed(sem, count, समयout)) अणु
			rwsem_release(&sem->dep_map, _RET_IP_);
			वापस 0;
		पूर्ण
	पूर्ण
	lock_acquired(&sem->dep_map, _RET_IP_);
	वापस 1;
पूर्ण

अटल पूर्णांक __ldsem_करोwn_ग_लिखो_nested(काष्ठा ld_semaphore *sem,
					    पूर्णांक subclass, दीर्घ समयout)
अणु
	दीर्घ count;

	rwsem_acquire(&sem->dep_map, subclass, 0, _RET_IP_);

	count = atomic_दीर्घ_add_वापस(LDSEM_WRITE_BIAS, &sem->count);
	अगर ((count & LDSEM_ACTIVE_MASK) != LDSEM_ACTIVE_BIAS) अणु
		lock_contended(&sem->dep_map, _RET_IP_);
		अगर (!करोwn_ग_लिखो_failed(sem, count, समयout)) अणु
			rwsem_release(&sem->dep_map, _RET_IP_);
			वापस 0;
		पूर्ण
	पूर्ण
	lock_acquired(&sem->dep_map, _RET_IP_);
	वापस 1;
पूर्ण


/*
 * lock क्रम पढ़ोing -- वापसs 1 अगर successful, 0 अगर समयd out
 */
पूर्णांक __sched ldsem_करोwn_पढ़ो(काष्ठा ld_semaphore *sem, दीर्घ समयout)
अणु
	might_sleep();
	वापस __ldsem_करोwn_पढ़ो_nested(sem, 0, समयout);
पूर्ण

/*
 * trylock क्रम पढ़ोing -- वापसs 1 अगर successful, 0 अगर contention
 */
पूर्णांक ldsem_करोwn_पढ़ो_trylock(काष्ठा ld_semaphore *sem)
अणु
	दीर्घ count = atomic_दीर्घ_पढ़ो(&sem->count);

	जबतक (count >= 0) अणु
		अगर (atomic_दीर्घ_try_cmpxchg(&sem->count, &count, count + LDSEM_READ_BIAS)) अणु
			rwsem_acquire_पढ़ो(&sem->dep_map, 0, 1, _RET_IP_);
			lock_acquired(&sem->dep_map, _RET_IP_);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * lock क्रम writing -- वापसs 1 अगर successful, 0 अगर समयd out
 */
पूर्णांक __sched ldsem_करोwn_ग_लिखो(काष्ठा ld_semaphore *sem, दीर्घ समयout)
अणु
	might_sleep();
	वापस __ldsem_करोwn_ग_लिखो_nested(sem, 0, समयout);
पूर्ण

/*
 * trylock क्रम writing -- वापसs 1 अगर successful, 0 अगर contention
 */
पूर्णांक ldsem_करोwn_ग_लिखो_trylock(काष्ठा ld_semaphore *sem)
अणु
	दीर्घ count = atomic_दीर्घ_पढ़ो(&sem->count);

	जबतक ((count & LDSEM_ACTIVE_MASK) == 0) अणु
		अगर (atomic_दीर्घ_try_cmpxchg(&sem->count, &count, count + LDSEM_WRITE_BIAS)) अणु
			rwsem_acquire(&sem->dep_map, 0, 1, _RET_IP_);
			lock_acquired(&sem->dep_map, _RET_IP_);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * release a पढ़ो lock
 */
व्योम ldsem_up_पढ़ो(काष्ठा ld_semaphore *sem)
अणु
	दीर्घ count;

	rwsem_release(&sem->dep_map, _RET_IP_);

	count = atomic_दीर्घ_add_वापस(-LDSEM_READ_BIAS, &sem->count);
	अगर (count < 0 && (count & LDSEM_ACTIVE_MASK) == 0)
		ldsem_wake(sem);
पूर्ण

/*
 * release a ग_लिखो lock
 */
व्योम ldsem_up_ग_लिखो(काष्ठा ld_semaphore *sem)
अणु
	दीर्घ count;

	rwsem_release(&sem->dep_map, _RET_IP_);

	count = atomic_दीर्घ_add_वापस(-LDSEM_WRITE_BIAS, &sem->count);
	अगर (count < 0)
		ldsem_wake(sem);
पूर्ण


#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

पूर्णांक ldsem_करोwn_पढ़ो_nested(काष्ठा ld_semaphore *sem, पूर्णांक subclass, दीर्घ समयout)
अणु
	might_sleep();
	वापस __ldsem_करोwn_पढ़ो_nested(sem, subclass, समयout);
पूर्ण

पूर्णांक ldsem_करोwn_ग_लिखो_nested(काष्ठा ld_semaphore *sem, पूर्णांक subclass,
			    दीर्घ समयout)
अणु
	might_sleep();
	वापस __ldsem_करोwn_ग_लिखो_nested(sem, subclass, समयout);
पूर्ण

#पूर्ण_अगर
