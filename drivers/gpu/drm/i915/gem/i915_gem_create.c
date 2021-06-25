<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "gem/i915_gem_ioctls.h"
#समावेश "gem/i915_gem_region.h"

#समावेश "i915_drv.h"

अटल पूर्णांक
i915_gem_create(काष्ठा drm_file *file,
		काष्ठा पूर्णांकel_memory_region *mr,
		u64 *size_p,
		u32 *handle_p)
अणु
	काष्ठा drm_i915_gem_object *obj;
	u32 handle;
	u64 size;
	पूर्णांक ret;

	GEM_BUG_ON(!is_घातer_of_2(mr->min_page_size));
	size = round_up(*size_p, mr->min_page_size);
	अगर (size == 0)
		वापस -EINVAL;

	/* For most of the ABI (e.g. mmap) we think in प्रणाली pages */
	GEM_BUG_ON(!IS_ALIGNED(size, PAGE_SIZE));

	/* Allocate the new object */
	obj = i915_gem_object_create_region(mr, size, 0);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	GEM_BUG_ON(size != obj->base.size);

	ret = drm_gem_handle_create(file, &obj->base, &handle);
	/* drop reference from allocate - handle holds it now */
	i915_gem_object_put(obj);
	अगर (ret)
		वापस ret;

	*handle_p = handle;
	*size_p = size;
	वापस 0;
पूर्ण

पूर्णांक
i915_gem_dumb_create(काष्ठा drm_file *file,
		     काष्ठा drm_device *dev,
		     काष्ठा drm_mode_create_dumb *args)
अणु
	क्रमागत पूर्णांकel_memory_type mem_type;
	पूर्णांक cpp = DIV_ROUND_UP(args->bpp, 8);
	u32 क्रमmat;

	चयन (cpp) अणु
	हाल 1:
		क्रमmat = DRM_FORMAT_C8;
		अवरोध;
	हाल 2:
		क्रमmat = DRM_FORMAT_RGB565;
		अवरोध;
	हाल 4:
		क्रमmat = DRM_FORMAT_XRGB8888;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* have to work out size/pitch and वापस them */
	args->pitch = ALIGN(args->width * cpp, 64);

	/* align stride to page size so that we can remap */
	अगर (args->pitch > पूर्णांकel_plane_fb_max_stride(to_i915(dev), क्रमmat,
						    DRM_FORMAT_MOD_LINEAR))
		args->pitch = ALIGN(args->pitch, 4096);

	अगर (args->pitch < args->width)
		वापस -EINVAL;

	args->size = mul_u32_u32(args->pitch, args->height);

	mem_type = INTEL_MEMORY_SYSTEM;
	अगर (HAS_LMEM(to_i915(dev)))
		mem_type = INTEL_MEMORY_LOCAL;

	वापस i915_gem_create(file,
			       पूर्णांकel_memory_region_by_type(to_i915(dev),
							   mem_type),
			       &args->size, &args->handle);
पूर्ण

/**
 * Creates a new mm object and वापसs a handle to it.
 * @dev: drm device poपूर्णांकer
 * @data: ioctl data blob
 * @file: drm file poपूर्णांकer
 */
पूर्णांक
i915_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_create *args = data;

	i915_gem_flush_मुक्त_objects(i915);

	वापस i915_gem_create(file,
			       पूर्णांकel_memory_region_by_type(i915,
							   INTEL_MEMORY_SYSTEM),
			       &args->size, &args->handle);
पूर्ण
