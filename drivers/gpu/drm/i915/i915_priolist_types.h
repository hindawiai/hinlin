<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#अगर_अघोषित _I915_PRIOLIST_TYPES_H_
#घोषणा _I915_PRIOLIST_TYPES_H_

#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>

#समावेश <uapi/drm/i915_drm.h>

क्रमागत अणु
	I915_PRIORITY_MIN = I915_CONTEXT_MIN_USER_PRIORITY - 1,
	I915_PRIORITY_NORMAL = I915_CONTEXT_DEFAULT_PRIORITY,
	I915_PRIORITY_MAX = I915_CONTEXT_MAX_USER_PRIORITY + 1,

	/* A preemptive pulse used to monitor the health of each engine */
	I915_PRIORITY_HEARTBEAT,

	/* Interactive workload, scheduled क्रम immediate pageflipping */
	I915_PRIORITY_DISPLAY,
पूर्ण;

/* Smallest priority value that cannot be bumped. */
#घोषणा I915_PRIORITY_INVALID (पूर्णांक_न्यून)

/*
 * Requests containing perक्रमmance queries must not be preempted by
 * another context. They get scheduled with their शेष priority and
 * once they reach the execlist ports we ensure that they stick on the
 * HW until finished by pretending that they have maximum priority,
 * i.e. nothing can have higher priority and क्रमce us to usurp the
 * active request.
 */
#घोषणा I915_PRIORITY_UNPREEMPTABLE पूर्णांक_उच्च
#घोषणा I915_PRIORITY_BARRIER (I915_PRIORITY_UNPREEMPTABLE - 1)

काष्ठा i915_priolist अणु
	काष्ठा list_head requests;
	काष्ठा rb_node node;
	पूर्णांक priority;
पूर्ण;

#पूर्ण_अगर /* _I915_PRIOLIST_TYPES_H_ */
