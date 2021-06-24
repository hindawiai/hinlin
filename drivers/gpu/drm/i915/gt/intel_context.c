<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_pm.h"

#समावेश "i915_drv.h"
#समावेश "i915_globals.h"

#समावेश "intel_context.h"
#समावेश "intel_engine.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_ring.h"

अटल काष्ठा i915_global_context अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_ce;
पूर्ण global;

अटल काष्ठा पूर्णांकel_context *पूर्णांकel_context_alloc(व्योम)
अणु
	वापस kmem_cache_zalloc(global.slab_ce, GFP_KERNEL);
पूर्ण

अटल व्योम rcu_context_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा पूर्णांकel_context *ce = container_of(rcu, typeof(*ce), rcu);

	kmem_cache_मुक्त(global.slab_ce, ce);
पूर्ण

व्योम पूर्णांकel_context_मुक्त(काष्ठा पूर्णांकel_context *ce)
अणु
	call_rcu(&ce->rcu, rcu_context_मुक्त);
पूर्ण

काष्ठा पूर्णांकel_context *
पूर्णांकel_context_create(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;

	ce = पूर्णांकel_context_alloc();
	अगर (!ce)
		वापस ERR_PTR(-ENOMEM);

	पूर्णांकel_context_init(ce, engine);
	वापस ce;
पूर्ण

पूर्णांक पूर्णांकel_context_alloc_state(काष्ठा पूर्णांकel_context *ce)
अणु
	पूर्णांक err = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&ce->pin_mutex))
		वापस -EINTR;

	अगर (!test_bit(CONTEXT_ALLOC_BIT, &ce->flags)) अणु
		अगर (पूर्णांकel_context_is_banned(ce)) अणु
			err = -EIO;
			जाओ unlock;
		पूर्ण

		err = ce->ops->alloc(ce);
		अगर (unlikely(err))
			जाओ unlock;

		set_bit(CONTEXT_ALLOC_BIT, &ce->flags);
	पूर्ण

unlock:
	mutex_unlock(&ce->pin_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_context_active_acquire(काष्ठा पूर्णांकel_context *ce)
अणु
	पूर्णांक err;

	__i915_active_acquire(&ce->active);

	अगर (पूर्णांकel_context_is_barrier(ce))
		वापस 0;

	/* Pपुनः_स्मृतिate tracking nodes */
	err = i915_active_acquire_pपुनः_स्मृतिate_barrier(&ce->active,
						      ce->engine);
	अगर (err)
		i915_active_release(&ce->active);

	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_context_active_release(काष्ठा पूर्णांकel_context *ce)
अणु
	/* Nodes pपुनः_स्मृतिated in पूर्णांकel_context_active() */
	i915_active_acquire_barrier(&ce->active);
	i915_active_release(&ce->active);
पूर्ण

अटल पूर्णांक __context_pin_state(काष्ठा i915_vma *vma, काष्ठा i915_gem_ww_ctx *ww)
अणु
	अचिन्हित पूर्णांक bias = i915_ggtt_pin_bias(vma) | PIN_OFFSET_BIAS;
	पूर्णांक err;

	err = i915_ggtt_pin(vma, ww, 0, bias | PIN_HIGH);
	अगर (err)
		वापस err;

	err = i915_active_acquire(&vma->active);
	अगर (err)
		जाओ err_unpin;

	/*
	 * And mark it as a globally pinned object to let the shrinker know
	 * it cannot reclaim the object until we release it.
	 */
	i915_vma_make_unshrinkable(vma);
	vma->obj->mm.dirty = true;

	वापस 0;

err_unpin:
	i915_vma_unpin(vma);
	वापस err;
पूर्ण

अटल व्योम __context_unpin_state(काष्ठा i915_vma *vma)
अणु
	i915_vma_make_shrinkable(vma);
	i915_active_release(&vma->active);
	__i915_vma_unpin(vma);
पूर्ण

अटल पूर्णांक __ring_active(काष्ठा पूर्णांकel_ring *ring,
			 काष्ठा i915_gem_ww_ctx *ww)
अणु
	पूर्णांक err;

	err = पूर्णांकel_ring_pin(ring, ww);
	अगर (err)
		वापस err;

	err = i915_active_acquire(&ring->vma->active);
	अगर (err)
		जाओ err_pin;

	वापस 0;

err_pin:
	पूर्णांकel_ring_unpin(ring);
	वापस err;
पूर्ण

अटल व्योम __ring_retire(काष्ठा पूर्णांकel_ring *ring)
अणु
	i915_active_release(&ring->vma->active);
	पूर्णांकel_ring_unpin(ring);
पूर्ण

अटल पूर्णांक पूर्णांकel_context_pre_pin(काष्ठा पूर्णांकel_context *ce,
				 काष्ठा i915_gem_ww_ctx *ww)
अणु
	पूर्णांक err;

	CE_TRACE(ce, "active\n");

	err = __ring_active(ce->ring, ww);
	अगर (err)
		वापस err;

	err = पूर्णांकel_समयline_pin(ce->समयline, ww);
	अगर (err)
		जाओ err_ring;

	अगर (!ce->state)
		वापस 0;

	err = __context_pin_state(ce->state, ww);
	अगर (err)
		जाओ err_समयline;


	वापस 0;

err_समयline:
	पूर्णांकel_समयline_unpin(ce->समयline);
err_ring:
	__ring_retire(ce->ring);
	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_context_post_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
	अगर (ce->state)
		__context_unpin_state(ce->state);

	पूर्णांकel_समयline_unpin(ce->समयline);
	__ring_retire(ce->ring);
पूर्ण

पूर्णांक __पूर्णांकel_context_करो_pin_ww(काष्ठा पूर्णांकel_context *ce,
			      काष्ठा i915_gem_ww_ctx *ww)
अणु
	bool hanकरोff = false;
	व्योम *vaddr;
	पूर्णांक err = 0;

	अगर (unlikely(!test_bit(CONTEXT_ALLOC_BIT, &ce->flags))) अणु
		err = पूर्णांकel_context_alloc_state(ce);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * We always pin the context/ring/समयline here, to ensure a pin
	 * refcount क्रम __पूर्णांकel_context_active(), which prevent a lock
	 * inversion of ce->pin_mutex vs dma_resv_lock().
	 */

	err = i915_gem_object_lock(ce->समयline->hwsp_ggtt->obj, ww);
	अगर (!err && ce->ring->vma->obj)
		err = i915_gem_object_lock(ce->ring->vma->obj, ww);
	अगर (!err && ce->state)
		err = i915_gem_object_lock(ce->state->obj, ww);
	अगर (!err)
		err = पूर्णांकel_context_pre_pin(ce, ww);
	अगर (err)
		वापस err;

	err = i915_active_acquire(&ce->active);
	अगर (err)
		जाओ err_ctx_unpin;

	err = ce->ops->pre_pin(ce, ww, &vaddr);
	अगर (err)
		जाओ err_release;

	err = mutex_lock_पूर्णांकerruptible(&ce->pin_mutex);
	अगर (err)
		जाओ err_post_unpin;

	अगर (unlikely(पूर्णांकel_context_is_बंदd(ce))) अणु
		err = -ENOENT;
		जाओ err_unlock;
	पूर्ण

	अगर (likely(!atomic_add_unless(&ce->pin_count, 1, 0))) अणु
		err = पूर्णांकel_context_active_acquire(ce);
		अगर (unlikely(err))
			जाओ err_unlock;

		err = ce->ops->pin(ce, vaddr);
		अगर (err) अणु
			पूर्णांकel_context_active_release(ce);
			जाओ err_unlock;
		पूर्ण

		CE_TRACE(ce, "pin ring:{start:%08x, head:%04x, tail:%04x}\n",
			 i915_ggtt_offset(ce->ring->vma),
			 ce->ring->head, ce->ring->tail);

		hanकरोff = true;
		smp_mb__beक्रमe_atomic(); /* flush pin beक्रमe it is visible */
		atomic_inc(&ce->pin_count);
	पूर्ण

	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(ce)); /* no overflow! */

