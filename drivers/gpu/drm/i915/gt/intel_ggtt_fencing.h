<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __INTEL_GGTT_FENCING_H__
#घोषणा __INTEL_GGTT_FENCING_H__

#समावेश <linux/list.h>
#समावेश <linux/types.h>

#समावेश "i915_active.h"

काष्ठा drm_i915_gem_object;
काष्ठा i915_ggtt;
काष्ठा i915_vma;
काष्ठा पूर्णांकel_gt;
काष्ठा sg_table;

#घोषणा I965_FENCE_PAGE 4096UL

काष्ठा i915_fence_reg अणु
	काष्ठा list_head link;
	काष्ठा i915_ggtt *ggtt;
	काष्ठा i915_vma *vma;
	atomic_t pin_count;
	काष्ठा i915_active active;
	पूर्णांक id;
	/**
	 * Whether the tiling parameters क्रम the currently
	 * associated fence रेजिस्टर have changed. Note that
	 * क्रम the purposes of tracking tiling changes we also
	 * treat the unfenced रेजिस्टर, the रेजिस्टर slot that
	 * the object occupies whilst it executes a fenced
	 * command (such as BLT on gen2/3), as a "fence".
	 */
	bool dirty;
	u32 start;
	u32 size;
	u32 tiling;
	u32 stride;
पूर्ण;

काष्ठा i915_fence_reg *i915_reserve_fence(काष्ठा i915_ggtt *ggtt);
व्योम i915_unreserve_fence(काष्ठा i915_fence_reg *fence);

व्योम पूर्णांकel_ggtt_restore_fences(काष्ठा i915_ggtt *ggtt);

व्योम i915_gem_object_करो_bit_17_swizzle(काष्ठा drm_i915_gem_object *obj,
				       काष्ठा sg_table *pages);
व्योम i915_gem_object_save_bit_17_swizzle(काष्ठा drm_i915_gem_object *obj,
					 काष्ठा sg_table *pages);

व्योम पूर्णांकel_ggtt_init_fences(काष्ठा i915_ggtt *ggtt);
व्योम पूर्णांकel_ggtt_fini_fences(काष्ठा i915_ggtt *ggtt);

व्योम पूर्णांकel_gt_init_swizzling(काष्ठा पूर्णांकel_gt *gt);

#पूर्ण_अगर
