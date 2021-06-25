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

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_modeset_lock.h>

/**
 * DOC: kms locking
 *
 * As KMS moves toward more fine grained locking, and atomic ioctl where
 * userspace can indirectly control locking order, it becomes necessary
 * to use &ww_mutex and acquire-contexts to aव्योम deadlocks.  But because
 * the locking is more distributed around the driver code, we want a bit
 * of extra utility/tracking out of our acquire-ctx.  This is provided
 * by &काष्ठा drm_modeset_lock and &काष्ठा drm_modeset_acquire_ctx.
 *
 * For basic principles of &ww_mutex, see: Documentation/locking/ww-mutex-design.rst
 *
 * The basic usage pattern is to::
 *
 *     drm_modeset_acquire_init(ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE)
 *     retry:
 *     क्रमeach (lock in अक्रमom_ordered_set_of_locks) अणु
 *         ret = drm_modeset_lock(lock, ctx)
 *         अगर (ret == -EDEADLK) अणु
 *             ret = drm_modeset_backoff(ctx);
 *             अगर (!ret)
 *                 जाओ retry;
 *         पूर्ण
 *         अगर (ret)
 *             जाओ out;
 *     पूर्ण
 *     ... करो stuff ...
 *     out:
 *     drm_modeset_drop_locks(ctx);
 *     drm_modeset_acquire_fini(ctx);
 *
 * For convenience this control flow is implemented in
 * DRM_MODESET_LOCK_ALL_BEGIN() and DRM_MODESET_LOCK_ALL_END() क्रम the हाल
 * where all modeset locks need to be taken through drm_modeset_lock_all_ctx().
 *
 * If all that is needed is a single modeset lock, then the &काष्ठा
 * drm_modeset_acquire_ctx is not needed and the locking can be simplअगरied
 * by passing a शून्य instead of ctx in the drm_modeset_lock() call or
 * calling  drm_modeset_lock_single_पूर्णांकerruptible(). To unlock afterwards
 * call drm_modeset_unlock().
 *
 * On top of these per-object locks using &ww_mutex there's also an overall
 * &drm_mode_config.mutex, क्रम protecting everything अन्यथा. Mostly this means
 * probe state of connectors, and preventing hotplug add/removal of connectors.
 *
 * Finally there's a bunch of dedicated locks to protect drm core पूर्णांकernal
 * lists and lookup data काष्ठाures.
 */

अटल DEFINE_WW_CLASS(crtc_ww_class);

/**
 * drm_modeset_lock_all - take all modeset locks
 * @dev: DRM device
 *
 * This function takes all modeset locks, suitable where a more fine-grained
 * scheme isn't (yet) implemented. Locks must be dropped by calling the
 * drm_modeset_unlock_all() function.
 *
 * This function is deprecated. It allocates a lock acquisition context and
 * stores it in &drm_device.mode_config. This facilitate conversion of
 * existing code because it हटाओs the need to manually deal with the
 * acquisition context, but it is also brittle because the context is global
 * and care must be taken not to nest calls. New code should use the
 * drm_modeset_lock_all_ctx() function and pass in the context explicitly.
 */
व्योम drm_modeset_lock_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_modeset_acquire_ctx *ctx;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL | __GFP_NOFAIL);
	अगर (WARN_ON(!ctx))
		वापस;

	mutex_lock(&config->mutex);

	drm_modeset_acquire_init(ctx, 0);

retry:
	ret = drm_modeset_lock_all_ctx(dev, ctx);
	अगर (ret < 0) अणु
		अगर (ret == -EDEADLK) अणु
			drm_modeset_backoff(ctx);
			जाओ retry;
		पूर्ण

		drm_modeset_acquire_fini(ctx);
		kमुक्त(ctx);
		वापस;
	पूर्ण
	ww_acquire_करोne(&ctx->ww_ctx);

	WARN_ON(config->acquire_ctx);

	/*
	 * We hold the locks now, so it is safe to stash the acquisition
	 * context क्रम drm_modeset_unlock_all().
	 */
	config->acquire_ctx = ctx;

	drm_warn_on_modeset_not_all_locked(dev);
पूर्ण
EXPORT_SYMBOL(drm_modeset_lock_all);

/**
 * drm_modeset_unlock_all - drop all modeset locks
 * @dev: DRM device
 *
 * This function drops all modeset locks taken by a previous call to the
 * drm_modeset_lock_all() function.
 *
 * This function is deprecated. It uses the lock acquisition context stored
 * in &drm_device.mode_config. This facilitates conversion of existing
 * code because it हटाओs the need to manually deal with the acquisition
 * context, but it is also brittle because the context is global and care must
 * be taken not to nest calls. New code should pass the acquisition context
 * directly to the drm_modeset_drop_locks() function.
 */
