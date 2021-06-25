<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2008 Intel Corporation
 */

#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>

#समावेश "i915_drv.h"
#समावेश "i915_gem.h"
#समावेश "i915_gem_ioctls.h"
#समावेश "i915_gem_mman.h"
#समावेश "i915_gem_object.h"

/**
 * DOC: buffer object tiling
 *
 * i915_gem_set_tiling_ioctl() and i915_gem_get_tiling_ioctl() is the userspace
 * पूर्णांकerface to declare fence रेजिस्टर requirements.
 *
 * In principle GEM करोesn't care at all about the पूर्णांकernal data layout of an
 * object, and hence it also करोesn't care about tiling or swizzling. There's two
 * exceptions:
 *
 * - For X and Y tiling the hardware provides detilers क्रम CPU access, so called
 *   fences. Since there's only a limited amount of them the kernel must manage
 *   these, and thereक्रमe userspace must tell the kernel the object tiling अगर it
 *   wants to use fences क्रम detiling.
 * - On gen3 and gen4 platक्रमms have a swizzling pattern क्रम tiled objects which
 *   depends upon the physical page frame number. When swapping such objects the
 *   page frame number might change and the kernel must be able to fix this up
 *   and hence now the tiling. Note that on a subset of platक्रमms with
 *   asymmetric memory channel population the swizzling pattern changes in an
 *   unknown way, and क्रम those the kernel simply क्रमbids swapping completely.
 *
 * Since neither of this applies क्रम new tiling layouts on modern platक्रमms like
 * W, Ys and Yf tiling GEM only allows object tiling to be set to X or Y tiled.
 * Anything अन्यथा can be handled in userspace entirely without the kernel's
 * invovlement.
 */

/**
 * i915_gem_fence_size - required global GTT size क्रम a fence
 * @i915: i915 device
 * @size: object size
 * @tiling: tiling mode
 * @stride: tiling stride
 *
 * Return the required global GTT size क्रम a fence (view of a tiled object),
 * taking पूर्णांकo account potential fence रेजिस्टर mapping.
 */
u32 i915_gem_fence_size(काष्ठा drm_i915_निजी *i915,
			u32 size, अचिन्हित पूर्णांक tiling, अचिन्हित पूर्णांक stride)
अणु
	u32 ggtt_size;

	GEM_BUG_ON(!size);

	अगर (tiling == I915_TILING_NONE)
		वापस size;

	GEM_BUG_ON(!stride);

	अगर (INTEL_GEN(i915) >= 4) अणु
		stride *= i915_gem_tile_height(tiling);
		GEM_BUG_ON(!IS_ALIGNED(stride, I965_FENCE_PAGE));
		वापस roundup(size, stride);
	पूर्ण

	/* Previous chips need a घातer-of-two fence region when tiling */
	अगर (IS_GEN(i915, 3))
		ggtt_size = 1024*1024;
	अन्यथा
		ggtt_size = 512*1024;

	जबतक (ggtt_size < size)
		ggtt_size <<= 1;

	वापस ggtt_size;
पूर्ण

/**
 * i915_gem_fence_alignment - required global GTT alignment क्रम a fence
 * @i915: i915 device
 * @size: object size
 * @tiling: tiling mode
 * @stride: tiling stride
 *
 * Return the required global GTT alignment क्रम a fence (a view of a tiled
 * object), taking पूर्णांकo account potential fence रेजिस्टर mapping.
 */
u32 i915_gem_fence_alignment(काष्ठा drm_i915_निजी *i915, u32 size,
			     अचिन्हित पूर्णांक tiling, अचिन्हित पूर्णांक stride)
अणु
	GEM_BUG_ON(!size);

	/*
	 * Minimum alignment is 4k (GTT page size), but might be greater
	 * अगर a fence रेजिस्टर is needed क्रम the object.
	 */
	अगर (tiling == I915_TILING_NONE)
		वापस I915_GTT_MIN_ALIGNMENT;

	अगर (INTEL_GEN(i915) >= 4)
		वापस I965_FENCE_PAGE;

	/*
	 * Previous chips need to be aligned to the size of the smallest
	 * fence रेजिस्टर that can contain the object.
	 */
	वापस i915_gem_fence_size(i915, size, tiling, stride);
