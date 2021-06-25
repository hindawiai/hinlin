<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2018 Intel Corporation
 */

#अगर_अघोषित INTEL_GT_BUFFER_POOL_TYPES_H
#घोषणा INTEL_GT_BUFFER_POOL_TYPES_H

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "gem/i915_gem_object_types.h"
#समावेश "i915_active_types.h"

काष्ठा पूर्णांकel_gt_buffer_pool अणु
	spinlock_t lock;
	काष्ठा list_head cache_list[4];
	काष्ठा delayed_work work;
पूर्ण;

काष्ठा पूर्णांकel_gt_buffer_pool_node अणु
	काष्ठा i915_active active;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा list_head link;
	जोड़ अणु
		काष्ठा पूर्णांकel_gt_buffer_pool *pool;
		काष्ठा पूर्णांकel_gt_buffer_pool_node *मुक्त;
		काष्ठा rcu_head rcu;
	पूर्ण;
	अचिन्हित दीर्घ age;
	क्रमागत i915_map_type type;
	u32 pinned;
पूर्ण;

#पूर्ण_अगर /* INTEL_GT_BUFFER_POOL_TYPES_H */
