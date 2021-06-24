<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "intel_context.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_ring.h"
#समावेश "selftest_rc6.h"

#समावेश "selftests/i915_random.h"
#समावेश "selftests/librapl.h"

अटल u64 rc6_residency(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	u64 result;

	/* XXX VLV_GT_MEDIA_RC6? */

	result = पूर्णांकel_rc6_residency_ns(rc6, GEN6_GT_GFX_RC6);
	अगर (HAS_RC6p(rc6_to_i915(rc6)))
		result += पूर्णांकel_rc6_residency_ns(rc6, GEN6_GT_GFX_RC6p);
	अगर (HAS_RC6pp(rc6_to_i915(rc6)))
		result += पूर्णांकel_rc6_residency_ns(rc6, GEN6_GT_GFX_RC6pp);

	वापस result;
पूर्ण

पूर्णांक live_rc6_manual(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_rc6 *rc6 = &gt->rc6;
	u64 rc0_घातer, rc6_घातer;
	पूर्णांकel_wakeref_t wakeref;
	kसमय_प्रकार dt;
	u64 res[2];
	पूर्णांक err = 0;

	/*
	 * Our claim is that we can "encourage" the GPU to enter rc6 at will.
	 * Let's try it!
	 */

	अगर (!rc6->enabled)
		वापस 0;

	/* bsw/byt use a PCU and decouple RC6 from our manual control */
	अगर (IS_VALLEYVIEW(gt->i915) || IS_CHERRYVIEW(gt->i915))
		वापस 0;

	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	/* Force RC6 off क्रम starters */
	__पूर्णांकel_rc6_disable(rc6);
	msleep(1); /* wakeup is not immediate, takes about 100us on icl */

	res[0] = rc6_residency(rc6);

	dt = kसमय_get();
	rc0_घातer = librapl_energy_uJ();
	msleep(250);
	rc0_घातer = librapl_energy_uJ() - rc0_घातer;
	dt = kसमय_sub(kसमय_get(), dt);
	res[1] = rc6_residency(rc6);
	अगर ((res[1] - res[0]) >> 10) अणु
		pr_err("RC6 residency increased by %lldus while disabled for 250ms!\n",
		       (res[1] - res[0]) >> 10);
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	rc0_घातer = भाग64_u64(NSEC_PER_SEC * rc0_घातer, kसमय_प्रकारo_ns(dt));
	अगर (!rc0_घातer) अणु
		pr_err("No power measured while in RC0\n");
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* Manually enter RC6 */
	पूर्णांकel_rc6_park(rc6);

	res[0] = rc6_residency(rc6);
	पूर्णांकel_uncore_क्रमcewake_flush(rc6_to_uncore(rc6), FORCEWAKE_ALL);
	dt = kसमय_get();
	rc6_घातer = librapl_energy_uJ();
	msleep(100);
	rc6_घातer = librapl_energy_uJ() - rc6_घातer;
	dt = kसमय_sub(kसमय_get(), dt);
	res[1] = rc6_residency(rc6);
	अगर (res[1] == res[0]) अणु
		pr_err("Did not enter RC6! RC6_STATE=%08x, RC6_CONTROL=%08x, residency=%lld\n",
		       पूर्णांकel_uncore_पढ़ो_fw(gt->uncore, GEN6_RC_STATE),
		       पूर्णांकel_uncore_पढ़ो_fw(gt->uncore, GEN6_RC_CONTROL),
		       res[0]);
		err = -EINVAL;
	पूर्ण

	rc6_घातer = भाग64_u64(NSEC_PER_SEC * rc6_घातer, kसमय_प्रकारo_ns(dt));
	pr_info("GPU consumed %llduW in RC0 and %llduW in RC6\n",
		rc0_घातer, rc6_घातer);
	अगर (2 * rc6_घातer > rc0_घातer) अणु
		pr_err("GPU leaked energy while in RC6!\n");
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* Restore what should have been the original state! */
	पूर्णांकel_rc6_unpark(rc6);

out_unlock:
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
	वापस err;
पूर्ण

अटल स्थिर u32 *__live_rc6_ctx(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_request *rq;
	स्थिर u32 *result;
	u32 cmd;
	u32 *cs;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस ERR_CAST(rq);

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस cs;
	पूर्ण

	cmd = MI_STORE_REGISTER_MEM | MI_USE_GGTT;
	अगर (INTEL_GEN(rq->engine->i915) >= 8)
		cmd++;

	*cs++ = cmd;
	*cs++ = i915_mmio_reg_offset(GEN8_RC6_CTX_INFO);
	*cs++ = ce->समयline->hwsp_offset + 8;
	*cs++ = 0;
	पूर्णांकel_ring_advance(rq, cs);

	result = rq->hwsp_seqno + 2;
	i915_request_add(rq);

	वापस result;
पूर्ण

अटल काष्ठा पूर्णांकel_engine_cs **
अक्रमomised_engines(काष्ठा पूर्णांकel_gt *gt,
		   काष्ठा rnd_state *prng,
		   अचिन्हित पूर्णांक *count)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine, **engines;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक n;

	n = 0;
	क्रम_each_engine(engine, gt, id)
		n++;
	अगर (!n)
		वापस शून्य;

	engines = kदो_स्मृति_array(n, माप(*engines), GFP_KERNEL);
	अगर (!engines)
		वापस शून्य;

	n = 0;
	क्रम_each_engine(engine, gt, id)
		engines[n++] = engine;

	i915_pअक्रमom_shuffle(engines, माप(*engines), n, prng);

	*count = n;
	वापस engines;
पूर्ण

पूर्णांक live_rc6_ctx_wa(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs **engines;
	अचिन्हित पूर्णांक n, count;
	I915_RND_STATE(prng);
	पूर्णांक err = 0;

	/* A पढ़ो of CTX_INFO upsets rc6. Poke the bear! */
	अगर (INTEL_GEN(gt->i915) < 8)
		वापस 0;

	engines = अक्रमomised_engines(gt, &prng, &count);
	अगर (!engines)
		वापस 0;

	क्रम (n = 0; n < count; n++) अणु
		काष्ठा पूर्णांकel_engine_cs *engine = engines[n];
		पूर्णांक pass;

		क्रम (pass = 0; pass < 2; pass++) अणु
			काष्ठा i915_gpu_error *error = &gt->i915->gpu_error;
			काष्ठा पूर्णांकel_context *ce;
			अचिन्हित पूर्णांक resets =
				i915_reset_engine_count(error, engine);
			स्थिर u32 *res;

			/* Use a sacrअगरical context */
			ce = पूर्णांकel_context_create(engine);
			अगर (IS_ERR(ce)) अणु
				err = PTR_ERR(ce);
				जाओ out;
			पूर्ण

			पूर्णांकel_engine_pm_get(engine);
			res = __live_rc6_ctx(ce);
			पूर्णांकel_engine_pm_put(engine);
			पूर्णांकel_context_put(ce);
			अगर (IS_ERR(res)) अणु
				err = PTR_ERR(res);
				जाओ out;
			पूर्ण

			अगर (पूर्णांकel_gt_रुको_क्रम_idle(gt, HZ / 5) == -ETIME) अणु
				पूर्णांकel_gt_set_wedged(gt);
				err = -ETIME;
				जाओ out;
			पूर्ण

			पूर्णांकel_gt_pm_रुको_क्रम_idle(gt);
			pr_debug("%s: CTX_INFO=%0x\n",
				 engine->name, READ_ONCE(*res));

			अगर (resets !=
			    i915_reset_engine_count(error, engine)) अणु
				pr_err("%s: GPU reset required\n",
				       engine->name);
				add_taपूर्णांक_क्रम_CI(gt->i915, TAINT_WARN);
				err = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(engines);
	वापस err;
पूर्ण
