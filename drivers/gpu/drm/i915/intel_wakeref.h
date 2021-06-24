<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_WAKEREF_H
#घोषणा INTEL_WAKEREF_H

#समावेश <linux/atomic.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>
#समावेश <linux/stackdepot.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG)
#घोषणा INTEL_WAKEREF_BUG_ON(expr) BUG_ON(expr)
#अन्यथा
#घोषणा INTEL_WAKEREF_BUG_ON(expr) BUILD_BUG_ON_INVALID(expr)
#पूर्ण_अगर

काष्ठा पूर्णांकel_runसमय_pm;
काष्ठा पूर्णांकel_wakeref;

प्रकार depot_stack_handle_t पूर्णांकel_wakeref_t;

काष्ठा पूर्णांकel_wakeref_ops अणु
	पूर्णांक (*get)(काष्ठा पूर्णांकel_wakeref *wf);
	पूर्णांक (*put)(काष्ठा पूर्णांकel_wakeref *wf);
पूर्ण;

काष्ठा पूर्णांकel_wakeref अणु
	atomic_t count;
	काष्ठा mutex mutex;

	पूर्णांकel_wakeref_t wakeref;

	काष्ठा पूर्णांकel_runसमय_pm *rpm;
	स्थिर काष्ठा पूर्णांकel_wakeref_ops *ops;

	काष्ठा delayed_work work;
पूर्ण;

काष्ठा पूर्णांकel_wakeref_lockclass अणु
	काष्ठा lock_class_key mutex;
	काष्ठा lock_class_key work;
पूर्ण;

व्योम __पूर्णांकel_wakeref_init(काष्ठा पूर्णांकel_wakeref *wf,
			  काष्ठा पूर्णांकel_runसमय_pm *rpm,
			  स्थिर काष्ठा पूर्णांकel_wakeref_ops *ops,
			  काष्ठा पूर्णांकel_wakeref_lockclass *key);
#घोषणा पूर्णांकel_wakeref_init(wf, rpm, ops) करो अणु				\
	अटल काष्ठा पूर्णांकel_wakeref_lockclass __key;			\
									\
	__पूर्णांकel_wakeref_init((wf), (rpm), (ops), &__key);		\
पूर्ण जबतक (0)

पूर्णांक __पूर्णांकel_wakeref_get_first(काष्ठा पूर्णांकel_wakeref *wf);
व्योम __पूर्णांकel_wakeref_put_last(काष्ठा पूर्णांकel_wakeref *wf, अचिन्हित दीर्घ flags);

/**
 * पूर्णांकel_wakeref_get: Acquire the wakeref
 * @wf: the wakeref
 *
 * Acquire a hold on the wakeref. The first user to करो so, will acquire
 * the runसमय pm wakeref and then call the @fn underneath the wakeref
 * mutex.
 *
 * Note that @fn is allowed to fail, in which हाल the runसमय-pm wakeref
 * will be released and the acquisition unwound, and an error reported.
 *
 * Returns: 0 अगर the wakeref was acquired successfully, or a negative error
 * code otherwise.
 */
