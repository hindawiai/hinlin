<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "i915_gem_client_blt.h"
#समावेश "i915_gem_object_blt.h"

काष्ठा i915_sleeve अणु
	काष्ठा i915_vma *vma;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा sg_table *pages;
	काष्ठा i915_page_sizes page_sizes;
पूर्ण;

अटल पूर्णांक vma_set_pages(काष्ठा i915_vma *vma)
अणु
	काष्ठा i915_sleeve *sleeve = vma->निजी;

	vma->pages = sleeve->pages;
	vma->page_sizes = sleeve->page_sizes;

	वापस 0;
पूर्ण

अटल व्योम vma_clear_pages(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!vma->pages);
	vma->pages = शून्य;
पूर्ण

अटल व्योम vma_bind(काष्ठा i915_address_space *vm,
		     काष्ठा i915_vm_pt_stash *stash,
		     काष्ठा i915_vma *vma,
		     क्रमागत i915_cache_level cache_level,
		     u32 flags)
अणु
	vm->vma_ops.bind_vma(vm, stash, vma, cache_level, flags);
पूर्ण

अटल व्योम vma_unbind(काष्ठा i915_address_space *vm, काष्ठा i915_vma *vma)
अणु
	vm->vma_ops.unbind_vma(vm, vma);
पूर्ण

अटल स्थिर काष्ठा i915_vma_ops proxy_vma_ops = अणु
	.set_pages = vma_set_pages,
	.clear_pages = vma_clear_pages,
	.bind_vma = vma_bind,
	.unbind_vma = vma_unbind,
पूर्ण;

अटल काष्ठा i915_sleeve *create_sleeve(काष्ठा i915_address_space *vm,
					 काष्ठा drm_i915_gem_object *obj,
					 काष्ठा sg_table *pages,
					 काष्ठा i915_page_sizes *page_sizes)
अणु
	काष्ठा i915_sleeve *sleeve;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	sleeve = kzalloc(माप(*sleeve), GFP_KERNEL);
	अगर (!sleeve)
		वापस ERR_PTR(-ENOMEM);

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_मुक्त;
	पूर्ण

	vma->निजी = sleeve;
	vma->ops = &proxy_vma_ops;

	sleeve->vma = vma;
	sleeve->pages = pages;
	sleeve->page_sizes = *page_sizes;

	वापस sleeve;

err_मुक्त:
	kमुक्त(sleeve);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम destroy_sleeve(काष्ठा i915_sleeve *sleeve)
अणु
	kमुक्त(sleeve);
पूर्ण

काष्ठा clear_pages_work अणु
	काष्ठा dma_fence dma;
	काष्ठा dma_fence_cb cb;
	काष्ठा i915_sw_fence रुको;
	काष्ठा work_काष्ठा work;
	काष्ठा irq_work irq_work;
	काष्ठा i915_sleeve *sleeve;
	काष्ठा पूर्णांकel_context *ce;
	u32 value;
पूर्ण;

अटल स्थिर अक्षर *clear_pages_work_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस DRIVER_NAME;
पूर्ण

अटल स्थिर अक्षर *clear_pages_work_समयline_name(काष्ठा dma_fence *fence)
अणु
	वापस "clear";
पूर्ण

अटल व्योम clear_pages_work_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा clear_pages_work *w = container_of(fence, typeof(*w), dma);

	destroy_sleeve(w->sleeve);

	i915_sw_fence_fini(&w->रुको);

	BUILD_BUG_ON(दुरत्व(typeof(*w), dma));
	dma_fence_मुक्त(&w->dma);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops clear_pages_work_ops = अणु
	.get_driver_name = clear_pages_work_driver_name,
	.get_समयline_name = clear_pages_work_समयline_name,
	.release = clear_pages_work_release,
पूर्ण;

अटल व्योम clear_pages_संकेत_irq_worker(काष्ठा irq_work *work)
अणु
	काष्ठा clear_pages_work *w = container_of(work, typeof(*w), irq_work);

	dma_fence_संकेत(&w->dma);
	dma_fence_put(&w->dma);
पूर्ण

