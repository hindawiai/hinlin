<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#समावेश <linux/circ_buf.h>

#समावेश "gem/i915_gem_context.h"
#समावेश "gt/gen8_engine_cs.h"
#समावेश "gt/intel_breadcrumbs.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_lrc.h"
#समावेश "gt/intel_mocs.h"
#समावेश "gt/intel_ring.h"

#समावेश "intel_guc_submission.h"

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"

/**
 * DOC: GuC-based command submission
 *
 * IMPORTANT NOTE: GuC submission is currently not supported in i915. The GuC
 * firmware is moving to an updated submission पूर्णांकerface and we plan to
 * turn submission back on when that lands. The below करोcumentation (and related
 * code) matches the old submission model and will be updated as part of the
 * upgrade to the new flow.
 *
 * GuC stage descriptor:
 * During initialization, the driver allocates a अटल pool of 1024 such
 * descriptors, and shares them with the GuC. Currently, we only use one
 * descriptor. This stage descriptor lets the GuC know about the workqueue and
 * process descriptor. Theoretically, it also lets the GuC know about our HW
 * contexts (context ID, etc...), but we actually employ a kind of submission
 * where the GuC uses the LRCA sent via the work item instead. This is called
 * a "proxy" submission.
 *
 * The Scratch रेजिस्टरs:
 * There are 16 MMIO-based रेजिस्टरs start from 0xC180. The kernel driver ग_लिखोs
 * a value to the action रेजिस्टर (SOFT_SCRATCH_0) aदीर्घ with any data. It then
 * triggers an पूर्णांकerrupt on the GuC via another रेजिस्टर ग_लिखो (0xC4C8).
 * Firmware ग_लिखोs a success/fail code back to the action रेजिस्टर after
 * processes the request. The kernel driver polls रुकोing क्रम this update and
 * then proceeds.
 *
 * Work Items:
 * There are several types of work items that the host may place पूर्णांकo a
 * workqueue, each with its own requirements and limitations. Currently only
 * WQ_TYPE_INORDER is needed to support legacy submission via GuC, which
 * represents in-order queue. The kernel driver packs ring tail poपूर्णांकer and an
 * ELSP context descriptor dword पूर्णांकo Work Item.
 * See guc_add_request()
 *
 */

#घोषणा GUC_REQUEST_SIZE 64 /* bytes */

अटल अंतरभूत काष्ठा i915_priolist *to_priolist(काष्ठा rb_node *rb)
अणु
	वापस rb_entry(rb, काष्ठा i915_priolist, node);
पूर्ण

अटल काष्ठा guc_stage_desc *__get_stage_desc(काष्ठा पूर्णांकel_guc *guc, u32 id)
अणु
	काष्ठा guc_stage_desc *base = guc->stage_desc_pool_vaddr;

	वापस &base[id];
पूर्ण