व्योम drm_modeset_unlock_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_modeset_acquire_ctx *ctx = config->acquire_ctx;

	अगर (WARN_ON(!ctx))
		वापस;

	config->acquire_ctx = शून्य;
	drm_modeset_drop_locks(ctx);
	drm_modeset_acquire_fini(ctx);

	kमुक्त(ctx);

	mutex_unlock(&dev->mode_config.mutex);
पूर्ण
EXPORT_SYMBOL(drm_modeset_unlock_all);

/**
 * drm_warn_on_modeset_not_all_locked - check that all modeset locks are locked
 * @dev: device
 *
 * Useful as a debug निश्चित.
 */
व्योम drm_warn_on_modeset_not_all_locked(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_crtc *crtc;

	/* Locking is currently fubar in the panic handler. */
	अगर (oops_in_progress)
		वापस;

	drm_क्रम_each_crtc(crtc, dev)
		WARN_ON(!drm_modeset_is_locked(&crtc->mutex));

	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
	WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));
पूर्ण
EXPORT_SYMBOL(drm_warn_on_modeset_not_all_locked);

/**
 * drm_modeset_acquire_init - initialize acquire context
 * @ctx: the acquire context
 * @flags: 0 or %DRM_MODESET_ACQUIRE_INTERRUPTIBLE
 *
 * When passing %DRM_MODESET_ACQUIRE_INTERRUPTIBLE to @flags,
 * all calls to drm_modeset_lock() will perक्रमm an पूर्णांकerruptible
 * रुको.
 */
व्योम drm_modeset_acquire_init(काष्ठा drm_modeset_acquire_ctx *ctx,
		uपूर्णांक32_t flags)
अणु
	स_रखो(ctx, 0, माप(*ctx));
	ww_acquire_init(&ctx->ww_ctx, &crtc_ww_class);
	INIT_LIST_HEAD(&ctx->locked);

	अगर (flags & DRM_MODESET_ACQUIRE_INTERRUPTIBLE)
		ctx->पूर्णांकerruptible = true;
पूर्ण
EXPORT_SYMBOL(drm_modeset_acquire_init);

/**
 * drm_modeset_acquire_fini - cleanup acquire context
 * @ctx: the acquire context
 */
