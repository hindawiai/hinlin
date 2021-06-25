<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_RC6_TYPES_H
#घोषणा INTEL_RC6_TYPES_H

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश "intel_engine_types.h"

काष्ठा drm_i915_gem_object;

काष्ठा पूर्णांकel_rc6 अणु
	u64 prev_hw_residency[4];
	u64 cur_residency[4];

	u32 ctl_enable;

	काष्ठा drm_i915_gem_object *pctx;

	bool supported : 1;
	bool enabled : 1;
	bool manual : 1;
	bool wakeref : 1;
पूर्ण;

#पूर्ण_अगर /* INTEL_RC6_TYPES_H */