अटल पूर्णांक guc_stage_desc_pool_create(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 size = PAGE_ALIGN(माप(काष्ठा guc_stage_desc) *
			      GUC_MAX_STAGE_DESCRIPTORS);

	वापस पूर्णांकel_guc_allocate_and_map_vma(guc, size, &guc->stage_desc_pool,
					      &guc->stage_desc_pool_vaddr);
पूर्ण

अटल व्योम guc_stage_desc_pool_destroy(काष्ठा पूर्णांकel_guc *guc)
अणु
	i915_vma_unpin_and_release(&guc->stage_desc_pool, I915_VMA_RELEASE_MAP);
पूर्ण

/*
 * Initialise/clear the stage descriptor shared with the GuC firmware.
 *
 * This descriptor tells the GuC where (in GGTT space) to find the important
 * data काष्ठाures related to work submission (process descriptor, ग_लिखो queue,
 * etc).
 */
अटल व्योम guc_stage_desc_init(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा guc_stage_desc *desc;

	/* we only use 1 stage desc, so hardcode it to 0 */
	desc = __get_stage_desc(guc, 0);
	स_रखो(desc, 0, माप(*desc));

	desc->attribute = GUC_STAGE_DESC_ATTR_ACTIVE |
			  GUC_STAGE_DESC_ATTR_KERNEL;

	desc->stage_id = 0;
	desc->priority = GUC_CLIENT_PRIORITY_KMD_NORMAL;

	desc->wq_size = GUC_WQ_SIZE;
पूर्ण

अटल व्योम guc_stage_desc_fini(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा guc_stage_desc *desc;

	desc = __get_stage_desc(guc, 0);
	स_रखो(desc, 0, माप(*desc));
पूर्ण

अटल व्योम guc_add_request(काष्ठा पूर्णांकel_guc *guc, काष्ठा i915_request *rq)
अणु
	/* Leaving stub as this function will be used in future patches */
पूर्ण

/*
 * When we're करोing submissions using regular execlists backend, writing to
 * ELSP from CPU side is enough to make sure that ग_लिखोs to ringbuffer pages
 * pinned in mappable aperture portion of GGTT are visible to command streamer.
 * Writes करोne by GuC on our behalf are not guaranteeing such ordering,
 * thereक्रमe, to ensure the flush, we're issuing a POSTING READ.
 */
अटल व्योम flush_ggtt_ग_लिखोs(काष्ठा i915_vma *vma)
अणु
	अगर (i915_vma_is_map_and_fenceable(vma))
		पूर्णांकel_uncore_posting_पढ़ो_fw(vma->vm->gt->uncore,
					     GUC_STATUS);
पूर्ण

अटल व्योम guc_submit(काष्ठा पूर्णांकel_engine_cs *engine,
		       काष्ठा i915_request **out,
		       काष्ठा i915_request **end)
अणु
	काष्ठा पूर्णांकel_guc *guc = &engine->gt->uc.guc;

	करो अणु
		काष्ठा i915_request *rq = *out++;

		flush_ggtt_ग_लिखोs(rq->ring->vma);
		guc_add_request(guc, rq);
	पूर्ण जबतक (out != end);
पूर्ण

अटल अंतरभूत पूर्णांक rq_prio(स्थिर काष्ठा i915_request *rq)
अणु
	वापस rq->sched.attr.priority;
पूर्ण

अटल काष्ठा i915_request *schedule_in(काष्ठा i915_request *rq, पूर्णांक idx)
अणु
	trace_i915_request_in(rq, idx);

	/*
	 * Currently we are not tracking the rq->context being inflight
	 * (ce->inflight = rq->engine). It is only used by the execlists
	 * backend at the moment, a similar counting strategy would be
	 * required अगर we generalise the inflight tracking.
	 */

	__पूर्णांकel_gt_pm_get(rq->engine->gt);
	वापस i915_request_get(rq);
पूर्ण

अटल व्योम schedule_out(काष्ठा i915_request *rq)
अणु
	trace_i915_request_out(rq);

	पूर्णांकel_gt_pm_put_async(rq->engine->gt);
	i915_request_put(rq);
पूर्ण

अटल व्योम __guc_dequeue(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा i915_request **first = execlists->inflight;
	काष्ठा i915_request ** स्थिर last_port = first + execlists->port_mask;
	काष्ठा i915_request *last = first[0];
	काष्ठा i915_request **port;
	bool submit = false;
	काष्ठा rb_node *rb;

	lockdep_निश्चित_held(&engine->active.lock);

	अगर (last) अणु
		अगर (*++first)
			वापस;

		last = शून्य;
	पूर्ण

	/*
	 * We ग_लिखो directly पूर्णांकo the execlists->inflight queue and करोn't use
	 * the execlists->pending queue, as we करोn't have a distinct चयन
	 * event.
	 */
	port = first;
	जबतक ((rb = rb_first_cached(&execlists->queue))) अणु
		काष्ठा i915_priolist *p = to_priolist(rb);
		काष्ठा i915_request *rq, *rn;

		priolist_क्रम_each_request_consume(rq, rn, p) अणु
			अगर (last && rq->context != last->context) अणु
				अगर (port == last_port)
					जाओ करोne;

				*port = schedule_in(last,
						    port - execlists->inflight);
				port++;
			पूर्ण

			list_del_init(&rq->sched.link);
			__i915_request_submit(rq);
			submit = true;
			last = rq;
		पूर्ण

		rb_erase_cached(&p->node, &execlists->queue);
		i915_priolist_मुक्त(p);
	पूर्ण
करोne:
	execlists->queue_priority_hपूर्णांक =
		rb ? to_priolist(rb)->priority : पूर्णांक_न्यून;
	अगर (submit) अणु
		*port = schedule_in(last, port - execlists->inflight);
		*++port = शून्य;
		guc_submit(engine, first, port);
	पूर्ण
	execlists->active = execlists->inflight;
पूर्ण

अटल व्योम guc_submission_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा पूर्णांकel_engine_cs * स्थिर engine =
		from_tasklet(engine, t, execlists.tasklet);
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा i915_request **port, *rq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&engine->active.lock, flags);

	क्रम (port = execlists->inflight; (rq = *port); port++) अणु
		अगर (!i915_request_completed(rq))
			अवरोध;

		schedule_out(rq);
	पूर्ण
	अगर (port != execlists->inflight) अणु
		पूर्णांक idx = port - execlists->inflight;
		पूर्णांक rem = ARRAY_SIZE(execlists->inflight) - idx;
		स_हटाओ(execlists->inflight, port, rem * माप(*port));
	पूर्ण

	__guc_dequeue(engine);

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम guc_reset_prepare(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;

	ENGINE_TRACE(engine, "\n");

	/*
	 * Prevent request submission to the hardware until we have
	 * completed the reset in i915_gem_reset_finish(). If a request
	 * is completed by one engine, it may then queue a request
	 * to a second via its execlists->tasklet *just* as we are
	 * calling engine->init_hw() and also writing the ELSP.
	 * Turning off the execlists->tasklet until the reset is over
	 * prevents the race.
	 */
	__tasklet_disable_sync_once(&execlists->tasklet);
पूर्ण

अटल व्योम guc_reset_state(काष्ठा पूर्णांकel_context *ce,
			    काष्ठा पूर्णांकel_engine_cs *engine,
			    u32 head,
			    bool scrub)
अणु
	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(ce));

	/*
	 * We want a simple context + ring to execute the bपढ़ोcrumb update.
	 * We cannot rely on the context being पूर्णांकact across the GPU hang,
	 * so clear it and rebuild just what we need क्रम the bपढ़ोcrumb.
	 * All pending requests क्रम this context will be zapped, and any
	 * future request will be after userspace has had the opportunity
	 * to recreate its own state.
	 */
	अगर (scrub)
		lrc_init_regs(ce, engine, true);

	/* Rerun the request; its payload has been neutered (अगर guilty). */
	lrc_update_regs(ce, engine, head);
पूर्ण

अटल व्योम guc_reset_शुरुआत(काष्ठा पूर्णांकel_engine_cs *engine, bool stalled)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा i915_request *rq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&engine->active.lock, flags);

	/* Push back any incomplete requests क्रम replay after the reset. */
	rq = execlists_unwind_incomplete_requests(execlists);
	अगर (!rq)
		जाओ out_unlock;

	अगर (!i915_request_started(rq))
		stalled = false;

	__i915_request_reset(rq, stalled);
	guc_reset_state(rq->context, engine, rq->head, stalled);

out_unlock:
	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम guc_reset_cancel(काष्ठा पूर्णांकel_engine_cs *engine)
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
	spin_lock_irqsave(&engine->active.lock, flags);

	/* Mark all executing requests as skipped. */
	list_क्रम_each_entry(rq, &engine->active.requests, sched.link) अणु
		i915_request_set_error_once(rq, -EIO);
		i915_request_mark_complete(rq);
	पूर्ण

	/* Flush the queued requests to the समयline list (क्रम retiring). */
	जबतक ((rb = rb_first_cached(&execlists->queue))) अणु
		काष्ठा i915_priolist *p = to_priolist(rb);

		priolist_क्रम_each_request_consume(rq, rn, p) अणु
			list_del_init(&rq->sched.link);
			__i915_request_submit(rq);
			dma_fence_set_error(&rq->fence, -EIO);
			i915_request_mark_complete(rq);
		पूर्ण

		rb_erase_cached(&p->node, &execlists->queue);
		i915_priolist_मुक्त(p);
	पूर्ण

	/* Reमुख्यing _unपढ़ोy_ requests will be nop'ed when submitted */

	execlists->queue_priority_hपूर्णांक = पूर्णांक_न्यून;
	execlists->queue = RB_ROOT_CACHED;

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम guc_reset_finish(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;

	अगर (__tasklet_enable(&execlists->tasklet))
		/* And kick in हाल we missed a new request submission. */
		tasklet_hi_schedule(&execlists->tasklet);

	ENGINE_TRACE(engine, "depth->%d\n",
		     atomic_पढ़ो(&execlists->tasklet.count));
पूर्ण

/*
 * Set up the memory resources to be shared with the GuC (via the GGTT)
 * at firmware loading समय.
 */
पूर्णांक पूर्णांकel_guc_submission_init(काष्ठा पूर्णांकel_guc *guc)
अणु
	पूर्णांक ret;

	अगर (guc->stage_desc_pool)
		वापस 0;

	ret = guc_stage_desc_pool_create(guc);
	अगर (ret)
		वापस ret;
	/*
	 * Keep अटल analysers happy, let them know that we allocated the
	 * vma after testing that it didn't exist earlier.
	 */
	GEM_BUG_ON(!guc->stage_desc_pool);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_guc_submission_fini(काष्ठा पूर्णांकel_guc *guc)
अणु
	अगर (guc->stage_desc_pool) अणु
		guc_stage_desc_pool_destroy(guc);
	पूर्ण
पूर्ण

अटल व्योम guc_पूर्णांकerrupts_capture(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 irqs = GT_CONTEXT_SWITCH_INTERRUPT;
	u32 dmask = irqs << 16 | irqs;

	GEM_BUG_ON(INTEL_GEN(gt->i915) < 11);

	/* Don't handle the ctx चयन पूर्णांकerrupt in GuC submission mode */
	पूर्णांकel_uncore_rmw(uncore, GEN11_RENDER_COPY_INTR_ENABLE, dmask, 0);
	पूर्णांकel_uncore_rmw(uncore, GEN11_VCS_VECS_INTR_ENABLE, dmask, 0);
पूर्ण

अटल व्योम guc_पूर्णांकerrupts_release(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 irqs = GT_CONTEXT_SWITCH_INTERRUPT;
	u32 dmask = irqs << 16 | irqs;

	GEM_BUG_ON(INTEL_GEN(gt->i915) < 11);

	/* Handle ctx चयन पूर्णांकerrupts again */
	पूर्णांकel_uncore_rmw(uncore, GEN11_RENDER_COPY_INTR_ENABLE, 0, dmask);
	पूर्णांकel_uncore_rmw(uncore, GEN11_VCS_VECS_INTR_ENABLE, 0, dmask);
पूर्ण

अटल पूर्णांक guc_context_alloc(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस lrc_alloc(ce, ce->engine);
पूर्ण

अटल पूर्णांक guc_context_pre_pin(काष्ठा पूर्णांकel_context *ce,
			       काष्ठा i915_gem_ww_ctx *ww,
			       व्योम **vaddr)
अणु
	वापस lrc_pre_pin(ce, ce->engine, ww, vaddr);
पूर्ण

अटल पूर्णांक guc_context_pin(काष्ठा पूर्णांकel_context *ce, व्योम *vaddr)
अणु
	वापस lrc_pin(ce, ce->engine, vaddr);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_context_ops guc_context_ops = अणु
	.alloc = guc_context_alloc,

	.pre_pin = guc_context_pre_pin,
	.pin = guc_context_pin,
	.unpin = lrc_unpin,
	.post_unpin = lrc_post_unpin,

	.enter = पूर्णांकel_context_enter_engine,
	.निकास = पूर्णांकel_context_निकास_engine,

	.reset = lrc_reset,
	.destroy = lrc_destroy,
पूर्ण;

अटल पूर्णांक guc_request_alloc(काष्ठा i915_request *request)
अणु
	पूर्णांक ret;

	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(request->context));

	/*
	 * Flush enough space to reduce the likelihood of रुकोing after
	 * we start building the request - in which हाल we will just
	 * have to repeat work.
	 */
	request->reserved_space += GUC_REQUEST_SIZE;

	/*
	 * Note that after this poपूर्णांक, we have committed to using
	 * this request as it is being used to both track the
	 * state of engine initialisation and liveness of the
	 * golden renderstate above. Think twice beक्रमe you try
	 * to cancel/unwind this request now.
	 */

	/* Unconditionally invalidate GPU caches and TLBs. */
	ret = request->engine->emit_flush(request, EMIT_INVALIDATE);
	अगर (ret)
		वापस ret;

	request->reserved_space -= GUC_REQUEST_SIZE;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम queue_request(काष्ठा पूर्णांकel_engine_cs *engine,
				 काष्ठा i915_request *rq,
				 पूर्णांक prio)
अणु
	GEM_BUG_ON(!list_empty(&rq->sched.link));
	list_add_tail(&rq->sched.link,
		      i915_sched_lookup_priolist(engine, prio));
	set_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);
पूर्ण

अटल व्योम guc_submit_request(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	अचिन्हित दीर्घ flags;

	/* Will be called from irq-context when using क्रमeign fences. */
	spin_lock_irqsave(&engine->active.lock, flags);

	queue_request(engine, rq, rq_prio(rq));

	GEM_BUG_ON(RB_EMPTY_ROOT(&engine->execlists.queue.rb_root));
	GEM_BUG_ON(list_empty(&rq->sched.link));

	tasklet_hi_schedule(&engine->execlists.tasklet);

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम sanitize_hwsp(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_समयline *tl;

	list_क्रम_each_entry(tl, &engine->status_page.समयlines, engine_link)
		पूर्णांकel_समयline_reset_seqno(tl);
पूर्ण

अटल व्योम guc_sanitize(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
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

	/*
	 * The kernel_context HWSP is stored in the status_page. As above,
	 * that may be lost on resume/initialisation, and so we need to
	 * reset the value in the HWSP.
	 */
	sanitize_hwsp(engine);

	/* And scrub the dirty cachelines क्रम the HWSP */
	clflush_cache_range(engine->status_page.addr, PAGE_SIZE);
पूर्ण

अटल व्योम setup_hwsp(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_engine_set_hwsp_ग_लिखोmask(engine, ~0u); /* HWSTAM */

	ENGINE_WRITE_FW(engine,
			RING_HWS_PGA,
			i915_ggtt_offset(engine->status_page.vma));
पूर्ण

अटल व्योम start_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_WRITE_FW(engine,
			RING_MODE_GEN7,
			_MASKED_BIT_ENABLE(GEN11_GFX_DISABLE_LEGACY_MODE));

	ENGINE_WRITE_FW(engine, RING_MI_MODE, _MASKED_BIT_DISABLE(STOP_RING));
	ENGINE_POSTING_READ(engine, RING_MI_MODE);
पूर्ण

अटल पूर्णांक guc_resume(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	निश्चित_क्रमcewakes_active(engine->uncore, FORCEWAKE_ALL);

	पूर्णांकel_mocs_init_engine(engine);

	पूर्णांकel_bपढ़ोcrumbs_reset(engine->bपढ़ोcrumbs);

	setup_hwsp(engine);
	start_engine(engine);

	वापस 0;
पूर्ण

अटल व्योम guc_set_शेष_submission(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->submit_request = guc_submit_request;
	engine->schedule = i915_schedule;
	engine->execlists.tasklet.callback = guc_submission_tasklet;

	engine->reset.prepare = guc_reset_prepare;
	engine->reset.शुरुआत = guc_reset_शुरुआत;
	engine->reset.cancel = guc_reset_cancel;
	engine->reset.finish = guc_reset_finish;

	engine->flags |= I915_ENGINE_NEEDS_BREADCRUMB_TASKLET;
	engine->flags |= I915_ENGINE_HAS_PREEMPTION;

	/*
	 * TODO: GuC supports बारlicing and semaphores as well, but they're
	 * handled by the firmware so some minor tweaks are required beक्रमe
	 * enabling.
	 *
	 * engine->flags |= I915_ENGINE_HAS_TIMESLICES;
	 * engine->flags |= I915_ENGINE_HAS_SEMAPHORES;
	 */

	engine->emit_bb_start = gen8_emit_bb_start;

	/*
	 * For the bपढ़ोcrumb irq to work we need the पूर्णांकerrupts to stay
	 * enabled. However, on all platक्रमms on which we'll have support क्रम
	 * GuC submission we करोn't allow disabling the पूर्णांकerrupts at runसमय, so
	 * we're always safe with the current flow.
	 */
	GEM_BUG_ON(engine->irq_enable || engine->irq_disable);
पूर्ण

अटल व्योम guc_release(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->sanitize = शून्य; /* no दीर्घer in control, nothing to sanitize */

	tasklet_समाप्त(&engine->execlists.tasklet);

	पूर्णांकel_engine_cleanup_common(engine);
	lrc_fini_wa_ctx(engine);
पूर्ण

अटल व्योम guc_शेष_vfuncs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/* Default vfuncs which can be overridden by each engine. */

	engine->resume = guc_resume;

	engine->cops = &guc_context_ops;
	engine->request_alloc = guc_request_alloc;

	engine->emit_flush = gen8_emit_flush_xcs;
	engine->emit_init_bपढ़ोcrumb = gen8_emit_init_bपढ़ोcrumb;
	engine->emit_fini_bपढ़ोcrumb = gen8_emit_fini_bपढ़ोcrumb_xcs;
	अगर (INTEL_GEN(engine->i915) >= 12) अणु
		engine->emit_fini_bपढ़ोcrumb = gen12_emit_fini_bपढ़ोcrumb_xcs;
		engine->emit_flush = gen12_emit_flush_xcs;
	पूर्ण
	engine->set_शेष_submission = guc_set_शेष_submission;
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

अटल अंतरभूत व्योम guc_शेष_irqs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->irq_keep_mask = GT_RENDER_USER_INTERRUPT;
पूर्ण

पूर्णांक पूर्णांकel_guc_submission_setup(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	/*
	 * The setup relies on several assumptions (e.g. irqs always enabled)
	 * that are only valid on gen11+
	 */
	GEM_BUG_ON(INTEL_GEN(i915) < 11);

	tasklet_setup(&engine->execlists.tasklet, guc_submission_tasklet);

	guc_शेष_vfuncs(engine);
	guc_शेष_irqs(engine);

	अगर (engine->class == RENDER_CLASS)
		rcs_submission_override(engine);

	lrc_init_wa_ctx(engine);

	/* Finally, take ownership and responsibility क्रम cleanup! */
	engine->sanitize = guc_sanitize;
	engine->release = guc_release;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_guc_submission_enable(काष्ठा पूर्णांकel_guc *guc)
अणु
	guc_stage_desc_init(guc);

	/* Take over from manual control of ELSP (execlists) */
	guc_पूर्णांकerrupts_capture(guc_to_gt(guc));
पूर्ण

व्योम पूर्णांकel_guc_submission_disable(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	GEM_BUG_ON(gt->awake); /* GT should be parked first */

	/* Note: By the समय we're here, GuC may have alपढ़ोy been reset */

	guc_पूर्णांकerrupts_release(gt);

	guc_stage_desc_fini(guc);
पूर्ण

अटल bool __guc_submission_selected(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा drm_i915_निजी *i915 = guc_to_gt(guc)->i915;

	अगर (!पूर्णांकel_guc_submission_is_supported(guc))
		वापस false;

	वापस i915->params.enable_guc & ENABLE_GUC_SUBMISSION;
पूर्ण

व्योम पूर्णांकel_guc_submission_init_early(काष्ठा पूर्णांकel_guc *guc)
अणु
	guc->submission_selected = __guc_submission_selected(guc);
पूर्ण

bool पूर्णांकel_engine_in_guc_submission_mode(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->set_शेष_submission == guc_set_शेष_submission;
पूर्ण
