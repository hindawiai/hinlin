<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_GTT_H__
#घोषणा __I915_GEM_GTT_H__

#समावेश <linux/io-mapping.h>
#समावेश <linux/types.h>

#समावेश <drm/drm_mm.h>

#समावेश "gt/intel_gtt.h"
#समावेश "i915_scatterlist.h"

काष्ठा drm_i915_gem_object;
काष्ठा i915_address_space;

पूर्णांक __must_check i915_gem_gtt_prepare_pages(काष्ठा drm_i915_gem_object *obj,
					    काष्ठा sg_table *pages);
व्योम i915_gem_gtt_finish_pages(काष्ठा drm_i915_gem_object *obj,
			       काष्ठा sg_table *pages);

पूर्णांक i915_gem_gtt_reserve(काष्ठा i915_address_space *vm,
			 काष्ठा drm_mm_node *node,
			 u64 size, u64 offset, अचिन्हित दीर्घ color,
			 अचिन्हित पूर्णांक flags);

पूर्णांक i915_gem_gtt_insert(काष्ठा i915_address_space *vm,
			काष्ठा drm_mm_node *node,
			u64 size, u64 alignment, अचिन्हित दीर्घ color,
			u64 start, u64 end, अचिन्हित पूर्णांक flags);

/* Flags used by pin/bind&मित्रs. */
#घोषणा PIN_NOEVICT		BIT_ULL(0)
#घोषणा PIN_NOSEARCH		BIT_ULL(1)
#घोषणा PIN_NONBLOCK		BIT_ULL(2)
#घोषणा PIN_MAPPABLE		BIT_ULL(3)
#घोषणा PIN_ZONE_4G		BIT_ULL(4)
#घोषणा PIN_HIGH		BIT_ULL(5)
#घोषणा PIN_OFFSET_BIAS		BIT_ULL(6)
#घोषणा PIN_OFFSET_FIXED	BIT_ULL(7)

#घोषणा PIN_GLOBAL		BIT_ULL(10) /* I915_VMA_GLOBAL_BIND */
#घोषणा PIN_USER		BIT_ULL(11) /* I915_VMA_LOCAL_BIND */

#घोषणा PIN_OFFSET_MASK		I915_GTT_PAGE_MASK

#पूर्ण_अगर
