<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_engine_heartbeat.h"
#समावेश "gt/intel_reset.h"
#समावेश "gt/selftest_engine_heartbeat.h"

#समावेश "i915_selftest.h"
#समावेश "selftests/i915_random.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_live_test.h"
#समावेश "selftests/igt_spinner.h"
#समावेश "selftests/lib_sw_fence.h"

#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "gem/selftests/mock_context.h"

#घोषणा CS_GPR(engine, n) ((engine)->mmio_base + 0x600 + (n) * 4)
#घोषणा NUM_GPR 16
#घोषणा NUM_GPR_DW (NUM_GPR * 2) /* each GPR is 2 dwords */

अटल bool is_active(काष्ठा i915_request *rq)
अणु
	अगर (i915_request_is_active(rq))
		वापस true;

	अगर (i915_request_on_hold(rq))
		वापस true;

	अगर (i915_request_has_initial_bपढ़ोcrumb(rq) && i915_request_started(rq))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक रुको_क्रम_submit(काष्ठा पूर्णांकel_engine_cs *engine,
			   काष्ठा i915_request *rq,
			   अचिन्हित दीर्घ समयout)
अणु
	/* Ignore our own attempts to suppress excess tasklets */
	tasklet_hi_schedule(&engine->execlists.tasklet);

	समयout += jअगरfies;
	करो अणु
		bool करोne = समय_after(jअगरfies, समयout);

		अगर (i915_request_completed(rq)) /* that was quick! */
			वापस 0;

		/* Wait until the HW has acknowleged the submission (or err) */
		पूर्णांकel_engine_flush_submission(engine);
		अगर (!READ_ONCE(engine->execlists.pending[0]) && is_active(rq))
			वापस 0;

		अगर (करोne)
			वापस -ETIME;

		cond_resched();
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक रुको_क्रम_reset(काष्ठा पूर्णांकel_engine_cs *engine,
			  काष्ठा i915_request *rq,
			  अचिन्हित दीर्घ समयout)
