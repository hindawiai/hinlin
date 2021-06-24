<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित IGT_LIVE_TEST_H
#घोषणा IGT_LIVE_TEST_H

#समावेश "gt/intel_engine.h" /* क्रम I915_NUM_ENGINES */

काष्ठा drm_i915_निजी;

काष्ठा igt_live_test अणु
	काष्ठा drm_i915_निजी *i915;
	स्थिर अक्षर *func;
	स्थिर अक्षर *name;

	अचिन्हित पूर्णांक reset_global;
	अचिन्हित पूर्णांक reset_engine[I915_NUM_ENGINES];
पूर्ण;

/*
 * Flush the GPU state beक्रमe and after the test to ensure that no residual
 * code is running on the GPU that may affect this test. Also compare the
 * state beक्रमe and after the test and alert अगर it unexpectedly changes,
 * e.g. अगर the GPU was reset.
 */
पूर्णांक igt_live_test_begin(काष्ठा igt_live_test *t,
			काष्ठा drm_i915_निजी *i915,
			स्थिर अक्षर *func,
			स्थिर अक्षर *name);
पूर्णांक igt_live_test_end(काष्ठा igt_live_test *t);

#पूर्ण_अगर /* IGT_LIVE_TEST_H */
