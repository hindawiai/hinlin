<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic रुकोing primitives.
 *
 * (C) 2004 Nadia Yvette Chambers, Oracle
 */
#समावेश "sched.h"

व्योम __init_रुकोqueue_head(काष्ठा रुको_queue_head *wq_head, स्थिर अक्षर *name, काष्ठा lock_class_key *key)
अणु
	spin_lock_init(&wq_head->lock);
	lockdep_set_class_and_name(&wq_head->lock, key, name);
	INIT_LIST_HEAD(&wq_head->head);
पूर्ण

EXPORT_SYMBOL(__init_रुकोqueue_head);

व्योम add_रुको_queue(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	अचिन्हित दीर्घ flags;

	wq_entry->flags &= ~WQ_FLAG_EXCLUSIVE;
	spin_lock_irqsave(&wq_head->lock, flags);
	__add_रुको_queue(wq_head, wq_entry);
	spin_unlock_irqrestore(&wq_head->lock, flags);
पूर्ण
EXPORT_SYMBOL(add_रुको_queue);

व्योम add_रुको_queue_exclusive(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	अचिन्हित दीर्घ flags;

	wq_entry->flags |= WQ_FLAG_EXCLUSIVE;
	spin_lock_irqsave(&wq_head->lock, flags);
	__add_रुको_queue_entry_tail(wq_head, wq_entry);
	spin_unlock_irqrestore(&wq_head->lock, flags);
पूर्ण
EXPORT_SYMBOL(add_रुको_queue_exclusive);

व्योम add_रुको_queue_priority(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	अचिन्हित दीर्घ flags;

	wq_entry->flags |= WQ_FLAG_EXCLUSIVE | WQ_FLAG_PRIORITY;
	spin_lock_irqsave(&wq_head->lock, flags);
	__add_रुको_queue(wq_head, wq_entry);
	spin_unlock_irqrestore(&wq_head->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(add_रुको_queue_priority);

व्योम हटाओ_रुको_queue(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wq_head->lock, flags);
	__हटाओ_रुको_queue(wq_head, wq_entry);
	spin_unlock_irqrestore(&wq_head->lock, flags);
पूर्ण
EXPORT_SYMBOL(हटाओ_रुको_queue);

/*
 * Scan threshold to अवरोध रुको queue walk.
 * This allows a waker to take a अवरोध from holding the
 * रुको queue lock during the रुको queue walk.
 */
#घोषणा WAITQUEUE_WALK_BREAK_CNT 64

/*
 * The core wakeup function. Non-exclusive wakeups (nr_exclusive == 0) just
 * wake everything up. If it's an exclusive wakeup (nr_exclusive == small +ve
 * number) then we wake that number of exclusive tasks, and potentially all
 * the non-exclusive tasks. Normally, exclusive tasks will be at the end of
 * the list and any non-exclusive tasks will be woken first. A priority task
 * may be at the head of the list, and can consume the event without any other
 * tasks being woken.
 *
 * There are circumstances in which we can try to wake a task which has alपढ़ोy
 * started to run but is not in state TASK_RUNNING. try_to_wake_up() वापसs
 * zero in this (rare) हाल, and we handle it by continuing to scan the queue.
 */
अटल पूर्णांक __wake_up_common(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode,
			पूर्णांक nr_exclusive, पूर्णांक wake_flags, व्योम *key,
			रुको_queue_entry_t *bookmark)
अणु
	रुको_queue_entry_t *curr, *next;
	पूर्णांक cnt = 0;

	lockdep_निश्चित_held(&wq_head->lock);

	अगर (bookmark && (bookmark->flags & WQ_FLAG_BOOKMARK)) अणु
		curr = list_next_entry(bookmark, entry);

		list_del(&bookmark->entry);
		bookmark->flags = 0;
	पूर्ण अन्यथा
		curr = list_first_entry(&wq_head->head, रुको_queue_entry_t, entry);

	अगर (&curr->entry == &wq_head->head)
		वापस nr_exclusive;

	list_क्रम_each_entry_safe_from(curr, next, &wq_head->head, entry) अणु
		अचिन्हित flags = curr->flags;
		पूर्णांक ret;

		अगर (flags & WQ_FLAG_BOOKMARK)
			जारी;

		ret = curr->func(curr, mode, wake_flags, key);
		अगर (ret < 0)
			अवरोध;
		अगर (ret && (flags & WQ_FLAG_EXCLUSIVE) && !--nr_exclusive)
			अवरोध;

		अगर (bookmark && (++cnt > WAITQUEUE_WALK_BREAK_CNT) &&
				(&next->entry != &wq_head->head)) अणु
			bookmark->flags = WQ_FLAG_BOOKMARK;
			list_add_tail(&bookmark->entry, &next->entry);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस nr_exclusive;
पूर्ण

अटल व्योम __wake_up_common_lock(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode,
			पूर्णांक nr_exclusive, पूर्णांक wake_flags, व्योम *key)
अणु
	अचिन्हित दीर्घ flags;
	रुको_queue_entry_t bookmark;

	bookmark.flags = 0;
	bookmark.निजी = शून्य;
	bookmark.func = शून्य;
	INIT_LIST_HEAD(&bookmark.entry);

	करो अणु
		spin_lock_irqsave(&wq_head->lock, flags);
		nr_exclusive = __wake_up_common(wq_head, mode, nr_exclusive,
						wake_flags, key, &bookmark);
		spin_unlock_irqrestore(&wq_head->lock, flags);
	पूर्ण जबतक (bookmark.flags & WQ_FLAG_BOOKMARK);
पूर्ण

/**
 * __wake_up - wake up thपढ़ोs blocked on a रुकोqueue.
 * @wq_head: the रुकोqueue
 * @mode: which thपढ़ोs
 * @nr_exclusive: how many wake-one or wake-many thपढ़ोs to wake up
 * @key: is directly passed to the wakeup function
 *
 * If this function wakes up a task, it executes a full memory barrier beक्रमe
 * accessing the task state.
 */
व्योम __wake_up(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode,
			पूर्णांक nr_exclusive, व्योम *key)
अणु
	__wake_up_common_lock(wq_head, mode, nr_exclusive, 0, key);
पूर्ण
EXPORT_SYMBOL(__wake_up);

/*
 * Same as __wake_up but called with the spinlock in रुको_queue_head_t held.
 */
व्योम __wake_up_locked(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode, पूर्णांक nr)
अणु
	__wake_up_common(wq_head, mode, nr, 0, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(__wake_up_locked);

व्योम __wake_up_locked_key(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode, व्योम *key)
अणु
	__wake_up_common(wq_head, mode, 1, 0, key, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(__wake_up_locked_key);

व्योम __wake_up_locked_key_bookmark(काष्ठा रुको_queue_head *wq_head,
		अचिन्हित पूर्णांक mode, व्योम *key, रुको_queue_entry_t *bookmark)
अणु
	__wake_up_common(wq_head, mode, 1, 0, key, bookmark);
पूर्ण
EXPORT_SYMBOL_GPL(__wake_up_locked_key_bookmark);

/**
 * __wake_up_sync_key - wake up thपढ़ोs blocked on a रुकोqueue.
 * @wq_head: the रुकोqueue
 * @mode: which thपढ़ोs
 * @key: opaque value to be passed to wakeup tarमाला_लो
 *
 * The sync wakeup dअगरfers that the waker knows that it will schedule
 * away soon, so जबतक the target thपढ़ो will be woken up, it will not
 * be migrated to another CPU - ie. the two thपढ़ोs are 'synchronized'
 * with each other. This can prevent needless bouncing between CPUs.
 *
 * On UP it can prevent extra preemption.
 *
 * If this function wakes up a task, it executes a full memory barrier beक्रमe
 * accessing the task state.
 */
व्योम __wake_up_sync_key(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode,
			व्योम *key)
अणु
	अगर (unlikely(!wq_head))
		वापस;

	__wake_up_common_lock(wq_head, mode, 1, WF_SYNC, key);
पूर्ण
EXPORT_SYMBOL_GPL(__wake_up_sync_key);

/**
 * __wake_up_locked_sync_key - wake up a thपढ़ो blocked on a locked रुकोqueue.
 * @wq_head: the रुकोqueue
 * @mode: which thपढ़ोs
 * @key: opaque value to be passed to wakeup tarमाला_लो
 *
 * The sync wakeup dअगरfers in that the waker knows that it will schedule
 * away soon, so जबतक the target thपढ़ो will be woken up, it will not
 * be migrated to another CPU - ie. the two thपढ़ोs are 'synchronized'
 * with each other. This can prevent needless bouncing between CPUs.
 *
 * On UP it can prevent extra preemption.
 *
 * If this function wakes up a task, it executes a full memory barrier beक्रमe
 * accessing the task state.
 */
व्योम __wake_up_locked_sync_key(काष्ठा रुको_queue_head *wq_head,
			       अचिन्हित पूर्णांक mode, व्योम *key)
अणु
        __wake_up_common(wq_head, mode, 1, WF_SYNC, key, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(__wake_up_locked_sync_key);

/*
 * __wake_up_sync - see __wake_up_sync_key()
 */
व्योम __wake_up_sync(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode)
अणु
	__wake_up_sync_key(wq_head, mode, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(__wake_up_sync);	/* For पूर्णांकernal use only */

/*
 * Note: we use "set_current_state()" _after_ the रुको-queue add,
 * because we need a memory barrier there on SMP, so that any
 * wake-function that tests क्रम the रुको-queue being active
 * will be guaranteed to see रुकोqueue addition _or_ subsequent
 * tests in this thपढ़ो will see the wakeup having taken place.
 *
 * The spin_unlock() itself is semi-permeable and only protects
 * one way (it only protects stuff inside the critical region and
 * stops them from bleeding out - it would still allow subsequent
 * loads to move पूर्णांकo the critical region).
 */
व्योम
prepare_to_रुको(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry, पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;

	wq_entry->flags &= ~WQ_FLAG_EXCLUSIVE;
	spin_lock_irqsave(&wq_head->lock, flags);
	अगर (list_empty(&wq_entry->entry))
		__add_रुको_queue(wq_head, wq_entry);
	set_current_state(state);
	spin_unlock_irqrestore(&wq_head->lock, flags);
पूर्ण
EXPORT_SYMBOL(prepare_to_रुको);

व्योम
prepare_to_रुको_exclusive(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry, पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;

	wq_entry->flags |= WQ_FLAG_EXCLUSIVE;
	spin_lock_irqsave(&wq_head->lock, flags);
	अगर (list_empty(&wq_entry->entry))
		__add_रुको_queue_entry_tail(wq_head, wq_entry);
	set_current_state(state);
	spin_unlock_irqrestore(&wq_head->lock, flags);
पूर्ण
EXPORT_SYMBOL(prepare_to_रुको_exclusive);

व्योम init_रुको_entry(काष्ठा रुको_queue_entry *wq_entry, पूर्णांक flags)
अणु
	wq_entry->flags = flags;
	wq_entry->निजी = current;
	wq_entry->func = स्वतःहटाओ_wake_function;
	INIT_LIST_HEAD(&wq_entry->entry);
पूर्ण
EXPORT_SYMBOL(init_रुको_entry);

दीर्घ prepare_to_रुको_event(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry, पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ ret = 0;

	spin_lock_irqsave(&wq_head->lock, flags);
	अगर (संकेत_pending_state(state, current)) अणु
		/*
		 * Exclusive रुकोer must not fail अगर it was selected by wakeup,
		 * it should "consume" the condition we were रुकोing क्रम.
		 *
		 * The caller will recheck the condition and वापस success अगर
		 * we were alपढ़ोy woken up, we can not miss the event because
		 * wakeup locks/unlocks the same wq_head->lock.
		 *
		 * But we need to ensure that set-condition + wakeup after that
		 * can't see us, it should wake up another exclusive रुकोer अगर
		 * we fail.
		 */
		list_del_init(&wq_entry->entry);
		ret = -ERESTARTSYS;
	पूर्ण अन्यथा अणु
		अगर (list_empty(&wq_entry->entry)) अणु
			अगर (wq_entry->flags & WQ_FLAG_EXCLUSIVE)
				__add_रुको_queue_entry_tail(wq_head, wq_entry);
			अन्यथा
				__add_रुको_queue(wq_head, wq_entry);
		पूर्ण
		set_current_state(state);
	पूर्ण
	spin_unlock_irqrestore(&wq_head->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(prepare_to_रुको_event);

/*
 * Note! These two रुको functions are entered with the
 * रुको-queue lock held (and पूर्णांकerrupts off in the _irq
 * हाल), so there is no race with testing the wakeup
 * condition in the caller beक्रमe they add the रुको
 * entry to the wake queue.
 */
पूर्णांक करो_रुको_पूर्णांकr(रुको_queue_head_t *wq, रुको_queue_entry_t *रुको)
अणु
	अगर (likely(list_empty(&रुको->entry)))
		__add_रुको_queue_entry_tail(wq, रुको);

	set_current_state(TASK_INTERRUPTIBLE);
	अगर (संकेत_pending(current))
		वापस -ERESTARTSYS;

	spin_unlock(&wq->lock);
	schedule();
	spin_lock(&wq->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(करो_रुको_पूर्णांकr);

पूर्णांक करो_रुको_पूर्णांकr_irq(रुको_queue_head_t *wq, रुको_queue_entry_t *रुको)
अणु
	अगर (likely(list_empty(&रुको->entry)))
		__add_रुको_queue_entry_tail(wq, रुको);

	set_current_state(TASK_INTERRUPTIBLE);
	अगर (संकेत_pending(current))
		वापस -ERESTARTSYS;

	spin_unlock_irq(&wq->lock);
	schedule();
	spin_lock_irq(&wq->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(करो_रुको_पूर्णांकr_irq);

/**
 * finish_रुको - clean up after रुकोing in a queue
 * @wq_head: रुकोqueue रुकोed on
 * @wq_entry: रुको descriptor
 *
 * Sets current thपढ़ो back to running state and हटाओs
 * the रुको descriptor from the given रुकोqueue अगर still
 * queued.
 */
व्योम finish_रुको(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	अचिन्हित दीर्घ flags;

	__set_current_state(TASK_RUNNING);
	/*
	 * We can check क्रम list emptiness outside the lock
	 * IFF:
	 *  - we use the "careful" check that verअगरies both
	 *    the next and prev poपूर्णांकers, so that there cannot
	 *    be any half-pending updates in progress on other
	 *    CPU's that we haven't seen yet (and that might
	 *    still change the stack area.
	 * and
	 *  - all other users take the lock (ie we can only
	 *    have _one_ other CPU that looks at or modअगरies
	 *    the list).
	 */
	अगर (!list_empty_careful(&wq_entry->entry)) अणु
		spin_lock_irqsave(&wq_head->lock, flags);
		list_del_init(&wq_entry->entry);
		spin_unlock_irqrestore(&wq_head->lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(finish_रुको);

पूर्णांक स्वतःहटाओ_wake_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	पूर्णांक ret = शेष_wake_function(wq_entry, mode, sync, key);

	अगर (ret)
		list_del_init_careful(&wq_entry->entry);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(स्वतःहटाओ_wake_function);

अटल अंतरभूत bool is_kthपढ़ो_should_stop(व्योम)
अणु
	वापस (current->flags & PF_KTHREAD) && kthपढ़ो_should_stop();
पूर्ण

/*
 * DEFINE_WAIT_FUNC(रुको, woken_wake_func);
 *
 * add_रुको_queue(&wq_head, &रुको);
 * क्रम (;;) अणु
 *     अगर (condition)
 *         अवरोध;
 *
 *     // in रुको_woken()			// in woken_wake_function()
 *
 *     p->state = mode;				wq_entry->flags |= WQ_FLAG_WOKEN;
 *     smp_mb(); // A				try_to_wake_up():
 *     अगर (!(wq_entry->flags & WQ_FLAG_WOKEN))	   <full barrier>
 *         schedule()				   अगर (p->state & mode)
 *     p->state = TASK_RUNNING;			      p->state = TASK_RUNNING;
 *     wq_entry->flags &= ~WQ_FLAG_WOKEN;	~~~~~~~~~~~~~~~~~~
 *     smp_mb(); // B				condition = true;
 * पूर्ण						smp_mb(); // C
 * हटाओ_रुको_queue(&wq_head, &रुको);		wq_entry->flags |= WQ_FLAG_WOKEN;
 */
दीर्घ रुको_woken(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, दीर्घ समयout)
अणु
	/*
	 * The below executes an smp_mb(), which matches with the full barrier
	 * executed by the try_to_wake_up() in woken_wake_function() such that
	 * either we see the store to wq_entry->flags in woken_wake_function()
	 * or woken_wake_function() sees our store to current->state.
	 */
	set_current_state(mode); /* A */
	अगर (!(wq_entry->flags & WQ_FLAG_WOKEN) && !is_kthपढ़ो_should_stop())
		समयout = schedule_समयout(समयout);
	__set_current_state(TASK_RUNNING);

	/*
	 * The below executes an smp_mb(), which matches with the smp_mb() (C)
	 * in woken_wake_function() such that either we see the रुको condition
	 * being true or the store to wq_entry->flags in woken_wake_function()
	 * follows ours in the coherence order.
	 */
	smp_store_mb(wq_entry->flags, wq_entry->flags & ~WQ_FLAG_WOKEN); /* B */

	वापस समयout;
पूर्ण
EXPORT_SYMBOL(रुको_woken);

पूर्णांक woken_wake_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	/* Pairs with the smp_store_mb() in रुको_woken(). */
	smp_mb(); /* C */
	wq_entry->flags |= WQ_FLAG_WOKEN;

	वापस शेष_wake_function(wq_entry, mode, sync, key);
पूर्ण
EXPORT_SYMBOL(woken_wake_function);
