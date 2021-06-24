<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "display/intel_frontbuffer.h"

#समावेश "i915_drv.h"
#समावेश "i915_gem_clflush.h"
#समावेश "i915_sw_fence_work.h"
#समावेश "i915_trace.h"

काष्ठा clflush अणु
	काष्ठा dma_fence_work base;
	काष्ठा drm_i915_gem_object *obj;
पूर्ण;

अटल व्योम __करो_clflush(काष्ठा drm_i915_gem_object *obj)
अणु
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	drm_clflush_sg(obj->mm.pages);

	i915_gem_object_flush_frontbuffer(obj, ORIGIN_CPU);
पूर्ण

अटल पूर्णांक clflush_work(काष्ठा dma_fence_work *base)
अणु
	काष्ठा clflush *clflush = container_of(base, typeof(*clflush), base);

	__करो_clflush(clflush->obj);

	वापस 0;
पूर्ण

अटल व्योम clflush_release(काष्ठा dma_fence_work *base)
अणु
	काष्ठा clflush *clflush = container_of(base, typeof(*clflush), base);

	i915_gem_object_unpin_pages(clflush->obj);
	i915_gem_object_put(clflush->obj);
पूर्ण

अटल स्थिर काष्ठा dma_fence_work_ops clflush_ops = अणु
	.name = "clflush",
	.work = clflush_work,
	.release = clflush_release,
पूर्ण;

अटल काष्ठा clflush *clflush_work_create(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा clflush *clflush;

	GEM_BUG_ON(!obj->cache_dirty);

	clflush = kदो_स्मृति(माप(*clflush), GFP_KERNEL);
	अगर (!clflush)
		वापस शून्य;

	अगर (__i915_gem_object_get_pages(obj) < 0) अणु
		kमुक्त(clflush);
		वापस शून्य;
	पूर्ण

	dma_fence_work_init(&clflush->base, &clflush_ops);
	clflush->obj = i915_gem_object_get(obj); /* obj <-> clflush cycle */

	वापस clflush;
पूर्ण

bool i915_gem_clflush_object(काष्ठा drm_i915_gem_object *obj,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा clflush *clflush;

	निश्चित_object_held(obj);

	/*
	 * Stolen memory is always coherent with the GPU as it is explicitly
	 * marked as wc by the प्रणाली, or the प्रणाली is cache-coherent.
	 * Similarly, we only access काष्ठा pages through the CPU cache, so
	 * anything not backed by physical memory we consider to be always
	 * coherent and not need clflushing.
	 */
	अगर (!i915_gem_object_has_काष्ठा_page(obj)) अणु
		obj->cache_dirty = false;
		वापस false;
	पूर्ण

	/* If the GPU is snooping the contents of the CPU cache,
	 * we करो not need to manually clear the CPU cache lines.  However,
	 * the caches are only snooped when the render cache is
	 * flushed/invalidated.  As we always have to emit invalidations
	 * and flushes when moving पूर्णांकo and out of the RENDER करोमुख्य, correct
	 * snooping behaviour occurs naturally as the result of our करोमुख्य
	 * tracking.
	 */
	अगर (!(flags & I915_CLFLUSH_FORCE) &&
	    obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ)
		वापस false;

	trace_i915_gem_object_clflush(obj);

	clflush = शून्य;
	अगर (!(flags & I915_CLFLUSH_SYNC))
		clflush = clflush_work_create(obj);
	अगर (clflush) अणु
		i915_sw_fence_aरुको_reservation(&clflush->base.chain,
						obj->base.resv, शून्य, true,
						i915_fence_समयout(to_i915(obj->base.dev)),
						I915_FENCE_GFP);
		dma_resv_add_excl_fence(obj->base.resv, &clflush->base.dma);
		dma_fence_work_commit(&clflush->base);
	पूर्ण अन्यथा अगर (obj->mm.pages) अणु
		__करो_clflush(obj);
	पूर्ण अन्यथा अणु
		GEM_BUG_ON(obj->ग_लिखो_करोमुख्य != I915_GEM_DOMAIN_CPU);
	पूर्ण

	obj->cache_dirty = false;
	वापस true;
पूर्ण