अणु
	समयout += jअगरfies;

	करो अणु
		cond_resched();
		पूर्णांकel_engine_flush_submission(engine);

		अगर (READ_ONCE(engine->execlists.pending[0]))
			जारी;

		अगर (i915_request_completed(rq))
			अवरोध;

		अगर (READ_ONCE(rq->fence.error))
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	flush_scheduled_work();

	अगर (rq->fence.error != -EIO) अणु
		pr_err("%s: hanging request %llx:%lld not reset\n",
		       engine->name,
		       rq->fence.context,
		       rq->fence.seqno);
		वापस -EINVAL;
	पूर्ण

	/* Give the request a jअगरfie to complete after flushing the worker */
	अगर (i915_request_रुको(rq, 0,
			      max(0l, (दीर्घ)(समयout - jअगरfies)) + 1) < 0) अणु
		pr_err("%s: hanging request %llx:%lld did not complete\n",
		       engine->name,
		       rq->fence.context,
		       rq->fence.seqno);
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक live_sanitycheck(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	अगर (!HAS_LOGICAL_RING_CONTEXTS(gt->i915))
		वापस 0;

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा i915_request *rq;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			अवरोध;
		पूर्ण

		rq = igt_spinner_create_request(&spin, ce, MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out_ctx;
		पूर्ण

		i915_request_add(rq);
		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			GEM_TRACE("spinner failed to start\n");
			GEM_TRACE_DUMP();
			पूर्णांकel_gt_set_wedged(gt);
			err = -EIO;
			जाओ out_ctx;
		पूर्ण

		igt_spinner_end(&spin);
		अगर (igt_flush_test(gt->i915)) अणु
			err = -EIO;
			जाओ out_ctx;
		पूर्ण

out_ctx:
		पूर्णांकel_context_put(ce);
		अगर (err)
			अवरोध;
	पूर्ण

	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_unlite_restore(काष्ठा पूर्णांकel_gt *gt, पूर्णांक prio)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = -ENOMEM;

	/*
	 * Check that we can correctly context चयन between 2 instances
	 * on the same engine from the same parent context.
	 */

	अगर (igt_spinner_init(&spin, gt))
		वापस err;

	err = 0;
	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce[2] = अणुपूर्ण;
		काष्ठा i915_request *rq[2];
		काष्ठा igt_live_test t;
		पूर्णांक n;

		अगर (prio && !पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण
		st_engine_heartbeat_disable(engine);

		क्रम (n = 0; n < ARRAY_SIZE(ce); n++) अणु
			काष्ठा पूर्णांकel_context *पंचांगp;

			पंचांगp = पूर्णांकel_context_create(engine);
			अगर (IS_ERR(पंचांगp)) अणु
				err = PTR_ERR(पंचांगp);
				जाओ err_ce;
			पूर्ण

			err = पूर्णांकel_context_pin(पंचांगp);
			अगर (err) अणु
				पूर्णांकel_context_put(पंचांगp);
				जाओ err_ce;
			पूर्ण

			/*
			 * Setup the pair of contexts such that अगर we
			 * lite-restore using the RING_TAIL from ce[1] it
			 * will execute garbage from ce[0]->ring.
			 */
			स_रखो(पंचांगp->ring->vaddr,
			       POISON_INUSE, /* IPEHR: 0x5a5a5a5a [hung!] */
			       पंचांगp->ring->vma->size);

			ce[n] = पंचांगp;
		पूर्ण
		GEM_BUG_ON(!ce[1]->ring->size);
		पूर्णांकel_ring_reset(ce[1]->ring, ce[1]->ring->size / 2);
		lrc_update_regs(ce[1], engine, ce[1]->ring->head);

		rq[0] = igt_spinner_create_request(&spin, ce[0], MI_ARB_CHECK);
		अगर (IS_ERR(rq[0])) अणु
			err = PTR_ERR(rq[0]);
			जाओ err_ce;
		पूर्ण

		i915_request_get(rq[0]);
		i915_request_add(rq[0]);
		GEM_BUG_ON(rq[0]->postfix > ce[1]->ring->emit);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq[0])) अणु
			i915_request_put(rq[0]);
			जाओ err_ce;
		पूर्ण

		rq[1] = i915_request_create(ce[1]);
		अगर (IS_ERR(rq[1])) अणु
			err = PTR_ERR(rq[1]);
			i915_request_put(rq[0]);
			जाओ err_ce;
		पूर्ण

		अगर (!prio) अणु
			/*
			 * Ensure we करो the चयन to ce[1] on completion.
			 *
			 * rq[0] is alपढ़ोy submitted, so this should reduce
			 * to a no-op (a रुको on a request on the same engine
			 * uses the submit fence, not the completion fence),
			 * but it will install a dependency on rq[1] क्रम rq[0]
			 * that will prevent the pair being reordered by
			 * बारlicing.
			 */
			i915_request_aरुको_dma_fence(rq[1], &rq[0]->fence);
		पूर्ण

		i915_request_get(rq[1]);
		i915_request_add(rq[1]);
		GEM_BUG_ON(rq[1]->postfix <= rq[0]->postfix);
		i915_request_put(rq[0]);

		अगर (prio) अणु
			काष्ठा i915_sched_attr attr = अणु
				.priority = prio,
			पूर्ण;

			/* Alternatively preempt the spinner with ce[1] */
			engine->schedule(rq[1], &attr);
		पूर्ण

		/* And चयन back to ce[0] क्रम good measure */
		rq[0] = i915_request_create(ce[0]);
		अगर (IS_ERR(rq[0])) अणु
			err = PTR_ERR(rq[0]);
			i915_request_put(rq[1]);
			जाओ err_ce;
		पूर्ण

		i915_request_aरुको_dma_fence(rq[0], &rq[1]->fence);
		i915_request_get(rq[0]);
		i915_request_add(rq[0]);
		GEM_BUG_ON(rq[0]->postfix > rq[1]->postfix);
		i915_request_put(rq[1]);
		i915_request_put(rq[0]);

err_ce:
		पूर्णांकel_engine_flush_submission(engine);
		igt_spinner_end(&spin);
		क्रम (n = 0; n < ARRAY_SIZE(ce); n++) अणु
			अगर (IS_ERR_OR_शून्य(ce[n]))
				अवरोध;

			पूर्णांकel_context_unpin(ce[n]);
			पूर्णांकel_context_put(ce[n]);
		पूर्ण

		st_engine_heartbeat_enable(engine);
		अगर (igt_live_test_end(&t))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_unlite_चयन(व्योम *arg)
अणु
	वापस live_unlite_restore(arg, 0);
पूर्ण

अटल पूर्णांक live_unlite_preempt(व्योम *arg)
अणु
	वापस live_unlite_restore(arg, I915_PRIORITY_MAX);
पूर्ण

अटल पूर्णांक live_unlite_ring(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा igt_spinner spin;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Setup a preemption event that will cause almost the entire ring
	 * to be unwound, potentially fooling our पूर्णांकel_ring_direction()
	 * पूर्णांकo emitting a क्रमward lite-restore instead of the rollback.
	 */

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce[2] = अणुपूर्ण;
		काष्ठा i915_request *rq;
		काष्ठा igt_live_test t;
		पूर्णांक n;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण
		st_engine_heartbeat_disable(engine);

		क्रम (n = 0; n < ARRAY_SIZE(ce); n++) अणु
			काष्ठा पूर्णांकel_context *पंचांगp;

			पंचांगp = पूर्णांकel_context_create(engine);
			अगर (IS_ERR(पंचांगp)) अणु
				err = PTR_ERR(पंचांगp);
				जाओ err_ce;
			पूर्ण

			err = पूर्णांकel_context_pin(पंचांगp);
			अगर (err) अणु
				पूर्णांकel_context_put(पंचांगp);
				जाओ err_ce;
			पूर्ण

			स_रखो32(पंचांगp->ring->vaddr,
				 0xdeadbeef, /* trigger a hang अगर executed */
				 पंचांगp->ring->vma->size / माप(u32));

			ce[n] = पंचांगp;
		पूर्ण

		/* Create max prio spinner, followed by N low prio nops */
		rq = igt_spinner_create_request(&spin, ce[0], MI_ARB_CHECK);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_ce;
		पूर्ण

		i915_request_get(rq);
		rq->sched.attr.priority = I915_PRIORITY_BARRIER;
		i915_request_add(rq);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			पूर्णांकel_gt_set_wedged(gt);
			i915_request_put(rq);
			err = -ETIME;
			जाओ err_ce;
		पूर्ण

		/* Fill the ring, until we will cause a wrap */
		n = 0;
		जबतक (पूर्णांकel_ring_direction(ce[0]->ring,
					    rq->wa_tail,
					    ce[0]->ring->tail) <= 0) अणु
			काष्ठा i915_request *पंचांगp;

			पंचांगp = पूर्णांकel_context_create_request(ce[0]);
			अगर (IS_ERR(पंचांगp)) अणु
				err = PTR_ERR(पंचांगp);
				i915_request_put(rq);
				जाओ err_ce;
			पूर्ण

			i915_request_add(पंचांगp);
			पूर्णांकel_engine_flush_submission(engine);
			n++;
		पूर्ण
		पूर्णांकel_engine_flush_submission(engine);
		pr_debug("%s: Filled ring with %d nop tails {size:%x, tail:%x, emit:%x, rq.tail:%x}\n",
			 engine->name, n,
			 ce[0]->ring->size,
			 ce[0]->ring->tail,
			 ce[0]->ring->emit,
			 rq->tail);
		GEM_BUG_ON(पूर्णांकel_ring_direction(ce[0]->ring,
						rq->tail,
						ce[0]->ring->tail) <= 0);
		i915_request_put(rq);

		/* Create a second ring to preempt the first ring after rq[0] */
		rq = पूर्णांकel_context_create_request(ce[1]);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_ce;
		पूर्ण

		rq->sched.attr.priority = I915_PRIORITY_BARRIER;
		i915_request_get(rq);
		i915_request_add(rq);

		err = रुको_क्रम_submit(engine, rq, HZ / 2);
		i915_request_put(rq);
		अगर (err) अणु
			pr_err("%s: preemption request was not submitted\n",
			       engine->name);
			err = -ETIME;
		पूर्ण

		pr_debug("%s: ring[0]:{ tail:%x, emit:%x }, ring[1]:{ tail:%x, emit:%x }\n",
			 engine->name,
			 ce[0]->ring->tail, ce[0]->ring->emit,
			 ce[1]->ring->tail, ce[1]->ring->emit);

err_ce:
		पूर्णांकel_engine_flush_submission(engine);
		igt_spinner_end(&spin);
		क्रम (n = 0; n < ARRAY_SIZE(ce); n++) अणु
			अगर (IS_ERR_OR_शून्य(ce[n]))
				अवरोध;

			पूर्णांकel_context_unpin(ce[n]);
			पूर्णांकel_context_put(ce[n]);
		पूर्ण
		st_engine_heartbeat_enable(engine);
		अगर (igt_live_test_end(&t))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_pin_शुरुआत(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * We have to be careful not to trust पूर्णांकel_ring too much, क्रम example
	 * ring->head is updated upon retire which is out of sync with pinning
	 * the context. Thus we cannot use ring->head to set CTX_RING_HEAD,
	 * or अन्यथा we risk writing an older, stale value.
	 *
	 * To simulate this, let's apply a bit of deliberate sabotague.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा i915_request *rq;
		काष्ठा पूर्णांकel_ring *ring;
		काष्ठा igt_live_test t;

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			अवरोध;
		पूर्ण

		err = पूर्णांकel_context_pin(ce);
		अगर (err) अणु
			पूर्णांकel_context_put(ce);
			अवरोध;
		पूर्ण

		/* Keep the context awake जबतक we play games */
		err = i915_active_acquire(&ce->active);
		अगर (err) अणु
			पूर्णांकel_context_unpin(ce);
			पूर्णांकel_context_put(ce);
			अवरोध;
		पूर्ण
		ring = ce->ring;

		/* Poison the ring, and offset the next request from HEAD */
		स_रखो32(ring->vaddr, STACK_MAGIC, ring->size / माप(u32));
		ring->emit = ring->size / 2;
		ring->tail = ring->emit;
		GEM_BUG_ON(ring->head);

		पूर्णांकel_context_unpin(ce);

		/* Submit a simple nop request */
		GEM_BUG_ON(पूर्णांकel_context_is_pinned(ce));
		rq = पूर्णांकel_context_create_request(ce);
		i915_active_release(&ce->active); /* e.g. async retire */
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण
		GEM_BUG_ON(!rq->head);
		i915_request_add(rq);

		/* Expect not to hang! */
		अगर (igt_live_test_end(&t)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक live_hold_reset(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	/*
	 * In order to support offline error capture क्रम fast preempt reset,
	 * we need to decouple the guilty request and ensure that it and its
	 * descendents are not executed जबतक the capture is in progress.
	 */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा i915_request *rq;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			अवरोध;
		पूर्ण

		st_engine_heartbeat_disable(engine);

		rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out;
		पूर्ण
		i915_request_add(rq);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			पूर्णांकel_gt_set_wedged(gt);
			err = -ETIME;
			जाओ out;
		पूर्ण

		/* We have our request executing, now हटाओ it and reset */

		local_bh_disable();
		अगर (test_and_set_bit(I915_RESET_ENGINE + id,
				     &gt->reset.flags)) अणु
			local_bh_enable();
			पूर्णांकel_gt_set_wedged(gt);
			err = -EBUSY;
			जाओ out;
		पूर्ण
		tasklet_disable(&engine->execlists.tasklet);

		engine->execlists.tasklet.callback(&engine->execlists.tasklet);
		GEM_BUG_ON(execlists_active(&engine->execlists) != rq);

		i915_request_get(rq);
		execlists_hold(engine, rq);
		GEM_BUG_ON(!i915_request_on_hold(rq));

		__पूर्णांकel_engine_reset_bh(engine, शून्य);
		GEM_BUG_ON(rq->fence.error != -EIO);

		tasklet_enable(&engine->execlists.tasklet);
		clear_and_wake_up_bit(I915_RESET_ENGINE + id,
				      &gt->reset.flags);
		local_bh_enable();

		/* Check that we करो not resubmit the held request */
		अगर (!i915_request_रुको(rq, 0, HZ / 5)) अणु
			pr_err("%s: on hold request completed!\n",
			       engine->name);
			i915_request_put(rq);
			err = -EIO;
			जाओ out;
		पूर्ण
		GEM_BUG_ON(!i915_request_on_hold(rq));

		/* But is resubmitted on release */
		execlists_unhold(engine, rq);
		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
			pr_err("%s: held request did not complete!\n",
			       engine->name);
			पूर्णांकel_gt_set_wedged(gt);
			err = -ETIME;
		पूर्ण
		i915_request_put(rq);

out:
		st_engine_heartbeat_enable(engine);
		पूर्णांकel_context_put(ce);
		अगर (err)
			अवरोध;
	पूर्ण

	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल स्थिर अक्षर *error_repr(पूर्णांक err)
अणु
	वापस err ? "bad" : "good";
पूर्ण

अटल पूर्णांक live_error_पूर्णांकerrupt(व्योम *arg)
अणु
	अटल स्थिर काष्ठा error_phase अणु
		क्रमागत अणु GOOD = 0, BAD = -EIO पूर्ण error[2];
	पूर्ण phases[] = अणु
		अणु अणु BAD,  GOOD पूर्ण पूर्ण,
		अणु अणु BAD,  BAD  पूर्ण पूर्ण,
		अणु अणु BAD,  GOOD पूर्ण पूर्ण,
		अणु अणु GOOD, GOOD पूर्ण पूर्ण, /* sentinel */
	पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * We hook up the CS_MASTER_ERROR_INTERRUPT to have क्रमewarning
	 * of invalid commands in user batches that will cause a GPU hang.
	 * This is a faster mechanism than using hangcheck/heartbeats, but
	 * only detects problems the HW knows about -- it will not warn when
	 * we समाप्त the HW!
	 *
	 * To verअगरy our detection and reset, we throw some invalid commands
	 * at the HW and रुको क्रम the पूर्णांकerrupt.
	 */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		स्थिर काष्ठा error_phase *p;
		पूर्णांक err = 0;

		st_engine_heartbeat_disable(engine);

		क्रम (p = phases; p->error[0] != GOOD; p++) अणु
			काष्ठा i915_request *client[ARRAY_SIZE(phases->error)];
			u32 *cs;
			पूर्णांक i;

			स_रखो(client, 0, माप(*client));
			क्रम (i = 0; i < ARRAY_SIZE(client); i++) अणु
				काष्ठा पूर्णांकel_context *ce;
				काष्ठा i915_request *rq;

				ce = पूर्णांकel_context_create(engine);
				अगर (IS_ERR(ce)) अणु
					err = PTR_ERR(ce);
					जाओ out;
				पूर्ण

				rq = पूर्णांकel_context_create_request(ce);
				पूर्णांकel_context_put(ce);
				अगर (IS_ERR(rq)) अणु
					err = PTR_ERR(rq);
					जाओ out;
				पूर्ण

				अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
					err = rq->engine->emit_init_bपढ़ोcrumb(rq);
					अगर (err) अणु
						i915_request_add(rq);
						जाओ out;
					पूर्ण
				पूर्ण

				cs = पूर्णांकel_ring_begin(rq, 2);
				अगर (IS_ERR(cs)) अणु
					i915_request_add(rq);
					err = PTR_ERR(cs);
					जाओ out;
				पूर्ण

				अगर (p->error[i]) अणु
					*cs++ = 0xdeadbeef;
					*cs++ = 0xdeadbeef;
				पूर्ण अन्यथा अणु
					*cs++ = MI_NOOP;
					*cs++ = MI_NOOP;
				पूर्ण

				client[i] = i915_request_get(rq);
				i915_request_add(rq);
			पूर्ण

			err = रुको_क्रम_submit(engine, client[0], HZ / 2);
			अगर (err) अणु
				pr_err("%s: first request did not start within time!\n",
				       engine->name);
				err = -ETIME;
				जाओ out;
			पूर्ण

			क्रम (i = 0; i < ARRAY_SIZE(client); i++) अणु
				अगर (i915_request_रुको(client[i], 0, HZ / 5) < 0)
					pr_debug("%s: %s request incomplete!\n",
						 engine->name,
						 error_repr(p->error[i]));

				अगर (!i915_request_started(client[i])) अणु
					pr_err("%s: %s request not started!\n",
					       engine->name,
					       error_repr(p->error[i]));
					err = -ETIME;
					जाओ out;
				पूर्ण

				/* Kick the tasklet to process the error */
				पूर्णांकel_engine_flush_submission(engine);
				अगर (client[i]->fence.error != p->error[i]) अणु
					pr_err("%s: %s request (%s) with wrong error code: %d\n",
					       engine->name,
					       error_repr(p->error[i]),
					       i915_request_completed(client[i]) ? "completed" : "running",
					       client[i]->fence.error);
					err = -EINVAL;
					जाओ out;
				पूर्ण
			पूर्ण

out:
			क्रम (i = 0; i < ARRAY_SIZE(client); i++)
				अगर (client[i])
					i915_request_put(client[i]);
			अगर (err) अणु
				pr_err("%s: failed at phase[%zd] { %d, %d }\n",
				       engine->name, p - phases,
				       p->error[0], p->error[1]);
				अवरोध;
			पूर्ण
		पूर्ण

		st_engine_heartbeat_enable(engine);
		अगर (err) अणु
			पूर्णांकel_gt_set_wedged(gt);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
emit_semaphore_chain(काष्ठा i915_request *rq, काष्ठा i915_vma *vma, पूर्णांक idx)
अणु
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 10);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;

	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = i915_ggtt_offset(vma) + 4 * idx;
	*cs++ = 0;

	अगर (idx > 0) अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = i915_ggtt_offset(vma) + 4 * (idx - 1);
		*cs++ = 0;
		*cs++ = 1;
	पूर्ण अन्यथा अणु
		*cs++ = MI_NOOP;
		*cs++ = MI_NOOP;
		*cs++ = MI_NOOP;
		*cs++ = MI_NOOP;
	पूर्ण

	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;

	पूर्णांकel_ring_advance(rq, cs);
	वापस 0;
पूर्ण

अटल काष्ठा i915_request *
semaphore_queue(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा i915_vma *vma, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	पूर्णांक err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस ERR_CAST(ce);

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		जाओ out_ce;

	err = 0;
	अगर (rq->engine->emit_init_bपढ़ोcrumb)
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
	अगर (err == 0)
		err = emit_semaphore_chain(rq, vma, idx);
	अगर (err == 0)
		i915_request_get(rq);
	i915_request_add(rq);
	अगर (err)
		rq = ERR_PTR(err);

out_ce:
	पूर्णांकel_context_put(ce);
	वापस rq;
पूर्ण

अटल पूर्णांक
release_queue(काष्ठा पूर्णांकel_engine_cs *engine,
	      काष्ठा i915_vma *vma,
	      पूर्णांक idx, पूर्णांक prio)
अणु
	काष्ठा i915_sched_attr attr = अणु
		.priority = prio,
	पूर्ण;
	काष्ठा i915_request *rq;
	u32 *cs;

	rq = पूर्णांकel_engine_create_kernel_request(engine);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = i915_ggtt_offset(vma) + 4 * (idx - 1);
	*cs++ = 0;
	*cs++ = 1;

	पूर्णांकel_ring_advance(rq, cs);

	i915_request_get(rq);
	i915_request_add(rq);

	local_bh_disable();
	engine->schedule(rq, &attr);
	local_bh_enable(); /* kick tasklet */

	i915_request_put(rq);

	वापस 0;
पूर्ण

अटल पूर्णांक
slice_semaphore_queue(काष्ठा पूर्णांकel_engine_cs *outer,
		      काष्ठा i915_vma *vma,
		      पूर्णांक count)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_request *head;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err, i, n = 0;

	head = semaphore_queue(outer, vma, n++);
	अगर (IS_ERR(head))
		वापस PTR_ERR(head);

	क्रम_each_engine(engine, outer->gt, id) अणु
		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		क्रम (i = 0; i < count; i++) अणु
			काष्ठा i915_request *rq;

			rq = semaphore_queue(engine, vma, n++);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				जाओ out;
			पूर्ण

			i915_request_put(rq);
		पूर्ण
	पूर्ण

	err = release_queue(outer, vma, n, I915_PRIORITY_BARRIER);
	अगर (err)
		जाओ out;

	अगर (i915_request_रुको(head, 0,
			      2 * outer->gt->info.num_engines * (count + 2) * (count + 3)) < 0) अणु
		pr_err("%s: Failed to slice along semaphore chain of length (%d, %d)!\n",
		       outer->name, count, n);
		GEM_TRACE_DUMP();
		पूर्णांकel_gt_set_wedged(outer->gt);
		err = -EIO;
	पूर्ण

out:
	i915_request_put(head);
	वापस err;
पूर्ण

अटल पूर्णांक live_बारlice_preempt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा i915_vma *vma;
	व्योम *vaddr;
	पूर्णांक err = 0;

	/*
	 * If a request takes too दीर्घ, we would like to give other users
	 * a fair go on the GPU. In particular, users may create batches
	 * that रुको upon बाह्यal input, where that input may even be
	 * supplied by another GPU job. To aव्योम blocking क्रमever, we
	 * need to preempt the current task and replace it with another
	 * पढ़ोy task.
	 */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_TIMESLICE_DURATION))
		वापस 0;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_obj;
	पूर्ण

	vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ err_obj;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
	अगर (err)
		जाओ err_map;

	err = i915_vma_sync(vma);
	अगर (err)
		जाओ err_pin;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		स_रखो(vaddr, 0, PAGE_SIZE);

		st_engine_heartbeat_disable(engine);
		err = slice_semaphore_queue(engine, vma, 5);
		st_engine_heartbeat_enable(engine);
		अगर (err)
			जाओ err_pin;

		अगर (igt_flush_test(gt->i915)) अणु
			err = -EIO;
			जाओ err_pin;
		पूर्ण
	पूर्ण

err_pin:
	i915_vma_unpin(vma);
err_map:
	i915_gem_object_unpin_map(obj);
err_obj:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल काष्ठा i915_request *
create_शुरुआतer(काष्ठा पूर्णांकel_context *ce,
		काष्ठा i915_request *रुको,
		व्योम *slot, पूर्णांक idx)
अणु
	स्थिर u32 offset =
		i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(slot);
	काष्ठा i915_request *rq;
	u32 *cs;
	पूर्णांक err;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस rq;

	अगर (रुको) अणु
		err = i915_request_aरुको_dma_fence(rq, &रुको->fence);
		अगर (err)
			जाओ err;
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, 14);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err;
	पूर्ण

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	*cs++ = MI_NOOP;

	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_GTE_SDD;
	*cs++ = idx;
	*cs++ = offset;
	*cs++ = 0;

	*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_reg_offset(RING_TIMESTAMP(rq->engine->mmio_base));
	*cs++ = offset + idx * माप(u32);
	*cs++ = 0;

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = idx + 1;

	पूर्णांकel_ring_advance(rq, cs);

	err = 0;
err:
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (err) अणु
		i915_request_put(rq);
		वापस ERR_PTR(err);
	पूर्ण

	वापस rq;
पूर्ण

अटल पूर्णांक live_बारlice_शुरुआत(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * The usual presumption on बारlice expiration is that we replace
	 * the active context with another. However, given a chain of
	 * dependencies we may end up with replacing the context with itself,
	 * but only a few of those requests, क्रमcing us to शुरुआत the
	 * RING_TAIL of the original request.
	 */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_TIMESLICE_DURATION))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		क्रमागत अणु A1, A2, B1 पूर्ण;
		क्रमागत अणु X = 1, Z, Y पूर्ण;
		काष्ठा i915_request *rq[3] = अणुपूर्ण;
		काष्ठा पूर्णांकel_context *ce;
		अचिन्हित दीर्घ बारlice;
		पूर्णांक i, err = 0;
		u32 *slot;

		अगर (!पूर्णांकel_engine_has_बारlices(engine))
			जारी;

		/*
		 * A:rq1 -- semaphore रुको, बारtamp X
		 * A:rq2 -- ग_लिखो बारtamp Y
		 *
		 * B:rq1 [aरुको A:rq1] -- ग_लिखो बारtamp Z
		 *
		 * Force बारlice, release semaphore.
		 *
		 * Expect execution/evaluation order XZY
		 */

		st_engine_heartbeat_disable(engine);
		बारlice = xchg(&engine->props.बारlice_duration_ms, 1);

		slot = स_रखो32(engine->status_page.addr + 1000, 0, 4);

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ err;
		पूर्ण

		rq[A1] = create_शुरुआतer(ce, शून्य, slot, X);
		अगर (IS_ERR(rq[A1])) अणु
			पूर्णांकel_context_put(ce);
			जाओ err;
		पूर्ण

		rq[A2] = create_शुरुआतer(ce, शून्य, slot, Y);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq[A2]))
			जाओ err;

		err = रुको_क्रम_submit(engine, rq[A2], HZ / 2);
		अगर (err) अणु
			pr_err("%s: failed to submit first context\n",
			       engine->name);
			जाओ err;
		पूर्ण

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ err;
		पूर्ण

		rq[B1] = create_शुरुआतer(ce, rq[A1], slot, Z);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq[2]))
			जाओ err;

		err = रुको_क्रम_submit(engine, rq[B1], HZ / 2);
		अगर (err) अणु
			pr_err("%s: failed to submit second context\n",
			       engine->name);
			जाओ err;
		पूर्ण

		/* ELSP[] = अणु अणु A:rq1, A:rq2 पूर्ण, अणु B:rq1 पूर्ण पूर्ण */
		ENGINE_TRACE(engine, "forcing tasklet for rewind\n");
		जबतक (i915_request_is_active(rq[A2])) अणु /* semaphore yield! */
			/* Wait क्रम the बारlice to kick in */
			del_समयr(&engine->execlists.समयr);
			tasklet_hi_schedule(&engine->execlists.tasklet);
			पूर्णांकel_engine_flush_submission(engine);
		पूर्ण
		/* -> ELSP[] = अणु अणु A:rq1 पूर्ण, अणु B:rq1 पूर्ण पूर्ण */
		GEM_BUG_ON(!i915_request_is_active(rq[A1]));
		GEM_BUG_ON(!i915_request_is_active(rq[B1]));
		GEM_BUG_ON(i915_request_is_active(rq[A2]));

		/* Release the hounds! */
		slot[0] = 1;
		wmb(); /* "pairs" with GPU; paranoid kick of पूर्णांकernal CPU$ */

		क्रम (i = 1; i <= 3; i++) अणु
			अचिन्हित दीर्घ समयout = jअगरfies + HZ / 2;

			जबतक (!READ_ONCE(slot[i]) &&
			       समय_beक्रमe(jअगरfies, समयout))
				;

			अगर (!समय_beक्रमe(jअगरfies, समयout)) अणु
				pr_err("%s: rq[%d] timed out\n",
				       engine->name, i - 1);
				err = -ETIME;
				जाओ err;
			पूर्ण

			pr_debug("%s: slot[%d]:%x\n", engine->name, i, slot[i]);
		पूर्ण

		/* XZY: XZ < XY */
		अगर (slot[Z] - slot[X] >= slot[Y] - slot[X]) अणु
			pr_err("%s: timeslicing did not run context B [%u] before A [%u]!\n",
			       engine->name,
			       slot[Z] - slot[X],
			       slot[Y] - slot[X]);
			err = -EINVAL;
		पूर्ण

