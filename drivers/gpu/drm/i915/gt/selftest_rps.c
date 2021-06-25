<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/pm_qos.h>
#समावेश <linux/sort.h>

#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt_clock_utils.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_rc6.h"
#समावेश "selftest_engine_heartbeat.h"
#समावेश "selftest_rps.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_spinner.h"
#समावेश "selftests/librapl.h"

/* Try to isolate the impact of cstates from determing frequency response */
#घोषणा CPU_LATENCY 0 /* -1 to disable pm_qos, 0 to disable cstates */

अटल व्योम dummy_rps_work(काष्ठा work_काष्ठा *wrk)
अणु
पूर्ण

अटल पूर्णांक cmp_u64(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर u64 *a = A, *b = B;

	अगर (*a < *b)
		वापस -1;
	अन्यथा अगर (*a > *b)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक cmp_u32(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर u32 *a = A, *b = B;

	अगर (*a < *b)
		वापस -1;
	अन्यथा अगर (*a > *b)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल काष्ठा i915_vma *
create_spin_counter(काष्ठा पूर्णांकel_engine_cs *engine,
		    काष्ठा i915_address_space *vm,
		    bool srm,
		    u32 **cancel,
		    u32 **counter)
अणु
	क्रमागत अणु
		COUNT,
		INC,
		__NGPR__,
	पूर्ण;
#घोषणा CS_GPR(x) GEN8_RING_CS_GPR(engine->mmio_base, x)
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	अचिन्हित दीर्घ end;
	u32 *base, *cs;
	पूर्णांक loop, i;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, 64 << 10);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	end = obj->base.size / माप(u32) - 1;

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_put;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ err_unlock;

	i915_vma_lock(vma);

	base = i915_gem_object_pin_map(obj, I915_MAP_WC);
	अगर (IS_ERR(base)) अणु
		err = PTR_ERR(base);
		जाओ err_unpin;
	पूर्ण
	cs = base;

	*cs++ = MI_LOAD_REGISTER_IMM(__NGPR__ * 2);
	क्रम (i = 0; i < __NGPR__; i++) अणु
		*cs++ = i915_mmio_reg_offset(CS_GPR(i));
		*cs++ = 0;
		*cs++ = i915_mmio_reg_offset(CS_GPR(i)) + 4;
		*cs++ = 0;
	पूर्ण

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(CS_GPR(INC));
	*cs++ = 1;

	loop = cs - base;

	/* Unroll the loop to aव्योम MI_BB_START stalls impacting measurements */
	क्रम (i = 0; i < 1024; i++) अणु
		*cs++ = MI_MATH(4);
		*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCA, MI_MATH_REG(COUNT));
		*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCB, MI_MATH_REG(INC));
		*cs++ = MI_MATH_ADD;
		*cs++ = MI_MATH_STORE(MI_MATH_REG(COUNT), MI_MATH_REG_ACCU);

		अगर (srm) अणु
			*cs++ = MI_STORE_REGISTER_MEM_GEN8;
			*cs++ = i915_mmio_reg_offset(CS_GPR(COUNT));
			*cs++ = lower_32_bits(vma->node.start + end * माप(*cs));
			*cs++ = upper_32_bits(vma->node.start + end * माप(*cs));
		पूर्ण
	पूर्ण

	*cs++ = MI_BATCH_BUFFER_START_GEN8;
	*cs++ = lower_32_bits(vma->node.start + loop * माप(*cs));
	*cs++ = upper_32_bits(vma->node.start + loop * माप(*cs));
	GEM_BUG_ON(cs - base > end);

	i915_gem_object_flush_map(obj);

	*cancel = base + loop;
	*counter = srm ? स_रखो32(base + end, 0, 1) : शून्य;
	वापस vma;

err_unpin:
	i915_vma_unpin(vma);
err_unlock:
	i915_vma_unlock(vma);
err_put:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल u8 रुको_क्रम_freq(काष्ठा पूर्णांकel_rps *rps, u8 freq, पूर्णांक समयout_ms)
अणु
	u8 history[64], i;
	अचिन्हित दीर्घ end;
	पूर्णांक sleep;

	i = 0;
	स_रखो(history, freq, माप(history));
	sleep = 20;

	/* The PCU करोes not change instantly, but drअगरts towards the goal? */
	end = jअगरfies + msecs_to_jअगरfies(समयout_ms);
	करो अणु
		u8 act;

		act = पढ़ो_cagf(rps);
		अगर (समय_after(jअगरfies, end))
			वापस act;

		/* Target acquired */
		अगर (act == freq)
			वापस act;

		/* Any change within the last N samples? */
		अगर (!स_प्रथम_inv(history, act, माप(history)))
			वापस act;

		history[i] = act;
		i = (i + 1) % ARRAY_SIZE(history);

		usleep_range(sleep, 2 * sleep);
		sleep *= 2;
		अगर (sleep > समयout_ms * 20)
			sleep = समयout_ms * 20;
	पूर्ण जबतक (1);
पूर्ण

