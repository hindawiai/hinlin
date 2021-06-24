<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic रुको-क्रम-completion handler;
 *
 * It dअगरfers from semaphores in that their शेष हाल is the opposite,
 * रुको_क्रम_completion शेष blocks whereas semaphore शेष non-block. The
 * पूर्णांकerface also makes it easy to 'complete' multiple रुकोing thपढ़ोs,
 * something which isn't entirely natural क्रम semaphores.
 *
 * But more importantly, the primitive करोcuments the usage. Semaphores would
 * typically be used क्रम exclusion which gives rise to priority inversion.
 * Waiting क्रम completion is a typically sync poपूर्णांक, but not an exclusion poपूर्णांक.
 */
#समावेश "sched.h"

/**
 * complete: - संकेतs a single thपढ़ो रुकोing on this completion
 * @x:  holds the state of this particular completion
 *
 * This will wake up a single thपढ़ो रुकोing on this completion. Thपढ़ोs will be
 * awakened in the same order in which they were queued.
 *
 * See also complete_all(), रुको_क्रम_completion() and related routines.
 *
 * If this function wakes up a task, it executes a full memory barrier beक्रमe
 * accessing the task state.
 */
व्योम complete(काष्ठा completion *x)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&x->रुको.lock, flags);

	अगर (x->करोne != अच_पूर्णांक_उच्च)
		x->करोne++;
	swake_up_locked(&x->रुको);
	raw_spin_unlock_irqrestore(&x->रुको.lock, flags);
पूर्ण
EXPORT_SYMBOL(complete);

/**
 * complete_all: - संकेतs all thपढ़ोs रुकोing on this completion
 * @x:  holds the state of this particular completion
 *
 * This will wake up all thपढ़ोs रुकोing on this particular completion event.
 *
 * If this function wakes up a task, it executes a full memory barrier beक्रमe
 * accessing the task state.
 *
 * Since complete_all() sets the completion of @x permanently to करोne
 * to allow multiple रुकोers to finish, a call to reinit_completion()
 * must be used on @x अगर @x is to be used again. The code must make
 * sure that all रुकोers have woken and finished beक्रमe reinitializing
 * @x. Also note that the function completion_करोne() can not be used
 * to know अगर there are still रुकोers after complete_all() has been called.
 */
व्योम complete_all(काष्ठा completion *x)
अणु
	अचिन्हित दीर्घ flags;

	lockdep_निश्चित_RT_in_thपढ़ोed_ctx();

	raw_spin_lock_irqsave(&x->रुको.lock, flags);
	x->करोne = अच_पूर्णांक_उच्च;
	swake_up_all_locked(&x->रुको);
	raw_spin_unlock_irqrestore(&x->रुको.lock, flags);
पूर्ण
EXPORT_SYMBOL(complete_all);

अटल अंतरभूत दीर्घ __sched
करो_रुको_क्रम_common(काष्ठा completion *x,
		   दीर्घ (*action)(दीर्घ), दीर्घ समयout, पूर्णांक state)
अणु
	अगर (!x->करोne) अणु
		DECLARE_SWAITQUEUE(रुको);

		करो अणु
			अगर (संकेत_pending_state(state, current)) अणु
				समयout = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			__prepare_to_sरुको(&x->रुको, &रुको);
			__set_current_state(state);
			raw_spin_unlock_irq(&x->रुको.lock);
			समयout = action(समयout);
			raw_spin_lock_irq(&x->रुको.lock);
		पूर्ण जबतक (!x->करोne && समयout);
		__finish_sरुको(&x->रुको, &रुको);
		अगर (!x->करोne)
			वापस समयout;
	पूर्ण
	अगर (x->करोne != अच_पूर्णांक_उच्च)
		x->करोne--;
	वापस समयout ?: 1;
पूर्ण

अटल अंतरभूत दीर्घ __sched
__रुको_क्रम_common(काष्ठा completion *x,
		  दीर्घ (*action)(दीर्घ), दीर्घ समयout, पूर्णांक state)
अणु
	might_sleep();

	complete_acquire(x);

	raw_spin_lock_irq(&x->रुको.lock);
	समयout = करो_रुको_क्रम_common(x, action, समयout, state);
	raw_spin_unlock_irq(&x->रुको.lock);

	complete_release(x);

	वापस समयout;
पूर्ण

