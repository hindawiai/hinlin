<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_LMEM_H
#घोषणा __I915_GEM_LMEM_H

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा drm_i915_gem_object;
काष्ठा पूर्णांकel_memory_region;

बाह्य स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_lmem_obj_ops;

bool i915_gem_object_is_lmem(काष्ठा drm_i915_gem_object *obj);

काष्ठा drm_i915_gem_object *
i915_gem_object_create_lmem(काष्ठा drm_i915_निजी *i915,
			    resource_माप_प्रकार size,
			    अचिन्हित पूर्णांक flags);

पूर्णांक __i915_gem_lmem_object_init(काष्ठा पूर्णांकel_memory_region *mem,
				काष्ठा drm_i915_gem_object *obj,
				resource_माप_प्रकार size,
				अचिन्हित पूर्णांक flags);

#पूर्ण_अगर /* !__I915_GEM_LMEM_H */
