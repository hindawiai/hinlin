<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014 Intel Corporation
 */

/**
 * DOC: Logical Rings, Logical Ring Contexts and Execlists
 *
 * Motivation:
 * GEN8 brings an expansion of the HW contexts: "Logical Ring Contexts".
 * These expanded contexts enable a number of new abilities, especially
 * "Execlists" (also implemented in this file).
 *
 * One of the मुख्य dअगरferences with the legacy HW contexts is that logical
 * ring contexts incorporate many more things to the context's state, like
 * PDPs or ringbuffer control रेजिस्टरs:
 *
 * The reason why PDPs are included in the context is straightक्रमward: as
 * PPGTTs (per-process GTTs) are actually per-context, having the PDPs
 * contained there mean you करोn't need to करो a ppgtt->चयन_mm yourself,
 * instead, the GPU will करो it क्रम you on the context चयन.
 *
 * But, what about the ringbuffer control रेजिस्टरs (head, tail, etc..)?
 * shouldn't we just need a set of those per engine command streamer? This is
 * where the name "Logical Rings" starts to make sense: by भवizing the
 * rings, the engine cs shअगरts to a new "ring buffer" with every context
 * चयन. When you want to submit a workload to the GPU you: A) choose your
 * context, B) find its appropriate भवized ring, C) ग_लिखो commands to it
 * and then, finally, D) tell the GPU to चयन to that context.
 *
 * Instead of the legacy MI_SET_CONTEXT, the way you tell the GPU to चयन
 * to a contexts is via a context execution list, ergo "Execlists".
 *
 * LRC implementation:
 * Regarding the creation of contexts, we have:
 *
 * - One global शेष context.
 * - One local शेष context क्रम each खोलोed fd.
 * - One local extra context क्रम each context create ioctl call.
 *
 * Now that ringbuffers beदीर्घ per-context (and not per-engine, like beक्रमe)
 * and that contexts are uniquely tied to a given engine (and not reusable,
 * like beक्रमe) we need:
 *
 * - One ringbuffer per-engine inside each context.
 * - One backing object per-engine inside each context.
 *
 * The global शेष context starts its lअगरe with these new objects fully
 * allocated and populated. The local शेष context क्रम each खोलोed fd is
 * more complex, because we करोn't know at creation समय which engine is going
 * to use them. To handle this, we have implemented a deferred creation of LR
 * contexts:
 *
 * The local context starts its lअगरe as a hollow or blank holder, that only
 * माला_लो populated क्रम a given engine once we receive an execbuffer. If later
 * on we receive another execbuffer ioctl क्रम the same context but a dअगरferent
 * engine, we allocate/populate a new ringbuffer and context backing object and
 * so on.
 *
 * Finally, regarding local contexts created using the ioctl call: as they are
 * only allowed with the render ring, we can allocate & populate them right
 * away (no need to defer anything, at least क्रम now).
 *
 * Execlists implementation:
 * Execlists are the new method by which, on gen8+ hardware, workloads are
 * submitted क्रम execution (as opposed to the legacy, ringbuffer-based, method).
 * This method works as follows:
 *
 * When a request is committed, its commands (the BB start and any leading or
 * trailing commands, like the seqno bपढ़ोcrumbs) are placed in the ringbuffer
 * क्रम the appropriate context. The tail poपूर्णांकer in the hardware context is not
 * updated at this समय, but instead, kept by the driver in the ringbuffer
 * काष्ठाure. A काष्ठाure representing this request is added to a request queue
 * क्रम the appropriate engine: this काष्ठाure contains a copy of the context's
 * tail after the request was written to the ring buffer and a poपूर्णांकer to the
 * context itself.
 *
 * If the engine's request queue was empty beक्रमe the request was added, the
 * queue is processed immediately. Otherwise the queue will be processed during
 * a context चयन पूर्णांकerrupt. In any हाल, elements on the queue will get sent
 * (in pairs) to the GPU's ExecLists Submit Port (ELSP, क्रम लघु) with a
 * globally unique 20-bits submission ID.
 *
 * When execution of a request completes, the GPU updates the context status
 * buffer with a context complete event and generates a context चयन पूर्णांकerrupt.
 * During the पूर्णांकerrupt handling, the driver examines the events in the buffer:
 * क्रम each context complete event, अगर the announced ID matches that on the head
 * of the request queue, then that request is retired and हटाओd from the queue.
 *
 * After processing, अगर any requests were retired and the queue is not empty
 * then a new execution list can be submitted. The two requests at the front of
 * the queue are next to be submitted but since a context may not occur twice in
 * an execution list, अगर subsequent requests have the same ID as the first then
 * the two requests must be combined. This is करोne simply by discarding requests
 * at the head of the queue until either only one requests is left (in which हाल
 * we use a शून्य second context) or the first two requests have unique IDs.
 *
 * By always executing the first two requests in the queue the driver ensures
 * that the GPU is kept as busy as possible. In the हाल where a single context
 * completes but a second context is still executing, the request क्रम this second
 * context will be at the head of the queue when we हटाओ the first one. This
 * request will then be resubmitted aदीर्घ with a new request क्रम a dअगरferent context,
 * which will cause the hardware to जारी executing the second request and queue
 * the new request (the GPU detects the condition of a context getting preempted
 * with the same context and optimizes the context चयन flow by not करोing
 * preemption, but just sampling the new tail poपूर्णांकer).
 *
 */
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"
#समावेश "gen8_engine_cs.h"
#समावेश "intel_breadcrumbs.h"
#समावेश "intel_context.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_engine_stats.h"
#समावेश "intel_execlists_submission.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_lrc.h"
#समावेश "intel_lrc_reg.h"
#समावेश "intel_mocs.h"
#समावेश "intel_reset.h"
#समावेश "intel_ring.h"
#समावेश "intel_workarounds.h"
#समावेश "shmem_utils.h"

#घोषणा RING_EXECLIST_QFULL		(1 << 0x2)
#घोषणा RING_EXECLIST1_VALID		(1 << 0x3)
#घोषणा RING_EXECLIST0_VALID		(1 << 0x4)
#घोषणा RING_EXECLIST_ACTIVE_STATUS	(3 << 0xE)
#घोषणा RING_EXECLIST1_ACTIVE		(1 << 0x11)
#घोषणा RING_EXECLIST0_ACTIVE		(1 << 0x12)

#घोषणा GEN8_CTX_STATUS_IDLE_ACTIVE	(1 << 0)
#घोषणा GEN8_CTX_STATUS_PREEMPTED	(1 << 1)
#घोषणा GEN8_CTX_STATUS_ELEMENT_SWITCH	(1 << 2)
#घोषणा GEN8_CTX_STATUS_ACTIVE_IDLE	(1 << 3)
#घोषणा GEN8_CTX_STATUS_COMPLETE	(1 << 4)
#घोषणा GEN8_CTX_STATUS_LITE_RESTORE	(1 << 15)

#घोषणा GEN8_CTX_STATUS_COMPLETED_MASK \
	 (GEN8_CTX_STATUS_COMPLETE | GEN8_CTX_STATUS_PREEMPTED)

#घोषणा GEN12_CTX_STATUS_SWITCHED_TO_NEW_QUEUE	(0x1) /* lower csb dword */
#घोषणा GEN12_CTX_SWITCH_DETAIL(csb_dw)	((csb_dw) & 0xF) /* upper csb dword */
#घोषणा GEN12_CSB_SW_CTX_ID_MASK		GENMASK(25, 15)
#घोषणा GEN12_IDLE_CTX_ID		0x7FF
#घोषणा GEN12_CSB_CTX_VALID(csb_dw) \
	(FIELD_GET(GEN12_CSB_SW_CTX_ID_MASK, csb_dw) != GEN12_IDLE_CTX_ID)

/* Typical size of the average request (2 pipecontrols and a MI_BB) */
#घोषणा EXECLISTS_REQUEST_SIZE 64 /* bytes */

काष्ठा भव_engine अणु
	काष्ठा पूर्णांकel_engine_cs base;
	काष्ठा पूर्णांकel_context context;
	काष्ठा rcu_work rcu;

	/*
	 * We allow only a single request through the भव engine at a समय
	 * (each request in the समयline रुकोs क्रम the completion fence of
	 * the previous beक्रमe being submitted). By restricting ourselves to
	 * only submitting a single request, each request is placed on to a
	 * physical to maximise load spपढ़ोing (by virtue of the late greedy
	 * scheduling -- each real engine takes the next available request
	 * upon idling).
	 */
	काष्ठा i915_request *request;

	/*
	 * We keep a rbtree of available भव engines inside each physical
	 * engine, sorted by priority. Here we pपुनः_स्मृतिate the nodes we need
	 * क्रम the भव engine, indexed by physical_engine->id.
	 */
	काष्ठा ve_node अणु
		काष्ठा rb_node rb;
		पूर्णांक prio;
	पूर्ण nodes[I915_NUM_ENGINES];

	/*
	 * Keep track of bonded pairs -- restrictions upon on our selection
	 * of physical engines any particular request may be submitted to.
	 * If we receive a submit-fence from a master engine, we will only
	 * use one of sibling_mask physical engines.
	 */
	काष्ठा ve_bond अणु
		स्थिर काष्ठा पूर्णांकel_engine_cs *master;
		पूर्णांकel_engine_mask_t sibling_mask;
	पूर्ण *bonds;
	अचिन्हित पूर्णांक num_bonds;

	/* And finally, which physical engines this भव engine maps onto. */
	अचिन्हित पूर्णांक num_siblings;
	काष्ठा पूर्णांकel_engine_cs *siblings[];
पूर्ण;

अटल काष्ठा भव_engine *to_भव_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	GEM_BUG_ON(!पूर्णांकel_engine_is_भव(engine));
	वापस container_of(engine, काष्ठा भव_engine, base);
पूर्ण

अटल काष्ठा i915_request *
__active_request(स्थिर काष्ठा पूर्णांकel_समयline * स्थिर tl,
		 काष्ठा i915_request *rq,
		 पूर्णांक error)
अणु
	काष्ठा i915_request *active = rq;

	list_क्रम_each_entry_from_reverse(rq, &tl->requests, link) अणु
		अगर (__i915_request_is_complete(rq))
			अवरोध;

		अगर (error) अणु
			i915_request_set_error_once(rq, error);
			__i915_request_skip(rq);
		पूर्ण
		active = rq;
	पूर्ण

	वापस active;
पूर्ण

अटल काष्ठा i915_request *
active_request(स्थिर काष्ठा पूर्णांकel_समयline * स्थिर tl, काष्ठा i915_request *rq)
अणु
	वापस __active_request(tl, rq, 0);
पूर्ण

अटल व्योम ring_set_छोड़ोd(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, पूर्णांक state)
अणु
	/*
	 * We inspect HWS_PREEMPT with a semaphore inside
	 * engine->emit_fini_bपढ़ोcrumb. If the dword is true,
	 * the ring is छोड़ोd as the semaphore will busyरुको
	 * until the dword is false.
	 */
	engine->status_page.addr[I915_GEM_HWS_PREEMPT] = state;
	अगर (state)
		wmb();
पूर्ण

अटल काष्ठा i915_priolist *to_priolist(काष्ठा rb_node *rb)
अणु
	वापस rb_entry(rb, काष्ठा i915_priolist, node);
पूर्ण

अटल पूर्णांक rq_prio(स्थिर काष्ठा i915_request *rq)
अणु
	वापस READ_ONCE(rq->sched.attr.priority);
पूर्ण

अटल पूर्णांक effective_prio(स्थिर काष्ठा i915_request *rq)
अणु
	पूर्णांक prio = rq_prio(rq);

	/*
	 * If this request is special and must not be पूर्णांकerrupted at any
	 * cost, so be it. Note we are only checking the most recent request
	 * in the context and so may be masking an earlier vip request. It
	 * is hoped that under the conditions where nopreempt is used, this
	 * will not matter (i.e. all requests to that context will be
	 * nopreempt क्रम as दीर्घ as desired).
	 */
	अगर (i915_request_has_nopreempt(rq))
		prio = I915_PRIORITY_UNPREEMPTABLE;

	वापस prio;
पूर्ण

