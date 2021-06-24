<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/sort.h>

#समावेश "i915_selftest.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt_clock_utils.h"
#समावेश "selftest_engine.h"
#समावेश "selftest_engine_heartbeat.h"
#समावेश "selftests/igt_atomic.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_spinner.h"

#घोषणा COUNT 5

अटल पूर्णांक cmp_u64(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर u64 *a = A, *b = B;

	वापस *a - *b;
पूर्ण

अटल u64 trअगरilter(u64 *a)
अणु
	sort(a, COUNT, माप(*a), cmp_u64, शून्य);
	वापस (a[1] + 2 * a[2] + a[3]) >> 2;
पूर्ण

अटल u32 *emit_रुको(u32 *cs, u32 offset, पूर्णांक op, u32 value)
अणु
	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		op;
	*cs++ = value;
	*cs++ = offset;
	*cs++ = 0;

	वापस cs;
पूर्ण

अटल u32 *emit_store(u32 *cs, u32 offset, u32 value)
अणु
	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = value;

	वापस cs;
पूर्ण

अटल u32 *emit_srm(u32 *cs, i915_reg_t reg, u32 offset)
अणु
	*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_reg_offset(reg);
	*cs++ = offset;
	*cs++ = 0;

	वापस cs;
पूर्ण

अटल व्योम ग_लिखो_semaphore(u32 *x, u32 value)
अणु
	WRITE_ONCE(*x, value);
	wmb();
पूर्ण

अटल पूर्णांक __measure_बारtamps(काष्ठा पूर्णांकel_context *ce,
				u64 *dt, u64 *d_ring, u64 *d_ctx)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	u32 *sema = स_रखो32(engine->status_page.addr + 1000, 0, 5);
	u32 offset = i915_ggtt_offset(engine->status_page.vma);
	काष्ठा i915_request *rq;
	u32 *cs;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 28);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	/* Signal & रुको क्रम start */
	cs = emit_store(cs, offset + 4008, 1);
	cs = emit_रुको(cs, offset + 4008, MI_SEMAPHORE_SAD_NEQ_SDD, 1);

	cs = emit_srm(cs, RING_TIMESTAMP(engine->mmio_base), offset + 4000);
	cs = emit_srm(cs, RING_CTX_TIMESTAMP(engine->mmio_base), offset + 4004);

	/* Busy रुको */
	cs = emit_रुको(cs, offset + 4008, MI_SEMAPHORE_SAD_EQ_SDD, 1);

	cs = emit_srm(cs, RING_TIMESTAMP(engine->mmio_base), offset + 4016);
	cs = emit_srm(cs, RING_CTX_TIMESTAMP(engine->mmio_base), offset + 4012);

	पूर्णांकel_ring_advance(rq, cs);
	i915_request_get(rq);
	i915_request_add(rq);
	पूर्णांकel_engine_flush_submission(engine);

	/* Wait क्रम the request to start executing, that then रुकोs क्रम us */
	जबतक (READ_ONCE(sema[2]) == 0)
		cpu_relax();

	/* Run the request क्रम a 100us, sampling बारtamps beक्रमe/after */
	local_irq_disable();
	ग_लिखो_semaphore(&sema[2], 0);
	जबतक (READ_ONCE(sema[1]) == 0) /* रुको क्रम the gpu to catch up */
		cpu_relax();
	*dt = local_घड़ी();
	udelay(100);
	*dt = local_घड़ी() - *dt;
	ग_लिखो_semaphore(&sema[2], 1);
	local_irq_enable();

	अगर (i915_request_रुको(rq, 0, HZ / 2) < 0) अणु
		i915_request_put(rq);
		वापस -ETIME;
	पूर्ण
	i915_request_put(rq);

	pr_debug("%s CTX_TIMESTAMP: [%x, %x], RING_TIMESTAMP: [%x, %x]\n",
		 engine->name, sema[1], sema[3], sema[0], sema[4]);

	*d_ctx = sema[3] - sema[1];
	*d_ring = sema[4] - sema[0];
	वापस 0;
पूर्ण