व्योम drm_modeset_acquire_fini(काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	ww_acquire_fini(&ctx->ww_ctx);
पूर्ण
EXPORT_SYMBOL(drm_modeset_acquire_fini);

/**
 * drm_modeset_drop_locks - drop all locks
 * @ctx: the acquire context
 *
 * Drop all locks currently held against this acquire context.
 */
व्योम drm_modeset_drop_locks(काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	WARN_ON(ctx->contended);
	जबतक (!list_empty(&ctx->locked)) अणु
		काष्ठा drm_modeset_lock *lock;

		lock = list_first_entry(&ctx->locked,
				काष्ठा drm_modeset_lock, head);

		drm_modeset_unlock(lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_modeset_drop_locks);

अटल अंतरभूत पूर्णांक modeset_lock(काष्ठा drm_modeset_lock *lock,
		काष्ठा drm_modeset_acquire_ctx *ctx,
		bool पूर्णांकerruptible, bool slow)
अणु
	पूर्णांक ret;

	WARN_ON(ctx->contended);

	अगर (ctx->trylock_only) अणु
		lockdep_निश्चित_held(&ctx->ww_ctx);

		अगर (!ww_mutex_trylock(&lock->mutex))
			वापस -EBUSY;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर (पूर्णांकerruptible && slow) अणु
		ret = ww_mutex_lock_slow_पूर्णांकerruptible(&lock->mutex, &ctx->ww_ctx);
	पूर्ण अन्यथा अगर (पूर्णांकerruptible) अणु
		ret = ww_mutex_lock_पूर्णांकerruptible(&lock->mutex, &ctx->ww_ctx);
	पूर्ण अन्यथा अगर (slow) अणु
		ww_mutex_lock_slow(&lock->mutex, &ctx->ww_ctx);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = ww_mutex_lock(&lock->mutex, &ctx->ww_ctx);
	पूर्ण
	अगर (!ret) अणु
		WARN_ON(!list_empty(&lock->head));
		list_add(&lock->head, &ctx->locked);
	पूर्ण अन्यथा अगर (ret == -EALREADY) अणु
		/* we alपढ़ोy hold the lock.. this is fine.  For atomic
		 * we will need to be able to drm_modeset_lock() things
		 * without having to keep track of what is alपढ़ोy locked
		 * or not.
		 */
		ret = 0;
	पूर्ण अन्यथा अगर (ret == -EDEADLK) अणु
		ctx->contended = lock;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * drm_modeset_backoff - deadlock aव्योमance backoff
 * @ctx: the acquire context
 *
 * If deadlock is detected (ie. drm_modeset_lock() वापसs -EDEADLK),
 * you must call this function to drop all currently held locks and
 * block until the contended lock becomes available.
 *
 * This function वापसs 0 on success, or -ERESTARTSYS अगर this context
 * is initialized with %DRM_MODESET_ACQUIRE_INTERRUPTIBLE and the
 * रुको has been पूर्णांकerrupted.
 */
पूर्णांक drm_modeset_backoff(काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_modeset_lock *contended = ctx->contended;

	ctx->contended = शून्य;

	अगर (WARN_ON(!contended))
		वापस 0;

	drm_modeset_drop_locks(ctx);

	वापस modeset_lock(contended, ctx, ctx->पूर्णांकerruptible, true);
पूर्ण
EXPORT_SYMBOL(drm_modeset_backoff);

/**
 * drm_modeset_lock_init - initialize lock
 * @lock: lock to init
 */
व्योम drm_modeset_lock_init(काष्ठा drm_modeset_lock *lock)
अणु
	ww_mutex_init(&lock->mutex, &crtc_ww_class);
	INIT_LIST_HEAD(&lock->head);
पूर्ण
EXPORT_SYMBOL(drm_modeset_lock_init);

/**
 * drm_modeset_lock - take modeset lock
 * @lock: lock to take
 * @ctx: acquire ctx
 *
 * If @ctx is not शून्य, then its ww acquire context is used and the
 * lock will be tracked by the context and can be released by calling
 * drm_modeset_drop_locks().  If -EDEADLK is वापसed, this means a
 * deadlock scenario has been detected and it is an error to attempt
 * to take any more locks without first calling drm_modeset_backoff().
 *
 * If the @ctx is not शून्य and initialized with
 * %DRM_MODESET_ACQUIRE_INTERRUPTIBLE, this function will fail with
 * -ERESTARTSYS when पूर्णांकerrupted.
 *
 * If @ctx is शून्य then the function call behaves like a normal,
 * unपूर्णांकerruptible non-nesting mutex_lock() call.
 */
पूर्णांक drm_modeset_lock(काष्ठा drm_modeset_lock *lock,
		काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	अगर (ctx)
		वापस modeset_lock(lock, ctx, ctx->पूर्णांकerruptible, false);

	ww_mutex_lock(&lock->mutex, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_modeset_lock);

/**
 * drm_modeset_lock_single_पूर्णांकerruptible - take a single modeset lock
 * @lock: lock to take
 *
 * This function behaves as drm_modeset_lock() with a शून्य context,
 * but perक्रमms पूर्णांकerruptible रुकोs.
 *
 * This function वापसs 0 on success, or -ERESTARTSYS when पूर्णांकerrupted.
 */
पूर्णांक drm_modeset_lock_single_पूर्णांकerruptible(काष्ठा drm_modeset_lock *lock)
अणु
	वापस ww_mutex_lock_पूर्णांकerruptible(&lock->mutex, शून्य);
पूर्ण
EXPORT_SYMBOL(drm_modeset_lock_single_पूर्णांकerruptible);

/**
 * drm_modeset_unlock - drop modeset lock
 * @lock: lock to release
 */
व्योम drm_modeset_unlock(काष्ठा drm_modeset_lock *lock)
अणु
	list_del_init(&lock->head);
	ww_mutex_unlock(&lock->mutex);
पूर्ण
EXPORT_SYMBOL(drm_modeset_unlock);

/**
 * drm_modeset_lock_all_ctx - take all modeset locks
 * @dev: DRM device
 * @ctx: lock acquisition context
 *
 * This function takes all modeset locks, suitable where a more fine-grained
 * scheme isn't (yet) implemented.
 *
 * Unlike drm_modeset_lock_all(), it करोesn't take the &drm_mode_config.mutex
 * since that lock isn't required क्रम modeset state changes. Callers which
 * need to grab that lock too need to करो so outside of the acquire context
 * @ctx.
 *
 * Locks acquired with this function should be released by calling the
 * drm_modeset_drop_locks() function on @ctx.
 *
 * See also: DRM_MODESET_LOCK_ALL_BEGIN() and DRM_MODESET_LOCK_ALL_END()
 *
 * Returns: 0 on success or a negative error-code on failure.
 */
पूर्णांक drm_modeset_lock_all_ctx(काष्ठा drm_device *dev,
			     काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_निजी_obj *privobj;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;
	पूर्णांक ret;

	ret = drm_modeset_lock(&dev->mode_config.connection_mutex, ctx);
	अगर (ret)
		वापस ret;

	drm_क्रम_each_crtc(crtc, dev) अणु
		ret = drm_modeset_lock(&crtc->mutex, ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	drm_क्रम_each_plane(plane, dev) अणु
		ret = drm_modeset_lock(&plane->mutex, ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	drm_क्रम_each_privobj(privobj, dev) अणु
		ret = drm_modeset_lock(&privobj->lock, ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_modeset_lock_all_ctx);