अटल u8 rps_set_check(काष्ठा पूर्णांकel_rps *rps, u8 freq)
अणु
	mutex_lock(&rps->lock);
	GEM_BUG_ON(!पूर्णांकel_rps_is_active(rps));
	अगर (रुको_क्रम(!पूर्णांकel_rps_set(rps, freq), 50)) अणु
		mutex_unlock(&rps->lock);
		वापस 0;
	पूर्ण
	GEM_BUG_ON(rps->last_freq != freq);
	mutex_unlock(&rps->lock);

	वापस रुको_क्रम_freq(rps, freq, 50);
पूर्ण

अटल व्योम show_pstate_limits(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);

	अगर (IS_BROXTON(i915)) अणु
		pr_info("P_STATE_CAP[%x]: 0x%08x\n",
			i915_mmio_reg_offset(BXT_RP_STATE_CAP),
			पूर्णांकel_uncore_पढ़ो(rps_to_uncore(rps),
					  BXT_RP_STATE_CAP));
	पूर्ण अन्यथा अगर (IS_GEN(i915, 9)) अणु
		pr_info("P_STATE_LIMITS[%x]: 0x%08x\n",
			i915_mmio_reg_offset(GEN9_RP_STATE_LIMITS),
			पूर्णांकel_uncore_पढ़ो(rps_to_uncore(rps),
					  GEN9_RP_STATE_LIMITS));
	पूर्ण
पूर्ण

पूर्णांक live_rps_घड़ी_पूर्णांकerval(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	व्योम (*saved_work)(काष्ठा work_काष्ठा *wrk);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	अगर (!पूर्णांकel_rps_is_enabled(rps) || INTEL_GEN(gt->i915) < 6)
		वापस 0;

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	saved_work = rps->work.func;
	rps->work.func = dummy_rps_work;

	पूर्णांकel_gt_pm_get(gt);
	पूर्णांकel_rps_disable(&gt->rps);

	पूर्णांकel_gt_check_घड़ी_frequency(gt);

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq;
		u32 cycles;
		u64 dt;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		st_engine_heartbeat_disable(engine);

		rq = igt_spinner_create_request(&spin,
						engine->kernel_context,
						MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			st_engine_heartbeat_enable(engine);
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_add(rq);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			pr_err("%s: RPS spinner did not start\n",
			       engine->name);
			igt_spinner_end(&spin);
			st_engine_heartbeat_enable(engine);
			पूर्णांकel_gt_set_wedged(engine->gt);
			err = -EIO;
			अवरोध;
		पूर्ण

		पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);

		पूर्णांकel_uncore_ग_लिखो_fw(gt->uncore, GEN6_RP_CUR_UP_EI, 0);

		/* Set the evaluation पूर्णांकerval to infinity! */
		पूर्णांकel_uncore_ग_लिखो_fw(gt->uncore,
				      GEN6_RP_UP_EI, 0xffffffff);
		पूर्णांकel_uncore_ग_लिखो_fw(gt->uncore,
				      GEN6_RP_UP_THRESHOLD, 0xffffffff);

		पूर्णांकel_uncore_ग_लिखो_fw(gt->uncore, GEN6_RP_CONTROL,
				      GEN6_RP_ENABLE | GEN6_RP_UP_BUSY_AVG);

		अगर (रुको_क्रम(पूर्णांकel_uncore_पढ़ो_fw(gt->uncore,
						  GEN6_RP_CUR_UP_EI),
			     10)) अणु
			/* Just skip the test; assume lack of HW support */
			pr_notice("%s: rps evaluation interval not ticking\n",
				  engine->name);
			err = -ENODEV;
		पूर्ण अन्यथा अणु
			kसमय_प्रकार dt_[5];
			u32 cycles_[5];
			पूर्णांक i;

			क्रम (i = 0; i < 5; i++) अणु
				preempt_disable();

				dt_[i] = kसमय_get();
				cycles_[i] = -पूर्णांकel_uncore_पढ़ो_fw(gt->uncore, GEN6_RP_CUR_UP_EI);

				udelay(1000);

				dt_[i] = kसमय_sub(kसमय_get(), dt_[i]);
				cycles_[i] += पूर्णांकel_uncore_पढ़ो_fw(gt->uncore, GEN6_RP_CUR_UP_EI);

				preempt_enable();
			पूर्ण

			/* Use the median of both cycle/dt; बंद enough */
			sort(cycles_, 5, माप(*cycles_), cmp_u32, शून्य);
			cycles = (cycles_[1] + 2 * cycles_[2] + cycles_[3]) / 4;
			sort(dt_, 5, माप(*dt_), cmp_u64, शून्य);
			dt = भाग_u64(dt_[1] + 2 * dt_[2] + dt_[3], 4);
		पूर्ण

		पूर्णांकel_uncore_ग_लिखो_fw(gt->uncore, GEN6_RP_CONTROL, 0);
		पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);

		igt_spinner_end(&spin);
		st_engine_heartbeat_enable(engine);

		अगर (err == 0) अणु
			u64 समय = पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(gt, cycles);
			u32 expected =
				पूर्णांकel_gt_ns_to_pm_पूर्णांकerval(gt, dt);

			pr_info("%s: rps counted %d C0 cycles [%lldns] in %lldns [%d cycles], using GT clock frequency of %uKHz\n",
				engine->name, cycles, समय, dt, expected,
				gt->घड़ी_frequency / 1000);

			अगर (10 * समय < 8 * dt ||
			    8 * समय > 10 * dt) अणु
				pr_err("%s: rps clock time does not match walltime!\n",
				       engine->name);
				err = -EINVAL;
			पूर्ण

			अगर (10 * expected < 8 * cycles ||
			    8 * expected > 10 * cycles) अणु
				pr_err("%s: walltime does not match rps clock ticks!\n",
				       engine->name);
				err = -EINVAL;
			पूर्ण
		पूर्ण

		अगर (igt_flush_test(gt->i915))
			err = -EIO;

		अवरोध; /* once is enough */
	पूर्ण

	पूर्णांकel_rps_enable(&gt->rps);
	पूर्णांकel_gt_pm_put(gt);

	igt_spinner_fini(&spin);

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	rps->work.func = saved_work;

	अगर (err == -ENODEV) /* skipped, करोn't report a fail */
		err = 0;

	वापस err;