अटल पूर्णांक __live_engine_बारtamps(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	u64 s_ring[COUNT], s_ctx[COUNT], st[COUNT], d_ring, d_ctx, dt;
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक i, err = 0;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	क्रम (i = 0; i < COUNT; i++) अणु
		err = __measure_बारtamps(ce, &st[i], &s_ring[i], &s_ctx[i]);
		अगर (err)
			अवरोध;
	पूर्ण
	पूर्णांकel_context_put(ce);
	अगर (err)
		वापस err;

	dt = trअगरilter(st);
	d_ring = trअगरilter(s_ring);
	d_ctx = trअगरilter(s_ctx);

	pr_info("%s elapsed:%lldns, CTX_TIMESTAMP:%lldns, RING_TIMESTAMP:%lldns\n",
		engine->name, dt,
		पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(engine->gt, d_ctx),
		पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(engine->gt, d_ring));

	d_ring = पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(engine->gt, d_ring);
	अगर (3 * dt > 4 * d_ring || 4 * dt < 3 * d_ring) अणु
		pr_err("%s Mismatch between ring timestamp and walltime!\n",
		       engine->name);
		वापस -EINVAL;
	पूर्ण

	d_ring = trअगरilter(s_ring);
	d_ctx = trअगरilter(s_ctx);

	d_ctx *= engine->gt->घड़ी_frequency;
	अगर (IS_ICELAKE(engine->i915))
		d_ring *= 12500000; /* Fixed 80ns क्रम icl ctx बारtamp? */
	अन्यथा
		d_ring *= engine->gt->घड़ी_frequency;

	अगर (3 * d_ctx > 4 * d_ring || 4 * d_ctx < 3 * d_ring) अणु
		pr_err("%s Mismatch between ring and context timestamps!\n",
		       engine->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक live_engine_बारtamps(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * Check that CS_TIMESTAMP / CTX_TIMESTAMP are in sync, i.e. share
	 * the same CS घड़ी.
	 */

	अगर (INTEL_GEN(gt->i915) < 8)
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांक err;

		st_engine_heartbeat_disable(engine);
		err = __live_engine_बारtamps(engine);
		st_engine_heartbeat_enable(engine);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक live_engine_busy_stats(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	/*
	 * Check that अगर an engine supports busy-stats, they tell the truth.
	 */

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	GEM_BUG_ON(पूर्णांकel_gt_pm_is_awake(gt));
	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq;
		kसमय_प्रकार de, dt;
		kसमय_प्रकार t[2];

		अगर (!पूर्णांकel_engine_supports_stats(engine))
			जारी;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (पूर्णांकel_gt_pm_रुको_क्रम_idle(gt)) अणु
			err = -EBUSY;
			अवरोध;
		पूर्ण

		st_engine_heartbeat_disable(engine);

		ENGINE_TRACE(engine, "measuring idle time\n");
		preempt_disable();
		de = पूर्णांकel_engine_get_busy_समय(engine, &t[0]);
		udelay(100);
		de = kसमय_sub(पूर्णांकel_engine_get_busy_समय(engine, &t[1]), de);
		preempt_enable();
		dt = kसमय_sub(t[1], t[0]);
		अगर (de < 0 || de > 10) अणु
			pr_err("%s: reported %lldns [%d%%] busyness while sleeping [for %lldns]\n",
			       engine->name,
			       de, (पूर्णांक)भाग64_u64(100 * de, dt), dt);
			GEM_TRACE_DUMP();
			err = -EINVAL;
			जाओ end;
		पूर्ण

		/* 100% busy */
		rq = igt_spinner_create_request(&spin,
						engine->kernel_context,
						MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ end;
		पूर्ण
		i915_request_add(rq);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			पूर्णांकel_gt_set_wedged(engine->gt);
			err = -ETIME;
			जाओ end;
		पूर्ण

		ENGINE_TRACE(engine, "measuring busy time\n");
		preempt_disable();
		de = पूर्णांकel_engine_get_busy_समय(engine, &t[0]);
		udelay(100);
		de = kसमय_sub(पूर्णांकel_engine_get_busy_समय(engine, &t[1]), de);
		preempt_enable();
		dt = kसमय_sub(t[1], t[0]);
		अगर (100 * de < 95 * dt || 95 * de > 100 * dt) अणु
			pr_err("%s: reported %lldns [%d%%] busyness while spinning [for %lldns]\n",
			       engine->name,
			       de, (पूर्णांक)भाग64_u64(100 * de, dt), dt);
			GEM_TRACE_DUMP();
			err = -EINVAL;
			जाओ end;
		पूर्ण

end:
		st_engine_heartbeat_enable(engine);
		igt_spinner_end(&spin);
		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	igt_spinner_fini(&spin);
	अगर (igt_flush_test(gt->i915))
		err = -EIO;
	वापस err;
पूर्ण

अटल पूर्णांक live_engine_pm(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * Check we can call पूर्णांकel_engine_pm_put from any context. No
	 * failures are reported directly, but अगर we mess up lockdep should
	 * tell us.
	 */
	अगर (पूर्णांकel_gt_pm_रुको_क्रम_idle(gt)) अणु
		pr_err("Unable to flush GT pm before test\n");
		वापस -EBUSY;
	पूर्ण

	GEM_BUG_ON(पूर्णांकel_gt_pm_is_awake(gt));
	क्रम_each_engine(engine, gt, id) अणु
		स्थिर typeof(*igt_atomic_phases) *p;

		क्रम (p = igt_atomic_phases; p->name; p++) अणु
			/*
			 * Acquisition is always synchronous, except अगर we
			 * know that the engine is alपढ़ोy awake, in which
			 * हाल we should use पूर्णांकel_engine_pm_get_अगर_awake()
			 * to atomically grab the wakeref.
			 *
			 * In practice,
			 *    पूर्णांकel_engine_pm_get();
			 *    पूर्णांकel_engine_pm_put();
			 * occurs in one thपढ़ो, जबतक simultaneously
			 *    पूर्णांकel_engine_pm_get_अगर_awake();
			 *    पूर्णांकel_engine_pm_put();
			 * occurs from atomic context in another.
			 */
			GEM_BUG_ON(पूर्णांकel_engine_pm_is_awake(engine));
			पूर्णांकel_engine_pm_get(engine);

			p->critical_section_begin();
			अगर (!पूर्णांकel_engine_pm_get_अगर_awake(engine))
				pr_err("intel_engine_pm_get_if_awake(%s) failed under %s\n",
				       engine->name, p->name);
			अन्यथा
				पूर्णांकel_engine_pm_put_async(engine);
			पूर्णांकel_engine_pm_put_async(engine);
			p->critical_section_end();

			पूर्णांकel_engine_pm_flush(engine);

			अगर (पूर्णांकel_engine_pm_is_awake(engine)) अणु
				pr_err("%s is still awake after flushing pm\n",
				       engine->name);
				वापस -EINVAL;
			पूर्ण

			/* gt wakeref is async (deferred to workqueue) */
			अगर (पूर्णांकel_gt_pm_रुको_क्रम_idle(gt)) अणु
				pr_err("GT failed to idle\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक live_engine_pm_selftests(काष्ठा पूर्णांकel_gt *gt)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_engine_बारtamps),
		SUBTEST(live_engine_busy_stats),
		SUBTEST(live_engine_pm),
	पूर्ण;

	वापस पूर्णांकel_gt_live_subtests(tests, gt);
पूर्ण