अटल अंतरभूत पूर्णांक
पूर्णांकel_wakeref_get(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	might_sleep();
	अगर (unlikely(!atomic_inc_not_zero(&wf->count)))
		वापस __पूर्णांकel_wakeref_get_first(wf);

	वापस 0;
पूर्ण

/**
 * __पूर्णांकel_wakeref_get: Acquire the wakeref, again
 * @wf: the wakeref
 *
 * Increment the wakeref counter, only valid अगर it is alपढ़ोy held by
 * the caller.
 *
 * See पूर्णांकel_wakeref_get().
 */
अटल अंतरभूत व्योम
__पूर्णांकel_wakeref_get(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	INTEL_WAKEREF_BUG_ON(atomic_पढ़ो(&wf->count) <= 0);
	atomic_inc(&wf->count);
पूर्ण

/**
 * पूर्णांकel_wakeref_get_अगर_in_use: Acquire the wakeref
 * @wf: the wakeref
 *
 * Acquire a hold on the wakeref, but only अगर the wakeref is alपढ़ोy
 * active.
 *
 * Returns: true अगर the wakeref was acquired, false otherwise.
 */
अटल अंतरभूत bool
पूर्णांकel_wakeref_get_अगर_active(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	वापस atomic_inc_not_zero(&wf->count);
पूर्ण

क्रमागत अणु
	INTEL_WAKEREF_PUT_ASYNC_BIT = 0,
	__INTEL_WAKEREF_PUT_LAST_BIT__
पूर्ण;

/**
 * पूर्णांकel_wakeref_put_flags: Release the wakeref
 * @wf: the wakeref
 * @flags: control flags
 *
 * Release our hold on the wakeref. When there are no more users,
 * the runसमय pm wakeref will be released after the @fn callback is called
 * underneath the wakeref mutex.
 *
 * Note that @fn is allowed to fail, in which हाल the runसमय-pm wakeref
 * is retained and an error reported.
 *
 * Returns: 0 अगर the wakeref was released successfully, or a negative error
 * code otherwise.
 */
अटल अंतरभूत व्योम
__पूर्णांकel_wakeref_put(काष्ठा पूर्णांकel_wakeref *wf, अचिन्हित दीर्घ flags)
#घोषणा INTEL_WAKEREF_PUT_ASYNC BIT(INTEL_WAKEREF_PUT_ASYNC_BIT)
#घोषणा INTEL_WAKEREF_PUT_DELAY \
	GENMASK(BITS_PER_LONG - 1, __INTEL_WAKEREF_PUT_LAST_BIT__)
अणु
	INTEL_WAKEREF_BUG_ON(atomic_पढ़ो(&wf->count) <= 0);
	अगर (unlikely(!atomic_add_unless(&wf->count, -1, 1)))
		__पूर्णांकel_wakeref_put_last(wf, flags);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_wakeref_put(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	might_sleep();
	__पूर्णांकel_wakeref_put(wf, 0);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_wakeref_put_async(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	__पूर्णांकel_wakeref_put(wf, INTEL_WAKEREF_PUT_ASYNC);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_wakeref_put_delay(काष्ठा पूर्णांकel_wakeref *wf, अचिन्हित दीर्घ delay)
अणु
	__पूर्णांकel_wakeref_put(wf,
			    INTEL_WAKEREF_PUT_ASYNC |
			    FIELD_PREP(INTEL_WAKEREF_PUT_DELAY, delay));
पूर्ण

/**
 * पूर्णांकel_wakeref_lock: Lock the wakeref (mutex)
 * @wf: the wakeref
 *
 * Locks the wakeref to prevent it being acquired or released. New users
 * can still adjust the counter, but the wakeref itself (and callback)
 * cannot be acquired or released.
 */
अटल अंतरभूत व्योम
पूर्णांकel_wakeref_lock(काष्ठा पूर्णांकel_wakeref *wf)
	__acquires(wf->mutex)
अणु
	mutex_lock(&wf->mutex);
पूर्ण

/**
 * पूर्णांकel_wakeref_unlock: Unlock the wakeref
 * @wf: the wakeref
 *
 * Releases a previously acquired पूर्णांकel_wakeref_lock().
 */
अटल अंतरभूत व्योम
पूर्णांकel_wakeref_unlock(काष्ठा पूर्णांकel_wakeref *wf)
	__releases(wf->mutex)
अणु
	mutex_unlock(&wf->mutex);
पूर्ण

/**
 * पूर्णांकel_wakeref_unlock_रुको: Wait until the active callback is complete
 * @wf: the wakeref
 *
 * Waits क्रम the active callback (under the @wf->mutex or another CPU) is
 * complete.
 */
अटल अंतरभूत व्योम
पूर्णांकel_wakeref_unlock_रुको(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	mutex_lock(&wf->mutex);
	mutex_unlock(&wf->mutex);
	flush_delayed_work(&wf->work);
पूर्ण

/**
 * पूर्णांकel_wakeref_is_active: Query whether the wakeref is currently held
 * @wf: the wakeref
 *
 * Returns: true अगर the wakeref is currently held.
 */
अटल अंतरभूत bool
पूर्णांकel_wakeref_is_active(स्थिर काष्ठा पूर्णांकel_wakeref *wf)
अणु
	वापस READ_ONCE(wf->wakeref);
पूर्ण

/**
 * __पूर्णांकel_wakeref_defer_park: Defer the current park callback
 * @wf: the wakeref
 */
अटल अंतरभूत व्योम
__पूर्णांकel_wakeref_defer_park(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	lockdep_निश्चित_held(&wf->mutex);
	INTEL_WAKEREF_BUG_ON(atomic_पढ़ो(&wf->count));
	atomic_set_release(&wf->count, 1);
पूर्ण

/**
 * पूर्णांकel_wakeref_रुको_क्रम_idle: Wait until the wakeref is idle
 * @wf: the wakeref
 *
 * Wait क्रम the earlier asynchronous release of the wakeref. Note
 * this will रुको क्रम any third party as well, so make sure you only रुको
 * when you have control over the wakeref and trust no one अन्यथा is acquiring
 * it.
 *
 * Return: 0 on success, error code अगर समाप्तed.
 */
पूर्णांक पूर्णांकel_wakeref_रुको_क्रम_idle(काष्ठा पूर्णांकel_wakeref *wf);

काष्ठा पूर्णांकel_wakeref_स्वतः अणु
	काष्ठा पूर्णांकel_runसमय_pm *rpm;
	काष्ठा समयr_list समयr;
	पूर्णांकel_wakeref_t wakeref;
	spinlock_t lock;
	refcount_t count;
पूर्ण;

/**
 * पूर्णांकel_wakeref_स्वतः: Delay the runसमय-pm स्वतःsuspend
 * @wf: the wakeref
 * @समयout: relative समयout in jअगरfies
 *
 * The runसमय-pm core uses a suspend delay after the last wakeref
 * is released beक्रमe triggering runसमय suspend of the device. That
 * delay is configurable via sysfs with little regard to the device
 * अक्षरacteristics. Instead, we want to tune the स्वतःsuspend based on our
 * HW knowledge. पूर्णांकel_wakeref_स्वतः() delays the sleep by the supplied
 * समयout.
 *
 * Pass @समयout = 0 to cancel a previous स्वतःsuspend by executing the
 * suspend immediately.
 */
व्योम पूर्णांकel_wakeref_स्वतः(काष्ठा पूर्णांकel_wakeref_स्वतः *wf, अचिन्हित दीर्घ समयout);

व्योम पूर्णांकel_wakeref_स्वतः_init(काष्ठा पूर्णांकel_wakeref_स्वतः *wf,
			     काष्ठा पूर्णांकel_runसमय_pm *rpm);
व्योम पूर्णांकel_wakeref_स्वतः_fini(काष्ठा पूर्णांकel_wakeref_स्वतः *wf);

#पूर्ण_अगर /* INTEL_WAKEREF_H */
