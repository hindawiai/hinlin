<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "gem/i915_gem_context.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_drv.h"
#समावेश "intel_context.h"
#समावेश "intel_engine_pm.h"

#समावेश "mock_engine.h"
#समावेश "selftests/mock_request.h"

अटल पूर्णांक mock_समयline_pin(काष्ठा पूर्णांकel_समयline *tl)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!i915_gem_object_trylock(tl->hwsp_ggtt->obj)))
		वापस -EBUSY;

	err = पूर्णांकel_समयline_pin_map(tl);
	i915_gem_object_unlock(tl->hwsp_ggtt->obj);
	अगर (err)
		वापस err;

	atomic_inc(&tl->pin_count);
	वापस 0;
पूर्ण

अटल व्योम mock_समयline_unpin(काष्ठा पूर्णांकel_समयline *tl)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&tl->pin_count));
	atomic_dec(&tl->pin_count);
पूर्ण

अटल काष्ठा पूर्णांकel_ring *mock_ring(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर अचिन्हित दीर्घ sz = PAGE_SIZE / 2;
	काष्ठा पूर्णांकel_ring *ring;

	ring = kzalloc(माप(*ring) + sz, GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	kref_init(&ring->ref);
	ring->size = sz;
	ring->effective_size = sz;
	ring->vaddr = (व्योम *)(ring + 1);
	atomic_set(&ring->pin_count, 1);

	ring->vma = i915_vma_alloc();
	अगर (!ring->vma) अणु
		kमुक्त(ring);
		वापस शून्य;
	पूर्ण
	i915_active_init(&ring->vma->active, शून्य, शून्य);
	__set_bit(I915_VMA_GGTT_BIT, __i915_vma_flags(ring->vma));
	__set_bit(DRM_MM_NODE_ALLOCATED_BIT, &ring->vma->node.flags);
	ring->vma->node.size = sz;

	पूर्णांकel_ring_update_space(ring);

	वापस ring;
पूर्ण

अटल व्योम mock_ring_मुक्त(काष्ठा पूर्णांकel_ring *ring)
अणु
	i915_active_fini(&ring->vma->active);
	i915_vma_मुक्त(ring->vma);

	kमुक्त(ring);
पूर्ण

अटल काष्ठा i915_request *first_request(काष्ठा mock_engine *engine)
अणु
	वापस list_first_entry_or_null(&engine->hw_queue,
					काष्ठा i915_request,
					mock.link);
पूर्ण

अटल व्योम advance(काष्ठा i915_request *request)
अणु
	list_del_init(&request->mock.link);
	i915_request_mark_complete(request);
	GEM_BUG_ON(!i915_request_completed(request));

	पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(request->engine);
पूर्ण

अटल व्योम hw_delay_complete(काष्ठा समयr_list *t)
अणु
	काष्ठा mock_engine *engine = from_समयr(engine, t, hw_delay);
	काष्ठा i915_request *request;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&engine->hw_lock, flags);

	/* Timer fired, first request is complete */
	request = first_request(engine);
	अगर (request)
		advance(request);

	/*
	 * Also immediately संकेत any subsequent 0-delay requests, but
	 * requeue the समयr क्रम the next delayed request.
	 */
	जबतक ((request = first_request(engine))) अणु
		अगर (request->mock.delay) अणु
			mod_समयr(&engine->hw_delay,
				  jअगरfies + request->mock.delay);
			अवरोध;
		पूर्ण

		advance(request);
	पूर्ण

	spin_unlock_irqrestore(&engine->hw_lock, flags);
पूर्ण

अटल व्योम mock_context_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
पूर्ण

अटल व्योम mock_context_post_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
पूर्ण

अटल व्योम mock_context_destroy(काष्ठा kref *ref)
अणु
	काष्ठा पूर्णांकel_context *ce = container_of(ref, typeof(*ce), ref);

	GEM_BUG_ON(पूर्णांकel_context_is_pinned(ce));

	अगर (test_bit(CONTEXT_ALLOC_BIT, &ce->flags)) अणु
		mock_ring_मुक्त(ce->ring);
		mock_समयline_unpin(ce->समयline);
	पूर्ण

	पूर्णांकel_context_fini(ce);
	पूर्णांकel_context_मुक्त(ce);
पूर्ण

अटल पूर्णांक mock_context_alloc(काष्ठा पूर्णांकel_context *ce)
अणु
	पूर्णांक err;

	ce->ring = mock_ring(ce->engine);
	अगर (!ce->ring)
		वापस -ENOMEM;

	ce->समयline = पूर्णांकel_समयline_create(ce->engine->gt);
	अगर (IS_ERR(ce->समयline)) अणु
		kमुक्त(ce->engine);
		वापस PTR_ERR(ce->समयline);
	पूर्ण

	err = mock_समयline_pin(ce->समयline);
	अगर (err) अणु
		पूर्णांकel_समयline_put(ce->समयline);
		ce->समयline = शून्य;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mock_context_pre_pin(काष्ठा पूर्णांकel_context *ce,
				काष्ठा i915_gem_ww_ctx *ww, व्योम **unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mock_context_pin(काष्ठा पूर्णांकel_context *ce, व्योम *unused)
अणु
	वापस 0;
पूर्ण

अटल व्योम mock_context_reset(काष्ठा पूर्णांकel_context *ce)
अणु
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_context_ops mock_context_ops = अणु
	.alloc = mock_context_alloc,

	.pre_pin = mock_context_pre_pin,
	.pin = mock_context_pin,
	.unpin = mock_context_unpin,
	.post_unpin = mock_context_post_unpin,

	.enter = पूर्णांकel_context_enter_engine,
	.निकास = पूर्णांकel_context_निकास_engine,

	.reset = mock_context_reset,
	.destroy = mock_context_destroy,
पूर्ण;

अटल पूर्णांक mock_request_alloc(काष्ठा i915_request *request)
अणु
	INIT_LIST_HEAD(&request->mock.link);
	request->mock.delay = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mock_emit_flush(काष्ठा i915_request *request,
			   अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल u32 *mock_emit_bपढ़ोcrumb(काष्ठा i915_request *request, u32 *cs)
अणु
	वापस cs;
पूर्ण

अटल व्योम mock_submit_request(काष्ठा i915_request *request)
अणु
	काष्ठा mock_engine *engine =
		container_of(request->engine, typeof(*engine), base);
	अचिन्हित दीर्घ flags;

	i915_request_submit(request);

	spin_lock_irqsave(&engine->hw_lock, flags);
	list_add_tail(&request->mock.link, &engine->hw_queue);
	अगर (list_is_first(&request->mock.link, &engine->hw_queue)) अणु
		अगर (request->mock.delay)
			mod_समयr(&engine->hw_delay,
				  jअगरfies + request->mock.delay);
		अन्यथा
			advance(request);
	पूर्ण
	spin_unlock_irqrestore(&engine->hw_lock, flags);
पूर्ण

अटल व्योम mock_reset_prepare(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
पूर्ण

अटल व्योम mock_reset_शुरुआत(काष्ठा पूर्णांकel_engine_cs *engine, bool stalled)
अणु
	GEM_BUG_ON(stalled);
पूर्ण

अटल व्योम mock_reset_cancel(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा mock_engine *mock =
		container_of(engine, typeof(*mock), base);
	काष्ठा i915_request *rq;
	अचिन्हित दीर्घ flags;

	del_समयr_sync(&mock->hw_delay);

	spin_lock_irqsave(&engine->active.lock, flags);

	/* Mark all submitted requests as skipped. */
	list_क्रम_each_entry(rq, &engine->active.requests, sched.link)
		i915_request_put(i915_request_mark_eio(rq));
	पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(engine);

	/* Cancel and submit all pending requests. */
	list_क्रम_each_entry(rq, &mock->hw_queue, mock.link) अणु
		अगर (i915_request_mark_eio(rq)) अणु
			__i915_request_submit(rq);
			i915_request_put(rq);
		पूर्ण
	पूर्ण
	INIT_LIST_HEAD(&mock->hw_queue);

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम mock_reset_finish(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
पूर्ण

अटल व्योम mock_engine_release(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा mock_engine *mock =
		container_of(engine, typeof(*mock), base);

	GEM_BUG_ON(समयr_pending(&mock->hw_delay));

	पूर्णांकel_bपढ़ोcrumbs_मुक्त(engine->bपढ़ोcrumbs);

	पूर्णांकel_context_unpin(engine->kernel_context);
	पूर्णांकel_context_put(engine->kernel_context);

	पूर्णांकel_engine_fini_retire(engine);
पूर्ण

काष्ठा पूर्णांकel_engine_cs *mock_engine(काष्ठा drm_i915_निजी *i915,
				    स्थिर अक्षर *name,
				    पूर्णांक id)
अणु
	काष्ठा mock_engine *engine;

	GEM_BUG_ON(id >= I915_NUM_ENGINES);
	GEM_BUG_ON(!i915->gt.uncore);

	engine = kzalloc(माप(*engine) + PAGE_SIZE, GFP_KERNEL);
	अगर (!engine)
		वापस शून्य;

	/* minimal engine setup क्रम requests */
	engine->base.i915 = i915;
	engine->base.gt = &i915->gt;
	engine->base.uncore = i915->gt.uncore;
	snम_लिखो(engine->base.name, माप(engine->base.name), "%s", name);
	engine->base.id = id;
	engine->base.mask = BIT(id);
	engine->base.legacy_idx = INVALID_ENGINE;
	engine->base.instance = id;
	engine->base.status_page.addr = (व्योम *)(engine + 1);

	engine->base.cops = &mock_context_ops;
	engine->base.request_alloc = mock_request_alloc;
	engine->base.emit_flush = mock_emit_flush;
	engine->base.emit_fini_bपढ़ोcrumb = mock_emit_bपढ़ोcrumb;
	engine->base.submit_request = mock_submit_request;

	engine->base.reset.prepare = mock_reset_prepare;
	engine->base.reset.शुरुआत = mock_reset_शुरुआत;
	engine->base.reset.cancel = mock_reset_cancel;
	engine->base.reset.finish = mock_reset_finish;

	engine->base.release = mock_engine_release;

	i915->gt.engine[id] = &engine->base;
	i915->gt.engine_class[0][id] = &engine->base;

	/* fake hw queue */
	spin_lock_init(&engine->hw_lock);
	समयr_setup(&engine->hw_delay, hw_delay_complete, 0);
	INIT_LIST_HEAD(&engine->hw_queue);

	पूर्णांकel_engine_add_user(&engine->base);

	वापस &engine->base;
पूर्ण

पूर्णांक mock_engine_init(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;

	पूर्णांकel_engine_init_active(engine, ENGINE_MOCK);
	पूर्णांकel_engine_init_execlists(engine);
	पूर्णांकel_engine_init__pm(engine);
	पूर्णांकel_engine_init_retire(engine);

	engine->bपढ़ोcrumbs = पूर्णांकel_bपढ़ोcrumbs_create(शून्य);
	अगर (!engine->bपढ़ोcrumbs)
		वापस -ENOMEM;

	ce = create_kernel_context(engine);
	अगर (IS_ERR(ce))
		जाओ err_bपढ़ोcrumbs;

	/* We insist the kernel context is using the status_page */
	engine->status_page.vma = ce->समयline->hwsp_ggtt;

	engine->kernel_context = ce;
	वापस 0;

err_bपढ़ोcrumbs:
	पूर्णांकel_bपढ़ोcrumbs_मुक्त(engine->bपढ़ोcrumbs);
	वापस -ENOMEM;
पूर्ण

व्योम mock_engine_flush(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा mock_engine *mock =
		container_of(engine, typeof(*mock), base);
	काष्ठा i915_request *request, *rn;

	del_समयr_sync(&mock->hw_delay);

	spin_lock_irq(&mock->hw_lock);
	list_क्रम_each_entry_safe(request, rn, &mock->hw_queue, mock.link)
		advance(request);
	spin_unlock_irq(&mock->hw_lock);
पूर्ण

व्योम mock_engine_reset(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
पूर्ण
