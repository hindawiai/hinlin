<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_REGION_H__
#घोषणा __I915_GEM_REGION_H__

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_memory_region;
काष्ठा drm_i915_gem_object;
काष्ठा sg_table;

पूर्णांक i915_gem_object_get_pages_buddy(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_put_pages_buddy(काष्ठा drm_i915_gem_object *obj,
				     काष्ठा sg_table *pages);

व्योम i915_gem_object_init_memory_region(काष्ठा drm_i915_gem_object *obj,
					काष्ठा पूर्णांकel_memory_region *mem);
व्योम i915_gem_object_release_memory_region(काष्ठा drm_i915_gem_object *obj);

काष्ठा drm_i915_gem_object *
i915_gem_object_create_region(काष्ठा पूर्णांकel_memory_region *mem,
			      resource_माप_प्रकार size,
			      अचिन्हित पूर्णांक flags);

#पूर्ण_अगर