err:
		स_रखो32(&slot[0], -1, 4);
		wmb();

		engine->props.बारlice_duration_ms = बारlice;
		st_engine_heartbeat_enable(engine);
		क्रम (i = 0; i < 3; i++)
			i915_request_put(rq[i]);
		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i915_request *nop_request(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_request *rq;

	rq = पूर्णांकel_engine_create_kernel_request(engine);
	अगर (IS_ERR(rq))
		वापस rq;

	i915_request_get(rq);
	i915_request_add(rq);

	वापस rq;
पूर्ण

अटल दीर्घ slice_समयout(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	दीर्घ समयout;

	/* Enough समय क्रम a बारlice to kick in, and kick out */
	समयout = 2 * msecs_to_jअगरfies_समयout(बारlice(engine));

	/* Enough समय क्रम the nop request to complete */
	समयout += HZ / 5;

	वापस समयout + 1;
पूर्ण

अटल पूर्णांक live_बारlice_queue(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा i915_vma *vma;
	व्योम *vaddr;
	पूर्णांक err = 0;

	/*
	 * Make sure that even अगर ELSP[0] and ELSP[1] are filled with
	 * बारlicing between them disabled, we *करो* enable बारlicing
	 * अगर the queue demands it. (Normally, we करो not submit अगर
	 * ELSP[1] is alपढ़ोy occupied, so must rely on बारlicing to
	 * eject ELSP[0] in favour of the queue.)
	 */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_TIMESLICE_DURATION))
		वापस 0;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_obj;
	पूर्ण

	vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ err_obj;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
	अगर (err)
		जाओ err_map;

	err = i915_vma_sync(vma);
	अगर (err)
		जाओ err_pin;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_sched_attr attr = अणु .priority = I915_PRIORITY_MAX पूर्ण;
		काष्ठा i915_request *rq, *nop;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		st_engine_heartbeat_disable(engine);
		स_रखो(vaddr, 0, PAGE_SIZE);

		/* ELSP[0]: semaphore रुको */
		rq = semaphore_queue(engine, vma, 0);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_heartbeat;
		पूर्ण
		engine->schedule(rq, &attr);
		err = रुको_क्रम_submit(engine, rq, HZ / 2);
		अगर (err) अणु
			pr_err("%s: Timed out trying to submit semaphores\n",
			       engine->name);
			जाओ err_rq;
		पूर्ण

		/* ELSP[1]: nop request */
		nop = nop_request(engine);
		अगर (IS_ERR(nop)) अणु
			err = PTR_ERR(nop);
			जाओ err_rq;
		पूर्ण
		err = रुको_क्रम_submit(engine, nop, HZ / 2);
		i915_request_put(nop);
		अगर (err) अणु
			pr_err("%s: Timed out trying to submit nop\n",
			       engine->name);
			जाओ err_rq;
		पूर्ण

		GEM_BUG_ON(i915_request_completed(rq));
		GEM_BUG_ON(execlists_active(&engine->execlists) != rq);

		/* Queue: semaphore संकेत, matching priority as semaphore */
		err = release_queue(engine, vma, 1, effective_prio(rq));
		अगर (err)
			जाओ err_rq;

		/* Wait until we ack the release_queue and start बारlicing */
		करो अणु
			cond_resched();
			पूर्णांकel_engine_flush_submission(engine);
		पूर्ण जबतक (READ_ONCE(engine->execlists.pending[0]));

		/* Timeslice every jअगरfy, so within 2 we should संकेत */
		अगर (i915_request_रुको(rq, 0, slice_समयout(engine)) < 0) अणु
			काष्ठा drm_prपूर्णांकer p =
				drm_info_prपूर्णांकer(gt->i915->drm.dev);

			pr_err("%s: Failed to timeslice into queue\n",
			       engine->name);
			पूर्णांकel_engine_dump(engine, &p,
					  "%s\n", engine->name);

			स_रखो(vaddr, 0xff, PAGE_SIZE);
			err = -EIO;
		पूर्ण
err_rq:
		i915_request_put(rq);
err_heartbeat:
		st_engine_heartbeat_enable(engine);
		अगर (err)
			अवरोध;
	पूर्ण

err_pin:
	i915_vma_unpin(vma);
err_map:
	i915_gem_object_unpin_map(obj);
err_obj:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल पूर्णांक live_बारlice_nopreempt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	पूर्णांक err = 0;

	/*
	 * We should not बारlice पूर्णांकo a request that is marked with
	 * I915_REQUEST_NOPREEMPT.
	 */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_TIMESLICE_DURATION))
		वापस 0;

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा i915_request *rq;
		अचिन्हित दीर्घ बारlice;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			अवरोध;
		पूर्ण

		st_engine_heartbeat_disable(engine);
		बारlice = xchg(&engine->props.बारlice_duration_ms, 1);

		/* Create an unpreemptible spinner */

		rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out_heartbeat;
		पूर्ण

		i915_request_get(rq);
		i915_request_add(rq);

		अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
			i915_request_put(rq);
			err = -ETIME;
			जाओ out_spin;
		पूर्ण

		set_bit(I915_FENCE_FLAG_NOPREEMPT, &rq->fence.flags);
		i915_request_put(rq);

		/* Followed by a maximum priority barrier (heartbeat) */

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out_spin;
		पूर्ण

		rq = पूर्णांकel_context_create_request(ce);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out_spin;
		पूर्ण

		rq->sched.attr.priority = I915_PRIORITY_BARRIER;
		i915_request_get(rq);
		i915_request_add(rq);

		/*
		 * Wait until the barrier is in ELSP, and we know बारlicing
		 * will have been activated.
		 */
		अगर (रुको_क्रम_submit(engine, rq, HZ / 2)) अणु
			i915_request_put(rq);
			err = -ETIME;
			जाओ out_spin;
		पूर्ण

		/*
		 * Since the ELSP[0] request is unpreemptible, it should not
		 * allow the maximum priority barrier through. Wait दीर्घ
		 * enough to see अगर it is बारliced in by mistake.
		 */
		अगर (i915_request_रुको(rq, 0, slice_समयout(engine)) >= 0) अणु
			pr_err("%s: I915_PRIORITY_BARRIER request completed, bypassing no-preempt request\n",
			       engine->name);
			err = -EINVAL;
		पूर्ण
		i915_request_put(rq);

out_spin:
		igt_spinner_end(&spin);
