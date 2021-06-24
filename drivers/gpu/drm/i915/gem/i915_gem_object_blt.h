<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_OBJECT_BLT_H__
#घोषणा __I915_GEM_OBJECT_BLT_H__

#समावेश <linux/types.h>

#समावेश "gt/intel_context.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "i915_vma.h"

काष्ठा drm_i915_gem_object;
काष्ठा i915_gem_ww_ctx;

काष्ठा i915_vma *पूर्णांकel_emit_vma_fill_blt(काष्ठा पूर्णांकel_context *ce,
					 काष्ठा i915_vma *vma,
					 काष्ठा i915_gem_ww_ctx *ww,
					 u32 value);

काष्ठा i915_vma *पूर्णांकel_emit_vma_copy_blt(काष्ठा पूर्णांकel_context *ce,
					 काष्ठा i915_gem_ww_ctx *ww,
					 काष्ठा i915_vma *src,
					 काष्ठा i915_vma *dst);

पूर्णांक पूर्णांकel_emit_vma_mark_active(काष्ठा i915_vma *vma, काष्ठा i915_request *rq);
व्योम पूर्णांकel_emit_vma_release(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_vma *vma);

पूर्णांक i915_gem_object_fill_blt(काष्ठा drm_i915_gem_object *obj,
			     काष्ठा पूर्णांकel_context *ce,
			     u32 value);

पूर्णांक i915_gem_object_copy_blt(काष्ठा drm_i915_gem_object *src,
			     काष्ठा drm_i915_gem_object *dst,
			     काष्ठा पूर्णांकel_context *ce);

#पूर्ण_अगर
