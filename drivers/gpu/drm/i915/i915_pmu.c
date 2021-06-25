<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017-2018 Intel Corporation
 */

#समावेश <linux/pm_runसमय.स>

#समावेश "gt/intel_engine.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_rc6.h"
#समावेश "gt/intel_rps.h"

#समावेश "i915_drv.h"
#समावेश "i915_pmu.h"
#समावेश "intel_pm.h"

/* Frequency क्रम the sampling समयr क्रम events which need it. */
#घोषणा FREQUENCY 200
#घोषणा PERIOD max_t(u64, 10000, NSEC_PER_SEC / FREQUENCY)

#घोषणा ENGINE_SAMPLE_MASK \
	(BIT(I915_SAMPLE_BUSY) | \
	 BIT(I915_SAMPLE_WAIT) | \
	 BIT(I915_SAMPLE_SEMA))

अटल cpumask_t i915_pmu_cpumask;
अटल अचिन्हित पूर्णांक i915_pmu_target_cpu = -1;

अटल u8 engine_config_sample(u64 config)
अणु
	वापस config & I915_PMU_SAMPLE_MASK;
पूर्ण

अटल u8 engine_event_sample(काष्ठा perf_event *event)
अणु
	वापस engine_config_sample(event->attr.config);
पूर्ण

अटल u8 engine_event_class(काष्ठा perf_event *event)
अणु
	वापस (event->attr.config >> I915_PMU_CLASS_SHIFT) & 0xff;
पूर्ण

अटल u8 engine_event_instance(काष्ठा perf_event *event)
अणु
	वापस (event->attr.config >> I915_PMU_SAMPLE_BITS) & 0xff;
पूर्ण

अटल bool is_engine_config(u64 config)
अणु
	वापस config < __I915_PMU_OTHER(0);
पूर्ण

अटल अचिन्हित पूर्णांक other_bit(स्थिर u64 config)
अणु
	अचिन्हित पूर्णांक val;

	चयन (config) अणु
	हाल I915_PMU_ACTUAL_FREQUENCY:
		val =  __I915_PMU_ACTUAL_FREQUENCY_ENABLED;
		अवरोध;
	हाल I915_PMU_REQUESTED_FREQUENCY:
		val = __I915_PMU_REQUESTED_FREQUENCY_ENABLED;
		अवरोध;
	हाल I915_PMU_RC6_RESIDENCY:
		val = __I915_PMU_RC6_RESIDENCY_ENABLED;
		अवरोध;
	शेष:
		/*
		 * Events that करो not require sampling, or tracking state
		 * transitions between enabled and disabled can be ignored.
		 */
		वापस -1;
	पूर्ण

	वापस I915_ENGINE_SAMPLE_COUNT + val;
पूर्ण

अटल अचिन्हित पूर्णांक config_bit(स्थिर u64 config)
अणु
	अगर (is_engine_config(config))
		वापस engine_config_sample(config);
	अन्यथा
		वापस other_bit(config);
पूर्ण

अटल u64 config_mask(u64 config)
अणु
	वापस BIT_ULL(config_bit(config));
पूर्ण

अटल bool is_engine_event(काष्ठा perf_event *event)
अणु
	वापस is_engine_config(event->attr.config);
पूर्ण

अटल अचिन्हित पूर्णांक event_bit(काष्ठा perf_event *event)
अणु
	वापस config_bit(event->attr.config);
पूर्ण

अटल bool pmu_needs_समयr(काष्ठा i915_pmu *pmu, bool gpu_active)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(pmu, typeof(*i915), pmu);
	u32 enable;

	/*
	 * Only some counters need the sampling समयr.
	 *
	 * We start with a biपंचांगask of all currently enabled events.
	 */
	enable = pmu->enable;

	/*
	 * Mask out all the ones which करो not need the समयr, or in
	 * other words keep all the ones that could need the समयr.
	 */
	enable &= config_mask(I915_PMU_ACTUAL_FREQUENCY) |
		  config_mask(I915_PMU_REQUESTED_FREQUENCY) |
		  ENGINE_SAMPLE_MASK;

	/*
	 * When the GPU is idle per-engine counters करो not need to be
	 * running so clear those bits out.
	 */
	अगर (!gpu_active)
		enable &= ~ENGINE_SAMPLE_MASK;
	/*
	 * Also there is software busyness tracking available we करो not
	 * need the समयr क्रम I915_SAMPLE_BUSY counter.
	 */
	अन्यथा अगर (i915->caps.scheduler & I915_SCHEDULER_CAP_ENGINE_BUSY_STATS)
		enable &= ~BIT(I915_SAMPLE_BUSY);

	/*
	 * If some bits reमुख्य it means we need the sampling समयr running.
	 */
	वापस enable;
पूर्ण

अटल u64 __get_rc6(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	u64 val;

	val = पूर्णांकel_rc6_residency_ns(&gt->rc6,
				     IS_VALLEYVIEW(i915) ?
				     VLV_GT_RENDER_RC6 :
				     GEN6_GT_GFX_RC6);

	अगर (HAS_RC6p(i915))
		val += पूर्णांकel_rc6_residency_ns(&gt->rc6, GEN6_GT_GFX_RC6p);

	अगर (HAS_RC6pp(i915))
		val += पूर्णांकel_rc6_residency_ns(&gt->rc6, GEN6_GT_GFX_RC6pp);

	वापस val;
पूर्ण

अटल अंतरभूत s64 kसमय_since_raw(स्थिर kसमय_प्रकार kt)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_sub(kसमय_get_raw(), kt));
पूर्ण