पूर्ण

/* Check pitch स्थिरriants क्रम all chips & tiling क्रमmats */
अटल bool
i915_tiling_ok(काष्ठा drm_i915_gem_object *obj,
	       अचिन्हित पूर्णांक tiling, अचिन्हित पूर्णांक stride)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	अचिन्हित पूर्णांक tile_width;

	/* Linear is always fine */
	अगर (tiling == I915_TILING_NONE)
		वापस true;

	अगर (tiling > I915_TILING_LAST)
		वापस false;

	/* check maximum stride & object size */
	/* i965+ stores the end address of the gtt mapping in the fence
	 * reg, so करोnt bother to check the size */
	अगर (INTEL_GEN(i915) >= 7) अणु
		अगर (stride / 128 > GEN7_FENCE_MAX_PITCH_VAL)
			वापस false;
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 4) अणु
		अगर (stride / 128 > I965_FENCE_MAX_PITCH_VAL)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (stride > 8192)
			वापस false;

		अगर (!is_घातer_of_2(stride))
			वापस false;
	पूर्ण

	अगर (IS_GEN(i915, 2) ||
	    (tiling == I915_TILING_Y && HAS_128_BYTE_Y_TILING(i915)))
		tile_width = 128;
	अन्यथा
		tile_width = 512;

	अगर (!stride || !IS_ALIGNED(stride, tile_width))
		वापस false;

	वापस true;
पूर्ण

अटल bool i915_vma_fence_prepare(काष्ठा i915_vma *vma,
				   पूर्णांक tiling_mode, अचिन्हित पूर्णांक stride)
अणु
	काष्ठा drm_i915_निजी *i915 = vma->vm->i915;
	u32 size, alignment;

	अगर (!i915_vma_is_map_and_fenceable(vma))
		वापस true;

	size = i915_gem_fence_size(i915, vma->size, tiling_mode, stride);
	अगर (vma->node.size < size)
		वापस false;

	alignment = i915_gem_fence_alignment(i915, vma->size, tiling_mode, stride);
	अगर (!IS_ALIGNED(vma->node.start, alignment))
		वापस false;

	वापस true;
पूर्ण

/* Make the current GTT allocation valid क्रम the change in tiling. */
अटल पूर्णांक
i915_gem_object_fence_prepare(काष्ठा drm_i915_gem_object *obj,
			      पूर्णांक tiling_mode, अचिन्हित पूर्णांक stride)
अणु
	काष्ठा i915_ggtt *ggtt = &to_i915(obj->base.dev)->ggtt;
	काष्ठा i915_vma *vma, *vn;
	LIST_HEAD(unbind);
	पूर्णांक ret = 0;

	अगर (tiling_mode == I915_TILING_NONE)
		वापस 0;

	mutex_lock(&ggtt->vm.mutex);

	spin_lock(&obj->vma.lock);
	क्रम_each_ggtt_vma(vma, obj) अणु
		GEM_BUG_ON(vma->vm != &ggtt->vm);

		अगर (i915_vma_fence_prepare(vma, tiling_mode, stride))
			जारी;

		list_move(&vma->vm_link, &unbind);
	पूर्ण
	spin_unlock(&obj->vma.lock);

	list_क्रम_each_entry_safe(vma, vn, &unbind, vm_link) अणु
		ret = __i915_vma_unbind(vma);
		अगर (ret) अणु
			/* Restore the reमुख्यing vma on an error */
			list_splice(&unbind, &ggtt->vm.bound_list);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&ggtt->vm.mutex);

	वापस ret;
पूर्ण