पूर्ण

पूर्णांक live_rps_control(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	व्योम (*saved_work)(काष्ठा work_काष्ठा *wrk);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	/*
	 * Check that the actual frequency matches our requested frequency,
	 * to verअगरy our control mechanism. We have to be careful that the
	 * PCU may throttle the GPU in which हाल the actual frequency used
	 * will be lowered than requested.
	 */

	अगर (!पूर्णांकel_rps_is_enabled(rps))
		वापस 0;

	अगर (IS_CHERRYVIEW(gt->i915)) /* XXX fragile PCU */
		वापस 0;

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	saved_work = rps->work.func;
	rps->work.func = dummy_rps_work;

	पूर्णांकel_gt_pm_get(gt);
	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq;
		kसमय_प्रकार min_dt, max_dt;
		पूर्णांक f, limit;
		पूर्णांक min, max;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		st_engine_heartbeat_disable(engine);

		rq = igt_spinner_create_request(&spin,
						engine->kernel_context,
						MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_add(rq);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			pr_err("%s: RPS spinner did not start\n",
			       engine->name);
			igt_spinner_end(&spin);
			st_engine_heartbeat_enable(engine);
			पूर्णांकel_gt_set_wedged(engine->gt);
			err = -EIO;
			अवरोध;
		पूर्ण

		अगर (rps_set_check(rps, rps->min_freq) != rps->min_freq) अणु
			pr_err("%s: could not set minimum frequency [%x], only %x!\n",
			       engine->name, rps->min_freq, पढ़ो_cagf(rps));
			igt_spinner_end(&spin);
			st_engine_heartbeat_enable(engine);
			show_pstate_limits(rps);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		क्रम (f = rps->min_freq + 1; f < rps->max_freq; f++) अणु
			अगर (rps_set_check(rps, f) < f)
				अवरोध;
		पूर्ण

		limit = rps_set_check(rps, f);

		अगर (rps_set_check(rps, rps->min_freq) != rps->min_freq) अणु
			pr_err("%s: could not restore minimum frequency [%x], only %x!\n",
			       engine->name, rps->min_freq, पढ़ो_cagf(rps));
			igt_spinner_end(&spin);
			st_engine_heartbeat_enable(engine);
			show_pstate_limits(rps);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		max_dt = kसमय_get();
		max = rps_set_check(rps, limit);
		max_dt = kसमय_sub(kसमय_get(), max_dt);

		min_dt = kसमय_get();
		min = rps_set_check(rps, rps->min_freq);
		min_dt = kसमय_sub(kसमय_get(), min_dt);

		igt_spinner_end(&spin);
		st_engine_heartbeat_enable(engine);

		pr_info("%s: range:[%x:%uMHz, %x:%uMHz] limit:[%x:%uMHz], %x:%x response %lluns:%lluns\n",
			engine->name,
			rps->min_freq, पूर्णांकel_gpu_freq(rps, rps->min_freq),
			rps->max_freq, पूर्णांकel_gpu_freq(rps, rps->max_freq),
			limit, पूर्णांकel_gpu_freq(rps, limit),
			min, max, kसमय_प्रकारo_ns(min_dt), kसमय_प्रकारo_ns(max_dt));

		अगर (limit == rps->min_freq) अणु
			pr_err("%s: GPU throttled to minimum!\n",
			       engine->name);
			show_pstate_limits(rps);
			err = -ENODEV;
			अवरोध;
		पूर्ण

		अगर (igt_flush_test(gt->i915)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण
	पूर्णांकel_gt_pm_put(gt);

	igt_spinner_fini(&spin);

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	rps->work.func = saved_work;

	वापस err;
पूर्ण

अटल व्योम show_pcu_config(काष्ठा पूर्णांकel_rps *rps)
अणु
	काष्ठा drm_i915_निजी *i915 = rps_to_i915(rps);
	अचिन्हित पूर्णांक max_gpu_freq, min_gpu_freq;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक gpu_freq;

	अगर (!HAS_LLC(i915))
		वापस;

	min_gpu_freq = rps->min_freq;
	max_gpu_freq = rps->max_freq;
	अगर (INTEL_GEN(i915) >= 9) अणु
		/* Convert GT frequency to 50 HZ units */
		min_gpu_freq /= GEN9_FREQ_SCALER;
		max_gpu_freq /= GEN9_FREQ_SCALER;
	पूर्ण

	wakeref = पूर्णांकel_runसमय_pm_get(rps_to_uncore(rps)->rpm);

	pr_info("%5s  %5s  %5s\n", "GPU", "eCPU", "eRing");
	क्रम (gpu_freq = min_gpu_freq; gpu_freq <= max_gpu_freq; gpu_freq++) अणु
		पूर्णांक ia_freq = gpu_freq;

		sandybridge_pcode_पढ़ो(i915,
				       GEN6_PCODE_READ_MIN_FREQ_TABLE,
				       &ia_freq, शून्य);

		pr_info("%5d  %5d  %5d\n",
			gpu_freq * 50,
			((ia_freq >> 0) & 0xff) * 100,
			((ia_freq >> 8) & 0xff) * 100);
	पूर्ण

	पूर्णांकel_runसमय_pm_put(rps_to_uncore(rps)->rpm, wakeref);
पूर्ण

अटल u64 __measure_frequency(u32 *cntr, पूर्णांक duration_ms)
अणु
	u64 dc, dt;

	dt = kसमय_get();
	dc = READ_ONCE(*cntr);
	usleep_range(1000 * duration_ms, 2000 * duration_ms);
	dc = READ_ONCE(*cntr) - dc;
	dt = kसमय_get() - dt;

	वापस भाग64_u64(1000 * 1000 * dc, dt);
पूर्ण

अटल u64 measure_frequency_at(काष्ठा पूर्णांकel_rps *rps, u32 *cntr, पूर्णांक *freq)
अणु
	u64 x[5];
	पूर्णांक i;

	*freq = rps_set_check(rps, *freq);
	क्रम (i = 0; i < 5; i++)
		x[i] = __measure_frequency(cntr, 2);
	*freq = (*freq + पढ़ो_cagf(rps)) / 2;

	/* A simple triangle filter क्रम better result stability */
	sort(x, 5, माप(*x), cmp_u64, शून्य);
	वापस भाग_u64(x[1] + 2 * x[2] + x[3], 4);
पूर्ण

अटल u64 __measure_cs_frequency(काष्ठा पूर्णांकel_engine_cs *engine,
				  पूर्णांक duration_ms)
अणु
	u64 dc, dt;

	dt = kसमय_get();
	dc = पूर्णांकel_uncore_पढ़ो_fw(engine->uncore, CS_GPR(0));
	usleep_range(1000 * duration_ms, 2000 * duration_ms);
	dc = पूर्णांकel_uncore_पढ़ो_fw(engine->uncore, CS_GPR(0)) - dc;
	dt = kसमय_get() - dt;

	वापस भाग64_u64(1000 * 1000 * dc, dt);
पूर्ण

अटल u64 measure_cs_frequency_at(काष्ठा पूर्णांकel_rps *rps,
				   काष्ठा पूर्णांकel_engine_cs *engine,
				   पूर्णांक *freq)
अणु
	u64 x[5];
	पूर्णांक i;

	*freq = rps_set_check(rps, *freq);
	क्रम (i = 0; i < 5; i++)
		x[i] = __measure_cs_frequency(engine, 2);
	*freq = (*freq + पढ़ो_cagf(rps)) / 2;

	/* A simple triangle filter क्रम better result stability */
	sort(x, 5, माप(*x), cmp_u64, शून्य);
	वापस भाग_u64(x[1] + 2 * x[2] + x[3], 4);
पूर्ण

अटल bool scaled_within(u64 x, u64 y, u32 f_n, u32 f_d)
अणु
	वापस f_d * x > f_n * y && f_n * x < f_d * y;
पूर्ण

पूर्णांक live_rps_frequency_cs(व्योम *arg)
अणु
	व्योम (*saved_work)(काष्ठा work_काष्ठा *wrk);
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा pm_qos_request qos;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * The premise is that the GPU करोes change freqency at our behest.
	 * Let's check there is a correspondence between the requested
	 * frequency, the actual frequency, and the observed घड़ी rate.
	 */

	अगर (!पूर्णांकel_rps_is_enabled(rps))
		वापस 0;

	अगर (INTEL_GEN(gt->i915) < 8) /* क्रम CS simplicity */
		वापस 0;

	अगर (CPU_LATENCY >= 0)
		cpu_latency_qos_add_request(&qos, CPU_LATENCY);

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	saved_work = rps->work.func;
	rps->work.func = dummy_rps_work;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq;
		काष्ठा i915_vma *vma;
		u32 *cancel, *cntr;
		काष्ठा अणु
			u64 count;
			पूर्णांक freq;
		पूर्ण min, max;

		st_engine_heartbeat_disable(engine);

		vma = create_spin_counter(engine,
					  engine->kernel_context->vm, false,
					  &cancel, &cntr);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			st_engine_heartbeat_enable(engine);
			अवरोध;
		पूर्ण

		rq = पूर्णांकel_engine_create_kernel_request(engine);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_vma;
		पूर्ण

		err = i915_request_aरुको_object(rq, vma->obj, false);
		अगर (!err)
			err = i915_vma_move_to_active(vma, rq, 0);
		अगर (!err)
			err = rq->engine->emit_bb_start(rq,
							vma->node.start,
							PAGE_SIZE, 0);
		i915_request_add(rq);
		अगर (err)
			जाओ err_vma;

		अगर (रुको_क्रम(पूर्णांकel_uncore_पढ़ो(engine->uncore, CS_GPR(0)),
			     10)) अणु
			pr_err("%s: timed loop did not start\n",
			       engine->name);
			जाओ err_vma;
		पूर्ण

		min.freq = rps->min_freq;
		min.count = measure_cs_frequency_at(rps, engine, &min.freq);

		max.freq = rps->max_freq;
		max.count = measure_cs_frequency_at(rps, engine, &max.freq);

		pr_info("%s: min:%lluKHz @ %uMHz, max:%lluKHz @ %uMHz [%d%%]\n",
			engine->name,
			min.count, पूर्णांकel_gpu_freq(rps, min.freq),
			max.count, पूर्णांकel_gpu_freq(rps, max.freq),
			(पूर्णांक)DIV64_U64_ROUND_CLOSEST(100 * min.freq * max.count,
						     max.freq * min.count));

		अगर (!scaled_within(max.freq * min.count,
				   min.freq * max.count,
				   2, 3)) अणु
			पूर्णांक f;

			pr_err("%s: CS did not scale with frequency! scaled min:%llu, max:%llu\n",
			       engine->name,
			       max.freq * min.count,
			       min.freq * max.count);
			show_pcu_config(rps);

			क्रम (f = min.freq + 1; f <= rps->max_freq; f++) अणु
				पूर्णांक act = f;
				u64 count;

				count = measure_cs_frequency_at(rps, engine, &act);
				अगर (act < f)
					अवरोध;

				pr_info("%s: %x:%uMHz: %lluKHz [%d%%]\n",
					engine->name,
					act, पूर्णांकel_gpu_freq(rps, act), count,
					(पूर्णांक)DIV64_U64_ROUND_CLOSEST(100 * min.freq * count,
								     act * min.count));

				f = act; /* may skip ahead [pcu granularity] */
			पूर्ण

			err = -EINTR; /* ignore error, जारी on with test */
		पूर्ण

err_vma:
		*cancel = MI_BATCH_BUFFER_END;
		i915_gem_object_flush_map(vma->obj);
		i915_gem_object_unpin_map(vma->obj);
		i915_vma_unpin(vma);
		i915_vma_unlock(vma);
		i915_vma_put(vma);

		st_engine_heartbeat_enable(engine);
		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	rps->work.func = saved_work;

	अगर (CPU_LATENCY >= 0)
		cpu_latency_qos_हटाओ_request(&qos);

	वापस err;
पूर्ण

पूर्णांक live_rps_frequency_srm(व्योम *arg)
अणु
	व्योम (*saved_work)(काष्ठा work_काष्ठा *wrk);
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा pm_qos_request qos;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * The premise is that the GPU करोes change freqency at our behest.
	 * Let's check there is a correspondence between the requested
	 * frequency, the actual frequency, and the observed घड़ी rate.
	 */

	अगर (!पूर्णांकel_rps_is_enabled(rps))
		वापस 0;

	अगर (INTEL_GEN(gt->i915) < 8) /* क्रम CS simplicity */
		वापस 0;

	अगर (CPU_LATENCY >= 0)
		cpu_latency_qos_add_request(&qos, CPU_LATENCY);

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	saved_work = rps->work.func;
	rps->work.func = dummy_rps_work;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq;
		काष्ठा i915_vma *vma;
		u32 *cancel, *cntr;
		काष्ठा अणु
			u64 count;
			पूर्णांक freq;
		पूर्ण min, max;

		st_engine_heartbeat_disable(engine);

		vma = create_spin_counter(engine,
					  engine->kernel_context->vm, true,
					  &cancel, &cntr);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			st_engine_heartbeat_enable(engine);
			अवरोध;
		पूर्ण

		rq = पूर्णांकel_engine_create_kernel_request(engine);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_vma;
		पूर्ण

		err = i915_request_aरुको_object(rq, vma->obj, false);
		अगर (!err)
			err = i915_vma_move_to_active(vma, rq, 0);
		अगर (!err)
			err = rq->engine->emit_bb_start(rq,
							vma->node.start,
							PAGE_SIZE, 0);
		i915_request_add(rq);
		अगर (err)
			जाओ err_vma;

		अगर (रुको_क्रम(READ_ONCE(*cntr), 10)) अणु
			pr_err("%s: timed loop did not start\n",
			       engine->name);
			जाओ err_vma;
		पूर्ण

		min.freq = rps->min_freq;
		min.count = measure_frequency_at(rps, cntr, &min.freq);

		max.freq = rps->max_freq;
		max.count = measure_frequency_at(rps, cntr, &max.freq);

		pr_info("%s: min:%lluKHz @ %uMHz, max:%lluKHz @ %uMHz [%d%%]\n",
			engine->name,
			min.count, पूर्णांकel_gpu_freq(rps, min.freq),
			max.count, पूर्णांकel_gpu_freq(rps, max.freq),
			(पूर्णांक)DIV64_U64_ROUND_CLOSEST(100 * min.freq * max.count,
						     max.freq * min.count));

		अगर (!scaled_within(max.freq * min.count,
				   min.freq * max.count,
				   1, 2)) अणु
			पूर्णांक f;

			pr_err("%s: CS did not scale with frequency! scaled min:%llu, max:%llu\n",
			       engine->name,
			       max.freq * min.count,
			       min.freq * max.count);
			show_pcu_config(rps);

			क्रम (f = min.freq + 1; f <= rps->max_freq; f++) अणु
				पूर्णांक act = f;
				u64 count;

				count = measure_frequency_at(rps, cntr, &act);
				अगर (act < f)
					अवरोध;

				pr_info("%s: %x:%uMHz: %lluKHz [%d%%]\n",
					engine->name,
					act, पूर्णांकel_gpu_freq(rps, act), count,
					(पूर्णांक)DIV64_U64_ROUND_CLOSEST(100 * min.freq * count,
								     act * min.count));

				f = act; /* may skip ahead [pcu granularity] */
			पूर्ण

			err = -EINTR; /* ignore error, जारी on with test */
		पूर्ण

err_vma:
		*cancel = MI_BATCH_BUFFER_END;
		i915_gem_object_flush_map(vma->obj);
		i915_gem_object_unpin_map(vma->obj);
		i915_vma_unpin(vma);
		i915_vma_unlock(vma);
		i915_vma_put(vma);

		st_engine_heartbeat_enable(engine);
		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	rps->work.func = saved_work;

	अगर (CPU_LATENCY >= 0)
		cpu_latency_qos_हटाओ_request(&qos);

	वापस err;
पूर्ण

अटल व्योम sleep_क्रम_ei(काष्ठा पूर्णांकel_rps *rps, पूर्णांक समयout_us)
अणु
	/* Flush any previous EI */
	usleep_range(समयout_us, 2 * समयout_us);

	/* Reset the पूर्णांकerrupt status */
	rps_disable_पूर्णांकerrupts(rps);
	GEM_BUG_ON(rps->pm_iir);
	rps_enable_पूर्णांकerrupts(rps);

	/* And then रुको क्रम the समयout, क्रम real this समय */
	usleep_range(2 * समयout_us, 3 * समयout_us);
पूर्ण

अटल पूर्णांक __rps_up_पूर्णांकerrupt(काष्ठा पूर्णांकel_rps *rps,
			      काष्ठा पूर्णांकel_engine_cs *engine,
			      काष्ठा igt_spinner *spin)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	काष्ठा i915_request *rq;
	u32 समयout;

	अगर (!पूर्णांकel_engine_can_store_dword(engine))
		वापस 0;

	rps_set_check(rps, rps->min_freq);

	rq = igt_spinner_create_request(spin, engine->kernel_context, MI_NOOP);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	i915_request_get(rq);
	i915_request_add(rq);

	अगर (!igt_रुको_क्रम_spinner(spin, rq)) अणु
		pr_err("%s: RPS spinner did not start\n",
		       engine->name);
		i915_request_put(rq);
		पूर्णांकel_gt_set_wedged(engine->gt);
		वापस -EIO;
	पूर्ण

	अगर (!पूर्णांकel_rps_is_active(rps)) अणु
		pr_err("%s: RPS not enabled on starting spinner\n",
		       engine->name);
		igt_spinner_end(spin);
		i915_request_put(rq);
		वापस -EINVAL;
	पूर्ण

	अगर (!(rps->pm_events & GEN6_PM_RP_UP_THRESHOLD)) अणु
		pr_err("%s: RPS did not register UP interrupt\n",
		       engine->name);
		i915_request_put(rq);
		वापस -EINVAL;
	पूर्ण

	अगर (rps->last_freq != rps->min_freq) अणु
		pr_err("%s: RPS did not program min frequency\n",
		       engine->name);
		i915_request_put(rq);
		वापस -EINVAL;
	पूर्ण

	समयout = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_EI);
	समयout = पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(engine->gt, समयout);
	समयout = DIV_ROUND_UP(समयout, 1000);

	sleep_क्रम_ei(rps, समयout);
	GEM_BUG_ON(i915_request_completed(rq));

	igt_spinner_end(spin);
	i915_request_put(rq);

	अगर (rps->cur_freq != rps->min_freq) अणु
		pr_err("%s: Frequency unexpectedly changed [up], now %d!\n",
		       engine->name, पूर्णांकel_rps_पढ़ो_actual_frequency(rps));
		वापस -EINVAL;
	पूर्ण

	अगर (!(rps->pm_iir & GEN6_PM_RP_UP_THRESHOLD)) अणु
		pr_err("%s: UP interrupt not recorded for spinner, pm_iir:%x, prev_up:%x, up_threshold:%x, up_ei:%x\n",
		       engine->name, rps->pm_iir,
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_PREV_UP),
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_THRESHOLD),
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_EI));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __rps_करोwn_पूर्णांकerrupt(काष्ठा पूर्णांकel_rps *rps,
				काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	u32 समयout;

	rps_set_check(rps, rps->max_freq);

	अगर (!(rps->pm_events & GEN6_PM_RP_DOWN_THRESHOLD)) अणु
		pr_err("%s: RPS did not register DOWN interrupt\n",
		       engine->name);
		वापस -EINVAL;
	पूर्ण

	अगर (rps->last_freq != rps->max_freq) अणु
		pr_err("%s: RPS did not program max frequency\n",
		       engine->name);
		वापस -EINVAL;
	पूर्ण

	समयout = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_DOWN_EI);
	समयout = पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(engine->gt, समयout);
	समयout = DIV_ROUND_UP(समयout, 1000);

	sleep_क्रम_ei(rps, समयout);

	अगर (rps->cur_freq != rps->max_freq) अणु
		pr_err("%s: Frequency unexpectedly changed [down], now %d!\n",
		       engine->name,
		       पूर्णांकel_rps_पढ़ो_actual_frequency(rps));
		वापस -EINVAL;
	पूर्ण

	अगर (!(rps->pm_iir & (GEN6_PM_RP_DOWN_THRESHOLD | GEN6_PM_RP_DOWN_TIMEOUT))) अणु
		pr_err("%s: DOWN interrupt not recorded for idle, pm_iir:%x, prev_down:%x, down_threshold:%x, down_ei:%x [prev_up:%x, up_threshold:%x, up_ei:%x]\n",
		       engine->name, rps->pm_iir,
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_PREV_DOWN),
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_DOWN_THRESHOLD),
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_DOWN_EI),
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_PREV_UP),
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_THRESHOLD),
		       पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RP_UP_EI));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक live_rps_पूर्णांकerrupt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	व्योम (*saved_work)(काष्ठा work_काष्ठा *wrk);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	u32 pm_events;
	पूर्णांक err = 0;

	/*
	 * First, let's check whether or not we are receiving पूर्णांकerrupts.
	 */

	अगर (!पूर्णांकel_rps_has_पूर्णांकerrupts(rps) || INTEL_GEN(gt->i915) < 6)
		वापस 0;

	पूर्णांकel_gt_pm_get(gt);
	pm_events = rps->pm_events;
	पूर्णांकel_gt_pm_put(gt);
	अगर (!pm_events) अणु
		pr_err("No RPS PM events registered, but RPS is enabled?\n");
		वापस -ENODEV;
	पूर्ण

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	saved_work = rps->work.func;
	rps->work.func = dummy_rps_work;

	क्रम_each_engine(engine, gt, id) अणु
		/* Keep the engine busy with a spinner; expect an UP! */
		अगर (pm_events & GEN6_PM_RP_UP_THRESHOLD) अणु
			पूर्णांकel_gt_pm_रुको_क्रम_idle(engine->gt);
			GEM_BUG_ON(पूर्णांकel_rps_is_active(rps));

			st_engine_heartbeat_disable(engine);

			err = __rps_up_पूर्णांकerrupt(rps, engine, &spin);

			st_engine_heartbeat_enable(engine);
			अगर (err)
				जाओ out;

			पूर्णांकel_gt_pm_रुको_क्रम_idle(engine->gt);
		पूर्ण

		/* Keep the engine awake but idle and check क्रम DOWN */
		अगर (pm_events & GEN6_PM_RP_DOWN_THRESHOLD) अणु
			st_engine_heartbeat_disable(engine);
			पूर्णांकel_rc6_disable(&gt->rc6);

			err = __rps_करोwn_पूर्णांकerrupt(rps, engine);

			पूर्णांकel_rc6_enable(&gt->rc6);
			st_engine_heartbeat_enable(engine);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	igt_spinner_fini(&spin);

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	rps->work.func = saved_work;

	वापस err;