अटल पूर्णांक queue_prio(स्थिर काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	काष्ठा rb_node *rb;

	rb = rb_first_cached(&execlists->queue);
	अगर (!rb)
		वापस पूर्णांक_न्यून;

	वापस to_priolist(rb)->priority;
पूर्ण

अटल पूर्णांक भव_prio(स्थिर काष्ठा पूर्णांकel_engine_execlists *el)
अणु
	काष्ठा rb_node *rb = rb_first_cached(&el->भव);

	वापस rb ? rb_entry(rb, काष्ठा ve_node, rb)->prio : पूर्णांक_न्यून;
पूर्ण

अटल bool need_preempt(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			 स्थिर काष्ठा i915_request *rq)
अणु
	पूर्णांक last_prio;

	अगर (!पूर्णांकel_engine_has_semaphores(engine))
		वापस false;

	/*
	 * Check अगर the current priority hपूर्णांक merits a preemption attempt.
	 *
	 * We record the highest value priority we saw during rescheduling
	 * prior to this dequeue, thereक्रमe we know that अगर it is strictly
	 * less than the current tail of ESLP[0], we करो not need to क्रमce
	 * a preempt-to-idle cycle.
	 *
	 * However, the priority hपूर्णांक is a mere hपूर्णांक that we may need to
	 * preempt. If that hपूर्णांक is stale or we may be trying to preempt
	 * ourselves, ignore the request.
	 *
	 * More naturally we would ग_लिखो
	 *      prio >= max(0, last);
	 * except that we wish to prevent triggering preemption at the same
	 * priority level: the task that is running should reमुख्य running
	 * to preserve FIFO ordering of dependencies.
	 */
	last_prio = max(effective_prio(rq), I915_PRIORITY_NORMAL - 1);
	अगर (engine->execlists.queue_priority_hपूर्णांक <= last_prio)
		वापस false;

	/*
	 * Check against the first request in ELSP[1], it will, thanks to the
	 * घातer of PI, be the highest priority of that context.
	 */
	अगर (!list_is_last(&rq->sched.link, &engine->active.requests) &&
	    rq_prio(list_next_entry(rq, sched.link)) > last_prio)
		वापस true;

	/*
	 * If the inflight context did not trigger the preemption, then maybe
	 * it was the set of queued requests? Pick the highest priority in
	 * the queue (the first active priolist) and see अगर it deserves to be
	 * running instead of ELSP[0].
	 *
	 * The highest priority request in the queue can not be either
	 * ELSP[0] or ELSP[1] as, thanks again to PI, अगर it was the same
	 * context, it's priority would not exceed ELSP[0] aka last_prio.
	 */
	वापस max(भव_prio(&engine->execlists),
		   queue_prio(&engine->execlists)) > last_prio;
पूर्ण

__maybe_unused अटल bool
निश्चित_priority_queue(स्थिर काष्ठा i915_request *prev,
		      स्थिर काष्ठा i915_request *next)
अणु
	/*
	 * Without preemption, the prev may refer to the still active element
	 * which we refuse to let go.
	 *
	 * Even with preemption, there are बार when we think it is better not
	 * to preempt and leave an ostensibly lower priority request in flight.
	 */
	अगर (i915_request_is_active(prev))
		वापस true;

	वापस rq_prio(prev) >= rq_prio(next);
पूर्ण

अटल काष्ठा i915_request *
__unwind_incomplete_requests(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_request *rq, *rn, *active = शून्य;
	काष्ठा list_head *pl;
	पूर्णांक prio = I915_PRIORITY_INVALID;

	lockdep_निश्चित_held(&engine->active.lock);

	list_क्रम_each_entry_safe_reverse(rq, rn,
					 &engine->active.requests,
					 sched.link) अणु
		अगर (__i915_request_is_complete(rq)) अणु
			list_del_init(&rq->sched.link);
			जारी;
		पूर्ण

		__i915_request_unsubmit(rq);

		GEM_BUG_ON(rq_prio(rq) == I915_PRIORITY_INVALID);
		अगर (rq_prio(rq) != prio) अणु
			prio = rq_prio(rq);
			pl = i915_sched_lookup_priolist(engine, prio);
		पूर्ण
		GEM_BUG_ON(RB_EMPTY_ROOT(&engine->execlists.queue.rb_root));

		list_move(&rq->sched.link, pl);
		set_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);

		/* Check in हाल we rollback so far we wrap [size/2] */
		अगर (पूर्णांकel_ring_direction(rq->ring,
					 rq->tail,
					 rq->ring->tail + 8) > 0)
			rq->context->lrc.desc |= CTX_DESC_FORCE_RESTORE;

		active = rq;
	पूर्ण

	वापस active;
पूर्ण

काष्ठा i915_request *
execlists_unwind_incomplete_requests(काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine =
		container_of(execlists, typeof(*engine), execlists);

	वापस __unwind_incomplete_requests(engine);
पूर्ण

अटल व्योम
execlists_context_status_change(काष्ठा i915_request *rq, अचिन्हित दीर्घ status)
अणु
	/*
	 * Only used when GVT-g is enabled now. When GVT-g is disabled,
	 * The compiler should eliminate this function as dead-code.
	 */
	अगर (!IS_ENABLED(CONFIG_DRM_I915_GVT))
		वापस;

	atomic_notअगरier_call_chain(&rq->engine->context_status_notअगरier,
				   status, rq);
पूर्ण

अटल व्योम reset_active(काष्ठा i915_request *rq,
			 काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context * स्थिर ce = rq->context;
	u32 head;

	/*
	 * The executing context has been cancelled. We want to prevent
	 * further execution aदीर्घ this context and propagate the error on
	 * to anything depending on its results.
	 *
	 * In __i915_request_submit(), we apply the -EIO and हटाओ the
	 * requests' payloads क्रम any banned requests. But first, we must
	 * शुरुआत the context back to the start of the incomplete request so
	 * that we करो not jump back पूर्णांकo the middle of the batch.
	 *
	 * We preserve the bपढ़ोcrumbs and semaphores of the incomplete
	 * requests so that पूर्णांकer-समयline dependencies (i.e other समयlines)
	 * reमुख्य correctly ordered. And we defer to __i915_request_submit()
	 * so that all asynchronous रुकोs are correctly handled.
	 */
	ENGINE_TRACE(engine, "{ reset rq=%llx:%lld }\n",
		     rq->fence.context, rq->fence.seqno);

	/* On resubmission of the active request, payload will be scrubbed */
	अगर (__i915_request_is_complete(rq))
		head = rq->tail;
	अन्यथा
		head = __active_request(ce->समयline, rq, -EIO)->head;
	head = पूर्णांकel_ring_wrap(ce->ring, head);

	/* Scrub the context image to prevent replaying the previous batch */
	lrc_init_regs(ce, engine, true);

	/* We've चयनed away, so this should be a no-op, but पूर्णांकent matters */
	ce->lrc.lrca = lrc_update_regs(ce, engine, head);
पूर्ण

अटल bool bad_request(स्थिर काष्ठा i915_request *rq)
अणु
	वापस rq->fence.error && i915_request_started(rq);
पूर्ण

अटल काष्ठा पूर्णांकel_engine_cs *
__execlists_schedule_in(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs * स्थिर engine = rq->engine;
	काष्ठा पूर्णांकel_context * स्थिर ce = rq->context;

	पूर्णांकel_context_get(ce);

	अगर (unlikely(पूर्णांकel_context_is_बंदd(ce) &&
		     !पूर्णांकel_engine_has_heartbeat(engine)))
		पूर्णांकel_context_set_banned(ce);

	अगर (unlikely(पूर्णांकel_context_is_banned(ce) || bad_request(rq)))
		reset_active(rq, engine);

	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		lrc_check_regs(ce, engine, "before");

	अगर (ce->tag) अणु
		/* Use a fixed tag क्रम OA and मित्रs */
		GEM_BUG_ON(ce->tag <= BITS_PER_LONG);
		ce->lrc.ccid = ce->tag;
	पूर्ण अन्यथा अणु
		/* We करोn't need a strict matching tag, just dअगरferent values */
		अचिन्हित पूर्णांक tag = __ffs(engine->context_tag);

		GEM_BUG_ON(tag >= BITS_PER_LONG);
		__clear_bit(tag, &engine->context_tag);
		ce->lrc.ccid = (1 + tag) << (GEN11_SW_CTX_ID_SHIFT - 32);

		BUILD_BUG_ON(BITS_PER_LONG > GEN12_MAX_CONTEXT_HW_ID);
	पूर्ण

	ce->lrc.ccid |= engine->execlists.ccid;

	__पूर्णांकel_gt_pm_get(engine->gt);
	अगर (engine->fw_करोमुख्य && !engine->fw_active++)
		पूर्णांकel_uncore_क्रमcewake_get(engine->uncore, engine->fw_करोमुख्य);
	execlists_context_status_change(rq, INTEL_CONTEXT_SCHEDULE_IN);
	पूर्णांकel_engine_context_in(engine);

	CE_TRACE(ce, "schedule-in, ccid:%x\n", ce->lrc.ccid);

	वापस engine;
पूर्ण

अटल व्योम execlists_schedule_in(काष्ठा i915_request *rq, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_context * स्थिर ce = rq->context;
	काष्ठा पूर्णांकel_engine_cs *old;

	GEM_BUG_ON(!पूर्णांकel_engine_pm_is_awake(rq->engine));
	trace_i915_request_in(rq, idx);

	old = ce->inflight;
	अगर (!old)
		old = __execlists_schedule_in(rq);
	WRITE_ONCE(ce->inflight, ptr_inc(old));

	GEM_BUG_ON(पूर्णांकel_context_inflight(ce) != rq->engine);
पूर्ण

अटल व्योम
resubmit_भव_request(काष्ठा i915_request *rq, काष्ठा भव_engine *ve)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;

	spin_lock_irq(&engine->active.lock);

	clear_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);
	WRITE_ONCE(rq->engine, &ve->base);
	ve->base.submit_request(rq);

	spin_unlock_irq(&engine->active.lock);
पूर्ण

अटल व्योम kick_siblings(काष्ठा i915_request *rq, काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा भव_engine *ve = container_of(ce, typeof(*ve), context);
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;

	/*
	 * After this poपूर्णांक, the rq may be transferred to a new sibling, so
	 * beक्रमe we clear ce->inflight make sure that the context has been
	 * हटाओd from the b->संकेतers and furthermore we need to make sure
	 * that the concurrent iterator in संकेत_irq_work is no दीर्घer
	 * following ce->संकेत_link.
	 */
	अगर (!list_empty(&ce->संकेतs))
		पूर्णांकel_context_हटाओ_bपढ़ोcrumbs(ce, engine->bपढ़ोcrumbs);

	/*
	 * This engine is now too busy to run this भव request, so
	 * see अगर we can find an alternative engine क्रम it to execute on.
	 * Once a request has become bonded to this engine, we treat it the
	 * same as other native request.
	 */
	अगर (i915_request_in_priority_queue(rq) &&
	    rq->execution_mask != engine->mask)
		resubmit_भव_request(rq, ve);

	अगर (READ_ONCE(ve->request))
		tasklet_hi_schedule(&ve->base.execlists.tasklet);
पूर्ण

अटल व्योम __execlists_schedule_out(काष्ठा i915_request * स्थिर rq,
				     काष्ठा पूर्णांकel_context * स्थिर ce)
अणु
	काष्ठा पूर्णांकel_engine_cs * स्थिर engine = rq->engine;
	अचिन्हित पूर्णांक ccid;

	/*
	 * NB process_csb() is not under the engine->active.lock and hence
	 * schedule_out can race with schedule_in meaning that we should
	 * refrain from करोing non-trivial work here.
	 */

	CE_TRACE(ce, "schedule-out, ccid:%x\n", ce->lrc.ccid);
	GEM_BUG_ON(ce->inflight != engine);

	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		lrc_check_regs(ce, engine, "after");

	/*
	 * If we have just completed this context, the engine may now be
	 * idle and we want to re-enter घातersaving.
	 */
	अगर (पूर्णांकel_समयline_is_last(ce->समयline, rq) &&
	    __i915_request_is_complete(rq))
		पूर्णांकel_engine_add_retire(engine, ce->समयline);

	ccid = ce->lrc.ccid;
	ccid >>= GEN11_SW_CTX_ID_SHIFT - 32;
	ccid &= GEN12_MAX_CONTEXT_HW_ID;
	अगर (ccid < BITS_PER_LONG) अणु
		GEM_BUG_ON(ccid == 0);
		GEM_BUG_ON(test_bit(ccid - 1, &engine->context_tag));
		__set_bit(ccid - 1, &engine->context_tag);
	पूर्ण

	lrc_update_runसमय(ce);
	पूर्णांकel_engine_context_out(engine);
	execlists_context_status_change(rq, INTEL_CONTEXT_SCHEDULE_OUT);
	अगर (engine->fw_करोमुख्य && !--engine->fw_active)
		पूर्णांकel_uncore_क्रमcewake_put(engine->uncore, engine->fw_करोमुख्य);
	पूर्णांकel_gt_pm_put_async(engine->gt);

	/*
	 * If this is part of a भव engine, its next request may
	 * have been blocked रुकोing क्रम access to the active context.
	 * We have to kick all the siblings again in हाल we need to
	 * चयन (e.g. the next request is not runnable on this
	 * engine). Hopefully, we will alपढ़ोy have submitted the next
	 * request beक्रमe the tasklet runs and करो not need to rebuild
	 * each भव tree and kick everyone again.
	 */
	अगर (ce->engine != engine)
		kick_siblings(rq, ce);

	WRITE_ONCE(ce->inflight, शून्य);
	पूर्णांकel_context_put(ce);
पूर्ण

अटल अंतरभूत व्योम execlists_schedule_out(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_context * स्थिर ce = rq->context;

	trace_i915_request_out(rq);

	GEM_BUG_ON(!ce->inflight);
	ce->inflight = ptr_dec(ce->inflight);
	अगर (!__पूर्णांकel_context_inflight_count(ce->inflight))
		__execlists_schedule_out(rq, ce);

	i915_request_put(rq);
पूर्ण

अटल u64 execlists_update_context(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_context *ce = rq->context;
	u64 desc = ce->lrc.desc;
	u32 tail, prev;

	/*
	 * WaIdleLiteRestore:bdw,skl
	 *
	 * We should never submit the context with the same RING_TAIL twice
	 * just in हाल we submit an empty ring, which confuses the HW.
	 *
	 * We append a couple of NOOPs (gen8_emit_wa_tail) after the end of
	 * the normal request to be able to always advance the RING_TAIL on
	 * subsequent resubmissions (क्रम lite restore). Should that fail us,
	 * and we try and submit the same tail again, क्रमce the context
	 * reload.
	 *
	 * If we need to वापस to a preempted context, we need to skip the
	 * lite-restore and क्रमce it to reload the RING_TAIL. Otherwise, the
	 * HW has a tendency to ignore us शुरुआतing the TAIL to the end of
	 * an earlier request.
	 */
	GEM_BUG_ON(ce->lrc_reg_state[CTX_RING_TAIL] != rq->ring->tail);
	prev = rq->ring->tail;
	tail = पूर्णांकel_ring_set_tail(rq->ring, rq->tail);
	अगर (unlikely(पूर्णांकel_ring_direction(rq->ring, tail, prev) <= 0))
		desc |= CTX_DESC_FORCE_RESTORE;
	ce->lrc_reg_state[CTX_RING_TAIL] = tail;
	rq->tail = rq->wa_tail;

	/*
	 * Make sure the context image is complete beक्रमe we submit it to HW.
	 *
	 * Ostensibly, ग_लिखोs (including the WCB) should be flushed prior to
	 * an uncached ग_लिखो such as our mmio रेजिस्टर access, the empirical
	 * evidence (esp. on Braswell) suggests that the WC ग_लिखो पूर्णांकo memory
	 * may not be visible to the HW prior to the completion of the UC
	 * रेजिस्टर ग_लिखो and that we may begin execution from the context
	 * beक्रमe its image is complete leading to invalid PD chasing.
	 */
	wmb();

	ce->lrc.desc &= ~CTX_DESC_FORCE_RESTORE;
	वापस desc;
पूर्ण

अटल व्योम ग_लिखो_desc(काष्ठा पूर्णांकel_engine_execlists *execlists, u64 desc, u32 port)
अणु
	अगर (execlists->ctrl_reg) अणु
		ग_लिखोl(lower_32_bits(desc), execlists->submit_reg + port * 2);
		ग_लिखोl(upper_32_bits(desc), execlists->submit_reg + port * 2 + 1);
	पूर्ण अन्यथा अणु
		ग_लिखोl(upper_32_bits(desc), execlists->submit_reg);
		ग_लिखोl(lower_32_bits(desc), execlists->submit_reg);
	पूर्ण
पूर्ण

अटल __maybe_unused अक्षर *
dump_port(अक्षर *buf, पूर्णांक buflen, स्थिर अक्षर *prefix, काष्ठा i915_request *rq)
अणु
	अगर (!rq)
		वापस "";

	snम_लिखो(buf, buflen, "%sccid:%x %llx:%lld%s prio %d",
		 prefix,
		 rq->context->lrc.ccid,
		 rq->fence.context, rq->fence.seqno,
		 __i915_request_is_complete(rq) ? "!" :
		 __i915_request_has_started(rq) ? "*" :
		 "",
		 rq_prio(rq));

	वापस buf;
पूर्ण

अटल __maybe_unused noअंतरभूत व्योम
trace_ports(स्थिर काष्ठा पूर्णांकel_engine_execlists *execlists,
	    स्थिर अक्षर *msg,
	    काष्ठा i915_request * स्थिर *ports)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine =
		container_of(execlists, typeof(*engine), execlists);
	अक्षर __maybe_unused p0[40], p1[40];

	अगर (!ports[0])
		वापस;

	ENGINE_TRACE(engine, "%s { %s%s }\n", msg,
		     dump_port(p0, माप(p0), "", ports[0]),
		     dump_port(p1, माप(p1), ", ", ports[1]));
पूर्ण

अटल bool
reset_in_progress(स्थिर काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	वापस unlikely(!__tasklet_is_enabled(&execlists->tasklet));
पूर्ण

अटल __maybe_unused noअंतरभूत bool
निश्चित_pending_valid(स्थिर काष्ठा पूर्णांकel_engine_execlists *execlists,
		     स्थिर अक्षर *msg)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine =
		container_of(execlists, typeof(*engine), execlists);
	काष्ठा i915_request * स्थिर *port, *rq, *prev = शून्य;
	काष्ठा पूर्णांकel_context *ce = शून्य;
	u32 ccid = -1;

	trace_ports(execlists, msg, execlists->pending);

	/* We may be messing around with the lists during reset, lalala */
	अगर (reset_in_progress(execlists))
		वापस true;

	अगर (!execlists->pending[0]) अणु
		GEM_TRACE_ERR("%s: Nothing pending for promotion!\n",
			      engine->name);
		वापस false;
	पूर्ण

	अगर (execlists->pending[execlists_num_ports(execlists)]) अणु
		GEM_TRACE_ERR("%s: Excess pending[%d] for promotion!\n",
			      engine->name, execlists_num_ports(execlists));
		वापस false;
	पूर्ण

	क्रम (port = execlists->pending; (rq = *port); port++) अणु
		अचिन्हित दीर्घ flags;
		bool ok = true;

		GEM_BUG_ON(!kref_पढ़ो(&rq->fence.refcount));
		GEM_BUG_ON(!i915_request_is_active(rq));

		अगर (ce == rq->context) अणु
			GEM_TRACE_ERR("%s: Dup context:%llx in pending[%zd]\n",
				      engine->name,
				      ce->समयline->fence_context,
				      port - execlists->pending);
			वापस false;
		पूर्ण
		ce = rq->context;

		अगर (ccid == ce->lrc.ccid) अणु
			GEM_TRACE_ERR("%s: Dup ccid:%x context:%llx in pending[%zd]\n",
				      engine->name,
				      ccid, ce->समयline->fence_context,
				      port - execlists->pending);
			वापस false;
		पूर्ण
		ccid = ce->lrc.ccid;

		/*
		 * Sentinels are supposed to be the last request so they flush
		 * the current execution off the HW. Check that they are the only
		 * request in the pending submission.
		 *
		 * NB: Due to the async nature of preempt-to-busy and request
		 * cancellation we need to handle the हाल where request
		 * becomes a sentinel in parallel to CSB processing.
		 */
		अगर (prev && i915_request_has_sentinel(prev) &&
		    !READ_ONCE(prev->fence.error)) अणु
			GEM_TRACE_ERR("%s: context:%llx after sentinel in pending[%zd]\n",
				      engine->name,
				      ce->समयline->fence_context,
				      port - execlists->pending);
			वापस false;
		पूर्ण
		prev = rq;

		/*
		 * We want भव requests to only be in the first slot so
		 * that they are never stuck behind a hog and can be immediately
		 * transferred onto the next idle engine.
		 */
		अगर (rq->execution_mask != engine->mask &&
		    port != execlists->pending) अणु
			GEM_TRACE_ERR("%s: virtual engine:%llx not in prime position[%zd]\n",
				      engine->name,
				      ce->समयline->fence_context,
				      port - execlists->pending);
			वापस false;
		पूर्ण

		/* Hold tightly onto the lock to prevent concurrent retires! */
		अगर (!spin_trylock_irqsave(&rq->lock, flags))
			जारी;

		अगर (__i915_request_is_complete(rq))
			जाओ unlock;

		अगर (i915_active_is_idle(&ce->active) &&
		    !पूर्णांकel_context_is_barrier(ce)) अणु
			GEM_TRACE_ERR("%s: Inactive context:%llx in pending[%zd]\n",
				      engine->name,
				      ce->समयline->fence_context,
				      port - execlists->pending);
			ok = false;
			जाओ unlock;
		पूर्ण

		अगर (!i915_vma_is_pinned(ce->state)) अणु
			GEM_TRACE_ERR("%s: Unpinned context:%llx in pending[%zd]\n",
				      engine->name,
				      ce->समयline->fence_context,
				      port - execlists->pending);
			ok = false;
			जाओ unlock;
		पूर्ण

		अगर (!i915_vma_is_pinned(ce->ring->vma)) अणु
			GEM_TRACE_ERR("%s: Unpinned ring:%llx in pending[%zd]\n",
				      engine->name,
				      ce->समयline->fence_context,
				      port - execlists->pending);
			ok = false;
			जाओ unlock;
		पूर्ण

unlock:
		spin_unlock_irqrestore(&rq->lock, flags);
		अगर (!ok)
			वापस false;
	पूर्ण

	वापस ce;
पूर्ण

अटल व्योम execlists_submit_ports(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists *execlists = &engine->execlists;
	अचिन्हित पूर्णांक n;

	GEM_BUG_ON(!निश्चित_pending_valid(execlists, "submit"));

	/*
	 * We can skip acquiring पूर्णांकel_runसमय_pm_get() here as it was taken
	 * on our behalf by the request (see i915_gem_mark_busy()) and it will
	 * not be relinquished until the device is idle (see
	 * i915_gem_idle_work_handler()). As a precaution, we make sure
	 * that all ELSP are drained i.e. we have processed the CSB,
	 * beक्रमe allowing ourselves to idle and calling पूर्णांकel_runसमय_pm_put().
	 */
	GEM_BUG_ON(!पूर्णांकel_engine_pm_is_awake(engine));

	/*
	 * ELSQ note: the submit queue is not cleared after being submitted
	 * to the HW so we need to make sure we always clean it up. This is
	 * currently ensured by the fact that we always ग_लिखो the same number
	 * of elsq entries, keep this in mind beक्रमe changing the loop below.
	 */
	क्रम (n = execlists_num_ports(execlists); n--; ) अणु
		काष्ठा i915_request *rq = execlists->pending[n];

		ग_लिखो_desc(execlists,
			   rq ? execlists_update_context(rq) : 0,
			   n);
	पूर्ण

	/* we need to manually load the submit queue */
	अगर (execlists->ctrl_reg)
		ग_लिखोl(EL_CTRL_LOAD, execlists->ctrl_reg);
पूर्ण

अटल bool ctx_single_port_submission(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस (IS_ENABLED(CONFIG_DRM_I915_GVT) &&
		पूर्णांकel_context_क्रमce_single_submission(ce));
पूर्ण

अटल bool can_merge_ctx(स्थिर काष्ठा पूर्णांकel_context *prev,
			  स्थिर काष्ठा पूर्णांकel_context *next)
अणु
	अगर (prev != next)
		वापस false;

	अगर (ctx_single_port_submission(prev))
		वापस false;

	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ i915_request_flags(स्थिर काष्ठा i915_request *rq)
अणु
	वापस READ_ONCE(rq->fence.flags);
पूर्ण

अटल bool can_merge_rq(स्थिर काष्ठा i915_request *prev,
			 स्थिर काष्ठा i915_request *next)
अणु
	GEM_BUG_ON(prev == next);
	GEM_BUG_ON(!निश्चित_priority_queue(prev, next));

	/*
	 * We करो not submit known completed requests. Thereक्रमe अगर the next
	 * request is alपढ़ोy completed, we can pretend to merge it in
	 * with the previous context (and we will skip updating the ELSP
	 * and tracking). Thus hopefully keeping the ELSP full with active
	 * contexts, despite the best efक्रमts of preempt-to-busy to confuse
	 * us.
	 */
	अगर (__i915_request_is_complete(next))
		वापस true;

	अगर (unlikely((i915_request_flags(prev) | i915_request_flags(next)) &
		     (BIT(I915_FENCE_FLAG_NOPREEMPT) |
		      BIT(I915_FENCE_FLAG_SENTINEL))))
		वापस false;

	अगर (!can_merge_ctx(prev->context, next->context))
		वापस false;

	GEM_BUG_ON(i915_seqno_passed(prev->fence.seqno, next->fence.seqno));
	वापस true;
पूर्ण

अटल bool भव_matches(स्थिर काष्ठा भव_engine *ve,
			    स्थिर काष्ठा i915_request *rq,
			    स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs *inflight;

	अगर (!rq)
		वापस false;

	अगर (!(rq->execution_mask & engine->mask)) /* We peeked too soon! */
		वापस false;

	/*
	 * We track when the HW has completed saving the context image
	 * (i.e. when we have seen the final CS event चयनing out of
	 * the context) and must not overग_लिखो the context image beक्रमe
	 * then. This restricts us to only using the active engine
	 * जबतक the previous भवized request is inflight (so
	 * we reuse the रेजिस्टर offsets). This is a very small
	 * hystersis on the greedy seelction algorithm.
	 */
	inflight = पूर्णांकel_context_inflight(&ve->context);
	अगर (inflight && inflight != engine)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा भव_engine *
first_भव_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists *el = &engine->execlists;
	काष्ठा rb_node *rb = rb_first_cached(&el->भव);

	जबतक (rb) अणु
		काष्ठा भव_engine *ve =
			rb_entry(rb, typeof(*ve), nodes[engine->id].rb);
		काष्ठा i915_request *rq = READ_ONCE(ve->request);

		/* lazily cleanup after another engine handled rq */
		अगर (!rq || !भव_matches(ve, rq, engine)) अणु
			rb_erase_cached(rb, &el->भव);
			RB_CLEAR_NODE(rb);
			rb = rb_first_cached(&el->भव);
			जारी;
		पूर्ण

		वापस ve;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम भव_xfer_context(काष्ठा भव_engine *ve,
				 काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अचिन्हित पूर्णांक n;

	अगर (likely(engine == ve->siblings[0]))
		वापस;

	GEM_BUG_ON(READ_ONCE(ve->context.inflight));
	अगर (!पूर्णांकel_engine_has_relative_mmio(engine))
		lrc_update_offsets(&ve->context, engine);

	/*
	 * Move the bound engine to the top of the list क्रम
	 * future execution. We then kick this tasklet first
	 * beक्रमe checking others, so that we preferentially
	 * reuse this set of bound रेजिस्टरs.
	 */
	क्रम (n = 1; n < ve->num_siblings; n++) अणु
		अगर (ve->siblings[n] == engine) अणु
			swap(ve->siblings[n], ve->siblings[0]);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम defer_request(काष्ठा i915_request *rq, काष्ठा list_head * स्थिर pl)
अणु
	LIST_HEAD(list);

	/*
	 * We want to move the पूर्णांकerrupted request to the back of
	 * the round-robin list (i.e. its priority level), but
	 * in करोing so, we must then move all requests that were in
	 * flight and were रुकोing क्रम the पूर्णांकerrupted request to
	 * be run after it again.
	 */
	करो अणु
		काष्ठा i915_dependency *p;

		GEM_BUG_ON(i915_request_is_active(rq));
		list_move_tail(&rq->sched.link, pl);

		क्रम_each_रुकोer(p, rq) अणु
			काष्ठा i915_request *w =
				container_of(p->रुकोer, typeof(*w), sched);

			अगर (p->flags & I915_DEPENDENCY_WEAK)
				जारी;

			/* Leave semaphores spinning on the other engines */
			अगर (w->engine != rq->engine)
				जारी;

			/* No रुकोer should start beक्रमe its संकेतer */
			GEM_BUG_ON(i915_request_has_initial_bपढ़ोcrumb(w) &&
				   __i915_request_has_started(w) &&
				   !__i915_request_is_complete(rq));

			अगर (!i915_request_is_पढ़ोy(w))
				जारी;

			अगर (rq_prio(w) < rq_prio(rq))
				जारी;

			GEM_BUG_ON(rq_prio(w) > rq_prio(rq));
			GEM_BUG_ON(i915_request_is_active(w));
			list_move_tail(&w->sched.link, &list);
		पूर्ण

		rq = list_first_entry_or_null(&list, typeof(*rq), sched.link);
	पूर्ण जबतक (rq);
पूर्ण

अटल व्योम defer_active(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_request *rq;

	rq = __unwind_incomplete_requests(engine);
	अगर (!rq)
		वापस;

	defer_request(rq, i915_sched_lookup_priolist(engine, rq_prio(rq)));
पूर्ण

अटल bool
बारlice_yield(स्थिर काष्ठा पूर्णांकel_engine_execlists *el,
		स्थिर काष्ठा i915_request *rq)
अणु
	/*
	 * Once bitten, क्रमever smitten!
	 *
	 * If the active context ever busy-रुकोed on a semaphore,
	 * it will be treated as a hog until the end of its बारlice (i.e.
	 * until it is scheduled out and replaced by a new submission,
	 * possibly even its own lite-restore). The HW only sends an पूर्णांकerrupt
	 * on the first miss, and we करो know अगर that semaphore has been
	 * संकेतed, or even अगर it is now stuck on another semaphore. Play
	 * safe, yield अगर it might be stuck -- it will be given a fresh
	 * बारlice in the near future.
	 */
	वापस rq->context->lrc.ccid == READ_ONCE(el->yield);
पूर्ण

अटल bool needs_बारlice(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर काष्ठा i915_request *rq)
अणु
	अगर (!पूर्णांकel_engine_has_बारlices(engine))
		वापस false;

	/* If not currently active, or about to चयन, रुको क्रम next event */
	अगर (!rq || __i915_request_is_complete(rq))
		वापस false;

	/* We करो not need to start the बारlice until after the ACK */
	अगर (READ_ONCE(engine->execlists.pending[0]))
		वापस false;

	/* If ELSP[1] is occupied, always check to see अगर worth slicing */
	अगर (!list_is_last_rcu(&rq->sched.link, &engine->active.requests)) अणु
		ENGINE_TRACE(engine, "timeslice required for second inflight context\n");
		वापस true;
	पूर्ण

	/* Otherwise, ELSP[0] is by itself, but may be रुकोing in the queue */
	अगर (!RB_EMPTY_ROOT(&engine->execlists.queue.rb_root)) अणु
		ENGINE_TRACE(engine, "timeslice required for queue\n");
		वापस true;
	पूर्ण

	अगर (!RB_EMPTY_ROOT(&engine->execlists.भव.rb_root)) अणु
		ENGINE_TRACE(engine, "timeslice required for virtual\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool
बारlice_expired(काष्ठा पूर्णांकel_engine_cs *engine, स्थिर काष्ठा i915_request *rq)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_execlists *el = &engine->execlists;

	अगर (i915_request_has_nopreempt(rq) && __i915_request_has_started(rq))
		वापस false;

	अगर (!needs_बारlice(engine, rq))
		वापस false;

	वापस समयr_expired(&el->समयr) || बारlice_yield(el, rq);
पूर्ण

अटल अचिन्हित दीर्घ बारlice(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस READ_ONCE(engine->props.बारlice_duration_ms);
पूर्ण

अटल व्योम start_बारlice(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists *el = &engine->execlists;
	अचिन्हित दीर्घ duration;

	/* Disable the समयr अगर there is nothing to चयन to */
	duration = 0;
	अगर (needs_बारlice(engine, *el->active)) अणु
		/* Aव्योम continually proदीर्घing an active बारlice */
		अगर (समयr_active(&el->समयr)) अणु
			/*
			 * If we just submitted a new ELSP after an old
			 * context, that context may have alपढ़ोy consumed
			 * its बारlice, so recheck.
			 */
			अगर (!समयr_pending(&el->समयr))
				tasklet_hi_schedule(&el->tasklet);
			वापस;
		पूर्ण

		duration = बारlice(engine);
	पूर्ण

	set_समयr_ms(&el->समयr, duration);
पूर्ण

अटल व्योम record_preemption(काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	(व्योम)I915_SELFTEST_ONLY(execlists->preempt_hang.count++);
पूर्ण

अटल अचिन्हित दीर्घ active_preempt_समयout(काष्ठा पूर्णांकel_engine_cs *engine,
					    स्थिर काष्ठा i915_request *rq)
अणु
	अगर (!rq)
		वापस 0;

	/* Force a fast reset क्रम terminated contexts (ignoring sysfs!) */
	अगर (unlikely(पूर्णांकel_context_is_banned(rq->context) || bad_request(rq)))
		वापस 1;

	वापस READ_ONCE(engine->props.preempt_समयout_ms);
पूर्ण

अटल व्योम set_preempt_समयout(काष्ठा पूर्णांकel_engine_cs *engine,
				स्थिर काष्ठा i915_request *rq)
अणु
	अगर (!पूर्णांकel_engine_has_preempt_reset(engine))
		वापस;

	set_समयr_ms(&engine->execlists.preempt,
		     active_preempt_समयout(engine, rq));
पूर्ण

अटल bool completed(स्थिर काष्ठा i915_request *rq)
अणु
	अगर (i915_request_has_sentinel(rq))
		वापस false;

	वापस __i915_request_is_complete(rq);
पूर्ण

अटल व्योम execlists_dequeue(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा i915_request **port = execlists->pending;
	काष्ठा i915_request ** स्थिर last_port = port + execlists->port_mask;
	काष्ठा i915_request *last, * स्थिर *active;
	काष्ठा भव_engine *ve;
	काष्ठा rb_node *rb;
	bool submit = false;

	/*
	 * Hardware submission is through 2 ports. Conceptually each port
	 * has a (RING_START, RING_HEAD, RING_TAIL) tuple. RING_START is
	 * अटल क्रम a context, and unique to each, so we only execute
	 * requests beदीर्घing to a single context from each ring. RING_HEAD
	 * is मुख्यtained by the CS in the context image, it marks the place
	 * where it got up to last समय, and through RING_TAIL we tell the CS
	 * where we want to execute up to this समय.
	 *
	 * In this list the requests are in order of execution. Consecutive
	 * requests from the same context are adjacent in the ringbuffer. We
	 * can combine these requests पूर्णांकo a single RING_TAIL update:
	 *
	 *              RING_HEAD...req1...req2
	 *                                    ^- RING_TAIL
	 * since to execute req2 the CS must first execute req1.
	 *
	 * Our goal then is to poपूर्णांक each port to the end of a consecutive
	 * sequence of requests as being the most optimal (fewest wake ups
	 * and context चयनes) submission.
	 */

	spin_lock(&engine->active.lock);

	/*
	 * If the queue is higher priority than the last
	 * request in the currently active context, submit afresh.
	 * We will resubmit again afterwards in हाल we need to split
	 * the active context to पूर्णांकerject the preemption request,
	 * i.e. we will retrigger preemption following the ack in हाल
	 * of trouble.
	 *
	 */
	active = execlists->active;
	जबतक ((last = *active) && completed(last))
		active++;

	अगर (last) अणु
		अगर (need_preempt(engine, last)) अणु
			ENGINE_TRACE(engine,
				     "preempting last=%llx:%lld, prio=%d, hint=%d\n",
				     last->fence.context,
				     last->fence.seqno,
				     last->sched.attr.priority,
				     execlists->queue_priority_hपूर्णांक);
			record_preemption(execlists);

			/*
			 * Don't let the RING_HEAD advance past the bपढ़ोcrumb
			 * as we unwind (and until we resubmit) so that we करो
			 * not accidentally tell it to go backwards.
			 */
			ring_set_छोड़ोd(engine, 1);

			/*
			 * Note that we have not stopped the GPU at this poपूर्णांक,
			 * so we are unwinding the incomplete requests as they
			 * reमुख्य inflight and so by the समय we करो complete
			 * the preemption, some of the unwound requests may
			 * complete!
			 */
			__unwind_incomplete_requests(engine);

			last = शून्य;
		पूर्ण अन्यथा अगर (बारlice_expired(engine, last)) अणु
			ENGINE_TRACE(engine,
				     "expired:%s last=%llx:%lld, prio=%d, hint=%d, yield?=%s\n",
				     yesno(समयr_expired(&execlists->समयr)),
				     last->fence.context, last->fence.seqno,
				     rq_prio(last),
				     execlists->queue_priority_hपूर्णांक,
				     yesno(बारlice_yield(execlists, last)));

			/*
			 * Consume this बारlice; ensure we start a new one.
			 *
			 * The बारlice expired, and we will unwind the
			 * running contexts and recompute the next ELSP.
			 * If that submit will be the same pair of contexts
			 * (due to dependency ordering), we will skip the
			 * submission. If we करोn't cancel the समयr now,
			 * we will see that the समयr has expired and
			 * reschedule the tasklet; continually until the
			 * next context चयन or other preeemption event.
			 *
			 * Since we have decided to reschedule based on
			 * consumption of this बारlice, अगर we submit the
			 * same context again, grant it a full बारlice.
			 */
			cancel_समयr(&execlists->समयr);
			ring_set_छोड़ोd(engine, 1);
			defer_active(engine);

			/*
			 * Unlike क्रम preemption, अगर we शुरुआत and जारी
			 * executing the same context as previously active,
			 * the order of execution will reमुख्य the same and
			 * the tail will only advance. We करो not need to
			 * क्रमce a full context restore, as a lite-restore
			 * is sufficient to resample the monotonic TAIL.
			 *
			 * If we चयन to any other context, similarly we
			 * will not शुरुआत TAIL of current context, and
			 * normal save/restore will preserve state and allow
			 * us to later जारी executing the same request.
			 */
			last = शून्य;
		पूर्ण अन्यथा अणु
			/*
			 * Otherwise अगर we alपढ़ोy have a request pending
			 * क्रम execution after the current one, we can
			 * just रुको until the next CS event beक्रमe
			 * queuing more. In either हाल we will क्रमce a
			 * lite-restore preemption event, but अगर we रुको
			 * we hopefully coalesce several updates पूर्णांकo a single
			 * submission.
			 */
			अगर (active[1]) अणु
				/*
				 * Even अगर ELSP[1] is occupied and not worthy
				 * of बारlices, our queue might be.
				 */
				spin_unlock(&engine->active.lock);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* XXX भव is always taking precedence */
	जबतक ((ve = first_भव_engine(engine))) अणु
		काष्ठा i915_request *rq;

		spin_lock(&ve->base.active.lock);

		rq = ve->request;
		अगर (unlikely(!भव_matches(ve, rq, engine)))
			जाओ unlock; /* lost the race to a sibling */

		GEM_BUG_ON(rq->engine != &ve->base);
		GEM_BUG_ON(rq->context != &ve->context);

		अगर (unlikely(rq_prio(rq) < queue_prio(execlists))) अणु
			spin_unlock(&ve->base.active.lock);
			अवरोध;
		पूर्ण

		अगर (last && !can_merge_rq(last, rq)) अणु
			spin_unlock(&ve->base.active.lock);
			spin_unlock(&engine->active.lock);
			वापस; /* leave this क्रम another sibling */
		पूर्ण

		ENGINE_TRACE(engine,
			     "virtual rq=%llx:%lld%s, new engine? %s\n",
			     rq->fence.context,
			     rq->fence.seqno,
			     __i915_request_is_complete(rq) ? "!" :
			     __i915_request_has_started(rq) ? "*" :
			     "",
			     yesno(engine != ve->siblings[0]));

		WRITE_ONCE(ve->request, शून्य);
		WRITE_ONCE(ve->base.execlists.queue_priority_hपूर्णांक, पूर्णांक_न्यून);

		rb = &ve->nodes[engine->id].rb;
		rb_erase_cached(rb, &execlists->भव);
		RB_CLEAR_NODE(rb);

		GEM_BUG_ON(!(rq->execution_mask & engine->mask));
		WRITE_ONCE(rq->engine, engine);

		अगर (__i915_request_submit(rq)) अणु
			/*
			 * Only after we confirm that we will submit
			 * this request (i.e. it has not alपढ़ोy
			 * completed), करो we want to update the context.
			 *
			 * This serves two purposes. It aव्योमs
			 * unnecessary work अगर we are resubmitting an
			 * alपढ़ोy completed request after बारlicing.
			 * But more importantly, it prevents us altering
			 * ve->siblings[] on an idle context, where
			 * we may be using ve->siblings[] in
			 * भव_context_enter / भव_context_निकास.
			 */
			भव_xfer_context(ve, engine);
			GEM_BUG_ON(ve->siblings[0] != engine);

			submit = true;
			last = rq;
		पूर्ण

		i915_request_put(rq);
unlock:
		spin_unlock(&ve->base.active.lock);

		/*
		 * Hmm, we have a bunch of भव engine requests,
		 * but the first one was alपढ़ोy completed (thanks
		 * preempt-to-busy!). Keep looking at the veng queue
		 * until we have no more relevant requests (i.e.
		 * the normal submit queue has higher priority).
		 */
		अगर (submit)
			अवरोध;
	पूर्ण

	जबतक ((rb = rb_first_cached(&execlists->queue))) अणु
		काष्ठा i915_priolist *p = to_priolist(rb);
		काष्ठा i915_request *rq, *rn;

		priolist_क्रम_each_request_consume(rq, rn, p) अणु
			bool merge = true;

			/*
			 * Can we combine this request with the current port?
			 * It has to be the same context/ringbuffer and not
			 * have any exceptions (e.g. GVT saying never to
			 * combine contexts).
			 *
			 * If we can combine the requests, we can execute both
			 * by updating the RING_TAIL to poपूर्णांक to the end of the
			 * second request, and so we never need to tell the
			 * hardware about the first.
			 */
			अगर (last && !can_merge_rq(last, rq)) अणु
				/*
				 * If we are on the second port and cannot
				 * combine this request with the last, then we
				 * are करोne.
				 */
				अगर (port == last_port)
					जाओ करोne;

				/*
				 * We must not populate both ELSP[] with the
				 * same LRCA, i.e. we must submit 2 dअगरferent
				 * contexts अगर we submit 2 ELSP.
				 */
				अगर (last->context == rq->context)
					जाओ करोne;

				अगर (i915_request_has_sentinel(last))
					जाओ करोne;

				/*
				 * We aव्योम submitting भव requests पूर्णांकo
				 * the secondary ports so that we can migrate
				 * the request immediately to another engine
				 * rather than रुको क्रम the primary request.
				 */
				अगर (rq->execution_mask != engine->mask)
					जाओ करोne;

				/*
				 * If GVT overrides us we only ever submit
				 * port[0], leaving port[1] empty. Note that we
				 * also have to be careful that we करोn't queue
				 * the same context (even though a dअगरferent
				 * request) to the second port.
				 */
				अगर (ctx_single_port_submission(last->context) ||
				    ctx_single_port_submission(rq->context))
					जाओ करोne;

				merge = false;
			पूर्ण

			अगर (__i915_request_submit(rq)) अणु
				अगर (!merge) अणु
					*port++ = i915_request_get(last);
					last = शून्य;
				पूर्ण

				GEM_BUG_ON(last &&
					   !can_merge_ctx(last->context,
							  rq->context));
				GEM_BUG_ON(last &&
					   i915_seqno_passed(last->fence.seqno,
							     rq->fence.seqno));

				submit = true;
				last = rq;
			पूर्ण
		पूर्ण

		rb_erase_cached(&p->node, &execlists->queue);
		i915_priolist_मुक्त(p);
	पूर्ण
करोne:
	*port++ = i915_request_get(last);

	/*
	 * Here be a bit of magic! Or sleight-of-hand, whichever you prefer.
	 *
	 * We choose the priority hपूर्णांक such that अगर we add a request of greater
	 * priority than this, we kick the submission tasklet to decide on
	 * the right order of submitting the requests to hardware. We must
	 * also be prepared to reorder requests as they are in-flight on the
	 * HW. We derive the priority hपूर्णांक then as the first "hole" in
	 * the HW submission ports and अगर there are no available slots,
	 * the priority of the lowest executing request, i.e. last.
	 *
	 * When we करो receive a higher priority request पढ़ोy to run from the
	 * user, see queue_request(), the priority hपूर्णांक is bumped to that
	 * request triggering preemption on the next dequeue (or subsequent
	 * पूर्णांकerrupt क्रम secondary ports).
	 */
	execlists->queue_priority_hपूर्णांक = queue_prio(execlists);
	spin_unlock(&engine->active.lock);

	/*
	 * We can skip poking the HW अगर we ended up with exactly the same set
	 * of requests as currently running, e.g. trying to बारlice a pair
	 * of ordered contexts.
	 */
	अगर (submit &&
	    स_भेद(active,
		   execlists->pending,
		   (port - execlists->pending) * माप(*port))) अणु
		*port = शून्य;
		जबतक (port-- != execlists->pending)
			execlists_schedule_in(*port, port - execlists->pending);

		WRITE_ONCE(execlists->yield, -1);
		set_preempt_समयout(engine, *active);
		execlists_submit_ports(engine);
	पूर्ण अन्यथा अणु
		ring_set_छोड़ोd(engine, 0);
		जबतक (port-- != execlists->pending)
			i915_request_put(*port);
		*execlists->pending = शून्य;
	पूर्ण
पूर्ण

अटल व्योम execlists_dequeue_irq(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	local_irq_disable(); /* Suspend पूर्णांकerrupts across request submission */
	execlists_dequeue(engine);
	local_irq_enable(); /* flush irq_work (e.g. bपढ़ोcrumb enabling) */
पूर्ण

अटल व्योम clear_ports(काष्ठा i915_request **ports, पूर्णांक count)
अणु
	स_रखो_p((व्योम **)ports, शून्य, count);
पूर्ण

अटल व्योम
copy_ports(काष्ठा i915_request **dst, काष्ठा i915_request **src, पूर्णांक count)
अणु
	/* A स_नकल_p() would be very useful here! */
	जबतक (count--)
		WRITE_ONCE(*dst++, *src++); /* aव्योम ग_लिखो tearing */
पूर्ण

अटल काष्ठा i915_request **
cancel_port_requests(काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists,
		     काष्ठा i915_request **inactive)
अणु
	काष्ठा i915_request * स्थिर *port;

	क्रम (port = execlists->pending; *port; port++)
		*inactive++ = *port;
	clear_ports(execlists->pending, ARRAY_SIZE(execlists->pending));

	/* Mark the end of active beक्रमe we overग_लिखो *active */
	क्रम (port = xchg(&execlists->active, execlists->pending); *port; port++)
		*inactive++ = *port;
	clear_ports(execlists->inflight, ARRAY_SIZE(execlists->inflight));

	smp_wmb(); /* complete the seqlock क्रम execlists_active() */
	WRITE_ONCE(execlists->active, execlists->inflight);

	/* Having cancelled all outstanding process_csb(), stop their समयrs */
	GEM_BUG_ON(execlists->pending[0]);
	cancel_समयr(&execlists->समयr);
	cancel_समयr(&execlists->preempt);

	वापस inactive;
पूर्ण

अटल व्योम invalidate_csb_entries(स्थिर u64 *first, स्थिर u64 *last)
अणु
	clflush((व्योम *)first);
	clflush((व्योम *)last);
पूर्ण

/*
 * Starting with Gen12, the status has a new क्रमmat:
 *
 *     bit  0:     चयनed to new queue
 *     bit  1:     reserved
 *     bit  2:     semaphore रुको mode (poll or संकेत), only valid when
 *                 चयन detail is set to "wait on semaphore"
 *     bits 3-5:   engine class
 *     bits 6-11:  engine instance
 *     bits 12-14: reserved
 *     bits 15-25: sw context id of the lrc the GT चयनed to
 *     bits 26-31: sw counter of the lrc the GT चयनed to
 *     bits 32-35: context चयन detail
 *                  - 0: ctx complete
 *                  - 1: रुको on sync flip
 *                  - 2: रुको on vblank
 *                  - 3: रुको on scanline
 *                  - 4: रुको on semaphore
 *                  - 5: context preempted (not on SEMAPHORE_WAIT or
 *                       WAIT_FOR_EVENT)
 *     bit  36:    reserved
 *     bits 37-43: रुको detail (क्रम चयन detail 1 to 4)
 *     bits 44-46: reserved
 *     bits 47-57: sw context id of the lrc the GT चयनed away from
 *     bits 58-63: sw counter of the lrc the GT चयनed away from
 */
अटल bool gen12_csb_parse(स्थिर u64 csb)
अणु
	bool ctx_away_valid = GEN12_CSB_CTX_VALID(upper_32_bits(csb));
	bool new_queue =
		lower_32_bits(csb) & GEN12_CTX_STATUS_SWITCHED_TO_NEW_QUEUE;

	/*
	 * The context चयन detail is not guaranteed to be 5 when a preemption
	 * occurs, so we can't just check क्रम that. The check below works क्रम
	 * all the हालs we care about, including preemptions of WAIT
	 * inकाष्ठाions and lite-restore. Preempt-to-idle via the CTRL रेजिस्टर
	 * would require some extra handling, but we करोn't support that.
	 */
	अगर (!ctx_away_valid || new_queue) अणु
		GEM_BUG_ON(!GEN12_CSB_CTX_VALID(lower_32_bits(csb)));
		वापस true;
	पूर्ण

	/*
	 * चयन detail = 5 is covered by the हाल above and we करो not expect a
	 * context चयन on an unsuccessful रुको inकाष्ठाion since we always
	 * use polling mode.
	 */
	GEM_BUG_ON(GEN12_CTX_SWITCH_DETAIL(upper_32_bits(csb)));
	वापस false;
पूर्ण

अटल bool gen8_csb_parse(स्थिर u64 csb)
अणु
	वापस csb & (GEN8_CTX_STATUS_IDLE_ACTIVE | GEN8_CTX_STATUS_PREEMPTED);
पूर्ण

अटल noअंतरभूत u64
wa_csb_पढ़ो(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, u64 * स्थिर csb)
अणु
	u64 entry;

	/*
	 * Reading from the HWSP has one particular advantage: we can detect
	 * a stale entry. Since the ग_लिखो पूर्णांकo HWSP is broken, we have no reason
	 * to trust the HW at all, the mmio entry may equally be unordered, so
	 * we prefer the path that is self-checking and as a last resort,
	 * वापस the mmio value.
	 *
	 * tgl,dg1:HSDES#22011327657
	 */
	preempt_disable();
	अगर (रुको_क्रम_atomic_us((entry = READ_ONCE(*csb)) != -1, 10)) अणु
		पूर्णांक idx = csb - engine->execlists.csb_status;
		पूर्णांक status;

		status = GEN8_EXECLISTS_STATUS_BUF;
		अगर (idx >= 6) अणु
			status = GEN11_EXECLISTS_STATUS_BUF2;
			idx -= 6;
		पूर्ण
		status += माप(u64) * idx;

		entry = पूर्णांकel_uncore_पढ़ो64(engine->uncore,
					    _MMIO(engine->mmio_base + status));
	पूर्ण
	preempt_enable();

	वापस entry;
पूर्ण

अटल u64 csb_पढ़ो(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, u64 * स्थिर csb)
अणु
	u64 entry = READ_ONCE(*csb);

	/*
	 * Unक्रमtunately, the GPU करोes not always serialise its ग_लिखो
	 * of the CSB entries beक्रमe its ग_लिखो of the CSB poपूर्णांकer, at least
	 * from the perspective of the CPU, using what is known as a Global
	 * Observation Poपूर्णांक. We may पढ़ो a new CSB tail poपूर्णांकer, but then
	 * पढ़ो the stale CSB entries, causing us to misपूर्णांकerpret the
	 * context-चयन events, and eventually declare the GPU hung.
	 *
	 * icl:HSDES#1806554093
	 * tgl:HSDES#22011248461
	 */
	अगर (unlikely(entry == -1))
		entry = wa_csb_पढ़ो(engine, csb);

	/* Consume this entry so that we can spot its future reuse. */
	WRITE_ONCE(*csb, -1);

	/* ELSP is an implicit wmb() beक्रमe the GPU wraps and overग_लिखोs csb */
	वापस entry;
पूर्ण

अटल व्योम new_बारlice(काष्ठा पूर्णांकel_engine_execlists *el)
अणु
	/* By cancelling, we will start afresh in start_बारlice() */
	cancel_समयr(&el->समयr);
पूर्ण

अटल काष्ठा i915_request **
process_csb(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा i915_request **inactive)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	u64 * स्थिर buf = execlists->csb_status;
	स्थिर u8 num_entries = execlists->csb_size;
	काष्ठा i915_request **prev;
	u8 head, tail;

	/*
	 * As we modअगरy our execlists state tracking we require exclusive
	 * access. Either we are inside the tasklet, or the tasklet is disabled
	 * and we assume that is only inside the reset paths and so serialised.
	 */
	GEM_BUG_ON(!tasklet_is_locked(&execlists->tasklet) &&
		   !reset_in_progress(execlists));
	GEM_BUG_ON(!पूर्णांकel_engine_in_execlists_submission_mode(engine));

	/*
	 * Note that csb_ग_लिखो, csb_status may be either in HWSP or mmio.
	 * When पढ़ोing from the csb_ग_लिखो mmio रेजिस्टर, we have to be
	 * careful to only use the GEN8_CSB_WRITE_PTR portion, which is
	 * the low 4bits. As it happens we know the next 4bits are always
	 * zero and so we can simply masked off the low u8 of the रेजिस्टर
	 * and treat it identically to पढ़ोing from the HWSP (without having
	 * to use explicit shअगरting and masking, and probably bअगरurcating
	 * the code to handle the legacy mmio पढ़ो).
	 */
	head = execlists->csb_head;
	tail = READ_ONCE(*execlists->csb_ग_लिखो);
	अगर (unlikely(head == tail))
		वापस inactive;

	/*
	 * We will consume all events from HW, or at least pretend to.
	 *
	 * The sequence of events from the HW is deterministic, and derived
	 * from our ग_लिखोs to the ELSP, with a smidgen of variability क्रम
	 * the arrival of the asynchronous requests wrt to the inflight
	 * execution. If the HW sends an event that करोes not correspond with
	 * the one we are expecting, we have to abanकरोn all hope as we lose
	 * all tracking of what the engine is actually executing. We will
	 * only detect we are out of sequence with the HW when we get an
	 * 'impossible' event because we have alपढ़ोy drained our own
	 * preemption/promotion queue. If this occurs, we know that we likely
	 * lost track of execution earlier and must unwind and restart, the
	 * simplest way is by stop processing the event queue and क्रमce the
	 * engine to reset.
	 */
	execlists->csb_head = tail;
	ENGINE_TRACE(engine, "cs-irq head=%d, tail=%d\n", head, tail);

	/*
	 * Hopefully paired with a wmb() in HW!
	 *
	 * We must complete the पढ़ो of the ग_लिखो poपूर्णांकer beक्रमe any पढ़ोs
	 * from the CSB, so that we करो not see stale values. Without an rmb
	 * (lfence) the HW may speculatively perक्रमm the CSB[] पढ़ोs *beक्रमe*
	 * we perक्रमm the READ_ONCE(*csb_ग_लिखो).
	 */
	rmb();

	/* Remember who was last running under the समयr */
	prev = inactive;
	*prev = शून्य;

	करो अणु
		bool promote;
		u64 csb;

		अगर (++head == num_entries)
			head = 0;

		/*
		 * We are flying near dragons again.
		 *
		 * We hold a reference to the request in execlist_port[]
		 * but no more than that. We are operating in softirq
		 * context and so cannot hold any mutex or sleep. That
		 * prevents us stopping the requests we are processing
		 * in port[] from being retired simultaneously (the
		 * bपढ़ोcrumb will be complete beक्रमe we see the
		 * context-चयन). As we only hold the reference to the
		 * request, any poपूर्णांकer chasing underneath the request
		 * is subject to a potential use-after-मुक्त. Thus we
		 * store all of the bookkeeping within port[] as
		 * required, and aव्योम using unguarded poपूर्णांकers beneath
		 * request itself. The same applies to the atomic
		 * status notअगरier.
		 */

		csb = csb_पढ़ो(engine, buf + head);
		ENGINE_TRACE(engine, "csb[%d]: status=0x%08x:0x%08x\n",
			     head, upper_32_bits(csb), lower_32_bits(csb));

		अगर (INTEL_GEN(engine->i915) >= 12)
			promote = gen12_csb_parse(csb);
		अन्यथा
			promote = gen8_csb_parse(csb);
		अगर (promote) अणु
			काष्ठा i915_request * स्थिर *old = execlists->active;

			अगर (GEM_WARN_ON(!*execlists->pending)) अणु
				execlists->error_पूर्णांकerrupt |= ERROR_CSB;
				अवरोध;
			पूर्ण

			ring_set_छोड़ोd(engine, 0);

			/* Poपूर्णांक active to the new ELSP; prevent overwriting */
			WRITE_ONCE(execlists->active, execlists->pending);
			smp_wmb(); /* notअगरy execlists_active() */

			/* cancel old inflight, prepare क्रम चयन */
			trace_ports(execlists, "preempted", old);
			जबतक (*old)
				*inactive++ = *old++;

			/* चयन pending to inflight */
			GEM_BUG_ON(!निश्चित_pending_valid(execlists, "promote"));
			copy_ports(execlists->inflight,
				   execlists->pending,
				   execlists_num_ports(execlists));
			smp_wmb(); /* complete the seqlock */
			WRITE_ONCE(execlists->active, execlists->inflight);

			/* XXX Magic delay क्रम tgl */
			ENGINE_POSTING_READ(engine, RING_CONTEXT_STATUS_PTR);

			WRITE_ONCE(execlists->pending[0], शून्य);
		पूर्ण अन्यथा अणु
			अगर (GEM_WARN_ON(!*execlists->active)) अणु
				execlists->error_पूर्णांकerrupt |= ERROR_CSB;
				अवरोध;
			पूर्ण

			/* port0 completed, advanced to port1 */
			trace_ports(execlists, "completed", execlists->active);

			/*
			 * We rely on the hardware being strongly
			 * ordered, that the bपढ़ोcrumb ग_लिखो is
			 * coherent (visible from the CPU) beक्रमe the
			 * user पूर्णांकerrupt is processed. One might assume
			 * that the bपढ़ोcrumb ग_लिखो being beक्रमe the
			 * user पूर्णांकerrupt and the CS event क्रम the context
			 * चयन would thereक्रमe be beक्रमe the CS event
			 * itself...
			 */
			अगर (GEM_SHOW_DEBUG() &&
			    !__i915_request_is_complete(*execlists->active)) अणु
				काष्ठा i915_request *rq = *execlists->active;
				स्थिर u32 *regs __maybe_unused =
					rq->context->lrc_reg_state;

				ENGINE_TRACE(engine,
					     "context completed before request!\n");
				ENGINE_TRACE(engine,
					     "ring:{start:0x%08x, head:%04x, tail:%04x, ctl:%08x, mode:%08x}\n",
					     ENGINE_READ(engine, RING_START),
					     ENGINE_READ(engine, RING_HEAD) & HEAD_ADDR,
					     ENGINE_READ(engine, RING_TAIL) & TAIL_ADDR,
					     ENGINE_READ(engine, RING_CTL),
					     ENGINE_READ(engine, RING_MI_MODE));
				ENGINE_TRACE(engine,
					     "rq:{start:%08x, head:%04x, tail:%04x, seqno:%llx:%d, hwsp:%d}, ",
					     i915_ggtt_offset(rq->ring->vma),
					     rq->head, rq->tail,
					     rq->fence.context,
					     lower_32_bits(rq->fence.seqno),
					     hwsp_seqno(rq));
				ENGINE_TRACE(engine,
					     "ctx:{start:%08x, head:%04x, tail:%04x}, ",
					     regs[CTX_RING_START],
					     regs[CTX_RING_HEAD],
					     regs[CTX_RING_TAIL]);
			पूर्ण

			*inactive++ = *execlists->active++;

			GEM_BUG_ON(execlists->active - execlists->inflight >
				   execlists_num_ports(execlists));
		पूर्ण
	पूर्ण जबतक (head != tail);

	/*
	 * Gen11 has proven to fail wrt global observation poपूर्णांक between
	 * entry and tail update, failing on the ordering and thus
	 * we see an old entry in the context status buffer.
	 *
	 * Forcibly evict out entries क्रम the next gpu csb update,
	 * to increase the odds that we get a fresh entries with non
	 * working hardware. The cost क्रम करोing so comes out mostly with
	 * the wash as hardware, working or not, will need to करो the
	 * invalidation beक्रमe.
	 */
	invalidate_csb_entries(&buf[0], &buf[num_entries - 1]);

	/*
	 * We assume that any event reflects a change in context flow
	 * and merits a fresh बारlice. We reinstall the समयr after
	 * inspecting the queue to see अगर we need to resumbit.
	 */
	अगर (*prev != *execlists->active) /* elide lite-restores */
		new_बारlice(execlists);

	वापस inactive;
पूर्ण

अटल व्योम post_process_csb(काष्ठा i915_request **port,
			     काष्ठा i915_request **last)
अणु
	जबतक (port != last)
		execlists_schedule_out(*port++);
पूर्ण

अटल व्योम __execlists_hold(काष्ठा i915_request *rq)
अणु
	LIST_HEAD(list);

	करो अणु
		काष्ठा i915_dependency *p;

		अगर (i915_request_is_active(rq))
			__i915_request_unsubmit(rq);

		clear_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);
		list_move_tail(&rq->sched.link, &rq->engine->active.hold);
		i915_request_set_hold(rq);
		RQ_TRACE(rq, "on hold\n");

		क्रम_each_रुकोer(p, rq) अणु
			काष्ठा i915_request *w =
				container_of(p->रुकोer, typeof(*w), sched);

			अगर (p->flags & I915_DEPENDENCY_WEAK)
				जारी;

			/* Leave semaphores spinning on the other engines */
			अगर (w->engine != rq->engine)
				जारी;

			अगर (!i915_request_is_पढ़ोy(w))
				जारी;

			अगर (__i915_request_is_complete(w))
				जारी;

			अगर (i915_request_on_hold(w))
				जारी;

			list_move_tail(&w->sched.link, &list);
		पूर्ण

		rq = list_first_entry_or_null(&list, typeof(*rq), sched.link);
	पूर्ण जबतक (rq);
पूर्ण

अटल bool execlists_hold(काष्ठा पूर्णांकel_engine_cs *engine,
			   काष्ठा i915_request *rq)
अणु
	अगर (i915_request_on_hold(rq))
		वापस false;

	spin_lock_irq(&engine->active.lock);

	अगर (__i915_request_is_complete(rq)) अणु /* too late! */
		rq = शून्य;
		जाओ unlock;
	पूर्ण

	/*
	 * Transfer this request onto the hold queue to prevent it
	 * being resumbitted to HW (and potentially completed) beक्रमe we have
	 * released it. Since we may have alपढ़ोy submitted following
	 * requests, we need to हटाओ those as well.
	 */
	GEM_BUG_ON(i915_request_on_hold(rq));
	GEM_BUG_ON(rq->engine != engine);
	__execlists_hold(rq);
	GEM_BUG_ON(list_empty(&engine->active.hold));

unlock:
	spin_unlock_irq(&engine->active.lock);
	वापस rq;
पूर्ण

अटल bool hold_request(स्थिर काष्ठा i915_request *rq)
अणु
	काष्ठा i915_dependency *p;
	bool result = false;

	/*
	 * If one of our ancestors is on hold, we must also be on hold,
	 * otherwise we will bypass it and execute beक्रमe it.
	 */
	rcu_पढ़ो_lock();
	क्रम_each_संकेतer(p, rq) अणु
		स्थिर काष्ठा i915_request *s =
			container_of(p->संकेतer, typeof(*s), sched);

		अगर (s->engine != rq->engine)
			जारी;

		result = i915_request_on_hold(s);
		अगर (result)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

अटल व्योम __execlists_unhold(काष्ठा i915_request *rq)
अणु
	LIST_HEAD(list);

	करो अणु
		काष्ठा i915_dependency *p;

		RQ_TRACE(rq, "hold release\n");

		GEM_BUG_ON(!i915_request_on_hold(rq));
		GEM_BUG_ON(!i915_sw_fence_संकेतed(&rq->submit));

		i915_request_clear_hold(rq);
		list_move_tail(&rq->sched.link,
			       i915_sched_lookup_priolist(rq->engine,
							  rq_prio(rq)));
		set_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);

		/* Also release any children on this engine that are पढ़ोy */
		क्रम_each_रुकोer(p, rq) अणु
			काष्ठा i915_request *w =
				container_of(p->रुकोer, typeof(*w), sched);

			अगर (p->flags & I915_DEPENDENCY_WEAK)
				जारी;

			/* Propagate any change in error status */
			अगर (rq->fence.error)
				i915_request_set_error_once(w, rq->fence.error);

			अगर (w->engine != rq->engine)
				जारी;

			अगर (!i915_request_on_hold(w))
				जारी;

			/* Check that no other parents are also on hold */
			अगर (hold_request(w))
				जारी;

			list_move_tail(&w->sched.link, &list);
		पूर्ण

		rq = list_first_entry_or_null(&list, typeof(*rq), sched.link);
	पूर्ण जबतक (rq);
पूर्ण

अटल व्योम execlists_unhold(काष्ठा पूर्णांकel_engine_cs *engine,
			     काष्ठा i915_request *rq)
अणु
	spin_lock_irq(&engine->active.lock);

	/*
	 * Move this request back to the priority queue, and all of its
	 * children and gअक्रमchildren that were suspended aदीर्घ with it.
	 */
	__execlists_unhold(rq);

	अगर (rq_prio(rq) > engine->execlists.queue_priority_hपूर्णांक) अणु
		engine->execlists.queue_priority_hपूर्णांक = rq_prio(rq);
		tasklet_hi_schedule(&engine->execlists.tasklet);
	पूर्ण

	spin_unlock_irq(&engine->active.lock);
पूर्ण

काष्ठा execlists_capture अणु
	काष्ठा work_काष्ठा work;
	काष्ठा i915_request *rq;
	काष्ठा i915_gpu_coredump *error;
पूर्ण;

अटल व्योम execlists_capture_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा execlists_capture *cap = container_of(work, typeof(*cap), work);
	स्थिर gfp_t gfp = GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN;
	काष्ठा पूर्णांकel_engine_cs *engine = cap->rq->engine;
	काष्ठा पूर्णांकel_gt_coredump *gt = cap->error->gt;
	काष्ठा पूर्णांकel_engine_capture_vma *vma;

	/* Compress all the objects attached to the request, slow! */
	vma = पूर्णांकel_engine_coredump_add_request(gt->engine, cap->rq, gfp);
	अगर (vma) अणु
		काष्ठा i915_vma_compress *compress =
			i915_vma_capture_prepare(gt);

		पूर्णांकel_engine_coredump_add_vma(gt->engine, vma, compress);
		i915_vma_capture_finish(gt, compress);
	पूर्ण

	gt->simulated = gt->engine->simulated;
	cap->error->simulated = gt->simulated;

	/* Publish the error state, and announce it to the world */
	i915_error_state_store(cap->error);
	i915_gpu_coredump_put(cap->error);

	/* Return this request and all that depend upon it क्रम संकेतing */
	execlists_unhold(engine, cap->rq);
	i915_request_put(cap->rq);

	kमुक्त(cap);
पूर्ण

अटल काष्ठा execlists_capture *capture_regs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर gfp_t gfp = GFP_ATOMIC | __GFP_NOWARN;
	काष्ठा execlists_capture *cap;

	cap = kदो_स्मृति(माप(*cap), gfp);
	अगर (!cap)
		वापस शून्य;

	cap->error = i915_gpu_coredump_alloc(engine->i915, gfp);
	अगर (!cap->error)
		जाओ err_cap;

	cap->error->gt = पूर्णांकel_gt_coredump_alloc(engine->gt, gfp);
	अगर (!cap->error->gt)
		जाओ err_gpu;

	cap->error->gt->engine = पूर्णांकel_engine_coredump_alloc(engine, gfp);
	अगर (!cap->error->gt->engine)
		जाओ err_gt;

	cap->error->gt->engine->hung = true;

	वापस cap;

err_gt:
	kमुक्त(cap->error->gt);
err_gpu:
	kमुक्त(cap->error);
err_cap:
	kमुक्त(cap);
	वापस शून्य;
पूर्ण

अटल काष्ठा i915_request *
active_context(काष्ठा पूर्णांकel_engine_cs *engine, u32 ccid)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_execlists * स्थिर el = &engine->execlists;
	काष्ठा i915_request * स्थिर *port, *rq;

	/*
	 * Use the most recent result from process_csb(), but just in हाल
	 * we trigger an error (via पूर्णांकerrupt) beक्रमe the first CS event has
	 * been written, peek at the next submission.
	 */

	क्रम (port = el->active; (rq = *port); port++) अणु
		अगर (rq->context->lrc.ccid == ccid) अणु
			ENGINE_TRACE(engine,
				     "ccid:%x found at active:%zd\n",
				     ccid, port - el->active);
			वापस rq;
		पूर्ण
	पूर्ण

	क्रम (port = el->pending; (rq = *port); port++) अणु
		अगर (rq->context->lrc.ccid == ccid) अणु
			ENGINE_TRACE(engine,
				     "ccid:%x found at pending:%zd\n",
				     ccid, port - el->pending);
			वापस rq;
		पूर्ण
	पूर्ण

	ENGINE_TRACE(engine, "ccid:%x not found\n", ccid);
	वापस शून्य;
पूर्ण

अटल u32 active_ccid(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस ENGINE_READ_FW(engine, RING_EXECLIST_STATUS_HI);
पूर्ण

अटल व्योम execlists_capture(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा execlists_capture *cap;

	अगर (!IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR))
		वापस;

	/*
	 * We need to _quickly_ capture the engine state beक्रमe we reset.
	 * We are inside an atomic section (softirq) here and we are delaying
	 * the क्रमced preemption event.
	 */
	cap = capture_regs(engine);
	अगर (!cap)
		वापस;

	spin_lock_irq(&engine->active.lock);
	cap->rq = active_context(engine, active_ccid(engine));
	अगर (cap->rq) अणु
		cap->rq = active_request(cap->rq->context->समयline, cap->rq);
		cap->rq = i915_request_get_rcu(cap->rq);
	पूर्ण
	spin_unlock_irq(&engine->active.lock);
	अगर (!cap->rq)
		जाओ err_मुक्त;

	/*
	 * Remove the request from the execlists queue, and take ownership
	 * of the request. We pass it to our worker who will _slowly_ compress
	 * all the pages the _user_ requested क्रम debugging their batch, after
	 * which we वापस it to the queue क्रम संकेतing.
	 *
	 * By removing them from the execlists queue, we also हटाओ the
	 * requests from being processed by __unwind_incomplete_requests()
	 * during the पूर्णांकel_engine_reset(), and so they will *not* be replayed
	 * afterwards.
	 *
	 * Note that because we have not yet reset the engine at this poपूर्णांक,
	 * it is possible क्रम the request that we have identअगरied as being
	 * guilty, did in fact complete and we will then hit an arbitration
	 * poपूर्णांक allowing the outstanding preemption to succeed. The likelihood
	 * of that is very low (as capturing of the engine रेजिस्टरs should be
	 * fast enough to run inside an irq-off atomic section!), so we will
	 * simply hold that request accountable क्रम being non-preemptible
	 * दीर्घ enough to क्रमce the reset.
	 */
	अगर (!execlists_hold(engine, cap->rq))
		जाओ err_rq;

	INIT_WORK(&cap->work, execlists_capture_work);
	schedule_work(&cap->work);
	वापस;

err_rq:
	i915_request_put(cap->rq);
err_मुक्त:
	i915_gpu_coredump_put(cap->error);
	kमुक्त(cap);
पूर्ण

अटल व्योम execlists_reset(काष्ठा पूर्णांकel_engine_cs *engine, स्थिर अक्षर *msg)
अणु
	स्थिर अचिन्हित पूर्णांक bit = I915_RESET_ENGINE + engine->id;
	अचिन्हित दीर्घ *lock = &engine->gt->reset.flags;

	अगर (!पूर्णांकel_has_reset_engine(engine->gt))
		वापस;

	अगर (test_and_set_bit(bit, lock))
		वापस;

	ENGINE_TRACE(engine, "reset for %s\n", msg);

	/* Mark this tasklet as disabled to aव्योम रुकोing क्रम it to complete */
	tasklet_disable_nosync(&engine->execlists.tasklet);

	ring_set_छोड़ोd(engine, 1); /* Freeze the current request in place */
	execlists_capture(engine);
	पूर्णांकel_engine_reset(engine, msg);

	tasklet_enable(&engine->execlists.tasklet);
	clear_and_wake_up_bit(bit, lock);
पूर्ण

अटल bool preempt_समयout(स्थिर काष्ठा पूर्णांकel_engine_cs *स्थिर engine)
अणु
	स्थिर काष्ठा समयr_list *t = &engine->execlists.preempt;

	अगर (!CONFIG_DRM_I915_PREEMPT_TIMEOUT)
		वापस false;

	अगर (!समयr_expired(t))
		वापस false;

	वापस engine->execlists.pending[0];
पूर्ण

/*
 * Check the unपढ़ो Context Status Buffers and manage the submission of new
 * contexts to the ELSP accordingly.
 */
अटल व्योम execlists_submission_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा पूर्णांकel_engine_cs * स्थिर engine =
		from_tasklet(engine, t, execlists.tasklet);
	काष्ठा i915_request *post[2 * EXECLIST_MAX_PORTS];
	काष्ठा i915_request **inactive;

	rcu_पढ़ो_lock();
	inactive = process_csb(engine, post);
	GEM_BUG_ON(inactive - post > ARRAY_SIZE(post));

	अगर (unlikely(preempt_समयout(engine))) अणु
		cancel_समयr(&engine->execlists.preempt);
		engine->execlists.error_पूर्णांकerrupt |= ERROR_PREEMPT;
	पूर्ण

	अगर (unlikely(READ_ONCE(engine->execlists.error_पूर्णांकerrupt))) अणु
		स्थिर अक्षर *msg;

		/* Generate the error message in priority wrt to the user! */
		अगर (engine->execlists.error_पूर्णांकerrupt & GENMASK(15, 0))
			msg = "CS error"; /* thrown by a user payload */
		अन्यथा अगर (engine->execlists.error_पूर्णांकerrupt & ERROR_CSB)
			msg = "invalid CSB event";
		अन्यथा अगर (engine->execlists.error_पूर्णांकerrupt & ERROR_PREEMPT)
			msg = "preemption time out";
		अन्यथा
			msg = "internal error";

		engine->execlists.error_पूर्णांकerrupt = 0;
		execlists_reset(engine, msg);
	पूर्ण

	अगर (!engine->execlists.pending[0]) अणु
		execlists_dequeue_irq(engine);
		start_बारlice(engine);
	पूर्ण

	post_process_csb(post, inactive);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम __execlists_kick(काष्ठा पूर्णांकel_engine_execlists *execlists)
अणु
	/* Kick the tasklet क्रम some पूर्णांकerrupt coalescing and reset handling */
	tasklet_hi_schedule(&execlists->tasklet);
पूर्ण

#घोषणा execlists_kick(t, member) \
	__execlists_kick(container_of(t, काष्ठा पूर्णांकel_engine_execlists, member))

अटल व्योम execlists_बारlice(काष्ठा समयr_list *समयr)
अणु
	execlists_kick(समयr, समयr);
पूर्ण

अटल व्योम execlists_preempt(काष्ठा समयr_list *समयr)
अणु
	execlists_kick(समयr, preempt);
पूर्ण

अटल व्योम queue_request(काष्ठा पूर्णांकel_engine_cs *engine,
			  काष्ठा i915_request *rq)
अणु
	GEM_BUG_ON(!list_empty(&rq->sched.link));
	list_add_tail(&rq->sched.link,
		      i915_sched_lookup_priolist(engine, rq_prio(rq)));
	set_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);
पूर्ण

अटल bool submit_queue(काष्ठा पूर्णांकel_engine_cs *engine,
			 स्थिर काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_execlists *execlists = &engine->execlists;

	अगर (rq_prio(rq) <= execlists->queue_priority_hपूर्णांक)
		वापस false;

	execlists->queue_priority_hपूर्णांक = rq_prio(rq);
	वापस true;
पूर्ण

अटल bool ancestor_on_hold(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			     स्थिर काष्ठा i915_request *rq)
अणु
	GEM_BUG_ON(i915_request_on_hold(rq));
	वापस !list_empty(&engine->active.hold) && hold_request(rq);
पूर्ण

अटल व्योम execlists_submit_request(काष्ठा i915_request *request)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = request->engine;
	अचिन्हित दीर्घ flags;

	/* Will be called from irq-context when using क्रमeign fences. */
	spin_lock_irqsave(&engine->active.lock, flags);

	अगर (unlikely(ancestor_on_hold(engine, request))) अणु
		RQ_TRACE(request, "ancestor on hold\n");
		list_add_tail(&request->sched.link, &engine->active.hold);
		i915_request_set_hold(request);
	पूर्ण अन्यथा अणु
		queue_request(engine, request);

		GEM_BUG_ON(RB_EMPTY_ROOT(&engine->execlists.queue.rb_root));
		GEM_BUG_ON(list_empty(&request->sched.link));

		अगर (submit_queue(engine, request))
			__execlists_kick(&engine->execlists);
	पूर्ण

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल पूर्णांक
__execlists_context_pre_pin(काष्ठा पूर्णांकel_context *ce,
			    काष्ठा पूर्णांकel_engine_cs *engine,
			    काष्ठा i915_gem_ww_ctx *ww, व्योम **vaddr)
अणु
	पूर्णांक err;

	err = lrc_pre_pin(ce, engine, ww, vaddr);
	अगर (err)
		वापस err;

	अगर (!__test_and_set_bit(CONTEXT_INIT_BIT, &ce->flags)) अणु
		lrc_init_state(ce, engine, *vaddr);

		 __i915_gem_object_flush_map(ce->state->obj, 0, engine->context_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक execlists_context_pre_pin(काष्ठा पूर्णांकel_context *ce,
				     काष्ठा i915_gem_ww_ctx *ww,
				     व्योम **vaddr)
अणु
	वापस __execlists_context_pre_pin(ce, ce->engine, ww, vaddr);
पूर्ण

अटल पूर्णांक execlists_context_pin(काष्ठा पूर्णांकel_context *ce, व्योम *vaddr)
अणु
	वापस lrc_pin(ce, ce->engine, vaddr);
पूर्ण

अटल पूर्णांक execlists_context_alloc(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस lrc_alloc(ce, ce->engine);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_context_ops execlists_context_ops = अणु
	.flags = COPS_HAS_INFLIGHT,

	.alloc = execlists_context_alloc,

	.pre_pin = execlists_context_pre_pin,
	.pin = execlists_context_pin,
	.unpin = lrc_unpin,
	.post_unpin = lrc_post_unpin,

	.enter = पूर्णांकel_context_enter_engine,
	.निकास = पूर्णांकel_context_निकास_engine,

	.reset = lrc_reset,
	.destroy = lrc_destroy,
पूर्ण;

अटल पूर्णांक emit_pdps(काष्ठा i915_request *rq)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs * स्थिर engine = rq->engine;
	काष्ठा i915_ppgtt * स्थिर ppgtt = i915_vm_to_ppgtt(rq->context->vm);
	पूर्णांक err, i;
	u32 *cs;

	GEM_BUG_ON(पूर्णांकel_vgpu_active(rq->engine->i915));

	/*
	 * Beware ye of the dragons, this sequence is magic!
	 *
	 * Small changes to this sequence can cause anything from
	 * GPU hangs to क्रमcewake errors and machine lockups!
	 */

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	/* Flush any residual operations from the context load */
	err = engine->emit_flush(rq, EMIT_FLUSH);
	अगर (err)
		वापस err;

	/* Magic required to prevent क्रमcewake errors! */
	err = engine->emit_flush(rq, EMIT_INVALIDATE);
	अगर (err)
		वापस err;

	cs = पूर्णांकel_ring_begin(rq, 4 * GEN8_3LVL_PDPES + 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	/* Ensure the LRI have landed beक्रमe we invalidate & जारी */
	*cs++ = MI_LOAD_REGISTER_IMM(2 * GEN8_3LVL_PDPES) | MI_LRI_FORCE_POSTED;
	क्रम (i = GEN8_3LVL_PDPES; i--; ) अणु
		स्थिर dma_addr_t pd_daddr = i915_page_dir_dma_addr(ppgtt, i);
		u32 base = engine->mmio_base;

		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_UDW(base, i));
		*cs++ = upper_32_bits(pd_daddr);
		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_LDW(base, i));
		*cs++ = lower_32_bits(pd_daddr);
	पूर्ण
	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	पूर्णांकel_ring_advance(rq, cs);

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक execlists_request_alloc(काष्ठा i915_request *request)
अणु
	पूर्णांक ret;

	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(request->context));

	/*
	 * Flush enough space to reduce the likelihood of रुकोing after
	 * we start building the request - in which हाल we will just
	 * have to repeat work.
	 */
	request->reserved_space += EXECLISTS_REQUEST_SIZE;

	/*
	 * Note that after this poपूर्णांक, we have committed to using
	 * this request as it is being used to both track the
	 * state of engine initialisation and liveness of the
	 * golden renderstate above. Think twice beक्रमe you try
	 * to cancel/unwind this request now.
	 */

	अगर (!i915_vm_is_4lvl(request->context->vm)) अणु
		ret = emit_pdps(request);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Unconditionally invalidate GPU caches and TLBs. */
	ret = request->engine->emit_flush(request, EMIT_INVALIDATE);
	अगर (ret)
		वापस ret;

	request->reserved_space -= EXECLISTS_REQUEST_SIZE;
	वापस 0;
पूर्ण

अटल व्योम reset_csb_poपूर्णांकers(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	स्थिर अचिन्हित पूर्णांक reset_value = execlists->csb_size - 1;

	ring_set_छोड़ोd(engine, 0);

	/*
	 * Someबार Icelake क्रममाला_लो to reset its poपूर्णांकers on a GPU reset.
	 * Bludgeon them with a mmio update to be sure.
	 */
	ENGINE_WRITE(engine, RING_CONTEXT_STATUS_PTR,
		     0xffff << 16 | reset_value << 8 | reset_value);
	ENGINE_POSTING_READ(engine, RING_CONTEXT_STATUS_PTR);

	/*
	 * After a reset, the HW starts writing पूर्णांकo CSB entry [0]. We
	 * thereक्रमe have to set our HEAD poपूर्णांकer back one entry so that
	 * the *first* entry we check is entry 0. To complicate this further,
	 * as we करोn't रुको क्रम the first पूर्णांकerrupt after reset, we have to
	 * fake the HW ग_लिखो to poपूर्णांक back to the last entry so that our
	 * अंतरभूत comparison of our cached head position against the last HW
	 * ग_लिखो works even beक्रमe the first पूर्णांकerrupt.
	 */
	execlists->csb_head = reset_value;
	WRITE_ONCE(*execlists->csb_ग_लिखो, reset_value);
	wmb(); /* Make sure this is visible to HW (paranoia?) */

	/* Check that the GPU करोes indeed update the CSB entries! */
	स_रखो(execlists->csb_status, -1, (reset_value + 1) * माप(u64));
	invalidate_csb_entries(&execlists->csb_status[0],
			       &execlists->csb_status[reset_value]);

	/* Once more क्रम luck and our trusty paranoia */
	ENGINE_WRITE(engine, RING_CONTEXT_STATUS_PTR,
		     0xffff << 16 | reset_value << 8 | reset_value);
	ENGINE_POSTING_READ(engine, RING_CONTEXT_STATUS_PTR);

	GEM_BUG_ON(READ_ONCE(*execlists->csb_ग_लिखो) != reset_value);
पूर्ण

अटल व्योम sanitize_hwsp(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_समयline *tl;

	list_क्रम_each_entry(tl, &engine->status_page.समयlines, engine_link)
		पूर्णांकel_समयline_reset_seqno(tl);
पूर्ण

अटल व्योम execlists_sanitize(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	GEM_BUG_ON(execlists_active(&engine->execlists));

	/*
	 * Poison residual state on resume, in हाल the suspend didn't!
	 *
	 * We have to assume that across suspend/resume (or other loss
	 * of control) that the contents of our pinned buffers has been
	 * lost, replaced by garbage. Since this करोesn't always happen,
	 * let's poison such state so that we more quickly spot when
	 * we falsely assume it has been preserved.
	 */
	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		स_रखो(engine->status_page.addr, POISON_INUSE, PAGE_SIZE);

	reset_csb_poपूर्णांकers(engine);

	/*
	 * The kernel_context HWSP is stored in the status_page. As above,
	 * that may be lost on resume/initialisation, and so we need to
	 * reset the value in the HWSP.
	 */
	sanitize_hwsp(engine);

	/* And scrub the dirty cachelines क्रम the HWSP */
	clflush_cache_range(engine->status_page.addr, PAGE_SIZE);
पूर्ण

अटल व्योम enable_error_पूर्णांकerrupt(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	u32 status;

	engine->execlists.error_पूर्णांकerrupt = 0;
	ENGINE_WRITE(engine, RING_EMR, ~0u);
	ENGINE_WRITE(engine, RING_EIR, ~0u); /* clear all existing errors */

	status = ENGINE_READ(engine, RING_ESR);
	अगर (unlikely(status)) अणु
		drm_err(&engine->i915->drm,
			"engine '%s' resumed still in error: %08x\n",
			engine->name, status);
		__पूर्णांकel_gt_reset(engine->gt, engine->mask);
	पूर्ण

	/*
	 * On current gen8+, we have 2 संकेतs to play with
	 *
	 * - I915_ERROR_INSTUCTION (bit 0)
	 *
	 *    Generate an error अगर the command parser encounters an invalid
	 *    inकाष्ठाion
	 *
	 *    This is a fatal error.
	 *
	 * - CP_PRIV (bit 2)
	 *
	 *    Generate an error on privilege violation (where the CP replaces
	 *    the inकाष्ठाion with a no-op). This also fires क्रम ग_लिखोs पूर्णांकo
	 *    पढ़ो-only scratch pages.
	 *
	 *    This is a non-fatal error, parsing जारीs.
	 *
	 * * there are a few others defined क्रम odd HW that we करो not use
	 *
	 * Since CP_PRIV fires क्रम हालs where we have chosen to ignore the
	 * error (as the HW is validating and suppressing the mistakes), we
	 * only unmask the inकाष्ठाion error bit.
	 */
	ENGINE_WRITE(engine, RING_EMR, ~I915_ERROR_INSTRUCTION);
पूर्ण

अटल व्योम enable_execlists(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	u32 mode;

	निश्चित_क्रमcewakes_active(engine->uncore, FORCEWAKE_ALL);

	पूर्णांकel_engine_set_hwsp_ग_लिखोmask(engine, ~0u); /* HWSTAM */

	अगर (INTEL_GEN(engine->i915) >= 11)
		mode = _MASKED_BIT_ENABLE(GEN11_GFX_DISABLE_LEGACY_MODE);
	अन्यथा
		mode = _MASKED_BIT_ENABLE(GFX_RUN_LIST_ENABLE);
	ENGINE_WRITE_FW(engine, RING_MODE_GEN7, mode);

	ENGINE_WRITE_FW(engine, RING_MI_MODE, _MASKED_BIT_DISABLE(STOP_RING));

	ENGINE_WRITE_FW(engine,
			RING_HWS_PGA,
			i915_ggtt_offset(engine->status_page.vma));
	ENGINE_POSTING_READ(engine, RING_HWS_PGA);

	enable_error_पूर्णांकerrupt(engine);
पूर्ण

अटल पूर्णांक execlists_resume(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_mocs_init_engine(engine);
	पूर्णांकel_bपढ़ोcrumbs_reset(engine->bपढ़ोcrumbs);

	enable_execlists(engine);

	वापस 0;
पूर्ण

अटल व्योम execlists_reset_prepare(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;

	ENGINE_TRACE(engine, "depth<-%d\n",
		     atomic_पढ़ो(&execlists->tasklet.count));

	/*
	 * Prevent request submission to the hardware until we have
	 * completed the reset in i915_gem_reset_finish(). If a request
	 * is completed by one engine, it may then queue a request
	 * to a second via its execlists->tasklet *just* as we are
	 * calling engine->resume() and also writing the ELSP.
	 * Turning off the execlists->tasklet until the reset is over
	 * prevents the race.
	 */
	__tasklet_disable_sync_once(&execlists->tasklet);
	GEM_BUG_ON(!reset_in_progress(execlists));

	/*
	 * We stop engines, otherwise we might get failed reset and a
	 * dead gpu (on elk). Also as modern gpu as kbl can suffer
	 * from प्रणाली hang अगर batchbuffer is progressing when
	 * the reset is issued, regardless of READY_TO_RESET ack.
	 * Thus assume it is best to stop engines on all gens
	 * where we have a gpu reset.
	 *
	 * WaKBLVECSSemaphoreWaitPoll:kbl (on ALL_ENGINES)
	 *
	 * FIXME: Wa क्रम more modern gens needs to be validated
	 */
	ring_set_छोड़ोd(engine, 1);
	पूर्णांकel_engine_stop_cs(engine);

	engine->execlists.reset_ccid = active_ccid(engine);
पूर्ण

अटल काष्ठा i915_request **
reset_csb(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा i915_request **inactive)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;

	mb(); /* paranoia: पढ़ो the CSB poपूर्णांकers from after the reset */
	clflush(execlists->csb_ग_लिखो);
	mb();

	inactive = process_csb(engine, inactive); /* drain preemption events */

	/* Following the reset, we need to reload the CSB पढ़ो/ग_लिखो poपूर्णांकers */
	reset_csb_poपूर्णांकers(engine);

	वापस inactive;
पूर्ण

अटल व्योम
execlists_reset_active(काष्ठा पूर्णांकel_engine_cs *engine, bool stalled)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	u32 head;

	/*
	 * Save the currently executing context, even अगर we completed
	 * its request, it was still running at the समय of the
	 * reset and will have been clobbered.
	 */
	rq = active_context(engine, engine->execlists.reset_ccid);
	अगर (!rq)
		वापस;

	ce = rq->context;
	GEM_BUG_ON(!i915_vma_is_pinned(ce->state));

	अगर (__i915_request_is_complete(rq)) अणु
		/* Idle context; tidy up the ring so we can restart afresh */
		head = पूर्णांकel_ring_wrap(ce->ring, rq->tail);
		जाओ out_replay;
	पूर्ण

	/* We still have requests in-flight; the engine should be active */
	GEM_BUG_ON(!पूर्णांकel_engine_pm_is_awake(engine));

	/* Context has requests still in-flight; it should not be idle! */
	GEM_BUG_ON(i915_active_is_idle(&ce->active));

	rq = active_request(ce->समयline, rq);
	head = पूर्णांकel_ring_wrap(ce->ring, rq->head);
	GEM_BUG_ON(head == ce->ring->tail);

	/*
	 * If this request hasn't started yet, e.g. it is रुकोing on a
	 * semaphore, we need to aव्योम skipping the request or अन्यथा we
	 * अवरोध the संकेतing chain. However, अगर the context is corrupt
	 * the request will not restart and we will be stuck with a wedged
	 * device. It is quite often the हाल that अगर we issue a reset
	 * जबतक the GPU is loading the context image, that the context
	 * image becomes corrupt.
	 *
	 * Otherwise, अगर we have not started yet, the request should replay
	 * perfectly and we करो not need to flag the result as being erroneous.
	 */
	अगर (!__i915_request_has_started(rq))
		जाओ out_replay;

	/*
	 * If the request was innocent, we leave the request in the ELSP
	 * and will try to replay it on restarting. The context image may
	 * have been corrupted by the reset, in which हाल we may have
	 * to service a new GPU hang, but more likely we can जारी on
	 * without impact.
	 *
	 * If the request was guilty, we presume the context is corrupt
	 * and have to at least restore the RING रेजिस्टर in the context
	 * image back to the expected values to skip over the guilty request.
	 */
	__i915_request_reset(rq, stalled);

	/*
	 * We want a simple context + ring to execute the bपढ़ोcrumb update.
	 * We cannot rely on the context being पूर्णांकact across the GPU hang,
	 * so clear it and rebuild just what we need क्रम the bपढ़ोcrumb.
	 * All pending requests क्रम this context will be zapped, and any
	 * future request will be after userspace has had the opportunity
	 * to recreate its own state.
	 */
out_replay:
	ENGINE_TRACE(engine, "replay {head:%04x, tail:%04x}\n",
		     head, ce->ring->tail);
	lrc_reset_regs(ce, engine);
	ce->lrc.lrca = lrc_update_regs(ce, engine, head);
पूर्ण

अटल व्योम execlists_reset_csb(काष्ठा पूर्णांकel_engine_cs *engine, bool stalled)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा i915_request *post[2 * EXECLIST_MAX_PORTS];
	काष्ठा i915_request **inactive;

	rcu_पढ़ो_lock();
	inactive = reset_csb(engine, post);

	execlists_reset_active(engine, true);

	inactive = cancel_port_requests(execlists, inactive);
	post_process_csb(post, inactive);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम execlists_reset_शुरुआत(काष्ठा पूर्णांकel_engine_cs *engine, bool stalled)
अणु
	अचिन्हित दीर्घ flags;

	ENGINE_TRACE(engine, "\n");

	/* Process the csb, find the guilty context and throw away */
	execlists_reset_csb(engine, stalled);

	/* Push back any incomplete requests क्रम replay after the reset. */
	rcu_पढ़ो_lock();
	spin_lock_irqsave(&engine->active.lock, flags);
	__unwind_incomplete_requests(engine);
	spin_unlock_irqrestore(&engine->active.lock, flags);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम nop_submission_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा पूर्णांकel_engine_cs * स्थिर engine =
		from_tasklet(engine, t, execlists.tasklet);

	/* The driver is wedged; करोn't process any more events. */
	WRITE_ONCE(engine->execlists.queue_priority_hपूर्णांक, पूर्णांक_न्यून);
पूर्ण

अटल व्योम execlists_reset_cancel(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा i915_request *rq, *rn;
	काष्ठा rb_node *rb;
	अचिन्हित दीर्घ flags;

	ENGINE_TRACE(engine, "\n");

	/*
	 * Beक्रमe we call engine->cancel_requests(), we should have exclusive
	 * access to the submission state. This is arranged क्रम us by the
	 * caller disabling the पूर्णांकerrupt generation, the tasklet and other
	 * thपढ़ोs that may then access the same state, giving us a मुक्त hand
	 * to reset state. However, we still need to let lockdep be aware that
	 * we know this state may be accessed in hardirq context, so we
	 * disable the irq around this manipulation and we want to keep
	 * the spinlock focused on its duties and not accidentally conflate
	 * coverage to the submission's irq state. (Similarly, although we
	 * shouldn't need to disable irq around the manipulation of the
	 * submission's irq state, we also wish to remind ourselves that
	 * it is irq state.)
	 */
	execlists_reset_csb(engine, true);

	rcu_पढ़ो_lock();
	spin_lock_irqsave(&engine->active.lock, flags);

	/* Mark all executing requests as skipped. */
	list_क्रम_each_entry(rq, &engine->active.requests, sched.link)
		i915_request_put(i915_request_mark_eio(rq));
	पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(engine);

	/* Flush the queued requests to the समयline list (क्रम retiring). */
	जबतक ((rb = rb_first_cached(&execlists->queue))) अणु
		काष्ठा i915_priolist *p = to_priolist(rb);

		priolist_क्रम_each_request_consume(rq, rn, p) अणु
			अगर (i915_request_mark_eio(rq)) अणु
				__i915_request_submit(rq);
				i915_request_put(rq);
			पूर्ण
		पूर्ण

		rb_erase_cached(&p->node, &execlists->queue);
		i915_priolist_मुक्त(p);
	पूर्ण

	/* On-hold requests will be flushed to समयline upon their release */
	list_क्रम_each_entry(rq, &engine->active.hold, sched.link)
		i915_request_put(i915_request_mark_eio(rq));

	/* Cancel all attached भव engines */
	जबतक ((rb = rb_first_cached(&execlists->भव))) अणु
		काष्ठा भव_engine *ve =
			rb_entry(rb, typeof(*ve), nodes[engine->id].rb);

		rb_erase_cached(rb, &execlists->भव);
		RB_CLEAR_NODE(rb);

		spin_lock(&ve->base.active.lock);
		rq = fetch_and_zero(&ve->request);
		अगर (rq) अणु
			अगर (i915_request_mark_eio(rq)) अणु
				rq->engine = engine;
				__i915_request_submit(rq);
				i915_request_put(rq);
			पूर्ण
			i915_request_put(rq);

			ve->base.execlists.queue_priority_hपूर्णांक = पूर्णांक_न्यून;
		पूर्ण
		spin_unlock(&ve->base.active.lock);
	पूर्ण

	/* Reमुख्यing _unपढ़ोy_ requests will be nop'ed when submitted */

	execlists->queue_priority_hपूर्णांक = पूर्णांक_न्यून;
	execlists->queue = RB_ROOT_CACHED;

	GEM_BUG_ON(__tasklet_is_enabled(&execlists->tasklet));
	execlists->tasklet.callback = nop_submission_tasklet;

	spin_unlock_irqrestore(&engine->active.lock, flags);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम execlists_reset_finish(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;

	/*
	 * After a GPU reset, we may have requests to replay. Do so now जबतक
	 * we still have the क्रमcewake to be sure that the GPU is not allowed
	 * to sleep beक्रमe we restart and reload a context.
	 *
	 * If the GPU reset fails, the engine may still be alive with requests
	 * inflight. We expect those to complete, or क्रम the device to be
	 * reset as the next level of recovery, and as a final resort we
	 * will declare the device wedged.
	 */
	GEM_BUG_ON(!reset_in_progress(execlists));

	/* And kick in हाल we missed a new request submission. */
	अगर (__tasklet_enable(&execlists->tasklet))
		__execlists_kick(execlists);

	ENGINE_TRACE(engine, "depth->%d\n",
		     atomic_पढ़ो(&execlists->tasklet.count));
पूर्ण

अटल व्योम gen8_logical_ring_enable_irq(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_WRITE(engine, RING_IMR,
		     ~(engine->irq_enable_mask | engine->irq_keep_mask));
	ENGINE_POSTING_READ(engine, RING_IMR);
पूर्ण

अटल व्योम gen8_logical_ring_disable_irq(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_WRITE(engine, RING_IMR, ~engine->irq_keep_mask);
पूर्ण

अटल व्योम execlists_park(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	cancel_समयr(&engine->execlists.समयr);
	cancel_समयr(&engine->execlists.preempt);
पूर्ण

अटल bool can_preempt(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (INTEL_GEN(engine->i915) > 8)
		वापस true;

	/* GPGPU on bdw requires extra w/a; not implemented */
	वापस engine->class != RENDER_CLASS;
पूर्ण

अटल व्योम execlists_set_शेष_submission(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->submit_request = execlists_submit_request;
	engine->schedule = i915_schedule;
	engine->execlists.tasklet.callback = execlists_submission_tasklet;

	engine->reset.prepare = execlists_reset_prepare;
	engine->reset.शुरुआत = execlists_reset_शुरुआत;
	engine->reset.cancel = execlists_reset_cancel;
	engine->reset.finish = execlists_reset_finish;

	engine->park = execlists_park;
	engine->unpark = शून्य;

	engine->flags |= I915_ENGINE_SUPPORTS_STATS;
	अगर (!पूर्णांकel_vgpu_active(engine->i915)) अणु
		engine->flags |= I915_ENGINE_HAS_SEMAPHORES;
		अगर (can_preempt(engine)) अणु
			engine->flags |= I915_ENGINE_HAS_PREEMPTION;
			अगर (IS_ACTIVE(CONFIG_DRM_I915_TIMESLICE_DURATION))
				engine->flags |= I915_ENGINE_HAS_TIMESLICES;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकel_engine_has_preemption(engine))
		engine->emit_bb_start = gen8_emit_bb_start;
	अन्यथा
		engine->emit_bb_start = gen8_emit_bb_start_noarb;
पूर्ण

अटल व्योम execlists_shutकरोwn(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/* Synchronise with residual समयrs and any softirq they उठाओ */
	del_समयr_sync(&engine->execlists.समयr);
	del_समयr_sync(&engine->execlists.preempt);
	tasklet_समाप्त(&engine->execlists.tasklet);
पूर्ण

अटल व्योम execlists_release(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->sanitize = शून्य; /* no दीर्घer in control, nothing to sanitize */

	execlists_shutकरोwn(engine);

	पूर्णांकel_engine_cleanup_common(engine);
	lrc_fini_wa_ctx(engine);
पूर्ण

अटल व्योम
logical_ring_शेष_vfuncs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/* Default vfuncs which can be overridden by each engine. */

	engine->resume = execlists_resume;

	engine->cops = &execlists_context_ops;
	engine->request_alloc = execlists_request_alloc;

	engine->emit_flush = gen8_emit_flush_xcs;
	engine->emit_init_bपढ़ोcrumb = gen8_emit_init_bपढ़ोcrumb;
	engine->emit_fini_bपढ़ोcrumb = gen8_emit_fini_bपढ़ोcrumb_xcs;
	अगर (INTEL_GEN(engine->i915) >= 12) अणु
		engine->emit_fini_bपढ़ोcrumb = gen12_emit_fini_bपढ़ोcrumb_xcs;
		engine->emit_flush = gen12_emit_flush_xcs;
	पूर्ण
	engine->set_शेष_submission = execlists_set_शेष_submission;

	अगर (INTEL_GEN(engine->i915) < 11) अणु
		engine->irq_enable = gen8_logical_ring_enable_irq;
		engine->irq_disable = gen8_logical_ring_disable_irq;
	पूर्ण अन्यथा अणु
		/*
		 * TODO: On Gen11 पूर्णांकerrupt masks need to be clear
		 * to allow C6 entry. Keep पूर्णांकerrupts enabled at
		 * and take the hit of generating extra पूर्णांकerrupts
		 * until a more refined solution exists.
		 */
	पूर्ण
पूर्ण

अटल व्योम logical_ring_शेष_irqs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अचिन्हित पूर्णांक shअगरt = 0;

	अगर (INTEL_GEN(engine->i915) < 11) अणु
		स्थिर u8 irq_shअगरts[] = अणु
			[RCS0]  = GEN8_RCS_IRQ_SHIFT,
			[BCS0]  = GEN8_BCS_IRQ_SHIFT,
			[VCS0]  = GEN8_VCS0_IRQ_SHIFT,
			[VCS1]  = GEN8_VCS1_IRQ_SHIFT,
			[VECS0] = GEN8_VECS_IRQ_SHIFT,
		पूर्ण;

		shअगरt = irq_shअगरts[engine->id];
	पूर्ण

	engine->irq_enable_mask = GT_RENDER_USER_INTERRUPT << shअगरt;
	engine->irq_keep_mask = GT_CONTEXT_SWITCH_INTERRUPT << shअगरt;
	engine->irq_keep_mask |= GT_CS_MASTER_ERROR_INTERRUPT << shअगरt;
	engine->irq_keep_mask |= GT_WAIT_SEMAPHORE_INTERRUPT << shअगरt;
पूर्ण

अटल व्योम rcs_submission_override(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	चयन (INTEL_GEN(engine->i915)) अणु
	हाल 12:
		engine->emit_flush = gen12_emit_flush_rcs;
		engine->emit_fini_bपढ़ोcrumb = gen12_emit_fini_bपढ़ोcrumb_rcs;
		अवरोध;
	हाल 11:
		engine->emit_flush = gen11_emit_flush_rcs;
		engine->emit_fini_bपढ़ोcrumb = gen11_emit_fini_bपढ़ोcrumb_rcs;
		अवरोध;
	शेष:
		engine->emit_flush = gen8_emit_flush_rcs;
		engine->emit_fini_bपढ़ोcrumb = gen8_emit_fini_bपढ़ोcrumb_rcs;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_execlists_submission_setup(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा drm_i915_निजी *i915 = engine->i915;
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	u32 base = engine->mmio_base;

	tasklet_setup(&engine->execlists.tasklet, execlists_submission_tasklet);
	समयr_setup(&engine->execlists.समयr, execlists_बारlice, 0);
	समयr_setup(&engine->execlists.preempt, execlists_preempt, 0);

	logical_ring_शेष_vfuncs(engine);
	logical_ring_शेष_irqs(engine);

	अगर (engine->class == RENDER_CLASS)
		rcs_submission_override(engine);

	lrc_init_wa_ctx(engine);

	अगर (HAS_LOGICAL_RING_ELSQ(i915)) अणु
		execlists->submit_reg = uncore->regs +
			i915_mmio_reg_offset(RING_EXECLIST_SQ_CONTENTS(base));
		execlists->ctrl_reg = uncore->regs +
			i915_mmio_reg_offset(RING_EXECLIST_CONTROL(base));
	पूर्ण अन्यथा अणु
		execlists->submit_reg = uncore->regs +
			i915_mmio_reg_offset(RING_ELSP(base));
	पूर्ण

	execlists->csb_status =
		(u64 *)&engine->status_page.addr[I915_HWS_CSB_BUF0_INDEX];

	execlists->csb_ग_लिखो =
		&engine->status_page.addr[पूर्णांकel_hws_csb_ग_लिखो_index(i915)];

	अगर (INTEL_GEN(i915) < 11)
		execlists->csb_size = GEN8_CSB_ENTRIES;
	अन्यथा
		execlists->csb_size = GEN11_CSB_ENTRIES;

	engine->context_tag = GENMASK(BITS_PER_LONG - 2, 0);
	अगर (INTEL_GEN(engine->i915) >= 11) अणु
		execlists->ccid |= engine->instance << (GEN11_ENGINE_INSTANCE_SHIFT - 32);
		execlists->ccid |= engine->class << (GEN11_ENGINE_CLASS_SHIFT - 32);
	पूर्ण

	/* Finally, take ownership and responsibility क्रम cleanup! */
	engine->sanitize = execlists_sanitize;
	engine->release = execlists_release;

	वापस 0;
पूर्ण

अटल काष्ठा list_head *भव_queue(काष्ठा भव_engine *ve)
अणु
	वापस &ve->base.execlists.शेष_priolist.requests;
पूर्ण

अटल व्योम rcu_भव_context_destroy(काष्ठा work_काष्ठा *wrk)
अणु
	काष्ठा भव_engine *ve =
		container_of(wrk, typeof(*ve), rcu.work);
	अचिन्हित पूर्णांक n;

	GEM_BUG_ON(ve->context.inflight);

	/* Preempt-to-busy may leave a stale request behind. */
	अगर (unlikely(ve->request)) अणु
		काष्ठा i915_request *old;

		spin_lock_irq(&ve->base.active.lock);

		old = fetch_and_zero(&ve->request);
		अगर (old) अणु
			GEM_BUG_ON(!__i915_request_is_complete(old));
			__i915_request_submit(old);
			i915_request_put(old);
		पूर्ण

		spin_unlock_irq(&ve->base.active.lock);
	पूर्ण

	/*
	 * Flush the tasklet in हाल it is still running on another core.
	 *
	 * This needs to be करोne beक्रमe we हटाओ ourselves from the siblings'
	 * rbtrees as in the हाल it is running in parallel, it may reinsert
	 * the rb_node पूर्णांकo a sibling.
	 */
	tasklet_समाप्त(&ve->base.execlists.tasklet);

	/* Decouple ourselves from the siblings, no more access allowed. */
	क्रम (n = 0; n < ve->num_siblings; n++) अणु
		काष्ठा पूर्णांकel_engine_cs *sibling = ve->siblings[n];
		काष्ठा rb_node *node = &ve->nodes[sibling->id].rb;

		अगर (RB_EMPTY_NODE(node))
			जारी;

		spin_lock_irq(&sibling->active.lock);

		/* Detachment is lazily perक्रमmed in the execlists tasklet */
		अगर (!RB_EMPTY_NODE(node))
			rb_erase_cached(node, &sibling->execlists.भव);

		spin_unlock_irq(&sibling->active.lock);
	पूर्ण
	GEM_BUG_ON(__tasklet_is_scheduled(&ve->base.execlists.tasklet));
	GEM_BUG_ON(!list_empty(भव_queue(ve)));

	lrc_fini(&ve->context);
	पूर्णांकel_context_fini(&ve->context);

	पूर्णांकel_bपढ़ोcrumbs_मुक्त(ve->base.bपढ़ोcrumbs);
	पूर्णांकel_engine_मुक्त_request_pool(&ve->base);

	kमुक्त(ve->bonds);
	kमुक्त(ve);
पूर्ण

अटल व्योम भव_context_destroy(काष्ठा kref *kref)
अणु
	काष्ठा भव_engine *ve =
		container_of(kref, typeof(*ve), context.ref);

	GEM_BUG_ON(!list_empty(&ve->context.संकेतs));

	/*
	 * When destroying the भव engine, we have to be aware that
	 * it may still be in use from an hardirq/softirq context causing
	 * the resubmission of a completed request (background completion
	 * due to preempt-to-busy). Beक्रमe we can मुक्त the engine, we need
	 * to flush the submission code and tasklets that are still potentially
	 * accessing the engine. Flushing the tasklets requires process context,
	 * and since we can guard the resubmit onto the engine with an RCU पढ़ो
	 * lock, we can delegate the मुक्त of the engine to an RCU worker.
	 */
	INIT_RCU_WORK(&ve->rcu, rcu_भव_context_destroy);
	queue_rcu_work(प्रणाली_wq, &ve->rcu);
पूर्ण

अटल व्योम भव_engine_initial_hपूर्णांक(काष्ठा भव_engine *ve)
अणु
	पूर्णांक swp;

	/*
	 * Pick a अक्रमom sibling on starting to help spपढ़ो the load around.
	 *
	 * New contexts are typically created with exactly the same order
	 * of siblings, and often started in batches. Due to the way we iterate
	 * the array of sibling when submitting requests, sibling[0] is
	 * prioritised क्रम dequeuing. If we make sure that sibling[0] is fairly
	 * अक्रमomised across the प्रणाली, we also help spपढ़ो the load by the
	 * first engine we inspect being dअगरferent each समय.
	 *
	 * NB This करोes not क्रमce us to execute on this engine, it will just
	 * typically be the first we inspect क्रम submission.
	 */
	swp = pअक्रमom_u32_max(ve->num_siblings);
	अगर (swp)
		swap(ve->siblings[swp], ve->siblings[0]);
पूर्ण

अटल पूर्णांक भव_context_alloc(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा भव_engine *ve = container_of(ce, typeof(*ve), context);

	वापस lrc_alloc(ce, ve->siblings[0]);
पूर्ण

अटल पूर्णांक भव_context_pre_pin(काष्ठा पूर्णांकel_context *ce,
				   काष्ठा i915_gem_ww_ctx *ww,
				   व्योम **vaddr)
अणु
	काष्ठा भव_engine *ve = container_of(ce, typeof(*ve), context);

	 /* Note: we must use a real engine class क्रम setting up reg state */
	वापस __execlists_context_pre_pin(ce, ve->siblings[0], ww, vaddr);
पूर्ण

अटल पूर्णांक भव_context_pin(काष्ठा पूर्णांकel_context *ce, व्योम *vaddr)
अणु
	काष्ठा भव_engine *ve = container_of(ce, typeof(*ve), context);

	वापस lrc_pin(ce, ve->siblings[0], vaddr);
पूर्ण

अटल व्योम भव_context_enter(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा भव_engine *ve = container_of(ce, typeof(*ve), context);
	अचिन्हित पूर्णांक n;

	क्रम (n = 0; n < ve->num_siblings; n++)
		पूर्णांकel_engine_pm_get(ve->siblings[n]);

	पूर्णांकel_समयline_enter(ce->समयline);
पूर्ण

अटल व्योम भव_context_निकास(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा भव_engine *ve = container_of(ce, typeof(*ve), context);
	अचिन्हित पूर्णांक n;

	पूर्णांकel_समयline_निकास(ce->समयline);

	क्रम (n = 0; n < ve->num_siblings; n++)
		पूर्णांकel_engine_pm_put(ve->siblings[n]);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_context_ops भव_context_ops = अणु
	.flags = COPS_HAS_INFLIGHT,

	.alloc = भव_context_alloc,

	.pre_pin = भव_context_pre_pin,
	.pin = भव_context_pin,
	.unpin = lrc_unpin,
	.post_unpin = lrc_post_unpin,

	.enter = भव_context_enter,
	.निकास = भव_context_निकास,

	.destroy = भव_context_destroy,
पूर्ण;

अटल पूर्णांकel_engine_mask_t भव_submission_mask(काष्ठा भव_engine *ve)
अणु
	काष्ठा i915_request *rq;
	पूर्णांकel_engine_mask_t mask;

	rq = READ_ONCE(ve->request);
	अगर (!rq)
		वापस 0;

	/* The rq is पढ़ोy क्रम submission; rq->execution_mask is now stable. */
	mask = rq->execution_mask;
	अगर (unlikely(!mask)) अणु
		/* Invalid selection, submit to a अक्रमom engine in error */
		i915_request_set_error_once(rq, -ENODEV);
		mask = ve->siblings[0]->mask;
	पूर्ण

	ENGINE_TRACE(&ve->base, "rq=%llx:%lld, mask=%x, prio=%d\n",
		     rq->fence.context, rq->fence.seqno,
		     mask, ve->base.execlists.queue_priority_hपूर्णांक);

	वापस mask;
पूर्ण

अटल व्योम भव_submission_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा भव_engine * स्थिर ve =
		from_tasklet(ve, t, base.execlists.tasklet);
	स्थिर पूर्णांक prio = READ_ONCE(ve->base.execlists.queue_priority_hपूर्णांक);
	पूर्णांकel_engine_mask_t mask;
	अचिन्हित पूर्णांक n;

	rcu_पढ़ो_lock();
	mask = भव_submission_mask(ve);
	rcu_पढ़ो_unlock();
	अगर (unlikely(!mask))
		वापस;

	क्रम (n = 0; n < ve->num_siblings; n++) अणु
		काष्ठा पूर्णांकel_engine_cs *sibling = READ_ONCE(ve->siblings[n]);
		काष्ठा ve_node * स्थिर node = &ve->nodes[sibling->id];
		काष्ठा rb_node **parent, *rb;
		bool first;

		अगर (!READ_ONCE(ve->request))
			अवरोध; /* alपढ़ोy handled by a sibling's tasklet */

		spin_lock_irq(&sibling->active.lock);

		अगर (unlikely(!(mask & sibling->mask))) अणु
			अगर (!RB_EMPTY_NODE(&node->rb)) अणु
				rb_erase_cached(&node->rb,
						&sibling->execlists.भव);
				RB_CLEAR_NODE(&node->rb);
			पूर्ण

			जाओ unlock_engine;
		पूर्ण

		अगर (unlikely(!RB_EMPTY_NODE(&node->rb))) अणु
			/*
			 * Cheat and aव्योम rebalancing the tree अगर we can
			 * reuse this node in situ.
			 */
			first = rb_first_cached(&sibling->execlists.भव) ==
				&node->rb;
			अगर (prio == node->prio || (prio > node->prio && first))
				जाओ submit_engine;

			rb_erase_cached(&node->rb, &sibling->execlists.भव);
		पूर्ण

		rb = शून्य;
		first = true;
		parent = &sibling->execlists.भव.rb_root.rb_node;
		जबतक (*parent) अणु
			काष्ठा ve_node *other;

			rb = *parent;
			other = rb_entry(rb, typeof(*other), rb);
			अगर (prio > other->prio) अणु
				parent = &rb->rb_left;
			पूर्ण अन्यथा अणु
				parent = &rb->rb_right;
				first = false;
			पूर्ण
		पूर्ण

		rb_link_node(&node->rb, rb, parent);
		rb_insert_color_cached(&node->rb,
				       &sibling->execlists.भव,
				       first);

submit_engine:
		GEM_BUG_ON(RB_EMPTY_NODE(&node->rb));
		node->prio = prio;
		अगर (first && prio > sibling->execlists.queue_priority_hपूर्णांक)
			tasklet_hi_schedule(&sibling->execlists.tasklet);

unlock_engine:
		spin_unlock_irq(&sibling->active.lock);

		अगर (पूर्णांकel_context_inflight(&ve->context))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम भव_submit_request(काष्ठा i915_request *rq)
अणु
	काष्ठा भव_engine *ve = to_भव_engine(rq->engine);
	अचिन्हित दीर्घ flags;

	ENGINE_TRACE(&ve->base, "rq=%llx:%lld\n",
		     rq->fence.context,
		     rq->fence.seqno);

	GEM_BUG_ON(ve->base.submit_request != भव_submit_request);

	spin_lock_irqsave(&ve->base.active.lock, flags);

	/* By the समय we resubmit a request, it may be completed */
	अगर (__i915_request_is_complete(rq)) अणु
		__i915_request_submit(rq);
		जाओ unlock;
	पूर्ण

	अगर (ve->request) अणु /* background completion from preempt-to-busy */
		GEM_BUG_ON(!__i915_request_is_complete(ve->request));
		__i915_request_submit(ve->request);
		i915_request_put(ve->request);
	पूर्ण

	ve->base.execlists.queue_priority_hपूर्णांक = rq_prio(rq);
	ve->request = i915_request_get(rq);

	GEM_BUG_ON(!list_empty(भव_queue(ve)));
	list_move_tail(&rq->sched.link, भव_queue(ve));

	tasklet_hi_schedule(&ve->base.execlists.tasklet);

unlock:
	spin_unlock_irqrestore(&ve->base.active.lock, flags);
पूर्ण

अटल काष्ठा ve_bond *
भव_find_bond(काष्ठा भव_engine *ve,
		  स्थिर काष्ठा पूर्णांकel_engine_cs *master)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ve->num_bonds; i++) अणु
		अगर (ve->bonds[i].master == master)
			वापस &ve->bonds[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
भव_bond_execute(काष्ठा i915_request *rq, काष्ठा dma_fence *संकेत)
अणु
	काष्ठा भव_engine *ve = to_भव_engine(rq->engine);
	पूर्णांकel_engine_mask_t allowed, exec;
	काष्ठा ve_bond *bond;

	allowed = ~to_request(संकेत)->engine->mask;

	bond = भव_find_bond(ve, to_request(संकेत)->engine);
	अगर (bond)
		allowed &= bond->sibling_mask;

	/* Restrict the bonded request to run on only the available engines */
	exec = READ_ONCE(rq->execution_mask);
	जबतक (!try_cmpxchg(&rq->execution_mask, &exec, exec & allowed))
		;

	/* Prevent the master from being re-run on the bonded engines */
	to_request(संकेत)->execution_mask &= ~allowed;
पूर्ण

काष्ठा पूर्णांकel_context *
पूर्णांकel_execlists_create_भव(काष्ठा पूर्णांकel_engine_cs **siblings,
			       अचिन्हित पूर्णांक count)
अणु
	काष्ठा भव_engine *ve;
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	अगर (count == 0)
		वापस ERR_PTR(-EINVAL);

	अगर (count == 1)
		वापस पूर्णांकel_context_create(siblings[0]);

	ve = kzalloc(काष्ठा_size(ve, siblings, count), GFP_KERNEL);
	अगर (!ve)
		वापस ERR_PTR(-ENOMEM);

	ve->base.i915 = siblings[0]->i915;
	ve->base.gt = siblings[0]->gt;
	ve->base.uncore = siblings[0]->uncore;
	ve->base.id = -1;

	ve->base.class = OTHER_CLASS;
	ve->base.uabi_class = I915_ENGINE_CLASS_INVALID;
	ve->base.instance = I915_ENGINE_CLASS_INVALID_VIRTUAL;
	ve->base.uabi_instance = I915_ENGINE_CLASS_INVALID_VIRTUAL;

	/*
	 * The decision on whether to submit a request using semaphores
	 * depends on the saturated state of the engine. We only compute
	 * this during HW submission of the request, and we need क्रम this
	 * state to be globally applied to all requests being submitted
	 * to this engine. Virtual engines encompass more than one physical
	 * engine and so we cannot accurately tell in advance अगर one of those
	 * engines is alपढ़ोy saturated and so cannot afक्रमd to use a semaphore
	 * and be pessimized in priority क्रम करोing so -- अगर we are the only
	 * context using semaphores after all other clients have stopped, we
	 * will be starved on the saturated प्रणाली. Such a global चयन क्रम
	 * semaphores is less than ideal, but alas is the current compromise.
	 */
	ve->base.saturated = ALL_ENGINES;

	snम_लिखो(ve->base.name, माप(ve->base.name), "virtual");

	पूर्णांकel_engine_init_active(&ve->base, ENGINE_VIRTUAL);
	पूर्णांकel_engine_init_execlists(&ve->base);

	ve->base.cops = &भव_context_ops;
	ve->base.request_alloc = execlists_request_alloc;

	ve->base.schedule = i915_schedule;
	ve->base.submit_request = भव_submit_request;
	ve->base.bond_execute = भव_bond_execute;

	INIT_LIST_HEAD(भव_queue(ve));
	ve->base.execlists.queue_priority_hपूर्णांक = पूर्णांक_न्यून;
	tasklet_setup(&ve->base.execlists.tasklet, भव_submission_tasklet);

	पूर्णांकel_context_init(&ve->context, &ve->base);

	ve->base.bपढ़ोcrumbs = पूर्णांकel_bपढ़ोcrumbs_create(शून्य);
	अगर (!ve->base.bपढ़ोcrumbs) अणु
		err = -ENOMEM;
		जाओ err_put;
	पूर्ण

	क्रम (n = 0; n < count; n++) अणु
		काष्ठा पूर्णांकel_engine_cs *sibling = siblings[n];

		GEM_BUG_ON(!is_घातer_of_2(sibling->mask));
		अगर (sibling->mask & ve->base.mask) अणु
			DRM_DEBUG("duplicate %s entry in load balancer\n",
				  sibling->name);
			err = -EINVAL;
			जाओ err_put;
		पूर्ण

		/*
		 * The भव engine implementation is tightly coupled to
		 * the execlists backend -- we push out request directly
		 * पूर्णांकo a tree inside each physical engine. We could support
		 * layering अगर we handle cloning of the requests and
		 * submitting a copy पूर्णांकo each backend.
		 */
		अगर (sibling->execlists.tasklet.callback !=
		    execlists_submission_tasklet) अणु
			err = -ENODEV;
			जाओ err_put;
		पूर्ण

		GEM_BUG_ON(RB_EMPTY_NODE(&ve->nodes[sibling->id].rb));
		RB_CLEAR_NODE(&ve->nodes[sibling->id].rb);

		ve->siblings[ve->num_siblings++] = sibling;
		ve->base.mask |= sibling->mask;

		/*
		 * All physical engines must be compatible क्रम their emission
		 * functions (as we build the inकाष्ठाions during request
		 * स्थिरruction and करो not alter them beक्रमe submission
		 * on the physical engine). We use the engine class as a guide
		 * here, although that could be refined.
		 */
		अगर (ve->base.class != OTHER_CLASS) अणु
			अगर (ve->base.class != sibling->class) अणु
				DRM_DEBUG("invalid mixing of engine class, sibling %d, already %d\n",
					  sibling->class, ve->base.class);
				err = -EINVAL;
				जाओ err_put;
			पूर्ण
			जारी;
		पूर्ण

		ve->base.class = sibling->class;
		ve->base.uabi_class = sibling->uabi_class;
		snम_लिखो(ve->base.name, माप(ve->base.name),
			 "v%dx%d", ve->base.class, count);
		ve->base.context_size = sibling->context_size;

		ve->base.emit_bb_start = sibling->emit_bb_start;
		ve->base.emit_flush = sibling->emit_flush;
		ve->base.emit_init_bपढ़ोcrumb = sibling->emit_init_bपढ़ोcrumb;
		ve->base.emit_fini_bपढ़ोcrumb = sibling->emit_fini_bपढ़ोcrumb;
		ve->base.emit_fini_bपढ़ोcrumb_dw =
			sibling->emit_fini_bपढ़ोcrumb_dw;

		ve->base.flags = sibling->flags;
	पूर्ण

	ve->base.flags |= I915_ENGINE_IS_VIRTUAL;

	भव_engine_initial_hपूर्णांक(ve);
	वापस &ve->context;

err_put:
	पूर्णांकel_context_put(&ve->context);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा पूर्णांकel_context *
पूर्णांकel_execlists_clone_भव(काष्ठा पूर्णांकel_engine_cs *src)
अणु
	काष्ठा भव_engine *se = to_भव_engine(src);
	काष्ठा पूर्णांकel_context *dst;

	dst = पूर्णांकel_execlists_create_भव(se->siblings,
					     se->num_siblings);
	अगर (IS_ERR(dst))
		वापस dst;

	अगर (se->num_bonds) अणु
		काष्ठा भव_engine *de = to_भव_engine(dst->engine);

		de->bonds = kmemdup(se->bonds,
				    माप(*se->bonds) * se->num_bonds,
				    GFP_KERNEL);
		अगर (!de->bonds) अणु
			पूर्णांकel_context_put(dst);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		de->num_bonds = se->num_bonds;
	पूर्ण

	वापस dst;
पूर्ण

पूर्णांक पूर्णांकel_भव_engine_attach_bond(काष्ठा पूर्णांकel_engine_cs *engine,
				     स्थिर काष्ठा पूर्णांकel_engine_cs *master,
				     स्थिर काष्ठा पूर्णांकel_engine_cs *sibling)
अणु
	काष्ठा भव_engine *ve = to_भव_engine(engine);
	काष्ठा ve_bond *bond;
	पूर्णांक n;

	/* Sanity check the sibling is part of the भव engine */
	क्रम (n = 0; n < ve->num_siblings; n++)
		अगर (sibling == ve->siblings[n])
			अवरोध;
	अगर (n == ve->num_siblings)
		वापस -EINVAL;

	bond = भव_find_bond(ve, master);
	अगर (bond) अणु
		bond->sibling_mask |= sibling->mask;
		वापस 0;
	पूर्ण

	bond = kपुनः_स्मृति(ve->bonds,
			माप(*bond) * (ve->num_bonds + 1),
			GFP_KERNEL);
	अगर (!bond)
		वापस -ENOMEM;

	bond[ve->num_bonds].master = master;
	bond[ve->num_bonds].sibling_mask = sibling->mask;

	ve->bonds = bond;
	ve->num_bonds++;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_execlists_show_requests(काष्ठा पूर्णांकel_engine_cs *engine,
				   काष्ठा drm_prपूर्णांकer *m,
				   व्योम (*show_request)(काष्ठा drm_prपूर्णांकer *m,
							स्थिर काष्ठा i915_request *rq,
							स्थिर अक्षर *prefix,
							पूर्णांक indent),
				   अचिन्हित पूर्णांक max)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_execlists *execlists = &engine->execlists;
	काष्ठा i915_request *rq, *last;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count;
	काष्ठा rb_node *rb;

	spin_lock_irqsave(&engine->active.lock, flags);

	last = शून्य;
	count = 0;
	list_क्रम_each_entry(rq, &engine->active.requests, sched.link) अणु
		अगर (count++ < max - 1)
			show_request(m, rq, "\t\t", 0);
		अन्यथा
			last = rq;
	पूर्ण
	अगर (last) अणु
		अगर (count > max) अणु
			drm_म_लिखो(m,
				   "\t\t...skipping %d executing requests...\n",
				   count - max);
		पूर्ण
		show_request(m, last, "\t\t", 0);
	पूर्ण

	अगर (execlists->queue_priority_hपूर्णांक != पूर्णांक_न्यून)
		drm_म_लिखो(m, "\t\tQueue priority hint: %d\n",
			   READ_ONCE(execlists->queue_priority_hपूर्णांक));

	last = शून्य;
	count = 0;
	क्रम (rb = rb_first_cached(&execlists->queue); rb; rb = rb_next(rb)) अणु
		काष्ठा i915_priolist *p = rb_entry(rb, typeof(*p), node);

		priolist_क्रम_each_request(rq, p) अणु
			अगर (count++ < max - 1)
				show_request(m, rq, "\t\t", 0);
			अन्यथा
				last = rq;
		पूर्ण
	पूर्ण
	अगर (last) अणु
		अगर (count > max) अणु
			drm_म_लिखो(m,
				   "\t\t...skipping %d queued requests...\n",
				   count - max);
		पूर्ण
		show_request(m, last, "\t\t", 0);
	पूर्ण

	last = शून्य;
	count = 0;
	क्रम (rb = rb_first_cached(&execlists->भव); rb; rb = rb_next(rb)) अणु
		काष्ठा भव_engine *ve =
			rb_entry(rb, typeof(*ve), nodes[engine->id].rb);
		काष्ठा i915_request *rq = READ_ONCE(ve->request);

		अगर (rq) अणु
			अगर (count++ < max - 1)
				show_request(m, rq, "\t\t", 0);
			अन्यथा
				last = rq;
		पूर्ण
	पूर्ण
	अगर (last) अणु
		अगर (count > max) अणु
			drm_म_लिखो(m,
				   "\t\t...skipping %d virtual requests...\n",
				   count - max);
		पूर्ण
		show_request(m, last, "\t\t", 0);
	पूर्ण

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

bool
पूर्णांकel_engine_in_execlists_submission_mode(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->set_शेष_submission ==
	       execlists_set_शेष_submission;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_execlists.c"
#पूर्ण_अगर