पूर्णांक
i915_gem_object_set_tiling(काष्ठा drm_i915_gem_object *obj,
			   अचिन्हित पूर्णांक tiling, अचिन्हित पूर्णांक stride)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	/* Make sure we करोn't cross-contaminate obj->tiling_and_stride */
	BUILD_BUG_ON(I915_TILING_LAST & STRIDE_MASK);

	GEM_BUG_ON(!i915_tiling_ok(obj, tiling, stride));
	GEM_BUG_ON(!stride ^ (tiling == I915_TILING_NONE));

	अगर ((tiling | stride) == obj->tiling_and_stride)
		वापस 0;

	अगर (i915_gem_object_is_framebuffer(obj))
		वापस -EBUSY;

	/* We need to rebind the object अगर its current allocation
	 * no दीर्घer meets the alignment restrictions क्रम its new
	 * tiling mode. Otherwise we can just leave it alone, but
	 * need to ensure that any fence रेजिस्टर is updated beक्रमe
	 * the next fenced (either through the GTT or by the BLT unit
	 * on older GPUs) access.
	 *
	 * After updating the tiling parameters, we then flag whether
	 * we need to update an associated fence रेजिस्टर. Note this
	 * has to also include the unfenced रेजिस्टर the GPU uses
	 * whilst executing a fenced command क्रम an untiled object.
	 */

	i915_gem_object_lock(obj, शून्य);
	अगर (i915_gem_object_is_framebuffer(obj)) अणु
		i915_gem_object_unlock(obj);
		वापस -EBUSY;
	पूर्ण

	err = i915_gem_object_fence_prepare(obj, tiling, stride);
	अगर (err) अणु
		i915_gem_object_unlock(obj);
		वापस err;
	पूर्ण

	/* If the memory has unknown (i.e. varying) swizzling, we pin the
	 * pages to prevent them being swapped out and causing corruption
	 * due to the change in swizzling.
	 */
	अगर (i915_gem_object_has_pages(obj) &&
	    obj->mm.madv == I915_MADV_WILLNEED &&
	    i915->quirks & QUIRK_PIN_SWIZZLED_PAGES) अणु
		अगर (tiling == I915_TILING_NONE) अणु
			GEM_BUG_ON(!i915_gem_object_has_tiling_quirk(obj));
			i915_gem_object_clear_tiling_quirk(obj);
			i915_gem_object_make_shrinkable(obj);
		पूर्ण
		अगर (!i915_gem_object_is_tiled(obj)) अणु
			GEM_BUG_ON(i915_gem_object_has_tiling_quirk(obj));
			i915_gem_object_make_unshrinkable(obj);
			i915_gem_object_set_tiling_quirk(obj);
		पूर्ण
	पूर्ण

	spin_lock(&obj->vma.lock);
	क्रम_each_ggtt_vma(vma, obj) अणु
		vma->fence_size =
			i915_gem_fence_size(i915, vma->size, tiling, stride);
		vma->fence_alignment =
			i915_gem_fence_alignment(i915,
						 vma->size, tiling, stride);

		अगर (vma->fence)
			vma->fence->dirty = true;
	पूर्ण
	spin_unlock(&obj->vma.lock);

	obj->tiling_and_stride = tiling | stride;
	i915_gem_object_unlock(obj);

	/* Force the fence to be reacquired क्रम GTT access */
	i915_gem_object_release_mmap_gtt(obj);

	/* Try to pपुनः_स्मृतिate memory required to save swizzling on put-pages */
	अगर (i915_gem_object_needs_bit17_swizzle(obj)) अणु
		अगर (!obj->bit_17) अणु
			obj->bit_17 = biपंचांगap_zalloc(obj->base.size >> PAGE_SHIFT,
						    GFP_KERNEL);
		पूर्ण
	पूर्ण अन्यथा अणु
		biपंचांगap_मुक्त(obj->bit_17);
		obj->bit_17 = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i915_gem_set_tiling_ioctl - IOCTL handler to set tiling mode
 * @dev: DRM device
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file: DRM file क्रम the ioctl call
 *
 * Sets the tiling mode of an object, वापसing the required swizzling of
 * bit 6 of addresses in the object.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक
