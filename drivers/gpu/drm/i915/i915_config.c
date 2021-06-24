<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "i915_drv.h"

अचिन्हित दीर्घ
i915_fence_context_समयout(स्थिर काष्ठा drm_i915_निजी *i915, u64 context)
अणु
	अगर (context && IS_ACTIVE(CONFIG_DRM_I915_FENCE_TIMEOUT))
		वापस msecs_to_jअगरfies_समयout(CONFIG_DRM_I915_FENCE_TIMEOUT);

	वापस 0;
पूर्ण