अटल दीर्घ __sched
रुको_क्रम_common(काष्ठा completion *x, दीर्घ समयout, पूर्णांक state)
अणु
	वापस __रुको_क्रम_common(x, schedule_समयout, समयout, state);
पूर्ण

अटल दीर्घ __sched
रुको_क्रम_common_io(काष्ठा completion *x, दीर्घ समयout, पूर्णांक state)
अणु
	वापस __रुको_क्रम_common(x, io_schedule_समयout, समयout, state);
पूर्ण

/**
 * रुको_क्रम_completion: - रुकोs क्रम completion of a task
 * @x:  holds the state of this particular completion
 *
 * This रुकोs to be संकेतed क्रम completion of a specअगरic task. It is NOT
 * पूर्णांकerruptible and there is no समयout.
 *
 * See also similar routines (i.e. रुको_क्रम_completion_समयout()) with समयout
 * and पूर्णांकerrupt capability. Also see complete().
 */
व्योम __sched रुको_क्रम_completion(काष्ठा completion *x)
अणु
	रुको_क्रम_common(x, MAX_SCHEDULE_TIMEOUT, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion);

/**
 * रुको_क्रम_completion_समयout: - रुकोs क्रम completion of a task (w/समयout)
 * @x:  holds the state of this particular completion
 * @समयout:  समयout value in jअगरfies
 *
 * This रुकोs क्रम either a completion of a specअगरic task to be संकेतed or क्रम a
 * specअगरied समयout to expire. The समयout is in jअगरfies. It is not
 * पूर्णांकerruptible.
 *
 * Return: 0 अगर समयd out, and positive (at least 1, or number of jअगरfies left
 * till समयout) अगर completed.
 */
अचिन्हित दीर्घ __sched
रुको_क्रम_completion_समयout(काष्ठा completion *x, अचिन्हित दीर्घ समयout)
अणु
	वापस रुको_क्रम_common(x, समयout, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion_समयout);

/**
 * रुको_क्रम_completion_io: - रुकोs क्रम completion of a task
 * @x:  holds the state of this particular completion
 *
 * This रुकोs to be संकेतed क्रम completion of a specअगरic task. It is NOT
 * पूर्णांकerruptible and there is no समयout. The caller is accounted as रुकोing
 * क्रम IO (which traditionally means blkio only).
 */
व्योम __sched रुको_क्रम_completion_io(काष्ठा completion *x)
अणु
	रुको_क्रम_common_io(x, MAX_SCHEDULE_TIMEOUT, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion_io);

/**
 * रुको_क्रम_completion_io_समयout: - रुकोs क्रम completion of a task (w/समयout)
 * @x:  holds the state of this particular completion
 * @समयout:  समयout value in jअगरfies
 *
 * This रुकोs क्रम either a completion of a specअगरic task to be संकेतed or क्रम a
 * specअगरied समयout to expire. The समयout is in jअगरfies. It is not
 * पूर्णांकerruptible. The caller is accounted as रुकोing क्रम IO (which traditionally
 * means blkio only).
 *
 * Return: 0 अगर समयd out, and positive (at least 1, or number of jअगरfies left
 * till समयout) अगर completed.
 */
अचिन्हित दीर्घ __sched
रुको_क्रम_completion_io_समयout(काष्ठा completion *x, अचिन्हित दीर्घ समयout)
अणु
	वापस रुको_क्रम_common_io(x, समयout, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion_io_समयout);

/**
 * रुको_क्रम_completion_पूर्णांकerruptible: - रुकोs क्रम completion of a task (w/पूर्णांकr)
 * @x:  holds the state of this particular completion
 *
 * This रुकोs क्रम completion of a specअगरic task to be संकेतed. It is
 * पूर्णांकerruptible.
 *
 * Return: -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर completed.
 */
पूर्णांक __sched रुको_क्रम_completion_पूर्णांकerruptible(काष्ठा completion *x)
अणु
	दीर्घ t = रुको_क्रम_common(x, MAX_SCHEDULE_TIMEOUT, TASK_INTERRUPTIBLE);
	अगर (t == -ERESTARTSYS)
		वापस t;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion_पूर्णांकerruptible);

/**
 * रुको_क्रम_completion_पूर्णांकerruptible_समयout: - रुकोs क्रम completion (w/(to,पूर्णांकr))
 * @x:  holds the state of this particular completion
 * @समयout:  समयout value in jअगरfies
 *
 * This रुकोs क्रम either a completion of a specअगरic task to be संकेतed or क्रम a
 * specअगरied समयout to expire. It is पूर्णांकerruptible. The समयout is in jअगरfies.
 *
 * Return: -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर समयd out, positive (at least 1,
 * or number of jअगरfies left till समयout) अगर completed.
 */