i915_gem_set_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_i915_gem_set_tiling *args = data;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err;

	अगर (!dev_priv->ggtt.num_fences)
		वापस -EOPNOTSUPP;

	obj = i915_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	/*
	 * The tiling mode of proxy objects is handled by its generator, and
	 * not allowed to be changed by userspace.
	 */
	अगर (i915_gem_object_is_proxy(obj)) अणु
		err = -ENXIO;
		जाओ err;
	पूर्ण

	अगर (!i915_tiling_ok(obj, args->tiling_mode, args->stride)) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (args->tiling_mode == I915_TILING_NONE) अणु
		args->swizzle_mode = I915_BIT_6_SWIZZLE_NONE;
		args->stride = 0;
	पूर्ण अन्यथा अणु
		अगर (args->tiling_mode == I915_TILING_X)
			args->swizzle_mode = to_i915(dev)->ggtt.bit_6_swizzle_x;
		अन्यथा
			args->swizzle_mode = to_i915(dev)->ggtt.bit_6_swizzle_y;

		/* Hide bit 17 swizzling from the user.  This prevents old Mesa
		 * from पातing the application on sw fallbacks to bit 17,
		 * and we use the pपढ़ो/pग_लिखो bit17 paths to swizzle क्रम it.
		 * If there was a user that was relying on the swizzle
		 * inक्रमmation क्रम drm_पूर्णांकel_bo_map()ed पढ़ोs/ग_लिखोs this would
		 * अवरोध it, but we करोn't have any of those.
		 */
		अगर (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_17)
			args->swizzle_mode = I915_BIT_6_SWIZZLE_9;
		अगर (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_10_17)
			args->swizzle_mode = I915_BIT_6_SWIZZLE_9_10;

		/* If we can't handle the swizzling, make it untiled. */
		अगर (args->swizzle_mode == I915_BIT_6_SWIZZLE_UNKNOWN) अणु
			args->tiling_mode = I915_TILING_NONE;
			args->swizzle_mode = I915_BIT_6_SWIZZLE_NONE;
			args->stride = 0;
		पूर्ण
	पूर्ण

	err = i915_gem_object_set_tiling(obj, args->tiling_mode, args->stride);

	/* We have to मुख्यtain this existing ABI... */
	args->stride = i915_gem_object_get_stride(obj);
	args->tiling_mode = i915_gem_object_get_tiling(obj);

err:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

/**
 * i915_gem_get_tiling_ioctl - IOCTL handler to get tiling mode
 * @dev: DRM device
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file: DRM file क्रम the ioctl call
 *
 * Returns the current tiling mode and required bit 6 swizzling क्रम the object.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक
i915_gem_get_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_get_tiling *args = data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err = -ENOENT;

	अगर (!dev_priv->ggtt.num_fences)
		वापस -EOPNOTSUPP;

	rcu_पढ़ो_lock();
	obj = i915_gem_object_lookup_rcu(file, args->handle);
	अगर (obj) अणु
		args->tiling_mode =
			READ_ONCE(obj->tiling_and_stride) & TILING_MASK;
		err = 0;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (unlikely(err))
		वापस err;

	चयन (args->tiling_mode) अणु
	हाल I915_TILING_X:
		args->swizzle_mode = dev_priv->ggtt.bit_6_swizzle_x;
		अवरोध;
	हाल I915_TILING_Y:
		args->swizzle_mode = dev_priv->ggtt.bit_6_swizzle_y;
		अवरोध;
	शेष:
	हाल I915_TILING_NONE:
		args->swizzle_mode = I915_BIT_6_SWIZZLE_NONE;
		अवरोध;
	पूर्ण

	/* Hide bit 17 from the user -- see comment in i915_gem_set_tiling */
	अगर (dev_priv->quirks & QUIRK_PIN_SWIZZLED_PAGES)
		args->phys_swizzle_mode = I915_BIT_6_SWIZZLE_UNKNOWN;
	अन्यथा
		args->phys_swizzle_mode = args->swizzle_mode;
	अगर (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_17)
		args->swizzle_mode = I915_BIT_6_SWIZZLE_9;
	अगर (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_10_17)
		args->swizzle_mode = I915_BIT_6_SWIZZLE_9_10;

	वापस 0;
पूर्ण
