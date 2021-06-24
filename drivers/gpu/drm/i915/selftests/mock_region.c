<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "gem/i915_gem_region.h"
#समावेश "intel_memory_region.h"

#समावेश "mock_region.h"

अटल स्थिर काष्ठा drm_i915_gem_object_ops mock_region_obj_ops = अणु
	.name = "mock-region",
	.get_pages = i915_gem_object_get_pages_buddy,
	.put_pages = i915_gem_object_put_pages_buddy,
	.release = i915_gem_object_release_memory_region,
पूर्ण;

अटल पूर्णांक mock_object_init(काष्ठा पूर्णांकel_memory_region *mem,
			    काष्ठा drm_i915_gem_object *obj,
			    resource_माप_प्रकार size,
			    अचिन्हित पूर्णांक flags)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_निजी *i915 = mem->i915;

	अगर (size > mem->mm.size)
		वापस -E2BIG;

	drm_gem_निजी_object_init(&i915->drm, &obj->base, size);
	i915_gem_object_init(obj, &mock_region_obj_ops, &lock_class, flags);

	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU | I915_GEM_DOMAIN_GTT;

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_NONE);

	i915_gem_object_init_memory_region(obj, mem);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_memory_region_ops mock_region_ops = अणु
	.init = पूर्णांकel_memory_region_init_buddy,
	.release = पूर्णांकel_memory_region_release_buddy,
	.init_object = mock_object_init,
पूर्ण;

काष्ठा पूर्णांकel_memory_region *
mock_region_create(काष्ठा drm_i915_निजी *i915,
		   resource_माप_प्रकार start,
		   resource_माप_प्रकार size,
		   resource_माप_प्रकार min_page_size,
		   resource_माप_प्रकार io_start)
अणु
	वापस पूर्णांकel_memory_region_create(i915, start, size, min_page_size,
					  io_start, &mock_region_ops);
पूर्ण