दीर्घ __sched
रुको_क्रम_completion_पूर्णांकerruptible_समयout(काष्ठा completion *x,
					  अचिन्हित दीर्घ समयout)
अणु
	वापस रुको_क्रम_common(x, समयout, TASK_INTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion_पूर्णांकerruptible_समयout);

/**
 * रुको_क्रम_completion_समाप्तable: - रुकोs क्रम completion of a task (समाप्तable)
 * @x:  holds the state of this particular completion
 *
 * This रुकोs to be संकेतed क्रम completion of a specअगरic task. It can be
 * पूर्णांकerrupted by a समाप्त संकेत.
 *
 * Return: -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर completed.
 */
पूर्णांक __sched रुको_क्रम_completion_समाप्तable(काष्ठा completion *x)
अणु
	दीर्घ t = रुको_क्रम_common(x, MAX_SCHEDULE_TIMEOUT, TASK_KILLABLE);
	अगर (t == -ERESTARTSYS)
		वापस t;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion_समाप्तable);

/**
 * रुको_क्रम_completion_समाप्तable_समयout: - रुकोs क्रम completion of a task (w/(to,समाप्तable))
 * @x:  holds the state of this particular completion
 * @समयout:  समयout value in jअगरfies
 *
 * This रुकोs क्रम either a completion of a specअगरic task to be
 * संकेतed or क्रम a specअगरied समयout to expire. It can be
 * पूर्णांकerrupted by a समाप्त संकेत. The समयout is in jअगरfies.
 *
 * Return: -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर समयd out, positive (at least 1,
 * or number of jअगरfies left till समयout) अगर completed.
 */
दीर्घ __sched
रुको_क्रम_completion_समाप्तable_समयout(काष्ठा completion *x,
				     अचिन्हित दीर्घ समयout)
अणु
	वापस रुको_क्रम_common(x, समयout, TASK_KILLABLE);
पूर्ण
EXPORT_SYMBOL(रुको_क्रम_completion_समाप्तable_समयout);

/**
 *	try_रुको_क्रम_completion - try to decrement a completion without blocking
 *	@x:	completion काष्ठाure
 *
 *	Return: 0 अगर a decrement cannot be करोne without blocking
 *		 1 अगर a decrement succeeded.
 *
 *	If a completion is being used as a counting completion,
 *	attempt to decrement the counter without blocking. This
 *	enables us to aव्योम रुकोing अगर the resource the completion
 *	is protecting is not available.
 */
bool try_रुको_क्रम_completion(काष्ठा completion *x)
अणु
	अचिन्हित दीर्घ flags;
	bool ret = true;

	/*
	 * Since x->करोne will need to be locked only
	 * in the non-blocking हाल, we check x->करोne
	 * first without taking the lock so we can
	 * वापस early in the blocking हाल.
	 */
	अगर (!READ_ONCE(x->करोne))
		वापस false;

	raw_spin_lock_irqsave(&x->रुको.lock, flags);
	अगर (!x->करोne)
		ret = false;
	अन्यथा अगर (x->करोne != अच_पूर्णांक_उच्च)
		x->करोne--;
	raw_spin_unlock_irqrestore(&x->रुको.lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(try_रुको_क्रम_completion);

/**
 *	completion_करोne - Test to see अगर a completion has any रुकोers
 *	@x:	completion काष्ठाure
 *
 *	Return: 0 अगर there are रुकोers (रुको_क्रम_completion() in progress)
 *		 1 अगर there are no रुकोers.
 *
 *	Note, this will always वापस true अगर complete_all() was called on @X.
 */
bool completion_करोne(काष्ठा completion *x)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!READ_ONCE(x->करोne))
		वापस false;

	/*
	 * If ->करोne, we need to रुको क्रम complete() to release ->रुको.lock
	 * otherwise we can end up मुक्तing the completion beक्रमe complete()
	 * is करोne referencing it.
	 */
	raw_spin_lock_irqsave(&x->रुको.lock, flags);
	raw_spin_unlock_irqrestore(&x->रुको.lock, flags);
	वापस true;
पूर्ण
EXPORT_SYMBOL(completion_करोne);
