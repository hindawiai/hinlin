<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2018 Intel Corporation
 */

#अगर_अघोषित INTEL_GT_BUFFER_POOL_H
#घोषणा INTEL_GT_BUFFER_POOL_H

#समावेश <linux/types.h>

#समावेश "i915_active.h"
#समावेश "intel_gt_buffer_pool_types.h"

काष्ठा पूर्णांकel_gt;
काष्ठा i915_request;

काष्ठा पूर्णांकel_gt_buffer_pool_node *
पूर्णांकel_gt_get_buffer_pool(काष्ठा पूर्णांकel_gt *gt, माप_प्रकार size,
			 क्रमागत i915_map_type type);

व्योम पूर्णांकel_gt_buffer_pool_mark_used(काष्ठा पूर्णांकel_gt_buffer_pool_node *node);

अटल अंतरभूत पूर्णांक
पूर्णांकel_gt_buffer_pool_mark_active(काष्ठा पूर्णांकel_gt_buffer_pool_node *node,
				 काष्ठा i915_request *rq)
अणु
	/* did we call mark_used? */
	GEM_WARN_ON(!node->pinned);

	वापस i915_active_add_request(&node->active, rq);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_gt_buffer_pool_put(काष्ठा पूर्णांकel_gt_buffer_pool_node *node)
अणु
	i915_active_release(&node->active);
पूर्ण

व्योम पूर्णांकel_gt_init_buffer_pool(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_flush_buffer_pool(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_fini_buffer_pool(काष्ठा पूर्णांकel_gt *gt);

#पूर्ण_अगर /* INTEL_GT_BUFFER_POOL_H */
