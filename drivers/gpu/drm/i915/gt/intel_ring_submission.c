<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2008-2021 Intel Corporation
 */

#समावेश "gen2_engine_cs.h"
#समावेश "gen6_engine_cs.h"
#समावेश "gen6_ppgtt.h"
#समावेश "gen7_renderclear.h"
#समावेश "i915_drv.h"
#समावेश "i915_mitigations.h"
#समावेश "intel_breadcrumbs.h"
#समावेश "intel_context.h"
#समावेश "intel_gt.h"
#समावेश "intel_reset.h"
#समावेश "intel_ring.h"
#समावेश "shmem_utils.h"

/* Rough estimate of the typical request size, perक्रमming a flush,
 * set-context and then emitting the batch.
 */
#घोषणा LEGACY_REQUEST_SIZE 200

अटल व्योम set_hwstam(काष्ठा पूर्णांकel_engine_cs *engine, u32 mask)
अणु
	/*
	 * Keep the render पूर्णांकerrupt unmasked as this papers over
	 * lost पूर्णांकerrupts following a reset.
	 */
	अगर (engine->class == RENDER_CLASS) अणु
		अगर (INTEL_GEN(engine->i915) >= 6)
			mask &= ~BIT(0);
		अन्यथा
			mask &= ~I915_USER_INTERRUPT;
	पूर्ण

	पूर्णांकel_engine_set_hwsp_ग_लिखोmask(engine, mask);
पूर्ण

अटल व्योम set_hws_pga(काष्ठा पूर्णांकel_engine_cs *engine, phys_addr_t phys)
अणु
	u32 addr;

	addr = lower_32_bits(phys);
	अगर (INTEL_GEN(engine->i915) >= 4)
		addr |= (phys >> 28) & 0xf0;

	पूर्णांकel_uncore_ग_लिखो(engine->uncore, HWS_PGA, addr);
पूर्ण