err_unlock:
	mutex_unlock(&ce->pin_mutex);
err_post_unpin:
	अगर (!hanकरोff)
		ce->ops->post_unpin(ce);
err_release:
	i915_active_release(&ce->active);
err_ctx_unpin:
	पूर्णांकel_context_post_unpin(ce);

	/*
	 * Unlock the hwsp_ggtt object since it's shared.
	 * In principle we can unlock all the global state locked above
	 * since it's pinned and doesn't need fencing, and will
	 * thus reमुख्य resident until it is explicitly unpinned.
	 */
	i915_gem_ww_unlock_single(ce->समयline->hwsp_ggtt->obj);

	वापस err;
पूर्ण

पूर्णांक __पूर्णांकel_context_करो_pin(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = __पूर्णांकel_context_करो_pin_ww(ce, &ww);
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	वापस err;
पूर्ण

व्योम पूर्णांकel_context_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
	अगर (!atomic_dec_and_test(&ce->pin_count))
		वापस;

	CE_TRACE(ce, "unpin\n");
	ce->ops->unpin(ce);
	ce->ops->post_unpin(ce);

	/*
	 * Once released, we may asynchronously drop the active reference.
	 * As that may be the only reference keeping the context alive,
	 * take an extra now so that it is not मुक्तd beक्रमe we finish
	 * dereferencing it.
	 */
	पूर्णांकel_context_get(ce);
	पूर्णांकel_context_active_release(ce);
	पूर्णांकel_context_put(ce);
पूर्ण

__i915_active_call
अटल व्योम __पूर्णांकel_context_retire(काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_context *ce = container_of(active, typeof(*ce), active);

	CE_TRACE(ce, "retire runtime: { total:%lluns, avg:%lluns }\n",
		 पूर्णांकel_context_get_total_runसमय_ns(ce),
		 पूर्णांकel_context_get_avg_runसमय_ns(ce));

	set_bit(CONTEXT_VALID_BIT, &ce->flags);
	पूर्णांकel_context_post_unpin(ce);
	पूर्णांकel_context_put(ce);
पूर्ण

अटल पूर्णांक __पूर्णांकel_context_active(काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_context *ce = container_of(active, typeof(*ce), active);

	पूर्णांकel_context_get(ce);

	/* everything should alपढ़ोy be activated by पूर्णांकel_context_pre_pin() */
	GEM_WARN_ON(!i915_active_acquire_अगर_busy(&ce->ring->vma->active));
	__पूर्णांकel_ring_pin(ce->ring);

	__पूर्णांकel_समयline_pin(ce->समयline);

	अगर (ce->state) अणु
		GEM_WARN_ON(!i915_active_acquire_अगर_busy(&ce->state->active));
		__i915_vma_pin(ce->state);
		i915_vma_make_unshrinkable(ce->state);
	पूर्ण

	वापस 0;
पूर्ण

व्योम
पूर्णांकel_context_init(काष्ठा पूर्णांकel_context *ce, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	GEM_BUG_ON(!engine->cops);
	GEM_BUG_ON(!engine->gt->vm);

	kref_init(&ce->ref);

	ce->engine = engine;
	ce->ops = engine->cops;
	ce->sseu = engine->sseu;
	ce->ring = __पूर्णांकel_context_ring_size(SZ_4K);

	ewma_runसमय_init(&ce->runसमय.avg);

	ce->vm = i915_vm_get(engine->gt->vm);

	/* NB ce->संकेत_link/lock is used under RCU */
	spin_lock_init(&ce->संकेत_lock);
	INIT_LIST_HEAD(&ce->संकेतs);

	mutex_init(&ce->pin_mutex);

	i915_active_init(&ce->active,
			 __पूर्णांकel_context_active, __पूर्णांकel_context_retire);
पूर्ण

व्योम पूर्णांकel_context_fini(काष्ठा पूर्णांकel_context *ce)
अणु
	अगर (ce->समयline)
		पूर्णांकel_समयline_put(ce->समयline);
	i915_vm_put(ce->vm);

	mutex_destroy(&ce->pin_mutex);
	i915_active_fini(&ce->active);
पूर्ण

अटल व्योम i915_global_context_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_ce);
पूर्ण

अटल व्योम i915_global_context_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_ce);
पूर्ण

अटल काष्ठा i915_global_context global = अणु अणु
	.shrink = i915_global_context_shrink,
	.निकास = i915_global_context_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_context_init(व्योम)
अणु
	global.slab_ce = KMEM_CACHE(पूर्णांकel_context, SLAB_HWCACHE_ALIGN);
	अगर (!global.slab_ce)
		वापस -ENOMEM;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;
पूर्ण

व्योम पूर्णांकel_context_enter_engine(काष्ठा पूर्णांकel_context *ce)
अणु
	पूर्णांकel_engine_pm_get(ce->engine);
	पूर्णांकel_समयline_enter(ce->समयline);
पूर्ण

व्योम पूर्णांकel_context_निकास_engine(काष्ठा पूर्णांकel_context *ce)
अणु
	पूर्णांकel_समयline_निकास(ce->समयline);
	पूर्णांकel_engine_pm_put(ce->engine);
पूर्ण

पूर्णांक पूर्णांकel_context_prepare_remote_request(काष्ठा पूर्णांकel_context *ce,
					 काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_समयline *tl = ce->समयline;
	पूर्णांक err;

	/* Only suitable क्रम use in remotely modअगरying this context */
	GEM_BUG_ON(rq->context == ce);

	अगर (rcu_access_poपूर्णांकer(rq->समयline) != tl) अणु /* समयline sharing! */
		/* Queue this चयन after current activity by this context. */
		err = i915_active_fence_set(&tl->last_request, rq);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Guarantee context image and the समयline reमुख्यs pinned until the
	 * modअगरying request is retired by setting the ce activity tracker.
	 *
	 * But we only need to take one pin on the account of it. Or in other
	 * words transfer the pinned ce object to tracked active request.
	 */
	GEM_BUG_ON(i915_active_is_idle(&ce->active));
	वापस i915_active_add_request(&ce->active, rq);
पूर्ण

काष्ठा i915_request *पूर्णांकel_context_create_request(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_request *rq;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = पूर्णांकel_context_pin_ww(ce, &ww);
	अगर (!err) अणु
		rq = i915_request_create(ce);
		पूर्णांकel_context_unpin(ce);
	पूर्ण अन्यथा अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
		rq = ERR_PTR(err);
	पूर्ण अन्यथा अणु
		rq = ERR_PTR(err);
	पूर्ण

	i915_gem_ww_ctx_fini(&ww);

	अगर (IS_ERR(rq))
		वापस rq;

	/*
	 * समयline->mutex should be the inner lock, but is used as outer lock.
	 * Hack around this to shut up lockdep in selftests..
	 */
	lockdep_unpin_lock(&ce->समयline->mutex, rq->cookie);
	mutex_release(&ce->समयline->mutex.dep_map, _RET_IP_);
	mutex_acquire(&ce->समयline->mutex.dep_map, SINGLE_DEPTH_NESTING, 0, _RET_IP_);
	rq->cookie = lockdep_pin_lock(&ce->समयline->mutex);

	वापस rq;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_context.c"
#पूर्ण_अगर
