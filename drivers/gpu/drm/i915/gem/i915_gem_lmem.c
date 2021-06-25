<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "intel_memory_region.h"
#समावेश "gem/i915_gem_region.h"
#समावेश "gem/i915_gem_lmem.h"
#समावेश "i915_drv.h"

स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_lmem_obj_ops = अणु
	.name = "i915_gem_object_lmem",
	.flags = I915_GEM_OBJECT_HAS_IOMEM,

	.get_pages = i915_gem_object_get_pages_buddy,
	.put_pages = i915_gem_object_put_pages_buddy,
	.release = i915_gem_object_release_memory_region,
पूर्ण;

bool i915_gem_object_is_lmem(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->ops == &i915_gem_lmem_obj_ops;
पूर्ण

काष्ठा drm_i915_gem_object *
i915_gem_object_create_lmem(काष्ठा drm_i915_निजी *i915,
			    resource_माप_प्रकार size,
			    अचिन्हित पूर्णांक flags)
अणु
	वापस i915_gem_object_create_region(i915->mm.regions[INTEL_REGION_LMEM],
					     size, flags);
पूर्ण

पूर्णांक __i915_gem_lmem_object_init(काष्ठा पूर्णांकel_memory_region *mem,
				काष्ठा drm_i915_gem_object *obj,
				resource_माप_प्रकार size,
				अचिन्हित पूर्णांक flags)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_निजी *i915 = mem->i915;

	drm_gem_निजी_object_init(&i915->drm, &obj->base, size);
	i915_gem_object_init(obj, &i915_gem_lmem_obj_ops, &lock_class, flags);

	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_WC | I915_GEM_DOMAIN_GTT;

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_NONE);

	i915_gem_object_init_memory_region(obj, mem);

	वापस 0;
पूर्ण
