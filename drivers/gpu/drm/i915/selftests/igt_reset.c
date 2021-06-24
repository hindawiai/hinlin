<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश "igt_reset.h"

#समावेश "gt/intel_engine.h"
#समावेश "gt/intel_gt.h"

#समावेश "../i915_drv.h"

व्योम igt_global_reset_lock(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	pr_debug("%s: current gpu_error=%08lx\n", __func__, gt->reset.flags);

	जबतक (test_and_set_bit(I915_RESET_BACKOFF, &gt->reset.flags))
		रुको_event(gt->reset.queue,
			   !test_bit(I915_RESET_BACKOFF, &gt->reset.flags));

	क्रम_each_engine(engine, gt, id) अणु
		जबतक (test_and_set_bit(I915_RESET_ENGINE + id,
					&gt->reset.flags))
			रुको_on_bit(&gt->reset.flags, I915_RESET_ENGINE + id,
				    TASK_UNINTERRUPTIBLE);
	पूर्ण
पूर्ण

व्योम igt_global_reset_unlock(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id)
		clear_bit(I915_RESET_ENGINE + id, &gt->reset.flags);

	clear_bit(I915_RESET_BACKOFF, &gt->reset.flags);
	wake_up_all(&gt->reset.queue);
पूर्ण

bool igt_क्रमce_reset(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_gt_set_wedged(gt);
	पूर्णांकel_gt_reset(gt, 0, शून्य);

	वापस !पूर्णांकel_gt_is_wedged(gt);
पूर्ण
