<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश "display/intel_frontbuffer.h"
#समावेश "gt/intel_gt.h"

#समावेश "i915_drv.h"
#समावेश "i915_gem_clflush.h"
#समावेश "i915_gem_gtt.h"
#समावेश "i915_gem_ioctls.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_vma.h"
#समावेश "i915_gem_lmem.h"
#समावेश "i915_gem_mman.h"

अटल bool gpu_ग_लिखो_needs_clflush(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस !(obj->cache_level == I915_CACHE_NONE ||
		 obj->cache_level == I915_CACHE_WT);
पूर्ण

अटल व्योम
flush_ग_लिखो_करोमुख्य(काष्ठा drm_i915_gem_object *obj, अचिन्हित पूर्णांक flush_करोमुख्यs)
अणु
	काष्ठा i915_vma *vma;

	निश्चित_object_held(obj);

	अगर (!(obj->ग_लिखो_करोमुख्य & flush_करोमुख्यs))
		वापस;

	चयन (obj->ग_लिखो_करोमुख्य) अणु
	हाल I915_GEM_DOMAIN_GTT:
		spin_lock(&obj->vma.lock);
		क्रम_each_ggtt_vma(vma, obj) अणु
			अगर (i915_vma_unset_ggtt_ग_लिखो(vma))
				पूर्णांकel_gt_flush_ggtt_ग_लिखोs(vma->vm->gt);
		पूर्ण
		spin_unlock(&obj->vma.lock);

		i915_gem_object_flush_frontbuffer(obj, ORIGIN_CPU);
		अवरोध;

	हाल I915_GEM_DOMAIN_WC:
		wmb();
		अवरोध;

	हाल I915_GEM_DOMAIN_CPU:
		i915_gem_clflush_object(obj, I915_CLFLUSH_SYNC);
		अवरोध;

	हाल I915_GEM_DOMAIN_RENDER:
		अगर (gpu_ग_लिखो_needs_clflush(obj))
			obj->cache_dirty = true;
		अवरोध;
	पूर्ण

	obj->ग_लिखो_करोमुख्य = 0;
पूर्ण

अटल व्योम __i915_gem_object_flush_क्रम_display(काष्ठा drm_i915_gem_object *obj)
अणु
	/*
	 * We manually flush the CPU करोमुख्य so that we can override and
	 * क्रमce the flush क्रम the display, and perक्रमm it asyncrhonously.
	 */
	flush_ग_लिखो_करोमुख्य(obj, ~I915_GEM_DOMAIN_CPU);
	अगर (obj->cache_dirty)
		i915_gem_clflush_object(obj, I915_CLFLUSH_FORCE);
	obj->ग_लिखो_करोमुख्य = 0;
पूर्ण

व्योम i915_gem_object_flush_अगर_display(काष्ठा drm_i915_gem_object *obj)
अणु
	अगर (!i915_gem_object_is_framebuffer(obj))
		वापस;

	i915_gem_object_lock(obj, शून्य);
	__i915_gem_object_flush_क्रम_display(obj);
	i915_gem_object_unlock(obj);
पूर्ण

व्योम i915_gem_object_flush_अगर_display_locked(काष्ठा drm_i915_gem_object *obj)
अणु
	अगर (i915_gem_object_is_framebuffer(obj))
		__i915_gem_object_flush_क्रम_display(obj);
पूर्ण

/**
 * Moves a single object to the WC पढ़ो, and possibly ग_लिखो करोमुख्य.
 * @obj: object to act on
 * @ग_लिखो: ask क्रम ग_लिखो access or पढ़ो only
 *
 * This function वापसs when the move is complete, including रुकोing on
 * flushes to occur.
 */
पूर्णांक
i915_gem_object_set_to_wc_करोमुख्य(काष्ठा drm_i915_gem_object *obj, bool ग_लिखो)
अणु
	पूर्णांक ret;

	निश्चित_object_held(obj);

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   (ग_लिखो ? I915_WAIT_ALL : 0),
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (obj->ग_लिखो_करोमुख्य == I915_GEM_DOMAIN_WC)
		वापस 0;

	/* Flush and acquire obj->pages so that we are coherent through
	 * direct access in memory with previous cached ग_लिखोs through
	 * shmemfs and that our cache करोमुख्य tracking reमुख्यs valid.
	 * For example, अगर the obj->filp was moved to swap without us
	 * being notअगरied and releasing the pages, we would mistakenly
	 * जारी to assume that the obj reमुख्यed out of the CPU cached
	 * करोमुख्य.
	 */
	ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		वापस ret;

	flush_ग_लिखो_करोमुख्य(obj, ~I915_GEM_DOMAIN_WC);

	/* Serialise direct access to this object with the barriers क्रम
	 * coherent ग_लिखोs from the GPU, by effectively invalidating the
	 * WC करोमुख्य upon first access.
	 */
	अगर ((obj->पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_WC) == 0)
		mb();

	/* It should now be out of any other ग_लिखो करोमुख्यs, and we can update
	 * the करोमुख्य values क्रम our changes.
	 */
	GEM_BUG_ON((obj->ग_लिखो_करोमुख्य & ~I915_GEM_DOMAIN_WC) != 0);
	obj->पढ़ो_करोमुख्यs |= I915_GEM_DOMAIN_WC;
	अगर (ग_लिखो) अणु
		obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_WC;
		obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_WC;
		obj->mm.dirty = true;
	पूर्ण

	i915_gem_object_unpin_pages(obj);
	वापस 0;
पूर्ण

/**
 * Moves a single object to the GTT पढ़ो, and possibly ग_लिखो करोमुख्य.
 * @obj: object to act on
 * @ग_लिखो: ask क्रम ग_लिखो access or पढ़ो only
 *
 * This function वापसs when the move is complete, including रुकोing on
 * flushes to occur.
 */
पूर्णांक
i915_gem_object_set_to_gtt_करोमुख्य(काष्ठा drm_i915_gem_object *obj, bool ग_लिखो)
अणु
	पूर्णांक ret;

	निश्चित_object_held(obj);

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   (ग_लिखो ? I915_WAIT_ALL : 0),
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		वापस ret;

	अगर (obj->ग_लिखो_करोमुख्य == I915_GEM_DOMAIN_GTT)
		वापस 0;

	/* Flush and acquire obj->pages so that we are coherent through
	 * direct access in memory with previous cached ग_लिखोs through
	 * shmemfs and that our cache करोमुख्य tracking reमुख्यs valid.
	 * For example, अगर the obj->filp was moved to swap without us
	 * being notअगरied and releasing the pages, we would mistakenly
	 * जारी to assume that the obj reमुख्यed out of the CPU cached
	 * करोमुख्य.
	 */
	ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		वापस ret;

	flush_ग_लिखो_करोमुख्य(obj, ~I915_GEM_DOMAIN_GTT);

	/* Serialise direct access to this object with the barriers क्रम
	 * coherent ग_लिखोs from the GPU, by effectively invalidating the
	 * GTT करोमुख्य upon first access.
	 */
	अगर ((obj->पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_GTT) == 0)
		mb();

	/* It should now be out of any other ग_लिखो करोमुख्यs, and we can update
	 * the करोमुख्य values क्रम our changes.
	 */
	GEM_BUG_ON((obj->ग_लिखो_करोमुख्य & ~I915_GEM_DOMAIN_GTT) != 0);
	obj->पढ़ो_करोमुख्यs |= I915_GEM_DOMAIN_GTT;
	अगर (ग_लिखो) अणु
		काष्ठा i915_vma *vma;

		obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_GTT;
		obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_GTT;
		obj->mm.dirty = true;

		spin_lock(&obj->vma.lock);
		क्रम_each_ggtt_vma(vma, obj)
			अगर (i915_vma_is_bound(vma, I915_VMA_GLOBAL_BIND))
				i915_vma_set_ggtt_ग_लिखो(vma);
		spin_unlock(&obj->vma.lock);
	पूर्ण

	i915_gem_object_unpin_pages(obj);
	वापस 0;
पूर्ण

/**
 * Changes the cache-level of an object across all VMA.
 * @obj: object to act on
 * @cache_level: new cache level to set क्रम the object
 *
 * After this function वापसs, the object will be in the new cache-level
 * across all GTT and the contents of the backing storage will be coherent,
 * with respect to the new cache-level. In order to keep the backing storage
 * coherent क्रम all users, we only allow a single cache level to be set
 * globally on the object and prevent it from being changed whilst the
 * hardware is पढ़ोing from the object. That is अगर the object is currently
 * on the scanout it will be set to uncached (or equivalent display
 * cache coherency) and all non-MOCS GPU access will also be uncached so
 * that all direct access to the scanout reमुख्यs coherent.
 */
पूर्णांक i915_gem_object_set_cache_level(काष्ठा drm_i915_gem_object *obj,
				    क्रमागत i915_cache_level cache_level)
अणु
	पूर्णांक ret;

	अगर (obj->cache_level == cache_level)
		वापस 0;

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_ALL,
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* Always invalidate stale cachelines */
	अगर (obj->cache_level != cache_level) अणु
		i915_gem_object_set_cache_coherency(obj, cache_level);
		obj->cache_dirty = true;
	पूर्ण

	/* The cache-level will be applied when each vma is rebound. */
	वापस i915_gem_object_unbind(obj,
				      I915_GEM_OBJECT_UNBIND_ACTIVE |
				      I915_GEM_OBJECT_UNBIND_BARRIER);
पूर्ण

पूर्णांक i915_gem_get_caching_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_caching *args = data;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	obj = i915_gem_object_lookup_rcu(file, args->handle);
	अगर (!obj) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	चयन (obj->cache_level) अणु
	हाल I915_CACHE_LLC:
	हाल I915_CACHE_L3_LLC:
		args->caching = I915_CACHING_CACHED;
		अवरोध;

	हाल I915_CACHE_WT:
		args->caching = I915_CACHING_DISPLAY;
		अवरोध;

	शेष:
		args->caching = I915_CACHING_NONE;
		अवरोध;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

पूर्णांक i915_gem_set_caching_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_caching *args = data;
	काष्ठा drm_i915_gem_object *obj;
	क्रमागत i915_cache_level level;
	पूर्णांक ret = 0;

	चयन (args->caching) अणु
	हाल I915_CACHING_NONE:
		level = I915_CACHE_NONE;
		अवरोध;
	हाल I915_CACHING_CACHED:
		/*
		 * Due to a HW issue on BXT A stepping, GPU stores via a
		 * snooped mapping may leave stale data in a corresponding CPU
		 * cacheline, whereas normally such cachelines would get
		 * invalidated.
		 */
		अगर (!HAS_LLC(i915) && !HAS_SNOOP(i915))
			वापस -ENODEV;

		level = I915_CACHE_LLC;
		अवरोध;
	हाल I915_CACHING_DISPLAY:
		level = HAS_WT(i915) ? I915_CACHE_WT : I915_CACHE_NONE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	obj = i915_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	/*
	 * The caching mode of proxy object is handled by its generator, and
	 * not allowed to be changed by userspace.
	 */
	अगर (i915_gem_object_is_proxy(obj)) अणु
		/*
		 * Silently allow cached क्रम userptr; the vulkan driver
		 * sets all objects to cached
		 */
		अगर (!i915_gem_object_is_userptr(obj) ||
		    args->caching != I915_CACHING_CACHED)
			ret = -ENXIO;

		जाओ out;
	पूर्ण

	ret = i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य);
	अगर (ret)
		जाओ out;

	ret = i915_gem_object_set_cache_level(obj, level);
	i915_gem_object_unlock(obj);

