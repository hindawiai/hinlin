<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */
#अगर_अघोषित __I915_GEM_CLIENT_BLT_H__
#घोषणा __I915_GEM_CLIENT_BLT_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_gem_object;
काष्ठा i915_page_sizes;
काष्ठा पूर्णांकel_context;
काष्ठा sg_table;

पूर्णांक i915_gem_schedule_fill_pages_blt(काष्ठा drm_i915_gem_object *obj,
				     काष्ठा पूर्णांकel_context *ce,
				     काष्ठा sg_table *pages,
				     काष्ठा i915_page_sizes *page_sizes,
				     u32 value);

#पूर्ण_अगर
