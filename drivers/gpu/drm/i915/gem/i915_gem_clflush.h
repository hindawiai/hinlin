<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_CLFLUSH_H__
#घोषणा __I915_GEM_CLFLUSH_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा drm_i915_gem_object;

bool i915_gem_clflush_object(काष्ठा drm_i915_gem_object *obj,
			     अचिन्हित पूर्णांक flags);
#घोषणा I915_CLFLUSH_FORCE BIT(0)
#घोषणा I915_CLFLUSH_SYNC BIT(1)

#पूर्ण_अगर /* __I915_GEM_CLFLUSH_H__ */