अटल u64 get_rc6(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा i915_pmu *pmu = &i915->pmu;
	अचिन्हित दीर्घ flags;
	bool awake = false;
	u64 val;

	अगर (पूर्णांकel_gt_pm_get_अगर_awake(gt)) अणु
		val = __get_rc6(gt);
		पूर्णांकel_gt_pm_put_async(gt);
		awake = true;
	पूर्ण

	spin_lock_irqsave(&pmu->lock, flags);

	अगर (awake) अणु
		pmu->sample[__I915_SAMPLE_RC6].cur = val;
	पूर्ण अन्यथा अणु
		/*
		 * We think we are runसमय suspended.
		 *
		 * Report the delta from when the device was suspended to now,
		 * on top of the last known real value, as the approximated RC6
		 * counter value.
		 */
		val = kसमय_since_raw(pmu->sleep_last);
		val += pmu->sample[__I915_SAMPLE_RC6].cur;
	पूर्ण

	अगर (val < pmu->sample[__I915_SAMPLE_RC6_LAST_REPORTED].cur)
		val = pmu->sample[__I915_SAMPLE_RC6_LAST_REPORTED].cur;
	अन्यथा
		pmu->sample[__I915_SAMPLE_RC6_LAST_REPORTED].cur = val;

	spin_unlock_irqrestore(&pmu->lock, flags);

	वापस val;
पूर्ण

अटल व्योम init_rc6(काष्ठा i915_pmu *pmu)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(pmu, typeof(*i915), pmu);
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_runसमय_pm(i915->gt.uncore->rpm, wakeref) अणु
		pmu->sample[__I915_SAMPLE_RC6].cur = __get_rc6(&i915->gt);
		pmu->sample[__I915_SAMPLE_RC6_LAST_REPORTED].cur =
					pmu->sample[__I915_SAMPLE_RC6].cur;
		pmu->sleep_last = kसमय_get_raw();
	पूर्ण
पूर्ण

अटल व्योम park_rc6(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_pmu *pmu = &i915->pmu;

	pmu->sample[__I915_SAMPLE_RC6].cur = __get_rc6(&i915->gt);
	pmu->sleep_last = kसमय_get_raw();
पूर्ण

अटल व्योम __i915_pmu_maybe_start_समयr(काष्ठा i915_pmu *pmu)
अणु
	अगर (!pmu->समयr_enabled && pmu_needs_समयr(pmu, true)) अणु
		pmu->समयr_enabled = true;
		pmu->समयr_last = kसमय_get();
		hrसमयr_start_range_ns(&pmu->समयr,
				       ns_to_kसमय(PERIOD), 0,
				       HRTIMER_MODE_REL_PINNED);
	पूर्ण
पूर्ण

व्योम i915_pmu_gt_parked(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_pmu *pmu = &i915->pmu;

	अगर (!pmu->base.event_init)
		वापस;

	spin_lock_irq(&pmu->lock);

	park_rc6(i915);

	/*
	 * Signal sampling समयr to stop अगर only engine events are enabled and
	 * GPU went idle.
	 */
	pmu->समयr_enabled = pmu_needs_समयr(pmu, false);

	spin_unlock_irq(&pmu->lock);
पूर्ण

व्योम i915_pmu_gt_unparked(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_pmu *pmu = &i915->pmu;

	अगर (!pmu->base.event_init)
		वापस;

	spin_lock_irq(&pmu->lock);

	/*
	 * Re-enable sampling समयr when GPU goes active.
	 */
	__i915_pmu_maybe_start_समयr(pmu);

	spin_unlock_irq(&pmu->lock);
पूर्ण

अटल व्योम
add_sample(काष्ठा i915_pmu_sample *sample, u32 val)
अणु
	sample->cur += val;
पूर्ण

अटल bool exclusive_mmio_access(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	/*
	 * We have to aव्योम concurrent mmio cache line access on gen7 or
	 * risk a machine hang. For a fun history lesson dig out the old
	 * userspace पूर्णांकel_gpu_top and run it on Ivybridge or Haswell!
	 */
	वापस IS_GEN(i915, 7);
पूर्ण

अटल व्योम engine_sample(काष्ठा पूर्णांकel_engine_cs *engine, अचिन्हित पूर्णांक period_ns)
अणु
	काष्ठा पूर्णांकel_engine_pmu *pmu = &engine->pmu;
	bool busy;
	u32 val;

	val = ENGINE_READ_FW(engine, RING_CTL);
	अगर (val == 0) /* घातerwell off => engine idle */
		वापस;

	अगर (val & RING_WAIT)
		add_sample(&pmu->sample[I915_SAMPLE_WAIT], period_ns);
	अगर (val & RING_WAIT_SEMAPHORE)
		add_sample(&pmu->sample[I915_SAMPLE_SEMA], period_ns);

	/* No need to sample when busy stats are supported. */
	अगर (पूर्णांकel_engine_supports_stats(engine))
		वापस;

	/*
	 * While रुकोing on a semaphore or event, MI_MODE reports the
	 * ring as idle. However, previously using the seqno, and with
	 * execlists sampling, we account क्रम the ring रुकोing as the
	 * engine being busy. Thereक्रमe, we record the sample as being
	 * busy अगर either रुकोing or !idle.
	 */
	busy = val & (RING_WAIT_SEMAPHORE | RING_WAIT);
	अगर (!busy) अणु
		val = ENGINE_READ_FW(engine, RING_MI_MODE);
		busy = !(val & MODE_IDLE);
	पूर्ण
	अगर (busy)
		add_sample(&pmu->sample[I915_SAMPLE_BUSY], period_ns);
पूर्ण

अटल व्योम
engines_sample(काष्ठा पूर्णांकel_gt *gt, अचिन्हित पूर्णांक period_ns)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	अचिन्हित दीर्घ flags;

	अगर ((i915->pmu.enable & ENGINE_SAMPLE_MASK) == 0)
		वापस;

	अगर (!पूर्णांकel_gt_pm_is_awake(gt))
		वापस;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (!पूर्णांकel_engine_pm_get_अगर_awake(engine))
			जारी;

		अगर (exclusive_mmio_access(i915)) अणु
			spin_lock_irqsave(&engine->uncore->lock, flags);
			engine_sample(engine, period_ns);
			spin_unlock_irqrestore(&engine->uncore->lock, flags);
		पूर्ण अन्यथा अणु
			engine_sample(engine, period_ns);
		पूर्ण

		पूर्णांकel_engine_pm_put_async(engine);
	पूर्ण
पूर्ण

अटल व्योम
add_sample_mult(काष्ठा i915_pmu_sample *sample, u32 val, u32 mul)
अणु
	sample->cur += mul_u32_u32(val, mul);
पूर्ण

अटल bool frequency_sampling_enabled(काष्ठा i915_pmu *pmu)
अणु
	वापस pmu->enable &
	       (config_mask(I915_PMU_ACTUAL_FREQUENCY) |
		config_mask(I915_PMU_REQUESTED_FREQUENCY));
पूर्ण

अटल व्योम
frequency_sample(काष्ठा पूर्णांकel_gt *gt, अचिन्हित पूर्णांक period_ns)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	काष्ठा i915_pmu *pmu = &i915->pmu;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;

	अगर (!frequency_sampling_enabled(pmu))
		वापस;

	/* Report 0/0 (actual/requested) frequency जबतक parked. */
	अगर (!पूर्णांकel_gt_pm_get_अगर_awake(gt))
		वापस;

	अगर (pmu->enable & config_mask(I915_PMU_ACTUAL_FREQUENCY)) अणु
		u32 val;

		/*
		 * We take a quick peek here without using क्रमcewake
		 * so that we करोn't perturb the प्रणाली under observation
		 * (क्रमcewake => !rc6 => increased घातer use). We expect
		 * that अगर the पढ़ो fails because it is outside of the
		 * mmio घातer well, then it will वापस 0 -- in which
		 * हाल we assume the प्रणाली is running at the पूर्णांकended
		 * frequency. Fortunately, the पढ़ो should rarely fail!
		 */
		val = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN6_RPSTAT1);
		अगर (val)
			val = पूर्णांकel_rps_get_cagf(rps, val);
		अन्यथा
			val = rps->cur_freq;

		add_sample_mult(&pmu->sample[__I915_SAMPLE_FREQ_ACT],
				पूर्णांकel_gpu_freq(rps, val), period_ns / 1000);
	पूर्ण

	अगर (pmu->enable & config_mask(I915_PMU_REQUESTED_FREQUENCY)) अणु
		add_sample_mult(&pmu->sample[__I915_SAMPLE_FREQ_REQ],
				पूर्णांकel_gpu_freq(rps, rps->cur_freq),
				period_ns / 1000);
	पूर्ण

	पूर्णांकel_gt_pm_put_async(gt);
पूर्ण

अटल क्रमागत hrसमयr_restart i915_sample(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(hrसमयr, काष्ठा drm_i915_निजी, pmu.समयr);
	काष्ठा i915_pmu *pmu = &i915->pmu;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	अचिन्हित पूर्णांक period_ns;
	kसमय_प्रकार now;

	अगर (!READ_ONCE(pmu->समयr_enabled))
		वापस HRTIMER_NORESTART;

	now = kसमय_get();
	period_ns = kसमय_प्रकारo_ns(kसमय_sub(now, pmu->समयr_last));
	pmu->समयr_last = now;

	/*
	 * Strictly speaking the passed in period may not be 100% accurate क्रम
	 * all पूर्णांकernal calculation, since some amount of समय can be spent on
	 * grabbing the क्रमcewake. However the potential error from समयr call-
	 * back delay greatly करोminates this so we keep it simple.
	 */
	engines_sample(gt, period_ns);
	frequency_sample(gt, period_ns);

	hrसमयr_क्रमward(hrसमयr, now, ns_to_kसमय(PERIOD));

	वापस HRTIMER_RESTART;
पूर्ण

अटल व्योम i915_pmu_event_destroy(काष्ठा perf_event *event)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);

	drm_WARN_ON(&i915->drm, event->parent);

	drm_dev_put(&i915->drm);
पूर्ण

अटल पूर्णांक
engine_event_status(काष्ठा पूर्णांकel_engine_cs *engine,
		    क्रमागत drm_i915_pmu_engine_sample sample)
अणु
	चयन (sample) अणु
	हाल I915_SAMPLE_BUSY:
	हाल I915_SAMPLE_WAIT:
		अवरोध;
	हाल I915_SAMPLE_SEMA:
		अगर (INTEL_GEN(engine->i915) < 6)
			वापस -ENODEV;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
config_status(काष्ठा drm_i915_निजी *i915, u64 config)
अणु
	चयन (config) अणु
	हाल I915_PMU_ACTUAL_FREQUENCY:
		अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
			/* Requires a mutex क्रम sampling! */
			वापस -ENODEV;
		fallthrough;
	हाल I915_PMU_REQUESTED_FREQUENCY:
		अगर (INTEL_GEN(i915) < 6)
			वापस -ENODEV;
		अवरोध;
	हाल I915_PMU_INTERRUPTS:
		अवरोध;
	हाल I915_PMU_RC6_RESIDENCY:
		अगर (!HAS_RC6(i915))
			वापस -ENODEV;
		अवरोध;
	हाल I915_PMU_SOFTWARE_GT_AWAKE_TIME:
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक engine_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	काष्ठा पूर्णांकel_engine_cs *engine;

	engine = पूर्णांकel_engine_lookup_user(i915, engine_event_class(event),
					  engine_event_instance(event));
	अगर (!engine)
		वापस -ENODEV;

	वापस engine_event_status(engine, engine_event_sample(event));
पूर्ण

अटल पूर्णांक i915_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	काष्ठा i915_pmu *pmu = &i915->pmu;
	पूर्णांक ret;

	अगर (pmu->बंदd)
		वापस -ENODEV;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* unsupported modes and filters */
	अगर (event->attr.sample_period) /* no sampling */
		वापस -EINVAL;

	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	/* only allow running on one cpu at a समय */
	अगर (!cpumask_test_cpu(event->cpu, &i915_pmu_cpumask))
		वापस -EINVAL;

	अगर (is_engine_event(event))
		ret = engine_event_init(event);
	अन्यथा
		ret = config_status(i915, event->attr.config);
	अगर (ret)
		वापस ret;

	अगर (!event->parent) अणु
		drm_dev_get(&i915->drm);
		event->destroy = i915_pmu_event_destroy;
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 __i915_pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	काष्ठा i915_pmu *pmu = &i915->pmu;
	u64 val = 0;

	अगर (is_engine_event(event)) अणु
		u8 sample = engine_event_sample(event);
		काष्ठा पूर्णांकel_engine_cs *engine;

		engine = पूर्णांकel_engine_lookup_user(i915,
						  engine_event_class(event),
						  engine_event_instance(event));

		अगर (drm_WARN_ON_ONCE(&i915->drm, !engine)) अणु
			/* Do nothing */
		पूर्ण अन्यथा अगर (sample == I915_SAMPLE_BUSY &&
			   पूर्णांकel_engine_supports_stats(engine)) अणु
			kसमय_प्रकार unused;

			val = kसमय_प्रकारo_ns(पूर्णांकel_engine_get_busy_समय(engine,
								     &unused));
		पूर्ण अन्यथा अणु
			val = engine->pmu.sample[sample].cur;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (event->attr.config) अणु
		हाल I915_PMU_ACTUAL_FREQUENCY:
			val =
			   भाग_u64(pmu->sample[__I915_SAMPLE_FREQ_ACT].cur,
				   USEC_PER_SEC /* to MHz */);
			अवरोध;
		हाल I915_PMU_REQUESTED_FREQUENCY:
			val =
			   भाग_u64(pmu->sample[__I915_SAMPLE_FREQ_REQ].cur,
				   USEC_PER_SEC /* to MHz */);
			अवरोध;
		हाल I915_PMU_INTERRUPTS:
			val = READ_ONCE(pmu->irq_count);
			अवरोध;
		हाल I915_PMU_RC6_RESIDENCY:
			val = get_rc6(&i915->gt);
			अवरोध;
		हाल I915_PMU_SOFTWARE_GT_AWAKE_TIME:
			val = kसमय_प्रकारo_ns(पूर्णांकel_gt_get_awake_समय(&i915->gt));
			अवरोध;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम i915_pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा i915_pmu *pmu = &i915->pmu;
	u64 prev, new;

	अगर (pmu->बंदd) अणु
		event->hw.state = PERF_HES_STOPPED;
		वापस;
	पूर्ण
again:
	prev = local64_पढ़ो(&hwc->prev_count);
	new = __i915_pmu_event_पढ़ो(event);

	अगर (local64_cmpxchg(&hwc->prev_count, prev, new) != prev)
		जाओ again;

	local64_add(new - prev, &event->count);
पूर्ण

अटल व्योम i915_pmu_enable(काष्ठा perf_event *event)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	काष्ठा i915_pmu *pmu = &i915->pmu;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bit;

	bit = event_bit(event);
	अगर (bit == -1)
		जाओ update;

	spin_lock_irqsave(&pmu->lock, flags);

	/*
	 * Update the biपंचांगask of enabled events and increment
	 * the event reference counter.
	 */
	BUILD_BUG_ON(ARRAY_SIZE(pmu->enable_count) != I915_PMU_MASK_BITS);
	GEM_BUG_ON(bit >= ARRAY_SIZE(pmu->enable_count));
	GEM_BUG_ON(pmu->enable_count[bit] == ~0);

	pmu->enable |= BIT_ULL(bit);
	pmu->enable_count[bit]++;

	/*
	 * Start the sampling समयr अगर needed and not alपढ़ोy enabled.
	 */
	__i915_pmu_maybe_start_समयr(pmu);

	/*
	 * For per-engine events the biपंचांगask and reference counting
	 * is stored per engine.
	 */
	अगर (is_engine_event(event)) अणु
		u8 sample = engine_event_sample(event);
		काष्ठा पूर्णांकel_engine_cs *engine;

		engine = पूर्णांकel_engine_lookup_user(i915,
						  engine_event_class(event),
						  engine_event_instance(event));

		BUILD_BUG_ON(ARRAY_SIZE(engine->pmu.enable_count) !=
			     I915_ENGINE_SAMPLE_COUNT);
		BUILD_BUG_ON(ARRAY_SIZE(engine->pmu.sample) !=
			     I915_ENGINE_SAMPLE_COUNT);
		GEM_BUG_ON(sample >= ARRAY_SIZE(engine->pmu.enable_count));
		GEM_BUG_ON(sample >= ARRAY_SIZE(engine->pmu.sample));
		GEM_BUG_ON(engine->pmu.enable_count[sample] == ~0);

		engine->pmu.enable |= BIT(sample);
		engine->pmu.enable_count[sample]++;
	पूर्ण

	spin_unlock_irqrestore(&pmu->lock, flags);

update:
	/*
	 * Store the current counter value so we can report the correct delta
	 * क्रम all listeners. Even when the event was alपढ़ोy enabled and has
	 * an existing non-zero value.
	 */
	local64_set(&event->hw.prev_count, __i915_pmu_event_पढ़ो(event));
पूर्ण

अटल व्योम i915_pmu_disable(काष्ठा perf_event *event)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	अचिन्हित पूर्णांक bit = event_bit(event);
	काष्ठा i915_pmu *pmu = &i915->pmu;
	अचिन्हित दीर्घ flags;

	अगर (bit == -1)
		वापस;

	spin_lock_irqsave(&pmu->lock, flags);

	अगर (is_engine_event(event)) अणु
		u8 sample = engine_event_sample(event);
		काष्ठा पूर्णांकel_engine_cs *engine;

		engine = पूर्णांकel_engine_lookup_user(i915,
						  engine_event_class(event),
						  engine_event_instance(event));

		GEM_BUG_ON(sample >= ARRAY_SIZE(engine->pmu.enable_count));
		GEM_BUG_ON(sample >= ARRAY_SIZE(engine->pmu.sample));
		GEM_BUG_ON(engine->pmu.enable_count[sample] == 0);

		/*
		 * Decrement the reference count and clear the enabled
		 * biपंचांगask when the last listener on an event goes away.
		 */
		अगर (--engine->pmu.enable_count[sample] == 0)
			engine->pmu.enable &= ~BIT(sample);
	पूर्ण

	GEM_BUG_ON(bit >= ARRAY_SIZE(pmu->enable_count));
	GEM_BUG_ON(pmu->enable_count[bit] == 0);
	/*
	 * Decrement the reference count and clear the enabled
	 * biपंचांगask when the last listener on an event goes away.
	 */
	अगर (--pmu->enable_count[bit] == 0) अणु
		pmu->enable &= ~BIT_ULL(bit);
		pmu->समयr_enabled &= pmu_needs_समयr(pmu, true);
	पूर्ण

	spin_unlock_irqrestore(&pmu->lock, flags);
पूर्ण

अटल व्योम i915_pmu_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	काष्ठा i915_pmu *pmu = &i915->pmu;

	अगर (pmu->बंदd)
		वापस;

	i915_pmu_enable(event);
	event->hw.state = 0;
पूर्ण

अटल व्योम i915_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_UPDATE)
		i915_pmu_event_पढ़ो(event);
	i915_pmu_disable(event);
	event->hw.state = PERF_HES_STOPPED;
पूर्ण

अटल पूर्णांक i915_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(event->pmu, typeof(*i915), pmu.base);
	काष्ठा i915_pmu *pmu = &i915->pmu;

	अगर (pmu->बंदd)
		वापस -ENODEV;

	अगर (flags & PERF_EF_START)
		i915_pmu_event_start(event, flags);

	वापस 0;
पूर्ण

अटल व्योम i915_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	i915_pmu_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक i915_pmu_event_event_idx(काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण

काष्ठा i915_str_attribute अणु
	काष्ठा device_attribute attr;
	स्थिर अक्षर *str;
पूर्ण;

अटल sमाप_प्रकार i915_pmu_क्रमmat_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i915_str_attribute *eattr;

	eattr = container_of(attr, काष्ठा i915_str_attribute, attr);
	वापस प्र_लिखो(buf, "%s\n", eattr->str);
पूर्ण

#घोषणा I915_PMU_FORMAT_ATTR(_name, _config) \
	(&((काष्ठा i915_str_attribute[]) अणु \
		अणु .attr = __ATTR(_name, 0444, i915_pmu_क्रमmat_show, शून्य), \
		  .str = _config, पूर्ण \
	पूर्ण)[0].attr.attr)

अटल काष्ठा attribute *i915_pmu_क्रमmat_attrs[] = अणु
	I915_PMU_FORMAT_ATTR(i915_eventid, "config:0-20"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group i915_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = i915_pmu_क्रमmat_attrs,
पूर्ण;

काष्ठा i915_ext_attribute अणु
	काष्ठा device_attribute attr;
	अचिन्हित दीर्घ val;
पूर्ण;

अटल sमाप_प्रकार i915_pmu_event_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i915_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा i915_ext_attribute, attr);
	वापस प्र_लिखो(buf, "config=0x%lx\n", eattr->val);
पूर्ण

अटल sमाप_प्रकार
i915_pmu_get_attr_cpumask(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &i915_pmu_cpumask);
पूर्ण

अटल DEVICE_ATTR(cpumask, 0444, i915_pmu_get_attr_cpumask, शून्य);

अटल काष्ठा attribute *i915_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group i915_pmu_cpumask_attr_group = अणु
	.attrs = i915_cpumask_attrs,
पूर्ण;

#घोषणा __event(__config, __name, __unit) \
अणु \
	.config = (__config), \
	.name = (__name), \
	.unit = (__unit), \
पूर्ण

#घोषणा __engine_event(__sample, __name) \
अणु \
	.sample = (__sample), \
	.name = (__name), \
पूर्ण

अटल काष्ठा i915_ext_attribute *
add_i915_attr(काष्ठा i915_ext_attribute *attr, स्थिर अक्षर *name, u64 config)
अणु
	sysfs_attr_init(&attr->attr.attr);
	attr->attr.attr.name = name;
	attr->attr.attr.mode = 0444;
	attr->attr.show = i915_pmu_event_show;
	attr->val = config;

	वापस ++attr;
पूर्ण

अटल काष्ठा perf_pmu_events_attr *
add_pmu_attr(काष्ठा perf_pmu_events_attr *attr, स्थिर अक्षर *name,
	     स्थिर अक्षर *str)
अणु
	sysfs_attr_init(&attr->attr.attr);
	attr->attr.attr.name = name;
	attr->attr.attr.mode = 0444;
	attr->attr.show = perf_event_sysfs_show;
	attr->event_str = str;

	वापस ++attr;
पूर्ण

अटल काष्ठा attribute **
create_event_attributes(काष्ठा i915_pmu *pmu)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(pmu, typeof(*i915), pmu);
	अटल स्थिर काष्ठा अणु
		u64 config;
		स्थिर अक्षर *name;
		स्थिर अक्षर *unit;
	पूर्ण events[] = अणु
		__event(I915_PMU_ACTUAL_FREQUENCY, "actual-frequency", "M"),
		__event(I915_PMU_REQUESTED_FREQUENCY, "requested-frequency", "M"),
		__event(I915_PMU_INTERRUPTS, "interrupts", शून्य),
		__event(I915_PMU_RC6_RESIDENCY, "rc6-residency", "ns"),
		__event(I915_PMU_SOFTWARE_GT_AWAKE_TIME, "software-gt-awake-time", "ns"),
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		क्रमागत drm_i915_pmu_engine_sample sample;
		अक्षर *name;
	पूर्ण engine_events[] = अणु
		__engine_event(I915_SAMPLE_BUSY, "busy"),
		__engine_event(I915_SAMPLE_SEMA, "sema"),
		__engine_event(I915_SAMPLE_WAIT, "wait"),
	पूर्ण;
	अचिन्हित पूर्णांक count = 0;
	काष्ठा perf_pmu_events_attr *pmu_attr = शून्य, *pmu_iter;
	काष्ठा i915_ext_attribute *i915_attr = शून्य, *i915_iter;
	काष्ठा attribute **attr = शून्य, **attr_iter;
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित पूर्णांक i;

	/* Count how many counters we will be exposing. */
	क्रम (i = 0; i < ARRAY_SIZE(events); i++) अणु
		अगर (!config_status(i915, events[i].config))
			count++;
	पूर्ण

	क्रम_each_uabi_engine(engine, i915) अणु
		क्रम (i = 0; i < ARRAY_SIZE(engine_events); i++) अणु
			अगर (!engine_event_status(engine,
						 engine_events[i].sample))
				count++;
		पूर्ण
	पूर्ण

	/* Allocate attribute objects and table. */
	i915_attr = kसुस्मृति(count, माप(*i915_attr), GFP_KERNEL);
	अगर (!i915_attr)
		जाओ err_alloc;

	pmu_attr = kसुस्मृति(count, माप(*pmu_attr), GFP_KERNEL);
	अगर (!pmu_attr)
		जाओ err_alloc;

	/* Max one poपूर्णांकer of each attribute type plus a termination entry. */
	attr = kसुस्मृति(count * 2 + 1, माप(*attr), GFP_KERNEL);
	अगर (!attr)
		जाओ err_alloc;

	i915_iter = i915_attr;
	pmu_iter = pmu_attr;
	attr_iter = attr;

	/* Initialize supported non-engine counters. */
	क्रम (i = 0; i < ARRAY_SIZE(events); i++) अणु
		अक्षर *str;

		अगर (config_status(i915, events[i].config))
			जारी;

		str = kstrdup(events[i].name, GFP_KERNEL);
		अगर (!str)
			जाओ err;

		*attr_iter++ = &i915_iter->attr.attr;
		i915_iter = add_i915_attr(i915_iter, str, events[i].config);

		अगर (events[i].unit) अणु
			str = kaप्र_लिखो(GFP_KERNEL, "%s.unit", events[i].name);
			अगर (!str)
				जाओ err;

			*attr_iter++ = &pmu_iter->attr.attr;
			pmu_iter = add_pmu_attr(pmu_iter, str, events[i].unit);
		पूर्ण
	पूर्ण

	/* Initialize supported engine counters. */
	क्रम_each_uabi_engine(engine, i915) अणु
		क्रम (i = 0; i < ARRAY_SIZE(engine_events); i++) अणु
			अक्षर *str;

			अगर (engine_event_status(engine,
						engine_events[i].sample))
				जारी;

			str = kaप्र_लिखो(GFP_KERNEL, "%s-%s",
					engine->name, engine_events[i].name);
			अगर (!str)
				जाओ err;

			*attr_iter++ = &i915_iter->attr.attr;
			i915_iter =
				add_i915_attr(i915_iter, str,
					      __I915_PMU_ENGINE(engine->uabi_class,
								engine->uabi_instance,
								engine_events[i].sample));

			str = kaप्र_लिखो(GFP_KERNEL, "%s-%s.unit",
					engine->name, engine_events[i].name);
			अगर (!str)
				जाओ err;

			*attr_iter++ = &pmu_iter->attr.attr;
			pmu_iter = add_pmu_attr(pmu_iter, str, "ns");
		पूर्ण
	पूर्ण

	pmu->i915_attr = i915_attr;
	pmu->pmu_attr = pmu_attr;

	वापस attr;

err:;
	क्रम (attr_iter = attr; *attr_iter; attr_iter++)
		kमुक्त((*attr_iter)->name);

err_alloc:
	kमुक्त(attr);
	kमुक्त(i915_attr);
	kमुक्त(pmu_attr);

	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_event_attributes(काष्ठा i915_pmu *pmu)
अणु
	काष्ठा attribute **attr_iter = pmu->events_attr_group.attrs;

	क्रम (; *attr_iter; attr_iter++)
		kमुक्त((*attr_iter)->name);

	kमुक्त(pmu->events_attr_group.attrs);
	kमुक्त(pmu->i915_attr);
	kमुक्त(pmu->pmu_attr);

	pmu->events_attr_group.attrs = शून्य;
	pmu->i915_attr = शून्य;
	pmu->pmu_attr = शून्य;
पूर्ण

अटल पूर्णांक i915_pmu_cpu_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा i915_pmu *pmu = hlist_entry_safe(node, typeof(*pmu), cpuhp.node);

	GEM_BUG_ON(!pmu->base.event_init);

	/* Select the first online CPU as a designated पढ़ोer. */
	अगर (!cpumask_weight(&i915_pmu_cpumask))
		cpumask_set_cpu(cpu, &i915_pmu_cpumask);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_pmu_cpu_offline(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा i915_pmu *pmu = hlist_entry_safe(node, typeof(*pmu), cpuhp.node);
	अचिन्हित पूर्णांक target = i915_pmu_target_cpu;

	GEM_BUG_ON(!pmu->base.event_init);

	/*
	 * Unरेजिस्टरing an instance generates a CPU offline event which we must
	 * ignore to aव्योम incorrectly modअगरying the shared i915_pmu_cpumask.
	 */
	अगर (pmu->बंदd)
		वापस 0;

	अगर (cpumask_test_and_clear_cpu(cpu, &i915_pmu_cpumask)) अणु
		target = cpumask_any_but(topology_sibling_cpumask(cpu), cpu);

		/* Migrate events अगर there is a valid target */
		अगर (target < nr_cpu_ids) अणु
			cpumask_set_cpu(target, &i915_pmu_cpumask);
			i915_pmu_target_cpu = target;
		पूर्ण
	पूर्ण

	अगर (target < nr_cpu_ids && target != pmu->cpuhp.cpu) अणु
		perf_pmu_migrate_context(&pmu->base, cpu, target);
		pmu->cpuhp.cpu = target;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत cpuhp_state cpuhp_slot = CPUHP_INVALID;

व्योम i915_pmu_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
				      "perf/x86/intel/i915:online",
				      i915_pmu_cpu_online,
				      i915_pmu_cpu_offline);
	अगर (ret < 0)
		pr_notice("Failed to setup cpuhp state for i915 PMU! (%d)\n",
			  ret);
	अन्यथा
		cpuhp_slot = ret;
पूर्ण

व्योम i915_pmu_निकास(व्योम)
अणु
	अगर (cpuhp_slot != CPUHP_INVALID)
		cpuhp_हटाओ_multi_state(cpuhp_slot);
पूर्ण

अटल पूर्णांक i915_pmu_रेजिस्टर_cpuhp_state(काष्ठा i915_pmu *pmu)
अणु
	अगर (cpuhp_slot == CPUHP_INVALID)
		वापस -EINVAL;

	वापस cpuhp_state_add_instance(cpuhp_slot, &pmu->cpuhp.node);
पूर्ण

अटल व्योम i915_pmu_unरेजिस्टर_cpuhp_state(काष्ठा i915_pmu *pmu)
अणु
	cpuhp_state_हटाओ_instance(cpuhp_slot, &pmu->cpuhp.node);
पूर्ण

अटल bool is_igp(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);

	/* IGP is 0000:00:02.0 */
	वापस pci_करोमुख्य_nr(pdev->bus) == 0 &&
	       pdev->bus->number == 0 &&
	       PCI_SLOT(pdev->devfn) == 2 &&
	       PCI_FUNC(pdev->devfn) == 0;
पूर्ण

व्योम i915_pmu_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_pmu *pmu = &i915->pmu;
	स्थिर काष्ठा attribute_group *attr_groups[] = अणु
		&i915_pmu_क्रमmat_attr_group,
		&pmu->events_attr_group,
		&i915_pmu_cpumask_attr_group,
		शून्य
	पूर्ण;

	पूर्णांक ret = -ENOMEM;

	अगर (INTEL_GEN(i915) <= 2) अणु
		drm_info(&i915->drm, "PMU not supported for this GPU.");
		वापस;
	पूर्ण

	spin_lock_init(&pmu->lock);
	hrसमयr_init(&pmu->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	pmu->समयr.function = i915_sample;
	pmu->cpuhp.cpu = -1;
	init_rc6(pmu);

	अगर (!is_igp(i915)) अणु
		pmu->name = kaप्र_लिखो(GFP_KERNEL,
				      "i915_%s",
				      dev_name(i915->drm.dev));
		अगर (pmu->name) अणु
			/* tools/perf reserves colons as special. */
			strreplace((अक्षर *)pmu->name, ':', '_');
		पूर्ण
	पूर्ण अन्यथा अणु
		pmu->name = "i915";
	पूर्ण
	अगर (!pmu->name)
		जाओ err;

	pmu->events_attr_group.name = "events";
	pmu->events_attr_group.attrs = create_event_attributes(pmu);
	अगर (!pmu->events_attr_group.attrs)
		जाओ err_name;

	pmu->base.attr_groups = kmemdup(attr_groups, माप(attr_groups),
					GFP_KERNEL);
	अगर (!pmu->base.attr_groups)
		जाओ err_attr;

	pmu->base.module	= THIS_MODULE;
	pmu->base.task_ctx_nr	= perf_invalid_context;
	pmu->base.event_init	= i915_pmu_event_init;
	pmu->base.add		= i915_pmu_event_add;
	pmu->base.del		= i915_pmu_event_del;
	pmu->base.start		= i915_pmu_event_start;
	pmu->base.stop		= i915_pmu_event_stop;
	pmu->base.पढ़ो		= i915_pmu_event_पढ़ो;
	pmu->base.event_idx	= i915_pmu_event_event_idx;

	ret = perf_pmu_रेजिस्टर(&pmu->base, pmu->name, -1);
	अगर (ret)
		जाओ err_groups;

	ret = i915_pmu_रेजिस्टर_cpuhp_state(pmu);
	अगर (ret)
		जाओ err_unreg;

	वापस;

err_unreg:
	perf_pmu_unरेजिस्टर(&pmu->base);
err_groups:
	kमुक्त(pmu->base.attr_groups);
err_attr:
	pmu->base.event_init = शून्य;
	मुक्त_event_attributes(pmu);
err_name:
	अगर (!is_igp(i915))
		kमुक्त(pmu->name);
err:
	drm_notice(&i915->drm, "Failed to register PMU!\n");
पूर्ण

व्योम i915_pmu_unरेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_pmu *pmu = &i915->pmu;

	अगर (!pmu->base.event_init)
		वापस;

	/*
	 * "Disconnect" the PMU callbacks - since all are atomic synchronize_rcu
	 * ensures all currently executing ones will have निकासed beक्रमe we
	 * proceed with unregistration.
	 */
	pmu->बंदd = true;
	synchronize_rcu();

	hrसमयr_cancel(&pmu->समयr);

	i915_pmu_unरेजिस्टर_cpuhp_state(pmu);

	perf_pmu_unरेजिस्टर(&pmu->base);
	pmu->base.event_init = शून्य;
	kमुक्त(pmu->base.attr_groups);
	अगर (!is_igp(i915))
		kमुक्त(pmu->name);
	मुक्त_event_attributes(pmu);
पूर्ण