out:
	i915_gem_object_put(obj);
	वापस ret;
पूर्ण

/*
 * Prepare buffer क्रम display plane (scanout, cursors, etc). Can be called from
 * an unपूर्णांकerruptible phase (modesetting) and allows any flushes to be pipelined
 * (क्रम pageflips). We only flush the caches जबतक preparing the buffer क्रम
 * display, the callers are responsible क्रम frontbuffer flush.
 */
काष्ठा i915_vma *
i915_gem_object_pin_to_display_plane(काष्ठा drm_i915_gem_object *obj,
				     काष्ठा i915_gem_ww_ctx *ww,
				     u32 alignment,
				     स्थिर काष्ठा i915_ggtt_view *view,
				     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_vma *vma;
	पूर्णांक ret;

	/* Frame buffer must be in LMEM (no migration yet) */
	अगर (HAS_LMEM(i915) && !i915_gem_object_is_lmem(obj))
		वापस ERR_PTR(-EINVAL);

	/*
	 * The display engine is not coherent with the LLC cache on gen6.  As
	 * a result, we make sure that the pinning that is about to occur is
	 * करोne with uncached PTEs. This is lowest common denominator क्रम all
	 * chipsets.
	 *
	 * However क्रम gen6+, we could करो better by using the GFDT bit instead
	 * of uncaching, which would allow us to flush all the LLC-cached data
	 * with that bit in the PTE to मुख्य memory with just one PIPE_CONTROL.
	 */
	ret = i915_gem_object_set_cache_level(obj,
					      HAS_WT(i915) ?
					      I915_CACHE_WT : I915_CACHE_NONE);
	अगर (ret)
		वापस ERR_PTR(ret);

	/*
	 * As the user may map the buffer once pinned in the display plane
	 * (e.g. libkms क्रम the bootup splash), we have to ensure that we
	 * always use map_and_fenceable क्रम all scanout buffers. However,
	 * it may simply be too big to fit पूर्णांकo mappable, in which हाल
	 * put it anyway and hope that userspace can cope (but always first
	 * try to preserve the existing ABI).
	 */
	vma = ERR_PTR(-ENOSPC);
	अगर ((flags & PIN_MAPPABLE) == 0 &&
	    (!view || view->type == I915_GGTT_VIEW_NORMAL))
		vma = i915_gem_object_ggtt_pin_ww(obj, ww, view, 0, alignment,
						  flags | PIN_MAPPABLE |
						  PIN_NONBLOCK);
	अगर (IS_ERR(vma) && vma != ERR_PTR(-EDEADLK))
		vma = i915_gem_object_ggtt_pin_ww(obj, ww, view, 0,
						  alignment, flags);
	अगर (IS_ERR(vma))
		वापस vma;

	vma->display_alignment = max_t(u64, vma->display_alignment, alignment);
	i915_vma_mark_scanout(vma);

	i915_gem_object_flush_अगर_display_locked(obj);

	वापस vma;
पूर्ण

/**
 * Moves a single object to the CPU पढ़ो, and possibly ग_लिखो करोमुख्य.
 * @obj: object to act on
 * @ग_लिखो: requesting ग_लिखो or पढ़ो-only access
 *
 * This function वापसs when the move is complete, including रुकोing on
 * flushes to occur.
 */
पूर्णांक
i915_gem_object_set_to_cpu_करोमुख्य(काष्ठा drm_i915_gem_object *obj, bool ग_लिखो)
अणु
	पूर्णांक ret;

	निश्चित_object_held(obj);

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   (ग_लिखो ? I915_WAIT_ALL : 0),
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		वापस ret;

	flush_ग_लिखो_करोमुख्य(obj, ~I915_GEM_DOMAIN_CPU);

	/* Flush the CPU cache अगर it's still invalid. */
	अगर ((obj->पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_CPU) == 0) अणु
		i915_gem_clflush_object(obj, I915_CLFLUSH_SYNC);
		obj->पढ़ो_करोमुख्यs |= I915_GEM_DOMAIN_CPU;
	पूर्ण

	/* It should now be out of any other ग_लिखो करोमुख्यs, and we can update
	 * the करोमुख्य values क्रम our changes.
	 */
	GEM_BUG_ON(obj->ग_लिखो_करोमुख्य & ~I915_GEM_DOMAIN_CPU);

	/* If we're writing through the CPU, then the GPU पढ़ो करोमुख्यs will
	 * need to be invalidated at next use.
	 */
	अगर (ग_लिखो)
		__start_cpu_ग_लिखो(obj);

	वापस 0;
पूर्ण

/**
 * Called when user space prepares to use an object with the CPU, either
 * through the mmap ioctl's mapping or a GTT mapping.
 * @dev: drm device
 * @data: ioctl data blob
 * @file: drm file
 */
पूर्णांक
i915_gem_set_करोमुख्य_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_set_करोमुख्य *args = data;
	काष्ठा drm_i915_gem_object *obj;
	u32 पढ़ो_करोमुख्यs = args->पढ़ो_करोमुख्यs;
	u32 ग_लिखो_करोमुख्य = args->ग_लिखो_करोमुख्य;
	पूर्णांक err;

	/* Only handle setting करोमुख्यs to types used by the CPU. */
	अगर ((ग_लिखो_करोमुख्य | पढ़ो_करोमुख्यs) & I915_GEM_GPU_DOMAINS)
		वापस -EINVAL;

	/*
	 * Having something in the ग_लिखो करोमुख्य implies it's in the पढ़ो
	 * करोमुख्य, and only that पढ़ो करोमुख्य.  Enक्रमce that in the request.
	 */
	अगर (ग_लिखो_करोमुख्य && पढ़ो_करोमुख्यs != ग_लिखो_करोमुख्य)
		वापस -EINVAL;

	अगर (!पढ़ो_करोमुख्यs)
		वापस 0;

	obj = i915_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	/*
	 * Try to flush the object off the GPU without holding the lock.
	 * We will repeat the flush holding the lock in the normal manner
	 * to catch हालs where we are gazumped.
	 */
	err = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_PRIORITY |
				   (ग_लिखो_करोमुख्य ? I915_WAIT_ALL : 0),
				   MAX_SCHEDULE_TIMEOUT);
	अगर (err)
		जाओ out;

	अगर (i915_gem_object_is_userptr(obj)) अणु
		/*
		 * Try to grab userptr pages, iris uses set_करोमुख्य to check
		 * userptr validity
		 */
		err = i915_gem_object_userptr_validate(obj);
		अगर (!err)
			err = i915_gem_object_रुको(obj,
						   I915_WAIT_INTERRUPTIBLE |
						   I915_WAIT_PRIORITY |
						   (ग_लिखो_करोमुख्य ? I915_WAIT_ALL : 0),
						   MAX_SCHEDULE_TIMEOUT);
		जाओ out;
	पूर्ण

	/*
	 * Proxy objects करो not control access to the backing storage, ergo
	 * they cannot be used as a means to manipulate the cache करोमुख्य
	 * tracking क्रम that backing storage. The proxy object is always
	 * considered to be outside of any cache करोमुख्य.
	 */
	अगर (i915_gem_object_is_proxy(obj)) अणु
		err = -ENXIO;
		जाओ out;
	पूर्ण

	err = i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य);
	अगर (err)
		जाओ out;

	/*
	 * Flush and acquire obj->pages so that we are coherent through
	 * direct access in memory with previous cached ग_लिखोs through
	 * shmemfs and that our cache करोमुख्य tracking reमुख्यs valid.
	 * For example, अगर the obj->filp was moved to swap without us
	 * being notअगरied and releasing the pages, we would mistakenly
	 * जारी to assume that the obj reमुख्यed out of the CPU cached
	 * करोमुख्य.
	 */
	err = i915_gem_object_pin_pages(obj);
	अगर (err)
		जाओ out_unlock;

	/*
	 * Alपढ़ोy in the desired ग_लिखो करोमुख्य? Nothing क्रम us to करो!
	 *
	 * We apply a little bit of cunning here to catch a broader set of
	 * no-ops. If obj->ग_लिखो_करोमुख्य is set, we must be in the same
	 * obj->पढ़ो_करोमुख्यs, and only that करोमुख्य. Thereक्रमe, अगर that
	 * obj->ग_लिखो_करोमुख्य matches the request पढ़ो_करोमुख्यs, we are
	 * alपढ़ोy in the same पढ़ो/ग_लिखो करोमुख्य and can skip the operation,
	 * without having to further check the requested ग_लिखो_करोमुख्य.
	 */
	अगर (READ_ONCE(obj->ग_लिखो_करोमुख्य) == पढ़ो_करोमुख्यs)
		जाओ out_unpin;

	अगर (पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_WC)
		err = i915_gem_object_set_to_wc_करोमुख्य(obj, ग_लिखो_करोमुख्य);
	अन्यथा अगर (पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_GTT)
		err = i915_gem_object_set_to_gtt_करोमुख्य(obj, ग_लिखो_करोमुख्य);
	अन्यथा
		err = i915_gem_object_set_to_cpu_करोमुख्य(obj, ग_लिखो_करोमुख्य);