पूर्ण

अटल u64 __measure_घातer(पूर्णांक duration_ms)
अणु
	u64 dE, dt;

	dt = kसमय_get();
	dE = librapl_energy_uJ();
	usleep_range(1000 * duration_ms, 2000 * duration_ms);
	dE = librapl_energy_uJ() - dE;
	dt = kसमय_get() - dt;

	वापस भाग64_u64(1000 * 1000 * dE, dt);
पूर्ण

अटल u64 measure_घातer_at(काष्ठा पूर्णांकel_rps *rps, पूर्णांक *freq)
अणु
	u64 x[5];
	पूर्णांक i;

	*freq = rps_set_check(rps, *freq);
	क्रम (i = 0; i < 5; i++)
		x[i] = __measure_घातer(5);
	*freq = (*freq + पढ़ो_cagf(rps)) / 2;

	/* A simple triangle filter क्रम better result stability */
	sort(x, 5, माप(*x), cmp_u64, शून्य);
	वापस भाग_u64(x[1] + 2 * x[2] + x[3], 4);
पूर्ण

पूर्णांक live_rps_घातer(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	व्योम (*saved_work)(काष्ठा work_काष्ठा *wrk);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	/*
	 * Our fundamental assumption is that running at lower frequency
	 * actually saves घातer. Let's see अगर our RAPL measurement support
	 * that theory.
	 */

	अगर (!पूर्णांकel_rps_is_enabled(rps) || INTEL_GEN(gt->i915) < 6)
		वापस 0;

	अगर (!librapl_energy_uJ())
		वापस 0;

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	saved_work = rps->work.func;
	rps->work.func = dummy_rps_work;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq;
		काष्ठा अणु
			u64 घातer;
			पूर्णांक freq;
		पूर्ण min, max;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		st_engine_heartbeat_disable(engine);

		rq = igt_spinner_create_request(&spin,
						engine->kernel_context,
						MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			st_engine_heartbeat_enable(engine);
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_add(rq);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			pr_err("%s: RPS spinner did not start\n",
			       engine->name);
			igt_spinner_end(&spin);
			st_engine_heartbeat_enable(engine);
			पूर्णांकel_gt_set_wedged(engine->gt);
			err = -EIO;
			अवरोध;
		पूर्ण

		max.freq = rps->max_freq;
		max.घातer = measure_घातer_at(rps, &max.freq);

		min.freq = rps->min_freq;
		min.घातer = measure_घातer_at(rps, &min.freq);

		igt_spinner_end(&spin);
		st_engine_heartbeat_enable(engine);

		pr_info("%s: min:%llumW @ %uMHz, max:%llumW @ %uMHz\n",
			engine->name,
			min.घातer, पूर्णांकel_gpu_freq(rps, min.freq),
			max.घातer, पूर्णांकel_gpu_freq(rps, max.freq));

		अगर (10 * min.freq >= 9 * max.freq) अणु
			pr_notice("Could not control frequency, ran at [%d:%uMHz, %d:%uMhz]\n",
				  min.freq, पूर्णांकel_gpu_freq(rps, min.freq),
				  max.freq, पूर्णांकel_gpu_freq(rps, max.freq));
			जारी;
		पूर्ण

		अगर (11 * min.घातer > 10 * max.घातer) अणु
			pr_err("%s: did not conserve power when setting lower frequency!\n",
			       engine->name);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (igt_flush_test(gt->i915)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	igt_spinner_fini(&spin);

	पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
	rps->work.func = saved_work;

	वापस err;
पूर्ण

पूर्णांक live_rps_dynamic(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rps *rps = &gt->rps;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	/*
	 * We've looked at the bascs, and have established that we
	 * can change the घड़ी frequency and that the HW will generate
	 * पूर्णांकerrupts based on load. Now we check how we पूर्णांकegrate those
	 * moving parts पूर्णांकo dynamic reघड़ीing based on load.
	 */

	अगर (!पूर्णांकel_rps_is_enabled(rps) || INTEL_GEN(gt->i915) < 6)
		वापस 0;

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	अगर (पूर्णांकel_rps_has_पूर्णांकerrupts(rps))
		pr_info("RPS has interrupt support\n");
	अगर (पूर्णांकel_rps_uses_समयr(rps))
		pr_info("RPS has timer support\n");

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq;
		काष्ठा अणु
			kसमय_प्रकार dt;
			u8 freq;
		पूर्ण min, max;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
		GEM_BUG_ON(पूर्णांकel_rps_is_active(rps));
		rps->cur_freq = rps->min_freq;

		पूर्णांकel_engine_pm_get(engine);
		पूर्णांकel_rc6_disable(&gt->rc6);
		GEM_BUG_ON(rps->last_freq != rps->min_freq);

		rq = igt_spinner_create_request(&spin,
						engine->kernel_context,
						MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err;
		पूर्ण

		i915_request_add(rq);

		max.dt = kसमय_get();
		max.freq = रुको_क्रम_freq(rps, rps->max_freq, 500);
		max.dt = kसमय_sub(kसमय_get(), max.dt);

		igt_spinner_end(&spin);

		min.dt = kसमय_get();
		min.freq = रुको_क्रम_freq(rps, rps->min_freq, 2000);
		min.dt = kसमय_sub(kसमय_get(), min.dt);

		pr_info("%s: dynamically reclocked to %u:%uMHz while busy in %lluns, and %u:%uMHz while idle in %lluns\n",
			engine->name,
			max.freq, पूर्णांकel_gpu_freq(rps, max.freq),
			kसमय_प्रकारo_ns(max.dt),
			min.freq, पूर्णांकel_gpu_freq(rps, min.freq),
			kसमय_प्रकारo_ns(min.dt));
		अगर (min.freq >= max.freq) अणु
			pr_err("%s: dynamic reclocking of spinner failed\n!",
			       engine->name);
			err = -EINVAL;
		पूर्ण

err:
		पूर्णांकel_rc6_enable(&gt->rc6);
		पूर्णांकel_engine_pm_put(engine);

		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	igt_spinner_fini(&spin);

	वापस err;
पूर्ण
