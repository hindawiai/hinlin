<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/suspend.h>

#समावेश "i915_drv.h"
#समावेश "i915_globals.h"
#समावेश "i915_params.h"
#समावेश "intel_context.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_clock_utils.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_llc.h"
#समावेश "intel_pm.h"
#समावेश "intel_rc6.h"
#समावेश "intel_rps.h"
#समावेश "intel_wakeref.h"

अटल व्योम user_क्रमcewake(काष्ठा पूर्णांकel_gt *gt, bool suspend)
अणु
	पूर्णांक count = atomic_पढ़ो(&gt->user_wakeref);

	/* Inside suspend/resume so single thपढ़ोed, no races to worry about. */
	अगर (likely(!count))
		वापस;

	पूर्णांकel_gt_pm_get(gt);
	अगर (suspend) अणु
		GEM_BUG_ON(count > atomic_पढ़ो(&gt->wakeref.count));
		atomic_sub(count, &gt->wakeref.count);
	पूर्ण अन्यथा अणु
		atomic_add(count, &gt->wakeref.count);
	पूर्ण
	पूर्णांकel_gt_pm_put(gt);
पूर्ण

अटल व्योम runसमय_begin(काष्ठा पूर्णांकel_gt *gt)
अणु
	local_irq_disable();
	ग_लिखो_seqcount_begin(&gt->stats.lock);
	gt->stats.start = kसमय_get();
	gt->stats.active = true;
	ग_लिखो_seqcount_end(&gt->stats.lock);
	local_irq_enable();
पूर्ण

अटल व्योम runसमय_end(काष्ठा पूर्णांकel_gt *gt)
अणु
	local_irq_disable();
	ग_लिखो_seqcount_begin(&gt->stats.lock);
	gt->stats.active = false;
	gt->stats.total =
		kसमय_add(gt->stats.total,
			  kसमय_sub(kसमय_get(), gt->stats.start));
	ग_लिखो_seqcount_end(&gt->stats.lock);
	local_irq_enable();
पूर्ण

