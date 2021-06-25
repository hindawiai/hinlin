<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_STOLEN_H__
#घोषणा __I915_GEM_STOLEN_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा drm_mm_node;
काष्ठा drm_i915_gem_object;

पूर्णांक i915_gem_stolen_insert_node(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा drm_mm_node *node, u64 size,
				अचिन्हित alignment);
पूर्णांक i915_gem_stolen_insert_node_in_range(काष्ठा drm_i915_निजी *dev_priv,
					 काष्ठा drm_mm_node *node, u64 size,
					 अचिन्हित alignment, u64 start,
					 u64 end);
व्योम i915_gem_stolen_हटाओ_node(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा drm_mm_node *node);
काष्ठा पूर्णांकel_memory_region *i915_gem_stolen_setup(काष्ठा drm_i915_निजी *i915);
काष्ठा drm_i915_gem_object *
i915_gem_object_create_stolen(काष्ठा drm_i915_निजी *dev_priv,
			      resource_माप_प्रकार size);
काष्ठा drm_i915_gem_object *
i915_gem_object_create_stolen_क्रम_pपुनः_स्मृतिated(काष्ठा drm_i915_निजी *dev_priv,
					       resource_माप_प्रकार stolen_offset,
					       resource_माप_प्रकार size);

bool i915_gem_object_is_stolen(स्थिर काष्ठा drm_i915_gem_object *obj);

#घोषणा I915_GEM_STOLEN_BIAS SZ_128K

#पूर्ण_अगर /* __I915_GEM_STOLEN_H__ */