out_heartbeat:
		xchg(&engine->props.बारlice_duration_ms, बारlice);
		st_engine_heartbeat_enable(engine);
		अगर (err)
			अवरोध;

		अगर (igt_flush_test(gt->i915)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_busyरुको_preempt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gem_context *ctx_hi, *ctx_lo;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;
	u32 *map;

	/*
	 * Verअगरy that even without HAS_LOGICAL_RING_PREEMPTION, we can
	 * preempt the busyरुकोs used to synchronise between rings.
	 */

	ctx_hi = kernel_context(gt->i915);
	अगर (!ctx_hi)
		वापस -ENOMEM;
	ctx_hi->sched.priority = I915_CONTEXT_MAX_USER_PRIORITY;

	ctx_lo = kernel_context(gt->i915);
	अगर (!ctx_lo)
		जाओ err_ctx_hi;
	ctx_lo->sched.priority = I915_CONTEXT_MIN_USER_PRIORITY;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ err_ctx_lo;
	पूर्ण

	map = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(map)) अणु
		err = PTR_ERR(map);
		जाओ err_obj;
	पूर्ण

	vma = i915_vma_instance(obj, &gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_map;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
	अगर (err)
		जाओ err_map;

	err = i915_vma_sync(vma);
	अगर (err)
		जाओ err_vma;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *lo, *hi;
		काष्ठा igt_live_test t;
		u32 *cs;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			जाओ err_vma;
		पूर्ण

		/*
		 * We create two requests. The low priority request
		 * busyरुकोs on a semaphore (inside the ringbuffer where
		 * is should be preemptible) and the high priority requests
		 * uses a MI_STORE_DWORD_IMM to update the semaphore value
		 * allowing the first request to complete. If preemption
		 * fails, we hang instead.
		 */

		lo = igt_request_alloc(ctx_lo, engine);
		अगर (IS_ERR(lo)) अणु
			err = PTR_ERR(lo);
			जाओ err_vma;
		पूर्ण

		cs = पूर्णांकel_ring_begin(lo, 8);
		अगर (IS_ERR(cs)) अणु
			err = PTR_ERR(cs);
			i915_request_add(lo);
			जाओ err_vma;
		पूर्ण

		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = i915_ggtt_offset(vma);
		*cs++ = 0;
		*cs++ = 1;

		/* XXX Do we need a flush + invalidate here? */

		*cs++ = MI_SEMAPHORE_WAIT |
			MI_SEMAPHORE_GLOBAL_GTT |
			MI_SEMAPHORE_POLL |
			MI_SEMAPHORE_SAD_EQ_SDD;
		*cs++ = 0;
		*cs++ = i915_ggtt_offset(vma);
		*cs++ = 0;

		पूर्णांकel_ring_advance(lo, cs);

		i915_request_get(lo);
		i915_request_add(lo);

		अगर (रुको_क्रम(READ_ONCE(*map), 10)) अणु
			i915_request_put(lo);
			err = -ETIMEDOUT;
			जाओ err_vma;
		पूर्ण

		/* Low priority request should be busyरुकोing now */
		अगर (i915_request_रुको(lo, 0, 1) != -ETIME) अणु
			i915_request_put(lo);
			pr_err("%s: Busywaiting request did not!\n",
			       engine->name);
			err = -EIO;
			जाओ err_vma;
		पूर्ण

		hi = igt_request_alloc(ctx_hi, engine);
		अगर (IS_ERR(hi)) अणु
			err = PTR_ERR(hi);
			i915_request_put(lo);
			जाओ err_vma;
		पूर्ण

		cs = पूर्णांकel_ring_begin(hi, 4);
		अगर (IS_ERR(cs)) अणु
			err = PTR_ERR(cs);
			i915_request_add(hi);
			i915_request_put(lo);
			जाओ err_vma;
		पूर्ण

		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = i915_ggtt_offset(vma);
		*cs++ = 0;
		*cs++ = 0;

		पूर्णांकel_ring_advance(hi, cs);
		i915_request_add(hi);

		अगर (i915_request_रुको(lo, 0, HZ / 5) < 0) अणु
			काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

			pr_err("%s: Failed to preempt semaphore busywait!\n",
			       engine->name);

			पूर्णांकel_engine_dump(engine, &p, "%s\n", engine->name);
			GEM_TRACE_DUMP();

			i915_request_put(lo);
			पूर्णांकel_gt_set_wedged(gt);
			err = -EIO;
			जाओ err_vma;
		पूर्ण
		GEM_BUG_ON(READ_ONCE(*map));
		i915_request_put(lo);

		अगर (igt_live_test_end(&t)) अणु
			err = -EIO;
			जाओ err_vma;
		पूर्ण
	पूर्ण

	err = 0;
err_vma:
	i915_vma_unpin(vma);
err_map:
	i915_gem_object_unpin_map(obj);
err_obj:
	i915_gem_object_put(obj);
err_ctx_lo:
	kernel_context_बंद(ctx_lo);
err_ctx_hi:
	kernel_context_बंद(ctx_hi);
	वापस err;
पूर्ण

अटल काष्ठा i915_request *
spinner_create_request(काष्ठा igt_spinner *spin,
		       काष्ठा i915_gem_context *ctx,
		       काष्ठा पूर्णांकel_engine_cs *engine,
		       u32 arb)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;

	ce = i915_gem_context_get_engine(ctx, engine->legacy_idx);
	अगर (IS_ERR(ce))
		वापस ERR_CAST(ce);

	rq = igt_spinner_create_request(spin, ce, arb);
	पूर्णांकel_context_put(ce);
	वापस rq;
पूर्ण

अटल पूर्णांक live_preempt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gem_context *ctx_hi, *ctx_lo;
	काष्ठा igt_spinner spin_hi, spin_lo;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;

	अगर (igt_spinner_init(&spin_hi, gt))
		वापस -ENOMEM;

	अगर (igt_spinner_init(&spin_lo, gt))
		जाओ err_spin_hi;

	ctx_hi = kernel_context(gt->i915);
	अगर (!ctx_hi)
		जाओ err_spin_lo;
	ctx_hi->sched.priority = I915_CONTEXT_MAX_USER_PRIORITY;

	ctx_lo = kernel_context(gt->i915);
	अगर (!ctx_lo)
		जाओ err_ctx_hi;
	ctx_lo->sched.priority = I915_CONTEXT_MIN_USER_PRIORITY;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा igt_live_test t;
		काष्ठा i915_request *rq;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			जाओ err_ctx_lo;
		पूर्ण

		rq = spinner_create_request(&spin_lo, ctx_lo, engine,
					    MI_ARB_CHECK);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_ctx_lo;
		पूर्ण

		i915_request_add(rq);
		अगर (!igt_रुको_क्रम_spinner(&spin_lo, rq)) अणु
			GEM_TRACE("lo spinner failed to start\n");
			GEM_TRACE_DUMP();
			पूर्णांकel_gt_set_wedged(gt);
			err = -EIO;
			जाओ err_ctx_lo;
		पूर्ण

		rq = spinner_create_request(&spin_hi, ctx_hi, engine,
					    MI_ARB_CHECK);
		अगर (IS_ERR(rq)) अणु
			igt_spinner_end(&spin_lo);
			err = PTR_ERR(rq);
			जाओ err_ctx_lo;
		पूर्ण

		i915_request_add(rq);
		अगर (!igt_रुको_क्रम_spinner(&spin_hi, rq)) अणु
			GEM_TRACE("hi spinner failed to start\n");
			GEM_TRACE_DUMP();
			पूर्णांकel_gt_set_wedged(gt);
			err = -EIO;
			जाओ err_ctx_lo;
		पूर्ण

		igt_spinner_end(&spin_hi);
		igt_spinner_end(&spin_lo);

		अगर (igt_live_test_end(&t)) अणु
			err = -EIO;
			जाओ err_ctx_lo;
		पूर्ण
	पूर्ण

	err = 0;
err_ctx_lo:
	kernel_context_बंद(ctx_lo);
err_ctx_hi:
	kernel_context_बंद(ctx_hi);
err_spin_lo:
	igt_spinner_fini(&spin_lo);
err_spin_hi:
	igt_spinner_fini(&spin_hi);
	वापस err;
पूर्ण

अटल पूर्णांक live_late_preempt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gem_context *ctx_hi, *ctx_lo;
	काष्ठा igt_spinner spin_hi, spin_lo;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_sched_attr attr = अणुपूर्ण;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;

	अगर (igt_spinner_init(&spin_hi, gt))
		वापस -ENOMEM;

	अगर (igt_spinner_init(&spin_lo, gt))
		जाओ err_spin_hi;

	ctx_hi = kernel_context(gt->i915);
	अगर (!ctx_hi)
		जाओ err_spin_lo;

	ctx_lo = kernel_context(gt->i915);
	अगर (!ctx_lo)
		जाओ err_ctx_hi;

	/* Make sure ctx_lo stays beक्रमe ctx_hi until we trigger preemption. */
	ctx_lo->sched.priority = 1;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा igt_live_test t;
		काष्ठा i915_request *rq;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			जाओ err_ctx_lo;
		पूर्ण

		rq = spinner_create_request(&spin_lo, ctx_lo, engine,
					    MI_ARB_CHECK);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_ctx_lo;
		पूर्ण

		i915_request_add(rq);
		अगर (!igt_रुको_क्रम_spinner(&spin_lo, rq)) अणु
			pr_err("First context failed to start\n");
			जाओ err_wedged;
		पूर्ण

		rq = spinner_create_request(&spin_hi, ctx_hi, engine,
					    MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			igt_spinner_end(&spin_lo);
			err = PTR_ERR(rq);
			जाओ err_ctx_lo;
		पूर्ण

		i915_request_add(rq);
		अगर (igt_रुको_क्रम_spinner(&spin_hi, rq)) अणु
			pr_err("Second context overtook first?\n");
			जाओ err_wedged;
		पूर्ण

		attr.priority = I915_PRIORITY_MAX;
		engine->schedule(rq, &attr);

		अगर (!igt_रुको_क्रम_spinner(&spin_hi, rq)) अणु
			pr_err("High priority context failed to preempt the low priority context\n");
			GEM_TRACE_DUMP();
			जाओ err_wedged;
		पूर्ण

		igt_spinner_end(&spin_hi);
		igt_spinner_end(&spin_lo);

		अगर (igt_live_test_end(&t)) अणु
			err = -EIO;
			जाओ err_ctx_lo;
		पूर्ण
	पूर्ण

	err = 0;
err_ctx_lo:
	kernel_context_बंद(ctx_lo);
err_ctx_hi:
	kernel_context_बंद(ctx_hi);
err_spin_lo:
	igt_spinner_fini(&spin_lo);
err_spin_hi:
	igt_spinner_fini(&spin_hi);
	वापस err;

err_wedged:
	igt_spinner_end(&spin_hi);
	igt_spinner_end(&spin_lo);
	पूर्णांकel_gt_set_wedged(gt);
	err = -EIO;
	जाओ err_ctx_lo;
पूर्ण

काष्ठा preempt_client अणु
	काष्ठा igt_spinner spin;
	काष्ठा i915_gem_context *ctx;
पूर्ण;

अटल पूर्णांक preempt_client_init(काष्ठा पूर्णांकel_gt *gt, काष्ठा preempt_client *c)
अणु
	c->ctx = kernel_context(gt->i915);
	अगर (!c->ctx)
		वापस -ENOMEM;

	अगर (igt_spinner_init(&c->spin, gt))
		जाओ err_ctx;

	वापस 0;

err_ctx:
	kernel_context_बंद(c->ctx);
	वापस -ENOMEM;
पूर्ण

अटल व्योम preempt_client_fini(काष्ठा preempt_client *c)
अणु
	igt_spinner_fini(&c->spin);
	kernel_context_बंद(c->ctx);
पूर्ण

अटल पूर्णांक live_nopreempt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा preempt_client a, b;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;

	/*
	 * Verअगरy that we can disable preemption क्रम an inभागidual request
	 * that may be being observed and not want to be पूर्णांकerrupted.
	 */

	अगर (preempt_client_init(gt, &a))
		वापस -ENOMEM;
	अगर (preempt_client_init(gt, &b))
		जाओ err_client_a;
	b.ctx->sched.priority = I915_PRIORITY_MAX;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq_a, *rq_b;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		engine->execlists.preempt_hang.count = 0;

		rq_a = spinner_create_request(&a.spin,
					      a.ctx, engine,
					      MI_ARB_CHECK);
		अगर (IS_ERR(rq_a)) अणु
			err = PTR_ERR(rq_a);
			जाओ err_client_b;
		पूर्ण

		/* Low priority client, but unpreemptable! */
		__set_bit(I915_FENCE_FLAG_NOPREEMPT, &rq_a->fence.flags);

		i915_request_add(rq_a);
		अगर (!igt_रुको_क्रम_spinner(&a.spin, rq_a)) अणु
			pr_err("First client failed to start\n");
			जाओ err_wedged;
		पूर्ण

		rq_b = spinner_create_request(&b.spin,
					      b.ctx, engine,
					      MI_ARB_CHECK);
		अगर (IS_ERR(rq_b)) अणु
			err = PTR_ERR(rq_b);
			जाओ err_client_b;
		पूर्ण

		i915_request_add(rq_b);

		/* B is much more important than A! (But A is unpreemptable.) */
		GEM_BUG_ON(rq_prio(rq_b) <= rq_prio(rq_a));

		/* Wait दीर्घ enough क्रम preemption and बारlicing */
		अगर (igt_रुको_क्रम_spinner(&b.spin, rq_b)) अणु
			pr_err("Second client started too early!\n");
			जाओ err_wedged;
		पूर्ण

		igt_spinner_end(&a.spin);

		अगर (!igt_रुको_क्रम_spinner(&b.spin, rq_b)) अणु
			pr_err("Second client failed to start\n");
			जाओ err_wedged;
		पूर्ण

		igt_spinner_end(&b.spin);

		अगर (engine->execlists.preempt_hang.count) अणु
			pr_err("Preemption recorded x%d; should have been suppressed!\n",
			       engine->execlists.preempt_hang.count);
			err = -EINVAL;
			जाओ err_wedged;
		पूर्ण

		अगर (igt_flush_test(gt->i915))
			जाओ err_wedged;
	पूर्ण

	err = 0;
err_client_b:
	preempt_client_fini(&b);
err_client_a:
	preempt_client_fini(&a);
	वापस err;

err_wedged:
	igt_spinner_end(&b.spin);
	igt_spinner_end(&a.spin);
	पूर्णांकel_gt_set_wedged(gt);
	err = -EIO;
	जाओ err_client_b;
पूर्ण

काष्ठा live_preempt_cancel अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा preempt_client a, b;
पूर्ण;

अटल पूर्णांक __cancel_active0(काष्ठा live_preempt_cancel *arg)
अणु
	काष्ठा i915_request *rq;
	काष्ठा igt_live_test t;
	पूर्णांक err;

	/* Preempt cancel of ELSP0 */
	GEM_TRACE("%s(%s)\n", __func__, arg->engine->name);
	अगर (igt_live_test_begin(&t, arg->engine->i915,
				__func__, arg->engine->name))
		वापस -EIO;

	rq = spinner_create_request(&arg->a.spin,
				    arg->a.ctx, arg->engine,
				    MI_ARB_CHECK);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	clear_bit(CONTEXT_BANNED, &rq->context->flags);
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (!igt_रुको_क्रम_spinner(&arg->a.spin, rq)) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	पूर्णांकel_context_set_banned(rq->context);
	err = पूर्णांकel_engine_pulse(arg->engine);
	अगर (err)
		जाओ out;

	err = रुको_क्रम_reset(arg->engine, rq, HZ / 2);
	अगर (err) अणु
		pr_err("Cancelled inflight0 request did not reset\n");
		जाओ out;
	पूर्ण

out:
	i915_request_put(rq);
	अगर (igt_live_test_end(&t))
		err = -EIO;
	वापस err;
पूर्ण

अटल पूर्णांक __cancel_active1(काष्ठा live_preempt_cancel *arg)
अणु
	काष्ठा i915_request *rq[2] = अणुपूर्ण;
	काष्ठा igt_live_test t;
	पूर्णांक err;

	/* Preempt cancel of ELSP1 */
	GEM_TRACE("%s(%s)\n", __func__, arg->engine->name);
	अगर (igt_live_test_begin(&t, arg->engine->i915,
				__func__, arg->engine->name))
		वापस -EIO;

	rq[0] = spinner_create_request(&arg->a.spin,
				       arg->a.ctx, arg->engine,
				       MI_NOOP); /* no preemption */
	अगर (IS_ERR(rq[0]))
		वापस PTR_ERR(rq[0]);

	clear_bit(CONTEXT_BANNED, &rq[0]->context->flags);
	i915_request_get(rq[0]);
	i915_request_add(rq[0]);
	अगर (!igt_रुको_क्रम_spinner(&arg->a.spin, rq[0])) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	rq[1] = spinner_create_request(&arg->b.spin,
				       arg->b.ctx, arg->engine,
				       MI_ARB_CHECK);
	अगर (IS_ERR(rq[1])) अणु
		err = PTR_ERR(rq[1]);
		जाओ out;
	पूर्ण

	clear_bit(CONTEXT_BANNED, &rq[1]->context->flags);
	i915_request_get(rq[1]);
	err = i915_request_aरुको_dma_fence(rq[1], &rq[0]->fence);
	i915_request_add(rq[1]);
	अगर (err)
		जाओ out;

	पूर्णांकel_context_set_banned(rq[1]->context);
	err = पूर्णांकel_engine_pulse(arg->engine);
	अगर (err)
		जाओ out;

	igt_spinner_end(&arg->a.spin);
	err = रुको_क्रम_reset(arg->engine, rq[1], HZ / 2);
	अगर (err)
		जाओ out;

	अगर (rq[0]->fence.error != 0) अणु
		pr_err("Normal inflight0 request did not complete\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (rq[1]->fence.error != -EIO) अणु
		pr_err("Cancelled inflight1 request did not report -EIO\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

out:
	i915_request_put(rq[1]);
	i915_request_put(rq[0]);
	अगर (igt_live_test_end(&t))
		err = -EIO;
	वापस err;
पूर्ण

अटल पूर्णांक __cancel_queued(काष्ठा live_preempt_cancel *arg)
अणु
	काष्ठा i915_request *rq[3] = अणुपूर्ण;
	काष्ठा igt_live_test t;
	पूर्णांक err;

	/* Full ELSP and one in the wings */
	GEM_TRACE("%s(%s)\n", __func__, arg->engine->name);
	अगर (igt_live_test_begin(&t, arg->engine->i915,
				__func__, arg->engine->name))
		वापस -EIO;

	rq[0] = spinner_create_request(&arg->a.spin,
				       arg->a.ctx, arg->engine,
				       MI_ARB_CHECK);
	अगर (IS_ERR(rq[0]))
		वापस PTR_ERR(rq[0]);

	clear_bit(CONTEXT_BANNED, &rq[0]->context->flags);
	i915_request_get(rq[0]);
	i915_request_add(rq[0]);
	अगर (!igt_रुको_क्रम_spinner(&arg->a.spin, rq[0])) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	rq[1] = igt_request_alloc(arg->b.ctx, arg->engine);
	अगर (IS_ERR(rq[1])) अणु
		err = PTR_ERR(rq[1]);
		जाओ out;
	पूर्ण

	clear_bit(CONTEXT_BANNED, &rq[1]->context->flags);
	i915_request_get(rq[1]);
	err = i915_request_aरुको_dma_fence(rq[1], &rq[0]->fence);
	i915_request_add(rq[1]);
	अगर (err)
		जाओ out;

	rq[2] = spinner_create_request(&arg->b.spin,
				       arg->a.ctx, arg->engine,
				       MI_ARB_CHECK);
	अगर (IS_ERR(rq[2])) अणु
		err = PTR_ERR(rq[2]);
		जाओ out;
	पूर्ण

	i915_request_get(rq[2]);
	err = i915_request_aरुको_dma_fence(rq[2], &rq[1]->fence);
	i915_request_add(rq[2]);
	अगर (err)
		जाओ out;

	पूर्णांकel_context_set_banned(rq[2]->context);
	err = पूर्णांकel_engine_pulse(arg->engine);
	अगर (err)
		जाओ out;

	err = रुको_क्रम_reset(arg->engine, rq[2], HZ / 2);
	अगर (err)
		जाओ out;

	अगर (rq[0]->fence.error != -EIO) अणु
		pr_err("Cancelled inflight0 request did not report -EIO\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (rq[1]->fence.error != 0) अणु
		pr_err("Normal inflight1 request did not complete\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (rq[2]->fence.error != -EIO) अणु
		pr_err("Cancelled queued request did not report -EIO\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

out:
	i915_request_put(rq[2]);
	i915_request_put(rq[1]);
	i915_request_put(rq[0]);
	अगर (igt_live_test_end(&t))
		err = -EIO;
	वापस err;
पूर्ण

अटल पूर्णांक __cancel_hostile(काष्ठा live_preempt_cancel *arg)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	/* Preempt cancel non-preemptible spinner in ELSP0 */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_PREEMPT_TIMEOUT))
		वापस 0;

	अगर (!पूर्णांकel_has_reset_engine(arg->engine->gt))
		वापस 0;

	GEM_TRACE("%s(%s)\n", __func__, arg->engine->name);
	rq = spinner_create_request(&arg->a.spin,
				    arg->a.ctx, arg->engine,
				    MI_NOOP); /* preemption disabled */
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	clear_bit(CONTEXT_BANNED, &rq->context->flags);
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (!igt_रुको_क्रम_spinner(&arg->a.spin, rq)) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	पूर्णांकel_context_set_banned(rq->context);
	err = पूर्णांकel_engine_pulse(arg->engine); /* क्रमce reset */
	अगर (err)
		जाओ out;

	err = रुको_क्रम_reset(arg->engine, rq, HZ / 2);
	अगर (err) अणु
		pr_err("Cancelled inflight0 request did not reset\n");
		जाओ out;
	पूर्ण

out:
	i915_request_put(rq);
	अगर (igt_flush_test(arg->engine->i915))
		err = -EIO;
	वापस err;
पूर्ण

अटल व्योम क्रमce_reset_समयout(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->reset_समयout.probability = 999;
	atomic_set(&engine->reset_समयout.बार, -1);
पूर्ण

अटल व्योम cancel_reset_समयout(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स_रखो(&engine->reset_समयout, 0, माप(engine->reset_समयout));
पूर्ण

अटल पूर्णांक __cancel_fail(काष्ठा live_preempt_cancel *arg)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = arg->engine;
	काष्ठा i915_request *rq;
	पूर्णांक err;

	अगर (!IS_ACTIVE(CONFIG_DRM_I915_PREEMPT_TIMEOUT))
		वापस 0;

	अगर (!पूर्णांकel_has_reset_engine(engine->gt))
		वापस 0;

	GEM_TRACE("%s(%s)\n", __func__, engine->name);
	rq = spinner_create_request(&arg->a.spin,
				    arg->a.ctx, engine,
				    MI_NOOP); /* preemption disabled */
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	clear_bit(CONTEXT_BANNED, &rq->context->flags);
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (!igt_रुको_क्रम_spinner(&arg->a.spin, rq)) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	पूर्णांकel_context_set_banned(rq->context);

	err = पूर्णांकel_engine_pulse(engine);
	अगर (err)
		जाओ out;

	क्रमce_reset_समयout(engine);

	/* क्रमce preempt reset [failure] */
	जबतक (!engine->execlists.pending[0])
		पूर्णांकel_engine_flush_submission(engine);
	del_समयr_sync(&engine->execlists.preempt);
	पूर्णांकel_engine_flush_submission(engine);

	cancel_reset_समयout(engine);

	/* after failure, require heartbeats to reset device */
	पूर्णांकel_engine_set_heartbeat(engine, 1);
	err = रुको_क्रम_reset(engine, rq, HZ / 2);
	पूर्णांकel_engine_set_heartbeat(engine,
				   engine->शेषs.heartbeat_पूर्णांकerval_ms);
	अगर (err) अणु
		pr_err("Cancelled inflight0 request did not reset\n");
		जाओ out;
	पूर्ण

out:
	i915_request_put(rq);
	अगर (igt_flush_test(engine->i915))
		err = -EIO;
	वापस err;
पूर्ण

अटल पूर्णांक live_preempt_cancel(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा live_preempt_cancel data;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;

	/*
	 * To cancel an inflight context, we need to first हटाओ it from the
	 * GPU. That sounds like preemption! Plus a little bit of bookkeeping.
	 */

	अगर (preempt_client_init(gt, &data.a))
		वापस -ENOMEM;
	अगर (preempt_client_init(gt, &data.b))
		जाओ err_client_a;

	क्रम_each_engine(data.engine, gt, id) अणु
		अगर (!पूर्णांकel_engine_has_preemption(data.engine))
			जारी;

		err = __cancel_active0(&data);
		अगर (err)
			जाओ err_wedged;

		err = __cancel_active1(&data);
		अगर (err)
			जाओ err_wedged;

		err = __cancel_queued(&data);
		अगर (err)
			जाओ err_wedged;

		err = __cancel_hostile(&data);
		अगर (err)
			जाओ err_wedged;

		err = __cancel_fail(&data);
		अगर (err)
			जाओ err_wedged;
	पूर्ण

	err = 0;
err_client_b:
	preempt_client_fini(&data.b);
err_client_a:
	preempt_client_fini(&data.a);
	वापस err;

err_wedged:
	GEM_TRACE_DUMP();
	igt_spinner_end(&data.b.spin);
	igt_spinner_end(&data.a.spin);
	पूर्णांकel_gt_set_wedged(gt);
	जाओ err_client_b;
पूर्ण

अटल पूर्णांक live_suppress_self_preempt(व्योम *arg)
अणु
	काष्ठा i915_sched_attr attr = अणु .priority = I915_PRIORITY_MAX पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा preempt_client a, b;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;

	/*
	 * Verअगरy that अगर a preemption request करोes not cause a change in
	 * the current execution order, the preempt-to-idle injection is
	 * skipped and that we करो not accidentally apply it after the CS
	 * completion event.
	 */

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0; /* presume black blox */

	अगर (पूर्णांकel_vgpu_active(gt->i915))
		वापस 0; /* GVT क्रमces single port & request submission */

	अगर (preempt_client_init(gt, &a))
		वापस -ENOMEM;
	अगर (preempt_client_init(gt, &b))
		जाओ err_client_a;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq_a, *rq_b;
		पूर्णांक depth;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (igt_flush_test(gt->i915))
			जाओ err_wedged;

		st_engine_heartbeat_disable(engine);
		engine->execlists.preempt_hang.count = 0;

		rq_a = spinner_create_request(&a.spin,
					      a.ctx, engine,
					      MI_NOOP);
		अगर (IS_ERR(rq_a)) अणु
			err = PTR_ERR(rq_a);
			st_engine_heartbeat_enable(engine);
			जाओ err_client_b;
		पूर्ण

		i915_request_add(rq_a);
		अगर (!igt_रुको_क्रम_spinner(&a.spin, rq_a)) अणु
			pr_err("First client failed to start\n");
			st_engine_heartbeat_enable(engine);
			जाओ err_wedged;
		पूर्ण

		/* Keep postponing the समयr to aव्योम premature slicing */
		mod_समयr(&engine->execlists.समयr, jअगरfies + HZ);
		क्रम (depth = 0; depth < 8; depth++) अणु
			rq_b = spinner_create_request(&b.spin,
						      b.ctx, engine,
						      MI_NOOP);
			अगर (IS_ERR(rq_b)) अणु
				err = PTR_ERR(rq_b);
				st_engine_heartbeat_enable(engine);
				जाओ err_client_b;
			पूर्ण
			i915_request_add(rq_b);

			GEM_BUG_ON(i915_request_completed(rq_a));
			engine->schedule(rq_a, &attr);
			igt_spinner_end(&a.spin);

			अगर (!igt_रुको_क्रम_spinner(&b.spin, rq_b)) अणु
				pr_err("Second client failed to start\n");
				st_engine_heartbeat_enable(engine);
				जाओ err_wedged;
			पूर्ण

			swap(a, b);
			rq_a = rq_b;
		पूर्ण
		igt_spinner_end(&a.spin);

		अगर (engine->execlists.preempt_hang.count) अणु
			pr_err("Preemption on %s recorded x%d, depth %d; should have been suppressed!\n",
			       engine->name,
			       engine->execlists.preempt_hang.count,
			       depth);
			st_engine_heartbeat_enable(engine);
			err = -EINVAL;
			जाओ err_client_b;
		पूर्ण

		st_engine_heartbeat_enable(engine);
		अगर (igt_flush_test(gt->i915))
			जाओ err_wedged;
	पूर्ण

	err = 0;
err_client_b:
	preempt_client_fini(&b);
err_client_a:
	preempt_client_fini(&a);
	वापस err;

err_wedged:
	igt_spinner_end(&b.spin);
	igt_spinner_end(&a.spin);
	पूर्णांकel_gt_set_wedged(gt);
	err = -EIO;
	जाओ err_client_b;
पूर्ण

अटल पूर्णांक live_chain_preempt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा preempt_client hi, lo;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;

	/*
	 * Build a chain AB...BA between two contexts (A, B) and request
	 * preemption of the last request. It should then complete beक्रमe
	 * the previously submitted spinner in B.
	 */

	अगर (preempt_client_init(gt, &hi))
		वापस -ENOMEM;

	अगर (preempt_client_init(gt, &lo))
		जाओ err_client_hi;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_sched_attr attr = अणु .priority = I915_PRIORITY_MAX पूर्ण;
		काष्ठा igt_live_test t;
		काष्ठा i915_request *rq;
		पूर्णांक ring_size, count, i;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		rq = spinner_create_request(&lo.spin,
					    lo.ctx, engine,
					    MI_ARB_CHECK);
		अगर (IS_ERR(rq))
			जाओ err_wedged;

		i915_request_get(rq);
		i915_request_add(rq);

		ring_size = rq->wa_tail - rq->head;
		अगर (ring_size < 0)
			ring_size += rq->ring->size;
		ring_size = rq->ring->size / ring_size;
		pr_debug("%s(%s): Using maximum of %d requests\n",
			 __func__, engine->name, ring_size);

		igt_spinner_end(&lo.spin);
		अगर (i915_request_रुको(rq, 0, HZ / 2) < 0) अणु
			pr_err("Timed out waiting to flush %s\n", engine->name);
			i915_request_put(rq);
			जाओ err_wedged;
		पूर्ण
		i915_request_put(rq);

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			जाओ err_wedged;
		पूर्ण

		क्रम_each_prime_number_from(count, 1, ring_size) अणु
			rq = spinner_create_request(&hi.spin,
						    hi.ctx, engine,
						    MI_ARB_CHECK);
			अगर (IS_ERR(rq))
				जाओ err_wedged;
			i915_request_add(rq);
			अगर (!igt_रुको_क्रम_spinner(&hi.spin, rq))
				जाओ err_wedged;

			rq = spinner_create_request(&lo.spin,
						    lo.ctx, engine,
						    MI_ARB_CHECK);
			अगर (IS_ERR(rq))
				जाओ err_wedged;
			i915_request_add(rq);

			क्रम (i = 0; i < count; i++) अणु
				rq = igt_request_alloc(lo.ctx, engine);
				अगर (IS_ERR(rq))
					जाओ err_wedged;
				i915_request_add(rq);
			पूर्ण

			rq = igt_request_alloc(hi.ctx, engine);
			अगर (IS_ERR(rq))
				जाओ err_wedged;

			i915_request_get(rq);
			i915_request_add(rq);
			engine->schedule(rq, &attr);

			igt_spinner_end(&hi.spin);
			अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
				काष्ठा drm_prपूर्णांकer p =
					drm_info_prपूर्णांकer(gt->i915->drm.dev);

				pr_err("Failed to preempt over chain of %d\n",
				       count);
				पूर्णांकel_engine_dump(engine, &p,
						  "%s\n", engine->name);
				i915_request_put(rq);
				जाओ err_wedged;
			पूर्ण
			igt_spinner_end(&lo.spin);
			i915_request_put(rq);

			rq = igt_request_alloc(lo.ctx, engine);
			अगर (IS_ERR(rq))
				जाओ err_wedged;

			i915_request_get(rq);
			i915_request_add(rq);

			अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
				काष्ठा drm_prपूर्णांकer p =
					drm_info_prपूर्णांकer(gt->i915->drm.dev);

				pr_err("Failed to flush low priority chain of %d requests\n",
				       count);
				पूर्णांकel_engine_dump(engine, &p,
						  "%s\n", engine->name);

				i915_request_put(rq);
				जाओ err_wedged;
			पूर्ण
			i915_request_put(rq);
		पूर्ण

		अगर (igt_live_test_end(&t)) अणु
			err = -EIO;
			जाओ err_wedged;
		पूर्ण
	पूर्ण

	err = 0;
err_client_lo:
	preempt_client_fini(&lo);
err_client_hi:
	preempt_client_fini(&hi);
	वापस err;

err_wedged:
	igt_spinner_end(&hi.spin);
	igt_spinner_end(&lo.spin);
	पूर्णांकel_gt_set_wedged(gt);
	err = -EIO;
	जाओ err_client_lo;
पूर्ण

अटल पूर्णांक create_gang(काष्ठा पूर्णांकel_engine_cs *engine,
		       काष्ठा i915_request **prev)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	u32 *cs;
	पूर्णांक err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	obj = i915_gem_object_create_पूर्णांकernal(engine->i915, 4096);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ err_ce;
	पूर्ण

	vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_obj;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ err_obj;

	cs = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_obj;
	पूर्ण

	/* Semaphore target: spin until zero */
	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;

	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_EQ_SDD;
	*cs++ = 0;
	*cs++ = lower_32_bits(vma->node.start);
	*cs++ = upper_32_bits(vma->node.start);

	अगर (*prev) अणु
		u64 offset = (*prev)->batch->node.start;

		/* Terminate the spinner in the next lower priority batch. */
		*cs++ = MI_STORE_DWORD_IMM_GEN4;
		*cs++ = lower_32_bits(offset);
		*cs++ = upper_32_bits(offset);
		*cs++ = 0;
	पूर्ण

	*cs++ = MI_BATCH_BUFFER_END;
	i915_gem_object_flush_map(obj);
	i915_gem_object_unpin_map(obj);

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_obj;
	पूर्ण

	rq->batch = i915_vma_get(vma);
	i915_request_get(rq);

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, false);
	अगर (!err)
		err = i915_vma_move_to_active(vma, rq, 0);
	अगर (!err)
		err = rq->engine->emit_bb_start(rq,
						vma->node.start,
						PAGE_SIZE, 0);
	i915_vma_unlock(vma);
	i915_request_add(rq);
	अगर (err)
		जाओ err_rq;

	i915_gem_object_put(obj);
	पूर्णांकel_context_put(ce);

	rq->mock.link.next = &(*prev)->mock.link;
	*prev = rq;
	वापस 0;

err_rq:
	i915_vma_put(rq->batch);
	i915_request_put(rq);
err_obj:
	i915_gem_object_put(obj);
err_ce:
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक __live_preempt_ring(काष्ठा पूर्णांकel_engine_cs *engine,
			       काष्ठा igt_spinner *spin,
			       पूर्णांक queue_sz, पूर्णांक ring_sz)
अणु
	काष्ठा पूर्णांकel_context *ce[2] = अणुपूर्ण;
	काष्ठा i915_request *rq;
	काष्ठा igt_live_test t;
	पूर्णांक err = 0;
	पूर्णांक n;

	अगर (igt_live_test_begin(&t, engine->i915, __func__, engine->name))
		वापस -EIO;

	क्रम (n = 0; n < ARRAY_SIZE(ce); n++) अणु
		काष्ठा पूर्णांकel_context *पंचांगp;

		पंचांगp = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(पंचांगp)) अणु
			err = PTR_ERR(पंचांगp);
			जाओ err_ce;
		पूर्ण

		पंचांगp->ring = __पूर्णांकel_context_ring_size(ring_sz);

		err = पूर्णांकel_context_pin(पंचांगp);
		अगर (err) अणु
			पूर्णांकel_context_put(पंचांगp);
			जाओ err_ce;
		पूर्ण

		स_रखो32(पंचांगp->ring->vaddr,
			 0xdeadbeef, /* trigger a hang अगर executed */
			 पंचांगp->ring->vma->size / माप(u32));

		ce[n] = पंचांगp;
	पूर्ण

	rq = igt_spinner_create_request(spin, ce[0], MI_ARB_CHECK);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_ce;
	पूर्ण

	i915_request_get(rq);
	rq->sched.attr.priority = I915_PRIORITY_BARRIER;
	i915_request_add(rq);

	अगर (!igt_रुको_क्रम_spinner(spin, rq)) अणु
		पूर्णांकel_gt_set_wedged(engine->gt);
		i915_request_put(rq);
		err = -ETIME;
		जाओ err_ce;
	पूर्ण

	/* Fill the ring, until we will cause a wrap */
	n = 0;
	जबतक (ce[0]->ring->tail - rq->wa_tail <= queue_sz) अणु
		काष्ठा i915_request *पंचांगp;

		पंचांगp = पूर्णांकel_context_create_request(ce[0]);
		अगर (IS_ERR(पंचांगp)) अणु
			err = PTR_ERR(पंचांगp);
			i915_request_put(rq);
			जाओ err_ce;
		पूर्ण

		i915_request_add(पंचांगp);
		पूर्णांकel_engine_flush_submission(engine);
		n++;
	पूर्ण
	पूर्णांकel_engine_flush_submission(engine);
	pr_debug("%s: Filled %d with %d nop tails {size:%x, tail:%x, emit:%x, rq.tail:%x}\n",
		 engine->name, queue_sz, n,
		 ce[0]->ring->size,
		 ce[0]->ring->tail,
		 ce[0]->ring->emit,
		 rq->tail);
	i915_request_put(rq);

	/* Create a second request to preempt the first ring */
	rq = पूर्णांकel_context_create_request(ce[1]);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_ce;
	पूर्ण

	rq->sched.attr.priority = I915_PRIORITY_BARRIER;
	i915_request_get(rq);
	i915_request_add(rq);

	err = रुको_क्रम_submit(engine, rq, HZ / 2);
	i915_request_put(rq);
	अगर (err) अणु
		pr_err("%s: preemption request was not submitted\n",
		       engine->name);
		err = -ETIME;
	पूर्ण

	pr_debug("%s: ring[0]:{ tail:%x, emit:%x }, ring[1]:{ tail:%x, emit:%x }\n",
		 engine->name,
		 ce[0]->ring->tail, ce[0]->ring->emit,
		 ce[1]->ring->tail, ce[1]->ring->emit);

err_ce:
	पूर्णांकel_engine_flush_submission(engine);
	igt_spinner_end(spin);
	क्रम (n = 0; n < ARRAY_SIZE(ce); n++) अणु
		अगर (IS_ERR_OR_शून्य(ce[n]))
			अवरोध;

		पूर्णांकel_context_unpin(ce[n]);
		पूर्णांकel_context_put(ce[n]);
	पूर्ण
	अगर (igt_live_test_end(&t))
		err = -EIO;
	वापस err;
पूर्ण

अटल पूर्णांक live_preempt_ring(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा igt_spinner spin;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Check that we rollback large chunks of a ring in order to करो a
	 * preemption event. Similar to live_unlite_ring, but looking at
	 * ring size rather than the impact of पूर्णांकel_ring_direction().
	 */

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांक n;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		st_engine_heartbeat_disable(engine);

		क्रम (n = 0; n <= 3; n++) अणु
			err = __live_preempt_ring(engine, &spin,
						  n * SZ_4K / 4, SZ_4K);
			अगर (err)
				अवरोध;
		पूर्ण

		st_engine_heartbeat_enable(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_preempt_gang(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * Build as दीर्घ a chain of preempters as we can, with each
	 * request higher priority than the last. Once we are पढ़ोy, we release
	 * the last batch which then precolates करोwn the chain, each releasing
	 * the next oldest in turn. The पूर्णांकent is to simply push as hard as we
	 * can with the number of preemptions, trying to exceed narrow HW
	 * limits. At a minimum, we insist that we can sort all the user
	 * high priority levels पूर्णांकo execution order.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq = शून्य;
		काष्ठा igt_live_test t;
		IGT_TIMEOUT(end_समय);
		पूर्णांक prio = 0;
		पूर्णांक err = 0;
		u32 *cs;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name))
			वापस -EIO;

		करो अणु
			काष्ठा i915_sched_attr attr = अणु .priority = prio++ पूर्ण;

			err = create_gang(engine, &rq);
			अगर (err)
				अवरोध;

			/* Submit each spinner at increasing priority */
			engine->schedule(rq, &attr);
		पूर्ण जबतक (prio <= I915_PRIORITY_MAX &&
			 !__igt_समयout(end_समय, शून्य));
		pr_debug("%s: Preempt chain of %d requests\n",
			 engine->name, prio);

		/*
		 * Such that the last spinner is the highest priority and
		 * should execute first. When that spinner completes,
		 * it will terminate the next lowest spinner until there
		 * are no more spinners and the gang is complete.
		 */
		cs = i915_gem_object_pin_map_unlocked(rq->batch->obj, I915_MAP_WC);
		अगर (!IS_ERR(cs)) अणु
			*cs = 0;
			i915_gem_object_unpin_map(rq->batch->obj);
		पूर्ण अन्यथा अणु
			err = PTR_ERR(cs);
			पूर्णांकel_gt_set_wedged(gt);
		पूर्ण

		जबतक (rq) अणु /* रुको क्रम each rq from highest to lowest prio */
			काष्ठा i915_request *n = list_next_entry(rq, mock.link);

			अगर (err == 0 && i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
				काष्ठा drm_prपूर्णांकer p =
					drm_info_prपूर्णांकer(engine->i915->drm.dev);

				pr_err("Failed to flush chain of %d requests, at %d\n",
				       prio, rq_prio(rq));
				पूर्णांकel_engine_dump(engine, &p,
						  "%s\n", engine->name);

				err = -ETIME;
			पूर्ण

			i915_vma_put(rq->batch);
			i915_request_put(rq);
			rq = n;
		पूर्ण

		अगर (igt_live_test_end(&t))
			err = -EIO;
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i915_vma *
create_gpr_user(काष्ठा पूर्णांकel_engine_cs *engine,
		काष्ठा i915_vma *result,
		अचिन्हित पूर्णांक offset)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक i;

	obj = i915_gem_object_create_पूर्णांकernal(engine->i915, 4096);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, result->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस vma;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err) अणु
		i915_vma_put(vma);
		वापस ERR_PTR(err);
	पूर्ण

	cs = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(cs)) अणु
		i915_vma_put(vma);
		वापस ERR_CAST(cs);
	पूर्ण

	/* All GPR are clear क्रम new contexts. We use GPR(0) as a स्थिरant */
	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = CS_GPR(engine, 0);
	*cs++ = 1;

	क्रम (i = 1; i < NUM_GPR; i++) अणु
		u64 addr;

		/*
		 * Perक्रमm: GPR[i]++
		 *
		 * As we पढ़ो and ग_लिखो पूर्णांकo the context saved GPR[i], अगर
		 * we restart this batch buffer from an earlier poपूर्णांक, we
		 * will repeat the increment and store a value > 1.
		 */
		*cs++ = MI_MATH(4);
		*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCA, MI_MATH_REG(i));
		*cs++ = MI_MATH_LOAD(MI_MATH_REG_SRCB, MI_MATH_REG(0));
		*cs++ = MI_MATH_ADD;
		*cs++ = MI_MATH_STORE(MI_MATH_REG(i), MI_MATH_REG_ACCU);

		addr = result->node.start + offset + i * माप(*cs);
		*cs++ = MI_STORE_REGISTER_MEM_GEN8;
		*cs++ = CS_GPR(engine, 2 * i);
		*cs++ = lower_32_bits(addr);
		*cs++ = upper_32_bits(addr);

		*cs++ = MI_SEMAPHORE_WAIT |
			MI_SEMAPHORE_POLL |
			MI_SEMAPHORE_SAD_GTE_SDD;
		*cs++ = i;
		*cs++ = lower_32_bits(result->node.start);
		*cs++ = upper_32_bits(result->node.start);
	पूर्ण

	*cs++ = MI_BATCH_BUFFER_END;
	i915_gem_object_flush_map(obj);
	i915_gem_object_unpin_map(obj);

	वापस vma;
पूर्ण

अटल काष्ठा i915_vma *create_global(काष्ठा पूर्णांकel_gt *gt, माप_प्रकार sz)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, sz);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस vma;
	पूर्ण

	err = i915_ggtt_pin(vma, शून्य, 0, 0);
	अगर (err) अणु
		i915_vma_put(vma);
		वापस ERR_PTR(err);
	पूर्ण

	वापस vma;
पूर्ण

अटल काष्ठा i915_request *
create_gpr_client(काष्ठा पूर्णांकel_engine_cs *engine,
		  काष्ठा i915_vma *global,
		  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा i915_vma *batch, *vma;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	पूर्णांक err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस ERR_CAST(ce);

	vma = i915_vma_instance(global->obj, ce->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ out_ce;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ out_ce;

	batch = create_gpr_user(engine, vma, offset);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_vma;
	पूर्ण

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_batch;
	पूर्ण

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, false);
	अगर (!err)
		err = i915_vma_move_to_active(vma, rq, 0);
	i915_vma_unlock(vma);

	i915_vma_lock(batch);
	अगर (!err)
		err = i915_request_aरुको_object(rq, batch->obj, false);
	अगर (!err)
		err = i915_vma_move_to_active(batch, rq, 0);
	अगर (!err)
		err = rq->engine->emit_bb_start(rq,
						batch->node.start,
						PAGE_SIZE, 0);
	i915_vma_unlock(batch);
	i915_vma_unpin(batch);

	अगर (!err)
		i915_request_get(rq);
	i915_request_add(rq);

out_batch:
	i915_vma_put(batch);
out_vma:
	i915_vma_unpin(vma);
out_ce:
	पूर्णांकel_context_put(ce);
	वापस err ? ERR_PTR(err) : rq;
पूर्ण

अटल पूर्णांक preempt_user(काष्ठा पूर्णांकel_engine_cs *engine,
			काष्ठा i915_vma *global,
			पूर्णांक id)
अणु
	काष्ठा i915_sched_attr attr = अणु
		.priority = I915_PRIORITY_MAX
	पूर्ण;
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;
	u32 *cs;

	rq = पूर्णांकel_engine_create_kernel_request(engine);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = i915_ggtt_offset(global);
	*cs++ = 0;
	*cs++ = id;

	पूर्णांकel_ring_advance(rq, cs);

	i915_request_get(rq);
	i915_request_add(rq);

	engine->schedule(rq, &attr);

	अगर (i915_request_रुको(rq, 0, HZ / 2) < 0)
		err = -ETIME;
	i915_request_put(rq);

	वापस err;
पूर्ण

अटल पूर्णांक live_preempt_user(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_vma *global;
	क्रमागत पूर्णांकel_engine_id id;
	u32 *result;
	पूर्णांक err = 0;

	/*
	 * In our other tests, we look at preemption in carefully
	 * controlled conditions in the ringbuffer. Since most of the
	 * समय is spent in user batches, most of our preemptions naturally
	 * occur there. We want to verअगरy that when we preempt inside a batch
	 * we जारी on from the current inकाष्ठाion and करो not roll back
	 * to the start, or another earlier arbitration poपूर्णांक.
	 *
	 * To verअगरy this, we create a batch which is a mixture of
	 * MI_MATH (gpr++) MI_SRM (gpr) and preemption poपूर्णांकs. Then with
	 * a few preempting contexts thrown पूर्णांकo the mix, we look क्रम any
	 * repeated inकाष्ठाions (which show up as incorrect values).
	 */

	global = create_global(gt, 4096);
	अगर (IS_ERR(global))
		वापस PTR_ERR(global);

	result = i915_gem_object_pin_map_unlocked(global->obj, I915_MAP_WC);
	अगर (IS_ERR(result)) अणु
		i915_vma_unpin_and_release(&global, 0);
		वापस PTR_ERR(result);
	पूर्ण

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *client[3] = अणुपूर्ण;
		काष्ठा igt_live_test t;
		पूर्णांक i;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		अगर (IS_GEN(gt->i915, 8) && engine->class != RENDER_CLASS)
			जारी; /* we need per-context GPR */

		अगर (igt_live_test_begin(&t, gt->i915, __func__, engine->name)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण

		स_रखो(result, 0, 4096);

		क्रम (i = 0; i < ARRAY_SIZE(client); i++) अणु
			काष्ठा i915_request *rq;

			rq = create_gpr_client(engine, global,
					       NUM_GPR * i * माप(u32));
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				जाओ end_test;
			पूर्ण

			client[i] = rq;
		पूर्ण

		/* Continuously preempt the set of 3 running contexts */
		क्रम (i = 1; i <= NUM_GPR; i++) अणु
			err = preempt_user(engine, global, i);
			अगर (err)
				जाओ end_test;
		पूर्ण

		अगर (READ_ONCE(result[0]) != NUM_GPR) अणु
			pr_err("%s: Failed to release semaphore\n",
			       engine->name);
			err = -EIO;
			जाओ end_test;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(client); i++) अणु
			पूर्णांक gpr;

			अगर (i915_request_रुको(client[i], 0, HZ / 2) < 0) अणु
				err = -ETIME;
				जाओ end_test;
			पूर्ण

			क्रम (gpr = 1; gpr < NUM_GPR; gpr++) अणु
				अगर (result[NUM_GPR * i + gpr] != 1) अणु
					pr_err("%s: Invalid result, client %d, gpr %d, result: %d\n",
					       engine->name,
					       i, gpr, result[NUM_GPR * i + gpr]);
					err = -EINVAL;
					जाओ end_test;
				पूर्ण
			पूर्ण
		पूर्ण

end_test:
		क्रम (i = 0; i < ARRAY_SIZE(client); i++) अणु
			अगर (!client[i])
				अवरोध;

			i915_request_put(client[i]);
		पूर्ण

		/* Flush the semaphores on error */
		smp_store_mb(result[0], -1);
		अगर (igt_live_test_end(&t))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	i915_vma_unpin_and_release(&global, I915_VMA_RELEASE_MAP);
	वापस err;
पूर्ण

अटल पूर्णांक live_preempt_समयout(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gem_context *ctx_hi, *ctx_lo;
	काष्ठा igt_spinner spin_lo;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = -ENOMEM;

	/*
	 * Check that we क्रमce preemption to occur by cancelling the previous
	 * context अगर it refuses to yield the GPU.
	 */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_PREEMPT_TIMEOUT))
		वापस 0;

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	अगर (igt_spinner_init(&spin_lo, gt))
		वापस -ENOMEM;

	ctx_hi = kernel_context(gt->i915);
	अगर (!ctx_hi)
		जाओ err_spin_lo;
	ctx_hi->sched.priority = I915_CONTEXT_MAX_USER_PRIORITY;

	ctx_lo = kernel_context(gt->i915);
	अगर (!ctx_lo)
		जाओ err_ctx_hi;
	ctx_lo->sched.priority = I915_CONTEXT_MIN_USER_PRIORITY;

	क्रम_each_engine(engine, gt, id) अणु
		अचिन्हित दीर्घ saved_समयout;
		काष्ठा i915_request *rq;

		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		rq = spinner_create_request(&spin_lo, ctx_lo, engine,
					    MI_NOOP); /* preemption disabled */
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_ctx_lo;
		पूर्ण

		i915_request_add(rq);
		अगर (!igt_रुको_क्रम_spinner(&spin_lo, rq)) अणु
			पूर्णांकel_gt_set_wedged(gt);
			err = -EIO;
			जाओ err_ctx_lo;
		पूर्ण

		rq = igt_request_alloc(ctx_hi, engine);
		अगर (IS_ERR(rq)) अणु
			igt_spinner_end(&spin_lo);
			err = PTR_ERR(rq);
			जाओ err_ctx_lo;
		पूर्ण

		/* Flush the previous CS ack beक्रमe changing समयouts */
		जबतक (READ_ONCE(engine->execlists.pending[0]))
			cpu_relax();

		saved_समयout = engine->props.preempt_समयout_ms;
		engine->props.preempt_समयout_ms = 1; /* in ms, -> 1 jअगरfie */

		i915_request_get(rq);
		i915_request_add(rq);

		पूर्णांकel_engine_flush_submission(engine);
		engine->props.preempt_समयout_ms = saved_समयout;

		अगर (i915_request_रुको(rq, 0, HZ / 10) < 0) अणु
			पूर्णांकel_gt_set_wedged(gt);
			i915_request_put(rq);
			err = -ETIME;
			जाओ err_ctx_lo;
		पूर्ण

		igt_spinner_end(&spin_lo);
		i915_request_put(rq);
	पूर्ण

	err = 0;
err_ctx_lo:
	kernel_context_बंद(ctx_lo);
err_ctx_hi:
	kernel_context_बंद(ctx_hi);
err_spin_lo:
	igt_spinner_fini(&spin_lo);
	वापस err;
पूर्ण

अटल पूर्णांक अक्रमom_range(काष्ठा rnd_state *rnd, पूर्णांक min, पूर्णांक max)
अणु
	वापस i915_pअक्रमom_u32_max_state(max - min, rnd) + min;
पूर्ण

अटल पूर्णांक अक्रमom_priority(काष्ठा rnd_state *rnd)
अणु
	वापस अक्रमom_range(rnd, I915_PRIORITY_MIN, I915_PRIORITY_MAX);
पूर्ण

काष्ठा preempt_smoke अणु
	काष्ठा पूर्णांकel_gt *gt;
	काष्ठा i915_gem_context **contexts;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा drm_i915_gem_object *batch;
	अचिन्हित पूर्णांक ncontext;
	काष्ठा rnd_state prng;
	अचिन्हित दीर्घ count;
पूर्ण;

अटल काष्ठा i915_gem_context *smoke_context(काष्ठा preempt_smoke *smoke)
अणु
	वापस smoke->contexts[i915_pअक्रमom_u32_max_state(smoke->ncontext,
							  &smoke->prng)];
पूर्ण

अटल पूर्णांक smoke_submit(काष्ठा preempt_smoke *smoke,
			काष्ठा i915_gem_context *ctx, पूर्णांक prio,
			काष्ठा drm_i915_gem_object *batch)
अणु
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma = शून्य;
	पूर्णांक err = 0;

	अगर (batch) अणु
		काष्ठा i915_address_space *vm;

		vm = i915_gem_context_get_vm_rcu(ctx);
		vma = i915_vma_instance(batch, vm, शून्य);
		i915_vm_put(vm);
		अगर (IS_ERR(vma))
			वापस PTR_ERR(vma);

		err = i915_vma_pin(vma, 0, 0, PIN_USER);
		अगर (err)
			वापस err;
	पूर्ण

	ctx->sched.priority = prio;

	rq = igt_request_alloc(ctx, smoke->engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ unpin;
	पूर्ण

	अगर (vma) अणु
		i915_vma_lock(vma);
		err = i915_request_aरुको_object(rq, vma->obj, false);
		अगर (!err)
			err = i915_vma_move_to_active(vma, rq, 0);
		अगर (!err)
			err = rq->engine->emit_bb_start(rq,
							vma->node.start,
							PAGE_SIZE, 0);
		i915_vma_unlock(vma);
	पूर्ण

	i915_request_add(rq);

unpin:
	अगर (vma)
		i915_vma_unpin(vma);

	वापस err;
पूर्ण

अटल पूर्णांक smoke_crescenकरो_thपढ़ो(व्योम *arg)
अणु
	काष्ठा preempt_smoke *smoke = arg;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;

	count = 0;
	करो अणु
		काष्ठा i915_gem_context *ctx = smoke_context(smoke);
		पूर्णांक err;

		err = smoke_submit(smoke,
				   ctx, count % I915_PRIORITY_MAX,
				   smoke->batch);
		अगर (err)
			वापस err;

		count++;
	पूर्ण जबतक (count < smoke->ncontext && !__igt_समयout(end_समय, शून्य));

	smoke->count = count;
	वापस 0;
पूर्ण

अटल पूर्णांक smoke_crescenकरो(काष्ठा preempt_smoke *smoke, अचिन्हित पूर्णांक flags)
#घोषणा BATCH BIT(0)
अणु
	काष्ठा task_काष्ठा *tsk[I915_NUM_ENGINES] = अणुपूर्ण;
	काष्ठा preempt_smoke arg[I915_NUM_ENGINES];
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	अचिन्हित दीर्घ count;
	पूर्णांक err = 0;

	क्रम_each_engine(engine, smoke->gt, id) अणु
		arg[id] = *smoke;
		arg[id].engine = engine;
		अगर (!(flags & BATCH))
			arg[id].batch = शून्य;
		arg[id].count = 0;

		tsk[id] = kthपढ़ो_run(smoke_crescenकरो_thपढ़ो, &arg,
				      "igt/smoke:%d", id);
		अगर (IS_ERR(tsk[id])) अणु
			err = PTR_ERR(tsk[id]);
			अवरोध;
		पूर्ण
		get_task_काष्ठा(tsk[id]);
	पूर्ण

	yield(); /* start all thपढ़ोs beक्रमe we kthपढ़ो_stop() */

	count = 0;
	क्रम_each_engine(engine, smoke->gt, id) अणु
		पूर्णांक status;

		अगर (IS_ERR_OR_शून्य(tsk[id]))
			जारी;

		status = kthपढ़ो_stop(tsk[id]);
		अगर (status && !err)
			err = status;

		count += arg[id].count;

		put_task_काष्ठा(tsk[id]);
	पूर्ण

	pr_info("Submitted %lu crescendo:%x requests across %d engines and %d contexts\n",
		count, flags, smoke->gt->info.num_engines, smoke->ncontext);
	वापस 0;
पूर्ण

अटल पूर्णांक smoke_अक्रमom(काष्ठा preempt_smoke *smoke, अचिन्हित पूर्णांक flags)
अणु
	क्रमागत पूर्णांकel_engine_id id;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;

	count = 0;
	करो अणु
		क्रम_each_engine(smoke->engine, smoke->gt, id) अणु
			काष्ठा i915_gem_context *ctx = smoke_context(smoke);
			पूर्णांक err;

			err = smoke_submit(smoke,
					   ctx, अक्रमom_priority(&smoke->prng),
					   flags & BATCH ? smoke->batch : शून्य);
			अगर (err)
				वापस err;

			count++;
		पूर्ण
	पूर्ण जबतक (count < smoke->ncontext && !__igt_समयout(end_समय, शून्य));

	pr_info("Submitted %lu random:%x requests across %d engines and %d contexts\n",
		count, flags, smoke->gt->info.num_engines, smoke->ncontext);
	वापस 0;
पूर्ण

अटल पूर्णांक live_preempt_smoke(व्योम *arg)
अणु
	काष्ठा preempt_smoke smoke = अणु
		.gt = arg,
		.prng = I915_RND_STATE_INITIALIZER(i915_selftest.अक्रमom_seed),
		.ncontext = 256,
	पूर्ण;
	स्थिर अचिन्हित पूर्णांक phase[] = अणु 0, BATCH पूर्ण;
	काष्ठा igt_live_test t;
	पूर्णांक err = -ENOMEM;
	u32 *cs;
	पूर्णांक n;

	smoke.contexts = kदो_स्मृति_array(smoke.ncontext,
				       माप(*smoke.contexts),
				       GFP_KERNEL);
	अगर (!smoke.contexts)
		वापस -ENOMEM;

	smoke.batch =
		i915_gem_object_create_पूर्णांकernal(smoke.gt->i915, PAGE_SIZE);
	अगर (IS_ERR(smoke.batch)) अणु
		err = PTR_ERR(smoke.batch);
		जाओ err_मुक्त;
	पूर्ण

	cs = i915_gem_object_pin_map_unlocked(smoke.batch, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_batch;
	पूर्ण
	क्रम (n = 0; n < PAGE_SIZE / माप(*cs) - 1; n++)
		cs[n] = MI_ARB_CHECK;
	cs[n] = MI_BATCH_BUFFER_END;
	i915_gem_object_flush_map(smoke.batch);
	i915_gem_object_unpin_map(smoke.batch);

	अगर (igt_live_test_begin(&t, smoke.gt->i915, __func__, "all")) अणु
		err = -EIO;
		जाओ err_batch;
	पूर्ण

	क्रम (n = 0; n < smoke.ncontext; n++) अणु
		smoke.contexts[n] = kernel_context(smoke.gt->i915);
		अगर (!smoke.contexts[n])
			जाओ err_ctx;
	पूर्ण

	क्रम (n = 0; n < ARRAY_SIZE(phase); n++) अणु
		err = smoke_crescenकरो(&smoke, phase[n]);
		अगर (err)
			जाओ err_ctx;

		err = smoke_अक्रमom(&smoke, phase[n]);
		अगर (err)
			जाओ err_ctx;
	पूर्ण

err_ctx:
	अगर (igt_live_test_end(&t))
		err = -EIO;

	क्रम (n = 0; n < smoke.ncontext; n++) अणु
		अगर (!smoke.contexts[n])
			अवरोध;
		kernel_context_बंद(smoke.contexts[n]);
	पूर्ण

err_batch:
	i915_gem_object_put(smoke.batch);
err_मुक्त:
	kमुक्त(smoke.contexts);

	वापस err;
पूर्ण

अटल पूर्णांक nop_भव_engine(काष्ठा पूर्णांकel_gt *gt,
			      काष्ठा पूर्णांकel_engine_cs **siblings,
			      अचिन्हित पूर्णांक nsibling,
			      अचिन्हित पूर्णांक nctx,
			      अचिन्हित पूर्णांक flags)
#घोषणा CHAIN BIT(0)
अणु
	IGT_TIMEOUT(end_समय);
	काष्ठा i915_request *request[16] = अणुपूर्ण;
	काष्ठा पूर्णांकel_context *ve[16];
	अचिन्हित दीर्घ n, prime, nc;
	काष्ठा igt_live_test t;
	kसमय_प्रकार बार[2] = अणुपूर्ण;
	पूर्णांक err;

	GEM_BUG_ON(!nctx || nctx > ARRAY_SIZE(ve));

	क्रम (n = 0; n < nctx; n++) अणु
		ve[n] = पूर्णांकel_execlists_create_भव(siblings, nsibling);
		अगर (IS_ERR(ve[n])) अणु
			err = PTR_ERR(ve[n]);
			nctx = n;
			जाओ out;
		पूर्ण

		err = पूर्णांकel_context_pin(ve[n]);
		अगर (err) अणु
			पूर्णांकel_context_put(ve[n]);
			nctx = n;
			जाओ out;
		पूर्ण
	पूर्ण

	err = igt_live_test_begin(&t, gt->i915, __func__, ve[0]->engine->name);
	अगर (err)
		जाओ out;

	क्रम_each_prime_number_from(prime, 1, 8192) अणु
		बार[1] = kसमय_get_raw();

		अगर (flags & CHAIN) अणु
			क्रम (nc = 0; nc < nctx; nc++) अणु
				क्रम (n = 0; n < prime; n++) अणु
					काष्ठा i915_request *rq;

					rq = i915_request_create(ve[nc]);
					अगर (IS_ERR(rq)) अणु
						err = PTR_ERR(rq);
						जाओ out;
					पूर्ण

					अगर (request[nc])
						i915_request_put(request[nc]);
					request[nc] = i915_request_get(rq);
					i915_request_add(rq);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (n = 0; n < prime; n++) अणु
				क्रम (nc = 0; nc < nctx; nc++) अणु
					काष्ठा i915_request *rq;

					rq = i915_request_create(ve[nc]);
					अगर (IS_ERR(rq)) अणु
						err = PTR_ERR(rq);
						जाओ out;
					पूर्ण

					अगर (request[nc])
						i915_request_put(request[nc]);
					request[nc] = i915_request_get(rq);
					i915_request_add(rq);
				पूर्ण
			पूर्ण
		पूर्ण

		क्रम (nc = 0; nc < nctx; nc++) अणु
			अगर (i915_request_रुको(request[nc], 0, HZ / 10) < 0) अणु
				pr_err("%s(%s): wait for %llx:%lld timed out\n",
				       __func__, ve[0]->engine->name,
				       request[nc]->fence.context,
				       request[nc]->fence.seqno);

				GEM_TRACE("%s(%s) failed at request %llx:%lld\n",
					  __func__, ve[0]->engine->name,
					  request[nc]->fence.context,
					  request[nc]->fence.seqno);
				GEM_TRACE_DUMP();
				पूर्णांकel_gt_set_wedged(gt);
				अवरोध;
			पूर्ण
		पूर्ण

		बार[1] = kसमय_sub(kसमय_get_raw(), बार[1]);
		अगर (prime == 1)
			बार[0] = बार[1];

		क्रम (nc = 0; nc < nctx; nc++) अणु
			i915_request_put(request[nc]);
			request[nc] = शून्य;
		पूर्ण

		अगर (__igt_समयout(end_समय, शून्य))
			अवरोध;
	पूर्ण

	err = igt_live_test_end(&t);
	अगर (err)
		जाओ out;

	pr_info("Requestx%d latencies on %s: 1 = %lluns, %lu = %lluns\n",
		nctx, ve[0]->engine->name, kसमय_प्रकारo_ns(बार[0]),
		prime, भाग64_u64(kसमय_प्रकारo_ns(बार[1]), prime));

out:
	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	क्रम (nc = 0; nc < nctx; nc++) अणु
		i915_request_put(request[nc]);
		पूर्णांकel_context_unpin(ve[nc]);
		पूर्णांकel_context_put(ve[nc]);
	पूर्ण
	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक
__select_siblings(काष्ठा पूर्णांकel_gt *gt,
		  अचिन्हित पूर्णांक class,
		  काष्ठा पूर्णांकel_engine_cs **siblings,
		  bool (*filter)(स्थिर काष्ठा पूर्णांकel_engine_cs *))
अणु
	अचिन्हित पूर्णांक n = 0;
	अचिन्हित पूर्णांक inst;

	क्रम (inst = 0; inst <= MAX_ENGINE_INSTANCE; inst++) अणु
		अगर (!gt->engine_class[class][inst])
			जारी;

		अगर (filter && !filter(gt->engine_class[class][inst]))
			जारी;

		siblings[n++] = gt->engine_class[class][inst];
	पूर्ण

	वापस n;
पूर्ण

अटल अचिन्हित पूर्णांक
select_siblings(काष्ठा पूर्णांकel_gt *gt,
		अचिन्हित पूर्णांक class,
		काष्ठा पूर्णांकel_engine_cs **siblings)
अणु
	वापस __select_siblings(gt, class, siblings, शून्य);
पूर्ण

अटल पूर्णांक live_भव_engine(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *siblings[MAX_ENGINE_INSTANCE + 1];
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	अचिन्हित पूर्णांक class;
	पूर्णांक err;

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		err = nop_भव_engine(gt, &engine, 1, 1, 0);
		अगर (err) अणु
			pr_err("Failed to wrap engine %s: err=%d\n",
			       engine->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	क्रम (class = 0; class <= MAX_ENGINE_CLASS; class++) अणु
		पूर्णांक nsibling, n;

		nsibling = select_siblings(gt, class, siblings);
		अगर (nsibling < 2)
			जारी;

		क्रम (n = 1; n <= nsibling + 1; n++) अणु
			err = nop_भव_engine(gt, siblings, nsibling,
						 n, 0);
			अगर (err)
				वापस err;
		पूर्ण

		err = nop_भव_engine(gt, siblings, nsibling, n, CHAIN);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mask_भव_engine(काष्ठा पूर्णांकel_gt *gt,
			       काष्ठा पूर्णांकel_engine_cs **siblings,
			       अचिन्हित पूर्णांक nsibling)
अणु
	काष्ठा i915_request *request[MAX_ENGINE_INSTANCE + 1];
	काष्ठा पूर्णांकel_context *ve;
	काष्ठा igt_live_test t;
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	/*
	 * Check that by setting the execution mask on a request, we can
	 * restrict it to our desired engine within the भव engine.
	 */

	ve = पूर्णांकel_execlists_create_भव(siblings, nsibling);
	अगर (IS_ERR(ve)) अणु
		err = PTR_ERR(ve);
		जाओ out_बंद;
	पूर्ण

	err = पूर्णांकel_context_pin(ve);
	अगर (err)
		जाओ out_put;

	err = igt_live_test_begin(&t, gt->i915, __func__, ve->engine->name);
	अगर (err)
		जाओ out_unpin;

	क्रम (n = 0; n < nsibling; n++) अणु
		request[n] = i915_request_create(ve);
		अगर (IS_ERR(request[n])) अणु
			err = PTR_ERR(request[n]);
			nsibling = n;
			जाओ out;
		पूर्ण

		/* Reverse order as it's more likely to be unnatural */
		request[n]->execution_mask = siblings[nsibling - n - 1]->mask;

		i915_request_get(request[n]);
		i915_request_add(request[n]);
	पूर्ण

	क्रम (n = 0; n < nsibling; n++) अणु
		अगर (i915_request_रुको(request[n], 0, HZ / 10) < 0) अणु
			pr_err("%s(%s): wait for %llx:%lld timed out\n",
			       __func__, ve->engine->name,
			       request[n]->fence.context,
			       request[n]->fence.seqno);

			GEM_TRACE("%s(%s) failed at request %llx:%lld\n",
				  __func__, ve->engine->name,
				  request[n]->fence.context,
				  request[n]->fence.seqno);
			GEM_TRACE_DUMP();
			पूर्णांकel_gt_set_wedged(gt);
			err = -EIO;
			जाओ out;
		पूर्ण

		अगर (request[n]->engine != siblings[nsibling - n - 1]) अणु
			pr_err("Executed on wrong sibling '%s', expected '%s'\n",
			       request[n]->engine->name,
			       siblings[nsibling - n - 1]->name);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	err = igt_live_test_end(&t);
out:
	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	क्रम (n = 0; n < nsibling; n++)
		i915_request_put(request[n]);

out_unpin:
	पूर्णांकel_context_unpin(ve);
out_put:
	पूर्णांकel_context_put(ve);
out_बंद:
	वापस err;
पूर्ण

अटल पूर्णांक live_भव_mask(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *siblings[MAX_ENGINE_INSTANCE + 1];
	अचिन्हित पूर्णांक class;
	पूर्णांक err;

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	क्रम (class = 0; class <= MAX_ENGINE_CLASS; class++) अणु
		अचिन्हित पूर्णांक nsibling;

		nsibling = select_siblings(gt, class, siblings);
		अगर (nsibling < 2)
			जारी;

		err = mask_भव_engine(gt, siblings, nsibling);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक slicein_भव_engine(काष्ठा पूर्णांकel_gt *gt,
				  काष्ठा पूर्णांकel_engine_cs **siblings,
				  अचिन्हित पूर्णांक nsibling)
अणु
	स्थिर दीर्घ समयout = slice_समयout(siblings[0]);
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	काष्ठा igt_spinner spin;
	अचिन्हित पूर्णांक n;
	पूर्णांक err = 0;

	/*
	 * Virtual requests must take part in बारlicing on the target engines.
	 */

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	क्रम (n = 0; n < nsibling; n++) अणु
		ce = पूर्णांकel_context_create(siblings[n]);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out;
		पूर्ण

		rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out;
		पूर्ण

		i915_request_add(rq);
	पूर्ण

	ce = पूर्णांकel_execlists_create_भव(siblings, nsibling);
	अगर (IS_ERR(ce)) अणु
		err = PTR_ERR(ce);
		जाओ out;
	पूर्ण

	rq = पूर्णांकel_context_create_request(ce);
	पूर्णांकel_context_put(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out;
	पूर्ण

	i915_request_get(rq);
	i915_request_add(rq);
	अगर (i915_request_रुको(rq, 0, समयout) < 0) अणु
		GEM_TRACE_ERR("%s(%s) failed to slice in virtual request\n",
			      __func__, rq->engine->name);
		GEM_TRACE_DUMP();
		पूर्णांकel_gt_set_wedged(gt);
		err = -EIO;
	पूर्ण
	i915_request_put(rq);

out:
	igt_spinner_end(&spin);
	अगर (igt_flush_test(gt->i915))
		err = -EIO;
	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक sliceout_भव_engine(काष्ठा पूर्णांकel_gt *gt,
				   काष्ठा पूर्णांकel_engine_cs **siblings,
				   अचिन्हित पूर्णांक nsibling)
अणु
	स्थिर दीर्घ समयout = slice_समयout(siblings[0]);
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	काष्ठा igt_spinner spin;
	अचिन्हित पूर्णांक n;
	पूर्णांक err = 0;

	/*
	 * Virtual requests must allow others a fair बारlice.
	 */

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	/* XXX We करो not handle oversubscription and fairness with normal rq */
	क्रम (n = 0; n < nsibling; n++) अणु
		ce = पूर्णांकel_execlists_create_भव(siblings, nsibling);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out;
		पूर्ण

		rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out;
		पूर्ण

		i915_request_add(rq);
	पूर्ण

	क्रम (n = 0; !err && n < nsibling; n++) अणु
		ce = पूर्णांकel_context_create(siblings[n]);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out;
		पूर्ण

		rq = पूर्णांकel_context_create_request(ce);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out;
		पूर्ण

		i915_request_get(rq);
		i915_request_add(rq);
		अगर (i915_request_रुको(rq, 0, समयout) < 0) अणु
			GEM_TRACE_ERR("%s(%s) failed to slice out virtual request\n",
				      __func__, siblings[n]->name);
			GEM_TRACE_DUMP();
			पूर्णांकel_gt_set_wedged(gt);
			err = -EIO;
		पूर्ण
		i915_request_put(rq);
	पूर्ण

out:
	igt_spinner_end(&spin);
	अगर (igt_flush_test(gt->i915))
		err = -EIO;
	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_भव_slice(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *siblings[MAX_ENGINE_INSTANCE + 1];
	अचिन्हित पूर्णांक class;
	पूर्णांक err;

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	क्रम (class = 0; class <= MAX_ENGINE_CLASS; class++) अणु
		अचिन्हित पूर्णांक nsibling;

		nsibling = __select_siblings(gt, class, siblings,
					     पूर्णांकel_engine_has_बारlices);
		अगर (nsibling < 2)
			जारी;

		err = slicein_भव_engine(gt, siblings, nsibling);
		अगर (err)
			वापस err;

		err = sliceout_भव_engine(gt, siblings, nsibling);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक preserved_भव_engine(काष्ठा पूर्णांकel_gt *gt,
				    काष्ठा पूर्णांकel_engine_cs **siblings,
				    अचिन्हित पूर्णांक nsibling)
अणु
	काष्ठा i915_request *last = शून्य;
	काष्ठा पूर्णांकel_context *ve;
	काष्ठा i915_vma *scratch;
	काष्ठा igt_live_test t;
	अचिन्हित पूर्णांक n;
	पूर्णांक err = 0;
	u32 *cs;

	scratch =
		__vm_create_scratch_क्रम_पढ़ो_pinned(&siblings[0]->gt->ggtt->vm,
						    PAGE_SIZE);
	अगर (IS_ERR(scratch))
		वापस PTR_ERR(scratch);

	err = i915_vma_sync(scratch);
	अगर (err)
		जाओ out_scratch;

	ve = पूर्णांकel_execlists_create_भव(siblings, nsibling);
	अगर (IS_ERR(ve)) अणु
		err = PTR_ERR(ve);
		जाओ out_scratch;
	पूर्ण

	err = पूर्णांकel_context_pin(ve);
	अगर (err)
		जाओ out_put;

	err = igt_live_test_begin(&t, gt->i915, __func__, ve->engine->name);
	अगर (err)
		जाओ out_unpin;

	क्रम (n = 0; n < NUM_GPR_DW; n++) अणु
		काष्ठा पूर्णांकel_engine_cs *engine = siblings[n % nsibling];
		काष्ठा i915_request *rq;

		rq = i915_request_create(ve);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out_end;
		पूर्ण

		i915_request_put(last);
		last = i915_request_get(rq);

		cs = पूर्णांकel_ring_begin(rq, 8);
		अगर (IS_ERR(cs)) अणु
			i915_request_add(rq);
			err = PTR_ERR(cs);
			जाओ out_end;
		पूर्ण

		*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
		*cs++ = CS_GPR(engine, n);
		*cs++ = i915_ggtt_offset(scratch) + n * माप(u32);
		*cs++ = 0;

		*cs++ = MI_LOAD_REGISTER_IMM(1);
		*cs++ = CS_GPR(engine, (n + 1) % NUM_GPR_DW);
		*cs++ = n + 1;

		*cs++ = MI_NOOP;
		पूर्णांकel_ring_advance(rq, cs);

		/* Restrict this request to run on a particular engine */
		rq->execution_mask = engine->mask;
		i915_request_add(rq);
	पूर्ण

	अगर (i915_request_रुको(last, 0, HZ / 5) < 0) अणु
		err = -ETIME;
		जाओ out_end;
	पूर्ण

	cs = i915_gem_object_pin_map_unlocked(scratch->obj, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ out_end;
	पूर्ण

	क्रम (n = 0; n < NUM_GPR_DW; n++) अणु
		अगर (cs[n] != n) अणु
			pr_err("Incorrect value[%d] found for GPR[%d]\n",
			       cs[n], n);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	i915_gem_object_unpin_map(scratch->obj);

out_end:
	अगर (igt_live_test_end(&t))
		err = -EIO;
	i915_request_put(last);
out_unpin:
	पूर्णांकel_context_unpin(ve);
out_put:
	पूर्णांकel_context_put(ve);
out_scratch:
	i915_vma_unpin_and_release(&scratch, 0);
	वापस err;
पूर्ण

अटल पूर्णांक live_भव_preserved(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *siblings[MAX_ENGINE_INSTANCE + 1];
	अचिन्हित पूर्णांक class;

	/*
	 * Check that the context image retains non-privileged (user) रेजिस्टरs
	 * from one engine to the next. For this we check that the CS_GPR
	 * are preserved.
	 */

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	/* As we use CS_GPR we cannot run beक्रमe they existed on all engines. */
	अगर (INTEL_GEN(gt->i915) < 9)
		वापस 0;

	क्रम (class = 0; class <= MAX_ENGINE_CLASS; class++) अणु
		पूर्णांक nsibling, err;

		nsibling = select_siblings(gt, class, siblings);
		अगर (nsibling < 2)
			जारी;

		err = preserved_भव_engine(gt, siblings, nsibling);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bond_भव_engine(काष्ठा पूर्णांकel_gt *gt,
			       अचिन्हित पूर्णांक class,
			       काष्ठा पूर्णांकel_engine_cs **siblings,
			       अचिन्हित पूर्णांक nsibling,
			       अचिन्हित पूर्णांक flags)
#घोषणा BOND_SCHEDULE BIT(0)
अणु
	काष्ठा पूर्णांकel_engine_cs *master;
	काष्ठा i915_request *rq[16];
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	अचिन्हित दीर्घ n;
	पूर्णांक err;

	/*
	 * A set of bonded requests is पूर्णांकended to be run concurrently
	 * across a number of engines. We use one request per-engine
	 * and a magic fence to schedule each of the bonded requests
	 * at the same समय. A consequence of our current scheduler is that
	 * we only move requests to the HW पढ़ोy queue when the request
	 * becomes पढ़ोy, that is when all of its prerequisite fences have
	 * been संकेतed. As one of those fences is the master submit fence,
	 * there is a delay on all secondary fences as the HW may be
	 * currently busy. Equally, as all the requests are independent,
	 * they may have other fences that delay inभागidual request
	 * submission to HW. Ergo, we करो not guarantee that all requests are
	 * immediately submitted to HW at the same समय, just that अगर the
	 * rules are abided by, they are पढ़ोy at the same समय as the
	 * first is submitted. Userspace can embed semaphores in its batch
	 * to ensure parallel execution of its phases as it requires.
	 * Though naturally it माला_लो requested that perhaps the scheduler should
	 * take care of parallel execution, even across preemption events on
	 * dअगरferent HW. (The proper answer is of course "lalalala".)
	 *
	 * With the submit-fence, we have identअगरied three possible phases
	 * of synchronisation depending on the master fence: queued (not
	 * पढ़ोy), executing, and संकेतed. The first two are quite simple
	 * and checked below. However, the संकेतed master fence handling is
	 * contentious. Currently we करो not distinguish between a संकेतed
	 * fence and an expired fence, as once संकेतed it करोes not convey
	 * any inक्रमmation about the previous execution. It may even be मुक्तd
	 * and hence checking later it may not exist at all. Ergo we currently
	 * करो not apply the bonding स्थिरraपूर्णांक क्रम an alपढ़ोy संकेतed fence,
	 * as our expectation is that it should not स्थिरrain the secondaries
	 * and is outside of the scope of the bonded request API (i.e. all
	 * userspace requests are meant to be running in parallel). As
	 * it imposes no स्थिरraपूर्णांक, and is effectively a no-op, we करो not
	 * check below as normal execution flows are checked extensively above.
	 *
	 * XXX Is the degenerate handling of संकेतed submit fences the
	 * expected behaviour क्रम userpace?
	 */

	GEM_BUG_ON(nsibling >= ARRAY_SIZE(rq) - 1);

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	err = 0;
	rq[0] = ERR_PTR(-ENOMEM);
	क्रम_each_engine(master, gt, id) अणु
		काष्ठा i915_sw_fence fence = अणुपूर्ण;
		काष्ठा पूर्णांकel_context *ce;

		अगर (master->class == class)
			जारी;

		ce = पूर्णांकel_context_create(master);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out;
		पूर्ण

		स_रखो_p((व्योम *)rq, ERR_PTR(-EINVAL), ARRAY_SIZE(rq));

		rq[0] = igt_spinner_create_request(&spin, ce, MI_NOOP);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq[0])) अणु
			err = PTR_ERR(rq[0]);
			जाओ out;
		पूर्ण
		i915_request_get(rq[0]);

		अगर (flags & BOND_SCHEDULE) अणु
			onstack_fence_init(&fence);
			err = i915_sw_fence_aरुको_sw_fence_gfp(&rq[0]->submit,
							       &fence,
							       GFP_KERNEL);
		पूर्ण

		i915_request_add(rq[0]);
		अगर (err < 0)
			जाओ out;

		अगर (!(flags & BOND_SCHEDULE) &&
		    !igt_रुको_क्रम_spinner(&spin, rq[0])) अणु
			err = -EIO;
			जाओ out;
		पूर्ण

		क्रम (n = 0; n < nsibling; n++) अणु
			काष्ठा पूर्णांकel_context *ve;

			ve = पूर्णांकel_execlists_create_भव(siblings, nsibling);
			अगर (IS_ERR(ve)) अणु
				err = PTR_ERR(ve);
				onstack_fence_fini(&fence);
				जाओ out;
			पूर्ण

			err = पूर्णांकel_भव_engine_attach_bond(ve->engine,
							       master,
							       siblings[n]);
			अगर (err) अणु
				पूर्णांकel_context_put(ve);
				onstack_fence_fini(&fence);
				जाओ out;
			पूर्ण

			err = पूर्णांकel_context_pin(ve);
			पूर्णांकel_context_put(ve);
			अगर (err) अणु
				onstack_fence_fini(&fence);
				जाओ out;
			पूर्ण

			rq[n + 1] = i915_request_create(ve);
			पूर्णांकel_context_unpin(ve);
			अगर (IS_ERR(rq[n + 1])) अणु
				err = PTR_ERR(rq[n + 1]);
				onstack_fence_fini(&fence);
				जाओ out;
			पूर्ण
			i915_request_get(rq[n + 1]);

			err = i915_request_aरुको_execution(rq[n + 1],
							   &rq[0]->fence,
							   ve->engine->bond_execute);
			i915_request_add(rq[n + 1]);
			अगर (err < 0) अणु
				onstack_fence_fini(&fence);
				जाओ out;
			पूर्ण
		पूर्ण
		onstack_fence_fini(&fence);
		पूर्णांकel_engine_flush_submission(master);
		igt_spinner_end(&spin);

		अगर (i915_request_रुको(rq[0], 0, HZ / 10) < 0) अणु
			pr_err("Master request did not execute (on %s)!\n",
			       rq[0]->engine->name);
			err = -EIO;
			जाओ out;
		पूर्ण

		क्रम (n = 0; n < nsibling; n++) अणु
			अगर (i915_request_रुको(rq[n + 1], 0,
					      MAX_SCHEDULE_TIMEOUT) < 0) अणु
				err = -EIO;
				जाओ out;
			पूर्ण

			अगर (rq[n + 1]->engine != siblings[n]) अणु
				pr_err("Bonded request did not execute on target engine: expected %s, used %s; master was %s\n",
				       siblings[n]->name,
				       rq[n + 1]->engine->name,
				       rq[0]->engine->name);
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण

		क्रम (n = 0; !IS_ERR(rq[n]); n++)
			i915_request_put(rq[n]);
		rq[0] = ERR_PTR(-ENOMEM);
	पूर्ण

out:
	क्रम (n = 0; !IS_ERR(rq[n]); n++)
		i915_request_put(rq[n]);
	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_भव_bond(व्योम *arg)
अणु
	अटल स्थिर काष्ठा phase अणु
		स्थिर अक्षर *name;
		अचिन्हित पूर्णांक flags;
	पूर्ण phases[] = अणु
		अणु "", 0 पूर्ण,
		अणु "schedule", BOND_SCHEDULE पूर्ण,
		अणु पूर्ण,
	पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *siblings[MAX_ENGINE_INSTANCE + 1];
	अचिन्हित पूर्णांक class;
	पूर्णांक err;

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	क्रम (class = 0; class <= MAX_ENGINE_CLASS; class++) अणु
		स्थिर काष्ठा phase *p;
		पूर्णांक nsibling;

		nsibling = select_siblings(gt, class, siblings);
		अगर (nsibling < 2)
			जारी;

		क्रम (p = phases; p->name; p++) अणु
			err = bond_भव_engine(gt,
						  class, siblings, nsibling,
						  p->flags);
			अगर (err) अणु
				pr_err("%s(%s): failed class=%d, nsibling=%d, err=%d\n",
				       __func__, p->name, class, nsibling, err);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक reset_भव_engine(काष्ठा पूर्णांकel_gt *gt,
				काष्ठा पूर्णांकel_engine_cs **siblings,
				अचिन्हित पूर्णांक nsibling)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा पूर्णांकel_context *ve;
	काष्ठा igt_spinner spin;
	काष्ठा i915_request *rq;
	अचिन्हित पूर्णांक n;
	पूर्णांक err = 0;

	/*
	 * In order to support offline error capture क्रम fast preempt reset,
	 * we need to decouple the guilty request and ensure that it and its
	 * descendents are not executed जबतक the capture is in progress.
	 */

	अगर (igt_spinner_init(&spin, gt))
		वापस -ENOMEM;

	ve = पूर्णांकel_execlists_create_भव(siblings, nsibling);
	अगर (IS_ERR(ve)) अणु
		err = PTR_ERR(ve);
		जाओ out_spin;
	पूर्ण

	क्रम (n = 0; n < nsibling; n++)
		st_engine_heartbeat_disable(siblings[n]);

	rq = igt_spinner_create_request(&spin, ve, MI_ARB_CHECK);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_heartbeat;
	पूर्ण
	i915_request_add(rq);

	अगर (!igt_रुको_क्रम_spinner(&spin, rq)) अणु
		पूर्णांकel_gt_set_wedged(gt);
		err = -ETIME;
		जाओ out_heartbeat;
	पूर्ण

	engine = rq->engine;
	GEM_BUG_ON(engine == ve->engine);

	/* Take ownership of the reset and tasklet */
	local_bh_disable();
	अगर (test_and_set_bit(I915_RESET_ENGINE + engine->id,
			     &gt->reset.flags)) अणु
		local_bh_enable();
		पूर्णांकel_gt_set_wedged(gt);
		err = -EBUSY;
		जाओ out_heartbeat;
	पूर्ण
	tasklet_disable(&engine->execlists.tasklet);

	engine->execlists.tasklet.callback(&engine->execlists.tasklet);
	GEM_BUG_ON(execlists_active(&engine->execlists) != rq);

	/* Fake a preemption event; failed of course */
	spin_lock_irq(&engine->active.lock);
	__unwind_incomplete_requests(engine);
	spin_unlock_irq(&engine->active.lock);
	GEM_BUG_ON(rq->engine != engine);

	/* Reset the engine जबतक keeping our active request on hold */
	execlists_hold(engine, rq);
	GEM_BUG_ON(!i915_request_on_hold(rq));

	__पूर्णांकel_engine_reset_bh(engine, शून्य);
	GEM_BUG_ON(rq->fence.error != -EIO);

	/* Release our grasp on the engine, letting CS flow again */
	tasklet_enable(&engine->execlists.tasklet);
	clear_and_wake_up_bit(I915_RESET_ENGINE + engine->id, &gt->reset.flags);
	local_bh_enable();

	/* Check that we करो not resubmit the held request */
	i915_request_get(rq);
	अगर (!i915_request_रुको(rq, 0, HZ / 5)) अणु
		pr_err("%s: on hold request completed!\n",
		       engine->name);
		पूर्णांकel_gt_set_wedged(gt);
		err = -EIO;
		जाओ out_rq;
	पूर्ण
	GEM_BUG_ON(!i915_request_on_hold(rq));

	/* But is resubmitted on release */
	execlists_unhold(engine, rq);
	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
		pr_err("%s: held request did not complete!\n",
		       engine->name);
		पूर्णांकel_gt_set_wedged(gt);
		err = -ETIME;
	पूर्ण

out_rq:
	i915_request_put(rq);
out_heartbeat:
	क्रम (n = 0; n < nsibling; n++)
		st_engine_heartbeat_enable(siblings[n]);

	पूर्णांकel_context_put(ve);
out_spin:
	igt_spinner_fini(&spin);
	वापस err;
पूर्ण

अटल पूर्णांक live_भव_reset(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *siblings[MAX_ENGINE_INSTANCE + 1];
	अचिन्हित पूर्णांक class;

	/*
	 * Check that we handle a reset event within a भव engine.
	 * Only the physical engine is reset, but we have to check the flow
	 * of the भव requests around the reset, and make sure it is not
	 * क्रमgotten.
	 */

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	क्रम (class = 0; class <= MAX_ENGINE_CLASS; class++) अणु
		पूर्णांक nsibling, err;

		nsibling = select_siblings(gt, class, siblings);
		अगर (nsibling < 2)
			जारी;

		err = reset_भव_engine(gt, siblings, nsibling);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_execlists_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_sanitycheck),
		SUBTEST(live_unlite_चयन),
		SUBTEST(live_unlite_preempt),
		SUBTEST(live_unlite_ring),
		SUBTEST(live_pin_शुरुआत),
		SUBTEST(live_hold_reset),
		SUBTEST(live_error_पूर्णांकerrupt),
		SUBTEST(live_बारlice_preempt),
		SUBTEST(live_बारlice_शुरुआत),
		SUBTEST(live_बारlice_queue),
		SUBTEST(live_बारlice_nopreempt),
		SUBTEST(live_busyरुको_preempt),
		SUBTEST(live_preempt),
		SUBTEST(live_late_preempt),
		SUBTEST(live_nopreempt),
		SUBTEST(live_preempt_cancel),
		SUBTEST(live_suppress_self_preempt),
		SUBTEST(live_chain_preempt),
		SUBTEST(live_preempt_ring),
		SUBTEST(live_preempt_gang),
		SUBTEST(live_preempt_समयout),
		SUBTEST(live_preempt_user),
		SUBTEST(live_preempt_smoke),
		SUBTEST(live_भव_engine),
		SUBTEST(live_भव_mask),
		SUBTEST(live_भव_preserved),
		SUBTEST(live_भव_slice),
		SUBTEST(live_भव_bond),
		SUBTEST(live_भव_reset),
	पूर्ण;

	अगर (!HAS_EXECLISTS(i915))
		वापस 0;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
