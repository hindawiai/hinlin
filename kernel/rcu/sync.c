<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * RCU-based infraकाष्ठाure क्रम lightweight पढ़ोer-ग_लिखोr locking
 *
 * Copyright (c) 2015, Red Hat, Inc.
 *
 * Author: Oleg Nesterov <oleg@redhat.com>
 */

#समावेश <linux/rcu_sync.h>
#समावेश <linux/sched.h>

क्रमागत अणु GP_IDLE = 0, GP_ENTER, GP_PASSED, GP_EXIT, GP_REPLAY पूर्ण;

#घोषणा	rss_lock	gp_रुको.lock

/**
 * rcu_sync_init() - Initialize an rcu_sync काष्ठाure
 * @rsp: Poपूर्णांकer to rcu_sync काष्ठाure to be initialized
 */
व्योम rcu_sync_init(काष्ठा rcu_sync *rsp)
अणु
	स_रखो(rsp, 0, माप(*rsp));
	init_रुकोqueue_head(&rsp->gp_रुको);
पूर्ण

/**
 * rcu_sync_enter_start - Force पढ़ोers onto slow path क्रम multiple updates
 * @rsp: Poपूर्णांकer to rcu_sync काष्ठाure to use क्रम synchronization
 *
 * Must be called after rcu_sync_init() and beक्रमe first use.
 *
 * Ensures rcu_sync_is_idle() वापसs false and rcu_sync_अणुenter,निकासपूर्ण()
 * pairs turn पूर्णांकo NO-OPs.
 */
व्योम rcu_sync_enter_start(काष्ठा rcu_sync *rsp)
अणु
	rsp->gp_count++;
	rsp->gp_state = GP_PASSED;
पूर्ण


अटल व्योम rcu_sync_func(काष्ठा rcu_head *rhp);

अटल व्योम rcu_sync_call(काष्ठा rcu_sync *rsp)
अणु
	call_rcu(&rsp->cb_head, rcu_sync_func);
पूर्ण

/**
 * rcu_sync_func() - Callback function managing पढ़ोer access to fastpath
 * @rhp: Poपूर्णांकer to rcu_head in rcu_sync काष्ठाure to use क्रम synchronization
 *
 * This function is passed to call_rcu() function by rcu_sync_enter() and
 * rcu_sync_निकास(), so that it is invoked after a grace period following the
 * that invocation of enter/निकास.
 *
 * If it is called by rcu_sync_enter() it संकेतs that all the पढ़ोers were
 * चयनed onto slow path.
 *
 * If it is called by rcu_sync_निकास() it takes action based on events that
 * have taken place in the meanसमय, so that बंदly spaced rcu_sync_enter()
 * and rcu_sync_निकास() pairs need not रुको क्रम a grace period.
 *
 * If another rcu_sync_enter() is invoked beक्रमe the grace period
 * ended, reset state to allow the next rcu_sync_निकास() to let the
 * पढ़ोers back onto their fastpaths (after a grace period).  If both
 * another rcu_sync_enter() and its matching rcu_sync_निकास() are invoked
 * beक्रमe the grace period ended, re-invoke call_rcu() on behalf of that
 * rcu_sync_निकास().  Otherwise, set all state back to idle so that पढ़ोers
 * can again use their fastpaths.
 */
अटल व्योम rcu_sync_func(काष्ठा rcu_head *rhp)
अणु
	काष्ठा rcu_sync *rsp = container_of(rhp, काष्ठा rcu_sync, cb_head);
	अचिन्हित दीर्घ flags;

	WARN_ON_ONCE(READ_ONCE(rsp->gp_state) == GP_IDLE);
	WARN_ON_ONCE(READ_ONCE(rsp->gp_state) == GP_PASSED);

	spin_lock_irqsave(&rsp->rss_lock, flags);
	अगर (rsp->gp_count) अणु
		/*
		 * We're at least a GP after the GP_IDLE->GP_ENTER transition.
		 */
		WRITE_ONCE(rsp->gp_state, GP_PASSED);
		wake_up_locked(&rsp->gp_रुको);
	पूर्ण अन्यथा अगर (rsp->gp_state == GP_REPLAY) अणु
		/*
		 * A new rcu_sync_निकास() has happened; requeue the callback to
		 * catch a later GP.
		 */
		WRITE_ONCE(rsp->gp_state, GP_EXIT);
		rcu_sync_call(rsp);
	पूर्ण अन्यथा अणु
		/*
		 * We're at least a GP after the last rcu_sync_निकास(); eveybody
		 * will now have observed the ग_लिखो side critical section.
		 * Let 'em rip!.
		 */
		WRITE_ONCE(rsp->gp_state, GP_IDLE);
	पूर्ण
	spin_unlock_irqrestore(&rsp->rss_lock, flags);
