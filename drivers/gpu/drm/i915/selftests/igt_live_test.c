<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "gt/intel_gt_requests.h"

#समावेश "../i915_selftest.h"
#समावेश "igt_flush_test.h"
#समावेश "igt_live_test.h"

पूर्णांक igt_live_test_begin(काष्ठा igt_live_test *t,
			काष्ठा drm_i915_निजी *i915,
			स्थिर अक्षर *func,
			स्थिर अक्षर *name)
अणु
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err;

	t->i915 = i915;
	t->func = func;
	t->name = name;

	err = पूर्णांकel_gt_रुको_क्रम_idle(gt, MAX_SCHEDULE_TIMEOUT);
	अगर (err) अणु
		pr_err("%s(%s): failed to idle before, with err=%d!",
		       func, name, err);
		वापस err;
	पूर्ण

	t->reset_global = i915_reset_count(&i915->gpu_error);

	क्रम_each_engine(engine, gt, id)
		t->reset_engine[id] =
			i915_reset_engine_count(&i915->gpu_error, engine);

	वापस 0;
पूर्ण

पूर्णांक igt_live_test_end(काष्ठा igt_live_test *t)
अणु
	काष्ठा drm_i915_निजी *i915 = t->i915;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	अगर (igt_flush_test(i915))
		वापस -EIO;

	अगर (t->reset_global != i915_reset_count(&i915->gpu_error)) अणु
		pr_err("%s(%s): GPU was reset %d times!\n",
		       t->func, t->name,
		       i915_reset_count(&i915->gpu_error) - t->reset_global);
		वापस -EIO;
	पूर्ण

	क्रम_each_engine(engine, &i915->gt, id) अणु
		अगर (t->reset_engine[id] ==
		    i915_reset_engine_count(&i915->gpu_error, engine))
			जारी;

		pr_err("%s(%s): engine '%s' was reset %d times!\n",
		       t->func, t->name, engine->name,
		       i915_reset_engine_count(&i915->gpu_error, engine) -
		       t->reset_engine[id]);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
