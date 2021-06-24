<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/sort.h>

#समावेश "intel_gt_clock_utils.h"

#समावेश "selftest_llc.h"
#समावेश "selftest_rc6.h"
#समावेश "selftest_rps.h"

अटल पूर्णांक cmp_u64(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर u64 *a = A, *b = B;

	अगर (a < b)
		वापस -1;
	अन्यथा अगर (a > b)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक cmp_u32(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर u32 *a = A, *b = B;

	अगर (a < b)
		वापस -1;
	अन्यथा अगर (a > b)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम measure_घड़ीs(काष्ठा पूर्णांकel_engine_cs *engine,
			   u32 *out_cycles, kसमय_प्रकार *out_dt)
अणु
	kसमय_प्रकार dt[5];
	u32 cycles[5];
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		preempt_disable();
		cycles[i] = -ENGINE_READ_FW(engine, RING_TIMESTAMP);
		dt[i] = kसमय_get();

		udelay(1000);

		dt[i] = kसमय_sub(kसमय_get(), dt[i]);
		cycles[i] += ENGINE_READ_FW(engine, RING_TIMESTAMP);
		preempt_enable();
	पूर्ण

	/* Use the median of both cycle/dt; बंद enough */
	sort(cycles, 5, माप(*cycles), cmp_u32, शून्य);
	*out_cycles = (cycles[1] + 2 * cycles[2] + cycles[3]) / 4;

	sort(dt, 5, माप(*dt), cmp_u64, शून्य);
	*out_dt = भाग_u64(dt[1] + 2 * dt[2] + dt[3], 4);
पूर्ण

अटल पूर्णांक live_gt_घड़ीs(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	अगर (!gt->घड़ी_frequency) अणु /* unknown */
		pr_info("CS_TIMESTAMP frequency unknown\n");
		वापस 0;
	पूर्ण

	अगर (INTEL_GEN(gt->i915) < 4) /* Any CS_TIMESTAMP? */
		वापस 0;

	अगर (IS_GEN(gt->i915, 5))
		/*
		 * XXX CS_TIMESTAMP low dword is dysfunctional?
		 *
		 * Ville's experiments indicate the high dword still works,
		 * but at a correspondingly reduced frequency.
		 */
		वापस 0;

	अगर (IS_GEN(gt->i915, 4))
		/*
		 * XXX CS_TIMESTAMP appears gibberish
		 *
		 * Ville's experiments indicate that it mostly appears 'stuck'
		 * in that we see the रेजिस्टर report the same cycle count
		 * क्रम a couple of पढ़ोs.
		 */
		वापस 0;

	पूर्णांकel_gt_pm_get(gt);
	पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);

	क्रम_each_engine(engine, gt, id) अणु
		u32 cycles;
		u32 expected;
		u64 समय;
		u64 dt;

		अगर (INTEL_GEN(engine->i915) < 7 && engine->id != RCS0)
			जारी;

		measure_घड़ीs(engine, &cycles, &dt);

		समय = पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(engine->gt, cycles);
		expected = पूर्णांकel_gt_ns_to_घड़ी_पूर्णांकerval(engine->gt, dt);

		pr_info("%s: TIMESTAMP %d cycles [%lldns] in %lldns [%d cycles], using CS clock frequency of %uKHz\n",
			engine->name, cycles, समय, dt, expected,
			engine->gt->घड़ी_frequency / 1000);

		अगर (9 * समय < 8 * dt || 8 * समय > 9 * dt) अणु
			pr_err("%s: CS ticks did not match walltime!\n",
			       engine->name);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (9 * expected < 8 * cycles || 8 * expected > 9 * cycles) अणु
			pr_err("%s: walltime did not match CS ticks!\n",
			       engine->name);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);
	पूर्णांकel_gt_pm_put(gt);

	वापस err;
पूर्ण

अटल पूर्णांक live_gt_resume(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	IGT_TIMEOUT(end_समय);
	पूर्णांक err;

	/* Do several suspend/resume cycles to check we करोn't explode! */
	करो अणु
		पूर्णांकel_gt_suspend_prepare(gt);
		पूर्णांकel_gt_suspend_late(gt);

		अगर (gt->rc6.enabled) अणु
			pr_err("rc6 still enabled after suspend!\n");
			पूर्णांकel_gt_set_wedged_on_init(gt);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		err = पूर्णांकel_gt_resume(gt);
		अगर (err)
			अवरोध;

		अगर (gt->rc6.supported && !gt->rc6.enabled) अणु
			pr_err("rc6 not enabled upon resume!\n");
			पूर्णांकel_gt_set_wedged_on_init(gt);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		err = st_llc_verअगरy(&gt->llc);
		अगर (err) अणु
			pr_err("llc state not restored upon resume!\n");
			पूर्णांकel_gt_set_wedged_on_init(gt);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_gt_pm_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_gt_घड़ीs),
		SUBTEST(live_rc6_manual),
		SUBTEST(live_rps_घड़ी_पूर्णांकerval),
		SUBTEST(live_rps_control),
		SUBTEST(live_rps_frequency_cs),
		SUBTEST(live_rps_frequency_srm),
		SUBTEST(live_rps_घातer),
		SUBTEST(live_rps_पूर्णांकerrupt),
		SUBTEST(live_rps_dynamic),
		SUBTEST(live_gt_resume),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण

पूर्णांक पूर्णांकel_gt_pm_late_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		/*
		 * These tests may leave the प्रणाली in an undesirable state.
		 * They are पूर्णांकended to be run last in CI and the प्रणाली
		 * rebooted afterwards.
		 */
		SUBTEST(live_rc6_ctx_wa),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