अटल काष्ठा page *status_page(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_gem_object *obj = engine->status_page.vma->obj;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	वापस sg_page(obj->mm.pages->sgl);
पूर्ण

अटल व्योम ring_setup_phys_status_page(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	set_hws_pga(engine, PFN_PHYS(page_to_pfn(status_page(engine))));
	set_hwstam(engine, ~0u);
पूर्ण

अटल व्योम set_hwsp(काष्ठा पूर्णांकel_engine_cs *engine, u32 offset)
अणु
	i915_reg_t hwsp;

	/*
	 * The ring status page addresses are no दीर्घer next to the rest of
	 * the ring रेजिस्टरs as of gen7.
	 */
	अगर (IS_GEN(engine->i915, 7)) अणु
		चयन (engine->id) अणु
		/*
		 * No more rings exist on Gen7. Default हाल is only to shut up
		 * gcc चयन check warning.
		 */
		शेष:
			GEM_BUG_ON(engine->id);
			fallthrough;
		हाल RCS0:
			hwsp = RENDER_HWS_PGA_GEN7;
			अवरोध;
		हाल BCS0:
			hwsp = BLT_HWS_PGA_GEN7;
			अवरोध;
		हाल VCS0:
			hwsp = BSD_HWS_PGA_GEN7;
			अवरोध;
		हाल VECS0:
			hwsp = VEBOX_HWS_PGA_GEN7;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN(engine->i915, 6)) अणु
		hwsp = RING_HWS_PGA_GEN6(engine->mmio_base);
	पूर्ण अन्यथा अणु
		hwsp = RING_HWS_PGA(engine->mmio_base);
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो_fw(engine->uncore, hwsp, offset);
	पूर्णांकel_uncore_posting_पढ़ो_fw(engine->uncore, hwsp);
पूर्ण

अटल व्योम flush_cs_tlb(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!IS_GEN_RANGE(engine->i915, 6, 7))
		वापस;

	/* ring should be idle beक्रमe issuing a sync flush*/
	GEM_DEBUG_WARN_ON((ENGINE_READ(engine, RING_MI_MODE) & MODE_IDLE) == 0);

	ENGINE_WRITE_FW(engine, RING_INSTPM,
			_MASKED_BIT_ENABLE(INSTPM_TLB_INVALIDATE |
					   INSTPM_SYNC_FLUSH));
	अगर (__पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(engine->uncore,
					 RING_INSTPM(engine->mmio_base),
					 INSTPM_SYNC_FLUSH, 0,
					 2000, 0, शून्य))
		ENGINE_TRACE(engine,
			     "wait for SyncFlush to complete for TLB invalidation timed out\n");
पूर्ण

अटल व्योम ring_setup_status_page(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	set_hwsp(engine, i915_ggtt_offset(engine->status_page.vma));
	set_hwstam(engine, ~0u);

	flush_cs_tlb(engine);
पूर्ण

अटल काष्ठा i915_address_space *vm_alias(काष्ठा i915_address_space *vm)
अणु
	अगर (i915_is_ggtt(vm))
		vm = &i915_vm_to_ggtt(vm)->alias->vm;

	वापस vm;
पूर्ण

अटल u32 pp_dir(काष्ठा i915_address_space *vm)
अणु
	वापस to_gen6_ppgtt(i915_vm_to_ppgtt(vm))->pp_dir;
पूर्ण

अटल व्योम set_pp_dir(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_address_space *vm = vm_alias(engine->gt->vm);

	अगर (!vm)
		वापस;

	ENGINE_WRITE_FW(engine, RING_PP_सूची_DCLV, PP_सूची_DCLV_2G);
	ENGINE_WRITE_FW(engine, RING_PP_सूची_BASE, pp_dir(vm));

	अगर (INTEL_GEN(engine->i915) >= 7) अणु
		ENGINE_WRITE_FW(engine,
				RING_MODE_GEN7,
				_MASKED_BIT_ENABLE(GFX_PPGTT_ENABLE));
	पूर्ण
पूर्ण

अटल bool stop_ring(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/* Empty the ring by skipping to the end */
	ENGINE_WRITE_FW(engine, RING_HEAD, ENGINE_READ_FW(engine, RING_TAIL));
	ENGINE_POSTING_READ(engine, RING_HEAD);

	/* The ring must be empty beक्रमe it is disabled */
	ENGINE_WRITE_FW(engine, RING_CTL, 0);
	ENGINE_POSTING_READ(engine, RING_CTL);

	/* Then reset the disabled ring */
	ENGINE_WRITE_FW(engine, RING_HEAD, 0);
	ENGINE_WRITE_FW(engine, RING_TAIL, 0);

	वापस (ENGINE_READ_FW(engine, RING_HEAD) & HEAD_ADDR) == 0;
पूर्ण

अटल पूर्णांक xcs_resume(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_ring *ring = engine->legacy.ring;

	ENGINE_TRACE(engine, "ring:{HEAD:%04x, TAIL:%04x}\n",
		     ring->head, ring->tail);

	/* Double check the ring is empty & disabled beक्रमe we resume */
	synchronize_hardirq(engine->i915->drm.irq);
	अगर (!stop_ring(engine))
		जाओ err;

	अगर (HWS_NEEDS_PHYSICAL(engine->i915))
		ring_setup_phys_status_page(engine);
	अन्यथा
		ring_setup_status_page(engine);

	पूर्णांकel_bपढ़ोcrumbs_reset(engine->bपढ़ोcrumbs);

	/* Enक्रमce ordering by पढ़ोing HEAD रेजिस्टर back */
	ENGINE_POSTING_READ(engine, RING_HEAD);

	/*
	 * Initialize the ring. This must happen _after_ we've cleared the ring
	 * रेजिस्टरs with the above sequence (the पढ़ोback of the HEAD रेजिस्टरs
	 * also enक्रमces ordering), otherwise the hw might lose the new ring
	 * रेजिस्टर values.
	 */
	ENGINE_WRITE_FW(engine, RING_START, i915_ggtt_offset(ring->vma));

	/* Check that the ring offsets poपूर्णांक within the ring! */
	GEM_BUG_ON(!पूर्णांकel_ring_offset_valid(ring, ring->head));
	GEM_BUG_ON(!पूर्णांकel_ring_offset_valid(ring, ring->tail));
	पूर्णांकel_ring_update_space(ring);

	set_pp_dir(engine);

	/* First wake the ring up to an empty/idle ring */
	ENGINE_WRITE_FW(engine, RING_HEAD, ring->head);
	ENGINE_WRITE_FW(engine, RING_TAIL, ring->head);
	ENGINE_POSTING_READ(engine, RING_TAIL);

	ENGINE_WRITE_FW(engine, RING_CTL,
			RING_CTL_SIZE(ring->size) | RING_VALID);

	/* If the head is still not zero, the ring is dead */
	अगर (__पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(engine->uncore,
					 RING_CTL(engine->mmio_base),
					 RING_VALID, RING_VALID,
					 5000, 0, शून्य))
		जाओ err;

	अगर (INTEL_GEN(engine->i915) > 2)
		ENGINE_WRITE_FW(engine,
				RING_MI_MODE, _MASKED_BIT_DISABLE(STOP_RING));

	/* Now awake, let it get started */
	अगर (ring->tail != ring->head) अणु
		ENGINE_WRITE_FW(engine, RING_TAIL, ring->tail);
		ENGINE_POSTING_READ(engine, RING_TAIL);
	पूर्ण

	/* Papering over lost _पूर्णांकerrupts_ immediately following the restart */
	पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(engine);
	वापस 0;

err:
	drm_err(&engine->i915->drm,
		"%s initialization failed; "
		"ctl %08x (valid? %d) head %08x [%08x] tail %08x [%08x] start %08x [expected %08x]\n",
		engine->name,
		ENGINE_READ(engine, RING_CTL),
		ENGINE_READ(engine, RING_CTL) & RING_VALID,
		ENGINE_READ(engine, RING_HEAD), ring->head,
		ENGINE_READ(engine, RING_TAIL), ring->tail,
		ENGINE_READ(engine, RING_START),
		i915_ggtt_offset(ring->vma));
	वापस -EIO;
पूर्ण

अटल व्योम sanitize_hwsp(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_समयline *tl;

	list_क्रम_each_entry(tl, &engine->status_page.समयlines, engine_link)
		पूर्णांकel_समयline_reset_seqno(tl);
पूर्ण

अटल व्योम xcs_sanitize(काष्ठा पूर्णांकel_engine_cs *engine)
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

अटल व्योम reset_prepare(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
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
	 * WaMediaResetMainRingCleanup:ctg,elk (presumably)
	 * WaClearRingBufHeadRegAtInit:ctg,elk
	 *
	 * FIXME: Wa क्रम more modern gens needs to be validated
	 */
	ENGINE_TRACE(engine, "\n");
	पूर्णांकel_engine_stop_cs(engine);

	अगर (!stop_ring(engine)) अणु
		/* G45 ring initialization often fails to reset head to zero */
		ENGINE_TRACE(engine,
			     "HEAD not reset to zero, "
			     "{ CTL:%08x, HEAD:%08x, TAIL:%08x, START:%08x }\n",
			     ENGINE_READ_FW(engine, RING_CTL),
			     ENGINE_READ_FW(engine, RING_HEAD),
			     ENGINE_READ_FW(engine, RING_TAIL),
			     ENGINE_READ_FW(engine, RING_START));
		अगर (!stop_ring(engine)) अणु
			drm_err(&engine->i915->drm,
				"failed to set %s head to zero "
				"ctl %08x head %08x tail %08x start %08x\n",
				engine->name,
				ENGINE_READ_FW(engine, RING_CTL),
				ENGINE_READ_FW(engine, RING_HEAD),
				ENGINE_READ_FW(engine, RING_TAIL),
				ENGINE_READ_FW(engine, RING_START));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम reset_शुरुआत(काष्ठा पूर्णांकel_engine_cs *engine, bool stalled)
अणु
	काष्ठा i915_request *pos, *rq;
	अचिन्हित दीर्घ flags;
	u32 head;

	rq = शून्य;
	spin_lock_irqsave(&engine->active.lock, flags);
	rcu_पढ़ो_lock();
	list_क्रम_each_entry(pos, &engine->active.requests, sched.link) अणु
		अगर (!__i915_request_is_complete(pos)) अणु
			rq = pos;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * The guilty request will get skipped on a hung engine.
	 *
	 * Users of client शेष contexts करो not rely on logical
	 * state preserved between batches so it is safe to execute
	 * queued requests following the hang. Non शेष contexts
	 * rely on preserved state, so skipping a batch loses the
	 * evolution of the state and it needs to be considered corrupted.
	 * Executing more queued batches on top of corrupted state is
	 * risky. But we take the risk by trying to advance through
	 * the queued requests in order to make the client behaviour
	 * more predictable around resets, by not throwing away अक्रमom
	 * amount of batches it has prepared क्रम execution. Sophisticated
	 * clients can use gem_reset_stats_ioctl and dma fence status
	 * (exported via sync_file info ioctl on explicit fences) to observe
	 * when it loses the context state and should rebuild accordingly.
	 *
	 * The context ban, and ultimately the client ban, mechanism are safety
	 * valves अगर client submission ends up resulting in nothing more than
	 * subsequent hangs.
	 */

	अगर (rq) अणु
		/*
		 * Try to restore the logical GPU state to match the
		 * continuation of the request queue. If we skip the
		 * context/PD restore, then the next request may try to execute
		 * assuming that its context is valid and loaded on the GPU and
		 * so may try to access invalid memory, prompting repeated GPU
		 * hangs.
		 *
		 * If the request was guilty, we still restore the logical
		 * state in हाल the next request requires it (e.g. the
		 * aliasing ppgtt), but skip over the hung batch.
		 *
		 * If the request was innocent, we try to replay the request
		 * with the restored context.
		 */
		__i915_request_reset(rq, stalled);

		GEM_BUG_ON(rq->ring != engine->legacy.ring);
		head = rq->head;
	पूर्ण अन्यथा अणु
		head = engine->legacy.ring->tail;
	पूर्ण
	engine->legacy.ring->head = पूर्णांकel_ring_wrap(engine->legacy.ring, head);

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम reset_finish(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
पूर्ण

अटल व्योम reset_cancel(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_request *request;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&engine->active.lock, flags);

	/* Mark all submitted requests as skipped. */
	list_क्रम_each_entry(request, &engine->active.requests, sched.link)
		i915_request_put(i915_request_mark_eio(request));
	पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(engine);

	/* Reमुख्यing _unपढ़ोy_ requests will be nop'ed when submitted */

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम i9xx_submit_request(काष्ठा i915_request *request)
अणु
	i915_request_submit(request);
	wmb(); /* paranoid flush ग_लिखोs out of the WCB beक्रमe mmio */

	ENGINE_WRITE(request->engine, RING_TAIL,
		     पूर्णांकel_ring_set_tail(request->ring, request->tail));
पूर्ण

अटल व्योम __ring_context_fini(काष्ठा पूर्णांकel_context *ce)
अणु
	i915_vma_put(ce->state);
पूर्ण

अटल व्योम ring_context_destroy(काष्ठा kref *ref)
अणु
	काष्ठा पूर्णांकel_context *ce = container_of(ref, typeof(*ce), ref);

	GEM_BUG_ON(पूर्णांकel_context_is_pinned(ce));

	अगर (ce->state)
		__ring_context_fini(ce);

	पूर्णांकel_context_fini(ce);
	पूर्णांकel_context_मुक्त(ce);
पूर्ण

अटल पूर्णांक ring_context_init_शेष_state(काष्ठा पूर्णांकel_context *ce,
					   काष्ठा i915_gem_ww_ctx *ww)
अणु
	काष्ठा drm_i915_gem_object *obj = ce->state->obj;
	व्योम *vaddr;

	vaddr = i915_gem_object_pin_map(obj, I915_MAP_WB);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	shmem_पढ़ो(ce->engine->शेष_state, 0,
		   vaddr, ce->engine->context_size);

	i915_gem_object_flush_map(obj);
	__i915_gem_object_release_map(obj);

	__set_bit(CONTEXT_VALID_BIT, &ce->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ring_context_pre_pin(काष्ठा पूर्णांकel_context *ce,
				काष्ठा i915_gem_ww_ctx *ww,
				व्योम **unused)
अणु
	काष्ठा i915_address_space *vm;
	पूर्णांक err = 0;

	अगर (ce->engine->शेष_state &&
	    !test_bit(CONTEXT_VALID_BIT, &ce->flags)) अणु
		err = ring_context_init_शेष_state(ce, ww);
		अगर (err)
			वापस err;
	पूर्ण

	vm = vm_alias(ce->vm);
	अगर (vm)
		err = gen6_ppgtt_pin(i915_vm_to_ppgtt((vm)), ww);

	वापस err;
पूर्ण

अटल व्योम __context_unpin_ppgtt(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_address_space *vm;

	vm = vm_alias(ce->vm);
	अगर (vm)
		gen6_ppgtt_unpin(i915_vm_to_ppgtt(vm));
पूर्ण

अटल व्योम ring_context_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
पूर्ण

अटल व्योम ring_context_post_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
	__context_unpin_ppgtt(ce);
पूर्ण

अटल काष्ठा i915_vma *
alloc_context_vma(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	obj = i915_gem_object_create_shmem(i915, engine->context_size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	/*
	 * Try to make the context utilize L3 as well as LLC.
	 *
	 * On VLV we करोn't have L3 controls in the PTEs so we
	 * shouldn't touch the cache level, especially as that
	 * would make the object snooped which might have a
	 * negative perक्रमmance impact.
	 *
	 * Snooping is required on non-llc platक्रमms in execlist
	 * mode, but since all GGTT accesses use PAT entry 0 we
	 * get snooping anyway regardless of cache_level.
	 *
	 * This is only applicable क्रम Ivy Bridge devices since
	 * later platक्रमms करोn't have L3 control bits in the PTE.
	 */
	अगर (IS_IVYBRIDGE(i915))
		i915_gem_object_set_cache_coherency(obj, I915_CACHE_L3_LLC);

	vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_obj;
	पूर्ण

	वापस vma;

err_obj:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक ring_context_alloc(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;

	/* One ringbuffer to rule them all */
	GEM_BUG_ON(!engine->legacy.ring);
	ce->ring = engine->legacy.ring;
	ce->समयline = पूर्णांकel_समयline_get(engine->legacy.समयline);

	GEM_BUG_ON(ce->state);
	अगर (engine->context_size) अणु
		काष्ठा i915_vma *vma;

		vma = alloc_context_vma(engine);
		अगर (IS_ERR(vma))
			वापस PTR_ERR(vma);

		ce->state = vma;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ring_context_pin(काष्ठा पूर्णांकel_context *ce, व्योम *unused)
अणु
	वापस 0;
पूर्ण

अटल व्योम ring_context_reset(काष्ठा पूर्णांकel_context *ce)
अणु
	पूर्णांकel_ring_reset(ce->ring, ce->ring->emit);
	clear_bit(CONTEXT_VALID_BIT, &ce->flags);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_context_ops ring_context_ops = अणु
	.alloc = ring_context_alloc,

	.pre_pin = ring_context_pre_pin,
	.pin = ring_context_pin,
	.unpin = ring_context_unpin,
	.post_unpin = ring_context_post_unpin,

	.enter = पूर्णांकel_context_enter_engine,
	.निकास = पूर्णांकel_context_निकास_engine,

	.reset = ring_context_reset,
	.destroy = ring_context_destroy,
पूर्ण;

अटल पूर्णांक load_pd_dir(काष्ठा i915_request *rq,
		       काष्ठा i915_address_space *vm,
		       u32 valid)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs * स्थिर engine = rq->engine;
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 12);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(RING_PP_सूची_DCLV(engine->mmio_base));
	*cs++ = valid;

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(RING_PP_सूची_BASE(engine->mmio_base));
	*cs++ = pp_dir(vm);

	/* Stall until the page table load is complete? */
	*cs++ = MI_STORE_REGISTER_MEM | MI_SRM_LRM_GLOBAL_GTT;
	*cs++ = i915_mmio_reg_offset(RING_PP_सूची_BASE(engine->mmio_base));
	*cs++ = पूर्णांकel_gt_scratch_offset(engine->gt,
					INTEL_GT_SCRATCH_FIELD_DEFAULT);

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(RING_INSTPM(engine->mmio_base));
	*cs++ = _MASKED_BIT_ENABLE(INSTPM_TLB_INVALIDATE);

	पूर्णांकel_ring_advance(rq, cs);

	वापस rq->engine->emit_flush(rq, EMIT_FLUSH);
पूर्ण

अटल पूर्णांक mi_set_context(काष्ठा i915_request *rq,
			  काष्ठा पूर्णांकel_context *ce,
			  u32 flags)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	काष्ठा drm_i915_निजी *i915 = engine->i915;
	क्रमागत पूर्णांकel_engine_id id;
	स्थिर पूर्णांक num_engines =
		IS_HASWELL(i915) ? engine->gt->info.num_engines - 1 : 0;
	bool क्रमce_restore = false;
	पूर्णांक len;
	u32 *cs;

	len = 4;
	अगर (IS_GEN(i915, 7))
		len += 2 + (num_engines ? 4 * num_engines + 6 : 0);
	अन्यथा अगर (IS_GEN(i915, 5))
		len += 2;
	अगर (flags & MI_FORCE_RESTORE) अणु
		GEM_BUG_ON(flags & MI_RESTORE_INHIBIT);
		flags &= ~MI_FORCE_RESTORE;
		क्रमce_restore = true;
		len += 2;
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, len);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	/* WaProgramMiArbOnOffAroundMiSetContext:ivb,vlv,hsw,bdw,chv */
	अगर (IS_GEN(i915, 7)) अणु
		*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;
		अगर (num_engines) अणु
			काष्ठा पूर्णांकel_engine_cs *संकेतler;

			*cs++ = MI_LOAD_REGISTER_IMM(num_engines);
			क्रम_each_engine(संकेतler, engine->gt, id) अणु
				अगर (संकेतler == engine)
					जारी;

				*cs++ = i915_mmio_reg_offset(
					   RING_PSMI_CTL(संकेतler->mmio_base));
				*cs++ = _MASKED_BIT_ENABLE(
						GEN6_PSMI_SLEEP_MSG_DISABLE);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN(i915, 5)) अणु
		/*
		 * This w/a is only listed क्रम pre-production ilk a/b steppings,
		 * but is also mentioned क्रम programming the घातerctx. To be
		 * safe, just apply the workaround; we करो not use SyncFlush so
		 * this should never take effect and so be a no-op!
		 */
		*cs++ = MI_SUSPEND_FLUSH | MI_SUSPEND_FLUSH_EN;
	पूर्ण

	अगर (क्रमce_restore) अणु
		/*
		 * The HW करोesn't handle being told to restore the current
		 * context very well. Quite often it likes goes to go off and
		 * sulk, especially when it is meant to be reloading PP_सूची.
		 * A very simple fix to क्रमce the reload is to simply चयन
		 * away from the current context and back again.
		 *
		 * Note that the kernel_context will contain अक्रमom state
		 * following the INHIBIT_RESTORE. We accept this since we
		 * never use the kernel_context state; it is merely a
		 * placeholder we use to flush other contexts.
		 */
		*cs++ = MI_SET_CONTEXT;
		*cs++ = i915_ggtt_offset(engine->kernel_context->state) |
			MI_MM_SPACE_GTT |
			MI_RESTORE_INHIBIT;
	पूर्ण

	*cs++ = MI_NOOP;
	*cs++ = MI_SET_CONTEXT;
	*cs++ = i915_ggtt_offset(ce->state) | flags;
	/*
	 * w/a: MI_SET_CONTEXT must always be followed by MI_NOOP
	 * WaMiSetContext_Hang:snb,ivb,vlv
	 */
	*cs++ = MI_NOOP;

	अगर (IS_GEN(i915, 7)) अणु
		अगर (num_engines) अणु
			काष्ठा पूर्णांकel_engine_cs *संकेतler;
			i915_reg_t last_reg = अणुपूर्ण; /* keep gcc quiet */

			*cs++ = MI_LOAD_REGISTER_IMM(num_engines);
			क्रम_each_engine(संकेतler, engine->gt, id) अणु
				अगर (संकेतler == engine)
					जारी;

				last_reg = RING_PSMI_CTL(संकेतler->mmio_base);
				*cs++ = i915_mmio_reg_offset(last_reg);
				*cs++ = _MASKED_BIT_DISABLE(
						GEN6_PSMI_SLEEP_MSG_DISABLE);
			पूर्ण

			/* Insert a delay beक्रमe the next चयन! */
			*cs++ = MI_STORE_REGISTER_MEM | MI_SRM_LRM_GLOBAL_GTT;
			*cs++ = i915_mmio_reg_offset(last_reg);
			*cs++ = पूर्णांकel_gt_scratch_offset(engine->gt,
							INTEL_GT_SCRATCH_FIELD_DEFAULT);
			*cs++ = MI_NOOP;
		पूर्ण
		*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	पूर्ण अन्यथा अगर (IS_GEN(i915, 5)) अणु
		*cs++ = MI_SUSPEND_FLUSH;
	पूर्ण

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक remap_l3_slice(काष्ठा i915_request *rq, पूर्णांक slice)
अणु
#घोषणा L3LOG_DW (GEN7_L3LOG_SIZE / माप(u32))
	u32 *cs, *remap_info = rq->engine->i915->l3_parity.remap_info[slice];
	पूर्णांक i;

	अगर (!remap_info)
		वापस 0;

	cs = पूर्णांकel_ring_begin(rq, L3LOG_DW * 2 + 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	/*
	 * Note: We करो not worry about the concurrent रेजिस्टर cacheline hang
	 * here because no other code should access these रेजिस्टरs other than
	 * at initialization समय.
	 */
	*cs++ = MI_LOAD_REGISTER_IMM(L3LOG_DW);
	क्रम (i = 0; i < L3LOG_DW; i++) अणु
		*cs++ = i915_mmio_reg_offset(GEN7_L3LOG(slice, i));
		*cs++ = remap_info[i];
	पूर्ण
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
#अघोषित L3LOG_DW
पूर्ण

अटल पूर्णांक remap_l3(काष्ठा i915_request *rq)
अणु
	काष्ठा i915_gem_context *ctx = i915_request_gem_context(rq);
	पूर्णांक i, err;

	अगर (!ctx || !ctx->remap_slice)
		वापस 0;

	क्रम (i = 0; i < MAX_L3_SLICES; i++) अणु
		अगर (!(ctx->remap_slice & BIT(i)))
			जारी;

		err = remap_l3_slice(rq, i);
		अगर (err)
			वापस err;
	पूर्ण

	ctx->remap_slice = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक चयन_mm(काष्ठा i915_request *rq, काष्ठा i915_address_space *vm)
अणु
	पूर्णांक ret;

	अगर (!vm)
		वापस 0;

	ret = rq->engine->emit_flush(rq, EMIT_FLUSH);
	अगर (ret)
		वापस ret;

	/*
	 * Not only करो we need a full barrier (post-sync ग_लिखो) after
	 * invalidating the TLBs, but we need to रुको a little bit
	 * दीर्घer. Whether this is merely delaying us, or the
	 * subsequent flush is a key part of serialising with the
	 * post-sync op, this extra pass appears vital beक्रमe a
	 * mm चयन!
	 */
	ret = load_pd_dir(rq, vm, PP_सूची_DCLV_2G);
	अगर (ret)
		वापस ret;

	वापस rq->engine->emit_flush(rq, EMIT_INVALIDATE);
पूर्ण

अटल पूर्णांक clear_residuals(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	पूर्णांक ret;

	ret = चयन_mm(rq, vm_alias(engine->kernel_context->vm));
	अगर (ret)
		वापस ret;

	अगर (engine->kernel_context->state) अणु
		ret = mi_set_context(rq,
				     engine->kernel_context,
				     MI_MM_SPACE_GTT | MI_RESTORE_INHIBIT);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = engine->emit_bb_start(rq,
				    engine->wa_ctx.vma->node.start, 0,
				    0);
	अगर (ret)
		वापस ret;

	ret = engine->emit_flush(rq, EMIT_FLUSH);
	अगर (ret)
		वापस ret;

	/* Always invalidate beक्रमe the next चयन_mm() */
	वापस engine->emit_flush(rq, EMIT_INVALIDATE);
पूर्ण

अटल पूर्णांक चयन_context(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	काष्ठा पूर्णांकel_context *ce = rq->context;
	व्योम **residuals = शून्य;
	पूर्णांक ret;

	GEM_BUG_ON(HAS_EXECLISTS(engine->i915));

	अगर (engine->wa_ctx.vma && ce != engine->kernel_context) अणु
		अगर (engine->wa_ctx.vma->निजी != ce &&
		    i915_mitigate_clear_residuals()) अणु
			ret = clear_residuals(rq);
			अगर (ret)
				वापस ret;

			residuals = &engine->wa_ctx.vma->निजी;
		पूर्ण
	पूर्ण

	ret = चयन_mm(rq, vm_alias(ce->vm));
	अगर (ret)
		वापस ret;

	अगर (ce->state) अणु
		u32 flags;

		GEM_BUG_ON(engine->id != RCS0);

		/* For resource streamer on HSW+ and घातer context अन्यथाwhere */
		BUILD_BUG_ON(HSW_MI_RS_SAVE_STATE_EN != MI_SAVE_EXT_STATE_EN);
		BUILD_BUG_ON(HSW_MI_RS_RESTORE_STATE_EN != MI_RESTORE_EXT_STATE_EN);

		flags = MI_SAVE_EXT_STATE_EN | MI_MM_SPACE_GTT;
		अगर (test_bit(CONTEXT_VALID_BIT, &ce->flags))
			flags |= MI_RESTORE_EXT_STATE_EN;
		अन्यथा
			flags |= MI_RESTORE_INHIBIT;

		ret = mi_set_context(rq, ce, flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = remap_l3(rq);
	अगर (ret)
		वापस ret;

	/*
	 * Now past the poपूर्णांक of no वापस, this request _will_ be emitted.
	 *
	 * Or at least this preamble will be emitted, the request may be
	 * पूर्णांकerrupted prior to submitting the user payload. If so, we
	 * still submit the "empty" request in order to preserve global
	 * state tracking such as this, our tracking of the current
	 * dirty context.
	 */
	अगर (residuals) अणु
		पूर्णांकel_context_put(*residuals);
		*residuals = पूर्णांकel_context_get(ce);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ring_request_alloc(काष्ठा i915_request *request)
अणु
	पूर्णांक ret;

	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(request->context));
	GEM_BUG_ON(i915_request_समयline(request)->has_initial_bपढ़ोcrumb);

	/*
	 * Flush enough space to reduce the likelihood of रुकोing after
	 * we start building the request - in which हाल we will just
	 * have to repeat work.
	 */
	request->reserved_space += LEGACY_REQUEST_SIZE;

	/* Unconditionally invalidate GPU caches and TLBs. */
	ret = request->engine->emit_flush(request, EMIT_INVALIDATE);
	अगर (ret)
		वापस ret;

	ret = चयन_context(request);
	अगर (ret)
		वापस ret;

	request->reserved_space -= LEGACY_REQUEST_SIZE;
	वापस 0;
पूर्ण

अटल व्योम gen6_bsd_submit_request(काष्ठा i915_request *request)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = request->engine->uncore;

	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);

       /* Every tail move must follow the sequence below */

	/* Disable notअगरication that the ring is IDLE. The GT
	 * will then assume that it is busy and bring it out of rc6.
	 */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_BSD_SLEEP_PSMI_CONTROL,
			      _MASKED_BIT_ENABLE(GEN6_BSD_SLEEP_MSG_DISABLE));

	/* Clear the context id. Here be magic! */
	पूर्णांकel_uncore_ग_लिखो64_fw(uncore, GEN6_BSD_RNCID, 0x0);

	/* Wait क्रम the ring not to be idle, i.e. क्रम it to wake up. */
	अगर (__पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					 GEN6_BSD_SLEEP_PSMI_CONTROL,
					 GEN6_BSD_SLEEP_INDICATOR,
					 0,
					 1000, 0, शून्य))
		drm_err(&uncore->i915->drm,
			"timed out waiting for the BSD ring to wake up\n");

	/* Now that the ring is fully घातered up, update the tail */
	i9xx_submit_request(request);

	/* Let the ring send IDLE messages to the GT again,
	 * and so let it sleep to conserve घातer when idle.
	 */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_BSD_SLEEP_PSMI_CONTROL,
			      _MASKED_BIT_DISABLE(GEN6_BSD_SLEEP_MSG_DISABLE));

	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);
पूर्ण

अटल व्योम i9xx_set_शेष_submission(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->submit_request = i9xx_submit_request;

	engine->park = शून्य;
	engine->unpark = शून्य;
पूर्ण

अटल व्योम gen6_bsd_set_शेष_submission(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	i9xx_set_शेष_submission(engine);
	engine->submit_request = gen6_bsd_submit_request;
पूर्ण

अटल व्योम ring_release(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *dev_priv = engine->i915;

	drm_WARN_ON(&dev_priv->drm, INTEL_GEN(dev_priv) > 2 &&
		    (ENGINE_READ(engine, RING_MI_MODE) & MODE_IDLE) == 0);

	पूर्णांकel_engine_cleanup_common(engine);

	अगर (engine->wa_ctx.vma) अणु
		पूर्णांकel_context_put(engine->wa_ctx.vma->निजी);
		i915_vma_unpin_and_release(&engine->wa_ctx.vma, 0);
	पूर्ण

	पूर्णांकel_ring_unpin(engine->legacy.ring);
	पूर्णांकel_ring_put(engine->legacy.ring);

	पूर्णांकel_समयline_unpin(engine->legacy.समयline);
	पूर्णांकel_समयline_put(engine->legacy.समयline);
पूर्ण

अटल व्योम setup_irq(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (INTEL_GEN(i915) >= 6) अणु
		engine->irq_enable = gen6_irq_enable;
		engine->irq_disable = gen6_irq_disable;
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 5) अणु
		engine->irq_enable = gen5_irq_enable;
		engine->irq_disable = gen5_irq_disable;
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 3) अणु
		engine->irq_enable = gen3_irq_enable;
		engine->irq_disable = gen3_irq_disable;
	पूर्ण अन्यथा अणु
		engine->irq_enable = gen2_irq_enable;
		engine->irq_disable = gen2_irq_disable;
	पूर्ण
पूर्ण

अटल व्योम setup_common(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	/* gen8+ are only supported with execlists */
	GEM_BUG_ON(INTEL_GEN(i915) >= 8);

	setup_irq(engine);

	engine->resume = xcs_resume;
	engine->sanitize = xcs_sanitize;

	engine->reset.prepare = reset_prepare;
	engine->reset.शुरुआत = reset_शुरुआत;
	engine->reset.cancel = reset_cancel;
	engine->reset.finish = reset_finish;

	engine->cops = &ring_context_ops;
	engine->request_alloc = ring_request_alloc;

	/*
	 * Using a global execution समयline; the previous final bपढ़ोcrumb is
	 * equivalent to our next initial bपढ़ो so we can elide
	 * engine->emit_init_bपढ़ोcrumb().
	 */
	engine->emit_fini_bपढ़ोcrumb = gen3_emit_bपढ़ोcrumb;
	अगर (IS_GEN(i915, 5))
		engine->emit_fini_bपढ़ोcrumb = gen5_emit_bपढ़ोcrumb;

	engine->set_शेष_submission = i9xx_set_शेष_submission;

	अगर (INTEL_GEN(i915) >= 6)
		engine->emit_bb_start = gen6_emit_bb_start;
	अन्यथा अगर (INTEL_GEN(i915) >= 4)
		engine->emit_bb_start = gen4_emit_bb_start;
	अन्यथा अगर (IS_I830(i915) || IS_I845G(i915))
		engine->emit_bb_start = i830_emit_bb_start;
	अन्यथा
		engine->emit_bb_start = gen3_emit_bb_start;
पूर्ण

अटल व्योम setup_rcs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (HAS_L3_DPF(i915))
		engine->irq_keep_mask = GT_RENDER_L3_PARITY_ERROR_INTERRUPT;

	engine->irq_enable_mask = GT_RENDER_USER_INTERRUPT;

	अगर (INTEL_GEN(i915) >= 7) अणु
		engine->emit_flush = gen7_emit_flush_rcs;
		engine->emit_fini_bपढ़ोcrumb = gen7_emit_bपढ़ोcrumb_rcs;
	पूर्ण अन्यथा अगर (IS_GEN(i915, 6)) अणु
		engine->emit_flush = gen6_emit_flush_rcs;
		engine->emit_fini_bपढ़ोcrumb = gen6_emit_bपढ़ोcrumb_rcs;
	पूर्ण अन्यथा अगर (IS_GEN(i915, 5)) अणु
		engine->emit_flush = gen4_emit_flush_rcs;
	पूर्ण अन्यथा अणु
		अगर (INTEL_GEN(i915) < 4)
			engine->emit_flush = gen2_emit_flush;
		अन्यथा
			engine->emit_flush = gen4_emit_flush_rcs;
		engine->irq_enable_mask = I915_USER_INTERRUPT;
	पूर्ण

	अगर (IS_HASWELL(i915))
		engine->emit_bb_start = hsw_emit_bb_start;
पूर्ण

अटल व्योम setup_vcs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (INTEL_GEN(i915) >= 6) अणु
		/* gen6 bsd needs a special wa क्रम tail updates */
		अगर (IS_GEN(i915, 6))
			engine->set_शेष_submission = gen6_bsd_set_शेष_submission;
		engine->emit_flush = gen6_emit_flush_vcs;
		engine->irq_enable_mask = GT_BSD_USER_INTERRUPT;

		अगर (IS_GEN(i915, 6))
			engine->emit_fini_bपढ़ोcrumb = gen6_emit_bपढ़ोcrumb_xcs;
		अन्यथा
			engine->emit_fini_bपढ़ोcrumb = gen7_emit_bपढ़ोcrumb_xcs;
	पूर्ण अन्यथा अणु
		engine->emit_flush = gen4_emit_flush_vcs;
		अगर (IS_GEN(i915, 5))
			engine->irq_enable_mask = ILK_BSD_USER_INTERRUPT;
		अन्यथा
			engine->irq_enable_mask = I915_BSD_USER_INTERRUPT;
	पूर्ण
पूर्ण

अटल व्योम setup_bcs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	engine->emit_flush = gen6_emit_flush_xcs;
	engine->irq_enable_mask = GT_BLT_USER_INTERRUPT;

	अगर (IS_GEN(i915, 6))
		engine->emit_fini_bपढ़ोcrumb = gen6_emit_bपढ़ोcrumb_xcs;
	अन्यथा
		engine->emit_fini_bपढ़ोcrumb = gen7_emit_bपढ़ोcrumb_xcs;
पूर्ण

अटल व्योम setup_vecs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	GEM_BUG_ON(INTEL_GEN(i915) < 7);

	engine->emit_flush = gen6_emit_flush_xcs;
	engine->irq_enable_mask = PM_VEBOX_USER_INTERRUPT;
	engine->irq_enable = hsw_irq_enable_vecs;
	engine->irq_disable = hsw_irq_disable_vecs;

	engine->emit_fini_bपढ़ोcrumb = gen7_emit_bपढ़ोcrumb_xcs;
पूर्ण

अटल पूर्णांक gen7_ctx_चयन_bb_setup(काष्ठा पूर्णांकel_engine_cs * स्थिर engine,
				    काष्ठा i915_vma * स्थिर vma)
अणु
	वापस gen7_setup_clear_gpr_bb(engine, vma);
पूर्ण

अटल पूर्णांक gen7_ctx_चयन_bb_init(काष्ठा पूर्णांकel_engine_cs *engine,
				   काष्ठा i915_gem_ww_ctx *ww,
				   काष्ठा i915_vma *vma)
अणु
	पूर्णांक err;

	err = i915_vma_pin_ww(vma, ww, 0, 0, PIN_USER | PIN_HIGH);
	अगर (err)
		वापस err;

	err = i915_vma_sync(vma);
	अगर (err)
		जाओ err_unpin;

	err = gen7_ctx_चयन_bb_setup(engine, vma);
	अगर (err)
		जाओ err_unpin;

	engine->wa_ctx.vma = vma;
	वापस 0;

err_unpin:
	i915_vma_unpin(vma);
	वापस err;
पूर्ण

अटल काष्ठा i915_vma *gen7_ctx_vma(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक size, err;

	अगर (!IS_GEN(engine->i915, 7) || engine->class != RENDER_CLASS)
		वापस 0;

	err = gen7_ctx_चयन_bb_setup(engine, शून्य /* probe size */);
	अगर (err < 0)
		वापस ERR_PTR(err);
	अगर (!err)
		वापस शून्य;

	size = ALIGN(err, PAGE_SIZE);

	obj = i915_gem_object_create_पूर्णांकernal(engine->i915, size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, engine->gt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस ERR_CAST(vma);
	पूर्ण

	vma->निजी = पूर्णांकel_context_create(engine); /* dummy residuals */
	अगर (IS_ERR(vma->निजी)) अणु
		err = PTR_ERR(vma->निजी);
		vma->निजी = शून्य;
		i915_gem_object_put(obj);
		वापस ERR_PTR(err);
	पूर्ण

	वापस vma;
पूर्ण

पूर्णांक पूर्णांकel_ring_submission_setup(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा पूर्णांकel_समयline *समयline;
	काष्ठा पूर्णांकel_ring *ring;
	काष्ठा i915_vma *gen7_wa_vma;
	पूर्णांक err;

	setup_common(engine);

	चयन (engine->class) अणु
	हाल RENDER_CLASS:
		setup_rcs(engine);
		अवरोध;
	हाल VIDEO_DECODE_CLASS:
		setup_vcs(engine);
		अवरोध;
	हाल COPY_ENGINE_CLASS:
		setup_bcs(engine);
		अवरोध;
	हाल VIDEO_ENHANCEMENT_CLASS:
		setup_vecs(engine);
		अवरोध;
	शेष:
		MISSING_CASE(engine->class);
		वापस -ENODEV;
	पूर्ण

	समयline = पूर्णांकel_समयline_create_from_engine(engine,
						     I915_GEM_HWS_SEQNO_ADDR);
	अगर (IS_ERR(समयline)) अणु
		err = PTR_ERR(समयline);
		जाओ err;
	पूर्ण
	GEM_BUG_ON(समयline->has_initial_bपढ़ोcrumb);

	ring = पूर्णांकel_engine_create_ring(engine, SZ_16K);
	अगर (IS_ERR(ring)) अणु
		err = PTR_ERR(ring);
		जाओ err_समयline;
	पूर्ण

	GEM_BUG_ON(engine->legacy.ring);
	engine->legacy.ring = ring;
	engine->legacy.समयline = समयline;

	gen7_wa_vma = gen7_ctx_vma(engine);
	अगर (IS_ERR(gen7_wa_vma)) अणु
		err = PTR_ERR(gen7_wa_vma);
		जाओ err_ring;
	पूर्ण

	i915_gem_ww_ctx_init(&ww, false);

retry:
	err = i915_gem_object_lock(समयline->hwsp_ggtt->obj, &ww);
	अगर (!err && gen7_wa_vma)
		err = i915_gem_object_lock(gen7_wa_vma->obj, &ww);
	अगर (!err && engine->legacy.ring->vma->obj)
		err = i915_gem_object_lock(engine->legacy.ring->vma->obj, &ww);
	अगर (!err)
		err = पूर्णांकel_समयline_pin(समयline, &ww);
	अगर (!err) अणु
		err = पूर्णांकel_ring_pin(ring, &ww);
		अगर (err)
			पूर्णांकel_समयline_unpin(समयline);
	पूर्ण
	अगर (err)
		जाओ out;

	GEM_BUG_ON(समयline->hwsp_ggtt != engine->status_page.vma);

	अगर (gen7_wa_vma) अणु
		err = gen7_ctx_चयन_bb_init(engine, &ww, gen7_wa_vma);
		अगर (err) अणु
			पूर्णांकel_ring_unpin(ring);
			पूर्णांकel_समयline_unpin(समयline);
		पूर्ण
	पूर्ण

out:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	अगर (err)
		जाओ err_gen7_put;

	/* Finally, take ownership and responsibility क्रम cleanup! */
	engine->release = ring_release;

	वापस 0;

err_gen7_put:
	अगर (gen7_wa_vma) अणु
		पूर्णांकel_context_put(gen7_wa_vma->निजी);
		i915_gem_object_put(gen7_wa_vma->obj);
	पूर्ण
err_ring:
	पूर्णांकel_ring_put(ring);
err_समयline:
	पूर्णांकel_समयline_put(समयline);
err:
	पूर्णांकel_engine_cleanup_common(engine);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_ring_submission.c"
#पूर्ण_अगर
