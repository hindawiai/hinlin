<शैली गुरु>
/*
 * Copyright (C) 2014 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित DRM_MODESET_LOCK_H_
#घोषणा DRM_MODESET_LOCK_H_

#समावेश <linux/ww_mutex.h>

काष्ठा drm_modeset_lock;

/**
 * काष्ठा drm_modeset_acquire_ctx - locking context (see ww_acquire_ctx)
 * @ww_ctx: base acquire ctx
 * @contended: used पूर्णांकernally क्रम -EDEADLK handling
 * @locked: list of held locks
 * @trylock_only: trylock mode used in atomic contexts/panic notअगरiers
 * @पूर्णांकerruptible: whether पूर्णांकerruptible locking should be used.
 *
 * Each thपढ़ो competing क्रम a set of locks must use one acquire
 * ctx.  And अगर any lock fxn वापसs -EDEADLK, it must backoff and
 * retry.
 */
काष्ठा drm_modeset_acquire_ctx अणु

	काष्ठा ww_acquire_ctx ww_ctx;

	/*
	 * Contended lock: अगर a lock is contended you should only call
	 * drm_modeset_backoff() which drops locks and slow-locks the
	 * contended lock.
	 */
	काष्ठा drm_modeset_lock *contended;

	/*
	 * list of held locks (drm_modeset_lock)
	 */
	काष्ठा list_head locked;

	/*
	 * Trylock mode, use only क्रम panic handlers!
	 */
	bool trylock_only;

	/* Perक्रमm पूर्णांकerruptible रुकोs on this context. */
	bool पूर्णांकerruptible;
पूर्ण;

/**
 * काष्ठा drm_modeset_lock - used क्रम locking modeset resources.
 * @mutex: resource locking
 * @head: used to hold its place on &drm_atomi_state.locked list when
 *    part of an atomic update
 *
 * Used क्रम locking CRTCs and other modeset resources.
 */
काष्ठा drm_modeset_lock अणु
	/*
	 * modeset lock
	 */
	काष्ठा ww_mutex mutex;

	/*
	 * Resources that are locked as part of an atomic update are added
	 * to a list (so we know what to unlock at the end).
	 */
	काष्ठा list_head head;
पूर्ण;

#घोषणा DRM_MODESET_ACQUIRE_INTERRUPTIBLE BIT(0)

व्योम drm_modeset_acquire_init(काष्ठा drm_modeset_acquire_ctx *ctx,
		uपूर्णांक32_t flags);