अटल व्योम clear_pages_dma_fence_cb(काष्ठा dma_fence *fence,
				     काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा clear_pages_work *w = container_of(cb, typeof(*w), cb);

	अगर (fence->error)
		dma_fence_set_error(&w->dma, fence->error);

	/*
	 * Push the संकेतling of the fence पूर्णांकo yet another worker to aव्योम
	 * the nighपंचांगare locking around the fence spinlock.
	 */
	irq_work_queue(&w->irq_work);
पूर्ण

अटल व्योम clear_pages_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा clear_pages_work *w = container_of(work, typeof(*w), work);
	काष्ठा drm_i915_gem_object *obj = w->sleeve->vma->obj;
	काष्ठा i915_vma *vma = w->sleeve->vma;
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *batch;
	पूर्णांक err = w->dma.error;

	अगर (unlikely(err))
		जाओ out_संकेत;

	अगर (obj->cache_dirty) अणु
		अगर (i915_gem_object_has_काष्ठा_page(obj))
			drm_clflush_sg(w->sleeve->pages);
		obj->cache_dirty = false;
	पूर्ण
	obj->पढ़ो_करोमुख्यs = I915_GEM_GPU_DOMAINS;
	obj->ग_लिखो_करोमुख्य = 0;

	i915_gem_ww_ctx_init(&ww, false);
	पूर्णांकel_engine_pm_get(w->ce->engine);
retry:
	err = पूर्णांकel_context_pin_ww(w->ce, &ww);
	अगर (err)
		जाओ out_संकेत;

	batch = पूर्णांकel_emit_vma_fill_blt(w->ce, vma, &ww, w->value);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_ctx;
	पूर्ण

	rq = i915_request_create(w->ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_batch;
	पूर्ण

	/* There's no way the fence has संकेतled */
	अगर (dma_fence_add_callback(&rq->fence, &w->cb,
				   clear_pages_dma_fence_cb))
		GEM_BUG_ON(1);

	err = पूर्णांकel_emit_vma_mark_active(batch, rq);
	अगर (unlikely(err))
		जाओ out_request;

	/*
	 * w->dma is alपढ़ोy exported via (vma|obj)->resv we need only
	 * keep track of the GPU activity within this vma/request, and
	 * propagate the संकेत from the request to w->dma.
	 */
	err = __i915_vma_move_to_active(vma, rq);
	अगर (err)
		जाओ out_request;

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (unlikely(err))
			जाओ out_request;
	पूर्ण

	err = rq->engine->emit_bb_start(rq,
					batch->node.start, batch->node.size,
					0);
out_request:
	अगर (unlikely(err)) अणु
		i915_request_set_error_once(rq, err);
		err = 0;
	पूर्ण

	i915_request_add(rq);
out_batch:
	पूर्णांकel_emit_vma_release(w->ce, batch);
out_ctx:
	पूर्णांकel_context_unpin(w->ce);
out_संकेत:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	i915_vma_unpin(w->sleeve->vma);
	पूर्णांकel_engine_pm_put(w->ce->engine);

	अगर (unlikely(err)) अणु
		dma_fence_set_error(&w->dma, err);
		dma_fence_संकेत(&w->dma);
		dma_fence_put(&w->dma);
	पूर्ण
पूर्ण

अटल पूर्णांक pin_रुको_clear_pages_work(काष्ठा clear_pages_work *w,
				     काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_vma *vma = w->sleeve->vma;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, false);
retry:
	err = i915_gem_object_lock(vma->obj, &ww);
	अगर (err)
		जाओ out;

	err = i915_vma_pin_ww(vma, &ww, 0, 0, PIN_USER);
	अगर (unlikely(err))
		जाओ out;

	err = i915_sw_fence_aरुको_reservation(&w->रुको,
					      vma->obj->base.resv, शून्य,
					      true, 0, I915_FENCE_GFP);
	अगर (err)
		जाओ err_unpin_vma;

	dma_resv_add_excl_fence(vma->obj->base.resv, &w->dma);

err_unpin_vma:
	अगर (err)
		i915_vma_unpin(vma);
out:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	वापस err;
पूर्ण

अटल पूर्णांक __i915_sw_fence_call
clear_pages_work_notअगरy(काष्ठा i915_sw_fence *fence,
			क्रमागत i915_sw_fence_notअगरy state)
अणु
	काष्ठा clear_pages_work *w = container_of(fence, typeof(*w), रुको);

	चयन (state) अणु
	हाल FENCE_COMPLETE:
		schedule_work(&w->work);
		अवरोध;

	हाल FENCE_FREE:
		dma_fence_put(&w->dma);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल DEFINE_SPINLOCK(fence_lock);

/* XXX: better name please */
पूर्णांक i915_gem_schedule_fill_pages_blt(काष्ठा drm_i915_gem_object *obj,
				     काष्ठा पूर्णांकel_context *ce,
				     काष्ठा sg_table *pages,
				     काष्ठा i915_page_sizes *page_sizes,
				     u32 value)
अणु
	काष्ठा clear_pages_work *work;
	काष्ठा i915_sleeve *sleeve;
	पूर्णांक err;

	sleeve = create_sleeve(ce->vm, obj, pages, page_sizes);
	अगर (IS_ERR(sleeve))
		वापस PTR_ERR(sleeve);

	work = kदो_स्मृति(माप(*work), GFP_KERNEL);
	अगर (!work) अणु
		destroy_sleeve(sleeve);
		वापस -ENOMEM;
	पूर्ण

	work->value = value;
	work->sleeve = sleeve;
	work->ce = ce;

	INIT_WORK(&work->work, clear_pages_worker);

	init_irq_work(&work->irq_work, clear_pages_संकेत_irq_worker);

	dma_fence_init(&work->dma, &clear_pages_work_ops, &fence_lock, 0, 0);
	i915_sw_fence_init(&work->रुको, clear_pages_work_notअगरy);

	err = pin_रुको_clear_pages_work(work, ce);
	अगर (err < 0)
		dma_fence_set_error(&work->dma, err);

	dma_fence_get(&work->dma);
	i915_sw_fence_commit(&work->रुको);

	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_gem_client_blt.c"
#पूर्ण_अगर
