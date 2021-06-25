<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश <linux/jअगरfies.h>

#समावेश <drm/drm_file.h>

#समावेश "i915_drv.h"
#समावेश "i915_gem_context.h"
#समावेश "i915_gem_ioctls.h"
#समावेश "i915_gem_object.h"

/*
 * 20ms is a fairly arbitrary limit (greater than the average frame समय)
 * chosen to prevent the CPU getting more than a frame ahead of the GPU
 * (when using lax throttling क्रम the frontbuffer). We also use it to
 * offer मुक्त GPU रुकोboosts क्रम severely congested workloads.
 */
#घोषणा DRM_I915_THROTTLE_JIFFIES msecs_to_jअगरfies(20)

/*
 * Throttle our rendering by रुकोing until the ring has completed our requests
 * emitted over 20 msec ago.
 *
 * Note that अगर we were to use the current jअगरfies each समय around the loop,
 * we wouldn't escape the function with any frames outstanding अगर the समय to
 * render a frame was over 20ms.
 *
 * This should get us reasonable parallelism between CPU and GPU but also
 * relatively low latency when blocking on a particular request to finish.
 */
पूर्णांक
i915_gem_throttle_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file)
अणु
	स्थिर अचिन्हित दीर्घ recent_enough = jअगरfies - DRM_I915_THROTTLE_JIFFIES;
	काष्ठा drm_i915_file_निजी *file_priv = file->driver_priv;
	काष्ठा i915_gem_context *ctx;
	अचिन्हित दीर्घ idx;
	दीर्घ ret;

	/* ABI: वापस -EIO अगर alपढ़ोy wedged */
	ret = पूर्णांकel_gt_terminally_wedged(&to_i915(dev)->gt);
	अगर (ret)
		वापस ret;

	rcu_पढ़ो_lock();
	xa_क्रम_each(&file_priv->context_xa, idx, ctx) अणु
		काष्ठा i915_gem_engines_iter it;
		काष्ठा पूर्णांकel_context *ce;

		अगर (!kref_get_unless_zero(&ctx->ref))
			जारी;
		rcu_पढ़ो_unlock();

		क्रम_each_gem_engine(ce,
				    i915_gem_context_lock_engines(ctx),
				    it) अणु
			काष्ठा i915_request *rq, *target = शून्य;

			अगर (!ce->समयline)
				जारी;

			mutex_lock(&ce->समयline->mutex);
			list_क्रम_each_entry_reverse(rq,
						    &ce->समयline->requests,
						    link) अणु
				अगर (i915_request_completed(rq))
					अवरोध;

				अगर (समय_after(rq->emitted_jअगरfies,
					       recent_enough))
					जारी;

				target = i915_request_get(rq);
				अवरोध;
			पूर्ण
			mutex_unlock(&ce->समयline->mutex);
			अगर (!target)
				जारी;

			ret = i915_request_रुको(target,
						I915_WAIT_INTERRUPTIBLE,
						MAX_SCHEDULE_TIMEOUT);
			i915_request_put(target);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		i915_gem_context_unlock_engines(ctx);
		i915_gem_context_put(ctx);

		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret < 0 ? ret : 0;
पूर्ण