व्योम drm_modeset_acquire_fini(काष्ठा drm_modeset_acquire_ctx *ctx);
व्योम drm_modeset_drop_locks(काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक drm_modeset_backoff(काष्ठा drm_modeset_acquire_ctx *ctx);

व्योम drm_modeset_lock_init(काष्ठा drm_modeset_lock *lock);

/**
 * drm_modeset_lock_fini - cleanup lock
 * @lock: lock to cleanup
 */
अटल अंतरभूत व्योम drm_modeset_lock_fini(काष्ठा drm_modeset_lock *lock)
अणु
	WARN_ON(!list_empty(&lock->head));
पूर्ण

/**
 * drm_modeset_is_locked - equivalent to mutex_is_locked()
 * @lock: lock to check
 */
अटल अंतरभूत bool drm_modeset_is_locked(काष्ठा drm_modeset_lock *lock)
अणु
	वापस ww_mutex_is_locked(&lock->mutex);
पूर्ण

/**
 * drm_modeset_lock_निश्चित_held - equivalent to lockdep_निश्चित_held()
 * @lock: lock to check
 */
अटल अंतरभूत व्योम drm_modeset_lock_निश्चित_held(काष्ठा drm_modeset_lock *lock)
अणु
	lockdep_निश्चित_held(&lock->mutex.base);
पूर्ण

पूर्णांक drm_modeset_lock(काष्ठा drm_modeset_lock *lock,
		काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक __must_check drm_modeset_lock_single_पूर्णांकerruptible(काष्ठा drm_modeset_lock *lock);
व्योम drm_modeset_unlock(काष्ठा drm_modeset_lock *lock);

काष्ठा drm_device;
काष्ठा drm_crtc;
काष्ठा drm_plane;

व्योम drm_modeset_lock_all(काष्ठा drm_device *dev);
व्योम drm_modeset_unlock_all(काष्ठा drm_device *dev);
व्योम drm_warn_on_modeset_not_all_locked(काष्ठा drm_device *dev);

पूर्णांक drm_modeset_lock_all_ctx(काष्ठा drm_device *dev,
			     काष्ठा drm_modeset_acquire_ctx *ctx);

/**
 * DRM_MODESET_LOCK_ALL_BEGIN - Helper to acquire modeset locks
 * @dev: drm device
 * @ctx: local modeset acquire context, will be dereferenced
 * @flags: DRM_MODESET_ACQUIRE_* flags to pass to drm_modeset_acquire_init()
 * @ret: local ret/err/etc variable to track error status
 *
 * Use these macros to simplअगरy grabbing all modeset locks using a local
 * context. This has the advantage of reducing boilerplate, but also properly
 * checking वापस values where appropriate.
 *
 * Any code run between BEGIN and END will be holding the modeset locks.
 *
 * This must be paired with DRM_MODESET_LOCK_ALL_END(). We will jump back and
 * क्रमth between the labels on deadlock and error conditions.
 *
 * Drivers can acquire additional modeset locks. If any lock acquisition
 * fails, the control flow needs to jump to DRM_MODESET_LOCK_ALL_END() with
 * the @ret parameter containing the वापस value of drm_modeset_lock().
 *
 * Returns:
 * The only possible value of ret immediately after DRM_MODESET_LOCK_ALL_BEGIN()
 * is 0, so no error checking is necessary
 */
#घोषणा DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, flags, ret)		\
	अगर (!drm_drv_uses_atomic_modeset(dev))				\
		mutex_lock(&dev->mode_config.mutex);			\
	drm_modeset_acquire_init(&ctx, flags);				\
modeset_lock_retry:							\
	ret = drm_modeset_lock_all_ctx(dev, &ctx);			\
	अगर (ret)							\
		जाओ modeset_lock_fail;

/**
 * DRM_MODESET_LOCK_ALL_END - Helper to release and cleanup modeset locks
 * @dev: drm device
 * @ctx: local modeset acquire context, will be dereferenced
 * @ret: local ret/err/etc variable to track error status
 *
 * The other side of DRM_MODESET_LOCK_ALL_BEGIN(). It will bounce back to BEGIN
 * अगर ret is -EDEADLK.
 *
 * It's important that you use the same ret variable क्रम begin and end so
 * deadlock conditions are properly handled.
 *
 * Returns:
 * ret will be untouched unless it is -EDEADLK on entry. That means that अगर you
 * successfully acquire the locks, ret will be whatever your code sets it to. If
 * there is a deadlock or other failure with acquire or backoff, ret will be set
 * to that failure. In both of these हालs the code between BEGIN/END will not
 * be run, so the failure will reflect the inability to grab the locks.
 */
#घोषणा DRM_MODESET_LOCK_ALL_END(dev, ctx, ret)				\
modeset_lock_fail:							\
	अगर (ret == -EDEADLK) अणु						\
		ret = drm_modeset_backoff(&ctx);			\
		अगर (!ret)						\
			जाओ modeset_lock_retry;			\
	पूर्ण								\
	drm_modeset_drop_locks(&ctx);					\
	drm_modeset_acquire_fini(&ctx);					\
	अगर (!drm_drv_uses_atomic_modeset(dev))				\
		mutex_unlock(&dev->mode_config.mutex);

#पूर्ण_अगर /* DRM_MODESET_LOCK_H_ */