अटल पूर्णांक __gt_unpark(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	काष्ठा पूर्णांकel_gt *gt = container_of(wf, typeof(*gt), wakeref);
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	GT_TRACE(gt, "\n");

	i915_globals_unpark();

	/*
	 * It seems that the DMC likes to transition between the DC states a lot
	 * when there are no connected displays (no active घातer करोमुख्यs) during
	 * command submission.
	 *
	 * This activity has negative impact on the perक्रमmance of the chip with
	 * huge latencies observed in the पूर्णांकerrupt handler and अन्यथाwhere.
	 *
	 * Work around it by grabbing a GT IRQ घातer करोमुख्य whilst there is any
	 * GT activity, preventing any DC state transitions.
	 */
	gt->awake = पूर्णांकel_display_घातer_get(i915, POWER_DOMAIN_GT_IRQ);
	GEM_BUG_ON(!gt->awake);

	पूर्णांकel_rc6_unpark(&gt->rc6);
	पूर्णांकel_rps_unpark(&gt->rps);
	i915_pmu_gt_unparked(i915);

	पूर्णांकel_gt_unpark_requests(gt);
	runसमय_begin(gt);

	वापस 0;
पूर्ण

अटल पूर्णांक __gt_park(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	काष्ठा पूर्णांकel_gt *gt = container_of(wf, typeof(*gt), wakeref);
	पूर्णांकel_wakeref_t wakeref = fetch_and_zero(&gt->awake);
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	GT_TRACE(gt, "\n");

	runसमय_end(gt);
	पूर्णांकel_gt_park_requests(gt);

	i915_vma_parked(gt);
	i915_pmu_gt_parked(i915);
	पूर्णांकel_rps_park(&gt->rps);
	पूर्णांकel_rc6_park(&gt->rc6);

	/* Everything चयनed off, flush any residual पूर्णांकerrupt just in हाल */
	पूर्णांकel_synchronize_irq(i915);

	/* Defer dropping the display घातer well क्रम 100ms, it's slow! */
	GEM_BUG_ON(!wakeref);
	पूर्णांकel_display_घातer_put_async(i915, POWER_DOMAIN_GT_IRQ, wakeref);

	i915_globals_park();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_wakeref_ops wf_ops = अणु
	.get = __gt_unpark,
	.put = __gt_park,
पूर्ण;

व्योम पूर्णांकel_gt_pm_init_early(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_wakeref_init(&gt->wakeref, gt->uncore->rpm, &wf_ops);
	seqcount_mutex_init(&gt->stats.lock, &gt->wakeref.mutex);
पूर्ण

व्योम पूर्णांकel_gt_pm_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	/*
	 * Enabling घातer-management should be "self-healing". If we cannot
	 * enable a feature, simply leave it disabled with a notice to the
	 * user.
	 */
	पूर्णांकel_rc6_init(&gt->rc6);
	पूर्णांकel_rps_init(&gt->rps);
पूर्ण

अटल bool reset_engines(काष्ठा पूर्णांकel_gt *gt)
अणु
	अगर (INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		वापस false;

	वापस __पूर्णांकel_gt_reset(gt, ALL_ENGINES) == 0;
पूर्ण

अटल व्योम gt_sanitize(काष्ठा पूर्णांकel_gt *gt, bool क्रमce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांकel_wakeref_t wakeref;

	GT_TRACE(gt, "force:%s", yesno(क्रमce));

	/* Use a raw wakeref to aव्योम calling पूर्णांकel_display_घातer_get early */
	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);
	पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);

	पूर्णांकel_gt_check_घड़ी_frequency(gt);

	/*
	 * As we have just resumed the machine and woken the device up from
	 * deep PCI sleep (presumably D3_cold), assume the HW has been reset
	 * back to शेषs, recovering from whatever wedged state we left it
	 * in and so worth trying to use the device once more.
	 */
	अगर (पूर्णांकel_gt_is_wedged(gt))
		पूर्णांकel_gt_unset_wedged(gt);

	पूर्णांकel_uc_sanitize(&gt->uc);

	क्रम_each_engine(engine, gt, id)
		अगर (engine->reset.prepare)
			engine->reset.prepare(engine);

	पूर्णांकel_uc_reset_prepare(&gt->uc);

	क्रम_each_engine(engine, gt, id)
		अगर (engine->sanitize)
			engine->sanitize(engine);

	अगर (reset_engines(gt) || क्रमce) अणु
		क्रम_each_engine(engine, gt, id)
			__पूर्णांकel_engine_reset(engine, false);
	पूर्ण

	क्रम_each_engine(engine, gt, id)
		अगर (engine->reset.finish)
			engine->reset.finish(engine);

	पूर्णांकel_rps_sanitize(&gt->rps);

	पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
पूर्ण

व्योम पूर्णांकel_gt_pm_fini(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_rc6_fini(&gt->rc6);
पूर्ण

पूर्णांक पूर्णांकel_gt_resume(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err;

	err = पूर्णांकel_gt_has_unrecoverable_error(gt);
	अगर (err)
		वापस err;

	GT_TRACE(gt, "\n");

	/*
	 * After resume, we may need to poke पूर्णांकo the pinned kernel
	 * contexts to paper over any damage caused by the sudden suspend.
	 * Only the kernel contexts should reमुख्य pinned over suspend,
	 * allowing us to fixup the user contexts on their first pin.
	 */
	gt_sanitize(gt, true);

	पूर्णांकel_gt_pm_get(gt);

	पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);
	पूर्णांकel_rc6_sanitize(&gt->rc6);
	अगर (पूर्णांकel_gt_is_wedged(gt)) अणु
		err = -EIO;
		जाओ out_fw;
	पूर्ण

	/* Only when the HW is re-initialised, can we replay the requests */
	err = पूर्णांकel_gt_init_hw(gt);
	अगर (err) अणु
		i915_probe_error(gt->i915,
				 "Failed to initialize GPU, declaring it wedged!\n");
		जाओ err_wedged;
	पूर्ण

	पूर्णांकel_rps_enable(&gt->rps);
	पूर्णांकel_llc_enable(&gt->llc);

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांकel_engine_pm_get(engine);

		engine->serial++; /* kernel context lost */
		err = पूर्णांकel_engine_resume(engine);

		पूर्णांकel_engine_pm_put(engine);
		अगर (err) अणु
			drm_err(&gt->i915->drm,
				"Failed to restart %s (%d)\n",
				engine->name, err);
			जाओ err_wedged;
		पूर्ण
	पूर्ण

	पूर्णांकel_rc6_enable(&gt->rc6);

	पूर्णांकel_uc_resume(&gt->uc);

	user_क्रमcewake(gt, false);

out_fw:
	पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);
	पूर्णांकel_gt_pm_put(gt);
	वापस err;

err_wedged:
	पूर्णांकel_gt_set_wedged(gt);
	जाओ out_fw;
पूर्ण

अटल व्योम रुको_क्रम_suspend(काष्ठा पूर्णांकel_gt *gt)
अणु
	अगर (!पूर्णांकel_gt_pm_is_awake(gt))
		वापस;

	अगर (पूर्णांकel_gt_रुको_क्रम_idle(gt, I915_GEM_IDLE_TIMEOUT) == -ETIME) अणु
		/*
		 * Forcibly cancel outstanding work and leave
		 * the gpu quiet.
		 */
		पूर्णांकel_gt_set_wedged(gt);
		पूर्णांकel_gt_retire_requests(gt);
	पूर्ण

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
पूर्ण

व्योम पूर्णांकel_gt_suspend_prepare(काष्ठा पूर्णांकel_gt *gt)
अणु
	user_क्रमcewake(gt, true);
	रुको_क्रम_suspend(gt);

	पूर्णांकel_uc_suspend(&gt->uc);
पूर्ण

अटल suspend_state_t pm_suspend_target(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SUSPEND) && IS_ENABLED(CONFIG_PM_SLEEP)
	वापस pm_suspend_target_state;
#अन्यथा
	वापस PM_SUSPEND_TO_IDLE;
#पूर्ण_अगर
पूर्ण

व्योम पूर्णांकel_gt_suspend_late(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_wakeref_t wakeref;

	/* We expect to be idle alपढ़ोy; but also want to be independent */
	रुको_क्रम_suspend(gt);

	अगर (is_mock_gt(gt))
		वापस;

	GEM_BUG_ON(gt->awake);

	/*
	 * On disabling the device, we want to turn off HW access to memory
	 * that we no दीर्घer own.
	 *
	 * However, not all suspend-states disable the device. S0 (s2idle)
	 * is effectively runसमय-suspend, the device is left घातered on
	 * but needs to be put पूर्णांकo a low घातer state. We need to keep
	 * घातermanagement enabled, but we also retain प्रणाली state and so
	 * it reमुख्यs safe to keep on using our allocated memory.
	 */
	अगर (pm_suspend_target() == PM_SUSPEND_TO_IDLE)
		वापस;

	with_पूर्णांकel_runसमय_pm(gt->uncore->rpm, wakeref) अणु
		पूर्णांकel_rps_disable(&gt->rps);
		पूर्णांकel_rc6_disable(&gt->rc6);
		पूर्णांकel_llc_disable(&gt->llc);
	पूर्ण

	gt_sanitize(gt, false);

	GT_TRACE(gt, "\n");
पूर्ण

व्योम पूर्णांकel_gt_runसमय_suspend(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_uc_runसमय_suspend(&gt->uc);

	GT_TRACE(gt, "\n");
पूर्ण

पूर्णांक पूर्णांकel_gt_runसमय_resume(काष्ठा पूर्णांकel_gt *gt)
अणु
	GT_TRACE(gt, "\n");
	पूर्णांकel_gt_init_swizzling(gt);
	पूर्णांकel_ggtt_restore_fences(gt->ggtt);

	वापस पूर्णांकel_uc_runसमय_resume(&gt->uc);
पूर्ण

अटल kसमय_प्रकार __पूर्णांकel_gt_get_awake_समय(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	kसमय_प्रकार total = gt->stats.total;

	अगर (gt->stats.active)
		total = kसमय_add(total,
				  kसमय_sub(kसमय_get(), gt->stats.start));

	वापस total;
पूर्ण

kसमय_प्रकार पूर्णांकel_gt_get_awake_समय(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार total;

	करो अणु
		seq = पढ़ो_seqcount_begin(&gt->stats.lock);
		total = __पूर्णांकel_gt_get_awake_समय(gt);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&gt->stats.lock, seq));

	वापस total;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_gt_pm.c"
#पूर्ण_अगर