पूर्ण

/**
 * rcu_sync_enter() - Force पढ़ोers onto slowpath
 * @rsp: Poपूर्णांकer to rcu_sync काष्ठाure to use क्रम synchronization
 *
 * This function is used by updaters who need पढ़ोers to make use of
 * a slowpath during the update.  After this function वापसs, all
 * subsequent calls to rcu_sync_is_idle() will वापस false, which
 * tells पढ़ोers to stay off their fastpaths.  A later call to
 * rcu_sync_निकास() re-enables पढ़ोer slowpaths.
 *
 * When called in isolation, rcu_sync_enter() must रुको क्रम a grace
 * period, however, बंदly spaced calls to rcu_sync_enter() can
 * optimize away the grace-period रुको via a state machine implemented
 * by rcu_sync_enter(), rcu_sync_निकास(), and rcu_sync_func().
 */
व्योम rcu_sync_enter(काष्ठा rcu_sync *rsp)
अणु
	पूर्णांक gp_state;

	spin_lock_irq(&rsp->rss_lock);
	gp_state = rsp->gp_state;
	अगर (gp_state == GP_IDLE) अणु
		WRITE_ONCE(rsp->gp_state, GP_ENTER);
		WARN_ON_ONCE(rsp->gp_count);
		/*
		 * Note that we could simply करो rcu_sync_call(rsp) here and
		 * aव्योम the "if (gp_state == GP_IDLE)" block below.
		 *
		 * However, synchronize_rcu() can be faster अगर rcu_expedited
		 * or rcu_blocking_is_gp() is true.
		 *
		 * Another reason is that we can't रुको क्रम rcu callback अगर
		 * we are called at early boot समय but this shouldn't happen.
		 */
	पूर्ण
	rsp->gp_count++;
	spin_unlock_irq(&rsp->rss_lock);

	अगर (gp_state == GP_IDLE) अणु
		/*
		 * See the comment above, this simply करोes the "synchronous"
		 * call_rcu(rcu_sync_func) which करोes GP_ENTER -> GP_PASSED.
		 */
		synchronize_rcu();
		rcu_sync_func(&rsp->cb_head);
		/* Not really needed, रुको_event() would see GP_PASSED. */
		वापस;
	पूर्ण

	रुको_event(rsp->gp_रुको, READ_ONCE(rsp->gp_state) >= GP_PASSED);
पूर्ण

/**
 * rcu_sync_निकास() - Allow पढ़ोers back onto fast path after grace period
 * @rsp: Poपूर्णांकer to rcu_sync काष्ठाure to use क्रम synchronization
 *
 * This function is used by updaters who have completed, and can thereक्रमe
 * now allow पढ़ोers to make use of their fastpaths after a grace period
 * has elapsed.  After this grace period has completed, all subsequent
 * calls to rcu_sync_is_idle() will वापस true, which tells पढ़ोers that
 * they can once again use their fastpaths.
 */
व्योम rcu_sync_निकास(काष्ठा rcu_sync *rsp)
अणु
	WARN_ON_ONCE(READ_ONCE(rsp->gp_state) == GP_IDLE);
	WARN_ON_ONCE(READ_ONCE(rsp->gp_count) == 0);

	spin_lock_irq(&rsp->rss_lock);
	अगर (!--rsp->gp_count) अणु
		अगर (rsp->gp_state == GP_PASSED) अणु
			WRITE_ONCE(rsp->gp_state, GP_EXIT);
			rcu_sync_call(rsp);
		पूर्ण अन्यथा अगर (rsp->gp_state == GP_EXIT) अणु
			WRITE_ONCE(rsp->gp_state, GP_REPLAY);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&rsp->rss_lock);
पूर्ण

/**
 * rcu_sync_dtor() - Clean up an rcu_sync काष्ठाure
 * @rsp: Poपूर्णांकer to rcu_sync काष्ठाure to be cleaned up
 */
व्योम rcu_sync_dtor(काष्ठा rcu_sync *rsp)
अणु
	पूर्णांक gp_state;

	WARN_ON_ONCE(READ_ONCE(rsp->gp_count));
	WARN_ON_ONCE(READ_ONCE(rsp->gp_state) == GP_PASSED);

	spin_lock_irq(&rsp->rss_lock);
	अगर (rsp->gp_state == GP_REPLAY)
		WRITE_ONCE(rsp->gp_state, GP_EXIT);
	gp_state = rsp->gp_state;
	spin_unlock_irq(&rsp->rss_lock);

	अगर (gp_state != GP_IDLE) अणु
		rcu_barrier();
		WARN_ON_ONCE(rsp->gp_state != GP_IDLE);
	पूर्ण
पूर्ण
