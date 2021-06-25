<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश "i915_selftest.h"
#समावेश "selftest_engine.h"

पूर्णांक पूर्णांकel_engine_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल पूर्णांक (* स्थिर tests[])(काष्ठा पूर्णांकel_gt *) = अणु
		live_engine_pm_selftests,
		शून्य,
	पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	typeof(*tests) *fn;

	क्रम (fn = tests; *fn; fn++) अणु
		पूर्णांक err;

		err = (*fn)(gt);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
