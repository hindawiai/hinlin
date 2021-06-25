<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/रुको_bit.h>

#समावेश "intel_runtime_pm.h"
#समावेश "intel_wakeref.h"

अटल व्योम rpm_get(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	wf->wakeref = पूर्णांकel_runसमय_pm_get(wf->rpm);
पूर्ण

अटल व्योम rpm_put(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	पूर्णांकel_wakeref_t wakeref = fetch_and_zero(&wf->wakeref);

	पूर्णांकel_runसमय_pm_put(wf->rpm, wakeref);
	INTEL_WAKEREF_BUG_ON(!wakeref);
पूर्ण

पूर्णांक __पूर्णांकel_wakeref_get_first(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	/*
	 * Treat get/put as dअगरferent subclasses, as we may need to run
	 * the put callback from under the shrinker and करो not want to
	 * cross-contanimate that callback with any extra work perक्रमmed
	 * upon acquiring the wakeref.
	 */
	mutex_lock_nested(&wf->mutex, SINGLE_DEPTH_NESTING);
	अगर (!atomic_पढ़ो(&wf->count)) अणु
		पूर्णांक err;

		rpm_get(wf);

		err = wf->ops->get(wf);
		अगर (unlikely(err)) अणु
			rpm_put(wf);
			mutex_unlock(&wf->mutex);
			वापस err;
		पूर्ण

		smp_mb__beक्रमe_atomic(); /* release wf->count */
	पूर्ण
	atomic_inc(&wf->count);
	mutex_unlock(&wf->mutex);

	INTEL_WAKEREF_BUG_ON(atomic_पढ़ो(&wf->count) <= 0);
	वापस 0;
पूर्ण

अटल व्योम ____पूर्णांकel_wakeref_put_last(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	INTEL_WAKEREF_BUG_ON(atomic_पढ़ो(&wf->count) <= 0);
	अगर (unlikely(!atomic_dec_and_test(&wf->count)))
		जाओ unlock;

	/* ops->put() must reschedule its own release on error/deferral */
	अगर (likely(!wf->ops->put(wf))) अणु
		rpm_put(wf);
		wake_up_var(&wf->wakeref);
	पूर्ण

unlock:
	mutex_unlock(&wf->mutex);
पूर्ण

व्योम __पूर्णांकel_wakeref_put_last(काष्ठा पूर्णांकel_wakeref *wf, अचिन्हित दीर्घ flags)
अणु
	INTEL_WAKEREF_BUG_ON(delayed_work_pending(&wf->work));

	/* Assume we are not in process context and so cannot sleep. */
	अगर (flags & INTEL_WAKEREF_PUT_ASYNC || !mutex_trylock(&wf->mutex)) अणु
		mod_delayed_work(प्रणाली_wq, &wf->work,
				 FIELD_GET(INTEL_WAKEREF_PUT_DELAY, flags));
		वापस;
	पूर्ण

	____पूर्णांकel_wakeref_put_last(wf);
पूर्ण

अटल व्योम __पूर्णांकel_wakeref_put_work(काष्ठा work_काष्ठा *wrk)
अणु
	काष्ठा पूर्णांकel_wakeref *wf = container_of(wrk, typeof(*wf), work.work);

	अगर (atomic_add_unless(&wf->count, -1, 1))
		वापस;

	mutex_lock(&wf->mutex);
	____पूर्णांकel_wakeref_put_last(wf);
पूर्ण

व्योम __पूर्णांकel_wakeref_init(काष्ठा पूर्णांकel_wakeref *wf,
			  काष्ठा पूर्णांकel_runसमय_pm *rpm,
			  स्थिर काष्ठा पूर्णांकel_wakeref_ops *ops,
			  काष्ठा पूर्णांकel_wakeref_lockclass *key)
अणु
	wf->rpm = rpm;
	wf->ops = ops;

	__mutex_init(&wf->mutex, "wakeref.mutex", &key->mutex);
	atomic_set(&wf->count, 0);
	wf->wakeref = 0;

	INIT_DELAYED_WORK(&wf->work, __पूर्णांकel_wakeref_put_work);
	lockdep_init_map(&wf->work.work.lockdep_map,
			 "wakeref.work", &key->work, 0);
पूर्ण

पूर्णांक पूर्णांकel_wakeref_रुको_क्रम_idle(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	पूर्णांक err;

	might_sleep();

	err = रुको_var_event_समाप्तable(&wf->wakeref,
				      !पूर्णांकel_wakeref_is_active(wf));
	अगर (err)
		वापस err;

	पूर्णांकel_wakeref_unlock_रुको(wf);
	वापस 0;
पूर्ण

अटल व्योम wakeref_स्वतः_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा पूर्णांकel_wakeref_स्वतः *wf = from_समयr(wf, t, समयr);
	पूर्णांकel_wakeref_t wakeref;
	अचिन्हित दीर्घ flags;

	अगर (!refcount_dec_and_lock_irqsave(&wf->count, &wf->lock, &flags))
		वापस;

	wakeref = fetch_and_zero(&wf->wakeref);
	spin_unlock_irqrestore(&wf->lock, flags);

	पूर्णांकel_runसमय_pm_put(wf->rpm, wakeref);
पूर्ण

व्योम पूर्णांकel_wakeref_स्वतः_init(काष्ठा पूर्णांकel_wakeref_स्वतः *wf,
			     काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	spin_lock_init(&wf->lock);
	समयr_setup(&wf->समयr, wakeref_स्वतः_समयout, 0);
	refcount_set(&wf->count, 0);
	wf->wakeref = 0;
	wf->rpm = rpm;
पूर्ण

व्योम पूर्णांकel_wakeref_स्वतः(काष्ठा पूर्णांकel_wakeref_स्वतः *wf, अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!समयout) अणु
		अगर (del_समयr_sync(&wf->समयr))
			wakeref_स्वतः_समयout(&wf->समयr);
		वापस;
	पूर्ण

	/* Our mission is that we only extend an alपढ़ोy active wakeref */
	निश्चित_rpm_wakelock_held(wf->rpm);

	अगर (!refcount_inc_not_zero(&wf->count)) अणु
		spin_lock_irqsave(&wf->lock, flags);
		अगर (!refcount_inc_not_zero(&wf->count)) अणु
			INTEL_WAKEREF_BUG_ON(wf->wakeref);
			wf->wakeref = पूर्णांकel_runसमय_pm_get_अगर_in_use(wf->rpm);
			refcount_set(&wf->count, 1);
		पूर्ण
		spin_unlock_irqrestore(&wf->lock, flags);
	पूर्ण

	/*
	 * If we extend a pending समयr, we will only get a single समयr
	 * callback and so need to cancel the local inc by running the
	 * elided callback to keep the wf->count balanced.
	 */
	अगर (mod_समयr(&wf->समयr, jअगरfies + समयout))
		wakeref_स्वतः_समयout(&wf->समयr);
पूर्ण

व्योम पूर्णांकel_wakeref_स्वतः_fini(काष्ठा पूर्णांकel_wakeref_स्वतः *wf)
अणु
	पूर्णांकel_wakeref_स्वतः(wf, 0);
	INTEL_WAKEREF_BUG_ON(wf->wakeref);
पूर्ण
