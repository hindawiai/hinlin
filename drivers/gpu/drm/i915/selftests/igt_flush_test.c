<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_requests.h"

#समावेश "i915_drv.h"
#समावेश "i915_selftest.h"

#समावेश "igt_flush_test.h"

पूर्णांक igt_flush_test(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	पूर्णांक ret = पूर्णांकel_gt_is_wedged(gt) ? -EIO : 0;

	cond_resched();

	अगर (पूर्णांकel_gt_रुको_क्रम_idle(gt, HZ / 5) == -ETIME) अणु
		pr_err("%pS timed out, cancelling all further testing.\n",
		       __builtin_वापस_address(0));

		GEM_TRACE("%pS timed out.\n",
			  __builtin_वापस_address(0));
		GEM_TRACE_DUMP();

		पूर्णांकel_gt_set_wedged(gt);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण
