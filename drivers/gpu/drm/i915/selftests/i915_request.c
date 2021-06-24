<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/prime_numbers.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/sort.h>

#समावेश "gem/i915_gem_pm.h"
#समावेश "gem/selftests/mock_context.h"

#समावेश "gt/intel_engine_heartbeat.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_clock_utils.h"
#समावेश "gt/intel_gt_requests.h"
#समावेश "gt/selftest_engine_heartbeat.h"

#समावेश "i915_random.h"
#समावेश "i915_selftest.h"
#समावेश "igt_flush_test.h"
#समावेश "igt_live_test.h"
#समावेश "igt_spinner.h"
#समावेश "lib_sw_fence.h"

#समावेश "mock_drm.h"
#समावेश "mock_gem_device.h"

अटल अचिन्हित पूर्णांक num_uabi_engines(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित पूर्णांक count;

	count = 0;
	क्रम_each_uabi_engine(engine, i915)
		count++;

	वापस count;
पूर्ण

अटल काष्ठा पूर्णांकel_engine_cs *rcs0(काष्ठा drm_i915_निजी *i915)
अणु
	वापस पूर्णांकel_engine_lookup_user(i915, I915_ENGINE_CLASS_RENDER, 0);
पूर्ण

अटल पूर्णांक igt_add_request(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_request *request;

	/* Basic preliminary test to create a request and let it loose! */

	request = mock_request(rcs0(i915)->kernel_context, HZ / 10);
	अगर (!request)
		वापस -ENOMEM;

	i915_request_add(request);

	वापस 0;
पूर्ण

अटल पूर्णांक igt_रुको_request(व्योम *arg)
अणु
	स्थिर दीर्घ T = HZ / 4;
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_request *request;
	पूर्णांक err = -EINVAL;

	/* Submit a request, then रुको upon it */

	request = mock_request(rcs0(i915)->kernel_context, T);
	अगर (!request)
		वापस -ENOMEM;

	i915_request_get(request);

	अगर (i915_request_रुको(request, 0, 0) != -ETIME) अणु
		pr_err("request wait (busy query) succeeded (expected timeout before submit!)\n");
		जाओ out_request;
	पूर्ण

	अगर (i915_request_रुको(request, 0, T) != -ETIME) अणु
		pr_err("request wait succeeded (expected timeout before submit!)\n");
		जाओ out_request;
	पूर्ण

	अगर (i915_request_completed(request)) अणु
		pr_err("request completed before submit!!\n");
		जाओ out_request;
	पूर्ण

	i915_request_add(request);

	अगर (i915_request_रुको(request, 0, 0) != -ETIME) अणु
		pr_err("request wait (busy query) succeeded (expected timeout after submit!)\n");
		जाओ out_request;
	पूर्ण

	अगर (i915_request_completed(request)) अणु
		pr_err("request completed immediately!\n");
		जाओ out_request;
	पूर्ण

	अगर (i915_request_रुको(request, 0, T / 2) != -ETIME) अणु
		pr_err("request wait succeeded (expected timeout!)\n");
		जाओ out_request;
	पूर्ण

	अगर (i915_request_रुको(request, 0, T) == -ETIME) अणु
		pr_err("request wait timed out!\n");
		जाओ out_request;
	पूर्ण

	अगर (!i915_request_completed(request)) अणु
		pr_err("request not complete after waiting!\n");
		जाओ out_request;
	पूर्ण

	अगर (i915_request_रुको(request, 0, T) == -ETIME) अणु
		pr_err("request wait timed out when already complete!\n");
		जाओ out_request;
	पूर्ण

	err = 0;
out_request:
	i915_request_put(request);
	mock_device_flush(i915);
	वापस err;
पूर्ण

अटल पूर्णांक igt_fence_रुको(व्योम *arg)
अणु
	स्थिर दीर्घ T = HZ / 4;
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_request *request;
	पूर्णांक err = -EINVAL;

	/* Submit a request, treat it as a fence and रुको upon it */

	request = mock_request(rcs0(i915)->kernel_context, T);
	अगर (!request)
		वापस -ENOMEM;

	अगर (dma_fence_रुको_समयout(&request->fence, false, T) != -ETIME) अणु
		pr_err("fence wait success before submit (expected timeout)!\n");
		जाओ out;
	पूर्ण

	i915_request_add(request);

	अगर (dma_fence_is_संकेतed(&request->fence)) अणु
		pr_err("fence signaled immediately!\n");
		जाओ out;
	पूर्ण

	अगर (dma_fence_रुको_समयout(&request->fence, false, T / 2) != -ETIME) अणु
		pr_err("fence wait success after submit (expected timeout)!\n");
		जाओ out;
	पूर्ण

	अगर (dma_fence_रुको_समयout(&request->fence, false, T) <= 0) अणु
		pr_err("fence wait timed out (expected success)!\n");
		जाओ out;
	पूर्ण

	अगर (!dma_fence_is_संकेतed(&request->fence)) अणु
		pr_err("fence unsignaled after waiting!\n");
		जाओ out;
	पूर्ण

	अगर (dma_fence_रुको_समयout(&request->fence, false, T) <= 0) अणु
		pr_err("fence wait timed out when complete (expected success)!\n");
		जाओ out;
	पूर्ण

	err = 0;
out:
	mock_device_flush(i915);
	वापस err;
पूर्ण

अटल पूर्णांक igt_request_शुरुआत(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_request *request, *vip;
	काष्ठा i915_gem_context *ctx[2];
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err = -EINVAL;

	ctx[0] = mock_context(i915, "A");

	ce = i915_gem_context_get_engine(ctx[0], RCS0);
	GEM_BUG_ON(IS_ERR(ce));
	request = mock_request(ce, 2 * HZ);
	पूर्णांकel_context_put(ce);
	अगर (!request) अणु
		err = -ENOMEM;
		जाओ err_context_0;
	पूर्ण

	i915_request_get(request);
	i915_request_add(request);

	ctx[1] = mock_context(i915, "B");

	ce = i915_gem_context_get_engine(ctx[1], RCS0);
	GEM_BUG_ON(IS_ERR(ce));
	vip = mock_request(ce, 0);
	पूर्णांकel_context_put(ce);
	अगर (!vip) अणु
		err = -ENOMEM;
		जाओ err_context_1;
	पूर्ण

	/* Simulate preemption by manual reordering */
	अगर (!mock_cancel_request(request)) अणु
		pr_err("failed to cancel request (already executed)!\n");
		i915_request_add(vip);
		जाओ err_context_1;
	पूर्ण
	i915_request_get(vip);
	i915_request_add(vip);
	rcu_पढ़ो_lock();
	request->engine->submit_request(request);
	rcu_पढ़ो_unlock();


	अगर (i915_request_रुको(vip, 0, HZ) == -ETIME) अणु
		pr_err("timed out waiting for high priority request\n");
		जाओ err;
	पूर्ण

	अगर (i915_request_completed(request)) अणु
		pr_err("low priority request already completed\n");
		जाओ err;
	पूर्ण

	err = 0;
err:
	i915_request_put(vip);
err_context_1:
	mock_context_बंद(ctx[1]);
	i915_request_put(request);
err_context_0:
	mock_context_बंद(ctx[0]);
	mock_device_flush(i915);
	वापस err;
पूर्ण

काष्ठा smoketest अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_gem_context **contexts;
	atomic_दीर्घ_t num_रुकोs, num_fences;
	पूर्णांक ncontexts, max_batch;
	काष्ठा i915_request *(*request_alloc)(काष्ठा पूर्णांकel_context *ce);
पूर्ण;

अटल काष्ठा i915_request *
__mock_request_alloc(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस mock_request(ce, 0);
पूर्ण

अटल काष्ठा i915_request *
__live_request_alloc(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस पूर्णांकel_context_create_request(ce);
पूर्ण

अटल पूर्णांक __igt_bपढ़ोcrumbs_smoketest(व्योम *arg)
अणु
	काष्ठा smoketest *t = arg;
	स्थिर अचिन्हित पूर्णांक max_batch = min(t->ncontexts, t->max_batch) - 1;
	स्थिर अचिन्हित पूर्णांक total = 4 * t->ncontexts + 1;
	अचिन्हित पूर्णांक num_रुकोs = 0, num_fences = 0;
	काष्ठा i915_request **requests;
	I915_RND_STATE(prng);
	अचिन्हित पूर्णांक *order;
	पूर्णांक err = 0;

	/*
	 * A very simple test to catch the most egregious of list handling bugs.
	 *
	 * At its heart, we simply create oodles of requests running across
	 * multiple kthपढ़ोs and enable संकेतing on them, क्रम the sole purpose
	 * of stressing our bपढ़ोcrumb handling. The only inspection we करो is
	 * that the fences were marked as संकेतed.
	 */

	requests = kसुस्मृति(total, माप(*requests), GFP_KERNEL);
	अगर (!requests)
		वापस -ENOMEM;

	order = i915_अक्रमom_order(total, &prng);
	अगर (!order) अणु
		err = -ENOMEM;
		जाओ out_requests;
	पूर्ण

	जबतक (!kthपढ़ो_should_stop()) अणु
		काष्ठा i915_sw_fence *submit, *रुको;
		अचिन्हित पूर्णांक n, count;

		submit = heap_fence_create(GFP_KERNEL);
		अगर (!submit) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		रुको = heap_fence_create(GFP_KERNEL);
		अगर (!रुको) अणु
			i915_sw_fence_commit(submit);
			heap_fence_put(submit);
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		i915_अक्रमom_reorder(order, total, &prng);
		count = 1 + i915_pअक्रमom_u32_max_state(max_batch, &prng);

		क्रम (n = 0; n < count; n++) अणु
			काष्ठा i915_gem_context *ctx =
				t->contexts[order[n] % t->ncontexts];
			काष्ठा i915_request *rq;
			काष्ठा पूर्णांकel_context *ce;

			ce = i915_gem_context_get_engine(ctx, t->engine->legacy_idx);
			GEM_BUG_ON(IS_ERR(ce));
			rq = t->request_alloc(ce);
			पूर्णांकel_context_put(ce);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				count = n;
				अवरोध;
			पूर्ण

			err = i915_sw_fence_aरुको_sw_fence_gfp(&rq->submit,
							       submit,
							       GFP_KERNEL);

			requests[n] = i915_request_get(rq);
			i915_request_add(rq);

			अगर (err >= 0)
				err = i915_sw_fence_aरुको_dma_fence(रुको,
								    &rq->fence,
								    0,
								    GFP_KERNEL);

			अगर (err < 0) अणु
				i915_request_put(rq);
				count = n;
				अवरोध;
			पूर्ण
		पूर्ण

		i915_sw_fence_commit(submit);
		i915_sw_fence_commit(रुको);

		अगर (!रुको_event_समयout(रुको->रुको,
					i915_sw_fence_करोne(रुको),
					5 * HZ)) अणु
			काष्ठा i915_request *rq = requests[count - 1];

			pr_err("waiting for %d/%d fences (last %llx:%lld) on %s timed out!\n",
			       atomic_पढ़ो(&रुको->pending), count,
			       rq->fence.context, rq->fence.seqno,
			       t->engine->name);
			GEM_TRACE_DUMP();

			पूर्णांकel_gt_set_wedged(t->engine->gt);
			GEM_BUG_ON(!i915_request_completed(rq));
			i915_sw_fence_रुको(रुको);
			err = -EIO;
		पूर्ण

		क्रम (n = 0; n < count; n++) अणु
			काष्ठा i915_request *rq = requests[n];

			अगर (!test_bit(DMA_FENCE_FLAG_SIGNALED_BIT,
				      &rq->fence.flags)) अणु
				pr_err("%llu:%llu was not signaled!\n",
				       rq->fence.context, rq->fence.seqno);
				err = -EINVAL;
			पूर्ण

			i915_request_put(rq);
		पूर्ण

		heap_fence_put(रुको);
		heap_fence_put(submit);

		अगर (err < 0)
			अवरोध;

		num_fences += count;
		num_रुकोs++;

		cond_resched();
	पूर्ण

	atomic_दीर्घ_add(num_fences, &t->num_fences);
	atomic_दीर्घ_add(num_रुकोs, &t->num_रुकोs);

	kमुक्त(order);
out_requests:
	kमुक्त(requests);
	वापस err;
पूर्ण

अटल पूर्णांक mock_bपढ़ोcrumbs_smoketest(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा smoketest t = अणु
		.engine = rcs0(i915),
		.ncontexts = 1024,
		.max_batch = 1024,
		.request_alloc = __mock_request_alloc
	पूर्ण;
	अचिन्हित पूर्णांक ncpus = num_online_cpus();
	काष्ठा task_काष्ठा **thपढ़ोs;
	अचिन्हित पूर्णांक n;
	पूर्णांक ret = 0;

	/*
	 * Smoketest our bपढ़ोcrumb/संकेत handling क्रम requests across multiple
	 * thपढ़ोs. A very simple test to only catch the most egregious of bugs.
	 * See __igt_bपढ़ोcrumbs_smoketest();
	 */

	thपढ़ोs = kसुस्मृति(ncpus, माप(*thपढ़ोs), GFP_KERNEL);
	अगर (!thपढ़ोs)
		वापस -ENOMEM;

	t.contexts = kसुस्मृति(t.ncontexts, माप(*t.contexts), GFP_KERNEL);
	अगर (!t.contexts) अणु
		ret = -ENOMEM;
		जाओ out_thपढ़ोs;
	पूर्ण

	क्रम (n = 0; n < t.ncontexts; n++) अणु
		t.contexts[n] = mock_context(t.engine->i915, "mock");
		अगर (!t.contexts[n]) अणु
			ret = -ENOMEM;
			जाओ out_contexts;
		पूर्ण
	पूर्ण

	क्रम (n = 0; n < ncpus; n++) अणु
		thपढ़ोs[n] = kthपढ़ो_run(__igt_bपढ़ोcrumbs_smoketest,
					 &t, "igt/%d", n);
		अगर (IS_ERR(thपढ़ोs[n])) अणु
			ret = PTR_ERR(thपढ़ोs[n]);
			ncpus = n;
			अवरोध;
		पूर्ण

		get_task_काष्ठा(thपढ़ोs[n]);
	पूर्ण

	yield(); /* start all thपढ़ोs beक्रमe we begin */
	msleep(jअगरfies_to_msecs(i915_selftest.समयout_jअगरfies));

	क्रम (n = 0; n < ncpus; n++) अणु
		पूर्णांक err;

		err = kthपढ़ो_stop(thपढ़ोs[n]);
		अगर (err < 0 && !ret)
			ret = err;

		put_task_काष्ठा(thपढ़ोs[n]);
	पूर्ण
	pr_info("Completed %lu waits for %lu fence across %d cpus\n",
		atomic_दीर्घ_पढ़ो(&t.num_रुकोs),
		atomic_दीर्घ_पढ़ो(&t.num_fences),
		ncpus);

out_contexts:
	क्रम (n = 0; n < t.ncontexts; n++) अणु
		अगर (!t.contexts[n])
			अवरोध;
		mock_context_बंद(t.contexts[n]);
	पूर्ण
	kमुक्त(t.contexts);
out_thपढ़ोs:
	kमुक्त(thपढ़ोs);
	वापस ret;
पूर्ण

पूर्णांक i915_request_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_add_request),
		SUBTEST(igt_रुको_request),
		SUBTEST(igt_fence_रुको),
		SUBTEST(igt_request_शुरुआत),
		SUBTEST(mock_bपढ़ोcrumbs_smoketest),
	पूर्ण;
	काष्ठा drm_i915_निजी *i915;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक err = 0;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref)
		err = i915_subtests(tests, i915);

	mock_destroy_device(i915);

	वापस err;
पूर्ण

अटल पूर्णांक live_nop_request(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा igt_live_test t;
	पूर्णांक err = -ENODEV;

	/*
	 * Submit various sized batches of empty requests, to each engine
	 * (inभागidually), and रुको क्रम the batch to complete. We can check
	 * the overhead of submitting requests to the hardware.
	 */

	क्रम_each_uabi_engine(engine, i915) अणु
		अचिन्हित दीर्घ n, prime;
		IGT_TIMEOUT(end_समय);
		kसमय_प्रकार बार[2] = अणुपूर्ण;

		err = igt_live_test_begin(&t, i915, __func__, engine->name);
		अगर (err)
			वापस err;

		पूर्णांकel_engine_pm_get(engine);
		क्रम_each_prime_number_from(prime, 1, 8192) अणु
			काष्ठा i915_request *request = शून्य;

			बार[1] = kसमय_get_raw();

			क्रम (n = 0; n < prime; n++) अणु
				i915_request_put(request);
				request = i915_request_create(engine->kernel_context);
				अगर (IS_ERR(request))
					वापस PTR_ERR(request);

				/*
				 * This space is left पूर्णांकentionally blank.
				 *
				 * We करो not actually want to perक्रमm any
				 * action with this request, we just want
				 * to measure the latency in allocation
				 * and submission of our bपढ़ोcrumbs -
				 * ensuring that the bare request is sufficient
				 * क्रम the प्रणाली to work (i.e. proper HEAD
				 * tracking of the rings, पूर्णांकerrupt handling,
				 * etc). It also gives us the lowest bounds
				 * क्रम latency.
				 */

				i915_request_get(request);
				i915_request_add(request);
			पूर्ण
			i915_request_रुको(request, 0, MAX_SCHEDULE_TIMEOUT);
			i915_request_put(request);

			बार[1] = kसमय_sub(kसमय_get_raw(), बार[1]);
			अगर (prime == 1)
				बार[0] = बार[1];

			अगर (__igt_समयout(end_समय, शून्य))
				अवरोध;
		पूर्ण
		पूर्णांकel_engine_pm_put(engine);

		err = igt_live_test_end(&t);
		अगर (err)
			वापस err;

		pr_info("Request latencies on %s: 1 = %lluns, %lu = %lluns\n",
			engine->name,
			kसमय_प्रकारo_ns(बार[0]),
			prime, भाग64_u64(kसमय_प्रकारo_ns(बार[1]), prime));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __cancel_inactive(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा igt_spinner spin;
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;

	अगर (igt_spinner_init(&spin, engine->gt))
		वापस -ENOMEM;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce)) अणु
		err = PTR_ERR(ce);
		जाओ out_spin;
	पूर्ण

	rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_ce;
	पूर्ण

	pr_debug("%s: Cancelling inactive request\n", engine->name);
	i915_request_cancel(rq, -EINTR);
	i915_request_get(rq);
	i915_request_add(rq);

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(engine->i915->drm.dev);

		pr_err("%s: Failed to cancel inactive request\n", engine->name);
		पूर्णांकel_engine_dump(engine, &p, "%s\n", engine->name);
		err = -ETIME;
		जाओ out_rq;
	पूर्ण

	अगर (rq->fence.error != -EINTR) अणु
		pr_err("%s: fence not cancelled (%u)\n",
		       engine->name, rq->fence.error);
		err = -EINVAL;
	पूर्ण

out_rq:
	i915_request_put(rq);
out_ce:
	पूर्णांकel_context_put(ce);
out_spin:
	igt_spinner_fini(&spin);
	अगर (err)
		pr_err("%s: %s error %d\n", __func__, engine->name, err);
	वापस err;
पूर्ण

अटल पूर्णांक __cancel_active(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा igt_spinner spin;
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;

	अगर (igt_spinner_init(&spin, engine->gt))
		वापस -ENOMEM;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce)) अणु
		err = PTR_ERR(ce);
		जाओ out_spin;
	पूर्ण

	rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_ce;
	पूर्ण

	pr_debug("%s: Cancelling active request\n", engine->name);
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(engine->i915->drm.dev);

		pr_err("Failed to start spinner on %s\n", engine->name);
		पूर्णांकel_engine_dump(engine, &p, "%s\n", engine->name);
		err = -ETIME;
		जाओ out_rq;
	पूर्ण
	i915_request_cancel(rq, -EINTR);

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(engine->i915->drm.dev);

		pr_err("%s: Failed to cancel active request\n", engine->name);
		पूर्णांकel_engine_dump(engine, &p, "%s\n", engine->name);
		err = -ETIME;
		जाओ out_rq;
	पूर्ण

	अगर (rq->fence.error != -EINTR) अणु
		pr_err("%s: fence not cancelled (%u)\n",
		       engine->name, rq->fence.error);
		err = -EINVAL;
	पूर्ण

out_rq:
	i915_request_put(rq);
out_ce:
	पूर्णांकel_context_put(ce);
out_spin:
	igt_spinner_fini(&spin);
	अगर (err)
		pr_err("%s: %s error %d\n", __func__, engine->name, err);
	वापस err;
पूर्ण

अटल पूर्णांक __cancel_completed(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा igt_spinner spin;
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;

	अगर (igt_spinner_init(&spin, engine->gt))
		वापस -ENOMEM;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce)) अणु
		err = PTR_ERR(ce);
		जाओ out_spin;
	पूर्ण

	rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_ce;
	पूर्ण
	igt_spinner_end(&spin);
	i915_request_get(rq);
	i915_request_add(rq);

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
		err = -ETIME;
		जाओ out_rq;
	पूर्ण

	pr_debug("%s: Cancelling completed request\n", engine->name);
	i915_request_cancel(rq, -EINTR);
	अगर (rq->fence.error) अणु
		pr_err("%s: fence not cancelled (%u)\n",
		       engine->name, rq->fence.error);
		err = -EINVAL;
	पूर्ण

out_rq:
	i915_request_put(rq);
out_ce:
	पूर्णांकel_context_put(ce);
out_spin:
	igt_spinner_fini(&spin);
	अगर (err)
		pr_err("%s: %s error %d\n", __func__, engine->name, err);
	वापस err;
पूर्ण

अटल पूर्णांक live_cancel_request(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;

	/*
	 * Check cancellation of requests. We expect to be able to immediately
	 * cancel active requests, even अगर they are currently on the GPU.
	 */

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा igt_live_test t;
		पूर्णांक err, err2;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		err = igt_live_test_begin(&t, i915, __func__, engine->name);
		अगर (err)
			वापस err;

		err = __cancel_inactive(engine);
		अगर (err == 0)
			err = __cancel_active(engine);
		अगर (err == 0)
			err = __cancel_completed(engine);

		err2 = igt_live_test_end(&t);
		अगर (err)
			वापस err;
		अगर (err2)
			वापस err2;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i915_vma *empty_batch(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 *cmd;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	cmd = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ err;
	पूर्ण

	*cmd = MI_BATCH_BUFFER_END;

	__i915_gem_object_flush_map(obj, 0, 64);
	i915_gem_object_unpin_map(obj);

	पूर्णांकel_gt_chipset_flush(&i915->gt);

	vma = i915_vma_instance(obj, &i915->ggtt.vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER | PIN_GLOBAL);
	अगर (err)
		जाओ err;

	/* Force the रुको रुको now to aव्योम including it in the benchmark */
	err = i915_vma_sync(vma);
	अगर (err)
		जाओ err_pin;

	वापस vma;

err_pin:
	i915_vma_unpin(vma);
err:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा i915_request *
empty_request(काष्ठा पूर्णांकel_engine_cs *engine,
	      काष्ठा i915_vma *batch)
अणु
	काष्ठा i915_request *request;
	पूर्णांक err;

	request = i915_request_create(engine->kernel_context);
	अगर (IS_ERR(request))
		वापस request;

	err = engine->emit_bb_start(request,
				    batch->node.start,
				    batch->node.size,
				    I915_DISPATCH_SECURE);
	अगर (err)
		जाओ out_request;

	i915_request_get(request);
out_request:
	i915_request_add(request);
	वापस err ? ERR_PTR(err) : request;
पूर्ण

अटल पूर्णांक live_empty_request(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा igt_live_test t;
	काष्ठा i915_vma *batch;
	पूर्णांक err = 0;

	/*
	 * Submit various sized batches of empty requests, to each engine
	 * (inभागidually), and रुको क्रम the batch to complete. We can check
	 * the overhead of submitting requests to the hardware.
	 */

	batch = empty_batch(i915);
	अगर (IS_ERR(batch))
		वापस PTR_ERR(batch);

	क्रम_each_uabi_engine(engine, i915) अणु
		IGT_TIMEOUT(end_समय);
		काष्ठा i915_request *request;
		अचिन्हित दीर्घ n, prime;
		kसमय_प्रकार बार[2] = अणुपूर्ण;

		err = igt_live_test_begin(&t, i915, __func__, engine->name);
		अगर (err)
			जाओ out_batch;

		पूर्णांकel_engine_pm_get(engine);

		/* Warmup / preload */
		request = empty_request(engine, batch);
		अगर (IS_ERR(request)) अणु
			err = PTR_ERR(request);
			पूर्णांकel_engine_pm_put(engine);
			जाओ out_batch;
		पूर्ण
		i915_request_रुको(request, 0, MAX_SCHEDULE_TIMEOUT);

		क्रम_each_prime_number_from(prime, 1, 8192) अणु
			बार[1] = kसमय_get_raw();

			क्रम (n = 0; n < prime; n++) अणु
				i915_request_put(request);
				request = empty_request(engine, batch);
				अगर (IS_ERR(request)) अणु
					err = PTR_ERR(request);
					पूर्णांकel_engine_pm_put(engine);
					जाओ out_batch;
				पूर्ण
			पूर्ण
			i915_request_रुको(request, 0, MAX_SCHEDULE_TIMEOUT);

			बार[1] = kसमय_sub(kसमय_get_raw(), बार[1]);
			अगर (prime == 1)
				बार[0] = बार[1];

			अगर (__igt_समयout(end_समय, शून्य))
				अवरोध;
		पूर्ण
		i915_request_put(request);
		पूर्णांकel_engine_pm_put(engine);

		err = igt_live_test_end(&t);
		अगर (err)
			जाओ out_batch;

		pr_info("Batch latencies on %s: 1 = %lluns, %lu = %lluns\n",
			engine->name,
			kसमय_प्रकारo_ns(बार[0]),
			prime, भाग64_u64(kसमय_प्रकारo_ns(बार[1]), prime));
	पूर्ण

out_batch:
	i915_vma_unpin(batch);
	i915_vma_put(batch);
	वापस err;
पूर्ण

अटल काष्ठा i915_vma *recursive_batch(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_i915_gem_object *obj;
	स्थिर पूर्णांक gen = INTEL_GEN(i915);
	काष्ठा i915_vma *vma;
	u32 *cmd;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, i915->gt.vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ err;

	cmd = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ err;
	पूर्ण

	अगर (gen >= 8) अणु
		*cmd++ = MI_BATCH_BUFFER_START | 1 << 8 | 1;
		*cmd++ = lower_32_bits(vma->node.start);
		*cmd++ = upper_32_bits(vma->node.start);
	पूर्ण अन्यथा अगर (gen >= 6) अणु
		*cmd++ = MI_BATCH_BUFFER_START | 1 << 8;
		*cmd++ = lower_32_bits(vma->node.start);
	पूर्ण अन्यथा अणु
		*cmd++ = MI_BATCH_BUFFER_START | MI_BATCH_GTT;
		*cmd++ = lower_32_bits(vma->node.start);
	पूर्ण
	*cmd++ = MI_BATCH_BUFFER_END; /* terminate early in हाल of error */

	__i915_gem_object_flush_map(obj, 0, 64);
	i915_gem_object_unpin_map(obj);

	पूर्णांकel_gt_chipset_flush(&i915->gt);

	वापस vma;

err:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक recursive_batch_resolve(काष्ठा i915_vma *batch)
अणु
	u32 *cmd;

	cmd = i915_gem_object_pin_map_unlocked(batch->obj, I915_MAP_WC);
	अगर (IS_ERR(cmd))
		वापस PTR_ERR(cmd);

	*cmd = MI_BATCH_BUFFER_END;

	__i915_gem_object_flush_map(batch->obj, 0, माप(*cmd));
	i915_gem_object_unpin_map(batch->obj);

	पूर्णांकel_gt_chipset_flush(batch->vm->gt);

	वापस 0;
पूर्ण

अटल पूर्णांक live_all_engines(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	स्थिर अचिन्हित पूर्णांक nengines = num_uabi_engines(i915);
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_request **request;
	काष्ठा igt_live_test t;
	काष्ठा i915_vma *batch;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	/*
	 * Check we can submit requests to all engines simultaneously. We
	 * send a recursive batch to each engine - checking that we करोn't
	 * block करोing so, and that they करोn't complete too soon.
	 */

	request = kसुस्मृति(nengines, माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	err = igt_live_test_begin(&t, i915, __func__, "");
	अगर (err)
		जाओ out_मुक्त;

	batch = recursive_batch(i915);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		pr_err("%s: Unable to create batch, err=%d\n", __func__, err);
		जाओ out_मुक्त;
	पूर्ण

	i915_vma_lock(batch);

	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		request[idx] = पूर्णांकel_engine_create_kernel_request(engine);
		अगर (IS_ERR(request[idx])) अणु
			err = PTR_ERR(request[idx]);
			pr_err("%s: Request allocation failed with err=%d\n",
			       __func__, err);
			जाओ out_request;
		पूर्ण

		err = i915_request_aरुको_object(request[idx], batch->obj, 0);
		अगर (err == 0)
			err = i915_vma_move_to_active(batch, request[idx], 0);
		GEM_BUG_ON(err);

		err = engine->emit_bb_start(request[idx],
					    batch->node.start,
					    batch->node.size,
					    0);
		GEM_BUG_ON(err);
		request[idx]->batch = batch;

		i915_request_get(request[idx]);
		i915_request_add(request[idx]);
		idx++;
	पूर्ण

	i915_vma_unlock(batch);

	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		अगर (i915_request_completed(request[idx])) अणु
			pr_err("%s(%s): request completed too early!\n",
			       __func__, engine->name);
			err = -EINVAL;
			जाओ out_request;
		पूर्ण
		idx++;
	पूर्ण

	err = recursive_batch_resolve(batch);
	अगर (err) अणु
		pr_err("%s: failed to resolve batch, err=%d\n", __func__, err);
		जाओ out_request;
	पूर्ण

	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		दीर्घ समयout;

		समयout = i915_request_रुको(request[idx], 0,
					    MAX_SCHEDULE_TIMEOUT);
		अगर (समयout < 0) अणु
			err = समयout;
			pr_err("%s: error waiting for request on %s, err=%d\n",
			       __func__, engine->name, err);
			जाओ out_request;
		पूर्ण

		GEM_BUG_ON(!i915_request_completed(request[idx]));
		i915_request_put(request[idx]);
		request[idx] = शून्य;
		idx++;
	पूर्ण

	err = igt_live_test_end(&t);

out_request:
	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		अगर (request[idx])
			i915_request_put(request[idx]);
		idx++;
	पूर्ण
	i915_vma_unpin(batch);
	i915_vma_put(batch);
out_मुक्त:
	kमुक्त(request);
	वापस err;
पूर्ण

अटल पूर्णांक live_sequential_engines(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	स्थिर अचिन्हित पूर्णांक nengines = num_uabi_engines(i915);
	काष्ठा i915_request **request;
	काष्ठा i915_request *prev = शून्य;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा igt_live_test t;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	/*
	 * Check we can submit requests to all engines sequentially, such
	 * that each successive request रुकोs क्रम the earlier ones. This
	 * tests that we करोn't execute requests out of order, even though
	 * they are running on independent engines.
	 */

	request = kसुस्मृति(nengines, माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	err = igt_live_test_begin(&t, i915, __func__, "");
	अगर (err)
		जाओ out_मुक्त;

	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा i915_vma *batch;

		batch = recursive_batch(i915);
		अगर (IS_ERR(batch)) अणु
			err = PTR_ERR(batch);
			pr_err("%s: Unable to create batch for %s, err=%d\n",
			       __func__, engine->name, err);
			जाओ out_मुक्त;
		पूर्ण

		i915_vma_lock(batch);
		request[idx] = पूर्णांकel_engine_create_kernel_request(engine);
		अगर (IS_ERR(request[idx])) अणु
			err = PTR_ERR(request[idx]);
			pr_err("%s: Request allocation failed for %s with err=%d\n",
			       __func__, engine->name, err);
			जाओ out_unlock;
		पूर्ण

		अगर (prev) अणु
			err = i915_request_aरुको_dma_fence(request[idx],
							   &prev->fence);
			अगर (err) अणु
				i915_request_add(request[idx]);
				pr_err("%s: Request await failed for %s with err=%d\n",
				       __func__, engine->name, err);
				जाओ out_unlock;
			पूर्ण
		पूर्ण

		err = i915_request_aरुको_object(request[idx],
						batch->obj, false);
		अगर (err == 0)
			err = i915_vma_move_to_active(batch, request[idx], 0);
		GEM_BUG_ON(err);

		err = engine->emit_bb_start(request[idx],
					    batch->node.start,
					    batch->node.size,
					    0);
		GEM_BUG_ON(err);
		request[idx]->batch = batch;

		i915_request_get(request[idx]);
		i915_request_add(request[idx]);

		prev = request[idx];
		idx++;

out_unlock:
		i915_vma_unlock(batch);
		अगर (err)
			जाओ out_request;
	पूर्ण

	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		दीर्घ समयout;

		अगर (i915_request_completed(request[idx])) अणु
			pr_err("%s(%s): request completed too early!\n",
			       __func__, engine->name);
			err = -EINVAL;
			जाओ out_request;
		पूर्ण

		err = recursive_batch_resolve(request[idx]->batch);
		अगर (err) अणु
			pr_err("%s: failed to resolve batch, err=%d\n",
			       __func__, err);
			जाओ out_request;
		पूर्ण

		समयout = i915_request_रुको(request[idx], 0,
					    MAX_SCHEDULE_TIMEOUT);
		अगर (समयout < 0) अणु
			err = समयout;
			pr_err("%s: error waiting for request on %s, err=%d\n",
			       __func__, engine->name, err);
			जाओ out_request;
		पूर्ण

		GEM_BUG_ON(!i915_request_completed(request[idx]));
		idx++;
	पूर्ण

	err = igt_live_test_end(&t);

out_request:
	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		u32 *cmd;

		अगर (!request[idx])
			अवरोध;

		cmd = i915_gem_object_pin_map_unlocked(request[idx]->batch->obj,
						       I915_MAP_WC);
		अगर (!IS_ERR(cmd)) अणु
			*cmd = MI_BATCH_BUFFER_END;

			__i915_gem_object_flush_map(request[idx]->batch->obj,
						    0, माप(*cmd));
			i915_gem_object_unpin_map(request[idx]->batch->obj);

			पूर्णांकel_gt_chipset_flush(engine->gt);
		पूर्ण

		i915_vma_put(request[idx]->batch);
		i915_request_put(request[idx]);
		idx++;
	पूर्ण
out_मुक्त:
	kमुक्त(request);
	वापस err;
पूर्ण

अटल पूर्णांक __live_parallel_engine1(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = arg;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;
	पूर्णांक err = 0;

	count = 0;
	पूर्णांकel_engine_pm_get(engine);
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(engine->kernel_context);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_get(rq);
		i915_request_add(rq);

		err = 0;
		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
			err = -ETIME;
		i915_request_put(rq);
		अगर (err)
			अवरोध;

		count++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	पूर्णांकel_engine_pm_put(engine);

	pr_info("%s: %lu request + sync\n", engine->name, count);
	वापस err;
पूर्ण

अटल पूर्णांक __live_parallel_engineN(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = arg;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;
	पूर्णांक err = 0;

	count = 0;
	पूर्णांकel_engine_pm_get(engine);
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(engine->kernel_context);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_add(rq);
		count++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	पूर्णांकel_engine_pm_put(engine);

	pr_info("%s: %lu requests\n", engine->name, count);
	वापस err;
पूर्ण

अटल bool wake_all(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (atomic_dec_and_test(&i915->selftest.counter)) अणु
		wake_up_var(&i915->selftest.counter);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक रुको_क्रम_all(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (wake_all(i915))
		वापस 0;

	अगर (रुको_var_event_समयout(&i915->selftest.counter,
				   !atomic_पढ़ो(&i915->selftest.counter),
				   i915_selftest.समयout_jअगरfies))
		वापस 0;

	वापस -ETIME;
पूर्ण

अटल पूर्णांक __live_parallel_spin(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = arg;
	काष्ठा igt_spinner spin;
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;

	/*
	 * Create a spinner running क्रम eternity on each engine. If a second
	 * spinner is incorrectly placed on the same engine, it will not be
	 * able to start in समय.
	 */

	अगर (igt_spinner_init(&spin, engine->gt)) अणु
		wake_all(engine->i915);
		वापस -ENOMEM;
	पूर्ण

	पूर्णांकel_engine_pm_get(engine);
	rq = igt_spinner_create_request(&spin,
					engine->kernel_context,
					MI_NOOP); /* no preemption */
	पूर्णांकel_engine_pm_put(engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		अगर (err == -ENODEV)
			err = 0;
		wake_all(engine->i915);
		जाओ out_spin;
	पूर्ण

	i915_request_get(rq);
	i915_request_add(rq);
	अगर (igt_रुको_क्रम_spinner(&spin, rq)) अणु
		/* Occupy this engine क्रम the whole test */
		err = रुको_क्रम_all(engine->i915);
	पूर्ण अन्यथा अणु
		pr_err("Failed to start spinner on %s\n", engine->name);
		err = -EINVAL;
	पूर्ण
	igt_spinner_end(&spin);

	अगर (err == 0 && i915_request_रुको(rq, 0, HZ / 5) < 0)
		err = -EIO;
	i915_request_put(rq);

out_spin:
	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_parallel_engines(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अटल पूर्णांक (* स्थिर func[])(व्योम *arg) = अणु
		__live_parallel_engine1,
		__live_parallel_engineN,
		__live_parallel_spin,
		शून्य,
	पूर्ण;
	स्थिर अचिन्हित पूर्णांक nengines = num_uabi_engines(i915);
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक (* स्थिर *fn)(व्योम *arg);
	काष्ठा task_काष्ठा **tsk;
	पूर्णांक err = 0;

	/*
	 * Check we can submit requests to all engines concurrently. This
	 * tests that we load up the प्रणाली maximally.
	 */

	tsk = kसुस्मृति(nengines, माप(*tsk), GFP_KERNEL);
	अगर (!tsk)
		वापस -ENOMEM;

	क्रम (fn = func; !err && *fn; fn++) अणु
		अक्षर name[KSYM_NAME_LEN];
		काष्ठा igt_live_test t;
		अचिन्हित पूर्णांक idx;

		snम_लिखो(name, माप(name), "%ps", *fn);
		err = igt_live_test_begin(&t, i915, __func__, name);
		अगर (err)
			अवरोध;

		atomic_set(&i915->selftest.counter, nengines);

		idx = 0;
		क्रम_each_uabi_engine(engine, i915) अणु
			tsk[idx] = kthपढ़ो_run(*fn, engine,
					       "igt/parallel:%s",
					       engine->name);
			अगर (IS_ERR(tsk[idx])) अणु
				err = PTR_ERR(tsk[idx]);
				अवरोध;
			पूर्ण
			get_task_काष्ठा(tsk[idx++]);
		पूर्ण

		yield(); /* start all thपढ़ोs beक्रमe we kthपढ़ो_stop() */

		idx = 0;
		क्रम_each_uabi_engine(engine, i915) अणु
			पूर्णांक status;

			अगर (IS_ERR(tsk[idx]))
				अवरोध;

			status = kthपढ़ो_stop(tsk[idx]);
			अगर (status && !err)
				err = status;

			put_task_काष्ठा(tsk[idx++]);
		पूर्ण

		अगर (igt_live_test_end(&t))
			err = -EIO;
	पूर्ण

	kमुक्त(tsk);
	वापस err;
पूर्ण

अटल पूर्णांक
max_batches(काष्ठा i915_gem_context *ctx, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक ret;

	/*
	 * Beक्रमe execlists, all contexts share the same ringbuffer. With
	 * execlists, each context/engine has a separate ringbuffer and
	 * क्रम the purposes of this test, inexhaustible.
	 *
	 * For the global ringbuffer though, we have to be very careful
	 * that we करो not wrap जबतक preventing the execution of requests
	 * with a unसंकेतed fence.
	 */
	अगर (HAS_EXECLISTS(ctx->i915))
		वापस पूर्णांक_उच्च;

	rq = igt_request_alloc(ctx, engine);
	अगर (IS_ERR(rq)) अणु
		ret = PTR_ERR(rq);
	पूर्ण अन्यथा अणु
		पूर्णांक sz;

		ret = rq->ring->size - rq->reserved_space;
		i915_request_add(rq);

		sz = rq->ring->emit - rq->head;
		अगर (sz < 0)
			sz += rq->ring->size;
		ret /= sz;
		ret /= 2; /* leave half spare, in हाल of emergency! */
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक live_bपढ़ोcrumbs_smoketest(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	स्थिर अचिन्हित पूर्णांक nengines = num_uabi_engines(i915);
	स्थिर अचिन्हित पूर्णांक ncpus = num_online_cpus();
	अचिन्हित दीर्घ num_रुकोs, num_fences;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा task_काष्ठा **thपढ़ोs;
	काष्ठा igt_live_test live;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा smoketest *smoke;
	अचिन्हित पूर्णांक n, idx;
	काष्ठा file *file;
	पूर्णांक ret = 0;

	/*
	 * Smoketest our bपढ़ोcrumb/संकेत handling क्रम requests across multiple
	 * thपढ़ोs. A very simple test to only catch the most egregious of bugs.
	 * See __igt_bपढ़ोcrumbs_smoketest();
	 *
	 * On real hardware this समय.
	 */

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	file = mock_file(i915);
	अगर (IS_ERR(file)) अणु
		ret = PTR_ERR(file);
		जाओ out_rpm;
	पूर्ण

	smoke = kसुस्मृति(nengines, माप(*smoke), GFP_KERNEL);
	अगर (!smoke) अणु
		ret = -ENOMEM;
		जाओ out_file;
	पूर्ण

	thपढ़ोs = kसुस्मृति(ncpus * nengines, माप(*thपढ़ोs), GFP_KERNEL);
	अगर (!thपढ़ोs) अणु
		ret = -ENOMEM;
		जाओ out_smoke;
	पूर्ण

	smoke[0].request_alloc = __live_request_alloc;
	smoke[0].ncontexts = 64;
	smoke[0].contexts = kसुस्मृति(smoke[0].ncontexts,
				    माप(*smoke[0].contexts),
				    GFP_KERNEL);
	अगर (!smoke[0].contexts) अणु
		ret = -ENOMEM;
		जाओ out_thपढ़ोs;
	पूर्ण

	क्रम (n = 0; n < smoke[0].ncontexts; n++) अणु
		smoke[0].contexts[n] = live_context(i915, file);
		अगर (IS_ERR(smoke[0].contexts[n])) अणु
			ret = PTR_ERR(smoke[0].contexts[n]);
			जाओ out_contexts;
		पूर्ण
	पूर्ण

	ret = igt_live_test_begin(&live, i915, __func__, "");
	अगर (ret)
		जाओ out_contexts;

	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		smoke[idx] = smoke[0];
		smoke[idx].engine = engine;
		smoke[idx].max_batch =
			max_batches(smoke[0].contexts[0], engine);
		अगर (smoke[idx].max_batch < 0) अणु
			ret = smoke[idx].max_batch;
			जाओ out_flush;
		पूर्ण
		/* One ring पूर्णांकerleaved between requests from all cpus */
		smoke[idx].max_batch /= num_online_cpus() + 1;
		pr_debug("Limiting batches to %d requests on %s\n",
			 smoke[idx].max_batch, engine->name);

		क्रम (n = 0; n < ncpus; n++) अणु
			काष्ठा task_काष्ठा *tsk;

			tsk = kthपढ़ो_run(__igt_bपढ़ोcrumbs_smoketest,
					  &smoke[idx], "igt/%d.%d", idx, n);
			अगर (IS_ERR(tsk)) अणु
				ret = PTR_ERR(tsk);
				जाओ out_flush;
			पूर्ण

			get_task_काष्ठा(tsk);
			thपढ़ोs[idx * ncpus + n] = tsk;
		पूर्ण

		idx++;
	पूर्ण

	yield(); /* start all thपढ़ोs beक्रमe we begin */
	msleep(jअगरfies_to_msecs(i915_selftest.समयout_jअगरfies));

out_flush:
	idx = 0;
	num_रुकोs = 0;
	num_fences = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		क्रम (n = 0; n < ncpus; n++) अणु
			काष्ठा task_काष्ठा *tsk = thपढ़ोs[idx * ncpus + n];
			पूर्णांक err;

			अगर (!tsk)
				जारी;

			err = kthपढ़ो_stop(tsk);
			अगर (err < 0 && !ret)
				ret = err;

			put_task_काष्ठा(tsk);
		पूर्ण

		num_रुकोs += atomic_दीर्घ_पढ़ो(&smoke[idx].num_रुकोs);
		num_fences += atomic_दीर्घ_पढ़ो(&smoke[idx].num_fences);
		idx++;
	पूर्ण
	pr_info("Completed %lu waits for %lu fences across %d engines and %d cpus\n",
		num_रुकोs, num_fences, idx, ncpus);

	ret = igt_live_test_end(&live) ?: ret;
out_contexts:
	kमुक्त(smoke[0].contexts);
out_thपढ़ोs:
	kमुक्त(thपढ़ोs);
out_smoke:
	kमुक्त(smoke);
out_file:
	fput(file);
out_rpm:
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);

	वापस ret;
पूर्ण

पूर्णांक i915_request_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_nop_request),
		SUBTEST(live_all_engines),
		SUBTEST(live_sequential_engines),
		SUBTEST(live_parallel_engines),
		SUBTEST(live_empty_request),
		SUBTEST(live_cancel_request),
		SUBTEST(live_bपढ़ोcrumbs_smoketest),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_subtests(tests, i915);
पूर्ण

अटल पूर्णांक चयन_to_kernel_sync(काष्ठा पूर्णांकel_context *ce, पूर्णांक err)
अणु
	काष्ठा i915_request *rq;
	काष्ठा dma_fence *fence;

	rq = पूर्णांकel_engine_create_kernel_request(ce->engine);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	fence = i915_active_fence_get(&ce->समयline->last_request);
	अगर (fence) अणु
		i915_request_aरुको_dma_fence(rq, fence);
		dma_fence_put(fence);
	पूर्ण

	rq = i915_request_get(rq);
	i915_request_add(rq);
	अगर (i915_request_रुको(rq, 0, HZ / 2) < 0 && !err)
		err = -ETIME;
	i915_request_put(rq);

	जबतक (!err && !पूर्णांकel_engine_is_idle(ce->engine))
		पूर्णांकel_engine_flush_submission(ce->engine);

	वापस err;
पूर्ण

काष्ठा perf_stats अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित दीर्घ count;
	kसमय_प्रकार समय;
	kसमय_प्रकार busy;
	u64 runसमय;
पूर्ण;

काष्ठा perf_series अणु
	काष्ठा drm_i915_निजी *i915;
	अचिन्हित पूर्णांक nengines;
	काष्ठा पूर्णांकel_context *ce[];
पूर्ण;

अटल पूर्णांक cmp_u32(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर u32 *a = A, *b = B;

	वापस *a - *b;
पूर्ण

अटल u32 trअगरilter(u32 *a)
अणु
	u64 sum;

#घोषणा TF_COUNT 5
	sort(a, TF_COUNT, माप(*a), cmp_u32, शून्य);

	sum = mul_u32_u32(a[2], 2);
	sum += a[1];
	sum += a[3];

	GEM_BUG_ON(sum > U32_MAX);
	वापस sum;
#घोषणा TF_BIAS 2
पूर्ण

अटल u64 cycles_to_ns(काष्ठा पूर्णांकel_engine_cs *engine, u32 cycles)
अणु
	u64 ns = पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(engine->gt, cycles);

	वापस DIV_ROUND_CLOSEST(ns, 1 << TF_BIAS);
पूर्ण

अटल u32 *emit_बारtamp_store(u32 *cs, काष्ठा पूर्णांकel_context *ce, u32 offset)
अणु
	*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_reg_offset(RING_TIMESTAMP((ce->engine->mmio_base)));
	*cs++ = offset;
	*cs++ = 0;

	वापस cs;
पूर्ण

अटल u32 *emit_store_dw(u32 *cs, u32 offset, u32 value)
अणु
	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = value;

	वापस cs;
पूर्ण

अटल u32 *emit_semaphore_poll(u32 *cs, u32 mode, u32 value, u32 offset)
अणु
	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		mode;
	*cs++ = value;
	*cs++ = offset;
	*cs++ = 0;

	वापस cs;
पूर्ण

अटल u32 *emit_semaphore_poll_until(u32 *cs, u32 offset, u32 value)
अणु
	वापस emit_semaphore_poll(cs, MI_SEMAPHORE_SAD_EQ_SDD, value, offset);
पूर्ण

अटल व्योम semaphore_set(u32 *sema, u32 value)
अणु
	WRITE_ONCE(*sema, value);
	wmb(); /* flush the update to the cache, and beyond */
पूर्ण

अटल u32 *hwsp_scratch(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस स_रखो32(ce->engine->status_page.addr + 1000, 0, 21);
पूर्ण

अटल u32 hwsp_offset(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *dw)
अणु
	वापस (i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(dw));
पूर्ण

अटल पूर्णांक measure_semaphore_response(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *sema = hwsp_scratch(ce);
	स्थिर u32 offset = hwsp_offset(ce, sema);
	u32 elapsed[TF_COUNT], cycles;
	काष्ठा i915_request *rq;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * Measure how many cycles it takes क्रम the HW to detect the change
	 * in a semaphore value.
	 *
	 *    A: पढ़ो CS_TIMESTAMP from CPU
	 *    poke semaphore
	 *    B: पढ़ो CS_TIMESTAMP on GPU
	 *
	 * Semaphore latency: B - A
	 */

	semaphore_set(sema, -1);

	rq = i915_request_create(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 4 + 12 * ARRAY_SIZE(elapsed));
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		err = PTR_ERR(cs);
		जाओ err;
	पूर्ण

	cs = emit_store_dw(cs, offset, 0);
	क्रम (i = 1; i <= ARRAY_SIZE(elapsed); i++) अणु
		cs = emit_semaphore_poll_until(cs, offset, i);
		cs = emit_बारtamp_store(cs, ce, offset + i * माप(u32));
		cs = emit_store_dw(cs, offset, 0);
	पूर्ण

	पूर्णांकel_ring_advance(rq, cs);
	i915_request_add(rq);

	अगर (रुको_क्रम(READ_ONCE(*sema) == 0, 50)) अणु
		err = -EIO;
		जाओ err;
	पूर्ण

	क्रम (i = 1; i <= ARRAY_SIZE(elapsed); i++) अणु
		preempt_disable();
		cycles = ENGINE_READ_FW(ce->engine, RING_TIMESTAMP);
		semaphore_set(sema, i);
		preempt_enable();

		अगर (रुको_क्रम(READ_ONCE(*sema) == 0, 50)) अणु
			err = -EIO;
			जाओ err;
		पूर्ण

		elapsed[i - 1] = sema[i] - cycles;
	पूर्ण

	cycles = trअगरilter(elapsed);
	pr_info("%s: semaphore response %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	वापस पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ);

err:
	पूर्णांकel_gt_set_wedged(ce->engine->gt);
	वापस err;
पूर्ण

अटल पूर्णांक measure_idle_dispatch(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *sema = hwsp_scratch(ce);
	स्थिर u32 offset = hwsp_offset(ce, sema);
	u32 elapsed[TF_COUNT], cycles;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * Measure how दीर्घ it takes क्रम us to submit a request जबतक the
	 * engine is idle, but is resting in our context.
	 *
	 *    A: पढ़ो CS_TIMESTAMP from CPU
	 *    submit request
	 *    B: पढ़ो CS_TIMESTAMP on GPU
	 *
	 * Submission latency: B - A
	 */

	क्रम (i = 0; i < ARRAY_SIZE(elapsed); i++) अणु
		काष्ठा i915_request *rq;

		err = पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ / 2);
		अगर (err)
			वापस err;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err;
		पूर्ण

		cs = पूर्णांकel_ring_begin(rq, 4);
		अगर (IS_ERR(cs)) अणु
			i915_request_add(rq);
			err = PTR_ERR(cs);
			जाओ err;
		पूर्ण

		cs = emit_बारtamp_store(cs, ce, offset + i * माप(u32));

		पूर्णांकel_ring_advance(rq, cs);

		preempt_disable();
		local_bh_disable();
		elapsed[i] = ENGINE_READ_FW(ce->engine, RING_TIMESTAMP);
		i915_request_add(rq);
		local_bh_enable();
		preempt_enable();
	पूर्ण

	err = पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ / 2);
	अगर (err)
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(elapsed); i++)
		elapsed[i] = sema[i] - elapsed[i];

	cycles = trअगरilter(elapsed);
	pr_info("%s: idle dispatch latency %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	वापस पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ);

err:
	पूर्णांकel_gt_set_wedged(ce->engine->gt);
	वापस err;
पूर्ण

अटल पूर्णांक measure_busy_dispatch(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *sema = hwsp_scratch(ce);
	स्थिर u32 offset = hwsp_offset(ce, sema);
	u32 elapsed[TF_COUNT + 1], cycles;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * Measure how दीर्घ it takes क्रम us to submit a request जबतक the
	 * engine is busy, polling on a semaphore in our context. With
	 * direct submission, this will include the cost of a lite restore.
	 *
	 *    A: पढ़ो CS_TIMESTAMP from CPU
	 *    submit request
	 *    B: पढ़ो CS_TIMESTAMP on GPU
	 *
	 * Submission latency: B - A
	 */

	क्रम (i = 1; i <= ARRAY_SIZE(elapsed); i++) अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err;
		पूर्ण

		cs = पूर्णांकel_ring_begin(rq, 12);
		अगर (IS_ERR(cs)) अणु
			i915_request_add(rq);
			err = PTR_ERR(cs);
			जाओ err;
		पूर्ण

		cs = emit_store_dw(cs, offset + i * माप(u32), -1);
		cs = emit_semaphore_poll_until(cs, offset, i);
		cs = emit_बारtamp_store(cs, ce, offset + i * माप(u32));

		पूर्णांकel_ring_advance(rq, cs);

		अगर (i > 1 && रुको_क्रम(READ_ONCE(sema[i - 1]), 500)) अणु
			err = -EIO;
			जाओ err;
		पूर्ण

		preempt_disable();
		local_bh_disable();
		elapsed[i - 1] = ENGINE_READ_FW(ce->engine, RING_TIMESTAMP);
		i915_request_add(rq);
		local_bh_enable();
		semaphore_set(sema, i - 1);
		preempt_enable();
	पूर्ण

	रुको_क्रम(READ_ONCE(sema[i - 1]), 500);
	semaphore_set(sema, i - 1);

	क्रम (i = 1; i <= TF_COUNT; i++) अणु
		GEM_BUG_ON(sema[i] == -1);
		elapsed[i - 1] = sema[i] - elapsed[i];
	पूर्ण

	cycles = trअगरilter(elapsed);
	pr_info("%s: busy dispatch latency %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	वापस पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ);

err:
	पूर्णांकel_gt_set_wedged(ce->engine->gt);
	वापस err;
पूर्ण

अटल पूर्णांक plug(काष्ठा पूर्णांकel_engine_cs *engine, u32 *sema, u32 mode, पूर्णांक value)
अणु
	स्थिर u32 offset =
		i915_ggtt_offset(engine->status_page.vma) +
		offset_in_page(sema);
	काष्ठा i915_request *rq;
	u32 *cs;

	rq = i915_request_create(engine->kernel_context);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	cs = emit_semaphore_poll(cs, mode, value, offset);

	पूर्णांकel_ring_advance(rq, cs);
	i915_request_add(rq);

	वापस 0;
पूर्ण

अटल पूर्णांक measure_पूर्णांकer_request(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *sema = hwsp_scratch(ce);
	स्थिर u32 offset = hwsp_offset(ce, sema);
	u32 elapsed[TF_COUNT + 1], cycles;
	काष्ठा i915_sw_fence *submit;
	पूर्णांक i, err;

	/*
	 * Measure how दीर्घ it takes to advance from one request पूर्णांकo the
	 * next. Between each request we flush the GPU caches to memory,
	 * update the bपढ़ोcrumbs, and then invalidate those caches.
	 * We queue up all the requests to be submitted in one batch so
	 * it should be one set of contiguous measurements.
	 *
	 *    A: पढ़ो CS_TIMESTAMP on GPU
	 *    advance request
	 *    B: पढ़ो CS_TIMESTAMP on GPU
	 *
	 * Request latency: B - A
	 */

	err = plug(ce->engine, sema, MI_SEMAPHORE_SAD_NEQ_SDD, 0);
	अगर (err)
		वापस err;

	submit = heap_fence_create(GFP_KERNEL);
	अगर (!submit) अणु
		semaphore_set(sema, 1);
		वापस -ENOMEM;
	पूर्ण

	पूर्णांकel_engine_flush_submission(ce->engine);
	क्रम (i = 1; i <= ARRAY_SIZE(elapsed); i++) अणु
		काष्ठा i915_request *rq;
		u32 *cs;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_submit;
		पूर्ण

		err = i915_sw_fence_aरुको_sw_fence_gfp(&rq->submit,
						       submit,
						       GFP_KERNEL);
		अगर (err < 0) अणु
			i915_request_add(rq);
			जाओ err_submit;
		पूर्ण

		cs = पूर्णांकel_ring_begin(rq, 4);
		अगर (IS_ERR(cs)) अणु
			i915_request_add(rq);
			err = PTR_ERR(cs);
			जाओ err_submit;
		पूर्ण

		cs = emit_बारtamp_store(cs, ce, offset + i * माप(u32));

		पूर्णांकel_ring_advance(rq, cs);
		i915_request_add(rq);
	पूर्ण
	i915_sw_fence_commit(submit);
	पूर्णांकel_engine_flush_submission(ce->engine);
	heap_fence_put(submit);

	semaphore_set(sema, 1);
	err = पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ / 2);
	अगर (err)
		जाओ err;

	क्रम (i = 1; i <= TF_COUNT; i++)
		elapsed[i - 1] = sema[i + 1] - sema[i];

	cycles = trअगरilter(elapsed);
	pr_info("%s: inter-request latency %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	वापस पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ);

err_submit:
	i915_sw_fence_commit(submit);
	heap_fence_put(submit);
	semaphore_set(sema, 1);
err:
	पूर्णांकel_gt_set_wedged(ce->engine->gt);
	वापस err;
पूर्ण

अटल पूर्णांक measure_context_चयन(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *sema = hwsp_scratch(ce);
	स्थिर u32 offset = hwsp_offset(ce, sema);
	काष्ठा i915_request *fence = शून्य;
	u32 elapsed[TF_COUNT + 1], cycles;
	पूर्णांक i, j, err;
	u32 *cs;

	/*
	 * Measure how दीर्घ it takes to advance from one request in one
	 * context to a request in another context. This allows us to
	 * measure how दीर्घ the context save/restore take, aदीर्घ with all
	 * the पूर्णांकer-context setup we require.
	 *
	 *    A: पढ़ो CS_TIMESTAMP on GPU
	 *    चयन context
	 *    B: पढ़ो CS_TIMESTAMP on GPU
	 *
	 * Context चयन latency: B - A
	 */

	err = plug(ce->engine, sema, MI_SEMAPHORE_SAD_NEQ_SDD, 0);
	अगर (err)
		वापस err;

	क्रम (i = 1; i <= ARRAY_SIZE(elapsed); i++) अणु
		काष्ठा पूर्णांकel_context *arr[] = अणु
			ce, ce->engine->kernel_context
		पूर्ण;
		u32 addr = offset + ARRAY_SIZE(arr) * i * माप(u32);

		क्रम (j = 0; j < ARRAY_SIZE(arr); j++) अणु
			काष्ठा i915_request *rq;

			rq = i915_request_create(arr[j]);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				जाओ err_fence;
			पूर्ण

			अगर (fence) अणु
				err = i915_request_aरुको_dma_fence(rq,
								   &fence->fence);
				अगर (err) अणु
					i915_request_add(rq);
					जाओ err_fence;
				पूर्ण
			पूर्ण

			cs = पूर्णांकel_ring_begin(rq, 4);
			अगर (IS_ERR(cs)) अणु
				i915_request_add(rq);
				err = PTR_ERR(cs);
				जाओ err_fence;
			पूर्ण

			cs = emit_बारtamp_store(cs, ce, addr);
			addr += माप(u32);

			पूर्णांकel_ring_advance(rq, cs);

			i915_request_put(fence);
			fence = i915_request_get(rq);

			i915_request_add(rq);
		पूर्ण
	पूर्ण
	i915_request_put(fence);
	पूर्णांकel_engine_flush_submission(ce->engine);

	semaphore_set(sema, 1);
	err = पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ / 2);
	अगर (err)
		जाओ err;

	क्रम (i = 1; i <= TF_COUNT; i++)
		elapsed[i - 1] = sema[2 * i + 2] - sema[2 * i + 1];

	cycles = trअगरilter(elapsed);
	pr_info("%s: context switch latency %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	वापस पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ);

err_fence:
	i915_request_put(fence);
	semaphore_set(sema, 1);
err:
	पूर्णांकel_gt_set_wedged(ce->engine->gt);
	वापस err;
पूर्ण

अटल पूर्णांक measure_preemption(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *sema = hwsp_scratch(ce);
	स्थिर u32 offset = hwsp_offset(ce, sema);
	u32 elapsed[TF_COUNT], cycles;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * We measure two latencies जबतक triggering preemption. The first
	 * latency is how दीर्घ it takes क्रम us to submit a preempting request.
	 * The second latency is how it takes क्रम us to वापस from the
	 * preemption back to the original context.
	 *
	 *    A: पढ़ो CS_TIMESTAMP from CPU
	 *    submit preemption
	 *    B: पढ़ो CS_TIMESTAMP on GPU (in preempting context)
	 *    context चयन
	 *    C: पढ़ो CS_TIMESTAMP on GPU (in original context)
	 *
	 * Preemption dispatch latency: B - A
	 * Preemption चयन latency: C - B
	 */

	अगर (!पूर्णांकel_engine_has_preemption(ce->engine))
		वापस 0;

	क्रम (i = 1; i <= ARRAY_SIZE(elapsed); i++) अणु
		u32 addr = offset + 2 * i * माप(u32);
		काष्ठा i915_request *rq;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err;
		पूर्ण

		cs = पूर्णांकel_ring_begin(rq, 12);
		अगर (IS_ERR(cs)) अणु
			i915_request_add(rq);
			err = PTR_ERR(cs);
			जाओ err;
		पूर्ण

		cs = emit_store_dw(cs, addr, -1);
		cs = emit_semaphore_poll_until(cs, offset, i);
		cs = emit_बारtamp_store(cs, ce, addr + माप(u32));

		पूर्णांकel_ring_advance(rq, cs);
		i915_request_add(rq);

		अगर (रुको_क्रम(READ_ONCE(sema[2 * i]) == -1, 500)) अणु
			err = -EIO;
			जाओ err;
		पूर्ण

		rq = i915_request_create(ce->engine->kernel_context);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err;
		पूर्ण

		cs = पूर्णांकel_ring_begin(rq, 8);
		अगर (IS_ERR(cs)) अणु
			i915_request_add(rq);
			err = PTR_ERR(cs);
			जाओ err;
		पूर्ण

		cs = emit_बारtamp_store(cs, ce, addr);
		cs = emit_store_dw(cs, offset, i);

		पूर्णांकel_ring_advance(rq, cs);
		rq->sched.attr.priority = I915_PRIORITY_BARRIER;

		elapsed[i - 1] = ENGINE_READ_FW(ce->engine, RING_TIMESTAMP);
		i915_request_add(rq);
	पूर्ण

	अगर (रुको_क्रम(READ_ONCE(sema[2 * i - 2]) != -1, 500)) अणु
		err = -EIO;
		जाओ err;
	पूर्ण

	क्रम (i = 1; i <= TF_COUNT; i++)
		elapsed[i - 1] = sema[2 * i + 0] - elapsed[i - 1];

	cycles = trअगरilter(elapsed);
	pr_info("%s: preemption dispatch latency %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	क्रम (i = 1; i <= TF_COUNT; i++)
		elapsed[i - 1] = sema[2 * i + 1] - sema[2 * i + 0];

	cycles = trअगरilter(elapsed);
	pr_info("%s: preemption switch latency %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	वापस पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ);

err:
	पूर्णांकel_gt_set_wedged(ce->engine->gt);
	वापस err;
पूर्ण

काष्ठा संकेत_cb अणु
	काष्ठा dma_fence_cb base;
	bool seen;
पूर्ण;

अटल व्योम संकेत_cb(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा संकेत_cb *s = container_of(cb, typeof(*s), base);

	smp_store_mb(s->seen, true); /* be safe, be strong */
पूर्ण

अटल पूर्णांक measure_completion(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *sema = hwsp_scratch(ce);
	स्थिर u32 offset = hwsp_offset(ce, sema);
	u32 elapsed[TF_COUNT], cycles;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * Measure how दीर्घ it takes क्रम the संकेत (पूर्णांकerrupt) to be
	 * sent from the GPU to be processed by the CPU.
	 *
	 *    A: पढ़ो CS_TIMESTAMP on GPU
	 *    संकेत
	 *    B: पढ़ो CS_TIMESTAMP from CPU
	 *
	 * Completion latency: B - A
	 */

	क्रम (i = 1; i <= ARRAY_SIZE(elapsed); i++) अणु
		काष्ठा संकेत_cb cb = अणु .seen = false पूर्ण;
		काष्ठा i915_request *rq;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err;
		पूर्ण

		cs = पूर्णांकel_ring_begin(rq, 12);
		अगर (IS_ERR(cs)) अणु
			i915_request_add(rq);
			err = PTR_ERR(cs);
			जाओ err;
		पूर्ण

		cs = emit_store_dw(cs, offset + i * माप(u32), -1);
		cs = emit_semaphore_poll_until(cs, offset, i);
		cs = emit_बारtamp_store(cs, ce, offset + i * माप(u32));

		पूर्णांकel_ring_advance(rq, cs);

		dma_fence_add_callback(&rq->fence, &cb.base, संकेत_cb);
		i915_request_add(rq);

		पूर्णांकel_engine_flush_submission(ce->engine);
		अगर (रुको_क्रम(READ_ONCE(sema[i]) == -1, 50)) अणु
			err = -EIO;
			जाओ err;
		पूर्ण

		preempt_disable();
		semaphore_set(sema, i);
		जबतक (!READ_ONCE(cb.seen))
			cpu_relax();

		elapsed[i - 1] = ENGINE_READ_FW(ce->engine, RING_TIMESTAMP);
		preempt_enable();
	पूर्ण

	err = पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ / 2);
	अगर (err)
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(elapsed); i++) अणु
		GEM_BUG_ON(sema[i + 1] == -1);
		elapsed[i] = elapsed[i] - sema[i + 1];
	पूर्ण

	cycles = trअगरilter(elapsed);
	pr_info("%s: completion latency %d cycles, %lluns\n",
		ce->engine->name, cycles >> TF_BIAS,
		cycles_to_ns(ce->engine, cycles));

	वापस पूर्णांकel_gt_रुको_क्रम_idle(ce->engine->gt, HZ);

err:
	पूर्णांकel_gt_set_wedged(ce->engine->gt);
	वापस err;
पूर्ण

अटल व्योम rps_pin(काष्ठा पूर्णांकel_gt *gt)
अणु
	/* Pin the frequency to max */
	atomic_inc(&gt->rps.num_रुकोers);
	पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);

	mutex_lock(&gt->rps.lock);
	पूर्णांकel_rps_set(&gt->rps, gt->rps.max_freq);
	mutex_unlock(&gt->rps.lock);
पूर्ण

अटल व्योम rps_unpin(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);
	atomic_dec(&gt->rps.num_रुकोers);
पूर्ण

अटल पूर्णांक perf_request_latency(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा pm_qos_request qos;
	पूर्णांक err = 0;

	अगर (INTEL_GEN(i915) < 8) /* per-engine CS बारtamp, semaphores */
		वापस 0;

	cpu_latency_qos_add_request(&qos, 0); /* disable cstates */

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा पूर्णांकel_context *ce;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out;
		पूर्ण

		err = पूर्णांकel_context_pin(ce);
		अगर (err) अणु
			पूर्णांकel_context_put(ce);
			जाओ out;
		पूर्ण

		st_engine_heartbeat_disable(engine);
		rps_pin(engine->gt);

		अगर (err == 0)
			err = measure_semaphore_response(ce);
		अगर (err == 0)
			err = measure_idle_dispatch(ce);
		अगर (err == 0)
			err = measure_busy_dispatch(ce);
		अगर (err == 0)
			err = measure_पूर्णांकer_request(ce);
		अगर (err == 0)
			err = measure_context_चयन(ce);
		अगर (err == 0)
			err = measure_preemption(ce);
		अगर (err == 0)
			err = measure_completion(ce);

		rps_unpin(engine->gt);
		st_engine_heartbeat_enable(engine);

		पूर्णांकel_context_unpin(ce);
		पूर्णांकel_context_put(ce);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	अगर (igt_flush_test(i915))
		err = -EIO;

	cpu_latency_qos_हटाओ_request(&qos);
	वापस err;
पूर्ण

अटल पूर्णांक s_sync0(व्योम *arg)
अणु
	काष्ठा perf_series *ps = arg;
	IGT_TIMEOUT(end_समय);
	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक err = 0;

	GEM_BUG_ON(!ps->nengines);
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(ps->ce[idx]);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_get(rq);
		i915_request_add(rq);

		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
			err = -ETIME;
		i915_request_put(rq);
		अगर (err)
			अवरोध;

		अगर (++idx == ps->nengines)
			idx = 0;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

	वापस err;
पूर्ण

अटल पूर्णांक s_sync1(व्योम *arg)
अणु
	काष्ठा perf_series *ps = arg;
	काष्ठा i915_request *prev = शून्य;
	IGT_TIMEOUT(end_समय);
	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक err = 0;

	GEM_BUG_ON(!ps->nengines);
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(ps->ce[idx]);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_get(rq);
		i915_request_add(rq);

		अगर (prev && i915_request_रुको(prev, 0, HZ / 5) < 0)
			err = -ETIME;
		i915_request_put(prev);
		prev = rq;
		अगर (err)
			अवरोध;

		अगर (++idx == ps->nengines)
			idx = 0;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	i915_request_put(prev);

	वापस err;
पूर्ण

अटल पूर्णांक s_many(व्योम *arg)
अणु
	काष्ठा perf_series *ps = arg;
	IGT_TIMEOUT(end_समय);
	अचिन्हित पूर्णांक idx = 0;

	GEM_BUG_ON(!ps->nengines);
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(ps->ce[idx]);
		अगर (IS_ERR(rq))
			वापस PTR_ERR(rq);

		i915_request_add(rq);

		अगर (++idx == ps->nengines)
			idx = 0;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

	वापस 0;
पूर्ण

अटल पूर्णांक perf_series_engines(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अटल पूर्णांक (* स्थिर func[])(व्योम *arg) = अणु
		s_sync0,
		s_sync1,
		s_many,
		शून्य,
	पूर्ण;
	स्थिर अचिन्हित पूर्णांक nengines = num_uabi_engines(i915);
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक (* स्थिर *fn)(व्योम *arg);
	काष्ठा pm_qos_request qos;
	काष्ठा perf_stats *stats;
	काष्ठा perf_series *ps;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err = 0;

	stats = kसुस्मृति(nengines, माप(*stats), GFP_KERNEL);
	अगर (!stats)
		वापस -ENOMEM;

	ps = kzalloc(काष्ठा_size(ps, ce, nengines), GFP_KERNEL);
	अगर (!ps) अणु
		kमुक्त(stats);
		वापस -ENOMEM;
	पूर्ण

	cpu_latency_qos_add_request(&qos, 0); /* disable cstates */

	ps->i915 = i915;
	ps->nengines = nengines;

	idx = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा पूर्णांकel_context *ce;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out;
		पूर्ण

		err = पूर्णांकel_context_pin(ce);
		अगर (err) अणु
			पूर्णांकel_context_put(ce);
			जाओ out;
		पूर्ण

		ps->ce[idx++] = ce;
	पूर्ण
	GEM_BUG_ON(idx != ps->nengines);

	क्रम (fn = func; *fn && !err; fn++) अणु
		अक्षर name[KSYM_NAME_LEN];
		काष्ठा igt_live_test t;

		snम_लिखो(name, माप(name), "%ps", *fn);
		err = igt_live_test_begin(&t, i915, __func__, name);
		अगर (err)
			अवरोध;

		क्रम (idx = 0; idx < nengines; idx++) अणु
			काष्ठा perf_stats *p =
				स_रखो(&stats[idx], 0, माप(stats[idx]));
			काष्ठा पूर्णांकel_context *ce = ps->ce[idx];

			p->engine = ps->ce[idx]->engine;
			पूर्णांकel_engine_pm_get(p->engine);

			अगर (पूर्णांकel_engine_supports_stats(p->engine))
				p->busy = पूर्णांकel_engine_get_busy_समय(p->engine,
								     &p->समय) + 1;
			अन्यथा
				p->समय = kसमय_get();
			p->runसमय = -पूर्णांकel_context_get_total_runसमय_ns(ce);
		पूर्ण

		err = (*fn)(ps);
		अगर (igt_live_test_end(&t))
			err = -EIO;

		क्रम (idx = 0; idx < nengines; idx++) अणु
			काष्ठा perf_stats *p = &stats[idx];
			काष्ठा पूर्णांकel_context *ce = ps->ce[idx];
			पूर्णांक पूर्णांकeger, decimal;
			u64 busy, dt, now;

			अगर (p->busy)
				p->busy = kसमय_sub(पूर्णांकel_engine_get_busy_समय(p->engine,
									       &now),
						    p->busy - 1);
			अन्यथा
				now = kसमय_get();
			p->समय = kसमय_sub(now, p->समय);

			err = चयन_to_kernel_sync(ce, err);
			p->runसमय += पूर्णांकel_context_get_total_runसमय_ns(ce);
			पूर्णांकel_engine_pm_put(p->engine);

			busy = 100 * kसमय_प्रकारo_ns(p->busy);
			dt = kसमय_प्रकारo_ns(p->समय);
			अगर (dt) अणु
				पूर्णांकeger = भाग64_u64(busy, dt);
				busy -= पूर्णांकeger * dt;
				decimal = भाग64_u64(100 * busy, dt);
			पूर्ण अन्यथा अणु
				पूर्णांकeger = 0;
				decimal = 0;
			पूर्ण

			pr_info("%s %5s: { seqno:%d, busy:%d.%02d%%, runtime:%lldms, walltime:%lldms }\n",
				name, p->engine->name, ce->समयline->seqno,
				पूर्णांकeger, decimal,
				भाग_u64(p->runसमय, 1000 * 1000),
				भाग_u64(kसमय_प्रकारo_ns(p->समय), 1000 * 1000));
		पूर्ण
	पूर्ण

out:
	क्रम (idx = 0; idx < nengines; idx++) अणु
		अगर (IS_ERR_OR_शून्य(ps->ce[idx]))
			अवरोध;

		पूर्णांकel_context_unpin(ps->ce[idx]);
		पूर्णांकel_context_put(ps->ce[idx]);
	पूर्ण
	kमुक्त(ps);

	cpu_latency_qos_हटाओ_request(&qos);
	kमुक्त(stats);
	वापस err;
पूर्ण

अटल पूर्णांक p_sync0(व्योम *arg)
अणु
	काष्ठा perf_stats *p = arg;
	काष्ठा पूर्णांकel_engine_cs *engine = p->engine;
	काष्ठा पूर्णांकel_context *ce;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;
	bool busy;
	पूर्णांक err = 0;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	err = पूर्णांकel_context_pin(ce);
	अगर (err) अणु
		पूर्णांकel_context_put(ce);
		वापस err;
	पूर्ण

	अगर (पूर्णांकel_engine_supports_stats(engine)) अणु
		p->busy = पूर्णांकel_engine_get_busy_समय(engine, &p->समय);
		busy = true;
	पूर्ण अन्यथा अणु
		p->समय = kसमय_get();
		busy = false;
	पूर्ण

	count = 0;
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_get(rq);
		i915_request_add(rq);

		err = 0;
		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
			err = -ETIME;
		i915_request_put(rq);
		अगर (err)
			अवरोध;

		count++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

	अगर (busy) अणु
		kसमय_प्रकार now;

		p->busy = kसमय_sub(पूर्णांकel_engine_get_busy_समय(engine, &now),
				    p->busy);
		p->समय = kसमय_sub(now, p->समय);
	पूर्ण अन्यथा अणु
		p->समय = kसमय_sub(kसमय_get(), p->समय);
	पूर्ण

	err = चयन_to_kernel_sync(ce, err);
	p->runसमय = पूर्णांकel_context_get_total_runसमय_ns(ce);
	p->count = count;

	पूर्णांकel_context_unpin(ce);
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक p_sync1(व्योम *arg)
अणु
	काष्ठा perf_stats *p = arg;
	काष्ठा पूर्णांकel_engine_cs *engine = p->engine;
	काष्ठा i915_request *prev = शून्य;
	काष्ठा पूर्णांकel_context *ce;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;
	bool busy;
	पूर्णांक err = 0;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	err = पूर्णांकel_context_pin(ce);
	अगर (err) अणु
		पूर्णांकel_context_put(ce);
		वापस err;
	पूर्ण

	अगर (पूर्णांकel_engine_supports_stats(engine)) अणु
		p->busy = पूर्णांकel_engine_get_busy_समय(engine, &p->समय);
		busy = true;
	पूर्ण अन्यथा अणु
		p->समय = kसमय_get();
		busy = false;
	पूर्ण

	count = 0;
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_get(rq);
		i915_request_add(rq);

		err = 0;
		अगर (prev && i915_request_रुको(prev, 0, HZ / 5) < 0)
			err = -ETIME;
		i915_request_put(prev);
		prev = rq;
		अगर (err)
			अवरोध;

		count++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	i915_request_put(prev);

	अगर (busy) अणु
		kसमय_प्रकार now;

		p->busy = kसमय_sub(पूर्णांकel_engine_get_busy_समय(engine, &now),
				    p->busy);
		p->समय = kसमय_sub(now, p->समय);
	पूर्ण अन्यथा अणु
		p->समय = kसमय_sub(kसमय_get(), p->समय);
	पूर्ण

	err = चयन_to_kernel_sync(ce, err);
	p->runसमय = पूर्णांकel_context_get_total_runसमय_ns(ce);
	p->count = count;

	पूर्णांकel_context_unpin(ce);
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक p_many(व्योम *arg)
अणु
	काष्ठा perf_stats *p = arg;
	काष्ठा पूर्णांकel_engine_cs *engine = p->engine;
	काष्ठा पूर्णांकel_context *ce;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;
	पूर्णांक err = 0;
	bool busy;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	err = पूर्णांकel_context_pin(ce);
	अगर (err) अणु
		पूर्णांकel_context_put(ce);
		वापस err;
	पूर्ण

	अगर (पूर्णांकel_engine_supports_stats(engine)) अणु
		p->busy = पूर्णांकel_engine_get_busy_समय(engine, &p->समय);
		busy = true;
	पूर्ण अन्यथा अणु
		p->समय = kसमय_get();
		busy = false;
	पूर्ण

	count = 0;
	करो अणु
		काष्ठा i915_request *rq;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_add(rq);
		count++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

	अगर (busy) अणु
		kसमय_प्रकार now;

		p->busy = kसमय_sub(पूर्णांकel_engine_get_busy_समय(engine, &now),
				    p->busy);
		p->समय = kसमय_sub(now, p->समय);
	पूर्ण अन्यथा अणु
		p->समय = kसमय_sub(kसमय_get(), p->समय);
	पूर्ण

	err = चयन_to_kernel_sync(ce, err);
	p->runसमय = पूर्णांकel_context_get_total_runसमय_ns(ce);
	p->count = count;

	पूर्णांकel_context_unpin(ce);
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक perf_parallel_engines(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अटल पूर्णांक (* स्थिर func[])(व्योम *arg) = अणु
		p_sync0,
		p_sync1,
		p_many,
		शून्य,
	पूर्ण;
	स्थिर अचिन्हित पूर्णांक nengines = num_uabi_engines(i915);
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक (* स्थिर *fn)(व्योम *arg);
	काष्ठा pm_qos_request qos;
	काष्ठा अणु
		काष्ठा perf_stats p;
		काष्ठा task_काष्ठा *tsk;
	पूर्ण *engines;
	पूर्णांक err = 0;

	engines = kसुस्मृति(nengines, माप(*engines), GFP_KERNEL);
	अगर (!engines)
		वापस -ENOMEM;

	cpu_latency_qos_add_request(&qos, 0);

	क्रम (fn = func; *fn; fn++) अणु
		अक्षर name[KSYM_NAME_LEN];
		काष्ठा igt_live_test t;
		अचिन्हित पूर्णांक idx;

		snम_लिखो(name, माप(name), "%ps", *fn);
		err = igt_live_test_begin(&t, i915, __func__, name);
		अगर (err)
			अवरोध;

		atomic_set(&i915->selftest.counter, nengines);

		idx = 0;
		क्रम_each_uabi_engine(engine, i915) अणु
			पूर्णांकel_engine_pm_get(engine);

			स_रखो(&engines[idx].p, 0, माप(engines[idx].p));
			engines[idx].p.engine = engine;

			engines[idx].tsk = kthपढ़ो_run(*fn, &engines[idx].p,
						       "igt:%s", engine->name);
			अगर (IS_ERR(engines[idx].tsk)) अणु
				err = PTR_ERR(engines[idx].tsk);
				पूर्णांकel_engine_pm_put(engine);
				अवरोध;
			पूर्ण
			get_task_काष्ठा(engines[idx++].tsk);
		पूर्ण

		yield(); /* start all thपढ़ोs beक्रमe we kthपढ़ो_stop() */

		idx = 0;
		क्रम_each_uabi_engine(engine, i915) अणु
			पूर्णांक status;

			अगर (IS_ERR(engines[idx].tsk))
				अवरोध;

			status = kthपढ़ो_stop(engines[idx].tsk);
			अगर (status && !err)
				err = status;

			पूर्णांकel_engine_pm_put(engine);
			put_task_काष्ठा(engines[idx++].tsk);
		पूर्ण

		अगर (igt_live_test_end(&t))
			err = -EIO;
		अगर (err)
			अवरोध;

		idx = 0;
		क्रम_each_uabi_engine(engine, i915) अणु
			काष्ठा perf_stats *p = &engines[idx].p;
			u64 busy = 100 * kसमय_प्रकारo_ns(p->busy);
			u64 dt = kसमय_प्रकारo_ns(p->समय);
			पूर्णांक पूर्णांकeger, decimal;

			अगर (dt) अणु
				पूर्णांकeger = भाग64_u64(busy, dt);
				busy -= पूर्णांकeger * dt;
				decimal = भाग64_u64(100 * busy, dt);
			पूर्ण अन्यथा अणु
				पूर्णांकeger = 0;
				decimal = 0;
			पूर्ण

			GEM_BUG_ON(engine != p->engine);
			pr_info("%s %5s: { count:%lu, busy:%d.%02d%%, runtime:%lldms, walltime:%lldms }\n",
				name, engine->name, p->count, पूर्णांकeger, decimal,
				भाग_u64(p->runसमय, 1000 * 1000),
				भाग_u64(kसमय_प्रकारo_ns(p->समय), 1000 * 1000));
			idx++;
		पूर्ण
	पूर्ण

	cpu_latency_qos_हटाओ_request(&qos);
	kमुक्त(engines);
	वापस err;
पूर्ण

पूर्णांक i915_request_perf_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(perf_request_latency),
		SUBTEST(perf_series_engines),
		SUBTEST(perf_parallel_engines),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_subtests(tests, i915);
पूर्ण