out_unpin:
	i915_gem_object_unpin_pages(obj);

out_unlock:
	i915_gem_object_unlock(obj);

	अगर (!err && ग_लिखो_करोमुख्य)
		i915_gem_object_invalidate_frontbuffer(obj, ORIGIN_CPU);

out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

/*
 * Pins the specअगरied object's pages and synchronizes the object with
 * GPU accesses. Sets needs_clflush to non-zero अगर the caller should
 * flush the object from the CPU cache.
 */
पूर्णांक i915_gem_object_prepare_पढ़ो(काष्ठा drm_i915_gem_object *obj,
				 अचिन्हित पूर्णांक *needs_clflush)
अणु
	पूर्णांक ret;

	*needs_clflush = 0;
	अगर (!i915_gem_object_has_काष्ठा_page(obj))
		वापस -ENODEV;

	निश्चित_object_held(obj);

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE,
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		वापस ret;

	ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		वापस ret;

	अगर (obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ ||
	    !अटल_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		ret = i915_gem_object_set_to_cpu_करोमुख्य(obj, false);
		अगर (ret)
			जाओ err_unpin;
		अन्यथा
			जाओ out;
	पूर्ण

	flush_ग_लिखो_करोमुख्य(obj, ~I915_GEM_DOMAIN_CPU);

	/* If we're not in the cpu पढ़ो करोमुख्य, set ourself पूर्णांकo the gtt
	 * पढ़ो करोमुख्य and manually flush cachelines (अगर required). This
	 * optimizes क्रम the हाल when the gpu will dirty the data
	 * anyway again beक्रमe the next pपढ़ो happens.
	 */
	अगर (!obj->cache_dirty &&
	    !(obj->पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_CPU))
		*needs_clflush = CLFLUSH_BEFORE;

out:
	/* वापस with the pages pinned */
	वापस 0;

err_unpin:
	i915_gem_object_unpin_pages(obj);
	वापस ret;
पूर्ण

पूर्णांक i915_gem_object_prepare_ग_लिखो(काष्ठा drm_i915_gem_object *obj,
				  अचिन्हित पूर्णांक *needs_clflush)
अणु
	पूर्णांक ret;

	*needs_clflush = 0;
	अगर (!i915_gem_object_has_काष्ठा_page(obj))
		वापस -ENODEV;

	निश्चित_object_held(obj);

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_ALL,
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		वापस ret;

	ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		वापस ret;

	अगर (obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_WRITE ||
	    !अटल_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		ret = i915_gem_object_set_to_cpu_करोमुख्य(obj, true);
		अगर (ret)
			जाओ err_unpin;
		अन्यथा
			जाओ out;
	पूर्ण

	flush_ग_लिखो_करोमुख्य(obj, ~I915_GEM_DOMAIN_CPU);

	/* If we're not in the cpu ग_लिखो करोमुख्य, set ourself पूर्णांकo the
	 * gtt ग_लिखो करोमुख्य and manually flush cachelines (as required).
	 * This optimizes क्रम the हाल when the gpu will use the data
	 * right away and we thereक्रमe have to clflush anyway.
	 */
	अगर (!obj->cache_dirty) अणु
		*needs_clflush |= CLFLUSH_AFTER;

		/*
		 * Same trick applies to invalidate partially written
		 * cachelines पढ़ो beक्रमe writing.
		 */
		अगर (!(obj->पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_CPU))
			*needs_clflush |= CLFLUSH_BEFORE;
	पूर्ण

out:
	i915_gem_object_invalidate_frontbuffer(obj, ORIGIN_CPU);
	obj->mm.dirty = true;
	/* वापस with the pages pinned */
	वापस 0;

err_unpin:
	i915_gem_object_unpin_pages(obj);
	वापस ret;
पूर्ण
